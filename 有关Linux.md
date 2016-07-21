#有关Linux
*-----Linux学习笔记*


##有关Linux内核
###引导
- BIOS
- 加载内核

###启动加载器GRUB
###编译内核
	apt-get source linux-image-$(uname -r)		#下载当前版本内核
###vmlinuz可引导的、压缩的内核（vmlinux未压缩）
	make zImage		#小内核，自带gzip解压代码，老的zImage解压缩内核到低端内存(第一个640K)
    make bzImage	#大内核，自带gzip解压代码，bzImage解压缩内核到高端内存(1M以上)
###initrd.img
###System.map内核符号表
	cat /boot/System.map | grep do_fork		#查看do_fork地址
###初始化系统 - sysvinit
###初始化系统 - systemd
###内核信息
	cat /proc/cmdline
	cat /proc/kallsyms


###有关Linux运维
####简单shell命令
    sh -n xxx.sh       	#检查语法
	sh -vx xxx.sh		#运行跟踪
	touch file			#创建文件
	cp file1 file2				#拷贝文件，有些比较强大的选项，例如-R递归拷贝，-P保留原有时间
    mv name1 name2		#修改名字
    rm 	 file/dir		#删除文件或目录，-rf递归强制删除
	mkdir dir		#创建目录，rmdir dir可以删除空目录
    stat file		#查看文件统计信息
    file name		#查看文件类型，类型分为：文本文件、可执行文件、数据文件
    cat file		#查看文件内容，-b显示行号，-T不显示制表符
    head/tail file		#查看部分文件内容
    more/less		#分屏显示

####进程管理
	ps		#显示进程信息，最复杂的命令之一，支持三种风格选项，Unix、BSD、GNU
	top		#实时显示进程信息
    kill pid		#例如发送KILL无条件终止信号，kill -9 pid or kill -s KILL pid
    killall pidname	#通杀所有进程，支持通配符

####环境变量
	set		#显示所有有值变量，包括局部环境变量和全局环境变量
    unset var		#删除环境变量
    var=value		#设置局部环境变量，通常用小写字母，用于区分全局变量
    echo $var		#显示变量的值
    export var		#导到全局环境中，这样所有shell进程中都可见

####debian/ubuntu软件包管理
	/etc/apt/source.list		#软件源

####键盘布局
	loadkeys "keymap_name"		#键盘布局，ubuntu：/usr/share/ibus/keymaps

####硬盘分区


###有关Linux工具
####Ftrace(>=2.6.27，Documentation/ftrace.txt)
	$sudo su							#切换到root
    $cd /sys/kernel/debug/tracing		#存在，表明支持Ftrace
    $cat available_tracers				#该内核支持的trace类
    $sudo apt-get install trace-cmd		#Ftrace前端命令工具
    $sudo apt-get install kernelshark	#Ftrace可视化前端工具

###资料
- [SysVinit (简体中文)] (https://wiki.archlinux.org/index.php/SysVinit_\(简体中文\))
- UNIX Linux系统管理技术手册（第4版）
- Linux命令行与Shell脚本编程大全