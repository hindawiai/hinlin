<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* bit search implementation
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * Copyright (C) 2008 IBM Corporation
 * 'find_last_bit' is written by Rusty Russell <rusty@rustcorp.com.au>
 * (Inspired by David Howell's find_next_bit implementation)
 *
 * Rewritten by Yury Norov <yury.norov@gmail.com> to decrease
 * size and improve perक्रमmance, 2015.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/export.h>
#समावेश <linux/गणित.स>
#समावेश <linux/minmax.h>
#समावेश <linux/swab.h>

#अगर !defined(find_next_bit) || !defined(find_next_zero_bit) ||			\
	!defined(find_next_bit_le) || !defined(find_next_zero_bit_le) ||	\
	!defined(find_next_and_bit)
/*
 * This is a common helper function क्रम find_next_bit, find_next_zero_bit, and
 * find_next_and_bit. The dअगरferences are:
 *  - The "invert" argument, which is XORed with each fetched word beक्रमe
 *    searching it क्रम one bits.
 *  - The optional "addr2", which is anded with "addr1" अगर present.
 */
अचिन्हित दीर्घ _find_next_bit(स्थिर अचिन्हित दीर्घ *addr1,
		स्थिर अचिन्हित दीर्घ *addr2, अचिन्हित दीर्घ nbits,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ invert, अचिन्हित दीर्घ le)
अणु
	अचिन्हित दीर्घ पंचांगp, mask;

	अगर (unlikely(start >= nbits))
		वापस nbits;

	पंचांगp = addr1[start / BITS_PER_LONG];
	अगर (addr2)
		पंचांगp &= addr2[start / BITS_PER_LONG];
	पंचांगp ^= invert;

	/* Handle 1st word. */
	mask = BITMAP_FIRST_WORD_MASK(start);
	अगर (le)
		mask = swab(mask);

	पंचांगp &= mask;

	start = round_करोwn(start, BITS_PER_LONG);

	जबतक (!पंचांगp) अणु
		start += BITS_PER_LONG;
		अगर (start >= nbits)
			वापस nbits;

		पंचांगp = addr1[start / BITS_PER_LONG];
		अगर (addr2)
			पंचांगp &= addr2[start / BITS_PER_LONG];
		पंचांगp ^= invert;
	पूर्ण

	अगर (le)
		पंचांगp = swab(पंचांगp);

	वापस min(start + __ffs(पंचांगp), nbits);
पूर्ण
EXPORT_SYMBOL(_find_next_bit);
#पूर्ण_अगर

#अगर_अघोषित find_first_bit
/*
 * Find the first set bit in a memory region.
 */
अचिन्हित दीर्घ _find_first_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ idx;

	क्रम (idx = 0; idx * BITS_PER_LONG < size; idx++) अणु
		अगर (addr[idx])
			वापस min(idx * BITS_PER_LONG + __ffs(addr[idx]), size);
	पूर्ण

	वापस size;
पूर्ण
EXPORT_SYMBOL(_find_first_bit);
#पूर्ण_अगर

#अगर_अघोषित find_first_zero_bit
/*
 * Find the first cleared bit in a memory region.
 */
अचिन्हित दीर्घ _find_first_zero_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ idx;

	क्रम (idx = 0; idx * BITS_PER_LONG < size; idx++) अणु
		अगर (addr[idx] != ~0UL)
			वापस min(idx * BITS_PER_LONG + ffz(addr[idx]), size);
	पूर्ण

	वापस size;
पूर्ण
EXPORT_SYMBOL(_find_first_zero_bit);
#पूर्ण_अगर

#अगर_अघोषित find_last_bit
अचिन्हित दीर्घ _find_last_bit(स्थिर अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ size)
अणु
	अगर (size) अणु
		अचिन्हित दीर्घ val = BITMAP_LAST_WORD_MASK(size);
		अचिन्हित दीर्घ idx = (size-1) / BITS_PER_LONG;

		करो अणु
			val &= addr[idx];
			अगर (val)
				वापस idx * BITS_PER_LONG + __fls(val);

			val = ~0ul;
		पूर्ण जबतक (idx--);
	पूर्ण
	वापस size;
पूर्ण
EXPORT_SYMBOL(_find_last_bit);
#पूर्ण_अगर

अचिन्हित दीर्घ find_next_clump8(अचिन्हित दीर्घ *clump, स्थिर अचिन्हित दीर्घ *addr,
			       अचिन्हित दीर्घ size, अचिन्हित दीर्घ offset)
अणु
	offset = find_next_bit(addr, size, offset);
	अगर (offset == size)
		वापस size;

	offset = round_करोwn(offset, 8);
	*clump = biपंचांगap_get_value8(addr, offset);

	वापस offset;
पूर्ण
EXPORT_SYMBOL(find_next_clump8);
