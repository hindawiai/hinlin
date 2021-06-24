<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_FIFO_UNDERRUN_H__
#घोषणा __INTEL_FIFO_UNDERRUN_H__

#समावेश <linux/types.h>

#समावेश "intel_display.h"

काष्ठा drm_i915_निजी;

bool पूर्णांकel_set_cpu_fअगरo_underrun_reporting(काष्ठा drm_i915_निजी *dev_priv,
					   क्रमागत pipe pipe, bool enable);
bool पूर्णांकel_set_pch_fअगरo_underrun_reporting(काष्ठा drm_i915_निजी *dev_priv,
					   क्रमागत pipe pch_transcoder,
					   bool enable);
व्योम पूर्णांकel_cpu_fअगरo_underrun_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत pipe pipe);
व्योम पूर्णांकel_pch_fअगरo_underrun_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत pipe pch_transcoder);
व्योम पूर्णांकel_check_cpu_fअगरo_underruns(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_check_pch_fअगरo_underruns(काष्ठा drm_i915_निजी *dev_priv);

#पूर्ण_अगर /* __INTEL_FIFO_UNDERRUN_H__ */
