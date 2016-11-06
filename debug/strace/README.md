### 使用strace 来调试程序
#####1.执行方式
```strace ./executable_name ```

使用strace可以用于跟踪系统调用，还有信号的传递。

#####2.参数说明:
1. -c 统计系统调用的次数
2. -T 统计各个调用消耗的时间
3. -o 将strace 程序记录的结果输出到指定文件之中
4. -p 跟踪指定pid的程序

#####3.使用示例
在strace路径下利用cmake生成可执行文件example，然后使用strace进行跟踪，即```strace ./example```

输出如下所示:
    ```
    open("input.txt", O_RDONLY)             = -1 ENOENT (No such file or directory)
    ```
可见错误的原因是无法打开input.txt文件，因为当前目录下没有这个文件。

> 在debug百思不得其解的时候，往往 **strace** 会令你的思路焕然一新.
