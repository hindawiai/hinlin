<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_ATOMIC_H_
#घोषणा _ASM_POWERPC_ATOMIC_H_

/*
 * PowerPC atomic operations
 */

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>

/*
 * Since *_वापस_relaxed and अणुcmpपूर्णxchg_relaxed are implemented with
 * a "bne-" inकाष्ठाion at the end, so an isync is enough as a acquire barrier
 * on the platक्रमm without lwsync.
 */
#घोषणा __atomic_acquire_fence()					\
	__यंत्र__ __अस्थिर__(PPC_ACQUIRE_BARRIER "" : : : "memory")

#घोषणा __atomic_release_fence()					\
	__यंत्र__ __अस्थिर__(PPC_RELEASE_BARRIER "" : : : "memory")

अटल __अंतरभूत__ पूर्णांक atomic_पढ़ो(स्थिर atomic_t *v)
अणु
	पूर्णांक t;

	__यंत्र__ __अस्थिर__("lwz%U1%X1 %0,%1" : "=r"(t) : "m"UPD_CONSTR(v->counter));

	वापस t;
पूर्ण

अटल __अंतरभूत__ व्योम atomic_set(atomic_t *v, पूर्णांक i)
अणु
	__यंत्र__ __अस्थिर__("stw%U0%X0 %1,%0" : "=m"UPD_CONSTR(v->counter) : "r"(i));
पूर्ण

#घोषणा ATOMIC_OP(op, यंत्र_op)						\
अटल __अंतरभूत__ व्योम atomic_##op(पूर्णांक a, atomic_t *v)			\
अणु									\
	पूर्णांक t;								\
									\
	__यंत्र__ __अस्थिर__(						\
"1:	lwarx	%0,0,%3		# atomic_" #op "\n"			\
	#यंत्र_op " %0,%2,%0\n"						\
"	stwcx.	%0,0,%3 \n"						\
"	bne-	1b\n"							\
	: "=&r" (t), "+m" (v->counter)					\
	: "r" (a), "r" (&v->counter)					\
	: "cc");							\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN_RELAXED(op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस_relaxed(पूर्णांक a, atomic_t *v)	\
अणु									\
	पूर्णांक t;								\
									\
	__यंत्र__ __अस्थिर__(						\
"1:	lwarx	%0,0,%3		# atomic_" #op "_return_relaxed\n"	\
	#यंत्र_op " %0,%2,%0\n"						\
"	stwcx.	%0,0,%3\n"						\
"	bne-	1b\n"							\
	: "=&r" (t), "+m" (v->counter)					\
	: "r" (a), "r" (&v->counter)					\
	: "cc");							\
									\
	वापस t;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP_RELAXED(op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op##_relaxed(पूर्णांक a, atomic_t *v)	\
अणु									\
	पूर्णांक res, t;							\
									\
	__यंत्र__ __अस्थिर__(						\
"1:	lwarx	%0,0,%4		# atomic_fetch_" #op "_relaxed\n"	\
	#यंत्र_op " %1,%3,%0\n"						\
"	stwcx.	%1,0,%4\n"						\
"	bne-	1b\n"							\
	: "=&r" (res), "=&r" (t), "+m" (v->counter)			\
	: "r" (a), "r" (&v->counter)					\
	: "cc");							\
									\
	वापस res;							\
पूर्ण

#घोषणा ATOMIC_OPS(op, यंत्र_op)						\
	ATOMIC_OP(op, यंत्र_op)						\
	ATOMIC_OP_RETURN_RELAXED(op, यंत्र_op)				\
	ATOMIC_FETCH_OP_RELAXED(op, यंत्र_op)

ATOMIC_OPS(add, add)
ATOMIC_OPS(sub, subf)

#घोषणा atomic_add_वापस_relaxed atomic_add_वापस_relaxed
#घोषणा atomic_sub_वापस_relaxed atomic_sub_वापस_relaxed

#घोषणा atomic_fetch_add_relaxed atomic_fetch_add_relaxed
#घोषणा atomic_fetch_sub_relaxed atomic_fetch_sub_relaxed

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op, यंत्र_op)						\
	ATOMIC_OP(op, यंत्र_op)						\
	ATOMIC_FETCH_OP_RELAXED(op, यंत्र_op)

ATOMIC_OPS(and, and)
ATOMIC_OPS(or, or)
ATOMIC_OPS(xor, xor)

#घोषणा atomic_fetch_and_relaxed atomic_fetch_and_relaxed
#घोषणा atomic_fetch_or_relaxed  atomic_fetch_or_relaxed
#घोषणा atomic_fetch_xor_relaxed atomic_fetch_xor_relaxed

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP_RELAXED
#अघोषित ATOMIC_OP_RETURN_RELAXED
#अघोषित ATOMIC_OP

अटल __अंतरभूत__ व्योम atomic_inc(atomic_t *v)
अणु
	पूर्णांक t;

	__यंत्र__ __अस्थिर__(
"1:	lwarx	%0,0,%2		# atomic_inc\न\
	addic	%0,%0,1\न"
"	stwcx.	%0,0,%2 \न\
	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");
पूर्ण
#घोषणा atomic_inc atomic_inc

अटल __अंतरभूत__ पूर्णांक atomic_inc_वापस_relaxed(atomic_t *v)
अणु
	पूर्णांक t;

	__यंत्र__ __अस्थिर__(
"1:	lwarx	%0,0,%2		# atomic_inc_return_relaxed\n"
"	addic	%0,%0,1\n"
"	stwcx.	%0,0,%2\n"
"	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");

	वापस t;
पूर्ण

अटल __अंतरभूत__ व्योम atomic_dec(atomic_t *v)
अणु
	पूर्णांक t;

	__यंत्र__ __अस्थिर__(
"1:	lwarx	%0,0,%2		# atomic_dec\न\
	addic	%0,%0,-1\न"
"	stwcx.	%0,0,%2\न\
	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");
पूर्ण
#घोषणा atomic_dec atomic_dec

अटल __अंतरभूत__ पूर्णांक atomic_dec_वापस_relaxed(atomic_t *v)
अणु
	पूर्णांक t;

	__यंत्र__ __अस्थिर__(
"1:	lwarx	%0,0,%2		# atomic_dec_return_relaxed\n"
"	addic	%0,%0,-1\n"
"	stwcx.	%0,0,%2\n"
"	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");

	वापस t;
पूर्ण

#घोषणा atomic_inc_वापस_relaxed atomic_inc_वापस_relaxed
#घोषणा atomic_dec_वापस_relaxed atomic_dec_वापस_relaxed

#घोषणा atomic_cmpxchg(v, o, n) (cmpxchg(&((v)->counter), (o), (n)))
#घोषणा atomic_cmpxchg_relaxed(v, o, n) \
	cmpxchg_relaxed(&((v)->counter), (o), (n))
#घोषणा atomic_cmpxchg_acquire(v, o, n) \
	cmpxchg_acquire(&((v)->counter), (o), (n))

#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))
#घोषणा atomic_xchg_relaxed(v, new) xchg_relaxed(&((v)->counter), (new))

/*
 * Don't want to override the generic atomic_try_cmpxchg_acquire, because
 * we add a lock hपूर्णांक to the lwarx, which may not be wanted क्रम the
 * _acquire हाल (and is not used by the other _acquire variants so it
 * would be a surprise).
 */
अटल __always_अंतरभूत bool
atomic_try_cmpxchg_lock(atomic_t *v, पूर्णांक *old, पूर्णांक new)
अणु
	पूर्णांक r, o = *old;

	__यंत्र__ __अस्थिर__ (
"1:\t"	PPC_LWARX(%0,0,%2,1) "	# atomic_try_cmpxchg_acquire	\n"
"	cmpw	0,%0,%3							\n"
"	bne-	2f							\n"
"	stwcx.	%4,0,%2							\n"
"	bne-	1b							\n"
"\t"	PPC_ACQUIRE_BARRIER "						\n"
"2:									\n"
	: "=&r" (r), "+m" (v->counter)
	: "r" (&v->counter), "r" (o), "r" (new)
	: "cr0", "memory");

	अगर (unlikely(r != o))
		*old = r;
	वापस likely(r == o);
पूर्ण

/**
 * atomic_fetch_add_unless - add unless the number is a given value
 * @v: poपूर्णांकer of type atomic_t
 * @a: the amount to add to v...
 * @u: ...unless v is equal to u.
 *
 * Atomically adds @a to @v, so दीर्घ as it was not @u.
 * Returns the old value of @v.
 */
अटल __अंतरभूत__ पूर्णांक atomic_fetch_add_unless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक t;

	__यंत्र__ __अस्थिर__ (
	PPC_ATOMIC_ENTRY_BARRIER
"1:	lwarx	%0,0,%1		# atomic_fetch_add_unless\न\
	cmpw	0,%0,%3 \न\
	beq	2f \न\
	add	%0,%2,%0 \न"
"	stwcx.	%0,0,%1 \न\
	bne-	1b \न"
	PPC_ATOMIC_EXIT_BARRIER
"	subf	%0,%2,%0 \न\
2:"
	: "=&r" (t)
	: "r" (&v->counter), "r" (a), "r" (u)
	: "cc", "memory");

	वापस t;
पूर्ण
#घोषणा atomic_fetch_add_unless atomic_fetch_add_unless

/**
 * atomic_inc_not_zero - increment unless the number is zero
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically increments @v by 1, so दीर्घ as @v is non-zero.
 * Returns non-zero अगर @v was non-zero, and zero otherwise.
 */
अटल __अंतरभूत__ पूर्णांक atomic_inc_not_zero(atomic_t *v)
अणु
	पूर्णांक t1, t2;

	__यंत्र__ __अस्थिर__ (
	PPC_ATOMIC_ENTRY_BARRIER
"1:	lwarx	%0,0,%2		# atomic_inc_not_zero\न\
	cmpwi	0,%0,0\न\
	beq-	2f\न\
	addic	%1,%0,1\न"
"	stwcx.	%1,0,%2\न\
	bne-	1b\न"
	PPC_ATOMIC_EXIT_BARRIER
	"\न\
2:"
	: "=&r" (t1), "=&r" (t2)
	: "r" (&v->counter)
	: "cc", "xer", "memory");

	वापस t1;
पूर्ण
#घोषणा atomic_inc_not_zero(v) atomic_inc_not_zero((v))

/*
 * Atomically test *v and decrement अगर it is greater than 0.
 * The function वापसs the old value of *v minus 1, even अगर
 * the atomic variable, v, was not decremented.
 */
अटल __अंतरभूत__ पूर्णांक atomic_dec_अगर_positive(atomic_t *v)
अणु
	पूर्णांक t;

	__यंत्र__ __अस्थिर__(
	PPC_ATOMIC_ENTRY_BARRIER
"1:	lwarx	%0,0,%1		# atomic_dec_अगर_positive\न\
	cmpwi	%0,1\न\
	addi	%0,%0,-1\न\
	blt-	2f\न"
"	stwcx.	%0,0,%1\न\
	bne-	1b"
	PPC_ATOMIC_EXIT_BARRIER
	"\न\
2:"	: "=&b" (t)
	: "r" (&v->counter)
	: "cc", "memory");

	वापस t;
पूर्ण
#घोषणा atomic_dec_अगर_positive atomic_dec_अगर_positive

#अगर_घोषित __घातerpc64__

#घोषणा ATOMIC64_INIT(i)	अणु (i) पूर्ण

अटल __अंतरभूत__ s64 atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	s64 t;

	__यंत्र__ __अस्थिर__("ld%U1%X1 %0,%1" : "=r"(t) : "m"UPD_CONSTR(v->counter));

	वापस t;
पूर्ण

अटल __अंतरभूत__ व्योम atomic64_set(atomic64_t *v, s64 i)
अणु
	__यंत्र__ __अस्थिर__("std%U0%X0 %1,%0" : "=m"UPD_CONSTR(v->counter) : "r"(i));
पूर्ण

#घोषणा ATOMIC64_OP(op, यंत्र_op)						\
अटल __अंतरभूत__ व्योम atomic64_##op(s64 a, atomic64_t *v)		\
अणु									\
	s64 t;								\
									\
	__यंत्र__ __अस्थिर__(						\
"1:	ldarx	%0,0,%3		# atomic64_" #op "\n"			\
	#यंत्र_op " %0,%2,%0\n"						\
"	stdcx.	%0,0,%3 \n"						\
"	bne-	1b\n"							\
	: "=&r" (t), "+m" (v->counter)					\
	: "r" (a), "r" (&v->counter)					\
	: "cc");							\
पूर्ण

#घोषणा ATOMIC64_OP_RETURN_RELAXED(op, यंत्र_op)				\
अटल अंतरभूत s64							\
atomic64_##op##_वापस_relaxed(s64 a, atomic64_t *v)			\
अणु									\
	s64 t;								\
									\
	__यंत्र__ __अस्थिर__(						\
"1:	ldarx	%0,0,%3		# atomic64_" #op "_return_relaxed\n"	\
	#यंत्र_op " %0,%2,%0\n"						\
"	stdcx.	%0,0,%3\n"						\
"	bne-	1b\n"							\
	: "=&r" (t), "+m" (v->counter)					\
	: "r" (a), "r" (&v->counter)					\
	: "cc");							\
									\
	वापस t;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OP_RELAXED(op, यंत्र_op)				\
अटल अंतरभूत s64							\
atomic64_fetch_##op##_relaxed(s64 a, atomic64_t *v)			\
अणु									\
	s64 res, t;							\
									\
	__यंत्र__ __अस्थिर__(						\
"1:	ldarx	%0,0,%4		# atomic64_fetch_" #op "_relaxed\n"	\
	#यंत्र_op " %1,%3,%0\n"						\
"	stdcx.	%1,0,%4\n"						\
"	bne-	1b\n"							\
	: "=&r" (res), "=&r" (t), "+m" (v->counter)			\
	: "r" (a), "r" (&v->counter)					\
	: "cc");							\
									\
	वापस res;							\
पूर्ण

#घोषणा ATOMIC64_OPS(op, यंत्र_op)					\
	ATOMIC64_OP(op, यंत्र_op)						\
	ATOMIC64_OP_RETURN_RELAXED(op, यंत्र_op)				\
	ATOMIC64_FETCH_OP_RELAXED(op, यंत्र_op)

ATOMIC64_OPS(add, add)
ATOMIC64_OPS(sub, subf)

#घोषणा atomic64_add_वापस_relaxed atomic64_add_वापस_relaxed
#घोषणा atomic64_sub_वापस_relaxed atomic64_sub_वापस_relaxed

#घोषणा atomic64_fetch_add_relaxed atomic64_fetch_add_relaxed
#घोषणा atomic64_fetch_sub_relaxed atomic64_fetch_sub_relaxed

#अघोषित ATOMIC64_OPS
#घोषणा ATOMIC64_OPS(op, यंत्र_op)					\
	ATOMIC64_OP(op, यंत्र_op)						\
	ATOMIC64_FETCH_OP_RELAXED(op, यंत्र_op)

ATOMIC64_OPS(and, and)
ATOMIC64_OPS(or, or)
ATOMIC64_OPS(xor, xor)

#घोषणा atomic64_fetch_and_relaxed atomic64_fetch_and_relaxed
#घोषणा atomic64_fetch_or_relaxed  atomic64_fetch_or_relaxed
#घोषणा atomic64_fetch_xor_relaxed atomic64_fetch_xor_relaxed

#अघोषित ATOPIC64_OPS
#अघोषित ATOMIC64_FETCH_OP_RELAXED
#अघोषित ATOMIC64_OP_RETURN_RELAXED
#अघोषित ATOMIC64_OP

अटल __अंतरभूत__ व्योम atomic64_inc(atomic64_t *v)
अणु
	s64 t;

	__यंत्र__ __अस्थिर__(
"1:	ldarx	%0,0,%2		# atomic64_inc\न\
	addic	%0,%0,1\न\
	stdcx.	%0,0,%2 \न\
	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");
पूर्ण
#घोषणा atomic64_inc atomic64_inc

अटल __अंतरभूत__ s64 atomic64_inc_वापस_relaxed(atomic64_t *v)
अणु
	s64 t;

	__यंत्र__ __अस्थिर__(
"1:	ldarx	%0,0,%2		# atomic64_inc_return_relaxed\n"
"	addic	%0,%0,1\n"
"	stdcx.	%0,0,%2\n"
"	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");

	वापस t;
पूर्ण

अटल __अंतरभूत__ व्योम atomic64_dec(atomic64_t *v)
अणु
	s64 t;

	__यंत्र__ __अस्थिर__(
"1:	ldarx	%0,0,%2		# atomic64_dec\न\
	addic	%0,%0,-1\न\
	stdcx.	%0,0,%2\न\
	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");
पूर्ण
#घोषणा atomic64_dec atomic64_dec

अटल __अंतरभूत__ s64 atomic64_dec_वापस_relaxed(atomic64_t *v)
अणु
	s64 t;

	__यंत्र__ __अस्थिर__(
"1:	ldarx	%0,0,%2		# atomic64_dec_return_relaxed\n"
"	addic	%0,%0,-1\n"
"	stdcx.	%0,0,%2\n"
"	bne-	1b"
	: "=&r" (t), "+m" (v->counter)
	: "r" (&v->counter)
	: "cc", "xer");

	वापस t;
पूर्ण

#घोषणा atomic64_inc_वापस_relaxed atomic64_inc_वापस_relaxed
#घोषणा atomic64_dec_वापस_relaxed atomic64_dec_वापस_relaxed

/*
 * Atomically test *v and decrement अगर it is greater than 0.
 * The function वापसs the old value of *v minus 1.
 */
अटल __अंतरभूत__ s64 atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	s64 t;

	__यंत्र__ __अस्थिर__(
	PPC_ATOMIC_ENTRY_BARRIER
"1:	ldarx	%0,0,%1		# atomic64_dec_अगर_positive\न\
	addic.	%0,%0,-1\न\
	blt-	2f\न\
	stdcx.	%0,0,%1\न\
	bne-	1b"
	PPC_ATOMIC_EXIT_BARRIER
	"\न\
2:"	: "=&r" (t)
	: "r" (&v->counter)
	: "cc", "xer", "memory");

	वापस t;
पूर्ण
#घोषणा atomic64_dec_अगर_positive atomic64_dec_अगर_positive

#घोषणा atomic64_cmpxchg(v, o, n) (cmpxchg(&((v)->counter), (o), (n)))
#घोषणा atomic64_cmpxchg_relaxed(v, o, n) \
	cmpxchg_relaxed(&((v)->counter), (o), (n))
#घोषणा atomic64_cmpxchg_acquire(v, o, n) \
	cmpxchg_acquire(&((v)->counter), (o), (n))

#घोषणा atomic64_xchg(v, new) (xchg(&((v)->counter), new))
#घोषणा atomic64_xchg_relaxed(v, new) xchg_relaxed(&((v)->counter), (new))

/**
 * atomic64_fetch_add_unless - add unless the number is a given value
 * @v: poपूर्णांकer of type atomic64_t
 * @a: the amount to add to v...
 * @u: ...unless v is equal to u.
 *
 * Atomically adds @a to @v, so दीर्घ as it was not @u.
 * Returns the old value of @v.
 */
अटल __अंतरभूत__ s64 atomic64_fetch_add_unless(atomic64_t *v, s64 a, s64 u)
अणु
	s64 t;

	__यंत्र__ __अस्थिर__ (
	PPC_ATOMIC_ENTRY_BARRIER
"1:	ldarx	%0,0,%1		# atomic64_fetch_add_unless\न\
	cmpd	0,%0,%3 \न\
	beq	2f \न\
	add	%0,%2,%0 \न"
"	stdcx.	%0,0,%1 \न\
	bne-	1b \न"
	PPC_ATOMIC_EXIT_BARRIER
"	subf	%0,%2,%0 \न\
2:"
	: "=&r" (t)
	: "r" (&v->counter), "r" (a), "r" (u)
	: "cc", "memory");

	वापस t;
पूर्ण
#घोषणा atomic64_fetch_add_unless atomic64_fetch_add_unless

/**
 * atomic_inc64_not_zero - increment unless the number is zero
 * @v: poपूर्णांकer of type atomic64_t
 *
 * Atomically increments @v by 1, so दीर्घ as @v is non-zero.
 * Returns non-zero अगर @v was non-zero, and zero otherwise.
 */
अटल __अंतरभूत__ पूर्णांक atomic64_inc_not_zero(atomic64_t *v)
अणु
	s64 t1, t2;

	__यंत्र__ __अस्थिर__ (
	PPC_ATOMIC_ENTRY_BARRIER
"1:	ldarx	%0,0,%2		# atomic64_inc_not_zero\न\
	cmpdi	0,%0,0\न\
	beq-	2f\न\
	addic	%1,%0,1\न\
	stdcx.	%1,0,%2\न\
	bne-	1b\न"
	PPC_ATOMIC_EXIT_BARRIER
	"\न\
2:"
	: "=&r" (t1), "=&r" (t2)
	: "r" (&v->counter)
	: "cc", "xer", "memory");

	वापस t1 != 0;
पूर्ण
#घोषणा atomic64_inc_not_zero(v) atomic64_inc_not_zero((v))

#पूर्ण_अगर /* __घातerpc64__ */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_ATOMIC_H_ */
