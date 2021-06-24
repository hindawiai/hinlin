<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  arch/sparc64/kernel/process.c
 *
 *  Copyright (C) 1995, 1996, 2008 David S. Miller (davem@davemloft.net)
 *  Copyright (C) 1996       Eddie C. Dost   (ecd@skynet.be)
 *  Copyright (C) 1997, 1998 Jakub Jelinek   (jj@sunsite.mff.cuni.cz)
 */

/*
 * This file handles the architecture-dependent parts of process handling..
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/user.h>
#समावेश <linux/delay.h>
#समावेश <linux/compat.h>
#समावेश <linux/tick.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/nmi.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/संकेत.स>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/pcr.h>

#समावेश "kstack.h"

/* Idle loop support on sparc64. */
व्योम arch_cpu_idle(व्योम)
अणु
	अगर (tlb_type != hypervisor) अणु
		touch_nmi_watchकरोg();
		raw_local_irq_enable();
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ pstate;

		raw_local_irq_enable();

                /* The sun4v sleeping code requires that we have PSTATE.IE cleared over
                 * the cpu sleep hypervisor call.
                 */
		__यंत्र__ __अस्थिर__(
			"rdpr %%pstate, %0\n\t"
			"andn %0, %1, %0\n\t"
			"wrpr %0, %%g0, %%pstate"
			: "=&r" (pstate)
			: "i" (PSTATE_IE));

		अगर (!need_resched() && !cpu_is_offline(smp_processor_id())) अणु
			sun4v_cpu_yield();
			/* If resumed by cpu_poke then we need to explicitly
			 * call scheduler_ipi().
			 */
			scheduler_poke();
		पूर्ण

		/* Re-enable पूर्णांकerrupts. */
		__यंत्र__ __अस्थिर__(
			"rdpr %%pstate, %0\n\t"
			"or %0, %1, %0\n\t"
			"wrpr %0, %%g0, %%pstate"
			: "=&r" (pstate)
			: "i" (PSTATE_IE));
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम arch_cpu_idle_dead(व्योम)
अणु
	sched_preempt_enable_no_resched();
	cpu_play_dead();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
अटल व्योम show_regwinकरोw32(काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw32 __user *rw;
	काष्ठा reg_winकरोw32 r_w;
	mm_segment_t old_fs;
	
	__यंत्र__ __अस्थिर__ ("flushw");
	rw = compat_ptr((अचिन्हित पूर्णांक)regs->u_regs[14]);
	old_fs = get_fs();
	set_fs (USER_DS);
	अगर (copy_from_user (&r_w, rw, माप(r_w))) अणु
		set_fs (old_fs);
		वापस;
	पूर्ण

	set_fs (old_fs);			
	prपूर्णांकk("l0: %08x l1: %08x l2: %08x l3: %08x "
	       "l4: %08x l5: %08x l6: %08x l7: %08x\n",
	       r_w.locals[0], r_w.locals[1], r_w.locals[2], r_w.locals[3],
	       r_w.locals[4], r_w.locals[5], r_w.locals[6], r_w.locals[7]);
	prपूर्णांकk("i0: %08x i1: %08x i2: %08x i3: %08x "
	       "i4: %08x i5: %08x i6: %08x i7: %08x\n",
	       r_w.ins[0], r_w.ins[1], r_w.ins[2], r_w.ins[3],
	       r_w.ins[4], r_w.ins[5], r_w.ins[6], r_w.ins[7]);
पूर्ण
#अन्यथा
#घोषणा show_regwinकरोw32(regs)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम show_regwinकरोw(काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw __user *rw;
	काष्ठा reg_winकरोw *rwk;
	काष्ठा reg_winकरोw r_w;
	mm_segment_t old_fs;

	अगर ((regs->tstate & TSTATE_PRIV) || !(test_thपढ़ो_flag(TIF_32BIT))) अणु
		__यंत्र__ __अस्थिर__ ("flushw");
		rw = (काष्ठा reg_winकरोw __user *)
			(regs->u_regs[14] + STACK_BIAS);
		rwk = (काष्ठा reg_winकरोw *)
			(regs->u_regs[14] + STACK_BIAS);
		अगर (!(regs->tstate & TSTATE_PRIV)) अणु
			old_fs = get_fs();
			set_fs (USER_DS);
			अगर (copy_from_user (&r_w, rw, माप(r_w))) अणु
				set_fs (old_fs);
				वापस;
			पूर्ण
			rwk = &r_w;
			set_fs (old_fs);			
		पूर्ण
	पूर्ण अन्यथा अणु
		show_regwinकरोw32(regs);
		वापस;
	पूर्ण
	prपूर्णांकk("l0: %016lx l1: %016lx l2: %016lx l3: %016lx\n",
	       rwk->locals[0], rwk->locals[1], rwk->locals[2], rwk->locals[3]);
	prपूर्णांकk("l4: %016lx l5: %016lx l6: %016lx l7: %016lx\n",
	       rwk->locals[4], rwk->locals[5], rwk->locals[6], rwk->locals[7]);
	prपूर्णांकk("i0: %016lx i1: %016lx i2: %016lx i3: %016lx\n",
	       rwk->ins[0], rwk->ins[1], rwk->ins[2], rwk->ins[3]);
	prपूर्णांकk("i4: %016lx i5: %016lx i6: %016lx i7: %016lx\n",
	       rwk->ins[4], rwk->ins[5], rwk->ins[6], rwk->ins[7]);
	अगर (regs->tstate & TSTATE_PRIV)
		prपूर्णांकk("I7: <%pS>\n", (व्योम *) rwk->ins[7]);
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	prपूर्णांकk("TSTATE: %016lx TPC: %016lx TNPC: %016lx Y: %08x    %s\n", regs->tstate,
	       regs->tpc, regs->tnpc, regs->y, prपूर्णांक_taपूर्णांकed());
	prपूर्णांकk("TPC: <%pS>\n", (व्योम *) regs->tpc);
	prपूर्णांकk("g0: %016lx g1: %016lx g2: %016lx g3: %016lx\n",
	       regs->u_regs[0], regs->u_regs[1], regs->u_regs[2],
	       regs->u_regs[3]);
	prपूर्णांकk("g4: %016lx g5: %016lx g6: %016lx g7: %016lx\n",
	       regs->u_regs[4], regs->u_regs[5], regs->u_regs[6],
	       regs->u_regs[7]);
	prपूर्णांकk("o0: %016lx o1: %016lx o2: %016lx o3: %016lx\n",
	       regs->u_regs[8], regs->u_regs[9], regs->u_regs[10],
	       regs->u_regs[11]);
	prपूर्णांकk("o4: %016lx o5: %016lx sp: %016lx ret_pc: %016lx\n",
	       regs->u_regs[12], regs->u_regs[13], regs->u_regs[14],
	       regs->u_regs[15]);
	prपूर्णांकk("RPC: <%pS>\n", (व्योम *) regs->u_regs[15]);
	show_regwinकरोw(regs);
	show_stack(current, (अचिन्हित दीर्घ *)regs->u_regs[UREG_FP], KERN_DEFAULT);
पूर्ण

जोड़ global_cpu_snapshot global_cpu_snapshot[NR_CPUS];
अटल DEFINE_SPINLOCK(global_cpu_snapshot_lock);

अटल व्योम __global_reg_self(काष्ठा thपढ़ो_info *tp, काष्ठा pt_regs *regs,
			      पूर्णांक this_cpu)
अणु
	काष्ठा global_reg_snapshot *rp;

	flushw_all();

	rp = &global_cpu_snapshot[this_cpu].reg;

	rp->tstate = regs->tstate;
	rp->tpc = regs->tpc;
	rp->tnpc = regs->tnpc;
	rp->o7 = regs->u_regs[UREG_I7];

	अगर (regs->tstate & TSTATE_PRIV) अणु
		काष्ठा reg_winकरोw *rw;

		rw = (काष्ठा reg_winकरोw *)
			(regs->u_regs[UREG_FP] + STACK_BIAS);
		अगर (kstack_valid(tp, (अचिन्हित दीर्घ) rw)) अणु
			rp->i7 = rw->ins[7];
			rw = (काष्ठा reg_winकरोw *)
				(rw->ins[6] + STACK_BIAS);
			अगर (kstack_valid(tp, (अचिन्हित दीर्घ) rw))
				rp->rpc = rw->ins[7];
		पूर्ण
	पूर्ण अन्यथा अणु
		rp->i7 = 0;
		rp->rpc = 0;
	पूर्ण
	rp->thपढ़ो = tp;
पूर्ण

/* In order to aव्योम hangs we करो not try to synchronize with the
 * global रेजिस्टर dump client cpus.  The last store they make is to
 * the thपढ़ो poपूर्णांकer, so करो a लघु poll रुकोing क्रम that to become
 * non-शून्य.
 */
अटल व्योम __global_reg_poll(काष्ठा global_reg_snapshot *gp)
अणु
	पूर्णांक limit = 0;

	जबतक (!gp->thपढ़ो && ++limit < 100) अणु
		barrier();
		udelay(1);
	पूर्ण
पूर्ण

व्योम arch_trigger_cpumask_backtrace(स्थिर cpumask_t *mask, bool exclude_self)
अणु
	काष्ठा thपढ़ो_info *tp = current_thपढ़ो_info();
	काष्ठा pt_regs *regs = get_irq_regs();
	अचिन्हित दीर्घ flags;
	पूर्णांक this_cpu, cpu;

	अगर (!regs)
		regs = tp->kregs;

	spin_lock_irqsave(&global_cpu_snapshot_lock, flags);

	this_cpu = raw_smp_processor_id();

	स_रखो(global_cpu_snapshot, 0, माप(global_cpu_snapshot));

	अगर (cpumask_test_cpu(this_cpu, mask) && !exclude_self)
		__global_reg_self(tp, regs, this_cpu);

	smp_fetch_global_regs();

	क्रम_each_cpu(cpu, mask) अणु
		काष्ठा global_reg_snapshot *gp;

		अगर (exclude_self && cpu == this_cpu)
			जारी;

		gp = &global_cpu_snapshot[cpu].reg;

		__global_reg_poll(gp);

		tp = gp->thपढ़ो;
		prपूर्णांकk("%c CPU[%3d]: TSTATE[%016lx] TPC[%016lx] TNPC[%016lx] TASK[%s:%d]\n",
		       (cpu == this_cpu ? '*' : ' '), cpu,
		       gp->tstate, gp->tpc, gp->tnpc,
		       ((tp && tp->task) ? tp->task->comm : "NULL"),
		       ((tp && tp->task) ? tp->task->pid : -1));

		अगर (gp->tstate & TSTATE_PRIV) अणु
			prपूर्णांकk("             TPC[%pS] O7[%pS] I7[%pS] RPC[%pS]\n",
			       (व्योम *) gp->tpc,
			       (व्योम *) gp->o7,
			       (व्योम *) gp->i7,
			       (व्योम *) gp->rpc);
		पूर्ण अन्यथा अणु
			prपूर्णांकk("             TPC[%lx] O7[%lx] I7[%lx] RPC[%lx]\n",
			       gp->tpc, gp->o7, gp->i7, gp->rpc);
		पूर्ण

		touch_nmi_watchकरोg();
	पूर्ण

	स_रखो(global_cpu_snapshot, 0, माप(global_cpu_snapshot));

	spin_unlock_irqrestore(&global_cpu_snapshot_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_MAGIC_SYSRQ

अटल व्योम sysrq_handle_globreg(पूर्णांक key)
अणु
	trigger_all_cpu_backtrace();
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sparc_globalreg_op = अणु
	.handler	= sysrq_handle_globreg,
	.help_msg	= "global-regs(y)",
	.action_msg	= "Show Global CPU Regs",
पूर्ण;

अटल व्योम __global_pmu_self(पूर्णांक this_cpu)
अणु
	काष्ठा global_pmu_snapshot *pp;
	पूर्णांक i, num;

	अगर (!pcr_ops)
		वापस;

	pp = &global_cpu_snapshot[this_cpu].pmu;

	num = 1;
	अगर (tlb_type == hypervisor &&
	    sun4v_chip_type >= SUN4V_CHIP_NIAGARA4)
		num = 4;

	क्रम (i = 0; i < num; i++) अणु
		pp->pcr[i] = pcr_ops->पढ़ो_pcr(i);
		pp->pic[i] = pcr_ops->पढ़ो_pic(i);
	पूर्ण
पूर्ण

अटल व्योम __global_pmu_poll(काष्ठा global_pmu_snapshot *pp)
अणु
	पूर्णांक limit = 0;

	जबतक (!pp->pcr[0] && ++limit < 100) अणु
		barrier();
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम pmu_snapshot_all_cpus(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक this_cpu, cpu;

	spin_lock_irqsave(&global_cpu_snapshot_lock, flags);

	स_रखो(global_cpu_snapshot, 0, माप(global_cpu_snapshot));

	this_cpu = raw_smp_processor_id();

	__global_pmu_self(this_cpu);

	smp_fetch_global_pmu();

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा global_pmu_snapshot *pp = &global_cpu_snapshot[cpu].pmu;

		__global_pmu_poll(pp);

		prपूर्णांकk("%c CPU[%3d]: PCR[%08lx:%08lx:%08lx:%08lx] PIC[%08lx:%08lx:%08lx:%08lx]\n",
		       (cpu == this_cpu ? '*' : ' '), cpu,
		       pp->pcr[0], pp->pcr[1], pp->pcr[2], pp->pcr[3],
		       pp->pic[0], pp->pic[1], pp->pic[2], pp->pic[3]);

		touch_nmi_watchकरोg();
	पूर्ण

	स_रखो(global_cpu_snapshot, 0, माप(global_cpu_snapshot));

	spin_unlock_irqrestore(&global_cpu_snapshot_lock, flags);
पूर्ण

अटल व्योम sysrq_handle_globpmu(पूर्णांक key)
अणु
	pmu_snapshot_all_cpus();
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sparc_globalpmu_op = अणु
	.handler	= sysrq_handle_globpmu,
	.help_msg	= "global-pmu(x)",
	.action_msg	= "Show Global PMU Regs",
पूर्ण;

अटल पूर्णांक __init sparc_sysrq_init(व्योम)
अणु
	पूर्णांक ret = रेजिस्टर_sysrq_key('y', &sparc_globalreg_op);

	अगर (!ret)
		ret = रेजिस्टर_sysrq_key('x', &sparc_globalpmu_op);
	वापस ret;
पूर्ण

core_initcall(sparc_sysrq_init);

#पूर्ण_अगर

/* Free current thपढ़ो data काष्ठाures etc.. */
व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_info *t = task_thपढ़ो_info(tsk);

	अगर (t->utraps) अणु
		अगर (t->utraps[0] < 2)
			kमुक्त (t->utraps);
		अन्यथा
			t->utraps[0]--;
	पूर्ण
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
	काष्ठा thपढ़ो_info *t = current_thपढ़ो_info();
	काष्ठा mm_काष्ठा *mm;

	mm = t->task->mm;
	अगर (mm)
		tsb_context_चयन(mm);

	set_thपढ़ो_wsaved(0);

	/* Clear FPU रेजिस्टर state. */
	t->fpsaved[0] = 0;
पूर्ण

/* It's a bit more tricky when 64-bit tasks are involved... */
अटल अचिन्हित दीर्घ clone_stackframe(अचिन्हित दीर्घ csp, अचिन्हित दीर्घ psp)
अणु
	bool stack_64bit = test_thपढ़ो_64bit_stack(psp);
	अचिन्हित दीर्घ fp, distance, rval;

	अगर (stack_64bit) अणु
		csp += STACK_BIAS;
		psp += STACK_BIAS;
		__get_user(fp, &(((काष्ठा reg_winकरोw __user *)psp)->ins[6]));
		fp += STACK_BIAS;
		अगर (test_thपढ़ो_flag(TIF_32BIT))
			fp &= 0xffffffff;
	पूर्ण अन्यथा
		__get_user(fp, &(((काष्ठा reg_winकरोw32 __user *)psp)->ins[6]));

	/* Now align the stack as this is mandatory in the Sparc ABI
	 * due to how रेजिस्टर winकरोws work.  This hides the
	 * restriction from thपढ़ो libraries etc.
	 */
	csp &= ~15UL;

	distance = fp - psp;
	rval = (csp - distance);
	अगर (copy_in_user((व्योम __user *) rval, (व्योम __user *) psp, distance))
		rval = 0;
	अन्यथा अगर (!stack_64bit) अणु
		अगर (put_user(((u32)csp),
			     &(((काष्ठा reg_winकरोw32 __user *)rval)->ins[6])))
			rval = 0;
	पूर्ण अन्यथा अणु
		अगर (put_user(((u64)csp - STACK_BIAS),
			     &(((काष्ठा reg_winकरोw __user *)rval)->ins[6])))
			rval = 0;
		अन्यथा
			rval = rval - STACK_BIAS;
	पूर्ण

	वापस rval;
पूर्ण

/* Standard stuff. */
अटल अंतरभूत व्योम shअगरt_winकरोw_buffer(पूर्णांक first_win, पूर्णांक last_win,
				       काष्ठा thपढ़ो_info *t)
अणु
	पूर्णांक i;

	क्रम (i = first_win; i < last_win; i++) अणु
		t->rwbuf_stkptrs[i] = t->rwbuf_stkptrs[i+1];
		स_नकल(&t->reg_winकरोw[i], &t->reg_winकरोw[i+1],
		       माप(काष्ठा reg_winकरोw));
	पूर्ण
पूर्ण

व्योम synchronize_user_stack(व्योम)
अणु
	काष्ठा thपढ़ो_info *t = current_thपढ़ो_info();
	अचिन्हित दीर्घ winकरोw;

	flush_user_winकरोws();
	अगर ((winकरोw = get_thपढ़ो_wsaved()) != 0) अणु
		winकरोw -= 1;
		करो अणु
			काष्ठा reg_winकरोw *rwin = &t->reg_winकरोw[winकरोw];
			पूर्णांक winsize = माप(काष्ठा reg_winकरोw);
			अचिन्हित दीर्घ sp;

			sp = t->rwbuf_stkptrs[winकरोw];

			अगर (test_thपढ़ो_64bit_stack(sp))
				sp += STACK_BIAS;
			अन्यथा
				winsize = माप(काष्ठा reg_winकरोw32);

			अगर (!copy_to_user((अक्षर __user *)sp, rwin, winsize)) अणु
				shअगरt_winकरोw_buffer(winकरोw, get_thपढ़ो_wsaved() - 1, t);
				set_thपढ़ो_wsaved(get_thपढ़ो_wsaved() - 1);
			पूर्ण
		पूर्ण जबतक (winकरोw--);
	पूर्ण
पूर्ण

अटल व्योम stack_unaligned(अचिन्हित दीर्घ sp)
अणु
	क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम __user *) sp, 0);
पूर्ण

अटल स्थिर अक्षर uwfault32[] = KERN_INFO \
	"%s[%d]: bad register window fault: SP %08lx (orig_sp %08lx) TPC %08lx O7 %08lx\n";
अटल स्थिर अक्षर uwfault64[] = KERN_INFO \
	"%s[%d]: bad register window fault: SP %016lx (orig_sp %016lx) TPC %08lx O7 %016lx\n";

व्योम fault_in_user_winकरोws(काष्ठा pt_regs *regs)
अणु
	काष्ठा thपढ़ो_info *t = current_thपढ़ो_info();
	अचिन्हित दीर्घ winकरोw;

	flush_user_winकरोws();
	winकरोw = get_thपढ़ो_wsaved();

	अगर (likely(winकरोw != 0)) अणु
		winकरोw -= 1;
		करो अणु
			काष्ठा reg_winकरोw *rwin = &t->reg_winकरोw[winकरोw];
			पूर्णांक winsize = माप(काष्ठा reg_winकरोw);
			अचिन्हित दीर्घ sp, orig_sp;

			orig_sp = sp = t->rwbuf_stkptrs[winकरोw];

			अगर (test_thपढ़ो_64bit_stack(sp))
				sp += STACK_BIAS;
			अन्यथा
				winsize = माप(काष्ठा reg_winकरोw32);

			अगर (unlikely(sp & 0x7UL))
				stack_unaligned(sp);

			अगर (unlikely(copy_to_user((अक्षर __user *)sp,
						  rwin, winsize))) अणु
				अगर (show_unhandled_संकेतs)
					prपूर्णांकk_ratelimited(is_compat_task() ?
							   uwfault32 : uwfault64,
							   current->comm, current->pid,
							   sp, orig_sp,
							   regs->tpc,
							   regs->u_regs[UREG_I7]);
				जाओ barf;
			पूर्ण
		पूर्ण जबतक (winकरोw--);
	पूर्ण
	set_thपढ़ो_wsaved(0);
	वापस;

barf:
	set_thपढ़ो_wsaved(winकरोw + 1);
	क्रमce_sig(संक_अंश);
पूर्ण

/* Copy a Sparc thपढ़ो.  The विभाजन() वापस value conventions
 * under SunOS are nothing लघु of bletcherous:
 * Parent -->  %o0 == childs  pid, %o1 == 0
 * Child  -->  %o0 == parents pid, %o1 == 1
 */
पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ sp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा thपढ़ो_info *t = task_thपढ़ो_info(p);
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा sparc_stackf *parent_sf;
	अचिन्हित दीर्घ child_stack_sz;
	अक्षर *child_trap_frame;

	/* Calculate offset to stack_frame & pt_regs */
	child_stack_sz = (STACKFRAME_SZ + TRACEREG_SZ);
	child_trap_frame = (task_stack_page(p) +
			    (THREAD_SIZE - child_stack_sz));

	t->new_child = 1;
	t->ksp = ((अचिन्हित दीर्घ) child_trap_frame) - STACK_BIAS;
	t->kregs = (काष्ठा pt_regs *) (child_trap_frame +
				       माप(काष्ठा sparc_stackf));
	t->fpsaved[0] = 0;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(child_trap_frame, 0, child_stack_sz);
		__thपढ़ो_flag_byte_ptr(t)[TI_FLAG_BYTE_CWP] = 
			(current_pt_regs()->tstate + 1) & TSTATE_CWP;
		t->current_ds = ASI_P;
		t->kregs->u_regs[UREG_G1] = sp; /* function */
		t->kregs->u_regs[UREG_G2] = arg;
		वापस 0;
	पूर्ण

	parent_sf = ((काष्ठा sparc_stackf *) regs) - 1;
	स_नकल(child_trap_frame, parent_sf, child_stack_sz);
	अगर (t->flags & _TIF_32BIT) अणु
		sp &= 0x00000000ffffffffUL;
		regs->u_regs[UREG_FP] &= 0x00000000ffffffffUL;
	पूर्ण
	t->kregs->u_regs[UREG_FP] = sp;
	__thपढ़ो_flag_byte_ptr(t)[TI_FLAG_BYTE_CWP] = 
		(regs->tstate + 1) & TSTATE_CWP;
	t->current_ds = ASI_AIUS;
	अगर (sp != regs->u_regs[UREG_FP]) अणु
		अचिन्हित दीर्घ csp;

		csp = clone_stackframe(sp, regs->u_regs[UREG_FP]);
		अगर (!csp)
			वापस -EFAULT;
		t->kregs->u_regs[UREG_FP] = csp;
	पूर्ण
	अगर (t->utraps)
		t->utraps[0]++;

	/* Set the वापस value क्रम the child. */
	t->kregs->u_regs[UREG_I0] = current->pid;
	t->kregs->u_regs[UREG_I1] = 1;

	/* Set the second वापस value क्रम the parent. */
	regs->u_regs[UREG_I1] = 0;

	अगर (clone_flags & CLONE_SETTLS)
		t->kregs->u_regs[UREG_G7] = tls;

	वापस 0;
पूर्ण

/* TIF_MCDPER in thपढ़ो info flags क्रम current task is updated lazily upon
 * a context चयन. Update this flag in current task's thपढ़ो flags
 * beक्रमe dup so the dup'd task will inherit the current TIF_MCDPER flag.
 */
पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	अगर (adi_capable()) अणु
		रेजिस्टर अचिन्हित दीर्घ पंचांगp_mcdper;

		__यंत्र__ __अस्थिर__(
			".word 0x83438000\n\t"	/* rd  %mcdper, %g1 */
			"mov %%g1, %0\n\t"
			: "=r" (पंचांगp_mcdper)
			:
			: "g1");
		अगर (पंचांगp_mcdper)
			set_thपढ़ो_flag(TIF_MCDPER);
		अन्यथा
			clear_thपढ़ो_flag(TIF_MCDPER);
	पूर्ण

	*dst = *src;
	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ pc, fp, bias = 0;
	काष्ठा thपढ़ो_info *tp;
	काष्ठा reg_winकरोw *rw;
        अचिन्हित दीर्घ ret = 0;
	पूर्णांक count = 0; 

	अगर (!task || task == current ||
            task->state == TASK_RUNNING)
		जाओ out;

	tp = task_thपढ़ो_info(task);
	bias = STACK_BIAS;
	fp = task_thपढ़ो_info(task)->ksp + bias;

	करो अणु
		अगर (!kstack_valid(tp, fp))
			अवरोध;
		rw = (काष्ठा reg_winकरोw *) fp;
		pc = rw->ins[7];
		अगर (!in_sched_functions(pc)) अणु
			ret = pc;
			जाओ out;
		पूर्ण
		fp = rw->ins[6] + bias;
	पूर्ण जबतक (++count < 16);

out:
	वापस ret;
पूर्ण
