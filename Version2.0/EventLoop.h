#pragma once
#include "Noncopyable.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <iostream>
using std::cout;
using std::endl;
using std::map;
using std::vector;

namespace wd
{
    class EventLoop
        : Noncopyable
    {
    public:
        EventLoop(Acceptor &);
        void Loop();
        void UnLoop();

        void setConnectionCallBack(const TcpConnectionCallBack &);
        void setMessageCallBack(const TcpConnectionCallBack &);
        void setCloseCallBack(const TcpConnectionCallBack &);

    private:
        void epollWait(); //epoll_wait封装
        void addNewConnection(int fd); //监听到socket描述符，添加新的客户端连接
        void handleMessage(int fd); // 监听到客户端描述符，处理信息 
        int getEpollFd();      //创建epfd
        void epollDel(int fd); //epfd中删除fd的监控
        void epollAdd(int fd); //epfd中增加fd的监控
        bool isClientQuit(int fd); //判断客户端是否退出

    private:
        int _epfd;                          //epoll 的描述符
        Acceptor &_acceptor;                //用于得到服务器的socket与accept的newfd
        vector<epoll_event> _evs;           //存放就绪的描述符
        map<int, TcpConnectionPtr> _tcpMap; //<描述符，Tcp通信类>
        bool _isLoop;                       //epoll是否正在监测中

        TcpConnectionCallBack _connectionCB;
        TcpConnectionCallBack _messageCB;
        TcpConnectionCallBack _closeCB;
    };
} // namespace wd