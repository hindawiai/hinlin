<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Definitions क्रम IEEE Double Precision
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

#अगर_अघोषित    __MATH_EMU_DOUBLE_H__
#घोषणा    __MATH_EMU_DOUBLE_H__

#अगर _FP_W_TYPE_SIZE < 32
#त्रुटि "Here's a nickel kid.  Go buy yourself a real computer."
#पूर्ण_अगर

#अगर _FP_W_TYPE_SIZE < 64
#घोषणा _FP_FRACTBITS_D		(2 * _FP_W_TYPE_SIZE)
#अन्यथा
#घोषणा _FP_FRACTBITS_D		_FP_W_TYPE_SIZE
#पूर्ण_अगर

#घोषणा _FP_FRACBITS_D		53
#घोषणा _FP_FRACXBITS_D		(_FP_FRACTBITS_D - _FP_FRACBITS_D)
#घोषणा _FP_WFRACBITS_D		(_FP_WORKBITS + _FP_FRACBITS_D)
#घोषणा _FP_WFRACXBITS_D	(_FP_FRACTBITS_D - _FP_WFRACBITS_D)
#घोषणा _FP_EXPBITS_D		11
#घोषणा _FP_EXPBIAS_D		1023
#घोषणा _FP_EXPMAX_D		2047

#घोषणा _FP_Qन_अंकBIT_D		\
	((_FP_W_TYPE)1 << (_FP_FRACBITS_D-2) % _FP_W_TYPE_SIZE)
#घोषणा _FP_IMPLBIT_D		\
	((_FP_W_TYPE)1 << (_FP_FRACBITS_D-1) % _FP_W_TYPE_SIZE)
#घोषणा _FP_OVERFLOW_D		\
	((_FP_W_TYPE)1 << _FP_WFRACBITS_D % _FP_W_TYPE_SIZE)

#अगर _FP_W_TYPE_SIZE < 64

जोड़ _FP_UNION_D
अणु
  द्विगुन flt;
  काष्ठा अणु
#अगर __BYTE_ORDER == __BIG_ENDIAN
    अचिन्हित sign  : 1;
    अचिन्हित exp   : _FP_EXPBITS_D;
    अचिन्हित frac1 : _FP_FRACBITS_D - (_FP_IMPLBIT_D != 0) - _FP_W_TYPE_SIZE;
    अचिन्हित frac0 : _FP_W_TYPE_SIZE;
#अन्यथा
    अचिन्हित frac0 : _FP_W_TYPE_SIZE;
    अचिन्हित frac1 : _FP_FRACBITS_D - (_FP_IMPLBIT_D != 0) - _FP_W_TYPE_SIZE;
    अचिन्हित exp   : _FP_EXPBITS_D;
    अचिन्हित sign  : 1;
#पूर्ण_अगर
  पूर्ण bits __attribute__((packed));
पूर्ण;

#घोषणा FP_DECL_D(X)		_FP_DECL(2,X)
#घोषणा FP_UNPACK_RAW_D(X,val)	_FP_UNPACK_RAW_2(D,X,val)
#घोषणा FP_UNPACK_RAW_DP(X,val)	_FP_UNPACK_RAW_2_P(D,X,val)
#घोषणा FP_PACK_RAW_D(val,X)	_FP_PACK_RAW_2(D,val,X)
#घोषणा FP_PACK_RAW_DP(val,X)		\
  करो अणु					\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_2_P(D,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_D(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_2(D,X,val);		\
    _FP_UNPACK_CANONICAL(D,2,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_DP(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_2_P(D,X,val);	\
    _FP_UNPACK_CANONICAL(D,2,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_D(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(D,2,X);		\
    _FP_PACK_RAW_2(D,val,X);		\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_DP(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(D,2,X);		\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_2_P(D,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_ISSIGन_अंक_D(X)		_FP_ISSIGन_अंक(D,2,X)
#घोषणा FP_NEG_D(R,X)			_FP_NEG(D,2,R,X)
#घोषणा FP_ADD_D(R,X,Y)			_FP_ADD(D,2,R,X,Y)
#घोषणा FP_SUB_D(R,X,Y)			_FP_SUB(D,2,R,X,Y)
#घोषणा FP_MUL_D(R,X,Y)			_FP_MUL(D,2,R,X,Y)
#घोषणा FP_DIV_D(R,X,Y)			_FP_DIV(D,2,R,X,Y)
#घोषणा FP_SQRT_D(R,X)			_FP_SQRT(D,2,R,X)
#घोषणा _FP_SQRT_MEAT_D(R,S,T,X,Q)	_FP_SQRT_MEAT_2(R,S,T,X,Q)

#घोषणा FP_CMP_D(r,X,Y,un)	_FP_CMP(D,2,r,X,Y,un)
#घोषणा FP_CMP_EQ_D(r,X,Y)	_FP_CMP_EQ(D,2,r,X,Y)

#घोषणा FP_TO_INT_D(r,X,rsz,rsg)	_FP_TO_INT(D,2,r,X,rsz,rsg)
#घोषणा FP_TO_INT_ROUND_D(r,X,rsz,rsg)	_FP_TO_INT_ROUND(D,2,r,X,rsz,rsg)
#घोषणा FP_FROM_INT_D(X,r,rs,rt)	_FP_FROM_INT(D,2,X,r,rs,rt)

#घोषणा _FP_FRAC_HIGH_D(X)	_FP_FRAC_HIGH_2(X)
#घोषणा _FP_FRAC_HIGH_RAW_D(X)	_FP_FRAC_HIGH_2(X)

#अन्यथा

जोड़ _FP_UNION_D
अणु
  द्विगुन flt;
  काष्ठा अणु
#अगर __BYTE_ORDER == __BIG_ENDIAN
    अचिन्हित sign : 1;
    अचिन्हित exp  : _FP_EXPBITS_D;
    अचिन्हित दीर्घ frac : _FP_FRACBITS_D - (_FP_IMPLBIT_D != 0);
#अन्यथा
    अचिन्हित दीर्घ frac : _FP_FRACBITS_D - (_FP_IMPLBIT_D != 0);
    अचिन्हित exp  : _FP_EXPBITS_D;
    अचिन्हित sign : 1;
#पूर्ण_अगर
  पूर्ण bits __attribute__((packed));
पूर्ण;

#घोषणा FP_DECL_D(X)		_FP_DECL(1,X)
#घोषणा FP_UNPACK_RAW_D(X,val)	_FP_UNPACK_RAW_1(D,X,val)
#घोषणा FP_UNPACK_RAW_DP(X,val)	_FP_UNPACK_RAW_1_P(D,X,val)
#घोषणा FP_PACK_RAW_D(val,X)	_FP_PACK_RAW_1(D,val,X)
#घोषणा FP_PACK_RAW_DP(val,X)		\
  करो अणु					\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_1_P(D,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_D(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_1(D,X,val);		\
    _FP_UNPACK_CANONICAL(D,1,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_DP(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_1_P(D,X,val);	\
    _FP_UNPACK_CANONICAL(D,1,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_D(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(D,1,X);		\
    _FP_PACK_RAW_1(D,val,X);		\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_DP(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(D,1,X);		\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_1_P(D,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_ISSIGन_अंक_D(X)		_FP_ISSIGन_अंक(D,1,X)
#घोषणा FP_NEG_D(R,X)			_FP_NEG(D,1,R,X)
#घोषणा FP_ADD_D(R,X,Y)			_FP_ADD(D,1,R,X,Y)
#घोषणा FP_SUB_D(R,X,Y)			_FP_SUB(D,1,R,X,Y)
#घोषणा FP_MUL_D(R,X,Y)			_FP_MUL(D,1,R,X,Y)
#घोषणा FP_DIV_D(R,X,Y)			_FP_DIV(D,1,R,X,Y)
#घोषणा FP_SQRT_D(R,X)			_FP_SQRT(D,1,R,X)
#घोषणा _FP_SQRT_MEAT_D(R,S,T,X,Q)	_FP_SQRT_MEAT_1(R,S,T,X,Q)

/* The implementation of _FP_MUL_D and _FP_DIV_D should be chosen by
   the target machine.  */

#घोषणा FP_CMP_D(r,X,Y,un)	_FP_CMP(D,1,r,X,Y,un)
#घोषणा FP_CMP_EQ_D(r,X,Y)	_FP_CMP_EQ(D,1,r,X,Y)

#घोषणा FP_TO_INT_D(r,X,rsz,rsg)	_FP_TO_INT(D,1,r,X,rsz,rsg)
#घोषणा FP_TO_INT_ROUND_D(r,X,rsz,rsg)	_FP_TO_INT_ROUND(D,1,r,X,rsz,rsg)
#घोषणा FP_FROM_INT_D(X,r,rs,rt)	_FP_FROM_INT(D,1,X,r,rs,rt)

#घोषणा _FP_FRAC_HIGH_D(X)	_FP_FRAC_HIGH_1(X)
#घोषणा _FP_FRAC_HIGH_RAW_D(X)	_FP_FRAC_HIGH_1(X)

#पूर्ण_अगर /* W_TYPE_SIZE < 64 */


#पूर्ण_अगर /* __MATH_EMU_DOUBLE_H__ */
