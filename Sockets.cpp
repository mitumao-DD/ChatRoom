//
// Created by wyp on 2020/8/25.
//

#include "Sockets.h"

//void Sockets::CreateSocket() {
//    fd = socket(family,type,0);
//    if(fd<0)
//        perror("CreatSocket Error");
//}

void Sockets::SetSocket() {
    int opt = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}

void Sockets::Bind() {
    int n;
    n=bind(fd,(struct sockaddr*)&myaddr,sizeof(myaddr));
    if(n<0)
    {
        perror("Bind Error");
    }
}

void Sockets::Listen() {
    int n;
    n = listen(fd,backlog);
    if(n<0)
    {
        perror("Listen Error");
    }
}

int Sockets::Accept() {
    int n;
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    if((n=accept4(fd,(struct sockaddr*)&cliaddr,&len,SOCK_NONBLOCK | SOCK_CLOEXEC))<0)
    {
        perror("Accept Error");
    }
    return n;
}

void Sockets::init() {
    //CreateSocket();
    SetSocket();
    Bind();
    Listen();
}

void Sockets::Connect() {
    int n;
    n = connect(fd,(struct sockaddr*)&myaddr,sizeof(myaddr));
    if(n<0)
        perror("Connect Error");
}