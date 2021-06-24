<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#अगर_अघोषित _EXYNOS_DRM_FB_H_
#घोषणा _EXYNOS_DRM_FB_H_

#समावेश "exynos_drm_gem.h"

काष्ठा drm_framebuffer *
exynos_drm_framebuffer_init(काष्ठा drm_device *dev,
			    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			    काष्ठा exynos_drm_gem **exynos_gem,
			    पूर्णांक count);

dma_addr_t exynos_drm_fb_dma_addr(काष्ठा drm_framebuffer *fb, पूर्णांक index);

व्योम exynos_drm_mode_config_init(काष्ठा drm_device *dev);

#पूर्ण_अगर
