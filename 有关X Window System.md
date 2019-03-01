# 有关X Window System

## TTY系统

![](/doc/TTY1.jpg)

* 真实终端，目前指鼠标、键盘、显示器等
* 虚拟终端-ttyn
  * ttyn<->真实终端，ttyn切换
* 伪终端-ptsn
  * ptsn(master)<->ttyn(slaver)

## 架构

![](https://www.x.org/wiki/guide/xorg.svg)

## 命令
    ps l    #查看所有tty情况，包括pts
    ps      #显示当前终端所持有的tty/pts及进程
    tty     #显示当前终端持有的tty/pts
    lsof /dev/ptmx  #显示打开ptmx设备文件的进程
    pstree -ps pid（Xorg）#显示(Xorg)父进程及其子进程关系
    stty


## 参考
1、[X_Window_System's Wiki](https://en.wikipedia.org/wiki/X_Window_System)