<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Riअक्षरd Henderson (rth@cygnus.com),
		  Jakub Jelinek (jj@ultra.linux.cz),
		  David S. Miller (davem@redhat.com) and
		  Peter Maydell (pmaydell@chiark.greenend.org.uk).

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
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#अगर_अघोषित __MATH_EMU_SOFT_FP_H__
#घोषणा __MATH_EMU_SOFT_FP_H__

#समावेश <यंत्र/sfp-machine.h>

/* Allow sfp-machine to have its own byte order definitions. */
#अगर_अघोषित __BYTE_ORDER
#समावेश <endian.h>
#पूर्ण_अगर

#घोषणा _FP_WORKBITS		3
#घोषणा _FP_WORK_LSB		((_FP_W_TYPE)1 << 3)
#घोषणा _FP_WORK_ROUND		((_FP_W_TYPE)1 << 2)
#घोषणा _FP_WORK_GUARD		((_FP_W_TYPE)1 << 1)
#घोषणा _FP_WORK_STICKY		((_FP_W_TYPE)1 << 0)

#अगर_अघोषित FP_RND_NEAREST
# define FP_RND_NEAREST		0
# define FP_RND_ZERO		1
# define FP_RND_PINF		2
# define FP_RND_MINF		3
#अगर_अघोषित FP_ROUNDMODE
# define FP_ROUNDMODE		FP_RND_NEAREST
#पूर्ण_अगर
#पूर्ण_अगर

/* By शेष करोn't care about exceptions. */
#अगर_अघोषित FP_EX_INVALID
#घोषणा FP_EX_INVALID		0
#पूर्ण_अगर
#अगर_अघोषित FP_EX_INVALID_Sन_अंक
#घोषणा FP_EX_INVALID_Sन_अंक	0
#पूर्ण_अगर
/* inf - inf */
#अगर_अघोषित FP_EX_INVALID_ISI
#घोषणा FP_EX_INVALID_ISI	0
#पूर्ण_अगर
/* inf / inf */
#अगर_अघोषित FP_EX_INVALID_IDI
#घोषणा FP_EX_INVALID_IDI	0
#पूर्ण_अगर
/* 0 / 0 */
#अगर_अघोषित FP_EX_INVALID_ZDZ
#घोषणा FP_EX_INVALID_ZDZ	0
#पूर्ण_अगर
/* inf * 0 */
#अगर_अघोषित FP_EX_INVALID_IMZ
#घोषणा FP_EX_INVALID_IMZ	0
#पूर्ण_अगर
#अगर_अघोषित FP_EX_OVERFLOW
#घोषणा FP_EX_OVERFLOW		0
#पूर्ण_अगर
#अगर_अघोषित FP_EX_UNDERFLOW
#घोषणा FP_EX_UNDERFLOW		
#पूर्ण_अगर
#अगर_अघोषित FP_EX_DIVZERO
#घोषणा FP_EX_DIVZERO		0
#पूर्ण_अगर
#अगर_अघोषित FP_EX_INEXACT
#घोषणा FP_EX_INEXACT		0
#पूर्ण_अगर
#अगर_अघोषित FP_EX_DENORM
#घोषणा FP_EX_DENORM		0
#पूर्ण_अगर

#अगर_घोषित _FP_DECL_EX
#घोषणा FP_DECL_EX					\
  पूर्णांक _fex = 0;						\
  _FP_DECL_EX
#अन्यथा
#घोषणा FP_DECL_EX पूर्णांक _fex = 0
#पूर्ण_अगर
  
#अगर_अघोषित FP_INIT_ROUNDMODE
#घोषणा FP_INIT_ROUNDMODE करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित FP_HANDLE_EXCEPTIONS
#घोषणा FP_HANDLE_EXCEPTIONS करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* By शेष we never flush denormal input opeअक्रमs to चिन्हित zero. */
#अगर_अघोषित FP_DENORM_ZERO
#घोषणा FP_DENORM_ZERO 0
#पूर्ण_अगर

#अगर_अघोषित FP_INHIBIT_RESULTS
/* By शेष we ग_लिखो the results always.
 * sfp-machine may override this and e.g.
 * check अगर some exceptions are unmasked
 * and inhibit it in such a हाल.
 */
#घोषणा FP_INHIBIT_RESULTS 0
#पूर्ण_अगर

#अगर_अघोषित FP_TRAPPING_EXCEPTIONS
#घोषणा FP_TRAPPING_EXCEPTIONS 0
#पूर्ण_अगर

#घोषणा FP_SET_EXCEPTION(ex)				\
  _fex |= (ex)
  
#घोषणा FP_UNSET_EXCEPTION(ex)				\
  _fex &= ~(ex)

#घोषणा FP_CUR_EXCEPTIONS				\
  (_fex)

#घोषणा FP_CLEAR_EXCEPTIONS				\
  _fex = 0

#घोषणा _FP_ROUND_NEAREST(wc, X)			\
करो अणु							\
    अगर ((_FP_FRAC_LOW_##wc(X) & 15) != _FP_WORK_ROUND)	\
      _FP_FRAC_ADDI_##wc(X, _FP_WORK_ROUND);		\
पूर्ण जबतक (0)

#घोषणा _FP_ROUND_ZERO(wc, X)		(व्योम)0

#घोषणा _FP_ROUND_PINF(wc, X)				\
करो अणु							\
    अगर (!X##_s && (_FP_FRAC_LOW_##wc(X) & 7))		\
      _FP_FRAC_ADDI_##wc(X, _FP_WORK_LSB);		\
पूर्ण जबतक (0)

#घोषणा _FP_ROUND_MINF(wc, X)				\
करो अणु							\
    अगर (X##_s && (_FP_FRAC_LOW_##wc(X) & 7))		\
      _FP_FRAC_ADDI_##wc(X, _FP_WORK_LSB);		\
पूर्ण जबतक (0)

#घोषणा _FP_ROUND(wc, X)			\
करो अणु						\
	अगर (_FP_FRAC_LOW_##wc(X) & 7)		\
	  FP_SET_EXCEPTION(FP_EX_INEXACT);	\
	चयन (FP_ROUNDMODE)			\
	अणु					\
	  हाल FP_RND_NEAREST:			\
	    _FP_ROUND_NEAREST(wc,X);		\
	    अवरोध;				\
	  हाल FP_RND_ZERO:			\
	    _FP_ROUND_ZERO(wc,X);		\
	    अवरोध;				\
	  हाल FP_RND_PINF:			\
	    _FP_ROUND_PINF(wc,X);		\
	    अवरोध;				\
	  हाल FP_RND_MINF:			\
	    _FP_ROUND_MINF(wc,X);		\
	    अवरोध;				\
	पूर्ण					\
पूर्ण जबतक (0)

#घोषणा FP_CLS_NORMAL		0
#घोषणा FP_CLS_ZERO		1
#घोषणा FP_CLS_INF		2
#घोषणा FP_CLS_न_अंक		3

#घोषणा _FP_CLS_COMBINE(x,y)	(((x) << 2) | (y))

#समावेश <math-emu/op-1.h>
#समावेश <math-emu/op-2.h>
#समावेश <math-emu/op-4.h>
#समावेश <math-emu/op-8.h>
#समावेश <math-emu/op-common.h>

/* Sigh.  Silly things दीर्घदीर्घ.h needs.  */
#घोषणा UWtype		_FP_W_TYPE
#घोषणा W_TYPE_SIZE	_FP_W_TYPE_SIZE

प्रकार पूर्णांक SItype __attribute__((mode(SI)));
प्रकार पूर्णांक DItype __attribute__((mode(DI)));
प्रकार अचिन्हित पूर्णांक USItype __attribute__((mode(SI)));
प्रकार अचिन्हित पूर्णांक UDItype __attribute__((mode(DI)));
#अगर _FP_W_TYPE_SIZE == 32
प्रकार अचिन्हित पूर्णांक UHWtype __attribute__((mode(HI)));
#या_अगर _FP_W_TYPE_SIZE == 64
प्रकार USItype UHWtype;
#पूर्ण_अगर

#अगर_अघोषित umul_ppmm
#समावेश <stdlib/दीर्घदीर्घ.h>
#पूर्ण_अगर

#पूर्ण_अगर /* __MATH_EMU_SOFT_FP_H__ */
