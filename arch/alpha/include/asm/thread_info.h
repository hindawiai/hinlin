<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_THREAD_INFO_H
#घोषणा _ALPHA_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/sysinfo.h>
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
काष्ठा thपढ़ो_info अणु
	काष्ठा pcb_काष्ठा	pcb;		/* palcode state */

	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित पूर्णांक		flags;		/* low level flags */
	अचिन्हित पूर्णांक		ieee_state;	/* see fpu.h */

	mm_segment_t		addr_limit;	/* thपढ़ो address space */
	अचिन्हित		cpu;		/* current CPU */
	पूर्णांक			preempt_count; /* 0 => preemptable, <0 => BUG */
	अचिन्हित पूर्णांक		status;		/* thपढ़ो-synchronous flags */

	पूर्णांक bpt_nsaved;
	अचिन्हित दीर्घ bpt_addr[2];		/* अवरोधpoपूर्णांक handling  */
	अचिन्हित पूर्णांक bpt_insn[2];
पूर्ण;

/*
 * Macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure.
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.addr_limit	= KERNEL_DS,		\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
पूर्ण

/* How to get the thपढ़ो inक्रमmation काष्ठा from C.  */
रेजिस्टर काष्ठा thपढ़ो_info *__current_thपढ़ो_info __यंत्र__("$8");
#घोषणा current_thपढ़ो_info()  __current_thपढ़ो_info

#पूर्ण_अगर /* __ASSEMBLY__ */

/* Thपढ़ो inक्रमmation allocation.  */
#घोषणा THREAD_SIZE_ORDER 1
#घोषणा THREAD_SIZE (2*PAGE_SIZE)

/*
 * Thपढ़ो inक्रमmation flags:
 * - these are process state flags and used from assembly
 * - pending work-to-be-करोne flags come first and must be asचिन्हित to be
 *   within bits 0 to 7 to fit in and immediate opeअक्रम.
 *
 * TIF_SYSCALL_TRACE is known to be 0 via blbs.
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME	1	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_SYSCALL_AUDIT	4	/* syscall audit active */
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरications exist */
#घोषणा TIF_DIE_IF_KERNEL	9	/* dik recursion lock */
#घोषणा TIF_MEMDIE		13	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_POLLING_NRFLAG	14	/* idle is polling क्रम TIF_NEED_RESCHED */

#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_SYSCALL_AUDIT	(1<<TIF_SYSCALL_AUDIT)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_POLLING_NRFLAG	(1<<TIF_POLLING_NRFLAG)

/* Work to करो on पूर्णांकerrupt/exception वापस.  */
#घोषणा _TIF_WORK_MASK		(_TIF_SIGPENDING | _TIF_NEED_RESCHED | \
				 _TIF_NOTIFY_RESUME)

/* Work to करो on any वापस to userspace.  */
#घोषणा _TIF_ALLWORK_MASK	(_TIF_WORK_MASK		\
				 | _TIF_SYSCALL_TRACE)

#घोषणा TS_UAC_NOPRINT		0x0001	/* ! Preserve the following three */
#घोषणा TS_UAC_NOFIX		0x0002	/* ! flags as they match          */
#घोषणा TS_UAC_SIGBUS		0x0004	/* ! userspace part of 'osf_sysinfo' */

#घोषणा SET_UNALIGN_CTL(task,value)	(अणु				\
	__u32 status = task_thपढ़ो_info(task)->status & ~UAC_BITMASK;	\
	अगर (value & PR_UNALIGN_NOPRINT)					\
		status |= TS_UAC_NOPRINT;				\
	अगर (value & PR_UNALIGN_SIGBUS)					\
		status |= TS_UAC_SIGBUS;				\
	अगर (value & 4)	/* alpha-specअगरic */				\
		status |= TS_UAC_NOFIX;					\
	task_thपढ़ो_info(task)->status = status;			\
	0; पूर्ण)

#घोषणा GET_UNALIGN_CTL(task,value)	(अणु				\
	__u32 status = task_thपढ़ो_info(task)->status & ~UAC_BITMASK;	\
	__u32 res = 0;							\
	अगर (status & TS_UAC_NOPRINT)					\
		res |= PR_UNALIGN_NOPRINT;				\
	अगर (status & TS_UAC_SIGBUS)					\
		res |= PR_UNALIGN_SIGBUS;				\
	अगर (status & TS_UAC_NOFIX)					\
		res |= 4;						\
	put_user(res, (पूर्णांक __user *)(value));				\
	पूर्ण)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ALPHA_THREAD_INFO_H */
