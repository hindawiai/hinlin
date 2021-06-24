<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    PARISC Architecture-dependent parts of process handling
 *    based on the work क्रम i386
 *
 *    Copyright (C) 1999-2003 Matthew Wilcox <willy at parisc-linux.org>
 *    Copyright (C) 2000 Martin K Petersen <mkp at mkp.net>
 *    Copyright (C) 2000 John Marvin <jsm at parisc-linux.org>
 *    Copyright (C) 2000 David Huggins-Daines <dhd with pobox.org>
 *    Copyright (C) 2000-2003 Paul Bame <bame at parisc-linux.org>
 *    Copyright (C) 2000 Philipp Rumpf <prumpf with tux.org>
 *    Copyright (C) 2000 David Kennedy <dkennedy with linuxcare.com>
 *    Copyright (C) 2000 Riअक्षरd Hirst <rhirst with parisc-linux.org>
 *    Copyright (C) 2000 Grant Grundler <grundler with parisc-linux.org>
 *    Copyright (C) 2001 Alan Modra <amodra at parisc-linux.org>
 *    Copyright (C) 2001-2002 Ryan Bradetich <rbrad at parisc-linux.org>
 *    Copyright (C) 2001-2014 Helge Deller <deller@gmx.de>
 *    Copyright (C) 2002 Ranकरोlph Chung <tausq with parisc-linux.org>
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/elf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/personality.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/nmi.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/assembly.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdc_chassis.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/sections.h>

#घोषणा COMMAND_GLOBAL  F_EXTEND(0xfffe0030)
#घोषणा CMD_RESET       5       /* reset any module */

/*
** The Wright Brothers and Gecko प्रणालीs have a H/W problem
** (Lasi...'nuf said) may cause a broadcast reset to lockup
** the प्रणाली. An HVERSION dependent PDC call was developed
** to perक्रमm a "safe", platक्रमm specअगरic broadcast reset instead
** of kludging up all the code.
**
** Older machines which करो not implement PDC_BROADCAST_RESET will
** वापस (with an error) and the regular broadcast reset can be
** issued. Obviously, अगर the PDC करोes implement PDC_BROADCAST_RESET
** the PDC call will not वापस (the प्रणाली will be reset).
*/
व्योम machine_restart(अक्षर *cmd)
अणु
#अगर_घोषित FASTBOOT_SELFTEST_SUPPORT
	/*
	 ** If user has modअगरied the Firmware Selftest Biपंचांगap,
	 ** run the tests specअगरied in the biपंचांगap after the
	 ** प्रणाली is rebooted w/PDC_DO_RESET.
	 **
	 ** ftc_biपंचांगap = 0x1AUL "Skip destructive memory tests"
	 **
	 ** Using "directed resets" at each processor with the MEM_TOC
	 ** vector cleared will also aव्योम running deकाष्ठाive
	 ** memory self tests. (Not implemented yet)
	 */
	अगर (ftc_biपंचांगap) अणु
		pdc_करो_firm_test_reset(ftc_biपंचांगap);
	पूर्ण
#पूर्ण_अगर
	/* set up a new led state on प्रणालीs shipped with a LED State panel */
	pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_SHUTDOWN);
	
	/* "Normal" प्रणाली reset */
	pdc_करो_reset();

	/* Nope...box should reset with just CMD_RESET now */
	gsc_ग_लिखोl(CMD_RESET, COMMAND_GLOBAL);

	/* Wait क्रम RESET to lay us to rest. */
	जबतक (1) ;

पूर्ण

व्योम (*chassis_घातer_off)(व्योम);

/*
 * This routine is called from sys_reboot to actually turn off the
 * machine 
 */
व्योम machine_घातer_off(व्योम)
अणु
	/* If there is a रेजिस्टरed घातer off handler, call it. */
	अगर (chassis_घातer_off)
		chassis_घातer_off();

	/* Put the soft घातer button back under hardware control.
	 * If the user had alपढ़ोy pressed the घातer button, the
	 * following call will immediately घातer off. */
	pdc_soft_घातer_button(0);
	
	pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_SHUTDOWN);

	/* ipmi_घातeroff may have been installed. */
	अगर (pm_घातer_off)
		pm_घातer_off();
		
	/* It seems we have no way to घातer the प्रणाली off via
	 * software. The user has to press the button himself. */

	prपूर्णांकk(KERN_EMERG "System shut down completed.\n"
	       "Please power this system off now.");

	/* prevent soft lockup/stalled CPU messages क्रम endless loop. */
	rcu_sysrq_start();
	lockup_detector_soft_घातeroff();
	क्रम (;;);
पूर्ण

व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL(pm_घातer_off);

व्योम machine_halt(व्योम)
अणु
	machine_घातer_off();
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
	/* Only needs to handle fpu stuff or perf monitors.
	** REVISIT: several arches implement a "lazy fpu state".
	*/
पूर्ण

व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

/*
 * Idle thपढ़ो support
 *
 * Detect when running on QEMU with SeaBIOS PDC Firmware and let
 * QEMU idle the host too.
 */

पूर्णांक running_on_qemu __ro_after_init;
EXPORT_SYMBOL(running_on_qemu);

व्योम __cpuidle arch_cpu_idle_dead(व्योम)
अणु
	/* nop on real hardware, qemu will offline CPU. */
	यंत्र अस्थिर("or %%r31,%%r31,%%r31\n":::);
पूर्ण

व्योम __cpuidle arch_cpu_idle(व्योम)
अणु
	raw_local_irq_enable();

	/* nop on real hardware, qemu will idle sleep. */
	यंत्र अस्थिर("or %%r10,%%r10,%%r10\n":::);
पूर्ण

अटल पूर्णांक __init parisc_idle_init(व्योम)
अणु
	अगर (!running_on_qemu)
		cpu_idle_poll_ctrl(1);

	वापस 0;
पूर्ण
arch_initcall(parisc_idle_init);

/*
 * Copy architecture-specअगरic thपढ़ो state
 */
पूर्णांक
copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp,
	    अचिन्हित दीर्घ kthपढ़ो_arg, काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *cregs = &(p->thपढ़ो.regs);
	व्योम *stack = task_stack_page(p);
	
	/* We have to use व्योम * instead of a function poपूर्णांकer, because
	 * function poपूर्णांकers aren't a poपूर्णांकer to the function on 64-bit.
	 * Make them स्थिर so the compiler knows they live in .text */
	बाह्य व्योम * स्थिर ret_from_kernel_thपढ़ो;
	बाह्य व्योम * स्थिर child_वापस;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* kernel thपढ़ो */
		स_रखो(cregs, 0, माप(काष्ठा pt_regs));
		अगर (!usp) /* idle thपढ़ो */
			वापस 0;
		/* Must निकास via ret_from_kernel_thपढ़ो in order
		 * to call schedule_tail()
		 */
		cregs->ksp = (अचिन्हित दीर्घ)stack + THREAD_SZ_ALGN + FRAME_SIZE;
		cregs->kpc = (अचिन्हित दीर्घ) &ret_from_kernel_thपढ़ो;
		/*
		 * Copy function and argument to be called from
		 * ret_from_kernel_thपढ़ो.
		 */
#अगर_घोषित CONFIG_64BIT
		cregs->gr[27] = ((अचिन्हित दीर्घ *)usp)[3];
		cregs->gr[26] = ((अचिन्हित दीर्घ *)usp)[2];
#अन्यथा
		cregs->gr[26] = usp;
#पूर्ण_अगर
		cregs->gr[25] = kthपढ़ो_arg;
	पूर्ण अन्यथा अणु
		/* user thपढ़ो */
		/* usp must be word aligned.  This also prevents users from
		 * passing in the value 1 (which is the संकेत क्रम a special
		 * वापस क्रम a kernel thपढ़ो) */
		अगर (usp) अणु
			usp = ALIGN(usp, 4);
			अगर (likely(usp))
				cregs->gr[30] = usp;
		पूर्ण
		cregs->ksp = (अचिन्हित दीर्घ)stack + THREAD_SZ_ALGN + FRAME_SIZE;
		cregs->kpc = (अचिन्हित दीर्घ) &child_वापस;

		/* Setup thपढ़ो TLS area */
		अगर (clone_flags & CLONE_SETTLS)
			cregs->cr27 = tls;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित दीर्घ
get_wchan(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा unwind_frame_info info;
	अचिन्हित दीर्घ ip;
	पूर्णांक count = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	/*
	 * These bracket the sleeping functions..
	 */

	unwind_frame_init_from_blocked_task(&info, p);
	करो अणु
		अगर (unwind_once(&info) < 0)
			वापस 0;
		अगर (p->state == TASK_RUNNING)
                        वापस 0;
		ip = info.ip;
		अगर (!in_sched_functions(ip))
			वापस ip;
	पूर्ण जबतक (count++ < MAX_UNWIND_ENTRIES);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_64BIT
व्योम *dereference_function_descriptor(व्योम *ptr)
अणु
	Elf64_Fdesc *desc = ptr;
	व्योम *p;

	अगर (!get_kernel_nofault(p, (व्योम *)&desc->addr))
		ptr = p;
	वापस ptr;
पूर्ण

व्योम *dereference_kernel_function_descriptor(व्योम *ptr)
अणु
	अगर (ptr < (व्योम *)__start_opd ||
			ptr >= (व्योम *)__end_opd)
		वापस ptr;

	वापस dereference_function_descriptor(ptr);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ brk_rnd(व्योम)
अणु
	वापस (get_अक्रमom_पूर्णांक() & BRK_RND_MASK) << PAGE_SHIFT;
पूर्ण

अचिन्हित दीर्घ arch_अक्रमomize_brk(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ ret = PAGE_ALIGN(mm->brk + brk_rnd());

	अगर (ret < mm->brk)
		वापस mm->brk;
	वापस ret;
पूर्ण
