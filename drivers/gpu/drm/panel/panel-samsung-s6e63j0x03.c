<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MIPI-DSI based S6E63J0X03 AMOLED lcd 1.63 inch panel driver.
 *
 * Copyright (c) 2014-2017 Samsung Electronics Co., Ltd
 *
 * Inki Dae <inki.dae@samsung.com>
 * Hoegeun Kwon <hoegeun.kwon@samsung.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा MCS_LEVEL2_KEY		0xf0
#घोषणा MCS_MTP_KEY		0xf1
#घोषणा MCS_MTP_SET3		0xd4

#घोषणा MAX_BRIGHTNESS		100
#घोषणा DEFAULT_BRIGHTNESS	80

#घोषणा NUM_GAMMA_STEPS		9
#घोषणा GAMMA_CMD_CNT		28

#घोषणा FIRST_COLUMN 20

काष्ठा s6e63j0x03 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा backlight_device *bl_dev;

	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 4649,
	.hdisplay = 320,
	.hsync_start = 320 + 1,
	.hsync_end = 320 + 1 + 1,
	.htotal = 320 + 1 + 1 + 1,
	.vdisplay = 320,
	.vsync_start = 320 + 150,
	.vsync_end = 320 + 150 + 1,
	.vtotal = 320 + 150 + 1 + 2,
	.flags = 0,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर gamma_tbl[NUM_GAMMA_STEPS][GAMMA_CMD_CNT] = अणु
	अणु	/* Gamma 10 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x52, 0x6b, 0x6f, 0x26,
		0x28, 0x2d, 0x28, 0x26, 0x27, 0x33, 0x34, 0x32, 0x36, 0x36,
		0x35, 0x00, 0xab, 0x00, 0xae, 0x00, 0xbf
	पूर्ण,
	अणु	/* gamma 30 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x70, 0x7f, 0x7f, 0x4e, 0x64, 0x69, 0x26,
		0x27, 0x2a, 0x28, 0x29, 0x27, 0x31, 0x32, 0x31, 0x35, 0x34,
		0x35, 0x00, 0xc4, 0x00, 0xca, 0x00, 0xdc
	पूर्ण,
	अणु	/* gamma 60 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x65, 0x7b, 0x7d, 0x5f, 0x67, 0x68, 0x2a,
		0x28, 0x29, 0x28, 0x2a, 0x27, 0x31, 0x2f, 0x30, 0x34, 0x33,
		0x34, 0x00, 0xd9, 0x00, 0xe4, 0x00, 0xf5
	पूर्ण,
	अणु	/* gamma 90 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x4d, 0x6f, 0x71, 0x67, 0x6a, 0x6c, 0x29,
		0x28, 0x28, 0x28, 0x29, 0x27, 0x30, 0x2e, 0x30, 0x32, 0x31,
		0x31, 0x00, 0xea, 0x00, 0xf6, 0x01, 0x09
	पूर्ण,
	अणु	/* gamma 120 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x3d, 0x66, 0x68, 0x69, 0x69, 0x69, 0x28,
		0x28, 0x27, 0x28, 0x28, 0x27, 0x30, 0x2e, 0x2f, 0x31, 0x31,
		0x30, 0x00, 0xf9, 0x01, 0x05, 0x01, 0x1b
	पूर्ण,
	अणु	/* gamma 150 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x31, 0x51, 0x53, 0x66, 0x66, 0x67, 0x28,
		0x29, 0x27, 0x28, 0x27, 0x27, 0x2e, 0x2d, 0x2e, 0x31, 0x31,
		0x30, 0x01, 0x04, 0x01, 0x11, 0x01, 0x29
	पूर्ण,
	अणु	/* gamma 200 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x2f, 0x4f, 0x51, 0x67, 0x65, 0x65, 0x29,
		0x2a, 0x28, 0x27, 0x25, 0x26, 0x2d, 0x2c, 0x2c, 0x30, 0x30,
		0x30, 0x01, 0x14, 0x01, 0x23, 0x01, 0x3b
	पूर्ण,
	अणु	/* gamma 240 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x2c, 0x4d, 0x50, 0x65, 0x63, 0x64, 0x2a,
		0x2c, 0x29, 0x26, 0x24, 0x25, 0x2c, 0x2b, 0x2b, 0x30, 0x30,
		0x30, 0x01, 0x1e, 0x01, 0x2f, 0x01, 0x47
	पूर्ण,
	अणु	/* gamma 300 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x38, 0x61, 0x64, 0x65, 0x63, 0x64, 0x28,
		0x2a, 0x27, 0x26, 0x23, 0x25, 0x2b, 0x2b, 0x2a, 0x30, 0x2f,
		0x30, 0x01, 0x2d, 0x01, 0x3f, 0x01, 0x57
	पूर्ण
पूर्ण;

अटल अंतरभूत काष्ठा s6e63j0x03 *panel_to_s6e63j0x03(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा s6e63j0x03, panel);
पूर्ण

अटल अंतरभूत sमाप_प्रकार s6e63j0x03_dcs_ग_लिखो_seq(काष्ठा s6e63j0x03 *ctx,
					स्थिर व्योम *seq, माप_प्रकार len)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	वापस mipi_dsi_dcs_ग_लिखो_buffer(dsi, seq, len);
पूर्ण

#घोषणा s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, seq...)			\
	(अणु								\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		s6e63j0x03_dcs_ग_लिखो_seq(ctx, d, ARRAY_SIZE(d));	\
	पूर्ण)

अटल अंतरभूत पूर्णांक s6e63j0x03_enable_lv2_command(काष्ठा s6e63j0x03 *ctx)
अणु
	वापस s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, MCS_LEVEL2_KEY, 0x5a, 0x5a);
पूर्ण

अटल अंतरभूत पूर्णांक s6e63j0x03_apply_mtp_key(काष्ठा s6e63j0x03 *ctx, bool on)
अणु
	अगर (on)
		वापस s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx,
				MCS_MTP_KEY, 0x5a, 0x5a);

	वापस s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, MCS_MTP_KEY, 0xa5, 0xa5);
पूर्ण

अटल पूर्णांक s6e63j0x03_घातer_on(काष्ठा s6e63j0x03 *ctx)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	msleep(30);

	gpiod_set_value(ctx->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value(ctx->reset_gpio, 0);
	usleep_range(5000, 6000);

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63j0x03_घातer_off(काष्ठा s6e63j0x03 *ctx)
अणु
	वापस regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल अचिन्हित पूर्णांक s6e63j0x03_get_brightness_index(अचिन्हित पूर्णांक brightness)
अणु
	अचिन्हित पूर्णांक index;

	index = brightness / (MAX_BRIGHTNESS / NUM_GAMMA_STEPS);

	अगर (index >= NUM_GAMMA_STEPS)
		index = NUM_GAMMA_STEPS - 1;

	वापस index;
पूर्ण

अटल पूर्णांक s6e63j0x03_update_gamma(काष्ठा s6e63j0x03 *ctx,
					अचिन्हित पूर्णांक brightness)
अणु
	काष्ठा backlight_device *bl_dev = ctx->bl_dev;
	अचिन्हित पूर्णांक index = s6e63j0x03_get_brightness_index(brightness);
	पूर्णांक ret;

	ret = s6e63j0x03_apply_mtp_key(ctx, true);
	अगर (ret < 0)
		वापस ret;

	ret = s6e63j0x03_dcs_ग_लिखो_seq(ctx, gamma_tbl[index], GAMMA_CMD_CNT);
	अगर (ret < 0)
		वापस ret;

	ret = s6e63j0x03_apply_mtp_key(ctx, false);
	अगर (ret < 0)
		वापस ret;

	bl_dev->props.brightness = brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63j0x03_set_brightness(काष्ठा backlight_device *bl_dev)
अणु
	काष्ठा s6e63j0x03 *ctx = bl_get_data(bl_dev);
	अचिन्हित पूर्णांक brightness = bl_dev->props.brightness;

	वापस s6e63j0x03_update_gamma(ctx, brightness);
पूर्ण

अटल स्थिर काष्ठा backlight_ops s6e63j0x03_bl_ops = अणु
	.update_status = s6e63j0x03_set_brightness,
पूर्ण;

अटल पूर्णांक s6e63j0x03_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63j0x03 *ctx = panel_to_s6e63j0x03(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		वापस ret;

	ctx->bl_dev->props.घातer = FB_BLANK_NORMAL;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0)
		वापस ret;

	msleep(120);

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63j0x03_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63j0x03 *ctx = panel_to_s6e63j0x03(panel);
	पूर्णांक ret;

	ret = s6e63j0x03_घातer_off(ctx);
	अगर (ret < 0)
		वापस ret;

	ctx->bl_dev->props.घातer = FB_BLANK_POWERDOWN;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63j0x03_panel_init(काष्ठा s6e63j0x03 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	ret = s6e63j0x03_enable_lv2_command(ctx);
	अगर (ret < 0)
		वापस ret;

	ret = s6e63j0x03_apply_mtp_key(ctx, true);
	अगर (ret < 0)
		वापस ret;

	/* set porch adjusपंचांगent */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xf2, 0x1c, 0x28);
	अगर (ret < 0)
		वापस ret;

	/* set frame freq */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xb5, 0x00, 0x02, 0x00);
	अगर (ret < 0)
		वापस ret;

	/* set हालt, paset */
	ret = mipi_dsi_dcs_set_column_address(dsi, FIRST_COLUMN,
		शेष_mode.hdisplay - 1 + FIRST_COLUMN);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_dsi_dcs_set_page_address(dsi, 0, शेष_mode.vdisplay - 1);
	अगर (ret < 0)
		वापस ret;

	/* set ltps timming 0, 1 */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xf8, 0x08, 0x08, 0x08, 0x17,
		0x00, 0x2a, 0x02, 0x26, 0x00, 0x00, 0x02, 0x00, 0x00);
	अगर (ret < 0)
		वापस ret;

	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xf7, 0x02);
	अगर (ret < 0)
		वापस ret;

	/* set param pos te_edge */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xb0, 0x01);
	अगर (ret < 0)
		वापस ret;

	/* set te rising edge */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xe2, 0x0f);
	अगर (ret < 0)
		वापस ret;

	/* set param pos शेष */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xb0, 0x00);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0)
		वापस ret;

	ret = s6e63j0x03_apply_mtp_key(ctx, false);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63j0x03_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63j0x03 *ctx = panel_to_s6e63j0x03(panel);
	पूर्णांक ret;

	ret = s6e63j0x03_घातer_on(ctx);
	अगर (ret < 0)
		वापस ret;

	ret = s6e63j0x03_panel_init(ctx);
	अगर (ret < 0)
		जाओ err;

	ctx->bl_dev->props.घातer = FB_BLANK_NORMAL;

	वापस 0;

err:
	s6e63j0x03_घातer_off(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक s6e63j0x03_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा s6e63j0x03 *ctx = panel_to_s6e63j0x03(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	msleep(120);

	ret = s6e63j0x03_apply_mtp_key(ctx, true);
	अगर (ret < 0)
		वापस ret;

	/* set elvss_cond */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx, 0xb1, 0x00, 0x09);
	अगर (ret < 0)
		वापस ret;

	/* set pos */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx,
		MIPI_DCS_SET_ADDRESS_MODE, 0x40);
	अगर (ret < 0)
		वापस ret;

	/* set शेष white brightness */
	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x00ff);
	अगर (ret < 0)
		वापस ret;

	/* set white ctrl */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx,
		MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x20);
	अगर (ret < 0)
		वापस ret;

	/* set acl off */
	ret = s6e63j0x03_dcs_ग_लिखो_seq_अटल(ctx,
		MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	अगर (ret < 0)
		वापस ret;

	ret = s6e63j0x03_apply_mtp_key(ctx, false);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0)
		वापस ret;

	ctx->bl_dev->props.घातer = FB_BLANK_UNBLANK;

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63j0x03_get_modes(काष्ठा drm_panel *panel,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 29;
	connector->display_info.height_mm = 29;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs s6e63j0x03_funcs = अणु
	.disable = s6e63j0x03_disable,
	.unprepare = s6e63j0x03_unprepare,
	.prepare = s6e63j0x03_prepare,
	.enable = s6e63j0x03_enable,
	.get_modes = s6e63j0x03_get_modes,
पूर्ण;

अटल पूर्णांक s6e63j0x03_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा s6e63j0x03 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(काष्ठा s6e63j0x03), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 1;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_EOT_PACKET;

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset-gpio: %ld\n",
				PTR_ERR(ctx->reset_gpio));
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	drm_panel_init(&ctx->panel, dev, &s6e63j0x03_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->bl_dev = backlight_device_रेजिस्टर("s6e63j0x03", dev, ctx,
						&s6e63j0x03_bl_ops, शून्य);
	अगर (IS_ERR(ctx->bl_dev)) अणु
		dev_err(dev, "failed to register backlight device\n");
		वापस PTR_ERR(ctx->bl_dev);
	पूर्ण

	ctx->bl_dev->props.max_brightness = MAX_BRIGHTNESS;
	ctx->bl_dev->props.brightness = DEFAULT_BRIGHTNESS;
	ctx->bl_dev->props.घातer = FB_BLANK_POWERDOWN;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0)
		जाओ हटाओ_panel;

	वापस ret;

हटाओ_panel:
	drm_panel_हटाओ(&ctx->panel);
	backlight_device_unरेजिस्टर(ctx->bl_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक s6e63j0x03_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा s6e63j0x03 *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&ctx->panel);

	backlight_device_unरेजिस्टर(ctx->bl_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id s6e63j0x03_of_match[] = अणु
	अणु .compatible = "samsung,s6e63j0x03" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s6e63j0x03_of_match);

अटल काष्ठा mipi_dsi_driver s6e63j0x03_driver = अणु
	.probe = s6e63j0x03_probe,
	.हटाओ = s6e63j0x03_हटाओ,
	.driver = अणु
		.name = "panel_samsung_s6e63j0x03",
		.of_match_table = s6e63j0x03_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(s6e63j0x03_driver);

MODULE_AUTHOR("Inki Dae <inki.dae@samsung.com>");
MODULE_AUTHOR("Hoegeun Kwon <hoegeun.kwon@samsung.com>");
MODULE_DESCRIPTION("MIPI-DSI based s6e63j0x03 AMOLED LCD Panel Driver");
MODULE_LICENSE("GPL v2");
