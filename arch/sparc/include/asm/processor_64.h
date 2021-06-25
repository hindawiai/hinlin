<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र/processor.h
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित __ASM_SPARC64_PROCESSOR_H
#घोषणा __ASM_SPARC64_PROCESSOR_H

#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/page.h>

/*
 * User lives in his very own context, and cannot reference us. Note
 * that TASK_SIZE is a misnomer, it really gives maximum user भव
 * address that the kernel will allocate out.
 *
 * XXX No दीर्घer using भव page tables, समाप्त this upper limit...
 */
#घोषणा VA_BITS		44
#अगर_अघोषित __ASSEMBLY__
#घोषणा VPTE_SIZE	(1UL << (VA_BITS - PAGE_SHIFT + 3))
#अन्यथा
#घोषणा VPTE_SIZE	(1 << (VA_BITS - PAGE_SHIFT + 3))
#पूर्ण_अगर

#घोषणा TASK_SIZE_OF(tsk) \
	(test_tsk_thपढ़ो_flag(tsk,TIF_32BIT) ? \
	 (1UL << 32UL) : ((अचिन्हित दीर्घ)-VPTE_SIZE))
#घोषणा TASK_SIZE \
	(test_thपढ़ो_flag(TIF_32BIT) ? \
	 (1UL << 32UL) : ((अचिन्हित दीर्घ)-VPTE_SIZE))
#अगर_घोषित __KERNEL__

#घोषणा STACK_TOP32	((1UL << 32UL) - PAGE_SIZE)
#घोषणा STACK_TOP64	(0x0000080000000000UL - (1UL << 32UL))

#घोषणा STACK_TOP	(test_thपढ़ो_flag(TIF_32BIT) ? \
			 STACK_TOP32 : STACK_TOP64)

#घोषणा STACK_TOP_MAX	STACK_TOP64

#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित अक्षर seg;
पूर्ण mm_segment_t;

/* The Sparc processor specअगरic thपढ़ो काष्ठा. */
/* XXX This should die, everything can go पूर्णांकo thपढ़ो_info now. */
काष्ठा thपढ़ो_काष्ठा अणु
#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	/* How many spinlocks held by this thपढ़ो.
	 * Used with spin lock debugging to catch tasks
	 * sleeping illegally with locks held.
	 */
	पूर्णांक smp_lock_count;
	अचिन्हित पूर्णांक smp_lock_pc;
#अन्यथा
	पूर्णांक dummy; /* f'in gcc bug... */
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#अगर_अघोषित CONFIG_DEBUG_SPINLOCK
#घोषणा INIT_THREAD  अणु			\
	0,				\
पूर्ण
#अन्यथा /* CONFIG_DEBUG_SPINLOCK */
#घोषणा INIT_THREAD  अणु					\
/* smp_lock_count, smp_lock_pc, */			\
   0,		   0,					\
पूर्ण
#पूर्ण_अगर /* !(CONFIG_DEBUG_SPINLOCK) */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/fpumacro.h>

काष्ठा task_काष्ठा;

/* On Uniprocessor, even in RMO processes see TSO semantics */
#अगर_घोषित CONFIG_SMP
#घोषणा TSTATE_INITIAL_MM	TSTATE_TSO
#अन्यथा
#घोषणा TSTATE_INITIAL_MM	TSTATE_RMO
#पूर्ण_अगर

/* Do necessary setup to start up a newly executed thपढ़ो. */
#घोषणा start_thपढ़ो(regs, pc, sp) \
करो अणु \
	अचिन्हित दीर्घ __asi = ASI_PNF; \
	regs->tstate = (regs->tstate & (TSTATE_CWP)) | (TSTATE_INITIAL_MM|TSTATE_IE) | (__asi << 24UL); \
	regs->tpc = ((pc & (~3)) - 4); \
	regs->tnpc = regs->tpc + 4; \
	regs->y = 0; \
	set_thपढ़ो_wstate(1 << 3); \
	अगर (current_thपढ़ो_info()->utraps) अणु \
		अगर (*(current_thपढ़ो_info()->utraps) < 2) \
			kमुक्त(current_thपढ़ो_info()->utraps); \
		अन्यथा \
			(*(current_thपढ़ो_info()->utraps))--; \
		current_thपढ़ो_info()->utraps = शून्य; \
	पूर्ण \
	__यंत्र__ __अस्थिर__( \
	"stx		%%g0, [%0 + %2 + 0x00]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x08]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x10]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x18]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x20]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x28]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x30]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x38]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x40]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x48]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x50]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x58]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x60]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x68]\n\t" \
	"stx		%1,   [%0 + %2 + 0x70]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x78]\n\t" \
	"wrpr		%%g0, (1 << 3), %%wstate\n\t" \
	: \
	: "r" (regs), "r" (sp - माप(काष्ठा reg_winकरोw) - STACK_BIAS), \
	  "i" ((स्थिर अचिन्हित दीर्घ)(&((काष्ठा pt_regs *)0)->u_regs[0]))); \
	fprs_ग_लिखो(0);	\
	current_thपढ़ो_info()->xfsr[0] = 0;	\
	current_thपढ़ो_info()->fpsaved[0] = 0;	\
	regs->tstate &= ~TSTATE_PEF;	\
पूर्ण जबतक (0)

#घोषणा start_thपढ़ो32(regs, pc, sp) \
करो अणु \
	अचिन्हित दीर्घ __asi = ASI_PNF; \
	pc &= 0x00000000ffffffffUL; \
	sp &= 0x00000000ffffffffUL; \
	regs->tstate = (regs->tstate & (TSTATE_CWP))|(TSTATE_INITIAL_MM|TSTATE_IE|TSTATE_AM) | (__asi << 24UL); \
	regs->tpc = ((pc & (~3)) - 4); \
	regs->tnpc = regs->tpc + 4; \
	regs->y = 0; \
	set_thपढ़ो_wstate(2 << 3); \
	अगर (current_thपढ़ो_info()->utraps) अणु \
		अगर (*(current_thपढ़ो_info()->utraps) < 2) \
			kमुक्त(current_thपढ़ो_info()->utraps); \
		अन्यथा \
			(*(current_thपढ़ो_info()->utraps))--; \
		current_thपढ़ो_info()->utraps = शून्य; \
	पूर्ण \
	__यंत्र__ __अस्थिर__( \
	"stx		%%g0, [%0 + %2 + 0x00]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x08]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x10]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x18]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x20]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x28]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x30]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x38]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x40]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x48]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x50]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x58]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x60]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x68]\n\t" \
	"stx		%1,   [%0 + %2 + 0x70]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x78]\n\t" \
	"wrpr		%%g0, (2 << 3), %%wstate\n\t" \
	: \
	: "r" (regs), "r" (sp - माप(काष्ठा reg_winकरोw32)), \
	  "i" ((स्थिर अचिन्हित दीर्घ)(&((काष्ठा pt_regs *)0)->u_regs[0]))); \
	fprs_ग_लिखो(0);	\
	current_thपढ़ो_info()->xfsr[0] = 0;	\
	current_thपढ़ो_info()->fpsaved[0] = 0;	\
	regs->tstate &= ~TSTATE_PEF;	\
पूर्ण जबतक (0)

/* Free all resources held by a thपढ़ो. */
#घोषणा release_thपढ़ो(tsk)		करो अणु पूर्ण जबतक (0)

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *task);

#घोषणा task_pt_regs(tsk) (task_thपढ़ो_info(tsk)->kregs)
#घोषणा KSTK_EIP(tsk)  (task_pt_regs(tsk)->tpc)
#घोषणा KSTK_ESP(tsk)  (task_pt_regs(tsk)->u_regs[UREG_FP])

/* Please see the commentary in यंत्र/backoff.h क्रम a description of
 * what these inकाष्ठाions are करोing and how they have been chosen.
 * To make a दीर्घ story लघु, we are trying to yield the current cpu
 * stअक्रम during busy loops.
 */
#अगर_घोषित	BUILD_VDSO
#घोषणा	cpu_relax()	यंत्र अस्थिर("\n99:\n\t"			\
				     "rd	%%ccr, %%g0\n\t"	\
				     "rd	%%ccr, %%g0\n\t"	\
				     "rd	%%ccr, %%g0\n\t"	\
				     ::: "memory")
#अन्यथा /* ! BUILD_VDSO */
#घोषणा cpu_relax()	यंत्र अस्थिर("\n99:\n\t"			\
				     "rd	%%ccr, %%g0\n\t"	\
				     "rd	%%ccr, %%g0\n\t"	\
				     "rd	%%ccr, %%g0\n\t"	\
				     ".section	.pause_3insn_patch,\"ax\"\n\t"\
				     ".word	99b\n\t"		\
				     "wr	%%g0, 128, %%asr27\n\t"	\
				     "nop\n\t"				\
				     "nop\n\t"				\
				     ".previous"			\
				     ::: "memory")
#पूर्ण_अगर

/* Prefetch support.  This is tuned क्रम UltraSPARC-III and later.
 * UltraSPARC-I will treat these as nops, and UltraSPARC-II has
 * a shallower prefetch queue than later chips.
 */
#घोषणा ARCH_HAS_PREFETCH
#घोषणा ARCH_HAS_PREFETCHW
#घोषणा ARCH_HAS_SPINLOCK_PREFETCH

अटल अंतरभूत व्योम prefetch(स्थिर व्योम *x)
अणु
	/* We करो not use the पढ़ो prefetch mnemonic because that
	 * prefetches पूर्णांकo the prefetch-cache which only is accessible
	 * by भग्नing poपूर्णांक operations in UltraSPARC-III and later.
	 * By contrast, "#one_write" prefetches पूर्णांकo the L2 cache
	 * in shared state.
	 */
	__यंत्र__ __अस्थिर__("prefetch [%0], #one_write"
			     : /* no outमाला_दो */
			     : "r" (x));
पूर्ण

अटल अंतरभूत व्योम prefetchw(स्थिर व्योम *x)
अणु
	/* The most optimal prefetch to use क्रम ग_लिखोs is
	 * "#n_writes".  This brings the cacheline पूर्णांकo the
	 * L2 cache in "owned" state.
	 */
	__यंत्र__ __अस्थिर__("prefetch [%0], #n_writes"
			     : /* no outमाला_दो */
			     : "r" (x));
पूर्ण

#घोषणा spin_lock_prefetch(x)	prefetchw(x)

#घोषणा HAVE_ARCH_PICK_MMAP_LAYOUT

पूर्णांक करो_mathemu(काष्ठा pt_regs *regs, काष्ठा fpustate *f, bool illegal_insn_trap);

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(__ASM_SPARC64_PROCESSOR_H) */
