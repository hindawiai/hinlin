<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+
 *
 * Machine-dependent software भग्नing-poपूर्णांक definitions.
   SuperH kernel version.
   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Riअक्षरd Henderson (rth@cygnus.com),
		  Jakub Jelinek (jj@ultra.linux.cz),
		  David S. Miller (davem@redhat.com) and
		  Peter Maydell (pmaydell@chiark.greenend.org.uk).
*/

#अगर_अघोषित _SFP_MACHINE_H
#घोषणा _SFP_MACHINE_H

#घोषणा _FP_W_TYPE_SIZE		32
#घोषणा _FP_W_TYPE		अचिन्हित दीर्घ
#घोषणा _FP_WS_TYPE		चिन्हित दीर्घ
#घोषणा _FP_I_TYPE		दीर्घ

#घोषणा _FP_MUL_MEAT_S(R,X,Y)					\
  _FP_MUL_MEAT_1_wide(_FP_WFRACBITS_S,R,X,Y,umul_ppmm)
#घोषणा _FP_MUL_MEAT_D(R,X,Y)					\
  _FP_MUL_MEAT_2_wide(_FP_WFRACBITS_D,R,X,Y,umul_ppmm)
#घोषणा _FP_MUL_MEAT_Q(R,X,Y)					\
  _FP_MUL_MEAT_4_wide(_FP_WFRACBITS_Q,R,X,Y,umul_ppmm)

#घोषणा _FP_DIV_MEAT_S(R,X,Y)	_FP_DIV_MEAT_1_uभाग(S,R,X,Y)
#घोषणा _FP_DIV_MEAT_D(R,X,Y)	_FP_DIV_MEAT_2_uभाग(D,R,X,Y)
#घोषणा _FP_DIV_MEAT_Q(R,X,Y)	_FP_DIV_MEAT_4_uभाग(Q,R,X,Y)

#घोषणा _FP_न_अंकFRAC_S		((_FP_Qन_अंकBIT_S << 1) - 1)
#घोषणा _FP_न_अंकFRAC_D		((_FP_Qन_अंकBIT_D << 1) - 1), -1
#घोषणा _FP_न_अंकFRAC_Q		((_FP_Qन_अंकBIT_Q << 1) - 1), -1, -1, -1
#घोषणा _FP_न_अंकSIGN_S		0
#घोषणा _FP_न_अंकSIGN_D		0
#घोषणा _FP_न_अंकSIGN_Q		0

#घोषणा _FP_KEEPन_अंकFRACP 1

/*
 * If one NaN is संकेतing and the other is not,
 * we choose that one, otherwise we choose X.
 */
#घोषणा _FP_CHOOSEन_अंक(fs, wc, R, X, Y, OP)                      \
  करो अणु                                                          \
    अगर ((_FP_FRAC_HIGH_RAW_##fs(X) & _FP_Qन_अंकBIT_##fs)          \
        && !(_FP_FRAC_HIGH_RAW_##fs(Y) & _FP_Qन_अंकBIT_##fs))     \
      अणु                                                         \
        R##_s = Y##_s;                                          \
        _FP_FRAC_COPY_##wc(R,Y);                                \
      पूर्ण                                                         \
    अन्यथा                                                        \
      अणु                                                         \
        R##_s = X##_s;                                          \
        _FP_FRAC_COPY_##wc(R,X);                                \
      पूर्ण                                                         \
    R##_c = FP_CLS_न_अंक;                                         \
  पूर्ण जबतक (0)

//#घोषणा FP_ROUNDMODE		FPSCR_RM
#घोषणा FP_DENORM_ZERO		1/*FPSCR_DN*/

/* Exception flags. */
#घोषणा FP_EX_INVALID		(1<<4)
#घोषणा FP_EX_DIVZERO		(1<<3)
#घोषणा FP_EX_OVERFLOW		(1<<2)
#घोषणा FP_EX_UNDERFLOW		(1<<1)
#घोषणा FP_EX_INEXACT		(1<<0)

#पूर्ण_अगर

