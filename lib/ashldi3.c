<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/export.h>

#समावेश <linux/libgcc.h>

दीर्घ दीर्घ notrace __ashldi3(दीर्घ दीर्घ u, word_type b)
अणु
	DWजोड़ uu, w;
	word_type bm;

	अगर (b == 0)
		वापस u;

	uu.ll = u;
	bm = 32 - b;

	अगर (bm <= 0) अणु
		w.s.low = 0;
		w.s.high = (अचिन्हित पूर्णांक) uu.s.low << -bm;
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित पूर्णांक carries = (अचिन्हित पूर्णांक) uu.s.low >> bm;

		w.s.low = (अचिन्हित पूर्णांक) uu.s.low << b;
		w.s.high = ((अचिन्हित पूर्णांक) uu.s.high << b) | carries;
	पूर्ण

	वापस w.ll;
पूर्ण
EXPORT_SYMBOL(__ashldi3);
