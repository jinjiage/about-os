# 有关Qemu #

##qemu用户级仿真，能够运行那些为不同处理器编译的Linux程序

##qemu系统级仿真，仿真同构与非同构处理器及其他外部设备，运行完整的操作系统
	#配置阶段
	x86_cpu_common_class_init，★设置与x86 cpu相关的一系列函数，
		|dc->realize -> x86_cpu_realizefn，★初始化cpu
							|qemu_init_vcpu，☆
								|kvm_enabled,
								|tcg_enabled,
						
	#初始化阶段
	global：init_type_list数组，共4个元素MODULE_INIT_BLOCK、MODULE_INIT_OPTS、MODULE_INIT_QAPI、MODULE_INIT_QOM，每个元素代表不同类型对象或模块，每个元素挂接一个队列，队列中存放不同具体模块（qemu是一个oop，任何东西都是模块，包括非设备、选项、块设备、...）的初始化函数
	
	.init:通过4个宏block_init、opts_init、qapi_init、type_init把模块初始化函数注册到init_type_list数组中，等待后续调用。
		
	vl.c:main
			|
			|qemu_init_cpu_loop
				|qemu_init_sigbus,初始化qemu自身的信号
				|qemu_cond_init，初始化4个条件变量（qemu_cpu_cond、qemu_pause_cond、qemu_work_cond、qemu_io_proceeded_cond），用于控制qemu自身状态
				|qemu_mutex_init，初始化一个互斥量（qemu_global_mutex）
				|qemu_thread_get_self，设置一个线程函数（io_thread）
			
			|qemu_mutex_lock_iothread

			|module_call_init(MODULE_INIT_QOM)，module_call_init是调用模块初始化函数，此处对象模型初始化
				|其中一个是CPU模块初始化：x86_cpu_register_types
					type_register_static(&x86_cpu_type_info)，注册了x86 CPU类型，x86_cpu_type_info中包含了CPU各种特性，★如果设置了预编译宏CONFIG_KVM，则注册为host_x86_cpu_type_info；★不同type_info,其.class_init和.instance_init比较重要，对应不同函数 

			|module_call_init(MODULE_INIT_OPTS)，选项对象初始化

			|bdrv_init_with_whitelist
				|module_call_init(MODULE_INIT_BLOCK),调用块设备对象初始化

			|if defconfig=true，从userconfig加载默认参数到vm_config_groups中
			
			|for(;;){
				//根据参数，选择性初始化模块
				|kvm分支：case QEMU_OPTION_enable_kvm：
				
				|tcg分支：case QEMU_OPTION_no_kvm:

				|xen分支：case QEMU_OPTION_xen_domid
					
			 }

			|cpu_exec_init_all
				|io_mem_init，初始化IO端口
				
				|memory_map_init，初始化整个系统总线线性地址空间和io地址空间
					|申请并初始化了一块名为“system”的MemoryRegion，放到全局变量address_space_memory（代表线性地址空间）中
					|申请并初始化了一块名为“io”的MemoryRegion，address_space_io（代表io地址空间）中

			|socket_init，初始化qemu通信socket

			|machine_class->init(current_machine);

			|machine_usb，初始化usb设备

			|qemu_run_machine_init_done_notifiers
		
	#执行阶段
	qemu_tcg_cpu_thread_fn，线程
		|while(1)
			|tcg_exec_all
				|tcg_cpu_exec
					|cpu_exec，☆
						|CPU_GET_CLASS宏，获取cpu类型
						|tcg_current_cpu，设置全局
						|cc->cpu_exec_enter，调用多态函数，实际调用跟体系结构相关的函数，如果是x86，调用的是x86_cpu_exec_enter函数
						|for(;;)
							|tb_find_fast，查找指令
								|tb_find_slow，指令不在TB中，执行此处
									|translate-all.c:tb_gen_code，☆翻译指令
										|target-xxx\translate.c:gen_intermediate_code，★Guest Code -> TCG IR
										|tcg_gen_code，☆TCG IR -> Host Code
							|cpu_loop_exec_tb，执行指令
								|cpu_tb_exec
								|cpu_exec_nocache
									|tb_gen_code


##KVM半虚拟化
	#配置阶段
	kvm-all.c:kvm_accel_class_init，☆
		|ac->init_machine = kvm_init，
			|target-xxx\kvm.c:kvm_arch_init，★

	#执行阶段
	qemu_kvm_cpu_thread_fn，线程

##XEN半虚拟化
	#执行阶段
	qemu_kvm_cpu_thread_fn，线程

###pc_machine_info例子

	pc_machine_initfn
		DEFINE_I440FX_MACHINE
			|pc_init1
				|pc_memory_init，申请一块"pc.ram"的MemoryRegion，加载bios
				|pc_cmos_init，初始化cmos