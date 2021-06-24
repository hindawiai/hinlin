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


व्योम dpp30_पढ़ो_state(काष्ठा dpp *dpp_base,
		काष्ठा dcn_dpp_state *s)
अणु
	काष्ठा dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_GET(DPP_CONTROL,
			DPP_CLOCK_ENABLE, &s->is_enabled);

	// TODO: Implement क्रम DCN3
पूर्ण
/*program post scaler scs block in dpp CM*/
व्योम dpp3_program_post_csc(
		काष्ठा dpp *dpp_base,
		क्रमागत dc_color_space color_space,
		क्रमागत dcn10_input_csc_select input_select,
		स्थिर काष्ठा out_csc_color_matrix *tbl_entry)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	पूर्णांक i;
	पूर्णांक arr_size = माप(dpp_input_csc_matrix)/माप(काष्ठा dpp_input_csc_matrix);
	स्थिर uपूर्णांक16_t *regval = शून्य;
	uपूर्णांक32_t cur_select = 0;
	क्रमागत dcn10_input_csc_select select;
	काष्ठा color_matrices_reg gam_regs;

	अगर (input_select == INPUT_CSC_SELECT_BYPASS) अणु
		REG_SET(CM_POST_CSC_CONTROL, 0, CM_POST_CSC_MODE, 0);
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
	REG_GET(CM_POST_CSC_CONTROL,
			CM_POST_CSC_MODE_CURRENT, &cur_select);

	अगर (cur_select != INPUT_CSC_SELECT_ICSC)
		select = INPUT_CSC_SELECT_ICSC;
	अन्यथा
		select = INPUT_CSC_SELECT_COMA;

	gam_regs.shअगरts.csc_c11 = dpp->tf_shअगरt->CM_POST_CSC_C11;
	gam_regs.masks.csc_c11  = dpp->tf_mask->CM_POST_CSC_C11;
	gam_regs.shअगरts.csc_c12 = dpp->tf_shअगरt->CM_POST_CSC_C12;
	gam_regs.masks.csc_c12 = dpp->tf_mask->CM_POST_CSC_C12;

	अगर (select == INPUT_CSC_SELECT_ICSC) अणु

		gam_regs.csc_c11_c12 = REG(CM_POST_CSC_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_POST_CSC_C33_C34);

	पूर्ण अन्यथा अणु

		gam_regs.csc_c11_c12 = REG(CM_POST_CSC_B_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_POST_CSC_B_C33_C34);

	पूर्ण

	cm_helper_program_color_matrices(
			dpp->base.ctx,
			regval,
			&gam_regs);

	REG_SET(CM_POST_CSC_CONTROL, 0,
			CM_POST_CSC_MODE, select);
पूर्ण


/*CNVC degam unit has पढ़ो only LUTs*/
व्योम dpp3_set_pre_degam(काष्ठा dpp *dpp_base, क्रमागत dc_transfer_func_predefined tr)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	पूर्णांक pre_degam_en = 1;
	पूर्णांक degamma_lut_selection = 0;

	चयन (tr) अणु
	हाल TRANSFER_FUNCTION_LINEAR:
	हाल TRANSFER_FUNCTION_UNITY:
		pre_degam_en = 0; //bypass
		अवरोध;
	हाल TRANSFER_FUNCTION_SRGB:
		degamma_lut_selection = 0;
		अवरोध;
	हाल TRANSFER_FUNCTION_BT709:
		degamma_lut_selection = 4;
		अवरोध;
	हाल TRANSFER_FUNCTION_PQ:
		degamma_lut_selection = 5;
		अवरोध;
	हाल TRANSFER_FUNCTION_HLG:
		degamma_lut_selection = 6;
		अवरोध;
	हाल TRANSFER_FUNCTION_GAMMA22:
		degamma_lut_selection = 1;
		अवरोध;
	हाल TRANSFER_FUNCTION_GAMMA24:
		degamma_lut_selection = 2;
		अवरोध;
	हाल TRANSFER_FUNCTION_GAMMA26:
		degamma_lut_selection = 3;
		अवरोध;
	शेष:
		pre_degam_en = 0;
		अवरोध;
	पूर्ण

	REG_SET_2(PRE_DEGAM, 0,
			PRE_DEGAM_MODE, pre_degam_en,
			PRE_DEGAM_SELECT, degamma_lut_selection);
पूर्ण

अटल व्योम dpp3_cnv_setup (
		काष्ठा dpp *dpp_base,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		क्रमागत expansion_mode mode,
		काष्ठा dc_csc_transक्रमm input_csc_color_matrix,
		क्रमागत dc_color_space input_color_space,
		काष्ठा cnv_alpha_2bit_lut *alpha_2bit_lut)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	uपूर्णांक32_t pixel_क्रमmat = 0;
	uपूर्णांक32_t alpha_en = 1;
	क्रमागत dc_color_space color_space = COLOR_SPACE_SRGB;
	क्रमागत dcn10_input_csc_select select = INPUT_CSC_SELECT_BYPASS;
	bool क्रमce_disable_cursor = false;
	uपूर्णांक32_t is_2bit = 0;
	uपूर्णांक32_t alpha_plane_enable = 0;
	uपूर्णांक32_t dealpha_en = 0, dealpha_ablnd_en = 0;
	uपूर्णांक32_t realpha_en = 0, realpha_ablnd_en = 0;
	uपूर्णांक32_t program_prealpha_dealpha = 0;
	काष्ठा out_csc_color_matrix tbl_entry;
	पूर्णांक i;

	REG_SET_2(FORMAT_CONTROL, 0,
		CNVC_BYPASS, 0,
		FORMAT_EXPANSION_MODE, mode);

	REG_UPDATE(FORMAT_CONTROL, FORMAT_CNV16, 0);
	REG_UPDATE(FORMAT_CONTROL, CNVC_BYPASS_MSB_ALIGN, 0);
	REG_UPDATE(FORMAT_CONTROL, CLAMP_POSITIVE, 0);
	REG_UPDATE(FORMAT_CONTROL, CLAMP_POSITIVE_C, 0);

	REG_UPDATE(FORMAT_CONTROL, FORMAT_CROSSBAR_R, 0);
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CROSSBAR_G, 1);
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CROSSBAR_B, 2);

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
		is_2bit = 1;
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
	हाल SURFACE_PIXEL_FORMAT_VIDEO_AYCrCb8888:
		pixel_क्रमmat = 12;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX:
		pixel_क्रमmat = 112;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX:
		pixel_क्रमmat = 113;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010:
		pixel_क्रमmat = 114;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		is_2bit = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_CrYCbA1010102:
		pixel_क्रमmat = 115;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		is_2bit = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE:
		pixel_क्रमmat = 116;
		alpha_plane_enable = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA:
		pixel_क्रमmat = 116;
		alpha_plane_enable = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT:
		pixel_क्रमmat = 118;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT:
		pixel_क्रमmat = 119;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (is_2bit == 1 && alpha_2bit_lut != शून्य) अणु
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT0, alpha_2bit_lut->lut0);
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT1, alpha_2bit_lut->lut1);
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT2, alpha_2bit_lut->lut2);
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT3, alpha_2bit_lut->lut3);
	पूर्ण

	REG_SET_2(CNVC_SURFACE_PIXEL_FORMAT, 0,
			CNVC_SURFACE_PIXEL_FORMAT, pixel_क्रमmat,
			CNVC_ALPHA_PLANE_ENABLE, alpha_plane_enable);
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CONTROL__ALPHA_EN, alpha_en);

	अगर (program_prealpha_dealpha) अणु
		dealpha_en = 1;
		realpha_en = 1;
	पूर्ण
	REG_SET_2(PRE_DEALPHA, 0,
			PRE_DEALPHA_EN, dealpha_en,
			PRE_DEALPHA_ABLND_EN, dealpha_ablnd_en);
	REG_SET_2(PRE_REALPHA, 0,
			PRE_REALPHA_EN, realpha_en,
			PRE_REALPHA_ABLND_EN, realpha_ablnd_en);

	/* If input adjusपंचांगent exists, program the ICSC with those values. */
	अगर (input_csc_color_matrix.enable_adjusपंचांगent == true) अणु
		क्रम (i = 0; i < 12; i++)
			tbl_entry.regval[i] = input_csc_color_matrix.matrix[i];

		tbl_entry.color_space = input_color_space;

		अगर (color_space >= COLOR_SPACE_YCBCR601)
			select = INPUT_CSC_SELECT_ICSC;
		अन्यथा
			select = INPUT_CSC_SELECT_BYPASS;

		dpp3_program_post_csc(dpp_base, color_space, select,
				      &tbl_entry);
	पूर्ण अन्यथा अणु
		dpp3_program_post_csc(dpp_base, color_space, select, शून्य);
	पूर्ण

	अगर (क्रमce_disable_cursor) अणु
		REG_UPDATE(CURSOR_CONTROL,
				CURSOR_ENABLE, 0);
		REG_UPDATE(CURSOR0_CONTROL,
				CUR0_ENABLE, 0);
	पूर्ण
पूर्ण

#घोषणा IDENTITY_RATIO(ratio) (dc_fixpt_u3d19(ratio) == (1 << 19))

व्योम dpp3_set_cursor_attributes(
		काष्ठा dpp *dpp_base,
		काष्ठा dc_cursor_attributes *cursor_attributes)
अणु
	क्रमागत dc_cursor_color_क्रमmat color_क्रमmat = cursor_attributes->color_क्रमmat;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	पूर्णांक cur_rom_en = 0;

	अगर (color_क्रमmat == CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA ||
		color_क्रमmat == CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA)
		cur_rom_en = 1;

	REG_UPDATE_3(CURSOR0_CONTROL,
			CUR0_MODE, color_क्रमmat,
			CUR0_EXPANSION_MODE, 0,
			CUR0_ROM_EN, cur_rom_en);

	अगर (color_क्रमmat == CURSOR_MODE_MONO) अणु
		/* toकरो: clarअगरy what to program these to */
		REG_UPDATE(CURSOR0_COLOR0,
				CUR0_COLOR0, 0x00000000);
		REG_UPDATE(CURSOR0_COLOR1,
				CUR0_COLOR1, 0xFFFFFFFF);
	पूर्ण
पूर्ण


bool dpp3_get_optimal_number_of_taps(
		काष्ठा dpp *dpp,
		काष्ठा scaler_data *scl_data,
		स्थिर काष्ठा scaling_taps *in_taps)
अणु
	पूर्णांक num_part_y, num_part_c;
	पूर्णांक max_taps_y, max_taps_c;
	पूर्णांक min_taps_y, min_taps_c;
	क्रमागत lb_memory_config lb_config;

	/* Some ASICs करोes not support  FP16 scaling, so we reject modes require this*/
	अगर (scl_data->viewport.width  != scl_data->h_active &&
		scl_data->viewport.height != scl_data->v_active &&
		dpp->caps->dscl_data_proc_क्रमmat == DSCL_DATA_PRCESSING_FIXED_FORMAT &&
		scl_data->क्रमmat == PIXEL_FORMAT_FP16)
		वापस false;

	अगर (scl_data->viewport.width > scl_data->h_active &&
		dpp->ctx->dc->debug.max_करोwnscale_src_width != 0 &&
		scl_data->viewport.width > dpp->ctx->dc->debug.max_करोwnscale_src_width)
		वापस false;

	/*
	 * Set शेष taps अगर none are provided
	 * From programming guide: taps = minअणु उच्चमान(2*H_RATIO,1), 8पूर्ण क्रम करोwnscaling
	 * taps = 4 क्रम upscaling
	 */
	अगर (in_taps->h_taps == 0) अणु
		अगर (dc_fixpt_उच्चमान(scl_data->ratios.horz) > 1)
			scl_data->taps.h_taps = min(2 * dc_fixpt_उच्चमान(scl_data->ratios.horz), 8);
		अन्यथा
			scl_data->taps.h_taps = 4;
	पूर्ण अन्यथा
		scl_data->taps.h_taps = in_taps->h_taps;
	अगर (in_taps->v_taps == 0) अणु
		अगर (dc_fixpt_उच्चमान(scl_data->ratios.vert) > 1)
			scl_data->taps.v_taps = min(dc_fixpt_उच्चमान(dc_fixpt_mul_पूर्णांक(scl_data->ratios.vert, 2)), 8);
		अन्यथा
			scl_data->taps.v_taps = 4;
	पूर्ण अन्यथा
		scl_data->taps.v_taps = in_taps->v_taps;
	अगर (in_taps->v_taps_c == 0) अणु
		अगर (dc_fixpt_उच्चमान(scl_data->ratios.vert_c) > 1)
			scl_data->taps.v_taps_c = min(dc_fixpt_उच्चमान(dc_fixpt_mul_पूर्णांक(scl_data->ratios.vert_c, 2)), 8);
		अन्यथा
			scl_data->taps.v_taps_c = 4;
	पूर्ण अन्यथा
		scl_data->taps.v_taps_c = in_taps->v_taps_c;
	अगर (in_taps->h_taps_c == 0) अणु
		अगर (dc_fixpt_उच्चमान(scl_data->ratios.horz_c) > 1)
			scl_data->taps.h_taps_c = min(2 * dc_fixpt_उच्चमान(scl_data->ratios.horz_c), 8);
		अन्यथा
			scl_data->taps.h_taps_c = 4;
	पूर्ण अन्यथा अगर ((in_taps->h_taps_c % 2) != 0 && in_taps->h_taps_c != 1)
		/* Only 1 and even h_taps_c are supported by hw */
		scl_data->taps.h_taps_c = in_taps->h_taps_c - 1;
	अन्यथा
		scl_data->taps.h_taps_c = in_taps->h_taps_c;

	/*Ensure we can support the requested number of vtaps*/
	min_taps_y = dc_fixpt_उच्चमान(scl_data->ratios.vert);
	min_taps_c = dc_fixpt_उच्चमान(scl_data->ratios.vert_c);

	/* Use LB_MEMORY_CONFIG_3 क्रम 4:2:0 */
	अगर ((scl_data->क्रमmat == PIXEL_FORMAT_420BPP8) || (scl_data->क्रमmat == PIXEL_FORMAT_420BPP10))
		lb_config = LB_MEMORY_CONFIG_3;
	अन्यथा
		lb_config = LB_MEMORY_CONFIG_0;

	dpp->caps->dscl_calc_lb_num_partitions(
			scl_data, lb_config, &num_part_y, &num_part_c);

	/* MAX_V_TAPS = MIN (NUM_LINES - MAX(CEILING(V_RATIO,1)-2, 0), 8) */
	अगर (dc_fixpt_उच्चमान(scl_data->ratios.vert) > 2)
		max_taps_y = num_part_y - (dc_fixpt_उच्चमान(scl_data->ratios.vert) - 2);
	अन्यथा
		max_taps_y = num_part_y;

	अगर (dc_fixpt_उच्चमान(scl_data->ratios.vert_c) > 2)
		max_taps_c = num_part_c - (dc_fixpt_उच्चमान(scl_data->ratios.vert_c) - 2);
	अन्यथा
		max_taps_c = num_part_c;

	अगर (max_taps_y < min_taps_y)
		वापस false;
	अन्यथा अगर (max_taps_c < min_taps_c)
		वापस false;

	अगर (scl_data->taps.v_taps > max_taps_y)
		scl_data->taps.v_taps = max_taps_y;

	अगर (scl_data->taps.v_taps_c > max_taps_c)
		scl_data->taps.v_taps_c = max_taps_c;

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

व्योम dpp3_cnv_set_bias_scale(
		काष्ठा dpp *dpp_base,
		काष्ठा  dc_bias_and_scale *bias_and_scale)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_UPDATE(FCNV_FP_BIAS_R, FCNV_FP_BIAS_R, bias_and_scale->bias_red);
	REG_UPDATE(FCNV_FP_BIAS_G, FCNV_FP_BIAS_G, bias_and_scale->bias_green);
	REG_UPDATE(FCNV_FP_BIAS_B, FCNV_FP_BIAS_B, bias_and_scale->bias_blue);
	REG_UPDATE(FCNV_FP_SCALE_R, FCNV_FP_SCALE_R, bias_and_scale->scale_red);
	REG_UPDATE(FCNV_FP_SCALE_G, FCNV_FP_SCALE_G, bias_and_scale->scale_green);
	REG_UPDATE(FCNV_FP_SCALE_B, FCNV_FP_SCALE_B, bias_and_scale->scale_blue);
पूर्ण

अटल व्योम dpp3_घातer_on_blnd_lut(
	काष्ठा dpp *dpp_base,
	bool घातer_on)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm) अणु
		REG_UPDATE(CM_MEM_PWR_CTRL, BLNDGAM_MEM_PWR_FORCE, घातer_on ? 0 : 3);
		अगर (घातer_on)
			REG_WAIT(CM_MEM_PWR_STATUS, BLNDGAM_MEM_PWR_STATE, 0, 1, 5);
	पूर्ण अन्यथा अणु
		REG_SET(CM_MEM_PWR_CTRL, 0,
				BLNDGAM_MEM_PWR_FORCE, घातer_on == true ? 0 : 1);
	पूर्ण
पूर्ण

अटल व्योम dpp3_घातer_on_hdr3dlut(
	काष्ठा dpp *dpp_base,
	bool घातer_on)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm) अणु
		REG_UPDATE(CM_MEM_PWR_CTRL2, HDR3DLUT_MEM_PWR_FORCE, घातer_on ? 0 : 3);
		अगर (घातer_on)
			REG_WAIT(CM_MEM_PWR_STATUS2, HDR3DLUT_MEM_PWR_STATE, 0, 1, 5);
	पूर्ण
पूर्ण

अटल व्योम dpp3_घातer_on_shaper(
	काष्ठा dpp *dpp_base,
	bool घातer_on)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm) अणु
		REG_UPDATE(CM_MEM_PWR_CTRL2, SHAPER_MEM_PWR_FORCE, घातer_on ? 0 : 3);
		अगर (घातer_on)
			REG_WAIT(CM_MEM_PWR_STATUS2, SHAPER_MEM_PWR_STATE, 0, 1, 5);
	पूर्ण
पूर्ण

अटल व्योम dpp3_configure_blnd_lut(
		काष्ठा dpp *dpp_base,
		bool is_ram_a)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_UPDATE_2(CM_BLNDGAM_LUT_CONTROL,
			CM_BLNDGAM_LUT_WRITE_COLOR_MASK, 7,
			CM_BLNDGAM_LUT_HOST_SEL, is_ram_a == true ? 0 : 1);

	REG_SET(CM_BLNDGAM_LUT_INDEX, 0, CM_BLNDGAM_LUT_INDEX, 0);
पूर्ण

अटल व्योम dpp3_program_blnd_pwl(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_result_data *rgb,
		uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t i;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	uपूर्णांक32_t last_base_value_red = rgb[num-1].red_reg + rgb[num-1].delta_red_reg;
	uपूर्णांक32_t last_base_value_green = rgb[num-1].green_reg + rgb[num-1].delta_green_reg;
	uपूर्णांक32_t last_base_value_blue = rgb[num-1].blue_reg + rgb[num-1].delta_blue_reg;

	अगर (is_rgb_equal(rgb, num)) अणु
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, rgb[i].red_reg);
		REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, last_base_value_red);
	पूर्ण अन्यथा अणु
		REG_UPDATE(CM_BLNDGAM_LUT_CONTROL, CM_BLNDGAM_LUT_WRITE_COLOR_MASK, 4);
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, rgb[i].red_reg);
		REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, last_base_value_red);

		REG_UPDATE(CM_BLNDGAM_LUT_CONTROL, CM_BLNDGAM_LUT_WRITE_COLOR_MASK, 2);
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, rgb[i].green_reg);
		REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, last_base_value_green);

		REG_UPDATE(CM_BLNDGAM_LUT_CONTROL, CM_BLNDGAM_LUT_WRITE_COLOR_MASK, 1);
		क्रम (i = 0 ; i < num; i++)
			REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, rgb[i].blue_reg);
		REG_SET(CM_BLNDGAM_LUT_DATA, 0, CM_BLNDGAM_LUT_DATA, last_base_value_blue);
	पूर्ण
पूर्ण

अटल व्योम dcn3_dpp_cm_get_reg_field(
		काष्ठा dcn3_dpp *dpp,
		काष्ठा dcn3_xfer_func_reg *reg)
अणु
	reg->shअगरts.exp_region0_lut_offset = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shअगरts.exp_region0_num_segments = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shअगरts.exp_region1_lut_offset = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shअगरts.exp_region1_num_segments = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;

	reg->shअगरts.field_region_end = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION_END_B;
	reg->masks.field_region_end = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION_END_B;
	reg->shअगरts.field_region_end_slope = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->shअगरts.field_region_end_base = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->shअगरts.field_region_linear_slope = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION_START_SLOPE_B;
	reg->masks.field_region_linear_slope = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION_START_SLOPE_B;
	reg->shअगरts.exp_region_start = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION_START_B;
	reg->masks.exp_region_start = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION_START_B;
	reg->shअगरts.exp_resion_start_segment = dpp->tf_shअगरt->CM_BLNDGAM_RAMA_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = dpp->tf_mask->CM_BLNDGAM_RAMA_EXP_REGION_START_SEGMENT_B;
पूर्ण

/*program blnd lut RAM A*/
अटल व्योम dpp3_program_blnd_luta_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	काष्ठा dcn3_xfer_func_reg gam_regs;

	dcn3_dpp_cm_get_reg_field(dpp, &gam_regs);

	gam_regs.start_cntl_b = REG(CM_BLNDGAM_RAMA_START_CNTL_B);
	gam_regs.start_cntl_g = REG(CM_BLNDGAM_RAMA_START_CNTL_G);
	gam_regs.start_cntl_r = REG(CM_BLNDGAM_RAMA_START_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(CM_BLNDGAM_RAMA_START_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(CM_BLNDGAM_RAMA_START_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(CM_BLNDGAM_RAMA_START_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(CM_BLNDGAM_RAMA_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(CM_BLNDGAM_RAMA_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(CM_BLNDGAM_RAMA_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(CM_BLNDGAM_RAMA_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(CM_BLNDGAM_RAMA_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(CM_BLNDGAM_RAMA_END_CNTL2_R);
	gam_regs.region_start = REG(CM_BLNDGAM_RAMA_REGION_0_1);
	gam_regs.region_end = REG(CM_BLNDGAM_RAMA_REGION_32_33);

	cm_helper_program_gamcor_xfer_func(dpp->base.ctx, params, &gam_regs);
पूर्ण

/*program blnd lut RAM B*/
अटल व्योम dpp3_program_blnd_lutb_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);
	काष्ठा dcn3_xfer_func_reg gam_regs;

	dcn3_dpp_cm_get_reg_field(dpp, &gam_regs);

	gam_regs.start_cntl_b = REG(CM_BLNDGAM_RAMB_START_CNTL_B);
	gam_regs.start_cntl_g = REG(CM_BLNDGAM_RAMB_START_CNTL_G);
	gam_regs.start_cntl_r = REG(CM_BLNDGAM_RAMB_START_CNTL_R);
	gam_regs.start_slope_cntl_b = REG(CM_BLNDGAM_RAMB_START_SLOPE_CNTL_B);
	gam_regs.start_slope_cntl_g = REG(CM_BLNDGAM_RAMB_START_SLOPE_CNTL_G);
	gam_regs.start_slope_cntl_r = REG(CM_BLNDGAM_RAMB_START_SLOPE_CNTL_R);
	gam_regs.start_end_cntl1_b = REG(CM_BLNDGAM_RAMB_END_CNTL1_B);
	gam_regs.start_end_cntl2_b = REG(CM_BLNDGAM_RAMB_END_CNTL2_B);
	gam_regs.start_end_cntl1_g = REG(CM_BLNDGAM_RAMB_END_CNTL1_G);
	gam_regs.start_end_cntl2_g = REG(CM_BLNDGAM_RAMB_END_CNTL2_G);
	gam_regs.start_end_cntl1_r = REG(CM_BLNDGAM_RAMB_END_CNTL1_R);
	gam_regs.start_end_cntl2_r = REG(CM_BLNDGAM_RAMB_END_CNTL2_R);
	gam_regs.region_start = REG(CM_BLNDGAM_RAMB_REGION_0_1);
	gam_regs.region_end = REG(CM_BLNDGAM_RAMB_REGION_32_33);

	cm_helper_program_gamcor_xfer_func(dpp->base.ctx, params, &gam_regs);
पूर्ण

अटल क्रमागत dc_lut_mode dpp3_get_blndgam_current(काष्ठा dpp *dpp_base)
अणु
	क्रमागत dc_lut_mode mode;
	uपूर्णांक32_t mode_current = 0;
	uपूर्णांक32_t in_use = 0;

	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_GET(CM_BLNDGAM_CONTROL,
			CM_BLNDGAM_MODE_CURRENT, &mode_current);
	REG_GET(CM_BLNDGAM_CONTROL,
			CM_BLNDGAM_SELECT_CURRENT, &in_use);

		चयन (mode_current) अणु
		हाल 0:
		हाल 1:
			mode = LUT_BYPASS;
			अवरोध;

		हाल 2:
			अगर (in_use == 0)
				mode = LUT_RAM_A;
			अन्यथा
				mode = LUT_RAM_B;
			अवरोध;
		शेष:
			mode = LUT_BYPASS;
			अवरोध;
		पूर्ण
		वापस mode;
पूर्ण

bool dpp3_program_blnd_lut(
	काष्ठा dpp *dpp_base, स्थिर काष्ठा pwl_params *params)
अणु
	क्रमागत dc_lut_mode current_mode;
	क्रमागत dc_lut_mode next_mode;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अगर (params == शून्य) अणु
		REG_SET(CM_BLNDGAM_CONTROL, 0, CM_BLNDGAM_MODE, 0);
		अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm)
			dpp3_घातer_on_blnd_lut(dpp_base, false);
		वापस false;
	पूर्ण

	current_mode = dpp3_get_blndgam_current(dpp_base);
	अगर (current_mode == LUT_BYPASS || current_mode == LUT_RAM_B)
		next_mode = LUT_RAM_A;
	अन्यथा
		next_mode = LUT_RAM_B;

	dpp3_घातer_on_blnd_lut(dpp_base, true);
	dpp3_configure_blnd_lut(dpp_base, next_mode == LUT_RAM_A);

	अगर (next_mode == LUT_RAM_A)
		dpp3_program_blnd_luta_settings(dpp_base, params);
	अन्यथा
		dpp3_program_blnd_lutb_settings(dpp_base, params);

	dpp3_program_blnd_pwl(
			dpp_base, params->rgb_resulted, params->hw_poपूर्णांकs_num);

	REG_UPDATE_2(CM_BLNDGAM_CONTROL,
			CM_BLNDGAM_MODE, 2,
			CM_BLNDGAM_SELECT, next_mode == LUT_RAM_A ? 0 : 1);

	वापस true;
पूर्ण


अटल व्योम dpp3_program_shaper_lut(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_result_data *rgb,
		uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t i, red, green, blue;
	uपूर्णांक32_t  red_delta, green_delta, blue_delta;
	uपूर्णांक32_t  red_value, green_value, blue_value;

	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	क्रम (i = 0 ; i < num; i++) अणु

		red   = rgb[i].red_reg;
		green = rgb[i].green_reg;
		blue  = rgb[i].blue_reg;

		red_delta   = rgb[i].delta_red_reg;
		green_delta = rgb[i].delta_green_reg;
		blue_delta  = rgb[i].delta_blue_reg;

		red_value   = ((red_delta   & 0x3ff) << 14) | (red   & 0x3fff);
		green_value = ((green_delta & 0x3ff) << 14) | (green & 0x3fff);
		blue_value  = ((blue_delta  & 0x3ff) << 14) | (blue  & 0x3fff);

		REG_SET(CM_SHAPER_LUT_DATA, 0, CM_SHAPER_LUT_DATA, red_value);
		REG_SET(CM_SHAPER_LUT_DATA, 0, CM_SHAPER_LUT_DATA, green_value);
		REG_SET(CM_SHAPER_LUT_DATA, 0, CM_SHAPER_LUT_DATA, blue_value);
	पूर्ण

पूर्ण

अटल क्रमागत dc_lut_mode dpp3_get_shaper_current(काष्ठा dpp *dpp_base)
अणु
	क्रमागत dc_lut_mode mode;
	uपूर्णांक32_t state_mode;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_GET(CM_SHAPER_CONTROL,
			CM_SHAPER_MODE_CURRENT, &state_mode);

		चयन (state_mode) अणु
		हाल 0:
			mode = LUT_BYPASS;
			अवरोध;
		हाल 1:
			mode = LUT_RAM_A;
			अवरोध;
		हाल 2:
			mode = LUT_RAM_B;
			अवरोध;
		शेष:
			mode = LUT_BYPASS;
			अवरोध;
		पूर्ण
		वापस mode;
पूर्ण

अटल व्योम dpp3_configure_shaper_lut(
		काष्ठा dpp *dpp_base,
		bool is_ram_a)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_UPDATE(CM_SHAPER_LUT_WRITE_EN_MASK,
			CM_SHAPER_LUT_WRITE_EN_MASK, 7);
	REG_UPDATE(CM_SHAPER_LUT_WRITE_EN_MASK,
			CM_SHAPER_LUT_WRITE_SEL, is_ram_a == true ? 0:1);
	REG_SET(CM_SHAPER_LUT_INDEX, 0, CM_SHAPER_LUT_INDEX, 0);
पूर्ण

/*program shaper RAM A*/

अटल व्योम dpp3_program_shaper_luta_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	स्थिर काष्ठा gamma_curve *curve;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_SET_2(CM_SHAPER_RAMA_START_CNTL_B, 0,
		CM_SHAPER_RAMA_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].blue.custom_भग्न_x,
		CM_SHAPER_RAMA_EXP_REGION_START_SEGMENT_B, 0);
	REG_SET_2(CM_SHAPER_RAMA_START_CNTL_G, 0,
		CM_SHAPER_RAMA_EXP_REGION_START_G, params->corner_poपूर्णांकs[0].green.custom_भग्न_x,
		CM_SHAPER_RAMA_EXP_REGION_START_SEGMENT_G, 0);
	REG_SET_2(CM_SHAPER_RAMA_START_CNTL_R, 0,
		CM_SHAPER_RAMA_EXP_REGION_START_R, params->corner_poपूर्णांकs[0].red.custom_भग्न_x,
		CM_SHAPER_RAMA_EXP_REGION_START_SEGMENT_R, 0);

	REG_SET_2(CM_SHAPER_RAMA_END_CNTL_B, 0,
		CM_SHAPER_RAMA_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_x,
		CM_SHAPER_RAMA_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_y);

	REG_SET_2(CM_SHAPER_RAMA_END_CNTL_G, 0,
		CM_SHAPER_RAMA_EXP_REGION_END_G, params->corner_poपूर्णांकs[1].green.custom_भग्न_x,
		CM_SHAPER_RAMA_EXP_REGION_END_BASE_G, params->corner_poपूर्णांकs[1].green.custom_भग्न_y);

	REG_SET_2(CM_SHAPER_RAMA_END_CNTL_R, 0,
		CM_SHAPER_RAMA_EXP_REGION_END_R, params->corner_poपूर्णांकs[1].red.custom_भग्न_x,
		CM_SHAPER_RAMA_EXP_REGION_END_BASE_R, params->corner_poपूर्णांकs[1].red.custom_भग्न_y);

	curve = params->arr_curve_poपूर्णांकs;
	REG_SET_4(CM_SHAPER_RAMA_REGION_0_1, 0,
		CM_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_2_3, 0,
		CM_SHAPER_RAMA_EXP_REGION2_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION2_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION3_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION3_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_4_5, 0,
		CM_SHAPER_RAMA_EXP_REGION4_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION4_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION5_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION5_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_6_7, 0,
		CM_SHAPER_RAMA_EXP_REGION6_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION6_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION7_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION7_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_8_9, 0,
		CM_SHAPER_RAMA_EXP_REGION8_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION8_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION9_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION9_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_10_11, 0,
		CM_SHAPER_RAMA_EXP_REGION10_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION10_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION11_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION11_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_12_13, 0,
		CM_SHAPER_RAMA_EXP_REGION12_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION12_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION13_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION13_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_14_15, 0,
		CM_SHAPER_RAMA_EXP_REGION14_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION14_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION15_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION15_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_16_17, 0,
		CM_SHAPER_RAMA_EXP_REGION16_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION16_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION17_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION17_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_18_19, 0,
		CM_SHAPER_RAMA_EXP_REGION18_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION18_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION19_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION19_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_20_21, 0,
		CM_SHAPER_RAMA_EXP_REGION20_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION20_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION21_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION21_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_22_23, 0,
		CM_SHAPER_RAMA_EXP_REGION22_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION22_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION23_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION23_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_24_25, 0,
		CM_SHAPER_RAMA_EXP_REGION24_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION24_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION25_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION25_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_26_27, 0,
		CM_SHAPER_RAMA_EXP_REGION26_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION26_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION27_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION27_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_28_29, 0,
		CM_SHAPER_RAMA_EXP_REGION28_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION28_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION29_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION29_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_30_31, 0,
		CM_SHAPER_RAMA_EXP_REGION30_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION30_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION31_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION31_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMA_REGION_32_33, 0,
		CM_SHAPER_RAMA_EXP_REGION32_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMA_EXP_REGION32_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMA_EXP_REGION33_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMA_EXP_REGION33_NUM_SEGMENTS, curve[1].segments_num);
पूर्ण

/*program shaper RAM B*/
अटल व्योम dpp3_program_shaper_lutb_settings(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	स्थिर काष्ठा gamma_curve *curve;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_SET_2(CM_SHAPER_RAMB_START_CNTL_B, 0,
		CM_SHAPER_RAMB_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].blue.custom_भग्न_x,
		CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_B, 0);
	REG_SET_2(CM_SHAPER_RAMB_START_CNTL_G, 0,
		CM_SHAPER_RAMB_EXP_REGION_START_G, params->corner_poपूर्णांकs[0].green.custom_भग्न_x,
		CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_G, 0);
	REG_SET_2(CM_SHAPER_RAMB_START_CNTL_R, 0,
		CM_SHAPER_RAMB_EXP_REGION_START_R, params->corner_poपूर्णांकs[0].red.custom_भग्न_x,
		CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_R, 0);

	REG_SET_2(CM_SHAPER_RAMB_END_CNTL_B, 0,
		CM_SHAPER_RAMB_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_x,
		CM_SHAPER_RAMB_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_y);

	REG_SET_2(CM_SHAPER_RAMB_END_CNTL_G, 0,
		CM_SHAPER_RAMB_EXP_REGION_END_G, params->corner_poपूर्णांकs[1].green.custom_भग्न_x,
		CM_SHAPER_RAMB_EXP_REGION_END_BASE_G, params->corner_poपूर्णांकs[1].green.custom_भग्न_y);

	REG_SET_2(CM_SHAPER_RAMB_END_CNTL_R, 0,
		CM_SHAPER_RAMB_EXP_REGION_END_R, params->corner_poपूर्णांकs[1].red.custom_भग्न_x,
		CM_SHAPER_RAMB_EXP_REGION_END_BASE_R, params->corner_poपूर्णांकs[1].red.custom_भग्न_y);

	curve = params->arr_curve_poपूर्णांकs;
	REG_SET_4(CM_SHAPER_RAMB_REGION_0_1, 0,
		CM_SHAPER_RAMB_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_2_3, 0,
		CM_SHAPER_RAMB_EXP_REGION2_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION2_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION3_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION3_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_4_5, 0,
		CM_SHAPER_RAMB_EXP_REGION4_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION4_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION5_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION5_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_6_7, 0,
		CM_SHAPER_RAMB_EXP_REGION6_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION6_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION7_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION7_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_8_9, 0,
		CM_SHAPER_RAMB_EXP_REGION8_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION8_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION9_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION9_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_10_11, 0,
		CM_SHAPER_RAMB_EXP_REGION10_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION10_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION11_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION11_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_12_13, 0,
		CM_SHAPER_RAMB_EXP_REGION12_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION12_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION13_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION13_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_14_15, 0,
		CM_SHAPER_RAMB_EXP_REGION14_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION14_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION15_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION15_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_16_17, 0,
		CM_SHAPER_RAMB_EXP_REGION16_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION16_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION17_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION17_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_18_19, 0,
		CM_SHAPER_RAMB_EXP_REGION18_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION18_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION19_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION19_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_20_21, 0,
		CM_SHAPER_RAMB_EXP_REGION20_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION20_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION21_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION21_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_22_23, 0,
		CM_SHAPER_RAMB_EXP_REGION22_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION22_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION23_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION23_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_24_25, 0,
		CM_SHAPER_RAMB_EXP_REGION24_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION24_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION25_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION25_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_26_27, 0,
		CM_SHAPER_RAMB_EXP_REGION26_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION26_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION27_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION27_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_28_29, 0,
		CM_SHAPER_RAMB_EXP_REGION28_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION28_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION29_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION29_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_30_31, 0,
		CM_SHAPER_RAMB_EXP_REGION30_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION30_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION31_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION31_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_32_33, 0,
		CM_SHAPER_RAMB_EXP_REGION32_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION32_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION33_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION33_NUM_SEGMENTS, curve[1].segments_num);

पूर्ण


bool dpp3_program_shaper(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा pwl_params *params)
अणु
	क्रमागत dc_lut_mode current_mode;
	क्रमागत dc_lut_mode next_mode;

	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अगर (params == शून्य) अणु
		REG_SET(CM_SHAPER_CONTROL, 0, CM_SHAPER_LUT_MODE, 0);
		अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm)
			dpp3_घातer_on_shaper(dpp_base, false);
		वापस false;
	पूर्ण

	अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm)
		dpp3_घातer_on_shaper(dpp_base, true);

	current_mode = dpp3_get_shaper_current(dpp_base);

	अगर (current_mode == LUT_BYPASS || current_mode == LUT_RAM_A)
		next_mode = LUT_RAM_B;
	अन्यथा
		next_mode = LUT_RAM_A;

	dpp3_configure_shaper_lut(dpp_base, next_mode == LUT_RAM_A);

	अगर (next_mode == LUT_RAM_A)
		dpp3_program_shaper_luta_settings(dpp_base, params);
	अन्यथा
		dpp3_program_shaper_lutb_settings(dpp_base, params);

	dpp3_program_shaper_lut(
			dpp_base, params->rgb_resulted, params->hw_poपूर्णांकs_num);

	REG_SET(CM_SHAPER_CONTROL, 0, CM_SHAPER_LUT_MODE, next_mode == LUT_RAM_A ? 1:2);

	वापस true;

पूर्ण

अटल क्रमागत dc_lut_mode get3dlut_config(
			काष्ठा dpp *dpp_base,
			bool *is_17x17x17,
			bool *is_12bits_color_channel)
अणु
	uपूर्णांक32_t i_mode, i_enable_10bits, lut_size;
	क्रमागत dc_lut_mode mode;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_GET(CM_3DLUT_READ_WRITE_CONTROL,
			CM_3DLUT_30BIT_EN, &i_enable_10bits);
	REG_GET(CM_3DLUT_MODE,
			CM_3DLUT_MODE_CURRENT, &i_mode);

	चयन (i_mode) अणु
	हाल 0:
		mode = LUT_BYPASS;
		अवरोध;
	हाल 1:
		mode = LUT_RAM_A;
		अवरोध;
	हाल 2:
		mode = LUT_RAM_B;
		अवरोध;
	शेष:
		mode = LUT_BYPASS;
		अवरोध;
	पूर्ण
	अगर (i_enable_10bits > 0)
		*is_12bits_color_channel = false;
	अन्यथा
		*is_12bits_color_channel = true;

	REG_GET(CM_3DLUT_MODE, CM_3DLUT_SIZE, &lut_size);

	अगर (lut_size == 0)
		*is_17x17x17 = true;
	अन्यथा
		*is_17x17x17 = false;

	वापस mode;
पूर्ण
/*
 * select ramA or ramB, or bypass
 * select color channel size 10 or 12 bits
 * select 3dlut size 17x17x17 or 9x9x9
 */
अटल व्योम dpp3_set_3dlut_mode(
		काष्ठा dpp *dpp_base,
		क्रमागत dc_lut_mode mode,
		bool is_color_channel_12bits,
		bool is_lut_size17x17x17)
अणु
	uपूर्णांक32_t lut_mode;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	अगर (mode == LUT_BYPASS)
		lut_mode = 0;
	अन्यथा अगर (mode == LUT_RAM_A)
		lut_mode = 1;
	अन्यथा
		lut_mode = 2;

	REG_UPDATE_2(CM_3DLUT_MODE,
			CM_3DLUT_MODE, lut_mode,
			CM_3DLUT_SIZE, is_lut_size17x17x17 == true ? 0 : 1);
पूर्ण

अटल व्योम dpp3_select_3dlut_ram(
		काष्ठा dpp *dpp_base,
		क्रमागत dc_lut_mode mode,
		bool is_color_channel_12bits)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_UPDATE_2(CM_3DLUT_READ_WRITE_CONTROL,
			CM_3DLUT_RAM_SEL, mode == LUT_RAM_A ? 0 : 1,
			CM_3DLUT_30BIT_EN,
			is_color_channel_12bits == true ? 0:1);
पूर्ण



अटल व्योम dpp3_set3dlut_ram12(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा dc_rgb *lut,
		uपूर्णांक32_t entries)
अणु
	uपूर्णांक32_t i, red, green, blue, red1, green1, blue1;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	क्रम (i = 0 ; i < entries; i += 2) अणु
		red   = lut[i].red<<4;
		green = lut[i].green<<4;
		blue  = lut[i].blue<<4;
		red1   = lut[i+1].red<<4;
		green1 = lut[i+1].green<<4;
		blue1  = lut[i+1].blue<<4;

		REG_SET_2(CM_3DLUT_DATA, 0,
				CM_3DLUT_DATA0, red,
				CM_3DLUT_DATA1, red1);

		REG_SET_2(CM_3DLUT_DATA, 0,
				CM_3DLUT_DATA0, green,
				CM_3DLUT_DATA1, green1);

		REG_SET_2(CM_3DLUT_DATA, 0,
				CM_3DLUT_DATA0, blue,
				CM_3DLUT_DATA1, blue1);

	पूर्ण
पूर्ण

/*
 * load selected lut with 10 bits color channels
 */
अटल व्योम dpp3_set3dlut_ram10(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा dc_rgb *lut,
		uपूर्णांक32_t entries)
अणु
	uपूर्णांक32_t i, red, green, blue, value;
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	क्रम (i = 0; i < entries; i++) अणु
		red   = lut[i].red;
		green = lut[i].green;
		blue  = lut[i].blue;

		value = (red<<20) | (green<<10) | blue;

		REG_SET(CM_3DLUT_DATA_30BIT, 0, CM_3DLUT_DATA_30BIT, value);
	पूर्ण

पूर्ण


अटल व्योम dpp3_select_3dlut_ram_mask(
		काष्ठा dpp *dpp_base,
		uपूर्णांक32_t ram_selection_mask)
अणु
	काष्ठा dcn3_dpp *dpp = TO_DCN30_DPP(dpp_base);

	REG_UPDATE(CM_3DLUT_READ_WRITE_CONTROL, CM_3DLUT_WRITE_EN_MASK,
			ram_selection_mask);
	REG_SET(CM_3DLUT_INDEX, 0, CM_3DLUT_INDEX, 0);
पूर्ण

bool dpp3_program_3dlut(
		काष्ठा dpp *dpp_base,
		काष्ठा tetrahedral_params *params)
अणु
	क्रमागत dc_lut_mode mode;
	bool is_17x17x17;
	bool is_12bits_color_channel;
	काष्ठा dc_rgb *lut0;
	काष्ठा dc_rgb *lut1;
	काष्ठा dc_rgb *lut2;
	काष्ठा dc_rgb *lut3;
	पूर्णांक lut_size0;
	पूर्णांक lut_size;

	अगर (params == शून्य) अणु
		dpp3_set_3dlut_mode(dpp_base, LUT_BYPASS, false, false);
		अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm)
			dpp3_घातer_on_hdr3dlut(dpp_base, false);
		वापस false;
	पूर्ण

	अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.cm)
		dpp3_घातer_on_hdr3dlut(dpp_base, true);

	mode = get3dlut_config(dpp_base, &is_17x17x17, &is_12bits_color_channel);

	अगर (mode == LUT_BYPASS || mode == LUT_RAM_B)
		mode = LUT_RAM_A;
	अन्यथा
		mode = LUT_RAM_B;

	is_17x17x17 = !params->use_tetrahedral_9;
	is_12bits_color_channel = params->use_12bits;
	अगर (is_17x17x17) अणु
		lut0 = params->tetrahedral_17.lut0;
		lut1 = params->tetrahedral_17.lut1;
		lut2 = params->tetrahedral_17.lut2;
		lut3 = params->tetrahedral_17.lut3;
		lut_size0 = माप(params->tetrahedral_17.lut0)/
					माप(params->tetrahedral_17.lut0[0]);
		lut_size  = माप(params->tetrahedral_17.lut1)/
					माप(params->tetrahedral_17.lut1[0]);
	पूर्ण अन्यथा अणु
		lut0 = params->tetrahedral_9.lut0;
		lut1 = params->tetrahedral_9.lut1;
		lut2 = params->tetrahedral_9.lut2;
		lut3 = params->tetrahedral_9.lut3;
		lut_size0 = माप(params->tetrahedral_9.lut0)/
				माप(params->tetrahedral_9.lut0[0]);
		lut_size  = माप(params->tetrahedral_9.lut1)/
				माप(params->tetrahedral_9.lut1[0]);
		पूर्ण

	dpp3_select_3dlut_ram(dpp_base, mode,
				is_12bits_color_channel);
	dpp3_select_3dlut_ram_mask(dpp_base, 0x1);
	अगर (is_12bits_color_channel)
		dpp3_set3dlut_ram12(dpp_base, lut0, lut_size0);
	अन्यथा
		dpp3_set3dlut_ram10(dpp_base, lut0, lut_size0);

	dpp3_select_3dlut_ram_mask(dpp_base, 0x2);
	अगर (is_12bits_color_channel)
		dpp3_set3dlut_ram12(dpp_base, lut1, lut_size);
	अन्यथा
		dpp3_set3dlut_ram10(dpp_base, lut1, lut_size);

	dpp3_select_3dlut_ram_mask(dpp_base, 0x4);
	अगर (is_12bits_color_channel)
		dpp3_set3dlut_ram12(dpp_base, lut2, lut_size);
	अन्यथा
		dpp3_set3dlut_ram10(dpp_base, lut2, lut_size);

	dpp3_select_3dlut_ram_mask(dpp_base, 0x8);
	अगर (is_12bits_color_channel)
		dpp3_set3dlut_ram12(dpp_base, lut3, lut_size);
	अन्यथा
		dpp3_set3dlut_ram10(dpp_base, lut3, lut_size);


	dpp3_set_3dlut_mode(dpp_base, mode, is_12bits_color_channel,
					is_17x17x17);

	वापस true;
पूर्ण
अटल काष्ठा dpp_funcs dcn30_dpp_funcs = अणु
	.dpp_program_gamcor_lut = dpp3_program_gamcor_lut,
	.dpp_पढ़ो_state			= dpp30_पढ़ो_state,
	.dpp_reset			= dpp_reset,
	.dpp_set_scaler			= dpp1_dscl_set_scaler_manual_scale,
	.dpp_get_optimal_number_of_taps	= dpp3_get_optimal_number_of_taps,
	.dpp_set_gamut_remap		= dpp3_cm_set_gamut_remap,
	.dpp_set_csc_adjusपंचांगent		= शून्य,
	.dpp_set_csc_शेष		= शून्य,
	.dpp_program_regamma_pwl	= शून्य,
	.dpp_set_pre_degam		= dpp3_set_pre_degam,
	.dpp_program_input_lut		= शून्य,
	.dpp_full_bypass		= dpp1_full_bypass,
	.dpp_setup			= dpp3_cnv_setup,
	.dpp_program_degamma_pwl	= शून्य,
	.dpp_program_cm_dealpha = dpp3_program_cm_dealpha,
	.dpp_program_cm_bias = dpp3_program_cm_bias,
	.dpp_program_blnd_lut = dpp3_program_blnd_lut,
	.dpp_program_shaper_lut = dpp3_program_shaper,
	.dpp_program_3dlut = dpp3_program_3dlut,
	.dpp_program_bias_and_scale	= शून्य,
	.dpp_cnv_set_alpha_keyer	= dpp2_cnv_set_alpha_keyer,
	.set_cursor_attributes		= dpp3_set_cursor_attributes,
	.set_cursor_position		= dpp1_set_cursor_position,
	.set_optional_cursor_attributes	= dpp1_cnv_set_optional_cursor_attributes,
	.dpp_dppclk_control		= dpp1_dppclk_control,
	.dpp_set_hdr_multiplier		= dpp3_set_hdr_multiplier,
पूर्ण;


अटल काष्ठा dpp_caps dcn30_dpp_cap = अणु
	.dscl_data_proc_क्रमmat = DSCL_DATA_PRCESSING_FLOAT_FORMAT,
	.dscl_calc_lb_num_partitions = dscl2_calc_lb_num_partitions,
पूर्ण;

bool dpp3_स्थिरruct(
	काष्ठा dcn3_dpp *dpp,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn3_dpp_रेजिस्टरs *tf_regs,
	स्थिर काष्ठा dcn3_dpp_shअगरt *tf_shअगरt,
	स्थिर काष्ठा dcn3_dpp_mask *tf_mask)
अणु
	dpp->base.ctx = ctx;

	dpp->base.inst = inst;
	dpp->base.funcs = &dcn30_dpp_funcs;
	dpp->base.caps = &dcn30_dpp_cap;

	dpp->tf_regs = tf_regs;
	dpp->tf_shअगरt = tf_shअगरt;
	dpp->tf_mask = tf_mask;

	dpp->lb_pixel_depth_supported =
		LB_PIXEL_DEPTH_18BPP |
		LB_PIXEL_DEPTH_24BPP |
		LB_PIXEL_DEPTH_30BPP;

	dpp->lb_bits_per_entry = LB_BITS_PER_ENTRY;
	dpp->lb_memory_size = LB_TOTAL_NUMBER_OF_ENTRIES; /*0x1404*/

	वापस true;
पूर्ण

