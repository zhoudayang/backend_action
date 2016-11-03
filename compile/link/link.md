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
