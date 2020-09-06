//
// Created by wyp on 2020/8/25.
//

#include "Epoller.h"

void Epoller::poll(DispatcherList* dispatchers) {
    int n = epoll_wait(epfd,&*myevents.begin(),static_cast<int>(myevents.size()),1*1000);
    //printf("%d\n",n);
    if(n<0)
        perror("epoll error");
    else{
        filldispatcher(n,dispatchers);
        if(uint (n)==myevents.size())
            myevents.resize(myevents.size()*2);
    }
}

void Epoller::filldispatcher(int numevents, DispatcherList* dispatchers) {
    for(int i=0;i<numevents;i++)
    {
        Dispatcher* dispatcher = static_cast<Dispatcher*>(myevents[i].data.ptr);
        dispatcher->setEvents(myevents[i].events);
        //printf("xxxx %d\n",dispatcher->getfd());
        dispatchers->push_back(dispatcher);
    }
}