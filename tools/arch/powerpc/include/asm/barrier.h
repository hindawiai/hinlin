<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copied from the kernel sources:
 *
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 */
#अगर_अघोषित _TOOLS_LINUX_ASM_POWERPC_BARRIER_H
#घोषणा _TOOLS_LINUX_ASM_POWERPC_BARRIER_H

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
 */
#घोषणा mb()   __यंत्र__ __अस्थिर__ ("sync" : : : "memory")
#घोषणा rmb()  __यंत्र__ __अस्थिर__ ("sync" : : : "memory")
#घोषणा wmb()  __यंत्र__ __अस्थिर__ ("sync" : : : "memory")

#अगर defined(__घातerpc64__)
#घोषणा smp_lwsync()	__यंत्र__ __अस्थिर__ ("lwsync" : : : "memory")

#घोषणा smp_store_release(p, v)			\
करो अणु						\
	smp_lwsync();				\
	WRITE_ONCE(*p, v);			\
पूर्ण जबतक (0)

#घोषणा smp_load_acquire(p)			\
(अणु						\
	typeof(*p) ___p1 = READ_ONCE(*p);	\
	smp_lwsync();				\
	___p1;					\
पूर्ण)
#पूर्ण_अगर /* defined(__घातerpc64__) */
#पूर्ण_अगर /* _TOOLS_LINUX_ASM_POWERPC_BARRIER_H */
