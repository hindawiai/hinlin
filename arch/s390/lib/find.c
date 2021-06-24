<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MSB0 numbered special bitops handling.
 *
 * The bits are numbered:
 *   |0..............63|64............127|128...........191|192...........255|
 *
 * The reason क्रम this bit numbering is the fact that the hardware sets bits
 * in a biपंचांगap starting at bit 0 (MSB) and we करोn't want to scan the biपंचांगap
 * from the 'wrong end'.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/bitops.h>
#समावेश <linux/export.h>

अचिन्हित दीर्घ find_first_bit_inv(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size)
अणु
	स्थिर अचिन्हित दीर्घ *p = addr;
	अचिन्हित दीर्घ result = 0;
	अचिन्हित दीर्घ पंचांगp;

	जबतक (size & ~(BITS_PER_LONG - 1)) अणु
		अगर ((पंचांगp = *(p++)))
			जाओ found;
		result += BITS_PER_LONG;
		size -= BITS_PER_LONG;
	पूर्ण
	अगर (!size)
		वापस result;
	पंचांगp = (*p) & (~0UL << (BITS_PER_LONG - size));
	अगर (!पंचांगp)		/* Are any bits set? */
		वापस result + size;	/* Nope. */
found:
	वापस result + (__fls(पंचांगp) ^ (BITS_PER_LONG - 1));
पूर्ण
EXPORT_SYMBOL(find_first_bit_inv);

अचिन्हित दीर्घ find_next_bit_inv(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ offset)
अणु
	स्थिर अचिन्हित दीर्घ *p = addr + (offset / BITS_PER_LONG);
	अचिन्हित दीर्घ result = offset & ~(BITS_PER_LONG - 1);
	अचिन्हित दीर्घ पंचांगp;

	अगर (offset >= size)
		वापस size;
	size -= result;
	offset %= BITS_PER_LONG;
	अगर (offset) अणु
		पंचांगp = *(p++);
		पंचांगp &= (~0UL >> offset);
		अगर (size < BITS_PER_LONG)
			जाओ found_first;
		अगर (पंचांगp)
			जाओ found_middle;
		size -= BITS_PER_LONG;
		result += BITS_PER_LONG;
	पूर्ण
	जबतक (size & ~(BITS_PER_LONG-1)) अणु
		अगर ((पंचांगp = *(p++)))
			जाओ found_middle;
		result += BITS_PER_LONG;
		size -= BITS_PER_LONG;
	पूर्ण
	अगर (!size)
		वापस result;
	पंचांगp = *p;
found_first:
	पंचांगp &= (~0UL << (BITS_PER_LONG - size));
	अगर (!पंचांगp)		/* Are any bits set? */
		वापस result + size;	/* Nope. */
found_middle:
	वापस result + (__fls(पंचांगp) ^ (BITS_PER_LONG - 1));
पूर्ण
EXPORT_SYMBOL(find_next_bit_inv);
