<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित _INTEL_DDI_BUF_TRANS_H_
#घोषणा _INTEL_DDI_BUF_TRANS_H_

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_crtc_state;

काष्ठा ddi_buf_trans अणु
	u32 trans1;	/* balance leg enable, de-emph level */
	u32 trans2;	/* vref sel, vswing */
	u8 i_boost;	/* SKL: I_boost; valid: 0x0, 0x1, 0x3, 0x7 */
पूर्ण;

काष्ठा bxt_ddi_buf_trans अणु
	u8 margin;	/* swing value */
	u8 scale;	/* scale value */
	u8 enable;	/* scale enable */
	u8 deemphasis;
पूर्ण;

काष्ठा cnl_ddi_buf_trans अणु
	u8 dw2_swing_sel;
	u8 dw7_n_scalar;
	u8 dw4_cursor_coeff;
	u8 dw4_post_cursor_2;
	u8 dw4_post_cursor_1;
पूर्ण;

काष्ठा icl_mg_phy_ddi_buf_trans अणु
	u32 cri_txdeemph_override_11_6;
	u32 cri_txdeemph_override_5_0;
	u32 cri_txdeemph_override_17_12;
पूर्ण;

काष्ठा tgl_dkl_phy_ddi_buf_trans अणु
	u32 dkl_vswing_control;
	u32 dkl_preshoot_control;
	u32 dkl_de_emphasis_control;
पूर्ण;

bool is_hobl_buf_trans(स्थिर काष्ठा cnl_ddi_buf_trans *table);

पूर्णांक पूर्णांकel_ddi_hdmi_num_entries(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       पूर्णांक *शेष_entry);

स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_edp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries);
स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_fdi(काष्ठा drm_i915_निजी *dev_priv,
			    पूर्णांक *n_entries);
स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_hdmi(काष्ठा पूर्णांकel_encoder *encoder,
			     पूर्णांक *n_entries);
स्थिर काष्ठा ddi_buf_trans *
पूर्णांकel_ddi_get_buf_trans_dp(काष्ठा पूर्णांकel_encoder *encoder, पूर्णांक *n_entries);

स्थिर काष्ठा bxt_ddi_buf_trans *
bxt_get_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		  पूर्णांक *n_entries);

स्थिर काष्ठा cnl_ddi_buf_trans *
tgl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries);
स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans *
tgl_get_dkl_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      पूर्णांक *n_entries);
स्थिर काष्ठा cnl_ddi_buf_trans *
jsl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries);
स्थिर काष्ठा cnl_ddi_buf_trans *
ehl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries);
स्थिर काष्ठा cnl_ddi_buf_trans *
icl_get_combo_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			पूर्णांक *n_entries);
स्थिर काष्ठा icl_mg_phy_ddi_buf_trans *
icl_get_mg_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		     पूर्णांक *n_entries);

स्थिर काष्ठा cnl_ddi_buf_trans *
cnl_get_buf_trans(काष्ठा पूर्णांकel_encoder *encoder,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		  पूर्णांक *n_entries);

#पूर्ण_अगर
