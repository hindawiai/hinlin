<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_FBC_H__
#घोषणा __INTEL_FBC_H__

#समावेश <linux/types.h>

#समावेश "intel_frontbuffer.h"

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_plane_state;

व्योम पूर्णांकel_fbc_choose_crtc(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_atomic_state *state);
bool पूर्णांकel_fbc_is_active(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_fbc_pre_update(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_fbc_post_update(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_fbc_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_fbc_enable(काष्ठा पूर्णांकel_atomic_state *state,
		      काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_fbc_disable(काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_fbc_global_disable(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_fbc_invalidate(काष्ठा drm_i915_निजी *dev_priv,
			  अचिन्हित पूर्णांक frontbuffer_bits,
			  क्रमागत fb_op_origin origin);
व्योम पूर्णांकel_fbc_flush(काष्ठा drm_i915_निजी *dev_priv,
		     अचिन्हित पूर्णांक frontbuffer_bits, क्रमागत fb_op_origin origin);
व्योम पूर्णांकel_fbc_cleanup_cfb(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_fbc_handle_fअगरo_underrun_irq(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_fbc_reset_underrun(काष्ठा drm_i915_निजी *dev_priv);

#पूर्ण_अगर /* __INTEL_FBC_H__ */
