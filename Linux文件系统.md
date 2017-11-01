# Linux文件系统 #


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
	- 索引节点对象inode及操作对象inode_operations
	- 目录项对象dentry及操作对象dentry_operations
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
- struct proc\_dir\_entry

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

- static const struct dentry\_operations proc\_sys\_dentry\_operations;

- static const struct file\_operations proc\_sys\_file\_operations;

- static const struct inode\_operations proc\_sys\_inode\_operations;

- static const struct file\_operations proc\_sys\_dir\_file\_operations;

- static const struct inode\_operations proc\_sys\_dir\_operations;

### 核心函数 ###
- proc\_root\_init函数，注册proc文件系统及创建部分/proc顶层目录和文件
	- 调用proc\_init\_inodecache创建proc专用inode缓存
	- 调用register\_filesystem注册文件系统proc\_fs_type

			static struct file_system_type proc_fs_type = {
	    		.name		= "proc",
	    		.mount		= proc_mount,
	    		.kill_sb	= proc_kill_sb,
	    		.fs_flags	= FS_USERNS_MOUNT,
	    	};
	- proc\_self_init
		- proc\_alloc\_inum(&self_inum);从proc\_inum\_ida(基于idr一种快速查找数据结构对象的技术，proc\_inum\_ida是其中的一个layer)中分配一个i，加上PROC\_DYNAMIC\_FIRST基址后赋给self\_inum,后续作为/proc/self的inode的id
	- proc_thread_self_init，同上，赋给thread\_self\_inum
	- proc_symlink
	- proc\_net_init
	- proc_mkdir
	- proc\_tty_init
	- proc\_sys_init
- proc_mount挂载函数
	- proc\_fill_super
		- root\_inode = proc\_get_inode(s, &proc\_root);**申请proc文件系统的根目录inode对象，同时安装inode\_operations proc\_root\_inode\_operations和file\_operations proc\_root\_operations**
- proc\_root\_lookup函数，**根目录inode\_operations proc\_root\_inode\_operations的.lookup函数，下面选择其一**
	- proc\_pid\_lookup
	- proc\_lookup

## sysfs文件系统 ##
### 初始化 ###

- sysfs_init

## udev文件系统 ##
### 初始化 ###

## docker aufs联合文件系统 ##
### 初始化 ###

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