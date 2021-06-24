<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC process.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 * This file handles the architecture-dependent parts of process handling...
 */

#घोषणा __KERNEL_SYSCALLS__
#समावेश <मानकतर्क.स>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/init_task.h>
#समावेश <linux/mqueue.h>
#समावेश <linux/fs.h>
#समावेश <linux/reboot.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/spr_defs.h>

#समावेश <linux/smp.h>

/*
 * Poपूर्णांकer to Current thपढ़ो info काष्ठाure.
 *
 * Used at user space -> kernel transitions.
 */
काष्ठा thपढ़ो_info *current_thपढ़ो_info_set[NR_CPUS] = अणु &init_thपढ़ो_info, पूर्ण;

व्योम machine_restart(अक्षर *cmd)
अणु
	करो_kernel_restart(cmd);

	/* Give a grace period क्रम failure to restart of 1s */
	mdelay(1000);

	/* Whoops - the platक्रमm was unable to reboot. Tell the user! */
	pr_emerg("Reboot failed -- System halted\n");
	जबतक (1);
पूर्ण

/*
 * Similar to machine_घातer_off, but करोn't shut off घातer.  Add code
 * here to मुक्तze the प्रणाली क्रम e.g. post-mortem debug purpose when
 * possible.  This halt has nothing to करो with the idle halt.
 */
व्योम machine_halt(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "*** MACHINE HALT ***\n");
	__यंत्र__("l.nop 1");
पूर्ण

/* If or when software घातer-off is implemented, add code here.  */
व्योम machine_घातer_off(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "*** MACHINE POWER OFF ***\n");
	__यंत्र__("l.nop 1");
पूर्ण

/*
 * Send the करोze संकेत to the cpu अगर available.
 * Make sure, that all पूर्णांकerrupts are enabled
 */
व्योम arch_cpu_idle(व्योम)
अणु
	raw_local_irq_enable();
	अगर (mfspr(SPR_UPR) & SPR_UPR_PMP)
		mtspr(SPR_PMR, mfspr(SPR_PMR) | SPR_PMR_DME);
पूर्ण

व्योम (*pm_घातer_off) (व्योम) = machine_घातer_off;
EXPORT_SYMBOL(pm_घातer_off);

/*
 * When a process करोes an "exec", machine state like FPU and debug
 * रेजिस्टरs need to be reset.  This is a hook function क्रम that.
 * Currently we करोn't have any such state to reset, so this is empty.
 */
व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	बाह्य व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs);

	show_regs_prपूर्णांक_info(KERN_DEFAULT);
	/* __PHX__ cleanup this mess */
	show_रेजिस्टरs(regs);
पूर्ण

व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

/*
 * Copy the thपढ़ो-specअगरic (arch specअगरic) info from the current
 * process to the new one p
 */
बाह्य यंत्रlinkage व्योम ret_from_विभाजन(व्योम);

/*
 * copy_thपढ़ो
 * @clone_flags: flags
 * @usp: user stack poपूर्णांकer or fn क्रम kernel thपढ़ो
 * @arg: arg to fn क्रम kernel thपढ़ो; always शून्य क्रम userspace thपढ़ो
 * @p: the newly created task
 * @tls: the Thपढ़ो Local Storage poपूर्णांकer क्रम the new process
 *
 * At the top of a newly initialized kernel stack are two stacked pt_reg
 * काष्ठाures.  The first (topmost) is the userspace context of the thपढ़ो.
 * The second is the kernelspace context of the thपढ़ो.
 *
 * A kernel thपढ़ो will not be वापसing to userspace, so the topmost pt_regs
 * काष्ठा can be uninitialized; it _करोes_ need to exist, though, because
 * a kernel thपढ़ो can become a userspace thपढ़ो by करोing a kernel_execve, in
 * which हाल the topmost context will be initialized and used क्रम 'returning'
 * to userspace.
 *
 * The second pt_reg काष्ठा needs to be initialized to 'return' to
 * ret_from_विभाजन.  A kernel thपढ़ो will need to set r20 to the address of
 * a function to call पूर्णांकo (with arg in r22); userspace thपढ़ोs need to set
 * r20 to शून्य in which हाल ret_from_विभाजन will just जारी a वापस to
 * userspace.
 *
 * A kernel thपढ़ो 'fn' may वापस; this is effectively what happens when
 * kernel_execve is called.  In that हाल, the userspace pt_regs must have
 * been initialized (which kernel_execve takes care of, see start_thपढ़ो
 * below); ret_from_विभाजन will then जारी its execution causing the
 * 'kernel thread' to वापस to userspace as a userspace thपढ़ो.
 */

पूर्णांक
copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp, अचिन्हित दीर्घ arg,
	    काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *userregs;
	काष्ठा pt_regs *kregs;
	अचिन्हित दीर्घ sp = (अचिन्हित दीर्घ)task_stack_page(p) + THREAD_SIZE;
	अचिन्हित दीर्घ top_of_kernel_stack;

	top_of_kernel_stack = sp;

	/* Locate userspace context on stack... */
	sp -= STACK_FRAME_OVERHEAD;	/* redzone */
	sp -= माप(काष्ठा pt_regs);
	userregs = (काष्ठा pt_regs *) sp;

	/* ...and kernel context */
	sp -= STACK_FRAME_OVERHEAD;	/* redzone */
	sp -= माप(काष्ठा pt_regs);
	kregs = (काष्ठा pt_regs *)sp;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(kregs, 0, माप(काष्ठा pt_regs));
		kregs->gpr[20] = usp; /* fn, kernel thपढ़ो */
		kregs->gpr[22] = arg;
	पूर्ण अन्यथा अणु
		*userregs = *current_pt_regs();

		अगर (usp)
			userregs->sp = usp;

		/*
		 * For CLONE_SETTLS set "tp" (r10) to the TLS poपूर्णांकer.
		 */
		अगर (clone_flags & CLONE_SETTLS)
			userregs->gpr[10] = tls;

		userregs->gpr[11] = 0;	/* Result from विभाजन() */

		kregs->gpr[20] = 0;	/* Userspace thपढ़ो */
	पूर्ण

	/*
	 * _चयन wants the kernel stack page in pt_regs->sp so that it
	 * can restore it to thपढ़ो_info->ksp... see _चयन क्रम details.
	 */
	kregs->sp = top_of_kernel_stack;
	kregs->gpr[9] = (अचिन्हित दीर्घ)ret_from_विभाजन;

	task_thपढ़ो_info(p)->ksp = (अचिन्हित दीर्घ)kregs;

	वापस 0;
पूर्ण

/*
 * Set up a thपढ़ो क्रम executing a new program
 */
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ sr = mfspr(SPR_SR) & ~SPR_SR_SM;

	स_रखो(regs, 0, माप(काष्ठा pt_regs));

	regs->pc = pc;
	regs->sr = sr;
	regs->sp = sp;
पूर्ण

बाह्य काष्ठा thपढ़ो_info *_चयन(काष्ठा thपढ़ो_info *old_ti,
				   काष्ठा thपढ़ो_info *new_ti);
बाह्य पूर्णांक lwa_flag;

काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *old,
				काष्ठा task_काष्ठा *new)
अणु
	काष्ठा task_काष्ठा *last;
	काष्ठा thपढ़ो_info *new_ti, *old_ti;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* current_set is an array of saved current poपूर्णांकers
	 * (one क्रम each cpu). we need them at user->kernel transition,
	 * जबतक we save them at kernel->user transition
	 */
	new_ti = new->stack;
	old_ti = old->stack;

	lwa_flag = 0;

	current_thपढ़ो_info_set[smp_processor_id()] = new_ti;
	last = (_चयन(old_ti, new_ti))->task;

	local_irq_restore(flags);

	वापस last;
पूर्ण

/*
 * Write out रेजिस्टरs in core dump क्रमmat, as defined by the
 * काष्ठा user_regs_काष्ठा
 */
व्योम dump_elf_thपढ़ो(elf_greg_t *dest, काष्ठा pt_regs* regs)
अणु
	dest[0] = 0; /* r0 */
	स_नकल(dest+1, regs->gpr+1, 31*माप(अचिन्हित दीर्घ));
	dest[32] = regs->pc;
	dest[33] = regs->sr;
	dest[34] = 0;
	dest[35] = 0;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	/* TODO */

	वापस 0;
पूर्ण
