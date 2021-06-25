<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* atomic.h: These still suck, but the I-cache hit rate is higher.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 2000 Anton Blanअक्षरd (anton@linuxcare.com.au)
 * Copyright (C) 2007 Kyle McMartin (kyle@parisc-linux.org)
 *
 * Additions by Keith M Wesolowski (wesolows@foobazco.org) based
 * on यंत्र-parisc/atomic.h Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>.
 */

#अगर_अघोषित __ARCH_SPARC_ATOMIC__
#घोषणा __ARCH_SPARC_ATOMIC__

#समावेश <linux/types.h>

#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र-generic/atomic64.h>

पूर्णांक atomic_add_वापस(पूर्णांक, atomic_t *);
पूर्णांक atomic_fetch_add(पूर्णांक, atomic_t *);
पूर्णांक atomic_fetch_and(पूर्णांक, atomic_t *);
पूर्णांक atomic_fetch_or(पूर्णांक, atomic_t *);
पूर्णांक atomic_fetch_xor(पूर्णांक, atomic_t *);
पूर्णांक atomic_cmpxchg(atomic_t *, पूर्णांक, पूर्णांक);
पूर्णांक atomic_xchg(atomic_t *, पूर्णांक);
पूर्णांक atomic_fetch_add_unless(atomic_t *, पूर्णांक, पूर्णांक);
व्योम atomic_set(atomic_t *, पूर्णांक);

#घोषणा atomic_fetch_add_unless	atomic_fetch_add_unless

#घोषणा atomic_set_release(v, i)	atomic_set((v), (i))

#घोषणा atomic_पढ़ो(v)          READ_ONCE((v)->counter)

#घोषणा atomic_add(i, v)	((व्योम)atomic_add_वापस( (पूर्णांक)(i), (v)))
#घोषणा atomic_sub(i, v)	((व्योम)atomic_add_वापस(-(पूर्णांक)(i), (v)))

#घोषणा atomic_and(i, v)	((व्योम)atomic_fetch_and((i), (v)))
#घोषणा atomic_or(i, v)		((व्योम)atomic_fetch_or((i), (v)))
#घोषणा atomic_xor(i, v)	((व्योम)atomic_fetch_xor((i), (v)))

#घोषणा atomic_sub_वापस(i, v)	(atomic_add_वापस(-(पूर्णांक)(i), (v)))
#घोषणा atomic_fetch_sub(i, v)  (atomic_fetch_add (-(पूर्णांक)(i), (v)))

#पूर्ण_अगर /* !(__ARCH_SPARC_ATOMIC__) */
