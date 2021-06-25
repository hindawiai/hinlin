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
#समावेश "resource.h"
#समावेश "dwb.h"
#समावेश "dcn30_dwb.h"


#घोषणा REG(reg)\
	dwbc30->dwbc_regs->reg

#घोषणा CTX \
	dwbc30->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dwbc30->dwbc_shअगरt->field_name, dwbc30->dwbc_mask->field_name

#घोषणा DC_LOGGER \
	dwbc30->base.ctx->logger

अटल bool dwb3_get_caps(काष्ठा dwbc *dwbc, काष्ठा dwb_caps *caps)
अणु
	अगर (caps) अणु
		caps->adapter_id = 0;	/* we only support 1 adapter currently */
		caps->hw_version = DCN_VERSION_3_0;
		caps->num_pipes = 2;
		स_रखो(&caps->reserved, 0, माप(caps->reserved));
		स_रखो(&caps->reserved2, 0, माप(caps->reserved2));
		caps->sw_version = dwb_ver_2_0;
		caps->caps.support_dwb = true;
		caps->caps.support_ogam = true;
		caps->caps.support_wbscl = true;
		caps->caps.support_ocsc = false;
		caps->caps.support_stereo = true;
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

व्योम dwb3_config_fc(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	/* Set DWB source size */
	REG_UPDATE_2(FC_SOURCE_SIZE, FC_SOURCE_WIDTH, params->cnv_params.src_width,
			FC_SOURCE_HEIGHT, params->cnv_params.src_height);

	/* source size is not equal the source size, then enable cropping. */
	अगर (params->cnv_params.crop_en) अणु
		REG_UPDATE(FC_MODE_CTRL,    FC_WINDOW_CROP_EN, 1);
		REG_UPDATE(FC_WINDOW_START, FC_WINDOW_START_X, params->cnv_params.crop_x);
		REG_UPDATE(FC_WINDOW_START, FC_WINDOW_START_Y, params->cnv_params.crop_y);
		REG_UPDATE(FC_WINDOW_SIZE,  FC_WINDOW_WIDTH,   params->cnv_params.crop_width);
		REG_UPDATE(FC_WINDOW_SIZE,  FC_WINDOW_HEIGHT,  params->cnv_params.crop_height);
	पूर्ण अन्यथा अणु
		REG_UPDATE(FC_MODE_CTRL,    FC_WINDOW_CROP_EN, 0);
	पूर्ण

	/* Set CAPTURE_RATE */
	REG_UPDATE(FC_MODE_CTRL, FC_FRAME_CAPTURE_RATE, params->capture_rate);

	dwb3_set_stereo(dwbc, &params->stereo_params);
पूर्ण

bool dwb3_enable(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);
	DC_LOG_DWB("%s dwb3_enabled at inst = %d", __func__, dwbc->inst);

	/* Set WB_ENABLE (not द्विगुन buffered; capture not enabled) */
	REG_UPDATE(DWB_ENABLE_CLK_CTRL, DWB_ENABLE, 1);

	/* Set FC parameters */
	dwb3_config_fc(dwbc, params);

	/* Program color processing unit */
	dwb3_program_hdr_mult(dwbc, params);
	dwb3_set_gamut_remap(dwbc, params);
	dwb3_ogam_set_input_transfer_func(dwbc, params->out_transfer_func);

	/* Program output denorm */
	dwb3_set_denorm(dwbc, params);

	/* Enable DWB capture enable (द्विगुन buffered) */
	REG_UPDATE(FC_MODE_CTRL, FC_FRAME_CAPTURE_EN, DWB_FRAME_CAPTURE_ENABLE);

	/* First pixel count */
	REG_UPDATE(FC_FLOW_CTRL, FC_FIRST_PIXEL_DELAY_COUNT, 96);

	वापस true;
पूर्ण

bool dwb3_disable(काष्ठा dwbc *dwbc)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	/* disable FC */
	REG_UPDATE(FC_MODE_CTRL, FC_FRAME_CAPTURE_EN, DWB_FRAME_CAPTURE_DISABLE);

	/* disable WB */
	REG_UPDATE(DWB_ENABLE_CLK_CTRL, DWB_ENABLE, 0);

	DC_LOG_DWB("%s dwb3_disabled at inst = %d", __func__, dwbc->inst);
	वापस true;
पूर्ण

bool dwb3_update(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);
	अचिन्हित पूर्णांक pre_locked;

	/*
	 * Check अगर the caller has alपढ़ोy locked DWB रेजिस्टरs.
	 * If so: assume the caller will unlock, so करोn't touch the lock.
	 * If not: lock them क्रम this update, then unlock after the
	 * update is complete.
	 */
	REG_GET(DWB_UPDATE_CTRL, DWB_UPDATE_LOCK, &pre_locked);
	DC_LOG_DWB("%s dwb update, inst = %d", __func__, dwbc->inst);

	अगर (pre_locked == 0) अणु
		/* Lock DWB रेजिस्टरs */
		REG_UPDATE(DWB_UPDATE_CTRL, DWB_UPDATE_LOCK, 1);
	पूर्ण

	/* Set FC parameters */
	dwb3_config_fc(dwbc, params);

	/* Program color processing unit */
	dwb3_program_hdr_mult(dwbc, params);
	dwb3_set_gamut_remap(dwbc, params);
	dwb3_ogam_set_input_transfer_func(dwbc, params->out_transfer_func);

	/* Program output denorm */
	dwb3_set_denorm(dwbc, params);

	अगर (pre_locked == 0) अणु
		/* Unlock DWB रेजिस्टरs */
		REG_UPDATE(DWB_UPDATE_CTRL, DWB_UPDATE_LOCK, 0);
	पूर्ण

	वापस true;
पूर्ण

bool dwb3_is_enabled(काष्ठा dwbc *dwbc)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);
	अचिन्हित पूर्णांक dwb_enabled = 0;
	अचिन्हित पूर्णांक fc_frame_capture_en = 0;

	REG_GET(DWB_ENABLE_CLK_CTRL, DWB_ENABLE, &dwb_enabled);
	REG_GET(FC_MODE_CTRL, FC_FRAME_CAPTURE_EN, &fc_frame_capture_en);

	वापस ((dwb_enabled != 0) && (fc_frame_capture_en != 0));
पूर्ण

व्योम dwb3_set_stereo(काष्ठा dwbc *dwbc,
		काष्ठा dwb_stereo_params *stereo_params)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	अगर (stereo_params->stereo_enabled) अणु
		REG_UPDATE(FC_MODE_CTRL, FC_EYE_SELECTION,       stereo_params->stereo_eye_select);
		REG_UPDATE(FC_MODE_CTRL, FC_STEREO_EYE_POLARITY, stereo_params->stereo_polarity);
		DC_LOG_DWB("%s dwb stereo enabled", __func__);
	पूर्ण अन्यथा अणु
		REG_UPDATE(FC_MODE_CTRL, FC_EYE_SELECTION, 0);
		DC_LOG_DWB("%s dwb stereo disabled", __func__);
	पूर्ण
पूर्ण

व्योम dwb3_set_new_content(काष्ठा dwbc *dwbc,
						bool is_new_content)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	REG_UPDATE(FC_MODE_CTRL, FC_NEW_CONTENT, is_new_content);
पूर्ण

व्योम dwb3_set_denorm(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	/* Set output क्रमmat*/
	REG_UPDATE(DWB_OUT_CTRL, OUT_FORMAT, params->cnv_params.fc_out_क्रमmat);

	/* Set output denorm */
	अगर (params->cnv_params.fc_out_क्रमmat == DWB_OUT_FORMAT_32BPP_ARGB ||
			params->cnv_params.fc_out_क्रमmat == DWB_OUT_FORMAT_32BPP_RGBA) अणु
		REG_UPDATE(DWB_OUT_CTRL, OUT_DENORM, params->cnv_params.out_denorm_mode);
		REG_UPDATE(DWB_OUT_CTRL, OUT_MAX,    params->cnv_params.out_max_pix_val);
		REG_UPDATE(DWB_OUT_CTRL, OUT_MIN,    params->cnv_params.out_min_pix_val);
	पूर्ण
पूर्ण


स्थिर काष्ठा dwbc_funcs dcn30_dwbc_funcs = अणु
	.get_caps		= dwb3_get_caps,
	.enable			= dwb3_enable,
	.disable		= dwb3_disable,
	.update			= dwb3_update,
	.is_enabled		= dwb3_is_enabled,
	.set_stereo		= dwb3_set_stereo,
	.set_new_content	= dwb3_set_new_content,
	.dwb_program_output_csc	= शून्य,
	.dwb_ogam_set_input_transfer_func	= dwb3_ogam_set_input_transfer_func, //TODO: नाम
	.dwb_set_scaler		= शून्य,
पूर्ण;

व्योम dcn30_dwbc_स्थिरruct(काष्ठा dcn30_dwbc *dwbc30,
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dcn30_dwbc_रेजिस्टरs *dwbc_regs,
		स्थिर काष्ठा dcn30_dwbc_shअगरt *dwbc_shअगरt,
		स्थिर काष्ठा dcn30_dwbc_mask *dwbc_mask,
		पूर्णांक inst)
अणु
	dwbc30->base.ctx = ctx;

	dwbc30->base.inst = inst;
	dwbc30->base.funcs = &dcn30_dwbc_funcs;

	dwbc30->dwbc_regs = dwbc_regs;
	dwbc30->dwbc_shअगरt = dwbc_shअगरt;
	dwbc30->dwbc_mask = dwbc_mask;
पूर्ण

व्योम dwb3_set_host_पढ़ो_rate_control(काष्ठा dwbc *dwbc, bool host_पढ़ो_delay)
अणु
	काष्ठा dcn30_dwbc *dwbc30 = TO_DCN30_DWBC(dwbc);

	/*
	 * Set maximum delay of host पढ़ो access to DWBSCL LUT or OGAM LUT अगर there are no
	 * idle cycles in HW pipeline (in number of घड़ी cycles बार 4)
	 */
	REG_UPDATE(DWB_HOST_READ_CONTROL, DWB_HOST_READ_RATE_CONTROL, host_पढ़ो_delay);

	DC_LOG_DWB("%s dwb3_rate_control at inst = %d", __func__, dwbc->inst);
पूर्ण
