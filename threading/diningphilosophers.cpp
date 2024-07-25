#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <mutex>
#include <syncstream>
#include <condition_variable>
#include <thread>

using namespace std;

template<typename... Args>
void print(Args &&... args) {
    std::osyncstream bout{std::cout};
    (bout << ... << std::forward<Args>(args)) << endl;
}

/*
 * SEMAPHORES
 * A synchronization primitive used to keep track of the number of threads accessing a section of
 * code (n-thread access).
 * - initialized to a non-negative integer
 * - P() - waits until value is positive then atomically decrements it
 * - V() - atomically increments value
 */

struct Semaphore {
    mutex mtx;
    int count;
    condition_variable_any cv;

    Semaphore(int count) : count(count) {};

    void wait() {
        lock_guard<mutex> lg{mtx};
        cv.wait(mtx, [this] { return count > 0; });
        count--;
    }

    void signal() {
        lock_guard<mutex> lg{mtx};
        count++;
        if (count > 0) cv.notify_one();
    }
};

/*
 * Dining Philosopher problem:
 * 5 Philosophers at a time. Randomly, they think, eat, think, eat, think, eat. When they eat,
 * they eat with 2 forks. There are 5 forks.
 *
 * If all 5 philosophers pick up left fork, all deadlocks.
 */

const int PEOPLE = 5; //people at roundtable
const int CYCLES = 1; //think eat cycles
const int TIME = 3; //times eaten
random_device rd;
mutex io_mutex;
Semaphore s{PEOPLE - 1};

class Philosopher {
public:
    Philosopher(int id) : id(id), gen(rd()), unigen(0, TIME) {}

    //sleep time from [0, TIME]
    void sleep() {
        this_thread::sleep_for(chrono::seconds(unigen(gen)));
    }

    void think() {
        print("uhh... philosopher: ", id, " is starting to think");
        sleep();
        print("philosopher: ", id, " is done thinking");
    }

    void eat(mutex &fork1, mutex &fork2) {
        s.wait();
        fork1.lock();
        this_thread::sleep_for(chrono::seconds(unigen(gen)));
        fork2.lock();
        print("yum! philosopher: ", id, " is eating");
        fork1.unlock();
        io_mutex.lock();
        fork2.unlock();
        print("yay!! philosopher: ", id, " ate!");
        io_mutex.unlock();
        s.signal();
    }

    void dine(mutex &fork1, mutex &fork2) {
        for (int i = 0; i < CYCLES; i++) {
            think();
            eat(fork1, fork2);
        }
    }

    int id;
private:
    mt19937 gen;
    uniform_int_distribution<int> unigen;
};

vector<Philosopher> philosophers;

void startDining() {
    vector<thread> v(PEOPLE);
    vector<mutex> fork(PEOPLE);
    for (int i = 0; i < PEOPLE; i++) {
        v[i] = thread(&Philosopher::dine, &philosophers[i], ref(fork[i]),
                      ref(fork[(i + 1) % PEOPLE]));
    }
    for (int i = 0; i < PEOPLE; i++) {
        v[i].join();
    }
}

int main() {
    for (int i = 0; i < PEOPLE; i++) {
        philosophers.emplace_back(i);
    }
    startDining();
}

