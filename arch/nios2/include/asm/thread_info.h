<शैली गुरु>
/*
 * NiosII low-level thपढ़ो inक्रमmation
 *
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * Based on यंत्र/thपढ़ो_info_no.h from m68k which is:
 *
 * Copyright (C) 2002 David Howells <dhowells@redhat.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_THREAD_INFO_H
#घोषणा _ASM_NIOS2_THREAD_INFO_H

#अगर_घोषित __KERNEL__

/*
 * Size of the kernel stack क्रम each process.
 */
#घोषणा THREAD_SIZE_ORDER	1
#घोषणा THREAD_SIZE		8192 /* 2 * PAGE_SIZE */

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 * - अगर the contents of this काष्ठाure are changed, the assembly स्थिरants
 *   must also be changed
 */
काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;		/* low level flags */
	__u32			cpu;		/* current CPU */
	पूर्णांक			preempt_count;	/* 0 => preemptable,<0 => BUG */
	mm_segment_t		addr_limit;	/* thपढ़ो address space:
						  0-0x7FFFFFFF क्रम user-thead
						  0-0xFFFFFFFF क्रम kernel-thपढ़ो
						*/
	काष्ठा pt_regs		*regs;
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 *
 * preempt_count needs to be 1 initially, until the scheduler is functional.
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.flags		= 0,			\
	.cpu		= 0,			\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
	.addr_limit	= KERNEL_DS,		\
पूर्ण

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	रेजिस्टर अचिन्हित दीर्घ sp यंत्र("sp");

	वापस (काष्ठा thपढ़ो_info *)(sp & ~(THREAD_SIZE - 1));
पूर्ण
#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files may need to
 *   access
 * - pending work-to-be-करोne flags are in LSW
 * - other flags in MSW
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME	1	/* resumption notअगरication requested */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_MEMDIE		4	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_SECCOMP		5	/* secure computing */
#घोषणा TIF_SYSCALL_AUDIT	6	/* syscall auditing active */
#घोषणा TIF_NOTIFY_SIGNAL	7	/* संकेत notअगरications exist */
#घोषणा TIF_RESTORE_SIGMASK	9	/* restore संकेत mask in करो_संकेत() */

#घोषणा TIF_POLLING_NRFLAG	16	/* true अगर poll_idle() is polling
					   TIF_NEED_RESCHED */

#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_RESTORE_SIGMASK	(1 << TIF_RESTORE_SIGMASK)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)

/* work to करो on पूर्णांकerrupt/exception वापस */
#घोषणा _TIF_WORK_MASK		0x0000FFFE

/* work to करो on any वापस to u-space */
# define _TIF_ALLWORK_MASK	0x0000FFFF

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_NIOS2_THREAD_INFO_H */
