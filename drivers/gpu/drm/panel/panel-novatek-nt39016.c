<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Novatek NT39016 TFT LCD panel driver
 *
 * Copyright (C) 2017, Maarten ter Huurne <maarten@treewalker.org>
 * Copyright (C) 2019, Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

क्रमागत nt39016_regs अणु
	NT39016_REG_SYSTEM,
	NT39016_REG_TIMING,
	NT39016_REG_OP,
	NT39016_REG_DATA_IN,
	NT39016_REG_SRC_TIMING_DELAY,
	NT39016_REG_GATE_TIMING_DELAY,
	NT39016_REG_RESERVED,
	NT39016_REG_INITIAL_FUNC,
	NT39016_REG_CONTRAST,
	NT39016_REG_BRIGHTNESS,
	NT39016_REG_HUE_SATURATION,
	NT39016_REG_RB_SUBCONTRAST,
	NT39016_REG_R_SUBBRIGHTNESS,
	NT39016_REG_B_SUBBRIGHTNESS,
	NT39016_REG_VCOMDC,
	NT39016_REG_VCOMAC,
	NT39016_REG_VGAM2,
	NT39016_REG_VGAM34,
	NT39016_REG_VGAM56,
	NT39016_REG_VCOMDC_TRIM = 0x1e,
	NT39016_REG_DISPLAY_MODE = 0x20,
पूर्ण;

#घोषणा NT39016_SYSTEM_RESET_N	BIT(0)
#घोषणा NT39016_SYSTEM_STANDBY	BIT(1)

काष्ठा nt39016_panel_info अणु
	स्थिर काष्ठा drm_display_mode *display_modes;
	अचिन्हित पूर्णांक num_modes;
	u16 width_mm, height_mm;
	u32 bus_क्रमmat, bus_flags;
पूर्ण;

काष्ठा nt39016 अणु
	काष्ठा drm_panel drm_panel;
	काष्ठा regmap *map;
	काष्ठा regulator *supply;
	स्थिर काष्ठा nt39016_panel_info *panel_info;

	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

अटल अंतरभूत काष्ठा nt39016 *to_nt39016(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा nt39016, drm_panel);
पूर्ण

#घोषणा RV(REG, VAL) अणु .reg = (REG), .def = (VAL), .delay_us = 2 पूर्ण
अटल स्थिर काष्ठा reg_sequence nt39016_panel_regs[] = अणु
	RV(NT39016_REG_SYSTEM, 0x00),
	RV(NT39016_REG_TIMING, 0x00),
	RV(NT39016_REG_OP, 0x03),
	RV(NT39016_REG_DATA_IN, 0xCC),
	RV(NT39016_REG_SRC_TIMING_DELAY, 0x46),
	RV(NT39016_REG_GATE_TIMING_DELAY, 0x05),
	RV(NT39016_REG_RESERVED, 0x00),
	RV(NT39016_REG_INITIAL_FUNC, 0x00),
	RV(NT39016_REG_CONTRAST, 0x08),
	RV(NT39016_REG_BRIGHTNESS, 0x40),
	RV(NT39016_REG_HUE_SATURATION, 0x88),
	RV(NT39016_REG_RB_SUBCONTRAST, 0x88),
	RV(NT39016_REG_R_SUBBRIGHTNESS, 0x20),
	RV(NT39016_REG_B_SUBBRIGHTNESS, 0x20),
	RV(NT39016_REG_VCOMDC, 0x67),
	RV(NT39016_REG_VCOMAC, 0xA4),
	RV(NT39016_REG_VGAM2, 0x04),
	RV(NT39016_REG_VGAM34, 0x24),
	RV(NT39016_REG_VGAM56, 0x24),
	RV(NT39016_REG_DISPLAY_MODE, 0x00),
पूर्ण;

#अघोषित RV

अटल स्थिर काष्ठा regmap_range nt39016_regmap_no_ranges[] = अणु
	regmap_reg_range(0x13, 0x1D),
	regmap_reg_range(0x1F, 0x1F),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table nt39016_regmap_access_table = अणु
	.no_ranges = nt39016_regmap_no_ranges,
	.n_no_ranges = ARRAY_SIZE(nt39016_regmap_no_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config nt39016_regmap_config = अणु
	.reg_bits = 6,
	.pad_bits = 2,
	.val_bits = 8,

	.max_रेजिस्टर = NT39016_REG_DISPLAY_MODE,
	.wr_table = &nt39016_regmap_access_table,
	.ग_लिखो_flag_mask = 0x02,

	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक nt39016_prepare(काष्ठा drm_panel *drm_panel)
अणु
	काष्ठा nt39016 *panel = to_nt39016(drm_panel);
	पूर्णांक err;

	err = regulator_enable(panel->supply);
	अगर (err) अणु
		dev_err(drm_panel->dev, "Failed to enable power supply: %d\n", err);
		वापस err;
	पूर्ण

	/*
	 * Reset the NT39016.
	 * The करोcumentation says the reset pulse should be at least 40 us to
	 * pass the glitch filter, but when testing I see some resets fail and
	 * some succeed when using a 70 us delay, so we use 100 us instead.
	 */
	gpiod_set_value_cansleep(panel->reset_gpio, 1);
	usleep_range(100, 1000);
	gpiod_set_value_cansleep(panel->reset_gpio, 0);
	udelay(2);

	/* Init all रेजिस्टरs. */
	err = regmap_multi_reg_ग_लिखो(panel->map, nt39016_panel_regs,
				     ARRAY_SIZE(nt39016_panel_regs));
	अगर (err) अणु
		dev_err(drm_panel->dev, "Failed to init registers: %d\n", err);
		जाओ err_disable_regulator;
	पूर्ण

	वापस 0;

err_disable_regulator:
	regulator_disable(panel->supply);
	वापस err;
पूर्ण

अटल पूर्णांक nt39016_unprepare(काष्ठा drm_panel *drm_panel)
अणु
	काष्ठा nt39016 *panel = to_nt39016(drm_panel);

	gpiod_set_value_cansleep(panel->reset_gpio, 1);

	regulator_disable(panel->supply);

	वापस 0;
पूर्ण

अटल पूर्णांक nt39016_enable(काष्ठा drm_panel *drm_panel)
अणु
	काष्ठा nt39016 *panel = to_nt39016(drm_panel);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(panel->map, NT39016_REG_SYSTEM,
			   NT39016_SYSTEM_RESET_N | NT39016_SYSTEM_STANDBY);
	अगर (ret) अणु
		dev_err(drm_panel->dev, "Unable to enable panel: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (drm_panel->backlight) अणु
		/* Wait क्रम the picture to be पढ़ोy beक्रमe enabling backlight */
		msleep(150);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nt39016_disable(काष्ठा drm_panel *drm_panel)
अणु
	काष्ठा nt39016 *panel = to_nt39016(drm_panel);
	पूर्णांक err;

	err = regmap_ग_लिखो(panel->map, NT39016_REG_SYSTEM,
			   NT39016_SYSTEM_RESET_N);
	अगर (err) अणु
		dev_err(drm_panel->dev, "Unable to disable panel: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nt39016_get_modes(काष्ठा drm_panel *drm_panel,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा nt39016 *panel = to_nt39016(drm_panel);
	स्थिर काष्ठा nt39016_panel_info *panel_info = panel->panel_info;
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

अटल स्थिर काष्ठा drm_panel_funcs nt39016_funcs = अणु
	.prepare	= nt39016_prepare,
	.unprepare	= nt39016_unprepare,
	.enable		= nt39016_enable,
	.disable	= nt39016_disable,
	.get_modes	= nt39016_get_modes,
पूर्ण;

अटल पूर्णांक nt39016_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा nt39016 *panel;
	पूर्णांक err;

	panel = devm_kzalloc(dev, माप(*panel), GFP_KERNEL);
	अगर (!panel)
		वापस -ENOMEM;

	spi_set_drvdata(spi, panel);

	panel->panel_info = of_device_get_match_data(dev);
	अगर (!panel->panel_info)
		वापस -EINVAL;

	panel->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(panel->supply)) अणु
		dev_err(dev, "Failed to get power supply\n");
		वापस PTR_ERR(panel->supply);
	पूर्ण

	panel->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(panel->reset_gpio)) अणु
		dev_err(dev, "Failed to get reset GPIO\n");
		वापस PTR_ERR(panel->reset_gpio);
	पूर्ण

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_3 | SPI_3WIRE;
	err = spi_setup(spi);
	अगर (err) अणु
		dev_err(dev, "Failed to setup SPI\n");
		वापस err;
	पूर्ण

	panel->map = devm_regmap_init_spi(spi, &nt39016_regmap_config);
	अगर (IS_ERR(panel->map)) अणु
		dev_err(dev, "Failed to init regmap\n");
		वापस PTR_ERR(panel->map);
	पूर्ण

	drm_panel_init(&panel->drm_panel, dev, &nt39016_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	err = drm_panel_of_backlight(&panel->drm_panel);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get backlight handle\n");
		वापस err;
	पूर्ण

	drm_panel_add(&panel->drm_panel);

	वापस 0;
पूर्ण

अटल पूर्णांक nt39016_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा nt39016 *panel = spi_get_drvdata(spi);

	drm_panel_हटाओ(&panel->drm_panel);

	nt39016_disable(&panel->drm_panel);
	nt39016_unprepare(&panel->drm_panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode kd035g6_display_modes[] = अणु
	अणु	/* 60 Hz */
		.घड़ी = 6000,
		.hdisplay = 320,
		.hsync_start = 320 + 10,
		.hsync_end = 320 + 10 + 50,
		.htotal = 320 + 10 + 50 + 20,
		.vdisplay = 240,
		.vsync_start = 240 + 5,
		.vsync_end = 240 + 5 + 1,
		.vtotal = 240 + 5 + 1 + 4,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
	अणु	/* 50 Hz */
		.घड़ी = 5400,
		.hdisplay = 320,
		.hsync_start = 320 + 42,
		.hsync_end = 320 + 42 + 50,
		.htotal = 320 + 42 + 50 + 20,
		.vdisplay = 240,
		.vsync_start = 240 + 5,
		.vsync_end = 240 + 5 + 1,
		.vtotal = 240 + 5 + 1 + 4,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nt39016_panel_info kd035g6_info = अणु
	.display_modes = kd035g6_display_modes,
	.num_modes = ARRAY_SIZE(kd035g6_display_modes),
	.width_mm = 71,
	.height_mm = 53,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id nt39016_of_match[] = अणु
	अणु .compatible = "kingdisplay,kd035g6-54nt", .data = &kd035g6_info पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nt39016_of_match);

अटल काष्ठा spi_driver nt39016_driver = अणु
	.driver = अणु
		.name = "nt39016",
		.of_match_table = nt39016_of_match,
	पूर्ण,
	.probe = nt39016_probe,
	.हटाओ = nt39016_हटाओ,
पूर्ण;

module_spi_driver(nt39016_driver);

MODULE_AUTHOR("Maarten ter Huurne <maarten@treewalker.org>");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_LICENSE("GPL v2");
