<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_ATOMIC_H
#घोषणा _ASM_ARC_ATOMIC_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/smp.h>

#घोषणा atomic_पढ़ो(v)  READ_ONCE((v)->counter)

#अगर_घोषित CONFIG_ARC_HAS_LLSC

#घोषणा atomic_set(v, i) WRITE_ONCE(((v)->counter), (i))

#घोषणा ATOMIC_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित पूर्णांक val;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:	llock   %[val], [%[ctr]]		\n"		\
	"	" #यंत्र_op " %[val], %[val], %[i]	\n"		\
	"	scond   %[val], [%[ctr]]		\n"		\
	"	bnz     1b				\n"		\
	: [val]	"=&r"	(val) /* Early clobber to prevent reg reuse */	\
	: [ctr]	"r"	(&v->counter), /* Not "m": llock only supports reg direct addr mode */	\
	  [i]	"ir"	(i)						\
	: "cc");							\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित पूर्णांक val;						\
									\
	/*								\
	 * Explicit full memory barrier needed beक्रमe/after as		\
	 * LLOCK/SCOND themselves करोn't provide any such semantics	\
	 */								\
	smp_mb();							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:	llock   %[val], [%[ctr]]		\n"		\
	"	" #यंत्र_op " %[val], %[val], %[i]	\n"		\
	"	scond   %[val], [%[ctr]]		\n"		\
	"	bnz     1b				\n"		\
	: [val]	"=&r"	(val)						\
	: [ctr]	"r"	(&v->counter),					\
	  [i]	"ir"	(i)						\
	: "cc");							\
									\
	smp_mb();							\
									\
	वापस val;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित पूर्णांक val, orig;						\
									\
	/*								\
	 * Explicit full memory barrier needed beक्रमe/after as		\
	 * LLOCK/SCOND themselves करोn't provide any such semantics	\
	 */								\
	smp_mb();							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:	llock   %[orig], [%[ctr]]		\n"		\
	"	" #यंत्र_op " %[val], %[orig], %[i]	\n"		\
	"	scond   %[val], [%[ctr]]		\n"		\
	"	bnz     1b				\n"		\
	: [val]	"=&r"	(val),						\
	  [orig] "=&r" (orig)						\
	: [ctr]	"r"	(&v->counter),					\
	  [i]	"ir"	(i)						\
	: "cc");							\
									\
	smp_mb();							\
									\
	वापस orig;							\
पूर्ण

#अन्यथा	/* !CONFIG_ARC_HAS_LLSC */

#अगर_अघोषित CONFIG_SMP

 /* violating atomic_xxx API locking protocol in UP क्रम optimization sake */
#घोषणा atomic_set(v, i) WRITE_ONCE(((v)->counter), (i))

#अन्यथा

अटल अंतरभूत व्योम atomic_set(atomic_t *v, पूर्णांक i)
अणु
	/*
	 * Independent of hardware support, all of the atomic_xxx() APIs need
	 * to follow the same locking rules to make sure that a "hardware"
	 * atomic insn (e.g. LD) करोesn't clobber an "emulated" atomic insn
	 * sequence
	 *
	 * Thus atomic_set() despite being 1 insn (and seemingly atomic)
	 * requires the locking.
	 */
	अचिन्हित दीर्घ flags;

	atomic_ops_lock(flags);
	WRITE_ONCE(v->counter, i);
	atomic_ops_unlock(flags);
पूर्ण

#घोषणा atomic_set_release(v, i)	atomic_set((v), (i))

#पूर्ण_अगर

/*
 * Non hardware assisted Atomic-R-M-W
 * Locking would change to irq-disabling only (UP) and spinlocks (SMP)
 */

#घोषणा ATOMIC_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	atomic_ops_lock(flags);						\
	v->counter c_op i;						\
	atomic_ops_unlock(flags);					\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	अचिन्हित दीर्घ temp;						\
									\
	/*								\
	 * spin lock/unlock provides the needed smp_mb() beक्रमe/after	\
	 */								\
	atomic_ops_lock(flags);						\
	temp = v->counter;						\
	temp c_op i;							\
	v->counter = temp;						\
	atomic_ops_unlock(flags);					\
									\
	वापस temp;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
	अचिन्हित दीर्घ orig;						\
									\
	/*								\
	 * spin lock/unlock provides the needed smp_mb() beक्रमe/after	\
	 */								\
	atomic_ops_lock(flags);						\
	orig = v->counter;						\
	v->counter c_op i;						\
	atomic_ops_unlock(flags);					\
									\
	वापस orig;							\
पूर्ण

#पूर्ण_अगर /* !CONFIG_ARC_HAS_LLSC */

#घोषणा ATOMIC_OPS(op, c_op, यंत्र_op)					\
	ATOMIC_OP(op, c_op, यंत्र_op)					\
	ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
	ATOMIC_FETCH_OP(op, c_op, यंत्र_op)

ATOMIC_OPS(add, +=, add)
ATOMIC_OPS(sub, -=, sub)

#घोषणा atomic_andnot		atomic_andnot
#घोषणा atomic_fetch_andnot	atomic_fetch_andnot

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op, c_op, यंत्र_op)					\
	ATOMIC_OP(op, c_op, यंत्र_op)					\
	ATOMIC_FETCH_OP(op, c_op, यंत्र_op)

ATOMIC_OPS(and, &=, and)
ATOMIC_OPS(andnot, &= ~, bic)
ATOMIC_OPS(or, |=, or)
ATOMIC_OPS(xor, ^=, xor)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#अगर_घोषित CONFIG_GENERIC_ATOMIC64

#समावेश <यंत्र-generic/atomic64.h>

#अन्यथा	/* Kconfig ensures this is only enabled with needed h/w assist */

/*
 * ARCv2 supports 64-bit exclusive load (LLOCKD) / store (SCONDD)
 *  - The address HAS to be 64-bit aligned
 *  - There are 2 semantics involved here:
 *    = exclusive implies no पूर्णांकerim update between load/store to same addr
 *    = both words are observed/updated together: this is guaranteed even
 *      क्रम regular 64-bit load (LDD) / store (STD). Thus atomic64_set()
 *      is NOT required to use LLOCKD+SCONDD, STD suffices
 */

प्रकार काष्ठा अणु
	s64 __aligned(8) counter;
पूर्ण atomic64_t;

#घोषणा ATOMIC64_INIT(a) अणु (a) पूर्ण

अटल अंतरभूत s64 atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	s64 val;

	__यंत्र__ __अस्थिर__(
	"	ldd   %0, [%1]	\n"
	: "=r"(val)
	: "r"(&v->counter));

	वापस val;
पूर्ण

अटल अंतरभूत व्योम atomic64_set(atomic64_t *v, s64 a)
अणु
	/*
	 * This could have been a simple assignment in "C" but would need
	 * explicit अस्थिर. Otherwise gcc optimizers could elide the store
	 * which borked atomic64 self-test
	 * In the अंतरभूत यंत्र version, memory clobber needed क्रम exact same
	 * reason, to tell gcc about the store.
	 *
	 * This however is not needed क्रम sibling atomic64_add() etc since both
	 * load/store are explicitly करोne in अंतरभूत यंत्र. As दीर्घ as API is used
	 * क्रम each access, gcc has no way to optimize away any load/store
	 */
	__यंत्र__ __अस्थिर__(
	"	std   %0, [%1]	\n"
	:
	: "r"(a), "r"(&v->counter)
	: "memory");
पूर्ण

#घोषणा ATOMIC64_OP(op, op1, op2)					\
अटल अंतरभूत व्योम atomic64_##op(s64 a, atomic64_t *v)			\
अणु									\
	s64 val;							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:				\n"				\
	"	llockd  %0, [%1]	\n"				\
	"	" #op1 " %L0, %L0, %L2	\n"				\
	"	" #op2 " %H0, %H0, %H2	\n"				\
	"	scondd   %0, [%1]	\n"				\
	"	bnz     1b		\n"				\
	: "=&r"(val)							\
	: "r"(&v->counter), "ir"(a)					\
	: "cc");							\
पूर्ण									\

#घोषणा ATOMIC64_OP_RETURN(op, op1, op2)		        	\
अटल अंतरभूत s64 atomic64_##op##_वापस(s64 a, atomic64_t *v)		\
अणु									\
	s64 val;							\
									\
	smp_mb();							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:				\n"				\
	"	llockd   %0, [%1]	\n"				\
	"	" #op1 " %L0, %L0, %L2	\n"				\
	"	" #op2 " %H0, %H0, %H2	\n"				\
	"	scondd   %0, [%1]	\n"				\
	"	bnz     1b		\n"				\
	: [val] "=&r"(val)						\
	: "r"(&v->counter), "ir"(a)					\
	: "cc");	/* memory clobber comes from smp_mb() */	\
									\
	smp_mb();							\
									\
	वापस val;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OP(op, op1, op2)		        		\
अटल अंतरभूत s64 atomic64_fetch_##op(s64 a, atomic64_t *v)		\
अणु									\
	s64 val, orig;							\
									\
	smp_mb();							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:				\n"				\
	"	llockd   %0, [%2]	\n"				\
	"	" #op1 " %L1, %L0, %L3	\n"				\
	"	" #op2 " %H1, %H0, %H3	\n"				\
	"	scondd   %1, [%2]	\n"				\
	"	bnz     1b		\n"				\
	: "=&r"(orig), "=&r"(val)					\
	: "r"(&v->counter), "ir"(a)					\
	: "cc");	/* memory clobber comes from smp_mb() */	\
									\
	smp_mb();							\
									\
	वापस orig;							\
पूर्ण

#घोषणा ATOMIC64_OPS(op, op1, op2)					\
	ATOMIC64_OP(op, op1, op2)					\
	ATOMIC64_OP_RETURN(op, op1, op2)				\
	ATOMIC64_FETCH_OP(op, op1, op2)

#घोषणा atomic64_andnot		atomic64_andnot
#घोषणा atomic64_fetch_andnot	atomic64_fetch_andnot

ATOMIC64_OPS(add, add.f, adc)
ATOMIC64_OPS(sub, sub.f, sbc)
ATOMIC64_OPS(and, and, and)
ATOMIC64_OPS(andnot, bic, bic)
ATOMIC64_OPS(or, or, or)
ATOMIC64_OPS(xor, xor, xor)

#अघोषित ATOMIC64_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP_RETURN
#अघोषित ATOMIC64_OP

अटल अंतरभूत s64
atomic64_cmpxchg(atomic64_t *ptr, s64 expected, s64 new)
अणु
	s64 prev;

	smp_mb();

	__यंत्र__ __अस्थिर__(
	"1:	llockd  %0, [%1]	\n"
	"	brne    %L0, %L2, 2f	\n"
	"	brne    %H0, %H2, 2f	\n"
	"	scondd  %3, [%1]	\n"
	"	bnz     1b		\n"
	"2:				\n"
	: "=&r"(prev)
	: "r"(ptr), "ir"(expected), "r"(new)
	: "cc");	/* memory clobber comes from smp_mb() */

	smp_mb();

	वापस prev;
पूर्ण

अटल अंतरभूत s64 atomic64_xchg(atomic64_t *ptr, s64 new)
अणु
	s64 prev;

	smp_mb();

	__यंत्र__ __अस्थिर__(
	"1:	llockd  %0, [%1]	\n"
	"	scondd  %2, [%1]	\n"
	"	bnz     1b		\n"
	"2:				\n"
	: "=&r"(prev)
	: "r"(ptr), "r"(new)
	: "cc");	/* memory clobber comes from smp_mb() */

	smp_mb();

	वापस prev;
पूर्ण

/**
 * atomic64_dec_अगर_positive - decrement by 1 अगर old value positive
 * @v: poपूर्णांकer of type atomic64_t
 *
 * The function वापसs the old value of *v minus 1, even अगर
 * the atomic variable, v, was not decremented.
 */

अटल अंतरभूत s64 atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	s64 val;

	smp_mb();

	__यंत्र__ __अस्थिर__(
	"1:	llockd  %0, [%1]	\n"
	"	sub.f   %L0, %L0, 1	# w0 - 1, set C on borrow\n"
	"	sub.c   %H0, %H0, 1	# if C set, w1 - 1\n"
	"	brlt    %H0, 0, 2f	\n"
	"	scondd  %0, [%1]	\n"
	"	bnz     1b		\n"
	"2:				\n"
	: "=&r"(val)
	: "r"(&v->counter)
	: "cc");	/* memory clobber comes from smp_mb() */

	smp_mb();

	वापस val;
पूर्ण
#घोषणा atomic64_dec_अगर_positive atomic64_dec_अगर_positive

/**
 * atomic64_fetch_add_unless - add unless the number is a given value
 * @v: poपूर्णांकer of type atomic64_t
 * @a: the amount to add to v...
 * @u: ...unless v is equal to u.
 *
 * Atomically adds @a to @v, अगर it was not @u.
 * Returns the old value of @v
 */
अटल अंतरभूत s64 atomic64_fetch_add_unless(atomic64_t *v, s64 a, s64 u)
अणु
	s64 old, temp;

	smp_mb();

	__यंत्र__ __अस्थिर__(
	"1:	llockd  %0, [%2]	\n"
	"	brne	%L0, %L4, 2f	# continue to add since v != u \n"
	"	breq.d	%H0, %H4, 3f	# return since v == u \n"
	"2:				\n"
	"	add.f   %L1, %L0, %L3	\n"
	"	adc     %H1, %H0, %H3	\n"
	"	scondd  %1, [%2]	\n"
	"	bnz     1b		\n"
	"3:				\n"
	: "=&r"(old), "=&r" (temp)
	: "r"(&v->counter), "r"(a), "r"(u)
	: "cc");	/* memory clobber comes from smp_mb() */

	smp_mb();

	वापस old;
पूर्ण
#घोषणा atomic64_fetch_add_unless atomic64_fetch_add_unless

#पूर्ण_अगर	/* !CONFIG_GENERIC_ATOMIC64 */

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर
