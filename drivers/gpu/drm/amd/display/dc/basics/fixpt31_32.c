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
#समावेश "include/fixed31_32.h"

अटल स्थिर काष्ठा fixed31_32 dc_fixpt_two_pi = अणु 26986075409LL पूर्ण;
अटल स्थिर काष्ठा fixed31_32 dc_fixpt_ln2 = अणु 2977044471LL पूर्ण;
अटल स्थिर काष्ठा fixed31_32 dc_fixpt_ln2_भाग_2 = अणु 1488522236LL पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ असल_i64(
	दीर्घ दीर्घ arg)
अणु
	अगर (arg > 0)
		वापस (अचिन्हित दीर्घ दीर्घ)arg;
	अन्यथा
		वापस (अचिन्हित दीर्घ दीर्घ)(-arg);
पूर्ण

/*
 * @brief
 * result = भागidend / भागisor
 * *reमुख्यder = भागidend % भागisor
 */
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ complete_पूर्णांकeger_भागision_u64(
	अचिन्हित दीर्घ दीर्घ भागidend,
	अचिन्हित दीर्घ दीर्घ भागisor,
	अचिन्हित दीर्घ दीर्घ *reमुख्यder)
अणु
	अचिन्हित दीर्घ दीर्घ result;

	ASSERT(भागisor);

	result = भाग64_u64_rem(भागidend, भागisor, reमुख्यder);

	वापस result;
पूर्ण


#घोषणा FRACTIONAL_PART_MASK \
	((1ULL << FIXED31_32_BITS_PER_FRACTIONAL_PART) - 1)

#घोषणा GET_INTEGER_PART(x) \
	((x) >> FIXED31_32_BITS_PER_FRACTIONAL_PART)

#घोषणा GET_FRACTIONAL_PART(x) \
	(FRACTIONAL_PART_MASK & (x))

काष्ठा fixed31_32 dc_fixpt_from_fraction(दीर्घ दीर्घ numerator, दीर्घ दीर्घ denominator)
अणु
	काष्ठा fixed31_32 res;

	bool arg1_negative = numerator < 0;
	bool arg2_negative = denominator < 0;

	अचिन्हित दीर्घ दीर्घ arg1_value = arg1_negative ? -numerator : numerator;
	अचिन्हित दीर्घ दीर्घ arg2_value = arg2_negative ? -denominator : denominator;

	अचिन्हित दीर्घ दीर्घ reमुख्यder;

	/* determine पूर्णांकeger part */

	अचिन्हित दीर्घ दीर्घ res_value = complete_पूर्णांकeger_भागision_u64(
		arg1_value, arg2_value, &reमुख्यder);

	ASSERT(res_value <= दीर्घ_उच्च);

	/* determine fractional part */
	अणु
		अचिन्हित पूर्णांक i = FIXED31_32_BITS_PER_FRACTIONAL_PART;

		करो अणु
			reमुख्यder <<= 1;

			res_value <<= 1;

			अगर (reमुख्यder >= arg2_value) अणु
				res_value |= 1;
				reमुख्यder -= arg2_value;
			पूर्ण
		पूर्ण जबतक (--i != 0);
	पूर्ण

	/* round up LSB */
	अणु
		अचिन्हित दीर्घ दीर्घ summand = (reमुख्यder << 1) >= arg2_value;

		ASSERT(res_value <= Lदीर्घ_उच्च - summand);

		res_value += summand;
	पूर्ण

	res.value = (दीर्घ दीर्घ)res_value;

	अगर (arg1_negative ^ arg2_negative)
		res.value = -res.value;

	वापस res;
पूर्ण

काष्ठा fixed31_32 dc_fixpt_mul(काष्ठा fixed31_32 arg1, काष्ठा fixed31_32 arg2)
अणु
	काष्ठा fixed31_32 res;

	bool arg1_negative = arg1.value < 0;
	bool arg2_negative = arg2.value < 0;

	अचिन्हित दीर्घ दीर्घ arg1_value = arg1_negative ? -arg1.value : arg1.value;
	अचिन्हित दीर्घ दीर्घ arg2_value = arg2_negative ? -arg2.value : arg2.value;

	अचिन्हित दीर्घ दीर्घ arg1_पूर्णांक = GET_INTEGER_PART(arg1_value);
	अचिन्हित दीर्घ दीर्घ arg2_पूर्णांक = GET_INTEGER_PART(arg2_value);

	अचिन्हित दीर्घ दीर्घ arg1_fra = GET_FRACTIONAL_PART(arg1_value);
	अचिन्हित दीर्घ दीर्घ arg2_fra = GET_FRACTIONAL_PART(arg2_value);

	अचिन्हित दीर्घ दीर्घ पंचांगp;

	res.value = arg1_पूर्णांक * arg2_पूर्णांक;

	ASSERT(res.value <= दीर्घ_उच्च);

	res.value <<= FIXED31_32_BITS_PER_FRACTIONAL_PART;

	पंचांगp = arg1_पूर्णांक * arg2_fra;

	ASSERT(पंचांगp <= (अचिन्हित दीर्घ दीर्घ)(Lदीर्घ_उच्च - res.value));

	res.value += पंचांगp;

	पंचांगp = arg2_पूर्णांक * arg1_fra;

	ASSERT(पंचांगp <= (अचिन्हित दीर्घ दीर्घ)(Lदीर्घ_उच्च - res.value));

	res.value += पंचांगp;

	पंचांगp = arg1_fra * arg2_fra;

	पंचांगp = (पंचांगp >> FIXED31_32_BITS_PER_FRACTIONAL_PART) +
		(पंचांगp >= (अचिन्हित दीर्घ दीर्घ)dc_fixpt_half.value);

	ASSERT(पंचांगp <= (अचिन्हित दीर्घ दीर्घ)(Lदीर्घ_उच्च - res.value));

	res.value += पंचांगp;

	अगर (arg1_negative ^ arg2_negative)
		res.value = -res.value;

	वापस res;
पूर्ण

काष्ठा fixed31_32 dc_fixpt_sqr(काष्ठा fixed31_32 arg)
अणु
	काष्ठा fixed31_32 res;

	अचिन्हित दीर्घ दीर्घ arg_value = असल_i64(arg.value);

	अचिन्हित दीर्घ दीर्घ arg_पूर्णांक = GET_INTEGER_PART(arg_value);

	अचिन्हित दीर्घ दीर्घ arg_fra = GET_FRACTIONAL_PART(arg_value);

	अचिन्हित दीर्घ दीर्घ पंचांगp;

	res.value = arg_पूर्णांक * arg_पूर्णांक;

	ASSERT(res.value <= दीर्घ_उच्च);

	res.value <<= FIXED31_32_BITS_PER_FRACTIONAL_PART;

	पंचांगp = arg_पूर्णांक * arg_fra;

	ASSERT(पंचांगp <= (अचिन्हित दीर्घ दीर्घ)(Lदीर्घ_उच्च - res.value));

	res.value += पंचांगp;

	ASSERT(पंचांगp <= (अचिन्हित दीर्घ दीर्घ)(Lदीर्घ_उच्च - res.value));

	res.value += पंचांगp;

	पंचांगp = arg_fra * arg_fra;

	पंचांगp = (पंचांगp >> FIXED31_32_BITS_PER_FRACTIONAL_PART) +
		(पंचांगp >= (अचिन्हित दीर्घ दीर्घ)dc_fixpt_half.value);

	ASSERT(पंचांगp <= (अचिन्हित दीर्घ दीर्घ)(Lदीर्घ_उच्च - res.value));

	res.value += पंचांगp;

	वापस res;
पूर्ण

काष्ठा fixed31_32 dc_fixpt_recip(काष्ठा fixed31_32 arg)
अणु
	/*
	 * @note
	 * Good idea to use Newton's method
	 */

	ASSERT(arg.value);

	वापस dc_fixpt_from_fraction(
		dc_fixpt_one.value,
		arg.value);
पूर्ण

काष्ठा fixed31_32 dc_fixpt_sinc(काष्ठा fixed31_32 arg)
अणु
	काष्ठा fixed31_32 square;

	काष्ठा fixed31_32 res = dc_fixpt_one;

	पूर्णांक n = 27;

	काष्ठा fixed31_32 arg_norm = arg;

	अगर (dc_fixpt_le(
		dc_fixpt_two_pi,
		dc_fixpt_असल(arg))) अणु
		arg_norm = dc_fixpt_sub(
			arg_norm,
			dc_fixpt_mul_पूर्णांक(
				dc_fixpt_two_pi,
				(पूर्णांक)भाग64_s64(
					arg_norm.value,
					dc_fixpt_two_pi.value)));
	पूर्ण

	square = dc_fixpt_sqr(arg_norm);

	करो अणु
		res = dc_fixpt_sub(
			dc_fixpt_one,
			dc_fixpt_भाग_पूर्णांक(
				dc_fixpt_mul(
					square,
					res),
				n * (n - 1)));

		n -= 2;
	पूर्ण जबतक (n > 2);

	अगर (arg.value != arg_norm.value)
		res = dc_fixpt_भाग(
			dc_fixpt_mul(res, arg_norm),
			arg);

	वापस res;
पूर्ण

काष्ठा fixed31_32 dc_fixpt_sin(काष्ठा fixed31_32 arg)
अणु
	वापस dc_fixpt_mul(
		arg,
		dc_fixpt_sinc(arg));
पूर्ण

काष्ठा fixed31_32 dc_fixpt_cos(काष्ठा fixed31_32 arg)
अणु
	/* TODO implement argument normalization */

	स्थिर काष्ठा fixed31_32 square = dc_fixpt_sqr(arg);

	काष्ठा fixed31_32 res = dc_fixpt_one;

	पूर्णांक n = 26;

	करो अणु
		res = dc_fixpt_sub(
			dc_fixpt_one,
			dc_fixpt_भाग_पूर्णांक(
				dc_fixpt_mul(
					square,
					res),
				n * (n - 1)));

		n -= 2;
	पूर्ण जबतक (n != 0);

	वापस res;
पूर्ण

/*
 * @brief
 * result = exp(arg),
 * where असल(arg) < 1
 *
 * Calculated as Taylor series.
 */
अटल काष्ठा fixed31_32 fixed31_32_exp_from_taylor_series(काष्ठा fixed31_32 arg)
अणु
	अचिन्हित पूर्णांक n = 9;

	काष्ठा fixed31_32 res = dc_fixpt_from_fraction(
		n + 2,
		n + 1);
	/* TODO find correct res */

	ASSERT(dc_fixpt_lt(arg, dc_fixpt_one));

	करो
		res = dc_fixpt_add(
			dc_fixpt_one,
			dc_fixpt_भाग_पूर्णांक(
				dc_fixpt_mul(
					arg,
					res),
				n));
	जबतक (--n != 1);

	वापस dc_fixpt_add(
		dc_fixpt_one,
		dc_fixpt_mul(
			arg,
			res));
पूर्ण

काष्ठा fixed31_32 dc_fixpt_exp(काष्ठा fixed31_32 arg)
अणु
	/*
	 * @brief
	 * Main equation is:
	 * exp(x) = exp(r + m * ln(2)) = (1 << m) * exp(r),
	 * where m = round(x / ln(2)), r = x - m * ln(2)
	 */

	अगर (dc_fixpt_le(
		dc_fixpt_ln2_भाग_2,
		dc_fixpt_असल(arg))) अणु
		पूर्णांक m = dc_fixpt_round(
			dc_fixpt_भाग(
				arg,
				dc_fixpt_ln2));

		काष्ठा fixed31_32 r = dc_fixpt_sub(
			arg,
			dc_fixpt_mul_पूर्णांक(
				dc_fixpt_ln2,
				m));

		ASSERT(m != 0);

		ASSERT(dc_fixpt_lt(
			dc_fixpt_असल(r),
			dc_fixpt_one));

		अगर (m > 0)
			वापस dc_fixpt_shl(
				fixed31_32_exp_from_taylor_series(r),
				(अचिन्हित अक्षर)m);
		अन्यथा
			वापस dc_fixpt_भाग_पूर्णांक(
				fixed31_32_exp_from_taylor_series(r),
				1LL << -m);
	पूर्ण अन्यथा अगर (arg.value != 0)
		वापस fixed31_32_exp_from_taylor_series(arg);
	अन्यथा
		वापस dc_fixpt_one;
पूर्ण

काष्ठा fixed31_32 dc_fixpt_log(काष्ठा fixed31_32 arg)
अणु
	काष्ठा fixed31_32 res = dc_fixpt_neg(dc_fixpt_one);
	/* TODO improve 1st estimation */

	काष्ठा fixed31_32 error;

	ASSERT(arg.value > 0);
	/* TODO अगर arg is negative, वापस NaN */
	/* TODO अगर arg is zero, वापस -INF */

	करो अणु
		काष्ठा fixed31_32 res1 = dc_fixpt_add(
			dc_fixpt_sub(
				res,
				dc_fixpt_one),
			dc_fixpt_भाग(
				arg,
				dc_fixpt_exp(res)));

		error = dc_fixpt_sub(
			res,
			res1);

		res = res1;
		/* TODO determine max_allowed_error based on quality of exp() */
	पूर्ण जबतक (असल_i64(error.value) > 100ULL);

	वापस res;
पूर्ण


/* this function is a generic helper to translate fixed poपूर्णांक value to
 * specअगरied पूर्णांकeger क्रमmat that will consist of पूर्णांकeger_bits पूर्णांकeger part and
 * fractional_bits fractional part. For example it is used in
 * dc_fixpt_u2d19 to receive 2 bits पूर्णांकeger part and 19 bits fractional
 * part in 32 bits. It is used in hw programming (scaler)
 */

अटल अंतरभूत अचिन्हित पूर्णांक ux_dy(
	दीर्घ दीर्घ value,
	अचिन्हित पूर्णांक पूर्णांकeger_bits,
	अचिन्हित पूर्णांक fractional_bits)
अणु
	/* 1. create mask of पूर्णांकeger part */
	अचिन्हित पूर्णांक result = (1 << पूर्णांकeger_bits) - 1;
	/* 2. mask out fractional part */
	अचिन्हित पूर्णांक fractional_part = FRACTIONAL_PART_MASK & value;
	/* 3. shrink fixed poपूर्णांक पूर्णांकeger part to be of पूर्णांकeger_bits width*/
	result &= GET_INTEGER_PART(value);
	/* 4. make space क्रम fractional part to be filled in after पूर्णांकeger */
	result <<= fractional_bits;
	/* 5. shrink fixed poपूर्णांक fractional part to of fractional_bits width*/
	fractional_part >>= FIXED31_32_BITS_PER_FRACTIONAL_PART - fractional_bits;
	/* 6. merge the result */
	वापस result | fractional_part;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक clamp_ux_dy(
	दीर्घ दीर्घ value,
	अचिन्हित पूर्णांक पूर्णांकeger_bits,
	अचिन्हित पूर्णांक fractional_bits,
	अचिन्हित पूर्णांक min_clamp)
अणु
	अचिन्हित पूर्णांक truncated_val = ux_dy(value, पूर्णांकeger_bits, fractional_bits);

	अगर (value >= (1LL << (पूर्णांकeger_bits + FIXED31_32_BITS_PER_FRACTIONAL_PART)))
		वापस (1 << (पूर्णांकeger_bits + fractional_bits)) - 1;
	अन्यथा अगर (truncated_val > min_clamp)
		वापस truncated_val;
	अन्यथा
		वापस min_clamp;
पूर्ण

अचिन्हित पूर्णांक dc_fixpt_u4d19(काष्ठा fixed31_32 arg)
अणु
	वापस ux_dy(arg.value, 4, 19);
पूर्ण

अचिन्हित पूर्णांक dc_fixpt_u3d19(काष्ठा fixed31_32 arg)
अणु
	वापस ux_dy(arg.value, 3, 19);
पूर्ण

अचिन्हित पूर्णांक dc_fixpt_u2d19(काष्ठा fixed31_32 arg)
अणु
	वापस ux_dy(arg.value, 2, 19);
पूर्ण

अचिन्हित पूर्णांक dc_fixpt_u0d19(काष्ठा fixed31_32 arg)
अणु
	वापस ux_dy(arg.value, 0, 19);
पूर्ण

अचिन्हित पूर्णांक dc_fixpt_clamp_u0d14(काष्ठा fixed31_32 arg)
अणु
	वापस clamp_ux_dy(arg.value, 0, 14, 1);
पूर्ण

अचिन्हित पूर्णांक dc_fixpt_clamp_u0d10(काष्ठा fixed31_32 arg)
अणु
	वापस clamp_ux_dy(arg.value, 0, 10, 1);
पूर्ण

पूर्णांक dc_fixpt_s4d19(काष्ठा fixed31_32 arg)
अणु
	अगर (arg.value < 0)
		वापस -(पूर्णांक)ux_dy(dc_fixpt_असल(arg).value, 4, 19);
	अन्यथा
		वापस ux_dy(arg.value, 4, 19);
पूर्ण
