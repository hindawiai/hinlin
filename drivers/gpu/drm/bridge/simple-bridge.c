<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2016 Free Electrons
 * Copyright (C) 2015-2016 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

काष्ठा simple_bridge_info अणु
	स्थिर काष्ठा drm_bridge_timings *timings;
	अचिन्हित पूर्णांक connector_type;
पूर्ण;

काष्ठा simple_bridge अणु
	काष्ठा drm_bridge	bridge;
	काष्ठा drm_connector	connector;

	स्थिर काष्ठा simple_bridge_info *info;

	काष्ठा drm_bridge	*next_bridge;
	काष्ठा regulator	*vdd;
	काष्ठा gpio_desc	*enable;
पूर्ण;

अटल अंतरभूत काष्ठा simple_bridge *
drm_bridge_to_simple_bridge(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा simple_bridge, bridge);
पूर्ण

अटल अंतरभूत काष्ठा simple_bridge *
drm_connector_to_simple_bridge(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा simple_bridge, connector);
पूर्ण

अटल पूर्णांक simple_bridge_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा simple_bridge *sbridge = drm_connector_to_simple_bridge(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	अगर (sbridge->next_bridge->ops & DRM_BRIDGE_OP_EDID) अणु
		edid = drm_bridge_get_edid(sbridge->next_bridge, connector);
		अगर (!edid)
			DRM_INFO("EDID read failed. Fallback to standard modes\n");
	पूर्ण अन्यथा अणु
		edid = शून्य;
	पूर्ण

	अगर (!edid) अणु
		/*
		 * In हाल we cannot retrieve the EDIDs (missing or broken DDC
		 * bus from the next bridge), fallback on the XGA standards and
		 * prefer a mode pretty much anyone can handle.
		 */
		ret = drm_add_modes_noedid(connector, 1920, 1200);
		drm_set_preferred_mode(connector, 1024, 768);
		वापस ret;
	पूर्ण

	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs simple_bridge_con_helper_funcs = अणु
	.get_modes	= simple_bridge_get_modes,
पूर्ण;

अटल क्रमागत drm_connector_status
simple_bridge_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा simple_bridge *sbridge = drm_connector_to_simple_bridge(connector);

	वापस drm_bridge_detect(sbridge->next_bridge);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs simple_bridge_con_funcs = अणु
	.detect			= simple_bridge_connector_detect,
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= drm_connector_cleanup,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक simple_bridge_attach(काष्ठा drm_bridge *bridge,
				क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा simple_bridge *sbridge = drm_bridge_to_simple_bridge(bridge);
	पूर्णांक ret;

	ret = drm_bridge_attach(bridge->encoder, sbridge->next_bridge, bridge,
				DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret < 0)
		वापस ret;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Missing encoder\n");
		वापस -ENODEV;
	पूर्ण

	drm_connector_helper_add(&sbridge->connector,
				 &simple_bridge_con_helper_funcs);
	ret = drm_connector_init_with_ddc(bridge->dev, &sbridge->connector,
					  &simple_bridge_con_funcs,
					  sbridge->info->connector_type,
					  sbridge->next_bridge->ddc);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector\n");
		वापस ret;
	पूर्ण

	drm_connector_attach_encoder(&sbridge->connector, bridge->encoder);

	वापस 0;
पूर्ण

अटल व्योम simple_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा simple_bridge *sbridge = drm_bridge_to_simple_bridge(bridge);
	पूर्णांक ret;

	अगर (sbridge->vdd) अणु
		ret = regulator_enable(sbridge->vdd);
		अगर (ret)
			DRM_ERROR("Failed to enable vdd regulator: %d\n", ret);
	पूर्ण

	gpiod_set_value_cansleep(sbridge->enable, 1);
पूर्ण

अटल व्योम simple_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा simple_bridge *sbridge = drm_bridge_to_simple_bridge(bridge);

	gpiod_set_value_cansleep(sbridge->enable, 0);

	अगर (sbridge->vdd)
		regulator_disable(sbridge->vdd);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs simple_bridge_bridge_funcs = अणु
	.attach		= simple_bridge_attach,
	.enable		= simple_bridge_enable,
	.disable	= simple_bridge_disable,
पूर्ण;

अटल पूर्णांक simple_bridge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा simple_bridge *sbridge;
	काष्ठा device_node *remote;

	sbridge = devm_kzalloc(&pdev->dev, माप(*sbridge), GFP_KERNEL);
	अगर (!sbridge)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, sbridge);

	sbridge->info = of_device_get_match_data(&pdev->dev);

	/* Get the next bridge in the pipeline. */
	remote = of_graph_get_remote_node(pdev->dev.of_node, 1, -1);
	अगर (!remote)
		वापस -EINVAL;

	sbridge->next_bridge = of_drm_find_bridge(remote);
	of_node_put(remote);

	अगर (!sbridge->next_bridge) अणु
		dev_dbg(&pdev->dev, "Next bridge not found, deferring probe\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	/* Get the regulator and GPIO resources. */
	sbridge->vdd = devm_regulator_get_optional(&pdev->dev, "vdd");
	अगर (IS_ERR(sbridge->vdd)) अणु
		पूर्णांक ret = PTR_ERR(sbridge->vdd);
		अगर (ret == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		sbridge->vdd = शून्य;
		dev_dbg(&pdev->dev, "No vdd regulator found: %d\n", ret);
	पूर्ण

	sbridge->enable = devm_gpiod_get_optional(&pdev->dev, "enable",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(sbridge->enable)) अणु
		अगर (PTR_ERR(sbridge->enable) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Unable to retrieve enable GPIO\n");
		वापस PTR_ERR(sbridge->enable);
	पूर्ण

	/* Register the bridge. */
	sbridge->bridge.funcs = &simple_bridge_bridge_funcs;
	sbridge->bridge.of_node = pdev->dev.of_node;
	sbridge->bridge.timings = sbridge->info->timings;

	drm_bridge_add(&sbridge->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक simple_bridge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा simple_bridge *sbridge = platक्रमm_get_drvdata(pdev);

	drm_bridge_हटाओ(&sbridge->bridge);

	वापस 0;
पूर्ण

/*
 * We assume the ADV7123 DAC is the "default" क्रम historical reasons
 * Inक्रमmation taken from the ADV7123 datasheet, revision D.
 * NOTE: the ADV7123EP seems to have other timings and need a new timings
 * set अगर used.
 */
अटल स्थिर काष्ठा drm_bridge_timings शेष_bridge_timings = अणु
	/* Timing specअगरications, datasheet page 7 */
	.input_bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
	.setup_समय_ps = 500,
	.hold_समय_ps = 1500,
पूर्ण;

/*
 * Inक्रमmation taken from the THS8134, THS8134A, THS8134B datasheet named
 * "SLVS205D", dated May 1990, revised March 2000.
 */
अटल स्थिर काष्ठा drm_bridge_timings ti_ths8134_bridge_timings = अणु
	/* From timing diagram, datasheet page 9 */
	.input_bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
	/* From datasheet, page 12 */
	.setup_समय_ps = 3000,
	/* I guess this means latched input */
	.hold_समय_ps = 0,
पूर्ण;

/*
 * Inक्रमmation taken from the THS8135 datasheet named "SLAS343B", dated
 * May 2001, revised April 2013.
 */
अटल स्थिर काष्ठा drm_bridge_timings ti_ths8135_bridge_timings = अणु
	/* From timing diagram, datasheet page 14 */
	.input_bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
	/* From datasheet, page 16 */
	.setup_समय_ps = 2000,
	.hold_समय_ps = 500,
पूर्ण;

अटल स्थिर काष्ठा of_device_id simple_bridge_match[] = अणु
	अणु
		.compatible = "dumb-vga-dac",
		.data = &(स्थिर काष्ठा simple_bridge_info) अणु
			.connector_type = DRM_MODE_CONNECTOR_VGA,
		पूर्ण,
	पूर्ण, अणु
		.compatible = "adi,adv7123",
		.data = &(स्थिर काष्ठा simple_bridge_info) अणु
			.timings = &शेष_bridge_timings,
			.connector_type = DRM_MODE_CONNECTOR_VGA,
		पूर्ण,
	पूर्ण, अणु
		.compatible = "ti,opa362",
		.data = &(स्थिर काष्ठा simple_bridge_info) अणु
			.connector_type = DRM_MODE_CONNECTOR_Composite,
		पूर्ण,
	पूर्ण, अणु
		.compatible = "ti,ths8135",
		.data = &(स्थिर काष्ठा simple_bridge_info) अणु
			.timings = &ti_ths8135_bridge_timings,
			.connector_type = DRM_MODE_CONNECTOR_VGA,
		पूर्ण,
	पूर्ण, अणु
		.compatible = "ti,ths8134",
		.data = &(स्थिर काष्ठा simple_bridge_info) अणु
			.timings = &ti_ths8134_bridge_timings,
			.connector_type = DRM_MODE_CONNECTOR_VGA,
		पूर्ण,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, simple_bridge_match);

अटल काष्ठा platक्रमm_driver simple_bridge_driver = अणु
	.probe	= simple_bridge_probe,
	.हटाओ	= simple_bridge_हटाओ,
	.driver		= अणु
		.name		= "simple-bridge",
		.of_match_table	= simple_bridge_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(simple_bridge_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Simple DRM bridge driver");
MODULE_LICENSE("GPL");
