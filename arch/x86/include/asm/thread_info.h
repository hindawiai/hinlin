<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* thपढ़ो_info.h: low-level thपढ़ो inक्रमmation
 *
 * Copyright (C) 2002  David Howells (dhowells@redhat.com)
 * - Incorporating suggestions made by Linus Torvalds and Dave Miller
 */

#अगर_अघोषित _ASM_X86_THREAD_INFO_H
#घोषणा _ASM_X86_THREAD_INFO_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/types.h>

/*
 * TOP_OF_KERNEL_STACK_PADDING is a number of unused bytes that we
 * reserve at the top of the kernel stack.  We करो it because of a nasty
 * 32-bit corner हाल.  On x86_32, the hardware stack frame is
 * variable-length.  Except क्रम vm86 mode, काष्ठा pt_regs assumes a
 * maximum-length frame.  If we enter from CPL 0, the top 8 bytes of
 * pt_regs करोn't actually exist.  Ordinarily this doesn't matter, but it
 * करोes in at least one हाल:
 *
 * If we take an NMI early enough in SYSENTER, then we can end up with
 * pt_regs that extends above sp0.  On the way out, in the espfix code,
 * we can पढ़ो the saved SS value, but that value will be above sp0.
 * Without this offset, that can result in a page fault.  (We are
 * careful that, in this हाल, the value we पढ़ो करोesn't matter.)
 *
 * In vm86 mode, the hardware frame is much दीर्घer still, so add 16
 * bytes to make room क्रम the real-mode segments.
 *
 * x86_64 has a fixed-length stack frame.
 */
#अगर_घोषित CONFIG_X86_32
# अगरdef CONFIG_VM86
#  define TOP_OF_KERNEL_STACK_PADDING 16
# अन्यथा
#  define TOP_OF_KERNEL_STACK_PADDING 8
# endअगर
#अन्यथा
# define TOP_OF_KERNEL_STACK_PADDING 0
#पूर्ण_अगर

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 */
#अगर_अघोषित __ASSEMBLY__
काष्ठा task_काष्ठा;
#समावेश <यंत्र/cpufeature.h>
#समावेश <linux/atomic.h>

काष्ठा thपढ़ो_info अणु
	अचिन्हित दीर्घ		flags;		/* low level flags */
	अचिन्हित दीर्घ		syscall_work;	/* SYSCALL_WORK_ flags */
	u32			status;		/* thपढ़ो synchronous flags */
पूर्ण;

#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.flags		= 0,			\
पूर्ण

#अन्यथा /* !__ASSEMBLY__ */

#समावेश <यंत्र/यंत्र-offsets.h>

#पूर्ण_अगर

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files
 *   may need to access
 */
#घोषणा TIF_NOTIFY_RESUME	1	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_SINGLESTEP		4	/* reenable singlestep on user वापस*/
#घोषणा TIF_SSBD		5	/* Speculative store bypass disable */
#घोषणा TIF_SPEC_IB		9	/* Indirect branch speculation mitigation */
#घोषणा TIF_SPEC_FORCE_UPDATE	10	/* Force speculation MSR update in context चयन */
#घोषणा TIF_USER_RETURN_NOTIFY	11	/* notअगरy kernel of userspace वापस */
#घोषणा TIF_UPROBE		12	/* अवरोधpoपूर्णांकed or singlestepping */
#घोषणा TIF_PATCH_PENDING	13	/* pending live patching update */
#घोषणा TIF_NEED_FPU_LOAD	14	/* load FPU on वापस to userspace */
#घोषणा TIF_NOCPUID		15	/* CPUID is not accessible in userland */
#घोषणा TIF_NOTSC		16	/* TSC is not accessible in userland */
#घोषणा TIF_NOTIFY_SIGNAL	17	/* संकेत notअगरications exist */
#घोषणा TIF_SLD			18	/* Restore split lock detection on context चयन */
#घोषणा TIF_MEMDIE		20	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_POLLING_NRFLAG	21	/* idle is polling क्रम TIF_NEED_RESCHED */
#घोषणा TIF_IO_BITMAP		22	/* uses I/O biपंचांगap */
#घोषणा TIF_FORCED_TF		24	/* true अगर TF in eflags artअगरicially */
#घोषणा TIF_BLOCKSTEP		25	/* set when we want DEBUGCTLMSR_BTF */
#घोषणा TIF_LAZY_MMU_UPDATES	27	/* task is updating the mmu lazily */
#घोषणा TIF_ADDR32		29	/* 32-bit address space on 64 bits */

#घोषणा _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#घोषणा _TIF_SINGLESTEP		(1 << TIF_SINGLESTEP)
#घोषणा _TIF_SSBD		(1 << TIF_SSBD)
#घोषणा _TIF_SPEC_IB		(1 << TIF_SPEC_IB)
#घोषणा _TIF_SPEC_FORCE_UPDATE	(1 << TIF_SPEC_FORCE_UPDATE)
#घोषणा _TIF_USER_RETURN_NOTIFY	(1 << TIF_USER_RETURN_NOTIFY)
#घोषणा _TIF_UPROBE		(1 << TIF_UPROBE)
#घोषणा _TIF_PATCH_PENDING	(1 << TIF_PATCH_PENDING)
#घोषणा _TIF_NEED_FPU_LOAD	(1 << TIF_NEED_FPU_LOAD)
#घोषणा _TIF_NOCPUID		(1 << TIF_NOCPUID)
#घोषणा _TIF_NOTSC		(1 << TIF_NOTSC)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_SLD		(1 << TIF_SLD)
#घोषणा _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)
#घोषणा _TIF_IO_BITMAP		(1 << TIF_IO_BITMAP)
#घोषणा _TIF_FORCED_TF		(1 << TIF_FORCED_TF)
#घोषणा _TIF_BLOCKSTEP		(1 << TIF_BLOCKSTEP)
#घोषणा _TIF_LAZY_MMU_UPDATES	(1 << TIF_LAZY_MMU_UPDATES)
#घोषणा _TIF_ADDR32		(1 << TIF_ADDR32)

/* flags to check in __चयन_to() */
#घोषणा _TIF_WORK_CTXSW_BASE					\
	(_TIF_NOCPUID | _TIF_NOTSC | _TIF_BLOCKSTEP |		\
	 _TIF_SSBD | _TIF_SPEC_FORCE_UPDATE | _TIF_SLD)

/*
 * Aव्योम calls to __चयन_to_xtra() on UP as STIBP is not evaluated.
 */
#अगर_घोषित CONFIG_SMP
# define _TIF_WORK_CTXSW	(_TIF_WORK_CTXSW_BASE | _TIF_SPEC_IB)
#अन्यथा
# define _TIF_WORK_CTXSW	(_TIF_WORK_CTXSW_BASE)
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
# define _TIF_WORK_CTXSW_PREV	(_TIF_WORK_CTXSW| _TIF_USER_RETURN_NOTIFY | \
				 _TIF_IO_BITMAP)
#अन्यथा
# define _TIF_WORK_CTXSW_PREV	(_TIF_WORK_CTXSW| _TIF_USER_RETURN_NOTIFY)
#पूर्ण_अगर

#घोषणा _TIF_WORK_CTXSW_NEXT	(_TIF_WORK_CTXSW)

#घोषणा STACK_WARN		(THREAD_SIZE/8)

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 *
 * preempt_count needs to be 1 initially, until the scheduler is functional.
 */
#अगर_अघोषित __ASSEMBLY__

/*
 * Walks up the stack frames to make sure that the specअगरied object is
 * entirely contained by a single stack frame.
 *
 * Returns:
 *	GOOD_FRAME	अगर within a frame
 *	BAD_STACK	अगर placed across a frame boundary (or outside stack)
 *	NOT_STACK	unable to determine (no frame poपूर्णांकers, etc)
 */
अटल अंतरभूत पूर्णांक arch_within_stack_frames(स्थिर व्योम * स्थिर stack,
					   स्थिर व्योम * स्थिर stackend,
					   स्थिर व्योम *obj, अचिन्हित दीर्घ len)
अणु
#अगर defined(CONFIG_FRAME_POINTER)
	स्थिर व्योम *frame = शून्य;
	स्थिर व्योम *oldframe;

	oldframe = __builtin_frame_address(1);
	अगर (oldframe)
		frame = __builtin_frame_address(2);
	/*
	 * low ----------------------------------------------> high
	 * [saved bp][saved ip][args][local vars][saved bp][saved ip]
	 *                     ^----------------^
	 *               allow copies only within here
	 */
	जबतक (stack <= frame && frame < stackend) अणु
		/*
		 * If obj + len extends past the last frame, this
		 * check won't pass and the next frame will be 0,
		 * causing us to bail out and correctly report
		 * the copy as invalid.
		 */
		अगर (obj + len <= frame)
			वापस obj >= oldframe + 2 * माप(व्योम *) ?
				GOOD_FRAME : BAD_STACK;
		oldframe = frame;
		frame = *(स्थिर व्योम * स्थिर *)frame;
	पूर्ण
	वापस BAD_STACK;
#अन्यथा
	वापस NOT_STACK;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर  /* !__ASSEMBLY__ */

/*
 * Thपढ़ो-synchronous status.
 *
 * This is dअगरferent from the flags in that nobody अन्यथा
 * ever touches our thपढ़ो-synchronous status, so we करोn't
 * have to worry about atomic accesses.
 */
#घोषणा TS_COMPAT		0x0002	/* 32bit syscall active (64BIT)*/

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_COMPAT
#घोषणा TS_I386_REGS_POKED	0x0004	/* regs poked by 32-bit ptracer */

#घोषणा arch_set_restart_data(restart)	\
	करो अणु restart->arch_data = current_thपढ़ो_info()->status; पूर्ण जबतक (0)

#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
#घोषणा in_ia32_syscall() true
#अन्यथा
#घोषणा in_ia32_syscall() (IS_ENABLED(CONFIG_IA32_EMULATION) && \
			   current_thपढ़ो_info()->status & TS_COMPAT)
#पूर्ण_अगर

बाह्य व्योम arch_task_cache_init(व्योम);
बाह्य पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src);
बाह्य व्योम arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम arch_setup_new_exec(व्योम);
#घोषणा arch_setup_new_exec arch_setup_new_exec
#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_THREAD_INFO_H */
