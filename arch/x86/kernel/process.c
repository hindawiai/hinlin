<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/prctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/idle.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/pm.h>
#समावेश <linux/tick.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/user-वापस-notअगरier.h>
#समावेश <linux/dmi.h>
#समावेश <linux/utsname.h>
#समावेश <linux/stackprotector.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/acpi.h>
#समावेश <linux/elf-अक्रमomize.h>
#समावेश <trace/events/घातer.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/apic.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/vm86.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/prctl.h>
#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/io_biपंचांगap.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/frame.h>

#समावेश "process.h"

/*
 * per-CPU TSS segments. Thपढ़ोs are completely 'soft' on Linux,
 * no more per-task TSS's. The TSS size is kept cacheline-aligned
 * so they are allowed to end up in the .data..cacheline_aligned
 * section. Since TSS's are completely CPU-local, we want them
 * on exact cacheline boundaries, to eliminate cacheline ping-pong.
 */
__visible DEFINE_PER_CPU_PAGE_ALIGNED(काष्ठा tss_काष्ठा, cpu_tss_rw) = अणु
	.x86_tss = अणु
		/*
		 * .sp0 is only used when entering ring 0 from a lower
		 * privilege level.  Since the init task never runs anything
		 * but ring 0 code, there is no need क्रम a valid value here.
		 * Poison it.
		 */
		.sp0 = (1UL << (BITS_PER_LONG-1)) + 1,

#अगर_घोषित CONFIG_X86_32
		.sp1 = TOP_OF_INIT_STACK,

		.ss0 = __KERNEL_DS,
		.ss1 = __KERNEL_CS,
#पूर्ण_अगर
		.io_biपंचांगap_base	= IO_BITMAP_OFFSET_INVALID,
	 पूर्ण,
पूर्ण;
EXPORT_PER_CPU_SYMBOL(cpu_tss_rw);

DEFINE_PER_CPU(bool, __tss_limit_invalid);
EXPORT_PER_CPU_SYMBOL_GPL(__tss_limit_invalid);

/*
 * this माला_लो called so that we can store lazy state पूर्णांकo memory and copy the
 * current task पूर्णांकo the new thपढ़ो.
 */
पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	स_नकल(dst, src, arch_task_काष्ठा_size);
#अगर_घोषित CONFIG_VM86
	dst->thपढ़ो.vm86 = शून्य;
#पूर्ण_अगर

	वापस fpu__copy(dst, src);
पूर्ण

/*
 * Free thपढ़ो data काष्ठाures etc..
 */
व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;
	काष्ठा fpu *fpu = &t->fpu;

	अगर (test_thपढ़ो_flag(TIF_IO_BITMAP))
		io_biपंचांगap_निकास(tsk);

	मुक्त_vm86(t);

	fpu__drop(fpu);
पूर्ण

अटल पूर्णांक set_new_tls(काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा user_desc __user *utls = (काष्ठा user_desc __user *)tls;

	अगर (in_ia32_syscall())
		वापस करो_set_thपढ़ो_area(p, -1, utls, 0);
	अन्यथा
		वापस करो_set_thपढ़ो_area_64(p, ARCH_SET_FS, tls);
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ sp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा inactive_task_frame *frame;
	काष्ठा विभाजन_frame *विभाजन_frame;
	काष्ठा pt_regs *childregs;
	पूर्णांक ret = 0;

	childregs = task_pt_regs(p);
	विभाजन_frame = container_of(childregs, काष्ठा विभाजन_frame, regs);
	frame = &विभाजन_frame->frame;

	frame->bp = encode_frame_poपूर्णांकer(childregs);
	frame->ret_addr = (अचिन्हित दीर्घ) ret_from_विभाजन;
	p->thपढ़ो.sp = (अचिन्हित दीर्घ) विभाजन_frame;
	p->thपढ़ो.io_biपंचांगap = शून्य;
	स_रखो(p->thपढ़ो.ptrace_bps, 0, माप(p->thपढ़ो.ptrace_bps));

#अगर_घोषित CONFIG_X86_64
	current_save_fsgs();
	p->thपढ़ो.fsindex = current->thपढ़ो.fsindex;
	p->thपढ़ो.fsbase = current->thपढ़ो.fsbase;
	p->thपढ़ो.gsindex = current->thपढ़ो.gsindex;
	p->thपढ़ो.gsbase = current->thपढ़ो.gsbase;

	savesegment(es, p->thपढ़ो.es);
	savesegment(ds, p->thपढ़ो.ds);
#अन्यथा
	p->thपढ़ो.sp0 = (अचिन्हित दीर्घ) (childregs + 1);
	/*
	 * Clear all status flags including IF and set fixed bit. 64bit
	 * करोes not have this initialization as the frame करोes not contain
	 * flags. The flags consistency (especially vs. AC) is there
	 * ensured via objtool, which lacks 32bit support.
	 */
	frame->flags = X86_EFLAGS_FIXED;
#पूर्ण_अगर

	/* Kernel thपढ़ो ? */
	अगर (unlikely(p->flags & PF_KTHREAD)) अणु
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		kthपढ़ो_frame_init(frame, sp, arg);
		वापस 0;
	पूर्ण

	frame->bx = 0;
	*childregs = *current_pt_regs();
	childregs->ax = 0;
	अगर (sp)
		childregs->sp = sp;

#अगर_घोषित CONFIG_X86_32
	task_user_gs(p) = get_user_gs(current_pt_regs());
#पूर्ण_अगर

	अगर (unlikely(p->flags & PF_IO_WORKER)) अणु
		/*
		 * An IO thपढ़ो is a user space thपढ़ो, but it करोesn't
		 * वापस to ret_after_विभाजन().
		 *
		 * In order to indicate that to tools like gdb,
		 * we reset the stack and inकाष्ठाion poपूर्णांकers.
		 *
		 * It करोes the same kernel frame setup to वापस to a kernel
		 * function that a kernel thपढ़ो करोes.
		 */
		childregs->sp = 0;
		childregs->ip = 0;
		kthपढ़ो_frame_init(frame, sp, arg);
		वापस 0;
	पूर्ण

	/* Set a new TLS क्रम the child thपढ़ो? */
	अगर (clone_flags & CLONE_SETTLS)
		ret = set_new_tls(p, tls);

	अगर (!ret && unlikely(test_tsk_thपढ़ो_flag(current, TIF_IO_BITMAP)))
		io_biपंचांगap_share(p);

	वापस ret;
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	flush_ptrace_hw_अवरोधpoपूर्णांक(tsk);
	स_रखो(tsk->thपढ़ो.tls_array, 0, माप(tsk->thपढ़ो.tls_array));

	fpu__clear_all(&tsk->thपढ़ो.fpu);
पूर्ण

व्योम disable_TSC(व्योम)
अणु
	preempt_disable();
	अगर (!test_and_set_thपढ़ो_flag(TIF_NOTSC))
		/*
		 * Must flip the CPU state synchronously with
		 * TIF_NOTSC in the current running context.
		 */
		cr4_set_bits(X86_CR4_TSD);
	preempt_enable();
पूर्ण

अटल व्योम enable_TSC(व्योम)
अणु
	preempt_disable();
	अगर (test_and_clear_thपढ़ो_flag(TIF_NOTSC))
		/*
		 * Must flip the CPU state synchronously with
		 * TIF_NOTSC in the current running context.
		 */
		cr4_clear_bits(X86_CR4_TSD);
	preempt_enable();
पूर्ण

पूर्णांक get_tsc_mode(अचिन्हित दीर्घ adr)
अणु
	अचिन्हित पूर्णांक val;

	अगर (test_thपढ़ो_flag(TIF_NOTSC))
		val = PR_TSC_संक_अंश;
	अन्यथा
		val = PR_TSC_ENABLE;

	वापस put_user(val, (अचिन्हित पूर्णांक __user *)adr);
पूर्ण

पूर्णांक set_tsc_mode(अचिन्हित पूर्णांक val)
अणु
	अगर (val == PR_TSC_संक_अंश)
		disable_TSC();
	अन्यथा अगर (val == PR_TSC_ENABLE)
		enable_TSC();
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

DEFINE_PER_CPU(u64, msr_misc_features_shaकरोw);

अटल व्योम set_cpuid_faulting(bool on)
अणु
	u64 msrval;

	msrval = this_cpu_पढ़ो(msr_misc_features_shaकरोw);
	msrval &= ~MSR_MISC_FEATURES_ENABLES_CPUID_FAULT;
	msrval |= (on << MSR_MISC_FEATURES_ENABLES_CPUID_FAULT_BIT);
	this_cpu_ग_लिखो(msr_misc_features_shaकरोw, msrval);
	wrmsrl(MSR_MISC_FEATURES_ENABLES, msrval);
पूर्ण

अटल व्योम disable_cpuid(व्योम)
अणु
	preempt_disable();
	अगर (!test_and_set_thपढ़ो_flag(TIF_NOCPUID)) अणु
		/*
		 * Must flip the CPU state synchronously with
		 * TIF_NOCPUID in the current running context.
		 */
		set_cpuid_faulting(true);
	पूर्ण
	preempt_enable();
पूर्ण

अटल व्योम enable_cpuid(व्योम)
अणु
	preempt_disable();
	अगर (test_and_clear_thपढ़ो_flag(TIF_NOCPUID)) अणु
		/*
		 * Must flip the CPU state synchronously with
		 * TIF_NOCPUID in the current running context.
		 */
		set_cpuid_faulting(false);
	पूर्ण
	preempt_enable();
पूर्ण

अटल पूर्णांक get_cpuid_mode(व्योम)
अणु
	वापस !test_thपढ़ो_flag(TIF_NOCPUID);
पूर्ण

अटल पूर्णांक set_cpuid_mode(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ cpuid_enabled)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_CPUID_FAULT))
		वापस -ENODEV;

	अगर (cpuid_enabled)
		enable_cpuid();
	अन्यथा
		disable_cpuid();

	वापस 0;
पूर्ण

/*
 * Called immediately after a successful exec.
 */
व्योम arch_setup_new_exec(व्योम)
अणु
	/* If cpuid was previously disabled क्रम this task, re-enable it. */
	अगर (test_thपढ़ो_flag(TIF_NOCPUID))
		enable_cpuid();

	/*
	 * Don't inherit TIF_SSBD across exec boundary when
	 * PR_SPEC_DISABLE_NOEXEC is used.
	 */
	अगर (test_thपढ़ो_flag(TIF_SSBD) &&
	    task_spec_ssb_noexec(current)) अणु
		clear_thपढ़ो_flag(TIF_SSBD);
		task_clear_spec_ssb_disable(current);
		task_clear_spec_ssb_noexec(current);
		speculation_ctrl_update(task_thपढ़ो_info(current)->flags);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
अटल अंतरभूत व्योम चयन_to_biपंचांगap(अचिन्हित दीर्घ tअगरp)
अणु
	/*
	 * Invalidate I/O biपंचांगap अगर the previous task used it. This prevents
	 * any possible leakage of an active I/O biपंचांगap.
	 *
	 * If the next task has an I/O biपंचांगap it will handle it on निकास to
	 * user mode.
	 */
	अगर (tअगरp & _TIF_IO_BITMAP)
		tss_invalidate_io_biपंचांगap();
पूर्ण

अटल व्योम tss_copy_io_biपंचांगap(काष्ठा tss_काष्ठा *tss, काष्ठा io_biपंचांगap *iobm)
अणु
	/*
	 * Copy at least the byte range of the incoming tasks biपंचांगap which
	 * covers the permitted I/O ports.
	 *
	 * If the previous task which used an I/O biपंचांगap had more bits
	 * permitted, then the copy needs to cover those as well so they
	 * get turned off.
	 */
	स_नकल(tss->io_biपंचांगap.biपंचांगap, iobm->biपंचांगap,
	       max(tss->io_biपंचांगap.prev_max, iobm->max));

	/*
	 * Store the new max and the sequence number of this biपंचांगap
	 * and a poपूर्णांकer to the biपंचांगap itself.
	 */
	tss->io_biपंचांगap.prev_max = iobm->max;
	tss->io_biपंचांगap.prev_sequence = iobm->sequence;
पूर्ण

/**
 * tss_update_io_biपंचांगap - Update I/O biपंचांगap beक्रमe निकासing to usermode
 */
व्योम native_tss_update_io_biपंचांगap(व्योम)
अणु
	काष्ठा tss_काष्ठा *tss = this_cpu_ptr(&cpu_tss_rw);
	काष्ठा thपढ़ो_काष्ठा *t = &current->thपढ़ो;
	u16 *base = &tss->x86_tss.io_biपंचांगap_base;

	अगर (!test_thपढ़ो_flag(TIF_IO_BITMAP)) अणु
		native_tss_invalidate_io_biपंचांगap();
		वापस;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_X86_IOPL_IOPERM) && t->iopl_emul == 3) अणु
		*base = IO_BITMAP_OFFSET_VALID_ALL;
	पूर्ण अन्यथा अणु
		काष्ठा io_biपंचांगap *iobm = t->io_biपंचांगap;

		/*
		 * Only copy biपंचांगap data when the sequence number dअगरfers. The
		 * update समय is accounted to the incoming task.
		 */
		अगर (tss->io_biपंचांगap.prev_sequence != iobm->sequence)
			tss_copy_io_biपंचांगap(tss, iobm);

		/* Enable the biपंचांगap */
		*base = IO_BITMAP_OFFSET_VALID_MAP;
	पूर्ण

	/*
	 * Make sure that the TSS limit is covering the IO biपंचांगap. It might have
	 * been cut करोwn by a VMEXIT to 0x67 which would cause a subsequent I/O
	 * access from user space to trigger a #GP because tbe biपंचांगap is outside
	 * the TSS limit.
	 */
	refresh_tss_limit();
पूर्ण
#अन्यथा /* CONFIG_X86_IOPL_IOPERM */
अटल अंतरभूत व्योम चयन_to_biपंचांगap(अचिन्हित दीर्घ tअगरp) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP

काष्ठा ssb_state अणु
	काष्ठा ssb_state	*shared_state;
	raw_spinlock_t		lock;
	अचिन्हित पूर्णांक		disable_state;
	अचिन्हित दीर्घ		local_state;
पूर्ण;

#घोषणा LSTATE_SSB	0

अटल DEFINE_PER_CPU(काष्ठा ssb_state, ssb_state);

व्योम speculative_store_bypass_ht_init(व्योम)
अणु
	काष्ठा ssb_state *st = this_cpu_ptr(&ssb_state);
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	अचिन्हित पूर्णांक cpu;

	st->local_state = 0;

	/*
	 * Shared state setup happens once on the first bringup
	 * of the CPU. It's not destroyed on CPU hotunplug.
	 */
	अगर (st->shared_state)
		वापस;

	raw_spin_lock_init(&st->lock);

	/*
	 * Go over HT siblings and check whether one of them has set up the
	 * shared state poपूर्णांकer alपढ़ोy.
	 */
	क्रम_each_cpu(cpu, topology_sibling_cpumask(this_cpu)) अणु
		अगर (cpu == this_cpu)
			जारी;

		अगर (!per_cpu(ssb_state, cpu).shared_state)
			जारी;

		/* Link it to the state of the sibling: */
		st->shared_state = per_cpu(ssb_state, cpu).shared_state;
		वापस;
	पूर्ण

	/*
	 * First HT sibling to come up on the core.  Link shared state of
	 * the first HT sibling to itself. The siblings on the same core
	 * which come up later will see the shared state poपूर्णांकer and link
	 * themselves to the state of this CPU.
	 */
	st->shared_state = st;
पूर्ण

/*
 * Logic is: First HT sibling enables SSBD क्रम both siblings in the core
 * and last sibling to disable it, disables it क्रम the whole core. This how
 * MSR_SPEC_CTRL works in "hardware":
 *
 *  CORE_SPEC_CTRL = THREAD0_SPEC_CTRL | THREAD1_SPEC_CTRL
 */
अटल __always_अंतरभूत व्योम amd_set_core_ssb_state(अचिन्हित दीर्घ tअगरn)
अणु
	काष्ठा ssb_state *st = this_cpu_ptr(&ssb_state);
	u64 msr = x86_amd_ls_cfg_base;

	अगर (!अटल_cpu_has(X86_FEATURE_ZEN)) अणु
		msr |= ssbd_tअगर_to_amd_ls_cfg(tअगरn);
		wrmsrl(MSR_AMD64_LS_CFG, msr);
		वापस;
	पूर्ण

	अगर (tअगरn & _TIF_SSBD) अणु
		/*
		 * Since this can race with prctl(), block reentry on the
		 * same CPU.
		 */
		अगर (__test_and_set_bit(LSTATE_SSB, &st->local_state))
			वापस;

		msr |= x86_amd_ls_cfg_ssbd_mask;

		raw_spin_lock(&st->shared_state->lock);
		/* First sibling enables SSBD: */
		अगर (!st->shared_state->disable_state)
			wrmsrl(MSR_AMD64_LS_CFG, msr);
		st->shared_state->disable_state++;
		raw_spin_unlock(&st->shared_state->lock);
	पूर्ण अन्यथा अणु
		अगर (!__test_and_clear_bit(LSTATE_SSB, &st->local_state))
			वापस;

		raw_spin_lock(&st->shared_state->lock);
		st->shared_state->disable_state--;
		अगर (!st->shared_state->disable_state)
			wrmsrl(MSR_AMD64_LS_CFG, msr);
		raw_spin_unlock(&st->shared_state->lock);
	पूर्ण
पूर्ण
#अन्यथा
अटल __always_अंतरभूत व्योम amd_set_core_ssb_state(अचिन्हित दीर्घ tअगरn)
अणु
	u64 msr = x86_amd_ls_cfg_base | ssbd_tअगर_to_amd_ls_cfg(tअगरn);

	wrmsrl(MSR_AMD64_LS_CFG, msr);
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम amd_set_ssb_virt_state(अचिन्हित दीर्घ tअगरn)
अणु
	/*
	 * SSBD has the same definition in SPEC_CTRL and VIRT_SPEC_CTRL,
	 * so ssbd_tअगर_to_spec_ctrl() just works.
	 */
	wrmsrl(MSR_AMD64_VIRT_SPEC_CTRL, ssbd_tअगर_to_spec_ctrl(tअगरn));
पूर्ण

/*
 * Update the MSRs managing speculation control, during context चयन.
 *
 * tअगरp: Previous task's thपढ़ो flags
 * tअगरn: Next task's thपढ़ो flags
 */
अटल __always_अंतरभूत व्योम __speculation_ctrl_update(अचिन्हित दीर्घ tअगरp,
						      अचिन्हित दीर्घ tअगरn)
अणु
	अचिन्हित दीर्घ tअगर_dअगरf = tअगरp ^ tअगरn;
	u64 msr = x86_spec_ctrl_base;
	bool updmsr = false;

	lockdep_निश्चित_irqs_disabled();

	/* Handle change of TIF_SSBD depending on the mitigation method. */
	अगर (अटल_cpu_has(X86_FEATURE_VIRT_SSBD)) अणु
		अगर (tअगर_dअगरf & _TIF_SSBD)
			amd_set_ssb_virt_state(tअगरn);
	पूर्ण अन्यथा अगर (अटल_cpu_has(X86_FEATURE_LS_CFG_SSBD)) अणु
		अगर (tअगर_dअगरf & _TIF_SSBD)
			amd_set_core_ssb_state(tअगरn);
	पूर्ण अन्यथा अगर (अटल_cpu_has(X86_FEATURE_SPEC_CTRL_SSBD) ||
		   अटल_cpu_has(X86_FEATURE_AMD_SSBD)) अणु
		updmsr |= !!(tअगर_dअगरf & _TIF_SSBD);
		msr |= ssbd_tअगर_to_spec_ctrl(tअगरn);
	पूर्ण

	/* Only evaluate TIF_SPEC_IB अगर conditional STIBP is enabled. */
	अगर (IS_ENABLED(CONFIG_SMP) &&
	    अटल_branch_unlikely(&चयन_to_cond_stibp)) अणु
		updmsr |= !!(tअगर_dअगरf & _TIF_SPEC_IB);
		msr |= stibp_tअगर_to_spec_ctrl(tअगरn);
	पूर्ण

	अगर (updmsr)
		wrmsrl(MSR_IA32_SPEC_CTRL, msr);
पूर्ण

अटल अचिन्हित दीर्घ speculation_ctrl_update_tअगर(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (test_and_clear_tsk_thपढ़ो_flag(tsk, TIF_SPEC_FORCE_UPDATE)) अणु
		अगर (task_spec_ssb_disable(tsk))
			set_tsk_thपढ़ो_flag(tsk, TIF_SSBD);
		अन्यथा
			clear_tsk_thपढ़ो_flag(tsk, TIF_SSBD);

		अगर (task_spec_ib_disable(tsk))
			set_tsk_thपढ़ो_flag(tsk, TIF_SPEC_IB);
		अन्यथा
			clear_tsk_thपढ़ो_flag(tsk, TIF_SPEC_IB);
	पूर्ण
	/* Return the updated thपढ़ोinfo flags*/
	वापस task_thपढ़ो_info(tsk)->flags;
पूर्ण

व्योम speculation_ctrl_update(अचिन्हित दीर्घ tअगर)
अणु
	अचिन्हित दीर्घ flags;

	/* Forced update. Make sure all relevant TIF flags are dअगरferent */
	local_irq_save(flags);
	__speculation_ctrl_update(~tअगर, tअगर);
	local_irq_restore(flags);
पूर्ण

/* Called from seccomp/prctl update */
व्योम speculation_ctrl_update_current(व्योम)
अणु
	preempt_disable();
	speculation_ctrl_update(speculation_ctrl_update_tअगर(current));
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम cr4_toggle_bits_irqsoff(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ newval, cr4 = this_cpu_पढ़ो(cpu_tlbstate.cr4);

	newval = cr4 ^ mask;
	अगर (newval != cr4) अणु
		this_cpu_ग_लिखो(cpu_tlbstate.cr4, newval);
		__ग_लिखो_cr4(newval);
	पूर्ण
पूर्ण

व्योम __चयन_to_xtra(काष्ठा task_काष्ठा *prev_p, काष्ठा task_काष्ठा *next_p)
अणु
	अचिन्हित दीर्घ tअगरp, tअगरn;

	tअगरn = READ_ONCE(task_thपढ़ो_info(next_p)->flags);
	tअगरp = READ_ONCE(task_thपढ़ो_info(prev_p)->flags);

	चयन_to_biपंचांगap(tअगरp);

	propagate_user_वापस_notअगरy(prev_p, next_p);

	अगर ((tअगरp & _TIF_BLOCKSTEP || tअगरn & _TIF_BLOCKSTEP) &&
	    arch_has_block_step()) अणु
		अचिन्हित दीर्घ debugctl, msk;

		rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
		debugctl &= ~DEBUGCTLMSR_BTF;
		msk = tअगरn & _TIF_BLOCKSTEP;
		debugctl |= (msk >> TIF_BLOCKSTEP) << DEBUGCTLMSR_BTF_SHIFT;
		wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
	पूर्ण

	अगर ((tअगरp ^ tअगरn) & _TIF_NOTSC)
		cr4_toggle_bits_irqsoff(X86_CR4_TSD);

	अगर ((tअगरp ^ tअगरn) & _TIF_NOCPUID)
		set_cpuid_faulting(!!(tअगरn & _TIF_NOCPUID));

	अगर (likely(!((tअगरp | tअगरn) & _TIF_SPEC_FORCE_UPDATE))) अणु
		__speculation_ctrl_update(tअगरp, tअगरn);
	पूर्ण अन्यथा अणु
		speculation_ctrl_update_tअगर(prev_p);
		tअगरn = speculation_ctrl_update_tअगर(next_p);

		/* Enक्रमce MSR update to ensure consistent state */
		__speculation_ctrl_update(~tअगरn, tअगरn);
	पूर्ण

	अगर ((tअगरp ^ tअगरn) & _TIF_SLD)
		चयन_to_sld(tअगरn);
पूर्ण

/*
 * Idle related variables and functions
 */
अचिन्हित दीर्घ boot_option_idle_override = IDLE_NO_OVERRIDE;
EXPORT_SYMBOL(boot_option_idle_override);

अटल व्योम (*x86_idle)(व्योम);

#अगर_अघोषित CONFIG_SMP
अटल अंतरभूत व्योम play_dead(व्योम)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर

व्योम arch_cpu_idle_enter(व्योम)
अणु
	tsc_verअगरy_tsc_adjust(false);
	local_touch_nmi();
पूर्ण

व्योम arch_cpu_idle_dead(व्योम)
अणु
	play_dead();
पूर्ण

/*
 * Called from the generic idle code.
 */
व्योम arch_cpu_idle(व्योम)
अणु
	x86_idle();
पूर्ण

/*
 * We use this अगर we करोn't have any better idle routine..
 */
व्योम __cpuidle शेष_idle(व्योम)
अणु
	raw_safe_halt();
पूर्ण
#अगर defined(CONFIG_APM_MODULE) || defined(CONFIG_HALTPOLL_CPUIDLE_MODULE)
EXPORT_SYMBOL(शेष_idle);
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN
bool xen_set_शेष_idle(व्योम)
अणु
	bool ret = !!x86_idle;

	x86_idle = शेष_idle;

	वापस ret;
पूर्ण
#पूर्ण_अगर

व्योम stop_this_cpu(व्योम *dummy)
अणु
	local_irq_disable();
	/*
	 * Remove this CPU:
	 */
	set_cpu_online(smp_processor_id(), false);
	disable_local_APIC();
	mcheck_cpu_clear(this_cpu_ptr(&cpu_info));

	/*
	 * Use wbinvd on processors that support SME. This provides support
	 * क्रम perक्रमming a successful kexec when going from SME inactive
	 * to SME active (or vice-versa). The cache must be cleared so that
	 * अगर there are entries with the same physical address, both with and
	 * without the encryption bit, they करोn't race each other when flushed
	 * and potentially end up with the wrong entry being committed to
	 * memory.
	 */
	अगर (boot_cpu_has(X86_FEATURE_SME))
		native_wbinvd();
	क्रम (;;) अणु
		/*
		 * Use native_halt() so that memory contents करोn't change
		 * (stack usage and variables) after possibly issuing the
		 * native_wbinvd() above.
		 */
		native_halt();
	पूर्ण
पूर्ण

/*
 * AMD Erratum 400 aware idle routine. We handle it the same way as C3 घातer
 * states (local apic समयr and TSC stop).
 *
 * XXX this function is completely buggered vs RCU and tracing.
 */
अटल व्योम amd_e400_idle(व्योम)
अणु
	/*
	 * We cannot use अटल_cpu_has_bug() here because X86_BUG_AMD_APIC_C1E
	 * माला_लो set after अटल_cpu_has() places have been converted via
	 * alternatives.
	 */
	अगर (!boot_cpu_has_bug(X86_BUG_AMD_APIC_C1E)) अणु
		शेष_idle();
		वापस;
	पूर्ण

	tick_broadcast_enter();

	शेष_idle();

	/*
	 * The चयन back from broadcast mode needs to be called with
	 * पूर्णांकerrupts disabled.
	 */
	raw_local_irq_disable();
	tick_broadcast_निकास();
	raw_local_irq_enable();
पूर्ण

/*
 * Intel Core2 and older machines prefer MWAIT over HALT क्रम C1.
 * We can't rely on cpuidle installing MWAIT, because it will not load
 * on प्रणालीs that support only C1 -- so the boot शेष must be MWAIT.
 *
 * Some AMD machines are the opposite, they depend on using HALT.
 *
 * So क्रम शेष C1, which is used during boot until cpuidle loads,
 * use MWAIT-C1 on Intel HW that has it, अन्यथा use HALT.
 */
अटल पूर्णांक prefer_mरुको_c1_over_halt(स्थिर काष्ठा cpuinfo_x86 *c)
अणु
	अगर (c->x86_venकरोr != X86_VENDOR_INTEL)
		वापस 0;

	अगर (!cpu_has(c, X86_FEATURE_MWAIT) || boot_cpu_has_bug(X86_BUG_MONITOR))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * MONITOR/MWAIT with no hपूर्णांकs, used क्रम शेष C1 state. This invokes MWAIT
 * with पूर्णांकerrupts enabled and no flags, which is backwards compatible with the
 * original MWAIT implementation.
 */
अटल __cpuidle व्योम mरुको_idle(व्योम)
अणु
	अगर (!current_set_polling_and_test()) अणु
		अगर (this_cpu_has(X86_BUG_CLFLUSH_MONITOR)) अणु
			mb(); /* quirk */
			clflush((व्योम *)&current_thपढ़ो_info()->flags);
			mb(); /* quirk */
		पूर्ण

		__monitor((व्योम *)&current_thपढ़ो_info()->flags, 0, 0);
		अगर (!need_resched())
			__sti_mरुको(0, 0);
		अन्यथा
			raw_local_irq_enable();
	पूर्ण अन्यथा अणु
		raw_local_irq_enable();
	पूर्ण
	__current_clr_polling();
पूर्ण

व्योम select_idle_routine(स्थिर काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (boot_option_idle_override == IDLE_POLL && smp_num_siblings > 1)
		pr_warn_once("WARNING: polling idle and HT enabled, performance may degrade\n");
#पूर्ण_अगर
	अगर (x86_idle || boot_option_idle_override == IDLE_POLL)
		वापस;

	अगर (boot_cpu_has_bug(X86_BUG_AMD_E400)) अणु
		pr_info("using AMD E400 aware idle routine\n");
		x86_idle = amd_e400_idle;
	पूर्ण अन्यथा अगर (prefer_mरुको_c1_over_halt(c)) अणु
		pr_info("using mwait in idle threads\n");
		x86_idle = mरुको_idle;
	पूर्ण अन्यथा
		x86_idle = शेष_idle;
पूर्ण

व्योम amd_e400_c1e_apic_setup(व्योम)
अणु
	अगर (boot_cpu_has_bug(X86_BUG_AMD_APIC_C1E)) अणु
		pr_info("Switch to broadcast mode on CPU%d\n", smp_processor_id());
		local_irq_disable();
		tick_broadcast_क्रमce();
		local_irq_enable();
	पूर्ण
पूर्ण

व्योम __init arch_post_acpi_subsys_init(व्योम)
अणु
	u32 lo, hi;

	अगर (!boot_cpu_has_bug(X86_BUG_AMD_E400))
		वापस;

	/*
	 * AMD E400 detection needs to happen after ACPI has been enabled. If
	 * the machine is affected K8_INTP_C1E_ACTIVE_MASK bits are set in
	 * MSR_K8_INT_PENDING_MSG.
	 */
	rdmsr(MSR_K8_INT_PENDING_MSG, lo, hi);
	अगर (!(lo & K8_INTP_C1E_ACTIVE_MASK))
		वापस;

	boot_cpu_set_bug(X86_BUG_AMD_APIC_C1E);

	अगर (!boot_cpu_has(X86_FEATURE_NONSTOP_TSC))
		mark_tsc_unstable("TSC halt in AMD C1E");
	pr_info("System has AMD C1E enabled\n");
पूर्ण

अटल पूर्णांक __init idle_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	अगर (!म_भेद(str, "poll")) अणु
		pr_info("using polling idle threads\n");
		boot_option_idle_override = IDLE_POLL;
		cpu_idle_poll_ctrl(true);
	पूर्ण अन्यथा अगर (!म_भेद(str, "halt")) अणु
		/*
		 * When the boot option of idle=halt is added, halt is
		 * क्रमced to be used क्रम CPU idle. In such हाल CPU C2/C3
		 * won't be used again.
		 * To जारी to load the CPU idle driver, करोn't touch
		 * the boot_option_idle_override.
		 */
		x86_idle = शेष_idle;
		boot_option_idle_override = IDLE_HALT;
	पूर्ण अन्यथा अगर (!म_भेद(str, "nomwait")) अणु
		/*
		 * If the boot option of "idle=nomwait" is added,
		 * it means that mरुको will be disabled क्रम CPU C2/C3
		 * states. In such हाल it won't touch the variable
		 * of boot_option_idle_override.
		 */
		boot_option_idle_override = IDLE_NOMWAIT;
	पूर्ण अन्यथा
		वापस -1;

	वापस 0;
पूर्ण
early_param("idle", idle_setup);

अचिन्हित दीर्घ arch_align_stack(अचिन्हित दीर्घ sp)
अणु
	अगर (!(current->personality & ADDR_NO_RANDOMIZE) && अक्रमomize_va_space)
		sp -= get_अक्रमom_पूर्णांक() % 8192;
	वापस sp & ~0xf;
पूर्ण

अचिन्हित दीर्घ arch_अक्रमomize_brk(काष्ठा mm_काष्ठा *mm)
अणु
	वापस अक्रमomize_page(mm->brk, 0x02000000);
पूर्ण

/*
 * Called from fs/proc with a reference on @p to find the function
 * which called पूर्णांकo schedule(). This needs to be करोne carefully
 * because the task might wake up and we might look at a stack
 * changing under us.
 */
अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ start, bottom, top, sp, fp, ip, ret = 0;
	पूर्णांक count = 0;

	अगर (p == current || p->state == TASK_RUNNING)
		वापस 0;

	अगर (!try_get_task_stack(p))
		वापस 0;

	start = (अचिन्हित दीर्घ)task_stack_page(p);
	अगर (!start)
		जाओ out;

	/*
	 * Layout of the stack page:
	 *
	 * ----------- topmax = start + THREAD_SIZE - माप(अचिन्हित दीर्घ)
	 * PADDING
	 * ----------- top = topmax - TOP_OF_KERNEL_STACK_PADDING
	 * stack
	 * ----------- bottom = start
	 *
	 * The tasks stack poपूर्णांकer poपूर्णांकs at the location where the
	 * framepoपूर्णांकer is stored. The data on the stack is:
	 * ... IP FP ... IP FP
	 *
	 * We need to पढ़ो FP and IP, so we need to adjust the upper
	 * bound by another अचिन्हित दीर्घ.
	 */
	top = start + THREAD_SIZE - TOP_OF_KERNEL_STACK_PADDING;
	top -= 2 * माप(अचिन्हित दीर्घ);
	bottom = start;

	sp = READ_ONCE(p->thपढ़ो.sp);
	अगर (sp < bottom || sp > top)
		जाओ out;

	fp = READ_ONCE_NOCHECK(((काष्ठा inactive_task_frame *)sp)->bp);
	करो अणु
		अगर (fp < bottom || fp > top)
			जाओ out;
		ip = READ_ONCE_NOCHECK(*(अचिन्हित दीर्घ *)(fp + माप(अचिन्हित दीर्घ)));
		अगर (!in_sched_functions(ip)) अणु
			ret = ip;
			जाओ out;
		पूर्ण
		fp = READ_ONCE_NOCHECK(*(अचिन्हित दीर्घ *)fp);
	पूर्ण जबतक (count++ < 16 && p->state != TASK_RUNNING);

out:
	put_task_stack(p);
	वापस ret;
पूर्ण

दीर्घ करो_arch_prctl_common(काष्ठा task_काष्ठा *task, पूर्णांक option,
			  अचिन्हित दीर्घ cpuid_enabled)
अणु
	चयन (option) अणु
	हाल ARCH_GET_CPUID:
		वापस get_cpuid_mode();
	हाल ARCH_SET_CPUID:
		वापस set_cpuid_mode(task, cpuid_enabled);
	पूर्ण

	वापस -EINVAL;
पूर्ण
