<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित _SKL_UNIVERSAL_PLANE_H_
#घोषणा _SKL_UNIVERSAL_PLANE_H_

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_initial_plane_config;
काष्ठा पूर्णांकel_plane_state;

क्रमागत pipe;
क्रमागत plane_id;

काष्ठा पूर्णांकel_plane *
skl_universal_plane_create(काष्ठा drm_i915_निजी *dev_priv,
			   क्रमागत pipe pipe, क्रमागत plane_id plane_id);

व्योम skl_get_initial_plane_config(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_initial_plane_config *plane_config);

पूर्णांक skl_क्रमmat_to_fourcc(पूर्णांक क्रमmat, bool rgb_order, bool alpha);

पूर्णांक skl_calc_मुख्य_surface_offset(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
				 पूर्णांक *x, पूर्णांक *y, u32 *offset);

bool icl_is_nv12_y_plane(काष्ठा drm_i915_निजी *dev_priv,
			 क्रमागत plane_id plane_id);
bool icl_is_hdr_plane(काष्ठा drm_i915_निजी *dev_priv, क्रमागत plane_id plane_id);

#पूर्ण_अगर
