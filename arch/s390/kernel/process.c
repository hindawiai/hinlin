<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file handles the architecture dependent parts of process handling.
 *
 *    Copyright IBM Corp. 1999, 2009
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Harपंचांगut Penner <hp@de.ibm.com>,
 *		 Denis Joseph Barrow,
 */

#समावेश <linux/elf-अक्रमomize.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/smp.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tick.h>
#समावेश <linux/personality.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/compat.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/export.h>
#समावेश <linux/init_task.h>
#समावेश <linux/entry-common.h>
#समावेश <यंत्र/cpu_mf.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/vसमयr.h>
#समावेश <यंत्र/exec.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/runसमय_instr.h>
#समावेश <यंत्र/unwind.h>
#समावेश "entry.h"

व्योम ret_from_विभाजन(व्योम) यंत्र("ret_from_fork");

व्योम __ret_from_विभाजन(काष्ठा task_काष्ठा *prev, काष्ठा pt_regs *regs)
अणु
	व्योम (*func)(व्योम *arg);

	schedule_tail(prev);

	अगर (!user_mode(regs)) अणु
		/* Kernel thपढ़ो */
		func = (व्योम *)regs->gprs[9];
		func((व्योम *)regs->gprs[10]);
	पूर्ण
	clear_pt_regs_flag(regs, PIF_SYSCALL);
	syscall_निकास_to_user_mode(regs);
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

व्योम arch_setup_new_exec(व्योम)
अणु
	अगर (S390_lowcore.current_pid != current->pid) अणु
		S390_lowcore.current_pid = current->pid;
		अगर (test_facility(40))
			lpp(&S390_lowcore.lpp);
	पूर्ण
पूर्ण

व्योम arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk)
अणु
	runसमय_instr_release(tsk);
	guarded_storage_release(tsk);
पूर्ण

पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	/*
	 * Save the भग्नing-poपूर्णांक or vector रेजिस्टर state of the current
	 * task and set the CIF_FPU flag to lazy restore the FPU रेजिस्टर
	 * state when वापसing to user space.
	 */
	save_fpu_regs();

	स_नकल(dst, src, arch_task_काष्ठा_size);
	dst->thपढ़ो.fpu.regs = dst->thपढ़ो.fpu.fprs;
	वापस 0;
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ new_stackp,
		अचिन्हित दीर्घ arg, काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा fake_frame
	अणु
		काष्ठा stack_frame sf;
		काष्ठा pt_regs childregs;
	पूर्ण *frame;

	frame = container_of(task_pt_regs(p), काष्ठा fake_frame, childregs);
	p->thपढ़ो.ksp = (अचिन्हित दीर्घ) frame;
	/* Save access रेजिस्टरs to new thपढ़ो काष्ठाure. */
	save_access_regs(&p->thपढ़ो.acrs[0]);
	/* start new process with ar4 poपूर्णांकing to the correct address space */
	/* Don't copy debug रेजिस्टरs */
	स_रखो(&p->thपढ़ो.per_user, 0, माप(p->thपढ़ो.per_user));
	स_रखो(&p->thपढ़ो.per_event, 0, माप(p->thपढ़ो.per_event));
	clear_tsk_thपढ़ो_flag(p, TIF_SINGLE_STEP);
	p->thपढ़ो.per_flags = 0;
	/* Initialize per thपढ़ो user and प्रणाली समयr values */
	p->thपढ़ो.user_समयr = 0;
	p->thपढ़ो.guest_समयr = 0;
	p->thपढ़ो.प्रणाली_समयr = 0;
	p->thपढ़ो.hardirq_समयr = 0;
	p->thपढ़ो.softirq_समयr = 0;
	p->thपढ़ो.last_अवरोध = 1;

	frame->sf.back_chain = 0;
	frame->sf.gprs[5] = (अचिन्हित दीर्घ)frame + माप(काष्ठा stack_frame);
	frame->sf.gprs[6] = (अचिन्हित दीर्घ)p;
	/* new वापस poपूर्णांक is ret_from_विभाजन */
	frame->sf.gprs[8] = (अचिन्हित दीर्घ)ret_from_विभाजन;
	/* fake वापस stack क्रम resume(), करोn't go back to schedule */
	frame->sf.gprs[9] = (अचिन्हित दीर्घ)frame;

	/* Store access रेजिस्टरs to kernel stack of new process. */
	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* kernel thपढ़ो */
		स_रखो(&frame->childregs, 0, माप(काष्ठा pt_regs));
		frame->childregs.psw.mask = PSW_KERNEL_BITS | PSW_MASK_DAT |
				PSW_MASK_IO | PSW_MASK_EXT | PSW_MASK_MCHECK;
		frame->childregs.psw.addr =
				(अचिन्हित दीर्घ)__ret_from_विभाजन;
		frame->childregs.gprs[9] = new_stackp; /* function */
		frame->childregs.gprs[10] = arg;
		frame->childregs.gprs[11] = (अचिन्हित दीर्घ)करो_निकास;
		frame->childregs.orig_gpr2 = -1;

		वापस 0;
	पूर्ण
	frame->childregs = *current_pt_regs();
	frame->childregs.gprs[2] = 0;	/* child वापसs 0 on विभाजन. */
	frame->childregs.flags = 0;
	अगर (new_stackp)
		frame->childregs.gprs[15] = new_stackp;

	/* Don't copy runसमय instrumentation info */
	p->thपढ़ो.ri_cb = शून्य;
	frame->childregs.psw.mask &= ~PSW_MASK_RI;
	/* Don't copy guarded storage control block */
	p->thपढ़ो.gs_cb = शून्य;
	p->thपढ़ो.gs_bc_cb = शून्य;

	/* Set a new TLS ?  */
	अगर (clone_flags & CLONE_SETTLS) अणु
		अगर (is_compat_task()) अणु
			p->thपढ़ो.acrs[0] = (अचिन्हित पूर्णांक)tls;
		पूर्ण अन्यथा अणु
			p->thपढ़ो.acrs[0] = (अचिन्हित पूर्णांक)(tls >> 32);
			p->thपढ़ो.acrs[1] = (अचिन्हित पूर्णांक)tls;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम execve_tail(व्योम)
अणु
	current->thपढ़ो.fpu.fpc = 0;
	यंत्र अस्थिर("sfpc %0" : : "d" (0));
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ ip = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING || !task_stack_page(p))
		वापस 0;

	अगर (!try_get_task_stack(p))
		वापस 0;

	unwind_क्रम_each_frame(&state, p, शून्य, 0) अणु
		अगर (state.stack_info.type != STACK_TYPE_TASK) अणु
			ip = 0;
			अवरोध;
		पूर्ण

		ip = unwind_get_वापस_address(&state);
		अगर (!ip)
			अवरोध;

		अगर (!in_sched_functions(ip))
			अवरोध;
	पूर्ण

	put_task_stack(p);
	वापस ip;
पूर्ण

अचिन्हित दीर्घ arch_align_stack(अचिन्हित दीर्घ sp)
अणु
	अगर (!(current->personality & ADDR_NO_RANDOMIZE) && अक्रमomize_va_space)
		sp -= get_अक्रमom_पूर्णांक() & ~PAGE_MASK;
	वापस sp & ~0xf;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ brk_rnd(व्योम)
अणु
	वापस (get_अक्रमom_पूर्णांक() & BRK_RND_MASK) << PAGE_SHIFT;
पूर्ण

अचिन्हित दीर्घ arch_अक्रमomize_brk(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ ret;

	ret = PAGE_ALIGN(mm->brk + brk_rnd());
	वापस (ret > mm->brk) ? ret : mm->brk;
पूर्ण
