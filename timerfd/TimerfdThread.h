#pragma once
#include "Thread.h"
#include "Timerfd.h"

namespace wd
{
    class TimerfdThread
    {
    public:
        TimerfdThread(int initialTime, int intervalTime, TimerfdCallBack&& cb)
        :_Timerfd(initialTime, intervalTime, std::move(cb))
        ,_thread(std::bind(&Timerfd::start, &_Timerfd)) // 
        {
        }

        void start()
        {
            _thread.start();
        }

        void stop()
        {
            _Timerfd.stop();
            _thread.join();
        }


    private:
        Timerfd _Timerfd;
        Thread _thread;
    };
} // namespace wd