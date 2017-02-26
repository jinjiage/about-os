# Linux网络管理 #

## 网络协议 ##
![](doc/protocols.png)

## Linux网络实现及数据流 ##
![](doc/Network_data_flow_through_kernel.png)

## Linux网络IO模型 ##
![](doc/io-model.png)

## 网络设备 ##

### 网桥briage ###

### 虚拟以太网卡veth ###

### TUN/TAP ###

### bonding ###

  bonding的模式一共有7种，常用的为0、1两种：

- round-robin(balance-rr)  0  网卡的负载均衡模式
- active-backup  1 网卡的容错模式
- balance-xor  2 需要交换机支持
- broadcast  3 广播模式
- ieee802.3ad  4 动态链路聚合模式，需要交换机支持
- mode-tlb  5 自适应模式
- mode-alb  6 网卡虚拟化方式

## 网络IO模型及编程 ##
- blocking 同步阻塞式I/O
	
	默认情况下,所有套接口都是阻塞的
		
	![](doc/blocking.png)

	单进程模型             |  多线程/进程模式 | 线程/进程池模式
	:-------------------------:|:-------------------------:|:-------------------------:
	![](doc/network-singleprocess.png)  |  ![](doc/network-multithread.png) |  ![](doc/network-threadpool.png)

	1. 通过多线程/进程模式**解决了多连接阻塞问题**，连接用的accept函数在主进程中，把影响（指阻塞）accept的数据交互部分（recv和send）移到子线程/进程中，这样就不会阻塞连接也不会阻塞其他子线程/进程收发数据，是一种被动规避方案
	2. 多线程/进程模式下，虽然一定程度上解决了连接问题，但大量连接情况下会导致大量的线程/进程开销
	3. 线程/进程池模式，解决在一定程度上解决了连接问题和开销问题，但同样存在“池”大小选择问题，过大过小都不合适
	4. 上面两种模式，线程/进程中没有使用非阻塞I/O，因为没有必要

- nonblocking 同步非阻塞式I/O

	![](doc/nonblocking.png)

- multiplexing I/O多路复用(select/poll/epoll)

- signal driven 信号驱动式I/O(SIGIO)

- asynchronous 异步I/O(POSIX的aio_系列函数)

## 管理工具 ##
- ifconfig
- ethtool
- iwconfig
- tcpdump
- netstat
- ping
- hostname
- ip
