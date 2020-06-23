#include <unistd.h>
#include <iostream>
#include <sys/eventfd.h>
using namespace std;

/*

### 前言：为什么需要eventfd? 
在我们之前的学习中，进行进程/线程间通信的方法有两个：
1. 条件变量
需要使用锁，线程的互斥，唤醒等机制，使用此方法来进行通信实在是很麻烦；

2. 管道
管道的特点在于传送信息，并且会产生两个文件描述符，也是同样的麻烦。

于是乎，eventfd便产生了，通过同一个文件描述符，能够快速的进行进程/线程间的通信。




### eventfd 进程/线程间通信

#include <sys/eventfd.h>

* int eventfd(unsigned int initval, int flags);

* flags：
如果是2.6.26或之后版本的内核，flags 必须设置为0。
EFD_NONBLOCK      类似于使用O_NONBLOCK标志设置文件描述符。
EFD_CLOEXEC  类似open以O_CLOEXEC标志打开， O_CLOEXEC 应该表示执行exec()时，之前通过open()打开的文件描述符会自动关闭.

* initval：
初始化计数器值，该值保存在内核, 如果设置为0，则代表还未进行写入

*/

int main()
{
    int evfd = eventfd(0, 0);
    uint64_t event_read, event_write;
    if (fork())
    {
        sleep(1);
        event_write = 100;
        write(evfd, &event_write, 8);
        cout << "father write, event_write = " << event_write << endl;
    }
    else
    {
        read(evfd, &event_read, 8);
        cout << "child read,  event_read = " << event_read << endl;
        
    }
    return 0;
}