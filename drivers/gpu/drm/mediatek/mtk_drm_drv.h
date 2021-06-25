<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#अगर_अघोषित MTK_DRM_DRV_H
#घोषणा MTK_DRM_DRV_H

#समावेश <linux/पन.स>
#समावेश "mtk_drm_ddp_comp.h"

#घोषणा MAX_CRTC	3
#घोषणा MAX_CONNECTOR	2

काष्ठा device;
काष्ठा device_node;
काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा drm_fb_helper;
काष्ठा drm_property;
काष्ठा regmap;

काष्ठा mtk_mmsys_driver_data अणु
	स्थिर क्रमागत mtk_ddp_comp_id *मुख्य_path;
	अचिन्हित पूर्णांक मुख्य_len;
	स्थिर क्रमागत mtk_ddp_comp_id *ext_path;
	अचिन्हित पूर्णांक ext_len;
	स्थिर क्रमागत mtk_ddp_comp_id *third_path;
	अचिन्हित पूर्णांक third_len;

	bool shaकरोw_रेजिस्टर;
पूर्ण;

काष्ठा mtk_drm_निजी अणु
	काष्ठा drm_device *drm;
	काष्ठा device *dma_dev;

	अचिन्हित पूर्णांक num_pipes;

	काष्ठा device_node *mutex_node;
	काष्ठा device *mutex_dev;
	काष्ठा device *mmsys_dev;
	काष्ठा device_node *comp_node[DDP_COMPONENT_ID_MAX];
	काष्ठा mtk_ddp_comp ddp_comp[DDP_COMPONENT_ID_MAX];
	स्थिर काष्ठा mtk_mmsys_driver_data *data;
	काष्ठा drm_atomic_state *suspend_state;
पूर्ण;

बाह्य काष्ठा platक्रमm_driver mtk_disp_ccorr_driver;
बाह्य काष्ठा platक्रमm_driver mtk_disp_color_driver;
बाह्य काष्ठा platक्रमm_driver mtk_disp_gamma_driver;
बाह्य काष्ठा platक्रमm_driver mtk_disp_ovl_driver;
बाह्य काष्ठा platक्रमm_driver mtk_disp_rdma_driver;
बाह्य काष्ठा platक्रमm_driver mtk_dpi_driver;
बाह्य काष्ठा platक्रमm_driver mtk_dsi_driver;

#पूर्ण_अगर /* MTK_DRM_DRV_H */
