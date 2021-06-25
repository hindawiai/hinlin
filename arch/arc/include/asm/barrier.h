<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_BARRIER_H
#घोषणा __ASM_BARRIER_H

#अगर_घोषित CONFIG_ISA_ARCV2

/*
 * ARCv2 based HS38 cores are in-order issue, but still weakly ordered
 * due to micro-arch buffering/queuing of load/store, cache hit vs. miss ...
 *
 * Explicit barrier provided by DMB inकाष्ठाion
 *  - Opeअक्रम supports fine grained load/store/load+store semantics
 *  - Ensures that selected memory operation issued beक्रमe it will complete
 *    beक्रमe any subsequent memory operation of same type
 *  - DMB guarantees SMP as well as local barrier semantics
 *    (यंत्र-generic/barrier.h ensures sane smp_*mb अगर not defined here, i.e.
 *    UP: barrier(), SMP: smp_*mb == *mb)
 *  - DSYNC provides DMB+completion_of_cache_bpu_मुख्यtenance_ops hence not needed
 *    in the general हाल. Plus it only provides full barrier.
 */

#घोषणा mb()	यंत्र अस्थिर("dmb 3\n" : : : "memory")
#घोषणा rmb()	यंत्र अस्थिर("dmb 1\n" : : : "memory")
#घोषणा wmb()	यंत्र अस्थिर("dmb 2\n" : : : "memory")

#अन्यथा

/*
 * ARCompact based cores (ARC700) only have SYNC inकाष्ठाion which is super
 * heavy weight as it flushes the pipeline as well.
 * There are no real SMP implementations of such cores.
 */

#घोषणा mb()	यंत्र अस्थिर("sync\n" : : : "memory")

#पूर्ण_अगर

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर
