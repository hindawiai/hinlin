<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 * Authors: Slava Grigorev <slava.grigorev@amd.com>
 */

#समावेश <linux/gcd.h>

#समावेश <drm/drm_crtc.h>
#समावेश "dce6_afmt.h"
#समावेश "evergreen_hdmi.h"
#समावेश "radeon.h"
#समावेश "atom.h"
#समावेश "r600.h"
#समावेश "radeon_audio.h"

व्योम dce6_audio_enable(काष्ठा radeon_device *rdev, काष्ठा r600_audio_pin *pin,
		u8 enable_mask);
काष्ठा r600_audio_pin* r600_audio_get_pin(काष्ठा radeon_device *rdev);
काष्ठा r600_audio_pin* dce6_audio_get_pin(काष्ठा radeon_device *rdev);
अटल व्योम radeon_audio_hdmi_mode_set(काष्ठा drm_encoder *encoder,
	काष्ठा drm_display_mode *mode);
अटल व्योम radeon_audio_dp_mode_set(काष्ठा drm_encoder *encoder,
	काष्ठा drm_display_mode *mode);

अटल स्थिर u32 pin_offsets[7] =
अणु
	(0x5e00 - 0x5e00),
	(0x5e18 - 0x5e00),
	(0x5e30 - 0x5e00),
	(0x5e48 - 0x5e00),
	(0x5e60 - 0x5e00),
	(0x5e78 - 0x5e00),
	(0x5e90 - 0x5e00),
पूर्ण;

अटल u32 radeon_audio_rreg(काष्ठा radeon_device *rdev, u32 offset, u32 reg)
अणु
	वापस RREG32(reg);
पूर्ण

अटल व्योम radeon_audio_wreg(काष्ठा radeon_device *rdev, u32 offset,
		u32 reg, u32 v)
अणु
	WREG32(reg, v);
पूर्ण

अटल काष्ठा radeon_audio_basic_funcs r600_funcs = अणु
	.endpoपूर्णांक_rreg = radeon_audio_rreg,
	.endpoपूर्णांक_wreg = radeon_audio_wreg,
	.enable = r600_audio_enable,
पूर्ण;

अटल काष्ठा radeon_audio_basic_funcs dce32_funcs = अणु
	.endpoपूर्णांक_rreg = radeon_audio_rreg,
	.endpoपूर्णांक_wreg = radeon_audio_wreg,
	.enable = r600_audio_enable,
पूर्ण;

अटल काष्ठा radeon_audio_basic_funcs dce4_funcs = अणु
	.endpoपूर्णांक_rreg = radeon_audio_rreg,
	.endpoपूर्णांक_wreg = radeon_audio_wreg,
	.enable = dce4_audio_enable,
पूर्ण;

अटल काष्ठा radeon_audio_basic_funcs dce6_funcs = अणु
	.endpoपूर्णांक_rreg = dce6_endpoपूर्णांक_rreg,
	.endpoपूर्णांक_wreg = dce6_endpoपूर्णांक_wreg,
	.enable = dce6_audio_enable,
पूर्ण;

अटल काष्ठा radeon_audio_funcs r600_hdmi_funcs = अणु
	.get_pin = r600_audio_get_pin,
	.set_dto = r600_hdmi_audio_set_dto,
	.update_acr = r600_hdmi_update_acr,
	.set_vbi_packet = r600_set_vbi_packet,
	.set_avi_packet = r600_set_avi_packet,
	.set_audio_packet = r600_set_audio_packet,
	.set_mute = r600_set_mute,
	.mode_set = radeon_audio_hdmi_mode_set,
	.dpms = r600_hdmi_enable,
पूर्ण;

अटल काष्ठा radeon_audio_funcs dce32_hdmi_funcs = अणु
	.get_pin = r600_audio_get_pin,
	.ग_लिखो_sad_regs = dce3_2_afmt_ग_लिखो_sad_regs,
	.ग_लिखो_speaker_allocation = dce3_2_afmt_hdmi_ग_लिखो_speaker_allocation,
	.set_dto = dce3_2_audio_set_dto,
	.update_acr = dce3_2_hdmi_update_acr,
	.set_vbi_packet = r600_set_vbi_packet,
	.set_avi_packet = r600_set_avi_packet,
	.set_audio_packet = dce3_2_set_audio_packet,
	.set_mute = dce3_2_set_mute,
	.mode_set = radeon_audio_hdmi_mode_set,
	.dpms = r600_hdmi_enable,
पूर्ण;

अटल काष्ठा radeon_audio_funcs dce32_dp_funcs = अणु
	.get_pin = r600_audio_get_pin,
	.ग_लिखो_sad_regs = dce3_2_afmt_ग_लिखो_sad_regs,
	.ग_लिखो_speaker_allocation = dce3_2_afmt_dp_ग_लिखो_speaker_allocation,
	.set_dto = dce3_2_audio_set_dto,
	.set_avi_packet = r600_set_avi_packet,
	.set_audio_packet = dce3_2_set_audio_packet,
पूर्ण;

अटल काष्ठा radeon_audio_funcs dce4_hdmi_funcs = अणु
	.get_pin = r600_audio_get_pin,
	.ग_लिखो_sad_regs = evergreen_hdmi_ग_लिखो_sad_regs,
	.ग_लिखो_speaker_allocation = dce4_afmt_hdmi_ग_लिखो_speaker_allocation,
	.ग_लिखो_latency_fields = dce4_afmt_ग_लिखो_latency_fields,
	.set_dto = dce4_hdmi_audio_set_dto,
	.update_acr = evergreen_hdmi_update_acr,
	.set_vbi_packet = dce4_set_vbi_packet,
	.set_color_depth = dce4_hdmi_set_color_depth,
	.set_avi_packet = evergreen_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.set_mute = dce4_set_mute,
	.mode_set = radeon_audio_hdmi_mode_set,
	.dpms = evergreen_hdmi_enable,
पूर्ण;

अटल काष्ठा radeon_audio_funcs dce4_dp_funcs = अणु
	.get_pin = r600_audio_get_pin,
	.ग_लिखो_sad_regs = evergreen_hdmi_ग_लिखो_sad_regs,
	.ग_लिखो_speaker_allocation = dce4_afmt_dp_ग_लिखो_speaker_allocation,
	.ग_लिखो_latency_fields = dce4_afmt_ग_लिखो_latency_fields,
	.set_dto = dce4_dp_audio_set_dto,
	.set_avi_packet = evergreen_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.mode_set = radeon_audio_dp_mode_set,
	.dpms = evergreen_dp_enable,
पूर्ण;

अटल काष्ठा radeon_audio_funcs dce6_hdmi_funcs = अणु
	.select_pin = dce6_afmt_select_pin,
	.get_pin = dce6_audio_get_pin,
	.ग_लिखो_sad_regs = dce6_afmt_ग_लिखो_sad_regs,
	.ग_लिखो_speaker_allocation = dce6_afmt_hdmi_ग_लिखो_speaker_allocation,
	.ग_लिखो_latency_fields = dce6_afmt_ग_लिखो_latency_fields,
	.set_dto = dce6_hdmi_audio_set_dto,
	.update_acr = evergreen_hdmi_update_acr,
	.set_vbi_packet = dce4_set_vbi_packet,
	.set_color_depth = dce4_hdmi_set_color_depth,
	.set_avi_packet = evergreen_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.set_mute = dce4_set_mute,
	.mode_set = radeon_audio_hdmi_mode_set,
	.dpms = evergreen_hdmi_enable,
पूर्ण;

अटल काष्ठा radeon_audio_funcs dce6_dp_funcs = अणु
	.select_pin = dce6_afmt_select_pin,
	.get_pin = dce6_audio_get_pin,
	.ग_लिखो_sad_regs = dce6_afmt_ग_लिखो_sad_regs,
	.ग_लिखो_speaker_allocation = dce6_afmt_dp_ग_लिखो_speaker_allocation,
	.ग_लिखो_latency_fields = dce6_afmt_ग_लिखो_latency_fields,
	.set_dto = dce6_dp_audio_set_dto,
	.set_avi_packet = evergreen_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.mode_set = radeon_audio_dp_mode_set,
	.dpms = evergreen_dp_enable,
पूर्ण;

अटल व्योम radeon_audio_enable(काष्ठा radeon_device *rdev,
				काष्ठा r600_audio_pin *pin, u8 enable_mask)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;
	काष्ठा radeon_encoder_atom_dig *dig;
	पूर्णांक pin_count = 0;

	अगर (!pin)
		वापस;

	अगर (rdev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(encoder, &rdev->ddev->mode_config.encoder_list, head) अणु
			अगर (radeon_encoder_is_digital(encoder)) अणु
				radeon_encoder = to_radeon_encoder(encoder);
				dig = radeon_encoder->enc_priv;
				अगर (dig->pin == pin)
					pin_count++;
			पूर्ण
		पूर्ण

		अगर ((pin_count > 1) && (enable_mask == 0))
			वापस;
	पूर्ण

	अगर (rdev->audio.funcs->enable)
		rdev->audio.funcs->enable(rdev, pin, enable_mask);
पूर्ण

अटल व्योम radeon_audio_पूर्णांकerface_init(काष्ठा radeon_device *rdev)
अणु
	अगर (ASIC_IS_DCE6(rdev)) अणु
		rdev->audio.funcs = &dce6_funcs;
		rdev->audपन.सdmi_funcs = &dce6_hdmi_funcs;
		rdev->audio.dp_funcs = &dce6_dp_funcs;
	पूर्ण अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
		rdev->audio.funcs = &dce4_funcs;
		rdev->audपन.सdmi_funcs = &dce4_hdmi_funcs;
		rdev->audio.dp_funcs = &dce4_dp_funcs;
	पूर्ण अन्यथा अगर (ASIC_IS_DCE32(rdev)) अणु
		rdev->audio.funcs = &dce32_funcs;
		rdev->audपन.सdmi_funcs = &dce32_hdmi_funcs;
		rdev->audio.dp_funcs = &dce32_dp_funcs;
	पूर्ण अन्यथा अणु
		rdev->audio.funcs = &r600_funcs;
		rdev->audपन.सdmi_funcs = &r600_hdmi_funcs;
		rdev->audio.dp_funcs = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_audio_chipset_supported(काष्ठा radeon_device *rdev)
अणु
	वापस ASIC_IS_DCE2(rdev) && !ASIC_IS_NODCE(rdev);
पूर्ण

पूर्णांक radeon_audio_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (!radeon_audio || !radeon_audio_chipset_supported(rdev))
		वापस 0;

	rdev->audio.enabled = true;

	अगर (ASIC_IS_DCE83(rdev))		/* KB: 2 streams, 3 endpoपूर्णांकs */
		rdev->audio.num_pins = 3;
	अन्यथा अगर (ASIC_IS_DCE81(rdev))	/* KV: 4 streams, 7 endpoपूर्णांकs */
		rdev->audio.num_pins = 7;
	अन्यथा अगर (ASIC_IS_DCE8(rdev))	/* BN/HW: 6 streams, 7 endpoपूर्णांकs */
		rdev->audio.num_pins = 7;
	अन्यथा अगर (ASIC_IS_DCE64(rdev))	/* OL: 2 streams, 2 endpoपूर्णांकs */
		rdev->audio.num_pins = 2;
	अन्यथा अगर (ASIC_IS_DCE61(rdev))	/* TN: 4 streams, 6 endpoपूर्णांकs */
		rdev->audio.num_pins = 6;
	अन्यथा अगर (ASIC_IS_DCE6(rdev))	/* SI: 6 streams, 6 endpoपूर्णांकs */
		rdev->audio.num_pins = 6;
	अन्यथा
		rdev->audio.num_pins = 1;

	क्रम (i = 0; i < rdev->audio.num_pins; i++) अणु
		rdev->audio.pin[i].channels = -1;
		rdev->audio.pin[i].rate = -1;
		rdev->audio.pin[i].bits_per_sample = -1;
		rdev->audio.pin[i].status_bits = 0;
		rdev->audio.pin[i].category_code = 0;
		rdev->audio.pin[i].connected = false;
		rdev->audio.pin[i].offset = pin_offsets[i];
		rdev->audio.pin[i].id = i;
	पूर्ण

	radeon_audio_पूर्णांकerface_init(rdev);

	/* disable audio.  it will be set up later */
	क्रम (i = 0; i < rdev->audio.num_pins; i++)
		radeon_audio_enable(rdev, &rdev->audio.pin[i], 0);

	वापस 0;
पूर्ण

u32 radeon_audio_endpoपूर्णांक_rreg(काष्ठा radeon_device *rdev, u32 offset, u32 reg)
अणु
	अगर (rdev->audio.funcs->endpoपूर्णांक_rreg)
		वापस rdev->audio.funcs->endpoपूर्णांक_rreg(rdev, offset, reg);

	वापस 0;
पूर्ण

व्योम radeon_audio_endpoपूर्णांक_wreg(काष्ठा radeon_device *rdev, u32 offset,
	u32 reg, u32 v)
अणु
	अगर (rdev->audio.funcs->endpoपूर्णांक_wreg)
		rdev->audio.funcs->endpoपूर्णांक_wreg(rdev, offset, reg, v);
पूर्ण

अटल व्योम radeon_audio_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा cea_sad *sads;
	पूर्णांक sad_count;

	अगर (!connector)
		वापस;

	sad_count = drm_edid_to_sad(radeon_connector_edid(connector), &sads);
	अगर (sad_count < 0)
		DRM_ERROR("Couldn't read SADs: %d\n", sad_count);
	अगर (sad_count <= 0)
		वापस;
	BUG_ON(!sads);

	अगर (radeon_encoder->audio && radeon_encoder->audio->ग_लिखो_sad_regs)
		radeon_encoder->audio->ग_लिखो_sad_regs(encoder, sads, sad_count);

	kमुक्त(sads);
पूर्ण

अटल व्योम radeon_audio_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	u8 *sadb = शून्य;
	पूर्णांक sad_count;

	अगर (!connector)
		वापस;

	sad_count = drm_edid_to_speaker_allocation(radeon_connector_edid(connector),
						   &sadb);
	अगर (sad_count < 0) अणु
		DRM_DEBUG("Couldn't read Speaker Allocation Data Block: %d\n",
			  sad_count);
		sad_count = 0;
	पूर्ण

	अगर (radeon_encoder->audio && radeon_encoder->audio->ग_लिखो_speaker_allocation)
		radeon_encoder->audio->ग_लिखो_speaker_allocation(encoder, sadb, sad_count);

	kमुक्त(sadb);
पूर्ण

अटल व्योम radeon_audio_ग_लिखो_latency_fields(काष्ठा drm_encoder *encoder,
					      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	अगर (!connector)
		वापस;

	अगर (radeon_encoder->audio && radeon_encoder->audio->ग_लिखो_latency_fields)
		radeon_encoder->audio->ग_लिखो_latency_fields(encoder, connector, mode);
पूर्ण

काष्ठा r600_audio_pin* radeon_audio_get_pin(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	अगर (radeon_encoder->audio && radeon_encoder->audio->get_pin)
		वापस radeon_encoder->audio->get_pin(rdev);

	वापस शून्य;
पूर्ण

अटल व्योम radeon_audio_select_pin(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	अगर (radeon_encoder->audio && radeon_encoder->audio->select_pin)
		radeon_encoder->audio->select_pin(encoder);
पूर्ण

व्योम radeon_audio_detect(काष्ठा drm_connector *connector,
			 काष्ठा drm_encoder *encoder,
			 क्रमागत drm_connector_status status)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig;

	अगर (!radeon_audio_chipset_supported(rdev))
		वापस;

	अगर (!radeon_encoder_is_digital(encoder))
		वापस;

	dig = radeon_encoder->enc_priv;

	अगर (status == connector_status_connected) अणु
		अगर (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) अणु
			काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

			अगर (radeon_dp_माला_लोinktype(radeon_connector) ==
			    CONNECTOR_OBJECT_ID_DISPLAYPORT)
				radeon_encoder->audio = rdev->audio.dp_funcs;
			अन्यथा
				radeon_encoder->audio = rdev->audपन.सdmi_funcs;
		पूर्ण अन्यथा अणु
			radeon_encoder->audio = rdev->audपन.सdmi_funcs;
		पूर्ण

		अगर (drm_detect_monitor_audio(radeon_connector_edid(connector))) अणु
			अगर (!dig->pin)
				dig->pin = radeon_audio_get_pin(encoder);
			radeon_audio_enable(rdev, dig->pin, 0xf);
		पूर्ण अन्यथा अणु
			radeon_audio_enable(rdev, dig->pin, 0);
			dig->pin = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		radeon_audio_enable(rdev, dig->pin, 0);
		dig->pin = शून्य;
	पूर्ण
पूर्ण

व्योम radeon_audio_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (!rdev->audio.enabled)
		वापस;

	क्रम (i = 0; i < rdev->audio.num_pins; i++)
		radeon_audio_enable(rdev, &rdev->audio.pin[i], 0);

	rdev->audio.enabled = false;
पूर्ण

अटल व्योम radeon_audio_set_dto(काष्ठा drm_encoder *encoder, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_crtc *crtc = to_radeon_crtc(encoder->crtc);

	अगर (radeon_encoder->audio && radeon_encoder->audio->set_dto)
		radeon_encoder->audio->set_dto(rdev, crtc, घड़ी);
पूर्ण

अटल पूर्णांक radeon_audio_set_avi_packet(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	काष्ठा hdmi_avi_infoframe frame;
	पूर्णांक err;

	अगर (!connector)
		वापस -EINVAL;

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame, connector, mode);
	अगर (err < 0) अणु
		DRM_ERROR("failed to setup AVI infoframe: %d\n", err);
		वापस err;
	पूर्ण

	अगर (radeon_encoder->output_csc != RADEON_OUTPUT_CSC_BYPASS) अणु
		drm_hdmi_avi_infoframe_quant_range(&frame, connector, mode,
						   radeon_encoder->output_csc == RADEON_OUTPUT_CSC_TVRGB ?
						   HDMI_QUANTIZATION_RANGE_LIMITED :
						   HDMI_QUANTIZATION_RANGE_FULL);
	पूर्ण

	err = hdmi_avi_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		DRM_ERROR("failed to pack AVI infoframe: %d\n", err);
		वापस err;
	पूर्ण

	अगर (dig && dig->afmt && radeon_encoder->audio &&
	    radeon_encoder->audio->set_avi_packet)
		radeon_encoder->audio->set_avi_packet(rdev, dig->afmt->offset,
			buffer, माप(buffer));

	वापस 0;
पूर्ण

/*
 * calculate CTS and N values अगर they are not found in the table
 */
अटल व्योम radeon_audio_calc_cts(अचिन्हित पूर्णांक घड़ी, पूर्णांक *CTS, पूर्णांक *N, पूर्णांक freq)
अणु
	पूर्णांक n, cts;
	अचिन्हित दीर्घ भाग, mul;

	/* Safe, but overly large values */
	n = 128 * freq;
	cts = घड़ी * 1000;

	/* Smallest valid fraction */
	भाग = gcd(n, cts);

	n /= भाग;
	cts /= भाग;

	/*
	 * The optimal N is 128*freq/1000. Calculate the बंदst larger
	 * value that करोesn't truncate any bits.
	 */
	mul = ((128*freq/1000) + (n-1))/n;

	n *= mul;
	cts *= mul;

	/* Check that we are in spec (not always possible) */
	अगर (n < (128*freq/1500))
		pr_warn("Calculated ACR N value is too small. You may experience audio problems.\n");
	अगर (n > (128*freq/300))
		pr_warn("Calculated ACR N value is too large. You may experience audio problems.\n");

	*N = n;
	*CTS = cts;

	DRM_DEBUG("Calculated ACR timing N=%d CTS=%d for frequency %d\n",
		*N, *CTS, freq);
पूर्ण

अटल स्थिर काष्ठा radeon_hdmi_acr* radeon_audio_acr(अचिन्हित पूर्णांक घड़ी)
अणु
	अटल काष्ठा radeon_hdmi_acr res;
	u8 i;

	अटल स्थिर काष्ठा radeon_hdmi_acr hdmi_predefined_acr[] = अणु
		/*       32kHz    44.1kHz   48kHz    */
		/* Clock      N     CTS      N     CTS      N     CTS */
		अणु  25175,  4096,  25175, 28224, 125875,  6144,  25175 पूर्ण, /*  25,20/1.001 MHz */
		अणु  25200,  4096,  25200,  6272,  28000,  6144,  25200 पूर्ण, /*  25.20       MHz */
		अणु  27000,  4096,  27000,  6272,  30000,  6144,  27000 पूर्ण, /*  27.00       MHz */
		अणु  27027,  4096,  27027,  6272,  30030,  6144,  27027 पूर्ण, /*  27.00*1.001 MHz */
		अणु  54000,  4096,  54000,  6272,  60000,  6144,  54000 पूर्ण, /*  54.00       MHz */
		अणु  54054,  4096,  54054,  6272,  60060,  6144,  54054 पूर्ण, /*  54.00*1.001 MHz */
		अणु  74176,  4096,  74176,  5733,  75335,  6144,  74176 पूर्ण, /*  74.25/1.001 MHz */
		अणु  74250,  4096,  74250,  6272,  82500,  6144,  74250 पूर्ण, /*  74.25       MHz */
		अणु 148352,  4096, 148352,  5733, 150670,  6144, 148352 पूर्ण, /* 148.50/1.001 MHz */
		अणु 148500,  4096, 148500,  6272, 165000,  6144, 148500 पूर्ण, /* 148.50       MHz */
	पूर्ण;

	/* Precalculated values क्रम common घड़ीs */
	क्रम (i = 0; i < ARRAY_SIZE(hdmi_predefined_acr); i++)
		अगर (hdmi_predefined_acr[i].घड़ी == घड़ी)
			वापस &hdmi_predefined_acr[i];

	/* And odd घड़ीs get manually calculated */
	radeon_audio_calc_cts(घड़ी, &res.cts_32khz, &res.n_32khz, 32000);
	radeon_audio_calc_cts(घड़ी, &res.cts_44_1khz, &res.n_44_1khz, 44100);
	radeon_audio_calc_cts(घड़ी, &res.cts_48khz, &res.n_48khz, 48000);

	वापस &res;
पूर्ण

/*
 * update the N and CTS parameters क्रम a given pixel घड़ी rate
 */
अटल व्योम radeon_audio_update_acr(काष्ठा drm_encoder *encoder, अचिन्हित पूर्णांक घड़ी)
अणु
	स्थिर काष्ठा radeon_hdmi_acr *acr = radeon_audio_acr(घड़ी);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (radeon_encoder->audio && radeon_encoder->audio->update_acr)
		radeon_encoder->audio->update_acr(encoder, dig->afmt->offset, acr);
पूर्ण

अटल व्योम radeon_audio_set_vbi_packet(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (radeon_encoder->audio && radeon_encoder->audio->set_vbi_packet)
		radeon_encoder->audio->set_vbi_packet(encoder, dig->afmt->offset);
पूर्ण

अटल व्योम radeon_hdmi_set_color_depth(काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक bpc = 8;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (encoder->crtc) अणु
		काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
		bpc = radeon_crtc->bpc;
	पूर्ण

	अगर (radeon_encoder->audio && radeon_encoder->audio->set_color_depth)
		radeon_encoder->audio->set_color_depth(encoder, dig->afmt->offset, bpc);
पूर्ण

अटल व्योम radeon_audio_set_audio_packet(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (radeon_encoder->audio && radeon_encoder->audio->set_audio_packet)
		radeon_encoder->audio->set_audio_packet(encoder, dig->afmt->offset);
पूर्ण

अटल व्योम radeon_audio_set_mute(काष्ठा drm_encoder *encoder, bool mute)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (radeon_encoder->audio && radeon_encoder->audio->set_mute)
		radeon_encoder->audio->set_mute(encoder, dig->afmt->offset, mute);
पूर्ण

/*
 * update the info frames with the data from the current display mode
 */
अटल व्योम radeon_audio_hdmi_mode_set(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (!connector)
		वापस;

	अगर (drm_detect_monitor_audio(radeon_connector_edid(connector))) अणु
		radeon_audio_set_mute(encoder, true);

		radeon_audio_ग_लिखो_speaker_allocation(encoder);
		radeon_audio_ग_लिखो_sad_regs(encoder);
		radeon_audio_ग_लिखो_latency_fields(encoder, mode);
		radeon_audio_set_dto(encoder, mode->घड़ी);
		radeon_audio_set_vbi_packet(encoder);
		radeon_hdmi_set_color_depth(encoder);
		radeon_audio_update_acr(encoder, mode->घड़ी);
		radeon_audio_set_audio_packet(encoder);
		radeon_audio_select_pin(encoder);

		अगर (radeon_audio_set_avi_packet(encoder, mode) < 0)
			वापस;

		radeon_audio_set_mute(encoder, false);
	पूर्ण अन्यथा अणु
		radeon_hdmi_set_color_depth(encoder);

		अगर (radeon_audio_set_avi_packet(encoder, mode) < 0)
			वापस;
	पूर्ण
पूर्ण

अटल व्योम radeon_audio_dp_mode_set(काष्ठा drm_encoder *encoder,
				     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);

	अगर (!dig || !dig->afmt)
		वापस;

	अगर (!connector)
		वापस;

	अगर (drm_detect_monitor_audio(radeon_connector_edid(connector))) अणु
		radeon_audio_ग_लिखो_speaker_allocation(encoder);
		radeon_audio_ग_लिखो_sad_regs(encoder);
		radeon_audio_ग_लिखो_latency_fields(encoder, mode);
		radeon_audio_set_dto(encoder, rdev->घड़ी.vco_freq * 10);
		radeon_audio_set_audio_packet(encoder);
		radeon_audio_select_pin(encoder);

		अगर (radeon_audio_set_avi_packet(encoder, mode) < 0)
			वापस;
	पूर्ण
पूर्ण

व्योम radeon_audio_mode_set(काष्ठा drm_encoder *encoder,
			   काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	अगर (radeon_encoder->audio && radeon_encoder->audio->mode_set)
		radeon_encoder->audio->mode_set(encoder, mode);
पूर्ण

व्योम radeon_audio_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	अगर (radeon_encoder->audio && radeon_encoder->audio->dpms)
		radeon_encoder->audio->dpms(encoder, mode == DRM_MODE_DPMS_ON);
पूर्ण

अचिन्हित पूर्णांक radeon_audio_decode_dfs_भाग(अचिन्हित पूर्णांक भाग)
अणु
	अगर (भाग >= 8 && भाग < 64)
		वापस (भाग - 8) * 25 + 200;
	अन्यथा अगर (भाग >= 64 && भाग < 96)
		वापस (भाग - 64) * 50 + 1600;
	अन्यथा अगर (भाग >= 96 && भाग < 128)
		वापस (भाग - 96) * 100 + 3200;
	अन्यथा
		वापस 0;
पूर्ण
