<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IEEE754 भग्नing poपूर्णांक arithmetic
 * single precision: CLASS.f
 * FPR[fd] = class(FPR[fs])
 *
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 2015 Imagination Technologies, Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 */

#समावेश "ieee754sp.h"

पूर्णांक ieee754sp_2008class(जोड़ ieee754sp x)
अणु
	COMPXSP;

	EXPLODEXSP;

	/*
	 * 10 bit mask as follows:
	 *
	 * bit0 = Sन_अंक
	 * bit1 = Qन_अंक
	 * bit2 = -INF
	 * bit3 = -NORM
	 * bit4 = -DNORM
	 * bit5 = -ZERO
	 * bit6 = INF
	 * bit7 = NORM
	 * bit8 = DNORM
	 * bit9 = ZERO
	 */

	चयन(xc) अणु
	हाल IEEE754_CLASS_Sन_अंक:
		वापस 0x01;
	हाल IEEE754_CLASS_Qन_अंक:
		वापस 0x02;
	हाल IEEE754_CLASS_INF:
		वापस 0x04 << (xs ? 0 : 4);
	हाल IEEE754_CLASS_NORM:
		वापस 0x08 << (xs ? 0 : 4);
	हाल IEEE754_CLASS_DNORM:
		वापस 0x10 << (xs ? 0 : 4);
	हाल IEEE754_CLASS_ZERO:
		वापस 0x20 << (xs ? 0 : 4);
	शेष:
		pr_err("Unknown class: %d\n", xc);
		वापस 0;
	पूर्ण
पूर्ण
