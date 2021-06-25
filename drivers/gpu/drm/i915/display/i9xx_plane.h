<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित _I9XX_PLANE_H_
#घोषणा _I9XX_PLANE_H_

#समावेश <linux/types.h>

क्रमागत pipe;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_initial_plane_config;
काष्ठा पूर्णांकel_plane;
काष्ठा पूर्णांकel_plane_state;

अचिन्हित पूर्णांक i965_plane_max_stride(काष्ठा पूर्णांकel_plane *plane,
				   u32 pixel_क्रमmat, u64 modअगरier,
				   अचिन्हित पूर्णांक rotation);
पूर्णांक i9xx_check_plane_surface(काष्ठा पूर्णांकel_plane_state *plane_state);

काष्ठा पूर्णांकel_plane *
पूर्णांकel_primary_plane_create(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe);

व्योम i9xx_get_initial_plane_config(काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_initial_plane_config *plane_config);
#पूर्ण_अगर
