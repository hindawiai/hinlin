<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * द्विगुन precision: common utilities
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754dp.h"

जोड़ ieee754dp ieee754dp_neg(जोड़ ieee754dp x)
अणु
	जोड़ ieee754dp y;

	अगर (ieee754_csr.असल2008) अणु
		y = x;
		DPSIGN(y) = !DPSIGN(x);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक oldrm;

		oldrm = ieee754_csr.rm;
		ieee754_csr.rm = FPU_CSR_RD;
		y = ieee754dp_sub(ieee754dp_zero(0), x);
		ieee754_csr.rm = oldrm;
	पूर्ण
	वापस y;
पूर्ण

जोड़ ieee754dp ieee754dp_असल(जोड़ ieee754dp x)
अणु
	जोड़ ieee754dp y;

	अगर (ieee754_csr.असल2008) अणु
		y = x;
		DPSIGN(y) = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक oldrm;

		oldrm = ieee754_csr.rm;
		ieee754_csr.rm = FPU_CSR_RD;
		अगर (DPSIGN(x))
			y = ieee754dp_sub(ieee754dp_zero(0), x);
		अन्यथा
			y = ieee754dp_add(ieee754dp_zero(0), x);
		ieee754_csr.rm = oldrm;
	पूर्ण
	वापस y;
पूर्ण
