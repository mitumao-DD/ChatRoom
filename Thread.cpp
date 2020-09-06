//
// Created by wyp on 2020/8/27.
//

#include "Thread.h"

struct ThreadArgs{

    pid_t tid_;
    std::string name_;
    ThreadCallback func_;

    ThreadArgs(ThreadCallback func, std::string& name, pid_t* tid):
            tid_(*tid),
            name_(name),
            func_(func)
    {

    }

    void runInThread() const
    {
        try{
            if(func_)
                func_();
        } catch (std::exception& e) {
            std::cout<<"Error happened in Thread: "<<name_<<". "<<"for "<<e.what();
            abort();
        }
    }
};

void* runThread(void* args){ //exec callback
    ThreadArgs* threadArgs = static_cast<ThreadArgs*>(args);
    threadArgs->runInThread();

    delete threadArgs;
    return nullptr;
}


Thread::Thread(ThreadCallback func, std::string &name):
tid_(0),
threadfunc_(std::move(func)),
thread_id_(0),
thread_name_(name)
{

}

Thread::~Thread() {
    if(!join_ && started_){
        pthread_detach(thread_id_);
    }
}

int Thread::join() {

    assert(started_);
    join_ = true;
    return  pthread_join(thread_id_, nullptr);
}


void Thread::start() {
    ThreadArgs* threadargs = new ThreadArgs(threadfunc_,thread_name_,&thread_id_);
    if(pthread_create(&tid_, nullptr,runThread,threadargs))
    {
        started_ = false;
        delete threadargs;
        perror("Creat new Thread Error!");
    }
    else{
        started_ = true;
    }
}

