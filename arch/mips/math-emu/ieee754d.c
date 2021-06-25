<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Some debug functions
 *
 * MIPS भग्नing poपूर्णांक support
 *
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 *
 *  Nov 7, 2000
 *  Modअगरied to build and operate in Linux kernel environment.
 *
 *  Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 *  Copyright (C) 2000 MIPS Technologies, Inc. All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश "ieee754.h"
#समावेश "ieee754sp.h"
#समावेश "ieee754dp.h"

जोड़ ieee754dp ieee754dp_dump(अक्षर *m, जोड़ ieee754dp x)
अणु
	पूर्णांक i;

	prपूर्णांकk("%s", m);
	prपूर्णांकk("<%08x,%08x>\n", (अचिन्हित) (x.bits >> 32),
	       (अचिन्हित) x.bits);
	prपूर्णांकk("\t=");
	चयन (ieee754dp_class(x)) अणु
	हाल IEEE754_CLASS_Qन_अंक:
	हाल IEEE754_CLASS_Sन_अंक:
		prपूर्णांकk("Nan %c", DPSIGN(x) ? '-' : '+');
		क्रम (i = DP_FBITS - 1; i >= 0; i--)
			prपूर्णांकk("%c", DPMANT(x) & DP_MBIT(i) ? '1' : '0');
		अवरोध;
	हाल IEEE754_CLASS_INF:
		prपूर्णांकk("%cInfinity", DPSIGN(x) ? '-' : '+');
		अवरोध;
	हाल IEEE754_CLASS_ZERO:
		prपूर्णांकk("%cZero", DPSIGN(x) ? '-' : '+');
		अवरोध;
	हाल IEEE754_CLASS_DNORM:
		prपूर्णांकk("%c0.", DPSIGN(x) ? '-' : '+');
		क्रम (i = DP_FBITS - 1; i >= 0; i--)
			prपूर्णांकk("%c", DPMANT(x) & DP_MBIT(i) ? '1' : '0');
		prपूर्णांकk("e%d", DPBEXP(x) - DP_EBIAS);
		अवरोध;
	हाल IEEE754_CLASS_NORM:
		prपूर्णांकk("%c1.", DPSIGN(x) ? '-' : '+');
		क्रम (i = DP_FBITS - 1; i >= 0; i--)
			prपूर्णांकk("%c", DPMANT(x) & DP_MBIT(i) ? '1' : '0');
		prपूर्णांकk("e%d", DPBEXP(x) - DP_EBIAS);
		अवरोध;
	शेष:
		prपूर्णांकk("Illegal/Unknown IEEE754 value class");
	पूर्ण
	prपूर्णांकk("\n");
	वापस x;
पूर्ण

जोड़ ieee754sp ieee754sp_dump(अक्षर *m, जोड़ ieee754sp x)
अणु
	पूर्णांक i;

	prपूर्णांकk("%s=", m);
	prपूर्णांकk("<%08x>\n", (अचिन्हित) x.bits);
	prपूर्णांकk("\t=");
	चयन (ieee754sp_class(x)) अणु
	हाल IEEE754_CLASS_Qन_अंक:
	हाल IEEE754_CLASS_Sन_अंक:
		prपूर्णांकk("Nan %c", SPSIGN(x) ? '-' : '+');
		क्रम (i = SP_FBITS - 1; i >= 0; i--)
			prपूर्णांकk("%c", SPMANT(x) & SP_MBIT(i) ? '1' : '0');
		अवरोध;
	हाल IEEE754_CLASS_INF:
		prपूर्णांकk("%cInfinity", SPSIGN(x) ? '-' : '+');
		अवरोध;
	हाल IEEE754_CLASS_ZERO:
		prपूर्णांकk("%cZero", SPSIGN(x) ? '-' : '+');
		अवरोध;
	हाल IEEE754_CLASS_DNORM:
		prपूर्णांकk("%c0.", SPSIGN(x) ? '-' : '+');
		क्रम (i = SP_FBITS - 1; i >= 0; i--)
			prपूर्णांकk("%c", SPMANT(x) & SP_MBIT(i) ? '1' : '0');
		prपूर्णांकk("e%d", SPBEXP(x) - SP_EBIAS);
		अवरोध;
	हाल IEEE754_CLASS_NORM:
		prपूर्णांकk("%c1.", SPSIGN(x) ? '-' : '+');
		क्रम (i = SP_FBITS - 1; i >= 0; i--)
			prपूर्णांकk("%c", SPMANT(x) & SP_MBIT(i) ? '1' : '0');
		prपूर्णांकk("e%d", SPBEXP(x) - SP_EBIAS);
		अवरोध;
	शेष:
		prपूर्णांकk("Illegal/Unknown IEEE754 value class");
	पूर्ण
	prपूर्णांकk("\n");
	वापस x;
पूर्ण
