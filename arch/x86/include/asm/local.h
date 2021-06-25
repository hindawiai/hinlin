<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_LOCAL_H
#घोषणा _ASM_X86_LOCAL_H

#समावेश <linux/percpu.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/यंत्र.h>

प्रकार काष्ठा अणु
	atomic_दीर्घ_t a;
पूर्ण local_t;

#घोषणा LOCAL_INIT(i)	अणु ATOMIC_LONG_INIT(i) पूर्ण

#घोषणा local_पढ़ो(l)	atomic_दीर्घ_पढ़ो(&(l)->a)
#घोषणा local_set(l, i)	atomic_दीर्घ_set(&(l)->a, (i))

अटल अंतरभूत व्योम local_inc(local_t *l)
अणु
	यंत्र अस्थिर(_ASM_INC "%0"
		     : "+m" (l->a.counter));
पूर्ण

अटल अंतरभूत व्योम local_dec(local_t *l)
अणु
	यंत्र अस्थिर(_ASM_DEC "%0"
		     : "+m" (l->a.counter));
पूर्ण

अटल अंतरभूत व्योम local_add(दीर्घ i, local_t *l)
अणु
	यंत्र अस्थिर(_ASM_ADD "%1,%0"
		     : "+m" (l->a.counter)
		     : "ir" (i));
पूर्ण

अटल अंतरभूत व्योम local_sub(दीर्घ i, local_t *l)
अणु
	यंत्र अस्थिर(_ASM_SUB "%1,%0"
		     : "+m" (l->a.counter)
		     : "ir" (i));
पूर्ण

/**
 * local_sub_and_test - subtract value from variable and test result
 * @i: पूर्णांकeger value to subtract
 * @l: poपूर्णांकer to type local_t
 *
 * Atomically subtracts @i from @l and वापसs
 * true अगर the result is zero, or false क्रम all
 * other हालs.
 */
अटल अंतरभूत bool local_sub_and_test(दीर्घ i, local_t *l)
अणु
	वापस GEN_BINARY_RMWcc(_ASM_SUB, l->a.counter, e, "er", i);
पूर्ण

/**
 * local_dec_and_test - decrement and test
 * @l: poपूर्णांकer to type local_t
 *
 * Atomically decrements @l by 1 and
 * वापसs true अगर the result is 0, or false क्रम all other
 * हालs.
 */
अटल अंतरभूत bool local_dec_and_test(local_t *l)
अणु
	वापस GEN_UNARY_RMWcc(_ASM_DEC, l->a.counter, e);
पूर्ण

/**
 * local_inc_and_test - increment and test
 * @l: poपूर्णांकer to type local_t
 *
 * Atomically increments @l by 1
 * and वापसs true अगर the result is zero, or false क्रम all
 * other हालs.
 */
अटल अंतरभूत bool local_inc_and_test(local_t *l)
अणु
	वापस GEN_UNARY_RMWcc(_ASM_INC, l->a.counter, e);
पूर्ण

/**
 * local_add_negative - add and test अगर negative
 * @i: पूर्णांकeger value to add
 * @l: poपूर्णांकer to type local_t
 *
 * Atomically adds @i to @l and वापसs true
 * अगर the result is negative, or false when
 * result is greater than or equal to zero.
 */
अटल अंतरभूत bool local_add_negative(दीर्घ i, local_t *l)
अणु
	वापस GEN_BINARY_RMWcc(_ASM_ADD, l->a.counter, s, "er", i);
पूर्ण

/**
 * local_add_वापस - add and वापस
 * @i: पूर्णांकeger value to add
 * @l: poपूर्णांकer to type local_t
 *
 * Atomically adds @i to @l and वापसs @i + @l
 */
अटल अंतरभूत दीर्घ local_add_वापस(दीर्घ i, local_t *l)
अणु
	दीर्घ __i = i;
	यंत्र अस्थिर(_ASM_XADD "%0, %1;"
		     : "+r" (i), "+m" (l->a.counter)
		     : : "memory");
	वापस i + __i;
पूर्ण

अटल अंतरभूत दीर्घ local_sub_वापस(दीर्घ i, local_t *l)
अणु
	वापस local_add_वापस(-i, l);
पूर्ण

#घोषणा local_inc_वापस(l)  (local_add_वापस(1, l))
#घोषणा local_dec_वापस(l)  (local_sub_वापस(1, l))

#घोषणा local_cmpxchg(l, o, n) \
	(cmpxchg_local(&((l)->a.counter), (o), (n)))
/* Always has a lock prefix */
#घोषणा local_xchg(l, n) (xchg(&((l)->a.counter), (n)))

/**
 * local_add_unless - add unless the number is a given value
 * @l: poपूर्णांकer of type local_t
 * @a: the amount to add to l...
 * @u: ...unless l is equal to u.
 *
 * Atomically adds @a to @l, so दीर्घ as it was not @u.
 * Returns non-zero अगर @l was not @u, and zero otherwise.
 */
#घोषणा local_add_unless(l, a, u)				\
(अणु								\
	दीर्घ c, old;						\
	c = local_पढ़ो((l));					\
	क्रम (;;) अणु						\
		अगर (unlikely(c == (u)))				\
			अवरोध;					\
		old = local_cmpxchg((l), c, c + (a));		\
		अगर (likely(old == c))				\
			अवरोध;					\
		c = old;					\
	पूर्ण							\
	c != (u);						\
पूर्ण)
#घोषणा local_inc_not_zero(l) local_add_unless((l), 1, 0)

/* On x86_32, these are no better than the atomic variants.
 * On x86-64 these are better than the atomic variants on SMP kernels
 * because they करोnt use a lock prefix.
 */
#घोषणा __local_inc(l)		local_inc(l)
#घोषणा __local_dec(l)		local_dec(l)
#घोषणा __local_add(i, l)	local_add((i), (l))
#घोषणा __local_sub(i, l)	local_sub((i), (l))

#पूर्ण_अगर /* _ASM_X86_LOCAL_H */
