<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * BPF Jit compiler defines
 *
 * Copyright IBM Corp. 2012,2015
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#अगर_अघोषित __ARCH_S390_NET_BPF_JIT_H
#घोषणा __ARCH_S390_NET_BPF_JIT_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/filter.h>
#समावेश <linux/types.h>

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Stackframe layout (packed stack):
 *
 *				    ^ high
 *	      +---------------+     |
 *	      | old backchain |     |
 *	      +---------------+     |
 *	      |   r15 - r6    |     |
 *	      +---------------+     |
 *	      | 4 byte align  |     |
 *	      | tail_call_cnt |     |
 * BFP	   -> +===============+     |
 *	      |		      |     |
 *	      |   BPF stack   |     |
 *	      |		      |     |
 * R15+160 -> +---------------+     |
 *	      | new backchain |     |
 * R15+152 -> +---------------+     |
 *	      | + 152 byte SA |     |
 * R15	   -> +---------------+     + low
 *
 * We get 160 bytes stack space from calling function, but only use
 * 12 * 8 byte क्रम old backchain, r15..r6, and tail_call_cnt.
 *
 * The stack size used by the BPF program ("BPF stack" above) is passed
 * via "aux->stack_depth".
 */
#घोषणा STK_SPACE_ADD	(160)
#घोषणा STK_160_UNUSED	(160 - 12 * 8)
#घोषणा STK_OFF		(STK_SPACE_ADD - STK_160_UNUSED)

#घोषणा STK_OFF_R6	(160 - 11 * 8)	/* Offset of r6 on stack */
#घोषणा STK_OFF_TCCNT	(160 - 12 * 8)	/* Offset of tail_call_cnt on stack */

#पूर्ण_अगर /* __ARCH_S390_NET_BPF_JIT_H */
