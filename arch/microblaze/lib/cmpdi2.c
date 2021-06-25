<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>

#समावेश "libgcc.h"

word_type __cmpdi2(दीर्घ दीर्घ a, दीर्घ दीर्घ b)
अणु
	स्थिर DWजोड़ au = अणु
		.ll = a
	पूर्ण;
	स्थिर DWजोड़ bu = अणु
		.ll = b
	पूर्ण;

	अगर (au.s.high < bu.s.high)
		वापस 0;
	अन्यथा अगर (au.s.high > bu.s.high)
		वापस 2;

	अगर ((अचिन्हित पूर्णांक) au.s.low < (अचिन्हित पूर्णांक) bu.s.low)
		वापस 0;
	अन्यथा अगर ((अचिन्हित पूर्णांक) au.s.low > (अचिन्हित पूर्णांक) bu.s.low)
		वापस 2;

	वापस 1;
पूर्ण
EXPORT_SYMBOL(__cmpdi2);
