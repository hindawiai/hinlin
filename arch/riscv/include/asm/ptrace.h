<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_PTRACE_H
#घोषणा _ASM_RISCV_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>
#समावेश <यंत्र/csr.h>
#समावेश <linux/compiler.h>

#अगर_अघोषित __ASSEMBLY__

काष्ठा pt_regs अणु
	अचिन्हित दीर्घ epc;
	अचिन्हित दीर्घ ra;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ gp;
	अचिन्हित दीर्घ tp;
	अचिन्हित दीर्घ t0;
	अचिन्हित दीर्घ t1;
	अचिन्हित दीर्घ t2;
	अचिन्हित दीर्घ s0;
	अचिन्हित दीर्घ s1;
	अचिन्हित दीर्घ a0;
	अचिन्हित दीर्घ a1;
	अचिन्हित दीर्घ a2;
	अचिन्हित दीर्घ a3;
	अचिन्हित दीर्घ a4;
	अचिन्हित दीर्घ a5;
	अचिन्हित दीर्घ a6;
	अचिन्हित दीर्घ a7;
	अचिन्हित दीर्घ s2;
	अचिन्हित दीर्घ s3;
	अचिन्हित दीर्घ s4;
	अचिन्हित दीर्घ s5;
	अचिन्हित दीर्घ s6;
	अचिन्हित दीर्घ s7;
	अचिन्हित दीर्घ s8;
	अचिन्हित दीर्घ s9;
	अचिन्हित दीर्घ s10;
	अचिन्हित दीर्घ s11;
	अचिन्हित दीर्घ t3;
	अचिन्हित दीर्घ t4;
	अचिन्हित दीर्घ t5;
	अचिन्हित दीर्घ t6;
	/* Supervisor/Machine CSRs */
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ badaddr;
	अचिन्हित दीर्घ cause;
	/* a0 value beक्रमe the syscall */
	अचिन्हित दीर्घ orig_a0;
पूर्ण;

#अगर_घोषित CONFIG_64BIT
#घोषणा REG_FMT "%016lx"
#अन्यथा
#घोषणा REG_FMT "%08lx"
#पूर्ण_अगर

#घोषणा user_mode(regs) (((regs)->status & SR_PP) == 0)

#घोषणा MAX_REG_OFFSET दुरत्व(काष्ठा pt_regs, orig_a0)

/* Helpers क्रम working with the inकाष्ठाion poपूर्णांकer */
अटल अंतरभूत अचिन्हित दीर्घ inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->epc;
पूर्ण
अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ val)
अणु
	regs->epc = val;
पूर्ण

#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)

/* Helpers क्रम working with the user stack poपूर्णांकer */
अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->sp;
पूर्ण
अटल अंतरभूत व्योम user_stack_poपूर्णांकer_set(काष्ठा pt_regs *regs,
					  अचिन्हित दीर्घ val)
अणु
	regs->sp =  val;
पूर्ण

/* Valid only क्रम Kernel mode traps. */
अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->sp;
पूर्ण

/* Helpers क्रम working with the frame poपूर्णांकer */
अटल अंतरभूत अचिन्हित दीर्घ frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->s0;
पूर्ण
अटल अंतरभूत व्योम frame_poपूर्णांकer_set(काष्ठा pt_regs *regs,
				     अचिन्हित दीर्घ val)
अणु
	regs->s0 = val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->a0;
पूर्ण

अटल अंतरभूत व्योम regs_set_वापस_value(काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ val)
अणु
	regs->a0 = val;
पूर्ण

बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
					       अचिन्हित पूर्णांक n);

व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent, अचिन्हित दीर्घ self_addr,
			   अचिन्हित दीर्घ frame_poपूर्णांकer);
पूर्णांक करो_syscall_trace_enter(काष्ठा pt_regs *regs);
व्योम करो_syscall_trace_निकास(काष्ठा pt_regs *regs);

/**
 * regs_get_रेजिस्टर() - get रेजिस्टर value from its offset
 * @regs:	pt_regs from which रेजिस्टर value is gotten
 * @offset:	offset of the रेजिस्टर.
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
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_RISCV_PTRACE_H */
