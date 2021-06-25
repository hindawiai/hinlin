<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Vineetg: Oct 2009
 *  No need क्रम ARC specअगरic thपढ़ो_info allocator (kदो_स्मृति/मुक्त). This is
 *  anyways one page allocation, thus slab alloc can be लघु-circuited and
 *  the generic version (get_मुक्त_page) would be loads better.
 *
 * Sameer Dhavale: Codito Technologies 2004
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_16KSTACKS
#घोषणा THREAD_SIZE_ORDER 1
#अन्यथा
#घोषणा THREAD_SIZE_ORDER 0
#पूर्ण_अगर

#घोषणा THREAD_SIZE     (PAGE_SIZE << THREAD_SIZE_ORDER)
#घोषणा THREAD_SHIFT	(PAGE_SHIFT << THREAD_SIZE_ORDER)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/segment.h>

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 * - अगर the contents of this काष्ठाure are changed, the assembly स्थिरants
 *   must also be changed
 */
काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ flags;		/* low level flags */
	पूर्णांक preempt_count;		/* 0 => preemptable, <0 => BUG */
	काष्ठा task_काष्ठा *task;	/* मुख्य task काष्ठाure */
	mm_segment_t addr_limit;	/* thपढ़ो address space */
	__u32 cpu;			/* current CPU */
	अचिन्हित दीर्घ thr_ptr;		/* TLS ptr */
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 *
 * preempt_count needs to be 1 initially, until the scheduler is functional.
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task       = &tsk,			\
	.flags      = 0,			\
	.cpu        = 0,			\
	.preempt_count  = INIT_PREEMPT_COUNT,	\
	.addr_limit = KERNEL_DS,		\
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	रेजिस्टर अचिन्हित दीर्घ sp यंत्र("sp");
	वापस (काष्ठा thपढ़ो_info *)(sp & ~(THREAD_SIZE - 1));
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files may need to
 *   access
 * - pending work-to-be-करोne flags are in LSW
 * - other flags in MSW
 */
#घोषणा TIF_RESTORE_SIGMASK	0	/* restore sig mask in करो_संकेत() */
#घोषणा TIF_NOTIFY_RESUME	1	/* resumption notअगरication requested */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_SYSCALL_AUDIT	4	/* syscall auditing active */
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरications exist */
#घोषणा TIF_SYSCALL_TRACE	15	/* syscall trace active */

/* true अगर poll_idle() is polling TIF_NEED_RESCHED */
#घोषणा TIF_MEMDIE		16

#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_SYSCALL_AUDIT	(1<<TIF_SYSCALL_AUDIT)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_MEMDIE		(1<<TIF_MEMDIE)

/* work to करो on पूर्णांकerrupt/exception वापस */
#घोषणा _TIF_WORK_MASK		(_TIF_NEED_RESCHED | _TIF_SIGPENDING | \
				 _TIF_NOTIFY_RESUME | _TIF_NOTIFY_SIGNAL)

/*
 * _TIF_ALLWORK_MASK includes SYSCALL_TRACE, but we करोn't need it.
 * SYSCALL_TRACE is anyway seperately/unconditionally tested right after a
 * syscall, so all that reamins to be tested is _TIF_WORK_MASK
 */

#पूर्ण_अगर /* _ASM_THREAD_INFO_H */
