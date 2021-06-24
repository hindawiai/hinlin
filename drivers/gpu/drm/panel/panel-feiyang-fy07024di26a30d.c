<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Amarula Solutions
 * Author: Jagan Teki <jagan@amarulasolutions.com>
 */

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा FEIYANG_INIT_CMD_LEN	2

काष्ठा feiyang अणु
	काष्ठा drm_panel	panel;
	काष्ठा mipi_dsi_device	*dsi;

	काष्ठा regulator	*dvdd;
	काष्ठा regulator	*avdd;
	काष्ठा gpio_desc	*reset;
पूर्ण;

अटल अंतरभूत काष्ठा feiyang *panel_to_feiyang(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा feiyang, panel);
पूर्ण

काष्ठा feiyang_init_cmd अणु
	u8 data[FEIYANG_INIT_CMD_LEN];
पूर्ण;

अटल स्थिर काष्ठा feiyang_init_cmd feiyang_init_cmds[] = अणु
	अणु .data = अणु 0x80, 0x58 पूर्ण पूर्ण,
	अणु .data = अणु 0x81, 0x47 पूर्ण पूर्ण,
	अणु .data = अणु 0x82, 0xD4 पूर्ण पूर्ण,
	अणु .data = अणु 0x83, 0x88 पूर्ण पूर्ण,
	अणु .data = अणु 0x84, 0xA9 पूर्ण पूर्ण,
	अणु .data = अणु 0x85, 0xC3 पूर्ण पूर्ण,
	अणु .data = अणु 0x86, 0x82 पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक feiyang_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा feiyang *ctx = panel_to_feiyang(panel);
	काष्ठा mipi_dsi_device *dsi = ctx->dsi;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = regulator_enable(ctx->dvdd);
	अगर (ret)
		वापस ret;

	/* T1 (dvdd start + dvdd rise) 0 < T1 <= 10ms */
	msleep(10);

	ret = regulator_enable(ctx->avdd);
	अगर (ret)
		वापस ret;

	/* T3 (dvdd rise + avdd start + avdd rise) T3 >= 20ms */
	msleep(20);

	gpiod_set_value(ctx->reset, 0);

	/*
	 * T5 + T6 (avdd rise + video & logic संकेत rise)
	 * T5 >= 10ms, 0 < T6 <= 10ms
	 */
	msleep(20);

	gpiod_set_value(ctx->reset, 1);

	/* T12 (video & logic संकेत rise + backlight rise) T12 >= 200ms */
	msleep(200);

	क्रम (i = 0; i < ARRAY_SIZE(feiyang_init_cmds); i++) अणु
		स्थिर काष्ठा feiyang_init_cmd *cmd =
						&feiyang_init_cmds[i];

		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, cmd->data,
						FEIYANG_INIT_CMD_LEN);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक feiyang_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा feiyang *ctx = panel_to_feiyang(panel);

	/* T12 (video & logic संकेत rise + backlight rise) T12 >= 200ms */
	msleep(200);

	mipi_dsi_dcs_set_display_on(ctx->dsi);

	वापस 0;
पूर्ण

अटल पूर्णांक feiyang_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा feiyang *ctx = panel_to_feiyang(panel);

	वापस mipi_dsi_dcs_set_display_off(ctx->dsi);
पूर्ण

अटल पूर्णांक feiyang_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा feiyang *ctx = panel_to_feiyang(panel);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(ctx->dsi);
	अगर (ret < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(ctx->dsi);
	अगर (ret < 0)
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", ret);

	/* T13 (backlight fall + video & logic संकेत fall) T13 >= 200ms */
	msleep(200);

	gpiod_set_value(ctx->reset, 0);

	regulator_disable(ctx->avdd);

	/* T11 (dvdd rise to fall) 0 < T11 <= 10ms  */
	msleep(10);

	regulator_disable(ctx->dvdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode feiyang_शेष_mode = अणु
	.घड़ी		= 55000,

	.hdisplay	= 1024,
	.hsync_start	= 1024 + 310,
	.hsync_end	= 1024 + 310 + 20,
	.htotal		= 1024 + 310 + 20 + 90,

	.vdisplay	= 600,
	.vsync_start	= 600 + 12,
	.vsync_end	= 600 + 12 + 2,
	.vtotal		= 600 + 12 + 2 + 21,

	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
पूर्ण;

अटल पूर्णांक feiyang_get_modes(काष्ठा drm_panel *panel,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा feiyang *ctx = panel_to_feiyang(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &feiyang_शेष_mode);
	अगर (!mode) अणु
		dev_err(&ctx->dsi->dev, "failed to add mode %ux%u@%u\n",
			feiyang_शेष_mode.hdisplay,
			feiyang_शेष_mode.vdisplay,
			drm_mode_vrefresh(&feiyang_शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs feiyang_funcs = अणु
	.disable = feiyang_disable,
	.unprepare = feiyang_unprepare,
	.prepare = feiyang_prepare,
	.enable = feiyang_enable,
	.get_modes = feiyang_get_modes,
पूर्ण;

अटल पूर्णांक feiyang_dsi_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा feiyang *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(&dsi->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);
	ctx->dsi = dsi;

	drm_panel_init(&ctx->panel, &dsi->dev, &feiyang_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->dvdd = devm_regulator_get(&dsi->dev, "dvdd");
	अगर (IS_ERR(ctx->dvdd)) अणु
		dev_err(&dsi->dev, "Couldn't get dvdd regulator\n");
		वापस PTR_ERR(ctx->dvdd);
	पूर्ण

	ctx->avdd = devm_regulator_get(&dsi->dev, "avdd");
	अगर (IS_ERR(ctx->avdd)) अणु
		dev_err(&dsi->dev, "Couldn't get avdd regulator\n");
		वापस PTR_ERR(ctx->avdd);
	पूर्ण

	ctx->reset = devm_gpiod_get(&dsi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset)) अणु
		dev_err(&dsi->dev, "Couldn't get our reset GPIO\n");
		वापस PTR_ERR(ctx->reset);
	पूर्ण

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	dsi->mode_flags = MIPI_DSI_MODE_VIDEO_BURST;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 4;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक feiyang_dsi_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा feiyang *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id feiyang_of_match[] = अणु
	अणु .compatible = "feiyang,fy07024di26a30d", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, feiyang_of_match);

अटल काष्ठा mipi_dsi_driver feiyang_driver = अणु
	.probe = feiyang_dsi_probe,
	.हटाओ = feiyang_dsi_हटाओ,
	.driver = अणु
		.name = "feiyang-fy07024di26a30d",
		.of_match_table = feiyang_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(feiyang_driver);

MODULE_AUTHOR("Jagan Teki <jagan@amarulasolutions.com>");
MODULE_DESCRIPTION("Feiyang FY07024DI26A30-D MIPI-DSI LCD panel");
MODULE_LICENSE("GPL");
