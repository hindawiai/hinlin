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

पूर्णांक ieee754sp_tपूर्णांक(जोड़ ieee754sp x)
अणु
	u32 residue;
	पूर्णांक round;
	पूर्णांक sticky;
	पूर्णांक odd;

	COMPXSP;

	ieee754_clearcx();

	EXPLODEXSP;
	FLUSHXSP;

	चयन (xc) अणु
	हाल IEEE754_CLASS_Sन_अंक:
	हाल IEEE754_CLASS_Qन_अंक:
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754si_indef();

	हाल IEEE754_CLASS_INF:
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754si_overflow(xs);

	हाल IEEE754_CLASS_ZERO:
		वापस 0;

	हाल IEEE754_CLASS_DNORM:
	हाल IEEE754_CLASS_NORM:
		अवरोध;
	पूर्ण
	अगर (xe >= 31) अणु
		/* look क्रम valid corner हाल */
		अगर (xe == 31 && xs && xm == SP_HIDDEN_BIT)
			वापस -0x80000000;
		/* Set invalid. We will only use overflow क्रम भग्नing
		   poपूर्णांक overflow */
		ieee754_setcx(IEEE754_INVALID_OPERATION);
		वापस ieee754si_overflow(xs);
	पूर्ण
	/* oh gawd */
	अगर (xe > SP_FBITS) अणु
		xm <<= xe - SP_FBITS;
	पूर्ण अन्यथा अणु
		अगर (xe < -1) अणु
			residue = xm;
			round = 0;
			sticky = residue != 0;
			xm = 0;
		पूर्ण अन्यथा अणु
			/* Shअगरting a u32 32 बार करोes not work,
			* so we करो it in two steps. Be aware that xe
			* may be -1 */
			residue = xm << (xe + 1);
			residue <<= 31 - SP_FBITS;
			round = (residue >> 31) != 0;
			sticky = (residue << 1) != 0;
			xm >>= SP_FBITS - xe;
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
		अगर ((xm >> 31) != 0) अणु
			/* This can happen after rounding */
			ieee754_setcx(IEEE754_INVALID_OPERATION);
			वापस ieee754si_overflow(xs);
		पूर्ण
		अगर (round || sticky)
			ieee754_setcx(IEEE754_INEXACT);
	पूर्ण
	अगर (xs)
		वापस -xm;
	अन्यथा
		वापस xm;
पूर्ण
