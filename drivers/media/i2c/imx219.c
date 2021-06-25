<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A V4L2 driver क्रम Sony IMX219 cameras.
 * Copyright (C) 2019, Raspberry Pi (Trading) Ltd
 *
 * Based on Sony imx258 camera driver
 * Copyright (C) 2018 Intel Corporation
 *
 * DT / fwnode changes, and regulator / GPIO control taken from imx214 driver
 * Copyright 2018 Qtechnology A/S
 *
 * Flip handling taken from the Sony IMX319 driver.
 * Copyright (C) 2018 Intel Corporation
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा IMX219_REG_VALUE_08BIT		1
#घोषणा IMX219_REG_VALUE_16BIT		2

#घोषणा IMX219_REG_MODE_SELECT		0x0100
#घोषणा IMX219_MODE_STANDBY		0x00
#घोषणा IMX219_MODE_STREAMING		0x01

/* Chip ID */
#घोषणा IMX219_REG_CHIP_ID		0x0000
#घोषणा IMX219_CHIP_ID			0x0219

/* External घड़ी frequency is 24.0M */
#घोषणा IMX219_XCLK_FREQ		24000000

/* Pixel rate is fixed at 182.4M क्रम all the modes */
#घोषणा IMX219_PIXEL_RATE		182400000

#घोषणा IMX219_DEFAULT_LINK_FREQ	456000000

/* V_TIMING पूर्णांकernal */
#घोषणा IMX219_REG_VTS			0x0160
#घोषणा IMX219_VTS_15FPS		0x0dc6
#घोषणा IMX219_VTS_30FPS_1080P		0x06e3
#घोषणा IMX219_VTS_30FPS_BINNED		0x06e3
#घोषणा IMX219_VTS_30FPS_640x480	0x06e3
#घोषणा IMX219_VTS_MAX			0xffff

#घोषणा IMX219_VBLANK_MIN		4

/*Frame Length Line*/
#घोषणा IMX219_FLL_MIN			0x08a6
#घोषणा IMX219_FLL_MAX			0xffff
#घोषणा IMX219_FLL_STEP			1
#घोषणा IMX219_FLL_DEFAULT		0x0c98

/* HBLANK control - पढ़ो only */
#घोषणा IMX219_PPL_DEFAULT		3448

/* Exposure control */
#घोषणा IMX219_REG_EXPOSURE		0x015a
#घोषणा IMX219_EXPOSURE_MIN		4
#घोषणा IMX219_EXPOSURE_STEP		1
#घोषणा IMX219_EXPOSURE_DEFAULT		0x640
#घोषणा IMX219_EXPOSURE_MAX		65535

/* Analog gain control */
#घोषणा IMX219_REG_ANALOG_GAIN		0x0157
#घोषणा IMX219_ANA_GAIN_MIN		0
#घोषणा IMX219_ANA_GAIN_MAX		232
#घोषणा IMX219_ANA_GAIN_STEP		1
#घोषणा IMX219_ANA_GAIN_DEFAULT		0x0

/* Digital gain control */
#घोषणा IMX219_REG_DIGITAL_GAIN		0x0158
#घोषणा IMX219_DGTL_GAIN_MIN		0x0100
#घोषणा IMX219_DGTL_GAIN_MAX		0x0fff
#घोषणा IMX219_DGTL_GAIN_DEFAULT	0x0100
#घोषणा IMX219_DGTL_GAIN_STEP		1

#घोषणा IMX219_REG_ORIENTATION		0x0172

/* Test Pattern Control */
#घोषणा IMX219_REG_TEST_PATTERN		0x0600
#घोषणा IMX219_TEST_PATTERN_DISABLE	0
#घोषणा IMX219_TEST_PATTERN_SOLID_COLOR	1
#घोषणा IMX219_TEST_PATTERN_COLOR_BARS	2
#घोषणा IMX219_TEST_PATTERN_GREY_COLOR	3
#घोषणा IMX219_TEST_PATTERN_PN9		4

/* Test pattern colour components */
#घोषणा IMX219_REG_TESTP_RED		0x0602
#घोषणा IMX219_REG_TESTP_GREENR		0x0604
#घोषणा IMX219_REG_TESTP_BLUE		0x0606
#घोषणा IMX219_REG_TESTP_GREENB		0x0608
#घोषणा IMX219_TESTP_COLOUR_MIN		0
#घोषणा IMX219_TESTP_COLOUR_MAX		0x03ff
#घोषणा IMX219_TESTP_COLOUR_STEP	1
#घोषणा IMX219_TESTP_RED_DEFAULT	IMX219_TESTP_COLOUR_MAX
#घोषणा IMX219_TESTP_GREENR_DEFAULT	0
#घोषणा IMX219_TESTP_BLUE_DEFAULT	0
#घोषणा IMX219_TESTP_GREENB_DEFAULT	0

/* IMX219 native and active pixel array size. */
#घोषणा IMX219_NATIVE_WIDTH		3296U
#घोषणा IMX219_NATIVE_HEIGHT		2480U
#घोषणा IMX219_PIXEL_ARRAY_LEFT		8U
#घोषणा IMX219_PIXEL_ARRAY_TOP		8U
#घोषणा IMX219_PIXEL_ARRAY_WIDTH	3280U
#घोषणा IMX219_PIXEL_ARRAY_HEIGHT	2464U

काष्ठा imx219_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा imx219_reg_list अणु
	अचिन्हित पूर्णांक num_of_regs;
	स्थिर काष्ठा imx219_reg *regs;
पूर्ण;

/* Mode : resolution and related config&values */
काष्ठा imx219_mode अणु
	/* Frame width */
	अचिन्हित पूर्णांक width;
	/* Frame height */
	अचिन्हित पूर्णांक height;

	/* Analog crop rectangle. */
	काष्ठा v4l2_rect crop;

	/* V-timing */
	अचिन्हित पूर्णांक vts_def;

	/* Default रेजिस्टर values */
	काष्ठा imx219_reg_list reg_list;
पूर्ण;

/*
 * Register sets lअगरted off the i2C पूर्णांकerface from the Raspberry Pi firmware
 * driver.
 * 3280x2464 = mode 2, 1920x1080 = mode 1, 1640x1232 = mode 4, 640x480 = mode 7.
 */
अटल स्थिर काष्ठा imx219_reg mode_3280x2464_regs[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x30eb, 0x0cपूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x300a, 0xffपूर्ण,
	अणु0x300b, 0xffपूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x30eb, 0x09पूर्ण,
	अणु0x0114, 0x01पूर्ण,
	अणु0x0128, 0x00पूर्ण,
	अणु0x012a, 0x18पूर्ण,
	अणु0x012b, 0x00पूर्ण,
	अणु0x0164, 0x00पूर्ण,
	अणु0x0165, 0x00पूर्ण,
	अणु0x0166, 0x0cपूर्ण,
	अणु0x0167, 0xcfपूर्ण,
	अणु0x0168, 0x00पूर्ण,
	अणु0x0169, 0x00पूर्ण,
	अणु0x016a, 0x09पूर्ण,
	अणु0x016b, 0x9fपूर्ण,
	अणु0x016c, 0x0cपूर्ण,
	अणु0x016d, 0xd0पूर्ण,
	अणु0x016e, 0x09पूर्ण,
	अणु0x016f, 0xa0पूर्ण,
	अणु0x0170, 0x01पूर्ण,
	अणु0x0171, 0x01पूर्ण,
	अणु0x0174, 0x00पूर्ण,
	अणु0x0175, 0x00पूर्ण,
	अणु0x0301, 0x05पूर्ण,
	अणु0x0303, 0x01पूर्ण,
	अणु0x0304, 0x03पूर्ण,
	अणु0x0305, 0x03पूर्ण,
	अणु0x0306, 0x00पूर्ण,
	अणु0x0307, 0x39पूर्ण,
	अणु0x030b, 0x01पूर्ण,
	अणु0x030c, 0x00पूर्ण,
	अणु0x030d, 0x72पूर्ण,
	अणु0x0624, 0x0cपूर्ण,
	अणु0x0625, 0xd0पूर्ण,
	अणु0x0626, 0x09पूर्ण,
	अणु0x0627, 0xa0पूर्ण,
	अणु0x455e, 0x00पूर्ण,
	अणु0x471e, 0x4bपूर्ण,
	अणु0x4767, 0x0fपूर्ण,
	अणु0x4750, 0x14पूर्ण,
	अणु0x4540, 0x00पूर्ण,
	अणु0x47b4, 0x14पूर्ण,
	अणु0x4713, 0x30पूर्ण,
	अणु0x478b, 0x10पूर्ण,
	अणु0x478f, 0x10पूर्ण,
	अणु0x4793, 0x10पूर्ण,
	अणु0x4797, 0x0eपूर्ण,
	अणु0x479b, 0x0eपूर्ण,
	अणु0x0162, 0x0dपूर्ण,
	अणु0x0163, 0x78पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx219_reg mode_1920_1080_regs[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x30eb, 0x0cपूर्ण,
	अणु0x300a, 0xffपूर्ण,
	अणु0x300b, 0xffपूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x30eb, 0x09पूर्ण,
	अणु0x0114, 0x01पूर्ण,
	अणु0x0128, 0x00पूर्ण,
	अणु0x012a, 0x18पूर्ण,
	अणु0x012b, 0x00पूर्ण,
	अणु0x0162, 0x0dपूर्ण,
	अणु0x0163, 0x78पूर्ण,
	अणु0x0164, 0x02पूर्ण,
	अणु0x0165, 0xa8पूर्ण,
	अणु0x0166, 0x0aपूर्ण,
	अणु0x0167, 0x27पूर्ण,
	अणु0x0168, 0x02पूर्ण,
	अणु0x0169, 0xb4पूर्ण,
	अणु0x016a, 0x06पूर्ण,
	अणु0x016b, 0xebपूर्ण,
	अणु0x016c, 0x07पूर्ण,
	अणु0x016d, 0x80पूर्ण,
	अणु0x016e, 0x04पूर्ण,
	अणु0x016f, 0x38पूर्ण,
	अणु0x0170, 0x01पूर्ण,
	अणु0x0171, 0x01पूर्ण,
	अणु0x0174, 0x00पूर्ण,
	अणु0x0175, 0x00पूर्ण,
	अणु0x0301, 0x05पूर्ण,
	अणु0x0303, 0x01पूर्ण,
	अणु0x0304, 0x03पूर्ण,
	अणु0x0305, 0x03पूर्ण,
	अणु0x0306, 0x00पूर्ण,
	अणु0x0307, 0x39पूर्ण,
	अणु0x030b, 0x01पूर्ण,
	अणु0x030c, 0x00पूर्ण,
	अणु0x030d, 0x72पूर्ण,
	अणु0x0624, 0x07पूर्ण,
	अणु0x0625, 0x80पूर्ण,
	अणु0x0626, 0x04पूर्ण,
	अणु0x0627, 0x38पूर्ण,
	अणु0x455e, 0x00पूर्ण,
	अणु0x471e, 0x4bपूर्ण,
	अणु0x4767, 0x0fपूर्ण,
	अणु0x4750, 0x14पूर्ण,
	अणु0x4540, 0x00पूर्ण,
	अणु0x47b4, 0x14पूर्ण,
	अणु0x4713, 0x30पूर्ण,
	अणु0x478b, 0x10पूर्ण,
	अणु0x478f, 0x10पूर्ण,
	अणु0x4793, 0x10पूर्ण,
	अणु0x4797, 0x0eपूर्ण,
	अणु0x479b, 0x0eपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx219_reg mode_1640_1232_regs[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x30eb, 0x0cपूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x300a, 0xffपूर्ण,
	अणु0x300b, 0xffपूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x30eb, 0x09पूर्ण,
	अणु0x0114, 0x01पूर्ण,
	अणु0x0128, 0x00पूर्ण,
	अणु0x012a, 0x18पूर्ण,
	अणु0x012b, 0x00पूर्ण,
	अणु0x0164, 0x00पूर्ण,
	अणु0x0165, 0x00पूर्ण,
	अणु0x0166, 0x0cपूर्ण,
	अणु0x0167, 0xcfपूर्ण,
	अणु0x0168, 0x00पूर्ण,
	अणु0x0169, 0x00पूर्ण,
	अणु0x016a, 0x09पूर्ण,
	अणु0x016b, 0x9fपूर्ण,
	अणु0x016c, 0x06पूर्ण,
	अणु0x016d, 0x68पूर्ण,
	अणु0x016e, 0x04पूर्ण,
	अणु0x016f, 0xd0पूर्ण,
	अणु0x0170, 0x01पूर्ण,
	अणु0x0171, 0x01पूर्ण,
	अणु0x0174, 0x01पूर्ण,
	अणु0x0175, 0x01पूर्ण,
	अणु0x0301, 0x05पूर्ण,
	अणु0x0303, 0x01पूर्ण,
	अणु0x0304, 0x03पूर्ण,
	अणु0x0305, 0x03पूर्ण,
	अणु0x0306, 0x00पूर्ण,
	अणु0x0307, 0x39पूर्ण,
	अणु0x030b, 0x01पूर्ण,
	अणु0x030c, 0x00पूर्ण,
	अणु0x030d, 0x72पूर्ण,
	अणु0x0624, 0x06पूर्ण,
	अणु0x0625, 0x68पूर्ण,
	अणु0x0626, 0x04पूर्ण,
	अणु0x0627, 0xd0पूर्ण,
	अणु0x455e, 0x00पूर्ण,
	अणु0x471e, 0x4bपूर्ण,
	अणु0x4767, 0x0fपूर्ण,
	अणु0x4750, 0x14पूर्ण,
	अणु0x4540, 0x00पूर्ण,
	अणु0x47b4, 0x14पूर्ण,
	अणु0x4713, 0x30पूर्ण,
	अणु0x478b, 0x10पूर्ण,
	अणु0x478f, 0x10पूर्ण,
	अणु0x4793, 0x10पूर्ण,
	अणु0x4797, 0x0eपूर्ण,
	अणु0x479b, 0x0eपूर्ण,
	अणु0x0162, 0x0dपूर्ण,
	अणु0x0163, 0x78पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx219_reg mode_640_480_regs[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x30eb, 0x0cपूर्ण,
	अणु0x300a, 0xffपूर्ण,
	अणु0x300b, 0xffपूर्ण,
	अणु0x30eb, 0x05पूर्ण,
	अणु0x30eb, 0x09पूर्ण,
	अणु0x0114, 0x01पूर्ण,
	अणु0x0128, 0x00पूर्ण,
	अणु0x012a, 0x18पूर्ण,
	अणु0x012b, 0x00पूर्ण,
	अणु0x0162, 0x0dपूर्ण,
	अणु0x0163, 0x78पूर्ण,
	अणु0x0164, 0x03पूर्ण,
	अणु0x0165, 0xe8पूर्ण,
	अणु0x0166, 0x08पूर्ण,
	अणु0x0167, 0xe7पूर्ण,
	अणु0x0168, 0x02पूर्ण,
	अणु0x0169, 0xf0पूर्ण,
	अणु0x016a, 0x06पूर्ण,
	अणु0x016b, 0xafपूर्ण,
	अणु0x016c, 0x02पूर्ण,
	अणु0x016d, 0x80पूर्ण,
	अणु0x016e, 0x01पूर्ण,
	अणु0x016f, 0xe0पूर्ण,
	अणु0x0170, 0x01पूर्ण,
	अणु0x0171, 0x01पूर्ण,
	अणु0x0174, 0x03पूर्ण,
	अणु0x0175, 0x03पूर्ण,
	अणु0x0301, 0x05पूर्ण,
	अणु0x0303, 0x01पूर्ण,
	अणु0x0304, 0x03पूर्ण,
	अणु0x0305, 0x03पूर्ण,
	अणु0x0306, 0x00पूर्ण,
	अणु0x0307, 0x39पूर्ण,
	अणु0x030b, 0x01पूर्ण,
	अणु0x030c, 0x00पूर्ण,
	अणु0x030d, 0x72पूर्ण,
	अणु0x0624, 0x06पूर्ण,
	अणु0x0625, 0x68पूर्ण,
	अणु0x0626, 0x04पूर्ण,
	अणु0x0627, 0xd0पूर्ण,
	अणु0x455e, 0x00पूर्ण,
	अणु0x471e, 0x4bपूर्ण,
	अणु0x4767, 0x0fपूर्ण,
	अणु0x4750, 0x14पूर्ण,
	अणु0x4540, 0x00पूर्ण,
	अणु0x47b4, 0x14पूर्ण,
	अणु0x4713, 0x30पूर्ण,
	अणु0x478b, 0x10पूर्ण,
	अणु0x478f, 0x10पूर्ण,
	अणु0x4793, 0x10पूर्ण,
	अणु0x4797, 0x0eपूर्ण,
	अणु0x479b, 0x0eपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx219_reg raw8_framefmt_regs[] = अणु
	अणु0x018c, 0x08पूर्ण,
	अणु0x018d, 0x08पूर्ण,
	अणु0x0309, 0x08पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx219_reg raw10_framefmt_regs[] = अणु
	अणु0x018c, 0x0aपूर्ण,
	अणु0x018d, 0x0aपूर्ण,
	अणु0x0309, 0x0aपूर्ण,
पूर्ण;

अटल स्थिर s64 imx219_link_freq_menu[] = अणु
	IMX219_DEFAULT_LINK_FREQ,
पूर्ण;

अटल स्थिर अक्षर * स्थिर imx219_test_pattern_menu[] = अणु
	"Disabled",
	"Color Bars",
	"Solid Color",
	"Grey Color Bars",
	"PN9"
पूर्ण;

अटल स्थिर पूर्णांक imx219_test_pattern_val[] = अणु
	IMX219_TEST_PATTERN_DISABLE,
	IMX219_TEST_PATTERN_COLOR_BARS,
	IMX219_TEST_PATTERN_SOLID_COLOR,
	IMX219_TEST_PATTERN_GREY_COLOR,
	IMX219_TEST_PATTERN_PN9,
पूर्ण;

/* regulator supplies */
अटल स्थिर अक्षर * स्थिर imx219_supply_name[] = अणु
	/* Supplies can be enabled in any order */
	"VANA",  /* Analog (2.8V) supply */
	"VDIG",  /* Digital Core (1.8V) supply */
	"VDDL",  /* IF (1.2V) supply */
पूर्ण;

#घोषणा IMX219_NUM_SUPPLIES ARRAY_SIZE(imx219_supply_name)

/*
 * The supported क्रमmats.
 * This table MUST contain 4 entries per क्रमmat, to cover the various flip
 * combinations in the order
 * - no flip
 * - h flip
 * - v flip
 * - h&v flips
 */
अटल स्थिर u32 codes[] = अणु
	MEDIA_BUS_FMT_SRGGB10_1X10,
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_SBGGR10_1X10,

	MEDIA_BUS_FMT_SRGGB8_1X8,
	MEDIA_BUS_FMT_SGRBG8_1X8,
	MEDIA_BUS_FMT_SGBRG8_1X8,
	MEDIA_BUS_FMT_SBGGR8_1X8,
पूर्ण;

/*
 * Initialisation delay between XCLR low->high and the moment when the sensor
 * can start capture (i.e. can leave software stanby) must be not less than:
 *   t4 + max(t5, t6 + <समय to initialize the sensor रेजिस्टर over I2C>)
 * where
 *   t4 is fixed, and is max 200uS,
 *   t5 is fixed, and is 6000uS,
 *   t6 depends on the sensor बाह्यal घड़ी, and is max 32000 घड़ी periods.
 * As per sensor datasheet, the बाह्यal घड़ी must be from 6MHz to 27MHz.
 * So क्रम any acceptable बाह्यal घड़ी t6 is always within the range of
 * 1185 to 5333 uS, and is always less than t5.
 * For this reason this is always safe to रुको (t4 + t5) = 6200 uS, then
 * initialize the sensor over I2C, and then निकास the software standby.
 *
 * This start-up समय can be optimized a bit more, अगर we start the ग_लिखोs
 * over I2C after (t4+t6), but beक्रमe (t4+t5) expires. But then sensor
 * initialization over I2C may complete beक्रमe (t4+t5) expires, and we must
 * ensure that capture is not started beक्रमe (t4+t5).
 *
 * This delay करोesn't account क्रम the घातer supply startup समय. If needed,
 * this should be taken care of via the regulator framework. E.g. in the
 * हाल of DT क्रम regulator-fixed one should define the startup-delay-us
 * property.
 */
#घोषणा IMX219_XCLR_MIN_DELAY_US	6200
#घोषणा IMX219_XCLR_DELAY_RANGE_US	1000

/* Mode configs */
अटल स्थिर काष्ठा imx219_mode supported_modes[] = अणु
	अणु
		/* 8MPix 15fps mode */
		.width = 3280,
		.height = 2464,
		.crop = अणु
			.left = IMX219_PIXEL_ARRAY_LEFT,
			.top = IMX219_PIXEL_ARRAY_TOP,
			.width = 3280,
			.height = 2464
		पूर्ण,
		.vts_def = IMX219_VTS_15FPS,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_3280x2464_regs),
			.regs = mode_3280x2464_regs,
		पूर्ण,
	पूर्ण,
	अणु
		/* 1080P 30fps cropped */
		.width = 1920,
		.height = 1080,
		.crop = अणु
			.left = 688,
			.top = 700,
			.width = 1920,
			.height = 1080
		पूर्ण,
		.vts_def = IMX219_VTS_30FPS_1080P,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1920_1080_regs),
			.regs = mode_1920_1080_regs,
		पूर्ण,
	पूर्ण,
	अणु
		/* 2x2 binned 30fps mode */
		.width = 1640,
		.height = 1232,
		.crop = अणु
			.left = IMX219_PIXEL_ARRAY_LEFT,
			.top = IMX219_PIXEL_ARRAY_TOP,
			.width = 3280,
			.height = 2464
		पूर्ण,
		.vts_def = IMX219_VTS_30FPS_BINNED,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1640_1232_regs),
			.regs = mode_1640_1232_regs,
		पूर्ण,
	पूर्ण,
	अणु
		/* 640x480 30fps mode */
		.width = 640,
		.height = 480,
		.crop = अणु
			.left = 1008,
			.top = 760,
			.width = 1280,
			.height = 960
		पूर्ण,
		.vts_def = IMX219_VTS_30FPS_640x480,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_640_480_regs),
			.regs = mode_640_480_regs,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा imx219 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;

	काष्ठा v4l2_mbus_framefmt fmt;

	काष्ठा clk *xclk; /* प्रणाली घड़ी to IMX219 */
	u32 xclk_freq;

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator_bulk_data supplies[IMX219_NUM_SUPPLIES];

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	/* V4L2 Controls */
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl *hblank;

	/* Current mode */
	स्थिर काष्ठा imx219_mode *mode;

	/*
	 * Mutex क्रम serialized access:
	 * Protect sensor module set pad क्रमmat and start/stop streaming safely.
	 */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;
पूर्ण;

अटल अंतरभूत काष्ठा imx219 *to_imx219(काष्ठा v4l2_subdev *_sd)
अणु
	वापस container_of(_sd, काष्ठा imx219, sd);
पूर्ण

/* Read रेजिस्टरs up to 2 at a समय */
अटल पूर्णांक imx219_पढ़ो_reg(काष्ठा imx219 *imx219, u16 reg, u32 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2] = अणु reg >> 8, reg & 0xff पूर्ण;
	u8 data_buf[4] = अणु 0, पूर्ण;
	पूर्णांक ret;

	अगर (len > 4)
		वापस -EINVAL;

	/* Write रेजिस्टर address */
	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = ARRAY_SIZE(addr_buf);
	msgs[0].buf = addr_buf;

	/* Read data from रेजिस्टर */
	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = &data_buf[4 - len];

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs))
		वापस -EIO;

	*val = get_unaligned_be32(data_buf);

	वापस 0;
पूर्ण

/* Write रेजिस्टरs up to 2 at a समय */
अटल पूर्णांक imx219_ग_लिखो_reg(काष्ठा imx219 *imx219, u16 reg, u32 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	u8 buf[6];

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);
	put_unaligned_be32(val << (8 * (4 - len)), buf + 2);
	अगर (i2c_master_send(client, buf, len + 2) != len + 2)
		वापस -EIO;

	वापस 0;
पूर्ण

/* Write a list of रेजिस्टरs */
अटल पूर्णांक imx219_ग_लिखो_regs(काष्ठा imx219 *imx219,
			     स्थिर काष्ठा imx219_reg *regs, u32 len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < len; i++) अणु
		ret = imx219_ग_लिखो_reg(imx219, regs[i].address, 1, regs[i].val);
		अगर (ret) अणु
			dev_err_ratelimited(&client->dev,
					    "Failed to write reg 0x%4.4x. error = %d\n",
					    regs[i].address, ret);

			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Get bayer order based on flip setting. */
अटल u32 imx219_get_क्रमmat_code(काष्ठा imx219 *imx219, u32 code)
अणु
	अचिन्हित पूर्णांक i;

	lockdep_निश्चित_held(&imx219->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(codes); i++)
		अगर (codes[i] == code)
			अवरोध;

	अगर (i >= ARRAY_SIZE(codes))
		i = 0;

	i = (i & ~3) | (imx219->vflip->val ? 2 : 0) |
	    (imx219->hflip->val ? 1 : 0);

	वापस codes[i];
पूर्ण

अटल व्योम imx219_set_शेष_क्रमmat(काष्ठा imx219 *imx219)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt;

	fmt = &imx219->fmt;
	fmt->code = MEDIA_BUS_FMT_SRGGB10_1X10;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	fmt->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true,
							  fmt->colorspace,
							  fmt->ycbcr_enc);
	fmt->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(fmt->colorspace);
	fmt->width = supported_modes[0].width;
	fmt->height = supported_modes[0].height;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक imx219_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा imx219 *imx219 = to_imx219(sd);
	काष्ठा v4l2_mbus_framefmt *try_fmt =
		v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);
	काष्ठा v4l2_rect *try_crop;

	mutex_lock(&imx219->mutex);

	/* Initialize try_fmt */
	try_fmt->width = supported_modes[0].width;
	try_fmt->height = supported_modes[0].height;
	try_fmt->code = imx219_get_क्रमmat_code(imx219,
					       MEDIA_BUS_FMT_SRGGB10_1X10);
	try_fmt->field = V4L2_FIELD_NONE;

	/* Initialize try_crop rectangle. */
	try_crop = v4l2_subdev_get_try_crop(sd, fh->pad, 0);
	try_crop->top = IMX219_PIXEL_ARRAY_TOP;
	try_crop->left = IMX219_PIXEL_ARRAY_LEFT;
	try_crop->width = IMX219_PIXEL_ARRAY_WIDTH;
	try_crop->height = IMX219_PIXEL_ARRAY_HEIGHT;

	mutex_unlock(&imx219->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक imx219_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imx219 *imx219 =
		container_of(ctrl->handler, काष्ठा imx219, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	पूर्णांक ret;

	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		पूर्णांक exposure_max, exposure_def;

		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = imx219->mode->height + ctrl->val - 4;
		exposure_def = (exposure_max < IMX219_EXPOSURE_DEFAULT) ?
			exposure_max : IMX219_EXPOSURE_DEFAULT;
		__v4l2_ctrl_modअगरy_range(imx219->exposure,
					 imx219->exposure->minimum,
					 exposure_max, imx219->exposure->step,
					 exposure_def);
	पूर्ण

	/*
	 * Applying V4L2 control value only happens
	 * when घातer is up क्रम streaming
	 */
	अगर (pm_runसमय_get_अगर_in_use(&client->dev) == 0)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_ANALOG_GAIN,
				       IMX219_REG_VALUE_08BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_EXPOSURE,
				       IMX219_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_DIGITAL_GAIN:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_DIGITAL_GAIN,
				       IMX219_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_TEST_PATTERN,
				       IMX219_REG_VALUE_16BIT,
				       imx219_test_pattern_val[ctrl->val]);
		अवरोध;
	हाल V4L2_CID_HFLIP:
	हाल V4L2_CID_VFLIP:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_ORIENTATION, 1,
				       imx219->hflip->val |
				       imx219->vflip->val << 1);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_VTS,
				       IMX219_REG_VALUE_16BIT,
				       imx219->mode->height + ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_RED:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_TESTP_RED,
				       IMX219_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_GREENR:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_TESTP_GREENR,
				       IMX219_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_BLUE:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_TESTP_BLUE,
				       IMX219_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN_GREENB:
		ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_TESTP_GREENB,
				       IMX219_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	शेष:
		dev_info(&client->dev,
			 "ctrl(id:0x%x,val:0x%x) is not handled\n",
			 ctrl->id, ctrl->val);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops imx219_ctrl_ops = अणु
	.s_ctrl = imx219_set_ctrl,
पूर्ण;

अटल पूर्णांक imx219_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा imx219 *imx219 = to_imx219(sd);

	अगर (code->index >= (ARRAY_SIZE(codes) / 4))
		वापस -EINVAL;

	mutex_lock(&imx219->mutex);
	code->code = imx219_get_क्रमmat_code(imx219, codes[code->index * 4]);
	mutex_unlock(&imx219->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक imx219_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा imx219 *imx219 = to_imx219(sd);
	u32 code;

	अगर (fse->index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	mutex_lock(&imx219->mutex);
	code = imx219_get_क्रमmat_code(imx219, fse->code);
	mutex_unlock(&imx219->mutex);
	अगर (fse->code != code)
		वापस -EINVAL;

	fse->min_width = supported_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = supported_modes[fse->index].height;
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल व्योम imx219_reset_colorspace(काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	fmt->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true,
							  fmt->colorspace,
							  fmt->ycbcr_enc);
	fmt->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(fmt->colorspace);
पूर्ण

अटल व्योम imx219_update_pad_क्रमmat(काष्ठा imx219 *imx219,
				     स्थिर काष्ठा imx219_mode *mode,
				     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	fmt->क्रमmat.width = mode->width;
	fmt->क्रमmat.height = mode->height;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;
	imx219_reset_colorspace(&fmt->क्रमmat);
पूर्ण

अटल पूर्णांक __imx219_get_pad_क्रमmat(काष्ठा imx219 *imx219,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *try_fmt =
			v4l2_subdev_get_try_क्रमmat(&imx219->sd, cfg, fmt->pad);
		/* update the code which could change due to vflip or hflip: */
		try_fmt->code = imx219_get_क्रमmat_code(imx219, try_fmt->code);
		fmt->क्रमmat = *try_fmt;
	पूर्ण अन्यथा अणु
		imx219_update_pad_क्रमmat(imx219, imx219->mode, fmt);
		fmt->क्रमmat.code = imx219_get_क्रमmat_code(imx219,
							  imx219->fmt.code);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx219_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx219 *imx219 = to_imx219(sd);
	पूर्णांक ret;

	mutex_lock(&imx219->mutex);
	ret = __imx219_get_pad_क्रमmat(imx219, cfg, fmt);
	mutex_unlock(&imx219->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक imx219_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx219 *imx219 = to_imx219(sd);
	स्थिर काष्ठा imx219_mode *mode;
	काष्ठा v4l2_mbus_framefmt *framefmt;
	पूर्णांक exposure_max, exposure_def, hblank;
	अचिन्हित पूर्णांक i;

	mutex_lock(&imx219->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(codes); i++)
		अगर (codes[i] == fmt->क्रमmat.code)
			अवरोध;
	अगर (i >= ARRAY_SIZE(codes))
		i = 0;

	/* Bayer order varies with flips */
	fmt->क्रमmat.code = imx219_get_क्रमmat_code(imx219, codes[i]);

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes),
				      width, height,
				      fmt->क्रमmat.width, fmt->क्रमmat.height);
	imx219_update_pad_क्रमmat(imx219, mode, fmt);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*framefmt = fmt->क्रमmat;
	पूर्ण अन्यथा अगर (imx219->mode != mode ||
		   imx219->fmt.code != fmt->क्रमmat.code) अणु
		imx219->fmt = fmt->क्रमmat;
		imx219->mode = mode;
		/* Update limits and set FPS to शेष */
		__v4l2_ctrl_modअगरy_range(imx219->vblank, IMX219_VBLANK_MIN,
					 IMX219_VTS_MAX - mode->height, 1,
					 mode->vts_def - mode->height);
		__v4l2_ctrl_s_ctrl(imx219->vblank,
				   mode->vts_def - mode->height);
		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = mode->vts_def - 4;
		exposure_def = (exposure_max < IMX219_EXPOSURE_DEFAULT) ?
			exposure_max : IMX219_EXPOSURE_DEFAULT;
		__v4l2_ctrl_modअगरy_range(imx219->exposure,
					 imx219->exposure->minimum,
					 exposure_max, imx219->exposure->step,
					 exposure_def);
		/*
		 * Currently PPL is fixed to IMX219_PPL_DEFAULT, so hblank
		 * depends on mode->width only, and is not changeble in any
		 * way other than changing the mode.
		 */
		hblank = IMX219_PPL_DEFAULT - mode->width;
		__v4l2_ctrl_modअगरy_range(imx219->hblank, hblank, hblank, 1,
					 hblank);
	पूर्ण

	mutex_unlock(&imx219->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक imx219_set_framefmt(काष्ठा imx219 *imx219)
अणु
	चयन (imx219->fmt.code) अणु
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		वापस imx219_ग_लिखो_regs(imx219, raw8_framefmt_regs,
					ARRAY_SIZE(raw8_framefmt_regs));

	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
		वापस imx219_ग_लिखो_regs(imx219, raw10_framefmt_regs,
					ARRAY_SIZE(raw10_framefmt_regs));
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_rect *
__imx219_get_pad_crop(काष्ठा imx219 *imx219, काष्ठा v4l2_subdev_pad_config *cfg,
		      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&imx219->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &imx219->mode->crop;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक imx219_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP: अणु
		काष्ठा imx219 *imx219 = to_imx219(sd);

		mutex_lock(&imx219->mutex);
		sel->r = *__imx219_get_pad_crop(imx219, cfg, sel->pad,
						sel->which);
		mutex_unlock(&imx219->mutex);

		वापस 0;
	पूर्ण

	हाल V4L2_SEL_TGT_NATIVE_SIZE:
		sel->r.top = 0;
		sel->r.left = 0;
		sel->r.width = IMX219_NATIVE_WIDTH;
		sel->r.height = IMX219_NATIVE_HEIGHT;

		वापस 0;

	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.top = IMX219_PIXEL_ARRAY_TOP;
		sel->r.left = IMX219_PIXEL_ARRAY_LEFT;
		sel->r.width = IMX219_PIXEL_ARRAY_WIDTH;
		sel->r.height = IMX219_PIXEL_ARRAY_HEIGHT;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक imx219_start_streaming(काष्ठा imx219 *imx219)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	स्थिर काष्ठा imx219_reg_list *reg_list;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&client->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&client->dev);
		वापस ret;
	पूर्ण

	/* Apply शेष values of current mode */
	reg_list = &imx219->mode->reg_list;
	ret = imx219_ग_लिखो_regs(imx219, reg_list->regs, reg_list->num_of_regs);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set mode\n", __func__);
		जाओ err_rpm_put;
	पूर्ण

	ret = imx219_set_framefmt(imx219);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set frame format: %d\n",
			__func__, ret);
		जाओ err_rpm_put;
	पूर्ण

	/* Apply customized values from user */
	ret =  __v4l2_ctrl_handler_setup(imx219->sd.ctrl_handler);
	अगर (ret)
		जाओ err_rpm_put;

	/* set stream on रेजिस्टर */
	ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_MODE_SELECT,
			       IMX219_REG_VALUE_08BIT, IMX219_MODE_STREAMING);
	अगर (ret)
		जाओ err_rpm_put;

	/* vflip and hflip cannot change during streaming */
	__v4l2_ctrl_grab(imx219->vflip, true);
	__v4l2_ctrl_grab(imx219->hflip, true);

	वापस 0;

err_rpm_put:
	pm_runसमय_put(&client->dev);
	वापस ret;
पूर्ण

अटल व्योम imx219_stop_streaming(काष्ठा imx219 *imx219)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	पूर्णांक ret;

	/* set stream off रेजिस्टर */
	ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_MODE_SELECT,
			       IMX219_REG_VALUE_08BIT, IMX219_MODE_STANDBY);
	अगर (ret)
		dev_err(&client->dev, "%s failed to set stream\n", __func__);

	__v4l2_ctrl_grab(imx219->vflip, false);
	__v4l2_ctrl_grab(imx219->hflip, false);

	pm_runसमय_put(&client->dev);
पूर्ण

अटल पूर्णांक imx219_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx219 *imx219 = to_imx219(sd);
	पूर्णांक ret = 0;

	mutex_lock(&imx219->mutex);
	अगर (imx219->streaming == enable) अणु
		mutex_unlock(&imx219->mutex);
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		/*
		 * Apply शेष & customized values
		 * and then start streaming.
		 */
		ret = imx219_start_streaming(imx219);
		अगर (ret)
			जाओ err_unlock;
	पूर्ण अन्यथा अणु
		imx219_stop_streaming(imx219);
	पूर्ण

	imx219->streaming = enable;

	mutex_unlock(&imx219->mutex);

	वापस ret;

err_unlock:
	mutex_unlock(&imx219->mutex);

	वापस ret;
पूर्ण

/* Power/घड़ी management functions */
अटल पूर्णांक imx219_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx219 *imx219 = to_imx219(sd);
	पूर्णांक ret;

	ret = regulator_bulk_enable(IMX219_NUM_SUPPLIES,
				    imx219->supplies);
	अगर (ret) अणु
		dev_err(dev, "%s: failed to enable regulators\n",
			__func__);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(imx219->xclk);
	अगर (ret) अणु
		dev_err(dev, "%s: failed to enable clock\n",
			__func__);
		जाओ reg_off;
	पूर्ण

	gpiod_set_value_cansleep(imx219->reset_gpio, 1);
	usleep_range(IMX219_XCLR_MIN_DELAY_US,
		     IMX219_XCLR_MIN_DELAY_US + IMX219_XCLR_DELAY_RANGE_US);

	वापस 0;

reg_off:
	regulator_bulk_disable(IMX219_NUM_SUPPLIES, imx219->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक imx219_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx219 *imx219 = to_imx219(sd);

	gpiod_set_value_cansleep(imx219->reset_gpio, 0);
	regulator_bulk_disable(IMX219_NUM_SUPPLIES, imx219->supplies);
	clk_disable_unprepare(imx219->xclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx219_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx219 *imx219 = to_imx219(sd);

	अगर (imx219->streaming)
		imx219_stop_streaming(imx219);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx219_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx219 *imx219 = to_imx219(sd);
	पूर्णांक ret;

	अगर (imx219->streaming) अणु
		ret = imx219_start_streaming(imx219);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	imx219_stop_streaming(imx219);
	imx219->streaming = false;

	वापस ret;
पूर्ण

अटल पूर्णांक imx219_get_regulators(काष्ठा imx219 *imx219)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IMX219_NUM_SUPPLIES; i++)
		imx219->supplies[i].supply = imx219_supply_name[i];

	वापस devm_regulator_bulk_get(&client->dev,
				       IMX219_NUM_SUPPLIES,
				       imx219->supplies);
पूर्ण

/* Verअगरy chip ID */
अटल पूर्णांक imx219_identअगरy_module(काष्ठा imx219 *imx219)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	पूर्णांक ret;
	u32 val;

	ret = imx219_पढ़ो_reg(imx219, IMX219_REG_CHIP_ID,
			      IMX219_REG_VALUE_16BIT, &val);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to read chip id %x\n",
			IMX219_CHIP_ID);
		वापस ret;
	पूर्ण

	अगर (val != IMX219_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x\n",
			IMX219_CHIP_ID, val);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops imx219_core_ops = अणु
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops imx219_video_ops = अणु
	.s_stream = imx219_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx219_pad_ops = अणु
	.क्रमागत_mbus_code = imx219_क्रमागत_mbus_code,
	.get_fmt = imx219_get_pad_क्रमmat,
	.set_fmt = imx219_set_pad_क्रमmat,
	.get_selection = imx219_get_selection,
	.क्रमागत_frame_size = imx219_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx219_subdev_ops = अणु
	.core = &imx219_core_ops,
	.video = &imx219_video_ops,
	.pad = &imx219_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops imx219_पूर्णांकernal_ops = अणु
	.खोलो = imx219_खोलो,
पूर्ण;

/* Initialize control handlers */
अटल पूर्णांक imx219_init_controls(काष्ठा imx219 *imx219)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx219->sd);
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	अचिन्हित पूर्णांक height = imx219->mode->height;
	काष्ठा v4l2_fwnode_device_properties props;
	पूर्णांक exposure_max, exposure_def, hblank;
	पूर्णांक i, ret;

	ctrl_hdlr = &imx219->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 12);
	अगर (ret)
		वापस ret;

	mutex_init(&imx219->mutex);
	ctrl_hdlr->lock = &imx219->mutex;

	/* By शेष, PIXEL_RATE is पढ़ो only */
	imx219->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops,
					       V4L2_CID_PIXEL_RATE,
					       IMX219_PIXEL_RATE,
					       IMX219_PIXEL_RATE, 1,
					       IMX219_PIXEL_RATE);

	imx219->link_freq =
		v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr, &imx219_ctrl_ops,
				       V4L2_CID_LINK_FREQ,
				       ARRAY_SIZE(imx219_link_freq_menu) - 1, 0,
				       imx219_link_freq_menu);
	अगर (imx219->link_freq)
		imx219->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	/* Initial vblank/hblank/exposure parameters based on current mode */
	imx219->vblank = v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops,
					   V4L2_CID_VBLANK, IMX219_VBLANK_MIN,
					   IMX219_VTS_MAX - height, 1,
					   imx219->mode->vts_def - height);
	hblank = IMX219_PPL_DEFAULT - imx219->mode->width;
	imx219->hblank = v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops,
					   V4L2_CID_HBLANK, hblank, hblank,
					   1, hblank);
	अगर (imx219->hblank)
		imx219->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	exposure_max = imx219->mode->vts_def - 4;
	exposure_def = (exposure_max < IMX219_EXPOSURE_DEFAULT) ?
		exposure_max : IMX219_EXPOSURE_DEFAULT;
	imx219->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     IMX219_EXPOSURE_MIN, exposure_max,
					     IMX219_EXPOSURE_STEP,
					     exposure_def);

	v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  IMX219_ANA_GAIN_MIN, IMX219_ANA_GAIN_MAX,
			  IMX219_ANA_GAIN_STEP, IMX219_ANA_GAIN_DEFAULT);

	v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  IMX219_DGTL_GAIN_MIN, IMX219_DGTL_GAIN_MAX,
			  IMX219_DGTL_GAIN_STEP, IMX219_DGTL_GAIN_DEFAULT);

	imx219->hflip = v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops,
					  V4L2_CID_HFLIP, 0, 1, 1, 0);
	अगर (imx219->hflip)
		imx219->hflip->flags |= V4L2_CTRL_FLAG_MODIFY_LAYOUT;

	imx219->vflip = v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops,
					  V4L2_CID_VFLIP, 0, 1, 1, 0);
	अगर (imx219->vflip)
		imx219->vflip->flags |= V4L2_CTRL_FLAG_MODIFY_LAYOUT;

	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &imx219_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(imx219_test_pattern_menu) - 1,
				     0, 0, imx219_test_pattern_menu);
	क्रम (i = 0; i < 4; i++) अणु
		/*
		 * The assumption is that
		 * V4L2_CID_TEST_PATTERN_GREENR == V4L2_CID_TEST_PATTERN_RED + 1
		 * V4L2_CID_TEST_PATTERN_BLUE   == V4L2_CID_TEST_PATTERN_RED + 2
		 * V4L2_CID_TEST_PATTERN_GREENB == V4L2_CID_TEST_PATTERN_RED + 3
		 */
		v4l2_ctrl_new_std(ctrl_hdlr, &imx219_ctrl_ops,
				  V4L2_CID_TEST_PATTERN_RED + i,
				  IMX219_TESTP_COLOUR_MIN,
				  IMX219_TESTP_COLOUR_MAX,
				  IMX219_TESTP_COLOUR_STEP,
				  IMX219_TESTP_COLOUR_MAX);
		/* The "Solid color" pattern is white by शेष */
	पूर्ण

	अगर (ctrl_hdlr->error) अणु
		ret = ctrl_hdlr->error;
		dev_err(&client->dev, "%s control init failed (%d)\n",
			__func__, ret);
		जाओ error;
	पूर्ण

	ret = v4l2_fwnode_device_parse(&client->dev, &props);
	अगर (ret)
		जाओ error;

	ret = v4l2_ctrl_new_fwnode_properties(ctrl_hdlr, &imx219_ctrl_ops,
					      &props);
	अगर (ret)
		जाओ error;

	imx219->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(ctrl_hdlr);
	mutex_destroy(&imx219->mutex);

	वापस ret;
पूर्ण

अटल व्योम imx219_मुक्त_controls(काष्ठा imx219 *imx219)
अणु
	v4l2_ctrl_handler_मुक्त(imx219->sd.ctrl_handler);
	mutex_destroy(&imx219->mutex);
पूर्ण

अटल पूर्णांक imx219_check_hwcfg(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	पूर्णांक ret = -EINVAL;

	endpoपूर्णांक = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(dev), शून्य);
	अगर (!endpoपूर्णांक) अणु
		dev_err(dev, "endpoint node not found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (v4l2_fwnode_endpoपूर्णांक_alloc_parse(endpoपूर्णांक, &ep_cfg)) अणु
		dev_err(dev, "could not parse endpoint\n");
		जाओ error_out;
	पूर्ण

	/* Check the number of MIPI CSI2 data lanes */
	अगर (ep_cfg.bus.mipi_csi2.num_data_lanes != 2) अणु
		dev_err(dev, "only 2 data lanes are currently supported\n");
		जाओ error_out;
	पूर्ण

	/* Check the link frequency set in device tree */
	अगर (!ep_cfg.nr_of_link_frequencies) अणु
		dev_err(dev, "link-frequency property not found in DT\n");
		जाओ error_out;
	पूर्ण

	अगर (ep_cfg.nr_of_link_frequencies != 1 ||
	    ep_cfg.link_frequencies[0] != IMX219_DEFAULT_LINK_FREQ) अणु
		dev_err(dev, "Link frequency not supported: %lld\n",
			ep_cfg.link_frequencies[0]);
		जाओ error_out;
	पूर्ण

	ret = 0;

error_out:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&ep_cfg);
	fwnode_handle_put(endpoपूर्णांक);

	वापस ret;
पूर्ण

अटल पूर्णांक imx219_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा imx219 *imx219;
	पूर्णांक ret;

	imx219 = devm_kzalloc(&client->dev, माप(*imx219), GFP_KERNEL);
	अगर (!imx219)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&imx219->sd, client, &imx219_subdev_ops);

	/* Check the hardware configuration in device tree */
	अगर (imx219_check_hwcfg(dev))
		वापस -EINVAL;

	/* Get प्रणाली घड़ी (xclk) */
	imx219->xclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(imx219->xclk)) अणु
		dev_err(dev, "failed to get xclk\n");
		वापस PTR_ERR(imx219->xclk);
	पूर्ण

	imx219->xclk_freq = clk_get_rate(imx219->xclk);
	अगर (imx219->xclk_freq != IMX219_XCLK_FREQ) अणु
		dev_err(dev, "xclk frequency not supported: %d Hz\n",
			imx219->xclk_freq);
		वापस -EINVAL;
	पूर्ण

	ret = imx219_get_regulators(imx219);
	अगर (ret) अणु
		dev_err(dev, "failed to get regulators\n");
		वापस ret;
	पूर्ण

	/* Request optional enable pin */
	imx219->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_HIGH);

	/*
	 * The sensor must be घातered क्रम imx219_identअगरy_module()
	 * to be able to पढ़ो the CHIP_ID रेजिस्टर
	 */
	ret = imx219_घातer_on(dev);
	अगर (ret)
		वापस ret;

	ret = imx219_identअगरy_module(imx219);
	अगर (ret)
		जाओ error_घातer_off;

	/* Set शेष mode to max resolution */
	imx219->mode = &supported_modes[0];

	/* sensor करोesn't enter LP-11 state upon घातer up until and unless
	 * streaming is started, so upon घातer up चयन the modes to:
	 * streaming -> standby
	 */
	ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_MODE_SELECT,
			       IMX219_REG_VALUE_08BIT, IMX219_MODE_STREAMING);
	अगर (ret < 0)
		जाओ error_घातer_off;
	usleep_range(100, 110);

	/* put sensor back to standby mode */
	ret = imx219_ग_लिखो_reg(imx219, IMX219_REG_MODE_SELECT,
			       IMX219_REG_VALUE_08BIT, IMX219_MODE_STANDBY);
	अगर (ret < 0)
		जाओ error_घातer_off;
	usleep_range(100, 110);

	ret = imx219_init_controls(imx219);
	अगर (ret)
		जाओ error_घातer_off;

	/* Initialize subdev */
	imx219->sd.पूर्णांकernal_ops = &imx219_पूर्णांकernal_ops;
	imx219->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
			    V4L2_SUBDEV_FL_HAS_EVENTS;
	imx219->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	/* Initialize source pad */
	imx219->pad.flags = MEDIA_PAD_FL_SOURCE;

	/* Initialize शेष क्रमmat */
	imx219_set_शेष_क्रमmat(imx219);

	ret = media_entity_pads_init(&imx219->sd.entity, 1, &imx219->pad);
	अगर (ret) अणु
		dev_err(dev, "failed to init entity pads: %d\n", ret);
		जाओ error_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&imx219->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register sensor sub-device: %d\n", ret);
		जाओ error_media_entity;
	पूर्ण

	/* Enable runसमय PM and turn off the device */
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	वापस 0;

error_media_entity:
	media_entity_cleanup(&imx219->sd.entity);

error_handler_मुक्त:
	imx219_मुक्त_controls(imx219);

error_घातer_off:
	imx219_घातer_off(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक imx219_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx219 *imx219 = to_imx219(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	imx219_मुक्त_controls(imx219);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		imx219_घातer_off(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx219_dt_ids[] = अणु
	अणु .compatible = "sony,imx219" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx219_dt_ids);

अटल स्थिर काष्ठा dev_pm_ops imx219_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(imx219_suspend, imx219_resume)
	SET_RUNTIME_PM_OPS(imx219_घातer_off, imx219_घातer_on, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver imx219_i2c_driver = अणु
	.driver = अणु
		.name = "imx219",
		.of_match_table	= imx219_dt_ids,
		.pm = &imx219_pm_ops,
	पूर्ण,
	.probe_new = imx219_probe,
	.हटाओ = imx219_हटाओ,
पूर्ण;

module_i2c_driver(imx219_i2c_driver);

MODULE_AUTHOR("Dave Stevenson <dave.stevenson@raspberrypi.com");
MODULE_DESCRIPTION("Sony IMX219 sensor driver");
MODULE_LICENSE("GPL v2");
