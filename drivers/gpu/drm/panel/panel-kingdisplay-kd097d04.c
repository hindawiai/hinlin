<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd
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

काष्ठा kingdisplay_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *link;

	काष्ठा regulator *supply;
	काष्ठा gpio_desc *enable_gpio;

	bool prepared;
	bool enabled;
पूर्ण;

काष्ठा kingdisplay_panel_cmd अणु
	अक्षर cmd;
	अक्षर data;
पूर्ण;

/*
 * According to the discussion on
 * https://review.coreboot.org/#/c/coreboot/+/22472/
 * the panel init array is not part of the panels datasheet but instead
 * just came in this क्रमm from the panel venकरोr.
 */
अटल स्थिर काष्ठा kingdisplay_panel_cmd init_code[] = अणु
	/* voltage setting */
	अणु 0xB0, 0x00 पूर्ण,
	अणु 0xB2, 0x02 पूर्ण,
	अणु 0xB3, 0x11 पूर्ण,
	अणु 0xB4, 0x00 पूर्ण,
	अणु 0xB6, 0x80 पूर्ण,
	/* VCOM disable */
	अणु 0xB7, 0x02 पूर्ण,
	अणु 0xB8, 0x80 पूर्ण,
	अणु 0xBA, 0x43 पूर्ण,
	/* VCOM setting */
	अणु 0xBB, 0x53 पूर्ण,
	/* VSP setting */
	अणु 0xBC, 0x0A पूर्ण,
	/* VSN setting */
	अणु 0xBD, 0x4A पूर्ण,
	/* VGH setting */
	अणु 0xBE, 0x2F पूर्ण,
	/* VGL setting */
	अणु 0xBF, 0x1A पूर्ण,
	अणु 0xF0, 0x39 पूर्ण,
	अणु 0xF1, 0x22 पूर्ण,
	/* Gamma setting */
	अणु 0xB0, 0x02 पूर्ण,
	अणु 0xC0, 0x00 पूर्ण,
	अणु 0xC1, 0x01 पूर्ण,
	अणु 0xC2, 0x0B पूर्ण,
	अणु 0xC3, 0x15 पूर्ण,
	अणु 0xC4, 0x22 पूर्ण,
	अणु 0xC5, 0x11 पूर्ण,
	अणु 0xC6, 0x15 पूर्ण,
	अणु 0xC7, 0x19 पूर्ण,
	अणु 0xC8, 0x1A पूर्ण,
	अणु 0xC9, 0x16 पूर्ण,
	अणु 0xCA, 0x18 पूर्ण,
	अणु 0xCB, 0x13 पूर्ण,
	अणु 0xCC, 0x18 पूर्ण,
	अणु 0xCD, 0x13 पूर्ण,
	अणु 0xCE, 0x1C पूर्ण,
	अणु 0xCF, 0x19 पूर्ण,
	अणु 0xD0, 0x21 पूर्ण,
	अणु 0xD1, 0x2C पूर्ण,
	अणु 0xD2, 0x2F पूर्ण,
	अणु 0xD3, 0x30 पूर्ण,
	अणु 0xD4, 0x19 पूर्ण,
	अणु 0xD5, 0x1F पूर्ण,
	अणु 0xD6, 0x00 पूर्ण,
	अणु 0xD7, 0x01 पूर्ण,
	अणु 0xD8, 0x0B पूर्ण,
	अणु 0xD9, 0x15 पूर्ण,
	अणु 0xDA, 0x22 पूर्ण,
	अणु 0xDB, 0x11 पूर्ण,
	अणु 0xDC, 0x15 पूर्ण,
	अणु 0xDD, 0x19 पूर्ण,
	अणु 0xDE, 0x1A पूर्ण,
	अणु 0xDF, 0x16 पूर्ण,
	अणु 0xE0, 0x18 पूर्ण,
	अणु 0xE1, 0x13 पूर्ण,
	अणु 0xE2, 0x18 पूर्ण,
	अणु 0xE3, 0x13 पूर्ण,
	अणु 0xE4, 0x1C पूर्ण,
	अणु 0xE5, 0x19 पूर्ण,
	अणु 0xE6, 0x21 पूर्ण,
	अणु 0xE7, 0x2C पूर्ण,
	अणु 0xE8, 0x2F पूर्ण,
	अणु 0xE9, 0x30 पूर्ण,
	अणु 0xEA, 0x19 पूर्ण,
	अणु 0xEB, 0x1F पूर्ण,
	/* GOA MUX setting */
	अणु 0xB0, 0x01 पूर्ण,
	अणु 0xC0, 0x10 पूर्ण,
	अणु 0xC1, 0x0F पूर्ण,
	अणु 0xC2, 0x0E पूर्ण,
	अणु 0xC3, 0x0D पूर्ण,
	अणु 0xC4, 0x0C पूर्ण,
	अणु 0xC5, 0x0B पूर्ण,
	अणु 0xC6, 0x0A पूर्ण,
	अणु 0xC7, 0x09 पूर्ण,
	अणु 0xC8, 0x08 पूर्ण,
	अणु 0xC9, 0x07 पूर्ण,
	अणु 0xCA, 0x06 पूर्ण,
	अणु 0xCB, 0x05 पूर्ण,
	अणु 0xCC, 0x00 पूर्ण,
	अणु 0xCD, 0x01 पूर्ण,
	अणु 0xCE, 0x02 पूर्ण,
	अणु 0xCF, 0x03 पूर्ण,
	अणु 0xD0, 0x04 पूर्ण,
	अणु 0xD6, 0x10 पूर्ण,
	अणु 0xD7, 0x0F पूर्ण,
	अणु 0xD8, 0x0E पूर्ण,
	अणु 0xD9, 0x0D पूर्ण,
	अणु 0xDA, 0x0C पूर्ण,
	अणु 0xDB, 0x0B पूर्ण,
	अणु 0xDC, 0x0A पूर्ण,
	अणु 0xDD, 0x09 पूर्ण,
	अणु 0xDE, 0x08 पूर्ण,
	अणु 0xDF, 0x07 पूर्ण,
	अणु 0xE0, 0x06 पूर्ण,
	अणु 0xE1, 0x05 पूर्ण,
	अणु 0xE2, 0x00 पूर्ण,
	अणु 0xE3, 0x01 पूर्ण,
	अणु 0xE4, 0x02 पूर्ण,
	अणु 0xE5, 0x03 पूर्ण,
	अणु 0xE6, 0x04 पूर्ण,
	अणु 0xE7, 0x00 पूर्ण,
	अणु 0xEC, 0xC0 पूर्ण,
	/* GOA timing setting */
	अणु 0xB0, 0x03 पूर्ण,
	अणु 0xC0, 0x01 पूर्ण,
	अणु 0xC2, 0x6F पूर्ण,
	अणु 0xC3, 0x6F पूर्ण,
	अणु 0xC5, 0x36 पूर्ण,
	अणु 0xC8, 0x08 पूर्ण,
	अणु 0xC9, 0x04 पूर्ण,
	अणु 0xCA, 0x41 पूर्ण,
	अणु 0xCC, 0x43 पूर्ण,
	अणु 0xCF, 0x60 पूर्ण,
	अणु 0xD2, 0x04 पूर्ण,
	अणु 0xD3, 0x04 पूर्ण,
	अणु 0xD4, 0x03 पूर्ण,
	अणु 0xD5, 0x02 पूर्ण,
	अणु 0xD6, 0x01 पूर्ण,
	अणु 0xD7, 0x00 पूर्ण,
	अणु 0xDB, 0x01 पूर्ण,
	अणु 0xDE, 0x36 पूर्ण,
	अणु 0xE6, 0x6F पूर्ण,
	अणु 0xE7, 0x6F पूर्ण,
	/* GOE setting */
	अणु 0xB0, 0x06 पूर्ण,
	अणु 0xB8, 0xA5 पूर्ण,
	अणु 0xC0, 0xA5 पूर्ण,
	अणु 0xD5, 0x3F पूर्ण,
पूर्ण;

अटल अंतरभूत
काष्ठा kingdisplay_panel *to_kingdisplay_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा kingdisplay_panel, base);
पूर्ण

अटल पूर्णांक kingdisplay_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);
	पूर्णांक err;

	अगर (!kingdisplay->enabled)
		वापस 0;

	err = mipi_dsi_dcs_set_display_off(kingdisplay->link);
	अगर (err < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", err);

	kingdisplay->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक kingdisplay_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);
	पूर्णांक err;

	अगर (!kingdisplay->prepared)
		वापस 0;

	err = mipi_dsi_dcs_enter_sleep_mode(kingdisplay->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", err);
		वापस err;
	पूर्ण

	/* T15: 120ms */
	msleep(120);

	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 0);

	err = regulator_disable(kingdisplay->supply);
	अगर (err < 0)
		वापस err;

	kingdisplay->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक kingdisplay_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);
	पूर्णांक err, regulator_err;
	अचिन्हित पूर्णांक i;

	अगर (kingdisplay->prepared)
		वापस 0;

	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 0);

	err = regulator_enable(kingdisplay->supply);
	अगर (err < 0)
		वापस err;

	/* T2: 15ms */
	usleep_range(15000, 16000);

	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 1);

	/* T4: 15ms */
	usleep_range(15000, 16000);

	क्रम (i = 0; i < ARRAY_SIZE(init_code); i++) अणु
		err = mipi_dsi_generic_ग_लिखो(kingdisplay->link, &init_code[i],
					माप(काष्ठा kingdisplay_panel_cmd));
		अगर (err < 0) अणु
			dev_err(panel->dev, "failed write init cmds: %d\n", err);
			जाओ घातeroff;
		पूर्ण
	पूर्ण

	err = mipi_dsi_dcs_निकास_sleep_mode(kingdisplay->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* T6: 120ms */
	msleep(120);

	err = mipi_dsi_dcs_set_display_on(kingdisplay->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* T7: 10ms */
	usleep_range(10000, 11000);

	kingdisplay->prepared = true;

	वापस 0;

घातeroff:
	gpiod_set_value_cansleep(kingdisplay->enable_gpio, 0);

	regulator_err = regulator_disable(kingdisplay->supply);
	अगर (regulator_err)
		dev_err(panel->dev, "failed to disable regulator: %d\n", regulator_err);

	वापस err;
पूर्ण

अटल पूर्णांक kingdisplay_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);

	अगर (kingdisplay->enabled)
		वापस 0;

	kingdisplay->enabled = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 229000,
	.hdisplay = 1536,
	.hsync_start = 1536 + 100,
	.hsync_end = 1536 + 100 + 24,
	.htotal = 1536 + 100 + 24 + 100,
	.vdisplay = 2048,
	.vsync_start = 2048 + 95,
	.vsync_end = 2048 + 95 + 2,
	.vtotal = 2048 + 95 + 2 + 23,
पूर्ण;

अटल पूर्णांक kingdisplay_panel_get_modes(काष्ठा drm_panel *panel,
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

	connector->display_info.width_mm = 147;
	connector->display_info.height_mm = 196;
	connector->display_info.bpc = 8;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs kingdisplay_panel_funcs = अणु
	.disable = kingdisplay_panel_disable,
	.unprepare = kingdisplay_panel_unprepare,
	.prepare = kingdisplay_panel_prepare,
	.enable = kingdisplay_panel_enable,
	.get_modes = kingdisplay_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id kingdisplay_of_match[] = अणु
	अणु .compatible = "kingdisplay,kd097d04", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, kingdisplay_of_match);

अटल पूर्णांक kingdisplay_panel_add(काष्ठा kingdisplay_panel *kingdisplay)
अणु
	काष्ठा device *dev = &kingdisplay->link->dev;
	पूर्णांक err;

	kingdisplay->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(kingdisplay->supply))
		वापस PTR_ERR(kingdisplay->supply);

	kingdisplay->enable_gpio = devm_gpiod_get_optional(dev, "enable",
							   GPIOD_OUT_HIGH);
	अगर (IS_ERR(kingdisplay->enable_gpio)) अणु
		err = PTR_ERR(kingdisplay->enable_gpio);
		dev_dbg(dev, "failed to get enable gpio: %d\n", err);
		kingdisplay->enable_gpio = शून्य;
	पूर्ण

	drm_panel_init(&kingdisplay->base, &kingdisplay->link->dev,
		       &kingdisplay_panel_funcs, DRM_MODE_CONNECTOR_DSI);

	err = drm_panel_of_backlight(&kingdisplay->base);
	अगर (err)
		वापस err;

	drm_panel_add(&kingdisplay->base);

	वापस 0;
पूर्ण

अटल व्योम kingdisplay_panel_del(काष्ठा kingdisplay_panel *kingdisplay)
अणु
	drm_panel_हटाओ(&kingdisplay->base);
पूर्ण

अटल पूर्णांक kingdisplay_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा kingdisplay_panel *kingdisplay;
	पूर्णांक err;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM;

	kingdisplay = devm_kzalloc(&dsi->dev, माप(*kingdisplay), GFP_KERNEL);
	अगर (!kingdisplay)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, kingdisplay);
	kingdisplay->link = dsi;

	err = kingdisplay_panel_add(kingdisplay);
	अगर (err < 0)
		वापस err;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक kingdisplay_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा kingdisplay_panel *kingdisplay = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;

	err = drm_panel_unprepare(&kingdisplay->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to unprepare panel: %d\n", err);

	err = drm_panel_disable(&kingdisplay->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", err);

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	kingdisplay_panel_del(kingdisplay);

	वापस 0;
पूर्ण

अटल व्योम kingdisplay_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा kingdisplay_panel *kingdisplay = mipi_dsi_get_drvdata(dsi);

	drm_panel_unprepare(&kingdisplay->base);
	drm_panel_disable(&kingdisplay->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver kingdisplay_panel_driver = अणु
	.driver = अणु
		.name = "panel-kingdisplay-kd097d04",
		.of_match_table = kingdisplay_of_match,
	पूर्ण,
	.probe = kingdisplay_panel_probe,
	.हटाओ = kingdisplay_panel_हटाओ,
	.shutकरोwn = kingdisplay_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(kingdisplay_panel_driver);

MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_AUTHOR("Nickey Yang <nickey.yang@rock-chips.com>");
MODULE_DESCRIPTION("kingdisplay KD097D04 panel driver");
MODULE_LICENSE("GPL v2");
