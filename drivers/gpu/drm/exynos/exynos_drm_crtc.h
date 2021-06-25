<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* exynos_drm_crtc.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#अगर_अघोषित _EXYNOS_DRM_CRTC_H_
#घोषणा _EXYNOS_DRM_CRTC_H_


#समावेश "exynos_drm_drv.h"

काष्ठा exynos_drm_crtc *exynos_drm_crtc_create(काष्ठा drm_device *drm_dev,
					काष्ठा drm_plane *plane,
					क्रमागत exynos_drm_output_type out_type,
					स्थिर काष्ठा exynos_drm_crtc_ops *ops,
					व्योम *context);
व्योम exynos_drm_crtc_रुको_pending_update(काष्ठा exynos_drm_crtc *exynos_crtc);
व्योम exynos_drm_crtc_finish_update(काष्ठा exynos_drm_crtc *exynos_crtc,
				   काष्ठा exynos_drm_plane *exynos_plane);

/* This function माला_लो crtc device matched with out_type. */
काष्ठा exynos_drm_crtc *exynos_drm_crtc_get_by_type(काष्ठा drm_device *drm_dev,
				       क्रमागत exynos_drm_output_type out_type);

पूर्णांक exynos_drm_set_possible_crtcs(काष्ठा drm_encoder *encoder,
		क्रमागत exynos_drm_output_type out_type);

/*
 * This function calls the crtc device(manager)'s te_handler() callback
 * to trigger to transfer video image at the tearing effect synchronization
 * संकेत.
 */
व्योम exynos_drm_crtc_te_handler(काष्ठा drm_crtc *crtc);

व्योम exynos_crtc_handle_event(काष्ठा exynos_drm_crtc *exynos_crtc);

#पूर्ण_अगर
