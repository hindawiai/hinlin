<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Process creation support क्रम Hexagon
 *
 * Copyright (c) 2010-2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/tick.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/tracehook.h>

/*
 * Program thपढ़ो launch.  Often defined as a macro in processor.h,
 * but we're shooting for a small footprint and it's not an inner-loop
 * perक्रमmance-critical operation.
 *
 * The Hexagon ABI specअगरies that R28 is zero'ed beक्रमe program launch,
 * so that माला_लो स्वतःmatically करोne here.  If we ever stop करोing that here,
 * we'll probably want to define the ELF_PLAT_INIT macro.
 */
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp)
अणु
	/* We want to zero all data-containing रेजिस्टरs. Is this overसमाप्त? */
	स_रखो(regs, 0, माप(*regs));
	/* We might want to also zero all Processor रेजिस्टरs here */
	pt_set_usermode(regs);
	pt_set_elr(regs, pc);
	pt_set_rte_sp(regs, sp);
पूर्ण

/*
 *  Spin, or better still, करो a hardware or VM रुको inकाष्ठाion
 *  If hardware or VM offer रुको termination even though पूर्णांकerrupts
 *  are disabled.
 */
व्योम arch_cpu_idle(व्योम)
अणु
	__vmरुको();
	/*  पूर्णांकerrupts wake us up, but irqs are still disabled */
	raw_local_irq_enable();
पूर्ण

/*
 * Copy architecture-specअगरic thपढ़ो state
 */
पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);
	काष्ठा hexagon_चयन_stack *ss;
	काष्ठा pt_regs *childregs;
	यंत्रlinkage व्योम ret_from_विभाजन(व्योम);

	childregs = (काष्ठा pt_regs *) (((अचिन्हित दीर्घ) ti + THREAD_SIZE) -
					माप(*childregs));

	ti->regs = childregs;

	/*
	 * Establish kernel stack poपूर्णांकer and initial PC क्रम new thपढ़ो
	 * Note that unlike the usual situation, we करो not copy the
	 * parent's callee-saved here; those are in pt_regs and whatever
	 * we leave here will be overridden on वापस to userland.
	 */
	ss = (काष्ठा hexagon_चयन_stack *) ((अचिन्हित दीर्घ) childregs -
						    माप(*ss));
	ss->lr = (अचिन्हित दीर्घ)ret_from_विभाजन;
	p->thपढ़ो.चयन_sp = ss;
	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		/* r24 <- fn, r25 <- arg */
		ss->r24 = usp;
		ss->r25 = arg;
		pt_set_kmode(childregs);
		वापस 0;
	पूर्ण
	स_नकल(childregs, current_pt_regs(), माप(*childregs));
	ss->r2524 = 0;

	अगर (usp)
		pt_set_rte_sp(childregs, usp);

	/* Child sees zero वापस value */
	childregs->r00 = 0;

	/*
	 * The clone syscall has the C signature:
	 * पूर्णांक [r0] clone(पूर्णांक flags [r0],
	 *           व्योम *child_frame [r1],
	 *           व्योम *parent_tid [r2],
	 *           व्योम *child_tid [r3],
	 *           व्योम *thपढ़ो_control_block [r4]);
	 * ugp is used to provide TLS support.
	 */
	अगर (clone_flags & CLONE_SETTLS)
		childregs->ugp = tls;

	/*
	 * Parent sees new pid -- not necessary, not even possible at
	 * this poपूर्णांक in the विभाजन process
	 * Might also want to set things like ti->addr_limit
	 */

	वापस 0;
पूर्ण

/*
 * Release any architecture-specअगरic resources locked by thपढ़ो
 */
व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

/*
 * Some archs flush debug and FPU info here
 */
व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

/*
 * The "wait channel" terminology is archaic, but what we want
 * is an identअगरication of the poपूर्णांक at which the scheduler
 * was invoked by a blocked thपढ़ो.
 */
अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ fp, pc;
	अचिन्हित दीर्घ stack_page;
	पूर्णांक count = 0;
	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	stack_page = (अचिन्हित दीर्घ)task_stack_page(p);
	fp = ((काष्ठा hexagon_चयन_stack *)p->thपढ़ो.चयन_sp)->fp;
	करो अणु
		अगर (fp < (stack_page + माप(काष्ठा thपढ़ो_info)) ||
			fp >= (THREAD_SIZE - 8 + stack_page))
			वापस 0;
		pc = ((अचिन्हित दीर्घ *)fp)[1];
		अगर (!in_sched_functions(pc))
			वापस pc;
		fp = *(अचिन्हित दीर्घ *) fp;
	पूर्ण जबतक (count++ < 16);

	वापस 0;
पूर्ण

/*
 * Called on the निकास path of event entry; see vm_entry.S
 *
 * Interrupts will alपढ़ोy be disabled.
 *
 * Returns 0 अगर there's no need to re-check क्रम more work.
 */

पूर्णांक करो_work_pending(काष्ठा pt_regs *regs, u32 thपढ़ो_info_flags)
अणु
	अगर (!(thपढ़ो_info_flags & _TIF_WORK_MASK)) अणु
		वापस 0;
	पूर्ण  /* लघुcut -- no work to be करोne */

	local_irq_enable();

	अगर (thपढ़ो_info_flags & _TIF_NEED_RESCHED) अणु
		schedule();
		वापस 1;
	पूर्ण

	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL)) अणु
		करो_संकेत(regs);
		वापस 1;
	पूर्ण

	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME) अणु
		tracehook_notअगरy_resume(regs);
		वापस 1;
	पूर्ण

	/* Should not even reach here */
	panic("%s: bad thread_info flags 0x%08x\n", __func__,
		thपढ़ो_info_flags);
पूर्ण
