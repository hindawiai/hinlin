<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/atomic.h
 *
 *  Copyright (C) 1996 Russell King.
 *  Copyright (C) 2002 Deep Blue Solutions Ltd.
 */
#अगर_अघोषित __ASM_ARM_ATOMIC_H
#घोषणा __ASM_ARM_ATOMIC_H

#समावेश <linux/compiler.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/types.h>
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cmpxchg.h>

#अगर_घोषित __KERNEL__

/*
 * On ARM, ordinary assignment (str inकाष्ठाion) करोesn't clear the local
 * strex/ldrex monitor on some implementations. The reason we can use it क्रम
 * atomic_set() is the clrex or dummy strex करोne on every exception वापस.
 */
#घोषणा atomic_पढ़ो(v)	READ_ONCE((v)->counter)
#घोषणा atomic_set(v,i)	WRITE_ONCE(((v)->counter), (i))

#अगर __LINUX_ARM_ARCH__ >= 6

/*
 * ARMv6 UP and SMP safe atomic ops.  We use load exclusive and
 * store exclusive to ensure that these are atomic.  We may loop
 * to ensure that the update happens.
 */

#घोषणा ATOMIC_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	prefetchw(&v->counter);						\
	__यंत्र__ __अस्थिर__("@ atomic_" #op "\n"			\
"1:	ldrex	%0, [%3]\n"						\
"	" #यंत्र_op "	%0, %0, %4\n"					\
"	strex	%1, %0, [%3]\n"						\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&r" (result), "=&r" (पंचांगp), "+Qo" (v->counter)		\
	: "r" (&v->counter), "Ir" (i)					\
	: "cc");							\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस_relaxed(पूर्णांक i, atomic_t *v)	\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	prefetchw(&v->counter);						\
									\
	__यंत्र__ __अस्थिर__("@ atomic_" #op "_return\n"		\
"1:	ldrex	%0, [%3]\n"						\
"	" #यंत्र_op "	%0, %0, %4\n"					\
"	strex	%1, %0, [%3]\n"						\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&r" (result), "=&r" (पंचांगp), "+Qo" (v->counter)		\
	: "r" (&v->counter), "Ir" (i)					\
	: "cc");							\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op##_relaxed(पूर्णांक i, atomic_t *v)	\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result, val;						\
									\
	prefetchw(&v->counter);						\
									\
	__यंत्र__ __अस्थिर__("@ atomic_fetch_" #op "\n"			\
"1:	ldrex	%0, [%4]\n"						\
"	" #यंत्र_op "	%1, %0, %5\n"					\
"	strex	%2, %1, [%4]\n"						\
"	teq	%2, #0\n"						\
"	bne	1b"							\
	: "=&r" (result), "=&r" (val), "=&r" (पंचांगp), "+Qo" (v->counter)	\
	: "r" (&v->counter), "Ir" (i)					\
	: "cc");							\
									\
	वापस result;							\
पूर्ण

#घोषणा atomic_add_वापस_relaxed	atomic_add_वापस_relaxed
#घोषणा atomic_sub_वापस_relaxed	atomic_sub_वापस_relaxed
#घोषणा atomic_fetch_add_relaxed	atomic_fetch_add_relaxed
#घोषणा atomic_fetch_sub_relaxed	atomic_fetch_sub_relaxed

#घोषणा atomic_fetch_and_relaxed	atomic_fetch_and_relaxed
#घोषणा atomic_fetch_andnot_relaxed	atomic_fetch_andnot_relaxed
#घोषणा atomic_fetch_or_relaxed		atomic_fetch_or_relaxed
#घोषणा atomic_fetch_xor_relaxed	atomic_fetch_xor_relaxed

अटल अंतरभूत पूर्णांक atomic_cmpxchg_relaxed(atomic_t *ptr, पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक oldval;
	अचिन्हित दीर्घ res;

	prefetchw(&ptr->counter);

	करो अणु
		__यंत्र__ __अस्थिर__("@ atomic_cmpxchg\n"
		"ldrex	%1, [%3]\n"
		"mov	%0, #0\n"
		"teq	%1, %4\n"
		"strexeq %0, %5, [%3]\n"
		    : "=&r" (res), "=&r" (oldval), "+Qo" (ptr->counter)
		    : "r" (&ptr->counter), "Ir" (old), "r" (new)
		    : "cc");
	पूर्ण जबतक (res);

	वापस oldval;
पूर्ण
#घोषणा atomic_cmpxchg_relaxed		atomic_cmpxchg_relaxed

अटल अंतरभूत पूर्णांक atomic_fetch_add_unless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक oldval, newval;
	अचिन्हित दीर्घ पंचांगp;

	smp_mb();
	prefetchw(&v->counter);

	__यंत्र__ __अस्थिर__ ("@ atomic_add_unless\n"
"1:	ldrex	%0, [%4]\n"
"	teq	%0, %5\n"
"	beq	2f\n"
"	add	%1, %0, %6\n"
"	strex	%2, %1, [%4]\n"
"	teq	%2, #0\n"
"	bne	1b\n"
"2:"
	: "=&r" (oldval), "=&r" (newval), "=&r" (पंचांगp), "+Qo" (v->counter)
	: "r" (&v->counter), "r" (u), "r" (a)
	: "cc");

	अगर (oldval != u)
		smp_mb();

	वापस oldval;
पूर्ण
#घोषणा atomic_fetch_add_unless		atomic_fetch_add_unless

#अन्यथा /* ARM_ARCH_6 */

#अगर_घोषित CONFIG_SMP
#त्रुटि SMP not supported on pre-ARMv6 CPUs
#पूर्ण_अगर

#घोषणा ATOMIC_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	raw_local_irq_save(flags);					\
	v->counter c_op i;						\
	raw_local_irq_restore(flags);					\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक val;							\
									\
	raw_local_irq_save(flags);					\
	v->counter c_op i;						\
	val = v->counter;						\
	raw_local_irq_restore(flags);					\
									\
	वापस val;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक val;							\
									\
	raw_local_irq_save(flags);					\
	val = v->counter;						\
	v->counter c_op i;						\
	raw_local_irq_restore(flags);					\
									\
	वापस val;							\
पूर्ण

अटल अंतरभूत पूर्णांक atomic_cmpxchg(atomic_t *v, पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	raw_local_irq_save(flags);
	ret = v->counter;
	अगर (likely(ret == old))
		v->counter = new;
	raw_local_irq_restore(flags);

	वापस ret;
पूर्ण

#घोषणा atomic_fetch_andnot		atomic_fetch_andnot

#पूर्ण_अगर /* __LINUX_ARM_ARCH__ */

#घोषणा ATOMIC_OPS(op, c_op, यंत्र_op)					\
	ATOMIC_OP(op, c_op, यंत्र_op)					\
	ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
	ATOMIC_FETCH_OP(op, c_op, यंत्र_op)

ATOMIC_OPS(add, +=, add)
ATOMIC_OPS(sub, -=, sub)

#घोषणा atomic_andnot atomic_andnot

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op, c_op, यंत्र_op)					\
	ATOMIC_OP(op, c_op, यंत्र_op)					\
	ATOMIC_FETCH_OP(op, c_op, यंत्र_op)

ATOMIC_OPS(and, &=, and)
ATOMIC_OPS(andnot, &= ~, bic)
ATOMIC_OPS(or,  |=, orr)
ATOMIC_OPS(xor, ^=, eor)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

#अगर_अघोषित CONFIG_GENERIC_ATOMIC64
प्रकार काष्ठा अणु
	s64 counter;
पूर्ण atomic64_t;

#घोषणा ATOMIC64_INIT(i) अणु (i) पूर्ण

#अगर_घोषित CONFIG_ARM_LPAE
अटल अंतरभूत s64 atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	s64 result;

	__यंत्र__ __अस्थिर__("@ atomic64_read\n"
"	ldrd	%0, %H0, [%1]"
	: "=&r" (result)
	: "r" (&v->counter), "Qo" (v->counter)
	);

	वापस result;
पूर्ण

अटल अंतरभूत व्योम atomic64_set(atomic64_t *v, s64 i)
अणु
	__यंत्र__ __अस्थिर__("@ atomic64_set\n"
"	strd	%2, %H2, [%1]"
	: "=Qo" (v->counter)
	: "r" (&v->counter), "r" (i)
	);
पूर्ण
#अन्यथा
अटल अंतरभूत s64 atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	s64 result;

	__यंत्र__ __अस्थिर__("@ atomic64_read\n"
"	ldrexd	%0, %H0, [%1]"
	: "=&r" (result)
	: "r" (&v->counter), "Qo" (v->counter)
	);

	वापस result;
पूर्ण

अटल अंतरभूत व्योम atomic64_set(atomic64_t *v, s64 i)
अणु
	s64 पंचांगp;

	prefetchw(&v->counter);
	__यंत्र__ __अस्थिर__("@ atomic64_set\n"
"1:	ldrexd	%0, %H0, [%2]\n"
"	strexd	%0, %3, %H3, [%2]\n"
"	teq	%0, #0\n"
"	bne	1b"
	: "=&r" (पंचांगp), "=Qo" (v->counter)
	: "r" (&v->counter), "r" (i)
	: "cc");
पूर्ण
#पूर्ण_अगर

#घोषणा ATOMIC64_OP(op, op1, op2)					\
अटल अंतरभूत व्योम atomic64_##op(s64 i, atomic64_t *v)			\
अणु									\
	s64 result;							\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	prefetchw(&v->counter);						\
	__यंत्र__ __अस्थिर__("@ atomic64_" #op "\n"			\
"1:	ldrexd	%0, %H0, [%3]\n"					\
"	" #op1 " %Q0, %Q0, %Q4\n"					\
"	" #op2 " %R0, %R0, %R4\n"					\
"	strexd	%1, %0, %H0, [%3]\n"					\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&r" (result), "=&r" (पंचांगp), "+Qo" (v->counter)		\
	: "r" (&v->counter), "r" (i)					\
	: "cc");							\
पूर्ण									\

#घोषणा ATOMIC64_OP_RETURN(op, op1, op2)				\
अटल अंतरभूत s64							\
atomic64_##op##_वापस_relaxed(s64 i, atomic64_t *v)			\
अणु									\
	s64 result;							\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	prefetchw(&v->counter);						\
									\
	__यंत्र__ __अस्थिर__("@ atomic64_" #op "_return\n"		\
"1:	ldrexd	%0, %H0, [%3]\n"					\
"	" #op1 " %Q0, %Q0, %Q4\n"					\
"	" #op2 " %R0, %R0, %R4\n"					\
"	strexd	%1, %0, %H0, [%3]\n"					\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&r" (result), "=&r" (पंचांगp), "+Qo" (v->counter)		\
	: "r" (&v->counter), "r" (i)					\
	: "cc");							\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OP(op, op1, op2)					\
अटल अंतरभूत s64							\
atomic64_fetch_##op##_relaxed(s64 i, atomic64_t *v)			\
अणु									\
	s64 result, val;						\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	prefetchw(&v->counter);						\
									\
	__यंत्र__ __अस्थिर__("@ atomic64_fetch_" #op "\n"		\
"1:	ldrexd	%0, %H0, [%4]\n"					\
"	" #op1 " %Q1, %Q0, %Q5\n"					\
"	" #op2 " %R1, %R0, %R5\n"					\
"	strexd	%2, %1, %H1, [%4]\n"					\
"	teq	%2, #0\n"						\
"	bne	1b"							\
	: "=&r" (result), "=&r" (val), "=&r" (पंचांगp), "+Qo" (v->counter)	\
	: "r" (&v->counter), "r" (i)					\
	: "cc");							\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC64_OPS(op, op1, op2)					\
	ATOMIC64_OP(op, op1, op2)					\
	ATOMIC64_OP_RETURN(op, op1, op2)				\
	ATOMIC64_FETCH_OP(op, op1, op2)

ATOMIC64_OPS(add, adds, adc)
ATOMIC64_OPS(sub, subs, sbc)

#घोषणा atomic64_add_वापस_relaxed	atomic64_add_वापस_relaxed
#घोषणा atomic64_sub_वापस_relaxed	atomic64_sub_वापस_relaxed
#घोषणा atomic64_fetch_add_relaxed	atomic64_fetch_add_relaxed
#घोषणा atomic64_fetch_sub_relaxed	atomic64_fetch_sub_relaxed

#अघोषित ATOMIC64_OPS
#घोषणा ATOMIC64_OPS(op, op1, op2)					\
	ATOMIC64_OP(op, op1, op2)					\
	ATOMIC64_FETCH_OP(op, op1, op2)

#घोषणा atomic64_andnot atomic64_andnot

ATOMIC64_OPS(and, and, and)
ATOMIC64_OPS(andnot, bic, bic)
ATOMIC64_OPS(or,  orr, orr)
ATOMIC64_OPS(xor, eor, eor)

#घोषणा atomic64_fetch_and_relaxed	atomic64_fetch_and_relaxed
#घोषणा atomic64_fetch_andnot_relaxed	atomic64_fetch_andnot_relaxed
#घोषणा atomic64_fetch_or_relaxed	atomic64_fetch_or_relaxed
#घोषणा atomic64_fetch_xor_relaxed	atomic64_fetch_xor_relaxed

#अघोषित ATOMIC64_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP_RETURN
#अघोषित ATOMIC64_OP

अटल अंतरभूत s64 atomic64_cmpxchg_relaxed(atomic64_t *ptr, s64 old, s64 new)
अणु
	s64 oldval;
	अचिन्हित दीर्घ res;

	prefetchw(&ptr->counter);

	करो अणु
		__यंत्र__ __अस्थिर__("@ atomic64_cmpxchg\n"
		"ldrexd		%1, %H1, [%3]\n"
		"mov		%0, #0\n"
		"teq		%1, %4\n"
		"teqeq		%H1, %H4\n"
		"strexdeq	%0, %5, %H5, [%3]"
		: "=&r" (res), "=&r" (oldval), "+Qo" (ptr->counter)
		: "r" (&ptr->counter), "r" (old), "r" (new)
		: "cc");
	पूर्ण जबतक (res);

	वापस oldval;
पूर्ण
#घोषणा atomic64_cmpxchg_relaxed	atomic64_cmpxchg_relaxed

अटल अंतरभूत s64 atomic64_xchg_relaxed(atomic64_t *ptr, s64 new)
अणु
	s64 result;
	अचिन्हित दीर्घ पंचांगp;

	prefetchw(&ptr->counter);

	__यंत्र__ __अस्थिर__("@ atomic64_xchg\n"
"1:	ldrexd	%0, %H0, [%3]\n"
"	strexd	%1, %4, %H4, [%3]\n"
"	teq	%1, #0\n"
"	bne	1b"
	: "=&r" (result), "=&r" (पंचांगp), "+Qo" (ptr->counter)
	: "r" (&ptr->counter), "r" (new)
	: "cc");

	वापस result;
पूर्ण
#घोषणा atomic64_xchg_relaxed		atomic64_xchg_relaxed

अटल अंतरभूत s64 atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	s64 result;
	अचिन्हित दीर्घ पंचांगp;

	smp_mb();
	prefetchw(&v->counter);

	__यंत्र__ __अस्थिर__("@ atomic64_dec_if_positive\n"
"1:	ldrexd	%0, %H0, [%3]\n"
"	subs	%Q0, %Q0, #1\n"
"	sbc	%R0, %R0, #0\n"
"	teq	%R0, #0\n"
"	bmi	2f\n"
"	strexd	%1, %0, %H0, [%3]\n"
"	teq	%1, #0\n"
"	bne	1b\n"
"2:"
	: "=&r" (result), "=&r" (पंचांगp), "+Qo" (v->counter)
	: "r" (&v->counter)
	: "cc");

	smp_mb();

	वापस result;
पूर्ण
#घोषणा atomic64_dec_अगर_positive atomic64_dec_अगर_positive

अटल अंतरभूत s64 atomic64_fetch_add_unless(atomic64_t *v, s64 a, s64 u)
अणु
	s64 oldval, newval;
	अचिन्हित दीर्घ पंचांगp;

	smp_mb();
	prefetchw(&v->counter);

	__यंत्र__ __अस्थिर__("@ atomic64_add_unless\n"
"1:	ldrexd	%0, %H0, [%4]\n"
"	teq	%0, %5\n"
"	teqeq	%H0, %H5\n"
"	beq	2f\n"
"	adds	%Q1, %Q0, %Q6\n"
"	adc	%R1, %R0, %R6\n"
"	strexd	%2, %1, %H1, [%4]\n"
"	teq	%2, #0\n"
"	bne	1b\n"
"2:"
	: "=&r" (oldval), "=&r" (newval), "=&r" (पंचांगp), "+Qo" (v->counter)
	: "r" (&v->counter), "r" (u), "r" (a)
	: "cc");

	अगर (oldval != u)
		smp_mb();

	वापस oldval;
पूर्ण
#घोषणा atomic64_fetch_add_unless atomic64_fetch_add_unless

#पूर्ण_अगर /* !CONFIG_GENERIC_ATOMIC64 */
#पूर्ण_अगर
#पूर्ण_अगर
