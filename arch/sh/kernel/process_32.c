<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/process.c
 *
 * This file handles the architecture-dependent parts of process handling..
 *
 *  Copyright (C) 1995  Linus Torvalds
 *
 *  SuperH version:  Copyright (C) 1999, 2000  Niibe Yutaka & Kaz Kojima
 *		     Copyright (C) 2006 Lineo Solutions Inc. support SH4A UBC
 *		     Copyright (C) 2002 - 2008  Paul Mundt
 */
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/fs.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/stackprotector.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/चयन_to.h>

व्योम show_regs(काष्ठा pt_regs * regs)
अणु
	pr_info("\n");
	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	pr_info("PC is at %pS\n", (व्योम *)inकाष्ठाion_poपूर्णांकer(regs));
	pr_info("PR is at %pS\n", (व्योम *)regs->pr);

	pr_info("PC  : %08lx SP  : %08lx SR  : %08lx ", regs->pc,
		regs->regs[15], regs->sr);
#अगर_घोषित CONFIG_MMU
	pr_cont("TEA : %08x\n", __raw_पढ़ोl(MMU_TEA));
#अन्यथा
	pr_cont("\n");
#पूर्ण_अगर

	pr_info("R0  : %08lx R1  : %08lx R2  : %08lx R3  : %08lx\n",
		regs->regs[0], regs->regs[1], regs->regs[2], regs->regs[3]);
	pr_info("R4  : %08lx R5  : %08lx R6  : %08lx R7  : %08lx\n",
		regs->regs[4], regs->regs[5], regs->regs[6], regs->regs[7]);
	pr_info("R8  : %08lx R9  : %08lx R10 : %08lx R11 : %08lx\n",
		regs->regs[8], regs->regs[9], regs->regs[10], regs->regs[11]);
	pr_info("R12 : %08lx R13 : %08lx R14 : %08lx\n",
		regs->regs[12], regs->regs[13], regs->regs[14]);
	pr_info("MACH: %08lx MACL: %08lx GBR : %08lx PR  : %08lx\n",
		regs->mach, regs->macl, regs->gbr, regs->pr);

	show_trace(शून्य, (अचिन्हित दीर्घ *)regs->regs[15], regs, KERN_DEFAULT);
	show_code(regs);
पूर्ण

व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ new_pc,
		  अचिन्हित दीर्घ new_sp)
अणु
	regs->pr = 0;
	regs->sr = SR_FD;
	regs->pc = new_pc;
	regs->regs[15] = new_sp;

	मुक्त_thपढ़ो_xstate(current);
पूर्ण
EXPORT_SYMBOL(start_thपढ़ो);

व्योम flush_thपढ़ो(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	flush_ptrace_hw_अवरोधpoपूर्णांक(tsk);

#अगर defined(CONFIG_SH_FPU)
	/* Forget lazy FPU state */
	clear_fpu(tsk, task_pt_regs(tsk));
	clear_used_math();
#पूर्ण_अगर
पूर्ण

व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
	/* करो nothing */
पूर्ण

यंत्रlinkage व्योम ret_from_विभाजन(व्योम);
यंत्रlinkage व्योम ret_from_kernel_thपढ़ो(व्योम);

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);
	काष्ठा pt_regs *childregs;

#अगर defined(CONFIG_SH_DSP)
	काष्ठा task_काष्ठा *tsk = current;

	अगर (is_dsp_enabled(tsk)) अणु
		/* We can use the __save_dsp or just copy the काष्ठा:
		 * __save_dsp(p);
		 * p->thपढ़ो.dsp_status.status |= SR_DSP
		 */
		p->thपढ़ो.dsp_status = tsk->thपढ़ो.dsp_status;
	पूर्ण
#पूर्ण_अगर

	स_रखो(p->thपढ़ो.ptrace_bps, 0, माप(p->thपढ़ो.ptrace_bps));

	childregs = task_pt_regs(p);
	p->thपढ़ो.sp = (अचिन्हित दीर्घ) childregs;
	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		p->thपढ़ो.pc = (अचिन्हित दीर्घ) ret_from_kernel_thपढ़ो;
		childregs->regs[4] = arg;
		childregs->regs[5] = usp;
		childregs->sr = SR_MD;
#अगर defined(CONFIG_SH_FPU)
		childregs->sr |= SR_FD;
#पूर्ण_अगर
		ti->addr_limit = KERNEL_DS;
		ti->status &= ~TS_USEDFPU;
		p->thपढ़ो.fpu_counter = 0;
		वापस 0;
	पूर्ण
	*childregs = *current_pt_regs();

	अगर (usp)
		childregs->regs[15] = usp;
	ti->addr_limit = USER_DS;

	अगर (clone_flags & CLONE_SETTLS)
		childregs->gbr = tls;

	childregs->regs[0] = 0; /* Set वापस value क्रम child */
	p->thपढ़ो.pc = (अचिन्हित दीर्घ) ret_from_विभाजन;
	वापस 0;
पूर्ण

/*
 *	चयन_to(x,y) should चयन tasks from x to y.
 *
 */
__notrace_funcgraph काष्ठा task_काष्ठा *
__चयन_to(काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	काष्ठा thपढ़ो_काष्ठा *next_t = &next->thपढ़ो;

#अगर defined(CONFIG_STACKPROTECTOR) && !defined(CONFIG_SMP)
	__stack_chk_guard = next->stack_canary;
#पूर्ण_अगर

	unlazy_fpu(prev, task_pt_regs(prev));

	/* we're going to use this soon, after a few expensive things */
	अगर (next->thपढ़ो.fpu_counter > 5)
		prefetch(next_t->xstate);

#अगर_घोषित CONFIG_MMU
	/*
	 * Restore the kernel mode रेजिस्टर
	 *	k7 (r7_bank1)
	 */
	यंत्र अस्थिर("ldc	%0, r7_bank"
		     : /* no output */
		     : "r" (task_thपढ़ो_info(next)));
#पूर्ण_अगर

	/*
	 * If the task has used fpu the last 5 बारlices, just करो a full
	 * restore of the math state immediately to aव्योम the trap; the
	 * chances of needing FPU soon are obviously high now
	 */
	अगर (next->thपढ़ो.fpu_counter > 5)
		__fpu_state_restore();

	वापस prev;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ pc;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	/*
	 * The same comment as on the Alpha applies here, too ...
	 */
	pc = thपढ़ो_saved_pc(p);

#अगर_घोषित CONFIG_FRAME_POINTER
	अगर (in_sched_functions(pc)) अणु
		अचिन्हित दीर्घ schedule_frame = (अचिन्हित दीर्घ)p->thपढ़ो.sp;
		वापस ((अचिन्हित दीर्घ *)schedule_frame)[21];
	पूर्ण
#पूर्ण_अगर

	वापस pc;
पूर्ण
