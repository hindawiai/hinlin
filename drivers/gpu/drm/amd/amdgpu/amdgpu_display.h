<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __AMDGPU_DISPLAY_H__
#घोषणा __AMDGPU_DISPLAY_H__

#घोषणा amdgpu_display_vblank_get_counter(adev, crtc) (adev)->mode_info.funcs->vblank_get_counter((adev), (crtc))
#घोषणा amdgpu_display_backlight_set_level(adev, e, l) (adev)->mode_info.funcs->backlight_set_level((e), (l))
#घोषणा amdgpu_display_backlight_get_level(adev, e) (adev)->mode_info.funcs->backlight_get_level((e))
#घोषणा amdgpu_display_hpd_sense(adev, h) (adev)->mode_info.funcs->hpd_sense((adev), (h))
#घोषणा amdgpu_display_hpd_set_polarity(adev, h) (adev)->mode_info.funcs->hpd_set_polarity((adev), (h))
#घोषणा amdgpu_display_hpd_get_gpio_reg(adev) (adev)->mode_info.funcs->hpd_get_gpio_reg((adev))
#घोषणा amdgpu_display_bandwidth_update(adev) (adev)->mode_info.funcs->bandwidth_update((adev))
#घोषणा amdgpu_display_page_flip(adev, crtc, base, async) (adev)->mode_info.funcs->page_flip((adev), (crtc), (base), (async))
#घोषणा amdgpu_display_page_flip_get_scanoutpos(adev, crtc, vbl, pos) (adev)->mode_info.funcs->page_flip_get_scanoutpos((adev), (crtc), (vbl), (pos))
#घोषणा amdgpu_display_add_encoder(adev, e, s, c) (adev)->mode_info.funcs->add_encoder((adev), (e), (s), (c))
#घोषणा amdgpu_display_add_connector(adev, ci, sd, ct, ib, coi, h, r) (adev)->mode_info.funcs->add_connector((adev), (ci), (sd), (ct), (ib), (coi), (h), (r))

पूर्णांक amdgpu_display_मुक्तsync_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *filp);
व्योम amdgpu_display_update_priority(काष्ठा amdgpu_device *adev);
uपूर्णांक32_t amdgpu_display_supported_करोमुख्यs(काष्ठा amdgpu_device *adev,
					  uपूर्णांक64_t bo_flags);
काष्ठा drm_framebuffer *
amdgpu_display_user_framebuffer_create(काष्ठा drm_device *dev,
				       काष्ठा drm_file *file_priv,
				       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);
स्थिर काष्ठा drm_क्रमmat_info *
amdgpu_lookup_क्रमmat_info(u32 क्रमmat, uपूर्णांक64_t modअगरier);

पूर्णांक amdgpu_display_suspend_helper(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_display_resume_helper(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
