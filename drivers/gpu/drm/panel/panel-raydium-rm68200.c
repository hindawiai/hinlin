<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

/*** Manufacturer Command Set ***/
#घोषणा MCS_CMD_MODE_SW		0xFE /* CMD Mode Switch */
#घोषणा MCS_CMD1_UCS		0x00 /* User Command Set (UCS = CMD1) */
#घोषणा MCS_CMD2_P0		0x01 /* Manufacture Command Set Page0 (CMD2 P0) */
#घोषणा MCS_CMD2_P1		0x02 /* Manufacture Command Set Page1 (CMD2 P1) */
#घोषणा MCS_CMD2_P2		0x03 /* Manufacture Command Set Page2 (CMD2 P2) */
#घोषणा MCS_CMD2_P3		0x04 /* Manufacture Command Set Page3 (CMD2 P3) */

/* CMD2 P0 commands (Display Options and Power) */
#घोषणा MCS_STBCTR		0x12 /* TE1 Output Setting Zig-Zag Connection */
#घोषणा MCS_SGOPCTR		0x16 /* Source Bias Current */
#घोषणा MCS_SDCTR		0x1A /* Source Output Delay Time */
#घोषणा MCS_INVCTR		0x1B /* Inversion Type */
#घोषणा MCS_EXT_PWR_IC		0x24 /* External PWR IC Control */
#घोषणा MCS_SETAVDD		0x27 /* PFM Control क्रम AVDD Output */
#घोषणा MCS_SETAVEE		0x29 /* PFM Control क्रम AVEE Output */
#घोषणा MCS_BT2CTR		0x2B /* DDVDL Charge Pump Control */
#घोषणा MCS_BT3CTR		0x2F /* VGH Charge Pump Control */
#घोषणा MCS_BT4CTR		0x34 /* VGL Charge Pump Control */
#घोषणा MCS_VCMCTR		0x46 /* VCOM Output Level Control */
#घोषणा MCS_SETVGN		0x52 /* VG M/S N Control */
#घोषणा MCS_SETVGP		0x54 /* VG M/S P Control */
#घोषणा MCS_SW_CTRL		0x5F /* Interface Control क्रम PFM and MIPI */

/* CMD2 P2 commands (GOA Timing Control) - no description in datasheet */
#घोषणा GOA_VSTV1		0x00
#घोषणा GOA_VSTV2		0x07
#घोषणा GOA_VCLK1		0x0E
#घोषणा GOA_VCLK2		0x17
#घोषणा GOA_VCLK_OPT1		0x20
#घोषणा GOA_BICLK1		0x2A
#घोषणा GOA_BICLK2		0x37
#घोषणा GOA_BICLK3		0x44
#घोषणा GOA_BICLK4		0x4F
#घोषणा GOA_BICLK_OPT1		0x5B
#घोषणा GOA_BICLK_OPT2		0x60
#घोषणा MCS_GOA_GPO1		0x6D
#घोषणा MCS_GOA_GPO2		0x71
#घोषणा MCS_GOA_EQ		0x74
#घोषणा MCS_GOA_CLK_GALLON	0x7C
#घोषणा MCS_GOA_FS_SEL0		0x7E
#घोषणा MCS_GOA_FS_SEL1		0x87
#घोषणा MCS_GOA_FS_SEL2		0x91
#घोषणा MCS_GOA_FS_SEL3		0x9B
#घोषणा MCS_GOA_BS_SEL0		0xAC
#घोषणा MCS_GOA_BS_SEL1		0xB5
#घोषणा MCS_GOA_BS_SEL2		0xBF
#घोषणा MCS_GOA_BS_SEL3		0xC9
#घोषणा MCS_GOA_BS_SEL4		0xD3

/* CMD2 P3 commands (Gamma) */
#घोषणा MCS_GAMMA_VP		0x60 /* Gamma VP1~VP16 */
#घोषणा MCS_GAMMA_VN		0x70 /* Gamma VN1~VN16 */

काष्ठा rm68200 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator *supply;
	bool prepared;
	bool enabled;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 54000,
	.hdisplay = 720,
	.hsync_start = 720 + 48,
	.hsync_end = 720 + 48 + 9,
	.htotal = 720 + 48 + 9 + 48,
	.vdisplay = 1280,
	.vsync_start = 1280 + 12,
	.vsync_end = 1280 + 12 + 5,
	.vtotal = 1280 + 12 + 5 + 12,
	.flags = 0,
	.width_mm = 68,
	.height_mm = 122,
पूर्ण;

अटल अंतरभूत काष्ठा rm68200 *panel_to_rm68200(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा rm68200, panel);
पूर्ण

अटल व्योम rm68200_dcs_ग_लिखो_buf(काष्ठा rm68200 *ctx, स्थिर व्योम *data,
				  माप_प्रकार len)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक err;

	err = mipi_dsi_dcs_ग_लिखो_buffer(dsi, data, len);
	अगर (err < 0)
		dev_err_ratelimited(ctx->dev, "MIPI DSI DCS write buffer failed: %d\n", err);
पूर्ण

अटल व्योम rm68200_dcs_ग_लिखो_cmd(काष्ठा rm68200 *ctx, u8 cmd, u8 value)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, cmd, &value, 1);
	अगर (err < 0)
		dev_err_ratelimited(ctx->dev, "MIPI DSI DCS write failed: %d\n", err);
पूर्ण

#घोषणा dcs_ग_लिखो_seq(ctx, seq...)				\
(अणु								\
	अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
								\
	rm68200_dcs_ग_लिखो_buf(ctx, d, ARRAY_SIZE(d));		\
पूर्ण)

/*
 * This panel is not able to स्वतः-increment all cmd addresses so क्रम some of
 * them, we need to send them one by one...
 */
#घोषणा dcs_ग_लिखो_cmd_seq(ctx, cmd, seq...)			\
(अणु								\
	अटल स्थिर u8 d[] = अणु seq पूर्ण;				\
	अचिन्हित पूर्णांक i;						\
								\
	क्रम (i = 0; i < ARRAY_SIZE(d) ; i++)			\
		rm68200_dcs_ग_लिखो_cmd(ctx, cmd + i, d[i]);	\
पूर्ण)

अटल व्योम rm68200_init_sequence(काष्ठा rm68200 *ctx)
अणु
	/* Enter CMD2 with page 0 */
	dcs_ग_लिखो_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P0);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_EXT_PWR_IC, 0xC0, 0x53, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_BT2CTR, 0xE5);
	dcs_ग_लिखो_seq(ctx, MCS_SETAVDD, 0x0A);
	dcs_ग_लिखो_seq(ctx, MCS_SETAVEE, 0x0A);
	dcs_ग_लिखो_seq(ctx, MCS_SGOPCTR, 0x52);
	dcs_ग_लिखो_seq(ctx, MCS_BT3CTR, 0x53);
	dcs_ग_लिखो_seq(ctx, MCS_BT4CTR, 0x5A);
	dcs_ग_लिखो_seq(ctx, MCS_INVCTR, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_STBCTR, 0x0A);
	dcs_ग_लिखो_seq(ctx, MCS_SDCTR, 0x06);
	dcs_ग_लिखो_seq(ctx, MCS_VCMCTR, 0x56);
	dcs_ग_लिखो_seq(ctx, MCS_SETVGN, 0xA0, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_SETVGP, 0xA0, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_SW_CTRL, 0x11); /* 2 data lanes, see करोc */

	dcs_ग_लिखो_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P2);
	dcs_ग_लिखो_seq(ctx, GOA_VSTV1, 0x05);
	dcs_ग_लिखो_seq(ctx, 0x02, 0x0B);
	dcs_ग_लिखो_seq(ctx, 0x03, 0x0F);
	dcs_ग_लिखो_seq(ctx, 0x04, 0x7D, 0x00, 0x50);
	dcs_ग_लिखो_cmd_seq(ctx, GOA_VSTV2, 0x05, 0x16, 0x0D, 0x11, 0x7D, 0x00,
			  0x50);
	dcs_ग_लिखो_cmd_seq(ctx, GOA_VCLK1, 0x07, 0x08, 0x01, 0x02, 0x00, 0x7D,
			  0x00, 0x85, 0x08);
	dcs_ग_लिखो_cmd_seq(ctx, GOA_VCLK2, 0x03, 0x04, 0x05, 0x06, 0x00, 0x7D,
			  0x00, 0x85, 0x08);
	dcs_ग_लिखो_seq(ctx, GOA_VCLK_OPT1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_cmd_seq(ctx, GOA_BICLK1, 0x07, 0x08);
	dcs_ग_लिखो_seq(ctx, 0x2D, 0x01);
	dcs_ग_लिखो_seq(ctx, 0x2F, 0x02, 0x00, 0x40, 0x05, 0x08, 0x54, 0x7D,
		      0x00);
	dcs_ग_लिखो_cmd_seq(ctx, GOA_BICLK2, 0x03, 0x04, 0x05, 0x06, 0x00);
	dcs_ग_लिखो_seq(ctx, 0x3D, 0x40);
	dcs_ग_लिखो_seq(ctx, 0x3F, 0x05, 0x08, 0x54, 0x7D, 0x00);
	dcs_ग_लिखो_seq(ctx, GOA_BICLK3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_seq(ctx, GOA_BICLK4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00);
	dcs_ग_लिखो_seq(ctx, 0x58, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_seq(ctx, GOA_BICLK_OPT1, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_seq(ctx, GOA_BICLK_OPT2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_GOA_GPO1, 0x00, 0x00, 0x00, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_GOA_GPO2, 0x00, 0x20, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_GOA_EQ, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
		      0x00, 0x00);
	dcs_ग_लिखो_seq(ctx, MCS_GOA_CLK_GALLON, 0x00, 0x00);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_FS_SEL0, 0xBF, 0x02, 0x06, 0x14, 0x10,
			  0x16, 0x12, 0x08, 0x3F);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_FS_SEL1, 0x3F, 0x3F, 0x3F, 0x3F, 0x0C,
			  0x0A, 0x0E, 0x3F, 0x3F, 0x00);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_FS_SEL2, 0x04, 0x3F, 0x3F, 0x3F, 0x3F,
			  0x05, 0x01, 0x3F, 0x3F, 0x0F);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_FS_SEL3, 0x0B, 0x0D, 0x3F, 0x3F, 0x3F,
			  0x3F);
	dcs_ग_लिखो_cmd_seq(ctx, 0xA2, 0x3F, 0x09, 0x13, 0x17, 0x11, 0x15);
	dcs_ग_लिखो_cmd_seq(ctx, 0xA9, 0x07, 0x03, 0x3F);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_BS_SEL0, 0x3F, 0x05, 0x01, 0x17, 0x13,
			  0x15, 0x11, 0x0F, 0x3F);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_BS_SEL1, 0x3F, 0x3F, 0x3F, 0x3F, 0x0B,
			  0x0D, 0x09, 0x3F, 0x3F, 0x07);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_BS_SEL2, 0x03, 0x3F, 0x3F, 0x3F, 0x3F,
			  0x02, 0x06, 0x3F, 0x3F, 0x08);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_BS_SEL3, 0x0C, 0x0A, 0x3F, 0x3F, 0x3F,
			  0x3F, 0x3F, 0x0E, 0x10, 0x14);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GOA_BS_SEL4, 0x12, 0x16, 0x00, 0x04, 0x3F);
	dcs_ग_लिखो_seq(ctx, 0xDC, 0x02);
	dcs_ग_लिखो_seq(ctx, 0xDE, 0x12);

	dcs_ग_लिखो_seq(ctx, MCS_CMD_MODE_SW, 0x0E); /* No करोcumentation */
	dcs_ग_लिखो_seq(ctx, 0x01, 0x75);

	dcs_ग_लिखो_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P3);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GAMMA_VP, 0x00, 0x0C, 0x12, 0x0E, 0x06,
			  0x12, 0x0E, 0x0B, 0x15, 0x0B, 0x10, 0x07, 0x0F,
			  0x12, 0x0C, 0x00);
	dcs_ग_लिखो_cmd_seq(ctx, MCS_GAMMA_VN, 0x00, 0x0C, 0x12, 0x0E, 0x06,
			  0x12, 0x0E, 0x0B, 0x15, 0x0B, 0x10, 0x07, 0x0F,
			  0x12, 0x0C, 0x00);

	/* Exit CMD2 */
	dcs_ग_लिखो_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD1_UCS);
पूर्ण

अटल पूर्णांक rm68200_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rm68200 *ctx = panel_to_rm68200(panel);

	अगर (!ctx->enabled)
		वापस 0;

	ctx->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक rm68200_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा rm68200 *ctx = panel_to_rm68200(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret)
		dev_warn(panel->dev, "failed to set display off: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret)
		dev_warn(panel->dev, "failed to enter sleep mode: %d\n", ret);

	msleep(120);

	अगर (ctx->reset_gpio) अणु
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		msleep(20);
	पूर्ण

	regulator_disable(ctx->supply);

	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक rm68200_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा rm68200 *ctx = panel_to_rm68200(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	ret = regulator_enable(ctx->supply);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to enable supply: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ctx->reset_gpio) अणु
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		msleep(20);
		gpiod_set_value_cansleep(ctx->reset_gpio, 0);
		msleep(100);
	पूर्ण

	rm68200_init_sequence(ctx);

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret)
		वापस ret;

	msleep(125);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret)
		वापस ret;

	msleep(20);

	ctx->prepared = true;

	वापस 0;
पूर्ण

अटल पूर्णांक rm68200_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rm68200 *ctx = panel_to_rm68200(panel);

	अगर (ctx->enabled)
		वापस 0;

	ctx->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक rm68200_get_modes(काष्ठा drm_panel *panel,
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

अटल स्थिर काष्ठा drm_panel_funcs rm68200_drm_funcs = अणु
	.disable = rm68200_disable,
	.unprepare = rm68200_unprepare,
	.prepare = rm68200_prepare,
	.enable = rm68200_enable,
	.get_modes = rm68200_get_modes,
पूर्ण;

अटल पूर्णांक rm68200_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा rm68200 *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		ret = PTR_ERR(ctx->reset_gpio);
		dev_err(dev, "cannot get reset GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(ctx->supply)) अणु
		ret = PTR_ERR(ctx->supply);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "cannot get regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM | MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &rm68200_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "mipi_dsi_attach() failed: %d\n", ret);
		drm_panel_हटाओ(&ctx->panel);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rm68200_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा rm68200 *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id raydium_rm68200_of_match[] = अणु
	अणु .compatible = "raydium,rm68200" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, raydium_rm68200_of_match);

अटल काष्ठा mipi_dsi_driver raydium_rm68200_driver = अणु
	.probe = rm68200_probe,
	.हटाओ = rm68200_हटाओ,
	.driver = अणु
		.name = "panel-raydium-rm68200",
		.of_match_table = raydium_rm68200_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(raydium_rm68200_driver);

MODULE_AUTHOR("Philippe Cornu <philippe.cornu@st.com>");
MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_DESCRIPTION("DRM Driver for Raydium RM68200 MIPI DSI panel");
MODULE_LICENSE("GPL v2");
