<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_BARRIER_H
#घोषणा __ASM_CSKY_BARRIER_H

#अगर_अघोषित __ASSEMBLY__

#घोषणा nop()	यंत्र अस्थिर ("nop\n":::"memory")

#अगर_घोषित CONFIG_SMP

/*
 * bar.brwarws: ordering barrier क्रम all load/store inकाष्ठाions
 *              beक्रमe/after
 *
 * |31|30 26|25 21|20 16|15  10|9   5|4           0|
 *  1  10000 00000 00000 100001	00001 0 bw br aw ar
 *
 * b: beक्रमe
 * a: after
 * r: पढ़ो
 * w: ग_लिखो
 *
 * Here are all combinations:
 *
 * bar.brw
 * bar.br
 * bar.bw
 * bar.arw
 * bar.ar
 * bar.aw
 * bar.brwarw
 * bar.brarw
 * bar.bwarw
 * bar.brwar
 * bar.brwaw
 * bar.brar
 * bar.bwaw
 */
#घोषणा __bar_brw()	यंत्र अस्थिर (".long 0x842cc000\n":::"memory")
#घोषणा __bar_br()	यंत्र अस्थिर (".long 0x8424c000\n":::"memory")
#घोषणा __bar_bw()	यंत्र अस्थिर (".long 0x8428c000\n":::"memory")
#घोषणा __bar_arw()	यंत्र अस्थिर (".long 0x8423c000\n":::"memory")
#घोषणा __bar_ar()	यंत्र अस्थिर (".long 0x8421c000\n":::"memory")
#घोषणा __bar_aw()	यंत्र अस्थिर (".long 0x8422c000\n":::"memory")
#घोषणा __bar_brwarw()	यंत्र अस्थिर (".long 0x842fc000\n":::"memory")
#घोषणा __bar_brarw()	यंत्र अस्थिर (".long 0x8427c000\n":::"memory")
#घोषणा __bar_bwarw()	यंत्र अस्थिर (".long 0x842bc000\n":::"memory")
#घोषणा __bar_brwar()	यंत्र अस्थिर (".long 0x842dc000\n":::"memory")
#घोषणा __bar_brwaw()	यंत्र अस्थिर (".long 0x842ec000\n":::"memory")
#घोषणा __bar_brar()	यंत्र अस्थिर (".long 0x8425c000\n":::"memory")
#घोषणा __bar_brar()	यंत्र अस्थिर (".long 0x8425c000\n":::"memory")
#घोषणा __bar_bwaw()	यंत्र अस्थिर (".long 0x842ac000\n":::"memory")

#घोषणा __smp_mb()	__bar_brwarw()
#घोषणा __smp_rmb()	__bar_brar()
#घोषणा __smp_wmb()	__bar_bwaw()

#घोषणा ACQUIRE_FENCE		".long 0x8427c000\n"
#घोषणा __smp_acquire_fence()	__bar_brarw()
#घोषणा __smp_release_fence()	__bar_brwaw()

#पूर्ण_अगर /* CONFIG_SMP */

/*
 * sync:        completion barrier, all sync.xx inकाष्ठाions
 *              guarantee the last response received by bus transaction
 *              made by ld/st inकाष्ठाions beक्रमe sync.s
 * sync.s:      inherit from sync, but also shareable to other cores
 * sync.i:      inherit from sync, but also flush cpu pipeline
 * sync.is:     the same with sync.i + sync.s
 */
#घोषणा mb()		यंत्र अस्थिर ("sync\n":::"memory")

#अगर_घोषित CONFIG_CPU_HAS_CACHEV2
/*
 * Using three sync.is to prevent speculative PTW
 */
#घोषणा sync_is()	यंत्र अस्थिर ("sync.is\nsync.is\nsync.is\n":::"memory")
#पूर्ण_अगर

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_CSKY_BARRIER_H */
