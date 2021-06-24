<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* thपढ़ो_info.h: PowerPC low-level thपढ़ो inक्रमmation
 * adapted from the i386 version by Paul Mackerras
 *
 * Copyright (C) 2002  David Howells (dhowells@redhat.com)
 * - Incorporating suggestions made by Linus Torvalds and Dave Miller
 */

#अगर_अघोषित _ASM_POWERPC_THREAD_INFO_H
#घोषणा _ASM_POWERPC_THREAD_INFO_H

#समावेश <यंत्र/यंत्र-स्थिर.h>
#समावेश <यंत्र/page.h>

#अगर_घोषित __KERNEL__

#अगर defined(CONFIG_VMAP_STACK) && CONFIG_THREAD_SHIFT < PAGE_SHIFT
#घोषणा THREAD_SHIFT		PAGE_SHIFT
#अन्यथा
#घोषणा THREAD_SHIFT		CONFIG_THREAD_SHIFT
#पूर्ण_अगर

#घोषणा THREAD_SIZE		(1 << THREAD_SHIFT)

/*
 * By aligning VMAP'd stacks to 2 * THREAD_SIZE, we can detect overflow by
 * checking sp & (1 << THREAD_SHIFT), which we can करो cheaply in the entry
 * assembly.
 */
#अगर_घोषित CONFIG_VMAP_STACK
#घोषणा THREAD_ALIGN_SHIFT	(THREAD_SHIFT + 1)
#अन्यथा
#घोषणा THREAD_ALIGN_SHIFT	THREAD_SHIFT
#पूर्ण_अगर

#घोषणा THREAD_ALIGN		(1 << THREAD_ALIGN_SHIFT)

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/cache.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/accounting.h>

#घोषणा SLB_PRELOAD_NR	16U
/*
 * low level task data.
 */
काष्ठा thपढ़ो_info अणु
	पूर्णांक		preempt_count;		/* 0 => preemptable,
						   <0 => BUG */
	अचिन्हित दीर्घ	local_flags;		/* निजी flags क्रम thपढ़ो */
#अगर_घोषित CONFIG_LIVEPATCH
	अचिन्हित दीर्घ *livepatch_sp;
#पूर्ण_अगर
#अगर defined(CONFIG_VIRT_CPU_ACCOUNTING_NATIVE) && defined(CONFIG_PPC32)
	काष्ठा cpu_accounting_data accounting;
#पूर्ण_अगर
	अचिन्हित अक्षर slb_preload_nr;
	अचिन्हित अक्षर slb_preload_tail;
	u32 slb_preload_esid[SLB_PRELOAD_NR];

	/* low level flags - has atomic operations करोne on it */
	अचिन्हित दीर्घ	flags ____cacheline_aligned_in_smp;
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.preempt_count = INIT_PREEMPT_COUNT,	\
	.flags =	0,			\
पूर्ण

#घोषणा THREAD_SIZE_ORDER	(THREAD_SHIFT - PAGE_SHIFT)

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
बाह्य पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src);

व्योम arch_setup_new_exec(व्योम);
#घोषणा arch_setup_new_exec arch_setup_new_exec

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flag bit numbers
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_NOTIFY_SIGNAL	3	/* संकेत notअगरications exist */
#घोषणा TIF_SYSCALL_EMU		4	/* syscall emulation active */
#घोषणा TIF_RESTORE_TM		5	/* need to restore TM FP/VEC/VSX */
#घोषणा TIF_PATCH_PENDING	6	/* pending live patching update */
#घोषणा TIF_SYSCALL_AUDIT	7	/* syscall auditing active */
#घोषणा TIF_SINGLESTEP		8	/* singlestepping active */
#घोषणा TIF_SECCOMP		10	/* secure computing */
#घोषणा TIF_RESTOREALL		11	/* Restore all regs (implies NOERROR) */
#घोषणा TIF_NOERROR		12	/* Force successful syscall वापस */
#घोषणा TIF_NOTIFY_RESUME	13	/* callback beक्रमe वापसing to user */
#घोषणा TIF_UPROBE		14	/* अवरोधpoपूर्णांकed or single-stepping */
#घोषणा TIF_SYSCALL_TRACEPOINT	15	/* syscall tracepoपूर्णांक instrumentation */
#घोषणा TIF_EMULATE_STACK_STORE	16	/* Is an inकाष्ठाion emulation
						क्रम stack store? */
#घोषणा TIF_MEMDIE		17	/* is terminating due to OOM समाप्तer */
#अगर defined(CONFIG_PPC64)
#घोषणा TIF_ELF2ABI		18	/* function descriptors must die! */
#पूर्ण_अगर
#घोषणा TIF_POLLING_NRFLAG	19	/* true अगर poll_idle() is polling TIF_NEED_RESCHED */
#घोषणा TIF_32BIT		20	/* 32 bit binary */

/* as above, but as bit values */
#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_POLLING_NRFLAG	(1<<TIF_POLLING_NRFLAG)
#घोषणा _TIF_32BIT		(1<<TIF_32BIT)
#घोषणा _TIF_RESTORE_TM		(1<<TIF_RESTORE_TM)
#घोषणा _TIF_PATCH_PENDING	(1<<TIF_PATCH_PENDING)
#घोषणा _TIF_SYSCALL_AUDIT	(1<<TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SINGLESTEP		(1<<TIF_SINGLESTEP)
#घोषणा _TIF_SECCOMP		(1<<TIF_SECCOMP)
#घोषणा _TIF_RESTOREALL		(1<<TIF_RESTOREALL)
#घोषणा _TIF_NOERROR		(1<<TIF_NOERROR)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_UPROBE		(1<<TIF_UPROBE)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1<<TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_EMULATE_STACK_STORE	(1<<TIF_EMULATE_STACK_STORE)
#घोषणा _TIF_SYSCALL_EMU	(1<<TIF_SYSCALL_EMU)
#घोषणा _TIF_SYSCALL_DOTRACE	(_TIF_SYSCALL_TRACE | _TIF_SYSCALL_AUDIT | \
				 _TIF_SECCOMP | _TIF_SYSCALL_TRACEPOINT | \
				 _TIF_SYSCALL_EMU)

#घोषणा _TIF_USER_WORK_MASK	(_TIF_SIGPENDING | _TIF_NEED_RESCHED | \
				 _TIF_NOTIFY_RESUME | _TIF_UPROBE | \
				 _TIF_RESTORE_TM | _TIF_PATCH_PENDING | \
				 _TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_PERSYSCALL_MASK	(_TIF_RESTOREALL|_TIF_NOERROR)

/* Bits in local_flags */
/* Don't move TLF_NAPPING without adjusting the code in entry_32.S */
#घोषणा TLF_NAPPING		0	/* idle thपढ़ो enabled NAP mode */
#घोषणा TLF_SLEEPING		1	/* suspend code enabled SLEEP mode */
#घोषणा TLF_LAZY_MMU		3	/* tlb_batch is active */
#घोषणा TLF_RUNLATCH		4	/* Is the runlatch enabled? */

#घोषणा _TLF_NAPPING		(1 << TLF_NAPPING)
#घोषणा _TLF_SLEEPING		(1 << TLF_SLEEPING)
#घोषणा _TLF_LAZY_MMU		(1 << TLF_LAZY_MMU)
#घोषणा _TLF_RUNLATCH		(1 << TLF_RUNLATCH)

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम clear_thपढ़ो_local_flags(अचिन्हित पूर्णांक flags)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	ti->local_flags &= ~flags;
पूर्ण

अटल अंतरभूत bool test_thपढ़ो_local_flags(अचिन्हित पूर्णांक flags)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	वापस (ti->local_flags & flags) != 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#घोषणा is_32bit_task()	(test_thपढ़ो_flag(TIF_32BIT))
#अन्यथा
#घोषणा is_32bit_task()	(IS_ENABLED(CONFIG_PPC32))
#पूर्ण_अगर

#अगर defined(CONFIG_PPC64)
#घोषणा is_elf2_task() (test_thपढ़ो_flag(TIF_ELF2ABI))
#अन्यथा
#घोषणा is_elf2_task() (0)
#पूर्ण_अगर

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_POWERPC_THREAD_INFO_H */
