<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * thपढ़ो_info.h: sparc low-level thपढ़ो inक्रमmation
 * adapted from the ppc version by Pete Zaitcev, which was
 * adapted from the i386 version by Paul Mackerras
 *
 * Copyright (C) 2002  David Howells (dhowells@redhat.com)
 * Copyright (c) 2002  Pete Zaitcev (zaitcev@yahoo.com)
 * - Incorporating suggestions made by Linus Torvalds and Dave Miller
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/page.h>

/*
 * Low level task data.
 *
 * If you change this, change the TI_* offsets below to match.
 */
#घोषणा NSWINS 8
काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ		uwinmask;
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;		/* low level flags */
	पूर्णांक			cpu;		/* cpu we're on */
	पूर्णांक			preempt_count;	/* 0 => preemptable,
						   <0 => BUG */
	पूर्णांक			softirq_count;
	पूर्णांक			hardirq_count;

	u32 __unused;

	/* Context चयन saved kernel state. */
	अचिन्हित दीर्घ ksp;	/* ... ksp __attribute__ ((aligned (8))); */
	अचिन्हित दीर्घ kpc;
	अचिन्हित दीर्घ kpsr;
	अचिन्हित दीर्घ kwim;

	/* A place to store user winकरोws and stack poपूर्णांकers
	 * when the stack needs inspection.
	 */
	काष्ठा reg_winकरोw32	reg_winकरोw[NSWINS];	/* align क्रम ldd! */
	अचिन्हित दीर्घ		rwbuf_stkptrs[NSWINS];
	अचिन्हित दीर्घ		w_saved;
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */
#घोषणा INIT_THREAD_INFO(tsk)				\
अणु							\
	.uwinmask	=	0,			\
	.task		=	&tsk,			\
	.flags		=	0,			\
	.cpu		=	0,			\
	.preempt_count	=	INIT_PREEMPT_COUNT,	\
पूर्ण

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
रेजिस्टर काष्ठा thपढ़ो_info *current_thपढ़ो_info_reg यंत्र("g6");
#घोषणा current_thपढ़ो_info()   (current_thपढ़ो_info_reg)

/*
 * thपढ़ो inक्रमmation allocation
 */
#घोषणा THREAD_SIZE_ORDER  1

#पूर्ण_अगर /* __ASSEMBLY__ */

/* Size of kernel stack क्रम each process */
#घोषणा THREAD_SIZE		(2 * PAGE_SIZE)

/*
 * Offsets in thपढ़ो_info काष्ठाure, used in assembly code
 * The "#define REGWIN_SZ 0x40" was abolished, so no multiplications.
 */
#घोषणा TI_UWINMASK	0x00	/* uwinmask */
#घोषणा TI_TASK		0x04
#घोषणा TI_FLAGS	0x08
#घोषणा TI_CPU		0x0c
#घोषणा TI_PREEMPT	0x10	/* preempt_count */
#घोषणा TI_SOFTIRQ	0x14	/* softirq_count */
#घोषणा TI_HARसूचीQ	0x18	/* hardirq_count */
#घोषणा TI_KSP		0x20	/* ksp */
#घोषणा TI_KPC		0x24	/* kpc (ldd'ed with kpc) */
#घोषणा TI_KPSR		0x28	/* kpsr */
#घोषणा TI_KWIM		0x2c	/* kwim (ldd'ed with kpsr) */
#घोषणा TI_REG_WINDOW	0x30
#घोषणा TI_RWIN_SPTRS	0x230
#घोषणा TI_W_SAVED	0x250

/*
 * thपढ़ो inक्रमmation flag bit numbers
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME	1	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_RESTORE_SIGMASK	4	/* restore संकेत mask in करो_संकेत() */
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरications exist */
#घोषणा TIF_USEDFPU		8	/* FPU was used by this task
					 * this quantum (SMP) */
#घोषणा TIF_POLLING_NRFLAG	9	/* true अगर poll_idle() is polling
					 * TIF_NEED_RESCHED */
#घोषणा TIF_MEMDIE		10	/* is terminating due to OOM समाप्तer */

/* as above, but as bit values */
#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_USEDFPU		(1<<TIF_USEDFPU)
#घोषणा _TIF_POLLING_NRFLAG	(1<<TIF_POLLING_NRFLAG)

#घोषणा _TIF_DO_NOTIFY_RESUME_MASK	(_TIF_NOTIFY_RESUME | \
					 _TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL)

#घोषणा is_32bit_task()	(1)

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_THREAD_INFO_H */
