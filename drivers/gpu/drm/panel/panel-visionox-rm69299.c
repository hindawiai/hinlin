<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा visionox_rm69299 अणु
	काष्ठा drm_panel panel;
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा mipi_dsi_device *dsi;
	bool prepared;
	bool enabled;
पूर्ण;

अटल अंतरभूत काष्ठा visionox_rm69299 *panel_to_ctx(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा visionox_rm69299, panel);
पूर्ण

अटल पूर्णांक visionox_rm69299_घातer_on(काष्ठा visionox_rm69299 *ctx)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Reset sequence of visionox panel requires the panel to be
	 * out of reset क्रम 10ms, followed by being held in reset
	 * क्रम 10ms and then out again
	 */
	gpiod_set_value(ctx->reset_gpio, 1);
	usleep_range(10000, 20000);
	gpiod_set_value(ctx->reset_gpio, 0);
	usleep_range(10000, 20000);
	gpiod_set_value(ctx->reset_gpio, 1);
	usleep_range(10000, 20000);

	वापस 0;
पूर्ण

अटल पूर्णांक visionox_rm69299_घातer_off(काष्ठा visionox_rm69299 *ctx)
अणु
	gpiod_set_value(ctx->reset_gpio, 0);

	वापस regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल पूर्णांक visionox_rm69299_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा visionox_rm69299 *ctx = panel_to_ctx(panel);
	पूर्णांक ret;

	ctx->dsi->mode_flags = 0;

	ret = mipi_dsi_dcs_ग_लिखो(ctx->dsi, MIPI_DCS_SET_DISPLAY_OFF, शून्य, 0);
	अगर (ret < 0)
		dev_err(ctx->panel.dev, "set_display_off cmd failed ret = %d\n", ret);

	/* 120ms delay required here as per DCS spec */
	msleep(120);

	ret = mipi_dsi_dcs_ग_लिखो(ctx->dsi, MIPI_DCS_ENTER_SLEEP_MODE, शून्य, 0);
	अगर (ret < 0) अणु
		dev_err(ctx->panel.dev, "enter_sleep cmd failed ret = %d\n", ret);
	पूर्ण

	ret = visionox_rm69299_घातer_off(ctx);

	ctx->prepared = false;
	वापस ret;
पूर्ण

अटल पूर्णांक visionox_rm69299_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा visionox_rm69299 *ctx = panel_to_ctx(panel);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = visionox_rm69299_घातer_on(ctx);
	अगर (ret < 0)
		वापस ret;

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_ग_लिखो_buffer(ctx->dsi, (u8[]) अणु 0xfe, 0x00 पूर्ण, 2);
	अगर (ret < 0) अणु
		dev_err(ctx->panel.dev, "cmd set tx 0 failed, ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	ret = mipi_dsi_dcs_ग_लिखो_buffer(ctx->dsi, (u8[]) अणु 0xc2, 0x08 पूर्ण, 2);
	अगर (ret < 0) अणु
		dev_err(ctx->panel.dev, "cmd set tx 1 failed, ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	ret = mipi_dsi_dcs_ग_लिखो_buffer(ctx->dsi, (u8[]) अणु 0x35, 0x00 पूर्ण, 2);
	अगर (ret < 0) अणु
		dev_err(ctx->panel.dev, "cmd set tx 2 failed, ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	ret = mipi_dsi_dcs_ग_लिखो_buffer(ctx->dsi, (u8[]) अणु 0x51, 0xff पूर्ण, 2);
	अगर (ret < 0) अणु
		dev_err(ctx->panel.dev, "cmd set tx 3 failed, ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	ret = mipi_dsi_dcs_ग_लिखो(ctx->dsi, MIPI_DCS_EXIT_SLEEP_MODE, शून्य, 0);
	अगर (ret < 0) अणु
		dev_err(ctx->panel.dev, "exit_sleep_mode cmd failed ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	/* Per DSI spec रुको 120ms after sending निकास sleep DCS command */
	msleep(120);

	ret = mipi_dsi_dcs_ग_लिखो(ctx->dsi, MIPI_DCS_SET_DISPLAY_ON, शून्य, 0);
	अगर (ret < 0) अणु
		dev_err(ctx->panel.dev, "set_display_on cmd failed ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	/* Per DSI spec रुको 120ms after sending set_display_on DCS command */
	msleep(120);

	ctx->prepared = true;

	वापस 0;

घातer_off:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode visionox_rm69299_1080x2248_60hz = अणु
	.name = "1080x2248",
	.घड़ी = 158695,
	.hdisplay = 1080,
	.hsync_start = 1080 + 26,
	.hsync_end = 1080 + 26 + 2,
	.htotal = 1080 + 26 + 2 + 36,
	.vdisplay = 2248,
	.vsync_start = 2248 + 56,
	.vsync_end = 2248 + 56 + 4,
	.vtotal = 2248 + 56 + 4 + 4,
	.flags = 0,
पूर्ण;

अटल पूर्णांक visionox_rm69299_get_modes(काष्ठा drm_panel *panel,
				      काष्ठा drm_connector *connector)
अणु
	काष्ठा visionox_rm69299 *ctx = panel_to_ctx(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_create(connector->dev);
	अगर (!mode) अणु
		dev_err(ctx->panel.dev, "failed to create a new display mode\n");
		वापस 0;
	पूर्ण

	connector->display_info.width_mm = 74;
	connector->display_info.height_mm = 131;
	drm_mode_copy(mode, &visionox_rm69299_1080x2248_60hz);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs visionox_rm69299_drm_funcs = अणु
	.unprepare = visionox_rm69299_unprepare,
	.prepare = visionox_rm69299_prepare,
	.get_modes = visionox_rm69299_get_modes,
पूर्ण;

अटल पूर्णांक visionox_rm69299_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा visionox_rm69299 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->panel.dev = dev;
	ctx->dsi = dsi;

	ctx->supplies[0].supply = "vdda";
	ctx->supplies[1].supply = "vdd3p3";

	ret = devm_regulator_bulk_get(ctx->panel.dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	ctx->reset_gpio = devm_gpiod_get(ctx->panel.dev,
					 "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset gpio %ld\n", PTR_ERR(ctx->reset_gpio));
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	drm_panel_init(&ctx->panel, dev, &visionox_rm69299_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.dev = dev;
	ctx->panel.funcs = &visionox_rm69299_drm_funcs;
	drm_panel_add(&ctx->panel);

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_LPM |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;
	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "dsi attach failed ret = %d\n", ret);
		जाओ err_dsi_attach;
	पूर्ण

	ret = regulator_set_load(ctx->supplies[0].consumer, 32000);
	अगर (ret) अणु
		dev_err(dev, "regulator set load failed for vdda supply ret = %d\n", ret);
		जाओ err_set_load;
	पूर्ण

	ret = regulator_set_load(ctx->supplies[1].consumer, 13200);
	अगर (ret) अणु
		dev_err(dev, "regulator set load failed for vdd3p3 supply ret = %d\n", ret);
		जाओ err_set_load;
	पूर्ण

	वापस 0;

err_set_load:
	mipi_dsi_detach(dsi);
err_dsi_attach:
	drm_panel_हटाओ(&ctx->panel);
	वापस ret;
पूर्ण

अटल पूर्णांक visionox_rm69299_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा visionox_rm69299 *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(ctx->dsi);
	mipi_dsi_device_unरेजिस्टर(ctx->dsi);

	drm_panel_हटाओ(&ctx->panel);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id visionox_rm69299_of_match[] = अणु
	अणु .compatible = "visionox,rm69299-1080p-display", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, visionox_rm69299_of_match);

अटल काष्ठा mipi_dsi_driver visionox_rm69299_driver = अणु
	.driver = अणु
		.name = "panel-visionox-rm69299",
		.of_match_table = visionox_rm69299_of_match,
	पूर्ण,
	.probe = visionox_rm69299_probe,
	.हटाओ = visionox_rm69299_हटाओ,
पूर्ण;
module_mipi_dsi_driver(visionox_rm69299_driver);

MODULE_DESCRIPTION("Visionox RM69299 DSI Panel Driver");
MODULE_LICENSE("GPL v2");
