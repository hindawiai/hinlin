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

जोड़ ieee754sp ieee754sp_mul(जोड़ ieee754sp x, जोड़ ieee754sp y)
अणु
	पूर्णांक re;
	पूर्णांक rs;
	अचिन्हित पूर्णांक rm;
	अचिन्हित लघु lxm;
	अचिन्हित लघु hxm;
	अचिन्हित लघु lym;
	अचिन्हित लघु hym;
	अचिन्हित पूर्णांक lrm;
	अचिन्हित पूर्णांक hrm;
	अचिन्हित पूर्णांक t;
	अचिन्हित पूर्णांक at;

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
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_INF):
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754sp_indef();

	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_INF):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_INF, IEEE754_CLASS_INF):
		वापस ieee754sp_inf(xs ^ ys);

	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_NORM):
	हाल CLPAIR(IEEE754_CLASS_ZERO, IEEE754_CLASS_DNORM):
	हाल CLPAIR(IEEE754_CLASS_NORM, IEEE754_CLASS_ZERO):
	हाल CLPAIR(IEEE754_CLASS_DNORM, IEEE754_CLASS_ZERO):
		वापस ieee754sp_zero(xs ^ ys);


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
	/* rm = xm * ym, re = xe+ye basically */
	निश्चित(xm & SP_HIDDEN_BIT);
	निश्चित(ym & SP_HIDDEN_BIT);

	re = xe + ye;
	rs = xs ^ ys;

	/* shunt to top of word */
	xm <<= 32 - (SP_FBITS + 1);
	ym <<= 32 - (SP_FBITS + 1);

	/*
	 * Multiply 32 bits xm, ym to give high 32 bits rm with stickness.
	 */
	lxm = xm & 0xffff;
	hxm = xm >> 16;
	lym = ym & 0xffff;
	hym = ym >> 16;

	lrm = lxm * lym;	/* 16 * 16 => 32 */
	hrm = hxm * hym;	/* 16 * 16 => 32 */

	t = lxm * hym; /* 16 * 16 => 32 */
	at = lrm + (t << 16);
	hrm += at < lrm;
	lrm = at;
	hrm = hrm + (t >> 16);

	t = hxm * lym; /* 16 * 16 => 32 */
	at = lrm + (t << 16);
	hrm += at < lrm;
	lrm = at;
	hrm = hrm + (t >> 16);

	rm = hrm | (lrm != 0);

	/*
	 * Sticky shअगरt करोwn to normal rounding precision.
	 */
	अगर ((पूर्णांक) rm < 0) अणु
		rm = (rm >> (32 - (SP_FBITS + 1 + 3))) |
		    ((rm << (SP_FBITS + 1 + 3)) != 0);
		re++;
	पूर्ण अन्यथा अणु
		rm = (rm >> (32 - (SP_FBITS + 1 + 3 + 1))) |
		     ((rm << (SP_FBITS + 1 + 3 + 1)) != 0);
	पूर्ण
	निश्चित(rm & (SP_HIDDEN_BIT << 3));

	वापस ieee754sp_क्रमmat(rs, re, rm);
पूर्ण
