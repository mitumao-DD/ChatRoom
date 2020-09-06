//
// Created by wyp on 2020/8/25.
//

#ifndef CHATROOM_DISPATCHER_H
#define CHATROOM_DISPATCHER_H

#include <functional>
#include <memory>
#include <sys/epoll.h>
typedef std::function<void()> EventCallback;

class Dispatcher{
public:
    Dispatcher(int socket_fd){
        fd = socket_fd;
    }

    void handleEvent();

    void setReadCallback(EventCallback readcallback)
    {
        ReadCallback = readcallback;
    }

    void setWriteCallback(EventCallback writecallback)
    {
        WriteCallback = writecallback;
    }

    void setErrorCallback(EventCallback errorcallback)
    {
        ErrorCallback = errorcallback;
    }

    void setCloseCallback(EventCallback closecallback)
    {
        CloseCallback = closecallback;
    }

    void setNewConnectionCallback(EventCallback newconnectioncallback){
        NewConnectionCallback = newconnectioncallback;
    }

    void enableRead(){event |= oread; updateState();}

    void enableWrite(){event |= owrite; updateState();}

    void disableRead(){event &= ~oread; updateState();}

    void disableWrite(){event &= ~owrite; updateState();}

    void setEvents(int ev) { gevent = ev; updateState();}

    int getEvents() const {return gevent; }

    void updateState();

    int getfd() const {return fd;}

private:
    int fd; //socket_fd
    int event;// event means current listening event;
    int gevent; // event  which gets recently
    EventCallback ReadCallback;
    EventCallback WriteCallback;
    EventCallback ErrorCallback;
    EventCallback CloseCallback;
    EventCallback NewConnectionCallback;

    static const int oread = EPOLLIN;
    static const int owrite = EPOLLOUT;
    static const int oerror = EPOLLERR;
};

#endif //CHATROOM_DISPATCHER_H
