//
// Created by wyp on 2020/8/25.
//

#include "../ChatServer.h"

int main(){
    ChatServer test("127.0.0.1",9999);
    test.start();
}