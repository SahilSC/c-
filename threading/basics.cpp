#include <iostream>
#include <syncstream>
#include <thread>
#include <mutex>

/* 1) Synchronization Variable - a data structure for coordinating concurrent access to
 *      shared state (locks, condition variables, mutex, semaphore). They coordinate access to state
 *      variables (normal fields of a class)
 * 2) Lock - a synchronization mechanism that typically only allows one thread to own it at a time,
 *      usually protecting access to a critical section (spin-lock read-write lock, reentrant locks)
 * 3) Mutex - a specific type of lock that provides mutual exclusion to a section of critical code,
 *      allowing only one thread to access the section at a time. It is system wide (across processes)

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
 * Mutex vs Semaphore:
 * - Mutex provides 1-access to piece of code, semaphore allows n-access
 * - Mutex typically used for accessing a shared resource, semaphores used for signaling
 * - Mutexes lock and unlock, semaphores wait and signal
 */

/*
 * Mutex vs Condition Variable
 * - They are typically used in conjunction with each other
 * - Mutexes are used to create exclusive access, condition variables are used for efficiently
 *   waiting and signaling on a condition. Without CVs, you would have to busy wait.
 */
void threadFunc(int a) {
    std::cout << "Thread " << std::this_thread::get_id() << " holds " << a << std::endl;
}

int main() {
    /*
     * THREAD BASICS
     * thread(function, arguments) - creating thread
     * std::this_thread::get_id() OR thread.get_id() - getting id of thread
     * t.join() - wait for thread t to finish before continuing this thread
     * t.joinable() - checks if thread is joinable (returns false if default constructed or already
     *    joined or detached). If a thread is finished but not joined, it is still joinable
     * std::osyncstream - locked version of std::cout (printing each string between << is thread
     *    safe, but the whole stream is not so you can get garbled output)
     */

    std::osyncstream bout{std::cout};
    std::thread a1(&threadFunc, 1);
    bout << "a1's id" << a1.get_id() << std::endl;

    if (a1.joinable())
        bout << "a1 is joinable" << std::endl; //this prints

    a1.join();
    bout << "MAIN Thread: " << std::this_thread::get_id() << " ending " << std::endl;
}
