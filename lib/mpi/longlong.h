<शैली गुरु>
/* दीर्घदीर्घ.h -- definitions क्रम mixed size 32/64 bit arithmetic.
 * Note: I added some stuff क्रम use with gnupg
 *
 * Copyright (C) 1991, 1992, 1993, 1994, 1996, 1998,
 *	2000, 2001, 2002, 2003 Free Software Foundation, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License क्रम more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * aदीर्घ with this file; see the file COPYING.LIB.  If not, ग_लिखो to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA. */

#समावेश <linux/count_zeros.h>

/* You have to define the following beक्रमe including this file:
 *
 * UWtype -- An अचिन्हित type, शेष type क्रम operations (typically a "word")
 * UHWtype -- An अचिन्हित type, at least half the size of UWtype.
 * UDWtype -- An अचिन्हित type, at least twice as large a UWtype
 * W_TYPE_SIZE -- size in bits of UWtype
 *
 * SItype, USItype -- Signed and अचिन्हित 32 bit types.
 * DItype, UDItype -- Signed and अचिन्हित 64 bit types.
 *
 * On a 32 bit machine UWtype should typically be USItype;
 * on a 64 bit machine, UWtype should typically be UDItype.
*/

#घोषणा __BITS4 (W_TYPE_SIZE / 4)
#घोषणा __ll_B ((UWtype) 1 << (W_TYPE_SIZE / 2))
#घोषणा __ll_lowpart(t) ((UWtype) (t) & (__ll_B - 1))
#घोषणा __ll_highpart(t) ((UWtype) (t) >> (W_TYPE_SIZE / 2))

/* This is used to make sure no undesirable sharing between dअगरferent libraries
	that use this file takes place.  */
#अगर_अघोषित __MPN
#घोषणा __MPN(x) __##x
#पूर्ण_अगर

/* Define auxiliary यंत्र macros.
 *
 * 1) umul_ppmm(high_prod, low_prod, multipler, multiplicand) multiplies two
 * UWtype पूर्णांकegers MULTIPLER and MULTIPLICAND, and generates a two UWtype
 * word product in HIGH_PROD and LOW_PROD.
 *
 * 2) __umulsidi3(a,b) multiplies two UWtype पूर्णांकegers A and B, and वापसs a
 * UDWtype product.  This is just a variant of umul_ppmm.

 * 3) uभाग_qrnnd(quotient, reमुख्यder, high_numerator, low_numerator,
 * denominator) भागides a UDWtype, composed by the UWtype पूर्णांकegers
 * HIGH_NUMERATOR and LOW_NUMERATOR, by DENOMINATOR and places the quotient
 * in QUOTIENT and the reमुख्यder in REMAINDER.	HIGH_NUMERATOR must be less
 * than DENOMINATOR क्रम correct operation.  If, in addition, the most
 * signअगरicant bit of DENOMINATOR must be 1, then the pre-processor symbol
 * UDIV_NEEDS_NORMALIZATION is defined to 1.
 * 4) sभाग_qrnnd(quotient, reमुख्यder, high_numerator, low_numerator,
 * denominator).  Like uभाग_qrnnd but the numbers are चिन्हित.  The quotient
 * is rounded towards 0.
 *
 * 5) count_leading_zeros(count, x) counts the number of zero-bits from the
 * msb to the first non-zero bit in the UWtype X.  This is the number of
 * steps X needs to be shअगरted left to set the msb.  Undefined क्रम X == 0,
 * unless the symbol COUNT_LEADING_ZEROS_0 is defined to some value.
 *
 * 6) count_trailing_zeros(count, x) like count_leading_zeros, but counts
 * from the least signअगरicant end.
 *
 * 7) add_ssaaaa(high_sum, low_sum, high_addend_1, low_addend_1,
 * high_addend_2, low_addend_2) adds two UWtype पूर्णांकegers, composed by
 * HIGH_ADDEND_1 and LOW_ADDEND_1, and HIGH_ADDEND_2 and LOW_ADDEND_2
 * respectively.  The result is placed in HIGH_SUM and LOW_SUM.  Overflow
 * (i.e. carry out) is not stored anywhere, and is lost.
 *
 * 8) sub_ddmmss(high_dअगरference, low_dअगरference, high_minuend, low_minuend,
 * high_subtrahend, low_subtrahend) subtracts two two-word UWtype पूर्णांकegers,
 * composed by HIGH_MINUEND_1 and LOW_MINUEND_1, and HIGH_SUBTRAHEND_2 and
 * LOW_SUBTRAHEND_2 respectively.  The result is placed in HIGH_DIFFERENCE
 * and LOW_DIFFERENCE.	Overflow (i.e. carry out) is not stored anywhere,
 * and is lost.
 *
 * If any of these macros are left undefined क्रम a particular CPU,
 * C macros are used.  */

/* The CPUs come in alphabetical order below.
 *
 * Please add support क्रम more CPUs here, or improve the current support
 * क्रम the CPUs below!	*/

#अगर defined(__GNUC__) && !defined(NO_ASM)

/* We someबार need to clobber "cc" with gcc2, but that would not be
	understood by gcc1.	Use cpp to aव्योम major code duplication.  */
#अगर __GNUC__ < 2
#घोषणा __CLOBBER_CC
#घोषणा __AND_CLOBBER_CC
#अन्यथा /* __GNUC__ >= 2 */
#घोषणा __CLOBBER_CC : "cc"
#घोषणा __AND_CLOBBER_CC , "cc"
#पूर्ण_अगर /* __GNUC__ < 2 */

/***************************************
	**************  A29K  *****************
	***************************************/
#अगर (defined(__a29k__) || defined(_AM29K)) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("add %1,%4,%5\n" \
		"addc %0,%2,%3" \
	: "=r" ((USItype)(sh)), \
		"=&r" ((USItype)(sl)) \
	: "%r" ((USItype)(ah)), \
		"rI" ((USItype)(bh)), \
		"%r" ((USItype)(al)), \
		"rI" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("sub %1,%4,%5\n" \
		"subc %0,%2,%3" \
	: "=r" ((USItype)(sh)), \
		"=&r" ((USItype)(sl)) \
	: "r" ((USItype)(ah)), \
		"rI" ((USItype)(bh)), \
		"r" ((USItype)(al)), \
		"rI" ((USItype)(bl)))
#घोषणा umul_ppmm(xh, xl, m0, m1) \
करो अणु \
		USItype __m0 = (m0), __m1 = (m1); \
		__यंत्र__ ("multiplu %0,%1,%2" \
		: "=r" ((USItype)(xl)) \
		: "r" (__m0), \
			"r" (__m1)); \
		__यंत्र__ ("multmu %0,%1,%2" \
		: "=r" ((USItype)(xh)) \
		: "r" (__m0), \
			"r" (__m1)); \
पूर्ण जबतक (0)
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
	__यंत्र__ ("dividu %0,%3,%4" \
	: "=r" ((USItype)(q)), \
		"=q" ((USItype)(r)) \
	: "1" ((USItype)(n1)), \
		"r" ((USItype)(n0)), \
		"r" ((USItype)(d)))
#पूर्ण_अगर /* __a29k__ */

#अगर defined(__alpha) && W_TYPE_SIZE == 64
#घोषणा umul_ppmm(ph, pl, m0, m1)			\
करो अणु							\
	UDItype __m0 = (m0), __m1 = (m1);		\
	(ph) = __builtin_alpha_umulh(__m0, __m1);	\
	(pl) = __m0 * __m1;                             \
पूर्ण जबतक (0)
#घोषणा UMUL_TIME 46
#अगर_अघोषित LONGLONG_STANDALONE
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
करो अणु UDItype __r; \
	(q) = __uभाग_qrnnd(&__r, (n1), (n0), (d)); \
	(r) = __r; \
पूर्ण जबतक (0)
बाह्य UDItype __uभाग_qrnnd(UDItype *, UDItype, UDItype, UDItype);
#घोषणा UDIV_TIME 220
#पूर्ण_अगर /* LONGLONG_STANDALONE */
#पूर्ण_अगर /* __alpha */

/***************************************
	**************  ARM  ******************
	***************************************/
#अगर defined(__arm__) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("adds %1, %4, %5\n" \
		"adc  %0, %2, %3" \
	: "=r" (sh), \
		"=&r" (sl) \
	: "%r" ((USItype)(ah)), \
		"rI" ((USItype)(bh)), \
		"%r" ((USItype)(al)), \
		"rI" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("subs %1, %4, %5\n" \
		"sbc  %0, %2, %3" \
	: "=r" (sh), \
		"=&r" (sl) \
	: "r" ((USItype)(ah)), \
		"rI" ((USItype)(bh)), \
		"r" ((USItype)(al)), \
		"rI" ((USItype)(bl)))
#अगर defined __ARM_ARCH_2__ || defined __ARM_ARCH_3__
#घोषणा umul_ppmm(xh, xl, a, b) \
	__यंत्र__ ("@ Inlined umul_ppmm\n" \
		"mov	%|r0, %2, lsr #16		@ AAAA\n" \
		"mov	%|r2, %3, lsr #16		@ BBBB\n" \
		"bic	%|r1, %2, %|r0, lsl #16		@ aaaa\n" \
		"bic	%0, %3, %|r2, lsl #16		@ bbbb\n" \
		"mul	%1, %|r1, %|r2			@ aaaa * BBBB\n" \
		"mul	%|r2, %|r0, %|r2		@ AAAA * BBBB\n" \
		"mul	%|r1, %0, %|r1			@ aaaa * bbbb\n" \
		"mul	%0, %|r0, %0			@ AAAA * bbbb\n" \
		"adds	%|r0, %1, %0			@ central sum\n" \
		"addcs	%|r2, %|r2, #65536\n" \
		"adds	%1, %|r1, %|r0, lsl #16\n" \
		"adc	%0, %|r2, %|r0, lsr #16" \
	: "=&r" (xh), \
		"=r" (xl) \
	: "r" ((USItype)(a)), \
		"r" ((USItype)(b)) \
	: "r0", "r1", "r2")
#अन्यथा
#घोषणा umul_ppmm(xh, xl, a, b) \
	__यंत्र__ ("@ Inlined umul_ppmm\n" \
		"umull %1, %0, %2, %3" \
	: "=&r" (xh), \
		"=&r" (xl) \
	: "r" ((USItype)(a)), \
		"r" ((USItype)(b)) \
	: "r0", "r1")
#पूर्ण_अगर
#घोषणा UMUL_TIME 20
#घोषणा UDIV_TIME 100
#पूर्ण_अगर /* __arm__ */

/***************************************
	**************  CLIPPER  **************
	***************************************/
#अगर defined(__clipper__) && W_TYPE_SIZE == 32
#घोषणा umul_ppmm(w1, w0, u, v) \
	(अणुजोड़ अणुUDItype __ll; \
		काष्ठा अणुUSItype __l, __h; पूर्ण __i; \
	पूर्ण __xx; \
	__यंत्र__ ("mulwux %2,%0" \
	: "=r" (__xx.__ll) \
	: "%0" ((USItype)(u)), \
		"r" ((USItype)(v))); \
	(w1) = __xx.__i.__h; (w0) = __xx.__i.__l; पूर्ण)
#घोषणा smul_ppmm(w1, w0, u, v) \
	(अणुजोड़ अणुDItype __ll; \
		काष्ठा अणुSItype __l, __h; पूर्ण __i; \
	पूर्ण __xx; \
	__यंत्र__ ("mulwx %2,%0" \
	: "=r" (__xx.__ll) \
	: "%0" ((SItype)(u)), \
		"r" ((SItype)(v))); \
	(w1) = __xx.__i.__h; (w0) = __xx.__i.__l; पूर्ण)
#घोषणा __umulsidi3(u, v) \
	(अणुUDItype __w; \
	__यंत्र__ ("mulwux %2,%0" \
	: "=r" (__w) \
	: "%0" ((USItype)(u)), \
		"r" ((USItype)(v))); \
	__w; पूर्ण)
#पूर्ण_अगर /* __clipper__ */

/***************************************
	**************  GMICRO  ***************
	***************************************/
#अगर defined(__gmicro__) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("add.w %5,%1\n" \
		"addx %3,%0" \
	: "=g" ((USItype)(sh)), \
		"=&g" ((USItype)(sl)) \
	: "%0" ((USItype)(ah)), \
		"g" ((USItype)(bh)), \
		"%1" ((USItype)(al)), \
		"g" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("sub.w %5,%1\n" \
		"subx %3,%0" \
	: "=g" ((USItype)(sh)), \
		"=&g" ((USItype)(sl)) \
	: "0" ((USItype)(ah)), \
		"g" ((USItype)(bh)), \
		"1" ((USItype)(al)), \
		"g" ((USItype)(bl)))
#घोषणा umul_ppmm(ph, pl, m0, m1) \
	__यंत्र__ ("mulx %3,%0,%1" \
	: "=g" ((USItype)(ph)), \
		"=r" ((USItype)(pl)) \
	: "%0" ((USItype)(m0)), \
		"g" ((USItype)(m1)))
#घोषणा uभाग_qrnnd(q, r, nh, nl, d) \
	__यंत्र__ ("divx %4,%0,%1" \
	: "=g" ((USItype)(q)), \
		"=r" ((USItype)(r)) \
	: "1" ((USItype)(nh)), \
		"0" ((USItype)(nl)), \
		"g" ((USItype)(d)))
#पूर्ण_अगर

/***************************************
	**************  HPPA  *****************
	***************************************/
#अगर defined(__hppa) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("add %4,%5,%1\n" \
		   "addc %2,%3,%0" \
	: "=r" ((USItype)(sh)), \
	     "=&r" ((USItype)(sl)) \
	: "%rM" ((USItype)(ah)), \
	     "rM" ((USItype)(bh)), \
	     "%rM" ((USItype)(al)), \
	     "rM" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("sub %4,%5,%1\n" \
	   "subb %2,%3,%0" \
	: "=r" ((USItype)(sh)), \
	     "=&r" ((USItype)(sl)) \
	: "rM" ((USItype)(ah)), \
	     "rM" ((USItype)(bh)), \
	     "rM" ((USItype)(al)), \
	     "rM" ((USItype)(bl)))
#अगर 0 && defined(_PA_RISC1_1)
/* xmpyu uses भग्नing poपूर्णांक रेजिस्टर which is not allowed in Linux kernel. */
#घोषणा umul_ppmm(wh, wl, u, v) \
करो अणु \
	जोड़ अणुUDItype __ll; \
	काष्ठा अणुUSItype __h, __l; पूर्ण __i; \
	पूर्ण __xx; \
	__यंत्र__ ("xmpyu %1,%2,%0" \
	: "=*f" (__xx.__ll) \
	: "*f" ((USItype)(u)), \
	       "*f" ((USItype)(v))); \
	(wh) = __xx.__i.__h; \
	(wl) = __xx.__i.__l; \
पूर्ण जबतक (0)
#घोषणा UMUL_TIME 8
#घोषणा UDIV_TIME 60
#अन्यथा
#घोषणा UMUL_TIME 40
#घोषणा UDIV_TIME 80
#पूर्ण_अगर
#अगर 0 /* #अगर_अघोषित LONGLONG_STANDALONE */
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
करो अणु USItype __r; \
	(q) = __uभाग_qrnnd(&__r, (n1), (n0), (d)); \
	(r) = __r; \
पूर्ण जबतक (0)
बाह्य USItype __uभाग_qrnnd();
#पूर्ण_अगर /* LONGLONG_STANDALONE */
#पूर्ण_अगर /* hppa */

/***************************************
	**************  I370  *****************
	***************************************/
#अगर (defined(__i370__) || defined(__mvs__)) && W_TYPE_SIZE == 32
#घोषणा umul_ppmm(xh, xl, m0, m1) \
करो अणु \
	जोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __h, __l; पूर्ण __i; \
	पूर्ण __xx; \
	USItype __m0 = (m0), __m1 = (m1); \
	__यंत्र__ ("mr %0,%3" \
	: "=r" (__xx.__i.__h), \
	       "=r" (__xx.__i.__l) \
	: "%1" (__m0), \
	       "r" (__m1)); \
	(xh) = __xx.__i.__h; (xl) = __xx.__i.__l; \
	(xh) += ((((SItype) __m0 >> 31) & __m1) \
	     + (((SItype) __m1 >> 31) & __m0)); \
पूर्ण जबतक (0)
#घोषणा smul_ppmm(xh, xl, m0, m1) \
करो अणु \
	जोड़ अणुDItype __ll; \
	   काष्ठा अणुUSItype __h, __l; पूर्ण __i; \
	पूर्ण __xx; \
	__यंत्र__ ("mr %0,%3" \
	: "=r" (__xx.__i.__h), \
	       "=r" (__xx.__i.__l) \
	: "%1" (m0), \
	       "r" (m1)); \
	(xh) = __xx.__i.__h; (xl) = __xx.__i.__l; \
पूर्ण जबतक (0)
#घोषणा sभाग_qrnnd(q, r, n1, n0, d) \
करो अणु \
	जोड़ अणुDItype __ll; \
	   काष्ठा अणुUSItype __h, __l; पूर्ण __i; \
	पूर्ण __xx; \
	__xx.__i.__h = n1; __xx.__i.__l = n0; \
	__यंत्र__ ("dr %0,%2" \
	: "=r" (__xx.__ll) \
	: "0" (__xx.__ll), "r" (d)); \
	(q) = __xx.__i.__l; (r) = __xx.__i.__h; \
पूर्ण जबतक (0)
#पूर्ण_अगर

/***************************************
	**************  I386  *****************
	***************************************/
#अघोषित __i386__
#अगर (defined(__i386__) || defined(__i486__)) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("addl %5,%1\n" \
	   "adcl %3,%0" \
	: "=r" (sh), \
	     "=&r" (sl) \
	: "%0" ((USItype)(ah)), \
	     "g" ((USItype)(bh)), \
	     "%1" ((USItype)(al)), \
	     "g" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("subl %5,%1\n" \
	   "sbbl %3,%0" \
	: "=r" (sh), \
	     "=&r" (sl) \
	: "0" ((USItype)(ah)), \
	     "g" ((USItype)(bh)), \
	     "1" ((USItype)(al)), \
	     "g" ((USItype)(bl)))
#घोषणा umul_ppmm(w1, w0, u, v) \
	__यंत्र__ ("mull %3" \
	: "=a" (w0), \
	     "=d" (w1) \
	: "%0" ((USItype)(u)), \
	     "rm" ((USItype)(v)))
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
	__यंत्र__ ("divl %4" \
	: "=a" (q), \
	     "=d" (r) \
	: "0" ((USItype)(n0)), \
	     "1" ((USItype)(n1)), \
	     "rm" ((USItype)(d)))
#अगर_अघोषित UMUL_TIME
#घोषणा UMUL_TIME 40
#पूर्ण_अगर
#अगर_अघोषित UDIV_TIME
#घोषणा UDIV_TIME 40
#पूर्ण_अगर
#पूर्ण_अगर /* 80x86 */

/***************************************
	**************  I860  *****************
	***************************************/
#अगर defined(__i860__) && W_TYPE_SIZE == 32
#घोषणा rshअगरt_rhlc(r, h, l, c) \
	__यंत्र__ ("shr %3,r0,r0\n" \
	"shrd %1,%2,%0" \
	   "=r" (r) : "r" (h), "r" (l), "rn" (c))
#पूर्ण_अगर /* i860 */

/***************************************
	**************  I960  *****************
	***************************************/
#अगर defined(__i960__) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("cmpo 1,0\n" \
	"addc %5,%4,%1\n" \
	"addc %3,%2,%0" \
	: "=r" ((USItype)(sh)), \
	     "=&r" ((USItype)(sl)) \
	: "%dI" ((USItype)(ah)), \
	     "dI" ((USItype)(bh)), \
	     "%dI" ((USItype)(al)), \
	     "dI" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("cmpo 0,0\n" \
	"subc %5,%4,%1\n" \
	"subc %3,%2,%0" \
	: "=r" ((USItype)(sh)), \
	     "=&r" ((USItype)(sl)) \
	: "dI" ((USItype)(ah)), \
	     "dI" ((USItype)(bh)), \
	     "dI" ((USItype)(al)), \
	     "dI" ((USItype)(bl)))
#घोषणा umul_ppmm(w1, w0, u, v) \
	(अणुजोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __l, __h; पूर्ण __i; \
	पूर्ण __xx; \
	__यंत्र__ ("emul        %2,%1,%0" \
	: "=d" (__xx.__ll) \
	: "%dI" ((USItype)(u)), \
	     "dI" ((USItype)(v))); \
	(w1) = __xx.__i.__h; (w0) = __xx.__i.__l; पूर्ण)
#घोषणा __umulsidi3(u, v) \
	(अणुUDItype __w; \
	__यंत्र__ ("emul      %2,%1,%0" \
	: "=d" (__w) \
	: "%dI" ((USItype)(u)), \
	       "dI" ((USItype)(v))); \
	__w; पूर्ण)
#घोषणा uभाग_qrnnd(q, r, nh, nl, d) \
करो अणु \
	जोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __l, __h; पूर्ण __i; \
	पूर्ण __nn; \
	__nn.__i.__h = (nh); __nn.__i.__l = (nl); \
	__यंत्र__ ("ediv %d,%n,%0" \
	: "=d" (__rq.__ll) \
	: "dI" (__nn.__ll), \
	     "dI" ((USItype)(d))); \
	(r) = __rq.__i.__l; (q) = __rq.__i.__h; \
पूर्ण जबतक (0)
#अगर defined(__i960mx)		/* what is the proper symbol to test??? */
#घोषणा rshअगरt_rhlc(r, h, l, c) \
करो अणु \
	जोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __l, __h; पूर्ण __i; \
	पूर्ण __nn; \
	__nn.__i.__h = (h); __nn.__i.__l = (l); \
	__यंत्र__ ("shre %2,%1,%0" \
	: "=d" (r) : "dI" (__nn.__ll), "dI" (c)); \
पूर्ण
#पूर्ण_अगर /* i960mx */
#पूर्ण_अगर /* i960 */

/***************************************
	**************  68000	****************
	***************************************/
#अगर (defined(__mc68000__) || defined(__mc68020__) || defined(__NeXT__) || defined(mc68020)) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("add%.l %5,%1\n" \
	   "addx%.l %3,%0" \
	: "=d" ((USItype)(sh)), \
	     "=&d" ((USItype)(sl)) \
	: "%0" ((USItype)(ah)), \
	     "d" ((USItype)(bh)), \
	     "%1" ((USItype)(al)), \
	     "g" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("sub%.l %5,%1\n" \
	   "subx%.l %3,%0" \
	: "=d" ((USItype)(sh)), \
	     "=&d" ((USItype)(sl)) \
	: "0" ((USItype)(ah)), \
	     "d" ((USItype)(bh)), \
	     "1" ((USItype)(al)), \
	     "g" ((USItype)(bl)))
#अगर (defined(__mc68020__) || defined(__NeXT__) || defined(mc68020))
#घोषणा umul_ppmm(w1, w0, u, v) \
	__यंत्र__ ("mulu%.l %3,%1:%0" \
	: "=d" ((USItype)(w0)), \
	     "=d" ((USItype)(w1)) \
	: "%0" ((USItype)(u)), \
	     "dmi" ((USItype)(v)))
#घोषणा UMUL_TIME 45
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
	__यंत्र__ ("divu%.l %4,%1:%0" \
	: "=d" ((USItype)(q)), \
	     "=d" ((USItype)(r)) \
	: "0" ((USItype)(n0)), \
	     "1" ((USItype)(n1)), \
	     "dmi" ((USItype)(d)))
#घोषणा UDIV_TIME 90
#घोषणा sभाग_qrnnd(q, r, n1, n0, d) \
	__यंत्र__ ("divs%.l %4,%1:%0" \
	: "=d" ((USItype)(q)), \
	     "=d" ((USItype)(r)) \
	: "0" ((USItype)(n0)), \
	     "1" ((USItype)(n1)), \
	     "dmi" ((USItype)(d)))
#अन्यथा /* not mc68020 */
#घोषणा umul_ppmm(xh, xl, a, b) \
करो अणु USItype __umul_पंचांगp1, __umul_पंचांगp2; \
	__यंत्र__ ("| Inlined umul_ppmm\n" \
	"move%.l %5,%3\n" \
	"move%.l %2,%0\n" \
	"move%.w %3,%1\n" \
	"swap	%3\n" \
	"swap	%0\n" \
	"mulu	%2,%1\n" \
	"mulu	%3,%0\n" \
	"mulu	%2,%3\n" \
	"swap	%2\n" \
	"mulu	%5,%2\n" \
	"add%.l	%3,%2\n" \
	"jcc	1f\n" \
	"add%.l	%#0x10000,%0\n" \
	"1:	move%.l %2,%3\n" \
	"clr%.w	%2\n" \
	"swap	%2\n" \
	"swap	%3\n" \
	"clr%.w	%3\n" \
	"add%.l	%3,%1\n" \
	"addx%.l %2,%0\n" \
	"| End inlined umul_ppmm" \
	: "=&d" ((USItype)(xh)), "=&d" ((USItype)(xl)), \
		"=d" (__umul_पंचांगp1), "=&d" (__umul_पंचांगp2) \
	: "%2" ((USItype)(a)), "d" ((USItype)(b))); \
पूर्ण जबतक (0)
#घोषणा UMUL_TIME 100
#घोषणा UDIV_TIME 400
#पूर्ण_अगर /* not mc68020 */
#पूर्ण_अगर /* mc68000 */

/***************************************
	**************  88000	****************
	***************************************/
#अगर defined(__m88000__) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("addu.co %1,%r4,%r5\n" \
	   "addu.ci %0,%r2,%r3" \
	: "=r" ((USItype)(sh)), \
	     "=&r" ((USItype)(sl)) \
	: "%rJ" ((USItype)(ah)), \
	     "rJ" ((USItype)(bh)), \
	     "%rJ" ((USItype)(al)), \
	     "rJ" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("subu.co %1,%r4,%r5\n" \
	   "subu.ci %0,%r2,%r3" \
	: "=r" ((USItype)(sh)), \
	     "=&r" ((USItype)(sl)) \
	: "rJ" ((USItype)(ah)), \
	     "rJ" ((USItype)(bh)), \
	     "rJ" ((USItype)(al)), \
	     "rJ" ((USItype)(bl)))
#अगर defined(__m88110__)
#घोषणा umul_ppmm(wh, wl, u, v) \
करो अणु \
	जोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __h, __l; पूर्ण __i; \
	पूर्ण __x; \
	__यंत्र__ ("mulu.d %0,%1,%2" : "=r" (__x.__ll) : "r" (u), "r" (v)); \
	(wh) = __x.__i.__h; \
	(wl) = __x.__i.__l; \
पूर्ण जबतक (0)
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
	(अणुजोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __h, __l; पूर्ण __i; \
	पूर्ण __x, __q; \
	__x.__i.__h = (n1); __x.__i.__l = (n0); \
	__यंत्र__ ("divu.d %0,%1,%2" \
	: "=r" (__q.__ll) : "r" (__x.__ll), "r" (d)); \
	(r) = (n0) - __q.__l * (d); (q) = __q.__l; पूर्ण)
#घोषणा UMUL_TIME 5
#घोषणा UDIV_TIME 25
#अन्यथा
#घोषणा UMUL_TIME 17
#घोषणा UDIV_TIME 150
#पूर्ण_अगर /* __m88110__ */
#पूर्ण_अगर /* __m88000__ */

/***************************************
	**************  MIPS  *****************
	***************************************/
#अगर defined(__mips__) && W_TYPE_SIZE == 32
#घोषणा umul_ppmm(w1, w0, u, v)			\
करो अणु						\
	UDItype __ll = (UDItype)(u) * (v);	\
	w1 = __ll >> 32;			\
	w0 = __ll;				\
पूर्ण जबतक (0)
#घोषणा UMUL_TIME 10
#घोषणा UDIV_TIME 100
#पूर्ण_अगर /* __mips__ */

/***************************************
	**************  MIPS/64  **************
	***************************************/
#अगर (defined(__mips) && __mips >= 3) && W_TYPE_SIZE == 64
#अगर defined(__mips_isa_rev) && __mips_isa_rev >= 6 && defined(CONFIG_CC_IS_GCC)
/*
 * GCC ends up emitting a __multi3 पूर्णांकrinsic call क्रम MIPS64r6 with the plain C
 * code below, so we special हाल MIPS64r6 until the compiler can करो better.
 */
#घोषणा umul_ppmm(w1, w0, u, v)						\
करो अणु									\
	__यंत्र__ ("dmulu %0,%1,%2"					\
		 : "=d" ((UDItype)(w0))					\
		 : "d" ((UDItype)(u)),					\
		   "d" ((UDItype)(v)));					\
	__यंत्र__ ("dmuhu %0,%1,%2"					\
		 : "=d" ((UDItype)(w1))					\
		 : "d" ((UDItype)(u)),					\
		   "d" ((UDItype)(v)));					\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा umul_ppmm(w1, w0, u, v) \
करो अणु									\
	प्रकार अचिन्हित पूर्णांक __ll_UTItype __attribute__((mode(TI)));	\
	__ll_UTItype __ll = (__ll_UTItype)(u) * (v);			\
	w1 = __ll >> 64;						\
	w0 = __ll;							\
पूर्ण जबतक (0)
#पूर्ण_अगर
#घोषणा UMUL_TIME 20
#घोषणा UDIV_TIME 140
#पूर्ण_अगर /* __mips__ */

/***************************************
	**************  32000	****************
	***************************************/
#अगर defined(__ns32000__) && W_TYPE_SIZE == 32
#घोषणा umul_ppmm(w1, w0, u, v) \
	(अणुजोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __l, __h; पूर्ण __i; \
	पूर्ण __xx; \
	__यंत्र__ ("meid %2,%0" \
	: "=g" (__xx.__ll) \
	: "%0" ((USItype)(u)), \
	     "g" ((USItype)(v))); \
	(w1) = __xx.__i.__h; (w0) = __xx.__i.__l; पूर्ण)
#घोषणा __umulsidi3(u, v) \
	(अणुUDItype __w; \
	__यंत्र__ ("meid %2,%0" \
	: "=g" (__w) \
	: "%0" ((USItype)(u)), \
	       "g" ((USItype)(v))); \
	__w; पूर्ण)
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
	(अणुजोड़ अणुUDItype __ll; \
	   काष्ठा अणुUSItype __l, __h; पूर्ण __i; \
	पूर्ण __xx; \
	__xx.__i.__h = (n1); __xx.__i.__l = (n0); \
	__यंत्र__ ("deid %2,%0" \
	: "=g" (__xx.__ll) \
	: "0" (__xx.__ll), \
	     "g" ((USItype)(d))); \
	(r) = __xx.__i.__l; (q) = __xx.__i.__h; पूर्ण)
#पूर्ण_अगर /* __ns32000__ */

/***************************************
	**************  PPC  ******************
	***************************************/
#अगर (defined(_ARCH_PPC) || defined(_IBMR2)) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
करो अणु \
	अगर (__builtin_स्थिरant_p(bh) && (bh) == 0) \
		__यंत्र__ ("{a%I4|add%I4c} %1,%3,%4\n\t{aze|addze} %0,%2" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "%r" ((USItype)(ah)), \
		"%r" ((USItype)(al)), \
		"rI" ((USItype)(bl))); \
	अन्यथा अगर (__builtin_स्थिरant_p(bh) && (bh) == ~(USItype) 0) \
		__यंत्र__ ("{a%I4|add%I4c} %1,%3,%4\n\t{ame|addme} %0,%2" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "%r" ((USItype)(ah)), \
		"%r" ((USItype)(al)), \
		"rI" ((USItype)(bl))); \
	अन्यथा \
		__यंत्र__ ("{a%I5|add%I5c} %1,%4,%5\n\t{ae|adde} %0,%2,%3" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "%r" ((USItype)(ah)), \
		"r" ((USItype)(bh)), \
		"%r" ((USItype)(al)), \
		"rI" ((USItype)(bl))); \
पूर्ण जबतक (0)
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
करो अणु \
	अगर (__builtin_स्थिरant_p(ah) && (ah) == 0) \
		__यंत्र__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{sfze|subfze} %0,%2" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "r" ((USItype)(bh)), \
		"rI" ((USItype)(al)), \
		"r" ((USItype)(bl))); \
	अन्यथा अगर (__builtin_स्थिरant_p(ah) && (ah) == ~(USItype) 0) \
		__यंत्र__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{sfme|subfme} %0,%2" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "r" ((USItype)(bh)), \
		"rI" ((USItype)(al)), \
		"r" ((USItype)(bl))); \
	अन्यथा अगर (__builtin_स्थिरant_p(bh) && (bh) == 0) \
		__यंत्र__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{ame|addme} %0,%2" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "r" ((USItype)(ah)), \
		"rI" ((USItype)(al)), \
		"r" ((USItype)(bl))); \
	अन्यथा अगर (__builtin_स्थिरant_p(bh) && (bh) == ~(USItype) 0) \
		__यंत्र__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{aze|addze} %0,%2" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "r" ((USItype)(ah)), \
		"rI" ((USItype)(al)), \
		"r" ((USItype)(bl))); \
	अन्यथा \
		__यंत्र__ ("{sf%I4|subf%I4c} %1,%5,%4\n\t{sfe|subfe} %0,%3,%2" \
		: "=r" (sh), \
		"=&r" (sl) \
		: "r" ((USItype)(ah)), \
		"r" ((USItype)(bh)), \
		"rI" ((USItype)(al)), \
		"r" ((USItype)(bl))); \
पूर्ण जबतक (0)
#अगर defined(_ARCH_PPC)
#घोषणा umul_ppmm(ph, pl, m0, m1) \
करो अणु \
	USItype __m0 = (m0), __m1 = (m1); \
	__यंत्र__ ("mulhwu %0,%1,%2" \
	: "=r" (ph) \
	: "%r" (__m0), \
	"r" (__m1)); \
	(pl) = __m0 * __m1; \
पूर्ण जबतक (0)
#घोषणा UMUL_TIME 15
#घोषणा smul_ppmm(ph, pl, m0, m1) \
करो अणु \
	SItype __m0 = (m0), __m1 = (m1); \
	__यंत्र__ ("mulhw %0,%1,%2" \
	: "=r" ((SItype) ph) \
	: "%r" (__m0), \
	"r" (__m1)); \
	(pl) = __m0 * __m1; \
पूर्ण जबतक (0)
#घोषणा SMUL_TIME 14
#घोषणा UDIV_TIME 120
#अन्यथा
#घोषणा umul_ppmm(xh, xl, m0, m1) \
करो अणु \
	USItype __m0 = (m0), __m1 = (m1); \
	__यंत्र__ ("mul %0,%2,%3" \
	: "=r" ((USItype)(xh)), \
	"=q" ((USItype)(xl)) \
	: "r" (__m0), \
	"r" (__m1)); \
	(xh) += ((((SItype) __m0 >> 31) & __m1) \
	+ (((SItype) __m1 >> 31) & __m0)); \
पूर्ण जबतक (0)
#घोषणा UMUL_TIME 8
#घोषणा smul_ppmm(xh, xl, m0, m1) \
	__यंत्र__ ("mul %0,%2,%3" \
	: "=r" ((SItype)(xh)), \
	"=q" ((SItype)(xl)) \
	: "r" (m0), \
	"r" (m1))
#घोषणा SMUL_TIME 4
#घोषणा sभाग_qrnnd(q, r, nh, nl, d) \
	__यंत्र__ ("div %0,%2,%4" \
	: "=r" ((SItype)(q)), "=q" ((SItype)(r)) \
	: "r" ((SItype)(nh)), "1" ((SItype)(nl)), "r" ((SItype)(d)))
#घोषणा UDIV_TIME 100
#पूर्ण_अगर
#पूर्ण_अगर /* Power architecture variants.  */

/***************************************
	**************  PYR  ******************
	***************************************/
#अगर defined(__pyr__) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("addw        %5,%1\n" \
	"addwc	%3,%0" \
	: "=r" ((USItype)(sh)), \
	"=&r" ((USItype)(sl)) \
	: "%0" ((USItype)(ah)), \
	"g" ((USItype)(bh)), \
	"%1" ((USItype)(al)), \
	"g" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("subw        %5,%1\n" \
	"subwb	%3,%0" \
	: "=r" ((USItype)(sh)), \
	"=&r" ((USItype)(sl)) \
	: "0" ((USItype)(ah)), \
	"g" ((USItype)(bh)), \
	"1" ((USItype)(al)), \
	"g" ((USItype)(bl)))
	/* This insn works on Pyramids with AP, XP, or MI CPUs, but not with SP.  */
#घोषणा umul_ppmm(w1, w0, u, v) \
	(अणुजोड़ अणुUDItype __ll; \
	काष्ठा अणुUSItype __h, __l; पूर्ण __i; \
	पूर्ण __xx; \
	__यंत्र__ ("movw %1,%R0\n" \
	"uemul %2,%0" \
	: "=&r" (__xx.__ll) \
	: "g" ((USItype) (u)), \
	"g" ((USItype)(v))); \
	(w1) = __xx.__i.__h; (w0) = __xx.__i.__l; पूर्ण)
#पूर्ण_अगर /* __pyr__ */

/***************************************
	**************  RT/ROMP  **************
	***************************************/
#अगर defined(__ibm032__) /* RT/ROMP */	&& W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("a %1,%5\n" \
	"ae %0,%3" \
	: "=r" ((USItype)(sh)), \
	"=&r" ((USItype)(sl)) \
	: "%0" ((USItype)(ah)), \
	"r" ((USItype)(bh)), \
	"%1" ((USItype)(al)), \
	"r" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("s %1,%5\n" \
	"se %0,%3" \
	: "=r" ((USItype)(sh)), \
	"=&r" ((USItype)(sl)) \
	: "0" ((USItype)(ah)), \
	"r" ((USItype)(bh)), \
	"1" ((USItype)(al)), \
	"r" ((USItype)(bl)))
#घोषणा umul_ppmm(ph, pl, m0, m1) \
करो अणु \
	USItype __m0 = (m0), __m1 = (m1); \
	__यंत्र__ ( \
	"s       r2,r2\n" \
	"mts	r10,%2\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"m	r2,%3\n" \
	"cas	%0,r2,r0\n" \
	"mfs	r10,%1" \
	: "=r" ((USItype)(ph)), \
	"=r" ((USItype)(pl)) \
	: "%r" (__m0), \
	"r" (__m1) \
	: "r2"); \
	(ph) += ((((SItype) __m0 >> 31) & __m1) \
	+ (((SItype) __m1 >> 31) & __m0)); \
पूर्ण जबतक (0)
#घोषणा UMUL_TIME 20
#घोषणा UDIV_TIME 200
#पूर्ण_अगर /* RT/ROMP */

/***************************************
	**************  SH2  ******************
	***************************************/
#अगर (defined(__sh2__) || defined(__sh3__) || defined(__SH4__)) \
	&& W_TYPE_SIZE == 32
#घोषणा umul_ppmm(w1, w0, u, v) \
	__यंत्र__ ( \
	"dmulu.l %2,%3\n" \
	"sts	macl,%1\n" \
	"sts	mach,%0" \
	: "=r" ((USItype)(w1)), \
	"=r" ((USItype)(w0)) \
	: "r" ((USItype)(u)), \
	"r" ((USItype)(v)) \
	: "macl", "mach")
#घोषणा UMUL_TIME 5
#पूर्ण_अगर

/***************************************
	**************  SPARC	****************
	***************************************/
#अगर defined(__sparc__) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("addcc %r4,%5,%1\n" \
	"addx %r2,%3,%0" \
	: "=r" ((USItype)(sh)), \
	"=&r" ((USItype)(sl)) \
	: "%rJ" ((USItype)(ah)), \
	"rI" ((USItype)(bh)), \
	"%rJ" ((USItype)(al)), \
	"rI" ((USItype)(bl)) \
	__CLOBBER_CC)
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("subcc %r4,%5,%1\n" \
	"subx %r2,%3,%0" \
	: "=r" ((USItype)(sh)), \
	"=&r" ((USItype)(sl)) \
	: "rJ" ((USItype)(ah)), \
	"rI" ((USItype)(bh)), \
	"rJ" ((USItype)(al)), \
	"rI" ((USItype)(bl)) \
	__CLOBBER_CC)
#अगर defined(__sparc_v8__)
/* Don't match immediate range because, 1) it is not often useful,
	2) the 'I' flag thinks of the range as a 13 bit चिन्हित पूर्णांकerval,
	जबतक we want to match a 13 bit पूर्णांकerval, sign extended to 32 bits,
	but INTERPRETED AS UNSIGNED.  */
#घोषणा umul_ppmm(w1, w0, u, v) \
	__यंत्र__ ("umul %2,%3,%1;rd %%y,%0" \
	: "=r" ((USItype)(w1)), \
	"=r" ((USItype)(w0)) \
	: "r" ((USItype)(u)), \
	"r" ((USItype)(v)))
#घोषणा UMUL_TIME 5
#अगर_अघोषित SUPERSPARC		/* SuperSPARC's uभाग only handles 53 bit भागidends */
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
करो अणु \
	USItype __q; \
	__यंत्र__ ("mov %1,%%y;nop;nop;nop;udiv %2,%3,%0" \
	: "=r" ((USItype)(__q)) \
	: "r" ((USItype)(n1)), \
	"r" ((USItype)(n0)), \
	"r" ((USItype)(d))); \
	(r) = (n0) - __q * (d); \
	(q) = __q; \
पूर्ण जबतक (0)
#घोषणा UDIV_TIME 25
#पूर्ण_अगर /* SUPERSPARC */
#अन्यथा /* ! __sparc_v8__ */
#अगर defined(__sparclite__)
/* This has hardware multiply but not भागide.  It also has two additional
	inकाष्ठाions scan (ffs from high bit) and भागscc.  */
#घोषणा umul_ppmm(w1, w0, u, v) \
	__यंत्र__ ("umul %2,%3,%1;rd %%y,%0" \
	: "=r" ((USItype)(w1)), \
	"=r" ((USItype)(w0)) \
	: "r" ((USItype)(u)), \
	"r" ((USItype)(v)))
#घोषणा UMUL_TIME 5
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
	__यंत्र__ ("! Inlined udiv_qrnnd\n" \
	"wr	%%g0,%2,%%y	! Not a delayed write for sparclite\n" \
	"tst	%%g0\n" \
	"divscc	%3,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%%g1\n" \
	"divscc	%%g1,%4,%0\n" \
	"rd	%%y,%1\n" \
	"bl,a 1f\n" \
	"add	%1,%4,%1\n" \
	"1:	! End of inline udiv_qrnnd" \
	: "=r" ((USItype)(q)), \
	"=r" ((USItype)(r)) \
	: "r" ((USItype)(n1)), \
	"r" ((USItype)(n0)), \
	"rI" ((USItype)(d)) \
	: "%g1" __AND_CLOBBER_CC)
#घोषणा UDIV_TIME 37
#पूर्ण_अगर /* __sparclite__ */
#पूर्ण_अगर /* __sparc_v8__ */
	/* Default to sparc v7 versions of umul_ppmm and uभाग_qrnnd.  */
#अगर_अघोषित umul_ppmm
#घोषणा umul_ppmm(w1, w0, u, v) \
	__यंत्र__ ("! Inlined umul_ppmm\n" \
	"wr	%%g0,%2,%%y	! SPARC has 0-3 delay insn after a wr\n" \
	"sra	%3,31,%%g2	! Don't move this insn\n" \
	"and	%2,%%g2,%%g2	! Don't move this insn\n" \
	"andcc	%%g0,0,%%g1	! Don't move this insn\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,%3,%%g1\n" \
	"mulscc	%%g1,0,%%g1\n" \
	"add	%%g1,%%g2,%0\n" \
	"rd	%%y,%1" \
	: "=r" ((USItype)(w1)), \
	"=r" ((USItype)(w0)) \
	: "%rI" ((USItype)(u)), \
	"r" ((USItype)(v)) \
	: "%g1", "%g2" __AND_CLOBBER_CC)
#घोषणा UMUL_TIME 39		/* 39 inकाष्ठाions */
/* It's quite necessary to add this much assembler क्रम the sparc.
   The शेष uभाग_qrnnd (in C) is more than 10 बार slower!  */
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
  __यंत्र__ ("! Inlined udiv_qrnnd\n\t"					\
	   "mov	32,%%g1\n\t"						\
	   "subcc	%1,%2,%%g0\n\t"					\
	   "1:	bcs	5f\n\t"						\
	   "addxcc %0,%0,%0	! shift n1n0 and a q-bit in lsb\n\t"	\
	   "sub	%1,%2,%1	! this kills msb of n\n\t"		\
	   "addx	%1,%1,%1	! so this can't give carry\n\t"	\
	   "subcc	%%g1,1,%%g1\n\t"				\
	   "2:	bne	1b\n\t"						\
	   "subcc	%1,%2,%%g0\n\t"					\
	   "bcs	3f\n\t"							\
	   "addxcc %0,%0,%0	! shift n1n0 and a q-bit in lsb\n\t"	\
	   "b		3f\n\t"						\
	   "sub	%1,%2,%1	! this kills msb of n\n\t"		\
	   "4:	sub	%1,%2,%1\n\t"					\
	   "5:	addxcc	%1,%1,%1\n\t"					\
	   "bcc	2b\n\t"							\
	   "subcc	%%g1,1,%%g1\n\t"				\
	   "! Got carry from n.  Subtract next step to cancel this carry.\n\t" \
	   "bne	4b\n\t"							\
	   "addcc	%0,%0,%0	! shift n1n0 and a 0-bit in lsb\n\t" \
	   "sub	%1,%2,%1\n\t"						\
	   "3:	xnor	%0,0,%0\n\t"					\
	   "! End of inline udiv_qrnnd\n"				\
	   : "=&r" ((USItype)(q)),					\
	     "=&r" ((USItype)(r))					\
	   : "r" ((USItype)(d)),					\
	     "1" ((USItype)(n1)),					\
	     "0" ((USItype)(n0)) : "%g1", "cc")
#घोषणा UDIV_TIME (3+7*32)      /* 7 inकाष्ठाions/iteration. 32 iterations.  */
#पूर्ण_अगर
#पूर्ण_अगर /* __sparc__ */

/***************************************
	**************  VAX  ******************
	***************************************/
#अगर defined(__vax__) && W_TYPE_SIZE == 32
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("addl2 %5,%1\n" \
	"adwc %3,%0" \
	: "=g" ((USItype)(sh)), \
	"=&g" ((USItype)(sl)) \
	: "%0" ((USItype)(ah)), \
	"g" ((USItype)(bh)), \
	"%1" ((USItype)(al)), \
	"g" ((USItype)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("subl2 %5,%1\n" \
	"sbwc %3,%0" \
	: "=g" ((USItype)(sh)), \
	"=&g" ((USItype)(sl)) \
	: "0" ((USItype)(ah)), \
	"g" ((USItype)(bh)), \
	"1" ((USItype)(al)), \
	"g" ((USItype)(bl)))
#घोषणा umul_ppmm(xh, xl, m0, m1) \
करो अणु \
	जोड़ अणुUDItype __ll; \
	काष्ठा अणुUSItype __l, __h; पूर्ण __i; \
	पूर्ण __xx; \
	USItype __m0 = (m0), __m1 = (m1); \
	__यंत्र__ ("emul %1,%2,$0,%0" \
	: "=g" (__xx.__ll) \
	: "g" (__m0), \
	"g" (__m1)); \
	(xh) = __xx.__i.__h; (xl) = __xx.__i.__l; \
	(xh) += ((((SItype) __m0 >> 31) & __m1) \
	+ (((SItype) __m1 >> 31) & __m0)); \
पूर्ण जबतक (0)
#घोषणा sभाग_qrnnd(q, r, n1, n0, d) \
करो अणु \
	जोड़ अणुDItype __ll; \
	काष्ठा अणुSItype __l, __h; पूर्ण __i; \
	पूर्ण __xx; \
	__xx.__i.__h = n1; __xx.__i.__l = n0; \
	__यंत्र__ ("ediv %3,%2,%0,%1" \
	: "=g" (q), "=g" (r) \
	: "g" (__xx.__ll), "g" (d)); \
पूर्ण जबतक (0)
#पूर्ण_अगर /* __vax__ */

/***************************************
	**************  Z8000	****************
	***************************************/
#अगर defined(__z8000__) && W_TYPE_SIZE == 16
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("add %H1,%H5\n\tadc  %H0,%H3" \
	: "=r" ((अचिन्हित पूर्णांक)(sh)), \
	"=&r" ((अचिन्हित पूर्णांक)(sl)) \
	: "%0" ((अचिन्हित पूर्णांक)(ah)), \
	"r" ((अचिन्हित पूर्णांक)(bh)), \
	"%1" ((अचिन्हित पूर्णांक)(al)), \
	"rQR" ((अचिन्हित पूर्णांक)(bl)))
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
	__यंत्र__ ("sub %H1,%H5\n\tsbc  %H0,%H3" \
	: "=r" ((अचिन्हित पूर्णांक)(sh)), \
	"=&r" ((अचिन्हित पूर्णांक)(sl)) \
	: "0" ((अचिन्हित पूर्णांक)(ah)), \
	"r" ((अचिन्हित पूर्णांक)(bh)), \
	"1" ((अचिन्हित पूर्णांक)(al)), \
	"rQR" ((अचिन्हित पूर्णांक)(bl)))
#घोषणा umul_ppmm(xh, xl, m0, m1) \
करो अणु \
	जोड़ अणुदीर्घ पूर्णांक __ll; \
	काष्ठा अणुअचिन्हित पूर्णांक __h, __l; पूर्ण __i; \
	पूर्ण __xx; \
	अचिन्हित पूर्णांक __m0 = (m0), __m1 = (m1); \
	__यंत्र__ ("mult      %S0,%H3" \
	: "=r" (__xx.__i.__h), \
	"=r" (__xx.__i.__l) \
	: "%1" (__m0), \
	"rQR" (__m1)); \
	(xh) = __xx.__i.__h; (xl) = __xx.__i.__l; \
	(xh) += ((((चिन्हित पूर्णांक) __m0 >> 15) & __m1) \
	+ (((चिन्हित पूर्णांक) __m1 >> 15) & __m0)); \
पूर्ण जबतक (0)
#पूर्ण_अगर /* __z8000__ */

#पूर्ण_अगर /* __GNUC__ */

/***************************************
	***********  Generic Versions	********
	***************************************/
#अगर !defined(umul_ppmm) && defined(__umulsidi3)
#घोषणा umul_ppmm(ph, pl, m0, m1) \
अणु \
	UDWtype __ll = __umulsidi3(m0, m1); \
	ph = (UWtype) (__ll >> W_TYPE_SIZE); \
	pl = (UWtype) __ll; \
पूर्ण
#पूर्ण_अगर

#अगर !defined(__umulsidi3)
#घोषणा __umulsidi3(u, v) \
	(अणुUWtype __hi, __lo; \
	umul_ppmm(__hi, __lo, u, v); \
	((UDWtype) __hi << W_TYPE_SIZE) | __lo; पूर्ण)
#पूर्ण_अगर

	/* If this machine has no अंतरभूत assembler, use C macros.  */

#अगर !defined(add_ssaaaa)
#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
करो अणु \
	UWtype __x; \
	__x = (al) + (bl); \
	(sh) = (ah) + (bh) + (__x < (al)); \
	(sl) = __x; \
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर !defined(sub_ddmmss)
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
करो अणु \
	UWtype __x; \
	__x = (al) - (bl); \
	(sh) = (ah) - (bh) - (__x > (al)); \
	(sl) = __x; \
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर !defined(umul_ppmm)
#घोषणा umul_ppmm(w1, w0, u, v) \
करो अणु \
	UWtype __x0, __x1, __x2, __x3; \
	UHWtype __ul, __vl, __uh, __vh; \
	UWtype __u = (u), __v = (v); \
	\
	__ul = __ll_lowpart(__u); \
	__uh = __ll_highpart(__u); \
	__vl = __ll_lowpart(__v); \
	__vh = __ll_highpart(__v); \
	\
	__x0 = (UWtype) __ul * __vl; \
	__x1 = (UWtype) __ul * __vh; \
	__x2 = (UWtype) __uh * __vl; \
	__x3 = (UWtype) __uh * __vh; \
	\
	__x1 += __ll_highpart(__x0);/* this can't give carry */ \
	__x1 += __x2;		/* but this indeed can */ \
	अगर (__x1 < __x2)		/* did we get it? */ \
	__x3 += __ll_B;		/* yes, add it in the proper pos. */ \
	\
	(w1) = __x3 + __ll_highpart(__x1); \
	(w0) = (__ll_lowpart(__x1) << W_TYPE_SIZE/2) + __ll_lowpart(__x0); \
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर !defined(umul_ppmm)
#घोषणा smul_ppmm(w1, w0, u, v) \
करो अणु \
	UWtype __w1; \
	UWtype __m0 = (u), __m1 = (v); \
	umul_ppmm(__w1, w0, __m0, __m1); \
	(w1) = __w1 - (-(__m0 >> (W_TYPE_SIZE - 1)) & __m1) \
	- (-(__m1 >> (W_TYPE_SIZE - 1)) & __m0); \
पूर्ण जबतक (0)
#पूर्ण_अगर

	/* Define this unconditionally, so it can be used क्रम debugging.  */
#घोषणा __uभाग_qrnnd_c(q, r, n1, n0, d) \
करो अणु \
	UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m; \
	__d1 = __ll_highpart(d); \
	__d0 = __ll_lowpart(d); \
	\
	__r1 = (n1) % __d1; \
	__q1 = (n1) / __d1; \
	__m = (UWtype) __q1 * __d0; \
	__r1 = __r1 * __ll_B | __ll_highpart(n0); \
	अगर (__r1 < __m) अणु \
		__q1--, __r1 += (d); \
		अगर (__r1 >= (d)) /* i.e. we didn't get carry when adding to __r1 */ \
		अगर (__r1 < __m) \
			__q1--, __r1 += (d); \
	पूर्ण \
	__r1 -= __m; \
	\
	__r0 = __r1 % __d1; \
	__q0 = __r1 / __d1; \
	__m = (UWtype) __q0 * __d0; \
	__r0 = __r0 * __ll_B | __ll_lowpart(n0); \
	अगर (__r0 < __m) अणु \
		__q0--, __r0 += (d); \
		अगर (__r0 >= (d)) \
			अगर (__r0 < __m) \
				__q0--, __r0 += (d); \
	पूर्ण \
	__r0 -= __m; \
	\
	(q) = (UWtype) __q1 * __ll_B | __q0; \
	(r) = __r0; \
पूर्ण जबतक (0)

/* If the processor has no uभाग_qrnnd but sभाग_qrnnd, go through
	__uभाग_w_sभाग (defined in libgcc or अन्यथाwhere).  */
#अगर !defined(uभाग_qrnnd) && defined(sभाग_qrnnd)
#घोषणा uभाग_qrnnd(q, r, nh, nl, d) \
करो अणु \
	UWtype __r; \
	(q) = __MPN(uभाग_w_sभाग) (&__r, nh, nl, d); \
	(r) = __r; \
पूर्ण जबतक (0)
#पूर्ण_अगर

	/* If uभाग_qrnnd was not defined क्रम this processor, use __uभाग_qrnnd_c.  */
#अगर !defined(uभाग_qrnnd)
#घोषणा UDIV_NEEDS_NORMALIZATION 1
#घोषणा uभाग_qrnnd __uभाग_qrnnd_c
#पूर्ण_अगर

#अगर_अघोषित UDIV_NEEDS_NORMALIZATION
#घोषणा UDIV_NEEDS_NORMALIZATION 0
#पूर्ण_अगर
