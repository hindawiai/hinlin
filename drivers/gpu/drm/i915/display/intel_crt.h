<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_CRT_H__
#घोषणा __INTEL_CRT_H__

#समावेश "i915_reg.h"

क्रमागत pipe;
काष्ठा drm_encoder;
काष्ठा drm_i915_निजी;

bool पूर्णांकel_crt_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			    i915_reg_t adpa_reg, क्रमागत pipe *pipe);
व्योम पूर्णांकel_crt_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_crt_reset(काष्ठा drm_encoder *encoder);

#पूर्ण_अगर /* __INTEL_CRT_H__ */
