<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/processor.h>
#पूर्ण_अगर


/* THREAD_SIZE is the size of the task_काष्ठा/kernel_stack combo.
 * normally, the stack is found by करोing something like p + THREAD_SIZE
 * in or32, a page is 8192 bytes, which seems like a sane size
 */

#घोषणा THREAD_SIZE_ORDER 0
#घोषणा THREAD_SIZE       (PAGE_SIZE << THREAD_SIZE_ORDER)

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 * - अगर the contents of this काष्ठाure are changed, the assembly स्थिरants
 *   must also be changed
 */
#अगर_अघोषित __ASSEMBLY__

प्रकार अचिन्हित दीर्घ mm_segment_t;

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;		/* low level flags */
	__u32			cpu;		/* current CPU */
	__s32			preempt_count; /* 0 => preemptable, <0 => BUG */

	mm_segment_t		addr_limit; /* thपढ़ो address space:
					       0-0x7FFFFFFF क्रम user-thead
					       0-0xFFFFFFFF क्रम kernel-thपढ़ो
					     */
	__u8			supervisor_stack[0];

	/* saved context data */
	अचिन्हित दीर्घ           ksp;
पूर्ण;
#पूर्ण_अगर

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 *
 * preempt_count needs to be 1 initially, until the scheduler is functional.
 */
#अगर_अघोषित __ASSEMBLY__
#घोषणा INIT_THREAD_INFO(tsk)				\
अणु							\
	.task		= &tsk,				\
	.flags		= 0,				\
	.cpu		= 0,				\
	.preempt_count	= INIT_PREEMPT_COUNT,		\
	.addr_limit	= KERNEL_DS,			\
	.ksp            = 0,                            \
पूर्ण

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
रेजिस्टर काष्ठा thपढ़ो_info *current_thपढ़ो_info_reg यंत्र("r10");
#घोषणा current_thपढ़ो_info()   (current_thपढ़ो_info_reg)

#घोषणा get_thपढ़ो_info(ti) get_task_काष्ठा((ti)->task)
#घोषणा put_thपढ़ो_info(ti) put_task_काष्ठा((ti)->task)

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flags
 *   these are process state flags that various assembly files may need to
 *   access
 *   - pending work-to-be-करोne flags are in LSW
 *   - other flags in MSW
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME	1	/* resumption notअगरication requested */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_SINGLESTEP		4	/* restore singlestep on वापस to user
					 * mode
					 */
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरications exist */
#घोषणा TIF_SYSCALL_TRACEPOINT  8       /* क्रम ftrace syscall instrumentation */
#घोषणा TIF_RESTORE_SIGMASK     9
#घोषणा TIF_POLLING_NRFLAG	16	/* true अगर poll_idle() is polling						 * TIF_NEED_RESCHED
					 */
#घोषणा TIF_MEMDIE              17

#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_SINGLESTEP		(1<<TIF_SINGLESTEP)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_POLLING_NRFLAG	(1<<TIF_POLLING_NRFLAG)


/* Work to करो when वापसing from पूर्णांकerrupt/exception */
/* For OpenRISC, this is anything in the LSW other than syscall trace */
#घोषणा _TIF_WORK_MASK (0xff & ~(_TIF_SYSCALL_TRACE|_TIF_SINGLESTEP))

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_THREAD_INFO_H */
