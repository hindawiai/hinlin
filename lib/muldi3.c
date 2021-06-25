<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/export.h>
#समावेश <linux/libgcc.h>

#घोषणा W_TYPE_SIZE 32

#घोषणा __ll_B ((अचिन्हित दीर्घ) 1 << (W_TYPE_SIZE / 2))
#घोषणा __ll_lowpart(t) ((अचिन्हित दीर्घ) (t) & (__ll_B - 1))
#घोषणा __ll_highpart(t) ((अचिन्हित दीर्घ) (t) >> (W_TYPE_SIZE / 2))

/* If we still करोn't have umul_ppmm, define it using plain C.  */
#अगर !defined(umul_ppmm)
#घोषणा umul_ppmm(w1, w0, u, v)						\
	करो अणु								\
		अचिन्हित दीर्घ __x0, __x1, __x2, __x3;			\
		अचिन्हित लघु __ul, __vl, __uh, __vh;			\
									\
		__ul = __ll_lowpart(u);					\
		__uh = __ll_highpart(u);				\
		__vl = __ll_lowpart(v);					\
		__vh = __ll_highpart(v);				\
									\
		__x0 = (अचिन्हित दीर्घ) __ul * __vl;			\
		__x1 = (अचिन्हित दीर्घ) __ul * __vh;			\
		__x2 = (अचिन्हित दीर्घ) __uh * __vl;			\
		__x3 = (अचिन्हित दीर्घ) __uh * __vh;			\
									\
		__x1 += __ll_highpart(__x0); /* this can't give carry */\
		__x1 += __x2; /* but this indeed can */			\
		अगर (__x1 < __x2) /* did we get it? */			\
		__x3 += __ll_B; /* yes, add it in the proper pos */	\
									\
		(w1) = __x3 + __ll_highpart(__x1);			\
		(w0) = __ll_lowpart(__x1) * __ll_B + __ll_lowpart(__x0);\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर !defined(__umulsidi3)
#घोषणा __umulsidi3(u, v) (अणु				\
	DWजोड़ __w;					\
	umul_ppmm(__w.s.high, __w.s.low, u, v);		\
	__w.ll;						\
	पूर्ण)
#पूर्ण_अगर

दीर्घ दीर्घ notrace __muldi3(दीर्घ दीर्घ u, दीर्घ दीर्घ v)
अणु
	स्थिर DWजोड़ uu = अणु.ll = uपूर्ण;
	स्थिर DWजोड़ vv = अणु.ll = vपूर्ण;
	DWजोड़ w = अणु.ll = __umulsidi3(uu.s.low, vv.s.low)पूर्ण;

	w.s.high += ((अचिन्हित दीर्घ) uu.s.low * (अचिन्हित दीर्घ) vv.s.high
		+ (अचिन्हित दीर्घ) uu.s.high * (अचिन्हित दीर्घ) vv.s.low);

	वापस w.ll;
पूर्ण
EXPORT_SYMBOL(__muldi3);
