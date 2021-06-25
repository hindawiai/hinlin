<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* include/यंत्र/processor.h
 *
 * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित __ASM_SPARC_PROCESSOR_H
#घोषणा __ASM_SPARC_PROCESSOR_H

#समावेश <यंत्र/psr.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/page.h>

/* Whee, this is STACK_TOP + PAGE_SIZE and the lowest kernel address too...
 * That one page is used to protect kernel from पूर्णांकruders, so that
 * we can make our access_ok test faster
 */
#घोषणा TASK_SIZE	PAGE_OFFSET
#अगर_घोषित __KERNEL__
#घोषणा STACK_TOP	(PAGE_OFFSET - PAGE_SIZE)
#घोषणा STACK_TOP_MAX	STACK_TOP
#पूर्ण_अगर /* __KERNEL__ */

काष्ठा task_काष्ठा;

#अगर_घोषित __KERNEL__
काष्ठा fpq अणु
	अचिन्हित दीर्घ *insn_addr;
	अचिन्हित दीर्घ insn;
पूर्ण;
#पूर्ण_अगर

प्रकार काष्ठा अणु
	पूर्णांक seg;
पूर्ण mm_segment_t;

/* The Sparc processor specअगरic thपढ़ो काष्ठा. */
काष्ठा thपढ़ो_काष्ठा अणु
	काष्ठा pt_regs *kregs;
	अचिन्हित पूर्णांक _pad1;

	/* Special child विभाजन kpsr/kwim values. */
	अचिन्हित दीर्घ विभाजन_kpsr __attribute__ ((aligned (8)));
	अचिन्हित दीर्घ विभाजन_kwim;

	/* Floating poपूर्णांक regs */
	अचिन्हित दीर्घ   भग्न_regs[32] __attribute__ ((aligned (8)));
	अचिन्हित दीर्घ   fsr;
	अचिन्हित दीर्घ   fpqdepth;
	काष्ठा fpq	fpqueue[16];
	mm_segment_t current_ds;
पूर्ण;

#घोषणा INIT_THREAD  अणु \
	.current_ds = KERNEL_DS, \
	.kregs = (काष्ठा pt_regs *)(init_stack+THREAD_SIZE)-1 \
पूर्ण

/* Do necessary setup to start up a newly executed thपढ़ो. */
अटल अंतरभूत व्योम start_thपढ़ो(काष्ठा pt_regs * regs, अचिन्हित दीर्घ pc,
				    अचिन्हित दीर्घ sp)
अणु
	रेजिस्टर अचिन्हित दीर्घ zero यंत्र("g1");

	regs->psr = (regs->psr & (PSR_CWP)) | PSR_S;
	regs->pc = ((pc & (~3)) - 4);
	regs->npc = regs->pc + 4;
	regs->y = 0;
	zero = 0;
	__यंत्र__ __अस्थिर__("std\t%%g0, [%0 + %3 + 0x00]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x08]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x10]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x18]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x20]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x28]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x30]\n\t"
			     "st\t%1, [%0 + %3 + 0x38]\n\t"
			     "st\t%%g0, [%0 + %3 + 0x3c]"
			     : /* no outमाला_दो */
			     : "r" (regs),
			       "r" (sp - माप(काष्ठा reg_winकरोw32)),
			       "r" (zero),
			       "i" ((स्थिर अचिन्हित दीर्घ)(&((काष्ठा pt_regs *)0)->u_regs[0]))
			     : "memory");
पूर्ण

/* Free all resources held by a thपढ़ो. */
#घोषणा release_thपढ़ो(tsk)		करो अणु पूर्ण जबतक(0)

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *);

#घोषणा task_pt_regs(tsk) ((tsk)->thपढ़ो.kregs)
#घोषणा KSTK_EIP(tsk)  ((tsk)->thपढ़ो.kregs->pc)
#घोषणा KSTK_ESP(tsk)  ((tsk)->thपढ़ो.kregs->u_regs[UREG_FP])

#अगर_घोषित __KERNEL__

बाह्य काष्ठा task_काष्ठा *last_task_used_math;
पूर्णांक करो_mathemu(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *fpt);

#घोषणा cpu_relax()	barrier()

बाह्य व्योम (*sparc_idle)(व्योम);

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SPARC_PROCESSOR_H */
