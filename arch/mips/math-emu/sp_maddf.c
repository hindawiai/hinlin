<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IEEE754 भग्नing poपूर्णांक arithmetic
 * single precision: MADDF.f (Fused Multiply Add)
 * MADDF.fmt: FPR[fd] = FPR[fd] + (FPR[fs] x FPR[ft])
 *
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 2015 Imagination Technologies, Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 */

#समावेश "ieee754sp.h"


अटल जोड़ ieee754sp _sp_maddf(जोड़ ieee754sp z, जोड़ ieee754sp x,
				 जोड़ ieee754sp y, क्रमागत maddf_flags flags)
अणु
	पूर्णांक re;
	पूर्णांक rs;
	अचिन्हित पूर्णांक rm;
	u64 rm64;
	u64 zm64;
	पूर्णांक s;

	COMPXSP;
	COMPYSP;
	COMPZSP;

	EXPLODEXSP;
	EXPLODEYSP;
	EXPLODEZSP;

	FLUSHXSP;
	FLUSHYSP;
	FLUSHZSP;

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
		वापस ieee754sp_nanxcpt(z);
	अगर (xc == IEEE754_CLASS_Sन_अंक)
		वापस ieee754sp_nanxcpt(x);
	अगर (yc == IEEE754_CLASS_Sन_अंक)
		वापस ieee754sp_nanxcpt(y);
	अगर (zc == IEEE754_CLASS_Qन_अंक)
		वापस z;
	अगर (xc == IEEE754_CLASS_Qन_अंक)
		वापस x;
	अगर (yc == IEEE754_CLASS_Qन_अंक)
		वापस y;

	अगर (zc == IEEE754_CLASS_DNORM)
		SPDNORMZ;
	/* ZERO z हालs are handled separately below */

	चयन (CLPAIR(xc, yc)) अणु


	/*
	 * Infinity handling
	 */
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754sp_indef();

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
			वापस ieee754sp_indef();
		पूर्ण
		/*
		 * z is here either not an infinity, or an infinity having the
		 * same sign as product (x*y). The result must be an infinity,
		 * and its sign is determined only by the sign of product (x*y).
		 */
		वापस ieee754sp_inf(rs);

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754sp_inf(zs);
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

			वापस ieee754sp_zero(ieee754_csr.rm == FPU_CSR_RD);
		पूर्ण
		/* x*y is here 0, and z is not 0, so just वापस z */
		वापस z;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_DNORM):
		SPDNORMX;
		fallthrough;
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_DNORM):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754sp_inf(zs);
		SPDNORMY;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_NORM):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754sp_inf(zs);
		SPDNORMX;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_NORM):
		अगर (zc == IEEE754_CLASS_INF)
			वापस ieee754sp_inf(zs);
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

	/* rm = xm * ym, re = xe+ye basically */
	निश्चित(xm & SP_HIDDEN_BIT);
	निश्चित(ym & SP_HIDDEN_BIT);

	re = xe + ye;

	/* Multiple 24 bit xm and ym to give 48 bit results */
	rm64 = (uपूर्णांक64_t)xm * ym;

	/* Shunt to top of word */
	rm64 = rm64 << 16;

	/* Put explicit bit at bit 62 अगर necessary */
	अगर ((पूर्णांक64_t) rm64 < 0) अणु
		rm64 = rm64 >> 1;
		re++;
	पूर्ण

	निश्चित(rm64 & (1 << 62));

	अगर (zc == IEEE754_CLASS_ZERO) अणु
		/*
		 * Move explicit bit from bit 62 to bit 26 since the
		 * ieee754sp_क्रमmat code expects the mantissa to be
		 * 27 bits wide (24 + 3 rounding bits).
		 */
		rm = XSPSRS64(rm64, (62 - 26));
		वापस ieee754sp_क्रमmat(rs, re, rm);
	पूर्ण

	/* Move explicit bit from bit 23 to bit 62 */
	zm64 = (uपूर्णांक64_t)zm << (62 - 23);
	निश्चित(zm64 & (1 << 62));

	/* Make the exponents the same */
	अगर (ze > re) अणु
		/*
		 * Have to shअगरt r fraction right to align.
		 */
		s = ze - re;
		rm64 = XSPSRS64(rm64, s);
		re += s;
	पूर्ण अन्यथा अगर (re > ze) अणु
		/*
		 * Have to shअगरt z fraction right to align.
		 */
		s = re - ze;
		zm64 = XSPSRS64(zm64, s);
		ze += s;
	पूर्ण
	निश्चित(ze == re);
	निश्चित(ze <= SP_EMAX);

	/* Do the addition */
	अगर (zs == rs) अणु
		/*
		 * Generate 64 bit result by adding two 63 bit numbers
		 * leaving result in zm64, zs and ze.
		 */
		zm64 = zm64 + rm64;
		अगर ((पूर्णांक64_t)zm64 < 0) अणु	/* carry out */
			zm64 = XSPSRS1(zm64);
			ze++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (zm64 >= rm64) अणु
			zm64 = zm64 - rm64;
		पूर्ण अन्यथा अणु
			zm64 = rm64 - zm64;
			zs = rs;
		पूर्ण
		अगर (zm64 == 0)
			वापस ieee754sp_zero(ieee754_csr.rm == FPU_CSR_RD);

		/*
		 * Put explicit bit at bit 62 अगर necessary.
		 */
		जबतक ((zm64 >> 62) == 0) अणु
			zm64 <<= 1;
			ze--;
		पूर्ण
	पूर्ण

	/*
	 * Move explicit bit from bit 62 to bit 26 since the
	 * ieee754sp_क्रमmat code expects the mantissa to be
	 * 27 bits wide (24 + 3 rounding bits).
	 */
	zm = XSPSRS64(zm64, (62 - 26));

	वापस ieee754sp_क्रमmat(zs, ze, zm);
पूर्ण

जोड़ ieee754sp ieee754sp_maddf(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y)
अणु
	वापस _sp_maddf(z, x, y, 0);
पूर्ण

जोड़ ieee754sp ieee754sp_msubf(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y)
अणु
	वापस _sp_maddf(z, x, y, MADDF_NEGATE_PRODUCT);
पूर्ण

जोड़ ieee754sp ieee754sp_madd(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y)
अणु
	वापस _sp_maddf(z, x, y, 0);
पूर्ण

जोड़ ieee754sp ieee754sp_msub(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y)
अणु
	वापस _sp_maddf(z, x, y, MADDF_NEGATE_ADDITION);
पूर्ण

जोड़ ieee754sp ieee754sp_nmadd(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y)
अणु
	वापस _sp_maddf(z, x, y, MADDF_NEGATE_PRODUCT|MADDF_NEGATE_ADDITION);
पूर्ण

जोड़ ieee754sp ieee754sp_nmsub(जोड़ ieee754sp z, जोड़ ieee754sp x,
				जोड़ ieee754sp y)
अणु
	वापस _sp_maddf(z, x, y, MADDF_NEGATE_PRODUCT);
पूर्ण
