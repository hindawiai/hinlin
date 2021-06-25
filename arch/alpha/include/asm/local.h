<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_LOCAL_H
#घोषणा _ALPHA_LOCAL_H

#समावेश <linux/percpu.h>
#समावेश <linux/atomic.h>

प्रकार काष्ठा
अणु
	atomic_दीर्घ_t a;
पूर्ण local_t;

#घोषणा LOCAL_INIT(i)	अणु ATOMIC_LONG_INIT(i) पूर्ण
#घोषणा local_पढ़ो(l)	atomic_दीर्घ_पढ़ो(&(l)->a)
#घोषणा local_set(l,i)	atomic_दीर्घ_set(&(l)->a, (i))
#घोषणा local_inc(l)	atomic_दीर्घ_inc(&(l)->a)
#घोषणा local_dec(l)	atomic_दीर्घ_dec(&(l)->a)
#घोषणा local_add(i,l)	atomic_दीर्घ_add((i),(&(l)->a))
#घोषणा local_sub(i,l)	atomic_दीर्घ_sub((i),(&(l)->a))

अटल __अंतरभूत__ दीर्घ local_add_वापस(दीर्घ i, local_t * l)
अणु
	दीर्घ temp, result;
	__यंत्र__ __अस्थिर__(
	"1:	ldq_l %0,%1\n"
	"	addq %0,%3,%2\n"
	"	addq %0,%3,%0\n"
	"	stq_c %0,%1\n"
	"	beq %0,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (l->a.counter), "=&r" (result)
	:"Ir" (i), "m" (l->a.counter) : "memory");
	वापस result;
पूर्ण

अटल __अंतरभूत__ दीर्घ local_sub_वापस(दीर्घ i, local_t * l)
अणु
	दीर्घ temp, result;
	__यंत्र__ __अस्थिर__(
	"1:	ldq_l %0,%1\n"
	"	subq %0,%3,%2\n"
	"	subq %0,%3,%0\n"
	"	stq_c %0,%1\n"
	"	beq %0,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (l->a.counter), "=&r" (result)
	:"Ir" (i), "m" (l->a.counter) : "memory");
	वापस result;
पूर्ण

#घोषणा local_cmpxchg(l, o, n) \
	(cmpxchg_local(&((l)->a.counter), (o), (n)))
#घोषणा local_xchg(l, n) (xchg_local(&((l)->a.counter), (n)))

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
	क्रम (;;) अणु						\
		अगर (unlikely(c == (u)))				\
			अवरोध;					\
		old = local_cmpxchg((l), c, c + (a));	\
		अगर (likely(old == c))				\
			अवरोध;					\
		c = old;					\
	पूर्ण							\
	c != (u);						\
पूर्ण)
#घोषणा local_inc_not_zero(l) local_add_unless((l), 1, 0)

#घोषणा local_add_negative(a, l) (local_add_वापस((a), (l)) < 0)

#घोषणा local_dec_वापस(l) local_sub_वापस(1,(l))

#घोषणा local_inc_वापस(l) local_add_वापस(1,(l))

#घोषणा local_sub_and_test(i,l) (local_sub_वापस((i), (l)) == 0)

#घोषणा local_inc_and_test(l) (local_add_वापस(1, (l)) == 0)

#घोषणा local_dec_and_test(l) (local_sub_वापस(1, (l)) == 0)

/* Verअगरy अगर faster than atomic ops */
#घोषणा __local_inc(l)		((l)->a.counter++)
#घोषणा __local_dec(l)		((l)->a.counter++)
#घोषणा __local_add(i,l)	((l)->a.counter+=(i))
#घोषणा __local_sub(i,l)	((l)->a.counter-=(i))

#पूर्ण_अगर /* _ALPHA_LOCAL_H */
