<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-h8300/processor.h
 *
 * Copyright (C) 2002 Yoshinori Sato
 *
 * Based on: linux/यंत्र-m68nommu/processor.h
 *
 * Copyright (C) 1995 Hamish Macकरोnald
 */

#अगर_अघोषित __ASM_H8300_PROCESSOR_H
#घोषणा __ASM_H8300_PROCESSOR_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/current.h>

अटल अंतरभूत अचिन्हित दीर्घ rdusp(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक	_sw_usp;

	वापस _sw_usp;
पूर्ण

अटल अंतरभूत व्योम wrusp(अचिन्हित दीर्घ usp)
अणु
	बाह्य अचिन्हित पूर्णांक	_sw_usp;

	_sw_usp = usp;
पूर्ण

/*
 * User space process size: 3.75GB. This is hardcoded पूर्णांकo a few places,
 * so करोn't change it unless you know what you are करोing.
 */
#घोषणा TASK_SIZE	(0xFFFFFFFFUL)

#अगर_घोषित __KERNEL__
#घोषणा STACK_TOP	TASK_SIZE
#घोषणा STACK_TOP_MAX	STACK_TOP
#पूर्ण_अगर

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's. We won't be using it
 */
#घोषणा TASK_UNMAPPED_BASE	0

काष्ठा thपढ़ो_काष्ठा अणु
	अचिन्हित दीर्घ  ksp;		/* kernel stack poपूर्णांकer */
	अचिन्हित दीर्घ  usp;		/* user stack poपूर्णांकer */
	अचिन्हित दीर्घ  ccr;		/* saved status रेजिस्टर */
	अचिन्हित दीर्घ  esp0;            /* poपूर्णांकs to SR of stack frame */
	काष्ठा अणु
		अचिन्हित लघु *addr;
		अचिन्हित लघु inst;
	पूर्ण अवरोधinfo;
पूर्ण;

#घोषणा INIT_THREAD  अणु						\
	.ksp  = माप(init_stack) + (अचिन्हित दीर्घ)init_stack, \
	.usp  = 0,						\
	.ccr  = PS_S,						\
	.esp0 = 0,						\
	.अवरोधinfo = अणु						\
		.addr = (अचिन्हित लघु *)-1,			\
		.inst = 0					\
	पूर्ण							\
पूर्ण

/*
 * Do necessary setup to start up a newly executed thपढ़ो.
 *
 * pass the data segment पूर्णांकo user programs अगर it exists,
 * it can't hurt anything as far as I can tell
 */
#अगर defined(CONFIG_CPU_H8300H)
#घोषणा start_thपढ़ो(_regs, _pc, _usp)				\
करो अणु								\
	(_regs)->pc = (_pc);					\
	(_regs)->ccr = 0x00;	   /* clear all flags */	\
	(_regs)->er5 = current->mm->start_data;	/* GOT base */	\
	(_regs)->sp = ((अचिन्हित दीर्घ)(_usp)) - माप(अचिन्हित दीर्घ) * 3; \
पूर्ण जबतक (0)
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_H8S)
#घोषणा start_thपढ़ो(_regs, _pc, _usp)				\
करो अणु								\
	(_regs)->pc = (_pc);					\
	(_regs)->ccr = 0x00;	   /* clear kernel flag */	\
	(_regs)->exr = 0x78;	   /* enable all पूर्णांकerrupts */	\
	(_regs)->er5 = current->mm->start_data;	/* GOT base */	\
	/* 14 = space क्रम retaddr(4), vector(4), er0(4) and exr(2) on stack */ \
	(_regs)->sp = ((अचिन्हित दीर्घ)(_usp)) - 14;		\
पूर्ण जबतक (0)
#पूर्ण_अगर

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा	KSTK_EIP(tsk)	\
	(अणु			 \
		अचिन्हित दीर्घ eip = 0;	      \
		अगर ((tsk)->thपढ़ो.esp0 > PAGE_SIZE &&	\
		    MAP_NR((tsk)->thपढ़ो.esp0) < max_mapnr)	 \
			eip = ((काष्ठा pt_regs *) (tsk)->thपढ़ो.esp0)->pc; \
		eip; पूर्ण)

#घोषणा	KSTK_ESP(tsk)	((tsk) == current ? rdusp() : (tsk)->thपढ़ो.usp)

#घोषणा cpu_relax()    barrier()

#घोषणा HARD_RESET_NOW() (अणु		\
	local_irq_disable();		\
	यंत्र("jmp @@0");			\
पूर्ण)

#पूर्ण_अगर
