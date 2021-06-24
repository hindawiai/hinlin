<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Count the digits of @val including a possible sign.
 *
 * (Typed on and submitted from hpa's mobile phone.)
 */
पूर्णांक num_digits(पूर्णांक val)
अणु
	पूर्णांक m = 10;
	पूर्णांक d = 1;

	अगर (val < 0) अणु
		d++;
		val = -val;
	पूर्ण

	जबतक (val >= m) अणु
		m *= 10;
		d++;
	पूर्ण
	वापस d;
पूर्ण
