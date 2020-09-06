//
// Created by wyp on 2020/8/27.
//

#ifndef CHATROOM_THREAD_H
#define CHATROOM_THREAD_H

#include <pthread.h>
#include <functional>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <memory>
#include <sys/syscall.h>

typedef std::function<void()> ThreadCallback;

class Thread {
public:

    Thread(ThreadCallback func,std::string& name);

    ~Thread();

    void start();

    int join();

    pid_t getid() const { return thread_id_;}

    std::string getNmae() const{return thread_name_;};

    pid_t getthread_id()
    {
        thread_id_ = static_cast<pid_t>(::syscall(SYS_gettid));
        return thread_id_;
    }

    void setCallback(ThreadCallback func) {threadfunc_ = func;}
    void setName(std::string& name) {thread_name_ = name;}

private:
    pthread_t tid_;


    ThreadCallback threadfunc_;

    bool join_;
    bool started_;

    pid_t thread_id_;
    std::string thread_name_;
};


#endif //CHATROOM_THREAD_H
