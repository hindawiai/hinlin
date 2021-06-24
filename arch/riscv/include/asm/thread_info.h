<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009 Chen Liqin <liqin.chen@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#अगर_अघोषित _ASM_RISCV_THREAD_INFO_H
#घोषणा _ASM_RISCV_THREAD_INFO_H

#समावेश <यंत्र/page.h>
#समावेश <linux/स्थिर.h>

/* thपढ़ो inक्रमmation allocation */
#अगर_घोषित CONFIG_64BIT
#घोषणा THREAD_SIZE_ORDER	(2)
#अन्यथा
#घोषणा THREAD_SIZE_ORDER	(1)
#पूर्ण_अगर
#घोषणा THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/csr.h>

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - अगर the members of this काष्ठा changes, the assembly स्थिरants
 *   in यंत्र-offsets.c must be updated accordingly
 * - thपढ़ो_info is included in task_काष्ठा at an offset of 0.  This means that
 *   tp poपूर्णांकs to both thपढ़ो_info and task_काष्ठा.
 */
काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ		flags;		/* low level flags */
	पूर्णांक                     preempt_count;  /* 0=>preemptible, <0=>BUG */
	/*
	 * These stack poपूर्णांकers are overwritten on every प्रणाली call or
	 * exception.  SP is also saved to the stack it can be recovered when
	 * overwritten.
	 */
	दीर्घ			kernel_sp;	/* Kernel stack poपूर्णांकer */
	दीर्घ			user_sp;	/* User stack poपूर्णांकer */
	पूर्णांक			cpu;
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 *
 * preempt_count needs to be 1 initially, until the scheduler is functional.
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.flags		= 0,			\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files may need to
 *   access
 * - pending work-to-be-करोne flags are in lowest half-word
 * - other flags in upper half-word(s)
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME	1	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_RESTORE_SIGMASK	4	/* restore संकेत mask in करो_संकेत() */
#घोषणा TIF_MEMDIE		5	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_SYSCALL_TRACEPOINT  6       /* syscall tracepoपूर्णांक instrumentation */
#घोषणा TIF_SYSCALL_AUDIT	7	/* syscall auditing */
#घोषणा TIF_SECCOMP		8	/* syscall secure computing */
#घोषणा TIF_NOTIFY_SIGNAL	9	/* संकेत notअगरications exist */
#घोषणा TIF_UPROBE		10	/* uprobe अवरोधpoपूर्णांक or singlestep */

#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1 << TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_UPROBE		(1 << TIF_UPROBE)

#घोषणा _TIF_WORK_MASK \
	(_TIF_NOTIFY_RESUME | _TIF_SIGPENDING | _TIF_NEED_RESCHED | \
	 _TIF_NOTIFY_SIGNAL | _TIF_UPROBE)

#घोषणा _TIF_SYSCALL_WORK \
	(_TIF_SYSCALL_TRACE | _TIF_SYSCALL_TRACEPOINT | _TIF_SYSCALL_AUDIT | \
	 _TIF_SECCOMP)

#पूर्ण_अगर /* _ASM_RISCV_THREAD_INFO_H */
