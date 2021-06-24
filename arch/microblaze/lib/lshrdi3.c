<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>

#समावेश "libgcc.h"

दीर्घ दीर्घ __lshrdi3(दीर्घ दीर्घ u, word_type b)
अणु
	DWजोड़ uu, w;
	word_type bm;

	अगर (b == 0)
		वापस u;

	uu.ll = u;
	bm = 32 - b;

	अगर (bm <= 0) अणु
		w.s.high = 0;
		w.s.low = (अचिन्हित पूर्णांक) uu.s.high >> -bm;
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित पूर्णांक carries = (अचिन्हित पूर्णांक) uu.s.high << bm;

		w.s.high = (अचिन्हित पूर्णांक) uu.s.high >> b;
		w.s.low = ((अचिन्हित पूर्णांक) uu.s.low >> b) | carries;
	पूर्ण

	वापस w.ll;
पूर्ण
EXPORT_SYMBOL(__lshrdi3);
