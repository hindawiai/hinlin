<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Caleb Connolly <caleb@connolly.tech>
 * Generated with linux-mdss-dsi-panel-driver-generator from venकरोr device tree:
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/swab.h>
#समावेश <linux/backlight.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा sofef00_panel अणु
	काष्ठा drm_panel panel;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;
	स्थिर काष्ठा drm_display_mode *mode;
	bool prepared;
पूर्ण;

अटल अंतरभूत
काष्ठा sofef00_panel *to_sofef00_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा sofef00_panel, panel);
पूर्ण

#घोषणा dsi_dcs_ग_लिखो_seq(dsi, seq...) करो अणु				\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		पूर्णांक ret;						\
		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, d, ARRAY_SIZE(d));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल व्योम sofef00_panel_reset(काष्ठा sofef00_panel *ctx)
अणु
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(5000, 6000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(12000, 13000);
पूर्ण

अटल पूर्णांक sofef00_panel_on(काष्ठा sofef00_panel *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = ctx->dsi;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण
	usleep_range(10000, 11000);

	dsi_dcs_ग_लिखो_seq(dsi, 0xf0, 0x5a, 0x5a);

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set tear on: %d\n", ret);
		वापस ret;
	पूर्ण

	dsi_dcs_ग_लिखो_seq(dsi, 0xf0, 0xa5, 0xa5);
	dsi_dcs_ग_लिखो_seq(dsi, 0xf0, 0x5a, 0x5a);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb0, 0x07);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb6, 0x12);
	dsi_dcs_ग_लिखो_seq(dsi, 0xf0, 0xa5, 0xa5);
	dsi_dcs_ग_लिखो_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x20);
	dsi_dcs_ग_लिखो_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x00);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set display on: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sofef00_panel_off(काष्ठा sofef00_panel *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = ctx->dsi;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set display off: %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(40);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(160);

	वापस 0;
पूर्ण

अटल पूर्णांक sofef00_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा sofef00_panel *ctx = to_sofef00_panel(panel);
	काष्ठा device *dev = &ctx->dsi->dev;
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = regulator_enable(ctx->supply);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	sofef00_panel_reset(ctx);

	ret = sofef00_panel_on(ctx);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		वापस ret;
	पूर्ण

	ctx->prepared = true;
	वापस 0;
पूर्ण

अटल पूर्णांक sofef00_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा sofef00_panel *ctx = to_sofef00_panel(panel);
	काष्ठा device *dev = &ctx->dsi->dev;
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = sofef00_panel_off(ctx);
	अगर (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	regulator_disable(ctx->supply);

	ctx->prepared = false;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode enchilada_panel_mode = अणु
	.घड़ी = (1080 + 112 + 16 + 36) * (2280 + 36 + 8 + 12) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 112,
	.hsync_end = 1080 + 112 + 16,
	.htotal = 1080 + 112 + 16 + 36,
	.vdisplay = 2280,
	.vsync_start = 2280 + 36,
	.vsync_end = 2280 + 36 + 8,
	.vtotal = 2280 + 36 + 8 + 12,
	.width_mm = 68,
	.height_mm = 145,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode fajita_panel_mode = अणु
	.घड़ी = (1080 + 72 + 16 + 36) * (2340 + 32 + 4 + 18) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 72,
	.hsync_end = 1080 + 72 + 16,
	.htotal = 1080 + 72 + 16 + 36,
	.vdisplay = 2340,
	.vsync_start = 2340 + 32,
	.vsync_end = 2340 + 32 + 4,
	.vtotal = 2340 + 32 + 4 + 18,
	.width_mm = 68,
	.height_mm = 145,
पूर्ण;

अटल पूर्णांक sofef00_panel_get_modes(काष्ठा drm_panel *panel, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;
	काष्ठा sofef00_panel *ctx = to_sofef00_panel(panel);

	mode = drm_mode_duplicate(connector->dev, ctx->mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs sofef00_panel_panel_funcs = अणु
	.prepare = sofef00_panel_prepare,
	.unprepare = sofef00_panel_unprepare,
	.get_modes = sofef00_panel_get_modes,
पूर्ण;

अटल पूर्णांक sofef00_panel_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा mipi_dsi_device *dsi = bl_get_data(bl);
	पूर्णांक err;
	u16 brightness;

	brightness = (u16)backlight_get_brightness(bl);
	// This panel needs the high and low bytes swapped क्रम the brightness value
	brightness = __swab16(brightness);

	err = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops sofef00_panel_bl_ops = अणु
	.update_status = sofef00_panel_bl_update_status,
पूर्ण;

अटल काष्ठा backlight_device *
sofef00_create_backlight(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	स्थिर काष्ठा backlight_properties props = अणु
		.type = BACKLIGHT_PLATFORM,
		.brightness = 1023,
		.max_brightness = 1023,
	पूर्ण;

	वापस devm_backlight_device_रेजिस्टर(dev, dev_name(dev), dev, dsi,
					      &sofef00_panel_bl_ops, &props);
पूर्ण

अटल पूर्णांक sofef00_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा sofef00_panel *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->mode = of_device_get_match_data(dev);

	अगर (!ctx->mode) अणु
		dev_err(dev, "Missing device mode\n");
		वापस -ENODEV;
	पूर्ण

	ctx->supply = devm_regulator_get(dev, "vddio");
	अगर (IS_ERR(ctx->supply)) अणु
		ret = PTR_ERR(ctx->supply);
		dev_err(dev, "Failed to get vddio regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		ret = PTR_ERR(ctx->reset_gpio);
		dev_warn(dev, "Failed to get reset-gpios: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;

	drm_panel_init(&ctx->panel, dev, &sofef00_panel_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->panel.backlight = sofef00_create_backlight(dsi);
	अगर (IS_ERR(ctx->panel.backlight))
		वापस dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sofef00_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा sofef00_panel *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sofef00_panel_of_match[] = अणु
	अणु // OnePlus 6 / enchilada
		.compatible = "samsung,sofef00",
		.data = &enchilada_panel_mode,
	पूर्ण,
	अणु // OnePlus 6T / fajita
		.compatible = "samsung,s6e3fc2x01",
		.data = &fajita_panel_mode,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sofef00_panel_of_match);

अटल काष्ठा mipi_dsi_driver sofef00_panel_driver = अणु
	.probe = sofef00_panel_probe,
	.हटाओ = sofef00_panel_हटाओ,
	.driver = अणु
		.name = "panel-oneplus6",
		.of_match_table = sofef00_panel_of_match,
	पूर्ण,
पूर्ण;

module_mipi_dsi_driver(sofef00_panel_driver);

MODULE_AUTHOR("Caleb Connolly <caleb@connolly.tech>");
MODULE_DESCRIPTION("DRM driver for Samsung AMOLED DSI panels found in OnePlus 6/6T phones");
MODULE_LICENSE("GPL v2");
