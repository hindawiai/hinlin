<शैली गुरु>
/* ashrdi3.c extracted from gcc-2.7.2/libgcc2.c which is: */
/* Copyright (C) 1989, 1992, 1993, 1994, 1995 Free Software Foundation, Inc.

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
__ashrdi3 (DItype u, word_type b)
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
      /* w.s.high = 1..1 or 0..0 */
      w.s.high = uu.s.high >> (माप (SItype) * BITS_PER_UNIT - 1);
      w.s.low = uu.s.high >> -bm;
    पूर्ण
  अन्यथा
    अणु
      USItype carries = (USItype)uu.s.high << bm;
      w.s.high = uu.s.high >> b;
      w.s.low = ((USItype)uu.s.low >> b) | carries;
    पूर्ण

  वापस w.ll;
पूर्ण
EXPORT_SYMBOL(__ashrdi3);
