# Linux容器技术 #
Docker是虚拟化的一种轻量级替代技术。Docker的容器技术不依赖任何语言、框架或系统，可以将App变成一种标准化的、可移植的、自管理的组件，并脱离服务器硬件在任何主流系统中开发、调试和运行。

## 容器核心技术 ##
- namespaces命名空间 - *提供环境的隔离*
- cgroups控制组 - *提供资源的隔离*
- AUFS层状文件系统 - *提供文件系统的隔离*

## namespaces命名空间 ##
1. UTS: CLONE_NEWUTS,命名空间间hostname主机名隔离,始于Linux2.4.19
1. IPC: CLONE_NEWIPC,命名空间内进程间通信,始于Linux2.6.19
1. PID: CLONE_NEWPID，命名空间间的进程PID隔离，始于Linux2.6.24
1. NS: CLONE_NEWNS，挂载点隔离，始于Linux2.4.19
1. NET: CLONE_NEWNET，网络隔离，始于Linux2.6.29
1. USER: CLONE_NEWUSER，虚拟user-id映射到真实的user-id，始于Linux3.8

## cgroups控制组 ##
### cgroups文件系统 ###
### cgroups子系统 ###
1. cpu子系统，限制进程的cpu使用率
1. cpuacct子系统，cpu使用报告
1. cpuset子系统，分配单独的cpu节点或者内存节点
1. memory子系统，限制memory使用量
1. blkio子系统，限制块设备io
1. devices子系统，控制进程访问某些设备
1. net_cls子系统，标记网络数据包，然后可以使用tc模块traffic control对数据包进行控制
1. freezer子系统，挂起或者恢复cgroups中的进程
1. ns子系统，不同cgroups下面的进程使用不同的namespace

## AUFS层状文件系统 ##
