//
// Created by wyp on 2020/8/26.
//

#ifndef CHATROOM_TCPCONNECTION_H
#define CHATROOM_TCPCONNECTION_H

#include "Dispatcher.h"
#include <string>
#include "Sockets.h"
class Buffer;

typedef std::shared_ptr<Dispatcher> DispatcherPtr;
typedef std::function<void(std::string&)> ParseCallback;

class Tcpconnection {
public:
    Tcpconnection(DispatcherPtr dispatcher):
    dispatcher_(dispatcher)
    {
        dispatcher_->setReadCallback(std::bind(&Tcpconnection::handleRead,this));
        dispatcher_->setWriteCallback(std::bind(&Tcpconnection::handleWrite,this));
        dispatcher_->setErrorCallback(std::bind(&Tcpconnection::handleError,this));
        dispatcher_->setCloseCallback(std::bind(&Tcpconnection::handleClose,this));
    }

    std::shared_ptr<Dispatcher> GetDispatcher(){
        return dispatcher_;
    }

    void handleRead();

    void handleWrite();

    void handleError();

    void handleClose();

    void setParseCallback(ParseCallback parse){parse_ = parse;}

    void Parse(const char* message);

private:
    DispatcherPtr dispatcher_;
    ParseCallback parse_;
    //Buffer readbuff;
    //Buffer writebuff;
};


#endif //CHATROOM_TCPCONNECTION_H
