<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#समावेश "dce110_timing_generator_v.h"

#समावेश "timing_generator.h"

#घोषणा DC_LOGGER \
	tg->ctx->logger
/** ********************************************************************************
 *
 * DCE11 Timing Generator Implementation
 *
 **********************************************************************************/

/*
 * Enable CRTCV
 */

अटल bool dce110_timing_generator_v_enable_crtc(काष्ठा timing_generator *tg)
अणु
/*
 * Set MASTER_UPDATE_MODE to 0
 * This is needed क्रम DRR, and also suggested to be शेष value by Syed.
 */
	uपूर्णांक32_t value;

	value = 0;
	set_reg_field_value(value, 0,
			CRTCV_MASTER_UPDATE_MODE, MASTER_UPDATE_MODE);
	dm_ग_लिखो_reg(tg->ctx,
			mmCRTCV_MASTER_UPDATE_MODE, value);

	/* TODO: may want this on क्रम looking क्रम underflow */
	value = 0;
	dm_ग_लिखो_reg(tg->ctx, mmCRTCV_MASTER_UPDATE_MODE, value);

	value = 0;
	set_reg_field_value(value, 1,
			CRTCV_MASTER_EN, CRTC_MASTER_EN);
	dm_ग_लिखो_reg(tg->ctx,
			mmCRTCV_MASTER_EN, value);

	वापस true;
पूर्ण

अटल bool dce110_timing_generator_v_disable_crtc(काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t value;

	value = dm_पढ़ो_reg(tg->ctx,
			mmCRTCV_CONTROL);
	set_reg_field_value(value, 0,
			CRTCV_CONTROL, CRTC_DISABLE_POINT_CNTL);
	set_reg_field_value(value, 0,
				CRTCV_CONTROL, CRTC_MASTER_EN);
	dm_ग_लिखो_reg(tg->ctx,
			mmCRTCV_CONTROL, value);
	/*
	 * TODO: call this when adding stereo support
	 * tg->funcs->disable_stereo(tg);
	 */
	वापस true;
पूर्ण

अटल व्योम dce110_timing_generator_v_blank_crtc(काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t addr = mmCRTCV_BLANK_CONTROL;
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		1,
		CRTCV_BLANK_CONTROL,
		CRTC_BLANK_DATA_EN);

	set_reg_field_value(
		value,
		0,
		CRTCV_BLANK_CONTROL,
		CRTC_BLANK_DE_MODE);

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

अटल व्योम dce110_timing_generator_v_unblank_crtc(काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t addr = mmCRTCV_BLANK_CONTROL;
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		0,
		CRTCV_BLANK_CONTROL,
		CRTC_BLANK_DATA_EN);

	set_reg_field_value(
		value,
		0,
		CRTCV_BLANK_CONTROL,
		CRTC_BLANK_DE_MODE);

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

अटल bool dce110_timing_generator_v_is_in_vertical_blank(
		काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t field = 0;

	addr = mmCRTCV_STATUS;
	value = dm_पढ़ो_reg(tg->ctx, addr);
	field = get_reg_field_value(value, CRTCV_STATUS, CRTC_V_BLANK);
	वापस field == 1;
पूर्ण

अटल bool dce110_timing_generator_v_is_counter_moving(काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t value;
	uपूर्णांक32_t h1 = 0;
	uपूर्णांक32_t h2 = 0;
	uपूर्णांक32_t v1 = 0;
	uपूर्णांक32_t v2 = 0;

	value = dm_पढ़ो_reg(tg->ctx, mmCRTCV_STATUS_POSITION);

	h1 = get_reg_field_value(
			value,
			CRTCV_STATUS_POSITION,
			CRTC_HORZ_COUNT);

	v1 = get_reg_field_value(
			value,
			CRTCV_STATUS_POSITION,
			CRTC_VERT_COUNT);

	value = dm_पढ़ो_reg(tg->ctx, mmCRTCV_STATUS_POSITION);

	h2 = get_reg_field_value(
			value,
			CRTCV_STATUS_POSITION,
			CRTC_HORZ_COUNT);

	v2 = get_reg_field_value(
			value,
			CRTCV_STATUS_POSITION,
			CRTC_VERT_COUNT);

	अगर (h1 == h2 && v1 == v2)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल व्योम dce110_timing_generator_v_रुको_क्रम_vblank(काष्ठा timing_generator *tg)
अणु
	/* We want to catch beginning of VBlank here, so अगर the first try are
	 * in VBlank, we might be very बंद to Active, in this हाल रुको क्रम
	 * another frame
	 */
	जबतक (dce110_timing_generator_v_is_in_vertical_blank(tg)) अणु
		अगर (!dce110_timing_generator_v_is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक (!dce110_timing_generator_v_is_in_vertical_blank(tg)) अणु
		अगर (!dce110_timing_generator_v_is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Wait till we are in VActive (anywhere in VActive)
 */
अटल व्योम dce110_timing_generator_v_रुको_क्रम_vactive(काष्ठा timing_generator *tg)
अणु
	जबतक (dce110_timing_generator_v_is_in_vertical_blank(tg)) अणु
		अगर (!dce110_timing_generator_v_is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dce110_timing_generator_v_रुको_क्रम_state(काष्ठा timing_generator *tg,
	क्रमागत crtc_state state)
अणु
	चयन (state) अणु
	हाल CRTC_STATE_VBLANK:
		dce110_timing_generator_v_रुको_क्रम_vblank(tg);
		अवरोध;

	हाल CRTC_STATE_VACTIVE:
		dce110_timing_generator_v_रुको_क्रम_vactive(tg);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dce110_timing_generator_v_program_blanking(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t vsync_offset = timing->v_border_bottom +
			timing->v_front_porch;
	uपूर्णांक32_t v_sync_start = timing->v_addressable + vsync_offset;

	uपूर्णांक32_t hsync_offset = timing->h_border_right +
			timing->h_front_porch;
	uपूर्णांक32_t h_sync_start = timing->h_addressable + hsync_offset;

	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t पंचांगp = 0;

	addr = mmCRTCV_H_TOTAL;
	value = dm_पढ़ो_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->h_total - 1,
		CRTCV_H_TOTAL,
		CRTC_H_TOTAL);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_V_TOTAL;
	value = dm_पढ़ो_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->v_total - 1,
		CRTCV_V_TOTAL,
		CRTC_V_TOTAL);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_H_BLANK_START_END;
	value = dm_पढ़ो_reg(ctx, addr);

	पंचांगp = timing->h_total -
		(h_sync_start + timing->h_border_left);

	set_reg_field_value(
		value,
		पंचांगp,
		CRTCV_H_BLANK_START_END,
		CRTC_H_BLANK_END);

	पंचांगp = पंचांगp + timing->h_addressable +
		timing->h_border_left + timing->h_border_right;

	set_reg_field_value(
		value,
		पंचांगp,
		CRTCV_H_BLANK_START_END,
		CRTC_H_BLANK_START);

	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_V_BLANK_START_END;
	value = dm_पढ़ो_reg(ctx, addr);

	पंचांगp = timing->v_total - (v_sync_start + timing->v_border_top);

	set_reg_field_value(
		value,
		पंचांगp,
		CRTCV_V_BLANK_START_END,
		CRTC_V_BLANK_END);

	पंचांगp = पंचांगp + timing->v_addressable + timing->v_border_top +
		timing->v_border_bottom;

	set_reg_field_value(
		value,
		पंचांगp,
		CRTCV_V_BLANK_START_END,
		CRTC_V_BLANK_START);

	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_H_SYNC_A;
	value = 0;
	set_reg_field_value(
		value,
		timing->h_sync_width,
		CRTCV_H_SYNC_A,
		CRTC_H_SYNC_A_END);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_H_SYNC_A_CNTL;
	value = dm_पढ़ो_reg(ctx, addr);
	अगर (timing->flags.HSYNC_POSITIVE_POLARITY) अणु
		set_reg_field_value(
			value,
			0,
			CRTCV_H_SYNC_A_CNTL,
			CRTC_H_SYNC_A_POL);
	पूर्ण अन्यथा अणु
		set_reg_field_value(
			value,
			1,
			CRTCV_H_SYNC_A_CNTL,
			CRTC_H_SYNC_A_POL);
	पूर्ण
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_V_SYNC_A;
	value = 0;
	set_reg_field_value(
		value,
		timing->v_sync_width,
		CRTCV_V_SYNC_A,
		CRTC_V_SYNC_A_END);
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_V_SYNC_A_CNTL;
	value = dm_पढ़ो_reg(ctx, addr);
	अगर (timing->flags.VSYNC_POSITIVE_POLARITY) अणु
		set_reg_field_value(
			value,
			0,
			CRTCV_V_SYNC_A_CNTL,
			CRTC_V_SYNC_A_POL);
	पूर्ण अन्यथा अणु
		set_reg_field_value(
			value,
			1,
			CRTCV_V_SYNC_A_CNTL,
			CRTC_V_SYNC_A_POL);
	पूर्ण
	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmCRTCV_INTERLACE_CONTROL;
	value = dm_पढ़ो_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->flags.INTERLACE,
		CRTCV_INTERLACE_CONTROL,
		CRTC_INTERLACE_ENABLE);
	dm_ग_लिखो_reg(ctx, addr, value);
पूर्ण

अटल व्योम dce110_timing_generator_v_enable_advanced_request(
	काष्ठा timing_generator *tg,
	bool enable,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t addr = mmCRTCV_START_LINE_CONTROL;
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	अगर (enable) अणु
		अगर ((timing->v_sync_width + timing->v_front_porch) <= 3) अणु
			set_reg_field_value(
				value,
				3,
				CRTCV_START_LINE_CONTROL,
				CRTC_ADVANCED_START_LINE_POSITION);
		पूर्ण अन्यथा अणु
			set_reg_field_value(
				value,
				4,
				CRTCV_START_LINE_CONTROL,
				CRTC_ADVANCED_START_LINE_POSITION);
		पूर्ण
		set_reg_field_value(
			value,
			0,
			CRTCV_START_LINE_CONTROL,
			CRTC_LEGACY_REQUESTOR_EN);
	पूर्ण अन्यथा अणु
		set_reg_field_value(
			value,
			2,
			CRTCV_START_LINE_CONTROL,
			CRTC_ADVANCED_START_LINE_POSITION);
		set_reg_field_value(
			value,
			1,
			CRTCV_START_LINE_CONTROL,
			CRTC_LEGACY_REQUESTOR_EN);
	पूर्ण

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

अटल व्योम dce110_timing_generator_v_set_blank(काष्ठा timing_generator *tg,
		bool enable_blanking)
अणु
	अगर (enable_blanking)
		dce110_timing_generator_v_blank_crtc(tg);
	अन्यथा
		dce110_timing_generator_v_unblank_crtc(tg);
पूर्ण

अटल व्योम dce110_timing_generator_v_program_timing(काष्ठा timing_generator *tg,
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
		dce110_timing_generator_v_program_blanking(tg, timing);
पूर्ण

अटल व्योम dce110_timing_generator_v_program_blank_color(
		काष्ठा timing_generator *tg,
		स्थिर काष्ठा tg_color *black_color)
अणु
	uपूर्णांक32_t addr = mmCRTCV_BLACK_COLOR;
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		black_color->color_b_cb,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB);
	set_reg_field_value(
		value,
		black_color->color_g_y,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_G_Y);
	set_reg_field_value(
		value,
		black_color->color_r_cr,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_R_CR);

	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

अटल व्योम dce110_timing_generator_v_set_overscan_color_black(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *color)
अणु
	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t value = 0;

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

	addr = mmCRTCV_OVERSCAN_COLOR;
	dm_ग_लिखो_reg(ctx, addr, value);
	addr = mmCRTCV_BLACK_COLOR;
	dm_ग_लिखो_reg(ctx, addr, value);
	/* This is desirable to have a स्थिरant DAC output voltage during the
	 * blank समय that is higher than the 0 volt reference level that the
	 * DAC outमाला_दो when the NBLANK संकेत
	 * is निश्चितed low, such as क्रम output to an analog TV. */
	addr = mmCRTCV_BLANK_DATA_COLOR;
	dm_ग_लिखो_reg(ctx, addr, value);

	/* TO DO we have to program EXT रेजिस्टरs and we need to know LB DATA
	 * क्रमmat because it is used when more 10 , i.e. 12 bits per color
	 *
	 * m_mmDxCRTC_OVERSCAN_COLOR_EXT
	 * m_mmDxCRTC_BLACK_COLOR_EXT
	 * m_mmDxCRTC_BLANK_DATA_COLOR_EXT
	 */
पूर्ण

अटल व्योम dce110_tg_v_program_blank_color(काष्ठा timing_generator *tg,
		स्थिर काष्ठा tg_color *black_color)
अणु
	uपूर्णांक32_t addr = mmCRTCV_BLACK_COLOR;
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		black_color->color_b_cb,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB);
	set_reg_field_value(
		value,
		black_color->color_g_y,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_G_Y);
	set_reg_field_value(
		value,
		black_color->color_r_cr,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_R_CR);

	dm_ग_लिखो_reg(tg->ctx, addr, value);

	addr = mmCRTCV_BLANK_DATA_COLOR;
	dm_ग_लिखो_reg(tg->ctx, addr, value);
पूर्ण

अटल व्योम dce110_timing_generator_v_set_overscan_color(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *overscan_color)
अणु
	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t addr;

	set_reg_field_value(
		value,
		overscan_color->color_b_cb,
		CRTCV_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_BLUE);

	set_reg_field_value(
		value,
		overscan_color->color_g_y,
		CRTCV_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_GREEN);

	set_reg_field_value(
		value,
		overscan_color->color_r_cr,
		CRTCV_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_RED);

	addr = mmCRTCV_OVERSCAN_COLOR;
	dm_ग_लिखो_reg(ctx, addr, value);
पूर्ण

अटल व्योम dce110_timing_generator_v_set_colors(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *blank_color,
	स्थिर काष्ठा tg_color *overscan_color)
अणु
	अगर (blank_color != शून्य)
		dce110_tg_v_program_blank_color(tg, blank_color);
	अगर (overscan_color != शून्य)
		dce110_timing_generator_v_set_overscan_color(tg, overscan_color);
पूर्ण

अटल व्योम dce110_timing_generator_v_set_early_control(
		काष्ठा timing_generator *tg,
		uपूर्णांक32_t early_cntl)
अणु
	uपूर्णांक32_t regval;
	uपूर्णांक32_t address = mmCRTC_CONTROL;

	regval = dm_पढ़ो_reg(tg->ctx, address);
	set_reg_field_value(regval, early_cntl,
			CRTCV_CONTROL, CRTC_HBLANK_EARLY_CONTROL);
	dm_ग_लिखो_reg(tg->ctx, address, regval);
पूर्ण

अटल uपूर्णांक32_t dce110_timing_generator_v_get_vblank_counter(काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t addr = mmCRTCV_STATUS_FRAME_COUNT;
	uपूर्णांक32_t value = dm_पढ़ो_reg(tg->ctx, addr);
	uपूर्णांक32_t field = get_reg_field_value(
			value, CRTCV_STATUS_FRAME_COUNT, CRTC_FRAME_COUNT);

	वापस field;
पूर्ण

अटल bool dce110_timing_generator_v_did_triggered_reset_occur(
	काष्ठा timing_generator *tg)
अणु
	DC_LOG_ERROR("Timing Sync not supported on underlay pipe\n");
	वापस false;
पूर्ण

अटल व्योम dce110_timing_generator_v_setup_global_swap_lock(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dcp_gsl_params *gsl_params)
अणु
	DC_LOG_ERROR("Timing Sync not supported on underlay pipe\n");
	वापस;
पूर्ण

अटल व्योम dce110_timing_generator_v_enable_reset_trigger(
	काष्ठा timing_generator *tg,
	पूर्णांक source_tg_inst)
अणु
	DC_LOG_ERROR("Timing Sync not supported on underlay pipe\n");
	वापस;
पूर्ण

अटल व्योम dce110_timing_generator_v_disable_reset_trigger(
	काष्ठा timing_generator *tg)
अणु
	DC_LOG_ERROR("Timing Sync not supported on underlay pipe\n");
	वापस;
पूर्ण

अटल व्योम dce110_timing_generator_v_tear_करोwn_global_swap_lock(
	काष्ठा timing_generator *tg)
अणु
	DC_LOG_ERROR("Timing Sync not supported on underlay pipe\n");
	वापस;
पूर्ण

अटल व्योम dce110_timing_generator_v_disable_vga(
	काष्ठा timing_generator *tg)
अणु
	वापस;
पूर्ण

/** ********************************************************************************************
 *
 * DCE11 Timing Generator Conकाष्ठाor / Deकाष्ठाor
 *
 *********************************************************************************************/
अटल स्थिर काष्ठा timing_generator_funcs dce110_tg_v_funcs = अणु
		.validate_timing = dce110_tg_validate_timing,
		.program_timing = dce110_timing_generator_v_program_timing,
		.enable_crtc = dce110_timing_generator_v_enable_crtc,
		.disable_crtc = dce110_timing_generator_v_disable_crtc,
		.is_counter_moving = dce110_timing_generator_v_is_counter_moving,
		.get_position = शून्य, /* Not to be implemented क्रम underlay*/
		.get_frame_count = dce110_timing_generator_v_get_vblank_counter,
		.set_early_control = dce110_timing_generator_v_set_early_control,
		.रुको_क्रम_state = dce110_timing_generator_v_रुको_क्रम_state,
		.set_blank = dce110_timing_generator_v_set_blank,
		.set_colors = dce110_timing_generator_v_set_colors,
		.set_overscan_blank_color =
				dce110_timing_generator_v_set_overscan_color_black,
		.set_blank_color = dce110_timing_generator_v_program_blank_color,
		.disable_vga = dce110_timing_generator_v_disable_vga,
		.did_triggered_reset_occur =
				dce110_timing_generator_v_did_triggered_reset_occur,
		.setup_global_swap_lock =
				dce110_timing_generator_v_setup_global_swap_lock,
		.enable_reset_trigger = dce110_timing_generator_v_enable_reset_trigger,
		.disable_reset_trigger = dce110_timing_generator_v_disable_reset_trigger,
		.tear_करोwn_global_swap_lock =
				dce110_timing_generator_v_tear_करोwn_global_swap_lock,
		.enable_advanced_request =
				dce110_timing_generator_v_enable_advanced_request
पूर्ण;

व्योम dce110_timing_generator_v_स्थिरruct(
	काष्ठा dce110_timing_generator *tg110,
	काष्ठा dc_context *ctx)
अणु
	tg110->controller_id = CONTROLLER_ID_UNDERLAY0;

	tg110->base.funcs = &dce110_tg_v_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_total = CRTC_H_TOTAL__CRTC_H_TOTAL_MASK + 1;
	tg110->max_v_total = CRTC_V_TOTAL__CRTC_V_TOTAL_MASK + 1;

	tg110->min_h_blank = 56;
	tg110->min_h_front_porch = 4;
	tg110->min_h_back_porch = 4;
पूर्ण
