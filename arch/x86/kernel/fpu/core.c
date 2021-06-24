<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1994 Linus Torvalds
 *
 *  Pentium III FXSR, SSE support
 *  General FPU state handling cleanups
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 */
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/fpu/regset.h>
#समावेश <यंत्र/fpu/संकेत.स>
#समावेश <यंत्र/fpu/types.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/irq_regs.h>

#समावेश <linux/hardirq.h>
#समावेश <linux/pkeys.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/trace/fpu.h>

/*
 * Represents the initial FPU state. It's mostly (but not completely) zeroes,
 * depending on the FPU hardware क्रमmat:
 */
जोड़ fpregs_state init_fpstate __पढ़ो_mostly;

/*
 * Track whether the kernel is using the FPU state
 * currently.
 *
 * This flag is used:
 *
 *   - by IRQ context code to potentially use the FPU
 *     अगर it's unused.
 *
 *   - to debug kernel_fpu_begin()/end() correctness
 */
अटल DEFINE_PER_CPU(bool, in_kernel_fpu);

/*
 * Track which context is using the FPU on the CPU:
 */
DEFINE_PER_CPU(काष्ठा fpu *, fpu_fpregs_owner_ctx);

अटल bool kernel_fpu_disabled(व्योम)
अणु
	वापस this_cpu_पढ़ो(in_kernel_fpu);
पूर्ण

अटल bool पूर्णांकerrupted_kernel_fpu_idle(व्योम)
अणु
	वापस !kernel_fpu_disabled();
पूर्ण

/*
 * Were we in user mode (or vm86 mode) when we were
 * पूर्णांकerrupted?
 *
 * Doing kernel_fpu_begin/end() is ok अगर we are running
 * in an पूर्णांकerrupt context from user mode - we'll just
 * save the FPU state as required.
 */
अटल bool पूर्णांकerrupted_user_mode(व्योम)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();
	वापस regs && user_mode(regs);
पूर्ण

/*
 * Can we use the FPU in kernel mode with the
 * whole "kernel_fpu_begin/end()" sequence?
 *
 * It's always ok in process context (ie "not interrupt")
 * but it is someबार ok even from an irq.
 */
bool irq_fpu_usable(व्योम)
अणु
	वापस !in_पूर्णांकerrupt() ||
		पूर्णांकerrupted_user_mode() ||
		पूर्णांकerrupted_kernel_fpu_idle();
पूर्ण
EXPORT_SYMBOL(irq_fpu_usable);

/*
 * These must be called with preempt disabled. Returns
 * 'true' अगर the FPU state is still पूर्णांकact and we can
 * keep रेजिस्टरs active.
 *
 * The legacy FNSAVE inकाष्ठाion cleared all FPU state
 * unconditionally, so रेजिस्टरs are essentially destroyed.
 * Modern FPU state can be kept in रेजिस्टरs, अगर there are
 * no pending FP exceptions.
 */
पूर्णांक copy_fpregs_to_fpstate(काष्ठा fpu *fpu)
अणु
	अगर (likely(use_xsave())) अणु
		copy_xregs_to_kernel(&fpu->state.xsave);

		/*
		 * AVX512 state is tracked here because its use is
		 * known to slow the max घड़ी speed of the core.
		 */
		अगर (fpu->state.xsave.header.xfeatures & XFEATURE_MASK_AVX512)
			fpu->avx512_बारtamp = jअगरfies;
		वापस 1;
	पूर्ण

	अगर (likely(use_fxsr())) अणु
		copy_fxregs_to_kernel(fpu);
		वापस 1;
	पूर्ण

	/*
	 * Legacy FPU रेजिस्टर saving, FNSAVE always clears FPU रेजिस्टरs,
	 * so we have to mark them inactive:
	 */
	यंत्र अस्थिर("fnsave %[fp]; fwait" : [fp] "=m" (fpu->state.fsave));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(copy_fpregs_to_fpstate);

व्योम kernel_fpu_begin_mask(अचिन्हित पूर्णांक kfpu_mask)
अणु
	preempt_disable();

	WARN_ON_FPU(!irq_fpu_usable());
	WARN_ON_FPU(this_cpu_पढ़ो(in_kernel_fpu));

	this_cpu_ग_लिखो(in_kernel_fpu, true);

	अगर (!(current->flags & PF_KTHREAD) &&
	    !test_thपढ़ो_flag(TIF_NEED_FPU_LOAD)) अणु
		set_thपढ़ो_flag(TIF_NEED_FPU_LOAD);
		/*
		 * Ignore वापस value -- we करोn't care अगर reg state
		 * is clobbered.
		 */
		copy_fpregs_to_fpstate(&current->thपढ़ो.fpu);
	पूर्ण
	__cpu_invalidate_fpregs_state();

	/* Put sane initial values पूर्णांकo the control रेजिस्टरs. */
	अगर (likely(kfpu_mask & KFPU_MXCSR) && boot_cpu_has(X86_FEATURE_XMM))
		ldmxcsr(MXCSR_DEFAULT);

	अगर (unlikely(kfpu_mask & KFPU_387) && boot_cpu_has(X86_FEATURE_FPU))
		यंत्र अस्थिर ("fninit");
पूर्ण
EXPORT_SYMBOL_GPL(kernel_fpu_begin_mask);

व्योम kernel_fpu_end(व्योम)
अणु
	WARN_ON_FPU(!this_cpu_पढ़ो(in_kernel_fpu));

	this_cpu_ग_लिखो(in_kernel_fpu, false);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(kernel_fpu_end);

/*
 * Save the FPU state (mark it क्रम reload अगर necessary):
 *
 * This only ever माला_लो called क्रम the current task.
 */
व्योम fpu__save(काष्ठा fpu *fpu)
अणु
	WARN_ON_FPU(fpu != &current->thपढ़ो.fpu);

	fpregs_lock();
	trace_x86_fpu_beक्रमe_save(fpu);

	अगर (!test_thपढ़ो_flag(TIF_NEED_FPU_LOAD)) अणु
		अगर (!copy_fpregs_to_fpstate(fpu)) अणु
			copy_kernel_to_fpregs(&fpu->state);
		पूर्ण
	पूर्ण

	trace_x86_fpu_after_save(fpu);
	fpregs_unlock();
पूर्ण

/*
 * Legacy x87 fpstate state init:
 */
अटल अंतरभूत व्योम fpstate_init_ख_स्थितिe(काष्ठा fregs_state *fp)
अणु
	fp->cwd = 0xffff037fu;
	fp->swd = 0xffff0000u;
	fp->twd = 0xffffffffu;
	fp->fos = 0xffff0000u;
पूर्ण

व्योम fpstate_init(जोड़ fpregs_state *state)
अणु
	अगर (!अटल_cpu_has(X86_FEATURE_FPU)) अणु
		fpstate_init_soft(&state->soft);
		वापस;
	पूर्ण

	स_रखो(state, 0, fpu_kernel_xstate_size);

	अगर (अटल_cpu_has(X86_FEATURE_XSAVES))
		fpstate_init_xstate(&state->xsave);
	अगर (अटल_cpu_has(X86_FEATURE_FXSR))
		fpstate_init_fxstate(&state->fxsave);
	अन्यथा
		fpstate_init_ख_स्थितिe(&state->fsave);
पूर्ण
EXPORT_SYMBOL_GPL(fpstate_init);

पूर्णांक fpu__copy(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	काष्ठा fpu *dst_fpu = &dst->thपढ़ो.fpu;
	काष्ठा fpu *src_fpu = &src->thपढ़ो.fpu;

	dst_fpu->last_cpu = -1;

	अगर (!अटल_cpu_has(X86_FEATURE_FPU))
		वापस 0;

	WARN_ON_FPU(src_fpu != &current->thपढ़ो.fpu);

	/*
	 * Don't let 'init optimized' areas of the XSAVE area
	 * leak पूर्णांकo the child task:
	 */
	स_रखो(&dst_fpu->state.xsave, 0, fpu_kernel_xstate_size);

	/*
	 * If the FPU रेजिस्टरs are not current just स_नकल() the state.
	 * Otherwise save current FPU रेजिस्टरs directly पूर्णांकo the child's FPU
	 * context, without any memory-to-memory copying.
	 *
	 * ( The function 'fails' in the FNSAVE हाल, which destroys
	 *   रेजिस्टर contents so we have to load them back. )
	 */
	fpregs_lock();
	अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		स_नकल(&dst_fpu->state, &src_fpu->state, fpu_kernel_xstate_size);

	अन्यथा अगर (!copy_fpregs_to_fpstate(dst_fpu))
		copy_kernel_to_fpregs(&dst_fpu->state);

	fpregs_unlock();

	set_tsk_thपढ़ो_flag(dst, TIF_NEED_FPU_LOAD);

	trace_x86_fpu_copy_src(src_fpu);
	trace_x86_fpu_copy_dst(dst_fpu);

	वापस 0;
पूर्ण

/*
 * Activate the current task's in-memory FPU context,
 * अगर it has not been used beक्रमe:
 */
अटल व्योम fpu__initialize(काष्ठा fpu *fpu)
अणु
	WARN_ON_FPU(fpu != &current->thपढ़ो.fpu);

	set_thपढ़ो_flag(TIF_NEED_FPU_LOAD);
	fpstate_init(&fpu->state);
	trace_x86_fpu_init_state(fpu);
पूर्ण

/*
 * This function must be called beक्रमe we पढ़ो a task's fpstate.
 *
 * There's two हालs where this माला_लो called:
 *
 * - क्रम the current task (when coredumping), in which हाल we have
 *   to save the latest FPU रेजिस्टरs पूर्णांकo the fpstate,
 *
 * - or it's called क्रम stopped tasks (ptrace), in which हाल the
 *   रेजिस्टरs were alपढ़ोy saved by the context-चयन code when
 *   the task scheduled out.
 *
 * If the task has used the FPU beक्रमe then save it.
 */
व्योम fpu__prepare_पढ़ो(काष्ठा fpu *fpu)
अणु
	अगर (fpu == &current->thपढ़ो.fpu)
		fpu__save(fpu);
पूर्ण

/*
 * This function must be called beक्रमe we ग_लिखो a task's fpstate.
 *
 * Invalidate any cached FPU रेजिस्टरs.
 *
 * After this function call, after रेजिस्टरs in the fpstate are
 * modअगरied and the child task has woken up, the child task will
 * restore the modअगरied FPU state from the modअगरied context. If we
 * didn't clear its cached status here then the cached in-रेजिस्टरs
 * state pending on its क्रमmer CPU could be restored, corrupting
 * the modअगरications.
 */
व्योम fpu__prepare_ग_लिखो(काष्ठा fpu *fpu)
अणु
	/*
	 * Only stopped child tasks can be used to modअगरy the FPU
	 * state in the fpstate buffer:
	 */
	WARN_ON_FPU(fpu == &current->thपढ़ो.fpu);

	/* Invalidate any cached state: */
	__fpu_invalidate_fpregs_state(fpu);
पूर्ण

/*
 * Drops current FPU state: deactivates the fpregs and
 * the fpstate. NOTE: it still leaves previous contents
 * in the fpregs in the eager-FPU हाल.
 *
 * This function can be used in हालs where we know that
 * a state-restore is coming: either an explicit one,
 * or a reschedule.
 */
व्योम fpu__drop(काष्ठा fpu *fpu)
अणु
	preempt_disable();

	अगर (fpu == &current->thपढ़ो.fpu) अणु
		/* Ignore delayed exceptions from user space */
		यंत्र अस्थिर("1: fwait\n"
			     "2:\n"
			     _ASM_EXTABLE(1b, 2b));
		fpregs_deactivate(fpu);
	पूर्ण

	trace_x86_fpu_dropped(fpu);

	preempt_enable();
पूर्ण

/*
 * Clear FPU रेजिस्टरs by setting them up from the init fpstate.
 * Caller must करो fpregs_[un]lock() around it.
 */
अटल अंतरभूत व्योम copy_init_fpstate_to_fpregs(u64 features_mask)
अणु
	अगर (use_xsave())
		copy_kernel_to_xregs(&init_fpstate.xsave, features_mask);
	अन्यथा अगर (अटल_cpu_has(X86_FEATURE_FXSR))
		copy_kernel_to_fxregs(&init_fpstate.fxsave);
	अन्यथा
		copy_kernel_to_fregs(&init_fpstate.fsave);

	अगर (boot_cpu_has(X86_FEATURE_OSPKE))
		copy_init_pkru_to_fpregs();
पूर्ण

/*
 * Clear the FPU state back to init state.
 *
 * Called by sys_execve(), by the संकेत handler code and by various
 * error paths.
 */
अटल व्योम fpu__clear(काष्ठा fpu *fpu, bool user_only)
अणु
	WARN_ON_FPU(fpu != &current->thपढ़ो.fpu);

	अगर (!अटल_cpu_has(X86_FEATURE_FPU)) अणु
		fpu__drop(fpu);
		fpu__initialize(fpu);
		वापस;
	पूर्ण

	fpregs_lock();

	अगर (user_only) अणु
		अगर (!fpregs_state_valid(fpu, smp_processor_id()) &&
		    xfeatures_mask_supervisor())
			copy_kernel_to_xregs(&fpu->state.xsave,
					     xfeatures_mask_supervisor());
		copy_init_fpstate_to_fpregs(xfeatures_mask_user());
	पूर्ण अन्यथा अणु
		copy_init_fpstate_to_fpregs(xfeatures_mask_all);
	पूर्ण

	fpregs_mark_activate();
	fpregs_unlock();
पूर्ण

व्योम fpu__clear_user_states(काष्ठा fpu *fpu)
अणु
	fpu__clear(fpu, true);
पूर्ण

व्योम fpu__clear_all(काष्ठा fpu *fpu)
अणु
	fpu__clear(fpu, false);
पूर्ण

/*
 * Load FPU context beक्रमe वापसing to userspace.
 */
व्योम चयन_fpu_वापस(व्योम)
अणु
	अगर (!अटल_cpu_has(X86_FEATURE_FPU))
		वापस;

	__fpregs_load_activate();
पूर्ण
EXPORT_SYMBOL_GPL(चयन_fpu_वापस);

#अगर_घोषित CONFIG_X86_DEBUG_FPU
/*
 * If current FPU state according to its tracking (loaded FPU context on this
 * CPU) is not valid then we must have TIF_NEED_FPU_LOAD set so the context is
 * loaded on वापस to userland.
 */
व्योम fpregs_निश्चित_state_consistent(व्योम)
अणु
	काष्ठा fpu *fpu = &current->thपढ़ो.fpu;

	अगर (test_thपढ़ो_flag(TIF_NEED_FPU_LOAD))
		वापस;

	WARN_ON_FPU(!fpregs_state_valid(fpu, smp_processor_id()));
पूर्ण
EXPORT_SYMBOL_GPL(fpregs_निश्चित_state_consistent);
#पूर्ण_अगर

व्योम fpregs_mark_activate(व्योम)
अणु
	काष्ठा fpu *fpu = &current->thपढ़ो.fpu;

	fpregs_activate(fpu);
	fpu->last_cpu = smp_processor_id();
	clear_thपढ़ो_flag(TIF_NEED_FPU_LOAD);
पूर्ण
EXPORT_SYMBOL_GPL(fpregs_mark_activate);

/*
 * x87 math exception handling:
 */

पूर्णांक fpu__exception_code(काष्ठा fpu *fpu, पूर्णांक trap_nr)
अणु
	पूर्णांक err;

	अगर (trap_nr == X86_TRAP_MF) अणु
		अचिन्हित लघु cwd, swd;
		/*
		 * (~cwd & swd) will mask out exceptions that are not set to unmasked
		 * status.  0x3f is the exception bits in these regs, 0x200 is the
		 * C1 reg you need in हाल of a stack fault, 0x040 is the stack
		 * fault bit.  We should only be taking one exception at a समय,
		 * so अगर this combination करोesn't produce any single exception,
		 * then we have a bad program that isn't synchronizing its FPU usage
		 * and it will suffer the consequences since we won't be able to
		 * fully reproduce the context of the exception.
		 */
		अगर (boot_cpu_has(X86_FEATURE_FXSR)) अणु
			cwd = fpu->state.fxsave.cwd;
			swd = fpu->state.fxsave.swd;
		पूर्ण अन्यथा अणु
			cwd = (अचिन्हित लघु)fpu->state.fsave.cwd;
			swd = (अचिन्हित लघु)fpu->state.fsave.swd;
		पूर्ण

		err = swd & ~cwd;
	पूर्ण अन्यथा अणु
		/*
		 * The SIMD FPU exceptions are handled a little dअगरferently, as there
		 * is only a single status/control रेजिस्टर.  Thus, to determine which
		 * unmasked exception was caught we must mask the exception mask bits
		 * at 0x1f80, and then use these to mask the exception bits at 0x3f.
		 */
		अचिन्हित लघु mxcsr = MXCSR_DEFAULT;

		अगर (boot_cpu_has(X86_FEATURE_XMM))
			mxcsr = fpu->state.fxsave.mxcsr;

		err = ~(mxcsr >> 7) & mxcsr;
	पूर्ण

	अगर (err & 0x001) अणु	/* Invalid op */
		/*
		 * swd & 0x240 == 0x040: Stack Underflow
		 * swd & 0x240 == 0x240: Stack Overflow
		 * User must clear the SF bit (0x40) अगर set
		 */
		वापस FPE_FLTINV;
	पूर्ण अन्यथा अगर (err & 0x004) अणु /* Divide by Zero */
		वापस FPE_FLTDIV;
	पूर्ण अन्यथा अगर (err & 0x008) अणु /* Overflow */
		वापस FPE_FLTOVF;
	पूर्ण अन्यथा अगर (err & 0x012) अणु /* Denormal, Underflow */
		वापस FPE_FLTUND;
	पूर्ण अन्यथा अगर (err & 0x020) अणु /* Precision */
		वापस FPE_FLTRES;
	पूर्ण

	/*
	 * If we're using IRQ 13, or supposedly even some trap
	 * X86_TRAP_MF implementations, it's possible
	 * we get a spurious trap, which is not an error.
	 */
	वापस 0;
पूर्ण
