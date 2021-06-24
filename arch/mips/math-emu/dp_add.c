<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: common utilities
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754dp.h"

जोड़ ieee754dp ieee754dp_add(जोड़ ieee754dp x, जोड़ ieee754dp y)
अणु
	पूर्णांक s;

	COMPXDP;
	COMPYDP;

	EXPLODEXDP;
	EXPLODEYDP;

	ieee754_clearcx();

	FLUSHXDP;
	FLUSHYDP;

	चयन (CLPAIR(xc, yc)) अणु
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_Sन_अंक):
		वापस ieee754dp_nanxcpt(y);

	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_INF):
		वापस ieee754dp_nanxcpt(x);

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_Qन_अंक):
		वापस y;

	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_INF):
		वापस x;


	/*
	 * Infinity handling
	 */
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_INF):
		अगर (xs == ys)
			वापस x;
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754dp_indef();

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_INF):
		वापस y;

	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_DNORM):
		वापस x;

	/*
	 * Zero handling
	 */
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
		अगर (xs == ys)
			वापस x;
		अन्यथा
			वापस ieee754dp_zero(ieee754_csr.rm == FPU_CSR_RD);

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		वापस x;

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
		वापस y;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_DNORM):
		DPDNORMX;
		fallthrough;
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_DNORM):
		DPDNORMY;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_NORM):
		DPDNORMX;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_NORM):
		अवरोध;
	पूर्ण
	निश्चित(xm & DP_HIDDEN_BIT);
	निश्चित(ym & DP_HIDDEN_BIT);

	/*
	 * Provide guard,round and stick bit space.
	 */
	xm <<= 3;
	ym <<= 3;

	अगर (xe > ye) अणु
		/*
		 * Have to shअगरt y fraction right to align.
		 */
		s = xe - ye;
		ym = XDPSRS(ym, s);
		ye += s;
	पूर्ण अन्यथा अगर (ye > xe) अणु
		/*
		 * Have to shअगरt x fraction right to align.
		 */
		s = ye - xe;
		xm = XDPSRS(xm, s);
		xe += s;
	पूर्ण
	निश्चित(xe == ye);
	निश्चित(xe <= DP_EMAX);

	अगर (xs == ys) अणु
		/*
		 * Generate 28 bit result of adding two 27 bit numbers
		 * leaving result in xm, xs and xe.
		 */
		xm = xm + ym;

		अगर (xm >> (DP_FBITS + 1 + 3)) अणु /* carry out */
			xm = XDPSRS1(xm);
			xe++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (xm >= ym) अणु
			xm = xm - ym;
		पूर्ण अन्यथा अणु
			xm = ym - xm;
			xs = ys;
		पूर्ण
		अगर (xm == 0)
			वापस ieee754dp_zero(ieee754_csr.rm == FPU_CSR_RD);

		/*
		 * Normalize to rounding precision.
		 */
		जबतक ((xm >> (DP_FBITS + 3)) == 0) अणु
			xm <<= 1;
			xe--;
		पूर्ण
	पूर्ण

	वापस ieee754dp_क्रमmat(xs, xe, xm);
पूर्ण
