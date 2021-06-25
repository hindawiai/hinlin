<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-sh/processor.h
 *
 * Copyright (C) 1999, 2000  Niibe Yutaka
 * Copyright (C) 2002, 2003  Paul Mundt
 */

#अगर_अघोषित __ASM_SH_PROCESSOR_32_H
#घोषणा __ASM_SH_PROCESSOR_32_H

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>

/* Core Processor Version Register */
#घोषणा CCN_PVR		0xff000030
#घोषणा CCN_CVR		0xff000040
#घोषणा CCN_PRR		0xff000044

/*
 * User space process size: 2GB.
 *
 * Since SH7709 and SH7750 have "area 7", we can't use 0x7c000000--0x7fffffff
 */
#घोषणा TASK_SIZE	0x7c000000UL

#घोषणा STACK_TOP	TASK_SIZE
#घोषणा STACK_TOP_MAX	STACK_TOP

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE	PAGE_ALIGN(TASK_SIZE / 3)

/*
 * Bit of SR रेजिस्टर
 *
 * FD-bit:
 *     When it's set, it means the processor doesn't have right to use FPU,
 *     and it results exception when the भग्नing operation is executed.
 *
 * IMASK-bit:
 *     Interrupt level mask
 */
#घोषणा SR_DSP		0x00001000
#घोषणा SR_IMASK	0x000000f0
#घोषणा SR_FD		0x00008000
#घोषणा SR_MD		0x40000000

/*
 * DSP काष्ठाure and data
 */
काष्ठा sh_dsp_काष्ठा अणु
	अचिन्हित दीर्घ dsp_regs[14];
	दीर्घ status;
पूर्ण;

/*
 * FPU काष्ठाure and data
 */

काष्ठा sh_fpu_hard_काष्ठा अणु
	अचिन्हित दीर्घ fp_regs[16];
	अचिन्हित दीर्घ xfp_regs[16];
	अचिन्हित दीर्घ fpscr;
	अचिन्हित दीर्घ fpul;

	दीर्घ status; /* software status inक्रमmation */
पूर्ण;

/* Dummy fpu emulator  */
काष्ठा sh_fpu_soft_काष्ठा अणु
	अचिन्हित दीर्घ fp_regs[16];
	अचिन्हित दीर्घ xfp_regs[16];
	अचिन्हित दीर्घ fpscr;
	अचिन्हित दीर्घ fpul;

	अचिन्हित अक्षर lookahead;
	अचिन्हित दीर्घ entry_pc;
पूर्ण;

जोड़ thपढ़ो_xstate अणु
	काष्ठा sh_fpu_hard_काष्ठा hardfpu;
	काष्ठा sh_fpu_soft_काष्ठा softfpu;
पूर्ण;

काष्ठा thपढ़ो_काष्ठा अणु
	/* Saved रेजिस्टरs when thपढ़ो is descheduled */
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ pc;

	/* Various thपढ़ो flags, see SH_THREAD_xxx */
	अचिन्हित दीर्घ flags;

	/* Save middle states of ptrace अवरोधpoपूर्णांकs */
	काष्ठा perf_event *ptrace_bps[HBP_NUM];

#अगर_घोषित CONFIG_SH_DSP
	/* Dsp status inक्रमmation */
	काष्ठा sh_dsp_काष्ठा dsp_status;
#पूर्ण_अगर

	/* Extended processor state */
	जोड़ thपढ़ो_xstate *xstate;

	/*
	 * fpu_counter contains the number of consecutive context चयनes
	 * that the FPU is used. If this is over a threshold, the lazy fpu
	 * saving becomes unlazy to save the trap. This is an अचिन्हित अक्षर
	 * so that after 256 बार the counter wraps and the behavior turns
	 * lazy again; this to deal with bursty apps that only use FPU क्रम
	 * a लघु समय
	 */
	अचिन्हित अक्षर fpu_counter;
पूर्ण;

#घोषणा INIT_THREAD  अणु						\
	.sp = माप(init_stack) + (दीर्घ) &init_stack,		\
	.flags = 0,						\
पूर्ण

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ new_pc, अचिन्हित दीर्घ new_sp);

/* Free all resources held by a thपढ़ो. */
बाह्य व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);

/*
 * FPU lazy state save handling.
 */

अटल __अंतरभूत__ व्योम disable_fpu(व्योम)
अणु
	अचिन्हित दीर्घ __dummy;

	/* Set FD flag in SR */
	__यंत्र__ __अस्थिर__("stc	sr, %0\n\t"
			     "or	%1, %0\n\t"
			     "ldc	%0, sr"
			     : "=&r" (__dummy)
			     : "r" (SR_FD));
पूर्ण

अटल __अंतरभूत__ व्योम enable_fpu(व्योम)
अणु
	अचिन्हित दीर्घ __dummy;

	/* Clear out FD flag in SR */
	__यंत्र__ __अस्थिर__("stc	sr, %0\n\t"
			     "and	%1, %0\n\t"
			     "ldc	%0, sr"
			     : "=&r" (__dummy)
			     : "r" (~SR_FD));
पूर्ण

/* Double presision, न_अंकS as न_अंकS, rounding to nearest, no exceptions */
#घोषणा FPSCR_INIT  0x00080000

#घोषणा	FPSCR_CAUSE_MASK	0x0001f000	/* Cause bits */
#घोषणा	FPSCR_FLAG_MASK		0x0000007c	/* Flag bits */

/*
 * Return saved PC of a blocked thपढ़ो.
 */
#घोषणा thपढ़ो_saved_pc(tsk)	(tsk->thपढ़ो.pc)

व्योम show_trace(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *sp,
		काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl);

#अगर_घोषित CONFIG_DUMP_CODE
व्योम show_code(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत व्योम show_code(काष्ठा pt_regs *regs)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा KSTK_EIP(tsk)  (task_pt_regs(tsk)->pc)
#घोषणा KSTK_ESP(tsk)  (task_pt_regs(tsk)->regs[15])

#अगर defined(CONFIG_CPU_SH2A) || defined(CONFIG_CPU_SH4)

#घोषणा PREFETCH_STRIDE		L1_CACHE_BYTES
#घोषणा ARCH_HAS_PREFETCH
#घोषणा ARCH_HAS_PREFETCHW

अटल अंतरभूत व्योम prefetch(स्थिर व्योम *x)
अणु
	__builtin_prefetch(x, 0, 3);
पूर्ण

अटल अंतरभूत व्योम prefetchw(स्थिर व्योम *x)
अणु
	__builtin_prefetch(x, 1, 3);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_PROCESSOR_32_H */
