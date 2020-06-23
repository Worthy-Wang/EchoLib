#pragma once
#include "Acceptor.h"
#include "EventLoop.h"
#include "Noncopyable.h"
#include <string>
using std::string;

namespace wd
{
    class TcpServer
        : Noncopyable
    {
    public:
        TcpServer(const string &Ip, unsigned short port);
        void start();
        void setConnectionCallBack(const TcpConnectionCallBack &);
        void setMessageCallBack(const TcpConnectionCallBack &);
        void setCloseCallBack(const TcpConnectionCallBack &);

    private:
        Acceptor _acceptor;
        EventLoop _eventLoop;
    };
} // namespace wd