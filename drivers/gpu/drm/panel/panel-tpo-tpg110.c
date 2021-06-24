<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Panel driver क्रम the TPO TPG110 400CH LTPS TFT LCD Single Chip
 * Digital Driver.
 *
 * This chip drives a TFT LCD, so it करोes not know what kind of
 * display is actually connected to it, so the width and height of that
 * display needs to be supplied from the machine configuration.
 *
 * Author:
 * Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>

#घोषणा TPG110_TEST			0x00
#घोषणा TPG110_CHIPID			0x01
#घोषणा TPG110_CTRL1			0x02
#घोषणा TPG110_RES_MASK			GENMASK(2, 0)
#घोषणा TPG110_RES_800X480		0x07
#घोषणा TPG110_RES_640X480		0x06
#घोषणा TPG110_RES_480X272		0x05
#घोषणा TPG110_RES_480X640		0x04
#घोषणा TPG110_RES_480X272_D		0x01 /* Dual scan: outमाला_दो 800x480 */
#घोषणा TPG110_RES_400X240_D		0x00 /* Dual scan: outमाला_दो 800x480 */
#घोषणा TPG110_CTRL2			0x03
#घोषणा TPG110_CTRL2_PM			BIT(0)
#घोषणा TPG110_CTRL2_RES_PM_CTRL	BIT(7)

/**
 * काष्ठा tpg110_panel_mode - lookup काष्ठा क्रम the supported modes
 */
काष्ठा tpg110_panel_mode अणु
	/**
	 * @name: the name of this panel
	 */
	स्थिर अक्षर *name;
	/**
	 * @magic: the magic value from the detection रेजिस्टर
	 */
	u32 magic;
	/**
	 * @mode: the DRM display mode क्रम this panel
	 */
	काष्ठा drm_display_mode mode;
	/**
	 * @bus_flags: the DRM bus flags क्रम this panel e.g. inverted घड़ी
	 */
	u32 bus_flags;
पूर्ण;

/**
 * काष्ठा tpg110 - state container क्रम the TPG110 panel
 */
काष्ठा tpg110 अणु
	/**
	 * @dev: the container device
	 */
	काष्ठा device *dev;
	/**
	 * @spi: the corresponding SPI device
	 */
	काष्ठा spi_device *spi;
	/**
	 * @panel: the DRM panel instance क्रम this device
	 */
	काष्ठा drm_panel panel;
	/**
	 * @panel_mode: the panel mode as detected
	 */
	स्थिर काष्ठा tpg110_panel_mode *panel_mode;
	/**
	 * @width: the width of this panel in mm
	 */
	u32 width;
	/**
	 * @height: the height of this panel in mm
	 */
	u32 height;
	/**
	 * @grestb: reset GPIO line
	 */
	काष्ठा gpio_desc *grestb;
पूर्ण;

/*
 * TPG110 modes, these are the simple modes, the dualscan modes that
 * take 400x240 or 480x272 in and display as 800x480 are not listed.
 */
अटल स्थिर काष्ठा tpg110_panel_mode tpg110_modes[] = अणु
	अणु
		.name = "800x480 RGB",
		.magic = TPG110_RES_800X480,
		.mode = अणु
			.घड़ी = 33200,
			.hdisplay = 800,
			.hsync_start = 800 + 40,
			.hsync_end = 800 + 40 + 1,
			.htotal = 800 + 40 + 1 + 216,
			.vdisplay = 480,
			.vsync_start = 480 + 10,
			.vsync_end = 480 + 10 + 1,
			.vtotal = 480 + 10 + 1 + 35,
		पूर्ण,
		.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
	पूर्ण,
	अणु
		.name = "640x480 RGB",
		.magic = TPG110_RES_640X480,
		.mode = अणु
			.घड़ी = 25200,
			.hdisplay = 640,
			.hsync_start = 640 + 24,
			.hsync_end = 640 + 24 + 1,
			.htotal = 640 + 24 + 1 + 136,
			.vdisplay = 480,
			.vsync_start = 480 + 18,
			.vsync_end = 480 + 18 + 1,
			.vtotal = 480 + 18 + 1 + 27,
		पूर्ण,
		.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
	पूर्ण,
	अणु
		.name = "480x272 RGB",
		.magic = TPG110_RES_480X272,
		.mode = अणु
			.घड़ी = 9000,
			.hdisplay = 480,
			.hsync_start = 480 + 2,
			.hsync_end = 480 + 2 + 1,
			.htotal = 480 + 2 + 1 + 43,
			.vdisplay = 272,
			.vsync_start = 272 + 2,
			.vsync_end = 272 + 2 + 1,
			.vtotal = 272 + 2 + 1 + 12,
		पूर्ण,
		.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
	पूर्ण,
	अणु
		.name = "480x640 RGB",
		.magic = TPG110_RES_480X640,
		.mode = अणु
			.घड़ी = 20500,
			.hdisplay = 480,
			.hsync_start = 480 + 2,
			.hsync_end = 480 + 2 + 1,
			.htotal = 480 + 2 + 1 + 43,
			.vdisplay = 640,
			.vsync_start = 640 + 4,
			.vsync_end = 640 + 4 + 1,
			.vtotal = 640 + 4 + 1 + 8,
		पूर्ण,
		.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
	पूर्ण,
	अणु
		.name = "400x240 RGB",
		.magic = TPG110_RES_400X240_D,
		.mode = अणु
			.घड़ी = 8300,
			.hdisplay = 400,
			.hsync_start = 400 + 20,
			.hsync_end = 400 + 20 + 1,
			.htotal = 400 + 20 + 1 + 108,
			.vdisplay = 240,
			.vsync_start = 240 + 2,
			.vsync_end = 240 + 2 + 1,
			.vtotal = 240 + 2 + 1 + 20,
		पूर्ण,
		.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा tpg110 *
to_tpg110(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा tpg110, panel);
पूर्ण

अटल u8 tpg110_पढ़ोग_लिखो_reg(काष्ठा tpg110 *tpg, bool ग_लिखो,
			       u8 address, u8 outval)
अणु
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[2];
	u8 buf[2];
	पूर्णांक ret;

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	अगर (ग_लिखो) अणु
		/*
		 * Clear address bit 0, 1 when writing, just to be sure
		 * The actual bit indicating a ग_लिखो here is bit 1, bit
		 * 0 is just surplus to pad it up to 8 bits.
		 */
		buf[0] = address << 2;
		buf[0] &= ~0x03;
		buf[1] = outval;

		t[0].bits_per_word = 8;
		t[0].tx_buf = &buf[0];
		t[0].len = 1;

		t[1].tx_buf = &buf[1];
		t[1].len = 1;
		t[1].bits_per_word = 8;
	पूर्ण अन्यथा अणु
		/* Set address bit 0 to 1 to पढ़ो */
		buf[0] = address << 1;
		buf[0] |= 0x01;

		/*
		 * The last bit/घड़ी is Hi-Z turnaround cycle, so we need
		 * to send only 7 bits here. The 8th bit is the high impedance
		 * turn-around cycle.
		 */
		t[0].bits_per_word = 7;
		t[0].tx_buf = &buf[0];
		t[0].len = 1;

		t[1].rx_buf = &buf[1];
		t[1].len = 1;
		t[1].bits_per_word = 8;
	पूर्ण

	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);
	ret = spi_sync(tpg->spi, &m);
	अगर (ret) अणु
		dev_err(tpg->dev, "SPI message error %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (ग_लिखो)
		वापस 0;
	/* Read */
	वापस buf[1];
पूर्ण

अटल u8 tpg110_पढ़ो_reg(काष्ठा tpg110 *tpg, u8 address)
अणु
	वापस tpg110_पढ़ोग_लिखो_reg(tpg, false, address, 0);
पूर्ण

अटल व्योम tpg110_ग_लिखो_reg(काष्ठा tpg110 *tpg, u8 address, u8 outval)
अणु
	tpg110_पढ़ोग_लिखो_reg(tpg, true, address, outval);
पूर्ण

अटल पूर्णांक tpg110_startup(काष्ठा tpg110 *tpg)
अणु
	u8 val;
	पूर्णांक i;

	/* De-निश्चित the reset संकेत */
	gpiod_set_value_cansleep(tpg->grestb, 0);
	usleep_range(1000, 2000);
	dev_dbg(tpg->dev, "de-asserted GRESTB\n");

	/* Test display communication */
	tpg110_ग_लिखो_reg(tpg, TPG110_TEST, 0x55);
	val = tpg110_पढ़ो_reg(tpg, TPG110_TEST);
	अगर (val != 0x55) अणु
		dev_err(tpg->dev, "failed communication test\n");
		वापस -ENODEV;
	पूर्ण

	val = tpg110_पढ़ो_reg(tpg, TPG110_CHIPID);
	dev_info(tpg->dev, "TPG110 chip ID: %d version: %d\n",
		 val >> 4, val & 0x0f);

	/* Show display resolution */
	val = tpg110_पढ़ो_reg(tpg, TPG110_CTRL1);
	val &= TPG110_RES_MASK;
	चयन (val) अणु
	हाल TPG110_RES_400X240_D:
		dev_info(tpg->dev, "IN 400x240 RGB -> OUT 800x480 RGB (dual scan)\n");
		अवरोध;
	हाल TPG110_RES_480X272_D:
		dev_info(tpg->dev, "IN 480x272 RGB -> OUT 800x480 RGB (dual scan)\n");
		अवरोध;
	हाल TPG110_RES_480X640:
		dev_info(tpg->dev, "480x640 RGB\n");
		अवरोध;
	हाल TPG110_RES_480X272:
		dev_info(tpg->dev, "480x272 RGB\n");
		अवरोध;
	हाल TPG110_RES_640X480:
		dev_info(tpg->dev, "640x480 RGB\n");
		अवरोध;
	हाल TPG110_RES_800X480:
		dev_info(tpg->dev, "800x480 RGB\n");
		अवरोध;
	शेष:
		dev_err(tpg->dev, "ILLEGAL RESOLUTION 0x%02x\n", val);
		अवरोध;
	पूर्ण

	/* From the producer side, this is the same resolution */
	अगर (val == TPG110_RES_480X272_D)
		val = TPG110_RES_480X272;

	क्रम (i = 0; i < ARRAY_SIZE(tpg110_modes); i++) अणु
		स्थिर काष्ठा tpg110_panel_mode *pm;

		pm = &tpg110_modes[i];
		अगर (pm->magic == val) अणु
			tpg->panel_mode = pm;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(tpg110_modes)) अणु
		dev_err(tpg->dev, "unsupported mode (%02x) detected\n", val);
		वापस -ENODEV;
	पूर्ण

	val = tpg110_पढ़ो_reg(tpg, TPG110_CTRL2);
	dev_info(tpg->dev, "resolution and standby is controlled by %s\n",
		 (val & TPG110_CTRL2_RES_PM_CTRL) ? "software" : "hardware");
	/* Take control over resolution and standby */
	val |= TPG110_CTRL2_RES_PM_CTRL;
	tpg110_ग_लिखो_reg(tpg, TPG110_CTRL2, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tpg110_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा tpg110 *tpg = to_tpg110(panel);
	u8 val;

	/* Put chip पूर्णांकo standby */
	val = tpg110_पढ़ो_reg(tpg, TPG110_CTRL2_PM);
	val &= ~TPG110_CTRL2_PM;
	tpg110_ग_लिखो_reg(tpg, TPG110_CTRL2_PM, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tpg110_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा tpg110 *tpg = to_tpg110(panel);
	u8 val;

	/* Take chip out of standby */
	val = tpg110_पढ़ो_reg(tpg, TPG110_CTRL2_PM);
	val |= TPG110_CTRL2_PM;
	tpg110_ग_लिखो_reg(tpg, TPG110_CTRL2_PM, val);

	वापस 0;
पूर्ण

/**
 * tpg110_get_modes() - वापस the appropriate mode
 * @panel: the panel to get the mode क्रम
 * @connector: reference to the central DRM connector control काष्ठाure
 *
 * This currently करोes not present a क्रमest of modes, instead it
 * presents the mode that is configured क्रम the प्रणाली under use,
 * and which is detected by पढ़ोing the रेजिस्टरs of the display.
 */
अटल पूर्णांक tpg110_get_modes(काष्ठा drm_panel *panel,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा tpg110 *tpg = to_tpg110(panel);
	काष्ठा drm_display_mode *mode;

	connector->display_info.width_mm = tpg->width;
	connector->display_info.height_mm = tpg->height;
	connector->display_info.bus_flags = tpg->panel_mode->bus_flags;

	mode = drm_mode_duplicate(connector->dev, &tpg->panel_mode->mode);
	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	mode->width_mm = tpg->width;
	mode->height_mm = tpg->height;

	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs tpg110_drm_funcs = अणु
	.disable = tpg110_disable,
	.enable = tpg110_enable,
	.get_modes = tpg110_get_modes,
पूर्ण;

अटल पूर्णांक tpg110_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा tpg110 *tpg;
	पूर्णांक ret;

	tpg = devm_kzalloc(dev, माप(*tpg), GFP_KERNEL);
	अगर (!tpg)
		वापस -ENOMEM;
	tpg->dev = dev;

	/* We get the physical display dimensions from the DT */
	ret = of_property_पढ़ो_u32(np, "width-mm", &tpg->width);
	अगर (ret)
		dev_err(dev, "no panel width specified\n");
	ret = of_property_पढ़ो_u32(np, "height-mm", &tpg->height);
	अगर (ret)
		dev_err(dev, "no panel height specified\n");

	/* This निश्चितs the GRESTB संकेत, putting the display पूर्णांकo reset */
	tpg->grestb = devm_gpiod_get(dev, "grestb", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tpg->grestb)) अणु
		dev_err(dev, "no GRESTB GPIO\n");
		वापस -ENODEV;
	पूर्ण

	spi->bits_per_word = 8;
	spi->mode |= SPI_3WIRE_HIZ;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(dev, "spi setup failed.\n");
		वापस ret;
	पूर्ण
	tpg->spi = spi;

	ret = tpg110_startup(tpg);
	अगर (ret)
		वापस ret;

	drm_panel_init(&tpg->panel, dev, &tpg110_drm_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	ret = drm_panel_of_backlight(&tpg->panel);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, tpg);

	drm_panel_add(&tpg->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक tpg110_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा tpg110 *tpg = spi_get_drvdata(spi);

	drm_panel_हटाओ(&tpg->panel);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tpg110_match[] = अणु
	अणु .compatible = "tpo,tpg110", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tpg110_match);

अटल काष्ठा spi_driver tpg110_driver = अणु
	.probe		= tpg110_probe,
	.हटाओ		= tpg110_हटाओ,
	.driver		= अणु
		.name	= "tpo-tpg110-panel",
		.of_match_table = tpg110_match,
	पूर्ण,
पूर्ण;
module_spi_driver(tpg110_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("TPO TPG110 panel driver");
MODULE_LICENSE("GPL v2");
