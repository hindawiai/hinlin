<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASM_NDS32_THREAD_INFO_H
#घोषणा __ASM_NDS32_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#घोषणा THREAD_SIZE_ORDER 	(1)
#घोषणा THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)

#अगर_अघोषित __ASSEMBLY__

काष्ठा task_काष्ठा;

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/types.h>

प्रकार अचिन्हित दीर्घ mm_segment_t;

/*
 * low level task data that entry.S needs immediate access to.
 * __चयन_to() assumes cpu_context follows immediately after cpu_करोमुख्य.
 */
काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ flags;	/* low level flags */
	__s32 preempt_count;	/* 0 => preemptable, <0 => bug */
	mm_segment_t addr_limit;	/* address limit */
पूर्ण;
#घोषणा INIT_THREAD_INFO(tsk)						\
अणु									\
	.preempt_count	= INIT_PREEMPT_COUNT,				\
	.addr_limit	= KERNEL_DS,					\
पूर्ण
#घोषणा thपढ़ो_saved_pc(tsk) ((अचिन्हित दीर्घ)(tsk->thपढ़ो.cpu_context.pc))
#घोषणा thपढ़ो_saved_fp(tsk) ((अचिन्हित दीर्घ)(tsk->thपढ़ो.cpu_context.fp))
#पूर्ण_अगर

/*
 * thपढ़ो inक्रमmation flags:
 *  TIF_SYSCALL_TRACE	- syscall trace active
 *  TIF_SIGPENDING	- संकेत pending
 *  TIF_NEED_RESCHED	- rescheduling necessary
 *  TIF_NOTIFY_RESUME	- callback beक्रमe वापसing to user
 *  TIF_POLLING_NRFLAG	- true अगर poll_idle() is polling TIF_NEED_RESCHED
 */
#घोषणा TIF_SIGPENDING		1
#घोषणा TIF_NEED_RESCHED	2
#घोषणा TIF_SINGLESTEP		3
#घोषणा TIF_NOTIFY_RESUME	4	/* callback beक्रमe वापसing to user */
#घोषणा TIF_NOTIFY_SIGNAL	5	/* संकेत notअगरications exist */
#घोषणा TIF_SYSCALL_TRACE	8
#घोषणा TIF_POLLING_NRFLAG	17
#घोषणा TIF_MEMDIE		18
#घोषणा TIF_FREEZE		19
#घोषणा TIF_RESTORE_SIGMASK	20

#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)
#घोषणा _TIF_FREEZE		(1 << TIF_FREEZE)
#घोषणा _TIF_RESTORE_SIGMASK	(1 << TIF_RESTORE_SIGMASK)

/*
 * Change these and you अवरोध ASM code in entry-common.S
 */
#घोषणा _TIF_WORK_MASK		0x000000ff
#घोषणा _TIF_WORK_SYSCALL_ENTRY (_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP)
#घोषणा _TIF_WORK_SYSCALL_LEAVE (_TIF_SYSCALL_TRACE | _TIF_SINGLESTEP)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_NDS32_THREAD_INFO_H */
