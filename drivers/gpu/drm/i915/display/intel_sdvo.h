<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_SDVO_H__
#घोषणा __INTEL_SDVO_H__

#समावेश <linux/types.h>

#समावेश "i915_reg.h"

काष्ठा drm_i915_निजी;
क्रमागत pipe;
क्रमागत port;

bool पूर्णांकel_sdvo_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			     i915_reg_t sdvo_reg, क्रमागत pipe *pipe);
bool पूर्णांकel_sdvo_init(काष्ठा drm_i915_निजी *dev_priv,
		     i915_reg_t reg, क्रमागत port port);

#पूर्ण_अगर /* __INTEL_SDVO_H__ */
