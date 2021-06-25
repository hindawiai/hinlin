<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_THREAD_INFO_H
#घोषणा __ASM_SH_THREAD_INFO_H

/* SuperH version
 * Copyright (C) 2002  Niibe Yutaka
 *
 * The copyright of original i386 version is:
 *
 *  Copyright (C) 2002  David Howells (dhowells@redhat.com)
 *  - Incorporating suggestions made by Linus Torvalds and Dave Miller
 */
#समावेश <यंत्र/page.h>

/*
 * Page fault error code bits
 */
#घोषणा FAULT_CODE_WRITE	(1 << 0)	/* ग_लिखो access */
#घोषणा FAULT_CODE_INITIAL	(1 << 1)	/* initial page ग_लिखो */
#घोषणा FAULT_CODE_ITLB		(1 << 2)	/* ITLB miss */
#घोषणा FAULT_CODE_PROT		(1 << 3)	/* protection fault */
#घोषणा FAULT_CODE_USER		(1 << 4)	/* user-mode access */

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/processor.h>

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;		/* low level flags */
	__u32			status;		/* thपढ़ो synchronous flags */
	__u32			cpu;
	पूर्णांक			preempt_count; /* 0 => preemptable, <0 => BUG */
	mm_segment_t		addr_limit;	/* thपढ़ो address space */
	अचिन्हित दीर्घ		previous_sp;	/* sp of previous stack in हाल
						   of nested IRQ stacks */
	__u8			supervisor_stack[0];
पूर्ण;

#पूर्ण_अगर

#अगर defined(CONFIG_4KSTACKS)
#घोषणा THREAD_SHIFT	12
#अन्यथा
#घोषणा THREAD_SHIFT	13
#पूर्ण_अगर

#घोषणा THREAD_SIZE	(1 << THREAD_SHIFT)
#घोषणा STACK_WARN	(THREAD_SIZE >> 3)

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */
#अगर_अघोषित __ASSEMBLY__
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.flags		= 0,			\
	.status		= 0,			\
	.cpu		= 0,			\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
	.addr_limit	= KERNEL_DS,		\
पूर्ण

/* how to get the current stack poपूर्णांकer from C */
रेजिस्टर अचिन्हित दीर्घ current_stack_poपूर्णांकer यंत्र("r15") __used;

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti;
#अगर defined(CONFIG_CPU_HAS_SR_RB)
	__यंत्र__ __अस्थिर__ ("stc	r7_bank, %0" : "=r" (ti));
#अन्यथा
	अचिन्हित दीर्घ __dummy;

	__यंत्र__ __अस्थिर__ (
		"mov	r15, %0\n\t"
		"and	%1, %0\n\t"
		: "=&r" (ti), "=r" (__dummy)
		: "1" (~(THREAD_SIZE - 1))
		: "memory");
#पूर्ण_अगर

	वापस ti;
पूर्ण

#घोषणा THREAD_SIZE_ORDER	(THREAD_SHIFT - PAGE_SHIFT)

बाह्य व्योम arch_task_cache_init(व्योम);
बाह्य पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src);
बाह्य व्योम arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम init_thपढ़ो_xstate(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Thपढ़ो inक्रमmation flags
 *
 * - Limited to 24 bits, upper byte used क्रम fault code encoding.
 *
 * - _TIF_ALLWORK_MASK and _TIF_WORK_MASK need to fit within 2 bytes, or
 *   we blow the tst immediate size स्थिरraपूर्णांकs and need to fix up
 *   arch/sh/kernel/entry-common.S.
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_NOTIFY_SIGNAL	3	/* संकेत notअगरications exist */
#घोषणा TIF_SINGLESTEP		4	/* singlestepping active */
#घोषणा TIF_SYSCALL_AUDIT	5	/* syscall auditing active */
#घोषणा TIF_SECCOMP		6	/* secure computing */
#घोषणा TIF_NOTIFY_RESUME	7	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SYSCALL_TRACEPOINT	8	/* क्रम ftrace syscall instrumentation */
#घोषणा TIF_POLLING_NRFLAG	17	/* true अगर poll_idle() is polling TIF_NEED_RESCHED */
#घोषणा TIF_MEMDIE		18	/* is terminating due to OOM समाप्तer */

#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1 << TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)

/* work to करो in syscall trace */
#घोषणा _TIF_WORK_SYSCALL_MASK	(_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP | \
				 _TIF_SYSCALL_AUDIT | _TIF_SECCOMP    | \
				 _TIF_SYSCALL_TRACEPOINT)

/* work to करो on any वापस to u-space */
#घोषणा _TIF_ALLWORK_MASK	(_TIF_SYSCALL_TRACE | _TIF_SIGPENDING      | \
				 _TIF_NEED_RESCHED  | _TIF_SYSCALL_AUDIT   | \
				 _TIF_SINGLESTEP    | _TIF_NOTIFY_RESUME   | \
				 _TIF_SYSCALL_TRACEPOINT | _TIF_NOTIFY_SIGNAL)

/* work to करो on पूर्णांकerrupt/exception वापस */
#घोषणा _TIF_WORK_MASK		(_TIF_ALLWORK_MASK & ~(_TIF_SYSCALL_TRACE | \
				 _TIF_SYSCALL_AUDIT | _TIF_SINGLESTEP))

/*
 * Thपढ़ो-synchronous status.
 *
 * This is dअगरferent from the flags in that nobody अन्यथा
 * ever touches our thपढ़ो-synchronous status, so we करोn't
 * have to worry about atomic accesses.
 */
#घोषणा TS_USEDFPU		0x0002	/* FPU used by this task this quantum */

#अगर_अघोषित __ASSEMBLY__

#घोषणा TI_FLAG_FAULT_CODE_SHIFT	24

/*
 * Additional thपढ़ो flag encoding
 */
अटल अंतरभूत व्योम set_thपढ़ो_fault_code(अचिन्हित पूर्णांक val)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	ti->flags = (ti->flags & (~0 >> (32 - TI_FLAG_FAULT_CODE_SHIFT)))
		| (val << TI_FLAG_FAULT_CODE_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_thपढ़ो_fault_code(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	वापस ti->flags >> TI_FLAG_FAULT_CODE_SHIFT;
पूर्ण

#पूर्ण_अगर	/* !__ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_SH_THREAD_INFO_H */
