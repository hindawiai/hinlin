<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains an ECC algorithm that detects and corrects 1 bit
 * errors in a 256 byte block of data.
 *
 * Copyright तऊ 2008 Koninklijke Philips Electronics NV.
 *                  Author: Frans Meulenbroeks
 *
 * Completely replaces the previous ECC implementation which was written by:
 *   Steven J. Hill (sjhill@realitydiluted.com)
 *   Thomas Gleixner (tglx@linutronix.de)
 *
 * Inक्रमmation on how this algorithm works and how it was developed
 * can be found in Documentation/driver-api/mtd/nand_ecc.rst
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/nand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>

/*
 * invparity is a 256 byte table that contains the odd parity
 * क्रम each byte. So अगर the number of bits in a byte is even,
 * the array element is 1, and when the number of bits is odd
 * the array eleemnt is 0.
 */
अटल स्थिर अक्षर invparity[256] = अणु
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1
पूर्ण;

/*
 * bitsperbyte contains the number of bits per byte
 * this is only used क्रम testing and repairing parity
 * (a precalculated value slightly improves perक्रमmance)
 */
अटल स्थिर अक्षर bitsperbyte[256] = अणु
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
पूर्ण;

/*
 * addressbits is a lookup table to filter out the bits from the xor-ed
 * ECC data that identअगरy the faulty location.
 * this is only used क्रम repairing parity
 * see the comments in nand_ecc_sw_hamming_correct क्रम more details
 */
अटल स्थिर अक्षर addressbits[256] = अणु
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f
पूर्ण;

पूर्णांक ecc_sw_hamming_calculate(स्थिर अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक step_size,
			     अचिन्हित अक्षर *code, bool sm_order)
अणु
	स्थिर u32 *bp = (uपूर्णांक32_t *)buf;
	स्थिर u32 eccsize_mult = (step_size == 256) ? 1 : 2;
	/* current value in buffer */
	u32 cur;
	/* rp0..rp17 are the various accumulated parities (per byte) */
	u32 rp0, rp1, rp2, rp3, rp4, rp5, rp6, rp7, rp8, rp9, rp10, rp11, rp12,
		rp13, rp14, rp15, rp16, rp17;
	/* Cumulative parity क्रम all data */
	u32 par;
	/* Cumulative parity at the end of the loop (rp12, rp14, rp16) */
	u32 पंचांगppar;
	पूर्णांक i;

	par = 0;
	rp4 = 0;
	rp6 = 0;
	rp8 = 0;
	rp10 = 0;
	rp12 = 0;
	rp14 = 0;
	rp16 = 0;
	rp17 = 0;

	/*
	 * The loop is unrolled a number of बार;
	 * This aव्योमs अगर statements to decide on which rp value to update
	 * Also we process the data by दीर्घwords.
	 * Note: passing unaligned data might give a perक्रमmance penalty.
	 * It is assumed that the buffers are aligned.
	 * पंचांगppar is the cumulative sum of this iteration.
	 * needed क्रम calculating rp12, rp14, rp16 and par
	 * also used as a perक्रमmance improvement क्रम rp6, rp8 and rp10
	 */
	क्रम (i = 0; i < eccsize_mult << 2; i++) अणु
		cur = *bp++;
		पंचांगppar = cur;
		rp4 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp6 ^= पंचांगppar;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp4 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp8 ^= पंचांगppar;

		cur = *bp++;
		पंचांगppar ^= cur;
		rp4 ^= cur;
		rp6 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp6 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp4 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp10 ^= पंचांगppar;

		cur = *bp++;
		पंचांगppar ^= cur;
		rp4 ^= cur;
		rp6 ^= cur;
		rp8 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp6 ^= cur;
		rp8 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp4 ^= cur;
		rp8 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp8 ^= cur;

		cur = *bp++;
		पंचांगppar ^= cur;
		rp4 ^= cur;
		rp6 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp6 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;
		rp4 ^= cur;
		cur = *bp++;
		पंचांगppar ^= cur;

		par ^= पंचांगppar;
		अगर ((i & 0x1) == 0)
			rp12 ^= पंचांगppar;
		अगर ((i & 0x2) == 0)
			rp14 ^= पंचांगppar;
		अगर (eccsize_mult == 2 && (i & 0x4) == 0)
			rp16 ^= पंचांगppar;
	पूर्ण

	/*
	 * handle the fact that we use दीर्घword operations
	 * we'll bring rp4..rp14..rp16 back to single byte entities by
	 * shअगरting and xoring first fold the upper and lower 16 bits,
	 * then the upper and lower 8 bits.
	 */
	rp4 ^= (rp4 >> 16);
	rp4 ^= (rp4 >> 8);
	rp4 &= 0xff;
	rp6 ^= (rp6 >> 16);
	rp6 ^= (rp6 >> 8);
	rp6 &= 0xff;
	rp8 ^= (rp8 >> 16);
	rp8 ^= (rp8 >> 8);
	rp8 &= 0xff;
	rp10 ^= (rp10 >> 16);
	rp10 ^= (rp10 >> 8);
	rp10 &= 0xff;
	rp12 ^= (rp12 >> 16);
	rp12 ^= (rp12 >> 8);
	rp12 &= 0xff;
	rp14 ^= (rp14 >> 16);
	rp14 ^= (rp14 >> 8);
	rp14 &= 0xff;
	अगर (eccsize_mult == 2) अणु
		rp16 ^= (rp16 >> 16);
		rp16 ^= (rp16 >> 8);
		rp16 &= 0xff;
	पूर्ण

	/*
	 * we also need to calculate the row parity क्रम rp0..rp3
	 * This is present in par, because par is now
	 * rp3 rp3 rp2 rp2 in little endian and
	 * rp2 rp2 rp3 rp3 in big endian
	 * as well as
	 * rp1 rp0 rp1 rp0 in little endian and
	 * rp0 rp1 rp0 rp1 in big endian
	 * First calculate rp2 and rp3
	 */
#अगर_घोषित __BIG_ENDIAN
	rp2 = (par >> 16);
	rp2 ^= (rp2 >> 8);
	rp2 &= 0xff;
	rp3 = par & 0xffff;
	rp3 ^= (rp3 >> 8);
	rp3 &= 0xff;
#अन्यथा
	rp3 = (par >> 16);
	rp3 ^= (rp3 >> 8);
	rp3 &= 0xff;
	rp2 = par & 0xffff;
	rp2 ^= (rp2 >> 8);
	rp2 &= 0xff;
#पूर्ण_अगर

	/* reduce par to 16 bits then calculate rp1 and rp0 */
	par ^= (par >> 16);
#अगर_घोषित __BIG_ENDIAN
	rp0 = (par >> 8) & 0xff;
	rp1 = (par & 0xff);
#अन्यथा
	rp1 = (par >> 8) & 0xff;
	rp0 = (par & 0xff);
#पूर्ण_अगर

	/* finally reduce par to 8 bits */
	par ^= (par >> 8);
	par &= 0xff;

	/*
	 * and calculate rp5..rp15..rp17
	 * note that par = rp4 ^ rp5 and due to the commutative property
	 * of the ^ चालक we can say:
	 * rp5 = (par ^ rp4);
	 * The & 0xff seems superfluous, but benchmarking learned that
	 * leaving it out gives slightly worse results. No idea why, probably
	 * it has to करो with the way the pipeline in pentium is organized.
	 */
	rp5 = (par ^ rp4) & 0xff;
	rp7 = (par ^ rp6) & 0xff;
	rp9 = (par ^ rp8) & 0xff;
	rp11 = (par ^ rp10) & 0xff;
	rp13 = (par ^ rp12) & 0xff;
	rp15 = (par ^ rp14) & 0xff;
	अगर (eccsize_mult == 2)
		rp17 = (par ^ rp16) & 0xff;

	/*
	 * Finally calculate the ECC bits.
	 * Again here it might seem that there are perक्रमmance optimisations
	 * possible, but benchmarks showed that on the प्रणाली this is developed
	 * the code below is the fastest
	 */
	अगर (sm_order) अणु
		code[0] = (invparity[rp7] << 7) | (invparity[rp6] << 6) |
			  (invparity[rp5] << 5) | (invparity[rp4] << 4) |
			  (invparity[rp3] << 3) | (invparity[rp2] << 2) |
			  (invparity[rp1] << 1) | (invparity[rp0]);
		code[1] = (invparity[rp15] << 7) | (invparity[rp14] << 6) |
			  (invparity[rp13] << 5) | (invparity[rp12] << 4) |
			  (invparity[rp11] << 3) | (invparity[rp10] << 2) |
			  (invparity[rp9] << 1) | (invparity[rp8]);
	पूर्ण अन्यथा अणु
		code[1] = (invparity[rp7] << 7) | (invparity[rp6] << 6) |
			  (invparity[rp5] << 5) | (invparity[rp4] << 4) |
			  (invparity[rp3] << 3) | (invparity[rp2] << 2) |
			  (invparity[rp1] << 1) | (invparity[rp0]);
		code[0] = (invparity[rp15] << 7) | (invparity[rp14] << 6) |
			  (invparity[rp13] << 5) | (invparity[rp12] << 4) |
			  (invparity[rp11] << 3) | (invparity[rp10] << 2) |
			  (invparity[rp9] << 1) | (invparity[rp8]);
	पूर्ण

	अगर (eccsize_mult == 1)
		code[2] =
		    (invparity[par & 0xf0] << 7) |
		    (invparity[par & 0x0f] << 6) |
		    (invparity[par & 0xcc] << 5) |
		    (invparity[par & 0x33] << 4) |
		    (invparity[par & 0xaa] << 3) |
		    (invparity[par & 0x55] << 2) |
		    3;
	अन्यथा
		code[2] =
		    (invparity[par & 0xf0] << 7) |
		    (invparity[par & 0x0f] << 6) |
		    (invparity[par & 0xcc] << 5) |
		    (invparity[par & 0x33] << 4) |
		    (invparity[par & 0xaa] << 3) |
		    (invparity[par & 0x55] << 2) |
		    (invparity[rp17] << 1) |
		    (invparity[rp16] << 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ecc_sw_hamming_calculate);

/**
 * nand_ecc_sw_hamming_calculate - Calculate 3-byte ECC क्रम 256/512-byte block
 * @nand: न_अंकD device
 * @buf: Input buffer with raw data
 * @code: Output buffer with ECC
 */
पूर्णांक nand_ecc_sw_hamming_calculate(काष्ठा nand_device *nand,
				  स्थिर अचिन्हित अक्षर *buf, अचिन्हित अक्षर *code)
अणु
	काष्ठा nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.priv;
	अचिन्हित पूर्णांक step_size = nand->ecc.ctx.conf.step_size;

	वापस ecc_sw_hamming_calculate(buf, step_size, code,
					engine_conf->sm_order);
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_hamming_calculate);

पूर्णांक ecc_sw_hamming_correct(अचिन्हित अक्षर *buf, अचिन्हित अक्षर *पढ़ो_ecc,
			   अचिन्हित अक्षर *calc_ecc, अचिन्हित पूर्णांक step_size,
			   bool sm_order)
अणु
	स्थिर u32 eccsize_mult = step_size >> 8;
	अचिन्हित अक्षर b0, b1, b2, bit_addr;
	अचिन्हित पूर्णांक byte_addr;

	/*
	 * b0 to b2 indicate which bit is faulty (अगर any)
	 * we might need the xor result  more than once,
	 * so keep them in a local var
	*/
	अगर (sm_order) अणु
		b0 = पढ़ो_ecc[0] ^ calc_ecc[0];
		b1 = पढ़ो_ecc[1] ^ calc_ecc[1];
	पूर्ण अन्यथा अणु
		b0 = पढ़ो_ecc[1] ^ calc_ecc[1];
		b1 = पढ़ो_ecc[0] ^ calc_ecc[0];
	पूर्ण

	b2 = पढ़ो_ecc[2] ^ calc_ecc[2];

	/* check अगर there are any bitfaults */

	/* repeated अगर statements are slightly more efficient than चयन ... */
	/* ordered in order of likelihood */

	अगर ((b0 | b1 | b2) == 0)
		वापस 0;	/* no error */

	अगर ((((b0 ^ (b0 >> 1)) & 0x55) == 0x55) &&
	    (((b1 ^ (b1 >> 1)) & 0x55) == 0x55) &&
	    ((eccsize_mult == 1 && ((b2 ^ (b2 >> 1)) & 0x54) == 0x54) ||
	     (eccsize_mult == 2 && ((b2 ^ (b2 >> 1)) & 0x55) == 0x55))) अणु
	/* single bit error */
		/*
		 * rp17/rp15/13/11/9/7/5/3/1 indicate which byte is the faulty
		 * byte, cp 5/3/1 indicate the faulty bit.
		 * A lookup table (called addressbits) is used to filter
		 * the bits from the byte they are in.
		 * A marginal optimisation is possible by having three
		 * dअगरferent lookup tables.
		 * One as we have now (क्रम b0), one क्रम b2
		 * (that would aव्योम the >> 1), and one क्रम b1 (with all values
		 * << 4). However it was felt that पूर्णांकroducing two more tables
		 * hardly justअगरy the gain.
		 *
		 * The b2 shअगरt is there to get rid of the lowest two bits.
		 * We could also करो addressbits[b2] >> 1 but क्रम the
		 * perक्रमmance it करोes not make any dअगरference
		 */
		अगर (eccsize_mult == 1)
			byte_addr = (addressbits[b1] << 4) + addressbits[b0];
		अन्यथा
			byte_addr = (addressbits[b2 & 0x3] << 8) +
				    (addressbits[b1] << 4) + addressbits[b0];
		bit_addr = addressbits[b2 >> 2];
		/* flip the bit */
		buf[byte_addr] ^= (1 << bit_addr);
		वापस 1;

	पूर्ण
	/* count nr of bits; use table lookup, faster than calculating it */
	अगर ((bitsperbyte[b0] + bitsperbyte[b1] + bitsperbyte[b2]) == 1)
		वापस 1;	/* error in ECC data; no action needed */

	pr_err("%s: uncorrectable ECC error\n", __func__);
	वापस -EBADMSG;
पूर्ण
EXPORT_SYMBOL(ecc_sw_hamming_correct);

/**
 * nand_ecc_sw_hamming_correct - Detect and correct bit error(s)
 * @nand: न_अंकD device
 * @buf: Raw data पढ़ो from the chip
 * @पढ़ो_ecc: ECC bytes पढ़ो from the chip
 * @calc_ecc: ECC calculated from the raw data
 *
 * Detect and correct up to 1 bit error per 256/512-byte block.
 */
पूर्णांक nand_ecc_sw_hamming_correct(काष्ठा nand_device *nand, अचिन्हित अक्षर *buf,
				अचिन्हित अक्षर *पढ़ो_ecc,
				अचिन्हित अक्षर *calc_ecc)
अणु
	काष्ठा nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.priv;
	अचिन्हित पूर्णांक step_size = nand->ecc.ctx.conf.step_size;

	वापस ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc, step_size,
				      engine_conf->sm_order);
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_hamming_correct);

पूर्णांक nand_ecc_sw_hamming_init_ctx(काष्ठा nand_device *nand)
अणु
	काष्ठा nand_ecc_props *conf = &nand->ecc.ctx.conf;
	काष्ठा nand_ecc_sw_hamming_conf *engine_conf;
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	पूर्णांक ret;

	अगर (!mtd->ooblayout) अणु
		चयन (mtd->oobsize) अणु
		हाल 8:
		हाल 16:
			mtd_set_ooblayout(mtd, nand_get_small_page_ooblayout());
			अवरोध;
		हाल 64:
		हाल 128:
			mtd_set_ooblayout(mtd,
					  nand_get_large_page_hamming_ooblayout());
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	conf->engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
	conf->algo = न_अंकD_ECC_ALGO_HAMMING;
	conf->step_size = nand->ecc.user_conf.step_size;
	conf->strength = 1;

	/* Use the strongest configuration by शेष */
	अगर (conf->step_size != 256 && conf->step_size != 512)
		conf->step_size = 256;

	engine_conf = kzalloc(माप(*engine_conf), GFP_KERNEL);
	अगर (!engine_conf)
		वापस -ENOMEM;

	ret = nand_ecc_init_req_tweaking(&engine_conf->req_ctx, nand);
	अगर (ret)
		जाओ मुक्त_engine_conf;

	engine_conf->code_size = 3;
	engine_conf->calc_buf = kzalloc(mtd->oobsize, GFP_KERNEL);
	engine_conf->code_buf = kzalloc(mtd->oobsize, GFP_KERNEL);
	अगर (!engine_conf->calc_buf || !engine_conf->code_buf) अणु
		ret = -ENOMEM;
		जाओ मुक्त_bufs;
	पूर्ण

	nand->ecc.ctx.priv = engine_conf;
	nand->ecc.ctx.nsteps = mtd->ग_लिखोsize / conf->step_size;
	nand->ecc.ctx.total = nand->ecc.ctx.nsteps * engine_conf->code_size;

	वापस 0;

मुक्त_bufs:
	nand_ecc_cleanup_req_tweaking(&engine_conf->req_ctx);
	kमुक्त(engine_conf->calc_buf);
	kमुक्त(engine_conf->code_buf);
मुक्त_engine_conf:
	kमुक्त(engine_conf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_hamming_init_ctx);

व्योम nand_ecc_sw_hamming_cleanup_ctx(काष्ठा nand_device *nand)
अणु
	काष्ठा nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.priv;

	अगर (engine_conf) अणु
		nand_ecc_cleanup_req_tweaking(&engine_conf->req_ctx);
		kमुक्त(engine_conf->calc_buf);
		kमुक्त(engine_conf->code_buf);
		kमुक्त(engine_conf);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_hamming_cleanup_ctx);

अटल पूर्णांक nand_ecc_sw_hamming_prepare_io_req(काष्ठा nand_device *nand,
					      काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.priv;
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	पूर्णांक eccsize = nand->ecc.ctx.conf.step_size;
	पूर्णांक eccbytes = engine_conf->code_size;
	पूर्णांक eccsteps = nand->ecc.ctx.nsteps;
	पूर्णांक total = nand->ecc.ctx.total;
	u8 *ecccalc = engine_conf->calc_buf;
	स्थिर u8 *data;
	पूर्णांक i;

	/* Nothing to करो क्रम a raw operation */
	अगर (req->mode == MTD_OPS_RAW)
		वापस 0;

	/* This engine करोes not provide BBM/मुक्त OOB bytes protection */
	अगर (!req->datalen)
		वापस 0;

	nand_ecc_tweak_req(&engine_conf->req_ctx, req);

	/* No more preparation क्रम page पढ़ो */
	अगर (req->type == न_अंकD_PAGE_READ)
		वापस 0;

	/* Preparation क्रम page ग_लिखो: derive the ECC bytes and place them */
	क्रम (i = 0, data = req->databuf.out;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_hamming_calculate(nand, data, &ecccalc[i]);

	वापस mtd_ooblayout_set_eccbytes(mtd, ecccalc, (व्योम *)req->oobbuf.out,
					  0, total);
पूर्ण

अटल पूर्णांक nand_ecc_sw_hamming_finish_io_req(काष्ठा nand_device *nand,
					     काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.priv;
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	पूर्णांक eccsize = nand->ecc.ctx.conf.step_size;
	पूर्णांक total = nand->ecc.ctx.total;
	पूर्णांक eccbytes = engine_conf->code_size;
	पूर्णांक eccsteps = nand->ecc.ctx.nsteps;
	u8 *ecccalc = engine_conf->calc_buf;
	u8 *ecccode = engine_conf->code_buf;
	अचिन्हित पूर्णांक max_bitflips = 0;
	u8 *data = req->databuf.in;
	पूर्णांक i, ret;

	/* Nothing to करो क्रम a raw operation */
	अगर (req->mode == MTD_OPS_RAW)
		वापस 0;

	/* This engine करोes not provide BBM/मुक्त OOB bytes protection */
	अगर (!req->datalen)
		वापस 0;

	/* No more preparation क्रम page ग_लिखो */
	अगर (req->type == न_अंकD_PAGE_WRITE) अणु
		nand_ecc_restore_req(&engine_conf->req_ctx, req);
		वापस 0;
	पूर्ण

	/* Finish a page पढ़ो: retrieve the (raw) ECC bytes*/
	ret = mtd_ooblayout_get_eccbytes(mtd, ecccode, req->oobbuf.in, 0,
					 total);
	अगर (ret)
		वापस ret;

	/* Calculate the ECC bytes */
	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_hamming_calculate(nand, data, &ecccalc[i]);

	/* Finish a page पढ़ो: compare and correct */
	क्रम (eccsteps = nand->ecc.ctx.nsteps, i = 0, data = req->databuf.in;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize) अणु
		पूर्णांक stat =  nand_ecc_sw_hamming_correct(nand, data,
							&ecccode[i],
							&ecccalc[i]);
		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण

	nand_ecc_restore_req(&engine_conf->req_ctx, req);

	वापस max_bitflips;
पूर्ण

अटल काष्ठा nand_ecc_engine_ops nand_ecc_sw_hamming_engine_ops = अणु
	.init_ctx = nand_ecc_sw_hamming_init_ctx,
	.cleanup_ctx = nand_ecc_sw_hamming_cleanup_ctx,
	.prepare_io_req = nand_ecc_sw_hamming_prepare_io_req,
	.finish_io_req = nand_ecc_sw_hamming_finish_io_req,
पूर्ण;

अटल काष्ठा nand_ecc_engine nand_ecc_sw_hamming_engine = अणु
	.ops = &nand_ecc_sw_hamming_engine_ops,
पूर्ण;

काष्ठा nand_ecc_engine *nand_ecc_sw_hamming_get_engine(व्योम)
अणु
	वापस &nand_ecc_sw_hamming_engine;
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_hamming_get_engine);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Frans Meulenbroeks <fransmeulenbroeks@gmail.com>");
MODULE_DESCRIPTION("NAND software Hamming ECC support");
