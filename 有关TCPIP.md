#有关TCP/IP(Linux实现)

## 1. 网络协议栈初始化 ##
### 1. 初始化顺序 ###
1. core\_initcall：sock_init，网络基础系统初始化
	1. 网络内存管理
	2. 网络文件系统初始化
		1. 调用**net_sysctl_init**
		2. 调用**skb_init**
		3. 调用**init_inodecache**创建inode缓存
		2. 调用**register\_filesystem**注册文件系统static struct file_system\_type **sock\_fs\_type** 
		3. 调用**kern\_mount**挂载文件系统

		备注：这里注册自身的sockfs文件系统及在proc文件系统下创建/proc/sys/net目录，对于这两种文件系统的分析，详见![Linux虚拟文件系统](Linux虚拟文件系统.md)

2. fs\_initcall：inet_init，网络协议初始化
3. subsys\_initcall：net\_dev_init
4. device\_initcall：设备驱动初始化

### 2. 系统调用 ###
#### 1. sock系统调用（net/socket.c） ####
1. 调用**sock\_create**，利用三元组↓，来构造struct socket *sock对象
	- 协议族，例如AF\_INET、AF\_INET6、AF\_LOCAL（或称AF\_UNIX，Unix域socket）、AF\_ROUTE等，
	- socket类型有SOCK\_STREAM、SOCK\_DGRAM、SOCK\_RAW、SOCK\_PACKET、SOCK\_SEQPACKET等，
    - 协议有IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等
    
2. 调用**sock\_map_fd**，sock与file挂钩，对file的操作映射到了static const struct file\_operations socket_file_ops