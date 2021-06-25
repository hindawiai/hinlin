<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ilitek ILI9322 TFT LCD drm_panel driver.
 *
 * This panel can be configured to support:
 * - 8-bit serial RGB पूर्णांकerface
 * - 24-bit parallel RGB पूर्णांकerface
 * - 8-bit ITU-R BT.601 पूर्णांकerface
 * - 8-bit ITU-R BT.656 पूर्णांकerface
 * - Up to 320RGBx240 करोts resolution TFT LCD displays
 * - Scaling, brightness and contrast
 *
 * The scaling means that the display accepts a 640x480 or 720x480
 * input and rescales it to fit to the 320x240 display. So what we
 * present to the प्रणाली is something अन्यथा than what comes out on the
 * actual display.
 *
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Derived from drivers/drm/gpu/panel/panel-samsung-ld9040.c
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <video/mipi_display.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा ILI9322_CHIP_ID			0x00
#घोषणा ILI9322_CHIP_ID_MAGIC		0x96

/*
 * Voltage on the communication पूर्णांकerface, from 0.7 (0x00)
 * to 1.32 (0x1f) बार the VREG1OUT voltage in 2% increments.
 * 1.00 (0x0f) is the शेष.
 */
#घोषणा ILI9322_VCOM_AMP		0x01

/*
 * High voltage on the communication संकेतs, from 0.37 (0x00) to
 * 1.0 (0x3f) बार the VREGOUT1 voltage in 1% increments.
 * 0.83 (0x2e) is the शेष.
 */
#घोषणा ILI9322_VCOM_HIGH		0x02

/*
 * VREG1 voltage regulator from 3.6V (0x00) to 6.0V (0x18) in 0.1V
 * increments. 5.4V (0x12) is the शेष. This is the reference
 * voltage क्रम the VCOM levels and the greyscale level.
 */
#घोषणा ILI9322_VREG1_VOLTAGE		0x03

/* Describes the incoming संकेत */
#घोषणा ILI9322_ENTRY			0x06
/* 0 = right-to-left, 1 = left-to-right (शेष), horizontal flip */
#घोषणा ILI9322_ENTRY_Hसूची		BIT(0)
/* 0 = करोwn-to-up, 1 = up-to-करोwn (शेष), vertical flip  */
#घोषणा ILI9322_ENTRY_Vसूची		BIT(1)
/* NTSC, PAL or स्वतःdetect */
#घोषणा ILI9322_ENTRY_NTSC		(0 << 2)
#घोषणा ILI9322_ENTRY_PAL		(1 << 2)
#घोषणा ILI9322_ENTRY_AUTODETECT	(3 << 2)
/* Input क्रमmat */
#घोषणा ILI9322_ENTRY_SERIAL_RGB_THROUGH (0 << 4)
#घोषणा ILI9322_ENTRY_SERIAL_RGB_ALIGNED (1 << 4)
#घोषणा ILI9322_ENTRY_SERIAL_RGB_DUMMY_320X240 (2 << 4)
#घोषणा ILI9322_ENTRY_SERIAL_RGB_DUMMY_360X240 (3 << 4)
#घोषणा ILI9322_ENTRY_DISABLE_1		(4 << 4)
#घोषणा ILI9322_ENTRY_PARALLEL_RGB_THROUGH (5 << 4)
#घोषणा ILI9322_ENTRY_PARALLEL_RGB_ALIGNED (6 << 4)
#घोषणा ILI9322_ENTRY_YUV_640Y_320CBCR_25_54_MHZ (7 << 4)
#घोषणा ILI9322_ENTRY_YUV_720Y_360CBCR_27_MHZ (8 << 4)
#घोषणा ILI9322_ENTRY_DISABLE_2		(9 << 4)
#घोषणा ILI9322_ENTRY_ITU_R_BT_656_720X360 (10 << 4)
#घोषणा ILI9322_ENTRY_ITU_R_BT_656_640X320 (11 << 4)

/* Power control */
#घोषणा ILI9322_POW_CTRL		0x07
#घोषणा ILI9322_POW_CTRL_STB		BIT(0) /* 0 = standby, 1 = normal */
#घोषणा ILI9322_POW_CTRL_VGL		BIT(1) /* 0 = off, 1 = on  */
#घोषणा ILI9322_POW_CTRL_VGH		BIT(2) /* 0 = off, 1 = on  */
#घोषणा ILI9322_POW_CTRL_DDVDH		BIT(3) /* 0 = off, 1 = on  */
#घोषणा ILI9322_POW_CTRL_VCOM		BIT(4) /* 0 = off, 1 = on  */
#घोषणा ILI9322_POW_CTRL_VCL		BIT(5) /* 0 = off, 1 = on  */
#घोषणा ILI9322_POW_CTRL_AUTO		BIT(6) /* 0 = पूर्णांकeractive, 1 = स्वतः */
#घोषणा ILI9322_POW_CTRL_STANDBY	(ILI9322_POW_CTRL_VGL | \
					 ILI9322_POW_CTRL_VGH | \
					 ILI9322_POW_CTRL_DDVDH | \
					 ILI9322_POW_CTRL_VCL | \
					 ILI9322_POW_CTRL_AUTO | \
					 BIT(7))
#घोषणा ILI9322_POW_CTRL_DEFAULT	(ILI9322_POW_CTRL_STANDBY | \
					 ILI9322_POW_CTRL_STB)

/* Vertical back porch bits 0..5 */
#घोषणा ILI9322_VBP			0x08

/* Horizontal back porch, 8 bits */
#घोषणा ILI9322_HBP			0x09

/*
 * Polarity settings:
 * 1 = positive polarity
 * 0 = negative polarity
 */
#घोषणा ILI9322_POL			0x0a
#घोषणा ILI9322_POL_DCLK		BIT(0) /* 1 शेष */
#घोषणा ILI9322_POL_HSYNC		BIT(1) /* 0 शेष */
#घोषणा ILI9322_POL_VSYNC		BIT(2) /* 0 शेष */
#घोषणा ILI9322_POL_DE			BIT(3) /* 1 शेष */
/*
 * 0 means YCBCR are ordered Cb0,Y0,Cr0,Y1,Cb2,Y2,Cr2,Y3 (शेष)
 *   in RGB mode this means RGB comes in RGBRGB
 * 1 means YCBCR are ordered Cr0,Y0,Cb0,Y1,Cr2,Y2,Cb2,Y3
 *   in RGB mode this means RGB comes in BGRBGR
 */
#घोषणा ILI9322_POL_YCBCR_MODE		BIT(4)
/* Formula A क्रम YCbCR->RGB = 0, Formula B = 1 */
#घोषणा ILI9322_POL_FORMULA		BIT(5)
/* Reverse polarity: 0 = 0..255, 1 = 255..0 */
#घोषणा ILI9322_POL_REV			BIT(6)

#घोषणा ILI9322_IF_CTRL			0x0b
#घोषणा ILI9322_IF_CTRL_HSYNC_VSYNC	0x00
#घोषणा ILI9322_IF_CTRL_HSYNC_VSYNC_DE	BIT(2)
#घोषणा ILI9322_IF_CTRL_DE_ONLY		BIT(3)
#घोषणा ILI9322_IF_CTRL_SYNC_DISABLED	(BIT(2) | BIT(3))
#घोषणा ILI9322_IF_CTRL_LINE_INVERSION	BIT(0) /* Not set means frame inv */

#घोषणा ILI9322_GLOBAL_RESET		0x04
#घोषणा ILI9322_GLOBAL_RESET_ASSERT	0x00 /* bit 0 = 0 -> reset */

/*
 * 4+4 bits of negative and positive gamma correction
 * Upper nybble, bits 4-7 are negative gamma
 * Lower nybble, bits 0-3 are positive gamma
 */
#घोषणा ILI9322_GAMMA_1			0x10
#घोषणा ILI9322_GAMMA_2			0x11
#घोषणा ILI9322_GAMMA_3			0x12
#घोषणा ILI9322_GAMMA_4			0x13
#घोषणा ILI9322_GAMMA_5			0x14
#घोषणा ILI9322_GAMMA_6			0x15
#घोषणा ILI9322_GAMMA_7			0x16
#घोषणा ILI9322_GAMMA_8			0x17

/*
 * क्रमागत ili9322_input - the क्रमmat of the incoming संकेत to the panel
 *
 * The panel can be connected to various input streams and four of them can
 * be selected by electronic straps on the display. However it is possible
 * to select another mode or override the electronic शेष with this
 * setting.
 */
क्रमागत ili9322_input अणु
	ILI9322_INPUT_SRGB_THROUGH = 0x0,
	ILI9322_INPUT_SRGB_ALIGNED = 0x1,
	ILI9322_INPUT_SRGB_DUMMY_320X240 = 0x2,
	ILI9322_INPUT_SRGB_DUMMY_360X240 = 0x3,
	ILI9322_INPUT_DISABLED_1 = 0x4,
	ILI9322_INPUT_PRGB_THROUGH = 0x5,
	ILI9322_INPUT_PRGB_ALIGNED = 0x6,
	ILI9322_INPUT_YUV_640X320_YCBCR = 0x7,
	ILI9322_INPUT_YUV_720X360_YCBCR = 0x8,
	ILI9322_INPUT_DISABLED_2 = 0x9,
	ILI9322_INPUT_ITU_R_BT656_720X360_YCBCR = 0xa,
	ILI9322_INPUT_ITU_R_BT656_640X320_YCBCR = 0xb,
	ILI9322_INPUT_UNKNOWN = 0xc,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ili9322_inमाला_दो[] = अणु
	"8 bit serial RGB through",
	"8 bit serial RGB aligned",
	"8 bit serial RGB dummy 320x240",
	"8 bit serial RGB dummy 360x240",
	"disabled 1",
	"24 bit parallel RGB through",
	"24 bit parallel RGB aligned",
	"24 bit YUV 640Y 320CbCr",
	"24 bit YUV 720Y 360CbCr",
	"disabled 2",
	"8 bit ITU-R BT.656 720Y 360CbCr",
	"8 bit ITU-R BT.656 640Y 320CbCr",
पूर्ण;

/**
 * काष्ठा ili9322_config - the प्रणाली specअगरic ILI9322 configuration
 * @width_mm: physical panel width [mm]
 * @height_mm: physical panel height [mm]
 * @flip_horizontal: flip the image horizontally (right-to-left scan)
 * (only in RGB and YUV modes)
 * @flip_vertical: flip the image vertically (करोwn-to-up scan)
 * (only in RGB and YUV modes)
 * @input: the input/entry type used in this प्रणाली, अगर this is set to
 * ILI9322_INPUT_UNKNOWN the driver will try to figure it out by probing
 * the hardware
 * @vreg1out_mv: the output in microvolts क्रम the VREGOUT1 regulator used
 * to drive the physical display. Valid ranges are 3600 thru 6000 in 100
 * microvolt increments. If not specअगरied, hardware शेषs will be
 * used (4.5V).
 * @vcom_high_percent: the percentage of VREGOUT1 used क्रम the peak
 * voltage on the communications link. Valid ranges are 37 thru 100
 * percent. If not specअगरied, hardware शेषs will be used (91%).
 * @vcom_amplitude_percent: the percentage of VREGOUT1 used क्रम the
 * peak-to-peak amplitude of the communcation संकेतs to the physical
 * display. Valid ranges are 70 thru 132 percent in increments अगर two
 * percent. Odd percentages will be truncated. If not specअगरied, hardware
 * शेषs will be used (114%).
 * @dclk_active_high: data/pixel घड़ी active high, data will be घड़ीed
 * in on the rising edge of the DCLK (this is usually the हाल).
 * @syncmode: The synchronization mode, what sync संकेतs are emitted.
 * See the क्रमागत क्रम details.
 * @de_active_high: DE (data entry) is active high
 * @hsync_active_high: HSYNC is active high
 * @vsync_active_high: VSYNC is active high
 * @gamma_corr_pos: a set of 8 nybbles describing positive
 * gamma correction क्रम voltages V1 thru V8. Valid range 0..15
 * @gamma_corr_neg: a set of 8 nybbles describing negative
 * gamma correction क्रम voltages V1 thru V8. Valid range 0..15
 *
 * These adjust what grayscale voltage will be output क्रम input data V1 = 0,
 * V2 = 16, V3 = 48, V4 = 96, V5 = 160, V6 = 208, V7 = 240 and V8 = 255.
 * The curve is shaped like this:
 *
 *  ^
 *  |                                                        V8
 *  |                                                   V7
 *  |                                          V6
 *  |                               V5
 *  |                    V4
 *  |            V3
 *  |     V2
 *  | V1
 *  +----------------------------------------------------------->
 *    0   16     48      96         160        208      240  255
 *
 * The negative and postive gamma values adjust the V1 thru V8 up/करोwn
 * according to the datasheet specअगरications. This is a property of the
 * physical display connected to the display controller and may vary.
 * If defined, both arrays must be supplied in full. If the properties
 * are not supplied, hardware शेषs will be used.
 */
काष्ठा ili9322_config अणु
	u32 width_mm;
	u32 height_mm;
	bool flip_horizontal;
	bool flip_vertical;
	क्रमागत ili9322_input input;
	u32 vreg1out_mv;
	u32 vcom_high_percent;
	u32 vcom_amplitude_percent;
	bool dclk_active_high;
	bool de_active_high;
	bool hsync_active_high;
	bool vsync_active_high;
	u8 syncmode;
	u8 gamma_corr_pos[8];
	u8 gamma_corr_neg[8];
पूर्ण;

काष्ठा ili9322 अणु
	काष्ठा device *dev;
	स्थिर काष्ठा ili9322_config *conf;
	काष्ठा drm_panel panel;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[3];
	काष्ठा gpio_desc *reset_gpio;
	क्रमागत ili9322_input input;
	काष्ठा videomode vm;
	u8 gamma[8];
	u8 vreg1out;
	u8 vcom_high;
	u8 vcom_amplitude;
पूर्ण;

अटल अंतरभूत काष्ठा ili9322 *panel_to_ili9322(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा ili9322, panel);
पूर्ण

अटल पूर्णांक ili9322_regmap_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				    माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 buf[2];

	/* Clear bit 7 to ग_लिखो */
	स_नकल(buf, data, 2);
	buf[0] &= ~0x80;

	dev_dbg(dev, "WRITE: %02x %02x\n", buf[0], buf[1]);
	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, 2, शून्य, 0);
पूर्ण

अटल पूर्णांक ili9322_regmap_spi_पढ़ो(व्योम *context, स्थिर व्योम *reg,
				   माप_प्रकार reg_size, व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 buf[1];

	/* Set bit 7 to 1 to पढ़ो */
	स_नकल(buf, reg, 1);
	dev_dbg(dev, "READ: %02x reg size = %zu, val size = %zu\n",
		buf[0], reg_size, val_size);
	buf[0] |= 0x80;

	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, 1, val, 1);
पूर्ण

अटल काष्ठा regmap_bus ili9322_regmap_bus = अणु
	.ग_लिखो = ili9322_regmap_spi_ग_लिखो,
	.पढ़ो = ili9322_regmap_spi_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल bool ili9322_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस false;
पूर्ण

अटल bool ili9322_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Just रेजिस्टर 0 is पढ़ो-only */
	अगर (reg == 0x00)
		वापस false;
	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config ili9322_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x44,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = ili9322_अस्थिर_reg,
	.ग_लिखोable_reg = ili9322_ग_लिखोable_reg,
पूर्ण;

अटल पूर्णांक ili9322_init(काष्ठा drm_panel *panel, काष्ठा ili9322 *ili)
अणु
	u8 reg;
	पूर्णांक ret;
	पूर्णांक i;

	/* Reset display */
	ret = regmap_ग_लिखो(ili->regmap, ILI9322_GLOBAL_RESET,
			   ILI9322_GLOBAL_RESET_ASSERT);
	अगर (ret) अणु
		dev_err(ili->dev, "can't issue GRESET (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Set up the मुख्य voltage regulator */
	अगर (ili->vreg1out != U8_MAX) अणु
		ret = regmap_ग_लिखो(ili->regmap, ILI9322_VREG1_VOLTAGE,
				   ili->vreg1out);
		अगर (ret) अणु
			dev_err(ili->dev, "can't set up VREG1OUT (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ili->vcom_amplitude != U8_MAX) अणु
		ret = regmap_ग_लिखो(ili->regmap, ILI9322_VCOM_AMP,
				   ili->vcom_amplitude);
		अगर (ret) अणु
			dev_err(ili->dev,
				"can't set up VCOM amplitude (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ili->vcom_high != U8_MAX) अणु
		ret = regmap_ग_लिखो(ili->regmap, ILI9322_VCOM_HIGH,
				   ili->vcom_high);
		अगर (ret) अणु
			dev_err(ili->dev, "can't set up VCOM high (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Set up gamma correction */
	क्रम (i = 0; i < ARRAY_SIZE(ili->gamma); i++) अणु
		ret = regmap_ग_लिखो(ili->regmap, ILI9322_GAMMA_1 + i,
				   ili->gamma[i]);
		अगर (ret) अणु
			dev_err(ili->dev,
				"can't write gamma V%d to 0x%02x (%d)\n",
				i + 1, ILI9322_GAMMA_1 + i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Polarity and inverted color order क्रम RGB input.
	 * None of this applies in the BT.656 mode.
	 */
	reg = 0;
	अगर (ili->conf->dclk_active_high)
		reg = ILI9322_POL_DCLK;
	अगर (ili->conf->de_active_high)
		reg |= ILI9322_POL_DE;
	अगर (ili->conf->hsync_active_high)
		reg |= ILI9322_POL_HSYNC;
	अगर (ili->conf->vsync_active_high)
		reg |= ILI9322_POL_VSYNC;
	ret = regmap_ग_लिखो(ili->regmap, ILI9322_POL, reg);
	अगर (ret) अणु
		dev_err(ili->dev, "can't write POL register (%d)\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Set up पूर्णांकerface control.
	 * This is not used in the BT.656 mode (no H/Vsync or DE संकेतs).
	 */
	reg = ili->conf->syncmode;
	reg |= ILI9322_IF_CTRL_LINE_INVERSION;
	ret = regmap_ग_लिखो(ili->regmap, ILI9322_IF_CTRL, reg);
	अगर (ret) अणु
		dev_err(ili->dev, "can't write IF CTRL register (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Set up the input mode */
	reg = (ili->input << 4);
	/* These are inverted, setting to 1 is the शेष, clearing flips */
	अगर (!ili->conf->flip_horizontal)
		reg |= ILI9322_ENTRY_Hसूची;
	अगर (!ili->conf->flip_vertical)
		reg |= ILI9322_ENTRY_Vसूची;
	reg |= ILI9322_ENTRY_AUTODETECT;
	ret = regmap_ग_लिखो(ili->regmap, ILI9322_ENTRY, reg);
	अगर (ret) अणु
		dev_err(ili->dev, "can't write ENTRY reg (%d)\n", ret);
		वापस ret;
	पूर्ण
	dev_info(ili->dev, "display is in %s mode, syncmode %02x\n",
		 ili9322_inमाला_दो[ili->input],
		 ili->conf->syncmode);

	dev_info(ili->dev, "initialized display\n");

	वापस 0;
पूर्ण

/*
 * This घातer-on sequence अगर from the datasheet, page 57.
 */
अटल पूर्णांक ili9322_घातer_on(काष्ठा ili9322 *ili)
अणु
	पूर्णांक ret;

	/* Assert RESET */
	gpiod_set_value(ili->reset_gpio, 1);

	ret = regulator_bulk_enable(ARRAY_SIZE(ili->supplies), ili->supplies);
	अगर (ret < 0) अणु
		dev_err(ili->dev, "unable to enable regulators\n");
		वापस ret;
	पूर्ण
	msleep(20);

	/* De-निश्चित RESET */
	gpiod_set_value(ili->reset_gpio, 0);

	msleep(10);

	वापस 0;
पूर्ण

अटल पूर्णांक ili9322_घातer_off(काष्ठा ili9322 *ili)
अणु
	वापस regulator_bulk_disable(ARRAY_SIZE(ili->supplies), ili->supplies);
पूर्ण

अटल पूर्णांक ili9322_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा ili9322 *ili = panel_to_ili9322(panel);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ili->regmap, ILI9322_POW_CTRL,
			   ILI9322_POW_CTRL_STANDBY);
	अगर (ret) अणु
		dev_err(ili->dev, "unable to go to standby mode\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ili9322_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ili9322 *ili = panel_to_ili9322(panel);

	वापस ili9322_घातer_off(ili);
पूर्ण

अटल पूर्णांक ili9322_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ili9322 *ili = panel_to_ili9322(panel);
	पूर्णांक ret;

	ret = ili9322_घातer_on(ili);
	अगर (ret < 0)
		वापस ret;

	ret = ili9322_init(panel, ili);
	अगर (ret < 0)
		ili9322_unprepare(panel);

	वापस ret;
पूर्ण

अटल पूर्णांक ili9322_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा ili9322 *ili = panel_to_ili9322(panel);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(ili->regmap, ILI9322_POW_CTRL,
			   ILI9322_POW_CTRL_DEFAULT);
	अगर (ret) अणु
		dev_err(ili->dev, "unable to enable panel\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Serial RGB modes */
अटल स्थिर काष्ठा drm_display_mode srgb_320x240_mode = अणु
	.घड़ी = 24535,
	.hdisplay = 320,
	.hsync_start = 320 + 359,
	.hsync_end = 320 + 359 + 1,
	.htotal = 320 + 359 + 1 + 241,
	.vdisplay = 240,
	.vsync_start = 240 + 4,
	.vsync_end = 240 + 4 + 1,
	.vtotal = 262,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode srgb_360x240_mode = अणु
	.घड़ी = 27000,
	.hdisplay = 360,
	.hsync_start = 360 + 35,
	.hsync_end = 360 + 35 + 1,
	.htotal = 360 + 35 + 1 + 241,
	.vdisplay = 240,
	.vsync_start = 240 + 21,
	.vsync_end = 240 + 21 + 1,
	.vtotal = 262,
	.flags = 0,
पूर्ण;

/* This is the only mode listed क्रम parallel RGB in the datasheet */
अटल स्थिर काष्ठा drm_display_mode prgb_320x240_mode = अणु
	.घड़ी = 64000,
	.hdisplay = 320,
	.hsync_start = 320 + 38,
	.hsync_end = 320 + 38 + 1,
	.htotal = 320 + 38 + 1 + 50,
	.vdisplay = 240,
	.vsync_start = 240 + 4,
	.vsync_end = 240 + 4 + 1,
	.vtotal = 262,
	.flags = 0,
पूर्ण;

/* YUV modes */
अटल स्थिर काष्ठा drm_display_mode yuv_640x320_mode = अणु
	.घड़ी = 24540,
	.hdisplay = 640,
	.hsync_start = 640 + 252,
	.hsync_end = 640 + 252 + 1,
	.htotal = 640 + 252 + 1 + 28,
	.vdisplay = 320,
	.vsync_start = 320 + 4,
	.vsync_end = 320 + 4 + 1,
	.vtotal = 320 + 4 + 1 + 18,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode yuv_720x360_mode = अणु
	.घड़ी = 27000,
	.hdisplay = 720,
	.hsync_start = 720 + 252,
	.hsync_end = 720 + 252 + 1,
	.htotal = 720 + 252 + 1 + 24,
	.vdisplay = 360,
	.vsync_start = 360 + 4,
	.vsync_end = 360 + 4 + 1,
	.vtotal = 360 + 4 + 1 + 18,
	.flags = 0,
पूर्ण;

/* BT.656 VGA mode, 640x480 */
अटल स्थिर काष्ठा drm_display_mode itu_r_bt_656_640_mode = अणु
	.घड़ी = 24540,
	.hdisplay = 640,
	.hsync_start = 640 + 3,
	.hsync_end = 640 + 3 + 1,
	.htotal = 640 + 3 + 1 + 272,
	.vdisplay = 480,
	.vsync_start = 480 + 4,
	.vsync_end = 480 + 4 + 1,
	.vtotal = 500,
	.flags = 0,
पूर्ण;

/* BT.656 D1 mode 720x480 */
अटल स्थिर काष्ठा drm_display_mode itu_r_bt_656_720_mode = अणु
	.घड़ी = 27000,
	.hdisplay = 720,
	.hsync_start = 720 + 3,
	.hsync_end = 720 + 3 + 1,
	.htotal = 720 + 3 + 1 + 272,
	.vdisplay = 480,
	.vsync_start = 480 + 4,
	.vsync_end = 480 + 4 + 1,
	.vtotal = 500,
	.flags = 0,
पूर्ण;

अटल पूर्णांक ili9322_get_modes(काष्ठा drm_panel *panel,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा ili9322 *ili = panel_to_ili9322(panel);
	काष्ठा drm_device *drm = connector->dev;
	काष्ठा drm_display_mode *mode;
	काष्ठा drm_display_info *info;

	info = &connector->display_info;
	info->width_mm = ili->conf->width_mm;
	info->height_mm = ili->conf->height_mm;
	अगर (ili->conf->dclk_active_high)
		info->bus_flags |= DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE;
	अन्यथा
		info->bus_flags |= DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE;

	अगर (ili->conf->de_active_high)
		info->bus_flags |= DRM_BUS_FLAG_DE_HIGH;
	अन्यथा
		info->bus_flags |= DRM_BUS_FLAG_DE_LOW;

	चयन (ili->input) अणु
	हाल ILI9322_INPUT_SRGB_DUMMY_320X240:
		mode = drm_mode_duplicate(drm, &srgb_320x240_mode);
		अवरोध;
	हाल ILI9322_INPUT_SRGB_DUMMY_360X240:
		mode = drm_mode_duplicate(drm, &srgb_360x240_mode);
		अवरोध;
	हाल ILI9322_INPUT_PRGB_THROUGH:
	हाल ILI9322_INPUT_PRGB_ALIGNED:
		mode = drm_mode_duplicate(drm, &prgb_320x240_mode);
		अवरोध;
	हाल ILI9322_INPUT_YUV_640X320_YCBCR:
		mode = drm_mode_duplicate(drm, &yuv_640x320_mode);
		अवरोध;
	हाल ILI9322_INPUT_YUV_720X360_YCBCR:
		mode = drm_mode_duplicate(drm, &yuv_720x360_mode);
		अवरोध;
	हाल ILI9322_INPUT_ITU_R_BT656_720X360_YCBCR:
		mode = drm_mode_duplicate(drm, &itu_r_bt_656_720_mode);
		अवरोध;
	हाल ILI9322_INPUT_ITU_R_BT656_640X320_YCBCR:
		mode = drm_mode_duplicate(drm, &itu_r_bt_656_640_mode);
		अवरोध;
	शेष:
		mode = शून्य;
		अवरोध;
	पूर्ण
	अगर (!mode) अणु
		dev_err(panel->dev, "bad mode or failed to add mode\n");
		वापस -EINVAL;
	पूर्ण
	drm_mode_set_name(mode);
	/*
	 * This is the preferred mode because most people are going
	 * to want to use the display with VGA type graphics.
	 */
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	/* Set up the polarity */
	अगर (ili->conf->hsync_active_high)
		mode->flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		mode->flags |= DRM_MODE_FLAG_NHSYNC;
	अगर (ili->conf->vsync_active_high)
		mode->flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		mode->flags |= DRM_MODE_FLAG_NVSYNC;

	mode->width_mm = ili->conf->width_mm;
	mode->height_mm = ili->conf->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1; /* Number of modes */
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs ili9322_drm_funcs = अणु
	.disable = ili9322_disable,
	.unprepare = ili9322_unprepare,
	.prepare = ili9322_prepare,
	.enable = ili9322_enable,
	.get_modes = ili9322_get_modes,
पूर्ण;

अटल पूर्णांक ili9322_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा ili9322 *ili;
	स्थिर काष्ठा regmap_config *regmap_config;
	u8 gamma;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	ili = devm_kzalloc(dev, माप(काष्ठा ili9322), GFP_KERNEL);
	अगर (!ili)
		वापस -ENOMEM;

	spi_set_drvdata(spi, ili);

	ili->dev = dev;

	/*
	 * Every new incarnation of this display must have a unique
	 * data entry क्रम the प्रणाली in this driver.
	 */
	ili->conf = of_device_get_match_data(dev);
	अगर (!ili->conf) अणु
		dev_err(dev, "missing device configuration\n");
		वापस -ENODEV;
	पूर्ण

	val = ili->conf->vreg1out_mv;
	अगर (!val) अणु
		/* Default HW value, करो not touch (should be 4.5V) */
		ili->vreg1out = U8_MAX;
	पूर्ण अन्यथा अणु
		अगर (val < 3600) अणु
			dev_err(dev, "too low VREG1OUT\n");
			वापस -EINVAL;
		पूर्ण
		अगर (val > 6000) अणु
			dev_err(dev, "too high VREG1OUT\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((val % 100) != 0) अणु
			dev_err(dev, "VREG1OUT is no even 100 microvolt\n");
			वापस -EINVAL;
		पूर्ण
		val -= 3600;
		val /= 100;
		dev_dbg(dev, "VREG1OUT = 0x%02x\n", val);
		ili->vreg1out = val;
	पूर्ण

	val = ili->conf->vcom_high_percent;
	अगर (!val) अणु
		/* Default HW value, करो not touch (should be 91%) */
		ili->vcom_high = U8_MAX;
	पूर्ण अन्यथा अणु
		अगर (val < 37) अणु
			dev_err(dev, "too low VCOM high\n");
			वापस -EINVAL;
		पूर्ण
		अगर (val > 100) अणु
			dev_err(dev, "too high VCOM high\n");
			वापस -EINVAL;
		पूर्ण
		val -= 37;
		dev_dbg(dev, "VCOM high = 0x%02x\n", val);
		ili->vcom_high = val;
	पूर्ण

	val = ili->conf->vcom_amplitude_percent;
	अगर (!val) अणु
		/* Default HW value, करो not touch (should be 114%) */
		ili->vcom_high = U8_MAX;
	पूर्ण अन्यथा अणु
		अगर (val < 70) अणु
			dev_err(dev, "too low VCOM amplitude\n");
			वापस -EINVAL;
		पूर्ण
		अगर (val > 132) अणु
			dev_err(dev, "too high VCOM amplitude\n");
			वापस -EINVAL;
		पूर्ण
		val -= 70;
		val >>= 1; /* Increments of 2% */
		dev_dbg(dev, "VCOM amplitude = 0x%02x\n", val);
		ili->vcom_amplitude = val;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ili->gamma); i++) अणु
		val = ili->conf->gamma_corr_neg[i];
		अगर (val > 15) अणु
			dev_err(dev, "negative gamma %u > 15, capping\n", val);
			val = 15;
		पूर्ण
		gamma = val << 4;
		val = ili->conf->gamma_corr_pos[i];
		अगर (val > 15) अणु
			dev_err(dev, "positive gamma %u > 15, capping\n", val);
			val = 15;
		पूर्ण
		gamma |= val;
		ili->gamma[i] = gamma;
		dev_dbg(dev, "gamma V%d: 0x%02x\n", i + 1, gamma);
	पूर्ण

	ili->supplies[0].supply = "vcc"; /* 2.7-3.6 V */
	ili->supplies[1].supply = "iovcc"; /* 1.65-3.6V */
	ili->supplies[2].supply = "vci"; /* 2.7-3.6V */
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ili->supplies),
				      ili->supplies);
	अगर (ret < 0)
		वापस ret;
	ret = regulator_set_voltage(ili->supplies[0].consumer,
				    2700000, 3600000);
	अगर (ret)
		वापस ret;
	ret = regulator_set_voltage(ili->supplies[1].consumer,
				    1650000, 3600000);
	अगर (ret)
		वापस ret;
	ret = regulator_set_voltage(ili->supplies[2].consumer,
				    2700000, 3600000);
	अगर (ret)
		वापस ret;

	ili->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ili->reset_gpio)) अणु
		dev_err(dev, "failed to get RESET GPIO\n");
		वापस PTR_ERR(ili->reset_gpio);
	पूर्ण

	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(dev, "spi setup failed.\n");
		वापस ret;
	पूर्ण
	regmap_config = &ili9322_regmap_config;
	ili->regmap = devm_regmap_init(dev, &ili9322_regmap_bus, dev,
				       regmap_config);
	अगर (IS_ERR(ili->regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(ili->regmap);
	पूर्ण

	ret = regmap_पढ़ो(ili->regmap, ILI9322_CHIP_ID, &val);
	अगर (ret) अणु
		dev_err(dev, "can't get chip ID (%d)\n", ret);
		वापस ret;
	पूर्ण
	अगर (val != ILI9322_CHIP_ID_MAGIC) अणु
		dev_err(dev, "chip ID 0x%0x2, expected 0x%02x\n", val,
			ILI9322_CHIP_ID_MAGIC);
		वापस -ENODEV;
	पूर्ण

	/* Probe the प्रणाली to find the display setting */
	अगर (ili->conf->input == ILI9322_INPUT_UNKNOWN) अणु
		ret = regmap_पढ़ो(ili->regmap, ILI9322_ENTRY, &val);
		अगर (ret) अणु
			dev_err(dev, "can't get entry setting (%d)\n", ret);
			वापस ret;
		पूर्ण
		/* Input क्रमागत corresponds to HW setting */
		ili->input = (val >> 4) & 0x0f;
		अगर (ili->input >= ILI9322_INPUT_UNKNOWN)
			ili->input = ILI9322_INPUT_UNKNOWN;
	पूर्ण अन्यथा अणु
		ili->input = ili->conf->input;
	पूर्ण

	drm_panel_init(&ili->panel, dev, &ili9322_drm_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&ili->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक ili9322_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ili9322 *ili = spi_get_drvdata(spi);

	ili9322_घातer_off(ili);
	drm_panel_हटाओ(&ili->panel);

	वापस 0;
पूर्ण

/*
 * The D-Link सूची-685 panel is marked LM918A01-1A SY-B4-091116-E0199
 */
अटल स्थिर काष्ठा ili9322_config ili9322_dir_685 = अणु
	.width_mm = 65,
	.height_mm = 50,
	.input = ILI9322_INPUT_ITU_R_BT656_640X320_YCBCR,
	.vreg1out_mv = 4600,
	.vcom_high_percent = 91,
	.vcom_amplitude_percent = 114,
	.syncmode = ILI9322_IF_CTRL_SYNC_DISABLED,
	.dclk_active_high = true,
	.gamma_corr_neg = अणु 0xa, 0x5, 0x7, 0x7, 0x7, 0x5, 0x1, 0x6 पूर्ण,
	.gamma_corr_pos = अणु 0x7, 0x7, 0x3, 0x2, 0x3, 0x5, 0x7, 0x2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ili9322_of_match[] = अणु
	अणु
		.compatible = "dlink,dir-685-panel",
		.data = &ili9322_dir_685,
	पूर्ण,
	अणु
		.compatible = "ilitek,ili9322",
		.data = शून्य,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ili9322_of_match);

अटल काष्ठा spi_driver ili9322_driver = अणु
	.probe = ili9322_probe,
	.हटाओ = ili9322_हटाओ,
	.driver = अणु
		.name = "panel-ilitek-ili9322",
		.of_match_table = ili9322_of_match,
	पूर्ण,
पूर्ण;
module_spi_driver(ili9322_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("ILI9322 LCD panel driver");
MODULE_LICENSE("GPL v2");
