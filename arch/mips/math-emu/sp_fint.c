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

जोड़ ieee754sp ieee754sp_fपूर्णांक(पूर्णांक x)
अणु
	अचिन्हित पूर्णांक xm;
	पूर्णांक xe;
	पूर्णांक xs;

	ieee754_clearcx();

	अगर (x == 0)
		वापस ieee754sp_zero(0);
	अगर (x == 1 || x == -1)
		वापस ieee754sp_one(x < 0);
	अगर (x == 10 || x == -10)
		वापस ieee754sp_ten(x < 0);

	xs = (x < 0);
	अगर (xs) अणु
		अगर (x == (1 << 31))
			xm = ((अचिन्हित) 1 << 31);	/* max neg can't be safely negated */
		अन्यथा
			xm = -x;
	पूर्ण अन्यथा अणु
		xm = x;
	पूर्ण
	xe = SP_FBITS + 3;

	अगर (xm >> (SP_FBITS + 1 + 3)) अणु
		/* shunt out overflow bits
		 */
		जबतक (xm >> (SP_FBITS + 1 + 3)) अणु
			SPXSRSX1();
		पूर्ण
	पूर्ण अन्यथा अणु
		/* normalize in grs extended single precision
		 */
		जबतक ((xm >> (SP_FBITS + 3)) == 0) अणु
			xm <<= 1;
			xe--;
		पूर्ण
	पूर्ण
	वापस ieee754sp_क्रमmat(xs, xe, xm);
पूर्ण
