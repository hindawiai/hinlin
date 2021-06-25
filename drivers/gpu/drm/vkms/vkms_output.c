<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश "vkms_drv.h"
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

अटल व्योम vkms_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs vkms_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = vkms_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक vkms_conn_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक count;

	count = drm_add_modes_noedid(connector, XRES_MAX, YRES_MAX);
	drm_set_preferred_mode(connector, XRES_DEF, YRES_DEF);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs vkms_conn_helper_funcs = अणु
	.get_modes    = vkms_conn_get_modes,
पूर्ण;

पूर्णांक vkms_output_init(काष्ठा vkms_device *vkmsdev, पूर्णांक index)
अणु
	काष्ठा vkms_output *output = &vkmsdev->output;
	काष्ठा drm_device *dev = &vkmsdev->drm;
	काष्ठा drm_connector *connector = &output->connector;
	काष्ठा drm_encoder *encoder = &output->encoder;
	काष्ठा drm_crtc *crtc = &output->crtc;
	काष्ठा drm_plane *primary, *cursor = शून्य;
	पूर्णांक ret;
	पूर्णांक ग_लिखोback;

	primary = vkms_plane_init(vkmsdev, DRM_PLANE_TYPE_PRIMARY, index);
	अगर (IS_ERR(primary))
		वापस PTR_ERR(primary);

	अगर (vkmsdev->config->cursor) अणु
		cursor = vkms_plane_init(vkmsdev, DRM_PLANE_TYPE_CURSOR, index);
		अगर (IS_ERR(cursor)) अणु
			ret = PTR_ERR(cursor);
			जाओ err_cursor;
		पूर्ण
	पूर्ण

	ret = vkms_crtc_init(dev, crtc, primary, cursor);
	अगर (ret)
		जाओ err_crtc;

	ret = drm_connector_init(dev, connector, &vkms_connector_funcs,
				 DRM_MODE_CONNECTOR_VIRTUAL);
	अगर (ret) अणु
		DRM_ERROR("Failed to init connector\n");
		जाओ err_connector;
	पूर्ण

	drm_connector_helper_add(connector, &vkms_conn_helper_funcs);

	ret = drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_VIRTUAL);
	अगर (ret) अणु
		DRM_ERROR("Failed to init encoder\n");
		जाओ err_encoder;
	पूर्ण
	encoder->possible_crtcs = 1;

	ret = drm_connector_attach_encoder(connector, encoder);
	अगर (ret) अणु
		DRM_ERROR("Failed to attach connector to encoder\n");
		जाओ err_attach;
	पूर्ण

	अगर (vkmsdev->config->ग_लिखोback) अणु
		ग_लिखोback = vkms_enable_ग_लिखोback_connector(vkmsdev);
		अगर (ग_लिखोback)
			DRM_ERROR("Failed to init writeback connector\n");
	पूर्ण

	drm_mode_config_reset(dev);

	वापस 0;

err_attach:
	drm_encoder_cleanup(encoder);

err_encoder:
	drm_connector_cleanup(connector);

err_connector:
	drm_crtc_cleanup(crtc);

err_crtc:
	अगर (vkmsdev->config->cursor)
		drm_plane_cleanup(cursor);

err_cursor:
	drm_plane_cleanup(primary);

	वापस ret;
पूर्ण
