<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IEEE754 भग्नing poपूर्णांक
 * common पूर्णांकernal header file
 */
/*
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 */
#अगर_अघोषित __IEEE754INT_H
#घोषणा __IEEE754INT_H

#समावेश "ieee754.h"

#घोषणा CLPAIR(x, y)	((x)*6+(y))

क्रमागत maddf_flags अणु
	MADDF_NEGATE_PRODUCT	= 1 << 0,
	MADDF_NEGATE_ADDITION	= 1 << 1,
पूर्ण;

अटल अंतरभूत व्योम ieee754_clearcx(व्योम)
अणु
	ieee754_csr.cx = 0;
पूर्ण

अटल अंतरभूत व्योम ieee754_setcx(स्थिर अचिन्हित पूर्णांक flags)
अणु
	ieee754_csr.cx |= flags;
	ieee754_csr.sx |= flags;
पूर्ण

अटल अंतरभूत पूर्णांक ieee754_setandtestcx(स्थिर अचिन्हित पूर्णांक x)
अणु
	ieee754_setcx(x);

	वापस ieee754_csr.mx & x;
पूर्ण

अटल अंतरभूत पूर्णांक ieee754_class_nan(पूर्णांक xc)
अणु
	वापस xc >= IEEE754_CLASS_Sन_अंक;
पूर्ण

#घोषणा COMPXSP \
	अचिन्हित पूर्णांक xm; पूर्णांक xe; पूर्णांक xs __maybe_unused; पूर्णांक xc

#घोषणा COMPYSP \
	अचिन्हित पूर्णांक ym; पूर्णांक ye; पूर्णांक ys; पूर्णांक yc

#घोषणा COMPZSP \
	अचिन्हित पूर्णांक zm; पूर्णांक ze; पूर्णांक zs; पूर्णांक zc

#घोषणा EXPLODESP(v, vc, vs, ve, vm)					\
अणु									\
	vs = SPSIGN(v);							\
	ve = SPBEXP(v);							\
	vm = SPMANT(v);							\
	अगर (ve == SP_EMAX+1+SP_EBIAS) अणु					\
		अगर (vm == 0)						\
			vc = IEEE754_CLASS_INF;				\
		अन्यथा अगर (ieee754_csr.nan2008 ^ !(vm & SP_MBIT(SP_FBITS - 1))) \
			vc = IEEE754_CLASS_Qन_अंक;			\
		अन्यथा							\
			vc = IEEE754_CLASS_Sन_अंक;			\
	पूर्ण अन्यथा अगर (ve == SP_EMIN-1+SP_EBIAS) अणु				\
		अगर (vm) अणु						\
			ve = SP_EMIN;					\
			vc = IEEE754_CLASS_DNORM;			\
		पूर्ण अन्यथा							\
			vc = IEEE754_CLASS_ZERO;			\
	पूर्ण अन्यथा अणु							\
		ve -= SP_EBIAS;						\
		vm |= SP_HIDDEN_BIT;					\
		vc = IEEE754_CLASS_NORM;				\
	पूर्ण								\
पूर्ण
#घोषणा EXPLODEXSP EXPLODESP(x, xc, xs, xe, xm)
#घोषणा EXPLODEYSP EXPLODESP(y, yc, ys, ye, ym)
#घोषणा EXPLODEZSP EXPLODESP(z, zc, zs, ze, zm)


#घोषणा COMPXDP \
	u64 xm; पूर्णांक xe; पूर्णांक xs __maybe_unused; पूर्णांक xc

#घोषणा COMPYDP \
	u64 ym; पूर्णांक ye; पूर्णांक ys; पूर्णांक yc

#घोषणा COMPZDP \
	u64 zm; पूर्णांक ze; पूर्णांक zs; पूर्णांक zc

#घोषणा EXPLODEDP(v, vc, vs, ve, vm)					\
अणु									\
	vm = DPMANT(v);							\
	vs = DPSIGN(v);							\
	ve = DPBEXP(v);							\
	अगर (ve == DP_EMAX+1+DP_EBIAS) अणु					\
		अगर (vm == 0)						\
			vc = IEEE754_CLASS_INF;				\
		अन्यथा अगर (ieee754_csr.nan2008 ^ !(vm & DP_MBIT(DP_FBITS - 1))) \
			vc = IEEE754_CLASS_Qन_अंक;			\
		अन्यथा							\
			vc = IEEE754_CLASS_Sन_अंक;			\
	पूर्ण अन्यथा अगर (ve == DP_EMIN-1+DP_EBIAS) अणु				\
		अगर (vm) अणु						\
			ve = DP_EMIN;					\
			vc = IEEE754_CLASS_DNORM;			\
		पूर्ण अन्यथा							\
			vc = IEEE754_CLASS_ZERO;			\
	पूर्ण अन्यथा अणु							\
		ve -= DP_EBIAS;						\
		vm |= DP_HIDDEN_BIT;					\
		vc = IEEE754_CLASS_NORM;				\
	पूर्ण								\
पूर्ण
#घोषणा EXPLODEXDP EXPLODEDP(x, xc, xs, xe, xm)
#घोषणा EXPLODEYDP EXPLODEDP(y, yc, ys, ye, ym)
#घोषणा EXPLODEZDP EXPLODEDP(z, zc, zs, ze, zm)

#घोषणा FLUSHDP(v, vc, vs, ve, vm)					\
	अगर (vc==IEEE754_CLASS_DNORM) अणु					\
		अगर (ieee754_csr.nod) अणु					\
			ieee754_setcx(IEEE754_INEXACT);			\
			vc = IEEE754_CLASS_ZERO;			\
			ve = DP_EMIN-1+DP_EBIAS;			\
			vm = 0;						\
			v = ieee754dp_zero(vs);				\
		पूर्ण							\
	पूर्ण

#घोषणा FLUSHSP(v, vc, vs, ve, vm)					\
	अगर (vc==IEEE754_CLASS_DNORM) अणु					\
		अगर (ieee754_csr.nod) अणु					\
			ieee754_setcx(IEEE754_INEXACT);			\
			vc = IEEE754_CLASS_ZERO;			\
			ve = SP_EMIN-1+SP_EBIAS;			\
			vm = 0;						\
			v = ieee754sp_zero(vs);				\
		पूर्ण							\
	पूर्ण

#घोषणा FLUSHXDP FLUSHDP(x, xc, xs, xe, xm)
#घोषणा FLUSHYDP FLUSHDP(y, yc, ys, ye, ym)
#घोषणा FLUSHZDP FLUSHDP(z, zc, zs, ze, zm)
#घोषणा FLUSHXSP FLUSHSP(x, xc, xs, xe, xm)
#घोषणा FLUSHYSP FLUSHSP(y, yc, ys, ye, ym)
#घोषणा FLUSHZSP FLUSHSP(z, zc, zs, ze, zm)

#पूर्ण_अगर /* __IEEE754INT_H  */
