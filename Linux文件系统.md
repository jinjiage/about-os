# Linux文件系统 #
       App    App     App    App
    --------------------------------
             C标准库(Libc)
	--------------------------------     用户空间
		      系统调用层
	--------------------------------     内核空间
	文件      VFS虚拟文件系统
         ---------------------------
    系统 具体文件系统： Ext2/3 procfs sysfs sockfs 
	--------------------------------
		      块I/O子系统
	--------------------------------
	
	linux的文件系统处于系统调用层和块I/O子系统之间，包含VFS虚拟文件系统和具体文件系统两部分：
    1、VFS是上层应用和具体文件系统之间的接口层，将各种具体文件系统的操作和管理内入统一的框架；
	2、具体文件系统有procfs、sysyfs、sockfs、Ext2/3/4，不同文件系统有各自的应用场景，以模块的形式向VFS注册回调函数；

## 系统调用层 ##
linux提供了open、read、write、mount等常见的文件系统相关的调用接口,还有一些专用的系统调用，例如sockfs文件系统的socket、bind

##文件系统 ##
- 概念
	- filesystem type
	- super block
	- inode
	- dentry
	- vfsmount


### VFS虚拟文件系统 ###
file_systems（定义在fs/filesystems.c）指向文件系统类型的指针

### 具体文件系统 ###
### proc ####
### sysfs ###
### sockfs ###

## 核心函数 ##
- vfs\_caches\_init初始化缓存
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
- struct proc_dir_entry {
- static const struct file_operations proc_reg_file_ops
- static const struct inode_operations proc_root_inode_operations
- struct proc_dir_entry proc_root
- static struct file_system_type proc_fs_type

### 核心函数 ###
- proc_create

> 调用register_filesystem注册proc文件类型		

	static struct file_system_type proc_fs_type = {
		.name		= "proc",
		.mount		= proc_mount,
		.kill_sb	= proc_kill_sb,
		.fs_flags	= FS_USERNS_MOUNT,
	};

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