<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_THREAD_INFO_H
#घोषणा _ASM_MICROBLAZE_THREAD_INFO_H

#अगर_घोषित __KERNEL__

/* we have 8k stack */
#घोषणा THREAD_SHIFT		13
#घोषणा THREAD_SIZE		(1 << THREAD_SHIFT)
#घोषणा THREAD_SIZE_ORDER	1

#अगर_अघोषित __ASSEMBLY__
# include <linux/types.h>
# include <यंत्र/processor.h>

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 * - अगर the contents of this काष्ठाure are changed, the assembly स्थिरants
 *	 must also be changed
 */

काष्ठा cpu_context अणु
	__u32	r1; /* stack poपूर्णांकer */
	__u32	r2;
	/* dedicated रेजिस्टरs */
	__u32	r13;
	__u32	r14;
	__u32	r15;
	__u32	r16;
	__u32	r17;
	__u32	r18;
	/* non-अस्थिर रेजिस्टरs */
	__u32	r19;
	__u32	r20;
	__u32	r21;
	__u32	r22;
	__u32	r23;
	__u32	r24;
	__u32	r25;
	__u32	r26;
	__u32	r27;
	__u32	r28;
	__u32	r29;
	__u32	r30;
	/* r31 is used as current task poपूर्णांकer */
	/* special purpose रेजिस्टरs */
	__u32	msr;
	__u32	ear;
	__u32	esr;
	__u32	fsr;
पूर्ण;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task; /* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags; /* low level flags */
	अचिन्हित दीर्घ		status; /* thपढ़ो-synchronous flags */
	__u32			cpu; /* current CPU */
	__s32			preempt_count; /* 0 => preemptable,< 0 => BUG*/
	mm_segment_t		addr_limit; /* thपढ़ो address space */

	काष्ठा cpu_context	cpu_context;
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
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
	रेजिस्टर अचिन्हित दीर्घ sp यंत्र("r1");

	वापस (काष्ठा thपढ़ो_info *)(sp & ~(THREAD_SIZE-1));
पूर्ण

/* thपढ़ो inक्रमmation allocation */
#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files may
 *   need to access
 * - pending work-to-be-करोne flags are in LSW
 * - other flags in MSW
 */
#घोषणा TIF_SYSCALL_TRACE	0 /* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME	1 /* resumption notअगरication requested */
#घोषणा TIF_SIGPENDING		2 /* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3 /* rescheduling necessary */
/* restore singlestep on वापस to user mode */
#घोषणा TIF_SINGLESTEP		4
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरications exist */
#घोषणा TIF_MEMDIE		6	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_SYSCALL_AUDIT	9       /* syscall auditing active */
#घोषणा TIF_SECCOMP		10      /* secure computing */

/* true अगर poll_idle() is polling TIF_NEED_RESCHED */
#घोषणा TIF_POLLING_NRFLAG	16

#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)

/* work to करो in syscall trace */
#घोषणा _TIF_WORK_SYSCALL_MASK  (_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP | \
				 _TIF_SYSCALL_AUDIT | _TIF_SECCOMP)

/* work to करो on पूर्णांकerrupt/exception वापस */
#घोषणा _TIF_WORK_MASK		0x0000FFFE

/* work to करो on any वापस to u-space */
#घोषणा _TIF_ALLWORK_MASK	0x0000FFFF

/*
 * Thपढ़ो-synchronous status.
 *
 * This is dअगरferent from the flags in that nobody अन्यथा
 * ever touches our thपढ़ो-synchronous status, so we करोn't
 * have to worry about atomic accesses.
 */
/* FPU was used by this task this quantum (SMP) */
#घोषणा TS_USEDFPU		0x0001

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_THREAD_INFO_H */
