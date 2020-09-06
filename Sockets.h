//
// Created by wyp on 2020/8/25.
//

#ifndef CHATROOM_SOCKETS_H
#define CHATROOM_SOCKETS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class Sockets{
public:
    Sockets(const char* IPdress,uint16_t port){
        myaddr.sin_family = family;
        myaddr.sin_addr.s_addr = inet_addr(IPdress);
        myaddr.sin_port = htons(port);
        fd = socket(family,type,0);
        if(fd<0)
            perror("Socket Init Error");
    }

    ~Sockets(){
        close(fd);
    }

    int GetFd(){return fd;}

    void ChangeFamily(int NewFamily) {
        family = NewFamily;
    }

    void ChangeType(int NewType){
        type = NewType;
    }

    void init();

    int Accept();

    void Connect();

private:
    int fd; //file desc
    int family = AF_INET;
    int type = SOCK_STREAM;// xieyi
    int backlog = 128; // for listening
    struct sockaddr_in  myaddr;

    //void CreateSocket();

    void SetSocket();

    void Bind();

    void Listen();

};

#endif //CHATROOM_SOCKETS_H
