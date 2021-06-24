<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 1999,2013
 *
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *
 * The description below was taken in large parts from the घातerpc
 * bitops header file:
 * Within a word, bits are numbered LSB first.  Lot's of places make
 * this assumption by directly testing bits with (val & (1<<nr)).
 * This can cause confusion क्रम large (> 1 word) biपंचांगaps on a
 * big-endian प्रणाली because, unlike little endian, the number of each
 * bit depends on the word size.
 *
 * The bitop functions are defined to work on अचिन्हित दीर्घs, so the bits
 * end up numbered:
 *   |63..............0|127............64|191...........128|255...........192|
 *
 * We also have special functions which work with an MSB0 encoding.
 * The bits are numbered:
 *   |0..............63|64............127|128...........191|192...........255|
 *
 * The मुख्य dअगरference is that bit 0-63 in the bit number field needs to be
 * reversed compared to the LSB0 encoded bit fields. This can be achieved by
 * XOR with 0x3f.
 *
 */

#अगर_अघोषित _S390_BITOPS_H
#घोषणा _S390_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/typecheck.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/atomic_ops.h>
#समावेश <यंत्र/barrier.h>

#घोषणा __BITOPS_WORDS(bits) (((bits) + BITS_PER_LONG - 1) / BITS_PER_LONG)

अटल अंतरभूत अचिन्हित दीर्घ *
__bitops_word(अचिन्हित दीर्घ nr, स्थिर अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ addr;

	addr = (अचिन्हित दीर्घ)ptr + ((nr ^ (nr & (BITS_PER_LONG - 1))) >> 3);
	वापस (अचिन्हित दीर्घ *)addr;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __bitops_mask(अचिन्हित दीर्घ nr)
अणु
	वापस 1UL << (nr & (BITS_PER_LONG - 1));
पूर्ण

अटल __always_अंतरभूत व्योम arch_set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);

	__atomic64_or(mask, (दीर्घ *)addr);
पूर्ण

अटल __always_अंतरभूत व्योम arch_clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);

	__atomic64_and(~mask, (दीर्घ *)addr);
पूर्ण

अटल __always_अंतरभूत व्योम arch_change_bit(अचिन्हित दीर्घ nr,
					    अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);

	__atomic64_xor(mask, (दीर्घ *)addr);
पूर्ण

अटल अंतरभूत bool arch_test_and_set_bit(अचिन्हित दीर्घ nr,
					 अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);
	अचिन्हित दीर्घ old;

	old = __atomic64_or_barrier(mask, (दीर्घ *)addr);
	वापस old & mask;
पूर्ण

अटल अंतरभूत bool arch_test_and_clear_bit(अचिन्हित दीर्घ nr,
					   अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);
	अचिन्हित दीर्घ old;

	old = __atomic64_and_barrier(~mask, (दीर्घ *)addr);
	वापस old & mask;
पूर्ण

अटल अंतरभूत bool arch_test_and_change_bit(अचिन्हित दीर्घ nr,
					    अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);
	अचिन्हित दीर्घ old;

	old = __atomic64_xor_barrier(mask, (दीर्घ *)addr);
	वापस old & mask;
पूर्ण

अटल अंतरभूत व्योम arch___set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);

	*addr |= mask;
पूर्ण

अटल अंतरभूत व्योम arch___clear_bit(अचिन्हित दीर्घ nr,
				    अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);

	*addr &= ~mask;
पूर्ण

अटल अंतरभूत व्योम arch___change_bit(अचिन्हित दीर्घ nr,
				     अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);

	*addr ^= mask;
पूर्ण

अटल अंतरभूत bool arch___test_and_set_bit(अचिन्हित दीर्घ nr,
					   अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);
	अचिन्हित दीर्घ old;

	old = *addr;
	*addr |= mask;
	वापस old & mask;
पूर्ण

अटल अंतरभूत bool arch___test_and_clear_bit(अचिन्हित दीर्घ nr,
					     अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);
	अचिन्हित दीर्घ old;

	old = *addr;
	*addr &= ~mask;
	वापस old & mask;
पूर्ण

अटल अंतरभूत bool arch___test_and_change_bit(अचिन्हित दीर्घ nr,
					      अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);
	अचिन्हित दीर्घ old;

	old = *addr;
	*addr ^= mask;
	वापस old & mask;
पूर्ण

अटल अंतरभूत bool arch_test_bit(अचिन्हित दीर्घ nr,
				 स्थिर अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	स्थिर अस्थिर अचिन्हित दीर्घ *addr = __bitops_word(nr, ptr);
	अचिन्हित दीर्घ mask = __bitops_mask(nr);

	वापस *addr & mask;
पूर्ण

अटल अंतरभूत bool arch_test_and_set_bit_lock(अचिन्हित दीर्घ nr,
					      अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अगर (arch_test_bit(nr, ptr))
		वापस 1;
	वापस arch_test_and_set_bit(nr, ptr);
पूर्ण

अटल अंतरभूत व्योम arch_clear_bit_unlock(अचिन्हित दीर्घ nr,
					 अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	smp_mb__beक्रमe_atomic();
	arch_clear_bit(nr, ptr);
पूर्ण

अटल अंतरभूत व्योम arch___clear_bit_unlock(अचिन्हित दीर्घ nr,
					   अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	smp_mb();
	arch___clear_bit(nr, ptr);
पूर्ण

#समावेश <यंत्र-generic/bitops/instrumented-atomic.h>
#समावेश <यंत्र-generic/bitops/instrumented-non-atomic.h>
#समावेश <यंत्र-generic/bitops/instrumented-lock.h>

/*
 * Functions which use MSB0 bit numbering.
 * The bits are numbered:
 *   |0..............63|64............127|128...........191|192...........255|
 */
अचिन्हित दीर्घ find_first_bit_inv(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size);
अचिन्हित दीर्घ find_next_bit_inv(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ offset);

#घोषणा क्रम_each_set_bit_inv(bit, addr, size)				\
	क्रम ((bit) = find_first_bit_inv((addr), (size));		\
	     (bit) < (size);						\
	     (bit) = find_next_bit_inv((addr), (size), (bit) + 1))

अटल अंतरभूत व्योम set_bit_inv(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	वापस set_bit(nr ^ (BITS_PER_LONG - 1), ptr);
पूर्ण

अटल अंतरभूत व्योम clear_bit_inv(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	वापस clear_bit(nr ^ (BITS_PER_LONG - 1), ptr);
पूर्ण

अटल अंतरभूत bool test_and_clear_bit_inv(अचिन्हित दीर्घ nr,
					  अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	वापस test_and_clear_bit(nr ^ (BITS_PER_LONG - 1), ptr);
पूर्ण

अटल अंतरभूत व्योम __set_bit_inv(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	वापस __set_bit(nr ^ (BITS_PER_LONG - 1), ptr);
पूर्ण

अटल अंतरभूत व्योम __clear_bit_inv(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	वापस __clear_bit(nr ^ (BITS_PER_LONG - 1), ptr);
पूर्ण

अटल अंतरभूत bool test_bit_inv(अचिन्हित दीर्घ nr,
				स्थिर अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	वापस test_bit(nr ^ (BITS_PER_LONG - 1), ptr);
पूर्ण

#अगर_घोषित CONFIG_HAVE_MARCH_Z9_109_FEATURES

/**
 * __flogr - find lefपंचांगost one
 * @word - The word to search
 *
 * Returns the bit number of the most signअगरicant bit set,
 * where the most signअगरicant bit has bit number 0.
 * If no bit is set this function वापसs 64.
 */
अटल अंतरभूत अचिन्हित अक्षर __flogr(अचिन्हित दीर्घ word)
अणु
	अगर (__builtin_स्थिरant_p(word)) अणु
		अचिन्हित दीर्घ bit = 0;

		अगर (!word)
			वापस 64;
		अगर (!(word & 0xffffffff00000000UL)) अणु
			word <<= 32;
			bit += 32;
		पूर्ण
		अगर (!(word & 0xffff000000000000UL)) अणु
			word <<= 16;
			bit += 16;
		पूर्ण
		अगर (!(word & 0xff00000000000000UL)) अणु
			word <<= 8;
			bit += 8;
		पूर्ण
		अगर (!(word & 0xf000000000000000UL)) अणु
			word <<= 4;
			bit += 4;
		पूर्ण
		अगर (!(word & 0xc000000000000000UL)) अणु
			word <<= 2;
			bit += 2;
		पूर्ण
		अगर (!(word & 0x8000000000000000UL)) अणु
			word <<= 1;
			bit += 1;
		पूर्ण
		वापस bit;
	पूर्ण अन्यथा अणु
		रेजिस्टर अचिन्हित दीर्घ bit यंत्र("4") = word;
		रेजिस्टर अचिन्हित दीर्घ out यंत्र("5");

		यंत्र अस्थिर(
			"       flogr   %[bit],%[bit]\n"
			: [bit] "+d" (bit), [out] "=d" (out) : : "cc");
		वापस bit;
	पूर्ण
पूर्ण

/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined अगर no bit exists, so code should check against 0 first.
 */
अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	वापस __flogr(-word & word) ^ (BITS_PER_LONG - 1);
पूर्ण

/**
 * ffs - find first bit set
 * @word: the word to search
 *
 * This is defined the same way as the libc and
 * compiler builtin ffs routines (man ffs).
 */
अटल अंतरभूत पूर्णांक ffs(पूर्णांक word)
अणु
	अचिन्हित दीर्घ mask = 2 * BITS_PER_LONG - 1;
	अचिन्हित पूर्णांक val = (अचिन्हित पूर्णांक)word;

	वापस (1 + (__flogr(-val & val) ^ (BITS_PER_LONG - 1))) & mask;
पूर्ण

/**
 * __fls - find last (most-signअगरicant) set bit in a दीर्घ word
 * @word: the word to search
 *
 * Undefined अगर no set bit exists, so code should check against 0 first.
 */
अटल अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ word)
अणु
	वापस __flogr(word) ^ (BITS_PER_LONG - 1);
पूर्ण

/**
 * fls64 - find last set bit in a 64-bit word
 * @word: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffsll, but वापसs the position of the most signअगरicant set bit.
 *
 * fls64(value) वापसs 0 अगर value is 0 or the position of the last
 * set bit अगर value is nonzero. The last (most signअगरicant) bit is
 * at position 64.
 */
अटल अंतरभूत पूर्णांक fls64(अचिन्हित दीर्घ word)
अणु
	अचिन्हित दीर्घ mask = 2 * BITS_PER_LONG - 1;

	वापस (1 + (__flogr(word) ^ (BITS_PER_LONG - 1))) & mask;
पूर्ण

/**
 * fls - find last (most-signअगरicant) bit set
 * @word: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक word)
अणु
	वापस fls64(word);
पूर्ण

#अन्यथा /* CONFIG_HAVE_MARCH_Z9_109_FEATURES */

#समावेश <यंत्र-generic/bitops/__ffs.h>
#समावेश <यंत्र-generic/bitops/ffs.h>
#समावेश <यंत्र-generic/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/fls.h>
#समावेश <यंत्र-generic/bitops/fls64.h>

#पूर्ण_अगर /* CONFIG_HAVE_MARCH_Z9_109_FEATURES */

#समावेश <यंत्र-generic/bitops/ffz.h>
#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#पूर्ण_अगर /* _S390_BITOPS_H */
