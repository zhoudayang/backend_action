## 使用gdb进行程序调试
### 1.启动
1. gdb program 使用gdb执行可执行文件program。
2. gdb program core 使用gdb同时调试运行一个运行程序和core文件，core是程序非法执行core down之后产生的文件。
3. gdb program 1234 如果程序是一个服务程序，那么可以指定这个服务程序运行时的进程ID,gdb会自动进行attach操作，并且调试这个程序。并且program应该在PATH环境变量中搜索得到。

###2.gdb命令
1. ```l <i>``` 显示第i行开始的代码,不指定i表示从开头开始显示代码
2. ```b <i>``` 在第i行设置断电
3. ```b <func>``` 在函数func处设置断点
4. ```info break``` 输出断点信息
5. ```d <i> ``` 删除编号i对应的断点
4. ```p <i>``` 打印出变量i的值
5. ```bt``` 查看函数的堆栈
6. ```r``` 开始运行程序
7. ```next``` 运行下一行代码
8. ```s``` step into,跳入执行
9. ```ptype <i>``` 输出变量i的类型，可以输出结构体的定义
9. ```finish```　退出函数
10. ```q``` 退出gdb

###3.使用gdb分析coredump文件
####1.coredump文件的存储路径
执行命令```cat /proc/sys/kernel/core_pattern```,如果返回的结果是core,表明core文件存储在可执行文件目录下，否则路径为返回结果所指定的路径。

####2.产生coredump文件的条件

##### 1. 系统对coredump最大大小的限制
执行命令```ulimit -c```会输出当前系统所能允许的最大coredump文件大小。通过执行命令```ulimit -c [size]```会为系统当前会话设置最大的coredump文件大小，这里的单位为block即512Bytes,如果想要系统对coredump文件大小无限制，可以执行命令```ulimit -c unlimited``` 。

##### 2.执行应用程序的用户是否对写入core的目录有足够的权限，并且此目录有足够的空间

##### 3.产生coredump文件的原因

1. 内存访问越界
2. 多线程程序使用了线程不安全的函数
3. 多线程读写的数据未保护
4. 非法指针，包括使用空指针或者随意使用指针转换
5. 堆栈溢出

##### 4.例子
core.cc
```
#include <stdio.h>

int main(){
    int b = 1;
    int * a;
    *a = b;
    return 0;
}
```

