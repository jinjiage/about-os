# Linux系统调用 #

一、进程控制：
------|------
fork|	创建一个新进程
clone|	按指定条件创建子进程
execve|	运行可执行文件
exit|	中止进程
_exit|	立即中止当前进程
getdtablesize|	进程所能打开的最大文件数
getpgid|	获取指定进程组标识号
setpgid|	设置指定进程组标志号
getpgrp|	获取当前进程组标识号
setpgrp|	设置当前进程组标志号
getpid|	获取进程标识号
getppid|	获取父进程标识号
getpriority|	获取调度优先级
setpriority|	设置调度优先级
modify_ldt|	读写进程的本地描述表
nanosleep|	使进程睡眠指定的时间
nice|	改变分时进程的优先级
pause|	挂起进程，等待信号
personality|	设置进程运行域
prctl|	对进程进行特定操作
ptrace|	进程跟踪
sched_get_priority_max|	取得静态优先级的上限
sched_get_priority_min|	取得静态优先级的下限
sched_getparam|	取得进程的调度参数
sched_getscheduler|	取得指定进程的调度策略
sched_rr_get_interval|	取得按RR算法调度的实时进程的时间片长度
sched_setparam|	设置进程的调度参数
sched_setscheduler|	设置指定进程的调度策略和参数
sched_yield|	进程主动让出处理器,并将自己等候调度队列队尾
vfork|	创建一个子进程，以供执行新程序，常与execve等同时使用
wait|	等待子进程终止
wait3|  参见wait
waitpid|	等待指定子进程终止
wait4|	参见waitpid
capget|	获取进程权限
capset|	设置进程权限
getsid|	获取会晤标识号
setsid|	设置会晤标识号