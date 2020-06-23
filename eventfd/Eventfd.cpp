#include "Eventfd.h"
#include <sys/poll.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

namespace wd
{
    Eventfd::Eventfd(EventfdCallBack &&cb)
        : _evfd(createEventfd()), _cb(cb), _isRunning(false)
    {
    }

    void Eventfd::start()
    {
        _isRunning = true;
        struct pollfd pfd;
        bzero(&pfd, sizeof(pfd));
        pfd.fd = _evfd;
        pfd.events = POLLIN;
        while (_isRunning)
        {
            int nready = poll(&pfd, 1, 5000);
            if (-1 == nready && errno == EINTR)
            {
                continue;
            }
            else if (-1 == nready)
            {
                perror("poll");
            }
            else if (0 == nready)
            {
                printf("timeout\n");
            }
            else
            {
                handleRead(); //先读取_evfd中的数据
                _cb();        //再调用回调函数
            }
        }
    }

    void Eventfd::stop()
    {
        if (_isRunning)
            _isRunning = false;
    }

    void Eventfd::wakeup()
    {
        uint64_t event_write = 1;
        if (write(_evfd, &event_write, sizeof(uint64_t)) != sizeof(uint64_t))
        {
            perror("write evfd");
        }
    }

    void Eventfd::handleRead()
    {
        uint64_t event_read;
        if (read(_evfd, &event_read, sizeof(uint64_t)) != sizeof(uint64_t))
        {
            perror("read evfd");
        }
    }

    int Eventfd::createEventfd()
    {
        int evfd = eventfd(0, 0);
        if (-1 == evfd)
        {
            perror("eventfd");
        }
        return evfd;
    }
} // namespace wd