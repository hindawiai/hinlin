<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_ATOMIC_PLANE_H__
#घोषणा __INTEL_ATOMIC_PLANE_H__

#समावेश <linux/types.h>

काष्ठा drm_plane;
काष्ठा drm_property;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_plane;
काष्ठा पूर्णांकel_plane_state;

बाह्य स्थिर काष्ठा drm_plane_helper_funcs पूर्णांकel_plane_helper_funcs;

अचिन्हित पूर्णांक पूर्णांकel_plane_pixel_rate(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);

अचिन्हित पूर्णांक पूर्णांकel_plane_data_rate(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);
व्योम पूर्णांकel_plane_copy_uapi_to_hw_state(काष्ठा पूर्णांकel_plane_state *plane_state,
				       स्थिर काष्ठा पूर्णांकel_plane_state *from_plane_state,
				       काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_plane_copy_hw_state(काष्ठा पूर्णांकel_plane_state *plane_state,
			       स्थिर काष्ठा पूर्णांकel_plane_state *from_plane_state);
व्योम पूर्णांकel_update_plane(काष्ठा पूर्णांकel_plane *plane,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);
व्योम पूर्णांकel_disable_plane(काष्ठा पूर्णांकel_plane *plane,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
काष्ठा पूर्णांकel_plane *पूर्णांकel_plane_alloc(व्योम);
व्योम पूर्णांकel_plane_मुक्त(काष्ठा पूर्णांकel_plane *plane);
काष्ठा drm_plane_state *पूर्णांकel_plane_duplicate_state(काष्ठा drm_plane *plane);
व्योम पूर्णांकel_plane_destroy_state(काष्ठा drm_plane *plane,
			       काष्ठा drm_plane_state *state);
व्योम skl_update_planes_on_crtc(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_crtc *crtc);
व्योम i9xx_update_planes_on_crtc(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc);
पूर्णांक पूर्णांकel_plane_atomic_check_with_state(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
					काष्ठा पूर्णांकel_crtc_state *crtc_state,
					स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state,
					काष्ठा पूर्णांकel_plane_state *पूर्णांकel_state);
पूर्णांक पूर्णांकel_plane_atomic_check(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_plane *plane);
पूर्णांक पूर्णांकel_plane_atomic_calc_changes(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state,
				    काष्ठा पूर्णांकel_plane_state *plane_state);
पूर्णांक पूर्णांकel_plane_calc_min_cdclk(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_plane *plane,
			       bool *need_cdclk_calc);
पूर्णांक पूर्णांकel_atomic_plane_check_clipping(काष्ठा पूर्णांकel_plane_state *plane_state,
				      काष्ठा पूर्णांकel_crtc_state *crtc_state,
				      पूर्णांक min_scale, पूर्णांक max_scale,
				      bool can_position);
व्योम पूर्णांकel_plane_set_invisible(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       काष्ठा पूर्णांकel_plane_state *plane_state);

#पूर्ण_अगर /* __INTEL_ATOMIC_PLANE_H__ */
