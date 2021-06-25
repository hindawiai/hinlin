<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_ATOMIC_H
#घोषणा _ALPHA_ATOMIC_H

#समावेश <linux/types.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cmpxchg.h>

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc...
 *
 * But use these as selकरोm as possible since they are much slower
 * than regular operations.
 */

/*
 * To ensure dependency ordering is preserved क्रम the _relaxed and
 * _release atomics, an smp_mb() is unconditionally inserted पूर्णांकo the
 * _relaxed variants, which are used to build the barriered versions.
 * Aव्योम redundant back-to-back fences in the _acquire and _fence
 * versions.
 */
#घोषणा __atomic_acquire_fence()
#घोषणा __atomic_post_full_fence()

#घोषणा ATOMIC64_INIT(i)	अणु (i) पूर्ण

#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)
#घोषणा atomic64_पढ़ो(v)	READ_ONCE((v)->counter)

#घोषणा atomic_set(v,i)		WRITE_ONCE((v)->counter, (i))
#घोषणा atomic64_set(v,i)	WRITE_ONCE((v)->counter, (i))

/*
 * To get proper branch prediction क्रम the मुख्य line, we must branch
 * क्रमward to code at the end of this object's .text section, then
 * branch back to restart the operation.
 */

#घोषणा ATOMIC_OP(op, यंत्र_op)						\
अटल __अंतरभूत__ व्योम atomic_##op(पूर्णांक i, atomic_t * v)			\
अणु									\
	अचिन्हित दीर्घ temp;						\
	__यंत्र__ __अस्थिर__(						\
	"1:	ldl_l %0,%1\n"						\
	"	" #यंत्र_op " %0,%2,%0\n"					\
	"	stl_c %0,%1\n"						\
	"	beq %0,2f\n"						\
	".subsection 2\n"						\
	"2:	br 1b\n"						\
	".previous"							\
	:"=&r" (temp), "=m" (v->counter)				\
	:"Ir" (i), "m" (v->counter));					\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op, यंत्र_op)					\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस_relaxed(पूर्णांक i, atomic_t *v)	\
अणु									\
	दीर्घ temp, result;						\
	__यंत्र__ __अस्थिर__(						\
	"1:	ldl_l %0,%1\n"						\
	"	" #यंत्र_op " %0,%3,%2\n"					\
	"	" #यंत्र_op " %0,%3,%0\n"					\
	"	stl_c %0,%1\n"						\
	"	beq %0,2f\n"						\
	".subsection 2\n"						\
	"2:	br 1b\n"						\
	".previous"							\
	:"=&r" (temp), "=m" (v->counter), "=&r" (result)		\
	:"Ir" (i), "m" (v->counter) : "memory");			\
	smp_mb();							\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, यंत्र_op)					\
अटल अंतरभूत पूर्णांक atomic_fetch_##op##_relaxed(पूर्णांक i, atomic_t *v)	\
अणु									\
	दीर्घ temp, result;						\
	__यंत्र__ __अस्थिर__(						\
	"1:	ldl_l %2,%1\n"						\
	"	" #यंत्र_op " %2,%3,%0\n"					\
	"	stl_c %0,%1\n"						\
	"	beq %0,2f\n"						\
	".subsection 2\n"						\
	"2:	br 1b\n"						\
	".previous"							\
	:"=&r" (temp), "=m" (v->counter), "=&r" (result)		\
	:"Ir" (i), "m" (v->counter) : "memory");			\
	smp_mb();							\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC64_OP(op, यंत्र_op)						\
अटल __अंतरभूत__ व्योम atomic64_##op(s64 i, atomic64_t * v)		\
अणु									\
	s64 temp;							\
	__यंत्र__ __अस्थिर__(						\
	"1:	ldq_l %0,%1\n"						\
	"	" #यंत्र_op " %0,%2,%0\n"					\
	"	stq_c %0,%1\n"						\
	"	beq %0,2f\n"						\
	".subsection 2\n"						\
	"2:	br 1b\n"						\
	".previous"							\
	:"=&r" (temp), "=m" (v->counter)				\
	:"Ir" (i), "m" (v->counter));					\
पूर्ण									\

#घोषणा ATOMIC64_OP_RETURN(op, यंत्र_op)					\
अटल __अंतरभूत__ s64 atomic64_##op##_वापस_relaxed(s64 i, atomic64_t * v)	\
अणु									\
	s64 temp, result;						\
	__यंत्र__ __अस्थिर__(						\
	"1:	ldq_l %0,%1\n"						\
	"	" #यंत्र_op " %0,%3,%2\n"					\
	"	" #यंत्र_op " %0,%3,%0\n"					\
	"	stq_c %0,%1\n"						\
	"	beq %0,2f\n"						\
	".subsection 2\n"						\
	"2:	br 1b\n"						\
	".previous"							\
	:"=&r" (temp), "=m" (v->counter), "=&r" (result)		\
	:"Ir" (i), "m" (v->counter) : "memory");			\
	smp_mb();							\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OP(op, यंत्र_op)					\
अटल __अंतरभूत__ s64 atomic64_fetch_##op##_relaxed(s64 i, atomic64_t * v)	\
अणु									\
	s64 temp, result;						\
	__यंत्र__ __अस्थिर__(						\
	"1:	ldq_l %2,%1\n"						\
	"	" #यंत्र_op " %2,%3,%0\n"					\
	"	stq_c %0,%1\n"						\
	"	beq %0,2f\n"						\
	".subsection 2\n"						\
	"2:	br 1b\n"						\
	".previous"							\
	:"=&r" (temp), "=m" (v->counter), "=&r" (result)		\
	:"Ir" (i), "m" (v->counter) : "memory");			\
	smp_mb();							\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_OPS(op)							\
	ATOMIC_OP(op, op##l)						\
	ATOMIC_OP_RETURN(op, op##l)					\
	ATOMIC_FETCH_OP(op, op##l)					\
	ATOMIC64_OP(op, op##q)						\
	ATOMIC64_OP_RETURN(op, op##q)					\
	ATOMIC64_FETCH_OP(op, op##q)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#घोषणा atomic_add_वापस_relaxed	atomic_add_वापस_relaxed
#घोषणा atomic_sub_वापस_relaxed	atomic_sub_वापस_relaxed
#घोषणा atomic_fetch_add_relaxed	atomic_fetch_add_relaxed
#घोषणा atomic_fetch_sub_relaxed	atomic_fetch_sub_relaxed

#घोषणा atomic64_add_वापस_relaxed	atomic64_add_वापस_relaxed
#घोषणा atomic64_sub_वापस_relaxed	atomic64_sub_वापस_relaxed
#घोषणा atomic64_fetch_add_relaxed	atomic64_fetch_add_relaxed
#घोषणा atomic64_fetch_sub_relaxed	atomic64_fetch_sub_relaxed

#घोषणा atomic_andnot atomic_andnot
#घोषणा atomic64_andnot atomic64_andnot

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op, यंत्र)						\
	ATOMIC_OP(op, यंत्र)						\
	ATOMIC_FETCH_OP(op, यंत्र)					\
	ATOMIC64_OP(op, यंत्र)						\
	ATOMIC64_FETCH_OP(op, यंत्र)

ATOMIC_OPS(and, and)
ATOMIC_OPS(andnot, bic)
ATOMIC_OPS(or, bis)
ATOMIC_OPS(xor, xor)

#घोषणा atomic_fetch_and_relaxed	atomic_fetch_and_relaxed
#घोषणा atomic_fetch_andnot_relaxed	atomic_fetch_andnot_relaxed
#घोषणा atomic_fetch_or_relaxed		atomic_fetch_or_relaxed
#घोषणा atomic_fetch_xor_relaxed	atomic_fetch_xor_relaxed

#घोषणा atomic64_fetch_and_relaxed	atomic64_fetch_and_relaxed
#घोषणा atomic64_fetch_andnot_relaxed	atomic64_fetch_andnot_relaxed
#घोषणा atomic64_fetch_or_relaxed	atomic64_fetch_or_relaxed
#घोषणा atomic64_fetch_xor_relaxed	atomic64_fetch_xor_relaxed

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP_RETURN
#अघोषित ATOMIC64_OP
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#घोषणा atomic64_cmpxchg(v, old, new) (cmpxchg(&((v)->counter), old, new))
#घोषणा atomic64_xchg(v, new) (xchg(&((v)->counter), new))

#घोषणा atomic_cmpxchg(v, old, new) (cmpxchg(&((v)->counter), old, new))
#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

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
	पूर्णांक c, new, old;
	smp_mb();
	__यंत्र__ __अस्थिर__(
	"1:	ldl_l	%[old],%[mem]\n"
	"	cmpeq	%[old],%[u],%[c]\n"
	"	addl	%[old],%[a],%[new]\n"
	"	bne	%[c],2f\n"
	"	stl_c	%[new],%[mem]\n"
	"	beq	%[new],3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	br	1b\n"
	".previous"
	: [old] "=&r"(old), [new] "=&r"(new), [c] "=&r"(c)
	: [mem] "m"(*v), [a] "rI"(a), [u] "rI"((दीर्घ)u)
	: "memory");
	smp_mb();
	वापस old;
पूर्ण
#घोषणा atomic_fetch_add_unless atomic_fetch_add_unless

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
	s64 c, new, old;
	smp_mb();
	__यंत्र__ __अस्थिर__(
	"1:	ldq_l	%[old],%[mem]\n"
	"	cmpeq	%[old],%[u],%[c]\n"
	"	addq	%[old],%[a],%[new]\n"
	"	bne	%[c],2f\n"
	"	stq_c	%[new],%[mem]\n"
	"	beq	%[new],3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	br	1b\n"
	".previous"
	: [old] "=&r"(old), [new] "=&r"(new), [c] "=&r"(c)
	: [mem] "m"(*v), [a] "rI"(a), [u] "rI"(u)
	: "memory");
	smp_mb();
	वापस old;
पूर्ण
#घोषणा atomic64_fetch_add_unless atomic64_fetch_add_unless

/*
 * atomic64_dec_अगर_positive - decrement by 1 अगर old value positive
 * @v: poपूर्णांकer of type atomic_t
 *
 * The function वापसs the old value of *v minus 1, even अगर
 * the atomic variable, v, was not decremented.
 */
अटल अंतरभूत s64 atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	s64 old, पंचांगp;
	smp_mb();
	__यंत्र__ __अस्थिर__(
	"1:	ldq_l	%[old],%[mem]\n"
	"	subq	%[old],1,%[tmp]\n"
	"	ble	%[old],2f\n"
	"	stq_c	%[tmp],%[mem]\n"
	"	beq	%[tmp],3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	br	1b\n"
	".previous"
	: [old] "=&r"(old), [पंचांगp] "=&r"(पंचांगp)
	: [mem] "m"(*v)
	: "memory");
	smp_mb();
	वापस old - 1;
पूर्ण
#घोषणा atomic64_dec_अगर_positive atomic64_dec_अगर_positive

#पूर्ण_अगर /* _ALPHA_ATOMIC_H */
