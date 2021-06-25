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

#समावेश "reg_helper.h"
#समावेश "fixed31_32.h"
#समावेश "resource.h"
#समावेश "basics/conversion.h"
#समावेश "dwb.h"
#समावेश "dcn30_dwb.h"
#समावेश "dcn30_cm_common.h"
#समावेश "dcn10/dcn10_cm_common.h"


#घोषणा REG(reg)\
	dwbc30->dwbc_regs->reg

#घोषणा CTX \
	dwbc30->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dwbc30->dwbc_shअगरt->field_name, dwbc30->dwbc_mask->field_name

#घोषणा TO_DCN30_DWBC(dwbc_base) \
	container_of(dwbc_base, काष्ठा dcn30_dwbc, base)

अटल व्योम dwb3_get_reg_field_ogam(काष्ठा dcn30_dwbc *dwbc30,
	काष्ठा dcn3_xfer_func_reg *reg)
अणु
	reg->shअगरts.exp_region0_lut_offset = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shअगरts.exp_region0_num_segments = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shअगरts.exp_region1_lut_offset = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shअगरts.exp_region1_num_segments = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;

	reg->shअगरts.field_region_end = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION_END_B;
	reg->masks.field_region_end = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION_END_B;
	reg->shअगरts.field_region_end_slope = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->shअगरts.field_region_end_base = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->shअगरts.field_region_linear_slope = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION_START_SLOPE_B;
	reg->masks.field_region_linear_slope = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION_START_SLOPE_B;
	reg->masks.field_offset = dwbc30->dwbc_mask->DWB_OGAM_RAMA_OFFSET_B;
	reg->shअगरts.field_offset = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_OFFSET_B;
	reg->shअगरts.exp_region_start = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION_START_B;
	reg->masks.exp_region_start = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION_START_B;
	reg->shअगरts.exp_resion_start_segment = dwbc30->dwbc_shअगरt->DWB_OGAM_RAMA_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = dwbc30->dwbc_mask->DWB_OGAM_RAMA_EXP_REGION_START_SEGMENT_B;
पूर्ण

/*program dwb ogam RAM A*/
अटल व्योम dwb3_program_ogam_luta_settings(
	काष्ठा dcn30_dwbc *dwbc30,
	स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn3_xfer_func_reg gam_regs;

	dwb3_get_reg_field_ogam(dwbc30, &gam_regs);

	gam_regs.start_cntl_b = REG(DWB_OGAM_RAMA_START_CNTL_B);
	gam_regs.start_cntl_g = REG(DWB_OGAM_RAMA_START_CNTL_G);
	gam_regs.start_cntl_r = REG(DWB_OGAM_RAMA_START_CNTL_R);
	gam_regs.start_base_cntl_b = REG(DWB_OGAM_RAMA_START_BASE_CNTL_B);
	gam_regs.start_base_cntl_g = REG(DWB_OGAM_RAMA_START_BASE_CNTL_G);
	gam_regs.start_base_cntl_r = REG(DWB_OGAM_RAMA_START_BASE_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(DWB_OGAM_RAMA_START_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(DWB_OGAM_RAMA_START_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(DWB_OGAM_RAMA_START_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(DWB_OGAM_RAMA_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(DWB_OGAM_RAMA_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(DWB_OGAM_RAMA_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(DWB_OGAM_RAMA_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(DWB_OGAM_RAMA_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(DWB_OGAM_RAMA_END_CNTL2_R);
	gam_regs.offset_b = REG(DWB_OGAM_RAMA_OFFSET_B);
	gam_regs.offset_g = REG(DWB_OGAM_RAMA_OFFSET_G);
	gam_regs.offset_r = REG(DWB_OGAM_RAMA_OFFSET_R);
	gam_regs.region_start = REG(DWB_OGAM_RAMA_REGION_0_1);
	gam_regs.region_end = REG(DWB_OGAM_RAMA_REGION_32_33);
	/*toकरो*/
	cm_helper_program_gamcor_xfer_func(dwbc30->base.ctx, params, &gam_regs);
पूर्ण

/*program dwb ogam RAM B*/
अटल व्योम dwb3_program_ogam_lutb_settings(
	काष्ठा dcn30_dwbc *dwbc30,
	स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn3_xfer_func_reg gam_regs;

	dwb3_get_reg_field_ogam(dwbc30, &gam_regs);

	gam_regs.start_cntl_b = REG(DWB_OGAM_RAMB_START_CNTL_B);
	gam_regs.start_cntl_g = REG(DWB_OGAM_RAMB_START_CNTL_G);
	gam_regs.start_cntl_r = REG(DWB_OGAM_RAMB_START_CNTL_R);
	gam_regs.start_base_cntl_b = REG(DWB_OGAM_RAMB_START_BASE_CNTL_B);
	gam_regs.start_base_cntl_g = REG(DWB_OGAM_RAMB_START_BASE_CNTL_G);
	gam_regs.start_base_cntl_r = REG(DWB_OGAM_RAMB_START_BASE_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(DWB_OGAM_RAMB_START_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(DWB_OGAM_RAMB_START_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(DWB_OGAM_RAMB_START_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(DWB_OGAM_RAMB_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(DWB_OGAM_RAMB_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(DWB_OGAM_RAMB_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(DWB_OGAM_RAMB_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(DWB_OGAM_RAMB_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(DWB_OGAM_RAMB_END_CNTL2_R);
	gam_regs.offset_b = REG(DWB_OGAM_RAMB_OFFSET_B);
	gam_regs.offset_g = REG(DWB_OGAM_RAMB_OFFSET_G);
	gam_regs.offset_r = REG(DWB_OGAM_RAMB_OFFSET_R);
	gam_regs.region_start = REG(DWB_OGAM_RAMB_REGION_0_1);
	gam_regs.region_end = REG(DWB_OGAM_RAMB_REGION_32_33);

	cm_helper_program_gamcor_xfer_func(dwbc30->base.ctx, params, &gam_regs);
पूर्ण

अटल क्रमागत dc_lut_mode dwb3_get_ogam_current(
	काष्ठा dcn30_dwbc *dwbc30)
अणु
	क्रमागत dc_lut_mode mode;
	uपूर्णांक32_t state_mode;
	uपूर्णांक32_t ram_select;

	REG_GET(DWB_OGAM_CONTROL,
		DWB_OGAM_MODE, &state_mode);
	REG_GET(DWB_OGAM_CONTROL,
		DWB_OGAM_SELECT, &ram_select);

	अगर (state_mode == 0) अणु
		mode = LUT_BYPASS;
	पूर्ण अन्यथा अगर (state_mode == 2) अणु
		अगर (ram_select == 0)
			mode = LUT_RAM_A;
		अन्यथा
			mode = LUT_RAM_B;
	पूर्ण अन्यथा अणु
		// Reserved value
		mode = LUT_BYPASS;
		BREAK_TO_DEBUGGER();
		वापस mode;
	पूर्ण
	वापस mode;
पूर्ण

अटल व्योम dwb3_configure_ogam_lut(
	काष्ठा dcn30_dwbc *dwbc30,
	bool is_ram_a)
अणु
	REG_UPDATE(DWB_OGAM_LUT_CONTROL,
		DWB_OGAM_LUT_READ_COLOR_SEL, 7);
	REG_UPDATE(DWB_OGAM_CONTROL,
		DWB_OGAM_SELECT, is_ram_a == true ? 0 : 1);
	REG_SET(DWB_OGAM_LUT_INDEX, 0, DWB_OGAM_LUT_INDEX, 0);
पूर्ण

अटल व्योम dwb3_program_ogam_pwl(काष्ठा dcn30_dwbc *dwbc30,
	स्थिर काष्ठा pwl_result_data *rgb,
	uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t i;

    // triple base implementation
	क्रम (i = 0; i < num/2; i++) अणु
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+0].red_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+0].green_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+0].blue_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+1].red_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+1].green_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+1].blue_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+2].red_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+2].green_reg);
		REG_SET(DWB_OGAM_LUT_DATA, 0, DWB_OGAM_LUT_DATA, rgb[2*i+2].blue_reg);
	पूर्ण
पूर्ण

अटल bool dwb3_program_ogam_lut(
	काष्ठा dcn30_dwbc *dwbc30,
	स्थिर काष्ठा pwl_params *params)
अणु
	क्रमागत dc_lut_mode current_mode;
	क्रमागत dc_lut_mode next_mode;

	अगर (params == शून्य) अणु
		REG_SET(DWB_OGAM_CONTROL, 0, DWB_OGAM_MODE, 0);
		वापस false;
	पूर्ण

	current_mode = dwb3_get_ogam_current(dwbc30);
	अगर (current_mode == LUT_BYPASS || current_mode == LUT_RAM_A)
		next_mode = LUT_RAM_B;
	अन्यथा
		next_mode = LUT_RAM_A;

	dwb3_configure_ogam_lut(dwbc30, next_mode == LUT_RAM_A);

	अगर (next_mode == LUT_RAM_A)
		dwb3_program_ogam_luta_settings(dwbc30, params);
	अन्यथा
		dwb3_program_ogam_lutb_settings(dwbc30, params);

	dwb3_program_ogam_pwl(
		dwbc30, params->rgb_resulted, params->hw_poपूर्णांकs_num);

	REG_SET(DWB_OGAM_CONTROL, 0, DWB_OGAM_MODE, 2);
	REG_SET(DWB_OGAM_CONTROL, 0, DWB_OGAM_SELECT, next_mode == LUT_RAM_A ? 0 : 1);

	वापस true;
पूर्ण

bool dwb3_ogam_set_input_transfer_func(
	काष्ठा dwbc *dwbc,
	स्थिर काष्ठा dc_transfer_func *in_transfer_func_dwb_ogam)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);
	bool result = false;
	काष्ठा pwl_params *dwb_ogam_lut = शून्य;

	अगर (in_transfer_func_dwb_ogam == शून्य)
		वापस result;

	dwb_ogam_lut = kzalloc(माप(*dwb_ogam_lut), GFP_KERNEL);

	अगर (dwb_ogam_lut) अणु
		cm_helper_translate_curve_to_hw_क्रमmat(
			in_transfer_func_dwb_ogam,
			dwb_ogam_lut, false);

		result = dwb3_program_ogam_lut(
			dwbc30,
			dwb_ogam_lut);
		kमुक्त(dwb_ogam_lut);
		dwb_ogam_lut = शून्य;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम dwb3_program_gamut_remap(
		काष्ठा dwbc *dwbc,
		स्थिर uपूर्णांक16_t *regval,
		क्रमागत cm_gamut_coef_क्रमmat coef_क्रमmat,
		क्रमागत cm_gamut_remap_select select)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	काष्ठा color_matrices_reg gam_regs;

	REG_UPDATE(DWB_GAMUT_REMAP_COEF_FORMAT, DWB_GAMUT_REMAP_COEF_FORMAT, coef_क्रमmat);

	अगर (regval == शून्य || select == CM_GAMUT_REMAP_MODE_BYPASS) अणु
		REG_SET(DWB_GAMUT_REMAP_MODE, 0,
				DWB_GAMUT_REMAP_MODE, 0);
		वापस;
	पूर्ण

	चयन (select) अणु
	हाल CM_GAMUT_REMAP_MODE_RAMA_COEFF:
		gam_regs.csc_c11_c12 = REG(DWB_GAMUT_REMAPA_C11_C12);
		gam_regs.csc_c33_c34 = REG(DWB_GAMUT_REMAPA_C33_C34);

		cm_helper_program_color_matrices(
				dwbc30->base.ctx,
				regval,
				&gam_regs);
		अवरोध;
	हाल CM_GAMUT_REMAP_MODE_RAMB_COEFF:
		gam_regs.csc_c11_c12 = REG(DWB_GAMUT_REMAPB_C11_C12);
		gam_regs.csc_c33_c34 = REG(DWB_GAMUT_REMAPB_C33_C34);

		cm_helper_program_color_matrices(
				dwbc30->base.ctx,
				regval,
				&gam_regs);
		अवरोध;
	हाल CM_GAMUT_REMAP_MODE_RESERVED:
		/* should never happen, bug */
		BREAK_TO_DEBUGGER();
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	REG_SET(DWB_GAMUT_REMAP_MODE, 0,
			DWB_GAMUT_REMAP_MODE, select);

पूर्ण

व्योम dwb3_set_gamut_remap(
	काष्ठा dwbc *dwbc,
	स्थिर काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);
	काष्ठा cm_grph_csc_adjusपंचांगent adjust = params->csc_params;
	पूर्णांक i = 0;

	अगर (adjust.gamut_adjust_type != CM_GAMUT_ADJUST_TYPE_SW) अणु
		/* Bypass अगर type is bypass or hw */
		dwb3_program_gamut_remap(dwbc, शून्य, adjust.gamut_coef_क्रमmat, CM_GAMUT_REMAP_MODE_BYPASS);
	पूर्ण अन्यथा अणु
		काष्ठा fixed31_32 arr_matrix[12];
		uपूर्णांक16_t arr_reg_val[12];
		अचिन्हित पूर्णांक current_mode;

		क्रम (i = 0; i < 12; i++)
			arr_matrix[i] = adjust.temperature_matrix[i];

		convert_भग्न_matrix(arr_reg_val, arr_matrix, 12);

		REG_GET(DWB_GAMUT_REMAP_MODE, DWB_GAMUT_REMAP_MODE_CURRENT, &current_mode);

		अगर (current_mode == CM_GAMUT_REMAP_MODE_RAMA_COEFF) अणु
			dwb3_program_gamut_remap(dwbc, arr_reg_val,
					adjust.gamut_coef_क्रमmat, CM_GAMUT_REMAP_MODE_RAMB_COEFF);
		पूर्ण अन्यथा अणु
			dwb3_program_gamut_remap(dwbc, arr_reg_val,
					adjust.gamut_coef_क्रमmat, CM_GAMUT_REMAP_MODE_RAMA_COEFF);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dwb3_program_hdr_mult(
	काष्ठा dwbc *dwbc,
	स्थिर काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	REG_UPDATE(DWB_HDR_MULT_COEF, DWB_HDR_MULT_COEF, params->hdr_mult);
पूर्ण
