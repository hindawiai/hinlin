<शैली गुरु>
/*
 * VMAC: Message Authentication Code using Universal Hashing
 *
 * Reference: https://tools.ietf.org/hपंचांगl/draft-krovetz-vmac-01
 *
 * Copyright (c) 2009, Intel Corporation.
 * Copyright (c) 2018, Google Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 */

/*
 * Derived from:
 *	VMAC and VHASH Implementation by Ted Krovetz (tdk@acm.org) and Wei Dai.
 *	This implementation is herby placed in the खुला करोमुख्य.
 *	The authors offers no warranty. Use at your own risk.
 *	Last modअगरied: 17 APR 08, 1700 PDT
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

/*
 * User definable settings.
 */
#घोषणा VMAC_TAG_LEN	64
#घोषणा VMAC_KEY_SIZE	128/* Must be 128, 192 or 256			*/
#घोषणा VMAC_KEY_LEN	(VMAC_KEY_SIZE/8)
#घोषणा VMAC_NHBYTES	128/* Must 2^i क्रम any 3 < i < 13 Standard = 128*/
#घोषणा VMAC_NONCEBYTES	16

/* per-transक्रमm (per-key) context */
काष्ठा vmac_tfm_ctx अणु
	काष्ठा crypto_cipher *cipher;
	u64 nhkey[(VMAC_NHBYTES/8)+2*(VMAC_TAG_LEN/64-1)];
	u64 polykey[2*VMAC_TAG_LEN/64];
	u64 l3key[2*VMAC_TAG_LEN/64];
पूर्ण;

/* per-request context */
काष्ठा vmac_desc_ctx अणु
	जोड़ अणु
		u8 partial[VMAC_NHBYTES];	/* partial block */
		__le64 partial_words[VMAC_NHBYTES / 8];
	पूर्ण;
	अचिन्हित पूर्णांक partial_size;	/* size of the partial block */
	bool first_block_processed;
	u64 polyपंचांगp[2*VMAC_TAG_LEN/64];	/* running total of L2-hash */
	जोड़ अणु
		u8 bytes[VMAC_NONCEBYTES];
		__be64 pads[VMAC_NONCEBYTES / 8];
	पूर्ण nonce;
	अचिन्हित पूर्णांक nonce_size; /* nonce bytes filled so far */
पूर्ण;

/*
 * Constants and masks
 */
#घोषणा UINT64_C(x) x##ULL
अटल स्थिर u64 p64   = UINT64_C(0xfffffffffffffeff);	/* 2^64 - 257 prime  */
अटल स्थिर u64 m62   = UINT64_C(0x3fffffffffffffff);	/* 62-bit mask       */
अटल स्थिर u64 m63   = UINT64_C(0x7fffffffffffffff);	/* 63-bit mask       */
अटल स्थिर u64 m64   = UINT64_C(0xffffffffffffffff);	/* 64-bit mask       */
अटल स्थिर u64 mpoly = UINT64_C(0x1fffffff1fffffff);	/* Poly key mask     */

#घोषणा pe64_to_cpup le64_to_cpup		/* Prefer little endian */

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा INDEX_HIGH 1
#घोषणा INDEX_LOW 0
#अन्यथा
#घोषणा INDEX_HIGH 0
#घोषणा INDEX_LOW 1
#पूर्ण_अगर

/*
 * The following routines are used in this implementation. They are
 * written via macros to simulate zero-overhead call-by-reference.
 *
 * MUL64: 64x64->128-bit multiplication
 * PMUL64: assumes top bits cleared on inमाला_दो
 * ADD128: 128x128->128-bit addition
 */

#घोषणा ADD128(rh, rl, ih, il)						\
	करो अणु								\
		u64 _il = (il);						\
		(rl) += (_il);						\
		अगर ((rl) < (_il))					\
			(rh)++;						\
		(rh) += (ih);						\
	पूर्ण जबतक (0)

#घोषणा MUL32(i1, i2)	((u64)(u32)(i1)*(u32)(i2))

#घोषणा PMUL64(rh, rl, i1, i2)	/* Assumes m करोesn't overflow */	\
	करो अणु								\
		u64 _i1 = (i1), _i2 = (i2);				\
		u64 m = MUL32(_i1, _i2>>32) + MUL32(_i1>>32, _i2);	\
		rh = MUL32(_i1>>32, _i2>>32);				\
		rl = MUL32(_i1, _i2);					\
		ADD128(rh, rl, (m >> 32), (m << 32));			\
	पूर्ण जबतक (0)

#घोषणा MUL64(rh, rl, i1, i2)						\
	करो अणु								\
		u64 _i1 = (i1), _i2 = (i2);				\
		u64 m1 = MUL32(_i1, _i2>>32);				\
		u64 m2 = MUL32(_i1>>32, _i2);				\
		rh = MUL32(_i1>>32, _i2>>32);				\
		rl = MUL32(_i1, _i2);					\
		ADD128(rh, rl, (m1 >> 32), (m1 << 32));			\
		ADD128(rh, rl, (m2 >> 32), (m2 << 32));			\
	पूर्ण जबतक (0)

/*
 * For highest perक्रमmance the L1 NH and L2 polynomial hashes should be
 * carefully implemented to take advantage of one's target architecture.
 * Here these two hash functions are defined multiple समय; once क्रम
 * 64-bit architectures, once क्रम 32-bit SSE2 architectures, and once
 * क्रम the rest (32-bit) architectures.
 * For each, nh_16 *must* be defined (works on multiples of 16 bytes).
 * Optionally, nh_vmac_nhbytes can be defined (क्रम multiples of
 * VMAC_NHBYTES), and nh_16_2 and nh_vmac_nhbytes_2 (versions that करो two
 * NH computations at once).
 */

#अगर_घोषित CONFIG_64BIT

#घोषणा nh_16(mp, kp, nw, rh, rl)					\
	करो अणु								\
		पूर्णांक i; u64 th, tl;					\
		rh = rl = 0;						\
		क्रम (i = 0; i < nw; i += 2) अणु				\
			MUL64(th, tl, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(rh, rl, th, tl);				\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा nh_16_2(mp, kp, nw, rh, rl, rh1, rl1)				\
	करो अणु								\
		पूर्णांक i; u64 th, tl;					\
		rh1 = rl1 = rh = rl = 0;				\
		क्रम (i = 0; i < nw; i += 2) अणु				\
			MUL64(th, tl, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+3]);	\
			ADD128(rh1, rl1, th, tl);			\
		पूर्ण							\
	पूर्ण जबतक (0)

#अगर (VMAC_NHBYTES >= 64) /* These versions करो 64-bytes of message at a समय */
#घोषणा nh_vmac_nhbytes(mp, kp, nw, rh, rl)				\
	करो अणु								\
		पूर्णांक i; u64 th, tl;					\
		rh = rl = 0;						\
		क्रम (i = 0; i < nw; i += 8) अणु				\
			MUL64(th, tl, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i+2)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+3)+(kp)[i+3]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i+4)+(kp)[i+4],	\
				pe64_to_cpup((mp)+i+5)+(kp)[i+5]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i+6)+(kp)[i+6],	\
				pe64_to_cpup((mp)+i+7)+(kp)[i+7]);	\
			ADD128(rh, rl, th, tl);				\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा nh_vmac_nhbytes_2(mp, kp, nw, rh, rl, rh1, rl1)			\
	करो अणु								\
		पूर्णांक i; u64 th, tl;					\
		rh1 = rl1 = rh = rl = 0;				\
		क्रम (i = 0; i < nw; i += 8) अणु				\
			MUL64(th, tl, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+3]);	\
			ADD128(rh1, rl1, th, tl);			\
			MUL64(th, tl, pe64_to_cpup((mp)+i+2)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+3)+(kp)[i+3]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i+2)+(kp)[i+4],	\
				pe64_to_cpup((mp)+i+3)+(kp)[i+5]);	\
			ADD128(rh1, rl1, th, tl);			\
			MUL64(th, tl, pe64_to_cpup((mp)+i+4)+(kp)[i+4],	\
				pe64_to_cpup((mp)+i+5)+(kp)[i+5]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i+4)+(kp)[i+6],	\
				pe64_to_cpup((mp)+i+5)+(kp)[i+7]);	\
			ADD128(rh1, rl1, th, tl);			\
			MUL64(th, tl, pe64_to_cpup((mp)+i+6)+(kp)[i+6],	\
				pe64_to_cpup((mp)+i+7)+(kp)[i+7]);	\
			ADD128(rh, rl, th, tl);				\
			MUL64(th, tl, pe64_to_cpup((mp)+i+6)+(kp)[i+8],	\
				pe64_to_cpup((mp)+i+7)+(kp)[i+9]);	\
			ADD128(rh1, rl1, th, tl);			\
		पूर्ण							\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा poly_step(ah, al, kh, kl, mh, ml)				\
	करो अणु								\
		u64 t1h, t1l, t2h, t2l, t3h, t3l, z = 0;		\
		/* compute ab*cd, put bd पूर्णांकo result रेजिस्टरs */	\
		PMUL64(t3h, t3l, al, kh);				\
		PMUL64(t2h, t2l, ah, kl);				\
		PMUL64(t1h, t1l, ah, 2*kh);				\
		PMUL64(ah, al, al, kl);					\
		/* add 2 * ac to result */				\
		ADD128(ah, al, t1h, t1l);				\
		/* add together ad + bc */				\
		ADD128(t2h, t2l, t3h, t3l);				\
		/* now (ah,al), (t2l,2*t2h) need summing */		\
		/* first add the high रेजिस्टरs, carrying पूर्णांकo t2h */	\
		ADD128(t2h, ah, z, t2l);				\
		/* द्विगुन t2h and add top bit of ah */			\
		t2h = 2 * t2h + (ah >> 63);				\
		ah &= m63;						\
		/* now add the low रेजिस्टरs */				\
		ADD128(ah, al, mh, ml);					\
		ADD128(ah, al, z, t2h);					\
	पूर्ण जबतक (0)

#अन्यथा /* ! CONFIG_64BIT */

#अगर_अघोषित nh_16
#घोषणा nh_16(mp, kp, nw, rh, rl)					\
	करो अणु								\
		u64 t1, t2, m1, m2, t;					\
		पूर्णांक i;							\
		rh = rl = t = 0;					\
		क्रम (i = 0; i < nw; i += 2)  अणु				\
			t1 = pe64_to_cpup(mp+i) + kp[i];		\
			t2 = pe64_to_cpup(mp+i+1) + kp[i+1];		\
			m2 = MUL32(t1 >> 32, t2);			\
			m1 = MUL32(t1, t2 >> 32);			\
			ADD128(rh, rl, MUL32(t1 >> 32, t2 >> 32),	\
				MUL32(t1, t2));				\
			rh += (u64)(u32)(m1 >> 32)			\
				+ (u32)(m2 >> 32);			\
			t += (u64)(u32)m1 + (u32)m2;			\
		पूर्ण							\
		ADD128(rh, rl, (t >> 32), (t << 32));			\
	पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम poly_step_func(u64 *ahi, u64 *alo,
			स्थिर u64 *kh, स्थिर u64 *kl,
			स्थिर u64 *mh, स्थिर u64 *ml)
अणु
#घोषणा a0 (*(((u32 *)alo)+INDEX_LOW))
#घोषणा a1 (*(((u32 *)alo)+INDEX_HIGH))
#घोषणा a2 (*(((u32 *)ahi)+INDEX_LOW))
#घोषणा a3 (*(((u32 *)ahi)+INDEX_HIGH))
#घोषणा k0 (*(((u32 *)kl)+INDEX_LOW))
#घोषणा k1 (*(((u32 *)kl)+INDEX_HIGH))
#घोषणा k2 (*(((u32 *)kh)+INDEX_LOW))
#घोषणा k3 (*(((u32 *)kh)+INDEX_HIGH))

	u64 p, q, t;
	u32 t2;

	p = MUL32(a3, k3);
	p += p;
	p += *(u64 *)mh;
	p += MUL32(a0, k2);
	p += MUL32(a1, k1);
	p += MUL32(a2, k0);
	t = (u32)(p);
	p >>= 32;
	p += MUL32(a0, k3);
	p += MUL32(a1, k2);
	p += MUL32(a2, k1);
	p += MUL32(a3, k0);
	t |= ((u64)((u32)p & 0x7fffffff)) << 32;
	p >>= 31;
	p += (u64)(((u32 *)ml)[INDEX_LOW]);
	p += MUL32(a0, k0);
	q =  MUL32(a1, k3);
	q += MUL32(a2, k2);
	q += MUL32(a3, k1);
	q += q;
	p += q;
	t2 = (u32)(p);
	p >>= 32;
	p += (u64)(((u32 *)ml)[INDEX_HIGH]);
	p += MUL32(a0, k1);
	p += MUL32(a1, k0);
	q =  MUL32(a2, k3);
	q += MUL32(a3, k2);
	q += q;
	p += q;
	*(u64 *)(alo) = (p << 32) | t2;
	p >>= 32;
	*(u64 *)(ahi) = p + t;

#अघोषित a0
#अघोषित a1
#अघोषित a2
#अघोषित a3
#अघोषित k0
#अघोषित k1
#अघोषित k2
#अघोषित k3
पूर्ण

#घोषणा poly_step(ah, al, kh, kl, mh, ml)				\
	poly_step_func(&(ah), &(al), &(kh), &(kl), &(mh), &(ml))

#पूर्ण_अगर  /* end of specialized NH and poly definitions */

/* At least nh_16 is defined. Defined others as needed here */
#अगर_अघोषित nh_16_2
#घोषणा nh_16_2(mp, kp, nw, rh, rl, rh2, rl2)				\
	करो अणु 								\
		nh_16(mp, kp, nw, rh, rl);				\
		nh_16(mp, ((kp)+2), nw, rh2, rl2);			\
	पूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_अघोषित nh_vmac_nhbytes
#घोषणा nh_vmac_nhbytes(mp, kp, nw, rh, rl)				\
	nh_16(mp, kp, nw, rh, rl)
#पूर्ण_अगर
#अगर_अघोषित nh_vmac_nhbytes_2
#घोषणा nh_vmac_nhbytes_2(mp, kp, nw, rh, rl, rh2, rl2)			\
	करो अणु								\
		nh_vmac_nhbytes(mp, kp, nw, rh, rl);			\
		nh_vmac_nhbytes(mp, ((kp)+2), nw, rh2, rl2);		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

अटल u64 l3hash(u64 p1, u64 p2, u64 k1, u64 k2, u64 len)
अणु
	u64 rh, rl, t, z = 0;

	/* fully reduce (p1,p2)+(len,0) mod p127 */
	t = p1 >> 63;
	p1 &= m63;
	ADD128(p1, p2, len, t);
	/* At this poपूर्णांक, (p1,p2) is at most 2^127+(len<<64) */
	t = (p1 > m63) + ((p1 == m63) && (p2 == m64));
	ADD128(p1, p2, z, t);
	p1 &= m63;

	/* compute (p1,p2)/(2^64-2^32) and (p1,p2)%(2^64-2^32) */
	t = p1 + (p2 >> 32);
	t += (t >> 32);
	t += (u32)t > 0xfffffffeu;
	p1 += (t >> 32);
	p2 += (p1 << 32);

	/* compute (p1+k1)%p64 and (p2+k2)%p64 */
	p1 += k1;
	p1 += (0 - (p1 < k1)) & 257;
	p2 += k2;
	p2 += (0 - (p2 < k2)) & 257;

	/* compute (p1+k1)*(p2+k2)%p64 */
	MUL64(rh, rl, p1, p2);
	t = rh >> 56;
	ADD128(t, rl, z, rh);
	rh <<= 8;
	ADD128(t, rl, z, rh);
	t += t << 8;
	rl += t;
	rl += (0 - (rl < t)) & 257;
	rl += (0 - (rl > p64-1)) & 257;
	वापस rl;
पूर्ण

/* L1 and L2-hash one or more VMAC_NHBYTES-byte blocks */
अटल व्योम vhash_blocks(स्थिर काष्ठा vmac_tfm_ctx *tctx,
			 काष्ठा vmac_desc_ctx *dctx,
			 स्थिर __le64 *mptr, अचिन्हित पूर्णांक blocks)
अणु
	स्थिर u64 *kptr = tctx->nhkey;
	स्थिर u64 pkh = tctx->polykey[0];
	स्थिर u64 pkl = tctx->polykey[1];
	u64 ch = dctx->polyपंचांगp[0];
	u64 cl = dctx->polyपंचांगp[1];
	u64 rh, rl;

	अगर (!dctx->first_block_processed) अणु
		dctx->first_block_processed = true;
		nh_vmac_nhbytes(mptr, kptr, VMAC_NHBYTES/8, rh, rl);
		rh &= m62;
		ADD128(ch, cl, rh, rl);
		mptr += (VMAC_NHBYTES/माप(u64));
		blocks--;
	पूर्ण

	जबतक (blocks--) अणु
		nh_vmac_nhbytes(mptr, kptr, VMAC_NHBYTES/8, rh, rl);
		rh &= m62;
		poly_step(ch, cl, pkh, pkl, rh, rl);
		mptr += (VMAC_NHBYTES/माप(u64));
	पूर्ण

	dctx->polyपंचांगp[0] = ch;
	dctx->polyपंचांगp[1] = cl;
पूर्ण

अटल पूर्णांक vmac_setkey(काष्ठा crypto_shash *tfm,
		       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा vmac_tfm_ctx *tctx = crypto_shash_ctx(tfm);
	__be64 out[2];
	u8 in[16] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (keylen != VMAC_KEY_LEN)
		वापस -EINVAL;

	err = crypto_cipher_setkey(tctx->cipher, key, keylen);
	अगर (err)
		वापस err;

	/* Fill nh key */
	in[0] = 0x80;
	क्रम (i = 0; i < ARRAY_SIZE(tctx->nhkey); i += 2) अणु
		crypto_cipher_encrypt_one(tctx->cipher, (u8 *)out, in);
		tctx->nhkey[i] = be64_to_cpu(out[0]);
		tctx->nhkey[i+1] = be64_to_cpu(out[1]);
		in[15]++;
	पूर्ण

	/* Fill poly key */
	in[0] = 0xC0;
	in[15] = 0;
	क्रम (i = 0; i < ARRAY_SIZE(tctx->polykey); i += 2) अणु
		crypto_cipher_encrypt_one(tctx->cipher, (u8 *)out, in);
		tctx->polykey[i] = be64_to_cpu(out[0]) & mpoly;
		tctx->polykey[i+1] = be64_to_cpu(out[1]) & mpoly;
		in[15]++;
	पूर्ण

	/* Fill ip key */
	in[0] = 0xE0;
	in[15] = 0;
	क्रम (i = 0; i < ARRAY_SIZE(tctx->l3key); i += 2) अणु
		करो अणु
			crypto_cipher_encrypt_one(tctx->cipher, (u8 *)out, in);
			tctx->l3key[i] = be64_to_cpu(out[0]);
			tctx->l3key[i+1] = be64_to_cpu(out[1]);
			in[15]++;
		पूर्ण जबतक (tctx->l3key[i] >= p64 || tctx->l3key[i+1] >= p64);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmac_init(काष्ठा shash_desc *desc)
अणु
	स्थिर काष्ठा vmac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा vmac_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->partial_size = 0;
	dctx->first_block_processed = false;
	स_नकल(dctx->polyपंचांगp, tctx->polykey, माप(dctx->polyपंचांगp));
	dctx->nonce_size = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vmac_update(काष्ठा shash_desc *desc, स्थिर u8 *p, अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा vmac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा vmac_desc_ctx *dctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक n;

	/* Nonce is passed as first VMAC_NONCEBYTES bytes of data */
	अगर (dctx->nonce_size < VMAC_NONCEBYTES) अणु
		n = min(len, VMAC_NONCEBYTES - dctx->nonce_size);
		स_नकल(&dctx->nonce.bytes[dctx->nonce_size], p, n);
		dctx->nonce_size += n;
		p += n;
		len -= n;
	पूर्ण

	अगर (dctx->partial_size) अणु
		n = min(len, VMAC_NHBYTES - dctx->partial_size);
		स_नकल(&dctx->partial[dctx->partial_size], p, n);
		dctx->partial_size += n;
		p += n;
		len -= n;
		अगर (dctx->partial_size == VMAC_NHBYTES) अणु
			vhash_blocks(tctx, dctx, dctx->partial_words, 1);
			dctx->partial_size = 0;
		पूर्ण
	पूर्ण

	अगर (len >= VMAC_NHBYTES) अणु
		n = round_करोwn(len, VMAC_NHBYTES);
		/* TODO: 'p' may be misaligned here */
		vhash_blocks(tctx, dctx, (स्थिर __le64 *)p, n / VMAC_NHBYTES);
		p += n;
		len -= n;
	पूर्ण

	अगर (len) अणु
		स_नकल(dctx->partial, p, len);
		dctx->partial_size = len;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 vhash_final(स्थिर काष्ठा vmac_tfm_ctx *tctx,
		       काष्ठा vmac_desc_ctx *dctx)
अणु
	अचिन्हित पूर्णांक partial = dctx->partial_size;
	u64 ch = dctx->polyपंचांगp[0];
	u64 cl = dctx->polyपंचांगp[1];

	/* L1 and L2-hash the final block अगर needed */
	अगर (partial) अणु
		/* Zero-pad to next 128-bit boundary */
		अचिन्हित पूर्णांक n = round_up(partial, 16);
		u64 rh, rl;

		स_रखो(&dctx->partial[partial], 0, n - partial);
		nh_16(dctx->partial_words, tctx->nhkey, n / 8, rh, rl);
		rh &= m62;
		अगर (dctx->first_block_processed)
			poly_step(ch, cl, tctx->polykey[0], tctx->polykey[1],
				  rh, rl);
		अन्यथा
			ADD128(ch, cl, rh, rl);
	पूर्ण

	/* L3-hash the 128-bit output of L2-hash */
	वापस l3hash(ch, cl, tctx->l3key[0], tctx->l3key[1], partial * 8);
पूर्ण

अटल पूर्णांक vmac_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	स्थिर काष्ठा vmac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा vmac_desc_ctx *dctx = shash_desc_ctx(desc);
	पूर्णांक index;
	u64 hash, pad;

	अगर (dctx->nonce_size != VMAC_NONCEBYTES)
		वापस -EINVAL;

	/*
	 * The VMAC specअगरication requires a nonce at least 1 bit लघुer than
	 * the block cipher's block length, so we actually only accept a 127-bit
	 * nonce.  We define the unused bit to be the first one and require that
	 * it be 0, so the needed prepending of a 0 bit is implicit.
	 */
	अगर (dctx->nonce.bytes[0] & 0x80)
		वापस -EINVAL;

	/* Finish calculating the VHASH of the message */
	hash = vhash_final(tctx, dctx);

	/* Generate pseuकरोअक्रमom pad by encrypting the nonce */
	BUILD_BUG_ON(VMAC_NONCEBYTES != 2 * (VMAC_TAG_LEN / 8));
	index = dctx->nonce.bytes[VMAC_NONCEBYTES - 1] & 1;
	dctx->nonce.bytes[VMAC_NONCEBYTES - 1] &= ~1;
	crypto_cipher_encrypt_one(tctx->cipher, dctx->nonce.bytes,
				  dctx->nonce.bytes);
	pad = be64_to_cpu(dctx->nonce.pads[index]);

	/* The VMAC is the sum of VHASH and the pseuकरोअक्रमom pad */
	put_unaligned_be64(hash + pad, out);
	वापस 0;
पूर्ण

अटल पूर्णांक vmac_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_instance *inst = crypto_tfm_alg_instance(tfm);
	काष्ठा crypto_cipher_spawn *spawn = crypto_instance_ctx(inst);
	काष्ठा vmac_tfm_ctx *tctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_cipher *cipher;

	cipher = crypto_spawn_cipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	tctx->cipher = cipher;
	वापस 0;
पूर्ण

अटल व्योम vmac_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा vmac_tfm_ctx *tctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_cipher(tctx->cipher);
पूर्ण

अटल पूर्णांक vmac_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा shash_instance *inst;
	काष्ठा crypto_cipher_spawn *spawn;
	काष्ठा crypto_alg *alg;
	u32 mask;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SHASH, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	spawn = shash_instance_ctx(inst);

	err = crypto_grab_cipher(spawn, shash_crypto_instance(inst),
				 crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	alg = crypto_spawn_cipher_alg(spawn);

	err = -EINVAL;
	अगर (alg->cra_blocksize != VMAC_NONCEBYTES)
		जाओ err_मुक्त_inst;

	err = crypto_inst_setname(shash_crypto_instance(inst), पंचांगpl->name, alg);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->cra_priority;
	inst->alg.base.cra_blocksize = alg->cra_blocksize;
	inst->alg.base.cra_alignmask = alg->cra_alignmask;

	inst->alg.base.cra_ctxsize = माप(काष्ठा vmac_tfm_ctx);
	inst->alg.base.cra_init = vmac_init_tfm;
	inst->alg.base.cra_निकास = vmac_निकास_tfm;

	inst->alg.descsize = माप(काष्ठा vmac_desc_ctx);
	inst->alg.digestsize = VMAC_TAG_LEN / 8;
	inst->alg.init = vmac_init;
	inst->alg.update = vmac_update;
	inst->alg.final = vmac_final;
	inst->alg.setkey = vmac_setkey;

	inst->मुक्त = shash_मुक्त_singlespawn_instance;

	err = shash_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		shash_मुक्त_singlespawn_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा vmac64_पंचांगpl = अणु
	.name = "vmac64",
	.create = vmac_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init vmac_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&vmac64_पंचांगpl);
पूर्ण

अटल व्योम __निकास vmac_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&vmac64_पंचांगpl);
पूर्ण

subsys_initcall(vmac_module_init);
module_निकास(vmac_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VMAC hash algorithm");
MODULE_ALIAS_CRYPTO("vmac64");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
