<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Intel Corporation.

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#घोषणा OV5675_REG_VALUE_08BIT		1
#घोषणा OV5675_REG_VALUE_16BIT		2
#घोषणा OV5675_REG_VALUE_24BIT		3

#घोषणा OV5675_LINK_FREQ_450MHZ		450000000ULL
#घोषणा OV5675_SCLK			90000000LL
#घोषणा OV5675_MCLK			19200000
#घोषणा OV5675_DATA_LANES		2
#घोषणा OV5675_RGB_DEPTH		10

#घोषणा OV5675_REG_CHIP_ID		0x300a
#घोषणा OV5675_CHIP_ID			0x5675

#घोषणा OV5675_REG_MODE_SELECT		0x0100
#घोषणा OV5675_MODE_STANDBY		0x00
#घोषणा OV5675_MODE_STREAMING		0x01

/* vertical-timings from sensor */
#घोषणा OV5675_REG_VTS			0x380e
#घोषणा OV5675_VTS_30FPS		0x07e4
#घोषणा OV5675_VTS_30FPS_MIN		0x07e4
#घोषणा OV5675_VTS_MAX			0x7fff

/* horizontal-timings from sensor */
#घोषणा OV5675_REG_HTS			0x380c

/* Exposure controls from sensor */
#घोषणा OV5675_REG_EXPOSURE		0x3500
#घोषणा	OV5675_EXPOSURE_MIN		4
#घोषणा OV5675_EXPOSURE_MAX_MARGIN	4
#घोषणा	OV5675_EXPOSURE_STEP		1

/* Analog gain controls from sensor */
#घोषणा OV5675_REG_ANALOG_GAIN		0x3508
#घोषणा	OV5675_ANAL_GAIN_MIN		128
#घोषणा	OV5675_ANAL_GAIN_MAX		2047
#घोषणा	OV5675_ANAL_GAIN_STEP		1

/* Digital gain controls from sensor */
#घोषणा OV5675_REG_MWB_R_GAIN		0x5019
#घोषणा OV5675_REG_MWB_G_GAIN		0x501b
#घोषणा OV5675_REG_MWB_B_GAIN		0x501d
#घोषणा OV5675_DGTL_GAIN_MIN		0
#घोषणा OV5675_DGTL_GAIN_MAX		4095
#घोषणा OV5675_DGTL_GAIN_STEP		1
#घोषणा OV5675_DGTL_GAIN_DEFAULT	1024

/* Test Pattern Control */
#घोषणा OV5675_REG_TEST_PATTERN		0x4503
#घोषणा OV5675_TEST_PATTERN_ENABLE	BIT(7)
#घोषणा OV5675_TEST_PATTERN_BAR_SHIFT	2

/* Flip Mirror Controls from sensor */
#घोषणा OV5675_REG_FORMAT1		0x3820
#घोषणा OV5675_REG_FORMAT2		0x373d

#घोषणा to_ov5675(_sd)			container_of(_sd, काष्ठा ov5675, sd)

क्रमागत अणु
	OV5675_LINK_FREQ_900MBPS,
पूर्ण;

काष्ठा ov5675_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा ov5675_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा ov5675_reg *regs;
पूर्ण;

काष्ठा ov5675_link_freq_config अणु
	स्थिर काष्ठा ov5675_reg_list reg_list;
पूर्ण;

काष्ठा ov5675_mode अणु
	/* Frame width in pixels */
	u32 width;

	/* Frame height in pixels */
	u32 height;

	/* Horizontal timining size */
	u32 hts;

	/* Default vertical timining size */
	u32 vts_def;

	/* Min vertical timining size */
	u32 vts_min;

	/* Link frequency needed क्रम this resolution */
	u32 link_freq_index;

	/* Sensor रेजिस्टर settings क्रम this resolution */
	स्थिर काष्ठा ov5675_reg_list reg_list;
पूर्ण;

अटल स्थिर काष्ठा ov5675_reg mipi_data_rate_900mbps[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0100, 0x00पूर्ण,
	अणु0x0300, 0x04पूर्ण,
	अणु0x0302, 0x8dपूर्ण,
	अणु0x0303, 0x00पूर्ण,
	अणु0x030d, 0x26पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov5675_reg mode_2592x1944_regs[] = अणु
	अणु0x3002, 0x21पूर्ण,
	अणु0x3107, 0x23पूर्ण,
	अणु0x3501, 0x20पूर्ण,
	अणु0x3503, 0x0cपूर्ण,
	अणु0x3508, 0x03पूर्ण,
	अणु0x3509, 0x00पूर्ण,
	अणु0x3600, 0x66पूर्ण,
	अणु0x3602, 0x30पूर्ण,
	अणु0x3610, 0xa5पूर्ण,
	अणु0x3612, 0x93पूर्ण,
	अणु0x3620, 0x80पूर्ण,
	अणु0x3642, 0x0eपूर्ण,
	अणु0x3661, 0x00पूर्ण,
	अणु0x3662, 0x10पूर्ण,
	अणु0x3664, 0xf3पूर्ण,
	अणु0x3665, 0x9eपूर्ण,
	अणु0x3667, 0xa5पूर्ण,
	अणु0x366e, 0x55पूर्ण,
	अणु0x366f, 0x55पूर्ण,
	अणु0x3670, 0x11पूर्ण,
	अणु0x3671, 0x11पूर्ण,
	अणु0x3672, 0x11पूर्ण,
	अणु0x3673, 0x11पूर्ण,
	अणु0x3714, 0x24पूर्ण,
	अणु0x371a, 0x3eपूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3734, 0x00पूर्ण,
	अणु0x373d, 0x24पूर्ण,
	अणु0x3764, 0x20पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x3766, 0x12पूर्ण,
	अणु0x37a1, 0x14पूर्ण,
	अणु0x37a8, 0x1cपूर्ण,
	अणु0x37ab, 0x0fपूर्ण,
	अणु0x37c2, 0x04पूर्ण,
	अणु0x37cb, 0x00पूर्ण,
	अणु0x37cc, 0x00पूर्ण,
	अणु0x37cd, 0x00पूर्ण,
	अणु0x37ce, 0x00पूर्ण,
	अणु0x37d8, 0x02पूर्ण,
	अणु0x37d9, 0x08पूर्ण,
	अणु0x37dc, 0x04पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x04पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xb3पूर्ण,
	अणु0x3808, 0x0aपूर्ण,
	अणु0x3809, 0x20पूर्ण,
	अणु0x380a, 0x07पूर्ण,
	अणु0x380b, 0x98पूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xeeपूर्ण,
	अणु0x380e, 0x07पूर्ण,
	अणु0x380f, 0xe4पूर्ण,
	अणु0x3811, 0x10पूर्ण,
	अणु0x3813, 0x0dपूर्ण,
	अणु0x3814, 0x01पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x01पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x381e, 0x02पूर्ण,
	अणु0x3820, 0x88पूर्ण,
	अणु0x3821, 0x01पूर्ण,
	अणु0x3832, 0x04पूर्ण,
	अणु0x3c80, 0x01पूर्ण,
	अणु0x3c82, 0x00पूर्ण,
	अणु0x3c83, 0xc8पूर्ण,
	अणु0x3c8c, 0x0fपूर्ण,
	अणु0x3c8d, 0xa0पूर्ण,
	अणु0x3c90, 0x07पूर्ण,
	अणु0x3c91, 0x00पूर्ण,
	अणु0x3c92, 0x00पूर्ण,
	अणु0x3c93, 0x00पूर्ण,
	अणु0x3c94, 0xd0पूर्ण,
	अणु0x3c95, 0x50पूर्ण,
	अणु0x3c96, 0x35पूर्ण,
	अणु0x3c97, 0x00पूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4008, 0x02पूर्ण,
	अणु0x4009, 0x0dपूर्ण,
	अणु0x400f, 0x80पूर्ण,
	अणु0x4013, 0x02पूर्ण,
	अणु0x4040, 0x00पूर्ण,
	अणु0x4041, 0x07पूर्ण,
	अणु0x404c, 0x50पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4500, 0x06पूर्ण,
	अणु0x4503, 0x00पूर्ण,
	अणु0x450a, 0x04पूर्ण,
	अणु0x4809, 0x04पूर्ण,
	अणु0x480c, 0x12पूर्ण,
	अणु0x4819, 0x70पूर्ण,
	अणु0x4825, 0x32पूर्ण,
	अणु0x4826, 0x32पूर्ण,
	अणु0x482a, 0x06पूर्ण,
	अणु0x4833, 0x08पूर्ण,
	अणु0x4837, 0x0dपूर्ण,
	अणु0x5000, 0x77पूर्ण,
	अणु0x5b00, 0x01पूर्ण,
	अणु0x5b01, 0x10पूर्ण,
	अणु0x5b02, 0x01पूर्ण,
	अणु0x5b03, 0xdbपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e10, 0xfcपूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x3Eपूर्ण,
	अणु0x3502, 0x60पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3508, 0x04पूर्ण,
	अणु0x3509, 0x00पूर्ण,
	अणु0x3832, 0x48पूर्ण,
	अणु0x5780, 0x3eपूर्ण,
	अणु0x5781, 0x0fपूर्ण,
	अणु0x5782, 0x44पूर्ण,
	अणु0x5783, 0x02पूर्ण,
	अणु0x5784, 0x01पूर्ण,
	अणु0x5785, 0x01पूर्ण,
	अणु0x5786, 0x00पूर्ण,
	अणु0x5787, 0x04पूर्ण,
	अणु0x5788, 0x02पूर्ण,
	अणु0x5789, 0x0fपूर्ण,
	अणु0x578a, 0xfdपूर्ण,
	अणु0x578b, 0xf5पूर्ण,
	अणु0x578c, 0xf5पूर्ण,
	अणु0x578d, 0x03पूर्ण,
	अणु0x578e, 0x08पूर्ण,
	अणु0x578f, 0x0cपूर्ण,
	अणु0x5790, 0x08पूर्ण,
	अणु0x5791, 0x06पूर्ण,
	अणु0x5792, 0x00पूर्ण,
	अणु0x5793, 0x52पूर्ण,
	अणु0x5794, 0xa3पूर्ण,
	अणु0x4003, 0x40पूर्ण,
	अणु0x3107, 0x01पूर्ण,
	अणु0x3c80, 0x08पूर्ण,
	अणु0x3c83, 0xb1पूर्ण,
	अणु0x3c8c, 0x10पूर्ण,
	अणु0x3c8d, 0x00पूर्ण,
	अणु0x3c90, 0x00पूर्ण,
	अणु0x3c94, 0x00पूर्ण,
	अणु0x3c95, 0x00पूर्ण,
	अणु0x3c96, 0x00पूर्ण,
	अणु0x37cb, 0x09पूर्ण,
	अणु0x37cc, 0x15पूर्ण,
	अणु0x37cd, 0x1fपूर्ण,
	अणु0x37ce, 0x1fपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov5675_reg mode_1296x972_regs[] = अणु
	अणु0x3002, 0x21पूर्ण,
	अणु0x3107, 0x23पूर्ण,
	अणु0x3501, 0x20पूर्ण,
	अणु0x3503, 0x0cपूर्ण,
	अणु0x3508, 0x03पूर्ण,
	अणु0x3509, 0x00पूर्ण,
	अणु0x3600, 0x66पूर्ण,
	अणु0x3602, 0x30पूर्ण,
	अणु0x3610, 0xa5पूर्ण,
	अणु0x3612, 0x93पूर्ण,
	अणु0x3620, 0x80पूर्ण,
	अणु0x3642, 0x0eपूर्ण,
	अणु0x3661, 0x00पूर्ण,
	अणु0x3662, 0x08पूर्ण,
	अणु0x3664, 0xf3पूर्ण,
	अणु0x3665, 0x9eपूर्ण,
	अणु0x3667, 0xa5पूर्ण,
	अणु0x366e, 0x55पूर्ण,
	अणु0x366f, 0x55पूर्ण,
	अणु0x3670, 0x11पूर्ण,
	अणु0x3671, 0x11पूर्ण,
	अणु0x3672, 0x11पूर्ण,
	अणु0x3673, 0x11पूर्ण,
	अणु0x3714, 0x28पूर्ण,
	अणु0x371a, 0x3eपूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3734, 0x00पूर्ण,
	अणु0x373d, 0x24पूर्ण,
	अणु0x3764, 0x20पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x3766, 0x12पूर्ण,
	अणु0x37a1, 0x14पूर्ण,
	अणु0x37a8, 0x1cपूर्ण,
	अणु0x37ab, 0x0fपूर्ण,
	अणु0x37c2, 0x14पूर्ण,
	अणु0x37cb, 0x00पूर्ण,
	अणु0x37cc, 0x00पूर्ण,
	अणु0x37cd, 0x00पूर्ण,
	अणु0x37ce, 0x00पूर्ण,
	अणु0x37d8, 0x02पूर्ण,
	अणु0x37d9, 0x04पूर्ण,
	अणु0x37dc, 0x04पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xb7पूर्ण,
	अणु0x3808, 0x05पूर्ण,
	अणु0x3809, 0x10पूर्ण,
	अणु0x380a, 0x03पूर्ण,
	अणु0x380b, 0xccपूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xeeपूर्ण,
	अणु0x380e, 0x07पूर्ण,
	अणु0x380f, 0xd0पूर्ण,
	अणु0x3811, 0x08पूर्ण,
	अणु0x3813, 0x0dपूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x03पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x381e, 0x02पूर्ण,
	अणु0x3820, 0x8bपूर्ण,
	अणु0x3821, 0x01पूर्ण,
	अणु0x3832, 0x04पूर्ण,
	अणु0x3c80, 0x01पूर्ण,
	अणु0x3c82, 0x00पूर्ण,
	अणु0x3c83, 0xc8पूर्ण,
	अणु0x3c8c, 0x0fपूर्ण,
	अणु0x3c8d, 0xa0पूर्ण,
	अणु0x3c90, 0x07पूर्ण,
	अणु0x3c91, 0x00पूर्ण,
	अणु0x3c92, 0x00पूर्ण,
	अणु0x3c93, 0x00पूर्ण,
	अणु0x3c94, 0xd0पूर्ण,
	अणु0x3c95, 0x50पूर्ण,
	अणु0x3c96, 0x35पूर्ण,
	अणु0x3c97, 0x00पूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x07पूर्ण,
	अणु0x400f, 0x80पूर्ण,
	अणु0x4013, 0x02पूर्ण,
	अणु0x4040, 0x00पूर्ण,
	अणु0x4041, 0x03पूर्ण,
	अणु0x404c, 0x50पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4500, 0x06पूर्ण,
	अणु0x4503, 0x00पूर्ण,
	अणु0x450a, 0x04पूर्ण,
	अणु0x4809, 0x04पूर्ण,
	अणु0x480c, 0x12पूर्ण,
	अणु0x4819, 0x70पूर्ण,
	अणु0x4825, 0x32पूर्ण,
	अणु0x4826, 0x32पूर्ण,
	अणु0x482a, 0x06पूर्ण,
	अणु0x4833, 0x08पूर्ण,
	अणु0x4837, 0x0dपूर्ण,
	अणु0x5000, 0x77पूर्ण,
	अणु0x5b00, 0x01पूर्ण,
	अणु0x5b01, 0x10पूर्ण,
	अणु0x5b02, 0x01पूर्ण,
	अणु0x5b03, 0xdbपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e10, 0xfcपूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x1Fपूर्ण,
	अणु0x3502, 0x20पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3508, 0x04पूर्ण,
	अणु0x3509, 0x00पूर्ण,
	अणु0x3832, 0x48पूर्ण,
	अणु0x5780, 0x3eपूर्ण,
	अणु0x5781, 0x0fपूर्ण,
	अणु0x5782, 0x44पूर्ण,
	अणु0x5783, 0x02पूर्ण,
	अणु0x5784, 0x01पूर्ण,
	अणु0x5785, 0x01पूर्ण,
	अणु0x5786, 0x00पूर्ण,
	अणु0x5787, 0x04पूर्ण,
	अणु0x5788, 0x02पूर्ण,
	अणु0x5789, 0x0fपूर्ण,
	अणु0x578a, 0xfdपूर्ण,
	अणु0x578b, 0xf5पूर्ण,
	अणु0x578c, 0xf5पूर्ण,
	अणु0x578d, 0x03पूर्ण,
	अणु0x578e, 0x08पूर्ण,
	अणु0x578f, 0x0cपूर्ण,
	अणु0x5790, 0x08पूर्ण,
	अणु0x5791, 0x06पूर्ण,
	अणु0x5792, 0x00पूर्ण,
	अणु0x5793, 0x52पूर्ण,
	अणु0x5794, 0xa3पूर्ण,
	अणु0x4003, 0x40पूर्ण,
	अणु0x3107, 0x01पूर्ण,
	अणु0x3c80, 0x08पूर्ण,
	अणु0x3c83, 0xb1पूर्ण,
	अणु0x3c8c, 0x10पूर्ण,
	अणु0x3c8d, 0x00पूर्ण,
	अणु0x3c90, 0x00पूर्ण,
	अणु0x3c94, 0x00पूर्ण,
	अणु0x3c95, 0x00पूर्ण,
	अणु0x3c96, 0x00पूर्ण,
	अणु0x37cb, 0x09पूर्ण,
	अणु0x37cc, 0x15पूर्ण,
	अणु0x37cd, 0x1fपूर्ण,
	अणु0x37ce, 0x1fपूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov5675_test_pattern_menu[] = अणु
	"Disabled",
	"Standard Color Bar",
	"Top-Bottom Darker Color Bar",
	"Right-Left Darker Color Bar",
	"Bottom-Top Darker Color Bar"
पूर्ण;

अटल स्थिर s64 link_freq_menu_items[] = अणु
	OV5675_LINK_FREQ_450MHZ,
पूर्ण;

अटल स्थिर काष्ठा ov5675_link_freq_config link_freq_configs[] = अणु
	[OV5675_LINK_FREQ_900MBPS] = अणु
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_900mbps),
			.regs = mipi_data_rate_900mbps,
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ov5675_mode supported_modes[] = अणु
	अणु
		.width = 2592,
		.height = 1944,
		.hts = 1500,
		.vts_def = OV5675_VTS_30FPS,
		.vts_min = OV5675_VTS_30FPS_MIN,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_2592x1944_regs),
			.regs = mode_2592x1944_regs,
		पूर्ण,
		.link_freq_index = OV5675_LINK_FREQ_900MBPS,
	पूर्ण,
	अणु
		.width = 1296,
		.height = 972,
		.hts = 1500,
		.vts_def = OV5675_VTS_30FPS,
		.vts_min = OV5675_VTS_30FPS_MIN,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1296x972_regs),
			.regs = mode_1296x972_regs,
		पूर्ण,
		.link_freq_index = OV5675_LINK_FREQ_900MBPS,
	पूर्ण
पूर्ण;

काष्ठा ov5675 अणु
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
	स्थिर काष्ठा ov5675_mode *cur_mode;

	/* To serialize asynchronus callbacks */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;
पूर्ण;

अटल u64 to_pixel_rate(u32 f_index)
अणु
	u64 pixel_rate = link_freq_menu_items[f_index] * 2 * OV5675_DATA_LANES;

	करो_भाग(pixel_rate, OV5675_RGB_DEPTH);

	वापस pixel_rate;
पूर्ण

अटल u64 to_pixels_per_line(u32 hts, u32 f_index)
अणु
	u64 ppl = hts * to_pixel_rate(f_index);

	करो_भाग(ppl, OV5675_SCLK);

	वापस ppl;
पूर्ण

अटल पूर्णांक ov5675_पढ़ो_reg(काष्ठा ov5675 *ov5675, u16 reg, u16 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2];
	u8 data_buf[4] = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, addr_buf);
	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = माप(addr_buf);
	msgs[0].buf = addr_buf;
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

अटल पूर्णांक ov5675_ग_लिखो_reg(काष्ठा ov5675 *ov5675, u16 reg, u16 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	u8 buf[6];

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);
	put_unaligned_be32(val << 8 * (4 - len), buf + 2);
	अगर (i2c_master_send(client, buf, len + 2) != len + 2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_ग_लिखो_reg_list(काष्ठा ov5675 *ov5675,
				 स्थिर काष्ठा ov5675_reg_list *r_list)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < r_list->num_of_regs; i++) अणु
		ret = ov5675_ग_लिखो_reg(ov5675, r_list->regs[i].address, 1,
				       r_list->regs[i].val);
		अगर (ret) अणु
			dev_err_ratelimited(&client->dev,
				    "failed to write reg 0x%4.4x. error = %d",
				    r_list->regs[i].address, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_update_digital_gain(काष्ठा ov5675 *ov5675, u32 d_gain)
अणु
	पूर्णांक ret;

	ret = ov5675_ग_लिखो_reg(ov5675, OV5675_REG_MWB_R_GAIN,
			       OV5675_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	ret = ov5675_ग_लिखो_reg(ov5675, OV5675_REG_MWB_G_GAIN,
			       OV5675_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	वापस ov5675_ग_लिखो_reg(ov5675, OV5675_REG_MWB_B_GAIN,
				OV5675_REG_VALUE_16BIT, d_gain);
पूर्ण

अटल पूर्णांक ov5675_test_pattern(काष्ठा ov5675 *ov5675, u32 pattern)
अणु
	अगर (pattern)
		pattern = (pattern - 1) << OV5675_TEST_PATTERN_BAR_SHIFT |
			  OV5675_TEST_PATTERN_ENABLE;

	वापस ov5675_ग_लिखो_reg(ov5675, OV5675_REG_TEST_PATTERN,
				OV5675_REG_VALUE_08BIT, pattern);
पूर्ण

/*
 * OV5675 supports keeping the pixel order by mirror and flip function
 * The Bayer order isn't affected by the flip controls
 */
अटल पूर्णांक ov5675_set_ctrl_hflip(काष्ठा ov5675 *ov5675, u32 ctrl_val)
अणु
	पूर्णांक ret;
	u32 val;

	ret = ov5675_पढ़ो_reg(ov5675, OV5675_REG_FORMAT1,
			      OV5675_REG_VALUE_08BIT, &val);
	अगर (ret)
		वापस ret;

	वापस ov5675_ग_लिखो_reg(ov5675, OV5675_REG_FORMAT1,
				OV5675_REG_VALUE_08BIT,
				ctrl_val ? val & ~BIT(3) : val | BIT(3));
पूर्ण

अटल पूर्णांक ov5675_set_ctrl_vflip(काष्ठा ov5675 *ov5675, u8 ctrl_val)
अणु
	पूर्णांक ret;
	u32 val;

	ret = ov5675_पढ़ो_reg(ov5675, OV5675_REG_FORMAT1,
			      OV5675_REG_VALUE_08BIT, &val);
	अगर (ret)
		वापस ret;

	ret = ov5675_ग_लिखो_reg(ov5675, OV5675_REG_FORMAT1,
			       OV5675_REG_VALUE_08BIT,
			       ctrl_val ? val | BIT(4) | BIT(5)  : val & ~BIT(4) & ~BIT(5));

	अगर (ret)
		वापस ret;

	ret = ov5675_पढ़ो_reg(ov5675, OV5675_REG_FORMAT2,
			      OV5675_REG_VALUE_08BIT, &val);

	अगर (ret)
		वापस ret;

	वापस ov5675_ग_लिखो_reg(ov5675, OV5675_REG_FORMAT2,
				OV5675_REG_VALUE_08BIT,
				ctrl_val ? val | BIT(1) : val & ~BIT(1));
पूर्ण

अटल पूर्णांक ov5675_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov5675 *ov5675 = container_of(ctrl->handler,
					     काष्ठा ov5675, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	s64 exposure_max;
	पूर्णांक ret = 0;

	/* Propagate change of current control to all related controls */
	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = ov5675->cur_mode->height + ctrl->val -
			OV5675_EXPOSURE_MAX_MARGIN;
		__v4l2_ctrl_modअगरy_range(ov5675->exposure,
					 ov5675->exposure->minimum,
					 exposure_max, ov5675->exposure->step,
					 exposure_max);
	पूर्ण

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov5675_ग_लिखो_reg(ov5675, OV5675_REG_ANALOG_GAIN,
				       OV5675_REG_VALUE_16BIT, ctrl->val);
		अवरोध;

	हाल V4L2_CID_DIGITAL_GAIN:
		ret = ov5675_update_digital_gain(ov5675, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE:
		/* 4 least signअगरicant bits of expsoure are fractional part
		 * val = val << 4
		 * क्रम ov5675, the unit of exposure is dअगरfernt from other
		 * OmniVision sensors, its exposure value is twice of the
		 * रेजिस्टर value, the exposure should be भागided by 2 beक्रमe
		 * set रेजिस्टर, e.g. val << 3.
		 */
		ret = ov5675_ग_लिखो_reg(ov5675, OV5675_REG_EXPOSURE,
				       OV5675_REG_VALUE_24BIT, ctrl->val << 3);
		अवरोध;

	हाल V4L2_CID_VBLANK:
		ret = ov5675_ग_लिखो_reg(ov5675, OV5675_REG_VTS,
				       OV5675_REG_VALUE_16BIT,
				       ov5675->cur_mode->height + ctrl->val +
				       10);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		ret = ov5675_test_pattern(ov5675, ctrl->val);
		अवरोध;

	हाल V4L2_CID_HFLIP:
		ov5675_set_ctrl_hflip(ov5675, ctrl->val);
		अवरोध;

	हाल V4L2_CID_VFLIP:
		ov5675_set_ctrl_vflip(ov5675, ctrl->val);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov5675_ctrl_ops = अणु
	.s_ctrl = ov5675_set_ctrl,
पूर्ण;

अटल पूर्णांक ov5675_init_controls(काष्ठा ov5675 *ov5675)
अणु
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	s64 exposure_max, h_blank;
	पूर्णांक ret;

	ctrl_hdlr = &ov5675->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 8);
	अगर (ret)
		वापस ret;

	ctrl_hdlr->lock = &ov5675->mutex;
	ov5675->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr, &ov5675_ctrl_ops,
					   V4L2_CID_LINK_FREQ,
					   ARRAY_SIZE(link_freq_menu_items) - 1,
					   0, link_freq_menu_items);
	अगर (ov5675->link_freq)
		ov5675->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ov5675->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops,
				       V4L2_CID_PIXEL_RATE, 0,
				       to_pixel_rate(OV5675_LINK_FREQ_900MBPS),
				       1,
				       to_pixel_rate(OV5675_LINK_FREQ_900MBPS));
	ov5675->vblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops,
			  V4L2_CID_VBLANK,
			  ov5675->cur_mode->vts_min - ov5675->cur_mode->height,
			  OV5675_VTS_MAX - ov5675->cur_mode->height, 1,
			  ov5675->cur_mode->vts_def - ov5675->cur_mode->height);
	h_blank = to_pixels_per_line(ov5675->cur_mode->hts,
		  ov5675->cur_mode->link_freq_index) - ov5675->cur_mode->width;
	ov5675->hblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops,
					   V4L2_CID_HBLANK, h_blank, h_blank, 1,
					   h_blank);
	अगर (ov5675->hblank)
		ov5675->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  OV5675_ANAL_GAIN_MIN, OV5675_ANAL_GAIN_MAX,
			  OV5675_ANAL_GAIN_STEP, OV5675_ANAL_GAIN_MIN);
	v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  OV5675_DGTL_GAIN_MIN, OV5675_DGTL_GAIN_MAX,
			  OV5675_DGTL_GAIN_STEP, OV5675_DGTL_GAIN_DEFAULT);
	exposure_max = (ov5675->cur_mode->vts_def - OV5675_EXPOSURE_MAX_MARGIN);
	ov5675->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     OV5675_EXPOSURE_MIN, exposure_max,
					     OV5675_EXPOSURE_STEP,
					     exposure_max);
	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &ov5675_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov5675_test_pattern_menu) - 1,
				     0, 0, ov5675_test_pattern_menu);
	v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(ctrl_hdlr, &ov5675_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);

	अगर (ctrl_hdlr->error)
		वापस ctrl_hdlr->error;

	ov5675->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;
पूर्ण

अटल व्योम ov5675_update_pad_क्रमmat(स्थिर काष्ठा ov5675_mode *mode,
				     काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov5675_start_streaming(काष्ठा ov5675 *ov5675)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	स्थिर काष्ठा ov5675_reg_list *reg_list;
	पूर्णांक link_freq_index, ret;

	link_freq_index = ov5675->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = ov5675_ग_लिखो_reg_list(ov5675, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set plls");
		वापस ret;
	पूर्ण

	reg_list = &ov5675->cur_mode->reg_list;
	ret = ov5675_ग_लिखो_reg_list(ov5675, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set mode");
		वापस ret;
	पूर्ण

	ret = __v4l2_ctrl_handler_setup(ov5675->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	ret = ov5675_ग_लिखो_reg(ov5675, OV5675_REG_MODE_SELECT,
			       OV5675_REG_VALUE_08BIT, OV5675_MODE_STREAMING);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set stream");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ov5675_stop_streaming(काष्ठा ov5675 *ov5675)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);

	अगर (ov5675_ग_लिखो_reg(ov5675, OV5675_REG_MODE_SELECT,
			     OV5675_REG_VALUE_08BIT, OV5675_MODE_STANDBY))
		dev_err(&client->dev, "failed to set stream");
पूर्ण

अटल पूर्णांक ov5675_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov5675 *ov5675 = to_ov5675(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (ov5675->streaming == enable)
		वापस 0;

	mutex_lock(&ov5675->mutex);
	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			mutex_unlock(&ov5675->mutex);
			वापस ret;
		पूर्ण

		ret = ov5675_start_streaming(ov5675);
		अगर (ret) अणु
			enable = 0;
			ov5675_stop_streaming(ov5675);
			pm_runसमय_put(&client->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		ov5675_stop_streaming(ov5675);
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov5675->streaming = enable;
	mutex_unlock(&ov5675->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ov5675_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov5675 *ov5675 = to_ov5675(sd);

	mutex_lock(&ov5675->mutex);
	अगर (ov5675->streaming)
		ov5675_stop_streaming(ov5675);

	mutex_unlock(&ov5675->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov5675_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov5675 *ov5675 = to_ov5675(sd);
	पूर्णांक ret;

	mutex_lock(&ov5675->mutex);
	अगर (ov5675->streaming) अणु
		ret = ov5675_start_streaming(ov5675);
		अगर (ret) अणु
			ov5675->streaming = false;
			ov5675_stop_streaming(ov5675);
			mutex_unlock(&ov5675->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&ov5675->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov5675 *ov5675 = to_ov5675(sd);
	स्थिर काष्ठा ov5675_mode *mode;
	s32 vblank_def, h_blank;

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes), width,
				      height, fmt->क्रमmat.width,
				      fmt->क्रमmat.height);

	mutex_lock(&ov5675->mutex);
	ov5675_update_pad_क्रमmat(mode, &fmt->क्रमmat);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		ov5675->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(ov5675->link_freq, mode->link_freq_index);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(ov5675->pixel_rate,
					 to_pixel_rate(mode->link_freq_index));

		/* Update limits and set FPS to शेष */
		vblank_def = mode->vts_def - mode->height;
		__v4l2_ctrl_modअगरy_range(ov5675->vblank,
					 mode->vts_min - mode->height,
					 OV5675_VTS_MAX - mode->height, 1,
					 vblank_def);
		__v4l2_ctrl_s_ctrl(ov5675->vblank, vblank_def);
		h_blank = to_pixels_per_line(mode->hts, mode->link_freq_index) -
			  mode->width;
		__v4l2_ctrl_modअगरy_range(ov5675->hblank, h_blank, h_blank, 1,
					 h_blank);
	पूर्ण

	mutex_unlock(&ov5675->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov5675 *ov5675 = to_ov5675(sd);

	mutex_lock(&ov5675->mutex);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(&ov5675->sd, cfg,
							  fmt->pad);
	अन्यथा
		ov5675_update_pad_क्रमmat(ov5675->cur_mode, &fmt->क्रमmat);

	mutex_unlock(&ov5675->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
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

अटल पूर्णांक ov5675_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov5675 *ov5675 = to_ov5675(sd);

	mutex_lock(&ov5675->mutex);
	ov5675_update_pad_क्रमmat(&supported_modes[0],
				 v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0));
	mutex_unlock(&ov5675->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov5675_video_ops = अणु
	.s_stream = ov5675_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov5675_pad_ops = अणु
	.set_fmt = ov5675_set_क्रमmat,
	.get_fmt = ov5675_get_क्रमmat,
	.क्रमागत_mbus_code = ov5675_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov5675_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov5675_subdev_ops = अणु
	.video = &ov5675_video_ops,
	.pad = &ov5675_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ov5675_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov5675_पूर्णांकernal_ops = अणु
	.खोलो = ov5675_खोलो,
पूर्ण;

अटल पूर्णांक ov5675_identअगरy_module(काष्ठा ov5675 *ov5675)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov5675->sd);
	पूर्णांक ret;
	u32 val;

	ret = ov5675_पढ़ो_reg(ov5675, OV5675_REG_CHIP_ID,
			      OV5675_REG_VALUE_24BIT, &val);
	अगर (ret)
		वापस ret;

	अगर (val != OV5675_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x",
			OV5675_CHIP_ID, val);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_check_hwcfg(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *ep;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	u32 mclk;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, j;

	अगर (!fwnode)
		वापस -ENXIO;

	ret = fwnode_property_पढ़ो_u32(fwnode, "clock-frequency", &mclk);

	अगर (ret) अणु
		dev_err(dev, "can't get clock frequency");
		वापस ret;
	पूर्ण

	अगर (mclk != OV5675_MCLK) अणु
		dev_err(dev, "external clock %d is not supported", mclk);
		वापस -EINVAL;
	पूर्ण

	ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (!ep)
		वापस -ENXIO;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	अगर (ret)
		वापस ret;

	अगर (bus_cfg.bus.mipi_csi2.num_data_lanes != OV5675_DATA_LANES) अणु
		dev_err(dev, "number of CSI2 data lanes %d is not supported",
			bus_cfg.bus.mipi_csi2.num_data_lanes);
		ret = -EINVAL;
		जाओ check_hwcfg_error;
	पूर्ण

	अगर (!bus_cfg.nr_of_link_frequencies) अणु
		dev_err(dev, "no link frequencies defined");
		ret = -EINVAL;
		जाओ check_hwcfg_error;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(link_freq_menu_items); i++) अणु
		क्रम (j = 0; j < bus_cfg.nr_of_link_frequencies; j++) अणु
			अगर (link_freq_menu_items[i] ==
				bus_cfg.link_frequencies[j])
				अवरोध;
		पूर्ण

		अगर (j == bus_cfg.nr_of_link_frequencies) अणु
			dev_err(dev, "no link frequency %lld supported",
				link_freq_menu_items[i]);
			ret = -EINVAL;
			जाओ check_hwcfg_error;
		पूर्ण
	पूर्ण

check_hwcfg_error:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5675_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov5675 *ov5675 = to_ov5675(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	pm_runसमय_disable(&client->dev);
	mutex_destroy(&ov5675->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5675_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov5675 *ov5675;
	पूर्णांक ret;

	ret = ov5675_check_hwcfg(&client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to check HW configuration: %d",
			ret);
		वापस ret;
	पूर्ण

	ov5675 = devm_kzalloc(&client->dev, माप(*ov5675), GFP_KERNEL);
	अगर (!ov5675)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&ov5675->sd, client, &ov5675_subdev_ops);
	ret = ov5675_identअगरy_module(ov5675);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		वापस ret;
	पूर्ण

	mutex_init(&ov5675->mutex);
	ov5675->cur_mode = &supported_modes[0];
	ret = ov5675_init_controls(ov5675);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init controls: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ov5675->sd.पूर्णांकernal_ops = &ov5675_पूर्णांकernal_ops;
	ov5675->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov5675->sd.entity.ops = &ov5675_subdev_entity_ops;
	ov5675->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ov5675->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&ov5675->sd.entity, 1, &ov5675->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&ov5675->sd);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to register V4L2 subdev: %d",
			ret);
		जाओ probe_error_media_entity_cleanup;
	पूर्ण

	/*
	 * Device is alपढ़ोy turned on by i2c-core with ACPI करोमुख्य PM.
	 * Enable runसमय PM and turn off the device.
	 */
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

probe_error_media_entity_cleanup:
	media_entity_cleanup(&ov5675->sd.entity);

probe_error_v4l2_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(ov5675->sd.ctrl_handler);
	mutex_destroy(&ov5675->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov5675_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ov5675_suspend, ov5675_resume)
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id ov5675_acpi_ids[] = अणु
	अणु"OVTI5675"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, ov5675_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov5675_i2c_driver = अणु
	.driver = अणु
		.name = "ov5675",
		.pm = &ov5675_pm_ops,
		.acpi_match_table = ACPI_PTR(ov5675_acpi_ids),
	पूर्ण,
	.probe_new = ov5675_probe,
	.हटाओ = ov5675_हटाओ,
पूर्ण;

module_i2c_driver(ov5675_i2c_driver);

MODULE_AUTHOR("Shawn Tu <shawnx.tu@intel.com>");
MODULE_DESCRIPTION("OmniVision OV5675 sensor driver");
MODULE_LICENSE("GPL v2");
