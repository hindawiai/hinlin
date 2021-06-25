<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#समावेश "bw_fixed.h"


#घोषणा MIN_I64 \
	(पूर्णांक64_t)(-(1LL << 63))

#घोषणा MAX_I64 \
	(पूर्णांक64_t)((1ULL << 63) - 1)

#घोषणा FRACTIONAL_PART_MASK \
	((1ULL << BW_FIXED_BITS_PER_FRACTIONAL_PART) - 1)

#घोषणा GET_FRACTIONAL_PART(x) \
	(FRACTIONAL_PART_MASK & (x))

अटल uपूर्णांक64_t असल_i64(पूर्णांक64_t arg)
अणु
	अगर (arg >= 0)
		वापस (uपूर्णांक64_t)(arg);
	अन्यथा
		वापस (uपूर्णांक64_t)(-arg);
पूर्ण

काष्ठा bw_fixed bw_पूर्णांक_to_fixed_nonस्थिर(पूर्णांक64_t value)
अणु
	काष्ठा bw_fixed res;
	ASSERT(value < BW_FIXED_MAX_I32 && value > BW_FIXED_MIN_I32);
	res.value = value << BW_FIXED_BITS_PER_FRACTIONAL_PART;
	वापस res;
पूर्ण

काष्ठा bw_fixed bw_frc_to_fixed(पूर्णांक64_t numerator, पूर्णांक64_t denominator)
अणु
	काष्ठा bw_fixed res;
	bool arg1_negative = numerator < 0;
	bool arg2_negative = denominator < 0;
	uपूर्णांक64_t arg1_value;
	uपूर्णांक64_t arg2_value;
	uपूर्णांक64_t reमुख्यder;

	/* determine पूर्णांकeger part */
	uपूर्णांक64_t res_value;

	ASSERT(denominator != 0);

	arg1_value = असल_i64(numerator);
	arg2_value = असल_i64(denominator);
	res_value = भाग64_u64_rem(arg1_value, arg2_value, &reमुख्यder);

	ASSERT(res_value <= BW_FIXED_MAX_I32);

	/* determine fractional part */
	अणु
		uपूर्णांक32_t i = BW_FIXED_BITS_PER_FRACTIONAL_PART;

		करो
		अणु
			reमुख्यder <<= 1;

			res_value <<= 1;

			अगर (reमुख्यder >= arg2_value)
			अणु
				res_value |= 1;
				reमुख्यder -= arg2_value;
			पूर्ण
		पूर्ण जबतक (--i != 0);
	पूर्ण

	/* round up LSB */
	अणु
		uपूर्णांक64_t summand = (reमुख्यder << 1) >= arg2_value;

		ASSERT(res_value <= MAX_I64 - summand);

		res_value += summand;
	पूर्ण

	res.value = (पूर्णांक64_t)(res_value);

	अगर (arg1_negative ^ arg2_negative)
		res.value = -res.value;
	वापस res;
पूर्ण

काष्ठा bw_fixed bw_न्यूनमान2(
	स्थिर काष्ठा bw_fixed arg,
	स्थिर काष्ठा bw_fixed signअगरicance)
अणु
	काष्ठा bw_fixed result;
	पूर्णांक64_t multiplicand;

	multiplicand = भाग64_s64(arg.value, असल_i64(signअगरicance.value));
	result.value = असल_i64(signअगरicance.value) * multiplicand;
	ASSERT(असल_i64(result.value) <= असल_i64(arg.value));
	वापस result;
पूर्ण

काष्ठा bw_fixed bw_उच्चमान2(
	स्थिर काष्ठा bw_fixed arg,
	स्थिर काष्ठा bw_fixed signअगरicance)
अणु
	काष्ठा bw_fixed result;
	पूर्णांक64_t multiplicand;

	multiplicand = भाग64_s64(arg.value, असल_i64(signअगरicance.value));
	result.value = असल_i64(signअगरicance.value) * multiplicand;
	अगर (असल_i64(result.value) < असल_i64(arg.value)) अणु
		अगर (arg.value < 0)
			result.value -= असल_i64(signअगरicance.value);
		अन्यथा
			result.value += असल_i64(signअगरicance.value);
	पूर्ण
	वापस result;
पूर्ण

काष्ठा bw_fixed bw_mul(स्थिर काष्ठा bw_fixed arg1, स्थिर काष्ठा bw_fixed arg2)
अणु
	काष्ठा bw_fixed res;

	bool arg1_negative = arg1.value < 0;
	bool arg2_negative = arg2.value < 0;

	uपूर्णांक64_t arg1_value = असल_i64(arg1.value);
	uपूर्णांक64_t arg2_value = असल_i64(arg2.value);

	uपूर्णांक64_t arg1_पूर्णांक = BW_FIXED_GET_INTEGER_PART(arg1_value);
	uपूर्णांक64_t arg2_पूर्णांक = BW_FIXED_GET_INTEGER_PART(arg2_value);

	uपूर्णांक64_t arg1_fra = GET_FRACTIONAL_PART(arg1_value);
	uपूर्णांक64_t arg2_fra = GET_FRACTIONAL_PART(arg2_value);

	uपूर्णांक64_t पंचांगp;

	res.value = arg1_पूर्णांक * arg2_पूर्णांक;

	ASSERT(res.value <= BW_FIXED_MAX_I32);

	res.value <<= BW_FIXED_BITS_PER_FRACTIONAL_PART;

	पंचांगp = arg1_पूर्णांक * arg2_fra;

	ASSERT(पंचांगp <= (uपूर्णांक64_t)(MAX_I64 - res.value));

	res.value += पंचांगp;

	पंचांगp = arg2_पूर्णांक * arg1_fra;

	ASSERT(पंचांगp <= (uपूर्णांक64_t)(MAX_I64 - res.value));

	res.value += पंचांगp;

	पंचांगp = arg1_fra * arg2_fra;

	पंचांगp = (पंचांगp >> BW_FIXED_BITS_PER_FRACTIONAL_PART) +
		(पंचांगp >= (uपूर्णांक64_t)(bw_frc_to_fixed(1, 2).value));

	ASSERT(पंचांगp <= (uपूर्णांक64_t)(MAX_I64 - res.value));

	res.value += पंचांगp;

	अगर (arg1_negative ^ arg2_negative)
		res.value = -res.value;
	वापस res;
पूर्ण

