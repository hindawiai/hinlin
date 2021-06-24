<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Davidlohr Bueso <davidlohr.bueso@hp.com>
 *
 *  Based on the shअगरt-and-subtract algorithm क्रम computing पूर्णांकeger
 *  square root from Guy L. Steele.
 */

#समावेश <linux/export.h>
#समावेश <linux/bitops.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/गणित.स>

/**
 * पूर्णांक_वर्ग_मूल - computes the पूर्णांकeger square root
 * @x: पूर्णांकeger of which to calculate the वर्ग_मूल
 *
 * Computes: न्यूनमान(वर्ग_मूल(x))
 */
अचिन्हित दीर्घ पूर्णांक_वर्ग_मूल(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ b, m, y = 0;

	अगर (x <= 1)
		वापस x;

	m = 1UL << (__fls(x) & ~1UL);
	जबतक (m != 0) अणु
		b = y + m;
		y >>= 1;

		अगर (x >= b) अणु
			x -= b;
			y += m;
		पूर्ण
		m >>= 2;
	पूर्ण

	वापस y;
पूर्ण
EXPORT_SYMBOL(पूर्णांक_वर्ग_मूल);

#अगर BITS_PER_LONG < 64
/**
 * पूर्णांक_वर्ग_मूल64 - strongly typed पूर्णांक_वर्ग_मूल function when minimum 64 bit input
 * is expected.
 * @x: 64bit पूर्णांकeger of which to calculate the वर्ग_मूल
 */
u32 पूर्णांक_वर्ग_मूल64(u64 x)
अणु
	u64 b, m, y = 0;

	अगर (x <= अच_दीर्घ_उच्च)
		वापस पूर्णांक_वर्ग_मूल((अचिन्हित दीर्घ) x);

	m = 1ULL << ((fls64(x) - 1) & ~1ULL);
	जबतक (m != 0) अणु
		b = y + m;
		y >>= 1;

		अगर (x >= b) अणु
			x -= b;
			y += m;
		पूर्ण
		m >>= 2;
	पूर्ण

	वापस y;
पूर्ण
EXPORT_SYMBOL(पूर्णांक_वर्ग_मूल64);
#पूर्ण_अगर
