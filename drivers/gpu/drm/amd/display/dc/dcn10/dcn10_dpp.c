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

क्रमागत pixel_क्रमmat_description अणु
	PIXEL_FORMAT_FIXED = 0,
	PIXEL_FORMAT_FIXED16,
	PIXEL_FORMAT_FLOAT

पूर्ण;

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

व्योम dpp_पढ़ो_state(काष्ठा dpp *dpp_base,
		काष्ठा dcn_dpp_state *s)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_GET(DPP_CONTROL,
			DPP_CLOCK_ENABLE, &s->is_enabled);
	REG_GET(CM_IGAM_CONTROL,
			CM_IGAM_LUT_MODE, &s->igam_lut_mode);
	REG_GET(CM_IGAM_CONTROL,
			CM_IGAM_INPUT_FORMAT, &s->igam_input_क्रमmat);
	REG_GET(CM_DGAM_CONTROL,
			CM_DGAM_LUT_MODE, &s->dgam_lut_mode);
	REG_GET(CM_RGAM_CONTROL,
			CM_RGAM_LUT_MODE, &s->rgam_lut_mode);
	REG_GET(CM_GAMUT_REMAP_CONTROL,
			CM_GAMUT_REMAP_MODE, &s->gamut_remap_mode);

	अगर (s->gamut_remap_mode) अणु
		s->gamut_remap_c11_c12 = REG_READ(CM_GAMUT_REMAP_C11_C12);
		s->gamut_remap_c13_c14 = REG_READ(CM_GAMUT_REMAP_C13_C14);
		s->gamut_remap_c21_c22 = REG_READ(CM_GAMUT_REMAP_C21_C22);
		s->gamut_remap_c23_c24 = REG_READ(CM_GAMUT_REMAP_C23_C24);
		s->gamut_remap_c31_c32 = REG_READ(CM_GAMUT_REMAP_C31_C32);
		s->gamut_remap_c33_c34 = REG_READ(CM_GAMUT_REMAP_C33_C34);
	पूर्ण
पूर्ण

/* Program gamut remap in bypass mode */
व्योम dpp_set_gamut_remap_bypass(काष्ठा dcn10_dpp *dpp)
अणु
	REG_SET(CM_GAMUT_REMAP_CONTROL, 0,
			CM_GAMUT_REMAP_MODE, 0);
	/* Gamut remap in bypass */
पूर्ण

#घोषणा IDENTITY_RATIO(ratio) (dc_fixpt_u2d19(ratio) == (1 << 19))

bool dpp1_get_optimal_number_of_taps(
		काष्ठा dpp *dpp,
		काष्ठा scaler_data *scl_data,
		स्थिर काष्ठा scaling_taps *in_taps)
अणु
	/* Some ASICs करोes not support  FP16 scaling, so we reject modes require this*/
	अगर (scl_data->क्रमmat == PIXEL_FORMAT_FP16 &&
		dpp->caps->dscl_data_proc_क्रमmat == DSCL_DATA_PRCESSING_FIXED_FORMAT &&
		scl_data->ratios.horz.value != dc_fixpt_one.value &&
		scl_data->ratios.vert.value != dc_fixpt_one.value)
		वापस false;

	अगर (scl_data->viewport.width > scl_data->h_active &&
		dpp->ctx->dc->debug.max_करोwnscale_src_width != 0 &&
		scl_data->viewport.width > dpp->ctx->dc->debug.max_करोwnscale_src_width)
		वापस false;

	/* TODO: add lb check */

	/* No support क्रम programming ratio of 4, drop to 3.99999.. */
	अगर (scl_data->ratios.horz.value == (4ll << 32))
		scl_data->ratios.horz.value--;
	अगर (scl_data->ratios.vert.value == (4ll << 32))
		scl_data->ratios.vert.value--;
	अगर (scl_data->ratios.horz_c.value == (4ll << 32))
		scl_data->ratios.horz_c.value--;
	अगर (scl_data->ratios.vert_c.value == (4ll << 32))
		scl_data->ratios.vert_c.value--;

	/* Set शेष taps अगर none are provided */
	अगर (in_taps->h_taps == 0)
		scl_data->taps.h_taps = 4;
	अन्यथा
		scl_data->taps.h_taps = in_taps->h_taps;
	अगर (in_taps->v_taps == 0)
		scl_data->taps.v_taps = 4;
	अन्यथा
		scl_data->taps.v_taps = in_taps->v_taps;
	अगर (in_taps->v_taps_c == 0)
		scl_data->taps.v_taps_c = 2;
	अन्यथा
		scl_data->taps.v_taps_c = in_taps->v_taps_c;
	अगर (in_taps->h_taps_c == 0)
		scl_data->taps.h_taps_c = 2;
	/* Only 1 and even h_taps_c are supported by hw */
	अन्यथा अगर ((in_taps->h_taps_c % 2) != 0 && in_taps->h_taps_c != 1)
		scl_data->taps.h_taps_c = in_taps->h_taps_c - 1;
	अन्यथा
		scl_data->taps.h_taps_c = in_taps->h_taps_c;

	अगर (!dpp->ctx->dc->debug.always_scale) अणु
		अगर (IDENTITY_RATIO(scl_data->ratios.horz))
			scl_data->taps.h_taps = 1;
		अगर (IDENTITY_RATIO(scl_data->ratios.vert))
			scl_data->taps.v_taps = 1;
		अगर (IDENTITY_RATIO(scl_data->ratios.horz_c))
			scl_data->taps.h_taps_c = 1;
		अगर (IDENTITY_RATIO(scl_data->ratios.vert_c))
			scl_data->taps.v_taps_c = 1;
	पूर्ण

	वापस true;
पूर्ण

व्योम dpp_reset(काष्ठा dpp *dpp_base)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	dpp->filter_h_c = शून्य;
	dpp->filter_v_c = शून्य;
	dpp->filter_h = शून्य;
	dpp->filter_v = शून्य;

	स_रखो(&dpp->scl_data, 0, माप(dpp->scl_data));
	स_रखो(&dpp->pwl_data, 0, माप(dpp->pwl_data));
पूर्ण



अटल व्योम dpp1_cm_set_regamma_pwl(
	काष्ठा dpp *dpp_base, स्थिर काष्ठा pwl_params *params, क्रमागत opp_regamma mode)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	uपूर्णांक32_t re_mode = 0;

	चयन (mode) अणु
	हाल OPP_REGAMMA_BYPASS:
		re_mode = 0;
		अवरोध;
	हाल OPP_REGAMMA_SRGB:
		re_mode = 1;
		अवरोध;
	हाल OPP_REGAMMA_XVYCC:
		re_mode = 2;
		अवरोध;
	हाल OPP_REGAMMA_USER:
		re_mode = dpp->is_ग_लिखो_to_ram_a_safe ? 4 : 3;
		अगर (स_भेद(&dpp->pwl_data, params, माप(*params)) == 0)
			अवरोध;

		dpp1_cm_घातer_on_regamma_lut(dpp_base, true);
		dpp1_cm_configure_regamma_lut(dpp_base, dpp->is_ग_लिखो_to_ram_a_safe);

		अगर (dpp->is_ग_लिखो_to_ram_a_safe)
			dpp1_cm_program_regamma_luta_settings(dpp_base, params);
		अन्यथा
			dpp1_cm_program_regamma_lutb_settings(dpp_base, params);

		dpp1_cm_program_regamma_lut(dpp_base, params->rgb_resulted,
					    params->hw_poपूर्णांकs_num);
		dpp->pwl_data = *params;

		re_mode = dpp->is_ग_लिखो_to_ram_a_safe ? 3 : 4;
		dpp->is_ग_लिखो_to_ram_a_safe = !dpp->is_ग_लिखो_to_ram_a_safe;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	REG_SET(CM_RGAM_CONTROL, 0, CM_RGAM_LUT_MODE, re_mode);
पूर्ण

अटल व्योम dpp1_setup_क्रमmat_flags(क्रमागत surface_pixel_क्रमmat input_क्रमmat,\
						क्रमागत pixel_क्रमmat_description *fmt)
अणु

	अगर (input_क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F ||
		input_क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F)
		*fmt = PIXEL_FORMAT_FLOAT;
	अन्यथा अगर (input_क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616)
		*fmt = PIXEL_FORMAT_FIXED16;
	अन्यथा
		*fmt = PIXEL_FORMAT_FIXED;
पूर्ण

अटल व्योम dpp1_set_degamma_क्रमmat_भग्न(
		काष्ठा dpp *dpp_base,
		bool is_भग्न)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	अगर (is_भग्न) अणु
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_INPUT_FORMAT, 3);
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, 1);
	पूर्ण अन्यथा अणु
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_INPUT_FORMAT, 2);
		REG_UPDATE(CM_IGAM_CONTROL, CM_IGAM_LUT_MODE, 0);
	पूर्ण
पूर्ण

व्योम dpp1_cnv_setup (
		काष्ठा dpp *dpp_base,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		क्रमागत expansion_mode mode,
		काष्ठा dc_csc_transक्रमm input_csc_color_matrix,
		क्रमागत dc_color_space input_color_space,
		काष्ठा cnv_alpha_2bit_lut *alpha_2bit_lut)
अणु
	uपूर्णांक32_t pixel_क्रमmat;
	uपूर्णांक32_t alpha_en;
	क्रमागत pixel_क्रमmat_description fmt ;
	क्रमागत dc_color_space color_space;
	क्रमागत dcn10_input_csc_select select;
	bool is_भग्न;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	bool क्रमce_disable_cursor = false;
	काष्ठा out_csc_color_matrix tbl_entry;
	पूर्णांक i = 0;

	dpp1_setup_क्रमmat_flags(क्रमmat, &fmt);
	alpha_en = 1;
	pixel_क्रमmat = 0;
	color_space = COLOR_SPACE_SRGB;
	select = INPUT_CSC_SELECT_BYPASS;
	is_भग्न = false;

	चयन (fmt) अणु
	हाल PIXEL_FORMAT_FIXED:
	हाल PIXEL_FORMAT_FIXED16:
	/*when output is भग्न then FORMAT_CONTROL__OUTPUT_FP=1*/
		REG_SET_3(FORMAT_CONTROL, 0,
			CNVC_BYPASS, 0,
			FORMAT_EXPANSION_MODE, mode,
			OUTPUT_FP, 0);
		अवरोध;
	हाल PIXEL_FORMAT_FLOAT:
		REG_SET_3(FORMAT_CONTROL, 0,
			CNVC_BYPASS, 0,
			FORMAT_EXPANSION_MODE, mode,
			OUTPUT_FP, 1);
		is_भग्न = true;
		अवरोध;
	शेष:

		अवरोध;
	पूर्ण

	dpp1_set_degamma_क्रमmat_भग्न(dpp_base, is_भग्न);

	चयन (क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		pixel_क्रमmat = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		pixel_क्रमmat = 3;
		alpha_en = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		pixel_क्रमmat = 8;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		pixel_क्रमmat = 10;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
		क्रमce_disable_cursor = false;
		pixel_क्रमmat = 65;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		क्रमce_disable_cursor = true;
		pixel_क्रमmat = 64;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
		क्रमce_disable_cursor = true;
		pixel_क्रमmat = 67;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		क्रमce_disable_cursor = true;
		pixel_क्रमmat = 66;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		pixel_क्रमmat = 22;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
		pixel_क्रमmat = 24;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		pixel_क्रमmat = 25;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Set शेष color space based on क्रमmat अगर none is given. */
	color_space = input_color_space ? input_color_space : color_space;

	REG_SET(CNVC_SURFACE_PIXEL_FORMAT, 0,
			CNVC_SURFACE_PIXEL_FORMAT, pixel_क्रमmat);
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CONTROL__ALPHA_EN, alpha_en);

	// अगर input adjusपंचांगents exist, program icsc with those values

	अगर (input_csc_color_matrix.enable_adjusपंचांगent
				== true) अणु
		क्रम (i = 0; i < 12; i++)
			tbl_entry.regval[i] = input_csc_color_matrix.matrix[i];

		tbl_entry.color_space = color_space;

		अगर (color_space >= COLOR_SPACE_YCBCR601)
			select = INPUT_CSC_SELECT_ICSC;
		अन्यथा
			select = INPUT_CSC_SELECT_BYPASS;

		dpp1_program_input_csc(dpp_base, color_space, select, &tbl_entry);
	पूर्ण अन्यथा
		dpp1_program_input_csc(dpp_base, color_space, select, शून्य);

	अगर (क्रमce_disable_cursor) अणु
		REG_UPDATE(CURSOR_CONTROL,
				CURSOR_ENABLE, 0);
		REG_UPDATE(CURSOR0_CONTROL,
				CUR0_ENABLE, 0);
	पूर्ण
पूर्ण

व्योम dpp1_set_cursor_attributes(
		काष्ठा dpp *dpp_base,
		काष्ठा dc_cursor_attributes *cursor_attributes)
अणु
	क्रमागत dc_cursor_color_क्रमmat color_क्रमmat = cursor_attributes->color_क्रमmat;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_UPDATE_2(CURSOR0_CONTROL,
			CUR0_MODE, color_क्रमmat,
			CUR0_EXPANSION_MODE, 0);

	अगर (color_क्रमmat == CURSOR_MODE_MONO) अणु
		/* toकरो: clarअगरy what to program these to */
		REG_UPDATE(CURSOR0_COLOR0,
				CUR0_COLOR0, 0x00000000);
		REG_UPDATE(CURSOR0_COLOR1,
				CUR0_COLOR1, 0xFFFFFFFF);
	पूर्ण
पूर्ण


व्योम dpp1_set_cursor_position(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा dc_cursor_position *pos,
		स्थिर काष्ठा dc_cursor_mi_param *param,
		uपूर्णांक32_t width,
		uपूर्णांक32_t height)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	पूर्णांक src_x_offset = pos->x - pos->x_hotspot - param->viewport.x;
	पूर्णांक src_y_offset = pos->y - pos->y_hotspot - param->viewport.y;
	uपूर्णांक32_t cur_en = pos->enable ? 1 : 0;

	// Cursor width/height and hotspots need to be rotated क्रम offset calculation
	अगर (param->rotation == ROTATION_ANGLE_90 || param->rotation == ROTATION_ANGLE_270) अणु
		swap(width, height);
		अगर (param->rotation == ROTATION_ANGLE_90) अणु
			src_x_offset = pos->x - pos->y_hotspot - param->viewport.x;
			src_y_offset = pos->y - pos->x_hotspot - param->viewport.y;
		पूर्ण
	पूर्ण अन्यथा अगर (param->rotation == ROTATION_ANGLE_180) अणु
		src_x_offset = pos->x - param->viewport.x;
		src_y_offset = pos->y - param->viewport.y;
	पूर्ण


	अगर (src_x_offset >= (पूर्णांक)param->viewport.width)
		cur_en = 0;  /* not visible beyond right edge*/

	अगर (src_x_offset + (पूर्णांक)width <= 0)
		cur_en = 0;  /* not visible beyond left edge*/

	अगर (src_y_offset >= (पूर्णांक)param->viewport.height)
		cur_en = 0;  /* not visible beyond bottom edge*/

	अगर (src_y_offset + (पूर्णांक)height <= 0)
		cur_en = 0;  /* not visible beyond top edge*/

	REG_UPDATE(CURSOR0_CONTROL,
			CUR0_ENABLE, cur_en);

पूर्ण

व्योम dpp1_cnv_set_optional_cursor_attributes(
		काष्ठा dpp *dpp_base,
		काष्ठा dpp_cursor_attributes *attr)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	अगर (attr) अणु
		REG_UPDATE(CURSOR0_FP_SCALE_BIAS,  CUR0_FP_BIAS,  attr->bias);
		REG_UPDATE(CURSOR0_FP_SCALE_BIAS,  CUR0_FP_SCALE, attr->scale);
	पूर्ण
पूर्ण

व्योम dpp1_dppclk_control(
		काष्ठा dpp *dpp_base,
		bool dppclk_भाग,
		bool enable)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	अगर (enable) अणु
		अगर (dpp->tf_mask->DPPCLK_RATE_CONTROL)
			REG_UPDATE_2(DPP_CONTROL,
				DPPCLK_RATE_CONTROL, dppclk_भाग,
				DPP_CLOCK_ENABLE, 1);
		अन्यथा
			REG_UPDATE(DPP_CONTROL, DPP_CLOCK_ENABLE, 1);
	पूर्ण अन्यथा
		REG_UPDATE(DPP_CONTROL, DPP_CLOCK_ENABLE, 0);
पूर्ण

अटल स्थिर काष्ठा dpp_funcs dcn10_dpp_funcs = अणु
		.dpp_पढ़ो_state = dpp_पढ़ो_state,
		.dpp_reset = dpp_reset,
		.dpp_set_scaler = dpp1_dscl_set_scaler_manual_scale,
		.dpp_get_optimal_number_of_taps = dpp1_get_optimal_number_of_taps,
		.dpp_set_gamut_remap = dpp1_cm_set_gamut_remap,
		.dpp_set_csc_adjusपंचांगent = dpp1_cm_set_output_csc_adjusपंचांगent,
		.dpp_set_csc_शेष = dpp1_cm_set_output_csc_शेष,
		.dpp_घातer_on_regamma_lut = dpp1_cm_घातer_on_regamma_lut,
		.dpp_program_regamma_lut = dpp1_cm_program_regamma_lut,
		.dpp_configure_regamma_lut = dpp1_cm_configure_regamma_lut,
		.dpp_program_regamma_lutb_settings = dpp1_cm_program_regamma_lutb_settings,
		.dpp_program_regamma_luta_settings = dpp1_cm_program_regamma_luta_settings,
		.dpp_program_regamma_pwl = dpp1_cm_set_regamma_pwl,
		.dpp_program_bias_and_scale = dpp1_program_bias_and_scale,
		.dpp_set_degamma = dpp1_set_degamma,
		.dpp_program_input_lut		= dpp1_program_input_lut,
		.dpp_program_degamma_pwl	= dpp1_set_degamma_pwl,
		.dpp_setup			= dpp1_cnv_setup,
		.dpp_full_bypass		= dpp1_full_bypass,
		.set_cursor_attributes = dpp1_set_cursor_attributes,
		.set_cursor_position = dpp1_set_cursor_position,
		.set_optional_cursor_attributes = dpp1_cnv_set_optional_cursor_attributes,
		.dpp_dppclk_control = dpp1_dppclk_control,
		.dpp_set_hdr_multiplier = dpp1_set_hdr_multiplier,
		.dpp_program_blnd_lut = शून्य,
		.dpp_program_shaper_lut = शून्य,
		.dpp_program_3dlut = शून्य
पूर्ण;

अटल काष्ठा dpp_caps dcn10_dpp_cap = अणु
	.dscl_data_proc_क्रमmat = DSCL_DATA_PRCESSING_FIXED_FORMAT,
	.dscl_calc_lb_num_partitions = dpp1_dscl_calc_lb_num_partitions,
पूर्ण;

/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

व्योम dpp1_स्थिरruct(
	काष्ठा dcn10_dpp *dpp,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn_dpp_रेजिस्टरs *tf_regs,
	स्थिर काष्ठा dcn_dpp_shअगरt *tf_shअगरt,
	स्थिर काष्ठा dcn_dpp_mask *tf_mask)
अणु
	dpp->base.ctx = ctx;

	dpp->base.inst = inst;
	dpp->base.funcs = &dcn10_dpp_funcs;
	dpp->base.caps = &dcn10_dpp_cap;

	dpp->tf_regs = tf_regs;
	dpp->tf_shअगरt = tf_shअगरt;
	dpp->tf_mask = tf_mask;

	dpp->lb_pixel_depth_supported =
		LB_PIXEL_DEPTH_18BPP |
		LB_PIXEL_DEPTH_24BPP |
		LB_PIXEL_DEPTH_30BPP;

	dpp->lb_bits_per_entry = LB_BITS_PER_ENTRY;
	dpp->lb_memory_size = LB_TOTAL_NUMBER_OF_ENTRIES; /*0x1404*/
पूर्ण
