<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * single precision
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754sp.h"

जोड़ ieee754sp ieee754sp_sub(जोड़ ieee754sp x, जोड़ ieee754sp y)
अणु
	पूर्णांक s;

	COMPXSP;
	COMPYSP;

	EXPLODEXSP;
	EXPLODEYSP;

	ieee754_clearcx();

	FLUSHXSP;
	FLUSHYSP;

	चयन (CLPAIR(xc, yc)) अणु
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_Sन_अंक):
		वापस ieee754sp_nanxcpt(y);

	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_Sन_अंक):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_Sन_अंक, IEEE754_CLASS_INF):
		वापस ieee754sp_nanxcpt(x);

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
		अगर (xs != ys)
			वापस x;
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754sp_indef();

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_INF):
		वापस ieee754sp_inf(ys ^ 1);

	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_DNORM):
		वापस x;

	/*
	 * Zero handling
	 */
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
		अगर (xs != ys)
			वापस x;
		अन्यथा
			वापस ieee754sp_zero(ieee754_csr.rm == FPU_CSR_RD);

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		वापस x;

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
		/* quick fix up */
		SPSIGN(y) ^= 1;
		वापस y;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_DNORM):
		SPDNORMX;
		fallthrough;
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_DNORM):
		SPDNORMY;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_NORM):
		SPDNORMX;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_NORM):
		अवरोध;
	पूर्ण
	/* flip sign of y and handle as add */
	ys ^= 1;

	निश्चित(xm & SP_HIDDEN_BIT);
	निश्चित(ym & SP_HIDDEN_BIT);


	/* provide guard,round and stick bit space */
	xm <<= 3;
	ym <<= 3;

	अगर (xe > ye) अणु
		/*
		 * have to shअगरt y fraction right to align
		 */
		s = xe - ye;
		ym = XSPSRS(ym, s);
		ye += s;
	पूर्ण अन्यथा अगर (ye > xe) अणु
		/*
		 * have to shअगरt x fraction right to align
		 */
		s = ye - xe;
		xm = XSPSRS(xm, s);
		xe += s;
	पूर्ण
	निश्चित(xe == ye);
	निश्चित(xe <= SP_EMAX);

	अगर (xs == ys) अणु
		/* generate 28 bit result of adding two 27 bit numbers
		 */
		xm = xm + ym;

		अगर (xm >> (SP_FBITS + 1 + 3)) अणु /* carry out */
			SPXSRSX1();	/* shअगरt preserving sticky */
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (xm >= ym) अणु
			xm = xm - ym;
		पूर्ण अन्यथा अणु
			xm = ym - xm;
			xs = ys;
		पूर्ण
		अगर (xm == 0) अणु
			अगर (ieee754_csr.rm == FPU_CSR_RD)
				वापस ieee754sp_zero(1);	/* round negative inf. => sign = -1 */
			अन्यथा
				वापस ieee754sp_zero(0);	/* other round modes   => sign = 1 */
		पूर्ण
		/* normalize to rounding precision
		 */
		जबतक ((xm >> (SP_FBITS + 3)) == 0) अणु
			xm <<= 1;
			xe--;
		पूर्ण
	पूर्ण

	वापस ieee754sp_क्रमmat(xs, xe, xm);
पूर्ण
