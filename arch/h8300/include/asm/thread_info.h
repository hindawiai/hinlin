<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* thपढ़ो_info.h: h8300 low-level thपढ़ो inक्रमmation
 * adapted from the i386 and PPC versions by Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * Copyright (C) 2002  David Howells (dhowells@redhat.com)
 * - Incorporating suggestions made by Linus Torvalds and Dave Miller
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/segment.h>

#अगर_घोषित __KERNEL__

/*
 * Size of kernel stack क्रम each process. This must be a घातer of 2...
 */
#घोषणा THREAD_SIZE_ORDER	1
#घोषणा THREAD_SIZE		8192	/* 2 pages */

#अगर_अघोषित __ASSEMBLY__

/*
 * low level task data.
 * If you change this, change the TI_* offsets below to match.
 */
काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा *task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ	   flags;		/* low level flags */
	पूर्णांक		   cpu;			/* cpu we're on */
	पूर्णांक		   preempt_count;	/* 0 => preemptable, <0 => BUG */
	mm_segment_t		addr_limit;
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task =		&tsk,			\
	.flags =	0,			\
	.cpu =		0,			\
	.preempt_count = INIT_PREEMPT_COUNT,	\
	.addr_limit	= KERNEL_DS,		\
पूर्ण

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti;

	__यंत्र__("mov.l	sp, %0\n\t"
		"and.w	%1, %T0"
		: "=&r"(ti)
		: "i" (~(THREAD_SIZE-1) & 0xffff));
	वापस ti;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flag bit numbers
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_SINGLESTEP		3	/* singlestepping active */
#घोषणा TIF_MEMDIE		4	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_RESTORE_SIGMASK	5	/* restore संकेत mask in करो_संकेत() */
#घोषणा TIF_NOTIFY_RESUME	6	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SYSCALL_AUDIT	7	/* syscall auditing active */
#घोषणा TIF_SYSCALL_TRACEPOINT	8	/* क्रम ftrace syscall instrumentation */
#घोषणा TIF_POLLING_NRFLAG	9	/* true अगर poll_idle() is polling TIF_NEED_RESCHED */
#घोषणा TIF_NOTIFY_SIGNAL	10	/* संकेत notअगरications exist */

/* as above, but as bit values */
#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1 << TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)

/* work to करो in syscall trace */
#घोषणा _TIF_WORK_SYSCALL_MASK	(_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP | \
				 _TIF_SYSCALL_AUDIT | _TIF_SYSCALL_TRACEPOINT)

/* work to करो on any वापस to u-space */
#घोषणा _TIF_ALLWORK_MASK	(_TIF_SYSCALL_TRACE | _TIF_SIGPENDING      | \
				 _TIF_NEED_RESCHED  | _TIF_SYSCALL_AUDIT   | \
				 _TIF_SINGLESTEP    | _TIF_NOTIFY_RESUME   | \
				 _TIF_SYSCALL_TRACEPOINT | _TIF_NOTIFY_SIGNAL)

/* work to करो on पूर्णांकerrupt/exception वापस */
#घोषणा _TIF_WORK_MASK		(_TIF_ALLWORK_MASK & ~(_TIF_SYSCALL_TRACE | \
				 _TIF_SYSCALL_AUDIT | _TIF_SINGLESTEP))

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_THREAD_INFO_H */
