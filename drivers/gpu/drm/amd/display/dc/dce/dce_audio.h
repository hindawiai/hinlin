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
#अगर_अघोषित __DAL_AUDIO_DCE_110_H__
#घोषणा __DAL_AUDIO_DCE_110_H__

#समावेश "audio.h"

#घोषणा AUD_COMMON_REG_LIST(id)\
	SRI(AZALIA_F0_CODEC_ENDPOINT_INDEX, AZF0ENDPOINT, id),\
	SRI(AZALIA_F0_CODEC_ENDPOINT_DATA, AZF0ENDPOINT, id),\
	SR(AZALIA_F0_CODEC_FUNCTION_PARAMETER_STREAM_FORMATS),\
	SR(AZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES),\
	SR(AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES),\
	SR(DCCG_AUDIO_DTO_SOURCE),\
	SR(DCCG_AUDIO_DTO0_MODULE),\
	SR(DCCG_AUDIO_DTO0_PHASE),\
	SR(DCCG_AUDIO_DTO1_MODULE),\
	SR(DCCG_AUDIO_DTO1_PHASE)


 /* set field name */
#घोषणा SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix


#घोषणा AUD_COMMON_MASK_SH_LIST_BASE(mask_sh)\
		SF(DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO0_SOURCE_SEL, mask_sh),\
		SF(DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO_SEL, mask_sh),\
		SF(DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO2_USE_512FBR_DTO, mask_sh),\
		SF(DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO0_USE_512FBR_DTO, mask_sh),\
		SF(DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO1_USE_512FBR_DTO, mask_sh),\
		SF(DCCG_AUDIO_DTO0_MODULE, DCCG_AUDIO_DTO0_MODULE, mask_sh),\
		SF(DCCG_AUDIO_DTO0_PHASE, DCCG_AUDIO_DTO0_PHASE, mask_sh),\
		SF(DCCG_AUDIO_DTO1_MODULE, DCCG_AUDIO_DTO1_MODULE, mask_sh),\
		SF(DCCG_AUDIO_DTO1_PHASE, DCCG_AUDIO_DTO1_PHASE, mask_sh),\
		SF(AZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES, AUDIO_RATE_CAPABILITIES, mask_sh),\
		SF(AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES, CLKSTOP, mask_sh),\
		SF(AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES, EPSS, mask_sh)

#घोषणा AUD_COMMON_MASK_SH_LIST(mask_sh)\
		AUD_COMMON_MASK_SH_LIST_BASE(mask_sh),\
		SF(AZALIA_F0_CODEC_ENDPOINT_INDEX, AZALIA_ENDPOINT_REG_INDEX, mask_sh),\
		SF(AZALIA_F0_CODEC_ENDPOINT_DATA, AZALIA_ENDPOINT_REG_DATA, mask_sh)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा AUD_DCE60_MASK_SH_LIST(mask_sh)\
		SF(DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO0_SOURCE_SEL, mask_sh),\
		SF(DCCG_AUDIO_DTO_SOURCE, DCCG_AUDIO_DTO_SEL, mask_sh),\
		SF(DCCG_AUDIO_DTO0_MODULE, DCCG_AUDIO_DTO0_MODULE, mask_sh),\
		SF(DCCG_AUDIO_DTO0_PHASE, DCCG_AUDIO_DTO0_PHASE, mask_sh),\
		SF(DCCG_AUDIO_DTO1_MODULE, DCCG_AUDIO_DTO1_MODULE, mask_sh),\
		SF(DCCG_AUDIO_DTO1_PHASE, DCCG_AUDIO_DTO1_PHASE, mask_sh),\
		SF(AZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES, AUDIO_RATE_CAPABILITIES, mask_sh),\
		SF(AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES, CLKSTOP, mask_sh),\
		SF(AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES, EPSS, mask_sh), \
		SF(AZALIA_F0_CODEC_ENDPOINT_INDEX, AZALIA_ENDPOINT_REG_INDEX, mask_sh),\
		SF(AZALIA_F0_CODEC_ENDPOINT_DATA, AZALIA_ENDPOINT_REG_DATA, mask_sh)
#पूर्ण_अगर

काष्ठा dce_audio_रेजिस्टरs अणु
	uपूर्णांक32_t AZALIA_F0_CODEC_ENDPOINT_INDEX;
	uपूर्णांक32_t AZALIA_F0_CODEC_ENDPOINT_DATA;

	uपूर्णांक32_t AZALIA_F0_CODEC_FUNCTION_PARAMETER_STREAM_FORMATS;
	uपूर्णांक32_t AZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES;
	uपूर्णांक32_t AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES;

	uपूर्णांक32_t DCCG_AUDIO_DTO_SOURCE;
	uपूर्णांक32_t DCCG_AUDIO_DTO0_MODULE;
	uपूर्णांक32_t DCCG_AUDIO_DTO0_PHASE;
	uपूर्णांक32_t DCCG_AUDIO_DTO1_MODULE;
	uपूर्णांक32_t DCCG_AUDIO_DTO1_PHASE;

	uपूर्णांक32_t AUDIO_RATE_CAPABILITIES;
पूर्ण;

काष्ठा dce_audio_shअगरt अणु
	uपूर्णांक8_t AZALIA_ENDPOINT_REG_INDEX;
	uपूर्णांक8_t AZALIA_ENDPOINT_REG_DATA;

	uपूर्णांक8_t AUDIO_RATE_CAPABILITIES;
	uपूर्णांक8_t CLKSTOP;
	uपूर्णांक8_t EPSS;

	uपूर्णांक8_t DCCG_AUDIO_DTO0_SOURCE_SEL;
	uपूर्णांक8_t DCCG_AUDIO_DTO_SEL;
	uपूर्णांक8_t DCCG_AUDIO_DTO0_MODULE;
	uपूर्णांक8_t DCCG_AUDIO_DTO0_PHASE;
	uपूर्णांक8_t DCCG_AUDIO_DTO1_MODULE;
	uपूर्णांक8_t DCCG_AUDIO_DTO1_PHASE;
	uपूर्णांक8_t DCCG_AUDIO_DTO2_USE_512FBR_DTO;
	uपूर्णांक32_t DCCG_AUDIO_DTO0_USE_512FBR_DTO;
	uपूर्णांक32_t DCCG_AUDIO_DTO1_USE_512FBR_DTO;
पूर्ण;

काष्ठा dce_audio_mask अणु
	uपूर्णांक32_t AZALIA_ENDPOINT_REG_INDEX;
	uपूर्णांक32_t AZALIA_ENDPOINT_REG_DATA;

	uपूर्णांक32_t AUDIO_RATE_CAPABILITIES;
	uपूर्णांक32_t CLKSTOP;
	uपूर्णांक32_t EPSS;

	uपूर्णांक32_t DCCG_AUDIO_DTO0_SOURCE_SEL;
	uपूर्णांक32_t DCCG_AUDIO_DTO_SEL;
	uपूर्णांक32_t DCCG_AUDIO_DTO0_MODULE;
	uपूर्णांक32_t DCCG_AUDIO_DTO0_PHASE;
	uपूर्णांक32_t DCCG_AUDIO_DTO1_MODULE;
	uपूर्णांक32_t DCCG_AUDIO_DTO1_PHASE;
	uपूर्णांक32_t DCCG_AUDIO_DTO2_USE_512FBR_DTO;
	uपूर्णांक32_t DCCG_AUDIO_DTO0_USE_512FBR_DTO;
	uपूर्णांक32_t DCCG_AUDIO_DTO1_USE_512FBR_DTO;

पूर्ण;

काष्ठा dce_audio अणु
	काष्ठा audio base;
	स्थिर काष्ठा dce_audio_रेजिस्टरs *regs;
	स्थिर काष्ठा dce_audio_shअगरt *shअगरts;
	स्थिर काष्ठा dce_audio_mask *masks;
पूर्ण;

काष्ठा audio *dce_audio_create(
		काष्ठा dc_context *ctx,
		अचिन्हित पूर्णांक inst,
		स्थिर काष्ठा dce_audio_रेजिस्टरs *reg,
		स्थिर काष्ठा dce_audio_shअगरt *shअगरts,
		स्थिर काष्ठा dce_audio_mask *masks);

#अगर defined(CONFIG_DRM_AMD_DC_SI)
काष्ठा audio *dce60_audio_create(
		काष्ठा dc_context *ctx,
		अचिन्हित पूर्णांक inst,
		स्थिर काष्ठा dce_audio_रेजिस्टरs *reg,
		स्थिर काष्ठा dce_audio_shअगरt *shअगरts,
		स्थिर काष्ठा dce_audio_mask *masks);
#पूर्ण_अगर

व्योम dce_aud_destroy(काष्ठा audio **audio);

व्योम dce_aud_hw_init(काष्ठा audio *audio);

व्योम dce_aud_az_enable(काष्ठा audio *audio);
व्योम dce_aud_az_disable(काष्ठा audio *audio);

व्योम dce_aud_az_configure(काष्ठा audio *audio,
	क्रमागत संकेत_type संकेत,
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	स्थिर काष्ठा audio_info *audio_info);

व्योम dce_aud_wall_dto_setup(काष्ठा audio *audio,
	क्रमागत संकेत_type संकेत,
	स्थिर काष्ठा audio_crtc_info *crtc_info,
	स्थिर काष्ठा audio_pll_info *pll_info);

#पूर्ण_अगर   /*__DAL_AUDIO_DCE_110_H__*/
