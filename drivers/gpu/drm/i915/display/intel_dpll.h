<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित _INTEL_DPLL_H_
#घोषणा _INTEL_DPLL_H_

काष्ठा dpll;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
क्रमागत pipe;

व्योम पूर्णांकel_dpll_init_घड़ी_hook(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक vlv_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *घड़ी);
पूर्णांक pnv_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *घड़ी);
पूर्णांक i9xx_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *घड़ी);
व्योम vlv_compute_dpll(काष्ठा पूर्णांकel_crtc *crtc,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम chv_compute_dpll(काष्ठा पूर्णांकel_crtc *crtc,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config);

पूर्णांक vlv_क्रमce_pll_on(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe,
		     स्थिर काष्ठा dpll *dpll);
व्योम vlv_क्रमce_pll_off(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe);
व्योम i9xx_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम vlv_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
		    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम chv_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
		    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम vlv_disable_pll(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe);
व्योम chv_disable_pll(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe);
व्योम i9xx_disable_pll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम vlv_prepare_pll(काष्ठा पूर्णांकel_crtc *crtc,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम chv_prepare_pll(काष्ठा पूर्णांकel_crtc *crtc,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);

#पूर्ण_अगर
