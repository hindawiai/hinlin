<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/sparc/kernel/setup.c
 *
 *  Copyright (C) 1995  David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 2000  Anton Blanअक्षरd (anton@samba.org)
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/initrd.h>
#समावेश <यंत्र/smp.h>
#समावेश <linux/user.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/console.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/export.h>
#समावेश <linux/start_kernel.h>
#समावेश <uapi/linux/mount.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/mbus.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/sections.h>

#समावेश "kernel.h"

काष्ठा screen_info screen_info = अणु
	0, 0,			/* orig-x, orig-y */
	0,			/* unused */
	0,			/* orig-video-page */
	0,			/* orig-video-mode */
	128,			/* orig-video-cols */
	0,0,0,			/* ega_ax, ega_bx, ega_cx */
	54,			/* orig-video-lines */
	0,                      /* orig-video-isVGA */
	16                      /* orig-video-poपूर्णांकs */
पूर्ण;

/* Typing sync at the prom prompt calls the function poपूर्णांकed to by
 * romvec->pv_synchook which I set to the following function.
 * This should sync all fileप्रणालीs and वापस, क्रम now it just
 * prपूर्णांकs out pretty messages and वापसs.
 */

/* Pretty sick eh? */
अटल व्योम prom_sync_me(व्योम)
अणु
	अचिन्हित दीर्घ prom_tbr, flags;

	/* XXX Badly broken. FIX! - Anton */
	local_irq_save(flags);
	__यंत्र__ __अस्थिर__("rd %%tbr, %0\n\t" : "=r" (prom_tbr));
	__यंत्र__ __अस्थिर__("wr %0, 0x0, %%tbr\n\t"
			     "nop\n\t"
			     "nop\n\t"
			     "nop\n\t" : : "r" (&trapbase));

	prom_म_लिखो("PROM SYNC COMMAND...\n");
	show_मुक्त_areas(0, शून्य);
	अगर (!is_idle_task(current)) अणु
		local_irq_enable();
		ksys_sync();
		local_irq_disable();
	पूर्ण
	prom_म_लिखो("Returning to prom\n");

	__यंत्र__ __अस्थिर__("wr %0, 0x0, %%tbr\n\t"
			     "nop\n\t"
			     "nop\n\t"
			     "nop\n\t" : : "r" (prom_tbr));
	local_irq_restore(flags);
पूर्ण

अटल अचिन्हित पूर्णांक boot_flags __initdata = 0;
#घोषणा BOOTME_DEBUG  0x1

/* Exported क्रम mm/init.c:paging_init. */
अचिन्हित दीर्घ cmdline_memory_size __initdata = 0;

/* which CPU booted us (0xff = not set) */
अचिन्हित अक्षर boot_cpu_id = 0xff; /* 0xff will make it पूर्णांकo DATA section... */

अटल व्योम
prom_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	prom_ग_लिखो(s, n);
पूर्ण

अटल काष्ठा console prom_early_console = अणु
	.name =		"earlyprom",
	.ग_लिखो =	prom_console_ग_लिखो,
	.flags =	CON_PRINTBUFFER | CON_BOOT,
	.index =	-1,
पूर्ण;

/* 
 * Process kernel command line चयनes that are specअगरic to the
 * SPARC or that require special low-level processing.
 */
अटल व्योम __init process_चयन(अक्षर c)
अणु
	चयन (c) अणु
	हाल 'd':
		boot_flags |= BOOTME_DEBUG;
		अवरोध;
	हाल 's':
		अवरोध;
	हाल 'h':
		prom_म_लिखो("boot_flags_init: Halt!\n");
		prom_halt();
		अवरोध;
	हाल 'p':
		prom_early_console.flags &= ~CON_BOOT;
		अवरोध;
	शेष:
		prपूर्णांकk("Unknown boot switch (-%c)\n", c);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init boot_flags_init(अक्षर *commands)
अणु
	जबतक (*commands) अणु
		/* Move to the start of the next "argument". */
		जबतक (*commands == ' ')
			commands++;

		/* Process any command चयनes, otherwise skip it. */
		अगर (*commands == '\0')
			अवरोध;
		अगर (*commands == '-') अणु
			commands++;
			जबतक (*commands && *commands != ' ')
				process_चयन(*commands++);
			जारी;
		पूर्ण
		अगर (!म_भेदन(commands, "mem=", 4)) अणु
			/*
			 * "mem=XXX[kKmM] overrides the PROM-reported
			 * memory size.
			 */
			cmdline_memory_size = simple_म_से_अदीर्घ(commands + 4,
						     &commands, 0);
			अगर (*commands == 'K' || *commands == 'k') अणु
				cmdline_memory_size <<= 10;
				commands++;
			पूर्ण अन्यथा अगर (*commands=='M' || *commands=='m') अणु
				cmdline_memory_size <<= 20;
				commands++;
			पूर्ण
		पूर्ण
		जबतक (*commands && *commands != ' ')
			commands++;
	पूर्ण
पूर्ण

बाह्य अचिन्हित लघु root_flags;
बाह्य अचिन्हित लघु root_dev;
बाह्य अचिन्हित लघु ram_flags;
#घोषणा RAMDISK_IMAGE_START_MASK	0x07FF
#घोषणा RAMDISK_PROMPT_FLAG		0x8000
#घोषणा RAMDISK_LOAD_FLAG		0x4000

बाह्य पूर्णांक root_mountflags;

अक्षर reboot_command[COMMAND_LINE_SIZE];

काष्ठा cpuid_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	sun4d[3];
	अचिन्हित पूर्णांक	leon[3];
पूर्ण;
बाह्य काष्ठा cpuid_patch_entry __cpuid_patch, __cpuid_patch_end;

अटल व्योम __init per_cpu_patch(व्योम)
अणु
	काष्ठा cpuid_patch_entry *p;

	अगर (sparc_cpu_model == sun4m) अणु
		/* Nothing to करो, this is what the unpatched code
		 * tarमाला_लो.
		 */
		वापस;
	पूर्ण

	p = &__cpuid_patch;
	जबतक (p < &__cpuid_patch_end) अणु
		अचिन्हित दीर्घ addr = p->addr;
		अचिन्हित पूर्णांक *insns;

		चयन (sparc_cpu_model) अणु
		हाल sun4d:
			insns = &p->sun4d[0];
			अवरोध;

		हाल sparc_leon:
			insns = &p->leon[0];
			अवरोध;
		शेष:
			prom_म_लिखो("Unknown cpu type, halting.\n");
			prom_halt();
		पूर्ण
		*(अचिन्हित पूर्णांक *) (addr + 0) = insns[0];
		flushi(addr + 0);
		*(अचिन्हित पूर्णांक *) (addr + 4) = insns[1];
		flushi(addr + 4);
		*(अचिन्हित पूर्णांक *) (addr + 8) = insns[2];
		flushi(addr + 8);

		p++;
	पूर्ण
पूर्ण

काष्ठा leon_1insn_patch_entry अणु
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक insn;
पूर्ण;

क्रमागत sparc_cpu sparc_cpu_model;
EXPORT_SYMBOL(sparc_cpu_model);

अटल __init व्योम leon_patch(व्योम)
अणु
	काष्ठा leon_1insn_patch_entry *start = (व्योम *)__leon_1insn_patch;
	काष्ठा leon_1insn_patch_entry *end = (व्योम *)__leon_1insn_patch_end;

	/* Default inकाष्ठाion is leon - no patching */
	अगर (sparc_cpu_model == sparc_leon)
		वापस;

	जबतक (start < end) अणु
		अचिन्हित दीर्घ addr = start->addr;

		*(अचिन्हित पूर्णांक *)(addr) = start->insn;
		flushi(addr);

		start++;
	पूर्ण
पूर्ण

काष्ठा tt_entry *sparc_ttable;

/* Called from head_32.S - beक्रमe we have setup anything
 * in the kernel. Be very careful with what you करो here.
 */
व्योम __init sparc32_start_kernel(काष्ठा linux_romvec *rp)
अणु
	prom_init(rp);

	/* Set sparc_cpu_model */
	sparc_cpu_model = sun_unknown;
	अगर (!म_भेद(&cputypval[0], "sun4m"))
		sparc_cpu_model = sun4m;
	अगर (!म_भेद(&cputypval[0], "sun4s"))
		sparc_cpu_model = sun4m; /* CP-1200 with PROM 2.30 -E */
	अगर (!म_भेद(&cputypval[0], "sun4d"))
		sparc_cpu_model = sun4d;
	अगर (!म_भेद(&cputypval[0], "sun4e"))
		sparc_cpu_model = sun4e;
	अगर (!म_भेद(&cputypval[0], "sun4u"))
		sparc_cpu_model = sun4u;
	अगर (!म_भेदन(&cputypval[0], "leon" , 4))
		sparc_cpu_model = sparc_leon;

	leon_patch();
	start_kernel();
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ highest_paddr;

	sparc_ttable = &trapbase;

	/* Initialize PROM console and command line. */
	*cmdline_p = prom_getbootargs();
	strlcpy(boot_command_line, *cmdline_p, COMMAND_LINE_SIZE);
	parse_early_param();

	boot_flags_init(*cmdline_p);

	रेजिस्टर_console(&prom_early_console);

	चयन(sparc_cpu_model) अणु
	हाल sun4m:
		pr_info("ARCH: SUN4M\n");
		अवरोध;
	हाल sun4d:
		pr_info("ARCH: SUN4D\n");
		अवरोध;
	हाल sun4e:
		pr_info("ARCH: SUN4E\n");
		अवरोध;
	हाल sun4u:
		pr_info("ARCH: SUN4U\n");
		अवरोध;
	हाल sparc_leon:
		pr_info("ARCH: LEON\n");
		अवरोध;
	शेष:
		pr_info("ARCH: UNKNOWN!\n");
		अवरोध;
	पूर्ण

	idprom_init();
	load_mmu();

	phys_base = 0xffffffffUL;
	highest_paddr = 0UL;
	क्रम (i = 0; sp_banks[i].num_bytes != 0; i++) अणु
		अचिन्हित दीर्घ top;

		अगर (sp_banks[i].base_addr < phys_base)
			phys_base = sp_banks[i].base_addr;
		top = sp_banks[i].base_addr +
			sp_banks[i].num_bytes;
		अगर (highest_paddr < top)
			highest_paddr = top;
	पूर्ण
	pfn_base = phys_base >> PAGE_SHIFT;

	अगर (!root_flags)
		root_mountflags &= ~MS_RDONLY;
	ROOT_DEV = old_decode_dev(root_dev);
#अगर_घोषित CONFIG_BLK_DEV_RAM
	rd_image_start = ram_flags & RAMDISK_IMAGE_START_MASK;
#पूर्ण_अगर

	prom_setsync(prom_sync_me);

	अगर((boot_flags & BOOTME_DEBUG) && (linux_dbvec != शून्य) &&
	   ((*(लघु *)linux_dbvec) != -1)) अणु
		prपूर्णांकk("Booted under KADB. Syncing trap table.\n");
		(*(linux_dbvec->teach_debugger))();
	पूर्ण

	/* Run-समय patch inकाष्ठाions to match the cpu model */
	per_cpu_patch();

	paging_init();

	smp_setup_cpu_possible_map();
पूर्ण

बाह्य पूर्णांक stop_a_enabled;

व्योम sun_करो_अवरोध(व्योम)
अणु
	अगर (!stop_a_enabled)
		वापस;

	prपूर्णांकk("\n");
	flush_user_winकरोws();

	prom_cmdline();
पूर्ण
EXPORT_SYMBOL(sun_करो_अवरोध);

पूर्णांक stop_a_enabled = 1;

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i, ncpus, err;

	/* Count the number of physically present processors in
	 * the machine, even on uniprocessor, so that /proc/cpuinfo
	 * output is consistent with 2.4.x
	 */
	ncpus = 0;
	जबतक (!cpu_find_by_instance(ncpus, शून्य, शून्य))
		ncpus++;
	ncpus_probed = ncpus;

	err = 0;
	क्रम_each_online_cpu(i) अणु
		काष्ठा cpu *p = kzalloc(माप(*p), GFP_KERNEL);
		अगर (!p)
			err = -ENOMEM;
		अन्यथा
			रेजिस्टर_cpu(p, i);
	पूर्ण

	वापस err;
पूर्ण

subsys_initcall(topology_init);
