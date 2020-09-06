//
// Created by wyp on 2020/8/25.
//

#include "ChatServer.h"

void ChatServer::start() {
    m_socket.init();
    bool loop = true;
    while (loop) {
        m_dispatchers.clear();
        m_epoller.poll( &m_dispatchers);
        for (auto &dispatcher : m_dispatchers) {
            if (dispatcher->getfd() == m_socket.GetFd()) { //add new connection

                int cfd = m_socket.Accept();
                epoll_event tmp = m_epoller.getevent();
                //fix cfd!!!
                DispatcherPtr newdispatcher = std::make_shared<Dispatcher>(cfd);
                tmp.data.ptr = newdispatcher.get();
                tmp.events = EPOLLIN;
                epoll_ctl(m_epoller.getfd(),EPOLL_CTL_ADD,cfd,&tmp);

                TcpconnectionPtr newConnection = std::make_shared<Tcpconnection>(newdispatcher);
                newConnection->setParseCallback(std::bind(&ChatServer::Parse,this,std::placeholders::_1));
                m_connections[cfd] = newConnection;
                PrintNewConnection();//for debug
            } else {
                TcpconnectionPtr it = m_connections[dispatcher->getfd()]; // handle event
                if(it!= nullptr)
                {
                    it->GetDispatcher()->handleEvent();
                }
            }
        }
    }
    loop = false;
}

void ChatServer::PrintNewConnection() {
    printf("new connection coming\n");
}

void ChatServer::PrintMessage() {

}

void ChatServer::PrintRemoveConnection() {

}

void ChatServer::Parse(std::string& buf) {
    for(auto& it : m_connections)
    {
        printf("in Parse %s\n",buf.data());
        send(it.first,buf.c_str(),buf.size(),0);
    }
}

void ChatServer::SendToAll(std::string &buf, std::string &sender) {
    for(auto& it : m_clients)
    {
        if(it.first!=sender){
            send(it.second,buf.c_str(),buf.size(),0);
        }
    }
}

void ChatServer::SendToTarget(std::string &buf, std::string& sender, std::vector<std::string> &targets) {
    for(auto& it : targets)
    {
        int cfd = m_clients[it];
        send(cfd,buf.c_str(),buf.size(),0);
    }
}

void ChatServer::LookUpClients(std::string& sender) {
    std::string buf;
    for(auto& it : m_clients)
    {
        buf+=it.first+' ';
    }
    send(m_clients[sender],buf.c_str(),buf.size(),0);
}