<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Basic two-word fraction declaration and manipulation.
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

#अगर_अघोषित __MATH_EMU_OP_2_H__
#घोषणा __MATH_EMU_OP_2_H__

#घोषणा _FP_FRAC_DECL_2(X)	_FP_W_TYPE X##_f0 = 0, X##_f1 = 0
#घोषणा _FP_FRAC_COPY_2(D,S)	(D##_f0 = S##_f0, D##_f1 = S##_f1)
#घोषणा _FP_FRAC_SET_2(X,I)	__FP_FRAC_SET_2(X, I)
#घोषणा _FP_FRAC_HIGH_2(X)	(X##_f1)
#घोषणा _FP_FRAC_LOW_2(X)	(X##_f0)
#घोषणा _FP_FRAC_WORD_2(X,w)	(X##_f##w)
#घोषणा _FP_FRAC_SLL_2(X, N) (						       \
	(व्योम) (((N) < _FP_W_TYPE_SIZE)					       \
	  ? (अणु								       \
		अगर (__builtin_स्थिरant_p(N) && (N) == 1) अणु		       \
			X##_f1 = X##_f1 + X##_f1 +			       \
				(((_FP_WS_TYPE) (X##_f0)) < 0);		       \
			X##_f0 += X##_f0;				       \
		पूर्ण अन्यथा अणु						       \
			X##_f1 = X##_f1 << (N) | X##_f0 >>		       \
						(_FP_W_TYPE_SIZE - (N));       \
			X##_f0 <<= (N);					       \
		पूर्ण							       \
		0;							       \
	    पूर्ण)								       \
	  : (अणु								       \
	      X##_f1 = X##_f0 << ((N) - _FP_W_TYPE_SIZE);		       \
	      X##_f0 = 0;						       \
	  पूर्ण)))


#घोषणा _FP_FRAC_SRL_2(X, N) (						       \
	(व्योम) (((N) < _FP_W_TYPE_SIZE)					       \
	  ? (अणु								       \
	      X##_f0 = X##_f0 >> (N) | X##_f1 << (_FP_W_TYPE_SIZE - (N));      \
	      X##_f1 >>= (N);						       \
	    पूर्ण)								       \
	  : (अणु								       \
	      X##_f0 = X##_f1 >> ((N) - _FP_W_TYPE_SIZE);		       \
	      X##_f1 = 0;						       \
	    पूर्ण)))


/* Right shअगरt with sticky-lsb.  */
#घोषणा _FP_FRAC_SRS_2(X, N, sz) (					       \
	(व्योम) (((N) < _FP_W_TYPE_SIZE)					       \
	  ? (अणु								       \
	      X##_f0 = (X##_f1 << (_FP_W_TYPE_SIZE - (N)) | X##_f0 >> (N)      \
			| (__builtin_स्थिरant_p(N) && (N) == 1		       \
			   ? X##_f0 & 1					       \
			   : (X##_f0 << (_FP_W_TYPE_SIZE - (N))) != 0));       \
		X##_f1 >>= (N);						       \
	    पूर्ण)								       \
	  : (अणु								       \
	      X##_f0 = (X##_f1 >> ((N) - _FP_W_TYPE_SIZE)		       \
			| ((((N) == _FP_W_TYPE_SIZE			       \
			     ? 0					       \
			     : (X##_f1 << (2*_FP_W_TYPE_SIZE - (N))))          \
			    | X##_f0) != 0));				       \
	      X##_f1 = 0;						       \
	    पूर्ण)))

#घोषणा _FP_FRAC_ADDI_2(X,I)	\
  __FP_FRAC_ADDI_2(X##_f1, X##_f0, I)

#घोषणा _FP_FRAC_ADD_2(R,X,Y)	\
  __FP_FRAC_ADD_2(R##_f1, R##_f0, X##_f1, X##_f0, Y##_f1, Y##_f0)

#घोषणा _FP_FRAC_SUB_2(R,X,Y)	\
  __FP_FRAC_SUB_2(R##_f1, R##_f0, X##_f1, X##_f0, Y##_f1, Y##_f0)

#घोषणा _FP_FRAC_DEC_2(X,Y)	\
  __FP_FRAC_DEC_2(X##_f1, X##_f0, Y##_f1, Y##_f0)

#घोषणा _FP_FRAC_CLZ_2(R,X)	\
  करो अणु				\
    अगर (X##_f1)			\
      __FP_CLZ(R,X##_f1);	\
    अन्यथा 			\
    अणु				\
      __FP_CLZ(R,X##_f0);	\
      R += _FP_W_TYPE_SIZE;	\
    पूर्ण				\
  पूर्ण जबतक(0)

/* Predicates */
#घोषणा _FP_FRAC_NEGP_2(X)	((_FP_WS_TYPE)X##_f1 < 0)
#घोषणा _FP_FRAC_ZEROP_2(X)	((X##_f1 | X##_f0) == 0)
#घोषणा _FP_FRAC_OVERP_2(fs,X)	(_FP_FRAC_HIGH_##fs(X) & _FP_OVERFLOW_##fs)
#घोषणा _FP_FRAC_CLEAR_OVERP_2(fs,X)	(_FP_FRAC_HIGH_##fs(X) &= ~_FP_OVERFLOW_##fs)
#घोषणा _FP_FRAC_EQ_2(X, Y)	(X##_f1 == Y##_f1 && X##_f0 == Y##_f0)
#घोषणा _FP_FRAC_GT_2(X, Y)	\
  (X##_f1 > Y##_f1 || (X##_f1 == Y##_f1 && X##_f0 > Y##_f0))
#घोषणा _FP_FRAC_GE_2(X, Y)	\
  (X##_f1 > Y##_f1 || (X##_f1 == Y##_f1 && X##_f0 >= Y##_f0))

#घोषणा _FP_ZEROFRAC_2		0, 0
#घोषणा _FP_MINFRAC_2		0, 1
#घोषणा _FP_MAXFRAC_2		(~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0)

/*
 * Internals 
 */

#घोषणा __FP_FRAC_SET_2(X,I1,I0)	(X##_f0 = I0, X##_f1 = I1)

#घोषणा __FP_CLZ_2(R, xh, xl)	\
  करो अणु				\
    अगर (xh)			\
      __FP_CLZ(R,xh);		\
    अन्यथा 			\
    अणु				\
      __FP_CLZ(R,xl);		\
      R += _FP_W_TYPE_SIZE;	\
    पूर्ण				\
  पूर्ण जबतक(0)

#अगर 0

#अगर_अघोषित __FP_FRAC_ADDI_2
#घोषणा __FP_FRAC_ADDI_2(xh, xl, i)	\
  (xh += ((xl += i) < i))
#पूर्ण_अगर
#अगर_अघोषित __FP_FRAC_ADD_2
#घोषणा __FP_FRAC_ADD_2(rh, rl, xh, xl, yh, yl)	\
  (rh = xh + yh + ((rl = xl + yl) < xl))
#पूर्ण_अगर
#अगर_अघोषित __FP_FRAC_SUB_2
#घोषणा __FP_FRAC_SUB_2(rh, rl, xh, xl, yh, yl)	\
  (rh = xh - yh - ((rl = xl - yl) > xl))
#पूर्ण_अगर
#अगर_अघोषित __FP_FRAC_DEC_2
#घोषणा __FP_FRAC_DEC_2(xh, xl, yh, yl)	\
  करो अणु					\
    UWtype _t = xl;			\
    xh -= yh + ((xl -= yl) > _t);	\
  पूर्ण जबतक (0)
#पूर्ण_अगर

#अन्यथा

#अघोषित __FP_FRAC_ADDI_2
#घोषणा __FP_FRAC_ADDI_2(xh, xl, i)	add_ssaaaa(xh, xl, xh, xl, 0, i)
#अघोषित __FP_FRAC_ADD_2
#घोषणा __FP_FRAC_ADD_2			add_ssaaaa
#अघोषित __FP_FRAC_SUB_2
#घोषणा __FP_FRAC_SUB_2			sub_ddmmss
#अघोषित __FP_FRAC_DEC_2
#घोषणा __FP_FRAC_DEC_2(xh, xl, yh, yl)	sub_ddmmss(xh, xl, xh, xl, yh, yl)

#पूर्ण_अगर

/*
 * Unpack the raw bits of a native fp value.  Do not classअगरy or
 * normalize the data.
 */

#घोषणा _FP_UNPACK_RAW_2(fs, X, val)			\
  करो अणु							\
    जोड़ _FP_UNION_##fs _flo; _flo.flt = (val);	\
							\
    X##_f0 = _flo.bits.frac0;				\
    X##_f1 = _flo.bits.frac1;				\
    X##_e  = _flo.bits.exp;				\
    X##_s  = _flo.bits.sign;				\
  पूर्ण जबतक (0)

#घोषणा _FP_UNPACK_RAW_2_P(fs, X, val)			\
  करो अणु							\
    जोड़ _FP_UNION_##fs *_flo =			\
      (जोड़ _FP_UNION_##fs *)(val);			\
							\
    X##_f0 = _flo->bits.frac0;				\
    X##_f1 = _flo->bits.frac1;				\
    X##_e  = _flo->bits.exp;				\
    X##_s  = _flo->bits.sign;				\
  पूर्ण जबतक (0)


/*
 * Repack the raw bits of a native fp value.
 */

#घोषणा _FP_PACK_RAW_2(fs, val, X)			\
  करो अणु							\
    जोड़ _FP_UNION_##fs _flo;				\
							\
    _flo.bits.frac0 = X##_f0;				\
    _flo.bits.frac1 = X##_f1;				\
    _flo.bits.exp   = X##_e;				\
    _flo.bits.sign  = X##_s;				\
							\
    (val) = _flo.flt;					\
  पूर्ण जबतक (0)

#घोषणा _FP_PACK_RAW_2_P(fs, val, X)			\
  करो अणु							\
    जोड़ _FP_UNION_##fs *_flo =			\
      (जोड़ _FP_UNION_##fs *)(val);			\
							\
    _flo->bits.frac0 = X##_f0;				\
    _flo->bits.frac1 = X##_f1;				\
    _flo->bits.exp   = X##_e;				\
    _flo->bits.sign  = X##_s;				\
  पूर्ण जबतक (0)


/*
 * Multiplication algorithms:
 */

/* Given a 1W * 1W => 2W primitive, करो the extended multiplication.  */

#घोषणा _FP_MUL_MEAT_2_wide(wfracbits, R, X, Y, करोit)			\
  करो अणु									\
    _FP_FRAC_DECL_4(_z); _FP_FRAC_DECL_2(_b); _FP_FRAC_DECL_2(_c);	\
									\
    करोit(_FP_FRAC_WORD_4(_z,1), _FP_FRAC_WORD_4(_z,0), X##_f0, Y##_f0);	\
    करोit(_b_f1, _b_f0, X##_f0, Y##_f1);					\
    करोit(_c_f1, _c_f0, X##_f1, Y##_f0);					\
    करोit(_FP_FRAC_WORD_4(_z,3), _FP_FRAC_WORD_4(_z,2), X##_f1, Y##_f1);	\
									\
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		    _FP_FRAC_WORD_4(_z,1), 0, _b_f1, _b_f0,		\
		    _FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		    _FP_FRAC_WORD_4(_z,1));				\
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		    _FP_FRAC_WORD_4(_z,1), 0, _c_f1, _c_f0,		\
		    _FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		    _FP_FRAC_WORD_4(_z,1));				\
									\
    /* Normalize since we know where the msb of the multiplicands	\
       were (bit B), we know that the msb of the of the product is	\
       at either 2B or 2B-1.  */					\
    _FP_FRAC_SRS_4(_z, wfracbits-1, 2*wfracbits);			\
    R##_f0 = _FP_FRAC_WORD_4(_z,0);					\
    R##_f1 = _FP_FRAC_WORD_4(_z,1);					\
  पूर्ण जबतक (0)

/* Given a 1W * 1W => 2W primitive, करो the extended multiplication.
   Do only 3 multiplications instead of four. This one is क्रम machines
   where multiplication is much more expensive than subtraction.  */

#घोषणा _FP_MUL_MEAT_2_wide_3mul(wfracbits, R, X, Y, करोit)		\
  करो अणु									\
    _FP_FRAC_DECL_4(_z); _FP_FRAC_DECL_2(_b); _FP_FRAC_DECL_2(_c);	\
    _FP_W_TYPE _d;							\
    पूर्णांक _c1, _c2;							\
									\
    _b_f0 = X##_f0 + X##_f1;						\
    _c1 = _b_f0 < X##_f0;						\
    _b_f1 = Y##_f0 + Y##_f1;						\
    _c2 = _b_f1 < Y##_f0;						\
    करोit(_d, _FP_FRAC_WORD_4(_z,0), X##_f0, Y##_f0);			\
    करोit(_FP_FRAC_WORD_4(_z,2), _FP_FRAC_WORD_4(_z,1), _b_f0, _b_f1);	\
    करोit(_c_f1, _c_f0, X##_f1, Y##_f1);					\
									\
    _b_f0 &= -_c2;							\
    _b_f1 &= -_c1;							\
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		    _FP_FRAC_WORD_4(_z,1), (_c1 & _c2), 0, _d,		\
		    0, _FP_FRAC_WORD_4(_z,2), _FP_FRAC_WORD_4(_z,1));	\
    __FP_FRAC_ADDI_2(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		     _b_f0);						\
    __FP_FRAC_ADDI_2(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		     _b_f1);						\
    __FP_FRAC_DEC_3(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		    _FP_FRAC_WORD_4(_z,1),				\
		    0, _d, _FP_FRAC_WORD_4(_z,0));			\
    __FP_FRAC_DEC_3(_FP_FRAC_WORD_4(_z,3),_FP_FRAC_WORD_4(_z,2),	\
		    _FP_FRAC_WORD_4(_z,1), 0, _c_f1, _c_f0);		\
    __FP_FRAC_ADD_2(_FP_FRAC_WORD_4(_z,3), _FP_FRAC_WORD_4(_z,2),	\
		    _c_f1, _c_f0,					\
		    _FP_FRAC_WORD_4(_z,3), _FP_FRAC_WORD_4(_z,2));	\
									\
    /* Normalize since we know where the msb of the multiplicands	\
       were (bit B), we know that the msb of the of the product is	\
       at either 2B or 2B-1.  */					\
    _FP_FRAC_SRS_4(_z, wfracbits-1, 2*wfracbits);			\
    R##_f0 = _FP_FRAC_WORD_4(_z,0);					\
    R##_f1 = _FP_FRAC_WORD_4(_z,1);					\
  पूर्ण जबतक (0)

#घोषणा _FP_MUL_MEAT_2_gmp(wfracbits, R, X, Y)				\
  करो अणु									\
    _FP_FRAC_DECL_4(_z);						\
    _FP_W_TYPE _x[2], _y[2];						\
    _x[0] = X##_f0; _x[1] = X##_f1;					\
    _y[0] = Y##_f0; _y[1] = Y##_f1;					\
									\
    mpn_mul_n(_z_f, _x, _y, 2);						\
									\
    /* Normalize since we know where the msb of the multiplicands	\
       were (bit B), we know that the msb of the of the product is	\
       at either 2B or 2B-1.  */					\
    _FP_FRAC_SRS_4(_z, wfracbits-1, 2*wfracbits);			\
    R##_f0 = _z_f[0];							\
    R##_f1 = _z_f[1];							\
  पूर्ण जबतक (0)

/* Do at most 120x120=240 bits multiplication using द्विगुन भग्नing
   poपूर्णांक multiplication.  This is useful अगर भग्नing poपूर्णांक
   multiplication has much bigger throughput than पूर्णांकeger multiply.
   It is supposed to work क्रम _FP_W_TYPE_SIZE 64 and wfracbits
   between 106 and 120 only.  
   Caller guarantees that X and Y has (1LLL << (wfracbits - 1)) set.
   SETFETZ is a macro which will disable all FPU exceptions and set rounding
   towards zero,  RESETFE should optionally reset it back.  */

#घोषणा _FP_MUL_MEAT_2_120_240_द्विगुन(wfracbits, R, X, Y, setfetz, resetfe)	\
  करो अणु										\
    अटल स्थिर द्विगुन _स्थिर[] = अणु						\
      /* 2^-24 */ 5.9604644775390625e-08,					\
      /* 2^-48 */ 3.5527136788005009e-15,					\
      /* 2^-72 */ 2.1175823681357508e-22,					\
      /* 2^-96 */ 1.2621774483536189e-29,					\
      /* 2^28 */ 2.68435456e+08,						\
      /* 2^4 */ 1.600000e+01,							\
      /* 2^-20 */ 9.5367431640625e-07,						\
      /* 2^-44 */ 5.6843418860808015e-14,					\
      /* 2^-68 */ 3.3881317890172014e-21,					\
      /* 2^-92 */ 2.0194839173657902e-28,					\
      /* 2^-116 */ 1.2037062152420224e-35पूर्ण;					\
    द्विगुन _a240, _b240, _c240, _d240, _e240, _f240, 				\
	   _g240, _h240, _i240, _j240, _k240;					\
    जोड़ अणु द्विगुन d; UDItype i; पूर्ण _l240, _m240, _n240, _o240,			\
				   _p240, _q240, _r240, _s240;			\
    UDItype _t240, _u240, _v240, _w240, _x240, _y240 = 0;			\
										\
    अगर (wfracbits < 106 || wfracbits > 120)					\
      पात();									\
										\
    setfetz;									\
										\
    _e240 = (द्विगुन)(दीर्घ)(X##_f0 & 0xffffff);					\
    _j240 = (द्विगुन)(दीर्घ)(Y##_f0 & 0xffffff);					\
    _d240 = (द्विगुन)(दीर्घ)((X##_f0 >> 24) & 0xffffff);				\
    _i240 = (द्विगुन)(दीर्घ)((Y##_f0 >> 24) & 0xffffff);				\
    _c240 = (द्विगुन)(दीर्घ)(((X##_f1 << 16) & 0xffffff) | (X##_f0 >> 48));	\
    _h240 = (द्विगुन)(दीर्घ)(((Y##_f1 << 16) & 0xffffff) | (Y##_f0 >> 48));	\
    _b240 = (द्विगुन)(दीर्घ)((X##_f1 >> 8) & 0xffffff);				\
    _g240 = (द्विगुन)(दीर्घ)((Y##_f1 >> 8) & 0xffffff);				\
    _a240 = (द्विगुन)(दीर्घ)(X##_f1 >> 32);					\
    _f240 = (द्विगुन)(दीर्घ)(Y##_f1 >> 32);					\
    _e240 *= _स्थिर[3];								\
    _j240 *= _स्थिर[3];								\
    _d240 *= _स्थिर[2];								\
    _i240 *= _स्थिर[2];								\
    _c240 *= _स्थिर[1];								\
    _h240 *= _स्थिर[1];								\
    _b240 *= _स्थिर[0];								\
    _g240 *= _स्थिर[0];								\
    _s240.d =							      _e240*_j240;\
    _r240.d =						_d240*_j240 + _e240*_i240;\
    _q240.d =				  _c240*_j240 + _d240*_i240 + _e240*_h240;\
    _p240.d =		    _b240*_j240 + _c240*_i240 + _d240*_h240 + _e240*_g240;\
    _o240.d = _a240*_j240 + _b240*_i240 + _c240*_h240 + _d240*_g240 + _e240*_f240;\
    _n240.d = _a240*_i240 + _b240*_h240 + _c240*_g240 + _d240*_f240;		\
    _m240.d = _a240*_h240 + _b240*_g240 + _c240*_f240;				\
    _l240.d = _a240*_g240 + _b240*_f240;					\
    _k240 =   _a240*_f240;							\
    _r240.d += _s240.d;								\
    _q240.d += _r240.d;								\
    _p240.d += _q240.d;								\
    _o240.d += _p240.d;								\
    _n240.d += _o240.d;								\
    _m240.d += _n240.d;								\
    _l240.d += _m240.d;								\
    _k240 += _l240.d;								\
    _s240.d -= ((_स्थिर[10]+_s240.d)-_स्थिर[10]);				\
    _r240.d -= ((_स्थिर[9]+_r240.d)-_स्थिर[9]);					\
    _q240.d -= ((_स्थिर[8]+_q240.d)-_स्थिर[8]);					\
    _p240.d -= ((_स्थिर[7]+_p240.d)-_स्थिर[7]);					\
    _o240.d += _स्थिर[7];							\
    _n240.d += _स्थिर[6];							\
    _m240.d += _स्थिर[5];							\
    _l240.d += _स्थिर[4];							\
    अगर (_s240.d != 0.0) _y240 = 1;						\
    अगर (_r240.d != 0.0) _y240 = 1;						\
    अगर (_q240.d != 0.0) _y240 = 1;						\
    अगर (_p240.d != 0.0) _y240 = 1;						\
    _t240 = (DItype)_k240;							\
    _u240 = _l240.i;								\
    _v240 = _m240.i;								\
    _w240 = _n240.i;								\
    _x240 = _o240.i;								\
    R##_f1 = (_t240 << (128 - (wfracbits - 1)))					\
	     | ((_u240 & 0xffffff) >> ((wfracbits - 1) - 104));			\
    R##_f0 = ((_u240 & 0xffffff) << (168 - (wfracbits - 1)))			\
    	     | ((_v240 & 0xffffff) << (144 - (wfracbits - 1)))			\
    	     | ((_w240 & 0xffffff) << (120 - (wfracbits - 1)))			\
    	     | ((_x240 & 0xffffff) >> ((wfracbits - 1) - 96))			\
    	     | _y240;								\
    resetfe;									\
  पूर्ण जबतक (0)

/*
 * Division algorithms:
 */

#घोषणा _FP_DIV_MEAT_2_uभाग(fs, R, X, Y)				\
  करो अणु									\
    _FP_W_TYPE _n_f2, _n_f1, _n_f0, _r_f1, _r_f0, _m_f1, _m_f0;		\
    अगर (_FP_FRAC_GT_2(X, Y))						\
      अणु									\
	_n_f2 = X##_f1 >> 1;						\
	_n_f1 = X##_f1 << (_FP_W_TYPE_SIZE - 1) | X##_f0 >> 1;		\
	_n_f0 = X##_f0 << (_FP_W_TYPE_SIZE - 1);			\
      पूर्ण									\
    अन्यथा								\
      अणु									\
	R##_e--;							\
	_n_f2 = X##_f1;							\
	_n_f1 = X##_f0;							\
	_n_f0 = 0;							\
      पूर्ण									\
									\
    /* Normalize, i.e. make the most signअगरicant bit of the 		\
       denominator set. */						\
    _FP_FRAC_SLL_2(Y, _FP_WFRACXBITS_##fs);				\
									\
    uभाग_qrnnd(R##_f1, _r_f1, _n_f2, _n_f1, Y##_f1);			\
    umul_ppmm(_m_f1, _m_f0, R##_f1, Y##_f0);				\
    _r_f0 = _n_f0;							\
    अगर (_FP_FRAC_GT_2(_m, _r))						\
      अणु									\
	R##_f1--;							\
	_FP_FRAC_ADD_2(_r, Y, _r);					\
	अगर (_FP_FRAC_GE_2(_r, Y) && _FP_FRAC_GT_2(_m, _r))		\
	  अणु								\
	    R##_f1--;							\
	    _FP_FRAC_ADD_2(_r, Y, _r);					\
	  पूर्ण								\
      पूर्ण									\
    _FP_FRAC_DEC_2(_r, _m);						\
									\
    अगर (_r_f1 == Y##_f1)						\
      अणु									\
	/* This is a special हाल, not an optimization			\
	   (_r/Y##_f1 would not fit पूर्णांकo UWtype).			\
	   As _r is guaranteed to be < Y,  R##_f0 can be either		\
	   (UWtype)-1 or (UWtype)-2.  But as we know what kind		\
	   of bits it is (sticky, guard, round),  we करोn't care.	\
	   We also करोn't care what the reminder is,  because the	\
	   guard bit will be set anyway.  -jj */			\
	R##_f0 = -1;							\
      पूर्ण									\
    अन्यथा								\
      अणु									\
	uभाग_qrnnd(R##_f0, _r_f1, _r_f1, _r_f0, Y##_f1);		\
	umul_ppmm(_m_f1, _m_f0, R##_f0, Y##_f0);			\
	_r_f0 = 0;							\
	अगर (_FP_FRAC_GT_2(_m, _r))					\
	  अणु								\
	    R##_f0--;							\
	    _FP_FRAC_ADD_2(_r, Y, _r);					\
	    अगर (_FP_FRAC_GE_2(_r, Y) && _FP_FRAC_GT_2(_m, _r))		\
	      अणु								\
		R##_f0--;						\
		_FP_FRAC_ADD_2(_r, Y, _r);				\
	      पूर्ण								\
	  पूर्ण								\
	अगर (!_FP_FRAC_EQ_2(_r, _m))					\
	  R##_f0 |= _FP_WORK_STICKY;					\
      पूर्ण									\
  पूर्ण जबतक (0)


#घोषणा _FP_DIV_MEAT_2_gmp(fs, R, X, Y)					\
  करो अणु									\
    _FP_W_TYPE _x[4], _y[2], _z[4];					\
    _y[0] = Y##_f0; _y[1] = Y##_f1;					\
    _x[0] = _x[3] = 0;							\
    अगर (_FP_FRAC_GT_2(X, Y))						\
      अणु									\
	R##_e++;							\
	_x[1] = (X##_f0 << (_FP_WFRACBITS_##fs-1 - _FP_W_TYPE_SIZE) |	\
		 X##_f1 >> (_FP_W_TYPE_SIZE -				\
			    (_FP_WFRACBITS_##fs-1 - _FP_W_TYPE_SIZE)));	\
	_x[2] = X##_f1 << (_FP_WFRACBITS_##fs-1 - _FP_W_TYPE_SIZE);	\
      पूर्ण									\
    अन्यथा								\
      अणु									\
	_x[1] = (X##_f0 << (_FP_WFRACBITS_##fs - _FP_W_TYPE_SIZE) |	\
		 X##_f1 >> (_FP_W_TYPE_SIZE -				\
			    (_FP_WFRACBITS_##fs - _FP_W_TYPE_SIZE)));	\
	_x[2] = X##_f1 << (_FP_WFRACBITS_##fs - _FP_W_TYPE_SIZE);	\
      पूर्ण									\
									\
    (व्योम) mpn_भागrem (_z, 0, _x, 4, _y, 2);				\
    R##_f1 = _z[1];							\
    R##_f0 = _z[0] | ((_x[0] | _x[1]) != 0);				\
  पूर्ण जबतक (0)


/*
 * Square root algorithms:
 * We have just one right now, maybe Newton approximation
 * should be added क्रम those machines where भागision is fast.
 */
 
#घोषणा _FP_SQRT_MEAT_2(R, S, T, X, q)			\
  करो अणु							\
    जबतक (q)						\
      अणु							\
	T##_f1 = S##_f1 + q;				\
	अगर (T##_f1 <= X##_f1)				\
	  अणु						\
	    S##_f1 = T##_f1 + q;			\
	    X##_f1 -= T##_f1;				\
	    R##_f1 += q;				\
	  पूर्ण						\
	_FP_FRAC_SLL_2(X, 1);				\
	q >>= 1;					\
      पूर्ण							\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);		\
    जबतक (q != _FP_WORK_ROUND)				\
      अणु							\
	T##_f0 = S##_f0 + q;				\
	T##_f1 = S##_f1;				\
	अगर (T##_f1 < X##_f1 || 				\
	    (T##_f1 == X##_f1 && T##_f0 <= X##_f0))	\
	  अणु						\
	    S##_f0 = T##_f0 + q;			\
	    S##_f1 += (T##_f0 > S##_f0);		\
	    _FP_FRAC_DEC_2(X, T);			\
	    R##_f0 += q;				\
	  पूर्ण						\
	_FP_FRAC_SLL_2(X, 1);				\
	q >>= 1;					\
      पूर्ण							\
    अगर (X##_f0 | X##_f1)				\
      अणु							\
	अगर (S##_f1 < X##_f1 || 				\
	    (S##_f1 == X##_f1 && S##_f0 < X##_f0))	\
	  R##_f0 |= _FP_WORK_ROUND;			\
	R##_f0 |= _FP_WORK_STICKY;			\
      पूर्ण							\
  पूर्ण जबतक (0)


/*
 * Assembly/disassembly क्रम converting to/from पूर्णांकegral types.  
 * No shअगरting or overflow handled here.
 */

#घोषणा _FP_FRAC_ASSEMBLE_2(r, X, rsize)	\
	(व्योम) (((rsize) <= _FP_W_TYPE_SIZE)	\
		? (अणु (r) = X##_f0; पूर्ण)		\
		: (अणु				\
		     (r) = X##_f1;		\
		     (r) <<= _FP_W_TYPE_SIZE;	\
		     (r) += X##_f0;		\
		    पूर्ण))

#घोषणा _FP_FRAC_DISASSEMBLE_2(X, r, rsize)				\
  करो अणु									\
    X##_f0 = r;								\
    X##_f1 = (rsize <= _FP_W_TYPE_SIZE ? 0 : r >> _FP_W_TYPE_SIZE);	\
  पूर्ण जबतक (0)

/*
 * Convert FP values between word sizes
 */

#घोषणा _FP_FRAC_CONV_1_2(dfs, sfs, D, S)				\
  करो अणु									\
    अगर (S##_c != FP_CLS_न_अंक)						\
      _FP_FRAC_SRS_2(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs),	\
		     _FP_WFRACBITS_##sfs);				\
    अन्यथा								\
      _FP_FRAC_SRL_2(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs));	\
    D##_f = S##_f0;							\
  पूर्ण जबतक (0)

#घोषणा _FP_FRAC_CONV_2_1(dfs, sfs, D, S)				\
  करो अणु									\
    D##_f0 = S##_f;							\
    D##_f1 = 0;								\
    _FP_FRAC_SLL_2(D, (_FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs));	\
  पूर्ण जबतक (0)

#पूर्ण_अगर
