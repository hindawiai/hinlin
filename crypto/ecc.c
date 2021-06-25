<शैली गुरु>
/*
 * Copyright (c) 2013, 2014 Kenneth MacKay. All rights reserved.
 * Copyright (c) 2019 Vitaly Chikunov <vt@altlinux.org>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *  * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <crypto/ecc_curve.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/swab.h>
#समावेश <linux/fips.h>
#समावेश <crypto/ecdh.h>
#समावेश <crypto/rng.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/ratelimit.h>

#समावेश "ecc.h"
#समावेश "ecc_curve_defs.h"

प्रकार काष्ठा अणु
	u64 m_low;
	u64 m_high;
पूर्ण uपूर्णांक128_t;

/* Returns curv25519 curve param */
स्थिर काष्ठा ecc_curve *ecc_get_curve25519(व्योम)
अणु
	वापस &ecc_25519;
पूर्ण
EXPORT_SYMBOL(ecc_get_curve25519);

स्थिर काष्ठा ecc_curve *ecc_get_curve(अचिन्हित पूर्णांक curve_id)
अणु
	चयन (curve_id) अणु
	/* In FIPS mode only allow P256 and higher */
	हाल ECC_CURVE_NIST_P192:
		वापस fips_enabled ? शून्य : &nist_p192;
	हाल ECC_CURVE_NIST_P256:
		वापस &nist_p256;
	हाल ECC_CURVE_NIST_P384:
		वापस &nist_p384;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ecc_get_curve);

अटल u64 *ecc_alloc_digits_space(अचिन्हित पूर्णांक ndigits)
अणु
	माप_प्रकार len = ndigits * माप(u64);

	अगर (!len)
		वापस शून्य;

	वापस kदो_स्मृति(len, GFP_KERNEL);
पूर्ण

अटल व्योम ecc_मुक्त_digits_space(u64 *space)
अणु
	kमुक्त_sensitive(space);
पूर्ण

अटल काष्ठा ecc_poपूर्णांक *ecc_alloc_poपूर्णांक(अचिन्हित पूर्णांक ndigits)
अणु
	काष्ठा ecc_poपूर्णांक *p = kदो_स्मृति(माप(*p), GFP_KERNEL);

	अगर (!p)
		वापस शून्य;

	p->x = ecc_alloc_digits_space(ndigits);
	अगर (!p->x)
		जाओ err_alloc_x;

	p->y = ecc_alloc_digits_space(ndigits);
	अगर (!p->y)
		जाओ err_alloc_y;

	p->ndigits = ndigits;

	वापस p;

err_alloc_y:
	ecc_मुक्त_digits_space(p->x);
err_alloc_x:
	kमुक्त(p);
	वापस शून्य;
पूर्ण

अटल व्योम ecc_मुक्त_poपूर्णांक(काष्ठा ecc_poपूर्णांक *p)
अणु
	अगर (!p)
		वापस;

	kमुक्त_sensitive(p->x);
	kमुक्त_sensitive(p->y);
	kमुक्त_sensitive(p);
पूर्ण

अटल व्योम vli_clear(u64 *vli, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++)
		vli[i] = 0;
पूर्ण

/* Returns true अगर vli == 0, false otherwise. */
bool vli_is_zero(स्थिर u64 *vli, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++) अणु
		अगर (vli[i])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(vli_is_zero);

/* Returns nonzero अगर bit of vli is set. */
अटल u64 vli_test_bit(स्थिर u64 *vli, अचिन्हित पूर्णांक bit)
अणु
	वापस (vli[bit / 64] & ((u64)1 << (bit % 64)));
पूर्ण

अटल bool vli_is_negative(स्थिर u64 *vli, अचिन्हित पूर्णांक ndigits)
अणु
	वापस vli_test_bit(vli, ndigits * 64 - 1);
पूर्ण

/* Counts the number of 64-bit "digits" in vli. */
अटल अचिन्हित पूर्णांक vli_num_digits(स्थिर u64 *vli, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;

	/* Search from the end until we find a non-zero digit.
	 * We करो it in reverse because we expect that most digits will
	 * be nonzero.
	 */
	क्रम (i = ndigits - 1; i >= 0 && vli[i] == 0; i--);

	वापस (i + 1);
पूर्ण

/* Counts the number of bits required क्रम vli. */
अटल अचिन्हित पूर्णांक vli_num_bits(स्थिर u64 *vli, अचिन्हित पूर्णांक ndigits)
अणु
	अचिन्हित पूर्णांक i, num_digits;
	u64 digit;

	num_digits = vli_num_digits(vli, ndigits);
	अगर (num_digits == 0)
		वापस 0;

	digit = vli[num_digits - 1];
	क्रम (i = 0; digit; i++)
		digit >>= 1;

	वापस ((num_digits - 1) * 64 + i);
पूर्ण

/* Set dest from unaligned bit string src. */
व्योम vli_from_be64(u64 *dest, स्थिर व्योम *src, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;
	स्थिर u64 *from = src;

	क्रम (i = 0; i < ndigits; i++)
		dest[i] = get_unaligned_be64(&from[ndigits - 1 - i]);
पूर्ण
EXPORT_SYMBOL(vli_from_be64);

व्योम vli_from_le64(u64 *dest, स्थिर व्योम *src, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;
	स्थिर u64 *from = src;

	क्रम (i = 0; i < ndigits; i++)
		dest[i] = get_unaligned_le64(&from[i]);
पूर्ण
EXPORT_SYMBOL(vli_from_le64);

/* Sets dest = src. */
अटल व्योम vli_set(u64 *dest, स्थिर u64 *src, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++)
		dest[i] = src[i];
पूर्ण

/* Returns sign of left - right. */
पूर्णांक vli_cmp(स्थिर u64 *left, स्थिर u64 *right, अचिन्हित पूर्णांक ndigits)
अणु
	पूर्णांक i;

	क्रम (i = ndigits - 1; i >= 0; i--) अणु
		अगर (left[i] > right[i])
			वापस 1;
		अन्यथा अगर (left[i] < right[i])
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vli_cmp);

/* Computes result = in << c, वापसing carry. Can modअगरy in place
 * (अगर result == in). 0 < shअगरt < 64.
 */
अटल u64 vli_lshअगरt(u64 *result, स्थिर u64 *in, अचिन्हित पूर्णांक shअगरt,
		      अचिन्हित पूर्णांक ndigits)
अणु
	u64 carry = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++) अणु
		u64 temp = in[i];

		result[i] = (temp << shअगरt) | carry;
		carry = temp >> (64 - shअगरt);
	पूर्ण

	वापस carry;
पूर्ण

/* Computes vli = vli >> 1. */
अटल व्योम vli_rshअगरt1(u64 *vli, अचिन्हित पूर्णांक ndigits)
अणु
	u64 *end = vli;
	u64 carry = 0;

	vli += ndigits;

	जबतक (vli-- > end) अणु
		u64 temp = *vli;
		*vli = (temp >> 1) | carry;
		carry = temp << 63;
	पूर्ण
पूर्ण

/* Computes result = left + right, वापसing carry. Can modअगरy in place. */
अटल u64 vli_add(u64 *result, स्थिर u64 *left, स्थिर u64 *right,
		   अचिन्हित पूर्णांक ndigits)
अणु
	u64 carry = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++) अणु
		u64 sum;

		sum = left[i] + right[i] + carry;
		अगर (sum != left[i])
			carry = (sum < left[i]);

		result[i] = sum;
	पूर्ण

	वापस carry;
पूर्ण

/* Computes result = left + right, वापसing carry. Can modअगरy in place. */
अटल u64 vli_uadd(u64 *result, स्थिर u64 *left, u64 right,
		    अचिन्हित पूर्णांक ndigits)
अणु
	u64 carry = right;
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++) अणु
		u64 sum;

		sum = left[i] + carry;
		अगर (sum != left[i])
			carry = (sum < left[i]);
		अन्यथा
			carry = !!carry;

		result[i] = sum;
	पूर्ण

	वापस carry;
पूर्ण

/* Computes result = left - right, वापसing borrow. Can modअगरy in place. */
u64 vli_sub(u64 *result, स्थिर u64 *left, स्थिर u64 *right,
		   अचिन्हित पूर्णांक ndigits)
अणु
	u64 borrow = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++) अणु
		u64 dअगरf;

		dअगरf = left[i] - right[i] - borrow;
		अगर (dअगरf != left[i])
			borrow = (dअगरf > left[i]);

		result[i] = dअगरf;
	पूर्ण

	वापस borrow;
पूर्ण
EXPORT_SYMBOL(vli_sub);

/* Computes result = left - right, वापसing borrow. Can modअगरy in place. */
अटल u64 vli_usub(u64 *result, स्थिर u64 *left, u64 right,
	     अचिन्हित पूर्णांक ndigits)
अणु
	u64 borrow = right;
	पूर्णांक i;

	क्रम (i = 0; i < ndigits; i++) अणु
		u64 dअगरf;

		dअगरf = left[i] - borrow;
		अगर (dअगरf != left[i])
			borrow = (dअगरf > left[i]);

		result[i] = dअगरf;
	पूर्ण

	वापस borrow;
पूर्ण

अटल uपूर्णांक128_t mul_64_64(u64 left, u64 right)
अणु
	uपूर्णांक128_t result;
#अगर defined(CONFIG_ARCH_SUPPORTS_INT128)
	अचिन्हित __पूर्णांक128 m = (अचिन्हित __पूर्णांक128)left * right;

	result.m_low  = m;
	result.m_high = m >> 64;
#अन्यथा
	u64 a0 = left & 0xffffffffull;
	u64 a1 = left >> 32;
	u64 b0 = right & 0xffffffffull;
	u64 b1 = right >> 32;
	u64 m0 = a0 * b0;
	u64 m1 = a0 * b1;
	u64 m2 = a1 * b0;
	u64 m3 = a1 * b1;

	m2 += (m0 >> 32);
	m2 += m1;

	/* Overflow */
	अगर (m2 < m1)
		m3 += 0x100000000ull;

	result.m_low = (m0 & 0xffffffffull) | (m2 << 32);
	result.m_high = m3 + (m2 >> 32);
#पूर्ण_अगर
	वापस result;
पूर्ण

अटल uपूर्णांक128_t add_128_128(uपूर्णांक128_t a, uपूर्णांक128_t b)
अणु
	uपूर्णांक128_t result;

	result.m_low = a.m_low + b.m_low;
	result.m_high = a.m_high + b.m_high + (result.m_low < a.m_low);

	वापस result;
पूर्ण

अटल व्योम vli_mult(u64 *result, स्थिर u64 *left, स्थिर u64 *right,
		     अचिन्हित पूर्णांक ndigits)
अणु
	uपूर्णांक128_t r01 = अणु 0, 0 पूर्ण;
	u64 r2 = 0;
	अचिन्हित पूर्णांक i, k;

	/* Compute each digit of result in sequence, मुख्यtaining the
	 * carries.
	 */
	क्रम (k = 0; k < ndigits * 2 - 1; k++) अणु
		अचिन्हित पूर्णांक min;

		अगर (k < ndigits)
			min = 0;
		अन्यथा
			min = (k + 1) - ndigits;

		क्रम (i = min; i <= k && i < ndigits; i++) अणु
			uपूर्णांक128_t product;

			product = mul_64_64(left[i], right[k - i]);

			r01 = add_128_128(r01, product);
			r2 += (r01.m_high < product.m_high);
		पूर्ण

		result[k] = r01.m_low;
		r01.m_low = r01.m_high;
		r01.m_high = r2;
		r2 = 0;
	पूर्ण

	result[ndigits * 2 - 1] = r01.m_low;
पूर्ण

/* Compute product = left * right, क्रम a small right value. */
अटल व्योम vli_umult(u64 *result, स्थिर u64 *left, u32 right,
		      अचिन्हित पूर्णांक ndigits)
अणु
	uपूर्णांक128_t r01 = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < ndigits; k++) अणु
		uपूर्णांक128_t product;

		product = mul_64_64(left[k], right);
		r01 = add_128_128(r01, product);
		/* no carry */
		result[k] = r01.m_low;
		r01.m_low = r01.m_high;
		r01.m_high = 0;
	पूर्ण
	result[k] = r01.m_low;
	क्रम (++k; k < ndigits * 2; k++)
		result[k] = 0;
पूर्ण

अटल व्योम vli_square(u64 *result, स्थिर u64 *left, अचिन्हित पूर्णांक ndigits)
अणु
	uपूर्णांक128_t r01 = अणु 0, 0 पूर्ण;
	u64 r2 = 0;
	पूर्णांक i, k;

	क्रम (k = 0; k < ndigits * 2 - 1; k++) अणु
		अचिन्हित पूर्णांक min;

		अगर (k < ndigits)
			min = 0;
		अन्यथा
			min = (k + 1) - ndigits;

		क्रम (i = min; i <= k && i <= k - i; i++) अणु
			uपूर्णांक128_t product;

			product = mul_64_64(left[i], left[k - i]);

			अगर (i < k - i) अणु
				r2 += product.m_high >> 63;
				product.m_high = (product.m_high << 1) |
						 (product.m_low >> 63);
				product.m_low <<= 1;
			पूर्ण

			r01 = add_128_128(r01, product);
			r2 += (r01.m_high < product.m_high);
		पूर्ण

		result[k] = r01.m_low;
		r01.m_low = r01.m_high;
		r01.m_high = r2;
		r2 = 0;
	पूर्ण

	result[ndigits * 2 - 1] = r01.m_low;
पूर्ण

/* Computes result = (left + right) % mod.
 * Assumes that left < mod and right < mod, result != mod.
 */
अटल व्योम vli_mod_add(u64 *result, स्थिर u64 *left, स्थिर u64 *right,
			स्थिर u64 *mod, अचिन्हित पूर्णांक ndigits)
अणु
	u64 carry;

	carry = vli_add(result, left, right, ndigits);

	/* result > mod (result = mod + reमुख्यder), so subtract mod to
	 * get reमुख्यder.
	 */
	अगर (carry || vli_cmp(result, mod, ndigits) >= 0)
		vli_sub(result, result, mod, ndigits);
पूर्ण

/* Computes result = (left - right) % mod.
 * Assumes that left < mod and right < mod, result != mod.
 */
अटल व्योम vli_mod_sub(u64 *result, स्थिर u64 *left, स्थिर u64 *right,
			स्थिर u64 *mod, अचिन्हित पूर्णांक ndigits)
अणु
	u64 borrow = vli_sub(result, left, right, ndigits);

	/* In this हाल, p_result == -dअगरf == (max पूर्णांक) - dअगरf.
	 * Since -x % d == d - x, we can get the correct result from
	 * result + mod (with overflow).
	 */
	अगर (borrow)
		vli_add(result, result, mod, ndigits);
पूर्ण

/*
 * Computes result = product % mod
 * क्रम special क्रमm moduli: p = 2^k-c, क्रम small c (note the minus sign)
 *
 * References:
 * R. Cअक्रमall, C. Pomerance. Prime Numbers: A Computational Perspective.
 * 9 Fast Algorithms क्रम Large-Integer Arithmetic. 9.2.3 Moduli of special क्रमm
 * Algorithm 9.2.13 (Fast mod operation क्रम special-क्रमm moduli).
 */
अटल व्योम vli_mmod_special(u64 *result, स्थिर u64 *product,
			      स्थिर u64 *mod, अचिन्हित पूर्णांक ndigits)
अणु
	u64 c = -mod[0];
	u64 t[ECC_MAX_DIGITS * 2];
	u64 r[ECC_MAX_DIGITS * 2];

	vli_set(r, product, ndigits * 2);
	जबतक (!vli_is_zero(r + ndigits, ndigits)) अणु
		vli_umult(t, r + ndigits, c, ndigits);
		vli_clear(r + ndigits, ndigits);
		vli_add(r, r, t, ndigits * 2);
	पूर्ण
	vli_set(t, mod, ndigits);
	vli_clear(t + ndigits, ndigits);
	जबतक (vli_cmp(r, t, ndigits * 2) >= 0)
		vli_sub(r, r, t, ndigits * 2);
	vli_set(result, r, ndigits);
पूर्ण

/*
 * Computes result = product % mod
 * क्रम special क्रमm moduli: p = 2^अणुk-1पूर्ण+c, क्रम small c (note the plus sign)
 * where k-1 करोes not fit पूर्णांकo qword boundary by -1 bit (such as 255).

 * References (loosely based on):
 * A. Menezes, P. van Oorschot, S. Vanstone. Handbook of Applied Cryptography.
 * 14.3.4 Reduction methods क्रम moduli of special क्रमm. Algorithm 14.47.
 * URL: http://cacr.uwaterloo.ca/hac/about/chap14.pdf
 *
 * H. Cohen, G. Frey, R. Avanzi, C. Doche, T. Lange, K. Nguyen, F. Vercauteren.
 * Handbook of Elliptic and Hyperelliptic Curve Cryptography.
 * Algorithm 10.25 Fast reduction क्रम special क्रमm moduli
 */
अटल व्योम vli_mmod_special2(u64 *result, स्थिर u64 *product,
			       स्थिर u64 *mod, अचिन्हित पूर्णांक ndigits)
अणु
	u64 c2 = mod[0] * 2;
	u64 q[ECC_MAX_DIGITS];
	u64 r[ECC_MAX_DIGITS * 2];
	u64 m[ECC_MAX_DIGITS * 2]; /* expanded mod */
	पूर्णांक carry; /* last bit that करोesn't fit पूर्णांकo q */
	पूर्णांक i;

	vli_set(m, mod, ndigits);
	vli_clear(m + ndigits, ndigits);

	vli_set(r, product, ndigits);
	/* q and carry are top bits */
	vli_set(q, product + ndigits, ndigits);
	vli_clear(r + ndigits, ndigits);
	carry = vli_is_negative(r, ndigits);
	अगर (carry)
		r[ndigits - 1] &= (1ull << 63) - 1;
	क्रम (i = 1; carry || !vli_is_zero(q, ndigits); i++) अणु
		u64 qc[ECC_MAX_DIGITS * 2];

		vli_umult(qc, q, c2, ndigits);
		अगर (carry)
			vli_uadd(qc, qc, mod[0], ndigits * 2);
		vli_set(q, qc + ndigits, ndigits);
		vli_clear(qc + ndigits, ndigits);
		carry = vli_is_negative(qc, ndigits);
		अगर (carry)
			qc[ndigits - 1] &= (1ull << 63) - 1;
		अगर (i & 1)
			vli_sub(r, r, qc, ndigits * 2);
		अन्यथा
			vli_add(r, r, qc, ndigits * 2);
	पूर्ण
	जबतक (vli_is_negative(r, ndigits * 2))
		vli_add(r, r, m, ndigits * 2);
	जबतक (vli_cmp(r, m, ndigits * 2) >= 0)
		vli_sub(r, r, m, ndigits * 2);

	vli_set(result, r, ndigits);
पूर्ण

/*
 * Computes result = product % mod, where product is 2N words दीर्घ.
 * Reference: Ken MacKay's micro-ecc.
 * Currently only deचिन्हित to work क्रम curve_p or curve_n.
 */
अटल व्योम vli_mmod_slow(u64 *result, u64 *product, स्थिर u64 *mod,
			  अचिन्हित पूर्णांक ndigits)
अणु
	u64 mod_m[2 * ECC_MAX_DIGITS];
	u64 पंचांगp[2 * ECC_MAX_DIGITS];
	u64 *v[2] = अणु पंचांगp, product पूर्ण;
	u64 carry = 0;
	अचिन्हित पूर्णांक i;
	/* Shअगरt mod so its highest set bit is at the maximum position. */
	पूर्णांक shअगरt = (ndigits * 2 * 64) - vli_num_bits(mod, ndigits);
	पूर्णांक word_shअगरt = shअगरt / 64;
	पूर्णांक bit_shअगरt = shअगरt % 64;

	vli_clear(mod_m, word_shअगरt);
	अगर (bit_shअगरt > 0) अणु
		क्रम (i = 0; i < ndigits; ++i) अणु
			mod_m[word_shअगरt + i] = (mod[i] << bit_shअगरt) | carry;
			carry = mod[i] >> (64 - bit_shअगरt);
		पूर्ण
	पूर्ण अन्यथा
		vli_set(mod_m + word_shअगरt, mod, ndigits);

	क्रम (i = 1; shअगरt >= 0; --shअगरt) अणु
		u64 borrow = 0;
		अचिन्हित पूर्णांक j;

		क्रम (j = 0; j < ndigits * 2; ++j) अणु
			u64 dअगरf = v[i][j] - mod_m[j] - borrow;

			अगर (dअगरf != v[i][j])
				borrow = (dअगरf > v[i][j]);
			v[1 - i][j] = dअगरf;
		पूर्ण
		i = !(i ^ borrow); /* Swap the index अगर there was no borrow */
		vli_rshअगरt1(mod_m, ndigits);
		mod_m[ndigits - 1] |= mod_m[ndigits] << (64 - 1);
		vli_rshअगरt1(mod_m + ndigits, ndigits);
	पूर्ण
	vli_set(result, v[i], ndigits);
पूर्ण

/* Computes result = product % mod using Barrett's reduction with precomputed
 * value mu appended to the mod after ndigits, mu = (2^अणु2wपूर्ण / mod) and have
 * length ndigits + 1, where mu * (2^w - 1) should not overflow ndigits
 * boundary.
 *
 * Reference:
 * R. Brent, P. Zimmermann. Modern Computer Arithmetic. 2010.
 * 2.4.1 Barrett's algorithm. Algorithm 2.5.
 */
अटल व्योम vli_mmod_barrett(u64 *result, u64 *product, स्थिर u64 *mod,
			     अचिन्हित पूर्णांक ndigits)
अणु
	u64 q[ECC_MAX_DIGITS * 2];
	u64 r[ECC_MAX_DIGITS * 2];
	स्थिर u64 *mu = mod + ndigits;

	vli_mult(q, product + ndigits, mu, ndigits);
	अगर (mu[ndigits])
		vli_add(q + ndigits, q + ndigits, product + ndigits, ndigits);
	vli_mult(r, mod, q + ndigits, ndigits);
	vli_sub(r, product, r, ndigits * 2);
	जबतक (!vli_is_zero(r + ndigits, ndigits) ||
	       vli_cmp(r, mod, ndigits) != -1) अणु
		u64 carry;

		carry = vli_sub(r, r, mod, ndigits);
		vli_usub(r + ndigits, r + ndigits, carry, ndigits);
	पूर्ण
	vli_set(result, r, ndigits);
पूर्ण

/* Computes p_result = p_product % curve_p.
 * See algorithm 5 and 6 from
 * http://www.isys.uni-klu.ac.at/PDF/2001-0126-MT.pdf
 */
अटल व्योम vli_mmod_fast_192(u64 *result, स्थिर u64 *product,
			      स्थिर u64 *curve_prime, u64 *पंचांगp)
अणु
	स्थिर अचिन्हित पूर्णांक ndigits = 3;
	पूर्णांक carry;

	vli_set(result, product, ndigits);

	vli_set(पंचांगp, &product[3], ndigits);
	carry = vli_add(result, result, पंचांगp, ndigits);

	पंचांगp[0] = 0;
	पंचांगp[1] = product[3];
	पंचांगp[2] = product[4];
	carry += vli_add(result, result, पंचांगp, ndigits);

	पंचांगp[0] = पंचांगp[1] = product[5];
	पंचांगp[2] = 0;
	carry += vli_add(result, result, पंचांगp, ndigits);

	जबतक (carry || vli_cmp(curve_prime, result, ndigits) != 1)
		carry -= vli_sub(result, result, curve_prime, ndigits);
पूर्ण

/* Computes result = product % curve_prime
 * from http://www.nsa.gov/ia/_files/nist-routines.pdf
 */
अटल व्योम vli_mmod_fast_256(u64 *result, स्थिर u64 *product,
			      स्थिर u64 *curve_prime, u64 *पंचांगp)
अणु
	पूर्णांक carry;
	स्थिर अचिन्हित पूर्णांक ndigits = 4;

	/* t */
	vli_set(result, product, ndigits);

	/* s1 */
	पंचांगp[0] = 0;
	पंचांगp[1] = product[5] & 0xffffffff00000000ull;
	पंचांगp[2] = product[6];
	पंचांगp[3] = product[7];
	carry = vli_lshअगरt(पंचांगp, पंचांगp, 1, ndigits);
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s2 */
	पंचांगp[1] = product[6] << 32;
	पंचांगp[2] = (product[6] >> 32) | (product[7] << 32);
	पंचांगp[3] = product[7] >> 32;
	carry += vli_lshअगरt(पंचांगp, पंचांगp, 1, ndigits);
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s3 */
	पंचांगp[0] = product[4];
	पंचांगp[1] = product[5] & 0xffffffff;
	पंचांगp[2] = 0;
	पंचांगp[3] = product[7];
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s4 */
	पंचांगp[0] = (product[4] >> 32) | (product[5] << 32);
	पंचांगp[1] = (product[5] >> 32) | (product[6] & 0xffffffff00000000ull);
	पंचांगp[2] = product[7];
	पंचांगp[3] = (product[6] >> 32) | (product[4] << 32);
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* d1 */
	पंचांगp[0] = (product[5] >> 32) | (product[6] << 32);
	पंचांगp[1] = (product[6] >> 32);
	पंचांगp[2] = 0;
	पंचांगp[3] = (product[4] & 0xffffffff) | (product[5] << 32);
	carry -= vli_sub(result, result, पंचांगp, ndigits);

	/* d2 */
	पंचांगp[0] = product[6];
	पंचांगp[1] = product[7];
	पंचांगp[2] = 0;
	पंचांगp[3] = (product[4] >> 32) | (product[5] & 0xffffffff00000000ull);
	carry -= vli_sub(result, result, पंचांगp, ndigits);

	/* d3 */
	पंचांगp[0] = (product[6] >> 32) | (product[7] << 32);
	पंचांगp[1] = (product[7] >> 32) | (product[4] << 32);
	पंचांगp[2] = (product[4] >> 32) | (product[5] << 32);
	पंचांगp[3] = (product[6] << 32);
	carry -= vli_sub(result, result, पंचांगp, ndigits);

	/* d4 */
	पंचांगp[0] = product[7];
	पंचांगp[1] = product[4] & 0xffffffff00000000ull;
	पंचांगp[2] = product[5];
	पंचांगp[3] = product[6] & 0xffffffff00000000ull;
	carry -= vli_sub(result, result, पंचांगp, ndigits);

	अगर (carry < 0) अणु
		करो अणु
			carry += vli_add(result, result, curve_prime, ndigits);
		पूर्ण जबतक (carry < 0);
	पूर्ण अन्यथा अणु
		जबतक (carry || vli_cmp(curve_prime, result, ndigits) != 1)
			carry -= vli_sub(result, result, curve_prime, ndigits);
	पूर्ण
पूर्ण

#घोषणा SL32OR32(x32, y32) (((u64)x32 << 32) | y32)
#घोषणा AND64H(x64)  (x64 & 0xffFFffFF00000000ull)
#घोषणा AND64L(x64)  (x64 & 0x00000000ffFFffFFull)

/* Computes result = product % curve_prime
 * from "Mathematical routines for the NIST prime elliptic curves"
 */
अटल व्योम vli_mmod_fast_384(u64 *result, स्थिर u64 *product,
				स्थिर u64 *curve_prime, u64 *पंचांगp)
अणु
	पूर्णांक carry;
	स्थिर अचिन्हित पूर्णांक ndigits = 6;

	/* t */
	vli_set(result, product, ndigits);

	/* s1 */
	पंचांगp[0] = 0;		// 0 || 0
	पंचांगp[1] = 0;		// 0 || 0
	पंचांगp[2] = SL32OR32(product[11], (product[10]>>32));	//a22||a21
	पंचांगp[3] = product[11]>>32;	// 0 ||a23
	पंचांगp[4] = 0;		// 0 || 0
	पंचांगp[5] = 0;		// 0 || 0
	carry = vli_lshअगरt(पंचांगp, पंचांगp, 1, ndigits);
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s2 */
	पंचांगp[0] = product[6];	//a13||a12
	पंचांगp[1] = product[7];	//a15||a14
	पंचांगp[2] = product[8];	//a17||a16
	पंचांगp[3] = product[9];	//a19||a18
	पंचांगp[4] = product[10];	//a21||a20
	पंचांगp[5] = product[11];	//a23||a22
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s3 */
	पंचांगp[0] = SL32OR32(product[11], (product[10]>>32));	//a22||a21
	पंचांगp[1] = SL32OR32(product[6], (product[11]>>32));	//a12||a23
	पंचांगp[2] = SL32OR32(product[7], (product[6])>>32);	//a14||a13
	पंचांगp[3] = SL32OR32(product[8], (product[7]>>32));	//a16||a15
	पंचांगp[4] = SL32OR32(product[9], (product[8]>>32));	//a18||a17
	पंचांगp[5] = SL32OR32(product[10], (product[9]>>32));	//a20||a19
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s4 */
	पंचांगp[0] = AND64H(product[11]);	//a23|| 0
	पंचांगp[1] = (product[10]<<32);	//a20|| 0
	पंचांगp[2] = product[6];	//a13||a12
	पंचांगp[3] = product[7];	//a15||a14
	पंचांगp[4] = product[8];	//a17||a16
	पंचांगp[5] = product[9];	//a19||a18
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s5 */
	पंचांगp[0] = 0;		//  0|| 0
	पंचांगp[1] = 0;		//  0|| 0
	पंचांगp[2] = product[10];	//a21||a20
	पंचांगp[3] = product[11];	//a23||a22
	पंचांगp[4] = 0;		//  0|| 0
	पंचांगp[5] = 0;		//  0|| 0
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* s6 */
	पंचांगp[0] = AND64L(product[10]);	// 0 ||a20
	पंचांगp[1] = AND64H(product[10]);	//a21|| 0
	पंचांगp[2] = product[11];	//a23||a22
	पंचांगp[3] = 0;		// 0 || 0
	पंचांगp[4] = 0;		// 0 || 0
	पंचांगp[5] = 0;		// 0 || 0
	carry += vli_add(result, result, पंचांगp, ndigits);

	/* d1 */
	पंचांगp[0] = SL32OR32(product[6], (product[11]>>32));	//a12||a23
	पंचांगp[1] = SL32OR32(product[7], (product[6]>>32));	//a14||a13
	पंचांगp[2] = SL32OR32(product[8], (product[7]>>32));	//a16||a15
	पंचांगp[3] = SL32OR32(product[9], (product[8]>>32));	//a18||a17
	पंचांगp[4] = SL32OR32(product[10], (product[9]>>32));	//a20||a19
	पंचांगp[5] = SL32OR32(product[11], (product[10]>>32));	//a22||a21
	carry -= vli_sub(result, result, पंचांगp, ndigits);

	/* d2 */
	पंचांगp[0] = (product[10]<<32);	//a20|| 0
	पंचांगp[1] = SL32OR32(product[11], (product[10]>>32));	//a22||a21
	पंचांगp[2] = (product[11]>>32);	// 0 ||a23
	पंचांगp[3] = 0;		// 0 || 0
	पंचांगp[4] = 0;		// 0 || 0
	पंचांगp[5] = 0;		// 0 || 0
	carry -= vli_sub(result, result, पंचांगp, ndigits);

	/* d3 */
	पंचांगp[0] = 0;		// 0 || 0
	पंचांगp[1] = AND64H(product[11]);	//a23|| 0
	पंचांगp[2] = product[11]>>32;	// 0 ||a23
	पंचांगp[3] = 0;		// 0 || 0
	पंचांगp[4] = 0;		// 0 || 0
	पंचांगp[5] = 0;		// 0 || 0
	carry -= vli_sub(result, result, पंचांगp, ndigits);

	अगर (carry < 0) अणु
		करो अणु
			carry += vli_add(result, result, curve_prime, ndigits);
		पूर्ण जबतक (carry < 0);
	पूर्ण अन्यथा अणु
		जबतक (carry || vli_cmp(curve_prime, result, ndigits) != 1)
			carry -= vli_sub(result, result, curve_prime, ndigits);
	पूर्ण

पूर्ण

#अघोषित SL32OR32
#अघोषित AND64H
#अघोषित AND64L

/* Computes result = product % curve_prime क्रम dअगरferent curve_primes.
 *
 * Note that curve_primes are distinguished just by heuristic check and
 * not by complete conक्रमmance check.
 */
अटल bool vli_mmod_fast(u64 *result, u64 *product,
			  स्थिर काष्ठा ecc_curve *curve)
अणु
	u64 पंचांगp[2 * ECC_MAX_DIGITS];
	स्थिर u64 *curve_prime = curve->p;
	स्थिर अचिन्हित पूर्णांक ndigits = curve->g.ndigits;

	/* All NIST curves have name prefix 'nist_' */
	अगर (म_भेदन(curve->name, "nist_", 5) != 0) अणु
		/* Try to handle Pseuकरो-Marsenne primes. */
		अगर (curve_prime[ndigits - 1] == -1ull) अणु
			vli_mmod_special(result, product, curve_prime,
					 ndigits);
			वापस true;
		पूर्ण अन्यथा अगर (curve_prime[ndigits - 1] == 1ull << 63 &&
			   curve_prime[ndigits - 2] == 0) अणु
			vli_mmod_special2(result, product, curve_prime,
					  ndigits);
			वापस true;
		पूर्ण
		vli_mmod_barrett(result, product, curve_prime, ndigits);
		वापस true;
	पूर्ण

	चयन (ndigits) अणु
	हाल 3:
		vli_mmod_fast_192(result, product, curve_prime, पंचांगp);
		अवरोध;
	हाल 4:
		vli_mmod_fast_256(result, product, curve_prime, पंचांगp);
		अवरोध;
	हाल 6:
		vli_mmod_fast_384(result, product, curve_prime, पंचांगp);
		अवरोध;
	शेष:
		pr_err_ratelimited("ecc: unsupported digits size!\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Computes result = (left * right) % mod.
 * Assumes that mod is big enough curve order.
 */
व्योम vli_mod_mult_slow(u64 *result, स्थिर u64 *left, स्थिर u64 *right,
		       स्थिर u64 *mod, अचिन्हित पूर्णांक ndigits)
अणु
	u64 product[ECC_MAX_DIGITS * 2];

	vli_mult(product, left, right, ndigits);
	vli_mmod_slow(result, product, mod, ndigits);
पूर्ण
EXPORT_SYMBOL(vli_mod_mult_slow);

/* Computes result = (left * right) % curve_prime. */
अटल व्योम vli_mod_mult_fast(u64 *result, स्थिर u64 *left, स्थिर u64 *right,
			      स्थिर काष्ठा ecc_curve *curve)
अणु
	u64 product[2 * ECC_MAX_DIGITS];

	vli_mult(product, left, right, curve->g.ndigits);
	vli_mmod_fast(result, product, curve);
पूर्ण

/* Computes result = left^2 % curve_prime. */
अटल व्योम vli_mod_square_fast(u64 *result, स्थिर u64 *left,
				स्थिर काष्ठा ecc_curve *curve)
अणु
	u64 product[2 * ECC_MAX_DIGITS];

	vli_square(product, left, curve->g.ndigits);
	vli_mmod_fast(result, product, curve);
पूर्ण

#घोषणा EVEN(vli) (!(vli[0] & 1))
/* Computes result = (1 / p_input) % mod. All VLIs are the same size.
 * See "From Euclid's GCD to Montgomery Multiplication to the Great Divide"
 * https://द_असल.oracle.com/techrep/2001/smli_tr-2001-95.pdf
 */
व्योम vli_mod_inv(u64 *result, स्थिर u64 *input, स्थिर u64 *mod,
			अचिन्हित पूर्णांक ndigits)
अणु
	u64 a[ECC_MAX_DIGITS], b[ECC_MAX_DIGITS];
	u64 u[ECC_MAX_DIGITS], v[ECC_MAX_DIGITS];
	u64 carry;
	पूर्णांक cmp_result;

	अगर (vli_is_zero(input, ndigits)) अणु
		vli_clear(result, ndigits);
		वापस;
	पूर्ण

	vli_set(a, input, ndigits);
	vli_set(b, mod, ndigits);
	vli_clear(u, ndigits);
	u[0] = 1;
	vli_clear(v, ndigits);

	जबतक ((cmp_result = vli_cmp(a, b, ndigits)) != 0) अणु
		carry = 0;

		अगर (EVEN(a)) अणु
			vli_rshअगरt1(a, ndigits);

			अगर (!EVEN(u))
				carry = vli_add(u, u, mod, ndigits);

			vli_rshअगरt1(u, ndigits);
			अगर (carry)
				u[ndigits - 1] |= 0x8000000000000000ull;
		पूर्ण अन्यथा अगर (EVEN(b)) अणु
			vli_rshअगरt1(b, ndigits);

			अगर (!EVEN(v))
				carry = vli_add(v, v, mod, ndigits);

			vli_rshअगरt1(v, ndigits);
			अगर (carry)
				v[ndigits - 1] |= 0x8000000000000000ull;
		पूर्ण अन्यथा अगर (cmp_result > 0) अणु
			vli_sub(a, a, b, ndigits);
			vli_rshअगरt1(a, ndigits);

			अगर (vli_cmp(u, v, ndigits) < 0)
				vli_add(u, u, mod, ndigits);

			vli_sub(u, u, v, ndigits);
			अगर (!EVEN(u))
				carry = vli_add(u, u, mod, ndigits);

			vli_rshअगरt1(u, ndigits);
			अगर (carry)
				u[ndigits - 1] |= 0x8000000000000000ull;
		पूर्ण अन्यथा अणु
			vli_sub(b, b, a, ndigits);
			vli_rshअगरt1(b, ndigits);

			अगर (vli_cmp(v, u, ndigits) < 0)
				vli_add(v, v, mod, ndigits);

			vli_sub(v, v, u, ndigits);
			अगर (!EVEN(v))
				carry = vli_add(v, v, mod, ndigits);

			vli_rshअगरt1(v, ndigits);
			अगर (carry)
				v[ndigits - 1] |= 0x8000000000000000ull;
		पूर्ण
	पूर्ण

	vli_set(result, u, ndigits);
पूर्ण
EXPORT_SYMBOL(vli_mod_inv);

/* ------ Poपूर्णांक operations ------ */

/* Returns true अगर p_poपूर्णांक is the poपूर्णांक at infinity, false otherwise. */
अटल bool ecc_poपूर्णांक_is_zero(स्थिर काष्ठा ecc_poपूर्णांक *poपूर्णांक)
अणु
	वापस (vli_is_zero(poपूर्णांक->x, poपूर्णांक->ndigits) &&
		vli_is_zero(poपूर्णांक->y, poपूर्णांक->ndigits));
पूर्ण

/* Poपूर्णांक multiplication algorithm using Montgomery's ladder with co-Z
 * coordinates. From https://eprपूर्णांक.iacr.org/2011/338.pdf
 */

/* Double in place */
अटल व्योम ecc_poपूर्णांक_द्विगुन_jacobian(u64 *x1, u64 *y1, u64 *z1,
					स्थिर काष्ठा ecc_curve *curve)
अणु
	/* t1 = x, t2 = y, t3 = z */
	u64 t4[ECC_MAX_DIGITS];
	u64 t5[ECC_MAX_DIGITS];
	स्थिर u64 *curve_prime = curve->p;
	स्थिर अचिन्हित पूर्णांक ndigits = curve->g.ndigits;

	अगर (vli_is_zero(z1, ndigits))
		वापस;

	/* t4 = y1^2 */
	vli_mod_square_fast(t4, y1, curve);
	/* t5 = x1*y1^2 = A */
	vli_mod_mult_fast(t5, x1, t4, curve);
	/* t4 = y1^4 */
	vli_mod_square_fast(t4, t4, curve);
	/* t2 = y1*z1 = z3 */
	vli_mod_mult_fast(y1, y1, z1, curve);
	/* t3 = z1^2 */
	vli_mod_square_fast(z1, z1, curve);

	/* t1 = x1 + z1^2 */
	vli_mod_add(x1, x1, z1, curve_prime, ndigits);
	/* t3 = 2*z1^2 */
	vli_mod_add(z1, z1, z1, curve_prime, ndigits);
	/* t3 = x1 - z1^2 */
	vli_mod_sub(z1, x1, z1, curve_prime, ndigits);
	/* t1 = x1^2 - z1^4 */
	vli_mod_mult_fast(x1, x1, z1, curve);

	/* t3 = 2*(x1^2 - z1^4) */
	vli_mod_add(z1, x1, x1, curve_prime, ndigits);
	/* t1 = 3*(x1^2 - z1^4) */
	vli_mod_add(x1, x1, z1, curve_prime, ndigits);
	अगर (vli_test_bit(x1, 0)) अणु
		u64 carry = vli_add(x1, x1, curve_prime, ndigits);

		vli_rshअगरt1(x1, ndigits);
		x1[ndigits - 1] |= carry << 63;
	पूर्ण अन्यथा अणु
		vli_rshअगरt1(x1, ndigits);
	पूर्ण
	/* t1 = 3/2*(x1^2 - z1^4) = B */

	/* t3 = B^2 */
	vli_mod_square_fast(z1, x1, curve);
	/* t3 = B^2 - A */
	vli_mod_sub(z1, z1, t5, curve_prime, ndigits);
	/* t3 = B^2 - 2A = x3 */
	vli_mod_sub(z1, z1, t5, curve_prime, ndigits);
	/* t5 = A - x3 */
	vli_mod_sub(t5, t5, z1, curve_prime, ndigits);
	/* t1 = B * (A - x3) */
	vli_mod_mult_fast(x1, x1, t5, curve);
	/* t4 = B * (A - x3) - y1^4 = y3 */
	vli_mod_sub(t4, x1, t4, curve_prime, ndigits);

	vli_set(x1, z1, ndigits);
	vli_set(z1, y1, ndigits);
	vli_set(y1, t4, ndigits);
पूर्ण

/* Modअगरy (x1, y1) => (x1 * z^2, y1 * z^3) */
अटल व्योम apply_z(u64 *x1, u64 *y1, u64 *z, स्थिर काष्ठा ecc_curve *curve)
अणु
	u64 t1[ECC_MAX_DIGITS];

	vli_mod_square_fast(t1, z, curve);		/* z^2 */
	vli_mod_mult_fast(x1, x1, t1, curve);	/* x1 * z^2 */
	vli_mod_mult_fast(t1, t1, z, curve);	/* z^3 */
	vli_mod_mult_fast(y1, y1, t1, curve);	/* y1 * z^3 */
पूर्ण

/* P = (x1, y1) => 2P, (x2, y2) => P' */
अटल व्योम xycz_initial_द्विगुन(u64 *x1, u64 *y1, u64 *x2, u64 *y2,
				u64 *p_initial_z, स्थिर काष्ठा ecc_curve *curve)
अणु
	u64 z[ECC_MAX_DIGITS];
	स्थिर अचिन्हित पूर्णांक ndigits = curve->g.ndigits;

	vli_set(x2, x1, ndigits);
	vli_set(y2, y1, ndigits);

	vli_clear(z, ndigits);
	z[0] = 1;

	अगर (p_initial_z)
		vli_set(z, p_initial_z, ndigits);

	apply_z(x1, y1, z, curve);

	ecc_poपूर्णांक_द्विगुन_jacobian(x1, y1, z, curve);

	apply_z(x2, y2, z, curve);
पूर्ण

/* Input P = (x1, y1, Z), Q = (x2, y2, Z)
 * Output P' = (x1', y1', Z3), P + Q = (x3, y3, Z3)
 * or P => P', Q => P + Q
 */
अटल व्योम xycz_add(u64 *x1, u64 *y1, u64 *x2, u64 *y2,
			स्थिर काष्ठा ecc_curve *curve)
अणु
	/* t1 = X1, t2 = Y1, t3 = X2, t4 = Y2 */
	u64 t5[ECC_MAX_DIGITS];
	स्थिर u64 *curve_prime = curve->p;
	स्थिर अचिन्हित पूर्णांक ndigits = curve->g.ndigits;

	/* t5 = x2 - x1 */
	vli_mod_sub(t5, x2, x1, curve_prime, ndigits);
	/* t5 = (x2 - x1)^2 = A */
	vli_mod_square_fast(t5, t5, curve);
	/* t1 = x1*A = B */
	vli_mod_mult_fast(x1, x1, t5, curve);
	/* t3 = x2*A = C */
	vli_mod_mult_fast(x2, x2, t5, curve);
	/* t4 = y2 - y1 */
	vli_mod_sub(y2, y2, y1, curve_prime, ndigits);
	/* t5 = (y2 - y1)^2 = D */
	vli_mod_square_fast(t5, y2, curve);

	/* t5 = D - B */
	vli_mod_sub(t5, t5, x1, curve_prime, ndigits);
	/* t5 = D - B - C = x3 */
	vli_mod_sub(t5, t5, x2, curve_prime, ndigits);
	/* t3 = C - B */
	vli_mod_sub(x2, x2, x1, curve_prime, ndigits);
	/* t2 = y1*(C - B) */
	vli_mod_mult_fast(y1, y1, x2, curve);
	/* t3 = B - x3 */
	vli_mod_sub(x2, x1, t5, curve_prime, ndigits);
	/* t4 = (y2 - y1)*(B - x3) */
	vli_mod_mult_fast(y2, y2, x2, curve);
	/* t4 = y3 */
	vli_mod_sub(y2, y2, y1, curve_prime, ndigits);

	vli_set(x2, t5, ndigits);
पूर्ण

/* Input P = (x1, y1, Z), Q = (x2, y2, Z)
 * Output P + Q = (x3, y3, Z3), P - Q = (x3', y3', Z3)
 * or P => P - Q, Q => P + Q
 */
अटल व्योम xycz_add_c(u64 *x1, u64 *y1, u64 *x2, u64 *y2,
			स्थिर काष्ठा ecc_curve *curve)
अणु
	/* t1 = X1, t2 = Y1, t3 = X2, t4 = Y2 */
	u64 t5[ECC_MAX_DIGITS];
	u64 t6[ECC_MAX_DIGITS];
	u64 t7[ECC_MAX_DIGITS];
	स्थिर u64 *curve_prime = curve->p;
	स्थिर अचिन्हित पूर्णांक ndigits = curve->g.ndigits;

	/* t5 = x2 - x1 */
	vli_mod_sub(t5, x2, x1, curve_prime, ndigits);
	/* t5 = (x2 - x1)^2 = A */
	vli_mod_square_fast(t5, t5, curve);
	/* t1 = x1*A = B */
	vli_mod_mult_fast(x1, x1, t5, curve);
	/* t3 = x2*A = C */
	vli_mod_mult_fast(x2, x2, t5, curve);
	/* t4 = y2 + y1 */
	vli_mod_add(t5, y2, y1, curve_prime, ndigits);
	/* t4 = y2 - y1 */
	vli_mod_sub(y2, y2, y1, curve_prime, ndigits);

	/* t6 = C - B */
	vli_mod_sub(t6, x2, x1, curve_prime, ndigits);
	/* t2 = y1 * (C - B) */
	vli_mod_mult_fast(y1, y1, t6, curve);
	/* t6 = B + C */
	vli_mod_add(t6, x1, x2, curve_prime, ndigits);
	/* t3 = (y2 - y1)^2 */
	vli_mod_square_fast(x2, y2, curve);
	/* t3 = x3 */
	vli_mod_sub(x2, x2, t6, curve_prime, ndigits);

	/* t7 = B - x3 */
	vli_mod_sub(t7, x1, x2, curve_prime, ndigits);
	/* t4 = (y2 - y1)*(B - x3) */
	vli_mod_mult_fast(y2, y2, t7, curve);
	/* t4 = y3 */
	vli_mod_sub(y2, y2, y1, curve_prime, ndigits);

	/* t7 = (y2 + y1)^2 = F */
	vli_mod_square_fast(t7, t5, curve);
	/* t7 = x3' */
	vli_mod_sub(t7, t7, t6, curve_prime, ndigits);
	/* t6 = x3' - B */
	vli_mod_sub(t6, t7, x1, curve_prime, ndigits);
	/* t6 = (y2 + y1)*(x3' - B) */
	vli_mod_mult_fast(t6, t6, t5, curve);
	/* t2 = y3' */
	vli_mod_sub(y1, t6, y1, curve_prime, ndigits);

	vli_set(x1, t7, ndigits);
पूर्ण

अटल व्योम ecc_poपूर्णांक_mult(काष्ठा ecc_poपूर्णांक *result,
			   स्थिर काष्ठा ecc_poपूर्णांक *poपूर्णांक, स्थिर u64 *scalar,
			   u64 *initial_z, स्थिर काष्ठा ecc_curve *curve,
			   अचिन्हित पूर्णांक ndigits)
अणु
	/* R0 and R1 */
	u64 rx[2][ECC_MAX_DIGITS];
	u64 ry[2][ECC_MAX_DIGITS];
	u64 z[ECC_MAX_DIGITS];
	u64 sk[2][ECC_MAX_DIGITS];
	u64 *curve_prime = curve->p;
	पूर्णांक i, nb;
	पूर्णांक num_bits;
	पूर्णांक carry;

	carry = vli_add(sk[0], scalar, curve->n, ndigits);
	vli_add(sk[1], sk[0], curve->n, ndigits);
	scalar = sk[!carry];
	num_bits = माप(u64) * ndigits * 8 + 1;

	vli_set(rx[1], poपूर्णांक->x, ndigits);
	vli_set(ry[1], poपूर्णांक->y, ndigits);

	xycz_initial_द्विगुन(rx[1], ry[1], rx[0], ry[0], initial_z, curve);

	क्रम (i = num_bits - 2; i > 0; i--) अणु
		nb = !vli_test_bit(scalar, i);
		xycz_add_c(rx[1 - nb], ry[1 - nb], rx[nb], ry[nb], curve);
		xycz_add(rx[nb], ry[nb], rx[1 - nb], ry[1 - nb], curve);
	पूर्ण

	nb = !vli_test_bit(scalar, 0);
	xycz_add_c(rx[1 - nb], ry[1 - nb], rx[nb], ry[nb], curve);

	/* Find final 1/Z value. */
	/* X1 - X0 */
	vli_mod_sub(z, rx[1], rx[0], curve_prime, ndigits);
	/* Yb * (X1 - X0) */
	vli_mod_mult_fast(z, z, ry[1 - nb], curve);
	/* xP * Yb * (X1 - X0) */
	vli_mod_mult_fast(z, z, poपूर्णांक->x, curve);

	/* 1 / (xP * Yb * (X1 - X0)) */
	vli_mod_inv(z, z, curve_prime, poपूर्णांक->ndigits);

	/* yP / (xP * Yb * (X1 - X0)) */
	vli_mod_mult_fast(z, z, poपूर्णांक->y, curve);
	/* Xb * yP / (xP * Yb * (X1 - X0)) */
	vli_mod_mult_fast(z, z, rx[1 - nb], curve);
	/* End 1/Z calculation */

	xycz_add(rx[nb], ry[nb], rx[1 - nb], ry[1 - nb], curve);

	apply_z(rx[0], ry[0], z, curve);

	vli_set(result->x, rx[0], ndigits);
	vli_set(result->y, ry[0], ndigits);
पूर्ण

/* Computes R = P + Q mod p */
अटल व्योम ecc_poपूर्णांक_add(स्थिर काष्ठा ecc_poपूर्णांक *result,
		   स्थिर काष्ठा ecc_poपूर्णांक *p, स्थिर काष्ठा ecc_poपूर्णांक *q,
		   स्थिर काष्ठा ecc_curve *curve)
अणु
	u64 z[ECC_MAX_DIGITS];
	u64 px[ECC_MAX_DIGITS];
	u64 py[ECC_MAX_DIGITS];
	अचिन्हित पूर्णांक ndigits = curve->g.ndigits;

	vli_set(result->x, q->x, ndigits);
	vli_set(result->y, q->y, ndigits);
	vli_mod_sub(z, result->x, p->x, curve->p, ndigits);
	vli_set(px, p->x, ndigits);
	vli_set(py, p->y, ndigits);
	xycz_add(px, py, result->x, result->y, curve);
	vli_mod_inv(z, z, curve->p, ndigits);
	apply_z(result->x, result->y, z, curve);
पूर्ण

/* Computes R = u1P + u2Q mod p using Shamir's trick.
 * Based on: Kenneth MacKay's micro-ecc (2014).
 */
व्योम ecc_poपूर्णांक_mult_shamir(स्थिर काष्ठा ecc_poपूर्णांक *result,
			   स्थिर u64 *u1, स्थिर काष्ठा ecc_poपूर्णांक *p,
			   स्थिर u64 *u2, स्थिर काष्ठा ecc_poपूर्णांक *q,
			   स्थिर काष्ठा ecc_curve *curve)
अणु
	u64 z[ECC_MAX_DIGITS];
	u64 sump[2][ECC_MAX_DIGITS];
	u64 *rx = result->x;
	u64 *ry = result->y;
	अचिन्हित पूर्णांक ndigits = curve->g.ndigits;
	अचिन्हित पूर्णांक num_bits;
	काष्ठा ecc_poपूर्णांक sum = ECC_POINT_INIT(sump[0], sump[1], ndigits);
	स्थिर काष्ठा ecc_poपूर्णांक *poपूर्णांकs[4];
	स्थिर काष्ठा ecc_poपूर्णांक *poपूर्णांक;
	अचिन्हित पूर्णांक idx;
	पूर्णांक i;

	ecc_poपूर्णांक_add(&sum, p, q, curve);
	poपूर्णांकs[0] = शून्य;
	poपूर्णांकs[1] = p;
	poपूर्णांकs[2] = q;
	poपूर्णांकs[3] = &sum;

	num_bits = max(vli_num_bits(u1, ndigits), vli_num_bits(u2, ndigits));
	i = num_bits - 1;
	idx = (!!vli_test_bit(u1, i)) | ((!!vli_test_bit(u2, i)) << 1);
	poपूर्णांक = poपूर्णांकs[idx];

	vli_set(rx, poपूर्णांक->x, ndigits);
	vli_set(ry, poपूर्णांक->y, ndigits);
	vli_clear(z + 1, ndigits - 1);
	z[0] = 1;

	क्रम (--i; i >= 0; i--) अणु
		ecc_poपूर्णांक_द्विगुन_jacobian(rx, ry, z, curve);
		idx = (!!vli_test_bit(u1, i)) | ((!!vli_test_bit(u2, i)) << 1);
		poपूर्णांक = poपूर्णांकs[idx];
		अगर (poपूर्णांक) अणु
			u64 tx[ECC_MAX_DIGITS];
			u64 ty[ECC_MAX_DIGITS];
			u64 tz[ECC_MAX_DIGITS];

			vli_set(tx, poपूर्णांक->x, ndigits);
			vli_set(ty, poपूर्णांक->y, ndigits);
			apply_z(tx, ty, z, curve);
			vli_mod_sub(tz, rx, tx, curve->p, ndigits);
			xycz_add(tx, ty, rx, ry, curve);
			vli_mod_mult_fast(z, z, tz, curve);
		पूर्ण
	पूर्ण
	vli_mod_inv(z, z, curve->p, ndigits);
	apply_z(rx, ry, z, curve);
पूर्ण
EXPORT_SYMBOL(ecc_poपूर्णांक_mult_shamir);

अटल पूर्णांक __ecc_is_key_valid(स्थिर काष्ठा ecc_curve *curve,
			      स्थिर u64 *निजी_key, अचिन्हित पूर्णांक ndigits)
अणु
	u64 one[ECC_MAX_DIGITS] = अणु 1, पूर्ण;
	u64 res[ECC_MAX_DIGITS];

	अगर (!निजी_key)
		वापस -EINVAL;

	अगर (curve->g.ndigits != ndigits)
		वापस -EINVAL;

	/* Make sure the निजी key is in the range [2, n-3]. */
	अगर (vli_cmp(one, निजी_key, ndigits) != -1)
		वापस -EINVAL;
	vli_sub(res, curve->n, one, ndigits);
	vli_sub(res, res, one, ndigits);
	अगर (vli_cmp(res, निजी_key, ndigits) != 1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक ecc_is_key_valid(अचिन्हित पूर्णांक curve_id, अचिन्हित पूर्णांक ndigits,
		     स्थिर u64 *निजी_key, अचिन्हित पूर्णांक निजी_key_len)
अणु
	पूर्णांक nbytes;
	स्थिर काष्ठा ecc_curve *curve = ecc_get_curve(curve_id);

	nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;

	अगर (निजी_key_len != nbytes)
		वापस -EINVAL;

	वापस __ecc_is_key_valid(curve, निजी_key, ndigits);
पूर्ण
EXPORT_SYMBOL(ecc_is_key_valid);

/*
 * ECC निजी keys are generated using the method of extra अक्रमom bits,
 * equivalent to that described in FIPS 186-4, Appendix B.4.1.
 *
 * d = (c mod(nै 1)) + 1    where c is a string of अक्रमom bits, 64 bits दीर्घer
 *                         than requested
 * 0 <= c mod(n-1) <= n-2  and implies that
 * 1 <= d <= n-1
 *
 * This method generates a निजी key unअगरormly distributed in the range
 * [1, n-1].
 */
पूर्णांक ecc_gen_privkey(अचिन्हित पूर्णांक curve_id, अचिन्हित पूर्णांक ndigits, u64 *privkey)
अणु
	स्थिर काष्ठा ecc_curve *curve = ecc_get_curve(curve_id);
	u64 priv[ECC_MAX_DIGITS];
	अचिन्हित पूर्णांक nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;
	अचिन्हित पूर्णांक nbits = vli_num_bits(curve->n, ndigits);
	पूर्णांक err;

	/* Check that N is included in Table 1 of FIPS 186-4, section 6.1.1 */
	अगर (nbits < 160 || ndigits > ARRAY_SIZE(priv))
		वापस -EINVAL;

	/*
	 * FIPS 186-4 recommends that the निजी key should be obtained from a
	 * RBG with a security strength equal to or greater than the security
	 * strength associated with N.
	 *
	 * The maximum security strength identअगरied by NIST SP800-57pt1r4 क्रम
	 * ECC is 256 (N >= 512).
	 *
	 * This condition is met by the शेष RNG because it selects a favored
	 * DRBG with a security strength of 256.
	 */
	अगर (crypto_get_शेष_rng())
		वापस -EFAULT;

	err = crypto_rng_get_bytes(crypto_शेष_rng, (u8 *)priv, nbytes);
	crypto_put_शेष_rng();
	अगर (err)
		वापस err;

	/* Make sure the निजी key is in the valid range. */
	अगर (__ecc_is_key_valid(curve, priv, ndigits))
		वापस -EINVAL;

	ecc_swap_digits(priv, privkey, ndigits);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ecc_gen_privkey);

पूर्णांक ecc_make_pub_key(अचिन्हित पूर्णांक curve_id, अचिन्हित पूर्णांक ndigits,
		     स्थिर u64 *निजी_key, u64 *खुला_key)
अणु
	पूर्णांक ret = 0;
	काष्ठा ecc_poपूर्णांक *pk;
	u64 priv[ECC_MAX_DIGITS];
	स्थिर काष्ठा ecc_curve *curve = ecc_get_curve(curve_id);

	अगर (!निजी_key || !curve || ndigits > ARRAY_SIZE(priv)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ecc_swap_digits(निजी_key, priv, ndigits);

	pk = ecc_alloc_poपूर्णांक(ndigits);
	अगर (!pk) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ecc_poपूर्णांक_mult(pk, &curve->g, priv, शून्य, curve, ndigits);

	/* SP800-56A rev 3 5.6.2.1.3 key check */
	अगर (ecc_is_pubkey_valid_full(curve, pk)) अणु
		ret = -EAGAIN;
		जाओ err_मुक्त_poपूर्णांक;
	पूर्ण

	ecc_swap_digits(pk->x, खुला_key, ndigits);
	ecc_swap_digits(pk->y, &खुला_key[ndigits], ndigits);

err_मुक्त_poपूर्णांक:
	ecc_मुक्त_poपूर्णांक(pk);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ecc_make_pub_key);

/* SP800-56A section 5.6.2.3.4 partial verअगरication: ephemeral keys only */
पूर्णांक ecc_is_pubkey_valid_partial(स्थिर काष्ठा ecc_curve *curve,
				काष्ठा ecc_poपूर्णांक *pk)
अणु
	u64 yy[ECC_MAX_DIGITS], xxx[ECC_MAX_DIGITS], w[ECC_MAX_DIGITS];

	अगर (WARN_ON(pk->ndigits != curve->g.ndigits))
		वापस -EINVAL;

	/* Check 1: Verअगरy key is not the zero poपूर्णांक. */
	अगर (ecc_poपूर्णांक_is_zero(pk))
		वापस -EINVAL;

	/* Check 2: Verअगरy key is in the range [1, p-1]. */
	अगर (vli_cmp(curve->p, pk->x, pk->ndigits) != 1)
		वापस -EINVAL;
	अगर (vli_cmp(curve->p, pk->y, pk->ndigits) != 1)
		वापस -EINVAL;

	/* Check 3: Verअगरy that y^2 == (x^3 + aतङx + b) mod p */
	vli_mod_square_fast(yy, pk->y, curve); /* y^2 */
	vli_mod_square_fast(xxx, pk->x, curve); /* x^2 */
	vli_mod_mult_fast(xxx, xxx, pk->x, curve); /* x^3 */
	vli_mod_mult_fast(w, curve->a, pk->x, curve); /* aतङx */
	vli_mod_add(w, w, curve->b, curve->p, pk->ndigits); /* aतङx + b */
	vli_mod_add(w, w, xxx, curve->p, pk->ndigits); /* x^3 + aतङx + b */
	अगर (vli_cmp(yy, w, pk->ndigits) != 0) /* Equation */
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ecc_is_pubkey_valid_partial);

/* SP800-56A section 5.6.2.3.3 full verअगरication */
पूर्णांक ecc_is_pubkey_valid_full(स्थिर काष्ठा ecc_curve *curve,
			     काष्ठा ecc_poपूर्णांक *pk)
अणु
	काष्ठा ecc_poपूर्णांक *nQ;

	/* Checks 1 through 3 */
	पूर्णांक ret = ecc_is_pubkey_valid_partial(curve, pk);

	अगर (ret)
		वापस ret;

	/* Check 4: Verअगरy that nQ is the zero poपूर्णांक. */
	nQ = ecc_alloc_poपूर्णांक(pk->ndigits);
	अगर (!nQ)
		वापस -ENOMEM;

	ecc_poपूर्णांक_mult(nQ, pk, curve->n, शून्य, curve, pk->ndigits);
	अगर (!ecc_poपूर्णांक_is_zero(nQ))
		ret = -EINVAL;

	ecc_मुक्त_poपूर्णांक(nQ);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ecc_is_pubkey_valid_full);

पूर्णांक crypto_ecdh_shared_secret(अचिन्हित पूर्णांक curve_id, अचिन्हित पूर्णांक ndigits,
			      स्थिर u64 *निजी_key, स्थिर u64 *खुला_key,
			      u64 *secret)
अणु
	पूर्णांक ret = 0;
	काष्ठा ecc_poपूर्णांक *product, *pk;
	u64 priv[ECC_MAX_DIGITS];
	u64 अक्रम_z[ECC_MAX_DIGITS];
	अचिन्हित पूर्णांक nbytes;
	स्थिर काष्ठा ecc_curve *curve = ecc_get_curve(curve_id);

	अगर (!निजी_key || !खुला_key || !curve ||
	    ndigits > ARRAY_SIZE(priv) || ndigits > ARRAY_SIZE(अक्रम_z)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;

	get_अक्रमom_bytes(अक्रम_z, nbytes);

	pk = ecc_alloc_poपूर्णांक(ndigits);
	अगर (!pk) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ecc_swap_digits(खुला_key, pk->x, ndigits);
	ecc_swap_digits(&खुला_key[ndigits], pk->y, ndigits);
	ret = ecc_is_pubkey_valid_partial(curve, pk);
	अगर (ret)
		जाओ err_alloc_product;

	ecc_swap_digits(निजी_key, priv, ndigits);

	product = ecc_alloc_poपूर्णांक(ndigits);
	अगर (!product) अणु
		ret = -ENOMEM;
		जाओ err_alloc_product;
	पूर्ण

	ecc_poपूर्णांक_mult(product, pk, priv, अक्रम_z, curve, ndigits);

	अगर (ecc_poपूर्णांक_is_zero(product)) अणु
		ret = -EFAULT;
		जाओ err_validity;
	पूर्ण

	ecc_swap_digits(product->x, secret, ndigits);

err_validity:
	memzero_explicit(priv, माप(priv));
	memzero_explicit(अक्रम_z, माप(अक्रम_z));
	ecc_मुक्त_poपूर्णांक(product);
err_alloc_product:
	ecc_मुक्त_poपूर्णांक(pk);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(crypto_ecdh_shared_secret);

MODULE_LICENSE("Dual BSD/GPL");
