//
// Created by wyp on 2020/8/25.
//

#include "ChatClient.h"


void Client::startRead() {
    {
        MutexGuard lock_(m_mutex);
        if (!connected_) {
            connected_ = true;
            m_socket.Connect();
        }
    }
    bool loop = true;
    while(loop)
    {
        char buf[256];
        memset(buf,0,sizeof(buf));
        int n =recv(m_socket.GetFd(),buf,sizeof(buf),0);
        if(n>0) {
            printf("%s\n", buf);
        }
        if(n==0)
        {
            send(m_socket.GetFd(),buf,sizeof(buf),0); //send something to close client
        }
    }
}

void Client::startWrite() {
    {
        MutexGuard lock_(m_mutex);
        if (!connected_) {
            connected_ = true;
            m_socket.Connect();
        }
    }
    bool loop = true;
    while(loop)
    {
        std::string line;
        while(std::getline(std::cin,line)) {
            send(m_socket.GetFd(), line.c_str(), line.size(), 0);
            usleep(1000); // turn to new read data to stdout;
        }
    }
}