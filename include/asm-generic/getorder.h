<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_GETORDER_H
#घोषणा __ASM_GENERIC_GETORDER_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/log2.h>

/**
 * get_order - Determine the allocation order of a memory size
 * @size: The size क्रम which to get the order
 *
 * Determine the allocation order of a particular sized block of memory.  This
 * is on a logarithmic scale, where:
 *
 *	0 -> 2^0 * PAGE_SIZE and below
 *	1 -> 2^1 * PAGE_SIZE to 2^0 * PAGE_SIZE + 1
 *	2 -> 2^2 * PAGE_SIZE to 2^1 * PAGE_SIZE + 1
 *	3 -> 2^3 * PAGE_SIZE to 2^2 * PAGE_SIZE + 1
 *	4 -> 2^4 * PAGE_SIZE to 2^3 * PAGE_SIZE + 1
 *	...
 *
 * The order वापसed is used to find the smallest allocation granule required
 * to hold an object of the specअगरied size.
 *
 * The result is undefined अगर the size is 0.
 */
अटल __always_अंतरभूत __attribute_स्थिर__ पूर्णांक get_order(अचिन्हित दीर्घ size)
अणु
	अगर (__builtin_स्थिरant_p(size)) अणु
		अगर (!size)
			वापस BITS_PER_LONG - PAGE_SHIFT;

		अगर (size < (1UL << PAGE_SHIFT))
			वापस 0;

		वापस ilog2((size) - 1) - PAGE_SHIFT + 1;
	पूर्ण

	size--;
	size >>= PAGE_SHIFT;
#अगर BITS_PER_LONG == 32
	वापस fls(size);
#अन्यथा
	वापस fls64(size);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* __ASM_GENERIC_GETORDER_H */
