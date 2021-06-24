<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * common.c - C code क्रम kernel entry and निकास
 * Copyright (c) 2015 Andrew Lutomirski
 *
 * Based on यंत्र and ptrace code by many authors.  The code here originated
 * in ptrace.c and संकेत.c.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/entry-common.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/export.h>
#समावेश <linux/nospec.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_XEN_PV
#समावेश <xen/xen-ops.h>
#समावेश <xen/events.h>
#पूर्ण_अगर

#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/io_biपंचांगap.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/irq_stack.h>

#अगर_घोषित CONFIG_X86_64
__visible noinstr व्योम करो_syscall_64(अचिन्हित दीर्घ nr, काष्ठा pt_regs *regs)
अणु
	add_अक्रमom_kstack_offset();
	nr = syscall_enter_from_user_mode(regs, nr);

	instrumentation_begin();
	अगर (likely(nr < NR_syscalls)) अणु
		nr = array_index_nospec(nr, NR_syscalls);
		regs->ax = sys_call_table[nr](regs);
#अगर_घोषित CONFIG_X86_X32_ABI
	पूर्ण अन्यथा अगर (likely((nr & __X32_SYSCALL_BIT) &&
			  (nr & ~__X32_SYSCALL_BIT) < X32_NR_syscalls)) अणु
		nr = array_index_nospec(nr & ~__X32_SYSCALL_BIT,
					X32_NR_syscalls);
		regs->ax = x32_sys_call_table[nr](regs);
#पूर्ण_अगर
	पूर्ण
	instrumentation_end();
	syscall_निकास_to_user_mode(regs);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
अटल __always_अंतरभूत अचिन्हित पूर्णांक syscall_32_enter(काष्ठा pt_regs *regs)
अणु
	अगर (IS_ENABLED(CONFIG_IA32_EMULATION))
		current_thपढ़ो_info()->status |= TS_COMPAT;

	वापस (अचिन्हित पूर्णांक)regs->orig_ax;
पूर्ण

/*
 * Invoke a 32-bit syscall.  Called with IRQs on in CONTEXT_KERNEL.
 */
अटल __always_अंतरभूत व्योम करो_syscall_32_irqs_on(काष्ठा pt_regs *regs,
						  अचिन्हित पूर्णांक nr)
अणु
	अगर (likely(nr < IA32_NR_syscalls)) अणु
		nr = array_index_nospec(nr, IA32_NR_syscalls);
		regs->ax = ia32_sys_call_table[nr](regs);
	पूर्ण
पूर्ण

/* Handles पूर्णांक $0x80 */
__visible noinstr व्योम करो_पूर्णांक80_syscall_32(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक nr = syscall_32_enter(regs);

	add_अक्रमom_kstack_offset();
	/*
	 * Subtlety here: अगर ptrace pokes something larger than 2^32-1 पूर्णांकo
	 * orig_ax, the अचिन्हित पूर्णांक वापस value truncates it.  This may
	 * or may not be necessary, but it matches the old यंत्र behavior.
	 */
	nr = (अचिन्हित पूर्णांक)syscall_enter_from_user_mode(regs, nr);
	instrumentation_begin();

	करो_syscall_32_irqs_on(regs, nr);

	instrumentation_end();
	syscall_निकास_to_user_mode(regs);
पूर्ण

अटल noinstr bool __करो_fast_syscall_32(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक nr = syscall_32_enter(regs);
	पूर्णांक res;

	add_अक्रमom_kstack_offset();
	/*
	 * This cannot use syscall_enter_from_user_mode() as it has to
	 * fetch EBP beक्रमe invoking any of the syscall entry work
	 * functions.
	 */
	syscall_enter_from_user_mode_prepare(regs);

	instrumentation_begin();
	/* Fetch EBP from where the vDSO stashed it. */
	अगर (IS_ENABLED(CONFIG_X86_64)) अणु
		/*
		 * Micro-optimization: the poपूर्णांकer we're following is
		 * explicitly 32 bits, so it can't be out of range.
		 */
		res = __get_user(*(u32 *)&regs->bp,
			 (u32 __user __क्रमce *)(अचिन्हित दीर्घ)(u32)regs->sp);
	पूर्ण अन्यथा अणु
		res = get_user(*(u32 *)&regs->bp,
		       (u32 __user __क्रमce *)(अचिन्हित दीर्घ)(u32)regs->sp);
	पूर्ण

	अगर (res) अणु
		/* User code screwed up. */
		regs->ax = -EFAULT;

		instrumentation_end();
		local_irq_disable();
		irqentry_निकास_to_user_mode(regs);
		वापस false;
	पूर्ण

	/* The हाल truncates any ptrace induced syscall nr > 2^32 -1 */
	nr = (अचिन्हित पूर्णांक)syscall_enter_from_user_mode_work(regs, nr);

	/* Now this is just like a normal syscall. */
	करो_syscall_32_irqs_on(regs, nr);

	instrumentation_end();
	syscall_निकास_to_user_mode(regs);
	वापस true;
पूर्ण

/* Returns 0 to वापस using IRET or 1 to वापस using SYSEXIT/SYSRETL. */
__visible noinstr दीर्घ करो_fast_syscall_32(काष्ठा pt_regs *regs)
अणु
	/*
	 * Called using the पूर्णांकernal vDSO SYSENTER/SYSCALL32 calling
	 * convention.  Adjust regs so it looks like we entered using पूर्णांक80.
	 */
	अचिन्हित दीर्घ landing_pad = (अचिन्हित दीर्घ)current->mm->context.vdso +
					vdso_image_32.sym_पूर्णांक80_landing_pad;

	/*
	 * SYSENTER loses EIP, and even SYSCALL32 needs us to skip क्रमward
	 * so that 'regs->ip -= 2' lands back on an पूर्णांक $0x80 inकाष्ठाion.
	 * Fix it up.
	 */
	regs->ip = landing_pad;

	/* Invoke the syscall. If it failed, keep it simple: use IRET. */
	अगर (!__करो_fast_syscall_32(regs))
		वापस 0;

#अगर_घोषित CONFIG_X86_64
	/*
	 * Opportunistic SYSRETL: अगर possible, try to वापस using SYSRETL.
	 * SYSRETL is available on all 64-bit CPUs, so we करोn't need to
	 * bother with SYSEXIT.
	 *
	 * Unlike 64-bit opportunistic SYSRET, we can't check that CX == IP,
	 * because the ECX fixup above will ensure that this is essentially
	 * never the हाल.
	 */
	वापस regs->cs == __USER32_CS && regs->ss == __USER_DS &&
		regs->ip == landing_pad &&
		(regs->flags & (X86_EFLAGS_RF | X86_EFLAGS_TF)) == 0;
#अन्यथा
	/*
	 * Opportunistic SYSEXIT: अगर possible, try to वापस using SYSEXIT.
	 *
	 * Unlike 64-bit opportunistic SYSRET, we can't check that CX == IP,
	 * because the ECX fixup above will ensure that this is essentially
	 * never the हाल.
	 *
	 * We करोn't allow syscalls at all from VM86 mode, but we still
	 * need to check VM, because we might be वापसing from sys_vm86.
	 */
	वापस अटल_cpu_has(X86_FEATURE_SEP) &&
		regs->cs == __USER_CS && regs->ss == __USER_DS &&
		regs->ip == landing_pad &&
		(regs->flags & (X86_EFLAGS_RF | X86_EFLAGS_TF | X86_EFLAGS_VM)) == 0;
#पूर्ण_अगर
पूर्ण

/* Returns 0 to वापस using IRET or 1 to वापस using SYSEXIT/SYSRETL. */
__visible noinstr दीर्घ करो_SYSENTER_32(काष्ठा pt_regs *regs)
अणु
	/* SYSENTER loses RSP, but the vDSO saved it in RBP. */
	regs->sp = regs->bp;

	/* SYSENTER clobbers EFLAGS.IF.  Assume it was set in usermode. */
	regs->flags |= X86_EFLAGS_IF;

	वापस करो_fast_syscall_32(regs);
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE0(ni_syscall)
अणु
	वापस -ENOSYS;
पूर्ण

#अगर_घोषित CONFIG_XEN_PV
#अगर_अघोषित CONFIG_PREEMPTION
/*
 * Some hypercalls issued by the toolstack can take many 10s of
 * seconds. Allow tasks running hypercalls via the privcmd driver to
 * be voluntarily preempted even अगर full kernel preemption is
 * disabled.
 *
 * Such preemptible hypercalls are bracketed by
 * xen_preemptible_hcall_begin() and xen_preemptible_hcall_end()
 * calls.
 */
DEFINE_PER_CPU(bool, xen_in_preemptible_hcall);
EXPORT_SYMBOL_GPL(xen_in_preemptible_hcall);

/*
 * In हाल of scheduling the flag must be cleared and restored after
 * वापसing from schedule as the task might move to a dअगरferent CPU.
 */
अटल __always_अंतरभूत bool get_and_clear_inhcall(व्योम)
अणु
	bool inhcall = __this_cpu_पढ़ो(xen_in_preemptible_hcall);

	__this_cpu_ग_लिखो(xen_in_preemptible_hcall, false);
	वापस inhcall;
पूर्ण

अटल __always_अंतरभूत व्योम restore_inhcall(bool inhcall)
अणु
	__this_cpu_ग_लिखो(xen_in_preemptible_hcall, inhcall);
पूर्ण
#अन्यथा
अटल __always_अंतरभूत bool get_and_clear_inhcall(व्योम) अणु वापस false; पूर्ण
अटल __always_अंतरभूत व्योम restore_inhcall(bool inhcall) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __xen_pv_evtchn_करो_upcall(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	inc_irq_stat(irq_hv_callback_count);

	xen_hvm_evtchn_करो_upcall();

	set_irq_regs(old_regs);
पूर्ण

__visible noinstr व्योम xen_pv_evtchn_करो_upcall(काष्ठा pt_regs *regs)
अणु
	irqentry_state_t state = irqentry_enter(regs);
	bool inhcall;

	run_sysvec_on_irqstack_cond(__xen_pv_evtchn_करो_upcall, regs);

	inhcall = get_and_clear_inhcall();
	अगर (inhcall && !WARN_ON_ONCE(state.निकास_rcu)) अणु
		instrumentation_begin();
		irqentry_निकास_cond_resched();
		instrumentation_end();
		restore_inhcall(inhcall);
	पूर्ण अन्यथा अणु
		irqentry_निकास(regs, state);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_XEN_PV */
