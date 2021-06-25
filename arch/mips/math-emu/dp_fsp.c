<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: common utilities
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754sp.h"
#समावेश "ieee754dp.h"

अटल अंतरभूत जोड़ ieee754dp ieee754dp_nan_fsp(पूर्णांक xs, u64 xm)
अणु
	वापस builddp(xs, DP_EMAX + 1 + DP_EBIAS,
		       xm << (DP_FBITS - SP_FBITS));
पूर्ण

जोड़ ieee754dp ieee754dp_fsp(जोड़ ieee754sp x)
अणु
	COMPXSP;

	EXPLODEXSP;

	ieee754_clearcx();

	FLUSHXSP;

	चयन (xc) अणु
	हाल IEEE754_CLASS_Sन_अंक:
		वापस ieee754dp_nanxcpt(ieee754dp_nan_fsp(xs, xm));

	हाल IEEE754_CLASS_Qन_अंक:
		वापस ieee754dp_nan_fsp(xs, xm);

	हाल IEEE754_CLASS_INF:
		वापस ieee754dp_inf(xs);

	हाल IEEE754_CLASS_ZERO:
		वापस ieee754dp_zero(xs);

	हाल IEEE754_CLASS_DNORM:
		/* normalize */
		जबतक ((xm >> SP_FBITS) == 0) अणु
			xm <<= 1;
			xe--;
		पूर्ण
		अवरोध;

	हाल IEEE754_CLASS_NORM:
		अवरोध;
	पूर्ण

	/*
	 * Can't possibly overflow,underflow, or need rounding
	 */

	/* drop the hidden bit */
	xm &= ~SP_HIDDEN_BIT;

	वापस builddp(xs, xe + DP_EBIAS,
		       (u64) xm << (DP_FBITS - SP_FBITS));
पूर्ण
