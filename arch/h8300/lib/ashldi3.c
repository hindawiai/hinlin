<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "libgcc.h"

DWtype
__ashldi3(DWtype u, word_type b)
अणु
	स्थिर DWजोड़ uu = अणु.ll = uपूर्ण;
	स्थिर word_type bm = (माप (Wtype) * BITS_PER_UNIT) - b;
	DWजोड़ w;

	अगर (b == 0)
		वापस u;

	अगर (bm <= 0) अणु
		w.s.low = 0;
		w.s.high = (UWtype) uu.s.low << -bm;
	पूर्ण अन्यथा अणु
		स्थिर UWtype carries = (UWtype) uu.s.low >> bm;

		w.s.low = (UWtype) uu.s.low << b;
		w.s.high = ((UWtype) uu.s.high << b) | carries;
	पूर्ण

	वापस w.ll;
पूर्ण
