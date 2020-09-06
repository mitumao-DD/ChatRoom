//
// Created by wyp on 2020/8/25.
//

#ifndef CHATROOM_CHATCLIENT_H
#define CHATROOM_CHATCLIENT_H

#include "Sockets.h"
#include  <iostream>
#include <memory.h>
#include "Thread.h"
#include "Mutex.h"

class Client;

typedef std::function<void(Client *)> ClientCallback;

class Client{
public:
    Client(const char* IP,const uint16_t port):
    m_socket(IP,port)
    {

    }

    void startRead();

    void startWrite();

    void setConnectionCallback(ClientCallback func){
        m_func = func;
    }

private:
    Sockets m_socket;
    ClientCallback m_func;
    bool connected_ = false;
    Mutex m_mutex;
};

#endif //CHATROOM_CHATCLIENT_H
