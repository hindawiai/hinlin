<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_LVDS_H__
#घोषणा __INTEL_LVDS_H__

#समावेश <linux/types.h>

#समावेश "i915_reg.h"

क्रमागत pipe;
काष्ठा drm_i915_निजी;

bool पूर्णांकel_lvds_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			     i915_reg_t lvds_reg, क्रमागत pipe *pipe);
व्योम पूर्णांकel_lvds_init(काष्ठा drm_i915_निजी *dev_priv);
काष्ठा पूर्णांकel_encoder *पूर्णांकel_get_lvds_encoder(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_is_dual_link_lvds(काष्ठा drm_i915_निजी *dev_priv);

#पूर्ण_अगर /* __INTEL_LVDS_H__ */
