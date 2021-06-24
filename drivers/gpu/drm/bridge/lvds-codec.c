<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Copyright (C) 2016 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_panel.h>

काष्ठा lvds_codec अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा regulator *vcc;
	काष्ठा gpio_desc *घातerकरोwn_gpio;
	u32 connector_type;
पूर्ण;

अटल अंतरभूत काष्ठा lvds_codec *to_lvds_codec(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा lvds_codec, bridge);
पूर्ण

अटल पूर्णांक lvds_codec_attach(काष्ठा drm_bridge *bridge,
			     क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा lvds_codec *lvds_codec = to_lvds_codec(bridge);

	वापस drm_bridge_attach(bridge->encoder, lvds_codec->panel_bridge,
				 bridge, flags);
पूर्ण

अटल व्योम lvds_codec_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lvds_codec *lvds_codec = to_lvds_codec(bridge);
	पूर्णांक ret;

	ret = regulator_enable(lvds_codec->vcc);
	अगर (ret) अणु
		dev_err(lvds_codec->dev,
			"Failed to enable regulator \"vcc\": %d\n", ret);
		वापस;
	पूर्ण

	अगर (lvds_codec->घातerकरोwn_gpio)
		gpiod_set_value_cansleep(lvds_codec->घातerकरोwn_gpio, 0);
पूर्ण

अटल व्योम lvds_codec_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lvds_codec *lvds_codec = to_lvds_codec(bridge);
	पूर्णांक ret;

	अगर (lvds_codec->घातerकरोwn_gpio)
		gpiod_set_value_cansleep(lvds_codec->घातerकरोwn_gpio, 1);

	ret = regulator_disable(lvds_codec->vcc);
	अगर (ret)
		dev_err(lvds_codec->dev,
			"Failed to disable regulator \"vcc\": %d\n", ret);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs funcs = अणु
	.attach = lvds_codec_attach,
	.enable = lvds_codec_enable,
	.disable = lvds_codec_disable,
पूर्ण;

अटल पूर्णांक lvds_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *panel_node;
	काष्ठा drm_panel *panel;
	काष्ठा lvds_codec *lvds_codec;

	lvds_codec = devm_kzalloc(dev, माप(*lvds_codec), GFP_KERNEL);
	अगर (!lvds_codec)
		वापस -ENOMEM;

	lvds_codec->dev = &pdev->dev;
	lvds_codec->connector_type = (uपूर्णांकptr_t)of_device_get_match_data(dev);

	lvds_codec->vcc = devm_regulator_get(lvds_codec->dev, "power");
	अगर (IS_ERR(lvds_codec->vcc))
		वापस dev_err_probe(dev, PTR_ERR(lvds_codec->vcc),
				     "Unable to get \"vcc\" supply\n");

	lvds_codec->घातerकरोwn_gpio = devm_gpiod_get_optional(dev, "powerdown",
							     GPIOD_OUT_HIGH);
	अगर (IS_ERR(lvds_codec->घातerकरोwn_gpio))
		वापस dev_err_probe(dev, PTR_ERR(lvds_codec->घातerकरोwn_gpio),
				     "powerdown GPIO failure\n");

	/* Locate the panel DT node. */
	panel_node = of_graph_get_remote_node(dev->of_node, 1, 0);
	अगर (!panel_node) अणु
		dev_dbg(dev, "panel DT node not found\n");
		वापस -ENXIO;
	पूर्ण

	panel = of_drm_find_panel(panel_node);
	of_node_put(panel_node);
	अगर (IS_ERR(panel)) अणु
		dev_dbg(dev, "panel not found, deferring probe\n");
		वापस PTR_ERR(panel);
	पूर्ण

	lvds_codec->panel_bridge =
		devm_drm_panel_bridge_add_typed(dev, panel,
						lvds_codec->connector_type);
	अगर (IS_ERR(lvds_codec->panel_bridge))
		वापस PTR_ERR(lvds_codec->panel_bridge);

	/*
	 * The panel_bridge bridge is attached to the panel's of_node,
	 * but we need a bridge attached to our of_node क्रम our user
	 * to look up.
	 */
	lvds_codec->bridge.of_node = dev->of_node;
	lvds_codec->bridge.funcs = &funcs;
	drm_bridge_add(&lvds_codec->bridge);

	platक्रमm_set_drvdata(pdev, lvds_codec);

	वापस 0;
पूर्ण

अटल पूर्णांक lvds_codec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lvds_codec *lvds_codec = platक्रमm_get_drvdata(pdev);

	drm_bridge_हटाओ(&lvds_codec->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lvds_codec_match[] = अणु
	अणु
		.compatible = "lvds-decoder",
		.data = (व्योम *)DRM_MODE_CONNECTOR_DPI,
	पूर्ण,
	अणु
		.compatible = "lvds-encoder",
		.data = (व्योम *)DRM_MODE_CONNECTOR_LVDS,
	पूर्ण,
	अणु
		.compatible = "thine,thc63lvdm83d",
		.data = (व्योम *)DRM_MODE_CONNECTOR_LVDS,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lvds_codec_match);

अटल काष्ठा platक्रमm_driver lvds_codec_driver = अणु
	.probe	= lvds_codec_probe,
	.हटाओ	= lvds_codec_हटाओ,
	.driver		= अणु
		.name		= "lvds-codec",
		.of_match_table	= lvds_codec_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lvds_codec_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("LVDS encoders and decoders");
MODULE_LICENSE("GPL");
