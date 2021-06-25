<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_ASM_GENERIC_BITOPS_FIND_H_
#घोषणा _TOOLS_LINUX_ASM_GENERIC_BITOPS_FIND_H_

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

#अगर_अघोषित find_first_bit

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

#पूर्ण_अगर /* find_first_bit */

#अगर_अघोषित find_first_zero_bit

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
#पूर्ण_अगर

#पूर्ण_अगर /*_TOOLS_LINUX_ASM_GENERIC_BITOPS_FIND_H_ */
