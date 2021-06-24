<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Parade PS8622 eDP/LVDS bridge driver
 *
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

/* Brightness scale on the Parade chip */
#घोषणा PS8622_MAX_BRIGHTNESS 0xff

/* Timings taken from the version 1.7 datasheet क्रम the PS8622/PS8625 */
#घोषणा PS8622_POWER_RISE_T1_MIN_US 10
#घोषणा PS8622_POWER_RISE_T1_MAX_US 10000
#घोषणा PS8622_RST_HIGH_T2_MIN_US 3000
#घोषणा PS8622_RST_HIGH_T2_MAX_US 30000
#घोषणा PS8622_PWMO_END_T12_MS 200
#घोषणा PS8622_POWER_FALL_T16_MAX_US 10000
#घोषणा PS8622_POWER_OFF_T17_MS 500

#अगर ((PS8622_RST_HIGH_T2_MIN_US + PS8622_POWER_RISE_T1_MAX_US) > \
	(PS8622_RST_HIGH_T2_MAX_US + PS8622_POWER_RISE_T1_MIN_US))
#त्रुटि "T2.min + T1.max must be less than T2.max + T1.min"
#पूर्ण_अगर

काष्ठा ps8622_bridge अणु
	काष्ठा i2c_client *client;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा regulator *v12;
	काष्ठा backlight_device *bl;

	काष्ठा gpio_desc *gpio_slp;
	काष्ठा gpio_desc *gpio_rst;

	u32 max_lane_count;
	u32 lane_count;

	bool enabled;
पूर्ण;

अटल अंतरभूत काष्ठा ps8622_bridge *
		bridge_to_ps8622(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा ps8622_bridge, bridge);
पूर्ण

अटल पूर्णांक ps8622_set(काष्ठा i2c_client *client, u8 page, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा i2c_msg msg;
	u8 data[] = अणुreg, valपूर्ण;

	msg.addr = client->addr + page;
	msg.flags = 0;
	msg.len = माप(data);
	msg.buf = data;

	ret = i2c_transfer(adap, &msg, 1);
	अगर (ret != 1)
		pr_warn("PS8622 I2C write (0x%02x,0x%02x,0x%02x) failed: %d\n",
			client->addr + page, reg, val, ret);
	वापस !(ret == 1);
पूर्ण

अटल पूर्णांक ps8622_send_config(काष्ठा ps8622_bridge *ps8622)
अणु
	काष्ठा i2c_client *cl = ps8622->client;
	पूर्णांक err = 0;

	/* HPD low */
	err = ps8622_set(cl, 0x02, 0xa1, 0x01);
	अगर (err)
		जाओ error;

	/* SW setting: [1:0] SW output 1.2V voltage is lower to 96% */
	err = ps8622_set(cl, 0x04, 0x14, 0x01);
	अगर (err)
		जाओ error;

	/* RCO SS setting: [5:4] = b01 0.5%, b10 1%, b11 1.5% */
	err = ps8622_set(cl, 0x04, 0xe3, 0x20);
	अगर (err)
		जाओ error;

	/* [7] RCO SS enable */
	err = ps8622_set(cl, 0x04, 0xe2, 0x80);
	अगर (err)
		जाओ error;

	/* RPHY Setting
	 * [3:2] CDR tune रुको cycle beक्रमe measure क्रम fine tune
	 * b00: 1us b01: 0.5us b10:2us, b11: 4us
	 */
	err = ps8622_set(cl, 0x04, 0x8a, 0x0c);
	अगर (err)
		जाओ error;

	/* [3] RFD always on */
	err = ps8622_set(cl, 0x04, 0x89, 0x08);
	अगर (err)
		जाओ error;

	/* CTN lock in/out: 20000ppm/80000ppm. Lock out 2 बार. */
	err = ps8622_set(cl, 0x04, 0x71, 0x2d);
	अगर (err)
		जाओ error;

	/* 2.7G CDR settings: NOF=40LSB क्रम HBR CDR  setting */
	err = ps8622_set(cl, 0x04, 0x7d, 0x07);
	अगर (err)
		जाओ error;

	/* [1:0] Fmin=+4bands */
	err = ps8622_set(cl, 0x04, 0x7b, 0x00);
	अगर (err)
		जाओ error;

	/* [7:5] DCO_FTRNG=+-40% */
	err = ps8622_set(cl, 0x04, 0x7a, 0xfd);
	अगर (err)
		जाओ error;

	/* 1.62G CDR settings: [5:2]NOF=64LSB [1:0]DCO scale is 2/5 */
	err = ps8622_set(cl, 0x04, 0xc0, 0x12);
	अगर (err)
		जाओ error;

	/* Gitune=-37% */
	err = ps8622_set(cl, 0x04, 0xc1, 0x92);
	अगर (err)
		जाओ error;

	/* Fbstep=100% */
	err = ps8622_set(cl, 0x04, 0xc2, 0x1c);
	अगर (err)
		जाओ error;

	/* [7] LOS संकेत disable */
	err = ps8622_set(cl, 0x04, 0x32, 0x80);
	अगर (err)
		जाओ error;

	/* RPIO Setting: [7:4] LVDS driver bias current : 75% (250mV swing) */
	err = ps8622_set(cl, 0x04, 0x00, 0xb0);
	अगर (err)
		जाओ error;

	/* [7:6] Right-bar GPIO output strength is 8mA */
	err = ps8622_set(cl, 0x04, 0x15, 0x40);
	अगर (err)
		जाओ error;

	/* EQ Training State Machine Setting, RCO calibration start */
	err = ps8622_set(cl, 0x04, 0x54, 0x10);
	अगर (err)
		जाओ error;

	/* Logic, needs more than 10 I2C command */
	/* [4:0] MAX_LANE_COUNT set to max supported lanes */
	err = ps8622_set(cl, 0x01, 0x02, 0x80 | ps8622->max_lane_count);
	अगर (err)
		जाओ error;

	/* [4:0] LANE_COUNT_SET set to chosen lane count */
	err = ps8622_set(cl, 0x01, 0x21, 0x80 | ps8622->lane_count);
	अगर (err)
		जाओ error;

	err = ps8622_set(cl, 0x00, 0x52, 0x20);
	अगर (err)
		जाओ error;

	/* HPD CP toggle enable */
	err = ps8622_set(cl, 0x00, 0xf1, 0x03);
	अगर (err)
		जाओ error;

	err = ps8622_set(cl, 0x00, 0x62, 0x41);
	अगर (err)
		जाओ error;

	/* Counter number, add 1ms counter delay */
	err = ps8622_set(cl, 0x00, 0xf6, 0x01);
	अगर (err)
		जाओ error;

	/* [6]PWM function control by DPCD0040f[7], शेष is PWM block */
	err = ps8622_set(cl, 0x00, 0x77, 0x06);
	अगर (err)
		जाओ error;

	/* 04h Adjust VTotal toleranceto fix the 30Hz no display issue */
	err = ps8622_set(cl, 0x00, 0x4c, 0x04);
	अगर (err)
		जाओ error;

	/* DPCD00400='h00, Parade OUI ='h001cf8 */
	err = ps8622_set(cl, 0x01, 0xc0, 0x00);
	अगर (err)
		जाओ error;

	/* DPCD00401='h1c */
	err = ps8622_set(cl, 0x01, 0xc1, 0x1c);
	अगर (err)
		जाओ error;

	/* DPCD00402='hf8 */
	err = ps8622_set(cl, 0x01, 0xc2, 0xf8);
	अगर (err)
		जाओ error;

	/* DPCD403~408 = ASCII code, D2SLV5='h4432534c5635 */
	err = ps8622_set(cl, 0x01, 0xc3, 0x44);
	अगर (err)
		जाओ error;

	/* DPCD404 */
	err = ps8622_set(cl, 0x01, 0xc4, 0x32);
	अगर (err)
		जाओ error;

	/* DPCD405 */
	err = ps8622_set(cl, 0x01, 0xc5, 0x53);
	अगर (err)
		जाओ error;

	/* DPCD406 */
	err = ps8622_set(cl, 0x01, 0xc6, 0x4c);
	अगर (err)
		जाओ error;

	/* DPCD407 */
	err = ps8622_set(cl, 0x01, 0xc7, 0x56);
	अगर (err)
		जाओ error;

	/* DPCD408 */
	err = ps8622_set(cl, 0x01, 0xc8, 0x35);
	अगर (err)
		जाओ error;

	/* DPCD40A, Initial Code major revision '01' */
	err = ps8622_set(cl, 0x01, 0xca, 0x01);
	अगर (err)
		जाओ error;

	/* DPCD40B, Initial Code minor revision '05' */
	err = ps8622_set(cl, 0x01, 0xcb, 0x05);
	अगर (err)
		जाओ error;


	अगर (ps8622->bl) अणु
		/* DPCD720, पूर्णांकernal PWM */
		err = ps8622_set(cl, 0x01, 0xa5, 0xa0);
		अगर (err)
			जाओ error;

		/* FFh क्रम 100% brightness, 0h क्रम 0% brightness */
		err = ps8622_set(cl, 0x01, 0xa7,
				ps8622->bl->props.brightness);
		अगर (err)
			जाओ error;
	पूर्ण अन्यथा अणु
		/* DPCD720, बाह्यal PWM */
		err = ps8622_set(cl, 0x01, 0xa5, 0x80);
		अगर (err)
			जाओ error;
	पूर्ण

	/* Set LVDS output as 6bit-VESA mapping, single LVDS channel */
	err = ps8622_set(cl, 0x01, 0xcc, 0x13);
	अगर (err)
		जाओ error;

	/* Enable SSC set by रेजिस्टर */
	err = ps8622_set(cl, 0x02, 0xb1, 0x20);
	अगर (err)
		जाओ error;

	/* Set SSC enabled and +/-1% central spपढ़ोing */
	err = ps8622_set(cl, 0x04, 0x10, 0x16);
	अगर (err)
		जाओ error;

	/* Logic end */
	/* MPU Clock source: LC => RCO */
	err = ps8622_set(cl, 0x04, 0x59, 0x60);
	अगर (err)
		जाओ error;

	/* LC -> RCO */
	err = ps8622_set(cl, 0x04, 0x54, 0x14);
	अगर (err)
		जाओ error;

	/* HPD high */
	err = ps8622_set(cl, 0x02, 0xa1, 0x91);

error:
	वापस err ? -EIO : 0;
पूर्ण

अटल पूर्णांक ps8622_backlight_update(काष्ठा backlight_device *bl)
अणु
	काष्ठा ps8622_bridge *ps8622 = dev_get_drvdata(&bl->dev);
	पूर्णांक ret, brightness = bl->props.brightness;

	अगर (bl->props.घातer != FB_BLANK_UNBLANK ||
	    bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	अगर (!ps8622->enabled)
		वापस -EINVAL;

	ret = ps8622_set(ps8622->client, 0x01, 0xa7, brightness);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा backlight_ops ps8622_backlight_ops = अणु
	.update_status	= ps8622_backlight_update,
पूर्ण;

अटल व्योम ps8622_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ps8622_bridge *ps8622 = bridge_to_ps8622(bridge);
	पूर्णांक ret;

	अगर (ps8622->enabled)
		वापस;

	gpiod_set_value(ps8622->gpio_rst, 0);

	अगर (ps8622->v12) अणु
		ret = regulator_enable(ps8622->v12);
		अगर (ret)
			DRM_ERROR("fails to enable ps8622->v12");
	पूर्ण

	gpiod_set_value(ps8622->gpio_slp, 1);

	/*
	 * T1 is the range of समय that it takes क्रम the घातer to rise after we
	 * enable the lcd/ps8622 fet. T2 is the range of समय in which the
	 * data sheet specअगरies we should deनिश्चित the reset pin.
	 *
	 * If it takes T1.max क्रम the घातer to rise, we need to रुको atleast
	 * T2.min beक्रमe deनिश्चितing the reset pin. If it takes T1.min क्रम the
	 * घातer to rise, we need to रुको at most T2.max beक्रमe deनिश्चितing the
	 * reset pin.
	 */
	usleep_range(PS8622_RST_HIGH_T2_MIN_US + PS8622_POWER_RISE_T1_MAX_US,
		     PS8622_RST_HIGH_T2_MAX_US + PS8622_POWER_RISE_T1_MIN_US);

	gpiod_set_value(ps8622->gpio_rst, 1);

	/* रुको 20ms after RST high */
	usleep_range(20000, 30000);

	ret = ps8622_send_config(ps8622);
	अगर (ret) अणु
		DRM_ERROR("Failed to send config to bridge (%d)\n", ret);
		वापस;
	पूर्ण

	ps8622->enabled = true;
पूर्ण

अटल व्योम ps8622_disable(काष्ठा drm_bridge *bridge)
अणु
	/* Delay after panel is disabled */
	msleep(PS8622_PWMO_END_T12_MS);
पूर्ण

अटल व्योम ps8622_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ps8622_bridge *ps8622 = bridge_to_ps8622(bridge);

	अगर (!ps8622->enabled)
		वापस;

	ps8622->enabled = false;

	/*
	 * This करोesn't matter अगर the regulators are turned off, but something
	 * अन्यथा might keep them on. In that हाल, we want to निश्चित the slp gpio
	 * to lower घातer.
	 */
	gpiod_set_value(ps8622->gpio_slp, 0);

	अगर (ps8622->v12)
		regulator_disable(ps8622->v12);

	/*
	 * Sleep क्रम at least the amount of समय that it takes the घातer rail to
	 * fall to prevent निश्चितing the rst gpio from करोing anything.
	 */
	usleep_range(PS8622_POWER_FALL_T16_MAX_US,
		     2 * PS8622_POWER_FALL_T16_MAX_US);
	gpiod_set_value(ps8622->gpio_rst, 0);

	msleep(PS8622_POWER_OFF_T17_MS);
पूर्ण

अटल पूर्णांक ps8622_attach(काष्ठा drm_bridge *bridge,
			 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा ps8622_bridge *ps8622 = bridge_to_ps8622(bridge);

	वापस drm_bridge_attach(ps8622->bridge.encoder, ps8622->panel_bridge,
				 &ps8622->bridge, flags);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs ps8622_bridge_funcs = अणु
	.pre_enable = ps8622_pre_enable,
	.disable = ps8622_disable,
	.post_disable = ps8622_post_disable,
	.attach = ps8622_attach,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ps8622_devices[] = अणु
	अणु.compatible = "parade,ps8622",पूर्ण,
	अणु.compatible = "parade,ps8625",पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ps8622_devices);

अटल पूर्णांक ps8622_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ps8622_bridge *ps8622;
	काष्ठा drm_bridge *panel_bridge;
	काष्ठा drm_panel *panel;
	पूर्णांक ret;

	ps8622 = devm_kzalloc(dev, माप(*ps8622), GFP_KERNEL);
	अगर (!ps8622)
		वापस -ENOMEM;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0, &panel, शून्य);
	अगर (ret)
		वापस ret;

	panel_bridge = devm_drm_panel_bridge_add(dev, panel);
	अगर (IS_ERR(panel_bridge))
		वापस PTR_ERR(panel_bridge);

	ps8622->panel_bridge = panel_bridge;
	ps8622->client = client;

	ps8622->v12 = devm_regulator_get(dev, "vdd12");
	अगर (IS_ERR(ps8622->v12)) अणु
		dev_info(dev, "no 1.2v regulator found for PS8622\n");
		ps8622->v12 = शून्य;
	पूर्ण

	ps8622->gpio_slp = devm_gpiod_get(dev, "sleep", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ps8622->gpio_slp)) अणु
		ret = PTR_ERR(ps8622->gpio_slp);
		dev_err(dev, "cannot get gpio_slp %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Assert the reset pin high to aव्योम the bridge being
	 * initialized prematurely
	 */
	ps8622->gpio_rst = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ps8622->gpio_rst)) अणु
		ret = PTR_ERR(ps8622->gpio_rst);
		dev_err(dev, "cannot get gpio_rst %d\n", ret);
		वापस ret;
	पूर्ण

	ps8622->max_lane_count = id->driver_data;

	अगर (of_property_पढ़ो_u32(dev->of_node, "lane-count",
						&ps8622->lane_count)) अणु
		ps8622->lane_count = ps8622->max_lane_count;
	पूर्ण अन्यथा अगर (ps8622->lane_count > ps8622->max_lane_count) अणु
		dev_info(dev, "lane-count property is too high,"
						"using max_lane_count\n");
		ps8622->lane_count = ps8622->max_lane_count;
	पूर्ण

	अगर (!of_find_property(dev->of_node, "use-external-pwm", शून्य)) अणु
		ps8622->bl = backlight_device_रेजिस्टर("ps8622-backlight",
				dev, ps8622, &ps8622_backlight_ops,
				शून्य);
		अगर (IS_ERR(ps8622->bl)) अणु
			DRM_ERROR("failed to register backlight\n");
			ret = PTR_ERR(ps8622->bl);
			ps8622->bl = शून्य;
			वापस ret;
		पूर्ण
		ps8622->bl->props.max_brightness = PS8622_MAX_BRIGHTNESS;
		ps8622->bl->props.brightness = PS8622_MAX_BRIGHTNESS;
	पूर्ण

	ps8622->bridge.funcs = &ps8622_bridge_funcs;
	ps8622->bridge.type = DRM_MODE_CONNECTOR_LVDS;
	ps8622->bridge.of_node = dev->of_node;
	drm_bridge_add(&ps8622->bridge);

	i2c_set_clientdata(client, ps8622);

	वापस 0;
पूर्ण

अटल पूर्णांक ps8622_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ps8622_bridge *ps8622 = i2c_get_clientdata(client);

	backlight_device_unरेजिस्टर(ps8622->bl);
	drm_bridge_हटाओ(&ps8622->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ps8622_i2c_table[] = अणु
	/* Device type, max_lane_count */
	अणु"ps8622", 1पूर्ण,
	अणु"ps8625", 2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ps8622_i2c_table);

अटल काष्ठा i2c_driver ps8622_driver = अणु
	.id_table	= ps8622_i2c_table,
	.probe		= ps8622_probe,
	.हटाओ		= ps8622_हटाओ,
	.driver		= अणु
		.name	= "ps8622",
		.of_match_table = ps8622_devices,
	पूर्ण,
पूर्ण;
module_i2c_driver(ps8622_driver);

MODULE_AUTHOR("Vincent Palatin <vpalatin@chromium.org>");
MODULE_DESCRIPTION("Parade ps8622/ps8625 eDP-LVDS converter driver");
MODULE_LICENSE("GPL v2");
