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
#समावेश "dcn20_dpp.h"
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

व्योम dpp20_पढ़ो_state(काष्ठा dpp *dpp_base,
		काष्ठा dcn_dpp_state *s)
अणु
	काष्ठा dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_GET(DPP_CONTROL,
			DPP_CLOCK_ENABLE, &s->is_enabled);
	REG_GET(CM_DGAM_CONTROL,
			CM_DGAM_LUT_MODE, &s->dgam_lut_mode);
	// BGAM has no ROM, and definition is dअगरferent, can't reuse same dump
	//REG_GET(CM_BLNDGAM_CONTROL,
	//		CM_BLNDGAM_LUT_MODE, &s->rgam_lut_mode);
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

व्योम dpp2_घातer_on_obuf(
		काष्ठा dpp *dpp_base,
	bool घातer_on)
अणु
	काष्ठा dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE(CM_MEM_PWR_CTRL, SHARED_MEM_PWR_DIS, घातer_on == true ? 1:0);

	REG_UPDATE(OBUF_MEM_PWR_CTRL,
			OBUF_MEM_PWR_FORCE, घातer_on == true ? 0:1);

	REG_UPDATE(DSCL_MEM_PWR_CTRL,
			LUT_MEM_PWR_FORCE, घातer_on == true ? 0:1);
पूर्ण

व्योम dpp2_dummy_program_input_lut(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा dc_gamma *gamma)
अणुपूर्ण

अटल व्योम dpp2_cnv_setup (
		काष्ठा dpp *dpp_base,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		क्रमागत expansion_mode mode,
		काष्ठा dc_csc_transक्रमm input_csc_color_matrix,
		क्रमागत dc_color_space input_color_space,
		काष्ठा cnv_alpha_2bit_lut *alpha_2bit_lut)
अणु
	काष्ठा dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	uपूर्णांक32_t pixel_क्रमmat = 0;
	uपूर्णांक32_t alpha_en = 1;
	क्रमागत dc_color_space color_space = COLOR_SPACE_SRGB;
	क्रमागत dcn20_input_csc_select select = DCN2_ICSC_SELECT_BYPASS;
	bool क्रमce_disable_cursor = false;
	काष्ठा out_csc_color_matrix tbl_entry;
	uपूर्णांक32_t is_2bit = 0;
	पूर्णांक i = 0;

	REG_SET_2(FORMAT_CONTROL, 0,
		CNVC_BYPASS, 0,
		FORMAT_EXPANSION_MODE, mode);

	//hardcode शेष
    //FORMAT_CONTROL. FORMAT_CNV16                                 	शेष 0: U0.16/S.1.15;         1: U1.15/ S.1.14
    //FORMAT_CONTROL. CNVC_BYPASS_MSB_ALIGN          				शेष 0: disabled              1: enabled
    //FORMAT_CONTROL. CLAMP_POSITIVE                               	शेष 0: disabled              1: enabled
    //FORMAT_CONTROL. CLAMP_POSITIVE_C                          	शेष 0: disabled              1: enabled
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CNV16, 0);
	REG_UPDATE(FORMAT_CONTROL, CNVC_BYPASS_MSB_ALIGN, 0);
	REG_UPDATE(FORMAT_CONTROL, CLAMP_POSITIVE, 0);
	REG_UPDATE(FORMAT_CONTROL, CLAMP_POSITIVE_C, 0);

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
		select = DCN2_ICSC_SELECT_ICSC_A;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		क्रमce_disable_cursor = true;
		pixel_क्रमmat = 64;
		color_space = COLOR_SPACE_YCBCR709;
		select = DCN2_ICSC_SELECT_ICSC_A;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
		क्रमce_disable_cursor = true;
		pixel_क्रमmat = 67;
		color_space = COLOR_SPACE_YCBCR709;
		select = DCN2_ICSC_SELECT_ICSC_A;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		क्रमce_disable_cursor = true;
		pixel_क्रमmat = 66;
		color_space = COLOR_SPACE_YCBCR709;
		select = DCN2_ICSC_SELECT_ICSC_A;
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
		select = DCN2_ICSC_SELECT_ICSC_A;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX:
		pixel_क्रमmat = 112;
		alpha_en = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX:
		pixel_क्रमmat = 113;
		alpha_en = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010:
		pixel_क्रमmat = 114;
		color_space = COLOR_SPACE_YCBCR709;
		select = DCN2_ICSC_SELECT_ICSC_A;
		is_2bit = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_CrYCbA1010102:
		pixel_क्रमmat = 115;
		color_space = COLOR_SPACE_YCBCR709;
		select = DCN2_ICSC_SELECT_ICSC_A;
		is_2bit = 1;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT:
		pixel_क्रमmat = 118;
		alpha_en = 0;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT:
		pixel_क्रमmat = 119;
		alpha_en = 0;
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

	REG_SET(CNVC_SURFACE_PIXEL_FORMAT, 0,
			CNVC_SURFACE_PIXEL_FORMAT, pixel_क्रमmat);
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CONTROL__ALPHA_EN, alpha_en);

	// अगर input adjusपंचांगents exist, program icsc with those values
	अगर (input_csc_color_matrix.enable_adjusपंचांगent
				== true) अणु
		क्रम (i = 0; i < 12; i++)
			tbl_entry.regval[i] = input_csc_color_matrix.matrix[i];

		tbl_entry.color_space = input_color_space;

		अगर (color_space >= COLOR_SPACE_YCBCR601)
			select = DCN2_ICSC_SELECT_ICSC_A;
		अन्यथा
			select = DCN2_ICSC_SELECT_BYPASS;

		dpp2_program_input_csc(dpp_base, color_space, select, &tbl_entry);
	पूर्ण अन्यथा
	dpp2_program_input_csc(dpp_base, color_space, select, शून्य);

	अगर (क्रमce_disable_cursor) अणु
		REG_UPDATE(CURSOR_CONTROL,
				CURSOR_ENABLE, 0);
		REG_UPDATE(CURSOR0_CONTROL,
				CUR0_ENABLE, 0);

	पूर्ण
	dpp2_घातer_on_obuf(dpp_base, true);

पूर्ण

व्योम dpp2_cnv_set_bias_scale(
		काष्ठा dpp *dpp_base,
		काष्ठा  dc_bias_and_scale *bias_and_scale)
अणु
	काष्ठा dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE(FCNV_FP_BIAS_R, FCNV_FP_BIAS_R, bias_and_scale->bias_red);
	REG_UPDATE(FCNV_FP_BIAS_G, FCNV_FP_BIAS_G, bias_and_scale->bias_green);
	REG_UPDATE(FCNV_FP_BIAS_B, FCNV_FP_BIAS_B, bias_and_scale->bias_blue);
	REG_UPDATE(FCNV_FP_SCALE_R, FCNV_FP_SCALE_R, bias_and_scale->scale_red);
	REG_UPDATE(FCNV_FP_SCALE_G, FCNV_FP_SCALE_G, bias_and_scale->scale_green);
	REG_UPDATE(FCNV_FP_SCALE_B, FCNV_FP_SCALE_B, bias_and_scale->scale_blue);
पूर्ण

/*compute the maximum number of lines that we can fit in the line buffer*/
व्योम dscl2_calc_lb_num_partitions(
		स्थिर काष्ठा scaler_data *scl_data,
		क्रमागत lb_memory_config lb_config,
		पूर्णांक *num_part_y,
		पूर्णांक *num_part_c)
अणु
	पूर्णांक memory_line_size_y, memory_line_size_c, memory_line_size_a,
	lb_memory_size, lb_memory_size_c, lb_memory_size_a, num_partitions_a;

	पूर्णांक line_size = scl_data->viewport.width < scl_data->recout.width ?
			scl_data->viewport.width : scl_data->recout.width;
	पूर्णांक line_size_c = scl_data->viewport_c.width < scl_data->recout.width ?
			scl_data->viewport_c.width : scl_data->recout.width;

	अगर (line_size == 0)
		line_size = 1;

	अगर (line_size_c == 0)
		line_size_c = 1;

	memory_line_size_y = (line_size + 5) / 6; /* +5 to उच्चमान */
	memory_line_size_c = (line_size_c + 5) / 6; /* +5 to उच्चमान */
	memory_line_size_a = (line_size + 5) / 6; /* +5 to उच्चमान */

	अगर (lb_config == LB_MEMORY_CONFIG_1) अणु
		lb_memory_size = 970;
		lb_memory_size_c = 970;
		lb_memory_size_a = 970;
	पूर्ण अन्यथा अगर (lb_config == LB_MEMORY_CONFIG_2) अणु
		lb_memory_size = 1290;
		lb_memory_size_c = 1290;
		lb_memory_size_a = 1290;
	पूर्ण अन्यथा अगर (lb_config == LB_MEMORY_CONFIG_3) अणु
		/* 420 mode: using 3rd mem from Y, Cr and Cb */
		lb_memory_size = 970 + 1290 + 484 + 484 + 484;
		lb_memory_size_c = 970 + 1290;
		lb_memory_size_a = 970 + 1290 + 484;
	पूर्ण अन्यथा अणु
		lb_memory_size = 970 + 1290 + 484;
		lb_memory_size_c = 970 + 1290 + 484;
		lb_memory_size_a = 970 + 1290 + 484;
	पूर्ण
	*num_part_y = lb_memory_size / memory_line_size_y;
	*num_part_c = lb_memory_size_c / memory_line_size_c;
	num_partitions_a = lb_memory_size_a / memory_line_size_a;

	अगर (scl_data->lb_params.alpha_en
			&& (num_partitions_a < *num_part_y))
		*num_part_y = num_partitions_a;

	अगर (*num_part_y > 64)
		*num_part_y = 64;
	अगर (*num_part_c > 64)
		*num_part_c = 64;
पूर्ण

व्योम dpp2_cnv_set_alpha_keyer(
		काष्ठा dpp *dpp_base,
		काष्ठा cnv_color_keyer_params *color_keyer)
अणु
	काष्ठा dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE(COLOR_KEYER_CONTROL, COLOR_KEYER_EN, color_keyer->color_keyer_en);

	REG_UPDATE(COLOR_KEYER_CONTROL, COLOR_KEYER_MODE, color_keyer->color_keyer_mode);

	REG_UPDATE(COLOR_KEYER_ALPHA, COLOR_KEYER_ALPHA_LOW, color_keyer->color_keyer_alpha_low);
	REG_UPDATE(COLOR_KEYER_ALPHA, COLOR_KEYER_ALPHA_HIGH, color_keyer->color_keyer_alpha_high);

	REG_UPDATE(COLOR_KEYER_RED, COLOR_KEYER_RED_LOW, color_keyer->color_keyer_red_low);
	REG_UPDATE(COLOR_KEYER_RED, COLOR_KEYER_RED_HIGH, color_keyer->color_keyer_red_high);

	REG_UPDATE(COLOR_KEYER_GREEN, COLOR_KEYER_GREEN_LOW, color_keyer->color_keyer_green_low);
	REG_UPDATE(COLOR_KEYER_GREEN, COLOR_KEYER_GREEN_HIGH, color_keyer->color_keyer_green_high);

	REG_UPDATE(COLOR_KEYER_BLUE, COLOR_KEYER_BLUE_LOW, color_keyer->color_keyer_blue_low);
	REG_UPDATE(COLOR_KEYER_BLUE, COLOR_KEYER_BLUE_HIGH, color_keyer->color_keyer_blue_high);
पूर्ण

व्योम dpp2_set_cursor_attributes(
		काष्ठा dpp *dpp_base,
		काष्ठा dc_cursor_attributes *cursor_attributes)
अणु
	क्रमागत dc_cursor_color_क्रमmat color_क्रमmat = cursor_attributes->color_क्रमmat;
	काष्ठा dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	पूर्णांक cur_rom_en = 0;

	अगर (color_क्रमmat == CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA ||
		color_क्रमmat == CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA) अणु
		अगर (cursor_attributes->attribute_flags.bits.ENABLE_CURSOR_DEGAMMA) अणु
			cur_rom_en = 1;
		पूर्ण
	पूर्ण

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

व्योम oppn20_dummy_program_regamma_pwl(
		काष्ठा dpp *dpp,
		स्थिर काष्ठा pwl_params *params,
		क्रमागत opp_regamma mode)
अणुपूर्ण

अटल काष्ठा dpp_funcs dcn20_dpp_funcs = अणु
	.dpp_पढ़ो_state = dpp20_पढ़ो_state,
	.dpp_reset = dpp_reset,
	.dpp_set_scaler = dpp1_dscl_set_scaler_manual_scale,
	.dpp_get_optimal_number_of_taps = dpp1_get_optimal_number_of_taps,
	.dpp_set_gamut_remap = dpp2_cm_set_gamut_remap,
	.dpp_set_csc_adjusपंचांगent = शून्य,
	.dpp_set_csc_शेष = शून्य,
	.dpp_program_regamma_pwl = oppn20_dummy_program_regamma_pwl,
	.dpp_set_degamma		= dpp2_set_degamma,
	.dpp_program_input_lut		= dpp2_dummy_program_input_lut,
	.dpp_full_bypass		= dpp1_full_bypass,
	.dpp_setup			= dpp2_cnv_setup,
	.dpp_program_degamma_pwl	= dpp2_set_degamma_pwl,
	.dpp_program_blnd_lut = dpp20_program_blnd_lut,
	.dpp_program_shaper_lut = dpp20_program_shaper,
	.dpp_program_3dlut = dpp20_program_3dlut,
	.dpp_program_bias_and_scale = शून्य,
	.dpp_cnv_set_alpha_keyer = dpp2_cnv_set_alpha_keyer,
	.set_cursor_attributes = dpp2_set_cursor_attributes,
	.set_cursor_position = dpp1_set_cursor_position,
	.set_optional_cursor_attributes = dpp1_cnv_set_optional_cursor_attributes,
	.dpp_dppclk_control = dpp1_dppclk_control,
	.dpp_set_hdr_multiplier = dpp2_set_hdr_multiplier,
पूर्ण;

अटल काष्ठा dpp_caps dcn20_dpp_cap = अणु
	.dscl_data_proc_क्रमmat = DSCL_DATA_PRCESSING_FLOAT_FORMAT,
	.dscl_calc_lb_num_partitions = dscl2_calc_lb_num_partitions,
पूर्ण;

bool dpp2_स्थिरruct(
	काष्ठा dcn20_dpp *dpp,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn2_dpp_रेजिस्टरs *tf_regs,
	स्थिर काष्ठा dcn2_dpp_shअगरt *tf_shअगरt,
	स्थिर काष्ठा dcn2_dpp_mask *tf_mask)
अणु
	dpp->base.ctx = ctx;

	dpp->base.inst = inst;
	dpp->base.funcs = &dcn20_dpp_funcs;
	dpp->base.caps = &dcn20_dpp_cap;

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

