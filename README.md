
### 网络库框架简介

dd
该网络库框架模仿 `陈硕的Muduo库` 来实现，采用`Reactor + threadpool` 的模式：
主线程IO，工作线程计算，是能适应密集计算的`服务器框架`。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714210409248.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dvcnRoeV9XYW5n,size_16,color_FFFFFF,t_70)
`类别差异`：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200719203240652.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1dvcnRoeV9XYW5n,size_16,color_FFFFFF,t_70)

### 学习流程推荐
建议依次从`Version1.0` 开始学习，一直学习到 `Version5.0`，每一个版本都会在原版本上新增更多内容。
<br> 

### 技术核心
1. 搭建线程池框架
技术亮点：`基于对象线程池设计`，`Posix线程同步与互斥`，`任务队列`，`自动加解锁类`，`线程安全退出机制`，`bind回调函数`，` 智能指针unique_ptr`
2. 搭建服务器框架
技术亮点：`基于对象服务器设计`，`bind回调函数`，`socket网络编程`，`TCP连接`，`IO多路复用epoll`，`eventfd(IO线程与计算线程分离)`，`客户端安全退出机制` ，`智能指针shared_ptr`
