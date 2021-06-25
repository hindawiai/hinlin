<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 1999, 2009
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __ASM_BARRIER_H
#घोषणा __ASM_BARRIER_H

/*
 * Force strict CPU ordering.
 * And yes, this is required on UP too when we're talking
 * to devices.
 */

#अगर_घोषित CONFIG_HAVE_MARCH_Z196_FEATURES
/* Fast-BCR without checkpoपूर्णांक synchronization */
#घोषणा __ASM_BARRIER "bcr 14,0\n"
#अन्यथा
#घोषणा __ASM_BARRIER "bcr 15,0\n"
#पूर्ण_अगर

#घोषणा mb() करो अणु  यंत्र अस्थिर(__ASM_BARRIER : : : "memory"); पूर्ण जबतक (0)

#घोषणा rmb()				barrier()
#घोषणा wmb()				barrier()
#घोषणा dma_rmb()			mb()
#घोषणा dma_wmb()			mb()
#घोषणा __smp_mb()			mb()
#घोषणा __smp_rmb()			rmb()
#घोषणा __smp_wmb()			wmb()

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

#घोषणा __smp_mb__beक्रमe_atomic()	barrier()
#घोषणा __smp_mb__after_atomic()	barrier()

/**
 * array_index_mask_nospec - generate a mask क्रम array_idx() that is
 * ~0UL when the bounds check succeeds and 0 otherwise
 * @index: array element index
 * @size: number of elements in array
 */
#घोषणा array_index_mask_nospec array_index_mask_nospec
अटल अंतरभूत अचिन्हित दीर्घ array_index_mask_nospec(अचिन्हित दीर्घ index,
						    अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ mask;

	अगर (__builtin_स्थिरant_p(size) && size > 0) अणु
		यंत्र("	clgr	%2,%1\n"
		    "	slbgr	%0,%0\n"
		    :"=d" (mask) : "d" (size-1), "d" (index) :"cc");
		वापस mask;
	पूर्ण
	यंत्र("	clgr	%1,%2\n"
	    "	slbgr	%0,%0\n"
	    :"=d" (mask) : "d" (size), "d" (index) :"cc");
	वापस ~mask;
पूर्ण

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* __ASM_BARRIER_H */
