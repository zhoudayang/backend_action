### gcc和g++之间的误区

#### 1. gcc只能编译C代码，g++只能编译C++代码.
实际上gcc和g++上面两种代码都能够编译，实际使用的时候，注意下述两点：

1. 后缀为c的文件，gcc将其视为C程序，而g++视为C++程序。后缀为.cpp的文件，两者都将其视为C++程序。C++程序相比C程序而言，语法要求有所区别.比如下述代码，在C中可以编译通过，而在C++中会报错.
```
#include <stdio.h>
int main(int argc,char ** argv){
    if(argc==0)
        return;
    printString(argv);
    return;
}
int printString(char * string){
    sprintf(string,"this is a test string!\n");
}
```

2. 编译阶段，实际上g++会调用gcc,对于C++代码，实际上二者是完全等价的。但是因为gcc命令不能自动和C++程序使用的库进行链接，所以通常使用g++进行链接，为了同一起见，所以干脆全部使用g++了。

#### 2. gcc不会定义__cplusplus宏
实际上，这个宏只是标志着编译器把代码按照C还是C++语法进行解释。如果使用gcc且用其来编译.c文件，那么此宏就是未定义的，否则就是已经定义的。

#### 3. 编译只能使用gcc,链接只能用g++
链接使用g++实际上和```gcc -lstdc++```是一致的，gcc只是不能自动和C++标准库进行链接。

#### 4.extern "C" 与gcc/g++有关系
实际上并无关系，无论是gcc还是g++，使用extern "C"的时候，都是按照C的命名方式来为symbol命名，否则都是按照C++的方式来命名。


