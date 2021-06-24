<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
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

#घोषणा OTM8009A_BACKLIGHT_DEFAULT	240
#घोषणा OTM8009A_BACKLIGHT_MAX		255

/* Manufacturer Command Set */
#घोषणा MCS_ADRSFT	0x0000	/* Address Shअगरt Function */
#घोषणा MCS_PANSET	0xB3A6	/* Panel Type Setting */
#घोषणा MCS_SD_CTRL	0xC0A2	/* Source Driver Timing Setting */
#घोषणा MCS_P_DRV_M	0xC0B4	/* Panel Driving Mode */
#घोषणा MCS_OSC_ADJ	0xC181	/* Oscillator Adjusपंचांगent क्रम Idle/Normal mode */
#घोषणा MCS_RGB_VID_SET	0xC1A1	/* RGB Video Mode Setting */
#घोषणा MCS_SD_PCH_CTRL	0xC480	/* Source Driver Preअक्षरge Control */
#घोषणा MCS_NO_DOC1	0xC48A	/* Command not करोcumented */
#घोषणा MCS_PWR_CTRL1	0xC580	/* Power Control Setting 1 */
#घोषणा MCS_PWR_CTRL2	0xC590	/* Power Control Setting 2 क्रम Normal Mode */
#घोषणा MCS_PWR_CTRL4	0xC5B0	/* Power Control Setting 4 क्रम DC Voltage */
#घोषणा MCS_PANCTRLSET1	0xCB80	/* Panel Control Setting 1 */
#घोषणा MCS_PANCTRLSET2	0xCB90	/* Panel Control Setting 2 */
#घोषणा MCS_PANCTRLSET3	0xCBA0	/* Panel Control Setting 3 */
#घोषणा MCS_PANCTRLSET4	0xCBB0	/* Panel Control Setting 4 */
#घोषणा MCS_PANCTRLSET5	0xCBC0	/* Panel Control Setting 5 */
#घोषणा MCS_PANCTRLSET6	0xCBD0	/* Panel Control Setting 6 */
#घोषणा MCS_PANCTRLSET7	0xCBE0	/* Panel Control Setting 7 */
#घोषणा MCS_PANCTRLSET8	0xCBF0	/* Panel Control Setting 8 */
#घोषणा MCS_PANU2D1	0xCC80	/* Panel U2D Setting 1 */
#घोषणा MCS_PANU2D2	0xCC90	/* Panel U2D Setting 2 */
#घोषणा MCS_PANU2D3	0xCCA0	/* Panel U2D Setting 3 */
#घोषणा MCS_PAND2U1	0xCCB0	/* Panel D2U Setting 1 */
#घोषणा MCS_PAND2U2	0xCCC0	/* Panel D2U Setting 2 */
#घोषणा MCS_PAND2U3	0xCCD0	/* Panel D2U Setting 3 */
#घोषणा MCS_GOAVST	0xCE80	/* GOA VST Setting */
#घोषणा MCS_GOACLKA1	0xCEA0	/* GOA CLKA1 Setting */
#घोषणा MCS_GOACLKA3	0xCEB0	/* GOA CLKA3 Setting */
#घोषणा MCS_GOAECLK	0xCFC0	/* GOA ECLK Setting */
#घोषणा MCS_NO_DOC2	0xCFD0	/* Command not करोcumented */
#घोषणा MCS_GVDDSET	0xD800	/* GVDD/NGVDD */
#घोषणा MCS_VCOMDC	0xD900	/* VCOM Voltage Setting */
#घोषणा MCS_GMCT2_2P	0xE100	/* Gamma Correction 2.2+ Setting */
#घोषणा MCS_GMCT2_2N	0xE200	/* Gamma Correction 2.2- Setting */
#घोषणा MCS_NO_DOC3	0xF5B6	/* Command not करोcumented */
#घोषणा MCS_CMD2_ENA1	0xFF00	/* Enable Access Command2 "CMD2" */
#घोषणा MCS_CMD2_ENA2	0xFF80	/* Enable Access Orise Command2 */

काष्ठा oपंचांग8009a अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा backlight_device *bl_dev;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator *supply;
	bool prepared;
	bool enabled;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 29700,
	.hdisplay = 480,
	.hsync_start = 480 + 98,
	.hsync_end = 480 + 98 + 32,
	.htotal = 480 + 98 + 32 + 98,
	.vdisplay = 800,
	.vsync_start = 800 + 15,
	.vsync_end = 800 + 15 + 10,
	.vtotal = 800 + 15 + 10 + 14,
	.flags = 0,
	.width_mm = 52,
	.height_mm = 86,
पूर्ण;

अटल अंतरभूत काष्ठा oपंचांग8009a *panel_to_oपंचांग8009a(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा oपंचांग8009a, panel);
पूर्ण

अटल व्योम oपंचांग8009a_dcs_ग_लिखो_buf(काष्ठा oपंचांग8009a *ctx, स्थिर व्योम *data,
				   माप_प्रकार len)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	अगर (mipi_dsi_dcs_ग_लिखो_buffer(dsi, data, len) < 0)
		dev_warn(ctx->dev, "mipi dsi dcs write buffer failed\n");
पूर्ण

#घोषणा dcs_ग_लिखो_seq(ctx, seq...)			\
(अणु							\
	अटल स्थिर u8 d[] = अणु seq पूर्ण;			\
	oपंचांग8009a_dcs_ग_लिखो_buf(ctx, d, ARRAY_SIZE(d));	\
पूर्ण)

#घोषणा dcs_ग_लिखो_cmd_at(ctx, cmd, seq...)		\
(अणु							\
	dcs_ग_लिखो_seq(ctx, MCS_ADRSFT, (cmd) & 0xFF);	\
	dcs_ग_लिखो_seq(ctx, (cmd) >> 8, seq);		\
पूर्ण)

अटल पूर्णांक oपंचांग8009a_init_sequence(काष्ठा oपंचांग8009a *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	/* Enter CMD2 */
	dcs_ग_लिखो_cmd_at(ctx, MCS_CMD2_ENA1, 0x80, 0x09, 0x01);

	/* Enter Orise Command2 */
	dcs_ग_लिखो_cmd_at(ctx, MCS_CMD2_ENA2, 0x80, 0x09);

	dcs_ग_लिखो_cmd_at(ctx, MCS_SD_PCH_CTRL, 0x30);
	mdelay(10);

	dcs_ग_लिखो_cmd_at(ctx, MCS_NO_DOC1, 0x40);
	mdelay(10);

	dcs_ग_लिखो_cmd_at(ctx, MCS_PWR_CTRL4 + 1, 0xA9);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PWR_CTRL2 + 1, 0x34);
	dcs_ग_लिखो_cmd_at(ctx, MCS_P_DRV_M, 0x50);
	dcs_ग_लिखो_cmd_at(ctx, MCS_VCOMDC, 0x4E);
	dcs_ग_लिखो_cmd_at(ctx, MCS_OSC_ADJ, 0x66); /* 65Hz */
	dcs_ग_लिखो_cmd_at(ctx, MCS_PWR_CTRL2 + 2, 0x01);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PWR_CTRL2 + 5, 0x34);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PWR_CTRL2 + 4, 0x33);
	dcs_ग_लिखो_cmd_at(ctx, MCS_GVDDSET, 0x79, 0x79);
	dcs_ग_लिखो_cmd_at(ctx, MCS_SD_CTRL + 1, 0x1B);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PWR_CTRL1 + 2, 0x83);
	dcs_ग_लिखो_cmd_at(ctx, MCS_SD_PCH_CTRL + 1, 0x83);
	dcs_ग_लिखो_cmd_at(ctx, MCS_RGB_VID_SET, 0x0E);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANSET, 0x00, 0x01);

	dcs_ग_लिखो_cmd_at(ctx, MCS_GOAVST, 0x85, 0x01, 0x00, 0x84, 0x01, 0x00);
	dcs_ग_लिखो_cmd_at(ctx, MCS_GOACLKA1, 0x18, 0x04, 0x03, 0x39, 0x00, 0x00,
			 0x00, 0x18, 0x03, 0x03, 0x3A, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_cmd_at(ctx, MCS_GOACLKA3, 0x18, 0x02, 0x03, 0x3B, 0x00, 0x00,
			 0x00, 0x18, 0x01, 0x03, 0x3C, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_cmd_at(ctx, MCS_GOAECLK, 0x01, 0x01, 0x20, 0x20, 0x00, 0x00,
			 0x01, 0x02, 0x00, 0x00);

	dcs_ग_लिखो_cmd_at(ctx, MCS_NO_DOC2, 0x00);

	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			 0, 0, 0, 0, 0);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			 0, 0, 0, 0, 0);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET5, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0,
			 0, 0, 0, 0, 0);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET6, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4,
			 4, 0, 0, 0, 0);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANCTRLSET8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);

	dcs_ग_लिखो_cmd_at(ctx, MCS_PANU2D1, 0x00, 0x26, 0x09, 0x0B, 0x01, 0x25,
			 0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANU2D2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x0A, 0x0C, 0x02);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PANU2D3, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PAND2U1, 0x00, 0x25, 0x0C, 0x0A, 0x02, 0x26,
			 0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PAND2U2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x0B, 0x09, 0x01);
	dcs_ग_लिखो_cmd_at(ctx, MCS_PAND2U3, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

	dcs_ग_लिखो_cmd_at(ctx, MCS_PWR_CTRL1 + 1, 0x66);

	dcs_ग_लिखो_cmd_at(ctx, MCS_NO_DOC3, 0x06);

	dcs_ग_लिखो_cmd_at(ctx, MCS_GMCT2_2P, 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10,
			 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A,
			 0x01);
	dcs_ग_लिखो_cmd_at(ctx, MCS_GMCT2_2N, 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10,
			 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A,
			 0x01);

	/* Exit CMD2 */
	dcs_ग_लिखो_cmd_at(ctx, MCS_CMD2_ENA1, 0xFF, 0xFF, 0xFF);

	ret = mipi_dsi_dcs_nop(dsi);
	अगर (ret)
		वापस ret;

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret)
		वापस ret;

	/* Wait क्रम sleep out निकास */
	mdelay(120);

	/* Default portrait 480x800 rgb24 */
	dcs_ग_लिखो_seq(ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x00);

	ret = mipi_dsi_dcs_set_column_address(dsi, 0,
					      शेष_mode.hdisplay - 1);
	अगर (ret)
		वापस ret;

	ret = mipi_dsi_dcs_set_page_address(dsi, 0, शेष_mode.vdisplay - 1);
	अगर (ret)
		वापस ret;

	/* See oपंचांग8009a driver करोcumentation क्रम pixel क्रमmat descriptions */
	ret = mipi_dsi_dcs_set_pixel_क्रमmat(dsi, MIPI_DCS_PIXEL_FMT_24BIT |
					    MIPI_DCS_PIXEL_FMT_24BIT << 4);
	अगर (ret)
		वापस ret;

	/* Disable CABC feature */
	dcs_ग_लिखो_seq(ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x00);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret)
		वापस ret;

	ret = mipi_dsi_dcs_nop(dsi);
	अगर (ret)
		वापस ret;

	/* Send Command GRAM memory ग_लिखो (no parameters) */
	dcs_ग_लिखो_seq(ctx, MIPI_DCS_WRITE_MEMORY_START);

	/* Wait a लघु जबतक to let the panel be पढ़ोy beक्रमe the 1st frame */
	mdelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक oपंचांग8009a_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा oपंचांग8009a *ctx = panel_to_oपंचांग8009a(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (!ctx->enabled)
		वापस 0; /* This is not an issue so we वापस 0 here */

	backlight_disable(ctx->bl_dev);

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret)
		वापस ret;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret)
		वापस ret;

	msleep(120);

	ctx->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक oपंचांग8009a_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा oपंचांग8009a *ctx = panel_to_oपंचांग8009a(panel);

	अगर (!ctx->prepared)
		वापस 0;

	अगर (ctx->reset_gpio) अणु
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		msleep(20);
	पूर्ण

	regulator_disable(ctx->supply);

	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक oपंचांग8009a_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा oपंचांग8009a *ctx = panel_to_oपंचांग8009a(panel);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = regulator_enable(ctx->supply);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to enable supply: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ctx->reset_gpio) अणु
		gpiod_set_value_cansleep(ctx->reset_gpio, 0);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		msleep(20);
		gpiod_set_value_cansleep(ctx->reset_gpio, 0);
		msleep(100);
	पूर्ण

	ret = oपंचांग8009a_init_sequence(ctx);
	अगर (ret)
		वापस ret;

	ctx->prepared = true;

	वापस 0;
पूर्ण

अटल पूर्णांक oपंचांग8009a_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा oपंचांग8009a *ctx = panel_to_oपंचांग8009a(panel);

	अगर (ctx->enabled)
		वापस 0;

	backlight_enable(ctx->bl_dev);

	ctx->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक oपंचांग8009a_get_modes(काष्ठा drm_panel *panel,
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

	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs oपंचांग8009a_drm_funcs = अणु
	.disable   = oपंचांग8009a_disable,
	.unprepare = oपंचांग8009a_unprepare,
	.prepare   = oपंचांग8009a_prepare,
	.enable    = oपंचांग8009a_enable,
	.get_modes = oपंचांग8009a_get_modes,
पूर्ण;

/*
 * DSI-BASED BACKLIGHT
 */

अटल पूर्णांक oपंचांग8009a_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा oपंचांग8009a *ctx = bl_get_data(bd);
	u8 data[2];

	अगर (!ctx->prepared) अणु
		dev_dbg(&bd->dev, "lcd not ready yet for setting its backlight!\n");
		वापस -ENXIO;
	पूर्ण

	अगर (bd->props.घातer <= FB_BLANK_NORMAL) अणु
		/* Power on the backlight with the requested brightness
		 * Note We can not use mipi_dsi_dcs_set_display_brightness()
		 * as oपंचांग8009a driver support only 8-bit brightness (1 param).
		 */
		data[0] = MIPI_DCS_SET_DISPLAY_BRIGHTNESS;
		data[1] = bd->props.brightness;
		oपंचांग8009a_dcs_ग_लिखो_buf(ctx, data, ARRAY_SIZE(data));

		/* set Brightness Control & Backlight on */
		data[1] = 0x24;

	पूर्ण अन्यथा अणु
		/* Power off the backlight: set Brightness Control & Bl off */
		data[1] = 0;
	पूर्ण

	/* Update Brightness Control & Backlight */
	data[0] = MIPI_DCS_WRITE_CONTROL_DISPLAY;
	oपंचांग8009a_dcs_ग_लिखो_buf(ctx, data, ARRAY_SIZE(data));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops oपंचांग8009a_backlight_ops = अणु
	.update_status = oपंचांग8009a_backlight_update_status,
पूर्ण;

अटल पूर्णांक oपंचांग8009a_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा oपंचांग8009a *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset-gpio\n");
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	ctx->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(ctx->supply)) अणु
		ret = PTR_ERR(ctx->supply);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM | MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &oपंचांग8009a_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->bl_dev = devm_backlight_device_रेजिस्टर(dev, dev_name(dev),
						     dsi->host->dev, ctx,
						     &oपंचांग8009a_backlight_ops,
						     शून्य);
	अगर (IS_ERR(ctx->bl_dev)) अणु
		ret = PTR_ERR(ctx->bl_dev);
		dev_err(dev, "failed to register backlight: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->bl_dev->props.max_brightness = OTM8009A_BACKLIGHT_MAX;
	ctx->bl_dev->props.brightness = OTM8009A_BACKLIGHT_DEFAULT;
	ctx->bl_dev->props.घातer = FB_BLANK_POWERDOWN;
	ctx->bl_dev->props.type = BACKLIGHT_RAW;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "mipi_dsi_attach failed. Is host ready?\n");
		drm_panel_हटाओ(&ctx->panel);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक oपंचांग8009a_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा oपंचांग8009a *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id orisetech_oपंचांग8009a_of_match[] = अणु
	अणु .compatible = "orisetech,otm8009a" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, orisetech_oपंचांग8009a_of_match);

अटल काष्ठा mipi_dsi_driver orisetech_oपंचांग8009a_driver = अणु
	.probe  = oपंचांग8009a_probe,
	.हटाओ = oपंचांग8009a_हटाओ,
	.driver = अणु
		.name = "panel-orisetech-otm8009a",
		.of_match_table = orisetech_oपंचांग8009a_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(orisetech_oपंचांग8009a_driver);

MODULE_AUTHOR("Philippe Cornu <philippe.cornu@st.com>");
MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_DESCRIPTION("DRM driver for Orise Tech OTM8009A MIPI DSI panel");
MODULE_LICENSE("GPL v2");
