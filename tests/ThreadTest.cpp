//
// Created by wyp on 2020/8/28.
//

#include "../Thread.h"
#include <iostream>
#include "../ChatClient.h"


int main(int argc, char* argv[]){
    if(argc==4) {
        std::string name = argv[3];
        Client test(argv[1], atoi(argv[2]));
        Thread mythread(std::bind(&Client::startRead, &test), name);
        //Thread mythread(print,name);
        mythread.start();
        test.startWrite();
    } else
    {
        printf("Usage %s [ip] [port] [clietname]\n ",argv[0]);
    }
};