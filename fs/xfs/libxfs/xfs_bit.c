<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_bit.h"

/*
 * XFS bit manipulation routines, used in non-realसमय code.
 */

/*
 * Return whether biपंचांगap is empty.
 * Size is number of words in the biपंचांगap, which is padded to word boundary
 * Returns 1 क्रम empty, 0 क्रम non-empty.
 */
पूर्णांक
xfs_biपंचांगap_empty(uपूर्णांक *map, uपूर्णांक size)
अणु
	uपूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (map[i] != 0)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Count the number of contiguous bits set in the biपंचांगap starting with bit
 * start_bit.  Size is the size of the biपंचांगap in words.
 */
पूर्णांक
xfs_contig_bits(uपूर्णांक *map, uपूर्णांक	size, uपूर्णांक start_bit)
अणु
	uपूर्णांक * p = ((अचिन्हित पूर्णांक *) map) + (start_bit >> BIT_TO_WORD_SHIFT);
	uपूर्णांक result = 0;
	uपूर्णांक पंचांगp;

	size <<= BIT_TO_WORD_SHIFT;

	ASSERT(start_bit < size);
	size -= start_bit & ~(NBWORD - 1);
	start_bit &= (NBWORD - 1);
	अगर (start_bit) अणु
		पंचांगp = *p++;
		/* set to one first offset bits prior to start */
		पंचांगp |= (~0U >> (NBWORD-start_bit));
		अगर (पंचांगp != ~0U)
			जाओ found;
		result += NBWORD;
		size -= NBWORD;
	पूर्ण
	जबतक (size) अणु
		अगर ((पंचांगp = *p++) != ~0U)
			जाओ found;
		result += NBWORD;
		size -= NBWORD;
	पूर्ण
	वापस result - start_bit;
found:
	वापस result + ffz(पंचांगp) - start_bit;
पूर्ण

/*
 * This takes the bit number to start looking from and
 * वापसs the next set bit from there.  It वापसs -1
 * अगर there are no more bits set or the start bit is
 * beyond the end of the biपंचांगap.
 *
 * Size is the number of words, not bytes, in the biपंचांगap.
 */
पूर्णांक xfs_next_bit(uपूर्णांक *map, uपूर्णांक size, uपूर्णांक start_bit)
अणु
	uपूर्णांक * p = ((अचिन्हित पूर्णांक *) map) + (start_bit >> BIT_TO_WORD_SHIFT);
	uपूर्णांक result = start_bit & ~(NBWORD - 1);
	uपूर्णांक पंचांगp;

	size <<= BIT_TO_WORD_SHIFT;

	अगर (start_bit >= size)
		वापस -1;
	size -= result;
	start_bit &= (NBWORD - 1);
	अगर (start_bit) अणु
		पंचांगp = *p++;
		/* set to zero first offset bits prior to start */
		पंचांगp &= (~0U << start_bit);
		अगर (पंचांगp != 0U)
			जाओ found;
		result += NBWORD;
		size -= NBWORD;
	पूर्ण
	जबतक (size) अणु
		अगर ((पंचांगp = *p++) != 0U)
			जाओ found;
		result += NBWORD;
		size -= NBWORD;
	पूर्ण
	वापस -1;
found:
	वापस result + ffs(पंचांगp) - 1;
पूर्ण
