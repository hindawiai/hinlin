<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Definitions क्रम IEEE Quad Precision.
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

#अगर_अघोषित  __MATH_EMU_QUAD_H__
#घोषणा  __MATH_EMU_QUAD_H__

#अगर _FP_W_TYPE_SIZE < 32
#त्रुटि "Here's a nickel, kid. Go buy yourself a real computer."
#पूर्ण_अगर

#अगर _FP_W_TYPE_SIZE < 64
#घोषणा _FP_FRACTBITS_Q         (4*_FP_W_TYPE_SIZE)
#अन्यथा
#घोषणा _FP_FRACTBITS_Q		(2*_FP_W_TYPE_SIZE)
#पूर्ण_अगर

#घोषणा _FP_FRACBITS_Q		113
#घोषणा _FP_FRACXBITS_Q		(_FP_FRACTBITS_Q - _FP_FRACBITS_Q)
#घोषणा _FP_WFRACBITS_Q		(_FP_WORKBITS + _FP_FRACBITS_Q)
#घोषणा _FP_WFRACXBITS_Q	(_FP_FRACTBITS_Q - _FP_WFRACBITS_Q)
#घोषणा _FP_EXPBITS_Q		15
#घोषणा _FP_EXPBIAS_Q		16383
#घोषणा _FP_EXPMAX_Q		32767

#घोषणा _FP_Qन_अंकBIT_Q		\
	((_FP_W_TYPE)1 << (_FP_FRACBITS_Q-2) % _FP_W_TYPE_SIZE)
#घोषणा _FP_IMPLBIT_Q		\
	((_FP_W_TYPE)1 << (_FP_FRACBITS_Q-1) % _FP_W_TYPE_SIZE)
#घोषणा _FP_OVERFLOW_Q		\
	((_FP_W_TYPE)1 << (_FP_WFRACBITS_Q % _FP_W_TYPE_SIZE))

#अगर _FP_W_TYPE_SIZE < 64

जोड़ _FP_UNION_Q
अणु
   दीर्घ द्विगुन flt;
   काष्ठा 
   अणु
#अगर __BYTE_ORDER == __BIG_ENDIAN
      अचिन्हित sign : 1;
      अचिन्हित exp : _FP_EXPBITS_Q;
      अचिन्हित दीर्घ frac3 : _FP_FRACBITS_Q - (_FP_IMPLBIT_Q != 0)-(_FP_W_TYPE_SIZE * 3);
      अचिन्हित दीर्घ frac2 : _FP_W_TYPE_SIZE;
      अचिन्हित दीर्घ frac1 : _FP_W_TYPE_SIZE;
      अचिन्हित दीर्घ frac0 : _FP_W_TYPE_SIZE;
#अन्यथा
      अचिन्हित दीर्घ frac0 : _FP_W_TYPE_SIZE;
      अचिन्हित दीर्घ frac1 : _FP_W_TYPE_SIZE;
      अचिन्हित दीर्घ frac2 : _FP_W_TYPE_SIZE;
      अचिन्हित दीर्घ frac3 : _FP_FRACBITS_Q - (_FP_IMPLBIT_Q != 0)-(_FP_W_TYPE_SIZE * 3);
      अचिन्हित exp : _FP_EXPBITS_Q;
      अचिन्हित sign : 1;
#पूर्ण_अगर /* not bigendian */
   पूर्ण bits __attribute__((packed));
पूर्ण;


#घोषणा FP_DECL_Q(X)		_FP_DECL(4,X)
#घोषणा FP_UNPACK_RAW_Q(X,val)	_FP_UNPACK_RAW_4(Q,X,val)
#घोषणा FP_UNPACK_RAW_QP(X,val)	_FP_UNPACK_RAW_4_P(Q,X,val)
#घोषणा FP_PACK_RAW_Q(val,X)	_FP_PACK_RAW_4(Q,val,X)
#घोषणा FP_PACK_RAW_QP(val,X)		\
  करो अणु					\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_4_P(Q,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_Q(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_4(Q,X,val);		\
    _FP_UNPACK_CANONICAL(Q,4,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_QP(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_4_P(Q,X,val);	\
    _FP_UNPACK_CANONICAL(Q,4,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_Q(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(Q,4,X);		\
    _FP_PACK_RAW_4(Q,val,X);		\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_QP(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(Q,4,X);		\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_4_P(Q,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_ISSIGन_अंक_Q(X)		_FP_ISSIGन_अंक(Q,4,X)
#घोषणा FP_NEG_Q(R,X)			_FP_NEG(Q,4,R,X)
#घोषणा FP_ADD_Q(R,X,Y)			_FP_ADD(Q,4,R,X,Y)
#घोषणा FP_SUB_Q(R,X,Y)			_FP_SUB(Q,4,R,X,Y)
#घोषणा FP_MUL_Q(R,X,Y)			_FP_MUL(Q,4,R,X,Y)
#घोषणा FP_DIV_Q(R,X,Y)			_FP_DIV(Q,4,R,X,Y)
#घोषणा FP_SQRT_Q(R,X)			_FP_SQRT(Q,4,R,X)
#घोषणा _FP_SQRT_MEAT_Q(R,S,T,X,Q)	_FP_SQRT_MEAT_4(R,S,T,X,Q)

#घोषणा FP_CMP_Q(r,X,Y,un)	_FP_CMP(Q,4,r,X,Y,un)
#घोषणा FP_CMP_EQ_Q(r,X,Y)	_FP_CMP_EQ(Q,4,r,X,Y)

#घोषणा FP_TO_INT_Q(r,X,rsz,rsg)	_FP_TO_INT(Q,4,r,X,rsz,rsg)
#घोषणा FP_TO_INT_ROUND_Q(r,X,rsz,rsg)	_FP_TO_INT_ROUND(Q,4,r,X,rsz,rsg)
#घोषणा FP_FROM_INT_Q(X,r,rs,rt)	_FP_FROM_INT(Q,4,X,r,rs,rt)

#घोषणा _FP_FRAC_HIGH_Q(X)	_FP_FRAC_HIGH_4(X)
#घोषणा _FP_FRAC_HIGH_RAW_Q(X)	_FP_FRAC_HIGH_4(X)

#अन्यथा   /* not _FP_W_TYPE_SIZE < 64 */
जोड़ _FP_UNION_Q
अणु
  दीर्घ द्विगुन flt /* __attribute__((mode(TF))) */ ;
  काष्ठा अणु
#अगर __BYTE_ORDER == __BIG_ENDIAN
    अचिन्हित sign  : 1;
    अचिन्हित exp   : _FP_EXPBITS_Q;
    अचिन्हित दीर्घ frac1 : _FP_FRACBITS_Q-(_FP_IMPLBIT_Q != 0)-_FP_W_TYPE_SIZE;
    अचिन्हित दीर्घ frac0 : _FP_W_TYPE_SIZE;
#अन्यथा
    अचिन्हित दीर्घ frac0 : _FP_W_TYPE_SIZE;
    अचिन्हित दीर्घ frac1 : _FP_FRACBITS_Q-(_FP_IMPLBIT_Q != 0)-_FP_W_TYPE_SIZE;
    अचिन्हित exp   : _FP_EXPBITS_Q;
    अचिन्हित sign  : 1;
#पूर्ण_अगर
  पूर्ण bits;
पूर्ण;

#घोषणा FP_DECL_Q(X)		_FP_DECL(2,X)
#घोषणा FP_UNPACK_RAW_Q(X,val)	_FP_UNPACK_RAW_2(Q,X,val)
#घोषणा FP_UNPACK_RAW_QP(X,val)	_FP_UNPACK_RAW_2_P(Q,X,val)
#घोषणा FP_PACK_RAW_Q(val,X)	_FP_PACK_RAW_2(Q,val,X)
#घोषणा FP_PACK_RAW_QP(val,X)		\
  करो अणु					\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_2_P(Q,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_Q(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_2(Q,X,val);		\
    _FP_UNPACK_CANONICAL(Q,2,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_UNPACK_QP(X,val)		\
  करो अणु					\
    _FP_UNPACK_RAW_2_P(Q,X,val);	\
    _FP_UNPACK_CANONICAL(Q,2,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_Q(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(Q,2,X);		\
    _FP_PACK_RAW_2(Q,val,X);		\
  पूर्ण जबतक (0)

#घोषणा FP_PACK_QP(val,X)		\
  करो अणु					\
    _FP_PACK_CANONICAL(Q,2,X);		\
    अगर (!FP_INHIBIT_RESULTS)		\
      _FP_PACK_RAW_2_P(Q,val,X);	\
  पूर्ण जबतक (0)

#घोषणा FP_ISSIGन_अंक_Q(X)		_FP_ISSIGन_अंक(Q,2,X)
#घोषणा FP_NEG_Q(R,X)			_FP_NEG(Q,2,R,X)
#घोषणा FP_ADD_Q(R,X,Y)			_FP_ADD(Q,2,R,X,Y)
#घोषणा FP_SUB_Q(R,X,Y)			_FP_SUB(Q,2,R,X,Y)
#घोषणा FP_MUL_Q(R,X,Y)			_FP_MUL(Q,2,R,X,Y)
#घोषणा FP_DIV_Q(R,X,Y)			_FP_DIV(Q,2,R,X,Y)
#घोषणा FP_SQRT_Q(R,X)			_FP_SQRT(Q,2,R,X)
#घोषणा _FP_SQRT_MEAT_Q(R,S,T,X,Q)	_FP_SQRT_MEAT_2(R,S,T,X,Q)

#घोषणा FP_CMP_Q(r,X,Y,un)	_FP_CMP(Q,2,r,X,Y,un)
#घोषणा FP_CMP_EQ_Q(r,X,Y)	_FP_CMP_EQ(Q,2,r,X,Y)

#घोषणा FP_TO_INT_Q(r,X,rsz,rsg)	_FP_TO_INT(Q,2,r,X,rsz,rsg)
#घोषणा FP_TO_INT_ROUND_Q(r,X,rsz,rsg)	_FP_TO_INT_ROUND(Q,2,r,X,rsz,rsg)
#घोषणा FP_FROM_INT_Q(X,r,rs,rt)	_FP_FROM_INT(Q,2,X,r,rs,rt)

#घोषणा _FP_FRAC_HIGH_Q(X)	_FP_FRAC_HIGH_2(X)
#घोषणा _FP_FRAC_HIGH_RAW_Q(X)	_FP_FRAC_HIGH_2(X)

#पूर्ण_अगर /* not _FP_W_TYPE_SIZE < 64 */

#पूर्ण_अगर /* __MATH_EMU_QUAD_H__ */
