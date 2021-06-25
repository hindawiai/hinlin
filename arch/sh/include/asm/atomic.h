<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_ATOMIC_H
#घोषणा __ASM_SH_ATOMIC_H

#अगर defined(CONFIG_CPU_J2)

#समावेश <यंत्र-generic/atomic.h>

#अन्यथा

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 *
 */

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)
#घोषणा atomic_set(v,i)		WRITE_ONCE((v)->counter, (i))

#अगर defined(CONFIG_GUSA_RB)
#समावेश <यंत्र/atomic-grb.h>
#या_अगर defined(CONFIG_CPU_SH4A)
#समावेश <यंत्र/atomic-llsc.h>
#अन्यथा
#समावेश <यंत्र/atomic-irq.h>
#पूर्ण_अगर

#घोषणा atomic_xchg(v, new)		(xchg(&((v)->counter), new))
#घोषणा atomic_cmpxchg(v, o, n)		(cmpxchg(&((v)->counter), (o), (n)))

#पूर्ण_अगर /* CONFIG_CPU_J2 */

#पूर्ण_अगर /* __ASM_SH_ATOMIC_H */
