<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Texas Instruments
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "tilcdc_drv.h"
#समावेश "tilcdc_external.h"

अटल स्थिर काष्ठा tilcdc_panel_info panel_info_tda998x = अणु
		.ac_bias                = 255,
		.ac_bias_पूर्णांकrpt         = 0,
		.dma_burst_sz           = 16,
		.bpp                    = 16,
		.fdd                    = 0x80,
		.tft_alt_mode           = 0,
		.invert_pxl_clk		= 1,
		.sync_edge              = 1,
		.sync_ctrl              = 1,
		.raster_order           = 0,
पूर्ण;

अटल स्थिर काष्ठा tilcdc_panel_info panel_info_शेष = अणु
		.ac_bias                = 255,
		.ac_bias_पूर्णांकrpt         = 0,
		.dma_burst_sz           = 16,
		.bpp                    = 16,
		.fdd                    = 0x80,
		.tft_alt_mode           = 0,
		.sync_edge              = 0,
		.sync_ctrl              = 1,
		.raster_order           = 0,
पूर्ण;

अटल
काष्ठा drm_connector *tilcdc_encoder_find_connector(काष्ठा drm_device *ddev,
						    काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector;

	list_क्रम_each_entry(connector, &ddev->mode_config.connector_list, head) अणु
		अगर (drm_connector_has_possible_encoder(connector, encoder))
			वापस connector;
	पूर्ण

	dev_err(ddev->dev, "No connector found for %s encoder (id %d)\n",
		encoder->name, encoder->base.id);

	वापस शून्य;
पूर्ण

पूर्णांक tilcdc_add_component_encoder(काष्ठा drm_device *ddev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = ddev->dev_निजी;
	काष्ठा drm_encoder *encoder;

	list_क्रम_each_entry(encoder, &ddev->mode_config.encoder_list, head)
		अगर (encoder->possible_crtcs & (1 << priv->crtc->index))
			अवरोध;

	अगर (!encoder) अणु
		dev_err(ddev->dev, "%s: No suitable encoder found\n", __func__);
		वापस -ENODEV;
	पूर्ण

	priv->बाह्यal_connector =
		tilcdc_encoder_find_connector(ddev, encoder);

	अगर (!priv->बाह्यal_connector)
		वापस -ENODEV;

	/* Only tda998x is supported at the moment. */
	tilcdc_crtc_set_simulate_vesa_sync(priv->crtc, true);
	tilcdc_crtc_set_panel_info(priv->crtc, &panel_info_tda998x);

	वापस 0;
पूर्ण

अटल
पूर्णांक tilcdc_attach_bridge(काष्ठा drm_device *ddev, काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tilcdc_drm_निजी *priv = ddev->dev_निजी;
	पूर्णांक ret;

	priv->बाह्यal_encoder->possible_crtcs = BIT(0);

	ret = drm_bridge_attach(priv->बाह्यal_encoder, bridge, शून्य, 0);
	अगर (ret) अणु
		dev_err(ddev->dev, "drm_bridge_attach() failed %d\n", ret);
		वापस ret;
	पूर्ण

	tilcdc_crtc_set_panel_info(priv->crtc, &panel_info_शेष);

	priv->बाह्यal_connector =
		tilcdc_encoder_find_connector(ddev, priv->बाह्यal_encoder);
	अगर (!priv->बाह्यal_connector)
		वापस -ENODEV;

	वापस 0;
पूर्ण

पूर्णांक tilcdc_attach_बाह्यal_device(काष्ठा drm_device *ddev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = ddev->dev_निजी;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	ret = drm_of_find_panel_or_bridge(ddev->dev->of_node, 0, 0,
					  &panel, &bridge);
	अगर (ret == -ENODEV)
		वापस 0;
	अन्यथा अगर (ret)
		वापस ret;

	priv->बाह्यal_encoder = devm_kzalloc(ddev->dev,
					      माप(*priv->बाह्यal_encoder),
					      GFP_KERNEL);
	अगर (!priv->बाह्यal_encoder)
		वापस -ENOMEM;

	ret = drm_simple_encoder_init(ddev, priv->बाह्यal_encoder,
				      DRM_MODE_ENCODER_NONE);
	अगर (ret) अणु
		dev_err(ddev->dev, "drm_encoder_init() failed %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (panel) अणु
		bridge = devm_drm_panel_bridge_add_typed(ddev->dev, panel,
							 DRM_MODE_CONNECTOR_DPI);
		अगर (IS_ERR(bridge)) अणु
			ret = PTR_ERR(bridge);
			जाओ err_encoder_cleanup;
		पूर्ण
	पूर्ण

	ret = tilcdc_attach_bridge(ddev, bridge);
	अगर (ret)
		जाओ err_encoder_cleanup;

	वापस 0;

err_encoder_cleanup:
	drm_encoder_cleanup(priv->बाह्यal_encoder);
	वापस ret;
पूर्ण

अटल पूर्णांक dev_match_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

पूर्णांक tilcdc_get_बाह्यal_components(काष्ठा device *dev,
				   काष्ठा component_match **match)
अणु
	काष्ठा device_node *node;

	node = of_graph_get_remote_node(dev->of_node, 0, 0);

	अगर (!of_device_is_compatible(node, "nxp,tda998x")) अणु
		of_node_put(node);
		वापस 0;
	पूर्ण

	अगर (match)
		drm_of_component_match_add(dev, match, dev_match_of, node);
	of_node_put(node);
	वापस 1;
पूर्ण
