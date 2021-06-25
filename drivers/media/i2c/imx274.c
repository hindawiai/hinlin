<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * imx274.c - IMX274 CMOS Image Sensor driver
 *
 * Copyright (C) 2017, Leopard Imaging, Inc.
 *
 * Leon Luo <leonl@leopardimaging.com>
 * Edwin Zou <edwinz@leopardimaging.com>
 * Luca Ceresoli <luca@lucaceresoli.net>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

/*
 * See "SHR, SVR Setting" in datasheet
 */
#घोषणा IMX274_DEFAULT_FRAME_LENGTH		(4550)
#घोषणा IMX274_MAX_FRAME_LENGTH			(0x000fffff)

/*
 * See "Frame Rate Adjustment" in datasheet
 */
#घोषणा IMX274_PIXCLK_CONST1			(72000000)
#घोषणा IMX274_PIXCLK_CONST2			(1000000)

/*
 * The input gain is shअगरted by IMX274_GAIN_SHIFT to get
 * decimal number. The real gain is
 * (भग्न)input_gain_value / (1 << IMX274_GAIN_SHIFT)
 */
#घोषणा IMX274_GAIN_SHIFT			(8)
#घोषणा IMX274_GAIN_SHIFT_MASK			((1 << IMX274_GAIN_SHIFT) - 1)

/*
 * See "Analog Gain" and "Digital Gain" in datasheet
 * min gain is 1X
 * max gain is calculated based on IMX274_GAIN_REG_MAX
 */
#घोषणा IMX274_GAIN_REG_MAX			(1957)
#घोषणा IMX274_MIN_GAIN				(0x01 << IMX274_GAIN_SHIFT)
#घोषणा IMX274_MAX_ANALOG_GAIN			((2048 << IMX274_GAIN_SHIFT)\
					/ (2048 - IMX274_GAIN_REG_MAX))
#घोषणा IMX274_MAX_DIGITAL_GAIN			(8)
#घोषणा IMX274_DEF_GAIN				(20 << IMX274_GAIN_SHIFT)
#घोषणा IMX274_GAIN_CONST			(2048) /* क्रम gain क्रमmula */

/*
 * 1 line समय in us = (HMAX / 72), minimal is 4 lines
 */
#घोषणा IMX274_MIN_EXPOSURE_TIME		(4 * 260 / 72)

#घोषणा IMX274_MAX_WIDTH			(3840)
#घोषणा IMX274_MAX_HEIGHT			(2160)
#घोषणा IMX274_MAX_FRAME_RATE			(120)
#घोषणा IMX274_MIN_FRAME_RATE			(5)
#घोषणा IMX274_DEF_FRAME_RATE			(60)

/*
 * रेजिस्टर SHR is limited to (SVR value + 1) x VMAX value - 4
 */
#घोषणा IMX274_SHR_LIMIT_CONST			(4)

/*
 * Min and max sensor reset delay (microseconds)
 */
#घोषणा IMX274_RESET_DELAY1			(2000)
#घोषणा IMX274_RESET_DELAY2			(2200)

/*
 * shअगरt and mask स्थिरants
 */
#घोषणा IMX274_SHIFT_8_BITS			(8)
#घोषणा IMX274_SHIFT_16_BITS			(16)
#घोषणा IMX274_MASK_LSB_2_BITS			(0x03)
#घोषणा IMX274_MASK_LSB_3_BITS			(0x07)
#घोषणा IMX274_MASK_LSB_4_BITS			(0x0f)
#घोषणा IMX274_MASK_LSB_8_BITS			(0x00ff)

#घोषणा DRIVER_NAME "IMX274"

/*
 * IMX274 रेजिस्टर definitions
 */
#घोषणा IMX274_SHR_REG_MSB			0x300D /* SHR */
#घोषणा IMX274_SHR_REG_LSB			0x300C /* SHR */
#घोषणा IMX274_SVR_REG_MSB			0x300F /* SVR */
#घोषणा IMX274_SVR_REG_LSB			0x300E /* SVR */
#घोषणा IMX274_HTRIM_EN_REG			0x3037
#घोषणा IMX274_HTRIM_START_REG_LSB		0x3038
#घोषणा IMX274_HTRIM_START_REG_MSB		0x3039
#घोषणा IMX274_HTRIM_END_REG_LSB		0x303A
#घोषणा IMX274_HTRIM_END_REG_MSB		0x303B
#घोषणा IMX274_VWIDCUTEN_REG			0x30DD
#घोषणा IMX274_VWIDCUT_REG_LSB			0x30DE
#घोषणा IMX274_VWIDCUT_REG_MSB			0x30DF
#घोषणा IMX274_VWINPOS_REG_LSB			0x30E0
#घोषणा IMX274_VWINPOS_REG_MSB			0x30E1
#घोषणा IMX274_WRITE_VSIZE_REG_LSB		0x3130
#घोषणा IMX274_WRITE_VSIZE_REG_MSB		0x3131
#घोषणा IMX274_Y_OUT_SIZE_REG_LSB		0x3132
#घोषणा IMX274_Y_OUT_SIZE_REG_MSB		0x3133
#घोषणा IMX274_VMAX_REG_1			0x30FA /* VMAX, MSB */
#घोषणा IMX274_VMAX_REG_2			0x30F9 /* VMAX */
#घोषणा IMX274_VMAX_REG_3			0x30F8 /* VMAX, LSB */
#घोषणा IMX274_HMAX_REG_MSB			0x30F7 /* HMAX */
#घोषणा IMX274_HMAX_REG_LSB			0x30F6 /* HMAX */
#घोषणा IMX274_ANALOG_GAIN_ADDR_LSB		0x300A /* ANALOG GAIN LSB */
#घोषणा IMX274_ANALOG_GAIN_ADDR_MSB		0x300B /* ANALOG GAIN MSB */
#घोषणा IMX274_DIGITAL_GAIN_REG			0x3012 /* Digital Gain */
#घोषणा IMX274_VFLIP_REG			0x301A /* VERTICAL FLIP */
#घोषणा IMX274_TEST_PATTERN_REG			0x303D /* TEST PATTERN */
#घोषणा IMX274_STANDBY_REG			0x3000 /* STANDBY */

#घोषणा IMX274_TABLE_WAIT_MS			0
#घोषणा IMX274_TABLE_END			1

/* regulator supplies */
अटल स्थिर अक्षर * स्थिर imx274_supply_names[] = अणु
	"vddl",  /* IF (1.2V) supply */
	"vdig",  /* Digital Core (1.8V) supply */
	"vana",  /* Analog (2.8V) supply */
पूर्ण;

#घोषणा IMX274_NUM_SUPPLIES ARRAY_SIZE(imx274_supply_names)

/*
 * imx274 I2C operation related काष्ठाure
 */
काष्ठा reg_8 अणु
	u16 addr;
	u8 val;
पूर्ण;

अटल स्थिर काष्ठा regmap_config imx274_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/*
 * Parameters क्रम each imx274 पढ़ोout mode.
 *
 * These are the values to configure the sensor in one of the
 * implemented modes.
 *
 * @init_regs: रेजिस्टरs to initialize the mode
 * @wbin_ratio: width करोwnscale factor (e.g. 3 क्रम 1280; 3 = 3840/1280)
 * @hbin_ratio: height करोwnscale factor (e.g. 3 क्रम 720; 3 = 2160/720)
 * @min_frame_len: Minimum frame length क्रम each mode (see "Frame Rate
 *                 Adjusपंचांगent (CSI-2)" in the datasheet)
 * @min_SHR: Minimum SHR रेजिस्टर value (see "Shutter Setting (CSI-2)" in the
 *           datasheet)
 * @max_fps: Maximum frames per second
 * @nocpiop: Number of घड़ीs per पूर्णांकernal offset period (see "Integration Time
 *           in Each Reaकरोut Drive Mode (CSI-2)" in the datasheet)
 */
काष्ठा imx274_mode अणु
	स्थिर काष्ठा reg_8 *init_regs;
	u8 wbin_ratio;
	u8 hbin_ratio;
	पूर्णांक min_frame_len;
	पूर्णांक min_SHR;
	पूर्णांक max_fps;
	पूर्णांक nocpiop;
पूर्ण;

/*
 * imx274 test pattern related काष्ठाure
 */
क्रमागत अणु
	TEST_PATTERN_DISABLED = 0,
	TEST_PATTERN_ALL_000H,
	TEST_PATTERN_ALL_FFFH,
	TEST_PATTERN_ALL_555H,
	TEST_PATTERN_ALL_AAAH,
	TEST_PATTERN_VSP_5AH, /* VERTICAL STRIPE PATTERN 555H/AAAH */
	TEST_PATTERN_VSP_A5H, /* VERTICAL STRIPE PATTERN AAAH/555H */
	TEST_PATTERN_VSP_05H, /* VERTICAL STRIPE PATTERN 000H/555H */
	TEST_PATTERN_VSP_50H, /* VERTICAL STRIPE PATTERN 555H/000H */
	TEST_PATTERN_VSP_0FH, /* VERTICAL STRIPE PATTERN 000H/FFFH */
	TEST_PATTERN_VSP_F0H, /* VERTICAL STRIPE PATTERN FFFH/000H */
	TEST_PATTERN_H_COLOR_BARS,
	TEST_PATTERN_V_COLOR_BARS,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tp_qmenu[] = अणु
	"Disabled",
	"All 000h Pattern",
	"All FFFh Pattern",
	"All 555h Pattern",
	"All AAAh Pattern",
	"Vertical Stripe (555h / AAAh)",
	"Vertical Stripe (AAAh / 555h)",
	"Vertical Stripe (000h / 555h)",
	"Vertical Stripe (555h / 000h)",
	"Vertical Stripe (000h / FFFh)",
	"Vertical Stripe (FFFh / 000h)",
	"Vertical Color Bars",
	"Horizontal Color Bars",
पूर्ण;

/*
 * All-pixel scan mode (10-bit)
 * imx274 mode1(refer to datasheet) रेजिस्टर configuration with
 * 3840x2160 resolution, raw10 data and mipi four lane output
 */
अटल स्थिर काष्ठा reg_8 imx274_mode1_3840x2160_raw10[] = अणु
	अणु0x3004, 0x01पूर्ण,
	अणु0x3005, 0x01पूर्ण,
	अणु0x3006, 0x00पूर्ण,
	अणु0x3007, 0xa2पूर्ण,

	अणु0x3018, 0xA2पूर्ण, /* output XVS, HVS */

	अणु0x306B, 0x05पूर्ण,
	अणु0x30E2, 0x01पूर्ण,

	अणु0x30EE, 0x01पूर्ण,
	अणु0x3342, 0x0Aपूर्ण,
	अणु0x3343, 0x00पूर्ण,
	अणु0x3344, 0x16पूर्ण,
	अणु0x3345, 0x00पूर्ण,
	अणु0x33A6, 0x01पूर्ण,
	अणु0x3528, 0x0Eपूर्ण,
	अणु0x3554, 0x1Fपूर्ण,
	अणु0x3555, 0x01पूर्ण,
	अणु0x3556, 0x01पूर्ण,
	अणु0x3557, 0x01पूर्ण,
	अणु0x3558, 0x01पूर्ण,
	अणु0x3559, 0x00पूर्ण,
	अणु0x355A, 0x00पूर्ण,
	अणु0x35BA, 0x0Eपूर्ण,
	अणु0x366A, 0x1Bपूर्ण,
	अणु0x366B, 0x1Aपूर्ण,
	अणु0x366C, 0x19पूर्ण,
	अणु0x366D, 0x17पूर्ण,
	अणु0x3A41, 0x08पूर्ण,

	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * Horizontal/vertical 2/2-line binning
 * (Horizontal and vertical weightedbinning, 10-bit)
 * imx274 mode3(refer to datasheet) रेजिस्टर configuration with
 * 1920x1080 resolution, raw10 data and mipi four lane output
 */
अटल स्थिर काष्ठा reg_8 imx274_mode3_1920x1080_raw10[] = अणु
	अणु0x3004, 0x02पूर्ण,
	अणु0x3005, 0x21पूर्ण,
	अणु0x3006, 0x00पूर्ण,
	अणु0x3007, 0xb1पूर्ण,

	अणु0x3018, 0xA2पूर्ण, /* output XVS, HVS */

	अणु0x306B, 0x05पूर्ण,
	अणु0x30E2, 0x02पूर्ण,

	अणु0x30EE, 0x01पूर्ण,
	अणु0x3342, 0x0Aपूर्ण,
	अणु0x3343, 0x00पूर्ण,
	अणु0x3344, 0x1Aपूर्ण,
	अणु0x3345, 0x00पूर्ण,
	अणु0x33A6, 0x01पूर्ण,
	अणु0x3528, 0x0Eपूर्ण,
	अणु0x3554, 0x00पूर्ण,
	अणु0x3555, 0x01पूर्ण,
	अणु0x3556, 0x01पूर्ण,
	अणु0x3557, 0x01पूर्ण,
	अणु0x3558, 0x01पूर्ण,
	अणु0x3559, 0x00पूर्ण,
	अणु0x355A, 0x00पूर्ण,
	अणु0x35BA, 0x0Eपूर्ण,
	अणु0x366A, 0x1Bपूर्ण,
	अणु0x366B, 0x1Aपूर्ण,
	अणु0x366C, 0x19पूर्ण,
	अणु0x366D, 0x17पूर्ण,
	अणु0x3A41, 0x08पूर्ण,

	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * Vertical 2/3 subsampling binning horizontal 3 binning
 * imx274 mode5(refer to datasheet) रेजिस्टर configuration with
 * 1280x720 resolution, raw10 data and mipi four lane output
 */
अटल स्थिर काष्ठा reg_8 imx274_mode5_1280x720_raw10[] = अणु
	अणु0x3004, 0x03पूर्ण,
	अणु0x3005, 0x31पूर्ण,
	अणु0x3006, 0x00पूर्ण,
	अणु0x3007, 0xa9पूर्ण,

	अणु0x3018, 0xA2पूर्ण, /* output XVS, HVS */

	अणु0x306B, 0x05पूर्ण,
	अणु0x30E2, 0x03पूर्ण,

	अणु0x30EE, 0x01पूर्ण,
	अणु0x3342, 0x0Aपूर्ण,
	अणु0x3343, 0x00पूर्ण,
	अणु0x3344, 0x1Bपूर्ण,
	अणु0x3345, 0x00पूर्ण,
	अणु0x33A6, 0x01पूर्ण,
	अणु0x3528, 0x0Eपूर्ण,
	अणु0x3554, 0x00पूर्ण,
	अणु0x3555, 0x01पूर्ण,
	अणु0x3556, 0x01पूर्ण,
	अणु0x3557, 0x01पूर्ण,
	अणु0x3558, 0x01पूर्ण,
	अणु0x3559, 0x00पूर्ण,
	अणु0x355A, 0x00पूर्ण,
	अणु0x35BA, 0x0Eपूर्ण,
	अणु0x366A, 0x1Bपूर्ण,
	अणु0x366B, 0x19पूर्ण,
	अणु0x366C, 0x17पूर्ण,
	अणु0x366D, 0x17पूर्ण,
	अणु0x3A41, 0x04पूर्ण,

	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * Vertical 2/8 subsampling horizontal 3 binning
 * imx274 mode6(refer to datasheet) रेजिस्टर configuration with
 * 1280x540 resolution, raw10 data and mipi four lane output
 */
अटल स्थिर काष्ठा reg_8 imx274_mode6_1280x540_raw10[] = अणु
	अणु0x3004, 0x04पूर्ण, /* mode setting */
	अणु0x3005, 0x31पूर्ण,
	अणु0x3006, 0x00पूर्ण,
	अणु0x3007, 0x02पूर्ण, /* mode setting */

	अणु0x3018, 0xA2पूर्ण, /* output XVS, HVS */

	अणु0x306B, 0x05पूर्ण,
	अणु0x30E2, 0x04पूर्ण, /* mode setting */

	अणु0x30EE, 0x01पूर्ण,
	अणु0x3342, 0x0Aपूर्ण,
	अणु0x3343, 0x00पूर्ण,
	अणु0x3344, 0x16पूर्ण,
	अणु0x3345, 0x00पूर्ण,
	अणु0x33A6, 0x01पूर्ण,
	अणु0x3528, 0x0Eपूर्ण,
	अणु0x3554, 0x1Fपूर्ण,
	अणु0x3555, 0x01पूर्ण,
	अणु0x3556, 0x01पूर्ण,
	अणु0x3557, 0x01पूर्ण,
	अणु0x3558, 0x01पूर्ण,
	अणु0x3559, 0x00पूर्ण,
	अणु0x355A, 0x00पूर्ण,
	अणु0x35BA, 0x0Eपूर्ण,
	अणु0x366A, 0x1Bपूर्ण,
	अणु0x366B, 0x1Aपूर्ण,
	अणु0x366C, 0x19पूर्ण,
	अणु0x366D, 0x17पूर्ण,
	अणु0x3A41, 0x04पूर्ण,

	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * imx274 first step रेजिस्टर configuration क्रम
 * starting stream
 */
अटल स्थिर काष्ठा reg_8 imx274_start_1[] = अणु
	अणुIMX274_STANDBY_REG, 0x12पूर्ण,

	/* PLRD: घड़ी settings */
	अणु0x3120, 0xF0पूर्ण,
	अणु0x3121, 0x00पूर्ण,
	अणु0x3122, 0x02पूर्ण,
	अणु0x3129, 0x9Cपूर्ण,
	अणु0x312A, 0x02पूर्ण,
	अणु0x312D, 0x02पूर्ण,

	अणु0x310B, 0x00पूर्ण,

	/* PLSTMG */
	अणु0x304C, 0x00पूर्ण, /* PLSTMG01 */
	अणु0x304D, 0x03पूर्ण,
	अणु0x331C, 0x1Aपूर्ण,
	अणु0x331D, 0x00पूर्ण,
	अणु0x3502, 0x02पूर्ण,
	अणु0x3529, 0x0Eपूर्ण,
	अणु0x352A, 0x0Eपूर्ण,
	अणु0x352B, 0x0Eपूर्ण,
	अणु0x3538, 0x0Eपूर्ण,
	अणु0x3539, 0x0Eपूर्ण,
	अणु0x3553, 0x00पूर्ण,
	अणु0x357D, 0x05पूर्ण,
	अणु0x357F, 0x05पूर्ण,
	अणु0x3581, 0x04पूर्ण,
	अणु0x3583, 0x76पूर्ण,
	अणु0x3587, 0x01पूर्ण,
	अणु0x35BB, 0x0Eपूर्ण,
	अणु0x35BC, 0x0Eपूर्ण,
	अणु0x35BD, 0x0Eपूर्ण,
	अणु0x35BE, 0x0Eपूर्ण,
	अणु0x35BF, 0x0Eपूर्ण,
	अणु0x366E, 0x00पूर्ण,
	अणु0x366F, 0x00पूर्ण,
	अणु0x3670, 0x00पूर्ण,
	अणु0x3671, 0x00पूर्ण,

	/* PSMIPI */
	अणु0x3304, 0x32पूर्ण, /* PSMIPI1 */
	अणु0x3305, 0x00पूर्ण,
	अणु0x3306, 0x32पूर्ण,
	अणु0x3307, 0x00पूर्ण,
	अणु0x3590, 0x32पूर्ण,
	अणु0x3591, 0x00पूर्ण,
	अणु0x3686, 0x32पूर्ण,
	अणु0x3687, 0x00पूर्ण,

	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * imx274 second step रेजिस्टर configuration क्रम
 * starting stream
 */
अटल स्थिर काष्ठा reg_8 imx274_start_2[] = अणु
	अणुIMX274_STANDBY_REG, 0x00पूर्ण,
	अणु0x303E, 0x02पूर्ण, /* SYS_MODE = 2 */
	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * imx274 third step रेजिस्टर configuration क्रम
 * starting stream
 */
अटल स्थिर काष्ठा reg_8 imx274_start_3[] = अणु
	अणु0x30F4, 0x00पूर्ण,
	अणु0x3018, 0xA2पूर्ण, /* XHS VHS OUTPUT */
	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * imx274 रेजिस्टर configuration क्रम stopping stream
 */
अटल स्थिर काष्ठा reg_8 imx274_stop[] = अणु
	अणुIMX274_STANDBY_REG, 0x01पूर्ण,
	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * imx274 disable test pattern रेजिस्टर configuration
 */
अटल स्थिर काष्ठा reg_8 imx274_tp_disabled[] = अणु
	अणु0x303C, 0x00पूर्ण,
	अणु0x377F, 0x00पूर्ण,
	अणु0x3781, 0x00पूर्ण,
	अणु0x370B, 0x00पूर्ण,
	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * imx274 test pattern रेजिस्टर configuration
 * reg 0x303D defines the test pattern modes
 */
अटल स्थिर काष्ठा reg_8 imx274_tp_regs[] = अणु
	अणु0x303C, 0x11पूर्ण,
	अणु0x370E, 0x01पूर्ण,
	अणु0x377F, 0x01पूर्ण,
	अणु0x3781, 0x01पूर्ण,
	अणु0x370B, 0x11पूर्ण,
	अणुIMX274_TABLE_END, 0x00पूर्ण
पूर्ण;

/* nocpiop happens to be the same number क्रम the implemented modes */
अटल स्थिर काष्ठा imx274_mode imx274_modes[] = अणु
	अणु
		/* mode 1, 4K */
		.wbin_ratio = 1, /* 3840 */
		.hbin_ratio = 1, /* 2160 */
		.init_regs = imx274_mode1_3840x2160_raw10,
		.min_frame_len = 4550,
		.min_SHR = 12,
		.max_fps = 60,
		.nocpiop = 112,
	पूर्ण,
	अणु
		/* mode 3, 1080p */
		.wbin_ratio = 2, /* 1920 */
		.hbin_ratio = 2, /* 1080 */
		.init_regs = imx274_mode3_1920x1080_raw10,
		.min_frame_len = 2310,
		.min_SHR = 8,
		.max_fps = 120,
		.nocpiop = 112,
	पूर्ण,
	अणु
		/* mode 5, 720p */
		.wbin_ratio = 3, /* 1280 */
		.hbin_ratio = 3, /* 720 */
		.init_regs = imx274_mode5_1280x720_raw10,
		.min_frame_len = 2310,
		.min_SHR = 8,
		.max_fps = 120,
		.nocpiop = 112,
	पूर्ण,
	अणु
		/* mode 6, 540p */
		.wbin_ratio = 3, /* 1280 */
		.hbin_ratio = 4, /* 540 */
		.init_regs = imx274_mode6_1280x540_raw10,
		.min_frame_len = 2310,
		.min_SHR = 4,
		.max_fps = 120,
		.nocpiop = 112,
	पूर्ण,
पूर्ण;

/*
 * काष्ठा imx274_ctrls - imx274 ctrl काष्ठाure
 * @handler: V4L2 ctrl handler काष्ठाure
 * @exposure: Poपूर्णांकer to expsure ctrl काष्ठाure
 * @gain: Poपूर्णांकer to gain ctrl काष्ठाure
 * @vflip: Poपूर्णांकer to vflip ctrl काष्ठाure
 * @test_pattern: Poपूर्णांकer to test pattern ctrl काष्ठाure
 */
काष्ठा imx274_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *gain;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *test_pattern;
पूर्ण;

/*
 * काष्ठा stim274 - imx274 device काष्ठाure
 * @sd: V4L2 subdevice काष्ठाure
 * @pad: Media pad काष्ठाure
 * @client: Poपूर्णांकer to I2C client
 * @ctrls: imx274 control काष्ठाure
 * @crop: rect to be captured
 * @compose: compose rect, i.e. output resolution
 * @क्रमmat: V4L2 media bus frame क्रमmat काष्ठाure
 *          (width and height are in sync with the compose rect)
 * @frame_rate: V4L2 frame rate काष्ठाure
 * @regmap: Poपूर्णांकer to regmap काष्ठाure
 * @reset_gpio: Poपूर्णांकer to reset gpio
 * @supplies: List of analog and digital supply regulators
 * @inck: Poपूर्णांकer to sensor input घड़ी
 * @lock: Mutex काष्ठाure
 * @mode: Parameters क्रम the selected पढ़ोout mode
 */
काष्ठा stimx274 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा i2c_client *client;
	काष्ठा imx274_ctrls ctrls;
	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा v4l2_fract frame_पूर्णांकerval;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator_bulk_data supplies[IMX274_NUM_SUPPLIES];
	काष्ठा clk *inck;
	काष्ठा mutex lock; /* mutex lock क्रम operations */
	स्थिर काष्ठा imx274_mode *mode;
पूर्ण;

#घोषणा IMX274_ROUND(dim, step, flags)			\
	((flags) & V4L2_SEL_FLAG_GE			\
	 ? roundup((dim), (step))			\
	 : ((flags) & V4L2_SEL_FLAG_LE			\
	    ? roundकरोwn((dim), (step))			\
	    : roundकरोwn((dim) + (step) / 2, (step))))

/*
 * Function declaration
 */
अटल पूर्णांक imx274_set_gain(काष्ठा stimx274 *priv, काष्ठा v4l2_ctrl *ctrl);
अटल पूर्णांक imx274_set_exposure(काष्ठा stimx274 *priv, पूर्णांक val);
अटल पूर्णांक imx274_set_vflip(काष्ठा stimx274 *priv, पूर्णांक val);
अटल पूर्णांक imx274_set_test_pattern(काष्ठा stimx274 *priv, पूर्णांक val);
अटल पूर्णांक imx274_set_frame_पूर्णांकerval(काष्ठा stimx274 *priv,
				     काष्ठा v4l2_fract frame_पूर्णांकerval);

अटल अंतरभूत व्योम msleep_range(अचिन्हित पूर्णांक delay_base)
अणु
	usleep_range(delay_base * 1000, delay_base * 1000 + 500);
पूर्ण

/*
 * v4l2_ctrl and v4l2_subdev related operations
 */
अटल अंतरभूत काष्ठा v4l2_subdev *ctrl_to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler,
			     काष्ठा stimx274, ctrls.handler)->sd;
पूर्ण

अटल अंतरभूत काष्ठा stimx274 *to_imx274(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा stimx274, sd);
पूर्ण

/*
 * Writing a रेजिस्टर table
 *
 * @priv: Poपूर्णांकer to device
 * @table: Table containing रेजिस्टर values (with optional delays)
 *
 * This is used to ग_लिखो रेजिस्टर table पूर्णांकo sensor's reg map.
 *
 * Return: 0 on success, errors otherwise
 */
अटल पूर्णांक imx274_ग_लिखो_table(काष्ठा stimx274 *priv, स्थिर काष्ठा reg_8 table[])
अणु
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक err = 0;
	स्थिर काष्ठा reg_8 *next;
	u8 val;

	पूर्णांक range_start = -1;
	पूर्णांक range_count = 0;
	u8 range_vals[16];
	पूर्णांक max_range_vals = ARRAY_SIZE(range_vals);

	क्रम (next = table;; next++) अणु
		अगर ((next->addr != range_start + range_count) ||
		    (next->addr == IMX274_TABLE_END) ||
		    (next->addr == IMX274_TABLE_WAIT_MS) ||
		    (range_count == max_range_vals)) अणु
			अगर (range_count == 1)
				err = regmap_ग_लिखो(regmap,
						   range_start, range_vals[0]);
			अन्यथा अगर (range_count > 1)
				err = regmap_bulk_ग_लिखो(regmap, range_start,
							&range_vals[0],
							range_count);
			अन्यथा
				err = 0;

			अगर (err)
				वापस err;

			range_start = -1;
			range_count = 0;

			/* Handle special address values */
			अगर (next->addr == IMX274_TABLE_END)
				अवरोध;

			अगर (next->addr == IMX274_TABLE_WAIT_MS) अणु
				msleep_range(next->val);
				जारी;
			पूर्ण
		पूर्ण

		val = next->val;

		अगर (range_start == -1)
			range_start = next->addr;

		range_vals[range_count++] = val;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक imx274_ग_लिखो_reg(काष्ठा stimx274 *priv, u16 addr, u8 val)
अणु
	पूर्णांक err;

	err = regmap_ग_लिखो(priv->regmap, addr, val);
	अगर (err)
		dev_err(&priv->client->dev,
			"%s : i2c write failed, %x = %x\n", __func__,
			addr, val);
	अन्यथा
		dev_dbg(&priv->client->dev,
			"%s : addr 0x%x, val=0x%x\n", __func__,
			addr, val);
	वापस err;
पूर्ण

/**
 * imx274_पढ़ो_mbreg - Read a multibyte रेजिस्टर.
 *
 * Uses a bulk पढ़ो where possible.
 *
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @addr: Address of the LSB रेजिस्टर.  Other रेजिस्टरs must be
 *        consecutive, least-to-most signअगरicant.
 * @val: Poपूर्णांकer to store the रेजिस्टर value (cpu endianness)
 * @nbytes: Number of bytes to पढ़ो (range: [1..3]).
 *          Other bytes are zet to 0.
 *
 * Return: 0 on success, errors otherwise
 */
अटल पूर्णांक imx274_पढ़ो_mbreg(काष्ठा stimx274 *priv, u16 addr, u32 *val,
			     माप_प्रकार nbytes)
अणु
	__le32 val_le = 0;
	पूर्णांक err;

	err = regmap_bulk_पढ़ो(priv->regmap, addr, &val_le, nbytes);
	अगर (err) अणु
		dev_err(&priv->client->dev,
			"%s : i2c bulk read failed, %x (%zu bytes)\n",
			__func__, addr, nbytes);
	पूर्ण अन्यथा अणु
		*val = le32_to_cpu(val_le);
		dev_dbg(&priv->client->dev,
			"%s : addr 0x%x, val=0x%x (%zu bytes)\n",
			__func__, addr, *val, nbytes);
	पूर्ण

	वापस err;
पूर्ण

/**
 * imx274_ग_लिखो_mbreg - Write a multibyte रेजिस्टर.
 *
 * Uses a bulk ग_लिखो where possible.
 *
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @addr: Address of the LSB रेजिस्टर.  Other रेजिस्टरs must be
 *        consecutive, least-to-most signअगरicant.
 * @val: Value to be written to the रेजिस्टर (cpu endianness)
 * @nbytes: Number of bytes to ग_लिखो (range: [1..3])
 */
अटल पूर्णांक imx274_ग_लिखो_mbreg(काष्ठा stimx274 *priv, u16 addr, u32 val,
			      माप_प्रकार nbytes)
अणु
	__le32 val_le = cpu_to_le32(val);
	पूर्णांक err;

	err = regmap_bulk_ग_लिखो(priv->regmap, addr, &val_le, nbytes);
	अगर (err)
		dev_err(&priv->client->dev,
			"%s : i2c bulk write failed, %x = %x (%zu bytes)\n",
			__func__, addr, val, nbytes);
	अन्यथा
		dev_dbg(&priv->client->dev,
			"%s : addr 0x%x, val=0x%x (%zu bytes)\n",
			__func__, addr, val, nbytes);
	वापस err;
पूर्ण

/*
 * Set mode रेजिस्टरs to start stream.
 * @priv: Poपूर्णांकer to device काष्ठाure
 *
 * Return: 0 on success, errors otherwise
 */
अटल पूर्णांक imx274_mode_regs(काष्ठा stimx274 *priv)
अणु
	पूर्णांक err = 0;

	err = imx274_ग_लिखो_table(priv, imx274_start_1);
	अगर (err)
		वापस err;

	err = imx274_ग_लिखो_table(priv, priv->mode->init_regs);

	वापस err;
पूर्ण

/*
 * imx274_start_stream - Function क्रम starting stream per mode index
 * @priv: Poपूर्णांकer to device काष्ठाure
 *
 * Return: 0 on success, errors otherwise
 */
अटल पूर्णांक imx274_start_stream(काष्ठा stimx274 *priv)
अणु
	पूर्णांक err = 0;

	err = __v4l2_ctrl_handler_setup(&priv->ctrls.handler);
	अगर (err) अणु
		dev_err(&priv->client->dev, "Error %d setup controls\n", err);
		वापस err;
	पूर्ण

	/*
	 * Refer to "Standby Cancel Sequence when using CSI-2" in
	 * imx274 datasheet, it should रुको 10ms or more here.
	 * give it 1 extra ms क्रम margin
	 */
	msleep_range(11);
	err = imx274_ग_लिखो_table(priv, imx274_start_2);
	अगर (err)
		वापस err;

	/*
	 * Refer to "Standby Cancel Sequence when using CSI-2" in
	 * imx274 datasheet, it should रुको 7ms or more here.
	 * give it 1 extra ms क्रम margin
	 */
	msleep_range(8);
	err = imx274_ग_लिखो_table(priv, imx274_start_3);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/*
 * imx274_reset - Function called to reset the sensor
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @rst: Input value क्रम determining the sensor's end state after reset
 *
 * Set the senor in reset and then
 * अगर rst = 0, keep it in reset;
 * अगर rst = 1, bring it out of reset.
 *
 */
अटल व्योम imx274_reset(काष्ठा stimx274 *priv, पूर्णांक rst)
अणु
	gpiod_set_value_cansleep(priv->reset_gpio, 0);
	usleep_range(IMX274_RESET_DELAY1, IMX274_RESET_DELAY2);
	gpiod_set_value_cansleep(priv->reset_gpio, !!rst);
	usleep_range(IMX274_RESET_DELAY1, IMX274_RESET_DELAY2);
पूर्ण

अटल पूर्णांक imx274_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा stimx274 *imx274 = to_imx274(sd);
	पूर्णांक ret;

	/* keep sensor in reset beक्रमe घातer on */
	imx274_reset(imx274, 0);

	ret = clk_prepare_enable(imx274->inck);
	अगर (ret) अणु
		dev_err(&imx274->client->dev,
			"Failed to enable input clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(IMX274_NUM_SUPPLIES, imx274->supplies);
	अगर (ret) अणु
		dev_err(&imx274->client->dev,
			"Failed to enable regulators: %d\n", ret);
		जाओ fail_reg;
	पूर्ण

	udelay(2);
	imx274_reset(imx274, 1);

	वापस 0;

fail_reg:
	clk_disable_unprepare(imx274->inck);
	वापस ret;
पूर्ण

अटल पूर्णांक imx274_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा stimx274 *imx274 = to_imx274(sd);

	imx274_reset(imx274, 0);

	regulator_bulk_disable(IMX274_NUM_SUPPLIES, imx274->supplies);

	clk_disable_unprepare(imx274->inck);

	वापस 0;
पूर्ण

अटल पूर्णांक imx274_regulators_get(काष्ठा device *dev, काष्ठा stimx274 *imx274)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IMX274_NUM_SUPPLIES; i++)
		imx274->supplies[i].supply = imx274_supply_names[i];

	वापस devm_regulator_bulk_get(dev, IMX274_NUM_SUPPLIES,
					imx274->supplies);
पूर्ण

/**
 * imx274_s_ctrl - This is used to set the imx274 V4L2 controls
 * @ctrl: V4L2 control to be set
 *
 * This function is used to set the V4L2 controls क्रम the imx274 sensor.
 *
 * Return: 0 on success, errors otherwise
 */
अटल पूर्णांक imx274_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा stimx274 *imx274 = to_imx274(sd);
	पूर्णांक ret = -EINVAL;

	अगर (!pm_runसमय_get_अगर_in_use(&imx274->client->dev))
		वापस 0;

	dev_dbg(&imx274->client->dev,
		"%s : s_ctrl: %s, value: %d\n", __func__,
		ctrl->name, ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		dev_dbg(&imx274->client->dev,
			"%s : set V4L2_CID_EXPOSURE\n", __func__);
		ret = imx274_set_exposure(imx274, ctrl->val);
		अवरोध;

	हाल V4L2_CID_GAIN:
		dev_dbg(&imx274->client->dev,
			"%s : set V4L2_CID_GAIN\n", __func__);
		ret = imx274_set_gain(imx274, ctrl);
		अवरोध;

	हाल V4L2_CID_VFLIP:
		dev_dbg(&imx274->client->dev,
			"%s : set V4L2_CID_VFLIP\n", __func__);
		ret = imx274_set_vflip(imx274, ctrl->val);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		dev_dbg(&imx274->client->dev,
			"%s : set V4L2_CID_TEST_PATTERN\n", __func__);
		ret = imx274_set_test_pattern(imx274, ctrl->val);
		अवरोध;
	पूर्ण

	pm_runसमय_put(&imx274->client->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक imx274_binning_goodness(काष्ठा stimx274 *imx274,
				   पूर्णांक w, पूर्णांक ask_w,
				   पूर्णांक h, पूर्णांक ask_h, u32 flags)
अणु
	काष्ठा device *dev = &imx274->client->dev;
	स्थिर पूर्णांक goodness = 100000;
	पूर्णांक val = 0;

	अगर (flags & V4L2_SEL_FLAG_GE) अणु
		अगर (w < ask_w)
			val -= goodness;
		अगर (h < ask_h)
			val -= goodness;
	पूर्ण

	अगर (flags & V4L2_SEL_FLAG_LE) अणु
		अगर (w > ask_w)
			val -= goodness;
		अगर (h > ask_h)
			val -= goodness;
	पूर्ण

	val -= असल(w - ask_w);
	val -= असल(h - ask_h);

	dev_dbg(dev, "%s: ask %dx%d, size %dx%d, goodness %d\n",
		__func__, ask_w, ask_h, w, h, val);

	वापस val;
पूर्ण

/**
 * __imx274_change_compose - Helper function to change binning and set both
 *	compose and क्रमmat.
 *
 * We have two entry poपूर्णांकs to change binning: set_fmt and
 * set_selection(COMPOSE). Both have to compute the new output size
 * and set it in both the compose rect and the frame क्रमmat size. We
 * also need to करो the same things after setting cropping to restore
 * 1:1 binning.
 *
 * This function contains the common code क्रम these three हालs, it
 * has many arguments in order to accommodate the needs of all of
 * them.
 *
 * Must be called with imx274->lock locked.
 *
 * @imx274: The device object
 * @cfg:    The pad config we are editing क्रम TRY requests
 * @which:  V4L2_SUBDEV_FORMAT_ACTIVE or V4L2_SUBDEV_FORMAT_TRY from the caller
 * @width:  Input-output parameter: set to the desired width beक्रमe
 *          the call, contains the chosen value after वापसing successfully
 * @height: Input-output parameter क्रम height (see @width)
 * @flags:  Selection flags from काष्ठा v4l2_subdev_selection, or 0 अगर not
 *          available (when called from set_fmt)
 */
अटल पूर्णांक __imx274_change_compose(काष्ठा stimx274 *imx274,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   u32 which,
				   u32 *width,
				   u32 *height,
				   u32 flags)
अणु
	काष्ठा device *dev = &imx274->client->dev;
	स्थिर काष्ठा v4l2_rect *cur_crop;
	काष्ठा v4l2_mbus_framefmt *tgt_fmt;
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा imx274_mode *best_mode = &imx274_modes[0];
	पूर्णांक best_goodness = पूर्णांक_न्यून;

	अगर (which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cur_crop = &cfg->try_crop;
		tgt_fmt = &cfg->try_fmt;
	पूर्ण अन्यथा अणु
		cur_crop = &imx274->crop;
		tgt_fmt = &imx274->क्रमmat;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(imx274_modes); i++) अणु
		u8 wratio = imx274_modes[i].wbin_ratio;
		u8 hratio = imx274_modes[i].hbin_ratio;

		पूर्णांक goodness = imx274_binning_goodness(
			imx274,
			cur_crop->width / wratio, *width,
			cur_crop->height / hratio, *height,
			flags);

		अगर (goodness >= best_goodness) अणु
			best_goodness = goodness;
			best_mode = &imx274_modes[i];
		पूर्ण
	पूर्ण

	*width = cur_crop->width / best_mode->wbin_ratio;
	*height = cur_crop->height / best_mode->hbin_ratio;

	अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE)
		imx274->mode = best_mode;

	dev_dbg(dev, "%s: selected %ux%u binning\n",
		__func__, best_mode->wbin_ratio, best_mode->hbin_ratio);

	tgt_fmt->width = *width;
	tgt_fmt->height = *height;
	tgt_fmt->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

/**
 * imx274_get_fmt - Get the pad क्रमmat
 * @sd: Poपूर्णांकer to V4L2 Sub device काष्ठाure
 * @cfg: Poपूर्णांकer to sub device pad inक्रमmation काष्ठाure
 * @fmt: Poपूर्णांकer to pad level media bus क्रमmat
 *
 * This function is used to get the pad क्रमmat inक्रमmation.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा stimx274 *imx274 = to_imx274(sd);

	mutex_lock(&imx274->lock);
	fmt->क्रमmat = imx274->क्रमmat;
	mutex_unlock(&imx274->lock);
	वापस 0;
पूर्ण

/**
 * imx274_set_fmt - This is used to set the pad क्रमmat
 * @sd: Poपूर्णांकer to V4L2 Sub device काष्ठाure
 * @cfg: Poपूर्णांकer to sub device pad inक्रमmation काष्ठाure
 * @क्रमmat: Poपूर्णांकer to pad level media bus क्रमmat
 *
 * This function is used to set the pad क्रमmat.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा stimx274 *imx274 = to_imx274(sd);
	पूर्णांक err = 0;

	mutex_lock(&imx274->lock);

	err = __imx274_change_compose(imx274, cfg, क्रमmat->which,
				      &fmt->width, &fmt->height, 0);

	अगर (err)
		जाओ out;

	/*
	 * __imx274_change_compose alपढ़ोy set width and height in the
	 * applicable क्रमmat, but we need to keep all other क्रमmat
	 * values, so करो a full copy here
	 */
	fmt->field = V4L2_FIELD_NONE;
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		cfg->try_fmt = *fmt;
	अन्यथा
		imx274->क्रमmat = *fmt;

out:
	mutex_unlock(&imx274->lock);

	वापस err;
पूर्ण

अटल पूर्णांक imx274_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा stimx274 *imx274 = to_imx274(sd);
	स्थिर काष्ठा v4l2_rect *src_crop;
	स्थिर काष्ठा v4l2_mbus_framefmt *src_fmt;
	पूर्णांक ret = 0;

	अगर (sel->pad != 0)
		वापस -EINVAL;

	अगर (sel->target == V4L2_SEL_TGT_CROP_BOUNDS) अणु
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = IMX274_MAX_WIDTH;
		sel->r.height = IMX274_MAX_HEIGHT;
		वापस 0;
	पूर्ण

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		src_crop = &cfg->try_crop;
		src_fmt = &cfg->try_fmt;
	पूर्ण अन्यथा अणु
		src_crop = &imx274->crop;
		src_fmt = &imx274->क्रमmat;
	पूर्ण

	mutex_lock(&imx274->lock);

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		sel->r = *src_crop;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		sel->r.top = 0;
		sel->r.left = 0;
		sel->r.width = src_crop->width;
		sel->r.height = src_crop->height;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
		sel->r.top = 0;
		sel->r.left = 0;
		sel->r.width = src_fmt->width;
		sel->r.height = src_fmt->height;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&imx274->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक imx274_set_selection_crop(काष्ठा stimx274 *imx274,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा v4l2_rect *tgt_crop;
	काष्ठा v4l2_rect new_crop;
	bool size_changed;

	/*
	 * h_step could be 12 or 24 depending on the binning. But we
	 * won't know the binning until we choose the mode later in
	 * __imx274_change_compose(). Thus let's be safe and use the
	 * most conservative value in all हालs.
	 */
	स्थिर u32 h_step = 24;

	new_crop.width = min_t(u32,
			       IMX274_ROUND(sel->r.width, h_step, sel->flags),
			       IMX274_MAX_WIDTH);

	/* Constraपूर्णांक: HTRIMMING_END - HTRIMMING_START >= 144 */
	अगर (new_crop.width < 144)
		new_crop.width = 144;

	new_crop.left = min_t(u32,
			      IMX274_ROUND(sel->r.left, h_step, 0),
			      IMX274_MAX_WIDTH - new_crop.width);

	new_crop.height = min_t(u32,
				IMX274_ROUND(sel->r.height, 2, sel->flags),
				IMX274_MAX_HEIGHT);

	new_crop.top = min_t(u32, IMX274_ROUND(sel->r.top, 2, 0),
			     IMX274_MAX_HEIGHT - new_crop.height);

	sel->r = new_crop;

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY)
		tgt_crop = &cfg->try_crop;
	अन्यथा
		tgt_crop = &imx274->crop;

	mutex_lock(&imx274->lock);

	size_changed = (new_crop.width != tgt_crop->width ||
			new_crop.height != tgt_crop->height);

	/* __imx274_change_compose needs the new size in *tgt_crop */
	*tgt_crop = new_crop;

	/* अगर crop size changed then reset the output image size */
	अगर (size_changed)
		__imx274_change_compose(imx274, cfg, sel->which,
					&new_crop.width, &new_crop.height,
					sel->flags);

	mutex_unlock(&imx274->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक imx274_set_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा stimx274 *imx274 = to_imx274(sd);

	अगर (sel->pad != 0)
		वापस -EINVAL;

	अगर (sel->target == V4L2_SEL_TGT_CROP)
		वापस imx274_set_selection_crop(imx274, cfg, sel);

	अगर (sel->target == V4L2_SEL_TGT_COMPOSE) अणु
		पूर्णांक err;

		mutex_lock(&imx274->lock);
		err =  __imx274_change_compose(imx274, cfg, sel->which,
					       &sel->r.width, &sel->r.height,
					       sel->flags);
		mutex_unlock(&imx274->lock);

		/*
		 * __imx274_change_compose alपढ़ोy set width and
		 * height in set->r, we still need to set top-left
		 */
		अगर (!err) अणु
			sel->r.top = 0;
			sel->r.left = 0;
		पूर्ण

		वापस err;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक imx274_apply_trimming(काष्ठा stimx274 *imx274)
अणु
	u32 h_start;
	u32 h_end;
	u32 hmax;
	u32 v_cut;
	s32 v_pos;
	u32 ग_लिखो_v_size;
	u32 y_out_size;
	पूर्णांक err;

	h_start = imx274->crop.left + 12;
	h_end = h_start + imx274->crop.width;

	/* Use the minimum allowed value of HMAX */
	/* Note: except in mode 1, (width / 16 + 23) is always < hmax_min */
	/* Note: 260 is the minimum HMAX in all implemented modes */
	hmax = max_t(u32, 260, (imx274->crop.width) / 16 + 23);

	/* invert v_pos अगर VFLIP */
	v_pos = imx274->ctrls.vflip->cur.val ?
		(-imx274->crop.top / 2) : (imx274->crop.top / 2);
	v_cut = (IMX274_MAX_HEIGHT - imx274->crop.height) / 2;
	ग_लिखो_v_size = imx274->crop.height + 22;
	y_out_size   = imx274->crop.height;

	err = imx274_ग_लिखो_mbreg(imx274, IMX274_HMAX_REG_LSB, hmax, 2);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_HTRIM_EN_REG, 1, 1);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_HTRIM_START_REG_LSB,
					 h_start, 2);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_HTRIM_END_REG_LSB,
					 h_end, 2);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_VWIDCUTEN_REG, 1, 1);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_VWIDCUT_REG_LSB,
					 v_cut, 2);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_VWINPOS_REG_LSB,
					 v_pos, 2);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_WRITE_VSIZE_REG_LSB,
					 ग_लिखो_v_size, 2);
	अगर (!err)
		err = imx274_ग_लिखो_mbreg(imx274, IMX274_Y_OUT_SIZE_REG_LSB,
					 y_out_size, 2);

	वापस err;
पूर्ण

/**
 * imx274_g_frame_पूर्णांकerval - Get the frame पूर्णांकerval
 * @sd: Poपूर्णांकer to V4L2 Sub device काष्ठाure
 * @fi: Poपूर्णांकer to V4l2 Sub device frame पूर्णांकerval काष्ठाure
 *
 * This function is used to get the frame पूर्णांकerval.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा stimx274 *imx274 = to_imx274(sd);

	fi->पूर्णांकerval = imx274->frame_पूर्णांकerval;
	dev_dbg(&imx274->client->dev, "%s frame rate = %d / %d\n",
		__func__, imx274->frame_पूर्णांकerval.numerator,
		imx274->frame_पूर्णांकerval.denominator);

	वापस 0;
पूर्ण

/**
 * imx274_s_frame_पूर्णांकerval - Set the frame पूर्णांकerval
 * @sd: Poपूर्णांकer to V4L2 Sub device काष्ठाure
 * @fi: Poपूर्णांकer to V4l2 Sub device frame पूर्णांकerval काष्ठाure
 *
 * This function is used to set the frame पूर्णांकervavl.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा stimx274 *imx274 = to_imx274(sd);
	काष्ठा v4l2_ctrl *ctrl = imx274->ctrls.exposure;
	पूर्णांक min, max, def;
	पूर्णांक ret;

	mutex_lock(&imx274->lock);
	ret = imx274_set_frame_पूर्णांकerval(imx274, fi->पूर्णांकerval);

	अगर (!ret) अणु
		fi->पूर्णांकerval = imx274->frame_पूर्णांकerval;

		/*
		 * exposure समय range is decided by frame पूर्णांकerval
		 * need to update it after frame पूर्णांकerval changes
		 */
		min = IMX274_MIN_EXPOSURE_TIME;
		max = fi->पूर्णांकerval.numerator * 1000000
			/ fi->पूर्णांकerval.denominator;
		def = max;
		ret = __v4l2_ctrl_modअगरy_range(ctrl, min, max, 1, def);
		अगर (ret) अणु
			dev_err(&imx274->client->dev,
				"Exposure ctrl range update failed\n");
			जाओ unlock;
		पूर्ण

		/* update exposure समय accordingly */
		imx274_set_exposure(imx274, ctrl->val);

		dev_dbg(&imx274->client->dev, "set frame interval to %uus\n",
			fi->पूर्णांकerval.numerator * 1000000
			/ fi->पूर्णांकerval.denominator);
	पूर्ण

unlock:
	mutex_unlock(&imx274->lock);

	वापस ret;
पूर्ण

/**
 * imx274_load_शेष - load शेष control values
 * @priv: Poपूर्णांकer to device काष्ठाure
 *
 * Return: 0 on success, errors otherwise
 */
अटल व्योम imx274_load_शेष(काष्ठा stimx274 *priv)
अणु
	/* load शेष control values */
	priv->frame_पूर्णांकerval.numerator = 1;
	priv->frame_पूर्णांकerval.denominator = IMX274_DEF_FRAME_RATE;
	priv->ctrls.exposure->val = 1000000 / IMX274_DEF_FRAME_RATE;
	priv->ctrls.gain->val = IMX274_DEF_GAIN;
	priv->ctrls.vflip->val = 0;
	priv->ctrls.test_pattern->val = TEST_PATTERN_DISABLED;
पूर्ण

/**
 * imx274_s_stream - It is used to start/stop the streaming.
 * @sd: V4L2 Sub device
 * @on: Flag (True / False)
 *
 * This function controls the start or stop of streaming क्रम the
 * imx274 sensor.
 *
 * Return: 0 on success, errors otherwise
 */
अटल पूर्णांक imx274_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा stimx274 *imx274 = to_imx274(sd);
	पूर्णांक ret = 0;

	dev_dbg(&imx274->client->dev, "%s : %s, mode index = %td\n", __func__,
		on ? "Stream Start" : "Stream Stop",
		imx274->mode - &imx274_modes[0]);

	mutex_lock(&imx274->lock);

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&imx274->client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&imx274->client->dev);
			mutex_unlock(&imx274->lock);
			वापस ret;
		पूर्ण

		/* load mode रेजिस्टरs */
		ret = imx274_mode_regs(imx274);
		अगर (ret)
			जाओ fail;

		ret = imx274_apply_trimming(imx274);
		अगर (ret)
			जाओ fail;

		/*
		 * update frame rate & expsoure. अगर the last mode is dअगरferent,
		 * HMAX could be changed. As the result, frame rate & exposure
		 * are changed.
		 * gain is not affected.
		 */
		ret = imx274_set_frame_पूर्णांकerval(imx274,
						imx274->frame_पूर्णांकerval);
		अगर (ret)
			जाओ fail;

		/* start stream */
		ret = imx274_start_stream(imx274);
		अगर (ret)
			जाओ fail;
	पूर्ण अन्यथा अणु
		/* stop stream */
		ret = imx274_ग_लिखो_table(imx274, imx274_stop);
		अगर (ret)
			जाओ fail;

		pm_runसमय_put(&imx274->client->dev);
	पूर्ण

	mutex_unlock(&imx274->lock);
	dev_dbg(&imx274->client->dev, "%s : Done\n", __func__);
	वापस 0;

fail:
	pm_runसमय_put(&imx274->client->dev);
	mutex_unlock(&imx274->lock);
	dev_err(&imx274->client->dev, "s_stream failed\n");
	वापस ret;
पूर्ण

/*
 * imx274_get_frame_length - Function क्रम obtaining current frame length
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @val: Poपूर्णांकer to obaपूर्णांकed value
 *
 * frame_length = vmax x (svr + 1), in unit of hmax.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_get_frame_length(काष्ठा stimx274 *priv, u32 *val)
अणु
	पूर्णांक err;
	u32 svr;
	u32 vmax;

	err = imx274_पढ़ो_mbreg(priv, IMX274_SVR_REG_LSB, &svr, 2);
	अगर (err)
		जाओ fail;

	err = imx274_पढ़ो_mbreg(priv, IMX274_VMAX_REG_3, &vmax, 3);
	अगर (err)
		जाओ fail;

	*val = vmax * (svr + 1);

	वापस 0;

fail:
	dev_err(&priv->client->dev, "%s error = %d\n", __func__, err);
	वापस err;
पूर्ण

अटल पूर्णांक imx274_clamp_coarse_समय(काष्ठा stimx274 *priv, u32 *val,
				    u32 *frame_length)
अणु
	पूर्णांक err;

	err = imx274_get_frame_length(priv, frame_length);
	अगर (err)
		वापस err;

	अगर (*frame_length < priv->mode->min_frame_len)
		*frame_length =  priv->mode->min_frame_len;

	*val = *frame_length - *val; /* convert to raw shr */
	अगर (*val > *frame_length - IMX274_SHR_LIMIT_CONST)
		*val = *frame_length - IMX274_SHR_LIMIT_CONST;
	अन्यथा अगर (*val < priv->mode->min_SHR)
		*val = priv->mode->min_SHR;

	वापस 0;
पूर्ण

/*
 * imx274_set_digital gain - Function called when setting digital gain
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @dgain: Value of digital gain.
 *
 * Digital gain has only 4 steps: 1x, 2x, 4x, and 8x
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_digital_gain(काष्ठा stimx274 *priv, u32 dgain)
अणु
	u8 reg_val;

	reg_val = ffs(dgain);

	अगर (reg_val)
		reg_val--;

	reg_val = clamp(reg_val, (u8)0, (u8)3);

	वापस imx274_ग_लिखो_reg(priv, IMX274_DIGITAL_GAIN_REG,
				reg_val & IMX274_MASK_LSB_4_BITS);
पूर्ण

/*
 * imx274_set_gain - Function called when setting gain
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @val: Value of gain. the real value = val << IMX274_GAIN_SHIFT;
 * @ctrl: v4l2 control poपूर्णांकer
 *
 * Set the gain based on input value.
 * The caller should hold the mutex lock imx274->lock अगर necessary
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_gain(काष्ठा stimx274 *priv, काष्ठा v4l2_ctrl *ctrl)
अणु
	पूर्णांक err;
	u32 gain, analog_gain, digital_gain, gain_reg;

	gain = (u32)(ctrl->val);

	dev_dbg(&priv->client->dev,
		"%s : input gain = %d.%d\n", __func__,
		gain >> IMX274_GAIN_SHIFT,
		((gain & IMX274_GAIN_SHIFT_MASK) * 100) >> IMX274_GAIN_SHIFT);

	अगर (gain > IMX274_MAX_DIGITAL_GAIN * IMX274_MAX_ANALOG_GAIN)
		gain = IMX274_MAX_DIGITAL_GAIN * IMX274_MAX_ANALOG_GAIN;
	अन्यथा अगर (gain < IMX274_MIN_GAIN)
		gain = IMX274_MIN_GAIN;

	अगर (gain <= IMX274_MAX_ANALOG_GAIN)
		digital_gain = 1;
	अन्यथा अगर (gain <= IMX274_MAX_ANALOG_GAIN * 2)
		digital_gain = 2;
	अन्यथा अगर (gain <= IMX274_MAX_ANALOG_GAIN * 4)
		digital_gain = 4;
	अन्यथा
		digital_gain = IMX274_MAX_DIGITAL_GAIN;

	analog_gain = gain / digital_gain;

	dev_dbg(&priv->client->dev,
		"%s : digital gain = %d, analog gain = %d.%d\n",
		__func__, digital_gain, analog_gain >> IMX274_GAIN_SHIFT,
		((analog_gain & IMX274_GAIN_SHIFT_MASK) * 100)
		>> IMX274_GAIN_SHIFT);

	err = imx274_set_digital_gain(priv, digital_gain);
	अगर (err)
		जाओ fail;

	/* convert to रेजिस्टर value, refer to imx274 datasheet */
	gain_reg = (u32)IMX274_GAIN_CONST -
		(IMX274_GAIN_CONST << IMX274_GAIN_SHIFT) / analog_gain;
	अगर (gain_reg > IMX274_GAIN_REG_MAX)
		gain_reg = IMX274_GAIN_REG_MAX;

	err = imx274_ग_लिखो_mbreg(priv, IMX274_ANALOG_GAIN_ADDR_LSB, gain_reg,
				 2);
	अगर (err)
		जाओ fail;

	अगर (IMX274_GAIN_CONST - gain_reg == 0) अणु
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	/* convert रेजिस्टर value back to gain value */
	ctrl->val = (IMX274_GAIN_CONST << IMX274_GAIN_SHIFT)
			/ (IMX274_GAIN_CONST - gain_reg) * digital_gain;

	dev_dbg(&priv->client->dev,
		"%s : GAIN control success, gain_reg = %d, new gain = %d\n",
		__func__, gain_reg, ctrl->val);

	वापस 0;

fail:
	dev_err(&priv->client->dev, "%s error = %d\n", __func__, err);
	वापस err;
पूर्ण

/*
 * imx274_set_coarse_समय - Function called when setting SHR value
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @val: Value क्रम exposure समय in number of line_length, or [HMAX]
 *
 * Set SHR value based on input value.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_coarse_समय(काष्ठा stimx274 *priv, u32 *val)
अणु
	पूर्णांक err;
	u32 coarse_समय, frame_length;

	coarse_समय = *val;

	/* convert exposure_समय to appropriate SHR value */
	err = imx274_clamp_coarse_समय(priv, &coarse_समय, &frame_length);
	अगर (err)
		जाओ fail;

	err = imx274_ग_लिखो_mbreg(priv, IMX274_SHR_REG_LSB, coarse_समय, 2);
	अगर (err)
		जाओ fail;

	*val = frame_length - coarse_समय;
	वापस 0;

fail:
	dev_err(&priv->client->dev, "%s error = %d\n", __func__, err);
	वापस err;
पूर्ण

/*
 * imx274_set_exposure - Function called when setting exposure समय
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @val: Variable क्रम exposure समय, in the unit of micro-second
 *
 * Set exposure समय based on input value.
 * The caller should hold the mutex lock imx274->lock अगर necessary
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_exposure(काष्ठा stimx274 *priv, पूर्णांक val)
अणु
	पूर्णांक err;
	u32 hmax;
	u32 coarse_समय; /* exposure समय in unit of line (HMAX)*/

	dev_dbg(&priv->client->dev,
		"%s : EXPOSURE control input = %d\n", __func__, val);

	/* step 1: convert input exposure_समय (val) पूर्णांकo number of 1[HMAX] */

	err = imx274_पढ़ो_mbreg(priv, IMX274_HMAX_REG_LSB, &hmax, 2);
	अगर (err)
		जाओ fail;

	अगर (hmax == 0) अणु
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	coarse_समय = (IMX274_PIXCLK_CONST1 / IMX274_PIXCLK_CONST2 * val
			- priv->mode->nocpiop) / hmax;

	/* step 2: convert exposure_समय पूर्णांकo SHR value */

	/* set SHR */
	err = imx274_set_coarse_समय(priv, &coarse_समय);
	अगर (err)
		जाओ fail;

	priv->ctrls.exposure->val =
			(coarse_समय * hmax + priv->mode->nocpiop)
			/ (IMX274_PIXCLK_CONST1 / IMX274_PIXCLK_CONST2);

	dev_dbg(&priv->client->dev,
		"%s : EXPOSURE control success\n", __func__);
	वापस 0;

fail:
	dev_err(&priv->client->dev, "%s error = %d\n", __func__, err);

	वापस err;
पूर्ण

/*
 * imx274_set_vflip - Function called when setting vertical flip
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @val: Value क्रम vflip setting
 *
 * Set vertical flip based on input value.
 * val = 0: normal, no vertical flip
 * val = 1: vertical flip enabled
 * The caller should hold the mutex lock imx274->lock अगर necessary
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_vflip(काष्ठा stimx274 *priv, पूर्णांक val)
अणु
	पूर्णांक err;

	err = imx274_ग_लिखो_reg(priv, IMX274_VFLIP_REG, val);
	अगर (err) अणु
		dev_err(&priv->client->dev, "VFLIP control error\n");
		वापस err;
	पूर्ण

	dev_dbg(&priv->client->dev,
		"%s : VFLIP control success\n", __func__);

	वापस 0;
पूर्ण

/*
 * imx274_set_test_pattern - Function called when setting test pattern
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @val: Variable क्रम test pattern
 *
 * Set to dअगरferent test patterns based on input value.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_test_pattern(काष्ठा stimx274 *priv, पूर्णांक val)
अणु
	पूर्णांक err = 0;

	अगर (val == TEST_PATTERN_DISABLED) अणु
		err = imx274_ग_लिखो_table(priv, imx274_tp_disabled);
	पूर्ण अन्यथा अगर (val <= TEST_PATTERN_V_COLOR_BARS) अणु
		err = imx274_ग_लिखो_reg(priv, IMX274_TEST_PATTERN_REG, val - 1);
		अगर (!err)
			err = imx274_ग_लिखो_table(priv, imx274_tp_regs);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	अगर (!err)
		dev_dbg(&priv->client->dev,
			"%s : TEST PATTERN control success\n", __func__);
	अन्यथा
		dev_err(&priv->client->dev, "%s error = %d\n", __func__, err);

	वापस err;
पूर्ण

/*
 * imx274_set_frame_length - Function called when setting frame length
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @val: Variable क्रम frame length (= VMAX, i.e. vertical drive period length)
 *
 * Set frame length based on input value.
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_frame_length(काष्ठा stimx274 *priv, u32 val)
अणु
	पूर्णांक err;
	u32 frame_length;

	dev_dbg(&priv->client->dev, "%s : input length = %d\n",
		__func__, val);

	frame_length = (u32)val;

	err = imx274_ग_लिखो_mbreg(priv, IMX274_VMAX_REG_3, frame_length, 3);
	अगर (err)
		जाओ fail;

	वापस 0;

fail:
	dev_err(&priv->client->dev, "%s error = %d\n", __func__, err);
	वापस err;
पूर्ण

/*
 * imx274_set_frame_पूर्णांकerval - Function called when setting frame पूर्णांकerval
 * @priv: Poपूर्णांकer to device काष्ठाure
 * @frame_पूर्णांकerval: Variable क्रम frame पूर्णांकerval
 *
 * Change frame पूर्णांकerval by updating VMAX value
 * The caller should hold the mutex lock imx274->lock अगर necessary
 *
 * Return: 0 on success
 */
अटल पूर्णांक imx274_set_frame_पूर्णांकerval(काष्ठा stimx274 *priv,
				     काष्ठा v4l2_fract frame_पूर्णांकerval)
अणु
	पूर्णांक err;
	u32 frame_length, req_frame_rate;
	u32 svr;
	u32 hmax;

	dev_dbg(&priv->client->dev, "%s: input frame interval = %d / %d",
		__func__, frame_पूर्णांकerval.numerator,
		frame_पूर्णांकerval.denominator);

	अगर (frame_पूर्णांकerval.numerator == 0 || frame_पूर्णांकerval.denominator == 0) अणु
		frame_पूर्णांकerval.denominator = IMX274_DEF_FRAME_RATE;
		frame_पूर्णांकerval.numerator = 1;
	पूर्ण

	req_frame_rate = (u32)(frame_पूर्णांकerval.denominator
				/ frame_पूर्णांकerval.numerator);

	/* boundary check */
	अगर (req_frame_rate > priv->mode->max_fps) अणु
		frame_पूर्णांकerval.numerator = 1;
		frame_पूर्णांकerval.denominator = priv->mode->max_fps;
	पूर्ण अन्यथा अगर (req_frame_rate < IMX274_MIN_FRAME_RATE) अणु
		frame_पूर्णांकerval.numerator = 1;
		frame_पूर्णांकerval.denominator = IMX274_MIN_FRAME_RATE;
	पूर्ण

	/*
	 * VMAX = 1/frame_rate x 72M / (SVR+1) / HMAX
	 * frame_length (i.e. VMAX) = (frame_पूर्णांकerval) x 72M /(SVR+1) / HMAX
	 */

	err = imx274_पढ़ो_mbreg(priv, IMX274_SVR_REG_LSB, &svr, 2);
	अगर (err)
		जाओ fail;

	dev_dbg(&priv->client->dev,
		"%s : register SVR = %d\n", __func__, svr);

	err = imx274_पढ़ो_mbreg(priv, IMX274_HMAX_REG_LSB, &hmax, 2);
	अगर (err)
		जाओ fail;

	dev_dbg(&priv->client->dev,
		"%s : register HMAX = %d\n", __func__, hmax);

	अगर (hmax == 0 || frame_पूर्णांकerval.denominator == 0) अणु
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	frame_length = IMX274_PIXCLK_CONST1 / (svr + 1) / hmax
					* frame_पूर्णांकerval.numerator
					/ frame_पूर्णांकerval.denominator;

	err = imx274_set_frame_length(priv, frame_length);
	अगर (err)
		जाओ fail;

	priv->frame_पूर्णांकerval = frame_पूर्णांकerval;
	वापस 0;

fail:
	dev_err(&priv->client->dev, "%s error = %d\n", __func__, err);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx274_pad_ops = अणु
	.get_fmt = imx274_get_fmt,
	.set_fmt = imx274_set_fmt,
	.get_selection = imx274_get_selection,
	.set_selection = imx274_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops imx274_video_ops = अणु
	.g_frame_पूर्णांकerval = imx274_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = imx274_s_frame_पूर्णांकerval,
	.s_stream = imx274_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx274_subdev_ops = अणु
	.pad = &imx274_pad_ops,
	.video = &imx274_video_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops imx274_ctrl_ops = अणु
	.s_ctrl	= imx274_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx274_of_id_table[] = अणु
	अणु .compatible = "sony,imx274" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx274_of_id_table);

अटल स्थिर काष्ठा i2c_device_id imx274_id[] = अणु
	अणु "IMX274", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, imx274_id);

अटल पूर्णांक imx274_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा stimx274 *imx274;
	पूर्णांक ret;

	/* initialize imx274 */
	imx274 = devm_kzalloc(&client->dev, माप(*imx274), GFP_KERNEL);
	अगर (!imx274)
		वापस -ENOMEM;

	mutex_init(&imx274->lock);

	imx274->inck = devm_clk_get_optional(&client->dev, "inck");
	अगर (IS_ERR(imx274->inck))
		वापस PTR_ERR(imx274->inck);

	ret = imx274_regulators_get(&client->dev, imx274);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Failed to get power regulators, err: %d\n", ret);
		वापस ret;
	पूर्ण

	/* initialize क्रमmat */
	imx274->mode = &imx274_modes[0];
	imx274->crop.width = IMX274_MAX_WIDTH;
	imx274->crop.height = IMX274_MAX_HEIGHT;
	imx274->क्रमmat.width = imx274->crop.width / imx274->mode->wbin_ratio;
	imx274->क्रमmat.height = imx274->crop.height / imx274->mode->hbin_ratio;
	imx274->क्रमmat.field = V4L2_FIELD_NONE;
	imx274->क्रमmat.code = MEDIA_BUS_FMT_SRGGB10_1X10;
	imx274->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;
	imx274->frame_पूर्णांकerval.numerator = 1;
	imx274->frame_पूर्णांकerval.denominator = IMX274_DEF_FRAME_RATE;

	/* initialize regmap */
	imx274->regmap = devm_regmap_init_i2c(client, &imx274_regmap_config);
	अगर (IS_ERR(imx274->regmap)) अणु
		dev_err(&client->dev,
			"regmap init failed: %ld\n", PTR_ERR(imx274->regmap));
		ret = -ENODEV;
		जाओ err_regmap;
	पूर्ण

	/* initialize subdevice */
	imx274->client = client;
	sd = &imx274->sd;
	v4l2_i2c_subdev_init(sd, client, &imx274_subdev_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;

	/* initialize subdev media pad */
	imx274->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &imx274->pad);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"%s : media entity init Failed %d\n", __func__, ret);
		जाओ err_regmap;
	पूर्ण

	/* initialize sensor reset gpio */
	imx274->reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						     GPIOD_OUT_HIGH);
	अगर (IS_ERR(imx274->reset_gpio)) अणु
		अगर (PTR_ERR(imx274->reset_gpio) != -EPROBE_DEFER)
			dev_err(&client->dev, "Reset GPIO not setup in DT");
		ret = PTR_ERR(imx274->reset_gpio);
		जाओ err_me;
	पूर्ण

	/* घातer on the sensor */
	ret = imx274_घातer_on(&client->dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"%s : imx274 power on failed\n", __func__);
		जाओ err_me;
	पूर्ण

	/* initialize controls */
	ret = v4l2_ctrl_handler_init(&imx274->ctrls.handler, 4);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"%s : ctrl handler init Failed\n", __func__);
		जाओ err_घातer_off;
	पूर्ण

	imx274->ctrls.handler.lock = &imx274->lock;

	/* add new controls */
	imx274->ctrls.test_pattern = v4l2_ctrl_new_std_menu_items(
		&imx274->ctrls.handler, &imx274_ctrl_ops,
		V4L2_CID_TEST_PATTERN,
		ARRAY_SIZE(tp_qmenu) - 1, 0, 0, tp_qmenu);

	imx274->ctrls.gain = v4l2_ctrl_new_std(
		&imx274->ctrls.handler,
		&imx274_ctrl_ops,
		V4L2_CID_GAIN, IMX274_MIN_GAIN,
		IMX274_MAX_DIGITAL_GAIN * IMX274_MAX_ANALOG_GAIN, 1,
		IMX274_DEF_GAIN);

	imx274->ctrls.exposure = v4l2_ctrl_new_std(
		&imx274->ctrls.handler,
		&imx274_ctrl_ops,
		V4L2_CID_EXPOSURE, IMX274_MIN_EXPOSURE_TIME,
		1000000 / IMX274_DEF_FRAME_RATE, 1,
		IMX274_MIN_EXPOSURE_TIME);

	imx274->ctrls.vflip = v4l2_ctrl_new_std(
		&imx274->ctrls.handler,
		&imx274_ctrl_ops,
		V4L2_CID_VFLIP, 0, 1, 1, 0);

	imx274->sd.ctrl_handler = &imx274->ctrls.handler;
	अगर (imx274->ctrls.handler.error) अणु
		ret = imx274->ctrls.handler.error;
		जाओ err_ctrls;
	पूर्ण

	/* load शेष control values */
	imx274_load_शेष(imx274);

	/* रेजिस्टर subdevice */
	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"%s : v4l2_async_register_subdev failed %d\n",
			__func__, ret);
		जाओ err_ctrls;
	पूर्ण

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	dev_info(&client->dev, "imx274 : imx274 probe success !\n");
	वापस 0;

err_ctrls:
	v4l2_ctrl_handler_मुक्त(&imx274->ctrls.handler);
err_घातer_off:
	imx274_घातer_off(&client->dev);
err_me:
	media_entity_cleanup(&sd->entity);
err_regmap:
	mutex_destroy(&imx274->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक imx274_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा stimx274 *imx274 = to_imx274(sd);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		imx274_घातer_off(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	v4l2_async_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&imx274->ctrls.handler);

	media_entity_cleanup(&sd->entity);
	mutex_destroy(&imx274->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx274_pm_ops = अणु
	SET_RUNTIME_PM_OPS(imx274_घातer_off, imx274_घातer_on, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver imx274_i2c_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.pm = &imx274_pm_ops,
		.of_match_table	= imx274_of_id_table,
	पूर्ण,
	.probe_new	= imx274_probe,
	.हटाओ		= imx274_हटाओ,
	.id_table	= imx274_id,
पूर्ण;

module_i2c_driver(imx274_i2c_driver);

MODULE_AUTHOR("Leon Luo <leonl@leopardimaging.com>");
MODULE_DESCRIPTION("IMX274 CMOS Image Sensor driver");
MODULE_LICENSE("GPL v2");
