<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: MINअणु,Aपूर्ण.f
 * MIN : Scalar Floating-Poपूर्णांक Minimum
 * MINA: Scalar Floating-Poपूर्णांक argument with Minimum Absolute Value
 *
 * MIN.D : FPR[fd] = minNum(FPR[fs],FPR[ft])
 * MINA.D: FPR[fd] = maxNumMag(FPR[fs],FPR[ft])
 *
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 2015 Imagination Technologies, Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 */

#समावेश "ieee754dp.h"

जोड़ ieee754dp ieee754dp_fmin(जोड़ ieee754dp x, जोड़ ieee754dp y)
अणु
	COMPXDP;
	COMPYDP;

	EXPLODEXDP;
	EXPLODEYDP;

	FLUSHXDP;
	FLUSHYDP;

	ieee754_clearcx();

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

	/*
	 * Quiet NaN handling
	 */

	/*
	 *    The हाल of both inमाला_दो quiet NaNs
	 */
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_Qन_अंक):
		वापस x;

	/*
	 *    The हालs of exactly one input quiet NaN (numbers
	 *    are here preferred as वापसed values to NaNs)
	 */
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_Qन_अंक):
		वापस x;

	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_INF):
		वापस y;

	/*
	 * Infinity and zero handling
	 */
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		वापस xs ? x : y;

	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
		वापस ys ? y : x;

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
		वापस ieee754dp_zero(xs | ys);

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_DNORM):
		DPDNORMX;
		fallthrough;
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_DNORM):
		DPDNORMY;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_NORM):
		DPDNORMX;
	पूर्ण

	/* Finally get to करो some computation */

	निश्चित(xm & DP_HIDDEN_BIT);
	निश्चित(ym & DP_HIDDEN_BIT);

	/* Compare signs */
	अगर (xs > ys)
		वापस x;
	अन्यथा अगर (xs < ys)
		वापस y;

	/* Signs of inमाला_दो are the same, let's compare exponents */
	अगर (xs == 0) अणु
		/* Inमाला_दो are both positive */
		अगर (xe > ye)
			वापस y;
		अन्यथा अगर (xe < ye)
			वापस x;
	पूर्ण अन्यथा अणु
		/* Inमाला_दो are both negative */
		अगर (xe > ye)
			वापस x;
		अन्यथा अगर (xe < ye)
			वापस y;
	पूर्ण

	/* Signs and exponents of inमाला_दो are equal, let's compare mantissas */
	अगर (xs == 0) अणु
		/* Inमाला_दो are both positive, with equal signs and exponents */
		अगर (xm <= ym)
			वापस x;
		वापस y;
	पूर्ण
	/* Inमाला_दो are both negative, with equal signs and exponents */
	अगर (xm <= ym)
		वापस y;
	वापस x;
पूर्ण

जोड़ ieee754dp ieee754dp_fmina(जोड़ ieee754dp x, जोड़ ieee754dp y)
अणु
	COMPXDP;
	COMPYDP;

	EXPLODEXDP;
	EXPLODEYDP;

	FLUSHXDP;
	FLUSHYDP;

	ieee754_clearcx();

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

	/*
	 * Quiet NaN handling
	 */

	/*
	 *    The हाल of both inमाला_दो quiet NaNs
	 */
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_Qन_अंक):
		वापस x;

	/*
	 *    The हालs of exactly one input quiet NaN (numbers
	 *    are here preferred as वापसed values to NaNs)
	 */
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_Qन_अंक):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_Qन_अंक):
		वापस x;

	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_Qन_अंक, IEEE754_CLASS_INF):
		वापस y;

	/*
	 * Infinity and zero handling
	 */
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_INF):
		वापस ieee754dp_inf(xs | ys);

	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		वापस y;

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
		वापस x;

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
		वापस ieee754dp_zero(xs | ys);

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_DNORM):
		DPDNORMX;
		fallthrough;
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_DNORM):
		DPDNORMY;
		अवरोध;

	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_NORM):
		DPDNORMX;
	पूर्ण

	/* Finally get to करो some computation */

	निश्चित(xm & DP_HIDDEN_BIT);
	निश्चित(ym & DP_HIDDEN_BIT);

	/* Compare exponent */
	अगर (xe > ye)
		वापस y;
	अन्यथा अगर (xe < ye)
		वापस x;

	/* Compare mantissa */
	अगर (xm < ym)
		वापस x;
	अन्यथा अगर (xm > ym)
		वापस y;
	अन्यथा अगर (xs == 1)
		वापस x;
	वापस y;
पूर्ण
