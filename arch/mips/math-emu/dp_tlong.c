<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: common utilities
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754dp.h"

s64 ieee754dp_tदीर्घ(जोड़ ieee754dp x)
अणु
	u64 residue;
	पूर्णांक round;
	पूर्णांक sticky;
	पूर्णांक odd;

	COMPXDP;

	ieee754_clearcx();

	EXPLODEXDP;
	FLUSHXDP;

	चयन (xc) अणु
	हाल IEEE754_CLASS_Sन_अंक:
	हाल IEEE754_CLASS_Qन_अंक:
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754di_indef();

	हाल IEEE754_CLASS_INF:
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754di_overflow(xs);

	हाल IEEE754_CLASS_ZERO:
		वापस 0;

	हाल IEEE754_CLASS_DNORM:
	हाल IEEE754_CLASS_NORM:
		अवरोध;
	पूर्ण
	अगर (xe >= 63) अणु
		/* look क्रम valid corner हाल */
		अगर (xe == 63 && xs && xm == DP_HIDDEN_BIT)
			वापस -0x8000000000000000LL;
		/* Set invalid. We will only use overflow क्रम भग्नing
		   poपूर्णांक overflow */
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754di_overflow(xs);
	पूर्ण
	/* oh gawd */
	अगर (xe > DP_FBITS) अणु
		xm <<= xe - DP_FBITS;
	पूर्ण अन्यथा अगर (xe < DP_FBITS) अणु
		अगर (xe < -1) अणु
			residue = xm;
			round = 0;
			sticky = residue != 0;
			xm = 0;
		पूर्ण अन्यथा अणु
			/* Shअगरting a u64 64 बार करोes not work,
			* so we करो it in two steps. Be aware that xe
			* may be -1 */
			residue = xm << (xe + 1);
			residue <<= 63 - DP_FBITS;
			round = (residue >> 63) != 0;
			sticky = (residue << 1) != 0;
			xm >>= DP_FBITS - xe;
		पूर्ण
		odd = (xm & 0x1) != 0x0;
		चयन (ieee754_csr.rm) अणु
		हाल FPU_CSR_RN:
			अगर (round && (sticky || odd))
				xm++;
			अवरोध;
		हाल FPU_CSR_RZ:
			अवरोध;
		हाल FPU_CSR_RU:	/* toward +Infinity */
			अगर ((round || sticky) && !xs)
				xm++;
			अवरोध;
		हाल FPU_CSR_RD:	/* toward -Infinity */
			अगर ((round || sticky) && xs)
				xm++;
			अवरोध;
		पूर्ण
		अगर ((xm >> 63) != 0) अणु
			/* This can happen after rounding */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			वापस ieee754di_overflow(xs);
		पूर्ण
		अगर (round || sticky)
			ieee754_setcx(IEEE754_INEXACT);
	पूर्ण
	अगर (xs)
		वापस -xm;
	अन्यथा
		वापस xm;
पूर्ण
