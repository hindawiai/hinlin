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


#समावेश "reg_helper.h"
#समावेश "dcn10_optc.h"
#समावेश "dc.h"

#घोषणा REG(reg)\
	optc1->tg_regs->reg

#घोषणा CTX \
	optc1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	optc1->tg_shअगरt->field_name, optc1->tg_mask->field_name

#घोषणा STATIC_SCREEN_EVENT_MASK_RANGETIMING_DOUBLE_BUFFER_UPDATE_EN 0x100

/**
* apply_front_porch_workaround  TODO FPGA still need?
*
* This is a workaround क्रम a bug that has existed since R5xx and has not been
* fixed keep Front porch at minimum 2 क्रम Interlaced mode or 1 क्रम progressive.
*/
अटल व्योम apply_front_porch_workaround(काष्ठा dc_crtc_timing *timing)
अणु
	अगर (timing->flags.INTERLACE == 1) अणु
		अगर (timing->v_front_porch < 2)
			timing->v_front_porch = 2;
	पूर्ण अन्यथा अणु
		अगर (timing->v_front_porch < 1)
			timing->v_front_porch = 1;
	पूर्ण
पूर्ण

व्योम optc1_program_global_sync(
		काष्ठा timing_generator *optc,
		पूर्णांक vपढ़ोy_offset,
		पूर्णांक vstartup_start,
		पूर्णांक vupdate_offset,
		पूर्णांक vupdate_width)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	optc1->vपढ़ोy_offset = vपढ़ोy_offset;
	optc1->vstartup_start = vstartup_start;
	optc1->vupdate_offset = vupdate_offset;
	optc1->vupdate_width = vupdate_width;

	अगर (optc1->vstartup_start == 0) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	REG_SET(OTG_VSTARTUP_PARAM, 0,
		VSTARTUP_START, optc1->vstartup_start);

	REG_SET_2(OTG_VUPDATE_PARAM, 0,
			VUPDATE_OFFSET, optc1->vupdate_offset,
			VUPDATE_WIDTH, optc1->vupdate_width);

	REG_SET(OTG_VREADY_PARAM, 0,
			VREADY_OFFSET, optc1->vपढ़ोy_offset);
पूर्ण

अटल व्योम optc1_disable_stereo(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_STEREO_CONTROL, 0,
		OTG_STEREO_EN, 0);

	REG_SET_2(OTG_3D_STRUCTURE_CONTROL, 0,
		OTG_3D_STRUCTURE_EN, 0,
		OTG_3D_STRUCTURE_STEREO_SEL_OVR, 0);
पूर्ण

व्योम optc1_setup_vertical_पूर्णांकerrupt0(
		काष्ठा timing_generator *optc,
		uपूर्णांक32_t start_line,
		uपूर्णांक32_t end_line)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_2(OTG_VERTICAL_INTERRUPT0_POSITION, 0,
			OTG_VERTICAL_INTERRUPT0_LINE_START, start_line,
			OTG_VERTICAL_INTERRUPT0_LINE_END, end_line);
पूर्ण

व्योम optc1_setup_vertical_पूर्णांकerrupt1(
		काष्ठा timing_generator *optc,
		uपूर्णांक32_t start_line)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_VERTICAL_INTERRUPT1_POSITION, 0,
				OTG_VERTICAL_INTERRUPT1_LINE_START, start_line);
पूर्ण

व्योम optc1_setup_vertical_पूर्णांकerrupt2(
		काष्ठा timing_generator *optc,
		uपूर्णांक32_t start_line)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_VERTICAL_INTERRUPT2_POSITION, 0,
			OTG_VERTICAL_INTERRUPT2_LINE_START, start_line);
पूर्ण

/**
 * Vupdate keepout can be set to a winकरोw to block the update lock क्रम that pipe from changing.
 * Start offset begins with vstartup and goes क्रम x number of घड़ीs,
 * end offset starts from end of vupdate to x number of घड़ीs.
 */
व्योम optc1_set_vupdate_keepout(काष्ठा timing_generator *optc,
			       काष्ठा vupdate_keepout_params *params)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_3(OTG_VUPDATE_KEEPOUT, 0,
		  MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_START_OFFSET, params->start_offset,
		  MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_END_OFFSET, params->end_offset,
		  OTG_MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_EN, params->enable);
पूर्ण

/**
 * program_timing_generator   used by mode timing set
 * Program CRTC Timing Registers - OTG_H_*, OTG_V_*, Pixel repetition.
 * Including SYNC. Call BIOS command table to program Timings.
 */
व्योम optc1_program_timing(
	काष्ठा timing_generator *optc,
	स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing,
	पूर्णांक vपढ़ोy_offset,
	पूर्णांक vstartup_start,
	पूर्णांक vupdate_offset,
	पूर्णांक vupdate_width,
	स्थिर क्रमागत संकेत_type संकेत,
	bool use_vbios)
अणु
	काष्ठा dc_crtc_timing patched_crtc_timing;
	uपूर्णांक32_t asic_blank_end;
	uपूर्णांक32_t asic_blank_start;
	uपूर्णांक32_t v_total;
	uपूर्णांक32_t v_sync_end;
	uपूर्णांक32_t h_sync_polarity, v_sync_polarity;
	uपूर्णांक32_t start_poपूर्णांक = 0;
	uपूर्णांक32_t field_num = 0;
	क्रमागत h_timing_भाग_mode h_भाग = H_TIMING_NO_DIV;

	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	optc1->संकेत = संकेत;
	optc1->vपढ़ोy_offset = vपढ़ोy_offset;
	optc1->vstartup_start = vstartup_start;
	optc1->vupdate_offset = vupdate_offset;
	optc1->vupdate_width = vupdate_width;
	patched_crtc_timing = *dc_crtc_timing;
	apply_front_porch_workaround(&patched_crtc_timing);

	/* Load horizontal timing */

	/* CRTC_H_TOTAL = vesa.h_total - 1 */
	REG_SET(OTG_H_TOTAL, 0,
			OTG_H_TOTAL,  patched_crtc_timing.h_total - 1);

	/* h_sync_start = 0, h_sync_end = vesa.h_sync_width */
	REG_UPDATE_2(OTG_H_SYNC_A,
			OTG_H_SYNC_A_START, 0,
			OTG_H_SYNC_A_END, patched_crtc_timing.h_sync_width);

	/* blank_start = line end - front porch */
	asic_blank_start = patched_crtc_timing.h_total -
			patched_crtc_timing.h_front_porch;

	/* blank_end = blank_start - active */
	asic_blank_end = asic_blank_start -
			patched_crtc_timing.h_border_right -
			patched_crtc_timing.h_addressable -
			patched_crtc_timing.h_border_left;

	REG_UPDATE_2(OTG_H_BLANK_START_END,
			OTG_H_BLANK_START, asic_blank_start,
			OTG_H_BLANK_END, asic_blank_end);

	/* h_sync polarity */
	h_sync_polarity = patched_crtc_timing.flags.HSYNC_POSITIVE_POLARITY ?
			0 : 1;

	REG_UPDATE(OTG_H_SYNC_A_CNTL,
			OTG_H_SYNC_A_POL, h_sync_polarity);

	v_total = patched_crtc_timing.v_total - 1;

	REG_SET(OTG_V_TOTAL, 0,
			OTG_V_TOTAL, v_total);

	/* In हाल of V_TOTAL_CONTROL is on, make sure OTG_V_TOTAL_MAX and
	 * OTG_V_TOTAL_MIN are equal to V_TOTAL.
	 */
	REG_SET(OTG_V_TOTAL_MAX, 0,
		OTG_V_TOTAL_MAX, v_total);
	REG_SET(OTG_V_TOTAL_MIN, 0,
		OTG_V_TOTAL_MIN, v_total);

	/* v_sync_start = 0, v_sync_end = v_sync_width */
	v_sync_end = patched_crtc_timing.v_sync_width;

	REG_UPDATE_2(OTG_V_SYNC_A,
			OTG_V_SYNC_A_START, 0,
			OTG_V_SYNC_A_END, v_sync_end);

	/* blank_start = frame end - front porch */
	asic_blank_start = patched_crtc_timing.v_total -
			patched_crtc_timing.v_front_porch;

	/* blank_end = blank_start - active */
	asic_blank_end = asic_blank_start -
			patched_crtc_timing.v_border_bottom -
			patched_crtc_timing.v_addressable -
			patched_crtc_timing.v_border_top;

	REG_UPDATE_2(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, asic_blank_start,
			OTG_V_BLANK_END, asic_blank_end);

	/* v_sync polarity */
	v_sync_polarity = patched_crtc_timing.flags.VSYNC_POSITIVE_POLARITY ?
			0 : 1;

	REG_UPDATE(OTG_V_SYNC_A_CNTL,
		OTG_V_SYNC_A_POL, v_sync_polarity);

	अगर (optc1->संकेत == SIGNAL_TYPE_DISPLAY_PORT ||
			optc1->संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST ||
			optc1->संकेत == SIGNAL_TYPE_EDP) अणु
		start_poपूर्णांक = 1;
		अगर (patched_crtc_timing.flags.INTERLACE == 1)
			field_num = 1;
	पूर्ण

	/* Interlace */
	अगर (REG(OTG_INTERLACE_CONTROL)) अणु
		अगर (patched_crtc_timing.flags.INTERLACE == 1)
			REG_UPDATE(OTG_INTERLACE_CONTROL,
					OTG_INTERLACE_ENABLE, 1);
		अन्यथा
			REG_UPDATE(OTG_INTERLACE_CONTROL,
					OTG_INTERLACE_ENABLE, 0);
	पूर्ण

	/* VTG enable set to 0 first VInit */
	REG_UPDATE(CONTROL,
			VTG0_ENABLE, 0);

	/* original code is using VTG offset to address OTG reg, seems wrong */
	REG_UPDATE_2(OTG_CONTROL,
			OTG_START_POINT_CNTL, start_poपूर्णांक,
			OTG_FIELD_NUMBER_CNTL, field_num);

	optc->funcs->program_global_sync(optc,
			vपढ़ोy_offset,
			vstartup_start,
			vupdate_offset,
			vupdate_width);

	optc->funcs->set_vtg_params(optc, dc_crtc_timing, true);

	/* TODO
	 * patched_crtc_timing.flags.HORZ_COUNT_BY_TWO == 1
	 * program_horz_count_by_2
	 * क्रम DVI 30bpp mode, 0 otherwise
	 * program_horz_count_by_2(optc, &patched_crtc_timing);
	 */

	/* Enable stereo - only when we need to pack 3D frame. Other types
	 * of stereo handled in explicit call
	 */

	अगर (optc1_is_two_pixels_per_contaपूर्णांकer(&patched_crtc_timing) || optc1->opp_count == 2)
		h_भाग = H_TIMING_DIV_BY2;

	अगर (REG(OPTC_DATA_FORMAT_CONTROL)) अणु
		uपूर्णांक32_t data_fmt = 0;

		अगर (patched_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
			data_fmt = 1;
		अन्यथा अगर (patched_crtc_timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
			data_fmt = 2;

		REG_UPDATE(OPTC_DATA_FORMAT_CONTROL, OPTC_DATA_FORMAT, data_fmt);
	पूर्ण

	अगर (optc1->tg_mask->OTG_H_TIMING_DIV_MODE != 0) अणु
		अगर (optc1->opp_count == 4)
			h_भाग = H_TIMING_DIV_BY4;

		REG_UPDATE(OTG_H_TIMING_CNTL,
		OTG_H_TIMING_DIV_MODE, h_भाग);
	पूर्ण अन्यथा अणु
		REG_UPDATE(OTG_H_TIMING_CNTL,
		OTG_H_TIMING_DIV_BY2, h_भाग);
	पूर्ण
पूर्ण

व्योम optc1_set_vtg_params(काष्ठा timing_generator *optc,
		स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing, bool program_fp2)
अणु
	काष्ठा dc_crtc_timing patched_crtc_timing;
	uपूर्णांक32_t asic_blank_end;
	uपूर्णांक32_t v_init;
	uपूर्णांक32_t v_fp2 = 0;
	पूर्णांक32_t vertical_line_start;

	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	patched_crtc_timing = *dc_crtc_timing;
	apply_front_porch_workaround(&patched_crtc_timing);

	/* VCOUNT_INIT is the start of blank */
	v_init = patched_crtc_timing.v_total - patched_crtc_timing.v_front_porch;

	/* end of blank = v_init - active */
	asic_blank_end = v_init -
			patched_crtc_timing.v_border_bottom -
			patched_crtc_timing.v_addressable -
			patched_crtc_timing.v_border_top;

	/* अगर VSTARTUP is beक्रमe VSYNC, FP2 is the offset, otherwise 0 */
	vertical_line_start = asic_blank_end - optc1->vstartup_start + 1;
	अगर (vertical_line_start < 0)
		v_fp2 = -vertical_line_start;

	/* Interlace */
	अगर (REG(OTG_INTERLACE_CONTROL)) अणु
		अगर (patched_crtc_timing.flags.INTERLACE == 1) अणु
			v_init = v_init / 2;
			अगर ((optc1->vstartup_start/2)*2 > asic_blank_end)
				v_fp2 = v_fp2 / 2;
		पूर्ण
	पूर्ण

	अगर (program_fp2)
		REG_UPDATE_2(CONTROL,
				VTG0_FP2, v_fp2,
				VTG0_VCOUNT_INIT, v_init);
	अन्यथा
		REG_UPDATE(CONTROL, VTG0_VCOUNT_INIT, v_init);
पूर्ण

व्योम optc1_set_blank_data_द्विगुन_buffer(काष्ठा timing_generator *optc, bool enable)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	uपूर्णांक32_t blank_data_द्विगुन_buffer_enable = enable ? 1 : 0;

	REG_UPDATE(OTG_DOUBLE_BUFFER_CONTROL,
			OTG_BLANK_DATA_DOUBLE_BUFFER_EN, blank_data_द्विगुन_buffer_enable);
पूर्ण

/**
 * optc1_set_timing_द्विगुन_buffer() - DRR द्विगुन buffering control
 *
 * Sets द्विगुन buffer poपूर्णांक क्रम V_TOTAL, H_TOTAL, VTOTAL_MIN,
 * VTOTAL_MAX, VTOTAL_MIN_SEL and VTOTAL_MAX_SEL रेजिस्टरs.
 *
 * Options: any समय,  start of frame, dp start of frame (range timing)
 */
व्योम optc1_set_timing_द्विगुन_buffer(काष्ठा timing_generator *optc, bool enable)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t mode = enable ? 2 : 0;

	REG_UPDATE(OTG_DOUBLE_BUFFER_CONTROL,
		   OTG_RANGE_TIMING_DBUF_UPDATE_MODE, mode);
पूर्ण

/**
 * unblank_crtc
 * Call ASIC Control Object to UnBlank CRTC.
 */
अटल व्योम optc1_unblank_crtc(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE_2(OTG_BLANK_CONTROL,
			OTG_BLANK_DATA_EN, 0,
			OTG_BLANK_DE_MODE, 0);

	/* W/A क्रम स्वतःmated testing
	 * Automated testing will fail underflow test as there
	 * sporadic underflows which occur during the optc blank
	 * sequence.  As a w/a, clear underflow on unblank.
	 * This prevents the failure, but will not mask actual
	 * underflow that affect real use हालs.
	 */
	optc1_clear_optc_underflow(optc);
पूर्ण

/**
 * blank_crtc
 * Call ASIC Control Object to Blank CRTC.
 */

अटल व्योम optc1_blank_crtc(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE_2(OTG_BLANK_CONTROL,
			OTG_BLANK_DATA_EN, 1,
			OTG_BLANK_DE_MODE, 0);

	optc1_set_blank_data_द्विगुन_buffer(optc, false);
पूर्ण

व्योम optc1_set_blank(काष्ठा timing_generator *optc,
		bool enable_blanking)
अणु
	अगर (enable_blanking)
		optc1_blank_crtc(optc);
	अन्यथा
		optc1_unblank_crtc(optc);
पूर्ण

bool optc1_is_blanked(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t blank_en;
	uपूर्णांक32_t blank_state;

	REG_GET_2(OTG_BLANK_CONTROL,
			OTG_BLANK_DATA_EN, &blank_en,
			OTG_CURRENT_BLANK_STATE, &blank_state);

	वापस blank_en && blank_state;
पूर्ण

व्योम optc1_enable_optc_घड़ी(काष्ठा timing_generator *optc, bool enable)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	अगर (enable) अणु
		REG_UPDATE_2(OPTC_INPUT_CLOCK_CONTROL,
				OPTC_INPUT_CLK_EN, 1,
				OPTC_INPUT_CLK_GATE_DIS, 1);

		REG_WAIT(OPTC_INPUT_CLOCK_CONTROL,
				OPTC_INPUT_CLK_ON, 1,
				1, 1000);

		/* Enable घड़ी */
		REG_UPDATE_2(OTG_CLOCK_CONTROL,
				OTG_CLOCK_EN, 1,
				OTG_CLOCK_GATE_DIS, 1);
		REG_WAIT(OTG_CLOCK_CONTROL,
				OTG_CLOCK_ON, 1,
				1, 1000);
	पूर्ण अन्यथा  अणु
		REG_UPDATE_2(OTG_CLOCK_CONTROL,
				OTG_CLOCK_GATE_DIS, 0,
				OTG_CLOCK_EN, 0);

		REG_UPDATE_2(OPTC_INPUT_CLOCK_CONTROL,
				OPTC_INPUT_CLK_GATE_DIS, 0,
				OPTC_INPUT_CLK_EN, 0);
	पूर्ण
पूर्ण

/**
 * Enable CRTC
 * Enable CRTC - call ASIC Control Object to enable Timing generator.
 */
अटल bool optc1_enable_crtc(काष्ठा timing_generator *optc)
अणु
	/* TODO FPGA रुको क्रम answer
	 * OTG_MASTER_UPDATE_MODE != CRTC_MASTER_UPDATE_MODE
	 * OTG_MASTER_UPDATE_LOCK != CRTC_MASTER_UPDATE_LOCK
	 */
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	/* opp instance क्रम OTG. For DCN1.0, ODM is remoed.
	 * OPP and OPTC should 1:1 mapping
	 */
	REG_UPDATE(OPTC_DATA_SOURCE_SELECT,
			OPTC_SRC_SEL, optc->inst);

	/* VTG enable first is क्रम HW workaround */
	REG_UPDATE(CONTROL,
			VTG0_ENABLE, 1);

	REG_SEQ_START();

	/* Enable CRTC */
	REG_UPDATE_2(OTG_CONTROL,
			OTG_DISABLE_POINT_CNTL, 3,
			OTG_MASTER_EN, 1);

	REG_SEQ_SUBMIT();
	REG_SEQ_WAIT_DONE();

	वापस true;
पूर्ण

/* disable_crtc - call ASIC Control Object to disable Timing generator. */
bool optc1_disable_crtc(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	/* disable otg request until end of the first line
	 * in the vertical blank region
	 */
	REG_UPDATE_2(OTG_CONTROL,
			OTG_DISABLE_POINT_CNTL, 3,
			OTG_MASTER_EN, 0);

	REG_UPDATE(CONTROL,
			VTG0_ENABLE, 0);

	/* CRTC disabled, so disable  घड़ी. */
	REG_WAIT(OTG_CLOCK_CONTROL,
			OTG_BUSY, 0,
			1, 100000);

	वापस true;
पूर्ण


व्योम optc1_program_blank_color(
		काष्ठा timing_generator *optc,
		स्थिर काष्ठा tg_color *black_color)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_3(OTG_BLACK_COLOR, 0,
			OTG_BLACK_COLOR_B_CB, black_color->color_b_cb,
			OTG_BLACK_COLOR_G_Y, black_color->color_g_y,
			OTG_BLACK_COLOR_R_CR, black_color->color_r_cr);
पूर्ण

bool optc1_validate_timing(
	काष्ठा timing_generator *optc,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t v_blank;
	uपूर्णांक32_t h_blank;
	uपूर्णांक32_t min_v_blank;
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	ASSERT(timing != शून्य);

	v_blank = (timing->v_total - timing->v_addressable -
					timing->v_border_top - timing->v_border_bottom);

	h_blank = (timing->h_total - timing->h_addressable -
		timing->h_border_right -
		timing->h_border_left);

	अगर (timing->timing_3d_क्रमmat != TIMING_3D_FORMAT_NONE &&
		timing->timing_3d_क्रमmat != TIMING_3D_FORMAT_HW_FRAME_PACKING &&
		timing->timing_3d_क्रमmat != TIMING_3D_FORMAT_TOP_AND_BOTTOM &&
		timing->timing_3d_क्रमmat != TIMING_3D_FORMAT_SIDE_BY_SIDE &&
		timing->timing_3d_क्रमmat != TIMING_3D_FORMAT_FRAME_ALTERNATE &&
		timing->timing_3d_क्रमmat != TIMING_3D_FORMAT_INBAND_FA)
		वापस false;

	/* Temporarily blocking पूर्णांकerlacing mode until it's supported */
	अगर (timing->flags.INTERLACE == 1)
		वापस false;

	/* Check maximum number of pixels supported by Timing Generator
	 * (Currently will never fail, in order to fail needs display which
	 * needs more than 8192 horizontal and
	 * more than 8192 vertical total pixels)
	 */
	अगर (timing->h_total > optc1->max_h_total ||
		timing->v_total > optc1->max_v_total)
		वापस false;


	अगर (h_blank < optc1->min_h_blank)
		वापस false;

	अगर (timing->h_sync_width  < optc1->min_h_sync_width ||
		 timing->v_sync_width  < optc1->min_v_sync_width)
		वापस false;

	min_v_blank = timing->flags.INTERLACE?optc1->min_v_blank_पूर्णांकerlace:optc1->min_v_blank;

	अगर (v_blank < min_v_blank)
		वापस false;

	वापस true;

पूर्ण

/*
 * get_vblank_counter
 *
 * @brief
 * Get counter क्रम vertical blanks. use रेजिस्टर CRTC_STATUS_FRAME_COUNT which
 * holds the counter of frames.
 *
 * @param
 * काष्ठा timing_generator *optc - [in] timing generator which controls the
 * desired CRTC
 *
 * @वापस
 * Counter of frames, which should equal to number of vblanks.
 */
uपूर्णांक32_t optc1_get_vblank_counter(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t frame_count;

	REG_GET(OTG_STATUS_FRAME_COUNT,
		OTG_FRAME_COUNT, &frame_count);

	वापस frame_count;
पूर्ण

व्योम optc1_lock(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t regval = 0;

	regval = REG_READ(OTG_CONTROL);

	/* otg is not running, करो not need to be locked */
	अगर ((regval & 0x1) == 0x0)
		वापस;

	REG_SET(OTG_GLOBAL_CONTROL0, 0,
			OTG_MASTER_UPDATE_LOCK_SEL, optc->inst);
	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
			OTG_MASTER_UPDATE_LOCK, 1);

	/* Should be fast, status करोes not update on maximus */
	अगर (optc->ctx->dce_environment != DCE_ENV_FPGA_MAXIMUS) अणु

		REG_WAIT(OTG_MASTER_UPDATE_LOCK,
				UPDATE_LOCK_STATUS, 1,
				1, 10);
	पूर्ण
पूर्ण

व्योम optc1_unlock(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
			OTG_MASTER_UPDATE_LOCK, 0);
पूर्ण

bool optc1_is_locked(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t locked;

	REG_GET(OTG_MASTER_UPDATE_LOCK, UPDATE_LOCK_STATUS, &locked);

	वापस (locked == 1);
पूर्ण

व्योम optc1_get_position(काष्ठा timing_generator *optc,
		काष्ठा crtc_position *position)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_GET_2(OTG_STATUS_POSITION,
			OTG_HORZ_COUNT, &position->horizontal_count,
			OTG_VERT_COUNT, &position->vertical_count);

	REG_GET(OTG_NOM_VERT_POSITION,
			OTG_VERT_COUNT_NOM, &position->nominal_vcount);
पूर्ण

bool optc1_is_counter_moving(काष्ठा timing_generator *optc)
अणु
	काष्ठा crtc_position position1, position2;

	optc->funcs->get_position(optc, &position1);
	optc->funcs->get_position(optc, &position2);

	अगर (position1.horizontal_count == position2.horizontal_count &&
		position1.vertical_count == position2.vertical_count)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

bool optc1_did_triggered_reset_occur(
	काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t occurred_क्रमce, occurred_vsync;

	REG_GET(OTG_FORCE_COUNT_NOW_CNTL,
		OTG_FORCE_COUNT_NOW_OCCURRED, &occurred_क्रमce);

	REG_GET(OTG_VERT_SYNC_CONTROL,
		OTG_FORCE_VSYNC_NEXT_LINE_OCCURRED, &occurred_vsync);

	वापस occurred_vsync != 0 || occurred_क्रमce != 0;
पूर्ण

व्योम optc1_disable_reset_trigger(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_WRITE(OTG_TRIGA_CNTL, 0);

	REG_SET(OTG_FORCE_COUNT_NOW_CNTL, 0,
		OTG_FORCE_COUNT_NOW_CLEAR, 1);

	REG_SET(OTG_VERT_SYNC_CONTROL, 0,
		OTG_FORCE_VSYNC_NEXT_LINE_CLEAR, 1);
पूर्ण

व्योम optc1_enable_reset_trigger(काष्ठा timing_generator *optc, पूर्णांक source_tg_inst)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t falling_edge;

	REG_GET(OTG_V_SYNC_A_CNTL,
			OTG_V_SYNC_A_POL, &falling_edge);

	अगर (falling_edge)
		REG_SET_3(OTG_TRIGA_CNTL, 0,
				/* vsync संकेत from selected OTG pipe based
				 * on OTG_TRIG_SOURCE_PIPE_SELECT setting
				 */
				OTG_TRIGA_SOURCE_SELECT, 20,
				OTG_TRIGA_SOURCE_PIPE_SELECT, source_tg_inst,
				/* always detect falling edge */
				OTG_TRIGA_FALLING_EDGE_DETECT_CNTL, 1);
	अन्यथा
		REG_SET_3(OTG_TRIGA_CNTL, 0,
				/* vsync संकेत from selected OTG pipe based
				 * on OTG_TRIG_SOURCE_PIPE_SELECT setting
				 */
				OTG_TRIGA_SOURCE_SELECT, 20,
				OTG_TRIGA_SOURCE_PIPE_SELECT, source_tg_inst,
				/* always detect rising edge */
				OTG_TRIGA_RISING_EDGE_DETECT_CNTL, 1);

	REG_SET(OTG_FORCE_COUNT_NOW_CNTL, 0,
			/* क्रमce H count to H_TOTAL and V count to V_TOTAL in
			 * progressive mode and V_TOTAL-1 in पूर्णांकerlaced mode
			 */
			OTG_FORCE_COUNT_NOW_MODE, 2);
पूर्ण

व्योम optc1_enable_crtc_reset(
		काष्ठा timing_generator *optc,
		पूर्णांक source_tg_inst,
		काष्ठा crtc_trigger_info *crtc_tp)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t falling_edge = 0;
	uपूर्णांक32_t rising_edge = 0;

	चयन (crtc_tp->event) अणु

	हाल CRTC_EVENT_VSYNC_RISING:
		rising_edge = 1;
		अवरोध;

	हाल CRTC_EVENT_VSYNC_FALLING:
		falling_edge = 1;
		अवरोध;
	पूर्ण

	REG_SET_4(OTG_TRIGA_CNTL, 0,
		 /* vsync संकेत from selected OTG pipe based
		  * on OTG_TRIG_SOURCE_PIPE_SELECT setting
		  */
		  OTG_TRIGA_SOURCE_SELECT, 20,
		  OTG_TRIGA_SOURCE_PIPE_SELECT, source_tg_inst,
		  /* always detect falling edge */
		  OTG_TRIGA_RISING_EDGE_DETECT_CNTL, rising_edge,
		  OTG_TRIGA_FALLING_EDGE_DETECT_CNTL, falling_edge);

	चयन (crtc_tp->delay) अणु
	हाल TRIGGER_DELAY_NEXT_LINE:
		REG_SET(OTG_VERT_SYNC_CONTROL, 0,
				OTG_AUTO_FORCE_VSYNC_MODE, 1);
		अवरोध;
	हाल TRIGGER_DELAY_NEXT_PIXEL:
		REG_SET(OTG_FORCE_COUNT_NOW_CNTL, 0,
			/* क्रमce H count to H_TOTAL and V count to V_TOTAL in
			 * progressive mode and V_TOTAL-1 in पूर्णांकerlaced mode
			 */
			OTG_FORCE_COUNT_NOW_MODE, 2);
		अवरोध;
	पूर्ण
पूर्ण

व्योम optc1_रुको_क्रम_state(काष्ठा timing_generator *optc,
		क्रमागत crtc_state state)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	चयन (state) अणु
	हाल CRTC_STATE_VBLANK:
		REG_WAIT(OTG_STATUS,
				OTG_V_BLANK, 1,
				1, 100000); /* 1 vupdate at 10hz */
		अवरोध;

	हाल CRTC_STATE_VACTIVE:
		REG_WAIT(OTG_STATUS,
				OTG_V_ACTIVE_DISP, 1,
				1, 100000); /* 1 vupdate at 10hz */
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम optc1_set_early_control(
	काष्ठा timing_generator *optc,
	uपूर्णांक32_t early_cntl)
अणु
	/* asic design change, करो not need this control
	 * empty क्रम share caller logic
	 */
पूर्ण


व्योम optc1_set_अटल_screen_control(
	काष्ठा timing_generator *optc,
	uपूर्णांक32_t event_triggers,
	uपूर्णांक32_t num_frames)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	// By रेजिस्टर spec, it only takes 8 bit value
	अगर (num_frames > 0xFF)
		num_frames = 0xFF;

	/* Bit 8 is no दीर्घer applicable in RV क्रम PSR हाल,
	 * set bit 8 to 0 अगर given
	 */
	अगर ((event_triggers & STATIC_SCREEN_EVENT_MASK_RANGETIMING_DOUBLE_BUFFER_UPDATE_EN)
			!= 0)
		event_triggers = event_triggers &
		~STATIC_SCREEN_EVENT_MASK_RANGETIMING_DOUBLE_BUFFER_UPDATE_EN;

	REG_SET_2(OTG_STATIC_SCREEN_CONTROL, 0,
			OTG_STATIC_SCREEN_EVENT_MASK, event_triggers,
			OTG_STATIC_SCREEN_FRAME_COUNT, num_frames);
पूर्ण

व्योम optc1_setup_manual_trigger(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_GLOBAL_CONTROL2, 0,
			MANUAL_FLOW_CONTROL_SEL, optc->inst);

	REG_SET_8(OTG_TRIGA_CNTL, 0,
			OTG_TRIGA_SOURCE_SELECT, 22,
			OTG_TRIGA_SOURCE_PIPE_SELECT, optc->inst,
			OTG_TRIGA_RISING_EDGE_DETECT_CNTL, 1,
			OTG_TRIGA_FALLING_EDGE_DETECT_CNTL, 0,
			OTG_TRIGA_POLARITY_SELECT, 0,
			OTG_TRIGA_FREQUENCY_SELECT, 0,
			OTG_TRIGA_DELAY, 0,
			OTG_TRIGA_CLEAR, 1);
पूर्ण

व्योम optc1_program_manual_trigger(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_MANUAL_FLOW_CONTROL, 0,
			MANUAL_FLOW_CONTROL, 1);

	REG_SET(OTG_MANUAL_FLOW_CONTROL, 0,
			MANUAL_FLOW_CONTROL, 0);
पूर्ण


/**
 *****************************************************************************
 *  Function: set_drr
 *
 *  @brief
 *     Program dynamic refresh rate रेजिस्टरs m_OTGx_OTG_V_TOTAL_*.
 *
 *****************************************************************************
 */
व्योम optc1_set_drr(
	काष्ठा timing_generator *optc,
	स्थिर काष्ठा drr_params *params)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	अगर (params != शून्य &&
		params->vertical_total_max > 0 &&
		params->vertical_total_min > 0) अणु

		अगर (params->vertical_total_mid != 0) अणु

			REG_SET(OTG_V_TOTAL_MID, 0,
				OTG_V_TOTAL_MID, params->vertical_total_mid - 1);

			REG_UPDATE_2(OTG_V_TOTAL_CONTROL,
					OTG_VTOTAL_MID_REPLACING_MAX_EN, 1,
					OTG_VTOTAL_MID_FRAME_NUM,
					(uपूर्णांक8_t)params->vertical_total_mid_frame_num);

		पूर्ण

		REG_SET(OTG_V_TOTAL_MAX, 0,
			OTG_V_TOTAL_MAX, params->vertical_total_max - 1);

		REG_SET(OTG_V_TOTAL_MIN, 0,
			OTG_V_TOTAL_MIN, params->vertical_total_min - 1);

		REG_UPDATE_5(OTG_V_TOTAL_CONTROL,
				OTG_V_TOTAL_MIN_SEL, 1,
				OTG_V_TOTAL_MAX_SEL, 1,
				OTG_FORCE_LOCK_ON_EVENT, 0,
				OTG_SET_V_TOTAL_MIN_MASK_EN, 0,
				OTG_SET_V_TOTAL_MIN_MASK, 0);

		// Setup manual flow control क्रम खातापूर्ण via TRIG_A
		optc->funcs->setup_manual_trigger(optc);

	पूर्ण अन्यथा अणु
		REG_UPDATE_4(OTG_V_TOTAL_CONTROL,
				OTG_SET_V_TOTAL_MIN_MASK, 0,
				OTG_V_TOTAL_MIN_SEL, 0,
				OTG_V_TOTAL_MAX_SEL, 0,
				OTG_FORCE_LOCK_ON_EVENT, 0);

		REG_SET(OTG_V_TOTAL_MIN, 0,
			OTG_V_TOTAL_MIN, 0);

		REG_SET(OTG_V_TOTAL_MAX, 0,
			OTG_V_TOTAL_MAX, 0);
	पूर्ण
पूर्ण

अटल व्योम optc1_set_test_pattern(
	काष्ठा timing_generator *optc,
	/* TODO: replace 'controller_dp_test_pattern' by 'test_pattern_mode'
	 * because this is not DP-specअगरic (which is probably somewhere in DP
	 * encoder) */
	क्रमागत controller_dp_test_pattern test_pattern,
	क्रमागत dc_color_depth color_depth)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	क्रमागत test_pattern_color_क्रमmat bit_depth;
	क्रमागत test_pattern_dyn_range dyn_range;
	क्रमागत test_pattern_mode mode;
	uपूर्णांक32_t pattern_mask;
	uपूर्णांक32_t pattern_data;
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

		REG_UPDATE_2(OTG_TEST_PATTERN_PARAMETERS,
				OTG_TEST_PATTERN_VRES, 6,
				OTG_TEST_PATTERN_HRES, 6);

		REG_UPDATE_4(OTG_TEST_PATTERN_CONTROL,
				OTG_TEST_PATTERN_EN, 1,
				OTG_TEST_PATTERN_MODE, mode,
				OTG_TEST_PATTERN_DYNAMIC_RANGE, dyn_range,
				OTG_TEST_PATTERN_COLOR_FORMAT, bit_depth);
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

		REG_WRITE(OTG_TEST_PATTERN_PARAMETERS, 0);

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
		pattern_data = 0;
		क्रम (index = 0; index < 6; index++) अणु
			/* prepare color mask, first ग_लिखो PATTERN_DATA
			 * will have all zeros
			 */
			pattern_mask = (1 << index);

			/* ग_लिखो color component */
			REG_SET_2(OTG_TEST_PATTERN_COLOR, 0,
					OTG_TEST_PATTERN_MASK, pattern_mask,
					OTG_TEST_PATTERN_DATA, pattern_data);

			/* prepare next color component,
			 * will be written in the next iteration
			 */
			pattern_data = dst_color[index];
		पूर्ण
		/* ग_लिखो last color component,
		 * it's been alपढ़ोy prepared in the loop
		 */
		REG_SET_2(OTG_TEST_PATTERN_COLOR, 0,
				OTG_TEST_PATTERN_MASK, pattern_mask,
				OTG_TEST_PATTERN_DATA, pattern_data);

		/* enable test pattern */
		REG_UPDATE_4(OTG_TEST_PATTERN_CONTROL,
				OTG_TEST_PATTERN_EN, 1,
				OTG_TEST_PATTERN_MODE, mode,
				OTG_TEST_PATTERN_DYNAMIC_RANGE, 0,
				OTG_TEST_PATTERN_COLOR_FORMAT, bit_depth);
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

		चयन (bit_depth) अणु
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_6:
		अणु
			REG_UPDATE_5(OTG_TEST_PATTERN_PARAMETERS,
					OTG_TEST_PATTERN_INC0, inc_base,
					OTG_TEST_PATTERN_INC1, 0,
					OTG_TEST_PATTERN_HRES, 6,
					OTG_TEST_PATTERN_VRES, 6,
					OTG_TEST_PATTERN_RAMP0_OFFSET, 0);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
		अणु
			REG_UPDATE_5(OTG_TEST_PATTERN_PARAMETERS,
					OTG_TEST_PATTERN_INC0, inc_base,
					OTG_TEST_PATTERN_INC1, 0,
					OTG_TEST_PATTERN_HRES, 8,
					OTG_TEST_PATTERN_VRES, 6,
					OTG_TEST_PATTERN_RAMP0_OFFSET, 0);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
		अणु
			REG_UPDATE_5(OTG_TEST_PATTERN_PARAMETERS,
					OTG_TEST_PATTERN_INC0, inc_base,
					OTG_TEST_PATTERN_INC1, inc_base + 2,
					OTG_TEST_PATTERN_HRES, 8,
					OTG_TEST_PATTERN_VRES, 5,
					OTG_TEST_PATTERN_RAMP0_OFFSET, 384 << 6);
		पूर्ण
		अवरोध;
		शेष:
		अवरोध;
		पूर्ण

		REG_WRITE(OTG_TEST_PATTERN_COLOR, 0);

		/* enable test pattern */
		REG_WRITE(OTG_TEST_PATTERN_CONTROL, 0);

		REG_SET_4(OTG_TEST_PATTERN_CONTROL, 0,
				OTG_TEST_PATTERN_EN, 1,
				OTG_TEST_PATTERN_MODE, mode,
				OTG_TEST_PATTERN_DYNAMIC_RANGE, 0,
				OTG_TEST_PATTERN_COLOR_FORMAT, bit_depth);
	पूर्ण
	अवरोध;
	हाल CONTROLLER_DP_TEST_PATTERN_VIDEOMODE:
	अणु
		REG_WRITE(OTG_TEST_PATTERN_CONTROL, 0);
		REG_WRITE(OTG_TEST_PATTERN_COLOR, 0);
		REG_WRITE(OTG_TEST_PATTERN_PARAMETERS, 0);
	पूर्ण
	अवरोध;
	शेष:
		अवरोध;

	पूर्ण
पूर्ण

व्योम optc1_get_crtc_scanoutpos(
	काष्ठा timing_generator *optc,
	uपूर्णांक32_t *v_blank_start,
	uपूर्णांक32_t *v_blank_end,
	uपूर्णांक32_t *h_position,
	uपूर्णांक32_t *v_position)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	काष्ठा crtc_position position;

	REG_GET_2(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, v_blank_start,
			OTG_V_BLANK_END, v_blank_end);

	optc1_get_position(optc, &position);

	*h_position = position.horizontal_count;
	*v_position = position.vertical_count;
पूर्ण

अटल व्योम optc1_enable_stereo(काष्ठा timing_generator *optc,
	स्थिर काष्ठा dc_crtc_timing *timing, काष्ठा crtc_stereo_flags *flags)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	अगर (flags) अणु
		uपूर्णांक32_t stereo_en;
		stereo_en = flags->FRAME_PACKED == 0 ? 1 : 0;

		अगर (flags->PROGRAM_STEREO)
			REG_UPDATE_3(OTG_STEREO_CONTROL,
				OTG_STEREO_EN, stereo_en,
				OTG_STEREO_SYNC_OUTPUT_LINE_NUM, 0,
				OTG_STEREO_SYNC_OUTPUT_POLARITY, flags->RIGHT_EYE_POLARITY == 0 ? 0 : 1);

		अगर (flags->PROGRAM_POLARITY)
			REG_UPDATE(OTG_STEREO_CONTROL,
				OTG_STEREO_EYE_FLAG_POLARITY,
				flags->RIGHT_EYE_POLARITY == 0 ? 0 : 1);

		अगर (flags->DISABLE_STEREO_DP_SYNC)
			REG_UPDATE(OTG_STEREO_CONTROL,
				OTG_DISABLE_STEREOSYNC_OUTPUT_FOR_DP, 1);

		अगर (flags->PROGRAM_STEREO)
			REG_UPDATE_2(OTG_3D_STRUCTURE_CONTROL,
				OTG_3D_STRUCTURE_EN, flags->FRAME_PACKED,
				OTG_3D_STRUCTURE_STEREO_SEL_OVR, flags->FRAME_PACKED);

	पूर्ण
पूर्ण

व्योम optc1_program_stereo(काष्ठा timing_generator *optc,
	स्थिर काष्ठा dc_crtc_timing *timing, काष्ठा crtc_stereo_flags *flags)
अणु
	अगर (flags->PROGRAM_STEREO)
		optc1_enable_stereo(optc, timing, flags);
	अन्यथा
		optc1_disable_stereo(optc);
पूर्ण


bool optc1_is_stereo_left_eye(काष्ठा timing_generator *optc)
अणु
	bool ret = false;
	uपूर्णांक32_t left_eye = 0;
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_GET(OTG_STEREO_STATUS,
		OTG_STEREO_CURRENT_EYE, &left_eye);
	अगर (left_eye == 1)
		ret = true;
	अन्यथा
		ret = false;

	वापस ret;
पूर्ण

bool optc1_get_hw_timing(काष्ठा timing_generator *tg,
		काष्ठा dc_crtc_timing *hw_crtc_timing)
अणु
	काष्ठा dcn_otg_state s = अणु0पूर्ण;

	अगर (tg == शून्य || hw_crtc_timing == शून्य)
		वापस false;

	optc1_पढ़ो_otg_state(DCN10TG_FROM_TG(tg), &s);

	hw_crtc_timing->h_total = s.h_total + 1;
	hw_crtc_timing->h_addressable = s.h_total - ((s.h_total - s.h_blank_start) + s.h_blank_end);
	hw_crtc_timing->h_front_porch = s.h_total + 1 - s.h_blank_start;
	hw_crtc_timing->h_sync_width = s.h_sync_a_end - s.h_sync_a_start;

	hw_crtc_timing->v_total = s.v_total + 1;
	hw_crtc_timing->v_addressable = s.v_total - ((s.v_total - s.v_blank_start) + s.v_blank_end);
	hw_crtc_timing->v_front_porch = s.v_total + 1 - s.v_blank_start;
	hw_crtc_timing->v_sync_width = s.v_sync_a_end - s.v_sync_a_start;

	वापस true;
पूर्ण


व्योम optc1_पढ़ो_otg_state(काष्ठा optc *optc1,
		काष्ठा dcn_otg_state *s)
अणु
	REG_GET(OTG_CONTROL,
			OTG_MASTER_EN, &s->otg_enabled);

	REG_GET_2(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, &s->v_blank_start,
			OTG_V_BLANK_END, &s->v_blank_end);

	REG_GET(OTG_V_SYNC_A_CNTL,
			OTG_V_SYNC_A_POL, &s->v_sync_a_pol);

	REG_GET(OTG_V_TOTAL,
			OTG_V_TOTAL, &s->v_total);

	REG_GET(OTG_V_TOTAL_MAX,
			OTG_V_TOTAL_MAX, &s->v_total_max);

	REG_GET(OTG_V_TOTAL_MIN,
			OTG_V_TOTAL_MIN, &s->v_total_min);

	REG_GET(OTG_V_TOTAL_CONTROL,
			OTG_V_TOTAL_MAX_SEL, &s->v_total_max_sel);

	REG_GET(OTG_V_TOTAL_CONTROL,
			OTG_V_TOTAL_MIN_SEL, &s->v_total_min_sel);

	REG_GET_2(OTG_V_SYNC_A,
			OTG_V_SYNC_A_START, &s->v_sync_a_start,
			OTG_V_SYNC_A_END, &s->v_sync_a_end);

	REG_GET_2(OTG_H_BLANK_START_END,
			OTG_H_BLANK_START, &s->h_blank_start,
			OTG_H_BLANK_END, &s->h_blank_end);

	REG_GET_2(OTG_H_SYNC_A,
			OTG_H_SYNC_A_START, &s->h_sync_a_start,
			OTG_H_SYNC_A_END, &s->h_sync_a_end);

	REG_GET(OTG_H_SYNC_A_CNTL,
			OTG_H_SYNC_A_POL, &s->h_sync_a_pol);

	REG_GET(OTG_H_TOTAL,
			OTG_H_TOTAL, &s->h_total);

	REG_GET(OPTC_INPUT_GLOBAL_CONTROL,
			OPTC_UNDERFLOW_OCCURRED_STATUS, &s->underflow_occurred_status);
पूर्ण

bool optc1_get_otg_active_size(काष्ठा timing_generator *optc,
		uपूर्णांक32_t *otg_active_width,
		uपूर्णांक32_t *otg_active_height)
अणु
	uपूर्णांक32_t otg_enabled;
	uपूर्णांक32_t v_blank_start;
	uपूर्णांक32_t v_blank_end;
	uपूर्णांक32_t h_blank_start;
	uपूर्णांक32_t h_blank_end;
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);


	REG_GET(OTG_CONTROL,
			OTG_MASTER_EN, &otg_enabled);

	अगर (otg_enabled == 0)
		वापस false;

	REG_GET_2(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, &v_blank_start,
			OTG_V_BLANK_END, &v_blank_end);

	REG_GET_2(OTG_H_BLANK_START_END,
			OTG_H_BLANK_START, &h_blank_start,
			OTG_H_BLANK_END, &h_blank_end);

	*otg_active_width = v_blank_start - v_blank_end;
	*otg_active_height = h_blank_start - h_blank_end;
	वापस true;
पूर्ण

व्योम optc1_clear_optc_underflow(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OPTC_INPUT_GLOBAL_CONTROL, OPTC_UNDERFLOW_CLEAR, 1);
पूर्ण

व्योम optc1_tg_init(काष्ठा timing_generator *optc)
अणु
	optc1_set_blank_data_द्विगुन_buffer(optc, true);
	optc1_set_timing_द्विगुन_buffer(optc, true);
	optc1_clear_optc_underflow(optc);
पूर्ण

bool optc1_is_tg_enabled(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t otg_enabled = 0;

	REG_GET(OTG_CONTROL, OTG_MASTER_EN, &otg_enabled);

	वापस (otg_enabled != 0);

पूर्ण

bool optc1_is_optc_underflow_occurred(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t underflow_occurred = 0;

	REG_GET(OPTC_INPUT_GLOBAL_CONTROL,
			OPTC_UNDERFLOW_OCCURRED_STATUS,
			&underflow_occurred);

	वापस (underflow_occurred == 1);
पूर्ण

bool optc1_configure_crc(काष्ठा timing_generator *optc,
			  स्थिर काष्ठा crc_params *params)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	/* Cannot configure crc on a CRTC that is disabled */
	अगर (!optc1_is_tg_enabled(optc))
		वापस false;

	REG_WRITE(OTG_CRC_CNTL, 0);

	अगर (!params->enable)
		वापस true;

	/* Program frame boundaries */
	/* Winकरोw A x axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWA_X_CONTROL,
			OTG_CRC0_WINDOWA_X_START, params->winकरोwa_x_start,
			OTG_CRC0_WINDOWA_X_END, params->winकरोwa_x_end);

	/* Winकरोw A y axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWA_Y_CONTROL,
			OTG_CRC0_WINDOWA_Y_START, params->winकरोwa_y_start,
			OTG_CRC0_WINDOWA_Y_END, params->winकरोwa_y_end);

	/* Winकरोw B x axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWB_X_CONTROL,
			OTG_CRC0_WINDOWB_X_START, params->winकरोwb_x_start,
			OTG_CRC0_WINDOWB_X_END, params->winकरोwb_x_end);

	/* Winकरोw B y axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWB_Y_CONTROL,
			OTG_CRC0_WINDOWB_Y_START, params->winकरोwb_y_start,
			OTG_CRC0_WINDOWB_Y_END, params->winकरोwb_y_end);

	/* Set crc mode and selection, and enable. Only using CRC0*/
	REG_UPDATE_3(OTG_CRC_CNTL,
			OTG_CRC_CONT_EN, params->continuous_mode ? 1 : 0,
			OTG_CRC0_SELECT, params->selection,
			OTG_CRC_EN, 1);

	वापस true;
पूर्ण

bool optc1_get_crc(काष्ठा timing_generator *optc,
		    uपूर्णांक32_t *r_cr, uपूर्णांक32_t *g_y, uपूर्णांक32_t *b_cb)
अणु
	uपूर्णांक32_t field = 0;
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_GET(OTG_CRC_CNTL, OTG_CRC_EN, &field);

	/* Early वापस अगर CRC is not enabled क्रम this CRTC */
	अगर (!field)
		वापस false;

	REG_GET_2(OTG_CRC0_DATA_RG,
			CRC0_R_CR, r_cr,
			CRC0_G_Y, g_y);

	REG_GET(OTG_CRC0_DATA_B,
			CRC0_B_CB, b_cb);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा timing_generator_funcs dcn10_tg_funcs = अणु
		.validate_timing = optc1_validate_timing,
		.program_timing = optc1_program_timing,
		.setup_vertical_पूर्णांकerrupt0 = optc1_setup_vertical_पूर्णांकerrupt0,
		.setup_vertical_पूर्णांकerrupt1 = optc1_setup_vertical_पूर्णांकerrupt1,
		.setup_vertical_पूर्णांकerrupt2 = optc1_setup_vertical_पूर्णांकerrupt2,
		.program_global_sync = optc1_program_global_sync,
		.enable_crtc = optc1_enable_crtc,
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
		.set_blank = optc1_set_blank,
		.is_blanked = optc1_is_blanked,
		.set_blank_color = optc1_program_blank_color,
		.did_triggered_reset_occur = optc1_did_triggered_reset_occur,
		.enable_reset_trigger = optc1_enable_reset_trigger,
		.enable_crtc_reset = optc1_enable_crtc_reset,
		.disable_reset_trigger = optc1_disable_reset_trigger,
		.lock = optc1_lock,
		.is_locked = optc1_is_locked,
		.unlock = optc1_unlock,
		.enable_optc_घड़ी = optc1_enable_optc_घड़ी,
		.set_drr = optc1_set_drr,
		.set_अटल_screen_control = optc1_set_अटल_screen_control,
		.set_test_pattern = optc1_set_test_pattern,
		.program_stereo = optc1_program_stereo,
		.is_stereo_left_eye = optc1_is_stereo_left_eye,
		.set_blank_data_द्विगुन_buffer = optc1_set_blank_data_द्विगुन_buffer,
		.tg_init = optc1_tg_init,
		.is_tg_enabled = optc1_is_tg_enabled,
		.is_optc_underflow_occurred = optc1_is_optc_underflow_occurred,
		.clear_optc_underflow = optc1_clear_optc_underflow,
		.get_crc = optc1_get_crc,
		.configure_crc = optc1_configure_crc,
		.set_vtg_params = optc1_set_vtg_params,
		.program_manual_trigger = optc1_program_manual_trigger,
		.setup_manual_trigger = optc1_setup_manual_trigger,
		.get_hw_timing = optc1_get_hw_timing,
पूर्ण;

व्योम dcn10_timing_generator_init(काष्ठा optc *optc1)
अणु
	optc1->base.funcs = &dcn10_tg_funcs;

	optc1->max_h_total = optc1->tg_mask->OTG_H_TOTAL + 1;
	optc1->max_v_total = optc1->tg_mask->OTG_V_TOTAL + 1;

	optc1->min_h_blank = 32;
	optc1->min_v_blank = 3;
	optc1->min_v_blank_पूर्णांकerlace = 5;
	optc1->min_h_sync_width = 4;
	optc1->min_v_sync_width = 1;
पूर्ण

/* "Containter" vs. "pixel" is a concept within HW blocks, mostly those बंदr to the back-end. It works like this:
 *
 * - In most of the क्रमmats (RGB or YCbCr 4:4:4, 4:2:2 uncompressed and DSC 4:2:2 Simple) pixel rate is the same as
 *   contaपूर्णांकer rate.
 *
 * - In 4:2:0 (DSC or uncompressed) there are two pixels per container, hence the target container rate has to be
 *   halved to मुख्यtain the correct pixel rate.
 *
 * - Unlike 4:2:2 uncompressed, DSC 4:2:2 Native also has two pixels per container (this happens when DSC is applied
 *   to it) and has to be treated the same as 4:2:0, i.e. target contaपूर्णांकer rate has to be halved in this हाल as well.
 *
 */
bool optc1_is_two_pixels_per_contaपूर्णांकer(स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	bool two_pix = timing->pixel_encoding == PIXEL_ENCODING_YCBCR420;

	two_pix = two_pix || (timing->flags.DSC && timing->pixel_encoding == PIXEL_ENCODING_YCBCR422
			&& !timing->dsc_cfg.ycbcr422_simple);
	वापस two_pix;
पूर्ण

