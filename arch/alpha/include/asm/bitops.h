<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_BITOPS_H
#घोषणा _ALPHA_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/barrier.h>

/*
 * Copyright 1994, Linus Torvalds.
 */

/*
 * These have to be करोne with अंतरभूत assembly: that way the bit-setting
 * is guaranteed to be atomic. All bit operations वापस 0 अगर the bit
 * was cleared beक्रमe the operation and != 0 अगर it was not.
 *
 * To get proper branch prediction क्रम the मुख्य line, we must branch
 * क्रमward to code at the end of this object's .text section, then
 * branch back to restart the operation.
 *
 * bit 0 is the LSB of addr; bit 64 is the LSB of (addr+1).
 */

अटल अंतरभूत व्योम
set_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ temp;
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l %0,%3\n"
	"	bis %0,%2,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m)
	:"Ir" (1UL << (nr & 31)), "m" (*m));
पूर्ण

/*
 * WARNING: non atomic version.
 */
अटल अंतरभूत व्योम
__set_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	*m |= 1 << (nr & 31);
पूर्ण

अटल अंतरभूत व्योम
clear_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ temp;
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l %0,%3\n"
	"	bic %0,%2,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m)
	:"Ir" (1UL << (nr & 31)), "m" (*m));
पूर्ण

अटल अंतरभूत व्योम
clear_bit_unlock(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	smp_mb();
	clear_bit(nr, addr);
पूर्ण

/*
 * WARNING: non atomic version.
 */
अटल __अंतरभूत__ व्योम
__clear_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	*m &= ~(1 << (nr & 31));
पूर्ण

अटल अंतरभूत व्योम
__clear_bit_unlock(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	smp_mb();
	__clear_bit(nr, addr);
पूर्ण

अटल अंतरभूत व्योम
change_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ temp;
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l %0,%3\n"
	"	xor %0,%2,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m)
	:"Ir" (1UL << (nr & 31)), "m" (*m));
पूर्ण

/*
 * WARNING: non atomic version.
 */
अटल __अंतरभूत__ व्योम
__change_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	*m ^= 1 << (nr & 31);
पूर्ण

अटल अंतरभूत पूर्णांक
test_and_set_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ oldbit;
	अचिन्हित दीर्घ temp;
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	__यंत्र__ __अस्थिर__(
#अगर_घोषित CONFIG_SMP
	"	mb\n"
#पूर्ण_अगर
	"1:	ldl_l %0,%4\n"
	"	and %0,%3,%2\n"
	"	bne %2,2f\n"
	"	xor %0,%3,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,3f\n"
	"2:\n"
#अगर_घोषित CONFIG_SMP
	"	mb\n"
#पूर्ण_अगर
	".subsection 2\n"
	"3:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m), "=&r" (oldbit)
	:"Ir" (1UL << (nr & 31)), "m" (*m) : "memory");

	वापस oldbit != 0;
पूर्ण

अटल अंतरभूत पूर्णांक
test_and_set_bit_lock(अचिन्हित दीर्घ nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ oldbit;
	अचिन्हित दीर्घ temp;
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	__यंत्र__ __अस्थिर__(
	"1:	ldl_l %0,%4\n"
	"	and %0,%3,%2\n"
	"	bne %2,2f\n"
	"	xor %0,%3,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,3f\n"
	"2:\n"
#अगर_घोषित CONFIG_SMP
	"	mb\n"
#पूर्ण_अगर
	".subsection 2\n"
	"3:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m), "=&r" (oldbit)
	:"Ir" (1UL << (nr & 31)), "m" (*m) : "memory");

	वापस oldbit != 0;
पूर्ण

/*
 * WARNING: non atomic version.
 */
अटल अंतरभूत पूर्णांक
__test_and_set_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ mask = 1 << (nr & 0x1f);
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);
	पूर्णांक old = *m;

	*m = old | mask;
	वापस (old & mask) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक
test_and_clear_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ oldbit;
	अचिन्हित दीर्घ temp;
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	__यंत्र__ __अस्थिर__(
#अगर_घोषित CONFIG_SMP
	"	mb\n"
#पूर्ण_अगर
	"1:	ldl_l %0,%4\n"
	"	and %0,%3,%2\n"
	"	beq %2,2f\n"
	"	xor %0,%3,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,3f\n"
	"2:\n"
#अगर_घोषित CONFIG_SMP
	"	mb\n"
#पूर्ण_अगर
	".subsection 2\n"
	"3:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m), "=&r" (oldbit)
	:"Ir" (1UL << (nr & 31)), "m" (*m) : "memory");

	वापस oldbit != 0;
पूर्ण

/*
 * WARNING: non atomic version.
 */
अटल अंतरभूत पूर्णांक
__test_and_clear_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ mask = 1 << (nr & 0x1f);
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);
	पूर्णांक old = *m;

	*m = old & ~mask;
	वापस (old & mask) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक
test_and_change_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ oldbit;
	अचिन्हित दीर्घ temp;
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);

	__यंत्र__ __अस्थिर__(
#अगर_घोषित CONFIG_SMP
	"	mb\n"
#पूर्ण_अगर
	"1:	ldl_l %0,%4\n"
	"	and %0,%3,%2\n"
	"	xor %0,%3,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,3f\n"
#अगर_घोषित CONFIG_SMP
	"	mb\n"
#पूर्ण_अगर
	".subsection 2\n"
	"3:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m), "=&r" (oldbit)
	:"Ir" (1UL << (nr & 31)), "m" (*m) : "memory");

	वापस oldbit != 0;
पूर्ण

/*
 * WARNING: non atomic version.
 */
अटल __अंतरभूत__ पूर्णांक
__test_and_change_bit(अचिन्हित दीर्घ nr, अस्थिर व्योम * addr)
अणु
	अचिन्हित दीर्घ mask = 1 << (nr & 0x1f);
	पूर्णांक *m = ((पूर्णांक *) addr) + (nr >> 5);
	पूर्णांक old = *m;

	*m = old ^ mask;
	वापस (old & mask) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक
test_bit(पूर्णांक nr, स्थिर अस्थिर व्योम * addr)
अणु
	वापस (1UL & (((स्थिर पूर्णांक *) addr)[nr >> 5] >> (nr & 31))) != 0UL;
पूर्ण

/*
 * ffz = Find First Zero in word. Undefined अगर no zero exists,
 * so code should check against ~0UL first..
 *
 * Do a binary search on the bits.  Due to the nature of large
 * स्थिरants on the alpha, it is worthजबतक to split the search.
 */
अटल अंतरभूत अचिन्हित दीर्घ ffz_b(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ sum, x1, x2, x4;

	x = ~x & -~x;		/* set first 0 bit, clear others */
	x1 = x & 0xAA;
	x2 = x & 0xCC;
	x4 = x & 0xF0;
	sum = x2 ? 2 : 0;
	sum += (x4 != 0) * 4;
	sum += (x1 != 0);

	वापस sum;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ffz(अचिन्हित दीर्घ word)
अणु
#अगर defined(CONFIG_ALPHA_EV6) && defined(CONFIG_ALPHA_EV67)
	/* Whee.  EV67 can calculate it directly.  */
	वापस __kernel_cttz(~word);
#अन्यथा
	अचिन्हित दीर्घ bits, qofs, bofs;

	bits = __kernel_cmpbge(word, ~0UL);
	qofs = ffz_b(bits);
	bits = __kernel_extbl(word, qofs);
	bofs = ffz_b(bits);

	वापस qofs*8 + bofs;
#पूर्ण_अगर
पूर्ण

/*
 * __ffs = Find First set bit in word.  Undefined अगर no set bit exists.
 */
अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
#अगर defined(CONFIG_ALPHA_EV6) && defined(CONFIG_ALPHA_EV67)
	/* Whee.  EV67 can calculate it directly.  */
	वापस __kernel_cttz(word);
#अन्यथा
	अचिन्हित दीर्घ bits, qofs, bofs;

	bits = __kernel_cmpbge(0, word);
	qofs = ffz_b(bits);
	bits = __kernel_extbl(word, qofs);
	bofs = ffz_b(~bits);

	वापस qofs*8 + bofs;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित __KERNEL__

/*
 * ffs: find first bit set. This is defined the same way as
 * the libc and compiler builtin ffs routines, thereक्रमe
 * dअगरfers in spirit from the above __ffs.
 */

अटल अंतरभूत पूर्णांक ffs(पूर्णांक word)
अणु
	पूर्णांक result = __ffs(word) + 1;
	वापस word ? result : 0;
पूर्ण

/*
 * fls: find last bit set.
 */
#अगर defined(CONFIG_ALPHA_EV6) && defined(CONFIG_ALPHA_EV67)
अटल अंतरभूत पूर्णांक fls64(अचिन्हित दीर्घ word)
अणु
	वापस 64 - __kernel_ctlz(word);
पूर्ण
#अन्यथा
बाह्य स्थिर अचिन्हित अक्षर __flsm1_tab[256];

अटल अंतरभूत पूर्णांक fls64(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ t, a, r;

	t = __kernel_cmpbge (x, 0x0101010101010101UL);
	a = __flsm1_tab[t];
	t = __kernel_extbl (x, a);
	r = a*8 + __flsm1_tab[t] + (x != 0);

	वापस r;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ x)
अणु
	वापस fls64(x) - 1;
पूर्ण

अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	वापस fls64(x);
पूर्ण

/*
 * hweightN: वापसs the hamming weight (i.e. the number
 * of bits set) of a N-bit word
 */

#अगर defined(CONFIG_ALPHA_EV6) && defined(CONFIG_ALPHA_EV67)
/* Whee.  EV67 can calculate it directly.  */
अटल अंतरभूत अचिन्हित दीर्घ __arch_hweight64(अचिन्हित दीर्घ w)
अणु
	वापस __kernel_ctpop(w);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight32(अचिन्हित पूर्णांक w)
अणु
	वापस __arch_hweight64(w);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight16(अचिन्हित पूर्णांक w)
अणु
	वापस __arch_hweight64(w & 0xffff);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __arch_hweight8(अचिन्हित पूर्णांक w)
अणु
	वापस __arch_hweight64(w & 0xff);
पूर्ण
#अन्यथा
#समावेश <यंत्र-generic/bitops/arch_hweight.h>
#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/स्थिर_hweight.h>

#पूर्ण_अगर /* __KERNEL__ */

#समावेश <यंत्र-generic/bitops/find.h>

#अगर_घोषित __KERNEL__

/*
 * Every architecture must define this function. It's the fastest
 * way of searching a 100-bit biपंचांगap.  It's guaranteed that at least
 * one of the 100 bits is cleared.
 */
अटल अंतरभूत अचिन्हित दीर्घ
sched_find_first_bit(स्थिर अचिन्हित दीर्घ b[2])
अणु
	अचिन्हित दीर्घ b0, b1, ofs, पंचांगp;

	b0 = b[0];
	b1 = b[1];
	ofs = (b0 ? 0 : 64);
	पंचांगp = (b0 ? b0 : b1);

	वापस __ffs(पंचांगp) + ofs;
पूर्ण

#समावेश <यंत्र-generic/bitops/le.h>

#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ALPHA_BITOPS_H */
