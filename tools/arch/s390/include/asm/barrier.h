<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copied from the kernel sources:
 *
 * Copyright IBM Corp. 1999, 2009
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __TOOLS_LINUX_ASM_BARRIER_H
#घोषणा __TOOLS_LINUX_ASM_BARRIER_H

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

#घोषणा rmb()				mb()
#घोषणा wmb()				mb()

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

#पूर्ण_अगर /* __TOOLS_LIB_ASM_BARRIER_H */
