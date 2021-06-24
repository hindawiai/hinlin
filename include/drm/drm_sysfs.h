<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DRM_SYSFS_H_
#घोषणा _DRM_SYSFS_H_

काष्ठा drm_device;
काष्ठा device;
काष्ठा drm_connector;
काष्ठा drm_property;

पूर्णांक drm_class_device_रेजिस्टर(काष्ठा device *dev);
व्योम drm_class_device_unरेजिस्टर(काष्ठा device *dev);

व्योम drm_sysfs_hotplug_event(काष्ठा drm_device *dev);
व्योम drm_sysfs_connector_status_event(काष्ठा drm_connector *connector,
				      काष्ठा drm_property *property);
#पूर्ण_अगर
