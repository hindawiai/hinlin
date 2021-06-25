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

जोड़ ieee754dp ieee754dp_भाग(जोड़ ieee754dp x, जोड़ ieee754dp y)
अणु
	u64 rm;
	पूर्णांक re;
	u64 bm;

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
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754dp_indef();

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_INF):
		वापस ieee754dp_zero(xs ^ ys);

	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_DNORM):
		वापस ieee754dp_inf(xs ^ ys);

	/*
	 * Zero handling
	 */
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754dp_indef();

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		ieee754_setcx(IEEE754_ZERO_DIVIDE);
		वापस ieee754dp_inf(xs ^ ys);

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
		वापस ieee754dp_zero(xs == ys ? 0 : 1);

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

	/* provide rounding space */
	xm <<= 3;
	ym <<= 3;

	/* now the dirty work */

	rm = 0;
	re = xe - ye;

	क्रम (bm = DP_MBIT(DP_FBITS + 2); bm; bm >>= 1) अणु
		अगर (xm >= ym) अणु
			xm -= ym;
			rm |= bm;
			अगर (xm == 0)
				अवरोध;
		पूर्ण
		xm <<= 1;
	पूर्ण

	rm <<= 1;
	अगर (xm)
		rm |= 1;	/* have reमुख्यder, set sticky */

	निश्चित(rm);

	/*
	 * Normalise rm to rounding precision ?
	 */
	जबतक ((rm >> (DP_FBITS + 3)) == 0) अणु
		rm <<= 1;
		re--;
	पूर्ण

	वापस ieee754dp_क्रमmat(xs == ys ? 0 : 1, re, rm);
पूर्ण
