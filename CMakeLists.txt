cmake_minimum_required(VERSION 2.8)
project(ChatRoom)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -o3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -pthread")

#include_directories(.)
#include_directories(../yaml-cpp)

set(LIB_SRC  ChatServer.cpp Dispatcher.cpp Epoller.cpp
        Sockets.cpp Tcpconnection.cpp ChatClient.cpp
        Thread.cpp Mutex.h)

add_library(ChatRoom SHARED ${LIB_SRC})

add_executable(ServeTest tests/SocketsTest.cpp)
add_dependencies(ServeTest ChatRoom)
target_link_libraries(ServeTest ChatRoom)

add_executable(ClientTest tests/ClientTest.cpp)
add_dependencies(ClientTest ChatRoom)
target_link_libraries(ClientTest ChatRoom)

add_executable(ThreadTest tests/ThreadTest.cpp)
add_dependencies(ThreadTest ChatRoom)
target_link_libraries(ThreadTest ChatRoom)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)