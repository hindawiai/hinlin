<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_THREAD_INFO_H
#घोषणा _ASM_M68K_THREAD_INFO_H

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/segment.h>

/*
 * On machines with 4k pages we शेष to an 8k thपढ़ो size, though we
 * allow a 4k with config option. Any other machine page size then
 * the thपढ़ो size must match the page size (which is 8k and larger here).
 */
#अगर PAGE_SHIFT < 13
#अगर_घोषित CONFIG_4KSTACKS
#घोषणा THREAD_SIZE	4096
#अन्यथा
#घोषणा THREAD_SIZE	8192
#पूर्ण_अगर
#अन्यथा
#घोषणा THREAD_SIZE	PAGE_SIZE
#पूर्ण_अगर
#घोषणा THREAD_SIZE_ORDER	((THREAD_SIZE / PAGE_SIZE) - 1)

#अगर_अघोषित __ASSEMBLY__

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;
	mm_segment_t		addr_limit;	/* thपढ़ो address space */
	पूर्णांक			preempt_count;	/* 0 => preemptable, <0 => BUG */
	__u32			cpu;		/* should always be 0 on m68k */
	अचिन्हित दीर्घ		tp_value;	/* thपढ़ो poपूर्णांकer */
पूर्ण;
#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.addr_limit	= KERNEL_DS,		\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
पूर्ण

#अगर_अघोषित __ASSEMBLY__
/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti;
	__यंत्र__(
		"move.l %%sp, %0 \n\t"
		"and.l  %1, %0"
		: "=&d"(ti)
		: "di" (~(THREAD_SIZE-1))
		);
	वापस ti;
पूर्ण
#पूर्ण_अगर

/* entry.S relies on these definitions!
 * bits 0-7 are tested at every exception निकास
 * bits 8-15 are also tested at syscall निकास
 */
#घोषणा TIF_NOTIFY_SIGNAL	4
#घोषणा TIF_NOTIFY_RESUME	5	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SIGPENDING		6	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	7	/* rescheduling necessary */
#घोषणा TIF_DELAYED_TRACE	14	/* single step a syscall */
#घोषणा TIF_SYSCALL_TRACE	15	/* syscall trace active */
#घोषणा TIF_MEMDIE		16	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_RESTORE_SIGMASK	18	/* restore संकेत mask in करो_संकेत */

#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_DELAYED_TRACE	(1 << TIF_DELAYED_TRACE)
#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_MEMDIE		(1 << TIF_MEMDIE)
#घोषणा _TIF_RESTORE_SIGMASK	(1 << TIF_RESTORE_SIGMASK)

#पूर्ण_अगर	/* _ASM_M68K_THREAD_INFO_H */
