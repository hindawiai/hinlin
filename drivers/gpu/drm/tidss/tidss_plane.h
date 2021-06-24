<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#अगर_अघोषित __TIDSS_PLANE_H__
#घोषणा __TIDSS_PLANE_H__

#घोषणा to_tidss_plane(p) container_of((p), काष्ठा tidss_plane, plane)

काष्ठा tidss_device;

काष्ठा tidss_plane अणु
	काष्ठा drm_plane plane;

	u32 hw_plane_id;
पूर्ण;

काष्ठा tidss_plane *tidss_plane_create(काष्ठा tidss_device *tidss,
				       u32 hw_plane_id, u32 plane_type,
				       u32 crtc_mask, स्थिर u32 *क्रमmats,
				       u32 num_क्रमmats);

#पूर्ण_अगर
