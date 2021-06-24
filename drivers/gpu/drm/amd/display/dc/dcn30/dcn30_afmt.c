<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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


#समावेश "dc_bios_types.h"
#समावेश "hw_shared.h"
#समावेश "dcn30_afmt.h"
#समावेश "reg_helper.h"

#घोषणा DC_LOGGER \
		afmt3->base.ctx->logger

#घोषणा REG(reg)\
	(afmt3->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	afmt3->afmt_shअगरt->field_name, afmt3->afmt_mask->field_name


#घोषणा CTX \
	afmt3->base.ctx


अटल व्योम afmt3_setup_hdmi_audio(
	काष्ठा afmt *afmt)
अणु
	काष्ठा dcn30_afmt *afmt3 = DCN30_AFMT_FROM_AFMT(afmt);

	/* AFMT_AUDIO_PACKET_CONTROL */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL, AFMT_60958_CS_UPDATE, 1);

	/* AFMT_AUDIO_PACKET_CONTROL2 */
	REG_UPDATE_2(AFMT_AUDIO_PACKET_CONTROL2,
			AFMT_AUDIO_LAYOUT_OVRD, 0,
			AFMT_60958_OSF_OVRD, 0);

	/* AFMT_60958_0__AFMT_60958_CS_CHANNEL_NUMBER_L_MASK &
	 * AFMT_60958_0__AFMT_60958_CS_CLOCK_ACCURACY_MASK
	 */
	REG_UPDATE_2(AFMT_60958_0,
			AFMT_60958_CS_CHANNEL_NUMBER_L, 1,
			AFMT_60958_CS_CLOCK_ACCURACY, 0);

	/* AFMT_60958_1 AFMT_60958_CS_CHALNNEL_NUMBER_R */
	REG_UPDATE(AFMT_60958_1, AFMT_60958_CS_CHANNEL_NUMBER_R, 2);

	/* AFMT_60958_2 now keep this settings until
	 * Programming guide comes out
	 */
	REG_UPDATE_6(AFMT_60958_2,
			AFMT_60958_CS_CHANNEL_NUMBER_2, 3,
			AFMT_60958_CS_CHANNEL_NUMBER_3, 4,
			AFMT_60958_CS_CHANNEL_NUMBER_4, 5,
			AFMT_60958_CS_CHANNEL_NUMBER_5, 6,
			AFMT_60958_CS_CHANNEL_NUMBER_6, 7,
			AFMT_60958_CS_CHANNEL_NUMBER_7, 8);
पूर्ण

अटल जोड़ audio_cea_channels speakers_to_channels(
	काष्ठा audio_speaker_flags speaker_flags)
अणु
	जोड़ audio_cea_channels cea_channels = अणु0पूर्ण;

	/* these are one to one */
	cea_channels.channels.FL = speaker_flags.FL_FR;
	cea_channels.channels.FR = speaker_flags.FL_FR;
	cea_channels.channels.LFE = speaker_flags.LFE;
	cea_channels.channels.FC = speaker_flags.FC;

	/* अगर Rear Left and Right exist move RC speaker to channel 7
	 * otherwise to channel 5
	 */
	अगर (speaker_flags.RL_RR) अणु
		cea_channels.channels.RL_RC = speaker_flags.RL_RR;
		cea_channels.channels.RR = speaker_flags.RL_RR;
		cea_channels.channels.RC_RLC_FLC = speaker_flags.RC;
	पूर्ण अन्यथा अणु
		cea_channels.channels.RL_RC = speaker_flags.RC;
	पूर्ण

	/* FRONT Left Right Center and REAR Left Right Center are exclusive */
	अगर (speaker_flags.FLC_FRC) अणु
		cea_channels.channels.RC_RLC_FLC = speaker_flags.FLC_FRC;
		cea_channels.channels.RRC_FRC = speaker_flags.FLC_FRC;
	पूर्ण अन्यथा अणु
		cea_channels.channels.RC_RLC_FLC = speaker_flags.RLC_RRC;
		cea_channels.channels.RRC_FRC = speaker_flags.RLC_RRC;
	पूर्ण

	वापस cea_channels;
पूर्ण

अटल व्योम afmt3_se_audio_setup(
	काष्ठा afmt *afmt,
	अचिन्हित पूर्णांक az_inst,
	काष्ठा audio_info *audio_info)
अणु
	काष्ठा dcn30_afmt *afmt3 = DCN30_AFMT_FROM_AFMT(afmt);

	uपूर्णांक32_t speakers = 0;
	uपूर्णांक32_t channels = 0;

	ASSERT(audio_info);
	/* This should not happen.it करोes so we करोn't get BSOD*/
	अगर (audio_info == शून्य)
		वापस;

	speakers = audio_info->flags.info.ALLSPEAKERS;
	channels = speakers_to_channels(audio_info->flags.speaker_flags).all;

	/* setup the audio stream source select (audio -> dig mapping) */
	REG_SET(AFMT_AUDIO_SRC_CONTROL, 0, AFMT_AUDIO_SRC_SELECT, az_inst);

	/* Channel allocation */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL2, AFMT_AUDIO_CHANNEL_ENABLE, channels);

	/* Disable क्रमced mem घातer off */
	REG_UPDATE(AFMT_MEM_PWR, AFMT_MEM_PWR_FORCE, 0);
पूर्ण

अटल व्योम afmt3_audio_mute_control(
	काष्ठा afmt *afmt,
	bool mute)
अणु
	काष्ठा dcn30_afmt *afmt3 = DCN30_AFMT_FROM_AFMT(afmt);

	/* enable/disable transmission of audio packets */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL, AFMT_AUDIO_SAMPLE_SEND, !mute);
पूर्ण

अटल व्योम afmt3_audio_info_immediate_update(
	काष्ठा afmt *afmt)
अणु
	काष्ठा dcn30_afmt *afmt3 = DCN30_AFMT_FROM_AFMT(afmt);

	/* update द्विगुन-buffered AUDIO_INFO रेजिस्टरs immediately */
	REG_UPDATE(AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, 1);
पूर्ण

अटल व्योम afmt3_setup_dp_audio(
		काष्ठा afmt *afmt)
अणु
	काष्ठा dcn30_afmt *afmt3 = DCN30_AFMT_FROM_AFMT(afmt);

	/* AFMT_AUDIO_PACKET_CONTROL */
	REG_UPDATE(AFMT_AUDIO_PACKET_CONTROL, AFMT_60958_CS_UPDATE, 1);

	/* AFMT_AUDIO_PACKET_CONTROL2 */
	/* Program the ATP and AIP next */
	REG_UPDATE_2(AFMT_AUDIO_PACKET_CONTROL2,
			AFMT_AUDIO_LAYOUT_OVRD, 0,
			AFMT_60958_OSF_OVRD, 0);

	/* AFMT_INFOFRAME_CONTROL0 */
	REG_UPDATE(AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, 1);

	/* AFMT_60958_0__AFMT_60958_CS_CLOCK_ACCURACY_MASK */
	REG_UPDATE(AFMT_60958_0, AFMT_60958_CS_CLOCK_ACCURACY, 0);
पूर्ण

अटल काष्ठा afmt_funcs dcn30_afmt_funcs = अणु
	.setup_hdmi_audio		= afmt3_setup_hdmi_audio,
	.se_audio_setup			= afmt3_se_audio_setup,
	.audio_mute_control		= afmt3_audio_mute_control,
	.audio_info_immediate_update	= afmt3_audio_info_immediate_update,
	.setup_dp_audio			= afmt3_setup_dp_audio,
पूर्ण;

व्योम afmt3_स्थिरruct(काष्ठा dcn30_afmt *afmt3,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn30_afmt_रेजिस्टरs *afmt_regs,
	स्थिर काष्ठा dcn30_afmt_shअगरt *afmt_shअगरt,
	स्थिर काष्ठा dcn30_afmt_mask *afmt_mask)
अणु
	afmt3->base.ctx = ctx;

	afmt3->base.inst = inst;
	afmt3->base.funcs = &dcn30_afmt_funcs;

	afmt3->regs = afmt_regs;
	afmt3->afmt_shअगरt = afmt_shअगरt;
	afmt3->afmt_mask = afmt_mask;
पूर्ण
