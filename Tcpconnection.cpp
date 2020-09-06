//
// Created by wyp on 2020/8/26.
//

#include "Tcpconnection.h"
#include <unistd.h>
#include <memory.h>
void Tcpconnection::handleRead() {
    int n;
    char buf[256];
    memset(buf,0,sizeof(buf));
    if((n=recv(dispatcher_->getfd(),buf,sizeof(buf),0)) <= 0)
    {
        if(n==0)
            //shutdown(dispatcher_->getfd(),SHUT_RD);
            close(dispatcher_->getfd());
        else{
            perror("read error");
        }
    }
    std::string sbuf(buf);
    printf("fd:%d, nbytes: %d, rec:%s\n",dispatcher_->getfd(),n,buf);
    parse_(sbuf);

}

void Tcpconnection::handleWrite() {

}

void Tcpconnection::handleClose() {

}

void Tcpconnection::handleError() {

}

void Tcpconnection::Parse(const char* message) {

}