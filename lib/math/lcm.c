<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/compiler.h>
#समावेश <linux/gcd.h>
#समावेश <linux/export.h>
#समावेश <linux/lcm.h>

/* Lowest common multiple */
अचिन्हित दीर्घ lcm(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अगर (a && b)
		वापस (a / gcd(a, b)) * b;
	अन्यथा
		वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lcm);

अचिन्हित दीर्घ lcm_not_zero(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अचिन्हित दीर्घ l = lcm(a, b);

	अगर (l)
		वापस l;

	वापस (b ? : a);
पूर्ण
EXPORT_SYMBOL_GPL(lcm_not_zero);
