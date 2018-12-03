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

## 有关rpm ##
- 查看依赖
	
	rpm -q --requires

- 查看文件的提供者

	rpm -qf

- 查看安装位置

	rpm -ql

- 提取文件
	1. rpm2cpio test.rpm > test.cpio
	1. cpio -i --make-directories < test.cpio  

## 有关yum ##
- /usr/bin/yum

	python脚本，默认使用python2.6	

- yum repolist
	
	显示所有源/仓库列表，实际存放在/etc/yum.repos.d/目录中

- 安装epel第三方源

    CentOs 5.x，rpm -Uvh http://mirror.webtatic.com/yum/el5/latest.rpm

	CentOs 6.x，rpm -Uvh http://mirror.webtatic.com/yum/el6/latest.rpm

	CentOs 7.X，rpm -Uvh https://mirror.webtatic.com/yum/el7/epel-release.rpm;
				rpm -Uvh https://mirror.webtatic.com/yum/el7/webtatic-release.rpm

## 有关网络


## 源码安装git
1. yum remove git
1. yum install curl curl-devel #必须安装的依赖库
1. wget https://github.com/git/git/archive/v2.19.1.tar.gz
1. tar zxvf v2.19.1.tar.gz
1. cd git-2.19.1
1. make configure
1. ./configure --prefix=/usr/local/git --with-iconv=/usr/local/libiconv
1. make all doc #可能需要asciidoc、zlib-devel、xmlto
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

## 源码安装python
1. wget https://bootstrap.pypa.io/get-pip.py
2. python34 get-pip.py #安装对应版本pip

## 升级docker最新版
1. yum install docker-io #epel库，最新版本docker-1.7
1. curl -sSL -O https://get.docker.com/builds/Linux/x86_64/docker-1.9.1 #继续升级到docker-1.9
1. chmod +x docker-1.9.1 
1. mv /usr/bin/docker /usr/bin/docker-1.7
1. cp ./docker-1.9.1 /usr/bin/docker
1. /etc/init.d/docker restart
1. pip install docker-compose #安装docker-compose编码工具

## rpm安装ffmpeg
1. yum localinstall --nogpgcheck https://download1.rpmfusion.org/free/el/rpmfusion-free-release-6.noarch.rpm
1. yum -y install ffmpeg ffmpeg-devel

## 升级内核(源码升级)

## 升级内核(yum升级)
1. uname -r
1. yum update nss #如果出现curl: (35) SSL connect error
1. rpm --import https://www.elrepo.org/RPM-GPG-KEY-elrepo.org
1. rpm -Uvh http://www.elrepo.org/elrepo-release-6-8.el6.elrepo.noarch.rpm #参考：http://elrepo.org/tiki/tiki-index.php 根据系统版本选择el源
1. yum --enablerepo=elrepo-kernel install kernel-lt -y #或者安装kernel-ml（ml=mainline），yum --enablerepo=elrepo-kernel install kernel-ml -y
1. vim /etc/grub.conf，修改default=0