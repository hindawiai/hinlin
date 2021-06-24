<शैली गुरु>
/* ashrdi3.c extracted from gcc-2.95.2/libgcc2.c which is: */
/* Copyright (C) 1989, 92-98, 1999 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is मुक्त software; you can redistribute it and/or modअगरy
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License क्रम more details. */

#समावेश <linux/compiler.h>
#समावेश <linux/export.h>

#घोषणा BITS_PER_UNIT 8

प्रकार		 पूर्णांक SItype	__mode(SI);
प्रकार अचिन्हित पूर्णांक USItype	__mode(SI);
प्रकार		 पूर्णांक DItype	__mode(DI);
प्रकार पूर्णांक word_type           __mode(__word__);

काष्ठा DIकाष्ठा अणुSItype high, low;पूर्ण;

प्रकार जोड़
अणु
  काष्ठा DIकाष्ठा s;
  DItype ll;
पूर्ण DIजोड़;

DItype
__ashldi3 (DItype u, word_type b)
अणु
  DIजोड़ w;
  word_type bm;
  DIजोड़ uu;

  अगर (b == 0)
    वापस u;

  uu.ll = u;

  bm = (माप (SItype) * BITS_PER_UNIT) - b;
  अगर (bm <= 0)
    अणु
      w.s.low = 0;
      w.s.high = (USItype)uu.s.low << -bm;
    पूर्ण
  अन्यथा
    अणु
      USItype carries = (USItype)uu.s.low >> bm;
      w.s.low = (USItype)uu.s.low << b;
      w.s.high = ((USItype)uu.s.high << b) | carries;
    पूर्ण

  वापस w.ll;
पूर्ण
EXPORT_SYMBOL(__ashldi3);
