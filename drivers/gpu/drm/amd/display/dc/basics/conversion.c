<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश "dm_services.h"
#समावेश "conversion.h"

#घोषणा DIVIDER 10000

/* S2D13 value in [-3.00...0.9999] */
#घोषणा S2D13_MIN (-3 * DIVIDER)
#घोषणा S2D13_MAX (3 * DIVIDER)

uपूर्णांक16_t fixed_poपूर्णांक_to_पूर्णांक_frac(
	काष्ठा fixed31_32 arg,
	uपूर्णांक8_t पूर्णांकeger_bits,
	uपूर्णांक8_t fractional_bits)
अणु
	पूर्णांक32_t numerator;
	पूर्णांक32_t भागisor = 1 << fractional_bits;

	uपूर्णांक16_t result;

	uपूर्णांक16_t d = (uपूर्णांक16_t)dc_fixpt_न्यूनमान(
		dc_fixpt_असल(
			arg));

	अगर (d <= (uपूर्णांक16_t)(1 << पूर्णांकeger_bits) - (1 / (uपूर्णांक16_t)भागisor))
		numerator = (uपूर्णांक16_t)dc_fixpt_round(
			dc_fixpt_mul_पूर्णांक(
				arg,
				भागisor));
	अन्यथा अणु
		numerator = dc_fixpt_न्यूनमान(
			dc_fixpt_sub(
				dc_fixpt_from_पूर्णांक(
					1LL << पूर्णांकeger_bits),
				dc_fixpt_recip(
					dc_fixpt_from_पूर्णांक(
						भागisor))));
	पूर्ण

	अगर (numerator >= 0)
		result = (uपूर्णांक16_t)numerator;
	अन्यथा
		result = (uपूर्णांक16_t)(
		(1 << (पूर्णांकeger_bits + fractional_bits + 1)) + numerator);

	अगर ((result != 0) && dc_fixpt_lt(
		arg, dc_fixpt_zero))
		result |= 1 << (पूर्णांकeger_bits + fractional_bits);

	वापस result;
पूर्ण
/*
 * convert_भग्न_matrix - This converts a द्विगुन पूर्णांकo HW रेजिस्टर spec defined क्रमmat S2D13.
 */
व्योम convert_भग्न_matrix(
	uपूर्णांक16_t *matrix,
	काष्ठा fixed31_32 *flt,
	uपूर्णांक32_t buffer_size)
अणु
	स्थिर काष्ठा fixed31_32 min_2_13 =
		dc_fixpt_from_fraction(S2D13_MIN, DIVIDER);
	स्थिर काष्ठा fixed31_32 max_2_13 =
		dc_fixpt_from_fraction(S2D13_MAX, DIVIDER);
	uपूर्णांक32_t i;

	क्रम (i = 0; i < buffer_size; ++i) अणु
		uपूर्णांक32_t reg_value =
				fixed_poपूर्णांक_to_पूर्णांक_frac(
					dc_fixpt_clamp(
						flt[i],
						min_2_13,
						max_2_13),
						2,
						13);

		matrix[i] = (uपूर्णांक16_t)reg_value;
	पूर्ण
पूर्ण
