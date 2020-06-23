#include "Timerfd.h"
#include <sys/poll.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

namespace wd
{
    Timerfd::Timerfd(int initialTime, int intervalTime, TimerfdCallBack &&cb)
        :_initialTime(initialTime), _intervalTime(intervalTime), _timerfd(createTimerfd()), _cb(cb), _isRunning(false)
    {
    }

    void Timerfd::start()
    {
        _isRunning = true;
        setTimer(_initialTime, _intervalTime);
        
        struct pollfd pfd;
        bzero(&pfd, sizeof(pfd));
        pfd.fd = _timerfd;
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

    void Timerfd::stop()
    {
        if (_isRunning)
            _isRunning = false;
    }

    void Timerfd::setTimer(int initialTime, int intervalTime)
    {
        struct itimerspec itimer;
        itimer.it_value.tv_sec = initialTime;
        itimer.it_value.tv_nsec = 0;
        itimer.it_interval.tv_sec = intervalTime;
        itimer.it_interval.tv_nsec = 0;
        int ret = timerfd_settime(_timerfd, 0, &itimer, NULL);
        if (-1 == ret)
        {
            perror("timerfd_settime");
        }
    }


    void Timerfd::handleRead()
    {
        uint64_t timerfd_read;
        if (read(_timerfd, &timerfd_read, sizeof(uint64_t)) != sizeof(uint64_t))
        {
            perror("timerfd read");
        }
    }

    int Timerfd::createTimerfd()
    {
        int timerfd = timerfd_create(CLOCK_REALTIME, 0);
        if (-1 == timerfd)
        {
            perror("timerfd_create");
        }
        return timerfd;
    }
} // namespace wd