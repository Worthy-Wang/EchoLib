#pragma once
#include <sys/eventfd.h>
#include <functional>
using std::function;

namespace wd
{
    using EventfdCallBack = function<void()>;
    class Eventfd
    {
    public:
        Eventfd(EventfdCallBack&& cb);
        void start();
        void stop();
        void wakeup();     //向_evfd中发送信息

    private:
        void handleRead(); //读取_evfd中发送的信息
        int createEventfd();

    private:    
        int _evfd;
        EventfdCallBack _cb;
        bool _isRunning;
    };
};  