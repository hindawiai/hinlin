<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
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
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <video/mipi_display.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

/* Manufacturer Command Set */
#घोषणा MCS_MANPWR		0xb0
#घोषणा MCS_ELVSS_ON		0xb1
#घोषणा MCS_USER_SETTING	0xf0
#घोषणा MCS_DISPCTL		0xf2
#घोषणा MCS_POWER_CTRL		0xf4
#घोषणा MCS_GTCON		0xf7
#घोषणा MCS_PANEL_CONDITION	0xf8
#घोषणा MCS_GAMMA_SET1		0xf9
#घोषणा MCS_GAMMA_CTRL		0xfb

/* array of gamma tables क्रम gamma value 2.2 */
अटल u8 स्थिर ld9040_gammas[25][22] = अणु
	अणु 0xf9, 0x00, 0x13, 0xb2, 0xba, 0xd2, 0x00, 0x30, 0x00, 0xaf, 0xc0,
	  0xb8, 0xcd, 0x00, 0x3d, 0x00, 0xa8, 0xb8, 0xb7, 0xcd, 0x00, 0x44 पूर्ण,
	अणु 0xf9, 0x00, 0x13, 0xb9, 0xb9, 0xd0, 0x00, 0x3c, 0x00, 0xaf, 0xbf,
	  0xb6, 0xcb, 0x00, 0x4b, 0x00, 0xa8, 0xb9, 0xb5, 0xcc, 0x00, 0x52 पूर्ण,
	अणु 0xf9, 0x00, 0x13, 0xba, 0xb9, 0xcd, 0x00, 0x41, 0x00, 0xb0, 0xbe,
	  0xb5, 0xc9, 0x00, 0x51, 0x00, 0xa9, 0xb9, 0xb5, 0xca, 0x00, 0x57 पूर्ण,
	अणु 0xf9, 0x00, 0x13, 0xb9, 0xb8, 0xcd, 0x00, 0x46, 0x00, 0xb1, 0xbc,
	  0xb5, 0xc8, 0x00, 0x56, 0x00, 0xaa, 0xb8, 0xb4, 0xc9, 0x00, 0x5d पूर्ण,
	अणु 0xf9, 0x00, 0x13, 0xba, 0xb8, 0xcb, 0x00, 0x4b, 0x00, 0xb3, 0xbc,
	  0xb4, 0xc7, 0x00, 0x5c, 0x00, 0xac, 0xb8, 0xb4, 0xc8, 0x00, 0x62 पूर्ण,
	अणु 0xf9, 0x00, 0x13, 0xbb, 0xb7, 0xca, 0x00, 0x4f, 0x00, 0xb4, 0xbb,
	  0xb3, 0xc7, 0x00, 0x60, 0x00, 0xad, 0xb8, 0xb4, 0xc7, 0x00, 0x67 पूर्ण,
	अणु 0xf9, 0x00, 0x47, 0xba, 0xb6, 0xca, 0x00, 0x53, 0x00, 0xb5, 0xbb,
	  0xb3, 0xc6, 0x00, 0x65, 0x00, 0xae, 0xb8, 0xb3, 0xc7, 0x00, 0x6c पूर्ण,
	अणु 0xf9, 0x00, 0x71, 0xbb, 0xb5, 0xc8, 0x00, 0x57, 0x00, 0xb5, 0xbb,
	  0xb0, 0xc5, 0x00, 0x6a, 0x00, 0xae, 0xb9, 0xb1, 0xc6, 0x00, 0x70 पूर्ण,
	अणु 0xf9, 0x00, 0x7b, 0xbb, 0xb4, 0xc8, 0x00, 0x5b, 0x00, 0xb5, 0xba,
	  0xb1, 0xc4, 0x00, 0x6e, 0x00, 0xae, 0xb9, 0xb0, 0xc5, 0x00, 0x75 पूर्ण,
	अणु 0xf9, 0x00, 0x82, 0xba, 0xb4, 0xc7, 0x00, 0x5f, 0x00, 0xb5, 0xba,
	  0xb0, 0xc3, 0x00, 0x72, 0x00, 0xae, 0xb8, 0xb0, 0xc3, 0x00, 0x7a पूर्ण,
	अणु 0xf9, 0x00, 0x89, 0xba, 0xb3, 0xc8, 0x00, 0x62, 0x00, 0xb6, 0xba,
	  0xaf, 0xc3, 0x00, 0x76, 0x00, 0xaf, 0xb7, 0xae, 0xc4, 0x00, 0x7e पूर्ण,
	अणु 0xf9, 0x00, 0x8b, 0xb9, 0xb3, 0xc7, 0x00, 0x65, 0x00, 0xb7, 0xb8,
	  0xaf, 0xc3, 0x00, 0x7a, 0x00, 0x80, 0xb6, 0xae, 0xc4, 0x00, 0x81 पूर्ण,
	अणु 0xf9, 0x00, 0x93, 0xba, 0xb3, 0xc5, 0x00, 0x69, 0x00, 0xb8, 0xb9,
	  0xae, 0xc1, 0x00, 0x7f, 0x00, 0xb0, 0xb6, 0xae, 0xc3, 0x00, 0x85 पूर्ण,
	अणु 0xf9, 0x00, 0x97, 0xba, 0xb2, 0xc5, 0x00, 0x6c, 0x00, 0xb8, 0xb8,
	  0xae, 0xc1, 0x00, 0x82, 0x00, 0xb0, 0xb6, 0xae, 0xc2, 0x00, 0x89 पूर्ण,
	अणु 0xf9, 0x00, 0x9a, 0xba, 0xb1, 0xc4, 0x00, 0x6f, 0x00, 0xb8, 0xb8,
	  0xad, 0xc0, 0x00, 0x86, 0x00, 0xb0, 0xb7, 0xad, 0xc0, 0x00, 0x8d पूर्ण,
	अणु 0xf9, 0x00, 0x9c, 0xb9, 0xb0, 0xc4, 0x00, 0x72, 0x00, 0xb8, 0xb8,
	  0xac, 0xbf, 0x00, 0x8a, 0x00, 0xb0, 0xb6, 0xac, 0xc0, 0x00, 0x91 पूर्ण,
	अणु 0xf9, 0x00, 0x9e, 0xba, 0xb0, 0xc2, 0x00, 0x75, 0x00, 0xb9, 0xb8,
	  0xab, 0xbe, 0x00, 0x8e, 0x00, 0xb0, 0xb6, 0xac, 0xbf, 0x00, 0x94 पूर्ण,
	अणु 0xf9, 0x00, 0xa0, 0xb9, 0xaf, 0xc3, 0x00, 0x77, 0x00, 0xb9, 0xb7,
	  0xab, 0xbe, 0x00, 0x90, 0x00, 0xb0, 0xb6, 0xab, 0xbf, 0x00, 0x97 पूर्ण,
	अणु 0xf9, 0x00, 0xa2, 0xb9, 0xaf, 0xc2, 0x00, 0x7a, 0x00, 0xb9, 0xb7,
	  0xaa, 0xbd, 0x00, 0x94, 0x00, 0xb0, 0xb5, 0xab, 0xbf, 0x00, 0x9a पूर्ण,
	अणु 0xf9, 0x00, 0xa4, 0xb9, 0xaf, 0xc1, 0x00, 0x7d, 0x00, 0xb9, 0xb6,
	  0xaa, 0xbb, 0x00, 0x97, 0x00, 0xb1, 0xb5, 0xaa, 0xbf, 0x00, 0x9d पूर्ण,
	अणु 0xf9, 0x00, 0xa4, 0xb8, 0xb0, 0xbf, 0x00, 0x80, 0x00, 0xb8, 0xb6,
	  0xaa, 0xbc, 0x00, 0x9a, 0x00, 0xb0, 0xb5, 0xab, 0xbd, 0x00, 0xa0 पूर्ण,
	अणु 0xf9, 0x00, 0xa8, 0xb8, 0xae, 0xbe, 0x00, 0x84, 0x00, 0xb9, 0xb7,
	  0xa8, 0xbc, 0x00, 0x9d, 0x00, 0xb2, 0xb5, 0xaa, 0xbc, 0x00, 0xa4 पूर्ण,
	अणु 0xf9, 0x00, 0xa9, 0xb6, 0xad, 0xbf, 0x00, 0x86, 0x00, 0xb8, 0xb5,
	  0xa8, 0xbc, 0x00, 0xa0, 0x00, 0xb3, 0xb3, 0xa9, 0xbc, 0x00, 0xa7 पूर्ण,
	अणु 0xf9, 0x00, 0xa9, 0xb7, 0xae, 0xbd, 0x00, 0x89, 0x00, 0xb7, 0xb6,
	  0xa8, 0xba, 0x00, 0xa4, 0x00, 0xb1, 0xb4, 0xaa, 0xbb, 0x00, 0xaa पूर्ण,
	अणु 0xf9, 0x00, 0xa7, 0xb4, 0xae, 0xbf, 0x00, 0x91, 0x00, 0xb2, 0xb4,
	  0xaa, 0xbb, 0x00, 0xac, 0x00, 0xb3, 0xb1, 0xaa, 0xbc, 0x00, 0xb3 पूर्ण,
पूर्ण;

काष्ठा ld9040 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;

	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *reset_gpio;
	u32 घातer_on_delay;
	u32 reset_delay;
	काष्ठा videomode vm;
	u32 width_mm;
	u32 height_mm;

	पूर्णांक brightness;

	/* This field is tested by functions directly accessing bus beक्रमe
	 * transfer, transfer is skipped अगर it is set. In हाल of transfer
	 * failure or unexpected response the field is set to error value.
	 * Such स्थिरruct allows to eliminate many checks in higher level
	 * functions.
	 */
	पूर्णांक error;
पूर्ण;

अटल अंतरभूत काष्ठा ld9040 *panel_to_ld9040(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा ld9040, panel);
पूर्ण

अटल पूर्णांक ld9040_clear_error(काष्ठा ld9040 *ctx)
अणु
	पूर्णांक ret = ctx->error;

	ctx->error = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक ld9040_spi_ग_लिखो_word(काष्ठा ld9040 *ctx, u16 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(ctx->dev);
	काष्ठा spi_transfer xfer = अणु
		.len		= 2,
		.tx_buf		= &data,
	पूर्ण;
	काष्ठा spi_message msg;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	वापस spi_sync(spi, &msg);
पूर्ण

अटल व्योम ld9040_dcs_ग_लिखो(काष्ठा ld9040 *ctx, स्थिर u8 *data, माप_प्रकार len)
अणु
	पूर्णांक ret = 0;

	अगर (ctx->error < 0 || len == 0)
		वापस;

	dev_dbg(ctx->dev, "writing dcs seq: %*ph\n", (पूर्णांक)len, data);
	ret = ld9040_spi_ग_लिखो_word(ctx, *data);

	जबतक (!ret && --len) अणु
		++data;
		ret = ld9040_spi_ग_लिखो_word(ctx, *data | 0x100);
	पूर्ण

	अगर (ret) अणु
		dev_err(ctx->dev, "error %d writing dcs seq: %*ph\n", ret,
			(पूर्णांक)len, data);
		ctx->error = ret;
	पूर्ण

	usleep_range(300, 310);
पूर्ण

#घोषणा ld9040_dcs_ग_लिखो_seq_अटल(ctx, seq...) \
(अणु\
	अटल स्थिर u8 d[] = अणु seq पूर्ण;\
	ld9040_dcs_ग_लिखो(ctx, d, ARRAY_SIZE(d));\
पूर्ण)

अटल व्योम ld9040_brightness_set(काष्ठा ld9040 *ctx)
अणु
	ld9040_dcs_ग_लिखो(ctx, ld9040_gammas[ctx->brightness],
			 ARRAY_SIZE(ld9040_gammas[ctx->brightness]));

	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_GAMMA_CTRL, 0x02, 0x5a);
पूर्ण

अटल व्योम ld9040_init(काष्ठा ld9040 *ctx)
अणु
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_USER_SETTING, 0x5a, 0x5a);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_PANEL_CONDITION,
		0x05, 0x65, 0x96, 0x71, 0x7d, 0x19, 0x3b, 0x0d,
		0x19, 0x7e, 0x0d, 0xe2, 0x00, 0x00, 0x7e, 0x7d,
		0x07, 0x07, 0x20, 0x20, 0x20, 0x02, 0x02);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_DISPCTL,
		0x02, 0x08, 0x08, 0x10, 0x10);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_MANPWR, 0x04);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_POWER_CTRL,
		0x0a, 0x87, 0x25, 0x6a, 0x44, 0x02, 0x88);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_ELVSS_ON, 0x0d, 0x00, 0x16);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MCS_GTCON, 0x09, 0x00, 0x00);
	ld9040_brightness_set(ctx);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_EXIT_SLEEP_MODE);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_SET_DISPLAY_ON);
पूर्ण

अटल पूर्णांक ld9040_घातer_on(काष्ठा ld9040 *ctx)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	msleep(ctx->घातer_on_delay);
	gpiod_set_value(ctx->reset_gpio, 0);
	msleep(ctx->reset_delay);
	gpiod_set_value(ctx->reset_gpio, 1);
	msleep(ctx->reset_delay);

	वापस 0;
पूर्ण

अटल पूर्णांक ld9040_घातer_off(काष्ठा ld9040 *ctx)
अणु
	वापस regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल पूर्णांक ld9040_disable(काष्ठा drm_panel *panel)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ld9040_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ld9040 *ctx = panel_to_ld9040(panel);

	msleep(120);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_SET_DISPLAY_OFF);
	ld9040_dcs_ग_लिखो_seq_अटल(ctx, MIPI_DCS_ENTER_SLEEP_MODE);
	msleep(40);

	ld9040_clear_error(ctx);

	वापस ld9040_घातer_off(ctx);
पूर्ण

अटल पूर्णांक ld9040_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ld9040 *ctx = panel_to_ld9040(panel);
	पूर्णांक ret;

	ret = ld9040_घातer_on(ctx);
	अगर (ret < 0)
		वापस ret;

	ld9040_init(ctx);

	ret = ld9040_clear_error(ctx);

	अगर (ret < 0)
		ld9040_unprepare(panel);

	वापस ret;
पूर्ण

अटल पूर्णांक ld9040_enable(काष्ठा drm_panel *panel)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ld9040_get_modes(काष्ठा drm_panel *panel,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा ld9040 *ctx = panel_to_ld9040(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_create(connector->dev);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to create a new display mode\n");
		वापस 0;
	पूर्ण

	drm_display_mode_from_videomode(&ctx->vm, mode);
	mode->width_mm = ctx->width_mm;
	mode->height_mm = ctx->height_mm;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs ld9040_drm_funcs = अणु
	.disable = ld9040_disable,
	.unprepare = ld9040_unprepare,
	.prepare = ld9040_prepare,
	.enable = ld9040_enable,
	.get_modes = ld9040_get_modes,
पूर्ण;

अटल पूर्णांक ld9040_parse_dt(काष्ठा ld9040 *ctx)
अणु
	काष्ठा device *dev = ctx->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	ret = of_get_videomode(np, &ctx->vm, 0);
	अगर (ret < 0)
		वापस ret;

	of_property_पढ़ो_u32(np, "power-on-delay", &ctx->घातer_on_delay);
	of_property_पढ़ो_u32(np, "reset-delay", &ctx->reset_delay);
	of_property_पढ़ो_u32(np, "panel-width-mm", &ctx->width_mm);
	of_property_पढ़ो_u32(np, "panel-height-mm", &ctx->height_mm);

	वापस 0;
पूर्ण

अटल पूर्णांक ld9040_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा ld9040 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(काष्ठा ld9040), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	spi_set_drvdata(spi, ctx);

	ctx->dev = dev;
	ctx->brightness = ARRAY_SIZE(ld9040_gammas) - 1;

	ret = ld9040_parse_dt(ctx);
	अगर (ret < 0)
		वापस ret;

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(ctx->reset_gpio));
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	spi->bits_per_word = 9;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(dev, "spi setup failed.\n");
		वापस ret;
	पूर्ण

	drm_panel_init(&ctx->panel, dev, &ld9040_drm_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&ctx->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक ld9040_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ld9040 *ctx = spi_get_drvdata(spi);

	ld9040_घातer_off(ctx);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ld9040_of_match[] = अणु
	अणु .compatible = "samsung,ld9040" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ld9040_of_match);

अटल स्थिर काष्ठा spi_device_id ld9040_ids[] = अणु
	अणु "ld9040", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ld9040_ids);

अटल काष्ठा spi_driver ld9040_driver = अणु
	.probe = ld9040_probe,
	.हटाओ = ld9040_हटाओ,
	.driver = अणु
		.name = "panel-samsung-ld9040",
		.of_match_table = ld9040_of_match,
	पूर्ण,
पूर्ण;
module_spi_driver(ld9040_driver);

MODULE_AUTHOR("Andrzej Hajda <a.hajda@samsung.com>");
MODULE_DESCRIPTION("ld9040 LCD Driver");
MODULE_LICENSE("GPL v2");
