<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित _INTEL_CRTC_H_
#घोषणा _INTEL_CRTC_H_

#समावेश <linux/types.h>

क्रमागत pipe;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;

u32 पूर्णांकel_crtc_max_vblank_count(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्णांक पूर्णांकel_crtc_init(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe);
काष्ठा पूर्णांकel_crtc_state *पूर्णांकel_crtc_state_alloc(काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_crtc_state_reset(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    काष्ठा पूर्णांकel_crtc *crtc);

#पूर्ण_अगर
