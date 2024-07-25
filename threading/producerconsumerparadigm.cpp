#include <algorithm>
#include <mutex>
#include <vector>
#include <random>
#include <iostream>
#include <syncstream>
#include <queue>
#include <condition_variable>
#include <thread>

using namespace std;

template<typename... Args>
void print(Args &&... args) {
    std::osyncstream bout{std::cout};
    (bout << ... << std::forward<Args>(args)) << endl;
}

//BOTH INCLUSIVE
const int PRODUCER_TIME_MIN = 1;
const int PRODUCER_TIME_MAX = 2;
const int WORKER_TIME_MIN = 6;
const int WORKER_TIME_MAX = 8;
const int PROGRAM_DURATION = 50;
bool done = false;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> producergen(PRODUCER_TIME_MIN, PRODUCER_TIME_MAX);
uniform_int_distribution<int> workergen(WORKER_TIME_MIN, WORKER_TIME_MAX);
const int WORKER_THREADS = 11;
queue<int> q;
condition_variable_any cv;
mutex mtx;
vector<thread> producerThreads;
vector<thread> workerThreads;
int workCounter = 0;

void produce() {
    while (!done) {
        {
            scoped_lock<mutex> scl{mtx};
            q.push(workCounter);
            print("finished pushing work: ", workCounter);
        }
        this_thread::sleep_for(chrono::seconds(producergen(gen)));
        workCounter++;
        cv.notify_one();
    }
    //after done
    cv.notify_all();
}

void consume(int id) {
    unique_lock<mutex> lg{mtx};
    while (!done) {
        while (!q.empty()) {
            int j = q.front();
            q.pop();
            //assuming work takes majority of time
            lg.unlock();
            print("thread: ", id, " working: ", j);
            this_thread::sleep_for(chrono::seconds(workergen(gen)));
            lg.lock();
            print("thread: ", id, " finished work: ", j);
        }
        if (!done) cv.wait(lg);
    }
}

void createProducer() {
    producerThreads.emplace_back(produce);
}

void createWorkers() {
    for (int i = 0; i < WORKER_THREADS; i++)
        workerThreads.emplace_back(consume, i);
}

int main() {
    createProducer();
    createWorkers();
    this_thread::sleep_for(chrono::seconds(PROGRAM_DURATION));
    done = true;
    for (thread &t: producerThreads) t.join();
    for (thread &t: workerThreads) t.join();
}