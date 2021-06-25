<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __MATH_SUPPORT_H
#घोषणा __MATH_SUPPORT_H

#समावेश <linux/kernel.h> /* Override the definition of max/min from linux kernel*/

#घोषणा IS_ODD(a)            ((a) & 0x1)
#घोषणा IS_EVEN(a)           (!IS_ODD(a))

/* क्रमce a value to a lower even value */
#घोषणा EVEN_FLOOR(x)        ((x) & ~1)

/* ISP2401 */
/* If the number is odd, find the next even number */
#घोषणा EVEN_CEIL(x)         ((IS_ODD(x)) ? ((x) + 1) : (x))

/* A => B */
#घोषणा IMPLIES(a, b)        (!(a) || (b))

/* क्रम preprocessor and array sizing use MIN and MAX
   otherwise use min and max */
#घोषणा MAX(a, b)            (((a) > (b)) ? (a) : (b))
#घोषणा MIN(a, b)            (((a) < (b)) ? (a) : (b))

#घोषणा ROUND_DIV(a, b)      (((b) != 0) ? ((a) + ((b) >> 1)) / (b) : 0)
#घोषणा CEIL_DIV(a, b)       (((b) != 0) ? ((a) + (b) - 1) / (b) : 0)
#घोषणा CEIL_MUL(a, b)       (CEIL_DIV(a, b) * (b))
#घोषणा CEIL_MUL2(a, b)      (((a) + (b) - 1) & ~((b) - 1))
#घोषणा CEIL_SHIFT(a, b)     (((a) + (1 << (b)) - 1) >> (b))
#घोषणा CEIL_SHIFT_MUL(a, b) (CEIL_SHIFT(a, b) << (b))
#घोषणा ROUND_HALF_DOWN_DIV(a, b)	(((b) != 0) ? ((a) + (b / 2) - 1) / (b) : 0)
#घोषणा ROUND_HALF_DOWN_MUL(a, b)	(ROUND_HALF_DOWN_DIV(a, b) * (b))

/*To Find next घातer of 2 number from x */
#घोषणा bit2(x)            ((x)      | ((x) >> 1))
#घोषणा bit4(x)            (bit2(x)  | (bit2(x) >> 2))
#घोषणा bit8(x)            (bit4(x)  | (bit4(x) >> 4))
#घोषणा bit16(x)           (bit8(x)  | (bit8(x) >> 8))
#घोषणा bit32(x)           (bit16(x) | (bit16(x) >> 16))
#घोषणा NEXT_POWER_OF_2(x) (bit32(x - 1) + 1)

/* min and max should not be macros as they will evaluate their arguments twice.
   अगर you really need a macro (e.g. क्रम CPP or क्रम initializing an array)
   use MIN() and MAX(), otherwise use min() and max().

*/

#अगर !defined(PIPE_GENERATION)

/*
This macro versions are added back as we are mixing types in usage of अंतरभूत.
This causes corner हालs of calculations to be incorrect due to conversions
between चिन्हित and अचिन्हित variables or overflows.
Beक्रमe the addition of the अंतरभूत functions, max, min and उच्चमान_भाग were macros
and thereक्रमe adding them back.

Leaving out the other math utility functions as they are newly added
*/

#घोषणा उच्चमान_भाग(a, b)		(CEIL_DIV(a, b))

अटल अंतरभूत अचिन्हित पूर्णांक उच्चमान_mul(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	वापस CEIL_MUL(a, b);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक उच्चमान_mul2(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	वापस CEIL_MUL2(a, b);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक उच्चमान_shअगरt(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	वापस CEIL_SHIFT(a, b);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक उच्चमान_shअगरt_mul(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	वापस CEIL_SHIFT_MUL(a, b);
पूर्ण

/* ISP2401 */
अटल अंतरभूत अचिन्हित पूर्णांक round_half_करोwn_भाग(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	वापस ROUND_HALF_DOWN_DIV(a, b);
पूर्ण

/* ISP2401 */
अटल अंतरभूत अचिन्हित पूर्णांक round_half_करोwn_mul(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	वापस ROUND_HALF_DOWN_MUL(a, b);
पूर्ण

/* @brief Next Power of Two
 *
 *  @param[in] अचिन्हित number
 *
 *  @वापस next घातer of two
 *
 * This function rounds input to the nearest घातer of 2 (2^x)
 * towards infinity
 *
 * Input Range: 0 .. 2^(8*माप(पूर्णांक)-1)
 *
 * IF input is a घातer of 2
 *     out = in
 * OTHERWISE
 *     out = 2^(उच्चमान(log2(in))
 *
 */

अटल अंतरभूत अचिन्हित पूर्णांक उच्चमान_घात2(अचिन्हित पूर्णांक a)
अणु
	अगर (a == 0) अणु
		वापस 1;
	पूर्ण
	/* IF input is alपढ़ोy a घातer of two*/
	अन्यथा अगर ((!((a) & ((a) - 1)))) अणु
		वापस a;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक v = a;

		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		वापस (v + 1);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* !defined(PIPE_GENERATION) */

/*
 * For SP and ISP, SDK provides the definition of OP_std_modadd.
 * We need it only क्रम host
 */
#घोषणा OP_std_modadd(base, offset, size) ((base + offset) % (size))

#पूर्ण_अगर /* __MATH_SUPPORT_H */
