<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/ptrace.h
 *
 * Copyright (C) 1996-2003 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_PTRACE_H
#घोषणा __ASM_PTRACE_H

#समावेश <यंत्र/cpufeature.h>

#समावेश <uapi/यंत्र/ptrace.h>

/* Current Exception Level values, as contained in CurrentEL */
#घोषणा CurrentEL_EL1		(1 << 2)
#घोषणा CurrentEL_EL2		(2 << 2)

#घोषणा INIT_PSTATE_EL1 \
	(PSR_D_BIT | PSR_A_BIT | PSR_I_BIT | PSR_F_BIT | PSR_MODE_EL1h)
#घोषणा INIT_PSTATE_EL2 \
	(PSR_D_BIT | PSR_A_BIT | PSR_I_BIT | PSR_F_BIT | PSR_MODE_EL2h)

/*
 * PMR values used to mask/unmask पूर्णांकerrupts.
 *
 * GIC priority masking works as follows: अगर an IRQ's priority is a higher value
 * than the value held in PMR, that IRQ is masked. Lowering the value of PMR
 * means masking more IRQs (or at least that the same IRQs reमुख्य masked).
 *
 * To mask पूर्णांकerrupts, we clear the most signअगरicant bit of PMR.
 *
 * Some code sections either स्वतःmatically चयन back to PSR.I or explicitly
 * require to not use priority masking. If bit GIC_PRIO_PSR_I_SET is included
 * in the priority mask, it indicates that PSR.I should be set and
 * पूर्णांकerrupt disabling temporarily करोes not rely on IRQ priorities.
 */
#घोषणा GIC_PRIO_IRQON			0xe0
#घोषणा __GIC_PRIO_IRQOFF		(GIC_PRIO_IRQON & ~0x80)
#घोषणा __GIC_PRIO_IRQOFF_NS		0xa0
#घोषणा GIC_PRIO_PSR_I_SET		(1 << 4)

#घोषणा GIC_PRIO_IRQOFF							\
	(अणु								\
		बाह्य काष्ठा अटल_key_false gic_nonsecure_priorities;\
		u8 __prio = __GIC_PRIO_IRQOFF;				\
									\
		अगर (अटल_branch_unlikely(&gic_nonsecure_priorities))	\
			__prio = __GIC_PRIO_IRQOFF_NS;			\
									\
		__prio;							\
	पूर्ण)

/* Additional SPSR bits not exposed in the UABI */
#घोषणा PSR_MODE_THREAD_BIT	(1 << 0)
#घोषणा PSR_IL_BIT		(1 << 20)

/* AArch32-specअगरic ptrace requests */
#घोषणा COMPAT_PTRACE_GETREGS		12
#घोषणा COMPAT_PTRACE_SETREGS		13
#घोषणा COMPAT_PTRACE_GET_THREAD_AREA	22
#घोषणा COMPAT_PTRACE_SET_SYSCALL	23
#घोषणा COMPAT_PTRACE_GETVFPREGS	27
#घोषणा COMPAT_PTRACE_SETVFPREGS	28
#घोषणा COMPAT_PTRACE_GETHBPREGS	29
#घोषणा COMPAT_PTRACE_SETHBPREGS	30

/* SPSR_ELx bits क्रम exceptions taken from AArch32 */
#घोषणा PSR_AA32_MODE_MASK	0x0000001f
#घोषणा PSR_AA32_MODE_USR	0x00000010
#घोषणा PSR_AA32_MODE_FIQ	0x00000011
#घोषणा PSR_AA32_MODE_IRQ	0x00000012
#घोषणा PSR_AA32_MODE_SVC	0x00000013
#घोषणा PSR_AA32_MODE_ABT	0x00000017
#घोषणा PSR_AA32_MODE_HYP	0x0000001a
#घोषणा PSR_AA32_MODE_UND	0x0000001b
#घोषणा PSR_AA32_MODE_SYS	0x0000001f
#घोषणा PSR_AA32_T_BIT		0x00000020
#घोषणा PSR_AA32_F_BIT		0x00000040
#घोषणा PSR_AA32_I_BIT		0x00000080
#घोषणा PSR_AA32_A_BIT		0x00000100
#घोषणा PSR_AA32_E_BIT		0x00000200
#घोषणा PSR_AA32_PAN_BIT	0x00400000
#घोषणा PSR_AA32_SSBS_BIT	0x00800000
#घोषणा PSR_AA32_DIT_BIT	0x01000000
#घोषणा PSR_AA32_Q_BIT		0x08000000
#घोषणा PSR_AA32_V_BIT		0x10000000
#घोषणा PSR_AA32_C_BIT		0x20000000
#घोषणा PSR_AA32_Z_BIT		0x40000000
#घोषणा PSR_AA32_N_BIT		0x80000000
#घोषणा PSR_AA32_IT_MASK	0x0600fc00	/* If-Then execution state mask */
#घोषणा PSR_AA32_GE_MASK	0x000f0000

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा PSR_AA32_ENDSTATE	PSR_AA32_E_BIT
#अन्यथा
#घोषणा PSR_AA32_ENDSTATE	0
#पूर्ण_अगर

/* AArch32 CPSR bits, as seen in AArch32 */
#घोषणा COMPAT_PSR_DIT_BIT	0x00200000

/*
 * These are 'magic' values क्रम PTRACE_PEEKUSR that वापस info about where a
 * process is located in memory.
 */
#घोषणा COMPAT_PT_TEXT_ADDR		0x10000
#घोषणा COMPAT_PT_DATA_ADDR		0x10004
#घोषणा COMPAT_PT_TEXT_END_ADDR		0x10008

/*
 * If pt_regs.syscallno == NO_SYSCALL, then the thपढ़ो is not executing
 * a syscall -- i.e., its most recent entry पूर्णांकo the kernel from
 * userspace was not via SVC, or otherwise a tracer cancelled the syscall.
 *
 * This must have the value -1, क्रम ABI compatibility with ptrace etc.
 */
#घोषणा NO_SYSCALL (-1)

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/bug.h>
#समावेश <linux/types.h>

/* माप(काष्ठा user) क्रम AArch32 */
#घोषणा COMPAT_USER_SZ	296

/* Architecturally defined mapping between AArch32 and AArch64 रेजिस्टरs */
#घोषणा compat_usr(x)	regs[(x)]
#घोषणा compat_fp	regs[11]
#घोषणा compat_sp	regs[13]
#घोषणा compat_lr	regs[14]
#घोषणा compat_sp_hyp	regs[15]
#घोषणा compat_lr_irq	regs[16]
#घोषणा compat_sp_irq	regs[17]
#घोषणा compat_lr_svc	regs[18]
#घोषणा compat_sp_svc	regs[19]
#घोषणा compat_lr_abt	regs[20]
#घोषणा compat_sp_abt	regs[21]
#घोषणा compat_lr_und	regs[22]
#घोषणा compat_sp_und	regs[23]
#घोषणा compat_r8_fiq	regs[24]
#घोषणा compat_r9_fiq	regs[25]
#घोषणा compat_r10_fiq	regs[26]
#घोषणा compat_r11_fiq	regs[27]
#घोषणा compat_r12_fiq	regs[28]
#घोषणा compat_sp_fiq	regs[29]
#घोषणा compat_lr_fiq	regs[30]

अटल अंतरभूत अचिन्हित दीर्घ compat_psr_to_pstate(स्थिर अचिन्हित दीर्घ psr)
अणु
	अचिन्हित दीर्घ pstate;

	pstate = psr & ~COMPAT_PSR_DIT_BIT;

	अगर (psr & COMPAT_PSR_DIT_BIT)
		pstate |= PSR_AA32_DIT_BIT;

	वापस pstate;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pstate_to_compat_psr(स्थिर अचिन्हित दीर्घ pstate)
अणु
	अचिन्हित दीर्घ psr;

	psr = pstate & ~PSR_AA32_DIT_BIT;

	अगर (pstate & PSR_AA32_DIT_BIT)
		psr |= COMPAT_PSR_DIT_BIT;

	वापस psr;
पूर्ण

/*
 * This काष्ठा defines the way the रेजिस्टरs are stored on the stack during an
 * exception. Note that माप(काष्ठा pt_regs) has to be a multiple of 16 (क्रम
 * stack alignment). काष्ठा user_pt_regs must क्रमm a prefix of काष्ठा pt_regs.
 */
काष्ठा pt_regs अणु
	जोड़ अणु
		काष्ठा user_pt_regs user_regs;
		काष्ठा अणु
			u64 regs[31];
			u64 sp;
			u64 pc;
			u64 pstate;
		पूर्ण;
	पूर्ण;
	u64 orig_x0;
#अगर_घोषित __AARCH64EB__
	u32 unused2;
	s32 syscallno;
#अन्यथा
	s32 syscallno;
	u32 unused2;
#पूर्ण_अगर
	u64 sdei_ttbr1;
	/* Only valid when ARM64_HAS_IRQ_PRIO_MASKING is enabled. */
	u64 pmr_save;
	u64 stackframe[2];

	/* Only valid क्रम some EL1 exceptions. */
	u64 lockdep_hardirqs;
	u64 निकास_rcu;
पूर्ण;

अटल अंतरभूत bool in_syscall(काष्ठा pt_regs स्थिर *regs)
अणु
	वापस regs->syscallno != NO_SYSCALL;
पूर्ण

अटल अंतरभूत व्योम क्रमget_syscall(काष्ठा pt_regs *regs)
अणु
	regs->syscallno = NO_SYSCALL;
पूर्ण

#घोषणा MAX_REG_OFFSET दुरत्व(काष्ठा pt_regs, pstate)

#घोषणा arch_has_single_step()	(1)

#अगर_घोषित CONFIG_COMPAT
#घोषणा compat_thumb_mode(regs) \
	(((regs)->pstate & PSR_AA32_T_BIT))
#अन्यथा
#घोषणा compat_thumb_mode(regs) (0)
#पूर्ण_अगर

#घोषणा user_mode(regs)	\
	(((regs)->pstate & PSR_MODE_MASK) == PSR_MODE_EL0t)

#घोषणा compat_user_mode(regs)	\
	(((regs)->pstate & (PSR_MODE32_BIT | PSR_MODE_MASK)) == \
	 (PSR_MODE32_BIT | PSR_MODE_EL0t))

#घोषणा processor_mode(regs) \
	((regs)->pstate & PSR_MODE_MASK)

#घोषणा irqs_priority_unmasked(regs)					\
	(प्रणाली_uses_irq_prio_masking() ?				\
		(regs)->pmr_save == GIC_PRIO_IRQON :			\
		true)

#घोषणा पूर्णांकerrupts_enabled(regs)			\
	(!((regs)->pstate & PSR_I_BIT) && irqs_priority_unmasked(regs))

#घोषणा fast_पूर्णांकerrupts_enabled(regs) \
	(!((regs)->pstate & PSR_F_BIT))

अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	अगर (compat_user_mode(regs))
		वापस regs->compat_sp;
	वापस regs->sp;
पूर्ण

बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
					       अचिन्हित पूर्णांक n);

/**
 * regs_get_रेजिस्टर() - get रेजिस्टर value from its offset
 * @regs:	pt_regs from which रेजिस्टर value is gotten
 * @offset:	offset of the रेजिस्टर.
 *
 * regs_get_रेजिस्टर वापसs the value of a रेजिस्टर whose offset from @regs.
 * The @offset is the offset of the रेजिस्टर in काष्ठा pt_regs.
 * If @offset is bigger than MAX_REG_OFFSET, this वापसs 0.
 */
अटल अंतरभूत u64 regs_get_रेजिस्टर(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक offset)
अणु
	u64 val = 0;

	WARN_ON(offset & 7);

	offset >>= 3;
	चयन (offset) अणु
	हाल 0 ... 30:
		val = regs->regs[offset];
		अवरोध;
	हाल दुरत्व(काष्ठा pt_regs, sp) >> 3:
		val = regs->sp;
		अवरोध;
	हाल दुरत्व(काष्ठा pt_regs, pc) >> 3:
		val = regs->pc;
		अवरोध;
	हाल दुरत्व(काष्ठा pt_regs, pstate) >> 3:
		val = regs->pstate;
		अवरोध;
	शेष:
		val = 0;
	पूर्ण

	वापस val;
पूर्ण

/*
 * Read a रेजिस्टर given an architectural रेजिस्टर index r.
 * This handles the common हाल where 31 means XZR, not SP.
 */
अटल अंतरभूत अचिन्हित दीर्घ pt_regs_पढ़ो_reg(स्थिर काष्ठा pt_regs *regs, पूर्णांक r)
अणु
	वापस (r == 31) ? 0 : regs->regs[r];
पूर्ण

/*
 * Write a रेजिस्टर given an architectural रेजिस्टर index r.
 * This handles the common हाल where 31 means XZR, not SP.
 */
अटल अंतरभूत व्योम pt_regs_ग_लिखो_reg(काष्ठा pt_regs *regs, पूर्णांक r,
				     अचिन्हित दीर्घ val)
अणु
	अगर (r != 31)
		regs->regs[r] = val;
पूर्ण

/* Valid only क्रम Kernel mode traps. */
अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->sp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[0];
पूर्ण

अटल अंतरभूत व्योम regs_set_वापस_value(काष्ठा pt_regs *regs, अचिन्हित दीर्घ rc)
अणु
	regs->regs[0] = rc;
पूर्ण

/**
 * regs_get_kernel_argument() - get Nth function argument in kernel
 * @regs:	pt_regs of that context
 * @n:		function argument number (start from 0)
 *
 * regs_get_argument() वापसs @n th argument of the function call.
 *
 * Note that this chooses the most likely रेजिस्टर mapping. In very rare
 * हालs this may not वापस correct data, क्रम example, अगर one of the
 * function parameters is 16 bytes or bigger. In such हालs, we cannot
 * get access the parameter correctly and the रेजिस्टर assignment of
 * subsequent parameters will be shअगरted.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_kernel_argument(काष्ठा pt_regs *regs,
						     अचिन्हित पूर्णांक n)
अणु
#घोषणा NR_REG_ARGUMENTS 8
	अगर (n < NR_REG_ARGUMENTS)
		वापस pt_regs_पढ़ो_reg(regs, n);
	वापस 0;
पूर्ण

/* We must aव्योम circular header include via sched.h */
काष्ठा task_काष्ठा;
पूर्णांक valid_user_regs(काष्ठा user_pt_regs *regs, काष्ठा task_काष्ठा *task);

अटल अंतरभूत अचिन्हित दीर्घ inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->pc;
पूर्ण
अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ val)
अणु
	regs->pc = val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[29];
पूर्ण

#घोषणा procedure_link_poपूर्णांकer(regs)	((regs)->regs[30])

अटल अंतरभूत व्योम procedure_link_poपूर्णांकer_set(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ val)
अणु
	procedure_link_poपूर्णांकer(regs) = val;
पूर्ण

बाह्य अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
