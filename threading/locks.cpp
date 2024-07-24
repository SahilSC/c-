#include <vector>
#include <iostream>
#include <syncstream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>

using namespace std;
const int THREADS = 5;
vector<thread> threads;
mutex mtx; // Standard mutex
mutex mtx2; // Standard mutex
timed_mutex tmtx; // Timed mutex
recursive_mutex rmtx; // Recursive mutex
shared_mutex shmtx; // Shared mutex

template<typename... Args>
void print(Args &&... args) {
    std::osyncstream bout{std::cout};
    (bout << ... << std::forward<Args>(args)) << endl;
}

/*
 * BASIC: lock(mutex m1, mutex m2, ...)
 *    - locks m1, m2, ... in a way to prevent deadlock
 *    - doesn't provide RAII or unlocking, so you should use unique_lock w/ defer lock or lock_guard
 *      after
 */
void lock_example(int num) {
    //method 1)
    {
        unique_lock<mutex> umtx{mtx, defer_lock};
        unique_lock<mutex> umtx2{mtx2, defer_lock};
        print("1) thread id: ", std::this_thread::get_id(), " waiting for mutexes");
        lock(umtx, umtx2);
    }
    print("1) thread id: ", std::this_thread::get_id(), " got mutexes");
    //method 2)
    {
        lock(mtx, mtx2);
        lock_guard<mutex> lmtx{mtx, adopt_lock};
        lock_guard<mutex> lmtx2{mtx2, adopt_lock};
        print("2) thread id: ", std::this_thread::get_id(), " waiting for mutexes");
    }
    print("2) thread id: ", std::this_thread::get_id(), " got mutexes");
    //method 3)
    {
        scoped_lock lock(mtx, mtx2);
        print("3) thread id: ", std::this_thread::get_id(), " waiting for mutexes");
    }
    print("3) thread id: ", std::this_thread::get_id(), " got mutexes");
}

/* 0) lock_guard(mutex)
 *    - provides RAII for a lock by trying to obtain the lock then unlocking when out of scope
 *    - simple version of unique_lock
 *    - can acquire lock using adopt_lock
 */
void lock_guard_example(int num) {
    lock_guard<mutex> lmtx{mtx};
    print("thread id: ", std::this_thread::get_id(), " obtained lmtx.");
}

/* 1) unique_lock(mutex)
 *    - like lock_guard, provides RAII for locks; it essentially is lock_guard with more
 *      functionality
 *    - manual locking (lock/unlock)
 *    - try_lock/try_lock_for/try_lock_until
 *    - deferred locking (std::defer_lock), try_to_lock (std::try_to_lock), adopt_lock
 *         (std::adopt_lock); pass as second parameter
 */
void unique_lock_example(int num) {
    unique_lock<mutex> lock(mtx);
    print("thread id: ", std::this_thread::get_id(), " num: ", num);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
}

/* 2) shared_lock:
 *    - allows multiple readers or one writer
 *    - provides RAII
 *    - lock()/unlock() - works on shared_lock
 *    - lock_shared()/unlock_shared() - many threads may hold a shared lock at a given time, but
 *       no exclusive lock may be held
 *    - try_lock()/try_lock_for()/try_lock_until()
 *    - can defer/adopt/try_to_lock
 */
void shared_read_example(int num) {
    shared_lock<shared_mutex> shmx{shmtx};
    print("Reader thread id: ", std::this_thread::get_id(), " num: ", num);
}

void shared_write_example(int num) {
    if (shmtx.try_lock()) {
        print("Writer thread id: ", std::this_thread::get_id(), " num: ", num);
        shmtx.unlock();
    } else {
        print("Writer thread id: ", std::this_thread::get_id(), " failed to get lock.");
    }
}

/* 3) scoped-lock(mutex m1, mutex m2, ...):
 *       - like lock, but uses RAII to unlock locks at end of scope
 */
void scoped_lock_example(int num) {
    scoped_lock sclk{mtx, mtx2};
    print("thread id: ", std::this_thread::get_id(), " holds both mutexes");
}

void create_threads(void (*func)(int)) {
    for (int i = 0; i < THREADS; i++)
        threads.emplace_back(func, i);
    for (int i = 0; i < THREADS; i++) {
        threads[i].join();
    }
    threads.clear();
}

int main() {
    /*
     * TYPES OF LOCKS
     */

    //BASIC) locks
    print("Using lock");
    create_threads(lock_example);

    //0) lock_guard
    print("Using lock_guard:");
    create_threads(lock_guard_example);

    //1) unique_lock
    print("Using unique_lock:");
    create_threads(unique_lock_example);

    //2) shared_lock
    print("Using shared_lock (readers):");
    for (int i = 0; i < THREADS; i++) {
        threads.emplace_back(shared_read_example, i);
    }

    print("Using shared_lock (writers):");
    for (int i = 0; i < THREADS; i++) {
        threads.emplace_back(shared_write_example, i);
    }
    for (int i = 0; i < 2 * THREADS; i++) {
        threads[i].join();
    }
    threads.clear();

    //3) scoped_lock
    print("Using scoped_lock: ");
    create_threads(scoped_lock_example);
    return 0;
}
