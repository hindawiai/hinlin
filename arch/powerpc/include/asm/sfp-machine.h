<शैली गुरु>
/* Machine-dependent software भग्नing-poपूर्णांक definitions.  PPC version.
   Copyright (C) 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is मुक्त software; you can redistribute it and/or
   modअगरy it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License क्रम more details.

   You should have received a copy of the GNU Library General Public
   License aदीर्घ with the GNU C Library; see the file COPYING.LIB.  If
   not, ग_लिखो to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Actually, this is a PPC (32bit) version, written based on the
   i386, sparc, and sparc64 versions, by me,
   Peter Maydell (pmaydell@chiark.greenend.org.uk).
   Comments are by and large also mine, although they may be inaccurate.

   In picking out यंत्र fragments I've gone with the lowest common
   denominator, which also happens to be the hardware I have :->
   That is, a SPARC without hardware multiply and भागide.
 */

/* basic word size definitions */
#घोषणा _FP_W_TYPE_SIZE		32
#घोषणा _FP_W_TYPE		अचिन्हित पूर्णांक
#घोषणा _FP_WS_TYPE		चिन्हित पूर्णांक
#घोषणा _FP_I_TYPE		पूर्णांक

#घोषणा __ll_B			((UWtype) 1 << (W_TYPE_SIZE / 2))
#घोषणा __ll_lowpart(t)		((UWtype) (t) & (__ll_B - 1))
#घोषणा __ll_highpart(t)	((UWtype) (t) >> (W_TYPE_SIZE / 2))

/* You can optionally code some things like addition in यंत्र. For
 * example, i386 defines __FP_FRAC_ADD_2 as यंत्र. If you करोn't
 * then you get a fragment of C code [अगर you change an #अगर_घोषित 0
 * in op-2.h] or a call to add_ssaaaa (see below).
 * Good places to look क्रम यंत्र fragments to use are gcc and glibc.
 * gcc's दीर्घदीर्घ.h is useful.
 */

/* We need to know how to multiply and भागide. If the host word size
 * is >= 2*fracbits you can use FP_MUL_MEAT_n_imm(t,R,X,Y) which
 * codes the multiply with whatever gcc करोes to 'a * b'.
 * _FP_MUL_MEAT_n_wide(t,R,X,Y,f) is used when you have an यंत्र
 * function that can multiply two 1W values and get a 2W result.
 * Otherwise you're stuck with _FP_MUL_MEAT_n_hard(t,R,X,Y) which
 * करोes bitshअगरting to aव्योम overflow.
 * For भागision there is FP_DIV_MEAT_n_imm(t,R,X,Y,f) क्रम word size
 * >= 2*fracbits, where f is either _FP_DIV_HELP_imm or
 * _FP_DIV_HELP_द_भाग (see op-1.h).
 * _FP_DIV_MEAT_uभाग() is अगर you have यंत्र to करो 2W/1W => (1W, 1W).
 * [GCC and glibc have दीर्घदीर्घ.h which has the यंत्र macro uभाग_qrnnd
 * to करो this.]
 * In general, 'n' is the number of words required to hold the type,
 * and 't' is either S, D or Q क्रम single/द्विगुन/quad.
 *           -- PMM
 */
/* Example: SPARC64:
 * #घोषणा _FP_MUL_MEAT_S(R,X,Y)	_FP_MUL_MEAT_1_imm(S,R,X,Y)
 * #घोषणा _FP_MUL_MEAT_D(R,X,Y)	_FP_MUL_MEAT_1_wide(D,R,X,Y,umul_ppmm)
 * #घोषणा _FP_MUL_MEAT_Q(R,X,Y)	_FP_MUL_MEAT_2_wide(Q,R,X,Y,umul_ppmm)
 *
 * #घोषणा _FP_DIV_MEAT_S(R,X,Y)	_FP_DIV_MEAT_1_imm(S,R,X,Y,_FP_DIV_HELP_imm)
 * #घोषणा _FP_DIV_MEAT_D(R,X,Y)	_FP_DIV_MEAT_1_uभाग(D,R,X,Y)
 * #घोषणा _FP_DIV_MEAT_Q(R,X,Y)	_FP_DIV_MEAT_2_uभाग_64(Q,R,X,Y)
 *
 * Example: i386:
 * #घोषणा _FP_MUL_MEAT_S(R,X,Y)   _FP_MUL_MEAT_1_wide(S,R,X,Y,_i386_mul_32_64)
 * #घोषणा _FP_MUL_MEAT_D(R,X,Y)   _FP_MUL_MEAT_2_wide(D,R,X,Y,_i386_mul_32_64)
 *
 * #घोषणा _FP_DIV_MEAT_S(R,X,Y)   _FP_DIV_MEAT_1_uभाग(S,R,X,Y,_i386_भाग_64_32)
 * #घोषणा _FP_DIV_MEAT_D(R,X,Y)   _FP_DIV_MEAT_2_uभाग_64(D,R,X,Y)
 */

#घोषणा _FP_MUL_MEAT_S(R,X,Y)   _FP_MUL_MEAT_1_wide(_FP_WFRACBITS_S,R,X,Y,umul_ppmm)
#घोषणा _FP_MUL_MEAT_D(R,X,Y)   _FP_MUL_MEAT_2_wide(_FP_WFRACBITS_D,R,X,Y,umul_ppmm)

#घोषणा _FP_DIV_MEAT_S(R,X,Y)	_FP_DIV_MEAT_1_uभाग_norm(S,R,X,Y)
#घोषणा _FP_DIV_MEAT_D(R,X,Y)	_FP_DIV_MEAT_2_uभाग(D,R,X,Y)

/* These macros define what NaN looks like. They're supposed to expand to
 * a comma-separated set of 32bit अचिन्हित पूर्णांकs that encode NaN.
 */
#घोषणा _FP_न_अंकFRAC_S		((_FP_Qन_अंकBIT_S << 1) - 1)
#घोषणा _FP_न_अंकFRAC_D		((_FP_Qन_अंकBIT_D << 1) - 1), -1
#घोषणा _FP_न_अंकFRAC_Q		((_FP_Qन_अंकBIT_Q << 1) - 1), -1, -1, -1
#घोषणा _FP_न_अंकSIGN_S		0
#घोषणा _FP_न_अंकSIGN_D		0
#घोषणा _FP_न_अंकSIGN_Q		0

#घोषणा _FP_KEEPन_अंकFRACP 1

#अगर_घोषित FP_EX_BOOKE_E500_SPE
#घोषणा FP_EX_INEXACT		(1 << 21)
#घोषणा FP_EX_INVALID		(1 << 20)
#घोषणा FP_EX_DIVZERO		(1 << 19)
#घोषणा FP_EX_UNDERFLOW		(1 << 18)
#घोषणा FP_EX_OVERFLOW		(1 << 17)
#घोषणा FP_INHIBIT_RESULTS	0

#घोषणा __FPU_FPSCR	(current->thपढ़ो.spefscr)
#घोषणा __FPU_ENABLED_EXC		\
(अणु					\
	(__FPU_FPSCR >> 2) & 0x1f;	\
पूर्ण)
#अन्यथा
/* Exception flags.  We use the bit positions of the appropriate bits
   in the FPSCR, which also correspond to the FE_* bits.  This makes
   everything easier ;-).  */
#घोषणा FP_EX_INVALID         (1 << (31 - 2))
#घोषणा FP_EX_INVALID_Sन_अंक	EFLAG_VXSन_अंक
#घोषणा FP_EX_INVALID_ISI	EFLAG_VXISI
#घोषणा FP_EX_INVALID_IDI	EFLAG_VXIDI
#घोषणा FP_EX_INVALID_ZDZ	EFLAG_VXZDZ
#घोषणा FP_EX_INVALID_IMZ	EFLAG_VXIMZ
#घोषणा FP_EX_OVERFLOW        (1 << (31 - 3))
#घोषणा FP_EX_UNDERFLOW       (1 << (31 - 4))
#घोषणा FP_EX_DIVZERO         (1 << (31 - 5))
#घोषणा FP_EX_INEXACT         (1 << (31 - 6))

#घोषणा __FPU_FPSCR	(current->thपढ़ो.fp_state.fpscr)

/* We only actually ग_लिखो to the destination रेजिस्टर
 * अगर exceptions संकेतled (अगर any) will not trap.
 */
#घोषणा __FPU_ENABLED_EXC \
(अणु						\
	(__FPU_FPSCR >> 3) & 0x1f;	\
पूर्ण)

#पूर्ण_अगर

/*
 * If one NaN is संकेतing and the other is not,
 * we choose that one, otherwise we choose X.
 */
#घोषणा _FP_CHOOSEन_अंक(fs, wc, R, X, Y, OP)			\
  करो अणु								\
    अगर ((_FP_FRAC_HIGH_RAW_##fs(Y) & _FP_Qन_अंकBIT_##fs)		\
	&& !(_FP_FRAC_HIGH_RAW_##fs(X) & _FP_Qन_अंकBIT_##fs))	\
      अणु								\
	R##_s = X##_s;						\
	_FP_FRAC_COPY_##wc(R,X);				\
      पूर्ण								\
    अन्यथा							\
      अणु								\
	R##_s = Y##_s;						\
	_FP_FRAC_COPY_##wc(R,Y);				\
      पूर्ण								\
    R##_c = FP_CLS_न_अंक;						\
  पूर्ण जबतक (0)


#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>

#घोषणा __FPU_TRAP_P(bits) \
	((__FPU_ENABLED_EXC & (bits)) != 0)

#घोषणा __FP_PACK_S(val,X)			\
(अणु  पूर्णांक __exc = _FP_PACK_CANONICAL(S,1,X);	\
    अगर(!__exc || !__FPU_TRAP_P(__exc))		\
        _FP_PACK_RAW_1_P(S,val,X);		\
    __exc;					\
पूर्ण)

#घोषणा __FP_PACK_D(val,X)			\
   करो अणु									\
	_FP_PACK_CANONICAL(D, 2, X);					\
	अगर (!FP_CUR_EXCEPTIONS || !__FPU_TRAP_P(FP_CUR_EXCEPTIONS))	\
		_FP_PACK_RAW_2_P(D, val, X);				\
   पूर्ण जबतक (0)

#घोषणा __FP_PACK_DS(val,X)							\
   करो अणु										\
	   FP_DECL_S(__X);							\
	   FP_CONV(S, D, 1, 2, __X, X);						\
	   _FP_PACK_CANONICAL(S, 1, __X);					\
	   अगर (!FP_CUR_EXCEPTIONS || !__FPU_TRAP_P(FP_CUR_EXCEPTIONS)) अणु	\
		   _FP_UNPACK_CANONICAL(S, 1, __X);				\
		   FP_CONV(D, S, 2, 1, X, __X);					\
		   _FP_PACK_CANONICAL(D, 2, X);					\
		   अगर (!FP_CUR_EXCEPTIONS || !__FPU_TRAP_P(FP_CUR_EXCEPTIONS))	\
		   _FP_PACK_RAW_2_P(D, val, X);					\
	   पूर्ण									\
   पूर्ण जबतक (0)

/* Obtain the current rounding mode. */
#घोषणा FP_ROUNDMODE			\
(अणु					\
	__FPU_FPSCR & 0x3;		\
पूर्ण)

/* the यंत्र fragments go here: all these are taken from glibc-2.0.5's
 * stdlib/दीर्घदीर्घ.h
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

/* add_ssaaaa is used in op-2.h and should be equivalent to
 * #घोषणा add_ssaaaa(sh,sl,ah,al,bh,bl) (sh = ah+bh+ (( sl = al+bl) < al))
 * add_ssaaaa(high_sum, low_sum, high_addend_1, low_addend_1,
 * high_addend_2, low_addend_2) adds two UWtype पूर्णांकegers, composed by
 * HIGH_ADDEND_1 and LOW_ADDEND_1, and HIGH_ADDEND_2 and LOW_ADDEND_2
 * respectively.  The result is placed in HIGH_SUM and LOW_SUM.  Overflow
 * (i.e. carry out) is not stored anywhere, and is lost.
 */
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
  करो अणु									\
    अगर (__builtin_स्थिरant_p (bh) && (bh) == 0)				\
      __यंत्र__ ("add%I4c %1,%3,%4\n\taddze %0,%2"		\
	     : "=r" (sh), "=&r" (sl) : "r" (ah), "%r" (al), "rI" (bl));\
    अन्यथा अगर (__builtin_स्थिरant_p (bh) && (bh) == ~(USItype) 0)		\
      __यंत्र__ ("add%I4c %1,%3,%4\n\taddme %0,%2"		\
	     : "=r" (sh), "=&r" (sl) : "r" (ah), "%r" (al), "rI" (bl));\
    अन्यथा								\
      __यंत्र__ ("add%I5c %1,%4,%5\n\tadde %0,%2,%3"		\
	     : "=r" (sh), "=&r" (sl)					\
	     : "%r" (ah), "r" (bh), "%r" (al), "rI" (bl));		\
  पूर्ण जबतक (0)

/* sub_ddmmss is used in op-2.h and uभागmodti4.c and should be equivalent to
 * #घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) (sh = ah-bh - ((sl = al-bl) > al))
 * sub_ddmmss(high_dअगरference, low_dअगरference, high_minuend, low_minuend,
 * high_subtrahend, low_subtrahend) subtracts two two-word UWtype पूर्णांकegers,
 * composed by HIGH_MINUEND_1 and LOW_MINUEND_1, and HIGH_SUBTRAHEND_2 and
 * LOW_SUBTRAHEND_2 respectively.  The result is placed in HIGH_DIFFERENCE
 * and LOW_DIFFERENCE.  Overflow (i.e. carry out) is not stored anywhere,
 * and is lost.
 */
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
  करो अणु									\
    अगर (__builtin_स्थिरant_p (ah) && (ah) == 0)				\
      __यंत्र__ ("subf%I3c %1,%4,%3\n\tsubfze %0,%2"	\
	       : "=r" (sh), "=&r" (sl) : "r" (bh), "rI" (al), "r" (bl));\
    अन्यथा अगर (__builtin_स्थिरant_p (ah) && (ah) == ~(USItype) 0)		\
      __यंत्र__ ("subf%I3c %1,%4,%3\n\tsubfme %0,%2"	\
	       : "=r" (sh), "=&r" (sl) : "r" (bh), "rI" (al), "r" (bl));\
    अन्यथा अगर (__builtin_स्थिरant_p (bh) && (bh) == 0)			\
      __यंत्र__ ("subf%I3c %1,%4,%3\n\taddme %0,%2"		\
	       : "=r" (sh), "=&r" (sl) : "r" (ah), "rI" (al), "r" (bl));\
    अन्यथा अगर (__builtin_स्थिरant_p (bh) && (bh) == ~(USItype) 0)		\
      __यंत्र__ ("subf%I3c %1,%4,%3\n\taddze %0,%2"		\
	       : "=r" (sh), "=&r" (sl) : "r" (ah), "rI" (al), "r" (bl));\
    अन्यथा								\
      __यंत्र__ ("subf%I4c %1,%5,%4\n\tsubfe %0,%3,%2"	\
	       : "=r" (sh), "=&r" (sl)					\
	       : "r" (ah), "r" (bh), "rI" (al), "r" (bl));		\
  पूर्ण जबतक (0)

/* यंत्र fragments क्रम mul and भाग */

/* umul_ppmm(high_prod, low_prod, multipler, multiplicand) multiplies two
 * UWtype पूर्णांकegers MULTIPLER and MULTIPLICAND, and generates a two UWtype
 * word product in HIGH_PROD and LOW_PROD.
 */
#घोषणा umul_ppmm(ph, pl, m0, m1) \
  करो अणु									\
    USItype __m0 = (m0), __m1 = (m1);					\
    __यंत्र__ ("mulhwu %0,%1,%2" : "=r" (ph) : "%r" (m0), "r" (m1));	\
    (pl) = __m0 * __m1;							\
  पूर्ण जबतक (0)

/* uभाग_qrnnd(quotient, reमुख्यder, high_numerator, low_numerator,
 * denominator) भागides a UDWtype, composed by the UWtype पूर्णांकegers
 * HIGH_NUMERATOR and LOW_NUMERATOR, by DENOMINATOR and places the quotient
 * in QUOTIENT and the reमुख्यder in REMAINDER.  HIGH_NUMERATOR must be less
 * than DENOMINATOR क्रम correct operation.  If, in addition, the most
 * signअगरicant bit of DENOMINATOR must be 1, then the pre-processor symbol
 * UDIV_NEEDS_NORMALIZATION is defined to 1.
 */
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
  करो अणु									\
    UWtype __d1, __d0, __q1, __q0;					\
    UWtype __r1, __r0, __m;						\
    __d1 = __ll_highpart (d);						\
    __d0 = __ll_lowpart (d);						\
									\
    __r1 = (n1) % __d1;							\
    __q1 = (n1) / __d1;							\
    __m = (UWtype) __q1 * __d0;						\
    __r1 = __r1 * __ll_B | __ll_highpart (n0);				\
    अगर (__r1 < __m)							\
      अणु									\
	__q1--, __r1 += (d);						\
	अगर (__r1 >= (d)) /* i.e. we didn't get carry when adding to __r1 */\
	  अगर (__r1 < __m)						\
	    __q1--, __r1 += (d);					\
      पूर्ण									\
    __r1 -= __m;							\
									\
    __r0 = __r1 % __d1;							\
    __q0 = __r1 / __d1;							\
    __m = (UWtype) __q0 * __d0;						\
    __r0 = __r0 * __ll_B | __ll_lowpart (n0);				\
    अगर (__r0 < __m)							\
      अणु									\
	__q0--, __r0 += (d);						\
	अगर (__r0 >= (d))						\
	  अगर (__r0 < __m)						\
	    __q0--, __r0 += (d);					\
      पूर्ण									\
    __r0 -= __m;							\
									\
    (q) = (UWtype) __q1 * __ll_B | __q0;				\
    (r) = __r0;								\
  पूर्ण जबतक (0)

#घोषणा UDIV_NEEDS_NORMALIZATION 1

#घोषणा पात()								\
	वापस 0

#अगर_घोषित __BIG_ENDIAN
#घोषणा __BYTE_ORDER __BIG_ENDIAN
#अन्यथा
#घोषणा __BYTE_ORDER __LITTLE_ENDIAN
#पूर्ण_अगर

/* Exception flags. */
#घोषणा EFLAG_INVALID		(1 << (31 - 2))
#घोषणा EFLAG_OVERFLOW		(1 << (31 - 3))
#घोषणा EFLAG_UNDERFLOW		(1 << (31 - 4))
#घोषणा EFLAG_DIVZERO		(1 << (31 - 5))
#घोषणा EFLAG_INEXACT		(1 << (31 - 6))

#घोषणा EFLAG_VXSन_अंक		(1 << (31 - 7))
#घोषणा EFLAG_VXISI		(1 << (31 - 8))
#घोषणा EFLAG_VXIDI		(1 << (31 - 9))
#घोषणा EFLAG_VXZDZ		(1 << (31 - 10))
#घोषणा EFLAG_VXIMZ		(1 << (31 - 11))
#घोषणा EFLAG_VXVC		(1 << (31 - 12))
#घोषणा EFLAG_VXSOFT		(1 << (31 - 21))
#घोषणा EFLAG_VXSQRT		(1 << (31 - 22))
#घोषणा EFLAG_VXCVI		(1 << (31 - 23))
