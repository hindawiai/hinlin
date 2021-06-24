<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/gcd.h>
#समावेश <linux/export.h>

/*
 * This implements the binary GCD algorithm. (Often attributed to Stein,
 * but as Knuth has noted, appears in a first-century Chinese math text.)
 *
 * This is faster than the भागision-based algorithm even on x86, which
 * has decent hardware भागision.
 */

#अगर !defined(CONFIG_CPU_NO_EFFICIENT_FFS)

/* If __ffs is available, the even/odd algorithm benchmarks slower. */

/**
 * gcd - calculate and वापस the greatest common भागisor of 2 अचिन्हित दीर्घs
 * @a: first value
 * @b: second value
 */
अचिन्हित दीर्घ gcd(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अचिन्हित दीर्घ r = a | b;

	अगर (!a || !b)
		वापस r;

	b >>= __ffs(b);
	अगर (b == 1)
		वापस r & -r;

	क्रम (;;) अणु
		a >>= __ffs(a);
		अगर (a == 1)
			वापस r & -r;
		अगर (a == b)
			वापस a << __ffs(r);

		अगर (a < b)
			swap(a, b);
		a -= b;
	पूर्ण
पूर्ण

#अन्यथा

/* If normalization is करोne by loops, the even/odd algorithm is a win. */
अचिन्हित दीर्घ gcd(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अचिन्हित दीर्घ r = a | b;

	अगर (!a || !b)
		वापस r;

	/* Isolate lsbit of r */
	r &= -r;

	जबतक (!(b & r))
		b >>= 1;
	अगर (b == r)
		वापस r;

	क्रम (;;) अणु
		जबतक (!(a & r))
			a >>= 1;
		अगर (a == r)
			वापस r;
		अगर (a == b)
			वापस a;

		अगर (a < b)
			swap(a, b);
		a -= b;
		a >>= 1;
		अगर (a & r)
			a += b;
		a >>= 1;
	पूर्ण
पूर्ण

#पूर्ण_अगर

EXPORT_SYMBOL_GPL(gcd);
