<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#अगर_अघोषित AMD_DAL_DEV_AMDGPU_DM_AMDGPU_DM_CRC_H_
#घोषणा AMD_DAL_DEV_AMDGPU_DM_AMDGPU_DM_CRC_H_

काष्ठा drm_crtc;
काष्ठा dm_crtc_state;

क्रमागत amdgpu_dm_pipe_crc_source अणु
	AMDGPU_DM_PIPE_CRC_SOURCE_NONE = 0,
	AMDGPU_DM_PIPE_CRC_SOURCE_CRTC,
	AMDGPU_DM_PIPE_CRC_SOURCE_CRTC_DITHER,
	AMDGPU_DM_PIPE_CRC_SOURCE_DPRX,
	AMDGPU_DM_PIPE_CRC_SOURCE_DPRX_DITHER,
	AMDGPU_DM_PIPE_CRC_SOURCE_MAX,
	AMDGPU_DM_PIPE_CRC_SOURCE_INVALID = -1,
पूर्ण;

#अगर_घोषित CONFIG_DRM_AMD_SECURE_DISPLAY
काष्ठा crc_winकरोw_parm अणु
	uपूर्णांक16_t x_start;
	uपूर्णांक16_t y_start;
	uपूर्णांक16_t x_end;
	uपूर्णांक16_t y_end;
	/* CRC windwo is activated or not*/
	bool activated;
	/* Update crc winकरोw during vertical blank or not */
	bool update_win;
	/* skip पढ़ोing/writing क्रम few frames */
	पूर्णांक skip_frame_cnt;
पूर्ण;

काष्ठा crc_rd_work अणु
	काष्ठा work_काष्ठा notअगरy_ta_work;
	/* To protect crc_rd_work carried fields*/
	spinlock_t crc_rd_work_lock;
	काष्ठा drm_crtc *crtc;
	uपूर्णांक8_t phy_inst;
पूर्ण;
#पूर्ण_अगर

अटल अंतरभूत bool amdgpu_dm_is_valid_crc_source(क्रमागत amdgpu_dm_pipe_crc_source source)
अणु
	वापस (source > AMDGPU_DM_PIPE_CRC_SOURCE_NONE) &&
	       (source < AMDGPU_DM_PIPE_CRC_SOURCE_MAX);
पूर्ण

/* amdgpu_dm_crc.c */
#अगर_घोषित CONFIG_DEBUG_FS
पूर्णांक amdgpu_dm_crtc_configure_crc_source(काष्ठा drm_crtc *crtc,
					काष्ठा dm_crtc_state *dm_crtc_state,
					क्रमागत amdgpu_dm_pipe_crc_source source);
पूर्णांक amdgpu_dm_crtc_set_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *src_name);
पूर्णांक amdgpu_dm_crtc_verअगरy_crc_source(काष्ठा drm_crtc *crtc,
				     स्थिर अक्षर *src_name,
				     माप_प्रकार *values_cnt);
स्थिर अक्षर *स्थिर *amdgpu_dm_crtc_get_crc_sources(काष्ठा drm_crtc *crtc,
						  माप_प्रकार *count);
व्योम amdgpu_dm_crtc_handle_crc_irq(काष्ठा drm_crtc *crtc);
#अन्यथा
#घोषणा amdgpu_dm_crtc_set_crc_source शून्य
#घोषणा amdgpu_dm_crtc_verअगरy_crc_source शून्य
#घोषणा amdgpu_dm_crtc_get_crc_sources शून्य
#घोषणा amdgpu_dm_crtc_handle_crc_irq(x)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DRM_AMD_SECURE_DISPLAY
bool amdgpu_dm_crc_winकरोw_is_activated(काष्ठा drm_crtc *crtc);
व्योम amdgpu_dm_crtc_handle_crc_winकरोw_irq(काष्ठा drm_crtc *crtc);
काष्ठा crc_rd_work *amdgpu_dm_crtc_secure_display_create_work(व्योम);
व्योम amdgpu_dm_crtc_secure_display_resume(काष्ठा amdgpu_device *adev);
व्योम amdgpu_dm_crtc_secure_display_suspend(काष्ठा amdgpu_device *adev);
#अन्यथा
#घोषणा amdgpu_dm_crc_winकरोw_is_activated(x)
#घोषणा amdgpu_dm_crtc_handle_crc_winकरोw_irq(x)
#घोषणा amdgpu_dm_crtc_secure_display_create_work()
#घोषणा amdgpu_dm_crtc_secure_display_resume(x)
#घोषणा amdgpu_dm_crtc_secure_display_suspend(x)
#पूर्ण_अगर

#पूर्ण_अगर /* AMD_DAL_DEV_AMDGPU_DM_AMDGPU_DM_CRC_H_ */
