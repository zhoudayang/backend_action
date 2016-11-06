## 使用valgrind进行内存检查
> 在进行下述操作前请先使用cmake构建可执行文件.

### 例1:访问非法内存
illegal_memory.cc
```
#include <iostream>
#include <cstdlib>

using namespace std;

void func(){
        int * x = (int *) malloc(10 * sizeof (int));
        x[10] = 0;

}


int main(){
        
        func();
        cout<<"done!"<<endl;
        return 0;


}

```

```valgrind ./illegal_mem``` ,在函数func内存访问越界了.

```
==13075== Memcheck, a memory error detector
==13075== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==13075== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==13075== Command: ./illegal_mem
==13075== 
==13075== Invalid write of size 4
==13075==    at 0x40080E: func() (illegal_memory.cc:8)
==13075==    by 0x40081E: main (illegal_memory.cc:14)
==13075==  Address 0x5a1c068 is 0 bytes after a block of size 40 alloc'd
==13075==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==13075==    by 0x400801: func() (illegal_memory.cc:7)
==13075==    by 0x40081E: main (illegal_memory.cc:14)
==13075== 
done!
==13075== 
==13075== HEAP SUMMARY:
==13075==     in use at exit: 40 bytes in 1 blocks
==13075==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==13075== 
==13075== LEAK SUMMARY:
==13075==    definitely lost: 40 bytes in 1 blocks
==13075==    indirectly lost: 0 bytes in 0 blocks
==13075==      possibly lost: 0 bytes in 0 blocks
==13075==    still reachable: 0 bytes in 0 blocks
==13075==         suppressed: 0 bytes in 0 blocks
==13075== Rerun with --leak-check=full to see details of leaked memory
==13075== 
==13075== For counts of detected and suppressed errors, rerun with: -v
==13075== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

### 例2:使用未初始化的内存
uninitialized.cc
```
#include <iostream>

using namespace std;

int main(){
        int a[5];
        int i,s;
        a[0] = a[1] = a[3] = a[4] = 0;
    for(i=0;i<5;++i){
                s+=a[i];
            
    }
    if(s==33){
                cout<<"sum is 33"<<endl;
            
    }
        else
            cout<<"sum is not 33"<<endl;

        return 0;


}

```


```valgrind --tool=memcheck ./uninitialized ``` 程序中的a[2]没有定义.


```
==12545== Memcheck, a memory error detector
==12545== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==12545== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==12545== Command: ./uninitialized
==12545== 
==12545== Conditional jump or move depends on uninitialised value(s)
==12545==    at 0x4007F1: main (uninitialized.cc:12)
==12545== 
sum is not 33
```

### 例3:内存读写越界
out_of_bound.cc

```
#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
        int len = 4;
        int * pt = (int *) malloc(len * sizeof(int));
        int * p = pt;
    for(int i = 0;i < len;++i){
                p++;
            
    }
        *p = 5;
        cout<<"the value of p is "<<*p<<endl;

        return 0;

}

```

执行命令```valgrind --tool=memcheck ./out_of_bound ```
输出:

```
==14738== Memcheck, a memory error detector
==14738== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==14738== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==14738== Command: ./out_of_bound
==14738== 
==14738== Invalid write of size 4
==14738==    at 0x400888: main (out_of_bound.cc:13)
==14738==  Address 0x5a1c050 is 0 bytes after a block of size 16 alloc'd
==14738==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14738==    by 0x40085D: main (out_of_bound.cc:8)
==14738== 
==14738== Invalid read of size 4
==14738==    at 0x400892: main (out_of_bound.cc:14)
==14738==  Address 0x5a1c050 is 0 bytes after a block of size 16 alloc'd
==14738==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==14738==    by 0x40085D: main (out_of_bound.cc:8)
==14738== 
the value of p is 5
==14738== 
==14738== HEAP SUMMARY:
==14738==     in use at exit: 16 bytes in 1 blocks
==14738==   total heap usage: 1 allocs, 0 frees, 16 bytes allocated
==14738== 
==14738== LEAK SUMMARY:
==14738==    definitely lost: 16 bytes in 1 blocks
==14738==    indirectly lost: 0 bytes in 0 blocks
==14738==      possibly lost: 0 bytes in 0 blocks
==14738==    still reachable: 0 bytes in 0 blocks
==14738==         suppressed: 0 bytes in 0 blocks
==14738== Rerun with --leak-check=full to see details of leaked memory
==14738== 
==14738== For counts of detected and suppressed errors, rerun with: -v
==14738== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

### 例4:内存覆盖
cover.cc
```
#include <cstdio>
#include <cstdlib>
#include <string.h>

int main()
{
    char x[50];
    int i;
    for(i=0;i<50;++i)
        x[i] = i+1;
    strncpy(x+20,x,20);
    strncpy(x+20,x,21);
    strncpy(x,x+20,20);
    strncpy(x,x+20,21);
    x[39] = '\0';
    strcpy(x,x+20);
    x[39] = 39;
    x[40] = '\0';
    strcpy(x,x+20);
    return 0;
}
```

执行命令:```valgrind --tool=memcheck ./cover```

```
==16251== Memcheck, a memory error detector
==16251== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==16251== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==16251== Command: ./cover
==16251== 
==16251== Source and destination overlap in strncpy(0xffefffa59, 0xffefffa45, 21)
==16251==    at 0x4C2E833: __strncpy_sse2_unaligned (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==16251==    by 0x400640: main (cover.cc:12)
==16251== 
==16251== Source and destination overlap in strncpy(0xffefffa45, 0xffefffa59, 21)
==16251==    at 0x4C2E833: __strncpy_sse2_unaligned (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==16251==    by 0x400678: main (cover.cc:14)
==16251== 
==16251== Source and destination overlap in strcpy(0xffefffa30, 0xffefffa44)
==16251==    at 0x4C2E272: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==16251==    by 0x4006B2: main (cover.cc:19)
==16251== 
==16251== 
==16251== HEAP SUMMARY:
==16251==     in use at exit: 0 bytes in 0 blocks
==16251==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==16251== 
==16251== All heap blocks were freed -- no leaks are possible
==16251== 
==16251== For counts of detected and suppressed errors, rerun with: -v
==16251== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
```

### 5.动态内存管理错误
free_twice.cc

```
#include <iostream>
#include <cstdlib>

int main(){
    char * p = (char *) malloc(10);
    char * pt = p;
    for(int i=0;i<10;++i){
        p[i] = 'z';
    }
    delete p;
    pt[1] = 'x';
    free(pt);
    return 0;
}

```

执行命令```valgrind --tool=memcheck ./free_twice ```

```
==17263== Memcheck, a memory error detector
==17263== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==17263== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==17263== Command: ./free_twice
==17263== 
==17263== Mismatched free() / delete / delete []
==17263==    at 0x4C2C2BC: operator delete(void*) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==17263==    by 0x400739: main (free_twice.cc:10)
==17263==  Address 0x5a1c040 is 0 bytes inside a block of size 10 alloc'd
==17263==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==17263==    by 0x4006FE: main (free_twice.cc:5)
==17263== 
==17263== Invalid write of size 1
==17263==    at 0x400742: main (free_twice.cc:11)
==17263==  Address 0x5a1c041 is 1 bytes inside a block of size 10 free'd
==17263==    at 0x4C2C2BC: operator delete(void*) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==17263==    by 0x400739: main (free_twice.cc:10)
==17263== 
==17263== Invalid free() / delete / delete[] / realloc()
==17263==    at 0x4C2BDEC: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==17263==    by 0x400750: main (free_twice.cc:12)
==17263==  Address 0x5a1c040 is 0 bytes inside a block of size 10 free'd
==17263==    at 0x4C2C2BC: operator delete(void*) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==17263==    by 0x400739: main (free_twice.cc:10)
==17263== 
==17263== 
==17263== HEAP SUMMARY:
==17263==     in use at exit: 0 bytes in 0 blocks
==17263==   total heap usage: 1 allocs, 2 frees, 10 bytes allocated
==17263== 
==17263== All heap blocks were freed -- no leaks are possible
==17263== 
==17263== For counts of detected and suppressed errors, rerun with: -v
==17263== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)

```

### 6.内存泄露
mem_leaks.cc
```
#include <iostream>

using namespace std;

int main(){
    int * ptr = new int [10];
    
    int **arr = new int * [10];
    for(int i = 0;i<10;i++)
        arr[i] = new int [10];


    return 0;
}
```

执行命令：```valgrind --tool=memcheck ./mem_leak```

```
==18802== Memcheck, a memory error detector
==18802== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==18802== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==18802== Command: ./mem_leaks
==18802== 
==18802== 
==18802== HEAP SUMMARY:
==18802==     in use at exit: 520 bytes in 12 blocks
==18802==   total heap usage: 12 allocs, 0 frees, 520 bytes allocated
==18802== 
==18802== LEAK SUMMARY:
==18802==    definitely lost: 120 bytes in 2 blocks #肯定泄露的内存
==18802==    indirectly lost: 400 bytes in 10 blocks　#间接泄露的内存，指向该内存的指针也位于内存泄露区
==18802==      possibly lost: 0 bytes in 0 blocks
==18802==    still reachable: 0 bytes in 0 blocks
==18802==         suppressed: 0 bytes in 0 blocks
==18802== Rerun with --leak-check=full to see details of leaked memory
==18802== 
==18802== For counts of detected and suppressed errors, rerun with: -v
==18802== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```