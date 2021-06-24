<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2011 Intel Corporation
 */

काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा psb_पूर्णांकel_mode_device;

बाह्य स्थिर काष्ठा drm_crtc_helper_funcs cdv_पूर्णांकel_helper_funcs;
बाह्य स्थिर काष्ठा gma_घड़ी_funcs cdv_घड़ी_funcs;
बाह्य व्योम cdv_पूर्णांकel_crt_init(काष्ठा drm_device *dev,
			काष्ठा psb_पूर्णांकel_mode_device *mode_dev);
बाह्य व्योम cdv_पूर्णांकel_lvds_init(काष्ठा drm_device *dev,
			काष्ठा psb_पूर्णांकel_mode_device *mode_dev);
बाह्य व्योम cdv_hdmi_init(काष्ठा drm_device *dev, काष्ठा psb_पूर्णांकel_mode_device *mode_dev,
			पूर्णांक reg);
बाह्य काष्ठा drm_display_mode *cdv_पूर्णांकel_crtc_mode_get(काष्ठा drm_device *dev,
					     काष्ठा drm_crtc *crtc);
बाह्य व्योम cdv_update_wm(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc);
बाह्य व्योम cdv_disable_sr(काष्ठा drm_device *dev);
