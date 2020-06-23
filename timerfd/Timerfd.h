#pragma once
#include <sys/timerfd.h>
#include <functional>
using std::function;

namespace wd
{
    using TimerfdCallBack = function<void()>;
    class Timerfd
    {
    public:
        Timerfd(int initialTime, int intervalTime, TimerfdCallBack &&cb);
        void start();
        void stop();

    private:
        void setTimer(int initialTime, int intervalTime);
        void handleRead(); //读取_timerfd中发送的信息
        int createTimerfd();

    private:
        int _initialTime;
        int _intervalTime;
        int _timerfd;
        TimerfdCallBack _cb;
        bool _isRunning;
    };
}; // namespace wd