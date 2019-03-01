# debian9

## 查看内核及版本信息
lsb_release
cat /etc/issue
cat /etc/debian_version
uname -r

## 安装xfce4
	apt-get install xfce4 xfce4-goodies #xfce4-goodies包含了很多xfce4-*的包
	update-alternatives --config x-session-manager #切换界面

## [安装图形界面及xrdp远程登陆](http://c-nergy.be/blog/?p=5874)

## 设置apt源
添加/etc/apt/sources.list

	deb http://mirrors.163.com/debian/ stretch main non-free contrib
	deb http://mirrors.163.com/debian/ stretch-updates main non-free contrib
	deb http://mirrors.163.com/debian/ stretch-backports main non-free contrib
	deb-src http://mirrors.163.com/debian/ stretch main non-free contrib
	deb-src http://mirrors.163.com/debian/ stretch-updates main non-free contrib
	deb-src http://mirrors.163.com/debian/ stretch-backports main non-free contrib
	deb http://mirrors.163.com/debian-security/ stretch/updates main non-free contrib
	deb-src http://mirrors.163.com/debian-security/ stretch/updates main non-free contrib

## dpkg使用

## 添加第三方PPA
wget -qO- https://raw.githubusercontent.com/yejinlei/ppa/master/install.sh | sh  #debian没有add-apt-repository

## update-alternatives多版本管理

## 使用Zsh Shell
apt-get install zsh
chsh -s /bin/zsh
sh -c "$(wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)" #安装oh-my-zsh
apt-get install autoujump
echo '. /usr/share/autojump/autojump.sh' >> ~/.zshrc #激活autojump
source ~/.zshrc

## 设置系统语言及字体
	aptitude install locales
	dpkg-reconfigure locales 进入选择： zh_CN.*, en_US.UTF8
	设置/etc/default/locale，LANG=en_US.UTF-8, LANGUAGE=zh_CN.UTF-8影响菜单、快捷图标
	apt-get install fonts-arphic-uming 
	apt-get install xfonts-intl-chinese
	apt-get install xfonts-wqy
	apt-get install ttf-wqy-zenhei

## 安装输入法，详细参考http://wiki.ubuntu.org.cn/IBus
	apt-get install ibus ibus-pinyin ibus-sunpinyin
    ibus-setup #设置

## 安装C语言开发包
	apt-get install build-essential

## 安装docker及工具
	curl -sSL https://get.daocloud.io/docker
	apt-get install libssl-dev #如果出现curl ssl错误，可能要升级一下nss库
	apt-get install libcurl4-openssl-dev #如果数显Tls错误，可能要升级一下gnutls

    --------------------如果以上方法不行，请尝试以下方法-----------------------
	apt-get -y remove docker docker-engine docker.io
	apt-get update
	apt-get install -y apt-transport-https ca-certificates wget software-properties-common
	wget https://download.docker.com/linux/debian/gpg 
	apt-key add gpg
	echo "deb [arch=amd64] https://download.docker.com/linux/debian $(lsb_release -cs) stable" | tee -a /etc/apt/sources.list.d/docker.list
	apt-get update
	apt-cache policy docker-ce
	apt-get -y install docker-ce