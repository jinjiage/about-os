# Linux文件系统 #
                     App    App     App    App
    ------------------|-----------------------------------------    
                      |    C标准库(Libc)
	------------------|-----------------------------------------    用户空间
		                   系统调用层
	------------------------------------------------------------    内核空间
	文件 虚拟：            VFS虚拟文件系统
         -------------------------------------------------------    
    系统 具体： procfs/sysfs(特殊文件)   sockfs   Ext2/3(普通文件)   devfs(设备文件)
	-----------------|--------------------|-----------|-----------------|-----
                                       网络协议    通用块层
		                               网卡驱动    IO调度层           设备驱动
	-----------------|--------------------|------------|----------------|-----
    硬件          内    存              网   卡  硬盘及其他存储块设备   其他设备  
	------------------------------------------------------------
	linux的文件系统处于系统调用层和块I/O子系统之间，包含VFS虚拟文件系统和具体文件系统两部分：
    1、VFS是上层应用和具体文件系统之间的接口层，被称为虚拟文件系统，也称为虚拟文件系统交换层（Virtual Filesystem Switch），它为应用程序员提供一层抽象，屏蔽底层各种具体文件系统的差异；它将各种具体文件系统的操作和管理内入统一的框架；
	2、具体文件系统有procfs、sysyfs、sockfs、Ext2/3/4等，不同文件系统有各自的应用场景，以模块的形式向VFS注册回调函数；

## 系统调用层 ##
linux提供了open、read、write、mount等常见的文件系统相关的调用接口,还有一些专用的系统调用，例如sockfs文件系统的socket、bind

- mount命令
	- 通过系统调用层COMPAT_SYSCALL_DEFINE5(mount和SYSCALL_DEFINE5(mount
		- do_mount
			- do\_new\_mount
				- vfs\_kern\_mount，通过file\_system_type和文件系统名称返回vfsmount挂载点

## VFS虚拟文件系统 ##
- 概念
	- 文件系统类型结构filesystem，
	- 超级块结构super_block
	- 索引节点结构inode
	- 目录项结构dentry
	- 文件结构
	- 挂载点结构vfsmount

- 核心函数
	- vfs\_caches\_init初始化文件系统
		- dcache_init目录项缓存
		- inode_init节点缓存
		- files_init文件缓存
		- mnt_init挂节点缓存
			- kernfs_init
			- sysfs_init
			- init_rootfs
			- init_mount_tree
				- vfs\_kern\_mount 
		- bdev_cache_init块设备缓存
		- chrdev_init字符设备缓存 
	- register_filesystem
	- mount\_nodev、
	- kern_mount宏，很多内置文件系统通过该宏挂载
		- vfs\_kern\_mount
			- mount\_fs
## ramfs文件系统 ##

> 调用register_filesystem注册ramfs文件类型	

	static struct file_system_type ramfs_fs_type = {
		.name		= "ramfs",
		.mount		= ramfs_mount,
		.kill_sb	= ramfs_kill_sb,
		.fs_flags	= FS_USERNS_MOUNT,
	};

## tmpfs文件系统 ##

> 调用register_filesystem注册tmpfs文件类型	

	static struct file_system_type shmem_fs_type = {
		.owner		= THIS_MODULE,
		.name		= "tmpfs",
		.mount		= shmem_mount,
		.kill_sb	= kill_litter_super,
		.fs_flags	= FS_USERNS_MOUNT,
	};

## rootfs文件系统（ramfs、tmpfs） ##
### 初始化 ###

- init_rootfs

> 调用register_filesystem注册rootfs文件类型		

	static struct file_system_type rootfs_fs_type = {
		.name		= "rootfs",
		.mount		= rootfs_mount,
		.kill_sb	= kill_litter_super,
	};
> rootfs\_mount->mount\_nodev

## devtmpfs文件系统（ramfs、tmpfs） ##
> 调用register_filesystem注册devtmpfs文件类型		

	static struct file_system_type dev_fs_type = {
		.name = "devtmpfs",
		.mount = dev_mount,
		.kill_sb = kill_litter_super,
	};

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

- static const struct file_operations proc_reg_file_ops
- static const struct inode_operations proc_root_inode_operations
- struct proc_dir_entry proc_root
- static struct file_system_type proc_fs_type

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
				- set\_fs_pwd(current->fs, &root)，命名空间赋值给init_task进程的pwd和root
				- set\_fs_root(current->fs, &root)
		- bdev_cache_init()
			- kmem_cache_create()，为bdev文件系统的inode索引节点分配内存
			- kern_mount(&bd_type)，挂载bdev文件系统
		- chrdev_init()，为字符设备初始化设备号