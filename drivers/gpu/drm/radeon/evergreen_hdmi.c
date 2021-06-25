<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Christian Kथघnig.
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
 * Authors: Christian Kथघnig
 *          Rafaध Miधecki
 */
#समावेश <linux/hdmi.h>

#समावेश <drm/radeon_drm.h>
#समावेश "evergreen_hdmi.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "evergreend.h"
#समावेश "atom.h"

/* enable the audio stream */
व्योम dce4_audio_enable(काष्ठा radeon_device *rdev,
			      काष्ठा r600_audio_pin *pin,
			      u8 enable_mask)
अणु
	u32 पंचांगp = RREG32(AZ_HOT_PLUG_CONTROL);

	अगर (!pin)
		वापस;

	अगर (enable_mask) अणु
		पंचांगp |= AUDIO_ENABLED;
		अगर (enable_mask & 1)
			पंचांगp |= PIN0_AUDIO_ENABLED;
		अगर (enable_mask & 2)
			पंचांगp |= PIN1_AUDIO_ENABLED;
		अगर (enable_mask & 4)
			पंचांगp |= PIN2_AUDIO_ENABLED;
		अगर (enable_mask & 8)
			पंचांगp |= PIN3_AUDIO_ENABLED;
	पूर्ण अन्यथा अणु
		पंचांगp &= ~(AUDIO_ENABLED |
			 PIN0_AUDIO_ENABLED |
			 PIN1_AUDIO_ENABLED |
			 PIN2_AUDIO_ENABLED |
			 PIN3_AUDIO_ENABLED);
	पूर्ण

	WREG32(AZ_HOT_PLUG_CONTROL, पंचांगp);
पूर्ण

व्योम evergreen_hdmi_update_acr(काष्ठा drm_encoder *encoder, दीर्घ offset,
	स्थिर काष्ठा radeon_hdmi_acr *acr)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक bpc = 8;

	अगर (encoder->crtc) अणु
		काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
		bpc = radeon_crtc->bpc;
	पूर्ण

	अगर (bpc > 8)
		WREG32(HDMI_ACR_PACKET_CONTROL + offset,
			HDMI_ACR_AUTO_SEND);	/* allow hw to sent ACR packets when required */
	अन्यथा
		WREG32(HDMI_ACR_PACKET_CONTROL + offset,
			HDMI_ACR_SOURCE |		/* select SW CTS value */
			HDMI_ACR_AUTO_SEND);	/* allow hw to sent ACR packets when required */

	WREG32(HDMI_ACR_32_0 + offset, HDMI_ACR_CTS_32(acr->cts_32khz));
	WREG32(HDMI_ACR_32_1 + offset, acr->n_32khz);

	WREG32(HDMI_ACR_44_0 + offset, HDMI_ACR_CTS_44(acr->cts_44_1khz));
	WREG32(HDMI_ACR_44_1 + offset, acr->n_44_1khz);

	WREG32(HDMI_ACR_48_0 + offset, HDMI_ACR_CTS_48(acr->cts_48khz));
	WREG32(HDMI_ACR_48_1 + offset, acr->n_48khz);
पूर्ण

व्योम dce4_afmt_ग_लिखो_latency_fields(काष्ठा drm_encoder *encoder,
		काष्ठा drm_connector *connector, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	u32 पंचांगp = 0;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		अगर (connector->latency_present[1])
			पंचांगp = VIDEO_LIPSYNC(connector->video_latency[1]) |
				AUDIO_LIPSYNC(connector->audio_latency[1]);
		अन्यथा
			पंचांगp = VIDEO_LIPSYNC(255) | AUDIO_LIPSYNC(255);
	पूर्ण अन्यथा अणु
		अगर (connector->latency_present[0])
			पंचांगp = VIDEO_LIPSYNC(connector->video_latency[0]) |
				AUDIO_LIPSYNC(connector->audio_latency[0]);
		अन्यथा
			पंचांगp = VIDEO_LIPSYNC(255) | AUDIO_LIPSYNC(255);
	पूर्ण
	WREG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTROL_RESPONSE_LIPSYNC, पंचांगp);
पूर्ण

व्योम dce4_afmt_hdmi_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
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

व्योम dce4_afmt_dp_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
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

व्योम evergreen_hdmi_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder,
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

/*
 * build a AVI Info Frame
 */
व्योम evergreen_set_avi_packet(काष्ठा radeon_device *rdev, u32 offset,
			      अचिन्हित अक्षर *buffer, माप_प्रकार size)
अणु
	uपूर्णांक8_t *frame = buffer + 3;

	WREG32(AFMT_AVI_INFO0 + offset,
		frame[0x0] | (frame[0x1] << 8) | (frame[0x2] << 16) | (frame[0x3] << 24));
	WREG32(AFMT_AVI_INFO1 + offset,
		frame[0x4] | (frame[0x5] << 8) | (frame[0x6] << 16) | (frame[0x7] << 24));
	WREG32(AFMT_AVI_INFO2 + offset,
		frame[0x8] | (frame[0x9] << 8) | (frame[0xA] << 16) | (frame[0xB] << 24));
	WREG32(AFMT_AVI_INFO3 + offset,
		frame[0xC] | (frame[0xD] << 8) | (buffer[1] << 24));

	WREG32_P(HDMI_INFOFRAME_CONTROL1 + offset,
		 HDMI_AVI_INFO_LINE(2),	/* anything other than 0 */
		 ~HDMI_AVI_INFO_LINE_MASK);
पूर्ण

व्योम dce4_hdmi_audio_set_dto(काष्ठा radeon_device *rdev,
	काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी)
अणु
	अचिन्हित पूर्णांक max_ratio = घड़ी / 24000;
	u32 dto_phase;
	u32 wallघड़ी_ratio;
	u32 value;

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

	value = RREG32(DCCG_AUDIO_DTO0_CNTL) & ~DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK;
	value |= DCCG_AUDIO_DTO_WALLCLOCK_RATIO(wallघड़ी_ratio);
	value &= ~DCCG_AUDIO_DTO1_USE_512FBR_DTO;
	WREG32(DCCG_AUDIO_DTO0_CNTL, value);

	/* Two dtos; generally use dto0 क्रम HDMI */
	value = 0;

	अगर (crtc)
		value |= DCCG_AUDIO_DTO0_SOURCE_SEL(crtc->crtc_id);

	WREG32(DCCG_AUDIO_DTO_SOURCE, value);

	/* Express [24MHz / target pixel घड़ी] as an exact rational
	 * number (coefficient of two पूर्णांकeger numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	WREG32(DCCG_AUDIO_DTO0_PHASE, dto_phase);
	WREG32(DCCG_AUDIO_DTO0_MODULE, घड़ी);
पूर्ण

व्योम dce4_dp_audio_set_dto(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी)
अणु
	u32 value;

	value = RREG32(DCCG_AUDIO_DTO1_CNTL) & ~DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK;
	value |= DCCG_AUDIO_DTO1_USE_512FBR_DTO;
	WREG32(DCCG_AUDIO_DTO1_CNTL, value);

	/* Two dtos; generally use dto1 क्रम DP */
	value = 0;
	value |= DCCG_AUDIO_DTO_SEL;

	अगर (crtc)
		value |= DCCG_AUDIO_DTO0_SOURCE_SEL(crtc->crtc_id);

	WREG32(DCCG_AUDIO_DTO_SOURCE, value);

	/* Express [24MHz / target pixel घड़ी] as an exact rational
	 * number (coefficient of two पूर्णांकeger numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	अगर (ASIC_IS_DCE41(rdev)) अणु
		अचिन्हित पूर्णांक भाग = (RREG32(DCE41_DENTIST_DISPCLK_CNTL) &
			DENTIST_DPREFCLK_WDIVIDER_MASK) >>
			DENTIST_DPREFCLK_WDIVIDER_SHIFT;
		भाग = radeon_audio_decode_dfs_भाग(भाग);

		अगर (भाग)
			घड़ी = 100 * घड़ी / भाग;
	पूर्ण

	WREG32(DCCG_AUDIO_DTO1_PHASE, 24000);
	WREG32(DCCG_AUDIO_DTO1_MODULE, घड़ी);
पूर्ण

व्योम dce4_set_vbi_packet(काष्ठा drm_encoder *encoder, u32 offset)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	WREG32(HDMI_VBI_PACKET_CONTROL + offset,
		HDMI_शून्य_SEND |	/* send null packets when required */
		HDMI_GC_SEND |		/* send general control packets */
		HDMI_GC_CONT);		/* send general control packets every frame */
पूर्ण

व्योम dce4_hdmi_set_color_depth(काष्ठा drm_encoder *encoder, u32 offset, पूर्णांक bpc)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	uपूर्णांक32_t val;

	val = RREG32(HDMI_CONTROL + offset);
	val &= ~HDMI_DEEP_COLOR_ENABLE;
	val &= ~HDMI_DEEP_COLOR_DEPTH_MASK;

	चयन (bpc) अणु
		हाल 0:
		हाल 6:
		हाल 8:
		हाल 16:
		शेष:
			DRM_DEBUG("%s: Disabling hdmi deep color for %d bpc.\n",
					 connector->name, bpc);
			अवरोध;
		हाल 10:
			val |= HDMI_DEEP_COLOR_ENABLE;
			val |= HDMI_DEEP_COLOR_DEPTH(HDMI_30BIT_DEEP_COLOR);
			DRM_DEBUG("%s: Enabling hdmi deep color 30 for 10 bpc.\n",
					 connector->name);
			अवरोध;
		हाल 12:
			val |= HDMI_DEEP_COLOR_ENABLE;
			val |= HDMI_DEEP_COLOR_DEPTH(HDMI_36BIT_DEEP_COLOR);
			DRM_DEBUG("%s: Enabling hdmi deep color 36 for 12 bpc.\n",
					 connector->name);
			अवरोध;
	पूर्ण

	WREG32(HDMI_CONTROL + offset, val);
पूर्ण

व्योम dce4_set_audio_packet(काष्ठा drm_encoder *encoder, u32 offset)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	WREG32(AFMT_INFOFRAME_CONTROL0 + offset,
		AFMT_AUDIO_INFO_UPDATE); /* required क्रम audio info values to be updated */

	WREG32(AFMT_60958_0 + offset,
		AFMT_60958_CS_CHANNEL_NUMBER_L(1));

	WREG32(AFMT_60958_1 + offset,
		AFMT_60958_CS_CHANNEL_NUMBER_R(2));

	WREG32(AFMT_60958_2 + offset,
		AFMT_60958_CS_CHANNEL_NUMBER_2(3) |
		AFMT_60958_CS_CHANNEL_NUMBER_3(4) |
		AFMT_60958_CS_CHANNEL_NUMBER_4(5) |
		AFMT_60958_CS_CHANNEL_NUMBER_5(6) |
		AFMT_60958_CS_CHANNEL_NUMBER_6(7) |
		AFMT_60958_CS_CHANNEL_NUMBER_7(8));

	WREG32(AFMT_AUDIO_PACKET_CONTROL2 + offset,
		AFMT_AUDIO_CHANNEL_ENABLE(0xff));

	WREG32(HDMI_AUDIO_PACKET_CONTROL + offset,
	       HDMI_AUDIO_DELAY_EN(1) | /* set the शेष audio delay */
	       HDMI_AUDIO_PACKETS_PER_LINE(3)); /* should be suffient क्रम all audio modes and small enough क्रम all hblanks */

	/* allow 60958 channel status and send audio packets fields to be updated */
	WREG32_OR(AFMT_AUDIO_PACKET_CONTROL + offset,
		  AFMT_RESET_FIFO_WHEN_AUDIO_DIS | AFMT_60958_CS_UPDATE);
पूर्ण


व्योम dce4_set_mute(काष्ठा drm_encoder *encoder, u32 offset, bool mute)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (mute)
		WREG32_OR(HDMI_GC + offset, HDMI_GC_AVMUTE);
	अन्यथा
		WREG32_AND(HDMI_GC + offset, ~HDMI_GC_AVMUTE);
पूर्ण

व्योम evergreen_hdmi_enable(काष्ठा drm_encoder *encoder, bool enable)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (enable) अणु
		काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);

		अगर (connector && drm_detect_monitor_audio(radeon_connector_edid(connector))) अणु
			WREG32(HDMI_INFOFRAME_CONTROL0 + dig->afmt->offset,
			       HDMI_AVI_INFO_SEND | /* enable AVI info frames */
			       HDMI_AVI_INFO_CONT | /* required क्रम audio info values to be updated */
			       HDMI_AUDIO_INFO_SEND | /* enable audio info frames (frames won't be set until audio is enabled) */
			       HDMI_AUDIO_INFO_CONT); /* required क्रम audio info values to be updated */
			WREG32_OR(AFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset,
				  AFMT_AUDIO_SAMPLE_SEND);
		पूर्ण अन्यथा अणु
			WREG32(HDMI_INFOFRAME_CONTROL0 + dig->afmt->offset,
			       HDMI_AVI_INFO_SEND | /* enable AVI info frames */
			       HDMI_AVI_INFO_CONT); /* required क्रम audio info values to be updated */
			WREG32_AND(AFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset,
				   ~AFMT_AUDIO_SAMPLE_SEND);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32_AND(AFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset,
			   ~AFMT_AUDIO_SAMPLE_SEND);
		WREG32(HDMI_INFOFRAME_CONTROL0 + dig->afmt->offset, 0);
	पूर्ण

	dig->afmt->enabled = enable;

	DRM_DEBUG("%sabling HDMI interface @ 0x%04X for encoder 0x%x\n",
		  enable ? "En" : "Dis", dig->afmt->offset, radeon_encoder->encoder_id);
पूर्ण

व्योम evergreen_dp_enable(काष्ठा drm_encoder *encoder, bool enable)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (enable && connector &&
	    drm_detect_monitor_audio(radeon_connector_edid(connector))) अणु
		काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		काष्ठा radeon_connector_atom_dig *dig_connector;
		uपूर्णांक32_t val;

		WREG32_OR(AFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset,
			  AFMT_AUDIO_SAMPLE_SEND);

		WREG32(EVERGREEN_DP_SEC_TIMESTAMP + dig->afmt->offset,
		       EVERGREEN_DP_SEC_TIMESTAMP_MODE(1));

		अगर (!ASIC_IS_DCE6(rdev) && radeon_connector->con_priv) अणु
			dig_connector = radeon_connector->con_priv;
			val = RREG32(EVERGREEN_DP_SEC_AUD_N + dig->afmt->offset);
			val &= ~EVERGREEN_DP_SEC_N_BASE_MULTIPLE(0xf);

			अगर (dig_connector->dp_घड़ी == 162000)
				val |= EVERGREEN_DP_SEC_N_BASE_MULTIPLE(3);
			अन्यथा
				val |= EVERGREEN_DP_SEC_N_BASE_MULTIPLE(5);

			WREG32(EVERGREEN_DP_SEC_AUD_N + dig->afmt->offset, val);
		पूर्ण

		WREG32(EVERGREEN_DP_SEC_CNTL + dig->afmt->offset,
			EVERGREEN_DP_SEC_ASP_ENABLE |		/* Audio packet transmission */
			EVERGREEN_DP_SEC_ATP_ENABLE |		/* Audio बारtamp packet transmission */
			EVERGREEN_DP_SEC_AIP_ENABLE |		/* Audio infoframe packet transmission */
			EVERGREEN_DP_SEC_STREAM_ENABLE);	/* Master enable क्रम secondary stream engine */
	पूर्ण अन्यथा अणु
		WREG32(EVERGREEN_DP_SEC_CNTL + dig->afmt->offset, 0);
		WREG32_AND(AFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset,
			   ~AFMT_AUDIO_SAMPLE_SEND);
	पूर्ण

	dig->afmt->enabled = enable;
पूर्ण
