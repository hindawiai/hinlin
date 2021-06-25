<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ATOMIC_H
#घोषणा _ASM_X86_ATOMIC_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/rmwcc.h>
#समावेश <यंत्र/barrier.h>

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 */

/**
 * arch_atomic_पढ़ो - पढ़ो atomic variable
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically पढ़ोs the value of @v.
 */
अटल __always_अंतरभूत पूर्णांक arch_atomic_पढ़ो(स्थिर atomic_t *v)
अणु
	/*
	 * Note क्रम KASAN: we deliberately करोn't use READ_ONCE_NOCHECK() here,
	 * it's non-अंतरभूतd function that increases binary size and stack usage.
	 */
	वापस __READ_ONCE((v)->counter);
पूर्ण

/**
 * arch_atomic_set - set atomic variable
 * @v: poपूर्णांकer of type atomic_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
अटल __always_अंतरभूत व्योम arch_atomic_set(atomic_t *v, पूर्णांक i)
अणु
	__WRITE_ONCE(v->counter, i);
पूर्ण

/**
 * arch_atomic_add - add पूर्णांकeger to atomic variable
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically adds @i to @v.
 */
अटल __always_अंतरभूत व्योम arch_atomic_add(पूर्णांक i, atomic_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "addl %1,%0"
		     : "+m" (v->counter)
		     : "ir" (i) : "memory");
पूर्ण

/**
 * arch_atomic_sub - subtract पूर्णांकeger from atomic variable
 * @i: पूर्णांकeger value to subtract
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically subtracts @i from @v.
 */
अटल __always_अंतरभूत व्योम arch_atomic_sub(पूर्णांक i, atomic_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "subl %1,%0"
		     : "+m" (v->counter)
		     : "ir" (i) : "memory");
पूर्ण

/**
 * arch_atomic_sub_and_test - subtract value from variable and test result
 * @i: पूर्णांकeger value to subtract
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically subtracts @i from @v and वापसs
 * true अगर the result is zero, or false क्रम all
 * other हालs.
 */
अटल __always_अंतरभूत bool arch_atomic_sub_and_test(पूर्णांक i, atomic_t *v)
अणु
	वापस GEN_BINARY_RMWcc(LOCK_PREFIX "subl", v->counter, e, "er", i);
पूर्ण
#घोषणा arch_atomic_sub_and_test arch_atomic_sub_and_test

/**
 * arch_atomic_inc - increment atomic variable
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically increments @v by 1.
 */
अटल __always_अंतरभूत व्योम arch_atomic_inc(atomic_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "incl %0"
		     : "+m" (v->counter) :: "memory");
पूर्ण
#घोषणा arch_atomic_inc arch_atomic_inc

/**
 * arch_atomic_dec - decrement atomic variable
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically decrements @v by 1.
 */
अटल __always_अंतरभूत व्योम arch_atomic_dec(atomic_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "decl %0"
		     : "+m" (v->counter) :: "memory");
पूर्ण
#घोषणा arch_atomic_dec arch_atomic_dec

/**
 * arch_atomic_dec_and_test - decrement and test
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically decrements @v by 1 and
 * वापसs true अगर the result is 0, or false क्रम all other
 * हालs.
 */
अटल __always_अंतरभूत bool arch_atomic_dec_and_test(atomic_t *v)
अणु
	वापस GEN_UNARY_RMWcc(LOCK_PREFIX "decl", v->counter, e);
पूर्ण
#घोषणा arch_atomic_dec_and_test arch_atomic_dec_and_test

/**
 * arch_atomic_inc_and_test - increment and test
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically increments @v by 1
 * and वापसs true अगर the result is zero, or false क्रम all
 * other हालs.
 */
अटल __always_अंतरभूत bool arch_atomic_inc_and_test(atomic_t *v)
अणु
	वापस GEN_UNARY_RMWcc(LOCK_PREFIX "incl", v->counter, e);
पूर्ण
#घोषणा arch_atomic_inc_and_test arch_atomic_inc_and_test

/**
 * arch_atomic_add_negative - add and test अगर negative
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically adds @i to @v and वापसs true
 * अगर the result is negative, or false when
 * result is greater than or equal to zero.
 */
अटल __always_अंतरभूत bool arch_atomic_add_negative(पूर्णांक i, atomic_t *v)
अणु
	वापस GEN_BINARY_RMWcc(LOCK_PREFIX "addl", v->counter, s, "er", i);
पूर्ण
#घोषणा arch_atomic_add_negative arch_atomic_add_negative

/**
 * arch_atomic_add_वापस - add पूर्णांकeger and वापस
 * @i: पूर्णांकeger value to add
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically adds @i to @v and वापसs @i + @v
 */
अटल __always_अंतरभूत पूर्णांक arch_atomic_add_वापस(पूर्णांक i, atomic_t *v)
अणु
	वापस i + xadd(&v->counter, i);
पूर्ण
#घोषणा arch_atomic_add_वापस arch_atomic_add_वापस

/**
 * arch_atomic_sub_वापस - subtract पूर्णांकeger and वापस
 * @v: poपूर्णांकer of type atomic_t
 * @i: पूर्णांकeger value to subtract
 *
 * Atomically subtracts @i from @v and वापसs @v - @i
 */
अटल __always_अंतरभूत पूर्णांक arch_atomic_sub_वापस(पूर्णांक i, atomic_t *v)
अणु
	वापस arch_atomic_add_वापस(-i, v);
पूर्ण
#घोषणा arch_atomic_sub_वापस arch_atomic_sub_वापस

अटल __always_अंतरभूत पूर्णांक arch_atomic_fetch_add(पूर्णांक i, atomic_t *v)
अणु
	वापस xadd(&v->counter, i);
पूर्ण
#घोषणा arch_atomic_fetch_add arch_atomic_fetch_add

अटल __always_अंतरभूत पूर्णांक arch_atomic_fetch_sub(पूर्णांक i, atomic_t *v)
अणु
	वापस xadd(&v->counter, -i);
पूर्ण
#घोषणा arch_atomic_fetch_sub arch_atomic_fetch_sub

अटल __always_अंतरभूत पूर्णांक arch_atomic_cmpxchg(atomic_t *v, पूर्णांक old, पूर्णांक new)
अणु
	वापस arch_cmpxchg(&v->counter, old, new);
पूर्ण
#घोषणा arch_atomic_cmpxchg arch_atomic_cmpxchg

अटल __always_अंतरभूत bool arch_atomic_try_cmpxchg(atomic_t *v, पूर्णांक *old, पूर्णांक new)
अणु
	वापस arch_try_cmpxchg(&v->counter, old, new);
पूर्ण
#घोषणा arch_atomic_try_cmpxchg arch_atomic_try_cmpxchg

अटल __always_अंतरभूत पूर्णांक arch_atomic_xchg(atomic_t *v, पूर्णांक new)
अणु
	वापस arch_xchg(&v->counter, new);
पूर्ण
#घोषणा arch_atomic_xchg arch_atomic_xchg

अटल __always_अंतरभूत व्योम arch_atomic_and(पूर्णांक i, atomic_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "andl %1,%0"
			: "+m" (v->counter)
			: "ir" (i)
			: "memory");
पूर्ण

अटल __always_अंतरभूत पूर्णांक arch_atomic_fetch_and(पूर्णांक i, atomic_t *v)
अणु
	पूर्णांक val = arch_atomic_पढ़ो(v);

	करो अणु पूर्ण जबतक (!arch_atomic_try_cmpxchg(v, &val, val & i));

	वापस val;
पूर्ण
#घोषणा arch_atomic_fetch_and arch_atomic_fetch_and

अटल __always_अंतरभूत व्योम arch_atomic_or(पूर्णांक i, atomic_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "orl %1,%0"
			: "+m" (v->counter)
			: "ir" (i)
			: "memory");
पूर्ण

अटल __always_अंतरभूत पूर्णांक arch_atomic_fetch_or(पूर्णांक i, atomic_t *v)
अणु
	पूर्णांक val = arch_atomic_पढ़ो(v);

	करो अणु पूर्ण जबतक (!arch_atomic_try_cmpxchg(v, &val, val | i));

	वापस val;
पूर्ण
#घोषणा arch_atomic_fetch_or arch_atomic_fetch_or

अटल __always_अंतरभूत व्योम arch_atomic_xor(पूर्णांक i, atomic_t *v)
अणु
	यंत्र अस्थिर(LOCK_PREFIX "xorl %1,%0"
			: "+m" (v->counter)
			: "ir" (i)
			: "memory");
पूर्ण

अटल __always_अंतरभूत पूर्णांक arch_atomic_fetch_xor(पूर्णांक i, atomic_t *v)
अणु
	पूर्णांक val = arch_atomic_पढ़ो(v);

	करो अणु पूर्ण जबतक (!arch_atomic_try_cmpxchg(v, &val, val ^ i));

	वापस val;
पूर्ण
#घोषणा arch_atomic_fetch_xor arch_atomic_fetch_xor

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/atomic64_32.h>
#अन्यथा
# include <यंत्र/atomic64_64.h>
#पूर्ण_अगर

#घोषणा ARCH_ATOMIC

#पूर्ण_अगर /* _ASM_X86_ATOMIC_H */
