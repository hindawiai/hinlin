<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Intel Corporation.

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#घोषणा OV13858_REG_VALUE_08BIT		1
#घोषणा OV13858_REG_VALUE_16BIT		2
#घोषणा OV13858_REG_VALUE_24BIT		3

#घोषणा OV13858_REG_MODE_SELECT		0x0100
#घोषणा OV13858_MODE_STANDBY		0x00
#घोषणा OV13858_MODE_STREAMING		0x01

#घोषणा OV13858_REG_SOFTWARE_RST	0x0103
#घोषणा OV13858_SOFTWARE_RST		0x01

/* PLL1 generates PCLK and MIPI_PHY_CLK */
#घोषणा OV13858_REG_PLL1_CTRL_0		0x0300
#घोषणा OV13858_REG_PLL1_CTRL_1		0x0301
#घोषणा OV13858_REG_PLL1_CTRL_2		0x0302
#घोषणा OV13858_REG_PLL1_CTRL_3		0x0303
#घोषणा OV13858_REG_PLL1_CTRL_4		0x0304
#घोषणा OV13858_REG_PLL1_CTRL_5		0x0305

/* PLL2 generates DAC_CLK, SCLK and SRAM_CLK */
#घोषणा OV13858_REG_PLL2_CTRL_B		0x030b
#घोषणा OV13858_REG_PLL2_CTRL_C		0x030c
#घोषणा OV13858_REG_PLL2_CTRL_D		0x030d
#घोषणा OV13858_REG_PLL2_CTRL_E		0x030e
#घोषणा OV13858_REG_PLL2_CTRL_F		0x030f
#घोषणा OV13858_REG_PLL2_CTRL_12	0x0312
#घोषणा OV13858_REG_MIPI_SC_CTRL0	0x3016
#घोषणा OV13858_REG_MIPI_SC_CTRL1	0x3022

/* Chip ID */
#घोषणा OV13858_REG_CHIP_ID		0x300a
#घोषणा OV13858_CHIP_ID			0x00d855

/* V_TIMING पूर्णांकernal */
#घोषणा OV13858_REG_VTS			0x380e
#घोषणा OV13858_VTS_30FPS		0x0c8e /* 30 fps */
#घोषणा OV13858_VTS_60FPS		0x0648 /* 60 fps */
#घोषणा OV13858_VTS_MAX			0x7fff

/* HBLANK control - पढ़ो only */
#घोषणा OV13858_PPL_270MHZ		2244
#घोषणा OV13858_PPL_540MHZ		4488

/* Exposure control */
#घोषणा OV13858_REG_EXPOSURE		0x3500
#घोषणा OV13858_EXPOSURE_MIN		4
#घोषणा OV13858_EXPOSURE_STEP		1
#घोषणा OV13858_EXPOSURE_DEFAULT	0x640

/* Analog gain control */
#घोषणा OV13858_REG_ANALOG_GAIN		0x3508
#घोषणा OV13858_ANA_GAIN_MIN		0
#घोषणा OV13858_ANA_GAIN_MAX		0x1fff
#घोषणा OV13858_ANA_GAIN_STEP		1
#घोषणा OV13858_ANA_GAIN_DEFAULT	0x80

/* Digital gain control */
#घोषणा OV13858_REG_B_MWB_GAIN		0x5100
#घोषणा OV13858_REG_G_MWB_GAIN		0x5102
#घोषणा OV13858_REG_R_MWB_GAIN		0x5104
#घोषणा OV13858_DGTL_GAIN_MIN		0
#घोषणा OV13858_DGTL_GAIN_MAX		16384	/* Max = 16 X */
#घोषणा OV13858_DGTL_GAIN_DEFAULT	1024	/* Default gain = 1 X */
#घोषणा OV13858_DGTL_GAIN_STEP		1	/* Each step = 1/1024 */

/* Test Pattern Control */
#घोषणा OV13858_REG_TEST_PATTERN	0x4503
#घोषणा OV13858_TEST_PATTERN_ENABLE	BIT(7)
#घोषणा OV13858_TEST_PATTERN_MASK	0xfc

/* Number of frames to skip */
#घोषणा OV13858_NUM_OF_SKIP_FRAMES	2

काष्ठा ov13858_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा ov13858_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा ov13858_reg *regs;
पूर्ण;

/* Link frequency config */
काष्ठा ov13858_link_freq_config अणु
	u32 pixels_per_line;

	/* PLL रेजिस्टरs क्रम this link frequency */
	काष्ठा ov13858_reg_list reg_list;
पूर्ण;

/* Mode : resolution and related config&values */
काष्ठा ov13858_mode अणु
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
	काष्ठा ov13858_reg_list reg_list;
पूर्ण;

/* 4224x3136 needs 1080Mbps/lane, 4 lanes */
अटल स्थिर काष्ठा ov13858_reg mipi_data_rate_1080mbps[] = अणु
	/* PLL1 रेजिस्टरs */
	अणुOV13858_REG_PLL1_CTRL_0, 0x07पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_1, 0x01पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_2, 0xc2पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_3, 0x00पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_4, 0x00पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_5, 0x01पूर्ण,

	/* PLL2 रेजिस्टरs */
	अणुOV13858_REG_PLL2_CTRL_B, 0x05पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_C, 0x01पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_D, 0x0eपूर्ण,
	अणुOV13858_REG_PLL2_CTRL_E, 0x05पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_F, 0x01पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_12, 0x01पूर्ण,
	अणुOV13858_REG_MIPI_SC_CTRL0, 0x72पूर्ण,
	अणुOV13858_REG_MIPI_SC_CTRL1, 0x01पूर्ण,
पूर्ण;

/*
 * 2112x1568, 2112x1188, 1056x784 need 540Mbps/lane,
 * 4 lanes
 */
अटल स्थिर काष्ठा ov13858_reg mipi_data_rate_540mbps[] = अणु
	/* PLL1 रेजिस्टरs */
	अणुOV13858_REG_PLL1_CTRL_0, 0x07पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_1, 0x01पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_2, 0xc2पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_3, 0x01पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_4, 0x00पूर्ण,
	अणुOV13858_REG_PLL1_CTRL_5, 0x01पूर्ण,

	/* PLL2 रेजिस्टरs */
	अणुOV13858_REG_PLL2_CTRL_B, 0x05पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_C, 0x01पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_D, 0x0eपूर्ण,
	अणुOV13858_REG_PLL2_CTRL_E, 0x05पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_F, 0x01पूर्ण,
	अणुOV13858_REG_PLL2_CTRL_12, 0x01पूर्ण,
	अणुOV13858_REG_MIPI_SC_CTRL0, 0x72पूर्ण,
	अणुOV13858_REG_MIPI_SC_CTRL1, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov13858_reg mode_4224x3136_regs[] = अणु
	अणु0x3013, 0x32पूर्ण,
	अणु0x301b, 0xf0पूर्ण,
	अणु0x301f, 0xd0पूर्ण,
	अणु0x3106, 0x15पूर्ण,
	अणु0x3107, 0x23पूर्ण,
	अणु0x350a, 0x00पूर्ण,
	अणु0x350e, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x2bपूर्ण,
	अणु0x3601, 0x52पूर्ण,
	अणु0x3602, 0x60पूर्ण,
	अणु0x3612, 0x05पूर्ण,
	अणु0x3613, 0xa4पूर्ण,
	अणु0x3620, 0x80पूर्ण,
	अणु0x3621, 0x10पूर्ण,
	अणु0x3622, 0x30पूर्ण,
	अणु0x3624, 0x1cपूर्ण,
	अणु0x3640, 0x10पूर्ण,
	अणु0x3641, 0x70पूर्ण,
	अणु0x3660, 0x04पूर्ण,
	अणु0x3661, 0x80पूर्ण,
	अणु0x3662, 0x12पूर्ण,
	अणु0x3664, 0x73पूर्ण,
	अणु0x3665, 0xa7पूर्ण,
	अणु0x366e, 0xffपूर्ण,
	अणु0x366f, 0xf4पूर्ण,
	अणु0x3674, 0x00पूर्ण,
	अणु0x3679, 0x0cपूर्ण,
	अणु0x367f, 0x01पूर्ण,
	अणु0x3680, 0x0cपूर्ण,
	अणु0x3681, 0x50पूर्ण,
	अणु0x3682, 0x50पूर्ण,
	अणु0x3683, 0xa9पूर्ण,
	अणु0x3684, 0xa9पूर्ण,
	अणु0x3709, 0x5fपूर्ण,
	अणु0x3714, 0x24पूर्ण,
	अणु0x371a, 0x3eपूर्ण,
	अणु0x3737, 0x04पूर्ण,
	अणु0x3738, 0xccपूर्ण,
	अणु0x3739, 0x12पूर्ण,
	अणु0x373d, 0x26पूर्ण,
	अणु0x3764, 0x20पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x37a1, 0x36पूर्ण,
	अणु0x37a8, 0x3bपूर्ण,
	अणु0x37ab, 0x31पूर्ण,
	अणु0x37c2, 0x04पूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c5, 0x00पूर्ण,
	अणु0x37d8, 0x03पूर्ण,
	अणु0x37d9, 0x0cपूर्ण,
	अणु0x37da, 0xc2पूर्ण,
	अणु0x37dc, 0x02पूर्ण,
	अणु0x37e0, 0x00पूर्ण,
	अणु0x37e1, 0x0aपूर्ण,
	अणु0x37e2, 0x14पूर्ण,
	अणु0x37e3, 0x04पूर्ण,
	अणु0x37e4, 0x2aपूर्ण,
	अणु0x37e5, 0x03पूर्ण,
	अणु0x37e6, 0x04पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x08पूर्ण,
	अणु0x3804, 0x10पूर्ण,
	अणु0x3805, 0x9fपूर्ण,
	अणु0x3806, 0x0cपूर्ण,
	अणु0x3807, 0x57पूर्ण,
	अणु0x3808, 0x10पूर्ण,
	अणु0x3809, 0x80पूर्ण,
	अणु0x380a, 0x0cपूर्ण,
	अणु0x380b, 0x40पूर्ण,
	अणु0x380c, 0x04पूर्ण,
	अणु0x380d, 0x62पूर्ण,
	अणु0x380e, 0x0cपूर्ण,
	अणु0x380f, 0x8eपूर्ण,
	अणु0x3811, 0x04पूर्ण,
	अणु0x3813, 0x05पूर्ण,
	अणु0x3814, 0x01पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x01पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3820, 0xa8पूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x3822, 0xc2पूर्ण,
	अणु0x3823, 0x18पूर्ण,
	अणु0x3826, 0x11पूर्ण,
	अणु0x3827, 0x1cपूर्ण,
	अणु0x3829, 0x03पूर्ण,
	अणु0x3832, 0x00पूर्ण,
	अणु0x3c80, 0x00पूर्ण,
	अणु0x3c87, 0x01पूर्ण,
	अणु0x3c8c, 0x19पूर्ण,
	अणु0x3c8d, 0x1cपूर्ण,
	अणु0x3c90, 0x00पूर्ण,
	अणु0x3c91, 0x00पूर्ण,
	अणु0x3c92, 0x00पूर्ण,
	अणु0x3c93, 0x00पूर्ण,
	अणु0x3c94, 0x40पूर्ण,
	अणु0x3c95, 0x54पूर्ण,
	अणु0x3c96, 0x34पूर्ण,
	अणु0x3c97, 0x04पूर्ण,
	अणु0x3c98, 0x00पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xc0पूर्ण,
	अणु0x3f00, 0x0bपूर्ण,
	अणु0x3f03, 0x00पूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x0fपूर्ण,
	अणु0x4011, 0xf0पूर्ण,
	अणु0x4017, 0x08पूर्ण,
	अणु0x4050, 0x04पूर्ण,
	अणु0x4051, 0x0bपूर्ण,
	अणु0x4052, 0x00पूर्ण,
	अणु0x4053, 0x80पूर्ण,
	अणु0x4054, 0x00पूर्ण,
	अणु0x4055, 0x80पूर्ण,
	अणु0x4056, 0x00पूर्ण,
	अणु0x4057, 0x80पूर्ण,
	अणु0x4058, 0x00पूर्ण,
	अणु0x4059, 0x80पूर्ण,
	अणु0x405e, 0x20पूर्ण,
	अणु0x4500, 0x07पूर्ण,
	अणु0x4503, 0x00पूर्ण,
	अणु0x450a, 0x04पूर्ण,
	अणु0x4809, 0x04पूर्ण,
	अणु0x480c, 0x12पूर्ण,
	अणु0x481f, 0x30पूर्ण,
	अणु0x4833, 0x10पूर्ण,
	अणु0x4837, 0x0eपूर्ण,
	अणु0x4902, 0x01पूर्ण,
	अणु0x4d00, 0x03पूर्ण,
	अणु0x4d01, 0xc9पूर्ण,
	अणु0x4d02, 0xbcपूर्ण,
	अणु0x4d03, 0xd7पूर्ण,
	अणु0x4d04, 0xf0पूर्ण,
	अणु0x4d05, 0xa2पूर्ण,
	अणु0x5000, 0xfdपूर्ण,
	अणु0x5001, 0x01पूर्ण,
	अणु0x5040, 0x39पूर्ण,
	अणु0x5041, 0x10पूर्ण,
	अणु0x5042, 0x10पूर्ण,
	अणु0x5043, 0x84पूर्ण,
	अणु0x5044, 0x62पूर्ण,
	अणु0x5180, 0x00पूर्ण,
	अणु0x5181, 0x10पूर्ण,
	अणु0x5182, 0x02पूर्ण,
	अणु0x5183, 0x0fपूर्ण,
	अणु0x5200, 0x1bपूर्ण,
	अणु0x520b, 0x07पूर्ण,
	अणु0x520c, 0x0fपूर्ण,
	अणु0x5300, 0x04पूर्ण,
	अणु0x5301, 0x0cपूर्ण,
	अणु0x5302, 0x0cपूर्ण,
	अणु0x5303, 0x0fपूर्ण,
	अणु0x5304, 0x00पूर्ण,
	अणु0x5305, 0x70पूर्ण,
	अणु0x5306, 0x00पूर्ण,
	अणु0x5307, 0x80पूर्ण,
	अणु0x5308, 0x00पूर्ण,
	अणु0x5309, 0xa5पूर्ण,
	अणु0x530a, 0x00पूर्ण,
	अणु0x530b, 0xd3पूर्ण,
	अणु0x530c, 0x00पूर्ण,
	अणु0x530d, 0xf0पूर्ण,
	अणु0x530e, 0x01पूर्ण,
	अणु0x530f, 0x10पूर्ण,
	अणु0x5310, 0x01पूर्ण,
	अणु0x5311, 0x20पूर्ण,
	अणु0x5312, 0x01पूर्ण,
	अणु0x5313, 0x20पूर्ण,
	अणु0x5314, 0x01पूर्ण,
	अणु0x5315, 0x20पूर्ण,
	अणु0x5316, 0x08पूर्ण,
	अणु0x5317, 0x08पूर्ण,
	अणु0x5318, 0x10पूर्ण,
	अणु0x5319, 0x88पूर्ण,
	अणु0x531a, 0x88पूर्ण,
	अणु0x531b, 0xa9पूर्ण,
	अणु0x531c, 0xaaपूर्ण,
	अणु0x531d, 0x0aपूर्ण,
	अणु0x5405, 0x02पूर्ण,
	अणु0x5406, 0x67पूर्ण,
	अणु0x5407, 0x01पूर्ण,
	अणु0x5408, 0x4aपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov13858_reg mode_2112x1568_regs[] = अणु
	अणु0x3013, 0x32पूर्ण,
	अणु0x301b, 0xf0पूर्ण,
	अणु0x301f, 0xd0पूर्ण,
	अणु0x3106, 0x15पूर्ण,
	अणु0x3107, 0x23पूर्ण,
	अणु0x350a, 0x00पूर्ण,
	अणु0x350e, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x2bपूर्ण,
	अणु0x3601, 0x52पूर्ण,
	अणु0x3602, 0x60पूर्ण,
	अणु0x3612, 0x05पूर्ण,
	अणु0x3613, 0xa4पूर्ण,
	अणु0x3620, 0x80पूर्ण,
	अणु0x3621, 0x10पूर्ण,
	अणु0x3622, 0x30पूर्ण,
	अणु0x3624, 0x1cपूर्ण,
	अणु0x3640, 0x10पूर्ण,
	अणु0x3641, 0x70पूर्ण,
	अणु0x3660, 0x04पूर्ण,
	अणु0x3661, 0x80पूर्ण,
	अणु0x3662, 0x10पूर्ण,
	अणु0x3664, 0x73पूर्ण,
	अणु0x3665, 0xa7पूर्ण,
	अणु0x366e, 0xffपूर्ण,
	अणु0x366f, 0xf4पूर्ण,
	अणु0x3674, 0x00पूर्ण,
	अणु0x3679, 0x0cपूर्ण,
	अणु0x367f, 0x01पूर्ण,
	अणु0x3680, 0x0cपूर्ण,
	अणु0x3681, 0x50पूर्ण,
	अणु0x3682, 0x50पूर्ण,
	अणु0x3683, 0xa9पूर्ण,
	अणु0x3684, 0xa9पूर्ण,
	अणु0x3709, 0x5fपूर्ण,
	अणु0x3714, 0x28पूर्ण,
	अणु0x371a, 0x3eपूर्ण,
	अणु0x3737, 0x08पूर्ण,
	अणु0x3738, 0xccपूर्ण,
	अणु0x3739, 0x20पूर्ण,
	अणु0x373d, 0x26पूर्ण,
	अणु0x3764, 0x20पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x37a1, 0x36पूर्ण,
	अणु0x37a8, 0x3bपूर्ण,
	अणु0x37ab, 0x31पूर्ण,
	अणु0x37c2, 0x14पूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c5, 0x00पूर्ण,
	अणु0x37d8, 0x03पूर्ण,
	अणु0x37d9, 0x0cपूर्ण,
	अणु0x37da, 0xc2पूर्ण,
	अणु0x37dc, 0x02पूर्ण,
	अणु0x37e0, 0x00पूर्ण,
	अणु0x37e1, 0x0aपूर्ण,
	अणु0x37e2, 0x14पूर्ण,
	अणु0x37e3, 0x08पूर्ण,
	अणु0x37e4, 0x38पूर्ण,
	अणु0x37e5, 0x03पूर्ण,
	अणु0x37e6, 0x08पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x10पूर्ण,
	अणु0x3805, 0x9fपूर्ण,
	अणु0x3806, 0x0cपूर्ण,
	अणु0x3807, 0x5fपूर्ण,
	अणु0x3808, 0x08पूर्ण,
	अणु0x3809, 0x40पूर्ण,
	अणु0x380a, 0x06पूर्ण,
	अणु0x380b, 0x20पूर्ण,
	अणु0x380c, 0x04पूर्ण,
	अणु0x380d, 0x62पूर्ण,
	अणु0x380e, 0x0cपूर्ण,
	अणु0x380f, 0x8eपूर्ण,
	अणु0x3811, 0x04पूर्ण,
	अणु0x3813, 0x05पूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x03पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3820, 0xabपूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x3822, 0xc2पूर्ण,
	अणु0x3823, 0x18पूर्ण,
	अणु0x3826, 0x04पूर्ण,
	अणु0x3827, 0x90पूर्ण,
	अणु0x3829, 0x07पूर्ण,
	अणु0x3832, 0x00पूर्ण,
	अणु0x3c80, 0x00पूर्ण,
	अणु0x3c87, 0x01पूर्ण,
	अणु0x3c8c, 0x19पूर्ण,
	अणु0x3c8d, 0x1cपूर्ण,
	अणु0x3c90, 0x00पूर्ण,
	अणु0x3c91, 0x00पूर्ण,
	अणु0x3c92, 0x00पूर्ण,
	अणु0x3c93, 0x00पूर्ण,
	अणु0x3c94, 0x40पूर्ण,
	अणु0x3c95, 0x54पूर्ण,
	अणु0x3c96, 0x34पूर्ण,
	अणु0x3c97, 0x04पूर्ण,
	अणु0x3c98, 0x00पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xc0पूर्ण,
	अणु0x3f00, 0x0bपूर्ण,
	अणु0x3f03, 0x00पूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x0dपूर्ण,
	अणु0x4011, 0xf0पूर्ण,
	अणु0x4017, 0x08पूर्ण,
	अणु0x4050, 0x04पूर्ण,
	अणु0x4051, 0x0bपूर्ण,
	अणु0x4052, 0x00पूर्ण,
	अणु0x4053, 0x80पूर्ण,
	अणु0x4054, 0x00पूर्ण,
	अणु0x4055, 0x80पूर्ण,
	अणु0x4056, 0x00पूर्ण,
	अणु0x4057, 0x80पूर्ण,
	अणु0x4058, 0x00पूर्ण,
	अणु0x4059, 0x80पूर्ण,
	अणु0x405e, 0x20पूर्ण,
	अणु0x4500, 0x07पूर्ण,
	अणु0x4503, 0x00पूर्ण,
	अणु0x450a, 0x04पूर्ण,
	अणु0x4809, 0x04पूर्ण,
	अणु0x480c, 0x12पूर्ण,
	अणु0x481f, 0x30पूर्ण,
	अणु0x4833, 0x10पूर्ण,
	अणु0x4837, 0x1cपूर्ण,
	अणु0x4902, 0x01पूर्ण,
	अणु0x4d00, 0x03पूर्ण,
	अणु0x4d01, 0xc9पूर्ण,
	अणु0x4d02, 0xbcपूर्ण,
	अणु0x4d03, 0xd7पूर्ण,
	अणु0x4d04, 0xf0पूर्ण,
	अणु0x4d05, 0xa2पूर्ण,
	अणु0x5000, 0xfdपूर्ण,
	अणु0x5001, 0x01पूर्ण,
	अणु0x5040, 0x39पूर्ण,
	अणु0x5041, 0x10पूर्ण,
	अणु0x5042, 0x10पूर्ण,
	अणु0x5043, 0x84पूर्ण,
	अणु0x5044, 0x62पूर्ण,
	अणु0x5180, 0x00पूर्ण,
	अणु0x5181, 0x10पूर्ण,
	अणु0x5182, 0x02पूर्ण,
	अणु0x5183, 0x0fपूर्ण,
	अणु0x5200, 0x1bपूर्ण,
	अणु0x520b, 0x07पूर्ण,
	अणु0x520c, 0x0fपूर्ण,
	अणु0x5300, 0x04पूर्ण,
	अणु0x5301, 0x0cपूर्ण,
	अणु0x5302, 0x0cपूर्ण,
	अणु0x5303, 0x0fपूर्ण,
	अणु0x5304, 0x00पूर्ण,
	अणु0x5305, 0x70पूर्ण,
	अणु0x5306, 0x00पूर्ण,
	अणु0x5307, 0x80पूर्ण,
	अणु0x5308, 0x00पूर्ण,
	अणु0x5309, 0xa5पूर्ण,
	अणु0x530a, 0x00पूर्ण,
	अणु0x530b, 0xd3पूर्ण,
	अणु0x530c, 0x00पूर्ण,
	अणु0x530d, 0xf0पूर्ण,
	अणु0x530e, 0x01पूर्ण,
	अणु0x530f, 0x10पूर्ण,
	अणु0x5310, 0x01पूर्ण,
	अणु0x5311, 0x20पूर्ण,
	अणु0x5312, 0x01पूर्ण,
	अणु0x5313, 0x20पूर्ण,
	अणु0x5314, 0x01पूर्ण,
	अणु0x5315, 0x20पूर्ण,
	अणु0x5316, 0x08पूर्ण,
	अणु0x5317, 0x08पूर्ण,
	अणु0x5318, 0x10पूर्ण,
	अणु0x5319, 0x88पूर्ण,
	अणु0x531a, 0x88पूर्ण,
	अणु0x531b, 0xa9पूर्ण,
	अणु0x531c, 0xaaपूर्ण,
	अणु0x531d, 0x0aपूर्ण,
	अणु0x5405, 0x02पूर्ण,
	अणु0x5406, 0x67पूर्ण,
	अणु0x5407, 0x01पूर्ण,
	अणु0x5408, 0x4aपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov13858_reg mode_2112x1188_regs[] = अणु
	अणु0x3013, 0x32पूर्ण,
	अणु0x301b, 0xf0पूर्ण,
	अणु0x301f, 0xd0पूर्ण,
	अणु0x3106, 0x15पूर्ण,
	अणु0x3107, 0x23पूर्ण,
	अणु0x350a, 0x00पूर्ण,
	अणु0x350e, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x2bपूर्ण,
	अणु0x3601, 0x52पूर्ण,
	अणु0x3602, 0x60पूर्ण,
	अणु0x3612, 0x05पूर्ण,
	अणु0x3613, 0xa4पूर्ण,
	अणु0x3620, 0x80पूर्ण,
	अणु0x3621, 0x10पूर्ण,
	अणु0x3622, 0x30पूर्ण,
	अणु0x3624, 0x1cपूर्ण,
	अणु0x3640, 0x10पूर्ण,
	अणु0x3641, 0x70पूर्ण,
	अणु0x3660, 0x04पूर्ण,
	अणु0x3661, 0x80पूर्ण,
	अणु0x3662, 0x10पूर्ण,
	अणु0x3664, 0x73पूर्ण,
	अणु0x3665, 0xa7पूर्ण,
	अणु0x366e, 0xffपूर्ण,
	अणु0x366f, 0xf4पूर्ण,
	अणु0x3674, 0x00पूर्ण,
	अणु0x3679, 0x0cपूर्ण,
	अणु0x367f, 0x01पूर्ण,
	अणु0x3680, 0x0cपूर्ण,
	अणु0x3681, 0x50पूर्ण,
	अणु0x3682, 0x50पूर्ण,
	अणु0x3683, 0xa9पूर्ण,
	अणु0x3684, 0xa9पूर्ण,
	अणु0x3709, 0x5fपूर्ण,
	अणु0x3714, 0x28पूर्ण,
	अणु0x371a, 0x3eपूर्ण,
	अणु0x3737, 0x08पूर्ण,
	अणु0x3738, 0xccपूर्ण,
	अणु0x3739, 0x20पूर्ण,
	अणु0x373d, 0x26पूर्ण,
	अणु0x3764, 0x20पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x37a1, 0x36पूर्ण,
	अणु0x37a8, 0x3bपूर्ण,
	अणु0x37ab, 0x31पूर्ण,
	अणु0x37c2, 0x14पूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c5, 0x00पूर्ण,
	अणु0x37d8, 0x03पूर्ण,
	अणु0x37d9, 0x0cपूर्ण,
	अणु0x37da, 0xc2पूर्ण,
	अणु0x37dc, 0x02पूर्ण,
	अणु0x37e0, 0x00पूर्ण,
	अणु0x37e1, 0x0aपूर्ण,
	अणु0x37e2, 0x14पूर्ण,
	अणु0x37e3, 0x08पूर्ण,
	अणु0x37e4, 0x38पूर्ण,
	अणु0x37e5, 0x03पूर्ण,
	अणु0x37e6, 0x08पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x01पूर्ण,
	अणु0x3803, 0x84पूर्ण,
	अणु0x3804, 0x10पूर्ण,
	अणु0x3805, 0x9fपूर्ण,
	अणु0x3806, 0x0aपूर्ण,
	अणु0x3807, 0xd3पूर्ण,
	अणु0x3808, 0x08पूर्ण,
	अणु0x3809, 0x40पूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0xa4पूर्ण,
	अणु0x380c, 0x04पूर्ण,
	अणु0x380d, 0x62पूर्ण,
	अणु0x380e, 0x0cपूर्ण,
	अणु0x380f, 0x8eपूर्ण,
	अणु0x3811, 0x08पूर्ण,
	अणु0x3813, 0x03पूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x03पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3820, 0xabपूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x3822, 0xc2पूर्ण,
	अणु0x3823, 0x18पूर्ण,
	अणु0x3826, 0x04पूर्ण,
	अणु0x3827, 0x90पूर्ण,
	अणु0x3829, 0x07पूर्ण,
	अणु0x3832, 0x00पूर्ण,
	अणु0x3c80, 0x00पूर्ण,
	अणु0x3c87, 0x01पूर्ण,
	अणु0x3c8c, 0x19पूर्ण,
	अणु0x3c8d, 0x1cपूर्ण,
	अणु0x3c90, 0x00पूर्ण,
	अणु0x3c91, 0x00पूर्ण,
	अणु0x3c92, 0x00पूर्ण,
	अणु0x3c93, 0x00पूर्ण,
	अणु0x3c94, 0x40पूर्ण,
	अणु0x3c95, 0x54पूर्ण,
	अणु0x3c96, 0x34पूर्ण,
	अणु0x3c97, 0x04पूर्ण,
	अणु0x3c98, 0x00पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xc0पूर्ण,
	अणु0x3f00, 0x0bपूर्ण,
	अणु0x3f03, 0x00पूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x0dपूर्ण,
	अणु0x4011, 0xf0पूर्ण,
	अणु0x4017, 0x08पूर्ण,
	अणु0x4050, 0x04पूर्ण,
	अणु0x4051, 0x0bपूर्ण,
	अणु0x4052, 0x00पूर्ण,
	अणु0x4053, 0x80पूर्ण,
	अणु0x4054, 0x00पूर्ण,
	अणु0x4055, 0x80पूर्ण,
	अणु0x4056, 0x00पूर्ण,
	अणु0x4057, 0x80पूर्ण,
	अणु0x4058, 0x00पूर्ण,
	अणु0x4059, 0x80पूर्ण,
	अणु0x405e, 0x20पूर्ण,
	अणु0x4500, 0x07पूर्ण,
	अणु0x4503, 0x00पूर्ण,
	अणु0x450a, 0x04पूर्ण,
	अणु0x4809, 0x04पूर्ण,
	अणु0x480c, 0x12पूर्ण,
	अणु0x481f, 0x30पूर्ण,
	अणु0x4833, 0x10पूर्ण,
	अणु0x4837, 0x1cपूर्ण,
	अणु0x4902, 0x01पूर्ण,
	अणु0x4d00, 0x03पूर्ण,
	अणु0x4d01, 0xc9पूर्ण,
	अणु0x4d02, 0xbcपूर्ण,
	अणु0x4d03, 0xd7पूर्ण,
	अणु0x4d04, 0xf0पूर्ण,
	अणु0x4d05, 0xa2पूर्ण,
	अणु0x5000, 0xfdपूर्ण,
	अणु0x5001, 0x01पूर्ण,
	अणु0x5040, 0x39पूर्ण,
	अणु0x5041, 0x10पूर्ण,
	अणु0x5042, 0x10पूर्ण,
	अणु0x5043, 0x84पूर्ण,
	अणु0x5044, 0x62पूर्ण,
	अणु0x5180, 0x00पूर्ण,
	अणु0x5181, 0x10पूर्ण,
	अणु0x5182, 0x02पूर्ण,
	अणु0x5183, 0x0fपूर्ण,
	अणु0x5200, 0x1bपूर्ण,
	अणु0x520b, 0x07पूर्ण,
	अणु0x520c, 0x0fपूर्ण,
	अणु0x5300, 0x04पूर्ण,
	अणु0x5301, 0x0cपूर्ण,
	अणु0x5302, 0x0cपूर्ण,
	अणु0x5303, 0x0fपूर्ण,
	अणु0x5304, 0x00पूर्ण,
	अणु0x5305, 0x70पूर्ण,
	अणु0x5306, 0x00पूर्ण,
	अणु0x5307, 0x80पूर्ण,
	अणु0x5308, 0x00पूर्ण,
	अणु0x5309, 0xa5पूर्ण,
	अणु0x530a, 0x00पूर्ण,
	अणु0x530b, 0xd3पूर्ण,
	अणु0x530c, 0x00पूर्ण,
	अणु0x530d, 0xf0पूर्ण,
	अणु0x530e, 0x01पूर्ण,
	अणु0x530f, 0x10पूर्ण,
	अणु0x5310, 0x01पूर्ण,
	अणु0x5311, 0x20पूर्ण,
	अणु0x5312, 0x01पूर्ण,
	अणु0x5313, 0x20पूर्ण,
	अणु0x5314, 0x01पूर्ण,
	अणु0x5315, 0x20पूर्ण,
	अणु0x5316, 0x08पूर्ण,
	अणु0x5317, 0x08पूर्ण,
	अणु0x5318, 0x10पूर्ण,
	अणु0x5319, 0x88पूर्ण,
	अणु0x531a, 0x88पूर्ण,
	अणु0x531b, 0xa9पूर्ण,
	अणु0x531c, 0xaaपूर्ण,
	अणु0x531d, 0x0aपूर्ण,
	अणु0x5405, 0x02पूर्ण,
	अणु0x5406, 0x67पूर्ण,
	अणु0x5407, 0x01पूर्ण,
	अणु0x5408, 0x4aपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov13858_reg mode_1056x784_regs[] = अणु
	अणु0x3013, 0x32पूर्ण,
	अणु0x301b, 0xf0पूर्ण,
	अणु0x301f, 0xd0पूर्ण,
	अणु0x3106, 0x15पूर्ण,
	अणु0x3107, 0x23पूर्ण,
	अणु0x350a, 0x00पूर्ण,
	अणु0x350e, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x2bपूर्ण,
	अणु0x3601, 0x52पूर्ण,
	अणु0x3602, 0x60पूर्ण,
	अणु0x3612, 0x05पूर्ण,
	अणु0x3613, 0xa4पूर्ण,
	अणु0x3620, 0x80पूर्ण,
	अणु0x3621, 0x10पूर्ण,
	अणु0x3622, 0x30पूर्ण,
	अणु0x3624, 0x1cपूर्ण,
	अणु0x3640, 0x10पूर्ण,
	अणु0x3641, 0x70पूर्ण,
	अणु0x3660, 0x04पूर्ण,
	अणु0x3661, 0x80पूर्ण,
	अणु0x3662, 0x08पूर्ण,
	अणु0x3664, 0x73पूर्ण,
	अणु0x3665, 0xa7पूर्ण,
	अणु0x366e, 0xffपूर्ण,
	अणु0x366f, 0xf4पूर्ण,
	अणु0x3674, 0x00पूर्ण,
	अणु0x3679, 0x0cपूर्ण,
	अणु0x367f, 0x01पूर्ण,
	अणु0x3680, 0x0cपूर्ण,
	अणु0x3681, 0x50पूर्ण,
	अणु0x3682, 0x50पूर्ण,
	अणु0x3683, 0xa9पूर्ण,
	अणु0x3684, 0xa9पूर्ण,
	अणु0x3709, 0x5fपूर्ण,
	अणु0x3714, 0x30पूर्ण,
	अणु0x371a, 0x3eपूर्ण,
	अणु0x3737, 0x08पूर्ण,
	अणु0x3738, 0xccपूर्ण,
	अणु0x3739, 0x20पूर्ण,
	अणु0x373d, 0x26पूर्ण,
	अणु0x3764, 0x20पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x37a1, 0x36पूर्ण,
	अणु0x37a8, 0x3bपूर्ण,
	अणु0x37ab, 0x31पूर्ण,
	अणु0x37c2, 0x2cपूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c5, 0x00पूर्ण,
	अणु0x37d8, 0x03पूर्ण,
	अणु0x37d9, 0x06पूर्ण,
	अणु0x37da, 0xc2पूर्ण,
	अणु0x37dc, 0x02पूर्ण,
	अणु0x37e0, 0x00पूर्ण,
	अणु0x37e1, 0x0aपूर्ण,
	अणु0x37e2, 0x14पूर्ण,
	अणु0x37e3, 0x08पूर्ण,
	अणु0x37e4, 0x36पूर्ण,
	अणु0x37e5, 0x03पूर्ण,
	अणु0x37e6, 0x08पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x10पूर्ण,
	अणु0x3805, 0x9fपूर्ण,
	अणु0x3806, 0x0cपूर्ण,
	अणु0x3807, 0x5fपूर्ण,
	अणु0x3808, 0x04पूर्ण,
	अणु0x3809, 0x20पूर्ण,
	अणु0x380a, 0x03पूर्ण,
	अणु0x380b, 0x10पूर्ण,
	अणु0x380c, 0x04पूर्ण,
	अणु0x380d, 0x62पूर्ण,
	अणु0x380e, 0x0cपूर्ण,
	अणु0x380f, 0x8eपूर्ण,
	अणु0x3811, 0x04पूर्ण,
	अणु0x3813, 0x05पूर्ण,
	अणु0x3814, 0x07पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x07पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3820, 0xacपूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x3822, 0xc2पूर्ण,
	अणु0x3823, 0x18पूर्ण,
	अणु0x3826, 0x04पूर्ण,
	अणु0x3827, 0x48पूर्ण,
	अणु0x3829, 0x03पूर्ण,
	अणु0x3832, 0x00पूर्ण,
	अणु0x3c80, 0x00पूर्ण,
	अणु0x3c87, 0x01पूर्ण,
	अणु0x3c8c, 0x19पूर्ण,
	अणु0x3c8d, 0x1cपूर्ण,
	अणु0x3c90, 0x00पूर्ण,
	अणु0x3c91, 0x00पूर्ण,
	अणु0x3c92, 0x00पूर्ण,
	अणु0x3c93, 0x00पूर्ण,
	अणु0x3c94, 0x40पूर्ण,
	अणु0x3c95, 0x54पूर्ण,
	अणु0x3c96, 0x34पूर्ण,
	अणु0x3c97, 0x04पूर्ण,
	अणु0x3c98, 0x00पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xc0पूर्ण,
	अणु0x3f00, 0x0bपूर्ण,
	अणु0x3f03, 0x00पूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x05पूर्ण,
	अणु0x4011, 0xf0पूर्ण,
	अणु0x4017, 0x08पूर्ण,
	अणु0x4050, 0x02पूर्ण,
	अणु0x4051, 0x05पूर्ण,
	अणु0x4052, 0x00पूर्ण,
	अणु0x4053, 0x80पूर्ण,
	अणु0x4054, 0x00पूर्ण,
	अणु0x4055, 0x80पूर्ण,
	अणु0x4056, 0x00पूर्ण,
	अणु0x4057, 0x80पूर्ण,
	अणु0x4058, 0x00पूर्ण,
	अणु0x4059, 0x80पूर्ण,
	अणु0x405e, 0x20पूर्ण,
	अणु0x4500, 0x07पूर्ण,
	अणु0x4503, 0x00पूर्ण,
	अणु0x450a, 0x04पूर्ण,
	अणु0x4809, 0x04पूर्ण,
	अणु0x480c, 0x12पूर्ण,
	अणु0x481f, 0x30पूर्ण,
	अणु0x4833, 0x10पूर्ण,
	अणु0x4837, 0x1eपूर्ण,
	अणु0x4902, 0x02पूर्ण,
	अणु0x4d00, 0x03पूर्ण,
	अणु0x4d01, 0xc9पूर्ण,
	अणु0x4d02, 0xbcपूर्ण,
	अणु0x4d03, 0xd7पूर्ण,
	अणु0x4d04, 0xf0पूर्ण,
	अणु0x4d05, 0xa2पूर्ण,
	अणु0x5000, 0xfdपूर्ण,
	अणु0x5001, 0x01पूर्ण,
	अणु0x5040, 0x39पूर्ण,
	अणु0x5041, 0x10पूर्ण,
	अणु0x5042, 0x10पूर्ण,
	अणु0x5043, 0x84पूर्ण,
	अणु0x5044, 0x62पूर्ण,
	अणु0x5180, 0x00पूर्ण,
	अणु0x5181, 0x10पूर्ण,
	अणु0x5182, 0x02पूर्ण,
	अणु0x5183, 0x0fपूर्ण,
	अणु0x5200, 0x1bपूर्ण,
	अणु0x520b, 0x07पूर्ण,
	अणु0x520c, 0x0fपूर्ण,
	अणु0x5300, 0x04पूर्ण,
	अणु0x5301, 0x0cपूर्ण,
	अणु0x5302, 0x0cपूर्ण,
	अणु0x5303, 0x0fपूर्ण,
	अणु0x5304, 0x00पूर्ण,
	अणु0x5305, 0x70पूर्ण,
	अणु0x5306, 0x00पूर्ण,
	अणु0x5307, 0x80पूर्ण,
	अणु0x5308, 0x00पूर्ण,
	अणु0x5309, 0xa5पूर्ण,
	अणु0x530a, 0x00पूर्ण,
	अणु0x530b, 0xd3पूर्ण,
	अणु0x530c, 0x00पूर्ण,
	अणु0x530d, 0xf0पूर्ण,
	अणु0x530e, 0x01पूर्ण,
	अणु0x530f, 0x10पूर्ण,
	अणु0x5310, 0x01पूर्ण,
	अणु0x5311, 0x20पूर्ण,
	अणु0x5312, 0x01पूर्ण,
	अणु0x5313, 0x20पूर्ण,
	अणु0x5314, 0x01पूर्ण,
	अणु0x5315, 0x20पूर्ण,
	अणु0x5316, 0x08पूर्ण,
	अणु0x5317, 0x08पूर्ण,
	अणु0x5318, 0x10पूर्ण,
	अणु0x5319, 0x88पूर्ण,
	अणु0x531a, 0x88पूर्ण,
	अणु0x531b, 0xa9पूर्ण,
	अणु0x531c, 0xaaपूर्ण,
	अणु0x531d, 0x0aपूर्ण,
	अणु0x5405, 0x02पूर्ण,
	अणु0x5406, 0x67पूर्ण,
	अणु0x5407, 0x01पूर्ण,
	अणु0x5408, 0x4aपूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov13858_test_pattern_menu[] = अणु
	"Disabled",
	"Vertical Color Bar Type 1",
	"Vertical Color Bar Type 2",
	"Vertical Color Bar Type 3",
	"Vertical Color Bar Type 4"
पूर्ण;

/* Configurations क्रम supported link frequencies */
#घोषणा OV13858_NUM_OF_LINK_FREQS	2
#घोषणा OV13858_LINK_FREQ_540MHZ	540000000ULL
#घोषणा OV13858_LINK_FREQ_270MHZ	270000000ULL
#घोषणा OV13858_LINK_FREQ_INDEX_0	0
#घोषणा OV13858_LINK_FREQ_INDEX_1	1

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
अटल स्थिर s64 link_freq_menu_items[OV13858_NUM_OF_LINK_FREQS] = अणु
	OV13858_LINK_FREQ_540MHZ,
	OV13858_LINK_FREQ_270MHZ
पूर्ण;

/* Link frequency configs */
अटल स्थिर काष्ठा ov13858_link_freq_config
			link_freq_configs[OV13858_NUM_OF_LINK_FREQS] = अणु
	अणु
		.pixels_per_line = OV13858_PPL_540MHZ,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_1080mbps),
			.regs = mipi_data_rate_1080mbps,
		पूर्ण
	पूर्ण,
	अणु
		.pixels_per_line = OV13858_PPL_270MHZ,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_540mbps),
			.regs = mipi_data_rate_540mbps,
		पूर्ण
	पूर्ण
पूर्ण;

/* Mode configs */
अटल स्थिर काष्ठा ov13858_mode supported_modes[] = अणु
	अणु
		.width = 4224,
		.height = 3136,
		.vts_def = OV13858_VTS_30FPS,
		.vts_min = OV13858_VTS_30FPS,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_4224x3136_regs),
			.regs = mode_4224x3136_regs,
		पूर्ण,
		.link_freq_index = OV13858_LINK_FREQ_INDEX_0,
	पूर्ण,
	अणु
		.width = 2112,
		.height = 1568,
		.vts_def = OV13858_VTS_30FPS,
		.vts_min = 1608,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_2112x1568_regs),
			.regs = mode_2112x1568_regs,
		पूर्ण,
		.link_freq_index = OV13858_LINK_FREQ_INDEX_1,
	पूर्ण,
	अणु
		.width = 2112,
		.height = 1188,
		.vts_def = OV13858_VTS_30FPS,
		.vts_min = 1608,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_2112x1188_regs),
			.regs = mode_2112x1188_regs,
		पूर्ण,
		.link_freq_index = OV13858_LINK_FREQ_INDEX_1,
	पूर्ण,
	अणु
		.width = 1056,
		.height = 784,
		.vts_def = OV13858_VTS_30FPS,
		.vts_min = 804,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1056x784_regs),
			.regs = mode_1056x784_regs,
		पूर्ण,
		.link_freq_index = OV13858_LINK_FREQ_INDEX_1,
	पूर्ण
पूर्ण;

काष्ठा ov13858 अणु
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
	स्थिर काष्ठा ov13858_mode *cur_mode;

	/* Mutex क्रम serialized access */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;
पूर्ण;

#घोषणा to_ov13858(_sd)	container_of(_sd, काष्ठा ov13858, sd)

/* Read रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक ov13858_पढ़ो_reg(काष्ठा ov13858 *ov13858, u16 reg, u32 len,
			    u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	काष्ठा i2c_msg msgs[2];
	u8 *data_be_p;
	पूर्णांक ret;
	__be32 data_be = 0;
	__be16 reg_addr_be = cpu_to_be16(reg);

	अगर (len > 4)
		वापस -EINVAL;

	data_be_p = (u8 *)&data_be;
	/* Write रेजिस्टर address */
	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = 2;
	msgs[0].buf = (u8 *)&reg_addr_be;

	/* Read data from रेजिस्टर */
	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = &data_be_p[4 - len];

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs))
		वापस -EIO;

	*val = be32_to_cpu(data_be);

	वापस 0;
पूर्ण

/* Write रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक ov13858_ग_लिखो_reg(काष्ठा ov13858 *ov13858, u16 reg, u32 len,
			     u32 __val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	पूर्णांक buf_i, val_i;
	u8 buf[6], *val_p;
	__be32 val;

	अगर (len > 4)
		वापस -EINVAL;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	val = cpu_to_be32(__val);
	val_p = (u8 *)&val;
	buf_i = 2;
	val_i = 4 - len;

	जबतक (val_i < 4)
		buf[buf_i++] = val_p[val_i++];

	अगर (i2c_master_send(client, buf, len + 2) != len + 2)
		वापस -EIO;

	वापस 0;
पूर्ण

/* Write a list of रेजिस्टरs */
अटल पूर्णांक ov13858_ग_लिखो_regs(काष्ठा ov13858 *ov13858,
			      स्थिर काष्ठा ov13858_reg *regs, u32 len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	पूर्णांक ret;
	u32 i;

	क्रम (i = 0; i < len; i++) अणु
		ret = ov13858_ग_लिखो_reg(ov13858, regs[i].address, 1,
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

अटल पूर्णांक ov13858_ग_लिखो_reg_list(काष्ठा ov13858 *ov13858,
				  स्थिर काष्ठा ov13858_reg_list *r_list)
अणु
	वापस ov13858_ग_लिखो_regs(ov13858, r_list->regs, r_list->num_of_regs);
पूर्ण

/* Open sub-device */
अटल पूर्णांक ov13858_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov13858 *ov13858 = to_ov13858(sd);
	काष्ठा v4l2_mbus_framefmt *try_fmt = v4l2_subdev_get_try_क्रमmat(sd,
									fh->pad,
									0);

	mutex_lock(&ov13858->mutex);

	/* Initialize try_fmt */
	try_fmt->width = ov13858->cur_mode->width;
	try_fmt->height = ov13858->cur_mode->height;
	try_fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	try_fmt->field = V4L2_FIELD_NONE;

	/* No crop or compose */
	mutex_unlock(&ov13858->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov13858_update_digital_gain(काष्ठा ov13858 *ov13858, u32 d_gain)
अणु
	पूर्णांक ret;

	ret = ov13858_ग_लिखो_reg(ov13858, OV13858_REG_B_MWB_GAIN,
				OV13858_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	ret = ov13858_ग_लिखो_reg(ov13858, OV13858_REG_G_MWB_GAIN,
				OV13858_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	ret = ov13858_ग_लिखो_reg(ov13858, OV13858_REG_R_MWB_GAIN,
				OV13858_REG_VALUE_16BIT, d_gain);

	वापस ret;
पूर्ण

अटल पूर्णांक ov13858_enable_test_pattern(काष्ठा ov13858 *ov13858, u32 pattern)
अणु
	पूर्णांक ret;
	u32 val;

	ret = ov13858_पढ़ो_reg(ov13858, OV13858_REG_TEST_PATTERN,
			       OV13858_REG_VALUE_08BIT, &val);
	अगर (ret)
		वापस ret;

	अगर (pattern) अणु
		val &= OV13858_TEST_PATTERN_MASK;
		val |= (pattern - 1) | OV13858_TEST_PATTERN_ENABLE;
	पूर्ण अन्यथा अणु
		val &= ~OV13858_TEST_PATTERN_ENABLE;
	पूर्ण

	वापस ov13858_ग_लिखो_reg(ov13858, OV13858_REG_TEST_PATTERN,
				 OV13858_REG_VALUE_08BIT, val);
पूर्ण

अटल पूर्णांक ov13858_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov13858 *ov13858 = container_of(ctrl->handler,
					       काष्ठा ov13858, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	s64 max;
	पूर्णांक ret;

	/* Propagate change of current control to all related controls */
	चयन (ctrl->id) अणु
	हाल V4L2_CID_VBLANK:
		/* Update max exposure जबतक meeting expected vblanking */
		max = ov13858->cur_mode->height + ctrl->val - 8;
		__v4l2_ctrl_modअगरy_range(ov13858->exposure,
					 ov13858->exposure->minimum,
					 max, ov13858->exposure->step, max);
		अवरोध;
	पूर्ण

	/*
	 * Applying V4L2 control value only happens
	 * when घातer is up क्रम streaming
	 */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	ret = 0;
	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov13858_ग_लिखो_reg(ov13858, OV13858_REG_ANALOG_GAIN,
					OV13858_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_DIGITAL_GAIN:
		ret = ov13858_update_digital_gain(ov13858, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		ret = ov13858_ग_लिखो_reg(ov13858, OV13858_REG_EXPOSURE,
					OV13858_REG_VALUE_24BIT,
					ctrl->val << 4);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		/* Update VTS that meets expected vertical blanking */
		ret = ov13858_ग_लिखो_reg(ov13858, OV13858_REG_VTS,
					OV13858_REG_VALUE_16BIT,
					ov13858->cur_mode->height
					  + ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = ov13858_enable_test_pattern(ov13858, ctrl->val);
		अवरोध;
	शेष:
		dev_info(&client->dev,
			 "ctrl(id:0x%x,val:0x%x) is not handled\n",
			 ctrl->id, ctrl->val);
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov13858_ctrl_ops = अणु
	.s_ctrl = ov13858_set_ctrl,
पूर्ण;

अटल पूर्णांक ov13858_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	/* Only one bayer order(GRBG) is supported */
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov13858_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
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

अटल व्योम ov13858_update_pad_क्रमmat(स्थिर काष्ठा ov13858_mode *mode,
				      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	fmt->क्रमmat.width = mode->width;
	fmt->क्रमmat.height = mode->height;
	fmt->क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov13858_करो_get_pad_क्रमmat(काष्ठा ov13858 *ov13858,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *framefmt;
	काष्ठा v4l2_subdev *sd = &ov13858->sd;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		fmt->क्रमmat = *framefmt;
	पूर्ण अन्यथा अणु
		ov13858_update_pad_क्रमmat(ov13858->cur_mode, fmt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov13858_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov13858 *ov13858 = to_ov13858(sd);
	पूर्णांक ret;

	mutex_lock(&ov13858->mutex);
	ret = ov13858_करो_get_pad_क्रमmat(ov13858, cfg, fmt);
	mutex_unlock(&ov13858->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
ov13858_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov13858 *ov13858 = to_ov13858(sd);
	स्थिर काष्ठा ov13858_mode *mode;
	काष्ठा v4l2_mbus_framefmt *framefmt;
	s32 vblank_def;
	s32 vblank_min;
	s64 h_blank;
	s64 pixel_rate;
	s64 link_freq;

	mutex_lock(&ov13858->mutex);

	/* Only one raw bayer(GRBG) order is supported */
	अगर (fmt->क्रमmat.code != MEDIA_BUS_FMT_SGRBG10_1X10)
		fmt->क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes),
				      width, height,
				      fmt->क्रमmat.width, fmt->क्रमmat.height);
	ov13858_update_pad_क्रमmat(mode, fmt);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		*framefmt = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		ov13858->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(ov13858->link_freq, mode->link_freq_index);
		link_freq = link_freq_menu_items[mode->link_freq_index];
		pixel_rate = link_freq_to_pixel_rate(link_freq);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(ov13858->pixel_rate, pixel_rate);

		/* Update limits and set FPS to शेष */
		vblank_def = ov13858->cur_mode->vts_def -
			     ov13858->cur_mode->height;
		vblank_min = ov13858->cur_mode->vts_min -
			     ov13858->cur_mode->height;
		__v4l2_ctrl_modअगरy_range(
			ov13858->vblank, vblank_min,
			OV13858_VTS_MAX - ov13858->cur_mode->height, 1,
			vblank_def);
		__v4l2_ctrl_s_ctrl(ov13858->vblank, vblank_def);
		h_blank =
			link_freq_configs[mode->link_freq_index].pixels_per_line
			 - ov13858->cur_mode->width;
		__v4l2_ctrl_modअगरy_range(ov13858->hblank, h_blank,
					 h_blank, 1, h_blank);
	पूर्ण

	mutex_unlock(&ov13858->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov13858_get_skip_frames(काष्ठा v4l2_subdev *sd, u32 *frames)
अणु
	*frames = OV13858_NUM_OF_SKIP_FRAMES;

	वापस 0;
पूर्ण

/* Start streaming */
अटल पूर्णांक ov13858_start_streaming(काष्ठा ov13858 *ov13858)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	स्थिर काष्ठा ov13858_reg_list *reg_list;
	पूर्णांक ret, link_freq_index;

	/* Get out of from software reset */
	ret = ov13858_ग_लिखो_reg(ov13858, OV13858_REG_SOFTWARE_RST,
				OV13858_REG_VALUE_08BIT, OV13858_SOFTWARE_RST);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set powerup registers\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Setup PLL */
	link_freq_index = ov13858->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = ov13858_ग_लिखो_reg_list(ov13858, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set plls\n", __func__);
		वापस ret;
	पूर्ण

	/* Apply शेष values of current mode */
	reg_list = &ov13858->cur_mode->reg_list;
	ret = ov13858_ग_लिखो_reg_list(ov13858, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed to set mode\n", __func__);
		वापस ret;
	पूर्ण

	/* Apply customized values from user */
	ret =  __v4l2_ctrl_handler_setup(ov13858->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	वापस ov13858_ग_लिखो_reg(ov13858, OV13858_REG_MODE_SELECT,
				 OV13858_REG_VALUE_08BIT,
				 OV13858_MODE_STREAMING);
पूर्ण

/* Stop streaming */
अटल पूर्णांक ov13858_stop_streaming(काष्ठा ov13858 *ov13858)
अणु
	वापस ov13858_ग_लिखो_reg(ov13858, OV13858_REG_MODE_SELECT,
				 OV13858_REG_VALUE_08BIT, OV13858_MODE_STANDBY);
पूर्ण

अटल पूर्णांक ov13858_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov13858 *ov13858 = to_ov13858(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov13858->mutex);
	अगर (ov13858->streaming == enable) अणु
		mutex_unlock(&ov13858->mutex);
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
		ret = ov13858_start_streaming(ov13858);
		अगर (ret)
			जाओ err_rpm_put;
	पूर्ण अन्यथा अणु
		ov13858_stop_streaming(ov13858);
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov13858->streaming = enable;
	mutex_unlock(&ov13858->mutex);

	वापस ret;

err_rpm_put:
	pm_runसमय_put(&client->dev);
err_unlock:
	mutex_unlock(&ov13858->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ov13858_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov13858 *ov13858 = to_ov13858(sd);

	अगर (ov13858->streaming)
		ov13858_stop_streaming(ov13858);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov13858_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov13858 *ov13858 = to_ov13858(sd);
	पूर्णांक ret;

	अगर (ov13858->streaming) अणु
		ret = ov13858_start_streaming(ov13858);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	ov13858_stop_streaming(ov13858);
	ov13858->streaming = false;
	वापस ret;
पूर्ण

/* Verअगरy chip ID */
अटल पूर्णांक ov13858_identअगरy_module(काष्ठा ov13858 *ov13858)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	पूर्णांक ret;
	u32 val;

	ret = ov13858_पढ़ो_reg(ov13858, OV13858_REG_CHIP_ID,
			       OV13858_REG_VALUE_24BIT, &val);
	अगर (ret)
		वापस ret;

	अगर (val != OV13858_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x\n",
			OV13858_CHIP_ID, val);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov13858_video_ops = अणु
	.s_stream = ov13858_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov13858_pad_ops = अणु
	.क्रमागत_mbus_code = ov13858_क्रमागत_mbus_code,
	.get_fmt = ov13858_get_pad_क्रमmat,
	.set_fmt = ov13858_set_pad_क्रमmat,
	.क्रमागत_frame_size = ov13858_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops ov13858_sensor_ops = अणु
	.g_skip_frames = ov13858_get_skip_frames,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov13858_subdev_ops = अणु
	.video = &ov13858_video_ops,
	.pad = &ov13858_pad_ops,
	.sensor = &ov13858_sensor_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ov13858_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov13858_पूर्णांकernal_ops = अणु
	.खोलो = ov13858_खोलो,
पूर्ण;

/* Initialize control handlers */
अटल पूर्णांक ov13858_init_controls(काष्ठा ov13858 *ov13858)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	काष्ठा v4l2_fwnode_device_properties props;
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	s64 exposure_max;
	s64 vblank_def;
	s64 vblank_min;
	s64 hblank;
	s64 pixel_rate_min;
	s64 pixel_rate_max;
	स्थिर काष्ठा ov13858_mode *mode;
	पूर्णांक ret;

	ctrl_hdlr = &ov13858->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 10);
	अगर (ret)
		वापस ret;

	mutex_init(&ov13858->mutex);
	ctrl_hdlr->lock = &ov13858->mutex;
	ov13858->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr,
				&ov13858_ctrl_ops,
				V4L2_CID_LINK_FREQ,
				OV13858_NUM_OF_LINK_FREQS - 1,
				0,
				link_freq_menu_items);
	अगर (ov13858->link_freq)
		ov13858->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	pixel_rate_max = link_freq_to_pixel_rate(link_freq_menu_items[0]);
	pixel_rate_min = link_freq_to_pixel_rate(link_freq_menu_items[1]);
	/* By शेष, PIXEL_RATE is पढ़ो only */
	ov13858->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &ov13858_ctrl_ops,
						V4L2_CID_PIXEL_RATE,
						pixel_rate_min, pixel_rate_max,
						1, pixel_rate_max);

	mode = ov13858->cur_mode;
	vblank_def = mode->vts_def - mode->height;
	vblank_min = mode->vts_min - mode->height;
	ov13858->vblank = v4l2_ctrl_new_std(
				ctrl_hdlr, &ov13858_ctrl_ops, V4L2_CID_VBLANK,
				vblank_min, OV13858_VTS_MAX - mode->height, 1,
				vblank_def);

	hblank = link_freq_configs[mode->link_freq_index].pixels_per_line -
		 mode->width;
	ov13858->hblank = v4l2_ctrl_new_std(
				ctrl_hdlr, &ov13858_ctrl_ops, V4L2_CID_HBLANK,
				hblank, hblank, 1, hblank);
	अगर (ov13858->hblank)
		ov13858->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	exposure_max = mode->vts_def - 8;
	ov13858->exposure = v4l2_ctrl_new_std(
				ctrl_hdlr, &ov13858_ctrl_ops,
				V4L2_CID_EXPOSURE, OV13858_EXPOSURE_MIN,
				exposure_max, OV13858_EXPOSURE_STEP,
				OV13858_EXPOSURE_DEFAULT);

	v4l2_ctrl_new_std(ctrl_hdlr, &ov13858_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  OV13858_ANA_GAIN_MIN, OV13858_ANA_GAIN_MAX,
			  OV13858_ANA_GAIN_STEP, OV13858_ANA_GAIN_DEFAULT);

	/* Digital gain */
	v4l2_ctrl_new_std(ctrl_hdlr, &ov13858_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  OV13858_DGTL_GAIN_MIN, OV13858_DGTL_GAIN_MAX,
			  OV13858_DGTL_GAIN_STEP, OV13858_DGTL_GAIN_DEFAULT);

	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &ov13858_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov13858_test_pattern_menu) - 1,
				     0, 0, ov13858_test_pattern_menu);
	अगर (ctrl_hdlr->error) अणु
		ret = ctrl_hdlr->error;
		dev_err(&client->dev, "%s control init failed (%d)\n",
			__func__, ret);
		जाओ error;
	पूर्ण

	ret = v4l2_fwnode_device_parse(&client->dev, &props);
	अगर (ret)
		जाओ error;

	ret = v4l2_ctrl_new_fwnode_properties(ctrl_hdlr, &ov13858_ctrl_ops,
					      &props);
	अगर (ret)
		जाओ error;

	ov13858->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(ctrl_hdlr);
	mutex_destroy(&ov13858->mutex);

	वापस ret;
पूर्ण

अटल व्योम ov13858_मुक्त_controls(काष्ठा ov13858 *ov13858)
अणु
	v4l2_ctrl_handler_मुक्त(ov13858->sd.ctrl_handler);
	mutex_destroy(&ov13858->mutex);
पूर्ण

अटल पूर्णांक ov13858_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *devid)
अणु
	काष्ठा ov13858 *ov13858;
	पूर्णांक ret;
	u32 val = 0;

	device_property_पढ़ो_u32(&client->dev, "clock-frequency", &val);
	अगर (val != 19200000)
		वापस -EINVAL;

	ov13858 = devm_kzalloc(&client->dev, माप(*ov13858), GFP_KERNEL);
	अगर (!ov13858)
		वापस -ENOMEM;

	/* Initialize subdev */
	v4l2_i2c_subdev_init(&ov13858->sd, client, &ov13858_subdev_ops);

	/* Check module identity */
	ret = ov13858_identअगरy_module(ov13858);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to find sensor: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set शेष mode to max resolution */
	ov13858->cur_mode = &supported_modes[0];

	ret = ov13858_init_controls(ov13858);
	अगर (ret)
		वापस ret;

	/* Initialize subdev */
	ov13858->sd.पूर्णांकernal_ops = &ov13858_पूर्णांकernal_ops;
	ov13858->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov13858->sd.entity.ops = &ov13858_subdev_entity_ops;
	ov13858->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	/* Initialize source pad */
	ov13858->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&ov13858->sd.entity, 1, &ov13858->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "%s failed:%d\n", __func__, ret);
		जाओ error_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&ov13858->sd);
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
	media_entity_cleanup(&ov13858->sd.entity);

error_handler_मुक्त:
	ov13858_मुक्त_controls(ov13858);
	dev_err(&client->dev, "%s failed:%d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ov13858_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov13858 *ov13858 = to_ov13858(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	ov13858_मुक्त_controls(ov13858);

	pm_runसमय_disable(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov13858_id_table[] = अणु
	अणु"ov13858", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ov13858_id_table);

अटल स्थिर काष्ठा dev_pm_ops ov13858_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ov13858_suspend, ov13858_resume)
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id ov13858_acpi_ids[] = अणु
	अणु"OVTID858"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, ov13858_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov13858_i2c_driver = अणु
	.driver = अणु
		.name = "ov13858",
		.pm = &ov13858_pm_ops,
		.acpi_match_table = ACPI_PTR(ov13858_acpi_ids),
	पूर्ण,
	.probe = ov13858_probe,
	.हटाओ = ov13858_हटाओ,
	.id_table = ov13858_id_table,
पूर्ण;

module_i2c_driver(ov13858_i2c_driver);

MODULE_AUTHOR("Kan, Chris <chris.kan@intel.com>");
MODULE_AUTHOR("Rapolu, Chiranjeevi <chiranjeevi.rapolu@intel.com>");
MODULE_AUTHOR("Yang, Hyungwoo <hyungwoo.yang@intel.com>");
MODULE_DESCRIPTION("Omnivision ov13858 sensor driver");
MODULE_LICENSE("GPL v2");
