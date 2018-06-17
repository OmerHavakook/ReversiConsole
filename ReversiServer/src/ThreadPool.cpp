
#include "../include/ThreadPool.h"
#include <unistd.h>

ThreadPool::ThreadPool(int threadsNum) : stopped(false) {
    // create a new array of threads
    threads = new pthread_t[threadsNum];
    // create threads
    for (int i = 0; i < threadsNum; i++) {
        pthread_create(threads + i, NULL, execute, this);
    }
    pthread_mutex_init(&lock, NULL);
}

ThreadPool::~ThreadPool() {
    delete[] threads;
}

void *ThreadPool::execute(void *arg) {
    // save args in a ThreadPool var
    ThreadPool *pool = (ThreadPool *) arg;
    // execute the task
    pool->executeTasks();
}

void ThreadPool::addTask(Task *task) {
    // push task to the queue
    tasksQueue.push(task);
}

void ThreadPool::executeTasks() {
    // as long as the program should countinue working
    while (!stopped) {
        pthread_mutex_lock(&lock);
        // if the queue is not empty
        if (!tasksQueue.empty()) {
            // save the task in the front of the queue
            Task *task = tasksQueue.front();
            // pop the task from the the queue
            tasksQueue.pop();
            pthread_mutex_unlock(&lock);
            // execute the task
            task->execute();
            delete task;
        } else { // if the queue is empty than just sleep
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
}

void ThreadPool::terminate() {
    // change the bol member to true
    pthread_mutex_destroy(&lock);
    stopped = true;
}