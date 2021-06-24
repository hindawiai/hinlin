<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_LPE_AUDIO_H__
#घोषणा __INTEL_LPE_AUDIO_H__

#समावेश <linux/types.h>

क्रमागत pipe;
क्रमागत port;
काष्ठा drm_i915_निजी;

पूर्णांक  पूर्णांकel_lpe_audio_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_lpe_audio_tearकरोwn(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_lpe_audio_irq_handler(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_lpe_audio_notअगरy(काष्ठा drm_i915_निजी *dev_priv,
			    क्रमागत pipe pipe, क्रमागत port port,
			    स्थिर व्योम *eld, पूर्णांक ls_घड़ी, bool dp_output);

#पूर्ण_अगर /* __INTEL_LPE_AUDIO_H__ */
