<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_THREAD_INFO_H
#घोषणा _ASM_PARISC_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/special_insns.h>

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा *task;	/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ flags;		/* thपढ़ो_info flags (see TIF_*) */
	mm_segment_t addr_limit;	/* user-level address space limit */
	__u32 cpu;			/* current CPU */
	पूर्णांक preempt_count;		/* 0=premptable, <0=BUG; will also serve as bh-counter */
पूर्ण;

#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.flags		= 0,			\
	.cpu		= 0,			\
	.addr_limit	= KERNEL_DS,		\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
पूर्ण

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
#घोषणा current_thपढ़ो_info()	((काष्ठा thपढ़ो_info *)mfctl(30))

#पूर्ण_अगर /* !__ASSEMBLY */

/* thपढ़ो inक्रमmation allocation */

#अगर_घोषित CONFIG_IRQSTACKS
#घोषणा THREAD_SIZE_ORDER	2 /* PA-RISC requires at least 16k stack */
#अन्यथा
#घोषणा THREAD_SIZE_ORDER	3 /* PA-RISC requires at least 32k stack */
#पूर्ण_अगर

/* Be sure to hunt all references to this करोwn when you change the size of
 * the kernel stack */
#घोषणा THREAD_SIZE             (PAGE_SIZE << THREAD_SIZE_ORDER)
#घोषणा THREAD_SHIFT            (PAGE_SHIFT + THREAD_SIZE_ORDER)

/*
 * thपढ़ो inक्रमmation flags
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_POLLING_NRFLAG	3	/* true अगर poll_idle() is polling TIF_NEED_RESCHED */
#घोषणा TIF_32BIT               4       /* 32 bit binary */
#घोषणा TIF_MEMDIE		5	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_NOTIFY_SIGNAL	6	/* संकेत notअगरications exist */
#घोषणा TIF_SYSCALL_AUDIT	7	/* syscall auditing active */
#घोषणा TIF_NOTIFY_RESUME	8	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SINGLESTEP		9	/* single stepping? */
#घोषणा TIF_BLOCKSTEP		10	/* branch stepping? */
#घोषणा TIF_SECCOMP		11	/* secure computing */
#घोषणा TIF_SYSCALL_TRACEPOINT	12	/* syscall tracepoपूर्णांक instrumentation */

#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)
#घोषणा _TIF_32BIT		(1 << TIF_32BIT)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_BLOCKSTEP		(1 << TIF_BLOCKSTEP)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1 << TIF_SYSCALL_TRACEPOINT)

#घोषणा _TIF_USER_WORK_MASK     (_TIF_SIGPENDING | _TIF_NOTIFY_RESUME | \
                                 _TIF_NEED_RESCHED | _TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_SYSCALL_TRACE_MASK (_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP |	\
				 _TIF_BLOCKSTEP | _TIF_SYSCALL_AUDIT | \
				 _TIF_SECCOMP | _TIF_SYSCALL_TRACEPOINT)

#अगर_घोषित CONFIG_64BIT
# अगरdef CONFIG_COMPAT
#  define is_32bit_task()	(test_thपढ़ो_flag(TIF_32BIT))
# अन्यथा
#  define is_32bit_task()	(0)
# endअगर
#अन्यथा
# define is_32bit_task()	(1)
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_PARISC_THREAD_INFO_H */
