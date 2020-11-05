

### 项目简介
该并发服务器框架模仿 **陈硕的Muduo库**来实现，采用**reactor + threadpool**的模式，是一个能适应**密集计算**的并发服务器框架。该项目主要分为两个部分：**reactor**+ **threadpool**。**reactor**负责将**TCP连接**进行封装，并采用**Event-Loop**模式结合**epoll**多路复用进行监听，然后注册相应的**回调函数**，并且将**IO线程**与**计算线程**分离。**threadpool**部分基于**Posix线程**实现，会依次对**互斥锁**，**条件变量**，**任务队列**，**线程**，**线程池**类进行封装，同时注册相应的**回调函数**。

<br>

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714210409248.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dvcnRoeV9XYW5n,size_16,color_FFFFFF,t_70)

<br>

### 项目详细描述

该项目主要分为两个部分，**reactor + threadpool**。

* **reactor网络库部分**

reactor部分主要将**TCP网络编程**中的socket，bind，listen，accpet与SocketIO等操作进行封装，并且使用**Event-Loop模式**结合**多路复用epoll**进行监听描述符，之后再为reactor注册相关的**回调函数**。
回调函数有三个：
1. 新连接产生时的回调函数；

2. 连接发来消息时的回调函数；

3. 连接终止时的回调函数。

在进行完以上操作之后reactor就可以监听端口，处理新连接，处理对端发来的消息，处理连接断开的情况。

注意：

1. **第二个回调函数**会将消息封装成任务添加到**线程池中的任务队列**，这也是reactor 与 threadpool之间的桥梁。

2. 计算线程不能够直接给客户端发送消息，所以需要将计算线程与IO线程进行分离（设置`eventfd`）。

<br>


* **threadpool线程池部分**

线程池的部分主要对`Posix线程`进行了封装，对多线程以下五个部分进行了封装：
1.  **mutex互斥锁的加解锁封装**，并且利用对象的生命周期实现自动加解锁，以防忘记解锁之类的；

2. **条件变量condition的封装**，实现线程间的同步。

3. **任务队列的封装**，将线程间的同步与互斥都**隐藏**在任务队列的**入队和出队**中，并且设置好任务的**安全退出机制**，确保所有的线程在退出时都能够被安全的`join`。

4. **线程类的封装**，采用基于对象线程类的设计，通过注册回调函数的方式实现线程类的功能。

5. **线程池类的封装**，将任务队列与多个线程封装在一起，许多个线程争抢并执行任务队列中的任务。


<br>


### 学习流程推荐

建议依次从`Version1.0` 开始学习，一直学习到 `Version5.0`，每一个版本都会在原版本上新增更多内容。依次递进的学习，更有利于掌握该并发服务器模型。之后再去学习`陈硕老师的muduo库`，便是更加得心应手。

<br> 

### 技术核心
1. 搭建线程池框架

技术亮点：`基于对象线程池设计`，`Posix线程同步与互斥`，`任务队列`，`自动加解锁类`，`线程安全退出机制`，`bind回调函数`，` 智能指针unique_ptr`

2. 搭建服务器框架

技术亮点：`基于对象服务器设计`，`bind回调函数`，`socket网络编程`，`TCP连接`，`IO多路复用epoll`，`eventfd(IO线程与计算线程分离)`，`客户端安全退出机制` ，`智能指针shared_ptr`

<br>


>**补充：不同 并发服务器模型的类别差异**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200719203240652.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dvcnRoeV9XYW5n,size_16,color_FFFFFF,t_70)