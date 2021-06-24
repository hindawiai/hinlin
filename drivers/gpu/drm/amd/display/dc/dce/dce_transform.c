<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#समावेश "dce_transform.h"
#समावेश "reg_helper.h"
#समावेश "opp.h"
#समावेश "basics/conversion.h"
#समावेश "dc.h"

#घोषणा REG(reg) \
	(xfm_dce->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	xfm_dce->xfm_shअगरt->field_name, xfm_dce->xfm_mask->field_name

#घोषणा CTX \
	xfm_dce->base.ctx
#घोषणा DC_LOGGER \
	xfm_dce->base.ctx->logger

#घोषणा IDENTITY_RATIO(ratio) (dc_fixpt_u2d19(ratio) == (1 << 19))
#घोषणा GAMUT_MATRIX_SIZE 12
#घोषणा SCL_PHASES 16

क्रमागत dcp_out_trunc_round_mode अणु
	DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE,
	DCP_OUT_TRUNC_ROUND_MODE_ROUND
पूर्ण;

क्रमागत dcp_out_trunc_round_depth अणु
	DCP_OUT_TRUNC_ROUND_DEPTH_14BIT,
	DCP_OUT_TRUNC_ROUND_DEPTH_13BIT,
	DCP_OUT_TRUNC_ROUND_DEPTH_12BIT,
	DCP_OUT_TRUNC_ROUND_DEPTH_11BIT,
	DCP_OUT_TRUNC_ROUND_DEPTH_10BIT,
	DCP_OUT_TRUNC_ROUND_DEPTH_9BIT,
	DCP_OUT_TRUNC_ROUND_DEPTH_8BIT
पूर्ण;

/*  defines the various methods of bit reduction available क्रम use */
क्रमागत dcp_bit_depth_reduction_mode अणु
	DCP_BIT_DEPTH_REDUCTION_MODE_DITHER,
	DCP_BIT_DEPTH_REDUCTION_MODE_ROUND,
	DCP_BIT_DEPTH_REDUCTION_MODE_TRUNCATE,
	DCP_BIT_DEPTH_REDUCTION_MODE_DISABLED,
	DCP_BIT_DEPTH_REDUCTION_MODE_INVALID
पूर्ण;

क्रमागत dcp_spatial_dither_mode अणु
	DCP_SPATIAL_DITHER_MODE_AAAA,
	DCP_SPATIAL_DITHER_MODE_A_AA_A,
	DCP_SPATIAL_DITHER_MODE_AABBAABB,
	DCP_SPATIAL_DITHER_MODE_AABBCCAABBCC,
	DCP_SPATIAL_DITHER_MODE_INVALID
पूर्ण;

क्रमागत dcp_spatial_dither_depth अणु
	DCP_SPATIAL_DITHER_DEPTH_30BPP,
	DCP_SPATIAL_DITHER_DEPTH_24BPP
पूर्ण;

क्रमागत csc_color_mode अणु
	/* 00 - BITS2:0 Bypass */
	CSC_COLOR_MODE_GRAPHICS_BYPASS,
	/* 01 - hard coded coefficient TV RGB */
	CSC_COLOR_MODE_GRAPHICS_PREDEFINED,
	/* 04 - programmable OUTPUT CSC coefficient */
	CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC,
पूर्ण;

क्रमागत grph_color_adjust_option अणु
	GRPH_COLOR_MATRIX_HW_DEFAULT = 1,
	GRPH_COLOR_MATRIX_SW
पूर्ण;

अटल स्थिर काष्ठा out_csc_color_matrix global_color_matrix[] = अणु
अणु COLOR_SPACE_SRGB,
	अणु 0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0पूर्ण पूर्ण,
अणु COLOR_SPACE_SRGB_LIMITED,
	अणु 0x1B60, 0, 0, 0x200, 0, 0x1B60, 0, 0x200, 0, 0, 0x1B60, 0x200पूर्ण पूर्ण,
अणु COLOR_SPACE_YCBCR601,
	अणु 0xE00, 0xF447, 0xFDB9, 0x1000, 0x82F, 0x1012, 0x31F, 0x200, 0xFB47,
		0xF6B9, 0xE00, 0x1000पूर्ण पूर्ण,
अणु COLOR_SPACE_YCBCR709, अणु 0xE00, 0xF349, 0xFEB7, 0x1000, 0x5D2, 0x1394, 0x1FA,
	0x200, 0xFCCB, 0xF535, 0xE00, 0x1000पूर्ण पूर्ण,
/* TODO: correct values below */
अणु COLOR_SPACE_YCBCR601_LIMITED, अणु 0xE00, 0xF447, 0xFDB9, 0x1000, 0x991,
	0x12C9, 0x3A6, 0x200, 0xFB47, 0xF6B9, 0xE00, 0x1000पूर्ण पूर्ण,
अणु COLOR_SPACE_YCBCR709_LIMITED, अणु 0xE00, 0xF349, 0xFEB7, 0x1000, 0x6CE, 0x16E3,
	0x24F, 0x200, 0xFCCB, 0xF535, 0xE00, 0x1000पूर्ण पूर्ण
पूर्ण;

अटल bool setup_scaling_configuration(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा scaler_data *data)
अणु
	REG_SET(SCL_BYPASS_CONTROL, 0, SCL_BYPASS_MODE, 0);

	अगर (data->taps.h_taps + data->taps.v_taps <= 2) अणु
		/* Set bypass */
		अगर (xfm_dce->xfm_mask->SCL_PSCL_EN != 0)
			REG_UPDATE_2(SCL_MODE, SCL_MODE, 0, SCL_PSCL_EN, 0);
		अन्यथा
			REG_UPDATE(SCL_MODE, SCL_MODE, 0);
		वापस false;
	पूर्ण

	REG_SET_2(SCL_TAP_CONTROL, 0,
			SCL_H_NUM_OF_TAPS, data->taps.h_taps - 1,
			SCL_V_NUM_OF_TAPS, data->taps.v_taps - 1);

	अगर (data->क्रमmat <= PIXEL_FORMAT_GRPH_END)
		REG_UPDATE(SCL_MODE, SCL_MODE, 1);
	अन्यथा
		REG_UPDATE(SCL_MODE, SCL_MODE, 2);

	अगर (xfm_dce->xfm_mask->SCL_PSCL_EN != 0)
		REG_UPDATE(SCL_MODE, SCL_PSCL_EN, 1);

	/* 1 - Replace out of bound pixels with edge */
	REG_SET(SCL_CONTROL, 0, SCL_BOUNDARY_MODE, 1);

	वापस true;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल bool dce60_setup_scaling_configuration(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा scaler_data *data)
अणु
	REG_SET(SCL_BYPASS_CONTROL, 0, SCL_BYPASS_MODE, 0);

	अगर (data->taps.h_taps + data->taps.v_taps <= 2) अणु
		/* Set bypass */

		/* DCE6 has no SCL_MODE रेजिस्टर, skip scale mode programming */

		वापस false;
	पूर्ण

	REG_SET_2(SCL_TAP_CONTROL, 0,
			SCL_H_NUM_OF_TAPS, data->taps.h_taps - 1,
			SCL_V_NUM_OF_TAPS, data->taps.v_taps - 1);

	/* DCE6 has no SCL_MODE रेजिस्टर, skip scale mode programming */

	/* DCE6 has no SCL_BOUNDARY_MODE bit, skip replace out of bound pixels */

	वापस true;
पूर्ण
#पूर्ण_अगर

अटल व्योम program_overscan(
		काष्ठा dce_transक्रमm *xfm_dce,
		स्थिर काष्ठा scaler_data *data)
अणु
	पूर्णांक overscan_right = data->h_active
			- data->recout.x - data->recout.width;
	पूर्णांक overscan_bottom = data->v_active
			- data->recout.y - data->recout.height;

	अगर (xfm_dce->base.ctx->dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE) अणु
		overscan_bottom += 2;
		overscan_right += 2;
	पूर्ण

	अगर (overscan_right < 0) अणु
		BREAK_TO_DEBUGGER();
		overscan_right = 0;
	पूर्ण
	अगर (overscan_bottom < 0) अणु
		BREAK_TO_DEBUGGER();
		overscan_bottom = 0;
	पूर्ण

	REG_SET_2(EXT_OVERSCAN_LEFT_RIGHT, 0,
			EXT_OVERSCAN_LEFT, data->recout.x,
			EXT_OVERSCAN_RIGHT, overscan_right);
	REG_SET_2(EXT_OVERSCAN_TOP_BOTTOM, 0,
			EXT_OVERSCAN_TOP, data->recout.y,
			EXT_OVERSCAN_BOTTOM, overscan_bottom);
पूर्ण

अटल व्योम program_multi_taps_filter(
	काष्ठा dce_transक्रमm *xfm_dce,
	पूर्णांक taps,
	स्थिर uपूर्णांक16_t *coeffs,
	क्रमागत ram_filter_type filter_type)
अणु
	पूर्णांक phase, pair;
	पूर्णांक array_idx = 0;
	पूर्णांक taps_pairs = (taps + 1) / 2;
	पूर्णांक phases_to_program = SCL_PHASES / 2 + 1;

	uपूर्णांक32_t घातer_ctl = 0;

	अगर (!coeffs)
		वापस;

	/*We need to disable घातer gating on coeff memory to करो programming*/
	अगर (REG(DCFE_MEM_PWR_CTRL)) अणु
		घातer_ctl = REG_READ(DCFE_MEM_PWR_CTRL);
		REG_SET(DCFE_MEM_PWR_CTRL, घातer_ctl, SCL_COEFF_MEM_PWR_DIS, 1);

		REG_WAIT(DCFE_MEM_PWR_STATUS, SCL_COEFF_MEM_PWR_STATE, 0, 1, 10);
	पूर्ण
	क्रम (phase = 0; phase < phases_to_program; phase++) अणु
		/*we always program N/2 + 1 phases, total phases N, but N/2-1 are just mirror
		phase 0 is unique and phase N/2 is unique अगर N is even*/
		क्रम (pair = 0; pair < taps_pairs; pair++) अणु
			uपूर्णांक16_t odd_coeff = 0;
			uपूर्णांक16_t even_coeff = coeffs[array_idx];

			REG_SET_3(SCL_COEF_RAM_SELECT, 0,
					SCL_C_RAM_FILTER_TYPE, filter_type,
					SCL_C_RAM_PHASE, phase,
					SCL_C_RAM_TAP_PAIR_IDX, pair);

			अगर (taps % 2 && pair == taps_pairs - 1)
				array_idx++;
			अन्यथा अणु
				odd_coeff = coeffs[array_idx + 1];
				array_idx += 2;
			पूर्ण

			REG_SET_4(SCL_COEF_RAM_TAP_DATA, 0,
					SCL_C_RAM_EVEN_TAP_COEF_EN, 1,
					SCL_C_RAM_EVEN_TAP_COEF, even_coeff,
					SCL_C_RAM_ODD_TAP_COEF_EN, 1,
					SCL_C_RAM_ODD_TAP_COEF, odd_coeff);
		पूर्ण
	पूर्ण

	/*We need to restore घातer gating on coeff memory to initial state*/
	अगर (REG(DCFE_MEM_PWR_CTRL))
		REG_WRITE(DCFE_MEM_PWR_CTRL, घातer_ctl);
पूर्ण

अटल व्योम program_viewport(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा rect *view_port)
अणु
	REG_SET_2(VIEWPORT_START, 0,
			VIEWPORT_X_START, view_port->x,
			VIEWPORT_Y_START, view_port->y);

	REG_SET_2(VIEWPORT_SIZE, 0,
			VIEWPORT_HEIGHT, view_port->height,
			VIEWPORT_WIDTH, view_port->width);

	/* TODO: add stereo support */
पूर्ण

अटल व्योम calculate_inits(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा scaler_data *data,
	काष्ठा scl_ratios_inits *inits)
अणु
	काष्ठा fixed31_32 h_init;
	काष्ठा fixed31_32 v_init;

	inits->h_पूर्णांक_scale_ratio =
		dc_fixpt_u2d19(data->ratios.horz) << 5;
	inits->v_पूर्णांक_scale_ratio =
		dc_fixpt_u2d19(data->ratios.vert) << 5;

	h_init =
		dc_fixpt_भाग_पूर्णांक(
			dc_fixpt_add(
				data->ratios.horz,
				dc_fixpt_from_पूर्णांक(data->taps.h_taps + 1)),
				2);
	inits->h_init.पूर्णांकeger = dc_fixpt_न्यूनमान(h_init);
	inits->h_init.fraction = dc_fixpt_u0d19(h_init) << 5;

	v_init =
		dc_fixpt_भाग_पूर्णांक(
			dc_fixpt_add(
				data->ratios.vert,
				dc_fixpt_from_पूर्णांक(data->taps.v_taps + 1)),
				2);
	inits->v_init.पूर्णांकeger = dc_fixpt_न्यूनमान(v_init);
	inits->v_init.fraction = dc_fixpt_u0d19(v_init) << 5;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_calculate_inits(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा scaler_data *data,
	काष्ठा sclh_ratios_inits *inits)
अणु
	काष्ठा fixed31_32 v_init;

	inits->h_पूर्णांक_scale_ratio =
		dc_fixpt_u2d19(data->ratios.horz) << 5;
	inits->v_पूर्णांक_scale_ratio =
		dc_fixpt_u2d19(data->ratios.vert) << 5;

	/* DCE6 h_init_luma setting inspired by DCE110 */
	inits->h_init_luma.पूर्णांकeger = 1;

	/* DCE6 h_init_chroma setting inspired by DCE110 */
	inits->h_init_chroma.पूर्णांकeger = 1;

	v_init =
		dc_fixpt_भाग_पूर्णांक(
			dc_fixpt_add(
				data->ratios.vert,
				dc_fixpt_from_पूर्णांक(data->taps.v_taps + 1)),
				2);
	inits->v_init.पूर्णांकeger = dc_fixpt_न्यूनमान(v_init);
	inits->v_init.fraction = dc_fixpt_u0d19(v_init) << 5;
पूर्ण
#पूर्ण_अगर

अटल व्योम program_scl_ratios_inits(
	काष्ठा dce_transक्रमm *xfm_dce,
	काष्ठा scl_ratios_inits *inits)
अणु

	REG_SET(SCL_HORZ_FILTER_SCALE_RATIO, 0,
			SCL_H_SCALE_RATIO, inits->h_पूर्णांक_scale_ratio);

	REG_SET(SCL_VERT_FILTER_SCALE_RATIO, 0,
			SCL_V_SCALE_RATIO, inits->v_पूर्णांक_scale_ratio);

	REG_SET_2(SCL_HORZ_FILTER_INIT, 0,
			SCL_H_INIT_INT, inits->h_init.पूर्णांकeger,
			SCL_H_INIT_FRAC, inits->h_init.fraction);

	REG_SET_2(SCL_VERT_FILTER_INIT, 0,
			SCL_V_INIT_INT, inits->v_init.पूर्णांकeger,
			SCL_V_INIT_FRAC, inits->v_init.fraction);

	REG_WRITE(SCL_AUTOMATIC_MODE_CONTROL, 0);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_program_scl_ratios_inits(
	काष्ठा dce_transक्रमm *xfm_dce,
	काष्ठा sclh_ratios_inits *inits)
अणु

	REG_SET(SCL_HORZ_FILTER_SCALE_RATIO, 0,
			SCL_H_SCALE_RATIO, inits->h_पूर्णांक_scale_ratio);

	REG_SET(SCL_VERT_FILTER_SCALE_RATIO, 0,
			SCL_V_SCALE_RATIO, inits->v_पूर्णांक_scale_ratio);

	/* DCE6 has SCL_HORZ_FILTER_INIT_RGB_LUMA रेजिस्टर */
	REG_SET_2(SCL_HORZ_FILTER_INIT_RGB_LUMA, 0,
			SCL_H_INIT_INT_RGB_Y, inits->h_init_luma.पूर्णांकeger,
			SCL_H_INIT_FRAC_RGB_Y, inits->h_init_luma.fraction);

	/* DCE6 has SCL_HORZ_FILTER_INIT_CHROMA रेजिस्टर */
	REG_SET_2(SCL_HORZ_FILTER_INIT_CHROMA, 0,
			SCL_H_INIT_INT_CBCR, inits->h_init_chroma.पूर्णांकeger,
			SCL_H_INIT_FRAC_CBCR, inits->h_init_chroma.fraction);

	REG_SET_2(SCL_VERT_FILTER_INIT, 0,
			SCL_V_INIT_INT, inits->v_init.पूर्णांकeger,
			SCL_V_INIT_FRAC, inits->v_init.fraction);

	REG_WRITE(SCL_AUTOMATIC_MODE_CONTROL, 0);
पूर्ण
#पूर्ण_अगर

अटल स्थिर uपूर्णांक16_t *get_filter_coeffs_16p(पूर्णांक taps, काष्ठा fixed31_32 ratio)
अणु
	अगर (taps == 4)
		वापस get_filter_4tap_16p(ratio);
	अन्यथा अगर (taps == 3)
		वापस get_filter_3tap_16p(ratio);
	अन्यथा अगर (taps == 2)
		वापस get_filter_2tap_16p();
	अन्यथा अगर (taps == 1)
		वापस शून्य;
	अन्यथा अणु
		/* should never happen, bug */
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम dce_transक्रमm_set_scaler(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा scaler_data *data)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	bool is_scaling_required;
	bool filter_updated = false;
	स्थिर uपूर्णांक16_t *coeffs_v, *coeffs_h;

	/*Use all three pieces of memory always*/
	REG_SET_2(LB_MEMORY_CTRL, 0,
			LB_MEMORY_CONFIG, 0,
			LB_MEMORY_SIZE, xfm_dce->lb_memory_size);

	/* Clear SCL_F_SHARP_CONTROL value to 0 */
	REG_WRITE(SCL_F_SHARP_CONTROL, 0);

	/* 1. Program overscan */
	program_overscan(xfm_dce, data);

	/* 2. Program taps and configuration */
	is_scaling_required = setup_scaling_configuration(xfm_dce, data);

	अगर (is_scaling_required) अणु
		/* 3. Calculate and program ratio, filter initialization */
		काष्ठा scl_ratios_inits inits = अणु 0 पूर्ण;

		calculate_inits(xfm_dce, data, &inits);

		program_scl_ratios_inits(xfm_dce, &inits);

		coeffs_v = get_filter_coeffs_16p(data->taps.v_taps, data->ratios.vert);
		coeffs_h = get_filter_coeffs_16p(data->taps.h_taps, data->ratios.horz);

		अगर (coeffs_v != xfm_dce->filter_v || coeffs_h != xfm_dce->filter_h) अणु
			/* 4. Program vertical filters */
			अगर (xfm_dce->filter_v == शून्य)
				REG_SET(SCL_VERT_FILTER_CONTROL, 0,
						SCL_V_2TAP_HARDCODE_COEF_EN, 0);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FILTER_TYPE_RGB_Y_VERTICAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FILTER_TYPE_ALPHA_VERTICAL);

			/* 5. Program horizontal filters */
			अगर (xfm_dce->filter_h == शून्य)
				REG_SET(SCL_HORZ_FILTER_CONTROL, 0,
						SCL_H_2TAP_HARDCODE_COEF_EN, 0);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FILTER_TYPE_RGB_Y_HORIZONTAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FILTER_TYPE_ALPHA_HORIZONTAL);

			xfm_dce->filter_v = coeffs_v;
			xfm_dce->filter_h = coeffs_h;
			filter_updated = true;
		पूर्ण
	पूर्ण

	/* 6. Program the viewport */
	program_viewport(xfm_dce, &data->viewport);

	/* 7. Set bit to flip to new coefficient memory */
	अगर (filter_updated)
		REG_UPDATE(SCL_UPDATE, SCL_COEF_UPDATE_COMPLETE, 1);

	REG_UPDATE(LB_DATA_FORMAT, ALPHA_EN, data->lb_params.alpha_en);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_transक्रमm_set_scaler(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा scaler_data *data)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	bool is_scaling_required;
	स्थिर uपूर्णांक16_t *coeffs_v, *coeffs_h;

	/*Use whole line buffer memory always*/
	REG_SET(DC_LB_MEMORY_SPLIT, 0,
		DC_LB_MEMORY_CONFIG, 0);

	REG_SET(DC_LB_MEM_SIZE, 0,
		DC_LB_MEM_SIZE, xfm_dce->lb_memory_size);

	/* Clear SCL_F_SHARP_CONTROL value to 0 */
	REG_WRITE(SCL_F_SHARP_CONTROL, 0);

	/* 1. Program overscan */
	program_overscan(xfm_dce, data);

	/* 2. Program taps and configuration */
	is_scaling_required = dce60_setup_scaling_configuration(xfm_dce, data);

	अगर (is_scaling_required) अणु
		/* 3. Calculate and program ratio, DCE6 filter initialization */
		काष्ठा sclh_ratios_inits inits = अणु 0 पूर्ण;

		/* DCE6 has specअगरic calculate_inits() function */
		dce60_calculate_inits(xfm_dce, data, &inits);

		/* DCE6 has specअगरic program_scl_ratios_inits() function */
		dce60_program_scl_ratios_inits(xfm_dce, &inits);

		coeffs_v = get_filter_coeffs_16p(data->taps.v_taps, data->ratios.vert);
		coeffs_h = get_filter_coeffs_16p(data->taps.h_taps, data->ratios.horz);

		अगर (coeffs_v != xfm_dce->filter_v || coeffs_h != xfm_dce->filter_h) अणु
			/* 4. Program vertical filters */
			अगर (xfm_dce->filter_v == शून्य)
				REG_SET(SCL_VERT_FILTER_CONTROL, 0,
						SCL_V_2TAP_HARDCODE_COEF_EN, 0);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FILTER_TYPE_RGB_Y_VERTICAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FILTER_TYPE_ALPHA_VERTICAL);

			/* 5. Program horizontal filters */
			अगर (xfm_dce->filter_h == शून्य)
				REG_SET(SCL_HORZ_FILTER_CONTROL, 0,
						SCL_H_2TAP_HARDCODE_COEF_EN, 0);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FILTER_TYPE_RGB_Y_HORIZONTAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FILTER_TYPE_ALPHA_HORIZONTAL);

			xfm_dce->filter_v = coeffs_v;
			xfm_dce->filter_h = coeffs_h;
		पूर्ण
	पूर्ण

	/* 6. Program the viewport */
	program_viewport(xfm_dce, &data->viewport);

	/* DCE6 has no SCL_COEF_UPDATE_COMPLETE bit to flip to new coefficient memory */

	/* DCE6 DATA_FORMAT रेजिस्टर करोes not support ALPHA_EN */
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * set_clamp
 *
 * @param depth : bit depth to set the clamp to (should match denorm)
 *
 * @brief
 *     Programs clamp according to panel bit depth.
 *
 *******************************************************************************/
अटल व्योम set_clamp(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत dc_color_depth depth)
अणु
	पूर्णांक clamp_max = 0;

	/* At the clamp block the data will be MSB aligned, so we set the max
	 * clamp accordingly.
	 * For example, the max value क्रम 6 bits MSB aligned (14 bit bus) would
	 * be "11 1111 0000 0000" in binary, so 0x3F00.
	 */
	चयन (depth) अणु
	हाल COLOR_DEPTH_666:
		/* 6bit MSB aligned on 14 bit bus '11 1111 0000 0000' */
		clamp_max = 0x3F00;
		अवरोध;
	हाल COLOR_DEPTH_888:
		/* 8bit MSB aligned on 14 bit bus '11 1111 1100 0000' */
		clamp_max = 0x3FC0;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		/* 10bit MSB aligned on 14 bit bus '11 1111 1111 0000' */
		clamp_max = 0x3FF0;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		/* 12bit MSB aligned on 14 bit bus '11 1111 1111 1100' */
		clamp_max = 0x3FFC;
		अवरोध;
	शेष:
		clamp_max = 0x3FC0;
		BREAK_TO_DEBUGGER(); /* Invalid clamp bit depth */
	पूर्ण
	REG_SET_2(OUT_CLAMP_CONTROL_B_CB, 0,
			OUT_CLAMP_MIN_B_CB, 0,
			OUT_CLAMP_MAX_B_CB, clamp_max);

	REG_SET_2(OUT_CLAMP_CONTROL_G_Y, 0,
			OUT_CLAMP_MIN_G_Y, 0,
			OUT_CLAMP_MAX_G_Y, clamp_max);

	REG_SET_2(OUT_CLAMP_CONTROL_R_CR, 0,
			OUT_CLAMP_MIN_R_CR, 0,
			OUT_CLAMP_MAX_R_CR, clamp_max);
पूर्ण

/*******************************************************************************
 * set_round
 *
 * @brief
 *     Programs Round/Truncate
 *
 * @param [in] mode  :round or truncate
 * @param [in] depth :bit depth to round/truncate to
 OUT_ROUND_TRUNC_MODE 3:0 0xA Output data round or truncate mode
 POSSIBLE VALUES:
      00 - truncate to u0.12
      01 - truncate to u0.11
      02 - truncate to u0.10
      03 - truncate to u0.9
      04 - truncate to u0.8
      05 - reserved
      06 - truncate to u0.14
      07 - truncate to u0.13		set_reg_field_value(
			value,
			clamp_max,
			OUT_CLAMP_CONTROL_R_CR,
			OUT_CLAMP_MAX_R_CR);
      08 - round to u0.12
      09 - round to u0.11
      10 - round to u0.10
      11 - round to u0.9
      12 - round to u0.8
      13 - reserved
      14 - round to u0.14
      15 - round to u0.13

 ******************************************************************************/
अटल व्योम set_round(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत dcp_out_trunc_round_mode mode,
	क्रमागत dcp_out_trunc_round_depth depth)
अणु
	पूर्णांक depth_bits = 0;
	पूर्णांक mode_bit = 0;

	/*  set up bit depth */
	चयन (depth) अणु
	हाल DCP_OUT_TRUNC_ROUND_DEPTH_14BIT:
		depth_bits = 6;
		अवरोध;
	हाल DCP_OUT_TRUNC_ROUND_DEPTH_13BIT:
		depth_bits = 7;
		अवरोध;
	हाल DCP_OUT_TRUNC_ROUND_DEPTH_12BIT:
		depth_bits = 0;
		अवरोध;
	हाल DCP_OUT_TRUNC_ROUND_DEPTH_11BIT:
		depth_bits = 1;
		अवरोध;
	हाल DCP_OUT_TRUNC_ROUND_DEPTH_10BIT:
		depth_bits = 2;
		अवरोध;
	हाल DCP_OUT_TRUNC_ROUND_DEPTH_9BIT:
		depth_bits = 3;
		अवरोध;
	हाल DCP_OUT_TRUNC_ROUND_DEPTH_8BIT:
		depth_bits = 4;
		अवरोध;
	शेष:
		depth_bits = 4;
		BREAK_TO_DEBUGGER(); /* Invalid dcp_out_trunc_round_depth */
	पूर्ण

	/*  set up round or truncate */
	चयन (mode) अणु
	हाल DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE:
		mode_bit = 0;
		अवरोध;
	हाल DCP_OUT_TRUNC_ROUND_MODE_ROUND:
		mode_bit = 1;
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER(); /* Invalid dcp_out_trunc_round_mode */
	पूर्ण

	depth_bits |= mode_bit << 3;

	REG_SET(OUT_ROUND_CONTROL, 0, OUT_ROUND_TRUNC_MODE, depth_bits);
पूर्ण

/*****************************************************************************
 * set_dither
 *
 * @brief
 *     Programs Dither
 *
 * @param [in] dither_enable        : enable dither
 * @param [in] dither_mode           : dither mode to set
 * @param [in] dither_depth          : bit depth to dither to
 * @param [in] frame_अक्रमom_enable    : enable frame अक्रमom
 * @param [in] rgb_अक्रमom_enable      : enable rgb अक्रमom
 * @param [in] highpass_अक्रमom_enable : enable highpass अक्रमom
 *
 ******************************************************************************/

अटल व्योम set_dither(
	काष्ठा dce_transक्रमm *xfm_dce,
	bool dither_enable,
	क्रमागत dcp_spatial_dither_mode dither_mode,
	क्रमागत dcp_spatial_dither_depth dither_depth,
	bool frame_अक्रमom_enable,
	bool rgb_अक्रमom_enable,
	bool highpass_अक्रमom_enable)
अणु
	पूर्णांक dither_depth_bits = 0;
	पूर्णांक dither_mode_bits = 0;

	चयन (dither_mode) अणु
	हाल DCP_SPATIAL_DITHER_MODE_AAAA:
		dither_mode_bits = 0;
		अवरोध;
	हाल DCP_SPATIAL_DITHER_MODE_A_AA_A:
		dither_mode_bits = 1;
		अवरोध;
	हाल DCP_SPATIAL_DITHER_MODE_AABBAABB:
		dither_mode_bits = 2;
		अवरोध;
	हाल DCP_SPATIAL_DITHER_MODE_AABBCCAABBCC:
		dither_mode_bits = 3;
		अवरोध;
	शेष:
		/* Invalid dcp_spatial_dither_mode */
		BREAK_TO_DEBUGGER();
	पूर्ण

	चयन (dither_depth) अणु
	हाल DCP_SPATIAL_DITHER_DEPTH_30BPP:
		dither_depth_bits = 0;
		अवरोध;
	हाल DCP_SPATIAL_DITHER_DEPTH_24BPP:
		dither_depth_bits = 1;
		अवरोध;
	शेष:
		/* Invalid dcp_spatial_dither_depth */
		BREAK_TO_DEBUGGER();
	पूर्ण

	/*  ग_लिखो the रेजिस्टर */
	REG_SET_6(DCP_SPATIAL_DITHER_CNTL, 0,
			DCP_SPATIAL_DITHER_EN, dither_enable,
			DCP_SPATIAL_DITHER_MODE, dither_mode_bits,
			DCP_SPATIAL_DITHER_DEPTH, dither_depth_bits,
			DCP_FRAME_RANDOM_ENABLE, frame_अक्रमom_enable,
			DCP_RGB_RANDOM_ENABLE, rgb_अक्रमom_enable,
			DCP_HIGHPASS_RANDOM_ENABLE, highpass_अक्रमom_enable);
पूर्ण

/*****************************************************************************
 * dce_transक्रमm_bit_depth_reduction_program
 *
 * @brief
 *     Programs the DCP bit depth reduction रेजिस्टरs (Clamp, Round/Truncate,
 *      Dither) क्रम dce
 *
 * @param depth : bit depth to set the clamp to (should match denorm)
 *
 ******************************************************************************/
अटल व्योम program_bit_depth_reduction(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत dc_color_depth depth,
	स्थिर काष्ठा bit_depth_reduction_params *bit_depth_params)
अणु
	क्रमागत dcp_out_trunc_round_depth trunc_round_depth;
	क्रमागत dcp_out_trunc_round_mode trunc_mode;
	bool spatial_dither_enable;

	ASSERT(depth < COLOR_DEPTH_121212); /* Invalid clamp bit depth */

	spatial_dither_enable = bit_depth_params->flags.SPATIAL_DITHER_ENABLED;
	/* Default to 12 bit truncation without rounding */
	trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_12BIT;
	trunc_mode = DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE;

	अगर (bit_depth_params->flags.TRUNCATE_ENABLED) अणु
		/* Don't enable dithering अगर truncation is enabled */
		spatial_dither_enable = false;
		trunc_mode = bit_depth_params->flags.TRUNCATE_MODE ?
			     DCP_OUT_TRUNC_ROUND_MODE_ROUND :
			     DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE;

		अगर (bit_depth_params->flags.TRUNCATE_DEPTH == 0 ||
		    bit_depth_params->flags.TRUNCATE_DEPTH == 1)
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_8BIT;
		अन्यथा अगर (bit_depth_params->flags.TRUNCATE_DEPTH == 2)
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_10BIT;
		अन्यथा अणु
			/*
			 * Invalid truncate/round depth. Setting here to 12bit
			 * to prevent use-beक्रमe-initialize errors.
			 */
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_12BIT;
			BREAK_TO_DEBUGGER();
		पूर्ण
	पूर्ण

	set_clamp(xfm_dce, depth);
	set_round(xfm_dce, trunc_mode, trunc_round_depth);
	set_dither(xfm_dce,
		   spatial_dither_enable,
		   DCP_SPATIAL_DITHER_MODE_A_AA_A,
		   DCP_SPATIAL_DITHER_DEPTH_30BPP,
		   bit_depth_params->flags.FRAME_RANDOM,
		   bit_depth_params->flags.RGB_RANDOM,
		   bit_depth_params->flags.HIGHPASS_RANDOM);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
/*****************************************************************************
 * dce60_transक्रमm_bit_depth_reduction program
 *
 * @brief
 *     Programs the DCP bit depth reduction रेजिस्टरs (Clamp, Round/Truncate,
 *      Dither) क्रम dce
 *
 * @param depth : bit depth to set the clamp to (should match denorm)
 *
 ******************************************************************************/
अटल व्योम dce60_program_bit_depth_reduction(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत dc_color_depth depth,
	स्थिर काष्ठा bit_depth_reduction_params *bit_depth_params)
अणु
	क्रमागत dcp_out_trunc_round_depth trunc_round_depth;
	क्रमागत dcp_out_trunc_round_mode trunc_mode;
	bool spatial_dither_enable;

	ASSERT(depth < COLOR_DEPTH_121212); /* Invalid clamp bit depth */

	spatial_dither_enable = bit_depth_params->flags.SPATIAL_DITHER_ENABLED;
	/* Default to 12 bit truncation without rounding */
	trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_12BIT;
	trunc_mode = DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE;

	अगर (bit_depth_params->flags.TRUNCATE_ENABLED) अणु
		/* Don't enable dithering अगर truncation is enabled */
		spatial_dither_enable = false;
		trunc_mode = bit_depth_params->flags.TRUNCATE_MODE ?
			     DCP_OUT_TRUNC_ROUND_MODE_ROUND :
			     DCP_OUT_TRUNC_ROUND_MODE_TRUNCATE;

		अगर (bit_depth_params->flags.TRUNCATE_DEPTH == 0 ||
		    bit_depth_params->flags.TRUNCATE_DEPTH == 1)
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_8BIT;
		अन्यथा अगर (bit_depth_params->flags.TRUNCATE_DEPTH == 2)
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_10BIT;
		अन्यथा अणु
			/*
			 * Invalid truncate/round depth. Setting here to 12bit
			 * to prevent use-beक्रमe-initialize errors.
			 */
			trunc_round_depth = DCP_OUT_TRUNC_ROUND_DEPTH_12BIT;
			BREAK_TO_DEBUGGER();
		पूर्ण
	पूर्ण

	/* DCE6 has no OUT_CLAMP_CONTROL_* रेजिस्टरs - set_clamp() is skipped */
	set_round(xfm_dce, trunc_mode, trunc_round_depth);
	set_dither(xfm_dce,
		   spatial_dither_enable,
		   DCP_SPATIAL_DITHER_MODE_A_AA_A,
		   DCP_SPATIAL_DITHER_DEPTH_30BPP,
		   bit_depth_params->flags.FRAME_RANDOM,
		   bit_depth_params->flags.RGB_RANDOM,
		   bit_depth_params->flags.HIGHPASS_RANDOM);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dce_transक्रमm_get_max_num_of_supported_lines(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत lb_pixel_depth depth,
	पूर्णांक pixel_width)
अणु
	पूर्णांक pixels_per_entries = 0;
	पूर्णांक max_pixels_supports = 0;

	ASSERT(pixel_width);

	/* Find number of pixels that can fit पूर्णांकo a single LB entry and
	 * take न्यूनमान of the value since we cannot store a single pixel
	 * across multiple entries. */
	चयन (depth) अणु
	हाल LB_PIXEL_DEPTH_18BPP:
		pixels_per_entries = xfm_dce->lb_bits_per_entry / 18;
		अवरोध;

	हाल LB_PIXEL_DEPTH_24BPP:
		pixels_per_entries = xfm_dce->lb_bits_per_entry / 24;
		अवरोध;

	हाल LB_PIXEL_DEPTH_30BPP:
		pixels_per_entries = xfm_dce->lb_bits_per_entry / 30;
		अवरोध;

	हाल LB_PIXEL_DEPTH_36BPP:
		pixels_per_entries = xfm_dce->lb_bits_per_entry / 36;
		अवरोध;

	शेष:
		DC_LOG_WARNING("%s: Invalid LB pixel depth",
			__func__);
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	ASSERT(pixels_per_entries);

	max_pixels_supports =
			pixels_per_entries *
			xfm_dce->lb_memory_size;

	वापस (max_pixels_supports / pixel_width);
पूर्ण

अटल व्योम set_denormalization(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत dc_color_depth depth)
अणु
	पूर्णांक denorm_mode = 0;

	चयन (depth) अणु
	हाल COLOR_DEPTH_666:
		/* 63/64 क्रम 6 bit output color depth */
		denorm_mode = 1;
		अवरोध;
	हाल COLOR_DEPTH_888:
		/* Unity क्रम 8 bit output color depth
		 * because prescale is disabled by शेष */
		denorm_mode = 0;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		/* 1023/1024 क्रम 10 bit output color depth */
		denorm_mode = 3;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		/* 4095/4096 क्रम 12 bit output color depth */
		denorm_mode = 5;
		अवरोध;
	हाल COLOR_DEPTH_141414:
	हाल COLOR_DEPTH_161616:
	शेष:
		/* not valid used हाल! */
		अवरोध;
	पूर्ण

	REG_SET(DENORM_CONTROL, 0, DENORM_MODE, denorm_mode);
पूर्ण

अटल व्योम dce_transक्रमm_set_pixel_storage_depth(
	काष्ठा transक्रमm *xfm,
	क्रमागत lb_pixel_depth depth,
	स्थिर काष्ठा bit_depth_reduction_params *bit_depth_params)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	पूर्णांक pixel_depth, expan_mode;
	क्रमागत dc_color_depth color_depth;

	चयन (depth) अणु
	हाल LB_PIXEL_DEPTH_18BPP:
		color_depth = COLOR_DEPTH_666;
		pixel_depth = 2;
		expan_mode  = 1;
		अवरोध;
	हाल LB_PIXEL_DEPTH_24BPP:
		color_depth = COLOR_DEPTH_888;
		pixel_depth = 1;
		expan_mode  = 1;
		अवरोध;
	हाल LB_PIXEL_DEPTH_30BPP:
		color_depth = COLOR_DEPTH_101010;
		pixel_depth = 0;
		expan_mode  = 1;
		अवरोध;
	हाल LB_PIXEL_DEPTH_36BPP:
		color_depth = COLOR_DEPTH_121212;
		pixel_depth = 3;
		expan_mode  = 0;
		अवरोध;
	शेष:
		color_depth = COLOR_DEPTH_101010;
		pixel_depth = 0;
		expan_mode  = 1;
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	set_denormalization(xfm_dce, color_depth);
	program_bit_depth_reduction(xfm_dce, color_depth, bit_depth_params);

	REG_UPDATE_2(LB_DATA_FORMAT,
			PIXEL_DEPTH, pixel_depth,
			PIXEL_EXPAN_MODE, expan_mode);

	अगर (!(xfm_dce->lb_pixel_depth_supported & depth)) अणु
		/*we should use unsupported capabilities
		 *  unless it is required by w/a*/
		DC_LOG_WARNING("%s: Capability not supported",
			__func__);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_transक्रमm_set_pixel_storage_depth(
	काष्ठा transक्रमm *xfm,
	क्रमागत lb_pixel_depth depth,
	स्थिर काष्ठा bit_depth_reduction_params *bit_depth_params)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	क्रमागत dc_color_depth color_depth;

	चयन (depth) अणु
	हाल LB_PIXEL_DEPTH_18BPP:
		color_depth = COLOR_DEPTH_666;
		अवरोध;
	हाल LB_PIXEL_DEPTH_24BPP:
		color_depth = COLOR_DEPTH_888;
		अवरोध;
	हाल LB_PIXEL_DEPTH_30BPP:
		color_depth = COLOR_DEPTH_101010;
		अवरोध;
	हाल LB_PIXEL_DEPTH_36BPP:
		color_depth = COLOR_DEPTH_121212;
		अवरोध;
	शेष:
		color_depth = COLOR_DEPTH_101010;
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	set_denormalization(xfm_dce, color_depth);
	dce60_program_bit_depth_reduction(xfm_dce, color_depth, bit_depth_params);

	/* DATA_FORMAT in DCE6 करोes not have PIXEL_DEPTH and PIXEL_EXPAN_MODE masks */

	अगर (!(xfm_dce->lb_pixel_depth_supported & depth)) अणु
		/*we should use unsupported capabilities
		 *  unless it is required by w/a*/
		DC_LOG_WARNING("%s: Capability not supported",
			__func__);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम program_gamut_remap(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर uपूर्णांक16_t *reg_val)
अणु
	अगर (reg_val) अणु
		REG_SET_2(GAMUT_REMAP_C11_C12, 0,
				GAMUT_REMAP_C11, reg_val[0],
				GAMUT_REMAP_C12, reg_val[1]);
		REG_SET_2(GAMUT_REMAP_C13_C14, 0,
				GAMUT_REMAP_C13, reg_val[2],
				GAMUT_REMAP_C14, reg_val[3]);
		REG_SET_2(GAMUT_REMAP_C21_C22, 0,
				GAMUT_REMAP_C21, reg_val[4],
				GAMUT_REMAP_C22, reg_val[5]);
		REG_SET_2(GAMUT_REMAP_C23_C24, 0,
				GAMUT_REMAP_C23, reg_val[6],
				GAMUT_REMAP_C24, reg_val[7]);
		REG_SET_2(GAMUT_REMAP_C31_C32, 0,
				GAMUT_REMAP_C31, reg_val[8],
				GAMUT_REMAP_C32, reg_val[9]);
		REG_SET_2(GAMUT_REMAP_C33_C34, 0,
				GAMUT_REMAP_C33, reg_val[10],
				GAMUT_REMAP_C34, reg_val[11]);

		REG_SET(GAMUT_REMAP_CONTROL, 0, GRPH_GAMUT_REMAP_MODE, 1);
	पूर्ण अन्यथा
		REG_SET(GAMUT_REMAP_CONTROL, 0, GRPH_GAMUT_REMAP_MODE, 0);

पूर्ण

/*
 *****************************************************************************
 *  Function: dal_transक्रमm_wide_gamut_set_gamut_remap
 *
 *  @param [in] स्थिर काष्ठा xfm_grph_csc_adjusपंचांगent *adjust
 *
 *  @वापस
 *     व्योम
 *
 *  @note calculate and apply color temperature adjusपंचांगent to in Rgb color space
 *
 *  @see
 *
 *****************************************************************************
 */
अटल व्योम dce_transक्रमm_set_gamut_remap(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा xfm_grph_csc_adjusपंचांगent *adjust)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	पूर्णांक i = 0;

	अगर (adjust->gamut_adjust_type != GRAPHICS_GAMUT_ADJUST_TYPE_SW)
		/* Bypass अगर type is bypass or hw */
		program_gamut_remap(xfm_dce, शून्य);
	अन्यथा अणु
		काष्ठा fixed31_32 arr_matrix[GAMUT_MATRIX_SIZE];
		uपूर्णांक16_t arr_reg_val[GAMUT_MATRIX_SIZE];

		क्रम (i = 0; i < GAMUT_MATRIX_SIZE; i++)
			arr_matrix[i] = adjust->temperature_matrix[i];

		convert_भग्न_matrix(
			arr_reg_val, arr_matrix, GAMUT_MATRIX_SIZE);

		program_gamut_remap(xfm_dce, arr_reg_val);
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t decide_taps(काष्ठा fixed31_32 ratio, uपूर्णांक32_t in_taps, bool chroma)
अणु
	uपूर्णांक32_t taps;

	अगर (IDENTITY_RATIO(ratio)) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (in_taps != 0) अणु
		taps = in_taps;
	पूर्ण अन्यथा अणु
		taps = 4;
	पूर्ण

	अगर (chroma) अणु
		taps /= 2;
		अगर (taps < 2)
			taps = 2;
	पूर्ण

	वापस taps;
पूर्ण


bool dce_transक्रमm_get_optimal_number_of_taps(
	काष्ठा transक्रमm *xfm,
	काष्ठा scaler_data *scl_data,
	स्थिर काष्ठा scaling_taps *in_taps)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	पूर्णांक pixel_width = scl_data->viewport.width;
	पूर्णांक max_num_of_lines;

	अगर (xfm_dce->prescaler_on &&
			(scl_data->viewport.width > scl_data->recout.width))
		pixel_width = scl_data->recout.width;

	max_num_of_lines = dce_transक्रमm_get_max_num_of_supported_lines(
		xfm_dce,
		scl_data->lb_params.depth,
		pixel_width);

	/* Fail अगर in_taps are impossible */
	अगर (in_taps->v_taps >= max_num_of_lines)
		वापस false;

	/*
	 * Set taps according to this policy (in this order)
	 * - Use 1 क्रम no scaling
	 * - Use input taps
	 * - Use 4 and reduce as required by line buffer size
	 * - Decide chroma taps अगर chroma is scaled
	 *
	 * Ignore input chroma taps. Decide based on non-chroma
	 */
	scl_data->taps.h_taps = decide_taps(scl_data->ratios.horz, in_taps->h_taps, false);
	scl_data->taps.v_taps = decide_taps(scl_data->ratios.vert, in_taps->v_taps, false);
	scl_data->taps.h_taps_c = decide_taps(scl_data->ratios.horz_c, in_taps->h_taps, true);
	scl_data->taps.v_taps_c = decide_taps(scl_data->ratios.vert_c, in_taps->v_taps, true);

	अगर (!IDENTITY_RATIO(scl_data->ratios.vert)) अणु
		/* reduce v_taps अगर needed but ensure we have at least two */
		अगर (in_taps->v_taps == 0
				&& max_num_of_lines <= scl_data->taps.v_taps
				&& scl_data->taps.v_taps > 1) अणु
			scl_data->taps.v_taps = max_num_of_lines - 1;
		पूर्ण

		अगर (scl_data->taps.v_taps <= 1)
			वापस false;
	पूर्ण

	अगर (!IDENTITY_RATIO(scl_data->ratios.vert_c)) अणु
		/* reduce chroma v_taps अगर needed but ensure we have at least two */
		अगर (max_num_of_lines <= scl_data->taps.v_taps_c && scl_data->taps.v_taps_c > 1) अणु
			scl_data->taps.v_taps_c = max_num_of_lines - 1;
		पूर्ण

		अगर (scl_data->taps.v_taps_c <= 1)
			वापस false;
	पूर्ण

	/* we've got valid taps */
	वापस true;
पूर्ण

अटल व्योम dce_transक्रमm_reset(काष्ठा transक्रमm *xfm)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);

	xfm_dce->filter_h = शून्य;
	xfm_dce->filter_v = शून्य;
पूर्ण

अटल व्योम program_color_matrix(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा out_csc_color_matrix *tbl_entry,
	क्रमागत grph_color_adjust_option options)
अणु
	अणु
		REG_SET_2(OUTPUT_CSC_C11_C12, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[0],
			OUTPUT_CSC_C12, tbl_entry->regval[1]);
	पूर्ण
	अणु
		REG_SET_2(OUTPUT_CSC_C13_C14, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[2],
			OUTPUT_CSC_C12, tbl_entry->regval[3]);
	पूर्ण
	अणु
		REG_SET_2(OUTPUT_CSC_C21_C22, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[4],
			OUTPUT_CSC_C12, tbl_entry->regval[5]);
	पूर्ण
	अणु
		REG_SET_2(OUTPUT_CSC_C23_C24, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[6],
			OUTPUT_CSC_C12, tbl_entry->regval[7]);
	पूर्ण
	अणु
		REG_SET_2(OUTPUT_CSC_C31_C32, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[8],
			OUTPUT_CSC_C12, tbl_entry->regval[9]);
	पूर्ण
	अणु
		REG_SET_2(OUTPUT_CSC_C33_C34, 0,
			OUTPUT_CSC_C11, tbl_entry->regval[10],
			OUTPUT_CSC_C12, tbl_entry->regval[11]);
	पूर्ण
पूर्ण

अटल bool configure_graphics_mode(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत csc_color_mode config,
	क्रमागत graphics_csc_adjust_type csc_adjust_type,
	क्रमागत dc_color_space color_space)
अणु
	REG_SET(OUTPUT_CSC_CONTROL, 0,
		OUTPUT_CSC_GRPH_MODE, 0);

	अगर (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_SW) अणु
		अगर (config == CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC) अणु
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 4);
		पूर्ण अन्यथा अणु

			चयन (color_space) अणु
			हाल COLOR_SPACE_SRGB:
				/* by pass */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 0);
				अवरोध;
			हाल COLOR_SPACE_SRGB_LIMITED:
				/* TV RGB */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 1);
				अवरोध;
			हाल COLOR_SPACE_YCBCR601:
			हाल COLOR_SPACE_YCBCR601_LIMITED:
				/* YCbCr601 */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 2);
				अवरोध;
			हाल COLOR_SPACE_YCBCR709:
			हाल COLOR_SPACE_YCBCR709_LIMITED:
				/* YCbCr709 */
				REG_SET(OUTPUT_CSC_CONTROL, 0,
					OUTPUT_CSC_GRPH_MODE, 3);
				अवरोध;
			शेष:
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_HW) अणु
		चयन (color_space) अणु
		हाल COLOR_SPACE_SRGB:
			/* by pass */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 0);
			अवरोध;
		हाल COLOR_SPACE_SRGB_LIMITED:
			/* TV RGB */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 1);
			अवरोध;
		हाल COLOR_SPACE_YCBCR601:
		हाल COLOR_SPACE_YCBCR601_LIMITED:
			/* YCbCr601 */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 2);
			अवरोध;
		हाल COLOR_SPACE_YCBCR709:
		हाल COLOR_SPACE_YCBCR709_LIMITED:
			 /* YCbCr709 */
			REG_SET(OUTPUT_CSC_CONTROL, 0,
				OUTPUT_CSC_GRPH_MODE, 3);
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

	पूर्ण अन्यथा
		/* by pass */
		REG_SET(OUTPUT_CSC_CONTROL, 0,
			OUTPUT_CSC_GRPH_MODE, 0);

	वापस true;
पूर्ण

व्योम dce110_opp_set_csc_adjusपंचांगent(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा out_csc_color_matrix *tbl_entry)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	क्रमागत csc_color_mode config =
			CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC;

	program_color_matrix(
			xfm_dce, tbl_entry, GRPH_COLOR_MATRIX_SW);

	/*  We did everything ,now program DxOUTPUT_CSC_CONTROL */
	configure_graphics_mode(xfm_dce, config, GRAPHICS_CSC_ADJUST_TYPE_SW,
			tbl_entry->color_space);
पूर्ण

व्योम dce110_opp_set_csc_शेष(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा शेष_adjusपंचांगent *शेष_adjust)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	क्रमागत csc_color_mode config =
			CSC_COLOR_MODE_GRAPHICS_PREDEFINED;

	अगर (शेष_adjust->क्रमce_hw_शेष == false) अणु
		स्थिर काष्ठा out_csc_color_matrix *elm;
		/* currently parameter not in use */
		क्रमागत grph_color_adjust_option option =
			GRPH_COLOR_MATRIX_HW_DEFAULT;
		uपूर्णांक32_t i;
		/*
		 * HW शेष false we program locally defined matrix
		 * HW शेष true  we use predefined hw matrix and we
		 * करो not need to program matrix
		 * OEM wants the HW शेष via runसमय parameter.
		 */
		option = GRPH_COLOR_MATRIX_SW;

		क्रम (i = 0; i < ARRAY_SIZE(global_color_matrix); ++i) अणु
			elm = &global_color_matrix[i];
			अगर (elm->color_space != शेष_adjust->out_color_space)
				जारी;
			/* program the matrix with शेष values from this
			 * file */
			program_color_matrix(xfm_dce, elm, option);
			config = CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC;
			अवरोध;
		पूर्ण
	पूर्ण

	/* configure the what we programmed :
	 * 1. Default values from this file
	 * 2. Use hardware शेष from ROM_A and we करो not need to program
	 * matrix */

	configure_graphics_mode(xfm_dce, config,
		शेष_adjust->csc_adjust_type,
		शेष_adjust->out_color_space);
पूर्ण

अटल व्योम program_pwl(काष्ठा dce_transक्रमm *xfm_dce,
			स्थिर काष्ठा pwl_params *params)
अणु
	पूर्णांक retval;
	uपूर्णांक8_t max_tries = 10;
	uपूर्णांक8_t counter = 0;
	uपूर्णांक32_t i = 0;
	स्थिर काष्ठा pwl_result_data *rgb = params->rgb_resulted;

	/* Power on LUT memory */
	अगर (REG(DCFE_MEM_PWR_CTRL))
		REG_UPDATE(DCFE_MEM_PWR_CTRL,
			   DCP_REGAMMA_MEM_PWR_DIS, 1);
	अन्यथा
		REG_UPDATE(DCFE_MEM_LIGHT_SLEEP_CNTL,
			   REGAMMA_LUT_LIGHT_SLEEP_DIS, 1);

	जबतक (counter < max_tries) अणु
		अगर (REG(DCFE_MEM_PWR_STATUS)) अणु
			REG_GET(DCFE_MEM_PWR_STATUS,
				DCP_REGAMMA_MEM_PWR_STATE,
				&retval);

			अगर (retval == 0)
				अवरोध;
			++counter;
		पूर्ण अन्यथा अणु
			REG_GET(DCFE_MEM_LIGHT_SLEEP_CNTL,
				REGAMMA_LUT_MEM_PWR_STATE,
				&retval);

			अगर (retval == 0)
				अवरोध;
			++counter;
		पूर्ण
	पूर्ण

	अगर (counter == max_tries) अणु
		DC_LOG_WARNING("%s: regamma lut was not powered on "
				"in a timely manner,"
				" programming still proceeds\n",
				__func__);
	पूर्ण

	REG_UPDATE(REGAMMA_LUT_WRITE_EN_MASK,
		   REGAMMA_LUT_WRITE_EN_MASK, 7);

	REG_WRITE(REGAMMA_LUT_INDEX, 0);

	/* Program REGAMMA_LUT_DATA */
	जबतक (i != params->hw_poपूर्णांकs_num) अणु

		REG_WRITE(REGAMMA_LUT_DATA, rgb->red_reg);
		REG_WRITE(REGAMMA_LUT_DATA, rgb->green_reg);
		REG_WRITE(REGAMMA_LUT_DATA, rgb->blue_reg);
		REG_WRITE(REGAMMA_LUT_DATA, rgb->delta_red_reg);
		REG_WRITE(REGAMMA_LUT_DATA, rgb->delta_green_reg);
		REG_WRITE(REGAMMA_LUT_DATA, rgb->delta_blue_reg);

		++rgb;
		++i;
	पूर्ण

	/*  we are करोne with DCP LUT memory; re-enable low घातer mode */
	अगर (REG(DCFE_MEM_PWR_CTRL))
		REG_UPDATE(DCFE_MEM_PWR_CTRL,
			   DCP_REGAMMA_MEM_PWR_DIS, 0);
	अन्यथा
		REG_UPDATE(DCFE_MEM_LIGHT_SLEEP_CNTL,
			   REGAMMA_LUT_LIGHT_SLEEP_DIS, 0);
पूर्ण

अटल व्योम regamma_config_regions_and_segments(काष्ठा dce_transक्रमm *xfm_dce,
						स्थिर काष्ठा pwl_params *params)
अणु
	स्थिर काष्ठा gamma_curve *curve;

	REG_SET_2(REGAMMA_CNTLA_START_CNTL, 0,
		  REGAMMA_CNTLA_EXP_REGION_START, params->arr_poपूर्णांकs[0].custom_भग्न_x,
		  REGAMMA_CNTLA_EXP_REGION_START_SEGMENT, 0);

	REG_SET(REGAMMA_CNTLA_SLOPE_CNTL, 0,
		REGAMMA_CNTLA_EXP_REGION_LINEAR_SLOPE, params->arr_poपूर्णांकs[0].custom_भग्न_slope);

	REG_SET(REGAMMA_CNTLA_END_CNTL1, 0,
		REGAMMA_CNTLA_EXP_REGION_END, params->arr_poपूर्णांकs[1].custom_भग्न_x);

	REG_SET_2(REGAMMA_CNTLA_END_CNTL2, 0,
		  REGAMMA_CNTLA_EXP_REGION_END_BASE, params->arr_poपूर्णांकs[1].custom_भग्न_y,
		  REGAMMA_CNTLA_EXP_REGION_END_SLOPE, params->arr_poपूर्णांकs[1].custom_भग्न_slope);

	curve = params->arr_curve_poपूर्णांकs;

	REG_SET_4(REGAMMA_CNTLA_REGION_0_1, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
	curve += 2;

	REG_SET_4(REGAMMA_CNTLA_REGION_2_3, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
	curve += 2;

	REG_SET_4(REGAMMA_CNTLA_REGION_4_5, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
	curve += 2;

	REG_SET_4(REGAMMA_CNTLA_REGION_6_7, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
	curve += 2;

	REG_SET_4(REGAMMA_CNTLA_REGION_8_9, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
	curve += 2;

	REG_SET_4(REGAMMA_CNTLA_REGION_10_11, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
	curve += 2;

	REG_SET_4(REGAMMA_CNTLA_REGION_12_13, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
	curve += 2;

	REG_SET_4(REGAMMA_CNTLA_REGION_14_15, 0,
		  REGAMMA_CNTLA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		  REGAMMA_CNTLA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		  REGAMMA_CNTLA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		  REGAMMA_CNTLA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
पूर्ण



व्योम dce110_opp_program_regamma_pwl(काष्ठा transक्रमm *xfm,
				    स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);

	/* Setup regions */
	regamma_config_regions_and_segments(xfm_dce, params);

	/* Program PWL */
	program_pwl(xfm_dce, params);
पूर्ण

व्योम dce110_opp_घातer_on_regamma_lut(काष्ठा transक्रमm *xfm,
				     bool घातer_on)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);

	अगर (REG(DCFE_MEM_PWR_CTRL))
		REG_UPDATE_2(DCFE_MEM_PWR_CTRL,
			     DCP_REGAMMA_MEM_PWR_DIS, घातer_on,
			     DCP_LUT_MEM_PWR_DIS, घातer_on);
	अन्यथा
		REG_UPDATE_2(DCFE_MEM_LIGHT_SLEEP_CNTL,
			    REGAMMA_LUT_LIGHT_SLEEP_DIS, घातer_on,
			    DCP_LUT_LIGHT_SLEEP_DIS, घातer_on);

पूर्ण

व्योम dce110_opp_set_regamma_mode(काष्ठा transक्रमm *xfm,
				 क्रमागत opp_regamma mode)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);

	REG_SET(REGAMMA_CONTROL, 0,
		GRPH_REGAMMA_MODE, mode);
पूर्ण

अटल स्थिर काष्ठा transक्रमm_funcs dce_transक्रमm_funcs = अणु
	.transक्रमm_reset = dce_transक्रमm_reset,
	.transक्रमm_set_scaler = dce_transक्रमm_set_scaler,
	.transक्रमm_set_gamut_remap = dce_transक्रमm_set_gamut_remap,
	.opp_set_csc_adjusपंचांगent = dce110_opp_set_csc_adjusपंचांगent,
	.opp_set_csc_शेष = dce110_opp_set_csc_शेष,
	.opp_घातer_on_regamma_lut = dce110_opp_घातer_on_regamma_lut,
	.opp_program_regamma_pwl = dce110_opp_program_regamma_pwl,
	.opp_set_regamma_mode = dce110_opp_set_regamma_mode,
	.transक्रमm_set_pixel_storage_depth = dce_transक्रमm_set_pixel_storage_depth,
	.transक्रमm_get_optimal_number_of_taps = dce_transक्रमm_get_optimal_number_of_taps
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल स्थिर काष्ठा transक्रमm_funcs dce60_transक्रमm_funcs = अणु
	.transक्रमm_reset = dce_transक्रमm_reset,
	.transक्रमm_set_scaler = dce60_transक्रमm_set_scaler,
	.transक्रमm_set_gamut_remap = dce_transक्रमm_set_gamut_remap,
	.opp_set_csc_adjusपंचांगent = dce110_opp_set_csc_adjusपंचांगent,
	.opp_set_csc_शेष = dce110_opp_set_csc_शेष,
	.opp_घातer_on_regamma_lut = dce110_opp_घातer_on_regamma_lut,
	.opp_program_regamma_pwl = dce110_opp_program_regamma_pwl,
	.opp_set_regamma_mode = dce110_opp_set_regamma_mode,
	.transक्रमm_set_pixel_storage_depth = dce60_transक्रमm_set_pixel_storage_depth,
	.transक्रमm_get_optimal_number_of_taps = dce_transक्रमm_get_optimal_number_of_taps
पूर्ण;
#पूर्ण_अगर

/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

व्योम dce_transक्रमm_स्थिरruct(
	काष्ठा dce_transक्रमm *xfm_dce,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dce_transक्रमm_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_transक्रमm_shअगरt *xfm_shअगरt,
	स्थिर काष्ठा dce_transक्रमm_mask *xfm_mask)
अणु
	xfm_dce->base.ctx = ctx;

	xfm_dce->base.inst = inst;
	xfm_dce->base.funcs = &dce_transक्रमm_funcs;

	xfm_dce->regs = regs;
	xfm_dce->xfm_shअगरt = xfm_shअगरt;
	xfm_dce->xfm_mask = xfm_mask;

	xfm_dce->prescaler_on = true;
	xfm_dce->lb_pixel_depth_supported =
			LB_PIXEL_DEPTH_18BPP |
			LB_PIXEL_DEPTH_24BPP |
			LB_PIXEL_DEPTH_30BPP;

	xfm_dce->lb_bits_per_entry = LB_BITS_PER_ENTRY;
	xfm_dce->lb_memory_size = LB_TOTAL_NUMBER_OF_ENTRIES; /*0x6B0*/
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
व्योम dce60_transक्रमm_स्थिरruct(
	काष्ठा dce_transक्रमm *xfm_dce,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dce_transक्रमm_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_transक्रमm_shअगरt *xfm_shअगरt,
	स्थिर काष्ठा dce_transक्रमm_mask *xfm_mask)
अणु
	xfm_dce->base.ctx = ctx;

	xfm_dce->base.inst = inst;
	xfm_dce->base.funcs = &dce60_transक्रमm_funcs;

	xfm_dce->regs = regs;
	xfm_dce->xfm_shअगरt = xfm_shअगरt;
	xfm_dce->xfm_mask = xfm_mask;

	xfm_dce->prescaler_on = true;
	xfm_dce->lb_pixel_depth_supported =
			LB_PIXEL_DEPTH_18BPP |
			LB_PIXEL_DEPTH_24BPP |
			LB_PIXEL_DEPTH_30BPP;

	xfm_dce->lb_bits_per_entry = LB_BITS_PER_ENTRY;
	xfm_dce->lb_memory_size = LB_TOTAL_NUMBER_OF_ENTRIES; /*0x6B0*/
पूर्ण
#पूर्ण_अगर
