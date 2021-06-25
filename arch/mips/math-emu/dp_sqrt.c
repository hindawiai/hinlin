<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision square root
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754dp.h"

अटल स्थिर अचिन्हित पूर्णांक table[] = अणु
	0, 1204, 3062, 5746, 9193, 13348, 18162, 23592,
	29598, 36145, 43202, 50740, 58733, 67158, 75992,
	85215, 83599, 71378, 60428, 50647, 41945, 34246,
	27478, 21581, 16499, 12183, 8588, 5674, 3403,
	1742, 661, 130
पूर्ण;

जोड़ ieee754dp ieee754dp_वर्ग_मूल(जोड़ ieee754dp x)
अणु
	काष्ठा _ieee754_csr oldcsr;
	जोड़ ieee754dp y, z, t;
	अचिन्हित पूर्णांक scalx, yh;
	COMPXDP;

	EXPLODEXDP;
	ieee754_clearcx();
	FLUSHXDP;

	/* x == INF or न_अंक? */
	चयन (xc) अणु
	हाल IEEE754_CLASS_Sन_अंक:
		वापस ieee754dp_nanxcpt(x);

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
			वापस ieee754dp_indef();
		पूर्ण
		/* वर्ग_मूल(+Inf) = Inf */
		वापस x;

	हाल IEEE754_CLASS_DNORM:
		DPDNORMX;
		fallthrough;
	हाल IEEE754_CLASS_NORM:
		अगर (xs) अणु
			/* वर्ग_मूल(-x) = Nan */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			वापस ieee754dp_indef();
		पूर्ण
		अवरोध;
	पूर्ण

	/* save old csr; चयन off INX enable & flag; set RN rounding */
	oldcsr = ieee754_csr;
	ieee754_csr.mx &= ~IEEE754_INEXACT;
	ieee754_csr.sx &= ~IEEE754_INEXACT;
	ieee754_csr.rm = FPU_CSR_RN;

	/* adjust exponent to prevent overflow */
	scalx = 0;
	अगर (xe > 512) अणु		/* x > 2**-512? */
		xe -= 512;	/* x = x / 2**512 */
		scalx += 256;
	पूर्ण अन्यथा अगर (xe < -512) अणु /* x < 2**-512? */
		xe += 512;	/* x = x * 2**512 */
		scalx -= 256;
	पूर्ण

	x = builddp(0, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
	y = x;

	/* magic initial approximation to almost 8 sig. bits */
	yh = y.bits >> 32;
	yh = (yh >> 1) + 0x1ff80000;
	yh = yh - table[(yh >> 15) & 31];
	y.bits = ((u64) yh << 32) | (y.bits & 0xffffffff);

	/* Heron's rule once with correction to improve to ~18 sig. bits */
	/* t=x/y; y=y+t; py[n0]=py[n0]-0x00100006; py[n1]=0; */
	t = ieee754dp_भाग(x, y);
	y = ieee754dp_add(y, t);
	y.bits -= 0x0010000600000000LL;
	y.bits &= 0xffffffff00000000LL;

	/* triple to almost 56 sig. bits: y ~= वर्ग_मूल(x) to within 1 ulp */
	/* t=y*y; z=t;	pt[n0]+=0x00100000; t+=z; z=(x-z)*y; */
	t = ieee754dp_mul(y, y);
	z = t;
	t.bexp += 0x001;
	t = ieee754dp_add(t, z);
	z = ieee754dp_mul(ieee754dp_sub(x, z), y);

	/* t=z/(t+x) ;	pt[n0]+=0x00100000; y+=t; */
	t = ieee754dp_भाग(z, ieee754dp_add(t, x));
	t.bexp += 0x001;
	y = ieee754dp_add(y, t);

	/* twiddle last bit to क्रमce y correctly rounded */

	/* set RZ, clear INEX flag */
	ieee754_csr.rm = FPU_CSR_RZ;
	ieee754_csr.sx &= ~IEEE754_INEXACT;

	/* t=x/y; ...chopped quotient, possibly inexact */
	t = ieee754dp_भाग(x, y);

	अगर (ieee754_csr.sx & IEEE754_INEXACT || t.bits != y.bits) अणु

		अगर (!(ieee754_csr.sx & IEEE754_INEXACT))
			/* t = t-ulp */
			t.bits -= 1;

		/* add inexact to result status */
		oldcsr.cx |= IEEE754_INEXACT;
		oldcsr.sx |= IEEE754_INEXACT;

		चयन (oldcsr.rm) अणु
		हाल FPU_CSR_RU:
			y.bits += 1;
			fallthrough;
		हाल FPU_CSR_RN:
			t.bits += 1;
			अवरोध;
		पूर्ण

		/* y=y+t; ...chopped sum */
		y = ieee754dp_add(y, t);

		/* adjust scalx क्रम correctly rounded वर्ग_मूल(x) */
		scalx -= 1;
	पूर्ण

	/* py[n0]=py[n0]+scalx; ...scale back y */
	y.bexp += scalx;

	/* restore rounding mode, possibly set inexact */
	ieee754_csr = oldcsr;

	वापस y;
पूर्ण
