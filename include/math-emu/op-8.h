<शैली गुरु>
/* Software भग्नing-poपूर्णांक emulation.
   Basic eight-word fraction declaration and manipulation.
   Copyright (C) 1997,1998,1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Riअक्षरd Henderson (rth@cygnus.com),
		  Jakub Jelinek (jj@ultra.linux.cz) and
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

#अगर_अघोषित __MATH_EMU_OP_8_H__
#घोषणा __MATH_EMU_OP_8_H__

/* We need just a few things from here क्रम op-4, अगर we ever need some
   other macros, they can be added. */
#घोषणा _FP_FRAC_DECL_8(X)	_FP_W_TYPE X##_f[8]
#घोषणा _FP_FRAC_HIGH_8(X)	(X##_f[7])
#घोषणा _FP_FRAC_LOW_8(X)	(X##_f[0])
#घोषणा _FP_FRAC_WORD_8(X,w)	(X##_f[w])

#घोषणा _FP_FRAC_SLL_8(X,N)						\
  करो अणु									\
    _FP_I_TYPE _up, _करोwn, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _up = (N) % _FP_W_TYPE_SIZE;					\
    _करोwn = _FP_W_TYPE_SIZE - _up;					\
    अगर (!_up)								\
      क्रम (_i = 7; _i >= _skip; --_i)					\
	X##_f[_i] = X##_f[_i-_skip];					\
    अन्यथा								\
      अणु									\
	क्रम (_i = 7; _i > _skip; --_i)					\
	  X##_f[_i] = X##_f[_i-_skip] << _up				\
		      | X##_f[_i-_skip-1] >> _करोwn;			\
	X##_f[_i--] = X##_f[0] << _up; 					\
      पूर्ण									\
    क्रम (; _i >= 0; --_i)						\
      X##_f[_i] = 0;							\
  पूर्ण जबतक (0)

#घोषणा _FP_FRAC_SRL_8(X,N)						\
  करो अणु									\
    _FP_I_TYPE _up, _करोwn, _skip, _i;					\
    _skip = (N) / _FP_W_TYPE_SIZE;					\
    _करोwn = (N) % _FP_W_TYPE_SIZE;					\
    _up = _FP_W_TYPE_SIZE - _करोwn;					\
    अगर (!_करोwn)								\
      क्रम (_i = 0; _i <= 7-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    अन्यथा								\
      अणु									\
	क्रम (_i = 0; _i < 7-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _करोwn				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[7] >> _करोwn;				\
      पूर्ण									\
    क्रम (; _i < 8; ++_i)						\
      X##_f[_i] = 0;							\
  पूर्ण जबतक (0)


/* Right shअगरt with sticky-lsb. 
 * What this actually means is that we करो a standard right-shअगरt,
 * but that अगर any of the bits that fall off the right hand side
 * were one then we always set the LSbit.
 */
#घोषणा _FP_FRAC_SRS_8(X,N,size)					\
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
      क्रम (_i = 0; _i <= 7-_skip; ++_i)					\
	X##_f[_i] = X##_f[_i+_skip];					\
    अन्यथा								\
      अणु									\
	क्रम (_i = 0; _i < 7-_skip; ++_i)				\
	  X##_f[_i] = X##_f[_i+_skip] >> _करोwn				\
		      | X##_f[_i+_skip+1] << _up;			\
	X##_f[_i++] = X##_f[7] >> _करोwn;				\
      पूर्ण									\
    क्रम (; _i < 8; ++_i)						\
      X##_f[_i] = 0;							\
    /* करोn't fix the LSB until the very end when we're sure f[0] is stable */	\
    X##_f[0] |= (_s != 0);						\
  पूर्ण जबतक (0)

#पूर्ण_अगर
