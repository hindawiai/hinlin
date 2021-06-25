<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: MADDF.f (Fused Multiply Add)
 * MADDF.fmt: FPR[fd] = FPR[fd] + (FPR[fs] x FPR[ft])
 *
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 2015 Imagination Technologies, Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 */

#समावेश "ieee754dp.h"


/* 128 bits shअगरt right logical with rounding. */
अटल व्योम srl128(u64 *hptr, u64 *lptr, पूर्णांक count)
अणु
	u64 low;

	अगर (count >= 128) अणु
		*lptr = *hptr != 0 || *lptr != 0;
		*hptr = 0;
	पूर्ण अन्यथा अगर (count >= 64) अणु
		अगर (count == 64) अणु
			*lptr = *hptr | (*lptr != 0);
		पूर्ण अन्यथा अणु
			low = *lptr;
			*lptr = *hptr >> (count - 64);
			*lptr |= (*hptr << (128 - count)) != 0 || low != 0;
		पूर्ण
		*hptr = 0;
	पूर्ण अन्यथा अणु
		low = *lptr;
		*lptr = low >> count | *hptr << (64 - count);
		*lptr |= (low << (64 - count)) != 0;
		*hptr = *hptr >> count;
	पूर्ण
पूर्ण

अटल जोड़ ieee754dp _dp_maddf(जोड़ ieee754dp z, जोड़ ieee754dp x,
				 जोड़ ieee754dp y, क्रमागत maddf_flags flags)
अणु
	पूर्णांक re;
	पूर्णांक rs;
	अचिन्हित पूर्णांक lxm;
	अचिन्हित पूर्णांक hxm;
	अचिन्हित पूर्णांक lym;
	अचिन्हित पूर्णांक hym;
	u64 lrm;
	u64 hrm;
	u64 lzm;
	u64 hzm;
	u64 t;
	u64 at;
	पूर्णांक s;

	COMPXDP;
	COMPYDP;
	COMPZDP;

	EXPLODEXDP;
	EXPLODEYDP;
	EXPLODEZDP;

	FLUSHXDP;
	FLUSHYDP;
	FLUSHZDP;

	ieee754_clearcx();

	rs = xs ^ ys;
	अगर (flags & MADDF_NEGATE_PRODUCT)
		rs ^= 1;
	अगर (flags & MADDF_NEGATE_ADDITION)
		zs ^= 1;

	/*
	 * Handle the हालs when at least one of x, y or z is a NaN.
	 * Order of precedence is sNaN, qNaN and z, x, y.
	 */
	अगर (zc == IEEE754_CLASS_Sन_अंक)
		वापस ieee754dp_nanxcpt(z);
	अगर (xc == IEEE754_CLASS_Sन_अंक)
		वापस ieee754dp_nanxcpt(x);
	अगर (yc == IEEE754_CLASS_Sन_अंक)
		वापस ieee754dp_nanxcpt(y);
	अगर (zc == IEEE754_CLASS_Qन_अंक)
		वापस z;
	अगर (xc == IEEE754_CLASS_Qन_अंक)
		वापस x;
	अगर (yc == IEEE754_CLASS_Qन_अंक)
		वापस y;

	अगर (zc == IEEE754_CLASS_DNORM)
		DPDNORMZ;
	/* ZERO z हालs are handled separately below */

	चयन (CLPAIR(xc, yc)) अणु

	/*
	 * Infinity handling
	 */
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754dp_indef();

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_INF):
		अगर ((zc == IEEE754_CLASS_INF) && (zs != rs)) अणु
			/*
			 * Cases of addition of infinities with opposite signs
			 * or subtraction of infinities with same signs.
			 */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			वापस ieee754dp_indef();
		पूर्ण
		/*
		 * z is here either not an infinity, or an infinity having the
		 * same sign as product (x*y). The result must be an infinity,
		 * and its sign is determined only by the sign of product (x*y).
		 */
		वापस ieee754dp_inf(rs);

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754dp_inf(zs);
		अगर (zc == IEEE754_CLASS_ZERO) अणु
			/* Handle हालs +0 + (-0) and similar ones. */
			अगर (zs == rs)
				/*
				 * Cases of addition of zeros of equal signs
				 * or subtraction of zeroes of opposite signs.
				 * The sign of the resulting zero is in any
				 * such हाल determined only by the sign of z.
				 */
				वापस z;

			वापस ieee754dp_zero(ieee754_csr.rm == FPU_CSR_RD);
		पूर्ण
		/* x*y is here 0, and z is not 0, so just वापस z */
		वापस z;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_DNORM):
		DPDNORMX;
		fallthrough;
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_DNORM):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754dp_inf(zs);
		DPDNORMY;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_NORM):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754dp_inf(zs);
		DPDNORMX;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_NORM):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754dp_inf(zs);
		/* जारी to real computations */
	पूर्ण

	/* Finally get to करो some computation */

	/*
	 * Do the multiplication bit first
	 *
	 * rm = xm * ym, re = xe + ye basically
	 *
	 * At this poपूर्णांक xm and ym should have been normalized.
	 */
	निश्चित(xm & DP_HIDDEN_BIT);
	निश्चित(ym & DP_HIDDEN_BIT);

	re = xe + ye;

	/* shunt to top of word */
	xm <<= 64 - (DP_FBITS + 1);
	ym <<= 64 - (DP_FBITS + 1);

	/*
	 * Multiply 64 bits xm and ym to give 128 bits result in hrm:lrm.
	 */

	lxm = xm;
	hxm = xm >> 32;
	lym = ym;
	hym = ym >> 32;

	lrm = DPXMULT(lxm, lym);
	hrm = DPXMULT(hxm, hym);

	t = DPXMULT(lxm, hym);

	at = lrm + (t << 32);
	hrm += at < lrm;
	lrm = at;

	hrm = hrm + (t >> 32);

	t = DPXMULT(hxm, lym);

	at = lrm + (t << 32);
	hrm += at < lrm;
	lrm = at;

	hrm = hrm + (t >> 32);

	/* Put explicit bit at bit 126 अगर necessary */
	अगर ((पूर्णांक64_t)hrm < 0) अणु
		lrm = (hrm << 63) | (lrm >> 1);
		hrm = hrm >> 1;
		re++;
	पूर्ण

	निश्चित(hrm & (1 << 62));

	अगर (zc == IEEE754_CLASS_ZERO) अणु
		/*
		 * Move explicit bit from bit 126 to bit 55 since the
		 * ieee754dp_क्रमmat code expects the mantissa to be
		 * 56 bits wide (53 + 3 rounding bits).
		 */
		srl128(&hrm, &lrm, (126 - 55));
		वापस ieee754dp_क्रमmat(rs, re, lrm);
	पूर्ण

	/* Move explicit bit from bit 52 to bit 126 */
	lzm = 0;
	hzm = zm << 10;
	निश्चित(hzm & (1 << 62));

	/* Make the exponents the same */
	अगर (ze > re) अणु
		/*
		 * Have to shअगरt y fraction right to align.
		 */
		s = ze - re;
		srl128(&hrm, &lrm, s);
		re += s;
	पूर्ण अन्यथा अगर (re > ze) अणु
		/*
		 * Have to shअगरt x fraction right to align.
		 */
		s = re - ze;
		srl128(&hzm, &lzm, s);
		ze += s;
	पूर्ण
	निश्चित(ze == re);
	निश्चित(ze <= DP_EMAX);

	/* Do the addition */
	अगर (zs == rs) अणु
		/*
		 * Generate 128 bit result by adding two 127 bit numbers
		 * leaving result in hzm:lzm, zs and ze.
		 */
		hzm = hzm + hrm + (lzm > (lzm + lrm));
		lzm = lzm + lrm;
		अगर ((पूर्णांक64_t)hzm < 0) अणु        /* carry out */
			srl128(&hzm, &lzm, 1);
			ze++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hzm > hrm || (hzm == hrm && lzm >= lrm)) अणु
			hzm = hzm - hrm - (lzm < lrm);
			lzm = lzm - lrm;
		पूर्ण अन्यथा अणु
			hzm = hrm - hzm - (lrm < lzm);
			lzm = lrm - lzm;
			zs = rs;
		पूर्ण
		अगर (lzm == 0 && hzm == 0)
			वापस ieee754dp_zero(ieee754_csr.rm == FPU_CSR_RD);

		/*
		 * Put explicit bit at bit 126 अगर necessary.
		 */
		अगर (hzm == 0) अणु
			/* left shअगरt by 63 or 64 bits */
			अगर ((पूर्णांक64_t)lzm < 0) अणु
				/* MSB of lzm is the explicit bit */
				hzm = lzm >> 1;
				lzm = lzm << 63;
				ze -= 63;
			पूर्ण अन्यथा अणु
				hzm = lzm;
				lzm = 0;
				ze -= 64;
			पूर्ण
		पूर्ण

		t = 0;
		जबतक ((hzm >> (62 - t)) == 0)
			t++;

		निश्चित(t <= 62);
		अगर (t) अणु
			hzm = hzm << t | lzm >> (64 - t);
			lzm = lzm << t;
			ze -= t;
		पूर्ण
	पूर्ण

	/*
	 * Move explicit bit from bit 126 to bit 55 since the
	 * ieee754dp_क्रमmat code expects the mantissa to be
	 * 56 bits wide (53 + 3 rounding bits).
	 */
	srl128(&hzm, &lzm, (126 - 55));

	वापस ieee754dp_क्रमmat(zs, ze, lzm);
पूर्ण

जोड़ ieee754dp ieee754dp_maddf(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y)
अणु
	वापस _dp_maddf(z, x, y, 0);
पूर्ण

जोड़ ieee754dp ieee754dp_msubf(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y)
अणु
	वापस _dp_maddf(z, x, y, MADDF_NEGATE_PRODUCT);
पूर्ण

जोड़ ieee754dp ieee754dp_madd(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y)
अणु
	वापस _dp_maddf(z, x, y, 0);
पूर्ण

जोड़ ieee754dp ieee754dp_msub(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y)
अणु
	वापस _dp_maddf(z, x, y, MADDF_NEGATE_ADDITION);
पूर्ण

जोड़ ieee754dp ieee754dp_nmadd(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y)
अणु
	वापस _dp_maddf(z, x, y, MADDF_NEGATE_PRODUCT|MADDF_NEGATE_ADDITION);
पूर्ण

जोड़ ieee754dp ieee754dp_nmsub(जोड़ ieee754dp z, जोड़ ieee754dp x,
				जोड़ ieee754dp y)
अणु
	वापस _dp_maddf(z, x, y, MADDF_NEGATE_PRODUCT);
पूर्ण
