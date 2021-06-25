<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: common utilities
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 * Copyright (C) 2017 Imagination Technologies, Ltd.
 * Author: Aleksandar Markovic <aleksandar.markovic@imgtec.com>
 */

#समावेश "ieee754dp.h"

जोड़ ieee754dp ieee754dp_rपूर्णांक(जोड़ ieee754dp x)
अणु
	जोड़ ieee754dp ret;
	u64 residue;
	पूर्णांक sticky;
	पूर्णांक round;
	पूर्णांक odd;

	COMPXDP;

	ieee754_clearcx();

	EXPLODEXDP;
	FLUSHXDP;

	अगर (xc == IEEE754_CLASS_Sन_अंक)
		वापस ieee754dp_nanxcpt(x);

	अगर ((xc == IEEE754_CLASS_Qन_अंक) ||
	    (xc == IEEE754_CLASS_INF) ||
	    (xc == IEEE754_CLASS_ZERO))
		वापस x;

	अगर (xe >= DP_FBITS)
		वापस x;

	अगर (xe < -1) अणु
		residue = xm;
		round = 0;
		sticky = residue != 0;
		xm = 0;
	पूर्ण अन्यथा अणु
		residue = xm << (64 - DP_FBITS + xe);
		round = (residue >> 63) != 0;
		sticky = (residue << 1) != 0;
		xm >>= DP_FBITS - xe;
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

	ret = ieee754dp_fदीर्घ(xm);
	DPSIGN(ret) = xs;

	वापस ret;
पूर्ण
