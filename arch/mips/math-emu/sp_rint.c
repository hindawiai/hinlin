<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * single precision
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 * Copyright (C) 2017 Imagination Technologies, Ltd.
 * Author: Aleksandar Markovic <aleksandar.markovic@imgtec.com>
 */

#समावेश "ieee754sp.h"

जोड़ ieee754sp ieee754sp_rपूर्णांक(जोड़ ieee754sp x)
अणु
	जोड़ ieee754sp ret;
	u32 residue;
	पूर्णांक sticky;
	पूर्णांक round;
	पूर्णांक odd;

	COMPXDP;		/* <-- DP needed क्रम 64-bit mantissa पंचांगp */

	ieee754_clearcx();

	EXPLODEXSP;
	FLUSHXSP;

	अगर (xc == IEEE754_CLASS_Sन_अंक)
		वापस ieee754sp_nanxcpt(x);

	अगर ((xc == IEEE754_CLASS_Qन_अंक) ||
	    (xc == IEEE754_CLASS_INF) ||
	    (xc == IEEE754_CLASS_ZERO))
		वापस x;

	अगर (xe >= SP_FBITS)
		वापस x;

	अगर (xe < -1) अणु
		residue = xm;
		round = 0;
		sticky = residue != 0;
		xm = 0;
	पूर्ण अन्यथा अणु
		residue = xm << (xe + 1);
		residue <<= 31 - SP_FBITS;
		round = (residue >> 31) != 0;
		sticky = (residue << 1) != 0;
		xm >>= SP_FBITS - xe;
	पूर्ण

	odd = (xm & 0x1) != 0x0;

	चयन (ieee754_csr.rm) अणु
	हाल FPU_CSR_RN:	/* toward nearest */
		अगर (round && (sticky || odd))
			xm++;
		अवरोध;
	हाल FPU_CSR_RZ:	/* toward zero */
		अवरोध;
	हाल FPU_CSR_RU:	/* toward +infinity */
		अगर ((round || sticky) && !xs)
			xm++;
		अवरोध;
	हाल FPU_CSR_RD:	/* toward -infinity */
		अगर ((round || sticky) && xs)
			xm++;
		अवरोध;
	पूर्ण

	अगर (round || sticky)
		ieee754_setcx(IEEE754_INEXACT);

	ret = ieee754sp_fदीर्घ(xm);
	SPSIGN(ret) = xs;

	वापस ret;
पूर्ण
