# Linux虚拟文件系统 #

## 命令 ##
- df -lhaT
- mount
- umount

## 核心数据结构 ##
- struct mount {
- struct vfsmount {
- struct super_block {
- struct dentry｛
- struct inode { 
- struct files_struct {
- struct fs_struct {
- struct path {
- struct file_system_type {
- struct file_operations {
- static struct file_system_type *file_systems

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