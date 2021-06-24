<शैली गुरु>
/* Machine-dependent software भग्नing-poपूर्णांक definitions.
   Sparc userland (_Q_*) version.
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

/* Some assembly to speed things up. */
#घोषणा __FP_FRAC_ADD_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)			\
  __यंत्र__ ("addcc %r7,%8,%2\n\t"					\
	   "addxcc %r5,%6,%1\n\t"					\
	   "addx %r3,%4,%0\n"						\
	   : "=r" (r2),							\
	     "=&r" (r1),						\
	     "=&r" (r0)							\
	   : "%rJ" ((USItype)(x2)),					\
	     "rI" ((USItype)(y2)),					\
	     "%rJ" ((USItype)(x1)),					\
	     "rI" ((USItype)(y1)),					\
	     "%rJ" ((USItype)(x0)),					\
	     "rI" ((USItype)(y0))					\
	   : "cc")

#घोषणा __FP_FRAC_SUB_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)			\
  __यंत्र__ ("subcc %r7,%8,%2\n\t"					\
	    "subxcc %r5,%6,%1\n\t"					\
	    "subx %r3,%4,%0\n"						\
	   : "=r" (r2),							\
	     "=&r" (r1),						\
	     "=&r" (r0)							\
	   : "%rJ" ((USItype)(x2)),					\
	     "rI" ((USItype)(y2)),					\
	     "%rJ" ((USItype)(x1)),					\
	     "rI" ((USItype)(y1)),					\
	     "%rJ" ((USItype)(x0)),					\
	     "rI" ((USItype)(y0))					\
	   : "cc")

#घोषणा __FP_FRAC_ADD_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)		\
  करो अणु									\
    /* We need to fool gcc,  as we need to pass more than 10		\
       input/outमाला_दो.  */						\
    रेजिस्टर USItype _t1 __यंत्र__ ("g1"), _t2 __यंत्र__ ("g2");		\
    __यंत्र__ __अस्थिर__ (						\
	    "addcc %r8,%9,%1\n\t"					\
	    "addxcc %r6,%7,%0\n\t"					\
	    "addxcc %r4,%5,%%g2\n\t"					\
	    "addx %r2,%3,%%g1\n\t"					\
	   : "=&r" (r1),						\
	     "=&r" (r0)							\
	   : "%rJ" ((USItype)(x3)),					\
	     "rI" ((USItype)(y3)),					\
	     "%rJ" ((USItype)(x2)),					\
	     "rI" ((USItype)(y2)),					\
	     "%rJ" ((USItype)(x1)),					\
	     "rI" ((USItype)(y1)),					\
	     "%rJ" ((USItype)(x0)),					\
	     "rI" ((USItype)(y0))					\
	   : "cc", "g1", "g2");						\
    __यंत्र__ __अस्थिर__ ("" : "=r" (_t1), "=r" (_t2));			\
    r3 = _t1; r2 = _t2;							\
  पूर्ण जबतक (0)

#घोषणा __FP_FRAC_SUB_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)		\
  करो अणु									\
    /* We need to fool gcc,  as we need to pass more than 10		\
       input/outमाला_दो.  */						\
    रेजिस्टर USItype _t1 __यंत्र__ ("g1"), _t2 __यंत्र__ ("g2");		\
    __यंत्र__ __अस्थिर__ (						\
	    "subcc %r8,%9,%1\n\t"					\
	    "subxcc %r6,%7,%0\n\t"					\
	    "subxcc %r4,%5,%%g2\n\t"					\
	    "subx %r2,%3,%%g1\n\t"					\
	   : "=&r" (r1),						\
	     "=&r" (r0)							\
	   : "%rJ" ((USItype)(x3)),					\
	     "rI" ((USItype)(y3)),					\
	     "%rJ" ((USItype)(x2)),					\
	     "rI" ((USItype)(y2)),					\
	     "%rJ" ((USItype)(x1)),					\
	     "rI" ((USItype)(y1)),					\
	     "%rJ" ((USItype)(x0)),					\
	     "rI" ((USItype)(y0))					\
	   : "cc", "g1", "g2");						\
    __यंत्र__ __अस्थिर__ ("" : "=r" (_t1), "=r" (_t2));			\
    r3 = _t1; r2 = _t2;							\
  पूर्ण जबतक (0)

#घोषणा __FP_FRAC_DEC_3(x2,x1,x0,y2,y1,y0) __FP_FRAC_SUB_3(x2,x1,x0,x2,x1,x0,y2,y1,y0)

#घोषणा __FP_FRAC_DEC_4(x3,x2,x1,x0,y3,y2,y1,y0) __FP_FRAC_SUB_4(x3,x2,x1,x0,x3,x2,x1,x0,y3,y2,y1,y0)

#घोषणा __FP_FRAC_ADDI_4(x3,x2,x1,x0,i)					\
  __यंत्र__ ("addcc %3,%4,%3\n\t"						\
	   "addxcc %2,%%g0,%2\n\t"					\
	   "addxcc %1,%%g0,%1\n\t"					\
	   "addx %0,%%g0,%0\n\t"					\
	   : "=&r" (x3),						\
	     "=&r" (x2),						\
	     "=&r" (x1),						\
	     "=&r" (x0)							\
	   : "rI" ((USItype)(i)),					\
	     "0" ((USItype)(x3)),					\
	     "1" ((USItype)(x2)),					\
	     "2" ((USItype)(x1)),					\
	     "3" ((USItype)(x0))					\
	   : "cc")

#अगर_अघोषित CONFIG_SMP
बाह्य काष्ठा task_काष्ठा *last_task_used_math;
#पूर्ण_अगर

/* Obtain the current rounding mode. */
#अगर_अघोषित FP_ROUNDMODE
#अगर_घोषित CONFIG_SMP
#घोषणा FP_ROUNDMODE	((current->thपढ़ो.fsr >> 30) & 0x3)
#अन्यथा
#घोषणा FP_ROUNDMODE	((last_task_used_math->thपढ़ो.fsr >> 30) & 0x3)
#पूर्ण_अगर
#पूर्ण_अगर

/* Exception flags. */
#घोषणा FP_EX_INVALID		(1 << 4)
#घोषणा FP_EX_OVERFLOW		(1 << 3)
#घोषणा FP_EX_UNDERFLOW		(1 << 2)
#घोषणा FP_EX_DIVZERO		(1 << 1)
#घोषणा FP_EX_INEXACT		(1 << 0)

#घोषणा FP_HANDLE_EXCEPTIONS वापस _fex

#अगर_घोषित CONFIG_SMP
#घोषणा FP_INHIBIT_RESULTS ((current->thपढ़ो.fsr >> 23) & _fex)
#अन्यथा
#घोषणा FP_INHIBIT_RESULTS ((last_task_used_math->thपढ़ो.fsr >> 23) & _fex)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
#घोषणा FP_TRAPPING_EXCEPTIONS ((current->thपढ़ो.fsr >> 23) & 0x1f)
#अन्यथा
#घोषणा FP_TRAPPING_EXCEPTIONS ((last_task_used_math->thपढ़ो.fsr >> 23) & 0x1f)
#पूर्ण_अगर

#पूर्ण_अगर
