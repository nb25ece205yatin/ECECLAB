#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

atomic<int> unsynchronizedCounter{0};
atomic<int> readersReady{0};

void loseUpdateAtBarrier() {
    const int value = unsynchronizedCounter.load();
    readersReady.fetch_add(1);
    while (readersReady.load() != 2) {
        this_thread::yield();
    }
    unsynchronizedCounter.store(value + 1);
}

int safeCounter = 0;
mutex counterMutex;

void addSafely(int times) {
    for (int i = 0; i < times; ++i) {
        lock_guard<mutex> lock(counterMutex);
        ++safeCounter;
    }
}

int main() {
    cout << "Lost-update demonstration without lock_guard:\n";
    for (int run = 1; run <= 5; ++run) {
        unsynchronizedCounter.store(0);
        readersReady.store(0);
        thread first(loseUpdateAtBarrier);
        thread second(loseUpdateAtBarrier);
        first.join();
        second.join();
        cout << "Run " << run << ": counter = " << unsynchronizedCounter.load()
             << " (expected 2)\n";
    }

    thread first(addSafely, 100000);
    thread second(addSafely, 100000);
    first.join();
    second.join();
    cout << "With lock_guard: counter = " << safeCounter
         << " (expected 200000)\n";
    return 0;
}
