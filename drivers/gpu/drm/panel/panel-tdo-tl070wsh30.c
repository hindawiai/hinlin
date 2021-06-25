<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
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
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा tकरो_tl070wsh30_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *link;

	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;

	bool prepared;
पूर्ण;

अटल अंतरभूत
काष्ठा tकरो_tl070wsh30_panel *to_tकरो_tl070wsh30_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा tकरो_tl070wsh30_panel, base);
पूर्ण

अटल पूर्णांक tकरो_tl070wsh30_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा tकरो_tl070wsh30_panel *tकरो_tl070wsh30 = to_tकरो_tl070wsh30_panel(panel);
	पूर्णांक err;

	अगर (tकरो_tl070wsh30->prepared)
		वापस 0;

	err = regulator_enable(tकरो_tl070wsh30->supply);
	अगर (err < 0)
		वापस err;

	usleep_range(10000, 11000);

	gpiod_set_value_cansleep(tकरो_tl070wsh30->reset_gpio, 1);

	usleep_range(10000, 11000);

	gpiod_set_value_cansleep(tकरो_tl070wsh30->reset_gpio, 0);

	msleep(200);

	err = mipi_dsi_dcs_निकास_sleep_mode(tकरो_tl070wsh30->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		regulator_disable(tकरो_tl070wsh30->supply);
		वापस err;
	पूर्ण

	msleep(200);

	err = mipi_dsi_dcs_set_display_on(tकरो_tl070wsh30->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", err);
		regulator_disable(tकरो_tl070wsh30->supply);
		वापस err;
	पूर्ण

	msleep(20);

	tकरो_tl070wsh30->prepared = true;

	वापस 0;
पूर्ण

अटल पूर्णांक tकरो_tl070wsh30_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा tकरो_tl070wsh30_panel *tकरो_tl070wsh30 = to_tकरो_tl070wsh30_panel(panel);
	पूर्णांक err;

	अगर (!tकरो_tl070wsh30->prepared)
		वापस 0;

	err = mipi_dsi_dcs_set_display_off(tकरो_tl070wsh30->link);
	अगर (err < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", err);

	usleep_range(10000, 11000);

	err = mipi_dsi_dcs_enter_sleep_mode(tकरो_tl070wsh30->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", err);
		वापस err;
	पूर्ण

	usleep_range(10000, 11000);

	regulator_disable(tकरो_tl070wsh30->supply);

	tकरो_tl070wsh30->prepared = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 47250,
	.hdisplay = 1024,
	.hsync_start = 1024 + 46,
	.hsync_end = 1024 + 46 + 80,
	.htotal = 1024 + 46 + 80 + 100,
	.vdisplay = 600,
	.vsync_start = 600 + 5,
	.vsync_end = 600 + 5 + 5,
	.vtotal = 600 + 5 + 5 + 20,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल पूर्णांक tकरो_tl070wsh30_panel_get_modes(काष्ठा drm_panel *panel,
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

	connector->display_info.width_mm = 154;
	connector->display_info.height_mm = 85;
	connector->display_info.bpc = 8;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs tकरो_tl070wsh30_panel_funcs = अणु
	.unprepare = tकरो_tl070wsh30_panel_unprepare,
	.prepare = tकरो_tl070wsh30_panel_prepare,
	.get_modes = tकरो_tl070wsh30_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tकरो_tl070wsh30_of_match[] = अणु
	अणु .compatible = "tdo,tl070wsh30", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tकरो_tl070wsh30_of_match);

अटल पूर्णांक tकरो_tl070wsh30_panel_add(काष्ठा tकरो_tl070wsh30_panel *tकरो_tl070wsh30)
अणु
	काष्ठा device *dev = &tकरो_tl070wsh30->link->dev;
	पूर्णांक err;

	tकरो_tl070wsh30->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(tकरो_tl070wsh30->supply))
		वापस PTR_ERR(tकरो_tl070wsh30->supply);

	tकरो_tl070wsh30->reset_gpio = devm_gpiod_get(dev, "reset",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(tकरो_tl070wsh30->reset_gpio)) अणु
		err = PTR_ERR(tकरो_tl070wsh30->reset_gpio);
		dev_dbg(dev, "failed to get reset gpio: %d\n", err);
		वापस err;
	पूर्ण

	drm_panel_init(&tकरो_tl070wsh30->base, &tकरो_tl070wsh30->link->dev,
		       &tकरो_tl070wsh30_panel_funcs, DRM_MODE_CONNECTOR_DSI);

	err = drm_panel_of_backlight(&tकरो_tl070wsh30->base);
	अगर (err)
		वापस err;

	drm_panel_add(&tकरो_tl070wsh30->base);

	वापस 0;
पूर्ण

अटल पूर्णांक tकरो_tl070wsh30_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा tकरो_tl070wsh30_panel *tकरो_tl070wsh30;
	पूर्णांक err;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_MODE_LPM;

	tकरो_tl070wsh30 = devm_kzalloc(&dsi->dev, माप(*tकरो_tl070wsh30),
				    GFP_KERNEL);
	अगर (!tकरो_tl070wsh30)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, tकरो_tl070wsh30);
	tकरो_tl070wsh30->link = dsi;

	err = tकरो_tl070wsh30_panel_add(tकरो_tl070wsh30);
	अगर (err < 0)
		वापस err;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक tकरो_tl070wsh30_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा tकरो_tl070wsh30_panel *tकरो_tl070wsh30 = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	drm_panel_हटाओ(&tकरो_tl070wsh30->base);
	drm_panel_disable(&tकरो_tl070wsh30->base);
	drm_panel_unprepare(&tकरो_tl070wsh30->base);

	वापस 0;
पूर्ण

अटल व्योम tकरो_tl070wsh30_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा tकरो_tl070wsh30_panel *tकरो_tl070wsh30 = mipi_dsi_get_drvdata(dsi);

	drm_panel_disable(&tकरो_tl070wsh30->base);
	drm_panel_unprepare(&tकरो_tl070wsh30->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver tकरो_tl070wsh30_panel_driver = अणु
	.driver = अणु
		.name = "panel-tdo-tl070wsh30",
		.of_match_table = tकरो_tl070wsh30_of_match,
	पूर्ण,
	.probe = tकरो_tl070wsh30_panel_probe,
	.हटाओ = tकरो_tl070wsh30_panel_हटाओ,
	.shutकरोwn = tकरो_tl070wsh30_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(tकरो_tl070wsh30_panel_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("TDO TL070WSH30 panel driver");
MODULE_LICENSE("GPL v2");
