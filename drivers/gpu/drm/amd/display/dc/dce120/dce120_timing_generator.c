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

#समावेश "dce/dce_12_0_offset.h"
#समावेश "dce/dce_12_0_sh_mask.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"

#समावेश "dc_types.h"
#समावेश "dc_bios_types.h"

#समावेश "include/grph_object_id.h"
#समावेश "include/logger_interface.h"
#समावेश "dce120_timing_generator.h"

#समावेश "timing_generator.h"

#घोषणा CRTC_REG_UPDATE_N(reg_name, n, ...)	\
		generic_reg_update_soc15(tg110->base.ctx, tg110->offsets.crtc, reg_name, n, __VA_ARGS__)

#घोषणा CRTC_REG_SET_N(reg_name, n, ...)	\
		generic_reg_set_soc15(tg110->base.ctx, tg110->offsets.crtc, reg_name, n, __VA_ARGS__)

#घोषणा CRTC_REG_UPDATE(reg, field, val)	\
		CRTC_REG_UPDATE_N(reg, 1, FD(reg##__##field), val)

#घोषणा CRTC_REG_UPDATE_2(reg, field1, val1, field2, val2)	\
		CRTC_REG_UPDATE_N(reg, 2, FD(reg##__##field1), val1, FD(reg##__##field2), val2)

#घोषणा CRTC_REG_UPDATE_3(reg, field1, val1, field2, val2, field3, val3)	\
		CRTC_REG_UPDATE_N(reg, 3, FD(reg##__##field1), val1, FD(reg##__##field2), val2, FD(reg##__##field3), val3)

#घोषणा CRTC_REG_UPDATE_4(reg, field1, val1, field2, val2, field3, val3, field4, val4)	\
		CRTC_REG_UPDATE_N(reg, 3, FD(reg##__##field1), val1, FD(reg##__##field2), val2, FD(reg##__##field3), val3, FD(reg##__##field4), val4)

#घोषणा CRTC_REG_UPDATE_5(reg, field1, val1, field2, val2, field3, val3, field4, val4, field5, val5)	\
		CRTC_REG_UPDATE_N(reg, 3, FD(reg##__##field1), val1, FD(reg##__##field2), val2, FD(reg##__##field3), val3, FD(reg##__##field4), val4, FD(reg##__##field5), val5)

#घोषणा CRTC_REG_SET(reg, field, val)	\
		CRTC_REG_SET_N(reg, 1, FD(reg##__##field), val)

#घोषणा CRTC_REG_SET_2(reg, field1, val1, field2, val2)	\
		CRTC_REG_SET_N(reg, 2, FD(reg##__##field1), val1, FD(reg##__##field2), val2)

#घोषणा CRTC_REG_SET_3(reg, field1, val1, field2, val2, field3, val3)	\
		CRTC_REG_SET_N(reg, 3, FD(reg##__##field1), val1, FD(reg##__##field2), val2, FD(reg##__##field3), val3)

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
अटल bool dce120_timing_generator_is_in_vertical_blank(
		काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t field = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(
					tg->ctx,
					mmCRTC0_CRTC_STATUS,
					tg110->offsets.crtc);

	field = get_reg_field_value(value, CRTC0_CRTC_STATUS, CRTC_V_BLANK);
	वापस field == 1;
पूर्ण


/* determine अगर given timing can be supported by TG */
अटल bool dce120_timing_generator_validate_timing(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing,
	क्रमागत संकेत_type संकेत)
अणु
	uपूर्णांक32_t पूर्णांकerlace_factor = timing->flags.INTERLACE ? 2 : 1;
	uपूर्णांक32_t v_blank =
					(timing->v_total - timing->v_addressable -
					timing->v_border_top - timing->v_border_bottom) *
					पूर्णांकerlace_factor;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	अगर (!dce110_timing_generator_validate_timing(
					tg,
					timing,
					संकेत))
		वापस false;


	अगर (v_blank < tg110->min_v_blank	||
		 timing->h_sync_width  < tg110->min_h_sync_width ||
		 timing->v_sync_width  < tg110->min_v_sync_width)
		वापस false;

	वापस true;
पूर्ण

अटल bool dce120_tg_validate_timing(काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	वापस dce120_timing_generator_validate_timing(tg, timing, SIGNAL_TYPE_NONE);
पूर्ण

/******** HW programming ************/
/* Disable/Enable Timing Generator */
अटल bool dce120_timing_generator_enable_crtc(काष्ठा timing_generator *tg)
अणु
	क्रमागत bp_result result;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Set MASTER_UPDATE_MODE to 0
	 * This is needed क्रम DRR, and also suggested to be शेष value by Syed.*/

	CRTC_REG_UPDATE(CRTC0_CRTC_MASTER_UPDATE_MODE,
			MASTER_UPDATE_MODE, 0);

	CRTC_REG_UPDATE(CRTC0_CRTC_MASTER_UPDATE_LOCK,
			UNDERFLOW_UPDATE_LOCK, 0);

	/* TODO API क्रम AtomFirmware didn't change*/
	result = tg->bp->funcs->enable_crtc(tg->bp, tg110->controller_id, true);

	वापस result == BP_RESULT_OK;
पूर्ण

अटल व्योम dce120_timing_generator_set_early_control(
		काष्ठा timing_generator *tg,
		uपूर्णांक32_t early_cntl)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_UPDATE(CRTC0_CRTC_CONTROL,
			CRTC_HBLANK_EARLY_CONTROL, early_cntl);
पूर्ण

/**************** TG current status ******************/

/* वापस the current frame counter. Used by Linux kernel DRM */
अटल uपूर्णांक32_t dce120_timing_generator_get_vblank_counter(
		काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(
				tg->ctx,
				mmCRTC0_CRTC_STATUS_FRAME_COUNT,
				tg110->offsets.crtc);
	uपूर्णांक32_t field = get_reg_field_value(
				value, CRTC0_CRTC_STATUS_FRAME_COUNT, CRTC_FRAME_COUNT);

	वापस field;
पूर्ण

/* Get current H and V position */
अटल व्योम dce120_timing_generator_get_crtc_position(
	काष्ठा timing_generator *tg,
	काष्ठा crtc_position *position)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(
				tg->ctx,
				mmCRTC0_CRTC_STATUS_POSITION,
				tg110->offsets.crtc);

	position->horizontal_count = get_reg_field_value(value,
			CRTC0_CRTC_STATUS_POSITION, CRTC_HORZ_COUNT);

	position->vertical_count = get_reg_field_value(value,
			CRTC0_CRTC_STATUS_POSITION, CRTC_VERT_COUNT);

	value = dm_पढ़ो_reg_soc15(
				tg->ctx,
				mmCRTC0_CRTC_NOM_VERT_POSITION,
				tg110->offsets.crtc);

	position->nominal_vcount = get_reg_field_value(value,
			CRTC0_CRTC_NOM_VERT_POSITION, CRTC_VERT_COUNT_NOM);
पूर्ण

/* रुको until TG is in beginning of vertical blank region */
अटल व्योम dce120_timing_generator_रुको_क्रम_vblank(काष्ठा timing_generator *tg)
अणु
	/* We want to catch beginning of VBlank here, so अगर the first try are
	 * in VBlank, we might be very बंद to Active, in this हाल रुको क्रम
	 * another frame
	 */
	जबतक (dce120_timing_generator_is_in_vertical_blank(tg)) अणु
		अगर (!tg->funcs->is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक (!dce120_timing_generator_is_in_vertical_blank(tg)) अणु
		अगर (!tg->funcs->is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* रुको until TG is in beginning of active region */
अटल व्योम dce120_timing_generator_रुको_क्रम_vactive(काष्ठा timing_generator *tg)
अणु
	जबतक (dce120_timing_generator_is_in_vertical_blank(tg)) अणु
		अगर (!tg->funcs->is_counter_moving(tg)) अणु
			/* error - no poपूर्णांक to रुको अगर counter is not moving */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*********** Timing Generator Synchronization routines ****/

/* Setups Global Swap Lock group, TimingServer or TimingClient*/
अटल व्योम dce120_timing_generator_setup_global_swap_lock(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dcp_gsl_params *gsl_params)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value_crtc_vtotal =
							dm_पढ़ो_reg_soc15(tg->ctx,
							mmCRTC0_CRTC_V_TOTAL,
							tg110->offsets.crtc);
	/* Checkpoपूर्णांक relative to end of frame */
	uपूर्णांक32_t check_poपूर्णांक =
							get_reg_field_value(value_crtc_vtotal,
							CRTC0_CRTC_V_TOTAL,
							CRTC_V_TOTAL);


	dm_ग_लिखो_reg_soc15(tg->ctx, mmCRTC0_CRTC_GSL_WINDOW, tg110->offsets.crtc, 0);

	CRTC_REG_UPDATE_N(DCP0_DCP_GSL_CONTROL, 6,
		/* This pipe will beदीर्घ to GSL Group zero. */
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL0_EN), 1,
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_MASTER_EN), gsl_params->gsl_master == tg->inst,
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_FORCE_DELAY), HFLIP_READY_DELAY,
		/* Keep संकेत low (pending high) during 6 lines.
		 * Also defines minimum पूर्णांकerval beक्रमe re-checking संकेत. */
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_CHECK_DELAY), HFLIP_CHECK_DELAY,
		/* DCP_GSL_PURPOSE_SURFACE_FLIP */
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_SYNC_SOURCE), 0,
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_DELAY_SURFACE_UPDATE_PENDING), 1);

	CRTC_REG_SET_2(
			CRTC0_CRTC_GSL_CONTROL,
			CRTC_GSL_CHECK_LINE_NUM, check_poपूर्णांक - FLIP_READY_BACK_LOOKUP,
			CRTC_GSL_FORCE_DELAY, VFLIP_READY_DELAY);
पूर्ण

/* Clear all the रेजिस्टर ग_लिखोs करोne by setup_global_swap_lock */
अटल व्योम dce120_timing_generator_tear_करोwn_global_swap_lock(
	काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Settig HW शेष values from reg specs */
	CRTC_REG_SET_N(DCP0_DCP_GSL_CONTROL, 6,
			FD(DCP0_DCP_GSL_CONTROL__DCP_GSL0_EN), 0,
			FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_MASTER_EN), 0,
			FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_FORCE_DELAY), HFLIP_READY_DELAY,
			FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_CHECK_DELAY), HFLIP_CHECK_DELAY,
			/* DCP_GSL_PURPOSE_SURFACE_FLIP */
			FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_SYNC_SOURCE), 0,
			FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_DELAY_SURFACE_UPDATE_PENDING), 0);

	CRTC_REG_SET_2(CRTC0_CRTC_GSL_CONTROL,
		       CRTC_GSL_CHECK_LINE_NUM, 0,
		       CRTC_GSL_FORCE_DELAY, 0x2); /*TODO Why this value here ?*/
पूर्ण

/* Reset slave controllers on master VSync */
अटल व्योम dce120_timing_generator_enable_reset_trigger(
	काष्ठा timing_generator *tg,
	पूर्णांक source)
अणु
	क्रमागत trigger_source_select trig_src_select = TRIGGER_SOURCE_SELECT_LOGIC_ZERO;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t rising_edge = 0;
	uपूर्णांक32_t falling_edge = 0;
	/* Setup trigger edge */
	uपूर्णांक32_t pol_value = dm_पढ़ो_reg_soc15(
									tg->ctx,
									mmCRTC0_CRTC_V_SYNC_A_CNTL,
									tg110->offsets.crtc);

	/* Register spec has reversed definition:
	 *	0 क्रम positive, 1 क्रम negative */
	अगर (get_reg_field_value(pol_value,
			CRTC0_CRTC_V_SYNC_A_CNTL,
			CRTC_V_SYNC_A_POL) == 0) अणु
		rising_edge = 1;
	पूर्ण अन्यथा अणु
		falling_edge = 1;
	पूर्ण

	/* TODO What about other sources ?*/
	trig_src_select = TRIGGER_SOURCE_SELECT_GSL_GROUP0;

	CRTC_REG_UPDATE_N(CRTC0_CRTC_TRIGB_CNTL, 7,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_SOURCE_SELECT), trig_src_select,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_POLARITY_SELECT), TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_RISING_EDGE_DETECT_CNTL), rising_edge,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_FALLING_EDGE_DETECT_CNTL), falling_edge,
		/* send every संकेत */
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_FREQUENCY_SELECT), 0,
		/* no delay */
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_DELAY), 0,
		/* clear trigger status */
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_CLEAR), 1);

	CRTC_REG_UPDATE_3(
			CRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
			CRTC_FORCE_COUNT_NOW_MODE, 2,
			CRTC_FORCE_COUNT_NOW_TRIG_SEL, 1,
			CRTC_FORCE_COUNT_NOW_CLEAR, 1);
पूर्ण

/* disabling trigger-reset */
अटल व्योम dce120_timing_generator_disable_reset_trigger(
	काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_UPDATE_2(
		CRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
		CRTC_FORCE_COUNT_NOW_MODE, 0,
		CRTC_FORCE_COUNT_NOW_CLEAR, 1);

	CRTC_REG_UPDATE_3(
		CRTC0_CRTC_TRIGB_CNTL,
		CRTC_TRIGB_SOURCE_SELECT, TRIGGER_SOURCE_SELECT_LOGIC_ZERO,
		CRTC_TRIGB_POLARITY_SELECT, TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
		/* clear trigger status */
		CRTC_TRIGB_CLEAR, 1);

पूर्ण

/* Checks whether CRTC triggered reset occurred */
अटल bool dce120_timing_generator_did_triggered_reset_occur(
	काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(
			tg->ctx,
			mmCRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
			tg110->offsets.crtc);

	वापस get_reg_field_value(value,
			CRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
			CRTC_FORCE_COUNT_NOW_OCCURRED) != 0;
पूर्ण


/******** Stuff to move to other भव HW objects *****************/
/* Move to enable accelerated mode */
अटल व्योम dce120_timing_generator_disable_vga(काष्ठा timing_generator *tg)
अणु
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t value = 0;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	चयन (tg110->controller_id) अणु
	हाल CONTROLLER_ID_D0:
		offset = 0;
		अवरोध;
	हाल CONTROLLER_ID_D1:
		offset = mmD2VGA_CONTROL - mmD1VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D2:
		offset = mmD3VGA_CONTROL - mmD1VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D3:
		offset = mmD4VGA_CONTROL - mmD1VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D4:
		offset = mmD5VGA_CONTROL - mmD1VGA_CONTROL;
		अवरोध;
	हाल CONTROLLER_ID_D5:
		offset = mmD6VGA_CONTROL - mmD1VGA_CONTROL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	value = dm_पढ़ो_reg_soc15(tg->ctx, mmD1VGA_CONTROL, offset);

	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_MODE_ENABLE);
	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_TIMING_SELECT);
	set_reg_field_value(
			value, 0, D1VGA_CONTROL, D1VGA_SYNC_POLARITY_SELECT);
	set_reg_field_value(value, 0, D1VGA_CONTROL, D1VGA_OVERSCAN_COLOR_EN);

	dm_ग_लिखो_reg_soc15(tg->ctx, mmD1VGA_CONTROL, offset, value);
पूर्ण
/* TODO: Should we move it to transक्रमm */
/* Fully program CRTC timing in timing generator */
अटल व्योम dce120_timing_generator_program_blanking(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t पंचांगp1 = 0;
	uपूर्णांक32_t पंचांगp2 = 0;
	uपूर्णांक32_t vsync_offset = timing->v_border_bottom +
			timing->v_front_porch;
	uपूर्णांक32_t v_sync_start = timing->v_addressable + vsync_offset;

	uपूर्णांक32_t hsync_offset = timing->h_border_right +
			timing->h_front_porch;
	uपूर्णांक32_t h_sync_start = timing->h_addressable + hsync_offset;
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_UPDATE(
		CRTC0_CRTC_H_TOTAL,
		CRTC_H_TOTAL,
		timing->h_total - 1);

	CRTC_REG_UPDATE(
		CRTC0_CRTC_V_TOTAL,
		CRTC_V_TOTAL,
		timing->v_total - 1);

	/* In हाल of V_TOTAL_CONTROL is on, make sure V_TOTAL_MAX and
	 * V_TOTAL_MIN are equal to V_TOTAL.
	 */
	CRTC_REG_UPDATE(
		CRTC0_CRTC_V_TOTAL_MAX,
		CRTC_V_TOTAL_MAX,
		timing->v_total - 1);

	CRTC_REG_UPDATE(
		CRTC0_CRTC_V_TOTAL_MIN,
		CRTC_V_TOTAL_MIN,
		timing->v_total - 1);

	पंचांगp1 = timing->h_total -
			(h_sync_start + timing->h_border_left);
	पंचांगp2 = पंचांगp1 + timing->h_addressable +
			timing->h_border_left + timing->h_border_right;

	CRTC_REG_UPDATE_2(
			CRTC0_CRTC_H_BLANK_START_END,
			CRTC_H_BLANK_END, पंचांगp1,
			CRTC_H_BLANK_START, पंचांगp2);

	पंचांगp1 = timing->v_total - (v_sync_start + timing->v_border_top);
	पंचांगp2 = पंचांगp1 + timing->v_addressable + timing->v_border_top +
			timing->v_border_bottom;

	CRTC_REG_UPDATE_2(
		CRTC0_CRTC_V_BLANK_START_END,
		CRTC_V_BLANK_END, पंचांगp1,
		CRTC_V_BLANK_START, पंचांगp2);
पूर्ण

/* TODO: Should we move it to opp? */
/* Combine with below and move YUV/RGB color conversion to SW layer */
अटल व्योम dce120_timing_generator_program_blank_color(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *black_color)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_UPDATE_3(
		CRTC0_CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB, black_color->color_b_cb,
		CRTC_BLACK_COLOR_G_Y, black_color->color_g_y,
		CRTC_BLACK_COLOR_R_CR, black_color->color_r_cr);
पूर्ण
/* Combine with above and move YUV/RGB color conversion to SW layer */
अटल व्योम dce120_timing_generator_set_overscan_color_black(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *color)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = 0;
	CRTC_REG_SET_3(
		CRTC0_CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_BLUE, color->color_b_cb,
		CRTC_OVERSCAN_COLOR_GREEN, color->color_g_y,
		CRTC_OVERSCAN_COLOR_RED, color->color_r_cr);

	value = dm_पढ़ो_reg_soc15(
			tg->ctx,
			mmCRTC0_CRTC_OVERSCAN_COLOR,
			tg110->offsets.crtc);

	dm_ग_लिखो_reg_soc15(
			tg->ctx,
			mmCRTC0_CRTC_BLACK_COLOR,
			tg110->offsets.crtc,
			value);

	/* This is desirable to have a स्थिरant DAC output voltage during the
	 * blank समय that is higher than the 0 volt reference level that the
	 * DAC outमाला_दो when the NBLANK संकेत
	 * is निश्चितed low, such as क्रम output to an analog TV. */
	dm_ग_लिखो_reg_soc15(
		tg->ctx,
		mmCRTC0_CRTC_BLANK_DATA_COLOR,
		tg110->offsets.crtc,
		value);

	/* TO DO we have to program EXT रेजिस्टरs and we need to know LB DATA
	 * क्रमmat because it is used when more 10 , i.e. 12 bits per color
	 *
	 * m_mmDxCRTC_OVERSCAN_COLOR_EXT
	 * m_mmDxCRTC_BLACK_COLOR_EXT
	 * m_mmDxCRTC_BLANK_DATA_COLOR_EXT
	 */
पूर्ण

अटल व्योम dce120_timing_generator_set_drr(
	काष्ठा timing_generator *tg,
	स्थिर काष्ठा drr_params *params)
अणु

	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	अगर (params != शून्य &&
		params->vertical_total_max > 0 &&
		params->vertical_total_min > 0) अणु

		CRTC_REG_UPDATE(
				CRTC0_CRTC_V_TOTAL_MIN,
				CRTC_V_TOTAL_MIN, params->vertical_total_min - 1);
		CRTC_REG_UPDATE(
				CRTC0_CRTC_V_TOTAL_MAX,
				CRTC_V_TOTAL_MAX, params->vertical_total_max - 1);
		CRTC_REG_SET_N(CRTC0_CRTC_V_TOTAL_CONTROL, 6,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_V_TOTAL_MIN_SEL), 1,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_V_TOTAL_MAX_SEL), 1,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_FORCE_LOCK_ON_EVENT), 0,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_FORCE_LOCK_TO_MASTER_VSYNC), 0,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_SET_V_TOTAL_MIN_MASK_EN), 0,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_SET_V_TOTAL_MIN_MASK), 0);
		CRTC_REG_UPDATE(
				CRTC0_CRTC_STATIC_SCREEN_CONTROL,
				CRTC_STATIC_SCREEN_EVENT_MASK,
				0x180);

	पूर्ण अन्यथा अणु
		CRTC_REG_SET_N(CRTC0_CRTC_V_TOTAL_CONTROL, 5,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_V_TOTAL_MIN_SEL), 0,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_V_TOTAL_MAX_SEL), 0,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_FORCE_LOCK_ON_EVENT), 0,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_FORCE_LOCK_TO_MASTER_VSYNC), 0,
				FD(CRTC0_CRTC_V_TOTAL_CONTROL__CRTC_SET_V_TOTAL_MIN_MASK), 0);
		CRTC_REG_UPDATE(
				CRTC0_CRTC_V_TOTAL_MIN,
				CRTC_V_TOTAL_MIN, 0);
		CRTC_REG_UPDATE(
				CRTC0_CRTC_V_TOTAL_MAX,
				CRTC_V_TOTAL_MAX, 0);
		CRTC_REG_UPDATE(
				CRTC0_CRTC_STATIC_SCREEN_CONTROL,
				CRTC_STATIC_SCREEN_EVENT_MASK,
				0);
	पूर्ण
पूर्ण

अटल व्योम dce120_timing_generator_get_crtc_scanoutpos(
	काष्ठा timing_generator *tg,
	uपूर्णांक32_t *v_blank_start,
	uपूर्णांक32_t *v_blank_end,
	uपूर्णांक32_t *h_position,
	uपूर्णांक32_t *v_position)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	काष्ठा crtc_position position;

	uपूर्णांक32_t v_blank_start_end = dm_पढ़ो_reg_soc15(
			tg->ctx,
			mmCRTC0_CRTC_V_BLANK_START_END,
			tg110->offsets.crtc);

	*v_blank_start = get_reg_field_value(v_blank_start_end,
					     CRTC0_CRTC_V_BLANK_START_END,
					     CRTC_V_BLANK_START);
	*v_blank_end = get_reg_field_value(v_blank_start_end,
					   CRTC0_CRTC_V_BLANK_START_END,
					   CRTC_V_BLANK_END);

	dce120_timing_generator_get_crtc_position(
			tg, &position);

	*h_position = position.horizontal_count;
	*v_position = position.vertical_count;
पूर्ण

अटल व्योम dce120_timing_generator_enable_advanced_request(
	काष्ठा timing_generator *tg,
	bool enable,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t v_sync_width_and_b_porch =
				timing->v_total - timing->v_addressable -
				timing->v_border_bottom - timing->v_front_porch;
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(
				tg->ctx,
				mmCRTC0_CRTC_START_LINE_CONTROL,
				tg110->offsets.crtc);

	set_reg_field_value(
		value,
		enable ? 0 : 1,
		CRTC0_CRTC_START_LINE_CONTROL,
		CRTC_LEGACY_REQUESTOR_EN);

	/* Program advanced line position acc.to the best हाल from fetching data perspective to hide MC latency
	 * and prefilling Line Buffer in V Blank (to 10 lines as LB can store max 10 lines)
	 */
	अगर (v_sync_width_and_b_porch > 10)
		v_sync_width_and_b_porch = 10;

	set_reg_field_value(
		value,
		v_sync_width_and_b_porch,
		CRTC0_CRTC_START_LINE_CONTROL,
		CRTC_ADVANCED_START_LINE_POSITION);

	dm_ग_लिखो_reg_soc15(tg->ctx,
			mmCRTC0_CRTC_START_LINE_CONTROL,
			tg110->offsets.crtc,
			value);
पूर्ण

अटल व्योम dce120_tg_program_blank_color(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *black_color)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = 0;

	CRTC_REG_UPDATE_3(
		CRTC0_CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB, black_color->color_b_cb,
		CRTC_BLACK_COLOR_G_Y, black_color->color_g_y,
		CRTC_BLACK_COLOR_R_CR, black_color->color_r_cr);

	value = dm_पढ़ो_reg_soc15(
				tg->ctx,
				mmCRTC0_CRTC_BLACK_COLOR,
				tg110->offsets.crtc);
	dm_ग_लिखो_reg_soc15(
		tg->ctx,
		mmCRTC0_CRTC_BLANK_DATA_COLOR,
		tg110->offsets.crtc,
		value);
पूर्ण

अटल व्योम dce120_tg_set_overscan_color(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *overscan_color)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_SET_3(
		CRTC0_CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_BLUE, overscan_color->color_b_cb,
		CRTC_OVERSCAN_COLOR_GREEN, overscan_color->color_g_y,
		CRTC_OVERSCAN_COLOR_RED, overscan_color->color_r_cr);
पूर्ण

अटल व्योम dce120_tg_program_timing(काष्ठा timing_generator *tg,
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
		dce120_timing_generator_program_blanking(tg, timing);
पूर्ण

अटल bool dce120_tg_is_blanked(काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(
			tg->ctx,
			mmCRTC0_CRTC_BLANK_CONTROL,
			tg110->offsets.crtc);

	अगर (get_reg_field_value(
		value,
		CRTC0_CRTC_BLANK_CONTROL,
		CRTC_BLANK_DATA_EN) == 1 &&
	    get_reg_field_value(
		value,
		CRTC0_CRTC_BLANK_CONTROL,
		CRTC_CURRENT_BLANK_STATE) == 1)
			वापस true;

	वापस false;
पूर्ण

अटल व्योम dce120_tg_set_blank(काष्ठा timing_generator *tg,
		bool enable_blanking)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_SET(
		CRTC0_CRTC_DOUBLE_BUFFER_CONTROL,
		CRTC_BLANK_DATA_DOUBLE_BUFFER_EN, 1);

	अगर (enable_blanking)
		CRTC_REG_SET(CRTC0_CRTC_BLANK_CONTROL, CRTC_BLANK_DATA_EN, 1);
	अन्यथा
		dm_ग_लिखो_reg_soc15(tg->ctx, mmCRTC0_CRTC_BLANK_CONTROL,
			tg110->offsets.crtc, 0);
पूर्ण

bool dce120_tg_validate_timing(काष्ठा timing_generator *tg,
	स्थिर काष्ठा dc_crtc_timing *timing);

अटल व्योम dce120_tg_रुको_क्रम_state(काष्ठा timing_generator *tg,
	क्रमागत crtc_state state)
अणु
	चयन (state) अणु
	हाल CRTC_STATE_VBLANK:
		dce120_timing_generator_रुको_क्रम_vblank(tg);
		अवरोध;

	हाल CRTC_STATE_VACTIVE:
		dce120_timing_generator_रुको_क्रम_vactive(tg);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dce120_tg_set_colors(काष्ठा timing_generator *tg,
	स्थिर काष्ठा tg_color *blank_color,
	स्थिर काष्ठा tg_color *overscan_color)
अणु
	अगर (blank_color != शून्य)
		dce120_tg_program_blank_color(tg, blank_color);

	अगर (overscan_color != शून्य)
		dce120_tg_set_overscan_color(tg, overscan_color);
पूर्ण

अटल व्योम dce120_timing_generator_set_अटल_screen_control(
	काष्ठा timing_generator *tg,
	uपूर्णांक32_t event_triggers,
	uपूर्णांक32_t num_frames)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	// By रेजिस्टर spec, it only takes 8 bit value
	अगर (num_frames > 0xFF)
		num_frames = 0xFF;

	CRTC_REG_UPDATE_2(CRTC0_CRTC_STATIC_SCREEN_CONTROL,
			CRTC_STATIC_SCREEN_EVENT_MASK, event_triggers,
			CRTC_STATIC_SCREEN_FRAME_COUNT, num_frames);
पूर्ण

अटल व्योम dce120_timing_generator_set_test_pattern(
	काष्ठा timing_generator *tg,
	/* TODO: replace 'controller_dp_test_pattern' by 'test_pattern_mode'
	 * because this is not DP-specअगरic (which is probably somewhere in DP
	 * encoder) */
	क्रमागत controller_dp_test_pattern test_pattern,
	क्रमागत dc_color_depth color_depth)
अणु
	काष्ठा dc_context *ctx = tg->ctx;
	uपूर्णांक32_t value;
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

		CRTC_REG_UPDATE_2(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
				CRTC_TEST_PATTERN_VRES, 6,
				CRTC_TEST_PATTERN_HRES, 6);

		CRTC_REG_UPDATE_4(CRTC0_CRTC_TEST_PATTERN_CONTROL,
				CRTC_TEST_PATTERN_EN, 1,
				CRTC_TEST_PATTERN_MODE, mode,
				CRTC_TEST_PATTERN_DYNAMIC_RANGE, dyn_range,
				CRTC_TEST_PATTERN_COLOR_FORMAT, bit_depth);
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

		dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_PARAMETERS, tg110->offsets.crtc, 0);

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
		क्रम (index = 0; index < 6; index++) अणु
			/* prepare color mask, first ग_लिखो PATTERN_DATA
			 * will have all zeros
			 */
			set_reg_field_value(
				value,
				(1 << index),
				CRTC0_CRTC_TEST_PATTERN_COLOR,
				CRTC_TEST_PATTERN_MASK);
			/* ग_लिखो color component */
			dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, value);
			/* prepare next color component,
			 * will be written in the next iteration
			 */
			set_reg_field_value(
				value,
				dst_color[index],
				CRTC0_CRTC_TEST_PATTERN_COLOR,
				CRTC_TEST_PATTERN_DATA);
		पूर्ण
		/* ग_लिखो last color component,
		 * it's been alपढ़ोy prepared in the loop
		 */
		dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, value);

		/* enable test pattern */
		CRTC_REG_UPDATE_4(CRTC0_CRTC_TEST_PATTERN_CONTROL,
				CRTC_TEST_PATTERN_EN, 1,
				CRTC_TEST_PATTERN_MODE, mode,
				CRTC_TEST_PATTERN_DYNAMIC_RANGE, 0,
				CRTC_TEST_PATTERN_COLOR_FORMAT, bit_depth);
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
			CRTC_REG_UPDATE_5(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
					CRTC_TEST_PATTERN_INC0, inc_base,
					CRTC_TEST_PATTERN_INC1, 0,
					CRTC_TEST_PATTERN_HRES, 6,
					CRTC_TEST_PATTERN_VRES, 6,
					CRTC_TEST_PATTERN_RAMP0_OFFSET, 0);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
		अणु
			CRTC_REG_UPDATE_5(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
					CRTC_TEST_PATTERN_INC0, inc_base,
					CRTC_TEST_PATTERN_INC1, 0,
					CRTC_TEST_PATTERN_HRES, 8,
					CRTC_TEST_PATTERN_VRES, 6,
					CRTC_TEST_PATTERN_RAMP0_OFFSET, 0);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
		अणु
			CRTC_REG_UPDATE_5(CRTC0_CRTC_TEST_PATTERN_PARAMETERS,
					CRTC_TEST_PATTERN_INC0, inc_base,
					CRTC_TEST_PATTERN_INC1, inc_base + 2,
					CRTC_TEST_PATTERN_HRES, 8,
					CRTC_TEST_PATTERN_VRES, 5,
					CRTC_TEST_PATTERN_RAMP0_OFFSET, 384 << 6);
		पूर्ण
		अवरोध;
		शेष:
		अवरोध;
		पूर्ण

		dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, 0);

		/* enable test pattern */
		dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_CONTROL, tg110->offsets.crtc, 0);

		CRTC_REG_UPDATE_4(CRTC0_CRTC_TEST_PATTERN_CONTROL,
				CRTC_TEST_PATTERN_EN, 1,
				CRTC_TEST_PATTERN_MODE, mode,
				CRTC_TEST_PATTERN_DYNAMIC_RANGE, 0,
				CRTC_TEST_PATTERN_COLOR_FORMAT, bit_depth);
	पूर्ण
	अवरोध;
	हाल CONTROLLER_DP_TEST_PATTERN_VIDEOMODE:
	अणु
		value = 0;
		dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_CONTROL, tg110->offsets.crtc,  value);
		dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_COLOR, tg110->offsets.crtc, value);
		dm_ग_लिखो_reg_soc15(ctx, mmCRTC0_CRTC_TEST_PATTERN_PARAMETERS, tg110->offsets.crtc, value);
	पूर्ण
	अवरोध;
	शेष:
	अवरोध;
	पूर्ण
पूर्ण

अटल bool dce120_arm_vert_पूर्णांकr(
		काष्ठा timing_generator *tg,
		uपूर्णांक8_t width)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t v_blank_start, v_blank_end, h_position, v_position;

	tg->funcs->get_scanoutpos(
				tg,
				&v_blank_start,
				&v_blank_end,
				&h_position,
				&v_position);

	अगर (v_blank_start == 0 || v_blank_end == 0)
		वापस false;

	CRTC_REG_SET_2(
			CRTC0_CRTC_VERTICAL_INTERRUPT0_POSITION,
			CRTC_VERTICAL_INTERRUPT0_LINE_START, v_blank_start,
			CRTC_VERTICAL_INTERRUPT0_LINE_END, v_blank_start + width);

	वापस true;
पूर्ण


अटल bool dce120_is_tg_enabled(काष्ठा timing_generator *tg)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value, field;

	value = dm_पढ़ो_reg_soc15(tg->ctx, mmCRTC0_CRTC_CONTROL,
				  tg110->offsets.crtc);
	field = get_reg_field_value(value, CRTC0_CRTC_CONTROL,
				    CRTC_CURRENT_MASTER_EN_STATE);

	वापस field == 1;
पूर्ण

अटल bool dce120_configure_crc(काष्ठा timing_generator *tg,
				 स्थिर काष्ठा crc_params *params)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Cannot configure crc on a CRTC that is disabled */
	अगर (!dce120_is_tg_enabled(tg))
		वापस false;

	/* First, disable CRC beक्रमe we configure it. */
	dm_ग_लिखो_reg_soc15(tg->ctx, mmCRTC0_CRTC_CRC_CNTL,
			   tg110->offsets.crtc, 0);

	अगर (!params->enable)
		वापस true;

	/* Program frame boundaries */
	/* Winकरोw A x axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWA_X_CONTROL,
			  CRTC_CRC0_WINDOWA_X_START, params->winकरोwa_x_start,
			  CRTC_CRC0_WINDOWA_X_END, params->winकरोwa_x_end);

	/* Winकरोw A y axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWA_Y_CONTROL,
			  CRTC_CRC0_WINDOWA_Y_START, params->winकरोwa_y_start,
			  CRTC_CRC0_WINDOWA_Y_END, params->winकरोwa_y_end);

	/* Winकरोw B x axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWB_X_CONTROL,
			  CRTC_CRC0_WINDOWB_X_START, params->winकरोwb_x_start,
			  CRTC_CRC0_WINDOWB_X_END, params->winकरोwb_x_end);

	/* Winकरोw B y axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWB_Y_CONTROL,
			  CRTC_CRC0_WINDOWB_Y_START, params->winकरोwb_y_start,
			  CRTC_CRC0_WINDOWB_Y_END, params->winकरोwb_y_end);

	/* Set crc mode and selection, and enable. Only using CRC0*/
	CRTC_REG_UPDATE_3(CRTC0_CRTC_CRC_CNTL,
			  CRTC_CRC_EN, params->continuous_mode ? 1 : 0,
			  CRTC_CRC0_SELECT, params->selection,
			  CRTC_CRC_EN, 1);

	वापस true;
पूर्ण

अटल bool dce120_get_crc(काष्ठा timing_generator *tg, uपूर्णांक32_t *r_cr,
			   uपूर्णांक32_t *g_y, uपूर्णांक32_t *b_cb)
अणु
	काष्ठा dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uपूर्णांक32_t value, field;

	value = dm_पढ़ो_reg_soc15(tg->ctx, mmCRTC0_CRTC_CRC_CNTL,
				  tg110->offsets.crtc);
	field = get_reg_field_value(value, CRTC0_CRTC_CRC_CNTL, CRTC_CRC_EN);

	/* Early वापस अगर CRC is not enabled क्रम this CRTC */
	अगर (!field)
		वापस false;

	value = dm_पढ़ो_reg_soc15(tg->ctx, mmCRTC0_CRTC_CRC0_DATA_RG,
				  tg110->offsets.crtc);
	*r_cr = get_reg_field_value(value, CRTC0_CRTC_CRC0_DATA_RG, CRC0_R_CR);
	*g_y = get_reg_field_value(value, CRTC0_CRTC_CRC0_DATA_RG, CRC0_G_Y);

	value = dm_पढ़ो_reg_soc15(tg->ctx, mmCRTC0_CRTC_CRC0_DATA_B,
				  tg110->offsets.crtc);
	*b_cb = get_reg_field_value(value, CRTC0_CRTC_CRC0_DATA_B, CRC0_B_CB);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा timing_generator_funcs dce120_tg_funcs = अणु
		.validate_timing = dce120_tg_validate_timing,
		.program_timing = dce120_tg_program_timing,
		.enable_crtc = dce120_timing_generator_enable_crtc,
		.disable_crtc = dce110_timing_generator_disable_crtc,
		/* used by enable_timing_synchronization. Not need क्रम FPGA */
		.is_counter_moving = dce110_timing_generator_is_counter_moving,
		/* never be called */
		.get_position = dce120_timing_generator_get_crtc_position,
		.get_frame_count = dce120_timing_generator_get_vblank_counter,
		.get_scanoutpos = dce120_timing_generator_get_crtc_scanoutpos,
		.set_early_control = dce120_timing_generator_set_early_control,
		/* used by enable_timing_synchronization. Not need क्रम FPGA */
		.रुको_क्रम_state = dce120_tg_रुको_क्रम_state,
		.set_blank = dce120_tg_set_blank,
		.is_blanked = dce120_tg_is_blanked,
		/* never be called */
		.set_colors = dce120_tg_set_colors,
		.set_overscan_blank_color = dce120_timing_generator_set_overscan_color_black,
		.set_blank_color = dce120_timing_generator_program_blank_color,
		.disable_vga = dce120_timing_generator_disable_vga,
		.did_triggered_reset_occur = dce120_timing_generator_did_triggered_reset_occur,
		.setup_global_swap_lock = dce120_timing_generator_setup_global_swap_lock,
		.enable_reset_trigger = dce120_timing_generator_enable_reset_trigger,
		.disable_reset_trigger = dce120_timing_generator_disable_reset_trigger,
		.tear_करोwn_global_swap_lock = dce120_timing_generator_tear_करोwn_global_swap_lock,
		.enable_advanced_request = dce120_timing_generator_enable_advanced_request,
		.set_drr = dce120_timing_generator_set_drr,
		.set_अटल_screen_control = dce120_timing_generator_set_अटल_screen_control,
		.set_test_pattern = dce120_timing_generator_set_test_pattern,
		.arm_vert_पूर्णांकr = dce120_arm_vert_पूर्णांकr,
		.is_tg_enabled = dce120_is_tg_enabled,
		.configure_crc = dce120_configure_crc,
		.get_crc = dce120_get_crc,
पूर्ण;


व्योम dce120_timing_generator_स्थिरruct(
	काष्ठा dce110_timing_generator *tg110,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t instance,
	स्थिर काष्ठा dce110_timing_generator_offsets *offsets)
अणु
	tg110->controller_id = CONTROLLER_ID_D0 + instance;
	tg110->base.inst = instance;

	tg110->offsets = *offsets;

	tg110->base.funcs = &dce120_tg_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_total = CRTC0_CRTC_H_TOTAL__CRTC_H_TOTAL_MASK + 1;
	tg110->max_v_total = CRTC0_CRTC_V_TOTAL__CRTC_V_TOTAL_MASK + 1;

	/*//CRTC requires a minimum HBLANK = 32 pixels and o
	 * Minimum HSYNC = 8 pixels*/
	tg110->min_h_blank = 32;
	/*DCE12_CRTC_Block_ARch.करोc*/
	tg110->min_h_front_porch = 0;
	tg110->min_h_back_porch = 0;

	tg110->min_h_sync_width = 4;
	tg110->min_v_sync_width = 1;
	tg110->min_v_blank = 3;
पूर्ण
