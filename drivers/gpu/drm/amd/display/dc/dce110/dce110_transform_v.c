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

#समावेश "dce110_transform_v.h"
#समावेश "dm_services.h"
#समावेश "dc.h"
#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"

#घोषणा SCLV_PHASES 64
#घोषणा DC_LOGGER \
	xfm->ctx->logger

काष्ठा sclv_ratios_inits अणु
	uपूर्णांक32_t h_पूर्णांक_scale_ratio_luma;
	uपूर्णांक32_t h_पूर्णांक_scale_ratio_chroma;
	uपूर्णांक32_t v_पूर्णांक_scale_ratio_luma;
	uपूर्णांक32_t v_पूर्णांक_scale_ratio_chroma;
	काष्ठा init_पूर्णांक_and_frac h_init_luma;
	काष्ठा init_पूर्णांक_and_frac h_init_chroma;
	काष्ठा init_पूर्णांक_and_frac v_init_luma;
	काष्ठा init_पूर्णांक_and_frac v_init_chroma;
पूर्ण;

अटल व्योम calculate_viewport(
		स्थिर काष्ठा scaler_data *scl_data,
		काष्ठा rect *luma_viewport,
		काष्ठा rect *chroma_viewport)
अणु
	/*Do not set chroma vp क्रम rgb444 pixel क्रमmat*/
	luma_viewport->x = scl_data->viewport.x - scl_data->viewport.x % 2;
	luma_viewport->y = scl_data->viewport.y - scl_data->viewport.y % 2;
	luma_viewport->width =
		scl_data->viewport.width - scl_data->viewport.width % 2;
	luma_viewport->height =
		scl_data->viewport.height - scl_data->viewport.height % 2;
	chroma_viewport->x = luma_viewport->x;
	chroma_viewport->y = luma_viewport->y;
	chroma_viewport->height = luma_viewport->height;
	chroma_viewport->width = luma_viewport->width;

	अगर (scl_data->क्रमmat == PIXEL_FORMAT_420BPP8) अणु
		luma_viewport->height += luma_viewport->height % 2;
		luma_viewport->width += luma_viewport->width % 2;
		/*क्रम 420 video chroma is 1/4 the area of luma, scaled
		 *vertically and horizontally
		 */
		chroma_viewport->x = luma_viewport->x / 2;
		chroma_viewport->y = luma_viewport->y / 2;
		chroma_viewport->height = luma_viewport->height / 2;
		chroma_viewport->width = luma_viewport->width / 2;
	पूर्ण
पूर्ण

अटल व्योम program_viewport(
	काष्ठा dce_transक्रमm *xfm_dce,
	काष्ठा rect *luma_view_port,
	काष्ठा rect *chroma_view_port)
अणु
	काष्ठा dc_context *ctx = xfm_dce->base.ctx;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t addr = 0;

	अगर (luma_view_port->width != 0 && luma_view_port->height != 0) अणु
		addr = mmSCLV_VIEWPORT_START;
		value = 0;
		set_reg_field_value(
			value,
			luma_view_port->x,
			SCLV_VIEWPORT_START,
			VIEWPORT_X_START);
		set_reg_field_value(
			value,
			luma_view_port->y,
			SCLV_VIEWPORT_START,
			VIEWPORT_Y_START);
		dm_ग_लिखो_reg(ctx, addr, value);

		addr = mmSCLV_VIEWPORT_SIZE;
		value = 0;
		set_reg_field_value(
			value,
			luma_view_port->height,
			SCLV_VIEWPORT_SIZE,
			VIEWPORT_HEIGHT);
		set_reg_field_value(
			value,
			luma_view_port->width,
			SCLV_VIEWPORT_SIZE,
			VIEWPORT_WIDTH);
		dm_ग_लिखो_reg(ctx, addr, value);
	पूर्ण

	अगर (chroma_view_port->width != 0 && chroma_view_port->height != 0) अणु
		addr = mmSCLV_VIEWPORT_START_C;
		value = 0;
		set_reg_field_value(
			value,
			chroma_view_port->x,
			SCLV_VIEWPORT_START_C,
			VIEWPORT_X_START_C);
		set_reg_field_value(
			value,
			chroma_view_port->y,
			SCLV_VIEWPORT_START_C,
			VIEWPORT_Y_START_C);
		dm_ग_लिखो_reg(ctx, addr, value);

		addr = mmSCLV_VIEWPORT_SIZE_C;
		value = 0;
		set_reg_field_value(
			value,
			chroma_view_port->height,
			SCLV_VIEWPORT_SIZE_C,
			VIEWPORT_HEIGHT_C);
		set_reg_field_value(
			value,
			chroma_view_port->width,
			SCLV_VIEWPORT_SIZE_C,
			VIEWPORT_WIDTH_C);
		dm_ग_लिखो_reg(ctx, addr, value);
	पूर्ण
पूर्ण

/*
 * Function:
 * व्योम setup_scaling_configuration
 *
 * Purpose: setup scaling mode : bypass, RGb, YCbCr and nummber of taps
 * Input:   data
 *
 * Output:
 *  व्योम
 */
अटल bool setup_scaling_configuration(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा scaler_data *data)
अणु
	bool is_scaling_needed = false;
	काष्ठा dc_context *ctx = xfm_dce->base.ctx;
	uपूर्णांक32_t value = 0;

	set_reg_field_value(value, data->taps.h_taps - 1,
			SCLV_TAP_CONTROL, SCL_H_NUM_OF_TAPS);
	set_reg_field_value(value, data->taps.v_taps - 1,
			SCLV_TAP_CONTROL, SCL_V_NUM_OF_TAPS);
	set_reg_field_value(value, data->taps.h_taps_c - 1,
			SCLV_TAP_CONTROL, SCL_H_NUM_OF_TAPS_C);
	set_reg_field_value(value, data->taps.v_taps_c - 1,
			SCLV_TAP_CONTROL, SCL_V_NUM_OF_TAPS_C);
	dm_ग_लिखो_reg(ctx, mmSCLV_TAP_CONTROL, value);

	value = 0;
	अगर (data->taps.h_taps + data->taps.v_taps > 2) अणु
		set_reg_field_value(value, 1, SCLV_MODE, SCL_MODE);
		set_reg_field_value(value, 1, SCLV_MODE, SCL_PSCL_EN);
		is_scaling_needed = true;
	पूर्ण अन्यथा अणु
		set_reg_field_value(value, 0, SCLV_MODE, SCL_MODE);
		set_reg_field_value(value, 0, SCLV_MODE, SCL_PSCL_EN);
	पूर्ण

	अगर (data->taps.h_taps_c + data->taps.v_taps_c > 2) अणु
		set_reg_field_value(value, 1, SCLV_MODE, SCL_MODE_C);
		set_reg_field_value(value, 1, SCLV_MODE, SCL_PSCL_EN_C);
		is_scaling_needed = true;
	पूर्ण अन्यथा अगर (data->क्रमmat != PIXEL_FORMAT_420BPP8) अणु
		set_reg_field_value(
			value,
			get_reg_field_value(value, SCLV_MODE, SCL_MODE),
			SCLV_MODE,
			SCL_MODE_C);
		set_reg_field_value(
			value,
			get_reg_field_value(value, SCLV_MODE, SCL_PSCL_EN),
			SCLV_MODE,
			SCL_PSCL_EN_C);
	पूर्ण अन्यथा अणु
		set_reg_field_value(value, 0, SCLV_MODE, SCL_MODE_C);
		set_reg_field_value(value, 0, SCLV_MODE, SCL_PSCL_EN_C);
	पूर्ण
	dm_ग_लिखो_reg(ctx, mmSCLV_MODE, value);

	value = 0;
	/*
	 * 0 - Replaced out of bound pixels with black pixel
	 * (or any other required color)
	 * 1 - Replaced out of bound pixels with the edge pixel
	 */
	set_reg_field_value(value, 1, SCLV_CONTROL, SCL_BOUNDARY_MODE);
	dm_ग_लिखो_reg(ctx, mmSCLV_CONTROL, value);

	वापस is_scaling_needed;
पूर्ण

/*
 * Function:
 * व्योम program_overscan
 *
 * Purpose: Programs overscan border
 * Input:   overscan
 *
 * Output: व्योम
 */
अटल व्योम program_overscan(
		काष्ठा dce_transक्रमm *xfm_dce,
		स्थिर काष्ठा scaler_data *data)
अणु
	uपूर्णांक32_t overscan_left_right = 0;
	uपूर्णांक32_t overscan_top_bottom = 0;

	पूर्णांक overscan_right = data->h_active - data->recout.x - data->recout.width;
	पूर्णांक overscan_bottom = data->v_active - data->recout.y - data->recout.height;

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

	set_reg_field_value(overscan_left_right, data->recout.x,
			EXT_OVERSCAN_LEFT_RIGHT, EXT_OVERSCAN_LEFT);

	set_reg_field_value(overscan_left_right, overscan_right,
			EXT_OVERSCAN_LEFT_RIGHT, EXT_OVERSCAN_RIGHT);

	set_reg_field_value(overscan_top_bottom, data->recout.y,
			EXT_OVERSCAN_TOP_BOTTOM, EXT_OVERSCAN_TOP);

	set_reg_field_value(overscan_top_bottom, overscan_bottom,
			EXT_OVERSCAN_TOP_BOTTOM, EXT_OVERSCAN_BOTTOM);

	dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmSCLV_EXT_OVERSCAN_LEFT_RIGHT,
			overscan_left_right);

	dm_ग_लिखो_reg(xfm_dce->base.ctx,
			mmSCLV_EXT_OVERSCAN_TOP_BOTTOM,
			overscan_top_bottom);
पूर्ण

अटल व्योम set_coeff_update_complete(
		काष्ठा dce_transक्रमm *xfm_dce)
अणु
	uपूर्णांक32_t value;

	value = dm_पढ़ो_reg(xfm_dce->base.ctx, mmSCLV_UPDATE);
	set_reg_field_value(value, 1, SCLV_UPDATE, SCL_COEF_UPDATE_COMPLETE);
	dm_ग_लिखो_reg(xfm_dce->base.ctx, mmSCLV_UPDATE, value);
पूर्ण

अटल व्योम program_multi_taps_filter(
	काष्ठा dce_transक्रमm *xfm_dce,
	पूर्णांक taps,
	स्थिर uपूर्णांक16_t *coeffs,
	क्रमागत ram_filter_type filter_type)
अणु
	काष्ठा dc_context *ctx = xfm_dce->base.ctx;
	पूर्णांक i, phase, pair;
	पूर्णांक array_idx = 0;
	पूर्णांक taps_pairs = (taps + 1) / 2;
	पूर्णांक phases_to_program = SCLV_PHASES / 2 + 1;

	uपूर्णांक32_t select = 0;
	uपूर्णांक32_t घातer_ctl, घातer_ctl_off;

	अगर (!coeffs)
		वापस;

	/*We need to disable घातer gating on coeff memory to करो programming*/
	घातer_ctl = dm_पढ़ो_reg(ctx, mmDCFEV_MEM_PWR_CTRL);
	घातer_ctl_off = घातer_ctl;
	set_reg_field_value(घातer_ctl_off, 1, DCFEV_MEM_PWR_CTRL, SCLV_COEFF_MEM_PWR_DIS);
	dm_ग_लिखो_reg(ctx, mmDCFEV_MEM_PWR_CTRL, घातer_ctl_off);

	/*Wait to disable gating:*/
	क्रम (i = 0; i < 10; i++) अणु
		अगर (get_reg_field_value(
				dm_पढ़ो_reg(ctx, mmDCFEV_MEM_PWR_STATUS),
				DCFEV_MEM_PWR_STATUS,
				SCLV_COEFF_MEM_PWR_STATE) == 0)
			अवरोध;

		udelay(1);
	पूर्ण

	set_reg_field_value(select, filter_type, SCLV_COEF_RAM_SELECT, SCL_C_RAM_FILTER_TYPE);

	क्रम (phase = 0; phase < phases_to_program; phase++) अणु
		/*we always program N/2 + 1 phases, total phases N, but N/2-1 are just mirror
		phase 0 is unique and phase N/2 is unique अगर N is even*/
		set_reg_field_value(select, phase, SCLV_COEF_RAM_SELECT, SCL_C_RAM_PHASE);
		क्रम (pair = 0; pair < taps_pairs; pair++) अणु
			uपूर्णांक32_t data = 0;

			set_reg_field_value(select, pair,
					SCLV_COEF_RAM_SELECT, SCL_C_RAM_TAP_PAIR_IDX);

			dm_ग_लिखो_reg(ctx, mmSCLV_COEF_RAM_SELECT, select);

			set_reg_field_value(
					data, 1,
					SCLV_COEF_RAM_TAP_DATA,
					SCL_C_RAM_EVEN_TAP_COEF_EN);
			set_reg_field_value(
					data, coeffs[array_idx],
					SCLV_COEF_RAM_TAP_DATA,
					SCL_C_RAM_EVEN_TAP_COEF);

			अगर (taps % 2 && pair == taps_pairs - 1) अणु
				set_reg_field_value(
						data, 0,
						SCLV_COEF_RAM_TAP_DATA,
						SCL_C_RAM_ODD_TAP_COEF_EN);
				array_idx++;
			पूर्ण अन्यथा अणु
				set_reg_field_value(
						data, 1,
						SCLV_COEF_RAM_TAP_DATA,
						SCL_C_RAM_ODD_TAP_COEF_EN);
				set_reg_field_value(
						data, coeffs[array_idx + 1],
						SCLV_COEF_RAM_TAP_DATA,
						SCL_C_RAM_ODD_TAP_COEF);

				array_idx += 2;
			पूर्ण

			dm_ग_लिखो_reg(ctx, mmSCLV_COEF_RAM_TAP_DATA, data);
		पूर्ण
	पूर्ण

	/*We need to restore घातer gating on coeff memory to initial state*/
	dm_ग_लिखो_reg(ctx, mmDCFEV_MEM_PWR_CTRL, घातer_ctl);
पूर्ण

अटल व्योम calculate_inits(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा scaler_data *data,
	काष्ठा sclv_ratios_inits *inits,
	काष्ठा rect *luma_viewport,
	काष्ठा rect *chroma_viewport)
अणु
	inits->h_पूर्णांक_scale_ratio_luma =
		dc_fixpt_u2d19(data->ratios.horz) << 5;
	inits->v_पूर्णांक_scale_ratio_luma =
		dc_fixpt_u2d19(data->ratios.vert) << 5;
	inits->h_पूर्णांक_scale_ratio_chroma =
		dc_fixpt_u2d19(data->ratios.horz_c) << 5;
	inits->v_पूर्णांक_scale_ratio_chroma =
		dc_fixpt_u2d19(data->ratios.vert_c) << 5;

	inits->h_init_luma.पूर्णांकeger = 1;
	inits->v_init_luma.पूर्णांकeger = 1;
	inits->h_init_chroma.पूर्णांकeger = 1;
	inits->v_init_chroma.पूर्णांकeger = 1;
पूर्ण

अटल व्योम program_scl_ratios_inits(
	काष्ठा dce_transक्रमm *xfm_dce,
	काष्ठा sclv_ratios_inits *inits)
अणु
	काष्ठा dc_context *ctx = xfm_dce->base.ctx;
	uपूर्णांक32_t addr = mmSCLV_HORZ_FILTER_SCALE_RATIO;
	uपूर्णांक32_t value = 0;

	set_reg_field_value(
		value,
		inits->h_पूर्णांक_scale_ratio_luma,
		SCLV_HORZ_FILTER_SCALE_RATIO,
		SCL_H_SCALE_RATIO);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmSCLV_VERT_FILTER_SCALE_RATIO;
	value = 0;
	set_reg_field_value(
		value,
		inits->v_पूर्णांक_scale_ratio_luma,
		SCLV_VERT_FILTER_SCALE_RATIO,
		SCL_V_SCALE_RATIO);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmSCLV_HORZ_FILTER_SCALE_RATIO_C;
	value = 0;
	set_reg_field_value(
		value,
		inits->h_पूर्णांक_scale_ratio_chroma,
		SCLV_HORZ_FILTER_SCALE_RATIO_C,
		SCL_H_SCALE_RATIO_C);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmSCLV_VERT_FILTER_SCALE_RATIO_C;
	value = 0;
	set_reg_field_value(
		value,
		inits->v_पूर्णांक_scale_ratio_chroma,
		SCLV_VERT_FILTER_SCALE_RATIO_C,
		SCL_V_SCALE_RATIO_C);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmSCLV_HORZ_FILTER_INIT;
	value = 0;
	set_reg_field_value(
		value,
		inits->h_init_luma.fraction,
		SCLV_HORZ_FILTER_INIT,
		SCL_H_INIT_FRAC);
	set_reg_field_value(
		value,
		inits->h_init_luma.पूर्णांकeger,
		SCLV_HORZ_FILTER_INIT,
		SCL_H_INIT_INT);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmSCLV_VERT_FILTER_INIT;
	value = 0;
	set_reg_field_value(
		value,
		inits->v_init_luma.fraction,
		SCLV_VERT_FILTER_INIT,
		SCL_V_INIT_FRAC);
	set_reg_field_value(
		value,
		inits->v_init_luma.पूर्णांकeger,
		SCLV_VERT_FILTER_INIT,
		SCL_V_INIT_INT);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmSCLV_HORZ_FILTER_INIT_C;
	value = 0;
	set_reg_field_value(
		value,
		inits->h_init_chroma.fraction,
		SCLV_HORZ_FILTER_INIT_C,
		SCL_H_INIT_FRAC_C);
	set_reg_field_value(
		value,
		inits->h_init_chroma.पूर्णांकeger,
		SCLV_HORZ_FILTER_INIT_C,
		SCL_H_INIT_INT_C);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmSCLV_VERT_FILTER_INIT_C;
	value = 0;
	set_reg_field_value(
		value,
		inits->v_init_chroma.fraction,
		SCLV_VERT_FILTER_INIT_C,
		SCL_V_INIT_FRAC_C);
	set_reg_field_value(
		value,
		inits->v_init_chroma.पूर्णांकeger,
		SCLV_VERT_FILTER_INIT_C,
		SCL_V_INIT_INT_C);
	dm_ग_लिखो_reg(ctx, addr, value);
पूर्ण

अटल स्थिर uपूर्णांक16_t *get_filter_coeffs_64p(पूर्णांक taps, काष्ठा fixed31_32 ratio)
अणु
	अगर (taps == 4)
		वापस get_filter_4tap_64p(ratio);
	अन्यथा अगर (taps == 2)
		वापस get_filter_2tap_64p();
	अन्यथा अगर (taps == 1)
		वापस शून्य;
	अन्यथा अणु
		/* should never happen, bug */
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण
पूर्ण

अटल bool dce110_xfmv_घातer_up_line_buffer(काष्ठा transक्रमm *xfm)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	uपूर्णांक32_t value;

	value = dm_पढ़ो_reg(xfm_dce->base.ctx, mmLBV_MEMORY_CTRL);

	/*Use all three pieces of memory always*/
	set_reg_field_value(value, 0, LBV_MEMORY_CTRL, LB_MEMORY_CONFIG);
	/*hard coded number DCE11 1712(0x6B0) Partitions: 720/960/1712*/
	set_reg_field_value(value, xfm_dce->lb_memory_size, LBV_MEMORY_CTRL,
			LB_MEMORY_SIZE);

	dm_ग_लिखो_reg(xfm_dce->base.ctx, mmLBV_MEMORY_CTRL, value);

	वापस true;
पूर्ण

अटल व्योम dce110_xfmv_set_scaler(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा scaler_data *data)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	bool is_scaling_required = false;
	bool filter_updated = false;
	स्थिर uपूर्णांक16_t *coeffs_v, *coeffs_h, *coeffs_h_c, *coeffs_v_c;
	काष्ठा rect luma_viewport = अणु0पूर्ण;
	काष्ठा rect chroma_viewport = अणु0पूर्ण;

	dce110_xfmv_घातer_up_line_buffer(xfm);
	/* 1. Calculate viewport, viewport programming should happen after init
	 * calculations as they may require an adjusपंचांगent in the viewport.
	 */

	calculate_viewport(data, &luma_viewport, &chroma_viewport);

	/* 2. Program overscan */
	program_overscan(xfm_dce, data);

	/* 3. Program taps and configuration */
	is_scaling_required = setup_scaling_configuration(xfm_dce, data);

	अगर (is_scaling_required) अणु
		/* 4. Calculate and program ratio, filter initialization */

		काष्ठा sclv_ratios_inits inits = अणु 0 पूर्ण;

		calculate_inits(
			xfm_dce,
			data,
			&inits,
			&luma_viewport,
			&chroma_viewport);

		program_scl_ratios_inits(xfm_dce, &inits);

		coeffs_v = get_filter_coeffs_64p(data->taps.v_taps, data->ratios.vert);
		coeffs_h = get_filter_coeffs_64p(data->taps.h_taps, data->ratios.horz);
		coeffs_v_c = get_filter_coeffs_64p(data->taps.v_taps_c, data->ratios.vert_c);
		coeffs_h_c = get_filter_coeffs_64p(data->taps.h_taps_c, data->ratios.horz_c);

		अगर (coeffs_v != xfm_dce->filter_v
				|| coeffs_v_c != xfm_dce->filter_v_c
				|| coeffs_h != xfm_dce->filter_h
				|| coeffs_h_c != xfm_dce->filter_h_c) अणु
		/* 5. Program vertical filters */
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FILTER_TYPE_RGB_Y_VERTICAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps_c,
					coeffs_v_c,
					FILTER_TYPE_CBCR_VERTICAL);

		/* 6. Program horizontal filters */
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FILTER_TYPE_RGB_Y_HORIZONTAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps_c,
					coeffs_h_c,
					FILTER_TYPE_CBCR_HORIZONTAL);

			xfm_dce->filter_v = coeffs_v;
			xfm_dce->filter_v_c = coeffs_v_c;
			xfm_dce->filter_h = coeffs_h;
			xfm_dce->filter_h_c = coeffs_h_c;
			filter_updated = true;
		पूर्ण
	पूर्ण

	/* 7. Program the viewport */
	program_viewport(xfm_dce, &luma_viewport, &chroma_viewport);

	/* 8. Set bit to flip to new coefficient memory */
	अगर (filter_updated)
		set_coeff_update_complete(xfm_dce);
पूर्ण

अटल व्योम dce110_xfmv_reset(काष्ठा transक्रमm *xfm)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);

	xfm_dce->filter_h = शून्य;
	xfm_dce->filter_v = शून्य;
	xfm_dce->filter_h_c = शून्य;
	xfm_dce->filter_v_c = शून्य;
पूर्ण

अटल व्योम dce110_xfmv_set_gamut_remap(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा xfm_grph_csc_adjusपंचांगent *adjust)
अणु
	/* DO NOTHING*/
पूर्ण

अटल व्योम dce110_xfmv_set_pixel_storage_depth(
	काष्ठा transक्रमm *xfm,
	क्रमागत lb_pixel_depth depth,
	स्थिर काष्ठा bit_depth_reduction_params *bit_depth_params)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	पूर्णांक pixel_depth = 0;
	पूर्णांक expan_mode = 0;
	uपूर्णांक32_t reg_data = 0;

	चयन (depth) अणु
	हाल LB_PIXEL_DEPTH_18BPP:
		pixel_depth = 2;
		expan_mode  = 1;
		अवरोध;
	हाल LB_PIXEL_DEPTH_24BPP:
		pixel_depth = 1;
		expan_mode  = 1;
		अवरोध;
	हाल LB_PIXEL_DEPTH_30BPP:
		pixel_depth = 0;
		expan_mode  = 1;
		अवरोध;
	हाल LB_PIXEL_DEPTH_36BPP:
		pixel_depth = 3;
		expan_mode  = 0;
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण

	set_reg_field_value(
		reg_data,
		expan_mode,
		LBV_DATA_FORMAT,
		PIXEL_EXPAN_MODE);

	set_reg_field_value(
		reg_data,
		pixel_depth,
		LBV_DATA_FORMAT,
		PIXEL_DEPTH);

	dm_ग_लिखो_reg(xfm->ctx, mmLBV_DATA_FORMAT, reg_data);

	अगर (!(xfm_dce->lb_pixel_depth_supported & depth)) अणु
		/*we should use unsupported capabilities
		 *  unless it is required by w/a*/
		DC_LOG_WARNING("%s: Capability not supported",
			__func__);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा transक्रमm_funcs dce110_xfmv_funcs = अणु
	.transक्रमm_reset = dce110_xfmv_reset,
	.transक्रमm_set_scaler = dce110_xfmv_set_scaler,
	.transक्रमm_set_gamut_remap =
		dce110_xfmv_set_gamut_remap,
	.opp_set_csc_शेष = dce110_opp_v_set_csc_शेष,
	.opp_set_csc_adjusपंचांगent = dce110_opp_v_set_csc_adjusपंचांगent,
	.opp_घातer_on_regamma_lut = dce110_opp_घातer_on_regamma_lut_v,
	.opp_program_regamma_pwl = dce110_opp_program_regamma_pwl_v,
	.opp_set_regamma_mode = dce110_opp_set_regamma_mode_v,
	.transक्रमm_set_pixel_storage_depth =
			dce110_xfmv_set_pixel_storage_depth,
	.transक्रमm_get_optimal_number_of_taps =
		dce_transक्रमm_get_optimal_number_of_taps
पूर्ण;
/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

bool dce110_transक्रमm_v_स्थिरruct(
	काष्ठा dce_transक्रमm *xfm_dce,
	काष्ठा dc_context *ctx)
अणु
	xfm_dce->base.ctx = ctx;

	xfm_dce->base.funcs = &dce110_xfmv_funcs;

	xfm_dce->lb_pixel_depth_supported =
			LB_PIXEL_DEPTH_18BPP |
			LB_PIXEL_DEPTH_24BPP |
			LB_PIXEL_DEPTH_30BPP;

	xfm_dce->prescaler_on = true;
	xfm_dce->lb_bits_per_entry = LB_BITS_PER_ENTRY;
	xfm_dce->lb_memory_size = LB_TOTAL_NUMBER_OF_ENTRIES; /*0x6B0*/

	वापस true;
पूर्ण
