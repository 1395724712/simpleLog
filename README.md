# simpleLog
keywords:日志，简单，多线程安全，暂时不要求高性能，CMakeLists.txt生成动态库

## 底层实现
这是一个简单的、输出到终端的日志，不写文件，所以底层用`istream`实现就好。

## 多线程安全
使用单例模式确保全局唯一的日志对象。在此基础上使用锁来保护临界区。

## 日志格式：
时间+线程号+函数名+用户所要输出的内容+换行
* 时间：
> 可以是clock()返回的时间，只要能反应日志的先后顺序即可
* 线程号：
> ```
> #include<sys/types.h>
> pid_t gettid()
>````
* 函数名称：
>`__FUNCINFO__`

## todo:
- [ ] 动态库的生成与使用