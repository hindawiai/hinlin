<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copied from the kernel sources to tools/:
 *
 * Memory barrier definitions.  This is based on inक्रमmation published
 * in the Processor Abstraction Layer and the System Abstraction Layer
 * manual.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 */
#अगर_अघोषित _TOOLS_LINUX_ASM_IA64_BARRIER_H
#घोषणा _TOOLS_LINUX_ASM_IA64_BARRIER_H

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

#घोषणा smp_store_release(p, v)			\
करो अणु						\
	barrier();				\
	WRITE_ONCE(*p, v);			\
पूर्ण जबतक (0)

#घोषणा smp_load_acquire(p)			\
(अणु						\
	typeof(*p) ___p1 = READ_ONCE(*p);	\
	barrier();				\
	___p1;					\
पूर्ण)

#पूर्ण_अगर /* _TOOLS_LINUX_ASM_IA64_BARRIER_H */
