<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2005-2018 Andes Technology Corporation */

#समावेश <यंत्र/bitfield.h>

#घोषणा _FP_W_TYPE_SIZE		32
#घोषणा _FP_W_TYPE		अचिन्हित दीर्घ
#घोषणा _FP_WS_TYPE		चिन्हित दीर्घ
#घोषणा _FP_I_TYPE		दीर्घ

#घोषणा __ll_B ((UWtype) 1 << (W_TYPE_SIZE / 2))
#घोषणा __ll_lowpart(t) ((UWtype) (t) & (__ll_B - 1))
#घोषणा __ll_highpart(t) ((UWtype) (t) >> (W_TYPE_SIZE / 2))

#घोषणा _FP_MUL_MEAT_S(R, X, Y)				\
	_FP_MUL_MEAT_1_wide(_FP_WFRACBITS_S, R, X, Y, umul_ppmm)
#घोषणा _FP_MUL_MEAT_D(R, X, Y)				\
	_FP_MUL_MEAT_2_wide(_FP_WFRACBITS_D, R, X, Y, umul_ppmm)
#घोषणा _FP_MUL_MEAT_Q(R, X, Y)				\
	_FP_MUL_MEAT_4_wide(_FP_WFRACBITS_Q, R, X, Y, umul_ppmm)

#घोषणा _FP_MUL_MEAT_DW_S(R, X, Y)			\
	_FP_MUL_MEAT_DW_1_wide(_FP_WFRACBITS_S, R, X, Y, umul_ppmm)
#घोषणा _FP_MUL_MEAT_DW_D(R, X, Y)			\
	_FP_MUL_MEAT_DW_2_wide(_FP_WFRACBITS_D, R, X, Y, umul_ppmm)

#घोषणा _FP_DIV_MEAT_S(R, X, Y)	_FP_DIV_MEAT_1_uभाग_norm(S, R, X, Y)
#घोषणा _FP_DIV_MEAT_D(R, X, Y)	_FP_DIV_MEAT_2_uभाग(D, R, X, Y)

#घोषणा _FP_न_अंकFRAC_S		((_FP_Qन_अंकBIT_S << 1) - 1)
#घोषणा _FP_न_अंकFRAC_D		((_FP_Qन_अंकBIT_D << 1) - 1), -1
#घोषणा _FP_न_अंकFRAC_Q		((_FP_Qन_अंकBIT_Q << 1) - 1), -1, -1, -1
#घोषणा _FP_न_अंकSIGN_S		0
#घोषणा _FP_न_अंकSIGN_D		0
#घोषणा _FP_न_अंकSIGN_Q		0

#घोषणा _FP_KEEPन_अंकFRACP 1
#घोषणा _FP_Qन_अंकNEGATEDP 0

#घोषणा _FP_CHOOSEन_अंक(fs, wc, R, X, Y, OP)			\
करो अणु								\
	अगर ((_FP_FRAC_HIGH_RAW_##fs(X) & _FP_Qन_अंकBIT_##fs)	\
	  && !(_FP_FRAC_HIGH_RAW_##fs(Y) & _FP_Qन_अंकBIT_##fs)) अणु \
		R##_s = Y##_s;					\
		_FP_FRAC_COPY_##wc(R, Y);			\
	पूर्ण अन्यथा अणु						\
		R##_s = X##_s;					\
		_FP_FRAC_COPY_##wc(R, X);			\
	पूर्ण							\
	R##_c = FP_CLS_न_अंक;					\
पूर्ण जबतक (0)

#घोषणा __FPU_FPCSR	(current->thपढ़ो.fpu.fpcsr)

/* Obtain the current rounding mode. */
#घोषणा FP_ROUNDMODE                    \
(अणु                                      \
	__FPU_FPCSR & FPCSR_mskRM;      \
पूर्ण)

#घोषणा FP_RND_NEAREST		0
#घोषणा FP_RND_PINF		1
#घोषणा FP_RND_MINF		2
#घोषणा FP_RND_ZERO		3

#घोषणा FP_EX_INVALID		FPCSR_mskIVO
#घोषणा FP_EX_DIVZERO		FPCSR_mskDBZ
#घोषणा FP_EX_OVERFLOW		FPCSR_mskOVF
#घोषणा FP_EX_UNDERFLOW		FPCSR_mskUDF
#घोषणा FP_EX_INEXACT		FPCSR_mskIEX

#घोषणा SF_CEQ	2
#घोषणा SF_CLT	1
#घोषणा SF_CGT	3
#घोषणा SF_CUN	4

#समावेश <यंत्र/byteorder.h>

#अगर_घोषित __BIG_ENDIAN__
#घोषणा __BYTE_ORDER __BIG_ENDIAN
#घोषणा __LITTLE_ENDIAN 0
#अन्यथा
#घोषणा __BYTE_ORDER __LITTLE_ENDIAN
#घोषणा __BIG_ENDIAN 0
#पूर्ण_अगर

#घोषणा पात() करो अणु पूर्ण जबतक (0)
#घोषणा umul_ppmm(w1, w0, u, v)						\
करो अणु									\
	UWtype __x0, __x1, __x2, __x3;                                  \
	UHWtype __ul, __vl, __uh, __vh;                                 \
									\
	__ul = __ll_lowpart(u);						\
	__uh = __ll_highpart(u);					\
	__vl = __ll_lowpart(v);						\
	__vh = __ll_highpart(v);					\
									\
	__x0 = (UWtype) __ul * __vl;                                    \
	__x1 = (UWtype) __ul * __vh;                                    \
	__x2 = (UWtype) __uh * __vl;                                    \
	__x3 = (UWtype) __uh * __vh;                                    \
									\
	__x1 += __ll_highpart(__x0);					\
	__x1 += __x2;							\
	अगर (__x1 < __x2)						\
		__x3 += __ll_B;						\
									\
	(w1) = __x3 + __ll_highpart(__x1);				\
	(w0) = __ll_lowpart(__x1) * __ll_B + __ll_lowpart(__x0);	\
पूर्ण जबतक (0)

#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
करो अणु \
	UWtype __x; \
	__x = (al) + (bl); \
	(sh) = (ah) + (bh) + (__x < (al)); \
	(sl) = __x; \
पूर्ण जबतक (0)

#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
करो अणु \
	UWtype __x; \
	__x = (al) - (bl); \
	(sh) = (ah) - (bh) - (__x > (al)); \
	(sl) = __x; \
पूर्ण जबतक (0)

#घोषणा uभाग_qrnnd(q, r, n1, n0, d)				\
करो अणु								\
	UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m;		\
	__d1 = __ll_highpart(d);				\
	__d0 = __ll_lowpart(d);					\
								\
	__r1 = (n1) % __d1;					\
	__q1 = (n1) / __d1;					\
	__m = (UWtype) __q1 * __d0;				\
	__r1 = __r1 * __ll_B | __ll_highpart(n0);		\
	अगर (__r1 < __m)	अणु					\
		__q1--, __r1 += (d);				\
		अगर (__r1 >= (d))				\
			अगर (__r1 < __m)				\
				__q1--, __r1 += (d);		\
	पूर्ण							\
	__r1 -= __m;						\
	__r0 = __r1 % __d1;					\
	__q0 = __r1 / __d1;					\
	__m = (UWtype) __q0 * __d0;				\
	__r0 = __r0 * __ll_B | __ll_lowpart(n0);		\
	अगर (__r0 < __m)	अणु					\
		__q0--, __r0 += (d);				\
		अगर (__r0 >= (d))				\
			अगर (__r0 < __m)				\
				__q0--, __r0 += (d);		\
	पूर्ण							\
	__r0 -= __m;						\
	(q) = (UWtype) __q1 * __ll_B | __q0;			\
	(r) = __r0;						\
पूर्ण जबतक (0)
