<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_BARRIER_H
#घोषणा _ASM_X86_BARRIER_H

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/nops.h>

/*
 * Force strict CPU ordering.
 * And yes, this might be required on UP too when we're talking
 * to devices.
 */

#अगर_घोषित CONFIG_X86_32
#घोषणा mb() यंत्र अस्थिर(ALTERNATIVE("lock; addl $0,-4(%%esp)", "mfence", \
				      X86_FEATURE_XMM2) ::: "memory", "cc")
#घोषणा rmb() यंत्र अस्थिर(ALTERNATIVE("lock; addl $0,-4(%%esp)", "lfence", \
				       X86_FEATURE_XMM2) ::: "memory", "cc")
#घोषणा wmb() यंत्र अस्थिर(ALTERNATIVE("lock; addl $0,-4(%%esp)", "sfence", \
				       X86_FEATURE_XMM2) ::: "memory", "cc")
#अन्यथा
#घोषणा mb() 	यंत्र अस्थिर("mfence":::"memory")
#घोषणा rmb()	यंत्र अस्थिर("lfence":::"memory")
#घोषणा wmb()	यंत्र अस्थिर("sfence" ::: "memory")
#पूर्ण_अगर

/**
 * array_index_mask_nospec() - generate a mask that is ~0UL when the
 * 	bounds check succeeds and 0 otherwise
 * @index: array element index
 * @size: number of elements in array
 *
 * Returns:
 *     0 - (index < size)
 */
अटल अंतरभूत अचिन्हित दीर्घ array_index_mask_nospec(अचिन्हित दीर्घ index,
		अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ mask;

	यंत्र अस्थिर ("cmp %1,%2; sbb %0,%0;"
			:"=r" (mask)
			:"g"(size),"r" (index)
			:"cc");
	वापस mask;
पूर्ण

/* Override the शेष implementation from linux/nospec.h. */
#घोषणा array_index_mask_nospec array_index_mask_nospec

/* Prevent speculative execution past this barrier. */
#घोषणा barrier_nospec() alternative("", "lfence", X86_FEATURE_LFENCE_RDTSC)

#घोषणा dma_rmb()	barrier()
#घोषणा dma_wmb()	barrier()

#अगर_घोषित CONFIG_X86_32
#घोषणा __smp_mb()	यंत्र अस्थिर("lock; addl $0,-4(%%esp)" ::: "memory", "cc")
#अन्यथा
#घोषणा __smp_mb()	यंत्र अस्थिर("lock; addl $0,-4(%%rsp)" ::: "memory", "cc")
#पूर्ण_अगर
#घोषणा __smp_rmb()	dma_rmb()
#घोषणा __smp_wmb()	barrier()
#घोषणा __smp_store_mb(var, value) करो अणु (व्योम)xchg(&var, value); पूर्ण जबतक (0)

#घोषणा __smp_store_release(p, v)					\
करो अणु									\
	compileसमय_निश्चित_atomic_type(*p);				\
	barrier();							\
	WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)

#घोषणा __smp_load_acquire(p)						\
(अणु									\
	typeof(*p) ___p1 = READ_ONCE(*p);				\
	compileसमय_निश्चित_atomic_type(*p);				\
	barrier();							\
	___p1;								\
पूर्ण)

/* Atomic operations are alपढ़ोy serializing on x86 */
#घोषणा __smp_mb__beक्रमe_atomic()	करो अणु पूर्ण जबतक (0)
#घोषणा __smp_mb__after_atomic()	करो अणु पूर्ण जबतक (0)

#समावेश <यंत्र-generic/barrier.h>

/*
 * Make previous memory operations globally visible beक्रमe
 * a WRMSR.
 *
 * MFENCE makes ग_लिखोs visible, but only affects load/store
 * inकाष्ठाions.  WRMSR is unक्रमtunately not a load/store
 * inकाष्ठाion and is unaffected by MFENCE.  The LFENCE ensures
 * that the WRMSR is not reordered.
 *
 * Most WRMSRs are full serializing inकाष्ठाions themselves and
 * करो not require this barrier.  This is only required क्रम the
 * IA32_TSC_DEADLINE and X2APIC MSRs.
 */
अटल अंतरभूत व्योम weak_wrmsr_fence(व्योम)
अणु
	यंत्र अस्थिर("mfence; lfence" : : : "memory");
पूर्ण

#पूर्ण_अगर /* _ASM_X86_BARRIER_H */
