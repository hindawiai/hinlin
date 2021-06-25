<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BITMAP_H
#घोषणा __LINUX_BITMAP_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/align.h>
#समावेश <linux/bitops.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

काष्ठा device;

/*
 * biपंचांगaps provide bit arrays that consume one or more अचिन्हित
 * दीर्घs.  The biपंचांगap पूर्णांकerface and available operations are listed
 * here, in biपंचांगap.h
 *
 * Function implementations generic to all architectures are in
 * lib/biपंचांगap.c.  Functions implementations that are architecture
 * specअगरic are in various include/यंत्र-<arch>/bitops.h headers
 * and other arch/<arch> specअगरic files.
 *
 * See lib/biपंचांगap.c क्रम more details.
 */

/**
 * DOC: biपंचांगap overview
 *
 * The available biपंचांगap operations and their rough meaning in the
 * हाल that the biपंचांगap is a single अचिन्हित दीर्घ are thus:
 *
 * The generated code is more efficient when nbits is known at
 * compile-समय and at most BITS_PER_LONG.
 *
 * ::
 *
 *  biपंचांगap_zero(dst, nbits)                     *dst = 0UL
 *  biपंचांगap_fill(dst, nbits)                     *dst = ~0UL
 *  biपंचांगap_copy(dst, src, nbits)                *dst = *src
 *  biपंचांगap_and(dst, src1, src2, nbits)          *dst = *src1 & *src2
 *  biपंचांगap_or(dst, src1, src2, nbits)           *dst = *src1 | *src2
 *  biपंचांगap_xor(dst, src1, src2, nbits)          *dst = *src1 ^ *src2
 *  biपंचांगap_andnot(dst, src1, src2, nbits)       *dst = *src1 & ~(*src2)
 *  biपंचांगap_complement(dst, src, nbits)          *dst = ~(*src)
 *  biपंचांगap_equal(src1, src2, nbits)             Are *src1 and *src2 equal?
 *  biपंचांगap_पूर्णांकersects(src1, src2, nbits)        Do *src1 and *src2 overlap?
 *  biपंचांगap_subset(src1, src2, nbits)            Is *src1 a subset of *src2?
 *  biपंचांगap_empty(src, nbits)                    Are all bits zero in *src?
 *  biपंचांगap_full(src, nbits)                     Are all bits set in *src?
 *  biपंचांगap_weight(src, nbits)                   Hamming Weight: number set bits
 *  biपंचांगap_set(dst, pos, nbits)                 Set specअगरied bit area
 *  biपंचांगap_clear(dst, pos, nbits)               Clear specअगरied bit area
 *  biपंचांगap_find_next_zero_area(buf, len, pos, n, mask)  Find bit मुक्त area
 *  biपंचांगap_find_next_zero_area_off(buf, len, pos, n, mask, mask_off)  as above
 *  biपंचांगap_next_clear_region(map, &start, &end, nbits)  Find next clear region
 *  biपंचांगap_next_set_region(map, &start, &end, nbits)  Find next set region
 *  biपंचांगap_क्रम_each_clear_region(map, rs, re, start, end)
 *  						Iterate over all clear regions
 *  biपंचांगap_क्रम_each_set_region(map, rs, re, start, end)
 *  						Iterate over all set regions
 *  biपंचांगap_shअगरt_right(dst, src, n, nbits)      *dst = *src >> n
 *  biपंचांगap_shअगरt_left(dst, src, n, nbits)       *dst = *src << n
 *  biपंचांगap_cut(dst, src, first, n, nbits)       Cut n bits from first, copy rest
 *  biपंचांगap_replace(dst, old, new, mask, nbits)  *dst = (*old & ~(*mask)) | (*new & *mask)
 *  biपंचांगap_remap(dst, src, old, new, nbits)     *dst = map(old, new)(src)
 *  biपंचांगap_bitremap(oldbit, old, new, nbits)    newbit = map(old, new)(oldbit)
 *  biपंचांगap_onto(dst, orig, relmap, nbits)       *dst = orig relative to relmap
 *  biपंचांगap_fold(dst, orig, sz, nbits)           dst bits = orig bits mod sz
 *  biपंचांगap_parse(buf, buflen, dst, nbits)       Parse biपंचांगap dst from kernel buf
 *  biपंचांगap_parse_user(ubuf, ulen, dst, nbits)   Parse biपंचांगap dst from user buf
 *  biपंचांगap_parselist(buf, dst, nbits)           Parse biपंचांगap dst from kernel buf
 *  biपंचांगap_parselist_user(buf, dst, nbits)      Parse biपंचांगap dst from user buf
 *  biपंचांगap_find_मुक्त_region(biपंचांगap, bits, order)  Find and allocate bit region
 *  biपंचांगap_release_region(biपंचांगap, pos, order)   Free specअगरied bit region
 *  biपंचांगap_allocate_region(biपंचांगap, pos, order)  Allocate specअगरied bit region
 *  biपंचांगap_from_arr32(dst, buf, nbits)          Copy nbits from u32[] buf to dst
 *  biपंचांगap_to_arr32(buf, src, nbits)            Copy nbits from buf to u32[] dst
 *  biपंचांगap_get_value8(map, start)               Get 8bit value from map at start
 *  biपंचांगap_set_value8(map, value, start)        Set 8bit value to map at start
 *
 * Note, biपंचांगap_zero() and biपंचांगap_fill() operate over the region of
 * अचिन्हित दीर्घs, that is, bits behind biपंचांगap till the अचिन्हित दीर्घ
 * boundary will be zeroed or filled as well. Consider to use
 * biपंचांगap_clear() or biपंचांगap_set() to make explicit zeroing or filling
 * respectively.
 */

/**
 * DOC: biपंचांगap bitops
 *
 * Also the following operations in यंत्र/bitops.h apply to biपंचांगaps.::
 *
 *  set_bit(bit, addr)                  *addr |= bit
 *  clear_bit(bit, addr)                *addr &= ~bit
 *  change_bit(bit, addr)               *addr ^= bit
 *  test_bit(bit, addr)                 Is bit set in *addr?
 *  test_and_set_bit(bit, addr)         Set bit and वापस old value
 *  test_and_clear_bit(bit, addr)       Clear bit and वापस old value
 *  test_and_change_bit(bit, addr)      Change bit and वापस old value
 *  find_first_zero_bit(addr, nbits)    Position first zero bit in *addr
 *  find_first_bit(addr, nbits)         Position first set bit in *addr
 *  find_next_zero_bit(addr, nbits, bit)
 *                                      Position next zero bit in *addr >= bit
 *  find_next_bit(addr, nbits, bit)     Position next set bit in *addr >= bit
 *  find_next_and_bit(addr1, addr2, nbits, bit)
 *                                      Same as find_next_bit, but in
 *                                      (*addr1 & *addr2)
 *
 */

/**
 * DOC: declare biपंचांगap
 * The DECLARE_BITMAP(name,bits) macro, in linux/types.h, can be used
 * to declare an array named 'name' of just enough अचिन्हित दीर्घs to
 * contain all bit positions from 0 to 'bits' - 1.
 */

/*
 * Allocation and deallocation of biपंचांगap.
 * Provided in lib/biपंचांगap.c to aव्योम circular dependency.
 */
अचिन्हित दीर्घ *biपंचांगap_alloc(अचिन्हित पूर्णांक nbits, gfp_t flags);
अचिन्हित दीर्घ *biपंचांगap_zalloc(अचिन्हित पूर्णांक nbits, gfp_t flags);
व्योम biपंचांगap_मुक्त(स्थिर अचिन्हित दीर्घ *biपंचांगap);

/* Managed variants of the above. */
अचिन्हित दीर्घ *devm_biपंचांगap_alloc(काष्ठा device *dev,
				 अचिन्हित पूर्णांक nbits, gfp_t flags);
अचिन्हित दीर्घ *devm_biपंचांगap_zalloc(काष्ठा device *dev,
				  अचिन्हित पूर्णांक nbits, gfp_t flags);

/*
 * lib/biपंचांगap.c provides these functions:
 */

पूर्णांक __biपंचांगap_equal(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		   स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक nbits);
bool __pure __biपंचांगap_or_equal(स्थिर अचिन्हित दीर्घ *src1,
			      स्थिर अचिन्हित दीर्घ *src2,
			      स्थिर अचिन्हित दीर्घ *src3,
			      अचिन्हित पूर्णांक nbits);
व्योम __biपंचांगap_complement(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
			 अचिन्हित पूर्णांक nbits);
व्योम __biपंचांगap_shअगरt_right(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
			  अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक nbits);
व्योम __biपंचांगap_shअगरt_left(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
			 अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक nbits);
व्योम biपंचांगap_cut(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
		अचिन्हित पूर्णांक first, अचिन्हित पूर्णांक cut, अचिन्हित पूर्णांक nbits);
पूर्णांक __biपंचांगap_and(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		 स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक nbits);
व्योम __biपंचांगap_or(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		 स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक nbits);
व्योम __biपंचांगap_xor(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		  स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक nbits);
पूर्णांक __biपंचांगap_andnot(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		    स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक nbits);
व्योम __biपंचांगap_replace(अचिन्हित दीर्घ *dst,
		      स्थिर अचिन्हित दीर्घ *old, स्थिर अचिन्हित दीर्घ *new,
		      स्थिर अचिन्हित दीर्घ *mask, अचिन्हित पूर्णांक nbits);
पूर्णांक __biपंचांगap_पूर्णांकersects(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
			स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक nbits);
पूर्णांक __biपंचांगap_subset(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		    स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक nbits);
पूर्णांक __biपंचांगap_weight(स्थिर अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits);
व्योम __biपंचांगap_set(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start, पूर्णांक len);
व्योम __biपंचांगap_clear(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start, पूर्णांक len);

अचिन्हित दीर्घ biपंचांगap_find_next_zero_area_off(अचिन्हित दीर्घ *map,
					     अचिन्हित दीर्घ size,
					     अचिन्हित दीर्घ start,
					     अचिन्हित पूर्णांक nr,
					     अचिन्हित दीर्घ align_mask,
					     अचिन्हित दीर्घ align_offset);

/**
 * biपंचांगap_find_next_zero_area - find a contiguous aligned zero area
 * @map: The address to base the search on
 * @size: The biपंचांगap size in bits
 * @start: The bitnumber to start searching at
 * @nr: The number of zeroed bits we're looking क्रम
 * @align_mask: Alignment mask क्रम zero area
 *
 * The @align_mask should be one less than a घातer of 2; the effect is that
 * the bit offset of all zero areas this function finds is multiples of that
 * घातer of 2. A @align_mask of 0 means no alignment is required.
 */
अटल अंतरभूत अचिन्हित दीर्घ
biपंचांगap_find_next_zero_area(अचिन्हित दीर्घ *map,
			   अचिन्हित दीर्घ size,
			   अचिन्हित दीर्घ start,
			   अचिन्हित पूर्णांक nr,
			   अचिन्हित दीर्घ align_mask)
अणु
	वापस biपंचांगap_find_next_zero_area_off(map, size, start, nr,
					      align_mask, 0);
पूर्ण

पूर्णांक biपंचांगap_parse(स्थिर अक्षर *buf, अचिन्हित पूर्णांक buflen,
			अचिन्हित दीर्घ *dst, पूर्णांक nbits);
पूर्णांक biपंचांगap_parse_user(स्थिर अक्षर __user *ubuf, अचिन्हित पूर्णांक ulen,
			अचिन्हित दीर्घ *dst, पूर्णांक nbits);
पूर्णांक biपंचांगap_parselist(स्थिर अक्षर *buf, अचिन्हित दीर्घ *maskp,
			पूर्णांक nmaskbits);
पूर्णांक biपंचांगap_parselist_user(स्थिर अक्षर __user *ubuf, अचिन्हित पूर्णांक ulen,
			अचिन्हित दीर्घ *dst, पूर्णांक nbits);
व्योम biपंचांगap_remap(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
		स्थिर अचिन्हित दीर्घ *old, स्थिर अचिन्हित दीर्घ *new, अचिन्हित पूर्णांक nbits);
पूर्णांक biपंचांगap_bitremap(पूर्णांक oldbit,
		स्थिर अचिन्हित दीर्घ *old, स्थिर अचिन्हित दीर्घ *new, पूर्णांक bits);
व्योम biपंचांगap_onto(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *orig,
		स्थिर अचिन्हित दीर्घ *relmap, अचिन्हित पूर्णांक bits);
व्योम biपंचांगap_fold(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *orig,
		अचिन्हित पूर्णांक sz, अचिन्हित पूर्णांक nbits);
पूर्णांक biपंचांगap_find_मुक्त_region(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक bits, पूर्णांक order);
व्योम biपंचांगap_release_region(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक pos, पूर्णांक order);
पूर्णांक biपंचांगap_allocate_region(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक pos, पूर्णांक order);

#अगर_घोषित __BIG_ENDIAN
व्योम biपंचांगap_copy_le(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक nbits);
#अन्यथा
#घोषणा biपंचांगap_copy_le biपंचांगap_copy
#पूर्ण_अगर
अचिन्हित पूर्णांक biपंचांगap_ord_to_pos(स्थिर अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक ord, अचिन्हित पूर्णांक nbits);
पूर्णांक biपंचांगap_prपूर्णांक_to_pagebuf(bool list, अक्षर *buf,
				   स्थिर अचिन्हित दीर्घ *maskp, पूर्णांक nmaskbits);

#घोषणा BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) & (BITS_PER_LONG - 1)))
#घोषणा BITMAP_LAST_WORD_MASK(nbits) (~0UL >> (-(nbits) & (BITS_PER_LONG - 1)))

अटल अंतरभूत व्योम biपंचांगap_zero(अचिन्हित दीर्घ *dst, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक len = BITS_TO_LONGS(nbits) * माप(अचिन्हित दीर्घ);
	स_रखो(dst, 0, len);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_fill(अचिन्हित दीर्घ *dst, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक len = BITS_TO_LONGS(nbits) * माप(अचिन्हित दीर्घ);
	स_रखो(dst, 0xff, len);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_copy(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
			अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक len = BITS_TO_LONGS(nbits) * माप(अचिन्हित दीर्घ);
	स_नकल(dst, src, len);
पूर्ण

/*
 * Copy biपंचांगap and clear tail bits in last word.
 */
अटल अंतरभूत व्योम biपंचांगap_copy_clear_tail(अचिन्हित दीर्घ *dst,
		स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_copy(dst, src, nbits);
	अगर (nbits % BITS_PER_LONG)
		dst[nbits / BITS_PER_LONG] &= BITMAP_LAST_WORD_MASK(nbits);
पूर्ण

/*
 * On 32-bit प्रणालीs biपंचांगaps are represented as u32 arrays पूर्णांकernally, and
 * thereक्रमe conversion is not needed when copying data from/to arrays of u32.
 */
#अगर BITS_PER_LONG == 64
व्योम biपंचांगap_from_arr32(अचिन्हित दीर्घ *biपंचांगap, स्थिर u32 *buf,
							अचिन्हित पूर्णांक nbits);
व्योम biपंचांगap_to_arr32(u32 *buf, स्थिर अचिन्हित दीर्घ *biपंचांगap,
							अचिन्हित पूर्णांक nbits);
#अन्यथा
#घोषणा biपंचांगap_from_arr32(biपंचांगap, buf, nbits)			\
	biपंचांगap_copy_clear_tail((अचिन्हित दीर्घ *) (biपंचांगap),	\
			(स्थिर अचिन्हित दीर्घ *) (buf), (nbits))
#घोषणा biपंचांगap_to_arr32(buf, biपंचांगap, nbits)			\
	biपंचांगap_copy_clear_tail((अचिन्हित दीर्घ *) (buf),		\
			(स्थिर अचिन्हित दीर्घ *) (biपंचांगap), (nbits))
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक biपंचांगap_and(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस (*dst = *src1 & *src2 & BITMAP_LAST_WORD_MASK(nbits)) != 0;
	वापस __biपंचांगap_and(dst, src1, src2, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_or(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = *src1 | *src2;
	अन्यथा
		__biपंचांगap_or(dst, src1, src2, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_xor(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = *src1 ^ *src2;
	अन्यथा
		__biपंचांगap_xor(dst, src1, src2, nbits);
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_andnot(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस (*dst = *src1 & ~(*src2) & BITMAP_LAST_WORD_MASK(nbits)) != 0;
	वापस __biपंचांगap_andnot(dst, src1, src2, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_complement(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
			अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = ~(*src);
	अन्यथा
		__biपंचांगap_complement(dst, src, nbits);
पूर्ण

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा BITMAP_MEM_ALIGNMENT 8
#अन्यथा
#घोषणा BITMAP_MEM_ALIGNMENT (8 * माप(अचिन्हित दीर्घ))
#पूर्ण_अगर
#घोषणा BITMAP_MEM_MASK (BITMAP_MEM_ALIGNMENT - 1)

अटल अंतरभूत पूर्णांक biपंचांगap_equal(स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस !((*src1 ^ *src2) & BITMAP_LAST_WORD_MASK(nbits));
	अगर (__builtin_स्थिरant_p(nbits & BITMAP_MEM_MASK) &&
	    IS_ALIGNED(nbits, BITMAP_MEM_ALIGNMENT))
		वापस !स_भेद(src1, src2, nbits / 8);
	वापस __biपंचांगap_equal(src1, src2, nbits);
पूर्ण

/**
 * biपंचांगap_or_equal - Check whether the or of two biपंचांगaps is equal to a third
 * @src1:	Poपूर्णांकer to biपंचांगap 1
 * @src2:	Poपूर्णांकer to biपंचांगap 2 will be or'ed with biपंचांगap 1
 * @src3:	Poपूर्णांकer to biपंचांगap 3. Compare to the result of *@src1 | *@src2
 * @nbits:	number of bits in each of these biपंचांगaps
 *
 * Returns: True अगर (*@src1 | *@src2) == *@src3, false otherwise
 */
अटल अंतरभूत bool biपंचांगap_or_equal(स्थिर अचिन्हित दीर्घ *src1,
				   स्थिर अचिन्हित दीर्घ *src2,
				   स्थिर अचिन्हित दीर्घ *src3,
				   अचिन्हित पूर्णांक nbits)
अणु
	अगर (!small_स्थिर_nbits(nbits))
		वापस __biपंचांगap_or_equal(src1, src2, src3, nbits);

	वापस !(((*src1 | *src2) ^ *src3) & BITMAP_LAST_WORD_MASK(nbits));
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_पूर्णांकersects(स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस ((*src1 & *src2) & BITMAP_LAST_WORD_MASK(nbits)) != 0;
	अन्यथा
		वापस __biपंचांगap_पूर्णांकersects(src1, src2, nbits);
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_subset(स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस ! ((*src1 & ~(*src2)) & BITMAP_LAST_WORD_MASK(nbits));
	अन्यथा
		वापस __biपंचांगap_subset(src1, src2, nbits);
पूर्ण

अटल अंतरभूत bool biपंचांगap_empty(स्थिर अचिन्हित दीर्घ *src, अचिन्हित nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस ! (*src & BITMAP_LAST_WORD_MASK(nbits));

	वापस find_first_bit(src, nbits) == nbits;
पूर्ण

अटल अंतरभूत bool biपंचांगap_full(स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस ! (~(*src) & BITMAP_LAST_WORD_MASK(nbits));

	वापस find_first_zero_bit(src, nbits) == nbits;
पूर्ण

अटल __always_अंतरभूत पूर्णांक biपंचांगap_weight(स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस hweight_दीर्घ(*src & BITMAP_LAST_WORD_MASK(nbits));
	वापस __biपंचांगap_weight(src, nbits);
पूर्ण

अटल __always_अंतरभूत व्योम biपंचांगap_set(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start,
		अचिन्हित पूर्णांक nbits)
अणु
	अगर (__builtin_स्थिरant_p(nbits) && nbits == 1)
		__set_bit(start, map);
	अन्यथा अगर (__builtin_स्थिरant_p(start & BITMAP_MEM_MASK) &&
		 IS_ALIGNED(start, BITMAP_MEM_ALIGNMENT) &&
		 __builtin_स्थिरant_p(nbits & BITMAP_MEM_MASK) &&
		 IS_ALIGNED(nbits, BITMAP_MEM_ALIGNMENT))
		स_रखो((अक्षर *)map + start / 8, 0xff, nbits / 8);
	अन्यथा
		__biपंचांगap_set(map, start, nbits);
पूर्ण

अटल __always_अंतरभूत व्योम biपंचांगap_clear(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start,
		अचिन्हित पूर्णांक nbits)
अणु
	अगर (__builtin_स्थिरant_p(nbits) && nbits == 1)
		__clear_bit(start, map);
	अन्यथा अगर (__builtin_स्थिरant_p(start & BITMAP_MEM_MASK) &&
		 IS_ALIGNED(start, BITMAP_MEM_ALIGNMENT) &&
		 __builtin_स्थिरant_p(nbits & BITMAP_MEM_MASK) &&
		 IS_ALIGNED(nbits, BITMAP_MEM_ALIGNMENT))
		स_रखो((अक्षर *)map + start / 8, 0, nbits / 8);
	अन्यथा
		__biपंचांगap_clear(map, start, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_shअगरt_right(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = (*src & BITMAP_LAST_WORD_MASK(nbits)) >> shअगरt;
	अन्यथा
		__biपंचांगap_shअगरt_right(dst, src, shअगरt, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_shअगरt_left(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = (*src << shअगरt) & BITMAP_LAST_WORD_MASK(nbits);
	अन्यथा
		__biपंचांगap_shअगरt_left(dst, src, shअगरt, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_replace(अचिन्हित दीर्घ *dst,
				  स्थिर अचिन्हित दीर्घ *old,
				  स्थिर अचिन्हित दीर्घ *new,
				  स्थिर अचिन्हित दीर्घ *mask,
				  अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = (*old & ~(*mask)) | (*new & *mask);
	अन्यथा
		__biपंचांगap_replace(dst, old, new, mask, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_next_clear_region(अचिन्हित दीर्घ *biपंचांगap,
					    अचिन्हित पूर्णांक *rs, अचिन्हित पूर्णांक *re,
					    अचिन्हित पूर्णांक end)
अणु
	*rs = find_next_zero_bit(biपंचांगap, end, *rs);
	*re = find_next_bit(biपंचांगap, end, *rs + 1);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_next_set_region(अचिन्हित दीर्घ *biपंचांगap,
					  अचिन्हित पूर्णांक *rs, अचिन्हित पूर्णांक *re,
					  अचिन्हित पूर्णांक end)
अणु
	*rs = find_next_bit(biपंचांगap, end, *rs);
	*re = find_next_zero_bit(biपंचांगap, end, *rs + 1);
पूर्ण

/*
 * Biपंचांगap region iterators.  Iterates over the biपंचांगap between [@start, @end).
 * @rs and @re should be पूर्णांकeger variables and will be set to start and end
 * index of the current clear or set region.
 */
#घोषणा biपंचांगap_क्रम_each_clear_region(biपंचांगap, rs, re, start, end)	     \
	क्रम ((rs) = (start),						     \
	     biपंचांगap_next_clear_region((biपंचांगap), &(rs), &(re), (end));	     \
	     (rs) < (re);						     \
	     (rs) = (re) + 1,						     \
	     biपंचांगap_next_clear_region((biपंचांगap), &(rs), &(re), (end)))

#घोषणा biपंचांगap_क्रम_each_set_region(biपंचांगap, rs, re, start, end)		     \
	क्रम ((rs) = (start),						     \
	     biपंचांगap_next_set_region((biपंचांगap), &(rs), &(re), (end));	     \
	     (rs) < (re);						     \
	     (rs) = (re) + 1,						     \
	     biपंचांगap_next_set_region((biपंचांगap), &(rs), &(re), (end)))

/**
 * BITMAP_FROM_U64() - Represent u64 value in the क्रमmat suitable क्रम biपंचांगap.
 * @n: u64 value
 *
 * Linux biपंचांगaps are पूर्णांकernally arrays of अचिन्हित दीर्घs, i.e. 32-bit
 * पूर्णांकegers in 32-bit environment, and 64-bit पूर्णांकegers in 64-bit one.
 *
 * There are four combinations of endianness and length of the word in linux
 * ABIs: LE64, BE64, LE32 and BE32.
 *
 * On 64-bit kernels 64-bit LE and BE numbers are naturally ordered in
 * biपंचांगaps and thereक्रमe करोn't require any special handling.
 *
 * On 32-bit kernels 32-bit LE ABI orders lo word of 64-bit number in memory
 * prior to hi, and 32-bit BE orders hi word prior to lo. The biपंचांगap on the
 * other hand is represented as an array of 32-bit words and the position of
 * bit N may thereक्रमe be calculated as: word #(N/32) and bit #(N%32) in that
 * word.  For example, bit #42 is located at 10th position of 2nd word.
 * It matches 32-bit LE ABI, and we can simply let the compiler store 64-bit
 * values in memory as it usually करोes. But क्रम BE we need to swap hi and lo
 * words manually.
 *
 * With all that, the macro BITMAP_FROM_U64() करोes explicit reordering of hi and
 * lo parts of u64.  For LE32 it करोes nothing, and क्रम BE environment it swaps
 * hi and lo words, as is expected by biपंचांगap.
 */
#अगर __BITS_PER_LONG == 64
#घोषणा BITMAP_FROM_U64(n) (n)
#अन्यथा
#घोषणा BITMAP_FROM_U64(n) ((अचिन्हित दीर्घ) ((u64)(n) & अच_दीर्घ_उच्च)), \
				((अचिन्हित दीर्घ) ((u64)(n) >> 32))
#पूर्ण_अगर

/**
 * biपंचांगap_from_u64 - Check and swap words within u64.
 *  @mask: source biपंचांगap
 *  @dst:  destination biपंचांगap
 *
 * In 32-bit Big Endian kernel, when using ``(u32 *)(&val)[*]``
 * to पढ़ो u64 mask, we will get the wrong word.
 * That is ``(u32 *)(&val)[0]`` माला_लो the upper 32 bits,
 * but we expect the lower 32-bits of u64.
 */
अटल अंतरभूत व्योम biपंचांगap_from_u64(अचिन्हित दीर्घ *dst, u64 mask)
अणु
	dst[0] = mask & अच_दीर्घ_उच्च;

	अगर (माप(mask) > माप(अचिन्हित दीर्घ))
		dst[1] = mask >> 32;
पूर्ण

/**
 * biपंचांगap_get_value8 - get an 8-bit value within a memory region
 * @map: address to the biपंचांगap memory region
 * @start: bit offset of the 8-bit value; must be a multiple of 8
 *
 * Returns the 8-bit value located at the @start bit offset within the @src
 * memory region.
 */
अटल अंतरभूत अचिन्हित दीर्घ biपंचांगap_get_value8(स्थिर अचिन्हित दीर्घ *map,
					      अचिन्हित दीर्घ start)
अणु
	स्थिर माप_प्रकार index = BIT_WORD(start);
	स्थिर अचिन्हित दीर्घ offset = start % BITS_PER_LONG;

	वापस (map[index] >> offset) & 0xFF;
पूर्ण

/**
 * biपंचांगap_set_value8 - set an 8-bit value within a memory region
 * @map: address to the biपंचांगap memory region
 * @value: the 8-bit value; values wider than 8 bits may clobber biपंचांगap
 * @start: bit offset of the 8-bit value; must be a multiple of 8
 */
अटल अंतरभूत व्योम biपंचांगap_set_value8(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ value,
				     अचिन्हित दीर्घ start)
अणु
	स्थिर माप_प्रकार index = BIT_WORD(start);
	स्थिर अचिन्हित दीर्घ offset = start % BITS_PER_LONG;

	map[index] &= ~(0xFFUL << offset);
	map[index] |= value << offset;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __LINUX_BITMAP_H */
