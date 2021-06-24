<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_HDCP_H__
#घोषणा __INTEL_HDCP_H__

#समावेश <linux/types.h>

#घोषणा HDCP_ENCRYPT_STATUS_CHANGE_TIMEOUT_MS	50

काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_hdcp_shim;
काष्ठा पूर्णांकel_digital_port;
क्रमागत port;
क्रमागत transcoder;

व्योम पूर्णांकel_hdcp_atomic_check(काष्ठा drm_connector *connector,
			     काष्ठा drm_connector_state *old_state,
			     काष्ठा drm_connector_state *new_state);
पूर्णांक पूर्णांकel_hdcp_init(काष्ठा पूर्णांकel_connector *connector,
		    काष्ठा पूर्णांकel_digital_port *dig_port,
		    स्थिर काष्ठा पूर्णांकel_hdcp_shim *hdcp_shim);
पूर्णांक पूर्णांकel_hdcp_enable(काष्ठा पूर्णांकel_connector *connector,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config, u8 content_type);
पूर्णांक पूर्णांकel_hdcp_disable(काष्ठा पूर्णांकel_connector *connector);
व्योम पूर्णांकel_hdcp_update_pipe(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा drm_connector_state *conn_state);
bool is_hdcp_supported(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port);
bool पूर्णांकel_hdcp_capable(काष्ठा पूर्णांकel_connector *connector);
bool पूर्णांकel_hdcp2_capable(काष्ठा पूर्णांकel_connector *connector);
व्योम पूर्णांकel_hdcp_component_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_hdcp_component_fini(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_hdcp_cleanup(काष्ठा पूर्णांकel_connector *connector);
व्योम पूर्णांकel_hdcp_handle_cp_irq(काष्ठा पूर्णांकel_connector *connector);

#पूर्ण_अगर /* __INTEL_HDCP_H__ */
