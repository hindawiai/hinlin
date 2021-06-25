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

जोड़ ieee754dp ieee754dp_fपूर्णांक(पूर्णांक x)
अणु
	u64 xm;
	पूर्णांक xe;
	पूर्णांक xs;

	ieee754_clearcx();

	अगर (x == 0)
		वापस ieee754dp_zero(0);
	अगर (x == 1 || x == -1)
		वापस ieee754dp_one(x < 0);
	अगर (x == 10 || x == -10)
		वापस ieee754dp_ten(x < 0);

	xs = (x < 0);
	अगर (xs) अणु
		अगर (x == (1 << 31))
			xm = ((अचिन्हित) 1 << 31);	/* max neg can't be safely negated */
		अन्यथा
			xm = -x;
	पूर्ण अन्यथा अणु
		xm = x;
	पूर्ण

	/* normalize - result can never be inexact or overflow */
	xe = DP_FBITS;
	जबतक ((xm >> DP_FBITS) == 0) अणु
		xm <<= 1;
		xe--;
	पूर्ण
	वापस builddp(xs, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
पूर्ण
