<शैली गुरु>
/*
 * Generic binary BCH encoding/decoding library
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc., 51
 * Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 * Copyright तऊ 2011 Parrot S.A.
 *
 * Author: Ivan Djelic <ivan.djelic@parrot.com>
 *
 * Description:
 *
 * This library provides runसमय configurable encoding/decoding of binary
 * Bose-Chaudhuri-Hocquenghem (BCH) codes.
 *
 * Call bch_init to get a poपूर्णांकer to a newly allocated bch_control काष्ठाure क्रम
 * the given m (Galois field order), t (error correction capability) and
 * (optional) primitive polynomial parameters.
 *
 * Call bch_encode to compute and store ecc parity bytes to a given buffer.
 * Call bch_decode to detect and locate errors in received data.
 *
 * On प्रणालीs supporting hw BCH features, पूर्णांकermediate results may be provided
 * to bch_decode in order to skip certain steps. See bch_decode() करोcumentation
 * क्रम details.
 *
 * Option CONFIG_BCH_CONST_PARAMS can be used to क्रमce fixed values of
 * parameters m and t; thus allowing extra compiler optimizations and providing
 * better (up to 2x) encoding perक्रमmance. Using this option makes sense when
 * (m,t) are fixed and known in advance, e.g. when using BCH error correction
 * on a particular न_अंकD flash device.
 *
 * Algorithmic details:
 *
 * Encoding is perक्रमmed by processing 32 input bits in parallel, using 4
 * reमुख्यder lookup tables.
 *
 * The final stage of decoding involves the following पूर्णांकernal steps:
 * a. Syndrome computation
 * b. Error locator polynomial computation using Berlekamp-Massey algorithm
 * c. Error locator root finding (by far the most expensive step)
 *
 * In this implementation, step c is not perक्रमmed using the usual Chien search.
 * Instead, an alternative approach described in [1] is used. It consists in
 * factoring the error locator polynomial using the Berlekamp Trace algorithm
 * (BTA) करोwn to a certain degree (4), after which ad hoc low-degree polynomial
 * solving techniques [2] are used. The resulting algorithm, called BTZ, yields
 * much better perक्रमmance than Chien search क्रम usual (m,t) values (typically
 * m >= 13, t < 32, see [1]).
 *
 * [1] B. Biswas, V. Herbert. Efficient root finding of polynomials over fields
 * of अक्षरacteristic 2, in: Western European Workshop on Research in Cryptology
 * - WEWoRC 2009, Graz, Austria, LNCS, Springer, July 2009, to appear.
 * [2] [Zin96] V.A. Zinoviev. On the solution of equations of degree 10 over
 * finite fields GF(2^q). In Rapport de recherche INRIA no 2829, 1996.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bch.h>

#अगर defined(CONFIG_BCH_CONST_PARAMS)
#घोषणा GF_M(_p)               (CONFIG_BCH_CONST_M)
#घोषणा GF_T(_p)               (CONFIG_BCH_CONST_T)
#घोषणा GF_N(_p)               ((1 << (CONFIG_BCH_CONST_M))-1)
#घोषणा BCH_MAX_M              (CONFIG_BCH_CONST_M)
#घोषणा BCH_MAX_T	       (CONFIG_BCH_CONST_T)
#अन्यथा
#घोषणा GF_M(_p)               ((_p)->m)
#घोषणा GF_T(_p)               ((_p)->t)
#घोषणा GF_N(_p)               ((_p)->n)
#घोषणा BCH_MAX_M              15 /* 2KB */
#घोषणा BCH_MAX_T              64 /* 64 bit correction */
#पूर्ण_अगर

#घोषणा BCH_ECC_WORDS(_p)      DIV_ROUND_UP(GF_M(_p)*GF_T(_p), 32)
#घोषणा BCH_ECC_BYTES(_p)      DIV_ROUND_UP(GF_M(_p)*GF_T(_p), 8)

#घोषणा BCH_ECC_MAX_WORDS      DIV_ROUND_UP(BCH_MAX_M * BCH_MAX_T, 32)

#अगर_अघोषित dbg
#घोषणा dbg(_fmt, args...)     करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * represent a polynomial over GF(2^m)
 */
काष्ठा gf_poly अणु
	अचिन्हित पूर्णांक deg;    /* polynomial degree */
	अचिन्हित पूर्णांक c[];   /* polynomial terms */
पूर्ण;

/* given its degree, compute a polynomial size in bytes */
#घोषणा GF_POLY_SZ(_d) (माप(काष्ठा gf_poly)+((_d)+1)*माप(अचिन्हित पूर्णांक))

/* polynomial of degree 1 */
काष्ठा gf_poly_deg1 अणु
	काष्ठा gf_poly poly;
	अचिन्हित पूर्णांक   c[2];
पूर्ण;

अटल u8 swap_bits_table[] = अणु
	0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
	0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
	0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
	0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
	0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
	0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
	0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
	0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
	0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
	0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
	0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
	0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
	0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
	0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
	0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
	0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
	0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
	0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
	0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
	0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
	0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
	0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
	0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
	0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
	0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
	0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
	0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
	0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
	0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
	0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
	0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
	0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
पूर्ण;

अटल u8 swap_bits(काष्ठा bch_control *bch, u8 in)
अणु
	अगर (!bch->swap_bits)
		वापस in;

	वापस swap_bits_table[in];
पूर्ण

/*
 * same as bch_encode(), but process input data one byte at a समय
 */
अटल व्योम bch_encode_unaligned(काष्ठा bch_control *bch,
				 स्थिर अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len,
				 uपूर्णांक32_t *ecc)
अणु
	पूर्णांक i;
	स्थिर uपूर्णांक32_t *p;
	स्थिर पूर्णांक l = BCH_ECC_WORDS(bch)-1;

	जबतक (len--) अणु
		u8 पंचांगp = swap_bits(bch, *data++);

		p = bch->mod8_tab + (l+1)*(((ecc[0] >> 24)^(पंचांगp)) & 0xff);

		क्रम (i = 0; i < l; i++)
			ecc[i] = ((ecc[i] << 8)|(ecc[i+1] >> 24))^(*p++);

		ecc[l] = (ecc[l] << 8)^(*p);
	पूर्ण
पूर्ण

/*
 * convert ecc bytes to aligned, zero-padded 32-bit ecc words
 */
अटल व्योम load_ecc8(काष्ठा bch_control *bch, uपूर्णांक32_t *dst,
		      स्थिर uपूर्णांक8_t *src)
अणु
	uपूर्णांक8_t pad[4] = अणु0, 0, 0, 0पूर्ण;
	अचिन्हित पूर्णांक i, nwords = BCH_ECC_WORDS(bch)-1;

	क्रम (i = 0; i < nwords; i++, src += 4)
		dst[i] = ((u32)swap_bits(bch, src[0]) << 24) |
			((u32)swap_bits(bch, src[1]) << 16) |
			((u32)swap_bits(bch, src[2]) << 8) |
			swap_bits(bch, src[3]);

	स_नकल(pad, src, BCH_ECC_BYTES(bch)-4*nwords);
	dst[nwords] = ((u32)swap_bits(bch, pad[0]) << 24) |
		((u32)swap_bits(bch, pad[1]) << 16) |
		((u32)swap_bits(bch, pad[2]) << 8) |
		swap_bits(bch, pad[3]);
पूर्ण

/*
 * convert 32-bit ecc words to ecc bytes
 */
अटल व्योम store_ecc8(काष्ठा bch_control *bch, uपूर्णांक8_t *dst,
		       स्थिर uपूर्णांक32_t *src)
अणु
	uपूर्णांक8_t pad[4];
	अचिन्हित पूर्णांक i, nwords = BCH_ECC_WORDS(bch)-1;

	क्रम (i = 0; i < nwords; i++) अणु
		*dst++ = swap_bits(bch, src[i] >> 24);
		*dst++ = swap_bits(bch, src[i] >> 16);
		*dst++ = swap_bits(bch, src[i] >> 8);
		*dst++ = swap_bits(bch, src[i]);
	पूर्ण
	pad[0] = swap_bits(bch, src[nwords] >> 24);
	pad[1] = swap_bits(bch, src[nwords] >> 16);
	pad[2] = swap_bits(bch, src[nwords] >> 8);
	pad[3] = swap_bits(bch, src[nwords]);
	स_नकल(dst, pad, BCH_ECC_BYTES(bch)-4*nwords);
पूर्ण

/**
 * bch_encode - calculate BCH ecc parity of data
 * @bch:   BCH control काष्ठाure
 * @data:  data to encode
 * @len:   data length in bytes
 * @ecc:   ecc parity data, must be initialized by caller
 *
 * The @ecc parity array is used both as input and output parameter, in order to
 * allow incremental computations. It should be of the size indicated by member
 * @ecc_bytes of @bch, and should be initialized to 0 beक्रमe the first call.
 *
 * The exact number of computed ecc parity bits is given by member @ecc_bits of
 * @bch; it may be less than m*t क्रम large values of t.
 */
व्योम bch_encode(काष्ठा bch_control *bch, स्थिर uपूर्णांक8_t *data,
		अचिन्हित पूर्णांक len, uपूर्णांक8_t *ecc)
अणु
	स्थिर अचिन्हित पूर्णांक l = BCH_ECC_WORDS(bch)-1;
	अचिन्हित पूर्णांक i, mlen;
	अचिन्हित दीर्घ m;
	uपूर्णांक32_t w, r[BCH_ECC_MAX_WORDS];
	स्थिर माप_प्रकार r_bytes = BCH_ECC_WORDS(bch) * माप(*r);
	स्थिर uपूर्णांक32_t * स्थिर tab0 = bch->mod8_tab;
	स्थिर uपूर्णांक32_t * स्थिर tab1 = tab0 + 256*(l+1);
	स्थिर uपूर्णांक32_t * स्थिर tab2 = tab1 + 256*(l+1);
	स्थिर uपूर्णांक32_t * स्थिर tab3 = tab2 + 256*(l+1);
	स्थिर uपूर्णांक32_t *pdata, *p0, *p1, *p2, *p3;

	अगर (WARN_ON(r_bytes > माप(r)))
		वापस;

	अगर (ecc) अणु
		/* load ecc parity bytes पूर्णांकo पूर्णांकernal 32-bit buffer */
		load_ecc8(bch, bch->ecc_buf, ecc);
	पूर्ण अन्यथा अणु
		स_रखो(bch->ecc_buf, 0, r_bytes);
	पूर्ण

	/* process first unaligned data bytes */
	m = ((अचिन्हित दीर्घ)data) & 3;
	अगर (m) अणु
		mlen = (len < (4-m)) ? len : 4-m;
		bch_encode_unaligned(bch, data, mlen, bch->ecc_buf);
		data += mlen;
		len  -= mlen;
	पूर्ण

	/* process 32-bit aligned data words */
	pdata = (uपूर्णांक32_t *)data;
	mlen  = len/4;
	data += 4*mlen;
	len  -= 4*mlen;
	स_नकल(r, bch->ecc_buf, r_bytes);

	/*
	 * split each 32-bit word पूर्णांकo 4 polynomials of weight 8 as follows:
	 *
	 * 31 ...24  23 ...16  15 ... 8  7 ... 0
	 * xxxxxxxx  yyyyyyyy  zzzzzzzz  tttttttt
	 *                               tttttttt  mod g = r0 (precomputed)
	 *                     zzzzzzzz  00000000  mod g = r1 (precomputed)
	 *           yyyyyyyy  00000000  00000000  mod g = r2 (precomputed)
	 * xxxxxxxx  00000000  00000000  00000000  mod g = r3 (precomputed)
	 * xxxxxxxx  yyyyyyyy  zzzzzzzz  tttttttt  mod g = r0^r1^r2^r3
	 */
	जबतक (mlen--) अणु
		/* input data is पढ़ो in big-endian क्रमmat */
		w = cpu_to_be32(*pdata++);
		अगर (bch->swap_bits)
			w = (u32)swap_bits(bch, w) |
			    ((u32)swap_bits(bch, w >> 8) << 8) |
			    ((u32)swap_bits(bch, w >> 16) << 16) |
			    ((u32)swap_bits(bch, w >> 24) << 24);
		w ^= r[0];
		p0 = tab0 + (l+1)*((w >>  0) & 0xff);
		p1 = tab1 + (l+1)*((w >>  8) & 0xff);
		p2 = tab2 + (l+1)*((w >> 16) & 0xff);
		p3 = tab3 + (l+1)*((w >> 24) & 0xff);

		क्रम (i = 0; i < l; i++)
			r[i] = r[i+1]^p0[i]^p1[i]^p2[i]^p3[i];

		r[l] = p0[l]^p1[l]^p2[l]^p3[l];
	पूर्ण
	स_नकल(bch->ecc_buf, r, r_bytes);

	/* process last unaligned bytes */
	अगर (len)
		bch_encode_unaligned(bch, data, len, bch->ecc_buf);

	/* store ecc parity bytes पूर्णांकo original parity buffer */
	अगर (ecc)
		store_ecc8(bch, ecc, bch->ecc_buf);
पूर्ण
EXPORT_SYMBOL_GPL(bch_encode);

अटल अंतरभूत पूर्णांक modulo(काष्ठा bch_control *bch, अचिन्हित पूर्णांक v)
अणु
	स्थिर अचिन्हित पूर्णांक n = GF_N(bch);
	जबतक (v >= n) अणु
		v -= n;
		v = (v & n) + (v >> GF_M(bch));
	पूर्ण
	वापस v;
पूर्ण

/*
 * लघुer and faster modulo function, only works when v < 2N.
 */
अटल अंतरभूत पूर्णांक mod_s(काष्ठा bch_control *bch, अचिन्हित पूर्णांक v)
अणु
	स्थिर अचिन्हित पूर्णांक n = GF_N(bch);
	वापस (v < n) ? v : v-n;
पूर्ण

अटल अंतरभूत पूर्णांक deg(अचिन्हित पूर्णांक poly)
अणु
	/* polynomial degree is the most-signअगरicant bit index */
	वापस fls(poly)-1;
पूर्ण

अटल अंतरभूत पूर्णांक parity(अचिन्हित पूर्णांक x)
अणु
	/*
	 * खुला करोमुख्य code snippet, lअगरted from
	 * http://www-graphics.stanक्रमd.edu/~seander/bithacks.hपंचांगl
	 */
	x ^= x >> 1;
	x ^= x >> 2;
	x = (x & 0x11111111U) * 0x11111111U;
	वापस (x >> 28) & 1;
पूर्ण

/* Galois field basic operations: multiply, भागide, inverse, etc. */

अटल अंतरभूत अचिन्हित पूर्णांक gf_mul(काष्ठा bch_control *bch, अचिन्हित पूर्णांक a,
				  अचिन्हित पूर्णांक b)
अणु
	वापस (a && b) ? bch->a_घात_tab[mod_s(bch, bch->a_log_tab[a]+
					       bch->a_log_tab[b])] : 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gf_sqr(काष्ठा bch_control *bch, अचिन्हित पूर्णांक a)
अणु
	वापस a ? bch->a_घात_tab[mod_s(bch, 2*bch->a_log_tab[a])] : 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gf_भाग(काष्ठा bch_control *bch, अचिन्हित पूर्णांक a,
				  अचिन्हित पूर्णांक b)
अणु
	वापस a ? bch->a_घात_tab[mod_s(bch, bch->a_log_tab[a]+
					GF_N(bch)-bch->a_log_tab[b])] : 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gf_inv(काष्ठा bch_control *bch, अचिन्हित पूर्णांक a)
अणु
	वापस bch->a_घात_tab[GF_N(bch)-bch->a_log_tab[a]];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक a_घात(काष्ठा bch_control *bch, पूर्णांक i)
अणु
	वापस bch->a_घात_tab[modulo(bch, i)];
पूर्ण

अटल अंतरभूत पूर्णांक a_log(काष्ठा bch_control *bch, अचिन्हित पूर्णांक x)
अणु
	वापस bch->a_log_tab[x];
पूर्ण

अटल अंतरभूत पूर्णांक a_ilog(काष्ठा bch_control *bch, अचिन्हित पूर्णांक x)
अणु
	वापस mod_s(bch, GF_N(bch)-bch->a_log_tab[x]);
पूर्ण

/*
 * compute 2t syndromes of ecc polynomial, i.e. ecc(a^j) क्रम j=1..2t
 */
अटल व्योम compute_syndromes(काष्ठा bch_control *bch, uपूर्णांक32_t *ecc,
			      अचिन्हित पूर्णांक *syn)
अणु
	पूर्णांक i, j, s;
	अचिन्हित पूर्णांक m;
	uपूर्णांक32_t poly;
	स्थिर पूर्णांक t = GF_T(bch);

	s = bch->ecc_bits;

	/* make sure extra bits in last ecc word are cleared */
	m = ((अचिन्हित पूर्णांक)s) & 31;
	अगर (m)
		ecc[s/32] &= ~((1u << (32-m))-1);
	स_रखो(syn, 0, 2*t*माप(*syn));

	/* compute v(a^j) क्रम j=1 .. 2t-1 */
	करो अणु
		poly = *ecc++;
		s -= 32;
		जबतक (poly) अणु
			i = deg(poly);
			क्रम (j = 0; j < 2*t; j += 2)
				syn[j] ^= a_घात(bch, (j+1)*(i+s));

			poly ^= (1 << i);
		पूर्ण
	पूर्ण जबतक (s > 0);

	/* v(a^(2j)) = v(a^j)^2 */
	क्रम (j = 0; j < t; j++)
		syn[2*j+1] = gf_sqr(bch, syn[j]);
पूर्ण

अटल व्योम gf_poly_copy(काष्ठा gf_poly *dst, काष्ठा gf_poly *src)
अणु
	स_नकल(dst, src, GF_POLY_SZ(src->deg));
पूर्ण

अटल पूर्णांक compute_error_locator_polynomial(काष्ठा bch_control *bch,
					    स्थिर अचिन्हित पूर्णांक *syn)
अणु
	स्थिर अचिन्हित पूर्णांक t = GF_T(bch);
	स्थिर अचिन्हित पूर्णांक n = GF_N(bch);
	अचिन्हित पूर्णांक i, j, पंचांगp, l, pd = 1, d = syn[0];
	काष्ठा gf_poly *elp = bch->elp;
	काष्ठा gf_poly *pelp = bch->poly_2t[0];
	काष्ठा gf_poly *elp_copy = bch->poly_2t[1];
	पूर्णांक k, pp = -1;

	स_रखो(pelp, 0, GF_POLY_SZ(2*t));
	स_रखो(elp, 0, GF_POLY_SZ(2*t));

	pelp->deg = 0;
	pelp->c[0] = 1;
	elp->deg = 0;
	elp->c[0] = 1;

	/* use simplअगरied binary Berlekamp-Massey algorithm */
	क्रम (i = 0; (i < t) && (elp->deg <= t); i++) अणु
		अगर (d) अणु
			k = 2*i-pp;
			gf_poly_copy(elp_copy, elp);
			/* e[i+1](X) = e[i](X)+di*dp^-1*X^2(i-p)*e[p](X) */
			पंचांगp = a_log(bch, d)+n-a_log(bch, pd);
			क्रम (j = 0; j <= pelp->deg; j++) अणु
				अगर (pelp->c[j]) अणु
					l = a_log(bch, pelp->c[j]);
					elp->c[j+k] ^= a_घात(bch, पंचांगp+l);
				पूर्ण
			पूर्ण
			/* compute l[i+1] = max(l[i]->c[l[p]+2*(i-p]) */
			पंचांगp = pelp->deg+k;
			अगर (पंचांगp > elp->deg) अणु
				elp->deg = पंचांगp;
				gf_poly_copy(pelp, elp_copy);
				pd = d;
				pp = 2*i;
			पूर्ण
		पूर्ण
		/* di+1 = S(2i+3)+elp[i+1].1*S(2i+2)+...+elp[i+1].lS(2i+3-l) */
		अगर (i < t-1) अणु
			d = syn[2*i+2];
			क्रम (j = 1; j <= elp->deg; j++)
				d ^= gf_mul(bch, elp->c[j], syn[2*i+2-j]);
		पूर्ण
	पूर्ण
	dbg("elp=%s\n", gf_poly_str(elp));
	वापस (elp->deg > t) ? -1 : (पूर्णांक)elp->deg;
पूर्ण

/*
 * solve a m x m linear प्रणाली in GF(2) with an expected number of solutions,
 * and वापस the number of found solutions
 */
अटल पूर्णांक solve_linear_प्रणाली(काष्ठा bch_control *bch, अचिन्हित पूर्णांक *rows,
			       अचिन्हित पूर्णांक *sol, पूर्णांक nsol)
अणु
	स्थिर पूर्णांक m = GF_M(bch);
	अचिन्हित पूर्णांक पंचांगp, mask;
	पूर्णांक rem, c, r, p, k, param[BCH_MAX_M];

	k = 0;
	mask = 1 << m;

	/* Gaussian elimination */
	क्रम (c = 0; c < m; c++) अणु
		rem = 0;
		p = c-k;
		/* find suitable row क्रम elimination */
		क्रम (r = p; r < m; r++) अणु
			अगर (rows[r] & mask) अणु
				अगर (r != p) अणु
					पंचांगp = rows[r];
					rows[r] = rows[p];
					rows[p] = पंचांगp;
				पूर्ण
				rem = r+1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (rem) अणु
			/* perक्रमm elimination on reमुख्यing rows */
			पंचांगp = rows[p];
			क्रम (r = rem; r < m; r++) अणु
				अगर (rows[r] & mask)
					rows[r] ^= पंचांगp;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* elimination not needed, store defective row index */
			param[k++] = c;
		पूर्ण
		mask >>= 1;
	पूर्ण
	/* reग_लिखो प्रणाली, inserting fake parameter rows */
	अगर (k > 0) अणु
		p = k;
		क्रम (r = m-1; r >= 0; r--) अणु
			अगर ((r > m-1-k) && rows[r])
				/* प्रणाली has no solution */
				वापस 0;

			rows[r] = (p && (r == param[p-1])) ?
				p--, 1u << (m-r) : rows[r-p];
		पूर्ण
	पूर्ण

	अगर (nsol != (1 << k))
		/* unexpected number of solutions */
		वापस 0;

	क्रम (p = 0; p < nsol; p++) अणु
		/* set parameters क्रम p-th solution */
		क्रम (c = 0; c < k; c++)
			rows[param[c]] = (rows[param[c]] & ~1)|((p >> c) & 1);

		/* compute unique solution */
		पंचांगp = 0;
		क्रम (r = m-1; r >= 0; r--) अणु
			mask = rows[r] & (पंचांगp|1);
			पंचांगp |= parity(mask) << (m-r);
		पूर्ण
		sol[p] = पंचांगp >> 1;
	पूर्ण
	वापस nsol;
पूर्ण

/*
 * this function builds and solves a linear प्रणाली क्रम finding roots of a degree
 * 4 affine monic polynomial X^4+aX^2+bX+c over GF(2^m).
 */
अटल पूर्णांक find_affine4_roots(काष्ठा bch_control *bch, अचिन्हित पूर्णांक a,
			      अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c,
			      अचिन्हित पूर्णांक *roots)
अणु
	पूर्णांक i, j, k;
	स्थिर पूर्णांक m = GF_M(bch);
	अचिन्हित पूर्णांक mask = 0xff, t, rows[16] = अणु0,पूर्ण;

	j = a_log(bch, b);
	k = a_log(bch, a);
	rows[0] = c;

	/* build linear प्रणाली to solve X^4+aX^2+bX+c = 0 */
	क्रम (i = 0; i < m; i++) अणु
		rows[i+1] = bch->a_घात_tab[4*i]^
			(a ? bch->a_घात_tab[mod_s(bch, k)] : 0)^
			(b ? bch->a_घात_tab[mod_s(bch, j)] : 0);
		j++;
		k += 2;
	पूर्ण
	/*
	 * transpose 16x16 matrix beक्रमe passing it to linear solver
	 * warning: this code assumes m < 16
	 */
	क्रम (j = 8; j != 0; j >>= 1, mask ^= (mask << j)) अणु
		क्रम (k = 0; k < 16; k = (k+j+1) & ~j) अणु
			t = ((rows[k] >> j)^rows[k+j]) & mask;
			rows[k] ^= (t << j);
			rows[k+j] ^= t;
		पूर्ण
	पूर्ण
	वापस solve_linear_प्रणाली(bch, rows, roots, 4);
पूर्ण

/*
 * compute root r of a degree 1 polynomial over GF(2^m) (वापसed as log(1/r))
 */
अटल पूर्णांक find_poly_deg1_roots(काष्ठा bch_control *bch, काष्ठा gf_poly *poly,
				अचिन्हित पूर्णांक *roots)
अणु
	पूर्णांक n = 0;

	अगर (poly->c[0])
		/* poly[X] = bX+c with c!=0, root=c/b */
		roots[n++] = mod_s(bch, GF_N(bch)-bch->a_log_tab[poly->c[0]]+
				   bch->a_log_tab[poly->c[1]]);
	वापस n;
पूर्ण

/*
 * compute roots of a degree 2 polynomial over GF(2^m)
 */
अटल पूर्णांक find_poly_deg2_roots(काष्ठा bch_control *bch, काष्ठा gf_poly *poly,
				अचिन्हित पूर्णांक *roots)
अणु
	पूर्णांक n = 0, i, l0, l1, l2;
	अचिन्हित पूर्णांक u, v, r;

	अगर (poly->c[0] && poly->c[1]) अणु

		l0 = bch->a_log_tab[poly->c[0]];
		l1 = bch->a_log_tab[poly->c[1]];
		l2 = bch->a_log_tab[poly->c[2]];

		/* using z=a/bX, transक्रमm aX^2+bX+c पूर्णांकo z^2+z+u (u=ac/b^2) */
		u = a_घात(bch, l0+l2+2*(GF_N(bch)-l1));
		/*
		 * let u = sum(li.a^i) i=0..m-1; then compute r = sum(li.xi):
		 * r^2+r = sum(li.(xi^2+xi)) = sum(li.(a^i+Tr(a^i).a^k)) =
		 * u + sum(li.Tr(a^i).a^k) = u+a^k.Tr(sum(li.a^i)) = u+a^k.Tr(u)
		 * i.e. r and r+1 are roots अगरf Tr(u)=0
		 */
		r = 0;
		v = u;
		जबतक (v) अणु
			i = deg(v);
			r ^= bch->xi_tab[i];
			v ^= (1 << i);
		पूर्ण
		/* verअगरy root */
		अगर ((gf_sqr(bch, r)^r) == u) अणु
			/* reverse z=a/bX transक्रमmation and compute log(1/r) */
			roots[n++] = modulo(bch, 2*GF_N(bch)-l1-
					    bch->a_log_tab[r]+l2);
			roots[n++] = modulo(bch, 2*GF_N(bch)-l1-
					    bch->a_log_tab[r^1]+l2);
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

/*
 * compute roots of a degree 3 polynomial over GF(2^m)
 */
अटल पूर्णांक find_poly_deg3_roots(काष्ठा bch_control *bch, काष्ठा gf_poly *poly,
				अचिन्हित पूर्णांक *roots)
अणु
	पूर्णांक i, n = 0;
	अचिन्हित पूर्णांक a, b, c, a2, b2, c2, e3, पंचांगp[4];

	अगर (poly->c[0]) अणु
		/* transक्रमm polynomial पूर्णांकo monic X^3 + a2X^2 + b2X + c2 */
		e3 = poly->c[3];
		c2 = gf_भाग(bch, poly->c[0], e3);
		b2 = gf_भाग(bch, poly->c[1], e3);
		a2 = gf_भाग(bch, poly->c[2], e3);

		/* (X+a2)(X^3+a2X^2+b2X+c2) = X^4+aX^2+bX+c (affine) */
		c = gf_mul(bch, a2, c2);           /* c = a2c2      */
		b = gf_mul(bch, a2, b2)^c2;        /* b = a2b2 + c2 */
		a = gf_sqr(bch, a2)^b2;            /* a = a2^2 + b2 */

		/* find the 4 roots of this affine polynomial */
		अगर (find_affine4_roots(bch, a, b, c, पंचांगp) == 4) अणु
			/* हटाओ a2 from final list of roots */
			क्रम (i = 0; i < 4; i++) अणु
				अगर (पंचांगp[i] != a2)
					roots[n++] = a_ilog(bch, पंचांगp[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

/*
 * compute roots of a degree 4 polynomial over GF(2^m)
 */
अटल पूर्णांक find_poly_deg4_roots(काष्ठा bch_control *bch, काष्ठा gf_poly *poly,
				अचिन्हित पूर्णांक *roots)
अणु
	पूर्णांक i, l, n = 0;
	अचिन्हित पूर्णांक a, b, c, d, e = 0, f, a2, b2, c2, e4;

	अगर (poly->c[0] == 0)
		वापस 0;

	/* transक्रमm polynomial पूर्णांकo monic X^4 + aX^3 + bX^2 + cX + d */
	e4 = poly->c[4];
	d = gf_भाग(bch, poly->c[0], e4);
	c = gf_भाग(bch, poly->c[1], e4);
	b = gf_भाग(bch, poly->c[2], e4);
	a = gf_भाग(bch, poly->c[3], e4);

	/* use Y=1/X transक्रमmation to get an affine polynomial */
	अगर (a) अणु
		/* first, eliminate cX by using z=X+e with ae^2+c=0 */
		अगर (c) अणु
			/* compute e such that e^2 = c/a */
			f = gf_भाग(bch, c, a);
			l = a_log(bch, f);
			l += (l & 1) ? GF_N(bch) : 0;
			e = a_घात(bch, l/2);
			/*
			 * use transक्रमmation z=X+e:
			 * z^4+e^4 + a(z^3+ez^2+e^2z+e^3) + b(z^2+e^2) +cz+ce+d
			 * z^4 + az^3 + (ae+b)z^2 + (ae^2+c)z+e^4+be^2+ae^3+ce+d
			 * z^4 + az^3 + (ae+b)z^2 + e^4+be^2+d
			 * z^4 + az^3 +     b'z^2 + d'
			 */
			d = a_घात(bch, 2*l)^gf_mul(bch, b, f)^d;
			b = gf_mul(bch, a, e)^b;
		पूर्ण
		/* now, use Y=1/X to get Y^4 + b/dY^2 + a/dY + 1/d */
		अगर (d == 0)
			/* assume all roots have multiplicity 1 */
			वापस 0;

		c2 = gf_inv(bch, d);
		b2 = gf_भाग(bch, a, d);
		a2 = gf_भाग(bch, b, d);
	पूर्ण अन्यथा अणु
		/* polynomial is alपढ़ोy affine */
		c2 = d;
		b2 = c;
		a2 = b;
	पूर्ण
	/* find the 4 roots of this affine polynomial */
	अगर (find_affine4_roots(bch, a2, b2, c2, roots) == 4) अणु
		क्रम (i = 0; i < 4; i++) अणु
			/* post-process roots (reverse transक्रमmations) */
			f = a ? gf_inv(bch, roots[i]) : roots[i];
			roots[i] = a_ilog(bch, f^e);
		पूर्ण
		n = 4;
	पूर्ण
	वापस n;
पूर्ण

/*
 * build monic, log-based representation of a polynomial
 */
अटल व्योम gf_poly_logrep(काष्ठा bch_control *bch,
			   स्थिर काष्ठा gf_poly *a, पूर्णांक *rep)
अणु
	पूर्णांक i, d = a->deg, l = GF_N(bch)-a_log(bch, a->c[a->deg]);

	/* represent 0 values with -1; warning, rep[d] is not set to 1 */
	क्रम (i = 0; i < d; i++)
		rep[i] = a->c[i] ? mod_s(bch, a_log(bch, a->c[i])+l) : -1;
पूर्ण

/*
 * compute polynomial Euclidean भागision reमुख्यder in GF(2^m)[X]
 */
अटल व्योम gf_poly_mod(काष्ठा bch_control *bch, काष्ठा gf_poly *a,
			स्थिर काष्ठा gf_poly *b, पूर्णांक *rep)
अणु
	पूर्णांक la, p, m;
	अचिन्हित पूर्णांक i, j, *c = a->c;
	स्थिर अचिन्हित पूर्णांक d = b->deg;

	अगर (a->deg < d)
		वापस;

	/* reuse or compute log representation of denominator */
	अगर (!rep) अणु
		rep = bch->cache;
		gf_poly_logrep(bch, b, rep);
	पूर्ण

	क्रम (j = a->deg; j >= d; j--) अणु
		अगर (c[j]) अणु
			la = a_log(bch, c[j]);
			p = j-d;
			क्रम (i = 0; i < d; i++, p++) अणु
				m = rep[i];
				अगर (m >= 0)
					c[p] ^= bch->a_घात_tab[mod_s(bch,
								     m+la)];
			पूर्ण
		पूर्ण
	पूर्ण
	a->deg = d-1;
	जबतक (!c[a->deg] && a->deg)
		a->deg--;
पूर्ण

/*
 * compute polynomial Euclidean भागision quotient in GF(2^m)[X]
 */
अटल व्योम gf_poly_भाग(काष्ठा bch_control *bch, काष्ठा gf_poly *a,
			स्थिर काष्ठा gf_poly *b, काष्ठा gf_poly *q)
अणु
	अगर (a->deg >= b->deg) अणु
		q->deg = a->deg-b->deg;
		/* compute a mod b (modअगरies a) */
		gf_poly_mod(bch, a, b, शून्य);
		/* quotient is stored in upper part of polynomial a */
		स_नकल(q->c, &a->c[b->deg], (1+q->deg)*माप(अचिन्हित पूर्णांक));
	पूर्ण अन्यथा अणु
		q->deg = 0;
		q->c[0] = 0;
	पूर्ण
पूर्ण

/*
 * compute polynomial GCD (Greatest Common Divisor) in GF(2^m)[X]
 */
अटल काष्ठा gf_poly *gf_poly_gcd(काष्ठा bch_control *bch, काष्ठा gf_poly *a,
				   काष्ठा gf_poly *b)
अणु
	काष्ठा gf_poly *पंचांगp;

	dbg("gcd(%s,%s)=", gf_poly_str(a), gf_poly_str(b));

	अगर (a->deg < b->deg) अणु
		पंचांगp = b;
		b = a;
		a = पंचांगp;
	पूर्ण

	जबतक (b->deg > 0) अणु
		gf_poly_mod(bch, a, b, शून्य);
		पंचांगp = b;
		b = a;
		a = पंचांगp;
	पूर्ण

	dbg("%s\n", gf_poly_str(a));

	वापस a;
पूर्ण

/*
 * Given a polynomial f and an पूर्णांकeger k, compute Tr(a^kX) mod f
 * This is used in Berlekamp Trace algorithm क्रम splitting polynomials
 */
अटल व्योम compute_trace_bk_mod(काष्ठा bch_control *bch, पूर्णांक k,
				 स्थिर काष्ठा gf_poly *f, काष्ठा gf_poly *z,
				 काष्ठा gf_poly *out)
अणु
	स्थिर पूर्णांक m = GF_M(bch);
	पूर्णांक i, j;

	/* z contains z^2j mod f */
	z->deg = 1;
	z->c[0] = 0;
	z->c[1] = bch->a_घात_tab[k];

	out->deg = 0;
	स_रखो(out, 0, GF_POLY_SZ(f->deg));

	/* compute f log representation only once */
	gf_poly_logrep(bch, f, bch->cache);

	क्रम (i = 0; i < m; i++) अणु
		/* add a^(k*2^i)(z^(2^i) mod f) and compute (z^(2^i) mod f)^2 */
		क्रम (j = z->deg; j >= 0; j--) अणु
			out->c[j] ^= z->c[j];
			z->c[2*j] = gf_sqr(bch, z->c[j]);
			z->c[2*j+1] = 0;
		पूर्ण
		अगर (z->deg > out->deg)
			out->deg = z->deg;

		अगर (i < m-1) अणु
			z->deg *= 2;
			/* z^(2(i+1)) mod f = (z^(2^i) mod f)^2 mod f */
			gf_poly_mod(bch, z, f, bch->cache);
		पूर्ण
	पूर्ण
	जबतक (!out->c[out->deg] && out->deg)
		out->deg--;

	dbg("Tr(a^%d.X) mod f = %s\न", k, gf_poly_str(out));
पूर्ण

/*
 * factor a polynomial using Berlekamp Trace algorithm (BTA)
 */
अटल व्योम factor_polynomial(काष्ठा bch_control *bch, पूर्णांक k, काष्ठा gf_poly *f,
			      काष्ठा gf_poly **g, काष्ठा gf_poly **h)
अणु
	काष्ठा gf_poly *f2 = bch->poly_2t[0];
	काष्ठा gf_poly *q  = bch->poly_2t[1];
	काष्ठा gf_poly *tk = bch->poly_2t[2];
	काष्ठा gf_poly *z  = bch->poly_2t[3];
	काष्ठा gf_poly *gcd;

	dbg("factoring %s...\n", gf_poly_str(f));

	*g = f;
	*h = शून्य;

	/* tk = Tr(a^k.X) mod f */
	compute_trace_bk_mod(bch, k, f, z, tk);

	अगर (tk->deg > 0) अणु
		/* compute g = gcd(f, tk) (deकाष्ठाive operation) */
		gf_poly_copy(f2, f);
		gcd = gf_poly_gcd(bch, f2, tk);
		अगर (gcd->deg < f->deg) अणु
			/* compute h=f/gcd(f,tk); this will modअगरy f and q */
			gf_poly_भाग(bch, f, gcd, q);
			/* store g and h in-place (clobbering f) */
			*h = &((काष्ठा gf_poly_deg1 *)f)[gcd->deg].poly;
			gf_poly_copy(*g, gcd);
			gf_poly_copy(*h, q);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * find roots of a polynomial, using BTZ algorithm; see the beginning of this
 * file क्रम details
 */
अटल पूर्णांक find_poly_roots(काष्ठा bch_control *bch, अचिन्हित पूर्णांक k,
			   काष्ठा gf_poly *poly, अचिन्हित पूर्णांक *roots)
अणु
	पूर्णांक cnt;
	काष्ठा gf_poly *f1, *f2;

	चयन (poly->deg) अणु
		/* handle low degree polynomials with ad hoc techniques */
	हाल 1:
		cnt = find_poly_deg1_roots(bch, poly, roots);
		अवरोध;
	हाल 2:
		cnt = find_poly_deg2_roots(bch, poly, roots);
		अवरोध;
	हाल 3:
		cnt = find_poly_deg3_roots(bch, poly, roots);
		अवरोध;
	हाल 4:
		cnt = find_poly_deg4_roots(bch, poly, roots);
		अवरोध;
	शेष:
		/* factor polynomial using Berlekamp Trace Algorithm (BTA) */
		cnt = 0;
		अगर (poly->deg && (k <= GF_M(bch))) अणु
			factor_polynomial(bch, k, poly, &f1, &f2);
			अगर (f1)
				cnt += find_poly_roots(bch, k+1, f1, roots);
			अगर (f2)
				cnt += find_poly_roots(bch, k+1, f2, roots+cnt);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस cnt;
पूर्ण

#अगर defined(USE_CHIEN_SEARCH)
/*
 * exhaustive root search (Chien) implementation - not used, included only क्रम
 * reference/comparison tests
 */
अटल पूर्णांक chien_search(काष्ठा bch_control *bch, अचिन्हित पूर्णांक len,
			काष्ठा gf_poly *p, अचिन्हित पूर्णांक *roots)
अणु
	पूर्णांक m;
	अचिन्हित पूर्णांक i, j, syn, syn0, count = 0;
	स्थिर अचिन्हित पूर्णांक k = 8*len+bch->ecc_bits;

	/* use a log-based representation of polynomial */
	gf_poly_logrep(bch, p, bch->cache);
	bch->cache[p->deg] = 0;
	syn0 = gf_भाग(bch, p->c[0], p->c[p->deg]);

	क्रम (i = GF_N(bch)-k+1; i <= GF_N(bch); i++) अणु
		/* compute elp(a^i) */
		क्रम (j = 1, syn = syn0; j <= p->deg; j++) अणु
			m = bch->cache[j];
			अगर (m >= 0)
				syn ^= a_घात(bch, m+j*i);
		पूर्ण
		अगर (syn == 0) अणु
			roots[count++] = GF_N(bch)-i;
			अगर (count == p->deg)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस (count == p->deg) ? count : 0;
पूर्ण
#घोषणा find_poly_roots(_p, _k, _elp, _loc) chien_search(_p, len, _elp, _loc)
#पूर्ण_अगर /* USE_CHIEN_SEARCH */

/**
 * bch_decode - decode received codeword and find bit error locations
 * @bch:      BCH control काष्ठाure
 * @data:     received data, ignored अगर @calc_ecc is provided
 * @len:      data length in bytes, must always be provided
 * @recv_ecc: received ecc, अगर शून्य then assume it was XORed in @calc_ecc
 * @calc_ecc: calculated ecc, अगर शून्य then calc_ecc is computed from @data
 * @syn:      hw computed syndrome data (अगर शून्य, syndrome is calculated)
 * @errloc:   output array of error locations
 *
 * Returns:
 *  The number of errors found, or -EBADMSG अगर decoding failed, or -EINVAL अगर
 *  invalid parameters were provided
 *
 * Depending on the available hw BCH support and the need to compute @calc_ecc
 * separately (using bch_encode()), this function should be called with one of
 * the following parameter configurations -
 *
 * by providing @data and @recv_ecc only:
 *   bch_decode(@bch, @data, @len, @recv_ecc, शून्य, शून्य, @errloc)
 *
 * by providing @recv_ecc and @calc_ecc:
 *   bch_decode(@bch, शून्य, @len, @recv_ecc, @calc_ecc, शून्य, @errloc)
 *
 * by providing ecc = recv_ecc XOR calc_ecc:
 *   bch_decode(@bch, शून्य, @len, शून्य, ecc, शून्य, @errloc)
 *
 * by providing syndrome results @syn:
 *   bch_decode(@bch, शून्य, @len, शून्य, शून्य, @syn, @errloc)
 *
 * Once bch_decode() has successfully वापसed with a positive value, error
 * locations वापसed in array @errloc should be पूर्णांकerpreted as follows -
 *
 * अगर (errloc[n] >= 8*len), then n-th error is located in ecc (no need क्रम
 * data correction)
 *
 * अगर (errloc[n] < 8*len), then n-th error is located in data and can be
 * corrected with statement data[errloc[n]/8] ^= 1 << (errloc[n] % 8);
 *
 * Note that this function करोes not perक्रमm any data correction by itself, it
 * merely indicates error locations.
 */
पूर्णांक bch_decode(काष्ठा bch_control *bch, स्थिर uपूर्णांक8_t *data, अचिन्हित पूर्णांक len,
	       स्थिर uपूर्णांक8_t *recv_ecc, स्थिर uपूर्णांक8_t *calc_ecc,
	       स्थिर अचिन्हित पूर्णांक *syn, अचिन्हित पूर्णांक *errloc)
अणु
	स्थिर अचिन्हित पूर्णांक ecc_words = BCH_ECC_WORDS(bch);
	अचिन्हित पूर्णांक nbits;
	पूर्णांक i, err, nroots;
	uपूर्णांक32_t sum;

	/* sanity check: make sure data length can be handled */
	अगर (8*len > (bch->n-bch->ecc_bits))
		वापस -EINVAL;

	/* अगर caller करोes not provide syndromes, compute them */
	अगर (!syn) अणु
		अगर (!calc_ecc) अणु
			/* compute received data ecc पूर्णांकo an पूर्णांकernal buffer */
			अगर (!data || !recv_ecc)
				वापस -EINVAL;
			bch_encode(bch, data, len, शून्य);
		पूर्ण अन्यथा अणु
			/* load provided calculated ecc */
			load_ecc8(bch, bch->ecc_buf, calc_ecc);
		पूर्ण
		/* load received ecc or assume it was XORed in calc_ecc */
		अगर (recv_ecc) अणु
			load_ecc8(bch, bch->ecc_buf2, recv_ecc);
			/* XOR received and calculated ecc */
			क्रम (i = 0, sum = 0; i < (पूर्णांक)ecc_words; i++) अणु
				bch->ecc_buf[i] ^= bch->ecc_buf2[i];
				sum |= bch->ecc_buf[i];
			पूर्ण
			अगर (!sum)
				/* no error found */
				वापस 0;
		पूर्ण
		compute_syndromes(bch, bch->ecc_buf, bch->syn);
		syn = bch->syn;
	पूर्ण

	err = compute_error_locator_polynomial(bch, syn);
	अगर (err > 0) अणु
		nroots = find_poly_roots(bch, 1, bch->elp, errloc);
		अगर (err != nroots)
			err = -1;
	पूर्ण
	अगर (err > 0) अणु
		/* post-process raw error locations क्रम easier correction */
		nbits = (len*8)+bch->ecc_bits;
		क्रम (i = 0; i < err; i++) अणु
			अगर (errloc[i] >= nbits) अणु
				err = -1;
				अवरोध;
			पूर्ण
			errloc[i] = nbits-1-errloc[i];
			अगर (!bch->swap_bits)
				errloc[i] = (errloc[i] & ~7) |
					    (7-(errloc[i] & 7));
		पूर्ण
	पूर्ण
	वापस (err >= 0) ? err : -EBADMSG;
पूर्ण
EXPORT_SYMBOL_GPL(bch_decode);

/*
 * generate Galois field lookup tables
 */
अटल पूर्णांक build_gf_tables(काष्ठा bch_control *bch, अचिन्हित पूर्णांक poly)
अणु
	अचिन्हित पूर्णांक i, x = 1;
	स्थिर अचिन्हित पूर्णांक k = 1 << deg(poly);

	/* primitive polynomial must be of degree m */
	अगर (k != (1u << GF_M(bch)))
		वापस -1;

	क्रम (i = 0; i < GF_N(bch); i++) अणु
		bch->a_घात_tab[i] = x;
		bch->a_log_tab[x] = i;
		अगर (i && (x == 1))
			/* polynomial is not primitive (a^i=1 with 0<i<2^m-1) */
			वापस -1;
		x <<= 1;
		अगर (x & k)
			x ^= poly;
	पूर्ण
	bch->a_घात_tab[GF_N(bch)] = 1;
	bch->a_log_tab[0] = 0;

	वापस 0;
पूर्ण

/*
 * compute generator polynomial reमुख्यder tables क्रम fast encoding
 */
अटल व्योम build_mod8_tables(काष्ठा bch_control *bch, स्थिर uपूर्णांक32_t *g)
अणु
	पूर्णांक i, j, b, d;
	uपूर्णांक32_t data, hi, lo, *tab;
	स्थिर पूर्णांक l = BCH_ECC_WORDS(bch);
	स्थिर पूर्णांक plen = DIV_ROUND_UP(bch->ecc_bits+1, 32);
	स्थिर पूर्णांक ecclen = DIV_ROUND_UP(bch->ecc_bits, 32);

	स_रखो(bch->mod8_tab, 0, 4*256*l*माप(*bch->mod8_tab));

	क्रम (i = 0; i < 256; i++) अणु
		/* p(X)=i is a small polynomial of weight <= 8 */
		क्रम (b = 0; b < 4; b++) अणु
			/* we want to compute (p(X).X^(8*b+deg(g))) mod g(X) */
			tab = bch->mod8_tab + (b*256+i)*l;
			data = i << (8*b);
			जबतक (data) अणु
				d = deg(data);
				/* subtract X^d.g(X) from p(X).X^(8*b+deg(g)) */
				data ^= g[0] >> (31-d);
				क्रम (j = 0; j < ecclen; j++) अणु
					hi = (d < 31) ? g[j] << (d+1) : 0;
					lo = (j+1 < plen) ?
						g[j+1] >> (31-d) : 0;
					tab[j] ^= hi|lo;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * build a base क्रम factoring degree 2 polynomials
 */
अटल पूर्णांक build_deg2_base(काष्ठा bch_control *bch)
अणु
	स्थिर पूर्णांक m = GF_M(bch);
	पूर्णांक i, j, r;
	अचिन्हित पूर्णांक sum, x, y, reमुख्यing, ak = 0, xi[BCH_MAX_M];

	/* find k s.t. Tr(a^k) = 1 and 0 <= k < m */
	क्रम (i = 0; i < m; i++) अणु
		क्रम (j = 0, sum = 0; j < m; j++)
			sum ^= a_घात(bch, i*(1 << j));

		अगर (sum) अणु
			ak = bch->a_घात_tab[i];
			अवरोध;
		पूर्ण
	पूर्ण
	/* find xi, i=0..m-1 such that xi^2+xi = a^i+Tr(a^i).a^k */
	reमुख्यing = m;
	स_रखो(xi, 0, माप(xi));

	क्रम (x = 0; (x <= GF_N(bch)) && reमुख्यing; x++) अणु
		y = gf_sqr(bch, x)^x;
		क्रम (i = 0; i < 2; i++) अणु
			r = a_log(bch, y);
			अगर (y && (r < m) && !xi[r]) अणु
				bch->xi_tab[r] = x;
				xi[r] = 1;
				reमुख्यing--;
				dbg("x%d = %x\n", r, x);
				अवरोध;
			पूर्ण
			y ^= ak;
		पूर्ण
	पूर्ण
	/* should not happen but check anyway */
	वापस reमुख्यing ? -1 : 0;
पूर्ण

अटल व्योम *bch_alloc(माप_प्रकार size, पूर्णांक *err)
अणु
	व्योम *ptr;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	अगर (ptr == शून्य)
		*err = 1;
	वापस ptr;
पूर्ण

/*
 * compute generator polynomial क्रम given (m,t) parameters.
 */
अटल uपूर्णांक32_t *compute_generator_polynomial(काष्ठा bch_control *bch)
अणु
	स्थिर अचिन्हित पूर्णांक m = GF_M(bch);
	स्थिर अचिन्हित पूर्णांक t = GF_T(bch);
	पूर्णांक n, err = 0;
	अचिन्हित पूर्णांक i, j, nbits, r, word, *roots;
	काष्ठा gf_poly *g;
	uपूर्णांक32_t *genpoly;

	g = bch_alloc(GF_POLY_SZ(m*t), &err);
	roots = bch_alloc((bch->n+1)*माप(*roots), &err);
	genpoly = bch_alloc(DIV_ROUND_UP(m*t+1, 32)*माप(*genpoly), &err);

	अगर (err) अणु
		kमुक्त(genpoly);
		genpoly = शून्य;
		जाओ finish;
	पूर्ण

	/* क्रमागतerate all roots of g(X) */
	स_रखो(roots , 0, (bch->n+1)*माप(*roots));
	क्रम (i = 0; i < t; i++) अणु
		क्रम (j = 0, r = 2*i+1; j < m; j++) अणु
			roots[r] = 1;
			r = mod_s(bch, 2*r);
		पूर्ण
	पूर्ण
	/* build generator polynomial g(X) */
	g->deg = 0;
	g->c[0] = 1;
	क्रम (i = 0; i < GF_N(bch); i++) अणु
		अगर (roots[i]) अणु
			/* multiply g(X) by (X+root) */
			r = bch->a_घात_tab[i];
			g->c[g->deg+1] = 1;
			क्रम (j = g->deg; j > 0; j--)
				g->c[j] = gf_mul(bch, g->c[j], r)^g->c[j-1];

			g->c[0] = gf_mul(bch, g->c[0], r);
			g->deg++;
		पूर्ण
	पूर्ण
	/* store left-justअगरied binary representation of g(X) */
	n = g->deg+1;
	i = 0;

	जबतक (n > 0) अणु
		nbits = (n > 32) ? 32 : n;
		क्रम (j = 0, word = 0; j < nbits; j++) अणु
			अगर (g->c[n-1-j])
				word |= 1u << (31-j);
		पूर्ण
		genpoly[i++] = word;
		n -= nbits;
	पूर्ण
	bch->ecc_bits = g->deg;

finish:
	kमुक्त(g);
	kमुक्त(roots);

	वापस genpoly;
पूर्ण

/**
 * bch_init - initialize a BCH encoder/decoder
 * @m:          Galois field order, should be in the range 5-15
 * @t:          maximum error correction capability, in bits
 * @prim_poly:  user-provided primitive polynomial (or 0 to use शेष)
 * @swap_bits:  swap bits within data and syndrome bytes
 *
 * Returns:
 *  a newly allocated BCH control काष्ठाure अगर successful, शून्य otherwise
 *
 * This initialization can take some समय, as lookup tables are built क्रम fast
 * encoding/decoding; make sure not to call this function from a समय critical
 * path. Usually, bch_init() should be called on module/driver init and
 * bch_मुक्त() should be called to release memory on निकास.
 *
 * You may provide your own primitive polynomial of degree @m in argument
 * @prim_poly, or let bch_init() use its शेष polynomial.
 *
 * Once bch_init() has successfully वापसed a poपूर्णांकer to a newly allocated
 * BCH control काष्ठाure, ecc length in bytes is given by member @ecc_bytes of
 * the काष्ठाure.
 */
काष्ठा bch_control *bch_init(पूर्णांक m, पूर्णांक t, अचिन्हित पूर्णांक prim_poly,
			     bool swap_bits)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक i, words;
	uपूर्णांक32_t *genpoly;
	काष्ठा bch_control *bch = शून्य;

	स्थिर पूर्णांक min_m = 5;

	/* शेष primitive polynomials */
	अटल स्थिर अचिन्हित पूर्णांक prim_poly_tab[] = अणु
		0x25, 0x43, 0x83, 0x11d, 0x211, 0x409, 0x805, 0x1053, 0x201b,
		0x402b, 0x8003,
	पूर्ण;

#अगर defined(CONFIG_BCH_CONST_PARAMS)
	अगर ((m != (CONFIG_BCH_CONST_M)) || (t != (CONFIG_BCH_CONST_T))) अणु
		prपूर्णांकk(KERN_ERR "bch encoder/decoder was configured to support "
		       "parameters m=%d, t=%d only!\n",
		       CONFIG_BCH_CONST_M, CONFIG_BCH_CONST_T);
		जाओ fail;
	पूर्ण
#पूर्ण_अगर
	अगर ((m < min_m) || (m > BCH_MAX_M))
		/*
		 * values of m greater than 15 are not currently supported;
		 * supporting m > 15 would require changing table base type
		 * (uपूर्णांक16_t) and a small patch in matrix transposition
		 */
		जाओ fail;

	अगर (t > BCH_MAX_T)
		/*
		 * we can support larger than 64 bits अगर necessary, at the
		 * cost of higher stack usage.
		 */
		जाओ fail;

	/* sanity checks */
	अगर ((t < 1) || (m*t >= ((1 << m)-1)))
		/* invalid t value */
		जाओ fail;

	/* select a primitive polynomial क्रम generating GF(2^m) */
	अगर (prim_poly == 0)
		prim_poly = prim_poly_tab[m-min_m];

	bch = kzalloc(माप(*bch), GFP_KERNEL);
	अगर (bch == शून्य)
		जाओ fail;

	bch->m = m;
	bch->t = t;
	bch->n = (1 << m)-1;
	words  = DIV_ROUND_UP(m*t, 32);
	bch->ecc_bytes = DIV_ROUND_UP(m*t, 8);
	bch->a_घात_tab = bch_alloc((1+bch->n)*माप(*bch->a_घात_tab), &err);
	bch->a_log_tab = bch_alloc((1+bch->n)*माप(*bch->a_log_tab), &err);
	bch->mod8_tab  = bch_alloc(words*1024*माप(*bch->mod8_tab), &err);
	bch->ecc_buf   = bch_alloc(words*माप(*bch->ecc_buf), &err);
	bch->ecc_buf2  = bch_alloc(words*माप(*bch->ecc_buf2), &err);
	bch->xi_tab    = bch_alloc(m*माप(*bch->xi_tab), &err);
	bch->syn       = bch_alloc(2*t*माप(*bch->syn), &err);
	bch->cache     = bch_alloc(2*t*माप(*bch->cache), &err);
	bch->elp       = bch_alloc((t+1)*माप(काष्ठा gf_poly_deg1), &err);
	bch->swap_bits = swap_bits;

	क्रम (i = 0; i < ARRAY_SIZE(bch->poly_2t); i++)
		bch->poly_2t[i] = bch_alloc(GF_POLY_SZ(2*t), &err);

	अगर (err)
		जाओ fail;

	err = build_gf_tables(bch, prim_poly);
	अगर (err)
		जाओ fail;

	/* use generator polynomial क्रम computing encoding tables */
	genpoly = compute_generator_polynomial(bch);
	अगर (genpoly == शून्य)
		जाओ fail;

	build_mod8_tables(bch, genpoly);
	kमुक्त(genpoly);

	err = build_deg2_base(bch);
	अगर (err)
		जाओ fail;

	वापस bch;

fail:
	bch_मुक्त(bch);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(bch_init);

/**
 *  bch_मुक्त - मुक्त the BCH control काष्ठाure
 *  @bch:    BCH control काष्ठाure to release
 */
व्योम bch_मुक्त(काष्ठा bch_control *bch)
अणु
	अचिन्हित पूर्णांक i;

	अगर (bch) अणु
		kमुक्त(bch->a_घात_tab);
		kमुक्त(bch->a_log_tab);
		kमुक्त(bch->mod8_tab);
		kमुक्त(bch->ecc_buf);
		kमुक्त(bch->ecc_buf2);
		kमुक्त(bch->xi_tab);
		kमुक्त(bch->syn);
		kमुक्त(bch->cache);
		kमुक्त(bch->elp);

		क्रम (i = 0; i < ARRAY_SIZE(bch->poly_2t); i++)
			kमुक्त(bch->poly_2t[i]);

		kमुक्त(bch);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bch_मुक्त);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Djelic <ivan.djelic@parrot.com>");
MODULE_DESCRIPTION("Binary BCH encoder/decoder");
