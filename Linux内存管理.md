# Linux内存管理 #
## Intel体系架构下内存规范

- 地址过程：逻辑地址--> 线性地址-->物理地址

![IA-32段页式模式](doc/IA-32段页式模式.PNG)

- 4个内存管理寄存器：GDTR、LDTR、IDTR和TR

## 内存管理各个阶段
### 启动阶段
### 解压内核阶段
### 运行阶段




	             CPU                  CPU                  Bus
	           Virtual              Physical             Address
	           Address              Address               Space
	            Space                Space
	
	          +-------+             +------+             +------+
	          |       |             |MMIO  |   Offset    |      |
	          |       |  Virtual    |Space |   applied   |      |
	        C +-------+ --------> B +------+ ----------> +------+ A
	          |       |  mapping    |      |   by host   |      |
	+-----+   |       |             |      |   bridge    |      |   +--------+
	|     |   |       |             +------+             |      |   |        |
	| CPU |   |       |             | RAM  |             |      |   | Device |
	|     |   |       |             |      |             |      |   |        |
	+-----+   +-------+             +------+             +------+   +--------+
	          |       |  Virtual    |Buffer|   Mapping   |      |
	        X +-------+ --------> Y +------+ <---------- +------+ Z
	          |       |  mapping    | RAM  |   by IOMMU
	          |       |             |      |
	          |       |             |      |
	          +-------+             +------+
## 概念 ##
### node节点 ###

	typedef struct pglist_data {

### zone内存域 ###

	struct zone {

## 进程地址空间 ##

## 分配非连续内存块vmalloc机制 ##

## slub分配器 ##

## slob分配器 ##

## slab分配器 ##
### kmem_cache_create，创建slab对象 ###
### kmem_cache_alloc，申请 ###
### kmem_cache_free，释放 ###

## 伙伴系统分配 ##
### alloc_pages，申请页面返回页面地址 ###
### page_address，页面地址转内存地址 ###

## swap交换区 ##
1. 内核中涉及swap交换区的数据结构struct swap\_info\_struct *swap\_info[MAX_SWAPFILES]; //MAX_SWAPFILES大致为32

## glibc内存管理（用户空间）

## 资料
http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/