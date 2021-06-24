<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/* PIPAPO: PIle PAcket POlicies: AVX2 packet lookup routines
 *
 * Copyright (c) 2019-2020 Red Hat GmbH
 *
 * Author: Stefano Brivio <sbrivio@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <uapi/linux/netfilter/nf_tables.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>

#समावेश <linux/compiler.h>
#समावेश <यंत्र/fpu/api.h>

#समावेश "nft_set_pipapo_avx2.h"
#समावेश "nft_set_pipapo.h"

#घोषणा NFT_PIPAPO_LONGS_PER_M256	(XSAVE_YMM_SIZE / BITS_PER_LONG)

/* Load from memory पूर्णांकo YMM रेजिस्टर with non-temporal hपूर्णांक ("stream load"),
 * that is, करोn't fetch lines from memory पूर्णांकo the cache. This aव्योमs pushing
 * precious packet data out of the cache hierarchy, and is appropriate when:
 *
 * - loading buckets from lookup tables, as they are not going to be used
 *   again beक्रमe packets are entirely classअगरied
 *
 * - loading the result biपंचांगap from the previous field, as it's never used
 *   again
 */
#घोषणा NFT_PIPAPO_AVX2_LOAD(reg, loc)					\
	यंत्र अस्थिर("vmovntdqa %0, %%ymm" #reg : : "m" (loc))

/* Stream a single lookup table bucket पूर्णांकo YMM रेजिस्टर given lookup table,
 * group index, value of packet bits, bucket size.
 */
#घोषणा NFT_PIPAPO_AVX2_BUCKET_LOAD4(reg, lt, group, v, bsize)		\
	NFT_PIPAPO_AVX2_LOAD(reg,					\
			     lt[((group) * NFT_PIPAPO_BUCKETS(4) +	\
				 (v)) * (bsize)])
#घोषणा NFT_PIPAPO_AVX2_BUCKET_LOAD8(reg, lt, group, v, bsize)		\
	NFT_PIPAPO_AVX2_LOAD(reg,					\
			     lt[((group) * NFT_PIPAPO_BUCKETS(8) +	\
				 (v)) * (bsize)])

/* Bitwise AND: the staple operation of this algorithm */
#घोषणा NFT_PIPAPO_AVX2_AND(dst, a, b)					\
	यंत्र अस्थिर("vpand %ymm" #a ", %ymm" #b ", %ymm" #dst)

/* Jump to label अगर @reg is zero */
#घोषणा NFT_PIPAPO_AVX2_NOMATCH_GOTO(reg, label)			\
	यंत्र_अस्थिर_जाओ("vptest %%ymm" #reg ", %%ymm" #reg ";"	\
			  "je %l[" #label "]" : : : : label)

/* Store 256 bits from YMM रेजिस्टर पूर्णांकo memory. Contrary to bucket load
 * operation, we करोn't bypass the cache here, as stored matching results
 * are always used लघुly after.
 */
#घोषणा NFT_PIPAPO_AVX2_STORE(loc, reg)					\
	यंत्र अस्थिर("vmovdqa %%ymm" #reg ", %0" : "=m" (loc))

/* Zero out a complete YMM रेजिस्टर, @reg */
#घोषणा NFT_PIPAPO_AVX2_ZERO(reg)					\
	यंत्र अस्थिर("vpxor %ymm" #reg ", %ymm" #reg ", %ymm" #reg)

/* Current working biपंचांगap index, toggled between field matches */
अटल DEFINE_PER_CPU(bool, nft_pipapo_avx2_scratch_index);

/**
 * nft_pipapo_avx2_prepare() - Prepare beक्रमe मुख्य algorithm body
 *
 * This zeroes out ymm15, which is later used whenever we need to clear a
 * memory location, by storing its content पूर्णांकo memory.
 */
अटल व्योम nft_pipapo_avx2_prepare(व्योम)
अणु
	NFT_PIPAPO_AVX2_ZERO(15);
पूर्ण

/**
 * nft_pipapo_avx2_fill() - Fill a biपंचांगap region with ones
 * @data:	Base memory area
 * @start:	First bit to set
 * @len:	Count of bits to fill
 *
 * This is nothing अन्यथा than a version of biपंचांगap_set(), as used e.g. by
 * pipapo_refill(), tailored क्रम the microarchitectures using it and better
 * suited क्रम the specअगरic usage: it's very likely that we'll set a small number
 * of bits, not crossing a word boundary, and correct branch prediction is
 * critical here.
 *
 * This function करोesn't actually use any AVX2 inकाष्ठाion.
 */
अटल व्योम nft_pipapo_avx2_fill(अचिन्हित दीर्घ *data, पूर्णांक start, पूर्णांक len)
अणु
	पूर्णांक offset = start % BITS_PER_LONG;
	अचिन्हित दीर्घ mask;

	data += start / BITS_PER_LONG;

	अगर (likely(len == 1)) अणु
		*data |= BIT(offset);
		वापस;
	पूर्ण

	अगर (likely(len < BITS_PER_LONG || offset)) अणु
		अगर (likely(len + offset <= BITS_PER_LONG)) अणु
			*data |= GENMASK(len - 1 + offset, offset);
			वापस;
		पूर्ण

		*data |= ~0UL << offset;
		len -= BITS_PER_LONG - offset;
		data++;

		अगर (len <= BITS_PER_LONG) अणु
			mask = ~0UL >> (BITS_PER_LONG - len);
			*data |= mask;
			वापस;
		पूर्ण
	पूर्ण

	स_रखो(data, 0xff, len / BITS_PER_BYTE);
	data += len / BITS_PER_LONG;

	len %= BITS_PER_LONG;
	अगर (len)
		*data |= ~0UL >> (BITS_PER_LONG - len);
पूर्ण

/**
 * nft_pipapo_avx2_refill() - Scan biपंचांगap, select mapping table item, set bits
 * @offset:	Start from given biपंचांगap (equivalent to bucket) offset, in दीर्घs
 * @map:	Biपंचांगap to be scanned क्रम set bits
 * @dst:	Destination biपंचांगap
 * @mt:		Mapping table containing bit set specअगरiers
 * @len:	Length of biपंचांगap in दीर्घs
 * @last:	Return index of first set bit, अगर this is the last field
 *
 * This is an alternative implementation of pipapo_refill() suitable क्रम usage
 * with AVX2 lookup routines: we know there are four words to be scanned, at
 * a given offset inside the map, क्रम each matching iteration.
 *
 * This function करोesn't actually use any AVX2 inकाष्ठाion.
 *
 * Return: first set bit index अगर @last, index of first filled word otherwise.
 */
अटल पूर्णांक nft_pipapo_avx2_refill(पूर्णांक offset, अचिन्हित दीर्घ *map,
				  अचिन्हित दीर्घ *dst,
				  जोड़ nft_pipapo_map_bucket *mt, bool last)
अणु
	पूर्णांक ret = -1;

#घोषणा NFT_PIPAPO_AVX2_REFILL_ONE_WORD(x)				\
	करो अणु								\
		जबतक (map[(x)]) अणु					\
			पूर्णांक r = __builtin_ctzl(map[(x)]);		\
			पूर्णांक i = (offset + (x)) * BITS_PER_LONG + r;	\
									\
			अगर (last)					\
				वापस i;				\
									\
			nft_pipapo_avx2_fill(dst, mt[i].to, mt[i].n);	\
									\
			अगर (ret == -1)					\
				ret = mt[i].to;				\
									\
			map[(x)] &= ~(1UL << r);			\
		पूर्ण							\
	पूर्ण जबतक (0)

	NFT_PIPAPO_AVX2_REFILL_ONE_WORD(0);
	NFT_PIPAPO_AVX2_REFILL_ONE_WORD(1);
	NFT_PIPAPO_AVX2_REFILL_ONE_WORD(2);
	NFT_PIPAPO_AVX2_REFILL_ONE_WORD(3);
#अघोषित NFT_PIPAPO_AVX2_REFILL_ONE_WORD

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_4b_2() - AVX2-based lookup क्रम 2 four-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * Load buckets from lookup table corresponding to the values of each 4-bit
 * group of packet bytes, and perक्रमm a bitwise पूर्णांकersection between them. If
 * this is the first field in the set, simply AND the buckets together
 * (equivalent to using an all-ones starting biपंचांगap), use the provided starting
 * biपंचांगap otherwise. Then call nft_pipapo_avx2_refill() to generate the next
 * working biपंचांगap, @fill.
 *
 * This is used क्रम 8-bit fields (i.e. protocol numbers).
 *
 * Out-of-order (and superscalar) execution is vital here, so it's critical to
 * aव्योम false data dependencies. CPU and compiler could (mostly) take care of
 * this on their own, but the operation ordering is explicitly given here with
 * a likely execution order in mind, to highlight possible stalls. That's why
 * a number of logically distinct operations (i.e. loading buckets, पूर्णांकersecting
 * buckets) are पूर्णांकerleaved.
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_4b_2(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				       काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				       स्थिर u8 *pkt, bool first, bool last)
अणु
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	u8 pg[2] = अणु pkt[0] >> 4, pkt[0] & 0xf पूर्ण;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (first) अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(0, lt, 0, pg[0], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(1, lt, 1, pg[1], bsize);
			NFT_PIPAPO_AVX2_AND(4, 0, 1);
		पूर्ण अन्यथा अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(0, lt, 0, pg[0], bsize);
			NFT_PIPAPO_AVX2_LOAD(2, map[i_ul]);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(1, lt, 1, pg[1], bsize);
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(2, nothing);
			NFT_PIPAPO_AVX2_AND(3, 0, 1);
			NFT_PIPAPO_AVX2_AND(4, 2, 3);
		पूर्ण

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(4, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 4);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;
nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_4b_4() - AVX2-based lookup क्रम 4 four-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 16-bit fields (i.e. ports).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_4b_4(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				       काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				       स्थिर u8 *pkt, bool first, bool last)
अणु
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	u8 pg[4] = अणु pkt[0] >> 4, pkt[0] & 0xf, pkt[1] >> 4, pkt[1] & 0xf पूर्ण;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (first) अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(0, lt, 0, pg[0], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(1, lt, 1, pg[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(2, lt, 2, pg[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(3, lt, 3, pg[3], bsize);
			NFT_PIPAPO_AVX2_AND(4, 0, 1);
			NFT_PIPAPO_AVX2_AND(5, 2, 3);
			NFT_PIPAPO_AVX2_AND(7, 4, 5);
		पूर्ण अन्यथा अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(0, lt, 0, pg[0], bsize);

			NFT_PIPAPO_AVX2_LOAD(1, map[i_ul]);

			NFT_PIPAPO_AVX2_BUCKET_LOAD4(2, lt, 1, pg[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(3, lt, 2, pg[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(4, lt, 3, pg[3], bsize);
			NFT_PIPAPO_AVX2_AND(5, 0, 1);

			NFT_PIPAPO_AVX2_NOMATCH_GOTO(1, nothing);

			NFT_PIPAPO_AVX2_AND(6, 2, 3);
			NFT_PIPAPO_AVX2_AND(7, 4, 5);
			/* Stall */
			NFT_PIPAPO_AVX2_AND(7, 6, 7);
		पूर्ण

		/* Stall */
		NFT_PIPAPO_AVX2_NOMATCH_GOTO(7, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 7);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;
nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_4b_8() - AVX2-based lookup क्रम 8 four-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 32-bit fields (i.e. IPv4 addresses).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_4b_8(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				       काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				       स्थिर u8 *pkt, bool first, bool last)
अणु
	u8 pg[8] = अणु  pkt[0] >> 4,  pkt[0] & 0xf,  pkt[1] >> 4,  pkt[1] & 0xf,
		      pkt[2] >> 4,  pkt[2] & 0xf,  pkt[3] >> 4,  pkt[3] & 0xf,
		   पूर्ण;
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (first) अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(0,  lt, 0, pg[0], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(1,  lt, 1, pg[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(2,  lt, 2, pg[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt, 3, pg[3], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(4,  lt, 4, pg[4], bsize);
			NFT_PIPAPO_AVX2_AND(5,   0,  1);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(6,  lt, 5, pg[5], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(7,  lt, 6, pg[6], bsize);
			NFT_PIPAPO_AVX2_AND(8,   2,  3);
			NFT_PIPAPO_AVX2_AND(9,   4,  5);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(10, lt, 7, pg[7], bsize);
			NFT_PIPAPO_AVX2_AND(11,  6,  7);
			NFT_PIPAPO_AVX2_AND(12,  8,  9);
			NFT_PIPAPO_AVX2_AND(13, 10, 11);

			/* Stall */
			NFT_PIPAPO_AVX2_AND(1,  12, 13);
		पूर्ण अन्यथा अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(0,  lt, 0, pg[0], bsize);
			NFT_PIPAPO_AVX2_LOAD(1, map[i_ul]);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(2,  lt, 1, pg[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt, 2, pg[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(4,  lt, 3, pg[3], bsize);

			NFT_PIPAPO_AVX2_NOMATCH_GOTO(1, nothing);

			NFT_PIPAPO_AVX2_AND(5,   0,  1);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(6,  lt, 4, pg[4], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(7,  lt, 5, pg[5], bsize);
			NFT_PIPAPO_AVX2_AND(8,   2,  3);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(9,  lt, 6, pg[6], bsize);
			NFT_PIPAPO_AVX2_AND(10,  4,  5);
			NFT_PIPAPO_AVX2_BUCKET_LOAD4(11, lt, 7, pg[7], bsize);
			NFT_PIPAPO_AVX2_AND(12,  6,  7);
			NFT_PIPAPO_AVX2_AND(13,  8,  9);
			NFT_PIPAPO_AVX2_AND(14, 10, 11);

			/* Stall */
			NFT_PIPAPO_AVX2_AND(1,  12, 13);
			NFT_PIPAPO_AVX2_AND(1,   1, 14);
		पूर्ण

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(1, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 1);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;

nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_4b_12() - AVX2-based lookup क्रम 12 four-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 48-bit fields (i.e. MAC addresses/EUI-48).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_4b_12(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				        काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				        स्थिर u8 *pkt, bool first, bool last)
अणु
	u8 pg[12] = अणु  pkt[0] >> 4,  pkt[0] & 0xf,  pkt[1] >> 4,  pkt[1] & 0xf,
		       pkt[2] >> 4,  pkt[2] & 0xf,  pkt[3] >> 4,  pkt[3] & 0xf,
		       pkt[4] >> 4,  pkt[4] & 0xf,  pkt[5] >> 4,  pkt[5] & 0xf,
		    पूर्ण;
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (!first)
			NFT_PIPAPO_AVX2_LOAD(0, map[i_ul]);

		NFT_PIPAPO_AVX2_BUCKET_LOAD4(1,  lt,  0,  pg[0], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(2,  lt,  1,  pg[1], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt,  2,  pg[2], bsize);

		अगर (!first) अणु
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(0, nothing);
			NFT_PIPAPO_AVX2_AND(1, 1, 0);
		पूर्ण

		NFT_PIPAPO_AVX2_BUCKET_LOAD4(4,  lt,  3,  pg[3], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(5,  lt,  4,  pg[4], bsize);
		NFT_PIPAPO_AVX2_AND(6,   2,  3);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(7,  lt,  5,  pg[5], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(8,  lt,  6,  pg[6], bsize);
		NFT_PIPAPO_AVX2_AND(9,   1,  4);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(10, lt,  7,  pg[7], bsize);
		NFT_PIPAPO_AVX2_AND(11,  5,  6);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(12, lt,  8,  pg[8], bsize);
		NFT_PIPAPO_AVX2_AND(13,  7,  8);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(14, lt,  9,  pg[9], bsize);

		NFT_PIPAPO_AVX2_AND(0,   9, 10);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(1,  lt, 10,  pg[10], bsize);
		NFT_PIPAPO_AVX2_AND(2,  11, 12);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt, 11,  pg[11], bsize);
		NFT_PIPAPO_AVX2_AND(4,  13, 14);
		NFT_PIPAPO_AVX2_AND(5,   0,  1);

		NFT_PIPAPO_AVX2_AND(6,   2,  3);

		/* Stalls */
		NFT_PIPAPO_AVX2_AND(7,   4,  5);
		NFT_PIPAPO_AVX2_AND(8,   6,  7);

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(8, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 8);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;
nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_4b_32() - AVX2-based lookup क्रम 32 four-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 128-bit fields (i.e. IPv6 addresses).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_4b_32(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
					काष्ठा nft_pipapo_field *f, पूर्णांक offset,
					स्थिर u8 *pkt, bool first, bool last)
अणु
	u8 pg[32] = अणु  pkt[0] >> 4,  pkt[0] & 0xf,  pkt[1] >> 4,  pkt[1] & 0xf,
		       pkt[2] >> 4,  pkt[2] & 0xf,  pkt[3] >> 4,  pkt[3] & 0xf,
		       pkt[4] >> 4,  pkt[4] & 0xf,  pkt[5] >> 4,  pkt[5] & 0xf,
		       pkt[6] >> 4,  pkt[6] & 0xf,  pkt[7] >> 4,  pkt[7] & 0xf,
		       pkt[8] >> 4,  pkt[8] & 0xf,  pkt[9] >> 4,  pkt[9] & 0xf,
		      pkt[10] >> 4, pkt[10] & 0xf, pkt[11] >> 4, pkt[11] & 0xf,
		      pkt[12] >> 4, pkt[12] & 0xf, pkt[13] >> 4, pkt[13] & 0xf,
		      pkt[14] >> 4, pkt[14] & 0xf, pkt[15] >> 4, pkt[15] & 0xf,
		    पूर्ण;
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (!first)
			NFT_PIPAPO_AVX2_LOAD(0, map[i_ul]);

		NFT_PIPAPO_AVX2_BUCKET_LOAD4(1,  lt,  0,  pg[0], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(2,  lt,  1,  pg[1], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt,  2,  pg[2], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(4,  lt,  3,  pg[3], bsize);
		अगर (!first) अणु
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(0, nothing);
			NFT_PIPAPO_AVX2_AND(1, 1, 0);
		पूर्ण

		NFT_PIPAPO_AVX2_AND(5,   2,  3);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(6,  lt,  4,  pg[4], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(7,  lt,  5,  pg[5], bsize);
		NFT_PIPAPO_AVX2_AND(8,   1,  4);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(9,  lt,  6,  pg[6], bsize);
		NFT_PIPAPO_AVX2_AND(10,  5,  6);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(11, lt,  7,  pg[7], bsize);
		NFT_PIPAPO_AVX2_AND(12,  7,  8);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(13, lt,  8,  pg[8], bsize);
		NFT_PIPAPO_AVX2_AND(14,  9, 10);

		NFT_PIPAPO_AVX2_BUCKET_LOAD4(0,  lt,  9,  pg[9], bsize);
		NFT_PIPAPO_AVX2_AND(1,  11, 12);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(2,  lt, 10, pg[10], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt, 11, pg[11], bsize);
		NFT_PIPAPO_AVX2_AND(4,  13, 14);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(5,  lt, 12, pg[12], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(6,  lt, 13, pg[13], bsize);
		NFT_PIPAPO_AVX2_AND(7,   0,  1);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(8,  lt, 14, pg[14], bsize);
		NFT_PIPAPO_AVX2_AND(9,   2,  3);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(10, lt, 15, pg[15], bsize);
		NFT_PIPAPO_AVX2_AND(11,  4,  5);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(12, lt, 16, pg[16], bsize);
		NFT_PIPAPO_AVX2_AND(13,  6,  7);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(14, lt, 17, pg[17], bsize);

		NFT_PIPAPO_AVX2_AND(0,   8,  9);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(1,  lt, 18, pg[18], bsize);
		NFT_PIPAPO_AVX2_AND(2,  10, 11);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt, 19, pg[19], bsize);
		NFT_PIPAPO_AVX2_AND(4,  12, 13);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(5,  lt, 20, pg[20], bsize);
		NFT_PIPAPO_AVX2_AND(6,  14,  0);
		NFT_PIPAPO_AVX2_AND(7,   1,  2);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(8,  lt, 21, pg[21], bsize);
		NFT_PIPAPO_AVX2_AND(9,   3,  4);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(10, lt, 22, pg[22], bsize);
		NFT_PIPAPO_AVX2_AND(11,  5,  6);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(12, lt, 23, pg[23], bsize);
		NFT_PIPAPO_AVX2_AND(13,  7,  8);

		NFT_PIPAPO_AVX2_BUCKET_LOAD4(14, lt, 24, pg[24], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(0,  lt, 25, pg[25], bsize);
		NFT_PIPAPO_AVX2_AND(1,   9, 10);
		NFT_PIPAPO_AVX2_AND(2,  11, 12);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(3,  lt, 26, pg[26], bsize);
		NFT_PIPAPO_AVX2_AND(4,  13, 14);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(5,  lt, 27, pg[27], bsize);
		NFT_PIPAPO_AVX2_AND(6,   0,  1);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(7,  lt, 28, pg[28], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(8,  lt, 29, pg[29], bsize);
		NFT_PIPAPO_AVX2_AND(9,   2,  3);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(10, lt, 30, pg[30], bsize);
		NFT_PIPAPO_AVX2_AND(11,  4,  5);
		NFT_PIPAPO_AVX2_BUCKET_LOAD4(12, lt, 31, pg[31], bsize);

		NFT_PIPAPO_AVX2_AND(0,   6,  7);
		NFT_PIPAPO_AVX2_AND(1,   8,  9);
		NFT_PIPAPO_AVX2_AND(2,  10, 11);
		NFT_PIPAPO_AVX2_AND(3,  12,  0);

		/* Stalls */
		NFT_PIPAPO_AVX2_AND(4,   1,  2);
		NFT_PIPAPO_AVX2_AND(5,   3,  4);

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(5, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 5);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;
nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_8b_1() - AVX2-based lookup क्रम one eight-bit group
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 8-bit fields (i.e. protocol numbers).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_8b_1(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				       काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				       स्थिर u8 *pkt, bool first, bool last)
अणु
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (first) अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(2, lt, 0, pkt[0], bsize);
		पूर्ण अन्यथा अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(0, lt, 0, pkt[0], bsize);
			NFT_PIPAPO_AVX2_LOAD(1, map[i_ul]);
			NFT_PIPAPO_AVX2_AND(2, 0, 1);
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(1, nothing);
		पूर्ण

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(2, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 2);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;
nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_8b_2() - AVX2-based lookup क्रम 2 eight-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 16-bit fields (i.e. ports).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_8b_2(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				       काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				       स्थिर u8 *pkt, bool first, bool last)
अणु
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (first) अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(0, lt, 0, pkt[0], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(1, lt, 1, pkt[1], bsize);
			NFT_PIPAPO_AVX2_AND(4, 0, 1);
		पूर्ण अन्यथा अणु
			NFT_PIPAPO_AVX2_LOAD(0, map[i_ul]);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(1, lt, 0, pkt[0], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(2, lt, 1, pkt[1], bsize);

			/* Stall */
			NFT_PIPAPO_AVX2_AND(3, 0, 1);
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(0, nothing);
			NFT_PIPAPO_AVX2_AND(4, 3, 2);
		पूर्ण

		/* Stall */
		NFT_PIPAPO_AVX2_NOMATCH_GOTO(4, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 4);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;
nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_8b_4() - AVX2-based lookup क्रम 4 eight-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 32-bit fields (i.e. IPv4 addresses).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_8b_4(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				       काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				       स्थिर u8 *pkt, bool first, bool last)
अणु
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (first) अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(0,  lt, 0, pkt[0], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(1,  lt, 1, pkt[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(2,  lt, 2, pkt[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(3,  lt, 3, pkt[3], bsize);

			/* Stall */
			NFT_PIPAPO_AVX2_AND(4, 0, 1);
			NFT_PIPAPO_AVX2_AND(5, 2, 3);
			NFT_PIPAPO_AVX2_AND(0, 4, 5);
		पूर्ण अन्यथा अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(0,  lt, 0, pkt[0], bsize);
			NFT_PIPAPO_AVX2_LOAD(1, map[i_ul]);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(2,  lt, 1, pkt[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(3,  lt, 2, pkt[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(4,  lt, 3, pkt[3], bsize);

			NFT_PIPAPO_AVX2_AND(5, 0, 1);
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(1, nothing);
			NFT_PIPAPO_AVX2_AND(6, 2, 3);

			/* Stall */
			NFT_PIPAPO_AVX2_AND(7, 4, 5);
			NFT_PIPAPO_AVX2_AND(0, 6, 7);
		पूर्ण

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(0, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 0);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;

nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_8b_6() - AVX2-based lookup क्रम 6 eight-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 48-bit fields (i.e. MAC addresses/EUI-48).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_8b_6(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
				       काष्ठा nft_pipapo_field *f, पूर्णांक offset,
				       स्थिर u8 *pkt, bool first, bool last)
अणु
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (first) अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(0,  lt, 0, pkt[0], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(1,  lt, 1, pkt[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(2,  lt, 2, pkt[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(3,  lt, 3, pkt[3], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(4,  lt, 4, pkt[4], bsize);

			NFT_PIPAPO_AVX2_AND(5, 0, 1);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(6,  lt, 6, pkt[5], bsize);
			NFT_PIPAPO_AVX2_AND(7, 2, 3);

			/* Stall */
			NFT_PIPAPO_AVX2_AND(0, 4, 5);
			NFT_PIPAPO_AVX2_AND(1, 6, 7);
			NFT_PIPAPO_AVX2_AND(4, 0, 1);
		पूर्ण अन्यथा अणु
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(0,  lt, 0, pkt[0], bsize);
			NFT_PIPAPO_AVX2_LOAD(1, map[i_ul]);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(2,  lt, 1, pkt[1], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(3,  lt, 2, pkt[2], bsize);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(4,  lt, 3, pkt[3], bsize);

			NFT_PIPAPO_AVX2_AND(5, 0, 1);
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(1, nothing);

			NFT_PIPAPO_AVX2_AND(6, 2, 3);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(7,  lt, 4, pkt[4], bsize);
			NFT_PIPAPO_AVX2_AND(0, 4, 5);
			NFT_PIPAPO_AVX2_BUCKET_LOAD8(1,  lt, 5, pkt[5], bsize);
			NFT_PIPAPO_AVX2_AND(2, 6, 7);

			/* Stall */
			NFT_PIPAPO_AVX2_AND(3, 0, 1);
			NFT_PIPAPO_AVX2_AND(4, 2, 3);
		पूर्ण

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(4, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 4);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;

nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_8b_16() - AVX2-based lookup क्रम 16 eight-bit groups
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * See nft_pipapo_avx2_lookup_4b_2().
 *
 * This is used क्रम 128-bit fields (i.e. IPv6 addresses).
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_8b_16(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
					काष्ठा nft_pipapo_field *f, पूर्णांक offset,
					स्थिर u8 *pkt, bool first, bool last)
अणु
	पूर्णांक i, ret = -1, m256_size = f->bsize / NFT_PIPAPO_LONGS_PER_M256, b;
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;
	क्रम (i = offset; i < m256_size; i++, lt += NFT_PIPAPO_LONGS_PER_M256) अणु
		पूर्णांक i_ul = i * NFT_PIPAPO_LONGS_PER_M256;

		अगर (!first)
			NFT_PIPAPO_AVX2_LOAD(0, map[i_ul]);

		NFT_PIPAPO_AVX2_BUCKET_LOAD8(1, lt,  0,  pkt[0], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(2, lt,  1,  pkt[1], bsize);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(3, lt,  2,  pkt[2], bsize);
		अगर (!first) अणु
			NFT_PIPAPO_AVX2_NOMATCH_GOTO(0, nothing);
			NFT_PIPAPO_AVX2_AND(1, 1, 0);
		पूर्ण
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(4, lt,  3,  pkt[3], bsize);

		NFT_PIPAPO_AVX2_BUCKET_LOAD8(5, lt,  4,  pkt[4], bsize);
		NFT_PIPAPO_AVX2_AND(6, 1, 2);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(7, lt,  5,  pkt[5], bsize);
		NFT_PIPAPO_AVX2_AND(0, 3, 4);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(1, lt,  6,  pkt[6], bsize);

		NFT_PIPAPO_AVX2_BUCKET_LOAD8(2, lt,  7,  pkt[7], bsize);
		NFT_PIPAPO_AVX2_AND(3, 5, 6);
		NFT_PIPAPO_AVX2_AND(4, 0, 1);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(5, lt,  8,  pkt[8], bsize);

		NFT_PIPAPO_AVX2_AND(6, 2, 3);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(7, lt,  9,  pkt[9], bsize);
		NFT_PIPAPO_AVX2_AND(0, 4, 5);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(1, lt, 10, pkt[10], bsize);
		NFT_PIPAPO_AVX2_AND(2, 6, 7);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(3, lt, 11, pkt[11], bsize);
		NFT_PIPAPO_AVX2_AND(4, 0, 1);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(5, lt, 12, pkt[12], bsize);
		NFT_PIPAPO_AVX2_AND(6, 2, 3);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(7, lt, 13, pkt[13], bsize);
		NFT_PIPAPO_AVX2_AND(0, 4, 5);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(1, lt, 14, pkt[14], bsize);
		NFT_PIPAPO_AVX2_AND(2, 6, 7);
		NFT_PIPAPO_AVX2_BUCKET_LOAD8(3, lt, 15, pkt[15], bsize);
		NFT_PIPAPO_AVX2_AND(4, 0, 1);

		/* Stall */
		NFT_PIPAPO_AVX2_AND(5, 2, 3);
		NFT_PIPAPO_AVX2_AND(6, 4, 5);

		NFT_PIPAPO_AVX2_NOMATCH_GOTO(6, nomatch);
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 6);

		b = nft_pipapo_avx2_refill(i_ul, &map[i_ul], fill, f->mt, last);
		अगर (last)
			वापस b;

		अगर (unlikely(ret == -1))
			ret = b / XSAVE_YMM_SIZE;

		जारी;

nomatch:
		NFT_PIPAPO_AVX2_STORE(map[i_ul], 15);
nothing:
		;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_lookup_slow() - Fallback function क्रम uncommon field sizes
 * @map:	Previous match result, used as initial biपंचांगap
 * @fill:	Destination biपंचांगap to be filled with current match result
 * @f:		Field, containing lookup and mapping tables
 * @offset:	Ignore buckets beक्रमe the given index, no bits are filled there
 * @pkt:	Packet data, poपूर्णांकer to input nftables रेजिस्टर
 * @first:	If this is the first field, करोn't source previous result
 * @last:	Last field: stop at the first match and वापस bit index
 *
 * This function should never be called, but is provided क्रम the हाल the field
 * size करोesn't match any of the known data types. Matching rate is
 * substantially lower than AVX2 routines.
 *
 * Return: -1 on no match, rule index of match अगर @last, otherwise first दीर्घ
 * word index to be checked next (i.e. first filled word).
 */
अटल पूर्णांक nft_pipapo_avx2_lookup_slow(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ *fill,
					काष्ठा nft_pipapo_field *f, पूर्णांक offset,
					स्थिर u8 *pkt, bool first, bool last)
अणु
	अचिन्हित दीर्घ *lt = f->lt, bsize = f->bsize;
	पूर्णांक i, ret = -1, b;

	lt += offset * NFT_PIPAPO_LONGS_PER_M256;

	अगर (first)
		स_रखो(map, 0xff, bsize * माप(*map));

	क्रम (i = offset; i < bsize; i++) अणु
		अगर (f->bb == 8)
			pipapo_and_field_buckets_8bit(f, map, pkt);
		अन्यथा
			pipapo_and_field_buckets_4bit(f, map, pkt);
		NFT_PIPAPO_GROUP_BITS_ARE_8_OR_4;

		b = pipapo_refill(map, bsize, f->rules, fill, f->mt, last);

		अगर (last)
			वापस b;

		अगर (ret == -1)
			ret = b / XSAVE_YMM_SIZE;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_avx2_estimate() - Set size, space and lookup complनिकासy
 * @desc:	Set description, element count and field description used
 * @features:	Flags: NFT_SET_INTERVAL needs to be there
 * @est:	Storage क्रम estimation data
 *
 * Return: true अगर set is compatible and AVX2 available, false otherwise.
 */
bool nft_pipapo_avx2_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
			      काष्ठा nft_set_estimate *est)
अणु
	अगर (!(features & NFT_SET_INTERVAL) ||
	    desc->field_count < NFT_PIPAPO_MIN_FIELDS)
		वापस false;

	अगर (!boot_cpu_has(X86_FEATURE_AVX2) || !boot_cpu_has(X86_FEATURE_AVX))
		वापस false;

	est->size = pipapo_estimate_size(desc);
	अगर (!est->size)
		वापस false;

	est->lookup = NFT_SET_CLASS_O_LOG_N;

	est->space = NFT_SET_CLASS_O_N;

	वापस true;
पूर्ण

/**
 * nft_pipapo_avx2_lookup() - Lookup function क्रम AVX2 implementation
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @elem:	nftables API element representation containing key data
 * @ext:	nftables API extension poपूर्णांकer, filled with matching reference
 *
 * For more details, see DOC: Theory of Operation in nft_set_pipapo.c.
 *
 * This implementation exploits the repetitive अक्षरacteristic of the algorithm
 * to provide a fast, vectorised version using the AVX2 SIMD inकाष्ठाion set.
 *
 * Return: true on match, false otherwise.
 */
bool nft_pipapo_avx2_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			    स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	अचिन्हित दीर्घ *res, *fill, *scratch;
	u8 genmask = nft_genmask_cur(net);
	स्थिर u8 *rp = (स्थिर u8 *)key;
	काष्ठा nft_pipapo_match *m;
	काष्ठा nft_pipapo_field *f;
	bool map_index;
	पूर्णांक i, ret = 0;

	अगर (unlikely(!irq_fpu_usable()))
		वापस nft_pipapo_lookup(net, set, key, ext);

	m = rcu_dereference(priv->match);

	/* This also protects access to all data related to scratch maps */
	kernel_fpu_begin();

	scratch = *raw_cpu_ptr(m->scratch_aligned);
	अगर (unlikely(!scratch)) अणु
		kernel_fpu_end();
		वापस false;
	पूर्ण
	map_index = raw_cpu_पढ़ो(nft_pipapo_avx2_scratch_index);

	res  = scratch + (map_index ? m->bsize_max : 0);
	fill = scratch + (map_index ? 0 : m->bsize_max);

	/* Starting map करोesn't need to be set क्रम this implementation */

	nft_pipapo_avx2_prepare();

next_match:
	nft_pipapo_क्रम_each_field(f, i, m) अणु
		bool last = i == m->field_count - 1, first = !i;

#घोषणा NFT_SET_PIPAPO_AVX2_LOOKUP(b, n)				\
		(ret = nft_pipapo_avx2_lookup_##b##b_##n(res, fill, f,	\
							 ret, rp,	\
							 first, last))

		अगर (likely(f->bb == 8)) अणु
			अगर (f->groups == 1) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(8, 1);
			पूर्ण अन्यथा अगर (f->groups == 2) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(8, 2);
			पूर्ण अन्यथा अगर (f->groups == 4) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(8, 4);
			पूर्ण अन्यथा अगर (f->groups == 6) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(8, 6);
			पूर्ण अन्यथा अगर (f->groups == 16) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(8, 16);
			पूर्ण अन्यथा अणु
				ret = nft_pipapo_avx2_lookup_slow(res, fill, f,
								  ret, rp,
								  first, last);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (f->groups == 2) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(4, 2);
			पूर्ण अन्यथा अगर (f->groups == 4) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(4, 4);
			पूर्ण अन्यथा अगर (f->groups == 8) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(4, 8);
			पूर्ण अन्यथा अगर (f->groups == 12) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(4, 12);
			पूर्ण अन्यथा अगर (f->groups == 32) अणु
				NFT_SET_PIPAPO_AVX2_LOOKUP(4, 32);
			पूर्ण अन्यथा अणु
				ret = nft_pipapo_avx2_lookup_slow(res, fill, f,
								  ret, rp,
								  first, last);
			पूर्ण
		पूर्ण
		NFT_PIPAPO_GROUP_BITS_ARE_8_OR_4;

#अघोषित NFT_SET_PIPAPO_AVX2_LOOKUP

		अगर (ret < 0)
			जाओ out;

		अगर (last) अणु
			*ext = &f->mt[ret].e->ext;
			अगर (unlikely(nft_set_elem_expired(*ext) ||
				     !nft_set_elem_active(*ext, genmask))) अणु
				ret = 0;
				जाओ next_match;
			पूर्ण

			जाओ out;
		पूर्ण

		swap(res, fill);
		rp += NFT_PIPAPO_GROUPS_PADDED_SIZE(f);
	पूर्ण

out:
	अगर (i % 2)
		raw_cpu_ग_लिखो(nft_pipapo_avx2_scratch_index, !map_index);
	kernel_fpu_end();

	वापस ret >= 0;
पूर्ण
