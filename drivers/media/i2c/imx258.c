<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा IMX258_REG_VALUE_08BIT		1
#घोषणा IMX258_REG_VALUE_16BIT		2

#घोषणा IMX258_REG_MODE_SELECT		0x0100
#घोषणा IMX258_MODE_STANDBY		0x00
#घोषणा IMX258_MODE_STREAMING		0x01

/* Chip ID */
#घोषणा IMX258_REG_CHIP_ID		0x0016
#घोषणा IMX258_CHIP_ID			0x0258

/* V_TIMING पूर्णांकernal */
#घोषणा IMX258_VTS_30FPS		0x0c98
#घोषणा IMX258_VTS_30FPS_2K		0x0638
#घोषणा IMX258_VTS_30FPS_VGA		0x034c
#घोषणा IMX258_VTS_MAX			0xffff

/*Frame Length Line*/
#घोषणा IMX258_FLL_MIN			0x08a6
#घोषणा IMX258_FLL_MAX			0xffff
#घोषणा IMX258_FLL_STEP			1
#घोषणा IMX258_FLL_DEFAULT		0x0c98

/* HBLANK control - पढ़ो only */
#घोषणा IMX258_PPL_DEFAULT		5352

/* Exposure control */
#घोषणा IMX258_REG_EXPOSURE		0x0202
#घोषणा IMX258_EXPOSURE_MIN		4
#घोषणा IMX258_EXPOSURE_STEP		1
#घोषणा IMX258_EXPOSURE_DEFAULT		0x640
#घोषणा IMX258_EXPOSURE_MAX		65535

/* Analog gain control */
#घोषणा IMX258_REG_ANALOG_GAIN		0x0204
#घोषणा IMX258_ANA_GAIN_MIN		0
#घोषणा IMX258_ANA_GAIN_MAX		0x1fff
#घोषणा IMX258_ANA_GAIN_STEP		1
#घोषणा IMX258_ANA_GAIN_DEFAULT		0x0

/* Digital gain control */
#घोषणा IMX258_REG_GR_DIGITAL_GAIN	0x020e
#घोषणा IMX258_REG_R_DIGITAL_GAIN	0x0210
#घोषणा IMX258_REG_B_DIGITAL_GAIN	0x0212
#घोषणा IMX258_REG_GB_DIGITAL_GAIN	0x0214
#घोषणा IMX258_DGTL_GAIN_MIN		0
#घोषणा IMX258_DGTL_GAIN_MAX		4096	/* Max = 0xFFF */
#घोषणा IMX258_DGTL_GAIN_DEFAULT	1024
#घोषणा IMX258_DGTL_GAIN_STEP		1

/* HDR control */
#घोषणा IMX258_REG_HDR			0x0220
#घोषणा IMX258_HDR_ON			BIT(0)
#घोषणा IMX258_REG_HDR_RATIO		0x0222
#घोषणा IMX258_HDR_RATIO_MIN		0
#घोषणा IMX258_HDR_RATIO_MAX		5
#घोषणा IMX258_HDR_RATIO_STEP		1
#घोषणा IMX258_HDR_RATIO_DEFAULT	0x0

/* Test Pattern Control */
#घोषणा IMX258_REG_TEST_PATTERN		0x0600

/* Orientation */
#घोषणा REG_MIRROR_FLIP_CONTROL		0x0101
#घोषणा REG_CONFIG_MIRROR_FLIP		0x03
#घोषणा REG_CONFIG_FLIP_TEST_PATTERN	0x02

/* Input घड़ी frequency in Hz */
#घोषणा IMX258_INPUT_CLOCK_FREQ		19200000

काष्ठा imx258_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा imx258_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा imx258_reg *regs;
पूर्ण;

/* Link frequency config */
काष्ठा imx258_link_freq_config अणु
	u32 pixels_per_line;

	/* PLL रेजिस्टरs क्रम this link frequency */
	काष्ठा imx258_reg_list reg_list;
पूर्ण;

/* Mode : resolution and related config&values */
काष्ठा imx258_mode अणु
	/* Frame width */
	u32 width;
	/* Frame height */
	u32 height;

	/* V-timing */
	u32 vts_def;
	u32 vts_min;

	/* Index of Link frequency config to be used */
	u32 link_freq_index;
	/* Default रेजिस्टर values */
	काष्ठा imx258_reg_list reg_list;
पूर्ण;

/* 4208x3118 needs 1267Mbps/lane, 4 lanes */
अटल स्थिर काष्ठा imx258_reg mipi_data_rate_1267mbps[] = अणु
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x02 पूर्ण,
	अणु 0x0305, 0x03 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0xC6 पूर्ण,
	अणु 0x0309, 0x0A पूर्ण,
	अणु 0x030B, 0x01 पूर्ण,
	अणु 0x030D, 0x02 पूर्ण,
	अणु 0x030E, 0x00 पूर्ण,
	अणु 0x030F, 0xD8 पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0820, 0x13 पूर्ण,
	अणु 0x0821, 0x4C पूर्ण,
	अणु 0x0822, 0xCC पूर्ण,
	अणु 0x0823, 0xCC पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx258_reg mipi_data_rate_640mbps[] = अणु
	अणु 0x0301, 0x05 पूर्ण,
	अणु 0x0303, 0x02 पूर्ण,
	अणु 0x0305, 0x03 पूर्ण,
	अणु 0x0306, 0x00 पूर्ण,
	अणु 0x0307, 0x64 पूर्ण,
	अणु 0x0309, 0x0A पूर्ण,
	अणु 0x030B, 0x01 पूर्ण,
	अणु 0x030D, 0x02 पूर्ण,
	अणु 0x030E, 0x00 पूर्ण,
	अणु 0x030F, 0xD8 पूर्ण,
	अणु 0x0310, 0x00 पूर्ण,
	अणु 0x0820, 0x0A पूर्ण,
	अणु 0x0821, 0x00 पूर्ण,
	अणु 0x0822, 0x00 पूर्ण,
	अणु 0x0823, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx258_reg mode_4208x3118_regs[] = अणु
	अणु 0x0136, 0x13 पूर्ण,
	अणु 0x0137, 0x33 पूर्ण,
	अणु 0x3051, 0x00 पूर्ण,
	अणु 0x3052, 0x00 पूर्ण,
	अणु 0x4E21, 0x14 पूर्ण,
	अणु 0x6B11, 0xCF पूर्ण,
	अणु 0x7FF0, 0x08 पूर्ण,
	अणु 0x7FF1, 0x0F पूर्ण,
	अणु 0x7FF2, 0x08 पूर्ण,
	अणु 0x7FF3, 0x1B पूर्ण,
	अणु 0x7FF4, 0x23 पूर्ण,
	अणु 0x7FF5, 0x60 पूर्ण,
	अणु 0x7FF6, 0x00 पूर्ण,
	अणु 0x7FF7, 0x01 पूर्ण,
	अणु 0x7FF8, 0x00 पूर्ण,
	अणु 0x7FF9, 0x78 पूर्ण,
	अणु 0x7FFA, 0x00 पूर्ण,
	अणु 0x7FFB, 0x00 पूर्ण,
	अणु 0x7FFC, 0x00 पूर्ण,
	अणु 0x7FFD, 0x00 पूर्ण,
	अणु 0x7FFE, 0x00 पूर्ण,
	अणु 0x7FFF, 0x03 पूर्ण,
	अणु 0x7F76, 0x03 पूर्ण,
	अणु 0x7F77, 0xFE पूर्ण,
	अणु 0x7FA8, 0x03 पूर्ण,
	अणु 0x7FA9, 0xFE पूर्ण,
	अणु 0x7B24, 0x81 पूर्ण,
	अणु 0x7B25, 0x00 पूर्ण,
	अणु 0x6564, 0x07 पूर्ण,
	अणु 0x6B0D, 0x41 पूर्ण,
	अणु 0x653D, 0x04 पूर्ण,
	अणु 0x6B05, 0x8C पूर्ण,
	अणु 0x6B06, 0xF9 पूर्ण,
	अणु 0x6B08, 0x65 पूर्ण,
	अणु 0x6B09, 0xFC पूर्ण,
	अणु 0x6B0A, 0xCF पूर्ण,
	अणु 0x6B0B, 0xD2 पूर्ण,
	अणु 0x6700, 0x0E पूर्ण,
	अणु 0x6707, 0x0E पूर्ण,
	अणु 0x9104, 0x00 पूर्ण,
	अणु 0x4648, 0x7F पूर्ण,
	अणु 0x7420, 0x00 पूर्ण,
	अणु 0x7421, 0x1C पूर्ण,
	अणु 0x7422, 0x00 पूर्ण,
	अणु 0x7423, 0xD7 पूर्ण,
	अणु 0x5F04, 0x00 पूर्ण,
	अणु 0x5F05, 0xED पूर्ण,
	अणु 0x0112, 0x0A पूर्ण,
	अणु 0x0113, 0x0A पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x14 पूर्ण,
	अणु 0x0343, 0xE8 पूर्ण,
	अणु 0x0340, 0x0C पूर्ण,
	अणु 0x0341, 0x50 पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x00 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x10 पूर्ण,
	अणु 0x0349, 0x6F पूर्ण,
	अणु 0x034A, 0x0C पूर्ण,
	अणु 0x034B, 0x2E पूर्ण,
	अणु 0x0381, 0x01 पूर्ण,
	अणु 0x0383, 0x01 पूर्ण,
	अणु 0x0385, 0x01 पूर्ण,
	अणु 0x0387, 0x01 पूर्ण,
	अणु 0x0900, 0x00 पूर्ण,
	अणु 0x0901, 0x11 पूर्ण,
	अणु 0x0401, 0x00 पूर्ण,
	अणु 0x0404, 0x00 पूर्ण,
	अणु 0x0405, 0x10 पूर्ण,
	अणु 0x0408, 0x00 पूर्ण,
	अणु 0x0409, 0x00 पूर्ण,
	अणु 0x040A, 0x00 पूर्ण,
	अणु 0x040B, 0x00 पूर्ण,
	अणु 0x040C, 0x10 पूर्ण,
	अणु 0x040D, 0x70 पूर्ण,
	अणु 0x040E, 0x0C पूर्ण,
	अणु 0x040F, 0x30 पूर्ण,
	अणु 0x3038, 0x00 पूर्ण,
	अणु 0x303A, 0x00 पूर्ण,
	अणु 0x303B, 0x10 पूर्ण,
	अणु 0x300D, 0x00 पूर्ण,
	अणु 0x034C, 0x10 पूर्ण,
	अणु 0x034D, 0x70 पूर्ण,
	अणु 0x034E, 0x0C पूर्ण,
	अणु 0x034F, 0x30 पूर्ण,
	अणु 0x0350, 0x01 पूर्ण,
	अणु 0x0202, 0x0C पूर्ण,
	अणु 0x0203, 0x46 पूर्ण,
	अणु 0x0204, 0x00 पूर्ण,
	अणु 0x0205, 0x00 पूर्ण,
	अणु 0x020E, 0x01 पूर्ण,
	अणु 0x020F, 0x00 पूर्ण,
	अणु 0x0210, 0x01 पूर्ण,
	अणु 0x0211, 0x00 पूर्ण,
	अणु 0x0212, 0x01 पूर्ण,
	अणु 0x0213, 0x00 पूर्ण,
	अणु 0x0214, 0x01 पूर्ण,
	अणु 0x0215, 0x00 पूर्ण,
	अणु 0x7BCD, 0x00 पूर्ण,
	अणु 0x94DC, 0x20 पूर्ण,
	अणु 0x94DD, 0x20 पूर्ण,
	अणु 0x94DE, 0x20 पूर्ण,
	अणु 0x95DC, 0x20 पूर्ण,
	अणु 0x95DD, 0x20 पूर्ण,
	अणु 0x95DE, 0x20 पूर्ण,
	अणु 0x7FB0, 0x00 पूर्ण,
	अणु 0x9010, 0x3E पूर्ण,
	अणु 0x9419, 0x50 पूर्ण,
	अणु 0x941B, 0x50 पूर्ण,
	अणु 0x9519, 0x50 पूर्ण,
	अणु 0x951B, 0x50 पूर्ण,
	अणु 0x3030, 0x00 पूर्ण,
	अणु 0x3032, 0x00 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx258_reg mode_2104_1560_regs[] = अणु
	अणु 0x0136, 0x13 पूर्ण,
	अणु 0x0137, 0x33 पूर्ण,
	अणु 0x3051, 0x00 पूर्ण,
	अणु 0x3052, 0x00 पूर्ण,
	अणु 0x4E21, 0x14 पूर्ण,
	अणु 0x6B11, 0xCF पूर्ण,
	अणु 0x7FF0, 0x08 पूर्ण,
	अणु 0x7FF1, 0x0F पूर्ण,
	अणु 0x7FF2, 0x08 पूर्ण,
	अणु 0x7FF3, 0x1B पूर्ण,
	अणु 0x7FF4, 0x23 पूर्ण,
	अणु 0x7FF5, 0x60 पूर्ण,
	अणु 0x7FF6, 0x00 पूर्ण,
	अणु 0x7FF7, 0x01 पूर्ण,
	अणु 0x7FF8, 0x00 पूर्ण,
	अणु 0x7FF9, 0x78 पूर्ण,
	अणु 0x7FFA, 0x00 पूर्ण,
	अणु 0x7FFB, 0x00 पूर्ण,
	अणु 0x7FFC, 0x00 पूर्ण,
	अणु 0x7FFD, 0x00 पूर्ण,
	अणु 0x7FFE, 0x00 पूर्ण,
	अणु 0x7FFF, 0x03 पूर्ण,
	अणु 0x7F76, 0x03 पूर्ण,
	अणु 0x7F77, 0xFE पूर्ण,
	अणु 0x7FA8, 0x03 पूर्ण,
	अणु 0x7FA9, 0xFE पूर्ण,
	अणु 0x7B24, 0x81 पूर्ण,
	अणु 0x7B25, 0x00 पूर्ण,
	अणु 0x6564, 0x07 पूर्ण,
	अणु 0x6B0D, 0x41 पूर्ण,
	अणु 0x653D, 0x04 पूर्ण,
	अणु 0x6B05, 0x8C पूर्ण,
	अणु 0x6B06, 0xF9 पूर्ण,
	अणु 0x6B08, 0x65 पूर्ण,
	अणु 0x6B09, 0xFC पूर्ण,
	अणु 0x6B0A, 0xCF पूर्ण,
	अणु 0x6B0B, 0xD2 पूर्ण,
	अणु 0x6700, 0x0E पूर्ण,
	अणु 0x6707, 0x0E पूर्ण,
	अणु 0x9104, 0x00 पूर्ण,
	अणु 0x4648, 0x7F पूर्ण,
	अणु 0x7420, 0x00 पूर्ण,
	अणु 0x7421, 0x1C पूर्ण,
	अणु 0x7422, 0x00 पूर्ण,
	अणु 0x7423, 0xD7 पूर्ण,
	अणु 0x5F04, 0x00 पूर्ण,
	अणु 0x5F05, 0xED पूर्ण,
	अणु 0x0112, 0x0A पूर्ण,
	अणु 0x0113, 0x0A पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x14 पूर्ण,
	अणु 0x0343, 0xE8 पूर्ण,
	अणु 0x0340, 0x06 पूर्ण,
	अणु 0x0341, 0x38 पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x00 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x10 पूर्ण,
	अणु 0x0349, 0x6F पूर्ण,
	अणु 0x034A, 0x0C पूर्ण,
	अणु 0x034B, 0x2E पूर्ण,
	अणु 0x0381, 0x01 पूर्ण,
	अणु 0x0383, 0x01 पूर्ण,
	अणु 0x0385, 0x01 पूर्ण,
	अणु 0x0387, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x12 पूर्ण,
	अणु 0x0401, 0x01 पूर्ण,
	अणु 0x0404, 0x00 पूर्ण,
	अणु 0x0405, 0x20 पूर्ण,
	अणु 0x0408, 0x00 पूर्ण,
	अणु 0x0409, 0x02 पूर्ण,
	अणु 0x040A, 0x00 पूर्ण,
	अणु 0x040B, 0x00 पूर्ण,
	अणु 0x040C, 0x10 पूर्ण,
	अणु 0x040D, 0x6A पूर्ण,
	अणु 0x040E, 0x06 पूर्ण,
	अणु 0x040F, 0x18 पूर्ण,
	अणु 0x3038, 0x00 पूर्ण,
	अणु 0x303A, 0x00 पूर्ण,
	अणु 0x303B, 0x10 पूर्ण,
	अणु 0x300D, 0x00 पूर्ण,
	अणु 0x034C, 0x08 पूर्ण,
	अणु 0x034D, 0x38 पूर्ण,
	अणु 0x034E, 0x06 पूर्ण,
	अणु 0x034F, 0x18 पूर्ण,
	अणु 0x0350, 0x01 पूर्ण,
	अणु 0x0202, 0x06 पूर्ण,
	अणु 0x0203, 0x2E पूर्ण,
	अणु 0x0204, 0x00 पूर्ण,
	अणु 0x0205, 0x00 पूर्ण,
	अणु 0x020E, 0x01 पूर्ण,
	अणु 0x020F, 0x00 पूर्ण,
	अणु 0x0210, 0x01 पूर्ण,
	अणु 0x0211, 0x00 पूर्ण,
	अणु 0x0212, 0x01 पूर्ण,
	अणु 0x0213, 0x00 पूर्ण,
	अणु 0x0214, 0x01 पूर्ण,
	अणु 0x0215, 0x00 पूर्ण,
	अणु 0x7BCD, 0x01 पूर्ण,
	अणु 0x94DC, 0x20 पूर्ण,
	अणु 0x94DD, 0x20 पूर्ण,
	अणु 0x94DE, 0x20 पूर्ण,
	अणु 0x95DC, 0x20 पूर्ण,
	अणु 0x95DD, 0x20 पूर्ण,
	अणु 0x95DE, 0x20 पूर्ण,
	अणु 0x7FB0, 0x00 पूर्ण,
	अणु 0x9010, 0x3E पूर्ण,
	अणु 0x9419, 0x50 पूर्ण,
	अणु 0x941B, 0x50 पूर्ण,
	अणु 0x9519, 0x50 पूर्ण,
	अणु 0x951B, 0x50 पूर्ण,
	अणु 0x3030, 0x00 पूर्ण,
	अणु 0x3032, 0x00 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx258_reg mode_1048_780_regs[] = अणु
	अणु 0x0136, 0x13 पूर्ण,
	अणु 0x0137, 0x33 पूर्ण,
	अणु 0x3051, 0x00 पूर्ण,
	अणु 0x3052, 0x00 पूर्ण,
	अणु 0x4E21, 0x14 पूर्ण,
	अणु 0x6B11, 0xCF पूर्ण,
	अणु 0x7FF0, 0x08 पूर्ण,
	अणु 0x7FF1, 0x0F पूर्ण,
	अणु 0x7FF2, 0x08 पूर्ण,
	अणु 0x7FF3, 0x1B पूर्ण,
	अणु 0x7FF4, 0x23 पूर्ण,
	अणु 0x7FF5, 0x60 पूर्ण,
	अणु 0x7FF6, 0x00 पूर्ण,
	अणु 0x7FF7, 0x01 पूर्ण,
	अणु 0x7FF8, 0x00 पूर्ण,
	अणु 0x7FF9, 0x78 पूर्ण,
	अणु 0x7FFA, 0x00 पूर्ण,
	अणु 0x7FFB, 0x00 पूर्ण,
	अणु 0x7FFC, 0x00 पूर्ण,
	अणु 0x7FFD, 0x00 पूर्ण,
	अणु 0x7FFE, 0x00 पूर्ण,
	अणु 0x7FFF, 0x03 पूर्ण,
	अणु 0x7F76, 0x03 पूर्ण,
	अणु 0x7F77, 0xFE पूर्ण,
	अणु 0x7FA8, 0x03 पूर्ण,
	अणु 0x7FA9, 0xFE पूर्ण,
	अणु 0x7B24, 0x81 पूर्ण,
	अणु 0x7B25, 0x00 पूर्ण,
	अणु 0x6564, 0x07 पूर्ण,
	अणु 0x6B0D, 0x41 पूर्ण,
	अणु 0x653D, 0x04 पूर्ण,
	अणु 0x6B05, 0x8C पूर्ण,
	अणु 0x6B06, 0xF9 पूर्ण,
	अणु 0x6B08, 0x65 पूर्ण,
	अणु 0x6B09, 0xFC पूर्ण,
	अणु 0x6B0A, 0xCF पूर्ण,
	अणु 0x6B0B, 0xD2 पूर्ण,
	अणु 0x6700, 0x0E पूर्ण,
	अणु 0x6707, 0x0E पूर्ण,
	अणु 0x9104, 0x00 पूर्ण,
	अणु 0x4648, 0x7F पूर्ण,
	अणु 0x7420, 0x00 पूर्ण,
	अणु 0x7421, 0x1C पूर्ण,
	अणु 0x7422, 0x00 पूर्ण,
	अणु 0x7423, 0xD7 पूर्ण,
	अणु 0x5F04, 0x00 पूर्ण,
	अणु 0x5F05, 0xED पूर्ण,
	अणु 0x0112, 0x0A पूर्ण,
	अणु 0x0113, 0x0A पूर्ण,
	अणु 0x0114, 0x03 पूर्ण,
	अणु 0x0342, 0x14 पूर्ण,
	अणु 0x0343, 0xE8 पूर्ण,
	अणु 0x0340, 0x03 पूर्ण,
	अणु 0x0341, 0x4C पूर्ण,
	अणु 0x0344, 0x00 पूर्ण,
	अणु 0x0345, 0x00 पूर्ण,
	अणु 0x0346, 0x00 पूर्ण,
	अणु 0x0347, 0x00 पूर्ण,
	अणु 0x0348, 0x10 पूर्ण,
	अणु 0x0349, 0x6F पूर्ण,
	अणु 0x034A, 0x0C पूर्ण,
	अणु 0x034B, 0x2E पूर्ण,
	अणु 0x0381, 0x01 पूर्ण,
	अणु 0x0383, 0x01 पूर्ण,
	अणु 0x0385, 0x01 पूर्ण,
	अणु 0x0387, 0x01 पूर्ण,
	अणु 0x0900, 0x01 पूर्ण,
	अणु 0x0901, 0x14 पूर्ण,
	अणु 0x0401, 0x01 पूर्ण,
	अणु 0x0404, 0x00 पूर्ण,
	अणु 0x0405, 0x40 पूर्ण,
	अणु 0x0408, 0x00 पूर्ण,
	अणु 0x0409, 0x06 पूर्ण,
	अणु 0x040A, 0x00 पूर्ण,
	अणु 0x040B, 0x00 पूर्ण,
	अणु 0x040C, 0x10 पूर्ण,
	अणु 0x040D, 0x64 पूर्ण,
	अणु 0x040E, 0x03 पूर्ण,
	अणु 0x040F, 0x0C पूर्ण,
	अणु 0x3038, 0x00 पूर्ण,
	अणु 0x303A, 0x00 पूर्ण,
	अणु 0x303B, 0x10 पूर्ण,
	अणु 0x300D, 0x00 पूर्ण,
	अणु 0x034C, 0x04 पूर्ण,
	अणु 0x034D, 0x18 पूर्ण,
	अणु 0x034E, 0x03 पूर्ण,
	अणु 0x034F, 0x0C पूर्ण,
	अणु 0x0350, 0x01 पूर्ण,
	अणु 0x0202, 0x03 पूर्ण,
	अणु 0x0203, 0x42 पूर्ण,
	अणु 0x0204, 0x00 पूर्ण,
	अणु 0x0205, 0x00 पूर्ण,
	अणु 0x020E, 0x01 पूर्ण,
	अणु 0x020F, 0x00 पूर्ण,
	अणु 0x0210, 0x01 पूर्ण,
	अणु 0x0211, 0x00 पूर्ण,
	अणु 0x0212, 0x01 पूर्ण,
	अणु 0x0213, 0x00 पूर्ण,
	अणु 0x0214, 0x01 पूर्ण,
	अणु 0x0215, 0x00 पूर्ण,
	अणु 0x7BCD, 0x00 पूर्ण,
	अणु 0x94DC, 0x20 पूर्ण,
	अणु 0x94DD, 0x20 पूर्ण,
	अणु 0x94DE, 0x20 पूर्ण,
	अणु 0x95DC, 0x20 पूर्ण,
	अणु 0x95DD, 0x20 पूर्ण,
	अणु 0x95DE, 0x20 पूर्ण,
	अणु 0x7FB0, 0x00 पूर्ण,
	अणु 0x9010, 0x3E पूर्ण,
	अणु 0x9419, 0x50 पूर्ण,
	अणु 0x941B, 0x50 पूर्ण,
	अणु 0x9519, 0x50 पूर्ण,
	अणु 0x951B, 0x50 पूर्ण,
	अणु 0x3030, 0x00 पूर्ण,
	अणु 0x3032, 0x00 पूर्ण,
	अणु 0x0220, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर imx258_test_pattern_menu[] = अणु
	"Disabled",
	"Solid Colour",
	"Eight Vertical Colour Bars",
	"Colour Bars With Fade to Grey",
	"Pseudorandom Sequence (PN9)",
पूर्ण;

/* Configurations क्रम supported link frequencies */
#घोषणा IMX258_LINK_FREQ_634MHZ	633600000ULL
#घोषणा IMX258_LINK_FREQ_320MHZ	320000000ULL

क्रमागत अणु
	IMX258_LINK_FREQ_1267MBPS,
	IMX258_LINK_FREQ_640MBPS,
पूर्ण;

/*
 * pixel_rate = link_freq * data-rate * nr_of_lanes / bits_per_sample
 * data rate => द्विगुन data rate; number of lanes => 4; bits per pixel => 10
 */
अटल u64 link_freq_to_pixel_rate(u64 f)
अणु
	f *= 2 * 4;
	करो_भाग(f, 10);

	वापस f;
पूर्ण

/* Menu items क्रम LINK_FREQ V4L2 control */
अटल स्थिर s64 link_freq_menu_items[] = अणु
	IMX258_LINK_FREQ_634MHZ,
	IMX258_LINK_FREQ_320MHZ,
पूर्ण;

/* Link frequency configs */
अटल स्थिर काष्ठा imx258_link_freq_config link_freq_configs[] = अणु
	[IMX258_LINK_FREQ_1267MBPS] = अणु
		.pixels_per_line = IMX258_PPL_DEFAULT,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_1267mbps),
			.regs = mipi_data_rate_1267mbps,
		पूर्ण
	पूर्ण,
	[IMX258_LINK_FREQ_640MBPS] = अणु
		.pixels_per_line = IMX258_PPL_DEFAULT,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_640mbps),
			.regs = mipi_data_rate_640mbps,
		पूर्ण
	पूर्ण,
पूर्ण;

/* Mode configs */
अटल स्थिर काष्ठा imx258_mode supported_modes[] = अणु
	अणु
		.width = 4208,
		.height = 3118,
		.vts_def = IMX258_VTS_30FPS,
		.vts_min = IMX258_VTS_30FPS,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_4208x3118_regs),
			.regs = mode_4208x3118_regs,
		पूर्ण,
		.link_freq_index = IMX258_LINK_FREQ_1267MBPS,
	पूर्ण,
	अणु
		.width = 2104,
		.height = 1560,
		.vts_def = IMX258_VTS_30FPS_2K,
		.vts_min = IMX258_VTS_30FPS_2K,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_2104_1560_regs),
			.regs = mode_2104_1560_regs,
		पूर्ण,
		.link_freq_index = IMX258_LINK_FREQ_640MBPS,
	पूर्ण,
	अणु
		.width = 1048,
		.height = 780,
		.vts_def = IMX258_VTS_30FPS_VGA,
		.vts_min = IMX258_VTS_30FPS_VGA,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1048_780_regs),
			.regs = mode_1048_780_regs,
		पूर्ण,
		.link_freq_index = IMX258_LINK_FREQ_640MBPS,
	पूर्ण,
पूर्ण;

काष्ठा imx258 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	/* V4L2 Controls */
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl *hblank;
	काष्ठा v4l2_ctrl *exposure;

	/* Current mode */
	स्थिर काष्ठा imx258_mode *cur_mode;

	/*
	 * Mutex क्रम serialized access:
	 * Protect sensor module set pad क्रमmat and start/stop streaming safely.
	 */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;

	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा imx258 *to_imx258(काष्ठा v4l2_subdev *_sd)
अणु
	वापस container_of(_sd, काष्ठा imx258, sd);
पूर्ण

/* Read रेजिस्टरs up to 2 at a समय */
अटल पूर्णांक imx258_पढ़ो_reg(काष्ठा imx258 *imx258, u16 reg, u32 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
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
अटल पूर्णांक imx258_ग_लिखो_reg(काष्ठा imx258 *imx258, u16 reg, u32 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
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
अटल पूर्णांक imx258_ग_लिखो_regs(काष्ठा imx258 *imx258,
			     स्थिर काष्ठा imx258_reg *regs, u32 len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < len; i++) अणु
		ret = imx258_ग_लिखो_reg(imx258, regs[i].address, 1,
					regs[i].val);
		अगर (ret) अणु
			dev_err_ratelimited(
				&client->dev,
				"Failed to write reg 0x%4.4x. error = %d\n",
				regs[i].address, ret);

			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Open sub-device */
अटल पूर्णांक imx258_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *try_fmt =
		v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	/* Initialize try_fmt */
	try_fmt->width = supported_modes[0].width;
	try_fmt->height = supported_modes[0].height;
	try_fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	try_fmt->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक imx258_update_digital_gain(काष्ठा imx258 *imx258, u32 len, u32 val)
अणु
	पूर्णांक ret;

	ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_GR_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	अगर (ret)
		वापस ret;
	ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_GB_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	अगर (ret)
		वापस ret;
	ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_R_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	अगर (ret)
		वापस ret;
	ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_B_DIGITAL_GAIN,
				IMX258_REG_VALUE_16BIT,
				val);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक imx258_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imx258 *imx258 =
		container_of(ctrl->handler, काष्ठा imx258, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
	पूर्णांक ret = 0;

	/*
	 * Applying V4L2 control value only happens
	 * when घातer is up क्रम streaming
	 */
	अगर (pm_runसमय_get_अगर_in_use(&client->dev) == 0)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_ANALOG_GAIN,
				IMX258_REG_VALUE_16BIT,
				ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_EXPOSURE,
				IMX258_REG_VALUE_16BIT,
				ctrl->val);
		अवरोध;
	हाल V4L2_CID_DIGITAL_GAIN:
		ret = imx258_update_digital_gain(imx258, IMX258_REG_VALUE_16BIT,
				ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_TEST_PATTERN,
				IMX258_REG_VALUE_16BIT,
				ctrl->val);
		ret = imx258_ग_लिखो_reg(imx258, REG_MIRROR_FLIP_CONTROL,
				IMX258_REG_VALUE_08BIT,
				!ctrl->val ? REG_CONFIG_MIRROR_FLIP :
				REG_CONFIG_FLIP_TEST_PATTERN);
		अवरोध;
	हाल V4L2_CID_WIDE_DYNAMIC_RANGE:
		अगर (!ctrl->val) अणु
			ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_HDR,
					       IMX258_REG_VALUE_08BIT,
					       IMX258_HDR_RATIO_MIN);
		पूर्ण अन्यथा अणु
			ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_HDR,
					       IMX258_REG_VALUE_08BIT,
					       IMX258_HDR_ON);
			अगर (ret)
				अवरोध;
			ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_HDR_RATIO,
					       IMX258_REG_VALUE_08BIT,
					       BIT(IMX258_HDR_RATIO_MAX));
		पूर्ण
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

अटल स्थिर काष्ठा v4l2_ctrl_ops imx258_ctrl_ops = अणु
	.s_ctrl = imx258_set_ctrl,
पूर्ण;

अटल पूर्णांक imx258_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	/* Only one bayer order(GRBG) is supported */
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक imx258_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	अगर (fse->code != MEDIA_BUS_FMT_SGRBG10_1X10)
		वापस -EINVAL;

	fse->min_width = supported_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = supported_modes[fse->index].height;
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल व्योम imx258_update_pad_क्रमmat(स्थिर काष्ठा imx258_mode *mode,
				     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	fmt->क्रमmat.width = mode->width;
	fmt->क्रमmat.height = mode->height;
	fmt->क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक __imx258_get_pad_क्रमmat(काष्ठा imx258 *imx258,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(&imx258->sd, cfg,
							  fmt->pad);
	अन्यथा
		imx258_update_pad_क्रमmat(imx258->cur_mode, fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक imx258_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx258 *imx258 = to_imx258(sd);
	पूर्णांक ret;

	mutex_lock(&imx258->mutex);
	ret = __imx258_get_pad_क्रमmat(imx258, cfg, fmt);
	mutex_unlock(&imx258->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक imx258_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx258 *imx258 = to_imx258(sd);
	स्थिर काष्ठा imx258_mode *mode;
	काष्ठा v4l2_mbus_framefmt *framefmt;
	s32 vblank_def;
	s32 vblank_min;
	s64 h_blank;
	s64 pixel_rate;
	s64 link_freq;

	mutex_lock(&imx258->mutex);

	/* Only one raw bayer(GBRG) order is supported */
	fmt->क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;

	mode = v4l2_find_nearest_size(supported_modes,
		ARRAY_SIZE(supported_modes), width, height,
		fmt->क्रमmat.width, fmt->क्रमmat.height);
	imx258_update_pad_क्रमmat(mode, fmt);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*framefmt = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		imx258->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(imx258->link_freq, mode->link_freq_index);

		link_freq = link_freq_menu_items[mode->link_freq_index];
		pixel_rate = link_freq_to_pixel_rate(link_freq);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(imx258->pixel_rate, pixel_rate);
		/* Update limits and set FPS to शेष */
		vblank_def = imx258->cur_mode->vts_def -
			     imx258->cur_mode->height;
		vblank_min = imx258->cur_mode->vts_min -
			     imx258->cur_mode->height;
		__v4l2_ctrl_modअगरy_range(
			imx258->vblank, vblank_min,
			IMX258_VTS_MAX - imx258->cur_mode->height, 1,
			vblank_def);
		__v4l2_ctrl_s_ctrl(imx258->vblank, vblank_def);
		h_blank =
			link_freq_configs[mode->link_freq_index].pixels_per_line
			 - imx258->cur_mode->width;
		__v4l2_ctrl_modअगरy_range(imx258->hblank, h_blank,
					 h_blank, 1, h_blank);
	पूर्ण

	mutex_unlock(&imx258->mutex);

	वापस 0;
पूर्ण

/* Start streaming */
अटल पूर्णांक imx258_start_streaming(काष्ठा imx258 *imx258)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
	स्थिर काष्ठा imx258_reg_list *reg_list;
	पूर्णांक ret, link_freq_index;

	/* Setup PLL */
	link_freq_index = imx258->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = imx258_ग_लिखो_regs(imx258, reg_list->regs, reg_list->num_of_regs);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set plls\n", __func__);
		वापस ret;
	पूर्ण

	/* Apply शेष values of current mode */
	reg_list = &imx258->cur_mode->reg_list;
	ret = imx258_ग_लिखो_regs(imx258, reg_list->regs, reg_list->num_of_regs);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set mode\n", __func__);
		वापस ret;
	पूर्ण

	/* Set Orientation be 180 degree */
	ret = imx258_ग_लिखो_reg(imx258, REG_MIRROR_FLIP_CONTROL,
			       IMX258_REG_VALUE_08BIT, REG_CONFIG_MIRROR_FLIP);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set orientation\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Apply customized values from user */
	ret =  __v4l2_ctrl_handler_setup(imx258->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	/* set stream on रेजिस्टर */
	वापस imx258_ग_लिखो_reg(imx258, IMX258_REG_MODE_SELECT,
				IMX258_REG_VALUE_08BIT,
				IMX258_MODE_STREAMING);
पूर्ण

/* Stop streaming */
अटल पूर्णांक imx258_stop_streaming(काष्ठा imx258 *imx258)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
	पूर्णांक ret;

	/* set stream off रेजिस्टर */
	ret = imx258_ग_लिखो_reg(imx258, IMX258_REG_MODE_SELECT,
		IMX258_REG_VALUE_08BIT, IMX258_MODE_STANDBY);
	अगर (ret)
		dev_err(&client->dev, "%s failed to set stream\n", __func__);

	/*
	 * Return success even अगर it was an error, as there is nothing the
	 * caller can करो about it.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक imx258_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx258 *imx258 = to_imx258(sd);
	पूर्णांक ret;

	ret = clk_prepare_enable(imx258->clk);
	अगर (ret)
		dev_err(dev, "failed to enable clock\n");

	वापस ret;
पूर्ण

अटल पूर्णांक imx258_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx258 *imx258 = to_imx258(sd);

	clk_disable_unprepare(imx258->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक imx258_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx258 *imx258 = to_imx258(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	mutex_lock(&imx258->mutex);
	अगर (imx258->streaming == enable) अणु
		mutex_unlock(&imx258->mutex);
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
		ret = imx258_start_streaming(imx258);
		अगर (ret)
			जाओ err_rpm_put;
	पूर्ण अन्यथा अणु
		imx258_stop_streaming(imx258);
		pm_runसमय_put(&client->dev);
	पूर्ण

	imx258->streaming = enable;
	mutex_unlock(&imx258->mutex);

	वापस ret;

err_rpm_put:
	pm_runसमय_put(&client->dev);
err_unlock:
	mutex_unlock(&imx258->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused imx258_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx258 *imx258 = to_imx258(sd);

	अगर (imx258->streaming)
		imx258_stop_streaming(imx258);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx258_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx258 *imx258 = to_imx258(sd);
	पूर्णांक ret;

	अगर (imx258->streaming) अणु
		ret = imx258_start_streaming(imx258);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	imx258_stop_streaming(imx258);
	imx258->streaming = 0;
	वापस ret;
पूर्ण

/* Verअगरy chip ID */
अटल पूर्णांक imx258_identअगरy_module(काष्ठा imx258 *imx258)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
	पूर्णांक ret;
	u32 val;

	ret = imx258_पढ़ो_reg(imx258, IMX258_REG_CHIP_ID,
			      IMX258_REG_VALUE_16BIT, &val);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to read chip id %x\n",
			IMX258_CHIP_ID);
		वापस ret;
	पूर्ण

	अगर (val != IMX258_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x\n",
			IMX258_CHIP_ID, val);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops imx258_video_ops = अणु
	.s_stream = imx258_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx258_pad_ops = अणु
	.क्रमागत_mbus_code = imx258_क्रमागत_mbus_code,
	.get_fmt = imx258_get_pad_क्रमmat,
	.set_fmt = imx258_set_pad_क्रमmat,
	.क्रमागत_frame_size = imx258_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx258_subdev_ops = अणु
	.video = &imx258_video_ops,
	.pad = &imx258_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops imx258_पूर्णांकernal_ops = अणु
	.खोलो = imx258_खोलो,
पूर्ण;

/* Initialize control handlers */
अटल पूर्णांक imx258_init_controls(काष्ठा imx258 *imx258)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&imx258->sd);
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	s64 vblank_def;
	s64 vblank_min;
	s64 pixel_rate_min;
	s64 pixel_rate_max;
	पूर्णांक ret;

	ctrl_hdlr = &imx258->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 8);
	अगर (ret)
		वापस ret;

	mutex_init(&imx258->mutex);
	ctrl_hdlr->lock = &imx258->mutex;
	imx258->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr,
				&imx258_ctrl_ops,
				V4L2_CID_LINK_FREQ,
				ARRAY_SIZE(link_freq_menu_items) - 1,
				0,
				link_freq_menu_items);

	अगर (imx258->link_freq)
		imx258->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	pixel_rate_max = link_freq_to_pixel_rate(link_freq_menu_items[0]);
	pixel_rate_min = link_freq_to_pixel_rate(link_freq_menu_items[1]);
	/* By शेष, PIXEL_RATE is पढ़ो only */
	imx258->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &imx258_ctrl_ops,
				V4L2_CID_PIXEL_RATE,
				pixel_rate_min, pixel_rate_max,
				1, pixel_rate_max);


	vblank_def = imx258->cur_mode->vts_def - imx258->cur_mode->height;
	vblank_min = imx258->cur_mode->vts_min - imx258->cur_mode->height;
	imx258->vblank = v4l2_ctrl_new_std(
				ctrl_hdlr, &imx258_ctrl_ops, V4L2_CID_VBLANK,
				vblank_min,
				IMX258_VTS_MAX - imx258->cur_mode->height, 1,
				vblank_def);

	अगर (imx258->vblank)
		imx258->vblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	imx258->hblank = v4l2_ctrl_new_std(
				ctrl_hdlr, &imx258_ctrl_ops, V4L2_CID_HBLANK,
				IMX258_PPL_DEFAULT - imx258->cur_mode->width,
				IMX258_PPL_DEFAULT - imx258->cur_mode->width,
				1,
				IMX258_PPL_DEFAULT - imx258->cur_mode->width);

	अगर (imx258->hblank)
		imx258->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	imx258->exposure = v4l2_ctrl_new_std(
				ctrl_hdlr, &imx258_ctrl_ops,
				V4L2_CID_EXPOSURE, IMX258_EXPOSURE_MIN,
				IMX258_EXPOSURE_MAX, IMX258_EXPOSURE_STEP,
				IMX258_EXPOSURE_DEFAULT);

	v4l2_ctrl_new_std(ctrl_hdlr, &imx258_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
				IMX258_ANA_GAIN_MIN, IMX258_ANA_GAIN_MAX,
				IMX258_ANA_GAIN_STEP, IMX258_ANA_GAIN_DEFAULT);

	v4l2_ctrl_new_std(ctrl_hdlr, &imx258_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
				IMX258_DGTL_GAIN_MIN, IMX258_DGTL_GAIN_MAX,
				IMX258_DGTL_GAIN_STEP,
				IMX258_DGTL_GAIN_DEFAULT);

	v4l2_ctrl_new_std(ctrl_hdlr, &imx258_ctrl_ops, V4L2_CID_WIDE_DYNAMIC_RANGE,
				0, 1, 1, IMX258_HDR_RATIO_DEFAULT);

	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &imx258_ctrl_ops,
				V4L2_CID_TEST_PATTERN,
				ARRAY_SIZE(imx258_test_pattern_menu) - 1,
				0, 0, imx258_test_pattern_menu);

	अगर (ctrl_hdlr->error) अणु
		ret = ctrl_hdlr->error;
		dev_err(&client->dev, "%s control init failed (%d)\n",
				__func__, ret);
		जाओ error;
	पूर्ण

	imx258->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(ctrl_hdlr);
	mutex_destroy(&imx258->mutex);

	वापस ret;
पूर्ण

अटल व्योम imx258_मुक्त_controls(काष्ठा imx258 *imx258)
अणु
	v4l2_ctrl_handler_मुक्त(imx258->sd.ctrl_handler);
	mutex_destroy(&imx258->mutex);
पूर्ण

अटल पूर्णांक imx258_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा imx258 *imx258;
	पूर्णांक ret;
	u32 val = 0;

	imx258 = devm_kzalloc(&client->dev, माप(*imx258), GFP_KERNEL);
	अगर (!imx258)
		वापस -ENOMEM;

	imx258->clk = devm_clk_get_optional(&client->dev, शून्य);
	अगर (!imx258->clk) अणु
		dev_dbg(&client->dev,
			"no clock provided, using clock-frequency property\n");

		device_property_पढ़ो_u32(&client->dev, "clock-frequency", &val);
		अगर (val != IMX258_INPUT_CLOCK_FREQ)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (IS_ERR(imx258->clk)) अणु
		वापस dev_err_probe(&client->dev, PTR_ERR(imx258->clk),
				     "error getting clock\n");
	पूर्ण
	अगर (clk_get_rate(imx258->clk) != IMX258_INPUT_CLOCK_FREQ) अणु
		dev_err(&client->dev, "input clock frequency not supported\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check that the device is mounted upside करोwn. The driver only
	 * supports a single pixel order right now.
	 */
	ret = device_property_पढ़ो_u32(&client->dev, "rotation", &val);
	अगर (ret || val != 180)
		वापस -EINVAL;

	/* Initialize subdev */
	v4l2_i2c_subdev_init(&imx258->sd, client, &imx258_subdev_ops);

	/* Will be घातered off via pm_runसमय_idle */
	ret = imx258_घातer_on(&client->dev);
	अगर (ret)
		वापस ret;

	/* Check module identity */
	ret = imx258_identअगरy_module(imx258);
	अगर (ret)
		जाओ error_identअगरy;

	/* Set शेष mode to max resolution */
	imx258->cur_mode = &supported_modes[0];

	ret = imx258_init_controls(imx258);
	अगर (ret)
		जाओ error_identअगरy;

	/* Initialize subdev */
	imx258->sd.पूर्णांकernal_ops = &imx258_पूर्णांकernal_ops;
	imx258->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	imx258->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	/* Initialize source pad */
	imx258->pad.flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&imx258->sd.entity, 1, &imx258->pad);
	अगर (ret)
		जाओ error_handler_मुक्त;

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&imx258->sd);
	अगर (ret < 0)
		जाओ error_media_entity;

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

error_media_entity:
	media_entity_cleanup(&imx258->sd.entity);

error_handler_मुक्त:
	imx258_मुक्त_controls(imx258);

error_identअगरy:
	imx258_घातer_off(&client->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक imx258_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx258 *imx258 = to_imx258(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	imx258_मुक्त_controls(imx258);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		imx258_घातer_off(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx258_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(imx258_suspend, imx258_resume)
	SET_RUNTIME_PM_OPS(imx258_घातer_off, imx258_घातer_on, शून्य)
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id imx258_acpi_ids[] = अणु
	अणु "SONY258A" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, imx258_acpi_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id imx258_dt_ids[] = अणु
	अणु .compatible = "sony,imx258" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx258_dt_ids);

अटल काष्ठा i2c_driver imx258_i2c_driver = अणु
	.driver = अणु
		.name = "imx258",
		.pm = &imx258_pm_ops,
		.acpi_match_table = ACPI_PTR(imx258_acpi_ids),
		.of_match_table	= imx258_dt_ids,
	पूर्ण,
	.probe_new = imx258_probe,
	.हटाओ = imx258_हटाओ,
पूर्ण;

module_i2c_driver(imx258_i2c_driver);

MODULE_AUTHOR("Yeh, Andy <andy.yeh@intel.com>");
MODULE_AUTHOR("Chiang, Alan");
MODULE_AUTHOR("Chen, Jason");
MODULE_DESCRIPTION("Sony IMX258 sensor driver");
MODULE_LICENSE("GPL v2");
