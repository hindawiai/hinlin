<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Texas Instruments
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा HOTPLUG_DEBOUNCE_MS		1100

काष्ठा tfp410 अणु
	काष्ठा drm_bridge	bridge;
	काष्ठा drm_connector	connector;

	u32			bus_क्रमmat;
	काष्ठा delayed_work	hpd_work;
	काष्ठा gpio_desc	*घातerकरोwn;

	काष्ठा drm_bridge_timings timings;
	काष्ठा drm_bridge	*next_bridge;

	काष्ठा device *dev;
पूर्ण;

अटल अंतरभूत काष्ठा tfp410 *
drm_bridge_to_tfp410(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा tfp410, bridge);
पूर्ण

अटल अंतरभूत काष्ठा tfp410 *
drm_connector_to_tfp410(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा tfp410, connector);
पूर्ण

अटल पूर्णांक tfp410_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा tfp410 *dvi = drm_connector_to_tfp410(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	अगर (dvi->next_bridge->ops & DRM_BRIDGE_OP_EDID) अणु
		edid = drm_bridge_get_edid(dvi->next_bridge, connector);
		अगर (!edid)
			DRM_INFO("EDID read failed. Fallback to standard modes\n");
	पूर्ण अन्यथा अणु
		edid = शून्य;
	पूर्ण

	अगर (!edid) अणु
		/*
		 * No EDID, fallback on the XGA standard modes and prefer a mode
		 * pretty much anything can handle.
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

अटल स्थिर काष्ठा drm_connector_helper_funcs tfp410_con_helper_funcs = अणु
	.get_modes	= tfp410_get_modes,
पूर्ण;

अटल क्रमागत drm_connector_status
tfp410_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा tfp410 *dvi = drm_connector_to_tfp410(connector);

	वापस drm_bridge_detect(dvi->next_bridge);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs tfp410_con_funcs = अणु
	.detect			= tfp410_connector_detect,
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= drm_connector_cleanup,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल व्योम tfp410_hpd_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tfp410 *dvi;

	dvi = container_of(work, काष्ठा tfp410, hpd_work.work);

	अगर (dvi->bridge.dev)
		drm_helper_hpd_irq_event(dvi->bridge.dev);
पूर्ण

अटल व्योम tfp410_hpd_callback(व्योम *arg, क्रमागत drm_connector_status status)
अणु
	काष्ठा tfp410 *dvi = arg;

	mod_delayed_work(प्रणाली_wq, &dvi->hpd_work,
			 msecs_to_jअगरfies(HOTPLUG_DEBOUNCE_MS));
पूर्ण

अटल पूर्णांक tfp410_attach(काष्ठा drm_bridge *bridge,
			 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा tfp410 *dvi = drm_bridge_to_tfp410(bridge);
	पूर्णांक ret;

	ret = drm_bridge_attach(bridge->encoder, dvi->next_bridge, bridge,
				DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret < 0)
		वापस ret;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	अगर (!bridge->encoder) अणु
		dev_err(dvi->dev, "Missing encoder\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dvi->next_bridge->ops & DRM_BRIDGE_OP_DETECT)
		dvi->connector.polled = DRM_CONNECTOR_POLL_HPD;
	अन्यथा
		dvi->connector.polled = DRM_CONNECTOR_POLL_CONNECT | DRM_CONNECTOR_POLL_DISCONNECT;

	अगर (dvi->next_bridge->ops & DRM_BRIDGE_OP_HPD) अणु
		INIT_DELAYED_WORK(&dvi->hpd_work, tfp410_hpd_work_func);
		drm_bridge_hpd_enable(dvi->next_bridge, tfp410_hpd_callback,
				      dvi);
	पूर्ण

	drm_connector_helper_add(&dvi->connector,
				 &tfp410_con_helper_funcs);
	ret = drm_connector_init_with_ddc(bridge->dev, &dvi->connector,
					  &tfp410_con_funcs,
					  dvi->next_bridge->type,
					  dvi->next_bridge->ddc);
	अगर (ret) अणु
		dev_err(dvi->dev, "drm_connector_init_with_ddc() failed: %d\n",
			ret);
		वापस ret;
	पूर्ण

	drm_display_info_set_bus_क्रमmats(&dvi->connector.display_info,
					 &dvi->bus_क्रमmat, 1);

	drm_connector_attach_encoder(&dvi->connector, bridge->encoder);

	वापस 0;
पूर्ण

अटल व्योम tfp410_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tfp410 *dvi = drm_bridge_to_tfp410(bridge);

	अगर (dvi->connector.dev && dvi->next_bridge->ops & DRM_BRIDGE_OP_HPD) अणु
		drm_bridge_hpd_disable(dvi->next_bridge);
		cancel_delayed_work_sync(&dvi->hpd_work);
	पूर्ण
पूर्ण

अटल व्योम tfp410_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tfp410 *dvi = drm_bridge_to_tfp410(bridge);

	gpiod_set_value_cansleep(dvi->घातerकरोwn, 0);
पूर्ण

अटल व्योम tfp410_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tfp410 *dvi = drm_bridge_to_tfp410(bridge);

	gpiod_set_value_cansleep(dvi->घातerकरोwn, 1);
पूर्ण

अटल क्रमागत drm_mode_status tfp410_mode_valid(काष्ठा drm_bridge *bridge,
					      स्थिर काष्ठा drm_display_info *info,
					      स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी < 25000)
		वापस MODE_CLOCK_LOW;

	अगर (mode->घड़ी > 165000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tfp410_bridge_funcs = अणु
	.attach		= tfp410_attach,
	.detach		= tfp410_detach,
	.enable		= tfp410_enable,
	.disable	= tfp410_disable,
	.mode_valid	= tfp410_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_bridge_timings tfp410_शेष_timings = अणु
	.input_bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE
			 | DRM_BUS_FLAG_DE_HIGH,
	.setup_समय_ps = 1200,
	.hold_समय_ps = 1300,
पूर्ण;

अटल पूर्णांक tfp410_parse_timings(काष्ठा tfp410 *dvi, bool i2c)
अणु
	काष्ठा drm_bridge_timings *timings = &dvi->timings;
	काष्ठा device_node *ep;
	u32 pclk_sample = 0;
	u32 bus_width = 24;
	u32 deskew = 0;

	/* Start with शेषs. */
	*timings = tfp410_शेष_timings;

	अगर (i2c)
		/*
		 * In I2C mode timings are configured through the I2C पूर्णांकerface.
		 * As the driver करोesn't support I2C configuration yet, we just
		 * go with the शेषs (BSEL=1, DSEL=1, DKEN=0, EDGE=1).
		 */
		वापस 0;

	/*
	 * In non-I2C mode, timings are configured through the BSEL, DSEL, DKEN
	 * and EDGE pins. They are specअगरied in DT through endpoपूर्णांक properties
	 * and venकरोr-specअगरic properties.
	 */
	ep = of_graph_get_endpoपूर्णांक_by_regs(dvi->dev->of_node, 0, 0);
	अगर (!ep)
		वापस -EINVAL;

	/* Get the sampling edge from the endpoपूर्णांक. */
	of_property_पढ़ो_u32(ep, "pclk-sample", &pclk_sample);
	of_property_पढ़ो_u32(ep, "bus-width", &bus_width);
	of_node_put(ep);

	timings->input_bus_flags = DRM_BUS_FLAG_DE_HIGH;

	चयन (pclk_sample) अणु
	हाल 0:
		timings->input_bus_flags |= DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE
					 |  DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE;
		अवरोध;
	हाल 1:
		timings->input_bus_flags |= DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE
					 |  DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (bus_width) अणु
	हाल 12:
		dvi->bus_क्रमmat = MEDIA_BUS_FMT_RGB888_2X12_LE;
		अवरोध;
	हाल 24:
		dvi->bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Get the setup and hold समय from venकरोr-specअगरic properties. */
	of_property_पढ़ो_u32(dvi->dev->of_node, "ti,deskew", &deskew);
	अगर (deskew > 7)
		वापस -EINVAL;

	timings->setup_समय_ps = 1200 - 350 * ((s32)deskew - 4);
	timings->hold_समय_ps = max(0, 1300 + 350 * ((s32)deskew - 4));

	वापस 0;
पूर्ण

अटल पूर्णांक tfp410_init(काष्ठा device *dev, bool i2c)
अणु
	काष्ठा device_node *node;
	काष्ठा tfp410 *dvi;
	पूर्णांक ret;

	अगर (!dev->of_node) अणु
		dev_err(dev, "device-tree data is missing\n");
		वापस -ENXIO;
	पूर्ण

	dvi = devm_kzalloc(dev, माप(*dvi), GFP_KERNEL);
	अगर (!dvi)
		वापस -ENOMEM;

	dvi->dev = dev;
	dev_set_drvdata(dev, dvi);

	dvi->bridge.funcs = &tfp410_bridge_funcs;
	dvi->bridge.of_node = dev->of_node;
	dvi->bridge.timings = &dvi->timings;
	dvi->bridge.type = DRM_MODE_CONNECTOR_DVID;

	ret = tfp410_parse_timings(dvi, i2c);
	अगर (ret)
		वापस ret;

	/* Get the next bridge, connected to port@1. */
	node = of_graph_get_remote_node(dev->of_node, 1, -1);
	अगर (!node)
		वापस -ENODEV;

	dvi->next_bridge = of_drm_find_bridge(node);
	of_node_put(node);

	अगर (!dvi->next_bridge)
		वापस -EPROBE_DEFER;

	/* Get the घातerकरोwn GPIO. */
	dvi->घातerकरोwn = devm_gpiod_get_optional(dev, "powerdown",
						 GPIOD_OUT_HIGH);
	अगर (IS_ERR(dvi->घातerकरोwn)) अणु
		dev_err(dev, "failed to parse powerdown gpio\n");
		वापस PTR_ERR(dvi->घातerकरोwn);
	पूर्ण

	/*  Register the DRM bridge. */
	drm_bridge_add(&dvi->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक tfp410_fini(काष्ठा device *dev)
अणु
	काष्ठा tfp410 *dvi = dev_get_drvdata(dev);

	drm_bridge_हटाओ(&dvi->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक tfp410_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस tfp410_init(&pdev->dev, false);
पूर्ण

अटल पूर्णांक tfp410_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस tfp410_fini(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id tfp410_match[] = अणु
	अणु .compatible = "ti,tfp410" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tfp410_match);

अटल काष्ठा platक्रमm_driver tfp410_platक्रमm_driver = अणु
	.probe	= tfp410_probe,
	.हटाओ	= tfp410_हटाओ,
	.driver	= अणु
		.name		= "tfp410-bridge",
		.of_match_table	= tfp410_match,
	पूर्ण,
पूर्ण;

#अगर IS_ENABLED(CONFIG_I2C)
/* There is currently no i2c functionality. */
अटल पूर्णांक tfp410_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक reg;

	अगर (!client->dev.of_node ||
	    of_property_पढ़ो_u32(client->dev.of_node, "reg", &reg)) अणु
		dev_err(&client->dev,
			"Can't get i2c reg property from device-tree\n");
		वापस -ENXIO;
	पूर्ण

	वापस tfp410_init(&client->dev, true);
पूर्ण

अटल पूर्णांक tfp410_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस tfp410_fini(&client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tfp410_i2c_ids[] = अणु
	अणु "tfp410", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tfp410_i2c_ids);

अटल काष्ठा i2c_driver tfp410_i2c_driver = अणु
	.driver = अणु
		.name	= "tfp410",
		.of_match_table = of_match_ptr(tfp410_match),
	पूर्ण,
	.id_table	= tfp410_i2c_ids,
	.probe		= tfp410_i2c_probe,
	.हटाओ		= tfp410_i2c_हटाओ,
पूर्ण;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C) */

अटल काष्ठा अणु
	uपूर्णांक i2c:1;
	uपूर्णांक platक्रमm:1;
पूर्ण  tfp410_रेजिस्टरed_driver;

अटल पूर्णांक __init tfp410_module_init(व्योम)
अणु
	पूर्णांक ret;

#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&tfp410_i2c_driver);
	अगर (ret)
		pr_err("%s: registering i2c driver failed: %d",
		       __func__, ret);
	अन्यथा
		tfp410_रेजिस्टरed_driver.i2c = 1;
#पूर्ण_अगर

	ret = platक्रमm_driver_रेजिस्टर(&tfp410_platक्रमm_driver);
	अगर (ret)
		pr_err("%s: registering platform driver failed: %d",
		       __func__, ret);
	अन्यथा
		tfp410_रेजिस्टरed_driver.platक्रमm = 1;

	अगर (tfp410_रेजिस्टरed_driver.i2c ||
	    tfp410_रेजिस्टरed_driver.platक्रमm)
		वापस 0;

	वापस ret;
पूर्ण
module_init(tfp410_module_init);

अटल व्योम __निकास tfp410_module_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	अगर (tfp410_रेजिस्टरed_driver.i2c)
		i2c_del_driver(&tfp410_i2c_driver);
#पूर्ण_अगर
	अगर (tfp410_रेजिस्टरed_driver.platक्रमm)
		platक्रमm_driver_unरेजिस्टर(&tfp410_platक्रमm_driver);
पूर्ण
module_निकास(tfp410_module_निकास);

MODULE_AUTHOR("Jyri Sarha <jsarha@ti.com>");
MODULE_DESCRIPTION("TI TFP410 DVI bridge driver");
MODULE_LICENSE("GPL");
