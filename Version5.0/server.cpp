#include "./net/TcpServer.h"
#include "./threadpool/Threadpool.h"
#include <iostream>
#include <string.h>
#include <string>
using namespace std;
using namespace wd;
/*
网路库Version4.0: 
新增基于对象的线程池，利用子线程帮助服务器处理信息
对于一般的命令，主线程自己就可以解决；对于由复杂的逻辑操作的命令，交给子线程完成（实际过程就是像任务队列插入新的任务）

*/
Threadpool *pthreadpool = NULL; //定义全局变量：线程池

//子线程（计算线程）需要从任务队列中获取并处理的任务
class MyTask
{
public:
    MyTask(const string& msg, const TcpConnectionPtr& ptr)
    :_msg(msg)
    ,_ptr(ptr)
    {
    }

    void process()
    {
        // _ptr->send(_msg); 
        /*
        由子线程(计算线程)进行IO操作是不合理的，应该将需要发送的语句发送到EventLoop中，由主线程(IO线程)来完成
        */
        _ptr->sendInEventLoop(_msg);
    }
private:
    string _msg;
    TcpConnectionPtr _ptr;
};


void ConnectionCallBack(const TcpConnectionPtr& ptr)
{
    cout << ">>client has connected " << ptr->Address() << endl;
    ptr->send("welcome to server");
}

void MessageCallBack(const TcpConnectionPtr& ptr)
{
    cout << ">>from client:" << ptr->Address() << endl;
    string s = ptr->recv();
    cout << s;
    //send消息的工作交给子线程
    MyTask task(s, ptr);
    pthreadpool->addTask(std::bind(&MyTask::process, task));
    // ptr->send(s);
}

void CloseCallBack(const TcpConnectionPtr& ptr)
{
    cout << "client has broken up " << ptr->Address() << endl;
}


int main()
{
    Threadpool threadpool(4, 10);//4个线程，任务队列的容量为4
    pthreadpool = &threadpool;
    pthreadpool->start();

    TcpServer server("172.21.0.7", 2000);
    server.setConnectionCallBack(ConnectionCallBack);
    server.setMessageCallBack(MessageCallBack);
    server.setCloseCallBack(CloseCallBack);
    server.start();
    return 0;
}