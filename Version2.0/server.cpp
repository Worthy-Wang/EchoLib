#include "Socket.h"
#include "InetAddress.h"
#include "Acceptor.h"
#include "SocketIO.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include <iostream>
#include <string.h>
#include <string>
using namespace std;
using namespace wd;
/*
网路库Version2.0: 

TcpConnection类：通过回调函数,设置三类函数,注意回调函数的参数必须是TcpConnection类的指针，这样才能进行操作
connectionCallBack: 客户端连接上socket时调用的函数
messageCallBack: 通信函数
closeCallBack: 客户端断开时调用的函数

EventLoop类：设置epoll机制
注意也需要存放回调函数，用于设置每一个TcpConnection类的回调函数
关于EventLoop类中的回调函数，需要先设置好，然后再在每一个监听的TcpConnection中设置好EventLoop中公用的回调函数

*/

//设计TcpConnection中的回调函数
void ConnectionCallBack(const TcpConnectionPtr& ptr)
{
    cout << ">>client has connected " << ptr->Address() << endl;
    ptr->send("welcome to server");
}

void MessageCallBack(const TcpConnectionPtr& ptr)
{
    cout << ">>from client:" << ptr->Address() << endl;
    string s = ptr->recv();
    cout << s;
    ptr->send(s);
}

void CloseCallBack(const TcpConnectionPtr& ptr)
{
    cout << "client has broken up " << ptr->Address() << endl;
}


int main()
{
    Acceptor acceptor("172.21.0.7", 2000);
    acceptor.ready();
    EventLoop eventLoop(acceptor);
    eventLoop.setConnectionCallBack(ConnectionCallBack);
    eventLoop.setMessageCallBack(MessageCallBack);
    eventLoop.setCloseCallBack(CloseCallBack);
    eventLoop.Loop();    
    return 0;
}