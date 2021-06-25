<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

#अगर_अघोषित __DRM_PROBE_HELPER_H__
#घोषणा __DRM_PROBE_HELPER_H__

#समावेश <linux/types.h>

काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_modeset_acquire_ctx;

पूर्णांक drm_helper_probe_single_connector_modes(काष्ठा drm_connector
					    *connector, uपूर्णांक32_t maxX,
					    uपूर्णांक32_t maxY);
पूर्णांक drm_helper_probe_detect(काष्ठा drm_connector *connector,
			    काष्ठा drm_modeset_acquire_ctx *ctx,
			    bool क्रमce);
व्योम drm_kms_helper_poll_init(काष्ठा drm_device *dev);
व्योम drm_kms_helper_poll_fini(काष्ठा drm_device *dev);
bool drm_helper_hpd_irq_event(काष्ठा drm_device *dev);
व्योम drm_kms_helper_hotplug_event(काष्ठा drm_device *dev);

व्योम drm_kms_helper_poll_disable(काष्ठा drm_device *dev);
व्योम drm_kms_helper_poll_enable(काष्ठा drm_device *dev);
bool drm_kms_helper_is_poll_worker(व्योम);

#पूर्ण_अगर
