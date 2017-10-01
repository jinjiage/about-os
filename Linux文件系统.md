# Linux文件系统 #
                     App    App     App    App
    ------------------|-----------------------------------------    
                      |    C标准库(Libc)
	------------------|-----------------------------------------    用户空间
		                   系统调用层
	------------------------------------------------------------    内核空间
	文件 虚拟：            VFS虚拟文件系统
         -------------------------------------------------------    
    系统 具体： procfs/sysfs(特殊文件)   sockfs   Ext2/3(普通文件) 
	-----------------|--------------------|-----------|-----------------
                                       网络协议    通用块层
		                                          IO调度层           
                                       网卡驱动    块设备驱动
	-----------------|--------------------|------------|----------------
    硬件          内    存              网   卡  硬盘及其他存储块设备
	------------------------------------------------------------
	linux的文件系统处于系统调用层和块I/O子系统之间，包含VFS虚拟文件系统和具体文件系统两部分：
    1、VFS是上层应用和具体文件系统之间的接口层，被称为虚拟文件系统，也称为虚拟文件系统交换层（Virtual Filesystem Switch），它为应用程序员提供一层抽象，屏蔽底层各种具体文件系统的差异；它将各种具体文件系统的操作和管理内入统一的框架；
	2、具体文件系统有procfs、sysyfs、sockfs、Ext2/3/4等，不同文件系统有各自的应用场景，以模块的形式向VFS注册回调函数；


## 系统调用层 ##
linux提供了open、read、write、mount等常见的文件系统相关的调用接口,还有一些专用的系统调用，例如sockfs文件系统的socket、bind

- mount命令
	- 通过系统调用层COMPAT\_SYSCALL\_DEFINE5(mount和SYSCALL_DEFINE5(mount
		- do_mount
			- 修改挂载点属性
				- do_remount
			- 绑定loop
				- do_loopback
			- 修改挂载点传播方式
				- do_change_type
			- 挂载点转移
				- do_move_mount
			- 创建新的挂载点
				- do\_new\_mount
					- vfs\_kern\_mount，通过file\_system_type和文件系统名称返回vfsmount挂载点

## VFS虚拟文件系统 ##
- 概念
	- 在内核中唯一标示一种文件系统，file\_system\_type
		- name：文件系统名字，可以通过/proc/filesystems中查看已注册的文件系统
		- fs_flags：文件系统类型
			- FS\_REQUIRES\_DEV: 文件系统必须在物理设备上，cat /proc/filesystems可观察；
			- FS\_BINARY_MOUNTDATA:
			- FS\_HAS\_SUBTYPE: 文件系统含有子类型，最常见的就是FUSE，FUSE是用户态文件系统框架，所以要通过子文件系统类型来区别通过FUSE接口实现的不同文件系统；
			- FS\_USERNS\_MOUNT: 文件系统每次挂载都后都是不同的user namespace，如用于devpts；
			- FS\_USERNS\_DEV\_MOUNT: user namespace挂载支持MNT_DEV， 即非nodev模式。
			- FS\_RENAME\_DOES\_D\_MOVE: 文件系统将把重命名操作reame()直接按照移动操作d_move()来处理，主要用于网络文件系统；
		- mount：用户挂载此文件系统时使用的回调函数；
		- kill\_sb: 删除内存中的super block，在卸载文件系统时使用；
		- next: 指向文件系统类型链表的下一个文件系统类型；
		- fs\_supers: 具有相同文件系统类型的超级块结构，即系统中可以有多个super\_block;
	- 超级块结构super_block
	- 索引节点结构inode
	- 目录项结构dentry
	- 文件结构file
	- 挂载点结构vfsmount

- 核心函数
	- vfs\_caches\_init，为文件系统准备缓存，参考《文件系统初始化流程》
	- register\_filesystem，注册文件系统，本质上把预定义的file\_system\_type类型变量放到全局变量file_systems中
	- mount\_nodev、
	- kern_mount宏，很多内置文件系统通过该宏挂载
		- vfs\_kern\_mount
			- mount\_fs

## proc文件系统 ##
### 核心数据结构
- struct proc\_dir\_entry代表目录和文件

	在proc文件系统中，由proc\_dir\_entry代表目录，而/proc目录比较特殊，该目录下有一些“数字”代表进程的PID，而其他proc\_dir\_entry由proc_mkdir函数创建

	    struct proc_dir_entry proc_root = {
	    	.low_ino	= PROC_ROOT_INO, 
	    	.namelen	= 5, 
	    	.mode		= S_IFDIR | S_IRUGO | S_IXUGO, 
	    	.nlink		= 2, 
	    	.count		= ATOMIC_INIT(1),
	    	.proc_iops	= &proc_root_inode_operations,  //其他目录，使用proc_dir_inode_operations；文件，使用proc_file_inode_operations
	    	.proc_fops	= &proc_root_operations,        //其他目录，使用proc_dir_operations
	    	.parent		= &proc_root,                   //指向自身，其他目录指向父目录的proc_dir_entry
	    	.subdir		= RB_ROOT,
	    	.name		= "/proc",
    	};

- static const struct file\_operations proc\_reg\_file\_ops
- static const struct inode\_operations proc\_root\_inode\_operations
- struct proc\_dir\_entry proc_root
- static struct file\_system\_type proc\_fs\_type

### 核心函数 ###
- proc\_root\_init函数，初始化
	1. 调用proc\_init\_inodecache创建inode缓存
	2. 调用register\_filesystem注册文件系统proc\_fs_type

			static struct file_system_type proc_fs_type = {
	    		.name		= "proc",
	    		.mount		= proc_mount,
	    		.kill_sb	= proc_kill_sb,
	    		.fs_flags	= FS_USERNS_MOUNT,
	    	};

- proc_mkdir函数，用于创建目录
- proc_create函数，用于创建文件

> 调用register_filesystem注册proc文件类型		



## sysfs文件系统 ##
### 初始化 ###

- sysfs_init

### 注册 ###

> 调用register_filesystem注册sysfs文件类型		

	static struct file_system_type sysfs_fs_type = {
		.name		= "sysfs",
		.mount		= sysfs_mount,
		.kill_sb	= sysfs_kill_sb,
		.fs_flags	= FS_USERNS_MOUNT,
	};
 
### linux设备层次（kobject层次结构） ###

- struct kobject

- kobject\_create\_and\_add在已有kobject对象下添加新kobject对象


## cgroup文件系统 ##
> 调用register_filesystem注册cgroup文件类型		

	static struct file_system_type cgroup_fs_type = {
		.name = "cgroup",
		.mount = cgroup_mount,
		.kill_sb = cgroup_kill_sb,
	};

## 文件系统初始化流程
- start_kernel()
	- vfs\_caches\_init_early()
		- dcache\_init_early()，为文件系统的目录项结构dentry分配哈希
		- inode\_init_early()，为文件系统的inode索引节点分配哈希
	- vfs\_caches_init()
		- dcache_init()，为文件系统的目录项结构dentry分配内存及哈希
		- inode_init()，为文件系统的inode索引节点分配内存及哈希
	    - files_init(mempages)，为文件结构分配内存
	    - mnt_init()
		    - sysfs_init()，注册sysfs文件系统
			- init_rootfs()，注册rootfs文件系统
			- init\_mount_tree()
				- vfs\_kern_mount(type, 0, "rootfs", NULL)，挂载rootfs
				- create\_mnt_ns()，创建命名空间namespace
				- set\_fs\_pwd(current->fs, &root)，命名空间赋值给init_task进程的pwd和root
				- set\_fs_root(current->fs, &root)
		- bdev\_cache_init()
			- kmem\_cache_create()，为bdev文件系统的inode索引节点分配内存
			- kern\_mount(&bd_type)，挂载bdev文件系统
		- chrdev_init()，为字符设备初始化设备号