<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_DP_LINK_TRAINING_H__
#घोषणा __INTEL_DP_LINK_TRAINING_H__

#समावेश <drm/drm_dp_helper.h>

काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_dp;

पूर्णांक पूर्णांकel_dp_init_lttpr_and_dprx_caps(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);

व्योम पूर्णांकel_dp_get_adjust_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       क्रमागत drm_dp_phy dp_phy,
			       स्थिर u8 link_status[DP_LINK_STATUS_SIZE]);
व्योम पूर्णांकel_dp_program_link_training_pattern(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					    u8 dp_train_pat);
व्योम पूर्णांकel_dp_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				क्रमागत drm_dp_phy dp_phy);
व्योम पूर्णांकel_dp_start_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dp_stop_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

/* Get the TPSx symbol type of the value programmed to DP_TRAINING_PATTERN_SET */
अटल अंतरभूत u8 पूर्णांकel_dp_training_pattern_symbol(u8 pattern)
अणु
	वापस pattern & ~DP_LINK_SCRAMBLING_DISABLE;
पूर्ण

#पूर्ण_अगर /* __INTEL_DP_LINK_TRAINING_H__ */
