<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_FIND_H_
#घोषणा _ASM_GENERIC_BITOPS_FIND_H_

बाह्य अचिन्हित दीर्घ _find_next_bit(स्थिर अचिन्हित दीर्घ *addr1,
		स्थिर अचिन्हित दीर्घ *addr2, अचिन्हित दीर्घ nbits,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ invert, अचिन्हित दीर्घ le);
बाह्य अचिन्हित दीर्घ _find_first_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size);
बाह्य अचिन्हित दीर्घ _find_first_zero_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size);
बाह्य अचिन्हित दीर्घ _find_last_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size);

#अगर_अघोषित find_next_bit
/**
 * find_next_bit - find the next set bit in a memory region
 * @addr: The address to base the search on
 * @offset: The bitnumber to start searching at
 * @size: The biपंचांगap size in bits
 *
 * Returns the bit number क्रम the next set bit
 * If no bits are set, वापसs @size.
 */
अटल अंतरभूत
अचिन्हित दीर्घ find_next_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size,
			    अचिन्हित दीर्घ offset)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val;

		अगर (unlikely(offset >= size))
			वापस size;

		val = *addr & GENMASK(size - 1, offset);
		वापस val ? __ffs(val) : size;
	पूर्ण

	वापस _find_next_bit(addr, शून्य, size, offset, 0UL, 0);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित find_next_and_bit
/**
 * find_next_and_bit - find the next set bit in both memory regions
 * @addr1: The first address to base the search on
 * @addr2: The second address to base the search on
 * @offset: The bitnumber to start searching at
 * @size: The biपंचांगap size in bits
 *
 * Returns the bit number क्रम the next set bit
 * If no bits are set, वापसs @size.
 */
अटल अंतरभूत
अचिन्हित दीर्घ find_next_and_bit(स्थिर अचिन्हित दीर्घ *addr1,
		स्थिर अचिन्हित दीर्घ *addr2, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ offset)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val;

		अगर (unlikely(offset >= size))
			वापस size;

		val = *addr1 & *addr2 & GENMASK(size - 1, offset);
		वापस val ? __ffs(val) : size;
	पूर्ण

	वापस _find_next_bit(addr1, addr2, size, offset, 0UL, 0);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित find_next_zero_bit
/**
 * find_next_zero_bit - find the next cleared bit in a memory region
 * @addr: The address to base the search on
 * @offset: The bitnumber to start searching at
 * @size: The biपंचांगap size in bits
 *
 * Returns the bit number of the next zero bit
 * If no bits are zero, वापसs @size.
 */
अटल अंतरभूत
अचिन्हित दीर्घ find_next_zero_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size,
				 अचिन्हित दीर्घ offset)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val;

		अगर (unlikely(offset >= size))
			वापस size;

		val = *addr | ~GENMASK(size - 1, offset);
		वापस val == ~0UL ? size : ffz(val);
	पूर्ण

	वापस _find_next_bit(addr, शून्य, size, offset, ~0UL, 0);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_FIND_FIRST_BIT

/**
 * find_first_bit - find the first set bit in a memory region
 * @addr: The address to start the search at
 * @size: The maximum number of bits to search
 *
 * Returns the bit number of the first set bit.
 * If no bits are set, वापसs @size.
 */
अटल अंतरभूत
अचिन्हित दीर्घ find_first_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val = *addr & GENMASK(size - 1, 0);

		वापस val ? __ffs(val) : size;
	पूर्ण

	वापस _find_first_bit(addr, size);
पूर्ण

/**
 * find_first_zero_bit - find the first cleared bit in a memory region
 * @addr: The address to start the search at
 * @size: The maximum number of bits to search
 *
 * Returns the bit number of the first cleared bit.
 * If no bits are zero, वापसs @size.
 */
अटल अंतरभूत
अचिन्हित दीर्घ find_first_zero_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val = *addr | ~GENMASK(size - 1, 0);

		वापस val == ~0UL ? size : ffz(val);
	पूर्ण

	वापस _find_first_zero_bit(addr, size);
पूर्ण
#अन्यथा /* CONFIG_GENERIC_FIND_FIRST_BIT */

#अगर_अघोषित find_first_bit
#घोषणा find_first_bit(addr, size) find_next_bit((addr), (size), 0)
#पूर्ण_अगर
#अगर_अघोषित find_first_zero_bit
#घोषणा find_first_zero_bit(addr, size) find_next_zero_bit((addr), (size), 0)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_GENERIC_FIND_FIRST_BIT */

#अगर_अघोषित find_last_bit
/**
 * find_last_bit - find the last set bit in a memory region
 * @addr: The address to start the search at
 * @size: The number of bits to search
 *
 * Returns the bit number of the last set bit, or size.
 */
अटल अंतरभूत
अचिन्हित दीर्घ find_last_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val = *addr & GENMASK(size - 1, 0);

		वापस val ? __fls(val) : size;
	पूर्ण

	वापस _find_last_bit(addr, size);
पूर्ण
#पूर्ण_अगर

/**
 * find_next_clump8 - find next 8-bit clump with set bits in a memory region
 * @clump: location to store copy of found clump
 * @addr: address to base the search on
 * @size: biपंचांगap size in number of bits
 * @offset: bit offset at which to start searching
 *
 * Returns the bit offset क्रम the next set clump; the found clump value is
 * copied to the location poपूर्णांकed by @clump. If no bits are set, वापसs @size.
 */
बाह्य अचिन्हित दीर्घ find_next_clump8(अचिन्हित दीर्घ *clump,
				      स्थिर अचिन्हित दीर्घ *addr,
				      अचिन्हित दीर्घ size, अचिन्हित दीर्घ offset);

#घोषणा find_first_clump8(clump, bits, size) \
	find_next_clump8((clump), (bits), (size), 0)

#पूर्ण_अगर /*_ASM_GENERIC_BITOPS_FIND_H_ */
