<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_plane.h -- OMAP DRM Plane
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob@ti.com>
 */

#अगर_अघोषित __OMAPDRM_PLANE_H__
#घोषणा __OMAPDRM_PLANE_H__

#समावेश <linux/types.h>

क्रमागत drm_plane_type;

काष्ठा drm_device;
काष्ठा drm_mode_object;
काष्ठा drm_plane;

काष्ठा drm_plane *omap_plane_init(काष्ठा drm_device *dev,
		पूर्णांक idx, क्रमागत drm_plane_type type,
		u32 possible_crtcs);
व्योम omap_plane_install_properties(काष्ठा drm_plane *plane,
		काष्ठा drm_mode_object *obj);

#पूर्ण_अगर /* __OMAPDRM_PLANE_H__ */
