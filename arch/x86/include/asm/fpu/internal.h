<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1994 Linus Torvalds
 *
 * Pentium III FXSR, SSE support
 * General FPU state handling cleanups
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 * x86-64 work by Andi Kleen 2002
 */

#अगर_अघोषित _ASM_X86_FPU_INTERNAL_H
#घोषणा _ASM_X86_FPU_INTERNAL_H

#समावेश <linux/compat.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/user.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/fpu/xstate.h>
#समावेश <यंत्र/fpu/xcr.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/trace/fpu.h>

/*
 * High level FPU state handling functions:
 */
बाह्य व्योम fpu__prepare_पढ़ो(काष्ठा fpu *fpu);
बाह्य व्योम fpu__prepare_ग_लिखो(काष्ठा fpu *fpu);
बाह्य व्योम fpu__save(काष्ठा fpu *fpu);
बाह्य पूर्णांक  fpu__restore_sig(व्योम __user *buf, पूर्णांक ia32_frame);
बाह्य व्योम fpu__drop(काष्ठा fpu *fpu);
बाह्य पूर्णांक  fpu__copy(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src);
बाह्य व्योम fpu__clear_user_states(काष्ठा fpu *fpu);
बाह्य व्योम fpu__clear_all(काष्ठा fpu *fpu);
बाह्य पूर्णांक  fpu__exception_code(काष्ठा fpu *fpu, पूर्णांक trap_nr);

/*
 * Boot समय FPU initialization functions:
 */
बाह्य व्योम fpu__init_cpu(व्योम);
बाह्य व्योम fpu__init_प्रणाली_xstate(व्योम);
बाह्य व्योम fpu__init_cpu_xstate(व्योम);
बाह्य व्योम fpu__init_प्रणाली(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम fpu__init_check_bugs(व्योम);
बाह्य व्योम fpu__resume_cpu(व्योम);
बाह्य u64 fpu__get_supported_xfeatures_mask(व्योम);

/*
 * Debugging facility:
 */
#अगर_घोषित CONFIG_X86_DEBUG_FPU
# define WARN_ON_FPU(x) WARN_ON_ONCE(x)
#अन्यथा
# define WARN_ON_FPU(x) (अणु (व्योम)(x); 0; पूर्ण)
#पूर्ण_अगर

/*
 * FPU related CPU feature flag helper routines:
 */
अटल __always_अंतरभूत __pure bool use_xsaveopt(व्योम)
अणु
	वापस अटल_cpu_has(X86_FEATURE_XSAVEOPT);
पूर्ण

अटल __always_अंतरभूत __pure bool use_xsave(व्योम)
अणु
	वापस अटल_cpu_has(X86_FEATURE_XSAVE);
पूर्ण

अटल __always_अंतरभूत __pure bool use_fxsr(व्योम)
अणु
	वापस अटल_cpu_has(X86_FEATURE_FXSR);
पूर्ण

/*
 * fpstate handling functions:
 */

बाह्य जोड़ fpregs_state init_fpstate;

बाह्य व्योम fpstate_init(जोड़ fpregs_state *state);
#अगर_घोषित CONFIG_MATH_EMULATION
बाह्य व्योम fpstate_init_soft(काष्ठा swregs_state *soft);
#अन्यथा
अटल अंतरभूत व्योम fpstate_init_soft(काष्ठा swregs_state *soft) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम fpstate_init_xstate(काष्ठा xregs_state *xsave)
अणु
	/*
	 * XRSTORS requires these bits set in xcomp_bv, or it will
	 * trigger #GP:
	 */
	xsave->header.xcomp_bv = XCOMP_BV_COMPACTED_FORMAT | xfeatures_mask_all;
पूर्ण

अटल अंतरभूत व्योम fpstate_init_fxstate(काष्ठा fxregs_state *fx)
अणु
	fx->cwd = 0x37f;
	fx->mxcsr = MXCSR_DEFAULT;
पूर्ण
बाह्य व्योम fpstate_sanitize_xstate(काष्ठा fpu *fpu);

#घोषणा user_insn(insn, output, input...)				\
(अणु									\
	पूर्णांक err;							\
									\
	might_fault();							\
									\
	यंत्र अस्थिर(ASM_STAC "\n"					\
		     "1:" #insn "\n\t"					\
		     "2: " ASM_CLAC "\n"				\
		     ".section .fixup,\"ax\"\n"				\
		     "3:  movl $-1,%[err]\n"				\
		     "    jmp  2b\n"					\
		     ".previous\n"					\
		     _ASM_EXTABLE(1b, 3b)				\
		     : [err] "=r" (err), output				\
		     : "0"(0), input);					\
	err;								\
पूर्ण)

#घोषणा kernel_insn_err(insn, output, input...)				\
(अणु									\
	पूर्णांक err;							\
	यंत्र अस्थिर("1:" #insn "\n\t"					\
		     "2:\n"						\
		     ".section .fixup,\"ax\"\n"				\
		     "3:  movl $-1,%[err]\n"				\
		     "    jmp  2b\n"					\
		     ".previous\n"					\
		     _ASM_EXTABLE(1b, 3b)				\
		     : [err] "=r" (err), output				\
		     : "0"(0), input);					\
	err;								\
पूर्ण)

#घोषणा kernel_insn(insn, output, input...)				\
	यंत्र अस्थिर("1:" #insn "\n\t"					\
		     "2:\n"						\
		     _ASM_EXTABLE_HANDLE(1b, 2b, ex_handler_fprestore)	\
		     : output : input)

अटल अंतरभूत पूर्णांक copy_fregs_to_user(काष्ठा fregs_state __user *fx)
अणु
	वापस user_insn(fnsave %[fx]; fरुको,  [fx] "=m" (*fx), "m" (*fx));
पूर्ण

अटल अंतरभूत पूर्णांक copy_fxregs_to_user(काष्ठा fxregs_state __user *fx)
अणु
	अगर (IS_ENABLED(CONFIG_X86_32))
		वापस user_insn(fxsave %[fx], [fx] "=m" (*fx), "m" (*fx));
	अन्यथा
		वापस user_insn(fxsaveq %[fx], [fx] "=m" (*fx), "m" (*fx));

पूर्ण

अटल अंतरभूत व्योम copy_kernel_to_fxregs(काष्ठा fxregs_state *fx)
अणु
	अगर (IS_ENABLED(CONFIG_X86_32))
		kernel_insn(fxrstor %[fx], "=m" (*fx), [fx] "m" (*fx));
	अन्यथा
		kernel_insn(fxrstorq %[fx], "=m" (*fx), [fx] "m" (*fx));
पूर्ण

अटल अंतरभूत पूर्णांक copy_kernel_to_fxregs_err(काष्ठा fxregs_state *fx)
अणु
	अगर (IS_ENABLED(CONFIG_X86_32))
		वापस kernel_insn_err(fxrstor %[fx], "=m" (*fx), [fx] "m" (*fx));
	अन्यथा
		वापस kernel_insn_err(fxrstorq %[fx], "=m" (*fx), [fx] "m" (*fx));
पूर्ण

अटल अंतरभूत पूर्णांक copy_user_to_fxregs(काष्ठा fxregs_state __user *fx)
अणु
	अगर (IS_ENABLED(CONFIG_X86_32))
		वापस user_insn(fxrstor %[fx], "=m" (*fx), [fx] "m" (*fx));
	अन्यथा
		वापस user_insn(fxrstorq %[fx], "=m" (*fx), [fx] "m" (*fx));
पूर्ण

अटल अंतरभूत व्योम copy_kernel_to_fregs(काष्ठा fregs_state *fx)
अणु
	kernel_insn(frstor %[fx], "=m" (*fx), [fx] "m" (*fx));
पूर्ण

अटल अंतरभूत पूर्णांक copy_kernel_to_fregs_err(काष्ठा fregs_state *fx)
अणु
	वापस kernel_insn_err(frstor %[fx], "=m" (*fx), [fx] "m" (*fx));
पूर्ण

अटल अंतरभूत पूर्णांक copy_user_to_fregs(काष्ठा fregs_state __user *fx)
अणु
	वापस user_insn(frstor %[fx], "=m" (*fx), [fx] "m" (*fx));
पूर्ण

अटल अंतरभूत व्योम copy_fxregs_to_kernel(काष्ठा fpu *fpu)
अणु
	अगर (IS_ENABLED(CONFIG_X86_32))
		यंत्र अस्थिर( "fxsave %[fx]" : [fx] "=m" (fpu->state.fxsave));
	अन्यथा
		यंत्र अस्थिर("fxsaveq %[fx]" : [fx] "=m" (fpu->state.fxsave));
पूर्ण

/* These macros all use (%edi)/(%rdi) as the single memory argument. */
#घोषणा XSAVE		".byte " REX_PREFIX "0x0f,0xae,0x27"
#घोषणा XSAVEOPT	".byte " REX_PREFIX "0x0f,0xae,0x37"
#घोषणा XSAVES		".byte " REX_PREFIX "0x0f,0xc7,0x2f"
#घोषणा XRSTOR		".byte " REX_PREFIX "0x0f,0xae,0x2f"
#घोषणा XRSTORS		".byte " REX_PREFIX "0x0f,0xc7,0x1f"

#घोषणा XSTATE_OP(op, st, lmask, hmask, err)				\
	यंत्र अस्थिर("1:" op "\n\t"					\
		     "xor %[err], %[err]\n"				\
		     "2:\n\t"						\
		     ".pushsection .fixup,\"ax\"\n\t"			\
		     "3: movl $-2,%[err]\n\t"				\
		     "jmp 2b\n\t"					\
		     ".popsection\n\t"					\
		     _ASM_EXTABLE(1b, 3b)				\
		     : [err] "=r" (err)					\
		     : "D" (st), "m" (*st), "a" (lmask), "d" (hmask)	\
		     : "memory")

/*
 * If XSAVES is enabled, it replaces XSAVEOPT because it supports a compact
 * क्रमmat and supervisor states in addition to modअगरied optimization in
 * XSAVEOPT.
 *
 * Otherwise, अगर XSAVEOPT is enabled, XSAVEOPT replaces XSAVE because XSAVEOPT
 * supports modअगरied optimization which is not supported by XSAVE.
 *
 * We use XSAVE as a fallback.
 *
 * The 661 label is defined in the ALTERNATIVE* macros as the address of the
 * original inकाष्ठाion which माला_लो replaced. We need to use it here as the
 * address of the inकाष्ठाion where we might get an exception at.
 */
#घोषणा XSTATE_XSAVE(st, lmask, hmask, err)				\
	यंत्र अस्थिर(ALTERNATIVE_2(XSAVE,				\
				   XSAVEOPT, X86_FEATURE_XSAVEOPT,	\
				   XSAVES,   X86_FEATURE_XSAVES)	\
		     "\n"						\
		     "xor %[err], %[err]\n"				\
		     "3:\n"						\
		     ".pushsection .fixup,\"ax\"\n"			\
		     "4: movl $-2, %[err]\n"				\
		     "jmp 3b\n"						\
		     ".popsection\n"					\
		     _ASM_EXTABLE(661b, 4b)				\
		     : [err] "=r" (err)					\
		     : "D" (st), "m" (*st), "a" (lmask), "d" (hmask)	\
		     : "memory")

/*
 * Use XRSTORS to restore context अगर it is enabled. XRSTORS supports compact
 * XSAVE area क्रमmat.
 */
#घोषणा XSTATE_XRESTORE(st, lmask, hmask)				\
	यंत्र अस्थिर(ALTERNATIVE(XRSTOR,				\
				 XRSTORS, X86_FEATURE_XSAVES)		\
		     "\n"						\
		     "3:\n"						\
		     _ASM_EXTABLE_HANDLE(661b, 3b, ex_handler_fprestore)\
		     :							\
		     : "D" (st), "m" (*st), "a" (lmask), "d" (hmask)	\
		     : "memory")

/*
 * This function is called only during boot समय when x86 caps are not set
 * up and alternative can not be used yet.
 */
अटल अंतरभूत व्योम copy_xregs_to_kernel_booting(काष्ठा xregs_state *xstate)
अणु
	u64 mask = xfeatures_mask_all;
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	पूर्णांक err;

	WARN_ON(प्रणाली_state != SYSTEM_BOOTING);

	अगर (boot_cpu_has(X86_FEATURE_XSAVES))
		XSTATE_OP(XSAVES, xstate, lmask, hmask, err);
	अन्यथा
		XSTATE_OP(XSAVE, xstate, lmask, hmask, err);

	/* We should never fault when copying to a kernel buffer: */
	WARN_ON_FPU(err);
पूर्ण

/*
 * This function is called only during boot समय when x86 caps are not set
 * up and alternative can not be used yet.
 */
अटल अंतरभूत व्योम copy_kernel_to_xregs_booting(काष्ठा xregs_state *xstate)
अणु
	u64 mask = -1;
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	पूर्णांक err;

	WARN_ON(प्रणाली_state != SYSTEM_BOOTING);

	अगर (boot_cpu_has(X86_FEATURE_XSAVES))
		XSTATE_OP(XRSTORS, xstate, lmask, hmask, err);
	अन्यथा
		XSTATE_OP(XRSTOR, xstate, lmask, hmask, err);

	/*
	 * We should never fault when copying from a kernel buffer, and the FPU
	 * state we set at boot समय should be valid.
	 */
	WARN_ON_FPU(err);
पूर्ण

/*
 * Save processor xstate to xsave area.
 */
अटल अंतरभूत व्योम copy_xregs_to_kernel(काष्ठा xregs_state *xstate)
अणु
	u64 mask = xfeatures_mask_all;
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	पूर्णांक err;

	WARN_ON_FPU(!alternatives_patched);

	XSTATE_XSAVE(xstate, lmask, hmask, err);

	/* We should never fault when copying to a kernel buffer: */
	WARN_ON_FPU(err);
पूर्ण

/*
 * Restore processor xstate from xsave area.
 */
अटल अंतरभूत व्योम copy_kernel_to_xregs(काष्ठा xregs_state *xstate, u64 mask)
अणु
	u32 lmask = mask;
	u32 hmask = mask >> 32;

	XSTATE_XRESTORE(xstate, lmask, hmask);
पूर्ण

/*
 * Save xstate to user space xsave area.
 *
 * We करोn't use modअगरied optimization because xrstor/xrstors might track
 * a dअगरferent application.
 *
 * We करोn't use compacted क्रमmat xsave area क्रम
 * backward compatibility क्रम old applications which करोn't understand
 * compacted क्रमmat of xsave area.
 */
अटल अंतरभूत पूर्णांक copy_xregs_to_user(काष्ठा xregs_state __user *buf)
अणु
	u64 mask = xfeatures_mask_user();
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	पूर्णांक err;

	/*
	 * Clear the xsave header first, so that reserved fields are
	 * initialized to zero.
	 */
	err = __clear_user(&buf->header, माप(buf->header));
	अगर (unlikely(err))
		वापस -EFAULT;

	stac();
	XSTATE_OP(XSAVE, buf, lmask, hmask, err);
	clac();

	वापस err;
पूर्ण

/*
 * Restore xstate from user space xsave area.
 */
अटल अंतरभूत पूर्णांक copy_user_to_xregs(काष्ठा xregs_state __user *buf, u64 mask)
अणु
	काष्ठा xregs_state *xstate = ((__क्रमce काष्ठा xregs_state *)buf);
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	पूर्णांक err;

	stac();
	XSTATE_OP(XRSTOR, xstate, lmask, hmask, err);
	clac();

	वापस err;
पूर्ण

/*
 * Restore xstate from kernel space xsave area, वापस an error code instead of
 * an exception.
 */
अटल अंतरभूत पूर्णांक copy_kernel_to_xregs_err(काष्ठा xregs_state *xstate, u64 mask)
अणु
	u32 lmask = mask;
	u32 hmask = mask >> 32;
	पूर्णांक err;

	अगर (अटल_cpu_has(X86_FEATURE_XSAVES))
		XSTATE_OP(XRSTORS, xstate, lmask, hmask, err);
	अन्यथा
		XSTATE_OP(XRSTOR, xstate, lmask, hmask, err);

	वापस err;
पूर्ण

बाह्य पूर्णांक copy_fpregs_to_fpstate(काष्ठा fpu *fpu);

अटल अंतरभूत व्योम __copy_kernel_to_fpregs(जोड़ fpregs_state *fpstate, u64 mask)
अणु
	अगर (use_xsave()) अणु
		copy_kernel_to_xregs(&fpstate->xsave, mask);
	पूर्ण अन्यथा अणु
		अगर (use_fxsr())
			copy_kernel_to_fxregs(&fpstate->fxsave);
		अन्यथा
			copy_kernel_to_fregs(&fpstate->fsave);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम copy_kernel_to_fpregs(जोड़ fpregs_state *fpstate)
अणु
	/*
	 * AMD K7/K8 CPUs करोn't save/restore FDP/FIP/FOP unless an exception is
	 * pending. Clear the x87 state here by setting it to fixed values.
	 * "m" is a अक्रमom variable that should be in L1.
	 */
	अगर (unlikely(अटल_cpu_has_bug(X86_BUG_FXSAVE_LEAK))) अणु
		यंत्र अस्थिर(
			"fnclex\n\t"
			"emms\n\t"
			"fildl %P[addr]"	/* set F?P to defined value */
			: : [addr] "m" (fpstate));
	पूर्ण

	__copy_kernel_to_fpregs(fpstate, -1);
पूर्ण

बाह्य पूर्णांक copy_fpstate_to_sigframe(व्योम __user *buf, व्योम __user *fp, पूर्णांक size);

/*
 * FPU context चयन related helper methods:
 */

DECLARE_PER_CPU(काष्ठा fpu *, fpu_fpregs_owner_ctx);

/*
 * The in-रेजिस्टर FPU state क्रम an FPU context on a CPU is assumed to be
 * valid अगर the fpu->last_cpu matches the CPU, and the fpu_fpregs_owner_ctx
 * matches the FPU.
 *
 * If the FPU रेजिस्टर state is valid, the kernel can skip restoring the
 * FPU state from memory.
 *
 * Any code that clobbers the FPU रेजिस्टरs or updates the in-memory
 * FPU state क्रम a task MUST let the rest of the kernel know that the
 * FPU रेजिस्टरs are no दीर्घer valid क्रम this task.
 *
 * Either one of these invalidation functions is enough. Invalidate
 * a resource you control: CPU अगर using the CPU क्रम something अन्यथा
 * (with preemption disabled), FPU क्रम the current task, or a task that
 * is prevented from running by the current task.
 */
अटल अंतरभूत व्योम __cpu_invalidate_fpregs_state(व्योम)
अणु
	__this_cpu_ग_लिखो(fpu_fpregs_owner_ctx, शून्य);
पूर्ण

अटल अंतरभूत व्योम __fpu_invalidate_fpregs_state(काष्ठा fpu *fpu)
अणु
	fpu->last_cpu = -1;
पूर्ण

अटल अंतरभूत पूर्णांक fpregs_state_valid(काष्ठा fpu *fpu, अचिन्हित पूर्णांक cpu)
अणु
	वापस fpu == this_cpu_पढ़ो(fpu_fpregs_owner_ctx) && cpu == fpu->last_cpu;
पूर्ण

/*
 * These generally need preemption protection to work,
 * करो try to aव्योम using these on their own:
 */
अटल अंतरभूत व्योम fpregs_deactivate(काष्ठा fpu *fpu)
अणु
	this_cpu_ग_लिखो(fpu_fpregs_owner_ctx, शून्य);
	trace_x86_fpu_regs_deactivated(fpu);
पूर्ण

अटल अंतरभूत व्योम fpregs_activate(काष्ठा fpu *fpu)
अणु
	this_cpu_ग_लिखो(fpu_fpregs_owner_ctx, fpu);
	trace_x86_fpu_regs_activated(fpu);
पूर्ण

/*
 * Internal helper, करो not use directly. Use चयन_fpu_वापस() instead.
 */
अटल अंतरभूत व्योम __fpregs_load_activate(व्योम)
अणु
	काष्ठा fpu *fpu = &current->thपढ़ो.fpu;
	पूर्णांक cpu = smp_processor_id();

	अगर (WARN_ON_ONCE(current->flags & PF_KTHREAD))
		वापस;

	अगर (!fpregs_state_valid(fpu, cpu)) अणु
		copy_kernel_to_fpregs(&fpu->state);
		fpregs_activate(fpu);
		fpu->last_cpu = cpu;
	पूर्ण
	clear_thपढ़ो_flag(TIF_NEED_FPU_LOAD);
पूर्ण

/*
 * FPU state चयनing क्रम scheduling.
 *
 * This is a two-stage process:
 *
 *  - चयन_fpu_prepare() saves the old state.
 *    This is करोne within the context of the old process.
 *
 *  - चयन_fpu_finish() sets TIF_NEED_FPU_LOAD; the भग्नing poपूर्णांक state
 *    will get loaded on वापस to userspace, or when the kernel needs it.
 *
 * If TIF_NEED_FPU_LOAD is cleared then the CPU's FPU रेजिस्टरs
 * are saved in the current thपढ़ो's FPU रेजिस्टर state.
 *
 * If TIF_NEED_FPU_LOAD is set then CPU's FPU रेजिस्टरs may not
 * hold current()'s FPU रेजिस्टरs. It is required to load the
 * रेजिस्टरs beक्रमe वापसing to userland or using the content
 * otherwise.
 *
 * The FPU context is only stored/restored क्रम a user task and
 * PF_KTHREAD is used to distinguish between kernel and user thपढ़ोs.
 */
अटल अंतरभूत व्योम चयन_fpu_prepare(काष्ठा fpu *old_fpu, पूर्णांक cpu)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_FPU) && !(current->flags & PF_KTHREAD)) अणु
		अगर (!copy_fpregs_to_fpstate(old_fpu))
			old_fpu->last_cpu = -1;
		अन्यथा
			old_fpu->last_cpu = cpu;

		/* But leave fpu_fpregs_owner_ctx! */
		trace_x86_fpu_regs_deactivated(old_fpu);
	पूर्ण
पूर्ण

/*
 * Misc helper functions:
 */

/*
 * Load PKRU from the FPU context अगर available. Delay loading of the
 * complete FPU state until the वापस to userland.
 */
अटल अंतरभूत व्योम चयन_fpu_finish(काष्ठा fpu *new_fpu)
अणु
	u32 pkru_val = init_pkru_value;
	काष्ठा pkru_state *pk;

	अगर (!अटल_cpu_has(X86_FEATURE_FPU))
		वापस;

	set_thपढ़ो_flag(TIF_NEED_FPU_LOAD);

	अगर (!cpu_feature_enabled(X86_FEATURE_OSPKE))
		वापस;

	/*
	 * PKRU state is चयनed eagerly because it needs to be valid beक्रमe we
	 * वापस to userland e.g. क्रम a copy_to_user() operation.
	 */
	अगर (!(current->flags & PF_KTHREAD)) अणु
		/*
		 * If the PKRU bit in xsave.header.xfeatures is not set,
		 * then the PKRU component was in init state, which means
		 * XRSTOR will set PKRU to 0. If the bit is not set then
		 * get_xsave_addr() will वापस शून्य because the PKRU value
		 * in memory is not valid. This means pkru_val has to be
		 * set to 0 and not to init_pkru_value.
		 */
		pk = get_xsave_addr(&new_fpu->state.xsave, XFEATURE_PKRU);
		pkru_val = pk ? pk->pkru : 0;
	पूर्ण
	__ग_लिखो_pkru(pkru_val);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_FPU_INTERNAL_H */
