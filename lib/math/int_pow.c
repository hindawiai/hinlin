<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * An पूर्णांकeger based घातer function
 *
 * Derived from drivers/video/backlight/pwm_bl.c
 */

#समावेश <linux/export.h>
#समावेश <linux/गणित.स>
#समावेश <linux/types.h>

/**
 * पूर्णांक_घात - computes the exponentiation of the given base and exponent
 * @base: base which will be उठाओd to the given घातer
 * @exp: घातer to be उठाओd to
 *
 * Computes: घात(base, exp), i.e. @base उठाओd to the @exp घातer
 */
u64 पूर्णांक_घात(u64 base, अचिन्हित पूर्णांक exp)
अणु
	u64 result = 1;

	जबतक (exp) अणु
		अगर (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	पूर्ण

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांक_घात);
