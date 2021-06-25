<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Generic implementation of 64-bit atomics using spinlocks,
 * useful on processors that करोn't have 64-bit atomic inकाष्ठाions.
 *
 * Copyright तऊ 2009 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */
#अगर_अघोषित _ASM_GENERIC_ATOMIC64_H
#घोषणा _ASM_GENERIC_ATOMIC64_H
#समावेश <linux/types.h>

प्रकार काष्ठा अणु
	s64 counter;
पूर्ण atomic64_t;

#घोषणा ATOMIC64_INIT(i)	अणु (i) पूर्ण

बाह्य s64 atomic64_पढ़ो(स्थिर atomic64_t *v);
बाह्य व्योम atomic64_set(atomic64_t *v, s64 i);

#घोषणा atomic64_set_release(v, i)	atomic64_set((v), (i))

#घोषणा ATOMIC64_OP(op)							\
बाह्य व्योम	 atomic64_##op(s64 a, atomic64_t *v);

#घोषणा ATOMIC64_OP_RETURN(op)						\
बाह्य s64 atomic64_##op##_वापस(s64 a, atomic64_t *v);

#घोषणा ATOMIC64_FETCH_OP(op)						\
बाह्य s64 atomic64_fetch_##op(s64 a, atomic64_t *v);

#घोषणा ATOMIC64_OPS(op)	ATOMIC64_OP(op) ATOMIC64_OP_RETURN(op) ATOMIC64_FETCH_OP(op)

ATOMIC64_OPS(add)
ATOMIC64_OPS(sub)

#अघोषित ATOMIC64_OPS
#घोषणा ATOMIC64_OPS(op)	ATOMIC64_OP(op) ATOMIC64_FETCH_OP(op)

ATOMIC64_OPS(and)
ATOMIC64_OPS(or)
ATOMIC64_OPS(xor)

#अघोषित ATOMIC64_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP_RETURN
#अघोषित ATOMIC64_OP

बाह्य s64 atomic64_dec_अगर_positive(atomic64_t *v);
#घोषणा atomic64_dec_अगर_positive atomic64_dec_अगर_positive
बाह्य s64 atomic64_cmpxchg(atomic64_t *v, s64 o, s64 n);
बाह्य s64 atomic64_xchg(atomic64_t *v, s64 new);
बाह्य s64 atomic64_fetch_add_unless(atomic64_t *v, s64 a, s64 u);
#घोषणा atomic64_fetch_add_unless atomic64_fetch_add_unless

#पूर्ण_अगर  /*  _ASM_GENERIC_ATOMIC64_H  */
