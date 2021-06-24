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

#समावेश <linux/delay.h>

#समावेश "dm_services.h"

/* include DCE11 रेजिस्टर header files */
#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"

#समावेश "dce110_transform_v.h"

अटल व्योम घातer_on_lut(काष्ठा transक्रमm *xfm,
	bool घातer_on, bool inputgamma, bool regamma)
अणु
	uपूर्णांक32_t value = dm_पढ़ो_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL);
	पूर्णांक i;

	अगर (घातer_on) अणु
		अगर (inputgamma)
			set_reg_field_value(
				value,
				1,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_INPUT_GAMMA_MEM_PWR_DIS);
		अगर (regamma)
			set_reg_field_value(
				value,
				1,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_GAMMA_CORR_MEM_PWR_DIS);
	पूर्ण अन्यथा अणु
		अगर (inputgamma)
			set_reg_field_value(
				value,
				0,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_INPUT_GAMMA_MEM_PWR_DIS);
		अगर (regamma)
			set_reg_field_value(
				value,
				0,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_GAMMA_CORR_MEM_PWR_DIS);
	पूर्ण

	dm_ग_लिखो_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL, value);

	क्रम (i = 0; i < 3; i++) अणु
		value = dm_पढ़ो_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL);
		अगर (get_reg_field_value(value,
				DCFEV_MEM_PWR_CTRL,
				COL_MAN_INPUT_GAMMA_MEM_PWR_DIS) &&
			get_reg_field_value(value,
					DCFEV_MEM_PWR_CTRL,
					COL_MAN_GAMMA_CORR_MEM_PWR_DIS))
			अवरोध;

		udelay(2);
	पूर्ण
पूर्ण

अटल व्योम set_bypass_input_gamma(काष्ठा dce_transक्रमm *xfm_dce)
अणु
	uपूर्णांक32_t value;

	value = dm_पढ़ो_reg(xfm_dce->base.ctx,
			mmCOL_MAN_INPUT_GAMMA_CONTROL1);

	set_reg_field_value(
				value,
				0,
				COL_MAN_INPUT_GAMMA_CONTROL1,
				INPUT_GAMMA_MODE);

	dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmCOL_MAN_INPUT_GAMMA_CONTROL1, value);
पूर्ण

अटल व्योम configure_regamma_mode(काष्ठा dce_transक्रमm *xfm_dce, uपूर्णांक32_t mode)
अणु
	uपूर्णांक32_t value = 0;

	set_reg_field_value(
				value,
				mode,
				GAMMA_CORR_CONTROL,
				GAMMA_CORR_MODE);

	dm_ग_लिखो_reg(xfm_dce->base.ctx, mmGAMMA_CORR_CONTROL, 0);
पूर्ण

/*
 *****************************************************************************
 *  Function: regamma_config_regions_and_segments
 *
 *     build regamma curve by using predefined hw poपूर्णांकs
 *     uses पूर्णांकerface parameters ,like EDID coeff.
 *
 * @param   : parameters   पूर्णांकerface parameters
 *  @वापस व्योम
 *
 *  @note
 *
 *  @see
 *
 *****************************************************************************
 */
अटल व्योम regamma_config_regions_and_segments(
	काष्ठा dce_transक्रमm *xfm_dce, स्थिर काष्ठा pwl_params *params)
अणु
	स्थिर काष्ठा gamma_curve *curve;
	uपूर्णांक32_t value = 0;

	अणु
		set_reg_field_value(
			value,
			params->arr_poपूर्णांकs[0].custom_भग्न_x,
			GAMMA_CORR_CNTLA_START_CNTL,
			GAMMA_CORR_CNTLA_EXP_REGION_START);

		set_reg_field_value(
			value,
			0,
			GAMMA_CORR_CNTLA_START_CNTL,
			GAMMA_CORR_CNTLA_EXP_REGION_START_SEGMENT);

		dm_ग_लिखो_reg(xfm_dce->base.ctx, mmGAMMA_CORR_CNTLA_START_CNTL,
				value);
	पूर्ण
	अणु
		value = 0;
		set_reg_field_value(
			value,
			params->arr_poपूर्णांकs[0].custom_भग्न_slope,
			GAMMA_CORR_CNTLA_SLOPE_CNTL,
			GAMMA_CORR_CNTLA_EXP_REGION_LINEAR_SLOPE);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_SLOPE_CNTL, value);
	पूर्ण
	अणु
		value = 0;
		set_reg_field_value(
			value,
			params->arr_poपूर्णांकs[1].custom_भग्न_x,
			GAMMA_CORR_CNTLA_END_CNTL1,
			GAMMA_CORR_CNTLA_EXP_REGION_END);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_END_CNTL1, value);
	पूर्ण
	अणु
		value = 0;
		set_reg_field_value(
			value,
			params->arr_poपूर्णांकs[1].custom_भग्न_slope,
			GAMMA_CORR_CNTLA_END_CNTL2,
			GAMMA_CORR_CNTLA_EXP_REGION_END_BASE);

		set_reg_field_value(
			value,
			params->arr_poपूर्णांकs[1].custom_भग्न_y,
			GAMMA_CORR_CNTLA_END_CNTL2,
			GAMMA_CORR_CNTLA_EXP_REGION_END_SLOPE);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_END_CNTL2, value);
	पूर्ण

	curve = params->arr_curve_poपूर्णांकs;

	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_0_1,
			GAMMA_CORR_CNTLA_EXP_REGION0_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_0_1,
			GAMMA_CORR_CNTLA_EXP_REGION0_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_0_1,
			GAMMA_CORR_CNTLA_EXP_REGION1_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_0_1,
			GAMMA_CORR_CNTLA_EXP_REGION1_NUM_SEGMENTS);

		dm_ग_लिखो_reg(
				xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_0_1,
			value);
	पूर्ण

	curve += 2;
	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_2_3,
			GAMMA_CORR_CNTLA_EXP_REGION2_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_2_3,
			GAMMA_CORR_CNTLA_EXP_REGION2_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_2_3,
			GAMMA_CORR_CNTLA_EXP_REGION3_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_2_3,
			GAMMA_CORR_CNTLA_EXP_REGION3_NUM_SEGMENTS);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_2_3,
			value);
	पूर्ण

	curve += 2;
	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_4_5,
			GAMMA_CORR_CNTLA_EXP_REGION4_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_4_5,
			GAMMA_CORR_CNTLA_EXP_REGION4_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_4_5,
			GAMMA_CORR_CNTLA_EXP_REGION5_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_4_5,
			GAMMA_CORR_CNTLA_EXP_REGION5_NUM_SEGMENTS);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_4_5,
			value);
	पूर्ण

	curve += 2;
	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_6_7,
			GAMMA_CORR_CNTLA_EXP_REGION6_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_6_7,
			GAMMA_CORR_CNTLA_EXP_REGION6_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_6_7,
			GAMMA_CORR_CNTLA_EXP_REGION7_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_6_7,
			GAMMA_CORR_CNTLA_EXP_REGION7_NUM_SEGMENTS);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_6_7,
			value);
	पूर्ण

	curve += 2;
	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_8_9,
			GAMMA_CORR_CNTLA_EXP_REGION8_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_8_9,
			GAMMA_CORR_CNTLA_EXP_REGION8_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_8_9,
			GAMMA_CORR_CNTLA_EXP_REGION9_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_8_9,
			GAMMA_CORR_CNTLA_EXP_REGION9_NUM_SEGMENTS);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_8_9,
			value);
	पूर्ण

	curve += 2;
	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_10_11,
			GAMMA_CORR_CNTLA_EXP_REGION10_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_10_11,
			GAMMA_CORR_CNTLA_EXP_REGION10_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_10_11,
			GAMMA_CORR_CNTLA_EXP_REGION11_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_10_11,
			GAMMA_CORR_CNTLA_EXP_REGION11_NUM_SEGMENTS);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_10_11,
			value);
	पूर्ण

	curve += 2;
	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_12_13,
			GAMMA_CORR_CNTLA_EXP_REGION12_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_12_13,
			GAMMA_CORR_CNTLA_EXP_REGION12_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_12_13,
			GAMMA_CORR_CNTLA_EXP_REGION13_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_12_13,
			GAMMA_CORR_CNTLA_EXP_REGION13_NUM_SEGMENTS);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_12_13,
			value);
	पूर्ण

	curve += 2;
	अणु
		value = 0;
		set_reg_field_value(
			value,
			curve[0].offset,
			GAMMA_CORR_CNTLA_REGION_14_15,
			GAMMA_CORR_CNTLA_EXP_REGION14_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[0].segments_num,
			GAMMA_CORR_CNTLA_REGION_14_15,
			GAMMA_CORR_CNTLA_EXP_REGION14_NUM_SEGMENTS);

		set_reg_field_value(
			value,
			curve[1].offset,
			GAMMA_CORR_CNTLA_REGION_14_15,
			GAMMA_CORR_CNTLA_EXP_REGION15_LUT_OFFSET);

		set_reg_field_value(
			value,
			curve[1].segments_num,
			GAMMA_CORR_CNTLA_REGION_14_15,
			GAMMA_CORR_CNTLA_EXP_REGION15_NUM_SEGMENTS);

		dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmGAMMA_CORR_CNTLA_REGION_14_15,
			value);
	पूर्ण
पूर्ण

अटल व्योम program_pwl(काष्ठा dce_transक्रमm *xfm_dce,
		स्थिर काष्ठा pwl_params *params)
अणु
	uपूर्णांक32_t value = 0;

	set_reg_field_value(
		value,
		7,
		GAMMA_CORR_LUT_WRITE_EN_MASK,
		GAMMA_CORR_LUT_WRITE_EN_MASK);

	dm_ग_लिखो_reg(xfm_dce->base.ctx,
		mmGAMMA_CORR_LUT_WRITE_EN_MASK, value);

	dm_ग_लिखो_reg(xfm_dce->base.ctx,
		mmGAMMA_CORR_LUT_INDEX, 0);

	/* Program REGAMMA_LUT_DATA */
	अणु
		स्थिर uपूर्णांक32_t addr = mmGAMMA_CORR_LUT_DATA;
		uपूर्णांक32_t i = 0;
		स्थिर काष्ठा pwl_result_data *rgb =
				params->rgb_resulted;

		जबतक (i != params->hw_poपूर्णांकs_num) अणु
			dm_ग_लिखो_reg(xfm_dce->base.ctx, addr, rgb->red_reg);
			dm_ग_लिखो_reg(xfm_dce->base.ctx, addr, rgb->green_reg);
			dm_ग_लिखो_reg(xfm_dce->base.ctx, addr, rgb->blue_reg);

			dm_ग_लिखो_reg(xfm_dce->base.ctx, addr,
				rgb->delta_red_reg);
			dm_ग_लिखो_reg(xfm_dce->base.ctx, addr,
				rgb->delta_green_reg);
			dm_ग_लिखो_reg(xfm_dce->base.ctx, addr,
				rgb->delta_blue_reg);

			++rgb;
			++i;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dce110_opp_program_regamma_pwl_v(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);

	/* Setup regions */
	regamma_config_regions_and_segments(xfm_dce, params);

	set_bypass_input_gamma(xfm_dce);

	/* Power on gamma LUT memory */
	घातer_on_lut(xfm, true, false, true);

	/* Program PWL */
	program_pwl(xfm_dce, params);

	/* program regamma config */
	configure_regamma_mode(xfm_dce, 1);

	/* Power वापस to स्वतः back */
	घातer_on_lut(xfm, false, false, true);
पूर्ण

व्योम dce110_opp_घातer_on_regamma_lut_v(
	काष्ठा transक्रमm *xfm,
	bool घातer_on)
अणु
	uपूर्णांक32_t value = dm_पढ़ो_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL);

	set_reg_field_value(
		value,
		0,
		DCFEV_MEM_PWR_CTRL,
		COL_MAN_GAMMA_CORR_MEM_PWR_FORCE);

	set_reg_field_value(
		value,
		घातer_on,
		DCFEV_MEM_PWR_CTRL,
		COL_MAN_GAMMA_CORR_MEM_PWR_DIS);

	set_reg_field_value(
		value,
		0,
		DCFEV_MEM_PWR_CTRL,
		COL_MAN_INPUT_GAMMA_MEM_PWR_FORCE);

	set_reg_field_value(
		value,
		घातer_on,
		DCFEV_MEM_PWR_CTRL,
		COL_MAN_INPUT_GAMMA_MEM_PWR_DIS);

	dm_ग_लिखो_reg(xfm->ctx, mmDCFEV_MEM_PWR_CTRL, value);
पूर्ण

व्योम dce110_opp_set_regamma_mode_v(
	काष्ठा transक्रमm *xfm,
	क्रमागत opp_regamma mode)
अणु
	// TODO: need to implement the function
पूर्ण
