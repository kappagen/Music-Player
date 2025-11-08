#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <functional>

/**
 * Simple ThreadPool for managing concurrent collaborative tasks.
 * Allows submitting tasks for asynchronous execution.
 */
class ThreadPool {
private:
    std::queue<std::function<void()>> tasks;
    bool stop;

public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    
    // Submit a task to the pool
    template<class F>
    void enqueue(F&& f);
    
    // Wait for all tasks to complete
    void wait();
};

// Template implementation must be in header
template<class F>
void ThreadPool::enqueue(F&& f) {
    if (stop) {
        throw std::runtime_error("ThreadPool is stopped");
    }
    tasks.emplace(std::forward<F>(f));
    // Execute immediately (simplified non-threaded version)
    tasks.front()();
    tasks.pop();
}

#endif // THREADPOOL_H