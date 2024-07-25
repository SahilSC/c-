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
 * CONDITION VARIABLES
 * A synchronization variable used to efficiently wait for a shared state variable protected
 * by a lock
 */

/*
 * Conditional Variable Vs. Semaphore
 * - A conditional variable waits efficiently until some condition occurs, whereas a semaphore acts
 *   as a counter simply keeps tracks of the number of threads accessing a critical section of code
 * - Conditional Variables are stateless (queue of waiting threads, calling notify_one with
 *   another thread after calling wait still forces a wait), semaphores have state (mutex + counter
 *   + queue, calling notify_one/signal allows future thread that calls wait to be put in ready q)
 * - Conditional variables are for more event driven application, semaphores are used to keep
 *   track of number of threads
 *   - Conditional variables block its caller on wait, semaphores do not have to block (only when
 *   internal counter is 0)
 */

/*
 * condition_variable_any - allows efficienting waiting on any lock with .lock and .unlock
 *    (condition_variable only can operate on unique_lock<mutex> types)
 *    - NOTE: often used in conjunction with a lock and shared state to: lock to update/read
 *      the shared resource, then use .wait to efficiently wait until a condition is met
 *      (efficiency comes from putting the current thread from the ready to wait queue)
 *      wait(Lock& lock) calls lock.unlock() and places thread on waiting queue for scheduler until
 *      placed on ready queue by notify_one()/notify_all()
 *    - wait (Lock& lock, Predicate pred): while(!pred) cv.wait(lock);
 *    - notify_one() - places a thread on the cv's waiting queue on the ready queue
 *    - notify_all() - places all threads on the cv's waiting queue on the ready queue
 */


/*
 * Dining Philosopher problem:
 * 5 Philosophers at a time. Randomly, they think, eat, think, eat, think, eat. When they eat,
 * they eat with 2 forks. There are 5 forks.
 *
 * If all 5 philosophers pick up left fork, all deadlocks.
 */
const int PEOPLE = 5;
const int CYCLES = 1;
const int TIME = 3;
random_device rd;
mutex io_mutex;

void waitForPermission();

void grantPermission();

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
        waitForPermission();
        fork1.lock();
        fork2.lock();
        print("yum! philosopher: ", id, " is eating");
        fork1.unlock();
        io_mutex.lock();
        fork2.unlock();
        print("yay!! philosopher: ", id, " ate!");
        io_mutex.unlock();
        grantPermission();

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

mutex mtx;
condition_variable_any canEat;
vector<Philosopher> philosophers;
int maxforks = PEOPLE - 1;

void waitForPermission() {
    lock_guard<mutex> lg{mtx};
    canEat.wait(mtx, [] { return maxforks > 0; });
    maxforks--;
}

void grantPermission() {
    lock_guard<mutex> lg{mtx};
    maxforks++;
    canEat.notify_one();
}

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

