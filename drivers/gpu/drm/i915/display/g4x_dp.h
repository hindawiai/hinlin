<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित _G4X_DP_H_
#घोषणा _G4X_DP_H_

#समावेश <linux/types.h>

#समावेश "i915_reg.h"

क्रमागत pipe;
क्रमागत port;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_dp;
काष्ठा पूर्णांकel_encoder;

स्थिर काष्ठा dpll *vlv_get_dpll(काष्ठा drm_i915_निजी *i915);
क्रमागत pipe vlv_active_pipe(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम g4x_dp_set_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config);
bool g4x_dp_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			 i915_reg_t dp_reg, क्रमागत port port,
			 क्रमागत pipe *pipe);
bool g4x_dp_init(काष्ठा drm_i915_निजी *dev_priv,
		 i915_reg_t output_reg, क्रमागत port port);

#पूर्ण_अगर
