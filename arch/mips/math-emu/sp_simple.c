<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IEEE754 भग्नing poपूर्णांक arithmetic
 * single precision
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश "ieee754sp.h"

जोड़ ieee754sp ieee754sp_neg(जोड़ ieee754sp x)
अणु
	जोड़ ieee754sp y;

	अगर (ieee754_csr.असल2008) अणु
		y = x;
		SPSIGN(y) = !SPSIGN(x);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक oldrm;

		oldrm = ieee754_csr.rm;
		ieee754_csr.rm = FPU_CSR_RD;
		y = ieee754sp_sub(ieee754sp_zero(0), x);
		ieee754_csr.rm = oldrm;
	पूर्ण
	वापस y;
पूर्ण

जोड़ ieee754sp ieee754sp_असल(जोड़ ieee754sp x)
अणु
	जोड़ ieee754sp y;

	अगर (ieee754_csr.असल2008) अणु
		y = x;
		SPSIGN(y) = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक oldrm;

		oldrm = ieee754_csr.rm;
		ieee754_csr.rm = FPU_CSR_RD;
		अगर (SPSIGN(x))
			y = ieee754sp_sub(ieee754sp_zero(0), x);
		अन्यथा
			y = ieee754sp_add(ieee754sp_zero(0), x);
		ieee754_csr.rm = oldrm;
	पूर्ण
	वापस y;
पूर्ण
