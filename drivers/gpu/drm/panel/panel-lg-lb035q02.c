<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LG.Philips LB035Q02 LCD Panel Driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Based on the omapdrm-specअगरic panel-lgphilips-lb035q02 driver
 *
 * Copyright (C) 2013 Texas Instruments Incorporated
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * Based on a driver by: Steve Sakoman <steve@sakoman.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा lb035q02_device अणु
	काष्ठा drm_panel panel;

	काष्ठा spi_device *spi;
	काष्ठा gpio_desc *enable_gpio;
पूर्ण;

#घोषणा to_lb035q02_device(p) container_of(p, काष्ठा lb035q02_device, panel)

अटल पूर्णांक lb035q02_ग_लिखो(काष्ठा lb035q02_device *lcd, u16 reg, u16 val)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer index_xfer = अणु
		.len		= 3,
		.cs_change	= 1,
	पूर्ण;
	काष्ठा spi_transfer value_xfer = अणु
		.len		= 3,
	पूर्ण;
	u8	buffer[16];

	spi_message_init(&msg);

	/* रेजिस्टर index */
	buffer[0] = 0x70;
	buffer[1] = 0x00;
	buffer[2] = reg & 0x7f;
	index_xfer.tx_buf = buffer;
	spi_message_add_tail(&index_xfer, &msg);

	/* रेजिस्टर value */
	buffer[4] = 0x72;
	buffer[5] = val >> 8;
	buffer[6] = val;
	value_xfer.tx_buf = buffer + 4;
	spi_message_add_tail(&value_xfer, &msg);

	वापस spi_sync(lcd->spi, &msg);
पूर्ण

अटल पूर्णांक lb035q02_init(काष्ठा lb035q02_device *lcd)
अणु
	/* Init sequence from page 28 of the lb035q02 spec. */
	अटल स्थिर काष्ठा अणु
		u16 index;
		u16 value;
	पूर्ण init_data[] = अणु
		अणु 0x01, 0x6300 पूर्ण,
		अणु 0x02, 0x0200 पूर्ण,
		अणु 0x03, 0x0177 पूर्ण,
		अणु 0x04, 0x04c7 पूर्ण,
		अणु 0x05, 0xffc0 पूर्ण,
		अणु 0x06, 0xe806 पूर्ण,
		अणु 0x0a, 0x4008 पूर्ण,
		अणु 0x0b, 0x0000 पूर्ण,
		अणु 0x0d, 0x0030 पूर्ण,
		अणु 0x0e, 0x2800 पूर्ण,
		अणु 0x0f, 0x0000 पूर्ण,
		अणु 0x16, 0x9f80 पूर्ण,
		अणु 0x17, 0x0a0f पूर्ण,
		अणु 0x1e, 0x00c1 पूर्ण,
		अणु 0x30, 0x0300 पूर्ण,
		अणु 0x31, 0x0007 पूर्ण,
		अणु 0x32, 0x0000 पूर्ण,
		अणु 0x33, 0x0000 पूर्ण,
		अणु 0x34, 0x0707 पूर्ण,
		अणु 0x35, 0x0004 पूर्ण,
		अणु 0x36, 0x0302 पूर्ण,
		अणु 0x37, 0x0202 पूर्ण,
		अणु 0x3a, 0x0a0d पूर्ण,
		अणु 0x3b, 0x0806 पूर्ण,
	पूर्ण;

	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(init_data); ++i) अणु
		ret = lb035q02_ग_लिखो(lcd, init_data[i].index,
				     init_data[i].value);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lb035q02_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा lb035q02_device *lcd = to_lb035q02_device(panel);

	gpiod_set_value_cansleep(lcd->enable_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक lb035q02_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा lb035q02_device *lcd = to_lb035q02_device(panel);

	gpiod_set_value_cansleep(lcd->enable_gpio, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode lb035q02_mode = अणु
	.घड़ी = 6500,
	.hdisplay = 320,
	.hsync_start = 320 + 20,
	.hsync_end = 320 + 20 + 2,
	.htotal = 320 + 20 + 2 + 68,
	.vdisplay = 240,
	.vsync_start = 240 + 4,
	.vsync_end = 240 + 4 + 2,
	.vtotal = 240 + 4 + 2 + 18,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm = 70,
	.height_mm = 53,
पूर्ण;

अटल पूर्णांक lb035q02_get_modes(काष्ठा drm_panel *panel,
			      काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &lb035q02_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = lb035q02_mode.width_mm;
	connector->display_info.height_mm = lb035q02_mode.height_mm;
	/*
	 * FIXME: According to the datasheet pixel data is sampled on the
	 * rising edge of the घड़ी, but the code running on the Gumstix Overo
	 * Palo35 indicates sampling on the negative edge. This should be
	 * tested on a real device.
	 */
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_HIGH
					  | DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE
					  | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs lb035q02_funcs = अणु
	.disable = lb035q02_disable,
	.enable = lb035q02_enable,
	.get_modes = lb035q02_get_modes,
पूर्ण;

अटल पूर्णांक lb035q02_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा lb035q02_device *lcd;
	पूर्णांक ret;

	lcd = devm_kzalloc(&spi->dev, माप(*lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;

	lcd->enable_gpio = devm_gpiod_get(&spi->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->enable_gpio)) अणु
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		वापस PTR_ERR(lcd->enable_gpio);
	पूर्ण

	ret = lb035q02_init(lcd);
	अगर (ret < 0)
		वापस ret;

	drm_panel_init(&lcd->panel, &lcd->spi->dev, &lb035q02_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&lcd->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक lb035q02_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा lb035q02_device *lcd = spi_get_drvdata(spi);

	drm_panel_हटाओ(&lcd->panel);
	drm_panel_disable(&lcd->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lb035q02_of_match[] = अणु
	अणु .compatible = "lgphilips,lb035q02", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, lb035q02_of_match);

अटल स्थिर काष्ठा spi_device_id lb035q02_ids[] = अणु
	अणु "lb035q02", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, lb035q02_ids);

अटल काष्ठा spi_driver lb035q02_driver = अणु
	.probe		= lb035q02_probe,
	.हटाओ		= lb035q02_हटाओ,
	.id_table	= lb035q02_ids,
	.driver		= अणु
		.name	= "panel-lg-lb035q02",
		.of_match_table = lb035q02_of_match,
	पूर्ण,
पूर्ण;

module_spi_driver(lb035q02_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("LG.Philips LB035Q02 LCD Panel driver");
MODULE_LICENSE("GPL");
