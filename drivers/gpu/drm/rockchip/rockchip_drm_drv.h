<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 *
 * based on exynos_drm_drv.h
 */

#अगर_अघोषित _ROCKCHIP_DRM_DRV_H
#घोषणा _ROCKCHIP_DRM_DRV_H

#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_gem.h>

#समावेश <linux/module.h>
#समावेश <linux/component.h>

#घोषणा ROCKCHIP_MAX_FB_BUFFER	3
#घोषणा ROCKCHIP_MAX_CONNECTOR	2
#घोषणा ROCKCHIP_MAX_CRTC	2

काष्ठा drm_device;
काष्ठा drm_connector;
काष्ठा iommu_करोमुख्य;

काष्ठा rockchip_crtc_state अणु
	काष्ठा drm_crtc_state base;
	पूर्णांक output_type;
	पूर्णांक output_mode;
	पूर्णांक output_bpc;
	पूर्णांक output_flags;
	bool enable_afbc;
पूर्ण;
#घोषणा to_rockchip_crtc_state(s) \
		container_of(s, काष्ठा rockchip_crtc_state, base)

/*
 * Rockchip drm निजी काष्ठाure.
 *
 * @crtc: array of enabled CRTCs, used to map from "pipe" to drm_crtc.
 * @num_pipe: number of pipes क्रम this device.
 * @mm_lock: protect drm_mm on multi-thपढ़ोs.
 */
काष्ठा rockchip_drm_निजी अणु
	काष्ठा drm_fb_helper fbdev_helper;
	काष्ठा drm_gem_object *fbdev_bo;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा mutex mm_lock;
	काष्ठा drm_mm mm;
	काष्ठा list_head psr_list;
	काष्ठा mutex psr_list_lock;
पूर्ण;

पूर्णांक rockchip_drm_dma_attach_device(काष्ठा drm_device *drm_dev,
				   काष्ठा device *dev);
व्योम rockchip_drm_dma_detach_device(काष्ठा drm_device *drm_dev,
				    काष्ठा device *dev);
पूर्णांक rockchip_drm_रुको_vact_end(काष्ठा drm_crtc *crtc, अचिन्हित पूर्णांक msसमयout);

पूर्णांक rockchip_drm_endpoपूर्णांक_is_subdriver(काष्ठा device_node *ep);
बाह्य काष्ठा platक्रमm_driver cdn_dp_driver;
बाह्य काष्ठा platक्रमm_driver dw_hdmi_rockchip_pltfm_driver;
बाह्य काष्ठा platक्रमm_driver dw_mipi_dsi_rockchip_driver;
बाह्य काष्ठा platक्रमm_driver inno_hdmi_driver;
बाह्य काष्ठा platक्रमm_driver rockchip_dp_driver;
बाह्य काष्ठा platक्रमm_driver rockchip_lvds_driver;
बाह्य काष्ठा platक्रमm_driver vop_platक्रमm_driver;
बाह्य काष्ठा platक्रमm_driver rk3066_hdmi_driver;
#पूर्ण_अगर /* _ROCKCHIP_DRM_DRV_H_ */
