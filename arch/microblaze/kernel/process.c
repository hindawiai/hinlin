<शैली गुरु>
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/pm.h>
#समावेश <linux/tick.h>
#समावेश <linux/bitops.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h> /* क्रम USER_DS macros */
#समावेश <यंत्र/cacheflush.h>

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_INFO);

	pr_info(" Registers dump: mode=%X\r\n", regs->pt_mode);
	pr_info(" r1=%08lX, r2=%08lX, r3=%08lX, r4=%08lX\n",
				regs->r1, regs->r2, regs->r3, regs->r4);
	pr_info(" r5=%08lX, r6=%08lX, r7=%08lX, r8=%08lX\n",
				regs->r5, regs->r6, regs->r7, regs->r8);
	pr_info(" r9=%08lX, r10=%08lX, r11=%08lX, r12=%08lX\n",
				regs->r9, regs->r10, regs->r11, regs->r12);
	pr_info(" r13=%08lX, r14=%08lX, r15=%08lX, r16=%08lX\n",
				regs->r13, regs->r14, regs->r15, regs->r16);
	pr_info(" r17=%08lX, r18=%08lX, r19=%08lX, r20=%08lX\n",
				regs->r17, regs->r18, regs->r19, regs->r20);
	pr_info(" r21=%08lX, r22=%08lX, r23=%08lX, r24=%08lX\n",
				regs->r21, regs->r22, regs->r23, regs->r24);
	pr_info(" r25=%08lX, r26=%08lX, r27=%08lX, r28=%08lX\n",
				regs->r25, regs->r26, regs->r27, regs->r28);
	pr_info(" r29=%08lX, r30=%08lX, r31=%08lX, rPC=%08lX\n",
				regs->r29, regs->r30, regs->r31, regs->pc);
	pr_info(" msr=%08lX, ear=%08lX, esr=%08lX, fsr=%08lX\n",
				regs->msr, regs->ear, regs->esr, regs->fsr);
पूर्ण

व्योम (*pm_घातer_off)(व्योम) = शून्य;
EXPORT_SYMBOL(pm_घातer_off);

व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs = task_pt_regs(p);
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* अगर we're creating a new kernel thपढ़ो then just zeroing all
		 * the रेजिस्टरs. That's OK क्रम a bअक्रम new thपढ़ो.*/
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		स_रखो(&ti->cpu_context, 0, माप(काष्ठा cpu_context));
		ti->cpu_context.r1  = (अचिन्हित दीर्घ)childregs;
		ti->cpu_context.r20 = (अचिन्हित दीर्घ)usp; /* fn */
		ti->cpu_context.r19 = (अचिन्हित दीर्घ)arg;
		childregs->pt_mode = 1;
		local_save_flags(childregs->msr);
		ti->cpu_context.msr = childregs->msr & ~MSR_IE;
		ti->cpu_context.r15 = (अचिन्हित दीर्घ)ret_from_kernel_thपढ़ो - 8;
		वापस 0;
	पूर्ण
	*childregs = *current_pt_regs();
	अगर (usp)
		childregs->r1 = usp;

	स_रखो(&ti->cpu_context, 0, माप(काष्ठा cpu_context));
	ti->cpu_context.r1 = (अचिन्हित दीर्घ)childregs;
	childregs->msr |= MSR_UMS;

	/* we should consider the fact that childregs is a copy of the parent
	 * regs which were saved immediately after entering the kernel state
	 * beक्रमe enabling VM. This MSR will be restored in चयन_to and
	 * RETURN() and we want to have the right machine state there
	 * specअगरically this state must have INTs disabled beक्रमe and enabled
	 * after perक्रमming rtbd
	 * compose the right MSR क्रम RETURN(). It will work क्रम चयन_to also
	 * excepting क्रम VM and UMS
	 * करोn't touch UMS , CARRY and cache bits
	 * right now MSR is a copy of parent one */
	childregs->msr &= ~MSR_EIP;
	childregs->msr |= MSR_IE;
	childregs->msr &= ~MSR_VM;
	childregs->msr |= MSR_VMS;
	childregs->msr |= MSR_EE; /* exceptions will be enabled*/

	ti->cpu_context.msr = (childregs->msr|MSR_VM);
	ti->cpu_context.msr &= ~MSR_UMS; /* चयन_to to kernel mode */
	ti->cpu_context.msr &= ~MSR_IE;
	ti->cpu_context.r15 = (अचिन्हित दीर्घ)ret_from_विभाजन - 8;

	/*
	 *  r21 is the thपढ़ो reg, r10 is 6th arg to clone
	 *  which contains TLS area
	 */
	अगर (clone_flags & CLONE_SETTLS)
		childregs->r21 = tls;

	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
/* TBD (used by procfs) */
	वापस 0;
पूर्ण

/* Set up a thपढ़ो क्रम executing a new program */
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ usp)
अणु
	regs->pc = pc;
	regs->r1 = usp;
	regs->pt_mode = 0;
	regs->msr |= MSR_UMS;
	regs->msr &= ~MSR_VM;
पूर्ण

#समावेश <linux/elfcore.h>
/*
 * Set up a thपढ़ो क्रम executing a new program
 */
पूर्णांक dump_fpu(काष्ठा pt_regs *regs, elf_fpregset_t *fpregs)
अणु
	वापस 0; /* MicroBlaze has no separate FPU रेजिस्टरs */
पूर्ण

व्योम arch_cpu_idle(व्योम)
अणु
       raw_local_irq_enable();
पूर्ण
