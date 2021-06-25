<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2012
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com),
 *               Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "arch/i386/kernel/setup.c"
 *    Copyright (C) 1995, Linus Torvalds
 */

/*
 * This file handles the architecture-dependent parts of initialization
 */

#घोषणा KMSG_COMPONENT "setup"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/user.h>
#समावेश <linux/tty.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/console.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pfn.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/reboot.h>
#समावेश <linux/topology.h>
#समावेश <linux/kexec.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/memory.h>
#समावेश <linux/compat.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/boot_data.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/os_info.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/mem_detect.h>
#समावेश <यंत्र/uv.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश "entry.h"

/*
 * Machine setup..
 */
अचिन्हित पूर्णांक console_mode = 0;
EXPORT_SYMBOL(console_mode);

अचिन्हित पूर्णांक console_devno = -1;
EXPORT_SYMBOL(console_devno);

अचिन्हित पूर्णांक console_irq = -1;
EXPORT_SYMBOL(console_irq);

अचिन्हित दीर्घ elf_hwcap __पढ़ो_mostly = 0;
अक्षर elf_platक्रमm[ELF_PLATFORM_SIZE];

अचिन्हित दीर्घ पूर्णांक_hwcap = 0;

पूर्णांक __bootdata(noexec_disabled);
अचिन्हित दीर्घ __bootdata(ident_map_size);
अचिन्हित दीर्घ __bootdata(vदो_स्मृति_size);
काष्ठा mem_detect_info __bootdata(mem_detect);

काष्ठा exception_table_entry *__bootdata_preserved(__start_dma_ex_table);
काष्ठा exception_table_entry *__bootdata_preserved(__stop_dma_ex_table);
अचिन्हित दीर्घ __bootdata_preserved(__stext_dma);
अचिन्हित दीर्घ __bootdata_preserved(__etext_dma);
अचिन्हित दीर्घ __bootdata_preserved(__sdma);
अचिन्हित दीर्घ __bootdata_preserved(__edma);
अचिन्हित दीर्घ __bootdata_preserved(__kaslr_offset);
अचिन्हित पूर्णांक __bootdata_preserved(zlib_dfltcc_support);
EXPORT_SYMBOL(zlib_dfltcc_support);

अचिन्हित दीर्घ VMALLOC_START;
EXPORT_SYMBOL(VMALLOC_START);

अचिन्हित दीर्घ VMALLOC_END;
EXPORT_SYMBOL(VMALLOC_END);

काष्ठा page *vmemmap;
EXPORT_SYMBOL(vmemmap);
अचिन्हित दीर्घ vmemmap_size;

अचिन्हित दीर्घ MODULES_VADDR;
अचिन्हित दीर्घ MODULES_END;

/* An array with a poपूर्णांकer to the lowcore of every CPU. */
काष्ठा lowcore *lowcore_ptr[NR_CPUS];
EXPORT_SYMBOL(lowcore_ptr);

/*
 * The Write Back bit position in the physaddr is given by the SLPC PCI.
 * Leaving the mask zero always uses ग_लिखो through which is safe
 */
अचिन्हित दीर्घ mio_wb_bit_mask __ro_after_init;

/*
 * This is set up by the setup-routine at boot-समय
 * क्रम S390 need to find out, what we have to setup
 * using address 0x10400 ...
 */

#समावेश <यंत्र/setup.h>

/*
 * condev= and conmode= setup parameter.
 */

अटल पूर्णांक __init condev_setup(अक्षर *str)
अणु
	पूर्णांक vdev;

	vdev = simple_म_से_अदीर्घ(str, &str, 0);
	अगर (vdev >= 0 && vdev < 65536) अणु
		console_devno = vdev;
		console_irq = -1;
	पूर्ण
	वापस 1;
पूर्ण

__setup("condev=", condev_setup);

अटल व्योम __init set_preferred_console(व्योम)
अणु
	अगर (CONSOLE_IS_3215 || CONSOLE_IS_SCLP)
		add_preferred_console("ttyS", 0, शून्य);
	अन्यथा अगर (CONSOLE_IS_3270)
		add_preferred_console("tty3270", 0, शून्य);
	अन्यथा अगर (CONSOLE_IS_VT220)
		add_preferred_console("ttyS", 1, शून्य);
	अन्यथा अगर (CONSOLE_IS_HVC)
		add_preferred_console("hvc", 0, शून्य);
पूर्ण

अटल पूर्णांक __init conmode_setup(अक्षर *str)
अणु
#अगर defined(CONFIG_SCLP_CONSOLE) || defined(CONFIG_SCLP_VT220_CONSOLE)
	अगर (!म_भेद(str, "hwc") || !म_भेद(str, "sclp"))
                SET_CONSOLE_SCLP;
#पूर्ण_अगर
#अगर defined(CONFIG_TN3215_CONSOLE)
	अगर (!म_भेद(str, "3215"))
		SET_CONSOLE_3215;
#पूर्ण_अगर
#अगर defined(CONFIG_TN3270_CONSOLE)
	अगर (!म_भेद(str, "3270"))
		SET_CONSOLE_3270;
#पूर्ण_अगर
	set_preferred_console();
        वापस 1;
पूर्ण

__setup("conmode=", conmode_setup);

अटल व्योम __init conmode_शेष(व्योम)
अणु
	अक्षर query_buffer[1024];
	अक्षर *ptr;

        अगर (MACHINE_IS_VM) अणु
		cpcmd("QUERY CONSOLE", query_buffer, 1024, शून्य);
		console_devno = simple_म_से_अदीर्घ(query_buffer + 5, शून्य, 16);
		ptr = म_माला(query_buffer, "SUBCHANNEL =");
		console_irq = simple_म_से_अदीर्घ(ptr + 13, शून्य, 16);
		cpcmd("QUERY TERM", query_buffer, 1024, शून्य);
		ptr = म_माला(query_buffer, "CONMODE");
		/*
		 * Set the conmode to 3215 so that the device recognition 
		 * will set the cu_type of the console to 3215. If the
		 * conmode is 3270 and we करोn't set it back then both
		 * 3215 and the 3270 driver will try to access the console
		 * device (3215 as console and 3270 as normal tty).
		 */
		cpcmd("TERM CONMODE 3215", शून्य, 0, शून्य);
		अगर (ptr == शून्य) अणु
#अगर defined(CONFIG_SCLP_CONSOLE) || defined(CONFIG_SCLP_VT220_CONSOLE)
			SET_CONSOLE_SCLP;
#पूर्ण_अगर
			वापस;
		पूर्ण
		अगर (str_has_prefix(ptr + 8, "3270")) अणु
#अगर defined(CONFIG_TN3270_CONSOLE)
			SET_CONSOLE_3270;
#या_अगर defined(CONFIG_TN3215_CONSOLE)
			SET_CONSOLE_3215;
#या_अगर defined(CONFIG_SCLP_CONSOLE) || defined(CONFIG_SCLP_VT220_CONSOLE)
			SET_CONSOLE_SCLP;
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (str_has_prefix(ptr + 8, "3215")) अणु
#अगर defined(CONFIG_TN3215_CONSOLE)
			SET_CONSOLE_3215;
#या_अगर defined(CONFIG_TN3270_CONSOLE)
			SET_CONSOLE_3270;
#या_अगर defined(CONFIG_SCLP_CONSOLE) || defined(CONFIG_SCLP_VT220_CONSOLE)
			SET_CONSOLE_SCLP;
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अगर (MACHINE_IS_KVM) अणु
		अगर (sclp.has_vt220 && IS_ENABLED(CONFIG_SCLP_VT220_CONSOLE))
			SET_CONSOLE_VT220;
		अन्यथा अगर (sclp.has_linemode && IS_ENABLED(CONFIG_SCLP_CONSOLE))
			SET_CONSOLE_SCLP;
		अन्यथा
			SET_CONSOLE_HVC;
	पूर्ण अन्यथा अणु
#अगर defined(CONFIG_SCLP_CONSOLE) || defined(CONFIG_SCLP_VT220_CONSOLE)
		SET_CONSOLE_SCLP;
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CRASH_DUMP
अटल व्योम __init setup_zfcpdump(व्योम)
अणु
	अगर (!is_ipl_type_dump())
		वापस;
	अगर (OLDMEM_BASE)
		वापस;
	म_जोड़ो(boot_command_line, " cio_ignore=all,!ipldev,!condev");
	console_loglevel = 2;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम setup_zfcpdump(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

 /*
 * Reboot, halt and घातer_off stubs. They just call _machine_restart,
 * _machine_halt or _machine_घातer_off. 
 */

व्योम machine_restart(अक्षर *command)
अणु
	अगर ((!in_पूर्णांकerrupt() && !in_atomic()) || oops_in_progress)
		/*
		 * Only unblank the console अगर we are called in enabled
		 * context or a bust_spinlocks cleared the way क्रम us.
		 */
		console_unblank();
	_machine_restart(command);
पूर्ण

व्योम machine_halt(व्योम)
अणु
	अगर (!in_पूर्णांकerrupt() || oops_in_progress)
		/*
		 * Only unblank the console अगर we are called in enabled
		 * context or a bust_spinlocks cleared the way क्रम us.
		 */
		console_unblank();
	_machine_halt();
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	अगर (!in_पूर्णांकerrupt() || oops_in_progress)
		/*
		 * Only unblank the console अगर we are called in enabled
		 * context or a bust_spinlocks cleared the way क्रम us.
		 */
		console_unblank();
	_machine_घातer_off();
पूर्ण

/*
 * Dummy घातer off function.
 */
व्योम (*pm_घातer_off)(व्योम) = machine_घातer_off;
EXPORT_SYMBOL_GPL(pm_घातer_off);

व्योम *restart_stack;

अचिन्हित दीर्घ stack_alloc(व्योम)
अणु
#अगर_घोषित CONFIG_VMAP_STACK
	वापस (अचिन्हित दीर्घ)__vदो_स्मृति_node(THREAD_SIZE, THREAD_SIZE,
			THREADINFO_GFP, NUMA_NO_NODE,
			__builtin_वापस_address(0));
#अन्यथा
	वापस __get_मुक्त_pages(GFP_KERNEL, THREAD_SIZE_ORDER);
#पूर्ण_अगर
पूर्ण

व्योम stack_मुक्त(अचिन्हित दीर्घ stack)
अणु
#अगर_घोषित CONFIG_VMAP_STACK
	vमुक्त((व्योम *) stack);
#अन्यथा
	मुक्त_pages(stack, THREAD_SIZE_ORDER);
#पूर्ण_अगर
पूर्ण

पूर्णांक __init arch_early_irq_init(व्योम)
अणु
	अचिन्हित दीर्घ stack;

	stack = __get_मुक्त_pages(GFP_KERNEL, THREAD_SIZE_ORDER);
	अगर (!stack)
		panic("Couldn't allocate async stack");
	S390_lowcore.async_stack = stack + STACK_INIT_OFFSET;
	वापस 0;
पूर्ण

अटल पूर्णांक __init stack_पुनः_स्मृति(व्योम)
अणु
	अचिन्हित दीर्घ old, new;

	old = S390_lowcore.async_stack - STACK_INIT_OFFSET;
	new = stack_alloc();
	अगर (!new)
		panic("Couldn't allocate async stack");
	WRITE_ONCE(S390_lowcore.async_stack, new + STACK_INIT_OFFSET);
	मुक्त_pages(old, THREAD_SIZE_ORDER);

	old = S390_lowcore.mcck_stack - STACK_INIT_OFFSET;
	new = stack_alloc();
	अगर (!new)
		panic("Couldn't allocate machine check stack");
	WRITE_ONCE(S390_lowcore.mcck_stack, new + STACK_INIT_OFFSET);
	memblock_मुक्त_late(old, THREAD_SIZE);
	वापस 0;
पूर्ण
early_initcall(stack_पुनः_स्मृति);

व्योम __init arch_call_rest_init(व्योम)
अणु
	अचिन्हित दीर्घ stack;

	stack = stack_alloc();
	अगर (!stack)
		panic("Couldn't allocate kernel stack");
	current->stack = (व्योम *) stack;
#अगर_घोषित CONFIG_VMAP_STACK
	current->stack_vm_area = (व्योम *) stack;
#पूर्ण_अगर
	set_task_stack_end_magic(current);
	stack += STACK_INIT_OFFSET;
	S390_lowcore.kernel_stack = stack;
	CALL_ON_STACK_NORETURN(rest_init, stack);
पूर्ण

अटल व्योम __init setup_lowcore_dat_off(व्योम)
अणु
	अचिन्हित दीर्घ पूर्णांक_psw_mask = PSW_KERNEL_BITS;
	अचिन्हित दीर्घ mcck_stack;
	काष्ठा lowcore *lc;

	अगर (IS_ENABLED(CONFIG_KASAN))
		पूर्णांक_psw_mask |= PSW_MASK_DAT;

	/*
	 * Setup lowcore क्रम boot cpu
	 */
	BUILD_BUG_ON(माप(काष्ठा lowcore) != LC_PAGES * PAGE_SIZE);
	lc = memblock_alloc_low(माप(*lc), माप(*lc));
	अगर (!lc)
		panic("%s: Failed to allocate %zu bytes align=%zx\n",
		      __func__, माप(*lc), माप(*lc));

	lc->restart_psw.mask = PSW_KERNEL_BITS;
	lc->restart_psw.addr = (अचिन्हित दीर्घ) restart_पूर्णांक_handler;
	lc->बाह्यal_new_psw.mask = पूर्णांक_psw_mask | PSW_MASK_MCHECK;
	lc->बाह्यal_new_psw.addr = (अचिन्हित दीर्घ) ext_पूर्णांक_handler;
	lc->svc_new_psw.mask = पूर्णांक_psw_mask | PSW_MASK_MCHECK;
	lc->svc_new_psw.addr = (अचिन्हित दीर्घ) प्रणाली_call;
	lc->program_new_psw.mask = पूर्णांक_psw_mask | PSW_MASK_MCHECK;
	lc->program_new_psw.addr = (अचिन्हित दीर्घ) pgm_check_handler;
	lc->mcck_new_psw.mask = PSW_KERNEL_BITS;
	lc->mcck_new_psw.addr = (अचिन्हित दीर्घ) mcck_पूर्णांक_handler;
	lc->io_new_psw.mask = पूर्णांक_psw_mask | PSW_MASK_MCHECK;
	lc->io_new_psw.addr = (अचिन्हित दीर्घ) io_पूर्णांक_handler;
	lc->घड़ी_comparator = घड़ी_comparator_max;
	lc->nodat_stack = ((अचिन्हित दीर्घ) &init_thपढ़ो_जोड़)
		+ THREAD_SIZE - STACK_FRAME_OVERHEAD - माप(काष्ठा pt_regs);
	lc->current_task = (अचिन्हित दीर्घ)&init_task;
	lc->lpp = LPP_MAGIC;
	lc->machine_flags = S390_lowcore.machine_flags;
	lc->preempt_count = S390_lowcore.preempt_count;
	lc->stfl_fac_list = S390_lowcore.stfl_fac_list;
	स_नकल(lc->stfle_fac_list, S390_lowcore.stfle_fac_list,
	       माप(lc->stfle_fac_list));
	स_नकल(lc->alt_stfle_fac_list, S390_lowcore.alt_stfle_fac_list,
	       माप(lc->alt_stfle_fac_list));
	nmi_alloc_boot_cpu(lc);
	lc->sys_enter_समयr = S390_lowcore.sys_enter_समयr;
	lc->निकास_समयr = S390_lowcore.निकास_समयr;
	lc->user_समयr = S390_lowcore.user_समयr;
	lc->प्रणाली_समयr = S390_lowcore.प्रणाली_समयr;
	lc->steal_समयr = S390_lowcore.steal_समयr;
	lc->last_update_समयr = S390_lowcore.last_update_समयr;
	lc->last_update_घड़ी = S390_lowcore.last_update_घड़ी;

	/*
	 * Allocate the global restart stack which is the same क्रम
	 * all CPUs in cast *one* of them करोes a PSW restart.
	 */
	restart_stack = memblock_alloc(THREAD_SIZE, THREAD_SIZE);
	अगर (!restart_stack)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, THREAD_SIZE, THREAD_SIZE);
	restart_stack += STACK_INIT_OFFSET;

	/*
	 * Set up PSW restart to call ipl.c:करो_restart(). Copy the relevant
	 * restart data to the असलolute zero lowcore. This is necessary अगर
	 * PSW restart is करोne on an offline CPU that has lowcore zero.
	 */
	lc->restart_stack = (अचिन्हित दीर्घ) restart_stack;
	lc->restart_fn = (अचिन्हित दीर्घ) करो_restart;
	lc->restart_data = 0;
	lc->restart_source = -1UL;

	mcck_stack = (अचिन्हित दीर्घ)memblock_alloc(THREAD_SIZE, THREAD_SIZE);
	अगर (!mcck_stack)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, THREAD_SIZE, THREAD_SIZE);
	lc->mcck_stack = mcck_stack + STACK_INIT_OFFSET;

	/* Setup असलolute zero lowcore */
	mem_assign_असलolute(S390_lowcore.restart_stack, lc->restart_stack);
	mem_assign_असलolute(S390_lowcore.restart_fn, lc->restart_fn);
	mem_assign_असलolute(S390_lowcore.restart_data, lc->restart_data);
	mem_assign_असलolute(S390_lowcore.restart_source, lc->restart_source);
	mem_assign_असलolute(S390_lowcore.restart_psw, lc->restart_psw);

	lc->spinlock_lockval = arch_spin_lockval(0);
	lc->spinlock_index = 0;
	arch_spin_lock_setup(0);
	lc->br_r1_trampoline = 0x07f1;	/* br %r1 */
	lc->वापस_lpswe = gen_lpswe(__LC_RETURN_PSW);
	lc->वापस_mcck_lpswe = gen_lpswe(__LC_RETURN_MCCK_PSW);

	set_prefix((u32)(अचिन्हित दीर्घ) lc);
	lowcore_ptr[0] = lc;
पूर्ण

अटल व्योम __init setup_lowcore_dat_on(व्योम)
अणु
	__ctl_clear_bit(0, 28);
	S390_lowcore.बाह्यal_new_psw.mask |= PSW_MASK_DAT;
	S390_lowcore.svc_new_psw.mask |= PSW_MASK_DAT;
	S390_lowcore.program_new_psw.mask |= PSW_MASK_DAT;
	S390_lowcore.io_new_psw.mask |= PSW_MASK_DAT;
	__ctl_set_bit(0, 28);
पूर्ण

अटल काष्ठा resource code_resource = अणु
	.name  = "Kernel code",
	.flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अटल काष्ठा resource data_resource = अणु
	.name = "Kernel data",
	.flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अटल काष्ठा resource bss_resource = अणु
	.name = "Kernel bss",
	.flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM,
पूर्ण;

अटल काष्ठा resource __initdata *standard_resources[] = अणु
	&code_resource,
	&data_resource,
	&bss_resource,
पूर्ण;

अटल व्योम __init setup_resources(व्योम)
अणु
	काष्ठा resource *res, *std_res, *sub_res;
	phys_addr_t start, end;
	पूर्णांक j;
	u64 i;

	code_resource.start = (अचिन्हित दीर्घ) _text;
	code_resource.end = (अचिन्हित दीर्घ) _etext - 1;
	data_resource.start = (अचिन्हित दीर्घ) _etext;
	data_resource.end = (अचिन्हित दीर्घ) _edata - 1;
	bss_resource.start = (अचिन्हित दीर्घ) __bss_start;
	bss_resource.end = (अचिन्हित दीर्घ) __bss_stop - 1;

	क्रम_each_mem_range(i, &start, &end) अणु
		res = memblock_alloc(माप(*res), 8);
		अगर (!res)
			panic("%s: Failed to allocate %zu bytes align=0x%x\n",
			      __func__, माप(*res), 8);
		res->flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM;

		res->name = "System RAM";
		res->start = start;
		/*
		 * In memblock, end poपूर्णांकs to the first byte after the
		 * range जबतक in resourses, end poपूर्णांकs to the last byte in
		 * the range.
		 */
		res->end = end - 1;
		request_resource(&iomem_resource, res);

		क्रम (j = 0; j < ARRAY_SIZE(standard_resources); j++) अणु
			std_res = standard_resources[j];
			अगर (std_res->start < res->start ||
			    std_res->start > res->end)
				जारी;
			अगर (std_res->end > res->end) अणु
				sub_res = memblock_alloc(माप(*sub_res), 8);
				अगर (!sub_res)
					panic("%s: Failed to allocate %zu bytes align=0x%x\n",
					      __func__, माप(*sub_res), 8);
				*sub_res = *std_res;
				sub_res->end = res->end;
				std_res->start = res->end + 1;
				request_resource(res, sub_res);
			पूर्ण अन्यथा अणु
				request_resource(res, std_res);
			पूर्ण
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_CRASH_DUMP
	/*
	 * Re-add हटाओd crash kernel memory as reserved memory. This makes
	 * sure it will be mapped with the identity mapping and काष्ठा pages
	 * will be created, so it can be resized later on.
	 * However add it later since the crash kernel resource should not be
	 * part of the System RAM resource.
	 */
	अगर (crashk_res.end) अणु
		memblock_add_node(crashk_res.start, resource_size(&crashk_res), 0);
		memblock_reserve(crashk_res.start, resource_size(&crashk_res));
		insert_resource(&iomem_resource, &crashk_res);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init setup_ident_map_size(व्योम)
अणु
	अचिन्हित दीर्घ vmax, पंचांगp;

	/* Choose kernel address space layout: 3 or 4 levels. */
	पंचांगp = ident_map_size / PAGE_SIZE;
	पंचांगp = पंचांगp * (माप(काष्ठा page) + PAGE_SIZE);
	अगर (पंचांगp + vदो_स्मृति_size + MODULES_LEN <= _REGION2_SIZE)
		vmax = _REGION2_SIZE; /* 3-level kernel page table */
	अन्यथा
		vmax = _REGION1_SIZE; /* 4-level kernel page table */
	/* module area is at the end of the kernel address space. */
	MODULES_END = vmax;
	अगर (is_prot_virt_host())
		adjust_to_uv_max(&MODULES_END);
#अगर_घोषित CONFIG_KASAN
	vmax = _REGION1_SIZE;
	MODULES_END = kasan_vmax;
#पूर्ण_अगर
	MODULES_VADDR = MODULES_END - MODULES_LEN;
	VMALLOC_END = MODULES_VADDR;
	VMALLOC_START = VMALLOC_END - vदो_स्मृति_size;

	/* Split reमुख्यing भव space between 1:1 mapping & vmemmap array */
	पंचांगp = VMALLOC_START / (PAGE_SIZE + माप(काष्ठा page));
	/* vmemmap contains a multiple of PAGES_PER_SECTION काष्ठा pages */
	पंचांगp = SECTION_ALIGN_UP(पंचांगp);
	पंचांगp = VMALLOC_START - पंचांगp * माप(काष्ठा page);
	पंचांगp &= ~((vmax >> 11) - 1);	/* align to page table level */
	पंचांगp = min(पंचांगp, 1UL << MAX_PHYSMEM_BITS);
	vmemmap = (काष्ठा page *) पंचांगp;

	/* Take care that ident_map_size <= vmemmap */
	ident_map_size = min(ident_map_size, (अचिन्हित दीर्घ)vmemmap);
#अगर_घोषित CONFIG_KASAN
	ident_map_size = min(ident_map_size, KASAN_SHADOW_START);
#पूर्ण_अगर
	vmemmap_size = SECTION_ALIGN_UP(ident_map_size / PAGE_SIZE) * माप(काष्ठा page);
#अगर_घोषित CONFIG_KASAN
	/* move vmemmap above kasan shaकरोw only अगर stands in a way */
	अगर (KASAN_SHADOW_END > (अचिन्हित दीर्घ)vmemmap &&
	    (अचिन्हित दीर्घ)vmemmap + vmemmap_size > KASAN_SHADOW_START)
		vmemmap = max(vmemmap, (काष्ठा page *)KASAN_SHADOW_END);
#पूर्ण_अगर
	max_pfn = max_low_pfn = PFN_DOWN(ident_map_size);
	memblock_हटाओ(ident_map_size, अच_दीर्घ_उच्च);

	pr_notice("The maximum memory size is %luMB\n", ident_map_size >> 20);
पूर्ण

#अगर_घोषित CONFIG_CRASH_DUMP

/*
 * When kdump is enabled, we have to ensure that no memory from the area
 * [0 - crashkernel memory size] is set offline - it will be exchanged with
 * the crashkernel memory region when kdump is triggered. The crashkernel
 * memory region can never get offlined (pages are unmovable).
 */
अटल पूर्णांक kdump_mem_notअगरier(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा memory_notअगरy *arg = data;

	अगर (action != MEM_GOING_OFFLINE)
		वापस NOTIFY_OK;
	अगर (arg->start_pfn < PFN_DOWN(resource_size(&crashk_res)))
		वापस NOTIFY_BAD;
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block kdump_mem_nb = अणु
	.notअगरier_call = kdump_mem_notअगरier,
पूर्ण;

#पूर्ण_अगर

/*
 * Make sure that the area above identity mapping is रक्षित
 */
अटल व्योम __init reserve_above_ident_map(व्योम)
अणु
	memblock_reserve(ident_map_size, अच_दीर्घ_उच्च);
पूर्ण

/*
 * Make sure that oldmem, where the dump is stored, is रक्षित
 */
अटल व्योम __init reserve_oldmem(व्योम)
अणु
#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (OLDMEM_BASE)
		/* Forget all memory above the running kdump प्रणाली */
		memblock_reserve(OLDMEM_SIZE, (phys_addr_t)अच_दीर्घ_उच्च);
#पूर्ण_अगर
पूर्ण

/*
 * Make sure that oldmem, where the dump is stored, is रक्षित
 */
अटल व्योम __init हटाओ_oldmem(व्योम)
अणु
#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (OLDMEM_BASE)
		/* Forget all memory above the running kdump प्रणाली */
		memblock_हटाओ(OLDMEM_SIZE, (phys_addr_t)अच_दीर्घ_उच्च);
#पूर्ण_अगर
पूर्ण

/*
 * Reserve memory क्रम kdump kernel to be loaded with kexec
 */
अटल व्योम __init reserve_crashkernel(व्योम)
अणु
#अगर_घोषित CONFIG_CRASH_DUMP
	अचिन्हित दीर्घ दीर्घ crash_base, crash_size;
	phys_addr_t low, high;
	पूर्णांक rc;

	rc = parse_crashkernel(boot_command_line, ident_map_size, &crash_size,
			       &crash_base);

	crash_base = ALIGN(crash_base, KEXEC_CRASH_MEM_ALIGN);
	crash_size = ALIGN(crash_size, KEXEC_CRASH_MEM_ALIGN);
	अगर (rc || crash_size == 0)
		वापस;

	अगर (memblock.memory.regions[0].size < crash_size) अणु
		pr_info("crashkernel reservation failed: %s\n",
			"first memory chunk must be at least crashkernel size");
		वापस;
	पूर्ण

	low = crash_base ?: OLDMEM_BASE;
	high = low + crash_size;
	अगर (low >= OLDMEM_BASE && high <= OLDMEM_BASE + OLDMEM_SIZE) अणु
		/* The crashkernel fits पूर्णांकo OLDMEM, reuse OLDMEM */
		crash_base = low;
	पूर्ण अन्यथा अणु
		/* Find suitable area in मुक्त memory */
		low = max_t(अचिन्हित दीर्घ, crash_size, sclp.hsa_size);
		high = crash_base ? crash_base + crash_size : अच_दीर्घ_उच्च;

		अगर (crash_base && crash_base < low) अणु
			pr_info("crashkernel reservation failed: %s\n",
				"crash_base too low");
			वापस;
		पूर्ण
		low = crash_base ?: low;
		crash_base = memblock_find_in_range(low, high, crash_size,
						    KEXEC_CRASH_MEM_ALIGN);
	पूर्ण

	अगर (!crash_base) अणु
		pr_info("crashkernel reservation failed: %s\n",
			"no suitable area found");
		वापस;
	पूर्ण

	अगर (रेजिस्टर_memory_notअगरier(&kdump_mem_nb))
		वापस;

	अगर (!OLDMEM_BASE && MACHINE_IS_VM)
		diag10_range(PFN_DOWN(crash_base), PFN_DOWN(crash_size));
	crashk_res.start = crash_base;
	crashk_res.end = crash_base + crash_size - 1;
	memblock_हटाओ(crash_base, crash_size);
	pr_info("Reserving %lluMB of memory at %lluMB "
		"for crashkernel (System RAM: %luMB)\n",
		crash_size >> 20, crash_base >> 20,
		(अचिन्हित दीर्घ)memblock.memory.total_size >> 20);
	os_info_crashkernel_add(crash_base, crash_size);
#पूर्ण_अगर
पूर्ण

/*
 * Reserve the initrd from being used by memblock
 */
अटल व्योम __init reserve_initrd(व्योम)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (!INITRD_START || !INITRD_SIZE)
		वापस;
	initrd_start = INITRD_START;
	initrd_end = initrd_start + INITRD_SIZE;
	memblock_reserve(INITRD_START, INITRD_SIZE);
#पूर्ण_अगर
पूर्ण

/*
 * Reserve the memory area used to pass the certअगरicate lists
 */
अटल व्योम __init reserve_certअगरicate_list(व्योम)
अणु
	अगर (ipl_cert_list_addr)
		memblock_reserve(ipl_cert_list_addr, ipl_cert_list_size);
पूर्ण

अटल व्योम __init reserve_mem_detect_info(व्योम)
अणु
	अचिन्हित दीर्घ start, size;

	get_mem_detect_reserved(&start, &size);
	अगर (size)
		memblock_reserve(start, size);
पूर्ण

अटल व्योम __init मुक्त_mem_detect_info(व्योम)
अणु
	अचिन्हित दीर्घ start, size;

	get_mem_detect_reserved(&start, &size);
	अगर (size)
		memblock_मुक्त(start, size);
पूर्ण

अटल स्थिर अक्षर * __init get_mem_info_source(व्योम)
अणु
	चयन (mem_detect.info_source) अणु
	हाल MEM_DETECT_SCLP_STOR_INFO:
		वापस "sclp storage info";
	हाल MEM_DETECT_DIAG260:
		वापस "diag260";
	हाल MEM_DETECT_SCLP_READ_INFO:
		वापस "sclp read info";
	हाल MEM_DETECT_BIN_SEARCH:
		वापस "binary search";
	पूर्ण
	वापस "none";
पूर्ण

अटल व्योम __init memblock_add_mem_detect_info(व्योम)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक i;

	pr_debug("physmem info source: %s (%hhd)\n",
		 get_mem_info_source(), mem_detect.info_source);
	/* keep memblock lists बंद to the kernel */
	memblock_set_bottom_up(true);
	क्रम_each_mem_detect_block(i, &start, &end) अणु
		memblock_add(start, end - start);
		memblock_physmem_add(start, end - start);
	पूर्ण
	memblock_set_bottom_up(false);
	memblock_set_node(0, अच_दीर्घ_उच्च, &memblock.memory, 0);
	memblock_dump_all();
पूर्ण

/*
 * Check क्रम initrd being in usable memory
 */
अटल व्योम __init check_initrd(व्योम)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (INITRD_START && INITRD_SIZE &&
	    !memblock_is_region_memory(INITRD_START, INITRD_SIZE)) अणु
		pr_err("The initial RAM disk does not fit into the memory\n");
		memblock_मुक्त(INITRD_START, INITRD_SIZE);
		initrd_start = initrd_end = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Reserve memory used क्रम lowcore/command line/kernel image.
 */
अटल व्योम __init reserve_kernel(व्योम)
अणु
	अचिन्हित दीर्घ start_pfn = PFN_UP(__pa(_end));

	memblock_reserve(0, HEAD_END);
	memblock_reserve((अचिन्हित दीर्घ)_stext, PFN_PHYS(start_pfn)
			 - (अचिन्हित दीर्घ)_stext);
	memblock_reserve(__sdma, __edma - __sdma);
पूर्ण

अटल व्योम __init setup_memory(व्योम)
अणु
	phys_addr_t start, end;
	u64 i;

	/*
	 * Init storage key क्रम present memory
	 */
	क्रम_each_mem_range(i, &start, &end)
		storage_key_init_range(start, end);

	psw_set_key(PAGE_DEFAULT_KEY);

	/* Only cosmetics */
	memblock_enक्रमce_memory_limit(memblock_end_of_DRAM());
पूर्ण

/*
 * Setup hardware capabilities.
 */
अटल पूर्णांक __init setup_hwcaps(व्योम)
अणु
	अटल स्थिर पूर्णांक stfl_bits[6] = अणु 0, 2, 7, 17, 19, 21 पूर्ण;
	काष्ठा cpuid cpu_id;
	पूर्णांक i;

	/*
	 * The store facility list bits numbers as found in the principles
	 * of operation are numbered with bit 1UL<<31 as number 0 to
	 * bit 1UL<<0 as number 31.
	 *   Bit 0: inकाष्ठाions named N3, "backported" to esa-mode
	 *   Bit 2: z/Architecture mode is active
	 *   Bit 7: the store-facility-list-extended facility is installed
	 *   Bit 17: the message-security assist is installed
	 *   Bit 19: the दीर्घ-displacement facility is installed
	 *   Bit 21: the extended-immediate facility is installed
	 *   Bit 22: extended-translation facility 3 is installed
	 *   Bit 30: extended-translation facility 3 enhancement facility
	 * These get translated to:
	 *   HWCAP_S390_ESAN3 bit 0, HWCAP_S390_ZARCH bit 1,
	 *   HWCAP_S390_STFLE bit 2, HWCAP_S390_MSA bit 3,
	 *   HWCAP_S390_LDISP bit 4, HWCAP_S390_EIMM bit 5 and
	 *   HWCAP_S390_ETF3EH bit 8 (22 && 30).
	 */
	क्रम (i = 0; i < 6; i++)
		अगर (test_facility(stfl_bits[i]))
			elf_hwcap |= 1UL << i;

	अगर (test_facility(22) && test_facility(30))
		elf_hwcap |= HWCAP_S390_ETF3EH;

	/*
	 * Check क्रम additional facilities with store-facility-list-extended.
	 * stfle stores द्विगुनwords (8 byte) with bit 1ULL<<63 as bit 0
	 * and 1ULL<<0 as bit 63. Bits 0-31 contain the same inक्रमmation
	 * as stored by stfl, bits 32-xxx contain additional facilities.
	 * How many facility words are stored depends on the number of
	 * द्विगुनwords passed to the inकाष्ठाion. The additional facilities
	 * are:
	 *   Bit 42: decimal भग्नing poपूर्णांक facility is installed
	 *   Bit 44: perक्रमm भग्नing poपूर्णांक operation facility is installed
	 * translated to:
	 *   HWCAP_S390_DFP bit 6 (42 && 44).
	 */
	अगर ((elf_hwcap & (1UL << 2)) && test_facility(42) && test_facility(44))
		elf_hwcap |= HWCAP_S390_DFP;

	/*
	 * Huge page support HWCAP_S390_HPAGE is bit 7.
	 */
	अगर (MACHINE_HAS_EDAT1)
		elf_hwcap |= HWCAP_S390_HPAGE;

	/*
	 * 64-bit रेजिस्टर support क्रम 31-bit processes
	 * HWCAP_S390_HIGH_GPRS is bit 9.
	 */
	elf_hwcap |= HWCAP_S390_HIGH_GPRS;

	/*
	 * Transactional execution support HWCAP_S390_TE is bit 10.
	 */
	अगर (MACHINE_HAS_TE)
		elf_hwcap |= HWCAP_S390_TE;

	/*
	 * Vector extension HWCAP_S390_VXRS is bit 11. The Vector extension
	 * can be disabled with the "novx" parameter. Use MACHINE_HAS_VX
	 * instead of facility bit 129.
	 */
	अगर (MACHINE_HAS_VX) अणु
		elf_hwcap |= HWCAP_S390_VXRS;
		अगर (test_facility(134))
			elf_hwcap |= HWCAP_S390_VXRS_BCD;
		अगर (test_facility(135))
			elf_hwcap |= HWCAP_S390_VXRS_EXT;
		अगर (test_facility(148))
			elf_hwcap |= HWCAP_S390_VXRS_EXT2;
		अगर (test_facility(152))
			elf_hwcap |= HWCAP_S390_VXRS_PDE;
	पूर्ण
	अगर (test_facility(150))
		elf_hwcap |= HWCAP_S390_SORT;
	अगर (test_facility(151))
		elf_hwcap |= HWCAP_S390_DFLT;

	/*
	 * Guarded storage support HWCAP_S390_GS is bit 12.
	 */
	अगर (MACHINE_HAS_GS)
		elf_hwcap |= HWCAP_S390_GS;

	get_cpu_id(&cpu_id);
	add_device_अक्रमomness(&cpu_id, माप(cpu_id));
	चयन (cpu_id.machine) अणु
	हाल 0x2064:
	हाल 0x2066:
	शेष:	/* Use "z900" as शेष क्रम 64 bit kernels. */
		म_नकल(elf_platक्रमm, "z900");
		अवरोध;
	हाल 0x2084:
	हाल 0x2086:
		म_नकल(elf_platक्रमm, "z990");
		अवरोध;
	हाल 0x2094:
	हाल 0x2096:
		म_नकल(elf_platक्रमm, "z9-109");
		अवरोध;
	हाल 0x2097:
	हाल 0x2098:
		म_नकल(elf_platक्रमm, "z10");
		अवरोध;
	हाल 0x2817:
	हाल 0x2818:
		म_नकल(elf_platक्रमm, "z196");
		अवरोध;
	हाल 0x2827:
	हाल 0x2828:
		म_नकल(elf_platक्रमm, "zEC12");
		अवरोध;
	हाल 0x2964:
	हाल 0x2965:
		म_नकल(elf_platक्रमm, "z13");
		अवरोध;
	हाल 0x3906:
	हाल 0x3907:
		म_नकल(elf_platक्रमm, "z14");
		अवरोध;
	हाल 0x8561:
	हाल 0x8562:
		म_नकल(elf_platक्रमm, "z15");
		अवरोध;
	पूर्ण

	/*
	 * Virtualization support HWCAP_INT_SIE is bit 0.
	 */
	अगर (sclp.has_sief2)
		पूर्णांक_hwcap |= HWCAP_INT_SIE;

	वापस 0;
पूर्ण
arch_initcall(setup_hwcaps);

/*
 * Add प्रणाली inक्रमmation as device अक्रमomness
 */
अटल व्योम __init setup_अक्रमomness(व्योम)
अणु
	काष्ठा sysinfo_3_2_2 *vmms;

	vmms = (काष्ठा sysinfo_3_2_2 *) memblock_phys_alloc(PAGE_SIZE,
							    PAGE_SIZE);
	अगर (!vmms)
		panic("Failed to allocate memory for sysinfo structure\n");

	अगर (stsi(vmms, 3, 2, 2) == 0 && vmms->count)
		add_device_अक्रमomness(&vmms->vm, माप(vmms->vm[0]) * vmms->count);
	memblock_मुक्त((अचिन्हित दीर्घ) vmms, PAGE_SIZE);
पूर्ण

/*
 * Find the correct size क्रम the task_काष्ठा. This depends on
 * the size of the काष्ठा fpu at the end of the thपढ़ो_काष्ठा
 * which is embedded in the task_काष्ठा.
 */
अटल व्योम __init setup_task_size(व्योम)
अणु
	पूर्णांक task_size = माप(काष्ठा task_काष्ठा);

	अगर (!MACHINE_HAS_VX) अणु
		task_size -= माप(__vector128) * __NUM_VXRS;
		task_size += माप(freg_t) * __NUM_FPRS;
	पूर्ण
	arch_task_काष्ठा_size = task_size;
पूर्ण

/*
 * Issue diagnose 318 to set the control program name and
 * version codes.
 */
अटल व्योम __init setup_control_program_code(व्योम)
अणु
	जोड़ diag318_info diag318_info = अणु
		.cpnc = CPNC_LINUX,
		.cpvc = 0,
	पूर्ण;

	अगर (!sclp.has_diag318)
		वापस;

	diag_stat_inc(DIAG_STAT_X318);
	यंत्र अस्थिर("diag %0,0,0x318\n" : : "d" (diag318_info.val));
पूर्ण

/*
 * Prपूर्णांक the component list from the IPL report
 */
अटल व्योम __init log_component_list(व्योम)
अणु
	काष्ठा ipl_rb_component_entry *ptr, *end;
	अक्षर *str;

	अगर (!early_ipl_comp_list_addr)
		वापस;
	अगर (ipl_block.hdr.flags & IPL_PL_FLAG_SIPL)
		pr_info("Linux is running with Secure-IPL enabled\n");
	अन्यथा
		pr_info("Linux is running with Secure-IPL disabled\n");
	ptr = (व्योम *) early_ipl_comp_list_addr;
	end = (व्योम *) ptr + early_ipl_comp_list_size;
	pr_info("The IPL report contains the following components:\n");
	जबतक (ptr < end) अणु
		अगर (ptr->flags & IPL_RB_COMPONENT_FLAG_SIGNED) अणु
			अगर (ptr->flags & IPL_RB_COMPONENT_FLAG_VERIFIED)
				str = "signed, verified";
			अन्यथा
				str = "signed, verification failed";
		पूर्ण अन्यथा अणु
			str = "not signed";
		पूर्ण
		pr_info("%016llx - %016llx (%s)\n",
			ptr->addr, ptr->addr + ptr->len, str);
		ptr++;
	पूर्ण
पूर्ण

/*
 * Setup function called from init/मुख्य.c just after the banner
 * was prपूर्णांकed.
 */

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
        /*
         * prपूर्णांक what head.S has found out about the machine
         */
	अगर (MACHINE_IS_VM)
		pr_info("Linux is running as a z/VM "
			"guest operating system in 64-bit mode\n");
	अन्यथा अगर (MACHINE_IS_KVM)
		pr_info("Linux is running under KVM in 64-bit mode\n");
	अन्यथा अगर (MACHINE_IS_LPAR)
		pr_info("Linux is running natively in 64-bit mode\n");
	अन्यथा
		pr_info("Linux is running as a guest in 64-bit mode\n");

	log_component_list();

	/* Have one command line that is parsed and saved in /proc/cmdline */
	/* boot_command_line has been alपढ़ोy set up in early.c */
	*cmdline_p = boot_command_line;

        ROOT_DEV = Root_RAM0;

	init_mm.start_code = (अचिन्हित दीर्घ) _text;
	init_mm.end_code = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data = (अचिन्हित दीर्घ) _edata;
	init_mm.brk = (अचिन्हित दीर्घ) _end;

	अगर (IS_ENABLED(CONFIG_EXPOLINE_AUTO))
		nospec_स्वतः_detect();

	jump_label_init();
	parse_early_param();
#अगर_घोषित CONFIG_CRASH_DUMP
	/* Deactivate elfcorehdr= kernel parameter */
	elfcorehdr_addr = ELFCORE_ADDR_MAX;
#पूर्ण_अगर

	os_info_init();
	setup_ipl();
	setup_task_size();
	setup_control_program_code();

	/* Do some memory reservations *beक्रमe* memory is added to memblock */
	reserve_above_ident_map();
	reserve_oldmem();
	reserve_kernel();
	reserve_initrd();
	reserve_certअगरicate_list();
	reserve_mem_detect_info();
	memblock_allow_resize();

	/* Get inक्रमmation about *all* installed memory */
	memblock_add_mem_detect_info();

	मुक्त_mem_detect_info();
	हटाओ_oldmem();

	setup_uv();
	setup_ident_map_size();
	setup_memory();
	dma_contiguous_reserve(ident_map_size);
	vmcp_cma_reserve();
	अगर (MACHINE_HAS_EDAT2)
		hugetlb_cma_reserve(PUD_SHIFT - PAGE_SHIFT);

	check_initrd();
	reserve_crashkernel();
#अगर_घोषित CONFIG_CRASH_DUMP
	/*
	 * Be aware that smp_save_dump_cpus() triggers a प्रणाली reset.
	 * Thereक्रमe CPU and device initialization should be करोne afterwards.
	 */
	smp_save_dump_cpus();
#पूर्ण_अगर

	setup_resources();
	setup_lowcore_dat_off();
	smp_fill_possible_mask();
	cpu_detect_mhz_feature();
        cpu_init();
	numa_setup();
	smp_detect_cpus();
	topology_init_early();

	/*
	 * Create kernel page tables and चयन to भव addressing.
	 */
        paging_init();

	/*
	 * After paging_init created the kernel page table, the new PSWs
	 * in lowcore can now run with DAT enabled.
	 */
	setup_lowcore_dat_on();

        /* Setup शेष console */
	conmode_शेष();
	set_preferred_console();

	apply_alternative_inकाष्ठाions();
	अगर (IS_ENABLED(CONFIG_EXPOLINE))
		nospec_init_branches();

	/* Setup zfcp/nvme dump support */
	setup_zfcpdump();

	/* Add प्रणाली specअगरic data to the अक्रमom pool */
	setup_अक्रमomness();
पूर्ण
