<शैली गुरु>
/* evergreen_hdmi.h -- Private header क्रम radeon driver -*- linux-c -*-
 *
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
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __EVERGREEN_HDMI_H__
#घोषणा __EVERGREEN_HDMI_H__

काष्ठा cea_sa;
काष्ठा cea_sad;
काष्ठा drm_connector;
काष्ठा drm_display_mode;
काष्ठा drm_encoder;
काष्ठा r600_audio_pin;
काष्ठा radeon_crtc;
काष्ठा radeon_device;
काष्ठा radeon_hdmi_acr;

व्योम evergreen_hdmi_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder,
				   काष्ठा cea_sad *sads, पूर्णांक sad_count);
व्योम evergreen_set_avi_packet(काष्ठा radeon_device *rdev, u32 offset,
			      अचिन्हित अक्षर *buffer, माप_प्रकार size);
व्योम evergreen_hdmi_update_acr(काष्ठा drm_encoder *encoder, दीर्घ offset,
			       स्थिर काष्ठा radeon_hdmi_acr *acr);
व्योम evergreen_hdmi_enable(काष्ठा drm_encoder *encoder, bool enable);
व्योम evergreen_dp_enable(काष्ठा drm_encoder *encoder, bool enable);

व्योम dce4_audio_enable(काष्ठा radeon_device *rdev, काष्ठा r600_audio_pin *pin,
		       u8 enable_mask);
व्योम dce4_afmt_hdmi_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					     u8 *sadb, पूर्णांक sad_count);
व्योम dce4_afmt_dp_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					   u8 *sadb, पूर्णांक sad_count);
व्योम dce4_afmt_ग_लिखो_latency_fields(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_connector *connector,
				    काष्ठा drm_display_mode *mode);
व्योम dce4_hdmi_audio_set_dto(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी);
व्योम dce4_dp_audio_set_dto(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी);
व्योम dce4_set_vbi_packet(काष्ठा drm_encoder *encoder, u32 offset);
व्योम dce4_hdmi_set_color_depth(काष्ठा drm_encoder *encoder,
			       u32 offset, पूर्णांक bpc);
व्योम dce4_set_audio_packet(काष्ठा drm_encoder *encoder, u32 offset);
व्योम dce4_set_mute(काष्ठा drm_encoder *encoder, u32 offset, bool mute);

#पूर्ण_अगर				/* __EVERGREEN_HDMI_H__ */
