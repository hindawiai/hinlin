<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
-*- linux-c -*-
   drbd_receiver.c
   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.

 */

#अगर_अघोषित _DRBD_VLI_H
#घोषणा _DRBD_VLI_H

/*
 * At a granularity of 4KiB storage represented per bit,
 * and stroage sizes of several TiB,
 * and possibly small-bandwidth replication,
 * the biपंचांगap transfer समय can take much too दीर्घ,
 * अगर transmitted in plain text.
 *
 * We try to reduce the transferred biपंचांगap inक्रमmation
 * by encoding runlengths of bit polarity.
 *
 * We never actually need to encode a "zero" (runlengths are positive).
 * But then we have to store the value of the first bit.
 * The first bit of inक्रमmation thus shall encode अगर the first runlength
 * gives the number of set or unset bits.
 *
 * We assume that large areas are either completely set or unset,
 * which gives good compression with any runlength method,
 * even when encoding the runlength as fixed size 32bit/64bit पूर्णांकegers.
 *
 * Still, there may be areas where the polarity flips every few bits,
 * and encoding the runlength sequence of those areas with fix size
 * पूर्णांकegers would be much worse than plaपूर्णांकext.
 *
 * We want to encode small runlength values with minimum code length,
 * जबतक still being able to encode a Huge run of all zeros.
 *
 * Thus we need a Variable Length Integer encoding, VLI.
 *
 * For some हालs, we produce more code bits than plaपूर्णांकext input.
 * We need to send incompressible chunks as plaपूर्णांकext, skip over them
 * and then see अगर the next chunk compresses better.
 *
 * We करोn't care too much about "excellent" compression ratio क्रम large
 * runlengths (all set/all clear): whether we achieve a factor of 100
 * or 1000 is not that much of an issue.
 * We करो not want to waste too much on लघु runlengths in the "noisy"
 * parts of the biपंचांगap, though.
 *
 * There are endless variants of VLI, we experimented with:
 *  * simple byte-based
 *  * various bit based with dअगरferent code word length.
 *
 * To aव्योम yet an other configuration parameter (choice of biपंचांगap compression
 * algorithm) which was dअगरficult to explain and tune, we just chose the one
 * variant that turned out best in all test हालs.
 * Based on real world usage patterns, with device sizes ranging from a few GiB
 * to several TiB, file server/mailserver/webserver/mysql/postgress,
 * mostly idle to really busy, the all समय winner (though someबार only
 * marginally better) is:
 */

/*
 * encoding is "visualised" as
 * __little endian__ bitstream, least signअगरicant bit first (left most)
 *
 * this particular encoding is chosen so that the prefix code
 * starts as unary encoding the level, then modअगरied so that
 * 10 levels can be described in 8bit, with minimal overhead
 * क्रम the smaller levels.
 *
 * Number of data bits follow fibonacci sequence, with the exception of the
 * last level (+1 data bit, so it makes 64bit total).  The only worse code when
 * encoding bit polarity runlength is 1 plain bits => 2 code bits.
prefix    data bits                                    max val  Nतज data bits
0 x                                                         0x2            1
10 x                                                        0x4            1
110 xx                                                      0x8            2
1110 xxx                                                   0x10            3
11110 xxx xx                                               0x30            5
111110 xx xxxxxx                                          0x130            8
11111100  xxxxxxxx xxxxx                                 0x2130           13
11111110  xxxxxxxx xxxxxxxx xxxxx                      0x202130           21
11111101  xxxxxxxx xxxxxxxx xxxxxxxx  xxxxxxxx xx   0x400202130           34
11111111  xxxxxxxx xxxxxxxx xxxxxxxx  xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx 56
 * maximum encodable value: 0x100000400202130 == 2**56 + some */

/* compression "table":
 transmitted   x                                0.29
 as plaपूर्णांकext x                                  ........................
             x                                   ........................
            x                                    ........................
           x    0.59                         0.21........................
          x      ........................................................
         x       .. c ...................................................
        x    0.44.. o ...................................................
       x .......... d ...................................................
      x  .......... e ...................................................
     X.............   ...................................................
    x.............. b ...................................................
2.0x............... i ...................................................
 #X................ t ...................................................
 #................. s ...........................  plain bits  ..........
-+-----------------------------------------------------------------------
 1             16              32                              64
*/

/* LEVEL: (total bits, prefix bits, prefix value),
 * sorted ascending by number of total bits.
 * The rest of the code table is calculated at compileसमय from this. */

/* fibonacci data 1, 1, ... */
#घोषणा VLI_L_1_1() करो अणु \
	LEVEL( 2, 1, 0x00); \
	LEVEL( 3, 2, 0x01); \
	LEVEL( 5, 3, 0x03); \
	LEVEL( 7, 4, 0x07); \
	LEVEL(10, 5, 0x0f); \
	LEVEL(14, 6, 0x1f); \
	LEVEL(21, 8, 0x3f); \
	LEVEL(29, 8, 0x7f); \
	LEVEL(42, 8, 0xbf); \
	LEVEL(64, 8, 0xff); \
	पूर्ण जबतक (0)

/* finds a suitable level to decode the least signअगरicant part of in.
 * वापसs number of bits consumed.
 *
 * BUG() क्रम bad input, as that would mean a buggy code table. */
अटल अंतरभूत पूर्णांक vli_decode_bits(u64 *out, स्थिर u64 in)
अणु
	u64 adj = 1;

#घोषणा LEVEL(t,b,v)					\
	करो अणु						\
		अगर ((in & ((1 << b) -1)) == v) अणु	\
			*out = ((in & ((~0ULL) >> (64-t))) >> b) + adj;	\
			वापस t;			\
		पूर्ण					\
		adj += 1ULL << (t - b);			\
	पूर्ण जबतक (0)

	VLI_L_1_1();

	/* NOT REACHED, अगर VLI_LEVELS code table is defined properly */
	BUG();
#अघोषित LEVEL
पूर्ण

/* वापस number of code bits needed,
 * or negative error number */
अटल अंतरभूत पूर्णांक __vli_encode_bits(u64 *out, स्थिर u64 in)
अणु
	u64 max = 0;
	u64 adj = 1;

	अगर (in == 0)
		वापस -EINVAL;

#घोषणा LEVEL(t,b,v) करो अणु		\
		max += 1ULL << (t - b);	\
		अगर (in <= max) अणु	\
			अगर (out)	\
				*out = ((in - adj) << b) | v;	\
			वापस t;	\
		पूर्ण			\
		adj = max + 1;		\
	पूर्ण जबतक (0)

	VLI_L_1_1();

	वापस -EOVERFLOW;
#अघोषित LEVEL
पूर्ण

#अघोषित VLI_L_1_1

/* code from here करोwn is independend of actually used bit code */

/*
 * Code length is determined by some unique (e.g. unary) prefix.
 * This encodes arbitrary bit length, not whole bytes: we have a bit-stream,
 * not a byte stream.
 */

/* क्रम the bitstream, we need a cursor */
काष्ठा bitstream_cursor अणु
	/* the current byte */
	u8 *b;
	/* the current bit within *b, nomalized: 0..7 */
	अचिन्हित पूर्णांक bit;
पूर्ण;

/* initialize cursor to poपूर्णांक to first bit of stream */
अटल अंतरभूत व्योम bitstream_cursor_reset(काष्ठा bitstream_cursor *cur, व्योम *s)
अणु
	cur->b = s;
	cur->bit = 0;
पूर्ण

/* advance cursor by that many bits; maximum expected input value: 64,
 * but depending on VLI implementation, it may be more. */
अटल अंतरभूत व्योम bitstream_cursor_advance(काष्ठा bitstream_cursor *cur, अचिन्हित पूर्णांक bits)
अणु
	bits += cur->bit;
	cur->b = cur->b + (bits >> 3);
	cur->bit = bits & 7;
पूर्ण

/* the bitstream itself knows its length */
काष्ठा bitstream अणु
	काष्ठा bitstream_cursor cur;
	अचिन्हित अक्षर *buf;
	माप_प्रकार buf_len;		/* in bytes */

	/* क्रम input stream:
	 * number of trailing 0 bits क्रम padding
	 * total number of valid bits in stream: buf_len * 8 - pad_bits */
	अचिन्हित पूर्णांक pad_bits;
पूर्ण;

अटल अंतरभूत व्योम bitstream_init(काष्ठा bitstream *bs, व्योम *s, माप_प्रकार len, अचिन्हित पूर्णांक pad_bits)
अणु
	bs->buf = s;
	bs->buf_len = len;
	bs->pad_bits = pad_bits;
	bitstream_cursor_reset(&bs->cur, bs->buf);
पूर्ण

अटल अंतरभूत व्योम bitstream_शुरुआत(काष्ठा bitstream *bs)
अणु
	bitstream_cursor_reset(&bs->cur, bs->buf);
	स_रखो(bs->buf, 0, bs->buf_len);
पूर्ण

/* Put (at most 64) least signअगरicant bits of val पूर्णांकo bitstream, and advance cursor.
 * Ignores "pad_bits".
 * Returns zero अगर bits == 0 (nothing to करो).
 * Returns number of bits used अगर successful.
 *
 * If there is not enough room left in bitstream,
 * leaves bitstream unchanged and वापसs -ENOBUFS.
 */
अटल अंतरभूत पूर्णांक bitstream_put_bits(काष्ठा bitstream *bs, u64 val, स्थिर अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित अक्षर *b = bs->cur.b;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (bits == 0)
		वापस 0;

	अगर ((bs->cur.b + ((bs->cur.bit + bits -1) >> 3)) - bs->buf >= bs->buf_len)
		वापस -ENOBUFS;

	/* paranoia: strip off hi bits; they should not be set anyways. */
	अगर (bits < 64)
		val &= ~0ULL >> (64 - bits);

	*b++ |= (val & 0xff) << bs->cur.bit;

	क्रम (पंचांगp = 8 - bs->cur.bit; पंचांगp < bits; पंचांगp += 8)
		*b++ |= (val >> पंचांगp) & 0xff;

	bitstream_cursor_advance(&bs->cur, bits);
	वापस bits;
पूर्ण

/* Fetch (at most 64) bits from bitstream पूर्णांकo *out, and advance cursor.
 *
 * If more than 64 bits are requested, वापसs -EINVAL and leave *out unchanged.
 *
 * If there are less than the requested number of valid bits left in the
 * bitstream, still fetches all available bits.
 *
 * Returns number of actually fetched bits.
 */
अटल अंतरभूत पूर्णांक bitstream_get_bits(काष्ठा bitstream *bs, u64 *out, पूर्णांक bits)
अणु
	u64 val;
	अचिन्हित पूर्णांक n;

	अगर (bits > 64)
		वापस -EINVAL;

	अगर (bs->cur.b + ((bs->cur.bit + bs->pad_bits + bits -1) >> 3) - bs->buf >= bs->buf_len)
		bits = ((bs->buf_len - (bs->cur.b - bs->buf)) << 3)
			- bs->cur.bit - bs->pad_bits;

	अगर (bits == 0) अणु
		*out = 0;
		वापस 0;
	पूर्ण

	/* get the high bits */
	val = 0;
	n = (bs->cur.bit + bits + 7) >> 3;
	/* n may be at most 9, अगर cur.bit + bits > 64 */
	/* which means this copies at most 8 byte */
	अगर (n) अणु
		स_नकल(&val, bs->cur.b+1, n - 1);
		val = le64_to_cpu(val) << (8 - bs->cur.bit);
	पूर्ण

	/* we still need the low bits */
	val |= bs->cur.b[0] >> bs->cur.bit;

	/* and mask out bits we करोn't want */
	val &= ~0ULL >> (64 - bits);

	bitstream_cursor_advance(&bs->cur, bits);
	*out = val;

	वापस bits;
पूर्ण

/* encodes @in as vli पूर्णांकo @bs;

 * वापस values
 *  > 0: number of bits successfully stored in bitstream
 * -ENOBUFS @bs is full
 * -EINVAL input zero (invalid)
 * -EOVERFLOW input too large क्रम this vli code (invalid)
 */
अटल अंतरभूत पूर्णांक vli_encode_bits(काष्ठा bitstream *bs, u64 in)
अणु
	u64 code = code;
	पूर्णांक bits = __vli_encode_bits(&code, in);

	अगर (bits <= 0)
		वापस bits;

	वापस bitstream_put_bits(bs, code, bits);
पूर्ण

#पूर्ण_अगर
