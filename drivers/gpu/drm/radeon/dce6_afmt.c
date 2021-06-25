<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
 */
#समावेश <linux/hdmi.h>

#समावेश "dce6_afmt.h"
#समावेश "radeon.h"
#समावेश "radeon_audio.h"
#समावेश "sid.h"

#घोषणा DCE8_DCCG_AUDIO_DTO1_PHASE	0x05b8
#घोषणा DCE8_DCCG_AUDIO_DTO1_MODULE	0x05bc

u32 dce6_endpoपूर्णांक_rreg(काष्ठा radeon_device *rdev,
			      u32 block_offset, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->end_idx_lock, flags);
	WREG32(AZ_F0_CODEC_ENDPOINT_INDEX + block_offset, reg);
	r = RREG32(AZ_F0_CODEC_ENDPOINT_DATA + block_offset);
	spin_unlock_irqrestore(&rdev->end_idx_lock, flags);

	वापस r;
पूर्ण

व्योम dce6_endpoपूर्णांक_wreg(काष्ठा radeon_device *rdev,
			       u32 block_offset, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->end_idx_lock, flags);
	अगर (ASIC_IS_DCE8(rdev))
		WREG32(AZ_F0_CODEC_ENDPOINT_INDEX + block_offset, reg);
	अन्यथा
		WREG32(AZ_F0_CODEC_ENDPOINT_INDEX + block_offset,
		       AZ_ENDPOINT_REG_WRITE_EN | AZ_ENDPOINT_REG_INDEX(reg));
	WREG32(AZ_F0_CODEC_ENDPOINT_DATA + block_offset, v);
	spin_unlock_irqrestore(&rdev->end_idx_lock, flags);
पूर्ण

अटल व्योम dce6_afmt_get_connected_pins(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	u32 offset, पंचांगp;

	क्रम (i = 0; i < rdev->audio.num_pins; i++) अणु
		offset = rdev->audio.pin[i].offset;
		पंचांगp = RREG32_ENDPOINT(offset,
				      AZ_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT);
		अगर (((पंचांगp & PORT_CONNECTIVITY_MASK) >> PORT_CONNECTIVITY_SHIFT) == 1)
			rdev->audio.pin[i].connected = false;
		अन्यथा
			rdev->audio.pin[i].connected = true;
	पूर्ण
पूर्ण

काष्ठा r600_audio_pin *dce6_audio_get_pin(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;
	काष्ठा radeon_encoder_atom_dig *dig;
	काष्ठा r600_audio_pin *pin = शून्य;
	पूर्णांक i, pin_count;

	dce6_afmt_get_connected_pins(rdev);

	क्रम (i = 0; i < rdev->audio.num_pins; i++) अणु
		अगर (rdev->audio.pin[i].connected) अणु
			pin = &rdev->audio.pin[i];
			pin_count = 0;

			list_क्रम_each_entry(encoder, &rdev->ddev->mode_config.encoder_list, head) अणु
				अगर (radeon_encoder_is_digital(encoder)) अणु
					radeon_encoder = to_radeon_encoder(encoder);
					dig = radeon_encoder->enc_priv;
					अगर (dig->pin == pin)
						pin_count++;
				पूर्ण
			पूर्ण

			अगर (pin_count == 0)
				वापस pin;
		पूर्ण
	पूर्ण
	अगर (!pin)
		DRM_ERROR("No connected audio pins found!\n");
	वापस pin;
पूर्ण

व्योम dce6_afmt_select_pin(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	अगर (!dig || !dig->afmt || !dig->pin)
		वापस;

	WREG32(AFMT_AUDIO_SRC_CONTROL +  dig->afmt->offset,
	       AFMT_AUDIO_SRC_SELECT(dig->pin->id));
पूर्ण

व्योम dce6_afmt_ग_लिखो_latency_fields(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_connector *connector,
				    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	u32 पंचांगp = 0;

	अगर (!dig || !dig->afmt || !dig->pin)
		वापस;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		अगर (connector->latency_present[1])
			पंचांगp = VIDEO_LIPSYNC(connector->video_latency[1]) |
				AUDIO_LIPSYNC(connector->audio_latency[1]);
		अन्यथा
			पंचांगp = VIDEO_LIPSYNC(0) | AUDIO_LIPSYNC(0);
	पूर्ण अन्यथा अणु
		अगर (connector->latency_present[0])
			पंचांगp = VIDEO_LIPSYNC(connector->video_latency[0]) |
				AUDIO_LIPSYNC(connector->audio_latency[0]);
		अन्यथा
			पंचांगp = VIDEO_LIPSYNC(0) | AUDIO_LIPSYNC(0);
	पूर्ण
	WREG32_ENDPOINT(dig->pin->offset,
			AZ_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC, पंचांगp);
पूर्ण

व्योम dce6_afmt_hdmi_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					     u8 *sadb, पूर्णांक sad_count)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	u32 पंचांगp;

	अगर (!dig || !dig->afmt || !dig->pin)
		वापस;

	/* program the speaker allocation */
	पंचांगp = RREG32_ENDPOINT(dig->pin->offset,
			      AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER);
	पंचांगp &= ~(DP_CONNECTION | SPEAKER_ALLOCATION_MASK);
	/* set HDMI mode */
	पंचांगp |= HDMI_CONNECTION;
	अगर (sad_count)
		पंचांगp |= SPEAKER_ALLOCATION(sadb[0]);
	अन्यथा
		पंचांगp |= SPEAKER_ALLOCATION(5); /* stereo */
	WREG32_ENDPOINT(dig->pin->offset,
			AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER, पंचांगp);
पूर्ण

व्योम dce6_afmt_dp_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					   u8 *sadb, पूर्णांक sad_count)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	u32 पंचांगp;

	अगर (!dig || !dig->afmt || !dig->pin)
		वापस;

	/* program the speaker allocation */
	पंचांगp = RREG32_ENDPOINT(dig->pin->offset,
			      AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER);
	पंचांगp &= ~(HDMI_CONNECTION | SPEAKER_ALLOCATION_MASK);
	/* set DP mode */
	पंचांगp |= DP_CONNECTION;
	अगर (sad_count)
		पंचांगp |= SPEAKER_ALLOCATION(sadb[0]);
	अन्यथा
		पंचांगp |= SPEAKER_ALLOCATION(5); /* stereo */
	WREG32_ENDPOINT(dig->pin->offset,
			AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER, पंचांगp);
पूर्ण

व्योम dce6_afmt_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder,
			      काष्ठा cea_sad *sads, पूर्णांक sad_count)
अणु
	पूर्णांक i;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	अटल स्थिर u16 eld_reg_to_type[][2] = अणु
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0, HDMI_AUDIO_CODING_TYPE_PCM पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR1, HDMI_AUDIO_CODING_TYPE_AC3 पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR2, HDMI_AUDIO_CODING_TYPE_MPEG1 पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR3, HDMI_AUDIO_CODING_TYPE_MP3 पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR4, HDMI_AUDIO_CODING_TYPE_MPEG2 पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR5, HDMI_AUDIO_CODING_TYPE_AAC_LC पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR6, HDMI_AUDIO_CODING_TYPE_DTS पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR7, HDMI_AUDIO_CODING_TYPE_ATRAC पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR9, HDMI_AUDIO_CODING_TYPE_EAC3 पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR10, HDMI_AUDIO_CODING_TYPE_DTS_HD पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR11, HDMI_AUDIO_CODING_TYPE_MLP पूर्ण,
		अणु AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR13, HDMI_AUDIO_CODING_TYPE_WMA_PRO पूर्ण,
	पूर्ण;

	अगर (!dig || !dig->afmt || !dig->pin)
		वापस;

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

		WREG32_ENDPOINT(dig->pin->offset, eld_reg_to_type[i][0], value);
	पूर्ण
पूर्ण

व्योम dce6_audio_enable(काष्ठा radeon_device *rdev,
		       काष्ठा r600_audio_pin *pin,
		       u8 enable_mask)
अणु
	अगर (!pin)
		वापस;

	WREG32_ENDPOINT(pin->offset, AZ_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			enable_mask ? AUDIO_ENABLED : 0);
पूर्ण

व्योम dce6_hdmi_audio_set_dto(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी)
अणु
	/* Two dtos; generally use dto0 क्रम HDMI */
	u32 value = 0;

	अगर (crtc)
		value |= DCCG_AUDIO_DTO0_SOURCE_SEL(crtc->crtc_id);

	WREG32(DCCG_AUDIO_DTO_SOURCE, value);

	/* Express [24MHz / target pixel घड़ी] as an exact rational
	 * number (coefficient of two पूर्णांकeger numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	WREG32(DCCG_AUDIO_DTO0_PHASE, 24000);
	WREG32(DCCG_AUDIO_DTO0_MODULE, घड़ी);
पूर्ण

व्योम dce6_dp_audio_set_dto(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी)
अणु
	/* Two dtos; generally use dto1 क्रम DP */
	u32 value = 0;
	value |= DCCG_AUDIO_DTO_SEL;

	अगर (crtc)
		value |= DCCG_AUDIO_DTO0_SOURCE_SEL(crtc->crtc_id);

	WREG32(DCCG_AUDIO_DTO_SOURCE, value);

	/* Express [24MHz / target pixel घड़ी] as an exact rational
	 * number (coefficient of two पूर्णांकeger numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	अगर (ASIC_IS_DCE8(rdev)) अणु
		अचिन्हित पूर्णांक भाग = (RREG32(DENTIST_DISPCLK_CNTL) &
			DENTIST_DPREFCLK_WDIVIDER_MASK) >>
			DENTIST_DPREFCLK_WDIVIDER_SHIFT;
		भाग = radeon_audio_decode_dfs_भाग(भाग);

		अगर (भाग)
			घड़ी = घड़ी * 100 / भाग;

		WREG32(DCE8_DCCG_AUDIO_DTO1_PHASE, 24000);
		WREG32(DCE8_DCCG_AUDIO_DTO1_MODULE, घड़ी);
	पूर्ण अन्यथा अणु
		WREG32(DCCG_AUDIO_DTO1_PHASE, 24000);
		WREG32(DCCG_AUDIO_DTO1_MODULE, घड़ी);
	पूर्ण
पूर्ण
