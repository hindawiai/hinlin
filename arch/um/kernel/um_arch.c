<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/utsname.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/suspend.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <as-layout.h>
#समावेश <arch.h>
#समावेश <init.h>
#समावेश <kern.h>
#समावेश <kern_util.h>
#समावेश <mem_user.h>
#समावेश <os.h>

#घोषणा DEFAULT_COMMAND_LINE_ROOT "root=98:0"
#घोषणा DEFAULT_COMMAND_LINE_CONSOLE "console=tty"

/* Changed in add_arg and setup_arch, which run beक्रमe SMP is started */
अटल अक्षर __initdata command_line[COMMAND_LINE_SIZE] = अणु 0 पूर्ण;

अटल व्योम __init add_arg(अक्षर *arg)
अणु
	अगर (म_माप(command_line) + म_माप(arg) + 1 > COMMAND_LINE_SIZE) अणु
		os_warn("add_arg: Too many command line arguments!\n");
		निकास(1);
	पूर्ण
	अगर (म_माप(command_line) > 0)
		म_जोड़ो(command_line, " ");
	म_जोड़ो(command_line, arg);
पूर्ण

/*
 * These fields are initialized at boot समय and not changed.
 * XXX This काष्ठाure is used only in the non-SMP हाल.  Maybe this
 * should be moved to smp.c.
 */
काष्ठा cpuinfo_um boot_cpu_data = अणु
	.loops_per_jअगरfy	= 0,
	.ipi_pipe		= अणु -1, -1 पूर्ण
पूर्ण;

जोड़ thपढ़ो_जोड़ cpu0_irqstack
	__section(".data..init_irqstack") =
		अणु .thपढ़ो_info = INIT_THREAD_INFO(init_task) पूर्ण;

/* Changed in setup_arch, which is called in early boot */
अटल अक्षर host_info[(__NEW_UTS_LEN + 1) * 5];

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक index = 0;

	seq_म_लिखो(m, "processor\t: %d\n", index);
	seq_म_लिखो(m, "vendor_id\t: User Mode Linux\n");
	seq_म_लिखो(m, "model name\t: UML\n");
	seq_म_लिखो(m, "mode\t\t: skas\n");
	seq_म_लिखो(m, "host\t\t: %s\n", host_info);
	seq_म_लिखो(m, "bogomips\t: %lu.%02lu\n\n",
		   loops_per_jअगरfy/(500000/HZ),
		   (loops_per_jअगरfy/(5000/HZ)) % 100);

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos < NR_CPUS ? cpu_data + *pos : शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;

/* Set in linux_मुख्य */
अचिन्हित दीर्घ uml_physmem;
EXPORT_SYMBOL(uml_physmem);

अचिन्हित दीर्घ uml_reserved; /* Also modअगरied in mem_init */
अचिन्हित दीर्घ start_vm;
अचिन्हित दीर्घ end_vm;

/* Set in uml_ncpus_setup */
पूर्णांक ncpus = 1;

/* Set in early boot */
अटल पूर्णांक have_root __initdata;
अटल पूर्णांक have_console __initdata;

/* Set in uml_mem_setup and modअगरied in linux_मुख्य */
दीर्घ दीर्घ physmem_size = 32 * 1024 * 1024;
EXPORT_SYMBOL(physmem_size);

अटल स्थिर अक्षर *usage_string =
"User Mode Linux v%s\n"
"	available at http://user-mode-linux.sourceforge.net/\n\n";

अटल पूर्णांक __init uml_version_setup(अक्षर *line, पूर्णांक *add)
अणु
	/* Explicitly use म_लिखो() to show version in मानक_निकास */
	म_लिखो("%s\n", init_utsname()->release);
	निकास(0);

	वापस 0;
पूर्ण

__uml_setup("--version", uml_version_setup,
"--version\n"
"    Prints the version number of the kernel.\n\n"
);

अटल पूर्णांक __init uml_root_setup(अक्षर *line, पूर्णांक *add)
अणु
	have_root = 1;
	वापस 0;
पूर्ण

__uml_setup("root=", uml_root_setup,
"root=<file containing the root fs>\n"
"    This is actually used by the generic kernel in exactly the same\n"
"    way as in any other kernel. If you configure a number of block\n"
"    devices and want to boot off something other than ubd0, you \n"
"    would use something like:\n"
"        root=/dev/ubd5\n\n"
);

अटल पूर्णांक __init no_skas_debug_setup(अक्षर *line, पूर्णांक *add)
अणु
	os_warn("'debug' is not necessary to gdb UML in skas mode - run\n");
	os_warn("'gdb linux'\n");

	वापस 0;
पूर्ण

__uml_setup("debug", no_skas_debug_setup,
"debug\n"
"    this flag is not needed to run gdb on UML in skas mode\n\n"
);

अटल पूर्णांक __init uml_console_setup(अक्षर *line, पूर्णांक *add)
अणु
	have_console = 1;
	वापस 0;
पूर्ण

__uml_setup("console=", uml_console_setup,
"console=<preferred console>\n"
"    Specify the preferred console output driver\n\n"
);

अटल पूर्णांक __init Usage(अक्षर *line, पूर्णांक *add)
अणु
	स्थिर अक्षर **p;

	म_लिखो(usage_string, init_utsname()->release);
	p = &__uml_help_start;
	/* Explicitly use म_लिखो() to show help in मानक_निकास */
	जबतक (p < &__uml_help_end) अणु
		म_लिखो("%s", *p);
		p++;
	पूर्ण
	निकास(0);
	वापस 0;
पूर्ण

__uml_setup("--help", Usage,
"--help\n"
"    Prints this message.\n\n"
);

अटल व्योम __init uml_checksetup(अक्षर *line, पूर्णांक *add)
अणु
	काष्ठा uml_param *p;

	p = &__uml_setup_start;
	जबतक (p < &__uml_setup_end) अणु
		माप_प्रकार n;

		n = म_माप(p->str);
		अगर (!म_भेदन(line, p->str, n) && p->setup_func(line + n, add))
			वापस;
		p++;
	पूर्ण
पूर्ण

अटल व्योम __init uml_postsetup(व्योम)
अणु
	initcall_t *p;

	p = &__uml_postsetup_start;
	जबतक (p < &__uml_postsetup_end) अणु
		(*p)();
		p++;
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक panic_निकास(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ unused1,
		      व्योम *unused2)
अणु
	kmsg_dump(KMSG_DUMP_PANIC);
	bust_spinlocks(1);
	bust_spinlocks(0);
	uml_निकासcode = 1;
	os_dump_core();
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block panic_निकास_notअगरier = अणु
	.notअगरier_call 		= panic_निकास,
	.next 			= शून्य,
	.priority 		= 0
पूर्ण;

व्योम uml_finishsetup(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &panic_निकास_notअगरier);

	uml_postsetup();

	new_thपढ़ो_handler();
पूर्ण

/* Set during early boot */
अचिन्हित दीर्घ stub_start;
अचिन्हित दीर्घ task_size;
EXPORT_SYMBOL(task_size);

अचिन्हित दीर्घ host_task_size;

अचिन्हित दीर्घ brk_start;
अचिन्हित दीर्घ end_iomem;
EXPORT_SYMBOL(end_iomem);

#घोषणा MIN_VMALLOC (32 * 1024 * 1024)

पूर्णांक __init linux_मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित दीर्घ avail, dअगरf;
	अचिन्हित दीर्घ virपंचांगem_size, max_physmem;
	अचिन्हित दीर्घ stack;
	अचिन्हित पूर्णांक i;
	पूर्णांक add;

	क्रम (i = 1; i < argc; i++) अणु
		अगर ((i == 1) && (argv[i][0] == ' '))
			जारी;
		add = 1;
		uml_checksetup(argv[i], &add);
		अगर (add)
			add_arg(argv[i]);
	पूर्ण
	अगर (have_root == 0)
		add_arg(DEFAULT_COMMAND_LINE_ROOT);

	अगर (have_console == 0)
		add_arg(DEFAULT_COMMAND_LINE_CONSOLE);

	host_task_size = os_get_top_address();
	/* reserve two pages क्रम the stubs */
	host_task_size -= 2 * PAGE_SIZE;
	stub_start = host_task_size;

	/*
	 * TASK_SIZE needs to be PGसूची_SIZE aligned or अन्यथा निकास_mmap craps
	 * out
	 */
	task_size = host_task_size & PGसूची_MASK;

	/* OS sanity checks that need to happen beक्रमe the kernel runs */
	os_early_checks();

	brk_start = (अचिन्हित दीर्घ) sbrk(0);

	/*
	 * Increase physical memory size क्रम exec-shield users
	 * so they actually get what they asked क्रम. This should
	 * add zero क्रम non-exec shield users
	 */

	dअगरf = UML_ROUND_UP(brk_start) - UML_ROUND_UP(&_end);
	अगर (dअगरf > 1024 * 1024) अणु
		os_info("Adding %ld bytes to physical memory to account for "
			"exec-shield gap\n", dअगरf);
		physmem_size += UML_ROUND_UP(brk_start) - UML_ROUND_UP(&_end);
	पूर्ण

	uml_physmem = (अचिन्हित दीर्घ) __binary_start & PAGE_MASK;

	/* Reserve up to 4M after the current brk */
	uml_reserved = ROUND_4M(brk_start) + (1 << 22);

	setup_machinename(init_utsname()->machine);

	highmem = 0;
	iomem_size = (iomem_size + PAGE_SIZE - 1) & PAGE_MASK;
	max_physmem = TASK_SIZE - uml_physmem - iomem_size - MIN_VMALLOC;

	/*
	 * Zones have to begin on a 1 << MAX_ORDER page boundary,
	 * so this makes sure that's true क्रम highmem
	 */
	max_physmem &= ~((1 << (PAGE_SHIFT + MAX_ORDER)) - 1);
	अगर (physmem_size + iomem_size > max_physmem) अणु
		highmem = physmem_size + iomem_size - max_physmem;
		physmem_size -= highmem;
	पूर्ण

	high_physmem = uml_physmem + physmem_size;
	end_iomem = high_physmem + iomem_size;
	high_memory = (व्योम *) end_iomem;

	start_vm = VMALLOC_START;

	virपंचांगem_size = physmem_size;
	stack = (अचिन्हित दीर्घ) argv;
	stack &= ~(1024 * 1024 - 1);
	avail = stack - start_vm;
	अगर (physmem_size > avail)
		virपंचांगem_size = avail;
	end_vm = start_vm + virपंचांगem_size;

	अगर (virपंचांगem_size < physmem_size)
		os_info("Kernel virtual memory size shrunk to %lu bytes\n",
			virपंचांगem_size);

	os_flush_मानक_निकास();

	वापस start_uml();
पूर्ण

पूर्णांक __init __weak पढ़ो_initrd(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	stack_protections((अचिन्हित दीर्घ) &init_thपढ़ो_info);
	setup_physmem(uml_physmem, uml_reserved, physmem_size, highmem);
	mem_total_pages(physmem_size, iomem_size, highmem);
	पढ़ो_initrd();

	paging_init();
	strlcpy(boot_command_line, command_line, COMMAND_LINE_SIZE);
	*cmdline_p = command_line;
	setup_hostinfo(host_info, माप host_info);
पूर्ण

व्योम __init check_bugs(व्योम)
अणु
	arch_check_bugs();
	os_check_bugs();
पूर्ण

व्योम apply_alternatives(काष्ठा alt_instr *start, काष्ठा alt_instr *end)
अणु
पूर्ण

व्योम *text_poke(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len)
अणु
	/*
	 * In UML, the only reference to this function is in
	 * apply_relocate_add(), which shouldn't ever actually call this
	 * because UML करोesn't have live patching.
	 */
	WARN_ON(1);

	वापस स_नकल(addr, opcode, len);
पूर्ण

व्योम text_poke_sync(व्योम)
अणु
पूर्ण

व्योम uml_pm_wake(व्योम)
अणु
	pm_प्रणाली_wakeup();
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक um_suspend_valid(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_MEM;
पूर्ण

अटल पूर्णांक um_suspend_prepare(व्योम)
अणु
	um_irqs_suspend();
	वापस 0;
पूर्ण

अटल पूर्णांक um_suspend_enter(suspend_state_t state)
अणु
	अगर (WARN_ON(state != PM_SUSPEND_MEM))
		वापस -EINVAL;

	/*
	 * This is identical to the idle sleep, but we've just
	 * (during suspend) turned off all पूर्णांकerrupt sources
	 * except क्रम the ones we want, so now we can only wake
	 * up on something we actually want to wake up on. All
	 * timing has also been suspended.
	 */
	um_idle_sleep();
	वापस 0;
पूर्ण

अटल व्योम um_suspend_finish(व्योम)
अणु
	um_irqs_resume();
पूर्ण

स्थिर काष्ठा platक्रमm_suspend_ops um_suspend_ops = अणु
	.valid = um_suspend_valid,
	.prepare = um_suspend_prepare,
	.enter = um_suspend_enter,
	.finish = um_suspend_finish,
पूर्ण;

अटल पूर्णांक init_pm_wake_संकेत(व्योम)
अणु
	/*
	 * In बाह्यal समय-travel mode we can't use संकेतs to wake up
	 * since that would mess with the scheduling. We'll have to करो
	 * some additional work to support wakeup on virtio devices or
	 * similar, perhaps implementing a fake RTC controller that can
	 * trigger wakeup (and request the appropriate scheduling from
	 * the बाह्यal scheduler when going to suspend.)
	 */
	अगर (समय_प्रकारravel_mode != TT_MODE_EXTERNAL)
		रेजिस्टर_pm_wake_संकेत();

	suspend_set_ops(&um_suspend_ops);

	वापस 0;
पूर्ण

late_initcall(init_pm_wake_संकेत);
#पूर्ण_अगर
