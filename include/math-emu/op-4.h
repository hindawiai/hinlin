<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Basic four-word fraction declaration and manipulation.
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

#अगर_अघोषित __MATH_EMU_OP_4_H__
#घोषणा __MATH_EMU_OP_4_H__

#घोषणा _FP_FRAC_DECL_4(X)	_FP_W_TYPE X##_f[4]
#घोषणा _FP_FRAC_COPY_4(D,S)			\
  (D##_f[0] = S##_f[0], D##_f[1] = S##_f[1],	\
   D##_f[2] = S##_f[2], D##_f[3] = S##_f[3])
#घोषणा _FP_FRAC_SET_4(X,I)	__FP_FRAC_SET_4(X, I)
#घोषणा _FP_FRAC_HIGH_4(X)	(X##_f[3])
#घोषणा _FP_FRAC_LOW_4(X)	(X##_f[0])
#घोषणा _FP_FRAC_WORD_4(X,w)	(X##_f[w])

#घोषणा _FP_FRAC_SLL_4(X,N)						\
  करो अणु									\
    _FP_I_TYPE _up, _करोwn, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _up = (N) % _FP_W_TYPE_SIZE;					\
    _करोwn = _FP_W_TYPE_SIZE - _up;					\
    अगर (!_up)								\
      क्रम (_i = 3; _i >= _skip; --_i)					\
	X##_f[_i] = X##_f[_i-_skip];					\
    अन्यथा								\
      अणु									\
	क्रम (_i = 3; _i > _skip; --_i)					\
	  X##_f[_i] = X##_f[_i-_skip] << _up				\
		      | X##_f[_i-_skip-1] >> _करोwn;			\
	X##_f[_i--] = X##_f[0] << _up; 					\
      पूर्ण									\
    क्रम (; _i >= 0; --_i)						\
      X##_f[_i] = 0;							\
  पूर्ण जबतक (0)

/* This one was broken too */
#घोषणा _FP_FRAC_SRL_4(X,N)						\
  करो अणु									\
    _FP_I_TYPE _up, _करोwn, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _करोwn = (N) % _FP_W_TYPE_SIZE;					\
    _up = _FP_W_TYPE_SIZE - _करोwn;					\
    अगर (!_करोwn)								\
      क्रम (_i = 0; _i <= 3-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    अन्यथा								\
      अणु									\
	क्रम (_i = 0; _i < 3-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _करोwn				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[3] >> _करोwn;				\
      पूर्ण									\
    क्रम (; _i < 4; ++_i)						\
      X##_f[_i] = 0;							\
  पूर्ण जबतक (0)


/* Right shअगरt with sticky-lsb. 
 * What this actually means is that we करो a standard right-shअगरt,
 * but that अगर any of the bits that fall off the right hand side
 * were one then we always set the LSbit.
 */
#घोषणा _FP_FRAC_SRS_4(X,N,size)					\
  करो अणु									\
    _FP_I_TYPE _up, _करोwn, _skip, _i;					\
    _FP_W_TYPE _s;							\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _करोwn = (N) % _FP_W_TYPE_SIZE;					\
    _up = _FP_W_TYPE_SIZE - _करोwn;					\
    क्रम (_s = _i = 0; _i < _skip; ++_i)					\
      _s |= X##_f[_i];							\
    _s |= X##_f[_i] << _up;						\
/* s is now != 0 अगर we want to set the LSbit */				\
    अगर (!_करोwn)								\
      क्रम (_i = 0; _i <= 3-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    अन्यथा								\
      अणु									\
	क्रम (_i = 0; _i < 3-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _करोwn				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[3] >> _करोwn;				\
      पूर्ण									\
    क्रम (; _i < 4; ++_i)						\
      X##_f[_i] = 0;							\
    /* करोn't fix the LSB until the very end when we're sure f[0] is stable */	\
    X##_f[0] |= (_s != 0);						\
  पूर्ण जबतक (0)

#घोषणा _FP_FRAC_ADD_4(R,X,Y)						\
  __FP_FRAC_ADD_4(R##_f[3], R##_f[2], R##_f[1], R##_f[0],		\
		  X##_f[3], X##_f[2], X##_f[1], X##_f[0],		\
		  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])

#घोषणा _FP_FRAC_SUB_4(R,X,Y)						\
  __FP_FRAC_SUB_4(R##_f[3], R##_f[2], R##_f[1], R##_f[0],		\
		  X##_f[3], X##_f[2], X##_f[1], X##_f[0],		\
		  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])

#घोषणा _FP_FRAC_DEC_4(X,Y)						\
  __FP_FRAC_DEC_4(X##_f[3], X##_f[2], X##_f[1], X##_f[0],		\
		  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])

#घोषणा _FP_FRAC_ADDI_4(X,I)						\
  __FP_FRAC_ADDI_4(X##_f[3], X##_f[2], X##_f[1], X##_f[0], I)

#घोषणा _FP_ZEROFRAC_4  0,0,0,0
#घोषणा _FP_MINFRAC_4   0,0,0,1
#घोषणा _FP_MAXFRAC_4	(~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0), (~(_FP_WS_TYPE)0)

#घोषणा _FP_FRAC_ZEROP_4(X)     ((X##_f[0] | X##_f[1] | X##_f[2] | X##_f[3]) == 0)
#घोषणा _FP_FRAC_NEGP_4(X)      ((_FP_WS_TYPE)X##_f[3] < 0)
#घोषणा _FP_FRAC_OVERP_4(fs,X)  (_FP_FRAC_HIGH_##fs(X) & _FP_OVERFLOW_##fs)
#घोषणा _FP_FRAC_CLEAR_OVERP_4(fs,X)  (_FP_FRAC_HIGH_##fs(X) &= ~_FP_OVERFLOW_##fs)

#घोषणा _FP_FRAC_EQ_4(X,Y)				\
 (X##_f[0] == Y##_f[0] && X##_f[1] == Y##_f[1]		\
  && X##_f[2] == Y##_f[2] && X##_f[3] == Y##_f[3])

#घोषणा _FP_FRAC_GT_4(X,Y)				\
 (X##_f[3] > Y##_f[3] ||				\
  (X##_f[3] == Y##_f[3] && (X##_f[2] > Y##_f[2] ||	\
   (X##_f[2] == Y##_f[2] && (X##_f[1] > Y##_f[1] ||	\
    (X##_f[1] == Y##_f[1] && X##_f[0] > Y##_f[0])	\
   ))							\
  ))							\
 )

#घोषणा _FP_FRAC_GE_4(X,Y)				\
 (X##_f[3] > Y##_f[3] ||				\
  (X##_f[3] == Y##_f[3] && (X##_f[2] > Y##_f[2] ||	\
   (X##_f[2] == Y##_f[2] && (X##_f[1] > Y##_f[1] ||	\
    (X##_f[1] == Y##_f[1] && X##_f[0] >= Y##_f[0])	\
   ))							\
  ))							\
 )


#घोषणा _FP_FRAC_CLZ_4(R,X)		\
  करो अणु					\
    अगर (X##_f[3])			\
    अणु					\
	__FP_CLZ(R,X##_f[3]);		\
    पूर्ण					\
    अन्यथा अगर (X##_f[2])			\
    अणु					\
	__FP_CLZ(R,X##_f[2]);		\
	R += _FP_W_TYPE_SIZE;		\
    पूर्ण					\
    अन्यथा अगर (X##_f[1])			\
    अणु					\
	__FP_CLZ(R,X##_f[2]);		\
	R += _FP_W_TYPE_SIZE*2;		\
    पूर्ण					\
    अन्यथा				\
    अणु					\
	__FP_CLZ(R,X##_f[0]);		\
	R += _FP_W_TYPE_SIZE*3;		\
    पूर्ण					\
  पूर्ण जबतक(0)


#घोषणा _FP_UNPACK_RAW_4(fs, X, val)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs _flo; _flo.flt = (val);		\
    X##_f[0] = _flo.bits.frac0;					\
    X##_f[1] = _flo.bits.frac1;					\
    X##_f[2] = _flo.bits.frac2;					\
    X##_f[3] = _flo.bits.frac3;					\
    X##_e  = _flo.bits.exp;					\
    X##_s  = _flo.bits.sign;					\
  पूर्ण जबतक (0)

#घोषणा _FP_UNPACK_RAW_4_P(fs, X, val)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs *_flo =				\
      (जोड़ _FP_UNION_##fs *)(val);				\
								\
    X##_f[0] = _flo->bits.frac0;				\
    X##_f[1] = _flo->bits.frac1;				\
    X##_f[2] = _flo->bits.frac2;				\
    X##_f[3] = _flo->bits.frac3;				\
    X##_e  = _flo->bits.exp;					\
    X##_s  = _flo->bits.sign;					\
  पूर्ण जबतक (0)

#घोषणा _FP_PACK_RAW_4(fs, val, X)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs _flo;					\
    _flo.bits.frac0 = X##_f[0];					\
    _flo.bits.frac1 = X##_f[1];					\
    _flo.bits.frac2 = X##_f[2];					\
    _flo.bits.frac3 = X##_f[3];					\
    _flo.bits.exp   = X##_e;					\
    _flo.bits.sign  = X##_s;					\
    (val) = _flo.flt;				   		\
  पूर्ण जबतक (0)

#घोषणा _FP_PACK_RAW_4_P(fs, val, X)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs *_flo =				\
      (जोड़ _FP_UNION_##fs *)(val);				\
								\
    _flo->bits.frac0 = X##_f[0];				\
    _flo->bits.frac1 = X##_f[1];				\
    _flo->bits.frac2 = X##_f[2];				\
    _flo->bits.frac3 = X##_f[3];				\
    _flo->bits.exp   = X##_e;					\
    _flo->bits.sign  = X##_s;					\
  पूर्ण जबतक (0)

/*
 * Multiplication algorithms:
 */

/* Given a 1W * 1W => 2W primitive, करो the extended multiplication.  */

#घोषणा _FP_MUL_MEAT_4_wide(wfracbits, R, X, Y, करोit)			    \
  करो अणु									    \
    _FP_FRAC_DECL_8(_z); _FP_FRAC_DECL_2(_b); _FP_FRAC_DECL_2(_c);	    \
    _FP_FRAC_DECL_2(_d); _FP_FRAC_DECL_2(_e); _FP_FRAC_DECL_2(_f);	    \
									    \
    करोit(_FP_FRAC_WORD_8(_z,1), _FP_FRAC_WORD_8(_z,0), X##_f[0], Y##_f[0]); \
    करोit(_b_f1, _b_f0, X##_f[0], Y##_f[1]);				    \
    करोit(_c_f1, _c_f0, X##_f[1], Y##_f[0]);				    \
    करोit(_d_f1, _d_f0, X##_f[1], Y##_f[1]);				    \
    करोit(_e_f1, _e_f0, X##_f[0], Y##_f[2]);				    \
    करोit(_f_f1, _f_f0, X##_f[2], Y##_f[0]);				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,3),_FP_FRAC_WORD_8(_z,2),	    \
		    _FP_FRAC_WORD_8(_z,1), 0,_b_f1,_b_f0,		    \
		    0,0,_FP_FRAC_WORD_8(_z,1));				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,3),_FP_FRAC_WORD_8(_z,2),	    \
		    _FP_FRAC_WORD_8(_z,1), 0,_c_f1,_c_f0,		    \
		    _FP_FRAC_WORD_8(_z,3),_FP_FRAC_WORD_8(_z,2),	    \
		    _FP_FRAC_WORD_8(_z,1));				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,4),_FP_FRAC_WORD_8(_z,3),	    \
		    _FP_FRAC_WORD_8(_z,2), 0,_d_f1,_d_f0,		    \
		    0,_FP_FRAC_WORD_8(_z,3),_FP_FRAC_WORD_8(_z,2));	    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,4),_FP_FRAC_WORD_8(_z,3),	    \
		    _FP_FRAC_WORD_8(_z,2), 0,_e_f1,_e_f0,		    \
		    _FP_FRAC_WORD_8(_z,4),_FP_FRAC_WORD_8(_z,3),	    \
		    _FP_FRAC_WORD_8(_z,2));				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,4),_FP_FRAC_WORD_8(_z,3),	    \
		    _FP_FRAC_WORD_8(_z,2), 0,_f_f1,_f_f0,		    \
		    _FP_FRAC_WORD_8(_z,4),_FP_FRAC_WORD_8(_z,3),	    \
		    _FP_FRAC_WORD_8(_z,2));				    \
    करोit(_b_f1, _b_f0, X##_f[0], Y##_f[3]);				    \
    करोit(_c_f1, _c_f0, X##_f[3], Y##_f[0]);				    \
    करोit(_d_f1, _d_f0, X##_f[1], Y##_f[2]);				    \
    करोit(_e_f1, _e_f0, X##_f[2], Y##_f[1]);				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4),	    \
		    _FP_FRAC_WORD_8(_z,3), 0,_b_f1,_b_f0,		    \
		    0,_FP_FRAC_WORD_8(_z,4),_FP_FRAC_WORD_8(_z,3));	    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4),	    \
		    _FP_FRAC_WORD_8(_z,3), 0,_c_f1,_c_f0,		    \
		    _FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4),	    \
		    _FP_FRAC_WORD_8(_z,3));				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4),	    \
		    _FP_FRAC_WORD_8(_z,3), 0,_d_f1,_d_f0,		    \
		    _FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4),	    \
		    _FP_FRAC_WORD_8(_z,3));				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4),	    \
		    _FP_FRAC_WORD_8(_z,3), 0,_e_f1,_e_f0,		    \
		    _FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4),	    \
		    _FP_FRAC_WORD_8(_z,3));				    \
    करोit(_b_f1, _b_f0, X##_f[2], Y##_f[2]);				    \
    करोit(_c_f1, _c_f0, X##_f[1], Y##_f[3]);				    \
    करोit(_d_f1, _d_f0, X##_f[3], Y##_f[1]);				    \
    करोit(_e_f1, _e_f0, X##_f[2], Y##_f[3]);				    \
    करोit(_f_f1, _f_f0, X##_f[3], Y##_f[2]);				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,6),_FP_FRAC_WORD_8(_z,5),	    \
		    _FP_FRAC_WORD_8(_z,4), 0,_b_f1,_b_f0,		    \
		    0,_FP_FRAC_WORD_8(_z,5),_FP_FRAC_WORD_8(_z,4));	    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,6),_FP_FRAC_WORD_8(_z,5),	    \
		    _FP_FRAC_WORD_8(_z,4), 0,_c_f1,_c_f0,		    \
		    _FP_FRAC_WORD_8(_z,6),_FP_FRAC_WORD_8(_z,5),	    \
		    _FP_FRAC_WORD_8(_z,4));				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,6),_FP_FRAC_WORD_8(_z,5),	    \
		    _FP_FRAC_WORD_8(_z,4), 0,_d_f1,_d_f0,		    \
		    _FP_FRAC_WORD_8(_z,6),_FP_FRAC_WORD_8(_z,5),	    \
		    _FP_FRAC_WORD_8(_z,4));				    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,7),_FP_FRAC_WORD_8(_z,6),	    \
		    _FP_FRAC_WORD_8(_z,5), 0,_e_f1,_e_f0,		    \
		    0,_FP_FRAC_WORD_8(_z,6),_FP_FRAC_WORD_8(_z,5));	    \
    __FP_FRAC_ADD_3(_FP_FRAC_WORD_8(_z,7),_FP_FRAC_WORD_8(_z,6),	    \
		    _FP_FRAC_WORD_8(_z,5), 0,_f_f1,_f_f0,		    \
		    _FP_FRAC_WORD_8(_z,7),_FP_FRAC_WORD_8(_z,6),	    \
		    _FP_FRAC_WORD_8(_z,5));				    \
    करोit(_b_f1, _b_f0, X##_f[3], Y##_f[3]);				    \
    __FP_FRAC_ADD_2(_FP_FRAC_WORD_8(_z,7),_FP_FRAC_WORD_8(_z,6),	    \
		    _b_f1,_b_f0,					    \
		    _FP_FRAC_WORD_8(_z,7),_FP_FRAC_WORD_8(_z,6));	    \
									    \
    /* Normalize since we know where the msb of the multiplicands	    \
       were (bit B), we know that the msb of the of the product is	    \
       at either 2B or 2B-1.  */					    \
    _FP_FRAC_SRS_8(_z, wfracbits-1, 2*wfracbits);			    \
    __FP_FRAC_SET_4(R, _FP_FRAC_WORD_8(_z,3), _FP_FRAC_WORD_8(_z,2),	    \
		    _FP_FRAC_WORD_8(_z,1), _FP_FRAC_WORD_8(_z,0));	    \
  पूर्ण जबतक (0)

#घोषणा _FP_MUL_MEAT_4_gmp(wfracbits, R, X, Y)				    \
  करो अणु									    \
    _FP_FRAC_DECL_8(_z);						    \
									    \
    mpn_mul_n(_z_f, _x_f, _y_f, 4);					    \
									    \
    /* Normalize since we know where the msb of the multiplicands	    \
       were (bit B), we know that the msb of the of the product is	    \
       at either 2B or 2B-1.  */					    \
    _FP_FRAC_SRS_8(_z, wfracbits-1, 2*wfracbits);	 		    \
    __FP_FRAC_SET_4(R, _FP_FRAC_WORD_8(_z,3), _FP_FRAC_WORD_8(_z,2),	    \
		    _FP_FRAC_WORD_8(_z,1), _FP_FRAC_WORD_8(_z,0));	    \
  पूर्ण जबतक (0)

/*
 * Helper utility क्रम _FP_DIV_MEAT_4_uभाग:
 * pppp = m * nnn
 */
#घोषणा umul_ppppmnnn(p3,p2,p1,p0,m,n2,n1,n0)				    \
  करो अणु									    \
    UWtype _t;								    \
    umul_ppmm(p1,p0,m,n0);						    \
    umul_ppmm(p2,_t,m,n1);						    \
    __FP_FRAC_ADDI_2(p2,p1,_t);						    \
    umul_ppmm(p3,_t,m,n2);						    \
    __FP_FRAC_ADDI_2(p3,p2,_t);						    \
  पूर्ण जबतक (0)

/*
 * Division algorithms:
 */

#घोषणा _FP_DIV_MEAT_4_uभाग(fs, R, X, Y)				    \
  करो अणु									    \
    पूर्णांक _i;								    \
    _FP_FRAC_DECL_4(_n); _FP_FRAC_DECL_4(_m);				    \
    _FP_FRAC_SET_4(_n, _FP_ZEROFRAC_4);					    \
    अगर (_FP_FRAC_GT_4(X, Y))						    \
      अणु									    \
	_n_f[3] = X##_f[0] << (_FP_W_TYPE_SIZE - 1);			    \
	_FP_FRAC_SRL_4(X, 1);						    \
      पूर्ण									    \
    अन्यथा								    \
      R##_e--;								    \
									    \
    /* Normalize, i.e. make the most signअगरicant bit of the 		    \
       denominator set. */						    \
    _FP_FRAC_SLL_4(Y, _FP_WFRACXBITS_##fs);				    \
									    \
    क्रम (_i = 3; ; _i--)						    \
      अणु									    \
        अगर (X##_f[3] == Y##_f[3])					    \
          अणु								    \
            /* This is a special हाल, not an optimization		    \
               (X##_f[3]/Y##_f[3] would not fit पूर्णांकo UWtype).		    \
               As X## is guaranteed to be < Y,  R##_f[_i] can be either	    \
               (UWtype)-1 or (UWtype)-2.  */				    \
            R##_f[_i] = -1;						    \
            अगर (!_i)							    \
	      अवरोध;							    \
            __FP_FRAC_SUB_4(X##_f[3], X##_f[2], X##_f[1], X##_f[0],	    \
			    Y##_f[2], Y##_f[1], Y##_f[0], 0,		    \
			    X##_f[2], X##_f[1], X##_f[0], _n_f[_i]);	    \
            _FP_FRAC_SUB_4(X, Y, X);					    \
            अगर (X##_f[3] > Y##_f[3])					    \
              अणु								    \
                R##_f[_i] = -2;						    \
                _FP_FRAC_ADD_4(X, Y, X);				    \
              पूर्ण								    \
          पूर्ण								    \
        अन्यथा								    \
          अणु								    \
            uभाग_qrnnd(R##_f[_i], X##_f[3], X##_f[3], X##_f[2], Y##_f[3]);  \
            umul_ppppmnnn(_m_f[3], _m_f[2], _m_f[1], _m_f[0],		    \
			  R##_f[_i], Y##_f[2], Y##_f[1], Y##_f[0]);	    \
            X##_f[2] = X##_f[1];					    \
            X##_f[1] = X##_f[0];					    \
            X##_f[0] = _n_f[_i];					    \
            अगर (_FP_FRAC_GT_4(_m, X))					    \
              अणु								    \
                R##_f[_i]--;						    \
                _FP_FRAC_ADD_4(X, Y, X);				    \
                अगर (_FP_FRAC_GE_4(X, Y) && _FP_FRAC_GT_4(_m, X))	    \
                  अणु							    \
		    R##_f[_i]--;					    \
		    _FP_FRAC_ADD_4(X, Y, X);				    \
                  पूर्ण							    \
              पूर्ण								    \
            _FP_FRAC_DEC_4(X, _m);					    \
            अगर (!_i)							    \
	      अणु								    \
		अगर (!_FP_FRAC_EQ_4(X, _m))				    \
		  R##_f[0] |= _FP_WORK_STICKY;				    \
		अवरोध;							    \
	      पूर्ण								    \
          पूर्ण								    \
      पूर्ण									    \
  पूर्ण जबतक (0)


/*
 * Square root algorithms:
 * We have just one right now, maybe Newton approximation
 * should be added क्रम those machines where भागision is fast.
 */
 
#घोषणा _FP_SQRT_MEAT_4(R, S, T, X, q)				\
  करो अणु								\
    जबतक (q)							\
      अणु								\
	T##_f[3] = S##_f[3] + q;				\
	अगर (T##_f[3] <= X##_f[3])				\
	  अणु							\
	    S##_f[3] = T##_f[3] + q;				\
	    X##_f[3] -= T##_f[3];				\
	    R##_f[3] += q;					\
	  पूर्ण							\
	_FP_FRAC_SLL_4(X, 1);					\
	q >>= 1;						\
      पूर्ण								\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);			\
    जबतक (q)							\
      अणु								\
	T##_f[2] = S##_f[2] + q;				\
	T##_f[3] = S##_f[3];					\
	अगर (T##_f[3] < X##_f[3] || 				\
	    (T##_f[3] == X##_f[3] && T##_f[2] <= X##_f[2]))	\
	  अणु							\
	    S##_f[2] = T##_f[2] + q;				\
	    S##_f[3] += (T##_f[2] > S##_f[2]);			\
	    __FP_FRAC_DEC_2(X##_f[3], X##_f[2],			\
			    T##_f[3], T##_f[2]);		\
	    R##_f[2] += q;					\
	  पूर्ण							\
	_FP_FRAC_SLL_4(X, 1);					\
	q >>= 1;						\
      पूर्ण								\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);			\
    जबतक (q)							\
      अणु								\
	T##_f[1] = S##_f[1] + q;				\
	T##_f[2] = S##_f[2];					\
	T##_f[3] = S##_f[3];					\
	अगर (T##_f[3] < X##_f[3] || 				\
	    (T##_f[3] == X##_f[3] && (T##_f[2] < X##_f[2] ||	\
	     (T##_f[2] == X##_f[2] && T##_f[1] <= X##_f[1]))))	\
	  अणु							\
	    S##_f[1] = T##_f[1] + q;				\
	    S##_f[2] += (T##_f[1] > S##_f[1]);			\
	    S##_f[3] += (T##_f[2] > S##_f[2]);			\
	    __FP_FRAC_DEC_3(X##_f[3], X##_f[2], X##_f[1],	\
	    		    T##_f[3], T##_f[2], T##_f[1]);	\
	    R##_f[1] += q;					\
	  पूर्ण							\
	_FP_FRAC_SLL_4(X, 1);					\
	q >>= 1;						\
      पूर्ण								\
    q = (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE - 1);			\
    जबतक (q != _FP_WORK_ROUND)					\
      अणु								\
	T##_f[0] = S##_f[0] + q;				\
	T##_f[1] = S##_f[1];					\
	T##_f[2] = S##_f[2];					\
	T##_f[3] = S##_f[3];					\
	अगर (_FP_FRAC_GE_4(X,T))					\
	  अणु							\
	    S##_f[0] = T##_f[0] + q;				\
	    S##_f[1] += (T##_f[0] > S##_f[0]);			\
	    S##_f[2] += (T##_f[1] > S##_f[1]);			\
	    S##_f[3] += (T##_f[2] > S##_f[2]);			\
	    _FP_FRAC_DEC_4(X, T);				\
	    R##_f[0] += q;					\
	  पूर्ण							\
	_FP_FRAC_SLL_4(X, 1);					\
	q >>= 1;						\
      पूर्ण								\
    अगर (!_FP_FRAC_ZEROP_4(X))					\
      अणु								\
	अगर (_FP_FRAC_GT_4(X,S))					\
	  R##_f[0] |= _FP_WORK_ROUND;				\
	R##_f[0] |= _FP_WORK_STICKY;				\
      पूर्ण								\
  पूर्ण जबतक (0)


/*
 * Internals 
 */

#घोषणा __FP_FRAC_SET_4(X,I3,I2,I1,I0)					\
  (X##_f[3] = I3, X##_f[2] = I2, X##_f[1] = I1, X##_f[0] = I0)

#अगर_अघोषित __FP_FRAC_ADD_3
#घोषणा __FP_FRAC_ADD_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)		\
  करो अणु								\
    पूर्णांक _c1, _c2;							\
    r0 = x0 + y0;						\
    _c1 = r0 < x0;						\
    r1 = x1 + y1;						\
    _c2 = r1 < x1;						\
    r1 += _c1;							\
    _c2 |= r1 < _c1;						\
    r2 = x2 + y2 + _c2;						\
  पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __FP_FRAC_ADD_4
#घोषणा __FP_FRAC_ADD_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)	\
  करो अणु								\
    पूर्णांक _c1, _c2, _c3;						\
    r0 = x0 + y0;						\
    _c1 = r0 < x0;						\
    r1 = x1 + y1;						\
    _c2 = r1 < x1;						\
    r1 += _c1;							\
    _c2 |= r1 < _c1;						\
    r2 = x2 + y2;						\
    _c3 = r2 < x2;						\
    r2 += _c2;							\
    _c3 |= r2 < _c2;						\
    r3 = x3 + y3 + _c3;						\
  पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __FP_FRAC_SUB_3
#घोषणा __FP_FRAC_SUB_3(r2,r1,r0,x2,x1,x0,y2,y1,y0)		\
  करो अणु								\
    पूर्णांक _c1, _c2;							\
    r0 = x0 - y0;						\
    _c1 = r0 > x0;						\
    r1 = x1 - y1;						\
    _c2 = r1 > x1;						\
    r1 -= _c1;							\
    _c2 |= r1 > _c1;						\
    r2 = x2 - y2 - _c2;						\
  पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __FP_FRAC_SUB_4
#घोषणा __FP_FRAC_SUB_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)	\
  करो अणु								\
    पूर्णांक _c1, _c2, _c3;						\
    r0 = x0 - y0;						\
    _c1 = r0 > x0;						\
    r1 = x1 - y1;						\
    _c2 = r1 > x1;						\
    r1 -= _c1;							\
    _c2 |= r1 > _c1;						\
    r2 = x2 - y2;						\
    _c3 = r2 > x2;						\
    r2 -= _c2;							\
    _c3 |= r2 > _c2;						\
    r3 = x3 - y3 - _c3;						\
  पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __FP_FRAC_DEC_3
#घोषणा __FP_FRAC_DEC_3(x2,x1,x0,y2,y1,y0)				\
  करो अणु									\
    UWtype _t0, _t1, _t2;						\
    _t0 = x0, _t1 = x1, _t2 = x2;					\
    __FP_FRAC_SUB_3 (x2, x1, x0, _t2, _t1, _t0, y2, y1, y0);		\
  पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __FP_FRAC_DEC_4
#घोषणा __FP_FRAC_DEC_4(x3,x2,x1,x0,y3,y2,y1,y0)			\
  करो अणु									\
    UWtype _t0, _t1, _t2, _t3;						\
    _t0 = x0, _t1 = x1, _t2 = x2, _t3 = x3;				\
    __FP_FRAC_SUB_4 (x3,x2,x1,x0,_t3,_t2,_t1,_t0, y3,y2,y1,y0);		\
  पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __FP_FRAC_ADDI_4
#घोषणा __FP_FRAC_ADDI_4(x3,x2,x1,x0,i)					\
  करो अणु									\
    UWtype _t;								\
    _t = ((x0 += i) < i);						\
    x1 += _t; _t = (x1 < _t);						\
    x2 += _t; _t = (x2 < _t);						\
    x3 += _t;								\
  पूर्ण जबतक (0)
#पूर्ण_अगर

/* Convert FP values between word sizes. This appears to be more
 * complicated than I'd have expected it to be, so these might be
 * wrong... These macros are in any हाल somewhat bogus because they
 * use inक्रमmation about what various FRAC_n variables look like 
 * पूर्णांकernally [eg, that 2 word vars are X_f0 and x_f1]. But so करो
 * the ones in op-2.h and op-1.h. 
 */
#घोषणा _FP_FRAC_CONV_1_4(dfs, sfs, D, S)				\
   करो अणु									\
     अगर (S##_c != FP_CLS_न_अंक)						\
       _FP_FRAC_SRS_4(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs),	\
			  _FP_WFRACBITS_##sfs);				\
     अन्यथा								\
       _FP_FRAC_SRL_4(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs));	\
     D##_f = S##_f[0];							\
  पूर्ण जबतक (0)

#घोषणा _FP_FRAC_CONV_2_4(dfs, sfs, D, S)				\
   करो अणु									\
     अगर (S##_c != FP_CLS_न_अंक)						\
       _FP_FRAC_SRS_4(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs),	\
		      _FP_WFRACBITS_##sfs);				\
     अन्यथा								\
       _FP_FRAC_SRL_4(S, (_FP_WFRACBITS_##sfs - _FP_WFRACBITS_##dfs));	\
     D##_f0 = S##_f[0];							\
     D##_f1 = S##_f[1];							\
  पूर्ण जबतक (0)

/* Assembly/disassembly क्रम converting to/from पूर्णांकegral types.  
 * No shअगरting or overflow handled here.
 */
/* Put the FP value X पूर्णांकo r, which is an पूर्णांकeger of size rsize. */
#घोषणा _FP_FRAC_ASSEMBLE_4(r, X, rsize)				\
  करो अणु									\
    अगर (rsize <= _FP_W_TYPE_SIZE)					\
      r = X##_f[0];							\
    अन्यथा अगर (rsize <= 2*_FP_W_TYPE_SIZE)				\
    अणु									\
      r = X##_f[1];							\
      r <<= _FP_W_TYPE_SIZE;						\
      r += X##_f[0];							\
    पूर्ण									\
    अन्यथा								\
    अणु									\
      /* I'm feeling lazy so we deal with पूर्णांक == 3words (implausible)*/	\
      /* and पूर्णांक == 4words as a single हाल.			 */	\
      r = X##_f[3];							\
      r <<= _FP_W_TYPE_SIZE;						\
      r += X##_f[2];							\
      r <<= _FP_W_TYPE_SIZE;						\
      r += X##_f[1];							\
      r <<= _FP_W_TYPE_SIZE;						\
      r += X##_f[0];							\
    पूर्ण									\
  पूर्ण जबतक (0)

/* "No disassemble Number Five!" */
/* move an पूर्णांकeger of size rsize पूर्णांकo X's fractional part. We rely on
 * the _f[] array consisting of words of size _FP_W_TYPE_SIZE to aव्योम
 * having to mask the values we store पूर्णांकo it.
 */
#घोषणा _FP_FRAC_DISASSEMBLE_4(X, r, rsize)				\
  करो अणु									\
    X##_f[0] = r;							\
    X##_f[1] = (rsize <= _FP_W_TYPE_SIZE ? 0 : r >> _FP_W_TYPE_SIZE);	\
    X##_f[2] = (rsize <= 2*_FP_W_TYPE_SIZE ? 0 : r >> 2*_FP_W_TYPE_SIZE); \
    X##_f[3] = (rsize <= 3*_FP_W_TYPE_SIZE ? 0 : r >> 3*_FP_W_TYPE_SIZE); \
  पूर्ण जबतक (0)

#घोषणा _FP_FRAC_CONV_4_1(dfs, sfs, D, S)				\
   करो अणु									\
     D##_f[0] = S##_f;							\
     D##_f[1] = D##_f[2] = D##_f[3] = 0;				\
     _FP_FRAC_SLL_4(D, (_FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs));	\
   पूर्ण जबतक (0)

#घोषणा _FP_FRAC_CONV_4_2(dfs, sfs, D, S)				\
   करो अणु									\
     D##_f[0] = S##_f0;							\
     D##_f[1] = S##_f1;							\
     D##_f[2] = D##_f[3] = 0;						\
     _FP_FRAC_SLL_4(D, (_FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs));	\
   पूर्ण जबतक (0)

#पूर्ण_अगर
