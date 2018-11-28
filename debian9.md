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

## 设置中文界面及输入法
1. aptitude install locales
1. dpkg-reconfigure locales 进入选择： zh_CN GB2312 zh_CN.GBK GBK ;zh_CN.UTF-8 UTF-8  ; en_US.UF8
1. 设置/etc/default/locale，LANG=en_US.UTF-8
1. apt-get install ttf-arphic-uming 
1. apt-get install xfonts-intl-chinese
1. apt-get install xfonts-wqy
1. apt-get install ttf-wqy-zenhei
1. apt-get install scim 
1. apt-get install scim-chinese 
1. apt-get install scim-pinyin
1. apt-get install ibus-table-wubi 
2

## 安装docker及工具
1. wget -qO- https://get.docker.com | sh
2. apt-get install docker-compose

