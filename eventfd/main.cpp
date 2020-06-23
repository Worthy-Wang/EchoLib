#include "EventfdThread.h"
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace wd;

/*
### eventfd函数

#include <sys/eventfd.h>

int eventfd(unsigned int initval, int flags);

* initval 初始的引用计数，为64位无符号整数
* flags 标志位，一般设置为0

eventfd的作用主要在于进程，线程间通信；通过向eventfd write信号，eventfd接收信号并作出相应的回应


### eventfd 的封装
用多线程结合poll对eventfd进行监听，如果eventfd接收到信号那么就执行回调函数
*/

struct Mytask
{
    void process()
    {
        ::srand(::time(NULL));
        int number = ::rand() % 100;
        cout << ">> thread " << pthread_self()
             << "： get a number = " << number << endl;
    }
};

int main()
{
    EventfdThread th(std::bind(&Mytask::process, Mytask()));
    th.start();
    for (int i = 0; i < 3; i++)
    {
        th.wakeup();
        sleep(1);
    }
    th.stop();
    return 0;
}