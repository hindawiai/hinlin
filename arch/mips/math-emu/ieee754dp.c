<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: common utilities
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश <linux/compiler.h>

#समावेश "ieee754dp.h"

पूर्णांक ieee754dp_class(जोड़ ieee754dp x)
अणु
	COMPXDP;
	EXPLODEXDP;
	वापस xc;
पूर्ण

अटल अंतरभूत पूर्णांक ieee754dp_isnan(जोड़ ieee754dp x)
अणु
	वापस ieee754_class_nan(ieee754dp_class(x));
पूर्ण

अटल अंतरभूत पूर्णांक ieee754dp_issnan(जोड़ ieee754dp x)
अणु
	पूर्णांक qbit;

	निश्चित(ieee754dp_isnan(x));
	qbit = (DPMANT(x) & DP_MBIT(DP_FBITS - 1)) == DP_MBIT(DP_FBITS - 1);
	वापस ieee754_csr.nan2008 ^ qbit;
पूर्ण


/*
 * Raise the Invalid Operation IEEE 754 exception
 * and convert the संकेतing NaN supplied to a quiet NaN.
 */
जोड़ ieee754dp __cold ieee754dp_nanxcpt(जोड़ ieee754dp r)
अणु
	निश्चित(ieee754dp_issnan(r));

	ieee754_setcx(IEEE754_INVALID_OPERATION);
	अगर (ieee754_csr.nan2008) अणु
		DPMANT(r) |= DP_MBIT(DP_FBITS - 1);
	पूर्ण अन्यथा अणु
		DPMANT(r) &= ~DP_MBIT(DP_FBITS - 1);
		अगर (!ieee754dp_isnan(r))
			DPMANT(r) |= DP_MBIT(DP_FBITS - 2);
	पूर्ण

	वापस r;
पूर्ण

अटल u64 ieee754dp_get_rounding(पूर्णांक sn, u64 xm)
अणु
	/* inexact must round of 3 bits
	 */
	अगर (xm & (DP_MBIT(3) - 1)) अणु
		चयन (ieee754_csr.rm) अणु
		हाल FPU_CSR_RZ:
			अवरोध;
		हाल FPU_CSR_RN:
			xm += 0x3 + ((xm >> 3) & 1);
			/* xm += (xm&0x8)?0x4:0x3 */
			अवरोध;
		हाल FPU_CSR_RU:	/* toward +Infinity */
			अगर (!sn)	/* ?? */
				xm += 0x8;
			अवरोध;
		हाल FPU_CSR_RD:	/* toward -Infinity */
			अगर (sn) /* ?? */
				xm += 0x8;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस xm;
पूर्ण


/* generate a normal/denormal number with over,under handling
 * sn is sign
 * xe is an unbiased exponent
 * xm is 3bit extended precision value.
 */
जोड़ ieee754dp ieee754dp_क्रमmat(पूर्णांक sn, पूर्णांक xe, u64 xm)
अणु
	निश्चित(xm);		/* we करोn't gen exact zeros (probably should) */

	निश्चित((xm >> (DP_FBITS + 1 + 3)) == 0);	/* no excess */
	निश्चित(xm & (DP_HIDDEN_BIT << 3));

	अगर (xe < DP_EMIN) अणु
		/* strip lower bits */
		पूर्णांक es = DP_EMIN - xe;

		अगर (ieee754_csr.nod) अणु
			ieee754_setcx(IEEE754_UNDERFLOW);
			ieee754_setcx(IEEE754_INEXACT);

			चयन(ieee754_csr.rm) अणु
			हाल FPU_CSR_RN:
			हाल FPU_CSR_RZ:
				वापस ieee754dp_zero(sn);
			हाल FPU_CSR_RU:    /* toward +Infinity */
				अगर (sn == 0)
					वापस ieee754dp_min(0);
				अन्यथा
					वापस ieee754dp_zero(1);
			हाल FPU_CSR_RD:    /* toward -Infinity */
				अगर (sn == 0)
					वापस ieee754dp_zero(0);
				अन्यथा
					वापस ieee754dp_min(1);
			पूर्ण
		पूर्ण

		अगर (xe == DP_EMIN - 1 &&
		    ieee754dp_get_rounding(sn, xm) >> (DP_FBITS + 1 + 3))
		अणु
			/* Not tiny after rounding */
			ieee754_setcx(IEEE754_INEXACT);
			xm = ieee754dp_get_rounding(sn, xm);
			xm >>= 1;
			/* Clear grs bits */
			xm &= ~(DP_MBIT(3) - 1);
			xe++;
		पूर्ण
		अन्यथा अणु
			/* sticky right shअगरt es bits
			 */
			xm = XDPSRS(xm, es);
			xe += es;
			निश्चित((xm & (DP_HIDDEN_BIT << 3)) == 0);
			निश्चित(xe == DP_EMIN);
		पूर्ण
	पूर्ण
	अगर (xm & (DP_MBIT(3) - 1)) अणु
		ieee754_setcx(IEEE754_INEXACT);
		अगर ((xm & (DP_HIDDEN_BIT << 3)) == 0) अणु
			ieee754_setcx(IEEE754_UNDERFLOW);
		पूर्ण

		/* inexact must round of 3 bits
		 */
		xm = ieee754dp_get_rounding(sn, xm);
		/* adjust exponent क्रम rounding add overflowing
		 */
		अगर (xm >> (DP_FBITS + 3 + 1)) अणु
			/* add causes mantissa overflow */
			xm >>= 1;
			xe++;
		पूर्ण
	पूर्ण
	/* strip grs bits */
	xm >>= 3;

	निश्चित((xm >> (DP_FBITS + 1)) == 0);	/* no excess */
	निश्चित(xe >= DP_EMIN);

	अगर (xe > DP_EMAX) अणु
		ieee754_setcx(IEEE754_OVERFLOW);
		ieee754_setcx(IEEE754_INEXACT);
		/* -O can be table indexed by (rm,sn) */
		चयन (ieee754_csr.rm) अणु
		हाल FPU_CSR_RN:
			वापस ieee754dp_inf(sn);
		हाल FPU_CSR_RZ:
			वापस ieee754dp_max(sn);
		हाल FPU_CSR_RU:	/* toward +Infinity */
			अगर (sn == 0)
				वापस ieee754dp_inf(0);
			अन्यथा
				वापस ieee754dp_max(1);
		हाल FPU_CSR_RD:	/* toward -Infinity */
			अगर (sn == 0)
				वापस ieee754dp_max(0);
			अन्यथा
				वापस ieee754dp_inf(1);
		पूर्ण
	पूर्ण
	/* gen norm/denorm/zero */

	अगर ((xm & DP_HIDDEN_BIT) == 0) अणु
		/* we underflow (tiny/zero) */
		निश्चित(xe == DP_EMIN);
		अगर (ieee754_csr.mx & IEEE754_UNDERFLOW)
			ieee754_setcx(IEEE754_UNDERFLOW);
		वापस builddp(sn, DP_EMIN - 1 + DP_EBIAS, xm);
	पूर्ण अन्यथा अणु
		निश्चित((xm >> (DP_FBITS + 1)) == 0);	/* no excess */
		निश्चित(xm & DP_HIDDEN_BIT);

		वापस builddp(sn, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
	पूर्ण
पूर्ण
