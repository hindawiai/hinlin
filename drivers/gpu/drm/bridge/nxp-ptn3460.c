<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NXP PTN3460 DP/LVDS bridge driver
 *
 * Copyright (C) 2013 Google, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा PTN3460_EDID_ADDR			0x0
#घोषणा PTN3460_EDID_EMULATION_ADDR		0x84
#घोषणा PTN3460_EDID_ENABLE_EMULATION		0
#घोषणा PTN3460_EDID_EMULATION_SELECTION	1
#घोषणा PTN3460_EDID_SRAM_LOAD_ADDR		0x85

काष्ठा ptn3460_bridge अणु
	काष्ठा drm_connector connector;
	काष्ठा i2c_client *client;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा gpio_desc *gpio_pd_n;
	काष्ठा gpio_desc *gpio_rst_n;
	u32 edid_emulation;
	bool enabled;
पूर्ण;

अटल अंतरभूत काष्ठा ptn3460_bridge *
		bridge_to_ptn3460(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा ptn3460_bridge, bridge);
पूर्ण

अटल अंतरभूत काष्ठा ptn3460_bridge *
		connector_to_ptn3460(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा ptn3460_bridge, connector);
पूर्ण

अटल पूर्णांक ptn3460_पढ़ो_bytes(काष्ठा ptn3460_bridge *ptn_bridge, अक्षर addr,
		u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;

	ret = i2c_master_send(ptn_bridge->client, &addr, 1);
	अगर (ret <= 0) अणु
		DRM_ERROR("Failed to send i2c command, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(ptn_bridge->client, buf, len);
	अगर (ret <= 0) अणु
		DRM_ERROR("Failed to recv i2c data, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ptn3460_ग_लिखो_byte(काष्ठा ptn3460_bridge *ptn_bridge, अक्षर addr,
		अक्षर val)
अणु
	पूर्णांक ret;
	अक्षर buf[2];

	buf[0] = addr;
	buf[1] = val;

	ret = i2c_master_send(ptn_bridge->client, buf, ARRAY_SIZE(buf));
	अगर (ret <= 0) अणु
		DRM_ERROR("Failed to send i2c command, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ptn3460_select_edid(काष्ठा ptn3460_bridge *ptn_bridge)
अणु
	पूर्णांक ret;
	अक्षर val;

	/* Load the selected edid पूर्णांकo SRAM (accessed at PTN3460_EDID_ADDR) */
	ret = ptn3460_ग_लिखो_byte(ptn_bridge, PTN3460_EDID_SRAM_LOAD_ADDR,
			ptn_bridge->edid_emulation);
	अगर (ret) अणु
		DRM_ERROR("Failed to transfer EDID to sram, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable EDID emulation and select the desired EDID */
	val = 1 << PTN3460_EDID_ENABLE_EMULATION |
		ptn_bridge->edid_emulation << PTN3460_EDID_EMULATION_SELECTION;

	ret = ptn3460_ग_लिखो_byte(ptn_bridge, PTN3460_EDID_EMULATION_ADDR, val);
	अगर (ret) अणु
		DRM_ERROR("Failed to write EDID value, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ptn3460_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ptn3460_bridge *ptn_bridge = bridge_to_ptn3460(bridge);
	पूर्णांक ret;

	अगर (ptn_bridge->enabled)
		वापस;

	gpiod_set_value(ptn_bridge->gpio_pd_n, 1);

	gpiod_set_value(ptn_bridge->gpio_rst_n, 0);
	usleep_range(10, 20);
	gpiod_set_value(ptn_bridge->gpio_rst_n, 1);

	/*
	 * There's a bug in the PTN chip where it falsely निश्चितs hotplug beक्रमe
	 * it is fully functional. We're क्रमced to रुको क्रम the maximum start up
	 * समय specअगरied in the chip's datasheet to make sure we're really up.
	 */
	msleep(90);

	ret = ptn3460_select_edid(ptn_bridge);
	अगर (ret)
		DRM_ERROR("Select EDID failed ret=%d\n", ret);

	ptn_bridge->enabled = true;
पूर्ण

अटल व्योम ptn3460_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ptn3460_bridge *ptn_bridge = bridge_to_ptn3460(bridge);

	अगर (!ptn_bridge->enabled)
		वापस;

	ptn_bridge->enabled = false;

	gpiod_set_value(ptn_bridge->gpio_rst_n, 1);
	gpiod_set_value(ptn_bridge->gpio_pd_n, 0);
पूर्ण


अटल काष्ठा edid *ptn3460_get_edid(काष्ठा drm_bridge *bridge,
				     काष्ठा drm_connector *connector)
अणु
	काष्ठा ptn3460_bridge *ptn_bridge = bridge_to_ptn3460(bridge);
	bool घातer_off;
	u8 *edid;
	पूर्णांक ret;

	घातer_off = !ptn_bridge->enabled;
	ptn3460_pre_enable(&ptn_bridge->bridge);

	edid = kदो_स्मृति(EDID_LENGTH, GFP_KERNEL);
	अगर (!edid) अणु
		DRM_ERROR("Failed to allocate EDID\n");
		जाओ out;
	पूर्ण

	ret = ptn3460_पढ़ो_bytes(ptn_bridge, PTN3460_EDID_ADDR, edid,
				 EDID_LENGTH);
	अगर (ret) अणु
		kमुक्त(edid);
		edid = शून्य;
		जाओ out;
	पूर्ण

out:
	अगर (घातer_off)
		ptn3460_disable(&ptn_bridge->bridge);

	वापस (काष्ठा edid *)edid;
पूर्ण

अटल पूर्णांक ptn3460_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा ptn3460_bridge *ptn_bridge = connector_to_ptn3460(connector);
	काष्ठा edid *edid;
	पूर्णांक num_modes;

	edid = ptn3460_get_edid(&ptn_bridge->bridge, connector);
	drm_connector_update_edid_property(connector, edid);
	num_modes = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस num_modes;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs ptn3460_connector_helper_funcs = अणु
	.get_modes = ptn3460_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs ptn3460_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक ptn3460_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा ptn3460_bridge *ptn_bridge = bridge_to_ptn3460(bridge);
	पूर्णांक ret;

	/* Let this driver create connector अगर requested */
	ret = drm_bridge_attach(bridge->encoder, ptn_bridge->panel_bridge,
				bridge, flags | DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret < 0)
		वापस ret;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	ptn_bridge->connector.polled = DRM_CONNECTOR_POLL_HPD;
	ret = drm_connector_init(bridge->dev, &ptn_bridge->connector,
			&ptn3460_connector_funcs, DRM_MODE_CONNECTOR_LVDS);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण
	drm_connector_helper_add(&ptn_bridge->connector,
					&ptn3460_connector_helper_funcs);
	drm_connector_रेजिस्टर(&ptn_bridge->connector);
	drm_connector_attach_encoder(&ptn_bridge->connector,
							bridge->encoder);

	drm_helper_hpd_irq_event(ptn_bridge->connector.dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs ptn3460_bridge_funcs = अणु
	.pre_enable = ptn3460_pre_enable,
	.disable = ptn3460_disable,
	.attach = ptn3460_bridge_attach,
	.get_edid = ptn3460_get_edid,
पूर्ण;

अटल पूर्णांक ptn3460_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ptn3460_bridge *ptn_bridge;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	ptn_bridge = devm_kzalloc(dev, माप(*ptn_bridge), GFP_KERNEL);
	अगर (!ptn_bridge) अणु
		वापस -ENOMEM;
	पूर्ण

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0, &panel, शून्य);
	अगर (ret)
		वापस ret;

	panel_bridge = devm_drm_panel_bridge_add(dev, panel);
	अगर (IS_ERR(panel_bridge))
		वापस PTR_ERR(panel_bridge);

	ptn_bridge->panel_bridge = panel_bridge;
	ptn_bridge->client = client;

	ptn_bridge->gpio_pd_n = devm_gpiod_get(&client->dev, "powerdown",
					       GPIOD_OUT_HIGH);
	अगर (IS_ERR(ptn_bridge->gpio_pd_n)) अणु
		ret = PTR_ERR(ptn_bridge->gpio_pd_n);
		dev_err(dev, "cannot get gpio_pd_n %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Request the reset pin low to aव्योम the bridge being
	 * initialized prematurely
	 */
	ptn_bridge->gpio_rst_n = devm_gpiod_get(&client->dev, "reset",
						GPIOD_OUT_LOW);
	अगर (IS_ERR(ptn_bridge->gpio_rst_n)) अणु
		ret = PTR_ERR(ptn_bridge->gpio_rst_n);
		DRM_ERROR("cannot get gpio_rst_n %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "edid-emulation",
			&ptn_bridge->edid_emulation);
	अगर (ret) अणु
		dev_err(dev, "Can't read EDID emulation value\n");
		वापस ret;
	पूर्ण

	ptn_bridge->bridge.funcs = &ptn3460_bridge_funcs;
	ptn_bridge->bridge.ops = DRM_BRIDGE_OP_EDID;
	ptn_bridge->bridge.type = DRM_MODE_CONNECTOR_LVDS;
	ptn_bridge->bridge.of_node = dev->of_node;
	drm_bridge_add(&ptn_bridge->bridge);

	i2c_set_clientdata(client, ptn_bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक ptn3460_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ptn3460_bridge *ptn_bridge = i2c_get_clientdata(client);

	drm_bridge_हटाओ(&ptn_bridge->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ptn3460_i2c_table[] = अणु
	अणु"ptn3460", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ptn3460_i2c_table);

अटल स्थिर काष्ठा of_device_id ptn3460_match[] = अणु
	अणु .compatible = "nxp,ptn3460" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ptn3460_match);

अटल काष्ठा i2c_driver ptn3460_driver = अणु
	.id_table	= ptn3460_i2c_table,
	.probe		= ptn3460_probe,
	.हटाओ		= ptn3460_हटाओ,
	.driver		= अणु
		.name	= "nxp,ptn3460",
		.of_match_table = ptn3460_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(ptn3460_driver);

MODULE_AUTHOR("Sean Paul <seanpaul@chromium.org>");
MODULE_DESCRIPTION("NXP ptn3460 eDP-LVDS converter driver");
MODULE_LICENSE("GPL v2");
