<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:
 *      Sandy Huang <hjc@rock-chips.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_vop.h"
#समावेश "rockchip_rgb.h"

#घोषणा encoder_to_rgb(c) container_of(c, काष्ठा rockchip_rgb, encoder)

काष्ठा rockchip_rgb अणु
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_encoder encoder;
	पूर्णांक output_mode;
पूर्ण;

अटल पूर्णांक
rockchip_rgb_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				   काष्ठा drm_crtc_state *crtc_state,
				   काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा drm_display_info *info = &connector->display_info;
	u32 bus_क्रमmat;

	अगर (info->num_bus_क्रमmats)
		bus_क्रमmat = info->bus_क्रमmats[0];
	अन्यथा
		bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;

	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB666_1X18:
		s->output_mode = ROCKCHIP_OUT_MODE_P666;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_1X16:
		s->output_mode = ROCKCHIP_OUT_MODE_P565;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	हाल MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
	शेष:
		s->output_mode = ROCKCHIP_OUT_MODE_P888;
		अवरोध;
	पूर्ण

	s->output_type = DRM_MODE_CONNECTOR_LVDS;

	वापस 0;
पूर्ण

अटल स्थिर
काष्ठा drm_encoder_helper_funcs rockchip_rgb_encoder_helper_funcs = अणु
	.atomic_check = rockchip_rgb_encoder_atomic_check,
पूर्ण;

काष्ठा rockchip_rgb *rockchip_rgb_init(काष्ठा device *dev,
				       काष्ठा drm_crtc *crtc,
				       काष्ठा drm_device *drm_dev)
अणु
	काष्ठा rockchip_rgb *rgb;
	काष्ठा drm_encoder *encoder;
	काष्ठा device_node *port, *endpoपूर्णांक;
	u32 endpoपूर्णांक_id;
	पूर्णांक ret = 0, child_count = 0;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;

	rgb = devm_kzalloc(dev, माप(*rgb), GFP_KERNEL);
	अगर (!rgb)
		वापस ERR_PTR(-ENOMEM);

	rgb->dev = dev;
	rgb->drm_dev = drm_dev;

	port = of_graph_get_port_by_id(dev->of_node, 0);
	अगर (!port)
		वापस ERR_PTR(-EINVAL);

	क्रम_each_child_of_node(port, endpoपूर्णांक) अणु
		अगर (of_property_पढ़ो_u32(endpoपूर्णांक, "reg", &endpoपूर्णांक_id))
			endpoपूर्णांक_id = 0;

		/* अगर subdriver (> 0) or error हाल (< 0), ignore entry */
		अगर (rockchip_drm_endpoपूर्णांक_is_subdriver(endpoपूर्णांक) != 0)
			जारी;

		child_count++;
		ret = drm_of_find_panel_or_bridge(dev->of_node, 0, endpoपूर्णांक_id,
						  &panel, &bridge);
		अगर (!ret) अणु
			of_node_put(endpoपूर्णांक);
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(port);

	/* अगर the rgb output is not connected to anything, just वापस */
	अगर (!child_count)
		वापस शून्य;

	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "failed to find panel or bridge %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	encoder = &rgb->encoder;
	encoder->possible_crtcs = drm_crtc_mask(crtc);

	ret = drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_NONE);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(drm_dev->dev,
			      "failed to initialize encoder: %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_encoder_helper_add(encoder, &rockchip_rgb_encoder_helper_funcs);

	अगर (panel) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_LVDS);
		अगर (IS_ERR(bridge))
			वापस ERR_CAST(bridge);
	पूर्ण

	rgb->bridge = bridge;

	ret = drm_bridge_attach(encoder, rgb->bridge, शून्य, 0);
	अगर (ret) अणु
		DRM_DEV_ERROR(drm_dev->dev,
			      "failed to attach bridge: %d\n", ret);
		जाओ err_मुक्त_encoder;
	पूर्ण

	वापस rgb;

err_मुक्त_encoder:
	drm_encoder_cleanup(encoder);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_rgb_init);

व्योम rockchip_rgb_fini(काष्ठा rockchip_rgb *rgb)
अणु
	drm_panel_bridge_हटाओ(rgb->bridge);
	drm_encoder_cleanup(&rgb->encoder);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_rgb_fini);
