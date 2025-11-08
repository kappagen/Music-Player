#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    // Simplified non-threaded version (tasks execute immediately)
    (void)numThreads; // Unused in simplified version
}

ThreadPool::~ThreadPool() {
    stop = true;
}

void ThreadPool::wait() {
    // Simplified version - all tasks execute immediately, so nothing to wait for
}
