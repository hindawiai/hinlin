<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
 * Copyright 2014 Rafaध Miधecki
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
 */
#समावेश <linux/hdmi.h>

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "r600d.h"

व्योम dce3_2_afmt_hdmi_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
	u8 *sadb, पूर्णांक sad_count)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	u32 पंचांगp;

	/* program the speaker allocation */
	पंचांगp = RREG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTROL_CHANNEL_SPEAKER);
	पंचांगp &= ~(DP_CONNECTION | SPEAKER_ALLOCATION_MASK);
	/* set HDMI mode */
	पंचांगp |= HDMI_CONNECTION;
	अगर (sad_count)
		पंचांगp |= SPEAKER_ALLOCATION(sadb[0]);
	अन्यथा
		पंचांगp |= SPEAKER_ALLOCATION(5); /* stereo */
	WREG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTROL_CHANNEL_SPEAKER, पंचांगp);
पूर्ण

व्योम dce3_2_afmt_dp_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
	u8 *sadb, पूर्णांक sad_count)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	u32 पंचांगp;

	/* program the speaker allocation */
	पंचांगp = RREG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTROL_CHANNEL_SPEAKER);
	पंचांगp &= ~(HDMI_CONNECTION | SPEAKER_ALLOCATION_MASK);
	/* set DP mode */
	पंचांगp |= DP_CONNECTION;
	अगर (sad_count)
		पंचांगp |= SPEAKER_ALLOCATION(sadb[0]);
	अन्यथा
		पंचांगp |= SPEAKER_ALLOCATION(5); /* stereo */
	WREG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTROL_CHANNEL_SPEAKER, पंचांगp);
पूर्ण

व्योम dce3_2_afmt_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder,
	काष्ठा cea_sad *sads, पूर्णांक sad_count)
अणु
	पूर्णांक i;
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	अटल स्थिर u16 eld_reg_to_type[][2] = अणु
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR0, HDMI_AUDIO_CODING_TYPE_PCM पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR1, HDMI_AUDIO_CODING_TYPE_AC3 पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR2, HDMI_AUDIO_CODING_TYPE_MPEG1 पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR3, HDMI_AUDIO_CODING_TYPE_MP3 पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR4, HDMI_AUDIO_CODING_TYPE_MPEG2 पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR5, HDMI_AUDIO_CODING_TYPE_AAC_LC पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR6, HDMI_AUDIO_CODING_TYPE_DTS पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR7, HDMI_AUDIO_CODING_TYPE_ATRAC पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR9, HDMI_AUDIO_CODING_TYPE_EAC3 पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR10, HDMI_AUDIO_CODING_TYPE_DTS_HD पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR11, HDMI_AUDIO_CODING_TYPE_MLP पूर्ण,
		अणु AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR13, HDMI_AUDIO_CODING_TYPE_WMA_PRO पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(eld_reg_to_type); i++) अणु
		u32 value = 0;
		u8 stereo_freqs = 0;
		पूर्णांक max_channels = -1;
		पूर्णांक j;

		क्रम (j = 0; j < sad_count; j++) अणु
			काष्ठा cea_sad *sad = &sads[j];

			अगर (sad->क्रमmat == eld_reg_to_type[i][1]) अणु
				अगर (sad->channels > max_channels) अणु
					value = MAX_CHANNELS(sad->channels) |
						DESCRIPTOR_BYTE_2(sad->byte2) |
						SUPPORTED_FREQUENCIES(sad->freq);
					max_channels = sad->channels;
				पूर्ण

				अगर (sad->क्रमmat == HDMI_AUDIO_CODING_TYPE_PCM)
					stereo_freqs |= sad->freq;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण

		value |= SUPPORTED_FREQUENCIES_STEREO(stereo_freqs);

		WREG32_ENDPOINT(0, eld_reg_to_type[i][0], value);
	पूर्ण
पूर्ण

व्योम dce3_2_audio_set_dto(काष्ठा radeon_device *rdev,
	काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा radeon_encoder *radeon_encoder;
	काष्ठा radeon_encoder_atom_dig *dig;
	अचिन्हित पूर्णांक max_ratio = घड़ी / 24000;
	u32 dto_phase;
	u32 wallघड़ी_ratio;
	u32 dto_cntl;

	अगर (!crtc)
		वापस;

	radeon_encoder = to_radeon_encoder(crtc->encoder);
	dig = radeon_encoder->enc_priv;

	अगर (!dig)
		वापस;

	अगर (max_ratio >= 8) अणु
		dto_phase = 192 * 1000;
		wallघड़ी_ratio = 3;
	पूर्ण अन्यथा अगर (max_ratio >= 4) अणु
		dto_phase = 96 * 1000;
		wallघड़ी_ratio = 2;
	पूर्ण अन्यथा अगर (max_ratio >= 2) अणु
		dto_phase = 48 * 1000;
		wallघड़ी_ratio = 1;
	पूर्ण अन्यथा अणु
		dto_phase = 24 * 1000;
		wallघड़ी_ratio = 0;
	पूर्ण

	/* Express [24MHz / target pixel घड़ी] as an exact rational
	 * number (coefficient of two पूर्णांकeger numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	अगर (dig->dig_encoder == 0) अणु
		dto_cntl = RREG32(DCCG_AUDIO_DTO0_CNTL) & ~DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK;
		dto_cntl |= DCCG_AUDIO_DTO_WALLCLOCK_RATIO(wallघड़ी_ratio);
		WREG32(DCCG_AUDIO_DTO0_CNTL, dto_cntl);
		WREG32(DCCG_AUDIO_DTO0_PHASE, dto_phase);
		WREG32(DCCG_AUDIO_DTO0_MODULE, घड़ी);
		WREG32(DCCG_AUDIO_DTO_SELECT, 0); /* select DTO0 */
	पूर्ण अन्यथा अणु
		dto_cntl = RREG32(DCCG_AUDIO_DTO1_CNTL) & ~DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK;
		dto_cntl |= DCCG_AUDIO_DTO_WALLCLOCK_RATIO(wallघड़ी_ratio);
		WREG32(DCCG_AUDIO_DTO1_CNTL, dto_cntl);
		WREG32(DCCG_AUDIO_DTO1_PHASE, dto_phase);
		WREG32(DCCG_AUDIO_DTO1_MODULE, घड़ी);
		WREG32(DCCG_AUDIO_DTO_SELECT, 1); /* select DTO1 */
	पूर्ण
पूर्ण

व्योम dce3_2_hdmi_update_acr(काष्ठा drm_encoder *encoder, दीर्घ offset,
	स्थिर काष्ठा radeon_hdmi_acr *acr)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	WREG32(DCE3_HDMI0_ACR_PACKET_CONTROL + offset,
		HDMI0_ACR_SOURCE |		/* select SW CTS value */
		HDMI0_ACR_AUTO_SEND);	/* allow hw to sent ACR packets when required */

	WREG32_P(HDMI0_ACR_32_0 + offset,
		HDMI0_ACR_CTS_32(acr->cts_32khz),
		~HDMI0_ACR_CTS_32_MASK);
	WREG32_P(HDMI0_ACR_32_1 + offset,
		HDMI0_ACR_N_32(acr->n_32khz),
		~HDMI0_ACR_N_32_MASK);

	WREG32_P(HDMI0_ACR_44_0 + offset,
		HDMI0_ACR_CTS_44(acr->cts_44_1khz),
		~HDMI0_ACR_CTS_44_MASK);
	WREG32_P(HDMI0_ACR_44_1 + offset,
		HDMI0_ACR_N_44(acr->n_44_1khz),
		~HDMI0_ACR_N_44_MASK);

	WREG32_P(HDMI0_ACR_48_0 + offset,
		HDMI0_ACR_CTS_48(acr->cts_48khz),
		~HDMI0_ACR_CTS_48_MASK);
	WREG32_P(HDMI0_ACR_48_1 + offset,
		HDMI0_ACR_N_48(acr->n_48khz),
		~HDMI0_ACR_N_48_MASK);
पूर्ण

व्योम dce3_2_set_audio_packet(काष्ठा drm_encoder *encoder, u32 offset)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	WREG32(HDMI0_AUDIO_PACKET_CONTROL + offset,
		HDMI0_AUDIO_DELAY_EN(1) |			/* शेष audio delay */
		HDMI0_AUDIO_PACKETS_PER_LINE(3));	/* should be suffient क्रम all audio modes and small enough क्रम all hblanks */

	WREG32(AFMT_AUDIO_PACKET_CONTROL + offset,
		AFMT_AUDIO_SAMPLE_SEND |			/* send audio packets */
		AFMT_60958_CS_UPDATE);				/* allow 60958 channel status fields to be updated */

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		HDMI0_AUDIO_INFO_SEND |				/* enable audio info frames (frames won't be set until audio is enabled) */
		HDMI0_AUDIO_INFO_CONT);				/* send audio info frames every frame/field */

	WREG32_OR(HDMI0_INFOFRAME_CONTROL1 + offset,
		HDMI0_AUDIO_INFO_LINE(2));			/* anything other than 0 */
पूर्ण

व्योम dce3_2_set_mute(काष्ठा drm_encoder *encoder, u32 offset, bool mute)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (mute)
		WREG32_OR(HDMI0_GC + offset, HDMI0_GC_AVMUTE);
	अन्यथा
		WREG32_AND(HDMI0_GC + offset, ~HDMI0_GC_AVMUTE);
पूर्ण
