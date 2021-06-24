<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018-2019, Bridge Systems BV
 * Copyright (C) 2018-2019, Bootlin
 * Copyright (C) 2017, Free Electrons
 *
 * This file based on panel-ilitek-ili9881c.c
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/module.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा rb070d30_panel अणु
	काष्ठा drm_panel panel;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा regulator *supply;

	काष्ठा अणु
		काष्ठा gpio_desc *घातer;
		काष्ठा gpio_desc *reset;
		काष्ठा gpio_desc *updn;
		काष्ठा gpio_desc *shlr;
	पूर्ण gpios;
पूर्ण;

अटल अंतरभूत काष्ठा rb070d30_panel *panel_to_rb070d30_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा rb070d30_panel, panel);
पूर्ण

अटल पूर्णांक rb070d30_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);
	पूर्णांक ret;

	ret = regulator_enable(ctx->supply);
	अगर (ret < 0) अणु
		dev_err(&ctx->dsi->dev, "Failed to enable supply: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(20);
	gpiod_set_value(ctx->gpios.घातer, 1);
	msleep(20);
	gpiod_set_value(ctx->gpios.reset, 1);
	msleep(20);
	वापस 0;
पूर्ण

अटल पूर्णांक rb070d30_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);

	gpiod_set_value(ctx->gpios.reset, 0);
	gpiod_set_value(ctx->gpios.घातer, 0);
	regulator_disable(ctx->supply);

	वापस 0;
पूर्ण

अटल पूर्णांक rb070d30_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);

	वापस mipi_dsi_dcs_निकास_sleep_mode(ctx->dsi);
पूर्ण

अटल पूर्णांक rb070d30_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);

	वापस mipi_dsi_dcs_enter_sleep_mode(ctx->dsi);
पूर्ण

/* Default timings */
अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी		= 51206,
	.hdisplay	= 1024,
	.hsync_start	= 1024 + 160,
	.hsync_end	= 1024 + 160 + 80,
	.htotal		= 1024 + 160 + 80 + 80,
	.vdisplay	= 600,
	.vsync_start	= 600 + 12,
	.vsync_end	= 600 + 12 + 10,
	.vtotal		= 600 + 12 + 10 + 13,

	.width_mm	= 154,
	.height_mm	= 85,
पूर्ण;

अटल पूर्णांक rb070d30_panel_get_modes(काष्ठा drm_panel *panel,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);
	काष्ठा drm_display_mode *mode;
	अटल स्थिर u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(&ctx->dsi->dev, "Failed to add mode " DRM_MODE_FMT "\n",
			DRM_MODE_ARG(&शेष_mode));
		वापस -EINVAL;
	पूर्ण

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.bpc = 8;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_display_info_set_bus_क्रमmats(&connector->display_info,
					 &bus_क्रमmat, 1);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs rb070d30_panel_funcs = अणु
	.get_modes	= rb070d30_panel_get_modes,
	.prepare	= rb070d30_panel_prepare,
	.enable		= rb070d30_panel_enable,
	.disable	= rb070d30_panel_disable,
	.unprepare	= rb070d30_panel_unprepare,
पूर्ण;

अटल पूर्णांक rb070d30_panel_dsi_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा rb070d30_panel *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(&dsi->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->supply = devm_regulator_get(&dsi->dev, "vcc-lcd");
	अगर (IS_ERR(ctx->supply))
		वापस PTR_ERR(ctx->supply);

	mipi_dsi_set_drvdata(dsi, ctx);
	ctx->dsi = dsi;

	drm_panel_init(&ctx->panel, &dsi->dev, &rb070d30_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->gpios.reset = devm_gpiod_get(&dsi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->gpios.reset)) अणु
		dev_err(&dsi->dev, "Couldn't get our reset GPIO\n");
		वापस PTR_ERR(ctx->gpios.reset);
	पूर्ण

	ctx->gpios.घातer = devm_gpiod_get(&dsi->dev, "power", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->gpios.घातer)) अणु
		dev_err(&dsi->dev, "Couldn't get our power GPIO\n");
		वापस PTR_ERR(ctx->gpios.घातer);
	पूर्ण

	/*
	 * We करोn't change the state of that GPIO later on but we need
	 * to क्रमce it पूर्णांकo a low state.
	 */
	ctx->gpios.updn = devm_gpiod_get(&dsi->dev, "updn", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->gpios.updn)) अणु
		dev_err(&dsi->dev, "Couldn't get our updn GPIO\n");
		वापस PTR_ERR(ctx->gpios.updn);
	पूर्ण

	/*
	 * We करोn't change the state of that GPIO later on but we need
	 * to क्रमce it पूर्णांकo a low state.
	 */
	ctx->gpios.shlr = devm_gpiod_get(&dsi->dev, "shlr", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->gpios.shlr)) अणु
		dev_err(&dsi->dev, "Couldn't get our shlr GPIO\n");
		वापस PTR_ERR(ctx->gpios.shlr);
	पूर्ण

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_MODE_LPM;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 4;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक rb070d30_panel_dsi_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा rb070d30_panel *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rb070d30_panel_of_match[] = अणु
	अणु .compatible = "ronbo,rb070d30" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rb070d30_panel_of_match);

अटल काष्ठा mipi_dsi_driver rb070d30_panel_driver = अणु
	.probe = rb070d30_panel_dsi_probe,
	.हटाओ = rb070d30_panel_dsi_हटाओ,
	.driver = अणु
		.name = "panel-ronbo-rb070d30",
		.of_match_table	= rb070d30_panel_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(rb070d30_panel_driver);

MODULE_AUTHOR("Boris Brezillon <boris.brezillon@bootlin.com>");
MODULE_AUTHOR("Konstantin Sudakov <k.sudakov@integrasources.com>");
MODULE_DESCRIPTION("Ronbo RB070D30 Panel Driver");
MODULE_LICENSE("GPL");
