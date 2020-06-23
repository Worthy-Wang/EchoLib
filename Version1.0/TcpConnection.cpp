#include "TcpConnection.h"
#include <string.h>
#include <string>
using std::to_string;

namespace wd
{
    TcpConnection::TcpConnection(int fd)
        : _socket(fd), _sio(fd), _localAddress(getLocal(fd)), _peerAddress(getPeer(fd)), _isShutdownWrite(false)
    {
    }

    TcpConnection::~TcpConnection()
    {
        shutdownWrite();
    }

    string TcpConnection::recv()
    {
        char buf[65535];
        _sio.readn(buf, sizeof(buf));
        return string(buf);
    }

    string TcpConnection::recvLine()
    {
        char buf[65535];
        _sio.readline(buf, sizeof(buf));
        return string(buf);
    }

    void TcpConnection::send(const string& s)
    {
        _sio.writen(s.c_str(), strlen(s.c_str()));
    }

    string TcpConnection::showAddress() const
    {
        string s;
        s = _localAddress.getIp() + ":" + to_string(_localAddress.getPort()) + " >> " + _peerAddress.getIp() + ":" + to_string(_peerAddress.getPort());
        return s;
    }

    void TcpConnection::shutdownWrite()
    {
        if (!_isShutdownWrite)
        {
            _socket.shutdown_write();
            _isShutdownWrite = true;
        }
    }


    InetAddress TcpConnection::getLocal(int fd)
    {
        struct sockaddr_in local;
        bzero(&local, sizeof(local));
        socklen_t len = sizeof(sockaddr);
        int ret = getsockname(fd, (sockaddr *)&local, &len);
        if (ret)
        {
            perror("getsockname");
        }
        return InetAddress(local);
    }

    InetAddress TcpConnection::getPeer(int fd)
    {
        struct sockaddr_in peer;
        bzero(&peer, sizeof(peer));
        socklen_t len = sizeof(sockaddr);
        int ret = getpeername(fd, (sockaddr *)&peer, &len);
        if (ret)
        {
            perror("getpeername");
        }
        return InetAddress(peer);
    }
} // namespace wd