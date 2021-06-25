<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-m68k/processor.h
 *
 * Copyright (C) 1995 Hamish Macकरोnald
 */

#अगर_अघोषित __ASM_M68K_PROCESSOR_H
#घोषणा __ASM_M68K_PROCESSOR_H

#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/ptrace.h>

अटल अंतरभूत अचिन्हित दीर्घ rdusp(व्योम)
अणु
#अगर_घोषित CONFIG_COLDFIRE_SW_A7
	बाह्य अचिन्हित पूर्णांक sw_usp;
	वापस sw_usp;
#अन्यथा
	रेजिस्टर अचिन्हित दीर्घ usp __यंत्र__("a0");
	/* move %usp,%a0 */
	__यंत्र__ __अस्थिर__(".word 0x4e68" : "=a" (usp));
	वापस usp;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम wrusp(अचिन्हित दीर्घ usp)
अणु
#अगर_घोषित CONFIG_COLDFIRE_SW_A7
	बाह्य अचिन्हित पूर्णांक sw_usp;
	sw_usp = usp;
#अन्यथा
	रेजिस्टर अचिन्हित दीर्घ a0 __यंत्र__("a0") = usp;
	/* move %a0,%usp */
	__यंत्र__ __अस्थिर__(".word 0x4e60" : : "a" (a0) );
#पूर्ण_अगर
पूर्ण

/*
 * User space process size: 3.75GB. This is hardcoded पूर्णांकo a few places,
 * so करोn't change it unless you know what you are करोing.
 */
#अगर_घोषित CONFIG_MMU
#अगर defined(CONFIG_COLDFIRE)
#घोषणा TASK_SIZE	(0xC0000000UL)
#या_अगर defined(CONFIG_SUN3)
#घोषणा TASK_SIZE	(0x0E000000UL)
#अन्यथा
#घोषणा TASK_SIZE	(0xF0000000UL)
#पूर्ण_अगर
#अन्यथा
#घोषणा TASK_SIZE	(0xFFFFFFFFUL)
#पूर्ण_अगर

#अगर_घोषित __KERNEL__
#घोषणा STACK_TOP	TASK_SIZE
#घोषणा STACK_TOP_MAX	STACK_TOP
#पूर्ण_अगर

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#अगर_घोषित CONFIG_MMU
#अगर defined(CONFIG_COLDFIRE)
#घोषणा TASK_UNMAPPED_BASE	0x60000000UL
#या_अगर defined(CONFIG_SUN3)
#घोषणा TASK_UNMAPPED_BASE	0x0A000000UL
#अन्यथा
#घोषणा TASK_UNMAPPED_BASE	0xC0000000UL
#पूर्ण_अगर
#घोषणा TASK_UNMAPPED_ALIGN(addr, off)	PAGE_ALIGN(addr)
#अन्यथा
#घोषणा TASK_UNMAPPED_BASE	0
#पूर्ण_अगर

काष्ठा thपढ़ो_काष्ठा अणु
	अचिन्हित दीर्घ  ksp;		/* kernel stack poपूर्णांकer */
	अचिन्हित दीर्घ  usp;		/* user stack poपूर्णांकer */
	अचिन्हित लघु sr;		/* saved status रेजिस्टर */
	अचिन्हित लघु fs;		/* saved fs (sfc, dfc) */
	अचिन्हित दीर्घ  crp[2];		/* cpu root poपूर्णांकer */
	अचिन्हित दीर्घ  esp0;		/* poपूर्णांकs to SR of stack frame */
	अचिन्हित दीर्घ  faddr;		/* info about last fault */
	पूर्णांक            signo, code;
	अचिन्हित दीर्घ  fp[8*3];
	अचिन्हित दीर्घ  fpcntl[3];	/* fp control regs */
	अचिन्हित अक्षर  fpstate[FPSTATESIZE];  /* भग्नing poपूर्णांक state */
पूर्ण;

#घोषणा INIT_THREAD  अणु							\
	.ksp	= माप(init_stack) + (अचिन्हित दीर्घ) init_stack,	\
	.sr	= PS_S,							\
	.fs	= __KERNEL_DS,						\
पूर्ण

/*
 * ColdFire stack क्रमmat sbould be 0x4 क्रम an aligned usp (will always be
 * true on thपढ़ो creation). We need to set this explicitly.
 */
#अगर_घोषित CONFIG_COLDFIRE
#घोषणा setframeक्रमmat(_regs)	करो अणु (_regs)->क्रमmat = 0x4; पूर्ण जबतक(0)
#अन्यथा
#घोषणा setframeक्रमmat(_regs)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Do necessary setup to start up a newly executed thपढ़ो.
 */
अटल अंतरभूत व्योम start_thपढ़ो(काष्ठा pt_regs * regs, अचिन्हित दीर्घ pc,
				अचिन्हित दीर्घ usp)
अणु
	regs->pc = pc;
	regs->sr &= ~0x2000;
	setframeक्रमmat(regs);
	wrusp(usp);
पूर्ण

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा	KSTK_EIP(tsk)	\
    (अणु			\
	अचिन्हित दीर्घ eip = 0;	 \
	अगर ((tsk)->thपढ़ो.esp0 > PAGE_SIZE && \
	    (virt_addr_valid((tsk)->thपढ़ो.esp0))) \
	      eip = ((काष्ठा pt_regs *) (tsk)->thपढ़ो.esp0)->pc; \
	eip; पूर्ण)
#घोषणा	KSTK_ESP(tsk)	((tsk) == current ? rdusp() : (tsk)->thपढ़ो.usp)

#घोषणा task_pt_regs(tsk)	((काष्ठा pt_regs *) ((tsk)->thपढ़ो.esp0))

#घोषणा cpu_relax()	barrier()

#पूर्ण_अगर
