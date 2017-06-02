# Linux设备管理 #
## 字符设备 ##
## 块设备 ##
### loop循环设备 ###

loop循环设备是一个可以回接普通文件或块设备文件的虚拟块设备，可以用于各种用途。

- loop_init初始化,大致流程↓
	- register\_blkdev(LOOP_MAJOR, "loop")，注册块设备，主设备号7
	- loop_add添加loop设备
		- 通过kzalloc，申请struct loop_device对象lo
		- 设置lo对象，
			- .lo_state,设置为Lo_unbound
			- .tag_set.ops,设置blk_mq_ops为loop_mq_ops
			- .lo_queue,调用blk_mq_init_queue创建request_queue队列同时设置队列处理函数
		- alloc_disk，申请struct gendisk对象disk
		- 设置disk
			- disk->fops	，设置struct block_device_operations对象为lo_fops
			- disk->queue，设置队列lo->lo_queue
		- add_disk
- lo_ioctl
	- LOOP\_SET\_FD命令 =====> loop\_set\_fd，设置回接对象
		- loop\_prepare_queue准备队列
		- loop\_sysfs_init,sysfs相关
		- bdgrab，/dev相关
	- LOOP\_CHANGE\_FD命令 =====> loop\_change\_fd，打开loop设备
		- loop_switch
			- 回接块设备
			- 回接普通文件

## FIFO ##
## socket ##
