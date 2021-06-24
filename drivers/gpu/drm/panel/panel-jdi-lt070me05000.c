<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Inक्रमceComputing
 * Author: Vinay Simha BN <simhavcs@gmail.com>
 *
 * Copyright (C) 2016 Linaro Ltd
 * Author: Sumit Semwal <sumit.semwal@linaro.org>
 *
 * From पूर्णांकernet archives, the panel क्रम Nexus 7 2nd Gen, 2013 model is a
 * JDI model LT070ME05000, and its data sheet is at:
 * http://panelone.net/en/7-0-inch/JDI_LT070ME05000_7.0_inch-datasheet
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

अटल स्थिर अक्षर * स्थिर regulator_names[] = अणु
	"vddp",
	"iovcc"
पूर्ण;

काष्ठा jdi_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *dsi;

	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(regulator_names)];

	काष्ठा gpio_desc *enable_gpio;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *dcdc_en_gpio;
	काष्ठा backlight_device *backlight;

	bool prepared;
	bool enabled;

	स्थिर काष्ठा drm_display_mode *mode;
पूर्ण;

अटल अंतरभूत काष्ठा jdi_panel *to_jdi_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा jdi_panel, base);
पूर्ण

अटल पूर्णांक jdi_panel_init(काष्ठा jdi_panel *jdi)
अणु
	काष्ठा mipi_dsi_device *dsi = jdi->dsi;
	काष्ठा device *dev = &jdi->dsi->dev;
	पूर्णांक ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_soft_reset(dsi);
	अगर (ret < 0)
		वापस ret;

	usleep_range(10000, 20000);

	ret = mipi_dsi_dcs_set_pixel_क्रमmat(dsi, MIPI_DCS_PIXEL_FMT_24BIT << 4);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set pixel format: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mipi_dsi_dcs_set_column_address(dsi, 0, jdi->mode->hdisplay - 1);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set column address: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mipi_dsi_dcs_set_page_address(dsi, 0, jdi->mode->vdisplay - 1);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set page address: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * BIT(5) BCTRL = 1 Backlight Control Block On, Brightness रेजिस्टरs
	 *                  are active
	 * BIT(3) BL = 1    Backlight Control On
	 * BIT(2) DD = 0    Display Dimming is Off
	 */
	ret = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				 (u8[])अणु 0x24 पूर्ण, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to write control display: %d\n", ret);
		वापस ret;
	पूर्ण

	/* CABC off */
	ret = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_WRITE_POWER_SAVE,
				 (u8[])अणु 0x00 पूर्ण, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set cabc off: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set exit sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(120);

	ret = mipi_dsi_generic_ग_लिखो(dsi, (u8[])अणु0xB0, 0x00पूर्ण, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set mcap: %d\n", ret);
		वापस ret;
	पूर्ण

	mdelay(10);

	/* Interface setting, video mode */
	ret = mipi_dsi_generic_ग_लिखो(dsi, (u8[])
				     अणु0xB3, 0x26, 0x08, 0x00, 0x20, 0x00पूर्ण, 6);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set display interface setting: %d\n"
			, ret);
		वापस ret;
	पूर्ण

	mdelay(20);

	ret = mipi_dsi_generic_ग_लिखो(dsi, (u8[])अणु0xB0, 0x03पूर्ण, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set default values for mcap: %d\n"
			, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jdi_panel_on(काष्ठा jdi_panel *jdi)
अणु
	काष्ठा mipi_dsi_device *dsi = jdi->dsi;
	काष्ठा device *dev = &jdi->dsi->dev;
	पूर्णांक ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0)
		dev_err(dev, "failed to set display on: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम jdi_panel_off(काष्ठा jdi_panel *jdi)
अणु
	काष्ठा mipi_dsi_device *dsi = jdi->dsi;
	काष्ठा device *dev = &jdi->dsi->dev;
	पूर्णांक ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		dev_err(dev, "failed to set display off: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0)
		dev_err(dev, "failed to enter sleep mode: %d\n", ret);

	msleep(100);
पूर्ण

अटल पूर्णांक jdi_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा jdi_panel *jdi = to_jdi_panel(panel);

	अगर (!jdi->enabled)
		वापस 0;

	backlight_disable(jdi->backlight);

	jdi->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक jdi_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा jdi_panel *jdi = to_jdi_panel(panel);
	काष्ठा device *dev = &jdi->dsi->dev;
	पूर्णांक ret;

	अगर (!jdi->prepared)
		वापस 0;

	jdi_panel_off(jdi);

	ret = regulator_bulk_disable(ARRAY_SIZE(jdi->supplies), jdi->supplies);
	अगर (ret < 0)
		dev_err(dev, "regulator disable failed, %d\n", ret);

	gpiod_set_value(jdi->enable_gpio, 0);

	gpiod_set_value(jdi->reset_gpio, 1);

	gpiod_set_value(jdi->dcdc_en_gpio, 0);

	jdi->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक jdi_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा jdi_panel *jdi = to_jdi_panel(panel);
	काष्ठा device *dev = &jdi->dsi->dev;
	पूर्णांक ret;

	अगर (jdi->prepared)
		वापस 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(jdi->supplies), jdi->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "regulator enable failed, %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(20);

	gpiod_set_value(jdi->dcdc_en_gpio, 1);
	usleep_range(10, 20);

	gpiod_set_value(jdi->reset_gpio, 0);
	usleep_range(10, 20);

	gpiod_set_value(jdi->enable_gpio, 1);
	usleep_range(10, 20);

	ret = jdi_panel_init(jdi);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to init panel: %d\n", ret);
		जाओ घातeroff;
	पूर्ण

	ret = jdi_panel_on(jdi);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set panel on: %d\n", ret);
		जाओ घातeroff;
	पूर्ण

	jdi->prepared = true;

	वापस 0;

घातeroff:
	ret = regulator_bulk_disable(ARRAY_SIZE(jdi->supplies), jdi->supplies);
	अगर (ret < 0)
		dev_err(dev, "regulator disable failed, %d\n", ret);

	gpiod_set_value(jdi->enable_gpio, 0);

	gpiod_set_value(jdi->reset_gpio, 1);

	gpiod_set_value(jdi->dcdc_en_gpio, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक jdi_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा jdi_panel *jdi = to_jdi_panel(panel);

	अगर (jdi->enabled)
		वापस 0;

	backlight_enable(jdi->backlight);

	jdi->enabled = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
		.घड़ी = 155493,
		.hdisplay = 1200,
		.hsync_start = 1200 + 48,
		.hsync_end = 1200 + 48 + 32,
		.htotal = 1200 + 48 + 32 + 60,
		.vdisplay = 1920,
		.vsync_start = 1920 + 3,
		.vsync_end = 1920 + 3 + 5,
		.vtotal = 1920 + 3 + 5 + 6,
		.flags = 0,
पूर्ण;

अटल पूर्णांक jdi_panel_get_modes(काष्ठा drm_panel *panel,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;
	काष्ठा jdi_panel *jdi = to_jdi_panel(panel);
	काष्ठा device *dev = &jdi->dsi->dev;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(dev, "failed to add mode %ux%ux@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 95;
	connector->display_info.height_mm = 151;

	वापस 1;
पूर्ण

अटल पूर्णांक dsi_dcs_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा mipi_dsi_device *dsi = bl_get_data(bl);
	पूर्णांक ret;
	u16 brightness = bl->props.brightness;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness(dsi, &brightness);
	अगर (ret < 0)
		वापस ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	वापस brightness & 0xff;
पूर्ण

अटल पूर्णांक dsi_dcs_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा mipi_dsi_device *dsi = bl_get_data(bl);
	पूर्णांक ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, bl->props.brightness);
	अगर (ret < 0)
		वापस ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops dsi_bl_ops = अणु
	.update_status = dsi_dcs_bl_update_status,
	.get_brightness = dsi_dcs_bl_get_brightness,
पूर्ण;

अटल काष्ठा backlight_device *
drm_panel_create_dsi_backlight(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा backlight_properties props;

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.brightness = 255;
	props.max_brightness = 255;

	वापस devm_backlight_device_रेजिस्टर(dev, dev_name(dev), dev, dsi,
					      &dsi_bl_ops, &props);
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs jdi_panel_funcs = अणु
	.disable = jdi_panel_disable,
	.unprepare = jdi_panel_unprepare,
	.prepare = jdi_panel_prepare,
	.enable = jdi_panel_enable,
	.get_modes = jdi_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jdi_of_match[] = अणु
	अणु .compatible = "jdi,lt070me05000", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jdi_of_match);

अटल पूर्णांक jdi_panel_add(काष्ठा jdi_panel *jdi)
अणु
	काष्ठा device *dev = &jdi->dsi->dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	jdi->mode = &शेष_mode;

	क्रम (i = 0; i < ARRAY_SIZE(jdi->supplies); i++)
		jdi->supplies[i].supply = regulator_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(jdi->supplies),
				      jdi->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to init regulator, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	jdi->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(jdi->enable_gpio)) अणु
		ret = PTR_ERR(jdi->enable_gpio);
		dev_err(dev, "cannot get enable-gpio %d\n", ret);
		वापस ret;
	पूर्ण

	jdi->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(jdi->reset_gpio)) अणु
		ret = PTR_ERR(jdi->reset_gpio);
		dev_err(dev, "cannot get reset-gpios %d\n", ret);
		वापस ret;
	पूर्ण

	jdi->dcdc_en_gpio = devm_gpiod_get(dev, "dcdc-en", GPIOD_OUT_LOW);
	अगर (IS_ERR(jdi->dcdc_en_gpio)) अणु
		ret = PTR_ERR(jdi->dcdc_en_gpio);
		dev_err(dev, "cannot get dcdc-en-gpio %d\n", ret);
		वापस ret;
	पूर्ण

	jdi->backlight = drm_panel_create_dsi_backlight(jdi->dsi);
	अगर (IS_ERR(jdi->backlight)) अणु
		ret = PTR_ERR(jdi->backlight);
		dev_err(dev, "failed to register backlight %d\n", ret);
		वापस ret;
	पूर्ण

	drm_panel_init(&jdi->base, &jdi->dsi->dev, &jdi_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	drm_panel_add(&jdi->base);

	वापस 0;
पूर्ण

अटल व्योम jdi_panel_del(काष्ठा jdi_panel *jdi)
अणु
	अगर (jdi->base.dev)
		drm_panel_हटाओ(&jdi->base);
पूर्ण

अटल पूर्णांक jdi_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा jdi_panel *jdi;
	पूर्णांक ret;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags =  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_VIDEO |
			   MIPI_DSI_CLOCK_NON_CONTINUOUS;

	jdi = devm_kzalloc(&dsi->dev, माप(*jdi), GFP_KERNEL);
	अगर (!jdi)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, jdi);

	jdi->dsi = dsi;

	ret = jdi_panel_add(jdi);
	अगर (ret < 0)
		वापस ret;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक jdi_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा jdi_panel *jdi = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = jdi_panel_disable(&jdi->base);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", ret);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n",
			ret);

	jdi_panel_del(jdi);

	वापस 0;
पूर्ण

अटल व्योम jdi_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा jdi_panel *jdi = mipi_dsi_get_drvdata(dsi);

	jdi_panel_disable(&jdi->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver jdi_panel_driver = अणु
	.driver = अणु
		.name = "panel-jdi-lt070me05000",
		.of_match_table = jdi_of_match,
	पूर्ण,
	.probe = jdi_panel_probe,
	.हटाओ = jdi_panel_हटाओ,
	.shutकरोwn = jdi_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(jdi_panel_driver);

MODULE_AUTHOR("Sumit Semwal <sumit.semwal@linaro.org>");
MODULE_AUTHOR("Vinay Simha BN <simhavcs@gmail.com>");
MODULE_DESCRIPTION("JDI LT070ME05000 WUXGA");
MODULE_LICENSE("GPL v2");
