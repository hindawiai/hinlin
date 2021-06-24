<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/thपढ़ो_info.h
 *
 * Copyright (C) 2002 Russell King.
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_THREAD_INFO_H
#घोषणा __ASM_THREAD_INFO_H

#समावेश <linux/compiler.h>

#अगर_अघोषित __ASSEMBLY__

काष्ठा task_काष्ठा;

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/stack_poपूर्णांकer.h>
#समावेश <यंत्र/types.h>

/*
 * low level task data that entry.S needs immediate access to.
 */
काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ		flags;		/* low level flags */
#अगर_घोषित CONFIG_ARM64_SW_TTBR0_PAN
	u64			ttbr0;		/* saved TTBR0_EL1 */
#पूर्ण_अगर
	जोड़ अणु
		u64		preempt_count;	/* 0 => preemptible, <0 => bug */
		काष्ठा अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
			u32	need_resched;
			u32	count;
#अन्यथा
			u32	count;
			u32	need_resched;
#पूर्ण_अगर
		पूर्ण preempt;
	पूर्ण;
#अगर_घोषित CONFIG_SHADOW_CALL_STACK
	व्योम			*scs_base;
	व्योम			*scs_sp;
#पूर्ण_अगर
पूर्ण;

#घोषणा thपढ़ो_saved_pc(tsk)	\
	((अचिन्हित दीर्घ)(tsk->thपढ़ो.cpu_context.pc))
#घोषणा thपढ़ो_saved_sp(tsk)	\
	((अचिन्हित दीर्घ)(tsk->thपढ़ो.cpu_context.sp))
#घोषणा thपढ़ो_saved_fp(tsk)	\
	((अचिन्हित दीर्घ)(tsk->thपढ़ो.cpu_context.fp))

व्योम arch_setup_new_exec(व्योम);
#घोषणा arch_setup_new_exec     arch_setup_new_exec

व्योम arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk);
पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst,
				काष्ठा task_काष्ठा *src);

#पूर्ण_अगर

#घोषणा TIF_SIGPENDING		0	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	1	/* rescheduling necessary */
#घोषणा TIF_NOTIFY_RESUME	2	/* callback beक्रमe वापसing to user */
#घोषणा TIF_FOREIGN_FPSTATE	3	/* CPU's FP state is not current's */
#घोषणा TIF_UPROBE		4	/* uprobe अवरोधpoपूर्णांक or singlestep */
#घोषणा TIF_MTE_ASYNC_FAULT	5	/* MTE Asynchronous Tag Check Fault */
#घोषणा TIF_NOTIFY_SIGNAL	6	/* संकेत notअगरications exist */
#घोषणा TIF_SYSCALL_TRACE	8	/* syscall trace active */
#घोषणा TIF_SYSCALL_AUDIT	9	/* syscall auditing */
#घोषणा TIF_SYSCALL_TRACEPOINT	10	/* syscall tracepoपूर्णांक क्रम ftrace */
#घोषणा TIF_SECCOMP		11	/* syscall secure computing */
#घोषणा TIF_SYSCALL_EMU		12	/* syscall emulation active */
#घोषणा TIF_MEMDIE		18	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_FREEZE		19
#घोषणा TIF_RESTORE_SIGMASK	20
#घोषणा TIF_SINGLESTEP		21
#घोषणा TIF_32BIT		22	/* 32bit process */
#घोषणा TIF_SVE			23	/* Scalable Vector Extension in use */
#घोषणा TIF_SVE_VL_INHERIT	24	/* Inherit sve_vl_onexec across exec */
#घोषणा TIF_SSBD		25	/* Wants SSB mitigation */
#घोषणा TIF_TAGGED_ADDR		26	/* Allow tagged user addresses */

#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_FOREIGN_FPSTATE	(1 << TIF_FOREIGN_FPSTATE)
#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1 << TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)
#घोषणा _TIF_SYSCALL_EMU	(1 << TIF_SYSCALL_EMU)
#घोषणा _TIF_UPROBE		(1 << TIF_UPROBE)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_32BIT		(1 << TIF_32BIT)
#घोषणा _TIF_SVE		(1 << TIF_SVE)
#घोषणा _TIF_MTE_ASYNC_FAULT	(1 << TIF_MTE_ASYNC_FAULT)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)

#घोषणा _TIF_WORK_MASK		(_TIF_NEED_RESCHED | _TIF_SIGPENDING | \
				 _TIF_NOTIFY_RESUME | _TIF_FOREIGN_FPSTATE | \
				 _TIF_UPROBE | _TIF_MTE_ASYNC_FAULT | \
				 _TIF_NOTIFY_SIGNAL)

#घोषणा _TIF_SYSCALL_WORK	(_TIF_SYSCALL_TRACE | _TIF_SYSCALL_AUDIT | \
				 _TIF_SYSCALL_TRACEPOINT | _TIF_SECCOMP | \
				 _TIF_SYSCALL_EMU)

#अगर_घोषित CONFIG_SHADOW_CALL_STACK
#घोषणा INIT_SCS							\
	.scs_base	= init_shaकरोw_call_stack,			\
	.scs_sp		= init_shaकरोw_call_stack,
#अन्यथा
#घोषणा INIT_SCS
#पूर्ण_अगर

#घोषणा INIT_THREAD_INFO(tsk)						\
अणु									\
	.flags		= _TIF_FOREIGN_FPSTATE,				\
	.preempt_count	= INIT_PREEMPT_COUNT,				\
	INIT_SCS							\
पूर्ण

#पूर्ण_अगर /* __ASM_THREAD_INFO_H */
