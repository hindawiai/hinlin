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

#समावेश "dm_services.h"

/* include DCE11 रेजिस्टर header files */
#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"

#समावेश "dc_types.h"
#समावेश "dc_bios_types.h"
#समावेश "dc.h"

#समावेश "include/grph_object_id.h"
#समावेश "include/logger_interface.h"
#समावेश "dce110_timing_generator.h"

#समावेश "timing_generator.h"


#घोषणा NUMBER_OF_FRAME_TO_WAIT_ON_TRIGGERED_RESET 10

#घोषणा MAX_H_TOTAL (CRTC_H_TOTAL__CRTC_H_TOTAL_MASK + 1)
#घोषणा MAX_V_TOTAL (CRTC_V_TOTAL__CRTC_V_TOTAL_MASKhw + 1)

#घोषणा CRTC_REG(reg) (reg + tg110->offsets.crtc)
#घोषणा DCP_REG(reg) (reg + tg110->offsets.dcp)

/* Flowing रेजिस्टर offsets are same in files of
 * dce/dce_11_0_d.h
 * dce/vi_polaris10_p/vi_polaris10_d.h
 *
 * So we can create dce110 timing generator to use it.
 */


/*
* apply_front_porch_workaround
*
* This is a workaround क्रम a bug that has existed since R5xx and has not been
* fixed keep Front porch at minimum 2 क्रम Interlaced mode or 1 क्रम progressive.
*/
अटल व्योम dce110_timing_generator_apply_front_porch_workaround(
	काष्ठा timing_generator *tg,
	काष्ठा dc_crtc_timing *timing)
अणु
	अगर (timing->flags.INTERLACE == 1) अणु
		अगर (timing->v_front_porch < 2)
			timing->v_front_porch = 2;
	पूर्ण अन्यथा अणु
		अगर (timing->v_front_porch < 1)
			timing->v_front_porch = 1;
	पूर्ण
पूर्ण

/*
 *****************************************************************************
 *  Function: is_in_vertical_blank
 *
 *  @brief
 *     check the current status of CRTC to check अगर we are in Vertical Blank
 *     regioneased" state
 *
 *  @वापस
 *     true अगर currently in blank region, false otherwise
 *
 *****************************************************************************
 */
अटल bool dce110_timing_generator_is_in_vertical_blank(
		काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t field = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	addr = CRTC_REG(mmCRTC_STATUS);
	value = dm_पढ़ो_reg(tg->ctx, addr);
	field = get_reg_field_value(value, CRTC_STATUS, CRTC_V_BLANK);
	वापस field == 1;
पूर्ण

व्योम dce110_timing_generator_set_early_control(
		काष्ठा timing_generator *tg,
		uपूर्णांक32_t early_cntl)
अणु
	uपूर्णांक32_t regval;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t address = CRTC_REG(mmCRTC_CONTROL);

	regval = dm_पढ़ो_reg(tg->ctx, address);
	set_reg_field_value(regval, early_cntl,
			CRTC_CONTROL, CRTC_HBLANK_EARLY_CONTROL);
	dm_ग_लिखो_reg(tg->ctx, address, regval);
पूर्ण

/*
 * Enable CRTC
 * Enable CRTC - call ASIC Control Object to enable Timing generator.
 */
bool dce110_timing_generator_enable_crtc(काष्ठा timing_generator *tg)
अणु
	क्रमागत bp_result result;

	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = 0;

	/*
	 * 3 is used to make sure V_UPDATE occurs at the beginning of the first
	 * line of vertical front porch
	 */
	set_reg_field_value(
		value,
		0,
		CRTC_MASTER_UPDATE_MODE,
		MASTER_UPDATE_MODE);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_MODE), value);

	/* TODO: may want this on to catch underflow */
	value = 0;
	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_LOCK), value);

	result = tg->bp->funcs->enable_crtc(tg->bp, tg110->controller_id, true);

	वापस result == BP_RESULT_OK;
पूर्ण

व्योम dce110_timing_generator_program_blank_color(
		काष्ठा timing_generator *tg,
		स्थिर काष्ठा tg_color *black_color)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t addr = CRTC_REG(mmCRTC_BLACK_COLOR);
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		black_color->color_b_cb,
		CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB);
	set_reg_field_value(
		value,
		black_color->color_g_y,
		CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_G_Y);
	set_reg_field_value(
		value,
		black_color->color_r_cr,
		CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_R_CR);

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

/*
 *****************************************************************************
 *  Function: disable_stereo
 *
 *  @brief
 *     Disables active stereo on controller
 *     Frame Packing need to be disabled in vBlank or when CRTC not running
 *****************************************************************************
 */
#अगर 0
@TODOSTEREO
अटल व्योम disable_stereo(काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t addr = CRTC_REG(mmCRTC_3D_STRUCTURE_CONTROL);
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t test = 0;
	uपूर्णांक32_t field = 0;
	uपूर्णांक32_t struc_en = 0;
	uपूर्णांक32_t struc_stereo_sel_ovr = 0;

	value = dm_पढ़ो_reg(tg->ctx, addr);
	struc_en = get_reg_field_value(
			value,
			CRTC_3D_STRUCTURE_CONTROL,
			CRTC_3D_STRUCTURE_EN);

	struc_stereo_sel_ovr = get_reg_field_value(
			value,
			CRTC_3D_STRUCTURE_CONTROL,
			CRTC_3D_STRUCTURE_STEREO_SEL_OVR);

	/*
	 * When disabling Frame Packing in 2 step mode, we need to program both
	 * रेजिस्टरs at the same frame
	 * Programming it in the beginning of VActive makes sure we are ok
	 */

	अगर (struc_en != 0 && struc_stereo_sel_ovr == 0) अणु
		tg->funcs->रुको_क्रम_vblank(tg);
		tg->funcs->रुको_क्रम_vactive(tg);
	पूर्ण

	value = 0;
	dm_ग_लिखो_reg(tg->ctx, addr, value);

	addr = tg->regs[IDX_CRTC_STEREO_CONTROL];
	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण
#पूर्ण_अगर

/*
 * disable_crtc - call ASIC Control Object to disable Timing generator.
 */
bool dce110_timing_generator_disable_crtc(काष्ठा timing_generator *tg)
अणु
	क्रमागत bp_result result;

	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	result = tg->bp->funcs->enable_crtc(tg->bp, tg110->controller_id, false);

	/* Need to make sure stereo is disabled according to the DCE5.0 spec */

	/*
	 * @TODOSTEREO call this when adding stereo support
	 * tg->funcs->disable_stereo(tg);
	 */

	वापस result == BP_RESULT_OK;
पूर्ण

/*
 * program_horz_count_by_2
 * Programs DxCRTC_HORZ_COUNT_BY2_EN - 1 क्रम DVI 30bpp mode, 0 otherwise
 */
अटल व्योम program_horz_count_by_2(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t regval;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	regval = dm_पढ़ो_reg(tg->ctx,
			CRTC_REG(mmCRTC_COUNT_CONTROL));

	set_reg_field_value(regval, 0, CRTC_COUNT_CONTROL,
			CRTC_HORZ_COUNT_BY2_EN);

	अगर (timing->flags.HORZ_COUNT_BY_TWO)
		set_reg_field_value(regval, 1, CRTC_COUNT_CONTROL,
					CRTC_HORZ_COUNT_BY2_EN);

	dm_ग_लिखो_reg(tg->ctx,
			CRTC_REG(mmCRTC_COUNT_CONTROL), regval);
पूर्ण

/*
 * program_timing_generator
 * Program CRTC Timing Registers - DxCRTC_H_*, DxCRTC_V_*, Pixel repetition.
 * Call ASIC Control Object to program Timings.
 */
bool dce110_timing_generator_program_timing_generator(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing)
अणु
	क्रमागत bp_result result;
	काष्ठा bp_hw_crtc_timing_parameters bp_params;
	काष्ठा dc_crtc_timing patched_crtc_timing;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	uपूर्णांक32_t vsync_offset = dc_crtc_timing->v_border_bottom +
			dc_crtc_timing->v_front_porch;
	uपूर्णांक32_t v_sync_start =dc_crtc_timing->v_addressable + vsync_offset;

	uपूर्णांक32_t hsync_offset = dc_crtc_timing->h_border_right +
			dc_crtc_timing->h_front_porch;
	uपूर्णांक32_t h_sync_start = dc_crtc_timing->h_addressable + hsync_offset;

	स_रखो(&bp_params, 0, माप(काष्ठा bp_hw_crtc_timing_parameters));

	/* Due to an asic bug we need to apply the Front Porch workaround prior
	 * to programming the timing.
	 */

	patched_crtc_timing = *dc_crtc_timing;

	dce110_timing_generator_apply_front_porch_workaround(tg, &patched_crtc_timing);

	bp_params.controller_id = tg110->controller_id;

	bp_params.h_total = patched_crtc_timing.h_total;
	bp_params.h_addressable =
		patched_crtc_timing.h_addressable;
	bp_params.v_total = patched_crtc_timing.v_total;
	bp_params.v_addressable = patched_crtc_timing.v_addressable;

	bp_params.h_sync_start = h_sync_start;
	bp_params.h_sync_width = patched_crtc_timing.h_sync_width;
	bp_params.v_sync_start = v_sync_start;
	bp_params.v_sync_width = patched_crtc_timing.v_sync_width;

	/* Set overscan */
	bp_params.h_overscan_left =
		patched_crtc_timing.h_border_left;
	bp_params.h_overscan_right =
		patched_crtc_timing.h_border_right;
	bp_params.v_overscan_top = patched_crtc_timing.v_border_top;
	bp_params.v_overscan_bottom =
		patched_crtc_timing.v_border_bottom;

	/* Set flags */
	अगर (patched_crtc_timing.flags.HSYNC_POSITIVE_POLARITY == 1)
		bp_params.flags.HSYNC_POSITIVE_POLARITY = 1;

	अगर (patched_crtc_timing.flags.VSYNC_POSITIVE_POLARITY == 1)
		bp_params.flags.VSYNC_POSITIVE_POLARITY = 1;

	अगर (patched_crtc_timing.flags.INTERLACE == 1)
		bp_params.flags.INTERLACE = 1;

	अगर (patched_crtc_timing.flags.HORZ_COUNT_BY_TWO == 1)
		bp_params.flags.HORZ_COUNT_BY_TWO = 1;

	result = tg->bp->funcs->program_crtc_timing(tg->bp, &bp_params);

	program_horz_count_by_2(tg, &patched_crtc_timing);

	tg110->base.funcs->enable_advanced_request(tg, true, &patched_crtc_timing);

	/* Enable stereo - only when we need to pack 3D frame. Other types
	 * of stereo handled in explicit call */

	वापस result == BP_RESULT_OK;
पूर्ण

/*
 *****************************************************************************
 *  Function: set_drr
 *
 *  @brief
 *     Program dynamic refresh rate रेजिस्टरs m_DxCRTC_V_TOTAL_*.
 *
 *  @param [in] pHwCrtcTiming: poपूर्णांक to H
 *  wCrtcTiming काष्ठा
 *****************************************************************************
 */
व्योम dce110_timing_generator_set_drr(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा drr_params *params)
अणु
	/* रेजिस्टर values */
	uपूर्णांक32_t v_total_min = 0;
	uपूर्णांक32_t v_total_max = 0;
	uपूर्णांक32_t v_total_cntl = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	uपूर्णांक32_t addr = 0;

	addr = CRTC_REG(mmCRTC_V_TOTAL_MIN);
	v_total_min = dm_पढ़ो_reg(tg->ctx, addr);

	addr = CRTC_REG(mmCRTC_V_TOTAL_MAX);
	v_total_max = dm_पढ़ो_reg(tg->ctx, addr);

	addr = CRTC_REG(mmCRTC_V_TOTAL_CONTROL);
	v_total_cntl = dm_पढ़ो_reg(tg->ctx, addr);

	अगर (params != शून्य &&
		params->vertical_total_max > 0 &&
		params->vertical_total_min > 0) अणु

		set_reg_field_value(v_total_max,
				params->vertical_total_max - 1,
				CRTC_V_TOTAL_MAX,
				CRTC_V_TOTAL_MAX);

		set_reg_field_value(v_total_min,
				params->vertical_total_min - 1,
				CRTC_V_TOTAL_MIN,
				CRTC_V_TOTAL_MIN);

		set_reg_field_value(v_total_cntl,
				1,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MIN_SEL);

		set_reg_field_value(v_total_cntl,
				1,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MAX_SEL);

		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_ON_EVENT);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_TO_MASTER_VSYNC);

		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_SET_V_TOTAL_MIN_MASK_EN);

		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_SET_V_TOTAL_MIN_MASK);
	पूर्ण अन्यथा अणु
		set_reg_field_value(v_total_cntl,
			0,
			CRTC_V_TOTAL_CONTROL,
			CRTC_SET_V_TOTAL_MIN_MASK);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MIN_SEL);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MAX_SEL);
		set_reg_field_value(v_total_min,
				0,
				CRTC_V_TOTAL_MIN,
				CRTC_V_TOTAL_MIN);
		set_reg_field_value(v_total_max,
				0,
				CRTC_V_TOTAL_MAX,
				CRTC_V_TOTAL_MAX);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_ON_EVENT);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_TO_MASTER_VSYNC);
	पूर्ण

	addr = CRTC_REG(mmCRTC_V_TOTAL_MIN);
	dm_ग_लिखो_reg(tg->ctx, addr, v_total_min);

	addr = CRTC_REG(mmCRTC_V_TOTAL_MAX);
	dm_ग_लिखो_reg(tg->ctx, addr, v_total_max);

	addr = CRTC_REG(mmCRTC_V_TOTAL_CONTROL);
	dm_ग_लिखो_reg(tg->ctx, addr, v_total_cntl);
पूर्ण

व्योम dce110_timing_generator_set_अटल_screen_control(
	काष्ठा timing_generator *tg,
	uपूर्णांक32_t event_triggers,
	uपूर्णांक32_t num_frames)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t अटल_screen_cntl = 0;
	uपूर्णांक32_t addr = 0;

	// By रेजिस्टर spec, it only takes 8 bit value
	अगर (num_frames > 0xFF)
		num_frames = 0xFF;

	addr = CRTC_REG(mmCRTC_STATIC_SCREEN_CONTROL);
	अटल_screen_cntl = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(अटल_screen_cntl,
				event_triggers,
				CRTC_STATIC_SCREEN_CONTROL,
				CRTC_STATIC_SCREEN_EVENT_MASK);

	set_reg_field_value(अटल_screen_cntl,
				num_frames,
				CRTC_STATIC_SCREEN_CONTROL,
				CRTC_STATIC_SCREEN_FRAME_COUNT);

	dm_ग_लिखो_reg(tg->ctx, addr, अटल_screen_cntl);
पूर्ण

/*
 * get_vblank_counter
 *
 * @brief
 * Get counter क्रम vertical blanks. use रेजिस्टर CRTC_STATUS_FRAME_COUNT which
 * holds the counter of frames.
 *
 * @param
 * काष्ठा timing_generator *tg - [in] timing generator which controls the
 * desired CRTC
 *
 * @वापस
 * Counter of frames, which should equal to number of vblanks.
 */
uपूर्णांक32_t dce110_timing_generator_get_vblank_counter(काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t addr = CRTC_REG(mmCRTC_STATUS_FRAME_COUNT);
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);
	uपूर्णांक32_t field = get_reg_field_value(
			value, CRTC_STATUS_FRAME_COUNT, CRTC_FRAME_COUNT);

	वापस field;
पूर्ण

/*
 *****************************************************************************
 *  Function: dce110_timing_generator_get_position
 *
 *  @brief
 *     Returns CRTC vertical/horizontal counters
 *
 *  @param [out] position
 *****************************************************************************
 */
व्योम dce110_timing_generator_get_position(काष्ठा timing_generator *tg,
	काष्ठा crtc_position *position)
अणु
	uपूर्णांक32_t value;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_STATUS_POSITION));

	position->horizontal_count = get_reg_field_value(
			value,
			CRTC_STATUS_POSITION,
			CRTC_HORZ_COUNT);

	position->vertical_count = get_reg_field_value(
			value,
			CRTC_STATUS_POSITION,
			CRTC_VERT_COUNT);

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_NOM_VERT_POSITION));

	position->nominal_vcount = get_reg_field_value(
			value,
			CRTC_NOM_VERT_POSITION,
			CRTC_VERT_COUNT_NOM);
पूर्ण

/*
 *****************************************************************************
 *  Function: get_crtc_scanoutpos
 *
 *  @brief
 *     Returns CRTC vertical/horizontal counters
 *
 *  @param [out] vpos, hpos
 *****************************************************************************
 */
व्योम dce110_timing_generator_get_crtc_scanoutpos(
	काष्ठा timing_generator *tg,
	uपूर्णांक32_t *v_blank_start,
	uपूर्णांक32_t *v_blank_end,
	uपूर्णांक32_t *h_position,
	uपूर्णांक32_t *v_position)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	काष्ठा crtc_position position;

	uपूर्णांक32_t value  = dm_पढ़ो_reg(tg->ctx,
			CRTC_REG(mmCRTC_V_BLANK_START_END));

	*v_blank_start = get_reg_field_value(value,
					     CRTC_V_BLANK_START_END,
					     CRTC_V_BLANK_START);
	*v_blank_end = get_reg_field_value(value,
					   CRTC_V_BLANK_START_END,
					   CRTC_V_BLANK_END);

	dce110_timing_generator_get_position(
			tg, &position);

	*h_position = position.horizontal_count;
	*v_position = position.vertical_count;
पूर्ण

/* TODO: is it safe to assume that mask/shअगरt of Primary and Underlay
 * are the same?
 * For example: today CRTC_H_TOTAL == CRTCV_H_TOTAL but is it always
 * guaranteed? */
व्योम dce110_timing_generator_program_blanking(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t vsync_offset = timing->v_border_bottom +
			timing->v_front_porch;
	uपूर्णांक32_t v_sync_start =timing->v_addressable + vsync_offset;

	uपूर्णांक32_t hsync_offset = timing->h_border_right +
			timing->h_front_porch;
	uपूर्णांक32_t h_sync_start = timing->h_addressable + hsync_offset;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t पंचांगp = 0;

	addr = CRTC_REG(mmCRTC_H_TOTAL);
	value = dm_पढ़ो_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->h_total - 1,
		CRTC_H_TOTAL,
		CRTC_H_TOTAL);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_V_TOTAL);
	value = dm_पढ़ो_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->v_total - 1,
		CRTC_V_TOTAL,
		CRTC_V_TOTAL);
	dm_ग_लिखो_reg(ctx, addr, value);

	/* In हाल of V_TOTAL_CONTROL is on, make sure V_TOTAL_MAX and
	 * V_TOTAL_MIN are equal to V_TOTAL.
	 */
	addr = CRTC_REG(mmCRTC_V_TOTAL_MAX);
	value = dm_पढ़ो_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->v_total - 1,
		CRTC_V_TOTAL_MAX,
		CRTC_V_TOTAL_MAX);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_V_TOTAL_MIN);
	value = dm_पढ़ो_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->v_total - 1,
		CRTC_V_TOTAL_MIN,
		CRTC_V_TOTAL_MIN);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_H_BLANK_START_END);
	value = dm_पढ़ो_reg(ctx, addr);

	पंचांगp = timing->h_total -
		(h_sync_start + timing->h_border_left);

	set_reg_field_value(
		value,
		पंचांगp,
		CRTC_H_BLANK_START_END,
		CRTC_H_BLANK_END);

	पंचांगp = पंचांगp + timing->h_addressable +
		timing->h_border_left + timing->h_border_right;

	set_reg_field_value(
		value,
		पंचांगp,
		CRTC_H_BLANK_START_END,
		CRTC_H_BLANK_START);

	dm_ग_लिखो_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_V_BLANK_START_END);
	value = dm_पढ़ो_reg(ctx, addr);

	पंचांगp = timing->v_total - (v_sync_start + timing->v_border_top);

	set_reg_field_value(
		value,
		पंचांगp,
		CRTC_V_BLANK_START_END,
		CRTC_V_BLANK_END);

	पंचांगp = पंचांगp + timing->v_addressable + timing->v_border_top +
		timing->v_border_bottom;

	set_reg_field_value(
		value,
		पंचांगp,
		CRTC_V_BLANK_START_END,
		CRTC_V_BLANK_START);

	dm_ग_लिखो_reg(ctx, addr, value);
पूर्ण

व्योम dce110_timing_generator_set_test_pattern(
	काष्ठा timing_generator *tg,
	/* TODO: replace 'controller_dp_test_pattern' by 'test_pattern_mode'
	 * because this is not DP-specअगरic (which is probably somewhere in DP
	 * encoder) */
	क्रमागत controller_dp_test_pattern test_pattern,
	क्रमागत dc_color_depth color_depth)
अणु
	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t value;
	uपूर्णांक32_t addr;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	क्रमागत test_pattern_color_क्रमmat bit_depth;
	क्रमागत test_pattern_dyn_range dyn_range;
	क्रमागत test_pattern_mode mode;
	/* color ramp generator mixes 16-bits color */
	uपूर्णांक32_t src_bpc = 16;
	/* requested bpc */
	uपूर्णांक32_t dst_bpc;
	uपूर्णांक32_t index;
	/* RGB values of the color bars.
	 * Produce two RGB colors: RGB0 - white (all Fs)
	 * and RGB1 - black (all 0s)
	 * (three RGB components क्रम two colors)
	 */
	uपूर्णांक16_t src_color[6] = अणु0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
						0x0000, 0x0000पूर्ण;
	/* dest color (converted to the specअगरied color क्रमmat) */
	uपूर्णांक16_t dst_color[6];
	uपूर्णांक32_t inc_base;

	/* translate to bit depth */
	चयन (color_depth) अणु
	हाल COLOR_DEPTH_666:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_6;
	अवरोध;
	हाल COLOR_DEPTH_888:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_8;
	अवरोध;
	हाल COLOR_DEPTH_101010:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_10;
	अवरोध;
	हाल COLOR_DEPTH_121212:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_12;
	अवरोध;
	शेष:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_8;
	अवरोध;
	पूर्ण

	चयन (test_pattern) अणु
	हाल CONTROLLER_DP_TEST_PATTERN_COLORSQUARES:
	हाल CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA:
	अणु
		dyn_range = (test_pattern ==
				CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA ?
				TEST_PATTERN_DYN_RANGE_CEA :
				TEST_PATTERN_DYN_RANGE_VESA);
		mode = TEST_PATTERN_MODE_COLORSQUARES_RGB;
		value = 0;
		addr = CRTC_REG(mmCRTC_TEST_PATTERN_PARAMETERS);

		set_reg_field_value(
			value,
			6,
			CRTC_TEST_PATTERN_PARAMETERS,
			CRTC_TEST_PATTERN_VRES);
		set_reg_field_value(
			value,
			6,
			CRTC_TEST_PATTERN_PARAMETERS,
			CRTC_TEST_PATTERN_HRES);

		dm_ग_लिखो_reg(ctx, addr, value);

		addr = CRTC_REG(mmCRTC_TEST_PATTERN_CONTROL);
		value = 0;

		set_reg_field_value(
			value,
			1,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_EN);

		set_reg_field_value(
			value,
			mode,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_MODE);

		set_reg_field_value(
			value,
			dyn_range,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_DYNAMIC_RANGE);
		set_reg_field_value(
			value,
			bit_depth,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_COLOR_FORMAT);
		dm_ग_लिखो_reg(ctx, addr, value);
	पूर्ण
	अवरोध;

	हाल CONTROLLER_DP_TEST_PATTERN_VERTICALBARS:
	हाल CONTROLLER_DP_TEST_PATTERN_HORIZONTALBARS:
	अणु
		mode = (test_pattern ==
			CONTROLLER_DP_TEST_PATTERN_VERTICALBARS ?
			TEST_PATTERN_MODE_VERTICALBARS :
			TEST_PATTERN_MODE_HORIZONTALBARS);

		चयन (bit_depth) अणु
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_6:
			dst_bpc = 6;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
			dst_bpc = 8;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
			dst_bpc = 10;
		अवरोध;
		शेष:
			dst_bpc = 8;
		अवरोध;
		पूर्ण

		/* adjust color to the required colorFormat */
		क्रम (index = 0; index < 6; index++) अणु
			/* dst = 2^dstBpc * src / 2^srcBpc = src >>
			 * (srcBpc - dstBpc);
			 */
			dst_color[index] =
				src_color[index] >> (src_bpc - dst_bpc);
		/* CRTC_TEST_PATTERN_DATA has 16 bits,
		 * lowest 6 are hardwired to ZERO
		 * color bits should be left aligned aligned to MSB
		 * XXXXXXXXXX000000 क्रम 10 bit,
		 * XXXXXXXX00000000 क्रम 8 bit and XXXXXX0000000000 क्रम 6
		 */
			dst_color[index] <<= (16 - dst_bpc);
		पूर्ण

		value = 0;
		addr = CRTC_REG(mmCRTC_TEST_PATTERN_PARAMETERS);
		dm_ग_लिखो_reg(ctx, addr, value);

		/* We have to ग_लिखो the mask beक्रमe data, similar to pipeline.
		 * For example, क्रम 8 bpc, अगर we want RGB0 to be magenta,
		 * and RGB1 to be cyan,
		 * we need to make 7 ग_लिखोs:
		 * MASK   DATA
		 * 000001 00000000 00000000                     set mask to R0
		 * 000010 11111111 00000000     R0 255, 0xFF00, set mask to G0
		 * 000100 00000000 00000000     G0 0,   0x0000, set mask to B0
		 * 001000 11111111 00000000     B0 255, 0xFF00, set mask to R1
		 * 010000 00000000 00000000     R1 0,   0x0000, set mask to G1
		 * 100000 11111111 00000000     G1 255, 0xFF00, set mask to B1
		 * 100000 11111111 00000000     B1 255, 0xFF00
		 *
		 * we will make a loop of 6 in which we prepare the mask,
		 * then ग_लिखो, then prepare the color क्रम next ग_लिखो.
		 * first iteration will ग_लिखो mask only,
		 * but each next iteration color prepared in
		 * previous iteration will be written within new mask,
		 * the last component will written separately,
		 * mask is not changing between 6th and 7th ग_लिखो
		 * and color will be prepared by last iteration
		 */

		/* ग_लिखो color, color values mask in CRTC_TEST_PATTERN_MASK
		 * is B1, G1, R1, B0, G0, R0
		 */
		value = 0;
		addr = CRTC_REG(mmCRTC_TEST_PATTERN_COLOR);
		क्रम (index = 0; index < 6; index++) अणु
			/* prepare color mask, first ग_लिखो PATTERN_DATA
			 * will have all zeros
			 */
			set_reg_field_value(
				value,
				(1 << index),
				CRTC_TEST_PATTERN_COLOR,
				CRTC_TEST_PATTERN_MASK);
			/* ग_लिखो color component */
			dm_ग_लिखो_reg(ctx, addr, value);
			/* prepare next color component,
			 * will be written in the next iteration
			 */
			set_reg_field_value(
				value,
				dst_color[index],
				CRTC_TEST_PATTERN_COLOR,
				CRTC_TEST_PATTERN_DATA);
		पूर्ण
		/* ग_लिखो last color component,
		 * it's been alपढ़ोy prepared in the loop
		 */
		dm_ग_लिखो_reg(ctx, addr, value);

		/* enable test pattern */
		addr = CRTC_REG(mmCRTC_TEST_PATTERN_CONTROL);
		value = 0;

		set_reg_field_value(
			value,
			1,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_EN);

		set_reg_field_value(
			value,
			mode,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_MODE);

		set_reg_field_value(
			value,
			0,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_DYNAMIC_RANGE);

		set_reg_field_value(
			value,
			bit_depth,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_COLOR_FORMAT);

		dm_ग_लिखो_reg(ctx, addr, value);
	पूर्ण
	अवरोध;

	हाल CONTROLLER_DP_TEST_PATTERN_COLORRAMP:
	अणु
		mode = (bit_depth ==
			TEST_PATTERN_COLOR_FORMAT_BPC_10 ?
			TEST_PATTERN_MODE_DUALRAMP_RGB :
			TEST_PATTERN_MODE_SINGLERAMP_RGB);

		चयन (bit_depth) अणु
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_6:
			dst_bpc = 6;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
			dst_bpc = 8;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
			dst_bpc = 10;
		अवरोध;
		शेष:
			dst_bpc = 8;
		अवरोध;
		पूर्ण

		/* increment क्रम the first ramp क्रम one color gradation
		 * 1 gradation क्रम 6-bit color is 2^10
		 * gradations in 16-bit color
		 */
		inc_base = (src_bpc - dst_bpc);

		value = 0;
		addr = CRTC_REG(mmCRTC_TEST_PATTERN_PARAMETERS);

		चयन (bit_depth) अणु
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_6:
		अणु
			set_reg_field_value(
				value,
				inc_base,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_INC0);
			set_reg_field_value(
				value,
				0,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_INC1);
			set_reg_field_value(
				value,
				6,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_HRES);
			set_reg_field_value(
				value,
				6,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_VRES);
			set_reg_field_value(
				value,
				0,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_RAMP0_OFFSET);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
		अणु
			set_reg_field_value(
				value,
				inc_base,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_INC0);
			set_reg_field_value(
				value,
				0,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_INC1);
			set_reg_field_value(
				value,
				8,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_HRES);
			set_reg_field_value(
				value,
				6,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_VRES);
			set_reg_field_value(
				value,
				0,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_RAMP0_OFFSET);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
		अणु
			set_reg_field_value(
				value,
				inc_base,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_INC0);
			set_reg_field_value(
				value,
				inc_base + 2,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_INC1);
			set_reg_field_value(
				value,
				8,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_HRES);
			set_reg_field_value(
				value,
				5,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_VRES);
			set_reg_field_value(
				value,
				384 << 6,
				CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_RAMP0_OFFSET);
		पूर्ण
		अवरोध;
		शेष:
		अवरोध;
		पूर्ण
		dm_ग_लिखो_reg(ctx, addr, value);

		value = 0;
		addr = CRTC_REG(mmCRTC_TEST_PATTERN_COLOR);
		dm_ग_लिखो_reg(ctx, addr, value);

		/* enable test pattern */
		addr = CRTC_REG(mmCRTC_TEST_PATTERN_CONTROL);
		value = 0;

		set_reg_field_value(
			value,
			1,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_EN);

		set_reg_field_value(
			value,
			mode,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_MODE);

		set_reg_field_value(
			value,
			0,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_DYNAMIC_RANGE);
		/* add color depth translation here */
		set_reg_field_value(
			value,
			bit_depth,
			CRTC_TEST_PATTERN_CONTROL,
			CRTC_TEST_PATTERN_COLOR_FORMAT);

		dm_ग_लिखो_reg(ctx, addr, value);
	पूर्ण
	अवरोध;
	हाल CONTROLLER_DP_TEST_PATTERN_VIDEOMODE:
	अणु
		value = 0;
		dm_ग_लिखो_reg(ctx, CRTC_REG(mmCRTC_TEST_PATTERN_CONTROL), value);
		dm_ग_लिखो_reg(ctx, CRTC_REG(mmCRTC_TEST_PATTERN_COLOR), value);
		dm_ग_लिखो_reg(ctx, CRTC_REG(mmCRTC_TEST_PATTERN_PARAMETERS),
				value);
	पूर्ण
	अवरोध;
	शेष:
	अवरोध;
	पूर्ण
पूर्ण

/*
 * dce110_timing_generator_validate_timing
 * The timing generators support a maximum display size of is 8192 x 8192 pixels,
 * including both active display and blanking periods. Check H Total and V Total.
 */
bool dce110_timing_generator_validate_timing(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing,
	क्रमागत संकेत_type संकेत)
अणु
	uपूर्णांक32_t h_blank;
	uपूर्णांक32_t h_back_porch, hsync_offset, h_sync_start;

	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	ASSERT(timing != शून्य);

	अगर (!timing)
		वापस false;

	hsync_offset = timing->h_border_right + timing->h_front_porch;
	h_sync_start = timing->h_addressable + hsync_offset;

	/* Currently we करोn't support 3D, so block all 3D timings */
	अगर (timing->timing_3d_क्रमmat != TIMING_3D_FORMAT_NONE)
		वापस false;

	/* Temporarily blocking पूर्णांकerlacing mode until it's supported */
	अगर (timing->flags.INTERLACE == 1)
		वापस false;

	/* Check maximum number of pixels supported by Timing Generator
	 * (Currently will never fail, in order to fail needs display which
	 * needs more than 8192 horizontal and
	 * more than 8192 vertical total pixels)
	 */
	अगर (timing->h_total > tg110->max_h_total ||
		timing->v_total > tg110->max_v_total)
		वापस false;

	h_blank = (timing->h_total - timing->h_addressable -
		timing->h_border_right -
		timing->h_border_left);

	अगर (h_blank < tg110->min_h_blank)
		वापस false;

	अगर (timing->h_front_porch < tg110->min_h_front_porch)
		वापस false;

	h_back_porch = h_blank - (h_sync_start -
		timing->h_addressable -
		timing->h_border_right -
		timing->h_sync_width);

	अगर (h_back_porch < tg110->min_h_back_porch)
		वापस false;

	वापस true;
पूर्ण

/*
 * Wait till we are at the beginning of VBlank.
 */
व्योम dce110_timing_generator_रुको_क्रम_vblank(काष्ठा timing_generator *tg)
अणु
	/* We want to catch beginning of VBlank here, so अगर the first try are
	 * in VBlank, we might be very बंद to Active, in this हाल रुको क्रम
	 * another frame
	 */
	जबतक (dce110_timing_generator_is_in_vertical_blank(tg)) अणु
		अगर (!dce110_timing_generator_is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक (!dce110_timing_generator_is_in_vertical_blank(tg)) अणु
		अगर (!dce110_timing_generator_is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Wait till we are in VActive (anywhere in VActive)
 */
व्योम dce110_timing_generator_रुको_क्रम_vactive(काष्ठा timing_generator *tg)
अणु
	जबतक (dce110_timing_generator_is_in_vertical_blank(tg)) अणु
		अगर (!dce110_timing_generator_is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 *****************************************************************************
 *  Function: dce110_timing_generator_setup_global_swap_lock
 *
 *  @brief
 *     Setups Global Swap Lock group क्रम current pipe
 *     Pipe can join or leave GSL group, become a TimingServer or TimingClient
 *
 *  @param [in] gsl_params: setup data
 *****************************************************************************
 */
व्योम dce110_timing_generator_setup_global_swap_lock(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dcp_gsl_params *gsl_params)
अणु
	uपूर्णांक32_t value;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t address = DCP_REG(mmDCP_GSL_CONTROL);
	uपूर्णांक32_t check_poपूर्णांक = FLIP_READY_BACK_LOOKUP;

	value = dm_पढ़ो_reg(tg->ctx, address);

	/* This pipe will beदीर्घ to GSL Group zero. */
	set_reg_field_value(value,
			    1,
			    DCP_GSL_CONTROL,
			    DCP_GSL0_EN);

	set_reg_field_value(value,
			    gsl_params->gsl_master == tg->inst,
			    DCP_GSL_CONTROL,
			    DCP_GSL_MASTER_EN);

	set_reg_field_value(value,
			    HFLIP_READY_DELAY,
			    DCP_GSL_CONTROL,
			    DCP_GSL_HSYNC_FLIP_FORCE_DELAY);

	/* Keep संकेत low (pending high) during 6 lines.
	 * Also defines minimum पूर्णांकerval beक्रमe re-checking संकेत. */
	set_reg_field_value(value,
			    HFLIP_CHECK_DELAY,
			    DCP_GSL_CONTROL,
			    DCP_GSL_HSYNC_FLIP_CHECK_DELAY);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmDCP_GSL_CONTROL), value);
	value = 0;

	set_reg_field_value(value,
			    gsl_params->gsl_master,
			    DCIO_GSL0_CNTL,
			    DCIO_GSL0_VSYNC_SEL);

	set_reg_field_value(value,
			    0,
			    DCIO_GSL0_CNTL,
			    DCIO_GSL0_TIMING_SYNC_SEL);

	set_reg_field_value(value,
			    0,
			    DCIO_GSL0_CNTL,
			    DCIO_GSL0_GLOBAL_UNLOCK_SEL);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmDCIO_GSL0_CNTL), value);


	अणु
		uपूर्णांक32_t value_crtc_vtotal;

		value_crtc_vtotal = dm_पढ़ो_reg(tg->ctx,
				CRTC_REG(mmCRTC_V_TOTAL));

		set_reg_field_value(value,
				    0,/* DCP_GSL_PURPOSE_SURFACE_FLIP */
				    DCP_GSL_CONTROL,
				    DCP_GSL_SYNC_SOURCE);

		/* Checkpoपूर्णांक relative to end of frame */
		check_poपूर्णांक = get_reg_field_value(value_crtc_vtotal,
						  CRTC_V_TOTAL,
						  CRTC_V_TOTAL);

		dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_GSL_WINDOW), 0);
	पूर्ण

	set_reg_field_value(value,
			    1,
			    DCP_GSL_CONTROL,
			    DCP_GSL_DELAY_SURFACE_UPDATE_PENDING);

	dm_ग_लिखो_reg(tg->ctx, address, value);

	/********************************************************************/
	address = CRTC_REG(mmCRTC_GSL_CONTROL);

	value = dm_पढ़ो_reg(tg->ctx, address);
	set_reg_field_value(value,
			    check_poपूर्णांक - FLIP_READY_BACK_LOOKUP,
			    CRTC_GSL_CONTROL,
			    CRTC_GSL_CHECK_LINE_NUM);

	set_reg_field_value(value,
			    VFLIP_READY_DELAY,
			    CRTC_GSL_CONTROL,
			    CRTC_GSL_FORCE_DELAY);

	dm_ग_लिखो_reg(tg->ctx, address, value);
पूर्ण

व्योम dce110_timing_generator_tear_करोwn_global_swap_lock(
	काष्ठा timing_generator *tg)
अणु
	/* Clear all the रेजिस्टर ग_लिखोs करोne by
	 * dce110_timing_generator_setup_global_swap_lock
	 */

	uपूर्णांक32_t value;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t address = DCP_REG(mmDCP_GSL_CONTROL);

	value = 0;

	/* This pipe will beदीर्घ to GSL Group zero. */
	/* Settig HW शेष values from reg specs */
	set_reg_field_value(value,
			0,
			DCP_GSL_CONTROL,
			DCP_GSL0_EN);

	set_reg_field_value(value,
			0,
			DCP_GSL_CONTROL,
			DCP_GSL_MASTER_EN);

	set_reg_field_value(value,
			0x2,
			DCP_GSL_CONTROL,
			DCP_GSL_HSYNC_FLIP_FORCE_DELAY);

	set_reg_field_value(value,
			0x6,
			DCP_GSL_CONTROL,
			DCP_GSL_HSYNC_FLIP_CHECK_DELAY);

	/* Restore DCP_GSL_PURPOSE_SURFACE_FLIP */
	अणु
		dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_V_TOTAL));

		set_reg_field_value(value,
				0,
				DCP_GSL_CONTROL,
				DCP_GSL_SYNC_SOURCE);
	पूर्ण

	set_reg_field_value(value,
			0,
			DCP_GSL_CONTROL,
			DCP_GSL_DELAY_SURFACE_UPDATE_PENDING);

	dm_ग_लिखो_reg(tg->ctx, address, value);

	/********************************************************************/
	address = CRTC_REG(mmCRTC_GSL_CONTROL);

	value = 0;
	set_reg_field_value(value,
			0,
			CRTC_GSL_CONTROL,
			CRTC_GSL_CHECK_LINE_NUM);

	set_reg_field_value(value,
			0x2,
			CRTC_GSL_CONTROL,
			CRTC_GSL_FORCE_DELAY);

	dm_ग_लिखो_reg(tg->ctx, address, value);
पूर्ण
/*
 *****************************************************************************
 *  Function: is_counter_moving
 *
 *  @brief
 *     check अगर the timing generator is currently going
 *
 *  @वापस
 *     true अगर currently going, false अगर currently छोड़ोd or stopped.
 *
 *****************************************************************************
 */
bool dce110_timing_generator_is_counter_moving(काष्ठा timing_generator *tg)
अणु
	काष्ठा crtc_position position1, position2;

	tg->funcs->get_position(tg, &position1);
	tg->funcs->get_position(tg, &position2);

	अगर (position1.horizontal_count == position2.horizontal_count &&
		position1.vertical_count == position2.vertical_count)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

व्योम dce110_timing_generator_enable_advanced_request(
	काष्ठा timing_generator *tg,
	bool enable,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t addr = CRTC_REG(mmCRTC_START_LINE_CONTROL);
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	अगर (enable) अणु
		set_reg_field_value(
			value,
			0,
			CRTC_START_LINE_CONTROL,
			CRTC_LEGACY_REQUESTOR_EN);
	पूर्ण अन्यथा अणु
		set_reg_field_value(
			value,
			1,
			CRTC_START_LINE_CONTROL,
			CRTC_LEGACY_REQUESTOR_EN);
	पूर्ण

	अगर ((timing->v_sync_width + timing->v_front_porch) <= 3) अणु
		set_reg_field_value(
			value,
			3,
			CRTC_START_LINE_CONTROL,
			CRTC_ADVANCED_START_LINE_POSITION);
		set_reg_field_value(
			value,
			0,
			CRTC_START_LINE_CONTROL,
			CRTC_PREFETCH_EN);
	पूर्ण अन्यथा अणु
		set_reg_field_value(
			value,
			4,
			CRTC_START_LINE_CONTROL,
			CRTC_ADVANCED_START_LINE_POSITION);
		set_reg_field_value(
			value,
			1,
			CRTC_START_LINE_CONTROL,
			CRTC_PREFETCH_EN);
	पूर्ण

	set_reg_field_value(
		value,
		1,
		CRTC_START_LINE_CONTROL,
		CRTC_PROGRESSIVE_START_LINE_EARLY);

	set_reg_field_value(
		value,
		1,
		CRTC_START_LINE_CONTROL,
		CRTC_INTERLACE_START_LINE_EARLY);

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

/*TODO: Figure out अगर we need this function. */
व्योम dce110_timing_generator_set_lock_master(काष्ठा timing_generator *tg,
		bool lock)
अणु
	काष्ठा dc_context *ctx = tg->ctx;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t addr = CRTC_REG(mmCRTC_MASTER_UPDATE_LOCK);
	uपूर्णांक32_t value = dm_पढ़ो_reg(ctx, addr);

	set_reg_field_value(
		value,
		lock ? 1 : 0,
		CRTC_MASTER_UPDATE_LOCK,
		MASTER_UPDATE_LOCK);

	dm_ग_लिखो_reg(ctx, addr, value);
पूर्ण

व्योम dce110_timing_generator_enable_reset_trigger(
	काष्ठा timing_generator *tg,
	पूर्णांक source_tg_inst)
अणु
	uपूर्णांक32_t value;
	uपूर्णांक32_t rising_edge = 0;
	uपूर्णांक32_t falling_edge = 0;
	क्रमागत trigger_source_select trig_src_select = TRIGGER_SOURCE_SELECT_LOGIC_ZERO;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Setup trigger edge */
	अणु
		uपूर्णांक32_t pol_value = dm_पढ़ो_reg(tg->ctx,
				CRTC_REG(mmCRTC_V_SYNC_A_CNTL));

		/* Register spec has reversed definition:
		 *	0 क्रम positive, 1 क्रम negative */
		अगर (get_reg_field_value(pol_value,
				CRTC_V_SYNC_A_CNTL,
				CRTC_V_SYNC_A_POL) == 0) अणु
			rising_edge = 1;
		पूर्ण अन्यथा अणु
			falling_edge = 1;
		पूर्ण
	पूर्ण

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL));

	trig_src_select = TRIGGER_SOURCE_SELECT_GSL_GROUP0;

	set_reg_field_value(value,
			trig_src_select,
			CRTC_TRIGB_CNTL,
			CRTC_TRIGB_SOURCE_SELECT);

	set_reg_field_value(value,
			TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
			CRTC_TRIGB_CNTL,
			CRTC_TRIGB_POLARITY_SELECT);

	set_reg_field_value(value,
			rising_edge,
			CRTC_TRIGB_CNTL,
			CRTC_TRIGB_RISING_EDGE_DETECT_CNTL);

	set_reg_field_value(value,
			falling_edge,
			CRTC_TRIGB_CNTL,
			CRTC_TRIGB_FALLING_EDGE_DETECT_CNTL);

	set_reg_field_value(value,
			0, /* send every संकेत */
			CRTC_TRIGB_CNTL,
			CRTC_TRIGB_FREQUENCY_SELECT);

	set_reg_field_value(value,
			0, /* no delay */
			CRTC_TRIGB_CNTL,
			CRTC_TRIGB_DELAY);

	set_reg_field_value(value,
			1, /* clear trigger status */
			CRTC_TRIGB_CNTL,
			CRTC_TRIGB_CLEAR);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL), value);

	/**************************************************************/

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));

	set_reg_field_value(value,
			2, /* क्रमce H count to H_TOTAL and V count to V_TOTAL */
			CRTC_FORCE_COUNT_NOW_CNTL,
			CRTC_FORCE_COUNT_NOW_MODE);

	set_reg_field_value(value,
			1, /* TriggerB - we never use TriggerA */
			CRTC_FORCE_COUNT_NOW_CNTL,
			CRTC_FORCE_COUNT_NOW_TRIG_SEL);

	set_reg_field_value(value,
			1, /* clear trigger status */
			CRTC_FORCE_COUNT_NOW_CNTL,
			CRTC_FORCE_COUNT_NOW_CLEAR);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL), value);
पूर्ण

व्योम dce110_timing_generator_enable_crtc_reset(
		काष्ठा timing_generator *tg,
		पूर्णांक source_tg_inst,
		काष्ठा crtc_trigger_info *crtc_tp)
अणु
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t rising_edge = 0;
	uपूर्णांक32_t falling_edge = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Setup trigger edge */
	चयन (crtc_tp->event) अणु
	हाल CRTC_EVENT_VSYNC_RISING:
			rising_edge = 1;
			अवरोध;

	हाल CRTC_EVENT_VSYNC_FALLING:
		falling_edge = 1;
		अवरोध;
	पूर्ण

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL));

	set_reg_field_value(value,
			    source_tg_inst,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_SOURCE_SELECT);

	set_reg_field_value(value,
			    TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_POLARITY_SELECT);

	set_reg_field_value(value,
			    rising_edge,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_RISING_EDGE_DETECT_CNTL);

	set_reg_field_value(value,
			    falling_edge,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_FALLING_EDGE_DETECT_CNTL);

	set_reg_field_value(value,
			    1, /* clear trigger status */
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_CLEAR);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL), value);

	/**************************************************************/

	चयन (crtc_tp->delay) अणु
	हाल TRIGGER_DELAY_NEXT_LINE:
		value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));

		set_reg_field_value(value,
				    0, /* क्रमce H count to H_TOTAL and V count to V_TOTAL */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_MODE);

		set_reg_field_value(value,
				    0, /* TriggerB - we never use TriggerA */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_TRIG_SEL);

		set_reg_field_value(value,
				    1, /* clear trigger status */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_CLEAR);

		dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL), value);

		value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL));

		set_reg_field_value(value,
				    1,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_FORCE_VSYNC_NEXT_LINE_CLEAR);

		set_reg_field_value(value,
				    2,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_AUTO_FORCE_VSYNC_MODE);

		अवरोध;

	हाल TRIGGER_DELAY_NEXT_PIXEL:
		value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL));

		set_reg_field_value(value,
				    1,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_FORCE_VSYNC_NEXT_LINE_CLEAR);

		set_reg_field_value(value,
				    0,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_AUTO_FORCE_VSYNC_MODE);

		dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL), value);

		value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));

		set_reg_field_value(value,
				    2, /* क्रमce H count to H_TOTAL and V count to V_TOTAL */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_MODE);

		set_reg_field_value(value,
				    1, /* TriggerB - we never use TriggerA */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_TRIG_SEL);

		set_reg_field_value(value,
				    1, /* clear trigger status */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_CLEAR);

		dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL), value);
		अवरोध;
	पूर्ण

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_MODE));

	set_reg_field_value(value,
			    2,
			    CRTC_MASTER_UPDATE_MODE,
			    MASTER_UPDATE_MODE);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_MODE), value);
पूर्ण
व्योम dce110_timing_generator_disable_reset_trigger(
	काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t value;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));

	set_reg_field_value(value,
			    0, /* क्रमce counter now mode is disabled */
			    CRTC_FORCE_COUNT_NOW_CNTL,
			    CRTC_FORCE_COUNT_NOW_MODE);

	set_reg_field_value(value,
			    1, /* clear trigger status */
			    CRTC_FORCE_COUNT_NOW_CNTL,
			    CRTC_FORCE_COUNT_NOW_CLEAR);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL), value);

	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL));

	set_reg_field_value(value,
			    1,
			    CRTC_VERT_SYNC_CONTROL,
			    CRTC_FORCE_VSYNC_NEXT_LINE_CLEAR);

	set_reg_field_value(value,
			    0,
			    CRTC_VERT_SYNC_CONTROL,
			    CRTC_AUTO_FORCE_VSYNC_MODE);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL), value);

	/********************************************************************/
	value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL));

	set_reg_field_value(value,
			    TRIGGER_SOURCE_SELECT_LOGIC_ZERO,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_SOURCE_SELECT);

	set_reg_field_value(value,
			    TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_POLARITY_SELECT);

	set_reg_field_value(value,
			    1, /* clear trigger status */
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_CLEAR);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL), value);
पूर्ण

/*
 *****************************************************************************
 *  @brief
 *     Checks whether CRTC triggered reset occurred
 *
 *  @वापस
 *     true अगर triggered reset occurred, false otherwise
 *****************************************************************************
 */
bool dce110_timing_generator_did_triggered_reset_occur(
	काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx,
			CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));
	uपूर्णांक32_t value1 = dm_पढ़ो_reg(tg->ctx,
			CRTC_REG(mmCRTC_VERT_SYNC_CONTROL));
	bool क्रमce = get_reg_field_value(value,
					 CRTC_FORCE_COUNT_NOW_CNTL,
					 CRTC_FORCE_COUNT_NOW_OCCURRED) != 0;
	bool vert_sync = get_reg_field_value(value1,
					     CRTC_VERT_SYNC_CONTROL,
					     CRTC_FORCE_VSYNC_NEXT_LINE_OCCURRED) != 0;

	वापस (क्रमce || vert_sync);
पूर्ण

/*
 * dce110_timing_generator_disable_vga
 * Turn OFF VGA Mode and Timing  - DxVGA_CONTROL
 * VGA Mode and VGA Timing is used by VBIOS on CRT Monitors;
 */
व्योम dce110_timing_generator_disable_vga(
	काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t value = 0;

	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	चयन (tg110->controller_id) अणु
	हाल CONTROLLER_ID_D0:
		addr = mmD1VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D1:
		addr = mmD2VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D2:
		addr = mmD3VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D3:
		addr = mmD4VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D4:
		addr = mmD5VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D5:
		addr = mmD6VGA_CONTROL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	value = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_MODE_ENABLE);
	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_TIMING_SELECT);
	set_reg_field_value(
			value, 0, D1VGA_CONTROL, D1VGA_SYNC_POLARITY_SELECT);
	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_OVERSCAN_COLOR_EN);

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

/*
 * set_overscan_color_black
 *
 * @param :black_color is one of the color space
 *    :this routine will set overscan black color according to the color space.
 * @वापस none
 */
व्योम dce110_timing_generator_set_overscan_color_black(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *color)
अणु
	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t value = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	set_reg_field_value(
			value,
			color->color_b_cb,
			CRTC_OVERSCAN_COLOR,
			CRTC_OVERSCAN_COLOR_BLUE);

	set_reg_field_value(
			value,
			color->color_r_cr,
			CRTC_OVERSCAN_COLOR,
			CRTC_OVERSCAN_COLOR_RED);

	set_reg_field_value(
			value,
			color->color_g_y,
			CRTC_OVERSCAN_COLOR,
			CRTC_OVERSCAN_COLOR_GREEN);

	addr = CRTC_REG(mmCRTC_OVERSCAN_COLOR);
	dm_ग_लिखो_reg(ctx, addr, value);
	addr = CRTC_REG(mmCRTC_BLACK_COLOR);
	dm_ग_लिखो_reg(ctx, addr, value);
	/* This is desirable to have a स्थिरant DAC output voltage during the
	 * blank समय that is higher than the 0 volt reference level that the
	 * DAC outमाला_दो when the NBLANK संकेत
	 * is निश्चितed low, such as क्रम output to an analog TV. */
	addr = CRTC_REG(mmCRTC_BLANK_DATA_COLOR);
	dm_ग_लिखो_reg(ctx, addr, value);

	/* TO DO we have to program EXT रेजिस्टरs and we need to know LB DATA
	 * क्रमmat because it is used when more 10 , i.e. 12 bits per color
	 *
	 * m_mmDxCRTC_OVERSCAN_COLOR_EXT
	 * m_mmDxCRTC_BLACK_COLOR_EXT
	 * m_mmDxCRTC_BLANK_DATA_COLOR_EXT
	 */

पूर्ण

व्योम dce110_tg_program_blank_color(काष्ठा timing_generator *tg,
		स्थिर काष्ठा tg_color *black_color)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t addr = CRTC_REG(mmCRTC_BLACK_COLOR);
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		black_color->color_b_cb,
		CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB);
	set_reg_field_value(
		value,
		black_color->color_g_y,
		CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_G_Y);
	set_reg_field_value(
		value,
		black_color->color_r_cr,
		CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_R_CR);

	dm_ग_लिखो_reg(tg->ctx, addr, value);

	addr = CRTC_REG(mmCRTC_BLANK_DATA_COLOR);
	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

व्योम dce110_tg_set_overscan_color(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *overscan_color)
अणु
	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t addr;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	set_reg_field_value(
		value,
		overscan_color->color_b_cb,
		CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_BLUE);

	set_reg_field_value(
		value,
		overscan_color->color_g_y,
		CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_GREEN);

	set_reg_field_value(
		value,
		overscan_color->color_r_cr,
		CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_RED);

	addr = CRTC_REG(mmCRTC_OVERSCAN_COLOR);
	dm_ग_लिखो_reg(ctx, addr, value);
पूर्ण

व्योम dce110_tg_program_timing(काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing,
	पूर्णांक vपढ़ोy_offset,
	पूर्णांक vstartup_start,
	पूर्णांक vupdate_offset,
	पूर्णांक vupdate_width,
	स्थिर क्रमागत संकेत_type संकेत,
	bool use_vbios)
अणु
	अगर (use_vbios)
		dce110_timing_generator_program_timing_generator(tg, timing);
	अन्यथा
		dce110_timing_generator_program_blanking(tg, timing);
पूर्ण

bool dce110_tg_is_blanked(काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, CRTC_REG(mmCRTC_BLANK_CONTROL));

	अगर (get_reg_field_value(
			value,
			CRTC_BLANK_CONTROL,
			CRTC_BLANK_DATA_EN) == 1 &&
		get_reg_field_value(
			value,
			CRTC_BLANK_CONTROL,
			CRTC_CURRENT_BLANK_STATE) == 1)
		वापस true;
	वापस false;
पूर्ण

व्योम dce110_tg_set_blank(काष्ठा timing_generator *tg,
		bool enable_blanking)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = 0;

	set_reg_field_value(
		value,
		1,
		CRTC_DOUBLE_BUFFER_CONTROL,
		CRTC_BLANK_DATA_DOUBLE_BUFFER_EN);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_DOUBLE_BUFFER_CONTROL), value);
	value = 0;

	अगर (enable_blanking) अणु
		set_reg_field_value(
			value,
			1,
			CRTC_BLANK_CONTROL,
			CRTC_BLANK_DATA_EN);

		dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_BLANK_CONTROL), value);

	पूर्ण अन्यथा
		dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_BLANK_CONTROL), 0);
पूर्ण

bool dce110_tg_validate_timing(काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	वापस dce110_timing_generator_validate_timing(tg, timing, SIGNAL_TYPE_NONE);
पूर्ण

व्योम dce110_tg_रुको_क्रम_state(काष्ठा timing_generator *tg,
	क्रमागत crtc_state state)
अणु
	चयन (state) अणु
	हाल CRTC_STATE_VBLANK:
		dce110_timing_generator_रुको_क्रम_vblank(tg);
		अवरोध;

	हाल CRTC_STATE_VACTIVE:
		dce110_timing_generator_रुको_क्रम_vactive(tg);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम dce110_tg_set_colors(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *blank_color,
	स्थिर काष्ठा tg_color *overscan_color)
अणु
	अगर (blank_color != शून्य)
		dce110_tg_program_blank_color(tg, blank_color);
	अगर (overscan_color != शून्य)
		dce110_tg_set_overscan_color(tg, overscan_color);
पूर्ण

/* Gets first line of blank region of the display timing क्रम CRTC
 * and programms is as a trigger to fire vertical पूर्णांकerrupt
 */
bool dce110_arm_vert_पूर्णांकr(काष्ठा timing_generator *tg, uपूर्णांक8_t width)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t v_blank_start = 0;
	uपूर्णांक32_t v_blank_end = 0;
	uपूर्णांक32_t val = 0;
	uपूर्णांक32_t h_position, v_position;

	tg->funcs->get_scanoutpos(
			tg,
			&v_blank_start,
			&v_blank_end,
			&h_position,
			&v_position);

	अगर (v_blank_start == 0 || v_blank_end == 0)
		वापस false;

	set_reg_field_value(
		val,
		v_blank_start,
		CRTC_VERTICAL_INTERRUPT0_POSITION,
		CRTC_VERTICAL_INTERRUPT0_LINE_START);

	/* Set पूर्णांकerval width क्रम पूर्णांकerrupt to fire to 1 scanline */
	set_reg_field_value(
		val,
		v_blank_start + width,
		CRTC_VERTICAL_INTERRUPT0_POSITION,
		CRTC_VERTICAL_INTERRUPT0_LINE_END);

	dm_ग_लिखो_reg(tg->ctx, CRTC_REG(mmCRTC_VERTICAL_INTERRUPT0_POSITION), val);

	वापस true;
पूर्ण

अटल bool dce110_is_tg_enabled(काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t field = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	addr = CRTC_REG(mmCRTC_CONTROL);
	value = dm_पढ़ो_reg(tg->ctx, addr);
	field = get_reg_field_value(value, CRTC_CONTROL,
				    CRTC_CURRENT_MASTER_EN_STATE);
	वापस field == 1;
पूर्ण

bool dce110_configure_crc(काष्ठा timing_generator *tg,
			  स्थिर काष्ठा crc_params *params)
अणु
	uपूर्णांक32_t cntl_addr = 0;
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t value;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Cannot configure crc on a CRTC that is disabled */
	अगर (!dce110_is_tg_enabled(tg))
		वापस false;

	cntl_addr = CRTC_REG(mmCRTC_CRC_CNTL);

	/* First, disable CRC beक्रमe we configure it. */
	dm_ग_लिखो_reg(tg->ctx, cntl_addr, 0);

	अगर (!params->enable)
		वापस true;

	/* Program frame boundaries */
	/* Winकरोw A x axis start and end. */
	value = 0;
	addr = CRTC_REG(mmCRTC_CRC0_WINDOWA_X_CONTROL);
	set_reg_field_value(value, params->winकरोwa_x_start,
			    CRTC_CRC0_WINDOWA_X_CONTROL,
			    CRTC_CRC0_WINDOWA_X_START);
	set_reg_field_value(value, params->winकरोwa_x_end,
			    CRTC_CRC0_WINDOWA_X_CONTROL,
			    CRTC_CRC0_WINDOWA_X_END);
	dm_ग_लिखो_reg(tg->ctx, addr, value);

	/* Winकरोw A y axis start and end. */
	value = 0;
	addr = CRTC_REG(mmCRTC_CRC0_WINDOWA_Y_CONTROL);
	set_reg_field_value(value, params->winकरोwa_y_start,
			    CRTC_CRC0_WINDOWA_Y_CONTROL,
			    CRTC_CRC0_WINDOWA_Y_START);
	set_reg_field_value(value, params->winकरोwa_y_end,
			    CRTC_CRC0_WINDOWA_Y_CONTROL,
			    CRTC_CRC0_WINDOWA_Y_END);
	dm_ग_लिखो_reg(tg->ctx, addr, value);

	/* Winकरोw B x axis start and end. */
	value = 0;
	addr = CRTC_REG(mmCRTC_CRC0_WINDOWB_X_CONTROL);
	set_reg_field_value(value, params->winकरोwb_x_start,
			    CRTC_CRC0_WINDOWB_X_CONTROL,
			    CRTC_CRC0_WINDOWB_X_START);
	set_reg_field_value(value, params->winकरोwb_x_end,
			    CRTC_CRC0_WINDOWB_X_CONTROL,
			    CRTC_CRC0_WINDOWB_X_END);
	dm_ग_लिखो_reg(tg->ctx, addr, value);

	/* Winकरोw B y axis start and end. */
	value = 0;
	addr = CRTC_REG(mmCRTC_CRC0_WINDOWB_Y_CONTROL);
	set_reg_field_value(value, params->winकरोwb_y_start,
			    CRTC_CRC0_WINDOWB_Y_CONTROL,
			    CRTC_CRC0_WINDOWB_Y_START);
	set_reg_field_value(value, params->winकरोwb_y_end,
			    CRTC_CRC0_WINDOWB_Y_CONTROL,
			    CRTC_CRC0_WINDOWB_Y_END);
	dm_ग_लिखो_reg(tg->ctx, addr, value);

	/* Set crc mode and selection, and enable. Only using CRC0*/
	value = 0;
	set_reg_field_value(value, params->continuous_mode ? 1 : 0,
			    CRTC_CRC_CNTL, CRTC_CRC_CONT_EN);
	set_reg_field_value(value, params->selection,
			    CRTC_CRC_CNTL, CRTC_CRC0_SELECT);
	set_reg_field_value(value, 1, CRTC_CRC_CNTL, CRTC_CRC_EN);
	dm_ग_लिखो_reg(tg->ctx, cntl_addr, value);

	वापस true;
पूर्ण

bool dce110_get_crc(काष्ठा timing_generator *tg,
		    uपूर्णांक32_t *r_cr, uपूर्णांक32_t *g_y, uपूर्णांक32_t *b_cb)
अणु
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t field = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	addr = CRTC_REG(mmCRTC_CRC_CNTL);
	value = dm_पढ़ो_reg(tg->ctx, addr);
	field = get_reg_field_value(value, CRTC_CRC_CNTL, CRTC_CRC_EN);

	/* Early वापस अगर CRC is not enabled क्रम this CRTC */
	अगर (!field)
		वापस false;

	addr = CRTC_REG(mmCRTC_CRC0_DATA_RG);
	value = dm_पढ़ो_reg(tg->ctx, addr);
	*r_cr = get_reg_field_value(value, CRTC_CRC0_DATA_RG, CRC0_R_CR);
	*g_y = get_reg_field_value(value, CRTC_CRC0_DATA_RG, CRC0_G_Y);

	addr = CRTC_REG(mmCRTC_CRC0_DATA_B);
	value = dm_पढ़ो_reg(tg->ctx, addr);
	*b_cb = get_reg_field_value(value, CRTC_CRC0_DATA_B, CRC0_B_CB);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा timing_generator_funcs dce110_tg_funcs = अणु
		.validate_timing = dce110_tg_validate_timing,
		.program_timing = dce110_tg_program_timing,
		.enable_crtc = dce110_timing_generator_enable_crtc,
		.disable_crtc = dce110_timing_generator_disable_crtc,
		.is_counter_moving = dce110_timing_generator_is_counter_moving,
		.get_position = dce110_timing_generator_get_position,
		.get_frame_count = dce110_timing_generator_get_vblank_counter,
		.get_scanoutpos = dce110_timing_generator_get_crtc_scanoutpos,
		.set_early_control = dce110_timing_generator_set_early_control,
		.रुको_क्रम_state = dce110_tg_रुको_क्रम_state,
		.set_blank = dce110_tg_set_blank,
		.is_blanked = dce110_tg_is_blanked,
		.set_colors = dce110_tg_set_colors,
		.set_overscan_blank_color =
				dce110_timing_generator_set_overscan_color_black,
		.set_blank_color = dce110_timing_generator_program_blank_color,
		.disable_vga = dce110_timing_generator_disable_vga,
		.did_triggered_reset_occur =
				dce110_timing_generator_did_triggered_reset_occur,
		.setup_global_swap_lock =
				dce110_timing_generator_setup_global_swap_lock,
		.enable_reset_trigger = dce110_timing_generator_enable_reset_trigger,
		.enable_crtc_reset = dce110_timing_generator_enable_crtc_reset,
		.disable_reset_trigger = dce110_timing_generator_disable_reset_trigger,
		.tear_करोwn_global_swap_lock =
				dce110_timing_generator_tear_करोwn_global_swap_lock,
		.enable_advanced_request =
				dce110_timing_generator_enable_advanced_request,
		.set_drr =
				dce110_timing_generator_set_drr,
		.set_अटल_screen_control =
			dce110_timing_generator_set_अटल_screen_control,
		.set_test_pattern = dce110_timing_generator_set_test_pattern,
		.arm_vert_पूर्णांकr = dce110_arm_vert_पूर्णांकr,
		.is_tg_enabled = dce110_is_tg_enabled,
		.configure_crc = dce110_configure_crc,
		.get_crc = dce110_get_crc,
पूर्ण;

व्योम dce110_timing_generator_स्थिरruct(
	काष्ठा dce110_timing_generator *tg110,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t instance,
	स्थिर काष्ठा dce110_timing_generator_offsets *offsets)
अणु
	tg110->controller_id = CONTROLLER_ID_D0 + instance;
	tg110->base.inst = instance;

	tg110->offsets = *offsets;

	tg110->base.funcs = &dce110_tg_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_total = CRTC_H_TOTAL__CRTC_H_TOTAL_MASK + 1;
	tg110->max_v_total = CRTC_V_TOTAL__CRTC_V_TOTAL_MASK + 1;

	tg110->min_h_blank = 56;
	tg110->min_h_front_porch = 4;
	tg110->min_h_back_porch = 4;
पूर्ण
