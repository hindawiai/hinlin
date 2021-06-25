<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BITOPS_OP32_H
#घोषणा __ASM_SH_BITOPS_OP32_H

/*
 * The bit modअगरying inकाष्ठाions on SH-2A are only capable of working
 * with a 3-bit immediate, which signअगरies the shअगरt position क्रम the bit
 * being worked on.
 */
#अगर defined(__BIG_ENDIAN)
#घोषणा BITOP_LE_SWIZZLE	((BITS_PER_LONG-1) & ~0x7)
#घोषणा BYTE_NUMBER(nr)		((nr ^ BITOP_LE_SWIZZLE) / BITS_PER_BYTE)
#घोषणा BYTE_OFFSET(nr)		((nr ^ BITOP_LE_SWIZZLE) % BITS_PER_BYTE)
#अन्यथा
#घोषणा BYTE_NUMBER(nr)		((nr) / BITS_PER_BYTE)
#घोषणा BYTE_OFFSET(nr)		((nr) % BITS_PER_BYTE)
#पूर्ण_अगर

अटल अंतरभूत व्योम __set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अगर (__builtin_स्थिरant_p(nr)) अणु
		__यंत्र__ __अस्थिर__ (
			"bset.b %1, @(%O2,%0)		! __set_bit\n\t"
			: "+r" (addr)
			: "i" (BYTE_OFFSET(nr)), "i" (BYTE_NUMBER(nr))
			: "t", "memory"
		);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ mask = BIT_MASK(nr);
		अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);

		*p |= mask;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अगर (__builtin_स्थिरant_p(nr)) अणु
		__यंत्र__ __अस्थिर__ (
			"bclr.b %1, @(%O2,%0)		! __clear_bit\n\t"
			: "+r" (addr)
			: "i" (BYTE_OFFSET(nr)),
			  "i" (BYTE_NUMBER(nr))
			: "t", "memory"
		);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ mask = BIT_MASK(nr);
		अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);

		*p &= ~mask;
	पूर्ण
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
	अगर (__builtin_स्थिरant_p(nr)) अणु
		__यंत्र__ __अस्थिर__ (
			"bxor.b %1, @(%O2,%0)		! __change_bit\n\t"
			: "+r" (addr)
			: "i" (BYTE_OFFSET(nr)),
			  "i" (BYTE_NUMBER(nr))
			: "t", "memory"
		);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ mask = BIT_MASK(nr);
		अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);

		*p ^= mask;
	पूर्ण
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

#पूर्ण_अगर /* __ASM_SH_BITOPS_OP32_H */
