//
// Created by wyp on 2020/8/25.
//

#ifndef CHATROOM_EPOLLER_H
#define CHATROOM_EPOLLER_H

#include<sys/epoll.h>
#include <vector>
#include <memory>
#include "Dispatcher.h"

typedef std::shared_ptr<Dispatcher> DispatcherPtr;
typedef std::vector<Dispatcher*> DispatcherList;

class Epoller{
public:
    Epoller(DispatcherPtr dispatcher) :
    epfd(epoll_create1(EPOLL_CLOEXEC)), //?
    myevents(kInitEvents),
    m_dispatcher(std::move(dispatcher))
    {
        myev.events = EPOLLIN;
        myev.data.ptr = m_dispatcher.get();
        //printf("xxxxxx %d\n",m_dispatcher->getfd());
        epoll_ctl(epfd,EPOLL_CTL_ADD,m_dispatcher->getfd(),&myev);
    }

    void poll(DispatcherList* dispatchers);
    void filldispatcher(int numevents,DispatcherList* dispatchers);

    int getfd() const {return epfd;}
    epoll_event& getevent() {return myev;}

private:
    int epfd;
    struct epoll_event myev; //for epfd
    typedef std::vector<epoll_event> EventList;
    EventList myevents; //for events
    DispatcherPtr m_dispatcher;

    static const int kInitEvents = 16;

};


#endif //CHATROOM_EPOLLER_H
