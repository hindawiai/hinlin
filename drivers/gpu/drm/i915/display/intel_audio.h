<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_AUDIO_H__
#घोषणा __INTEL_AUDIO_H__

काष्ठा drm_connector_state;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_encoder;

व्योम पूर्णांकel_init_audio_hooks(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_audio_codec_enable(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_audio_codec_disable(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			       स्थिर काष्ठा drm_connector_state *old_conn_state);
व्योम पूर्णांकel_audio_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_audio_deinit(काष्ठा drm_i915_निजी *dev_priv);

#पूर्ण_अगर /* __INTEL_AUDIO_H__ */
