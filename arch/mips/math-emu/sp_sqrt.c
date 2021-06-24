<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * single precision square root
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754sp.h"

जोड़ ieee754sp ieee754sp_वर्ग_मूल(जोड़ ieee754sp x)
अणु
	पूर्णांक ix, s, q, m, t, i;
	अचिन्हित पूर्णांक r;
	COMPXSP;

	/* take care of Inf and NaN */

	EXPLODEXSP;
	ieee754_clearcx();
	FLUSHXSP;

	/* x == INF or न_अंक? */
	चयन (xc) अणु
	हाल IEEE754_CLASS_Sन_अंक:
		वापस ieee754sp_nanxcpt(x);

	हाल IEEE754_CLASS_Qन_अंक:
		/* वर्ग_मूल(Nan) = Nan */
		वापस x;

	हाल IEEE754_CLASS_ZERO:
		/* वर्ग_मूल(0) = 0 */
		वापस x;

	हाल IEEE754_CLASS_INF:
		अगर (xs) अणु
			/* वर्ग_मूल(-Inf) = Nan */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			वापस ieee754sp_indef();
		पूर्ण
		/* वर्ग_मूल(+Inf) = Inf */
		वापस x;

	हाल IEEE754_CLASS_DNORM:
	हाल IEEE754_CLASS_NORM:
		अगर (xs) अणु
			/* वर्ग_मूल(-x) = Nan */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			वापस ieee754sp_indef();
		पूर्ण
		अवरोध;
	पूर्ण

	ix = x.bits;

	/* normalize x */
	m = (ix >> 23);
	अगर (m == 0) अणु		/* subnormal x */
		क्रम (i = 0; (ix & 0x00800000) == 0; i++)
			ix <<= 1;
		m -= i - 1;
	पूर्ण
	m -= 127;		/* unbias exponent */
	ix = (ix & 0x007fffff) | 0x00800000;
	अगर (m & 1)		/* odd m, द्विगुन x to make it even */
		ix += ix;
	m >>= 1;		/* m = [m/2] */

	/* generate वर्ग_मूल(x) bit by bit */
	ix += ix;
	s = 0;
	q = 0;			/* q = वर्ग_मूल(x) */
	r = 0x01000000;		/* r = moving bit from right to left */

	जबतक (r != 0) अणु
		t = s + r;
		अगर (t <= ix) अणु
			s = t + r;
			ix -= t;
			q += r;
		पूर्ण
		ix += ix;
		r >>= 1;
	पूर्ण

	अगर (ix != 0) अणु
		ieee754_setcx(IEEE754_INEXACT);
		चयन (ieee754_csr.rm) अणु
		हाल FPU_CSR_RU:
			q += 2;
			अवरोध;
		हाल FPU_CSR_RN:
			q += (q & 1);
			अवरोध;
		पूर्ण
	पूर्ण
	ix = (q >> 1) + 0x3f000000;
	ix += (m << 23);
	x.bits = ix;
	वापस x;
पूर्ण
