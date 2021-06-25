<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_VRR_H__
#घोषणा __INTEL_VRR_H__

#समावेश <linux/types.h>

काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_dp;
काष्ठा पूर्णांकel_encoder;

bool पूर्णांकel_vrr_is_capable(काष्ठा drm_connector *connector);
व्योम पूर्णांकel_vrr_check_modeset(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_vrr_compute_config(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_vrr_enable(काष्ठा पूर्णांकel_encoder *encoder,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_vrr_send_push(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_vrr_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state);
व्योम पूर्णांकel_vrr_get_config(काष्ठा पूर्णांकel_crtc *crtc,
			  काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्णांक पूर्णांकel_vrr_vmax_vblank_start(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्णांक पूर्णांकel_vrr_vmin_vblank_start(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

#पूर्ण_अगर /* __INTEL_VRR_H__ */
