<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Linux driver क्रम Philips webcam
   Decompression क्रम chipset version 2 et 3
   (C) 2004-2006  Luc Saillard (luc@saillard.org)

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.


*/

#समावेश "pwc-timon.h"
#समावेश "pwc-kiara.h"
#समावेश "pwc-dec23.h"

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

/*
 * USE_LOOKUP_TABLE_TO_CLAMP
 *   0: use a C version of this tests:  अणु  a<0?0:(a>255?255:a) पूर्ण
 *   1: use a faster lookup table क्रम cpu with a big cache (पूर्णांकel)
 */
#घोषणा USE_LOOKUP_TABLE_TO_CLAMP	1
/*
 * UNROLL_LOOP_FOR_COPYING_BLOCK
 *   0: use a loop क्रम a smaller code (but little slower)
 *   1: when unrolling the loop, gcc produces some faster code (perhaps only
 *   valid क्रम पूर्णांकel processor class). Activating this option, स्वतःmatically
 *   activate USE_LOOKUP_TABLE_TO_CLAMP
 */
#घोषणा UNROLL_LOOP_FOR_COPY		1
#अगर UNROLL_LOOP_FOR_COPY
# undef USE_LOOKUP_TABLE_TO_CLAMP
# define USE_LOOKUP_TABLE_TO_CLAMP 1
#पूर्ण_अगर

अटल व्योम build_subblock_pattern(काष्ठा pwc_dec23_निजी *pdec)
अणु
	अटल स्थिर अचिन्हित पूर्णांक initial_values[12] = अणु
		-0x526500, -0x221200, 0x221200, 0x526500,
			   -0x3de200, 0x3de200,
		-0x6db480, -0x2d5d00, 0x2d5d00, 0x6db480,
			   -0x12c200, 0x12c200

	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक values_derivated[12] = अणु
		0xa4ca, 0x4424, -0x4424, -0xa4ca,
			0x7bc4, -0x7bc4,
		0xdb69, 0x5aba, -0x5aba, -0xdb69,
			0x2584, -0x2584
	पूर्ण;
	अचिन्हित पूर्णांक temp_values[12];
	पूर्णांक i, j;

	स_नकल(temp_values, initial_values, माप(initial_values));
	क्रम (i = 0; i < 256; i++) अणु
		क्रम (j = 0; j < 12; j++) अणु
			pdec->table_subblock[i][j] = temp_values[j];
			temp_values[j] += values_derivated[j];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम build_bit_घातermask_table(काष्ठा pwc_dec23_निजी *pdec)
अणु
	अचिन्हित अक्षर *p;
	अचिन्हित पूर्णांक bit, byte, mask, val;
	अचिन्हित पूर्णांक bitघातer = 1;

	क्रम (bit = 0; bit < 8; bit++) अणु
		mask = bitघातer - 1;
		p = pdec->table_bitघातermask[bit];
		क्रम (byte = 0; byte < 256; byte++) अणु
			val = (byte & mask);
			अगर (byte & bitघातer)
				val = -val;
			*p++ = val;
		पूर्ण
		bitघातer<<=1;
	पूर्ण
पूर्ण


अटल व्योम build_table_color(स्थिर अचिन्हित पूर्णांक romtable[16][8],
			      अचिन्हित अक्षर p0004[16][1024],
			      अचिन्हित अक्षर p8004[16][256])
अणु
	पूर्णांक compression_mode, j, k, bit, pw;
	अचिन्हित अक्षर *p0, *p8;
	स्थिर अचिन्हित पूर्णांक *r;

	/* We have 16 compressions tables */
	क्रम (compression_mode = 0; compression_mode < 16; compression_mode++) अणु
		p0 = p0004[compression_mode];
		p8 = p8004[compression_mode];
		r  = romtable[compression_mode];

		क्रम (j = 0; j < 8; j++, r++, p0 += 128) अणु

			क्रम (k = 0; k < 16; k++) अणु
				अगर (k == 0)
					bit = 1;
				अन्यथा अगर (k >= 1 && k < 3)
					bit = (r[0] >> 15) & 7;
				अन्यथा अगर (k >= 3 && k < 6)
					bit = (r[0] >> 12) & 7;
				अन्यथा अगर (k >= 6 && k < 10)
					bit = (r[0] >> 9) & 7;
				अन्यथा अगर (k >= 10 && k < 13)
					bit = (r[0] >> 6) & 7;
				अन्यथा अगर (k >= 13 && k < 15)
					bit = (r[0] >> 3) & 7;
				अन्यथा
					bit = (r[0]) & 7;
				अगर (k == 0)
					*p8++ = 8;
				अन्यथा
					*p8++ = j - bit;
				*p8++ = bit;

				pw = 1 << bit;
				p0[k + 0x00] = (1 * pw) + 0x80;
				p0[k + 0x10] = (2 * pw) + 0x80;
				p0[k + 0x20] = (3 * pw) + 0x80;
				p0[k + 0x30] = (4 * pw) + 0x80;
				p0[k + 0x40] = (-1 * pw) + 0x80;
				p0[k + 0x50] = (-2 * pw) + 0x80;
				p0[k + 0x60] = (-3 * pw) + 0x80;
				p0[k + 0x70] = (-4 * pw) + 0x80;
			पूर्ण	/* end of क्रम (k=0; k<16; k++, p8++) */
		पूर्ण	/* end of क्रम (j=0; j<8; j++ , table++) */
	पूर्ण /* end of क्रमeach compression_mode */
पूर्ण

/*
 *
 */
अटल व्योम fill_table_dc00_d800(काष्ठा pwc_dec23_निजी *pdec)
अणु
#घोषणा SCALEBITS 15
#घोषणा ONE_HALF  (1UL << (SCALEBITS - 1))
	पूर्णांक i;
	अचिन्हित पूर्णांक offset1 = ONE_HALF;
	अचिन्हित पूर्णांक offset2 = 0x0000;

	क्रम (i=0; i<256; i++) अणु
		pdec->table_dc00[i] = offset1 & ~(ONE_HALF);
		pdec->table_d800[i] = offset2;

		offset1 += 0x7bc4;
		offset2 += 0x7bc4;
	पूर्ण
पूर्ण

/*
 * To decode the stream:
 *   अगर look_bits(2) == 0:	# op == 2 in the lookup table
 *      skip_bits(2)
 *      end of the stream
 *   elअगर look_bits(3) == 7:	# op == 1 in the lookup table
 *      skip_bits(3)
 *      yyyy = get_bits(4)
 *      xxxx = get_bits(8)
 *   अन्यथा:			# op == 0 in the lookup table
 *      skip_bits(x)
 *
 * For speedup processing, we build a lookup table and we takes the first 6 bits.
 *
 * काष्ठा अणु
 *   अचिन्हित अक्षर op;	    // operation to execute
 *   अचिन्हित अक्षर bits;    // bits use to perक्रमm operation
 *   अचिन्हित अक्षर offset1; // offset to add to access in the table_0004 % 16
 *   अचिन्हित अक्षर offset2; // offset to add to access in the table_0004
 * पूर्ण
 *
 * How to build this table ?
 *   op == 2 when (i%4)==0
 *   op == 1 when (i%8)==7
 *   op == 0 otherwise
 *
 */
अटल स्थिर अचिन्हित अक्षर hash_table_ops[64*4] = अणु
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x01, 0x30,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x20,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x00,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x02, 0x10,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x60,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x40,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x40,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x01, 0x70,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x20,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x00,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x02, 0x50,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x60,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x40,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x40,
	0x01, 0x00, 0x00, 0x00
पूर्ण;

/*
 *
 */
अटल स्थिर अचिन्हित पूर्णांक MulIdx[16][16] = अणु
	अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,पूर्ण,
	अणु0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,पूर्ण,
	अणु0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,पूर्ण,
	अणु4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4,पूर्ण,
	अणु6, 7, 8, 9, 7, 10, 11, 8, 8, 11, 10, 7, 9, 8, 7, 6,पूर्ण,
	अणु4, 5, 5, 4, 4, 5, 5, 4, 4, 5, 5, 4, 4, 5, 5, 4,पूर्ण,
	अणु1, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2,पूर्ण,
	अणु0, 3, 3, 0, 1, 2, 2, 1, 2, 1, 1, 2, 3, 0, 0, 3,पूर्ण,
	अणु0, 1, 2, 3, 3, 2, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3,पूर्ण,
	अणु1, 1, 1, 1, 3, 3, 3, 3, 0, 0, 0, 0, 2, 2, 2, 2,पूर्ण,
	अणु7, 10, 11, 8, 9, 8, 7, 6, 6, 7, 8, 9, 8, 11, 10, 7,पूर्ण,
	अणु4, 5, 5, 4, 5, 4, 4, 5, 5, 4, 4, 5, 4, 5, 5, 4,पूर्ण,
	अणु7, 9, 6, 8, 10, 8, 7, 11, 11, 7, 8, 10, 8, 6, 9, 7,पूर्ण,
	अणु1, 3, 0, 2, 2, 0, 3, 1, 2, 0, 3, 1, 1, 3, 0, 2,पूर्ण,
	अणु1, 2, 2, 1, 3, 0, 0, 3, 0, 3, 3, 0, 2, 1, 1, 2,पूर्ण,
	अणु10, 8, 7, 11, 8, 6, 9, 7, 7, 9, 6, 8, 11, 7, 8, 10पूर्ण
पूर्ण;

#अगर USE_LOOKUP_TABLE_TO_CLAMP
#घोषणा MAX_OUTER_CROP_VALUE	(512)
अटल अचिन्हित अक्षर pwc_crop_table[256 + 2*MAX_OUTER_CROP_VALUE];
#घोषणा CLAMP(x) (pwc_crop_table[MAX_OUTER_CROP_VALUE+(x)])
#अन्यथा
#घोषणा CLAMP(x) ((x)>255?255:((x)<0?0:x))
#पूर्ण_अगर


/* If the type or the command change, we rebuild the lookup table */
व्योम pwc_dec23_init(काष्ठा pwc_device *pdev, स्थिर अचिन्हित अक्षर *cmd)
अणु
	पूर्णांक flags, version, shअगरt, i;
	काष्ठा pwc_dec23_निजी *pdec = &pdev->dec23;

	mutex_init(&pdec->lock);

	अगर (pdec->last_cmd_valid && pdec->last_cmd == cmd[2])
		वापस;

	अगर (DEVICE_USE_CODEC3(pdev->type)) अणु
		flags = cmd[2] & 0x18;
		अगर (flags == 8)
			pdec->nbits = 7;	/* More bits, mean more bits to encode the stream, but better quality */
		अन्यथा अगर (flags == 0x10)
			pdec->nbits = 8;
		अन्यथा
			pdec->nbits = 6;

		version = cmd[2] >> 5;
		build_table_color(KiaraRomTable[version][0], pdec->table_0004_pass1, pdec->table_8004_pass1);
		build_table_color(KiaraRomTable[version][1], pdec->table_0004_pass2, pdec->table_8004_pass2);

	पूर्ण अन्यथा अणु

		flags = cmd[2] & 6;
		अगर (flags == 2)
			pdec->nbits = 7;
		अन्यथा अगर (flags == 4)
			pdec->nbits = 8;
		अन्यथा
			pdec->nbits = 6;

		version = cmd[2] >> 3;
		build_table_color(TimonRomTable[version][0], pdec->table_0004_pass1, pdec->table_8004_pass1);
		build_table_color(TimonRomTable[version][1], pdec->table_0004_pass2, pdec->table_8004_pass2);
	पूर्ण

	/* Inक्रमmation can be coded on a variable number of bits but never less than 8 */
	shअगरt = 8 - pdec->nbits;
	pdec->scalebits = SCALEBITS - shअगरt;
	pdec->nbitsmask = 0xFF >> shअगरt;

	fill_table_dc00_d800(pdec);
	build_subblock_pattern(pdec);
	build_bit_घातermask_table(pdec);

#अगर USE_LOOKUP_TABLE_TO_CLAMP
	/* Build the अटल table to clamp value [0-255] */
	क्रम (i=0;i<MAX_OUTER_CROP_VALUE;i++)
		pwc_crop_table[i] = 0;
	क्रम (i=0; i<256; i++)
		pwc_crop_table[MAX_OUTER_CROP_VALUE+i] = i;
	क्रम (i=0; i<MAX_OUTER_CROP_VALUE; i++)
		pwc_crop_table[MAX_OUTER_CROP_VALUE+256+i] = 255;
#पूर्ण_अगर

	pdec->last_cmd = cmd[2];
	pdec->last_cmd_valid = 1;
पूर्ण

/*
 * Copy the 4x4 image block to Y plane buffer
 */
अटल व्योम copy_image_block_Y(स्थिर पूर्णांक *src, अचिन्हित अक्षर *dst, अचिन्हित पूर्णांक bytes_per_line, अचिन्हित पूर्णांक scalebits)
अणु
#अगर UNROLL_LOOP_FOR_COPY
	स्थिर अचिन्हित अक्षर *cm = pwc_crop_table+MAX_OUTER_CROP_VALUE;
	स्थिर पूर्णांक *c = src;
	अचिन्हित अक्षर *d = dst;

	*d++ = cm[c[0] >> scalebits];
	*d++ = cm[c[1] >> scalebits];
	*d++ = cm[c[2] >> scalebits];
	*d++ = cm[c[3] >> scalebits];

	d = dst + bytes_per_line;
	*d++ = cm[c[4] >> scalebits];
	*d++ = cm[c[5] >> scalebits];
	*d++ = cm[c[6] >> scalebits];
	*d++ = cm[c[7] >> scalebits];

	d = dst + bytes_per_line*2;
	*d++ = cm[c[8] >> scalebits];
	*d++ = cm[c[9] >> scalebits];
	*d++ = cm[c[10] >> scalebits];
	*d++ = cm[c[11] >> scalebits];

	d = dst + bytes_per_line*3;
	*d++ = cm[c[12] >> scalebits];
	*d++ = cm[c[13] >> scalebits];
	*d++ = cm[c[14] >> scalebits];
	*d++ = cm[c[15] >> scalebits];
#अन्यथा
	पूर्णांक i;
	स्थिर पूर्णांक *c = src;
	अचिन्हित अक्षर *d = dst;
	क्रम (i = 0; i < 4; i++, c++)
		*d++ = CLAMP((*c) >> scalebits);

	d = dst + bytes_per_line;
	क्रम (i = 0; i < 4; i++, c++)
		*d++ = CLAMP((*c) >> scalebits);

	d = dst + bytes_per_line*2;
	क्रम (i = 0; i < 4; i++, c++)
		*d++ = CLAMP((*c) >> scalebits);

	d = dst + bytes_per_line*3;
	क्रम (i = 0; i < 4; i++, c++)
		*d++ = CLAMP((*c) >> scalebits);
#पूर्ण_अगर
पूर्ण

/*
 * Copy the 4x4 image block to a CrCb plane buffer
 *
 */
अटल व्योम copy_image_block_CrCb(स्थिर पूर्णांक *src, अचिन्हित अक्षर *dst, अचिन्हित पूर्णांक bytes_per_line, अचिन्हित पूर्णांक scalebits)
अणु
#अगर UNROLL_LOOP_FOR_COPY
	/* Unroll all loops */
	स्थिर अचिन्हित अक्षर *cm = pwc_crop_table+MAX_OUTER_CROP_VALUE;
	स्थिर पूर्णांक *c = src;
	अचिन्हित अक्षर *d = dst;

	*d++ = cm[c[0] >> scalebits];
	*d++ = cm[c[4] >> scalebits];
	*d++ = cm[c[1] >> scalebits];
	*d++ = cm[c[5] >> scalebits];
	*d++ = cm[c[2] >> scalebits];
	*d++ = cm[c[6] >> scalebits];
	*d++ = cm[c[3] >> scalebits];
	*d++ = cm[c[7] >> scalebits];

	d = dst + bytes_per_line;
	*d++ = cm[c[12] >> scalebits];
	*d++ = cm[c[8] >> scalebits];
	*d++ = cm[c[13] >> scalebits];
	*d++ = cm[c[9] >> scalebits];
	*d++ = cm[c[14] >> scalebits];
	*d++ = cm[c[10] >> scalebits];
	*d++ = cm[c[15] >> scalebits];
	*d++ = cm[c[11] >> scalebits];
#अन्यथा
	पूर्णांक i;
	स्थिर पूर्णांक *c1 = src;
	स्थिर पूर्णांक *c2 = src + 4;
	अचिन्हित अक्षर *d = dst;

	क्रम (i = 0; i < 4; i++, c1++, c2++) अणु
		*d++ = CLAMP((*c1) >> scalebits);
		*d++ = CLAMP((*c2) >> scalebits);
	पूर्ण
	c1 = src + 12;
	d = dst + bytes_per_line;
	क्रम (i = 0; i < 4; i++, c1++, c2++) अणु
		*d++ = CLAMP((*c1) >> scalebits);
		*d++ = CLAMP((*c2) >> scalebits);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * To manage the stream, we keep bits in a 32 bits रेजिस्टर.
 * fill_nbits(n): fill the reservoir with at least n bits
 * skip_bits(n): discard n bits from the reservoir
 * get_bits(n): fill the reservoir, वापसs the first n bits and discard the
 *              bits from the reservoir.
 * __get_nbits(n): faster version of get_bits(n), but asumes that the reservoir
 *                 contains at least n bits. bits वापसed is discarded.
 */
#घोषणा fill_nbits(pdec, nbits_wanted) करो अणु \
   जबतक (pdec->nbits_in_reservoir<(nbits_wanted)) \
    अणु \
      pdec->reservoir |= (*(pdec->stream)++) << (pdec->nbits_in_reservoir); \
      pdec->nbits_in_reservoir += 8; \
    पूर्ण \
पूर्ण  जबतक(0);

#घोषणा skip_nbits(pdec, nbits_to_skip) करो अणु \
   pdec->reservoir >>= (nbits_to_skip); \
   pdec->nbits_in_reservoir -= (nbits_to_skip); \
पूर्ण  जबतक(0);

#घोषणा get_nbits(pdec, nbits_wanted, result) करो अणु \
   fill_nbits(pdec, nbits_wanted); \
   result = (pdec->reservoir) & ((1U<<(nbits_wanted))-1); \
   skip_nbits(pdec, nbits_wanted); \
पूर्ण  जबतक(0);

#घोषणा __get_nbits(pdec, nbits_wanted, result) करो अणु \
   result = (pdec->reservoir) & ((1U<<(nbits_wanted))-1); \
   skip_nbits(pdec, nbits_wanted); \
पूर्ण  जबतक(0);

#घोषणा look_nbits(pdec, nbits_wanted) \
   ((pdec->reservoir) & ((1U<<(nbits_wanted))-1))

/*
 * Decode a 4x4 pixel block
 */
अटल व्योम decode_block(काष्ठा pwc_dec23_निजी *pdec,
			 स्थिर अचिन्हित अक्षर *ptable0004,
			 स्थिर अचिन्हित अक्षर *ptable8004)
अणु
	अचिन्हित पूर्णांक primary_color;
	अचिन्हित पूर्णांक channel_v, offset1, op;
	पूर्णांक i;

	fill_nbits(pdec, 16);
	__get_nbits(pdec, pdec->nbits, primary_color);

	अगर (look_nbits(pdec,2) == 0) अणु
		skip_nbits(pdec, 2);
		/* Very simple, the color is the same क्रम all pixels of the square */
		क्रम (i = 0; i < 16; i++)
			pdec->temp_colors[i] = pdec->table_dc00[primary_color];

		वापस;
	पूर्ण

	/* This block is encoded with small pattern */
	क्रम (i = 0; i < 16; i++)
		pdec->temp_colors[i] = pdec->table_d800[primary_color];

	__get_nbits(pdec, 3, channel_v);
	channel_v = ((channel_v & 1) << 2) | (channel_v & 2) | ((channel_v & 4) >> 2);

	ptable0004 += (channel_v * 128);
	ptable8004 += (channel_v * 32);

	offset1 = 0;
	करो
	अणु
		अचिन्हित पूर्णांक htable_idx, rows = 0;
		स्थिर अचिन्हित पूर्णांक *block;

		/* [  zzzz y x x ]
		 *     xx == 00 :=> end of the block def, हटाओ the two bits from the stream
		 *    yxx == 111
		 *    yxx == any other value
		 *
		 */
		fill_nbits(pdec, 16);
		htable_idx = look_nbits(pdec, 6);
		op = hash_table_ops[htable_idx * 4];

		अगर (op == 2) अणु
			skip_nbits(pdec, 2);

		पूर्ण अन्यथा अगर (op == 1) अणु
			/* 15bits [ xxxx xxxx yyyy 111 ]
			 * yyy => offset in the table8004
			 * xxx => offset in the tabled004 (tree)
			 */
			अचिन्हित पूर्णांक mask, shअगरt;
			अचिन्हित पूर्णांक nbits, col1;
			अचिन्हित पूर्णांक yyyy;

			skip_nbits(pdec, 3);
			/* offset1 += yyyy */
			__get_nbits(pdec, 4, yyyy);
			offset1 += 1 + yyyy;
			offset1 &= 0x0F;
			nbits = ptable8004[offset1 * 2];

			/* col1 = xxxx xxxx */
			__get_nbits(pdec, nbits+1, col1);

			/* Bit mask table */
			mask = pdec->table_bitघातermask[nbits][col1];
			shअगरt = ptable8004[offset1 * 2 + 1];
			rows = ((mask << shअगरt) + 0x80) & 0xFF;

			block = pdec->table_subblock[rows];
			क्रम (i = 0; i < 16; i++)
				pdec->temp_colors[i] += block[MulIdx[offset1][i]];

		पूर्ण अन्यथा अणु
			/* op == 0
			 * offset1 is coded on 3 bits
			 */
			अचिन्हित पूर्णांक shअगरt;

			offset1 += hash_table_ops [htable_idx * 4 + 2];
			offset1 &= 0x0F;

			rows = ptable0004[offset1 + hash_table_ops [htable_idx * 4 + 3]];
			block = pdec->table_subblock[rows];
			क्रम (i = 0; i < 16; i++)
				pdec->temp_colors[i] += block[MulIdx[offset1][i]];

			shअगरt = hash_table_ops[htable_idx * 4 + 1];
			skip_nbits(pdec, shअगरt);
		पूर्ण

	पूर्ण जबतक (op != 2);

पूर्ण

अटल व्योम DecompressBand23(काष्ठा pwc_dec23_निजी *pdec,
			     स्थिर अचिन्हित अक्षर *rawyuv,
			     अचिन्हित अक्षर *planar_y,
			     अचिन्हित अक्षर *planar_u,
			     अचिन्हित अक्षर *planar_v,
			     अचिन्हित पूर्णांक   compressed_image_width,
			     अचिन्हित पूर्णांक   real_image_width)
अणु
	पूर्णांक compression_index, nblocks;
	स्थिर अचिन्हित अक्षर *ptable0004;
	स्थिर अचिन्हित अक्षर *ptable8004;

	pdec->reservoir = 0;
	pdec->nbits_in_reservoir = 0;
	pdec->stream = rawyuv + 1;	/* The first byte of the stream is skipped */

	get_nbits(pdec, 4, compression_index);

	/* pass 1: uncompress Y component */
	nblocks = compressed_image_width / 4;

	ptable0004 = pdec->table_0004_pass1[compression_index];
	ptable8004 = pdec->table_8004_pass1[compression_index];

	/* Each block decode a square of 4x4 */
	जबतक (nblocks) अणु
		decode_block(pdec, ptable0004, ptable8004);
		copy_image_block_Y(pdec->temp_colors, planar_y, real_image_width, pdec->scalebits);
		planar_y += 4;
		nblocks--;
	पूर्ण

	/* pass 2: uncompress UV component */
	nblocks = compressed_image_width / 8;

	ptable0004 = pdec->table_0004_pass2[compression_index];
	ptable8004 = pdec->table_8004_pass2[compression_index];

	/* Each block decode a square of 4x4 */
	जबतक (nblocks) अणु
		decode_block(pdec, ptable0004, ptable8004);
		copy_image_block_CrCb(pdec->temp_colors, planar_u, real_image_width/2, pdec->scalebits);

		decode_block(pdec, ptable0004, ptable8004);
		copy_image_block_CrCb(pdec->temp_colors, planar_v, real_image_width/2, pdec->scalebits);

		planar_v += 8;
		planar_u += 8;
		nblocks -= 2;
	पूर्ण

पूर्ण

/**
 * pwc_dec23_decompress - Uncompress a pwc23 buffer.
 * @pdev: poपूर्णांकer to pwc device's पूर्णांकernal काष्ठा
 * @src: raw data
 * @dst: image output
 */
व्योम pwc_dec23_decompress(काष्ठा pwc_device *pdev,
			  स्थिर व्योम *src,
			  व्योम *dst)
अणु
	पूर्णांक bandlines_left, bytes_per_block;
	काष्ठा pwc_dec23_निजी *pdec = &pdev->dec23;

	/* YUV420P image क्रमmat */
	अचिन्हित अक्षर *pout_planar_y;
	अचिन्हित अक्षर *pout_planar_u;
	अचिन्हित अक्षर *pout_planar_v;
	अचिन्हित पूर्णांक   plane_size;

	mutex_lock(&pdec->lock);

	bandlines_left = pdev->height / 4;
	bytes_per_block = pdev->width * 4;
	plane_size = pdev->height * pdev->width;

	pout_planar_y = dst;
	pout_planar_u = dst + plane_size;
	pout_planar_v = dst + plane_size + plane_size / 4;

	जबतक (bandlines_left--) अणु
		DecompressBand23(pdec, src,
				 pout_planar_y, pout_planar_u, pout_planar_v,
				 pdev->width, pdev->width);
		src += pdev->vbandlength;
		pout_planar_y += bytes_per_block;
		pout_planar_u += pdev->width;
		pout_planar_v += pdev->width;
	पूर्ण
	mutex_unlock(&pdec->lock);
पूर्ण
