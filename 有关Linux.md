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