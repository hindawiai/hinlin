<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/processor.h
 *
 *  Copyright (C) 1995-1999 Russell King
 */

#अगर_अघोषित __ASM_ARM_PROCESSOR_H
#घोषणा __ASM_ARM_PROCESSOR_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/unअगरied.h>
#समावेश <यंत्र/vdso/processor.h>

#अगर_घोषित __KERNEL__
#घोषणा STACK_TOP	((current->personality & ADDR_LIMIT_32BIT) ? \
			 TASK_SIZE : TASK_SIZE_26)
#घोषणा STACK_TOP_MAX	TASK_SIZE
#पूर्ण_अगर

काष्ठा debug_info अणु
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	काष्ठा perf_event	*hbp[ARM_MAX_HBP_SLOTS];
#पूर्ण_अगर
पूर्ण;

काष्ठा thपढ़ो_काष्ठा अणु
							/* fault info	  */
	अचिन्हित दीर्घ		address;
	अचिन्हित दीर्घ		trap_no;
	अचिन्हित दीर्घ		error_code;
							/* debugging	  */
	काष्ठा debug_info	debug;
पूर्ण;

/*
 * Everything usercopied to/from thपढ़ो_काष्ठा is अटलally-sized, so
 * no hardened usercopy whitelist is needed.
 */
अटल अंतरभूत व्योम arch_thपढ़ो_काष्ठा_whitelist(अचिन्हित दीर्घ *offset,
						अचिन्हित दीर्घ *size)
अणु
	*offset = *size = 0;
पूर्ण

#घोषणा INIT_THREAD  अणु	पूर्ण

#घोषणा start_thपढ़ो(regs,pc,sp)					\
(अणु									\
	अचिन्हित दीर्घ r7, r8, r9;					\
									\
	अगर (IS_ENABLED(CONFIG_BINFMT_ELF_FDPIC)) अणु			\
		r7 = regs->ARM_r7;					\
		r8 = regs->ARM_r8;					\
		r9 = regs->ARM_r9;					\
	पूर्ण								\
	स_रखो(regs->uregs, 0, माप(regs->uregs));			\
	अगर (IS_ENABLED(CONFIG_BINFMT_ELF_FDPIC) &&			\
	    current->personality & FDPIC_FUNCPTRS) अणु			\
		regs->ARM_r7 = r7;					\
		regs->ARM_r8 = r8;					\
		regs->ARM_r9 = r9;					\
		regs->ARM_r10 = current->mm->start_data;		\
	पूर्ण अन्यथा अगर (!IS_ENABLED(CONFIG_MMU))				\
		regs->ARM_r10 = current->mm->start_data;		\
	अगर (current->personality & ADDR_LIMIT_32BIT)			\
		regs->ARM_cpsr = USR_MODE;				\
	अन्यथा								\
		regs->ARM_cpsr = USR26_MODE;				\
	अगर (elf_hwcap & HWCAP_THUMB && pc & 1)				\
		regs->ARM_cpsr |= PSR_T_BIT;				\
	regs->ARM_cpsr |= PSR_ENDSTATE;					\
	regs->ARM_pc = pc & ~1;		/* pc */			\
	regs->ARM_sp = sp;		/* sp */			\
पूर्ण)

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
बाह्य व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा task_pt_regs(p) \
	((काष्ठा pt_regs *)(THREAD_START_SP + task_stack_page(p)) - 1)

#घोषणा KSTK_EIP(tsk)	task_pt_regs(tsk)->ARM_pc
#घोषणा KSTK_ESP(tsk)	task_pt_regs(tsk)->ARM_sp

#अगर_घोषित CONFIG_SMP
#घोषणा __ALT_SMP_ASM(smp, up)						\
	"9998:	" smp "\n"						\
	"	.pushsection \".alt.smp.init\", \"a\"\n"		\
	"	.long	9998b - .\n"					\
	"	" up "\n"						\
	"	.popsection\n"
#अन्यथा
#घोषणा __ALT_SMP_ASM(smp, up)	up
#पूर्ण_अगर

/*
 * Prefetching support - only ARMv5.
 */
#अगर __LINUX_ARM_ARCH__ >= 5

#घोषणा ARCH_HAS_PREFETCH
अटल अंतरभूत व्योम prefetch(स्थिर व्योम *ptr)
अणु
	__यंत्र__ __अस्थिर__(
		"pld\t%a0"
		:: "p" (ptr));
पूर्ण

#अगर __LINUX_ARM_ARCH__ >= 7 && defined(CONFIG_SMP)
#घोषणा ARCH_HAS_PREFETCHW
अटल अंतरभूत व्योम prefetchw(स्थिर व्योम *ptr)
अणु
	__यंत्र__ __अस्थिर__(
		".arch_extension	mp\n"
		__ALT_SMP_ASM(
			"pldw\t%a0",
			"pld\t%a0"
		)
		:: "p" (ptr));
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARM_PROCESSOR_H */
