#ifndef REVERSISERVER_TASK_H
#define REVERSISERVER_TASK_H


class Task {
public:
    /**
     * constructor
     * @param func - void * as the function to execute
     * @param arg  - the args for the func
     */
    Task(void *(*func)(void *arg), void *arg) :
            func(func), arg(arg) {}

    /**
     * this method executes the func with the args
     */
    void execute() {
        func(arg);
    }

    /**
     * destructor
     */
    virtual ~Task() {}

private:
    void *(*func)(void *arg);

    void *arg;
};


#endif //REVERSISERVER_TASK_H
