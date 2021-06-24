<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ATOMIC64_64_H
#घोषणा _ASM_X86_ATOMIC64_64_H

#समावेश <linux/types.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cmpxchg.h>

/* The 64-bit atomic type */

#घोषणा ATOMIC64_INIT(i)	अणु (i) पूर्ण

/**
 * arch_atomic64_पढ़ो - पढ़ो atomic64 variable
 * @v: poपूर्णांकer of type atomic64_t
 *
 * Atomically पढ़ोs the value of @v.
 * Doesn't imply a पढ़ो memory barrier.
 */
अटल अंतरभूत s64 arch_atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	वापस __READ_ONCE((v)->counter);
पूर्ण

/**
 * arch_atomic64_set - set atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
अटल अंतरभूत व्योम arch_atomic64_set(atomic64_t *v, s64 i)
अणु
	__WRITE_ONCE(v->counter, i);
पूर्ण

/**
 * arch_atomic64_add - add पूर्णांकeger to atomic64 variable
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically adds @i to @v.
 */
अटल __always_अंतरभूत व्योम arch_atomic64_add(s64 i, atomic64_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "addq %1,%0"
		     : "=m" (v->counter)
		     : "er" (i), "m" (v->counter) : "memory");
पूर्ण

/**
 * arch_atomic64_sub - subtract the atomic64 variable
 * @i: पूर्णांकeger value to subtract
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically subtracts @i from @v.
 */
अटल अंतरभूत व्योम arch_atomic64_sub(s64 i, atomic64_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "subq %1,%0"
		     : "=m" (v->counter)
		     : "er" (i), "m" (v->counter) : "memory");
पूर्ण

/**
 * arch_atomic64_sub_and_test - subtract value from variable and test result
 * @i: पूर्णांकeger value to subtract
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically subtracts @i from @v and वापसs
 * true अगर the result is zero, or false क्रम all
 * other हालs.
 */
अटल अंतरभूत bool arch_atomic64_sub_and_test(s64 i, atomic64_t *v)
अणु
	वापस GEN_BINARY_RMWcc(LOCK_PREFIX "subq", v->counter, e, "er", i);
पूर्ण
#घोषणा arch_atomic64_sub_and_test arch_atomic64_sub_and_test

/**
 * arch_atomic64_inc - increment atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically increments @v by 1.
 */
अटल __always_अंतरभूत व्योम arch_atomic64_inc(atomic64_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "incq %0"
		     : "=m" (v->counter)
		     : "m" (v->counter) : "memory");
पूर्ण
#घोषणा arch_atomic64_inc arch_atomic64_inc

/**
 * arch_atomic64_dec - decrement atomic64 variable
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically decrements @v by 1.
 */
अटल __always_अंतरभूत व्योम arch_atomic64_dec(atomic64_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "decq %0"
		     : "=m" (v->counter)
		     : "m" (v->counter) : "memory");
पूर्ण
#घोषणा arch_atomic64_dec arch_atomic64_dec

/**
 * arch_atomic64_dec_and_test - decrement and test
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically decrements @v by 1 and
 * वापसs true अगर the result is 0, or false क्रम all other
 * हालs.
 */
अटल अंतरभूत bool arch_atomic64_dec_and_test(atomic64_t *v)
अणु
	वापस GEN_UNARY_RMWcc(LOCK_PREFIX "decq", v->counter, e);
पूर्ण
#घोषणा arch_atomic64_dec_and_test arch_atomic64_dec_and_test

/**
 * arch_atomic64_inc_and_test - increment and test
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically increments @v by 1
 * and वापसs true अगर the result is zero, or false क्रम all
 * other हालs.
 */
अटल अंतरभूत bool arch_atomic64_inc_and_test(atomic64_t *v)
अणु
	वापस GEN_UNARY_RMWcc(LOCK_PREFIX "incq", v->counter, e);
पूर्ण
#घोषणा arch_atomic64_inc_and_test arch_atomic64_inc_and_test

/**
 * arch_atomic64_add_negative - add and test अगर negative
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically adds @i to @v and वापसs true
 * अगर the result is negative, or false when
 * result is greater than or equal to zero.
 */
अटल अंतरभूत bool arch_atomic64_add_negative(s64 i, atomic64_t *v)
अणु
	वापस GEN_BINARY_RMWcc(LOCK_PREFIX "addq", v->counter, s, "er", i);
पूर्ण
#घोषणा arch_atomic64_add_negative arch_atomic64_add_negative

/**
 * arch_atomic64_add_वापस - add and वापस
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer to type atomic64_t
 *
 * Atomically adds @i to @v and वापसs @i + @v
 */
अटल __always_अंतरभूत s64 arch_atomic64_add_वापस(s64 i, atomic64_t *v)
अणु
	वापस i + xadd(&v->counter, i);
पूर्ण
#घोषणा arch_atomic64_add_वापस arch_atomic64_add_वापस

अटल अंतरभूत s64 arch_atomic64_sub_वापस(s64 i, atomic64_t *v)
अणु
	वापस arch_atomic64_add_वापस(-i, v);
पूर्ण
#घोषणा arch_atomic64_sub_वापस arch_atomic64_sub_वापस

अटल अंतरभूत s64 arch_atomic64_fetch_add(s64 i, atomic64_t *v)
अणु
	वापस xadd(&v->counter, i);
पूर्ण
#घोषणा arch_atomic64_fetch_add arch_atomic64_fetch_add

अटल अंतरभूत s64 arch_atomic64_fetch_sub(s64 i, atomic64_t *v)
अणु
	वापस xadd(&v->counter, -i);
पूर्ण
#घोषणा arch_atomic64_fetch_sub arch_atomic64_fetch_sub

अटल अंतरभूत s64 arch_atomic64_cmpxchg(atomic64_t *v, s64 old, s64 new)
अणु
	वापस arch_cmpxchg(&v->counter, old, new);
पूर्ण
#घोषणा arch_atomic64_cmpxchg arch_atomic64_cmpxchg

अटल __always_अंतरभूत bool arch_atomic64_try_cmpxchg(atomic64_t *v, s64 *old, s64 new)
अणु
	वापस arch_try_cmpxchg(&v->counter, old, new);
पूर्ण
#घोषणा arch_atomic64_try_cmpxchg arch_atomic64_try_cmpxchg

अटल अंतरभूत s64 arch_atomic64_xchg(atomic64_t *v, s64 new)
अणु
	वापस arch_xchg(&v->counter, new);
पूर्ण
#घोषणा arch_atomic64_xchg arch_atomic64_xchg

अटल अंतरभूत व्योम arch_atomic64_and(s64 i, atomic64_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "andq %1,%0"
			: "+m" (v->counter)
			: "er" (i)
			: "memory");
पूर्ण

अटल अंतरभूत s64 arch_atomic64_fetch_and(s64 i, atomic64_t *v)
अणु
	s64 val = arch_atomic64_पढ़ो(v);

	करो अणु
	पूर्ण जबतक (!arch_atomic64_try_cmpxchg(v, &val, val & i));
	वापस val;
पूर्ण
#घोषणा arch_atomic64_fetch_and arch_atomic64_fetch_and

अटल अंतरभूत व्योम arch_atomic64_or(s64 i, atomic64_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "orq %1,%0"
			: "+m" (v->counter)
			: "er" (i)
			: "memory");
पूर्ण

अटल अंतरभूत s64 arch_atomic64_fetch_or(s64 i, atomic64_t *v)
अणु
	s64 val = arch_atomic64_पढ़ो(v);

	करो अणु
	पूर्ण जबतक (!arch_atomic64_try_cmpxchg(v, &val, val | i));
	वापस val;
पूर्ण
#घोषणा arch_atomic64_fetch_or arch_atomic64_fetch_or

अटल अंतरभूत व्योम arch_atomic64_xor(s64 i, atomic64_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "xorq %1,%0"
			: "+m" (v->counter)
			: "er" (i)
			: "memory");
पूर्ण

अटल अंतरभूत s64 arch_atomic64_fetch_xor(s64 i, atomic64_t *v)
अणु
	s64 val = arch_atomic64_पढ़ो(v);

	करो अणु
	पूर्ण जबतक (!arch_atomic64_try_cmpxchg(v, &val, val ^ i));
	वापस val;
पूर्ण
#घोषणा arch_atomic64_fetch_xor arch_atomic64_fetch_xor

#पूर्ण_अगर /* _ASM_X86_ATOMIC64_64_H */
