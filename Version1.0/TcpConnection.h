#pragma once
#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h" 
#include "Noncopyable.h"
#include <string>
using std::string;

namespace wd
{
    class TcpConnection
    :Noncopyable
    {
    public:
        TcpConnection(int fd);
        ~TcpConnection();
        string recv();
        string recvLine();
        void send(const string& s);
        void shutdownWrite();
        string showAddress() const;
    
    private:
        InetAddress getLocal(int);
        InetAddress getPeer(int);

    private:
        Socket _socket;
        SocketIO _sio;
        InetAddress _localAddress;
        InetAddress _peerAddress;
        bool _isShutdownWrite;
    };
}