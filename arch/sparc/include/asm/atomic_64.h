<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* atomic.h: Thankfully the V9 is at least reasonable क्रम this
 *           stuff.
 *
 * Copyright (C) 1996, 1997, 2000, 2012 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित __ARCH_SPARC64_ATOMIC__
#घोषणा __ARCH_SPARC64_ATOMIC__

#समावेश <linux/types.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

#घोषणा ATOMIC64_INIT(i)	अणु (i) पूर्ण

#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)
#घोषणा atomic64_पढ़ो(v)	READ_ONCE((v)->counter)

#घोषणा atomic_set(v, i)	WRITE_ONCE(((v)->counter), (i))
#घोषणा atomic64_set(v, i)	WRITE_ONCE(((v)->counter), (i))

#घोषणा ATOMIC_OP(op)							\
व्योम atomic_##op(पूर्णांक, atomic_t *);					\
व्योम atomic64_##op(s64, atomic64_t *);

#घोषणा ATOMIC_OP_RETURN(op)						\
पूर्णांक atomic_##op##_वापस(पूर्णांक, atomic_t *);				\
s64 atomic64_##op##_वापस(s64, atomic64_t *);

#घोषणा ATOMIC_FETCH_OP(op)						\
पूर्णांक atomic_fetch_##op(पूर्णांक, atomic_t *);					\
s64 atomic64_fetch_##op(s64, atomic64_t *);

#घोषणा ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_OP_RETURN(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS(or)
ATOMIC_OPS(xor)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#घोषणा atomic_cmpxchg(v, o, n) (cmpxchg(&((v)->counter), (o), (n)))

अटल अंतरभूत पूर्णांक atomic_xchg(atomic_t *v, पूर्णांक new)
अणु
	वापस xchg(&v->counter, new);
पूर्ण

#घोषणा atomic64_cmpxchg(v, o, n) \
	((__typeof__((v)->counter))cmpxchg(&((v)->counter), (o), (n)))
#घोषणा atomic64_xchg(v, new) (xchg(&((v)->counter), new))

s64 atomic64_dec_अगर_positive(atomic64_t *v);
#घोषणा atomic64_dec_अगर_positive atomic64_dec_अगर_positive

#पूर्ण_अगर /* !(__ARCH_SPARC64_ATOMIC__) */
