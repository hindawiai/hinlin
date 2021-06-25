<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2019 Theobroma Systems Design und Consulting GmbH
 *
 * base on panel-kingdisplay-kd097d04.c
 * Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/backlight.h>
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

काष्ठा ltk500hd1829 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator *vcc;
	काष्ठा regulator *iovcc;
	bool prepared;
पूर्ण;

काष्ठा ltk500hd1829_cmd अणु
	अक्षर cmd;
	अक्षर data;
पूर्ण;

/*
 * There is no description in the Reference Manual about these commands.
 * We received them from the venकरोr, so just use them as is.
 */
अटल स्थिर काष्ठा ltk500hd1829_cmd init_code[] = अणु
	अणु 0xE0, 0x00 पूर्ण,
	अणु 0xE1, 0x93 पूर्ण,
	अणु 0xE2, 0x65 पूर्ण,
	अणु 0xE3, 0xF8 पूर्ण,
	अणु 0x80, 0x03 पूर्ण,
	अणु 0xE0, 0x04 पूर्ण,
	अणु 0x2D, 0x03 पूर्ण,
	अणु 0xE0, 0x01 पूर्ण,
	अणु 0x00, 0x00 पूर्ण,
	अणु 0x01, 0xB6 पूर्ण,
	अणु 0x03, 0x00 पूर्ण,
	अणु 0x04, 0xC5 पूर्ण,
	अणु 0x17, 0x00 पूर्ण,
	अणु 0x18, 0xBF पूर्ण,
	अणु 0x19, 0x01 पूर्ण,
	अणु 0x1A, 0x00 पूर्ण,
	अणु 0x1B, 0xBF पूर्ण,
	अणु 0x1C, 0x01 पूर्ण,
	अणु 0x1F, 0x7C पूर्ण,
	अणु 0x20, 0x26 पूर्ण,
	अणु 0x21, 0x26 पूर्ण,
	अणु 0x22, 0x4E पूर्ण,
	अणु 0x37, 0x09 पूर्ण,
	अणु 0x38, 0x04 पूर्ण,
	अणु 0x39, 0x08 पूर्ण,
	अणु 0x3A, 0x1F पूर्ण,
	अणु 0x3B, 0x1F पूर्ण,
	अणु 0x3C, 0x78 पूर्ण,
	अणु 0x3D, 0xFF पूर्ण,
	अणु 0x3E, 0xFF पूर्ण,
	अणु 0x3F, 0x00 पूर्ण,
	अणु 0x40, 0x04 पूर्ण,
	अणु 0x41, 0xA0 पूर्ण,
	अणु 0x43, 0x0F पूर्ण,
	अणु 0x44, 0x0A पूर्ण,
	अणु 0x45, 0x24 पूर्ण,
	अणु 0x55, 0x01 पूर्ण,
	अणु 0x56, 0x01 पूर्ण,
	अणु 0x57, 0xA5 पूर्ण,
	अणु 0x58, 0x0A पूर्ण,
	अणु 0x59, 0x4A पूर्ण,
	अणु 0x5A, 0x38 पूर्ण,
	अणु 0x5B, 0x10 पूर्ण,
	अणु 0x5C, 0x19 पूर्ण,
	अणु 0x5D, 0x7C पूर्ण,
	अणु 0x5E, 0x64 पूर्ण,
	अणु 0x5F, 0x54 पूर्ण,
	अणु 0x60, 0x48 पूर्ण,
	अणु 0x61, 0x44 पूर्ण,
	अणु 0x62, 0x35 पूर्ण,
	अणु 0x63, 0x3A पूर्ण,
	अणु 0x64, 0x24 पूर्ण,
	अणु 0x65, 0x3B पूर्ण,
	अणु 0x66, 0x39 पूर्ण,
	अणु 0x67, 0x37 पूर्ण,
	अणु 0x68, 0x56 पूर्ण,
	अणु 0x69, 0x41 पूर्ण,
	अणु 0x6A, 0x47 पूर्ण,
	अणु 0x6B, 0x2F पूर्ण,
	अणु 0x6C, 0x23 पूर्ण,
	अणु 0x6D, 0x13 पूर्ण,
	अणु 0x6E, 0x02 पूर्ण,
	अणु 0x6F, 0x08 पूर्ण,
	अणु 0x70, 0x7C पूर्ण,
	अणु 0x71, 0x64 पूर्ण,
	अणु 0x72, 0x54 पूर्ण,
	अणु 0x73, 0x48 पूर्ण,
	अणु 0x74, 0x44 पूर्ण,
	अणु 0x75, 0x35 पूर्ण,
	अणु 0x76, 0x3A पूर्ण,
	अणु 0x77, 0x22 पूर्ण,
	अणु 0x78, 0x3B पूर्ण,
	अणु 0x79, 0x39 पूर्ण,
	अणु 0x7A, 0x38 पूर्ण,
	अणु 0x7B, 0x52 पूर्ण,
	अणु 0x7C, 0x41 पूर्ण,
	अणु 0x7D, 0x47 पूर्ण,
	अणु 0x7E, 0x2F पूर्ण,
	अणु 0x7F, 0x23 पूर्ण,
	अणु 0x80, 0x13 पूर्ण,
	अणु 0x81, 0x02 पूर्ण,
	अणु 0x82, 0x08 पूर्ण,
	अणु 0xE0, 0x02 पूर्ण,
	अणु 0x00, 0x57 पूर्ण,
	अणु 0x01, 0x77 पूर्ण,
	अणु 0x02, 0x44 पूर्ण,
	अणु 0x03, 0x46 पूर्ण,
	अणु 0x04, 0x48 पूर्ण,
	अणु 0x05, 0x4A पूर्ण,
	अणु 0x06, 0x4C पूर्ण,
	अणु 0x07, 0x4E पूर्ण,
	अणु 0x08, 0x50 पूर्ण,
	अणु 0x09, 0x55 पूर्ण,
	अणु 0x0A, 0x52 पूर्ण,
	अणु 0x0B, 0x55 पूर्ण,
	अणु 0x0C, 0x55 पूर्ण,
	अणु 0x0D, 0x55 पूर्ण,
	अणु 0x0E, 0x55 पूर्ण,
	अणु 0x0F, 0x55 पूर्ण,
	अणु 0x10, 0x55 पूर्ण,
	अणु 0x11, 0x55 पूर्ण,
	अणु 0x12, 0x55 पूर्ण,
	अणु 0x13, 0x40 पूर्ण,
	अणु 0x14, 0x55 पूर्ण,
	अणु 0x15, 0x55 पूर्ण,
	अणु 0x16, 0x57 पूर्ण,
	अणु 0x17, 0x77 पूर्ण,
	अणु 0x18, 0x45 पूर्ण,
	अणु 0x19, 0x47 पूर्ण,
	अणु 0x1A, 0x49 पूर्ण,
	अणु 0x1B, 0x4B पूर्ण,
	अणु 0x1C, 0x4D पूर्ण,
	अणु 0x1D, 0x4F पूर्ण,
	अणु 0x1E, 0x51 पूर्ण,
	अणु 0x1F, 0x55 पूर्ण,
	अणु 0x20, 0x53 पूर्ण,
	अणु 0x21, 0x55 पूर्ण,
	अणु 0x22, 0x55 पूर्ण,
	अणु 0x23, 0x55 पूर्ण,
	अणु 0x24, 0x55 पूर्ण,
	अणु 0x25, 0x55 पूर्ण,
	अणु 0x26, 0x55 पूर्ण,
	अणु 0x27, 0x55 पूर्ण,
	अणु 0x28, 0x55 पूर्ण,
	अणु 0x29, 0x41 पूर्ण,
	अणु 0x2A, 0x55 पूर्ण,
	अणु 0x2B, 0x55 पूर्ण,
	अणु 0x2C, 0x57 पूर्ण,
	अणु 0x2D, 0x77 पूर्ण,
	अणु 0x2E, 0x4F पूर्ण,
	अणु 0x2F, 0x4D पूर्ण,
	अणु 0x30, 0x4B पूर्ण,
	अणु 0x31, 0x49 पूर्ण,
	अणु 0x32, 0x47 पूर्ण,
	अणु 0x33, 0x45 पूर्ण,
	अणु 0x34, 0x41 पूर्ण,
	अणु 0x35, 0x55 पूर्ण,
	अणु 0x36, 0x53 पूर्ण,
	अणु 0x37, 0x55 पूर्ण,
	अणु 0x38, 0x55 पूर्ण,
	अणु 0x39, 0x55 पूर्ण,
	अणु 0x3A, 0x55 पूर्ण,
	अणु 0x3B, 0x55 पूर्ण,
	अणु 0x3C, 0x55 पूर्ण,
	अणु 0x3D, 0x55 पूर्ण,
	अणु 0x3E, 0x55 पूर्ण,
	अणु 0x3F, 0x51 पूर्ण,
	अणु 0x40, 0x55 पूर्ण,
	अणु 0x41, 0x55 पूर्ण,
	अणु 0x42, 0x57 पूर्ण,
	अणु 0x43, 0x77 पूर्ण,
	अणु 0x44, 0x4E पूर्ण,
	अणु 0x45, 0x4C पूर्ण,
	अणु 0x46, 0x4A पूर्ण,
	अणु 0x47, 0x48 पूर्ण,
	अणु 0x48, 0x46 पूर्ण,
	अणु 0x49, 0x44 पूर्ण,
	अणु 0x4A, 0x40 पूर्ण,
	अणु 0x4B, 0x55 पूर्ण,
	अणु 0x4C, 0x52 पूर्ण,
	अणु 0x4D, 0x55 पूर्ण,
	अणु 0x4E, 0x55 पूर्ण,
	अणु 0x4F, 0x55 पूर्ण,
	अणु 0x50, 0x55 पूर्ण,
	अणु 0x51, 0x55 पूर्ण,
	अणु 0x52, 0x55 पूर्ण,
	अणु 0x53, 0x55 पूर्ण,
	अणु 0x54, 0x55 पूर्ण,
	अणु 0x55, 0x50 पूर्ण,
	अणु 0x56, 0x55 पूर्ण,
	अणु 0x57, 0x55 पूर्ण,
	अणु 0x58, 0x40 पूर्ण,
	अणु 0x59, 0x00 पूर्ण,
	अणु 0x5A, 0x00 पूर्ण,
	अणु 0x5B, 0x10 पूर्ण,
	अणु 0x5C, 0x09 पूर्ण,
	अणु 0x5D, 0x30 पूर्ण,
	अणु 0x5E, 0x01 पूर्ण,
	अणु 0x5F, 0x02 पूर्ण,
	अणु 0x60, 0x30 पूर्ण,
	अणु 0x61, 0x03 पूर्ण,
	अणु 0x62, 0x04 पूर्ण,
	अणु 0x63, 0x06 पूर्ण,
	अणु 0x64, 0x6A पूर्ण,
	अणु 0x65, 0x75 पूर्ण,
	अणु 0x66, 0x0F पूर्ण,
	अणु 0x67, 0xB3 पूर्ण,
	अणु 0x68, 0x0B पूर्ण,
	अणु 0x69, 0x06 पूर्ण,
	अणु 0x6A, 0x6A पूर्ण,
	अणु 0x6B, 0x10 पूर्ण,
	अणु 0x6C, 0x00 पूर्ण,
	अणु 0x6D, 0x04 पूर्ण,
	अणु 0x6E, 0x04 पूर्ण,
	अणु 0x6F, 0x88 पूर्ण,
	अणु 0x70, 0x00 पूर्ण,
	अणु 0x71, 0x00 पूर्ण,
	अणु 0x72, 0x06 पूर्ण,
	अणु 0x73, 0x7B पूर्ण,
	अणु 0x74, 0x00 पूर्ण,
	अणु 0x75, 0xBC पूर्ण,
	अणु 0x76, 0x00 पूर्ण,
	अणु 0x77, 0x05 पूर्ण,
	अणु 0x78, 0x2E पूर्ण,
	अणु 0x79, 0x00 पूर्ण,
	अणु 0x7A, 0x00 पूर्ण,
	अणु 0x7B, 0x00 पूर्ण,
	अणु 0x7C, 0x00 पूर्ण,
	अणु 0x7D, 0x03 पूर्ण,
	अणु 0x7E, 0x7B पूर्ण,
	अणु 0xE0, 0x04 पूर्ण,
	अणु 0x09, 0x10 पूर्ण,
	अणु 0x2B, 0x2B पूर्ण,
	अणु 0x2E, 0x44 पूर्ण,
	अणु 0xE0, 0x00 पूर्ण,
	अणु 0xE6, 0x02 पूर्ण,
	अणु 0xE7, 0x02 पूर्ण,
	अणु 0x35, 0x00 पूर्ण,
पूर्ण;

अटल अंतरभूत
काष्ठा ltk500hd1829 *panel_to_ltk500hd1829(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा ltk500hd1829, panel);
पूर्ण

अटल पूर्णांक ltk500hd1829_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ltk500hd1829 *ctx = panel_to_ltk500hd1829(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", ret);
	पूर्ण

	/* 120ms to enter sleep mode */
	msleep(120);

	regulator_disable(ctx->iovcc);
	regulator_disable(ctx->vcc);

	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक ltk500hd1829_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ltk500hd1829 *ctx = panel_to_ltk500hd1829(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = regulator_enable(ctx->vcc);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable vci supply: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regulator_enable(ctx->iovcc);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable iovcc supply: %d\n", ret);
		जाओ disable_vcc;
	पूर्ण

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	/* tRW: 10us */
	usleep_range(10, 20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);

	/* tRT: >= 5ms */
	usleep_range(5000, 6000);

	क्रम (i = 0; i < ARRAY_SIZE(init_code); i++) अणु
		ret = mipi_dsi_generic_ग_लिखो(dsi, &init_code[i],
					     माप(काष्ठा ltk500hd1829_cmd));
		अगर (ret < 0) अणु
			dev_err(panel->dev, "failed to write init cmds: %d\n", ret);
			जाओ disable_iovcc;
		पूर्ण
	पूर्ण

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	/* 120ms to निकास sleep mode */
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	ctx->prepared = true;

	वापस 0;

disable_iovcc:
	regulator_disable(ctx->iovcc);
disable_vcc:
	regulator_disable(ctx->vcc);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.hdisplay	= 720,
	.hsync_start	= 720 + 50,
	.hsync_end	= 720 + 50 + 50,
	.htotal		= 720 + 50 + 50 + 50,
	.vdisplay	= 1280,
	.vsync_start	= 1280 + 30,
	.vsync_end	= 1280 + 30 + 4,
	.vtotal		= 1280 + 30 + 4 + 12,
	.घड़ी		= 69217,
	.width_mm	= 62,
	.height_mm	= 110,
पूर्ण;

अटल पूर्णांक ltk500hd1829_get_modes(काष्ठा drm_panel *panel,
				  काष्ठा drm_connector *connector)
अणु
	काष्ठा ltk500hd1829 *ctx = panel_to_ltk500hd1829(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(ctx->dev, "failed to add mode %ux%u@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs ltk500hd1829_funcs = अणु
	.unprepare = ltk500hd1829_unprepare,
	.prepare = ltk500hd1829_prepare,
	.get_modes = ltk500hd1829_get_modes,
पूर्ण;

अटल पूर्णांक ltk500hd1829_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा ltk500hd1829 *ctx;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	ctx = devm_kzalloc(&dsi->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset gpio\n");
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	ctx->vcc = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(ctx->vcc)) अणु
		ret = PTR_ERR(ctx->vcc);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request vcc regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->iovcc = devm_regulator_get(dev, "iovcc");
	अगर (IS_ERR(ctx->iovcc)) अणु
		ret = PTR_ERR(ctx->iovcc);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request iovcc regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_EOT_PACKET;

	drm_panel_init(&ctx->panel, &dsi->dev, &ltk500hd1829_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "mipi_dsi_attach failed: %d\n", ret);
		drm_panel_हटाओ(&ctx->panel);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ltk500hd1829_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा ltk500hd1829 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_unprepare(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to unprepare panel: %d\n", ret);

	ret = drm_panel_disable(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to disable panel: %d\n", ret);
पूर्ण

अटल पूर्णांक ltk500hd1829_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा ltk500hd1829 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ltk500hd1829_shutकरोwn(dsi);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ltk500hd1829_of_match[] = अणु
	अणु .compatible = "leadtek,ltk500hd1829", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ltk500hd1829_of_match);

अटल काष्ठा mipi_dsi_driver ltk500hd1829_driver = अणु
	.driver = अणु
		.name = "panel-leadtek-ltk500hd1829",
		.of_match_table = ltk500hd1829_of_match,
	पूर्ण,
	.probe = ltk500hd1829_probe,
	.हटाओ = ltk500hd1829_हटाओ,
	.shutकरोwn = ltk500hd1829_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(ltk500hd1829_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko.stuebner@theobroma-systems.com>");
MODULE_DESCRIPTION("Leadtek LTK500HD1829 panel driver");
MODULE_LICENSE("GPL v2");
