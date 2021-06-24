<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "core_types.h"
#समावेश "reg_helper.h"
#समावेश "dcn30_dpp.h"
#समावेश "basics/conversion.h"
#समावेश "dcn30_cm_common.h"

#घोषणा REG(reg)\
	dpp->tf_regs->reg

#घोषणा CTX \
	dpp->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dpp->tf_shअगरt->field_name, dpp->tf_mask->field_name

अटल व्योम dpp3_enable_cm_block(
		काष्ठा dpp *dpp_base)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अचिन्हित पूर्णांक cm_bypass_mode = 0;

	// debug option: put CM in bypass mode
	अगर (dpp_base->ctx->dc->debug.cm_in_bypass)
		cm_bypass_mode = 1;

	REG_UPDATE(CM_CONTROL, CM_BYPASS, cm_bypass_mode);
पूर्ण

अटल क्रमागत dc_lut_mode dpp30_get_gamcor_current(काष्ठा dpp *dpp_base)
अणु
	क्रमागत dc_lut_mode mode;
	uपूर्णांक32_t state_mode;
	uपूर्णांक32_t lut_mode;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_GET(CM_GAMCOR_CONTROL,
			CM_GAMCOR_MODE_CURRENT, &state_mode);

		अगर (state_mode == 0)
			mode = LUT_BYPASS;

		अगर (state_mode == 2) अणु//Programmable RAM LUT
			REG_GET(CM_GAMCOR_CONTROL,
					CM_GAMCOR_SELECT_CURRENT, &lut_mode);

			अगर (lut_mode == 0)
				mode = LUT_RAM_A;
			अन्यथा
				mode = LUT_RAM_B;
		पूर्ण

		वापस mode;
पूर्ण

अटल व्योम dpp3_program_gammcor_lut(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_result_data *rgb,
		uपूर्णांक32_t num,
		bool is_ram_a)
अणु
	uपूर्णांक32_t i;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	uपूर्णांक32_t last_base_value_red = rgb[num-1].red_reg + rgb[num-1].delta_red_reg;
	uपूर्णांक32_t last_base_value_green = rgb[num-1].green_reg + rgb[num-1].delta_green_reg;
	uपूर्णांक32_t last_base_value_blue = rgb[num-1].blue_reg + rgb[num-1].delta_blue_reg;

	/*fill in the LUT with all base values to be used by pwl module
	 * HW स्वतः increments the LUT index: back-to-back ग_लिखो
	 */
	अगर (is_rgb_equal(rgb,  num)) अणु
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, rgb[i].red_reg);

		REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, last_base_value_red);

	पूर्ण अन्यथा अणु
		REG_UPDATE(CM_GAMCOR_LUT_CONTROL,
				CM_GAMCOR_LUT_WRITE_COLOR_MASK, 4);
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, rgb[i].red_reg);

		REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, last_base_value_red);

		REG_SET(CM_GAMCOR_LUT_INDEX, 0, CM_GAMCOR_LUT_INDEX, 0);

		REG_UPDATE(CM_GAMCOR_LUT_CONTROL,
				CM_GAMCOR_LUT_WRITE_COLOR_MASK, 2);
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, rgb[i].green_reg);

		REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, last_base_value_green);

		REG_SET(CM_GAMCOR_LUT_INDEX, 0, CM_GAMCOR_LUT_INDEX, 0);

		REG_UPDATE(CM_GAMCOR_LUT_CONTROL,
				CM_GAMCOR_LUT_WRITE_COLOR_MASK, 1);
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, rgb[i].blue_reg);

		REG_SET(CM_GAMCOR_LUT_DATA, 0, CM_GAMCOR_LUT_DATA, last_base_value_blue);
	पूर्ण
पूर्ण

अटल व्योम dpp3_घातer_on_gamcor_lut(
		काष्ठा dpp *dpp_base,
	bool घातer_on)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm) अणु
		REG_UPDATE(CM_MEM_PWR_CTRL, GAMCOR_MEM_PWR_FORCE, घातer_on ? 0 : 3);
		अगर (घातer_on)
			REG_WAIT(CM_MEM_PWR_STATUS, GAMCOR_MEM_PWR_STATE, 0, 1, 5);
	पूर्ण अन्यथा
		REG_SET(CM_MEM_PWR_CTRL, 0,
				GAMCOR_MEM_PWR_DIS, घातer_on == true ? 0:1);
पूर्ण

व्योम dpp3_program_cm_dealpha(
		काष्ठा dpp *dpp_base,
	uपूर्णांक32_t enable, uपूर्णांक32_t additive_blending)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_SET_2(CM_DEALPHA, 0,
			CM_DEALPHA_EN, enable,
			CM_DEALPHA_ABLND, additive_blending);
पूर्ण

व्योम dpp3_program_cm_bias(
	काष्ठा dpp *dpp_base,
	काष्ठा CM_bias_params *bias_params)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_SET(CM_BIAS_CR_R, 0, CM_BIAS_CR_R, bias_params->cm_bias_cr_r);
	REG_SET_2(CM_BIAS_Y_G_CB_B, 0,
			CM_BIAS_Y_G, bias_params->cm_bias_y_g,
			CM_BIAS_CB_B, bias_params->cm_bias_cb_b);
पूर्ण

अटल व्योम dpp3_gamcor_reg_field(
		काष्ठा dcn3_dpp *dpp,
		काष्ठा dcn3_xfer_func_reg *reg)
अणु

	reg->shअगरts.field_region_start_base = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION_START_BASE_B;
	reg->masks.field_region_start_base = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION_START_BASE_B;
	reg->shअगरts.field_offset = dpp->tf_shअगरt->CM_GAMCOR_RAMA_OFFSET_B;
	reg->masks.field_offset = dpp->tf_mask->CM_GAMCOR_RAMA_OFFSET_B;

	reg->shअगरts.exp_region0_lut_offset = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shअगरts.exp_region0_num_segments = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shअगरts.exp_region1_lut_offset = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shअगरts.exp_region1_num_segments = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION1_NUM_SEGMENTS;

	reg->shअगरts.field_region_end = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION_END_B;
	reg->masks.field_region_end = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION_END_B;
	reg->shअगरts.field_region_end_slope = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION_END_SLOPE_B;
	reg->shअगरts.field_region_end_base = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION_END_BASE_B;
	reg->shअगरts.field_region_linear_slope = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION_START_SLOPE_B;
	reg->masks.field_region_linear_slope = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION_START_SLOPE_B;
	reg->shअगरts.exp_region_start = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION_START_B;
	reg->masks.exp_region_start = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION_START_B;
	reg->shअगरts.exp_resion_start_segment = dpp->tf_shअगरt->CM_GAMCOR_RAMA_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = dpp->tf_mask->CM_GAMCOR_RAMA_EXP_REGION_START_SEGMENT_B;
पूर्ण

अटल व्योम dpp3_configure_gamcor_lut(
		काष्ठा dpp *dpp_base,
		bool is_ram_a)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_UPDATE(CM_GAMCOR_LUT_CONTROL,
			CM_GAMCOR_LUT_WRITE_COLOR_MASK, 7);
	REG_UPDATE(CM_GAMCOR_LUT_CONTROL,
			CM_GAMCOR_LUT_HOST_SEL, is_ram_a == true ? 0:1);
	REG_SET(CM_GAMCOR_LUT_INDEX, 0, CM_GAMCOR_LUT_INDEX, 0);
पूर्ण


bool dpp3_program_gamcor_lut(
	काष्ठा dpp *dpp_base, स्थिर काष्ठा pwl_params *params)
अणु
	क्रमागत dc_lut_mode current_mode;
	क्रमागत dc_lut_mode next_mode;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	काष्ठा dcn3_xfer_func_reg gam_regs;

	dpp3_enable_cm_block(dpp_base);

	अगर (params == शून्य) अणु //bypass अगर we have no pwl data
		REG_SET(CM_GAMCOR_CONTROL, 0, CM_GAMCOR_MODE, 0);
		अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm)
			dpp3_घातer_on_gamcor_lut(dpp_base, false);
		वापस false;
	पूर्ण
	dpp3_घातer_on_gamcor_lut(dpp_base, true);
	REG_SET(CM_GAMCOR_CONTROL, 0, CM_GAMCOR_MODE, 2);

	current_mode = dpp30_get_gamcor_current(dpp_base);
	अगर (current_mode == LUT_BYPASS || current_mode == LUT_RAM_A)
		next_mode = LUT_RAM_B;
	अन्यथा
		next_mode = LUT_RAM_A;

	dpp3_घातer_on_gamcor_lut(dpp_base, true);
	dpp3_configure_gamcor_lut(dpp_base, next_mode == LUT_RAM_A);

	अगर (next_mode == LUT_RAM_B) अणु
		gam_regs.start_cntl_b = REG(CM_GAMCOR_RAMB_START_CNTL_B);
		gam_regs.start_cntl_g = REG(CM_GAMCOR_RAMB_START_CNTL_G);
		gam_regs.start_cntl_r = REG(CM_GAMCOR_RAMB_START_CNTL_R);
		gam_regs.start_slope_cntl_b = REG(CM_GAMCOR_RAMB_START_SLOPE_CNTL_B);
		gam_regs.start_slope_cntl_g = REG(CM_GAMCOR_RAMB_START_SLOPE_CNTL_G);
		gam_regs.start_slope_cntl_r = REG(CM_GAMCOR_RAMB_START_SLOPE_CNTL_R);
		gam_regs.start_end_cntl1_b = REG(CM_GAMCOR_RAMB_END_CNTL1_B);
		gam_regs.start_end_cntl2_b = REG(CM_GAMCOR_RAMB_END_CNTL2_B);
		gam_regs.start_end_cntl1_g = REG(CM_GAMCOR_RAMB_END_CNTL1_G);
		gam_regs.start_end_cntl2_g = REG(CM_GAMCOR_RAMB_END_CNTL2_G);
		gam_regs.start_end_cntl1_r = REG(CM_GAMCOR_RAMB_END_CNTL1_R);
		gam_regs.start_end_cntl2_r = REG(CM_GAMCOR_RAMB_END_CNTL2_R);
		gam_regs.region_start = REG(CM_GAMCOR_RAMB_REGION_0_1);
		gam_regs.region_end = REG(CM_GAMCOR_RAMB_REGION_32_33);
		//New रेजिस्टरs in DCN3AG/DCN GAMCOR block
		gam_regs.offset_b =  REG(CM_GAMCOR_RAMB_OFFSET_B);
		gam_regs.offset_g =  REG(CM_GAMCOR_RAMB_OFFSET_G);
		gam_regs.offset_r =  REG(CM_GAMCOR_RAMB_OFFSET_R);
		gam_regs.start_base_cntl_b = REG(CM_GAMCOR_RAMB_START_BASE_CNTL_B);
		gam_regs.start_base_cntl_g = REG(CM_GAMCOR_RAMB_START_BASE_CNTL_G);
		gam_regs.start_base_cntl_r = REG(CM_GAMCOR_RAMB_START_BASE_CNTL_R);
	पूर्ण अन्यथा अणु
		gam_regs.start_cntl_b = REG(CM_GAMCOR_RAMA_START_CNTL_B);
		gam_regs.start_cntl_g = REG(CM_GAMCOR_RAMA_START_CNTL_G);
		gam_regs.start_cntl_r = REG(CM_GAMCOR_RAMA_START_CNTL_R);
		gam_regs.start_slope_cntl_b = REG(CM_GAMCOR_RAMA_START_SLOPE_CNTL_B);
		gam_regs.start_slope_cntl_g = REG(CM_GAMCOR_RAMA_START_SLOPE_CNTL_G);
		gam_regs.start_slope_cntl_r = REG(CM_GAMCOR_RAMA_START_SLOPE_CNTL_R);
		gam_regs.start_end_cntl1_b = REG(CM_GAMCOR_RAMA_END_CNTL1_B);
		gam_regs.start_end_cntl2_b = REG(CM_GAMCOR_RAMA_END_CNTL2_B);
		gam_regs.start_end_cntl1_g = REG(CM_GAMCOR_RAMA_END_CNTL1_G);
		gam_regs.start_end_cntl2_g = REG(CM_GAMCOR_RAMA_END_CNTL2_G);
		gam_regs.start_end_cntl1_r = REG(CM_GAMCOR_RAMA_END_CNTL1_R);
		gam_regs.start_end_cntl2_r = REG(CM_GAMCOR_RAMA_END_CNTL2_R);
		gam_regs.region_start = REG(CM_GAMCOR_RAMA_REGION_0_1);
		gam_regs.region_end = REG(CM_GAMCOR_RAMA_REGION_32_33);
		//New रेजिस्टरs in DCN3AG/DCN GAMCOR block
		gam_regs.offset_b =  REG(CM_GAMCOR_RAMA_OFFSET_B);
		gam_regs.offset_g =  REG(CM_GAMCOR_RAMA_OFFSET_G);
		gam_regs.offset_r =  REG(CM_GAMCOR_RAMA_OFFSET_R);
		gam_regs.start_base_cntl_b = REG(CM_GAMCOR_RAMA_START_BASE_CNTL_B);
		gam_regs.start_base_cntl_g = REG(CM_GAMCOR_RAMA_START_BASE_CNTL_G);
		gam_regs.start_base_cntl_r = REG(CM_GAMCOR_RAMA_START_BASE_CNTL_R);
	पूर्ण

	//get रेजिस्टर fields
	dpp3_gamcor_reg_field(dpp, &gam_regs);

	//program रेजिस्टर set क्रम LUTA/LUTB
	cm_helper_program_gamcor_xfer_func(dpp_base->ctx, params, &gam_regs);

	dpp3_program_gammcor_lut(dpp_base, params->rgb_resulted, params->hw_poपूर्णांकs_num,
				 next_mode == LUT_RAM_A);

	//select Gamma LUT to use क्रम next frame
	REG_UPDATE(CM_GAMCOR_CONTROL, CM_GAMCOR_SELECT, next_mode == LUT_RAM_A ? 0:1);

	वापस true;
पूर्ण

व्योम dpp3_set_hdr_multiplier(
		काष्ठा dpp *dpp_base,
		uपूर्णांक32_t multiplier)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_UPDATE(CM_HDR_MULT_COEF, CM_HDR_MULT_COEF, multiplier);
पूर्ण


अटल व्योम program_gamut_remap(
		काष्ठा dcn3_dpp *dpp,
		स्थिर uपूर्णांक16_t *regval,
		पूर्णांक select)
अणु
	uपूर्णांक16_t selection = 0;
	काष्ठा color_matrices_reg gam_regs;

	अगर (regval == शून्य || select == GAMUT_REMAP_BYPASS) अणु
		REG_SET(CM_GAMUT_REMAP_CONTROL, 0,
				CM_GAMUT_REMAP_MODE, 0);
		वापस;
	पूर्ण
	चयन (select) अणु
	हाल GAMUT_REMAP_COEFF:
		selection = 1;
		अवरोध;
		/*this corresponds to GAMUT_REMAP coefficients set B
		 *we करोn't have common coefficient sets in dcn3ag/dcn3
		 */
	हाल GAMUT_REMAP_COMA_COEFF:
		selection = 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	gam_regs.shअगरts.csc_c11 = dpp->tf_shअगरt->CM_GAMUT_REMAP_C11;
	gam_regs.masks.csc_c11  = dpp->tf_mask->CM_GAMUT_REMAP_C11;
	gam_regs.shअगरts.csc_c12 = dpp->tf_shअगरt->CM_GAMUT_REMAP_C12;
	gam_regs.masks.csc_c12 = dpp->tf_mask->CM_GAMUT_REMAP_C12;


	अगर (select == GAMUT_REMAP_COEFF) अणु
		gam_regs.csc_c11_c12 = REG(CM_GAMUT_REMAP_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_GAMUT_REMAP_C33_C34);

		cm_helper_program_color_matrices(
				dpp->base.ctx,
				regval,
				&gam_regs);

	पूर्ण अन्यथा  अगर (select == GAMUT_REMAP_COMA_COEFF) अणु

		gam_regs.csc_c11_c12 = REG(CM_GAMUT_REMAP_B_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_GAMUT_REMAP_B_C33_C34);

		cm_helper_program_color_matrices(
				dpp->base.ctx,
				regval,
				&gam_regs);

	पूर्ण
	//select coefficient set to use
	REG_SET(
			CM_GAMUT_REMAP_CONTROL, 0,
			CM_GAMUT_REMAP_MODE, selection);
पूर्ण

व्योम dpp3_cm_set_gamut_remap(
	काष्ठा dpp *dpp_base,
	स्थिर काष्ठा dpp_grph_csc_adjusपंचांगent *adjust)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	पूर्णांक i = 0;
	पूर्णांक gamut_mode;

	अगर (adjust->gamut_adjust_type != GRAPHICS_GAMUT_ADJUST_TYPE_SW)
		/* Bypass अगर type is bypass or hw */
		program_gamut_remap(dpp, शून्य, GAMUT_REMAP_BYPASS);
	अन्यथा अणु
		काष्ठा fixed31_32 arr_matrix[12];
		uपूर्णांक16_t arr_reg_val[12];

		क्रम (i = 0; i < 12; i++)
			arr_matrix[i] = adjust->temperature_matrix[i];

		convert_भग्न_matrix(
			arr_reg_val, arr_matrix, 12);

		//current coefficient set in use
		REG_GET(CM_GAMUT_REMAP_CONTROL, CM_GAMUT_REMAP_MODE_CURRENT, &gamut_mode);

		अगर (gamut_mode == 0)
			gamut_mode = 1; //use coefficient set A
		अन्यथा अगर (gamut_mode == 1)
			gamut_mode = 2;
		अन्यथा
			gamut_mode = 1;

		//follow dcn2 approach क्रम now - using only coefficient set A
		program_gamut_remap(dpp, arr_reg_val, GAMUT_REMAP_COEFF);
	पूर्ण
पूर्ण
