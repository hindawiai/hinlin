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

जोड़ ieee754dp ieee754dp_fदीर्घ(s64 x)
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
		अगर (x == (1ULL << 63))
			xm = (1ULL << 63);	/* max neg can't be safely negated */
		अन्यथा
			xm = -x;
	पूर्ण अन्यथा अणु
		xm = x;
	पूर्ण

	/* normalize */
	xe = DP_FBITS + 3;
	अगर (xm >> (DP_FBITS + 1 + 3)) अणु
		/* shunt out overflow bits */
		जबतक (xm >> (DP_FBITS + 1 + 3)) अणु
			XDPSRSX1();
		पूर्ण
	पूर्ण अन्यथा अणु
		/* normalize in grs extended द्विगुन precision */
		जबतक ((xm >> (DP_FBITS + 3)) == 0) अणु
			xm <<= 1;
			xe--;
		पूर्ण
	पूर्ण

	वापस ieee754dp_क्रमmat(xs, xe, xm);
पूर्ण
