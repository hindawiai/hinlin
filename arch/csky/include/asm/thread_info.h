<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_CSKY_THREAD_INFO_H
#घोषणा _ASM_CSKY_THREAD_INFO_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <abi/चयन_context.h>

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;
	व्योम			*dump_exec_करोमुख्य;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			preempt_count;
	अचिन्हित दीर्घ		tp_value;
	mm_segment_t		addr_limit;
	काष्ठा restart_block	restart_block;
	काष्ठा pt_regs		*regs;
	अचिन्हित पूर्णांक		cpu;
पूर्ण;

#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.preempt_count  = INIT_PREEMPT_COUNT,	\
	.addr_limit     = KERNEL_DS,		\
	.cpu		= 0,			\
	.restart_block = अणु			\
		.fn = करो_no_restart_syscall,	\
	पूर्ण,					\
पूर्ण

#घोषणा THREAD_SIZE_ORDER (THREAD_SHIFT - PAGE_SHIFT)

#घोषणा thपढ़ो_saved_fp(tsk) \
	((अचिन्हित दीर्घ)(((काष्ठा चयन_stack *)(tsk->thपढ़ो.sp))->r8))

#घोषणा thपढ़ो_saved_sp(tsk) \
	((अचिन्हित दीर्घ)(tsk->thपढ़ो.sp))

#घोषणा thपढ़ो_saved_lr(tsk) \
	((अचिन्हित दीर्घ)(((काष्ठा चयन_stack *)(tsk->thपढ़ो.sp))->r15))

अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	अचिन्हित दीर्घ sp;

	यंत्र अस्थिर("mov %0, sp\n":"=r"(sp));

	वापस (काष्ठा thपढ़ो_info *)(sp & ~(THREAD_SIZE - 1));
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा TIF_SIGPENDING		0	/* संकेत pending */
#घोषणा TIF_NOTIFY_RESUME	1       /* callback beक्रमe वापसing to user */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_UPROBE		3	/* uprobe अवरोधpoपूर्णांक or singlestep */
#घोषणा TIF_SYSCALL_TRACE	4	/* syscall trace active */
#घोषणा TIF_SYSCALL_TRACEPOINT	5       /* syscall tracepoपूर्णांक instrumentation */
#घोषणा TIF_SYSCALL_AUDIT	6	/* syscall auditing */
#घोषणा TIF_NOTIFY_SIGNAL	7	/* संकेत notअगरications exist */
#घोषणा TIF_POLLING_NRFLAG	16	/* poll_idle() is TIF_NEED_RESCHED */
#घोषणा TIF_MEMDIE		18      /* is terminating due to OOM समाप्तer */
#घोषणा TIF_RESTORE_SIGMASK	20	/* restore संकेत mask in करो_संकेत() */
#घोषणा TIF_SECCOMP		21	/* secure computing */

#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1 << TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_UPROBE		(1 << TIF_UPROBE)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)
#घोषणा _TIF_MEMDIE		(1 << TIF_MEMDIE)
#घोषणा _TIF_RESTORE_SIGMASK	(1 << TIF_RESTORE_SIGMASK)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)

#घोषणा _TIF_WORK_MASK		(_TIF_NEED_RESCHED | _TIF_SIGPENDING | \
				 _TIF_NOTIFY_RESUME | _TIF_UPROBE | \
				 _TIF_NOTIFY_SIGNAL)

#घोषणा _TIF_SYSCALL_WORK	(_TIF_SYSCALL_TRACE | _TIF_SYSCALL_AUDIT | \
				 _TIF_SYSCALL_TRACEPOINT | _TIF_SECCOMP)

#पूर्ण_अगर	/* _ASM_CSKY_THREAD_INFO_H */
