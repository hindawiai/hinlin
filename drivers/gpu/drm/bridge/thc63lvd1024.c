<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * THC63LVD1024 LVDS to parallel data DRM bridge driver.
 *
 * Copyright (C) 2018 Jacopo Mondi <jacopo+renesas@jmondi.org>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_panel.h>

क्रमागत thc63_ports अणु
	THC63_LVDS_IN0,
	THC63_LVDS_IN1,
	THC63_RGB_OUT0,
	THC63_RGB_OUT1,
पूर्ण;

काष्ठा thc63_dev अणु
	काष्ठा device *dev;

	काष्ठा regulator *vcc;

	काष्ठा gpio_desc *pdwn;
	काष्ठा gpio_desc *oe;

	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *next;

	काष्ठा drm_bridge_timings timings;
पूर्ण;

अटल अंतरभूत काष्ठा thc63_dev *to_thc63(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा thc63_dev, bridge);
पूर्ण

अटल पूर्णांक thc63_attach(काष्ठा drm_bridge *bridge,
			क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा thc63_dev *thc63 = to_thc63(bridge);

	वापस drm_bridge_attach(bridge->encoder, thc63->next, bridge, flags);
पूर्ण

अटल क्रमागत drm_mode_status thc63_mode_valid(काष्ठा drm_bridge *bridge,
					स्थिर काष्ठा drm_display_info *info,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा thc63_dev *thc63 = to_thc63(bridge);
	अचिन्हित पूर्णांक min_freq;
	अचिन्हित पूर्णांक max_freq;

	/*
	 * The THC63LVD1024 pixel rate range is 8 to 135 MHz in all modes but
	 * dual-in, single-out where it is 40 to 150 MHz. As dual-in, dual-out
	 * isn't supported by the driver yet, simply derive the limits from the
	 * input mode.
	 */
	अगर (thc63->timings.dual_link) अणु
		min_freq = 40000;
		max_freq = 150000;
	पूर्ण अन्यथा अणु
		min_freq = 8000;
		max_freq = 135000;
	पूर्ण

	अगर (mode->घड़ी < min_freq)
		वापस MODE_CLOCK_LOW;

	अगर (mode->घड़ी > max_freq)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम thc63_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा thc63_dev *thc63 = to_thc63(bridge);
	पूर्णांक ret;

	ret = regulator_enable(thc63->vcc);
	अगर (ret) अणु
		dev_err(thc63->dev,
			"Failed to enable regulator \"vcc\": %d\n", ret);
		वापस;
	पूर्ण

	gpiod_set_value(thc63->pdwn, 0);
	gpiod_set_value(thc63->oe, 1);
पूर्ण

अटल व्योम thc63_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा thc63_dev *thc63 = to_thc63(bridge);
	पूर्णांक ret;

	gpiod_set_value(thc63->oe, 0);
	gpiod_set_value(thc63->pdwn, 1);

	ret = regulator_disable(thc63->vcc);
	अगर (ret)
		dev_err(thc63->dev,
			"Failed to disable regulator \"vcc\": %d\n", ret);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs thc63_bridge_func = अणु
	.attach	= thc63_attach,
	.mode_valid = thc63_mode_valid,
	.enable = thc63_enable,
	.disable = thc63_disable,
पूर्ण;

अटल पूर्णांक thc63_parse_dt(काष्ठा thc63_dev *thc63)
अणु
	काष्ठा device_node *endpoपूर्णांक;
	काष्ठा device_node *remote;

	endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(thc63->dev->of_node,
						 THC63_RGB_OUT0, -1);
	अगर (!endpoपूर्णांक) अणु
		dev_err(thc63->dev, "Missing endpoint in port@%u\n",
			THC63_RGB_OUT0);
		वापस -ENODEV;
	पूर्ण

	remote = of_graph_get_remote_port_parent(endpoपूर्णांक);
	of_node_put(endpoपूर्णांक);
	अगर (!remote) अणु
		dev_err(thc63->dev, "Endpoint in port@%u unconnected\n",
			THC63_RGB_OUT0);
		वापस -ENODEV;
	पूर्ण

	अगर (!of_device_is_available(remote)) अणु
		dev_err(thc63->dev, "port@%u remote endpoint is disabled\n",
			THC63_RGB_OUT0);
		of_node_put(remote);
		वापस -ENODEV;
	पूर्ण

	thc63->next = of_drm_find_bridge(remote);
	of_node_put(remote);
	अगर (!thc63->next)
		वापस -EPROBE_DEFER;

	endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(thc63->dev->of_node,
						 THC63_LVDS_IN1, -1);
	अगर (endpoपूर्णांक) अणु
		remote = of_graph_get_remote_port_parent(endpoपूर्णांक);
		of_node_put(endpoपूर्णांक);

		अगर (remote) अणु
			अगर (of_device_is_available(remote))
				thc63->timings.dual_link = true;
			of_node_put(remote);
		पूर्ण
	पूर्ण

	dev_dbg(thc63->dev, "operating in %s-link mode\n",
		thc63->timings.dual_link ? "dual" : "single");

	वापस 0;
पूर्ण

अटल पूर्णांक thc63_gpio_init(काष्ठा thc63_dev *thc63)
अणु
	thc63->oe = devm_gpiod_get_optional(thc63->dev, "oe", GPIOD_OUT_LOW);
	अगर (IS_ERR(thc63->oe)) अणु
		dev_err(thc63->dev, "Unable to get \"oe-gpios\": %ld\n",
			PTR_ERR(thc63->oe));
		वापस PTR_ERR(thc63->oe);
	पूर्ण

	thc63->pdwn = devm_gpiod_get_optional(thc63->dev, "powerdown",
					      GPIOD_OUT_HIGH);
	अगर (IS_ERR(thc63->pdwn)) अणु
		dev_err(thc63->dev, "Unable to get \"powerdown-gpios\": %ld\n",
			PTR_ERR(thc63->pdwn));
		वापस PTR_ERR(thc63->pdwn);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक thc63_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thc63_dev *thc63;
	पूर्णांक ret;

	thc63 = devm_kzalloc(&pdev->dev, माप(*thc63), GFP_KERNEL);
	अगर (!thc63)
		वापस -ENOMEM;

	thc63->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, thc63);

	thc63->vcc = devm_regulator_get(thc63->dev, "vcc");
	अगर (IS_ERR(thc63->vcc)) अणु
		अगर (PTR_ERR(thc63->vcc) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		dev_err(thc63->dev, "Unable to get \"vcc\" supply: %ld\n",
			PTR_ERR(thc63->vcc));
		वापस PTR_ERR(thc63->vcc);
	पूर्ण

	ret = thc63_gpio_init(thc63);
	अगर (ret)
		वापस ret;

	ret = thc63_parse_dt(thc63);
	अगर (ret)
		वापस ret;

	thc63->bridge.driver_निजी = thc63;
	thc63->bridge.of_node = pdev->dev.of_node;
	thc63->bridge.funcs = &thc63_bridge_func;
	thc63->bridge.timings = &thc63->timings;

	drm_bridge_add(&thc63->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक thc63_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thc63_dev *thc63 = platक्रमm_get_drvdata(pdev);

	drm_bridge_हटाओ(&thc63->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id thc63_match[] = अणु
	अणु .compatible = "thine,thc63lvd1024", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, thc63_match);

अटल काष्ठा platक्रमm_driver thc63_driver = अणु
	.probe	= thc63_probe,
	.हटाओ	= thc63_हटाओ,
	.driver	= अणु
		.name		= "thc63lvd1024",
		.of_match_table	= thc63_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(thc63_driver);

MODULE_AUTHOR("Jacopo Mondi <jacopo@jmondi.org>");
MODULE_DESCRIPTION("Thine THC63LVD1024 LVDS decoder DRM bridge driver");
MODULE_LICENSE("GPL v2");
