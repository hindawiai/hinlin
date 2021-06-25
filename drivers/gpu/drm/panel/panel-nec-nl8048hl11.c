<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NEC NL8048HL11 Panel Driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Based on the omapdrm-specअगरic panel-nec-nl8048hl11 driver
 *
 * Copyright (C) 2010 Texas Instruments Incorporated
 * Author: Erik Gilling <konkers@android.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा nl8048_panel अणु
	काष्ठा drm_panel panel;

	काष्ठा spi_device *spi;
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

#घोषणा to_nl8048_device(p) container_of(p, काष्ठा nl8048_panel, panel)

अटल पूर्णांक nl8048_ग_लिखो(काष्ठा nl8048_panel *lcd, अचिन्हित अक्षर addr,
			अचिन्हित अक्षर value)
अणु
	u8 data[4] = अणु value, 0x01, addr, 0x00 पूर्ण;
	पूर्णांक ret;

	ret = spi_ग_लिखो(lcd->spi, data, माप(data));
	अगर (ret)
		dev_err(&lcd->spi->dev, "SPI write to %u failed: %d\n",
			addr, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक nl8048_init(काष्ठा nl8048_panel *lcd)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित अक्षर addr;
		अचिन्हित अक्षर data;
	पूर्ण nl8048_init_seq[] = अणु
		अणु   3, 0x01 पूर्ण, अणु   0, 0x00 पूर्ण, अणु   1, 0x01 पूर्ण, अणु   4, 0x00 पूर्ण,
		अणु   5, 0x14 पूर्ण, अणु   6, 0x24 पूर्ण, अणु  16, 0xd7 पूर्ण, अणु  17, 0x00 पूर्ण,
		अणु  18, 0x00 पूर्ण, अणु  19, 0x55 पूर्ण, अणु  20, 0x01 पूर्ण, अणु  21, 0x70 पूर्ण,
		अणु  22, 0x1e पूर्ण, अणु  23, 0x25 पूर्ण, अणु  24, 0x25 पूर्ण, अणु  25, 0x02 पूर्ण,
		अणु  26, 0x02 पूर्ण, अणु  27, 0xa0 पूर्ण, अणु  32, 0x2f पूर्ण, अणु  33, 0x0f पूर्ण,
		अणु  34, 0x0f पूर्ण, अणु  35, 0x0f पूर्ण, अणु  36, 0x0f पूर्ण, अणु  37, 0x0f पूर्ण,
		अणु  38, 0x0f पूर्ण, अणु  39, 0x00 पूर्ण, अणु  40, 0x02 पूर्ण, अणु  41, 0x02 पूर्ण,
		अणु  42, 0x02 पूर्ण, अणु  43, 0x0f पूर्ण, अणु  44, 0x0f पूर्ण, अणु  45, 0x0f पूर्ण,
		अणु  46, 0x0f पूर्ण, अणु  47, 0x0f पूर्ण, अणु  48, 0x0f पूर्ण, अणु  49, 0x0f पूर्ण,
		अणु  50, 0x00 पूर्ण, अणु  51, 0x02 पूर्ण, अणु  52, 0x02 पूर्ण, अणु  53, 0x02 पूर्ण,
		अणु  80, 0x0c पूर्ण, अणु  83, 0x42 पूर्ण, अणु  84, 0x42 पूर्ण, अणु  85, 0x41 पूर्ण,
		अणु  86, 0x14 पूर्ण, अणु  89, 0x88 पूर्ण, अणु  90, 0x01 पूर्ण, अणु  91, 0x00 पूर्ण,
		अणु  92, 0x02 पूर्ण, अणु  93, 0x0c पूर्ण, अणु  94, 0x1c पूर्ण, अणु  95, 0x27 पूर्ण,
		अणु  98, 0x49 पूर्ण, अणु  99, 0x27 पूर्ण, अणु 102, 0x76 पूर्ण, अणु 103, 0x27 पूर्ण,
		अणु 112, 0x01 पूर्ण, अणु 113, 0x0e पूर्ण, अणु 114, 0x02 पूर्ण, अणु 115, 0x0c पूर्ण,
		अणु 118, 0x0c पूर्ण, अणु 121, 0x30 पूर्ण, अणु 130, 0x00 पूर्ण, अणु 131, 0x00 पूर्ण,
		अणु 132, 0xfc पूर्ण, अणु 134, 0x00 पूर्ण, अणु 136, 0x00 पूर्ण, अणु 138, 0x00 पूर्ण,
		अणु 139, 0x00 पूर्ण, अणु 140, 0x00 पूर्ण, अणु 141, 0xfc पूर्ण, अणु 143, 0x00 पूर्ण,
		अणु 145, 0x00 पूर्ण, अणु 147, 0x00 पूर्ण, अणु 148, 0x00 पूर्ण, अणु 149, 0x00 पूर्ण,
		अणु 150, 0xfc पूर्ण, अणु 152, 0x00 पूर्ण, अणु 154, 0x00 पूर्ण, अणु 156, 0x00 पूर्ण,
		अणु 157, 0x00 पूर्ण,
	पूर्ण;

	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(nl8048_init_seq); ++i) अणु
		ret = nl8048_ग_लिखो(lcd, nl8048_init_seq[i].addr,
				   nl8048_init_seq[i].data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	udelay(20);

	वापस nl8048_ग_लिखो(lcd, 2, 0x00);
पूर्ण

अटल पूर्णांक nl8048_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा nl8048_panel *lcd = to_nl8048_device(panel);

	gpiod_set_value_cansleep(lcd->reset_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक nl8048_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा nl8048_panel *lcd = to_nl8048_device(panel);

	gpiod_set_value_cansleep(lcd->reset_gpio, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode nl8048_mode = अणु
	/*  NEC PIX Clock Ratings MIN:21.8MHz TYP:23.8MHz MAX:25.7MHz */
	.घड़ी	= 23800,
	.hdisplay = 800,
	.hsync_start = 800 + 6,
	.hsync_end = 800 + 6 + 1,
	.htotal = 800 + 6 + 1 + 4,
	.vdisplay = 480,
	.vsync_start = 480 + 3,
	.vsync_end = 480 + 3 + 1,
	.vtotal = 480 + 3 + 1 + 4,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm = 89,
	.height_mm = 53,
पूर्ण;

अटल पूर्णांक nl8048_get_modes(काष्ठा drm_panel *panel,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &nl8048_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = nl8048_mode.width_mm;
	connector->display_info.height_mm = nl8048_mode.height_mm;
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_HIGH
					  | DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE
					  | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs nl8048_funcs = अणु
	.disable = nl8048_disable,
	.enable = nl8048_enable,
	.get_modes = nl8048_get_modes,
पूर्ण;

अटल पूर्णांक __maybe_unused nl8048_suspend(काष्ठा device *dev)
अणु
	काष्ठा nl8048_panel *lcd = dev_get_drvdata(dev);

	nl8048_ग_लिखो(lcd, 2, 0x01);
	msleep(40);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nl8048_resume(काष्ठा device *dev)
अणु
	काष्ठा nl8048_panel *lcd = dev_get_drvdata(dev);

	/* Reinitialize the panel. */
	spi_setup(lcd->spi);
	nl8048_ग_लिखो(lcd, 2, 0x00);
	nl8048_init(lcd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(nl8048_pm_ops, nl8048_suspend, nl8048_resume);

अटल पूर्णांक nl8048_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा nl8048_panel *lcd;
	पूर्णांक ret;

	lcd = devm_kzalloc(&spi->dev, माप(*lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;

	lcd->reset_gpio = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->reset_gpio)) अणु
		dev_err(&spi->dev, "failed to parse reset gpio\n");
		वापस PTR_ERR(lcd->reset_gpio);
	पूर्ण

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 32;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "failed to setup SPI: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = nl8048_init(lcd);
	अगर (ret < 0)
		वापस ret;

	drm_panel_init(&lcd->panel, &lcd->spi->dev, &nl8048_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&lcd->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक nl8048_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा nl8048_panel *lcd = spi_get_drvdata(spi);

	drm_panel_हटाओ(&lcd->panel);
	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nl8048_of_match[] = अणु
	अणु .compatible = "nec,nl8048hl11", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, nl8048_of_match);

अटल स्थिर काष्ठा spi_device_id nl8048_ids[] = अणु
	अणु "nl8048hl11", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, nl8048_ids);

अटल काष्ठा spi_driver nl8048_driver = अणु
	.probe		= nl8048_probe,
	.हटाओ		= nl8048_हटाओ,
	.id_table	= nl8048_ids,
	.driver		= अणु
		.name	= "panel-nec-nl8048hl11",
		.pm	= &nl8048_pm_ops,
		.of_match_table = nl8048_of_match,
	पूर्ण,
पूर्ण;

module_spi_driver(nl8048_driver);

MODULE_AUTHOR("Erik Gilling <konkers@android.com>");
MODULE_DESCRIPTION("NEC-NL8048HL11 Driver");
MODULE_LICENSE("GPL");
