# Linux虚拟内存系统 #

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