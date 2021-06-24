<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2019 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __DRM_BRIDGE_CONNECTOR_H__
#घोषणा __DRM_BRIDGE_CONNECTOR_H__

काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_encoder;

व्योम drm_bridge_connector_enable_hpd(काष्ठा drm_connector *connector);
व्योम drm_bridge_connector_disable_hpd(काष्ठा drm_connector *connector);
काष्ठा drm_connector *drm_bridge_connector_init(काष्ठा drm_device *drm,
						काष्ठा drm_encoder *encoder);

#पूर्ण_अगर /* __DRM_BRIDGE_CONNECTOR_H__ */
