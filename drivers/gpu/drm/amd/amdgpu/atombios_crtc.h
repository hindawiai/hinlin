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
 */

#अगर_अघोषित __ATOMBIOS_CRTC_H__
#घोषणा __ATOMBIOS_CRTC_H__

व्योम amdgpu_atombios_crtc_overscan_setup(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode);
व्योम amdgpu_atombios_crtc_scaler_setup(काष्ठा drm_crtc *crtc);
व्योम amdgpu_atombios_crtc_lock(काष्ठा drm_crtc *crtc, पूर्णांक lock);
व्योम amdgpu_atombios_crtc_enable(काष्ठा drm_crtc *crtc, पूर्णांक state);
व्योम amdgpu_atombios_crtc_blank(काष्ठा drm_crtc *crtc, पूर्णांक state);
व्योम amdgpu_atombios_crtc_घातergate(काष्ठा drm_crtc *crtc, पूर्णांक state);
व्योम amdgpu_atombios_crtc_घातergate_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_atombios_crtc_set_dtd_timing(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_display_mode *mode);
व्योम amdgpu_atombios_crtc_set_disp_eng_pll(काष्ठा amdgpu_device *adev,
				    u32 dispclk);
u32 amdgpu_atombios_crtc_set_dce_घड़ी(काष्ठा amdgpu_device *adev,
				       u32 freq, u8 clk_type, u8 clk_src);
व्योम amdgpu_atombios_crtc_program_pll(काष्ठा drm_crtc *crtc,
			       u32 crtc_id,
			       पूर्णांक pll_id,
			       u32 encoder_mode,
			       u32 encoder_id,
			       u32 घड़ी,
			       u32 ref_भाग,
			       u32 fb_भाग,
			       u32 frac_fb_भाग,
			       u32 post_भाग,
			       पूर्णांक bpc,
			       bool ss_enabled,
			       काष्ठा amdgpu_atom_ss *ss);
पूर्णांक amdgpu_atombios_crtc_prepare_pll(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_display_mode *mode);
व्योम amdgpu_atombios_crtc_set_pll(काष्ठा drm_crtc *crtc,
			   काष्ठा drm_display_mode *mode);

#पूर्ण_अगर
