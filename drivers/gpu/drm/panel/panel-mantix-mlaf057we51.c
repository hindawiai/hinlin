<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mantix MLAF057WE51 5.7" MIPI-DSI panel driver
 *
 * Copyright (C) Purism SPC 2020
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा DRV_NAME "panel-mantix-mlaf057we51"

/* Manufacturer specअगरic Commands send via DSI */
#घोषणा MANTIX_CMD_OTP_STOP_RELOAD_MIPI 0x41
#घोषणा MANTIX_CMD_INT_CANCEL           0x4C
#घोषणा MANTIX_CMD_SPI_FINISH           0x90

काष्ठा mantix अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *tp_rstn_gpio;

	काष्ठा regulator *avdd;
	काष्ठा regulator *avee;
	काष्ठा regulator *vddi;

	स्थिर काष्ठा drm_display_mode *शेष_mode;
पूर्ण;

अटल अंतरभूत काष्ठा mantix *panel_to_mantix(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा mantix, panel);
पूर्ण

#घोषणा dsi_generic_ग_लिखो_seq(dsi, seq...) करो अणु				\
		अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
		पूर्णांक ret;						\
		ret = mipi_dsi_generic_ग_लिखो(dsi, d, ARRAY_SIZE(d));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल पूर्णांक mantix_init_sequence(काष्ठा mantix *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	काष्ठा device *dev = ctx->dev;

	/*
	 * Init sequence was supplied by the panel venकरोr.
	 */
	dsi_generic_ग_लिखो_seq(dsi, MANTIX_CMD_OTP_STOP_RELOAD_MIPI, 0x5A);

	dsi_generic_ग_लिखो_seq(dsi, MANTIX_CMD_INT_CANCEL, 0x03);
	dsi_generic_ग_लिखो_seq(dsi, MANTIX_CMD_OTP_STOP_RELOAD_MIPI, 0x5A, 0x03);
	dsi_generic_ग_लिखो_seq(dsi, 0x80, 0xA9, 0x00);

	dsi_generic_ग_लिखो_seq(dsi, MANTIX_CMD_OTP_STOP_RELOAD_MIPI, 0x5A, 0x09);
	dsi_generic_ग_लिखो_seq(dsi, 0x80, 0x64, 0x00, 0x64, 0x00, 0x00);
	msleep(20);

	dsi_generic_ग_लिखो_seq(dsi, MANTIX_CMD_SPI_FINISH, 0xA5);
	dsi_generic_ग_लिखो_seq(dsi, MANTIX_CMD_OTP_STOP_RELOAD_MIPI, 0x00, 0x2F);
	msleep(20);

	dev_dbg(dev, "Panel init sequence done\n");
	वापस 0;
पूर्ण

अटल पूर्णांक mantix_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा mantix *ctx = panel_to_mantix(panel);
	काष्ठा device *dev = ctx->dev;
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	पूर्णांक ret;

	ret = mantix_init_sequence(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Panel init sequence failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to exit sleep mode\n");
		वापस ret;
	पूर्ण
	msleep(20);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret)
		वापस ret;
	usleep_range(10000, 12000);

	ret = mipi_dsi_turn_on_peripheral(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to turn on peripheral\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mantix_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा mantix *ctx = panel_to_mantix(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		dev_err(ctx->dev, "Failed to turn off the display: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0)
		dev_err(ctx->dev, "Failed to enter sleep mode: %d\n", ret);


	वापस 0;
पूर्ण

अटल पूर्णांक mantix_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा mantix *ctx = panel_to_mantix(panel);

	gpiod_set_value_cansleep(ctx->tp_rstn_gpio, 1);
	usleep_range(5000, 6000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	regulator_disable(ctx->avee);
	regulator_disable(ctx->avdd);
	/* T11 */
	usleep_range(5000, 6000);
	regulator_disable(ctx->vddi);
	/* T14 */
	msleep(50);

	वापस 0;
पूर्ण

अटल पूर्णांक mantix_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा mantix *ctx = panel_to_mantix(panel);
	पूर्णांक ret;

	/* Focaltech FT8006P, section 7.3.1 and 7.3.4 */
	dev_dbg(ctx->dev, "Resetting the panel\n");
	ret = regulator_enable(ctx->vddi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable vddi supply: %d\n", ret);
		वापस ret;
	पूर्ण

	/* T1 + T2 */
	usleep_range(8000, 10000);

	ret = regulator_enable(ctx->avdd);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable avdd supply: %d\n", ret);
		वापस ret;
	पूर्ण

	/* T2d */
	usleep_range(3500, 4000);
	ret = regulator_enable(ctx->avee);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable avee supply: %d\n", ret);
		वापस ret;
	पूर्ण

	/* T3 + T4 + समय क्रम voltage to become stable: */
	usleep_range(6000, 7000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	gpiod_set_value_cansleep(ctx->tp_rstn_gpio, 0);

	/* T6 */
	msleep(50);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode_mantix = अणु
	.hdisplay    = 720,
	.hsync_start = 720 + 45,
	.hsync_end   = 720 + 45 + 14,
	.htotal	     = 720 + 45 + 14 + 25,
	.vdisplay    = 1440,
	.vsync_start = 1440 + 130,
	.vsync_end   = 1440 + 130 + 8,
	.vtotal	     = 1440 + 130 + 8 + 106,
	.घड़ी	     = 85298,
	.flags	     = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm    = 65,
	.height_mm   = 130,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode शेष_mode_ys = अणु
	.hdisplay    = 720,
	.hsync_start = 720 + 45,
	.hsync_end   = 720 + 45 + 14,
	.htotal	     = 720 + 45 + 14 + 25,
	.vdisplay    = 1440,
	.vsync_start = 1440 + 175,
	.vsync_end   = 1440 + 175 + 8,
	.vtotal	     = 1440 + 175 + 8 + 50,
	.घड़ी	     = 85298,
	.flags	     = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm    = 65,
	.height_mm   = 130,
पूर्ण;

अटल पूर्णांक mantix_get_modes(काष्ठा drm_panel *panel,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा mantix *ctx = panel_to_mantix(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, ctx->शेष_mode);
	अगर (!mode) अणु
		dev_err(ctx->dev, "Failed to add mode %ux%u@%u\n",
			ctx->शेष_mode->hdisplay, ctx->शेष_mode->vdisplay,
			drm_mode_vrefresh(ctx->शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs mantix_drm_funcs = अणु
	.disable   = mantix_disable,
	.unprepare = mantix_unprepare,
	.prepare   = mantix_prepare,
	.enable	   = mantix_enable,
	.get_modes = mantix_get_modes,
पूर्ण;

अटल पूर्णांक mantix_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा mantix *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->शेष_mode = of_device_get_match_data(dev);

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset gpio\n");
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	ctx->tp_rstn_gpio = devm_gpiod_get(dev, "mantix,tp-rstn", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ctx->tp_rstn_gpio)) अणु
		dev_err(dev, "cannot get tp-rstn gpio\n");
		वापस PTR_ERR(ctx->tp_rstn_gpio);
	पूर्ण

	mipi_dsi_set_drvdata(dsi, ctx);
	ctx->dev = dev;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_MODE_VIDEO_SYNC_PULSE;

	ctx->avdd = devm_regulator_get(dev, "avdd");
	अगर (IS_ERR(ctx->avdd))
		वापस dev_err_probe(dev, PTR_ERR(ctx->avdd), "Failed to request avdd regulator\n");

	ctx->avee = devm_regulator_get(dev, "avee");
	अगर (IS_ERR(ctx->avee))
		वापस dev_err_probe(dev, PTR_ERR(ctx->avee), "Failed to request avee regulator\n");

	ctx->vddi = devm_regulator_get(dev, "vddi");
	अगर (IS_ERR(ctx->vddi))
		वापस dev_err_probe(dev, PTR_ERR(ctx->vddi), "Failed to request vddi regulator\n");

	drm_panel_init(&ctx->panel, dev, &mantix_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "mipi_dsi_attach failed (%d). Is host ready?\n", ret);
		drm_panel_हटाओ(&ctx->panel);
		वापस ret;
	पूर्ण

	dev_info(dev, "%ux%u@%u %ubpp dsi %udl - ready\n",
		 ctx->शेष_mode->hdisplay, ctx->शेष_mode->vdisplay,
		 drm_mode_vrefresh(ctx->शेष_mode),
		 mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat), dsi->lanes);

	वापस 0;
पूर्ण

अटल व्योम mantix_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा mantix *ctx = mipi_dsi_get_drvdata(dsi);

	drm_panel_unprepare(&ctx->panel);
	drm_panel_disable(&ctx->panel);
पूर्ण

अटल पूर्णांक mantix_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा mantix *ctx = mipi_dsi_get_drvdata(dsi);

	mantix_shutकरोwn(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mantix_of_match[] = अणु
	अणु .compatible = "mantix,mlaf057we51-x", .data = &शेष_mode_mantix पूर्ण,
	अणु .compatible = "ys,ys57pss36bh5gq", .data = &शेष_mode_ys पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mantix_of_match);

अटल काष्ठा mipi_dsi_driver mantix_driver = अणु
	.probe	= mantix_probe,
	.हटाओ = mantix_हटाओ,
	.shutकरोwn = mantix_shutकरोwn,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = mantix_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(mantix_driver);

MODULE_AUTHOR("Guido Gथञnther <agx@sigxcpu.org>");
MODULE_DESCRIPTION("DRM driver for Mantix MLAF057WE51-X MIPI DSI panel");
MODULE_LICENSE("GPL v2");
