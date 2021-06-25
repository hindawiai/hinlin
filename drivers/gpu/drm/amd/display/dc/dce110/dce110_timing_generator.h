<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
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

#अगर_अघोषित __DC_TIMING_GENERATOR_DCE110_H__
#घोषणा __DC_TIMING_GENERATOR_DCE110_H__

#समावेश "timing_generator.h"
#समावेश "../include/grph_object_id.h"

/* GSL Sync related values */

/* In VSync mode, after 4 units of समय, master pipe will generate
 * flip_पढ़ोy संकेत */
#घोषणा VFLIP_READY_DELAY 4
/* In HSync mode, after 2 units of समय, master pipe will generate
 * flip_पढ़ोy संकेत */
#घोषणा HFLIP_READY_DELAY 2
/* 6 lines delay between क्रमcing flip and checking all pipes पढ़ोy */
#घोषणा HFLIP_CHECK_DELAY 6
/* 3 lines beक्रमe end of frame */
#घोषणा FLIP_READY_BACK_LOOKUP 3

/* Trigger Source Select - ASIC-defendant, actual values क्रम the
 * रेजिस्टर programming */
क्रमागत trigger_source_select अणु
	TRIGGER_SOURCE_SELECT_LOGIC_ZERO = 0,
	TRIGGER_SOURCE_SELECT_CRTC_VSYNCA = 1,
	TRIGGER_SOURCE_SELECT_CRTC_HSYNCA = 2,
	TRIGGER_SOURCE_SELECT_CRTC_VSYNCB = 3,
	TRIGGER_SOURCE_SELECT_CRTC_HSYNCB = 4,
	TRIGGER_SOURCE_SELECT_GENERICF = 5,
	TRIGGER_SOURCE_SELECT_GENERICE = 6,
	TRIGGER_SOURCE_SELECT_VSYNCA = 7,
	TRIGGER_SOURCE_SELECT_HSYNCA = 8,
	TRIGGER_SOURCE_SELECT_VSYNCB = 9,
	TRIGGER_SOURCE_SELECT_HSYNCB = 10,
	TRIGGER_SOURCE_SELECT_HPD1 = 11,
	TRIGGER_SOURCE_SELECT_HPD2 = 12,
	TRIGGER_SOURCE_SELECT_GENERICD = 13,
	TRIGGER_SOURCE_SELECT_GENERICC = 14,
	TRIGGER_SOURCE_SELECT_VIDEO_CAPTURE = 15,
	TRIGGER_SOURCE_SELECT_GSL_GROUP0 = 16,
	TRIGGER_SOURCE_SELECT_GSL_GROUP1 = 17,
	TRIGGER_SOURCE_SELECT_GSL_GROUP2 = 18,
	TRIGGER_SOURCE_SELECT_BLONY = 19,
	TRIGGER_SOURCE_SELECT_GENERICA = 20,
	TRIGGER_SOURCE_SELECT_GENERICB = 21,
	TRIGGER_SOURCE_SELECT_GSL_ALLOW_FLIP = 22,
	TRIGGER_SOURCE_SELECT_MANUAL_TRIGGER = 23
पूर्ण;

/* Trigger Source Select - ASIC-dependant, actual values क्रम the
 * रेजिस्टर programming */
क्रमागत trigger_polarity_select अणु
	TRIGGER_POLARITY_SELECT_LOGIC_ZERO = 0,
	TRIGGER_POLARITY_SELECT_CRTC = 1,
	TRIGGER_POLARITY_SELECT_GENERICA = 2,
	TRIGGER_POLARITY_SELECT_GENERICB = 3,
	TRIGGER_POLARITY_SELECT_HSYNCA = 4,
	TRIGGER_POLARITY_SELECT_HSYNCB = 5,
	TRIGGER_POLARITY_SELECT_VIDEO_CAPTURE = 6,
	TRIGGER_POLARITY_SELECT_GENERICC = 7
पूर्ण;


काष्ठा dce110_timing_generator_offsets अणु
	पूर्णांक32_t crtc;
	पूर्णांक32_t dcp;

	/* DCE80 use only */
	पूर्णांक32_t dmअगर;
पूर्ण;

काष्ठा dce110_timing_generator अणु
	काष्ठा timing_generator base;
	काष्ठा dce110_timing_generator_offsets offsets;
	काष्ठा dce110_timing_generator_offsets derived_offsets;

	क्रमागत controller_id controller_id;

	uपूर्णांक32_t max_h_total;
	uपूर्णांक32_t max_v_total;

	uपूर्णांक32_t min_h_blank;
	uपूर्णांक32_t min_h_front_porch;
	uपूर्णांक32_t min_h_back_porch;

	/* DCE 12 */
	uपूर्णांक32_t min_h_sync_width;
	uपूर्णांक32_t min_v_sync_width;
	uपूर्णांक32_t min_v_blank;

पूर्ण;

#घोषणा DCE110TG_FROM_TG(tg)\
	container_of(tg, काष्ठा dce110_timing_generator, base)

व्योम dce110_timing_generator_स्थिरruct(
	काष्ठा dce110_timing_generator *tg,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t instance,
	स्थिर काष्ठा dce110_timing_generator_offsets *offsets);

/* determine अगर given timing can be supported by TG */
bool dce110_timing_generator_validate_timing(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing,
	क्रमागत संकेत_type संकेत);

/******** HW programming ************/

/* Program timing generator with given timing */
bool dce110_timing_generator_program_timing_generator(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing);

/* Disable/Enable Timing Generator */
bool dce110_timing_generator_enable_crtc(काष्ठा timing_generator *tg);
bool dce110_timing_generator_disable_crtc(काष्ठा timing_generator *tg);

व्योम dce110_timing_generator_set_early_control(
		काष्ठा timing_generator *tg,
		uपूर्णांक32_t early_cntl);

/**************** TG current status ******************/

/* वापस the current frame counter. Used by Linux kernel DRM */
uपूर्णांक32_t dce110_timing_generator_get_vblank_counter(
		काष्ठा timing_generator *tg);

व्योम dce110_timing_generator_get_position(
	काष्ठा timing_generator *tg,
	काष्ठा crtc_position *position);

/* वापस true अगर TG counter is moving. false अगर TG is stopped */
bool dce110_timing_generator_is_counter_moving(काष्ठा timing_generator *tg);

/* रुको until TG is in beginning of vertical blank region */
व्योम dce110_timing_generator_रुको_क्रम_vblank(काष्ठा timing_generator *tg);

/* रुको until TG is in beginning of active region */
व्योम dce110_timing_generator_रुको_क्रम_vactive(काष्ठा timing_generator *tg);

/*********** Timing Generator Synchronization routines ****/

/* Setups Global Swap Lock group, TimingServer or TimingClient*/
व्योम dce110_timing_generator_setup_global_swap_lock(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dcp_gsl_params *gsl_params);

/* Clear all the रेजिस्टर ग_लिखोs करोne by setup_global_swap_lock */
व्योम dce110_timing_generator_tear_करोwn_global_swap_lock(
	काष्ठा timing_generator *tg);

/* Reset crtc position on master VSync */
व्योम dce110_timing_generator_enable_crtc_reset(
	काष्ठा timing_generator *tg,
	पूर्णांक source,
	काष्ठा crtc_trigger_info *crtc_tp);

/* Reset slave controllers on master VSync */
व्योम dce110_timing_generator_enable_reset_trigger(
	काष्ठा timing_generator *tg,
	पूर्णांक source);

/* disabling trigger-reset */
व्योम dce110_timing_generator_disable_reset_trigger(
	काष्ठा timing_generator *tg);

/* Checks whether CRTC triggered reset occurred */
bool dce110_timing_generator_did_triggered_reset_occur(
	काष्ठा timing_generator *tg);

/******** Stuff to move to other भव HW objects *****************/
/* Move to enable accelerated mode */
व्योम dce110_timing_generator_disable_vga(काष्ठा timing_generator *tg);
/* TODO: Should we move it to transक्रमm */
/* Fully program CRTC timing in timing generator */
व्योम dce110_timing_generator_program_blanking(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing);

/* TODO: Should we move it to opp? */
/* Combine with below and move YUV/RGB color conversion to SW layer */
व्योम dce110_timing_generator_program_blank_color(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *black_color);
/* Combine with above and move YUV/RGB color conversion to SW layer */
व्योम dce110_timing_generator_set_overscan_color_black(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *color);
व्योम dce110_timing_generator_color_space_to_black_color(
		क्रमागत dc_color_space colorspace,
	काष्ठा tg_color *black_color);
/*************** End-of-move ********************/

/* Not called yet */
व्योम dce110_timing_generator_set_test_pattern(
	काष्ठा timing_generator *tg,
	/* TODO: replace 'controller_dp_test_pattern' by 'test_pattern_mode'
	 * because this is not DP-specअगरic (which is probably somewhere in DP
	 * encoder) */
	क्रमागत controller_dp_test_pattern test_pattern,
	क्रमागत dc_color_depth color_depth);

व्योम dce110_timing_generator_set_drr(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा drr_params *params);

व्योम dce110_timing_generator_set_अटल_screen_control(
	काष्ठा timing_generator *tg,
	uपूर्णांक32_t event_triggers,
	uपूर्णांक32_t num_frames);

व्योम dce110_timing_generator_get_crtc_scanoutpos(
	काष्ठा timing_generator *tg,
	uपूर्णांक32_t *v_blank_start,
	uपूर्णांक32_t *v_blank_end,
	uपूर्णांक32_t *h_position,
	uपूर्णांक32_t *v_position);

व्योम dce110_timing_generator_enable_advanced_request(
	काष्ठा timing_generator *tg,
	bool enable,
	स्थिर काष्ठा dc_crtc_timing *timing);

व्योम dce110_timing_generator_set_lock_master(काष्ठा timing_generator *tg,
		bool lock);

व्योम dce110_tg_program_blank_color(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *black_color);

व्योम dce110_tg_set_overscan_color(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *overscan_color);

व्योम dce110_tg_program_timing(काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing,
	पूर्णांक vपढ़ोy_offset,
	पूर्णांक vstartup_start,
	पूर्णांक vupdate_offset,
	पूर्णांक vupdate_width,
	स्थिर क्रमागत संकेत_type संकेत,
	bool use_vbios);

bool dce110_tg_is_blanked(काष्ठा timing_generator *tg);

व्योम dce110_tg_set_blank(काष्ठा timing_generator *tg,
		bool enable_blanking);

bool dce110_tg_validate_timing(काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing);

व्योम dce110_tg_रुको_क्रम_state(काष्ठा timing_generator *tg,
	क्रमागत crtc_state state);

व्योम dce110_tg_set_colors(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *blank_color,
	स्थिर काष्ठा tg_color *overscan_color);

bool dce110_arm_vert_पूर्णांकr(
		काष्ठा timing_generator *tg, uपूर्णांक8_t width);

bool dce110_configure_crc(काष्ठा timing_generator *tg,
			  स्थिर काष्ठा crc_params *params);

bool dce110_get_crc(काष्ठा timing_generator *tg,
		    uपूर्णांक32_t *r_cr, uपूर्णांक32_t *g_y, uपूर्णांक32_t *b_cb);

#पूर्ण_अगर /* __DC_TIMING_GENERATOR_DCE110_H__ */
