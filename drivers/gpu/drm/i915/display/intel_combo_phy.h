<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_COMBO_PHY_H__
#घोषणा __INTEL_COMBO_PHY_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
क्रमागत phy;

व्योम पूर्णांकel_combo_phy_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_combo_phy_uninit(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_combo_phy_घातer_up_lanes(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत phy phy, bool is_dsi,
				    पूर्णांक lane_count, bool lane_reversal);

#पूर्ण_अगर /* __INTEL_COMBO_PHY_H__ */
