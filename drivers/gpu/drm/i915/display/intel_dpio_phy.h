<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_DPIO_PHY_H__
#घोषणा __INTEL_DPIO_PHY_H__

#समावेश <linux/types.h>

क्रमागत dpio_channel;
क्रमागत dpio_phy;
क्रमागत port;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_encoder;

व्योम bxt_port_to_phy_channel(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port,
			     क्रमागत dpio_phy *phy, क्रमागत dpio_channel *ch);
व्योम bxt_ddi_phy_set_संकेत_level(काष्ठा drm_i915_निजी *dev_priv,
				  क्रमागत port port, u32 margin, u32 scale,
				  u32 enable, u32 deemphasis);
व्योम bxt_ddi_phy_init(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy);
व्योम bxt_ddi_phy_uninit(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy);
bool bxt_ddi_phy_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
			    क्रमागत dpio_phy phy);
bool bxt_ddi_phy_verअगरy_state(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत dpio_phy phy);
u8 bxt_ddi_phy_calc_lane_lat_optim_mask(u8 lane_count);
व्योम bxt_ddi_phy_set_lane_optim_mask(काष्ठा पूर्णांकel_encoder *encoder,
				     u8 lane_lat_optim_mask);
u8 bxt_ddi_phy_get_lane_lat_optim_mask(काष्ठा पूर्णांकel_encoder *encoder);

व्योम chv_set_phy_संकेत_level(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      u32 deemph_reg_value, u32 margin_reg_value,
			      bool uniq_trans_scale);
व्योम chv_data_lane_soft_reset(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      bool reset);
व्योम chv_phy_pre_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम chv_phy_pre_encoder_enable(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम chv_phy_release_cl2_override(काष्ठा पूर्णांकel_encoder *encoder);
व्योम chv_phy_post_pll_disable(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state);

व्योम vlv_set_phy_संकेत_level(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      u32 demph_reg_value, u32 preemph_reg_value,
			      u32 uniqtranscale_reg_value, u32 tx3_demph);
व्योम vlv_phy_pre_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम vlv_phy_pre_encoder_enable(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम vlv_phy_reset_lanes(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state);

#पूर्ण_अगर /* __INTEL_DPIO_PHY_H__ */
