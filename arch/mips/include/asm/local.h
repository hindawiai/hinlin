<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_MIPS_LOCAL_H
#घोषणा _ARCH_MIPS_LOCAL_H

#समावेश <linux/percpu.h>
#समावेश <linux/bitops.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/war.h>

प्रकार काष्ठा
अणु
	atomic_दीर्घ_t a;
पूर्ण local_t;

#घोषणा LOCAL_INIT(i)	अणु ATOMIC_LONG_INIT(i) पूर्ण

#घोषणा local_पढ़ो(l)	atomic_दीर्घ_पढ़ो(&(l)->a)
#घोषणा local_set(l, i) atomic_दीर्घ_set(&(l)->a, (i))

#घोषणा local_add(i, l) atomic_दीर्घ_add((i), (&(l)->a))
#घोषणा local_sub(i, l) atomic_दीर्घ_sub((i), (&(l)->a))
#घोषणा local_inc(l)	atomic_दीर्घ_inc(&(l)->a)
#घोषणा local_dec(l)	atomic_दीर्घ_dec(&(l)->a)

/*
 * Same as above, but वापस the result value
 */
अटल __अंतरभूत__ दीर्घ local_add_वापस(दीर्घ i, local_t * l)
अणु
	अचिन्हित दीर्घ result;

	अगर (kernel_uses_llsc && IS_ENABLED(CONFIG_WAR_R10000_LLSC)) अणु
		अचिन्हित दीर्घ temp;

		__यंत्र__ __अस्थिर__(
		"	.set	push					\n"
		"	.set	arch=r4000				\n"
			__SYNC(full, loongson3_war) "			\n"
		"1:"	__LL	"%1, %2		# local_add_return	\n"
		"	addu	%0, %1, %3				\n"
			__SC	"%0, %2					\n"
		"	beqzl	%0, 1b					\n"
		"	addu	%0, %1, %3				\n"
		"	.set	pop					\n"
		: "=&r" (result), "=&r" (temp), "=m" (l->a.counter)
		: "Ir" (i), "m" (l->a.counter)
		: "memory");
	पूर्ण अन्यथा अगर (kernel_uses_llsc) अणु
		अचिन्हित दीर्घ temp;

		__यंत्र__ __अस्थिर__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"			\n"
			__SYNC(full, loongson3_war) "			\n"
		"1:"	__LL	"%1, %2		# local_add_return	\n"
		"	addu	%0, %1, %3				\n"
			__SC	"%0, %2					\n"
		"	beqz	%0, 1b					\n"
		"	addu	%0, %1, %3				\n"
		"	.set	pop					\n"
		: "=&r" (result), "=&r" (temp), "=m" (l->a.counter)
		: "Ir" (i), "m" (l->a.counter)
		: "memory");
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		result = l->a.counter;
		result += i;
		l->a.counter = result;
		local_irq_restore(flags);
	पूर्ण

	वापस result;
पूर्ण

अटल __अंतरभूत__ दीर्घ local_sub_वापस(दीर्घ i, local_t * l)
अणु
	अचिन्हित दीर्घ result;

	अगर (kernel_uses_llsc && IS_ENABLED(CONFIG_WAR_R10000_LLSC)) अणु
		अचिन्हित दीर्घ temp;

		__यंत्र__ __अस्थिर__(
		"	.set	push					\n"
		"	.set	arch=r4000				\n"
			__SYNC(full, loongson3_war) "			\n"
		"1:"	__LL	"%1, %2		# local_sub_return	\n"
		"	subu	%0, %1, %3				\n"
			__SC	"%0, %2					\n"
		"	beqzl	%0, 1b					\n"
		"	subu	%0, %1, %3				\n"
		"	.set	pop					\n"
		: "=&r" (result), "=&r" (temp), "=m" (l->a.counter)
		: "Ir" (i), "m" (l->a.counter)
		: "memory");
	पूर्ण अन्यथा अगर (kernel_uses_llsc) अणु
		अचिन्हित दीर्घ temp;

		__यंत्र__ __अस्थिर__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"			\n"
			__SYNC(full, loongson3_war) "			\n"
		"1:"	__LL	"%1, %2		# local_sub_return	\n"
		"	subu	%0, %1, %3				\n"
			__SC	"%0, %2					\n"
		"	beqz	%0, 1b					\n"
		"	subu	%0, %1, %3				\n"
		"	.set	pop					\n"
		: "=&r" (result), "=&r" (temp), "=m" (l->a.counter)
		: "Ir" (i), "m" (l->a.counter)
		: "memory");
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		result = l->a.counter;
		result -= i;
		l->a.counter = result;
		local_irq_restore(flags);
	पूर्ण

	वापस result;
पूर्ण

#घोषणा local_cmpxchg(l, o, n) \
	((दीर्घ)cmpxchg_local(&((l)->a.counter), (o), (n)))
#घोषणा local_xchg(l, n) (atomic_दीर्घ_xchg((&(l)->a), (n)))

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
	c = local_पढ़ो(l);					\
	जबतक (c != (u) && (old = local_cmpxchg((l), c, c + (a))) != c) \
		c = old;					\
	c != (u);						\
पूर्ण)
#घोषणा local_inc_not_zero(l) local_add_unless((l), 1, 0)

#घोषणा local_dec_वापस(l) local_sub_वापस(1, (l))
#घोषणा local_inc_वापस(l) local_add_वापस(1, (l))

/*
 * local_sub_and_test - subtract value from variable and test result
 * @i: पूर्णांकeger value to subtract
 * @l: poपूर्णांकer of type local_t
 *
 * Atomically subtracts @i from @l and वापसs
 * true अगर the result is zero, or false क्रम all
 * other हालs.
 */
#घोषणा local_sub_and_test(i, l) (local_sub_वापस((i), (l)) == 0)

/*
 * local_inc_and_test - increment and test
 * @l: poपूर्णांकer of type local_t
 *
 * Atomically increments @l by 1
 * and वापसs true अगर the result is zero, or false क्रम all
 * other हालs.
 */
#घोषणा local_inc_and_test(l) (local_inc_वापस(l) == 0)

/*
 * local_dec_and_test - decrement by 1 and test
 * @l: poपूर्णांकer of type local_t
 *
 * Atomically decrements @l by 1 and
 * वापसs true अगर the result is 0, or false क्रम all other
 * हालs.
 */
#घोषणा local_dec_and_test(l) (local_sub_वापस(1, (l)) == 0)

/*
 * local_add_negative - add and test अगर negative
 * @l: poपूर्णांकer of type local_t
 * @i: पूर्णांकeger value to add
 *
 * Atomically adds @i to @l and वापसs true
 * अगर the result is negative, or false when
 * result is greater than or equal to zero.
 */
#घोषणा local_add_negative(i, l) (local_add_वापस(i, (l)) < 0)

/* Use these क्रम per-cpu local_t variables: on some archs they are
 * much more efficient than these naive implementations.  Note they take
 * a variable, not an address.
 */

#घोषणा __local_inc(l)		((l)->a.counter++)
#घोषणा __local_dec(l)		((l)->a.counter++)
#घोषणा __local_add(i, l)	((l)->a.counter+=(i))
#घोषणा __local_sub(i, l)	((l)->a.counter-=(i))

#पूर्ण_अगर /* _ARCH_MIPS_LOCAL_H */
