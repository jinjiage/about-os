# debian9

## 查看内核及版本信息
lsb_release
cat /etc/issue
cat /etc/debian_version
uname -r

## 安装xfce4
	apt-get install xfce4 xfce4-goodies #xfce4-goodies包含了很多xfce4-*的包
	update-alternatives --config x-session-manager #切换界面

## 设置apt源
添加/etc/apt/sources.list

	deb http://mirrors.163.com/debian/ stretch main contrib non-free
	deb http://mirrors.163.com/debian/ stretch-updates main contrib non-free
	deb http://mirrors.163.com/debian-security/ stretch/updates main contrib non-free
	deb http://mirrors.163/com/debian/ stretch-proposed-updates main contrib non-free

## 设置系统语言及字体
	aptitude install locales
	dpkg-reconfigure locales 进入选择： zh_CN.*, en_US.UTF8
	设置/etc/default/locale，LANG=en_US.UTF-8, LANGUAGE=zh_CN.UTF-8影响菜单、快捷图标
	#apt-get install ttf-arphic-uming 
	apt-get install xfonts-intl-chinese
	apt-get install xfonts-wqy
	apt-get install ttf-wqy-zenhei

## 安装输入法
	apt-get install scim 
	apt-get install scim-chinese 
	apt-get install scim-pinyin
	apt-get install ibus-table-wubi 

## 安装C语言开发包
	apt-get install build-essential

## 安装docker及工具
1. wget -qO- https://get.docker.com | sh #curl -fsSL https://get.docker.com/ | sh 或 curl -sSL https://get.daocloud.io/docker | sh
2. apt-get install docker-compose

