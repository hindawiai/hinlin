<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: CK Hu <ck.hu@mediatek.com>
 */

#अगर_अघोषित _MTK_DRM_PLANE_H_
#घोषणा _MTK_DRM_PLANE_H_

#समावेश <drm/drm_crtc.h>
#समावेश <linux/types.h>

काष्ठा mtk_plane_pending_state अणु
	bool				config;
	bool				enable;
	dma_addr_t			addr;
	अचिन्हित पूर्णांक			pitch;
	अचिन्हित पूर्णांक			क्रमmat;
	अचिन्हित पूर्णांक			x;
	अचिन्हित पूर्णांक			y;
	अचिन्हित पूर्णांक			width;
	अचिन्हित पूर्णांक			height;
	अचिन्हित पूर्णांक			rotation;
	bool				dirty;
	bool				async_dirty;
	bool				async_config;
पूर्ण;

काष्ठा mtk_plane_state अणु
	काष्ठा drm_plane_state		base;
	काष्ठा mtk_plane_pending_state	pending;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_plane_state *
to_mtk_plane_state(काष्ठा drm_plane_state *state)
अणु
	वापस container_of(state, काष्ठा mtk_plane_state, base);
पूर्ण

पूर्णांक mtk_plane_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane,
		   अचिन्हित दीर्घ possible_crtcs, क्रमागत drm_plane_type type,
		   अचिन्हित पूर्णांक supported_rotations);

#पूर्ण_अगर
