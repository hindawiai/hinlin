<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/thपढ़ो_info.h
 *
 *  Copyright (C) 2002 Russell King.
 */
#अगर_अघोषित __ASM_ARM_THREAD_INFO_H
#घोषणा __ASM_ARM_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <यंत्र/fpstate.h>
#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_KASAN
/*
 * KASan uses a lot of extra stack space so the thपढ़ो size order needs to
 * be increased.
 */
#घोषणा THREAD_SIZE_ORDER	2
#अन्यथा
#घोषणा THREAD_SIZE_ORDER	1
#पूर्ण_अगर
#घोषणा THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)
#घोषणा THREAD_START_SP		(THREAD_SIZE - 8)

#अगर_अघोषित __ASSEMBLY__

काष्ठा task_काष्ठा;

#समावेश <यंत्र/types.h>

प्रकार अचिन्हित दीर्घ mm_segment_t;

काष्ठा cpu_context_save अणु
	__u32	r4;
	__u32	r5;
	__u32	r6;
	__u32	r7;
	__u32	r8;
	__u32	r9;
	__u32	sl;
	__u32	fp;
	__u32	sp;
	__u32	pc;
	__u32	extra[2];		/* Xscale 'acc' रेजिस्टर, etc */
पूर्ण;

/*
 * low level task data that entry.S needs immediate access to.
 * __चयन_to() assumes cpu_context follows immediately after cpu_करोमुख्य.
 */
काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ		flags;		/* low level flags */
	पूर्णांक			preempt_count;	/* 0 => preemptable, <0 => bug */
	mm_segment_t		addr_limit;	/* address limit */
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	__u32			cpu;		/* cpu */
	__u32			cpu_करोमुख्य;	/* cpu करोमुख्य */
#अगर_घोषित CONFIG_STACKPROTECTOR_PER_TASK
	अचिन्हित दीर्घ		stack_canary;
#पूर्ण_अगर
	काष्ठा cpu_context_save	cpu_context;	/* cpu context */
	__u32			syscall;	/* syscall number */
	__u8			used_cp[16];	/* thपढ़ो used copro */
	अचिन्हित दीर्घ		tp_value[2];	/* TLS रेजिस्टरs */
#अगर_घोषित CONFIG_CRUNCH
	काष्ठा crunch_state	crunchstate;
#पूर्ण_अगर
	जोड़ fp_state		fpstate __attribute__((aligned(8)));
	जोड़ vfp_state		vfpstate;
#अगर_घोषित CONFIG_ARM_THUMBEE
	अचिन्हित दीर्घ		thumbee_state;	/* ThumbEE Handler Base रेजिस्टर */
#पूर्ण_अगर
पूर्ण;

#घोषणा INIT_THREAD_INFO(tsk)						\
अणु									\
	.task		= &tsk,						\
	.flags		= 0,						\
	.preempt_count	= INIT_PREEMPT_COUNT,				\
	.addr_limit	= KERNEL_DS,					\
पूर्ण

/*
 * how to get the thपढ़ो inक्रमmation काष्ठा from C
 */
अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम) __attribute_स्थिर__;

अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	वापस (काष्ठा thपढ़ो_info *)
		(current_stack_poपूर्णांकer & ~(THREAD_SIZE - 1));
पूर्ण

#घोषणा thपढ़ो_saved_pc(tsk)	\
	((अचिन्हित दीर्घ)(task_thपढ़ो_info(tsk)->cpu_context.pc))
#घोषणा thपढ़ो_saved_sp(tsk)	\
	((अचिन्हित दीर्घ)(task_thपढ़ो_info(tsk)->cpu_context.sp))

#अगर_अघोषित CONFIG_THUMB2_KERNEL
#घोषणा thपढ़ो_saved_fp(tsk)	\
	((अचिन्हित दीर्घ)(task_thपढ़ो_info(tsk)->cpu_context.fp))
#अन्यथा
#घोषणा thपढ़ो_saved_fp(tsk)	\
	((अचिन्हित दीर्घ)(task_thपढ़ो_info(tsk)->cpu_context.r7))
#पूर्ण_अगर

बाह्य व्योम crunch_task_disable(काष्ठा thपढ़ो_info *);
बाह्य व्योम crunch_task_copy(काष्ठा thपढ़ो_info *, व्योम *);
बाह्य व्योम crunch_task_restore(काष्ठा thपढ़ो_info *, व्योम *);
बाह्य व्योम crunch_task_release(काष्ठा thपढ़ो_info *);

बाह्य व्योम iwmmxt_task_disable(काष्ठा thपढ़ो_info *);
बाह्य व्योम iwmmxt_task_copy(काष्ठा thपढ़ो_info *, व्योम *);
बाह्य व्योम iwmmxt_task_restore(काष्ठा thपढ़ो_info *, व्योम *);
बाह्य व्योम iwmmxt_task_release(काष्ठा thपढ़ो_info *);
बाह्य व्योम iwmmxt_task_चयन(काष्ठा thपढ़ो_info *);

बाह्य व्योम vfp_sync_hwstate(काष्ठा thपढ़ो_info *);
बाह्य व्योम vfp_flush_hwstate(काष्ठा thपढ़ो_info *);

काष्ठा user_vfp;
काष्ठा user_vfp_exc;

बाह्य पूर्णांक vfp_preserve_user_clear_hwstate(काष्ठा user_vfp *,
					   काष्ठा user_vfp_exc *);
बाह्य पूर्णांक vfp_restore_user_hwstate(काष्ठा user_vfp *,
				    काष्ठा user_vfp_exc *);
#पूर्ण_अगर

/*
 * thपढ़ो inक्रमmation flags:
 *  TIF_USEDFPU		- FPU was used by this task this quantum (SMP)
 *  TIF_POLLING_NRFLAG	- true अगर poll_idle() is polling TIF_NEED_RESCHED
 *
 * Any bit in the range of 0..15 will cause करो_work_pending() to be invoked.
 */
#घोषणा TIF_SIGPENDING		0	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	1	/* rescheduling necessary */
#घोषणा TIF_NOTIFY_RESUME	2	/* callback beक्रमe वापसing to user */
#घोषणा TIF_UPROBE		3	/* अवरोधpoपूर्णांकed or singlestepping */
#घोषणा TIF_SYSCALL_TRACE	4	/* syscall trace active */
#घोषणा TIF_SYSCALL_AUDIT	5	/* syscall auditing active */
#घोषणा TIF_SYSCALL_TRACEPOINT	6	/* syscall tracepoपूर्णांक instrumentation */
#घोषणा TIF_SECCOMP		7	/* seccomp syscall filtering active */
#घोषणा TIF_NOTIFY_SIGNAL	8	/* संकेत notअगरications exist */

#घोषणा TIF_USING_IWMMXT	17
#घोषणा TIF_MEMDIE		18	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_RESTORE_SIGMASK	20

#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_UPROBE		(1 << TIF_UPROBE)
#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_SYSCALL_AUDIT	(1 << TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1 << TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_SECCOMP		(1 << TIF_SECCOMP)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_USING_IWMMXT	(1 << TIF_USING_IWMMXT)

/* Checks क्रम any syscall work in entry-common.S */
#घोषणा _TIF_SYSCALL_WORK (_TIF_SYSCALL_TRACE | _TIF_SYSCALL_AUDIT | \
			   _TIF_SYSCALL_TRACEPOINT | _TIF_SECCOMP)

/*
 * Change these and you अवरोध ASM code in entry-common.S
 */
#घोषणा _TIF_WORK_MASK		(_TIF_NEED_RESCHED | _TIF_SIGPENDING | \
				 _TIF_NOTIFY_RESUME | _TIF_UPROBE | \
				 _TIF_NOTIFY_SIGNAL)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_ARM_THREAD_INFO_H */
