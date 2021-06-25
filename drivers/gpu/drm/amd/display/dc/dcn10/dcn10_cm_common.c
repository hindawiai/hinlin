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
#समावेश "dc.h"
#समावेश "reg_helper.h"
#समावेश "dcn10_dpp.h"

#समावेश "dcn10_cm_common.h"
#समावेश "custom_float.h"

#घोषणा REG(reg) reg

#घोषणा CTX \
	ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	reg->shअगरts.field_name, reg->masks.field_name

व्योम cm_helper_program_color_matrices(
		काष्ठा dc_context *ctx,
		स्थिर uपूर्णांक16_t *regval,
		स्थिर काष्ठा color_matrices_reg *reg)
अणु
	uपूर्णांक32_t cur_csc_reg;
	अचिन्हित पूर्णांक i = 0;

	क्रम (cur_csc_reg = reg->csc_c11_c12;
			cur_csc_reg <= reg->csc_c33_c34;
			cur_csc_reg++) अणु

		स्थिर uपूर्णांक16_t *regval0 = &(regval[2 * i]);
		स्थिर uपूर्णांक16_t *regval1 = &(regval[(2 * i) + 1]);

		REG_SET_2(cur_csc_reg, 0,
				csc_c11, *regval0,
				csc_c12, *regval1);

		i++;
	पूर्ण

पूर्ण

व्योम cm_helper_program_xfer_func(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा pwl_params *params,
		स्थिर काष्ठा xfer_func_reg *reg)
अणु
	uपूर्णांक32_t reg_region_cur;
	अचिन्हित पूर्णांक i = 0;

	REG_SET_2(reg->start_cntl_b, 0,
			exp_region_start, params->corner_poपूर्णांकs[0].blue.custom_भग्न_x,
			exp_resion_start_segment, 0);
	REG_SET_2(reg->start_cntl_g, 0,
			exp_region_start, params->corner_poपूर्णांकs[0].green.custom_भग्न_x,
			exp_resion_start_segment, 0);
	REG_SET_2(reg->start_cntl_r, 0,
			exp_region_start, params->corner_poपूर्णांकs[0].red.custom_भग्न_x,
			exp_resion_start_segment, 0);

	REG_SET(reg->start_slope_cntl_b, 0,
			field_region_linear_slope, params->corner_poपूर्णांकs[0].blue.custom_भग्न_slope);
	REG_SET(reg->start_slope_cntl_g, 0,
			field_region_linear_slope, params->corner_poपूर्णांकs[0].green.custom_भग्न_slope);
	REG_SET(reg->start_slope_cntl_r, 0,
			field_region_linear_slope, params->corner_poपूर्णांकs[0].red.custom_भग्न_slope);

	REG_SET(reg->start_end_cntl1_b, 0,
			field_region_end, params->corner_poपूर्णांकs[1].blue.custom_भग्न_x);
	REG_SET_2(reg->start_end_cntl2_b, 0,
			field_region_end_slope, params->corner_poपूर्णांकs[1].blue.custom_भग्न_slope,
			field_region_end_base, params->corner_poपूर्णांकs[1].blue.custom_भग्न_y);

	REG_SET(reg->start_end_cntl1_g, 0,
			field_region_end, params->corner_poपूर्णांकs[1].green.custom_भग्न_x);
	REG_SET_2(reg->start_end_cntl2_g, 0,
			field_region_end_slope, params->corner_poपूर्णांकs[1].green.custom_भग्न_slope,
		field_region_end_base, params->corner_poपूर्णांकs[1].green.custom_भग्न_y);

	REG_SET(reg->start_end_cntl1_r, 0,
			field_region_end, params->corner_poपूर्णांकs[1].red.custom_भग्न_x);
	REG_SET_2(reg->start_end_cntl2_r, 0,
			field_region_end_slope, params->corner_poपूर्णांकs[1].red.custom_भग्न_slope,
		field_region_end_base, params->corner_poपूर्णांकs[1].red.custom_भग्न_y);

	क्रम (reg_region_cur = reg->region_start;
			reg_region_cur <= reg->region_end;
			reg_region_cur++) अणु

		स्थिर काष्ठा gamma_curve *curve0 = &(params->arr_curve_poपूर्णांकs[2 * i]);
		स्थिर काष्ठा gamma_curve *curve1 = &(params->arr_curve_poपूर्णांकs[(2 * i) + 1]);

		REG_SET_4(reg_region_cur, 0,
				exp_region0_lut_offset, curve0->offset,
				exp_region0_num_segments, curve0->segments_num,
				exp_region1_lut_offset, curve1->offset,
				exp_region1_num_segments, curve1->segments_num);

		i++;
	पूर्ण

पूर्ण



bool cm_helper_convert_to_custom_भग्न(
		काष्ठा pwl_result_data *rgb_resulted,
		काष्ठा curve_poपूर्णांकs3 *corner_poपूर्णांकs,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		bool fixpoपूर्णांक)
अणु
	काष्ठा custom_भग्न_क्रमmat fmt;

	काष्ठा pwl_result_data *rgb = rgb_resulted;

	uपूर्णांक32_t i = 0;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = false;

	/* corner_poपूर्णांकs[0] - beginning base, slope offset क्रम R,G,B
	 * corner_poपूर्णांकs[1] - end base, slope offset क्रम R,G,B
	 */
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].red.x, &fmt,
				&corner_poपूर्णांकs[0].red.custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].green.x, &fmt,
				&corner_poपूर्णांकs[0].green.custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].blue.x, &fmt,
				&corner_poपूर्णांकs[0].blue.custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].red.offset, &fmt,
				&corner_poपूर्णांकs[0].red.custom_भग्न_offset)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].green.offset, &fmt,
				&corner_poपूर्णांकs[0].green.custom_भग्न_offset)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].blue.offset, &fmt,
				&corner_poपूर्णांकs[0].blue.custom_भग्न_offset)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].red.slope, &fmt,
				&corner_poपूर्णांकs[0].red.custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].green.slope, &fmt,
				&corner_poपूर्णांकs[0].green.custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[0].blue.slope, &fmt,
				&corner_poपूर्णांकs[0].blue.custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	fmt.mantissa_bits = 10;
	fmt.sign = false;

	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].red.x, &fmt,
				&corner_poपूर्णांकs[1].red.custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].green.x, &fmt,
				&corner_poपूर्णांकs[1].green.custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].blue.x, &fmt,
				&corner_poपूर्णांकs[1].blue.custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (fixpoपूर्णांक == true) अणु
		corner_poपूर्णांकs[1].red.custom_भग्न_y =
				dc_fixpt_clamp_u0d14(corner_poपूर्णांकs[1].red.y);
		corner_poपूर्णांकs[1].green.custom_भग्न_y =
				dc_fixpt_clamp_u0d14(corner_poपूर्णांकs[1].green.y);
		corner_poपूर्णांकs[1].blue.custom_भग्न_y =
				dc_fixpt_clamp_u0d14(corner_poपूर्णांकs[1].blue.y);
	पूर्ण अन्यथा अणु
		अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].red.y,
				&fmt, &corner_poपूर्णांकs[1].red.custom_भग्न_y)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण
		अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].green.y,
				&fmt, &corner_poपूर्णांकs[1].green.custom_भग्न_y)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण
		अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].blue.y,
				&fmt, &corner_poपूर्णांकs[1].blue.custom_भग्न_y)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण
	पूर्ण

	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].red.slope, &fmt,
				&corner_poपूर्णांकs[1].red.custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].green.slope, &fmt,
				&corner_poपूर्णांकs[1].green.custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
	अगर (!convert_to_custom_भग्न_क्रमmat(corner_poपूर्णांकs[1].blue.slope, &fmt,
				&corner_poपूर्णांकs[1].blue.custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (hw_poपूर्णांकs_num == 0 || rgb_resulted == शून्य || fixpoपूर्णांक == true)
		वापस true;

	fmt.mantissa_bits = 12;
	fmt.sign = true;

	जबतक (i != hw_poपूर्णांकs_num) अणु
		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->red, &fmt,
						    &rgb->red_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->green, &fmt,
						    &rgb->green_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->blue, &fmt,
						    &rgb->blue_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->delta_red, &fmt,
						    &rgb->delta_red_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->delta_green, &fmt,
						    &rgb->delta_green_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->delta_blue, &fmt,
						    &rgb->delta_blue_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		++rgb;
		++i;
	पूर्ण

	वापस true;
पूर्ण

/* driver uses 32 regions or less, but DCN HW has 34, extra 2 are set to 0 */
#घोषणा MAX_REGIONS_NUMBER 34
#घोषणा MAX_LOW_POINT      25
#घोषणा NUMBER_REGIONS     32
#घोषणा NUMBER_SW_SEGMENTS 16

bool cm_helper_translate_curve_to_hw_क्रमmat(
				स्थिर काष्ठा dc_transfer_func *output_tf,
				काष्ठा pwl_params *lut_params, bool fixpoपूर्णांक)
अणु
	काष्ठा curve_poपूर्णांकs3 *corner_poपूर्णांकs;
	काष्ठा pwl_result_data *rgb_resulted;
	काष्ठा pwl_result_data *rgb;
	काष्ठा pwl_result_data *rgb_plus_1;
	काष्ठा pwl_result_data *rgb_minus_1;

	पूर्णांक32_t region_start, region_end;
	पूर्णांक32_t i;
	uपूर्णांक32_t j, k, seg_distr[MAX_REGIONS_NUMBER], increment, start_index, hw_poपूर्णांकs;

	अगर (output_tf == शून्य || lut_params == शून्य || output_tf->type == TF_TYPE_BYPASS)
		वापस false;

	corner_poपूर्णांकs = lut_params->corner_poपूर्णांकs;
	rgb_resulted = lut_params->rgb_resulted;
	hw_poपूर्णांकs = 0;

	स_रखो(lut_params, 0, माप(काष्ठा pwl_params));
	स_रखो(seg_distr, 0, माप(seg_distr));

	अगर (output_tf->tf == TRANSFER_FUNCTION_PQ || output_tf->tf == TRANSFER_FUNCTION_GAMMA22) अणु
		/* 32 segments
		 * segments are from 2^-25 to 2^7
		 */
		क्रम (i = 0; i < NUMBER_REGIONS ; i++)
			seg_distr[i] = 3;

		region_start = -MAX_LOW_POINT;
		region_end   = NUMBER_REGIONS - MAX_LOW_POINT;
	पूर्ण अन्यथा अणु
		/* 11 segments
		 * segment is from 2^-10 to 2^1
		 * There are less than 256 poपूर्णांकs, क्रम optimization
		 */
		seg_distr[0] = 3;
		seg_distr[1] = 4;
		seg_distr[2] = 4;
		seg_distr[3] = 4;
		seg_distr[4] = 4;
		seg_distr[5] = 4;
		seg_distr[6] = 4;
		seg_distr[7] = 4;
		seg_distr[8] = 4;
		seg_distr[9] = 4;
		seg_distr[10] = 1;

		region_start = -10;
		region_end = 1;
	पूर्ण

	क्रम (i = region_end - region_start; i < MAX_REGIONS_NUMBER ; i++)
		seg_distr[i] = -1;

	क्रम (k = 0; k < MAX_REGIONS_NUMBER; k++) अणु
		अगर (seg_distr[k] != -1)
			hw_poपूर्णांकs += (1 << seg_distr[k]);
	पूर्ण

	j = 0;
	क्रम (k = 0; k < (region_end - region_start); k++) अणु
		increment = NUMBER_SW_SEGMENTS / (1 << seg_distr[k]);
		start_index = (region_start + k + MAX_LOW_POINT) *
				NUMBER_SW_SEGMENTS;
		क्रम (i = start_index; i < start_index + NUMBER_SW_SEGMENTS;
				i += increment) अणु
			अगर (j == hw_poपूर्णांकs - 1)
				अवरोध;
			rgb_resulted[j].red = output_tf->tf_pts.red[i];
			rgb_resulted[j].green = output_tf->tf_pts.green[i];
			rgb_resulted[j].blue = output_tf->tf_pts.blue[i];
			j++;
		पूर्ण
	पूर्ण

	/* last poपूर्णांक */
	start_index = (region_end + MAX_LOW_POINT) * NUMBER_SW_SEGMENTS;
	rgb_resulted[hw_poपूर्णांकs - 1].red = output_tf->tf_pts.red[start_index];
	rgb_resulted[hw_poपूर्णांकs - 1].green = output_tf->tf_pts.green[start_index];
	rgb_resulted[hw_poपूर्णांकs - 1].blue = output_tf->tf_pts.blue[start_index];

	rgb_resulted[hw_poपूर्णांकs].red = rgb_resulted[hw_poपूर्णांकs - 1].red;
	rgb_resulted[hw_poपूर्णांकs].green = rgb_resulted[hw_poपूर्णांकs - 1].green;
	rgb_resulted[hw_poपूर्णांकs].blue = rgb_resulted[hw_poपूर्णांकs - 1].blue;

	// All 3 color channels have same x
	corner_poपूर्णांकs[0].red.x = dc_fixpt_घात(dc_fixpt_from_पूर्णांक(2),
					     dc_fixpt_from_पूर्णांक(region_start));
	corner_poपूर्णांकs[0].green.x = corner_poपूर्णांकs[0].red.x;
	corner_poपूर्णांकs[0].blue.x = corner_poपूर्णांकs[0].red.x;

	corner_poपूर्णांकs[1].red.x = dc_fixpt_घात(dc_fixpt_from_पूर्णांक(2),
					     dc_fixpt_from_पूर्णांक(region_end));
	corner_poपूर्णांकs[1].green.x = corner_poपूर्णांकs[1].red.x;
	corner_poपूर्णांकs[1].blue.x = corner_poपूर्णांकs[1].red.x;

	corner_poपूर्णांकs[0].red.y = rgb_resulted[0].red;
	corner_poपूर्णांकs[0].green.y = rgb_resulted[0].green;
	corner_poपूर्णांकs[0].blue.y = rgb_resulted[0].blue;

	corner_poपूर्णांकs[0].red.slope = dc_fixpt_भाग(corner_poपूर्णांकs[0].red.y,
			corner_poपूर्णांकs[0].red.x);
	corner_poपूर्णांकs[0].green.slope = dc_fixpt_भाग(corner_poपूर्णांकs[0].green.y,
			corner_poपूर्णांकs[0].green.x);
	corner_poपूर्णांकs[0].blue.slope = dc_fixpt_भाग(corner_poपूर्णांकs[0].blue.y,
			corner_poपूर्णांकs[0].blue.x);

	/* see comment above, m_arrPoपूर्णांकs[1].y should be the Y value क्रम the
	 * region end (m_numOfHwPoपूर्णांकs), not last HW poपूर्णांक(m_numOfHwPoपूर्णांकs - 1)
	 */
	corner_poपूर्णांकs[1].red.y = rgb_resulted[hw_poपूर्णांकs - 1].red;
	corner_poपूर्णांकs[1].green.y = rgb_resulted[hw_poपूर्णांकs - 1].green;
	corner_poपूर्णांकs[1].blue.y = rgb_resulted[hw_poपूर्णांकs - 1].blue;
	corner_poपूर्णांकs[1].red.slope = dc_fixpt_zero;
	corner_poपूर्णांकs[1].green.slope = dc_fixpt_zero;
	corner_poपूर्णांकs[1].blue.slope = dc_fixpt_zero;

	अगर (output_tf->tf == TRANSFER_FUNCTION_PQ) अणु
		/* क्रम PQ, we want to have a straight line from last HW X poपूर्णांक,
		 * and the slope to be such that we hit 1.0 at 10000 nits.
		 */
		स्थिर काष्ठा fixed31_32 end_value =
				dc_fixpt_from_पूर्णांक(125);

		corner_poपूर्णांकs[1].red.slope = dc_fixpt_भाग(
			dc_fixpt_sub(dc_fixpt_one, corner_poपूर्णांकs[1].red.y),
			dc_fixpt_sub(end_value, corner_poपूर्णांकs[1].red.x));
		corner_poपूर्णांकs[1].green.slope = dc_fixpt_भाग(
			dc_fixpt_sub(dc_fixpt_one, corner_poपूर्णांकs[1].green.y),
			dc_fixpt_sub(end_value, corner_poपूर्णांकs[1].green.x));
		corner_poपूर्णांकs[1].blue.slope = dc_fixpt_भाग(
			dc_fixpt_sub(dc_fixpt_one, corner_poपूर्णांकs[1].blue.y),
			dc_fixpt_sub(end_value, corner_poपूर्णांकs[1].blue.x));
	पूर्ण

	lut_params->hw_poपूर्णांकs_num = hw_poपूर्णांकs;

	k = 0;
	क्रम (i = 1; i < MAX_REGIONS_NUMBER; i++) अणु
		अगर (seg_distr[k] != -1) अणु
			lut_params->arr_curve_poपूर्णांकs[k].segments_num =
					seg_distr[k];
			lut_params->arr_curve_poपूर्णांकs[i].offset =
					lut_params->arr_curve_poपूर्णांकs[k].offset + (1 << seg_distr[k]);
		पूर्ण
		k++;
	पूर्ण

	अगर (seg_distr[k] != -1)
		lut_params->arr_curve_poपूर्णांकs[k].segments_num = seg_distr[k];

	rgb = rgb_resulted;
	rgb_plus_1 = rgb_resulted + 1;
	rgb_minus_1 = rgb;

	i = 1;
	जबतक (i != hw_poपूर्णांकs + 1) अणु

		अगर (i >= hw_poपूर्णांकs - 1) अणु
			अगर (dc_fixpt_lt(rgb_plus_1->red, rgb->red))
				rgb_plus_1->red = dc_fixpt_add(rgb->red, rgb_minus_1->delta_red);
			अगर (dc_fixpt_lt(rgb_plus_1->green, rgb->green))
				rgb_plus_1->green = dc_fixpt_add(rgb->green, rgb_minus_1->delta_green);
			अगर (dc_fixpt_lt(rgb_plus_1->blue, rgb->blue))
				rgb_plus_1->blue = dc_fixpt_add(rgb->blue, rgb_minus_1->delta_blue);
		पूर्ण

		rgb->delta_red   = dc_fixpt_sub(rgb_plus_1->red,   rgb->red);
		rgb->delta_green = dc_fixpt_sub(rgb_plus_1->green, rgb->green);
		rgb->delta_blue  = dc_fixpt_sub(rgb_plus_1->blue,  rgb->blue);

		अगर (fixpoपूर्णांक == true) अणु
			rgb->delta_red_reg   = dc_fixpt_clamp_u0d10(rgb->delta_red);
			rgb->delta_green_reg = dc_fixpt_clamp_u0d10(rgb->delta_green);
			rgb->delta_blue_reg  = dc_fixpt_clamp_u0d10(rgb->delta_blue);
			rgb->red_reg         = dc_fixpt_clamp_u0d14(rgb->red);
			rgb->green_reg       = dc_fixpt_clamp_u0d14(rgb->green);
			rgb->blue_reg        = dc_fixpt_clamp_u0d14(rgb->blue);
		पूर्ण

		++rgb_plus_1;
		rgb_minus_1 = rgb;
		++rgb;
		++i;
	पूर्ण
	cm_helper_convert_to_custom_भग्न(rgb_resulted,
						lut_params->corner_poपूर्णांकs,
						hw_poपूर्णांकs, fixpoपूर्णांक);

	वापस true;
पूर्ण

#घोषणा NUM_DEGAMMA_REGIONS    12


bool cm_helper_translate_curve_to_degamma_hw_क्रमmat(
				स्थिर काष्ठा dc_transfer_func *output_tf,
				काष्ठा pwl_params *lut_params)
अणु
	काष्ठा curve_poपूर्णांकs3 *corner_poपूर्णांकs;
	काष्ठा pwl_result_data *rgb_resulted;
	काष्ठा pwl_result_data *rgb;
	काष्ठा pwl_result_data *rgb_plus_1;

	पूर्णांक32_t region_start, region_end;
	पूर्णांक32_t i;
	uपूर्णांक32_t j, k, seg_distr[MAX_REGIONS_NUMBER], increment, start_index, hw_poपूर्णांकs;

	अगर (output_tf == शून्य || lut_params == शून्य || output_tf->type == TF_TYPE_BYPASS)
		वापस false;

	corner_poपूर्णांकs = lut_params->corner_poपूर्णांकs;
	rgb_resulted = lut_params->rgb_resulted;
	hw_poपूर्णांकs = 0;

	स_रखो(lut_params, 0, माप(काष्ठा pwl_params));
	स_रखो(seg_distr, 0, माप(seg_distr));

	region_start = -NUM_DEGAMMA_REGIONS;
	region_end   = 0;


	क्रम (i = region_end - region_start; i < MAX_REGIONS_NUMBER ; i++)
		seg_distr[i] = -1;
	/* 12 segments
	 * segments are from 2^-12 to 0
	 */
	क्रम (i = 0; i < NUM_DEGAMMA_REGIONS ; i++)
		seg_distr[i] = 4;

	क्रम (k = 0; k < MAX_REGIONS_NUMBER; k++) अणु
		अगर (seg_distr[k] != -1)
			hw_poपूर्णांकs += (1 << seg_distr[k]);
	पूर्ण

	j = 0;
	क्रम (k = 0; k < (region_end - region_start); k++) अणु
		increment = NUMBER_SW_SEGMENTS / (1 << seg_distr[k]);
		start_index = (region_start + k + MAX_LOW_POINT) *
				NUMBER_SW_SEGMENTS;
		क्रम (i = start_index; i < start_index + NUMBER_SW_SEGMENTS;
				i += increment) अणु
			अगर (j == hw_poपूर्णांकs - 1)
				अवरोध;
			rgb_resulted[j].red = output_tf->tf_pts.red[i];
			rgb_resulted[j].green = output_tf->tf_pts.green[i];
			rgb_resulted[j].blue = output_tf->tf_pts.blue[i];
			j++;
		पूर्ण
	पूर्ण

	/* last poपूर्णांक */
	start_index = (region_end + MAX_LOW_POINT) * NUMBER_SW_SEGMENTS;
	rgb_resulted[hw_poपूर्णांकs - 1].red = output_tf->tf_pts.red[start_index];
	rgb_resulted[hw_poपूर्णांकs - 1].green = output_tf->tf_pts.green[start_index];
	rgb_resulted[hw_poपूर्णांकs - 1].blue = output_tf->tf_pts.blue[start_index];

	rgb_resulted[hw_poपूर्णांकs].red = rgb_resulted[hw_poपूर्णांकs - 1].red;
	rgb_resulted[hw_poपूर्णांकs].green = rgb_resulted[hw_poपूर्णांकs - 1].green;
	rgb_resulted[hw_poपूर्णांकs].blue = rgb_resulted[hw_poपूर्णांकs - 1].blue;

	corner_poपूर्णांकs[0].red.x = dc_fixpt_घात(dc_fixpt_from_पूर्णांक(2),
					     dc_fixpt_from_पूर्णांक(region_start));
	corner_poपूर्णांकs[0].green.x = corner_poपूर्णांकs[0].red.x;
	corner_poपूर्णांकs[0].blue.x = corner_poपूर्णांकs[0].red.x;
	corner_poपूर्णांकs[1].red.x = dc_fixpt_घात(dc_fixpt_from_पूर्णांक(2),
					     dc_fixpt_from_पूर्णांक(region_end));
	corner_poपूर्णांकs[1].green.x = corner_poपूर्णांकs[1].red.x;
	corner_poपूर्णांकs[1].blue.x = corner_poपूर्णांकs[1].red.x;

	corner_poपूर्णांकs[0].red.y = rgb_resulted[0].red;
	corner_poपूर्णांकs[0].green.y = rgb_resulted[0].green;
	corner_poपूर्णांकs[0].blue.y = rgb_resulted[0].blue;

	/* see comment above, m_arrPoपूर्णांकs[1].y should be the Y value क्रम the
	 * region end (m_numOfHwPoपूर्णांकs), not last HW poपूर्णांक(m_numOfHwPoपूर्णांकs - 1)
	 */
	corner_poपूर्णांकs[1].red.y = rgb_resulted[hw_poपूर्णांकs - 1].red;
	corner_poपूर्णांकs[1].green.y = rgb_resulted[hw_poपूर्णांकs - 1].green;
	corner_poपूर्णांकs[1].blue.y = rgb_resulted[hw_poपूर्णांकs - 1].blue;
	corner_poपूर्णांकs[1].red.slope = dc_fixpt_zero;
	corner_poपूर्णांकs[1].green.slope = dc_fixpt_zero;
	corner_poपूर्णांकs[1].blue.slope = dc_fixpt_zero;

	अगर (output_tf->tf == TRANSFER_FUNCTION_PQ) अणु
		/* क्रम PQ, we want to have a straight line from last HW X poपूर्णांक,
		 * and the slope to be such that we hit 1.0 at 10000 nits.
		 */
		स्थिर काष्ठा fixed31_32 end_value =
				dc_fixpt_from_पूर्णांक(125);

		corner_poपूर्णांकs[1].red.slope = dc_fixpt_भाग(
			dc_fixpt_sub(dc_fixpt_one, corner_poपूर्णांकs[1].red.y),
			dc_fixpt_sub(end_value, corner_poपूर्णांकs[1].red.x));
		corner_poपूर्णांकs[1].green.slope = dc_fixpt_भाग(
			dc_fixpt_sub(dc_fixpt_one, corner_poपूर्णांकs[1].green.y),
			dc_fixpt_sub(end_value, corner_poपूर्णांकs[1].green.x));
		corner_poपूर्णांकs[1].blue.slope = dc_fixpt_भाग(
			dc_fixpt_sub(dc_fixpt_one, corner_poपूर्णांकs[1].blue.y),
			dc_fixpt_sub(end_value, corner_poपूर्णांकs[1].blue.x));
	पूर्ण

	lut_params->hw_poपूर्णांकs_num = hw_poपूर्णांकs;

	k = 0;
	क्रम (i = 1; i < MAX_REGIONS_NUMBER; i++) अणु
		अगर (seg_distr[k] != -1) अणु
			lut_params->arr_curve_poपूर्णांकs[k].segments_num =
					seg_distr[k];
			lut_params->arr_curve_poपूर्णांकs[i].offset =
					lut_params->arr_curve_poपूर्णांकs[k].offset + (1 << seg_distr[k]);
		पूर्ण
		k++;
	पूर्ण

	अगर (seg_distr[k] != -1)
		lut_params->arr_curve_poपूर्णांकs[k].segments_num = seg_distr[k];

	rgb = rgb_resulted;
	rgb_plus_1 = rgb_resulted + 1;

	i = 1;
	जबतक (i != hw_poपूर्णांकs + 1) अणु
		rgb->delta_red   = dc_fixpt_sub(rgb_plus_1->red,   rgb->red);
		rgb->delta_green = dc_fixpt_sub(rgb_plus_1->green, rgb->green);
		rgb->delta_blue  = dc_fixpt_sub(rgb_plus_1->blue,  rgb->blue);

		++rgb_plus_1;
		++rgb;
		++i;
	पूर्ण
	cm_helper_convert_to_custom_भग्न(rgb_resulted,
						lut_params->corner_poपूर्णांकs,
						hw_poपूर्णांकs, false);

	वापस true;
पूर्ण
