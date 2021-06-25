<शैली गुरु>
/*
 * dvb-math provides some complex fixed-poपूर्णांक math
 * operations shared between the dvb related stuff
 *
 * Copyright (C) 2006 Christoph Pfister (christophpfister@gmail.com)
 *
 * This library is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License क्रम more details.
 */

#अगर_अघोषित __DVB_MATH_H
#घोषणा __DVB_MATH_H

#समावेश <linux/types.h>

/**
 * पूर्णांकlog2 - computes log2 of a value; the result is shअगरted left by 24 bits
 *
 * @value: The value (must be != 0)
 *
 * to use rational values you can use the following method:
 *
 *   पूर्णांकlog2(value) = पूर्णांकlog2(value * 2^x) - x * 2^24
 *
 * Some useहाल examples:
 *
 *	पूर्णांकlog2(8) will give 3 << 24 = 3 * 2^24
 *
 *	पूर्णांकlog2(9) will give 3 << 24 + ... = 3.16... * 2^24
 *
 *	पूर्णांकlog2(1.5) = पूर्णांकlog2(3) - 2^24 = 0.584... * 2^24
 *
 *
 * वापस: log2(value) * 2^24
 */
बाह्य अचिन्हित पूर्णांक पूर्णांकlog2(u32 value);

/**
 * पूर्णांकlog10 - computes log10 of a value; the result is shअगरted left by 24 bits
 *
 * @value: The value (must be != 0)
 *
 * to use rational values you can use the following method:
 *
 *   पूर्णांकlog10(value) = पूर्णांकlog10(value * 10^x) - x * 2^24
 *
 * An useहाल example:
 *
 *	पूर्णांकlog10(1000) will give 3 << 24 = 3 * 2^24
 *
 *   due to the implementation पूर्णांकlog10(1000) might be not exactly 3 * 2^24
 *
 * look at पूर्णांकlog2 क्रम similar examples
 *
 * वापस: log10(value) * 2^24
 */
बाह्य अचिन्हित पूर्णांक पूर्णांकlog10(u32 value);

#पूर्ण_अगर
