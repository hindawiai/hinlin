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
#समावेश "dcn30_optc.h"
#समावेश "dc.h"
#समावेश "dcn_calc_math.h"

#घोषणा REG(reg)\
	optc1->tg_regs->reg

#घोषणा CTX \
	optc1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	optc1->tg_shअगरt->field_name, optc1->tg_mask->field_name

व्योम optc3_triplebuffer_lock(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OTG_GLOBAL_CONTROL2,
		OTG_MASTER_UPDATE_LOCK_SEL, optc->inst);

	REG_SET(OTG_VUPDATE_KEEPOUT, 0,
		OTG_MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_EN, 1);

	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
		OTG_MASTER_UPDATE_LOCK, 1);

	अगर (optc->ctx->dce_environment != DCE_ENV_FPGA_MAXIMUS)
		REG_WAIT(OTG_MASTER_UPDATE_LOCK,
				UPDATE_LOCK_STATUS, 1,
				1, 10);
पूर्ण

व्योम optc3_lock_द्विगुनbuffer_enable(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t v_blank_start = 0;
	uपूर्णांक32_t v_blank_end = 0;
	uपूर्णांक32_t h_blank_start = 0;
	uपूर्णांक32_t h_blank_end = 0;

	REG_GET_2(OTG_V_BLANK_START_END,
		OTG_V_BLANK_START, &v_blank_start,
		OTG_V_BLANK_END, &v_blank_end);
	REG_GET_2(OTG_H_BLANK_START_END,
		OTG_H_BLANK_START, &h_blank_start,
		OTG_H_BLANK_END, &h_blank_end);

	REG_UPDATE_2(OTG_GLOBAL_CONTROL1,
		MASTER_UPDATE_LOCK_DB_START_Y, v_blank_start,
		MASTER_UPDATE_LOCK_DB_END_Y, v_blank_end);
	REG_UPDATE_2(OTG_GLOBAL_CONTROL4,
		DIG_UPDATE_POSITION_X, 20,
		DIG_UPDATE_POSITION_Y, v_blank_start);
	REG_UPDATE_3(OTG_GLOBAL_CONTROL0,
		MASTER_UPDATE_LOCK_DB_START_X, h_blank_start - 200 - 1,
		MASTER_UPDATE_LOCK_DB_END_X, h_blank_end,
		MASTER_UPDATE_LOCK_DB_EN, 1);
	REG_UPDATE(OTG_GLOBAL_CONTROL2, GLOBAL_UPDATE_LOCK_EN, 1);
पूर्ण

व्योम optc3_lock_द्विगुनbuffer_disable(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE_2(OTG_GLOBAL_CONTROL0,
		MASTER_UPDATE_LOCK_DB_START_X, 0,
		MASTER_UPDATE_LOCK_DB_END_X, 0);
	REG_UPDATE_2(OTG_GLOBAL_CONTROL1,
		MASTER_UPDATE_LOCK_DB_START_Y, 0,
		MASTER_UPDATE_LOCK_DB_END_Y, 0);

	REG_UPDATE(OTG_GLOBAL_CONTROL2, GLOBAL_UPDATE_LOCK_EN, 0);
	REG_UPDATE(OTG_GLOBAL_CONTROL0, MASTER_UPDATE_LOCK_DB_EN, 1);
पूर्ण

व्योम optc3_lock(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OTG_GLOBAL_CONTROL2,
		OTG_MASTER_UPDATE_LOCK_SEL, optc->inst);
	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
		OTG_MASTER_UPDATE_LOCK, 1);

	/* Should be fast, status करोes not update on maximus */
	अगर (optc->ctx->dce_environment != DCE_ENV_FPGA_MAXIMUS)
		REG_WAIT(OTG_MASTER_UPDATE_LOCK,
				UPDATE_LOCK_STATUS, 1,
				1, 10);
पूर्ण

व्योम optc3_set_out_mux(काष्ठा timing_generator *optc, क्रमागत otg_out_mux_dest dest)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OTG_CONTROL, OTG_OUT_MUX, dest);
पूर्ण

व्योम optc3_program_blank_color(काष्ठा timing_generator *optc,
		स्थिर काष्ठा tg_color *blank_color)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_3(OTG_BLANK_DATA_COLOR, 0,
		OTG_BLANK_DATA_COLOR_BLUE_CB, blank_color->color_b_cb,
		OTG_BLANK_DATA_COLOR_GREEN_Y, blank_color->color_g_y,
		OTG_BLANK_DATA_COLOR_RED_CR, blank_color->color_r_cr);

	REG_SET_3(OTG_BLANK_DATA_COLOR_EXT, 0,
		OTG_BLANK_DATA_COLOR_BLUE_CB_EXT, blank_color->color_b_cb >> 10,
		OTG_BLANK_DATA_COLOR_GREEN_Y_EXT, blank_color->color_g_y >> 10,
		OTG_BLANK_DATA_COLOR_RED_CR_EXT, blank_color->color_r_cr >> 10);
पूर्ण

व्योम optc3_set_drr_trigger_winकरोw(काष्ठा timing_generator *optc,
		uपूर्णांक32_t winकरोw_start, uपूर्णांक32_t winकरोw_end)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_2(OTG_DRR_TRIGGER_WINDOW, 0,
		OTG_DRR_TRIGGER_WINDOW_START_X, winकरोw_start,
		OTG_DRR_TRIGGER_WINDOW_END_X, winकरोw_end);
पूर्ण

व्योम optc3_set_vtotal_change_limit(काष्ठा timing_generator *optc,
		uपूर्णांक32_t limit)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);


	REG_SET(OTG_DRR_V_TOTAL_CHANGE, 0,
		OTG_DRR_V_TOTAL_CHANGE_LIMIT, limit);
पूर्ण


/* Set DSC-related configuration.
 *   dsc_mode: 0 disables DSC, other values enable DSC in specअगरied क्रमmat
 *   sc_bytes_per_pixel: Bytes per pixel in u3.28 क्रमmat
 *   dsc_slice_width: Slice width in pixels
 */
व्योम optc3_set_dsc_config(काष्ठा timing_generator *optc,
		क्रमागत optc_dsc_mode dsc_mode,
		uपूर्णांक32_t dsc_bytes_per_pixel,
		uपूर्णांक32_t dsc_slice_width)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	optc2_set_dsc_config(optc, dsc_mode, dsc_bytes_per_pixel,
		dsc_slice_width);

		REG_UPDATE(OTG_V_SYNC_A_CNTL, OTG_V_SYNC_MODE, 0);

पूर्ण

व्योम optc3_set_odm_bypass(काष्ठा timing_generator *optc,
		स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	क्रमागत h_timing_भाग_mode h_भाग = H_TIMING_NO_DIV;

	REG_SET_5(OPTC_DATA_SOURCE_SELECT, 0,
			OPTC_NUM_OF_INPUT_SEGMENT, 0,
			OPTC_SEG0_SRC_SEL, optc->inst,
			OPTC_SEG1_SRC_SEL, 0xf,
			OPTC_SEG2_SRC_SEL, 0xf,
			OPTC_SEG3_SRC_SEL, 0xf
			);

	h_भाग = optc1_is_two_pixels_per_contaपूर्णांकer(dc_crtc_timing);
	REG_SET(OTG_H_TIMING_CNTL, 0,
			OTG_H_TIMING_DIV_MODE, h_भाग);

	REG_SET(OPTC_MEMORY_CONFIG, 0,
			OPTC_MEM_SEL, 0);
	optc1->opp_count = 1;
पूर्ण

अटल व्योम optc3_set_odm_combine(काष्ठा timing_generator *optc, पूर्णांक *opp_id, पूर्णांक opp_cnt,
		काष्ठा dc_crtc_timing *timing)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	पूर्णांक mpcc_hactive = (timing->h_addressable + timing->h_border_left + timing->h_border_right)
			/ opp_cnt;
	uपूर्णांक32_t memory_mask = 0;

	/* TODO: In pseuकरोcode but करोes not affect maximus, delete comment अगर we करोnt need on asic
	 * REG_SET(OTG_GLOBAL_CONTROL2, 0, GLOBAL_UPDATE_LOCK_EN, 1);
	 * Program OTG रेजिस्टर MASTER_UPDATE_LOCK_DB_X/Y to the position beक्रमe DP frame start
	 * REG_SET_2(OTG_GLOBAL_CONTROL1, 0,
	 *		MASTER_UPDATE_LOCK_DB_X, 160,
	 *		MASTER_UPDATE_LOCK_DB_Y, 240);
	 */

	ASSERT(opp_cnt == 2 || opp_cnt == 4);

	/* 2 pieces of memory required क्रम up to 5120 displays, 4 क्रम up to 8192,
	 * however, क्रम ODM combine we can simplअगरy by always using 4.
	 */
	अगर (opp_cnt == 2) अणु
		/* To make sure there's no memory overlap, each instance "reserves" 2
		 * memories and they are uniquely combined here.
		 */
		memory_mask = 0x3 << (opp_id[0] * 2) | 0x3 << (opp_id[1] * 2);
	पूर्ण अन्यथा अगर (opp_cnt == 4) अणु
		/* To make sure there's no memory overlap, each instance "reserves" 1
		 * memory and they are uniquely combined here.
		 */
		memory_mask = 0x1 << (opp_id[0] * 2) | 0x1 << (opp_id[1] * 2) | 0x1 << (opp_id[2] * 2) | 0x1 << (opp_id[3] * 2);
	पूर्ण

	अगर (REG(OPTC_MEMORY_CONFIG))
		REG_SET(OPTC_MEMORY_CONFIG, 0,
			OPTC_MEM_SEL, memory_mask);

	अगर (opp_cnt == 2) अणु
		REG_SET_3(OPTC_DATA_SOURCE_SELECT, 0,
				OPTC_NUM_OF_INPUT_SEGMENT, 1,
				OPTC_SEG0_SRC_SEL, opp_id[0],
				OPTC_SEG1_SRC_SEL, opp_id[1]);
	पूर्ण अन्यथा अगर (opp_cnt == 4) अणु
		REG_SET_5(OPTC_DATA_SOURCE_SELECT, 0,
				OPTC_NUM_OF_INPUT_SEGMENT, 3,
				OPTC_SEG0_SRC_SEL, opp_id[0],
				OPTC_SEG1_SRC_SEL, opp_id[1],
				OPTC_SEG2_SRC_SEL, opp_id[2],
				OPTC_SEG3_SRC_SEL, opp_id[3]);
	पूर्ण

	REG_UPDATE(OPTC_WIDTH_CONTROL,
			OPTC_SEGMENT_WIDTH, mpcc_hactive);

	REG_SET(OTG_H_TIMING_CNTL, 0, OTG_H_TIMING_DIV_MODE, opp_cnt - 1);
	optc1->opp_count = opp_cnt;
पूर्ण

/**
 * optc3_set_timing_द्विगुन_buffer() - DRR द्विगुन buffering control
 *
 * Sets द्विगुन buffer poपूर्णांक क्रम V_TOTAL, H_TOTAL, VTOTAL_MIN,
 * VTOTAL_MAX, VTOTAL_MIN_SEL and VTOTAL_MAX_SEL रेजिस्टरs.
 *
 * Options: any समय,  start of frame, dp start of frame (range timing)
 */
अटल व्योम optc3_set_timing_द्विगुन_buffer(काष्ठा timing_generator *optc, bool enable)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t mode = enable ? 2 : 0;

	REG_UPDATE(OTG_DOUBLE_BUFFER_CONTROL,
		   OTG_DRR_TIMING_DBUF_UPDATE_MODE, mode);
पूर्ण

व्योम optc3_tg_init(काष्ठा timing_generator *optc)
अणु
	optc3_set_timing_द्विगुन_buffer(optc, true);
	optc1_clear_optc_underflow(optc);
पूर्ण

अटल काष्ठा timing_generator_funcs dcn30_tg_funcs = अणु
		.validate_timing = optc1_validate_timing,
		.program_timing = optc1_program_timing,
		.setup_vertical_पूर्णांकerrupt0 = optc1_setup_vertical_पूर्णांकerrupt0,
		.setup_vertical_पूर्णांकerrupt1 = optc1_setup_vertical_पूर्णांकerrupt1,
		.setup_vertical_पूर्णांकerrupt2 = optc1_setup_vertical_पूर्णांकerrupt2,
		.program_global_sync = optc1_program_global_sync,
		.enable_crtc = optc2_enable_crtc,
		.disable_crtc = optc1_disable_crtc,
		/* used by enable_timing_synchronization. Not need क्रम FPGA */
		.is_counter_moving = optc1_is_counter_moving,
		.get_position = optc1_get_position,
		.get_frame_count = optc1_get_vblank_counter,
		.get_scanoutpos = optc1_get_crtc_scanoutpos,
		.get_otg_active_size = optc1_get_otg_active_size,
		.set_early_control = optc1_set_early_control,
		/* used by enable_timing_synchronization. Not need क्रम FPGA */
		.रुको_क्रम_state = optc1_रुको_क्रम_state,
		.set_blank_color = optc3_program_blank_color,
		.did_triggered_reset_occur = optc1_did_triggered_reset_occur,
		.triplebuffer_lock = optc3_triplebuffer_lock,
		.triplebuffer_unlock = optc2_triplebuffer_unlock,
		.enable_reset_trigger = optc1_enable_reset_trigger,
		.enable_crtc_reset = optc1_enable_crtc_reset,
		.disable_reset_trigger = optc1_disable_reset_trigger,
		.lock = optc3_lock,
		.is_locked = optc1_is_locked,
		.unlock = optc1_unlock,
		.lock_द्विगुनbuffer_enable = optc3_lock_द्विगुनbuffer_enable,
		.lock_द्विगुनbuffer_disable = optc3_lock_द्विगुनbuffer_disable,
		.enable_optc_घड़ी = optc1_enable_optc_घड़ी,
		.set_drr = optc1_set_drr,
		.set_अटल_screen_control = optc1_set_अटल_screen_control,
		.program_stereo = optc1_program_stereo,
		.is_stereo_left_eye = optc1_is_stereo_left_eye,
		.tg_init = optc3_tg_init,
		.is_tg_enabled = optc1_is_tg_enabled,
		.is_optc_underflow_occurred = optc1_is_optc_underflow_occurred,
		.clear_optc_underflow = optc1_clear_optc_underflow,
		.setup_global_swap_lock = शून्य,
		.get_crc = optc1_get_crc,
		.configure_crc = optc2_configure_crc,
		.set_dsc_config = optc3_set_dsc_config,
		.set_dwb_source = शून्य,
		.set_odm_bypass = optc3_set_odm_bypass,
		.set_odm_combine = optc3_set_odm_combine,
		.get_optc_source = optc2_get_optc_source,
		.set_out_mux = optc3_set_out_mux,
		.set_drr_trigger_winकरोw = optc3_set_drr_trigger_winकरोw,
		.set_vtotal_change_limit = optc3_set_vtotal_change_limit,
		.set_gsl = optc2_set_gsl,
		.set_gsl_source_select = optc2_set_gsl_source_select,
		.set_vtg_params = optc1_set_vtg_params,
		.program_manual_trigger = optc2_program_manual_trigger,
		.setup_manual_trigger = optc2_setup_manual_trigger,
		.get_hw_timing = optc1_get_hw_timing,
पूर्ण;

व्योम dcn30_timing_generator_init(काष्ठा optc *optc1)
अणु
	optc1->base.funcs = &dcn30_tg_funcs;

	optc1->max_h_total = optc1->tg_mask->OTG_H_TOTAL + 1;
	optc1->max_v_total = optc1->tg_mask->OTG_V_TOTAL + 1;

	optc1->min_h_blank = 32;
	optc1->min_v_blank = 3;
	optc1->min_v_blank_पूर्णांकerlace = 5;
	optc1->min_h_sync_width = 4;
	optc1->min_v_sync_width = 1;
पूर्ण

