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

#घोषणा SP_EBIAS	127
#घोषणा SP_EMIN		(-126)
#घोषणा SP_EMAX		127
#घोषणा SP_FBITS	23
#घोषणा SP_MBITS	23

#घोषणा SP_MBIT(x)	((u32)1 << (x))
#घोषणा SP_HIDDEN_BIT	SP_MBIT(SP_FBITS)
#घोषणा SP_SIGN_BIT	SP_MBIT(31)

#घोषणा SPSIGN(sp)	(sp.sign)
#घोषणा SPBEXP(sp)	(sp.bexp)
#घोषणा SPMANT(sp)	(sp.mant)

अटल अंतरभूत पूर्णांक ieee754sp_finite(जोड़ ieee754sp x)
अणु
	वापस SPBEXP(x) != SP_EMAX + 1 + SP_EBIAS;
पूर्ण

/* 64 bit right shअगरt with rounding */
#घोषणा XSPSRS64(v, rs)						\
	(((rs) >= 64) ? ((v) != 0) : ((v) >> (rs)) | ((v) << (64-(rs)) != 0))

/* 3bit extended single precision sticky right shअगरt */
#घोषणा XSPSRS(v, rs)						\
	((rs > (SP_FBITS+3))?1:((v) >> (rs)) | ((v) << (32-(rs)) != 0))

#घोषणा XSPSRS1(m) \
	((m >> 1) | (m & 1))

#घोषणा SPXSRSX1() \
	(xe++, (xm = XSPSRS1(xm)))

#घोषणा SPXSRSY1() \
	(ye++, (ym = XSPSRS1(ym)))

/* convert denormal to normalized with extended exponent */
#घोषणा SPDNORMx(m,e) \
	जबतक ((m >> SP_FBITS) == 0) अणु m <<= 1; e--; पूर्ण
#घोषणा SPDNORMX	SPDNORMx(xm, xe)
#घोषणा SPDNORMY	SPDNORMx(ym, ye)
#घोषणा SPDNORMZ	SPDNORMx(zm, ze)

अटल अंतरभूत जोड़ ieee754sp buildsp(पूर्णांक s, पूर्णांक bx, अचिन्हित पूर्णांक m)
अणु
	जोड़ ieee754sp r;

	निश्चित((s) == 0 || (s) == 1);
	निश्चित((bx) >= SP_EMIN - 1 + SP_EBIAS
	       && (bx) <= SP_EMAX + 1 + SP_EBIAS);
	निश्चित(((m) >> SP_FBITS) == 0);

	r.sign = s;
	r.bexp = bx;
	r.mant = m;

	वापस r;
पूर्ण

बाह्य जोड़ ieee754sp __cold ieee754sp_nanxcpt(जोड़ ieee754sp);
बाह्य जोड़ ieee754sp ieee754sp_क्रमmat(पूर्णांक, पूर्णांक, अचिन्हित);
