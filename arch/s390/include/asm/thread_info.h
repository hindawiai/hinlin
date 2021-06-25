<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 2002, 2006
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#समावेश <linux/bits.h>

/*
 * General size of kernel stacks
 */
#अगर_घोषित CONFIG_KASAN
#घोषणा THREAD_SIZE_ORDER 4
#अन्यथा
#घोषणा THREAD_SIZE_ORDER 2
#पूर्ण_अगर
#घोषणा BOOT_STACK_SIZE (PAGE_SIZE << 2)
#घोषणा THREAD_SIZE (PAGE_SIZE << THREAD_SIZE_ORDER)

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/page.h>

#घोषणा STACK_INIT_OFFSET \
	(THREAD_SIZE - STACK_FRAME_OVERHEAD - माप(काष्ठा pt_regs))

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 * - अगर the contents of this काष्ठाure are changed, the assembly स्थिरants must also be changed
 */
काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ		flags;		/* low level flags */
	अचिन्हित दीर्घ		syscall_work;	/* SYSCALL_WORK_ flags */
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.flags		= 0,			\
पूर्ण

काष्ठा task_काष्ठा;

व्योम arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk);
पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src);

व्योम arch_setup_new_exec(व्योम);
#घोषणा arch_setup_new_exec arch_setup_new_exec

#पूर्ण_अगर

/*
 * thपढ़ो inक्रमmation flags bit numbers
 */
/* _TIF_WORK bits */
#घोषणा TIF_NOTIFY_RESUME	0	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_UPROBE		3	/* अवरोधpoपूर्णांकed or single-stepping */
#घोषणा TIF_GUARDED_STORAGE	4	/* load guarded storage control block */
#घोषणा TIF_PATCH_PENDING	5	/* pending live patching update */
#घोषणा TIF_PGSTE		6	/* New mm's will use 4K page tables */
#घोषणा TIF_NOTIFY_SIGNAL	7	/* संकेत notअगरications exist */
#घोषणा TIF_ISOLATE_BP		8	/* Run process with isolated BP */
#घोषणा TIF_ISOLATE_BP_GUEST	9	/* Run KVM guests with isolated BP */
#घोषणा TIF_PER_TRAP		10	/* Need to handle PER trap on निकास to usermode */

#घोषणा TIF_31BIT		16	/* 32bit process */
#घोषणा TIF_MEMDIE		17	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_RESTORE_SIGMASK	18	/* restore संकेत mask in करो_संकेत() */
#घोषणा TIF_SINGLE_STEP		19	/* This task is single stepped */
#घोषणा TIF_BLOCK_STEP		20	/* This task is block stepped */
#घोषणा TIF_UPROBE_SINGLESTEP	21	/* This task is uprobe single stepped */

/* _TIF_TRACE bits */
#घोषणा TIF_SYSCALL_TRACE	24	/* syscall trace active */
#घोषणा TIF_SYSCALL_AUDIT	25	/* syscall auditing active */
#घोषणा TIF_SECCOMP		26	/* secure computing */
#घोषणा TIF_SYSCALL_TRACEPOINT	27	/* syscall tracepoपूर्णांक instrumentation */

#घोषणा _TIF_NOTIFY_RESUME	BIT(TIF_NOTIFY_RESUME)
#घोषणा _TIF_NOTIFY_SIGNAL	BIT(TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_SIGPENDING		BIT(TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	BIT(TIF_NEED_RESCHED)
#घोषणा _TIF_UPROBE		BIT(TIF_UPROBE)
#घोषणा _TIF_GUARDED_STORAGE	BIT(TIF_GUARDED_STORAGE)
#घोषणा _TIF_PATCH_PENDING	BIT(TIF_PATCH_PENDING)
#घोषणा _TIF_ISOLATE_BP		BIT(TIF_ISOLATE_BP)
#घोषणा _TIF_ISOLATE_BP_GUEST	BIT(TIF_ISOLATE_BP_GUEST)
#घोषणा _TIF_PER_TRAP		BIT(TIF_PER_TRAP)

#घोषणा _TIF_31BIT		BIT(TIF_31BIT)
#घोषणा _TIF_SINGLE_STEP	BIT(TIF_SINGLE_STEP)

#घोषणा _TIF_SYSCALL_TRACE	BIT(TIF_SYSCALL_TRACE)
#घोषणा _TIF_SYSCALL_AUDIT	BIT(TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SECCOMP		BIT(TIF_SECCOMP)
#घोषणा _TIF_SYSCALL_TRACEPOINT	BIT(TIF_SYSCALL_TRACEPOINT)

#पूर्ण_अगर /* _ASM_THREAD_INFO_H */
