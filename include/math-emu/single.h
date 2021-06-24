<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Definitions क्रम IEEE Single Precision.
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

#अगर_अघोषित    __MATH_EMU_SINGLE_H__
#घोषणा    __MATH_EMU_SINGLE_H__

#अगर _FP_W_TYPE_SIZE < 32
#त्रुटि "Here's a nickel kid.  Go buy yourself a real computer."
#पूर्ण_अगर

#घोषणा _FP_FRACBITS_S		24
#घोषणा _FP_FRACXBITS_S		(_FP_W_TYPE_SIZE - _FP_FRACBITS_S)
#घोषणा _FP_WFRACBITS_S		(_FP_WORKBITS + _FP_FRACBITS_S)
#घोषणा _FP_WFRACXBITS_S	(_FP_W_TYPE_SIZE - _FP_WFRACBITS_S)
#घोषणा _FP_EXPBITS_S		8
#घोषणा _FP_EXPBIAS_S		127
#घोषणा _FP_EXPMAX_S		255
#घोषणा _FP_Qन_अंकBIT_S		((_FP_W_TYPE)1 << (_FP_FRACBITS_S-2))
#घोषणा _FP_IMPLBIT_S		((_FP_W_TYPE)1 << (_FP_FRACBITS_S-1))
#घोषणा _FP_OVERFLOW_S		((_FP_W_TYPE)1 << (_FP_WFRACBITS_S))

/* The implementation of _FP_MUL_MEAT_S and _FP_DIV_MEAT_S should be
   chosen by the target machine.  */

जोड़ _FP_UNION_S
अणु
  भग्न flt;
  काष्ठा अणु
#अगर __BYTE_ORDER == __BIG_ENDIAN
    अचिन्हित sign : 1;
    अचिन्हित exp  : _FP_EXPBITS_S;
    अचिन्हित frac : _FP_FRACBITS_S - (_FP_IMPLBIT_S != 0);
#अन्यथा
    अचिन्हित frac : _FP_FRACBITS_S - (_FP_IMPLBIT_S != 0);
    अचिन्हित exp  : _FP_EXPBITS_S;
    अचिन्हित sign : 1;
#पूर्ण_अगर
  पूर्ण bits __attribute__((packed));
पूर्ण;

#घोषणा FP_DECL_S(X)		_FP_DECL(1,X)
#घोषणा FP_UNPACK_RAW_S(X,val)	_FP_UNPACK_RAW_1(S,X,val)
#घोषणा FP_UNPACK_RAW_SP(X,val)	_FP_UNPACK_RAW_1_P(S,X,val)
#घोषणा FP_PACK_RAW_S(val,X)	_FP_PACK_RAW_1(S,val,X)
#घोषणा FP_PACK_RAW_SP(val,X)		\
  करो अणु					\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_1_P(S,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_S(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_1(S,X,val);		\
    _FP_UNPACK_CANONICAL(S,1,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_SP(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_1_P(S,X,val);	\
    _FP_UNPACK_CANONICAL(S,1,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_S(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(S,1,X);		\
    _FP_PACK_RAW_1(S,val,X);		\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_SP(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(S,1,X);		\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_1_P(S,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_ISSIGन_अंक_S(X)		_FP_ISSIGन_अंक(S,1,X)
#घोषणा FP_NEG_S(R,X)			_FP_NEG(S,1,R,X)
#घोषणा FP_ADD_S(R,X,Y)			_FP_ADD(S,1,R,X,Y)
#घोषणा FP_SUB_S(R,X,Y)			_FP_SUB(S,1,R,X,Y)
#घोषणा FP_MUL_S(R,X,Y)			_FP_MUL(S,1,R,X,Y)
#घोषणा FP_DIV_S(R,X,Y)			_FP_DIV(S,1,R,X,Y)
#घोषणा FP_SQRT_S(R,X)			_FP_SQRT(S,1,R,X)
#घोषणा _FP_SQRT_MEAT_S(R,S,T,X,Q)	_FP_SQRT_MEAT_1(R,S,T,X,Q)

#घोषणा FP_CMP_S(r,X,Y,un)	_FP_CMP(S,1,r,X,Y,un)
#घोषणा FP_CMP_EQ_S(r,X,Y)	_FP_CMP_EQ(S,1,r,X,Y)

#घोषणा FP_TO_INT_S(r,X,rsz,rsg)	_FP_TO_INT(S,1,r,X,rsz,rsg)
#घोषणा FP_TO_INT_ROUND_S(r,X,rsz,rsg)	_FP_TO_INT_ROUND(S,1,r,X,rsz,rsg)
#घोषणा FP_FROM_INT_S(X,r,rs,rt)	_FP_FROM_INT(S,1,X,r,rs,rt)

#घोषणा _FP_FRAC_HIGH_S(X)	_FP_FRAC_HIGH_1(X)
#घोषणा _FP_FRAC_HIGH_RAW_S(X)	_FP_FRAC_HIGH_1(X)

#पूर्ण_अगर /* __MATH_EMU_SINGLE_H__ */
