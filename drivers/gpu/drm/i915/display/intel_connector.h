<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_CONNECTOR_H__
#घोषणा __INTEL_CONNECTOR_H__

#समावेश "intel_display.h"

काष्ठा drm_connector;
काष्ठा edid;
काष्ठा i2c_adapter;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_encoder;

पूर्णांक पूर्णांकel_connector_init(काष्ठा पूर्णांकel_connector *connector);
काष्ठा पूर्णांकel_connector *पूर्णांकel_connector_alloc(व्योम);
व्योम पूर्णांकel_connector_मुक्त(काष्ठा पूर्णांकel_connector *connector);
व्योम पूर्णांकel_connector_destroy(काष्ठा drm_connector *connector);
पूर्णांक पूर्णांकel_connector_रेजिस्टर(काष्ठा drm_connector *connector);
व्योम पूर्णांकel_connector_unरेजिस्टर(काष्ठा drm_connector *connector);
व्योम पूर्णांकel_connector_attach_encoder(काष्ठा पूर्णांकel_connector *connector,
				    काष्ठा पूर्णांकel_encoder *encoder);
bool पूर्णांकel_connector_get_hw_state(काष्ठा पूर्णांकel_connector *connector);
क्रमागत pipe पूर्णांकel_connector_get_pipe(काष्ठा पूर्णांकel_connector *connector);
पूर्णांक पूर्णांकel_connector_update_modes(काष्ठा drm_connector *connector,
				 काष्ठा edid *edid);
पूर्णांक पूर्णांकel_ddc_get_modes(काष्ठा drm_connector *c, काष्ठा i2c_adapter *adapter);
व्योम पूर्णांकel_attach_क्रमce_audio_property(काष्ठा drm_connector *connector);
व्योम पूर्णांकel_attach_broadcast_rgb_property(काष्ठा drm_connector *connector);
व्योम पूर्णांकel_attach_aspect_ratio_property(काष्ठा drm_connector *connector);
व्योम पूर्णांकel_attach_hdmi_colorspace_property(काष्ठा drm_connector *connector);
व्योम पूर्णांकel_attach_dp_colorspace_property(काष्ठा drm_connector *connector);

#पूर्ण_अगर /* __INTEL_CONNECTOR_H__ */
