### 链接详解

#### 静态链接库

1. 在static文件夹中，有add.cpp add.h以及sub.cpp sub.h定义了函数add和sub。首先使用g++编译生成.o文件,执行
```
　　g++ -c add.cpp
　　g++ -c sub.cpp
```
上述命令会在static文件夹下生成add.o和sub.o文件.
2. 接下来，执行下述命令，链接生成静态链接库
```ar cr lib/libmath.a add.o sub.o```
执行完毕之后，会在static/lib文件夹下生成libmath.a静态链接库文件.
3.接下来在main.cpp中引用上面生成的库文件，如下所示:
    ```
    #include "add.h"
    #include "sub.h"
    #include <iostream>
    using namespace std;
    int main(){
        cout<<add(1,2)<<endl;
        cout<<sub(3,2)<<endl;
    }

    ```

    执行命令```g++ -o main main.cpp -L lib -lmath```会生成main可执行文件.
注意-I 后面给出头文件搜索路径，-L后面给出库文件搜索路径，-l后面给出库文件名称.

>注意:若ar命令不可用，可能是因为zsh中的debian插件中声明的alias冲突，详细可执行```type ar``` 查明

#### 动态链接库
1.执行下述命令生成动态链接库
```g++ -fPIC -shared -o lib/libmath.so add.cpp sub.cpp```

2.执行下述命令生成可执行文件
```g++ -o main main.cpp -L lib -lmath```

> 此时执行./main, 会提示无法打开libmath.so动态链接库，只需要将libmath.so复制到　/usr/lib/中，这样程序就能够找到这个动态链接库。
> LD_LIBRARY_PATH定义了程序执行时动态链接库的搜索路径，必要的时候可以自己定义这个环境变量来指定动态链接库的搜索路径.

#### 链接库的特点

1. 动态链接库有利于进程间资源共享
2. 升级程序变得更简单，静态库升级需要重新编译，动态链接库直接替换库文件即可.
3. 有利于模块的分离.
4. 实际运行的时候，动态链接库的效率要低于静态链接库，动态链接库需要在运行的时候进行链接。
