<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_BITOPS_H
#घोषणा _ASM_X86_BITOPS_H

/*
 * Copyright 1992, Linus Torvalds.
 *
 * Note: अंतरभूतs with more than a single statement should be marked
 * __always_अंतरभूत to aव्योम problems with older gcc's inlining heuristics.
 */

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/compiler.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/rmwcc.h>
#समावेश <यंत्र/barrier.h>

#अगर BITS_PER_LONG == 32
# define _BITOPS_LONG_SHIFT 5
#या_अगर BITS_PER_LONG == 64
# define _BITOPS_LONG_SHIFT 6
#अन्यथा
# error "Unexpected BITS_PER_LONG"
#पूर्ण_अगर

#घोषणा BIT_64(n)			(U64_C(1) << (n))

/*
 * These have to be करोne with अंतरभूत assembly: that way the bit-setting
 * is guaranteed to be atomic. All bit operations वापस 0 अगर the bit
 * was cleared beक्रमe the operation and != 0 अगर it was not.
 *
 * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).
 */

#घोषणा RLONG_ADDR(x)			 "m" (*(अस्थिर दीर्घ *) (x))
#घोषणा WBYTE_ADDR(x)			"+m" (*(अस्थिर अक्षर *) (x))

#घोषणा ADDR				RLONG_ADDR(addr)

/*
 * We करो the locked ops that करोn't वापस the old value as
 * a mask operation on a byte.
 */
#घोषणा CONST_MASK_ADDR(nr, addr)	WBYTE_ADDR((व्योम *)(addr) + ((nr)>>3))
#घोषणा CONST_MASK(nr)			(1 << ((nr) & 7))

अटल __always_अंतरभूत व्योम
arch_set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अगर (__builtin_स्थिरant_p(nr)) अणु
		यंत्र अस्थिर(LOCK_PREFIX "orb %b1,%0"
			: CONST_MASK_ADDR(nr, addr)
			: "iq" (CONST_MASK(nr))
			: "memory");
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर(LOCK_PREFIX __ASM_SIZE(bts) " %1,%0"
			: : RLONG_ADDR(addr), "Ir" (nr) : "memory");
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम
arch___set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	यंत्र अस्थिर(__ASM_SIZE(bts) " %1,%0" : : ADDR, "Ir" (nr) : "memory");
पूर्ण

अटल __always_अंतरभूत व्योम
arch_clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अगर (__builtin_स्थिरant_p(nr)) अणु
		यंत्र अस्थिर(LOCK_PREFIX "andb %b1,%0"
			: CONST_MASK_ADDR(nr, addr)
			: "iq" (~CONST_MASK(nr)));
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर(LOCK_PREFIX __ASM_SIZE(btr) " %1,%0"
			: : RLONG_ADDR(addr), "Ir" (nr) : "memory");
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम
arch_clear_bit_unlock(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	barrier();
	arch_clear_bit(nr, addr);
पूर्ण

अटल __always_अंतरभूत व्योम
arch___clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	यंत्र अस्थिर(__ASM_SIZE(btr) " %1,%0" : : ADDR, "Ir" (nr) : "memory");
पूर्ण

अटल __always_अंतरभूत bool
arch_clear_bit_unlock_is_negative_byte(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	bool negative;
	यंत्र अस्थिर(LOCK_PREFIX "andb %2,%1"
		CC_SET(s)
		: CC_OUT(s) (negative), WBYTE_ADDR(addr)
		: "ir" ((अक्षर) ~(1 << nr)) : "memory");
	वापस negative;
पूर्ण
#घोषणा arch_clear_bit_unlock_is_negative_byte                                 \
	arch_clear_bit_unlock_is_negative_byte

अटल __always_अंतरभूत व्योम
arch___clear_bit_unlock(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	arch___clear_bit(nr, addr);
पूर्ण

अटल __always_अंतरभूत व्योम
arch___change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	यंत्र अस्थिर(__ASM_SIZE(btc) " %1,%0" : : ADDR, "Ir" (nr) : "memory");
पूर्ण

अटल __always_अंतरभूत व्योम
arch_change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अगर (__builtin_स्थिरant_p(nr)) अणु
		यंत्र अस्थिर(LOCK_PREFIX "xorb %b1,%0"
			: CONST_MASK_ADDR(nr, addr)
			: "iq" (CONST_MASK(nr)));
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर(LOCK_PREFIX __ASM_SIZE(btc) " %1,%0"
			: : RLONG_ADDR(addr), "Ir" (nr) : "memory");
	पूर्ण
पूर्ण

अटल __always_अंतरभूत bool
arch_test_and_set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस GEN_BINARY_RMWcc(LOCK_PREFIX __ASM_SIZE(bts), *addr, c, "Ir", nr);
पूर्ण

अटल __always_अंतरभूत bool
arch_test_and_set_bit_lock(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस arch_test_and_set_bit(nr, addr);
पूर्ण

अटल __always_अंतरभूत bool
arch___test_and_set_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	bool oldbit;

	यंत्र(__ASM_SIZE(bts) " %2,%1"
	    CC_SET(c)
	    : CC_OUT(c) (oldbit)
	    : ADDR, "Ir" (nr) : "memory");
	वापस oldbit;
पूर्ण

अटल __always_अंतरभूत bool
arch_test_and_clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस GEN_BINARY_RMWcc(LOCK_PREFIX __ASM_SIZE(btr), *addr, c, "Ir", nr);
पूर्ण

/*
 * Note: the operation is perक्रमmed atomically with respect to
 * the local CPU, but not other CPUs. Portable code should not
 * rely on this behaviour.
 * KVM relies on this behaviour on x86 क्रम modअगरying memory that is also
 * accessed from a hypervisor on the same CPU अगर running in a VM: करोn't change
 * this without also updating arch/x86/kernel/kvm.c
 */
अटल __always_अंतरभूत bool
arch___test_and_clear_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	bool oldbit;

	यंत्र अस्थिर(__ASM_SIZE(btr) " %2,%1"
		     CC_SET(c)
		     : CC_OUT(c) (oldbit)
		     : ADDR, "Ir" (nr) : "memory");
	वापस oldbit;
पूर्ण

अटल __always_अंतरभूत bool
arch___test_and_change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	bool oldbit;

	यंत्र अस्थिर(__ASM_SIZE(btc) " %2,%1"
		     CC_SET(c)
		     : CC_OUT(c) (oldbit)
		     : ADDR, "Ir" (nr) : "memory");

	वापस oldbit;
पूर्ण

अटल __always_अंतरभूत bool
arch_test_and_change_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस GEN_BINARY_RMWcc(LOCK_PREFIX __ASM_SIZE(btc), *addr, c, "Ir", nr);
पूर्ण

अटल __always_अंतरभूत bool स्थिरant_test_bit(दीर्घ nr, स्थिर अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस ((1UL << (nr & (BITS_PER_LONG-1))) &
		(addr[nr >> _BITOPS_LONG_SHIFT])) != 0;
पूर्ण

अटल __always_अंतरभूत bool variable_test_bit(दीर्घ nr, अस्थिर स्थिर अचिन्हित दीर्घ *addr)
अणु
	bool oldbit;

	यंत्र अस्थिर(__ASM_SIZE(bt) " %2,%1"
		     CC_SET(c)
		     : CC_OUT(c) (oldbit)
		     : "m" (*(अचिन्हित दीर्घ *)addr), "Ir" (nr) : "memory");

	वापस oldbit;
पूर्ण

#घोषणा arch_test_bit(nr, addr)			\
	(__builtin_स्थिरant_p((nr))		\
	 ? स्थिरant_test_bit((nr), (addr))	\
	 : variable_test_bit((nr), (addr)))

/**
 * __ffs - find first set bit in word
 * @word: The word to search
 *
 * Undefined अगर no bit exists, so code should check against 0 first.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	यंत्र("rep; bsf %1,%0"
		: "=r" (word)
		: "rm" (word));
	वापस word;
पूर्ण

/**
 * ffz - find first zero bit in word
 * @word: The word to search
 *
 * Undefined अगर no zero exists, so code should check against ~0UL first.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ ffz(अचिन्हित दीर्घ word)
अणु
	यंत्र("rep; bsf %1,%0"
		: "=r" (word)
		: "r" (~word));
	वापस word;
पूर्ण

/*
 * __fls: find last set bit in word
 * @word: The word to search
 *
 * Undefined अगर no set bit exists, so code should check against 0 first.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ word)
अणु
	यंत्र("bsr %1,%0"
	    : "=r" (word)
	    : "rm" (word));
	वापस word;
पूर्ण

#अघोषित ADDR

#अगर_घोषित __KERNEL__
/**
 * ffs - find first set bit in word
 * @x: the word to search
 *
 * This is defined the same way as the libc and compiler builtin ffs
 * routines, thereक्रमe dअगरfers in spirit from the other bitops.
 *
 * ffs(value) वापसs 0 अगर value is 0 or the position of the first
 * set bit अगर value is nonzero. The first (least signअगरicant) bit
 * is at position 1.
 */
अटल __always_अंतरभूत पूर्णांक ffs(पूर्णांक x)
अणु
	पूर्णांक r;

#अगर_घोषित CONFIG_X86_64
	/*
	 * AMD64 says BSFL won't clobber the dest reg अगर x==0; Intel64 says the
	 * dest reg is undefined अगर x==0, but their CPU architect says its
	 * value is written to set it to the same as beक्रमe, except that the
	 * top 32 bits will be cleared.
	 *
	 * We cannot करो this on 32 bits because at the very least some
	 * 486 CPUs did not behave this way.
	 */
	यंत्र("bsfl %1,%0"
	    : "=r" (r)
	    : "rm" (x), "0" (-1));
#या_अगर defined(CONFIG_X86_CMOV)
	यंत्र("bsfl %1,%0\n\t"
	    "cmovzl %2,%0"
	    : "=&r" (r) : "rm" (x), "r" (-1));
#अन्यथा
	यंत्र("bsfl %1,%0\n\t"
	    "jnz 1f\n\t"
	    "movl $-1,%0\n"
	    "1:" : "=r" (r) : "rm" (x));
#पूर्ण_अगर
	वापस r + 1;
पूर्ण

/**
 * fls - find last set bit in word
 * @x: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffs, but वापसs the position of the most signअगरicant set bit.
 *
 * fls(value) वापसs 0 अगर value is 0 or the position of the last
 * set bit अगर value is nonzero. The last (most signअगरicant) bit is
 * at position 32.
 */
अटल __always_अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक r;

#अगर_घोषित CONFIG_X86_64
	/*
	 * AMD64 says BSRL won't clobber the dest reg अगर x==0; Intel64 says the
	 * dest reg is undefined अगर x==0, but their CPU architect says its
	 * value is written to set it to the same as beक्रमe, except that the
	 * top 32 bits will be cleared.
	 *
	 * We cannot करो this on 32 bits because at the very least some
	 * 486 CPUs did not behave this way.
	 */
	यंत्र("bsrl %1,%0"
	    : "=r" (r)
	    : "rm" (x), "0" (-1));
#या_अगर defined(CONFIG_X86_CMOV)
	यंत्र("bsrl %1,%0\n\t"
	    "cmovzl %2,%0"
	    : "=&r" (r) : "rm" (x), "rm" (-1));
#अन्यथा
	यंत्र("bsrl %1,%0\n\t"
	    "jnz 1f\n\t"
	    "movl $-1,%0\n"
	    "1:" : "=r" (r) : "rm" (x));
#पूर्ण_अगर
	वापस r + 1;
पूर्ण

/**
 * fls64 - find last set bit in a 64-bit word
 * @x: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffsll, but वापसs the position of the most signअगरicant set bit.
 *
 * fls64(value) वापसs 0 अगर value is 0 or the position of the last
 * set bit अगर value is nonzero. The last (most signअगरicant) bit is
 * at position 64.
 */
#अगर_घोषित CONFIG_X86_64
अटल __always_अंतरभूत पूर्णांक fls64(__u64 x)
अणु
	पूर्णांक bitpos = -1;
	/*
	 * AMD64 says BSRQ won't clobber the dest reg अगर x==0; Intel64 says the
	 * dest reg is undefined अगर x==0, but their CPU architect says its
	 * value is written to set it to the same as beक्रमe.
	 */
	यंत्र("bsrq %1,%q0"
	    : "+r" (bitpos)
	    : "rm" (x));
	वापस bitpos + 1;
पूर्ण
#अन्यथा
#समावेश <यंत्र-generic/bitops/fls64.h>
#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/find.h>

#समावेश <यंत्र-generic/bitops/sched.h>

#समावेश <यंत्र/arch_hweight.h>

#समावेश <यंत्र-generic/bitops/स्थिर_hweight.h>

#समावेश <यंत्र-generic/bitops/instrumented-atomic.h>
#समावेश <यंत्र-generic/bitops/instrumented-non-atomic.h>
#समावेश <यंत्र-generic/bitops/instrumented-lock.h>

#समावेश <यंत्र-generic/bitops/le.h>

#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_X86_BITOPS_H */
