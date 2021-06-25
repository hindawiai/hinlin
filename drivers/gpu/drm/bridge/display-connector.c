<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>

काष्ठा display_connector अणु
	काष्ठा drm_bridge	bridge;

	काष्ठा gpio_desc	*hpd_gpio;
	पूर्णांक			hpd_irq;

	काष्ठा regulator	*dp_pwr;
पूर्ण;

अटल अंतरभूत काष्ठा display_connector *
to_display_connector(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा display_connector, bridge);
पूर्ण

अटल पूर्णांक display_connector_attach(काष्ठा drm_bridge *bridge,
				    क्रमागत drm_bridge_attach_flags flags)
अणु
	वापस flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR ? 0 : -EINVAL;
पूर्ण

अटल क्रमागत drm_connector_status
display_connector_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा display_connector *conn = to_display_connector(bridge);

	अगर (conn->hpd_gpio) अणु
		अगर (gpiod_get_value_cansleep(conn->hpd_gpio))
			वापस connector_status_connected;
		अन्यथा
			वापस connector_status_disconnected;
	पूर्ण

	अगर (conn->bridge.ddc && drm_probe_ddc(conn->bridge.ddc))
		वापस connector_status_connected;

	चयन (conn->bridge.type) अणु
	हाल DRM_MODE_CONNECTOR_DVIA:
	हाल DRM_MODE_CONNECTOR_DVID:
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_HDMIA:
	हाल DRM_MODE_CONNECTOR_HDMIB:
		/*
		 * For DVI and HDMI connectors a DDC probe failure indicates
		 * that no cable is connected.
		 */
		वापस connector_status_disconnected;

	हाल DRM_MODE_CONNECTOR_Composite:
	हाल DRM_MODE_CONNECTOR_SVIDEO:
	हाल DRM_MODE_CONNECTOR_VGA:
	शेष:
		/*
		 * Composite and S-Video connectors have no other detection
		 * mean than the HPD GPIO. For VGA connectors, even अगर we have
		 * an I2C bus, we can't assume that the cable is disconnected
		 * अगर drm_probe_ddc fails, as some cables करोn't wire the DDC
		 * pins.
		 */
		वापस connector_status_unknown;
	पूर्ण
पूर्ण

अटल काष्ठा edid *display_connector_get_edid(काष्ठा drm_bridge *bridge,
					       काष्ठा drm_connector *connector)
अणु
	काष्ठा display_connector *conn = to_display_connector(bridge);

	वापस drm_get_edid(connector, conn->bridge.ddc);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs display_connector_bridge_funcs = अणु
	.attach = display_connector_attach,
	.detect = display_connector_detect,
	.get_edid = display_connector_get_edid,
पूर्ण;

अटल irqवापस_t display_connector_hpd_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा display_connector *conn = arg;
	काष्ठा drm_bridge *bridge = &conn->bridge;

	drm_bridge_hpd_notअगरy(bridge, display_connector_detect(bridge));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक display_connector_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा display_connector *conn;
	अचिन्हित पूर्णांक type;
	स्थिर अक्षर *label;
	पूर्णांक ret;

	conn = devm_kzalloc(&pdev->dev, माप(*conn), GFP_KERNEL);
	अगर (!conn)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, conn);

	type = (uपूर्णांकptr_t)of_device_get_match_data(&pdev->dev);

	/* Get the exact connector type. */
	चयन (type) अणु
	हाल DRM_MODE_CONNECTOR_DVII: अणु
		bool analog, digital;

		analog = of_property_पढ़ो_bool(pdev->dev.of_node, "analog");
		digital = of_property_पढ़ो_bool(pdev->dev.of_node, "digital");
		अगर (analog && !digital) अणु
			conn->bridge.type = DRM_MODE_CONNECTOR_DVIA;
		पूर्ण अन्यथा अगर (!analog && digital) अणु
			conn->bridge.type = DRM_MODE_CONNECTOR_DVID;
		पूर्ण अन्यथा अगर (analog && digital) अणु
			conn->bridge.type = DRM_MODE_CONNECTOR_DVII;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "DVI connector with no type\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल DRM_MODE_CONNECTOR_HDMIA: अणु
		स्थिर अक्षर *hdmi_type;

		ret = of_property_पढ़ो_string(pdev->dev.of_node, "type",
					      &hdmi_type);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "HDMI connector with no type\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!म_भेद(hdmi_type, "a") || !म_भेद(hdmi_type, "c") ||
		    !म_भेद(hdmi_type, "d") || !म_भेद(hdmi_type, "e")) अणु
			conn->bridge.type = DRM_MODE_CONNECTOR_HDMIA;
		पूर्ण अन्यथा अगर (!म_भेद(hdmi_type, "b")) अणु
			conn->bridge.type = DRM_MODE_CONNECTOR_HDMIB;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev,
				"Unsupported HDMI connector type '%s'\n",
				hdmi_type);
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	पूर्ण

	शेष:
		conn->bridge.type = type;
		अवरोध;
	पूर्ण

	/* All the supported connector types support पूर्णांकerlaced modes. */
	conn->bridge.पूर्णांकerlace_allowed = true;

	/* Get the optional connector label. */
	of_property_पढ़ो_string(pdev->dev.of_node, "label", &label);

	/*
	 * Get the HPD GPIO क्रम DVI, HDMI and DP connectors. If the GPIO can provide
	 * edge पूर्णांकerrupts, रेजिस्टर an पूर्णांकerrupt handler.
	 */
	अगर (type == DRM_MODE_CONNECTOR_DVII ||
	    type == DRM_MODE_CONNECTOR_HDMIA ||
	    type == DRM_MODE_CONNECTOR_DisplayPort) अणु
		conn->hpd_gpio = devm_gpiod_get_optional(&pdev->dev, "hpd",
							 GPIOD_IN);
		अगर (IS_ERR(conn->hpd_gpio)) अणु
			अगर (PTR_ERR(conn->hpd_gpio) != -EPROBE_DEFER)
				dev_err(&pdev->dev,
					"Unable to retrieve HPD GPIO\n");
			वापस PTR_ERR(conn->hpd_gpio);
		पूर्ण

		conn->hpd_irq = gpiod_to_irq(conn->hpd_gpio);
	पूर्ण अन्यथा अणु
		conn->hpd_irq = -EINVAL;
	पूर्ण

	अगर (conn->hpd_irq >= 0) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, conn->hpd_irq,
						शून्य, display_connector_hpd_irq,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"HPD", conn);
		अगर (ret) अणु
			dev_info(&pdev->dev,
				 "Failed to request HPD edge interrupt, falling back to polling\n");
			conn->hpd_irq = -EINVAL;
		पूर्ण
	पूर्ण

	/* Retrieve the DDC I2C adapter क्रम DVI, HDMI and VGA connectors. */
	अगर (type == DRM_MODE_CONNECTOR_DVII ||
	    type == DRM_MODE_CONNECTOR_HDMIA ||
	    type == DRM_MODE_CONNECTOR_VGA) अणु
		काष्ठा device_node *phandle;

		phandle = of_parse_phandle(pdev->dev.of_node, "ddc-i2c-bus", 0);
		अगर (phandle) अणु
			conn->bridge.ddc = of_get_i2c_adapter_by_node(phandle);
			of_node_put(phandle);
			अगर (!conn->bridge.ddc)
				वापस -EPROBE_DEFER;
		पूर्ण अन्यथा अणु
			dev_dbg(&pdev->dev,
				"No I2C bus specified, disabling EDID readout\n");
		पूर्ण
	पूर्ण

	/* Get the DP PWR क्रम DP connector. */
	अगर (type == DRM_MODE_CONNECTOR_DisplayPort) अणु
		पूर्णांक ret;

		conn->dp_pwr = devm_regulator_get_optional(&pdev->dev, "dp-pwr");

		अगर (IS_ERR(conn->dp_pwr)) अणु
			ret = PTR_ERR(conn->dp_pwr);

			चयन (ret) अणु
			हाल -ENODEV:
				conn->dp_pwr = शून्य;
				अवरोध;

			हाल -EPROBE_DEFER:
				वापस -EPROBE_DEFER;

			शेष:
				dev_err(&pdev->dev, "failed to get DP PWR regulator: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (conn->dp_pwr) अणु
			ret = regulator_enable(conn->dp_pwr);
			अगर (ret) अणु
				dev_err(&pdev->dev, "failed to enable DP PWR regulator: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	conn->bridge.funcs = &display_connector_bridge_funcs;
	conn->bridge.of_node = pdev->dev.of_node;

	अगर (conn->bridge.ddc)
		conn->bridge.ops |= DRM_BRIDGE_OP_EDID
				 |  DRM_BRIDGE_OP_DETECT;
	अगर (conn->hpd_gpio)
		conn->bridge.ops |= DRM_BRIDGE_OP_DETECT;
	अगर (conn->hpd_irq >= 0)
		conn->bridge.ops |= DRM_BRIDGE_OP_HPD;

	dev_dbg(&pdev->dev,
		"Found %s display connector '%s' %s DDC bus and %s HPD GPIO (ops 0x%x)\n",
		drm_get_connector_type_name(conn->bridge.type),
		label ? label : "<unlabelled>",
		conn->bridge.ddc ? "with" : "without",
		conn->hpd_gpio ? "with" : "without",
		conn->bridge.ops);

	drm_bridge_add(&conn->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक display_connector_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा display_connector *conn = platक्रमm_get_drvdata(pdev);

	अगर (conn->dp_pwr)
		regulator_disable(conn->dp_pwr);

	drm_bridge_हटाओ(&conn->bridge);

	अगर (!IS_ERR(conn->bridge.ddc))
		i2c_put_adapter(conn->bridge.ddc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id display_connector_match[] = अणु
	अणु
		.compatible = "composite-video-connector",
		.data = (व्योम *)DRM_MODE_CONNECTOR_Composite,
	पूर्ण, अणु
		.compatible = "dvi-connector",
		.data = (व्योम *)DRM_MODE_CONNECTOR_DVII,
	पूर्ण, अणु
		.compatible = "hdmi-connector",
		.data = (व्योम *)DRM_MODE_CONNECTOR_HDMIA,
	पूर्ण, अणु
		.compatible = "svideo-connector",
		.data = (व्योम *)DRM_MODE_CONNECTOR_SVIDEO,
	पूर्ण, अणु
		.compatible = "vga-connector",
		.data = (व्योम *)DRM_MODE_CONNECTOR_VGA,
	पूर्ण, अणु
		.compatible = "dp-connector",
		.data = (व्योम *)DRM_MODE_CONNECTOR_DisplayPort,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, display_connector_match);

अटल काष्ठा platक्रमm_driver display_connector_driver = अणु
	.probe	= display_connector_probe,
	.हटाओ	= display_connector_हटाओ,
	.driver		= अणु
		.name		= "display-connector",
		.of_match_table	= display_connector_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(display_connector_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Display connector driver");
MODULE_LICENSE("GPL");
