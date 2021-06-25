<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/ptrace.h
 *
 *  Copyright (C) 1996-2003 Russell King
 */
#अगर_अघोषित __ASM_ARM_PTRACE_H
#घोषणा __ASM_ARM_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

काष्ठा pt_regs अणु
	अचिन्हित दीर्घ uregs[18];
पूर्ण;

काष्ठा svc_pt_regs अणु
	काष्ठा pt_regs regs;
	u32 dacr;
	u32 addr_limit;
पूर्ण;

#घोषणा to_svc_pt_regs(r) container_of(r, काष्ठा svc_pt_regs, regs)

#घोषणा user_mode(regs)	\
	(((regs)->ARM_cpsr & 0xf) == 0)

#अगर_घोषित CONFIG_ARM_THUMB
#घोषणा thumb_mode(regs) \
	(((regs)->ARM_cpsr & PSR_T_BIT))
#अन्यथा
#घोषणा thumb_mode(regs) (0)
#पूर्ण_अगर

#अगर_अघोषित CONFIG_CPU_V7M
#घोषणा isa_mode(regs) \
	((((regs)->ARM_cpsr & PSR_J_BIT) >> (__ffs(PSR_J_BIT) - 1)) | \
	 (((regs)->ARM_cpsr & PSR_T_BIT) >> (__ffs(PSR_T_BIT))))
#अन्यथा
#घोषणा isa_mode(regs) 1 /* Thumb */
#पूर्ण_अगर

#घोषणा processor_mode(regs) \
	((regs)->ARM_cpsr & MODE_MASK)

#घोषणा पूर्णांकerrupts_enabled(regs) \
	(!((regs)->ARM_cpsr & PSR_I_BIT))

#घोषणा fast_पूर्णांकerrupts_enabled(regs) \
	(!((regs)->ARM_cpsr & PSR_F_BIT))

/* Are the current रेजिस्टरs suitable क्रम user mode?
 * (used to मुख्यtain security in संकेत handlers)
 */
अटल अंतरभूत पूर्णांक valid_user_regs(काष्ठा pt_regs *regs)
अणु
#अगर_अघोषित CONFIG_CPU_V7M
	अचिन्हित दीर्घ mode = regs->ARM_cpsr & MODE_MASK;

	/*
	 * Always clear the F (FIQ) and A (delayed पात) bits
	 */
	regs->ARM_cpsr &= ~(PSR_F_BIT | PSR_A_BIT);

	अगर ((regs->ARM_cpsr & PSR_I_BIT) == 0) अणु
		अगर (mode == USR_MODE)
			वापस 1;
		अगर (elf_hwcap & HWCAP_26BIT && mode == USR26_MODE)
			वापस 1;
	पूर्ण

	/*
	 * Force CPSR to something logical...
	 */
	regs->ARM_cpsr &= PSR_f | PSR_s | PSR_x | PSR_T_BIT | MODE32_BIT;
	अगर (!(elf_hwcap & HWCAP_26BIT))
		regs->ARM_cpsr |= USR_MODE;

	वापस 0;
#अन्यथा /* अगरndef CONFIG_CPU_V7M */
	वापस 1;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->ARM_r0;
पूर्ण

#घोषणा inकाष्ठाion_poपूर्णांकer(regs)	(regs)->ARM_pc

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा frame_poपूर्णांकer(regs) (regs)->ARM_r7
#अन्यथा
#घोषणा frame_poपूर्णांकer(regs) (regs)->ARM_fp
#पूर्ण_अगर

अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ val)
अणु
	inकाष्ठाion_poपूर्णांकer(regs) = val;
पूर्ण

#अगर_घोषित CONFIG_SMP
बाह्य अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs);
#अन्यथा
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
#पूर्ण_अगर

#घोषणा predicate(x)		((x) & 0xf0000000)
#घोषणा PREDICATE_ALWAYS	0xe0000000

/*
 * True अगर instr is a 32-bit thumb inकाष्ठाion. This works अगर instr
 * is the first or only half-word of a thumb inकाष्ठाion. It also works
 * when instr holds all 32-bits of a wide thumb inकाष्ठाion अगर stored
 * in the क्रमm (first_half<<16)|(second_half)
 */
#घोषणा is_wide_inकाष्ठाion(instr)	((अचिन्हित)(instr) >= 0xe800)

/*
 * kprobe-based event tracer support
 */
#समावेश <linux/compiler.h>
#घोषणा MAX_REG_OFFSET (दुरत्व(काष्ठा pt_regs, ARM_ORIG_r0))

बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset);
बाह्य bool regs_within_kernel_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr);
बाह्य अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
					       अचिन्हित पूर्णांक n);

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

/* Valid only क्रम Kernel mode traps. */
अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->ARM_sp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->ARM_sp;
पूर्ण

#घोषणा current_pt_regs(व्योम) (अणु (काष्ठा pt_regs *)			\
		((current_stack_poपूर्णांकer | (THREAD_SIZE - 1)) - 7) - 1;	\
पूर्ण)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
