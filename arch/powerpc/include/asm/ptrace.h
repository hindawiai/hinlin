<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 *
 * This काष्ठा defines the way the रेजिस्टरs are stored on the
 * kernel stack during a प्रणाली call or other kernel entry.
 *
 * this should only contain अस्थिर regs
 * since we can keep non-अस्थिर in the thपढ़ो_काष्ठा
 * should set this up when only अस्थिरs are saved
 * by पूर्णांकr code.
 *
 * Since this is going on the stack, *CARE MUST BE TAKEN* to insure
 * that the overall काष्ठाure is a multiple of 16 bytes in length.
 *
 * Note that the offsets of the fields in this काष्ठा correspond with
 * the PT_* values below.  This simplअगरies arch/घातerpc/kernel/ptrace.c.
 */
#अगर_अघोषित _ASM_POWERPC_PTRACE_H
#घोषणा _ASM_POWERPC_PTRACE_H

#समावेश <linux/err.h>
#समावेश <uapi/यंत्र/ptrace.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>

#अगर_अघोषित __ASSEMBLY__
काष्ठा pt_regs
अणु
	जोड़ अणु
		काष्ठा user_pt_regs user_regs;
		काष्ठा अणु
			अचिन्हित दीर्घ gpr[32];
			अचिन्हित दीर्घ nip;
			अचिन्हित दीर्घ msr;
			अचिन्हित दीर्घ orig_gpr3;
			अचिन्हित दीर्घ ctr;
			अचिन्हित दीर्घ link;
			अचिन्हित दीर्घ xer;
			अचिन्हित दीर्घ ccr;
#अगर_घोषित CONFIG_PPC64
			अचिन्हित दीर्घ softe;
#अन्यथा
			अचिन्हित दीर्घ mq;
#पूर्ण_अगर
			अचिन्हित दीर्घ trap;
			अचिन्हित दीर्घ dar;
			अचिन्हित दीर्घ dsisr;
			अचिन्हित दीर्घ result;
		पूर्ण;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित CONFIG_PPC64
			अचिन्हित दीर्घ ppr;
#पूर्ण_अगर
			जोड़ अणु
#अगर_घोषित CONFIG_PPC_KUAP
				अचिन्हित दीर्घ kuap;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_PKEY
				अचिन्हित दीर्घ amr;
#पूर्ण_अगर
			पूर्ण;
#अगर_घोषित CONFIG_PPC_PKEY
			अचिन्हित दीर्घ iamr;
#पूर्ण_अगर
		पूर्ण;
		अचिन्हित दीर्घ __pad[4];	/* Maपूर्णांकain 16 byte पूर्णांकerrupt stack alignment */
	पूर्ण;
पूर्ण;
#पूर्ण_अगर


#घोषणा STACK_FRAME_WITH_PT_REGS (STACK_FRAME_OVERHEAD + माप(काष्ठा pt_regs))

#अगर_घोषित __घातerpc64__

/*
 * Size of redzone that userspace is allowed to use below the stack
 * poपूर्णांकer.  This is 288 in the 64-bit big-endian ELF ABI, and 512 in
 * the new ELFv2 little-endian ABI, so we allow the larger amount.
 *
 * For kernel code we allow a 288-byte redzone, in order to conserve
 * kernel stack space; gcc currently only uses 288 bytes, and will
 * hopefully allow explicit control of the redzone size in future.
 */
#घोषणा USER_REDZONE_SIZE	512
#घोषणा KERNEL_REDZONE_SIZE	288

#घोषणा STACK_FRAME_OVERHEAD	112	/* size of minimum stack frame */
#घोषणा STACK_FRAME_LR_SAVE	2	/* Location of LR in stack frame */
#घोषणा STACK_FRAME_REGS_MARKER	ASM_CONST(0x7265677368657265)
#घोषणा STACK_INT_FRAME_SIZE	(माप(काष्ठा pt_regs) + \
				 STACK_FRAME_OVERHEAD + KERNEL_REDZONE_SIZE)
#घोषणा STACK_FRAME_MARKER	12

#अगर_घोषित PPC64_ELF_ABI_v2
#घोषणा STACK_FRAME_MIN_SIZE	32
#अन्यथा
#घोषणा STACK_FRAME_MIN_SIZE	STACK_FRAME_OVERHEAD
#पूर्ण_अगर

/* Size of dummy stack frame allocated when calling संकेत handler. */
#घोषणा __SIGNAL_FRAMESIZE	128
#घोषणा __SIGNAL_FRAMESIZE32	64

#अन्यथा /* __घातerpc64__ */

#घोषणा USER_REDZONE_SIZE	0
#घोषणा KERNEL_REDZONE_SIZE	0
#घोषणा STACK_FRAME_OVERHEAD	16	/* size of minimum stack frame */
#घोषणा STACK_FRAME_LR_SAVE	1	/* Location of LR in stack frame */
#घोषणा STACK_FRAME_REGS_MARKER	ASM_CONST(0x72656773)
#घोषणा STACK_INT_FRAME_SIZE	(माप(काष्ठा pt_regs) + STACK_FRAME_OVERHEAD)
#घोषणा STACK_FRAME_MARKER	2
#घोषणा STACK_FRAME_MIN_SIZE	STACK_FRAME_OVERHEAD

/* Size of stack frame allocated when calling संकेत handler. */
#घोषणा __SIGNAL_FRAMESIZE	64

#पूर्ण_अगर /* __घातerpc64__ */

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत अचिन्हित दीर्घ inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->nip;
पूर्ण

अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ val)
अणु
	regs->nip = val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->gpr[1];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
बाह्य अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs);
#अन्यथा
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
#पूर्ण_अगर

दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs);
व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs);

#अगर_घोषित __घातerpc64__
#घोषणा user_mode(regs) ((((regs)->msr) >> MSR_PR_LG) & 0x1)
#अन्यथा
#घोषणा user_mode(regs) (((regs)->msr & MSR_PR) != 0)
#पूर्ण_अगर

#घोषणा क्रमce_successful_syscall_वापस()   \
	करो अणु \
		set_thपढ़ो_flag(TIF_NOERROR); \
	पूर्ण जबतक(0)

#घोषणा current_pt_regs() \
	((काष्ठा pt_regs *)((अचिन्हित दीर्घ)task_stack_page(current) + THREAD_SIZE) - 1)

/*
 * The 4 low bits (0xf) are available as flags to overload the trap word,
 * because पूर्णांकerrupt vectors have minimum alignment of 0x10. TRAP_FLAGS_MASK
 * must cover the bits used as flags, including bit 0 which is used as the
 * "norestart" bit.
 */
#अगर_घोषित __घातerpc64__
#घोषणा TRAP_FLAGS_MASK		0x1
#अन्यथा
/*
 * On 4xx we use bit 1 in the trap word to indicate whether the exception
 * is a critical exception (1 means it is).
 */
#घोषणा TRAP_FLAGS_MASK		0xf
#घोषणा IS_CRITICAL_EXC(regs)	(((regs)->trap & 2) != 0)
#घोषणा IS_MCHECK_EXC(regs)	(((regs)->trap & 4) != 0)
#घोषणा IS_DEBUG_EXC(regs)	(((regs)->trap & 8) != 0)
#पूर्ण_अगर /* __घातerpc64__ */
#घोषणा TRAP(regs)		((regs)->trap & ~TRAP_FLAGS_MASK)

अटल __always_अंतरभूत व्योम set_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ val)
अणु
	regs->trap = (regs->trap & TRAP_FLAGS_MASK) | (val & ~TRAP_FLAGS_MASK);
पूर्ण

अटल अंतरभूत bool trap_is_scv(काष्ठा pt_regs *regs)
अणु
	वापस (IS_ENABLED(CONFIG_PPC_BOOK3S_64) && TRAP(regs) == 0x3000);
पूर्ण

अटल अंतरभूत bool trap_is_unsupported_scv(काष्ठा pt_regs *regs)
अणु
	वापस IS_ENABLED(CONFIG_PPC_BOOK3S_64) && TRAP(regs) == 0x7ff0;
पूर्ण

अटल अंतरभूत bool trap_is_syscall(काष्ठा pt_regs *regs)
अणु
	वापस (trap_is_scv(regs) || TRAP(regs) == 0xc00);
पूर्ण

अटल अंतरभूत bool trap_norestart(काष्ठा pt_regs *regs)
अणु
	वापस regs->trap & 0x1;
पूर्ण

अटल __always_अंतरभूत व्योम set_trap_norestart(काष्ठा pt_regs *regs)
अणु
	regs->trap |= 0x1;
पूर्ण

#घोषणा kernel_stack_poपूर्णांकer(regs) ((regs)->gpr[1])
अटल अंतरभूत पूर्णांक is_syscall_success(काष्ठा pt_regs *regs)
अणु
	अगर (trap_is_scv(regs))
		वापस !IS_ERR_VALUE((अचिन्हित दीर्घ)regs->gpr[3]);
	अन्यथा
		वापस !(regs->ccr & 0x10000000);
पूर्ण

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	अगर (trap_is_scv(regs))
		वापस regs->gpr[3];

	अगर (is_syscall_success(regs))
		वापस regs->gpr[3];
	अन्यथा
		वापस -regs->gpr[3];
पूर्ण

अटल अंतरभूत व्योम regs_set_वापस_value(काष्ठा pt_regs *regs, अचिन्हित दीर्घ rc)
अणु
	regs->gpr[3] = rc;
पूर्ण

#घोषणा arch_has_single_step()	(1)
#घोषणा arch_has_block_step()	(true)
#घोषणा ARCH_HAS_USER_SINGLE_STEP_REPORT

/*
 * kprobe-based event tracer support
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/thपढ़ो_info.h>
बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset);
#घोषणा MAX_REG_OFFSET (दुरत्व(काष्ठा pt_regs, dsisr))

/**
 * regs_get_रेजिस्टर() - get रेजिस्टर value from its offset
 * @regs:	   pt_regs from which रेजिस्टर value is gotten
 * @offset:    offset number of the रेजिस्टर.
 *
 * regs_get_रेजिस्टर वापसs the value of a रेजिस्टर whose offset from @regs.
 * The @offset is the offset of the रेजिस्टर in काष्ठा pt_regs.
 * If @offset is bigger than MAX_REG_OFFSET, this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_रेजिस्टर(काष्ठा pt_regs *regs,
						अचिन्हित पूर्णांक offset)
अणु
	अगर (unlikely(offset > MAX_REG_OFFSET))
		वापस 0;
	वापस *(अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)regs + offset);
पूर्ण

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:      pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:      address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */

अटल अंतरभूत bool regs_within_kernel_stack(काष्ठा pt_regs *regs,
						अचिन्हित दीर्घ addr)
अणु
	वापस ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1)));
पूर्ण

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @n:		stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरied by @regs. If the @n th entry is NOT in the kernel stack,
 * this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
						      अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)kernel_stack_poपूर्णांकer(regs);
	addr += n;
	अगर (regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस *addr;
	अन्यथा
		वापस 0;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_अघोषित __घातerpc64__
/* We need PT_SOFTE defined at all समय to aव्योम #अगर_घोषितs */
#घोषणा PT_SOFTE PT_MQ
#अन्यथा /* __घातerpc64__ */
#घोषणा PT_FPSCR32 (PT_FPR0 + 2*32 + 1)	/* each FP reg occupies 2 32-bit userspace slots */
#घोषणा PT_VR0_32 164	/* each Vector reg occupies 4 slots in 32-bit */
#घोषणा PT_VSCR_32 (PT_VR0 + 32*4 + 3)
#घोषणा PT_VRSAVE_32 (PT_VR0 + 33*4)
#घोषणा PT_VSR0_32 300 	/* each VSR reg occupies 4 slots in 32-bit */
#पूर्ण_अगर /* __घातerpc64__ */
#पूर्ण_अगर /* _ASM_POWERPC_PTRACE_H */
