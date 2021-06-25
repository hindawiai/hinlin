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

#अगर_अघोषित __DAL_FIXED31_32_H__
#घोषणा __DAL_FIXED31_32_H__

#अगर_अघोषित Lदीर्घ_उच्च
#घोषणा Lदीर्घ_उच्च 9223372036854775807ll
#पूर्ण_अगर
#अगर_अघोषित Lदीर्घ_न्यून
#घोषणा Lदीर्घ_न्यून (-Lदीर्घ_उच्च - 1ll)
#पूर्ण_अगर

#घोषणा FIXED31_32_BITS_PER_FRACTIONAL_PART 32
#अगर_अघोषित Lदीर्घ_न्यून
#घोषणा Lदीर्घ_न्यून (1LL<<63)
#पूर्ण_अगर
#अगर_अघोषित Lदीर्घ_उच्च
#घोषणा Lदीर्घ_उच्च (-1LL>>1)
#पूर्ण_अगर

/*
 * @brief
 * Arithmetic operations on real numbers
 * represented as fixed-poपूर्णांक numbers.
 * There are: 1 bit क्रम sign,
 * 31 bit क्रम पूर्णांकeger part,
 * 32 bits क्रम fractional part.
 *
 * @note
 * Currently, overflows and underflows are निश्चितed;
 * no special result वापसed.
 */

काष्ठा fixed31_32 अणु
	दीर्घ दीर्घ value;
पूर्ण;


/*
 * @brief
 * Useful स्थिरants
 */

अटल स्थिर काष्ठा fixed31_32 dc_fixpt_zero = अणु 0 पूर्ण;
अटल स्थिर काष्ठा fixed31_32 dc_fixpt_epsilon = अणु 1LL पूर्ण;
अटल स्थिर काष्ठा fixed31_32 dc_fixpt_half = अणु 0x80000000LL पूर्ण;
अटल स्थिर काष्ठा fixed31_32 dc_fixpt_one = अणु 0x100000000LL पूर्ण;

/*
 * @brief
 * Initialization routines
 */

/*
 * @brief
 * result = numerator / denominator
 */
काष्ठा fixed31_32 dc_fixpt_from_fraction(दीर्घ दीर्घ numerator, दीर्घ दीर्घ denominator);

/*
 * @brief
 * result = arg
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_from_पूर्णांक(पूर्णांक arg)
अणु
	काष्ठा fixed31_32 res;

	res.value = (दीर्घ दीर्घ) arg << FIXED31_32_BITS_PER_FRACTIONAL_PART;

	वापस res;
पूर्ण

/*
 * @brief
 * Unary चालकs
 */

/*
 * @brief
 * result = -arg
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_neg(काष्ठा fixed31_32 arg)
अणु
	काष्ठा fixed31_32 res;

	res.value = -arg.value;

	वापस res;
पूर्ण

/*
 * @brief
 * result = असल(arg) := (arg >= 0) ? arg : -arg
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_असल(काष्ठा fixed31_32 arg)
अणु
	अगर (arg.value < 0)
		वापस dc_fixpt_neg(arg);
	अन्यथा
		वापस arg;
पूर्ण

/*
 * @brief
 * Binary relational चालकs
 */

/*
 * @brief
 * result = arg1 < arg2
 */
अटल अंतरभूत bool dc_fixpt_lt(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	वापस arg1.value < arg2.value;
पूर्ण

/*
 * @brief
 * result = arg1 <= arg2
 */
अटल अंतरभूत bool dc_fixpt_le(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	वापस arg1.value <= arg2.value;
पूर्ण

/*
 * @brief
 * result = arg1 == arg2
 */
अटल अंतरभूत bool dc_fixpt_eq(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	वापस arg1.value == arg2.value;
पूर्ण

/*
 * @brief
 * result = min(arg1, arg2) := (arg1 <= arg2) ? arg1 : arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_min(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	अगर (arg1.value <= arg2.value)
		वापस arg1;
	अन्यथा
		वापस arg2;
पूर्ण

/*
 * @brief
 * result = max(arg1, arg2) := (arg1 <= arg2) ? arg2 : arg1
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_max(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	अगर (arg1.value <= arg2.value)
		वापस arg2;
	अन्यथा
		वापस arg1;
पूर्ण

/*
 * @brief
 *          | min_value, when arg <= min_value
 * result = | arg, when min_value < arg < max_value
 *          | max_value, when arg >= max_value
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_clamp(
	काष्ठा fixed31_32 arg,
	काष्ठा fixed31_32 min_value,
	काष्ठा fixed31_32 max_value)
अणु
	अगर (dc_fixpt_le(arg, min_value))
		वापस min_value;
	अन्यथा अगर (dc_fixpt_le(max_value, arg))
		वापस max_value;
	अन्यथा
		वापस arg;
पूर्ण

/*
 * @brief
 * Binary shअगरt चालकs
 */

/*
 * @brief
 * result = arg << shअगरt
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_shl(काष्ठा fixed31_32 arg, अचिन्हित अक्षर shअगरt)
अणु
	ASSERT(((arg.value >= 0) && (arg.value <= Lदीर्घ_उच्च >> shअगरt)) ||
		((arg.value < 0) && (arg.value >= ~(Lदीर्घ_उच्च >> shअगरt))));

	arg.value = arg.value << shअगरt;

	वापस arg;
पूर्ण

/*
 * @brief
 * result = arg >> shअगरt
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_shr(काष्ठा fixed31_32 arg, अचिन्हित अक्षर shअगरt)
अणु
	bool negative = arg.value < 0;

	अगर (negative)
		arg.value = -arg.value;
	arg.value = arg.value >> shअगरt;
	अगर (negative)
		arg.value = -arg.value;
	वापस arg;
पूर्ण

/*
 * @brief
 * Binary additive चालकs
 */

/*
 * @brief
 * result = arg1 + arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_add(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	काष्ठा fixed31_32 res;

	ASSERT(((arg1.value >= 0) && (Lदीर्घ_उच्च - arg1.value >= arg2.value)) ||
		((arg1.value < 0) && (Lदीर्घ_न्यून - arg1.value <= arg2.value)));

	res.value = arg1.value + arg2.value;

	वापस res;
पूर्ण

/*
 * @brief
 * result = arg1 + arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_add_पूर्णांक(काष्ठा fixed31_32 arg1, पूर्णांक arg2)
अणु
	वापस dc_fixpt_add(arg1, dc_fixpt_from_पूर्णांक(arg2));
पूर्ण

/*
 * @brief
 * result = arg1 - arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_sub(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	काष्ठा fixed31_32 res;

	ASSERT(((arg2.value >= 0) && (Lदीर्घ_न्यून + arg2.value <= arg1.value)) ||
		((arg2.value < 0) && (Lदीर्घ_उच्च + arg2.value >= arg1.value)));

	res.value = arg1.value - arg2.value;

	वापस res;
पूर्ण

/*
 * @brief
 * result = arg1 - arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_sub_पूर्णांक(काष्ठा fixed31_32 arg1, पूर्णांक arg2)
अणु
	वापस dc_fixpt_sub(arg1, dc_fixpt_from_पूर्णांक(arg2));
पूर्ण


/*
 * @brief
 * Binary multiplicative चालकs
 */

/*
 * @brief
 * result = arg1 * arg2
 */
काष्ठा fixed31_32 dc_fixpt_mul(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2);


/*
 * @brief
 * result = arg1 * arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_mul_पूर्णांक(काष्ठा fixed31_32 arg1, पूर्णांक arg2)
अणु
	वापस dc_fixpt_mul(arg1, dc_fixpt_from_पूर्णांक(arg2));
पूर्ण

/*
 * @brief
 * result = square(arg) := arg * arg
 */
काष्ठा fixed31_32 dc_fixpt_sqr(काष्ठा fixed31_32 arg);

/*
 * @brief
 * result = arg1 / arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_भाग_पूर्णांक(काष्ठा fixed31_32 arg1, दीर्घ दीर्घ arg2)
अणु
	वापस dc_fixpt_from_fraction(arg1.value, dc_fixpt_from_पूर्णांक(arg2).value);
पूर्ण

/*
 * @brief
 * result = arg1 / arg2
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_भाग(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	वापस dc_fixpt_from_fraction(arg1.value, arg2.value);
पूर्ण

/*
 * @brief
 * Reciprocal function
 */

/*
 * @brief
 * result = reciprocal(arg) := 1 / arg
 *
 * @note
 * No special actions taken in हाल argument is zero.
 */
काष्ठा fixed31_32 dc_fixpt_recip(काष्ठा fixed31_32 arg);

/*
 * @brief
 * Trigonometric functions
 */

/*
 * @brief
 * result = sinc(arg) := sin(arg) / arg
 *
 * @note
 * Argument specअगरied in radians,
 * पूर्णांकernally it's normalized to [-2pi...2pi] range.
 */
काष्ठा fixed31_32 dc_fixpt_sinc(काष्ठा fixed31_32 arg);

/*
 * @brief
 * result = sin(arg)
 *
 * @note
 * Argument specअगरied in radians,
 * पूर्णांकernally it's normalized to [-2pi...2pi] range.
 */
काष्ठा fixed31_32 dc_fixpt_sin(काष्ठा fixed31_32 arg);

/*
 * @brief
 * result = cos(arg)
 *
 * @note
 * Argument specअगरied in radians
 * and should be in [-2pi...2pi] range -
 * passing arguments outside that range
 * will cause incorrect result!
 */
काष्ठा fixed31_32 dc_fixpt_cos(काष्ठा fixed31_32 arg);

/*
 * @brief
 * Transcendent functions
 */

/*
 * @brief
 * result = exp(arg)
 *
 * @note
 * Currently, function is verअगरied क्रम असल(arg) <= 1.
 */
काष्ठा fixed31_32 dc_fixpt_exp(काष्ठा fixed31_32 arg);

/*
 * @brief
 * result = log(arg)
 *
 * @note
 * Currently, असल(arg) should be less than 1.
 * No normalization is करोne.
 * Currently, no special actions taken
 * in हाल of invalid argument(s). Take care!
 */
काष्ठा fixed31_32 dc_fixpt_log(काष्ठा fixed31_32 arg);

/*
 * @brief
 * Power function
 */

/*
 * @brief
 * result = घात(arg1, arg2)
 *
 * @note
 * Currently, असल(arg1) should be less than 1. Take care!
 */
अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_घात(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	अगर (arg1.value == 0)
		वापस arg2.value == 0 ? dc_fixpt_one : dc_fixpt_zero;

	वापस dc_fixpt_exp(
		dc_fixpt_mul(
			dc_fixpt_log(arg1),
			arg2));
पूर्ण

/*
 * @brief
 * Rounding functions
 */

/*
 * @brief
 * result = न्यूनमान(arg) := greatest पूर्णांकeger lower than or equal to arg
 */
अटल अंतरभूत पूर्णांक dc_fixpt_न्यूनमान(काष्ठा fixed31_32 arg)
अणु
	अचिन्हित दीर्घ दीर्घ arg_value = arg.value > 0 ? arg.value : -arg.value;

	अगर (arg.value >= 0)
		वापस (पूर्णांक)(arg_value >> FIXED31_32_BITS_PER_FRACTIONAL_PART);
	अन्यथा
		वापस -(पूर्णांक)(arg_value >> FIXED31_32_BITS_PER_FRACTIONAL_PART);
पूर्ण

/*
 * @brief
 * result = round(arg) := पूर्णांकeger nearest to arg
 */
अटल अंतरभूत पूर्णांक dc_fixpt_round(काष्ठा fixed31_32 arg)
अणु
	अचिन्हित दीर्घ दीर्घ arg_value = arg.value > 0 ? arg.value : -arg.value;

	स्थिर दीर्घ दीर्घ summand = dc_fixpt_half.value;

	ASSERT(Lदीर्घ_उच्च - (दीर्घ दीर्घ)arg_value >= summand);

	arg_value += summand;

	अगर (arg.value >= 0)
		वापस (पूर्णांक)(arg_value >> FIXED31_32_BITS_PER_FRACTIONAL_PART);
	अन्यथा
		वापस -(पूर्णांक)(arg_value >> FIXED31_32_BITS_PER_FRACTIONAL_PART);
पूर्ण

/*
 * @brief
 * result = उच्चमान(arg) := lowest पूर्णांकeger greater than or equal to arg
 */
अटल अंतरभूत पूर्णांक dc_fixpt_उच्चमान(काष्ठा fixed31_32 arg)
अणु
	अचिन्हित दीर्घ दीर्घ arg_value = arg.value > 0 ? arg.value : -arg.value;

	स्थिर दीर्घ दीर्घ summand = dc_fixpt_one.value -
		dc_fixpt_epsilon.value;

	ASSERT(Lदीर्घ_उच्च - (दीर्घ दीर्घ)arg_value >= summand);

	arg_value += summand;

	अगर (arg.value >= 0)
		वापस (पूर्णांक)(arg_value >> FIXED31_32_BITS_PER_FRACTIONAL_PART);
	अन्यथा
		वापस -(पूर्णांक)(arg_value >> FIXED31_32_BITS_PER_FRACTIONAL_PART);
पूर्ण

/* the following two function are used in scaler hw programming to convert fixed
 * poपूर्णांक value to क्रमmat 2 bits from पूर्णांकeger part and 19 bits from fractional
 * part. The same applies क्रम u0d19, 0 bits from पूर्णांकeger part and 19 bits from
 * fractional
 */

अचिन्हित पूर्णांक dc_fixpt_u4d19(काष्ठा fixed31_32 arg);

अचिन्हित पूर्णांक dc_fixpt_u3d19(काष्ठा fixed31_32 arg);

अचिन्हित पूर्णांक dc_fixpt_u2d19(काष्ठा fixed31_32 arg);

अचिन्हित पूर्णांक dc_fixpt_u0d19(काष्ठा fixed31_32 arg);

अचिन्हित पूर्णांक dc_fixpt_clamp_u0d14(काष्ठा fixed31_32 arg);

अचिन्हित पूर्णांक dc_fixpt_clamp_u0d10(काष्ठा fixed31_32 arg);

पूर्णांक dc_fixpt_s4d19(काष्ठा fixed31_32 arg);

अटल अंतरभूत काष्ठा fixed31_32 dc_fixpt_truncate(काष्ठा fixed31_32 arg, अचिन्हित पूर्णांक frac_bits)
अणु
	bool negative = arg.value < 0;

	अगर (frac_bits >= FIXED31_32_BITS_PER_FRACTIONAL_PART) अणु
		ASSERT(frac_bits == FIXED31_32_BITS_PER_FRACTIONAL_PART);
		वापस arg;
	पूर्ण

	अगर (negative)
		arg.value = -arg.value;
	arg.value &= (~0LL) << (FIXED31_32_BITS_PER_FRACTIONAL_PART - frac_bits);
	अगर (negative)
		arg.value = -arg.value;
	वापस arg;
पूर्ण

#पूर्ण_अगर
