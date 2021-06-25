<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1+
/*
 * Copyright 2016 Tom aan de Wiel
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *
 * 8x8 Fast Walsh Hadamard Transक्रमm in sequency order based on the paper:
 *
 * A Recursive Algorithm क्रम Sequency-Ordered Fast Walsh Transक्रमms,
 * R.D. Brown, 1977
 */

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>
#समावेश "codec-fwht.h"

#घोषणा OVERFLOW_BIT BIT(14)

/*
 * Note: bit 0 of the header must always be 0. Otherwise it cannot
 * be guaranteed that the magic 8 byte sequence (see below) can
 * never occur in the rlc output.
 */
#घोषणा PFRAME_BIT BIT(15)
#घोषणा DUPS_MASK 0x1ffe

#घोषणा PBLOCK 0
#घोषणा IBLOCK 1

#घोषणा ALL_ZEROS 15

अटल स्थिर uपूर्णांक8_t zigzag[64] = अणु
	0,
	1,  8,
	2,  9, 16,
	3, 10, 17, 24,
	4, 11, 18, 25, 32,
	5, 12, 19, 26, 33, 40,
	6, 13, 20, 27, 34, 41, 48,
	7, 14, 21, 28, 35, 42, 49, 56,
	15, 22, 29, 36, 43, 50, 57,
	23, 30, 37, 44, 51, 58,
	31, 38, 45, 52, 59,
	39, 46, 53, 60,
	47, 54, 61,
	55, 62,
	63,
पूर्ण;

/*
 * noअंतरभूत_क्रम_stack to work around
 * https://bugs.llvm.org/show_bug.cgi?id=38809
 */
अटल पूर्णांक noअंतरभूत_क्रम_stack
rlc(स्थिर s16 *in, __be16 *output, पूर्णांक blocktype)
अणु
	s16 block[8 * 8];
	s16 *wp = block;
	पूर्णांक i = 0;
	पूर्णांक x, y;
	पूर्णांक ret = 0;

	/* पढ़ो in block from framebuffer */
	पूर्णांक lastzero_run = 0;
	पूर्णांक to_encode;

	क्रम (y = 0; y < 8; y++) अणु
		क्रम (x = 0; x < 8; x++) अणु
			*wp = in[x + y * 8];
			wp++;
		पूर्ण
	पूर्ण

	/* keep track of amount of trailing zeros */
	क्रम (i = 63; i >= 0 && !block[zigzag[i]]; i--)
		lastzero_run++;

	*output++ = (blocktype == PBLOCK ? htons(PFRAME_BIT) : 0);
	ret++;

	to_encode = 8 * 8 - (lastzero_run > 14 ? lastzero_run : 0);

	i = 0;
	जबतक (i < to_encode) अणु
		पूर्णांक cnt = 0;
		पूर्णांक पंचांगp;

		/* count leading zeros */
		जबतक ((पंचांगp = block[zigzag[i]]) == 0 && cnt < 14) अणु
			cnt++;
			i++;
			अगर (i == to_encode) अणु
				cnt--;
				अवरोध;
			पूर्ण
		पूर्ण
		/* 4 bits क्रम run, 12 क्रम coefficient (quantization by 4) */
		*output++ = htons((cnt | पंचांगp << 4));
		i++;
		ret++;
	पूर्ण
	अगर (lastzero_run > 14) अणु
		*output = htons(ALL_ZEROS | 0);
		ret++;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function will worst-हाल increase rlc_in by 65*2 bytes:
 * one s16 value क्रम the header and 8 * 8 coefficients of type s16.
 */
अटल noअंतरभूत_क्रम_stack u16
derlc(स्थिर __be16 **rlc_in, s16 *dwht_out, स्थिर __be16 *end_of_input)
अणु
	/* header */
	स्थिर __be16 *input = *rlc_in;
	u16 stat;
	पूर्णांक dec_count = 0;
	s16 block[8 * 8 + 16];
	s16 *wp = block;
	पूर्णांक i;

	अगर (input > end_of_input)
		वापस OVERFLOW_BIT;
	stat = ntohs(*input++);

	/*
	 * Now de-compress, it expands one byte to up to 15 bytes
	 * (or fills the reमुख्यder of the 64 bytes with zeroes अगर it
	 * is the last byte to expand).
	 *
	 * So block has to be 8 * 8 + 16 bytes, the '+ 16' is to
	 * allow क्रम overflow अगर the incoming data was malक्रमmed.
	 */
	जबतक (dec_count < 8 * 8) अणु
		s16 in;
		पूर्णांक length;
		पूर्णांक coeff;

		अगर (input > end_of_input)
			वापस OVERFLOW_BIT;
		in = ntohs(*input++);
		length = in & 0xf;
		coeff = in >> 4;

		/* fill reमुख्यder with zeros */
		अगर (length == 15) अणु
			क्रम (i = 0; i < 64 - dec_count; i++)
				*wp++ = 0;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < length; i++)
			*wp++ = 0;
		*wp++ = coeff;
		dec_count += length + 1;
	पूर्ण

	wp = block;

	क्रम (i = 0; i < 64; i++) अणु
		पूर्णांक pos = zigzag[i];
		पूर्णांक y = pos / 8;
		पूर्णांक x = pos % 8;

		dwht_out[x + y * 8] = *wp++;
	पूर्ण
	*rlc_in = input;
	वापस stat;
पूर्ण

अटल स्थिर पूर्णांक quant_table[] = अणु
	2, 2, 2, 2, 2, 2,  2,  2,
	2, 2, 2, 2, 2, 2,  2,  2,
	2, 2, 2, 2, 2, 2,  2,  3,
	2, 2, 2, 2, 2, 2,  3,  6,
	2, 2, 2, 2, 2, 3,  6,  6,
	2, 2, 2, 2, 3, 6,  6,  6,
	2, 2, 2, 3, 6, 6,  6,  6,
	2, 2, 3, 6, 6, 6,  6,  8,
पूर्ण;

अटल स्थिर पूर्णांक quant_table_p[] = अणु
	3, 3, 3, 3, 3, 3,  3,  3,
	3, 3, 3, 3, 3, 3,  3,  3,
	3, 3, 3, 3, 3, 3,  3,  3,
	3, 3, 3, 3, 3, 3,  3,  6,
	3, 3, 3, 3, 3, 3,  6,  6,
	3, 3, 3, 3, 3, 6,  6,  9,
	3, 3, 3, 3, 6, 6,  9,  9,
	3, 3, 3, 6, 6, 9,  9,  10,
पूर्ण;

अटल व्योम quantize_पूर्णांकra(s16 *coeff, s16 *de_coeff, u16 qp)
अणु
	स्थिर पूर्णांक *quant = quant_table;
	पूर्णांक i, j;

	क्रम (j = 0; j < 8; j++) अणु
		क्रम (i = 0; i < 8; i++, quant++, coeff++, de_coeff++) अणु
			*coeff >>= *quant;
			अगर (*coeff >= -qp && *coeff <= qp)
				*coeff = *de_coeff = 0;
			अन्यथा
				*de_coeff = *coeff << *quant;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dequantize_पूर्णांकra(s16 *coeff)
अणु
	स्थिर पूर्णांक *quant = quant_table;
	पूर्णांक i, j;

	क्रम (j = 0; j < 8; j++)
		क्रम (i = 0; i < 8; i++, quant++, coeff++)
			*coeff <<= *quant;
पूर्ण

अटल व्योम quantize_पूर्णांकer(s16 *coeff, s16 *de_coeff, u16 qp)
अणु
	स्थिर पूर्णांक *quant = quant_table_p;
	पूर्णांक i, j;

	क्रम (j = 0; j < 8; j++) अणु
		क्रम (i = 0; i < 8; i++, quant++, coeff++, de_coeff++) अणु
			*coeff >>= *quant;
			अगर (*coeff >= -qp && *coeff <= qp)
				*coeff = *de_coeff = 0;
			अन्यथा
				*de_coeff = *coeff << *quant;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dequantize_पूर्णांकer(s16 *coeff)
अणु
	स्थिर पूर्णांक *quant = quant_table_p;
	पूर्णांक i, j;

	क्रम (j = 0; j < 8; j++)
		क्रम (i = 0; i < 8; i++, quant++, coeff++)
			*coeff <<= *quant;
पूर्ण

अटल व्योम noअंतरभूत_क्रम_stack fwht(स्थिर u8 *block, s16 *output_block,
				    अचिन्हित पूर्णांक stride,
				    अचिन्हित पूर्णांक input_step, bool पूर्णांकra)
अणु
	/* we'll need more than 8 bits क्रम the transक्रमmed coefficients */
	s32 workspace1[8], workspace2[8];
	स्थिर u8 *पंचांगp = block;
	s16 *out = output_block;
	पूर्णांक add = पूर्णांकra ? 256 : 0;
	अचिन्हित पूर्णांक i;

	/* stage 1 */
	क्रम (i = 0; i < 8; i++, पंचांगp += stride, out += 8) अणु
		चयन (input_step) अणु
		हाल 1:
			workspace1[0]  = पंचांगp[0] + पंचांगp[1] - add;
			workspace1[1]  = पंचांगp[0] - पंचांगp[1];

			workspace1[2]  = पंचांगp[2] + पंचांगp[3] - add;
			workspace1[3]  = पंचांगp[2] - पंचांगp[3];

			workspace1[4]  = पंचांगp[4] + पंचांगp[5] - add;
			workspace1[5]  = पंचांगp[4] - पंचांगp[5];

			workspace1[6]  = पंचांगp[6] + पंचांगp[7] - add;
			workspace1[7]  = पंचांगp[6] - पंचांगp[7];
			अवरोध;
		हाल 2:
			workspace1[0]  = पंचांगp[0] + पंचांगp[2] - add;
			workspace1[1]  = पंचांगp[0] - पंचांगp[2];

			workspace1[2]  = पंचांगp[4] + पंचांगp[6] - add;
			workspace1[3]  = पंचांगp[4] - पंचांगp[6];

			workspace1[4]  = पंचांगp[8] + पंचांगp[10] - add;
			workspace1[5]  = पंचांगp[8] - पंचांगp[10];

			workspace1[6]  = पंचांगp[12] + पंचांगp[14] - add;
			workspace1[7]  = पंचांगp[12] - पंचांगp[14];
			अवरोध;
		हाल 3:
			workspace1[0]  = पंचांगp[0] + पंचांगp[3] - add;
			workspace1[1]  = पंचांगp[0] - पंचांगp[3];

			workspace1[2]  = पंचांगp[6] + पंचांगp[9] - add;
			workspace1[3]  = पंचांगp[6] - पंचांगp[9];

			workspace1[4]  = पंचांगp[12] + पंचांगp[15] - add;
			workspace1[5]  = पंचांगp[12] - पंचांगp[15];

			workspace1[6]  = पंचांगp[18] + पंचांगp[21] - add;
			workspace1[7]  = पंचांगp[18] - पंचांगp[21];
			अवरोध;
		शेष:
			workspace1[0]  = पंचांगp[0] + पंचांगp[4] - add;
			workspace1[1]  = पंचांगp[0] - पंचांगp[4];

			workspace1[2]  = पंचांगp[8] + पंचांगp[12] - add;
			workspace1[3]  = पंचांगp[8] - पंचांगp[12];

			workspace1[4]  = पंचांगp[16] + पंचांगp[20] - add;
			workspace1[5]  = पंचांगp[16] - पंचांगp[20];

			workspace1[6]  = पंचांगp[24] + पंचांगp[28] - add;
			workspace1[7]  = पंचांगp[24] - पंचांगp[28];
			अवरोध;
		पूर्ण

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];

		/* stage 3 */
		out[0] = workspace2[0] + workspace2[4];
		out[1] = workspace2[0] - workspace2[4];
		out[2] = workspace2[1] - workspace2[5];
		out[3] = workspace2[1] + workspace2[5];
		out[4] = workspace2[2] + workspace2[6];
		out[5] = workspace2[2] - workspace2[6];
		out[6] = workspace2[3] - workspace2[7];
		out[7] = workspace2[3] + workspace2[7];
	पूर्ण

	out = output_block;

	क्रम (i = 0; i < 8; i++, out++) अणु
		/* stage 1 */
		workspace1[0]  = out[0] + out[1 * 8];
		workspace1[1]  = out[0] - out[1 * 8];

		workspace1[2]  = out[2 * 8] + out[3 * 8];
		workspace1[3]  = out[2 * 8] - out[3 * 8];

		workspace1[4]  = out[4 * 8] + out[5 * 8];
		workspace1[5]  = out[4 * 8] - out[5 * 8];

		workspace1[6]  = out[6 * 8] + out[7 * 8];
		workspace1[7]  = out[6 * 8] - out[7 * 8];

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];
		/* stage 3 */
		out[0 * 8] = workspace2[0] + workspace2[4];
		out[1 * 8] = workspace2[0] - workspace2[4];
		out[2 * 8] = workspace2[1] - workspace2[5];
		out[3 * 8] = workspace2[1] + workspace2[5];
		out[4 * 8] = workspace2[2] + workspace2[6];
		out[5 * 8] = workspace2[2] - workspace2[6];
		out[6 * 8] = workspace2[3] - workspace2[7];
		out[7 * 8] = workspace2[3] + workspace2[7];
	पूर्ण
पूर्ण

/*
 * Not the nicest way of करोing it, but P-blocks get twice the range of
 * that of the I-blocks. Thereक्रमe we need a type bigger than 8 bits.
 * Furthermore values can be negative... This is just a version that
 * works with 16 चिन्हित data
 */
अटल व्योम noअंतरभूत_क्रम_stack
fwht16(स्थिर s16 *block, s16 *output_block, पूर्णांक stride, पूर्णांक पूर्णांकra)
अणु
	/* we'll need more than 8 bits क्रम the transक्रमmed coefficients */
	s32 workspace1[8], workspace2[8];
	स्थिर s16 *पंचांगp = block;
	s16 *out = output_block;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++, पंचांगp += stride, out += 8) अणु
		/* stage 1 */
		workspace1[0]  = पंचांगp[0] + पंचांगp[1];
		workspace1[1]  = पंचांगp[0] - पंचांगp[1];

		workspace1[2]  = पंचांगp[2] + पंचांगp[3];
		workspace1[3]  = पंचांगp[2] - पंचांगp[3];

		workspace1[4]  = पंचांगp[4] + पंचांगp[5];
		workspace1[5]  = पंचांगp[4] - पंचांगp[5];

		workspace1[6]  = पंचांगp[6] + पंचांगp[7];
		workspace1[7]  = पंचांगp[6] - पंचांगp[7];

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];

		/* stage 3 */
		out[0] = workspace2[0] + workspace2[4];
		out[1] = workspace2[0] - workspace2[4];
		out[2] = workspace2[1] - workspace2[5];
		out[3] = workspace2[1] + workspace2[5];
		out[4] = workspace2[2] + workspace2[6];
		out[5] = workspace2[2] - workspace2[6];
		out[6] = workspace2[3] - workspace2[7];
		out[7] = workspace2[3] + workspace2[7];
	पूर्ण

	out = output_block;

	क्रम (i = 0; i < 8; i++, out++) अणु
		/* stage 1 */
		workspace1[0]  = out[0] + out[1*8];
		workspace1[1]  = out[0] - out[1*8];

		workspace1[2]  = out[2*8] + out[3*8];
		workspace1[3]  = out[2*8] - out[3*8];

		workspace1[4]  = out[4*8] + out[5*8];
		workspace1[5]  = out[4*8] - out[5*8];

		workspace1[6]  = out[6*8] + out[7*8];
		workspace1[7]  = out[6*8] - out[7*8];

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];

		/* stage 3 */
		out[0*8] = workspace2[0] + workspace2[4];
		out[1*8] = workspace2[0] - workspace2[4];
		out[2*8] = workspace2[1] - workspace2[5];
		out[3*8] = workspace2[1] + workspace2[5];
		out[4*8] = workspace2[2] + workspace2[6];
		out[5*8] = workspace2[2] - workspace2[6];
		out[6*8] = workspace2[3] - workspace2[7];
		out[7*8] = workspace2[3] + workspace2[7];
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
अगरwht(स्थिर s16 *block, s16 *output_block, पूर्णांक पूर्णांकra)
अणु
	/*
	 * we'll need more than 8 bits क्रम the transक्रमmed coefficients
	 * use native unit of cpu
	 */
	पूर्णांक workspace1[8], workspace2[8];
	पूर्णांक पूर्णांकer = पूर्णांकra ? 0 : 1;
	स्थिर s16 *पंचांगp = block;
	s16 *out = output_block;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++, पंचांगp += 8, out += 8) अणु
		/* stage 1 */
		workspace1[0]  = पंचांगp[0] + पंचांगp[1];
		workspace1[1]  = पंचांगp[0] - पंचांगp[1];

		workspace1[2]  = पंचांगp[2] + पंचांगp[3];
		workspace1[3]  = पंचांगp[2] - पंचांगp[3];

		workspace1[4]  = पंचांगp[4] + पंचांगp[5];
		workspace1[5]  = पंचांगp[4] - पंचांगp[5];

		workspace1[6]  = पंचांगp[6] + पंचांगp[7];
		workspace1[7]  = पंचांगp[6] - पंचांगp[7];

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];

		/* stage 3 */
		out[0] = workspace2[0] + workspace2[4];
		out[1] = workspace2[0] - workspace2[4];
		out[2] = workspace2[1] - workspace2[5];
		out[3] = workspace2[1] + workspace2[5];
		out[4] = workspace2[2] + workspace2[6];
		out[5] = workspace2[2] - workspace2[6];
		out[6] = workspace2[3] - workspace2[7];
		out[7] = workspace2[3] + workspace2[7];
	पूर्ण

	out = output_block;

	क्रम (i = 0; i < 8; i++, out++) अणु
		/* stage 1 */
		workspace1[0]  = out[0] + out[1 * 8];
		workspace1[1]  = out[0] - out[1 * 8];

		workspace1[2]  = out[2 * 8] + out[3 * 8];
		workspace1[3]  = out[2 * 8] - out[3 * 8];

		workspace1[4]  = out[4 * 8] + out[5 * 8];
		workspace1[5]  = out[4 * 8] - out[5 * 8];

		workspace1[6]  = out[6 * 8] + out[7 * 8];
		workspace1[7]  = out[6 * 8] - out[7 * 8];

		/* stage 2 */
		workspace2[0] = workspace1[0] + workspace1[2];
		workspace2[1] = workspace1[0] - workspace1[2];
		workspace2[2] = workspace1[1] - workspace1[3];
		workspace2[3] = workspace1[1] + workspace1[3];

		workspace2[4] = workspace1[4] + workspace1[6];
		workspace2[5] = workspace1[4] - workspace1[6];
		workspace2[6] = workspace1[5] - workspace1[7];
		workspace2[7] = workspace1[5] + workspace1[7];

		/* stage 3 */
		अगर (पूर्णांकer) अणु
			पूर्णांक d;

			out[0 * 8] = workspace2[0] + workspace2[4];
			out[1 * 8] = workspace2[0] - workspace2[4];
			out[2 * 8] = workspace2[1] - workspace2[5];
			out[3 * 8] = workspace2[1] + workspace2[5];
			out[4 * 8] = workspace2[2] + workspace2[6];
			out[5 * 8] = workspace2[2] - workspace2[6];
			out[6 * 8] = workspace2[3] - workspace2[7];
			out[7 * 8] = workspace2[3] + workspace2[7];

			क्रम (d = 0; d < 8; d++)
				out[8 * d] >>= 6;
		पूर्ण अन्यथा अणु
			पूर्णांक d;

			out[0 * 8] = workspace2[0] + workspace2[4];
			out[1 * 8] = workspace2[0] - workspace2[4];
			out[2 * 8] = workspace2[1] - workspace2[5];
			out[3 * 8] = workspace2[1] + workspace2[5];
			out[4 * 8] = workspace2[2] + workspace2[6];
			out[5 * 8] = workspace2[2] - workspace2[6];
			out[6 * 8] = workspace2[3] - workspace2[7];
			out[7 * 8] = workspace2[3] + workspace2[7];

			क्रम (d = 0; d < 8; d++) अणु
				out[8 * d] >>= 6;
				out[8 * d] += 128;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fill_encoder_block(स्थिर u8 *input, s16 *dst,
			       अचिन्हित पूर्णांक stride, अचिन्हित पूर्णांक input_step)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 8; i++) अणु
		क्रम (j = 0; j < 8; j++, input += input_step)
			*dst++ = *input;
		input += stride - 8 * input_step;
	पूर्ण
पूर्ण

अटल पूर्णांक var_पूर्णांकra(स्थिर s16 *input)
अणु
	पूर्णांक32_t mean = 0;
	पूर्णांक32_t ret = 0;
	स्थिर s16 *पंचांगp = input;
	पूर्णांक i;

	क्रम (i = 0; i < 8 * 8; i++, पंचांगp++)
		mean += *पंचांगp;
	mean /= 64;
	पंचांगp = input;
	क्रम (i = 0; i < 8 * 8; i++, पंचांगp++)
		ret += (*पंचांगp - mean) < 0 ? -(*पंचांगp - mean) : (*पंचांगp - mean);
	वापस ret;
पूर्ण

अटल पूर्णांक var_पूर्णांकer(स्थिर s16 *old, स्थिर s16 *new)
अणु
	पूर्णांक32_t ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8 * 8; i++, old++, new++)
		ret += (*old - *new) < 0 ? -(*old - *new) : (*old - *new);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
decide_blocktype(स्थिर u8 *cur, स्थिर u8 *reference, s16 *deltablock,
		 अचिन्हित पूर्णांक stride, अचिन्हित पूर्णांक input_step)
अणु
	s16 पंचांगp[64];
	s16 old[64];
	s16 *work = पंचांगp;
	अचिन्हित पूर्णांक k, l;
	पूर्णांक vari;
	पूर्णांक vard;

	fill_encoder_block(cur, पंचांगp, stride, input_step);
	fill_encoder_block(reference, old, 8, 1);
	vari = var_पूर्णांकra(पंचांगp);

	क्रम (k = 0; k < 8; k++) अणु
		क्रम (l = 0; l < 8; l++) अणु
			*deltablock = *work - *reference;
			deltablock++;
			work++;
			reference++;
		पूर्ण
	पूर्ण
	deltablock -= 64;
	vard = var_पूर्णांकer(old, पंचांगp);
	वापस vari <= vard ? IBLOCK : PBLOCK;
पूर्ण

अटल व्योम fill_decoder_block(u8 *dst, स्थिर s16 *input, पूर्णांक stride,
			       अचिन्हित पूर्णांक dst_step)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 8; i++) अणु
		क्रम (j = 0; j < 8; j++, input++, dst += dst_step) अणु
			अगर (*input < 0)
				*dst = 0;
			अन्यथा अगर (*input > 255)
				*dst = 255;
			अन्यथा
				*dst = *input;
		पूर्ण
		dst += stride - (8 * dst_step);
	पूर्ण
पूर्ण

अटल व्योम add_deltas(s16 *deltas, स्थिर u8 *ref, पूर्णांक stride,
		       अचिन्हित पूर्णांक ref_step)
अणु
	पूर्णांक k, l;

	क्रम (k = 0; k < 8; k++) अणु
		क्रम (l = 0; l < 8; l++) अणु
			*deltas += *ref;
			ref += ref_step;
			/*
			 * Due to quantizing, it might possible that the
			 * decoded coefficients are slightly out of range
			 */
			अगर (*deltas < 0)
				*deltas = 0;
			अन्यथा अगर (*deltas > 255)
				*deltas = 255;
			deltas++;
		पूर्ण
		ref += stride - (8 * ref_step);
	पूर्ण
पूर्ण

अटल u32 encode_plane(u8 *input, u8 *refp, __be16 **rlco, __be16 *rlco_max,
			काष्ठा fwht_cframe *cf, u32 height, u32 width,
			u32 stride, अचिन्हित पूर्णांक input_step,
			bool is_पूर्णांकra, bool next_is_पूर्णांकra)
अणु
	u8 *input_start = input;
	__be16 *rlco_start = *rlco;
	s16 deltablock[64];
	__be16 pframe_bit = htons(PFRAME_BIT);
	u32 encoding = 0;
	अचिन्हित पूर्णांक last_size = 0;
	अचिन्हित पूर्णांक i, j;

	width = round_up(width, 8);
	height = round_up(height, 8);

	क्रम (j = 0; j < height / 8; j++) अणु
		input = input_start + j * 8 * stride;
		क्रम (i = 0; i < width / 8; i++) अणु
			/* पूर्णांकra code, first frame is always पूर्णांकra coded. */
			पूर्णांक blocktype = IBLOCK;
			अचिन्हित पूर्णांक size;

			अगर (!is_पूर्णांकra)
				blocktype = decide_blocktype(input, refp,
					deltablock, stride, input_step);
			अगर (blocktype == IBLOCK) अणु
				fwht(input, cf->coeffs, stride, input_step, 1);
				quantize_पूर्णांकra(cf->coeffs, cf->de_coeffs,
					       cf->i_frame_qp);
			पूर्ण अन्यथा अणु
				/* पूर्णांकer code */
				encoding |= FWHT_FRAME_PCODED;
				fwht16(deltablock, cf->coeffs, 8, 0);
				quantize_पूर्णांकer(cf->coeffs, cf->de_coeffs,
					       cf->p_frame_qp);
			पूर्ण
			अगर (!next_is_पूर्णांकra) अणु
				अगरwht(cf->de_coeffs, cf->de_fwht, blocktype);

				अगर (blocktype == PBLOCK)
					add_deltas(cf->de_fwht, refp, 8, 1);
				fill_decoder_block(refp, cf->de_fwht, 8, 1);
			पूर्ण

			input += 8 * input_step;
			refp += 8 * 8;

			size = rlc(cf->coeffs, *rlco, blocktype);
			अगर (last_size == size &&
			    !स_भेद(*rlco + 1, *rlco - size + 1, 2 * size - 2)) अणु
				__be16 *last_rlco = *rlco - size;
				s16 hdr = ntohs(*last_rlco);

				अगर (!((*last_rlco ^ **rlco) & pframe_bit) &&
				    (hdr & DUPS_MASK) < DUPS_MASK)
					*last_rlco = htons(hdr + 2);
				अन्यथा
					*rlco += size;
			पूर्ण अन्यथा अणु
				*rlco += size;
			पूर्ण
			अगर (*rlco >= rlco_max) अणु
				encoding |= FWHT_FRAME_UNENCODED;
				जाओ निकास_loop;
			पूर्ण
			last_size = size;
		पूर्ण
	पूर्ण

निकास_loop:
	अगर (encoding & FWHT_FRAME_UNENCODED) अणु
		u8 *out = (u8 *)rlco_start;
		u8 *p;

		input = input_start;
		/*
		 * The compressed stream should never contain the magic
		 * header, so when we copy the YUV data we replace 0xff
		 * by 0xfe. Since YUV is limited range such values
		 * shouldn't appear anyway.
		 */
		क्रम (j = 0; j < height; j++) अणु
			क्रम (i = 0, p = input; i < width; i++, p += input_step)
				*out++ = (*p == 0xff) ? 0xfe : *p;
			input += stride;
		पूर्ण
		*rlco = (__be16 *)out;
		encoding &= ~FWHT_FRAME_PCODED;
	पूर्ण
	वापस encoding;
पूर्ण

u32 fwht_encode_frame(काष्ठा fwht_raw_frame *frm,
		      काष्ठा fwht_raw_frame *ref_frm,
		      काष्ठा fwht_cframe *cf,
		      bool is_पूर्णांकra, bool next_is_पूर्णांकra,
		      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
		      अचिन्हित पूर्णांक stride, अचिन्हित पूर्णांक chroma_stride)
अणु
	अचिन्हित पूर्णांक size = height * width;
	__be16 *rlco = cf->rlc_data;
	__be16 *rlco_max;
	u32 encoding;

	rlco_max = rlco + size / 2 - 256;
	encoding = encode_plane(frm->luma, ref_frm->luma, &rlco, rlco_max, cf,
				height, width, stride,
				frm->luma_alpha_step, is_पूर्णांकra, next_is_पूर्णांकra);
	अगर (encoding & FWHT_FRAME_UNENCODED)
		encoding |= FWHT_LUMA_UNENCODED;
	encoding &= ~FWHT_FRAME_UNENCODED;

	अगर (frm->components_num >= 3) अणु
		u32 chroma_h = height / frm->height_भाग;
		u32 chroma_w = width / frm->width_भाग;
		अचिन्हित पूर्णांक chroma_size = chroma_h * chroma_w;

		rlco_max = rlco + chroma_size / 2 - 256;
		encoding |= encode_plane(frm->cb, ref_frm->cb, &rlco, rlco_max,
					 cf, chroma_h, chroma_w,
					 chroma_stride, frm->chroma_step,
					 is_पूर्णांकra, next_is_पूर्णांकra);
		अगर (encoding & FWHT_FRAME_UNENCODED)
			encoding |= FWHT_CB_UNENCODED;
		encoding &= ~FWHT_FRAME_UNENCODED;
		rlco_max = rlco + chroma_size / 2 - 256;
		encoding |= encode_plane(frm->cr, ref_frm->cr, &rlco, rlco_max,
					 cf, chroma_h, chroma_w,
					 chroma_stride, frm->chroma_step,
					 is_पूर्णांकra, next_is_पूर्णांकra);
		अगर (encoding & FWHT_FRAME_UNENCODED)
			encoding |= FWHT_CR_UNENCODED;
		encoding &= ~FWHT_FRAME_UNENCODED;
	पूर्ण

	अगर (frm->components_num == 4) अणु
		rlco_max = rlco + size / 2 - 256;
		encoding |= encode_plane(frm->alpha, ref_frm->alpha, &rlco,
					 rlco_max, cf, height, width,
					 stride, frm->luma_alpha_step,
					 is_पूर्णांकra, next_is_पूर्णांकra);
		अगर (encoding & FWHT_FRAME_UNENCODED)
			encoding |= FWHT_ALPHA_UNENCODED;
		encoding &= ~FWHT_FRAME_UNENCODED;
	पूर्ण

	cf->size = (rlco - cf->rlc_data) * माप(*rlco);
	वापस encoding;
पूर्ण

अटल bool decode_plane(काष्ठा fwht_cframe *cf, स्थिर __be16 **rlco,
			 u32 height, u32 width, स्थिर u8 *ref, u32 ref_stride,
			 अचिन्हित पूर्णांक ref_step, u8 *dst,
			 अचिन्हित पूर्णांक dst_stride, अचिन्हित पूर्णांक dst_step,
			 bool uncompressed, स्थिर __be16 *end_of_rlco_buf)
अणु
	अचिन्हित पूर्णांक copies = 0;
	s16 copy[8 * 8];
	u16 stat;
	अचिन्हित पूर्णांक i, j;
	bool is_पूर्णांकra = !ref;

	width = round_up(width, 8);
	height = round_up(height, 8);

	अगर (uncompressed) अणु
		पूर्णांक i;

		अगर (end_of_rlco_buf + 1 < *rlco + width * height / 2)
			वापस false;
		क्रम (i = 0; i < height; i++) अणु
			स_नकल(dst, *rlco, width);
			dst += dst_stride;
			*rlco += width / 2;
		पूर्ण
		वापस true;
	पूर्ण

	/*
	 * When decoding each macroblock the rlco poपूर्णांकer will be increased
	 * by 65 * 2 bytes worst-हाल.
	 * To aव्योम overflow the buffer has to be 65/64th of the actual raw
	 * image size, just in हाल someone feeds it malicious data.
	 */
	क्रम (j = 0; j < height / 8; j++) अणु
		क्रम (i = 0; i < width / 8; i++) अणु
			स्थिर u8 *refp = ref + j * 8 * ref_stride +
				i * 8 * ref_step;
			u8 *dstp = dst + j * 8 * dst_stride + i * 8 * dst_step;

			अगर (copies) अणु
				स_नकल(cf->de_fwht, copy, माप(copy));
				अगर ((stat & PFRAME_BIT) && !is_पूर्णांकra)
					add_deltas(cf->de_fwht, refp,
						   ref_stride, ref_step);
				fill_decoder_block(dstp, cf->de_fwht,
						   dst_stride, dst_step);
				copies--;
				जारी;
			पूर्ण

			stat = derlc(rlco, cf->coeffs, end_of_rlco_buf);
			अगर (stat & OVERFLOW_BIT)
				वापस false;
			अगर ((stat & PFRAME_BIT) && !is_पूर्णांकra)
				dequantize_पूर्णांकer(cf->coeffs);
			अन्यथा
				dequantize_पूर्णांकra(cf->coeffs);

			अगरwht(cf->coeffs, cf->de_fwht,
			      ((stat & PFRAME_BIT) && !is_पूर्णांकra) ? 0 : 1);

			copies = (stat & DUPS_MASK) >> 1;
			अगर (copies)
				स_नकल(copy, cf->de_fwht, माप(copy));
			अगर ((stat & PFRAME_BIT) && !is_पूर्णांकra)
				add_deltas(cf->de_fwht, refp,
					   ref_stride, ref_step);
			fill_decoder_block(dstp, cf->de_fwht, dst_stride,
					   dst_step);
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

bool fwht_decode_frame(काष्ठा fwht_cframe *cf, u32 hdr_flags,
		       अचिन्हित पूर्णांक components_num, अचिन्हित पूर्णांक width,
		       अचिन्हित पूर्णांक height, स्थिर काष्ठा fwht_raw_frame *ref,
		       अचिन्हित पूर्णांक ref_stride, अचिन्हित पूर्णांक ref_chroma_stride,
		       काष्ठा fwht_raw_frame *dst, अचिन्हित पूर्णांक dst_stride,
		       अचिन्हित पूर्णांक dst_chroma_stride)
अणु
	स्थिर __be16 *rlco = cf->rlc_data;
	स्थिर __be16 *end_of_rlco_buf = cf->rlc_data +
			(cf->size / माप(*rlco)) - 1;

	अगर (!decode_plane(cf, &rlco, height, width, ref->luma, ref_stride,
			  ref->luma_alpha_step, dst->luma, dst_stride,
			  dst->luma_alpha_step,
			  hdr_flags & V4L2_FWHT_FL_LUMA_IS_UNCOMPRESSED,
			  end_of_rlco_buf))
		वापस false;

	अगर (components_num >= 3) अणु
		u32 h = height;
		u32 w = width;

		अगर (!(hdr_flags & V4L2_FWHT_FL_CHROMA_FULL_HEIGHT))
			h /= 2;
		अगर (!(hdr_flags & V4L2_FWHT_FL_CHROMA_FULL_WIDTH))
			w /= 2;

		अगर (!decode_plane(cf, &rlco, h, w, ref->cb, ref_chroma_stride,
				  ref->chroma_step, dst->cb, dst_chroma_stride,
				  dst->chroma_step,
				  hdr_flags & V4L2_FWHT_FL_CB_IS_UNCOMPRESSED,
				  end_of_rlco_buf))
			वापस false;
		अगर (!decode_plane(cf, &rlco, h, w, ref->cr, ref_chroma_stride,
				  ref->chroma_step, dst->cr, dst_chroma_stride,
				  dst->chroma_step,
				  hdr_flags & V4L2_FWHT_FL_CR_IS_UNCOMPRESSED,
				  end_of_rlco_buf))
			वापस false;
	पूर्ण

	अगर (components_num == 4)
		अगर (!decode_plane(cf, &rlco, height, width, ref->alpha, ref_stride,
				  ref->luma_alpha_step, dst->alpha, dst_stride,
				  dst->luma_alpha_step,
				  hdr_flags & V4L2_FWHT_FL_ALPHA_IS_UNCOMPRESSED,
				  end_of_rlco_buf))
			वापस false;
	वापस true;
पूर्ण
