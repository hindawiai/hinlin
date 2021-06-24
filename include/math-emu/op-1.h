<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Basic one-word fraction declaration and manipulation.
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

#अगर_अघोषित    __MATH_EMU_OP_1_H__
#घोषणा    __MATH_EMU_OP_1_H__

#घोषणा _FP_FRAC_DECL_1(X)	_FP_W_TYPE X##_f=0
#घोषणा _FP_FRAC_COPY_1(D,S)	(D##_f = S##_f)
#घोषणा _FP_FRAC_SET_1(X,I)	(X##_f = I)
#घोषणा _FP_FRAC_HIGH_1(X)	(X##_f)
#घोषणा _FP_FRAC_LOW_1(X)	(X##_f)
#घोषणा _FP_FRAC_WORD_1(X,w)	(X##_f)

#घोषणा _FP_FRAC_ADDI_1(X,I)	(X##_f += I)
#घोषणा _FP_FRAC_SLL_1(X,N)			\
  करो अणु						\
    अगर (__builtin_स्थिरant_p(N) && (N) == 1)	\
      X##_f += X##_f;				\
    अन्यथा					\
      X##_f <<= (N);				\
  पूर्ण जबतक (0)
#घोषणा _FP_FRAC_SRL_1(X,N)	(X##_f >>= N)

/* Right shअगरt with sticky-lsb.  */
#घोषणा _FP_FRAC_SRS_1(X,N,sz)	__FP_FRAC_SRS_1(X##_f, N, sz)

#घोषणा __FP_FRAC_SRS_1(X,N,sz)						\
   (X = (X >> (N) | (__builtin_स्थिरant_p(N) && (N) == 1		\
		     ? X & 1 : (X << (_FP_W_TYPE_SIZE - (N))) != 0)))

#घोषणा _FP_FRAC_ADD_1(R,X,Y)	(R##_f = X##_f + Y##_f)
#घोषणा _FP_FRAC_SUB_1(R,X,Y)	(R##_f = X##_f - Y##_f)
#घोषणा _FP_FRAC_DEC_1(X,Y)	(X##_f -= Y##_f)
#घोषणा _FP_FRAC_CLZ_1(z, X)	__FP_CLZ(z, X##_f)

/* Predicates */
#घोषणा _FP_FRAC_NEGP_1(X)	((_FP_WS_TYPE)X##_f < 0)
#घोषणा _FP_FRAC_ZEROP_1(X)	(X##_f == 0)
#घोषणा _FP_FRAC_OVERP_1(fs,X)	(X##_f & _FP_OVERFLOW_##fs)
#घोषणा _FP_FRAC_CLEAR_OVERP_1(fs,X)	(X##_f &= ~_FP_OVERFLOW_##fs)
#घोषणा _FP_FRAC_EQ_1(X, Y)	(X##_f == Y##_f)
#घोषणा _FP_FRAC_GE_1(X, Y)	(X##_f >= Y##_f)
#घोषणा _FP_FRAC_GT_1(X, Y)	(X##_f > Y##_f)

#घोषणा _FP_ZEROFRAC_1		0
#घोषणा _FP_MINFRAC_1		1
#घोषणा _FP_MAXFRAC_1		(~(_FP_WS_TYPE)0)

/*
 * Unpack the raw bits of a native fp value.  Do not classअगरy or
 * normalize the data.
 */

#घोषणा _FP_UNPACK_RAW_1(fs, X, val)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs _flo; _flo.flt = (val);		\
								\
    X##_f = _flo.bits.frac;					\
    X##_e = _flo.bits.exp;					\
    X##_s = _flo.bits.sign;					\
  पूर्ण जबतक (0)

#घोषणा _FP_UNPACK_RAW_1_P(fs, X, val)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs *_flo =				\
      (जोड़ _FP_UNION_##fs *)(val);				\
								\
    X##_f = _flo->bits.frac;					\
    X##_e = _flo->bits.exp;					\
    X##_s = _flo->bits.sign;					\
  पूर्ण जबतक (0)

/*
 * Repack the raw bits of a native fp value.
 */

#घोषणा _FP_PACK_RAW_1(fs, val, X)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs _flo;					\
								\
    _flo.bits.frac = X##_f;					\
    _flo.bits.exp  = X##_e;					\
    _flo.bits.sign = X##_s;					\
								\
    (val) = _flo.flt;						\
  पूर्ण जबतक (0)

#घोषणा _FP_PACK_RAW_1_P(fs, val, X)				\
  करो अणु								\
    जोड़ _FP_UNION_##fs *_flo =				\
      (जोड़ _FP_UNION_##fs *)(val);				\
								\
    _flo->bits.frac = X##_f;					\
    _flo->bits.exp  = X##_e;					\
    _flo->bits.sign = X##_s;					\
  पूर्ण जबतक (0)


/*
 * Multiplication algorithms:
 */

/* Basic.  Assuming the host word size is >= 2*FRACBITS, we can करो the
   multiplication immediately.  */

#घोषणा _FP_MUL_MEAT_1_imm(wfracbits, R, X, Y)				\
  करो अणु									\
    R##_f = X##_f * Y##_f;						\
    /* Normalize since we know where the msb of the multiplicands	\
       were (bit B), we know that the msb of the of the product is	\
       at either 2B or 2B-1.  */					\
    _FP_FRAC_SRS_1(R, wfracbits-1, 2*wfracbits);			\
  पूर्ण जबतक (0)

/* Given a 1W * 1W => 2W primitive, करो the extended multiplication.  */

#घोषणा _FP_MUL_MEAT_1_wide(wfracbits, R, X, Y, करोit)			\
  करो अणु									\
    _FP_W_TYPE _Z_f0, _Z_f1;						\
    करोit(_Z_f1, _Z_f0, X##_f, Y##_f);					\
    /* Normalize since we know where the msb of the multiplicands	\
       were (bit B), we know that the msb of the of the product is	\
       at either 2B or 2B-1.  */					\
    _FP_FRAC_SRS_2(_Z, wfracbits-1, 2*wfracbits);			\
    R##_f = _Z_f0;							\
  पूर्ण जबतक (0)

/* Finally, a simple widening multiply algorithm.  What fun!  */

#घोषणा _FP_MUL_MEAT_1_hard(wfracbits, R, X, Y)				\
  करो अणु									\
    _FP_W_TYPE _xh, _xl, _yh, _yl, _z_f0, _z_f1, _a_f0, _a_f1;		\
									\
    /* split the words in half */					\
    _xh = X##_f >> (_FP_W_TYPE_SIZE/2);					\
    _xl = X##_f & (((_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE/2)) - 1);		\
    _yh = Y##_f >> (_FP_W_TYPE_SIZE/2);					\
    _yl = Y##_f & (((_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE/2)) - 1);		\
									\
    /* multiply the pieces */						\
    _z_f0 = _xl * _yl;							\
    _a_f0 = _xh * _yl;							\
    _a_f1 = _xl * _yh;							\
    _z_f1 = _xh * _yh;							\
									\
    /* reassemble पूर्णांकo two full words */				\
    अगर ((_a_f0 += _a_f1) < _a_f1)					\
      _z_f1 += (_FP_W_TYPE)1 << (_FP_W_TYPE_SIZE/2);			\
    _a_f1 = _a_f0 >> (_FP_W_TYPE_SIZE/2);				\
    _a_f0 = _a_f0 << (_FP_W_TYPE_SIZE/2);				\
    _FP_FRAC_ADD_2(_z, _z, _a);						\
									\
    /* normalize */							\
    _FP_FRAC_SRS_2(_z, wfracbits - 1, 2*wfracbits);			\
    R##_f = _z_f0;							\
  पूर्ण जबतक (0)


/*
 * Division algorithms:
 */

/* Basic.  Assuming the host word size is >= 2*FRACBITS, we can करो the
   भागision immediately.  Give this macro either _FP_DIV_HELP_imm क्रम
   C primitives or _FP_DIV_HELP_द_भाग क्रम the ISO function.  Which you
   choose will depend on what the compiler करोes with भागrem4.  */

#घोषणा _FP_DIV_MEAT_1_imm(fs, R, X, Y, करोit)		\
  करो अणु							\
    _FP_W_TYPE _q, _r;					\
    X##_f <<= (X##_f < Y##_f				\
	       ? R##_e--, _FP_WFRACBITS_##fs		\
	       : _FP_WFRACBITS_##fs - 1);		\
    करोit(_q, _r, X##_f, Y##_f);				\
    R##_f = _q | (_r != 0);				\
  पूर्ण जबतक (0)

/* GCC's दीर्घदीर्घ.h defines a 2W / 1W => (1W,1W) primitive uभाग_qrnnd
   that may be useful in this situation.  This first is क्रम a primitive
   that requires normalization, the second क्रम one that करोes not.  Look
   क्रम UDIV_NEEDS_NORMALIZATION to tell which your machine needs.  */

#घोषणा _FP_DIV_MEAT_1_uभाग_norm(fs, R, X, Y)				\
  करो अणु									\
    _FP_W_TYPE _nh, _nl, _q, _r, _y;					\
									\
    /* Normalize Y -- i.e. make the most signअगरicant bit set.  */	\
    _y = Y##_f << _FP_WFRACXBITS_##fs;					\
									\
    /* Shअगरt X op correspondingly high, that is, up one full word.  */	\
    अगर (X##_f < Y##_f)							\
      अणु									\
	R##_e--;							\
	_nl = 0;							\
	_nh = X##_f;							\
      पूर्ण									\
    अन्यथा								\
      अणु									\
	_nl = X##_f << (_FP_W_TYPE_SIZE - 1);				\
	_nh = X##_f >> 1;						\
      पूर्ण									\
    									\
    uभाग_qrnnd(_q, _r, _nh, _nl, _y);					\
    R##_f = _q | (_r != 0);						\
  पूर्ण जबतक (0)

#घोषणा _FP_DIV_MEAT_1_uभाग(fs, R, X, Y)		\
  करो अणु							\
    _FP_W_TYPE _nh, _nl, _q, _r;			\
    अगर (X##_f < Y##_f)					\
      अणु							\
	R##_e--;					\
	_nl = X##_f << _FP_WFRACBITS_##fs;		\
	_nh = X##_f >> _FP_WFRACXBITS_##fs;		\
      पूर्ण							\
    अन्यथा						\
      अणु							\
	_nl = X##_f << (_FP_WFRACBITS_##fs - 1);	\
	_nh = X##_f >> (_FP_WFRACXBITS_##fs + 1);	\
      पूर्ण							\
    uभाग_qrnnd(_q, _r, _nh, _nl, Y##_f);		\
    R##_f = _q | (_r != 0);				\
  पूर्ण जबतक (0)
  
  
/*
 * Square root algorithms:
 * We have just one right now, maybe Newton approximation
 * should be added क्रम those machines where भागision is fast.
 */
 
#घोषणा _FP_SQRT_MEAT_1(R, S, T, X, q)			\
  करो अणु							\
    जबतक (q != _FP_WORK_ROUND)				\
      अणु							\
        T##_f = S##_f + q;				\
        अगर (T##_f <= X##_f)				\
          अणु						\
            S##_f = T##_f + q;				\
            X##_f -= T##_f;				\
            R##_f += q;					\
          पूर्ण						\
        _FP_FRAC_SLL_1(X, 1);				\
        q >>= 1;					\
      पूर्ण							\
    अगर (X##_f)						\
      अणु							\
	अगर (S##_f < X##_f)				\
	  R##_f |= _FP_WORK_ROUND;			\
	R##_f |= _FP_WORK_STICKY;			\
      पूर्ण							\
  पूर्ण जबतक (0)

/*
 * Assembly/disassembly क्रम converting to/from पूर्णांकegral types.  
 * No shअगरting or overflow handled here.
 */

#घोषणा _FP_FRAC_ASSEMBLE_1(r, X, rsize)	(r = X##_f)
#घोषणा _FP_FRAC_DISASSEMBLE_1(X, r, rsize)	(X##_f = r)


/*
 * Convert FP values between word sizes
 */

#घोषणा _FP_FRAC_CONV_1_1(dfs, sfs, D, S)				\
  करो अणु									\
    D##_f = S##_f;							\
    अगर (_FP_WFRACBITS_##sfs > _FP_WFRACBITS_##dfs)			\
      अणु									\
	अगर (S##_c != FP_CLS_न_अंक)					\
	  _FP_FRAC_SRS_1(D, (_FP_WFRACBITS_##sfs-_FP_WFRACBITS_##dfs),	\
			 _FP_WFRACBITS_##sfs);				\
	अन्यथा								\
	  _FP_FRAC_SRL_1(D, (_FP_WFRACBITS_##sfs-_FP_WFRACBITS_##dfs));	\
      पूर्ण									\
    अन्यथा								\
      D##_f <<= _FP_WFRACBITS_##dfs - _FP_WFRACBITS_##sfs;		\
  पूर्ण जबतक (0)

#पूर्ण_अगर /* __MATH_EMU_OP_1_H__ */
