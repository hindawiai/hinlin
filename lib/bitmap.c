<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib/biपंचांगap.c
 * Helper functions क्रम biपंचांगap.h.
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/page.h>

#समावेश "kstrtox.h"

/**
 * DOC: biपंचांगap पूर्णांकroduction
 *
 * biपंचांगaps provide an array of bits, implemented using an
 * array of अचिन्हित दीर्घs.  The number of valid bits in a
 * given biपंचांगap करोes _not_ need to be an exact multiple of
 * BITS_PER_LONG.
 *
 * The possible unused bits in the last, partially used word
 * of a biपंचांगap are 'don't care'.  The implementation makes
 * no particular efक्रमt to keep them zero.  It ensures that
 * their value will not affect the results of any operation.
 * The biपंचांगap operations that वापस Boolean (biपंचांगap_empty,
 * क्रम example) or scalar (biपंचांगap_weight, क्रम example) results
 * carefully filter out these unused bits from impacting their
 * results.
 *
 * The byte ordering of biपंचांगaps is more natural on little
 * endian architectures.  See the big-endian headers
 * include/यंत्र-ppc64/bitops.h and include/यंत्र-s390/bitops.h
 * क्रम the best explanations of this ordering.
 */

पूर्णांक __biपंचांगap_equal(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k, lim = bits/BITS_PER_LONG;
	क्रम (k = 0; k < lim; ++k)
		अगर (biपंचांगap1[k] != biपंचांगap2[k])
			वापस 0;

	अगर (bits % BITS_PER_LONG)
		अगर ((biपंचांगap1[k] ^ biपंचांगap2[k]) & BITMAP_LAST_WORD_MASK(bits))
			वापस 0;

	वापस 1;
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_equal);

bool __biपंचांगap_or_equal(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		       स्थिर अचिन्हित दीर्घ *biपंचांगap2,
		       स्थिर अचिन्हित दीर्घ *biपंचांगap3,
		       अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k, lim = bits / BITS_PER_LONG;
	अचिन्हित दीर्घ पंचांगp;

	क्रम (k = 0; k < lim; ++k) अणु
		अगर ((biपंचांगap1[k] | biपंचांगap2[k]) != biपंचांगap3[k])
			वापस false;
	पूर्ण

	अगर (!(bits % BITS_PER_LONG))
		वापस true;

	पंचांगp = (biपंचांगap1[k] | biपंचांगap2[k]) ^ biपंचांगap3[k];
	वापस (पंचांगp & BITMAP_LAST_WORD_MASK(bits)) == 0;
पूर्ण

व्योम __biपंचांगap_complement(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k, lim = BITS_TO_LONGS(bits);
	क्रम (k = 0; k < lim; ++k)
		dst[k] = ~src[k];
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_complement);

/**
 * __biपंचांगap_shअगरt_right - logical right shअगरt of the bits in a biपंचांगap
 *   @dst : destination biपंचांगap
 *   @src : source biपंचांगap
 *   @shअगरt : shअगरt by this many bits
 *   @nbits : biपंचांगap size, in bits
 *
 * Shअगरting right (भागiding) means moving bits in the MS -> LS bit
 * direction.  Zeros are fed पूर्णांकo the vacated MS positions and the
 * LS bits shअगरted off the bottom are lost.
 */
व्योम __biपंचांगap_shअगरt_right(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
			अचिन्हित shअगरt, अचिन्हित nbits)
अणु
	अचिन्हित k, lim = BITS_TO_LONGS(nbits);
	अचिन्हित off = shअगरt/BITS_PER_LONG, rem = shअगरt % BITS_PER_LONG;
	अचिन्हित दीर्घ mask = BITMAP_LAST_WORD_MASK(nbits);
	क्रम (k = 0; off + k < lim; ++k) अणु
		अचिन्हित दीर्घ upper, lower;

		/*
		 * If shअगरt is not word aligned, take lower rem bits of
		 * word above and make them the top rem bits of result.
		 */
		अगर (!rem || off + k + 1 >= lim)
			upper = 0;
		अन्यथा अणु
			upper = src[off + k + 1];
			अगर (off + k + 1 == lim - 1)
				upper &= mask;
			upper <<= (BITS_PER_LONG - rem);
		पूर्ण
		lower = src[off + k];
		अगर (off + k == lim - 1)
			lower &= mask;
		lower >>= rem;
		dst[k] = lower | upper;
	पूर्ण
	अगर (off)
		स_रखो(&dst[lim - off], 0, off*माप(अचिन्हित दीर्घ));
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_shअगरt_right);


/**
 * __biपंचांगap_shअगरt_left - logical left shअगरt of the bits in a biपंचांगap
 *   @dst : destination biपंचांगap
 *   @src : source biपंचांगap
 *   @shअगरt : shअगरt by this many bits
 *   @nbits : biपंचांगap size, in bits
 *
 * Shअगरting left (multiplying) means moving bits in the LS -> MS
 * direction.  Zeros are fed पूर्णांकo the vacated LS bit positions
 * and those MS bits shअगरted off the top are lost.
 */

व्योम __biपंचांगap_shअगरt_left(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
			अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक nbits)
अणु
	पूर्णांक k;
	अचिन्हित पूर्णांक lim = BITS_TO_LONGS(nbits);
	अचिन्हित पूर्णांक off = shअगरt/BITS_PER_LONG, rem = shअगरt % BITS_PER_LONG;
	क्रम (k = lim - off - 1; k >= 0; --k) अणु
		अचिन्हित दीर्घ upper, lower;

		/*
		 * If shअगरt is not word aligned, take upper rem bits of
		 * word below and make them the bottom rem bits of result.
		 */
		अगर (rem && k > 0)
			lower = src[k - 1] >> (BITS_PER_LONG - rem);
		अन्यथा
			lower = 0;
		upper = src[k] << rem;
		dst[k + off] = lower | upper;
	पूर्ण
	अगर (off)
		स_रखो(dst, 0, off*माप(अचिन्हित दीर्घ));
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_shअगरt_left);

/**
 * biपंचांगap_cut() - हटाओ bit region from biपंचांगap and right shअगरt reमुख्यing bits
 * @dst: destination biपंचांगap, might overlap with src
 * @src: source biपंचांगap
 * @first: start bit of region to be हटाओd
 * @cut: number of bits to हटाओ
 * @nbits: biपंचांगap size, in bits
 *
 * Set the n-th bit of @dst अगरf the n-th bit of @src is set and
 * n is less than @first, or the m-th bit of @src is set क्रम any
 * m such that @first <= n < nbits, and m = n + @cut.
 *
 * In pictures, example क्रम a big-endian 32-bit architecture:
 *
 * The @src biपंचांगap is::
 *
 *   31                                   63
 *   |                                    |
 *   10000000 11000001 11110010 00010101  10000000 11000001 01110010 00010101
 *                   |  |              |                                    |
 *                  16  14             0                                   32
 *
 * अगर @cut is 3, and @first is 14, bits 14-16 in @src are cut and @dst is::
 *
 *   31                                   63
 *   |                                    |
 *   10110000 00011000 00110010 00010101  00010000 00011000 00101110 01000010
 *                      |              |                                    |
 *                      14 (bit 17     0                                   32
 *                          from @src)
 *
 * Note that @dst and @src might overlap partially or entirely.
 *
 * This is implemented in the obvious way, with a shअगरt and carry
 * step क्रम each moved bit. Optimisation is left as an exercise
 * क्रम the compiler.
 */
व्योम biपंचांगap_cut(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
		अचिन्हित पूर्णांक first, अचिन्हित पूर्णांक cut, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक len = BITS_TO_LONGS(nbits);
	अचिन्हित दीर्घ keep = 0, carry;
	पूर्णांक i;

	अगर (first % BITS_PER_LONG) अणु
		keep = src[first / BITS_PER_LONG] &
		       (~0UL >> (BITS_PER_LONG - first % BITS_PER_LONG));
	पूर्ण

	स_हटाओ(dst, src, len * माप(*dst));

	जबतक (cut--) अणु
		क्रम (i = first / BITS_PER_LONG; i < len; i++) अणु
			अगर (i < len - 1)
				carry = dst[i + 1] & 1UL;
			अन्यथा
				carry = 0;

			dst[i] = (dst[i] >> 1) | (carry << (BITS_PER_LONG - 1));
		पूर्ण
	पूर्ण

	dst[first / BITS_PER_LONG] &= ~0UL << (first % BITS_PER_LONG);
	dst[first / BITS_PER_LONG] |= keep;
पूर्ण
EXPORT_SYMBOL(biपंचांगap_cut);

पूर्णांक __biपंचांगap_and(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
				स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक lim = bits/BITS_PER_LONG;
	अचिन्हित दीर्घ result = 0;

	क्रम (k = 0; k < lim; k++)
		result |= (dst[k] = biपंचांगap1[k] & biपंचांगap2[k]);
	अगर (bits % BITS_PER_LONG)
		result |= (dst[k] = biपंचांगap1[k] & biपंचांगap2[k] &
			   BITMAP_LAST_WORD_MASK(bits));
	वापस result != 0;
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_and);

व्योम __biपंचांगap_or(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
				स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक nr = BITS_TO_LONGS(bits);

	क्रम (k = 0; k < nr; k++)
		dst[k] = biपंचांगap1[k] | biपंचांगap2[k];
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_or);

व्योम __biपंचांगap_xor(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
				स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक nr = BITS_TO_LONGS(bits);

	क्रम (k = 0; k < nr; k++)
		dst[k] = biपंचांगap1[k] ^ biपंचांगap2[k];
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_xor);

पूर्णांक __biपंचांगap_andnot(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
				स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक lim = bits/BITS_PER_LONG;
	अचिन्हित दीर्घ result = 0;

	क्रम (k = 0; k < lim; k++)
		result |= (dst[k] = biपंचांगap1[k] & ~biपंचांगap2[k]);
	अगर (bits % BITS_PER_LONG)
		result |= (dst[k] = biपंचांगap1[k] & ~biपंचांगap2[k] &
			   BITMAP_LAST_WORD_MASK(bits));
	वापस result != 0;
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_andnot);

व्योम __biपंचांगap_replace(अचिन्हित दीर्घ *dst,
		      स्थिर अचिन्हित दीर्घ *old, स्थिर अचिन्हित दीर्घ *new,
		      स्थिर अचिन्हित दीर्घ *mask, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक nr = BITS_TO_LONGS(nbits);

	क्रम (k = 0; k < nr; k++)
		dst[k] = (old[k] & ~mask[k]) | (new[k] & mask[k]);
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_replace);

पूर्णांक __biपंचांगap_पूर्णांकersects(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
			स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k, lim = bits/BITS_PER_LONG;
	क्रम (k = 0; k < lim; ++k)
		अगर (biपंचांगap1[k] & biपंचांगap2[k])
			वापस 1;

	अगर (bits % BITS_PER_LONG)
		अगर ((biपंचांगap1[k] & biपंचांगap2[k]) & BITMAP_LAST_WORD_MASK(bits))
			वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_पूर्णांकersects);

पूर्णांक __biपंचांगap_subset(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		    स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k, lim = bits/BITS_PER_LONG;
	क्रम (k = 0; k < lim; ++k)
		अगर (biपंचांगap1[k] & ~biपंचांगap2[k])
			वापस 0;

	अगर (bits % BITS_PER_LONG)
		अगर ((biपंचांगap1[k] & ~biपंचांगap2[k]) & BITMAP_LAST_WORD_MASK(bits))
			वापस 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_subset);

पूर्णांक __biपंचांगap_weight(स्थिर अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक k, lim = bits/BITS_PER_LONG;
	पूर्णांक w = 0;

	क्रम (k = 0; k < lim; k++)
		w += hweight_दीर्घ(biपंचांगap[k]);

	अगर (bits % BITS_PER_LONG)
		w += hweight_दीर्घ(biपंचांगap[k] & BITMAP_LAST_WORD_MASK(bits));

	वापस w;
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_weight);

व्योम __biपंचांगap_set(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start, पूर्णांक len)
अणु
	अचिन्हित दीर्घ *p = map + BIT_WORD(start);
	स्थिर अचिन्हित पूर्णांक size = start + len;
	पूर्णांक bits_to_set = BITS_PER_LONG - (start % BITS_PER_LONG);
	अचिन्हित दीर्घ mask_to_set = BITMAP_FIRST_WORD_MASK(start);

	जबतक (len - bits_to_set >= 0) अणु
		*p |= mask_to_set;
		len -= bits_to_set;
		bits_to_set = BITS_PER_LONG;
		mask_to_set = ~0UL;
		p++;
	पूर्ण
	अगर (len) अणु
		mask_to_set &= BITMAP_LAST_WORD_MASK(size);
		*p |= mask_to_set;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_set);

व्योम __biपंचांगap_clear(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start, पूर्णांक len)
अणु
	अचिन्हित दीर्घ *p = map + BIT_WORD(start);
	स्थिर अचिन्हित पूर्णांक size = start + len;
	पूर्णांक bits_to_clear = BITS_PER_LONG - (start % BITS_PER_LONG);
	अचिन्हित दीर्घ mask_to_clear = BITMAP_FIRST_WORD_MASK(start);

	जबतक (len - bits_to_clear >= 0) अणु
		*p &= ~mask_to_clear;
		len -= bits_to_clear;
		bits_to_clear = BITS_PER_LONG;
		mask_to_clear = ~0UL;
		p++;
	पूर्ण
	अगर (len) अणु
		mask_to_clear &= BITMAP_LAST_WORD_MASK(size);
		*p &= ~mask_to_clear;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__biपंचांगap_clear);

/**
 * biपंचांगap_find_next_zero_area_off - find a contiguous aligned zero area
 * @map: The address to base the search on
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @align_mask: Alignment mask क्रम zero area
 * @align_offset: Alignment offset क्रम zero area.
 *
 * The @align_mask should be one less than a घातer of 2; the effect is that
 * the bit offset of all zero areas this function finds plus @align_offset
 * is multiple of that घातer of 2.
 */
अचिन्हित दीर्घ biपंचांगap_find_next_zero_area_off(अचिन्हित दीर्घ *map,
					     अचिन्हित दीर्घ size,
					     अचिन्हित दीर्घ start,
					     अचिन्हित पूर्णांक nr,
					     अचिन्हित दीर्घ align_mask,
					     अचिन्हित दीर्घ align_offset)
अणु
	अचिन्हित दीर्घ index, end, i;
again:
	index = find_next_zero_bit(map, size, start);

	/* Align allocation */
	index = __ALIGN_MASK(index + align_offset, align_mask) - align_offset;

	end = index + nr;
	अगर (end > size)
		वापस end;
	i = find_next_bit(map, end, index);
	अगर (i < end) अणु
		start = i + 1;
		जाओ again;
	पूर्ण
	वापस index;
पूर्ण
EXPORT_SYMBOL(biपंचांगap_find_next_zero_area_off);

/*
 * Biपंचांगap prपूर्णांकing & parsing functions: first version by Nadia Yvette Chambers,
 * second version by Paul Jackson, third by Joe Korty.
 */

/**
 * biपंचांगap_parse_user - convert an ASCII hex string in a user buffer पूर्णांकo a biपंचांगap
 *
 * @ubuf: poपूर्णांकer to user buffer containing string.
 * @ulen: buffer size in bytes.  If string is smaller than this
 *    then it must be terminated with a \0.
 * @maskp: poपूर्णांकer to biपंचांगap array that will contain result.
 * @nmaskbits: size of biपंचांगap, in bits.
 */
पूर्णांक biपंचांगap_parse_user(स्थिर अक्षर __user *ubuf,
			अचिन्हित पूर्णांक ulen, अचिन्हित दीर्घ *maskp,
			पूर्णांक nmaskbits)
अणु
	अक्षर *buf;
	पूर्णांक ret;

	buf = memdup_user_nul(ubuf, ulen);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ret = biपंचांगap_parse(buf, अच_पूर्णांक_उच्च, maskp, nmaskbits);

	kमुक्त(buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(biपंचांगap_parse_user);

/**
 * biपंचांगap_prपूर्णांक_to_pagebuf - convert biपंचांगap to list or hex क्रमmat ASCII string
 * @list: indicates whether the biपंचांगap must be list
 * @buf: page aligned buffer पूर्णांकo which string is placed
 * @maskp: poपूर्णांकer to biपंचांगap to convert
 * @nmaskbits: size of biपंचांगap, in bits
 *
 * Output क्रमmat is a comma-separated list of decimal numbers and
 * ranges अगर list is specअगरied or hex digits grouped पूर्णांकo comma-separated
 * sets of 8 digits/set. Returns the number of अक्षरacters written to buf.
 *
 * It is assumed that @buf is a poपूर्णांकer पूर्णांकo a PAGE_SIZE, page-aligned
 * area and that sufficient storage reमुख्यs at @buf to accommodate the
 * biपंचांगap_prपूर्णांक_to_pagebuf() output. Returns the number of अक्षरacters
 * actually prपूर्णांकed to @buf, excluding terminating '\0'.
 */
पूर्णांक biपंचांगap_prपूर्णांक_to_pagebuf(bool list, अक्षर *buf, स्थिर अचिन्हित दीर्घ *maskp,
			    पूर्णांक nmaskbits)
अणु
	सूचक_भेद_प्रकार len = PAGE_SIZE - offset_in_page(buf);

	वापस list ? scnम_लिखो(buf, len, "%*pbl\n", nmaskbits, maskp) :
		      scnम_लिखो(buf, len, "%*pb\n", nmaskbits, maskp);
पूर्ण
EXPORT_SYMBOL(biपंचांगap_prपूर्णांक_to_pagebuf);

/*
 * Region 9-38:4/10 describes the following biपंचांगap काष्ठाure:
 * 0	   9  12    18			38	     N
 * .........****......****......****..................
 *	    ^  ^     ^			 ^	     ^
 *      start  off   group_len	       end	 nbits
 */
काष्ठा region अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक off;
	अचिन्हित पूर्णांक group_len;
	अचिन्हित पूर्णांक end;
	अचिन्हित पूर्णांक nbits;
पूर्ण;

अटल व्योम biपंचांगap_set_region(स्थिर काष्ठा region *r, अचिन्हित दीर्घ *biपंचांगap)
अणु
	अचिन्हित पूर्णांक start;

	क्रम (start = r->start; start <= r->end; start += r->group_len)
		biपंचांगap_set(biपंचांगap, start, min(r->end - start + 1, r->off));
पूर्ण

अटल पूर्णांक biपंचांगap_check_region(स्थिर काष्ठा region *r)
अणु
	अगर (r->start > r->end || r->group_len == 0 || r->off > r->group_len)
		वापस -EINVAL;

	अगर (r->end >= r->nbits)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *biपंचांगap_getnum(स्थिर अक्षर *str, अचिन्हित पूर्णांक *num,
				 अचिन्हित पूर्णांक lastbit)
अणु
	अचिन्हित दीर्घ दीर्घ n;
	अचिन्हित पूर्णांक len;

	अगर (str[0] == 'N') अणु
		*num = lastbit;
		वापस str + 1;
	पूर्ण

	len = _parse_पूर्णांकeger(str, 10, &n);
	अगर (!len)
		वापस ERR_PTR(-EINVAL);
	अगर (len & KSTRTOX_OVERFLOW || n != (अचिन्हित पूर्णांक)n)
		वापस ERR_PTR(-EOVERFLOW);

	*num = n;
	वापस str + len;
पूर्ण

अटल अंतरभूत bool end_of_str(अक्षर c)
अणु
	वापस c == '\0' || c == '\n';
पूर्ण

अटल अंतरभूत bool __end_of_region(अक्षर c)
अणु
	वापस है_खाली(c) || c == ',';
पूर्ण

अटल अंतरभूत bool end_of_region(अक्षर c)
अणु
	वापस __end_of_region(c) || end_of_str(c);
पूर्ण

/*
 * The क्रमmat allows commas and whitespaces at the beginning
 * of the region.
 */
अटल स्थिर अक्षर *biपंचांगap_find_region(स्थिर अक्षर *str)
अणु
	जबतक (__end_of_region(*str))
		str++;

	वापस end_of_str(*str) ? शून्य : str;
पूर्ण

अटल स्थिर अक्षर *biपंचांगap_find_region_reverse(स्थिर अक्षर *start, स्थिर अक्षर *end)
अणु
	जबतक (start <= end && __end_of_region(*end))
		end--;

	वापस end;
पूर्ण

अटल स्थिर अक्षर *biपंचांगap_parse_region(स्थिर अक्षर *str, काष्ठा region *r)
अणु
	अचिन्हित पूर्णांक lastbit = r->nbits - 1;

	str = biपंचांगap_getnum(str, &r->start, lastbit);
	अगर (IS_ERR(str))
		वापस str;

	अगर (end_of_region(*str))
		जाओ no_end;

	अगर (*str != '-')
		वापस ERR_PTR(-EINVAL);

	str = biपंचांगap_getnum(str + 1, &r->end, lastbit);
	अगर (IS_ERR(str))
		वापस str;

	अगर (end_of_region(*str))
		जाओ no_pattern;

	अगर (*str != ':')
		वापस ERR_PTR(-EINVAL);

	str = biपंचांगap_getnum(str + 1, &r->off, lastbit);
	अगर (IS_ERR(str))
		वापस str;

	अगर (*str != '/')
		वापस ERR_PTR(-EINVAL);

	वापस biपंचांगap_getnum(str + 1, &r->group_len, lastbit);

no_end:
	r->end = r->start;
no_pattern:
	r->off = r->end + 1;
	r->group_len = r->end + 1;

	वापस end_of_str(*str) ? शून्य : str;
पूर्ण

/**
 * biपंचांगap_parselist - convert list क्रमmat ASCII string to biपंचांगap
 * @buf: पढ़ो user string from this buffer; must be terminated
 *    with a \0 or \न.
 * @maskp: ग_लिखो resulting mask here
 * @nmaskbits: number of bits in mask to be written
 *
 * Input क्रमmat is a comma-separated list of decimal numbers and
 * ranges.  Consecutively set bits are shown as two hyphen-separated
 * decimal numbers, the smallest and largest bit numbers set in
 * the range.
 * Optionally each range can be postfixed to denote that only parts of it
 * should be set. The range will भागided to groups of specअगरic size.
 * From each group will be used only defined amount of bits.
 * Syntax: range:used_size/group_size
 * Example: 0-1023:2/256 ==> 0,1,256,257,512,513,768,769
 * The value 'N' can be used as a dynamically substituted token क्रम the
 * maximum allowed value; i.e (nmaskbits - 1).  Keep in mind that it is
 * dynamic, so अगर प्रणाली changes cause the biपंचांगap width to change, such
 * as more cores in a CPU list, then any ranges using N will also change.
 *
 * Returns: 0 on success, -त्रुटि_सं on invalid input strings. Error values:
 *
 *   - ``-EINVAL``: wrong region क्रमmat
 *   - ``-EINVAL``: invalid अक्षरacter in string
 *   - ``-दुस्फल``: bit number specअगरied too large क्रम mask
 *   - ``-EOVERFLOW``: पूर्णांकeger overflow in the input parameters
 */
पूर्णांक biपंचांगap_parselist(स्थिर अक्षर *buf, अचिन्हित दीर्घ *maskp, पूर्णांक nmaskbits)
अणु
	काष्ठा region r;
	दीर्घ ret;

	r.nbits = nmaskbits;
	biपंचांगap_zero(maskp, r.nbits);

	जबतक (buf) अणु
		buf = biपंचांगap_find_region(buf);
		अगर (buf == शून्य)
			वापस 0;

		buf = biपंचांगap_parse_region(buf, &r);
		अगर (IS_ERR(buf))
			वापस PTR_ERR(buf);

		ret = biपंचांगap_check_region(&r);
		अगर (ret)
			वापस ret;

		biपंचांगap_set_region(&r, maskp);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(biपंचांगap_parselist);


/**
 * biपंचांगap_parselist_user()
 *
 * @ubuf: poपूर्णांकer to user buffer containing string.
 * @ulen: buffer size in bytes.  If string is smaller than this
 *    then it must be terminated with a \0.
 * @maskp: poपूर्णांकer to biपंचांगap array that will contain result.
 * @nmaskbits: size of biपंचांगap, in bits.
 *
 * Wrapper क्रम biपंचांगap_parselist(), providing it with user buffer.
 */
पूर्णांक biपंचांगap_parselist_user(स्थिर अक्षर __user *ubuf,
			अचिन्हित पूर्णांक ulen, अचिन्हित दीर्घ *maskp,
			पूर्णांक nmaskbits)
अणु
	अक्षर *buf;
	पूर्णांक ret;

	buf = memdup_user_nul(ubuf, ulen);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ret = biपंचांगap_parselist(buf, maskp, nmaskbits);

	kमुक्त(buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(biपंचांगap_parselist_user);

अटल स्थिर अक्षर *biपंचांगap_get_x32_reverse(स्थिर अक्षर *start,
					स्थिर अक्षर *end, u32 *num)
अणु
	u32 ret = 0;
	पूर्णांक c, i;

	क्रम (i = 0; i < 32; i += 4) अणु
		c = hex_to_bin(*end--);
		अगर (c < 0)
			वापस ERR_PTR(-EINVAL);

		ret |= c << i;

		अगर (start > end || __end_of_region(*end))
			जाओ out;
	पूर्ण

	अगर (hex_to_bin(*end--) >= 0)
		वापस ERR_PTR(-EOVERFLOW);
out:
	*num = ret;
	वापस end;
पूर्ण

/**
 * biपंचांगap_parse - convert an ASCII hex string पूर्णांकo a biपंचांगap.
 * @start: poपूर्णांकer to buffer containing string.
 * @buflen: buffer size in bytes.  If string is smaller than this
 *    then it must be terminated with a \0 or \न. In that हाल,
 *    अच_पूर्णांक_उच्च may be provided instead of string length.
 * @maskp: poपूर्णांकer to biपंचांगap array that will contain result.
 * @nmaskbits: size of biपंचांगap, in bits.
 *
 * Commas group hex digits पूर्णांकo chunks.  Each chunk defines exactly 32
 * bits of the resultant biपंचांगask.  No chunk may specअगरy a value larger
 * than 32 bits (%-EOVERFLOW), and अगर a chunk specअगरies a smaller value
 * then leading 0-bits are prepended.  %-EINVAL is वापसed क्रम illegal
 * अक्षरacters. Grouping such as "1,,5", ",44", "," or "" is allowed.
 * Leading, embedded and trailing whitespace accepted.
 */
पूर्णांक biपंचांगap_parse(स्थिर अक्षर *start, अचिन्हित पूर्णांक buflen,
		अचिन्हित दीर्घ *maskp, पूर्णांक nmaskbits)
अणु
	स्थिर अक्षर *end = strnchrnul(start, buflen, '\n') - 1;
	पूर्णांक chunks = BITS_TO_U32(nmaskbits);
	u32 *biपंचांगap = (u32 *)maskp;
	पूर्णांक unset_bit;
	पूर्णांक chunk;

	क्रम (chunk = 0; ; chunk++) अणु
		end = biपंचांगap_find_region_reverse(start, end);
		अगर (start > end)
			अवरोध;

		अगर (!chunks--)
			वापस -EOVERFLOW;

#अगर defined(CONFIG_64BIT) && defined(__BIG_ENDIAN)
		end = biपंचांगap_get_x32_reverse(start, end, &biपंचांगap[chunk ^ 1]);
#अन्यथा
		end = biपंचांगap_get_x32_reverse(start, end, &biपंचांगap[chunk]);
#पूर्ण_अगर
		अगर (IS_ERR(end))
			वापस PTR_ERR(end);
	पूर्ण

	unset_bit = (BITS_TO_U32(nmaskbits) - chunks) * 32;
	अगर (unset_bit < nmaskbits) अणु
		biपंचांगap_clear(maskp, unset_bit, nmaskbits - unset_bit);
		वापस 0;
	पूर्ण

	अगर (find_next_bit(maskp, unset_bit, nmaskbits) != unset_bit)
		वापस -EOVERFLOW;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(biपंचांगap_parse);


#अगर_घोषित CONFIG_NUMA
/**
 * biपंचांगap_pos_to_ord - find ordinal of set bit at given position in biपंचांगap
 *	@buf: poपूर्णांकer to a biपंचांगap
 *	@pos: a bit position in @buf (0 <= @pos < @nbits)
 *	@nbits: number of valid bit positions in @buf
 *
 * Map the bit at position @pos in @buf (of length @nbits) to the
 * ordinal of which set bit it is.  If it is not set or अगर @pos
 * is not a valid bit position, map to -1.
 *
 * If क्रम example, just bits 4 through 7 are set in @buf, then @pos
 * values 4 through 7 will get mapped to 0 through 3, respectively,
 * and other @pos values will get mapped to -1.  When @pos value 7
 * माला_लो mapped to (वापसs) @ord value 3 in this example, that means
 * that bit 7 is the 3rd (starting with 0th) set bit in @buf.
 *
 * The bit positions 0 through @bits are valid positions in @buf.
 */
अटल पूर्णांक biपंचांगap_pos_to_ord(स्थिर अचिन्हित दीर्घ *buf, अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक nbits)
अणु
	अगर (pos >= nbits || !test_bit(pos, buf))
		वापस -1;

	वापस __biपंचांगap_weight(buf, pos);
पूर्ण

/**
 * biपंचांगap_ord_to_pos - find position of n-th set bit in biपंचांगap
 *	@buf: poपूर्णांकer to biपंचांगap
 *	@ord: ordinal bit position (n-th set bit, n >= 0)
 *	@nbits: number of valid bit positions in @buf
 *
 * Map the ordinal offset of bit @ord in @buf to its position in @buf.
 * Value of @ord should be in range 0 <= @ord < weight(buf). If @ord
 * >= weight(buf), वापसs @nbits.
 *
 * If क्रम example, just bits 4 through 7 are set in @buf, then @ord
 * values 0 through 3 will get mapped to 4 through 7, respectively,
 * and all other @ord values वापसs @nbits.  When @ord value 3
 * माला_लो mapped to (वापसs) @pos value 7 in this example, that means
 * that the 3rd set bit (starting with 0th) is at position 7 in @buf.
 *
 * The bit positions 0 through @nbits-1 are valid positions in @buf.
 */
अचिन्हित पूर्णांक biपंचांगap_ord_to_pos(स्थिर अचिन्हित दीर्घ *buf, अचिन्हित पूर्णांक ord, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक pos;

	क्रम (pos = find_first_bit(buf, nbits);
	     pos < nbits && ord;
	     pos = find_next_bit(buf, nbits, pos + 1))
		ord--;

	वापस pos;
पूर्ण

/**
 * biपंचांगap_remap - Apply map defined by a pair of biपंचांगaps to another biपंचांगap
 *	@dst: remapped result
 *	@src: subset to be remapped
 *	@old: defines करोमुख्य of map
 *	@new: defines range of map
 *	@nbits: number of bits in each of these biपंचांगaps
 *
 * Let @old and @new define a mapping of bit positions, such that
 * whatever position is held by the n-th set bit in @old is mapped
 * to the n-th set bit in @new.  In the more general हाल, allowing
 * क्रम the possibility that the weight 'w' of @new is less than the
 * weight of @old, map the position of the n-th set bit in @old to
 * the position of the m-th set bit in @new, where m == n % w.
 *
 * If either of the @old and @new biपंचांगaps are empty, or अगर @src and
 * @dst poपूर्णांक to the same location, then this routine copies @src
 * to @dst.
 *
 * The positions of unset bits in @old are mapped to themselves
 * (the identअगरy map).
 *
 * Apply the above specअगरied mapping to @src, placing the result in
 * @dst, clearing any bits previously set in @dst.
 *
 * For example, lets say that @old has bits 4 through 7 set, and
 * @new has bits 12 through 15 set.  This defines the mapping of bit
 * position 4 to 12, 5 to 13, 6 to 14 and 7 to 15, and of all other
 * bit positions unchanged.  So अगर say @src comes पूर्णांकo this routine
 * with bits 1, 5 and 7 set, then @dst should leave with bits 1,
 * 13 and 15 set.
 */
व्योम biपंचांगap_remap(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
		स्थिर अचिन्हित दीर्घ *old, स्थिर अचिन्हित दीर्घ *new,
		अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक oldbit, w;

	अगर (dst == src)		/* following करोesn't handle inplace remaps */
		वापस;
	biपंचांगap_zero(dst, nbits);

	w = biपंचांगap_weight(new, nbits);
	क्रम_each_set_bit(oldbit, src, nbits) अणु
		पूर्णांक n = biपंचांगap_pos_to_ord(old, oldbit, nbits);

		अगर (n < 0 || w == 0)
			set_bit(oldbit, dst);	/* identity map */
		अन्यथा
			set_bit(biपंचांगap_ord_to_pos(new, n % w, nbits), dst);
	पूर्ण
पूर्ण

/**
 * biपंचांगap_bitremap - Apply map defined by a pair of biपंचांगaps to a single bit
 *	@oldbit: bit position to be mapped
 *	@old: defines करोमुख्य of map
 *	@new: defines range of map
 *	@bits: number of bits in each of these biपंचांगaps
 *
 * Let @old and @new define a mapping of bit positions, such that
 * whatever position is held by the n-th set bit in @old is mapped
 * to the n-th set bit in @new.  In the more general हाल, allowing
 * क्रम the possibility that the weight 'w' of @new is less than the
 * weight of @old, map the position of the n-th set bit in @old to
 * the position of the m-th set bit in @new, where m == n % w.
 *
 * The positions of unset bits in @old are mapped to themselves
 * (the identअगरy map).
 *
 * Apply the above specअगरied mapping to bit position @oldbit, वापसing
 * the new bit position.
 *
 * For example, lets say that @old has bits 4 through 7 set, and
 * @new has bits 12 through 15 set.  This defines the mapping of bit
 * position 4 to 12, 5 to 13, 6 to 14 and 7 to 15, and of all other
 * bit positions unchanged.  So अगर say @oldbit is 5, then this routine
 * वापसs 13.
 */
पूर्णांक biपंचांगap_bitremap(पूर्णांक oldbit, स्थिर अचिन्हित दीर्घ *old,
				स्थिर अचिन्हित दीर्घ *new, पूर्णांक bits)
अणु
	पूर्णांक w = biपंचांगap_weight(new, bits);
	पूर्णांक n = biपंचांगap_pos_to_ord(old, oldbit, bits);
	अगर (n < 0 || w == 0)
		वापस oldbit;
	अन्यथा
		वापस biपंचांगap_ord_to_pos(new, n % w, bits);
पूर्ण

/**
 * biपंचांगap_onto - translate one biपंचांगap relative to another
 *	@dst: resulting translated biपंचांगap
 * 	@orig: original untranslated biपंचांगap
 * 	@relmap: biपंचांगap relative to which translated
 *	@bits: number of bits in each of these biपंचांगaps
 *
 * Set the n-th bit of @dst अगरf there exists some m such that the
 * n-th bit of @relmap is set, the m-th bit of @orig is set, and
 * the n-th bit of @relmap is also the m-th _set_ bit of @relmap.
 * (If you understood the previous sentence the first समय your
 * पढ़ो it, you're overqualअगरied क्रम your current job.)
 *
 * In other words, @orig is mapped onto (surjectively) @dst,
 * using the map अणु <n, m> | the n-th bit of @relmap is the
 * m-th set bit of @relmap पूर्ण.
 *
 * Any set bits in @orig above bit number W, where W is the
 * weight of (number of set bits in) @relmap are mapped nowhere.
 * In particular, अगर क्रम all bits m set in @orig, m >= W, then
 * @dst will end up empty.  In situations where the possibility
 * of such an empty result is not desired, one way to aव्योम it is
 * to use the biपंचांगap_fold() चालक, below, to first fold the
 * @orig biपंचांगap over itself so that all its set bits x are in the
 * range 0 <= x < W.  The biपंचांगap_fold() चालक करोes this by
 * setting the bit (m % W) in @dst, क्रम each bit (m) set in @orig.
 *
 * Example [1] क्रम biपंचांगap_onto():
 *  Let's say @relmap has bits 30-39 set, and @orig has bits
 *  1, 3, 5, 7, 9 and 11 set.  Then on वापस from this routine,
 *  @dst will have bits 31, 33, 35, 37 and 39 set.
 *
 *  When bit 0 is set in @orig, it means turn on the bit in
 *  @dst corresponding to whatever is the first bit (अगर any)
 *  that is turned on in @relmap.  Since bit 0 was off in the
 *  above example, we leave off that bit (bit 30) in @dst.
 *
 *  When bit 1 is set in @orig (as in the above example), it
 *  means turn on the bit in @dst corresponding to whatever
 *  is the second bit that is turned on in @relmap.  The second
 *  bit in @relmap that was turned on in the above example was
 *  bit 31, so we turned on bit 31 in @dst.
 *
 *  Similarly, we turned on bits 33, 35, 37 and 39 in @dst,
 *  because they were the 4th, 6th, 8th and 10th set bits
 *  set in @relmap, and the 4th, 6th, 8th and 10th bits of
 *  @orig (i.e. bits 3, 5, 7 and 9) were also set.
 *
 *  When bit 11 is set in @orig, it means turn on the bit in
 *  @dst corresponding to whatever is the twelfth bit that is
 *  turned on in @relmap.  In the above example, there were
 *  only ten bits turned on in @relmap (30..39), so that bit
 *  11 was set in @orig had no affect on @dst.
 *
 * Example [2] क्रम biपंचांगap_fold() + biपंचांगap_onto():
 *  Let's say @relmap has these ten bits set::
 *
 *		40 41 42 43 45 48 53 61 74 95
 *
 *  (क्रम the curious, that's 40 plus the first ten terms of the
 *  Fibonacci sequence.)
 *
 *  Further lets say we use the following code, invoking
 *  biपंचांगap_fold() then biपंचांगap_onto, as suggested above to
 *  aव्योम the possibility of an empty @dst result::
 *
 *	अचिन्हित दीर्घ *पंचांगp;	// a temporary biपंचांगap's bits
 *
 *	biपंचांगap_fold(पंचांगp, orig, biपंचांगap_weight(relmap, bits), bits);
 *	biपंचांगap_onto(dst, पंचांगp, relmap, bits);
 *
 *  Then this table shows what various values of @dst would be, क्रम
 *  various @orig's.  I list the zero-based positions of each set bit.
 *  The पंचांगp column shows the पूर्णांकermediate result, as computed by
 *  using biपंचांगap_fold() to fold the @orig biपंचांगap modulo ten
 *  (the weight of @relmap):
 *
 *      =============== ============== =================
 *      @orig           पंचांगp            @dst
 *      0                0             40
 *      1                1             41
 *      9                9             95
 *      10               0             40 [#f1]_
 *      1 3 5 7          1 3 5 7       41 43 48 61
 *      0 1 2 3 4        0 1 2 3 4     40 41 42 43 45
 *      0 9 18 27        0 9 8 7       40 61 74 95
 *      0 10 20 30       0             40
 *      0 11 22 33       0 1 2 3       40 41 42 43
 *      0 12 24 36       0 2 4 6       40 42 45 53
 *      78 102 211       1 2 8         41 42 74 [#f1]_
 *      =============== ============== =================
 *
 * .. [#f1]
 *
 *     For these marked lines, अगर we hadn't first करोne biपंचांगap_fold()
 *     पूर्णांकo पंचांगp, then the @dst result would have been empty.
 *
 * If either of @orig or @relmap is empty (no set bits), then @dst
 * will be वापसed empty.
 *
 * If (as explained above) the only set bits in @orig are in positions
 * m where m >= W, (where W is the weight of @relmap) then @dst will
 * once again be वापसed empty.
 *
 * All bits in @dst not set by the above rule are cleared.
 */
व्योम biपंचांगap_onto(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *orig,
			स्थिर अचिन्हित दीर्घ *relmap, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक n, m;	/* same meaning as in above comment */

	अगर (dst == orig)	/* following करोesn't handle inplace mappings */
		वापस;
	biपंचांगap_zero(dst, bits);

	/*
	 * The following code is a more efficient, but less
	 * obvious, equivalent to the loop:
	 *	क्रम (m = 0; m < biपंचांगap_weight(relmap, bits); m++) अणु
	 *		n = biपंचांगap_ord_to_pos(orig, m, bits);
	 *		अगर (test_bit(m, orig))
	 *			set_bit(n, dst);
	 *	पूर्ण
	 */

	m = 0;
	क्रम_each_set_bit(n, relmap, bits) अणु
		/* m == biपंचांगap_pos_to_ord(relmap, n, bits) */
		अगर (test_bit(m, orig))
			set_bit(n, dst);
		m++;
	पूर्ण
पूर्ण

/**
 * biपंचांगap_fold - fold larger biपंचांगap पूर्णांकo smaller, modulo specअगरied size
 *	@dst: resulting smaller biपंचांगap
 *	@orig: original larger biपंचांगap
 *	@sz: specअगरied size
 *	@nbits: number of bits in each of these biपंचांगaps
 *
 * For each bit oldbit in @orig, set bit oldbit mod @sz in @dst.
 * Clear all other bits in @dst.  See further the comment and
 * Example [2] क्रम biपंचांगap_onto() क्रम why and how to use this.
 */
व्योम biपंचांगap_fold(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *orig,
			अचिन्हित पूर्णांक sz, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक oldbit;

	अगर (dst == orig)	/* following करोesn't handle inplace mappings */
		वापस;
	biपंचांगap_zero(dst, nbits);

	क्रम_each_set_bit(oldbit, orig, nbits)
		set_bit(oldbit % sz, dst);
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

/*
 * Common code क्रम biपंचांगap_*_region() routines.
 *	biपंचांगap: array of अचिन्हित दीर्घs corresponding to the biपंचांगap
 *	pos: the beginning of the region
 *	order: region size (log base 2 of number of bits)
 *	reg_op: operation(s) to perक्रमm on that region of biपंचांगap
 *
 * Can set, verअगरy and/or release a region of bits in a biपंचांगap,
 * depending on which combination of REG_OP_* flag bits is set.
 *
 * A region of a biपंचांगap is a sequence of bits in the biपंचांगap, of
 * some size '1 << order' (a घातer of two), aligned to that same
 * '1 << order' घातer of two.
 *
 * Returns 1 अगर REG_OP_ISFREE succeeds (region is all zero bits).
 * Returns 0 in all other हालs and reg_ops.
 */

क्रमागत अणु
	REG_OP_ISFREE,		/* true अगर region is all zero bits */
	REG_OP_ALLOC,		/* set all bits in region */
	REG_OP_RELEASE,		/* clear all bits in region */
पूर्ण;

अटल पूर्णांक __reg_op(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक pos, पूर्णांक order, पूर्णांक reg_op)
अणु
	पूर्णांक nbits_reg;		/* number of bits in region */
	पूर्णांक index;		/* index first दीर्घ of region in biपंचांगap */
	पूर्णांक offset;		/* bit offset region in biपंचांगap[index] */
	पूर्णांक nदीर्घs_reg;		/* num दीर्घs spanned by region in biपंचांगap */
	पूर्णांक nbitsinदीर्घ;	/* num bits of region in each spanned दीर्घ */
	अचिन्हित दीर्घ mask;	/* biपंचांगask क्रम one दीर्घ of region */
	पूर्णांक i;			/* scans biपंचांगap by दीर्घs */
	पूर्णांक ret = 0;		/* वापस value */

	/*
	 * Either nदीर्घs_reg == 1 (क्रम small orders that fit in one दीर्घ)
	 * or (offset == 0 && mask == ~0UL) (क्रम larger multiword orders.)
	 */
	nbits_reg = 1 << order;
	index = pos / BITS_PER_LONG;
	offset = pos - (index * BITS_PER_LONG);
	nदीर्घs_reg = BITS_TO_LONGS(nbits_reg);
	nbitsinदीर्घ = min(nbits_reg,  BITS_PER_LONG);

	/*
	 * Can't करो "mask = (1UL << nbitsinlong) - 1", as that
	 * overflows अगर nbitsinदीर्घ == BITS_PER_LONG.
	 */
	mask = (1UL << (nbitsinदीर्घ - 1));
	mask += mask - 1;
	mask <<= offset;

	चयन (reg_op) अणु
	हाल REG_OP_ISFREE:
		क्रम (i = 0; i < nदीर्घs_reg; i++) अणु
			अगर (biपंचांगap[index + i] & mask)
				जाओ करोne;
		पूर्ण
		ret = 1;	/* all bits in region मुक्त (zero) */
		अवरोध;

	हाल REG_OP_ALLOC:
		क्रम (i = 0; i < nदीर्घs_reg; i++)
			biपंचांगap[index + i] |= mask;
		अवरोध;

	हाल REG_OP_RELEASE:
		क्रम (i = 0; i < nदीर्घs_reg; i++)
			biपंचांगap[index + i] &= ~mask;
		अवरोध;
	पूर्ण
करोne:
	वापस ret;
पूर्ण

/**
 * biपंचांगap_find_मुक्त_region - find a contiguous aligned mem region
 *	@biपंचांगap: array of अचिन्हित दीर्घs corresponding to the biपंचांगap
 *	@bits: number of bits in the biपंचांगap
 *	@order: region size (log base 2 of number of bits) to find
 *
 * Find a region of मुक्त (zero) bits in a @biपंचांगap of @bits bits and
 * allocate them (set them to one).  Only consider regions of length
 * a घातer (@order) of two, aligned to that घातer of two, which
 * makes the search algorithm much faster.
 *
 * Return the bit offset in biपंचांगap of the allocated region,
 * or -त्रुटि_सं on failure.
 */
पूर्णांक biपंचांगap_find_मुक्त_region(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक bits, पूर्णांक order)
अणु
	अचिन्हित पूर्णांक pos, end;		/* scans biपंचांगap by regions of size order */

	क्रम (pos = 0 ; (end = pos + (1U << order)) <= bits; pos = end) अणु
		अगर (!__reg_op(biपंचांगap, pos, order, REG_OP_ISFREE))
			जारी;
		__reg_op(biपंचांगap, pos, order, REG_OP_ALLOC);
		वापस pos;
	पूर्ण
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(biपंचांगap_find_मुक्त_region);

/**
 * biपंचांगap_release_region - release allocated biपंचांगap region
 *	@biपंचांगap: array of अचिन्हित दीर्घs corresponding to the biपंचांगap
 *	@pos: beginning of bit region to release
 *	@order: region size (log base 2 of number of bits) to release
 *
 * This is the complement to __biपंचांगap_find_मुक्त_region() and releases
 * the found region (by clearing it in the biपंचांगap).
 *
 * No वापस value.
 */
व्योम biपंचांगap_release_region(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक pos, पूर्णांक order)
अणु
	__reg_op(biपंचांगap, pos, order, REG_OP_RELEASE);
पूर्ण
EXPORT_SYMBOL(biपंचांगap_release_region);

/**
 * biपंचांगap_allocate_region - allocate biपंचांगap region
 *	@biपंचांगap: array of अचिन्हित दीर्घs corresponding to the biपंचांगap
 *	@pos: beginning of bit region to allocate
 *	@order: region size (log base 2 of number of bits) to allocate
 *
 * Allocate (set bits in) a specअगरied region of a biपंचांगap.
 *
 * Return 0 on success, or %-EBUSY अगर specअगरied region wasn't
 * मुक्त (not all bits were zero).
 */
पूर्णांक biपंचांगap_allocate_region(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक pos, पूर्णांक order)
अणु
	अगर (!__reg_op(biपंचांगap, pos, order, REG_OP_ISFREE))
		वापस -EBUSY;
	वापस __reg_op(biपंचांगap, pos, order, REG_OP_ALLOC);
पूर्ण
EXPORT_SYMBOL(biपंचांगap_allocate_region);

/**
 * biपंचांगap_copy_le - copy a biपंचांगap, putting the bits पूर्णांकo little-endian order.
 * @dst:   destination buffer
 * @src:   biपंचांगap to copy
 * @nbits: number of bits in the biपंचांगap
 *
 * Require nbits % BITS_PER_LONG == 0.
 */
#अगर_घोषित __BIG_ENDIAN
व्योम biपंचांगap_copy_le(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nbits/BITS_PER_LONG; i++) अणु
		अगर (BITS_PER_LONG == 64)
			dst[i] = cpu_to_le64(src[i]);
		अन्यथा
			dst[i] = cpu_to_le32(src[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(biपंचांगap_copy_le);
#पूर्ण_अगर

अचिन्हित दीर्घ *biपंचांगap_alloc(अचिन्हित पूर्णांक nbits, gfp_t flags)
अणु
	वापस kदो_स्मृति_array(BITS_TO_LONGS(nbits), माप(अचिन्हित दीर्घ),
			     flags);
पूर्ण
EXPORT_SYMBOL(biपंचांगap_alloc);

अचिन्हित दीर्घ *biपंचांगap_zalloc(अचिन्हित पूर्णांक nbits, gfp_t flags)
अणु
	वापस biपंचांगap_alloc(nbits, flags | __GFP_ZERO);
पूर्ण
EXPORT_SYMBOL(biपंचांगap_zalloc);

व्योम biपंचांगap_मुक्त(स्थिर अचिन्हित दीर्घ *biपंचांगap)
अणु
	kमुक्त(biपंचांगap);
पूर्ण
EXPORT_SYMBOL(biपंचांगap_मुक्त);

अटल व्योम devm_biपंचांगap_मुक्त(व्योम *data)
अणु
	अचिन्हित दीर्घ *biपंचांगap = data;

	biपंचांगap_मुक्त(biपंचांगap);
पूर्ण

अचिन्हित दीर्घ *devm_biपंचांगap_alloc(काष्ठा device *dev,
				 अचिन्हित पूर्णांक nbits, gfp_t flags)
अणु
	अचिन्हित दीर्घ *biपंचांगap;
	पूर्णांक ret;

	biपंचांगap = biपंचांगap_alloc(nbits, flags);
	अगर (!biपंचांगap)
		वापस शून्य;

	ret = devm_add_action_or_reset(dev, devm_biपंचांगap_मुक्त, biपंचांगap);
	अगर (ret)
		वापस शून्य;

	वापस biपंचांगap;
पूर्ण
EXPORT_SYMBOL_GPL(devm_biपंचांगap_alloc);

अचिन्हित दीर्घ *devm_biपंचांगap_zalloc(काष्ठा device *dev,
				  अचिन्हित पूर्णांक nbits, gfp_t flags)
अणु
	वापस devm_biपंचांगap_alloc(dev, nbits, flags | __GFP_ZERO);
पूर्ण
EXPORT_SYMBOL_GPL(devm_biपंचांगap_zalloc);

#अगर BITS_PER_LONG == 64
/**
 * biपंचांगap_from_arr32 - copy the contents of u32 array of bits to biपंचांगap
 *	@biपंचांगap: array of अचिन्हित दीर्घs, the destination biपंचांगap
 *	@buf: array of u32 (in host byte order), the source biपंचांगap
 *	@nbits: number of bits in @biपंचांगap
 */
व्योम biपंचांगap_from_arr32(अचिन्हित दीर्घ *biपंचांगap, स्थिर u32 *buf, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक i, halfwords;

	halfwords = DIV_ROUND_UP(nbits, 32);
	क्रम (i = 0; i < halfwords; i++) अणु
		biपंचांगap[i/2] = (अचिन्हित दीर्घ) buf[i];
		अगर (++i < halfwords)
			biपंचांगap[i/2] |= ((अचिन्हित दीर्घ) buf[i]) << 32;
	पूर्ण

	/* Clear tail bits in last word beyond nbits. */
	अगर (nbits % BITS_PER_LONG)
		biपंचांगap[(halfwords - 1) / 2] &= BITMAP_LAST_WORD_MASK(nbits);
पूर्ण
EXPORT_SYMBOL(biपंचांगap_from_arr32);

/**
 * biपंचांगap_to_arr32 - copy the contents of biपंचांगap to a u32 array of bits
 *	@buf: array of u32 (in host byte order), the dest biपंचांगap
 *	@biपंचांगap: array of अचिन्हित दीर्घs, the source biपंचांगap
 *	@nbits: number of bits in @biपंचांगap
 */
व्योम biपंचांगap_to_arr32(u32 *buf, स्थिर अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक i, halfwords;

	halfwords = DIV_ROUND_UP(nbits, 32);
	क्रम (i = 0; i < halfwords; i++) अणु
		buf[i] = (u32) (biपंचांगap[i/2] & अच_पूर्णांक_उच्च);
		अगर (++i < halfwords)
			buf[i] = (u32) (biपंचांगap[i/2] >> 32);
	पूर्ण

	/* Clear tail bits in last element of array beyond nbits. */
	अगर (nbits % BITS_PER_LONG)
		buf[halfwords - 1] &= (u32) (अच_पूर्णांक_उच्च >> ((-nbits) & 31));
पूर्ण
EXPORT_SYMBOL(biपंचांगap_to_arr32);

#पूर्ण_अगर
