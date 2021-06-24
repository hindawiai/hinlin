<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2003 Bernarकरो Innocenti <bernie@develer.com>
 *
 * Based on क्रमmer करो_भाग() implementation from यंत्र-parisc/भाग64.h:
 *	Copyright (C) 1999 Hewlett-Packard Co
 *	Copyright (C) 1999 David Mosberger-Tang <davidm@hpl.hp.com>
 *
 *
 * Generic C version of 64bit/32bit भागision and modulo, with
 * 64bit result and 32bit reमुख्यder.
 *
 * The fast हाल क्रम (n>>32 == 0) is handled अंतरभूत by करो_भाग().
 *
 * Code generated क्रम this function might be very inefficient
 * क्रम some CPUs. __भाग64_32() can be overridden by linking arch-specअगरic
 * assembly versions such as arch/ppc/lib/भाग64.S and arch/sh/lib/भाग64.S
 * or by defining a preprocessor macro in arch/include/यंत्र/भाग64.h.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <linux/गणित.स>
#समावेश <linux/math64.h>
#समावेश <linux/log2.h>

/* Not needed on 64bit architectures */
#अगर BITS_PER_LONG == 32

#अगर_अघोषित __भाग64_32
uपूर्णांक32_t __attribute__((weak)) __भाग64_32(uपूर्णांक64_t *n, uपूर्णांक32_t base)
अणु
	uपूर्णांक64_t rem = *n;
	uपूर्णांक64_t b = base;
	uपूर्णांक64_t res, d = 1;
	uपूर्णांक32_t high = rem >> 32;

	/* Reduce the thing a bit first */
	res = 0;
	अगर (high >= base) अणु
		high /= base;
		res = (uपूर्णांक64_t) high << 32;
		rem -= (uपूर्णांक64_t) (high*base) << 32;
	पूर्ण

	जबतक ((पूर्णांक64_t)b > 0 && b < rem) अणु
		b = b+b;
		d = d+d;
	पूर्ण

	करो अणु
		अगर (rem >= b) अणु
			rem -= b;
			res += d;
		पूर्ण
		b >>= 1;
		d >>= 1;
	पूर्ण जबतक (d);

	*n = res;
	वापस rem;
पूर्ण
EXPORT_SYMBOL(__भाग64_32);
#पूर्ण_अगर

/**
 * भाग_s64_rem - चिन्हित 64bit भागide with 64bit भागisor and reमुख्यder
 * @भागidend:	64bit भागidend
 * @भागisor:	64bit भागisor
 * @reमुख्यder:  64bit reमुख्यder
 */
#अगर_अघोषित भाग_s64_rem
s64 भाग_s64_rem(s64 भागidend, s32 भागisor, s32 *reमुख्यder)
अणु
	u64 quotient;

	अगर (भागidend < 0) अणु
		quotient = भाग_u64_rem(-भागidend, असल(भागisor), (u32 *)reमुख्यder);
		*reमुख्यder = -*reमुख्यder;
		अगर (भागisor > 0)
			quotient = -quotient;
	पूर्ण अन्यथा अणु
		quotient = भाग_u64_rem(भागidend, असल(भागisor), (u32 *)reमुख्यder);
		अगर (भागisor < 0)
			quotient = -quotient;
	पूर्ण
	वापस quotient;
पूर्ण
EXPORT_SYMBOL(भाग_s64_rem);
#पूर्ण_अगर

/**
 * भाग64_u64_rem - अचिन्हित 64bit भागide with 64bit भागisor and reमुख्यder
 * @भागidend:	64bit भागidend
 * @भागisor:	64bit भागisor
 * @reमुख्यder:  64bit reमुख्यder
 *
 * This implementation is a comparable to algorithm used by भाग64_u64.
 * But this operation, which includes math क्रम calculating the reमुख्यder,
 * is kept distinct to aव्योम slowing करोwn the भाग64_u64 operation on 32bit
 * प्रणालीs.
 */
#अगर_अघोषित भाग64_u64_rem
u64 भाग64_u64_rem(u64 भागidend, u64 भागisor, u64 *reमुख्यder)
अणु
	u32 high = भागisor >> 32;
	u64 quot;

	अगर (high == 0) अणु
		u32 rem32;
		quot = भाग_u64_rem(भागidend, भागisor, &rem32);
		*reमुख्यder = rem32;
	पूर्ण अन्यथा अणु
		पूर्णांक n = fls(high);
		quot = भाग_u64(भागidend >> n, भागisor >> n);

		अगर (quot != 0)
			quot--;

		*reमुख्यder = भागidend - quot * भागisor;
		अगर (*reमुख्यder >= भागisor) अणु
			quot++;
			*reमुख्यder -= भागisor;
		पूर्ण
	पूर्ण

	वापस quot;
पूर्ण
EXPORT_SYMBOL(भाग64_u64_rem);
#पूर्ण_अगर

/**
 * भाग64_u64 - अचिन्हित 64bit भागide with 64bit भागisor
 * @भागidend:	64bit भागidend
 * @भागisor:	64bit भागisor
 *
 * This implementation is a modअगरied version of the algorithm proposed
 * by the book 'Hacker's Delight'.  The original source and full proof
 * can be found here and is available क्रम use without restriction.
 *
 * 'http://www.hackersdelight.org/hdcodetxt/divDouble.c.txt'
 */
#अगर_अघोषित भाग64_u64
u64 भाग64_u64(u64 भागidend, u64 भागisor)
अणु
	u32 high = भागisor >> 32;
	u64 quot;

	अगर (high == 0) अणु
		quot = भाग_u64(भागidend, भागisor);
	पूर्ण अन्यथा अणु
		पूर्णांक n = fls(high);
		quot = भाग_u64(भागidend >> n, भागisor >> n);

		अगर (quot != 0)
			quot--;
		अगर ((भागidend - quot * भागisor) >= भागisor)
			quot++;
	पूर्ण

	वापस quot;
पूर्ण
EXPORT_SYMBOL(भाग64_u64);
#पूर्ण_अगर

/**
 * भाग64_s64 - चिन्हित 64bit भागide with 64bit भागisor
 * @भागidend:	64bit भागidend
 * @भागisor:	64bit भागisor
 */
#अगर_अघोषित भाग64_s64
s64 भाग64_s64(s64 भागidend, s64 भागisor)
अणु
	s64 quot, t;

	quot = भाग64_u64(असल(भागidend), असल(भागisor));
	t = (भागidend ^ भागisor) >> 63;

	वापस (quot ^ t) - t;
पूर्ण
EXPORT_SYMBOL(भाग64_s64);
#पूर्ण_अगर

#पूर्ण_अगर /* BITS_PER_LONG == 32 */

/*
 * Iterative भाग/mod क्रम use when भागidend is not expected to be much
 * bigger than भागisor.
 */
u32 iter_भाग_u64_rem(u64 भागidend, u32 भागisor, u64 *reमुख्यder)
अणु
	वापस __iter_भाग_u64_rem(भागidend, भागisor, reमुख्यder);
पूर्ण
EXPORT_SYMBOL(iter_भाग_u64_rem);

#अगर_अघोषित mul_u64_u64_भाग_u64
u64 mul_u64_u64_भाग_u64(u64 a, u64 b, u64 c)
अणु
	u64 res = 0, भाग, rem;
	पूर्णांक shअगरt;

	/* can a * b overflow ? */
	अगर (ilog2(a) + ilog2(b) > 62) अणु
		/*
		 * (b * a) / c is equal to
		 *
		 *      (b / c) * a +
		 *      (b % c) * a / c
		 *
		 * अगर nothing overflows. Can the 1st multiplication
		 * overflow? Yes, but we करो not care: this can only
		 * happen अगर the end result can't fit in u64 anyway.
		 *
		 * So the code below करोes
		 *
		 *      res = (b / c) * a;
		 *      b = b % c;
		 */
		भाग = भाग64_u64_rem(b, c, &rem);
		res = भाग * a;
		b = rem;

		shअगरt = ilog2(a) + ilog2(b) - 62;
		अगर (shअगरt > 0) अणु
			/* drop precision */
			b >>= shअगरt;
			c >>= shअगरt;
			अगर (!c)
				वापस res;
		पूर्ण
	पूर्ण

	वापस res + भाग64_u64(a * b, c);
पूर्ण
EXPORT_SYMBOL(mul_u64_u64_भाग_u64);
#पूर्ण_अगर
