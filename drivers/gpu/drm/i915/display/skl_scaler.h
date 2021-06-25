<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */
#अगर_अघोषित INTEL_SCALER_H
#घोषणा INTEL_SCALER_H

#समावेश <linux/types.h>

क्रमागत drm_scaling_filter;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_plane_state;
काष्ठा पूर्णांकel_plane;
क्रमागत pipe;

पूर्णांक skl_update_scaler_crtc(काष्ठा पूर्णांकel_crtc_state *crtc_state);

पूर्णांक skl_update_scaler_plane(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    काष्ठा पूर्णांकel_plane_state *plane_state);

व्योम skl_pfit_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

व्योम skl_program_plane_scaler(काष्ठा पूर्णांकel_plane *plane,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);
व्योम skl_detach_scalers(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम skl_scaler_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state);
#पूर्ण_अगर
