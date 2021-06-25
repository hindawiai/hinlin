<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित _INTEL_FDI_H_
#घोषणा _INTEL_FDI_H_

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_encoder;

#घोषणा I915_DISPLAY_CONFIG_RETRY 1
पूर्णांक ilk_fdi_compute_config(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc,
			   काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम पूर्णांकel_fdi_normal_train(काष्ठा पूर्णांकel_crtc *crtc);
व्योम ilk_fdi_disable(काष्ठा पूर्णांकel_crtc *crtc);
व्योम ilk_fdi_pll_disable(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc);
व्योम ilk_fdi_pll_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_fdi_init_hook(काष्ठा drm_i915_निजी *dev_priv);
व्योम hsw_fdi_link_train(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

#पूर्ण_अगर
