<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Stack trace utility functions etc.
 *
 * Copyright 2008 Christoph Hellwig, IBM Corp.
 * Copyright 2018 SUSE Linux GmbH
 * Copyright 2018 Nick Piggin, Michael Ellerman, IBM Corp.
 */

#समावेश <linux/export.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/module.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/ftrace.h>
#समावेश <यंत्र/kprobes.h>

#समावेश <यंत्र/paca.h>

व्योम arch_stack_walk(stack_trace_consume_fn consume_entry, व्योम *cookie,
		     काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp;

	अगर (regs && !consume_entry(cookie, regs->nip))
		वापस;

	अगर (regs)
		sp = regs->gpr[1];
	अन्यथा अगर (task == current)
		sp = current_stack_frame();
	अन्यथा
		sp = task->thपढ़ो.ksp;

	क्रम (;;) अणु
		अचिन्हित दीर्घ *stack = (अचिन्हित दीर्घ *) sp;
		अचिन्हित दीर्घ newsp, ip;

		अगर (!validate_sp(sp, task, STACK_FRAME_OVERHEAD))
			वापस;

		newsp = stack[0];
		ip = stack[STACK_FRAME_LR_SAVE];

		अगर (!consume_entry(cookie, ip))
			वापस;

		sp = newsp;
	पूर्ण
पूर्ण

/*
 * This function वापसs an error अगर it detects any unreliable features of the
 * stack.  Otherwise it guarantees that the stack trace is reliable.
 *
 * If the task is not 'current', the caller *must* ensure the task is inactive.
 */
पूर्णांक arch_stack_walk_reliable(stack_trace_consume_fn consume_entry,
			     व्योम *cookie, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ newsp;
	अचिन्हित दीर्घ stack_page = (अचिन्हित दीर्घ)task_stack_page(task);
	अचिन्हित दीर्घ stack_end;
	पूर्णांक graph_idx = 0;
	bool firstframe;

	stack_end = stack_page + THREAD_SIZE;
	अगर (!is_idle_task(task)) अणु
		/*
		 * For user tasks, this is the SP value loaded on
		 * kernel entry, see "PACAKSAVE(r13)" in _चयन() and
		 * प्रणाली_call_common()/EXCEPTION_PROLOG_COMMON().
		 *
		 * Likewise क्रम non-swapper kernel thपढ़ोs,
		 * this also happens to be the top of the stack
		 * as setup by copy_thपढ़ो().
		 *
		 * Note that stack backlinks are not properly setup by
		 * copy_thपढ़ो() and thus, a विभाजनed task() will have
		 * an unreliable stack trace until it's been
		 * _चयन()'ed to क्रम the first समय.
		 */
		stack_end -= STACK_FRAME_OVERHEAD + माप(काष्ठा pt_regs);
	पूर्ण अन्यथा अणु
		/*
		 * idle tasks have a custom stack layout,
		 * c.f. cpu_idle_thपढ़ो_init().
		 */
		stack_end -= STACK_FRAME_OVERHEAD;
	पूर्ण

	अगर (task == current)
		sp = current_stack_frame();
	अन्यथा
		sp = task->thपढ़ो.ksp;

	अगर (sp < stack_page + माप(काष्ठा thपढ़ो_काष्ठा) ||
	    sp > stack_end - STACK_FRAME_MIN_SIZE) अणु
		वापस -EINVAL;
	पूर्ण

	क्रम (firstframe = true; sp != stack_end;
	     firstframe = false, sp = newsp) अणु
		अचिन्हित दीर्घ *stack = (अचिन्हित दीर्घ *) sp;
		अचिन्हित दीर्घ ip;

		/* sanity check: ABI requires SP to be aligned 16 bytes. */
		अगर (sp & 0xF)
			वापस -EINVAL;

		newsp = stack[0];
		/* Stack grows करोwnwards; unwinder may only go up. */
		अगर (newsp <= sp)
			वापस -EINVAL;

		अगर (newsp != stack_end &&
		    newsp > stack_end - STACK_FRAME_MIN_SIZE) अणु
			वापस -EINVAL; /* invalid backlink, too far up. */
		पूर्ण

		/*
		 * We can only trust the bottom frame's backlink, the
		 * rest of the frame may be uninitialized, जारी to
		 * the next.
		 */
		अगर (firstframe)
			जारी;

		/* Mark stacktraces with exception frames as unreliable. */
		अगर (sp <= stack_end - STACK_INT_FRAME_SIZE &&
		    stack[STACK_FRAME_MARKER] == STACK_FRAME_REGS_MARKER) अणु
			वापस -EINVAL;
		पूर्ण

		/* Examine the saved LR: it must poपूर्णांक पूर्णांकo kernel code. */
		ip = stack[STACK_FRAME_LR_SAVE];
		अगर (!__kernel_text_address(ip))
			वापस -EINVAL;

		/*
		 * FIXME: IMHO these tests करो not beदीर्घ in
		 * arch-dependent code, they are generic.
		 */
		ip = ftrace_graph_ret_addr(task, &graph_idx, ip, stack);
#अगर_घोषित CONFIG_KPROBES
		/*
		 * Mark stacktraces with kretprobed functions on them
		 * as unreliable.
		 */
		अगर (ip == (अचिन्हित दीर्घ)kretprobe_trampoline)
			वापस -EINVAL;
#पूर्ण_अगर

		अगर (!consume_entry(cookie, ip))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_NMI_IPI)
अटल व्योम handle_backtrace_ipi(काष्ठा pt_regs *regs)
अणु
	nmi_cpu_backtrace(regs);
पूर्ण

अटल व्योम उठाओ_backtrace_ipi(cpumask_t *mask)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		अगर (cpu == smp_processor_id())
			handle_backtrace_ipi(शून्य);
		अन्यथा
			smp_send_safe_nmi_ipi(cpu, handle_backtrace_ipi, 5 * USEC_PER_SEC);
	पूर्ण

	क्रम_each_cpu(cpu, mask) अणु
		काष्ठा paca_काष्ठा *p = paca_ptrs[cpu];

		cpumask_clear_cpu(cpu, mask);

		pr_warn("CPU %d didn't respond to backtrace IPI, inspecting paca.\n", cpu);
		अगर (!virt_addr_valid(p)) अणु
			pr_warn("paca pointer appears corrupt? (%px)\n", p);
			जारी;
		पूर्ण

		pr_warn("irq_soft_mask: 0x%02x in_mce: %d in_nmi: %d",
			p->irq_soft_mask, p->in_mce, p->in_nmi);

		अगर (virt_addr_valid(p->__current))
			pr_cont(" current: %d (%s)\n", p->__current->pid,
				p->__current->comm);
		अन्यथा
			pr_cont(" current pointer corrupt? (%px)\n", p->__current);

		pr_warn("Back trace of paca->saved_r1 (0x%016llx) (possibly stale):\n", p->saved_r1);
		show_stack(p->__current, (अचिन्हित दीर्घ *)p->saved_r1, KERN_WARNING);
	पूर्ण
पूर्ण

व्योम arch_trigger_cpumask_backtrace(स्थिर cpumask_t *mask, bool exclude_self)
अणु
	nmi_trigger_cpumask_backtrace(mask, exclude_self, उठाओ_backtrace_ipi);
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_NMI_IPI) */
