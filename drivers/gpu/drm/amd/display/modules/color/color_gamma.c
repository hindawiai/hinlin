<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "dc.h"
#समावेश "opp.h"
#समावेश "color_gamma.h"

/* When calculating LUT values the first region and at least one subsequent
 * region are calculated with full precision. These defines are a demarcation
 * of where the second region starts and ends.
 * These are hardcoded values to aव्योम recalculating them in loops.
 */
#घोषणा PRECISE_LUT_REGION_START 224
#घोषणा PRECISE_LUT_REGION_END 239

अटल काष्ठा hw_x_poपूर्णांक coordinates_x[MAX_HW_POINTS + 2];

// these are helpers क्रम calculations to reduce stack usage
// करो not depend on these being preserved across calls

/* Helper to optimize gamma calculation, only use in translate_from_linear, in
 * particular the dc_fixpt_घात function which is very expensive
 * The idea is that our regions क्रम X poपूर्णांकs are exponential and currently they all use
 * the same number of poपूर्णांकs (NUM_PTS_IN_REGION) and in each region every poपूर्णांक
 * is exactly 2x the one at the same index in the previous region. In other words
 * X[i] = 2 * X[i-NUM_PTS_IN_REGION] क्रम i>=16
 * The other fact is that (2x)^gamma = 2^gamma * x^gamma
 * So we compute and save x^gamma क्रम the first 16 regions, and क्रम every next region
 * just multiply with 2^gamma which can be computed once, and save the result so we
 * recursively compute all the values.
 */
										/*sRGB	 709 2.2 2.4 P3*/
अटल स्थिर पूर्णांक32_t gamma_numerator01[] = अणु 31308,	180000,	0,	0,	0पूर्ण;
अटल स्थिर पूर्णांक32_t gamma_numerator02[] = अणु 12920,	4500,	0,	0,	0पूर्ण;
अटल स्थिर पूर्णांक32_t gamma_numerator03[] = अणु 55,	99,		0,	0,	0पूर्ण;
अटल स्थिर पूर्णांक32_t gamma_numerator04[] = अणु 55,	99,		0,	0,	0पूर्ण;
अटल स्थिर पूर्णांक32_t gamma_numerator05[] = अणु 2400,	2200,	2200, 2400, 2600पूर्ण;

/* one-समय setup of X poपूर्णांकs */
व्योम setup_x_poपूर्णांकs_distribution(व्योम)
अणु
	काष्ठा fixed31_32 region_size = dc_fixpt_from_पूर्णांक(128);
	पूर्णांक32_t segment;
	uपूर्णांक32_t seg_offset;
	uपूर्णांक32_t index;
	काष्ठा fixed31_32 increment;

	coordinates_x[MAX_HW_POINTS].x = region_size;
	coordinates_x[MAX_HW_POINTS + 1].x = region_size;

	क्रम (segment = 6; segment > (6 - NUM_REGIONS); segment--) अणु
		region_size = dc_fixpt_भाग_पूर्णांक(region_size, 2);
		increment = dc_fixpt_भाग_पूर्णांक(region_size,
						NUM_PTS_IN_REGION);
		seg_offset = (segment + (NUM_REGIONS - 7)) * NUM_PTS_IN_REGION;
		coordinates_x[seg_offset].x = region_size;

		क्रम (index = seg_offset + 1;
				index < seg_offset + NUM_PTS_IN_REGION;
				index++) अणु
			coordinates_x[index].x = dc_fixpt_add
					(coordinates_x[index-1].x, increment);
		पूर्ण
	पूर्ण
पूर्ण

व्योम log_x_poपूर्णांकs_distribution(काष्ठा dal_logger *logger)
अणु
	पूर्णांक i = 0;

	अगर (logger != शून्य) अणु
		LOG_GAMMA_WRITE("Log X Distribution\n");

		क्रम (i = 0; i < MAX_HW_POINTS; i++)
			LOG_GAMMA_WRITE("%llu\n", coordinates_x[i].x.value);
	पूर्ण
पूर्ण

अटल व्योम compute_pq(काष्ठा fixed31_32 in_x, काष्ठा fixed31_32 *out_y)
अणु
	/* स्थिरs क्रम PQ gamma क्रमmula. */
	स्थिर काष्ठा fixed31_32 m1 =
		dc_fixpt_from_fraction(159301758, 1000000000);
	स्थिर काष्ठा fixed31_32 m2 =
		dc_fixpt_from_fraction(7884375, 100000);
	स्थिर काष्ठा fixed31_32 c1 =
		dc_fixpt_from_fraction(8359375, 10000000);
	स्थिर काष्ठा fixed31_32 c2 =
		dc_fixpt_from_fraction(188515625, 10000000);
	स्थिर काष्ठा fixed31_32 c3 =
		dc_fixpt_from_fraction(186875, 10000);

	काष्ठा fixed31_32 l_घात_m1;
	काष्ठा fixed31_32 base;

	अगर (dc_fixpt_lt(in_x, dc_fixpt_zero))
		in_x = dc_fixpt_zero;

	l_घात_m1 = dc_fixpt_घात(in_x, m1);
	base = dc_fixpt_भाग(
			dc_fixpt_add(c1,
					(dc_fixpt_mul(c2, l_घात_m1))),
			dc_fixpt_add(dc_fixpt_one,
					(dc_fixpt_mul(c3, l_घात_m1))));
	*out_y = dc_fixpt_घात(base, m2);
पूर्ण

अटल व्योम compute_de_pq(काष्ठा fixed31_32 in_x, काष्ठा fixed31_32 *out_y)
अणु
	/* स्थिरs क्रम dePQ gamma क्रमmula. */
	स्थिर काष्ठा fixed31_32 m1 =
		dc_fixpt_from_fraction(159301758, 1000000000);
	स्थिर काष्ठा fixed31_32 m2 =
		dc_fixpt_from_fraction(7884375, 100000);
	स्थिर काष्ठा fixed31_32 c1 =
		dc_fixpt_from_fraction(8359375, 10000000);
	स्थिर काष्ठा fixed31_32 c2 =
		dc_fixpt_from_fraction(188515625, 10000000);
	स्थिर काष्ठा fixed31_32 c3 =
		dc_fixpt_from_fraction(186875, 10000);

	काष्ठा fixed31_32 l_घात_m1;
	काष्ठा fixed31_32 base, भाग;
	काष्ठा fixed31_32 base2;


	अगर (dc_fixpt_lt(in_x, dc_fixpt_zero))
		in_x = dc_fixpt_zero;

	l_घात_m1 = dc_fixpt_घात(in_x,
			dc_fixpt_भाग(dc_fixpt_one, m2));
	base = dc_fixpt_sub(l_घात_m1, c1);

	भाग = dc_fixpt_sub(c2, dc_fixpt_mul(c3, l_घात_m1));

	base2 = dc_fixpt_भाग(base, भाग);
	// aव्योम complex numbers
	अगर (dc_fixpt_lt(base2, dc_fixpt_zero))
		base2 = dc_fixpt_sub(dc_fixpt_zero, base2);


	*out_y = dc_fixpt_घात(base2, dc_fixpt_भाग(dc_fixpt_one, m1));

पूर्ण


/* de gamma, non-linear to linear */
अटल व्योम compute_hlg_eotf(काष्ठा fixed31_32 in_x,
		काष्ठा fixed31_32 *out_y,
		uपूर्णांक32_t sdr_white_level, uपूर्णांक32_t max_luminance_nits)
अणु
	काष्ठा fixed31_32 a;
	काष्ठा fixed31_32 b;
	काष्ठा fixed31_32 c;
	काष्ठा fixed31_32 threshold;
	काष्ठा fixed31_32 x;

	काष्ठा fixed31_32 scaling_factor =
			dc_fixpt_from_fraction(max_luminance_nits, sdr_white_level);
	a = dc_fixpt_from_fraction(17883277, 100000000);
	b = dc_fixpt_from_fraction(28466892, 100000000);
	c = dc_fixpt_from_fraction(55991073, 100000000);
	threshold = dc_fixpt_from_fraction(1, 2);

	अगर (dc_fixpt_lt(in_x, threshold)) अणु
		x = dc_fixpt_mul(in_x, in_x);
		x = dc_fixpt_भाग_पूर्णांक(x, 3);
	पूर्ण अन्यथा अणु
		x = dc_fixpt_sub(in_x, c);
		x = dc_fixpt_भाग(x, a);
		x = dc_fixpt_exp(x);
		x = dc_fixpt_add(x, b);
		x = dc_fixpt_भाग_पूर्णांक(x, 12);
	पूर्ण
	*out_y = dc_fixpt_mul(x, scaling_factor);

पूर्ण

/* re gamma, linear to non-linear */
अटल व्योम compute_hlg_oetf(काष्ठा fixed31_32 in_x, काष्ठा fixed31_32 *out_y,
		uपूर्णांक32_t sdr_white_level, uपूर्णांक32_t max_luminance_nits)
अणु
	काष्ठा fixed31_32 a;
	काष्ठा fixed31_32 b;
	काष्ठा fixed31_32 c;
	काष्ठा fixed31_32 threshold;
	काष्ठा fixed31_32 x;

	काष्ठा fixed31_32 scaling_factor =
			dc_fixpt_from_fraction(sdr_white_level, max_luminance_nits);
	a = dc_fixpt_from_fraction(17883277, 100000000);
	b = dc_fixpt_from_fraction(28466892, 100000000);
	c = dc_fixpt_from_fraction(55991073, 100000000);
	threshold = dc_fixpt_from_fraction(1, 12);
	x = dc_fixpt_mul(in_x, scaling_factor);


	अगर (dc_fixpt_lt(x, threshold)) अणु
		x = dc_fixpt_mul(x, dc_fixpt_from_fraction(3, 1));
		*out_y = dc_fixpt_घात(x, dc_fixpt_half);
	पूर्ण अन्यथा अणु
		x = dc_fixpt_mul(x, dc_fixpt_from_fraction(12, 1));
		x = dc_fixpt_sub(x, b);
		x = dc_fixpt_log(x);
		x = dc_fixpt_mul(a, x);
		*out_y = dc_fixpt_add(x, c);
	पूर्ण
पूर्ण


/* one-समय pre-compute PQ values - only क्रम sdr_white_level 80 */
व्योम precompute_pq(व्योम)
अणु
	पूर्णांक i;
	काष्ठा fixed31_32 x;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinates_x + 32;
	काष्ठा fixed31_32 scaling_factor =
			dc_fixpt_from_fraction(80, 10000);

	काष्ठा fixed31_32 *pq_table = mod_color_get_table(type_pq_table);

	/* घात function has problems with arguments too small */
	क्रम (i = 0; i < 32; i++)
		pq_table[i] = dc_fixpt_zero;

	क्रम (i = 32; i <= MAX_HW_POINTS; i++) अणु
		x = dc_fixpt_mul(coord_x->x, scaling_factor);
		compute_pq(x, &pq_table[i]);
		++coord_x;
	पूर्ण
पूर्ण

/* one-समय pre-compute dePQ values - only क्रम max pixel value 125 FP16 */
व्योम precompute_de_pq(व्योम)
अणु
	पूर्णांक i;
	काष्ठा fixed31_32  y;
	uपूर्णांक32_t begin_index, end_index;

	काष्ठा fixed31_32 scaling_factor = dc_fixpt_from_पूर्णांक(125);
	काष्ठा fixed31_32 *de_pq_table = mod_color_get_table(type_de_pq_table);
	/* X poपूर्णांकs is 2^-25 to 2^7
	 * De-gamma X is 2^-12 to 2^0 ै  we are skipping first -12-(-25) = 13 regions
	 */
	begin_index = 13 * NUM_PTS_IN_REGION;
	end_index = begin_index + 12 * NUM_PTS_IN_REGION;

	क्रम (i = 0; i <= begin_index; i++)
		de_pq_table[i] = dc_fixpt_zero;

	क्रम (; i <= end_index; i++) अणु
		compute_de_pq(coordinates_x[i].x, &y);
		de_pq_table[i] = dc_fixpt_mul(y, scaling_factor);
	पूर्ण

	क्रम (; i <= MAX_HW_POINTS; i++)
		de_pq_table[i] = de_pq_table[i-1];
पूर्ण
काष्ठा भागiders अणु
	काष्ठा fixed31_32 भागider1;
	काष्ठा fixed31_32 भागider2;
	काष्ठा fixed31_32 भागider3;
पूर्ण;


अटल bool build_coefficients(काष्ठा gamma_coefficients *coefficients, क्रमागत dc_transfer_func_predefined type)
अणु

	uपूर्णांक32_t i = 0;
	uपूर्णांक32_t index = 0;
	bool ret = true;

	अगर (type == TRANSFER_FUNCTION_SRGB)
		index = 0;
	अन्यथा अगर (type == TRANSFER_FUNCTION_BT709)
		index = 1;
	अन्यथा अगर (type == TRANSFER_FUNCTION_GAMMA22)
		index = 2;
	अन्यथा अगर (type == TRANSFER_FUNCTION_GAMMA24)
		index = 3;
	अन्यथा अगर (type == TRANSFER_FUNCTION_GAMMA26)
		index = 4;
	अन्यथा अणु
		ret = false;
		जाओ release;
	पूर्ण

	करो अणु
		coefficients->a0[i] = dc_fixpt_from_fraction(
			gamma_numerator01[index], 10000000);
		coefficients->a1[i] = dc_fixpt_from_fraction(
			gamma_numerator02[index], 1000);
		coefficients->a2[i] = dc_fixpt_from_fraction(
			gamma_numerator03[index], 1000);
		coefficients->a3[i] = dc_fixpt_from_fraction(
			gamma_numerator04[index], 1000);
		coefficients->user_gamma[i] = dc_fixpt_from_fraction(
			gamma_numerator05[index], 1000);

		++i;
	पूर्ण जबतक (i != ARRAY_SIZE(coefficients->a0));
release:
	वापस ret;
पूर्ण

अटल काष्ठा fixed31_32 translate_from_linear_space(
		काष्ठा translate_from_linear_space_args *args)
अणु
	स्थिर काष्ठा fixed31_32 one = dc_fixpt_from_पूर्णांक(1);

	काष्ठा fixed31_32 scratch_1, scratch_2;
	काष्ठा calculate_buffer *cal_buffer = args->cal_buffer;

	अगर (dc_fixpt_le(one, args->arg))
		वापस one;

	अगर (dc_fixpt_le(args->arg, dc_fixpt_neg(args->a0))) अणु
		scratch_1 = dc_fixpt_add(one, args->a3);
		scratch_2 = dc_fixpt_घात(
				dc_fixpt_neg(args->arg),
				dc_fixpt_recip(args->gamma));
		scratch_1 = dc_fixpt_mul(scratch_1, scratch_2);
		scratch_1 = dc_fixpt_sub(args->a2, scratch_1);

		वापस scratch_1;
	पूर्ण अन्यथा अगर (dc_fixpt_le(args->a0, args->arg)) अणु
		अगर (cal_buffer->buffer_index == 0) अणु
			cal_buffer->gamma_of_2 = dc_fixpt_घात(dc_fixpt_from_पूर्णांक(2),
					dc_fixpt_recip(args->gamma));
		पूर्ण
		scratch_1 = dc_fixpt_add(one, args->a3);
		/* In the first region (first 16 poपूर्णांकs) and in the
		 * region delimited by START/END we calculate with
		 * full precision to aव्योम error accumulation. 
		 */
		अगर ((cal_buffer->buffer_index >= PRECISE_LUT_REGION_START &&
			cal_buffer->buffer_index <= PRECISE_LUT_REGION_END) ||
			(cal_buffer->buffer_index < 16))
			scratch_2 = dc_fixpt_घात(args->arg,
					dc_fixpt_recip(args->gamma));
		अन्यथा
			scratch_2 = dc_fixpt_mul(cal_buffer->gamma_of_2,
					cal_buffer->buffer[cal_buffer->buffer_index%16]);

		अगर (cal_buffer->buffer_index != -1) अणु
			cal_buffer->buffer[cal_buffer->buffer_index%16] = scratch_2;
			cal_buffer->buffer_index++;
		पूर्ण

		scratch_1 = dc_fixpt_mul(scratch_1, scratch_2);
		scratch_1 = dc_fixpt_sub(scratch_1, args->a2);

		वापस scratch_1;
	पूर्ण
	अन्यथा
		वापस dc_fixpt_mul(args->arg, args->a1);
पूर्ण


अटल काष्ठा fixed31_32 translate_from_linear_space_दीर्घ(
		काष्ठा translate_from_linear_space_args *args)
अणु
	स्थिर काष्ठा fixed31_32 one = dc_fixpt_from_पूर्णांक(1);

	अगर (dc_fixpt_lt(one, args->arg))
		वापस one;

	अगर (dc_fixpt_le(args->arg, dc_fixpt_neg(args->a0)))
		वापस dc_fixpt_sub(
			args->a2,
			dc_fixpt_mul(
				dc_fixpt_add(
					one,
					args->a3),
				dc_fixpt_घात(
					dc_fixpt_neg(args->arg),
					dc_fixpt_recip(args->gamma))));
	अन्यथा अगर (dc_fixpt_le(args->a0, args->arg))
		वापस dc_fixpt_sub(
			dc_fixpt_mul(
				dc_fixpt_add(
					one,
					args->a3),
				dc_fixpt_घात(
						args->arg,
					dc_fixpt_recip(args->gamma))),
					args->a2);
	अन्यथा
		वापस dc_fixpt_mul(args->arg, args->a1);
पूर्ण

अटल काष्ठा fixed31_32 calculate_gamma22(काष्ठा fixed31_32 arg, bool use_eetf, काष्ठा calculate_buffer *cal_buffer)
अणु
	काष्ठा fixed31_32 gamma = dc_fixpt_from_fraction(22, 10);
	काष्ठा translate_from_linear_space_args scratch_gamma_args;

	scratch_gamma_args.arg = arg;
	scratch_gamma_args.a0 = dc_fixpt_zero;
	scratch_gamma_args.a1 = dc_fixpt_zero;
	scratch_gamma_args.a2 = dc_fixpt_zero;
	scratch_gamma_args.a3 = dc_fixpt_zero;
	scratch_gamma_args.cal_buffer = cal_buffer;
	scratch_gamma_args.gamma = gamma;

	अगर (use_eetf)
		वापस translate_from_linear_space_दीर्घ(&scratch_gamma_args);

	वापस translate_from_linear_space(&scratch_gamma_args);
पूर्ण


अटल काष्ठा fixed31_32 translate_to_linear_space(
	काष्ठा fixed31_32 arg,
	काष्ठा fixed31_32 a0,
	काष्ठा fixed31_32 a1,
	काष्ठा fixed31_32 a2,
	काष्ठा fixed31_32 a3,
	काष्ठा fixed31_32 gamma)
अणु
	काष्ठा fixed31_32 linear;

	a0 = dc_fixpt_mul(a0, a1);
	अगर (dc_fixpt_le(arg, dc_fixpt_neg(a0)))

		linear = dc_fixpt_neg(
				 dc_fixpt_घात(
				 dc_fixpt_भाग(
				 dc_fixpt_sub(a2, arg),
				 dc_fixpt_add(
				 dc_fixpt_one, a3)), gamma));

	अन्यथा अगर (dc_fixpt_le(dc_fixpt_neg(a0), arg) &&
			 dc_fixpt_le(arg, a0))
		linear = dc_fixpt_भाग(arg, a1);
	अन्यथा
		linear =  dc_fixpt_घात(
					dc_fixpt_भाग(
					dc_fixpt_add(a2, arg),
					dc_fixpt_add(
					dc_fixpt_one, a3)), gamma);

	वापस linear;
पूर्ण

अटल काष्ठा fixed31_32 translate_from_linear_space_ex(
	काष्ठा fixed31_32 arg,
	काष्ठा gamma_coefficients *coeff,
	uपूर्णांक32_t color_index,
	काष्ठा calculate_buffer *cal_buffer)
अणु
	काष्ठा translate_from_linear_space_args scratch_gamma_args;

	scratch_gamma_args.arg = arg;
	scratch_gamma_args.a0 = coeff->a0[color_index];
	scratch_gamma_args.a1 = coeff->a1[color_index];
	scratch_gamma_args.a2 = coeff->a2[color_index];
	scratch_gamma_args.a3 = coeff->a3[color_index];
	scratch_gamma_args.gamma = coeff->user_gamma[color_index];
	scratch_gamma_args.cal_buffer = cal_buffer;

	वापस translate_from_linear_space(&scratch_gamma_args);
पूर्ण


अटल अंतरभूत काष्ठा fixed31_32 translate_to_linear_space_ex(
	काष्ठा fixed31_32 arg,
	काष्ठा gamma_coefficients *coeff,
	uपूर्णांक32_t color_index)
अणु
	वापस translate_to_linear_space(
		arg,
		coeff->a0[color_index],
		coeff->a1[color_index],
		coeff->a2[color_index],
		coeff->a3[color_index],
		coeff->user_gamma[color_index]);
पूर्ण


अटल bool find_software_poपूर्णांकs(
	स्थिर काष्ठा dc_gamma *ramp,
	स्थिर काष्ठा gamma_pixel *axis_x,
	काष्ठा fixed31_32 hw_poपूर्णांक,
	क्रमागत channel_name channel,
	uपूर्णांक32_t *index_to_start,
	uपूर्णांक32_t *index_left,
	uपूर्णांक32_t *index_right,
	क्रमागत hw_poपूर्णांक_position *pos)
अणु
	स्थिर uपूर्णांक32_t max_number = ramp->num_entries + 3;

	काष्ठा fixed31_32 left, right;

	uपूर्णांक32_t i = *index_to_start;

	जबतक (i < max_number) अणु
		अगर (channel == CHANNEL_NAME_RED) अणु
			left = axis_x[i].r;

			अगर (i < max_number - 1)
				right = axis_x[i + 1].r;
			अन्यथा
				right = axis_x[max_number - 1].r;
		पूर्ण अन्यथा अगर (channel == CHANNEL_NAME_GREEN) अणु
			left = axis_x[i].g;

			अगर (i < max_number - 1)
				right = axis_x[i + 1].g;
			अन्यथा
				right = axis_x[max_number - 1].g;
		पूर्ण अन्यथा अणु
			left = axis_x[i].b;

			अगर (i < max_number - 1)
				right = axis_x[i + 1].b;
			अन्यथा
				right = axis_x[max_number - 1].b;
		पूर्ण

		अगर (dc_fixpt_le(left, hw_poपूर्णांक) &&
			dc_fixpt_le(hw_poपूर्णांक, right)) अणु
			*index_to_start = i;
			*index_left = i;

			अगर (i < max_number - 1)
				*index_right = i + 1;
			अन्यथा
				*index_right = max_number - 1;

			*pos = HW_POINT_POSITION_MIDDLE;

			वापस true;
		पूर्ण अन्यथा अगर ((i == *index_to_start) &&
			dc_fixpt_le(hw_poपूर्णांक, left)) अणु
			*index_to_start = i;
			*index_left = i;
			*index_right = i;

			*pos = HW_POINT_POSITION_LEFT;

			वापस true;
		पूर्ण अन्यथा अगर ((i == max_number - 1) &&
			dc_fixpt_le(right, hw_poपूर्णांक)) अणु
			*index_to_start = i;
			*index_left = i;
			*index_right = i;

			*pos = HW_POINT_POSITION_RIGHT;

			वापस true;
		पूर्ण

		++i;
	पूर्ण

	वापस false;
पूर्ण

अटल bool build_custom_gamma_mapping_coefficients_worker(
	स्थिर काष्ठा dc_gamma *ramp,
	काष्ठा pixel_gamma_poपूर्णांक *coeff,
	स्थिर काष्ठा hw_x_poपूर्णांक *coordinates_x,
	स्थिर काष्ठा gamma_pixel *axis_x,
	क्रमागत channel_name channel,
	uपूर्णांक32_t number_of_poपूर्णांकs)
अणु
	uपूर्णांक32_t i = 0;

	जबतक (i <= number_of_poपूर्णांकs) अणु
		काष्ठा fixed31_32 coord_x;

		uपूर्णांक32_t index_to_start = 0;
		uपूर्णांक32_t index_left = 0;
		uपूर्णांक32_t index_right = 0;

		क्रमागत hw_poपूर्णांक_position hw_pos;

		काष्ठा gamma_poपूर्णांक *poपूर्णांक;

		काष्ठा fixed31_32 left_pos;
		काष्ठा fixed31_32 right_pos;

		अगर (channel == CHANNEL_NAME_RED)
			coord_x = coordinates_x[i].regamma_y_red;
		अन्यथा अगर (channel == CHANNEL_NAME_GREEN)
			coord_x = coordinates_x[i].regamma_y_green;
		अन्यथा
			coord_x = coordinates_x[i].regamma_y_blue;

		अगर (!find_software_poपूर्णांकs(
			ramp, axis_x, coord_x, channel,
			&index_to_start, &index_left, &index_right, &hw_pos)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (index_left >= ramp->num_entries + 3) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (index_right >= ramp->num_entries + 3) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (channel == CHANNEL_NAME_RED) अणु
			poपूर्णांक = &coeff[i].r;

			left_pos = axis_x[index_left].r;
			right_pos = axis_x[index_right].r;
		पूर्ण अन्यथा अगर (channel == CHANNEL_NAME_GREEN) अणु
			poपूर्णांक = &coeff[i].g;

			left_pos = axis_x[index_left].g;
			right_pos = axis_x[index_right].g;
		पूर्ण अन्यथा अणु
			poपूर्णांक = &coeff[i].b;

			left_pos = axis_x[index_left].b;
			right_pos = axis_x[index_right].b;
		पूर्ण

		अगर (hw_pos == HW_POINT_POSITION_MIDDLE)
			poपूर्णांक->coeff = dc_fixpt_भाग(
				dc_fixpt_sub(
					coord_x,
					left_pos),
				dc_fixpt_sub(
					right_pos,
					left_pos));
		अन्यथा अगर (hw_pos == HW_POINT_POSITION_LEFT)
			poपूर्णांक->coeff = dc_fixpt_zero;
		अन्यथा अगर (hw_pos == HW_POINT_POSITION_RIGHT)
			poपूर्णांक->coeff = dc_fixpt_from_पूर्णांक(2);
		अन्यथा अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		poपूर्णांक->left_index = index_left;
		poपूर्णांक->right_index = index_right;
		poपूर्णांक->pos = hw_pos;

		++i;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा fixed31_32 calculate_mapped_value(
	काष्ठा pwl_भग्न_data *rgb,
	स्थिर काष्ठा pixel_gamma_poपूर्णांक *coeff,
	क्रमागत channel_name channel,
	uपूर्णांक32_t max_index)
अणु
	स्थिर काष्ठा gamma_poपूर्णांक *poपूर्णांक;

	काष्ठा fixed31_32 result;

	अगर (channel == CHANNEL_NAME_RED)
		poपूर्णांक = &coeff->r;
	अन्यथा अगर (channel == CHANNEL_NAME_GREEN)
		poपूर्णांक = &coeff->g;
	अन्यथा
		poपूर्णांक = &coeff->b;

	अगर ((poपूर्णांक->left_index < 0) || (poपूर्णांक->left_index > max_index)) अणु
		BREAK_TO_DEBUGGER();
		वापस dc_fixpt_zero;
	पूर्ण

	अगर ((poपूर्णांक->right_index < 0) || (poपूर्णांक->right_index > max_index)) अणु
		BREAK_TO_DEBUGGER();
		वापस dc_fixpt_zero;
	पूर्ण

	अगर (poपूर्णांक->pos == HW_POINT_POSITION_MIDDLE)
		अगर (channel == CHANNEL_NAME_RED)
			result = dc_fixpt_add(
				dc_fixpt_mul(
					poपूर्णांक->coeff,
					dc_fixpt_sub(
						rgb[poपूर्णांक->right_index].r,
						rgb[poपूर्णांक->left_index].r)),
				rgb[poपूर्णांक->left_index].r);
		अन्यथा अगर (channel == CHANNEL_NAME_GREEN)
			result = dc_fixpt_add(
				dc_fixpt_mul(
					poपूर्णांक->coeff,
					dc_fixpt_sub(
						rgb[poपूर्णांक->right_index].g,
						rgb[poपूर्णांक->left_index].g)),
				rgb[poपूर्णांक->left_index].g);
		अन्यथा
			result = dc_fixpt_add(
				dc_fixpt_mul(
					poपूर्णांक->coeff,
					dc_fixpt_sub(
						rgb[poपूर्णांक->right_index].b,
						rgb[poपूर्णांक->left_index].b)),
				rgb[poपूर्णांक->left_index].b);
	अन्यथा अगर (poपूर्णांक->pos == HW_POINT_POSITION_LEFT) अणु
		BREAK_TO_DEBUGGER();
		result = dc_fixpt_zero;
	पूर्ण अन्यथा अणु
		result = dc_fixpt_one;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम build_pq(काष्ठा pwl_भग्न_data_ex *rgb_regamma,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा hw_x_poपूर्णांक *coordinate_x,
		uपूर्णांक32_t sdr_white_level)
अणु
	uपूर्णांक32_t i, start_index;

	काष्ठा pwl_भग्न_data_ex *rgb = rgb_regamma;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinate_x;
	काष्ठा fixed31_32 x;
	काष्ठा fixed31_32 output;
	काष्ठा fixed31_32 scaling_factor =
			dc_fixpt_from_fraction(sdr_white_level, 10000);
	काष्ठा fixed31_32 *pq_table = mod_color_get_table(type_pq_table);

	अगर (!mod_color_is_table_init(type_pq_table) && sdr_white_level == 80) अणु
		precompute_pq();
		mod_color_set_table_init_state(type_pq_table, true);
	पूर्ण

	/* TODO: start index is from segment 2^-24, skipping first segment
	 * due to x values too small क्रम घातer calculations
	 */
	start_index = 32;
	rgb += start_index;
	coord_x += start_index;

	क्रम (i = start_index; i <= hw_poपूर्णांकs_num; i++) अणु
		/* Multiply 0.008 as regamma is 0-1 and FP16 input is 0-125.
		 * FP 1.0 = 80nits
		 */
		अगर (sdr_white_level == 80) अणु
			output = pq_table[i];
		पूर्ण अन्यथा अणु
			x = dc_fixpt_mul(coord_x->x, scaling_factor);
			compute_pq(x, &output);
		पूर्ण

		/* should really not happen? */
		अगर (dc_fixpt_lt(output, dc_fixpt_zero))
			output = dc_fixpt_zero;
		अन्यथा अगर (dc_fixpt_lt(dc_fixpt_one, output))
			output = dc_fixpt_one;

		rgb->r = output;
		rgb->g = output;
		rgb->b = output;

		++coord_x;
		++rgb;
	पूर्ण
पूर्ण

अटल व्योम build_de_pq(काष्ठा pwl_भग्न_data_ex *de_pq,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा hw_x_poपूर्णांक *coordinate_x)
अणु
	uपूर्णांक32_t i;
	काष्ठा fixed31_32 output;
	काष्ठा fixed31_32 *de_pq_table = mod_color_get_table(type_de_pq_table);
	काष्ठा fixed31_32 scaling_factor = dc_fixpt_from_पूर्णांक(125);

	अगर (!mod_color_is_table_init(type_de_pq_table)) अणु
		precompute_de_pq();
		mod_color_set_table_init_state(type_de_pq_table, true);
	पूर्ण


	क्रम (i = 0; i <= hw_poपूर्णांकs_num; i++) अणु
		output = de_pq_table[i];
		/* should really not happen? */
		अगर (dc_fixpt_lt(output, dc_fixpt_zero))
			output = dc_fixpt_zero;
		अन्यथा अगर (dc_fixpt_lt(scaling_factor, output))
			output = scaling_factor;
		de_pq[i].r = output;
		de_pq[i].g = output;
		de_pq[i].b = output;
	पूर्ण
पूर्ण

अटल bool build_regamma(काष्ठा pwl_भग्न_data_ex *rgb_regamma,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा hw_x_poपूर्णांक *coordinate_x,
		क्रमागत dc_transfer_func_predefined type,
		काष्ठा calculate_buffer *cal_buffer)
अणु
	uपूर्णांक32_t i;
	bool ret = false;

	काष्ठा gamma_coefficients *coeff;
	काष्ठा pwl_भग्न_data_ex *rgb = rgb_regamma;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinate_x;

	coeff = kvzalloc(माप(*coeff), GFP_KERNEL);
	अगर (!coeff)
		जाओ release;

	अगर (!build_coefficients(coeff, type))
		जाओ release;

	स_रखो(cal_buffer->buffer, 0, NUM_PTS_IN_REGION * माप(काष्ठा fixed31_32));
	cal_buffer->buffer_index = 0; // see variable definition क्रम more info

	i = 0;
	जबतक (i <= hw_poपूर्णांकs_num) अणु
		/* TODO use y vs r,g,b */
		rgb->r = translate_from_linear_space_ex(
			coord_x->x, coeff, 0, cal_buffer);
		rgb->g = rgb->r;
		rgb->b = rgb->r;
		++coord_x;
		++rgb;
		++i;
	पूर्ण
	cal_buffer->buffer_index = -1;
	ret = true;
release:
	kvमुक्त(coeff);
	वापस ret;
पूर्ण

अटल व्योम hermite_spline_eetf(काष्ठा fixed31_32 input_x,
				काष्ठा fixed31_32 max_display,
				काष्ठा fixed31_32 min_display,
				काष्ठा fixed31_32 max_content,
				काष्ठा fixed31_32 *out_x)
अणु
	काष्ठा fixed31_32 min_lum_pq;
	काष्ठा fixed31_32 max_lum_pq;
	काष्ठा fixed31_32 max_content_pq;
	काष्ठा fixed31_32 ks;
	काष्ठा fixed31_32 E1;
	काष्ठा fixed31_32 E2;
	काष्ठा fixed31_32 E3;
	काष्ठा fixed31_32 t;
	काष्ठा fixed31_32 t2;
	काष्ठा fixed31_32 t3;
	काष्ठा fixed31_32 two;
	काष्ठा fixed31_32 three;
	काष्ठा fixed31_32 temp1;
	काष्ठा fixed31_32 temp2;
	काष्ठा fixed31_32 a = dc_fixpt_from_fraction(15, 10);
	काष्ठा fixed31_32 b = dc_fixpt_from_fraction(5, 10);
	काष्ठा fixed31_32 epsilon = dc_fixpt_from_fraction(1, 1000000); // dc_fixpt_epsilon is a bit too small

	अगर (dc_fixpt_eq(max_content, dc_fixpt_zero)) अणु
		*out_x = dc_fixpt_zero;
		वापस;
	पूर्ण

	compute_pq(input_x, &E1);
	compute_pq(dc_fixpt_भाग(min_display, max_content), &min_lum_pq);
	compute_pq(dc_fixpt_भाग(max_display, max_content), &max_lum_pq);
	compute_pq(dc_fixpt_one, &max_content_pq); // always 1? DAL2 code is weird
	a = dc_fixpt_भाग(dc_fixpt_add(dc_fixpt_one, b), max_content_pq); // (1+b)/maxContent
	ks = dc_fixpt_sub(dc_fixpt_mul(a, max_lum_pq), b); // a * max_lum_pq - b

	अगर (dc_fixpt_lt(E1, ks))
		E2 = E1;
	अन्यथा अगर (dc_fixpt_le(ks, E1) && dc_fixpt_le(E1, dc_fixpt_one)) अणु
		अगर (dc_fixpt_lt(epsilon, dc_fixpt_sub(dc_fixpt_one, ks)))
			// t = (E1 - ks) / (1 - ks)
			t = dc_fixpt_भाग(dc_fixpt_sub(E1, ks),
					dc_fixpt_sub(dc_fixpt_one, ks));
		अन्यथा
			t = dc_fixpt_zero;

		two = dc_fixpt_from_पूर्णांक(2);
		three = dc_fixpt_from_पूर्णांक(3);

		t2 = dc_fixpt_mul(t, t);
		t3 = dc_fixpt_mul(t2, t);
		temp1 = dc_fixpt_mul(two, t3);
		temp2 = dc_fixpt_mul(three, t2);

		// (2t^3 - 3t^2 + 1) * ks
		E2 = dc_fixpt_mul(ks, dc_fixpt_add(dc_fixpt_one,
				dc_fixpt_sub(temp1, temp2)));

		// (-2t^3 + 3t^2) * max_lum_pq
		E2 = dc_fixpt_add(E2, dc_fixpt_mul(max_lum_pq,
				dc_fixpt_sub(temp2, temp1)));

		temp1 = dc_fixpt_mul(two, t2);
		temp2 = dc_fixpt_sub(dc_fixpt_one, ks);

		// (t^3 - 2t^2 + t) * (1-ks)
		E2 = dc_fixpt_add(E2, dc_fixpt_mul(temp2,
				dc_fixpt_add(t, dc_fixpt_sub(t3, temp1))));
	पूर्ण अन्यथा
		E2 = dc_fixpt_one;

	temp1 = dc_fixpt_sub(dc_fixpt_one, E2);
	temp2 = dc_fixpt_mul(temp1, temp1);
	temp2 = dc_fixpt_mul(temp2, temp2);
	// temp2 = (1-E2)^4

	E3 =  dc_fixpt_add(E2, dc_fixpt_mul(min_lum_pq, temp2));
	compute_de_pq(E3, out_x);

	*out_x = dc_fixpt_भाग(*out_x, dc_fixpt_भाग(max_display, max_content));
पूर्ण

अटल bool build_मुक्तsync_hdr(काष्ठा pwl_भग्न_data_ex *rgb_regamma,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा hw_x_poपूर्णांक *coordinate_x,
		स्थिर काष्ठा hdr_पंचांग_params *fs_params,
		काष्ठा calculate_buffer *cal_buffer)
अणु
	uपूर्णांक32_t i;
	काष्ठा pwl_भग्न_data_ex *rgb = rgb_regamma;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinate_x;
	स्थिर काष्ठा hw_x_poपूर्णांक *prv_coord_x = coord_x;
	काष्ठा fixed31_32 scaledX = dc_fixpt_zero;
	काष्ठा fixed31_32 scaledX1 = dc_fixpt_zero;
	काष्ठा fixed31_32 max_display;
	काष्ठा fixed31_32 min_display;
	काष्ठा fixed31_32 max_content;
	काष्ठा fixed31_32 clip = dc_fixpt_one;
	काष्ठा fixed31_32 output;
	bool use_eetf = false;
	bool is_clipped = false;
	काष्ठा fixed31_32 sdr_white_level;
	काष्ठा fixed31_32 coordX_dअगरf;
	काष्ठा fixed31_32 out_dist_max;
	काष्ठा fixed31_32 bright_norm;

	अगर (fs_params->max_content == 0 ||
			fs_params->max_display == 0)
		वापस false;

	max_display = dc_fixpt_from_पूर्णांक(fs_params->max_display);
	min_display = dc_fixpt_from_fraction(fs_params->min_display, 10000);
	max_content = dc_fixpt_from_पूर्णांक(fs_params->max_content);
	sdr_white_level = dc_fixpt_from_पूर्णांक(fs_params->sdr_white_level);

	अगर (fs_params->min_display > 1000) // cap at 0.1 at the bottom
		min_display = dc_fixpt_from_fraction(1, 10);
	अगर (fs_params->max_display < 100) // cap at 100 at the top
		max_display = dc_fixpt_from_पूर्णांक(100);

	// only max used, we करोn't adjust min luminance
	अगर (fs_params->max_content > fs_params->max_display)
		use_eetf = true;
	अन्यथा
		max_content = max_display;

	अगर (!use_eetf)
		cal_buffer->buffer_index = 0; // see var definition क्रम more info
	rgb += 32; // first 32 poपूर्णांकs have problems with fixed poपूर्णांक, too small
	coord_x += 32;

	क्रम (i = 32; i <= hw_poपूर्णांकs_num; i++) अणु
		अगर (!is_clipped) अणु
			अगर (use_eetf) अणु
				/* max content is equal 1 */
				scaledX1 = dc_fixpt_भाग(coord_x->x,
						dc_fixpt_भाग(max_content, sdr_white_level));
				hermite_spline_eetf(scaledX1, max_display, min_display,
						max_content, &scaledX);
			पूर्ण अन्यथा
				scaledX = dc_fixpt_भाग(coord_x->x,
						dc_fixpt_भाग(max_display, sdr_white_level));

			अगर (dc_fixpt_lt(scaledX, clip)) अणु
				अगर (dc_fixpt_lt(scaledX, dc_fixpt_zero))
					output = dc_fixpt_zero;
				अन्यथा
					output = calculate_gamma22(scaledX, use_eetf, cal_buffer);

				// Ensure output respects reasonable boundaries
				output = dc_fixpt_clamp(output, dc_fixpt_zero, dc_fixpt_one);

				rgb->r = output;
				rgb->g = output;
				rgb->b = output;
			पूर्ण अन्यथा अणु
				/* Here clipping happens क्रम the first समय */
				is_clipped = true;

				/* The next few lines implement the equation
				 * output = prev_out +
				 * (coord_x->x - prev_coord_x->x) *
				 * (1.0 - prev_out) /
				 * (maxDisp/sdr_white_level - prevCoordX)
				 *
				 * This equation पूर्णांकerpolates the first poपूर्णांक
				 * after max_display/80 so that the slope from
				 * hw_x_beक्रमe_max and hw_x_after_max is such
				 * that we hit Y=1.0 at max_display/80.
				 */

				coordX_dअगरf = dc_fixpt_sub(coord_x->x, prv_coord_x->x);
				out_dist_max = dc_fixpt_sub(dc_fixpt_one, output);
				bright_norm = dc_fixpt_भाग(max_display, sdr_white_level);

				output = dc_fixpt_add(
					output, dc_fixpt_mul(
						coordX_dअगरf, dc_fixpt_भाग(
							out_dist_max,
							dc_fixpt_sub(bright_norm, prv_coord_x->x)
						)
					)
				);

				/* Relaxing the maximum boundary to 1.07 (instead of 1.0)
				 * because the last poपूर्णांक in the curve must be such that
				 * the maximum display pixel brightness पूर्णांकerpolates to
				 * exactly 1.0. The worst हाल scenario was calculated
				 * around 1.057, so the limit of 1.07 leaves some safety
				 * margin.
				 */
				output = dc_fixpt_clamp(output, dc_fixpt_zero,
					dc_fixpt_from_fraction(107, 100));

				rgb->r = output;
				rgb->g = output;
				rgb->b = output;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Every other clipping after the first
			 * one is dealt with here
			 */
			rgb->r = clip;
			rgb->g = clip;
			rgb->b = clip;
		पूर्ण

		prv_coord_x = coord_x;
		++coord_x;
		++rgb;
	पूर्ण
	cal_buffer->buffer_index = -1;

	वापस true;
पूर्ण

अटल bool build_degamma(काष्ठा pwl_भग्न_data_ex *curve,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा hw_x_poपूर्णांक *coordinate_x, क्रमागत dc_transfer_func_predefined type)
अणु
	uपूर्णांक32_t i;
	काष्ठा gamma_coefficients coeff;
	uपूर्णांक32_t begin_index, end_index;
	bool ret = false;

	अगर (!build_coefficients(&coeff, type))
		जाओ release;

	i = 0;

	/* X poपूर्णांकs is 2^-25 to 2^7
	 * De-gamma X is 2^-12 to 2^0 ै  we are skipping first -12-(-25) = 13 regions
	 */
	begin_index = 13 * NUM_PTS_IN_REGION;
	end_index = begin_index + 12 * NUM_PTS_IN_REGION;

	जबतक (i != begin_index) अणु
		curve[i].r = dc_fixpt_zero;
		curve[i].g = dc_fixpt_zero;
		curve[i].b = dc_fixpt_zero;
		i++;
	पूर्ण

	जबतक (i != end_index) अणु
		curve[i].r = translate_to_linear_space_ex(
				coordinate_x[i].x, &coeff, 0);
		curve[i].g = curve[i].r;
		curve[i].b = curve[i].r;
		i++;
	पूर्ण
	जबतक (i != hw_poपूर्णांकs_num + 1) अणु
		curve[i].r = dc_fixpt_one;
		curve[i].g = dc_fixpt_one;
		curve[i].b = dc_fixpt_one;
		i++;
	पूर्ण
	ret = true;
release:
	वापस ret;
पूर्ण





अटल व्योम build_hlg_degamma(काष्ठा pwl_भग्न_data_ex *degamma,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा hw_x_poपूर्णांक *coordinate_x,
		uपूर्णांक32_t sdr_white_level, uपूर्णांक32_t max_luminance_nits)
अणु
	uपूर्णांक32_t i;

	काष्ठा pwl_भग्न_data_ex *rgb = degamma;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinate_x;

	i = 0;
	// check when i == 434
	जबतक (i != hw_poपूर्णांकs_num + 1) अणु
		compute_hlg_eotf(coord_x->x, &rgb->r, sdr_white_level, max_luminance_nits);
		rgb->g = rgb->r;
		rgb->b = rgb->r;
		++coord_x;
		++rgb;
		++i;
	पूर्ण
पूर्ण


अटल व्योम build_hlg_regamma(काष्ठा pwl_भग्न_data_ex *regamma,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा hw_x_poपूर्णांक *coordinate_x,
		uपूर्णांक32_t sdr_white_level, uपूर्णांक32_t max_luminance_nits)
अणु
	uपूर्णांक32_t i;

	काष्ठा pwl_भग्न_data_ex *rgb = regamma;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinate_x;

	i = 0;

	// when i == 471
	जबतक (i != hw_poपूर्णांकs_num + 1) अणु
		compute_hlg_oetf(coord_x->x, &rgb->r, sdr_white_level, max_luminance_nits);
		rgb->g = rgb->r;
		rgb->b = rgb->r;
		++coord_x;
		++rgb;
		++i;
	पूर्ण
पूर्ण

अटल व्योम scale_gamma(काष्ठा pwl_भग्न_data *pwl_rgb,
		स्थिर काष्ठा dc_gamma *ramp,
		काष्ठा भागiders भागiders)
अणु
	स्थिर काष्ठा fixed31_32 max_driver = dc_fixpt_from_पूर्णांक(0xFFFF);
	स्थिर काष्ठा fixed31_32 max_os = dc_fixpt_from_पूर्णांक(0xFF00);
	काष्ठा fixed31_32 scaler = max_os;
	uपूर्णांक32_t i;
	काष्ठा pwl_भग्न_data *rgb = pwl_rgb;
	काष्ठा pwl_भग्न_data *rgb_last = rgb + ramp->num_entries - 1;

	i = 0;

	करो अणु
		अगर (dc_fixpt_lt(max_os, ramp->entries.red[i]) ||
			dc_fixpt_lt(max_os, ramp->entries.green[i]) ||
			dc_fixpt_lt(max_os, ramp->entries.blue[i])) अणु
			scaler = max_driver;
			अवरोध;
		पूर्ण
		++i;
	पूर्ण जबतक (i != ramp->num_entries);

	i = 0;

	करो अणु
		rgb->r = dc_fixpt_भाग(
			ramp->entries.red[i], scaler);
		rgb->g = dc_fixpt_भाग(
			ramp->entries.green[i], scaler);
		rgb->b = dc_fixpt_भाग(
			ramp->entries.blue[i], scaler);

		++rgb;
		++i;
	पूर्ण जबतक (i != ramp->num_entries);

	rgb->r = dc_fixpt_mul(rgb_last->r,
			भागiders.भागider1);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			भागiders.भागider1);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			भागiders.भागider1);

	++rgb;

	rgb->r = dc_fixpt_mul(rgb_last->r,
			भागiders.भागider2);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			भागiders.भागider2);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			भागiders.भागider2);

	++rgb;

	rgb->r = dc_fixpt_mul(rgb_last->r,
			भागiders.भागider3);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			भागiders.भागider3);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			भागiders.भागider3);
पूर्ण

अटल व्योम scale_gamma_dx(काष्ठा pwl_भग्न_data *pwl_rgb,
		स्थिर काष्ठा dc_gamma *ramp,
		काष्ठा भागiders भागiders)
अणु
	uपूर्णांक32_t i;
	काष्ठा fixed31_32 min = dc_fixpt_zero;
	काष्ठा fixed31_32 max = dc_fixpt_one;

	काष्ठा fixed31_32 delta = dc_fixpt_zero;
	काष्ठा fixed31_32 offset = dc_fixpt_zero;

	क्रम (i = 0 ; i < ramp->num_entries; i++) अणु
		अगर (dc_fixpt_lt(ramp->entries.red[i], min))
			min = ramp->entries.red[i];

		अगर (dc_fixpt_lt(ramp->entries.green[i], min))
			min = ramp->entries.green[i];

		अगर (dc_fixpt_lt(ramp->entries.blue[i], min))
			min = ramp->entries.blue[i];

		अगर (dc_fixpt_lt(max, ramp->entries.red[i]))
			max = ramp->entries.red[i];

		अगर (dc_fixpt_lt(max, ramp->entries.green[i]))
			max = ramp->entries.green[i];

		अगर (dc_fixpt_lt(max, ramp->entries.blue[i]))
			max = ramp->entries.blue[i];
	पूर्ण

	अगर (dc_fixpt_lt(min, dc_fixpt_zero))
		delta = dc_fixpt_neg(min);

	offset = dc_fixpt_add(min, max);

	क्रम (i = 0 ; i < ramp->num_entries; i++) अणु
		pwl_rgb[i].r = dc_fixpt_भाग(
			dc_fixpt_add(
				ramp->entries.red[i], delta), offset);
		pwl_rgb[i].g = dc_fixpt_भाग(
			dc_fixpt_add(
				ramp->entries.green[i], delta), offset);
		pwl_rgb[i].b = dc_fixpt_भाग(
			dc_fixpt_add(
				ramp->entries.blue[i], delta), offset);

	पूर्ण

	pwl_rgb[i].r =  dc_fixpt_sub(dc_fixpt_mul_पूर्णांक(
				pwl_rgb[i-1].r, 2), pwl_rgb[i-2].r);
	pwl_rgb[i].g =  dc_fixpt_sub(dc_fixpt_mul_पूर्णांक(
				pwl_rgb[i-1].g, 2), pwl_rgb[i-2].g);
	pwl_rgb[i].b =  dc_fixpt_sub(dc_fixpt_mul_पूर्णांक(
				pwl_rgb[i-1].b, 2), pwl_rgb[i-2].b);
	++i;
	pwl_rgb[i].r =  dc_fixpt_sub(dc_fixpt_mul_पूर्णांक(
				pwl_rgb[i-1].r, 2), pwl_rgb[i-2].r);
	pwl_rgb[i].g =  dc_fixpt_sub(dc_fixpt_mul_पूर्णांक(
				pwl_rgb[i-1].g, 2), pwl_rgb[i-2].g);
	pwl_rgb[i].b =  dc_fixpt_sub(dc_fixpt_mul_पूर्णांक(
				pwl_rgb[i-1].b, 2), pwl_rgb[i-2].b);
पूर्ण

/* toकरो: all these scale_gamma functions are inherently the same but
 *  take dअगरferent काष्ठाures as params or dअगरferent क्रमmat क्रम ramp
 *  values. We could probably implement it in a more generic fashion
 */
अटल व्योम scale_user_regamma_ramp(काष्ठा pwl_भग्न_data *pwl_rgb,
		स्थिर काष्ठा regamma_ramp *ramp,
		काष्ठा भागiders भागiders)
अणु
	अचिन्हित लघु max_driver = 0xFFFF;
	अचिन्हित लघु max_os = 0xFF00;
	अचिन्हित लघु scaler = max_os;
	uपूर्णांक32_t i;
	काष्ठा pwl_भग्न_data *rgb = pwl_rgb;
	काष्ठा pwl_भग्न_data *rgb_last = rgb + GAMMA_RGB_256_ENTRIES - 1;

	i = 0;
	करो अणु
		अगर (ramp->gamma[i] > max_os ||
				ramp->gamma[i + 256] > max_os ||
				ramp->gamma[i + 512] > max_os) अणु
			scaler = max_driver;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण जबतक (i != GAMMA_RGB_256_ENTRIES);

	i = 0;
	करो अणु
		rgb->r = dc_fixpt_from_fraction(
				ramp->gamma[i], scaler);
		rgb->g = dc_fixpt_from_fraction(
				ramp->gamma[i + 256], scaler);
		rgb->b = dc_fixpt_from_fraction(
				ramp->gamma[i + 512], scaler);

		++rgb;
		++i;
	पूर्ण जबतक (i != GAMMA_RGB_256_ENTRIES);

	rgb->r = dc_fixpt_mul(rgb_last->r,
			भागiders.भागider1);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			भागiders.भागider1);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			भागiders.भागider1);

	++rgb;

	rgb->r = dc_fixpt_mul(rgb_last->r,
			भागiders.भागider2);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			भागiders.भागider2);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			भागiders.भागider2);

	++rgb;

	rgb->r = dc_fixpt_mul(rgb_last->r,
			भागiders.भागider3);
	rgb->g = dc_fixpt_mul(rgb_last->g,
			भागiders.भागider3);
	rgb->b = dc_fixpt_mul(rgb_last->b,
			भागiders.भागider3);
पूर्ण

/*
 * RS3+ color transक्रमm DDI - 1D LUT adjusपंचांगent is composed with regamma here
 * Input is evenly distributed in the output color space as specअगरied in
 * SetTimings
 *
 * Interpolation details:
 * 1D LUT has 4096 values which give curve correction in 0-1 भग्न range
 * क्रम evenly spaced poपूर्णांकs in 0-1 range. lut1D[index] gives correction
 * क्रम index/4095.
 * First we find index क्रम which:
 *	index/4095 < regamma_y < (index+1)/4095 =>
 *	index < 4095*regamma_y < index + 1
 * norm_y = 4095*regamma_y, and index is just truncating to nearest पूर्णांकeger
 * lut1 = lut1D[index], lut2 = lut1D[index+1]
 *
 * adjustedY is then linearly पूर्णांकerpolating regamma Y between lut1 and lut2
 *
 * Custom degamma on Linux uses the same पूर्णांकerpolation math, so is handled here
 */
अटल व्योम apply_lut_1d(
		स्थिर काष्ठा dc_gamma *ramp,
		uपूर्णांक32_t num_hw_poपूर्णांकs,
		काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts)
अणु
	पूर्णांक i = 0;
	पूर्णांक color = 0;
	काष्ठा fixed31_32 *regamma_y;
	काष्ठा fixed31_32 norm_y;
	काष्ठा fixed31_32 lut1;
	काष्ठा fixed31_32 lut2;
	स्थिर पूर्णांक max_lut_index = 4095;
	स्थिर काष्ठा fixed31_32 penult_lut_index_f =
			dc_fixpt_from_पूर्णांक(max_lut_index-1);
	स्थिर काष्ठा fixed31_32 max_lut_index_f =
			dc_fixpt_from_पूर्णांक(max_lut_index);
	पूर्णांक32_t index = 0, index_next = 0;
	काष्ठा fixed31_32 index_f;
	काष्ठा fixed31_32 delta_lut;
	काष्ठा fixed31_32 delta_index;

	अगर (ramp->type != GAMMA_CS_TFM_1D && ramp->type != GAMMA_CUSTOM)
		वापस; // this is not expected

	क्रम (i = 0; i < num_hw_poपूर्णांकs; i++) अणु
		क्रम (color = 0; color < 3; color++) अणु
			अगर (color == 0)
				regamma_y = &tf_pts->red[i];
			अन्यथा अगर (color == 1)
				regamma_y = &tf_pts->green[i];
			अन्यथा
				regamma_y = &tf_pts->blue[i];

			norm_y = dc_fixpt_mul(max_lut_index_f,
						   *regamma_y);
			index = dc_fixpt_न्यूनमान(norm_y);
			index_f = dc_fixpt_from_पूर्णांक(index);

			अगर (index < 0)
				जारी;

			अगर (index <= max_lut_index)
				index_next = (index == max_lut_index) ? index : index+1;
			अन्यथा अणु
				/* Here we are dealing with the last poपूर्णांक in the curve,
				 * which in some हालs might exceed the range given by
				 * max_lut_index. So we पूर्णांकerpolate the value using
				 * max_lut_index and max_lut_index - 1.
				 */
				index = max_lut_index - 1;
				index_next = max_lut_index;
				index_f = penult_lut_index_f;
			पूर्ण

			अगर (color == 0) अणु
				lut1 = ramp->entries.red[index];
				lut2 = ramp->entries.red[index_next];
			पूर्ण अन्यथा अगर (color == 1) अणु
				lut1 = ramp->entries.green[index];
				lut2 = ramp->entries.green[index_next];
			पूर्ण अन्यथा अणु
				lut1 = ramp->entries.blue[index];
				lut2 = ramp->entries.blue[index_next];
			पूर्ण

			// we have everything now, so पूर्णांकerpolate
			delta_lut = dc_fixpt_sub(lut2, lut1);
			delta_index = dc_fixpt_sub(norm_y, index_f);

			*regamma_y = dc_fixpt_add(lut1,
				dc_fixpt_mul(delta_index, delta_lut));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम build_evenly_distributed_poपूर्णांकs(
	काष्ठा gamma_pixel *poपूर्णांकs,
	uपूर्णांक32_t numberof_poपूर्णांकs,
	काष्ठा भागiders भागiders)
अणु
	काष्ठा gamma_pixel *p = poपूर्णांकs;
	काष्ठा gamma_pixel *p_last;

	uपूर्णांक32_t i = 0;

	// This function should not माला_लो called with 0 as a parameter
	ASSERT(numberof_poपूर्णांकs > 0);
	p_last = p + numberof_poपूर्णांकs - 1;

	करो अणु
		काष्ठा fixed31_32 value = dc_fixpt_from_fraction(i,
			numberof_poपूर्णांकs - 1);

		p->r = value;
		p->g = value;
		p->b = value;

		++p;
		++i;
	पूर्ण जबतक (i < numberof_poपूर्णांकs);

	p->r = dc_fixpt_भाग(p_last->r, भागiders.भागider1);
	p->g = dc_fixpt_भाग(p_last->g, भागiders.भागider1);
	p->b = dc_fixpt_भाग(p_last->b, भागiders.भागider1);

	++p;

	p->r = dc_fixpt_भाग(p_last->r, भागiders.भागider2);
	p->g = dc_fixpt_भाग(p_last->g, भागiders.भागider2);
	p->b = dc_fixpt_भाग(p_last->b, भागiders.भागider2);

	++p;

	p->r = dc_fixpt_भाग(p_last->r, भागiders.भागider3);
	p->g = dc_fixpt_भाग(p_last->g, भागiders.भागider3);
	p->b = dc_fixpt_भाग(p_last->b, भागiders.भागider3);
पूर्ण

अटल अंतरभूत व्योम copy_rgb_regamma_to_coordinates_x(
		काष्ठा hw_x_poपूर्णांक *coordinates_x,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		स्थिर काष्ठा pwl_भग्न_data_ex *rgb_ex)
अणु
	काष्ठा hw_x_poपूर्णांक *coords = coordinates_x;
	uपूर्णांक32_t i = 0;
	स्थिर काष्ठा pwl_भग्न_data_ex *rgb_regamma = rgb_ex;

	जबतक (i <= hw_poपूर्णांकs_num + 1) अणु
		coords->regamma_y_red = rgb_regamma->r;
		coords->regamma_y_green = rgb_regamma->g;
		coords->regamma_y_blue = rgb_regamma->b;

		++coords;
		++rgb_regamma;
		++i;
	पूर्ण
पूर्ण

अटल bool calculate_पूर्णांकerpolated_hardware_curve(
	स्थिर काष्ठा dc_gamma *ramp,
	काष्ठा pixel_gamma_poपूर्णांक *coeff128,
	काष्ठा pwl_भग्न_data *rgb_user,
	स्थिर काष्ठा hw_x_poपूर्णांक *coordinates_x,
	स्थिर काष्ठा gamma_pixel *axis_x,
	uपूर्णांक32_t number_of_poपूर्णांकs,
	काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts)
अणु

	स्थिर काष्ठा pixel_gamma_poपूर्णांक *coeff = coeff128;
	uपूर्णांक32_t max_entries = 3 - 1;

	uपूर्णांक32_t i = 0;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!build_custom_gamma_mapping_coefficients_worker(
				ramp, coeff128, coordinates_x, axis_x, i,
				number_of_poपूर्णांकs))
			वापस false;
	पूर्ण

	i = 0;
	max_entries += ramp->num_entries;

	/* TODO: भग्न poपूर्णांक हाल */

	जबतक (i <= number_of_poपूर्णांकs) अणु
		tf_pts->red[i] = calculate_mapped_value(
			rgb_user, coeff, CHANNEL_NAME_RED, max_entries);
		tf_pts->green[i] = calculate_mapped_value(
			rgb_user, coeff, CHANNEL_NAME_GREEN, max_entries);
		tf_pts->blue[i] = calculate_mapped_value(
			rgb_user, coeff, CHANNEL_NAME_BLUE, max_entries);

		++coeff;
		++i;
	पूर्ण

	वापस true;
पूर्ण

/* The "old" पूर्णांकerpolation uses a complicated scheme to build an array of
 * coefficients जबतक also using an array of 0-255 normalized to 0-1
 * Then there's another loop using both of the above + new scaled user ramp
 * and we concatenate them. It also searches क्रम poपूर्णांकs of पूर्णांकerpolation and
 * uses क्रमागतs क्रम positions.
 *
 * This function uses a dअगरferent approach:
 * user ramp is always applied on X with 0/255, 1/255, 2/255, ..., 255/255
 * To find index क्रम hwX , we notice the following:
 * i/255 <= hwX < (i+1)/255  <=> i <= 255*hwX < i+1
 * See apply_lut_1d which is the same principle, but on 4K entry 1D LUT
 *
 * Once the index is known, combined Y is simply:
 * user_ramp(index) + (hwX-index/255)*(user_ramp(index+1) - user_ramp(index)
 *
 * We should चयन to this method in all हालs, it's simpler and faster
 * ToDo one day - क्रम now this only applies to ADL regamma to aव्योम regression
 * क्रम regular use हालs (sRGB and PQ)
 */
अटल व्योम पूर्णांकerpolate_user_regamma(uपूर्णांक32_t hw_poपूर्णांकs_num,
		काष्ठा pwl_भग्न_data *rgb_user,
		bool apply_degamma,
		काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t color = 0;
	पूर्णांक32_t index;
	पूर्णांक32_t index_next;
	काष्ठा fixed31_32 *tf_poपूर्णांक;
	काष्ठा fixed31_32 hw_x;
	काष्ठा fixed31_32 norm_factor =
			dc_fixpt_from_पूर्णांक(255);
	काष्ठा fixed31_32 norm_x;
	काष्ठा fixed31_32 index_f;
	काष्ठा fixed31_32 lut1;
	काष्ठा fixed31_32 lut2;
	काष्ठा fixed31_32 delta_lut;
	काष्ठा fixed31_32 delta_index;

	i = 0;
	/* fixed_pt library has problems handling too small values */
	जबतक (i != 32) अणु
		tf_pts->red[i] = dc_fixpt_zero;
		tf_pts->green[i] = dc_fixpt_zero;
		tf_pts->blue[i] = dc_fixpt_zero;
		++i;
	पूर्ण
	जबतक (i <= hw_poपूर्णांकs_num + 1) अणु
		क्रम (color = 0; color < 3; color++) अणु
			अगर (color == 0)
				tf_poपूर्णांक = &tf_pts->red[i];
			अन्यथा अगर (color == 1)
				tf_poपूर्णांक = &tf_pts->green[i];
			अन्यथा
				tf_poपूर्णांक = &tf_pts->blue[i];

			अगर (apply_degamma) अणु
				अगर (color == 0)
					hw_x = coordinates_x[i].regamma_y_red;
				अन्यथा अगर (color == 1)
					hw_x = coordinates_x[i].regamma_y_green;
				अन्यथा
					hw_x = coordinates_x[i].regamma_y_blue;
			पूर्ण अन्यथा
				hw_x = coordinates_x[i].x;

			norm_x = dc_fixpt_mul(norm_factor, hw_x);
			index = dc_fixpt_न्यूनमान(norm_x);
			अगर (index < 0 || index > 255)
				जारी;

			index_f = dc_fixpt_from_पूर्णांक(index);
			index_next = (index == 255) ? index : index + 1;

			अगर (color == 0) अणु
				lut1 = rgb_user[index].r;
				lut2 = rgb_user[index_next].r;
			पूर्ण अन्यथा अगर (color == 1) अणु
				lut1 = rgb_user[index].g;
				lut2 = rgb_user[index_next].g;
			पूर्ण अन्यथा अणु
				lut1 = rgb_user[index].b;
				lut2 = rgb_user[index_next].b;
			पूर्ण

			// we have everything now, so पूर्णांकerpolate
			delta_lut = dc_fixpt_sub(lut2, lut1);
			delta_index = dc_fixpt_sub(norm_x, index_f);

			*tf_poपूर्णांक = dc_fixpt_add(lut1,
				dc_fixpt_mul(delta_index, delta_lut));
		पूर्ण
		++i;
	पूर्ण
पूर्ण

अटल व्योम build_new_custom_resulted_curve(
	uपूर्णांक32_t hw_poपूर्णांकs_num,
	काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts)
अणु
	uपूर्णांक32_t i = 0;

	जबतक (i != hw_poपूर्णांकs_num + 1) अणु
		tf_pts->red[i] = dc_fixpt_clamp(
			tf_pts->red[i], dc_fixpt_zero,
			dc_fixpt_one);
		tf_pts->green[i] = dc_fixpt_clamp(
			tf_pts->green[i], dc_fixpt_zero,
			dc_fixpt_one);
		tf_pts->blue[i] = dc_fixpt_clamp(
			tf_pts->blue[i], dc_fixpt_zero,
			dc_fixpt_one);

		++i;
	पूर्ण
पूर्ण

अटल व्योम apply_degamma_क्रम_user_regamma(काष्ठा pwl_भग्न_data_ex *rgb_regamma,
		uपूर्णांक32_t hw_poपूर्णांकs_num, काष्ठा calculate_buffer *cal_buffer)
अणु
	uपूर्णांक32_t i;

	काष्ठा gamma_coefficients coeff;
	काष्ठा pwl_भग्न_data_ex *rgb = rgb_regamma;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinates_x;

	build_coefficients(&coeff, TRANSFER_FUNCTION_SRGB);

	i = 0;
	जबतक (i != hw_poपूर्णांकs_num + 1) अणु
		rgb->r = translate_from_linear_space_ex(
				coord_x->x, &coeff, 0, cal_buffer);
		rgb->g = rgb->r;
		rgb->b = rgb->r;
		++coord_x;
		++rgb;
		++i;
	पूर्ण
पूर्ण

अटल bool map_regamma_hw_to_x_user(
	स्थिर काष्ठा dc_gamma *ramp,
	काष्ठा pixel_gamma_poपूर्णांक *coeff128,
	काष्ठा pwl_भग्न_data *rgb_user,
	काष्ठा hw_x_poपूर्णांक *coords_x,
	स्थिर काष्ठा gamma_pixel *axis_x,
	स्थिर काष्ठा pwl_भग्न_data_ex *rgb_regamma,
	uपूर्णांक32_t hw_poपूर्णांकs_num,
	काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts,
	bool mapUserRamp,
	bool करोClamping)
अणु
	/* setup to spare calculated ideal regamma values */

	पूर्णांक i = 0;
	काष्ठा hw_x_poपूर्णांक *coords = coords_x;
	स्थिर काष्ठा pwl_भग्न_data_ex *regamma = rgb_regamma;

	अगर (ramp && mapUserRamp) अणु
		copy_rgb_regamma_to_coordinates_x(coords,
				hw_poपूर्णांकs_num,
				rgb_regamma);

		calculate_पूर्णांकerpolated_hardware_curve(
			ramp, coeff128, rgb_user, coords, axis_x,
			hw_poपूर्णांकs_num, tf_pts);
	पूर्ण अन्यथा अणु
		/* just copy current rgb_regamma पूर्णांकo  tf_pts */
		जबतक (i <= hw_poपूर्णांकs_num) अणु
			tf_pts->red[i] = regamma->r;
			tf_pts->green[i] = regamma->g;
			tf_pts->blue[i] = regamma->b;

			++regamma;
			++i;
		पूर्ण
	पूर्ण

	अगर (करोClamping) अणु
		/* this should be named dअगरferently, all it करोes is clamp to 0-1 */
		build_new_custom_resulted_curve(hw_poपूर्णांकs_num, tf_pts);
	पूर्ण

	वापस true;
पूर्ण

#घोषणा _EXTRA_POINTS 3

bool calculate_user_regamma_coeff(काष्ठा dc_transfer_func *output_tf,
		स्थिर काष्ठा regamma_lut *regamma,
		काष्ठा calculate_buffer *cal_buffer,
		स्थिर काष्ठा dc_gamma *ramp)
अणु
	काष्ठा gamma_coefficients coeff;
	स्थिर काष्ठा hw_x_poपूर्णांक *coord_x = coordinates_x;
	uपूर्णांक32_t i = 0;

	करो अणु
		coeff.a0[i] = dc_fixpt_from_fraction(
				regamma->coeff.A0[i], 10000000);
		coeff.a1[i] = dc_fixpt_from_fraction(
				regamma->coeff.A1[i], 1000);
		coeff.a2[i] = dc_fixpt_from_fraction(
				regamma->coeff.A2[i], 1000);
		coeff.a3[i] = dc_fixpt_from_fraction(
				regamma->coeff.A3[i], 1000);
		coeff.user_gamma[i] = dc_fixpt_from_fraction(
				regamma->coeff.gamma[i], 1000);

		++i;
	पूर्ण जबतक (i != 3);

	i = 0;
	/* fixed_pt library has problems handling too small values */
	जबतक (i != 32) अणु
		output_tf->tf_pts.red[i] = dc_fixpt_zero;
		output_tf->tf_pts.green[i] = dc_fixpt_zero;
		output_tf->tf_pts.blue[i] = dc_fixpt_zero;
		++coord_x;
		++i;
	पूर्ण
	जबतक (i != MAX_HW_POINTS + 1) अणु
		output_tf->tf_pts.red[i] = translate_from_linear_space_ex(
				coord_x->x, &coeff, 0, cal_buffer);
		output_tf->tf_pts.green[i] = translate_from_linear_space_ex(
				coord_x->x, &coeff, 1, cal_buffer);
		output_tf->tf_pts.blue[i] = translate_from_linear_space_ex(
				coord_x->x, &coeff, 2, cal_buffer);
		++coord_x;
		++i;
	पूर्ण

	अगर (ramp && ramp->type == GAMMA_CS_TFM_1D)
		apply_lut_1d(ramp, MAX_HW_POINTS, &output_tf->tf_pts);

	// this function just clamps output to 0-1
	build_new_custom_resulted_curve(MAX_HW_POINTS, &output_tf->tf_pts);
	output_tf->type = TF_TYPE_DISTRIBUTED_POINTS;

	वापस true;
पूर्ण

bool calculate_user_regamma_ramp(काष्ठा dc_transfer_func *output_tf,
		स्थिर काष्ठा regamma_lut *regamma,
		काष्ठा calculate_buffer *cal_buffer,
		स्थिर काष्ठा dc_gamma *ramp)
अणु
	काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts = &output_tf->tf_pts;
	काष्ठा भागiders भागiders;

	काष्ठा pwl_भग्न_data *rgb_user = शून्य;
	काष्ठा pwl_भग्न_data_ex *rgb_regamma = शून्य;
	bool ret = false;

	अगर (regamma == शून्य)
		वापस false;

	output_tf->type = TF_TYPE_DISTRIBUTED_POINTS;

	rgb_user = kसुस्मृति(GAMMA_RGB_256_ENTRIES + _EXTRA_POINTS,
			   माप(*rgb_user),
			   GFP_KERNEL);
	अगर (!rgb_user)
		जाओ rgb_user_alloc_fail;

	rgb_regamma = kसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS,
			      माप(*rgb_regamma),
			      GFP_KERNEL);
	अगर (!rgb_regamma)
		जाओ rgb_regamma_alloc_fail;

	भागiders.भागider1 = dc_fixpt_from_fraction(3, 2);
	भागiders.भागider2 = dc_fixpt_from_पूर्णांक(2);
	भागiders.भागider3 = dc_fixpt_from_fraction(5, 2);

	scale_user_regamma_ramp(rgb_user, &regamma->ramp, भागiders);

	अगर (regamma->flags.bits.applyDegamma == 1) अणु
		apply_degamma_क्रम_user_regamma(rgb_regamma, MAX_HW_POINTS, cal_buffer);
		copy_rgb_regamma_to_coordinates_x(coordinates_x,
				MAX_HW_POINTS, rgb_regamma);
	पूर्ण

	पूर्णांकerpolate_user_regamma(MAX_HW_POINTS, rgb_user,
			regamma->flags.bits.applyDegamma, tf_pts);

	// no custom HDR curves!
	tf_pts->end_exponent = 0;
	tf_pts->x_poपूर्णांक_at_y1_red = 1;
	tf_pts->x_poपूर्णांक_at_y1_green = 1;
	tf_pts->x_poपूर्णांक_at_y1_blue = 1;

	अगर (ramp && ramp->type == GAMMA_CS_TFM_1D)
		apply_lut_1d(ramp, MAX_HW_POINTS, &output_tf->tf_pts);

	// this function just clamps output to 0-1
	build_new_custom_resulted_curve(MAX_HW_POINTS, tf_pts);

	ret = true;

	kमुक्त(rgb_regamma);
rgb_regamma_alloc_fail:
	kमुक्त(rgb_user);
rgb_user_alloc_fail:
	वापस ret;
पूर्ण

bool mod_color_calculate_degamma_params(काष्ठा dc_color_caps *dc_caps,
		काष्ठा dc_transfer_func *input_tf,
		स्थिर काष्ठा dc_gamma *ramp, bool mapUserRamp)
अणु
	काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts = &input_tf->tf_pts;
	काष्ठा भागiders भागiders;
	काष्ठा pwl_भग्न_data *rgb_user = शून्य;
	काष्ठा pwl_भग्न_data_ex *curve = शून्य;
	काष्ठा gamma_pixel *axis_x = शून्य;
	काष्ठा pixel_gamma_poपूर्णांक *coeff = शून्य;
	क्रमागत dc_transfer_func_predefined tf = TRANSFER_FUNCTION_SRGB;
	uपूर्णांक32_t i;
	bool ret = false;

	अगर (input_tf->type == TF_TYPE_BYPASS)
		वापस false;

	/* we can use hardcoded curve क्रम plain SRGB TF
	 * If linear, it's bypass अगर on user ramp
	 */
	अगर (input_tf->type == TF_TYPE_PREDEFINED) अणु
		अगर ((input_tf->tf == TRANSFER_FUNCTION_SRGB ||
				input_tf->tf == TRANSFER_FUNCTION_LINEAR) &&
				!mapUserRamp)
			वापस true;

		अगर (dc_caps != शून्य &&
			dc_caps->dpp.dcn_arch == 1) अणु

			अगर (input_tf->tf == TRANSFER_FUNCTION_PQ &&
					dc_caps->dpp.dgam_rom_caps.pq == 1)
				वापस true;

			अगर (input_tf->tf == TRANSFER_FUNCTION_GAMMA22 &&
					dc_caps->dpp.dgam_rom_caps.gamma2_2 == 1)
				वापस true;

			// HLG OOTF not accounted क्रम
			अगर (input_tf->tf == TRANSFER_FUNCTION_HLG &&
					dc_caps->dpp.dgam_rom_caps.hlg == 1)
				वापस true;
		पूर्ण
	पूर्ण

	input_tf->type = TF_TYPE_DISTRIBUTED_POINTS;

	अगर (mapUserRamp && ramp && ramp->type == GAMMA_RGB_256) अणु
		rgb_user = kvसुस्मृति(ramp->num_entries + _EXTRA_POINTS,
				माप(*rgb_user),
				GFP_KERNEL);
		अगर (!rgb_user)
			जाओ rgb_user_alloc_fail;

		axis_x = kvसुस्मृति(ramp->num_entries + _EXTRA_POINTS, माप(*axis_x),
				GFP_KERNEL);
		अगर (!axis_x)
			जाओ axis_x_alloc_fail;

		भागiders.भागider1 = dc_fixpt_from_fraction(3, 2);
		भागiders.भागider2 = dc_fixpt_from_पूर्णांक(2);
		भागiders.भागider3 = dc_fixpt_from_fraction(5, 2);

		build_evenly_distributed_poपूर्णांकs(
				axis_x,
				ramp->num_entries,
				भागiders);

		scale_gamma(rgb_user, ramp, भागiders);
	पूर्ण

	curve = kvसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS, माप(*curve),
			GFP_KERNEL);
	अगर (!curve)
		जाओ curve_alloc_fail;

	coeff = kvसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS, माप(*coeff),
			GFP_KERNEL);
	अगर (!coeff)
		जाओ coeff_alloc_fail;

	tf = input_tf->tf;

	अगर (tf == TRANSFER_FUNCTION_PQ)
		build_de_pq(curve,
				MAX_HW_POINTS,
				coordinates_x);
	अन्यथा अगर (tf == TRANSFER_FUNCTION_SRGB ||
		tf == TRANSFER_FUNCTION_BT709 ||
		tf == TRANSFER_FUNCTION_GAMMA22 ||
		tf == TRANSFER_FUNCTION_GAMMA24 ||
		tf == TRANSFER_FUNCTION_GAMMA26)
		build_degamma(curve,
				MAX_HW_POINTS,
				coordinates_x,
				tf);
	अन्यथा अगर (tf == TRANSFER_FUNCTION_HLG)
		build_hlg_degamma(curve,
				MAX_HW_POINTS,
				coordinates_x,
				80, 1000);
	अन्यथा अगर (tf == TRANSFER_FUNCTION_LINEAR) अणु
		// just copy coordinates_x पूर्णांकo curve
		i = 0;
		जबतक (i != MAX_HW_POINTS + 1) अणु
			curve[i].r = coordinates_x[i].x;
			curve[i].g = curve[i].r;
			curve[i].b = curve[i].r;
			i++;
		पूर्ण
	पूर्ण अन्यथा
		जाओ invalid_tf_fail;

	tf_pts->end_exponent = 0;
	tf_pts->x_poपूर्णांक_at_y1_red = 1;
	tf_pts->x_poपूर्णांक_at_y1_green = 1;
	tf_pts->x_poपूर्णांक_at_y1_blue = 1;

	अगर (input_tf->tf == TRANSFER_FUNCTION_PQ) अणु
		/* just copy current rgb_regamma पूर्णांकo  tf_pts */
		काष्ठा pwl_भग्न_data_ex *curvePt = curve;
		पूर्णांक i = 0;

		जबतक (i <= MAX_HW_POINTS) अणु
			tf_pts->red[i]   = curvePt->r;
			tf_pts->green[i] = curvePt->g;
			tf_pts->blue[i]  = curvePt->b;
			++curvePt;
			++i;
		पूर्ण
	पूर्ण अन्यथा अणु
		// clamps to 0-1
		map_regamma_hw_to_x_user(ramp, coeff, rgb_user,
				coordinates_x, axis_x, curve,
				MAX_HW_POINTS, tf_pts,
				mapUserRamp && ramp && ramp->type == GAMMA_RGB_256,
				true);
	पूर्ण



	अगर (ramp && ramp->type == GAMMA_CUSTOM)
		apply_lut_1d(ramp, MAX_HW_POINTS, tf_pts);

	ret = true;

invalid_tf_fail:
	kvमुक्त(coeff);
coeff_alloc_fail:
	kvमुक्त(curve);
curve_alloc_fail:
	kvमुक्त(axis_x);
axis_x_alloc_fail:
	kvमुक्त(rgb_user);
rgb_user_alloc_fail:

	वापस ret;
पूर्ण

अटल bool calculate_curve(क्रमागत dc_transfer_func_predefined trans,
				काष्ठा dc_transfer_func_distributed_poपूर्णांकs *poपूर्णांकs,
				काष्ठा pwl_भग्न_data_ex *rgb_regamma,
				स्थिर काष्ठा hdr_पंचांग_params *fs_params,
				uपूर्णांक32_t sdr_ref_white_level,
				काष्ठा calculate_buffer *cal_buffer)
अणु
	uपूर्णांक32_t i;
	bool ret = false;

	अगर (trans == TRANSFER_FUNCTION_UNITY ||
		trans == TRANSFER_FUNCTION_LINEAR) अणु
		poपूर्णांकs->end_exponent = 0;
		poपूर्णांकs->x_poपूर्णांक_at_y1_red = 1;
		poपूर्णांकs->x_poपूर्णांक_at_y1_green = 1;
		poपूर्णांकs->x_poपूर्णांक_at_y1_blue = 1;

		क्रम (i = 0; i <= MAX_HW_POINTS ; i++) अणु
			rgb_regamma[i].r = coordinates_x[i].x;
			rgb_regamma[i].g = coordinates_x[i].x;
			rgb_regamma[i].b = coordinates_x[i].x;
		पूर्ण

		ret = true;
	पूर्ण अन्यथा अगर (trans == TRANSFER_FUNCTION_PQ) अणु
		poपूर्णांकs->end_exponent = 7;
		poपूर्णांकs->x_poपूर्णांक_at_y1_red = 125;
		poपूर्णांकs->x_poपूर्णांक_at_y1_green = 125;
		poपूर्णांकs->x_poपूर्णांक_at_y1_blue = 125;

		build_pq(rgb_regamma,
				MAX_HW_POINTS,
				coordinates_x,
				sdr_ref_white_level);

		ret = true;
	पूर्ण अन्यथा अगर (trans == TRANSFER_FUNCTION_GAMMA22 &&
			fs_params != शून्य && fs_params->skip_पंचांग == 0) अणु
		build_मुक्तsync_hdr(rgb_regamma,
				MAX_HW_POINTS,
				coordinates_x,
				fs_params,
				cal_buffer);

		ret = true;
	पूर्ण अन्यथा अगर (trans == TRANSFER_FUNCTION_HLG) अणु
		poपूर्णांकs->end_exponent = 4;
		poपूर्णांकs->x_poपूर्णांक_at_y1_red = 12;
		poपूर्णांकs->x_poपूर्णांक_at_y1_green = 12;
		poपूर्णांकs->x_poपूर्णांक_at_y1_blue = 12;

		build_hlg_regamma(rgb_regamma,
				MAX_HW_POINTS,
				coordinates_x,
				80, 1000);

		ret = true;
	पूर्ण अन्यथा अणु
		// trans == TRANSFER_FUNCTION_SRGB
		// trans == TRANSFER_FUNCTION_BT709
		// trans == TRANSFER_FUNCTION_GAMMA22
		// trans == TRANSFER_FUNCTION_GAMMA24
		// trans == TRANSFER_FUNCTION_GAMMA26
		poपूर्णांकs->end_exponent = 0;
		poपूर्णांकs->x_poपूर्णांक_at_y1_red = 1;
		poपूर्णांकs->x_poपूर्णांक_at_y1_green = 1;
		poपूर्णांकs->x_poपूर्णांक_at_y1_blue = 1;

		build_regamma(rgb_regamma,
				MAX_HW_POINTS,
				coordinates_x,
				trans,
				cal_buffer);

		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

bool mod_color_calculate_regamma_params(काष्ठा dc_transfer_func *output_tf,
		स्थिर काष्ठा dc_gamma *ramp, bool mapUserRamp, bool canRomBeUsed,
		स्थिर काष्ठा hdr_पंचांग_params *fs_params,
		काष्ठा calculate_buffer *cal_buffer)
अणु
	काष्ठा dc_transfer_func_distributed_poपूर्णांकs *tf_pts = &output_tf->tf_pts;
	काष्ठा भागiders भागiders;

	काष्ठा pwl_भग्न_data *rgb_user = शून्य;
	काष्ठा pwl_भग्न_data_ex *rgb_regamma = शून्य;
	काष्ठा gamma_pixel *axis_x = शून्य;
	काष्ठा pixel_gamma_poपूर्णांक *coeff = शून्य;
	क्रमागत dc_transfer_func_predefined tf = TRANSFER_FUNCTION_SRGB;
	bool करोClamping = true;
	bool ret = false;

	अगर (output_tf->type == TF_TYPE_BYPASS)
		वापस false;

	/* we can use hardcoded curve क्रम plain SRGB TF */
	अगर (output_tf->type == TF_TYPE_PREDEFINED && canRomBeUsed == true &&
			output_tf->tf == TRANSFER_FUNCTION_SRGB) अणु
		अगर (ramp == शून्य)
			वापस true;
		अगर ((ramp->is_identity && ramp->type != GAMMA_CS_TFM_1D) ||
				(!mapUserRamp && ramp->type == GAMMA_RGB_256))
			वापस true;
	पूर्ण

	output_tf->type = TF_TYPE_DISTRIBUTED_POINTS;

	अगर (ramp && ramp->type != GAMMA_CS_TFM_1D &&
			(mapUserRamp || ramp->type != GAMMA_RGB_256)) अणु
		rgb_user = kvसुस्मृति(ramp->num_entries + _EXTRA_POINTS,
			    माप(*rgb_user),
			    GFP_KERNEL);
		अगर (!rgb_user)
			जाओ rgb_user_alloc_fail;

		axis_x = kvसुस्मृति(ramp->num_entries + 3, माप(*axis_x),
				GFP_KERNEL);
		अगर (!axis_x)
			जाओ axis_x_alloc_fail;

		भागiders.भागider1 = dc_fixpt_from_fraction(3, 2);
		भागiders.भागider2 = dc_fixpt_from_पूर्णांक(2);
		भागiders.भागider3 = dc_fixpt_from_fraction(5, 2);

		build_evenly_distributed_poपूर्णांकs(
				axis_x,
				ramp->num_entries,
				भागiders);

		अगर (ramp->type == GAMMA_RGB_256 && mapUserRamp)
			scale_gamma(rgb_user, ramp, भागiders);
		अन्यथा अगर (ramp->type == GAMMA_RGB_FLOAT_1024)
			scale_gamma_dx(rgb_user, ramp, भागiders);
	पूर्ण

	rgb_regamma = kvसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS,
			       माप(*rgb_regamma),
			       GFP_KERNEL);
	अगर (!rgb_regamma)
		जाओ rgb_regamma_alloc_fail;

	coeff = kvसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS, माप(*coeff),
			 GFP_KERNEL);
	अगर (!coeff)
		जाओ coeff_alloc_fail;

	tf = output_tf->tf;

	ret = calculate_curve(tf,
			tf_pts,
			rgb_regamma,
			fs_params,
			output_tf->sdr_ref_white_level,
			cal_buffer);

	अगर (ret) अणु
		करोClamping = !(output_tf->tf == TRANSFER_FUNCTION_GAMMA22 &&
			fs_params != शून्य && fs_params->skip_पंचांग == 0);

		map_regamma_hw_to_x_user(ramp, coeff, rgb_user,
				coordinates_x, axis_x, rgb_regamma,
				MAX_HW_POINTS, tf_pts,
				(mapUserRamp || (ramp && ramp->type != GAMMA_RGB_256)) &&
				(ramp && ramp->type != GAMMA_CS_TFM_1D),
				करोClamping);

		अगर (ramp && ramp->type == GAMMA_CS_TFM_1D)
			apply_lut_1d(ramp, MAX_HW_POINTS, tf_pts);
	पूर्ण

	kvमुक्त(coeff);
coeff_alloc_fail:
	kvमुक्त(rgb_regamma);
rgb_regamma_alloc_fail:
	kvमुक्त(axis_x);
axis_x_alloc_fail:
	kvमुक्त(rgb_user);
rgb_user_alloc_fail:
	वापस ret;
पूर्ण

bool  mod_color_calculate_degamma_curve(क्रमागत dc_transfer_func_predefined trans,
				काष्ठा dc_transfer_func_distributed_poपूर्णांकs *poपूर्णांकs)
अणु
	uपूर्णांक32_t i;
	bool ret = false;
	काष्ठा pwl_भग्न_data_ex *rgb_degamma = शून्य;

	अगर (trans == TRANSFER_FUNCTION_UNITY ||
		trans == TRANSFER_FUNCTION_LINEAR) अणु

		क्रम (i = 0; i <= MAX_HW_POINTS ; i++) अणु
			poपूर्णांकs->red[i]    = coordinates_x[i].x;
			poपूर्णांकs->green[i]  = coordinates_x[i].x;
			poपूर्णांकs->blue[i]   = coordinates_x[i].x;
		पूर्ण
		ret = true;
	पूर्ण अन्यथा अगर (trans == TRANSFER_FUNCTION_PQ) अणु
		rgb_degamma = kvसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS,
				       माप(*rgb_degamma),
				       GFP_KERNEL);
		अगर (!rgb_degamma)
			जाओ rgb_degamma_alloc_fail;


		build_de_pq(rgb_degamma,
				MAX_HW_POINTS,
				coordinates_x);
		क्रम (i = 0; i <= MAX_HW_POINTS ; i++) अणु
			poपूर्णांकs->red[i]    = rgb_degamma[i].r;
			poपूर्णांकs->green[i]  = rgb_degamma[i].g;
			poपूर्णांकs->blue[i]   = rgb_degamma[i].b;
		पूर्ण
		ret = true;

		kvमुक्त(rgb_degamma);
	पूर्ण अन्यथा अगर (trans == TRANSFER_FUNCTION_SRGB ||
		trans == TRANSFER_FUNCTION_BT709 ||
		trans == TRANSFER_FUNCTION_GAMMA22 ||
		trans == TRANSFER_FUNCTION_GAMMA24 ||
		trans == TRANSFER_FUNCTION_GAMMA26) अणु
		rgb_degamma = kvसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS,
				       माप(*rgb_degamma),
				       GFP_KERNEL);
		अगर (!rgb_degamma)
			जाओ rgb_degamma_alloc_fail;

		build_degamma(rgb_degamma,
				MAX_HW_POINTS,
				coordinates_x,
				trans);
		क्रम (i = 0; i <= MAX_HW_POINTS ; i++) अणु
			poपूर्णांकs->red[i]    = rgb_degamma[i].r;
			poपूर्णांकs->green[i]  = rgb_degamma[i].g;
			poपूर्णांकs->blue[i]   = rgb_degamma[i].b;
		पूर्ण
		ret = true;

		kvमुक्त(rgb_degamma);
	पूर्ण अन्यथा अगर (trans == TRANSFER_FUNCTION_HLG) अणु
		rgb_degamma = kvसुस्मृति(MAX_HW_POINTS + _EXTRA_POINTS,
				       माप(*rgb_degamma),
				       GFP_KERNEL);
		अगर (!rgb_degamma)
			जाओ rgb_degamma_alloc_fail;

		build_hlg_degamma(rgb_degamma,
				MAX_HW_POINTS,
				coordinates_x,
				80, 1000);
		क्रम (i = 0; i <= MAX_HW_POINTS ; i++) अणु
			poपूर्णांकs->red[i]    = rgb_degamma[i].r;
			poपूर्णांकs->green[i]  = rgb_degamma[i].g;
			poपूर्णांकs->blue[i]   = rgb_degamma[i].b;
		पूर्ण
		ret = true;
		kvमुक्त(rgb_degamma);
	पूर्ण
	poपूर्णांकs->end_exponent = 0;
	poपूर्णांकs->x_poपूर्णांक_at_y1_red = 1;
	poपूर्णांकs->x_poपूर्णांक_at_y1_green = 1;
	poपूर्णांकs->x_poपूर्णांक_at_y1_blue = 1;

rgb_degamma_alloc_fail:
	वापस ret;
पूर्ण
