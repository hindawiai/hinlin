<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "libgcc.h"

#घोषणा __ll_B ((UWtype) 1 << (W_TYPE_SIZE / 2))
#घोषणा __ll_lowpart(t) ((UWtype) (t) & (__ll_B - 1))
#घोषणा __ll_highpart(t) ((UWtype) (t) >> (W_TYPE_SIZE / 2))

#घोषणा umul_ppmm(w1, w0, u, v) \
	करो अणु			   \
		UWtype __x0, __x1, __x2, __x3;	\
		UHWtype __ul, __vl, __uh, __vh; \
		__ul = __ll_lowpart(u);	\
		__uh = __ll_highpart(u);	\
		__vl = __ll_lowpart(v);	\
		__vh = __ll_highpart(v);	\
		__x0 = (UWtype) __ul * __vl;	\
		__x1 = (UWtype) __ul * __vh;	\
		__x2 = (UWtype) __uh * __vl;	\
		__x3 = (UWtype) __uh * __vh;	\
		__x1 += __ll_highpart(__x0);	\
		__x1 += __x2;			\
		अगर (__x1 < __x2)		\
			__x3 += __ll_B;		\
		(w1) = __x3 + __ll_highpart(__x1);	       \
		(w0) = __ll_lowpart(__x1) * __ll_B + __ll_lowpart(__x0); \
	पूर्ण जबतक (0)

#घोषणा __umulsidi3(u, v) (			\
		अणु				\
			DWजोड़ __w;		\
			umul_ppmm(__w.s.high, __w.s.low, u, v);	\
			__w.ll; पूर्ण					\
		)

DWtype __muldi3(DWtype u, DWtype v)
अणु
	स्थिर DWजोड़ uu = अणु.ll = uपूर्ण;
	स्थिर DWजोड़ vv = अणु.ll = vपूर्ण;
	DWजोड़ w = अणु.ll = __umulsidi3(uu.s.low, vv.s.low)पूर्ण;

	w.s.high += ((UWtype) uu.s.low * (UWtype) vv.s.high
		     + (UWtype) uu.s.high * (UWtype) vv.s.low);

	वापस w.ll;
पूर्ण
