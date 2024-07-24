#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mutex1;
std::mutex mutex2;

void thread1() {
    std::unique_lock<std::mutex> lock1(mutex1);
    std::cout << "Thread 1 acquired mutex1\n";

    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Attempt to acquire mutex2
    std::unique_lock<std::mutex> lock2(mutex2);
    std::cout << "Thread 1 acquired mutex2\n";
}

void thread2() {
    std::unique_lock<std::mutex> lock2(mutex2);
    std::cout << "Thread 2 acquired mutex2\n";

    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Attempt to acquire mutex1
    std::unique_lock<std::mutex> lock1(mutex1);
    std::cout << "Thread 2 acquired mutex1\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    
    t1.join();
    t2.join();

    return 0;
}
