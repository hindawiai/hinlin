<शैली गुरु>
/*
 * Copyright 2020 Mauro Rossi <issor.oruam@gmail.com>
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

/* include DCE6 रेजिस्टर header files */
#समावेश "dce/dce_6_0_d.h"
#समावेश "dce/dce_6_0_sh_mask.h"

#समावेश "dc_types.h"

#समावेश "include/grph_object_id.h"
#समावेश "include/logger_interface.h"
#समावेश "../dce110/dce110_timing_generator.h"
#समावेश "dce60_timing_generator.h"

#समावेश "timing_generator.h"

क्रमागत black_color_क्रमmat अणु
	BLACK_COLOR_FORMAT_RGB_FULLRANGE = 0,	/* used as index in array */
	BLACK_COLOR_FORMAT_RGB_LIMITED,
	BLACK_COLOR_FORMAT_YUV_TV,
	BLACK_COLOR_FORMAT_YUV_CV,
	BLACK_COLOR_FORMAT_YUV_SUPER_AA,

	BLACK_COLOR_FORMAT_COUNT
पूर्ण;

अटल स्थिर काष्ठा dce110_timing_generator_offsets reg_offsets[] = अणु
अणु
	.crtc = (mmCRTC0_DCFE_MEM_LIGHT_SLEEP_CNTL - mmCRTC0_DCFE_MEM_LIGHT_SLEEP_CNTL),
	.dcp = (mmDCP0_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC1_DCFE_MEM_LIGHT_SLEEP_CNTL - mmCRTC0_DCFE_MEM_LIGHT_SLEEP_CNTL),
	.dcp = (mmDCP1_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC2_DCFE_MEM_LIGHT_SLEEP_CNTL - mmCRTC0_DCFE_MEM_LIGHT_SLEEP_CNTL),
	.dcp = (mmDCP2_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC3_DCFE_MEM_LIGHT_SLEEP_CNTL - mmCRTC0_DCFE_MEM_LIGHT_SLEEP_CNTL),
	.dcp = (mmDCP3_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC4_DCFE_MEM_LIGHT_SLEEP_CNTL - mmCRTC0_DCFE_MEM_LIGHT_SLEEP_CNTL),
	.dcp = (mmDCP4_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC5_DCFE_MEM_LIGHT_SLEEP_CNTL - mmCRTC0_DCFE_MEM_LIGHT_SLEEP_CNTL),
	.dcp = (mmDCP5_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
पूर्ण
पूर्ण;

#घोषणा NUMBER_OF_FRAME_TO_WAIT_ON_TRIGGERED_RESET 10

#घोषणा MAX_H_TOTAL (CRTC_H_TOTAL__CRTC_H_TOTAL_MASK + 1)
#घोषणा MAX_V_TOTAL (CRTC_V_TOTAL__CRTC_V_TOTAL_MASKhw + 1)

#घोषणा CRTC_REG(reg) (reg + tg110->offsets.crtc)
#घोषणा DCP_REG(reg) (reg + tg110->offsets.dcp)
#घोषणा DMIF_REG(reg) (reg + tg110->offsets.dmअगर)

अटल व्योम program_pix_dur(काष्ठा timing_generator *tg, uपूर्णांक32_t pix_clk_100hz)
अणु
	uपूर्णांक64_t pix_dur;
	uपूर्णांक32_t addr = mmDMIF_PG0_DPG_PIPE_ARBITRATION_CONTROL1
					+ DCE110TG_FROM_TG(tg)->offsets.dmअगर;
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	अगर (pix_clk_100hz == 0)
		वापस;

	pix_dur = भाग_u64(10000000000ull, pix_clk_100hz);

	set_reg_field_value(
		value,
		pix_dur,
		DPG_PIPE_ARBITRATION_CONTROL1,
		PIXEL_DURATION);

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

अटल व्योम program_timing(काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing,
	पूर्णांक vपढ़ोy_offset,
	पूर्णांक vstartup_start,
	पूर्णांक vupdate_offset,
	पूर्णांक vupdate_width,
	स्थिर क्रमागत संकेत_type संकेत,
	bool use_vbios)
अणु
	अगर (!use_vbios)
		program_pix_dur(tg, timing->pix_clk_100hz);

	dce110_tg_program_timing(tg, timing, 0, 0, 0, 0, 0, use_vbios);
पूर्ण

अटल व्योम dce60_timing_generator_enable_advanced_request(
	काष्ठा timing_generator *tg,
	bool enable,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t addr = CRTC_REG(mmCRTC_START_LINE_CONTROL);
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);
	/* DCE6 has CRTC_PREFETCH_EN bit in CRTC_CONTROL रेजिस्टर */
	uपूर्णांक32_t addr2 = CRTC_REG(mmCRTC_CONTROL);
	uपूर्णांक32_t value2 = dm_पढ़ो_reg(tg->ctx, addr2);

	/* DCE6 करोes not support CRTC_LEGACY_REQUESTOR_EN bit
	   so here is not possible to set bit based on enable argument */

	अगर ((timing->v_sync_width + timing->v_front_porch) <= 3) अणु
		set_reg_field_value(
			value,
			3,
			CRTC_START_LINE_CONTROL,
			CRTC_ADVANCED_START_LINE_POSITION);
		set_reg_field_value(
			value2,
			0,
			CRTC_CONTROL,
			CRTC_PREFETCH_EN);
	पूर्ण अन्यथा अणु
		set_reg_field_value(
			value,
			4,
			CRTC_START_LINE_CONTROL,
			CRTC_ADVANCED_START_LINE_POSITION);
		set_reg_field_value(
			value2,
			1,
			CRTC_CONTROL,
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
	dm_ग_लिखो_reg(tg->ctx, addr2, value2);
पूर्ण

अटल bool dce60_is_tg_enabled(काष्ठा timing_generator *tg)
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

अटल bool dce60_configure_crc(काष्ठा timing_generator *tg,
				स्थिर काष्ठा crc_params *params)
अणु
	/* Cannot configure crc on a CRTC that is disabled */
	अगर (!dce60_is_tg_enabled(tg))
		वापस false;

	/* DCE6 has no CRTC_CRC_CNTL रेजिस्टर, nothing to करो */

	वापस true;
पूर्ण

अटल स्थिर काष्ठा timing_generator_funcs dce60_tg_funcs = अणु
		.validate_timing = dce110_tg_validate_timing,
		.program_timing = program_timing,
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
		.disable_reset_trigger = dce110_timing_generator_disable_reset_trigger,
		.tear_करोwn_global_swap_lock =
				dce110_timing_generator_tear_करोwn_global_swap_lock,
		.set_drr = dce110_timing_generator_set_drr,
		.set_अटल_screen_control =
			dce110_timing_generator_set_अटल_screen_control,
		.set_test_pattern = dce110_timing_generator_set_test_pattern,
		.arm_vert_पूर्णांकr = dce110_arm_vert_पूर्णांकr,

		/* DCE6.0 overrides */
		.enable_advanced_request =
				dce60_timing_generator_enable_advanced_request,
		.configure_crc = dce60_configure_crc,
		.get_crc = dce110_get_crc,
पूर्ण;

व्योम dce60_timing_generator_स्थिरruct(
	काष्ठा dce110_timing_generator *tg110,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t instance,
	स्थिर काष्ठा dce110_timing_generator_offsets *offsets)
अणु
	tg110->controller_id = CONTROLLER_ID_D0 + instance;
	tg110->base.inst = instance;
	tg110->offsets = *offsets;
	tg110->derived_offsets = reg_offsets[instance];

	tg110->base.funcs = &dce60_tg_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_total = CRTC_H_TOTAL__CRTC_H_TOTAL_MASK + 1;
	tg110->max_v_total = CRTC_V_TOTAL__CRTC_V_TOTAL_MASK + 1;

	tg110->min_h_blank = 56;
	tg110->min_h_front_porch = 4;
	tg110->min_h_back_porch = 4;
पूर्ण

