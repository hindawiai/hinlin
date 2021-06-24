<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2014-2016 Hisilicon Limited.
 */

#अगर_अघोषित __KIRIN_DRM_DRV_H__
#घोषणा __KIRIN_DRM_DRV_H__

#घोषणा to_kirin_crtc(crtc) \
	container_of(crtc, काष्ठा kirin_crtc, base)

#घोषणा to_kirin_plane(plane) \
	container_of(plane, काष्ठा kirin_plane, base)

/* kirin-क्रमmat translate table */
काष्ठा kirin_क्रमmat अणु
	u32 pixel_क्रमmat;
	u32 hw_क्रमmat;
पूर्ण;

काष्ठा kirin_crtc अणु
	काष्ठा drm_crtc base;
	व्योम *hw_ctx;
	bool enable;
पूर्ण;

काष्ठा kirin_plane अणु
	काष्ठा drm_plane base;
	व्योम *hw_ctx;
	u32 ch;
पूर्ण;

/* display controller init/cleanup ops */
काष्ठा kirin_drm_data अणु
	स्थिर u32 *channel_क्रमmats;
	u32 channel_क्रमmats_cnt;
	पूर्णांक config_max_width;
	पूर्णांक config_max_height;
	u32 num_planes;
	u32 prim_plane;

	स्थिर काष्ठा drm_driver *driver;
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_helper_funcs;
	स्थिर काष्ठा drm_crtc_funcs *crtc_funcs;
	स्थिर काष्ठा drm_plane_helper_funcs *plane_helper_funcs;
	स्थिर काष्ठा drm_plane_funcs  *plane_funcs;
	स्थिर काष्ठा drm_mode_config_funcs *mode_config_funcs;

	व्योम *(*alloc_hw_ctx)(काष्ठा platक्रमm_device *pdev,
			      काष्ठा drm_crtc *crtc);
	व्योम (*cleanup_hw_ctx)(व्योम *hw_ctx);
पूर्ण;

बाह्य काष्ठा kirin_drm_data ade_driver_data;

#पूर्ण_अगर /* __KIRIN_DRM_DRV_H__ */
