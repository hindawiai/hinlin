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

#अगर_अघोषित __DAL_DCN30_AFMT_H__
#घोषणा __DAL_DCN30_AFMT_H__


#घोषणा DCN30_AFMT_FROM_AFMT(afmt)\
	container_of(afmt, काष्ठा dcn30_afmt, base)

#घोषणा AFMT_DCN3_REG_LIST(id) \
	SRI(AFMT_INFOFRAME_CONTROL0, AFMT, id), \
	SRI(AFMT_VBI_PACKET_CONTROL, AFMT, id), \
	SRI(AFMT_AUDIO_PACKET_CONTROL, AFMT, id), \
	SRI(AFMT_AUDIO_PACKET_CONTROL2, AFMT, id), \
	SRI(AFMT_AUDIO_SRC_CONTROL, AFMT, id), \
	SRI(AFMT_60958_0, AFMT, id), \
	SRI(AFMT_60958_1, AFMT, id), \
	SRI(AFMT_60958_2, AFMT, id), \
	SRI(AFMT_MEM_PWR, AFMT, id)

काष्ठा dcn30_afmt_रेजिस्टरs अणु
	uपूर्णांक32_t AFMT_INFOFRAME_CONTROL0;
	uपूर्णांक32_t AFMT_VBI_PACKET_CONTROL;
	uपूर्णांक32_t AFMT_AUDIO_PACKET_CONTROL;
	uपूर्णांक32_t AFMT_AUDIO_PACKET_CONTROL2;
	uपूर्णांक32_t AFMT_AUDIO_SRC_CONTROL;
	uपूर्णांक32_t AFMT_60958_0;
	uपूर्णांक32_t AFMT_60958_1;
	uपूर्णांक32_t AFMT_60958_2;
	uपूर्णांक32_t AFMT_MEM_PWR;
पूर्ण;

#घोषणा DCN3_AFMT_MASK_SH_LIST(mask_sh)\
	SE_SF(AFMT0_AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_SRC_CONTROL, AFMT_AUDIO_SRC_SELECT, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTROL2, AFMT_AUDIO_CHANNEL_ENABLE, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTROL, AFMT_60958_CS_UPDATE, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTROL2, AFMT_AUDIO_LAYOUT_OVRD, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTROL2, AFMT_60958_OSF_OVRD, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_0, AFMT_60958_CS_CHANNEL_NUMBER_L, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_0, AFMT_60958_CS_CLOCK_ACCURACY, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_1, AFMT_60958_CS_CHANNEL_NUMBER_R, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_2, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_3, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_4, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_5, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_6, mask_sh),\
	SE_SF(AFMT0_AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_7, mask_sh),\
	SE_SF(AFMT0_AFMT_AUDIO_PACKET_CONTROL, AFMT_AUDIO_SAMPLE_SEND, mask_sh),\
	SE_SF(AFMT0_AFMT_MEM_PWR, AFMT_MEM_PWR_FORCE, mask_sh)

#घोषणा AFMT_DCN3_REG_FIELD_LIST(type) \
		type AFMT_AUDIO_INFO_UPDATE;\
		type AFMT_AUDIO_SRC_SELECT;\
		type AFMT_AUDIO_CHANNEL_ENABLE;\
		type AFMT_60958_CS_UPDATE;\
		type AFMT_AUDIO_LAYOUT_OVRD;\
		type AFMT_60958_OSF_OVRD;\
		type AFMT_60958_CS_CHANNEL_NUMBER_L;\
		type AFMT_60958_CS_CLOCK_ACCURACY;\
		type AFMT_60958_CS_CHANNEL_NUMBER_R;\
		type AFMT_60958_CS_CHANNEL_NUMBER_2;\
		type AFMT_60958_CS_CHANNEL_NUMBER_3;\
		type AFMT_60958_CS_CHANNEL_NUMBER_4;\
		type AFMT_60958_CS_CHANNEL_NUMBER_5;\
		type AFMT_60958_CS_CHANNEL_NUMBER_6;\
		type AFMT_60958_CS_CHANNEL_NUMBER_7;\
		type AFMT_AUDIO_SAMPLE_SEND;\
		type AFMT_MEM_PWR_FORCE

काष्ठा dcn30_afmt_shअगरt अणु
	AFMT_DCN3_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn30_afmt_mask अणु
	AFMT_DCN3_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;


काष्ठा afmt;

काष्ठा afmt_funcs अणु

	व्योम (*setup_hdmi_audio)(
		काष्ठा afmt *afmt);

	व्योम (*se_audio_setup)(
		काष्ठा afmt *afmt,
		अचिन्हित पूर्णांक az_inst,
		काष्ठा audio_info *audio_info);

	व्योम (*audio_mute_control)(
		काष्ठा afmt *afmt,
		bool mute);

	व्योम (*audio_info_immediate_update)(
		काष्ठा afmt *afmt);

	व्योम (*setup_dp_audio)(
		काष्ठा afmt *afmt);
पूर्ण;

काष्ठा afmt अणु
	स्थिर काष्ठा afmt_funcs *funcs;
	काष्ठा dc_context *ctx;
	पूर्णांक inst;
पूर्ण;

काष्ठा dcn30_afmt अणु
	काष्ठा afmt base;
	स्थिर काष्ठा dcn30_afmt_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn30_afmt_shअगरt *afmt_shअगरt;
	स्थिर काष्ठा dcn30_afmt_mask *afmt_mask;
पूर्ण;

व्योम afmt3_स्थिरruct(काष्ठा dcn30_afmt *afmt3,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn30_afmt_रेजिस्टरs *afmt_regs,
	स्थिर काष्ठा dcn30_afmt_shअगरt *afmt_shअगरt,
	स्थिर काष्ठा dcn30_afmt_mask *afmt_mask);


#पूर्ण_अगर
