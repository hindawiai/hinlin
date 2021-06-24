<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_BITOPS_H
#घोषणा _ASM_IA64_BITOPS_H

/*
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * 02/06/02 find_next_bit() and find_first_bit() added from Erich Focht's ia64
 * O(1) scheduler patch
 */

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/barrier.h>

/**
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * अगर you करो not require the atomic guarantees.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 *
 * The address must be (at least) "long" aligned.
 * Note that there are driver (e.g., eepro100) which use these operations to
 * operate on hw-defined data-काष्ठाures, so we can't easily change these
 * operations to क्रमce a bigger alignment.
 *
 * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).
 */
अटल __अंतरभूत__ व्योम
set_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 bit, old, new;
	अस्थिर __u32 *m;
	CMPXCHG_BUGCHECK_DECL

	m = (अस्थिर __u32 *) addr + (nr >> 5);
	bit = 1 << (nr & 31);
	करो अणु
		CMPXCHG_BUGCHECK(m);
		old = *m;
		new = old | bit;
	पूर्ण जबतक (cmpxchg_acq(m, old, new) != old);
पूर्ण

/**
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
अटल __अंतरभूत__ व्योम
__set_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	*((__u32 *) addr + (nr >> 5)) |= (1 << (nr & 31));
पूर्ण

/**
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit() is atomic and may not be reordered.  However, it करोes
 * not contain a memory barrier, so अगर it is used क्रम locking purposes,
 * you should call smp_mb__beक्रमe_atomic() and/or smp_mb__after_atomic()
 * in order to ensure changes are visible on other processors.
 */
अटल __अंतरभूत__ व्योम
clear_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 mask, old, new;
	अस्थिर __u32 *m;
	CMPXCHG_BUGCHECK_DECL

	m = (अस्थिर __u32 *) addr + (nr >> 5);
	mask = ~(1 << (nr & 31));
	करो अणु
		CMPXCHG_BUGCHECK(m);
		old = *m;
		new = old & mask;
	पूर्ण जबतक (cmpxchg_acq(m, old, new) != old);
पूर्ण

/**
 * clear_bit_unlock - Clears a bit in memory with release
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit_unlock() is atomic and may not be reordered.  It करोes
 * contain a memory barrier suitable क्रम unlock type operations.
 */
अटल __अंतरभूत__ व्योम
clear_bit_unlock (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 mask, old, new;
	अस्थिर __u32 *m;
	CMPXCHG_BUGCHECK_DECL

	m = (अस्थिर __u32 *) addr + (nr >> 5);
	mask = ~(1 << (nr & 31));
	करो अणु
		CMPXCHG_BUGCHECK(m);
		old = *m;
		new = old & mask;
	पूर्ण जबतक (cmpxchg_rel(m, old, new) != old);
पूर्ण

/**
 * __clear_bit_unlock - Non-atomically clears a bit in memory with release
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * Similarly to clear_bit_unlock, the implementation uses a store
 * with release semantics. See also arch_spin_unlock().
 */
अटल __अंतरभूत__ व्योम
__clear_bit_unlock(पूर्णांक nr, व्योम *addr)
अणु
	__u32 * स्थिर m = (__u32 *) addr + (nr >> 5);
	__u32 स्थिर new = *m & ~(1 << (nr & 31));

	ia64_st4_rel_nta(m, new);
पूर्ण

/**
 * __clear_bit - Clears a bit in memory (non-atomic version)
 * @nr: the bit to clear
 * @addr: the address to start counting from
 *
 * Unlike clear_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
अटल __अंतरभूत__ व्योम
__clear_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	*((__u32 *) addr + (nr >> 5)) &= ~(1 << (nr & 31));
पूर्ण

/**
 * change_bit - Toggle a bit in memory
 * @nr: Bit to toggle
 * @addr: Address to start counting from
 *
 * change_bit() is atomic and may not be reordered.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल __अंतरभूत__ व्योम
change_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 bit, old, new;
	अस्थिर __u32 *m;
	CMPXCHG_BUGCHECK_DECL

	m = (अस्थिर __u32 *) addr + (nr >> 5);
	bit = (1 << (nr & 31));
	करो अणु
		CMPXCHG_BUGCHECK(m);
		old = *m;
		new = old ^ bit;
	पूर्ण जबतक (cmpxchg_acq(m, old, new) != old);
पूर्ण

/**
 * __change_bit - Toggle a bit in memory
 * @nr: the bit to toggle
 * @addr: the address to start counting from
 *
 * Unlike change_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
अटल __अंतरभूत__ व्योम
__change_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	*((__u32 *) addr + (nr >> 5)) ^= (1 << (nr & 31));
पूर्ण

/**
 * test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.  
 * It also implies the acquisition side of the memory barrier.
 */
अटल __अंतरभूत__ पूर्णांक
test_and_set_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 bit, old, new;
	अस्थिर __u32 *m;
	CMPXCHG_BUGCHECK_DECL

	m = (अस्थिर __u32 *) addr + (nr >> 5);
	bit = 1 << (nr & 31);
	करो अणु
		CMPXCHG_BUGCHECK(m);
		old = *m;
		new = old | bit;
	पूर्ण जबतक (cmpxchg_acq(m, old, new) != old);
	वापस (old & bit) != 0;
पूर्ण

/**
 * test_and_set_bit_lock - Set a bit and वापस its old value क्रम lock
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This is the same as test_and_set_bit on ia64
 */
#घोषणा test_and_set_bit_lock test_and_set_bit

/**
 * __test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.  
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
अटल __अंतरभूत__ पूर्णांक
__test_and_set_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 *p = (__u32 *) addr + (nr >> 5);
	__u32 m = 1 << (nr & 31);
	पूर्णांक oldbitset = (*p & m) != 0;

	*p |= m;
	वापस oldbitset;
पूर्ण

/**
 * test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.  
 * It also implies the acquisition side of the memory barrier.
 */
अटल __अंतरभूत__ पूर्णांक
test_and_clear_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 mask, old, new;
	अस्थिर __u32 *m;
	CMPXCHG_BUGCHECK_DECL

	m = (अस्थिर __u32 *) addr + (nr >> 5);
	mask = ~(1 << (nr & 31));
	करो अणु
		CMPXCHG_BUGCHECK(m);
		old = *m;
		new = old & mask;
	पूर्ण जबतक (cmpxchg_acq(m, old, new) != old);
	वापस (old & ~mask) != 0;
पूर्ण

/**
 * __test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.  
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
अटल __अंतरभूत__ पूर्णांक
__test_and_clear_bit(पूर्णांक nr, अस्थिर व्योम * addr)
अणु
	__u32 *p = (__u32 *) addr + (nr >> 5);
	__u32 m = 1 << (nr & 31);
	पूर्णांक oldbitset = (*p & m) != 0;

	*p &= ~m;
	वापस oldbitset;
पूर्ण

/**
 * test_and_change_bit - Change a bit and वापस its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.  
 * It also implies the acquisition side of the memory barrier.
 */
अटल __अंतरभूत__ पूर्णांक
test_and_change_bit (पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	__u32 bit, old, new;
	अस्थिर __u32 *m;
	CMPXCHG_BUGCHECK_DECL

	m = (अस्थिर __u32 *) addr + (nr >> 5);
	bit = (1 << (nr & 31));
	करो अणु
		CMPXCHG_BUGCHECK(m);
		old = *m;
		new = old ^ bit;
	पूर्ण जबतक (cmpxchg_acq(m, old, new) != old);
	वापस (old & bit) != 0;
पूर्ण

/**
 * __test_and_change_bit - Change a bit and वापस its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 */
अटल __अंतरभूत__ पूर्णांक
__test_and_change_bit (पूर्णांक nr, व्योम *addr)
अणु
	__u32 old, bit = (1 << (nr & 31));
	__u32 *m = (__u32 *) addr + (nr >> 5);

	old = *m;
	*m = old ^ bit;
	वापस (old & bit) != 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
test_bit (पूर्णांक nr, स्थिर अस्थिर व्योम *addr)
अणु
	वापस 1 & (((स्थिर अस्थिर __u32 *) addr)[nr >> 5] >> (nr & 31));
पूर्ण

/**
 * ffz - find the first zero bit in a दीर्घ word
 * @x: The दीर्घ word to find the bit in
 *
 * Returns the bit-number (0..63) of the first (least signअगरicant) zero bit.
 * Undefined अगर no zero exists, so code should check against ~0UL first...
 */
अटल अंतरभूत अचिन्हित दीर्घ
ffz (अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ result;

	result = ia64_popcnt(x & (~x - 1));
	वापस result;
पूर्ण

/**
 * __ffs - find first bit in word.
 * @x: The word to search
 *
 * Undefined अगर no bit exists, so code should check against 0 first.
 */
अटल __अंतरभूत__ अचिन्हित दीर्घ
__ffs (अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ result;

	result = ia64_popcnt((x-1) & ~x);
	वापस result;
पूर्ण

#अगर_घोषित __KERNEL__

/*
 * Return bit number of last (most-signअगरicant) bit set.  Undefined
 * क्रम x==0.  Bits are numbered from 0..63 (e.g., ia64_fls(9) == 3).
 */
अटल अंतरभूत अचिन्हित दीर्घ
ia64_fls (अचिन्हित दीर्घ x)
अणु
	दीर्घ द्विगुन d = x;
	दीर्घ exp;

	exp = ia64_getf_exp(d);
	वापस exp - 0xffff;
पूर्ण

/*
 * Find the last (most signअगरicant) bit set.  Returns 0 क्रम x==0 and
 * bits are numbered from 1..32 (e.g., fls(9) == 4).
 */
अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक t)
अणु
	अचिन्हित दीर्घ x = t & 0xffffffffu;

	अगर (!x)
		वापस 0;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	वापस ia64_popcnt(x);
पूर्ण

/*
 * Find the last (most signअगरicant) bit set.  Undefined क्रम x==0.
 * Bits are numbered from 0..63 (e.g., __fls(9) == 3).
 */
अटल अंतरभूत अचिन्हित दीर्घ
__fls (अचिन्हित दीर्घ x)
अणु
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	वापस ia64_popcnt(x) - 1;
पूर्ण

#समावेश <यंत्र-generic/bitops/fls64.h>

#समावेश <यंत्र-generic/bitops/builtin-ffs.h>

/*
 * hweightN: वापसs the hamming weight (i.e. the number
 * of bits set) of a N-bit word
 */
अटल __अंतरभूत__ अचिन्हित दीर्घ __arch_hweight64(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ result;
	result = ia64_popcnt(x);
	वापस result;
पूर्ण

#घोषणा __arch_hweight32(x) ((अचिन्हित पूर्णांक) __arch_hweight64((x) & 0xfffffffful))
#घोषणा __arch_hweight16(x) ((अचिन्हित पूर्णांक) __arch_hweight64((x) & 0xfffful))
#घोषणा __arch_hweight8(x)  ((अचिन्हित पूर्णांक) __arch_hweight64((x) & 0xfful))

#समावेश <यंत्र-generic/bitops/स्थिर_hweight.h>

#पूर्ण_अगर /* __KERNEL__ */

#समावेश <यंत्र-generic/bitops/find.h>

#अगर_घोषित __KERNEL__

#समावेश <यंत्र-generic/bitops/le.h>

#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#समावेश <यंत्र-generic/bitops/sched.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_IA64_BITOPS_H */
