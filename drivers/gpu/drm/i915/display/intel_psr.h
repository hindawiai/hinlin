<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_PSR_H__
#घोषणा __INTEL_PSR_H__

#समावेश "intel_frontbuffer.h"

काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_dp;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_plane_state;
काष्ठा पूर्णांकel_plane;

व्योम पूर्णांकel_psr_init_dpcd(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_psr_enable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_psr_disable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		       स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state);
व्योम पूर्णांकel_psr_update(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      स्थिर काष्ठा drm_connector_state *conn_state);
पूर्णांक पूर्णांकel_psr_debug_set(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u64 value);
व्योम पूर्णांकel_psr_invalidate(काष्ठा drm_i915_निजी *dev_priv,
			  अचिन्हित frontbuffer_bits,
			  क्रमागत fb_op_origin origin);
व्योम पूर्णांकel_psr_flush(काष्ठा drm_i915_निजी *dev_priv,
		     अचिन्हित frontbuffer_bits,
		     क्रमागत fb_op_origin origin);
व्योम पूर्णांकel_psr_init(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_psr_compute_config(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_psr_irq_handler(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u32 psr_iir);
व्योम पूर्णांकel_psr_लघु_pulse(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_psr_रुको_क्रम_idle(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state);
bool पूर्णांकel_psr_enabled(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
पूर्णांक पूर्णांकel_psr2_sel_fetch_update(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_psr2_program_trans_man_trk_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_psr2_program_plane_sel_fetch(काष्ठा पूर्णांकel_plane *plane,
					स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
					पूर्णांक color_plane);

#पूर्ण_अगर /* __INTEL_PSR_H__ */
