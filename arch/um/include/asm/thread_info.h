<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_THREAD_INFO_H
#घोषणा __UM_THREAD_INFO_H

#घोषणा THREAD_SIZE_ORDER CONFIG_KERNEL_STACK_ORDER
#घोषणा THREAD_SIZE ((1 << CONFIG_KERNEL_STACK_ORDER) * PAGE_SIZE)

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/segment.h>
#समावेश <sysdep/ptrace_user.h>

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;		/* low level flags */
	__u32			cpu;		/* current CPU */
	पूर्णांक			preempt_count;  /* 0 => preemptable,
						   <0 => BUG */
	mm_segment_t		addr_limit;	/* thपढ़ो address space:
					 	   0-0xBFFFFFFF क्रम user
						   0-0xFFFFFFFF क्रम kernel */
	काष्ठा thपढ़ो_info	*real_thपढ़ो;    /* Poपूर्णांकs to non-IRQ stack */
	अचिन्हित दीर्घ aux_fp_regs[FP_SIZE];	/* auxiliary fp_regs to save/restore
						   them out-of-band */
पूर्ण;

#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task =		&tsk,			\
	.flags =		0,		\
	.cpu =		0,			\
	.preempt_count = INIT_PREEMPT_COUNT,	\
	.addr_limit =	KERNEL_DS,		\
	.real_thपढ़ो = शून्य,			\
पूर्ण

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti;
	अचिन्हित दीर्घ mask = THREAD_SIZE - 1;
	व्योम *p;

	यंत्र अस्थिर ("" : "=r" (p) : "0" (&ti));
	ti = (काष्ठा thपढ़ो_info *) (((अचिन्हित दीर्घ)p) & ~mask);
	वापस ti;
पूर्ण

#पूर्ण_अगर

#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_NOTIFY_SIGNAL	3	/* संकेत notअगरications exist */
#घोषणा TIF_RESTART_BLOCK	4
#घोषणा TIF_MEMDIE		5	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_SYSCALL_AUDIT	6
#घोषणा TIF_RESTORE_SIGMASK	7
#घोषणा TIF_NOTIFY_RESUME	8
#घोषणा TIF_SECCOMP		9	/* secure computing */

#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_MEMDIE		(1 << TIF_MEMDIE)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)

#पूर्ण_अगर
