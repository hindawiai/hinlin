<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rational fractions
 *
 * Copyright (C) 2009 emlix GmbH, Oskar Schirmer <oskar@scara.com>
 * Copyright (C) 2019 Trent Piepho <tpiepho@gmail.com>
 *
 * helper functions when coping with rational numbers
 */

#समावेश <linux/rational.h>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/minmax.h>

/*
 * calculate best rational approximation क्रम a given fraction
 * taking पूर्णांकo account restricted रेजिस्टर size, e.g. to find
 * appropriate values क्रम a pll with 5 bit denominator and
 * 8 bit numerator रेजिस्टर fields, trying to set up with a
 * frequency ratio of 3.1415, one would say:
 *
 * rational_best_approximation(31415, 10000,
 *		(1 << 8) - 1, (1 << 5) - 1, &n, &d);
 *
 * you may look at given_numerator as a fixed poपूर्णांक number,
 * with the fractional part size described in given_denominator.
 *
 * क्रम theoretical background, see:
 * https://en.wikipedia.org/wiki/Continued_fraction
 */

व्योम rational_best_approximation(
	अचिन्हित दीर्घ given_numerator, अचिन्हित दीर्घ given_denominator,
	अचिन्हित दीर्घ max_numerator, अचिन्हित दीर्घ max_denominator,
	अचिन्हित दीर्घ *best_numerator, अचिन्हित दीर्घ *best_denominator)
अणु
	/* n/d is the starting rational, which is continually
	 * decreased each iteration using the Euclidean algorithm.
	 *
	 * dp is the value of d from the prior iteration.
	 *
	 * n2/d2, n1/d1, and n0/d0 are our successively more accurate
	 * approximations of the rational.  They are, respectively,
	 * the current, previous, and two prior iterations of it.
	 *
	 * a is current term of the जारीd fraction.
	 */
	अचिन्हित दीर्घ n, d, n0, d0, n1, d1, n2, d2;
	n = given_numerator;
	d = given_denominator;
	n0 = d1 = 0;
	n1 = d0 = 1;

	क्रम (;;) अणु
		अचिन्हित दीर्घ dp, a;

		अगर (d == 0)
			अवरोध;
		/* Find next term in जारीd fraction, 'a', via
		 * Euclidean algorithm.
		 */
		dp = d;
		a = n / d;
		d = n % d;
		n = dp;

		/* Calculate the current rational approximation (aka
		 * convergent), n2/d2, using the term just found and
		 * the two prior approximations.
		 */
		n2 = n0 + a * n1;
		d2 = d0 + a * d1;

		/* If the current convergent exceeds the maxes, then
		 * वापस either the previous convergent or the
		 * largest semi-convergent, the final term of which is
		 * found below as 't'.
		 */
		अगर ((n2 > max_numerator) || (d2 > max_denominator)) अणु
			अचिन्हित दीर्घ t = min((max_numerator - n0) / n1,
					      (max_denominator - d0) / d1);

			/* This tests अगर the semi-convergent is बंदr
			 * than the previous convergent.
			 */
			अगर (2u * t > a || (2u * t == a && d0 * dp > d1 * d)) अणु
				n1 = n0 + t * n1;
				d1 = d0 + t * d1;
			पूर्ण
			अवरोध;
		पूर्ण
		n0 = n1;
		n1 = n2;
		d0 = d1;
		d1 = d2;
	पूर्ण
	*best_numerator = n1;
	*best_denominator = d1;
पूर्ण

EXPORT_SYMBOL(rational_best_approximation);
