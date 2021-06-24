<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * x86 single-step support code, common to 32-bit and 64-bit.
 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/mmu_context.h>

अचिन्हित दीर्घ convert_ip_to_linear(काष्ठा task_काष्ठा *child, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr, seg;

	addr = regs->ip;
	seg = regs->cs;
	अगर (v8086_mode(regs)) अणु
		addr = (addr & 0xffff) + (seg << 4);
		वापस addr;
	पूर्ण

#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	/*
	 * We'll assume that the code segments in the GDT
	 * are all zero-based. That is largely true: the
	 * TLS segments are used क्रम data, and the PNPBIOS
	 * and APM bios ones we just ignore here.
	 */
	अगर ((seg & SEGMENT_TI_MASK) == SEGMENT_LDT) अणु
		काष्ठा desc_काष्ठा *desc;
		अचिन्हित दीर्घ base;

		seg >>= 3;

		mutex_lock(&child->mm->context.lock);
		अगर (unlikely(!child->mm->context.ldt ||
			     seg >= child->mm->context.ldt->nr_entries))
			addr = -1L; /* bogus selector, access would fault */
		अन्यथा अणु
			desc = &child->mm->context.ldt->entries[seg];
			base = get_desc_base(desc);

			/* 16-bit code segment? */
			अगर (!desc->d)
				addr &= 0xffff;
			addr += base;
		पूर्ण
		mutex_unlock(&child->mm->context.lock);
	पूर्ण
#पूर्ण_अगर

	वापस addr;
पूर्ण

अटल पूर्णांक is_setting_trap_flag(काष्ठा task_काष्ठा *child, काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, copied;
	अचिन्हित अक्षर opcode[15];
	अचिन्हित दीर्घ addr = convert_ip_to_linear(child, regs);

	copied = access_process_vm(child, addr, opcode, माप(opcode),
			FOLL_FORCE);
	क्रम (i = 0; i < copied; i++) अणु
		चयन (opcode[i]) अणु
		/* popf and iret */
		हाल 0x9d: हाल 0xcf:
			वापस 1;

			/* CHECKME: 64 65 */

		/* opcode and address size prefixes */
		हाल 0x66: हाल 0x67:
			जारी;
		/* irrelevant prefixes (segment overrides and repeats) */
		हाल 0x26: हाल 0x2e:
		हाल 0x36: हाल 0x3e:
		हाल 0x64: हाल 0x65:
		हाल 0xf0: हाल 0xf2: हाल 0xf3:
			जारी;

#अगर_घोषित CONFIG_X86_64
		हाल 0x40 ... 0x4f:
			अगर (!user_64bit_mode(regs))
				/* 32-bit mode: रेजिस्टर increment */
				वापस 0;
			/* 64-bit mode: REX prefix */
			जारी;
#पूर्ण_अगर

			/* CHECKME: f2, f3 */

		/*
		 * pushf: NOTE! We should probably not let
		 * the user see the TF bit being set. But
		 * it's more pain than it's worth to aव्योम
		 * it, and a debugger could emulate this
		 * all in user space अगर it _really_ cares.
		 */
		हाल 0x9c:
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Enable single-stepping.  Return nonzero अगर user mode is not using TF itself.
 */
अटल पूर्णांक enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(child);
	अचिन्हित दीर्घ oflags;

	/*
	 * If we stepped पूर्णांकo a sysenter/syscall insn, it trapped in
	 * kernel mode; करो_debug() cleared TF and set TIF_SINGLESTEP.
	 * If user-mode had set TF itself, then it's still clear from
	 * करो_debug() and we need to set it again to restore the user
	 * state so we करोn't wrongly set TIF_FORCED_TF below.
	 * If enable_single_step() was used last and that is what
	 * set TIF_SINGLESTEP, then both TF and TIF_FORCED_TF are
	 * alपढ़ोy set and our bookkeeping is fine.
	 */
	अगर (unlikely(test_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP)))
		regs->flags |= X86_EFLAGS_TF;

	/*
	 * Always set TIF_SINGLESTEP.  This will also
	 * cause us to set TF when वापसing to user mode.
	 */
	set_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);

	/*
	 * Ensure that a trap is triggered once stepping out of a प्रणाली
	 * call prior to executing any user inकाष्ठाion.
	 */
	set_task_syscall_work(child, SYSCALL_EXIT_TRAP);

	oflags = regs->flags;

	/* Set TF on the kernel stack.. */
	regs->flags |= X86_EFLAGS_TF;

	/*
	 * ..but अगर TF is changed by the inकाष्ठाion we will trace,
	 * करोn't mark it as being "us" that set it, so that we
	 * won't clear it by hand later.
	 *
	 * Note that अगर we करोn't actually execute the popf because
	 * of a संकेत arriving right now or suchlike, we will lose
	 * track of the fact that it really was "us" that set it.
	 */
	अगर (is_setting_trap_flag(child, regs)) अणु
		clear_tsk_thपढ़ो_flag(child, TIF_FORCED_TF);
		वापस 0;
	पूर्ण

	/*
	 * If TF was alपढ़ोy set, check whether it was us who set it.
	 * If not, we should never attempt a block step.
	 */
	अगर (oflags & X86_EFLAGS_TF)
		वापस test_tsk_thपढ़ो_flag(child, TIF_FORCED_TF);

	set_tsk_thपढ़ो_flag(child, TIF_FORCED_TF);

	वापस 1;
पूर्ण

व्योम set_task_blockstep(काष्ठा task_काष्ठा *task, bool on)
अणु
	अचिन्हित दीर्घ debugctl;

	/*
	 * Ensure irq/preemption can't change debugctl in between.
	 * Note also that both TIF_BLOCKSTEP and debugctl should
	 * be changed atomically wrt preemption.
	 *
	 * NOTE: this means that set/clear TIF_BLOCKSTEP is only safe अगर
	 * task is current or it can't be running, otherwise we can race
	 * with __चयन_to_xtra(). We rely on ptrace_मुक्तze_traced() but
	 * PTRACE_KILL is not safe.
	 */
	local_irq_disable();
	debugctl = get_debugctlmsr();
	अगर (on) अणु
		debugctl |= DEBUGCTLMSR_BTF;
		set_tsk_thपढ़ो_flag(task, TIF_BLOCKSTEP);
	पूर्ण अन्यथा अणु
		debugctl &= ~DEBUGCTLMSR_BTF;
		clear_tsk_thपढ़ो_flag(task, TIF_BLOCKSTEP);
	पूर्ण
	अगर (task == current)
		update_debugctlmsr(debugctl);
	local_irq_enable();
पूर्ण

/*
 * Enable single or block step.
 */
अटल व्योम enable_step(काष्ठा task_काष्ठा *child, bool block)
अणु
	/*
	 * Make sure block stepping (BTF) is not enabled unless it should be.
	 * Note that we करोn't try to worry about any is_setting_trap_flag()
	 * inकाष्ठाions after the first when using block stepping.
	 * So no one should try to use debugger block stepping in a program
	 * that uses user-mode single stepping itself.
	 */
	अगर (enable_single_step(child) && block)
		set_task_blockstep(child, true);
	अन्यथा अगर (test_tsk_thपढ़ो_flag(child, TIF_BLOCKSTEP))
		set_task_blockstep(child, false);
पूर्ण

व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	enable_step(child, 0);
पूर्ण

व्योम user_enable_block_step(काष्ठा task_काष्ठा *child)
अणु
	enable_step(child, 1);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	/*
	 * Make sure block stepping (BTF) is disabled.
	 */
	अगर (test_tsk_thपढ़ो_flag(child, TIF_BLOCKSTEP))
		set_task_blockstep(child, false);

	/* Always clear TIF_SINGLESTEP... */
	clear_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
	clear_task_syscall_work(child, SYSCALL_EXIT_TRAP);

	/* But touch TF only अगर it was set by us.. */
	अगर (test_and_clear_tsk_thपढ़ो_flag(child, TIF_FORCED_TF))
		task_pt_regs(child)->flags &= ~X86_EFLAGS_TF;
पूर्ण
