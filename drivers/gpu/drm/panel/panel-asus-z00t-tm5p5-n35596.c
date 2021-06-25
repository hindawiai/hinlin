<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा पंचांग5p5_nt35596 अणु
	काष्ठा drm_panel panel;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *reset_gpio;
	bool prepared;
पूर्ण;

अटल अंतरभूत काष्ठा पंचांग5p5_nt35596 *to_पंचांग5p5_nt35596(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा पंचांग5p5_nt35596, panel);
पूर्ण

#घोषणा dsi_generic_ग_लिखो_seq(dsi, seq...) करो अणु				\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		पूर्णांक ret;						\
		ret = mipi_dsi_generic_ग_लिखो(dsi, d, ARRAY_SIZE(d));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

#घोषणा dsi_dcs_ग_लिखो_seq(dsi, seq...) करो अणु				\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		पूर्णांक ret;						\
		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, d, ARRAY_SIZE(d));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल व्योम पंचांग5p5_nt35596_reset(काष्ठा पंचांग5p5_nt35596 *ctx)
अणु
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(15000, 16000);
पूर्ण

अटल पूर्णांक पंचांग5p5_nt35596_on(काष्ठा पंचांग5p5_nt35596 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = ctx->dsi;

	dsi_generic_ग_लिखो_seq(dsi, 0xff, 0x05);
	dsi_generic_ग_लिखो_seq(dsi, 0xfb, 0x01);
	dsi_generic_ग_लिखो_seq(dsi, 0xc5, 0x31);
	dsi_generic_ग_लिखो_seq(dsi, 0xff, 0x04);
	dsi_generic_ग_लिखो_seq(dsi, 0x01, 0x84);
	dsi_generic_ग_लिखो_seq(dsi, 0x05, 0x25);
	dsi_generic_ग_लिखो_seq(dsi, 0x06, 0x01);
	dsi_generic_ग_लिखो_seq(dsi, 0x07, 0x20);
	dsi_generic_ग_लिखो_seq(dsi, 0x08, 0x06);
	dsi_generic_ग_लिखो_seq(dsi, 0x09, 0x08);
	dsi_generic_ग_लिखो_seq(dsi, 0x0a, 0x10);
	dsi_generic_ग_लिखो_seq(dsi, 0x0b, 0x10);
	dsi_generic_ग_लिखो_seq(dsi, 0x0c, 0x10);
	dsi_generic_ग_लिखो_seq(dsi, 0x0d, 0x14);
	dsi_generic_ग_लिखो_seq(dsi, 0x0e, 0x14);
	dsi_generic_ग_लिखो_seq(dsi, 0x0f, 0x14);
	dsi_generic_ग_लिखो_seq(dsi, 0x10, 0x14);
	dsi_generic_ग_लिखो_seq(dsi, 0x11, 0x14);
	dsi_generic_ग_लिखो_seq(dsi, 0x12, 0x14);
	dsi_generic_ग_लिखो_seq(dsi, 0x17, 0xf3);
	dsi_generic_ग_लिखो_seq(dsi, 0x18, 0xc0);
	dsi_generic_ग_लिखो_seq(dsi, 0x19, 0xc0);
	dsi_generic_ग_लिखो_seq(dsi, 0x1a, 0xc0);
	dsi_generic_ग_लिखो_seq(dsi, 0x1b, 0xb3);
	dsi_generic_ग_लिखो_seq(dsi, 0x1c, 0xb3);
	dsi_generic_ग_लिखो_seq(dsi, 0x1d, 0xb3);
	dsi_generic_ग_लिखो_seq(dsi, 0x1e, 0xb3);
	dsi_generic_ग_लिखो_seq(dsi, 0x1f, 0xb3);
	dsi_generic_ग_लिखो_seq(dsi, 0x20, 0xb3);
	dsi_generic_ग_लिखो_seq(dsi, 0xfb, 0x01);
	dsi_generic_ग_लिखो_seq(dsi, 0xff, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, 0xfb, 0x01);
	dsi_generic_ग_लिखो_seq(dsi, 0x35, 0x01);
	dsi_generic_ग_लिखो_seq(dsi, 0xd3, 0x06);
	dsi_generic_ग_लिखो_seq(dsi, 0xd4, 0x04);
	dsi_generic_ग_लिखो_seq(dsi, 0x5e, 0x0d);
	dsi_generic_ग_लिखो_seq(dsi, 0x11, 0x00);
	msleep(100);
	dsi_generic_ग_लिखो_seq(dsi, 0x29, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, 0x53, 0x24);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग5p5_nt35596_off(काष्ठा पंचांग5p5_nt35596 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = ctx->dsi;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set display off: %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(60);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण

	dsi_dcs_ग_लिखो_seq(dsi, 0x4f, 0x01);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग5p5_nt35596_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा पंचांग5p5_nt35596 *ctx = to_पंचांग5p5_nt35596(panel);
	काष्ठा device *dev = &ctx->dsi->dev;
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	पंचांग5p5_nt35596_reset(ctx);

	ret = पंचांग5p5_nt35596_on(ctx);
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

अटल पूर्णांक पंचांग5p5_nt35596_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा पंचांग5p5_nt35596 *ctx = to_पंचांग5p5_nt35596(panel);
	काष्ठा device *dev = &ctx->dsi->dev;
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = पंचांग5p5_nt35596_off(ctx);
	अगर (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies),
			       ctx->supplies);

	ctx->prepared = false;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode पंचांग5p5_nt35596_mode = अणु
	.घड़ी = (1080 + 100 + 8 + 16) * (1920 + 4 + 2 + 4) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 100,
	.hsync_end = 1080 + 100 + 8,
	.htotal = 1080 + 100 + 8 + 16,
	.vdisplay = 1920,
	.vsync_start = 1920 + 4,
	.vsync_end = 1920 + 4 + 2,
	.vtotal = 1920 + 4 + 2 + 4,
	.width_mm = 68,
	.height_mm = 121,
पूर्ण;

अटल पूर्णांक पंचांग5p5_nt35596_get_modes(काष्ठा drm_panel *panel,
				   काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &पंचांग5p5_nt35596_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs पंचांग5p5_nt35596_panel_funcs = अणु
	.prepare = पंचांग5p5_nt35596_prepare,
	.unprepare = पंचांग5p5_nt35596_unprepare,
	.get_modes = पंचांग5p5_nt35596_get_modes,
पूर्ण;

अटल पूर्णांक पंचांग5p5_nt35596_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = bl->props.brightness;
	पूर्णांक ret;

	अगर (bl->props.घातer != FB_BLANK_UNBLANK ||
	    bl->props.fb_blank != FB_BLANK_UNBLANK ||
	    bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	अगर (ret < 0)
		वापस ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग5p5_nt35596_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = bl->props.brightness;
	पूर्णांक ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness(dsi, &brightness);
	अगर (ret < 0)
		वापस ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	वापस brightness & 0xff;
पूर्ण

अटल स्थिर काष्ठा backlight_ops पंचांग5p5_nt35596_bl_ops = अणु
	.update_status = पंचांग5p5_nt35596_bl_update_status,
	.get_brightness = पंचांग5p5_nt35596_bl_get_brightness,
पूर्ण;

अटल काष्ठा backlight_device *
पंचांग5p5_nt35596_create_backlight(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	स्थिर काष्ठा backlight_properties props = अणु
		.type = BACKLIGHT_RAW,
		.brightness = 255,
		.max_brightness = 255,
	पूर्ण;

	वापस devm_backlight_device_रेजिस्टर(dev, dev_name(dev), dev, dsi,
					      &पंचांग5p5_nt35596_bl_ops, &props);
पूर्ण

अटल पूर्णांक पंचांग5p5_nt35596_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा पंचांग5p5_nt35596 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->supplies[0].supply = "vdd";
	ctx->supplies[1].supply = "vddio";
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

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	drm_panel_init(&ctx->panel, dev, &पंचांग5p5_nt35596_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->panel.backlight = पंचांग5p5_nt35596_create_backlight(dsi);
	अगर (IS_ERR(ctx->panel.backlight)) अणु
		ret = PTR_ERR(ctx->panel.backlight);
		dev_err(dev, "Failed to create backlight: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग5p5_nt35596_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा पंचांग5p5_nt35596 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev,
			"Failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id पंचांग5p5_nt35596_of_match[] = अणु
	अणु .compatible = "asus,z00t-tm5p5-n35596" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांग5p5_nt35596_of_match);

अटल काष्ठा mipi_dsi_driver पंचांग5p5_nt35596_driver = अणु
	.probe = पंचांग5p5_nt35596_probe,
	.हटाओ = पंचांग5p5_nt35596_हटाओ,
	.driver = अणु
		.name = "panel-tm5p5-nt35596",
		.of_match_table = पंचांग5p5_nt35596_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(पंचांग5p5_nt35596_driver);

MODULE_AUTHOR("Konrad Dybcio <konradybcio@gmail.com>");
MODULE_DESCRIPTION("DRM driver for tm5p5 nt35596 1080p video mode dsi panel");
MODULE_LICENSE("GPL v2");
