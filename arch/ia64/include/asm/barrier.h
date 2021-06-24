<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Memory barrier definitions.  This is based on inक्रमmation published
 * in the Processor Abstraction Layer and the System Abstraction Layer
 * manual.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 */
#अगर_अघोषित _ASM_IA64_BARRIER_H
#घोषणा _ASM_IA64_BARRIER_H

#समावेश <linux/compiler.h>

/*
 * Macros to क्रमce memory ordering.  In these descriptions, "previous"
 * and "subsequent" refer to program order; "visible" means that all
 * architecturally visible effects of a memory access have occurred
 * (at a minimum, this means the memory has been पढ़ो or written).
 *
 *   wmb():	Guarantees that all preceding stores to memory-
 *		like regions are visible beक्रमe any subsequent
 *		stores and that all following stores will be
 *		visible only after all previous stores.
 *   rmb():	Like wmb(), but क्रम पढ़ोs.
 *   mb():	wmb()/rmb() combo, i.e., all previous memory
 *		accesses are visible beक्रमe all subsequent
 *		accesses and vice versa.  This is also known as
 *		a "fence."
 *
 * Note: "mb()" and its variants cannot be used as a fence to order
 * accesses to memory mapped I/O रेजिस्टरs.  For that, mf.a needs to
 * be used.  However, we करोn't want to always use mf.a because (a)
 * it's (presumably) much slower than mf and (b) mf.a is supported क्रम
 * sequential memory pages only.
 */
#घोषणा mb()		ia64_mf()
#घोषणा rmb()		mb()
#घोषणा wmb()		mb()

#घोषणा dma_rmb()	mb()
#घोषणा dma_wmb()	mb()

# define __smp_mb()	mb()

#घोषणा __smp_mb__beक्रमe_atomic()	barrier()
#घोषणा __smp_mb__after_atomic()	barrier()

/*
 * IA64 GCC turns अस्थिर stores पूर्णांकo st.rel and अस्थिर loads पूर्णांकo ld.acq no
 * need क्रम यंत्र trickery!
 */

#घोषणा __smp_store_release(p, v)						\
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

/*
 * The group barrier in front of the rsm & ssm are necessary to ensure
 * that none of the previous inकाष्ठाions in the same group are
 * affected by the rsm/ssm.
 */

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* _ASM_IA64_BARRIER_H */
