<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xinpeng xpp055c272 5.5" MIPI-DSI panel driver
 * Copyright (C) 2019 Theobroma Systems Design und Consulting GmbH
 *
 * based on
 *
 * Rockteck jh057n00900 5.5" MIPI-DSI panel driver
 * Copyright (C) Purism SPC 2019
 */

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#समावेश <video/display_timing.h>
#समावेश <video/mipi_display.h>

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

/* Manufacturer specअगरic Commands send via DSI */
#घोषणा XPP055C272_CMD_ALL_PIXEL_OFF	0x22
#घोषणा XPP055C272_CMD_ALL_PIXEL_ON	0x23
#घोषणा XPP055C272_CMD_SETDISP		0xb2
#घोषणा XPP055C272_CMD_SETRGBIF		0xb3
#घोषणा XPP055C272_CMD_SETCYC		0xb4
#घोषणा XPP055C272_CMD_SETBGP		0xb5
#घोषणा XPP055C272_CMD_SETVCOM		0xb6
#घोषणा XPP055C272_CMD_SETOTP		0xb7
#घोषणा XPP055C272_CMD_SETPOWER_EXT	0xb8
#घोषणा XPP055C272_CMD_SETEXTC		0xb9
#घोषणा XPP055C272_CMD_SETMIPI		0xbA
#घोषणा XPP055C272_CMD_SETVDC		0xbc
#घोषणा XPP055C272_CMD_SETPCR		0xbf
#घोषणा XPP055C272_CMD_SETSCR		0xc0
#घोषणा XPP055C272_CMD_SETPOWER		0xc1
#घोषणा XPP055C272_CMD_SETECO		0xc6
#घोषणा XPP055C272_CMD_SETPANEL		0xcc
#घोषणा XPP055C272_CMD_SETGAMMA		0xe0
#घोषणा XPP055C272_CMD_SETEQ		0xe3
#घोषणा XPP055C272_CMD_SETGIP1		0xe9
#घोषणा XPP055C272_CMD_SETGIP2		0xea

काष्ठा xpp055c272 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator *vci;
	काष्ठा regulator *iovcc;
	bool prepared;
पूर्ण;

अटल अंतरभूत काष्ठा xpp055c272 *panel_to_xpp055c272(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा xpp055c272, panel);
पूर्ण

#घोषणा dsi_generic_ग_लिखो_seq(dsi, cmd, seq...) करो अणु			\
		अटल स्थिर u8 b[] = अणु cmd, seq पूर्ण;			\
		पूर्णांक ret;						\
		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, b, ARRAY_SIZE(b));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल पूर्णांक xpp055c272_init_sequence(काष्ठा xpp055c272 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	काष्ठा device *dev = ctx->dev;

	/*
	 * Init sequence was supplied by the panel venकरोr without much
	 * करोcumentation.
	 */
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETEXTC, 0xf1, 0x12, 0x83);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETMIPI,
			      0x33, 0x81, 0x05, 0xf9, 0x0e, 0x0e, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x25,
			      0x00, 0x91, 0x0a, 0x00, 0x00, 0x02, 0x4f, 0x01,
			      0x00, 0x00, 0x37);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETPOWER_EXT, 0x25);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETPCR, 0x02, 0x11, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETRGBIF,
			      0x0c, 0x10, 0x0a, 0x50, 0x03, 0xff, 0x00, 0x00,
			      0x00, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETSCR,
			      0x73, 0x73, 0x50, 0x50, 0x00, 0x00, 0x08, 0x70,
			      0x00);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETVDC, 0x46);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETPANEL, 0x0b);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETCYC, 0x80);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETDISP, 0xc8, 0x12, 0x30);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETEQ,
			      0x07, 0x07, 0x0B, 0x0B, 0x03, 0x0B, 0x00, 0x00,
			      0x00, 0x00, 0xFF, 0x00, 0xC0, 0x10);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETPOWER,
			      0x53, 0x00, 0x1e, 0x1e, 0x77, 0xe1, 0xcc, 0xdd,
			      0x67, 0x77, 0x33, 0x33);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETECO, 0x00, 0x00, 0xff,
			      0xff, 0x01, 0xff);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETBGP, 0x09, 0x09);
	msleep(20);

	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETVCOM, 0x87, 0x95);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETGIP1,
			      0xc2, 0x10, 0x05, 0x05, 0x10, 0x05, 0xa0, 0x12,
			      0x31, 0x23, 0x3f, 0x81, 0x0a, 0xa0, 0x37, 0x18,
			      0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80,
			      0x01, 0x00, 0x00, 0x00, 0x48, 0xf8, 0x86, 0x42,
			      0x08, 0x88, 0x88, 0x80, 0x88, 0x88, 0x88, 0x58,
			      0xf8, 0x87, 0x53, 0x18, 0x88, 0x88, 0x81, 0x88,
			      0x88, 0x88, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETGIP2,
			      0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x1f, 0x88, 0x81, 0x35,
			      0x78, 0x88, 0x88, 0x85, 0x88, 0x88, 0x88, 0x0f,
			      0x88, 0x80, 0x24, 0x68, 0x88, 0x88, 0x84, 0x88,
			      0x88, 0x88, 0x23, 0x10, 0x00, 0x00, 0x1c, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x05,
			      0xa0, 0x00, 0x00, 0x00, 0x00);
	dsi_generic_ग_लिखो_seq(dsi, XPP055C272_CMD_SETGAMMA,
			      0x00, 0x06, 0x08, 0x2a, 0x31, 0x3f, 0x38, 0x36,
			      0x07, 0x0c, 0x0d, 0x11, 0x13, 0x12, 0x13, 0x11,
			      0x18, 0x00, 0x06, 0x08, 0x2a, 0x31, 0x3f, 0x38,
			      0x36, 0x07, 0x0c, 0x0d, 0x11, 0x13, 0x12, 0x13,
			      0x11, 0x18);

	msleep(60);

	dev_dbg(dev, "Panel init sequence done\n");
	वापस 0;
पूर्ण

अटल पूर्णांक xpp055c272_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा xpp055c272 *ctx = panel_to_xpp055c272(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		dev_err(ctx->dev, "failed to set display off: %d\n", ret);

	mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to enter sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण

	regulator_disable(ctx->iovcc);
	regulator_disable(ctx->vci);

	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक xpp055c272_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा xpp055c272 *ctx = panel_to_xpp055c272(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	dev_dbg(ctx->dev, "Resetting the panel\n");
	ret = regulator_enable(ctx->vci);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable vci supply: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regulator_enable(ctx->iovcc);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable iovcc supply: %d\n", ret);
		जाओ disable_vci;
	पूर्ण

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	/* T6: 10us */
	usleep_range(10, 20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);

	/* T8: 20ms */
	msleep(20);

	ret = xpp055c272_init_sequence(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Panel init sequence failed: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to exit sleep mode: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	/* T9: 120ms */
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to set display on: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	msleep(50);

	ctx->prepared = true;

	वापस 0;

disable_iovcc:
	regulator_disable(ctx->iovcc);
disable_vci:
	regulator_disable(ctx->vci);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.hdisplay	= 720,
	.hsync_start	= 720 + 40,
	.hsync_end	= 720 + 40 + 10,
	.htotal		= 720 + 40 + 10 + 40,
	.vdisplay	= 1280,
	.vsync_start	= 1280 + 22,
	.vsync_end	= 1280 + 22 + 4,
	.vtotal		= 1280 + 22 + 4 + 11,
	.घड़ी		= 64000,
	.width_mm	= 68,
	.height_mm	= 121,
पूर्ण;

अटल पूर्णांक xpp055c272_get_modes(काष्ठा drm_panel *panel,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा xpp055c272 *ctx = panel_to_xpp055c272(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(ctx->dev, "Failed to add mode %ux%u@%u\n",
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

अटल स्थिर काष्ठा drm_panel_funcs xpp055c272_funcs = अणु
	.unprepare	= xpp055c272_unprepare,
	.prepare	= xpp055c272_prepare,
	.get_modes	= xpp055c272_get_modes,
पूर्ण;

अटल पूर्णांक xpp055c272_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा xpp055c272 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset gpio\n");
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	ctx->vci = devm_regulator_get(dev, "vci");
	अगर (IS_ERR(ctx->vci)) अणु
		ret = PTR_ERR(ctx->vci);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request vci regulator: %d\n", ret);
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

	drm_panel_init(&ctx->panel, &dsi->dev, &xpp055c272_funcs,
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

अटल व्योम xpp055c272_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा xpp055c272 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_unprepare(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to unprepare panel: %d\n", ret);

	ret = drm_panel_disable(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to disable panel: %d\n", ret);
पूर्ण

अटल पूर्णांक xpp055c272_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा xpp055c272 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	xpp055c272_shutकरोwn(dsi);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xpp055c272_of_match[] = अणु
	अणु .compatible = "xinpeng,xpp055c272" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xpp055c272_of_match);

अटल काष्ठा mipi_dsi_driver xpp055c272_driver = अणु
	.driver = अणु
		.name = "panel-xinpeng-xpp055c272",
		.of_match_table = xpp055c272_of_match,
	पूर्ण,
	.probe	= xpp055c272_probe,
	.हटाओ = xpp055c272_हटाओ,
	.shutकरोwn = xpp055c272_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(xpp055c272_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko.stuebner@theobroma-systems.com>");
MODULE_DESCRIPTION("DRM driver for Xinpeng xpp055c272 MIPI DSI panel");
MODULE_LICENSE("GPL v2");
