<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Elida kd35t133 5.5" MIPI-DSI panel driver
 * Copyright (C) 2020 Theobroma Systems Design und Consulting GmbH
 *
 * based on
 *
 * Rockteck jh057n00900 5.5" MIPI-DSI panel driver
 * Copyright (C) Purism SPC 2019
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/display_timing.h>
#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

/* Manufacturer specअगरic Commands send via DSI */
#घोषणा KD35T133_CMD_INTERFACEMODECTRL		0xb0
#घोषणा KD35T133_CMD_FRAMERATECTRL		0xb1
#घोषणा KD35T133_CMD_DISPLAYINVERSIONCTRL	0xb4
#घोषणा KD35T133_CMD_DISPLAYFUNCTIONCTRL	0xb6
#घोषणा KD35T133_CMD_POWERCONTROL1		0xc0
#घोषणा KD35T133_CMD_POWERCONTROL2		0xc1
#घोषणा KD35T133_CMD_VCOMCONTROL		0xc5
#घोषणा KD35T133_CMD_POSITIVEGAMMA		0xe0
#घोषणा KD35T133_CMD_NEGATIVEGAMMA		0xe1
#घोषणा KD35T133_CMD_SETIMAGEFUNCTION		0xe9
#घोषणा KD35T133_CMD_ADJUSTCONTROL3		0xf7

काष्ठा kd35t133 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator *vdd;
	काष्ठा regulator *iovcc;
	bool prepared;
पूर्ण;

अटल अंतरभूत काष्ठा kd35t133 *panel_to_kd35t133(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा kd35t133, panel);
पूर्ण

#घोषणा dsi_dcs_ग_लिखो_seq(dsi, cmd, seq...) करो अणु			\
		अटल स्थिर u8 b[] = अणु cmd, seq पूर्ण;			\
		पूर्णांक ret;						\
		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, b, ARRAY_SIZE(b));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल पूर्णांक kd35t133_init_sequence(काष्ठा kd35t133 *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	काष्ठा device *dev = ctx->dev;

	/*
	 * Init sequence was supplied by the panel venकरोr with minimal
	 * करोcumentation.
	 */
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_POSITIVEGAMMA,
			  0x00, 0x13, 0x18, 0x04, 0x0f, 0x06, 0x3a, 0x56,
			  0x4d, 0x03, 0x0a, 0x06, 0x30, 0x3e, 0x0f);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_NEGATIVEGAMMA,
			  0x00, 0x13, 0x18, 0x01, 0x11, 0x06, 0x38, 0x34,
			  0x4d, 0x06, 0x0d, 0x0b, 0x31, 0x37, 0x0f);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_POWERCONTROL1, 0x18, 0x17);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_POWERCONTROL2, 0x41);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_VCOMCONTROL, 0x00, 0x1a, 0x80);
	dsi_dcs_ग_लिखो_seq(dsi, MIPI_DCS_SET_ADDRESS_MODE, 0x48);
	dsi_dcs_ग_लिखो_seq(dsi, MIPI_DCS_SET_PIXEL_FORMAT, 0x55);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_INTERFACEMODECTRL, 0x00);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_FRAMERATECTRL, 0xa0);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_DISPLAYINVERSIONCTRL, 0x02);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_DISPLAYFUNCTIONCTRL,
			  0x20, 0x02);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_SETIMAGEFUNCTION, 0x00);
	dsi_dcs_ग_लिखो_seq(dsi, KD35T133_CMD_ADJUSTCONTROL3,
			  0xa9, 0x51, 0x2c, 0x82);
	mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_ENTER_INVERT_MODE, शून्य, 0);

	dev_dbg(dev, "Panel init sequence done\n");
	वापस 0;
पूर्ण

अटल पूर्णांक kd35t133_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा kd35t133 *ctx = panel_to_kd35t133(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		dev_err(ctx->dev, "failed to set display off: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to enter sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण

	regulator_disable(ctx->iovcc);
	regulator_disable(ctx->vdd);

	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक kd35t133_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा kd35t133 *ctx = panel_to_kd35t133(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	dev_dbg(ctx->dev, "Resetting the panel\n");
	ret = regulator_enable(ctx->vdd);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable vdd supply: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_enable(ctx->iovcc);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable iovcc supply: %d\n", ret);
		जाओ disable_vdd;
	पूर्ण

	msleep(20);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10, 20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);

	msleep(20);

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to exit sleep mode: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	msleep(250);

	ret = kd35t133_init_sequence(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Panel init sequence failed: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

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
disable_vdd:
	regulator_disable(ctx->vdd);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.hdisplay	= 320,
	.hsync_start	= 320 + 130,
	.hsync_end	= 320 + 130 + 4,
	.htotal		= 320 + 130 + 4 + 130,
	.vdisplay	= 480,
	.vsync_start	= 480 + 2,
	.vsync_end	= 480 + 2 + 1,
	.vtotal		= 480 + 2 + 1 + 2,
	.घड़ी		= 17000,
	.width_mm	= 42,
	.height_mm	= 82,
पूर्ण;

अटल पूर्णांक kd35t133_get_modes(काष्ठा drm_panel *panel,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा kd35t133 *ctx = panel_to_kd35t133(panel);
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

अटल स्थिर काष्ठा drm_panel_funcs kd35t133_funcs = अणु
	.unprepare	= kd35t133_unprepare,
	.prepare	= kd35t133_prepare,
	.get_modes	= kd35t133_get_modes,
पूर्ण;

अटल पूर्णांक kd35t133_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा kd35t133 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset gpio\n");
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	ctx->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(ctx->vdd)) अणु
		ret = PTR_ERR(ctx->vdd);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request vdd regulator: %d\n", ret);
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

	dsi->lanes = 1;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, &dsi->dev, &kd35t133_funcs,
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

अटल व्योम kd35t133_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा kd35t133 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_unprepare(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to unprepare panel: %d\n", ret);

	ret = drm_panel_disable(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to disable panel: %d\n", ret);
पूर्ण

अटल पूर्णांक kd35t133_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा kd35t133 *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	kd35t133_shutकरोwn(dsi);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id kd35t133_of_match[] = अणु
	अणु .compatible = "elida,kd35t133" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, kd35t133_of_match);

अटल काष्ठा mipi_dsi_driver kd35t133_driver = अणु
	.driver = अणु
		.name = "panel-elida-kd35t133",
		.of_match_table = kd35t133_of_match,
	पूर्ण,
	.probe	= kd35t133_probe,
	.हटाओ = kd35t133_हटाओ,
	.shutकरोwn = kd35t133_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(kd35t133_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko.stuebner@theobroma-systems.com>");
MODULE_DESCRIPTION("DRM driver for Elida kd35t133 MIPI DSI panel");
MODULE_LICENSE("GPL v2");
