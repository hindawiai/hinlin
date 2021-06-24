<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * MIPI-DSI Samsung s6d16d0 panel driver. This is a 864x480
 * AMOLED panel with a command-only DSI पूर्णांकerface.
 */

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>

काष्ठा s6d16d0 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

/*
 * The timings are not very helpful as the display is used in
 * command mode.
 */
अटल स्थिर काष्ठा drm_display_mode samsung_s6d16d0_mode = अणु
	/* HS घड़ी, (htotal*vtotal*vrefresh)/1000 */
	.घड़ी = 420160,
	.hdisplay = 864,
	.hsync_start = 864 + 154,
	.hsync_end = 864 + 154 + 16,
	.htotal = 864 + 154 + 16 + 32,
	.vdisplay = 480,
	.vsync_start = 480 + 1,
	.vsync_end = 480 + 1 + 1,
	.vtotal = 480 + 1 + 1 + 1,
	.width_mm = 84,
	.height_mm = 48,
पूर्ण;

अटल अंतरभूत काष्ठा s6d16d0 *panel_to_s6d16d0(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा s6d16d0, panel);
पूर्ण

अटल पूर्णांक s6d16d0_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6d16d0 *s6 = panel_to_s6d16d0(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	पूर्णांक ret;

	/* Enter sleep mode */
	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret) अणु
		dev_err(s6->dev, "failed to enter sleep mode (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Assert RESET */
	gpiod_set_value_cansleep(s6->reset_gpio, 1);
	regulator_disable(s6->supply);

	वापस 0;
पूर्ण

अटल पूर्णांक s6d16d0_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6d16d0 *s6 = panel_to_s6d16d0(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	पूर्णांक ret;

	ret = regulator_enable(s6->supply);
	अगर (ret) अणु
		dev_err(s6->dev, "failed to enable supply (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Assert RESET */
	gpiod_set_value_cansleep(s6->reset_gpio, 1);
	udelay(10);
	/* De-निश्चित RESET */
	gpiod_set_value_cansleep(s6->reset_gpio, 0);
	msleep(120);

	/* Enabe tearing mode: send TE (tearing effect) at VBLANK */
	ret = mipi_dsi_dcs_set_tear_on(dsi,
				       MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	अगर (ret) अणु
		dev_err(s6->dev, "failed to enable vblank TE (%d)\n", ret);
		वापस ret;
	पूर्ण
	/* Exit sleep mode and घातer on */
	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret) अणु
		dev_err(s6->dev, "failed to exit sleep mode (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s6d16d0_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6d16d0 *s6 = panel_to_s6d16d0(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret) अणु
		dev_err(s6->dev, "failed to turn display on (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s6d16d0_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6d16d0 *s6 = panel_to_s6d16d0(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret) अणु
		dev_err(s6->dev, "failed to turn display off (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s6d16d0_get_modes(काष्ठा drm_panel *panel,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &samsung_s6d16d0_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "bad mode or failed to add mode\n");
		वापस -EINVAL;
	पूर्ण
	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	drm_mode_probed_add(connector, mode);

	वापस 1; /* Number of modes */
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs s6d16d0_drm_funcs = अणु
	.disable = s6d16d0_disable,
	.unprepare = s6d16d0_unprepare,
	.prepare = s6d16d0_prepare,
	.enable = s6d16d0_enable,
	.get_modes = s6d16d0_get_modes,
पूर्ण;

अटल पूर्णांक s6d16d0_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा s6d16d0 *s6;
	पूर्णांक ret;

	s6 = devm_kzalloc(dev, माप(काष्ठा s6d16d0), GFP_KERNEL);
	अगर (!s6)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, s6);
	s6->dev = dev;

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->hs_rate = 420160000;
	dsi->lp_rate = 19200000;
	/*
	 * This display uses command mode so no MIPI_DSI_MODE_VIDEO
	 * or MIPI_DSI_MODE_VIDEO_SYNC_PULSE
	 *
	 * As we only send commands we करो not need to be continuously
	 * घड़ीed.
	 */
	dsi->mode_flags = MIPI_DSI_CLOCK_NON_CONTINUOUS;

	s6->supply = devm_regulator_get(dev, "vdd1");
	अगर (IS_ERR(s6->supply))
		वापस PTR_ERR(s6->supply);

	/* This निश्चितs RESET by शेष */
	s6->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						 GPIOD_OUT_HIGH);
	अगर (IS_ERR(s6->reset_gpio)) अणु
		ret = PTR_ERR(s6->reset_gpio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request GPIO (%d)\n", ret);
		वापस ret;
	पूर्ण

	drm_panel_init(&s6->panel, dev, &s6d16d0_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	drm_panel_add(&s6->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0)
		drm_panel_हटाओ(&s6->panel);

	वापस ret;
पूर्ण

अटल पूर्णांक s6d16d0_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा s6d16d0 *s6 = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&s6->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id s6d16d0_of_match[] = अणु
	अणु .compatible = "samsung,s6d16d0" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s6d16d0_of_match);

अटल काष्ठा mipi_dsi_driver s6d16d0_driver = अणु
	.probe = s6d16d0_probe,
	.हटाओ = s6d16d0_हटाओ,
	.driver = अणु
		.name = "panel-samsung-s6d16d0",
		.of_match_table = s6d16d0_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(s6d16d0_driver);

MODULE_AUTHOR("Linus Wallei <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("MIPI-DSI s6d16d0 Panel Driver");
MODULE_LICENSE("GPL v2");
