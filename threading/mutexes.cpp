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
timed_mutex tmtx; // Timed mutex
recursive_mutex rmtx; // Recursive mutex
shared_mutex shmtx; // Shared mutex

template<typename... Args>
void print(Args &&... args) {
    std::osyncstream bout{std::cout};
    (bout << ... << std::forward<Args>(args)) << endl;
}

/* 1) mutex: only one thread can enter critical section
 *    - lock()
 *    - unlock()
 *    - try_lock() - returns true and locks the mutex if lock is available, false otherwise (may
 *      spuriously be false)
 */
void regular_lock(int num) {
    mtx.lock();
    print("thread id: ", std::this_thread::get_id(), " num: ", num);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    mtx.unlock();
}

/* 2) timed_mutex: similar to mutex, but can be locked with a timeout
 *    - lock(), unlock(), try_lock()
 *    - try_lock_for/try_lock_until(time)
 *       tries lock for/until specified time
 */
void timed_lock(int num) {
    //all can acquire lock
    if (tmtx.try_lock_for(std::chrono::milliseconds(10000))) {
        print("thread id: ", std::this_thread::get_id(), " num: ", num);
        std::this_thread::sleep_for(std::chrono::milliseconds(400)); // Simulate work
        print("thread ", std::this_thread::get_id(), " awoke!");
        tmtx.unlock();
    } else {
        print("thread id: ", std::this_thread::get_id(), " num: ", num, " failed to acquire lock");
    }
}

/* 3) recursive_mutex: allows the same thread to lock the mutex multiple times
 *    - lock(), unlock(), try_lock()
 *       - can lock more than once by owning thread
 *    - useful if you are recursively calling a function (if you have one mutex, you can't obtain
 *    the lock again)
 *    - useful if you are calling two members functions from each other
 */
void recursive_lock(int depth) {
    if (depth > 0) {
        rmtx.lock();
        print("thread id: ", std::this_thread::get_id(), " depth: ", depth);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        recursive_lock(depth - 1);
        rmtx.unlock();
    }
}

/* 4) shared_mutex: allows multiple readers or one writer
 * PART OF SHARED_MUTEX HEADER, NOT MUTEX HEADER
 *    - lock()/unlock() - exclusive (writer) lock; only 1 exclusive lock and no shared lock may be
 *       held
 *    - lock_shared()/unlock_shared() - many threads may hold a shared lock at a given time, but
 *       no exclusive lock may be held
 */
void shared_read(int num) {
    shmtx.lock_shared();
    print("Reader thread id: ", std::this_thread::get_id(), " num: ", num);
    shmtx.unlock_shared();
}

void shared_write(int num) {
    if (shmtx.try_lock()) {
        print("Writer thread id: ", std::this_thread::get_id(), " num: ", num);
        shmtx.unlock();
    } else {
        print("Writer thread id: ", std::this_thread::get_id(), " failed to get lock.");
    }
}

/*
 * 5, 6) shared_timed_mutex and recursive_timed_mutex also exist
 */
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
     * TYPES OF MUTEXES
     * 1) mutex
     */
    print("Using regular mutex:");
    create_threads(regular_lock);

    /*
     * 2) timed_mutex
     */
    print("Using timed mutex:");
    create_threads(timed_lock);

    /*
     * 3) recursive_mutex
     */
    print("Using recursive mutex:");
    create_threads(recursive_lock);

    /*
     * 4) shared_mutex
     *    sometimes, a writer will fail to get the lock
     */
    print("Using shared mutex (readers):");
    for (int i = 0; i < THREADS; i++) {
        threads.emplace_back(shared_read, i);
    }

    print("Using shared mutex (writer):");
    for (int i = 0; i < THREADS; i++) {
        threads.emplace_back(shared_write, i);
    }
    for (int i = 0; i < 2 * THREADS; i++) {
        threads[i].join();
    }
    threads.clear();

    return 0;
}
