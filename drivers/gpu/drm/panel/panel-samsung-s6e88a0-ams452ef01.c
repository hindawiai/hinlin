<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (C) 2019, Michael Srba

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा s6e88a0_ams452ef01 अणु
	काष्ठा drm_panel panel;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *reset_gpio;

	bool prepared;
पूर्ण;

अटल अंतरभूत काष्ठा
s6e88a0_ams452ef01 *to_s6e88a0_ams452ef01(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा s6e88a0_ams452ef01, panel);
पूर्ण

#घोषणा dsi_dcs_ग_लिखो_seq(dsi, seq...) करो अणु				\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		पूर्णांक ret;						\
		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, d, ARRAY_SIZE(d));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल व्योम s6e88a0_ams452ef01_reset(काष्ठा s6e88a0_ams452ef01 *ctx)
अणु
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(5000, 6000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
पूर्ण

अटल पूर्णांक s6e88a0_ams452ef01_on(काष्ठा s6e88a0_ams452ef01 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = ctx->dsi;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_dcs_ग_लिखो_seq(dsi, 0xf0, 0x5a, 0x5a); // enable LEVEL2 commands
	dsi_dcs_ग_लिखो_seq(dsi, 0xcc, 0x4c); // set Pixel Clock Divider polarity

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(120);

	// set शेष brightness/gama
	dsi_dcs_ग_लिखो_seq(dsi, 0xca,
			  0x01, 0x00, 0x01, 0x00, 0x01, 0x00,	// V255 RR,GG,BB
			  0x80, 0x80, 0x80,			// V203 R,G,B
			  0x80, 0x80, 0x80,			// V151 R,G,B
			  0x80, 0x80, 0x80,			// V87  R,G,B
			  0x80, 0x80, 0x80,			// V51  R,G,B
			  0x80, 0x80, 0x80,			// V35  R,G,B
			  0x80, 0x80, 0x80,			// V23  R,G,B
			  0x80, 0x80, 0x80,			// V11  R,G,B
			  0x6b, 0x68, 0x71,			// V3   R,G,B
			  0x00, 0x00, 0x00);			// V1   R,G,B
	// set शेष Amoled Off Ratio
	dsi_dcs_ग_लिखो_seq(dsi, 0xb2, 0x40, 0x0a, 0x17, 0x00, 0x0a);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb6, 0x2c, 0x0b); // set शेष elvss voltage
	dsi_dcs_ग_लिखो_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	dsi_dcs_ग_लिखो_seq(dsi, 0xf7, 0x03); // gamma/aor update
	dsi_dcs_ग_लिखो_seq(dsi, 0xf0, 0xa5, 0xa5); // disable LEVEL2 commands

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set display on: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s6e88a0_ams452ef01_off(काष्ठा s6e88a0_ams452ef01 *ctx)
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
	msleep(35);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(120);

	वापस 0;
पूर्ण

अटल पूर्णांक s6e88a0_ams452ef01_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e88a0_ams452ef01 *ctx = to_s6e88a0_ams452ef01(panel);
	काष्ठा device *dev = &ctx->dsi->dev;
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	s6e88a0_ams452ef01_reset(ctx);

	ret = s6e88a0_ams452ef01_on(ctx);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 0);
		regulator_bulk_disable(ARRAY_SIZE(ctx->supplies),
				       ctx->supplies);
		वापस ret;
	पूर्ण

	ctx->prepared = true;
	वापस 0;
पूर्ण

अटल पूर्णांक s6e88a0_ams452ef01_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e88a0_ams452ef01 *ctx = to_s6e88a0_ams452ef01(panel);
	काष्ठा device *dev = &ctx->dsi->dev;
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = s6e88a0_ams452ef01_off(ctx);
	अगर (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);

	ctx->prepared = false;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode s6e88a0_ams452ef01_mode = अणु
	.घड़ी = (540 + 88 + 4 + 20) * (960 + 14 + 2 + 8) * 60 / 1000,
	.hdisplay = 540,
	.hsync_start = 540 + 88,
	.hsync_end = 540 + 88 + 4,
	.htotal = 540 + 88 + 4 + 20,
	.vdisplay = 960,
	.vsync_start = 960 + 14,
	.vsync_end = 960 + 14 + 2,
	.vtotal = 960 + 14 + 2 + 8,
	.width_mm = 56,
	.height_mm = 100,
पूर्ण;

अटल पूर्णांक s6e88a0_ams452ef01_get_modes(काष्ठा drm_panel *panel,
					काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &s6e88a0_ams452ef01_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs s6e88a0_ams452ef01_panel_funcs = अणु
	.unprepare = s6e88a0_ams452ef01_unprepare,
	.prepare = s6e88a0_ams452ef01_prepare,
	.get_modes = s6e88a0_ams452ef01_get_modes,
पूर्ण;

अटल पूर्णांक s6e88a0_ams452ef01_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा s6e88a0_ams452ef01 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		ret = PTR_ERR(ctx->reset_gpio);
		dev_err(dev, "Failed to get reset-gpios: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST;

	drm_panel_init(&ctx->panel, dev, &s6e88a0_ams452ef01_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s6e88a0_ams452ef01_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा s6e88a0_ams452ef01 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id s6e88a0_ams452ef01_of_match[] = अणु
	अणु .compatible = "samsung,s6e88a0-ams452ef01" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s6e88a0_ams452ef01_of_match);

अटल काष्ठा mipi_dsi_driver s6e88a0_ams452ef01_driver = अणु
	.probe = s6e88a0_ams452ef01_probe,
	.हटाओ = s6e88a0_ams452ef01_हटाओ,
	.driver = अणु
		.name = "panel-s6e88a0-ams452ef01",
		.of_match_table = s6e88a0_ams452ef01_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(s6e88a0_ams452ef01_driver);

MODULE_AUTHOR("Michael Srba <Michael.Srba@seznam.cz>");
MODULE_DESCRIPTION("MIPI-DSI based Panel Driver for AMS452EF01 AMOLED LCD with a S6E88A0 controller");
MODULE_LICENSE("GPL v2");
