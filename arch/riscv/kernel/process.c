<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Sunplus Core Technology Co., Ltd.
 *  Chen Liqin <liqin.chen@sunplusct.com>
 *  Lennox Wu <lennox.wu@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/tick.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/csr.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/thपढ़ो_info.h>

रेजिस्टर अचिन्हित दीर्घ gp_in_global __यंत्र__("gp");

#अगर defined(CONFIG_STACKPROTECTOR) && !defined(CONFIG_STACKPROTECTOR_PER_TASK)
#समावेश <linux/stackprotector.h>
अचिन्हित दीर्घ __stack_chk_guard __पढ़ो_mostly;
EXPORT_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

बाह्य यंत्रlinkage व्योम ret_from_विभाजन(व्योम);
बाह्य यंत्रlinkage व्योम ret_from_kernel_thपढ़ो(व्योम);

व्योम arch_cpu_idle(व्योम)
अणु
	रुको_क्रम_पूर्णांकerrupt();
	raw_local_irq_enable();
पूर्ण

व्योम __show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	अगर (!user_mode(regs)) अणु
		pr_cont("epc : %pS\n", (व्योम *)regs->epc);
		pr_cont(" ra : %pS\n", (व्योम *)regs->ra);
	पूर्ण

	pr_cont("epc : " REG_FMT " ra : " REG_FMT " sp : " REG_FMT "\n",
		regs->epc, regs->ra, regs->sp);
	pr_cont(" gp : " REG_FMT " tp : " REG_FMT " t0 : " REG_FMT "\n",
		regs->gp, regs->tp, regs->t0);
	pr_cont(" t1 : " REG_FMT " t2 : " REG_FMT " s0 : " REG_FMT "\n",
		regs->t1, regs->t2, regs->s0);
	pr_cont(" s1 : " REG_FMT " a0 : " REG_FMT " a1 : " REG_FMT "\n",
		regs->s1, regs->a0, regs->a1);
	pr_cont(" a2 : " REG_FMT " a3 : " REG_FMT " a4 : " REG_FMT "\n",
		regs->a2, regs->a3, regs->a4);
	pr_cont(" a5 : " REG_FMT " a6 : " REG_FMT " a7 : " REG_FMT "\n",
		regs->a5, regs->a6, regs->a7);
	pr_cont(" s2 : " REG_FMT " s3 : " REG_FMT " s4 : " REG_FMT "\n",
		regs->s2, regs->s3, regs->s4);
	pr_cont(" s5 : " REG_FMT " s6 : " REG_FMT " s7 : " REG_FMT "\n",
		regs->s5, regs->s6, regs->s7);
	pr_cont(" s8 : " REG_FMT " s9 : " REG_FMT " s10: " REG_FMT "\n",
		regs->s8, regs->s9, regs->s10);
	pr_cont(" s11: " REG_FMT " t3 : " REG_FMT " t4 : " REG_FMT "\n",
		regs->s11, regs->t3, regs->t4);
	pr_cont(" t5 : " REG_FMT " t6 : " REG_FMT "\n",
		regs->t5, regs->t6);

	pr_cont("status: " REG_FMT " badaddr: " REG_FMT " cause: " REG_FMT "\n",
		regs->status, regs->badaddr, regs->cause);
पूर्ण
व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	__show_regs(regs);
	अगर (!user_mode(regs))
		dump_backtrace(regs, शून्य, KERN_DEFAULT);
पूर्ण

व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
	अचिन्हित दीर्घ sp)
अणु
	regs->status = SR_PIE;
	अगर (has_fpu) अणु
		regs->status |= SR_FS_INITIAL;
		/*
		 * Restore the initial value to the FP रेजिस्टर
		 * beक्रमe starting the user program.
		 */
		ख_स्थितिe_restore(current, regs);
	पूर्ण
	regs->epc = pc;
	regs->sp = sp;
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
#अगर_घोषित CONFIG_FPU
	/*
	 * Reset FPU state and context
	 *	frm: round to nearest, ties to even (IEEE शेष)
	 *	fflags: accrued exceptions cleared
	 */
	ख_स्थितिe_off(current, task_pt_regs(current));
	स_रखो(&current->thपढ़ो.ख_स्थितिe, 0, माप(current->thपढ़ो.ख_स्थितिe));
#पूर्ण_अगर
पूर्ण

पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	ख_स्थितिe_save(src, task_pt_regs(src));
	*dst = *src;
	वापस 0;
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs = task_pt_regs(p);

	/* p->thपढ़ो holds context to be restored by __चयन_to() */
	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* Kernel thपढ़ो */
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		childregs->gp = gp_in_global;
		/* Supervisor/Machine, irqs on: */
		childregs->status = SR_PP | SR_PIE;

		p->thपढ़ो.ra = (अचिन्हित दीर्घ)ret_from_kernel_thपढ़ो;
		p->thपढ़ो.s[0] = usp; /* fn */
		p->thपढ़ो.s[1] = arg;
	पूर्ण अन्यथा अणु
		*childregs = *(current_pt_regs());
		अगर (usp) /* User विभाजन */
			childregs->sp = usp;
		अगर (clone_flags & CLONE_SETTLS)
			childregs->tp = tls;
		childregs->a0 = 0; /* Return value of विभाजन() */
		p->thपढ़ो.ra = (अचिन्हित दीर्घ)ret_from_विभाजन;
	पूर्ण
	p->thपढ़ो.sp = (अचिन्हित दीर्घ)childregs; /* kernel sp */
	वापस 0;
पूर्ण
