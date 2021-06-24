<शैली गुरु>
/*
 * fp_emu.h
 *
 * Copyright Roman Zippel, 1997.  All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote
 *    products derived from this software without specअगरic prior
 *    written permission.
 *
 * ALTERNATIVELY, this product may be distributed under the terms of
 * the GNU General Public License, in which हाल the provisions of the GPL are
 * required INSTEAD OF the above restrictions.  (This clause is
 * necessary due to a potential bad पूर्णांकeraction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _FP_EMU_H
#घोषणा _FP_EMU_H

#अगर_घोषित __ASSEMBLY__
#समावेश <यंत्र/यंत्र-offsets.h>
#पूर्ण_अगर
#समावेश <यंत्र/math-emu.h>

#अगर_अघोषित __ASSEMBLY__

#घोषणा IS_INF(a) ((a)->exp == 0x7fff)
#घोषणा IS_ZERO(a) ((a)->mant.m64 == 0)


#घोषणा fp_set_sr(bit) (अणु					\
	FPDATA->fpsr |= 1 << (bit);				\
पूर्ण)

#घोषणा fp_set_quotient(quotient) (अणु				\
	FPDATA->fpsr &= 0xff00ffff;				\
	FPDATA->fpsr |= ((quotient) & 0xff) << 16;		\
पूर्ण)

/* linkage क्रम several useful functions */

/* Normalize the extended काष्ठा, वापस 0 क्रम a NaN */
#घोषणा fp_normalize_ext(fpreg) (अणु				\
	रेजिस्टर काष्ठा fp_ext *reg यंत्र ("a0") = fpreg;		\
	रेजिस्टर पूर्णांक res यंत्र ("d0");				\
								\
	यंत्र अस्थिर ("jsr fp_conv_ext2ext"			\
			: "=d" (res) : "a" (reg)		\
			: "a1", "d1", "d2", "memory");		\
	res;							\
पूर्ण)

#घोषणा fp_copy_ext(dest, src) (अणु				\
	*dest = *src;						\
पूर्ण)

#घोषणा fp_monadic_check(dest, src) (अणु				\
	fp_copy_ext(dest, src);					\
	अगर (!fp_normalize_ext(dest))				\
		वापस dest;					\
पूर्ण)

#घोषणा fp_dyadic_check(dest, src) (अणु				\
	अगर (!fp_normalize_ext(dest))				\
		वापस dest;					\
	अगर (!fp_normalize_ext(src)) अणु				\
		fp_copy_ext(dest, src);				\
		वापस dest;					\
	पूर्ण							\
पूर्ण)

बाह्य स्थिर काष्ठा fp_ext fp_QNaN;
बाह्य स्थिर काष्ठा fp_ext fp_Inf;

#घोषणा fp_set_nan(dest) (अणु					\
	fp_set_sr(FPSR_EXC_OPERR);				\
	*dest = fp_QNaN;					\
पूर्ण)

/* TODO check rounding mode? */
#घोषणा fp_set_ovrflw(dest) (अणु					\
	fp_set_sr(FPSR_EXC_OVFL);				\
	dest->exp = 0x7fff;					\
	dest->mant.m64 = 0;					\
पूर्ण)

#घोषणा fp_conv_ext2दीर्घ(src) (अणु				\
	रेजिस्टर काष्ठा fp_ext *__src यंत्र ("a0") = src;		\
	रेजिस्टर पूर्णांक __res यंत्र ("d0");				\
								\
	यंत्र अस्थिर ("jsr fp_conv_ext2long"			\
			: "=d" (__res) : "a" (__src)		\
			: "a1", "d1", "d2", "memory");		\
	__res;							\
पूर्ण)

#घोषणा fp_conv_दीर्घ2ext(dest, src) (अणु				\
	रेजिस्टर काष्ठा fp_ext *__dest यंत्र ("a0") = dest;	\
	रेजिस्टर पूर्णांक __src यंत्र ("d0") = src;			\
								\
	यंत्र अस्थिर ("jsr fp_conv_ext2long"			\
			: : "d" (__src), "a" (__dest)		\
			: "a1", "d1", "d2", "memory");		\
पूर्ण)

#अन्यथा /* __ASSEMBLY__ */

/*
 * set, reset or clear a bit in the fp status रेजिस्टर
 */
.macro	fp_set_sr	bit
	bset	#(\मit&7),(FPD_FPSR+3-(\मit/8),FPDATA)
.endm

.macro	fp_clr_sr	bit
	bclr	#(\मit&7),(FPD_FPSR+3-(\मit/8),FPDATA)
.endm

.macro	fp_tst_sr	bit
	btst	#(\मit&7),(FPD_FPSR+3-(\मit/8),FPDATA)
.endm

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _FP_EMU_H */
