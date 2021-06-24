<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>

#समावेश "libgcc.h"

/*
 * GCC 7 & older can suboptimally generate __multi3 calls क्रम mips64r6, so क्रम
 * that specअगरic हाल only we implement that पूर्णांकrinsic here.
 *
 * See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82981
 */
#अगर defined(CONFIG_64BIT) && defined(CONFIG_CPU_MIPSR6) && (__GNUC__ < 8)

/* multiply 64-bit values, low 64-bits वापसed */
अटल अंतरभूत दीर्घ दीर्घ notrace dmulu(दीर्घ दीर्घ a, दीर्घ दीर्घ b)
अणु
	दीर्घ दीर्घ res;

	यंत्र ("dmulu %0,%1,%2" : "=r" (res) : "r" (a), "r" (b));
	वापस res;
पूर्ण

/* multiply 64-bit अचिन्हित values, high 64-bits of 128-bit result वापसed */
अटल अंतरभूत दीर्घ दीर्घ notrace dmuhu(दीर्घ दीर्घ a, दीर्घ दीर्घ b)
अणु
	दीर्घ दीर्घ res;

	यंत्र ("dmuhu %0,%1,%2" : "=r" (res) : "r" (a), "r" (b));
	वापस res;
पूर्ण

/* multiply 128-bit values, low 128-bits वापसed */
ti_type notrace __multi3(ti_type a, ti_type b)
अणु
	TWजोड़ res, aa, bb;

	aa.ti = a;
	bb.ti = b;

	/*
	 * a * b =           (a.lo * b.lo)
	 *         + 2^64  * (a.hi * b.lo + a.lo * b.hi)
	 *        [+ 2^128 * (a.hi * b.hi)]
	 */
	res.s.low = dmulu(aa.s.low, bb.s.low);
	res.s.high = dmuhu(aa.s.low, bb.s.low);
	res.s.high += dmulu(aa.s.high, bb.s.low);
	res.s.high += dmulu(aa.s.low, bb.s.high);

	वापस res.ti;
पूर्ण
EXPORT_SYMBOL(__multi3);

#पूर्ण_अगर /* 64BIT && CPU_MIPSR6 && GCC7 */
