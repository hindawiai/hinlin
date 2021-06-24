<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#अगर_अघोषित MTK_DRM_CRTC_H
#घोषणा MTK_DRM_CRTC_H

#समावेश <drm/drm_crtc.h>
#समावेश "mtk_drm_ddp_comp.h"
#समावेश "mtk_drm_plane.h"

#घोषणा MTK_LUT_SIZE	512
#घोषणा MTK_MAX_BPC	10
#घोषणा MTK_MIN_BPC	3

व्योम mtk_drm_crtc_commit(काष्ठा drm_crtc *crtc);
पूर्णांक mtk_drm_crtc_create(काष्ठा drm_device *drm_dev,
			स्थिर क्रमागत mtk_ddp_comp_id *path,
			अचिन्हित पूर्णांक path_len);
पूर्णांक mtk_drm_crtc_plane_check(काष्ठा drm_crtc *crtc, काष्ठा drm_plane *plane,
			     काष्ठा mtk_plane_state *state);
व्योम mtk_drm_crtc_async_update(काष्ठा drm_crtc *crtc, काष्ठा drm_plane *plane,
			       काष्ठा drm_atomic_state *plane_state);

#पूर्ण_अगर /* MTK_DRM_CRTC_H */
