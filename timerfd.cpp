#include <sys/timerfd.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
using namespace std;
/*

前言：为什么需要定时器timerfd?
在多线程中，设置一个超时时间，当时间超时时，就会触发事件，这样的操作如果是我们自己做，那么需要使用到
<time.h> 和 <sys/time.h> 中的API进行不断地更新时间，再判断有没有超时，如果超时再找到对应的触发事件。
这样的操作很复杂，而且在多线程中容易出错，所以便有了timerfd

timerfd 定时器
将定时器创建出一个文件描述符，如果超时，那么描述符可读，经常与 select/poll/epoll搭配使用。


#include <sys/timerfd.h>

* int timerfd_create(int clockid, int flags);

* clockid:可设置为
CLOCK_REALTIME：相对时间，从1970.1.1到目前的时间。更改系统时间 会更改获取的值，它以系统时间为坐标。
CLOCK_MONOTONIC：绝对时间，获取的时间为系统重启到现在的时间，更改系统时间对齐没有影响。

* flags: 可设置为
TFD_NONBLOCK（非阻塞），
TFD_CLOEXEC（同O_CLOEXEC）
linux内核2.6.26版本以上都指定为0


* int timerfd_settime(int fd, int flags,
    const struct itimerspec *new_value,
    struct itimerspec *old_value);

* fd: 
timerfd对应的文件描述符

* flags:
0表示是相对定时器TFD_TIMER_ABSTIME表示是绝对定时器

* new_value:
设置超时时间，如果为0则表示停止定时器。

* old_value:
一般设为NULL, 不为NULL,则返回定时器这次设置之前的超时时间


int timerfd_gettime(int fd, struct itimerspec *curr_value);
一般不使用

*/

void setTimer(int timerfd, int initialTime, int intervalTime)
{
    struct itimerspec itimer;
    itimer.it_value.tv_sec = initialTime;
    itimer.it_value.tv_nsec = 0;
    itimer.it_interval.tv_sec = intervalTime;
    itimer.it_interval.tv_nsec = 0;
    int ret = timerfd_settime(timerfd, 0, &itimer, NULL);
    if (-1 == ret)
    {
        perror("timerfd_settime");
    }
}

int main()
{

    int timerfd = timerfd_create(CLOCK_REALTIME, 0);
    if (-1 == timerfd)
    {
        perror("timerfd_create");
    }
    setTimer(timerfd, 1, 2); //initialTime不能设置为0！

    timeval beg, now;
    gettimeofday(&beg, nullptr);
    do
    {
        uint64_t uread;
        if (read(timerfd, &uread, sizeof(uint64_t)) != sizeof(uint64_t))
        {
            perror("timerfd read");
        }
        cout << "read from timerfd:" << uread << endl;
        gettimeofday(&now, nullptr);
        cout << "time interval:" << now.tv_sec - beg.tv_sec << endl;
    } while ((now.tv_sec - beg.tv_sec) < 20);

    return 0;
}