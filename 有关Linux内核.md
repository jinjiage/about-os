#有关Linux内核

##重要流程
###启动加载器GRUB
###第一个程序 - Init
###第一个程序 - systemd
###内核信息
	cat /proc/cmdline
	cat /proc/kallsyms
###工具
####Ftrace(>=2.6.27，Documentation/ftrace.txt)
	$sudo su							 #切换到root
    $cd /sys/kernel/debug/tracing		#存在，表明支持Ftrace
    $cat available_tracers			   #该内核支持的trace类
    $sudo apt-get install trace-cmd      #Ftrace前端命令工具
    $sudo apt-get install kernelshark    #Ftrace可视化前端工具