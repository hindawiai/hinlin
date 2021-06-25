<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  reg_convert.c                                                            |
 |                                                                           |
 |  Convert रेजिस्टर representation.                                         |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1996,1997                                    |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#समावेश "exception.h"
#समावेश "fpu_emu.h"

पूर्णांक FPU_to_exp16(FPU_REG स्थिर *a, FPU_REG *x)
अणु
	पूर्णांक sign = माला_लोign(a);

	*(दीर्घ दीर्घ *)&(x->sigl) = *(स्थिर दीर्घ दीर्घ *)&(a->sigl);

	/* Set up the exponent as a 16 bit quantity. */
	setexponent16(x, exponent(a));

	अगर (exponent16(x) == EXP_UNDER) अणु
		/* The number is a de-normal or pseuकरोdenormal. */
		/* We only deal with the signअगरicand and exponent. */

		अगर (x->sigh & 0x80000000) अणु
			/* Is a pseuकरोdenormal. */
			/* This is non-80486 behaviour because the number
			   loses its 'denormal' identity. */
			addexponent(x, 1);
		पूर्ण अन्यथा अणु
			/* Is a denormal. */
			addexponent(x, 1);
			FPU_normalize_nuo(x);
		पूर्ण
	पूर्ण

	अगर (!(x->sigh & 0x80000000)) अणु
		EXCEPTION(EX_INTERNAL | 0x180);
	पूर्ण

	वापस sign;
पूर्ण
