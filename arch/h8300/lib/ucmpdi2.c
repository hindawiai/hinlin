<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "libgcc.h"

word_type __ucmpdi2(DWtype a, DWtype b)
अणु
	स्थिर DWजोड़ au = अणु.ll = aपूर्ण;
	स्थिर DWजोड़ bu = अणु.ll = bपूर्ण;

	अगर ((UWtype) au.s.high < (UWtype) bu.s.high)
		वापस 0;
	अन्यथा अगर ((UWtype) au.s.high > (UWtype) bu.s.high)
		वापस 2;
	अगर ((UWtype) au.s.low < (UWtype) bu.s.low)
		वापस 0;
	अन्यथा अगर ((UWtype) au.s.low > (UWtype) bu.s.low)
		वापस 2;
	वापस 1;
पूर्ण
