<शैली गुरु>
/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 *
 * But use these as selकरोm as possible since they are much more slower
 * than regular operations.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 97, 99, 2000, 03, 04, 06 by Ralf Baechle
 */
#अगर_अघोषित _ASM_ATOMIC_H
#घोषणा _ASM_ATOMIC_H

#समावेश <linux/irqflags.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/llsc.h>
#समावेश <यंत्र/sync.h>
#समावेश <यंत्र/war.h>

#घोषणा ATOMIC_OPS(pfx, type)						\
अटल __always_अंतरभूत type pfx##_पढ़ो(स्थिर pfx##_t *v)		\
अणु									\
	वापस READ_ONCE(v->counter);					\
पूर्ण									\
									\
अटल __always_अंतरभूत व्योम pfx##_set(pfx##_t *v, type i)		\
अणु									\
	WRITE_ONCE(v->counter, i);					\
पूर्ण									\
									\
अटल __always_अंतरभूत type pfx##_cmpxchg(pfx##_t *v, type o, type n)	\
अणु									\
	वापस cmpxchg(&v->counter, o, n);				\
पूर्ण									\
									\
अटल __always_अंतरभूत type pfx##_xchg(pfx##_t *v, type n)		\
अणु									\
	वापस xchg(&v->counter, n);					\
पूर्ण

ATOMIC_OPS(atomic, पूर्णांक)

#अगर_घोषित CONFIG_64BIT
# define ATOMIC64_INIT(i)	अणु (i) पूर्ण
ATOMIC_OPS(atomic64, s64)
#पूर्ण_अगर

#घोषणा ATOMIC_OP(pfx, op, type, c_op, यंत्र_op, ll, sc)			\
अटल __अंतरभूत__ व्योम pfx##_##op(type i, pfx##_t * v)			\
अणु									\
	type temp;							\
									\
	अगर (!kernel_uses_llsc) अणु					\
		अचिन्हित दीर्घ flags;					\
									\
		raw_local_irq_save(flags);				\
		v->counter c_op i;					\
		raw_local_irq_restore(flags);				\
		वापस;							\
	पूर्ण								\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_LEVEL "			\n"	\
	"	" __SYNC(full, loongson3_war) "			\n"	\
	"1:	" #ll "	%0, %1		# " #pfx "_" #op "	\n"	\
	"	" #यंत्र_op " %0, %2				\n"	\
	"	" #sc "	%0, %1					\n"	\
	"\t" __SC_BEQZ "%0, 1b					\n"	\
	"	.set	pop					\n"	\
	: "=&r" (temp), "+" GCC_OFF_SMALL_ASM() (v->counter)		\
	: "Ir" (i) : __LLSC_CLOBBER);					\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(pfx, op, type, c_op, यंत्र_op, ll, sc)		\
अटल __अंतरभूत__ type pfx##_##op##_वापस_relaxed(type i, pfx##_t * v)	\
अणु									\
	type temp, result;						\
									\
	अगर (!kernel_uses_llsc) अणु					\
		अचिन्हित दीर्घ flags;					\
									\
		raw_local_irq_save(flags);				\
		result = v->counter;					\
		result c_op i;						\
		v->counter = result;					\
		raw_local_irq_restore(flags);				\
		वापस result;						\
	पूर्ण								\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_LEVEL "			\n"	\
	"	" __SYNC(full, loongson3_war) "			\n"	\
	"1:	" #ll "	%1, %2		# " #pfx "_" #op "_return\n"	\
	"	" #यंत्र_op " %0, %1, %3				\n"	\
	"	" #sc "	%0, %2					\n"	\
	"\t" __SC_BEQZ "%0, 1b					\n"	\
	"	" #यंत्र_op " %0, %1, %3				\n"	\
	"	.set	pop					\n"	\
	: "=&r" (result), "=&r" (temp),					\
	  "+" GCC_OFF_SMALL_ASM() (v->counter)				\
	: "Ir" (i) : __LLSC_CLOBBER);					\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(pfx, op, type, c_op, यंत्र_op, ll, sc)		\
अटल __अंतरभूत__ type pfx##_fetch_##op##_relaxed(type i, pfx##_t * v)	\
अणु									\
	पूर्णांक temp, result;						\
									\
	अगर (!kernel_uses_llsc) अणु					\
		अचिन्हित दीर्घ flags;					\
									\
		raw_local_irq_save(flags);				\
		result = v->counter;					\
		v->counter c_op i;					\
		raw_local_irq_restore(flags);				\
		वापस result;						\
	पूर्ण								\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_LEVEL "			\n"	\
	"	" __SYNC(full, loongson3_war) "			\n"	\
	"1:	" #ll "	%1, %2		# " #pfx "_fetch_" #op "\n"	\
	"	" #यंत्र_op " %0, %1, %3				\n"	\
	"	" #sc "	%0, %2					\n"	\
	"\t" __SC_BEQZ "%0, 1b					\n"	\
	"	.set	pop					\n"	\
	"	move	%0, %1					\n"	\
	: "=&r" (result), "=&r" (temp),					\
	  "+" GCC_OFF_SMALL_ASM() (v->counter)				\
	: "Ir" (i) : __LLSC_CLOBBER);					\
									\
	वापस result;							\
पूर्ण

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(pfx, op, type, c_op, यंत्र_op, ll, sc)			\
	ATOMIC_OP(pfx, op, type, c_op, यंत्र_op, ll, sc)			\
	ATOMIC_OP_RETURN(pfx, op, type, c_op, यंत्र_op, ll, sc)		\
	ATOMIC_FETCH_OP(pfx, op, type, c_op, यंत्र_op, ll, sc)

ATOMIC_OPS(atomic, add, पूर्णांक, +=, addu, ll, sc)
ATOMIC_OPS(atomic, sub, पूर्णांक, -=, subu, ll, sc)

#घोषणा atomic_add_वापस_relaxed	atomic_add_वापस_relaxed
#घोषणा atomic_sub_वापस_relaxed	atomic_sub_वापस_relaxed
#घोषणा atomic_fetch_add_relaxed	atomic_fetch_add_relaxed
#घोषणा atomic_fetch_sub_relaxed	atomic_fetch_sub_relaxed

#अगर_घोषित CONFIG_64BIT
ATOMIC_OPS(atomic64, add, s64, +=, daddu, lld, scd)
ATOMIC_OPS(atomic64, sub, s64, -=, dsubu, lld, scd)
# define atomic64_add_वापस_relaxed	atomic64_add_वापस_relaxed
# define atomic64_sub_वापस_relaxed	atomic64_sub_वापस_relaxed
# define atomic64_fetch_add_relaxed	atomic64_fetch_add_relaxed
# define atomic64_fetch_sub_relaxed	atomic64_fetch_sub_relaxed
#पूर्ण_अगर /* CONFIG_64BIT */

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(pfx, op, type, c_op, यंत्र_op, ll, sc)			\
	ATOMIC_OP(pfx, op, type, c_op, यंत्र_op, ll, sc)			\
	ATOMIC_FETCH_OP(pfx, op, type, c_op, यंत्र_op, ll, sc)

ATOMIC_OPS(atomic, and, पूर्णांक, &=, and, ll, sc)
ATOMIC_OPS(atomic, or, पूर्णांक, |=, or, ll, sc)
ATOMIC_OPS(atomic, xor, पूर्णांक, ^=, xor, ll, sc)

#घोषणा atomic_fetch_and_relaxed	atomic_fetch_and_relaxed
#घोषणा atomic_fetch_or_relaxed		atomic_fetch_or_relaxed
#घोषणा atomic_fetch_xor_relaxed	atomic_fetch_xor_relaxed

#अगर_घोषित CONFIG_64BIT
ATOMIC_OPS(atomic64, and, s64, &=, and, lld, scd)
ATOMIC_OPS(atomic64, or, s64, |=, or, lld, scd)
ATOMIC_OPS(atomic64, xor, s64, ^=, xor, lld, scd)
# define atomic64_fetch_and_relaxed	atomic64_fetch_and_relaxed
# define atomic64_fetch_or_relaxed	atomic64_fetch_or_relaxed
# define atomic64_fetch_xor_relaxed	atomic64_fetch_xor_relaxed
#पूर्ण_अगर

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

/*
 * atomic_sub_अगर_positive - conditionally subtract पूर्णांकeger from atomic variable
 * @i: पूर्णांकeger value to subtract
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically test @v and subtract @i अगर @v is greater or equal than @i.
 * The function वापसs the old value of @v minus @i.
 */
#घोषणा ATOMIC_SIP_OP(pfx, type, op, ll, sc)				\
अटल __अंतरभूत__ पूर्णांक pfx##_sub_अगर_positive(type i, pfx##_t * v)	\
अणु									\
	type temp, result;						\
									\
	smp_mb__beक्रमe_atomic();					\
									\
	अगर (!kernel_uses_llsc) अणु					\
		अचिन्हित दीर्घ flags;					\
									\
		raw_local_irq_save(flags);				\
		result = v->counter;					\
		result -= i;						\
		अगर (result >= 0)					\
			v->counter = result;				\
		raw_local_irq_restore(flags);				\
		smp_mb__after_atomic();					\
		वापस result;						\
	पूर्ण								\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_LEVEL "			\n"	\
	"	" __SYNC(full, loongson3_war) "			\n"	\
	"1:	" #ll "	%1, %2		# atomic_sub_if_positive\n"	\
	"	.set	pop					\n"	\
	"	" #op "	%0, %1, %3				\n"	\
	"	move	%1, %0					\n"	\
	"	bltz	%0, 2f					\n"	\
	"	.set	push					\n"	\
	"	.set	" MIPS_ISA_LEVEL "			\n"	\
	"	" #sc "	%1, %2					\n"	\
	"	" __SC_BEQZ "%1, 1b				\n"	\
	"2:	" __SYNC(full, loongson3_war) "			\n"	\
	"	.set	pop					\n"	\
	: "=&r" (result), "=&r" (temp),					\
	  "+" GCC_OFF_SMALL_ASM() (v->counter)				\
	: "Ir" (i)							\
	: __LLSC_CLOBBER);						\
									\
	/*								\
	 * In the Loongson3 workaround हाल we alपढ़ोy have a		\
	 * completion barrier at 2: above, which is needed due to the	\
	 * bltz that can branch	to code outside of the LL/SC loop. As	\
	 * such, we करोn't need to emit another barrier here.		\
	 */								\
	अगर (__SYNC_loongson3_war == 0)					\
		smp_mb__after_atomic();					\
									\
	वापस result;							\
पूर्ण

ATOMIC_SIP_OP(atomic, पूर्णांक, subu, ll, sc)
#घोषणा atomic_dec_अगर_positive(v)	atomic_sub_अगर_positive(1, v)

#अगर_घोषित CONFIG_64BIT
ATOMIC_SIP_OP(atomic64, s64, dsubu, lld, scd)
#घोषणा atomic64_dec_अगर_positive(v)	atomic64_sub_अगर_positive(1, v)
#पूर्ण_अगर

#अघोषित ATOMIC_SIP_OP

#पूर्ण_अगर /* _ASM_ATOMIC_H */
