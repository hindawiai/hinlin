<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#अगर_अघोषित _ASM_IA64_THREAD_INFO_H
#घोषणा _ASM_IA64_THREAD_INFO_H

#अगर_अघोषित ASM_OFFSETS_C
#समावेश <यंत्र/यंत्र-offsets.h>
#पूर्ण_अगर
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा THREAD_SIZE			KERNEL_STACK_SIZE

#अगर_अघोषित __ASSEMBLY__

/*
 * On IA-64, we want to keep the task काष्ठाure and kernel stack together, so they can be
 * mapped by a single TLB entry and so they can be addressed by the "current" poपूर्णांकer
 * without having to करो poपूर्णांकer masking.
 */
काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा *task;	/* XXX not really needed, except क्रम dup_task_काष्ठा() */
	__u32 flags;			/* thपढ़ो_info flags (see TIF_*) */
	__u32 cpu;			/* current CPU */
	__u32 last_cpu;			/* Last CPU thपढ़ो ran on */
	__u32 status;			/* Thपढ़ो synchronous flags */
	mm_segment_t addr_limit;	/* user-level address space limit */
	पूर्णांक preempt_count;		/* 0=premptable, <0=BUG; will also serve as bh-counter */
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	__u64 uसमय;
	__u64 sसमय;
	__u64 gसमय;
	__u64 hardirq_समय;
	__u64 softirq_समय;
	__u64 idle_समय;
	__u64 ac_stamp;
	__u64 ac_leave;
	__u64 ac_sसमय;
	__u64 ac_uसमय;
#पूर्ण_अगर
पूर्ण;

#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.flags		= 0,			\
	.cpu		= 0,			\
	.addr_limit	= KERNEL_DS,		\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
पूर्ण

#अगर_अघोषित ASM_OFFSETS_C
/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
#घोषणा current_thपढ़ो_info()	((काष्ठा thपढ़ो_info *) ((अक्षर *) current + IA64_TASK_SIZE))
#घोषणा alloc_thपढ़ो_stack_node(tsk, node)	\
		((अचिन्हित दीर्घ *) ((अक्षर *) (tsk) + IA64_TASK_SIZE))
#घोषणा task_thपढ़ो_info(tsk)	((काष्ठा thपढ़ो_info *) ((अक्षर *) (tsk) + IA64_TASK_SIZE))
#अन्यथा
#घोषणा current_thपढ़ो_info()	((काष्ठा thपढ़ो_info *) 0)
#घोषणा alloc_thपढ़ो_stack_node(tsk, node)	((अचिन्हित दीर्घ *) 0)
#घोषणा task_thपढ़ो_info(tsk)	((काष्ठा thपढ़ो_info *) 0)
#पूर्ण_अगर
#घोषणा मुक्त_thपढ़ो_stack(tsk)	/* nothing */
#घोषणा task_stack_page(tsk)	((व्योम *)(tsk))

#घोषणा __HAVE_THREAD_FUNCTIONS
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
#घोषणा setup_thपढ़ो_stack(p, org)			\
	*task_thपढ़ो_info(p) = *task_thपढ़ो_info(org);	\
	task_thपढ़ो_info(p)->ac_sसमय = 0;		\
	task_thपढ़ो_info(p)->ac_uसमय = 0;		\
	task_thपढ़ो_info(p)->task = (p);
#अन्यथा
#घोषणा setup_thपढ़ो_stack(p, org) \
	*task_thपढ़ो_info(p) = *task_thपढ़ो_info(org); \
	task_thपढ़ो_info(p)->task = (p);
#पूर्ण_अगर
#घोषणा end_of_stack(p) (अचिन्हित दीर्घ *)((व्योम *)(p) + IA64_RBS_OFFSET)

#घोषणा alloc_task_काष्ठा_node(node)						\
(अणु										\
	काष्ठा page *page = alloc_pages_node(node, GFP_KERNEL | __GFP_COMP,	\
					     KERNEL_STACK_SIZE_ORDER);		\
	काष्ठा task_काष्ठा *ret = page ? page_address(page) : शून्य;		\
										\
	ret;									\
पूर्ण)
#घोषणा मुक्त_task_काष्ठा(tsk)	मुक्त_pages((अचिन्हित दीर्घ) (tsk), KERNEL_STACK_SIZE_ORDER)

#पूर्ण_अगर /* !__ASSEMBLY */

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files may need to access
 * - pending work-to-be-करोne flags are in least-signअगरicant 16 bits, other flags
 *   in top 16 bits
 */
#घोषणा TIF_SIGPENDING		0	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	1	/* rescheduling necessary */
#घोषणा TIF_SYSCALL_TRACE	2	/* syscall trace active */
#घोषणा TIF_SYSCALL_AUDIT	3	/* syscall auditing active */
#घोषणा TIF_SINGLESTEP		4	/* restore singlestep on वापस to user mode */
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरication exist */
#घोषणा TIF_NOTIFY_RESUME	6	/* resumption notअगरication requested */
#घोषणा TIF_MEMDIE		17	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_MCA_INIT		18	/* this task is processing MCA or INIT */
#घोषणा TIF_DB_DISABLED		19	/* debug trap disabled क्रम fsyscall */
#घोषणा TIF_RESTORE_RSE		21	/* user RBS is newer than kernel RBS */
#घोषणा TIF_POLLING_NRFLAG	22	/* idle is polling क्रम TIF_NEED_RESCHED */

#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_SYSCALL_TRACEAUDIT	(_TIF_SYSCALL_TRACE|_TIF_SYSCALL_AUDIT|_TIF_SINGLESTEP)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_MCA_INIT		(1 << TIF_MCA_INIT)
#घोषणा _TIF_DB_DISABLED	(1 << TIF_DB_DISABLED)
#घोषणा _TIF_RESTORE_RSE	(1 << TIF_RESTORE_RSE)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)

/* "work to do on user-return" bits */
#घोषणा TIF_ALLWORK_MASK	(_TIF_SIGPENDING|_TIF_NOTIFY_RESUME|_TIF_SYSCALL_AUDIT|\
				 _TIF_NEED_RESCHED|_TIF_SYSCALL_TRACE|_TIF_NOTIFY_SIGNAL)
/* like TIF_ALLWORK_BITS but sans TIF_SYSCALL_TRACE or TIF_SYSCALL_AUDIT */
#घोषणा TIF_WORK_MASK		(TIF_ALLWORK_MASK&~(_TIF_SYSCALL_TRACE|_TIF_SYSCALL_AUDIT))

#पूर्ण_अगर /* _ASM_IA64_THREAD_INFO_H */
