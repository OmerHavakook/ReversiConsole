
#ifndef REVERSISERVER_THREADPOOL_H
#define REVERSISERVER_THREADPOOL_H


#include "../include/Task.h"
#include <queue>
#include <pthread.h>

using namespace std;

class ThreadPool {
public:
    /**
     * constructor
     * @param threadsNum - the number of possible activated threads
     */
    ThreadPool(int threadsNum);

    /**
     * this method adds a task to the queue of tasks
     * @param task - a task to add
     */
    void addTask(Task *task);

    /**
     * this method terminates the thread pool
     */
    void terminate();

    /**
     * destructor
     */
    virtual ~ThreadPool();

private:
    queue<Task *> tasksQueue;
    pthread_t *threads;
    bool stopped;
    pthread_mutex_t lock;

    /**
     * this method runs the tasks in the queue
     */
    void executeTasks();

    /**
     * This method is called from the pthreadCreate in the executeTasks method
     * @param arg - Thread pool obj
     * @return this method doesn't return anything.
     */
    static void *execute(void *arg);
};


#endif //REVERSISERVER_THREADPOOL_H
