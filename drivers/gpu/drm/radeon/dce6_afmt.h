<शैली गुरु>
/* dce6_afmt.h -- Private header क्रम radeon driver -*- linux-c -*-
 *
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

#अगर_अघोषित __DCE6_AFMT_H__
#घोषणा __DCE6_AFMT_H__

काष्ठा cea_sad;
काष्ठा drm_connector;
काष्ठा drm_display_mode;
काष्ठा drm_encoder;
काष्ठा radeon_crtc;
काष्ठा radeon_device;

u32 dce6_endpoपूर्णांक_rreg(काष्ठा radeon_device *rdev, u32 offset, u32 reg);
व्योम dce6_endpoपूर्णांक_wreg(काष्ठा radeon_device *rdev, u32 offset, u32 reg, u32 v);
व्योम dce6_afmt_ग_लिखो_sad_regs(काष्ठा drm_encoder *encoder,
			      काष्ठा cea_sad *sads, पूर्णांक sad_count);
व्योम dce6_afmt_hdmi_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					     u8 *sadb, पूर्णांक sad_count);
व्योम dce6_afmt_dp_ग_लिखो_speaker_allocation(काष्ठा drm_encoder *encoder,
					   u8 *sadb, पूर्णांक sad_count);
व्योम dce6_afmt_ग_लिखो_latency_fields(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_connector *connector,
				    काष्ठा drm_display_mode *mode);
व्योम dce6_afmt_select_pin(काष्ठा drm_encoder *encoder);
व्योम dce6_hdmi_audio_set_dto(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी);
व्योम dce6_dp_audio_set_dto(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_crtc *crtc, अचिन्हित पूर्णांक घड़ी);

#पूर्ण_अगर                         /* __DCE6_AFMT_H__ */
