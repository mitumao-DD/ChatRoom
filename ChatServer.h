//
// Created by wyp on 2020/8/25.
//

#ifndef CHATROOM_CHATSERVER_H
#define CHATROOM_CHATSERVER_H

#include "Sockets.h"
#include "Epoller.h"
#include "Dispatcher.h"
#include "Tcpconnection.h"
#include <map>

typedef std::shared_ptr<Sockets> SocketPtr;
typedef std::shared_ptr<Epoller> EpollerPtr;
typedef std:: shared_ptr<Tcpconnection> TcpconnectionPtr;


class ChatServer{
public:
    ChatServer(const char* IP,uint16_t port) :
    m_socket(IP,port),
    m_epoller(std::make_shared<Dispatcher>(m_socket.GetFd()))
    {

    }

    void start();

    void PrintNewConnection();

    void PrintMessage();

    void PrintRemoveConnection();

    void Parse(std::string& buf);

    void SendToAll(std::string& buf,std::string& sender);

    void SendToTarget(std::string& buf,std::string& sender, std::vector<std::string>& targets);

    void LookUpClients(std::string& sender);

private:
    Sockets m_socket;
    Epoller m_epoller;
    DispatcherList m_dispatchers;
    typedef std::map<int,TcpconnectionPtr> TcpconnecionPtrMap;
    TcpconnecionPtrMap m_connections;
    typedef std::map<std::string,int> ClientMap;
    ClientMap m_clients;
};

#endif //CHATROOM_CHATSERVER_H
