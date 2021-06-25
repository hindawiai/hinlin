<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Heiko Schocher <hs@denx.de>
 *
 * from:
 * drivers/gpu/drm/panel/panel-ld9040.c
 * ld9040 AMOLED LCD drm_panel driver.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd
 * Derived from drivers/video/backlight/ld9040.c
 *
 * Andrzej Hajda <a.hajda@samsung.com>
*/

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <video/mipi_display.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा lg4573 अणु
	काष्ठा drm_panel panel;
	काष्ठा spi_device *spi;
	काष्ठा videomode vm;
पूर्ण;

अटल अंतरभूत काष्ठा lg4573 *panel_to_lg4573(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा lg4573, panel);
पूर्ण

अटल पूर्णांक lg4573_spi_ग_लिखो_u16(काष्ठा lg4573 *ctx, u16 data)
अणु
	काष्ठा spi_transfer xfer = अणु
		.len = 2,
	पूर्ण;
	__be16 temp = cpu_to_be16(data);
	काष्ठा spi_message msg;

	dev_dbg(ctx->panel.dev, "writing data: %x\n", data);
	xfer.tx_buf = &temp;
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	वापस spi_sync(ctx->spi, &msg);
पूर्ण

अटल पूर्णांक lg4573_spi_ग_लिखो_u16_array(काष्ठा lg4573 *ctx, स्थिर u16 *buffer,
				      अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = lg4573_spi_ग_लिखो_u16(ctx, buffer[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lg4573_spi_ग_लिखो_dcs(काष्ठा lg4573 *ctx, u8 dcs)
अणु
	वापस lg4573_spi_ग_लिखो_u16(ctx, (0x70 << 8 | dcs));
पूर्ण

अटल पूर्णांक lg4573_display_on(काष्ठा lg4573 *ctx)
अणु
	पूर्णांक ret;

	ret = lg4573_spi_ग_लिखो_dcs(ctx, MIPI_DCS_EXIT_SLEEP_MODE);
	अगर (ret)
		वापस ret;

	msleep(5);

	वापस lg4573_spi_ग_लिखो_dcs(ctx, MIPI_DCS_SET_DISPLAY_ON);
पूर्ण

अटल पूर्णांक lg4573_display_off(काष्ठा lg4573 *ctx)
अणु
	पूर्णांक ret;

	ret = lg4573_spi_ग_लिखो_dcs(ctx, MIPI_DCS_SET_DISPLAY_OFF);
	अगर (ret)
		वापस ret;

	msleep(120);

	वापस lg4573_spi_ग_लिखो_dcs(ctx, MIPI_DCS_ENTER_SLEEP_MODE);
पूर्ण

अटल पूर्णांक lg4573_display_mode_settings(काष्ठा lg4573 *ctx)
अणु
	अटल स्थिर u16 display_mode_settings[] = अणु
		0x703A, 0x7270, 0x70B1, 0x7208,
		0x723B, 0x720F, 0x70B2, 0x7200,
		0x72C8, 0x70B3, 0x7200, 0x70B4,
		0x7200, 0x70B5, 0x7242, 0x7210,
		0x7210, 0x7200, 0x7220, 0x70B6,
		0x720B, 0x720F, 0x723C, 0x7213,
		0x7213, 0x72E8, 0x70B7, 0x7246,
		0x7206, 0x720C, 0x7200, 0x7200,
	पूर्ण;

	dev_dbg(ctx->panel.dev, "transfer display mode settings\n");
	वापस lg4573_spi_ग_लिखो_u16_array(ctx, display_mode_settings,
					  ARRAY_SIZE(display_mode_settings));
पूर्ण

अटल पूर्णांक lg4573_घातer_settings(काष्ठा lg4573 *ctx)
अणु
	अटल स्थिर u16 घातer_settings[] = अणु
		0x70C0, 0x7201, 0x7211, 0x70C3,
		0x7207, 0x7203, 0x7204, 0x7204,
		0x7204, 0x70C4, 0x7212, 0x7224,
		0x7218, 0x7218, 0x7202, 0x7249,
		0x70C5, 0x726F, 0x70C6, 0x7241,
		0x7263,
	पूर्ण;

	dev_dbg(ctx->panel.dev, "transfer power settings\n");
	वापस lg4573_spi_ग_लिखो_u16_array(ctx, घातer_settings,
					  ARRAY_SIZE(घातer_settings));
पूर्ण

अटल पूर्णांक lg4573_gamma_settings(काष्ठा lg4573 *ctx)
अणु
	अटल स्थिर u16 gamma_settings[] = अणु
		0x70D0, 0x7203, 0x7207, 0x7273,
		0x7235, 0x7200, 0x7201, 0x7220,
		0x7200, 0x7203, 0x70D1, 0x7203,
		0x7207, 0x7273, 0x7235, 0x7200,
		0x7201, 0x7220, 0x7200, 0x7203,
		0x70D2, 0x7203, 0x7207, 0x7273,
		0x7235, 0x7200, 0x7201, 0x7220,
		0x7200, 0x7203, 0x70D3, 0x7203,
		0x7207, 0x7273, 0x7235, 0x7200,
		0x7201, 0x7220, 0x7200, 0x7203,
		0x70D4, 0x7203, 0x7207, 0x7273,
		0x7235, 0x7200, 0x7201, 0x7220,
		0x7200, 0x7203, 0x70D5, 0x7203,
		0x7207, 0x7273, 0x7235, 0x7200,
		0x7201, 0x7220, 0x7200, 0x7203,
	पूर्ण;

	dev_dbg(ctx->panel.dev, "transfer gamma settings\n");
	वापस lg4573_spi_ग_लिखो_u16_array(ctx, gamma_settings,
					  ARRAY_SIZE(gamma_settings));
पूर्ण

अटल पूर्णांक lg4573_init(काष्ठा lg4573 *ctx)
अणु
	पूर्णांक ret;

	dev_dbg(ctx->panel.dev, "initializing LCD\n");

	ret = lg4573_display_mode_settings(ctx);
	अगर (ret)
		वापस ret;

	ret = lg4573_घातer_settings(ctx);
	अगर (ret)
		वापस ret;

	वापस lg4573_gamma_settings(ctx);
पूर्ण

अटल पूर्णांक lg4573_घातer_on(काष्ठा lg4573 *ctx)
अणु
	वापस lg4573_display_on(ctx);
पूर्ण

अटल पूर्णांक lg4573_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा lg4573 *ctx = panel_to_lg4573(panel);

	वापस lg4573_display_off(ctx);
पूर्ण

अटल पूर्णांक lg4573_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा lg4573 *ctx = panel_to_lg4573(panel);

	lg4573_init(ctx);

	वापस lg4573_घातer_on(ctx);
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 28341,
	.hdisplay = 480,
	.hsync_start = 480 + 10,
	.hsync_end = 480 + 10 + 59,
	.htotal = 480 + 10 + 59 + 10,
	.vdisplay = 800,
	.vsync_start = 800 + 15,
	.vsync_end = 800 + 15 + 15,
	.vtotal = 800 + 15 + 15 + 15,
पूर्ण;

अटल पूर्णांक lg4573_get_modes(काष्ठा drm_panel *panel,
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

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 61;
	connector->display_info.height_mm = 103;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs lg4573_drm_funcs = अणु
	.disable = lg4573_disable,
	.enable = lg4573_enable,
	.get_modes = lg4573_get_modes,
पूर्ण;

अटल पूर्णांक lg4573_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा lg4573 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(&spi->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->spi = spi;

	spi_set_drvdata(spi, ctx);
	spi->bits_per_word = 8;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "SPI setup failed: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_panel_init(&ctx->panel, &spi->dev, &lg4573_drm_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&ctx->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक lg4573_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा lg4573 *ctx = spi_get_drvdata(spi);

	lg4573_display_off(ctx);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lg4573_of_match[] = अणु
	अणु .compatible = "lg,lg4573" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lg4573_of_match);

अटल काष्ठा spi_driver lg4573_driver = अणु
	.probe = lg4573_probe,
	.हटाओ = lg4573_हटाओ,
	.driver = अणु
		.name = "lg4573",
		.of_match_table = lg4573_of_match,
	पूर्ण,
पूर्ण;
module_spi_driver(lg4573_driver);

MODULE_AUTHOR("Heiko Schocher <hs@denx.de>");
MODULE_DESCRIPTION("lg4573 LCD Driver");
MODULE_LICENSE("GPL v2");
