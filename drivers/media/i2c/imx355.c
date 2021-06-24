<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>

#घोषणा IMX355_REG_MODE_SELECT		0x0100
#घोषणा IMX355_MODE_STANDBY		0x00
#घोषणा IMX355_MODE_STREAMING		0x01

/* Chip ID */
#घोषणा IMX355_REG_CHIP_ID		0x0016
#घोषणा IMX355_CHIP_ID			0x0355

/* V_TIMING पूर्णांकernal */
#घोषणा IMX355_REG_FLL			0x0340
#घोषणा IMX355_FLL_MAX			0xffff

/* Exposure control */
#घोषणा IMX355_REG_EXPOSURE		0x0202
#घोषणा IMX355_EXPOSURE_MIN		1
#घोषणा IMX355_EXPOSURE_STEP		1
#घोषणा IMX355_EXPOSURE_DEFAULT		0x0282

/* Analog gain control */
#घोषणा IMX355_REG_ANALOG_GAIN		0x0204
#घोषणा IMX355_ANA_GAIN_MIN		0
#घोषणा IMX355_ANA_GAIN_MAX		960
#घोषणा IMX355_ANA_GAIN_STEP		1
#घोषणा IMX355_ANA_GAIN_DEFAULT		0

/* Digital gain control */
#घोषणा IMX355_REG_DPGA_USE_GLOBAL_GAIN	0x3070
#घोषणा IMX355_REG_DIG_GAIN_GLOBAL	0x020e
#घोषणा IMX355_DGTL_GAIN_MIN		256
#घोषणा IMX355_DGTL_GAIN_MAX		4095
#घोषणा IMX355_DGTL_GAIN_STEP		1
#घोषणा IMX355_DGTL_GAIN_DEFAULT	256

/* Test Pattern Control */
#घोषणा IMX355_REG_TEST_PATTERN		0x0600
#घोषणा IMX355_TEST_PATTERN_DISABLED		0
#घोषणा IMX355_TEST_PATTERN_SOLID_COLOR		1
#घोषणा IMX355_TEST_PATTERN_COLOR_BARS		2
#घोषणा IMX355_TEST_PATTERN_GRAY_COLOR_BARS	3
#घोषणा IMX355_TEST_PATTERN_PN9			4

/* Flip Control */
#घोषणा IMX355_REG_ORIENTATION		0x0101

/* शेष link frequency and बाह्यal घड़ी */
#घोषणा IMX355_LINK_FREQ_DEFAULT	360000000
#घोषणा IMX355_EXT_CLK			19200000
#घोषणा IMX355_LINK_FREQ_INDEX		0

काष्ठा imx355_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा imx355_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा imx355_reg *regs;
पूर्ण;

/* Mode : resolution and related config&values */
काष्ठा imx355_mode अणु
	/* Frame width */
	u32 width;
	/* Frame height */
	u32 height;

	/* V-timing */
	u32 fll_def;
	u32 fll_min;

	/* H-timing */
	u32 llp;

	/* index of link frequency */
	u32 link_freq_index;

	/* Default रेजिस्टर values */
	काष्ठा imx355_reg_list reg_list;
पूर्ण;

काष्ठा imx355_hwcfg अणु
	u32 ext_clk;			/* sensor बाह्यal clk */
	s64 *link_freqs;		/* CSI-2 link frequencies */
	अचिन्हित पूर्णांक nr_of_link_freqs;
पूर्ण;

काष्ठा imx355 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	/* V4L2 Controls */
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl *hblank;
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *hflip;

	/* Current mode */
	स्थिर काष्ठा imx355_mode *cur_mode;

	काष्ठा imx355_hwcfg *hwcfg;
	s64 link_def_freq;	/* CSI-2 link शेष frequency */

	/*
	 * Mutex क्रम serialized access:
	 * Protect sensor set pad क्रमmat and start/stop streaming safely.
	 * Protect access to sensor v4l2 controls.
	 */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;
पूर्ण;

अटल स्थिर काष्ठा imx355_reg imx355_global_regs[] = अणु
	अणु 0x0136, 0x13 पूर्ण,
	अणु 0x0137, 0x33 पूर्ण,
	अणु 0x304e, 0x03 पूर्ण,
	अणु 0x4348, 0x16 पूर्ण,
	अणु 0x4350, 0x19 पूर्ण,
	अणु 0x4408, 0x0a पूर्ण,
	अणु 0x440c, 0x0b पूर्ण,
	अणु 0x4411, 0x5f पूर्ण,
	अणु 0x4412, 0x2c पूर्ण,
	अणु 0x4623, 0x00 पूर्ण,
	अणु 0x462c, 0x0f पूर्ण,
	अणु 0x462d, 0x00 पूर्ण,
	अणु 0x462e, 0x00 पूर्ण,
	अणु 0x4684, 0x54 पूर्ण,
	अणु 0x480a, 0x07 पूर्ण,
	अणु 0x4908, 0x07 पूर्ण,
	अणु 0x4909, 0x07 पूर्ण,
	अणु 0x490d, 0x0a पूर्ण,
	अणु 0x491e, 0x0f पूर्ण,
	अणु 0x4921, 0x06 पूर्ण,
	अणु 0x4923, 0x28 पूर्ण,
	अणु 0x4924, 0x28 पूर्ण,
	अणु 0x4925, 0x29 पूर्ण,
	अणु 0x4926, 0x29 पूर्ण,
	अणु 0x4927, 0x1f पूर्ण,
	अणु 0x4928, 0x20 पूर्ण,
	अणु 0x4929, 0x20 पूर्ण,
	अणु 0x492a, 0x20 पूर्ण,
	अणु 0x492c, 0x05 पूर्ण,
	अणु 0x492d, 0x06 पूर्ण,
	अणु 0x492e, 0x06 पूर्ण,
	अणु 0x492f, 0x06 पूर्ण,
	अणु 0x4930, 0x03 पूर्ण,
	अणु 0x4931, 0x04 पूर्ण,
	अणु 0x4932, 0x04 पूर्ण,
	अणु 0x4933, 0x05 पूर्ण,
	अणु 0x595e, 0x01 पूर्ण,
	अणु 0x5963, 0x01 पूर्ण,
	अणु 0x3030, 0x01 पूर्ण,
	अणु 0x3031, 0x01 पूर्ण,
	अणु 0x3045, 0x01 पूर्ण,
	अणु 0x4010, 0x00 पूर्ण,
	अणु 0x4011, 0x00 पूर्ण,
	अणु 0x4012, 0x00 पूर्ण,
	अणु 0x4013, 0x01 पूर्ण,
	अणु 0x68a8, 0xfe पूर्ण,
	अणु 0x68a9, 0xff पूर्ण,
	अणु 0x6888, 0x00 पूर्ण,
	अणु 0x6889, 0x00 पूर्ण,
	अणु 0x68b0, 0x00 पूर्ण,
	अणु 0x3058, 0x00 पूर्ण,
	अणु 0x305a, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg_list imx355_global_setting = अणु
	.num_of_regs = ARRAY_SIZE(imx355_global_regs),
	.regs = imx355_global_regs,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_3268x2448_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x0a पूर्ण,
	अणु 0x0341, 0x37 पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x08 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x08 पूर्ण,
	अणु 0x0348, 0x0c पूर्ण,
	अणु 0x0349, 0xcb पूर्ण,
	अणु 0x034a, 0x09 पूर्ण,
	अणु 0x034b, 0x97 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x0c पूर्ण,
	अणु 0x034d, 0xc4 पूर्ण,
	अणु 0x034e, 0x09 पूर्ण,
	अणु 0x034f, 0x90 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_3264x2448_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x0a पूर्ण,
	अणु 0x0341, 0x37 पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x08 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x08 पूर्ण,
	अणु 0x0348, 0x0c पूर्ण,
	अणु 0x0349, 0xc7 पूर्ण,
	अणु 0x034a, 0x09 पूर्ण,
	अणु 0x034b, 0x97 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x0c पूर्ण,
	अणु 0x034d, 0xc0 पूर्ण,
	अणु 0x034e, 0x09 पूर्ण,
	अणु 0x034f, 0x90 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_3280x2464_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x0a पूर्ण,
	अणु 0x0341, 0x37 पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x00 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x0c पूर्ण,
	अणु 0x0349, 0xcf पूर्ण,
	अणु 0x034a, 0x09 पूर्ण,
	अणु 0x034b, 0x9f पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x0c पूर्ण,
	अणु 0x034d, 0xd0 पूर्ण,
	अणु 0x034e, 0x09 पूर्ण,
	अणु 0x034f, 0xa0 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1940x1096_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x02 पूर्ण,
	अणु 0x0345, 0xa0 पूर्ण,
	अणु 0x0346, 0x02 पूर्ण,
	अणु 0x0347, 0xac पूर्ण,
	अणु 0x0348, 0x0a पूर्ण,
	अणु 0x0349, 0x33 पूर्ण,
	अणु 0x034a, 0x06 पूर्ण,
	अणु 0x034b, 0xf3 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x07 पूर्ण,
	अणु 0x034d, 0x94 पूर्ण,
	अणु 0x034e, 0x04 पूर्ण,
	अणु 0x034f, 0x48 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1936x1096_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x02 पूर्ण,
	अणु 0x0345, 0xa0 पूर्ण,
	अणु 0x0346, 0x02 पूर्ण,
	अणु 0x0347, 0xac पूर्ण,
	अणु 0x0348, 0x0a पूर्ण,
	अणु 0x0349, 0x2f पूर्ण,
	अणु 0x034a, 0x06 पूर्ण,
	अणु 0x034b, 0xf3 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x07 पूर्ण,
	अणु 0x034d, 0x90 पूर्ण,
	अणु 0x034e, 0x04 पूर्ण,
	अणु 0x034f, 0x48 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1924x1080_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x02 पूर्ण,
	अणु 0x0345, 0xa8 पूर्ण,
	अणु 0x0346, 0x02 पूर्ण,
	अणु 0x0347, 0xb4 पूर्ण,
	अणु 0x0348, 0x0a पूर्ण,
	अणु 0x0349, 0x2b पूर्ण,
	अणु 0x034a, 0x06 पूर्ण,
	अणु 0x034b, 0xeb पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x07 पूर्ण,
	अणु 0x034d, 0x84 पूर्ण,
	अणु 0x034e, 0x04 पूर्ण,
	अणु 0x034f, 0x38 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1920x1080_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x02 पूर्ण,
	अणु 0x0345, 0xa8 पूर्ण,
	अणु 0x0346, 0x02 पूर्ण,
	अणु 0x0347, 0xb4 पूर्ण,
	अणु 0x0348, 0x0a पूर्ण,
	अणु 0x0349, 0x27 पूर्ण,
	अणु 0x034a, 0x06 पूर्ण,
	अणु 0x034b, 0xeb पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x07 पूर्ण,
	अणु 0x034d, 0x80 पूर्ण,
	अणु 0x034e, 0x04 पूर्ण,
	अणु 0x034f, 0x38 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1640x1232_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x07 पूर्ण,
	अणु 0x0343, 0x2c पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x00 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x0c पूर्ण,
	अणु 0x0349, 0xcf पूर्ण,
	अणु 0x034a, 0x09 पूर्ण,
	अणु 0x034b, 0x9f पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x22 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x06 पूर्ण,
	अणु 0x034d, 0x68 पूर्ण,
	अणु 0x034e, 0x04 पूर्ण,
	अणु 0x034f, 0xd0 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1640x922_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x07 पूर्ण,
	अणु 0x0343, 0x2c पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x00 पूर्ण,
	अणु 0x0346, 0x01 पूर्ण,
	अणु 0x0347, 0x30 पूर्ण,
	अणु 0x0348, 0x0c पूर्ण,
	अणु 0x0349, 0xcf पूर्ण,
	अणु 0x034a, 0x08 पूर्ण,
	अणु 0x034b, 0x63 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x22 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x06 पूर्ण,
	अणु 0x034d, 0x68 पूर्ण,
	अणु 0x034e, 0x03 पूर्ण,
	अणु 0x034f, 0x9a पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1300x736_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x07 पूर्ण,
	अणु 0x0343, 0x2c पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x01 पूर्ण,
	अणु 0x0345, 0x58 पूर्ण,
	अणु 0x0346, 0x01 पूर्ण,
	अणु 0x0347, 0xf0 पूर्ण,
	अणु 0x0348, 0x0b पूर्ण,
	अणु 0x0349, 0x7f पूर्ण,
	अणु 0x034a, 0x07 पूर्ण,
	अणु 0x034b, 0xaf पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x22 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x05 पूर्ण,
	अणु 0x034d, 0x14 पूर्ण,
	अणु 0x034e, 0x02 पूर्ण,
	अणु 0x034f, 0xe0 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1296x736_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x07 पूर्ण,
	अणु 0x0343, 0x2c पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x01 पूर्ण,
	अणु 0x0345, 0x58 पूर्ण,
	अणु 0x0346, 0x01 पूर्ण,
	अणु 0x0347, 0xf0 पूर्ण,
	अणु 0x0348, 0x0b पूर्ण,
	अणु 0x0349, 0x77 पूर्ण,
	अणु 0x034a, 0x07 पूर्ण,
	अणु 0x034b, 0xaf पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x22 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x05 पूर्ण,
	अणु 0x034d, 0x10 पूर्ण,
	अणु 0x034e, 0x02 पूर्ण,
	अणु 0x034f, 0xe0 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1284x720_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x07 पूर्ण,
	अणु 0x0343, 0x2c पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x01 पूर्ण,
	अणु 0x0345, 0x68 पूर्ण,
	अणु 0x0346, 0x02 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x0b पूर्ण,
	अणु 0x0349, 0x6f पूर्ण,
	अणु 0x034a, 0x07 पूर्ण,
	अणु 0x034b, 0x9f पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x22 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x05 पूर्ण,
	अणु 0x034d, 0x04 पूर्ण,
	अणु 0x034e, 0x02 पूर्ण,
	अणु 0x034f, 0xd0 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_1280x720_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x07 पूर्ण,
	अणु 0x0343, 0x2c पूर्ण,
	अणु 0x0340, 0x05 पूर्ण,
	अणु 0x0341, 0x1a पूर्ण,
	अणु 0x0344, 0x01 पूर्ण,
	अणु 0x0345, 0x68 पूर्ण,
	अणु 0x0346, 0x02 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x0b पूर्ण,
	अणु 0x0349, 0x67 पूर्ण,
	अणु 0x034a, 0x07 पूर्ण,
	अणु 0x034b, 0x9f पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x22 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x05 पूर्ण,
	अणु 0x034d, 0x00 पूर्ण,
	अणु 0x034e, 0x02 पूर्ण,
	अणु 0x034f, 0xd0 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x00 पूर्ण,
	अणु 0x0701, 0x10 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx355_reg mode_820x616_regs[] = अणु
	अणु 0x0112, 0x0a पूर्ण,
	अणु 0x0113, 0x0a पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x0e पूर्ण,
	अणु 0x0343, 0x58 पूर्ण,
	अणु 0x0340, 0x02 पूर्ण,
	अणु 0x0341, 0x8c पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x00 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x0c पूर्ण,
	अणु 0x0349, 0xcf पूर्ण,
	अणु 0x034a, 0x09 पूर्ण,
	अणु 0x034b, 0x9f पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
	अणु 0x0222, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x44 पूर्ण,
	अणु 0x0902, 0x00 पूर्ण,
	अणु 0x034c, 0x03 पूर्ण,
	अणु 0x034d, 0x34 पूर्ण,
	अणु 0x034e, 0x02 पूर्ण,
	अणु 0x034f, 0x68 पूर्ण,
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x01 पूर्ण,
	अणु 0x0305, 0x02 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x78 पूर्ण,
	अणु 0x030b, 0x01 पूर्ण,
	अणु 0x030d, 0x02 पूर्ण,
	अणु 0x030e, 0x00 पूर्ण,
	अणु 0x030f, 0x4b पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0700, 0x02 पूर्ण,
	अणु 0x0701, 0x78 पूर्ण,
	अणु 0x0820, 0x0b पूर्ण,
	अणु 0x0821, 0x40 पूर्ण,
	अणु 0x3088, 0x04 पूर्ण,
	अणु 0x6813, 0x02 पूर्ण,
	अणु 0x6835, 0x07 पूर्ण,
	अणु 0x6836, 0x01 पूर्ण,
	अणु 0x6837, 0x04 पूर्ण,
	अणु 0x684d, 0x07 पूर्ण,
	अणु 0x684e, 0x01 पूर्ण,
	अणु 0x684f, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर imx355_test_pattern_menu[] = अणु
	"Disabled",
	"Solid Colour",
	"Eight Vertical Colour Bars",
	"Colour Bars With Fade to Grey",
	"Pseudorandom Sequence (PN9)",
पूर्ण;

/* supported link frequencies */
अटल स्थिर s64 link_freq_menu_items[] = अणु
	IMX355_LINK_FREQ_DEFAULT,
पूर्ण;

/* Mode configs */
अटल स्थिर काष्ठा imx355_mode supported_modes[] = अणु
	अणु
		.width = 3280,
		.height = 2464,
		.fll_def = 2615,
		.fll_min = 2615,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_3280x2464_regs),
			.regs = mode_3280x2464_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 3268,
		.height = 2448,
		.fll_def = 2615,
		.fll_min = 2615,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_3268x2448_regs),
			.regs = mode_3268x2448_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 3264,
		.height = 2448,
		.fll_def = 2615,
		.fll_min = 2615,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_3264x2448_regs),
			.regs = mode_3264x2448_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1940,
		.height = 1096,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1940x1096_regs),
			.regs = mode_1940x1096_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1936,
		.height = 1096,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1936x1096_regs),
			.regs = mode_1936x1096_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1924,
		.height = 1080,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1924x1080_regs),
			.regs = mode_1924x1080_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1920,
		.height = 1080,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1920x1080_regs),
			.regs = mode_1920x1080_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1640,
		.height = 1232,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 1836,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1640x1232_regs),
			.regs = mode_1640x1232_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1640,
		.height = 922,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 1836,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1640x922_regs),
			.regs = mode_1640x922_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1300,
		.height = 736,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 1836,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1300x736_regs),
			.regs = mode_1300x736_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1296,
		.height = 736,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 1836,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1296x736_regs),
			.regs = mode_1296x736_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1284,
		.height = 720,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 1836,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1284x720_regs),
			.regs = mode_1284x720_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 1280,
		.height = 720,
		.fll_def = 1306,
		.fll_min = 1306,
		.llp = 1836,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1280x720_regs),
			.regs = mode_1280x720_regs,
		पूर्ण,
	पूर्ण,
	अणु
		.width = 820,
		.height = 616,
		.fll_def = 652,
		.fll_min = 652,
		.llp = 3672,
		.link_freq_index = IMX355_LINK_FREQ_INDEX,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_820x616_regs),
			.regs = mode_820x616_regs,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा imx355 *to_imx355(काष्ठा v4l2_subdev *_sd)
अणु
	वापस container_of(_sd, काष्ठा imx355, sd);
पूर्ण

/* Get bayer order based on flip setting. */
अटल u32 imx355_get_क्रमmat_code(काष्ठा imx355 *imx355)
अणु
	/*
	 * Only one bayer order is supported.
	 * It depends on the flip settings.
	 */
	u32 code;
	अटल स्थिर u32 codes[2][2] = अणु
		अणु MEDIA_BUS_FMT_SRGGB10_1X10, MEDIA_BUS_FMT_SGRBG10_1X10, पूर्ण,
		अणु MEDIA_BUS_FMT_SGBRG10_1X10, MEDIA_BUS_FMT_SBGGR10_1X10, पूर्ण,
	पूर्ण;

	lockdep_निश्चित_held(&imx355->mutex);
	code = codes[imx355->vflip->val][imx355->hflip->val];

	वापस code;
पूर्ण

/* Read रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक imx355_पढ़ो_reg(काष्ठा imx355 *imx355, u16 reg, u32 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2];
	u8 data_buf[4] = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, addr_buf);
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

/* Write रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक imx355_ग_लिखो_reg(काष्ठा imx355 *imx355, u16 reg, u32 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
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
अटल पूर्णांक imx355_ग_लिखो_regs(काष्ठा imx355 *imx355,
			     स्थिर काष्ठा imx355_reg *regs, u32 len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
	पूर्णांक ret;
	u32 i;

	क्रम (i = 0; i < len; i++) अणु
		ret = imx355_ग_लिखो_reg(imx355, regs[i].address, 1, regs[i].val);
		अगर (ret) अणु
			dev_err_ratelimited(&client->dev,
					    "write reg 0x%4.4x return err %d",
					    regs[i].address, ret);

			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Open sub-device */
अटल पूर्णांक imx355_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा imx355 *imx355 = to_imx355(sd);
	काष्ठा v4l2_mbus_framefmt *try_fmt =
		v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	mutex_lock(&imx355->mutex);

	/* Initialize try_fmt */
	try_fmt->width = imx355->cur_mode->width;
	try_fmt->height = imx355->cur_mode->height;
	try_fmt->code = imx355_get_क्रमmat_code(imx355);
	try_fmt->field = V4L2_FIELD_NONE;

	mutex_unlock(&imx355->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक imx355_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imx355 *imx355 = container_of(ctrl->handler,
					     काष्ठा imx355, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
	s64 max;
	पूर्णांक ret;

	/* Propagate change of current control to all related controls */
	चयन (ctrl->id) अणु
	हाल V4L2_CID_VBLANK:
		/* Update max exposure जबतक meeting expected vblanking */
		max = imx355->cur_mode->height + ctrl->val - 10;
		__v4l2_ctrl_modअगरy_range(imx355->exposure,
					 imx355->exposure->minimum,
					 max, imx355->exposure->step, max);
		अवरोध;
	पूर्ण

	/*
	 * Applying V4L2 control value only happens
	 * when घातer is up क्रम streaming
	 */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		/* Analog gain = 1024/(1024 - ctrl->val) बार */
		ret = imx355_ग_लिखो_reg(imx355, IMX355_REG_ANALOG_GAIN, 2,
				       ctrl->val);
		अवरोध;
	हाल V4L2_CID_DIGITAL_GAIN:
		ret = imx355_ग_लिखो_reg(imx355, IMX355_REG_DIG_GAIN_GLOBAL, 2,
				       ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		ret = imx355_ग_लिखो_reg(imx355, IMX355_REG_EXPOSURE, 2,
				       ctrl->val);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		/* Update FLL that meets expected vertical blanking */
		ret = imx355_ग_लिखो_reg(imx355, IMX355_REG_FLL, 2,
				       imx355->cur_mode->height + ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = imx355_ग_लिखो_reg(imx355, IMX355_REG_TEST_PATTERN,
				       2, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
	हाल V4L2_CID_VFLIP:
		ret = imx355_ग_लिखो_reg(imx355, IMX355_REG_ORIENTATION, 1,
				       imx355->hflip->val |
				       imx355->vflip->val << 1);
		अवरोध;
	शेष:
		ret = -EINVAL;
		dev_info(&client->dev, "ctrl(id:0x%x,val:0x%x) is not handled",
			 ctrl->id, ctrl->val);
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops imx355_ctrl_ops = अणु
	.s_ctrl = imx355_set_ctrl,
पूर्ण;

अटल पूर्णांक imx355_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा imx355 *imx355 = to_imx355(sd);

	अगर (code->index > 0)
		वापस -EINVAL;

	mutex_lock(&imx355->mutex);
	code->code = imx355_get_क्रमmat_code(imx355);
	mutex_unlock(&imx355->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक imx355_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा imx355 *imx355 = to_imx355(sd);

	अगर (fse->index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	mutex_lock(&imx355->mutex);
	अगर (fse->code != imx355_get_क्रमmat_code(imx355)) अणु
		mutex_unlock(&imx355->mutex);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&imx355->mutex);

	fse->min_width = supported_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = supported_modes[fse->index].height;
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल व्योम imx355_update_pad_क्रमmat(काष्ठा imx355 *imx355,
				     स्थिर काष्ठा imx355_mode *mode,
				     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	fmt->क्रमmat.width = mode->width;
	fmt->क्रमmat.height = mode->height;
	fmt->क्रमmat.code = imx355_get_क्रमmat_code(imx355);
	fmt->क्रमmat.field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक imx355_करो_get_pad_क्रमmat(काष्ठा imx355 *imx355,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *framefmt;
	काष्ठा v4l2_subdev *sd = &imx355->sd;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		fmt->क्रमmat = *framefmt;
	पूर्ण अन्यथा अणु
		imx355_update_pad_क्रमmat(imx355, imx355->cur_mode, fmt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx355_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx355 *imx355 = to_imx355(sd);
	पूर्णांक ret;

	mutex_lock(&imx355->mutex);
	ret = imx355_करो_get_pad_क्रमmat(imx355, cfg, fmt);
	mutex_unlock(&imx355->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
imx355_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
		      काष्ठा v4l2_subdev_pad_config *cfg,
		      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx355 *imx355 = to_imx355(sd);
	स्थिर काष्ठा imx355_mode *mode;
	काष्ठा v4l2_mbus_framefmt *framefmt;
	s32 vblank_def;
	s32 vblank_min;
	s64 h_blank;
	u64 pixel_rate;
	u32 height;

	mutex_lock(&imx355->mutex);

	/*
	 * Only one bayer order is supported.
	 * It depends on the flip settings.
	 */
	fmt->क्रमmat.code = imx355_get_क्रमmat_code(imx355);

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes),
				      width, height,
				      fmt->क्रमmat.width, fmt->क्रमmat.height);
	imx355_update_pad_क्रमmat(imx355, mode, fmt);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*framefmt = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		imx355->cur_mode = mode;
		pixel_rate = imx355->link_def_freq * 2 * 4;
		करो_भाग(pixel_rate, 10);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(imx355->pixel_rate, pixel_rate);
		/* Update limits and set FPS to शेष */
		height = imx355->cur_mode->height;
		vblank_def = imx355->cur_mode->fll_def - height;
		vblank_min = imx355->cur_mode->fll_min - height;
		height = IMX355_FLL_MAX - height;
		__v4l2_ctrl_modअगरy_range(imx355->vblank, vblank_min, height, 1,
					 vblank_def);
		__v4l2_ctrl_s_ctrl(imx355->vblank, vblank_def);
		h_blank = mode->llp - imx355->cur_mode->width;
		/*
		 * Currently hblank is not changeable.
		 * So FPS control is करोne only by vblank.
		 */
		__v4l2_ctrl_modअगरy_range(imx355->hblank, h_blank,
					 h_blank, 1, h_blank);
	पूर्ण

	mutex_unlock(&imx355->mutex);

	वापस 0;
पूर्ण

/* Start streaming */
अटल पूर्णांक imx355_start_streaming(काष्ठा imx355 *imx355)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
	स्थिर काष्ठा imx355_reg_list *reg_list;
	पूर्णांक ret;

	/* Global Setting */
	reg_list = &imx355_global_setting;
	ret = imx355_ग_लिखो_regs(imx355, reg_list->regs, reg_list->num_of_regs);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set global settings");
		वापस ret;
	पूर्ण

	/* Apply शेष values of current mode */
	reg_list = &imx355->cur_mode->reg_list;
	ret = imx355_ग_लिखो_regs(imx355, reg_list->regs, reg_list->num_of_regs);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set mode");
		वापस ret;
	पूर्ण

	/* set digital gain control to all color mode */
	ret = imx355_ग_लिखो_reg(imx355, IMX355_REG_DPGA_USE_GLOBAL_GAIN, 1, 1);
	अगर (ret)
		वापस ret;

	/* Apply customized values from user */
	ret =  __v4l2_ctrl_handler_setup(imx355->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	वापस imx355_ग_लिखो_reg(imx355, IMX355_REG_MODE_SELECT,
				1, IMX355_MODE_STREAMING);
पूर्ण

/* Stop streaming */
अटल पूर्णांक imx355_stop_streaming(काष्ठा imx355 *imx355)
अणु
	वापस imx355_ग_लिखो_reg(imx355, IMX355_REG_MODE_SELECT,
				1, IMX355_MODE_STANDBY);
पूर्ण

अटल पूर्णांक imx355_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx355 *imx355 = to_imx355(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	mutex_lock(&imx355->mutex);
	अगर (imx355->streaming == enable) अणु
		mutex_unlock(&imx355->mutex);
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			जाओ err_unlock;
		पूर्ण

		/*
		 * Apply शेष & customized values
		 * and then start streaming.
		 */
		ret = imx355_start_streaming(imx355);
		अगर (ret)
			जाओ err_rpm_put;
	पूर्ण अन्यथा अणु
		imx355_stop_streaming(imx355);
		pm_runसमय_put(&client->dev);
	पूर्ण

	imx355->streaming = enable;

	/* vflip and hflip cannot change during streaming */
	__v4l2_ctrl_grab(imx355->vflip, enable);
	__v4l2_ctrl_grab(imx355->hflip, enable);

	mutex_unlock(&imx355->mutex);

	वापस ret;

err_rpm_put:
	pm_runसमय_put(&client->dev);
err_unlock:
	mutex_unlock(&imx355->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused imx355_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx355 *imx355 = to_imx355(sd);

	अगर (imx355->streaming)
		imx355_stop_streaming(imx355);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx355_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx355 *imx355 = to_imx355(sd);
	पूर्णांक ret;

	अगर (imx355->streaming) अणु
		ret = imx355_start_streaming(imx355);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	imx355_stop_streaming(imx355);
	imx355->streaming = 0;
	वापस ret;
पूर्ण

/* Verअगरy chip ID */
अटल पूर्णांक imx355_identअगरy_module(काष्ठा imx355 *imx355)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
	पूर्णांक ret;
	u32 val;

	ret = imx355_पढ़ो_reg(imx355, IMX355_REG_CHIP_ID, 2, &val);
	अगर (ret)
		वापस ret;

	अगर (val != IMX355_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x",
			IMX355_CHIP_ID, val);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops imx355_subdev_core_ops = अणु
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops imx355_video_ops = अणु
	.s_stream = imx355_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx355_pad_ops = अणु
	.क्रमागत_mbus_code = imx355_क्रमागत_mbus_code,
	.get_fmt = imx355_get_pad_क्रमmat,
	.set_fmt = imx355_set_pad_क्रमmat,
	.क्रमागत_frame_size = imx355_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx355_subdev_ops = अणु
	.core = &imx355_subdev_core_ops,
	.video = &imx355_video_ops,
	.pad = &imx355_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations imx355_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops imx355_पूर्णांकernal_ops = अणु
	.खोलो = imx355_खोलो,
पूर्ण;

/* Initialize control handlers */
अटल पूर्णांक imx355_init_controls(काष्ठा imx355 *imx355)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx355->sd);
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	s64 exposure_max;
	s64 vblank_def;
	s64 vblank_min;
	s64 hblank;
	u64 pixel_rate;
	स्थिर काष्ठा imx355_mode *mode;
	u32 max;
	पूर्णांक ret;

	ctrl_hdlr = &imx355->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 10);
	अगर (ret)
		वापस ret;

	ctrl_hdlr->lock = &imx355->mutex;
	max = ARRAY_SIZE(link_freq_menu_items) - 1;
	imx355->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr, &imx355_ctrl_ops,
						   V4L2_CID_LINK_FREQ, max, 0,
						   link_freq_menu_items);
	अगर (imx355->link_freq)
		imx355->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	/* pixel_rate = link_freq * 2 * nr_of_lanes / bits_per_sample */
	pixel_rate = imx355->link_def_freq * 2 * 4;
	करो_भाग(pixel_rate, 10);
	/* By शेष, PIXEL_RATE is पढ़ो only */
	imx355->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops,
					       V4L2_CID_PIXEL_RATE, pixel_rate,
					       pixel_rate, 1, pixel_rate);

	/* Initialize vblank/hblank/exposure parameters based on current mode */
	mode = imx355->cur_mode;
	vblank_def = mode->fll_def - mode->height;
	vblank_min = mode->fll_min - mode->height;
	imx355->vblank = v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops,
					   V4L2_CID_VBLANK, vblank_min,
					   IMX355_FLL_MAX - mode->height,
					   1, vblank_def);

	hblank = mode->llp - mode->width;
	imx355->hblank = v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops,
					   V4L2_CID_HBLANK, hblank, hblank,
					   1, hblank);
	अगर (imx355->hblank)
		imx355->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	/* fll >= exposure समय + adjust parameter (शेष value is 10) */
	exposure_max = mode->fll_def - 10;
	imx355->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     IMX355_EXPOSURE_MIN, exposure_max,
					     IMX355_EXPOSURE_STEP,
					     IMX355_EXPOSURE_DEFAULT);

	imx355->hflip = v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops,
					  V4L2_CID_HFLIP, 0, 1, 1, 0);
	imx355->vflip = v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops,
					  V4L2_CID_VFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  IMX355_ANA_GAIN_MIN, IMX355_ANA_GAIN_MAX,
			  IMX355_ANA_GAIN_STEP, IMX355_ANA_GAIN_DEFAULT);

	/* Digital gain */
	v4l2_ctrl_new_std(ctrl_hdlr, &imx355_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  IMX355_DGTL_GAIN_MIN, IMX355_DGTL_GAIN_MAX,
			  IMX355_DGTL_GAIN_STEP, IMX355_DGTL_GAIN_DEFAULT);

	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &imx355_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(imx355_test_pattern_menu) - 1,
				     0, 0, imx355_test_pattern_menu);
	अगर (ctrl_hdlr->error) अणु
		ret = ctrl_hdlr->error;
		dev_err(&client->dev, "control init failed: %d", ret);
		जाओ error;
	पूर्ण

	imx355->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(ctrl_hdlr);

	वापस ret;
पूर्ण

अटल काष्ठा imx355_hwcfg *imx355_get_hwcfg(काष्ठा device *dev)
अणु
	काष्ठा imx355_hwcfg *cfg;
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	काष्ठा fwnode_handle *ep;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!fwnode)
		वापस शून्य;

	ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (!ep)
		वापस शून्य;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	अगर (ret)
		जाओ out_err;

	cfg = devm_kzalloc(dev, माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		जाओ out_err;

	ret = fwnode_property_पढ़ो_u32(dev_fwnode(dev), "clock-frequency",
				       &cfg->ext_clk);
	अगर (ret) अणु
		dev_err(dev, "can't get clock frequency");
		जाओ out_err;
	पूर्ण

	dev_dbg(dev, "ext clk: %d", cfg->ext_clk);
	अगर (cfg->ext_clk != IMX355_EXT_CLK) अणु
		dev_err(dev, "external clock %d is not supported",
			cfg->ext_clk);
		जाओ out_err;
	पूर्ण

	dev_dbg(dev, "num of link freqs: %d", bus_cfg.nr_of_link_frequencies);
	अगर (!bus_cfg.nr_of_link_frequencies) अणु
		dev_warn(dev, "no link frequencies defined");
		जाओ out_err;
	पूर्ण

	cfg->nr_of_link_freqs = bus_cfg.nr_of_link_frequencies;
	cfg->link_freqs = devm_kसुस्मृति(dev,
				       bus_cfg.nr_of_link_frequencies + 1,
				       माप(*cfg->link_freqs), GFP_KERNEL);
	अगर (!cfg->link_freqs)
		जाओ out_err;

	क्रम (i = 0; i < bus_cfg.nr_of_link_frequencies; i++) अणु
		cfg->link_freqs[i] = bus_cfg.link_frequencies[i];
		dev_dbg(dev, "link_freq[%d] = %lld", i, cfg->link_freqs[i]);
	पूर्ण

	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);
	fwnode_handle_put(ep);
	वापस cfg;

out_err:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);
	fwnode_handle_put(ep);
	वापस शून्य;
पूर्ण

अटल पूर्णांक imx355_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा imx355 *imx355;
	पूर्णांक ret;
	u32 i;

	imx355 = devm_kzalloc(&client->dev, माप(*imx355), GFP_KERNEL);
	अगर (!imx355)
		वापस -ENOMEM;

	mutex_init(&imx355->mutex);

	/* Initialize subdev */
	v4l2_i2c_subdev_init(&imx355->sd, client, &imx355_subdev_ops);

	/* Check module identity */
	ret = imx355_identअगरy_module(imx355);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		जाओ error_probe;
	पूर्ण

	imx355->hwcfg = imx355_get_hwcfg(&client->dev);
	अगर (!imx355->hwcfg) अणु
		dev_err(&client->dev, "failed to get hwcfg");
		ret = -ENODEV;
		जाओ error_probe;
	पूर्ण

	imx355->link_def_freq = link_freq_menu_items[IMX355_LINK_FREQ_INDEX];
	क्रम (i = 0; i < imx355->hwcfg->nr_of_link_freqs; i++) अणु
		अगर (imx355->hwcfg->link_freqs[i] == imx355->link_def_freq) अणु
			dev_dbg(&client->dev, "link freq index %d matched", i);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == imx355->hwcfg->nr_of_link_freqs) अणु
		dev_err(&client->dev, "no link frequency supported");
		ret = -EINVAL;
		जाओ error_probe;
	पूर्ण

	/* Set शेष mode to max resolution */
	imx355->cur_mode = &supported_modes[0];

	ret = imx355_init_controls(imx355);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init controls: %d", ret);
		जाओ error_probe;
	पूर्ण

	/* Initialize subdev */
	imx355->sd.पूर्णांकernal_ops = &imx355_पूर्णांकernal_ops;
	imx355->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
		V4L2_SUBDEV_FL_HAS_EVENTS;
	imx355->sd.entity.ops = &imx355_subdev_entity_ops;
	imx355->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	/* Initialize source pad */
	imx355->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&imx355->sd.entity, 1, &imx355->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		जाओ error_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&imx355->sd);
	अगर (ret < 0)
		जाओ error_media_entity;

	/*
	 * Device is alपढ़ोy turned on by i2c-core with ACPI करोमुख्य PM.
	 * Enable runसमय PM and turn off the device.
	 */
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

error_media_entity:
	media_entity_cleanup(&imx355->sd.entity);

error_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(imx355->sd.ctrl_handler);

error_probe:
	mutex_destroy(&imx355->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक imx355_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx355 *imx355 = to_imx355(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	mutex_destroy(&imx355->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx355_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(imx355_suspend, imx355_resume)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id imx355_acpi_ids[] __maybe_unused = अणु
	अणु "SONY355A" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, imx355_acpi_ids);

अटल काष्ठा i2c_driver imx355_i2c_driver = अणु
	.driver = अणु
		.name = "imx355",
		.pm = &imx355_pm_ops,
		.acpi_match_table = ACPI_PTR(imx355_acpi_ids),
	पूर्ण,
	.probe_new = imx355_probe,
	.हटाओ = imx355_हटाओ,
पूर्ण;
module_i2c_driver(imx355_i2c_driver);

MODULE_AUTHOR("Qiu, Tianshu <tian.shu.qiu@intel.com>");
MODULE_AUTHOR("Rapolu, Chiranjeevi <chiranjeevi.rapolu@intel.com>");
MODULE_AUTHOR("Bingbu Cao <bingbu.cao@intel.com>");
MODULE_AUTHOR("Yang, Hyungwoo <hyungwoo.yang@intel.com>");
MODULE_DESCRIPTION("Sony imx355 sensor driver");
MODULE_LICENSE("GPL v2");
