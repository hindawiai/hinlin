<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019, Amarula Solutions.
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

#समावेश <video/mipi_display.h>

/* Command2 BKx selection command */
#घोषणा DSI_CMD2BKX_SEL			0xFF

/* Command2, BK0 commands */
#घोषणा DSI_CMD2_BK0_PVGAMCTRL		0xB0 /* Positive Voltage Gamma Control */
#घोषणा DSI_CMD2_BK0_NVGAMCTRL		0xB1 /* Negative Voltage Gamma Control */
#घोषणा DSI_CMD2_BK0_LNESET		0xC0 /* Display Line setting */
#घोषणा DSI_CMD2_BK0_PORCTRL		0xC1 /* Porch control */
#घोषणा DSI_CMD2_BK0_INVSEL		0xC2 /* Inversion selection, Frame Rate Control */

/* Command2, BK1 commands */
#घोषणा DSI_CMD2_BK1_VRHS		0xB0 /* Vop amplitude setting */
#घोषणा DSI_CMD2_BK1_VCOM		0xB1 /* VCOM amplitude setting */
#घोषणा DSI_CMD2_BK1_VGHSS		0xB2 /* VGH Voltage setting */
#घोषणा DSI_CMD2_BK1_TESTCMD		0xB3 /* TEST Command Setting */
#घोषणा DSI_CMD2_BK1_VGLS		0xB5 /* VGL Voltage setting */
#घोषणा DSI_CMD2_BK1_PWCTLR1		0xB7 /* Power Control 1 */
#घोषणा DSI_CMD2_BK1_PWCTLR2		0xB8 /* Power Control 2 */
#घोषणा DSI_CMD2_BK1_SPD1		0xC1 /* Source pre_drive timing set1 */
#घोषणा DSI_CMD2_BK1_SPD2		0xC2 /* Source EQ2 Setting */
#घोषणा DSI_CMD2_BK1_MIPISET1		0xD0 /* MIPI Setting 1 */

/**
 * Command2 with BK function selection.
 *
 * BIT[4, 0]: [CN2, BKXSEL]
 * 10 = CMD2BK0, Command2 BK0
 * 11 = CMD2BK1, Command2 BK1
 * 00 = Command2 disable
 */
#घोषणा DSI_CMD2BK1_SEL			0x11
#घोषणा DSI_CMD2BK0_SEL			0x10
#घोषणा DSI_CMD2BKX_SEL_NONE		0x00

/* Command2, BK0 bytes */
#घोषणा DSI_LINESET_LINE		0x69
#घोषणा DSI_LINESET_LDE_EN		BIT(7)
#घोषणा DSI_LINESET_LINEDELTA		GENMASK(1, 0)
#घोषणा DSI_CMD2_BK0_LNESET_B1		DSI_LINESET_LINEDELTA
#घोषणा DSI_CMD2_BK0_LNESET_B0		(DSI_LINESET_LDE_EN | DSI_LINESET_LINE)
#घोषणा DSI_INVSEL_DEFAULT		GENMASK(5, 4)
#घोषणा DSI_INVSEL_NLINV		GENMASK(2, 0)
#घोषणा DSI_INVSEL_RTNI			GENMASK(2, 1)
#घोषणा DSI_CMD2_BK0_INVSEL_B1		DSI_INVSEL_RTNI
#घोषणा DSI_CMD2_BK0_INVSEL_B0		(DSI_INVSEL_DEFAULT | DSI_INVSEL_NLINV)
#घोषणा DSI_CMD2_BK0_PORCTRL_B0(m)	((m)->vtotal - (m)->vsync_end)
#घोषणा DSI_CMD2_BK0_PORCTRL_B1(m)	((m)->vsync_start - (m)->vdisplay)

/* Command2, BK1 bytes */
#घोषणा DSI_CMD2_BK1_VRHA_SET		0x45
#घोषणा DSI_CMD2_BK1_VCOM_SET		0x13
#घोषणा DSI_CMD2_BK1_VGHSS_SET		GENMASK(2, 0)
#घोषणा DSI_CMD2_BK1_TESTCMD_VAL	BIT(7)
#घोषणा DSI_VGLS_DEFAULT		BIT(6)
#घोषणा DSI_VGLS_SEL			GENMASK(2, 0)
#घोषणा DSI_CMD2_BK1_VGLS_SET		(DSI_VGLS_DEFAULT | DSI_VGLS_SEL)
#घोषणा DSI_PWCTLR1_AP			BIT(7) /* Gamma OP bias, max */
#घोषणा DSI_PWCTLR1_APIS		BIT(2) /* Source OP input bias, min */
#घोषणा DSI_PWCTLR1_APOS		BIT(0) /* Source OP output bias, min */
#घोषणा DSI_CMD2_BK1_PWCTLR1_SET	(DSI_PWCTLR1_AP | DSI_PWCTLR1_APIS | \
					DSI_PWCTLR1_APOS)
#घोषणा DSI_PWCTLR2_AVDD		BIT(5) /* AVDD 6.6v */
#घोषणा DSI_PWCTLR2_AVCL		0x0    /* AVCL -4.4v */
#घोषणा DSI_CMD2_BK1_PWCTLR2_SET	(DSI_PWCTLR2_AVDD | DSI_PWCTLR2_AVCL)
#घोषणा DSI_SPD1_T2D			BIT(3)
#घोषणा DSI_CMD2_BK1_SPD1_SET		(GENMASK(6, 4) | DSI_SPD1_T2D)
#घोषणा DSI_CMD2_BK1_SPD2_SET		DSI_CMD2_BK1_SPD1_SET
#घोषणा DSI_MIPISET1_EOT_EN		BIT(3)
#घोषणा DSI_CMD2_BK1_MIPISET1_SET	(BIT(7) | DSI_MIPISET1_EOT_EN)

काष्ठा st7701_panel_desc अणु
	स्थिर काष्ठा drm_display_mode *mode;
	अचिन्हित पूर्णांक lanes;
	अचिन्हित दीर्घ flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	स्थिर अक्षर *स्थिर *supply_names;
	अचिन्हित पूर्णांक num_supplies;
	अचिन्हित पूर्णांक panel_sleep_delay;
पूर्ण;

काष्ठा st7701 अणु
	काष्ठा drm_panel panel;
	काष्ठा mipi_dsi_device *dsi;
	स्थिर काष्ठा st7701_panel_desc *desc;

	काष्ठा regulator_bulk_data *supplies;
	काष्ठा gpio_desc *reset;
	अचिन्हित पूर्णांक sleep_delay;
पूर्ण;

अटल अंतरभूत काष्ठा st7701 *panel_to_st7701(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा st7701, panel);
पूर्ण

अटल अंतरभूत पूर्णांक st7701_dsi_ग_लिखो(काष्ठा st7701 *st7701, स्थिर व्योम *seq,
				   माप_प्रकार len)
अणु
	वापस mipi_dsi_dcs_ग_लिखो_buffer(st7701->dsi, seq, len);
पूर्ण

#घोषणा ST7701_DSI(st7701, seq...)				\
	अणु							\
		स्थिर u8 d[] = अणु seq पूर्ण;				\
		st7701_dsi_ग_लिखो(st7701, d, ARRAY_SIZE(d));	\
	पूर्ण

अटल व्योम st7701_init_sequence(काष्ठा st7701 *st7701)
अणु
	स्थिर काष्ठा drm_display_mode *mode = st7701->desc->mode;

	ST7701_DSI(st7701, MIPI_DCS_SOFT_RESET, 0x00);

	/* We need to रुको 5ms beक्रमe sending new commands */
	msleep(5);

	ST7701_DSI(st7701, MIPI_DCS_EXIT_SLEEP_MODE, 0x00);

	msleep(st7701->sleep_delay);

	/* Command2, BK0 */
	ST7701_DSI(st7701, DSI_CMD2BKX_SEL,
		   0x77, 0x01, 0x00, 0x00, DSI_CMD2BK0_SEL);
	ST7701_DSI(st7701, DSI_CMD2_BK0_PVGAMCTRL, 0x00, 0x0E, 0x15, 0x0F,
		   0x11, 0x08, 0x08, 0x08, 0x08, 0x23, 0x04, 0x13, 0x12,
		   0x2B, 0x34, 0x1F);
	ST7701_DSI(st7701, DSI_CMD2_BK0_NVGAMCTRL, 0x00, 0x0E, 0x95, 0x0F,
		   0x13, 0x07, 0x09, 0x08, 0x08, 0x22, 0x04, 0x10, 0x0E,
		   0x2C, 0x34, 0x1F);
	ST7701_DSI(st7701, DSI_CMD2_BK0_LNESET,
		   DSI_CMD2_BK0_LNESET_B0, DSI_CMD2_BK0_LNESET_B1);
	ST7701_DSI(st7701, DSI_CMD2_BK0_PORCTRL,
		   DSI_CMD2_BK0_PORCTRL_B0(mode),
		   DSI_CMD2_BK0_PORCTRL_B1(mode));
	ST7701_DSI(st7701, DSI_CMD2_BK0_INVSEL,
		   DSI_CMD2_BK0_INVSEL_B0, DSI_CMD2_BK0_INVSEL_B1);

	/* Command2, BK1 */
	ST7701_DSI(st7701, DSI_CMD2BKX_SEL,
			0x77, 0x01, 0x00, 0x00, DSI_CMD2BK1_SEL);
	ST7701_DSI(st7701, DSI_CMD2_BK1_VRHS, DSI_CMD2_BK1_VRHA_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_VCOM, DSI_CMD2_BK1_VCOM_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_VGHSS, DSI_CMD2_BK1_VGHSS_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_TESTCMD, DSI_CMD2_BK1_TESTCMD_VAL);
	ST7701_DSI(st7701, DSI_CMD2_BK1_VGLS, DSI_CMD2_BK1_VGLS_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_PWCTLR1, DSI_CMD2_BK1_PWCTLR1_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_PWCTLR2, DSI_CMD2_BK1_PWCTLR2_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_SPD1, DSI_CMD2_BK1_SPD1_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_SPD2, DSI_CMD2_BK1_SPD2_SET);
	ST7701_DSI(st7701, DSI_CMD2_BK1_MIPISET1, DSI_CMD2_BK1_MIPISET1_SET);

	/**
	 * ST7701_SPEC_V1.2 is unable to provide enough inक्रमmation above this
	 * specअगरic command sequence, so grab the same from venकरोr BSP driver.
	 */
	ST7701_DSI(st7701, 0xE0, 0x00, 0x00, 0x02);
	ST7701_DSI(st7701, 0xE1, 0x0B, 0x00, 0x0D, 0x00, 0x0C, 0x00, 0x0E,
		   0x00, 0x00, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE2, 0x33, 0x33, 0x44, 0x44, 0x64, 0x00, 0x66,
		   0x00, 0x65, 0x00, 0x67, 0x00, 0x00);
	ST7701_DSI(st7701, 0xE3, 0x00, 0x00, 0x33, 0x33);
	ST7701_DSI(st7701, 0xE4, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE5, 0x0C, 0x78, 0x3C, 0xA0, 0x0E, 0x78, 0x3C,
		   0xA0, 0x10, 0x78, 0x3C, 0xA0, 0x12, 0x78, 0x3C, 0xA0);
	ST7701_DSI(st7701, 0xE6, 0x00, 0x00, 0x33, 0x33);
	ST7701_DSI(st7701, 0xE7, 0x44, 0x44);
	ST7701_DSI(st7701, 0xE8, 0x0D, 0x78, 0x3C, 0xA0, 0x0F, 0x78, 0x3C,
		   0xA0, 0x11, 0x78, 0x3C, 0xA0, 0x13, 0x78, 0x3C, 0xA0);
	ST7701_DSI(st7701, 0xEB, 0x02, 0x02, 0x39, 0x39, 0xEE, 0x44, 0x00);
	ST7701_DSI(st7701, 0xEC, 0x00, 0x00);
	ST7701_DSI(st7701, 0xED, 0xFF, 0xF1, 0x04, 0x56, 0x72, 0x3F, 0xFF,
		   0xFF, 0xFF, 0xFF, 0xF3, 0x27, 0x65, 0x40, 0x1F, 0xFF);

	/* disable Command2 */
	ST7701_DSI(st7701, DSI_CMD2BKX_SEL,
		   0x77, 0x01, 0x00, 0x00, DSI_CMD2BKX_SEL_NONE);
पूर्ण

अटल पूर्णांक st7701_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7701 *st7701 = panel_to_st7701(panel);
	पूर्णांक ret;

	gpiod_set_value(st7701->reset, 0);

	ret = regulator_bulk_enable(st7701->desc->num_supplies,
				    st7701->supplies);
	अगर (ret < 0)
		वापस ret;
	msleep(20);

	gpiod_set_value(st7701->reset, 1);
	msleep(150);

	st7701_init_sequence(st7701);

	वापस 0;
पूर्ण

अटल पूर्णांक st7701_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7701 *st7701 = panel_to_st7701(panel);

	ST7701_DSI(st7701, MIPI_DCS_SET_DISPLAY_ON, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक st7701_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7701 *st7701 = panel_to_st7701(panel);

	ST7701_DSI(st7701, MIPI_DCS_SET_DISPLAY_OFF, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक st7701_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7701 *st7701 = panel_to_st7701(panel);

	ST7701_DSI(st7701, MIPI_DCS_ENTER_SLEEP_MODE, 0x00);

	msleep(st7701->sleep_delay);

	gpiod_set_value(st7701->reset, 0);

	/**
	 * During the Resetting period, the display will be blanked
	 * (The display is entering blanking sequence, which maximum
	 * समय is 120 ms, when Reset Starts in Sleep Out ै mode. The
	 * display reमुख्यs the blank state in Sleep In ै mode.) and
	 * then वापस to Default condition क्रम Hardware Reset.
	 *
	 * So we need रुको sleep_delay समय to make sure reset completed.
	 */
	msleep(st7701->sleep_delay);

	regulator_bulk_disable(st7701->desc->num_supplies, st7701->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक st7701_get_modes(काष्ठा drm_panel *panel,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा st7701 *st7701 = panel_to_st7701(panel);
	स्थिर काष्ठा drm_display_mode *desc_mode = st7701->desc->mode;
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, desc_mode);
	अगर (!mode) अणु
		dev_err(&st7701->dsi->dev, "failed to add mode %ux%u@%u\n",
			desc_mode->hdisplay, desc_mode->vdisplay,
			drm_mode_vrefresh(desc_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = desc_mode->width_mm;
	connector->display_info.height_mm = desc_mode->height_mm;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs st7701_funcs = अणु
	.disable	= st7701_disable,
	.unprepare	= st7701_unprepare,
	.prepare	= st7701_prepare,
	.enable		= st7701_enable,
	.get_modes	= st7701_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ts8550b_mode = अणु
	.घड़ी		= 27500,

	.hdisplay	= 480,
	.hsync_start	= 480 + 38,
	.hsync_end	= 480 + 38 + 12,
	.htotal		= 480 + 38 + 12 + 12,

	.vdisplay	= 854,
	.vsync_start	= 854 + 18,
	.vsync_end	= 854 + 18 + 8,
	.vtotal		= 854 + 18 + 8 + 4,

	.width_mm	= 69,
	.height_mm	= 139,

	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ts8550b_supply_names[] = अणु
	"VCC",
	"IOVCC",
पूर्ण;

अटल स्थिर काष्ठा st7701_panel_desc ts8550b_desc = अणु
	.mode = &ts8550b_mode,
	.lanes = 2,
	.flags = MIPI_DSI_MODE_VIDEO,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.supply_names = ts8550b_supply_names,
	.num_supplies = ARRAY_SIZE(ts8550b_supply_names),
	.panel_sleep_delay = 80, /* panel need extra 80ms क्रम sleep out cmd */
पूर्ण;

अटल पूर्णांक st7701_dsi_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	स्थिर काष्ठा st7701_panel_desc *desc;
	काष्ठा st7701 *st7701;
	पूर्णांक ret, i;

	st7701 = devm_kzalloc(&dsi->dev, माप(*st7701), GFP_KERNEL);
	अगर (!st7701)
		वापस -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_flags = desc->flags;
	dsi->क्रमmat = desc->क्रमmat;
	dsi->lanes = desc->lanes;

	st7701->supplies = devm_kसुस्मृति(&dsi->dev, desc->num_supplies,
					माप(*st7701->supplies),
					GFP_KERNEL);
	अगर (!st7701->supplies)
		वापस -ENOMEM;

	क्रम (i = 0; i < desc->num_supplies; i++)
		st7701->supplies[i].supply = desc->supply_names[i];

	ret = devm_regulator_bulk_get(&dsi->dev, desc->num_supplies,
				      st7701->supplies);
	अगर (ret < 0)
		वापस ret;

	st7701->reset = devm_gpiod_get(&dsi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(st7701->reset)) अणु
		dev_err(&dsi->dev, "Couldn't get our reset GPIO\n");
		वापस PTR_ERR(st7701->reset);
	पूर्ण

	drm_panel_init(&st7701->panel, &dsi->dev, &st7701_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	/**
	 * Once sleep out has been issued, ST7701 IC required to रुको 120ms
	 * beक्रमe initiating new commands.
	 *
	 * On top of that some panels might need an extra delay to रुको, so
	 * add panel specअगरic delay क्रम those हालs. As now this panel specअगरic
	 * delay inक्रमmation is referenced from those panel BSP driver, example
	 * ts8550b and there is no valid करोcumentation क्रम that.
	 */
	st7701->sleep_delay = 120 + desc->panel_sleep_delay;

	ret = drm_panel_of_backlight(&st7701->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&st7701->panel);

	mipi_dsi_set_drvdata(dsi, st7701);
	st7701->dsi = dsi;
	st7701->desc = desc;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक st7701_dsi_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा st7701 *st7701 = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&st7701->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id st7701_of_match[] = अणु
	अणु .compatible = "techstar,ts8550b", .data = &ts8550b_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st7701_of_match);

अटल काष्ठा mipi_dsi_driver st7701_dsi_driver = अणु
	.probe		= st7701_dsi_probe,
	.हटाओ		= st7701_dsi_हटाओ,
	.driver = अणु
		.name		= "st7701",
		.of_match_table	= st7701_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(st7701_dsi_driver);

MODULE_AUTHOR("Jagan Teki <jagan@amarulasolutions.com>");
MODULE_DESCRIPTION("Sitronix ST7701 LCD Panel Driver");
MODULE_LICENSE("GPL");
