<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_BITOPS_H
#घोषणा _ASM_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>
#अगर_अघोषित CONFIG_ARC_HAS_LLSC
#समावेश <यंत्र/smp.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARC_HAS_LLSC

/*
 * Hardware assisted Atomic-R-M-W
 */

#घोषणा BIT_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम op##_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *m)\
अणु									\
	अचिन्हित पूर्णांक temp;						\
									\
	m += nr >> 5;							\
									\
	nr &= 0x1f;							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:	llock       %0, [%1]		\n"			\
	"	" #यंत्र_op " %0, %0, %2	\n"				\
	"	scond       %0, [%1]		\n"			\
	"	bnz         1b			\n"			\
	: "=&r"(temp)	/* Early clobber, to prevent reg reuse */	\
	: "r"(m),	/* Not "m": llock only supports reg direct addr mode */	\
	  "ir"(nr)							\
	: "cc");							\
पूर्ण

/*
 * Semantically:
 *    Test the bit
 *    अगर clear
 *        set it and वापस 0 (old value)
 *    अन्यथा
 *        वापस 1 (old value).
 *
 * Since ARC lacks a equivalent h/w primitive, the bit is set unconditionally
 * and the old value of bit is वापसed
 */
#घोषणा TEST_N_BIT_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत पूर्णांक test_and_##op##_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *m)\
अणु									\
	अचिन्हित दीर्घ old, temp;					\
									\
	m += nr >> 5;							\
									\
	nr &= 0x1f;							\
									\
	/*								\
	 * Explicit full memory barrier needed beक्रमe/after as		\
	 * LLOCK/SCOND themselves करोn't provide any such smenatic	\
	 */								\
	smp_mb();							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:	llock       %0, [%2]	\n"				\
	"	" #यंत्र_op " %1, %0, %3	\n"				\
	"	scond       %1, [%2]	\n"				\
	"	bnz         1b		\n"				\
	: "=&r"(old), "=&r"(temp)					\
	: "r"(m), "ir"(nr)						\
	: "cc");							\
									\
	smp_mb();							\
									\
	वापस (old & (1 << nr)) != 0;					\
पूर्ण

#अन्यथा /* !CONFIG_ARC_HAS_LLSC */

/*
 * Non hardware assisted Atomic-R-M-W
 * Locking would change to irq-disabling only (UP) and spinlocks (SMP)
 *
 * There's "significant" micro-optimization in writing our own variants of
 * bitops (over generic variants)
 *
 * (1) The generic APIs have "signed" @nr जबतक we have it "unsigned"
 *     This aव्योमs extra code to be generated क्रम poपूर्णांकer arithmatic, since
 *     is "not sure" that index is NOT -ve
 * (2) Utilize the fact that ARCompact bit fidding insn (BSET/BCLR/ASL) etc
 *     only consider bottom 5 bits of @nr, so NO need to mask them off.
 *     (GCC Quirk: however क्रम स्थिरant @nr we still need to करो the masking
 *             at compile समय)
 */

#घोषणा BIT_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम op##_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *m)\
अणु									\
	अचिन्हित दीर्घ temp, flags;					\
	m += nr >> 5;							\
									\
	/*								\
	 * spin lock/unlock provide the needed smp_mb() beक्रमe/after	\
	 */								\
	bitops_lock(flags);						\
									\
	temp = *m;							\
	*m = temp c_op (1UL << (nr & 0x1f));					\
									\
	bitops_unlock(flags);						\
पूर्ण

#घोषणा TEST_N_BIT_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत पूर्णांक test_and_##op##_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *m)\
अणु									\
	अचिन्हित दीर्घ old, flags;					\
	m += nr >> 5;							\
									\
	bitops_lock(flags);						\
									\
	old = *m;							\
	*m = old c_op (1UL << (nr & 0x1f));				\
									\
	bitops_unlock(flags);						\
									\
	वापस (old & (1UL << (nr & 0x1f))) != 0;			\
पूर्ण

#पूर्ण_अगर

/***************************************
 * Non atomic variants
 **************************************/

#घोषणा __BIT_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम __##op##_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *m)	\
अणु									\
	अचिन्हित दीर्घ temp;						\
	m += nr >> 5;							\
									\
	temp = *m;							\
	*m = temp c_op (1UL << (nr & 0x1f));				\
पूर्ण

#घोषणा __TEST_N_BIT_OP(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक __test_and_##op##_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *m)\
अणु									\
	अचिन्हित दीर्घ old;						\
	m += nr >> 5;							\
									\
	old = *m;							\
	*m = old c_op (1UL << (nr & 0x1f));				\
									\
	वापस (old & (1UL << (nr & 0x1f))) != 0;			\
पूर्ण

#घोषणा BIT_OPS(op, c_op, यंत्र_op)					\
									\
	/* set_bit(), clear_bit(), change_bit() */			\
	BIT_OP(op, c_op, यंत्र_op)					\
									\
	/* test_and_set_bit(), test_and_clear_bit(), test_and_change_bit() */\
	TEST_N_BIT_OP(op, c_op, यंत्र_op)					\
									\
	/* __set_bit(), __clear_bit(), __change_bit() */		\
	__BIT_OP(op, c_op, यंत्र_op)					\
									\
	/* __test_and_set_bit(), __test_and_clear_bit(), __test_and_change_bit() */\
	__TEST_N_BIT_OP(op, c_op, यंत्र_op)

BIT_OPS(set, |, bset)
BIT_OPS(clear, & ~, bclr)
BIT_OPS(change, ^, bxor)

/*
 * This routine करोesn't need to be atomic.
 */
अटल अंतरभूत पूर्णांक
test_bit(अचिन्हित पूर्णांक nr, स्थिर अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask;

	addr += nr >> 5;

	mask = 1UL << (nr & 0x1f);

	वापस ((mask & *addr) != 0);
पूर्ण

#अगर_घोषित CONFIG_ISA_ARCOMPACT

/*
 * Count the number of zeros, starting from MSB
 * Helper क्रम fls( ) मित्रs
 * This is a pure count, so (1-32) or (0-31) करोesn't apply
 * It could be 0 to 32, based on num of 0's in there
 * clz(0x8000_0000) = 0, clz(0xFFFF_FFFF)=0, clz(0) = 32, clz(1) = 31
 */
अटल अंतरभूत __attribute__ ((स्थिर)) पूर्णांक clz(अचिन्हित पूर्णांक x)
अणु
	अचिन्हित पूर्णांक res;

	__यंत्र__ __अस्थिर__(
	"	norm.f  %0, %1		\n"
	"	mov.n   %0, 0		\n"
	"	add.p   %0, %0, 1	\n"
	: "=r"(res)
	: "r"(x)
	: "cc");

	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक स्थिरant_fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक r = 32;

	अगर (!x)
		वापस 0;
	अगर (!(x & 0xffff0000u)) अणु
		x <<= 16;
		r -= 16;
	पूर्ण
	अगर (!(x & 0xff000000u)) अणु
		x <<= 8;
		r -= 8;
	पूर्ण
	अगर (!(x & 0xf0000000u)) अणु
		x <<= 4;
		r -= 4;
	पूर्ण
	अगर (!(x & 0xc0000000u)) अणु
		x <<= 2;
		r -= 2;
	पूर्ण
	अगर (!(x & 0x80000000u))
		r -= 1;
	वापस r;
पूर्ण

/*
 * fls = Find Last Set in word
 * @result: [1-32]
 * fls(1) = 1, fls(0x80000000) = 32, fls(0) = 0
 */
अटल अंतरभूत __attribute__ ((स्थिर)) पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	अगर (__builtin_स्थिरant_p(x))
	       वापस स्थिरant_fls(x);

	वापस 32 - clz(x);
पूर्ण

/*
 * __fls: Similar to fls, but zero based (0-31)
 */
अटल अंतरभूत __attribute__ ((स्थिर)) पूर्णांक __fls(अचिन्हित दीर्घ x)
अणु
	अगर (!x)
		वापस 0;
	अन्यथा
		वापस fls(x) - 1;
पूर्ण

/*
 * ffs = Find First Set in word (LSB to MSB)
 * @result: [1-32], 0 अगर all 0's
 */
#घोषणा ffs(x)	(अणु अचिन्हित दीर्घ __t = (x); fls(__t & -__t); पूर्ण)

/*
 * __ffs: Similar to ffs, but zero based (0-31)
 */
अटल अंतरभूत __attribute__ ((स्थिर)) अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	अगर (!word)
		वापस word;

	वापस ffs(word) - 1;
पूर्ण

#अन्यथा	/* CONFIG_ISA_ARCV2 */

/*
 * fls = Find Last Set in word
 * @result: [1-32]
 * fls(1) = 1, fls(0x80000000) = 32, fls(0) = 0
 */
अटल अंतरभूत __attribute__ ((स्थिर)) पूर्णांक fls(अचिन्हित दीर्घ x)
अणु
	पूर्णांक n;

	यंत्र अस्थिर(
	"	fls.f	%0, %1		\n"  /* 0:31; 0(Z) अगर src 0 */
	"	add.nz	%0, %0, 1	\n"  /* 0:31 -> 1:32 */
	: "=r"(n)	/* Early clobber not needed */
	: "r"(x)
	: "cc");

	वापस n;
पूर्ण

/*
 * __fls: Similar to fls, but zero based (0-31). Also 0 अगर no bit set
 */
अटल अंतरभूत __attribute__ ((स्थिर)) पूर्णांक __fls(अचिन्हित दीर्घ x)
अणु
	/* FLS insn has exactly same semantics as the API */
	वापस	__builtin_arc_fls(x);
पूर्ण

/*
 * ffs = Find First Set in word (LSB to MSB)
 * @result: [1-32], 0 अगर all 0's
 */
अटल अंतरभूत __attribute__ ((स्थिर)) पूर्णांक ffs(अचिन्हित दीर्घ x)
अणु
	पूर्णांक n;

	यंत्र अस्थिर(
	"	ffs.f	%0, %1		\n"  /* 0:31; 31(Z) अगर src 0 */
	"	add.nz	%0, %0, 1	\n"  /* 0:31 -> 1:32 */
	"	mov.z	%0, 0		\n"  /* 31(Z)-> 0 */
	: "=r"(n)	/* Early clobber not needed */
	: "r"(x)
	: "cc");

	वापस n;
पूर्ण

/*
 * __ffs: Similar to ffs, but zero based (0-31)
 */
अटल अंतरभूत __attribute__ ((स्थिर)) अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ n;

	यंत्र अस्थिर(
	"	ffs.f	%0, %1		\n"  /* 0:31; 31(Z) अगर src 0 */
	"	mov.z	%0, 0		\n"  /* 31(Z)-> 0 */
	: "=r"(n)
	: "r"(x)
	: "cc");

	वापस n;

पूर्ण

#पूर्ण_अगर	/* CONFIG_ISA_ARCOMPACT */

/*
 * ffz = Find First Zero in word.
 * @वापस:[0-31], 32 अगर all 1's
 */
#घोषणा ffz(x)	__ffs(~(x))

#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/lock.h>

#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर
