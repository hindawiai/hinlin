<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_DDI_H__
#घोषणा __INTEL_DDI_H__

#समावेश "intel_display.h"
#समावेश "i915_reg.h"

काष्ठा drm_connector_state;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_dp;
काष्ठा पूर्णांकel_dpll_hw_state;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_shared_dpll;
क्रमागत transcoder;

i915_reg_t dp_tp_ctl_reg(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
i915_reg_t dp_tp_status_reg(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_ddi_fdi_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				स्थिर काष्ठा drm_connector_state *old_conn_state);
व्योम पूर्णांकel_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_ddi_get_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
			 काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 काष्ठा पूर्णांकel_shared_dpll *pll);
व्योम hsw_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम hsw_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder);
bool hsw_ddi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder);
व्योम hsw_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *crtc_state);
काष्ठा पूर्णांकel_shared_dpll *icl_ddi_combo_get_pll(काष्ठा पूर्णांकel_encoder *encoder);
व्योम पूर्णांकel_prepare_dp_ddi_buffers(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_रुको_ddi_buf_idle(काष्ठा drm_i915_निजी *dev_priv,
			     क्रमागत port port);
व्योम पूर्णांकel_ddi_init(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port);
bool पूर्णांकel_ddi_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder, क्रमागत pipe *pipe);
व्योम पूर्णांकel_ddi_enable_transcoder_func(काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_ddi_disable_transcoder_func(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_ddi_enable_pipe_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_ddi_disable_pipe_घड़ी(स्थिर  काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_ddi_set_dp_msa(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा drm_connector_state *conn_state);
bool पूर्णांकel_ddi_connector_get_hw_state(काष्ठा पूर्णांकel_connector *पूर्णांकel_connector);
व्योम पूर्णांकel_ddi_set_vc_payload_alloc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    bool state);
व्योम पूर्णांकel_ddi_compute_min_voltage_level(काष्ठा drm_i915_निजी *dev_priv,
					 काष्ठा पूर्णांकel_crtc_state *crtc_state);
u32 bxt_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
u32 ddi_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्णांक पूर्णांकel_ddi_toggle_hdcp_bits(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
			       क्रमागत transcoder cpu_transcoder,
			       bool enable, u32 hdcp_mask);
व्योम पूर्णांकel_ddi_sanitize_encoder_pll_mapping(काष्ठा पूर्णांकel_encoder *encoder);

#पूर्ण_अगर /* __INTEL_DDI_H__ */
