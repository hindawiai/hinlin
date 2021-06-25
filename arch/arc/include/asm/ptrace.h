<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Amit Bhor, Sameer Dhavale: Codito Technologies 2004
 */
#अगर_अघोषित __ASM_ARC_PTRACE_H
#घोषणा __ASM_ARC_PTRACE_H

#समावेश <uapi/यंत्र/ptrace.h>

#अगर_अघोषित __ASSEMBLY__

/* THE pt_regs: Defines how regs are saved during entry पूर्णांकo kernel */

#अगर_घोषित CONFIG_ISA_ARCOMPACT
काष्ठा pt_regs अणु

	/* Real रेजिस्टरs */
	अचिन्हित दीर्घ bta;	/* bta_l1, bta_l2, erbta */

	अचिन्हित दीर्घ lp_start, lp_end, lp_count;

	अचिन्हित दीर्घ status32;	/* status32_l1, status32_l2, erstatus */
	अचिन्हित दीर्घ ret;	/* ilink1, ilink2 or eret */
	अचिन्हित दीर्घ blink;
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ r26;	/* gp */

	अचिन्हित दीर्घ r12, r11, r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0;

	अचिन्हित दीर्घ sp;	/* User/Kernel depending on where we came from */
	अचिन्हित दीर्घ orig_r0;

	/*
	 * To distinguish bet excp, syscall, irq
	 * For traps and exceptions, Exception Cause Register.
	 * 	ECR: <00> <VV> <CC> <PP>
	 * 	Last word used by Linux क्रम extra state mgmt (syscall-restart)
	 * For पूर्णांकerrupts, use artअगरicial ECR values to note current prio-level
	 */
	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
			अचिन्हित दीर्घ state:8, ecr_vec:8,
				      ecr_cause:8, ecr_param:8;
#अन्यथा
			अचिन्हित दीर्घ ecr_param:8, ecr_cause:8,
				      ecr_vec:8, state:8;
#पूर्ण_अगर
		पूर्ण;
		अचिन्हित दीर्घ event;
	पूर्ण;

	अचिन्हित दीर्घ user_r25;
पूर्ण;
#अन्यथा

काष्ठा pt_regs अणु

	अचिन्हित दीर्घ orig_r0;

	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
			अचिन्हित दीर्घ state:8, ecr_vec:8,
				      ecr_cause:8, ecr_param:8;
#अन्यथा
			अचिन्हित दीर्घ ecr_param:8, ecr_cause:8,
				      ecr_vec:8, state:8;
#पूर्ण_अगर
		पूर्ण;
		अचिन्हित दीर्घ event;
	पूर्ण;

	अचिन्हित दीर्घ bta;	/* bta_l1, bta_l2, erbta */

	अचिन्हित दीर्घ user_r25;

	अचिन्हित दीर्घ r26;	/* gp */
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ sp;	/* user/kernel sp depending on where we came from  */

	अचिन्हित दीर्घ r12, r30;

#अगर_घोषित CONFIG_ARC_HAS_ACCL_REGS
	अचिन्हित दीर्घ r58, r59;	/* ACCL/ACCH used by FPU / DSP MPY */
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARC_DSP_SAVE_RESTORE_REGS
	अचिन्हित दीर्घ DSP_CTRL;
#पूर्ण_अगर

	/*------- Below list स्वतः saved by h/w -----------*/
	अचिन्हित दीर्घ r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11;

	अचिन्हित दीर्घ blink;
	अचिन्हित दीर्घ lp_end, lp_start, lp_count;

	अचिन्हित दीर्घ ei, ldi, jli;

	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ status32;
पूर्ण;

#पूर्ण_अगर

/* Callee saved रेजिस्टरs - need to be saved only when you are scheduled out */

काष्ठा callee_regs अणु
	अचिन्हित दीर्घ r25, r24, r23, r22, r21, r20, r19, r18, r17, r16, r15, r14, r13;
पूर्ण;

#घोषणा inकाष्ठाion_poपूर्णांकer(regs)	((regs)->ret)
#घोषणा profile_pc(regs)		inकाष्ठाion_poपूर्णांकer(regs)

/* वापस 1 अगर user mode or 0 अगर kernel mode */
#घोषणा user_mode(regs) (regs->status32 & STATUS_U_MASK)

#घोषणा user_stack_poपूर्णांकer(regs)\
(अणु  अचिन्हित पूर्णांक sp;		\
	अगर (user_mode(regs))	\
		sp = (regs)->sp;\
	अन्यथा			\
		sp = -1;	\
	sp;			\
पूर्ण)

/* वापस 1 अगर PC in delay slot */
#घोषणा delay_mode(regs) ((regs->status32 & STATUS_DE_MASK) == STATUS_DE_MASK)

#घोषणा in_syscall(regs)    ((regs->ecr_vec == ECR_V_TRAP) && !regs->ecr_param)
#घोषणा in_brkpt_trap(regs) ((regs->ecr_vec == ECR_V_TRAP) && regs->ecr_param)

#घोषणा STATE_SCALL_RESTARTED	0x01

#घोषणा syscall_wont_restart(reg) (reg->state |= STATE_SCALL_RESTARTED)
#घोषणा syscall_restartable(reg) !(reg->state &  STATE_SCALL_RESTARTED)

#घोषणा current_pt_regs()					\
(अणु								\
	/* खोलो-coded current_thपढ़ो_info() */			\
	रेजिस्टर अचिन्हित दीर्घ sp यंत्र ("sp");			\
	अचिन्हित दीर्घ pg_start = (sp & ~(THREAD_SIZE - 1));	\
	(काष्ठा pt_regs *)(pg_start + THREAD_SIZE) - 1;	\
पूर्ण)

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस (दीर्घ)regs->r0;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_PTRACE_H */
