<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/process.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 */

/*
 * This file handles the architecture-dependent parts of process handling.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/समय.स>
#समावेश <linux/major.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/vt.h>
#समावेश <linux/mman.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/reboot.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>

#समावेश <यंत्र/reg.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/fpu.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"

/*
 * Power off function, अगर any
 */
व्योम (*pm_घातer_off)(व्योम) = machine_घातer_off;
EXPORT_SYMBOL(pm_घातer_off);

#अगर_घोषित CONFIG_ALPHA_WTINT
/*
 * Sleep the CPU.
 * EV6, LCA45 and QEMU know how to घातer करोwn, skipping N समयr पूर्णांकerrupts.
 */
व्योम arch_cpu_idle(व्योम)
अणु
	wtपूर्णांक(0);
	raw_local_irq_enable();
पूर्ण

व्योम arch_cpu_idle_dead(व्योम)
अणु
	wtपूर्णांक(पूर्णांक_उच्च);
पूर्ण
#पूर्ण_अगर /* ALPHA_WTINT */

काष्ठा halt_info अणु
	पूर्णांक mode;
	अक्षर *restart_cmd;
पूर्ण;

अटल व्योम
common_shutकरोwn_1(व्योम *generic_ptr)
अणु
	काष्ठा halt_info *how = (काष्ठा halt_info *)generic_ptr;
	काष्ठा percpu_काष्ठा *cpup;
	अचिन्हित दीर्घ *pflags, flags;
	पूर्णांक cpuid = smp_processor_id();

	/* No poपूर्णांक in taking पूर्णांकerrupts anymore. */
	local_irq_disable();

	cpup = (काष्ठा percpu_काष्ठा *)
			((अचिन्हित दीर्घ)hwrpb + hwrpb->processor_offset
			 + hwrpb->processor_size * cpuid);
	pflags = &cpup->flags;
	flags = *pflags;

	/* Clear reason to "default"; clear "bootstrap in progress". */
	flags &= ~0x00ff0001UL;

#अगर_घोषित CONFIG_SMP
	/* Secondaries halt here. */
	अगर (cpuid != boot_cpuid) अणु
		flags |= 0x00040000UL; /* "remain halted" */
		*pflags = flags;
		set_cpu_present(cpuid, false);
		set_cpu_possible(cpuid, false);
		halt();
	पूर्ण
#पूर्ण_अगर

	अगर (how->mode == LINUX_REBOOT_CMD_RESTART) अणु
		अगर (!how->restart_cmd) अणु
			flags |= 0x00020000UL; /* "cold bootstrap" */
		पूर्ण अन्यथा अणु
			/* For SRM, we could probably set environment
			   variables to get this to work.  We'd have to
			   delay this until after srm_paging_stop unless
			   we ever got srm_fixup working.

			   At the moment, SRM will use the last boot device,
			   but the file and flags will be the शेषs, when
			   करोing a "warm" bootstrap.  */
			flags |= 0x00030000UL; /* "warm bootstrap" */
		पूर्ण
	पूर्ण अन्यथा अणु
		flags |= 0x00040000UL; /* "remain halted" */
	पूर्ण
	*pflags = flags;

#अगर_घोषित CONFIG_SMP
	/* Wait क्रम the secondaries to halt. */
	set_cpu_present(boot_cpuid, false);
	set_cpu_possible(boot_cpuid, false);
	जबतक (cpumask_weight(cpu_present_mask))
		barrier();
#पूर्ण_अगर

	/* If booted from SRM, reset some of the original environment. */
	अगर (alpha_using_srm) अणु
#अगर_घोषित CONFIG_DUMMY_CONSOLE
		/* If we've gotten here after SysRq-b, leave पूर्णांकerrupt
		   context beक्रमe taking over the console. */
		अगर (in_irq())
			irq_निकास();
		/* This has the effect of resetting the VGA video origin.  */
		console_lock();
		करो_take_over_console(&dummy_con, 0, MAX_NR_CONSOLES-1, 1);
		console_unlock();
#पूर्ण_अगर
		pci_restore_srm_config();
		set_hae(srm_hae);
	पूर्ण

	अगर (alpha_mv.समाप्त_arch)
		alpha_mv.समाप्त_arch(how->mode);

	अगर (! alpha_using_srm && how->mode != LINUX_REBOOT_CMD_RESTART) अणु
		/* Unक्रमtunately, since MILO करोesn't currently understand
		   the hwrpb bits above, we can't reliably halt the 
		   processor and keep it halted.  So just loop.  */
		वापस;
	पूर्ण

	अगर (alpha_using_srm)
		srm_paging_stop();

	halt();
पूर्ण

अटल व्योम
common_shutकरोwn(पूर्णांक mode, अक्षर *restart_cmd)
अणु
	काष्ठा halt_info args;
	args.mode = mode;
	args.restart_cmd = restart_cmd;
	on_each_cpu(common_shutकरोwn_1, &args, 0);
पूर्ण

व्योम
machine_restart(अक्षर *restart_cmd)
अणु
	common_shutकरोwn(LINUX_REBOOT_CMD_RESTART, restart_cmd);
पूर्ण


व्योम
machine_halt(व्योम)
अणु
	common_shutकरोwn(LINUX_REBOOT_CMD_HALT, शून्य);
पूर्ण


व्योम
machine_घातer_off(व्योम)
अणु
	common_shutकरोwn(LINUX_REBOOT_CMD_POWER_OFF, शून्य);
पूर्ण


/* Used by sysrq-p, among others.  I करोn't believe r9-r15 are ever
   saved in the context it's used.  */

व्योम
show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_DEFAULT);
	dik_show_regs(regs, शून्य);
पूर्ण

/*
 * Re-start a thपढ़ो when करोing execve()
 */
व्योम
start_thपढ़ो(काष्ठा pt_regs * regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp)
अणु
	regs->pc = pc;
	regs->ps = 8;
	wrusp(sp);
पूर्ण
EXPORT_SYMBOL(start_thपढ़ो);

व्योम
flush_thपढ़ो(व्योम)
अणु
	/* Arrange क्रम each exec'ed process to start off with a clean slate
	   with respect to the FPU.  This is all exceptions disabled.  */
	current_thपढ़ो_info()->ieee_state = 0;
	wrfpcr(FPCR_DYN_NORMAL | ieee_swcr_to_fpcr(0));

	/* Clean slate क्रम TLS.  */
	current_thपढ़ो_info()->pcb.unique = 0;
पूर्ण

व्योम
release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

/*
 * Copy architecture-specअगरic thपढ़ो state
 */
पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp,
		अचिन्हित दीर्घ kthपढ़ो_arg, काष्ठा task_काष्ठा *p,
		अचिन्हित दीर्घ tls)
अणु
	बाह्य व्योम ret_from_विभाजन(व्योम);
	बाह्य व्योम ret_from_kernel_thपढ़ो(व्योम);

	काष्ठा thपढ़ो_info *childti = task_thपढ़ो_info(p);
	काष्ठा pt_regs *childregs = task_pt_regs(p);
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा चयन_stack *childstack, *stack;

	childstack = ((काष्ठा चयन_stack *) childregs) - 1;
	childti->pcb.ksp = (अचिन्हित दीर्घ) childstack;
	childti->pcb.flags = 1;	/* set FEN, clear everything अन्यथा */

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* kernel thपढ़ो */
		स_रखो(childstack, 0,
			माप(काष्ठा चयन_stack) + माप(काष्ठा pt_regs));
		childstack->r26 = (अचिन्हित दीर्घ) ret_from_kernel_thपढ़ो;
		childstack->r9 = usp;	/* function */
		childstack->r10 = kthपढ़ो_arg;
		childregs->hae = alpha_mv.hae_cache,
		childti->pcb.usp = 0;
		वापस 0;
	पूर्ण
	/* Note: अगर CLONE_SETTLS is not set, then we must inherit the
	   value from the parent, which will have been set by the block
	   copy in dup_task_काष्ठा.  This is non-पूर्णांकuitive, but is
	   required क्रम proper operation in the हाल of a thपढ़ोed
	   application calling विभाजन.  */
	अगर (clone_flags & CLONE_SETTLS)
		childti->pcb.unique = tls;
	अन्यथा
		regs->r20 = 0;	/* OSF/1 has some strange विभाजन() semantics.  */
	childti->pcb.usp = usp ?: rdusp();
	*childregs = *regs;
	childregs->r0 = 0;
	childregs->r19 = 0;
	childregs->r20 = 1;	/* OSF/1 has some strange विभाजन() semantics.  */
	stack = ((काष्ठा चयन_stack *) regs) - 1;
	*childstack = *stack;
	childstack->r26 = (अचिन्हित दीर्घ) ret_from_विभाजन;
	वापस 0;
पूर्ण

/*
 * Fill in the user काष्ठाure क्रम a ELF core dump.
 */
व्योम
dump_elf_thपढ़ो(elf_greg_t *dest, काष्ठा pt_regs *pt, काष्ठा thपढ़ो_info *ti)
अणु
	/* चयन stack follows right below pt_regs: */
	काष्ठा चयन_stack * sw = ((काष्ठा चयन_stack *) pt) - 1;

	dest[ 0] = pt->r0;
	dest[ 1] = pt->r1;
	dest[ 2] = pt->r2;
	dest[ 3] = pt->r3;
	dest[ 4] = pt->r4;
	dest[ 5] = pt->r5;
	dest[ 6] = pt->r6;
	dest[ 7] = pt->r7;
	dest[ 8] = pt->r8;
	dest[ 9] = sw->r9;
	dest[10] = sw->r10;
	dest[11] = sw->r11;
	dest[12] = sw->r12;
	dest[13] = sw->r13;
	dest[14] = sw->r14;
	dest[15] = sw->r15;
	dest[16] = pt->r16;
	dest[17] = pt->r17;
	dest[18] = pt->r18;
	dest[19] = pt->r19;
	dest[20] = pt->r20;
	dest[21] = pt->r21;
	dest[22] = pt->r22;
	dest[23] = pt->r23;
	dest[24] = pt->r24;
	dest[25] = pt->r25;
	dest[26] = pt->r26;
	dest[27] = pt->r27;
	dest[28] = pt->r28;
	dest[29] = pt->gp;
	dest[30] = ti == current_thपढ़ो_info() ? rdusp() : ti->pcb.usp;
	dest[31] = pt->pc;

	/* Once upon a समय this was the PS value.  Which is stupid
	   since that is always 8 क्रम usermode.  Usurped क्रम the more
	   useful value of the thपढ़ो's UNIQUE field.  */
	dest[32] = ti->pcb.unique;
पूर्ण
EXPORT_SYMBOL(dump_elf_thपढ़ो);

पूर्णांक
dump_elf_task(elf_greg_t *dest, काष्ठा task_काष्ठा *task)
अणु
	dump_elf_thपढ़ो(dest, task_pt_regs(task), task_thपढ़ो_info(task));
	वापस 1;
पूर्ण
EXPORT_SYMBOL(dump_elf_task);

पूर्णांक
dump_elf_task_fp(elf_fpreg_t *dest, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)task_pt_regs(task) - 1;
	स_नकल(dest, sw->fp, 32 * 8);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(dump_elf_task_fp);

/*
 * Return saved PC of a blocked thपढ़ो.  This assumes the frame
 * poपूर्णांकer is the 6th saved दीर्घ on the kernel stack and that the
 * saved वापस address is the first दीर्घ in the frame.  This all
 * holds provided the thपढ़ो blocked through a call to schedule() ($15
 * is the frame poपूर्णांकer in schedule() and $15 is saved at offset 48 by
 * entry.S:करो_चयन_stack).
 *
 * Under heavy swap load I've seen this lose in an ugly way.  So करो
 * some extra sanity checking on the ranges we expect these poपूर्णांकers
 * to be in so that we can fail gracefully.  This is just क्रम ps after
 * all.  -- r~
 */

अटल अचिन्हित दीर्घ
thपढ़ो_saved_pc(काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)task_stack_page(t);
	अचिन्हित दीर्घ fp, sp = task_thपढ़ो_info(t)->pcb.ksp;

	अगर (sp > base && sp+6*8 < base + 16*1024) अणु
		fp = ((अचिन्हित दीर्घ*)sp)[6];
		अगर (fp > sp && fp < base + 16*1024)
			वापस *(अचिन्हित दीर्घ *)fp;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित दीर्घ
get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ schedule_frame;
	अचिन्हित दीर्घ pc;
	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;
	/*
	 * This one depends on the frame size of schedule().  Do a
	 * "disass schedule" in gdb to find the frame size.  Also, the
	 * code assumes that sleep_on() follows immediately after
	 * पूर्णांकerruptible_sleep_on() and that add_समयr() follows
	 * immediately after पूर्णांकerruptible_sleep().  Ugly, isn't it?
	 * Maybe adding a wchan field to task_काष्ठा would be better,
	 * after all...
	 */

	pc = thपढ़ो_saved_pc(p);
	अगर (in_sched_functions(pc)) अणु
		schedule_frame = ((अचिन्हित दीर्घ *)task_thपढ़ो_info(p)->pcb.ksp)[6];
		वापस ((अचिन्हित दीर्घ *)schedule_frame)[12];
	पूर्ण
	वापस pc;
पूर्ण
