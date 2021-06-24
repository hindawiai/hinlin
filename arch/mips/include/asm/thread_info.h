<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* thपढ़ो_info.h: MIPS low-level thपढ़ो inक्रमmation
 *
 * Copyright (C) 2002  David Howells (dhowells@redhat.com)
 * - Incorporating suggestions made by Linus Torvalds and Dave Miller
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#अगर_घोषित __KERNEL__


#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/processor.h>

/*
 * low level task data that entry.S needs immediate access to
 * - this काष्ठा should fit entirely inside of one cache line
 * - this काष्ठा shares the supervisor stack pages
 * - अगर the contents of this काष्ठाure are changed, the assembly स्थिरants
 *   must also be changed
 */
काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;		/* low level flags */
	अचिन्हित दीर्घ		tp_value;	/* thपढ़ो poपूर्णांकer */
	__u32			cpu;		/* current CPU */
	पूर्णांक			preempt_count;	/* 0 => preemptable, <0 => BUG */
	काष्ठा pt_regs		*regs;
	दीर्घ			syscall;	/* syscall number */
पूर्ण;

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */
#घोषणा INIT_THREAD_INFO(tsk)			\
अणु						\
	.task		= &tsk,			\
	.flags		= _TIF_FIXADE,		\
	.cpu		= 0,			\
	.preempt_count	= INIT_PREEMPT_COUNT,	\
पूर्ण

/*
 * A poपूर्णांकer to the काष्ठा thपढ़ो_info क्रम the currently executing thपढ़ो is
 * held in रेजिस्टर $28/$gp.
 *
 * We declare __current_thपढ़ो_info as a global रेजिस्टर variable rather than a
 * local रेजिस्टर variable within current_thपढ़ो_info() because clang करोesn't
 * support explicit local रेजिस्टर variables.
 *
 * When building the VDSO we take care not to declare the global रेजिस्टर
 * variable because this causes GCC to not preserve the value of $28/$gp in
 * functions that change its value (which is common in the PIC VDSO when
 * accessing the GOT). Since the VDSO shouldn't be accessing
 * __current_thपढ़ो_info anyway we declare it बाह्य in order to cause a link
 * failure अगर it's referenced.
 */
#अगर_घोषित __VDSO__
बाह्य काष्ठा thपढ़ो_info *__current_thपढ़ो_info;
#अन्यथा
रेजिस्टर काष्ठा thपढ़ो_info *__current_thपढ़ो_info __यंत्र__("$28");
#पूर्ण_अगर

अटल अंतरभूत काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम)
अणु
	वापस __current_thपढ़ो_info;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

/* thपढ़ो inक्रमmation allocation */
#अगर defined(CONFIG_PAGE_SIZE_4KB) && defined(CONFIG_32BIT)
#घोषणा THREAD_SIZE_ORDER (1)
#पूर्ण_अगर
#अगर defined(CONFIG_PAGE_SIZE_4KB) && defined(CONFIG_64BIT)
#घोषणा THREAD_SIZE_ORDER (2)
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_8KB
#घोषणा THREAD_SIZE_ORDER (1)
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_16KB
#घोषणा THREAD_SIZE_ORDER (0)
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_32KB
#घोषणा THREAD_SIZE_ORDER (0)
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_64KB
#घोषणा THREAD_SIZE_ORDER (0)
#पूर्ण_अगर

#घोषणा THREAD_SIZE (PAGE_SIZE << THREAD_SIZE_ORDER)
#घोषणा THREAD_MASK (THREAD_SIZE - 1UL)

#घोषणा STACK_WARN	(THREAD_SIZE / 8)

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files may need to
 *   access
 * - pending work-to-be-करोne flags are in LSW
 * - other flags in MSW
 */
#घोषणा TIF_SIGPENDING		1	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	2	/* rescheduling necessary */
#घोषणा TIF_SYSCALL_AUDIT	3	/* syscall auditing active */
#घोषणा TIF_SECCOMP		4	/* secure computing */
#घोषणा TIF_NOTIFY_RESUME	5	/* callback beक्रमe वापसing to user */
#घोषणा TIF_UPROBE		6	/* अवरोधpoपूर्णांकed or singlestepping */
#घोषणा TIF_NOTIFY_SIGNAL	7	/* संकेत notअगरications exist */
#घोषणा TIF_RESTORE_SIGMASK	9	/* restore संकेत mask in करो_संकेत() */
#घोषणा TIF_USEDFPU		16	/* FPU was used by this task this quantum (SMP) */
#घोषणा TIF_MEMDIE		18	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_NOHZ		19	/* in adaptive nohz mode */
#घोषणा TIF_FIXADE		20	/* Fix address errors in software */
#घोषणा TIF_LOGADE		21	/* Log address errors to syslog */
#घोषणा TIF_32BIT_REGS		22	/* 32-bit general purpose रेजिस्टरs */
#घोषणा TIF_32BIT_ADDR		23	/* 32-bit address space (o32/n32) */
#घोषणा TIF_FPUBOUND		24	/* thपढ़ो bound to FPU-full CPU set */
#घोषणा TIF_LOAD_WATCH		25	/* If set, load watch रेजिस्टरs */
#घोषणा TIF_SYSCALL_TRACEPOINT	26	/* syscall tracepoपूर्णांक instrumentation */
#घोषणा TIF_32BIT_FPREGS	27	/* 32-bit भग्नing poपूर्णांक रेजिस्टरs */
#घोषणा TIF_HYBRID_FPREGS	28	/* 64b FP रेजिस्टरs, odd singles in bits 63:32 of even द्विगुनs */
#घोषणा TIF_USEDMSA		29	/* MSA has been used this quantum */
#घोषणा TIF_MSA_CTX_LIVE	30	/* MSA context must be preserved */
#घोषणा TIF_SYSCALL_TRACE	31	/* syscall trace active */

#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_SYSCALL_AUDIT	(1<<TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SECCOMP		(1<<TIF_SECCOMP)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_UPROBE		(1<<TIF_UPROBE)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_USEDFPU		(1<<TIF_USEDFPU)
#घोषणा _TIF_NOHZ		(1<<TIF_NOHZ)
#घोषणा _TIF_FIXADE		(1<<TIF_FIXADE)
#घोषणा _TIF_LOGADE		(1<<TIF_LOGADE)
#घोषणा _TIF_32BIT_REGS		(1<<TIF_32BIT_REGS)
#घोषणा _TIF_32BIT_ADDR		(1<<TIF_32BIT_ADDR)
#घोषणा _TIF_FPUBOUND		(1<<TIF_FPUBOUND)
#घोषणा _TIF_LOAD_WATCH		(1<<TIF_LOAD_WATCH)
#घोषणा _TIF_32BIT_FPREGS	(1<<TIF_32BIT_FPREGS)
#घोषणा _TIF_HYBRID_FPREGS	(1<<TIF_HYBRID_FPREGS)
#घोषणा _TIF_USEDMSA		(1<<TIF_USEDMSA)
#घोषणा _TIF_MSA_CTX_LIVE	(1<<TIF_MSA_CTX_LIVE)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1<<TIF_SYSCALL_TRACEPOINT)

#घोषणा _TIF_WORK_SYSCALL_ENTRY	(_TIF_NOHZ | _TIF_SYSCALL_TRACE |	\
				 _TIF_SYSCALL_AUDIT | \
				 _TIF_SYSCALL_TRACEPOINT | _TIF_SECCOMP)

/* work to करो in syscall_trace_leave() */
#घोषणा _TIF_WORK_SYSCALL_EXIT	(_TIF_NOHZ | _TIF_SYSCALL_TRACE |	\
				 _TIF_SYSCALL_AUDIT | _TIF_SYSCALL_TRACEPOINT)

/* work to करो on पूर्णांकerrupt/exception वापस */
#घोषणा _TIF_WORK_MASK		\
	(_TIF_SIGPENDING | _TIF_NEED_RESCHED | _TIF_NOTIFY_RESUME |	\
	 _TIF_UPROBE | _TIF_NOTIFY_SIGNAL)
/* work to करो on any वापस to u-space */
#घोषणा _TIF_ALLWORK_MASK	(_TIF_NOHZ | _TIF_WORK_MASK |		\
				 _TIF_WORK_SYSCALL_EXIT |		\
				 _TIF_SYSCALL_TRACEPOINT)

/*
 * We stash processor id पूर्णांकo a COP0 रेजिस्टर to retrieve it fast
 * at kernel exception entry.
 */
#अगर   defined(CONFIG_MIPS_PGD_C0_CONTEXT)
#घोषणा SMP_CPUID_REG		20, 0	/* XCONTEXT */
#घोषणा ASM_SMP_CPUID_REG	$20
#घोषणा SMP_CPUID_PTRSHIFT	48
#अन्यथा
#घोषणा SMP_CPUID_REG		4, 0	/* CONTEXT */
#घोषणा ASM_SMP_CPUID_REG	$4
#घोषणा SMP_CPUID_PTRSHIFT	23
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#घोषणा SMP_CPUID_REGSHIFT	(SMP_CPUID_PTRSHIFT + 3)
#अन्यथा
#घोषणा SMP_CPUID_REGSHIFT	(SMP_CPUID_PTRSHIFT + 2)
#पूर्ण_अगर

#घोषणा ASM_CPUID_MFC0		MFC0
#घोषणा UASM_i_CPUID_MFC0	UASM_i_MFC0

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_THREAD_INFO_H */
