#include "Socket.h"
#include "InetAddress.h"
#include "Acceptor.h"
#include "SocketIO.h"
#include "TcpConnection.h"
#include <iostream>
#include <string.h>
using namespace std;
using namespace wd;
/*
网路库：将TCP连接的过程进行类封装
Socket类:封装套接字fd
InetAddress类：对网络地址struct sockaddr_in 进行封装
Acceptor类：内部进行创建socket， bind， listen的操作
SocketIO类：对套接字fd进行recv, send操作
TcpConnection类：操作Acceptor接收到的描述符，保存本地与对端的网络地址

我们在执行TCP通信的过程中，只需要使用到 Acceptor类 与 TcpConnection类
socket获取，bind， listen， 以及acceptor 交给 Acceptor完成；
对accept的描述符的IO操作，保存本地以及对端的网络地址交给 TcpConnection类完成
*/

int main()
{
    Acceptor a("172.21.0.7", 2000);
    a.ready();
    TcpConnection conn(a.accept());
    conn.showAddress();
    conn.send("welcome to server");
    cout << conn.recvLine();

    return 0;
}