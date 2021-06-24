<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#समावेश "dm_services.h"
#समावेश "dc.h"
#समावेश "dc_bios_types.h"
#समावेश "core_types.h"
#समावेश "core_status.h"
#समावेश "resource.h"
#समावेश "dm_helpers.h"
#समावेश "dce110_hw_sequencer.h"
#समावेश "dce110_timing_generator.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "gpio_service_interface.h"

#समावेश "dce110_compressor.h"

#समावेश "bios/bios_parser_helper.h"
#समावेश "timing_generator.h"
#समावेश "mem_input.h"
#समावेश "opp.h"
#समावेश "ipp.h"
#समावेश "transform.h"
#समावेश "stream_encoder.h"
#समावेश "link_encoder.h"
#समावेश "link_hwss.h"
#समावेश "dc_link_dp.h"
#समावेश "clock_source.h"
#समावेश "clk_mgr.h"
#समावेश "abm.h"
#समावेश "audio.h"
#समावेश "reg_helper.h"
#समावेश "panel_cntl.h"

/* include DCE11 रेजिस्टर header files */
#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"
#समावेश "custom_float.h"

#समावेश "atomfirmware.h"

#घोषणा GAMMA_HW_POINTS_NUM 256

/*
 * All values are in milliseconds;
 * For eDP, after घातer-up/घातer/करोwn,
 * 300/500 msec max. delay from LCDVCC to black video generation
 */
#घोषणा PANEL_POWER_UP_TIMEOUT 300
#घोषणा PANEL_POWER_DOWN_TIMEOUT 500
#घोषणा HPD_CHECK_INTERVAL 10
#घोषणा OLED_POST_T7_DELAY 100
#घोषणा OLED_PRE_T11_DELAY 150

#घोषणा CTX \
	hws->ctx

#घोषणा DC_LOGGER_INIT()

#घोषणा REG(reg)\
	hws->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name

काष्ठा dce110_hw_seq_reg_offsets अणु
	uपूर्णांक32_t crtc;
पूर्ण;

अटल स्थिर काष्ठा dce110_hw_seq_reg_offsets reg_offsets[] = अणु
अणु
	.crtc = (mmCRTC0_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC1_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTC2_CRTC_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण,
अणु
	.crtc = (mmCRTCV_GSL_CONTROL - mmCRTC_GSL_CONTROL),
पूर्ण
पूर्ण;

#घोषणा HW_REG_BLND(reg, id)\
	(reg + reg_offsets[id].blnd)

#घोषणा HW_REG_CRTC(reg, id)\
	(reg + reg_offsets[id].crtc)

#घोषणा MAX_WATERMARK 0xFFFF
#घोषणा SAFE_NBP_MARK 0x7FFF

/*******************************************************************************
 * Private definitions
 ******************************************************************************/
/***************************PIPE_CONTROL***********************************/
अटल व्योम dce110_init_pte(काष्ठा dc_context *ctx)
अणु
	uपूर्णांक32_t addr;
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t chunk_पूर्णांक = 0;
	uपूर्णांक32_t chunk_mul = 0;

	addr = mmUNP_DVMM_PTE_CONTROL;
	value = dm_पढ़ो_reg(ctx, addr);

	set_reg_field_value(
		value,
		0,
		DVMM_PTE_CONTROL,
		DVMM_USE_SINGLE_PTE);

	set_reg_field_value(
		value,
		1,
		DVMM_PTE_CONTROL,
		DVMM_PTE_BUFFER_MODE0);

	set_reg_field_value(
		value,
		1,
		DVMM_PTE_CONTROL,
		DVMM_PTE_BUFFER_MODE1);

	dm_ग_लिखो_reg(ctx, addr, value);

	addr = mmDVMM_PTE_REQ;
	value = dm_पढ़ो_reg(ctx, addr);

	chunk_पूर्णांक = get_reg_field_value(
		value,
		DVMM_PTE_REQ,
		HFLIP_PTEREQ_PER_CHUNK_INT);

	chunk_mul = get_reg_field_value(
		value,
		DVMM_PTE_REQ,
		HFLIP_PTEREQ_PER_CHUNK_MULTIPLIER);

	अगर (chunk_पूर्णांक != 0x4 || chunk_mul != 0x4) अणु

		set_reg_field_value(
			value,
			255,
			DVMM_PTE_REQ,
			MAX_PTEREQ_TO_ISSUE);

		set_reg_field_value(
			value,
			4,
			DVMM_PTE_REQ,
			HFLIP_PTEREQ_PER_CHUNK_INT);

		set_reg_field_value(
			value,
			4,
			DVMM_PTE_REQ,
			HFLIP_PTEREQ_PER_CHUNK_MULTIPLIER);

		dm_ग_लिखो_reg(ctx, addr, value);
	पूर्ण
पूर्ण
/**************************************************************************/

अटल व्योम enable_display_pipe_घड़ी_gating(
	काष्ठा dc_context *ctx,
	bool घड़ी_gating)
अणु
	/*TODO*/
पूर्ण

अटल bool dce110_enable_display_घातer_gating(
	काष्ठा dc *dc,
	uपूर्णांक8_t controller_id,
	काष्ठा dc_bios *dcb,
	क्रमागत pipe_gating_control घातer_gating)
अणु
	क्रमागत bp_result bp_result = BP_RESULT_OK;
	क्रमागत bp_pipe_control_action cntl;
	काष्ठा dc_context *ctx = dc->ctx;
	अचिन्हित पूर्णांक underlay_idx = dc->res_pool->underlay_pipe_index;

	अगर (IS_FPGA_MAXIMUS_DC(ctx->dce_environment))
		वापस true;

	अगर (घातer_gating == PIPE_GATING_CONTROL_INIT)
		cntl = ASIC_PIPE_INIT;
	अन्यथा अगर (घातer_gating == PIPE_GATING_CONTROL_ENABLE)
		cntl = ASIC_PIPE_ENABLE;
	अन्यथा
		cntl = ASIC_PIPE_DISABLE;

	अगर (controller_id == underlay_idx)
		controller_id = CONTROLLER_ID_UNDERLAY0 - 1;

	अगर (घातer_gating != PIPE_GATING_CONTROL_INIT || controller_id == 0)अणु

		bp_result = dcb->funcs->enable_disp_घातer_gating(
						dcb, controller_id + 1, cntl);

		/* Revert MASTER_UPDATE_MODE to 0 because bios sets it 2
		 * by शेष when command table is called
		 *
		 * Bios parser accepts controller_id = 6 as indicative of
		 * underlay pipe in dce110. But we करो not support more
		 * than 3.
		 */
		अगर (controller_id < CONTROLLER_ID_MAX - 1)
			dm_ग_लिखो_reg(ctx,
				HW_REG_CRTC(mmCRTC_MASTER_UPDATE_MODE, controller_id),
				0);
	पूर्ण

	अगर (घातer_gating != PIPE_GATING_CONTROL_ENABLE)
		dce110_init_pte(ctx);

	अगर (bp_result == BP_RESULT_OK)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम build_prescale_params(काष्ठा ipp_prescale_params *prescale_params,
		स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	prescale_params->mode = IPP_PRESCALE_MODE_FIXED_UNSIGNED;

	चयन (plane_state->क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		prescale_params->scale = 0x2082;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		prescale_params->scale = 0x2020;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		prescale_params->scale = 0x2008;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		prescale_params->scale = 0x2000;
		अवरोध;
	शेष:
		ASSERT(false);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool
dce110_set_input_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
			       स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा input_pixel_processor *ipp = pipe_ctx->plane_res.ipp;
	स्थिर काष्ठा dc_transfer_func *tf = शून्य;
	काष्ठा ipp_prescale_params prescale_params = अणु 0 पूर्ण;
	bool result = true;

	अगर (ipp == शून्य)
		वापस false;

	अगर (plane_state->in_transfer_func)
		tf = plane_state->in_transfer_func;

	build_prescale_params(&prescale_params, plane_state);
	ipp->funcs->ipp_program_prescale(ipp, &prescale_params);

	अगर (plane_state->gamma_correction &&
			!plane_state->gamma_correction->is_identity &&
			dce_use_lut(plane_state->क्रमmat))
		ipp->funcs->ipp_program_input_lut(ipp, plane_state->gamma_correction);

	अगर (tf == शून्य) अणु
		/* Default हाल अगर no input transfer function specअगरied */
		ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_sRGB);
	पूर्ण अन्यथा अगर (tf->type == TF_TYPE_PREDEFINED) अणु
		चयन (tf->tf) अणु
		हाल TRANSFER_FUNCTION_SRGB:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_sRGB);
			अवरोध;
		हाल TRANSFER_FUNCTION_BT709:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_xvYCC);
			अवरोध;
		हाल TRANSFER_FUNCTION_LINEAR:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_BYPASS);
			अवरोध;
		हाल TRANSFER_FUNCTION_PQ:
		शेष:
			result = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (tf->type == TF_TYPE_BYPASS) अणु
		ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_BYPASS);
	पूर्ण अन्यथा अणु
		/*TF_TYPE_DISTRIBUTED_POINTS - Not supported in DCE 11*/
		result = false;
	पूर्ण

	वापस result;
पूर्ण

अटल bool convert_to_custom_भग्न(काष्ठा pwl_result_data *rgb_resulted,
				    काष्ठा curve_poपूर्णांकs *arr_poपूर्णांकs,
				    uपूर्णांक32_t hw_poपूर्णांकs_num)
अणु
	काष्ठा custom_भग्न_क्रमmat fmt;

	काष्ठा pwl_result_data *rgb = rgb_resulted;

	uपूर्णांक32_t i = 0;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = true;

	अगर (!convert_to_custom_भग्न_क्रमmat(arr_poपूर्णांकs[0].x, &fmt,
					    &arr_poपूर्णांकs[0].custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (!convert_to_custom_भग्न_क्रमmat(arr_poपूर्णांकs[0].offset, &fmt,
					    &arr_poपूर्णांकs[0].custom_भग्न_offset)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (!convert_to_custom_भग्न_क्रमmat(arr_poपूर्णांकs[0].slope, &fmt,
					    &arr_poपूर्णांकs[0].custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	fmt.mantissa_bits = 10;
	fmt.sign = false;

	अगर (!convert_to_custom_भग्न_क्रमmat(arr_poपूर्णांकs[1].x, &fmt,
					    &arr_poपूर्णांकs[1].custom_भग्न_x)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (!convert_to_custom_भग्न_क्रमmat(arr_poपूर्णांकs[1].y, &fmt,
					    &arr_poपूर्णांकs[1].custom_भग्न_y)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	अगर (!convert_to_custom_भग्न_क्रमmat(arr_poपूर्णांकs[1].slope, &fmt,
					    &arr_poपूर्णांकs[1].custom_भग्न_slope)) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	fmt.mantissa_bits = 12;
	fmt.sign = true;

	जबतक (i != hw_poपूर्णांकs_num) अणु
		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->red, &fmt,
						    &rgb->red_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->green, &fmt,
						    &rgb->green_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->blue, &fmt,
						    &rgb->blue_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->delta_red, &fmt,
						    &rgb->delta_red_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->delta_green, &fmt,
						    &rgb->delta_green_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		अगर (!convert_to_custom_भग्न_क्रमmat(rgb->delta_blue, &fmt,
						    &rgb->delta_blue_reg)) अणु
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण

		++rgb;
		++i;
	पूर्ण

	वापस true;
पूर्ण

#घोषणा MAX_LOW_POINT      25
#घोषणा NUMBER_REGIONS     16
#घोषणा NUMBER_SW_SEGMENTS 16

अटल bool
dce110_translate_regamma_to_hw_क्रमmat(स्थिर काष्ठा dc_transfer_func *output_tf,
				      काष्ठा pwl_params *regamma_params)
अणु
	काष्ठा curve_poपूर्णांकs *arr_poपूर्णांकs;
	काष्ठा pwl_result_data *rgb_resulted;
	काष्ठा pwl_result_data *rgb;
	काष्ठा pwl_result_data *rgb_plus_1;
	काष्ठा fixed31_32 y_r;
	काष्ठा fixed31_32 y_g;
	काष्ठा fixed31_32 y_b;
	काष्ठा fixed31_32 y1_min;
	काष्ठा fixed31_32 y3_max;

	पूर्णांक32_t region_start, region_end;
	uपूर्णांक32_t i, j, k, seg_distr[NUMBER_REGIONS], increment, start_index, hw_poपूर्णांकs;

	अगर (output_tf == शून्य || regamma_params == शून्य || output_tf->type == TF_TYPE_BYPASS)
		वापस false;

	arr_poपूर्णांकs = regamma_params->arr_poपूर्णांकs;
	rgb_resulted = regamma_params->rgb_resulted;
	hw_poपूर्णांकs = 0;

	स_रखो(regamma_params, 0, माप(काष्ठा pwl_params));

	अगर (output_tf->tf == TRANSFER_FUNCTION_PQ) अणु
		/* 16 segments
		 * segments are from 2^-11 to 2^5
		 */
		region_start = -11;
		region_end = region_start + NUMBER_REGIONS;

		क्रम (i = 0; i < NUMBER_REGIONS; i++)
			seg_distr[i] = 4;

	पूर्ण अन्यथा अणु
		/* 10 segments
		 * segment is from 2^-10 to 2^1
		 * We include an extra segment क्रम range [2^0, 2^1). This is to
		 * ensure that colors with normalized values of 1 करोn't miss the
		 * LUT.
		 */
		region_start = -10;
		region_end = 1;

		seg_distr[0] = 4;
		seg_distr[1] = 4;
		seg_distr[2] = 4;
		seg_distr[3] = 4;
		seg_distr[4] = 4;
		seg_distr[5] = 4;
		seg_distr[6] = 4;
		seg_distr[7] = 4;
		seg_distr[8] = 4;
		seg_distr[9] = 4;
		seg_distr[10] = 0;
		seg_distr[11] = -1;
		seg_distr[12] = -1;
		seg_distr[13] = -1;
		seg_distr[14] = -1;
		seg_distr[15] = -1;
	पूर्ण

	क्रम (k = 0; k < 16; k++) अणु
		अगर (seg_distr[k] != -1)
			hw_poपूर्णांकs += (1 << seg_distr[k]);
	पूर्ण

	j = 0;
	क्रम (k = 0; k < (region_end - region_start); k++) अणु
		increment = NUMBER_SW_SEGMENTS / (1 << seg_distr[k]);
		start_index = (region_start + k + MAX_LOW_POINT) *
				NUMBER_SW_SEGMENTS;
		क्रम (i = start_index; i < start_index + NUMBER_SW_SEGMENTS;
				i += increment) अणु
			अगर (j == hw_poपूर्णांकs - 1)
				अवरोध;
			rgb_resulted[j].red = output_tf->tf_pts.red[i];
			rgb_resulted[j].green = output_tf->tf_pts.green[i];
			rgb_resulted[j].blue = output_tf->tf_pts.blue[i];
			j++;
		पूर्ण
	पूर्ण

	/* last poपूर्णांक */
	start_index = (region_end + MAX_LOW_POINT) * NUMBER_SW_SEGMENTS;
	rgb_resulted[hw_poपूर्णांकs - 1].red = output_tf->tf_pts.red[start_index];
	rgb_resulted[hw_poपूर्णांकs - 1].green = output_tf->tf_pts.green[start_index];
	rgb_resulted[hw_poपूर्णांकs - 1].blue = output_tf->tf_pts.blue[start_index];

	arr_poपूर्णांकs[0].x = dc_fixpt_घात(dc_fixpt_from_पूर्णांक(2),
					     dc_fixpt_from_पूर्णांक(region_start));
	arr_poपूर्णांकs[1].x = dc_fixpt_घात(dc_fixpt_from_पूर्णांक(2),
					     dc_fixpt_from_पूर्णांक(region_end));

	y_r = rgb_resulted[0].red;
	y_g = rgb_resulted[0].green;
	y_b = rgb_resulted[0].blue;

	y1_min = dc_fixpt_min(y_r, dc_fixpt_min(y_g, y_b));

	arr_poपूर्णांकs[0].y = y1_min;
	arr_poपूर्णांकs[0].slope = dc_fixpt_भाग(arr_poपूर्णांकs[0].y,
						 arr_poपूर्णांकs[0].x);

	y_r = rgb_resulted[hw_poपूर्णांकs - 1].red;
	y_g = rgb_resulted[hw_poपूर्णांकs - 1].green;
	y_b = rgb_resulted[hw_poपूर्णांकs - 1].blue;

	/* see comment above, m_arrPoपूर्णांकs[1].y should be the Y value क्रम the
	 * region end (m_numOfHwPoपूर्णांकs), not last HW poपूर्णांक(m_numOfHwPoपूर्णांकs - 1)
	 */
	y3_max = dc_fixpt_max(y_r, dc_fixpt_max(y_g, y_b));

	arr_poपूर्णांकs[1].y = y3_max;

	arr_poपूर्णांकs[1].slope = dc_fixpt_zero;

	अगर (output_tf->tf == TRANSFER_FUNCTION_PQ) अणु
		/* क्रम PQ, we want to have a straight line from last HW X poपूर्णांक,
		 * and the slope to be such that we hit 1.0 at 10000 nits.
		 */
		स्थिर काष्ठा fixed31_32 end_value = dc_fixpt_from_पूर्णांक(125);

		arr_poपूर्णांकs[1].slope = dc_fixpt_भाग(
				dc_fixpt_sub(dc_fixpt_one, arr_poपूर्णांकs[1].y),
				dc_fixpt_sub(end_value, arr_poपूर्णांकs[1].x));
	पूर्ण

	regamma_params->hw_poपूर्णांकs_num = hw_poपूर्णांकs;

	k = 0;
	क्रम (i = 1; i < 16; i++) अणु
		अगर (seg_distr[k] != -1) अणु
			regamma_params->arr_curve_poपूर्णांकs[k].segments_num = seg_distr[k];
			regamma_params->arr_curve_poपूर्णांकs[i].offset =
					regamma_params->arr_curve_poपूर्णांकs[k].offset + (1 << seg_distr[k]);
		पूर्ण
		k++;
	पूर्ण

	अगर (seg_distr[k] != -1)
		regamma_params->arr_curve_poपूर्णांकs[k].segments_num = seg_distr[k];

	rgb = rgb_resulted;
	rgb_plus_1 = rgb_resulted + 1;

	i = 1;

	जबतक (i != hw_poपूर्णांकs + 1) अणु
		अगर (dc_fixpt_lt(rgb_plus_1->red, rgb->red))
			rgb_plus_1->red = rgb->red;
		अगर (dc_fixpt_lt(rgb_plus_1->green, rgb->green))
			rgb_plus_1->green = rgb->green;
		अगर (dc_fixpt_lt(rgb_plus_1->blue, rgb->blue))
			rgb_plus_1->blue = rgb->blue;

		rgb->delta_red = dc_fixpt_sub(rgb_plus_1->red, rgb->red);
		rgb->delta_green = dc_fixpt_sub(rgb_plus_1->green, rgb->green);
		rgb->delta_blue = dc_fixpt_sub(rgb_plus_1->blue, rgb->blue);

		++rgb_plus_1;
		++rgb;
		++i;
	पूर्ण

	convert_to_custom_भग्न(rgb_resulted, arr_poपूर्णांकs, hw_poपूर्णांकs);

	वापस true;
पूर्ण

अटल bool
dce110_set_output_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_stream_state *stream)
अणु
	काष्ठा transक्रमm *xfm = pipe_ctx->plane_res.xfm;

	xfm->funcs->opp_घातer_on_regamma_lut(xfm, true);
	xfm->regamma_params.hw_poपूर्णांकs_num = GAMMA_HW_POINTS_NUM;

	अगर (stream->out_transfer_func &&
	    stream->out_transfer_func->type == TF_TYPE_PREDEFINED &&
	    stream->out_transfer_func->tf == TRANSFER_FUNCTION_SRGB) अणु
		xfm->funcs->opp_set_regamma_mode(xfm, OPP_REGAMMA_SRGB);
	पूर्ण अन्यथा अगर (dce110_translate_regamma_to_hw_क्रमmat(stream->out_transfer_func,
							 &xfm->regamma_params)) अणु
		xfm->funcs->opp_program_regamma_pwl(xfm, &xfm->regamma_params);
		xfm->funcs->opp_set_regamma_mode(xfm, OPP_REGAMMA_USER);
	पूर्ण अन्यथा अणु
		xfm->funcs->opp_set_regamma_mode(xfm, OPP_REGAMMA_BYPASS);
	पूर्ण

	xfm->funcs->opp_घातer_on_regamma_lut(xfm, false);

	वापस true;
पूर्ण

व्योम dce110_update_info_frame(काष्ठा pipe_ctx *pipe_ctx)
अणु
	bool is_hdmi_पंचांगds;
	bool is_dp;

	ASSERT(pipe_ctx->stream);

	अगर (pipe_ctx->stream_res.stream_enc == शून्य)
		वापस;  /* this is not root pipe */

	is_hdmi_पंचांगds = dc_is_hdmi_पंचांगds_संकेत(pipe_ctx->stream->संकेत);
	is_dp = dc_is_dp_संकेत(pipe_ctx->stream->संकेत);

	अगर (!is_hdmi_पंचांगds && !is_dp)
		वापस;

	अगर (is_hdmi_पंचांगds)
		pipe_ctx->stream_res.stream_enc->funcs->update_hdmi_info_packets(
			pipe_ctx->stream_res.stream_enc,
			&pipe_ctx->stream_res.encoder_info_frame);
	अन्यथा
		pipe_ctx->stream_res.stream_enc->funcs->update_dp_info_packets(
			pipe_ctx->stream_res.stream_enc,
			&pipe_ctx->stream_res.encoder_info_frame);
पूर्ण

व्योम dce110_enable_stream(काष्ठा pipe_ctx *pipe_ctx)
अणु
	क्रमागत dc_lane_count lane_count =
		pipe_ctx->stream->link->cur_link_settings.lane_count;
	काष्ठा dc_crtc_timing *timing = &pipe_ctx->stream->timing;
	काष्ठा dc_link *link = pipe_ctx->stream->link;
	स्थिर काष्ठा dc *dc = link->dc;

	uपूर्णांक32_t active_total_with_borders;
	uपूर्णांक32_t early_control = 0;
	काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;

	/* For MST, there are multiply stream go to only one link.
	 * connect DIG back_end to front_end जबतक enable_stream and
	 * disconnect them during disable_stream
	 * BY this, it is logic clean to separate stream and link */
	link->link_enc->funcs->connect_dig_be_to_fe(link->link_enc,
						    pipe_ctx->stream_res.stream_enc->id, true);

	dc->hwss.update_info_frame(pipe_ctx);

	/* enable early control to aव्योम corruption on DP monitor*/
	active_total_with_borders =
			timing->h_addressable
				+ timing->h_border_left
				+ timing->h_border_right;

	अगर (lane_count != 0)
		early_control = active_total_with_borders % lane_count;

	अगर (early_control == 0)
		early_control = lane_count;

	tg->funcs->set_early_control(tg, early_control);

	/* enable audio only within mode set */
	अगर (pipe_ctx->stream_res.audio != शून्य) अणु
		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_enable(pipe_ctx->stream_res.stream_enc);
	पूर्ण




पूर्ण

अटल क्रमागत bp_result link_transmitter_control(
		काष्ठा dc_bios *bios,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result;

	result = bios->funcs->transmitter_control(bios, cntl);

	वापस result;
पूर्ण

/*
 * @brief
 * eDP only.
 */
व्योम dce110_edp_रुको_क्रम_hpd_पढ़ोy(
		काष्ठा dc_link *link,
		bool घातer_up)
अणु
	काष्ठा dc_context *ctx = link->ctx;
	काष्ठा graphics_object_id connector = link->link_enc->connector;
	काष्ठा gpio *hpd;
	काष्ठा dc_sink *sink = link->local_sink;
	bool edp_hpd_high = false;
	uपूर्णांक32_t समय_elapsed = 0;
	uपूर्णांक32_t समयout = घातer_up ?
		PANEL_POWER_UP_TIMEOUT : PANEL_POWER_DOWN_TIMEOUT;

	अगर (dal_graphics_object_id_get_connector_id(connector)
			!= CONNECTOR_ID_EDP) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	अगर (!घातer_up)
		/*
		 * From KV, we will not HPD low after turning off VCC -
		 * instead, we will check the SW समयr in घातer_up().
		 */
		वापस;

	/*
	 * When we घातer on/off the eDP panel,
	 * we need to रुको until SENSE bit is high/low.
	 */

	/* obtain HPD */
	/* TODO what to करो with this? */
	hpd = get_hpd_gpio(ctx->dc_bios, connector, ctx->gpio_service);

	अगर (!hpd) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	अगर (sink != शून्य) अणु
		अगर (sink->edid_caps.panel_patch.extra_t3_ms > 0) अणु
			पूर्णांक extra_t3_in_ms = sink->edid_caps.panel_patch.extra_t3_ms;

			msleep(extra_t3_in_ms);
		पूर्ण
	पूर्ण

	dal_gpio_खोलो(hpd, GPIO_MODE_INTERRUPT);

	/* रुको until समयout or panel detected */

	करो अणु
		uपूर्णांक32_t detected = 0;

		dal_gpio_get_value(hpd, &detected);

		अगर (!(detected ^ घातer_up)) अणु
			edp_hpd_high = true;
			अवरोध;
		पूर्ण

		msleep(HPD_CHECK_INTERVAL);

		समय_elapsed += HPD_CHECK_INTERVAL;
	पूर्ण जबतक (समय_elapsed < समयout);

	dal_gpio_बंद(hpd);

	dal_gpio_destroy_irq(&hpd);

	अगर (false == edp_hpd_high) अणु
		DC_LOG_ERROR(
				"%s: wait timed out!\n", __func__);
	पूर्ण
पूर्ण

व्योम dce110_edp_घातer_control(
		काष्ठा dc_link *link,
		bool घातer_up)
अणु
	काष्ठा dc_context *ctx = link->ctx;
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;
	क्रमागत bp_result bp_result;
	uपूर्णांक8_t panel_instance;


	अगर (dal_graphics_object_id_get_connector_id(link->link_enc->connector)
			!= CONNECTOR_ID_EDP) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	अगर (!link->panel_cntl)
		वापस;
	अगर (घातer_up !=
		link->panel_cntl->funcs->is_panel_घातered_on(link->panel_cntl)) अणु

		अचिन्हित दीर्घ दीर्घ current_ts = dm_get_बारtamp(ctx);
		अचिन्हित दीर्घ दीर्घ समय_since_edp_घातeroff_ms =
				भाग64_u64(dm_get_elapse_समय_in_ns(
						ctx,
						current_ts,
						link->link_trace.समय_stamp.edp_घातeroff), 1000000);
		अचिन्हित दीर्घ दीर्घ समय_since_edp_घातeron_ms =
				भाग64_u64(dm_get_elapse_समय_in_ns(
						ctx,
						current_ts,
						link->link_trace.समय_stamp.edp_घातeron), 1000000);
		DC_LOG_HW_RESUME_S3(
				"%s: transition: power_up=%d current_ts=%llu edp_poweroff=%llu edp_poweron=%llu time_since_edp_poweroff_ms=%llu time_since_edp_poweron_ms=%llu",
				__func__,
				घातer_up,
				current_ts,
				link->link_trace.समय_stamp.edp_घातeroff,
				link->link_trace.समय_stamp.edp_घातeron,
				समय_since_edp_घातeroff_ms,
				समय_since_edp_घातeron_ms);

		/* Send VBIOS command to prompt eDP panel घातer */
		अगर (घातer_up) अणु
			/* edp requires a min of 500ms from LCDVDD off to on */
			अचिन्हित दीर्घ दीर्घ reमुख्यing_min_edp_घातeroff_समय_ms = 500;

			/* add समय defined by a patch, अगर any (usually patch extra_t12_ms is 0) */
			अगर (link->local_sink != शून्य)
				reमुख्यing_min_edp_घातeroff_समय_ms +=
					link->local_sink->edid_caps.panel_patch.extra_t12_ms;

			/* Adjust reमुख्यing_min_edp_घातeroff_समय_ms अगर this is not the first समय. */
			अगर (link->link_trace.समय_stamp.edp_घातeroff != 0) अणु
				अगर (समय_since_edp_घातeroff_ms < reमुख्यing_min_edp_घातeroff_समय_ms)
					reमुख्यing_min_edp_घातeroff_समय_ms =
						reमुख्यing_min_edp_घातeroff_समय_ms - समय_since_edp_घातeroff_ms;
				अन्यथा
					reमुख्यing_min_edp_घातeroff_समय_ms = 0;
			पूर्ण

			अगर (reमुख्यing_min_edp_घातeroff_समय_ms) अणु
				DC_LOG_HW_RESUME_S3(
						"%s: remaining_min_edp_poweroff_time_ms=%llu: begin wait.\n",
						__func__, reमुख्यing_min_edp_घातeroff_समय_ms);
				msleep(reमुख्यing_min_edp_घातeroff_समय_ms);
				DC_LOG_HW_RESUME_S3(
						"%s: remaining_min_edp_poweroff_time_ms=%llu: end wait.\n",
						__func__, reमुख्यing_min_edp_घातeroff_समय_ms);
				dm_output_to_console("%s: wait %lld ms to power on eDP.\n",
						__func__, reमुख्यing_min_edp_घातeroff_समय_ms);
			पूर्ण अन्यथा अणु
				DC_LOG_HW_RESUME_S3(
						"%s: remaining_min_edp_poweroff_time_ms=%llu: no wait required.\n",
						__func__, reमुख्यing_min_edp_घातeroff_समय_ms);
			पूर्ण
		पूर्ण

		DC_LOG_HW_RESUME_S3(
				"%s: BEGIN: Panel Power action: %s\n",
				__func__, (घातer_up ? "On":"Off"));

		cntl.action = घातer_up ?
			TRANSMITTER_CONTROL_POWER_ON :
			TRANSMITTER_CONTROL_POWER_OFF;
		cntl.transmitter = link->link_enc->transmitter;
		cntl.connector_obj_id = link->link_enc->connector;
		cntl.coherent = false;
		cntl.lanes_number = LANE_COUNT_FOUR;
		cntl.hpd_sel = link->link_enc->hpd_source;
		panel_instance = link->panel_cntl->inst;

		अगर (ctx->dc->ctx->dmub_srv &&
				ctx->dc->debug.dmub_command_table) अणु
			अगर (cntl.action == TRANSMITTER_CONTROL_POWER_ON)
				bp_result = ctx->dc_bios->funcs->enable_lvपंचांगa_control(ctx->dc_bios,
						LVTMA_CONTROL_POWER_ON,
						panel_instance);
			अन्यथा
				bp_result = ctx->dc_bios->funcs->enable_lvपंचांगa_control(ctx->dc_bios,
						LVTMA_CONTROL_POWER_OFF,
						panel_instance);
		पूर्ण

		bp_result = link_transmitter_control(ctx->dc_bios, &cntl);

		DC_LOG_HW_RESUME_S3(
				"%s: END: Panel Power action: %s bp_result=%u\n",
				__func__, (घातer_up ? "On":"Off"),
				bp_result);

		अगर (!घातer_up)
			/*save driver घातer off समय stamp*/
			link->link_trace.समय_stamp.edp_घातeroff = dm_get_बारtamp(ctx);
		अन्यथा
			link->link_trace.समय_stamp.edp_घातeron = dm_get_बारtamp(ctx);

		DC_LOG_HW_RESUME_S3(
				"%s: updated values: edp_poweroff=%llu edp_poweron=%llu\n",
				__func__,
				link->link_trace.समय_stamp.edp_घातeroff,
				link->link_trace.समय_stamp.edp_घातeron);

		अगर (bp_result != BP_RESULT_OK)
			DC_LOG_ERROR(
					"%s: Panel Power bp_result: %d\n",
					__func__, bp_result);
	पूर्ण अन्यथा अणु
		DC_LOG_HW_RESUME_S3(
				"%s: Skipping Panel Power action: %s\n",
				__func__, (घातer_up ? "On":"Off"));
	पूर्ण
पूर्ण

व्योम dce110_edp_रुको_क्रम_T12(
		काष्ठा dc_link *link)
अणु
	काष्ठा dc_context *ctx = link->ctx;

	अगर (dal_graphics_object_id_get_connector_id(link->link_enc->connector)
			!= CONNECTOR_ID_EDP) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	अगर (!link->panel_cntl)
		वापस;

	अगर (!link->panel_cntl->funcs->is_panel_घातered_on(link->panel_cntl) &&
			link->link_trace.समय_stamp.edp_घातeroff != 0) अणु
		अचिन्हित पूर्णांक t12_duration = 500; // Default T12 as per spec
		अचिन्हित दीर्घ दीर्घ current_ts = dm_get_बारtamp(ctx);
		अचिन्हित दीर्घ दीर्घ समय_since_edp_घातeroff_ms =
				भाग64_u64(dm_get_elapse_समय_in_ns(
						ctx,
						current_ts,
						link->link_trace.समय_stamp.edp_घातeroff), 1000000);

		t12_duration += link->local_sink->edid_caps.panel_patch.extra_t12_ms; // Add extra T12

		अगर (समय_since_edp_घातeroff_ms < t12_duration)
			msleep(t12_duration - समय_since_edp_घातeroff_ms);
	पूर्ण
पूर्ण

/*toकरो: cloned in stream enc, fix*/
/*
 * @brief
 * eDP only. Control the backlight of the eDP panel
 */
व्योम dce110_edp_backlight_control(
		काष्ठा dc_link *link,
		bool enable)
अणु
	काष्ठा dc_context *ctx = link->ctx;
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;
	uपूर्णांक8_t panel_instance;

	अगर (dal_graphics_object_id_get_connector_id(link->link_enc->connector)
		!= CONNECTOR_ID_EDP) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	अगर (link->panel_cntl) अणु
		bool is_backlight_on = link->panel_cntl->funcs->is_panel_backlight_on(link->panel_cntl);

		अगर ((enable && is_backlight_on) || (!enable && !is_backlight_on)) अणु
			DC_LOG_HW_RESUME_S3(
				"%s: panel already powered up/off. Do nothing.\n",
				__func__);
			वापस;
		पूर्ण
	पूर्ण

	/* Send VBIOS command to control eDP panel backlight */

	DC_LOG_HW_RESUME_S3(
			"%s: backlight action: %s\n",
			__func__, (enable ? "On":"Off"));

	cntl.action = enable ?
		TRANSMITTER_CONTROL_BACKLIGHT_ON :
		TRANSMITTER_CONTROL_BACKLIGHT_OFF;

	/*cntl.engine_id = ctx->engine;*/
	cntl.transmitter = link->link_enc->transmitter;
	cntl.connector_obj_id = link->link_enc->connector;
	/*toकरो: unhardcode*/
	cntl.lanes_number = LANE_COUNT_FOUR;
	cntl.hpd_sel = link->link_enc->hpd_source;
	cntl.संकेत = SIGNAL_TYPE_EDP;

	/* For eDP, the following delays might need to be considered
	 * after link training completed:
	 * idle period - min. accounts क्रम required BS-Idle pattern,
	 * max. allows क्रम source frame synchronization);
	 * 50 msec max. delay from valid video data from source
	 * to video on dislpay or backlight enable.
	 *
	 * Disable the delay क्रम now.
	 * Enable it in the future अगर necessary.
	 */
	/* dc_service_sleep_in_milliseconds(50); */
		/*edp 1.2*/
	panel_instance = link->panel_cntl->inst;
	अगर (cntl.action == TRANSMITTER_CONTROL_BACKLIGHT_ON)
		edp_receiver_पढ़ोy_T7(link);

	अगर (ctx->dc->ctx->dmub_srv &&
			ctx->dc->debug.dmub_command_table) अणु
		अगर (cntl.action == TRANSMITTER_CONTROL_BACKLIGHT_ON)
			ctx->dc_bios->funcs->enable_lvपंचांगa_control(ctx->dc_bios,
					LVTMA_CONTROL_LCD_BLON,
					panel_instance);
		अन्यथा
			ctx->dc_bios->funcs->enable_lvपंचांगa_control(ctx->dc_bios,
					LVTMA_CONTROL_LCD_BLOFF,
					panel_instance);
	पूर्ण

	link_transmitter_control(ctx->dc_bios, &cntl);

	अगर (enable && link->dpcd_sink_ext_caps.bits.oled)
		msleep(OLED_POST_T7_DELAY);

	अगर (link->dpcd_sink_ext_caps.bits.oled ||
		link->dpcd_sink_ext_caps.bits.hdr_aux_backlight_control == 1 ||
		link->dpcd_sink_ext_caps.bits.sdr_aux_backlight_control == 1)
		dc_link_backlight_enable_aux(link, enable);

	/*edp 1.2*/
	अगर (cntl.action == TRANSMITTER_CONTROL_BACKLIGHT_OFF)
		edp_add_delay_क्रम_T9(link);

	अगर (!enable && link->dpcd_sink_ext_caps.bits.oled)
		msleep(OLED_PRE_T11_DELAY);
पूर्ण

व्योम dce110_enable_audio_stream(काष्ठा pipe_ctx *pipe_ctx)
अणु
	/* notअगरy audio driver क्रम audio modes of monitor */
	काष्ठा dc *dc;
	काष्ठा clk_mgr *clk_mgr;
	अचिन्हित पूर्णांक i, num_audio = 1;

	अगर (!pipe_ctx->stream)
		वापस;

	dc = pipe_ctx->stream->ctx->dc;
	clk_mgr = dc->clk_mgr;

	अगर (pipe_ctx->stream_res.audio && pipe_ctx->stream_res.audio->enabled == true)
		वापस;

	अगर (pipe_ctx->stream_res.audio) अणु
		क्रम (i = 0; i < MAX_PIPES; i++) अणु
			/*current_state not updated yet*/
			अगर (dc->current_state->res_ctx.pipe_ctx[i].stream_res.audio != शून्य)
				num_audio++;
		पूर्ण

		pipe_ctx->stream_res.audio->funcs->az_enable(pipe_ctx->stream_res.audio);

		अगर (num_audio >= 1 && clk_mgr->funcs->enable_pme_wa)
			/*this is the first audio. apply the PME w/a in order to wake AZ from D3*/
			clk_mgr->funcs->enable_pme_wa(clk_mgr);
		/* un-mute audio */
		/* TODO: audio should be per stream rather than per link */
		pipe_ctx->stream_res.stream_enc->funcs->audio_mute_control(
					pipe_ctx->stream_res.stream_enc, false);
		अगर (pipe_ctx->stream_res.audio)
			pipe_ctx->stream_res.audio->enabled = true;
	पूर्ण
पूर्ण

व्योम dce110_disable_audio_stream(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc *dc;
	काष्ठा clk_mgr *clk_mgr;

	अगर (!pipe_ctx || !pipe_ctx->stream)
		वापस;

	dc = pipe_ctx->stream->ctx->dc;
	clk_mgr = dc->clk_mgr;

	अगर (pipe_ctx->stream_res.audio && pipe_ctx->stream_res.audio->enabled == false)
		वापस;

	pipe_ctx->stream_res.stream_enc->funcs->audio_mute_control(
			pipe_ctx->stream_res.stream_enc, true);
	अगर (pipe_ctx->stream_res.audio) अणु
		pipe_ctx->stream_res.audio->enabled = false;

		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_disable(
					pipe_ctx->stream_res.stream_enc);
		अन्यथा
			pipe_ctx->stream_res.stream_enc->funcs->hdmi_audio_disable(
					pipe_ctx->stream_res.stream_enc);

		अगर (clk_mgr->funcs->enable_pme_wa)
			/*this is the first audio. apply the PME w/a in order to wake AZ from D3*/
			clk_mgr->funcs->enable_pme_wa(clk_mgr);

		/* TODO: notअगरy audio driver क्रम अगर audio modes list changed
		 * add audio mode list change flag */
		/* dal_audio_disable_azalia_audio_jack_presence(stream->audio,
		 * stream->stream_engine_id);
		 */
	पूर्ण
पूर्ण

व्योम dce110_disable_stream(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	काष्ठा dc *dc = pipe_ctx->stream->ctx->dc;

	अगर (dc_is_hdmi_पंचांगds_संकेत(pipe_ctx->stream->संकेत)) अणु
		pipe_ctx->stream_res.stream_enc->funcs->stop_hdmi_info_packets(
			pipe_ctx->stream_res.stream_enc);
		pipe_ctx->stream_res.stream_enc->funcs->hdmi_reset_stream_attribute(
			pipe_ctx->stream_res.stream_enc);
	पूर्ण

	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
		pipe_ctx->stream_res.stream_enc->funcs->stop_dp_info_packets(
			pipe_ctx->stream_res.stream_enc);

	dc->hwss.disable_audio_stream(pipe_ctx);

	link->link_enc->funcs->connect_dig_be_to_fe(
			link->link_enc,
			pipe_ctx->stream_res.stream_enc->id,
			false);

पूर्ण

व्योम dce110_unblank_stream(काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_link_settings *link_settings)
अणु
	काष्ठा encoder_unblank_param params = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	काष्ठा dce_hwseq *hws = link->dc->hwseq;

	/* only 3 items below are used by unblank */
	params.timing = pipe_ctx->stream->timing;
	params.link_settings.link_rate = link_settings->link_rate;

	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
		pipe_ctx->stream_res.stream_enc->funcs->dp_unblank(pipe_ctx->stream_res.stream_enc, &params);

	अगर (link->local_sink && link->local_sink->sink_संकेत == SIGNAL_TYPE_EDP) अणु
		hws->funcs.edp_backlight_control(link, true);
	पूर्ण
पूर्ण

व्योम dce110_blank_stream(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	काष्ठा dce_hwseq *hws = link->dc->hwseq;

	अगर (link->local_sink && link->local_sink->sink_संकेत == SIGNAL_TYPE_EDP) अणु
		hws->funcs.edp_backlight_control(link, false);
		link->dc->hwss.set_abm_immediate_disable(pipe_ctx);
	पूर्ण

	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत)) अणु
		pipe_ctx->stream_res.stream_enc->funcs->dp_blank(pipe_ctx->stream_res.stream_enc);

		अगर (!dc_is_embedded_संकेत(pipe_ctx->stream->संकेत)) अणु
			/*
			 * After output is idle pattern some sinks need समय to recognize the stream
			 * has changed or they enter protection state and hang.
			 */
			msleep(60);
		पूर्ण अन्यथा अगर (pipe_ctx->stream->संकेत == SIGNAL_TYPE_EDP)
			edp_receiver_पढ़ोy_T9(link);
	पूर्ण

पूर्ण


व्योम dce110_set_avmute(काष्ठा pipe_ctx *pipe_ctx, bool enable)
अणु
	अगर (pipe_ctx != शून्य && pipe_ctx->stream_res.stream_enc != शून्य)
		pipe_ctx->stream_res.stream_enc->funcs->set_avmute(pipe_ctx->stream_res.stream_enc, enable);
पूर्ण

अटल क्रमागत audio_dto_source translate_to_dto_source(क्रमागत controller_id crtc_id)
अणु
	चयन (crtc_id) अणु
	हाल CONTROLLER_ID_D0:
		वापस DTO_SOURCE_ID0;
	हाल CONTROLLER_ID_D1:
		वापस DTO_SOURCE_ID1;
	हाल CONTROLLER_ID_D2:
		वापस DTO_SOURCE_ID2;
	हाल CONTROLLER_ID_D3:
		वापस DTO_SOURCE_ID3;
	हाल CONTROLLER_ID_D4:
		वापस DTO_SOURCE_ID4;
	हाल CONTROLLER_ID_D5:
		वापस DTO_SOURCE_ID5;
	शेष:
		वापस DTO_SOURCE_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम build_audio_output(
	काष्ठा dc_state *state,
	स्थिर काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा audio_output *audio_output)
अणु
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	audio_output->engine_id = pipe_ctx->stream_res.stream_enc->id;

	audio_output->संकेत = pipe_ctx->stream->संकेत;

	/* audio_crtc_info  */

	audio_output->crtc_info.h_total =
		stream->timing.h_total;

	/*
	 * Audio packets are sent during actual CRTC blank physical संकेत, we
	 * need to specअगरy actual active संकेत portion
	 */
	audio_output->crtc_info.h_active =
			stream->timing.h_addressable
			+ stream->timing.h_border_left
			+ stream->timing.h_border_right;

	audio_output->crtc_info.v_active =
			stream->timing.v_addressable
			+ stream->timing.v_border_top
			+ stream->timing.v_border_bottom;

	audio_output->crtc_info.pixel_repetition = 1;

	audio_output->crtc_info.पूर्णांकerlaced =
			stream->timing.flags.INTERLACE;

	audio_output->crtc_info.refresh_rate =
		(stream->timing.pix_clk_100hz*100)/
		(stream->timing.h_total*stream->timing.v_total);

	audio_output->crtc_info.color_depth =
		stream->timing.display_color_depth;

	audio_output->crtc_info.requested_pixel_घड़ी_100Hz =
			pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz;

	audio_output->crtc_info.calculated_pixel_घड़ी_100Hz =
			pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz;

/*क्रम HDMI, audio ACR is with deep color ratio factor*/
	अगर (dc_is_hdmi_पंचांगds_संकेत(pipe_ctx->stream->संकेत) &&
		audio_output->crtc_info.requested_pixel_घड़ी_100Hz ==
				(stream->timing.pix_clk_100hz)) अणु
		अगर (pipe_ctx->stream_res.pix_clk_params.pixel_encoding == PIXEL_ENCODING_YCBCR420) अणु
			audio_output->crtc_info.requested_pixel_घड़ी_100Hz =
					audio_output->crtc_info.requested_pixel_घड़ी_100Hz/2;
			audio_output->crtc_info.calculated_pixel_घड़ी_100Hz =
					pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz/2;

		पूर्ण
	पूर्ण

	अगर (state->clk_mgr &&
		(pipe_ctx->stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT ||
			pipe_ctx->stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST)) अणु
		audio_output->pll_info.dp_dto_source_घड़ी_in_khz =
				state->clk_mgr->funcs->get_dp_ref_clk_frequency(
						state->clk_mgr);
	पूर्ण

	audio_output->pll_info.feed_back_भागider =
			pipe_ctx->pll_settings.feedback_भागider;

	audio_output->pll_info.dto_source =
		translate_to_dto_source(
			pipe_ctx->stream_res.tg->inst + 1);

	/* TODO hard code to enable क्रम now. Need get from stream */
	audio_output->pll_info.ss_enabled = true;

	audio_output->pll_info.ss_percentage =
			pipe_ctx->pll_settings.ss_percentage;
पूर्ण

अटल व्योम get_surface_visual_confirm_color(स्थिर काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा tg_color *color)
अणु
	uपूर्णांक32_t color_value = MAX_TG_COLOR_VALUE * (4 - pipe_ctx->stream_res.tg->inst) / 4;

	चयन (pipe_ctx->plane_res.scl_data.क्रमmat) अणु
	हाल PIXEL_FORMAT_ARGB8888:
		/* set boarder color to red */
		color->color_r_cr = color_value;
		अवरोध;

	हाल PIXEL_FORMAT_ARGB2101010:
		/* set boarder color to blue */
		color->color_b_cb = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_420BPP8:
		/* set boarder color to green */
		color->color_g_y = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_420BPP10:
		/* set boarder color to yellow */
		color->color_g_y = color_value;
		color->color_r_cr = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_FP16:
		/* set boarder color to white */
		color->color_r_cr = color_value;
		color->color_b_cb = color_value;
		color->color_g_y = color_value;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम program_scaler(स्थिर काष्ठा dc *dc,
		स्थिर काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा tg_color color = अणु0पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	/* TOFPGA */
	अगर (pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_pixel_storage_depth == शून्य)
		वापस;
#पूर्ण_अगर

	अगर (dc->debug.visual_confirm == VISUAL_CONFIRM_SURFACE)
		get_surface_visual_confirm_color(pipe_ctx, &color);
	अन्यथा
		color_space_to_black_color(dc,
				pipe_ctx->stream->output_color_space,
				&color);

	pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_pixel_storage_depth(
		pipe_ctx->plane_res.xfm,
		pipe_ctx->plane_res.scl_data.lb_params.depth,
		&pipe_ctx->stream->bit_depth_params);

	अगर (pipe_ctx->stream_res.tg->funcs->set_overscan_blank_color) अणु
		/*
		 * The way 420 is packed, 2 channels carry Y component, 1 channel
		 * alternate between Cb and Cr, so both channels need the pixel
		 * value क्रम Y
		 */
		अगर (pipe_ctx->stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
			color.color_r_cr = color.color_g_y;

		pipe_ctx->stream_res.tg->funcs->set_overscan_blank_color(
				pipe_ctx->stream_res.tg,
				&color);
	पूर्ण

	pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_scaler(pipe_ctx->plane_res.xfm,
		&pipe_ctx->plane_res.scl_data);
पूर्ण

अटल क्रमागत dc_status dce110_enable_stream_timing(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context,
		काष्ठा dc *dc)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा pipe_ctx *pipe_ctx_old = &dc->current_state->res_ctx.
			pipe_ctx[pipe_ctx->pipe_idx];
	काष्ठा tg_color black_color = अणु0पूर्ण;

	अगर (!pipe_ctx_old->stream) अणु

		/* program blank color */
		color_space_to_black_color(dc,
				stream->output_color_space, &black_color);
		pipe_ctx->stream_res.tg->funcs->set_blank_color(
				pipe_ctx->stream_res.tg,
				&black_color);

		/*
		 * Must blank CRTC after disabling घातer gating and beक्रमe any
		 * programming, otherwise CRTC will be hung in bad state
		 */
		pipe_ctx->stream_res.tg->funcs->set_blank(pipe_ctx->stream_res.tg, true);

		अगर (false == pipe_ctx->घड़ी_source->funcs->program_pix_clk(
				pipe_ctx->घड़ी_source,
				&pipe_ctx->stream_res.pix_clk_params,
				&pipe_ctx->pll_settings)) अणु
			BREAK_TO_DEBUGGER();
			वापस DC_ERROR_UNEXPECTED;
		पूर्ण

		pipe_ctx->stream_res.tg->funcs->program_timing(
				pipe_ctx->stream_res.tg,
				&stream->timing,
				0,
				0,
				0,
				0,
				pipe_ctx->stream->संकेत,
				true);
	पूर्ण

	अगर (!pipe_ctx_old->stream) अणु
		अगर (false == pipe_ctx->stream_res.tg->funcs->enable_crtc(
				pipe_ctx->stream_res.tg)) अणु
			BREAK_TO_DEBUGGER();
			वापस DC_ERROR_UNEXPECTED;
		पूर्ण
	पूर्ण

	वापस DC_OK;
पूर्ण

अटल क्रमागत dc_status apply_single_controller_ctx_to_hw(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context,
		काष्ठा dc *dc)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा drr_params params = अणु0पूर्ण;
	अचिन्हित पूर्णांक event_triggers = 0;
	काष्ठा pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	अगर (hws->funcs.disable_stream_gating) अणु
		hws->funcs.disable_stream_gating(dc, pipe_ctx);
	पूर्ण

	अगर (pipe_ctx->stream_res.audio != शून्य) अणु
		काष्ठा audio_output audio_output;

		build_audio_output(context, pipe_ctx, &audio_output);

		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
			pipe_ctx->stream_res.stream_enc->funcs->dp_audio_setup(
					pipe_ctx->stream_res.stream_enc,
					pipe_ctx->stream_res.audio->inst,
					&pipe_ctx->stream->audio_info);
		अन्यथा
			pipe_ctx->stream_res.stream_enc->funcs->hdmi_audio_setup(
					pipe_ctx->stream_res.stream_enc,
					pipe_ctx->stream_res.audio->inst,
					&pipe_ctx->stream->audio_info,
					&audio_output.crtc_info);

		pipe_ctx->stream_res.audio->funcs->az_configure(
				pipe_ctx->stream_res.audio,
				pipe_ctx->stream->संकेत,
				&audio_output.crtc_info,
				&pipe_ctx->stream->audio_info);
	पूर्ण

	/*  */
	/* Do not touch stream timing on seamless boot optimization. */
	अगर (!pipe_ctx->stream->apply_seamless_boot_optimization)
		hws->funcs.enable_stream_timing(pipe_ctx, context, dc);

	अगर (hws->funcs.setup_vupdate_पूर्णांकerrupt)
		hws->funcs.setup_vupdate_पूर्णांकerrupt(dc, pipe_ctx);

	params.vertical_total_min = stream->adjust.v_total_min;
	params.vertical_total_max = stream->adjust.v_total_max;
	अगर (pipe_ctx->stream_res.tg->funcs->set_drr)
		pipe_ctx->stream_res.tg->funcs->set_drr(
			pipe_ctx->stream_res.tg, &params);

	// DRR should set trigger event to monitor surface update event
	अगर (stream->adjust.v_total_min != 0 && stream->adjust.v_total_max != 0)
		event_triggers = 0x80;
	/* Event triggers and num frames initialized क्रम DRR, but can be
	 * later updated क्रम PSR use. Note DRR trigger events are generated
	 * regardless of whether num frames met.
	 */
	अगर (pipe_ctx->stream_res.tg->funcs->set_अटल_screen_control)
		pipe_ctx->stream_res.tg->funcs->set_अटल_screen_control(
				pipe_ctx->stream_res.tg, event_triggers, 2);

	अगर (!dc_is_भव_संकेत(pipe_ctx->stream->संकेत))
		pipe_ctx->stream_res.stream_enc->funcs->dig_connect_to_otg(
			pipe_ctx->stream_res.stream_enc,
			pipe_ctx->stream_res.tg->inst);

	pipe_ctx->stream_res.opp->funcs->opp_set_dyn_expansion(
			pipe_ctx->stream_res.opp,
			COLOR_SPACE_YCBCR601,
			stream->timing.display_color_depth,
			stream->संकेत);

	pipe_ctx->stream_res.opp->funcs->opp_program_fmt(
		pipe_ctx->stream_res.opp,
		&stream->bit_depth_params,
		&stream->clamping);
	जबतक (odm_pipe) अणु
		odm_pipe->stream_res.opp->funcs->opp_set_dyn_expansion(
				odm_pipe->stream_res.opp,
				COLOR_SPACE_YCBCR601,
				stream->timing.display_color_depth,
				stream->संकेत);

		odm_pipe->stream_res.opp->funcs->opp_program_fmt(
				odm_pipe->stream_res.opp,
				&stream->bit_depth_params,
				&stream->clamping);
		odm_pipe = odm_pipe->next_odm_pipe;
	पूर्ण

	अगर (!stream->dpms_off)
		core_link_enable_stream(context, pipe_ctx);

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = pipe_ctx->bottom_pipe != 0;

	pipe_ctx->stream->link->psr_settings.psr_feature_enabled = false;

	वापस DC_OK;
पूर्ण

/******************************************************************************/

अटल व्योम घातer_करोwn_encoders(काष्ठा dc *dc)
अणु
	पूर्णांक i;

	/* करो not know BIOS back-front mapping, simply blank all. It will not
	 * hurt क्रम non-DP
	 */
	क्रम (i = 0; i < dc->res_pool->stream_enc_count; i++) अणु
		dc->res_pool->stream_enc[i]->funcs->dp_blank(
					dc->res_pool->stream_enc[i]);
	पूर्ण

	क्रम (i = 0; i < dc->link_count; i++) अणु
		क्रमागत संकेत_type संकेत = dc->links[i]->connector_संकेत;

		अगर ((संकेत == SIGNAL_TYPE_EDP) ||
			(संकेत == SIGNAL_TYPE_DISPLAY_PORT))
			अगर (!dc->links[i]->wa_flags.dp_keep_receiver_घातered)
				dp_receiver_घातer_ctrl(dc->links[i], false);

		अगर (संकेत != SIGNAL_TYPE_EDP)
			संकेत = SIGNAL_TYPE_NONE;

		dc->links[i]->link_enc->funcs->disable_output(
				dc->links[i]->link_enc, संकेत);

		dc->links[i]->link_status.link_active = false;
		स_रखो(&dc->links[i]->cur_link_settings, 0,
				माप(dc->links[i]->cur_link_settings));
	पूर्ण
पूर्ण

अटल व्योम घातer_करोwn_controllers(काष्ठा dc *dc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dc->res_pool->timing_generator_count; i++) अणु
		dc->res_pool->timing_generators[i]->funcs->disable_crtc(
				dc->res_pool->timing_generators[i]);
	पूर्ण
पूर्ण

अटल व्योम घातer_करोwn_घड़ी_sources(काष्ठा dc *dc)
अणु
	पूर्णांक i;

	अगर (dc->res_pool->dp_घड़ी_source->funcs->cs_घातer_करोwn(
		dc->res_pool->dp_घड़ी_source) == false)
		dm_error("Failed to power down pll! (dp clk src)\n");

	क्रम (i = 0; i < dc->res_pool->clk_src_count; i++) अणु
		अगर (dc->res_pool->घड़ी_sources[i]->funcs->cs_घातer_करोwn(
				dc->res_pool->घड़ी_sources[i]) == false)
			dm_error("Failed to power down pll! (clk src index=%d)\n", i);
	पूर्ण
पूर्ण

अटल व्योम घातer_करोwn_all_hw_blocks(काष्ठा dc *dc)
अणु
	घातer_करोwn_encoders(dc);

	घातer_करोwn_controllers(dc);

	घातer_करोwn_घड़ी_sources(dc);

	अगर (dc->fbc_compressor)
		dc->fbc_compressor->funcs->disable_fbc(dc->fbc_compressor);
पूर्ण

अटल व्योम disable_vga_and_घातer_gate_all_controllers(
		काष्ठा dc *dc)
अणु
	पूर्णांक i;
	काष्ठा timing_generator *tg;
	काष्ठा dc_context *ctx = dc->ctx;

	क्रम (i = 0; i < dc->res_pool->timing_generator_count; i++) अणु
		tg = dc->res_pool->timing_generators[i];

		अगर (tg->funcs->disable_vga)
			tg->funcs->disable_vga(tg);
	पूर्ण
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		/* Enable CLOCK gating क्रम each pipe BEFORE controller
		 * घातergating. */
		enable_display_pipe_घड़ी_gating(ctx,
				true);

		dc->current_state->res_ctx.pipe_ctx[i].pipe_idx = i;
		dc->hwss.disable_plane(dc,
			&dc->current_state->res_ctx.pipe_ctx[i]);
	पूर्ण
पूर्ण


अटल व्योम get_edp_streams(काष्ठा dc_state *context,
		काष्ठा dc_stream_state **edp_streams,
		पूर्णांक *edp_stream_num)
अणु
	पूर्णांक i;

	*edp_stream_num = 0;
	क्रम (i = 0; i < context->stream_count; i++) अणु
		अगर (context->streams[i]->संकेत == SIGNAL_TYPE_EDP) अणु
			edp_streams[*edp_stream_num] = context->streams[i];
			अगर (++(*edp_stream_num) == MAX_NUM_EDP)
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_edp_links_with_sink(
		काष्ठा dc *dc,
		काष्ठा dc_link **edp_links_with_sink,
		पूर्णांक *edp_with_sink_num)
अणु
	पूर्णांक i;

	/* check अगर there is an eDP panel not in use */
	*edp_with_sink_num = 0;
	क्रम (i = 0; i < dc->link_count; i++) अणु
		अगर (dc->links[i]->local_sink &&
			dc->links[i]->local_sink->sink_संकेत == SIGNAL_TYPE_EDP) अणु
			edp_links_with_sink[*edp_with_sink_num] = dc->links[i];
			अगर (++(*edp_with_sink_num) == MAX_NUM_EDP)
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * When ASIC goes from VBIOS/VGA mode to driver/accelerated mode we need:
 *  1. Power करोwn all DC HW blocks
 *  2. Disable VGA engine on all controllers
 *  3. Enable घातer gating क्रम controller
 *  4. Set acc_mode_change bit (VBIOS will clear this bit when going to FSDOS)
 */
व्योम dce110_enable_accelerated_mode(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	काष्ठा dc_link *edp_links_with_sink[MAX_NUM_EDP];
	काष्ठा dc_link *edp_links[MAX_NUM_EDP];
	काष्ठा dc_stream_state *edp_streams[MAX_NUM_EDP];
	काष्ठा dc_link *edp_link_with_sink = शून्य;
	काष्ठा dc_link *edp_link = शून्य;
	काष्ठा dc_stream_state *edp_stream = शून्य;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	पूर्णांक edp_with_sink_num;
	पूर्णांक edp_num;
	पूर्णांक edp_stream_num;
	पूर्णांक i;
	bool can_apply_edp_fast_boot = false;
	bool can_apply_seamless_boot = false;
	bool keep_edp_vdd_on = false;
	DC_LOGGER_INIT();


	get_edp_links_with_sink(dc, edp_links_with_sink, &edp_with_sink_num);
	get_edp_links(dc, edp_links, &edp_num);

	अगर (hws->funcs.init_pipes)
		hws->funcs.init_pipes(dc, context);

	get_edp_streams(context, edp_streams, &edp_stream_num);

	// Check fastboot support, disable on DCE8 because of blank screens
	अगर (edp_num && dc->ctx->dce_version != DCE_VERSION_8_0 &&
		    dc->ctx->dce_version != DCE_VERSION_8_1 &&
		    dc->ctx->dce_version != DCE_VERSION_8_3) अणु
		क्रम (i = 0; i < edp_num; i++) अणु
			edp_link = edp_links[i];
			// enable fastboot अगर backend is enabled on eDP
			अगर (edp_link->link_enc->funcs->is_dig_enabled(edp_link->link_enc)) अणु
				/* Set optimization flag on eDP stream*/
				अगर (edp_stream_num && edp_link->link_status.link_active) अणु
					edp_stream = edp_streams[0];
					can_apply_edp_fast_boot = !is_edp_ilr_optimization_required(edp_stream->link, &edp_stream->timing);
					edp_stream->apply_edp_fast_boot_optimization = can_apply_edp_fast_boot;
					अगर (can_apply_edp_fast_boot)
						DC_LOG_EVENT_LINK_TRAINING("eDP fast boot disabled to optimize link rate\n");

					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		// We are trying to enable eDP, करोn't घातer करोwn VDD
		अगर (edp_stream_num)
			keep_edp_vdd_on = true;
	पूर्ण

	// Check seamless boot support
	क्रम (i = 0; i < context->stream_count; i++) अणु
		अगर (context->streams[i]->apply_seamless_boot_optimization) अणु
			can_apply_seamless_boot = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* eDP should not have stream in resume from S4 and so even with VBios post
	 * it should get turned off
	 */
	अगर (edp_with_sink_num)
		edp_link_with_sink = edp_links_with_sink[0];

	अगर (!can_apply_edp_fast_boot && !can_apply_seamless_boot) अणु
		अगर (edp_link_with_sink && !keep_edp_vdd_on) अणु
			/*turn off backlight beक्रमe DP_blank and encoder घातered करोwn*/
			hws->funcs.edp_backlight_control(edp_link_with_sink, false);
		पूर्ण
		/*resume from S3, no vbios posting, no need to घातer करोwn again*/
		घातer_करोwn_all_hw_blocks(dc);
		disable_vga_and_घातer_gate_all_controllers(dc);
		अगर (edp_link_with_sink && !keep_edp_vdd_on)
			dc->hwss.edp_घातer_control(edp_link_with_sink, false);
	पूर्ण
	bios_set_scratch_acc_mode_change(dc->ctx->dc_bios, 1);
पूर्ण

अटल uपूर्णांक32_t compute_pstate_blackout_duration(
	काष्ठा bw_fixed blackout_duration,
	स्थिर काष्ठा dc_stream_state *stream)
अणु
	uपूर्णांक32_t total_dest_line_समय_ns;
	uपूर्णांक32_t pstate_blackout_duration_ns;

	pstate_blackout_duration_ns = 1000 * blackout_duration.value >> 24;

	total_dest_line_समय_ns = 1000000UL *
		(stream->timing.h_total * 10) /
		stream->timing.pix_clk_100hz +
		pstate_blackout_duration_ns;

	वापस total_dest_line_समय_ns;
पूर्ण

अटल व्योम dce110_set_displaymarks(
	स्थिर काष्ठा dc *dc,
	काष्ठा dc_state *context)
अणु
	uपूर्णांक8_t i, num_pipes;
	अचिन्हित पूर्णांक underlay_idx = dc->res_pool->underlay_pipe_index;

	क्रम (i = 0, num_pipes = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		uपूर्णांक32_t total_dest_line_समय_ns;

		अगर (pipe_ctx->stream == शून्य)
			जारी;

		total_dest_line_समय_ns = compute_pstate_blackout_duration(
			dc->bw_vbios->blackout_duration, pipe_ctx->stream);
		pipe_ctx->plane_res.mi->funcs->mem_input_program_display_marks(
			pipe_ctx->plane_res.mi,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.stutter_निकास_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.stutter_entry_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.urgent_wm_ns[num_pipes],
			total_dest_line_समय_ns);
		अगर (i == underlay_idx) अणु
			num_pipes++;
			pipe_ctx->plane_res.mi->funcs->mem_input_program_chroma_display_marks(
				pipe_ctx->plane_res.mi,
				context->bw_ctx.bw.dce.nbp_state_change_wm_ns[num_pipes],
				context->bw_ctx.bw.dce.stutter_निकास_wm_ns[num_pipes],
				context->bw_ctx.bw.dce.urgent_wm_ns[num_pipes],
				total_dest_line_समय_ns);
		पूर्ण
		num_pipes++;
	पूर्ण
पूर्ण

व्योम dce110_set_safe_displaymarks(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	पूर्णांक underlay_idx = pool->underlay_pipe_index;
	काष्ठा dce_watermarks max_marks = अणु
		MAX_WATERMARK, MAX_WATERMARK, MAX_WATERMARK, MAX_WATERMARK पूर्ण;
	काष्ठा dce_watermarks nbp_marks = अणु
		SAFE_NBP_MARK, SAFE_NBP_MARK, SAFE_NBP_MARK, SAFE_NBP_MARK पूर्ण;
	काष्ठा dce_watermarks min_marks = अणु 0, 0, 0, 0पूर्ण;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (res_ctx->pipe_ctx[i].stream == शून्य || res_ctx->pipe_ctx[i].plane_res.mi == शून्य)
			जारी;

		res_ctx->pipe_ctx[i].plane_res.mi->funcs->mem_input_program_display_marks(
				res_ctx->pipe_ctx[i].plane_res.mi,
				nbp_marks,
				max_marks,
				min_marks,
				max_marks,
				MAX_WATERMARK);

		अगर (i == underlay_idx)
			res_ctx->pipe_ctx[i].plane_res.mi->funcs->mem_input_program_chroma_display_marks(
				res_ctx->pipe_ctx[i].plane_res.mi,
				nbp_marks,
				max_marks,
				max_marks,
				MAX_WATERMARK);

	पूर्ण
पूर्ण

/*******************************************************************************
 * Public functions
 ******************************************************************************/

अटल व्योम set_drr(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes, काष्ठा dc_crtc_timing_adjust adjust)
अणु
	पूर्णांक i = 0;
	काष्ठा drr_params params = अणु0पूर्ण;
	// DRR should set trigger event to monitor surface update event
	अचिन्हित पूर्णांक event_triggers = 0x80;
	// Note DRR trigger events are generated regardless of whether num frames met.
	अचिन्हित पूर्णांक num_frames = 2;

	params.vertical_total_max = adjust.v_total_max;
	params.vertical_total_min = adjust.v_total_min;

	/* TODO: If multiple pipes are to be supported, you need
	 * some GSL stuff. Static screen triggers may be programmed dअगरferently
	 * as well.
	 */
	क्रम (i = 0; i < num_pipes; i++) अणु
		pipe_ctx[i]->stream_res.tg->funcs->set_drr(
			pipe_ctx[i]->stream_res.tg, &params);

		अगर (adjust.v_total_max != 0 && adjust.v_total_min != 0)
			pipe_ctx[i]->stream_res.tg->funcs->set_अटल_screen_control(
					pipe_ctx[i]->stream_res.tg,
					event_triggers, num_frames);
	पूर्ण
पूर्ण

अटल व्योम get_position(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes,
		काष्ठा crtc_position *position)
अणु
	पूर्णांक i = 0;

	/* TODO: handle pipes > 1
	 */
	क्रम (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stream_res.tg->funcs->get_position(pipe_ctx[i]->stream_res.tg, position);
पूर्ण

अटल व्योम set_अटल_screen_control(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes, स्थिर काष्ठा dc_अटल_screen_params *params)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक triggers = 0;

	अगर (params->triggers.overlay_update)
		triggers |= 0x100;
	अगर (params->triggers.surface_update)
		triggers |= 0x80;
	अगर (params->triggers.cursor_update)
		triggers |= 0x2;
	अगर (params->triggers.क्रमce_trigger)
		triggers |= 0x1;

	अगर (num_pipes) अणु
		काष्ठा dc *dc = pipe_ctx[0]->stream->ctx->dc;

		अगर (dc->fbc_compressor)
			triggers |= 0x84;
	पूर्ण

	क्रम (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stream_res.tg->funcs->
			set_अटल_screen_control(pipe_ctx[i]->stream_res.tg,
					triggers, params->num_frames);
पूर्ण

/*
 *  Check अगर FBC can be enabled
 */
अटल bool should_enable_fbc(काष्ठा dc *dc,
		काष्ठा dc_state *context,
		uपूर्णांक32_t *pipe_idx)
अणु
	uपूर्णांक32_t i;
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	काष्ठा resource_context *res_ctx = &context->res_ctx;
	अचिन्हित पूर्णांक underlay_idx = dc->res_pool->underlay_pipe_index;


	ASSERT(dc->fbc_compressor);

	/* FBC memory should be allocated */
	अगर (!dc->ctx->fbc_gpu_addr)
		वापस false;

	/* Only supports single display */
	अगर (context->stream_count != 1)
		वापस false;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (res_ctx->pipe_ctx[i].stream) अणु

			pipe_ctx = &res_ctx->pipe_ctx[i];

			अगर (!pipe_ctx)
				जारी;

			/* fbc not applicable on underlay pipe */
			अगर (pipe_ctx->pipe_idx != underlay_idx) अणु
				*pipe_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i == dc->res_pool->pipe_count)
		वापस false;

	अगर (!pipe_ctx->stream->link)
		वापस false;

	/* Only supports eDP */
	अगर (pipe_ctx->stream->link->connector_संकेत != SIGNAL_TYPE_EDP)
		वापस false;

	/* PSR should not be enabled */
	अगर (pipe_ctx->stream->link->psr_settings.psr_feature_enabled)
		वापस false;

	/* Nothing to compress */
	अगर (!pipe_ctx->plane_state)
		वापस false;

	/* Only क्रम non-linear tiling */
	अगर (pipe_ctx->plane_state->tiling_info.gfx8.array_mode == DC_ARRAY_LINEAR_GENERAL)
		वापस false;

	वापस true;
पूर्ण

/*
 *  Enable FBC
 */
अटल व्योम enable_fbc(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	uपूर्णांक32_t pipe_idx = 0;

	अगर (should_enable_fbc(dc, context, &pipe_idx)) अणु
		/* Program GRPH COMPRESSED ADDRESS and PITCH */
		काष्ठा compr_addr_and_pitch_params params = अणु0, 0, 0पूर्ण;
		काष्ठा compressor *compr = dc->fbc_compressor;
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[pipe_idx];

		params.source_view_width = pipe_ctx->stream->timing.h_addressable;
		params.source_view_height = pipe_ctx->stream->timing.v_addressable;
		params.inst = pipe_ctx->stream_res.tg->inst;
		compr->compr_surface_address.quad_part = dc->ctx->fbc_gpu_addr;

		compr->funcs->surface_address_and_pitch(compr, &params);
		compr->funcs->set_fbc_invalidation_triggers(compr, 1);

		compr->funcs->enable_fbc(compr, &params);
	पूर्ण
पूर्ण

अटल व्योम dce110_reset_hw_ctx_wrap(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	/* Reset old context */
	/* look up the tarमाला_लो that have been हटाओd since last commit */
	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx_old =
			&dc->current_state->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		/* Note: We need to disable output अगर घड़ी sources change,
		 * since bios करोes optimization and करोesn't apply अगर changing
		 * PHY when not alपढ़ोy disabled.
		 */

		/* Skip underlay pipe since it will be handled in commit surface*/
		अगर (!pipe_ctx_old->stream || pipe_ctx_old->top_pipe)
			जारी;

		अगर (!pipe_ctx->stream ||
				pipe_need_reprogram(pipe_ctx_old, pipe_ctx)) अणु
			काष्ठा घड़ी_source *old_clk = pipe_ctx_old->घड़ी_source;

			/* Disable अगर new stream is null. O/w, अगर stream is
			 * disabled alपढ़ोy, no need to disable again.
			 */
			अगर (!pipe_ctx->stream || !pipe_ctx->stream->dpms_off) अणु
				core_link_disable_stream(pipe_ctx_old);

				/* मुक्त acquired resources*/
				अगर (pipe_ctx_old->stream_res.audio) अणु
					/*disable az_endpoपूर्णांक*/
					pipe_ctx_old->stream_res.audio->funcs->
							az_disable(pipe_ctx_old->stream_res.audio);

					/*मुक्त audio*/
					अगर (dc->caps.dynamic_audio == true) अणु
						/*we have to dynamic arbitrate the audio endpoपूर्णांकs*/
						/*we मुक्त the resource, need reset is_audio_acquired*/
						update_audio_usage(&dc->current_state->res_ctx, dc->res_pool,
								pipe_ctx_old->stream_res.audio, false);
						pipe_ctx_old->stream_res.audio = शून्य;
					पूर्ण
				पूर्ण
			पूर्ण

			pipe_ctx_old->stream_res.tg->funcs->set_blank(pipe_ctx_old->stream_res.tg, true);
			अगर (!hwss_रुको_क्रम_blank_complete(pipe_ctx_old->stream_res.tg)) अणु
				dm_error("DC: failed to blank crtc!\n");
				BREAK_TO_DEBUGGER();
			पूर्ण
			pipe_ctx_old->stream_res.tg->funcs->disable_crtc(pipe_ctx_old->stream_res.tg);
			pipe_ctx_old->plane_res.mi->funcs->मुक्त_mem_input(
					pipe_ctx_old->plane_res.mi, dc->current_state->stream_count);

			अगर (old_clk && 0 == resource_get_घड़ी_source_reference(&context->res_ctx,
										dc->res_pool,
										old_clk))
				old_clk->funcs->cs_घातer_करोwn(old_clk);

			dc->hwss.disable_plane(dc, pipe_ctx_old);

			pipe_ctx_old->stream = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dce110_setup_audio_dto(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	/* program audio wall घड़ी. use HDMI as घड़ी source अगर HDMI
	 * audio active. Otherwise, use DP as घड़ी source
	 * first, loop to find any HDMI audio, अगर not, loop find DP audio
	 */
	/* Setup audio rate घड़ी source */
	/* Issue:
	* Audio lag happened on DP monitor when unplug a HDMI monitor
	*
	* Cause:
	* In हाल of DP and HDMI connected or HDMI only, DCCG_AUDIO_DTO_SEL
	* is set to either dto0 or dto1, audio should work fine.
	* In हाल of DP connected only, DCCG_AUDIO_DTO_SEL should be dto1,
	* set to dto0 will cause audio lag.
	*
	* Solution:
	* Not optimized audio wall dto setup. When mode set, iterate pipe_ctx,
	* find first available pipe with audio, setup audio wall DTO per topology
	* instead of per pipe.
	*/
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream == शून्य)
			जारी;

		अगर (pipe_ctx->top_pipe)
			जारी;
		अगर (pipe_ctx->stream->संकेत != SIGNAL_TYPE_HDMI_TYPE_A)
			जारी;
		अगर (pipe_ctx->stream_res.audio != शून्य) अणु
			काष्ठा audio_output audio_output;

			build_audio_output(context, pipe_ctx, &audio_output);

			pipe_ctx->stream_res.audio->funcs->wall_dto_setup(
				pipe_ctx->stream_res.audio,
				pipe_ctx->stream->संकेत,
				&audio_output.crtc_info,
				&audio_output.pll_info);
			अवरोध;
		पूर्ण
	पूर्ण

	/* no HDMI audio is found, try DP audio */
	अगर (i == dc->res_pool->pipe_count) अणु
		क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
			काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

			अगर (pipe_ctx->stream == शून्य)
				जारी;

			अगर (pipe_ctx->top_pipe)
				जारी;

			अगर (!dc_is_dp_संकेत(pipe_ctx->stream->संकेत))
				जारी;

			अगर (pipe_ctx->stream_res.audio != शून्य) अणु
				काष्ठा audio_output audio_output;

				build_audio_output(context, pipe_ctx, &audio_output);

				pipe_ctx->stream_res.audio->funcs->wall_dto_setup(
					pipe_ctx->stream_res.audio,
					pipe_ctx->stream->संकेत,
					&audio_output.crtc_info,
					&audio_output.pll_info);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

क्रमागत dc_status dce110_apply_ctx_to_hw(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा dc_bios *dcb = dc->ctx->dc_bios;
	क्रमागत dc_status status;
	पूर्णांक i;

	/* Reset old context */
	/* look up the tarमाला_लो that have been हटाओd since last commit */
	hws->funcs.reset_hw_ctx_wrap(dc, context);

	/* Skip applying अगर no tarमाला_लो */
	अगर (context->stream_count <= 0)
		वापस DC_OK;

	/* Apply new context */
	dcb->funcs->set_scratch_critical_state(dcb, true);

	/* below is क्रम real asic only */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx_old =
					&dc->current_state->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream == शून्य || pipe_ctx->top_pipe)
			जारी;

		अगर (pipe_ctx->stream == pipe_ctx_old->stream) अणु
			अगर (pipe_ctx_old->घड़ी_source != pipe_ctx->घड़ी_source)
				dce_crtc_चयन_to_clk_src(dc->hwseq,
						pipe_ctx->घड़ी_source, i);
			जारी;
		पूर्ण

		hws->funcs.enable_display_घातer_gating(
				dc, i, dc->ctx->dc_bios,
				PIPE_GATING_CONTROL_DISABLE);
	पूर्ण

	अगर (dc->fbc_compressor)
		dc->fbc_compressor->funcs->disable_fbc(dc->fbc_compressor);

	dce110_setup_audio_dto(dc, context);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx_old =
					&dc->current_state->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream == शून्य)
			जारी;

		अगर (pipe_ctx->stream == pipe_ctx_old->stream &&
			pipe_ctx->stream->link->link_state_valid) अणु
			जारी;
		पूर्ण

		अगर (pipe_ctx_old->stream && !pipe_need_reprogram(pipe_ctx_old, pipe_ctx))
			जारी;

		अगर (pipe_ctx->top_pipe || pipe_ctx->prev_odm_pipe)
			जारी;

		status = apply_single_controller_ctx_to_hw(
				pipe_ctx,
				context,
				dc);

		अगर (DC_OK != status)
			वापस status;
	पूर्ण

	अगर (dc->fbc_compressor)
		enable_fbc(dc, dc->current_state);

	dcb->funcs->set_scratch_critical_state(dcb, false);

	वापस DC_OK;
पूर्ण

/*******************************************************************************
 * Front End programming
 ******************************************************************************/
अटल व्योम set_शेष_colors(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा शेष_adjusपंचांगent शेष_adjust = अणु 0 पूर्ण;

	शेष_adjust.क्रमce_hw_शेष = false;
	शेष_adjust.in_color_space = pipe_ctx->plane_state->color_space;
	शेष_adjust.out_color_space = pipe_ctx->stream->output_color_space;
	शेष_adjust.csc_adjust_type = GRAPHICS_CSC_ADJUST_TYPE_SW;
	शेष_adjust.surface_pixel_क्रमmat = pipe_ctx->plane_res.scl_data.क्रमmat;

	/* display color depth */
	शेष_adjust.color_depth =
		pipe_ctx->stream->timing.display_color_depth;

	/* Lb color depth */
	शेष_adjust.lb_color_depth = pipe_ctx->plane_res.scl_data.lb_params.depth;

	pipe_ctx->plane_res.xfm->funcs->opp_set_csc_शेष(
					pipe_ctx->plane_res.xfm, &शेष_adjust);
पूर्ण


/*******************************************************************************
 * In order to turn on/off specअगरic surface we will program
 * Blender + CRTC
 *
 * In हाल that we have two surfaces and they have a dअगरferent visibility
 * we can't turn off the CRTC since it will turn off the entire display
 *
 * |----------------------------------------------- |
 * |bottom pipe|curr pipe  |              |         |
 * |Surface    |Surface    | Blender      |  CRCT   |
 * |visibility |visibility | Configuration|         |
 * |------------------------------------------------|
 * |   off     |    off    | CURRENT_PIPE | blank   |
 * |   off     |    on     | CURRENT_PIPE | unblank |
 * |   on      |    off    | OTHER_PIPE   | unblank |
 * |   on      |    on     | BLENDING     | unblank |
 * -------------------------------------------------|
 *
 ******************************************************************************/
अटल व्योम program_surface_visibility(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	क्रमागत blnd_mode blender_mode = BLND_MODE_CURRENT_PIPE;
	bool blank_target = false;

	अगर (pipe_ctx->bottom_pipe) अणु

		/* For now we are supporting only two pipes */
		ASSERT(pipe_ctx->bottom_pipe->bottom_pipe == शून्य);

		अगर (pipe_ctx->bottom_pipe->plane_state->visible) अणु
			अगर (pipe_ctx->plane_state->visible)
				blender_mode = BLND_MODE_BLENDING;
			अन्यथा
				blender_mode = BLND_MODE_OTHER_PIPE;

		पूर्ण अन्यथा अगर (!pipe_ctx->plane_state->visible)
			blank_target = true;

	पूर्ण अन्यथा अगर (!pipe_ctx->plane_state->visible)
		blank_target = true;

	dce_set_blender_mode(dc->hwseq, pipe_ctx->stream_res.tg->inst, blender_mode);
	pipe_ctx->stream_res.tg->funcs->set_blank(pipe_ctx->stream_res.tg, blank_target);

पूर्ण

अटल व्योम program_gamut_remap(काष्ठा pipe_ctx *pipe_ctx)
अणु
	पूर्णांक i = 0;
	काष्ठा xfm_grph_csc_adjusपंचांगent adjust;
	स_रखो(&adjust, 0, माप(adjust));
	adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS;


	अगर (pipe_ctx->stream->gamut_remap_matrix.enable_remap == true) अणु
		adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_SW;

		क्रम (i = 0; i < CSC_TEMPERATURE_MATRIX_SIZE; i++)
			adjust.temperature_matrix[i] =
				pipe_ctx->stream->gamut_remap_matrix.matrix[i];
	पूर्ण

	pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_gamut_remap(pipe_ctx->plane_res.xfm, &adjust);
पूर्ण
अटल व्योम update_plane_addr(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;

	अगर (plane_state == शून्य)
		वापस;

	pipe_ctx->plane_res.mi->funcs->mem_input_program_surface_flip_and_addr(
			pipe_ctx->plane_res.mi,
			&plane_state->address,
			plane_state->flip_immediate);

	plane_state->status.requested_address = plane_state->address;
पूर्ण

अटल व्योम dce110_update_pending_status(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;

	अगर (plane_state == शून्य)
		वापस;

	plane_state->status.is_flip_pending =
			pipe_ctx->plane_res.mi->funcs->mem_input_is_flip_pending(
					pipe_ctx->plane_res.mi);

	अगर (plane_state->status.is_flip_pending && !plane_state->visible)
		pipe_ctx->plane_res.mi->current_address = pipe_ctx->plane_res.mi->request_address;

	plane_state->status.current_address = pipe_ctx->plane_res.mi->current_address;
	अगर (pipe_ctx->plane_res.mi->current_address.type == PLN_ADDR_TYPE_GRPH_STEREO &&
			pipe_ctx->stream_res.tg->funcs->is_stereo_left_eye) अणु
		plane_state->status.is_right_eye =\
				!pipe_ctx->stream_res.tg->funcs->is_stereo_left_eye(pipe_ctx->stream_res.tg);
	पूर्ण
पूर्ण

व्योम dce110_घातer_करोwn(काष्ठा dc *dc)
अणु
	घातer_करोwn_all_hw_blocks(dc);
	disable_vga_and_घातer_gate_all_controllers(dc);
पूर्ण

अटल bool रुको_क्रम_reset_trigger_to_occur(
	काष्ठा dc_context *dc_ctx,
	काष्ठा timing_generator *tg)
अणु
	bool rc = false;

	/* To aव्योम endless loop we रुको at most
	 * frames_to_रुको_on_triggered_reset frames क्रम the reset to occur. */
	स्थिर uपूर्णांक32_t frames_to_रुको_on_triggered_reset = 10;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < frames_to_रुको_on_triggered_reset; i++) अणु

		अगर (!tg->funcs->is_counter_moving(tg)) अणु
			DC_ERROR("TG counter is not moving!\n");
			अवरोध;
		पूर्ण

		अगर (tg->funcs->did_triggered_reset_occur(tg)) अणु
			rc = true;
			/* usually occurs at i=1 */
			DC_SYNC_INFO("GSL: reset occurred at wait count: %d\n",
					i);
			अवरोध;
		पूर्ण

		/* Wait क्रम one frame. */
		tg->funcs->रुको_क्रम_state(tg, CRTC_STATE_VACTIVE);
		tg->funcs->रुको_क्रम_state(tg, CRTC_STATE_VBLANK);
	पूर्ण

	अगर (false == rc)
		DC_ERROR("GSL: Timeout on reset trigger!\n");

	वापस rc;
पूर्ण

/* Enable timing synchronization क्रम a group of Timing Generators. */
अटल व्योम dce110_enable_timing_synchronization(
		काष्ठा dc *dc,
		पूर्णांक group_index,
		पूर्णांक group_size,
		काष्ठा pipe_ctx *grouped_pipes[])
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा dcp_gsl_params gsl_params = अणु 0 पूर्ण;
	पूर्णांक i;

	DC_SYNC_INFO("GSL: Setting-up...\n");

	/* Designate a single TG in the group as a master.
	 * Since HW करोesn't care which one, we always assign
	 * the 1st one in the group. */
	gsl_params.gsl_group = 0;
	gsl_params.gsl_master = grouped_pipes[0]->stream_res.tg->inst;

	क्रम (i = 0; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->setup_global_swap_lock(
					grouped_pipes[i]->stream_res.tg, &gsl_params);

	/* Reset slave controllers on master VSync */
	DC_SYNC_INFO("GSL: enabling trigger-reset\n");

	क्रम (i = 1 /* skip the master */; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->enable_reset_trigger(
				grouped_pipes[i]->stream_res.tg,
				gsl_params.gsl_group);

	क्रम (i = 1 /* skip the master */; i < group_size; i++) अणु
		DC_SYNC_INFO("GSL: waiting for reset to occur.\n");
		रुको_क्रम_reset_trigger_to_occur(dc_ctx, grouped_pipes[i]->stream_res.tg);
		grouped_pipes[i]->stream_res.tg->funcs->disable_reset_trigger(
				grouped_pipes[i]->stream_res.tg);
	पूर्ण

	/* GSL Vblank synchronization is a one समय sync mechanism, assumption
	 * is that the sync'ed displays will not drअगरt out of sync over समय*/
	DC_SYNC_INFO("GSL: Restoring register states.\n");
	क्रम (i = 0; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->tear_करोwn_global_swap_lock(grouped_pipes[i]->stream_res.tg);

	DC_SYNC_INFO("GSL: Set-up complete.\n");
पूर्ण

अटल व्योम dce110_enable_per_frame_crtc_position_reset(
		काष्ठा dc *dc,
		पूर्णांक group_size,
		काष्ठा pipe_ctx *grouped_pipes[])
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा dcp_gsl_params gsl_params = अणु 0 पूर्ण;
	पूर्णांक i;

	gsl_params.gsl_group = 0;
	gsl_params.gsl_master = 0;

	क्रम (i = 0; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->setup_global_swap_lock(
					grouped_pipes[i]->stream_res.tg, &gsl_params);

	DC_SYNC_INFO("GSL: enabling trigger-reset\n");

	क्रम (i = 1; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->enable_crtc_reset(
				grouped_pipes[i]->stream_res.tg,
				gsl_params.gsl_master,
				&grouped_pipes[i]->stream->triggered_crtc_reset);

	DC_SYNC_INFO("GSL: waiting for reset to occur.\n");
	क्रम (i = 1; i < group_size; i++)
		रुको_क्रम_reset_trigger_to_occur(dc_ctx, grouped_pipes[i]->stream_res.tg);

	क्रम (i = 0; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->tear_करोwn_global_swap_lock(grouped_pipes[i]->stream_res.tg);

पूर्ण

अटल व्योम init_pipes(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	// Do nothing
पूर्ण

अटल व्योम init_hw(काष्ठा dc *dc)
अणु
	पूर्णांक i;
	काष्ठा dc_bios *bp;
	काष्ठा transक्रमm *xfm;
	काष्ठा abm *abm;
	काष्ठा dmcu *dmcu;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	uपूर्णांक32_t backlight = MAX_BACKLIGHT_LEVEL;

	bp = dc->ctx->dc_bios;
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		xfm = dc->res_pool->transक्रमms[i];
		xfm->funcs->transक्रमm_reset(xfm);

		hws->funcs.enable_display_घातer_gating(
				dc, i, bp,
				PIPE_GATING_CONTROL_INIT);
		hws->funcs.enable_display_घातer_gating(
				dc, i, bp,
				PIPE_GATING_CONTROL_DISABLE);
		hws->funcs.enable_display_pipe_घड़ी_gating(
			dc->ctx,
			true);
	पूर्ण

	dce_घड़ी_gating_घातer_up(dc->hwseq, false);
	/***************************************/

	क्रम (i = 0; i < dc->link_count; i++) अणु
		/****************************************/
		/* Power up AND update implementation according to the
		 * required संकेत (which may be dअगरferent from the
		 * शेष संकेत on connector). */
		काष्ठा dc_link *link = dc->links[i];

		link->link_enc->funcs->hw_init(link->link_enc);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];

		tg->funcs->disable_vga(tg);

		/* Blank controller using driver code instead of
		 * command table. */
		tg->funcs->set_blank(tg, true);
		hwss_रुको_क्रम_blank_complete(tg);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->audio_count; i++) अणु
		काष्ठा audio *audio = dc->res_pool->audios[i];
		audio->funcs->hw_init(audio);
	पूर्ण

	क्रम (i = 0; i < dc->link_count; i++) अणु
		काष्ठा dc_link *link = dc->links[i];

		अगर (link->panel_cntl)
			backlight = link->panel_cntl->funcs->hw_init(link->panel_cntl);
	पूर्ण

	abm = dc->res_pool->abm;
	अगर (abm != शून्य)
		abm->funcs->abm_init(abm, backlight);

	dmcu = dc->res_pool->dmcu;
	अगर (dmcu != शून्य && abm != शून्य)
		abm->dmcu_is_running = dmcu->funcs->is_dmcu_initialized(dmcu);

	अगर (dc->fbc_compressor)
		dc->fbc_compressor->funcs->घातer_up_fbc(dc->fbc_compressor);

पूर्ण


व्योम dce110_prepare_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	काष्ठा clk_mgr *dccg = dc->clk_mgr;

	dce110_set_safe_displaymarks(&context->res_ctx, dc->res_pool);

	dccg->funcs->update_घड़ीs(
			dccg,
			context,
			false);
पूर्ण

व्योम dce110_optimize_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	काष्ठा clk_mgr *dccg = dc->clk_mgr;

	dce110_set_displaymarks(dc, context);

	dccg->funcs->update_घड़ीs(
			dccg,
			context,
			true);
पूर्ण

अटल व्योम dce110_program_front_end_क्रम_pipe(
		काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा mem_input *mi = pipe_ctx->plane_res.mi;
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	काष्ठा xfm_grph_csc_adjusपंचांगent adjust;
	काष्ठा out_csc_color_matrix tbl_entry;
	अचिन्हित पूर्णांक i;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	DC_LOGGER_INIT();
	स_रखो(&tbl_entry, 0, माप(tbl_entry));

	स_रखो(&adjust, 0, माप(adjust));
	adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS;

	dce_enable_fe_घड़ी(dc->hwseq, mi->inst, true);

	set_शेष_colors(pipe_ctx);
	अगर (pipe_ctx->stream->csc_color_matrix.enable_adjusपंचांगent
			== true) अणु
		tbl_entry.color_space =
			pipe_ctx->stream->output_color_space;

		क्रम (i = 0; i < 12; i++)
			tbl_entry.regval[i] =
			pipe_ctx->stream->csc_color_matrix.matrix[i];

		pipe_ctx->plane_res.xfm->funcs->opp_set_csc_adjusपंचांगent
				(pipe_ctx->plane_res.xfm, &tbl_entry);
	पूर्ण

	अगर (pipe_ctx->stream->gamut_remap_matrix.enable_remap == true) अणु
		adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_SW;

		क्रम (i = 0; i < CSC_TEMPERATURE_MATRIX_SIZE; i++)
			adjust.temperature_matrix[i] =
				pipe_ctx->stream->gamut_remap_matrix.matrix[i];
	पूर्ण

	pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_gamut_remap(pipe_ctx->plane_res.xfm, &adjust);

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = pipe_ctx->bottom_pipe != 0;

	program_scaler(dc, pipe_ctx);

	mi->funcs->mem_input_program_surface_config(
			mi,
			plane_state->क्रमmat,
			&plane_state->tiling_info,
			&plane_state->plane_size,
			plane_state->rotation,
			शून्य,
			false);
	अगर (mi->funcs->set_blank)
		mi->funcs->set_blank(mi, pipe_ctx->plane_state->visible);

	अगर (dc->config.gpu_vm_support)
		mi->funcs->mem_input_program_pte_vm(
				pipe_ctx->plane_res.mi,
				plane_state->क्रमmat,
				&plane_state->tiling_info,
				plane_state->rotation);

	/* Moved programming gamma from dc to hwss */
	अगर (pipe_ctx->plane_state->update_flags.bits.full_update ||
			pipe_ctx->plane_state->update_flags.bits.in_transfer_func_change ||
			pipe_ctx->plane_state->update_flags.bits.gamma_change)
		hws->funcs.set_input_transfer_func(dc, pipe_ctx, pipe_ctx->plane_state);

	अगर (pipe_ctx->plane_state->update_flags.bits.full_update)
		hws->funcs.set_output_transfer_func(dc, pipe_ctx, pipe_ctx->stream);

	DC_LOG_SURFACE(
			"Pipe:%d %p: addr hi:0x%x, "
			"addr low:0x%x, "
			"src: %d, %d, %d,"
			" %d; dst: %d, %d, %d, %d;"
			"clip: %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			(व्योम *) pipe_ctx->plane_state,
			pipe_ctx->plane_state->address.grph.addr.high_part,
			pipe_ctx->plane_state->address.grph.addr.low_part,
			pipe_ctx->plane_state->src_rect.x,
			pipe_ctx->plane_state->src_rect.y,
			pipe_ctx->plane_state->src_rect.width,
			pipe_ctx->plane_state->src_rect.height,
			pipe_ctx->plane_state->dst_rect.x,
			pipe_ctx->plane_state->dst_rect.y,
			pipe_ctx->plane_state->dst_rect.width,
			pipe_ctx->plane_state->dst_rect.height,
			pipe_ctx->plane_state->clip_rect.x,
			pipe_ctx->plane_state->clip_rect.y,
			pipe_ctx->plane_state->clip_rect.width,
			pipe_ctx->plane_state->clip_rect.height);

	DC_LOG_SURFACE(
			"Pipe %d: width, height, x, y\n"
			"viewport:%d, %d, %d, %d\n"
			"recout:  %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			pipe_ctx->plane_res.scl_data.viewport.width,
			pipe_ctx->plane_res.scl_data.viewport.height,
			pipe_ctx->plane_res.scl_data.viewport.x,
			pipe_ctx->plane_res.scl_data.viewport.y,
			pipe_ctx->plane_res.scl_data.recout.width,
			pipe_ctx->plane_res.scl_data.recout.height,
			pipe_ctx->plane_res.scl_data.recout.x,
			pipe_ctx->plane_res.scl_data.recout.y);
पूर्ण

अटल व्योम dce110_apply_ctx_क्रम_surface(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_stream_state *stream,
		पूर्णांक num_planes,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	अगर (num_planes == 0)
		वापस;

	अगर (dc->fbc_compressor)
		dc->fbc_compressor->funcs->disable_fbc(dc->fbc_compressor);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream != stream)
			जारी;

		/* Need to allocate mem beक्रमe program front end क्रम Fiji */
		pipe_ctx->plane_res.mi->funcs->allocate_mem_input(
				pipe_ctx->plane_res.mi,
				pipe_ctx->stream->timing.h_total,
				pipe_ctx->stream->timing.v_total,
				pipe_ctx->stream->timing.pix_clk_100hz / 10,
				context->stream_count);

		dce110_program_front_end_क्रम_pipe(dc, pipe_ctx);

		dc->hwss.update_plane_addr(dc, pipe_ctx);

		program_surface_visibility(dc, pipe_ctx);

	पूर्ण

	अगर (dc->fbc_compressor)
		enable_fbc(dc, context);
पूर्ण

अटल व्योम dce110_post_unlock_program_front_end(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
पूर्ण

अटल व्योम dce110_घातer_करोwn_fe(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	पूर्णांक fe_idx = pipe_ctx->plane_res.mi ?
		pipe_ctx->plane_res.mi->inst : pipe_ctx->pipe_idx;

	/* Do not घातer करोwn fe when stream is active on dce*/
	अगर (dc->current_state->res_ctx.pipe_ctx[fe_idx].stream)
		वापस;

	hws->funcs.enable_display_घातer_gating(
		dc, fe_idx, dc->ctx->dc_bios, PIPE_GATING_CONTROL_ENABLE);

	dc->res_pool->transक्रमms[fe_idx]->funcs->transक्रमm_reset(
				dc->res_pool->transक्रमms[fe_idx]);
पूर्ण

अटल व्योम dce110_रुको_क्रम_mpcc_disconnect(
		काष्ठा dc *dc,
		काष्ठा resource_pool *res_pool,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	/* करो nothing*/
पूर्ण

अटल व्योम program_output_csc(काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत dc_color_space colorspace,
		uपूर्णांक16_t *matrix,
		पूर्णांक opp_id)
अणु
	पूर्णांक i;
	काष्ठा out_csc_color_matrix tbl_entry;

	अगर (pipe_ctx->stream->csc_color_matrix.enable_adjusपंचांगent == true) अणु
		क्रमागत dc_color_space color_space = pipe_ctx->stream->output_color_space;

		क्रम (i = 0; i < 12; i++)
			tbl_entry.regval[i] = pipe_ctx->stream->csc_color_matrix.matrix[i];

		tbl_entry.color_space = color_space;

		pipe_ctx->plane_res.xfm->funcs->opp_set_csc_adjusपंचांगent(
				pipe_ctx->plane_res.xfm, &tbl_entry);
	पूर्ण
पूर्ण

अटल व्योम dce110_set_cursor_position(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_cursor_position pos_cpy = pipe_ctx->stream->cursor_position;
	काष्ठा input_pixel_processor *ipp = pipe_ctx->plane_res.ipp;
	काष्ठा mem_input *mi = pipe_ctx->plane_res.mi;
	काष्ठा dc_cursor_mi_param param = अणु
		.pixel_clk_khz = pipe_ctx->stream->timing.pix_clk_100hz / 10,
		.ref_clk_khz = pipe_ctx->stream->ctx->dc->res_pool->ref_घड़ीs.xtalin_घड़ी_inKhz,
		.viewport = pipe_ctx->plane_res.scl_data.viewport,
		.h_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.horz,
		.v_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.vert,
		.rotation = pipe_ctx->plane_state->rotation,
		.mirror = pipe_ctx->plane_state->horizontal_mirror
	पूर्ण;

	/**
	 * If the cursor's source viewport is clipped then we need to
	 * translate the cursor to appear in the correct position on
	 * the screen.
	 *
	 * This translation isn't affected by scaling so it needs to be
	 * करोne *after* we adjust the position क्रम the scale factor.
	 *
	 * This is only करोne by opt-in क्रम now since there are still
	 * some useहालs like tiled display that might enable the
	 * cursor on both streams जबतक expecting dc to clip it.
	 */
	अगर (pos_cpy.translate_by_source) अणु
		pos_cpy.x += pipe_ctx->plane_state->src_rect.x;
		pos_cpy.y += pipe_ctx->plane_state->src_rect.y;
	पूर्ण

	अगर (pipe_ctx->plane_state->address.type
			== PLN_ADDR_TYPE_VIDEO_PROGRESSIVE)
		pos_cpy.enable = false;

	अगर (pipe_ctx->top_pipe && pipe_ctx->plane_state != pipe_ctx->top_pipe->plane_state)
		pos_cpy.enable = false;

	अगर (ipp->funcs->ipp_cursor_set_position)
		ipp->funcs->ipp_cursor_set_position(ipp, &pos_cpy, &param);
	अगर (mi->funcs->set_cursor_position)
		mi->funcs->set_cursor_position(mi, &pos_cpy, &param);
पूर्ण

अटल व्योम dce110_set_cursor_attribute(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_cursor_attributes *attributes = &pipe_ctx->stream->cursor_attributes;

	अगर (pipe_ctx->plane_res.ipp &&
	    pipe_ctx->plane_res.ipp->funcs->ipp_cursor_set_attributes)
		pipe_ctx->plane_res.ipp->funcs->ipp_cursor_set_attributes(
				pipe_ctx->plane_res.ipp, attributes);

	अगर (pipe_ctx->plane_res.mi &&
	    pipe_ctx->plane_res.mi->funcs->set_cursor_attributes)
		pipe_ctx->plane_res.mi->funcs->set_cursor_attributes(
				pipe_ctx->plane_res.mi, attributes);

	अगर (pipe_ctx->plane_res.xfm &&
	    pipe_ctx->plane_res.xfm->funcs->set_cursor_attributes)
		pipe_ctx->plane_res.xfm->funcs->set_cursor_attributes(
				pipe_ctx->plane_res.xfm, attributes);
पूर्ण

bool dce110_set_backlight_level(काष्ठा pipe_ctx *pipe_ctx,
		uपूर्णांक32_t backlight_pwm_u16_16,
		uपूर्णांक32_t frame_ramp)
अणु
	काष्ठा dc_link *link = pipe_ctx->stream->link;
	काष्ठा dc  *dc = link->ctx->dc;
	काष्ठा abm *abm = pipe_ctx->stream_res.abm;
	काष्ठा panel_cntl *panel_cntl = link->panel_cntl;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	bool fw_set_brightness = true;
	/* DMCU -1 क्रम all controller id values,
	 * thereक्रमe +1 here
	 */
	uपूर्णांक32_t controller_id = pipe_ctx->stream_res.tg->inst + 1;

	अगर (abm == शून्य || panel_cntl == शून्य || (abm->funcs->set_backlight_level_pwm == शून्य))
		वापस false;

	अगर (dmcu)
		fw_set_brightness = dmcu->funcs->is_dmcu_initialized(dmcu);

	अगर (!fw_set_brightness && panel_cntl->funcs->driver_set_backlight)
		panel_cntl->funcs->driver_set_backlight(panel_cntl, backlight_pwm_u16_16);
	अन्यथा
		abm->funcs->set_backlight_level_pwm(
				abm,
				backlight_pwm_u16_16,
				frame_ramp,
				controller_id,
				link->panel_cntl->inst);

	वापस true;
पूर्ण

व्योम dce110_set_abm_immediate_disable(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा abm *abm = pipe_ctx->stream_res.abm;
	काष्ठा panel_cntl *panel_cntl = pipe_ctx->stream->link->panel_cntl;

	अगर (abm)
		abm->funcs->set_abm_immediate_disable(abm,
				pipe_ctx->stream->link->panel_cntl->inst);

	अगर (panel_cntl)
		panel_cntl->funcs->store_backlight_level(panel_cntl);
पूर्ण

व्योम dce110_set_pipe(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा abm *abm = pipe_ctx->stream_res.abm;
	काष्ठा panel_cntl *panel_cntl = pipe_ctx->stream->link->panel_cntl;
	uपूर्णांक32_t otg_inst = pipe_ctx->stream_res.tg->inst + 1;

	अगर (abm && panel_cntl)
		abm->funcs->set_pipe(abm, otg_inst, panel_cntl->inst);
पूर्ण

अटल स्थिर काष्ठा hw_sequencer_funcs dce110_funcs = अणु
	.program_gamut_remap = program_gamut_remap,
	.program_output_csc = program_output_csc,
	.init_hw = init_hw,
	.apply_ctx_to_hw = dce110_apply_ctx_to_hw,
	.apply_ctx_क्रम_surface = dce110_apply_ctx_क्रम_surface,
	.post_unlock_program_front_end = dce110_post_unlock_program_front_end,
	.update_plane_addr = update_plane_addr,
	.update_pending_status = dce110_update_pending_status,
	.enable_accelerated_mode = dce110_enable_accelerated_mode,
	.enable_timing_synchronization = dce110_enable_timing_synchronization,
	.enable_per_frame_crtc_position_reset = dce110_enable_per_frame_crtc_position_reset,
	.update_info_frame = dce110_update_info_frame,
	.enable_stream = dce110_enable_stream,
	.disable_stream = dce110_disable_stream,
	.unblank_stream = dce110_unblank_stream,
	.blank_stream = dce110_blank_stream,
	.enable_audio_stream = dce110_enable_audio_stream,
	.disable_audio_stream = dce110_disable_audio_stream,
	.disable_plane = dce110_घातer_करोwn_fe,
	.pipe_control_lock = dce_pipe_control_lock,
	.पूर्णांकerdependent_update_lock = शून्य,
	.cursor_lock = dce_pipe_control_lock,
	.prepare_bandwidth = dce110_prepare_bandwidth,
	.optimize_bandwidth = dce110_optimize_bandwidth,
	.set_drr = set_drr,
	.get_position = get_position,
	.set_अटल_screen_control = set_अटल_screen_control,
	.setup_stereo = शून्य,
	.set_avmute = dce110_set_avmute,
	.रुको_क्रम_mpcc_disconnect = dce110_रुको_क्रम_mpcc_disconnect,
	.edp_backlight_control = dce110_edp_backlight_control,
	.edp_घातer_control = dce110_edp_घातer_control,
	.edp_रुको_क्रम_hpd_पढ़ोy = dce110_edp_रुको_क्रम_hpd_पढ़ोy,
	.set_cursor_position = dce110_set_cursor_position,
	.set_cursor_attribute = dce110_set_cursor_attribute,
	.set_backlight_level = dce110_set_backlight_level,
	.set_abm_immediate_disable = dce110_set_abm_immediate_disable,
	.set_pipe = dce110_set_pipe,
पूर्ण;

अटल स्थिर काष्ठा hwseq_निजी_funcs dce110_निजी_funcs = अणु
	.init_pipes = init_pipes,
	.update_plane_addr = update_plane_addr,
	.set_input_transfer_func = dce110_set_input_transfer_func,
	.set_output_transfer_func = dce110_set_output_transfer_func,
	.घातer_करोwn = dce110_घातer_करोwn,
	.enable_display_pipe_घड़ी_gating = enable_display_pipe_घड़ी_gating,
	.enable_display_घातer_gating = dce110_enable_display_घातer_gating,
	.reset_hw_ctx_wrap = dce110_reset_hw_ctx_wrap,
	.enable_stream_timing = dce110_enable_stream_timing,
	.disable_stream_gating = शून्य,
	.enable_stream_gating = शून्य,
	.edp_backlight_control = dce110_edp_backlight_control,
पूर्ण;

व्योम dce110_hw_sequencer_स्थिरruct(काष्ठा dc *dc)
अणु
	dc->hwss = dce110_funcs;
	dc->hwseq->funcs = dce110_निजी_funcs;
पूर्ण

