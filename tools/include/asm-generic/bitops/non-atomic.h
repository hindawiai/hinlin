<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_NON_ATOMIC_H_
#घोषणा _ASM_GENERIC_BITOPS_NON_ATOMIC_H_

#समावेश <यंत्र/types.h>

/**
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
अटल अंतरभूत व्योम __set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);

	*p  |= mask;
पूर्ण

अटल अंतरभूत व्योम __clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);

	*p &= ~mask;
पूर्ण

/**
 * __change_bit - Toggle a bit in memory
 * @nr: the bit to change
 * @addr: the address to start counting from
 *
 * Unlike change_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
अटल अंतरभूत व्योम __change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);

	*p ^= mask;
पूर्ण

/**
 * __test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
अटल अंतरभूत पूर्णांक __test_and_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old = *p;

	*p = old | mask;
	वापस (old & mask) != 0;
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
अटल अंतरभूत पूर्णांक __test_and_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old = *p;

	*p = old & ~mask;
	वापस (old & mask) != 0;
पूर्ण

/* WARNING: non atomic and it can be reordered! */
अटल अंतरभूत पूर्णांक __test_and_change_bit(पूर्णांक nr,
					    अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old = *p;

	*p = old ^ mask;
	वापस (old & mask) != 0;
पूर्ण

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
अटल अंतरभूत पूर्णांक test_bit(पूर्णांक nr, स्थिर अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_NON_ATOMIC_H_ */
