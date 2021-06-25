<शैली गुरु>
/*
 *  Copyright (C) 1995  Linus Torvalds
 *
 *  Pentium III FXSR, SSE support
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 */

/*
 * This file handles the architecture-dependent parts of process handling..
 */

#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/user.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/export.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/personality.h>
#समावेश <linux/percpu.h>
#समावेश <linux/prctl.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/kdebug.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/ldt.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/desc.h>

#समावेश <linux/err.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/vm86.h>
#समावेश <यंत्र/resctrl.h>
#समावेश <यंत्र/proto.h>

#समावेश "process.h"

व्योम __show_regs(काष्ठा pt_regs *regs, क्रमागत show_regs_mode mode,
		 स्थिर अक्षर *log_lvl)
अणु
	अचिन्हित दीर्घ cr0 = 0L, cr2 = 0L, cr3 = 0L, cr4 = 0L;
	अचिन्हित दीर्घ d0, d1, d2, d3, d6, d7;
	अचिन्हित लघु gs;

	अगर (user_mode(regs))
		gs = get_user_gs(regs);
	अन्यथा
		savesegment(gs, gs);

	show_ip(regs, log_lvl);

	prपूर्णांकk("%sEAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx\n",
		log_lvl, regs->ax, regs->bx, regs->cx, regs->dx);
	prपूर्णांकk("%sESI: %08lx EDI: %08lx EBP: %08lx ESP: %08lx\n",
		log_lvl, regs->si, regs->di, regs->bp, regs->sp);
	prपूर्णांकk("%sDS: %04x ES: %04x FS: %04x GS: %04x SS: %04x EFLAGS: %08lx\n",
	       log_lvl, (u16)regs->ds, (u16)regs->es, (u16)regs->fs, gs, regs->ss, regs->flags);

	अगर (mode != SHOW_REGS_ALL)
		वापस;

	cr0 = पढ़ो_cr0();
	cr2 = पढ़ो_cr2();
	cr3 = __पढ़ो_cr3();
	cr4 = __पढ़ो_cr4();
	prपूर्णांकk("%sCR0: %08lx CR2: %08lx CR3: %08lx CR4: %08lx\n",
		log_lvl, cr0, cr2, cr3, cr4);

	get_debugreg(d0, 0);
	get_debugreg(d1, 1);
	get_debugreg(d2, 2);
	get_debugreg(d3, 3);
	get_debugreg(d6, 6);
	get_debugreg(d7, 7);

	/* Only prपूर्णांक out debug रेजिस्टरs अगर they are in their non-शेष state. */
	अगर ((d0 == 0) && (d1 == 0) && (d2 == 0) && (d3 == 0) &&
	    (d6 == DR6_RESERVED) && (d7 == 0x400))
		वापस;

	prपूर्णांकk("%sDR0: %08lx DR1: %08lx DR2: %08lx DR3: %08lx\n",
		log_lvl, d0, d1, d2, d3);
	prपूर्णांकk("%sDR6: %08lx DR7: %08lx\n",
		log_lvl, d6, d7);
पूर्ण

व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
	BUG_ON(dead_task->mm);
	release_vm86_irqs(dead_task);
पूर्ण

व्योम
start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ new_ip, अचिन्हित दीर्घ new_sp)
अणु
	set_user_gs(regs, 0);
	regs->fs		= 0;
	regs->ds		= __USER_DS;
	regs->es		= __USER_DS;
	regs->ss		= __USER_DS;
	regs->cs		= __USER_CS;
	regs->ip		= new_ip;
	regs->sp		= new_sp;
	regs->flags		= X86_EFLAGS_IF;
पूर्ण
EXPORT_SYMBOL_GPL(start_thपढ़ो);


/*
 *	चयन_to(x,y) should चयन tasks from x to y.
 *
 * We fsave/fरुको so that an exception goes off at the right समय
 * (as a call from the fsave or fरुको in effect) rather than to
 * the wrong process. Lazy FP saving no दीर्घer makes any sense
 * with modern CPU's, and this simplअगरies a lot of things (SMP
 * and UP become the same).
 *
 * NOTE! We used to use the x86 hardware context चयनing. The
 * reason क्रम not using it any more becomes apparent when you
 * try to recover gracefully from saved state that is no दीर्घer
 * valid (stale segment रेजिस्टर values in particular). With the
 * hardware task-चयन, there is no way to fix up bad state in
 * a reasonable manner.
 *
 * The fact that Intel करोcuments the hardware task-चयनing to
 * be slow is a fairly red herring - this code is not noticeably
 * faster. However, there _is_ some room क्रम improvement here,
 * so the perक्रमmance issues may eventually be a valid poपूर्णांक.
 * More important, however, is the fact that this allows us much
 * more flexibility.
 *
 * The वापस value (in %ax) will be the "prev" task after
 * the task-चयन, and shows up in ret_from_विभाजन in entry.S,
 * क्रम example.
 */
__visible __notrace_funcgraph काष्ठा task_काष्ठा *
__चयन_to(काष्ठा task_काष्ठा *prev_p, काष्ठा task_काष्ठा *next_p)
अणु
	काष्ठा thपढ़ो_काष्ठा *prev = &prev_p->thपढ़ो,
			     *next = &next_p->thपढ़ो;
	काष्ठा fpu *prev_fpu = &prev->fpu;
	काष्ठा fpu *next_fpu = &next->fpu;
	पूर्णांक cpu = smp_processor_id();

	/* never put a prपूर्णांकk in __चयन_to... prपूर्णांकk() calls wake_up*() indirectly */

	अगर (!test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		चयन_fpu_prepare(prev_fpu, cpu);

	/*
	 * Save away %gs. No need to save %fs, as it was saved on the
	 * stack on entry.  No need to save %es and %ds, as those are
	 * always kernel segments जबतक inside the kernel.  Doing this
	 * beक्रमe setting the new TLS descriptors aव्योमs the situation
	 * where we temporarily have non-reloadable segments in %fs
	 * and %gs.  This could be an issue अगर the NMI handler ever
	 * used %fs or %gs (it करोes not today), or अगर the kernel is
	 * running inside of a hypervisor layer.
	 */
	lazy_save_gs(prev->gs);

	/*
	 * Load the per-thपढ़ो Thपढ़ो-Local Storage descriptor.
	 */
	load_TLS(next, cpu);

	चयन_to_extra(prev_p, next_p);

	/*
	 * Leave lazy mode, flushing any hypercalls made here.
	 * This must be करोne beक्रमe restoring TLS segments so
	 * the GDT and LDT are properly updated.
	 */
	arch_end_context_चयन(next_p);

	/*
	 * Reload esp0 and cpu_current_top_of_stack.  This changes
	 * current_thपढ़ो_info().  Refresh the SYSENTER configuration in
	 * हाल prev or next is vm86.
	 */
	update_task_stack(next_p);
	refresh_sysenter_cs(next);
	this_cpu_ग_लिखो(cpu_current_top_of_stack,
		       (अचिन्हित दीर्घ)task_stack_page(next_p) +
		       THREAD_SIZE);

	/*
	 * Restore %gs अगर needed (which is common)
	 */
	अगर (prev->gs | next->gs)
		lazy_load_gs(next->gs);

	this_cpu_ग_लिखो(current_task, next_p);

	चयन_fpu_finish(next_fpu);

	/* Load the Intel cache allocation PQR MSR. */
	resctrl_sched_in();

	वापस prev_p;
पूर्ण

SYSCALL_DEFINE2(arch_prctl, पूर्णांक, option, अचिन्हित दीर्घ, arg2)
अणु
	वापस करो_arch_prctl_common(current, option, arg2);
पूर्ण
