<शैली गुरु>
/* Machine-dependent software भग्नing-poपूर्णांक definitions.
   Alpha kernel version.
   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Riअक्षरd Henderson (rth@cygnus.com),
		  Jakub Jelinek (jakub@redhat.com) and
		  David S. Miller (davem@redhat.com).

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

#अगर_अघोषित _SFP_MACHINE_H
#घोषणा _SFP_MACHINE_H
   
#घोषणा _FP_W_TYPE_SIZE		64
#घोषणा _FP_W_TYPE		अचिन्हित दीर्घ
#घोषणा _FP_WS_TYPE		चिन्हित दीर्घ
#घोषणा _FP_I_TYPE		दीर्घ

#घोषणा _FP_MUL_MEAT_S(R,X,Y)					\
  _FP_MUL_MEAT_1_imm(_FP_WFRACBITS_S,R,X,Y)
#घोषणा _FP_MUL_MEAT_D(R,X,Y)					\
  _FP_MUL_MEAT_1_wide(_FP_WFRACBITS_D,R,X,Y,umul_ppmm)
#घोषणा _FP_MUL_MEAT_Q(R,X,Y)					\
  _FP_MUL_MEAT_2_wide(_FP_WFRACBITS_Q,R,X,Y,umul_ppmm)

#घोषणा _FP_DIV_MEAT_S(R,X,Y)	_FP_DIV_MEAT_1_imm(S,R,X,Y,_FP_DIV_HELP_imm)
#घोषणा _FP_DIV_MEAT_D(R,X,Y)	_FP_DIV_MEAT_1_uभाग(D,R,X,Y)
#घोषणा _FP_DIV_MEAT_Q(R,X,Y)	_FP_DIV_MEAT_2_uभाग(Q,R,X,Y)

#घोषणा _FP_न_अंकFRAC_S		_FP_Qन_अंकBIT_S
#घोषणा _FP_न_अंकFRAC_D		_FP_Qन_अंकBIT_D
#घोषणा _FP_न_अंकFRAC_Q		_FP_Qन_अंकBIT_Q
#घोषणा _FP_न_अंकSIGN_S		1
#घोषणा _FP_न_अंकSIGN_D		1
#घोषणा _FP_न_अंकSIGN_Q		1

#घोषणा _FP_KEEPन_अंकFRACP 1

/* Alpha Architecture Handbook, 4.7.10.4 sais that
 * we should prefer any type of NaN in Fb, then Fa.
 */
#घोषणा _FP_CHOOSEन_अंक(fs, wc, R, X, Y, OP)			\
  करो अणु								\
    R##_s = Y##_s;						\
    _FP_FRAC_COPY_##wc(R,X);					\
    R##_c = FP_CLS_न_अंक;						\
  पूर्ण जबतक (0)

/* Obtain the current rounding mode. */
#घोषणा FP_ROUNDMODE	mode
#घोषणा FP_RND_NEAREST	(FPCR_DYN_NORMAL >> FPCR_DYN_SHIFT)
#घोषणा FP_RND_ZERO	(FPCR_DYN_CHOPPED >> FPCR_DYN_SHIFT)
#घोषणा FP_RND_PINF	(FPCR_DYN_PLUS >> FPCR_DYN_SHIFT)
#घोषणा FP_RND_MINF	(FPCR_DYN_MINUS >> FPCR_DYN_SHIFT)

/* Exception flags. */
#घोषणा FP_EX_INVALID		IEEE_TRAP_ENABLE_INV
#घोषणा FP_EX_OVERFLOW		IEEE_TRAP_ENABLE_OVF
#घोषणा FP_EX_UNDERFLOW		IEEE_TRAP_ENABLE_UNF
#घोषणा FP_EX_DIVZERO		IEEE_TRAP_ENABLE_DZE
#घोषणा FP_EX_INEXACT		IEEE_TRAP_ENABLE_INE
#घोषणा FP_EX_DENORM		IEEE_TRAP_ENABLE_DNO

#घोषणा FP_DENORM_ZERO		(swcr & IEEE_MAP_DMZ)

/* We ग_लिखो the results always */
#घोषणा FP_INHIBIT_RESULTS 0

#पूर्ण_अगर
