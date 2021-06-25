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
#समावेश "ieee754dp.h"

अटल अंतरभूत जोड़ ieee754sp ieee754sp_nan_fdp(पूर्णांक xs, u64 xm)
अणु
	वापस buildsp(xs, SP_EMAX + 1 + SP_EBIAS,
		       xm >> (DP_FBITS - SP_FBITS));
पूर्ण

जोड़ ieee754sp ieee754sp_fdp(जोड़ ieee754dp x)
अणु
	जोड़ ieee754sp y;
	u32 rm;

	COMPXDP;
	COMPYSP;

	EXPLODEXDP;

	ieee754_clearcx();

	FLUSHXDP;

	चयन (xc) अणु
	हाल IEEE754_CLASS_Sन_अंक:
		x = ieee754dp_nanxcpt(x);
		EXPLODEXDP;
		fallthrough;
	हाल IEEE754_CLASS_Qन_अंक:
		y = ieee754sp_nan_fdp(xs, xm);
		अगर (!ieee754_csr.nan2008) अणु
			EXPLODEYSP;
			अगर (!ieee754_class_nan(yc))
				y = ieee754sp_indef();
		पूर्ण
		वापस y;

	हाल IEEE754_CLASS_INF:
		वापस ieee754sp_inf(xs);

	हाल IEEE754_CLASS_ZERO:
		वापस ieee754sp_zero(xs);

	हाल IEEE754_CLASS_DNORM:
		/* can't possibly be sp representable */
		ieee754_setcx(IEEE754_UNDERFLOW);
		ieee754_setcx(IEEE754_INEXACT);
		अगर ((ieee754_csr.rm == FPU_CSR_RU && !xs) ||
				(ieee754_csr.rm == FPU_CSR_RD && xs))
			वापस ieee754sp_mind(xs);
		वापस ieee754sp_zero(xs);

	हाल IEEE754_CLASS_NORM:
		अवरोध;
	पूर्ण

	/*
	 * Convert from DP_FBITS to SP_FBITS+3 with sticky right shअगरt.
	 */
	rm = (xm >> (DP_FBITS - (SP_FBITS + 3))) |
	     ((xm << (64 - (DP_FBITS - (SP_FBITS + 3)))) != 0);

	वापस ieee754sp_क्रमmat(xs, xe, rm);
पूर्ण
