### top

用于实时显示系统中各个进程的资源占用情况。
重点介绍一点-下方列表表头:
1. PID　进程号
2. USER　运行用户
3. PR 优先级
4. NI 任务nice值
5. VIRT 虚拟内存用量
6. RES 物理内存用量
7. SHR　共享内存用量
8. S 进程状态
9. %CPU CPU占用比
10. %MEM MEM占用比
11. TIME+ 累计CPU占用时间
12. COMMAND 命令名／命令行　

### ps 
命令参数详解：
1. ps -u user　显示指定用户的信息
2. ps -ef　显示所有进程的信息
3. ps -l 将当前登入的PID与相关信息显示出来
4. ps aux 列出目前所有的正在内存中的程序

STAT状态参数：
1. R running 当前正在运行
2. S sleeping 当前正在睡眠
3. T stoped 当前程序已经停止
4. Z zombie 当前进程已经僵死
