<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PTRACE_H
#घोषणा __ASM_CSKY_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

#अगर_अघोषित __ASSEMBLY__

#घोषणा PS_S	0x80000000 /* Supervisor Mode */

#घोषणा USR_BKPT	0x1464

#घोषणा arch_has_single_step() (1)
#घोषणा current_pt_regs() \
(अणु (काष्ठा pt_regs *)((अक्षर *)current_thपढ़ो_info() + THREAD_SIZE) - 1; पूर्ण)

#घोषणा user_stack_poपूर्णांकer(regs) ((regs)->usp)

#घोषणा user_mode(regs) (!((regs)->sr & PS_S))
#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->pc)
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)
#घोषणा trap_no(regs) ((regs->sr >> 16) & 0xff)

अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ val)
अणु
	regs->pc = val;
पूर्ण

#अगर defined(__CSKYABIV2__)
#घोषणा MAX_REG_OFFSET दुरत्व(काष्ठा pt_regs, dcsr)
#अन्यथा
#घोषणा MAX_REG_OFFSET दुरत्व(काष्ठा pt_regs, regs[9])
#पूर्ण_अगर

अटल अंतरभूत bool in_syscall(काष्ठा pt_regs स्थिर *regs)
अणु
	वापस ((regs->sr >> 16) & 0xff) == VEC_TRAP0;
पूर्ण

अटल अंतरभूत व्योम क्रमget_syscall(काष्ठा pt_regs *regs)
अणु
	regs->sr &= ~(0xff << 16);
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

/* Valid only क्रम Kernel mode traps. */
अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->usp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[4];
पूर्ण
अटल अंतरभूत व्योम frame_poपूर्णांकer_set(काष्ठा pt_regs *regs,
				     अचिन्हित दीर्घ val)
अणु
	regs->regs[4] = val;
पूर्ण

बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
						अचिन्हित पूर्णांक n);

/*
 * regs_get_रेजिस्टर() - get रेजिस्टर value from its offset
 * @regs:      pt_regs from which रेजिस्टर value is gotten
 * @offset:    offset of the रेजिस्टर.
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
#पूर्ण_अगर /* __ASM_CSKY_PTRACE_H */
