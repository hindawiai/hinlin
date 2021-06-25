<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_ATOMIC_H__
#घोषणा __INTEL_ATOMIC_H__

#समावेश <linux/types.h>

काष्ठा drm_atomic_state;
काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा drm_crtc;
काष्ठा drm_crtc_state;
काष्ठा drm_device;
काष्ठा drm_i915_निजी;
काष्ठा drm_property;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;

पूर्णांक पूर्णांकel_digital_connector_atomic_get_property(काष्ठा drm_connector *connector,
						स्थिर काष्ठा drm_connector_state *state,
						काष्ठा drm_property *property,
						u64 *val);
पूर्णांक पूर्णांकel_digital_connector_atomic_set_property(काष्ठा drm_connector *connector,
						काष्ठा drm_connector_state *state,
						काष्ठा drm_property *property,
						u64 val);
पूर्णांक पूर्णांकel_digital_connector_atomic_check(काष्ठा drm_connector *conn,
					 काष्ठा drm_atomic_state *state);
काष्ठा drm_connector_state *
पूर्णांकel_digital_connector_duplicate_state(काष्ठा drm_connector *connector);
bool पूर्णांकel_connector_needs_modeset(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा drm_connector *connector);
काष्ठा पूर्णांकel_digital_connector_state *
पूर्णांकel_atomic_get_digital_connector_state(काष्ठा पूर्णांकel_atomic_state *state,
					 काष्ठा पूर्णांकel_connector *connector);

काष्ठा drm_crtc_state *पूर्णांकel_crtc_duplicate_state(काष्ठा drm_crtc *crtc);
व्योम पूर्णांकel_crtc_destroy_state(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_crtc_state *state);
व्योम पूर्णांकel_crtc_मुक्त_hw_state(काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_crtc_copy_color_blobs(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *from_crtc_state);
काष्ठा drm_atomic_state *पूर्णांकel_atomic_state_alloc(काष्ठा drm_device *dev);
व्योम पूर्णांकel_atomic_state_मुक्त(काष्ठा drm_atomic_state *state);
व्योम पूर्णांकel_atomic_state_clear(काष्ठा drm_atomic_state *state);

काष्ठा पूर्णांकel_crtc_state *
पूर्णांकel_atomic_get_crtc_state(काष्ठा drm_atomic_state *state,
			    काष्ठा पूर्णांकel_crtc *crtc);

पूर्णांक पूर्णांकel_atomic_setup_scalers(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state);

#पूर्ण_अगर /* __INTEL_ATOMIC_H__ */
