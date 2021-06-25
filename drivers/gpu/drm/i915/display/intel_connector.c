<शैली गुरु>
/*
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (c) 2007, 2010 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>

#समावेश "display/intel_panel.h"

#समावेश "i915_drv.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_debugfs.h"
#समावेश "intel_display_types.h"
#समावेश "intel_hdcp.h"

पूर्णांक पूर्णांकel_connector_init(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_connector_state *conn_state;

	/*
	 * Allocate enough memory to hold पूर्णांकel_digital_connector_state,
	 * This might be a few bytes too many, but क्रम connectors that करोn't
	 * need it we'll मुक्त the state and allocate a smaller one on the first
	 * successful commit anyway.
	 */
	conn_state = kzalloc(माप(*conn_state), GFP_KERNEL);
	अगर (!conn_state)
		वापस -ENOMEM;

	__drm_atomic_helper_connector_reset(&connector->base,
					    &conn_state->base);

	वापस 0;
पूर्ण

काष्ठा पूर्णांकel_connector *पूर्णांकel_connector_alloc(व्योम)
अणु
	काष्ठा पूर्णांकel_connector *connector;

	connector = kzalloc(माप(*connector), GFP_KERNEL);
	अगर (!connector)
		वापस शून्य;

	अगर (पूर्णांकel_connector_init(connector) < 0) अणु
		kमुक्त(connector);
		वापस शून्य;
	पूर्ण

	वापस connector;
पूर्ण

/*
 * Free the bits allocated by पूर्णांकel_connector_alloc.
 * This should only be used after पूर्णांकel_connector_alloc has वापसed
 * successfully, and beक्रमe drm_connector_init वापसs successfully.
 * Otherwise the destroy callbacks क्रम the connector and the state should
 * take care of proper cleanup/मुक्त (see पूर्णांकel_connector_destroy).
 */
व्योम पूर्णांकel_connector_मुक्त(काष्ठा पूर्णांकel_connector *connector)
अणु
	kमुक्त(to_पूर्णांकel_digital_connector_state(connector->base.state));
	kमुक्त(connector);
पूर्ण

/*
 * Connector type independent destroy hook क्रम drm_connector_funcs.
 */
व्योम पूर्णांकel_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);

	kमुक्त(पूर्णांकel_connector->detect_edid);

	पूर्णांकel_hdcp_cleanup(पूर्णांकel_connector);

	अगर (!IS_ERR_OR_शून्य(पूर्णांकel_connector->edid))
		kमुक्त(पूर्णांकel_connector->edid);

	पूर्णांकel_panel_fini(&पूर्णांकel_connector->panel);

	drm_connector_cleanup(connector);

	अगर (पूर्णांकel_connector->port)
		drm_dp_mst_put_port_दो_स्मृति(पूर्णांकel_connector->port);

	kमुक्त(connector);
पूर्ण

पूर्णांक पूर्णांकel_connector_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	पूर्णांक ret;

	ret = पूर्णांकel_backlight_device_रेजिस्टर(पूर्णांकel_connector);
	अगर (ret)
		जाओ err;

	अगर (i915_inject_probe_failure(to_i915(connector->dev))) अणु
		ret = -EFAULT;
		जाओ err_backlight;
	पूर्ण

	पूर्णांकel_connector_debugfs_add(connector);

	वापस 0;

err_backlight:
	पूर्णांकel_backlight_device_unरेजिस्टर(पूर्णांकel_connector);
err:
	वापस ret;
पूर्ण

व्योम पूर्णांकel_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);

	पूर्णांकel_backlight_device_unरेजिस्टर(पूर्णांकel_connector);
पूर्ण

व्योम पूर्णांकel_connector_attach_encoder(काष्ठा पूर्णांकel_connector *connector,
				    काष्ठा पूर्णांकel_encoder *encoder)
अणु
	connector->encoder = encoder;
	drm_connector_attach_encoder(&connector->base, &encoder->base);
पूर्ण

/*
 * Simple connector->get_hw_state implementation क्रम encoders that support only
 * one connector and no cloning and hence the encoder state determines the state
 * of the connector.
 */
bool पूर्णांकel_connector_get_hw_state(काष्ठा पूर्णांकel_connector *connector)
अणु
	क्रमागत pipe pipe = 0;
	काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_attached_encoder(connector);

	वापस encoder->get_hw_state(encoder, &pipe);
पूर्ण

क्रमागत pipe पूर्णांकel_connector_get_pipe(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->base.dev;

	drm_WARN_ON(dev,
		    !drm_modeset_is_locked(&dev->mode_config.connection_mutex));

	अगर (!connector->base.state->crtc)
		वापस INVALID_PIPE;

	वापस to_पूर्णांकel_crtc(connector->base.state->crtc)->pipe;
पूर्ण

/**
 * पूर्णांकel_connector_update_modes - update connector from edid
 * @connector: DRM connector device to use
 * @edid: previously पढ़ो EDID inक्रमmation
 */
पूर्णांक पूर्णांकel_connector_update_modes(काष्ठा drm_connector *connector,
				काष्ठा edid *edid)
अणु
	पूर्णांक ret;

	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_ddc_get_modes - get modelist from monitor
 * @connector: DRM connector device to use
 * @adapter: i2c adapter
 *
 * Fetch the EDID inक्रमmation from @connector using the DDC bus.
 */
पूर्णांक पूर्णांकel_ddc_get_modes(काष्ठा drm_connector *connector,
			काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा edid *edid;
	पूर्णांक ret;

	edid = drm_get_edid(connector, adapter);
	अगर (!edid)
		वापस 0;

	ret = पूर्णांकel_connector_update_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_prop_क्रमागत_list क्रमce_audio_names[] = अणु
	अणु HDMI_AUDIO_OFF_DVI, "force-dvi" पूर्ण,
	अणु HDMI_AUDIO_OFF, "off" पूर्ण,
	अणु HDMI_AUDIO_AUTO, "auto" पूर्ण,
	अणु HDMI_AUDIO_ON, "on" पूर्ण,
पूर्ण;

व्योम
पूर्णांकel_attach_क्रमce_audio_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_property *prop;

	prop = dev_priv->क्रमce_audio_property;
	अगर (prop == शून्य) अणु
		prop = drm_property_create_क्रमागत(dev, 0,
					   "audio",
					   क्रमce_audio_names,
					   ARRAY_SIZE(क्रमce_audio_names));
		अगर (prop == शून्य)
			वापस;

		dev_priv->क्रमce_audio_property = prop;
	पूर्ण
	drm_object_attach_property(&connector->base, prop, 0);
पूर्ण

अटल स्थिर काष्ठा drm_prop_क्रमागत_list broadcast_rgb_names[] = अणु
	अणु INTEL_BROADCAST_RGB_AUTO, "Automatic" पूर्ण,
	अणु INTEL_BROADCAST_RGB_FULL, "Full" पूर्ण,
	अणु INTEL_BROADCAST_RGB_LIMITED, "Limited 16:235" पूर्ण,
पूर्ण;

व्योम
पूर्णांकel_attach_broadcast_rgb_property(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_property *prop;

	prop = dev_priv->broadcast_rgb_property;
	अगर (prop == शून्य) अणु
		prop = drm_property_create_क्रमागत(dev, DRM_MODE_PROP_ENUM,
					   "Broadcast RGB",
					   broadcast_rgb_names,
					   ARRAY_SIZE(broadcast_rgb_names));
		अगर (prop == शून्य)
			वापस;

		dev_priv->broadcast_rgb_property = prop;
	पूर्ण

	drm_object_attach_property(&connector->base, prop, 0);
पूर्ण

व्योम
पूर्णांकel_attach_aspect_ratio_property(काष्ठा drm_connector *connector)
अणु
	अगर (!drm_mode_create_aspect_ratio_property(connector->dev))
		drm_object_attach_property(&connector->base,
			connector->dev->mode_config.aspect_ratio_property,
			DRM_MODE_PICTURE_ASPECT_NONE);
पूर्ण

व्योम
पूर्णांकel_attach_hdmi_colorspace_property(काष्ठा drm_connector *connector)
अणु
	अगर (!drm_mode_create_hdmi_colorspace_property(connector))
		drm_object_attach_property(&connector->base,
					   connector->colorspace_property, 0);
पूर्ण

व्योम
पूर्णांकel_attach_dp_colorspace_property(काष्ठा drm_connector *connector)
अणु
	अगर (!drm_mode_create_dp_colorspace_property(connector))
		drm_object_attach_property(&connector->base,
					   connector->colorspace_property, 0);
पूर्ण
