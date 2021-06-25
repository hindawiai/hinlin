<शैली गुरु>
/* Machine-dependent software भग्नing-poपूर्णांक definitions.
   Sparc64 kernel version.
   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Riअक्षरd Henderson (rth@cygnus.com),
		  Jakub Jelinek (jj@ultra.linux.cz) and
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
#घोषणा _FP_DIV_MEAT_D(R,X,Y)	_FP_DIV_MEAT_1_uभाग_norm(D,R,X,Y)
#घोषणा _FP_DIV_MEAT_Q(R,X,Y)	_FP_DIV_MEAT_2_uभाग(Q,R,X,Y)

#घोषणा _FP_न_अंकFRAC_S		((_FP_Qन_अंकBIT_S << 1) - 1)
#घोषणा _FP_न_अंकFRAC_D		((_FP_Qन_अंकBIT_D << 1) - 1)
#घोषणा _FP_न_अंकFRAC_Q		((_FP_Qन_अंकBIT_Q << 1) - 1), -1
#घोषणा _FP_न_अंकSIGN_S		0
#घोषणा _FP_न_अंकSIGN_D		0
#घोषणा _FP_न_अंकSIGN_Q		0

#घोषणा _FP_KEEPन_अंकFRACP 1

/* If one NaN is संकेतing and the other is not,
 * we choose that one, otherwise we choose X.
 */
/* For _Qp_* and _Q_*, this should prefer X, क्रम
 * CPU inकाष्ठाion emulation this should prefer Y.
 * (see SPAMv9 B.2.2 section).
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

/* Obtain the current rounding mode. */
#अगर_अघोषित FP_ROUNDMODE
#घोषणा FP_ROUNDMODE	((current_thपढ़ो_info()->xfsr[0] >> 30) & 0x3)
#पूर्ण_अगर

/* Exception flags. */
#घोषणा FP_EX_INVALID		(1 << 4)
#घोषणा FP_EX_OVERFLOW		(1 << 3)
#घोषणा FP_EX_UNDERFLOW		(1 << 2)
#घोषणा FP_EX_DIVZERO		(1 << 1)
#घोषणा FP_EX_INEXACT		(1 << 0)

#घोषणा FP_HANDLE_EXCEPTIONS वापस _fex

#घोषणा FP_INHIBIT_RESULTS ((current_thपढ़ो_info()->xfsr[0] >> 23) & _fex)

#घोषणा FP_TRAPPING_EXCEPTIONS ((current_thपढ़ो_info()->xfsr[0] >> 23) & 0x1f)

#पूर्ण_अगर
