# Linux设备管理 #
## 字符设备 ##
## 块设备 ##
### loop循环设备 ###

loop循环设备是一个可以回接普通文件或块设备文件的虚拟块设备，可以用于各种用途。

- loop_init初始化,大致流程↓
	- register\_blkdev(LOOP_MAJOR, "loop")，注册块设备，主设备号7
- loop_add添加loop设备
- lo_ioctl
	- LOOP\_SET\_FD命令 =====> loop\_set\_fd，设置回接对象
		- loop_prepare_queue准备队列
		- loop_sysfs_init,sysfs相关
		- bdgrab，/dev相关
	- LOOP\_CHANGE\_FD命令 =====> loop\_change\_fd，打开loop设备
		- loop_switch
			- 回接块设备
			- 回接普通文件

## FIFO ##
## socket ##
