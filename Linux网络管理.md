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

## 管理工具 ##
- ifconfig
- ethtool
- iwconfig
- tcpdump
- netstat
- ping
- hostname
- ip
