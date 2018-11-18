# centos #

## centos6.5 minimal 基本环境配置 ##
1. 启动网卡
	1. vi /etc/sysconfig/network-scripts/ifcfg-eth0 ONBOOT=no 改为 yes
	1. service network restart 重启网络
1. 配置sshd
	1. 在/etc/hosts.deny和/etc/hosts.allow加上sshd:ALL
	2. service sshd restart
1. 关闭selinux
	1. vi /etc/selinux/config，SELINUX=enforcing改成SELINUX=disabled
	2. reboot
1. 配置yum源
	1. yum -y install wget
	2. cd /etc/yum.repos.d/
	3. wget http://mirrors.163.com/.help/CentOS6-Base-163.repo
	4. yum clean all
	5. yum makecache
	6. yum update

## 有关yum ##
- yum repolist
	
	显示所有源/仓库列表，实际存放在/etc/yum.repos.d/目录中

## 源码安装git
1. yum remove git
1. yum install curl curl-devel #必须安装的依赖库
1. wget https://github.com/git/git/archive/v2.19.1.tar.gz
1. tar zxvf v2.19.1.tar.gz
1. cd git-2.19.1
1. make configure
1. ./configure --prefix=/usr/local/git --with-iconv=/usr/local/libiconv
1. make all doc
1. sudo make install install-doc install-html
1. sudo vim /etc/profile
1. export PATH=/usr/local/git/bin:$PATH
1. source /etc/profile

## 源码安装cmake
1. yum install gcc gcc-c++ ncurses-devel perl
2. wget https://cmake.org/files/v3.3/cmake-3.3.2.tar.gz
3. tar zxvf cmake-3.3.2.tar.gz
4. cd cmake-3.3.2
5. ./configure
6. make && make install


## 升级内核(源码升级)

## 升级内核(yum升级)
1. uname -r
2. rpm --import https://www.elrepo.org/RPM-GPG-KEY-elrepo.org
3. rpm -Uvh http://www.elrepo.org/elrepo-release-6-8.el6.elrepo.noarch.rpm #参考：http://elrepo.org/tiki/tiki-index.php 根据系统版本选择el源
4. yum --enablerepo=elrepo-kernel install kernel-lt -y #或者安装kernel-ml（ml=mainline），yum --enablerepo=elrepo-kernel install kernel-ml -y
5. vim /etc/grub.conf，修改default=0