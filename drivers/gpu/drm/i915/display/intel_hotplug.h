<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_HOTPLUG_H__
#घोषणा __INTEL_HOTPLUG_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_digital_port;
काष्ठा पूर्णांकel_encoder;
क्रमागत port;

व्योम पूर्णांकel_hpd_poll_enable(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_hpd_poll_disable(काष्ठा drm_i915_निजी *dev_priv);
क्रमागत पूर्णांकel_hotplug_state पूर्णांकel_encoder_hotplug(काष्ठा पूर्णांकel_encoder *encoder,
					       काष्ठा पूर्णांकel_connector *connector);
व्योम पूर्णांकel_hpd_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
			   u32 pin_mask, u32 दीर्घ_mask);
व्योम पूर्णांकel_hpd_trigger_irq(काष्ठा पूर्णांकel_digital_port *dig_port);
व्योम पूर्णांकel_hpd_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_hpd_init_work(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_hpd_cancel_work(काष्ठा drm_i915_निजी *dev_priv);
क्रमागत hpd_pin पूर्णांकel_hpd_pin_शेष(काष्ठा drm_i915_निजी *dev_priv,
				   क्रमागत port port);
bool पूर्णांकel_hpd_disable(काष्ठा drm_i915_निजी *dev_priv, क्रमागत hpd_pin pin);
व्योम पूर्णांकel_hpd_enable(काष्ठा drm_i915_निजी *dev_priv, क्रमागत hpd_pin pin);

#पूर्ण_अगर /* __INTEL_HOTPLUG_H__ */
