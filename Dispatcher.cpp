//
// Created by wyp on 2020/8/25.
//

#include "Dispatcher.h"

void Dispatcher::handleEvent() {
    if(gevent & oread)
    {
       if(ReadCallback)
           ReadCallback();
    }

    if(gevent & owrite)
    {
        if(WriteCallback)
           WriteCallback();
    }

    if(gevent & oerror)
    {
        if(ErrorCallback)
            ErrorCallback();
    }
}

void Dispatcher::updateState() {

}