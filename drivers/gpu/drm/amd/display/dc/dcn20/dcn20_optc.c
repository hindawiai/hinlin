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
#समावेश "dcn20_optc.h"
#समावेश "dc.h"

#घोषणा REG(reg)\
	optc1->tg_regs->reg

#घोषणा CTX \
	optc1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	optc1->tg_shअगरt->field_name, optc1->tg_mask->field_name

/**
 * Enable CRTC
 * Enable CRTC - call ASIC Control Object to enable Timing generator.
 */
bool optc2_enable_crtc(काष्ठा timing_generator *optc)
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
			OPTC_SEG0_SRC_SEL, optc->inst);

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

/**
 * DRR द्विगुन buffering control to select buffer poपूर्णांक
 * क्रम V_TOTAL, H_TOTAL, VTOTAL_MIN, VTOTAL_MAX, VTOTAL_MIN_SEL and VTOTAL_MAX_SEL रेजिस्टरs
 * Options: anyसमय, start of frame, dp start of frame (range timing)
 */
व्योम optc2_set_timing_db_mode(काष्ठा timing_generator *optc, bool enable)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	uपूर्णांक32_t blank_data_द्विगुन_buffer_enable = enable ? 1 : 0;

	REG_UPDATE(OTG_DOUBLE_BUFFER_CONTROL,
		OTG_RANGE_TIMING_DBUF_UPDATE_MODE, blank_data_द्विगुन_buffer_enable);
पूर्ण

/**
 *For the below, I'm not sure how your GSL parameters are stored in your env,
 * so I will assume a gsl_params काष्ठा क्रम now
 */
व्योम optc2_set_gsl(काष्ठा timing_generator *optc,
		   स्थिर काष्ठा gsl_params *params)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

/**
 * There are (MAX_OPTC+1)/2 gsl groups available क्रम use.
 * In each group (assign an OTG to a group by setting OTG_GSLX_EN = 1,
 * set one of the OTGs to be the master (OTG_GSL_MASTER_EN = 1) and the rest are slaves.
 */
	REG_UPDATE_5(OTG_GSL_CONTROL,
		OTG_GSL0_EN, params->gsl0_en,
		OTG_GSL1_EN, params->gsl1_en,
		OTG_GSL2_EN, params->gsl2_en,
		OTG_GSL_MASTER_EN, params->gsl_master_en,
		OTG_GSL_MASTER_MODE, params->gsl_master_mode);
पूर्ण


/* Use the gsl allow flip as the master update lock */
व्योम optc2_use_gsl_as_master_update_lock(काष्ठा timing_generator *optc,
		   स्थिर काष्ठा gsl_params *params)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OTG_GSL_CONTROL,
		OTG_MASTER_UPDATE_LOCK_GSL_EN, params->master_update_lock_gsl_en);
पूर्ण

/* You can control the GSL timing by limiting GSL to a winकरोw (X,Y) */
व्योम optc2_set_gsl_winकरोw(काष्ठा timing_generator *optc,
		   स्थिर काष्ठा gsl_params *params)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_2(OTG_GSL_WINDOW_X, 0,
		OTG_GSL_WINDOW_START_X, params->gsl_winकरोw_start_x,
		OTG_GSL_WINDOW_END_X, params->gsl_winकरोw_end_x);
	REG_SET_2(OTG_GSL_WINDOW_Y, 0,
		OTG_GSL_WINDOW_START_Y, params->gsl_winकरोw_start_y,
		OTG_GSL_WINDOW_END_Y, params->gsl_winकरोw_end_y);
पूर्ण

व्योम optc2_set_gsl_source_select(
		काष्ठा timing_generator *optc,
		पूर्णांक group_idx,
		uपूर्णांक32_t gsl_पढ़ोy_संकेत)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	चयन (group_idx) अणु
	हाल 1:
		REG_UPDATE(GSL_SOURCE_SELECT, GSL0_READY_SOURCE_SEL, gsl_पढ़ोy_संकेत);
		अवरोध;
	हाल 2:
		REG_UPDATE(GSL_SOURCE_SELECT, GSL1_READY_SOURCE_SEL, gsl_पढ़ोy_संकेत);
		अवरोध;
	हाल 3:
		REG_UPDATE(GSL_SOURCE_SELECT, GSL2_READY_SOURCE_SEL, gsl_पढ़ोy_संकेत);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* DSC encoder frame start controls: x = h position, line_num = # of lines from vstartup */
व्योम optc2_set_dsc_encoder_frame_start(काष्ठा timing_generator *optc,
					पूर्णांक x_position,
					पूर्णांक line_num)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_2(OTG_DSC_START_POSITION, 0,
			OTG_DSC_START_POSITION_X, x_position,
			OTG_DSC_START_POSITION_LINE_NUM, line_num);
पूर्ण

/* Set DSC-related configuration.
 *   dsc_mode: 0 disables DSC, other values enable DSC in specअगरied क्रमmat
 *   sc_bytes_per_pixel: Bytes per pixel in u3.28 क्रमmat
 *   dsc_slice_width: Slice width in pixels
 */
व्योम optc2_set_dsc_config(काष्ठा timing_generator *optc,
					क्रमागत optc_dsc_mode dsc_mode,
					uपूर्णांक32_t dsc_bytes_per_pixel,
					uपूर्णांक32_t dsc_slice_width)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE(OPTC_DATA_FORMAT_CONTROL,
		OPTC_DSC_MODE, dsc_mode);

	REG_SET(OPTC_BYTES_PER_PIXEL, 0,
		OPTC_DSC_BYTES_PER_PIXEL, dsc_bytes_per_pixel);

	REG_UPDATE(OPTC_WIDTH_CONTROL,
		OPTC_DSC_SLICE_WIDTH, dsc_slice_width);
पूर्ण

/*TEMP: Need to figure out inheritance model here.*/
bool optc2_is_two_pixels_per_contaपूर्णांकer(स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	वापस optc1_is_two_pixels_per_contaपूर्णांकer(timing);
पूर्ण

व्योम optc2_set_odm_bypass(काष्ठा timing_generator *optc,
		स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t h_भाग_2 = 0;

	REG_SET_3(OPTC_DATA_SOURCE_SELECT, 0,
			OPTC_NUM_OF_INPUT_SEGMENT, 0,
			OPTC_SEG0_SRC_SEL, optc->inst,
			OPTC_SEG1_SRC_SEL, 0xf);
	REG_WRITE(OTG_H_TIMING_CNTL, 0);

	h_भाग_2 = optc2_is_two_pixels_per_contaपूर्णांकer(dc_crtc_timing);
	REG_UPDATE(OTG_H_TIMING_CNTL,
			OTG_H_TIMING_DIV_BY2, h_भाग_2);
	REG_SET(OPTC_MEMORY_CONFIG, 0,
			OPTC_MEM_SEL, 0);
	optc1->opp_count = 1;
पूर्ण

व्योम optc2_set_odm_combine(काष्ठा timing_generator *optc, पूर्णांक *opp_id, पूर्णांक opp_cnt,
		काष्ठा dc_crtc_timing *timing)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	पूर्णांक mpcc_hactive = (timing->h_addressable + timing->h_border_left + timing->h_border_right)
			/ opp_cnt;
	uपूर्णांक32_t memory_mask;

	ASSERT(opp_cnt == 2);

	/* TODO: In pseuकरोcode but करोes not affect maximus, delete comment अगर we करोnt need on asic
	 * REG_SET(OTG_GLOBAL_CONTROL2, 0, GLOBAL_UPDATE_LOCK_EN, 1);
	 * Program OTG रेजिस्टर MASTER_UPDATE_LOCK_DB_X/Y to the position beक्रमe DP frame start
	 * REG_SET_2(OTG_GLOBAL_CONTROL1, 0,
	 *		MASTER_UPDATE_LOCK_DB_X, 160,
	 *		MASTER_UPDATE_LOCK_DB_Y, 240);
	 */

	/* 2 pieces of memory required क्रम up to 5120 displays, 4 क्रम up to 8192,
	 * however, क्रम ODM combine we can simplअगरy by always using 4.
	 * To make sure there's no overlap, each instance "reserves" 2 memories and
	 * they are uniquely combined here.
	 */
	memory_mask = 0x3 << (opp_id[0] * 2) | 0x3 << (opp_id[1] * 2);

	अगर (REG(OPTC_MEMORY_CONFIG))
		REG_SET(OPTC_MEMORY_CONFIG, 0,
			OPTC_MEM_SEL, memory_mask);

	REG_SET_3(OPTC_DATA_SOURCE_SELECT, 0,
			OPTC_NUM_OF_INPUT_SEGMENT, 1,
			OPTC_SEG0_SRC_SEL, opp_id[0],
			OPTC_SEG1_SRC_SEL, opp_id[1]);

	REG_UPDATE(OPTC_WIDTH_CONTROL,
			OPTC_SEGMENT_WIDTH, mpcc_hactive);

	REG_SET(OTG_H_TIMING_CNTL, 0, OTG_H_TIMING_DIV_BY2, 1);
	optc1->opp_count = opp_cnt;
पूर्ण

व्योम optc2_get_optc_source(काष्ठा timing_generator *optc,
		uपूर्णांक32_t *num_of_src_opp,
		uपूर्णांक32_t *src_opp_id_0,
		uपूर्णांक32_t *src_opp_id_1)
अणु
	uपूर्णांक32_t num_of_input_segments;
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_GET_3(OPTC_DATA_SOURCE_SELECT,
			OPTC_NUM_OF_INPUT_SEGMENT, &num_of_input_segments,
			OPTC_SEG0_SRC_SEL, src_opp_id_0,
			OPTC_SEG1_SRC_SEL, src_opp_id_1);

	अगर (num_of_input_segments == 1)
		*num_of_src_opp = 2;
	अन्यथा
		*num_of_src_opp = 1;

	/* Work around VBIOS not updating OPTC_NUM_OF_INPUT_SEGMENT */
	अगर (*src_opp_id_1 == 0xf)
		*num_of_src_opp = 1;
पूर्ण

व्योम optc2_set_dwb_source(काष्ठा timing_generator *optc,
		uपूर्णांक32_t dwb_pipe_inst)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	अगर (dwb_pipe_inst == 0)
		REG_UPDATE(DWB_SOURCE_SELECT,
				OPTC_DWB0_SOURCE_SELECT, optc->inst);
	अन्यथा अगर (dwb_pipe_inst == 1)
		REG_UPDATE(DWB_SOURCE_SELECT,
				OPTC_DWB1_SOURCE_SELECT, optc->inst);
पूर्ण

व्योम optc2_align_vblanks(
	काष्ठा timing_generator *optc_master,
	काष्ठा timing_generator *optc_slave,
	uपूर्णांक32_t master_pixel_घड़ी_100Hz,
	uपूर्णांक32_t slave_pixel_घड़ी_100Hz,
	uपूर्णांक8_t master_घड़ी_भागider,
	uपूर्णांक8_t slave_घड़ी_भागider)
अणु
	/* accessing slave OTG रेजिस्टरs */
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc_slave);

	uपूर्णांक32_t master_v_active = 0;
	uपूर्णांक32_t master_h_total = 0;
	uपूर्णांक32_t slave_h_total = 0;
	uपूर्णांक64_t L, XY;
	uपूर्णांक32_t X, Y, p = 10000;
	uपूर्णांक32_t master_update_lock;

	/* disable slave OTG */
	REG_UPDATE(OTG_CONTROL, OTG_MASTER_EN, 0);
	/* रुको until disabled */
	REG_WAIT(OTG_CONTROL,
			 OTG_CURRENT_MASTER_EN_STATE,
			 0, 10, 5000);

	REG_GET(OTG_H_TOTAL, OTG_H_TOTAL, &slave_h_total);

	/* assign slave OTG to be controlled by master update lock */
	REG_SET(OTG_GLOBAL_CONTROL0, 0,
			OTG_MASTER_UPDATE_LOCK_SEL, optc_master->inst);

	/* accessing master OTG रेजिस्टरs */
	optc1 = DCN10TG_FROM_TG(optc_master);

	/* saving update lock state, not sure अगर it's needed */
	REG_GET(OTG_MASTER_UPDATE_LOCK,
			OTG_MASTER_UPDATE_LOCK, &master_update_lock);
	/* unlocking master OTG */
	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
			OTG_MASTER_UPDATE_LOCK, 0);

	REG_GET(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, &master_v_active);
	REG_GET(OTG_H_TOTAL, OTG_H_TOTAL, &master_h_total);

	/* calculate when to enable slave OTG */
	L = (uपूर्णांक64_t)p * slave_h_total * master_pixel_घड़ी_100Hz;
	L = भाग_u64(L, master_h_total);
	L = भाग_u64(L, slave_pixel_घड़ी_100Hz);
	XY = भाग_u64(L, p);
	Y = master_v_active - XY - 1;
	X = भाग_u64(((XY + 1) * p - L) * master_h_total, p * master_घड़ी_भागider);

	/*
	 * set master OTG to unlock when V/H
	 * counters reach calculated values
	 */
	REG_UPDATE(OTG_GLOBAL_CONTROL1,
			   MASTER_UPDATE_LOCK_DB_EN, 1);
	REG_UPDATE_2(OTG_GLOBAL_CONTROL1,
				 MASTER_UPDATE_LOCK_DB_X,
				 X,
				 MASTER_UPDATE_LOCK_DB_Y,
				 Y);

	/* lock master OTG */
	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
			OTG_MASTER_UPDATE_LOCK, 1);
	REG_WAIT(OTG_MASTER_UPDATE_LOCK,
			 UPDATE_LOCK_STATUS, 1, 1, 10);

	/* accessing slave OTG रेजिस्टरs */
	optc1 = DCN10TG_FROM_TG(optc_slave);

	/*
	 * enable slave OTG, the OTG is locked with
	 * master's update lock, so it will not run
	 */
	REG_UPDATE(OTG_CONTROL,
			   OTG_MASTER_EN, 1);

	/* accessing master OTG रेजिस्टरs */
	optc1 = DCN10TG_FROM_TG(optc_master);

	/*
	 * unlock master OTG. When master H/V counters reach
	 * DB_XY poपूर्णांक, slave OTG will start
	 */
	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
			OTG_MASTER_UPDATE_LOCK, 0);

	/* accessing slave OTG रेजिस्टरs */
	optc1 = DCN10TG_FROM_TG(optc_slave);

	/* रुको क्रम slave OTG to start running*/
	REG_WAIT(OTG_CONTROL,
			 OTG_CURRENT_MASTER_EN_STATE,
			 1, 10, 5000);

	/* accessing master OTG रेजिस्टरs */
	optc1 = DCN10TG_FROM_TG(optc_master);

	/* disable the XY poपूर्णांक*/
	REG_UPDATE(OTG_GLOBAL_CONTROL1,
			   MASTER_UPDATE_LOCK_DB_EN, 0);
	REG_UPDATE_2(OTG_GLOBAL_CONTROL1,
				 MASTER_UPDATE_LOCK_DB_X,
				 0,
				 MASTER_UPDATE_LOCK_DB_Y,
				 0);

	/*restore master update lock*/
	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
			OTG_MASTER_UPDATE_LOCK, master_update_lock);

	/* accessing slave OTG रेजिस्टरs */
	optc1 = DCN10TG_FROM_TG(optc_slave);
	/* restore slave to be controlled by it's own */
	REG_SET(OTG_GLOBAL_CONTROL0, 0,
			OTG_MASTER_UPDATE_LOCK_SEL, optc_slave->inst);

पूर्ण

व्योम optc2_triplebuffer_lock(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_GLOBAL_CONTROL0, 0,
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

व्योम optc2_triplebuffer_unlock(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
		OTG_MASTER_UPDATE_LOCK, 0);

	REG_SET(OTG_VUPDATE_KEEPOUT, 0,
		OTG_MASTER_UPDATE_LOCK_VUPDATE_KEEPOUT_EN, 0);

पूर्ण

व्योम optc2_lock_द्विगुनbuffer_enable(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);
	uपूर्णांक32_t v_blank_start = 0;
	uपूर्णांक32_t h_blank_start = 0;

	REG_UPDATE(OTG_GLOBAL_CONTROL1, MASTER_UPDATE_LOCK_DB_EN, 1);

	REG_UPDATE_2(OTG_GLOBAL_CONTROL2, GLOBAL_UPDATE_LOCK_EN, 1,
			DIG_UPDATE_LOCATION, 20);

	REG_GET(OTG_V_BLANK_START_END, OTG_V_BLANK_START, &v_blank_start);

	REG_GET(OTG_H_BLANK_START_END, OTG_H_BLANK_START, &h_blank_start);

	REG_UPDATE_2(OTG_GLOBAL_CONTROL1,
			MASTER_UPDATE_LOCK_DB_X,
			h_blank_start - 200 - 1,
			MASTER_UPDATE_LOCK_DB_Y,
			v_blank_start - 1);
पूर्ण

व्योम optc2_lock_द्विगुनbuffer_disable(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_UPDATE_2(OTG_GLOBAL_CONTROL1,
				MASTER_UPDATE_LOCK_DB_X,
				0,
				MASTER_UPDATE_LOCK_DB_Y,
				0);

	REG_UPDATE_2(OTG_GLOBAL_CONTROL2, GLOBAL_UPDATE_LOCK_EN, 0,
				DIG_UPDATE_LOCATION, 0);

	REG_UPDATE(OTG_GLOBAL_CONTROL1, MASTER_UPDATE_LOCK_DB_EN, 0);
पूर्ण

व्योम optc2_setup_manual_trigger(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_8(OTG_TRIGA_CNTL, 0,
			OTG_TRIGA_SOURCE_SELECT, 21,
			OTG_TRIGA_SOURCE_PIPE_SELECT, optc->inst,
			OTG_TRIGA_RISING_EDGE_DETECT_CNTL, 1,
			OTG_TRIGA_FALLING_EDGE_DETECT_CNTL, 0,
			OTG_TRIGA_POLARITY_SELECT, 0,
			OTG_TRIGA_FREQUENCY_SELECT, 0,
			OTG_TRIGA_DELAY, 0,
			OTG_TRIGA_CLEAR, 1);
पूर्ण

व्योम optc2_program_manual_trigger(काष्ठा timing_generator *optc)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET(OTG_TRIGA_MANUAL_TRIG, 0,
			OTG_TRIGA_MANUAL_TRIG, 1);
पूर्ण

bool optc2_configure_crc(काष्ठा timing_generator *optc,
			  स्थिर काष्ठा crc_params *params)
अणु
	काष्ठा optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_SET_2(OTG_CRC_CNTL2, 0,
			OTG_CRC_DSC_MODE, params->dsc_mode,
			OTG_CRC_DATA_STREAM_COMBINE_MODE, params->odm_mode);

	वापस optc1_configure_crc(optc, params);
पूर्ण

अटल काष्ठा timing_generator_funcs dcn20_tg_funcs = अणु
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
		.set_blank = optc1_set_blank,
		.is_blanked = optc1_is_blanked,
		.set_blank_color = optc1_program_blank_color,
		.enable_reset_trigger = optc1_enable_reset_trigger,
		.enable_crtc_reset = optc1_enable_crtc_reset,
		.did_triggered_reset_occur = optc1_did_triggered_reset_occur,
		.triplebuffer_lock = optc2_triplebuffer_lock,
		.triplebuffer_unlock = optc2_triplebuffer_unlock,
		.disable_reset_trigger = optc1_disable_reset_trigger,
		.lock = optc1_lock,
		.unlock = optc1_unlock,
		.lock_द्विगुनbuffer_enable = optc2_lock_द्विगुनbuffer_enable,
		.lock_द्विगुनbuffer_disable = optc2_lock_द्विगुनbuffer_disable,
		.enable_optc_घड़ी = optc1_enable_optc_घड़ी,
		.set_drr = optc1_set_drr,
		.set_अटल_screen_control = optc1_set_अटल_screen_control,
		.program_stereo = optc1_program_stereo,
		.is_stereo_left_eye = optc1_is_stereo_left_eye,
		.set_blank_data_द्विगुन_buffer = optc1_set_blank_data_द्विगुन_buffer,
		.tg_init = optc1_tg_init,
		.is_tg_enabled = optc1_is_tg_enabled,
		.is_optc_underflow_occurred = optc1_is_optc_underflow_occurred,
		.clear_optc_underflow = optc1_clear_optc_underflow,
		.setup_global_swap_lock = शून्य,
		.get_crc = optc1_get_crc,
		.configure_crc = optc2_configure_crc,
		.set_dsc_config = optc2_set_dsc_config,
		.set_dwb_source = optc2_set_dwb_source,
		.set_odm_bypass = optc2_set_odm_bypass,
		.set_odm_combine = optc2_set_odm_combine,
		.get_optc_source = optc2_get_optc_source,
		.set_gsl = optc2_set_gsl,
		.set_gsl_source_select = optc2_set_gsl_source_select,
		.set_vtg_params = optc1_set_vtg_params,
		.program_manual_trigger = optc2_program_manual_trigger,
		.setup_manual_trigger = optc2_setup_manual_trigger,
		.get_hw_timing = optc1_get_hw_timing,
		.align_vblanks = optc2_align_vblanks,
पूर्ण;

व्योम dcn20_timing_generator_init(काष्ठा optc *optc1)
अणु
	optc1->base.funcs = &dcn20_tg_funcs;

	optc1->max_h_total = optc1->tg_mask->OTG_H_TOTAL + 1;
	optc1->max_v_total = optc1->tg_mask->OTG_V_TOTAL + 1;

	optc1->min_h_blank = 32;
	optc1->min_v_blank = 3;
	optc1->min_v_blank_पूर्णांकerlace = 5;
	optc1->min_h_sync_width = 4;//	Minimum HSYNC = 8 pixels asked By HW in the first place क्रम no actual reason. Oculus Rअगरt S will not light up with 8 as it's hsyncWidth is 6. Changing it to 4 to fix that issue.
	optc1->min_v_sync_width = 1;
पूर्ण

