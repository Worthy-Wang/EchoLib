#pragma once
#include "Thread.h"
#include "Eventfd.h"

namespace wd
{
    class EventfdThread
    {
    public:
        EventfdThread(EventfdCallBack&& cb)
        :_evfd(std::move(cb))
        ,_thread(std::bind(&Eventfd::start, &_evfd)) // 注意必须传入_evfd的地址
        {
        }

        void start()
        {
            _thread.start();
        }

        void stop()
        {
            _evfd.stop();
            _thread.join();
        }

        void wakeup()
        {
            _evfd.wakeup();
        }

    private:
        Eventfd _evfd;
        Thread _thread;
    };
} // namespace wd