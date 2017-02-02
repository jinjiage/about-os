# Linux系统调用 #

一、进程控制：

函数 | 说明 | 简要流程及使用Demo
-------------|-------------|-------------
fork|	创建一个新进程|
clone|	按指定条件创建子进程|
execve|	运行可执行文件|
exit|	中止进程|
_exit|	立即中止当前进程|
getdtablesize|	进程所能打开的最大文件数|
getpgid|	获取指定进程组标识号|
setpgid|	设置指定进程组标志号|
getpgrp|	获取当前进程组标识号|
setpgrp|	设置当前进程组标志号|
getpid|	获取进程标识号|
getppid|	获取父进程标识号|
getpriority|	获取调度优先级|
setpriority|	设置调度优先级|
modify_ldt|	读写进程的本地描述表|
nanosleep|	使进程睡眠指定的时间|
nice|	改变分时进程的优先级|
pause|	挂起进程，等待信号|
personality|	设置进程运行域|
prctl|	对进程进行特定操作|
ptrace|	进程跟踪|
sched_get_priority_max|	取得静态优先级的上限|
sched_get_priority_min|	取得静态优先级的下限|
sched_getparam|	取得进程的调度参数|
sched_getscheduler|	取得指定进程的调度策略|
sched_rr_get_interval|	取得按RR算法调度的实时进程的时间片长度|
sched_setparam|	设置进程的调度参数|
sched_setscheduler|	设置指定进程的调度策略和参数|
sched_yield|	进程主动让出处理器,并将自己等候调度队列队尾|
vfork|	创建一个子进程，以供执行新程序，常与execve等同时使用|
wait|	等待子进程终止|
wait3|  参见wait|
waitpid|	等待指定子进程终止|
wait4|	参见waitpid|
capget|	获取进程权限|
capset|	设置进程权限|
getsid|	获取会晤标识号|
setsid|	设置会晤标识号|

二、文件系统控制
1、文件读写操作

函数 | 说明 | 简要流程及使用Demo
-------------|-------------|-------------
fcntl|	文件控制|
open|	打开文件|
creat|	创建新文件|
close|	关闭文件描述字|
read|	读文件|
write|	写文件|
readv|	从文件读入数据到缓冲数组中|
writev|	将缓冲数组里的数据写入文件|
pread|	对文件随机读|
pwrite|	对文件随机写|
lseek|	移动文件指针|
_llseek|	在64位地址空间里移动文件指针|
dup|	复制已打开的文件描述字|
dup2|	按指定条件复制文件描述字|
flock|	文件加/解锁|
poll|	I/O多路转换|
truncate|	截断文件|
ftruncate|	参见truncate|
umask|	设置文件权限掩码|
fsync|	把文件在内存中的部分写回磁盘|

2、文件系统操作

函数 | 说明 | 简要流程及使用Demo
-------------|-------------|-------------
access|	确定文件的可存取性|
chdir|	改变当前工作目录|
fchdir|	参见chdir|
chmod|	改变文件方式|
fchmod|	参见chmod|
chown|	改变文件的属主或用户组|
fchown|	参见chown|
lchown|	参见chown|
chroot|	改变根目录|
stat|	取文件状态信息|
lstat|	参见stat|
fstat|	参见stat|
statfs|	取文件系统信息|
fstatfs|	参见statfs|
readdir|	读取目录项|
getdents|	读取目录项|
mkdir|	创建目录|
mknod|	创建索引节点|
rmdir|	删除目录|
rename|	文件改名|
link|	创建链接|
symlink|	创建符号链接|
unlink|	删除链接|
readlink|	读符号链接的值|
mount|	安装文件系统|
umount|	卸下文件系统|
ustat|	取文件系统信息|
utime|	改变文件的访问修改时间|
utimes|	参见utime|
quotactl|	控制磁盘配额|