<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश <video/videomode.h>

#समावेश "xen_drm_front.h"
#समावेश "xen_drm_front_conn.h"
#समावेश "xen_drm_front_kms.h"

अटल काष्ठा xen_drm_front_drm_pipeline *
to_xen_drm_pipeline(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा xen_drm_front_drm_pipeline, conn);
पूर्ण

अटल स्थिर u32 plane_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_YUYV,
पूर्ण;

स्थिर u32 *xen_drm_front_conn_get_क्रमmats(पूर्णांक *क्रमmat_count)
अणु
	*क्रमmat_count = ARRAY_SIZE(plane_क्रमmats);
	वापस plane_क्रमmats;
पूर्ण

अटल पूर्णांक connector_detect(काष्ठा drm_connector *connector,
			    काष्ठा drm_modeset_acquire_ctx *ctx,
			    bool क्रमce)
अणु
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(connector);

	अगर (drm_dev_is_unplugged(connector->dev))
		pipeline->conn_connected = false;

	वापस pipeline->conn_connected ? connector_status_connected :
			connector_status_disconnected;
पूर्ण

#घोषणा XEN_DRM_CRTC_VREFRESH_HZ	60

अटल पूर्णांक connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(connector);
	काष्ठा drm_display_mode *mode;
	काष्ठा videomode videomode;
	पूर्णांक width, height;

	mode = drm_mode_create(connector->dev);
	अगर (!mode)
		वापस 0;

	स_रखो(&videomode, 0, माप(videomode));
	videomode.hactive = pipeline->width;
	videomode.vactive = pipeline->height;
	width = videomode.hactive + videomode.hfront_porch +
			videomode.hback_porch + videomode.hsync_len;
	height = videomode.vactive + videomode.vfront_porch +
			videomode.vback_porch + videomode.vsync_len;
	videomode.pixelघड़ी = width * height * XEN_DRM_CRTC_VREFRESH_HZ;
	mode->type = DRM_MODE_TYPE_PREFERRED | DRM_MODE_TYPE_DRIVER;

	drm_display_mode_from_videomode(&videomode, mode);
	drm_mode_probed_add(connector, mode);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs connector_helper_funcs = अणु
	.get_modes = connector_get_modes,
	.detect_ctx = connector_detect,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

पूर्णांक xen_drm_front_conn_init(काष्ठा xen_drm_front_drm_info *drm_info,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(connector);

	drm_connector_helper_add(connector, &connector_helper_funcs);

	pipeline->conn_connected = true;

	connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;

	वापस drm_connector_init(drm_info->drm_dev, connector,
				  &connector_funcs, DRM_MODE_CONNECTOR_VIRTUAL);
पूर्ण
