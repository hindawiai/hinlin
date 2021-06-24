<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation. Common operations.
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

#अगर_अघोषित __MATH_EMU_OP_COMMON_H__
#घोषणा __MATH_EMU_OP_COMMON_H__

#घोषणा _FP_DECL(wc, X)			\
  _FP_I_TYPE X##_c=0, X##_s=0, X##_e=0;	\
  _FP_FRAC_DECL_##wc(X)

/*
 * Finish truly unpacking a native fp value by classअगरying the kind
 * of fp value and normalizing both the exponent and the fraction.
 */

#घोषणा _FP_UNPACK_CANONICAL(fs, wc, X)					\
करो अणु									\
  चयन (X##_e)							\
  अणु									\
  शेष:								\
    _FP_FRAC_HIGH_RAW_##fs(X) |= _FP_IMPLBIT_##fs;			\
    _FP_FRAC_SLL_##wc(X, _FP_WORKBITS);					\
    X##_e -= _FP_EXPBIAS_##fs;						\
    X##_c = FP_CLS_NORMAL;						\
    अवरोध;								\
									\
  हाल 0:								\
    अगर (_FP_FRAC_ZEROP_##wc(X))						\
      X##_c = FP_CLS_ZERO;						\
    अन्यथा								\
      अणु									\
	/* a denormalized number */					\
	_FP_I_TYPE _shअगरt;						\
	_FP_FRAC_CLZ_##wc(_shअगरt, X);					\
	_shअगरt -= _FP_FRACXBITS_##fs;					\
	_FP_FRAC_SLL_##wc(X, (_shअगरt+_FP_WORKBITS));			\
	X##_e -= _FP_EXPBIAS_##fs - 1 + _shअगरt;				\
	X##_c = FP_CLS_NORMAL;						\
	FP_SET_EXCEPTION(FP_EX_DENORM);					\
	अगर (FP_DENORM_ZERO)						\
	  अणु								\
	    FP_SET_EXCEPTION(FP_EX_INEXACT);				\
	    X##_c = FP_CLS_ZERO;					\
	  पूर्ण								\
      पूर्ण									\
    अवरोध;								\
									\
  हाल _FP_EXPMAX_##fs:							\
    अगर (_FP_FRAC_ZEROP_##wc(X))						\
      X##_c = FP_CLS_INF;						\
    अन्यथा								\
      अणु									\
	X##_c = FP_CLS_न_अंक;						\
	/* Check क्रम संकेतing NaN */					\
	अगर (!(_FP_FRAC_HIGH_RAW_##fs(X) & _FP_Qन_अंकBIT_##fs))		\
	  FP_SET_EXCEPTION(FP_EX_INVALID | FP_EX_INVALID_Sन_अंक);		\
      पूर्ण									\
    अवरोध;								\
  पूर्ण									\
पूर्ण जबतक (0)

/*
 * Beक्रमe packing the bits back पूर्णांकo the native fp result, take care
 * of such mundane things as rounding and overflow.  Also, क्रम some
 * kinds of fp values, the original parts may not have been fully
 * extracted -- but that is ok, we can regenerate them now.
 */

#घोषणा _FP_PACK_CANONICAL(fs, wc, X)				\
करो अणु								\
  चयन (X##_c)						\
  अणु								\
  हाल FP_CLS_NORMAL:						\
    X##_e += _FP_EXPBIAS_##fs;					\
    अगर (X##_e > 0)						\
      अणु								\
	_FP_ROUND(wc, X);					\
	अगर (_FP_FRAC_OVERP_##wc(fs, X))				\
	  अणु							\
	    _FP_FRAC_CLEAR_OVERP_##wc(fs, X);			\
	    X##_e++;						\
	  पूर्ण							\
	_FP_FRAC_SRL_##wc(X, _FP_WORKBITS);			\
	अगर (X##_e >= _FP_EXPMAX_##fs)				\
	  अणु							\
	    /* overflow */					\
	    चयन (FP_ROUNDMODE)				\
	      अणु							\
	      हाल FP_RND_NEAREST:				\
		X##_c = FP_CLS_INF;				\
		अवरोध;						\
	      हाल FP_RND_PINF:					\
		अगर (!X##_s) X##_c = FP_CLS_INF;			\
		अवरोध;						\
	      हाल FP_RND_MINF:					\
		अगर (X##_s) X##_c = FP_CLS_INF;			\
		अवरोध;						\
	      पूर्ण							\
	    अगर (X##_c == FP_CLS_INF)				\
	      अणु							\
		/* Overflow to infinity */			\
		X##_e = _FP_EXPMAX_##fs;			\
		_FP_FRAC_SET_##wc(X, _FP_ZEROFRAC_##wc);	\
	      पूर्ण							\
	    अन्यथा						\
	      अणु							\
		/* Overflow to maximum normal */		\
		X##_e = _FP_EXPMAX_##fs - 1;			\
		_FP_FRAC_SET_##wc(X, _FP_MAXFRAC_##wc);		\
	      पूर्ण							\
	    FP_SET_EXCEPTION(FP_EX_OVERFLOW);			\
            FP_SET_EXCEPTION(FP_EX_INEXACT);			\
	  पूर्ण							\
      पूर्ण								\
    अन्यथा							\
      अणु								\
	/* we've got a denormalized number */			\
	X##_e = -X##_e + 1;					\
	अगर (X##_e <= _FP_WFRACBITS_##fs)			\
	  अणु							\
	    _FP_FRAC_SRS_##wc(X, X##_e, _FP_WFRACBITS_##fs);	\
	    अगर (_FP_FRAC_HIGH_##fs(X)				\
		& (_FP_OVERFLOW_##fs >> 1))			\
	      अणु							\
	        X##_e = 1;					\
	        _FP_FRAC_SET_##wc(X, _FP_ZEROFRAC_##wc);	\
	      पूर्ण							\
	    अन्यथा						\
	      अणु							\
		_FP_ROUND(wc, X);				\
		अगर (_FP_FRAC_HIGH_##fs(X)			\
		   & (_FP_OVERFLOW_##fs >> 1))			\
		  अणु						\
		    X##_e = 1;					\
		    _FP_FRAC_SET_##wc(X, _FP_ZEROFRAC_##wc);	\
		    FP_SET_EXCEPTION(FP_EX_INEXACT);		\
		  पूर्ण						\
		अन्यथा						\
		  अणु						\
		    X##_e = 0;					\
		    _FP_FRAC_SRL_##wc(X, _FP_WORKBITS);		\
		  पूर्ण						\
	      पूर्ण							\
	    अगर ((FP_CUR_EXCEPTIONS & FP_EX_INEXACT) ||		\
		(FP_TRAPPING_EXCEPTIONS & FP_EX_UNDERFLOW))	\
		FP_SET_EXCEPTION(FP_EX_UNDERFLOW);		\
	  पूर्ण							\
	अन्यथा							\
	  अणु							\
	    /* underflow to zero */				\
	    X##_e = 0;						\
	    अगर (!_FP_FRAC_ZEROP_##wc(X))			\
	      अणु							\
	        _FP_FRAC_SET_##wc(X, _FP_MINFRAC_##wc);		\
	        _FP_ROUND(wc, X);				\
	        _FP_FRAC_LOW_##wc(X) >>= (_FP_WORKBITS);	\
	      पूर्ण							\
	    FP_SET_EXCEPTION(FP_EX_UNDERFLOW);			\
	  पूर्ण							\
      पूर्ण								\
    अवरोध;							\
								\
  हाल FP_CLS_ZERO:						\
    X##_e = 0;							\
    _FP_FRAC_SET_##wc(X, _FP_ZEROFRAC_##wc);			\
    अवरोध;							\
								\
  हाल FP_CLS_INF:						\
    X##_e = _FP_EXPMAX_##fs;					\
    _FP_FRAC_SET_##wc(X, _FP_ZEROFRAC_##wc);			\
    अवरोध;							\
								\
  हाल FP_CLS_न_अंक:						\
    X##_e = _FP_EXPMAX_##fs;					\
    अगर (!_FP_KEEPन_अंकFRACP)					\
      अणु								\
	_FP_FRAC_SET_##wc(X, _FP_न_अंकFRAC_##fs);			\
	X##_s = _FP_न_अंकSIGN_##fs;				\
      पूर्ण								\
    अन्यथा							\
      _FP_FRAC_HIGH_RAW_##fs(X) |= _FP_Qन_अंकBIT_##fs;		\
    अवरोध;							\
  पूर्ण								\
पूर्ण जबतक (0)

/* This one accepts raw argument and not cooked,  वापसs
 * 1 अगर X is a संकेतing NaN.
 */
#घोषणा _FP_ISSIGन_अंक(fs, wc, X)					\
(अणु								\
  पूर्णांक __ret = 0;						\
  अगर (X##_e == _FP_EXPMAX_##fs)					\
    अणु								\
      अगर (!_FP_FRAC_ZEROP_##wc(X)				\
	  && !(_FP_FRAC_HIGH_RAW_##fs(X) & _FP_Qन_अंकBIT_##fs))	\
	__ret = 1;						\
    पूर्ण								\
  __ret;							\
पूर्ण)





/*
 * Main addition routine.  The input values should be cooked.
 */

#घोषणा _FP_ADD_INTERNAL(fs, wc, R, X, Y, OP)				     \
करो अणु									     \
  चयन (_FP_CLS_COMBINE(X##_c, Y##_c))				     \
  अणु									     \
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_NORMAL):			     \
    अणु									     \
      /* shअगरt the smaller number so that its exponent matches the larger */ \
      _FP_I_TYPE dअगरf = X##_e - Y##_e;					     \
									     \
      अगर (dअगरf < 0)							     \
	अणु								     \
	  dअगरf = -dअगरf;							     \
	  अगर (dअगरf <= _FP_WFRACBITS_##fs)				     \
	    _FP_FRAC_SRS_##wc(X, dअगरf, _FP_WFRACBITS_##fs);		     \
	  अन्यथा अगर (!_FP_FRAC_ZEROP_##wc(X))				     \
	    _FP_FRAC_SET_##wc(X, _FP_MINFRAC_##wc);			     \
	  R##_e = Y##_e;						     \
	पूर्ण								     \
      अन्यथा								     \
	अणु								     \
	  अगर (dअगरf > 0)							     \
	    अणु								     \
	      अगर (dअगरf <= _FP_WFRACBITS_##fs)				     \
	        _FP_FRAC_SRS_##wc(Y, dअगरf, _FP_WFRACBITS_##fs);		     \
	      अन्यथा अगर (!_FP_FRAC_ZEROP_##wc(Y))				     \
	        _FP_FRAC_SET_##wc(Y, _FP_MINFRAC_##wc);			     \
	    पूर्ण								     \
	  R##_e = X##_e;						     \
	पूर्ण								     \
									     \
      R##_c = FP_CLS_NORMAL;						     \
									     \
      अगर (X##_s == Y##_s)						     \
	अणु								     \
	  R##_s = X##_s;						     \
	  _FP_FRAC_ADD_##wc(R, X, Y);					     \
	  अगर (_FP_FRAC_OVERP_##wc(fs, R))				     \
	    अणु								     \
	      _FP_FRAC_SRS_##wc(R, 1, _FP_WFRACBITS_##fs);		     \
	      R##_e++;							     \
	    पूर्ण								     \
	पूर्ण								     \
      अन्यथा								     \
	अणु								     \
	  R##_s = X##_s;						     \
	  _FP_FRAC_SUB_##wc(R, X, Y);					     \
	  अगर (_FP_FRAC_ZEROP_##wc(R))					     \
	    अणु								     \
	      /* वापस an exact zero */				     \
	      अगर (FP_ROUNDMODE == FP_RND_MINF)				     \
		R##_s |= Y##_s;						     \
	      अन्यथा							     \
		R##_s &= Y##_s;						     \
	      R##_c = FP_CLS_ZERO;					     \
	    पूर्ण								     \
	  अन्यथा								     \
	    अणु								     \
	      अगर (_FP_FRAC_NEGP_##wc(R))				     \
		अणु							     \
		  _FP_FRAC_SUB_##wc(R, Y, X);				     \
		  R##_s = Y##_s;					     \
		पूर्ण							     \
									     \
	      /* renormalize after subtraction */			     \
	      _FP_FRAC_CLZ_##wc(dअगरf, R);				     \
	      dअगरf -= _FP_WFRACXBITS_##fs;				     \
	      अगर (dअगरf)							     \
		अणु							     \
		  R##_e -= dअगरf;					     \
		  _FP_FRAC_SLL_##wc(R, dअगरf);				     \
		पूर्ण							     \
	    पूर्ण								     \
	पूर्ण								     \
      अवरोध;								     \
    पूर्ण									     \
									     \
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_न_अंक):				     \
    _FP_CHOOSEन_अंक(fs, wc, R, X, Y, OP);					     \
    अवरोध;								     \
									     \
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_ZERO):			     \
    R##_e = X##_e;							     \
	fallthrough;							     \
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_NORMAL):			     \
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_INF):				     \
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_ZERO):				     \
    _FP_FRAC_COPY_##wc(R, X);						     \
    R##_s = X##_s;							     \
    R##_c = X##_c;							     \
    अवरोध;								     \
									     \
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_NORMAL):			     \
    R##_e = Y##_e;							     \
	fallthrough;							     \
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_न_अंक):			     \
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_न_अंक):				     \
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_न_अंक):				     \
    _FP_FRAC_COPY_##wc(R, Y);						     \
    R##_s = Y##_s;							     \
    R##_c = Y##_c;							     \
    अवरोध;								     \
									     \
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_INF):				     \
    अगर (X##_s != Y##_s)							     \
      अणु									     \
	/* +INF + -INF => न_अंक */					     \
	_FP_FRAC_SET_##wc(R, _FP_न_अंकFRAC_##fs);				     \
	R##_s = _FP_न_अंकSIGN_##fs;					     \
	R##_c = FP_CLS_न_अंक;						     \
	FP_SET_EXCEPTION(FP_EX_INVALID | FP_EX_INVALID_ISI);		     \
	अवरोध;								     \
      पूर्ण									     \
    /* FALLTHRU */							     \
									     \
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_NORMAL):			     \
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_ZERO):				     \
    R##_s = X##_s;							     \
    R##_c = FP_CLS_INF;							     \
    अवरोध;								     \
									     \
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_INF):			     \
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_INF):				     \
    R##_s = Y##_s;							     \
    R##_c = FP_CLS_INF;							     \
    अवरोध;								     \
									     \
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_ZERO):			     \
    /* make sure the sign is correct */					     \
    अगर (FP_ROUNDMODE == FP_RND_MINF)					     \
      R##_s = X##_s | Y##_s;						     \
    अन्यथा								     \
      R##_s = X##_s & Y##_s;						     \
    R##_c = FP_CLS_ZERO;						     \
    अवरोध;								     \
									     \
  शेष:								     \
    पात();								     \
  पूर्ण									     \
पूर्ण जबतक (0)

#घोषणा _FP_ADD(fs, wc, R, X, Y) _FP_ADD_INTERNAL(fs, wc, R, X, Y, '+')
#घोषणा _FP_SUB(fs, wc, R, X, Y)					     \
  करो अणु									     \
    अगर (Y##_c != FP_CLS_न_अंक) Y##_s ^= 1;				     \
    _FP_ADD_INTERNAL(fs, wc, R, X, Y, '-');				     \
  पूर्ण जबतक (0)


/*
 * Main negation routine.  FIXME -- when we care about setting exception
 * bits reliably, this will not करो.  We should examine all of the fp classes.
 */

#घोषणा _FP_NEG(fs, wc, R, X)		\
  करो अणु					\
    _FP_FRAC_COPY_##wc(R, X);		\
    R##_c = X##_c;			\
    R##_e = X##_e;			\
    R##_s = 1 ^ X##_s;			\
  पूर्ण जबतक (0)


/*
 * Main multiplication routine.  The input values should be cooked.
 */

#घोषणा _FP_MUL(fs, wc, R, X, Y)			\
करो अणु							\
  R##_s = X##_s ^ Y##_s;				\
  चयन (_FP_CLS_COMBINE(X##_c, Y##_c))		\
  अणु							\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_NORMAL):	\
    R##_c = FP_CLS_NORMAL;				\
    R##_e = X##_e + Y##_e + 1;				\
							\
    _FP_MUL_MEAT_##fs(R,X,Y);				\
							\
    अगर (_FP_FRAC_OVERP_##wc(fs, R))			\
      _FP_FRAC_SRS_##wc(R, 1, _FP_WFRACBITS_##fs);	\
    अन्यथा						\
      R##_e--;						\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_न_अंक):		\
    _FP_CHOOSEन_अंक(fs, wc, R, X, Y, '*');		\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_NORMAL):	\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_INF):		\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_ZERO):		\
    R##_s = X##_s;					\
	  fallthrough;					\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_INF):		\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_NORMAL):	\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_NORMAL):	\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_ZERO):	\
    _FP_FRAC_COPY_##wc(R, X);				\
    R##_c = X##_c;					\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_न_अंक):	\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_न_अंक):		\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_न_अंक):		\
    R##_s = Y##_s;					\
	  fallthrough;					\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_INF):	\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_ZERO):	\
    _FP_FRAC_COPY_##wc(R, Y);				\
    R##_c = Y##_c;					\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_ZERO):		\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_INF):		\
    R##_s = _FP_न_अंकSIGN_##fs;				\
    R##_c = FP_CLS_न_अंक;					\
    _FP_FRAC_SET_##wc(R, _FP_न_अंकFRAC_##fs);		\
    FP_SET_EXCEPTION(FP_EX_INVALID | FP_EX_INVALID_IMZ);\
    अवरोध;						\
							\
  शेष:						\
    पात();						\
  पूर्ण							\
पूर्ण जबतक (0)


/*
 * Main भागision routine.  The input values should be cooked.
 */

#घोषणा _FP_DIV(fs, wc, R, X, Y)			\
करो अणु							\
  R##_s = X##_s ^ Y##_s;				\
  चयन (_FP_CLS_COMBINE(X##_c, Y##_c))		\
  अणु							\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_NORMAL):	\
    R##_c = FP_CLS_NORMAL;				\
    R##_e = X##_e - Y##_e;				\
							\
    _FP_DIV_MEAT_##fs(R,X,Y);				\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_न_अंक):		\
    _FP_CHOOSEन_अंक(fs, wc, R, X, Y, '/');		\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_NORMAL):	\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_INF):		\
  हाल _FP_CLS_COMBINE(FP_CLS_न_अंक,FP_CLS_ZERO):		\
    R##_s = X##_s;					\
    _FP_FRAC_COPY_##wc(R, X);				\
    R##_c = X##_c;					\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_न_अंक):	\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_न_अंक):		\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_न_अंक):		\
    R##_s = Y##_s;					\
    _FP_FRAC_COPY_##wc(R, Y);				\
    R##_c = Y##_c;					\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_INF):	\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_INF):		\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_NORMAL):	\
    R##_c = FP_CLS_ZERO;				\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_NORMAL,FP_CLS_ZERO):	\
    FP_SET_EXCEPTION(FP_EX_DIVZERO);			\
	fallthrough;					\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_ZERO):		\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_NORMAL):	\
    R##_c = FP_CLS_INF;					\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_INF,FP_CLS_INF):		\
    R##_s = _FP_न_अंकSIGN_##fs;				\
    R##_c = FP_CLS_न_अंक;					\
    _FP_FRAC_SET_##wc(R, _FP_न_अंकFRAC_##fs);		\
    FP_SET_EXCEPTION(FP_EX_INVALID | FP_EX_INVALID_IDI);\
    अवरोध;						\
							\
  हाल _FP_CLS_COMBINE(FP_CLS_ZERO,FP_CLS_ZERO):	\
    R##_s = _FP_न_अंकSIGN_##fs;				\
    R##_c = FP_CLS_न_अंक;					\
    _FP_FRAC_SET_##wc(R, _FP_न_अंकFRAC_##fs);		\
    FP_SET_EXCEPTION(FP_EX_INVALID | FP_EX_INVALID_ZDZ);\
    अवरोध;						\
							\
  शेष:						\
    पात();						\
  पूर्ण							\
पूर्ण जबतक (0)


/*
 * Main dअगरferential comparison routine.  The inमाला_दो should be raw not
 * cooked.  The वापस is -1,0,1 क्रम normal values, 2 otherwise.
 */

#घोषणा _FP_CMP(fs, wc, ret, X, Y, un)					\
  करो अणु									\
    /* न_अंकs are unordered */						\
    अगर ((X##_e == _FP_EXPMAX_##fs && !_FP_FRAC_ZEROP_##wc(X))		\
	|| (Y##_e == _FP_EXPMAX_##fs && !_FP_FRAC_ZEROP_##wc(Y)))	\
      अणु									\
	ret = un;							\
      पूर्ण									\
    अन्यथा								\
      अणु									\
	पूर्णांक __is_zero_x;						\
	पूर्णांक __is_zero_y;						\
									\
	__is_zero_x = (!X##_e && _FP_FRAC_ZEROP_##wc(X)) ? 1 : 0;	\
	__is_zero_y = (!Y##_e && _FP_FRAC_ZEROP_##wc(Y)) ? 1 : 0;	\
									\
	अगर (__is_zero_x && __is_zero_y)					\
		ret = 0;						\
	अन्यथा अगर (__is_zero_x)						\
		ret = Y##_s ? 1 : -1;					\
	अन्यथा अगर (__is_zero_y)						\
		ret = X##_s ? -1 : 1;					\
	अन्यथा अगर (X##_s != Y##_s)					\
	  ret = X##_s ? -1 : 1;						\
	अन्यथा अगर (X##_e > Y##_e)						\
	  ret = X##_s ? -1 : 1;						\
	अन्यथा अगर (X##_e < Y##_e)						\
	  ret = X##_s ? 1 : -1;						\
	अन्यथा अगर (_FP_FRAC_GT_##wc(X, Y))				\
	  ret = X##_s ? -1 : 1;						\
	अन्यथा अगर (_FP_FRAC_GT_##wc(Y, X))				\
	  ret = X##_s ? 1 : -1;						\
	अन्यथा								\
	  ret = 0;							\
      पूर्ण									\
  पूर्ण जबतक (0)


/* Simplअगरication क्रम strict equality.  */

#घोषणा _FP_CMP_EQ(fs, wc, ret, X, Y)					  \
  करो अणु									  \
    /* न_अंकs are unordered */						  \
    अगर ((X##_e == _FP_EXPMAX_##fs && !_FP_FRAC_ZEROP_##wc(X))		  \
	|| (Y##_e == _FP_EXPMAX_##fs && !_FP_FRAC_ZEROP_##wc(Y)))	  \
      अणु									  \
	ret = 1;							  \
      पूर्ण									  \
    अन्यथा								  \
      अणु									  \
	ret = !(X##_e == Y##_e						  \
		&& _FP_FRAC_EQ_##wc(X, Y)				  \
		&& (X##_s == Y##_s || !X##_e && _FP_FRAC_ZEROP_##wc(X))); \
      पूर्ण									  \
  पूर्ण जबतक (0)

/*
 * Main square root routine.  The input value should be cooked.
 */

#घोषणा _FP_SQRT(fs, wc, R, X)						\
करो अणु									\
    _FP_FRAC_DECL_##wc(T); _FP_FRAC_DECL_##wc(S);			\
    _FP_W_TYPE q;							\
    चयन (X##_c)							\
    अणु									\
    हाल FP_CLS_न_अंक:							\
	_FP_FRAC_COPY_##wc(R, X);					\
	R##_s = X##_s;							\
    	R##_c = FP_CLS_न_अंक;						\
    	अवरोध;								\
    हाल FP_CLS_INF:							\
    	अगर (X##_s)							\
    	  अणु								\
    	    R##_s = _FP_न_अंकSIGN_##fs;					\
	    R##_c = FP_CLS_न_अंक; /* न_अंक */				\
	    _FP_FRAC_SET_##wc(R, _FP_न_अंकFRAC_##fs);			\
	    FP_SET_EXCEPTION(FP_EX_INVALID);				\
    	  पूर्ण								\
    	अन्यथा								\
    	  अणु								\
    	    R##_s = 0;							\
    	    R##_c = FP_CLS_INF; /* वर्ग_मूल(+inf) = +inf */			\
    	  पूर्ण								\
    	अवरोध;								\
    हाल FP_CLS_ZERO:							\
	R##_s = X##_s;							\
	R##_c = FP_CLS_ZERO; /* वर्ग_मूल(+-0) = +-0 */			\
	अवरोध;								\
    हाल FP_CLS_NORMAL:							\
    	R##_s = 0;							\
        अगर (X##_s)							\
          अणु								\
	    R##_c = FP_CLS_न_अंक; /* sन_अंक */				\
	    R##_s = _FP_न_अंकSIGN_##fs;					\
	    _FP_FRAC_SET_##wc(R, _FP_न_अंकFRAC_##fs);			\
	    FP_SET_EXCEPTION(FP_EX_INVALID);				\
	    अवरोध;							\
          पूर्ण								\
    	R##_c = FP_CLS_NORMAL;						\
        अगर (X##_e & 1)							\
          _FP_FRAC_SLL_##wc(X, 1);					\
        R##_e = X##_e >> 1;						\
        _FP_FRAC_SET_##wc(S, _FP_ZEROFRAC_##wc);			\
        _FP_FRAC_SET_##wc(R, _FP_ZEROFRAC_##wc);			\
        q = _FP_OVERFLOW_##fs >> 1;					\
        _FP_SQRT_MEAT_##wc(R, S, T, X, q);				\
    पूर्ण									\
  पूर्ण जबतक (0)

/*
 * Convert from FP to पूर्णांकeger
 */

/* RSIGNED can have following values:
 * 0:  the number is required to be 0..(2^rsize)-1, अगर not, NV is set plus
 *     the result is either 0 or (2^rsize)-1 depending on the sign in such हाल.
 * 1:  the number is required to be -(2^(rsize-1))..(2^(rsize-1))-1, अगर not, NV is
 *     set plus the result is either -(2^(rsize-1)) or (2^(rsize-1))-1 depending
 *     on the sign in such हाल.
 * 2:  the number is required to be -(2^(rsize-1))..(2^(rsize-1))-1, अगर not, NV is
 *     set plus the result is truncated to fit पूर्णांकo destination.
 * -1: the number is required to be -(2^(rsize-1))..(2^rsize)-1, अगर not, NV is
 *     set plus the result is either -(2^(rsize-1)) or (2^(rsize-1))-1 depending
 *     on the sign in such हाल.
 */
#घोषणा _FP_TO_INT(fs, wc, r, X, rsize, rचिन्हित)				\
  करो अणु										\
    चयन (X##_c)								\
      अणु										\
      हाल FP_CLS_NORMAL:							\
	अगर (X##_e < 0)								\
	  अणु									\
	    FP_SET_EXCEPTION(FP_EX_INEXACT);					\
	  हाल FP_CLS_ZERO:							\
	    r = 0;								\
	  पूर्ण									\
	अन्यथा अगर (X##_e >= rsize - (rचिन्हित > 0 || X##_s)			\
		 || (!rचिन्हित && X##_s))					\
	  अणु	/* overflow */							\
	  हाल FP_CLS_न_अंक:                                                      \
	  हाल FP_CLS_INF:							\
	    अगर (rचिन्हित == 2)							\
	      अणु									\
		अगर (X##_c != FP_CLS_NORMAL					\
		    || X##_e >= rsize - 1 + _FP_WFRACBITS_##fs)			\
		  r = 0;							\
		अन्यथा								\
		  अणु								\
		    _FP_FRAC_SLL_##wc(X, (X##_e - _FP_WFRACBITS_##fs + 1));	\
		    _FP_FRAC_ASSEMBLE_##wc(r, X, rsize);			\
		  पूर्ण								\
	      पूर्ण									\
	    अन्यथा अगर (rचिन्हित)							\
	      अणु									\
		r = 1;								\
		r <<= rsize - 1;						\
		r -= 1 - X##_s;							\
	      पूर्ण									\
	    अन्यथा								\
	      अणु									\
		r = 0;								\
		अगर (!X##_s)							\
		  r = ~r;							\
	      पूर्ण									\
	    FP_SET_EXCEPTION(FP_EX_INVALID);					\
	  पूर्ण									\
	अन्यथा									\
	  अणु									\
	    अगर (_FP_W_TYPE_SIZE*wc < rsize)					\
	      अणु									\
		_FP_FRAC_ASSEMBLE_##wc(r, X, rsize);				\
		r <<= X##_e - _FP_WFRACBITS_##fs;				\
	      पूर्ण									\
	    अन्यथा								\
	      अणु									\
		अगर (X##_e >= _FP_WFRACBITS_##fs)				\
		  _FP_FRAC_SLL_##wc(X, (X##_e - _FP_WFRACBITS_##fs + 1));	\
		अन्यथा अगर (X##_e < _FP_WFRACBITS_##fs - 1)			\
		  अणु								\
		    _FP_FRAC_SRS_##wc(X, (_FP_WFRACBITS_##fs - X##_e - 2),	\
				      _FP_WFRACBITS_##fs);			\
		    अगर (_FP_FRAC_LOW_##wc(X) & 1)				\
		      FP_SET_EXCEPTION(FP_EX_INEXACT);				\
		    _FP_FRAC_SRL_##wc(X, 1);					\
		  पूर्ण								\
		_FP_FRAC_ASSEMBLE_##wc(r, X, rsize);				\
	      पूर्ण									\
	    अगर (rचिन्हित && X##_s)						\
	      r = -r;								\
	  पूर्ण									\
	अवरोध;									\
      पूर्ण										\
  पूर्ण जबतक (0)

#घोषणा _FP_TO_INT_ROUND(fs, wc, r, X, rsize, rचिन्हित)				\
  करो अणु										\
    r = 0;									\
    चयन (X##_c)								\
      अणु										\
      हाल FP_CLS_NORMAL:							\
	अगर (X##_e >= _FP_FRACBITS_##fs - 1)					\
	  अणु									\
	    अगर (X##_e < rsize - 1 + _FP_WFRACBITS_##fs)				\
	      अणु									\
		अगर (X##_e >= _FP_WFRACBITS_##fs - 1)				\
		  अणु								\
		    _FP_FRAC_ASSEMBLE_##wc(r, X, rsize);			\
		    r <<= X##_e - _FP_WFRACBITS_##fs + 1;			\
		  पूर्ण								\
		अन्यथा								\
		  अणु								\
		    _FP_FRAC_SRL_##wc(X, _FP_WORKBITS - X##_e			\
				      + _FP_FRACBITS_##fs - 1);			\
		    _FP_FRAC_ASSEMBLE_##wc(r, X, rsize);			\
		  पूर्ण								\
	      पूर्ण									\
	  पूर्ण									\
	अन्यथा									\
	  अणु									\
	    पूर्णांक _lz0, _lz1;							\
	    अगर (X##_e <= -_FP_WORKBITS - 1)					\
	      _FP_FRAC_SET_##wc(X, _FP_MINFRAC_##wc);				\
	    अन्यथा								\
	      _FP_FRAC_SRS_##wc(X, _FP_FRACBITS_##fs - 1 - X##_e,		\
				_FP_WFRACBITS_##fs);				\
	    _FP_FRAC_CLZ_##wc(_lz0, X);						\
	    _FP_ROUND(wc, X);							\
	    _FP_FRAC_CLZ_##wc(_lz1, X);						\
	    अगर (_lz1 < _lz0)							\
	      X##_e++; /* For overflow detection.  */				\
	    _FP_FRAC_SRL_##wc(X, _FP_WORKBITS);					\
	    _FP_FRAC_ASSEMBLE_##wc(r, X, rsize);				\
	  पूर्ण									\
	अगर (rचिन्हित && X##_s)							\
	  r = -r;								\
	अगर (X##_e >= rsize - (rचिन्हित > 0 || X##_s)				\
	    || (!rचिन्हित && X##_s))						\
	  अणु	/* overflow */							\
	  हाल FP_CLS_न_अंक:                                                      \
	  हाल FP_CLS_INF:							\
	    अगर (!rचिन्हित)							\
	      अणु									\
		r = 0;								\
		अगर (!X##_s)							\
		  r = ~r;							\
	      पूर्ण									\
	    अन्यथा अगर (rचिन्हित != 2)						\
	      अणु									\
		r = 1;								\
		r <<= rsize - 1;						\
		r -= 1 - X##_s;							\
	      पूर्ण									\
	    FP_SET_EXCEPTION(FP_EX_INVALID);					\
	  पूर्ण									\
	अवरोध;									\
      हाल FP_CLS_ZERO:								\
        अवरोध;									\
      पूर्ण										\
  पूर्ण जबतक (0)

#घोषणा _FP_FROM_INT(fs, wc, X, r, rsize, rtype)			\
  करो अणु									\
    अगर (r)								\
      अणु									\
        अचिन्हित rtype ur_;						\
	X##_c = FP_CLS_NORMAL;						\
									\
	अगर ((X##_s = (r < 0)))						\
	  ur_ = (अचिन्हित rtype) -r;					\
	अन्यथा								\
	  ur_ = (अचिन्हित rtype) r;					\
	(व्योम) (((rsize) <= _FP_W_TYPE_SIZE)				\
		? (अणु __FP_CLZ(X##_e, ur_); पूर्ण)				\
		: (अणु							\
		     __FP_CLZ_2(X##_e, (_FP_W_TYPE)(ur_ >> _FP_W_TYPE_SIZE),  \
							    (_FP_W_TYPE)ur_); \
		  पूर्ण));							\
	अगर (rsize < _FP_W_TYPE_SIZE)					\
		X##_e -= (_FP_W_TYPE_SIZE - rsize);			\
	X##_e = rsize - X##_e - 1;					\
									\
	अगर (_FP_FRACBITS_##fs < rsize && _FP_WFRACBITS_##fs <= X##_e)	\
	  __FP_FRAC_SRS_1(ur_, (X##_e - _FP_WFRACBITS_##fs + 1), rsize);\
	_FP_FRAC_DISASSEMBLE_##wc(X, ur_, rsize);			\
	अगर ((_FP_WFRACBITS_##fs - X##_e - 1) > 0)			\
	  _FP_FRAC_SLL_##wc(X, (_FP_WFRACBITS_##fs - X##_e - 1));	\
      पूर्ण									\
    अन्यथा								\
      अणु									\
	X##_c = FP_CLS_ZERO, X##_s = 0;					\
      पूर्ण									\
  पूर्ण जबतक (0)


#घोषणा FP_CONV(dfs,sfs,dwc,swc,D,S)			\
  करो अणु							\
    _FP_FRAC_CONV_##dwc##_##swc(dfs, sfs, D, S);	\
    D##_e = S##_e;					\
    D##_c = S##_c;					\
    D##_s = S##_s;					\
  पूर्ण जबतक (0)

/*
 * Helper primitives.
 */

/* Count leading zeros in a word.  */

#अगर_अघोषित __FP_CLZ
#अगर _FP_W_TYPE_SIZE < 64
/* this is just to shut the compiler up about shअगरts > word length -- PMM 02/1998 */
#घोषणा __FP_CLZ(r, x)				\
  करो अणु						\
    _FP_W_TYPE _t = (x);			\
    r = _FP_W_TYPE_SIZE - 1;			\
    अगर (_t > 0xffff) r -= 16;			\
    अगर (_t > 0xffff) _t >>= 16;			\
    अगर (_t > 0xff) r -= 8;			\
    अगर (_t > 0xff) _t >>= 8;			\
    अगर (_t & 0xf0) r -= 4;			\
    अगर (_t & 0xf0) _t >>= 4;			\
    अगर (_t & 0xc) r -= 2;			\
    अगर (_t & 0xc) _t >>= 2;			\
    अगर (_t & 0x2) r -= 1;			\
  पूर्ण जबतक (0)
#अन्यथा /* not _FP_W_TYPE_SIZE < 64 */
#घोषणा __FP_CLZ(r, x)				\
  करो अणु						\
    _FP_W_TYPE _t = (x);			\
    r = _FP_W_TYPE_SIZE - 1;			\
    अगर (_t > 0xffffffff) r -= 32;		\
    अगर (_t > 0xffffffff) _t >>= 32;		\
    अगर (_t > 0xffff) r -= 16;			\
    अगर (_t > 0xffff) _t >>= 16;			\
    अगर (_t > 0xff) r -= 8;			\
    अगर (_t > 0xff) _t >>= 8;			\
    अगर (_t & 0xf0) r -= 4;			\
    अगर (_t & 0xf0) _t >>= 4;			\
    अगर (_t & 0xc) r -= 2;			\
    अगर (_t & 0xc) _t >>= 2;			\
    अगर (_t & 0x2) r -= 1;			\
  पूर्ण जबतक (0)
#पूर्ण_अगर /* not _FP_W_TYPE_SIZE < 64 */
#पूर्ण_अगर /* ndef __FP_CLZ */

#घोषणा _FP_DIV_HELP_imm(q, r, n, d)		\
  करो अणु						\
    q = n / d, r = n % d;			\
  पूर्ण जबतक (0)

#पूर्ण_अगर /* __MATH_EMU_OP_COMMON_H__ */
