<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * single precision
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश <linux/compiler.h>

#समावेश "ieee754sp.h"

पूर्णांक ieee754sp_class(जोड़ ieee754sp x)
अणु
	COMPXSP;
	EXPLODEXSP;
	वापस xc;
पूर्ण

अटल अंतरभूत पूर्णांक ieee754sp_isnan(जोड़ ieee754sp x)
अणु
	वापस ieee754_class_nan(ieee754sp_class(x));
पूर्ण

अटल अंतरभूत पूर्णांक ieee754sp_issnan(जोड़ ieee754sp x)
अणु
	पूर्णांक qbit;

	निश्चित(ieee754sp_isnan(x));
	qbit = (SPMANT(x) & SP_MBIT(SP_FBITS - 1)) == SP_MBIT(SP_FBITS - 1);
	वापस ieee754_csr.nan2008 ^ qbit;
पूर्ण


/*
 * Raise the Invalid Operation IEEE 754 exception
 * and convert the संकेतing NaN supplied to a quiet NaN.
 */
जोड़ ieee754sp __cold ieee754sp_nanxcpt(जोड़ ieee754sp r)
अणु
	निश्चित(ieee754sp_issnan(r));

	ieee754_setcx(IEEE754_INVALID_OPERATION);
	अगर (ieee754_csr.nan2008) अणु
		SPMANT(r) |= SP_MBIT(SP_FBITS - 1);
	पूर्ण अन्यथा अणु
		SPMANT(r) &= ~SP_MBIT(SP_FBITS - 1);
		अगर (!ieee754sp_isnan(r))
			SPMANT(r) |= SP_MBIT(SP_FBITS - 2);
	पूर्ण

	वापस r;
पूर्ण

अटल अचिन्हित पूर्णांक ieee754sp_get_rounding(पूर्णांक sn, अचिन्हित पूर्णांक xm)
अणु
	/* inexact must round of 3 bits
	 */
	अगर (xm & (SP_MBIT(3) - 1)) अणु
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
जोड़ ieee754sp ieee754sp_क्रमmat(पूर्णांक sn, पूर्णांक xe, अचिन्हित पूर्णांक xm)
अणु
	निश्चित(xm);		/* we करोn't gen exact zeros (probably should) */

	निश्चित((xm >> (SP_FBITS + 1 + 3)) == 0);	/* no excess */
	निश्चित(xm & (SP_HIDDEN_BIT << 3));

	अगर (xe < SP_EMIN) अणु
		/* strip lower bits */
		पूर्णांक es = SP_EMIN - xe;

		अगर (ieee754_csr.nod) अणु
			ieee754_setcx(IEEE754_UNDERFLOW);
			ieee754_setcx(IEEE754_INEXACT);

			चयन(ieee754_csr.rm) अणु
			हाल FPU_CSR_RN:
			हाल FPU_CSR_RZ:
				वापस ieee754sp_zero(sn);
			हाल FPU_CSR_RU:      /* toward +Infinity */
				अगर (sn == 0)
					वापस ieee754sp_min(0);
				अन्यथा
					वापस ieee754sp_zero(1);
			हाल FPU_CSR_RD:      /* toward -Infinity */
				अगर (sn == 0)
					वापस ieee754sp_zero(0);
				अन्यथा
					वापस ieee754sp_min(1);
			पूर्ण
		पूर्ण

		अगर (xe == SP_EMIN - 1 &&
		    ieee754sp_get_rounding(sn, xm) >> (SP_FBITS + 1 + 3))
		अणु
			/* Not tiny after rounding */
			ieee754_setcx(IEEE754_INEXACT);
			xm = ieee754sp_get_rounding(sn, xm);
			xm >>= 1;
			/* Clear grs bits */
			xm &= ~(SP_MBIT(3) - 1);
			xe++;
		पूर्ण अन्यथा अणु
			/* sticky right shअगरt es bits
			 */
			xm = XSPSRS(xm, es);
			xe += es;
			निश्चित((xm & (SP_HIDDEN_BIT << 3)) == 0);
			निश्चित(xe == SP_EMIN);
		पूर्ण
	पूर्ण
	अगर (xm & (SP_MBIT(3) - 1)) अणु
		ieee754_setcx(IEEE754_INEXACT);
		अगर ((xm & (SP_HIDDEN_BIT << 3)) == 0) अणु
			ieee754_setcx(IEEE754_UNDERFLOW);
		पूर्ण

		/* inexact must round of 3 bits
		 */
		xm = ieee754sp_get_rounding(sn, xm);
		/* adjust exponent क्रम rounding add overflowing
		 */
		अगर (xm >> (SP_FBITS + 1 + 3)) अणु
			/* add causes mantissa overflow */
			xm >>= 1;
			xe++;
		पूर्ण
	पूर्ण
	/* strip grs bits */
	xm >>= 3;

	निश्चित((xm >> (SP_FBITS + 1)) == 0);	/* no excess */
	निश्चित(xe >= SP_EMIN);

	अगर (xe > SP_EMAX) अणु
		ieee754_setcx(IEEE754_OVERFLOW);
		ieee754_setcx(IEEE754_INEXACT);
		/* -O can be table indexed by (rm,sn) */
		चयन (ieee754_csr.rm) अणु
		हाल FPU_CSR_RN:
			वापस ieee754sp_inf(sn);
		हाल FPU_CSR_RZ:
			वापस ieee754sp_max(sn);
		हाल FPU_CSR_RU:	/* toward +Infinity */
			अगर (sn == 0)
				वापस ieee754sp_inf(0);
			अन्यथा
				वापस ieee754sp_max(1);
		हाल FPU_CSR_RD:	/* toward -Infinity */
			अगर (sn == 0)
				वापस ieee754sp_max(0);
			अन्यथा
				वापस ieee754sp_inf(1);
		पूर्ण
	पूर्ण
	/* gen norm/denorm/zero */

	अगर ((xm & SP_HIDDEN_BIT) == 0) अणु
		/* we underflow (tiny/zero) */
		निश्चित(xe == SP_EMIN);
		अगर (ieee754_csr.mx & IEEE754_UNDERFLOW)
			ieee754_setcx(IEEE754_UNDERFLOW);
		वापस buildsp(sn, SP_EMIN - 1 + SP_EBIAS, xm);
	पूर्ण अन्यथा अणु
		निश्चित((xm >> (SP_FBITS + 1)) == 0);	/* no excess */
		निश्चित(xm & SP_HIDDEN_BIT);

		वापस buildsp(sn, xe + SP_EBIAS, xm & ~SP_HIDDEN_BIT);
	पूर्ण
पूर्ण
