<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Red Hat
 * Copyright (C) 2015 Sony Mobile Communications Inc.
 * Author: Werner Johansson <werner.johansson@sonymobile.com>
 *
 * Based on AUO panel driver by Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

काष्ठा sharp_nt_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *dsi;

	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;

	bool prepared;
	bool enabled;

	स्थिर काष्ठा drm_display_mode *mode;
पूर्ण;

अटल अंतरभूत काष्ठा sharp_nt_panel *to_sharp_nt_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा sharp_nt_panel, base);
पूर्ण

अटल पूर्णांक sharp_nt_panel_init(काष्ठा sharp_nt_panel *sharp_nt)
अणु
	काष्ठा mipi_dsi_device *dsi = sharp_nt->dsi;
	पूर्णांक ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0)
		वापस ret;

	msleep(120);

	/* Novatek two-lane operation */
	ret = mipi_dsi_dcs_ग_लिखो(dsi, 0xae, (u8[])अणु 0x03 पूर्ण, 1);
	अगर (ret < 0)
		वापस ret;

	/* Set both MCU and RGB I/F to 24bpp */
	ret = mipi_dsi_dcs_set_pixel_क्रमmat(dsi, MIPI_DCS_PIXEL_FMT_24BIT |
					(MIPI_DCS_PIXEL_FMT_24BIT << 4));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_nt_panel_on(काष्ठा sharp_nt_panel *sharp_nt)
अणु
	काष्ठा mipi_dsi_device *dsi = sharp_nt->dsi;
	पूर्णांक ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_nt_panel_off(काष्ठा sharp_nt_panel *sharp_nt)
अणु
	काष्ठा mipi_dsi_device *dsi = sharp_nt->dsi;
	पूर्णांक ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण


अटल पूर्णांक sharp_nt_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_nt_panel *sharp_nt = to_sharp_nt_panel(panel);

	अगर (!sharp_nt->enabled)
		वापस 0;

	sharp_nt->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_nt_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_nt_panel *sharp_nt = to_sharp_nt_panel(panel);
	पूर्णांक ret;

	अगर (!sharp_nt->prepared)
		वापस 0;

	ret = sharp_nt_panel_off(sharp_nt);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to set panel off: %d\n", ret);
		वापस ret;
	पूर्ण

	regulator_disable(sharp_nt->supply);
	अगर (sharp_nt->reset_gpio)
		gpiod_set_value(sharp_nt->reset_gpio, 0);

	sharp_nt->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_nt_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_nt_panel *sharp_nt = to_sharp_nt_panel(panel);
	पूर्णांक ret;

	अगर (sharp_nt->prepared)
		वापस 0;

	ret = regulator_enable(sharp_nt->supply);
	अगर (ret < 0)
		वापस ret;

	msleep(20);

	अगर (sharp_nt->reset_gpio) अणु
		gpiod_set_value(sharp_nt->reset_gpio, 1);
		msleep(1);
		gpiod_set_value(sharp_nt->reset_gpio, 0);
		msleep(1);
		gpiod_set_value(sharp_nt->reset_gpio, 1);
		msleep(10);
	पूर्ण

	ret = sharp_nt_panel_init(sharp_nt);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to init panel: %d\n", ret);
		जाओ घातeroff;
	पूर्ण

	ret = sharp_nt_panel_on(sharp_nt);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to set panel on: %d\n", ret);
		जाओ घातeroff;
	पूर्ण

	sharp_nt->prepared = true;

	वापस 0;

घातeroff:
	regulator_disable(sharp_nt->supply);
	अगर (sharp_nt->reset_gpio)
		gpiod_set_value(sharp_nt->reset_gpio, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक sharp_nt_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_nt_panel *sharp_nt = to_sharp_nt_panel(panel);

	अगर (sharp_nt->enabled)
		वापस 0;

	sharp_nt->enabled = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 41118,
	.hdisplay = 540,
	.hsync_start = 540 + 48,
	.hsync_end = 540 + 48 + 80,
	.htotal = 540 + 48 + 80 + 32,
	.vdisplay = 960,
	.vsync_start = 960 + 3,
	.vsync_end = 960 + 3 + 15,
	.vtotal = 960 + 3 + 15 + 1,
पूर्ण;

अटल पूर्णांक sharp_nt_panel_get_modes(काष्ठा drm_panel *panel,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 54;
	connector->display_info.height_mm = 95;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs sharp_nt_panel_funcs = अणु
	.disable = sharp_nt_panel_disable,
	.unprepare = sharp_nt_panel_unprepare,
	.prepare = sharp_nt_panel_prepare,
	.enable = sharp_nt_panel_enable,
	.get_modes = sharp_nt_panel_get_modes,
पूर्ण;

अटल पूर्णांक sharp_nt_panel_add(काष्ठा sharp_nt_panel *sharp_nt)
अणु
	काष्ठा device *dev = &sharp_nt->dsi->dev;
	पूर्णांक ret;

	sharp_nt->mode = &शेष_mode;

	sharp_nt->supply = devm_regulator_get(dev, "avdd");
	अगर (IS_ERR(sharp_nt->supply))
		वापस PTR_ERR(sharp_nt->supply);

	sharp_nt->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(sharp_nt->reset_gpio)) अणु
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(sharp_nt->reset_gpio));
		sharp_nt->reset_gpio = शून्य;
	पूर्ण अन्यथा अणु
		gpiod_set_value(sharp_nt->reset_gpio, 0);
	पूर्ण

	drm_panel_init(&sharp_nt->base, &sharp_nt->dsi->dev,
		       &sharp_nt_panel_funcs, DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&sharp_nt->base);
	अगर (ret)
		वापस ret;

	drm_panel_add(&sharp_nt->base);

	वापस 0;
पूर्ण

अटल व्योम sharp_nt_panel_del(काष्ठा sharp_nt_panel *sharp_nt)
अणु
	अगर (sharp_nt->base.dev)
		drm_panel_हटाओ(&sharp_nt->base);
पूर्ण

अटल पूर्णांक sharp_nt_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा sharp_nt_panel *sharp_nt;
	पूर्णांक ret;

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
			MIPI_DSI_MODE_VIDEO_HSE |
			MIPI_DSI_CLOCK_NON_CONTINUOUS |
			MIPI_DSI_MODE_EOT_PACKET;

	sharp_nt = devm_kzalloc(&dsi->dev, माप(*sharp_nt), GFP_KERNEL);
	अगर (!sharp_nt)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, sharp_nt);

	sharp_nt->dsi = dsi;

	ret = sharp_nt_panel_add(sharp_nt);
	अगर (ret < 0)
		वापस ret;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक sharp_nt_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा sharp_nt_panel *sharp_nt = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_disable(&sharp_nt->base);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", ret);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	sharp_nt_panel_del(sharp_nt);

	वापस 0;
पूर्ण

अटल व्योम sharp_nt_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा sharp_nt_panel *sharp_nt = mipi_dsi_get_drvdata(dsi);

	drm_panel_disable(&sharp_nt->base);
पूर्ण

अटल स्थिर काष्ठा of_device_id sharp_nt_of_match[] = अणु
	अणु .compatible = "sharp,ls043t1le01-qhd", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sharp_nt_of_match);

अटल काष्ठा mipi_dsi_driver sharp_nt_panel_driver = अणु
	.driver = अणु
		.name = "panel-sharp-ls043t1le01-qhd",
		.of_match_table = sharp_nt_of_match,
	पूर्ण,
	.probe = sharp_nt_panel_probe,
	.हटाओ = sharp_nt_panel_हटाओ,
	.shutकरोwn = sharp_nt_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(sharp_nt_panel_driver);

MODULE_AUTHOR("Werner Johansson <werner.johansson@sonymobile.com>");
MODULE_DESCRIPTION("Sharp LS043T1LE01 NT35565-based qHD (540x960) video mode panel driver");
MODULE_LICENSE("GPL v2");
