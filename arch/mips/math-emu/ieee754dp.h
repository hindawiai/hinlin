<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IEEE754 भग्नing poपूर्णांक
 * द्विगुन precision पूर्णांकernal header file
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */

#समावेश <linux/compiler.h>

#समावेश "ieee754int.h"

#घोषणा निश्चित(expr) ((व्योम)0)

#घोषणा DP_EBIAS	1023
#घोषणा DP_EMIN		(-1022)
#घोषणा DP_EMAX		1023
#घोषणा DP_FBITS	52
#घोषणा DP_MBITS	52

#घोषणा DP_MBIT(x)	((u64)1 << (x))
#घोषणा DP_HIDDEN_BIT	DP_MBIT(DP_FBITS)
#घोषणा DP_SIGN_BIT	DP_MBIT(63)

#घोषणा DPSIGN(dp)	(dp.sign)
#घोषणा DPBEXP(dp)	(dp.bexp)
#घोषणा DPMANT(dp)	(dp.mant)

अटल अंतरभूत पूर्णांक ieee754dp_finite(जोड़ ieee754dp x)
अणु
	वापस DPBEXP(x) != DP_EMAX + 1 + DP_EBIAS;
पूर्ण

/* 3bit extended द्विगुन precision sticky right shअगरt */
#घोषणा XDPSRS(v,rs)	\
	((rs > (DP_FBITS+3))?1:((v) >> (rs)) | ((v) << (64-(rs)) != 0))

#घोषणा XDPSRSX1() \
	(xe++, (xm = (xm >> 1) | (xm & 1)))

#घोषणा XDPSRS1(v)	\
	(((v) >> 1) | ((v) & 1))

/* 32bit * 32bit => 64bit अचिन्हित पूर्णांकeger multiplication */
#घोषणा DPXMULT(x, y)	((u64)(x) * (u64)y)

/* convert denormal to normalized with extended exponent */
#घोषणा DPDNORMx(m,e) \
	जबतक ((m >> DP_FBITS) == 0) अणु m <<= 1; e--; पूर्ण
#घोषणा DPDNORMX	DPDNORMx(xm, xe)
#घोषणा DPDNORMY	DPDNORMx(ym, ye)
#घोषणा DPDNORMZ	DPDNORMx(zm, ze)

अटल अंतरभूत जोड़ ieee754dp builddp(पूर्णांक s, पूर्णांक bx, u64 m)
अणु
	जोड़ ieee754dp r;

	निश्चित((s) == 0 || (s) == 1);
	निश्चित((bx) >= DP_EMIN - 1 + DP_EBIAS
	       && (bx) <= DP_EMAX + 1 + DP_EBIAS);
	निश्चित(((m) >> DP_FBITS) == 0);

	r.sign = s;
	r.bexp = bx;
	r.mant = m;

	वापस r;
पूर्ण

बाह्य जोड़ ieee754dp __cold ieee754dp_nanxcpt(जोड़ ieee754dp);
बाह्य जोड़ ieee754dp ieee754dp_क्रमmat(पूर्णांक, पूर्णांक, u64);
