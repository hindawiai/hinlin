<शैली गुरु>
/*
 * include/यंत्र-xtensa/thपढ़ो_info.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_THREAD_INFO_H
#घोषणा _XTENSA_THREAD_INFO_H

#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/kmem_layout.h>

#घोषणा CURRENT_SHIFT KERNEL_STACK_SHIFT

#अगर_अघोषित __ASSEMBLY__
# include <यंत्र/processor.h>
#पूर्ण_अगर

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 * - अगर the contents of this काष्ठाure are changed, the assembly स्थिरants
 *   must also be changed
 */

#अगर_अघोषित __ASSEMBLY__

#अगर XTENSA_HAVE_COPROCESSORS

प्रकार काष्ठा xtregs_coprocessor अणु
	xtregs_cp0_t cp0;
	xtregs_cp1_t cp1;
	xtregs_cp2_t cp2;
	xtregs_cp3_t cp3;
	xtregs_cp4_t cp4;
	xtregs_cp5_t cp5;
	xtregs_cp6_t cp6;
	xtregs_cp7_t cp7;
पूर्ण xtregs_coprocessor_t;

#पूर्ण_अगर

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;		/* low level flags */
	अचिन्हित दीर्घ		status;		/* thपढ़ो-synchronous flags */
	__u32			cpu;		/* current CPU */
	__s32			preempt_count;	/* 0 => preemptable,< 0 => BUG*/

	mm_segment_t		addr_limit;	/* thपढ़ो address space */

	अचिन्हित दीर्घ		cpenable;
#अगर XCHAL_HAVE_EXCLUSIVE
	/* result of the most recent exclusive store */
	अचिन्हित दीर्घ		atomctl8;
#पूर्ण_अगर

	/* Allocate storage क्रम extra user states and coprocessor states. */
#अगर XTENSA_HAVE_COPROCESSORS
	xtregs_coprocessor_t	xtregs_cp;
#पूर्ण_अगर
	xtregs_user_t		xtregs_user;
पूर्ण;

#पूर्ण_अगर

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */

#अगर_अघोषित __ASSEMBLY__

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
	काष्ठा thपढ़ो_info *ti;
	 __यंत्र__("extui %0, a1, 0, "__stringअगरy(CURRENT_SHIFT)"\n\t"
	         "xor %0, a1, %0" : "=&r" (ti) : );
	वापस ti;
पूर्ण

#अन्यथा /* !__ASSEMBLY__ */

/* how to get the thपढ़ो inक्रमmation काष्ठा from ASM */
#घोषणा GET_THREAD_INFO(reg,sp) \
	extui reg, sp, 0, CURRENT_SHIFT; \
	xor   reg, sp, reg
#पूर्ण_अगर


/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files may need to access
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_SINGLESTEP		3	/* restore singlestep on वापस to user mode */
#घोषणा TIF_SYSCALL_TRACEPOINT	4	/* syscall tracepoपूर्णांक instrumentation */
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरications exist */
#घोषणा TIF_RESTORE_SIGMASK	6	/* restore संकेत mask in करो_संकेत() */
#घोषणा TIF_NOTIFY_RESUME	7	/* callback beक्रमe वापसing to user */
#घोषणा TIF_DB_DISABLED		8	/* debug trap disabled क्रम syscall */
#घोषणा TIF_SYSCALL_AUDIT	9	/* syscall auditing active */
#घोषणा TIF_SECCOMP		10	/* secure computing */
#घोषणा TIF_MEMDIE		11	/* is terminating due to OOM समाप्तer */

#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_SINGLESTEP		(1<<TIF_SINGLESTEP)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1<<TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_SYSCALL_AUDIT	(1<<TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SECCOMP		(1<<TIF_SECCOMP)

#घोषणा _TIF_WORK_MASK		(_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP | \
				 _TIF_SYSCALL_TRACEPOINT | \
				 _TIF_SYSCALL_AUDIT | _TIF_SECCOMP)

#घोषणा THREAD_SIZE KERNEL_STACK_SIZE
#घोषणा THREAD_SIZE_ORDER (KERNEL_STACK_SHIFT - PAGE_SHIFT)

#पूर्ण_अगर	/* _XTENSA_THREAD_INFO */
