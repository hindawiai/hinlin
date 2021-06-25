<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 MediaTek Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>

#घोषणा PAGE2_GPIO_H		0xa7
#घोषणा PS_GPIO9		BIT(1)
#घोषणा PAGE2_I2C_BYPASS	0xea
#घोषणा I2C_BYPASS_EN		0xd0
#घोषणा PAGE2_MCS_EN		0xf3
#घोषणा MCS_EN			BIT(0)
#घोषणा PAGE3_SET_ADD		0xfe
#घोषणा VDO_CTL_ADD		0x13
#घोषणा VDO_DIS			0x18
#घोषणा VDO_EN			0x1c
#घोषणा DP_NUM_LANES		4

/*
 * PS8640 uses multiple addresses:
 * page[0]: क्रम DP control
 * page[1]: क्रम VIDEO Bridge
 * page[2]: क्रम control top
 * page[3]: क्रम DSI Link Control1
 * page[4]: क्रम MIPI Phy
 * page[5]: क्रम VPLL
 * page[6]: क्रम DSI Link Control2
 * page[7]: क्रम SPI ROM mapping
 */
क्रमागत page_addr_offset अणु
	PAGE0_DP_CNTL = 0,
	PAGE1_VDO_BDG,
	PAGE2_TOP_CNTL,
	PAGE3_DSI_CNTL1,
	PAGE4_MIPI_PHY,
	PAGE5_VPLL,
	PAGE6_DSI_CNTL2,
	PAGE7_SPI_CNTL,
	MAX_DEVS
पूर्ण;

क्रमागत ps8640_vकरो_control अणु
	DISABLE = VDO_DIS,
	ENABLE = VDO_EN,
पूर्ण;

काष्ठा ps8640 अणु
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा i2c_client *page[MAX_DEVS];
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *gpio_reset;
	काष्ठा gpio_desc *gpio_घातerकरोwn;
	bool घातered;
पूर्ण;

अटल अंतरभूत काष्ठा ps8640 *bridge_to_ps8640(काष्ठा drm_bridge *e)
अणु
	वापस container_of(e, काष्ठा ps8640, bridge);
पूर्ण

अटल पूर्णांक ps8640_bridge_vकरो_control(काष्ठा ps8640 *ps_bridge,
				     स्थिर क्रमागत ps8640_vकरो_control ctrl)
अणु
	काष्ठा i2c_client *client = ps_bridge->page[PAGE3_DSI_CNTL1];
	u8 vकरो_ctrl_buf[] = अणु VDO_CTL_ADD, ctrl पूर्ण;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(client, PAGE3_SET_ADD,
					     माप(vकरो_ctrl_buf),
					     vकरो_ctrl_buf);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to %sable VDO: %d\n",
			  ctrl == ENABLE ? "en" : "dis", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ps8640_bridge_घातeron(काष्ठा ps8640 *ps_bridge)
अणु
	काष्ठा i2c_client *client = ps_bridge->page[PAGE2_TOP_CNTL];
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret, status;

	अगर (ps_bridge->घातered)
		वापस;

	ret = regulator_bulk_enable(ARRAY_SIZE(ps_bridge->supplies),
				    ps_bridge->supplies);
	अगर (ret < 0) अणु
		DRM_ERROR("cannot enable regulators %d\n", ret);
		वापस;
	पूर्ण

	gpiod_set_value(ps_bridge->gpio_घातerकरोwn, 0);
	gpiod_set_value(ps_bridge->gpio_reset, 1);
	usleep_range(2000, 2500);
	gpiod_set_value(ps_bridge->gpio_reset, 0);

	/*
	 * Wait क्रम the ps8640 embedded MCU to be पढ़ोy
	 * First रुको 200ms and then check the MCU पढ़ोy flag every 20ms
	 */
	msleep(200);

	समयout = jअगरfies + msecs_to_jअगरfies(200) + 1;

	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		status = i2c_smbus_पढ़ो_byte_data(client, PAGE2_GPIO_H);
		अगर (status < 0) अणु
			DRM_ERROR("failed read PAGE2_GPIO_H: %d\n", status);
			जाओ err_regulators_disable;
		पूर्ण
		अगर ((status & PS_GPIO9) == PS_GPIO9)
			अवरोध;

		msleep(20);
	पूर्ण

	msleep(50);

	/*
	 * The Manufacturer Command Set (MCS) is a device dependent पूर्णांकerface
	 * पूर्णांकended क्रम factory programming of the display module शेष
	 * parameters. Once the display module is configured, the MCS shall be
	 * disabled by the manufacturer. Once disabled, all MCS commands are
	 * ignored by the display पूर्णांकerface.
	 */
	status = i2c_smbus_पढ़ो_byte_data(client, PAGE2_MCS_EN);
	अगर (status < 0) अणु
		DRM_ERROR("failed read PAGE2_MCS_EN: %d\n", status);
		जाओ err_regulators_disable;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(client, PAGE2_MCS_EN,
					status & ~MCS_EN);
	अगर (ret < 0) अणु
		DRM_ERROR("failed write PAGE2_MCS_EN: %d\n", ret);
		जाओ err_regulators_disable;
	पूर्ण

	/* Switch access edp panel's edid through i2c */
	ret = i2c_smbus_ग_लिखो_byte_data(client, PAGE2_I2C_BYPASS,
					I2C_BYPASS_EN);
	अगर (ret < 0) अणु
		DRM_ERROR("failed write PAGE2_I2C_BYPASS: %d\n", ret);
		जाओ err_regulators_disable;
	पूर्ण

	ps_bridge->घातered = true;

	वापस;

err_regulators_disable:
	regulator_bulk_disable(ARRAY_SIZE(ps_bridge->supplies),
			       ps_bridge->supplies);
पूर्ण

अटल व्योम ps8640_bridge_घातeroff(काष्ठा ps8640 *ps_bridge)
अणु
	पूर्णांक ret;

	अगर (!ps_bridge->घातered)
		वापस;

	gpiod_set_value(ps_bridge->gpio_reset, 1);
	gpiod_set_value(ps_bridge->gpio_घातerकरोwn, 1);
	ret = regulator_bulk_disable(ARRAY_SIZE(ps_bridge->supplies),
				     ps_bridge->supplies);
	अगर (ret < 0)
		DRM_ERROR("cannot disable regulators %d\n", ret);

	ps_bridge->घातered = false;
पूर्ण

अटल व्योम ps8640_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ps8640 *ps_bridge = bridge_to_ps8640(bridge);
	पूर्णांक ret;

	ps8640_bridge_घातeron(ps_bridge);

	ret = ps8640_bridge_vकरो_control(ps_bridge, ENABLE);
	अगर (ret < 0)
		ps8640_bridge_घातeroff(ps_bridge);
पूर्ण

अटल व्योम ps8640_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ps8640 *ps_bridge = bridge_to_ps8640(bridge);

	ps8640_bridge_vकरो_control(ps_bridge, DISABLE);
	ps8640_bridge_घातeroff(ps_bridge);
पूर्ण

अटल पूर्णांक ps8640_bridge_attach(काष्ठा drm_bridge *bridge,
				क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा ps8640 *ps_bridge = bridge_to_ps8640(bridge);
	काष्ठा device *dev = &ps_bridge->page[0]->dev;
	काष्ठा device_node *in_ep, *dsi_node;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा mipi_dsi_host *host;
	पूर्णांक ret;
	स्थिर काष्ठा mipi_dsi_device_info info = अणु .type = "ps8640",
						   .channel = 0,
						   .node = शून्य,
						 पूर्ण;

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	/* port@0 is ps8640 dsi input port */
	in_ep = of_graph_get_endpoपूर्णांक_by_regs(dev->of_node, 0, -1);
	अगर (!in_ep)
		वापस -ENODEV;

	dsi_node = of_graph_get_remote_port_parent(in_ep);
	of_node_put(in_ep);
	अगर (!dsi_node)
		वापस -ENODEV;

	host = of_find_mipi_dsi_host_by_node(dsi_node);
	of_node_put(dsi_node);
	अगर (!host)
		वापस -ENODEV;

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		dev_err(dev, "failed to create dsi device\n");
		ret = PTR_ERR(dsi);
		वापस ret;
	पूर्ण

	ps_bridge->dsi = dsi;

	dsi->host = host;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
			  MIPI_DSI_MODE_VIDEO_SYNC_PULSE;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->lanes = DP_NUM_LANES;
	ret = mipi_dsi_attach(dsi);
	अगर (ret)
		जाओ err_dsi_attach;

	/* Attach the panel-bridge to the dsi bridge */
	वापस drm_bridge_attach(bridge->encoder, ps_bridge->panel_bridge,
				 &ps_bridge->bridge, flags);

err_dsi_attach:
	mipi_dsi_device_unरेजिस्टर(dsi);
	वापस ret;
पूर्ण

अटल काष्ठा edid *ps8640_bridge_get_edid(काष्ठा drm_bridge *bridge,
					   काष्ठा drm_connector *connector)
अणु
	काष्ठा ps8640 *ps_bridge = bridge_to_ps8640(bridge);
	bool घातeroff = !ps_bridge->घातered;
	काष्ठा edid *edid;

	/*
	 * When we end calling get_edid() triggered by an ioctl, i.e
	 *
	 *   drm_mode_अ_लोonnector (ioctl)
	 *     -> drm_helper_probe_single_connector_modes
	 *        -> drm_bridge_connector_get_modes
	 *           -> ps8640_bridge_get_edid
	 *
	 * We need to make sure that what we need is enabled beक्रमe पढ़ोing
	 * EDID, क्रम this chip, we need to करो a full घातeron, otherwise it will
	 * fail.
	 */
	drm_bridge_chain_pre_enable(bridge);

	edid = drm_get_edid(connector,
			    ps_bridge->page[PAGE0_DP_CNTL]->adapter);

	/*
	 * If we call the get_edid() function without having enabled the chip
	 * beक्रमe, वापस the chip to its original घातer state.
	 */
	अगर (घातeroff)
		drm_bridge_chain_post_disable(bridge);

	वापस edid;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs ps8640_bridge_funcs = अणु
	.attach = ps8640_bridge_attach,
	.get_edid = ps8640_bridge_get_edid,
	.post_disable = ps8640_post_disable,
	.pre_enable = ps8640_pre_enable,
पूर्ण;

अटल पूर्णांक ps8640_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा ps8640 *ps_bridge;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;
	u32 i;

	ps_bridge = devm_kzalloc(dev, माप(*ps_bridge), GFP_KERNEL);
	अगर (!ps_bridge)
		वापस -ENOMEM;

	/* port@1 is ps8640 output port */
	ret = drm_of_find_panel_or_bridge(np, 1, 0, &panel, शून्य);
	अगर (ret < 0)
		वापस ret;
	अगर (!panel)
		वापस -ENODEV;

	ps_bridge->panel_bridge = devm_drm_panel_bridge_add(dev, panel);
	अगर (IS_ERR(ps_bridge->panel_bridge))
		वापस PTR_ERR(ps_bridge->panel_bridge);

	ps_bridge->supplies[0].supply = "vdd33";
	ps_bridge->supplies[1].supply = "vdd12";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ps_bridge->supplies),
				      ps_bridge->supplies);
	अगर (ret)
		वापस ret;

	ps_bridge->gpio_घातerकरोwn = devm_gpiod_get(&client->dev, "powerdown",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(ps_bridge->gpio_घातerकरोwn))
		वापस PTR_ERR(ps_bridge->gpio_घातerकरोwn);

	/*
	 * Assert the reset to aव्योम the bridge being initialized prematurely
	 */
	ps_bridge->gpio_reset = devm_gpiod_get(&client->dev, "reset",
					       GPIOD_OUT_HIGH);
	अगर (IS_ERR(ps_bridge->gpio_reset))
		वापस PTR_ERR(ps_bridge->gpio_reset);

	ps_bridge->bridge.funcs = &ps8640_bridge_funcs;
	ps_bridge->bridge.of_node = dev->of_node;
	ps_bridge->bridge.ops = DRM_BRIDGE_OP_EDID;
	ps_bridge->bridge.type = DRM_MODE_CONNECTOR_eDP;

	ps_bridge->page[PAGE0_DP_CNTL] = client;

	क्रम (i = 1; i < ARRAY_SIZE(ps_bridge->page); i++) अणु
		ps_bridge->page[i] = devm_i2c_new_dummy_device(&client->dev,
							     client->adapter,
							     client->addr + i);
		अगर (IS_ERR(ps_bridge->page[i])) अणु
			dev_err(dev, "failed i2c dummy device, address %02x\n",
				client->addr + i);
			वापस PTR_ERR(ps_bridge->page[i]);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, ps_bridge);

	drm_bridge_add(&ps_bridge->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक ps8640_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ps8640 *ps_bridge = i2c_get_clientdata(client);

	drm_bridge_हटाओ(&ps_bridge->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ps8640_match[] = अणु
	अणु .compatible = "parade,ps8640" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ps8640_match);

अटल काष्ठा i2c_driver ps8640_driver = अणु
	.probe_new = ps8640_probe,
	.हटाओ = ps8640_हटाओ,
	.driver = अणु
		.name = "ps8640",
		.of_match_table = ps8640_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(ps8640_driver);

MODULE_AUTHOR("Jitao Shi <jitao.shi@mediatek.com>");
MODULE_AUTHOR("CK Hu <ck.hu@mediatek.com>");
MODULE_AUTHOR("Enric Balletbo i Serra <enric.balletbo@collabora.com>");
MODULE_DESCRIPTION("PARADE ps8640 DSI-eDP converter driver");
MODULE_LICENSE("GPL v2");
