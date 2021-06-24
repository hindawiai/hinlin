<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 */
#अगर_अघोषित _ASM_POWERPC_BARRIER_H
#घोषणा _ASM_POWERPC_BARRIER_H

#समावेश <यंत्र/यंत्र-स्थिर.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/ppc-opcode.h>
#पूर्ण_अगर

/*
 * Memory barrier.
 * The sync inकाष्ठाion guarantees that all memory accesses initiated
 * by this processor have been perक्रमmed (with respect to all other
 * mechanisms that access memory).  The eieio inकाष्ठाion is a barrier
 * providing an ordering (separately) क्रम (a) cacheable stores and (b)
 * loads and stores to non-cacheable memory (e.g. I/O devices).
 *
 * mb() prevents loads and stores being reordered across this poपूर्णांक.
 * rmb() prevents loads being reordered across this poपूर्णांक.
 * wmb() prevents stores being reordered across this poपूर्णांक.
 *
 * *mb() variants without smp_ prefix must order all types of memory
 * operations with one another. sync is the only inकाष्ठाion sufficient
 * to करो this.
 *
 * For the smp_ barriers, ordering is क्रम cacheable memory operations
 * only. We have to use the sync inकाष्ठाion क्रम smp_mb(), since lwsync
 * करोesn't order loads with respect to previous stores.  Lwsync can be
 * used क्रम smp_rmb() and smp_wmb().
 *
 * However, on CPUs that करोn't support lwsync, lwsync actually maps to a
 * heavy-weight sync, so smp_wmb() can be a lighter-weight eieio.
 */
#घोषणा mb()   __यंत्र__ __अस्थिर__ ("sync" : : : "memory")
#घोषणा rmb()  __यंत्र__ __अस्थिर__ ("sync" : : : "memory")
#घोषणा wmb()  __यंत्र__ __अस्थिर__ ("sync" : : : "memory")

/* The sub-arch has lwsync */
#अगर defined(CONFIG_PPC64) || defined(CONFIG_PPC_E500MC)
#    define SMPWMB      LWSYNC
#अन्यथा
#    define SMPWMB      eieio
#पूर्ण_अगर

#घोषणा __lwsync()	__यंत्र__ __अस्थिर__ (stringअगरy_in_c(LWSYNC) : : :"memory")
#घोषणा dma_rmb()	__lwsync()
#घोषणा dma_wmb()	__यंत्र__ __अस्थिर__ (stringअगरy_in_c(SMPWMB) : : :"memory")

#घोषणा __smp_lwsync()	__lwsync()

#घोषणा __smp_mb()	mb()
#घोषणा __smp_rmb()	__lwsync()
#घोषणा __smp_wmb()	__यंत्र__ __अस्थिर__ (stringअगरy_in_c(SMPWMB) : : :"memory")

/*
 * This is a barrier which prevents following inकाष्ठाions from being
 * started until the value of the argument x is known.  For example, अगर
 * x is a variable loaded from memory, this prevents following
 * inकाष्ठाions from being executed until the load has been perक्रमmed.
 */
#घोषणा data_barrier(x)	\
	यंत्र अस्थिर("twi 0,%0,0; isync" : : "r" (x) : "memory");

#घोषणा __smp_store_release(p, v)						\
करो अणु									\
	compileसमय_निश्चित_atomic_type(*p);				\
	__smp_lwsync();							\
	WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)

#घोषणा __smp_load_acquire(p)						\
(अणु									\
	typeof(*p) ___p1 = READ_ONCE(*p);				\
	compileसमय_निश्चित_atomic_type(*p);				\
	__smp_lwsync();							\
	___p1;								\
पूर्ण)

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#घोषणा NOSPEC_BARRIER_SLOT   nop
#या_अगर defined(CONFIG_PPC_FSL_BOOK3E)
#घोषणा NOSPEC_BARRIER_SLOT   nop; nop
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BARRIER_NOSPEC
/*
 * Prevent execution of subsequent inकाष्ठाions until preceding branches have
 * been fully resolved and are no दीर्घer executing speculatively.
 */
#घोषणा barrier_nospec_यंत्र NOSPEC_BARRIER_FIXUP_SECTION; NOSPEC_BARRIER_SLOT

// This also acts as a compiler barrier due to the memory clobber.
#घोषणा barrier_nospec() यंत्र (stringअगरy_in_c(barrier_nospec_यंत्र) ::: "memory")

#अन्यथा /* !CONFIG_PPC_BARRIER_NOSPEC */
#घोषणा barrier_nospec_यंत्र
#घोषणा barrier_nospec()
#पूर्ण_अगर /* CONFIG_PPC_BARRIER_NOSPEC */

/*
 * pmem_wmb() ensures that all stores क्रम which the modअगरication
 * are written to persistent storage by preceding dcbfps/dcbstps
 * inकाष्ठाions have updated persistent storage beक्रमe any data
 * access or data transfer caused by subsequent inकाष्ठाions is
 * initiated.
 */
#घोषणा pmem_wmb() __यंत्र__ __अस्थिर__(PPC_PHWSYNC ::: "memory")

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* _ASM_POWERPC_BARRIER_H */
