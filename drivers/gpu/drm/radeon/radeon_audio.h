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

#अगर_अघोषित __RADEON_AUDIO_H__
#घोषणा __RADEON_AUDIO_H__

#समावेश <linux/types.h>

#घोषणा RREG32_ENDPOINT(block, reg)		\
	radeon_audio_endpoपूर्णांक_rreg(rdev, (block), (reg))
#घोषणा WREG32_ENDPOINT(block, reg, v)	\
	radeon_audio_endpoपूर्णांक_wreg(rdev, (block), (reg), (v))

काष्ठा radeon_audio_basic_funcs
अणु
	u32  (*endpoपूर्णांक_rreg)(काष्ठा radeon_device *rdev, u32 offset, u32 reg);
	व्योम (*endpoपूर्णांक_wreg)(काष्ठा radeon_device *rdev,
		u32 offset, u32 reg, u32 v);
	व्योम (*enable)(काष्ठा radeon_device *rdev,
		काष्ठा r600_audio_pin *pin, u8 enable_mask);
पूर्ण;

काष्ठा radeon_audio_funcs
अणु
	व्योम (*select_pin)(काष्ठा drm_encoder *encoder);
	काष्ठा r600_audio_pin* (*get_pin)(काष्ठा radeon_device *rdev);
	व्योम (*ग_लिखो_latency_fields)(काष्ठा drm_encoder *encoder,
		काष्ठा drm_connector *connector, काष्ठा drm_display_mode *mode);
	व्योम (*ग_लिखो_sad_regs)(काष्ठा drm_encoder *encoder,
		काष्ठा cea_sad *sads, पूर्णांक sad_count);
	व्योम (*ग_लिखो_speaker_allocation)(काष्ठा drm_encoder *encoder,
		u8 *sadb, पूर्णांक sad_count);
	व्योम (*set_dto)(काष्ठा radeon_device *rdev,
		काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी);
	व्योम (*update_acr)(काष्ठा drm_encoder *encoder, दीर्घ offset,
		स्थिर काष्ठा radeon_hdmi_acr *acr);
	व्योम (*set_vbi_packet)(काष्ठा drm_encoder *encoder, u32 offset);
	व्योम (*set_color_depth)(काष्ठा drm_encoder *encoder, u32 offset, पूर्णांक bpc);
	व्योम (*set_avi_packet)(काष्ठा radeon_device *rdev, u32 offset,
		अचिन्हित अक्षर *buffer, माप_प्रकार size);
	व्योम (*set_audio_packet)(काष्ठा drm_encoder *encoder, u32 offset);
	व्योम (*set_mute)(काष्ठा drm_encoder *encoder, u32 offset, bool mute);
	व्योम (*mode_set)(काष्ठा drm_encoder *encoder,
		काष्ठा drm_display_mode *mode);
	व्योम (*dpms)(काष्ठा drm_encoder *encoder, bool mode);
पूर्ण;

पूर्णांक radeon_audio_init(काष्ठा radeon_device *rdev);
व्योम radeon_audio_detect(काष्ठा drm_connector *connector,
			 काष्ठा drm_encoder *encoder,
			 क्रमागत drm_connector_status status);
u32 radeon_audio_endpoपूर्णांक_rreg(काष्ठा radeon_device *rdev,
	u32 offset, u32 reg);
व्योम radeon_audio_endpoपूर्णांक_wreg(काष्ठा radeon_device *rdev,
	u32 offset,	u32 reg, u32 v);
काष्ठा r600_audio_pin *radeon_audio_get_pin(काष्ठा drm_encoder *encoder);
व्योम radeon_audio_fini(काष्ठा radeon_device *rdev);
व्योम radeon_audio_mode_set(काष्ठा drm_encoder *encoder,
	काष्ठा drm_display_mode *mode);
व्योम radeon_audio_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode);
अचिन्हित पूर्णांक radeon_audio_decode_dfs_भाग(अचिन्हित पूर्णांक भाग);

व्योम dce3_2_afmt_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder,
				काष्ठा cea_sad *sads, पूर्णांक sad_count);
व्योम dce3_2_afmt_hdmi_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					       u8 *sadb, पूर्णांक sad_count);
व्योम dce3_2_afmt_dp_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					     u8 *sadb, पूर्णांक sad_count);
व्योम dce3_2_audio_set_dto(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी);
व्योम dce3_2_hdmi_update_acr(काष्ठा drm_encoder *encoder, दीर्घ offset,
			    स्थिर काष्ठा radeon_hdmi_acr *acr);
व्योम dce3_2_set_audio_packet(काष्ठा drm_encoder *encoder, u32 offset);
व्योम dce3_2_set_mute(काष्ठा drm_encoder *encoder, u32 offset, bool mute);
#पूर्ण_अगर
