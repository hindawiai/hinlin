<शैली गुरु>
/*
 * Copyright 2012-17 Advanced Micro Devices, Inc.
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
#समावेश "dcn20_dwb.h"


#घोषणा REG(reg)\
	dwbc20->dwbc_regs->reg

#घोषणा CTX \
	dwbc20->base.ctx

#घोषणा DC_LOGGER \
	dwbc20->base.ctx->logger
#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dwbc20->dwbc_shअगरt->field_name, dwbc20->dwbc_mask->field_name

क्रमागत dwb_outside_pix_strategy अणु
	DWB_OUTSIDE_PIX_STRATEGY_BLACK = 0,
	DWB_OUTSIDE_PIX_STRATEGY_EDGE  = 1
पूर्ण;

अटल bool dwb2_get_caps(काष्ठा dwbc *dwbc, काष्ठा dwb_caps *caps)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	अगर (caps) अणु
		caps->adapter_id = 0;	/* we only support 1 adapter currently */
		caps->hw_version = DCN_VERSION_2_0;
		caps->num_pipes = 1;
		स_रखो(&caps->reserved, 0, माप(caps->reserved));
		स_रखो(&caps->reserved2, 0, माप(caps->reserved2));
		caps->sw_version = dwb_ver_1_0;
		caps->caps.support_dwb = true;
		caps->caps.support_ogam = false;
		caps->caps.support_wbscl = false;
		caps->caps.support_ocsc = false;
		DC_LOG_DWB("%s SUPPORTED! inst = %d", __func__, dwbc20->base.inst);
		वापस true;
	पूर्ण अन्यथा अणु
		DC_LOG_DWB("%s NOT SUPPORTED! inst = %d", __func__, dwbc20->base.inst);
		वापस false;
	पूर्ण
पूर्ण

व्योम dwb2_config_dwb_cnv(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_LOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	/* Set DWB source size */
	REG_UPDATE_2(CNV_SOURCE_SIZE, CNV_SOURCE_WIDTH, params->cnv_params.src_width,
			CNV_SOURCE_HEIGHT, params->cnv_params.src_height);

	/* source size is not equal the source size, then enable cropping. */
	अगर (params->cnv_params.crop_en) अणु
		REG_UPDATE(CNV_MODE, CNV_WINDOW_CROP_EN, 1);
		REG_UPDATE(CNV_WINDOW_START, CNV_WINDOW_START_X, params->cnv_params.crop_x);
		REG_UPDATE(CNV_WINDOW_START, CNV_WINDOW_START_Y, params->cnv_params.crop_y);
		REG_UPDATE(CNV_WINDOW_SIZE,  CNV_WINDOW_WIDTH,   params->cnv_params.crop_width);
		REG_UPDATE(CNV_WINDOW_SIZE,  CNV_WINDOW_HEIGHT,  params->cnv_params.crop_height);
	पूर्ण अन्यथा अणु
		REG_UPDATE(CNV_MODE, CNV_WINDOW_CROP_EN, 0);
	पूर्ण

	/* Set CAPTURE_RATE */
	REG_UPDATE(CNV_MODE, CNV_FRAME_CAPTURE_RATE, params->capture_rate);

	/* Set CNV output pixel depth */
	REG_UPDATE(CNV_MODE, CNV_OUT_BPC, params->cnv_params.cnv_out_bpc);
पूर्ण

अटल bool dwb2_enable(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);

	/* Only chroma scaling (sub-sampling) is supported in DCN2 */
अगर ((params->cnv_params.src_width  != params->dest_width) ||
		(params->cnv_params.src_height != params->dest_height)) अणु

		DC_LOG_DWB("%s inst = %d, FAILED!LUMA SCALING NOT SUPPORTED", __func__, dwbc20->base.inst);
		वापस false;
	पूर्ण
	DC_LOG_DWB("%s inst = %d, ENABLED", __func__, dwbc20->base.inst);

	/* disable घातer gating */
	//REG_UPDATE_5(WB_EC_CONFIG, DISPCLK_R_WB_GATE_DIS, 1,
	//			 DISPCLK_G_WB_GATE_DIS, 1, DISPCLK_G_WBSCL_GATE_DIS, 1,
	//			 WB_LB_LS_DIS, 1, WB_LUT_LS_DIS, 1);

	/* Set WB_ENABLE (not द्विगुन buffered; capture not enabled) */
	REG_UPDATE(WB_ENABLE, WB_ENABLE, 1);

	/* Set CNV parameters */
	dwb2_config_dwb_cnv(dwbc, params);

	/* Set scaling parameters */
	dwb2_set_scaler(dwbc, params);

	/* Enable DWB capture enable (द्विगुन buffered) */
	REG_UPDATE(CNV_MODE, CNV_FRAME_CAPTURE_EN, DWB_FRAME_CAPTURE_ENABLE);

	// disable warmup
	REG_UPDATE(WB_WARM_UP_MODE_CTL1, GMC_WARM_UP_ENABLE, 0);

	वापस true;
पूर्ण

bool dwb2_disable(काष्ठा dwbc *dwbc)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_LOG_DWB("%s inst = %d, Disabled", __func__, dwbc20->base.inst);

	/* disable CNV */
	REG_UPDATE(CNV_MODE, CNV_FRAME_CAPTURE_EN, DWB_FRAME_CAPTURE_DISABLE);

	/* disable WB */
	REG_UPDATE(WB_ENABLE, WB_ENABLE, 0);

	/* soft reset */
	REG_UPDATE(WB_SOFT_RESET, WB_SOFT_RESET, 1);
	REG_UPDATE(WB_SOFT_RESET, WB_SOFT_RESET, 0);

	/* enable घातer gating */
	//REG_UPDATE_5(WB_EC_CONFIG, DISPCLK_R_WB_GATE_DIS, 0,
	//			 DISPCLK_G_WB_GATE_DIS, 0, DISPCLK_G_WBSCL_GATE_DIS, 0,
	//			 WB_LB_LS_DIS, 0, WB_LUT_LS_DIS, 0);

	वापस true;
पूर्ण

अटल bool dwb2_update(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	अचिन्हित पूर्णांक pre_locked;

	/* Only chroma scaling (sub-sampling) is supported in DCN2 */
	अगर ((params->cnv_params.src_width != params->dest_width) ||
			(params->cnv_params.src_height != params->dest_height)) अणु
		DC_LOG_DWB("%s inst = %d, FAILED!LUMA SCALING NOT SUPPORTED", __func__, dwbc20->base.inst);
		वापस false;
	पूर्ण
	DC_LOG_DWB("%s inst = %d, scaling", __func__, dwbc20->base.inst);

	/*
	 * Check अगर the caller has alपढ़ोy locked CNV रेजिस्टरs.
	 * If so: assume the caller will unlock, so करोn't touch the lock.
	 * If not: lock them क्रम this update, then unlock after the
	 * update is complete.
	 */
	REG_GET(CNV_UPDATE, CNV_UPDATE_LOCK, &pre_locked);

	अगर (pre_locked == 0) अणु
		/* Lock DWB रेजिस्टरs */
		REG_UPDATE(CNV_UPDATE, CNV_UPDATE_LOCK, 1);
	पूर्ण

	/* Set CNV parameters */
	dwb2_config_dwb_cnv(dwbc, params);

	/* Set scaling parameters */
	dwb2_set_scaler(dwbc, params);

	अगर (pre_locked == 0) अणु
		/* Unlock DWB रेजिस्टरs */
		REG_UPDATE(CNV_UPDATE, CNV_UPDATE_LOCK, 0);
	पूर्ण

	वापस true;
पूर्ण

bool dwb2_is_enabled(काष्ठा dwbc *dwbc)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	अचिन्हित पूर्णांक wb_enabled = 0;
	अचिन्हित पूर्णांक cnv_frame_capture_en = 0;

	REG_GET(WB_ENABLE, WB_ENABLE, &wb_enabled);
	REG_GET(CNV_MODE, CNV_FRAME_CAPTURE_EN, &cnv_frame_capture_en);

	वापस ((wb_enabled != 0) && (cnv_frame_capture_en != 0));
पूर्ण

व्योम dwb2_set_stereo(काष्ठा dwbc *dwbc,
		काष्ठा dwb_stereo_params *stereo_params)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_LOG_DWB("%s inst = %d, enabled =%d", __func__,\
		dwbc20->base.inst, stereo_params->stereo_enabled);

	अगर (stereo_params->stereo_enabled) अणु
		REG_UPDATE(CNV_MODE, CNV_STEREO_TYPE,     stereo_params->stereo_type);
		REG_UPDATE(CNV_MODE, CNV_EYE_SELECTION,   stereo_params->stereo_eye_select);
		REG_UPDATE(CNV_MODE, CNV_STEREO_POLARITY, stereo_params->stereo_polarity);
	पूर्ण अन्यथा अणु
		REG_UPDATE(CNV_MODE, CNV_EYE_SELECTION, 0);
	पूर्ण
पूर्ण

व्योम dwb2_set_new_content(काष्ठा dwbc *dwbc,
						bool is_new_content)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_LOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	REG_UPDATE(CNV_MODE, CNV_NEW_CONTENT, is_new_content);
पूर्ण

अटल व्योम dwb2_set_warmup(काष्ठा dwbc *dwbc,
		काष्ठा dwb_warmup_params *warmup_params)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_LOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	REG_UPDATE(WB_WARM_UP_MODE_CTL1, GMC_WARM_UP_ENABLE, warmup_params->warmup_en);
	REG_UPDATE(WB_WARM_UP_MODE_CTL1, WIDTH_WARMUP, warmup_params->warmup_width);
	REG_UPDATE(WB_WARM_UP_MODE_CTL1, HEIGHT_WARMUP, warmup_params->warmup_height);

	REG_UPDATE(WB_WARM_UP_MODE_CTL2, DATA_VALUE_WARMUP, warmup_params->warmup_data);
	REG_UPDATE(WB_WARM_UP_MODE_CTL2, MODE_WARMUP, warmup_params->warmup_mode);
	REG_UPDATE(WB_WARM_UP_MODE_CTL2, DATA_DEPTH_WARMUP, warmup_params->warmup_depth);
पूर्ण

व्योम dwb2_set_scaler(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn20_dwbc *dwbc20 = TO_DCN20_DWBC(dwbc);
	DC_LOG_DWB("%s inst = %d", __func__, dwbc20->base.inst);

	/* Program scaling mode */
	REG_UPDATE_2(WBSCL_MODE, WBSCL_MODE, params->out_क्रमmat,
			WBSCL_OUT_BIT_DEPTH, params->output_depth);

	अगर (params->out_क्रमmat != dwb_scaler_mode_bypass444) अणु
		/* Program output size */
		REG_UPDATE(WBSCL_DEST_SIZE, WBSCL_DEST_WIDTH,	params->dest_width);
		REG_UPDATE(WBSCL_DEST_SIZE, WBSCL_DEST_HEIGHT,	params->dest_height);

		/* Program round offsets */
		REG_UPDATE(WBSCL_ROUND_OFFSET, WBSCL_ROUND_OFFSET_Y_RGB, 0x40);
		REG_UPDATE(WBSCL_ROUND_OFFSET, WBSCL_ROUND_OFFSET_CBCR,  0x200);

		/* Program clamp values */
		REG_UPDATE(WBSCL_CLAMP_Y_RGB,	WBSCL_CLAMP_UPPER_Y_RGB,	0x3fe);
		REG_UPDATE(WBSCL_CLAMP_Y_RGB,	WBSCL_CLAMP_LOWER_Y_RGB,	0x1);
		REG_UPDATE(WBSCL_CLAMP_CBCR,	WBSCL_CLAMP_UPPER_CBCR,		0x3fe);
		REG_UPDATE(WBSCL_CLAMP_CBCR,	WBSCL_CLAMP_LOWER_CBCR,		0x1);

		/* Program outside pixel strategy to use edge pixels */
		REG_UPDATE(WBSCL_OUTSIDE_PIX_STRATEGY, WBSCL_OUTSIDE_PIX_STRATEGY, DWB_OUTSIDE_PIX_STRATEGY_EDGE);

		अगर (params->cnv_params.crop_en) अणु
			/* horizontal scale */
			dwb_program_horz_scalar(dwbc20, params->cnv_params.crop_width,
							params->dest_width,
							params->scaler_taps);

			/* vertical scale */
			dwb_program_vert_scalar(dwbc20, params->cnv_params.crop_height,
							params->dest_height,
							params->scaler_taps,
							params->subsample_position);
		पूर्ण अन्यथा अणु
			/* horizontal scale */
			dwb_program_horz_scalar(dwbc20, params->cnv_params.src_width,
							params->dest_width,
							params->scaler_taps);

			/* vertical scale */
			dwb_program_vert_scalar(dwbc20, params->cnv_params.src_height,
							params->dest_height,
							params->scaler_taps,
							params->subsample_position);
		पूर्ण
	पूर्ण

पूर्ण

स्थिर काष्ठा dwbc_funcs dcn20_dwbc_funcs = अणु
	.get_caps		= dwb2_get_caps,
	.enable			= dwb2_enable,
	.disable		= dwb2_disable,
	.update			= dwb2_update,
	.is_enabled		= dwb2_is_enabled,
	.set_stereo		= dwb2_set_stereo,
	.set_new_content	= dwb2_set_new_content,
	.set_warmup		= dwb2_set_warmup,
	.dwb_set_scaler		= dwb2_set_scaler,
पूर्ण;

व्योम dcn20_dwbc_स्थिरruct(काष्ठा dcn20_dwbc *dwbc20,
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dcn20_dwbc_रेजिस्टरs *dwbc_regs,
		स्थिर काष्ठा dcn20_dwbc_shअगरt *dwbc_shअगरt,
		स्थिर काष्ठा dcn20_dwbc_mask *dwbc_mask,
		पूर्णांक inst)
अणु
	dwbc20->base.ctx = ctx;

	dwbc20->base.inst = inst;
	dwbc20->base.funcs = &dcn20_dwbc_funcs;

	dwbc20->dwbc_regs = dwbc_regs;
	dwbc20->dwbc_shअगरt = dwbc_shअगरt;
	dwbc20->dwbc_mask = dwbc_mask;
पूर्ण

