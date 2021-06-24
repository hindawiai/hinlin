<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/process.c
 *
 * Original Copyright (C) 1995  Linus Torvalds
 * Copyright (C) 1996-2000 Russell King - Converted to ARM.
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/compat.h>
#समावेश <linux/efi.h>
#समावेश <linux/elf.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/nospec.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/unistd.h>
#समावेश <linux/user.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/pm.h>
#समावेश <linux/tick.h>
#समावेश <linux/utsname.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/personality.h>
#समावेश <linux/notअगरier.h>
#समावेश <trace/events/घातer.h>
#समावेश <linux/percpu.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/prctl.h>

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/arch_gicv3.h>
#समावेश <यंत्र/compat.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/exec.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/poपूर्णांकer_auth.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#अगर defined(CONFIG_STACKPROTECTOR) && !defined(CONFIG_STACKPROTECTOR_PER_TASK)
#समावेश <linux/stackprotector.h>
अचिन्हित दीर्घ __stack_chk_guard __पढ़ो_mostly;
EXPORT_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

/*
 * Function poपूर्णांकers to optional machine specअगरic functions
 */
व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL_GPL(pm_घातer_off);

व्योम (*arm_pm_restart)(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *cmd);

अटल व्योम noinstr __cpu_करो_idle(व्योम)
अणु
	dsb(sy);
	wfi();
पूर्ण

अटल व्योम noinstr __cpu_करो_idle_irqprio(व्योम)
अणु
	अचिन्हित दीर्घ pmr;
	अचिन्हित दीर्घ daअगर_bits;

	daअगर_bits = पढ़ो_sysreg(daअगर);
	ग_लिखो_sysreg(daअगर_bits | PSR_I_BIT | PSR_F_BIT, daअगर);

	/*
	 * Unmask PMR beक्रमe going idle to make sure पूर्णांकerrupts can
	 * be उठाओd.
	 */
	pmr = gic_पढ़ो_pmr();
	gic_ग_लिखो_pmr(GIC_PRIO_IRQON | GIC_PRIO_PSR_I_SET);

	__cpu_करो_idle();

	gic_ग_लिखो_pmr(pmr);
	ग_लिखो_sysreg(daअगर_bits, daअगर);
पूर्ण

/*
 *	cpu_करो_idle()
 *
 *	Idle the processor (रुको क्रम पूर्णांकerrupt).
 *
 *	If the CPU supports priority masking we must करो additional work to
 *	ensure that पूर्णांकerrupts are not masked at the PMR (because the core will
 *	not wake up अगर we block the wake up संकेत in the पूर्णांकerrupt controller).
 */
व्योम noinstr cpu_करो_idle(व्योम)
अणु
	अगर (प्रणाली_uses_irq_prio_masking())
		__cpu_करो_idle_irqprio();
	अन्यथा
		__cpu_करो_idle();
पूर्ण

/*
 * This is our शेष idle handler.
 */
व्योम noinstr arch_cpu_idle(व्योम)
अणु
	/*
	 * This should करो all the घड़ी चयनing and रुको क्रम पूर्णांकerrupt
	 * tricks
	 */
	cpu_करो_idle();
	raw_local_irq_enable();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम arch_cpu_idle_dead(व्योम)
अणु
       cpu_die();
पूर्ण
#पूर्ण_अगर

/*
 * Called by kexec, immediately prior to machine_kexec().
 *
 * This must completely disable all secondary CPUs; simply causing those CPUs
 * to execute e.g. a RAM-based pin loop is not sufficient. This allows the
 * kexec'd kernel to use any and all RAM as it sees fit, without having to
 * aव्योम any code or data used by any SW CPU pin loop. The CPU hotplug
 * functionality embodied in smpt_shutकरोwn_nonboot_cpus() to achieve this.
 */
व्योम machine_shutकरोwn(व्योम)
अणु
	smp_shutकरोwn_nonboot_cpus(reboot_cpu);
पूर्ण

/*
 * Halting simply requires that the secondary CPUs stop perक्रमming any
 * activity (executing tasks, handling पूर्णांकerrupts). smp_send_stop()
 * achieves this.
 */
व्योम machine_halt(व्योम)
अणु
	local_irq_disable();
	smp_send_stop();
	जबतक (1);
पूर्ण

/*
 * Power-off simply requires that the secondary CPUs stop perक्रमming any
 * activity (executing tasks, handling पूर्णांकerrupts). smp_send_stop()
 * achieves this. When the प्रणाली घातer is turned off, it will take all CPUs
 * with it.
 */
व्योम machine_घातer_off(व्योम)
अणु
	local_irq_disable();
	smp_send_stop();
	अगर (pm_घातer_off)
		pm_घातer_off();
पूर्ण

/*
 * Restart requires that the secondary CPUs stop perक्रमming any activity
 * जबतक the primary CPU resets the प्रणाली. Systems with multiple CPUs must
 * provide a HW restart implementation, to ensure that all CPUs reset at once.
 * This is required so that any code running after reset on the primary CPU
 * करोesn't have to co-ordinate with other CPUs to ensure they aren't still
 * executing pre-reset code, and using RAM that the primary CPU's code wishes
 * to use. Implementing such co-ordination would be essentially impossible.
 */
व्योम machine_restart(अक्षर *cmd)
अणु
	/* Disable पूर्णांकerrupts first */
	local_irq_disable();
	smp_send_stop();

	/*
	 * UpdateCapsule() depends on the प्रणाली being reset via
	 * ResetSystem().
	 */
	अगर (efi_enabled(EFI_RUNTIME_SERVICES))
		efi_reboot(reboot_mode, शून्य);

	/* Now call the architecture specअगरic reboot code. */
	अगर (arm_pm_restart)
		arm_pm_restart(reboot_mode, cmd);
	अन्यथा
		करो_kernel_restart(cmd);

	/*
	 * Whoops - the architecture was unable to reboot.
	 */
	prपूर्णांकk("Reboot failed -- System halted\n");
	जबतक (1);
पूर्ण

#घोषणा bstr(suffix, str) [PSR_BTYPE_ ## suffix >> PSR_BTYPE_SHIFT] = str
अटल स्थिर अक्षर *स्थिर btypes[] = अणु
	bstr(NONE, "--"),
	bstr(  JC, "jc"),
	bstr(   C, "-c"),
	bstr(  J , "j-")
पूर्ण;
#अघोषित bstr

अटल व्योम prपूर्णांक_pstate(काष्ठा pt_regs *regs)
अणु
	u64 pstate = regs->pstate;

	अगर (compat_user_mode(regs)) अणु
		prपूर्णांकk("pstate: %08llx (%c%c%c%c %c %s %s %c%c%c)\n",
			pstate,
			pstate & PSR_AA32_N_BIT ? 'N' : 'n',
			pstate & PSR_AA32_Z_BIT ? 'Z' : 'z',
			pstate & PSR_AA32_C_BIT ? 'C' : 'c',
			pstate & PSR_AA32_V_BIT ? 'V' : 'v',
			pstate & PSR_AA32_Q_BIT ? 'Q' : 'q',
			pstate & PSR_AA32_T_BIT ? "T32" : "A32",
			pstate & PSR_AA32_E_BIT ? "BE" : "LE",
			pstate & PSR_AA32_A_BIT ? 'A' : 'a',
			pstate & PSR_AA32_I_BIT ? 'I' : 'i',
			pstate & PSR_AA32_F_BIT ? 'F' : 'f');
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *btype_str = btypes[(pstate & PSR_BTYPE_MASK) >>
					       PSR_BTYPE_SHIFT];

		prपूर्णांकk("pstate: %08llx (%c%c%c%c %c%c%c%c %cPAN %cUAO %cTCO BTYPE=%s)\n",
			pstate,
			pstate & PSR_N_BIT ? 'N' : 'n',
			pstate & PSR_Z_BIT ? 'Z' : 'z',
			pstate & PSR_C_BIT ? 'C' : 'c',
			pstate & PSR_V_BIT ? 'V' : 'v',
			pstate & PSR_D_BIT ? 'D' : 'd',
			pstate & PSR_A_BIT ? 'A' : 'a',
			pstate & PSR_I_BIT ? 'I' : 'i',
			pstate & PSR_F_BIT ? 'F' : 'f',
			pstate & PSR_PAN_BIT ? '+' : '-',
			pstate & PSR_UAO_BIT ? '+' : '-',
			pstate & PSR_TCO_BIT ? '+' : '-',
			btype_str);
	पूर्ण
पूर्ण

व्योम __show_regs(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, top_reg;
	u64 lr, sp;

	अगर (compat_user_mode(regs)) अणु
		lr = regs->compat_lr;
		sp = regs->compat_sp;
		top_reg = 12;
	पूर्ण अन्यथा अणु
		lr = regs->regs[30];
		sp = regs->sp;
		top_reg = 29;
	पूर्ण

	show_regs_prपूर्णांक_info(KERN_DEFAULT);
	prपूर्णांक_pstate(regs);

	अगर (!user_mode(regs)) अणु
		prपूर्णांकk("pc : %pS\n", (व्योम *)regs->pc);
		prपूर्णांकk("lr : %pS\n", (व्योम *)ptrauth_strip_insn_pac(lr));
	पूर्ण अन्यथा अणु
		prपूर्णांकk("pc : %016llx\n", regs->pc);
		prपूर्णांकk("lr : %016llx\n", lr);
	पूर्ण

	prपूर्णांकk("sp : %016llx\n", sp);

	अगर (प्रणाली_uses_irq_prio_masking())
		prपूर्णांकk("pmr_save: %08llx\n", regs->pmr_save);

	i = top_reg;

	जबतक (i >= 0) अणु
		prपूर्णांकk("x%-2d: %016llx", i, regs->regs[i]);

		जबतक (i-- % 3)
			pr_cont(" x%-2d: %016llx", i, regs->regs[i]);

		pr_cont("\n");
	पूर्ण
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	__show_regs(regs);
	dump_backtrace(regs, शून्य, KERN_DEFAULT);
पूर्ण

अटल व्योम tls_thपढ़ो_flush(व्योम)
अणु
	ग_लिखो_sysreg(0, tpidr_el0);

	अगर (is_compat_task()) अणु
		current->thपढ़ो.uw.tp_value = 0;

		/*
		 * We need to ensure ordering between the shaकरोw state and the
		 * hardware state, so that we करोn't corrupt the hardware state
		 * with a stale shaकरोw state during context चयन.
		 */
		barrier();
		ग_लिखो_sysreg(0, tpidrro_el0);
	पूर्ण
पूर्ण

अटल व्योम flush_tagged_addr_state(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_ARM64_TAGGED_ADDR_ABI))
		clear_thपढ़ो_flag(TIF_TAGGED_ADDR);
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
	fpsimd_flush_thपढ़ो();
	tls_thपढ़ो_flush();
	flush_ptrace_hw_अवरोधpoपूर्णांक(current);
	flush_tagged_addr_state();
पूर्ण

व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

व्योम arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk)
अणु
	fpsimd_release_task(tsk);
पूर्ण

पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	अगर (current->mm)
		fpsimd_preserve_current_state();
	*dst = *src;

	/* We rely on the above assignment to initialize dst's thपढ़ो_flags: */
	BUILD_BUG_ON(!IS_ENABLED(CONFIG_THREAD_INFO_IN_TASK));

	/*
	 * Detach src's sve_state (अगर any) from dst so that it करोes not
	 * get erroneously used or मुक्तd prematurely.  dst's sve_state
	 * will be allocated on demand later on अगर dst uses SVE.
	 * For consistency, also clear TIF_SVE here: this could be करोne
	 * later in copy_process(), but to aव्योम tripping up future
	 * मुख्यtainers it is best not to leave TIF_SVE and sve_state in
	 * an inconsistent state, even temporarily.
	 */
	dst->thपढ़ो.sve_state = शून्य;
	clear_tsk_thपढ़ो_flag(dst, TIF_SVE);

	/* clear any pending asynchronous tag fault उठाओd by the parent */
	clear_tsk_thपढ़ो_flag(dst, TIF_MTE_ASYNC_FAULT);

	वापस 0;
पूर्ण

यंत्रlinkage व्योम ret_from_विभाजन(व्योम) यंत्र("ret_from_fork");

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ stack_start,
		अचिन्हित दीर्घ stk_sz, काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs = task_pt_regs(p);

	स_रखो(&p->thपढ़ो.cpu_context, 0, माप(काष्ठा cpu_context));

	/*
	 * In हाल p was allocated the same task_काष्ठा poपूर्णांकer as some
	 * other recently-निकासed task, make sure p is disassociated from
	 * any cpu that may have run that now-निकासed task recently.
	 * Otherwise we could erroneously skip reloading the FPSIMD
	 * रेजिस्टरs क्रम p.
	 */
	fpsimd_flush_task_state(p);

	ptrauth_thपढ़ो_init_kernel(p);

	अगर (likely(!(p->flags & (PF_KTHREAD | PF_IO_WORKER)))) अणु
		*childregs = *current_pt_regs();
		childregs->regs[0] = 0;

		/*
		 * Read the current TLS poपूर्णांकer from tpidr_el0 as it may be
		 * out-of-sync with the saved value.
		 */
		*task_user_tls(p) = पढ़ो_sysreg(tpidr_el0);

		अगर (stack_start) अणु
			अगर (is_compat_thपढ़ो(task_thपढ़ो_info(p)))
				childregs->compat_sp = stack_start;
			अन्यथा
				childregs->sp = stack_start;
		पूर्ण

		/*
		 * If a TLS poपूर्णांकer was passed to clone, use it क्रम the new
		 * thपढ़ो.
		 */
		अगर (clone_flags & CLONE_SETTLS)
			p->thपढ़ो.uw.tp_value = tls;
	पूर्ण अन्यथा अणु
		/*
		 * A kthपढ़ो has no context to ERET to, so ensure any buggy
		 * ERET is treated as an illegal exception वापस.
		 *
		 * When a user task is created from a kthपढ़ो, childregs will
		 * be initialized by start_thपढ़ो() or start_compat_thपढ़ो().
		 */
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		childregs->pstate = PSR_MODE_EL1h | PSR_IL_BIT;

		p->thपढ़ो.cpu_context.x19 = stack_start;
		p->thपढ़ो.cpu_context.x20 = stk_sz;
	पूर्ण
	p->thपढ़ो.cpu_context.pc = (अचिन्हित दीर्घ)ret_from_विभाजन;
	p->thपढ़ो.cpu_context.sp = (अचिन्हित दीर्घ)childregs;

	ptrace_hw_copy_thपढ़ो(p);

	वापस 0;
पूर्ण

व्योम tls_preserve_current_state(व्योम)
अणु
	*task_user_tls(current) = पढ़ो_sysreg(tpidr_el0);
पूर्ण

अटल व्योम tls_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
	tls_preserve_current_state();

	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(next)))
		ग_लिखो_sysreg(next->thपढ़ो.uw.tp_value, tpidrro_el0);
	अन्यथा अगर (!arm64_kernel_unmapped_at_el0())
		ग_लिखो_sysreg(0, tpidrro_el0);

	ग_लिखो_sysreg(*task_user_tls(next), tpidr_el0);
पूर्ण

/*
 * Force SSBS state on context-चयन, since it may be lost after migrating
 * from a CPU which treats the bit as RES0 in a heterogeneous प्रणाली.
 */
अटल व्योम ssbs_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
	/*
	 * Nothing to करो क्रम kernel thपढ़ोs, but 'regs' may be junk
	 * (e.g. idle task) so check the flags and bail early.
	 */
	अगर (unlikely(next->flags & PF_KTHREAD))
		वापस;

	/*
	 * If all CPUs implement the SSBS extension, then we just need to
	 * context-चयन the PSTATE field.
	 */
	अगर (cpus_have_स्थिर_cap(ARM64_SSBS))
		वापस;

	spectre_v4_enable_task_mitigation(next);
पूर्ण

/*
 * We store our current task in sp_el0, which is clobbered by userspace. Keep a
 * shaकरोw copy so that we can restore this upon entry from userspace.
 *
 * This is *only* क्रम exception entry from EL0, and is not valid until we
 * __चयन_to() a user task.
 */
DEFINE_PER_CPU(काष्ठा task_काष्ठा *, __entry_task);

अटल व्योम entry_task_चयन(काष्ठा task_काष्ठा *next)
अणु
	__this_cpu_ग_लिखो(__entry_task, next);
पूर्ण

/*
 * ARM erratum 1418040 handling, affecting the 32bit view of CNTVCT.
 * Assuming the भव counter is enabled at the beginning of बार:
 *
 * - disable access when चयनing from a 64bit task to a 32bit task
 * - enable access when चयनing from a 32bit task to a 64bit task
 */
अटल व्योम erratum_1418040_thपढ़ो_चयन(काष्ठा task_काष्ठा *prev,
					  काष्ठा task_काष्ठा *next)
अणु
	bool prev32, next32;
	u64 val;

	अगर (!IS_ENABLED(CONFIG_ARM64_ERRATUM_1418040))
		वापस;

	prev32 = is_compat_thपढ़ो(task_thपढ़ो_info(prev));
	next32 = is_compat_thपढ़ो(task_thपढ़ो_info(next));

	अगर (prev32 == next32 || !this_cpu_has_cap(ARM64_WORKAROUND_1418040))
		वापस;

	val = पढ़ो_sysreg(cntkctl_el1);

	अगर (!next32)
		val |= ARCH_TIMER_USR_VCT_ACCESS_EN;
	अन्यथा
		val &= ~ARCH_TIMER_USR_VCT_ACCESS_EN;

	ग_लिखो_sysreg(val, cntkctl_el1);
पूर्ण

अटल व्योम update_sctlr_el1(u64 sctlr)
अणु
	/*
	 * EnIA must not be cleared जबतक in the kernel as this is necessary क्रम
	 * in-kernel PAC. It will be cleared on kernel निकास अगर needed.
	 */
	sysreg_clear_set(sctlr_el1, SCTLR_USER_MASK & ~SCTLR_ELx_ENIA, sctlr);

	/* ISB required क्रम the kernel uaccess routines when setting TCF0. */
	isb();
पूर्ण

व्योम set_task_sctlr_el1(u64 sctlr)
अणु
	/*
	 * __चयन_to() checks current->thपढ़ो.sctlr as an
	 * optimisation. Disable preemption so that it करोes not see
	 * the variable update beक्रमe the SCTLR_EL1 one.
	 */
	preempt_disable();
	current->thपढ़ो.sctlr_user = sctlr;
	update_sctlr_el1(sctlr);
	preempt_enable();
पूर्ण

/*
 * Thपढ़ो चयनing.
 */
__notrace_funcgraph काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *prev,
				काष्ठा task_काष्ठा *next)
अणु
	काष्ठा task_काष्ठा *last;

	fpsimd_thपढ़ो_चयन(next);
	tls_thपढ़ो_चयन(next);
	hw_अवरोधpoपूर्णांक_thपढ़ो_चयन(next);
	contextidr_thपढ़ो_चयन(next);
	entry_task_चयन(next);
	ssbs_thपढ़ो_चयन(next);
	erratum_1418040_thपढ़ो_चयन(prev, next);
	ptrauth_thपढ़ो_चयन_user(next);

	/*
	 * Complete any pending TLB or cache मुख्यtenance on this CPU in हाल
	 * the thपढ़ो migrates to a dअगरferent CPU.
	 * This full barrier is also required by the membarrier प्रणाली
	 * call.
	 */
	dsb(ish);

	/*
	 * MTE thपढ़ो चयनing must happen after the DSB above to ensure that
	 * any asynchronous tag check faults have been logged in the TFSR*_EL1
	 * रेजिस्टरs.
	 */
	mte_thपढ़ो_चयन(next);
	/* aव्योम expensive SCTLR_EL1 accesses अगर no change */
	अगर (prev->thपढ़ो.sctlr_user != next->thपढ़ो.sctlr_user)
		update_sctlr_el1(next->thपढ़ो.sctlr_user);

	/* the actual thपढ़ो चयन */
	last = cpu_चयन_to(prev, next);

	वापस last;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा stackframe frame;
	अचिन्हित दीर्घ stack_page, ret = 0;
	पूर्णांक count = 0;
	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	stack_page = (अचिन्हित दीर्घ)try_get_task_stack(p);
	अगर (!stack_page)
		वापस 0;

	start_backtrace(&frame, thपढ़ो_saved_fp(p), thपढ़ो_saved_pc(p));

	करो अणु
		अगर (unwind_frame(p, &frame))
			जाओ out;
		अगर (!in_sched_functions(frame.pc)) अणु
			ret = frame.pc;
			जाओ out;
		पूर्ण
	पूर्ण जबतक (count++ < 16);

out:
	put_task_stack(p);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ arch_align_stack(अचिन्हित दीर्घ sp)
अणु
	अगर (!(current->personality & ADDR_NO_RANDOMIZE) && अक्रमomize_va_space)
		sp -= get_अक्रमom_पूर्णांक() & ~PAGE_MASK;
	वापस sp & ~0xf;
पूर्ण

/*
 * Called from setup_new_exec() after (COMPAT_)SET_PERSONALITY.
 */
व्योम arch_setup_new_exec(व्योम)
अणु
	current->mm->context.flags = is_compat_task() ? MMCF_AARCH32 : 0;

	ptrauth_thपढ़ो_init_user();
	mte_thपढ़ो_init_user();

	अगर (task_spec_ssb_noexec(current)) अणु
		arch_prctl_spec_ctrl_set(current, PR_SPEC_STORE_BYPASS,
					 PR_SPEC_ENABLE);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARM64_TAGGED_ADDR_ABI
/*
 * Control the relaxed ABI allowing tagged user addresses पूर्णांकo the kernel.
 */
अटल अचिन्हित पूर्णांक tagged_addr_disabled;

दीर्घ set_tagged_addr_ctrl(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ valid_mask = PR_TAGGED_ADDR_ENABLE;
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(task);

	अगर (is_compat_thपढ़ो(ti))
		वापस -EINVAL;

	अगर (प्रणाली_supports_mte())
		valid_mask |= PR_MTE_TCF_MASK | PR_MTE_TAG_MASK;

	अगर (arg & ~valid_mask)
		वापस -EINVAL;

	/*
	 * Do not allow the enabling of the tagged address ABI अगर globally
	 * disabled via sysctl abi.tagged_addr_disabled.
	 */
	अगर (arg & PR_TAGGED_ADDR_ENABLE && tagged_addr_disabled)
		वापस -EINVAL;

	अगर (set_mte_ctrl(task, arg) != 0)
		वापस -EINVAL;

	update_ti_thपढ़ो_flag(ti, TIF_TAGGED_ADDR, arg & PR_TAGGED_ADDR_ENABLE);

	वापस 0;
पूर्ण

दीर्घ get_tagged_addr_ctrl(काष्ठा task_काष्ठा *task)
अणु
	दीर्घ ret = 0;
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(task);

	अगर (is_compat_thपढ़ो(ti))
		वापस -EINVAL;

	अगर (test_ti_thपढ़ो_flag(ti, TIF_TAGGED_ADDR))
		ret = PR_TAGGED_ADDR_ENABLE;

	ret |= get_mte_ctrl(task);

	वापस ret;
पूर्ण

/*
 * Global sysctl to disable the tagged user addresses support. This control
 * only prevents the tagged address ABI enabling via prctl() and करोes not
 * disable it क्रम tasks that alपढ़ोy opted in to the relaxed ABI.
 */

अटल काष्ठा ctl_table tagged_addr_sysctl_table[] = अणु
	अणु
		.procname	= "tagged_addr_disabled",
		.mode		= 0644,
		.data		= &tagged_addr_disabled,
		.maxlen		= माप(पूर्णांक),
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init tagged_addr_init(व्योम)
अणु
	अगर (!रेजिस्टर_sysctl("abi", tagged_addr_sysctl_table))
		वापस -EINVAL;
	वापस 0;
पूर्ण

core_initcall(tagged_addr_init);
#पूर्ण_अगर	/* CONFIG_ARM64_TAGGED_ADDR_ABI */

यंत्रlinkage व्योम __sched arm64_preempt_schedule_irq(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();

	/*
	 * Preempting a task from an IRQ means we leave copies of PSTATE
	 * on the stack. cpufeature's enable calls may modअगरy PSTATE, but
	 * resuming one of these preempted tasks would unकरो those changes.
	 *
	 * Only allow a task to be preempted once cpufeatures have been
	 * enabled.
	 */
	अगर (प्रणाली_capabilities_finalized())
		preempt_schedule_irq();
पूर्ण

#अगर_घोषित CONFIG_BINFMT_ELF
पूर्णांक arch_elf_adjust_prot(पूर्णांक prot, स्थिर काष्ठा arch_elf_state *state,
			 bool has_पूर्णांकerp, bool is_पूर्णांकerp)
अणु
	/*
	 * For dynamically linked executables the पूर्णांकerpreter is
	 * responsible क्रम setting PROT_BTI on everything except
	 * itself.
	 */
	अगर (is_पूर्णांकerp != has_पूर्णांकerp)
		वापस prot;

	अगर (!(state->flags & ARM64_ELF_BTI))
		वापस prot;

	अगर (prot & PROT_EXEC)
		prot |= PROT_BTI;

	वापस prot;
पूर्ण
#पूर्ण_अगर
