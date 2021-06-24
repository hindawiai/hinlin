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

#समावेश "dm_services.h"

#समावेश "core_types.h"

#समावेश "reg_helper.h"
#समावेश "dcn10_dpp.h"
#समावेश "basics/conversion.h"
#समावेश "dcn10_cm_common.h"

#घोषणा NUM_PHASES    64
#घोषणा HORZ_MAX_TAPS 8
#घोषणा VERT_MAX_TAPS 8

#घोषणा BLACK_OFFSET_RGB_Y 0x0
#घोषणा BLACK_OFFSET_CBCR  0x8000

#घोषणा REG(reg)\
	dpp->tf_regs->reg

#घोषणा CTX \
	dpp->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dpp->tf_shअगरt->field_name, dpp->tf_mask->field_name

#घोषणा NUM_ELEMENTS(a) (माप(a) / माप((a)[0]))


क्रमागत dcn10_coef_filter_type_sel अणु
	SCL_COEF_LUMA_VERT_FILTER = 0,
	SCL_COEF_LUMA_HORZ_FILTER = 1,
	SCL_COEF_CHROMA_VERT_FILTER = 2,
	SCL_COEF_CHROMA_HORZ_FILTER = 3,
	SCL_COEF_ALPHA_VERT_FILTER = 4,
	SCL_COEF_ALPHA_HORZ_FILTER = 5
पूर्ण;

क्रमागत dscl_स्वतःcal_mode अणु
	AUTOCAL_MODE_OFF = 0,

	/* Autocal calculate the scaling ratio and initial phase and the
	 * DSCL_MODE_SEL must be set to 1
	 */
	AUTOCAL_MODE_AUTOSCALE = 1,
	/* Autocal perक्रमm स्वतः centering without replication and the
	 * DSCL_MODE_SEL must be set to 0
	 */
	AUTOCAL_MODE_AUTOCENTER = 2,
	/* Autocal perक्रमm स्वतः centering and स्वतः replication and the
	 * DSCL_MODE_SEL must be set to 0
	 */
	AUTOCAL_MODE_AUTOREPLICATE = 3
पूर्ण;

क्रमागत dscl_mode_sel अणु
	DSCL_MODE_SCALING_444_BYPASS = 0,
	DSCL_MODE_SCALING_444_RGB_ENABLE = 1,
	DSCL_MODE_SCALING_444_YCBCR_ENABLE = 2,
	DSCL_MODE_SCALING_420_YCBCR_ENABLE = 3,
	DSCL_MODE_SCALING_420_LUMA_BYPASS = 4,
	DSCL_MODE_SCALING_420_CHROMA_BYPASS = 5,
	DSCL_MODE_DSCL_BYPASS = 6
पूर्ण;

अटल व्योम program_gamut_remap(
		काष्ठा dcn10_dpp *dpp,
		स्थिर uपूर्णांक16_t *regval,
		क्रमागत gamut_remap_select select)
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
	हाल GAMUT_REMAP_COMA_COEFF:
		selection = 2;
		अवरोध;
	हाल GAMUT_REMAP_COMB_COEFF:
		selection = 3;
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

		gam_regs.csc_c11_c12 = REG(CM_COMA_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_COMA_C33_C34);

		cm_helper_program_color_matrices(
				dpp->base.ctx,
				regval,
				&gam_regs);

	पूर्ण अन्यथा अणु

		gam_regs.csc_c11_c12 = REG(CM_COMB_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_COMB_C33_C34);

		cm_helper_program_color_matrices(
				dpp->base.ctx,
				regval,
				&gam_regs);
	पूर्ण

	REG_SET(
			CM_GAMUT_REMAP_CONTROL, 0,
			CM_GAMUT_REMAP_MODE, selection);

पूर्ण

व्योम dpp1_cm_set_gamut_remap(
	काष्ठा dpp *dpp_base,
	स्थिर काष्ठा dpp_grph_csc_adjusपंचांगent *adjust)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	पूर्णांक i = 0;

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

		program_gamut_remap(dpp, arr_reg_val, GAMUT_REMAP_COEFF);
	पूर्ण
पूर्ण

अटल व्योम dpp1_cm_program_color_matrix(
		काष्ठा dcn10_dpp *dpp,
		स्थिर uपूर्णांक16_t *regval)
अणु
	uपूर्णांक32_t ocsc_mode;
	uपूर्णांक32_t cur_mode;
	काष्ठा color_matrices_reg gam_regs;

	अगर (regval == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	/* determine which CSC matrix (ocsc or comb) we are using
	 * currently.  select the alternate set to द्विगुन buffer
	 * the CSC update so CSC is updated on frame boundary
	 */
	REG_SET(CM_TEST_DEBUG_INDEX, 0,
			CM_TEST_DEBUG_INDEX, 9);

	REG_GET(CM_TEST_DEBUG_DATA,
			CM_TEST_DEBUG_DATA_ID9_OCSC_MODE, &cur_mode);

	अगर (cur_mode != 4)
		ocsc_mode = 4;
	अन्यथा
		ocsc_mode = 5;


	gam_regs.shअगरts.csc_c11 = dpp->tf_shअगरt->CM_OCSC_C11;
	gam_regs.masks.csc_c11  = dpp->tf_mask->CM_OCSC_C11;
	gam_regs.shअगरts.csc_c12 = dpp->tf_shअगरt->CM_OCSC_C12;
	gam_regs.masks.csc_c12 = dpp->tf_mask->CM_OCSC_C12;

	अगर (ocsc_mode == 4) अणु

		gam_regs.csc_c11_c12 = REG(CM_OCSC_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_OCSC_C33_C34);

	पूर्ण अन्यथा अणु

		gam_regs.csc_c11_c12 = REG(CM_COMB_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_COMB_C33_C34);

	पूर्ण

	cm_helper_program_color_matrices(
			dpp->base.ctx,
			regval,
			&gam_regs);

	REG_SET(CM_OCSC_CONTROL, 0, CM_OCSC_MODE, ocsc_mode);

पूर्ण

व्योम dpp1_cm_set_output_csc_शेष(
		काष्ठा dpp *dpp_base,
		क्रमागत dc_color_space colorspace)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	स्थिर uपूर्णांक16_t *regval = शून्य;
	पूर्णांक arr_size;

	regval = find_color_matrix(colorspace, &arr_size);
	अगर (regval == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	dpp1_cm_program_color_matrix(dpp, regval);
पूर्ण

अटल व्योम dpp1_cm_get_reg_field(
		काष्ठा dcn10_dpp *dpp,
		काष्ठा xfer_func_reg *reg)
अणु
	reg->shअगरts.exp_region0_lut_offset = dpp->tf_shअगरt->CM_RGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = dpp->tf_mask->CM_RGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shअगरts.exp_region0_num_segments = dpp->tf_shअगरt->CM_RGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = dpp->tf_mask->CM_RGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shअगरts.exp_region1_lut_offset = dpp->tf_shअगरt->CM_RGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = dpp->tf_mask->CM_RGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shअगरts.exp_region1_num_segments = dpp->tf_shअगरt->CM_RGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = dpp->tf_mask->CM_RGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;

	reg->shअगरts.field_region_end = dpp->tf_shअगरt->CM_RGAM_RAMB_EXP_REGION_END_B;
	reg->masks.field_region_end = dpp->tf_mask->CM_RGAM_RAMB_EXP_REGION_END_B;
	reg->shअगरts.field_region_end_slope = dpp->tf_shअगरt->CM_RGAM_RAMB_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = dpp->tf_mask->CM_RGAM_RAMB_EXP_REGION_END_SLOPE_B;
	reg->shअगरts.field_region_end_base = dpp->tf_shअगरt->CM_RGAM_RAMB_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = dpp->tf_mask->CM_RGAM_RAMB_EXP_REGION_END_BASE_B;
	reg->shअगरts.field_region_linear_slope = dpp->tf_shअगरt->CM_RGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B;
	reg->masks.field_region_linear_slope = dpp->tf_mask->CM_RGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B;
	reg->shअगरts.exp_region_start = dpp->tf_shअगरt->CM_RGAM_RAMB_EXP_REGION_START_B;
	reg->masks.exp_region_start = dpp->tf_mask->CM_RGAM_RAMB_EXP_REGION_START_B;
	reg->shअगरts.exp_resion_start_segment = dpp->tf_shअगरt->CM_RGAM_RAMB_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = dpp->tf_mask->CM_RGAM_RAMB_EXP_REGION_START_SEGMENT_B;
पूर्ण

अटल व्योम dpp1_cm_get_degamma_reg_field(
		काष्ठा dcn10_dpp *dpp,
		काष्ठा xfer_func_reg *reg)
अणु
	reg->shअगरts.exp_region0_lut_offset = dpp->tf_shअगरt->CM_DGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shअगरts.exp_region0_num_segments = dpp->tf_shअगरt->CM_DGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shअगरts.exp_region1_lut_offset = dpp->tf_shअगरt->CM_DGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shअगरts.exp_region1_num_segments = dpp->tf_shअगरt->CM_DGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;

	reg->shअगरts.field_region_end = dpp->tf_shअगरt->CM_DGAM_RAMB_EXP_REGION_END_B;
	reg->masks.field_region_end = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_END_B;
	reg->shअगरts.field_region_end_slope = dpp->tf_shअगरt->CM_DGAM_RAMB_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_END_SLOPE_B;
	reg->shअगरts.field_region_end_base = dpp->tf_shअगरt->CM_DGAM_RAMB_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_END_BASE_B;
	reg->shअगरts.field_region_linear_slope = dpp->tf_shअगरt->CM_DGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B;
	reg->masks.field_region_linear_slope = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B;
	reg->shअगरts.exp_region_start = dpp->tf_shअगरt->CM_DGAM_RAMB_EXP_REGION_START_B;
	reg->masks.exp_region_start = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_START_B;
	reg->shअगरts.exp_resion_start_segment = dpp->tf_shअगरt->CM_DGAM_RAMB_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_START_SEGMENT_B;
पूर्ण
व्योम dpp1_cm_set_output_csc_adjusपंचांगent(
		काष्ठा dpp *dpp_base,
		स्थिर uपूर्णांक16_t *regval)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	dpp1_cm_program_color_matrix(dpp, regval);
पूर्ण

व्योम dpp1_cm_घातer_on_regamma_lut(काष्ठा dpp *dpp_base,
				  bool घातer_on)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_SET(CM_MEM_PWR_CTRL, 0,
		RGAM_MEM_PWR_FORCE, घातer_on == true ? 0:1);

पूर्ण

व्योम dpp1_cm_program_regamma_lut(काष्ठा dpp *dpp_base,
				 स्थिर काष्ठा pwl_result_data *rgb,
				 uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t i;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_SEQ_START();

	क्रम (i = 0 ; i < num; i++) अणु
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].red_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].green_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].blue_reg);

		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].delta_red_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].delta_green_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].delta_blue_reg);

	पूर्ण

पूर्ण

व्योम dpp1_cm_configure_regamma_lut(
		काष्ठा dpp *dpp_base,
		bool is_ram_a)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_UPDATE(CM_RGAM_LUT_WRITE_EN_MASK,
			CM_RGAM_LUT_WRITE_EN_MASK, 7);
	REG_UPDATE(CM_RGAM_LUT_WRITE_EN_MASK,
			CM_RGAM_LUT_WRITE_SEL, is_ram_a == true ? 0:1);
	REG_SET(CM_RGAM_LUT_INDEX, 0, CM_RGAM_LUT_INDEX, 0);
पूर्ण

/*program re gamma RAM A*/
व्योम dpp1_cm_program_regamma_luta_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	काष्ठा xfer_func_reg gam_regs;

	dpp1_cm_get_reg_field(dpp, &gam_regs);

	gam_regs.start_cntl_b = REG(CM_RGAM_RAMA_START_CNTL_B);
	gam_regs.start_cntl_g = REG(CM_RGAM_RAMA_START_CNTL_G);
	gam_regs.start_cntl_r = REG(CM_RGAM_RAMA_START_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(CM_RGAM_RAMA_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(CM_RGAM_RAMA_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(CM_RGAM_RAMA_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(CM_RGAM_RAMA_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(CM_RGAM_RAMA_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(CM_RGAM_RAMA_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(CM_RGAM_RAMA_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(CM_RGAM_RAMA_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(CM_RGAM_RAMA_END_CNTL2_R);
	gam_regs.region_start = REG(CM_RGAM_RAMA_REGION_0_1);
	gam_regs.region_end = REG(CM_RGAM_RAMA_REGION_32_33);

	cm_helper_program_xfer_func(dpp->base.ctx, params, &gam_regs);

पूर्ण

/*program re gamma RAM B*/
व्योम dpp1_cm_program_regamma_lutb_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	काष्ठा xfer_func_reg gam_regs;

	dpp1_cm_get_reg_field(dpp, &gam_regs);

	gam_regs.start_cntl_b = REG(CM_RGAM_RAMB_START_CNTL_B);
	gam_regs.start_cntl_g = REG(CM_RGAM_RAMB_START_CNTL_G);
	gam_regs.start_cntl_r = REG(CM_RGAM_RAMB_START_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(CM_RGAM_RAMB_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(CM_RGAM_RAMB_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(CM_RGAM_RAMB_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(CM_RGAM_RAMB_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(CM_RGAM_RAMB_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(CM_RGAM_RAMB_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(CM_RGAM_RAMB_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(CM_RGAM_RAMB_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(CM_RGAM_RAMB_END_CNTL2_R);
	gam_regs.region_start = REG(CM_RGAM_RAMB_REGION_0_1);
	gam_regs.region_end = REG(CM_RGAM_RAMB_REGION_32_33);

	cm_helper_program_xfer_func(dpp->base.ctx, params, &gam_regs);
पूर्ण

व्योम dpp1_program_input_csc(
		काष्ठा dpp *dpp_base,
		क्रमागत dc_color_space color_space,
		क्रमागत dcn10_input_csc_select input_select,
		स्थिर काष्ठा out_csc_color_matrix *tbl_entry)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	पूर्णांक i;
	पूर्णांक arr_size = माप(dpp_input_csc_matrix)/माप(काष्ठा dpp_input_csc_matrix);
	स्थिर uपूर्णांक16_t *regval = शून्य;
	uपूर्णांक32_t cur_select = 0;
	क्रमागत dcn10_input_csc_select select;
	काष्ठा color_matrices_reg gam_regs;

	अगर (input_select == INPUT_CSC_SELECT_BYPASS) अणु
		REG_SET(CM_ICSC_CONTROL, 0, CM_ICSC_MODE, 0);
		वापस;
	पूर्ण

	अगर (tbl_entry == शून्य) अणु
		क्रम (i = 0; i < arr_size; i++)
			अगर (dpp_input_csc_matrix[i].color_space == color_space) अणु
				regval = dpp_input_csc_matrix[i].regval;
				अवरोध;
			पूर्ण

		अगर (regval == शून्य) अणु
			BREAK_TO_DEBUGGER();
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		regval = tbl_entry->regval;
	पूर्ण

	/* determine which CSC matrix (icsc or coma) we are using
	 * currently.  select the alternate set to द्विगुन buffer
	 * the CSC update so CSC is updated on frame boundary
	 */
	REG_SET(CM_TEST_DEBUG_INDEX, 0,
			CM_TEST_DEBUG_INDEX, 9);

	REG_GET(CM_TEST_DEBUG_DATA,
			CM_TEST_DEBUG_DATA_ID9_ICSC_MODE, &cur_select);

	अगर (cur_select != INPUT_CSC_SELECT_ICSC)
		select = INPUT_CSC_SELECT_ICSC;
	अन्यथा
		select = INPUT_CSC_SELECT_COMA;

	gam_regs.shअगरts.csc_c11 = dpp->tf_shअगरt->CM_ICSC_C11;
	gam_regs.masks.csc_c11  = dpp->tf_mask->CM_ICSC_C11;
	gam_regs.shअगरts.csc_c12 = dpp->tf_shअगरt->CM_ICSC_C12;
	gam_regs.masks.csc_c12 = dpp->tf_mask->CM_ICSC_C12;

	अगर (select == INPUT_CSC_SELECT_ICSC) अणु

		gam_regs.csc_c11_c12 = REG(CM_ICSC_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_ICSC_C33_C34);

	पूर्ण अन्यथा अणु

		gam_regs.csc_c11_c12 = REG(CM_COMA_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_COMA_C33_C34);

	पूर्ण

	cm_helper_program_color_matrices(
			dpp->base.ctx,
			regval,
			&gam_regs);

	REG_SET(CM_ICSC_CONTROL, 0,
				CM_ICSC_MODE, select);
पूर्ण

//keep here क्रम now, decide multi dce support later
व्योम dpp1_program_bias_and_scale(
	काष्ठा dpp *dpp_base,
	काष्ठा dc_bias_and_scale *params)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_SET_2(CM_BNS_VALUES_R, 0,
		CM_BNS_SCALE_R, params->scale_red,
		CM_BNS_BIAS_R, params->bias_red);

	REG_SET_2(CM_BNS_VALUES_G, 0,
		CM_BNS_SCALE_G, params->scale_green,
		CM_BNS_BIAS_G, params->bias_green);

	REG_SET_2(CM_BNS_VALUES_B, 0,
		CM_BNS_SCALE_B, params->scale_blue,
		CM_BNS_BIAS_B, params->bias_blue);

पूर्ण

/*program de gamma RAM B*/
व्योम dpp1_program_degamma_lutb_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	काष्ठा xfer_func_reg gam_regs;

	dpp1_cm_get_degamma_reg_field(dpp, &gam_regs);

	gam_regs.start_cntl_b = REG(CM_DGAM_RAMB_START_CNTL_B);
	gam_regs.start_cntl_g = REG(CM_DGAM_RAMB_START_CNTL_G);
	gam_regs.start_cntl_r = REG(CM_DGAM_RAMB_START_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(CM_DGAM_RAMB_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(CM_DGAM_RAMB_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(CM_DGAM_RAMB_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(CM_DGAM_RAMB_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(CM_DGAM_RAMB_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(CM_DGAM_RAMB_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(CM_DGAM_RAMB_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(CM_DGAM_RAMB_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(CM_DGAM_RAMB_END_CNTL2_R);
	gam_regs.region_start = REG(CM_DGAM_RAMB_REGION_0_1);
	gam_regs.region_end = REG(CM_DGAM_RAMB_REGION_14_15);


	cm_helper_program_xfer_func(dpp->base.ctx, params, &gam_regs);
पूर्ण

/*program de gamma RAM A*/
व्योम dpp1_program_degamma_luta_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	काष्ठा xfer_func_reg gam_regs;

	dpp1_cm_get_degamma_reg_field(dpp, &gam_regs);

	gam_regs.start_cntl_b = REG(CM_DGAM_RAMA_START_CNTL_B);
	gam_regs.start_cntl_g = REG(CM_DGAM_RAMA_START_CNTL_G);
	gam_regs.start_cntl_r = REG(CM_DGAM_RAMA_START_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(CM_DGAM_RAMA_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(CM_DGAM_RAMA_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(CM_DGAM_RAMA_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(CM_DGAM_RAMA_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(CM_DGAM_RAMA_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(CM_DGAM_RAMA_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(CM_DGAM_RAMA_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(CM_DGAM_RAMA_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(CM_DGAM_RAMA_END_CNTL2_R);
	gam_regs.region_start = REG(CM_DGAM_RAMA_REGION_0_1);
	gam_regs.region_end = REG(CM_DGAM_RAMA_REGION_14_15);

	cm_helper_program_xfer_func(dpp->base.ctx, params, &gam_regs);
पूर्ण

व्योम dpp1_घातer_on_degamma_lut(
		काष्ठा dpp *dpp_base,
	bool घातer_on)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_SET(CM_MEM_PWR_CTRL, 0,
			SHARED_MEM_PWR_DIS, घातer_on ? 0:1);

पूर्ण

अटल व्योम dpp1_enable_cm_block(
		काष्ठा dpp *dpp_base)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_UPDATE(CM_CMOUT_CONTROL, CM_CMOUT_ROUND_TRUNC_MODE, 8);
	REG_UPDATE(CM_CONTROL, CM_BYPASS_EN, 0);
पूर्ण

व्योम dpp1_set_degamma(
		काष्ठा dpp *dpp_base,
		क्रमागत ipp_degamma_mode mode)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	dpp1_enable_cm_block(dpp_base);

	चयन (mode) अणु
	हाल IPP_DEGAMMA_MODE_BYPASS:
		/* Setting de gamma bypass क्रम now */
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 0);
		अवरोध;
	हाल IPP_DEGAMMA_MODE_HW_sRGB:
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 1);
		अवरोध;
	हाल IPP_DEGAMMA_MODE_HW_xvYCC:
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 2);
			अवरोध;
	हाल IPP_DEGAMMA_MODE_USER_PWL:
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 3);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	REG_SEQ_SUBMIT();
	REG_SEQ_WAIT_DONE();
पूर्ण

व्योम dpp1_degamma_ram_select(
		काष्ठा dpp *dpp_base,
							bool use_ram_a)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	अगर (use_ram_a)
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 3);
	अन्यथा
		REG_UPDATE(CM_DGAM_CONTROL, CM_DGAM_LUT_MODE, 4);

पूर्ण

अटल bool dpp1_degamma_ram_inuse(
		काष्ठा dpp *dpp_base,
							bool *ram_a_inuse)
अणु
	bool ret = false;
	uपूर्णांक32_t status_reg = 0;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_GET(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_DGAM_CONFIG_STATUS,
			&status_reg);

	अगर (status_reg == 9) अणु
		*ram_a_inuse = true;
		ret = true;
	पूर्ण अन्यथा अगर (status_reg == 10) अणु
		*ram_a_inuse = false;
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण

व्योम dpp1_program_degamma_lut(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_result_data *rgb,
		uपूर्णांक32_t num,
		bool is_ram_a)
अणु
	uपूर्णांक32_t i;

	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_HOST_EN, 0);
	REG_UPDATE(CM_DGAM_LUT_WRITE_EN_MASK,
				   CM_DGAM_LUT_WRITE_EN_MASK, 7);
	REG_UPDATE(CM_DGAM_LUT_WRITE_EN_MASK, CM_DGAM_LUT_WRITE_SEL,
					is_ram_a == true ? 0:1);

	REG_SET(CM_DGAM_LUT_INDEX, 0, CM_DGAM_LUT_INDEX, 0);
	क्रम (i = 0 ; i < num; i++) अणु
		REG_SET(CM_DGAM_LUT_DATA, 0, CM_DGAM_LUT_DATA, rgb[i].red_reg);
		REG_SET(CM_DGAM_LUT_DATA, 0, CM_DGAM_LUT_DATA, rgb[i].green_reg);
		REG_SET(CM_DGAM_LUT_DATA, 0, CM_DGAM_LUT_DATA, rgb[i].blue_reg);

		REG_SET(CM_DGAM_LUT_DATA, 0,
				CM_DGAM_LUT_DATA, rgb[i].delta_red_reg);
		REG_SET(CM_DGAM_LUT_DATA, 0,
				CM_DGAM_LUT_DATA, rgb[i].delta_green_reg);
		REG_SET(CM_DGAM_LUT_DATA, 0,
				CM_DGAM_LUT_DATA, rgb[i].delta_blue_reg);
	पूर्ण
पूर्ण

व्योम dpp1_set_degamma_pwl(काष्ठा dpp *dpp_base,
								 स्थिर काष्ठा pwl_params *params)
अणु
	bool is_ram_a = true;

	dpp1_घातer_on_degamma_lut(dpp_base, true);
	dpp1_enable_cm_block(dpp_base);
	dpp1_degamma_ram_inuse(dpp_base, &is_ram_a);
	अगर (is_ram_a == true)
		dpp1_program_degamma_lutb_settings(dpp_base, params);
	अन्यथा
		dpp1_program_degamma_luta_settings(dpp_base, params);

	dpp1_program_degamma_lut(dpp_base, params->rgb_resulted,
							params->hw_poपूर्णांकs_num, !is_ram_a);
	dpp1_degamma_ram_select(dpp_base, !is_ram_a);
पूर्ण

व्योम dpp1_full_bypass(काष्ठा dpp *dpp_base)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	/* Input pixel क्रमmat: ARGB8888 */
	REG_SET(CNVC_SURFACE_PIXEL_FORMAT, 0,
			CNVC_SURFACE_PIXEL_FORMAT, 0x8);

	/* Zero expansion */
	REG_SET_3(FORMAT_CONTROL, 0,
			CNVC_BYPASS, 0,
			FORMAT_CONTROL__ALPHA_EN, 0,
			FORMAT_EXPANSION_MODE, 0);

	/* COLOR_KEYER_CONTROL.COLOR_KEYER_EN = 0 this should be शेष */
	अगर (dpp->tf_mask->CM_BYPASS_EN)
		REG_SET(CM_CONTROL, 0, CM_BYPASS_EN, 1);
	अन्यथा
		REG_SET(CM_CONTROL, 0, CM_BYPASS, 1);

	/* Setting degamma bypass क्रम now */
	REG_SET(CM_DGAM_CONTROL, 0, CM_DGAM_LUT_MODE, 0);
पूर्ण

अटल bool dpp1_ingamma_ram_inuse(काष्ठा dpp *dpp_base,
							bool *ram_a_inuse)
अणु
	bool in_use = false;
	uपूर्णांक32_t status_reg = 0;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_GET(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_DGAM_CONFIG_STATUS,
				&status_reg);

	// 1 => IGAM_RAMA, 3 => IGAM_RAMA & DGAM_ROMA, 4 => IGAM_RAMA & DGAM_ROMB
	अगर (status_reg == 1 || status_reg == 3 || status_reg == 4) अणु
		*ram_a_inuse = true;
		in_use = true;
	// 2 => IGAM_RAMB, 5 => IGAM_RAMB & DGAM_ROMA, 6 => IGAM_RAMB & DGAM_ROMB
	पूर्ण अन्यथा अगर (status_reg == 2 || status_reg == 5 || status_reg == 6) अणु
		*ram_a_inuse = false;
		in_use = true;
	पूर्ण
	वापस in_use;
पूर्ण

/*
 * Input gamma LUT currently supports 256 values only. This means input color
 * can have a maximum of 8 bits per channel (= 256 possible values) in order to
 * have a one-to-one mapping with the LUT. Truncation will occur with color
 * values greater than 8 bits.
 *
 * In the future, this function should support additional input gamma methods,
 * such as piecewise linear mapping, and input gamma bypass.
 */
व्योम dpp1_program_input_lut(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा dc_gamma *gamma)
अणु
	पूर्णांक i;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	bool rama_occupied = false;
	uपूर्णांक32_t ram_num;
	// Power on LUT memory.
	REG_SET(CM_MEM_PWR_CTRL, 0, SHARED_MEM_PWR_DIS, 1);
	dpp1_enable_cm_block(dpp_base);
	// Determine whether to use RAM A or RAM B
	dpp1_ingamma_ram_inuse(dpp_base, &rama_occupied);
	अगर (!rama_occupied)
		REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_SEL, 0);
	अन्यथा
		REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_SEL, 1);
	// RW mode is 256-entry LUT
	REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_RW_MODE, 0);
	// IGAM Input क्रमmat should be 8 bits per channel.
	REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_INPUT_FORMAT, 0);
	// Do not mask any R,G,B values
	REG_UPDATE(CM_IGAM_LUT_RW_CONTROL, CM_IGAM_LUT_WRITE_EN_MASK, 7);
	// LUT-256, अचिन्हित, पूर्णांकeger, new u0.12 क्रमmat
	REG_UPDATE_3(
		CM_IGAM_CONTROL,
		CM_IGAM_LUT_FORMAT_R, 3,
		CM_IGAM_LUT_FORMAT_G, 3,
		CM_IGAM_LUT_FORMAT_B, 3);
	// Start at index 0 of IGAM LUT
	REG_UPDATE(CM_IGAM_LUT_RW_INDEX, CM_IGAM_LUT_RW_INDEX, 0);
	क्रम (i = 0; i < gamma->num_entries; i++) अणु
		REG_SET(CM_IGAM_LUT_SEQ_COLOR, 0, CM_IGAM_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.red[i]));
		REG_SET(CM_IGAM_LUT_SEQ_COLOR, 0, CM_IGAM_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.green[i]));
		REG_SET(CM_IGAM_LUT_SEQ_COLOR, 0, CM_IGAM_LUT_SEQ_COLOR,
				dc_fixpt_round(
					gamma->entries.blue[i]));
	पूर्ण
	// Power off LUT memory
	REG_SET(CM_MEM_PWR_CTRL, 0, SHARED_MEM_PWR_DIS, 0);
	// Enable IGAM LUT on ram we just wrote to. 2 => RAMA, 3 => RAMB
	REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, rama_occupied ? 3 : 2);
	REG_GET(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, &ram_num);
पूर्ण

व्योम dpp1_set_hdr_multiplier(
		काष्ठा dpp *dpp_base,
		uपूर्णांक32_t multiplier)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_UPDATE(CM_HDR_MULT_COEF, CM_HDR_MULT_COEF, multiplier);
पूर्ण
