<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 NVIDIA Corporation
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

काष्ठा sharp_panel अणु
	काष्ठा drm_panel base;
	/* the datasheet refers to them as DSI-LINK1 and DSI-LINK2 */
	काष्ठा mipi_dsi_device *link1;
	काष्ठा mipi_dsi_device *link2;

	काष्ठा regulator *supply;

	bool prepared;
	bool enabled;

	स्थिर काष्ठा drm_display_mode *mode;
पूर्ण;

अटल अंतरभूत काष्ठा sharp_panel *to_sharp_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा sharp_panel, base);
पूर्ण

अटल व्योम sharp_रुको_frames(काष्ठा sharp_panel *sharp, अचिन्हित पूर्णांक frames)
अणु
	अचिन्हित पूर्णांक refresh = drm_mode_vrefresh(sharp->mode);

	अगर (WARN_ON(frames > refresh))
		वापस;

	msleep(1000 / (refresh / frames));
पूर्ण

अटल पूर्णांक sharp_panel_ग_लिखो(काष्ठा sharp_panel *sharp, u16 offset, u8 value)
अणु
	u8 payload[3] = अणु offset >> 8, offset & 0xff, value पूर्ण;
	काष्ठा mipi_dsi_device *dsi = sharp->link1;
	sमाप_प्रकार err;

	err = mipi_dsi_generic_ग_लिखो(dsi, payload, माप(payload));
	अगर (err < 0) अणु
		dev_err(&dsi->dev, "failed to write %02x to %04x: %zd\n",
			value, offset, err);
		वापस err;
	पूर्ण

	err = mipi_dsi_dcs_nop(dsi);
	अगर (err < 0) अणु
		dev_err(&dsi->dev, "failed to send DCS nop: %zd\n", err);
		वापस err;
	पूर्ण

	usleep_range(10, 20);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक sharp_panel_पढ़ो(काष्ठा sharp_panel *sharp,
					   u16 offset, u8 *value)
अणु
	sमाप_प्रकार err;

	cpu_to_be16s(&offset);

	err = mipi_dsi_generic_पढ़ो(sharp->link1, &offset, माप(offset),
				    value, माप(*value));
	अगर (err < 0)
		dev_err(&sharp->link1->dev, "failed to read from %04x: %zd\n",
			offset, err);

	वापस err;
पूर्ण

अटल पूर्णांक sharp_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_panel *sharp = to_sharp_panel(panel);

	अगर (!sharp->enabled)
		वापस 0;

	sharp->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_panel *sharp = to_sharp_panel(panel);
	पूर्णांक err;

	अगर (!sharp->prepared)
		वापस 0;

	sharp_रुको_frames(sharp, 4);

	err = mipi_dsi_dcs_set_display_off(sharp->link1);
	अगर (err < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", err);

	err = mipi_dsi_dcs_enter_sleep_mode(sharp->link1);
	अगर (err < 0)
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", err);

	msleep(120);

	regulator_disable(sharp->supply);

	sharp->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_setup_symmetrical_split(काष्ठा mipi_dsi_device *left,
					 काष्ठा mipi_dsi_device *right,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक err;

	err = mipi_dsi_dcs_set_column_address(left, 0, mode->hdisplay / 2 - 1);
	अगर (err < 0) अणु
		dev_err(&left->dev, "failed to set column address: %d\n", err);
		वापस err;
	पूर्ण

	err = mipi_dsi_dcs_set_page_address(left, 0, mode->vdisplay - 1);
	अगर (err < 0) अणु
		dev_err(&left->dev, "failed to set page address: %d\n", err);
		वापस err;
	पूर्ण

	err = mipi_dsi_dcs_set_column_address(right, mode->hdisplay / 2,
					      mode->hdisplay - 1);
	अगर (err < 0) अणु
		dev_err(&right->dev, "failed to set column address: %d\n", err);
		वापस err;
	पूर्ण

	err = mipi_dsi_dcs_set_page_address(right, 0, mode->vdisplay - 1);
	अगर (err < 0) अणु
		dev_err(&right->dev, "failed to set page address: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_panel *sharp = to_sharp_panel(panel);
	u8 क्रमmat = MIPI_DCS_PIXEL_FMT_24BIT;
	पूर्णांक err;

	अगर (sharp->prepared)
		वापस 0;

	err = regulator_enable(sharp->supply);
	अगर (err < 0)
		वापस err;

	/*
	 * According to the datasheet, the panel needs around 10 ms to fully
	 * घातer up. At least another 120 ms is required beक्रमe निकासing sleep
	 * mode to make sure the panel is पढ़ोy. Throw in another 20 ms क्रम
	 * good measure.
	 */
	msleep(150);

	err = mipi_dsi_dcs_निकास_sleep_mode(sharp->link1);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/*
	 * The MIPI DCS specअगरication mandates this delay only between the
	 * निकास_sleep_mode and enter_sleep_mode commands, so it isn't strictly
	 * necessary here.
	 */
	/*
	msleep(120);
	*/

	/* set left-right mode */
	err = sharp_panel_ग_लिखो(sharp, 0x1000, 0x2a);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set left-right mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* enable command mode */
	err = sharp_panel_ग_लिखो(sharp, 0x1001, 0x01);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to enable command mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	err = mipi_dsi_dcs_set_pixel_क्रमmat(sharp->link1, क्रमmat);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set pixel format: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/*
	 * TODO: The device supports both left-right and even-odd split
	 * configurations, but this driver currently supports only the left-
	 * right split. To support a dअगरferent mode a mechanism needs to be
	 * put in place to communicate the configuration back to the DSI host
	 * controller.
	 */
	err = sharp_setup_symmetrical_split(sharp->link1, sharp->link2,
					    sharp->mode);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set up symmetrical split: %d\n",
			err);
		जाओ घातeroff;
	पूर्ण

	err = mipi_dsi_dcs_set_display_on(sharp->link1);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	sharp->prepared = true;

	/* रुको क्रम 6 frames beक्रमe continuing */
	sharp_रुको_frames(sharp, 6);

	वापस 0;

घातeroff:
	regulator_disable(sharp->supply);
	वापस err;
पूर्ण

अटल पूर्णांक sharp_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा sharp_panel *sharp = to_sharp_panel(panel);

	अगर (sharp->enabled)
		वापस 0;

	sharp->enabled = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 278000,
	.hdisplay = 2560,
	.hsync_start = 2560 + 128,
	.hsync_end = 2560 + 128 + 64,
	.htotal = 2560 + 128 + 64 + 64,
	.vdisplay = 1600,
	.vsync_start = 1600 + 4,
	.vsync_end = 1600 + 4 + 8,
	.vtotal = 1600 + 4 + 8 + 32,
पूर्ण;

अटल पूर्णांक sharp_panel_get_modes(काष्ठा drm_panel *panel,
				 काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%ux@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 217;
	connector->display_info.height_mm = 136;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs sharp_panel_funcs = अणु
	.disable = sharp_panel_disable,
	.unprepare = sharp_panel_unprepare,
	.prepare = sharp_panel_prepare,
	.enable = sharp_panel_enable,
	.get_modes = sharp_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sharp_of_match[] = अणु
	अणु .compatible = "sharp,lq101r1sx01", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sharp_of_match);

अटल पूर्णांक sharp_panel_add(काष्ठा sharp_panel *sharp)
अणु
	पूर्णांक ret;

	sharp->mode = &शेष_mode;

	sharp->supply = devm_regulator_get(&sharp->link1->dev, "power");
	अगर (IS_ERR(sharp->supply))
		वापस PTR_ERR(sharp->supply);

	drm_panel_init(&sharp->base, &sharp->link1->dev, &sharp_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&sharp->base);
	अगर (ret)
		वापस ret;

	drm_panel_add(&sharp->base);

	वापस 0;
पूर्ण

अटल व्योम sharp_panel_del(काष्ठा sharp_panel *sharp)
अणु
	अगर (sharp->base.dev)
		drm_panel_हटाओ(&sharp->base);

	अगर (sharp->link2)
		put_device(&sharp->link2->dev);
पूर्ण

अटल पूर्णांक sharp_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा mipi_dsi_device *secondary = शून्य;
	काष्ठा sharp_panel *sharp;
	काष्ठा device_node *np;
	पूर्णांक err;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_LPM;

	/* Find DSI-LINK1 */
	np = of_parse_phandle(dsi->dev.of_node, "link2", 0);
	अगर (np) अणु
		secondary = of_find_mipi_dsi_device_by_node(np);
		of_node_put(np);

		अगर (!secondary)
			वापस -EPROBE_DEFER;
	पूर्ण

	/* रेजिस्टर a panel क्रम only the DSI-LINK1 पूर्णांकerface */
	अगर (secondary) अणु
		sharp = devm_kzalloc(&dsi->dev, माप(*sharp), GFP_KERNEL);
		अगर (!sharp) अणु
			put_device(&secondary->dev);
			वापस -ENOMEM;
		पूर्ण

		mipi_dsi_set_drvdata(dsi, sharp);

		sharp->link2 = secondary;
		sharp->link1 = dsi;

		err = sharp_panel_add(sharp);
		अगर (err < 0) अणु
			put_device(&secondary->dev);
			वापस err;
		पूर्ण
	पूर्ण

	err = mipi_dsi_attach(dsi);
	अगर (err < 0) अणु
		अगर (secondary)
			sharp_panel_del(sharp);

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा sharp_panel *sharp = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;

	/* only detach from host क्रम the DSI-LINK2 पूर्णांकerface */
	अगर (!sharp) अणु
		mipi_dsi_detach(dsi);
		वापस 0;
	पूर्ण

	err = drm_panel_disable(&sharp->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", err);

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	sharp_panel_del(sharp);

	वापस 0;
पूर्ण

अटल व्योम sharp_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा sharp_panel *sharp = mipi_dsi_get_drvdata(dsi);

	/* nothing to करो क्रम DSI-LINK2 */
	अगर (!sharp)
		वापस;

	drm_panel_disable(&sharp->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver sharp_panel_driver = अणु
	.driver = अणु
		.name = "panel-sharp-lq101r1sx01",
		.of_match_table = sharp_of_match,
	पूर्ण,
	.probe = sharp_panel_probe,
	.हटाओ = sharp_panel_हटाओ,
	.shutकरोwn = sharp_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(sharp_panel_driver);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("Sharp LQ101R1SX01 panel driver");
MODULE_LICENSE("GPL v2");
