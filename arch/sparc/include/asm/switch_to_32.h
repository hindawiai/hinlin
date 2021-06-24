<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_SWITCH_TO_H
#घोषणा __SPARC_SWITCH_TO_H

#समावेश <यंत्र/smp.h>

बाह्य काष्ठा thपढ़ो_info *current_set[NR_CPUS];

/*
 * Flush winकरोws so that the VM चयन which follows
 * would not pull the stack from under us.
 *
 * SWITCH_ENTER and SWITCH_DO_LAZY_FPU करो not work yet (e.g. SMP करोes not work)
 * XXX WTF is the above comment? Found in late teen 2.4.x.
 */
#अगर_घोषित CONFIG_SMP
#घोषणा SWITCH_ENTER(prv) \
	करो अणु			\
	अगर (test_tsk_thपढ़ो_flag(prv, TIF_USEDFPU)) अणु \
		put_psr(get_psr() | PSR_EF); \
		fpsave(&(prv)->thपढ़ो.भग्न_regs[0], &(prv)->thपढ़ो.fsr, \
		       &(prv)->thपढ़ो.fpqueue[0], &(prv)->thपढ़ो.fpqdepth); \
		clear_tsk_thपढ़ो_flag(prv, TIF_USEDFPU); \
		(prv)->thपढ़ो.kregs->psr &= ~PSR_EF; \
	पूर्ण \
	पूर्ण जबतक(0)

#घोषणा SWITCH_DO_LAZY_FPU(next)	/* */
#अन्यथा
#घोषणा SWITCH_ENTER(prv)		/* */
#घोषणा SWITCH_DO_LAZY_FPU(nxt)	\
	करो अणु			\
	अगर (last_task_used_math != (nxt))		\
		(nxt)->thपढ़ो.kregs->psr&=~PSR_EF;	\
	पूर्ण जबतक(0)
#पूर्ण_अगर

#घोषणा prepare_arch_चयन(next) करो अणु \
	__यंत्र__ __अस्थिर__( \
	".globl\tflush_patch_switch\nflush_patch_switch:\n\t" \
	"save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp\n\t" \
	"save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp\n\t" \
	"save %sp, -0x40, %sp\n\t" \
	"restore; restore; restore; restore; restore; restore; restore"); \
पूर्ण जबतक(0)

	/* Much care has gone पूर्णांकo this code, करो not touch it.
	 *
	 * We need to loadup regs l0/l1 क्रम the newly विभाजनed child
	 * हाल because the trap वापस path relies on those रेजिस्टरs
	 * holding certain values, gcc is told that they are clobbered.
	 * Gcc needs रेजिस्टरs क्रम 3 values in and 1 value out, so we
	 * clobber every non-fixed-usage रेजिस्टर besides l2/l3/o4/o5.  -DaveM
	 *
	 * Hey Dave, that करो not touch sign is too much of an incentive
	 * - Anton & Pete
	 */
#घोषणा चयन_to(prev, next, last) करो अणु						\
	SWITCH_ENTER(prev);								\
	SWITCH_DO_LAZY_FPU(next);							\
	cpumask_set_cpu(smp_processor_id(), mm_cpumask(next->active_mm));		\
	__यंत्र__ __अस्थिर__(								\
	"sethi	%%hi(here - 0x8), %%o7\n\t"						\
	"mov	%%g6, %%g3\n\t"								\
	"or	%%o7, %%lo(here - 0x8), %%o7\n\t"					\
	"rd	%%psr, %%g4\n\t"							\
	"std	%%sp, [%%g6 + %4]\n\t"							\
	"rd	%%wim, %%g5\n\t"							\
	"wr	%%g4, 0x20, %%psr\n\t"							\
	"nop\n\t"									\
	"std	%%g4, [%%g6 + %3]\n\t"							\
	"ldd	[%2 + %3], %%g4\n\t"							\
	"mov	%2, %%g6\n\t"								\
	".globl	patchme_store_new_current\n"						\
"patchme_store_new_current:\n\t"							\
	"st	%2, [%1]\n\t"								\
	"wr	%%g4, 0x20, %%psr\n\t"							\
	"nop\n\t"									\
	"nop\n\t"									\
	"nop\n\t"	/* LEON needs all 3 nops: load to %sp depends on CWP. */		\
	"ldd	[%%g6 + %4], %%sp\n\t"							\
	"wr	%%g5, 0x0, %%wim\n\t"							\
	"ldd	[%%sp + 0x00], %%l0\n\t"						\
	"ldd	[%%sp + 0x38], %%i6\n\t"						\
	"wr	%%g4, 0x0, %%psr\n\t"							\
	"nop\n\t"									\
	"nop\n\t"									\
	"jmpl	%%o7 + 0x8, %%g0\n\t"							\
	" ld	[%%g3 + %5], %0\n\t"							\
	"here:\n"									\
        : "=&r" (last)									\
        : "r" (&(current_set[hard_smp_processor_id()])),	\
	  "r" (task_thपढ़ो_info(next)),				\
	  "i" (TI_KPSR),					\
	  "i" (TI_KSP),						\
	  "i" (TI_TASK)						\
	:       "g1", "g2", "g3", "g4", "g5",       "g7",	\
	  "l0", "l1",       "l3", "l4", "l5", "l6", "l7",	\
	  "i0", "i1", "i2", "i3", "i4", "i5",			\
	  "o0", "o1", "o2", "o3",                   "o7");	\
	पूर्ण जबतक(0)

व्योम fpsave(अचिन्हित दीर्घ *fpregs, अचिन्हित दीर्घ *fsr,
	    व्योम *fpqueue, अचिन्हित दीर्घ *fpqdepth);
व्योम synchronize_user_stack(व्योम);

#पूर्ण_अगर /* __SPARC_SWITCH_TO_H */
