<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Asia Better Technology Ltd. Y030XX067A IPS LCD panel driver
 *
 * Copyright (C) 2020, Paul Cercueil <paul@crapouillou.net>
 * Copyright (C) 2020, Christophe Branchereau <cbranchereau@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा REG00_VBRT_CTRL(val)		(val)

#घोषणा REG01_COM_DC(val)		(val)

#घोषणा REG02_DA_CONTRAST(val)		(val)
#घोषणा REG02_VESA_SEL(val)		((val) << 5)
#घोषणा REG02_COMDC_SW			BIT(7)

#घोषणा REG03_VPOSITION(val)		(val)
#घोषणा REG03_BSMOUNT			BIT(5)
#घोषणा REG03_COMTST			BIT(6)
#घोषणा REG03_HPOSITION1		BIT(7)

#घोषणा REG04_HPOSITION1(val)		(val)

#घोषणा REG05_CLIP			BIT(0)
#घोषणा REG05_NVM_VREFRESH		BIT(1)
#घोषणा REG05_SLFR			BIT(2)
#घोषणा REG05_SLBRCHARGE(val)		((val) << 3)
#घोषणा REG05_PRECHARGE_LEVEL(val)	((val) << 6)

#घोषणा REG06_TEST5			BIT(0)
#घोषणा REG06_SLDWN			BIT(1)
#घोषणा REG06_SLRGT			BIT(2)
#घोषणा REG06_TEST2			BIT(3)
#घोषणा REG06_XPSAVE			BIT(4)
#घोषणा REG06_GAMMA_SEL(val)		((val) << 5)
#घोषणा REG06_NT			BIT(7)

#घोषणा REG07_TEST1			BIT(0)
#घोषणा REG07_HDVD_POL			BIT(1)
#घोषणा REG07_CK_POL			BIT(2)
#घोषणा REG07_TEST3			BIT(3)
#घोषणा REG07_TEST4			BIT(4)
#घोषणा REG07_480_LINEMASK		BIT(5)
#घोषणा REG07_AMPTST(val)		((val) << 6)

#घोषणा REG08_SLHRC(val)		(val)
#घोषणा REG08_CLOCK_DIV(val)		((val) << 2)
#घोषणा REG08_PANEL(val)		((val) << 5)

#घोषणा REG09_SUB_BRIGHT_R(val)		(val)
#घोषणा REG09_NW_NB			BIT(6)
#घोषणा REG09_IPCON			BIT(7)

#घोषणा REG0A_SUB_BRIGHT_B(val)		(val)
#घोषणा REG0A_PAIR			BIT(6)
#घोषणा REG0A_DE_SEL			BIT(7)

#घोषणा REG0B_MBK_POSITION(val)		(val)
#घोषणा REG0B_HD_FREERUN		BIT(4)
#घोषणा REG0B_VD_FREERUN		BIT(5)
#घोषणा REG0B_YUV2BIN(val)		((val) << 6)

#घोषणा REG0C_CONTRAST_R(val)		(val)
#घोषणा REG0C_DOUBLEREAD		BIT(7)

#घोषणा REG0D_CONTRAST_G(val)		(val)
#घोषणा REG0D_RGB_YUV			BIT(7)

#घोषणा REG0E_CONTRAST_B(val)		(val)
#घोषणा REG0E_PIXELCOLORDRIVE		BIT(7)

#घोषणा REG0F_ASPECT			BIT(0)
#घोषणा REG0F_OVERSCAN(val)		((val) << 1)
#घोषणा REG0F_FRAMEWIDTH(val)		((val) << 3)

#घोषणा REG10_BRIGHT(val)		(val)

#घोषणा REG11_SIG_GAIN(val)		(val)
#घोषणा REG11_SIGC_CNTL			BIT(6)
#घोषणा REG11_SIGC_POL			BIT(7)

#घोषणा REG12_COLOR(val)		(val)
#घोषणा REG12_PWCKSEL(val)		((val) << 6)

#घोषणा REG13_4096LEVEL_CNTL(val)	(val)
#घोषणा REG13_SL4096(val)		((val) << 4)
#घोषणा REG13_LIMITER_CONTROL		BIT(7)

#घोषणा REG14_PANEL_TEST(val)		(val)

#घोषणा REG15_NVM_LINK0			BIT(0)
#घोषणा REG15_NVM_LINK1			BIT(1)
#घोषणा REG15_NVM_LINK2			BIT(2)
#घोषणा REG15_NVM_LINK3			BIT(3)
#घोषणा REG15_NVM_LINK4			BIT(4)
#घोषणा REG15_NVM_LINK5			BIT(5)
#घोषणा REG15_NVM_LINK6			BIT(6)
#घोषणा REG15_NVM_LINK7			BIT(7)

काष्ठा y030xx067a_info अणु
	स्थिर काष्ठा drm_display_mode *display_modes;
	अचिन्हित पूर्णांक num_modes;
	u16 width_mm, height_mm;
	u32 bus_क्रमmat, bus_flags;
पूर्ण;

काष्ठा y030xx067a अणु
	काष्ठा drm_panel panel;
	काष्ठा spi_device *spi;
	काष्ठा regmap *map;

	स्थिर काष्ठा y030xx067a_info *panel_info;

	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

अटल अंतरभूत काष्ठा y030xx067a *to_y030xx067a(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा y030xx067a, panel);
पूर्ण

अटल स्थिर काष्ठा reg_sequence y030xx067a_init_sequence[] = अणु
	अणु 0x00, REG00_VBRT_CTRL(0x7f) पूर्ण,
	अणु 0x01, REG01_COM_DC(0x3c) पूर्ण,
	अणु 0x02, REG02_VESA_SEL(0x3) | REG02_DA_CONTRAST(0x1f) पूर्ण,
	अणु 0x03, REG03_VPOSITION(0x0a) पूर्ण,
	अणु 0x04, REG04_HPOSITION1(0xd2) पूर्ण,
	अणु 0x05, REG05_CLIP | REG05_NVM_VREFRESH | REG05_SLBRCHARGE(0x2) पूर्ण,
	अणु 0x06, REG06_XPSAVE | REG06_NT पूर्ण,
	अणु 0x07, 0 पूर्ण,
	अणु 0x08, REG08_PANEL(0x1) | REG08_CLOCK_DIV(0x2) पूर्ण,
	अणु 0x09, REG09_SUB_BRIGHT_R(0x20) पूर्ण,
	अणु 0x0a, REG0A_SUB_BRIGHT_B(0x20) पूर्ण,
	अणु 0x0b, REG0B_HD_FREERUN | REG0B_VD_FREERUN पूर्ण,
	अणु 0x0c, REG0C_CONTRAST_R(0x10) पूर्ण,
	अणु 0x0d, REG0D_CONTRAST_G(0x10) पूर्ण,
	अणु 0x0e, REG0E_CONTRAST_B(0x10) पूर्ण,
	अणु 0x0f, 0 पूर्ण,
	अणु 0x10, REG10_BRIGHT(0x7f) पूर्ण,
	अणु 0x11, REG11_SIGC_CNTL | REG11_SIG_GAIN(0x3f) पूर्ण,
	अणु 0x12, REG12_COLOR(0x20) | REG12_PWCKSEL(0x1) पूर्ण,
	अणु 0x13, REG13_4096LEVEL_CNTL(0x8) पूर्ण,
	अणु 0x14, 0 पूर्ण,
	अणु 0x15, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक y030xx067a_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा y030xx067a *priv = to_y030xx067a(panel);
	काष्ठा device *dev = &priv->spi->dev;
	पूर्णांक err;

	err = regulator_enable(priv->supply);
	अगर (err) अणु
		dev_err(dev, "Failed to enable power supply: %d\n", err);
		वापस err;
	पूर्ण

	/* Reset the chip */
	gpiod_set_value_cansleep(priv->reset_gpio, 1);
	usleep_range(1000, 20000);
	gpiod_set_value_cansleep(priv->reset_gpio, 0);
	usleep_range(1000, 20000);

	err = regmap_multi_reg_ग_लिखो(priv->map, y030xx067a_init_sequence,
				     ARRAY_SIZE(y030xx067a_init_sequence));
	अगर (err) अणु
		dev_err(dev, "Failed to init registers: %d\n", err);
		जाओ err_disable_regulator;
	पूर्ण

	msleep(120);

	वापस 0;

err_disable_regulator:
	regulator_disable(priv->supply);
	वापस err;
पूर्ण

अटल पूर्णांक y030xx067a_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा y030xx067a *priv = to_y030xx067a(panel);

	gpiod_set_value_cansleep(priv->reset_gpio, 1);
	regulator_disable(priv->supply);

	वापस 0;
पूर्ण

अटल पूर्णांक y030xx067a_get_modes(काष्ठा drm_panel *panel,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा y030xx067a *priv = to_y030xx067a(panel);
	स्थिर काष्ठा y030xx067a_info *panel_info = priv->panel_info;
	काष्ठा drm_display_mode *mode;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < panel_info->num_modes; i++) अणु
		mode = drm_mode_duplicate(connector->dev,
					  &panel_info->display_modes[i]);
		अगर (!mode)
			वापस -ENOMEM;

		drm_mode_set_name(mode);

		mode->type = DRM_MODE_TYPE_DRIVER;
		अगर (panel_info->num_modes == 1)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
	पूर्ण

	connector->display_info.bpc = 8;
	connector->display_info.width_mm = panel_info->width_mm;
	connector->display_info.height_mm = panel_info->height_mm;

	drm_display_info_set_bus_क्रमmats(&connector->display_info,
					 &panel_info->bus_क्रमmat, 1);
	connector->display_info.bus_flags = panel_info->bus_flags;

	वापस panel_info->num_modes;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs y030xx067a_funcs = अणु
	.prepare	= y030xx067a_prepare,
	.unprepare	= y030xx067a_unprepare,
	.get_modes	= y030xx067a_get_modes,
पूर्ण;

अटल स्थिर काष्ठा regmap_config y030xx067a_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x15,
पूर्ण;

अटल पूर्णांक y030xx067a_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा y030xx067a *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->spi = spi;
	spi_set_drvdata(spi, priv);

	priv->map = devm_regmap_init_spi(spi, &y030xx067a_regmap_config);
	अगर (IS_ERR(priv->map)) अणु
		dev_err(dev, "Unable to init regmap\n");
		वापस PTR_ERR(priv->map);
	पूर्ण

	priv->panel_info = of_device_get_match_data(dev);
	अगर (!priv->panel_info)
		वापस -EINVAL;

	priv->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(priv->supply)) अणु
		dev_err(dev, "Failed to get power supply\n");
		वापस PTR_ERR(priv->supply);
	पूर्ण

	priv->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->reset_gpio)) अणु
		dev_err(dev, "Failed to get reset GPIO\n");
		वापस PTR_ERR(priv->reset_gpio);
	पूर्ण

	drm_panel_init(&priv->panel, dev, &y030xx067a_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	err = drm_panel_of_backlight(&priv->panel);
	अगर (err)
		वापस err;

	drm_panel_add(&priv->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक y030xx067a_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा y030xx067a *priv = spi_get_drvdata(spi);

	drm_panel_हटाओ(&priv->panel);
	drm_panel_disable(&priv->panel);
	drm_panel_unprepare(&priv->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode y030xx067a_modes[] = अणु
	अणु /* 60 Hz */
		.घड़ी = 14400,
		.hdisplay = 320,
		.hsync_start = 320 + 10,
		.hsync_end = 320 + 10 + 37,
		.htotal = 320 + 10 + 37 + 33,
		.vdisplay = 480,
		.vsync_start = 480 + 84,
		.vsync_end = 480 + 84 + 20,
		.vtotal = 480 + 84 + 20 + 16,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
	अणु /* 50 Hz */
		.घड़ी = 12000,
		.hdisplay = 320,
		.hsync_start = 320 + 10,
		.hsync_end = 320 + 10 + 37,
		.htotal = 320 + 10 + 37 + 33,
		.vdisplay = 480,
		.vsync_start = 480 + 84,
		.vsync_end = 480 + 84 + 20,
		.vtotal = 480 + 84 + 20 + 16,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा y030xx067a_info y030xx067a_info = अणु
	.display_modes = y030xx067a_modes,
	.num_modes = ARRAY_SIZE(y030xx067a_modes),
	.width_mm = 69,
	.height_mm = 51,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_3X8_DELTA,
	.bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE | DRM_BUS_FLAG_DE_LOW,
पूर्ण;

अटल स्थिर काष्ठा of_device_id y030xx067a_of_match[] = अणु
	अणु .compatible = "abt,y030xx067a", .data = &y030xx067a_info पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, y030xx067a_of_match);

अटल काष्ठा spi_driver y030xx067a_driver = अणु
	.driver = अणु
		.name = "abt-y030xx067a",
		.of_match_table = y030xx067a_of_match,
	पूर्ण,
	.probe = y030xx067a_probe,
	.हटाओ = y030xx067a_हटाओ,
पूर्ण;
module_spi_driver(y030xx067a_driver);

MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_AUTHOR("Christophe Branchereau <cbranchereau@gmail.com>");
MODULE_LICENSE("GPL v2");
