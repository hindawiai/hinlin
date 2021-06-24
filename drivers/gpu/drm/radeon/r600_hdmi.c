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
 */
#समावेश <linux/hdmi.h>
#समावेश <linux/gcd.h>

#समावेश <drm/radeon_drm.h>
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "r600.h"
#समावेश "r600d.h"
#समावेश "atom.h"

/*
 * HDMI color क्रमmat
 */
क्रमागत r600_hdmi_color_क्रमmat अणु
	RGB = 0,
	YCC_422 = 1,
	YCC_444 = 2
पूर्ण;

/*
 * IEC60958 status bits
 */
क्रमागत r600_hdmi_iec_status_bits अणु
	AUDIO_STATUS_DIG_ENABLE   = 0x01,
	AUDIO_STATUS_V            = 0x02,
	AUDIO_STATUS_VCFG         = 0x04,
	AUDIO_STATUS_EMPHASIS     = 0x08,
	AUDIO_STATUS_COPYRIGHT    = 0x10,
	AUDIO_STATUS_NONAUDIO     = 0x20,
	AUDIO_STATUS_PROFESSIONAL = 0x40,
	AUDIO_STATUS_LEVEL        = 0x80
पूर्ण;

अटल काष्ठा r600_audio_pin r600_audio_status(काष्ठा radeon_device *rdev)
अणु
	काष्ठा r600_audio_pin status = अणुपूर्ण;
	uपूर्णांक32_t value;

	value = RREG32(R600_AUDIO_RATE_BPS_CHANNEL);

	/* number of channels */
	status.channels = (value & 0x7) + 1;

	/* bits per sample */
	चयन ((value & 0xF0) >> 4) अणु
	हाल 0x0:
		status.bits_per_sample = 8;
		अवरोध;
	हाल 0x1:
		status.bits_per_sample = 16;
		अवरोध;
	हाल 0x2:
		status.bits_per_sample = 20;
		अवरोध;
	हाल 0x3:
		status.bits_per_sample = 24;
		अवरोध;
	हाल 0x4:
		status.bits_per_sample = 32;
		अवरोध;
	शेष:
		dev_err(rdev->dev, "Unknown bits per sample 0x%x, using 16\n",
			(पूर्णांक)value);
		status.bits_per_sample = 16;
	पूर्ण

	/* current sampling rate in HZ */
	अगर (value & 0x4000)
		status.rate = 44100;
	अन्यथा
		status.rate = 48000;
	status.rate *= ((value >> 11) & 0x7) + 1;
	status.rate /= ((value >> 8) & 0x7) + 1;

	value = RREG32(R600_AUDIO_STATUS_BITS);

	/* iec 60958 status bits */
	status.status_bits = value & 0xff;

	/* iec 60958 category code */
	status.category_code = (value >> 8) & 0xff;

	वापस status;
पूर्ण

/*
 * update all hdmi पूर्णांकerfaces with current audio parameters
 */
व्योम r600_audio_update_hdmi(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_device *rdev = container_of(work, काष्ठा radeon_device,
						  audio_work);
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा r600_audio_pin audio_status = r600_audio_status(rdev);
	काष्ठा drm_encoder *encoder;
	bool changed = false;

	अगर (rdev->audio.pin[0].channels != audio_status.channels ||
	    rdev->audio.pin[0].rate != audio_status.rate ||
	    rdev->audio.pin[0].bits_per_sample != audio_status.bits_per_sample ||
	    rdev->audio.pin[0].status_bits != audio_status.status_bits ||
	    rdev->audio.pin[0].category_code != audio_status.category_code) अणु
		rdev->audio.pin[0] = audio_status;
		changed = true;
	पूर्ण

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (!radeon_encoder_is_digital(encoder))
			जारी;
		अगर (changed || r600_hdmi_buffer_status_changed(encoder))
			r600_hdmi_update_audio_settings(encoder);
	पूर्ण
पूर्ण

/* enable the audio stream */
व्योम r600_audio_enable(काष्ठा radeon_device *rdev,
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

काष्ठा r600_audio_pin *r600_audio_get_pin(काष्ठा radeon_device *rdev)
अणु
	/* only one pin on 6xx-NI */
	वापस &rdev->audio.pin[0];
पूर्ण

व्योम r600_hdmi_update_acr(काष्ठा drm_encoder *encoder, दीर्घ offset,
	स्थिर काष्ठा radeon_hdmi_acr *acr)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	/* DCE 3.0 uses रेजिस्टर that's normally क्रम CRC_CONTROL */
	uपूर्णांक32_t acr_ctl = ASIC_IS_DCE3(rdev) ? DCE3_HDMI0_ACR_PACKET_CONTROL :
				       HDMI0_ACR_PACKET_CONTROL;
	WREG32_P(acr_ctl + offset,
		HDMI0_ACR_SOURCE |		/* select SW CTS value */
		HDMI0_ACR_AUTO_SEND,	/* allow hw to sent ACR packets when required */
		~(HDMI0_ACR_SOURCE |
		HDMI0_ACR_AUTO_SEND));

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

/*
 * build a HDMI Video Info Frame
 */
व्योम r600_set_avi_packet(काष्ठा radeon_device *rdev, u32 offset,
			 अचिन्हित अक्षर *buffer, माप_प्रकार size)
अणु
	uपूर्णांक8_t *frame = buffer + 3;

	WREG32(HDMI0_AVI_INFO0 + offset,
		frame[0x0] | (frame[0x1] << 8) | (frame[0x2] << 16) | (frame[0x3] << 24));
	WREG32(HDMI0_AVI_INFO1 + offset,
		frame[0x4] | (frame[0x5] << 8) | (frame[0x6] << 16) | (frame[0x7] << 24));
	WREG32(HDMI0_AVI_INFO2 + offset,
		frame[0x8] | (frame[0x9] << 8) | (frame[0xA] << 16) | (frame[0xB] << 24));
	WREG32(HDMI0_AVI_INFO3 + offset,
		frame[0xC] | (frame[0xD] << 8) | (buffer[1] << 24));

	WREG32_OR(HDMI0_INFOFRAME_CONTROL1 + offset,
		  HDMI0_AVI_INFO_LINE(2));	/* anything other than 0 */

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		  HDMI0_AVI_INFO_SEND |	/* enable AVI info frames */
		  HDMI0_AVI_INFO_CONT);	/* send AVI info frames every frame/field */

पूर्ण

/*
 * build a Audio Info Frame
 */
अटल व्योम r600_hdmi_update_audio_infoframe(काष्ठा drm_encoder *encoder,
					     स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	uपूर्णांक32_t offset = dig->afmt->offset;
	स्थिर u8 *frame = buffer + 3;

	WREG32(HDMI0_AUDIO_INFO0 + offset,
		frame[0x0] | (frame[0x1] << 8) | (frame[0x2] << 16) | (frame[0x3] << 24));
	WREG32(HDMI0_AUDIO_INFO1 + offset,
		frame[0x4] | (frame[0x5] << 8) | (frame[0x6] << 16) | (frame[0x8] << 24));
पूर्ण

/*
 * test अगर audio buffer is filled enough to start playing
 */
अटल bool r600_hdmi_is_audio_buffer_filled(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	uपूर्णांक32_t offset = dig->afmt->offset;

	वापस (RREG32(HDMI0_STATUS + offset) & 0x10) != 0;
पूर्ण

/*
 * have buffer status changed since last call?
 */
पूर्णांक r600_hdmi_buffer_status_changed(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	पूर्णांक status, result;

	अगर (!dig->afmt || !dig->afmt->enabled)
		वापस 0;

	status = r600_hdmi_is_audio_buffer_filled(encoder);
	result = dig->afmt->last_buffer_filled_status != status;
	dig->afmt->last_buffer_filled_status = status;

	वापस result;
पूर्ण

/*
 * ग_लिखो the audio workaround status to the hardware
 */
व्योम r600_hdmi_audio_workaround(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	uपूर्णांक32_t offset = dig->afmt->offset;
	bool hdmi_audio_workaround = false; /* FIXME */
	u32 value;

	अगर (!hdmi_audio_workaround ||
	    r600_hdmi_is_audio_buffer_filled(encoder))
		value = 0; /* disable workaround */
	अन्यथा
		value = HDMI0_AUDIO_TEST_EN; /* enable workaround */
	WREG32_P(HDMI0_AUDIO_PACKET_CONTROL + offset,
		 value, ~HDMI0_AUDIO_TEST_EN);
पूर्ण

व्योम r600_hdmi_audio_set_dto(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा radeon_encoder *radeon_encoder;
	काष्ठा radeon_encoder_atom_dig *dig;

	अगर (!crtc)
		वापस;

	radeon_encoder = to_radeon_encoder(crtc->encoder);
	dig = radeon_encoder->enc_priv;

	अगर (!dig)
		वापस;

	अगर (dig->dig_encoder == 0) अणु
		WREG32(DCCG_AUDIO_DTO0_PHASE, 24000 * 100);
		WREG32(DCCG_AUDIO_DTO0_MODULE, घड़ी * 100);
		WREG32(DCCG_AUDIO_DTO_SELECT, 0); /* select DTO0 */
	पूर्ण अन्यथा अणु
		WREG32(DCCG_AUDIO_DTO1_PHASE, 24000 * 100);
		WREG32(DCCG_AUDIO_DTO1_MODULE, घड़ी * 100);
		WREG32(DCCG_AUDIO_DTO_SELECT, 1); /* select DTO1 */
	पूर्ण
पूर्ण

व्योम r600_set_vbi_packet(काष्ठा drm_encoder *encoder, u32 offset)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	WREG32_OR(HDMI0_VBI_PACKET_CONTROL + offset,
		HDMI0_शून्य_SEND |	/* send null packets when required */
		HDMI0_GC_SEND |		/* send general control packets */
		HDMI0_GC_CONT);		/* send general control packets every frame */
पूर्ण

व्योम r600_set_audio_packet(काष्ठा drm_encoder *encoder, u32 offset)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	WREG32_P(HDMI0_AUDIO_PACKET_CONTROL + offset,
		HDMI0_AUDIO_SAMPLE_SEND |			/* send audio packets */
		HDMI0_AUDIO_DELAY_EN(1) |			/* शेष audio delay */
		HDMI0_AUDIO_PACKETS_PER_LINE(3) |	/* should be suffient क्रम all audio modes and small enough क्रम all hblanks */
		HDMI0_60958_CS_UPDATE,				/* allow 60958 channel status fields to be updated */
		~(HDMI0_AUDIO_SAMPLE_SEND |
		HDMI0_AUDIO_DELAY_EN_MASK |
		HDMI0_AUDIO_PACKETS_PER_LINE_MASK |
		HDMI0_60958_CS_UPDATE));

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		HDMI0_AUDIO_INFO_SEND |		/* enable audio info frames (frames won't be set until audio is enabled) */
		HDMI0_AUDIO_INFO_UPDATE);	/* required क्रम audio info values to be updated */

	WREG32_P(HDMI0_INFOFRAME_CONTROL1 + offset,
		HDMI0_AUDIO_INFO_LINE(2),	/* anything other than 0 */
		~HDMI0_AUDIO_INFO_LINE_MASK);

	WREG32_AND(HDMI0_GENERIC_PACKET_CONTROL + offset,
		~(HDMI0_GENERIC0_SEND |
		HDMI0_GENERIC0_CONT |
		HDMI0_GENERIC0_UPDATE |
		HDMI0_GENERIC1_SEND |
		HDMI0_GENERIC1_CONT |
		HDMI0_GENERIC0_LINE_MASK |
		HDMI0_GENERIC1_LINE_MASK));

	WREG32_P(HDMI0_60958_0 + offset,
		HDMI0_60958_CS_CHANNEL_NUMBER_L(1),
		~(HDMI0_60958_CS_CHANNEL_NUMBER_L_MASK |
		HDMI0_60958_CS_CLOCK_ACCURACY_MASK));

	WREG32_P(HDMI0_60958_1 + offset,
		HDMI0_60958_CS_CHANNEL_NUMBER_R(2),
		~HDMI0_60958_CS_CHANNEL_NUMBER_R_MASK);
पूर्ण

व्योम r600_set_mute(काष्ठा drm_encoder *encoder, u32 offset, bool mute)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (mute)
		WREG32_OR(HDMI0_GC + offset, HDMI0_GC_AVMUTE);
	अन्यथा
		WREG32_AND(HDMI0_GC + offset, ~HDMI0_GC_AVMUTE);
पूर्ण

/**
 * r600_hdmi_update_audio_settings - Update audio infoframe
 *
 * @encoder: drm encoder
 *
 * Gets info about current audio stream and updates audio infoframe.
 */
व्योम r600_hdmi_update_audio_settings(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा r600_audio_pin audio = r600_audio_status(rdev);
	uपूर्णांक8_t buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AUDIO_INFOFRAME_SIZE];
	काष्ठा hdmi_audio_infoframe frame;
	uपूर्णांक32_t offset;
	uपूर्णांक32_t value;
	sमाप_प्रकार err;

	अगर (!dig->afmt || !dig->afmt->enabled)
		वापस;
	offset = dig->afmt->offset;

	DRM_DEBUG("%s with %d channels, %d Hz sampling rate, %d bits per sample,\n",
		 r600_hdmi_is_audio_buffer_filled(encoder) ? "playing" : "stopped",
		  audio.channels, audio.rate, audio.bits_per_sample);
	DRM_DEBUG("0x%02X IEC60958 status bits and 0x%02X category code\n",
		  (पूर्णांक)audio.status_bits, (पूर्णांक)audio.category_code);

	err = hdmi_audio_infoframe_init(&frame);
	अगर (err < 0) अणु
		DRM_ERROR("failed to setup audio infoframe\n");
		वापस;
	पूर्ण

	frame.channels = audio.channels;

	err = hdmi_audio_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		DRM_ERROR("failed to pack audio infoframe\n");
		वापस;
	पूर्ण

	value = RREG32(HDMI0_AUDIO_PACKET_CONTROL + offset);
	अगर (value & HDMI0_AUDIO_TEST_EN)
		WREG32(HDMI0_AUDIO_PACKET_CONTROL + offset,
		       value & ~HDMI0_AUDIO_TEST_EN);

	WREG32_OR(HDMI0_CONTROL + offset,
		  HDMI0_ERROR_ACK);

	WREG32_AND(HDMI0_INFOFRAME_CONTROL0 + offset,
		   ~HDMI0_AUDIO_INFO_SOURCE);

	r600_hdmi_update_audio_infoframe(encoder, buffer, माप(buffer));

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		  HDMI0_AUDIO_INFO_CONT |
		  HDMI0_AUDIO_INFO_UPDATE);
पूर्ण

/*
 * enable the HDMI engine
 */
व्योम r600_hdmi_enable(काष्ठा drm_encoder *encoder, bool enable)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	u32 hdmi = HDMI0_ERROR_ACK;

	अगर (!dig || !dig->afmt)
		वापस;

	/* Older chipsets require setting HDMI and routing manually */
	अगर (!ASIC_IS_DCE3(rdev)) अणु
		अगर (enable)
			hdmi |= HDMI0_ENABLE;
		चयन (radeon_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
			अगर (enable) अणु
				WREG32_OR(AVIVO_TMDSA_CNTL, AVIVO_TMDSA_CNTL_HDMI_EN);
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_TMDSA);
			पूर्ण अन्यथा अणु
				WREG32_AND(AVIVO_TMDSA_CNTL, ~AVIVO_TMDSA_CNTL_HDMI_EN);
			पूर्ण
			अवरोध;
		हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
			अगर (enable) अणु
				WREG32_OR(AVIVO_LVTMA_CNTL, AVIVO_LVTMA_CNTL_HDMI_EN);
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_LVTMA);
			पूर्ण अन्यथा अणु
				WREG32_AND(AVIVO_LVTMA_CNTL, ~AVIVO_LVTMA_CNTL_HDMI_EN);
			पूर्ण
			अवरोध;
		हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
			अगर (enable) अणु
				WREG32_OR(DDIA_CNTL, DDIA_HDMI_EN);
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_DDIA);
			पूर्ण अन्यथा अणु
				WREG32_AND(DDIA_CNTL, ~DDIA_HDMI_EN);
			पूर्ण
			अवरोध;
		हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
			अगर (enable)
				hdmi |= HDMI0_STREAM(HDMI0_STREAM_DVOA);
			अवरोध;
		शेष:
			dev_err(rdev->dev, "Invalid encoder for HDMI: 0x%X\n",
				radeon_encoder->encoder_id);
			अवरोध;
		पूर्ण
		WREG32(HDMI0_CONTROL + dig->afmt->offset, hdmi);
	पूर्ण

	अगर (rdev->irq.installed) अणु
		/* अगर irq is available use it */
		/* XXX: shouldn't need this on any asics.  Double check DCE2/3 */
		अगर (enable)
			radeon_irq_kms_enable_afmt(rdev, dig->afmt->id);
		अन्यथा
			radeon_irq_kms_disable_afmt(rdev, dig->afmt->id);
	पूर्ण

	dig->afmt->enabled = enable;

	DRM_DEBUG("%sabling HDMI interface @ 0x%04X for encoder 0x%x\n",
		  enable ? "En" : "Dis", dig->afmt->offset, radeon_encoder->encoder_id);
पूर्ण

