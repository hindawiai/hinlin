<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Intel Corporation.

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#घोषणा OV8856_REG_VALUE_08BIT		1
#घोषणा OV8856_REG_VALUE_16BIT		2
#घोषणा OV8856_REG_VALUE_24BIT		3

#घोषणा OV8856_LINK_FREQ_360MHZ		360000000ULL
#घोषणा OV8856_LINK_FREQ_180MHZ		180000000ULL
#घोषणा OV8856_SCLK			144000000ULL
#घोषणा OV8856_XVCLK_19_2		19200000
#घोषणा OV8856_DATA_LANES		4
#घोषणा OV8856_RGB_DEPTH		10

#घोषणा OV8856_REG_CHIP_ID		0x300a
#घोषणा OV8856_CHIP_ID			0x00885a

#घोषणा OV8856_REG_MODE_SELECT		0x0100
#घोषणा OV8856_MODE_STANDBY		0x00
#घोषणा OV8856_MODE_STREAMING		0x01

/* module revisions */
#घोषणा OV8856_2A_MODULE		0x01
#घोषणा OV8856_1B_MODULE		0x02

/* the OTP पढ़ो-out buffer is at 0x7000 and 0xf is the offset
 * of the byte in the OTP that means the module revision
 */
#घोषणा OV8856_MODULE_REVISION		0x700f
#घोषणा OV8856_OTP_MODE_CTRL		0x3d84
#घोषणा OV8856_OTP_LOAD_CTRL		0x3d81
#घोषणा OV8856_OTP_MODE_AUTO		0x00
#घोषणा OV8856_OTP_LOAD_CTRL_ENABLE	BIT(0)

/* vertical-timings from sensor */
#घोषणा OV8856_REG_VTS			0x380e
#घोषणा OV8856_VTS_MAX			0x7fff

/* horizontal-timings from sensor */
#घोषणा OV8856_REG_HTS			0x380c

/* Exposure controls from sensor */
#घोषणा OV8856_REG_EXPOSURE		0x3500
#घोषणा	OV8856_EXPOSURE_MIN		6
#घोषणा OV8856_EXPOSURE_MAX_MARGIN	6
#घोषणा	OV8856_EXPOSURE_STEP		1

/* Analog gain controls from sensor */
#घोषणा OV8856_REG_ANALOG_GAIN		0x3508
#घोषणा	OV8856_ANAL_GAIN_MIN		128
#घोषणा	OV8856_ANAL_GAIN_MAX		2047
#घोषणा	OV8856_ANAL_GAIN_STEP		1

/* Digital gain controls from sensor */
#घोषणा OV8856_REG_MWB_R_GAIN		0x5019
#घोषणा OV8856_REG_MWB_G_GAIN		0x501b
#घोषणा OV8856_REG_MWB_B_GAIN		0x501d
#घोषणा OV8856_DGTL_GAIN_MIN		0
#घोषणा OV8856_DGTL_GAIN_MAX		4095
#घोषणा OV8856_DGTL_GAIN_STEP		1
#घोषणा OV8856_DGTL_GAIN_DEFAULT	1024

/* Test Pattern Control */
#घोषणा OV8856_REG_TEST_PATTERN		0x5e00
#घोषणा OV8856_TEST_PATTERN_ENABLE	BIT(7)
#घोषणा OV8856_TEST_PATTERN_BAR_SHIFT	2

#घोषणा to_ov8856(_sd)			container_of(_sd, काष्ठा ov8856, sd)

अटल स्थिर अक्षर * स्थिर ov8856_supply_names[] = अणु
	"dovdd",	/* Digital I/O घातer */
	"avdd",		/* Analog घातer */
	"dvdd",		/* Digital core घातer */
पूर्ण;

क्रमागत अणु
	OV8856_LINK_FREQ_720MBPS,
	OV8856_LINK_FREQ_360MBPS,
पूर्ण;

काष्ठा ov8856_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा ov8856_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा ov8856_reg *regs;
पूर्ण;

काष्ठा ov8856_link_freq_config अणु
	स्थिर काष्ठा ov8856_reg_list reg_list;
पूर्ण;

काष्ठा ov8856_mode अणु
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
	स्थिर काष्ठा ov8856_reg_list reg_list;
पूर्ण;

अटल स्थिर काष्ठा ov8856_reg mipi_data_rate_720mbps[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0100, 0x00पूर्ण,
	अणु0x0302, 0x4bपूर्ण,
	अणु0x0303, 0x01पूर्ण,
	अणु0x030b, 0x02पूर्ण,
	अणु0x030d, 0x4bपूर्ण,
	अणु0x031e, 0x0cपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov8856_reg mipi_data_rate_360mbps[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0100, 0x00पूर्ण,
	अणु0x0302, 0x4bपूर्ण,
	अणु0x0303, 0x03पूर्ण,
	अणु0x030b, 0x02पूर्ण,
	अणु0x030d, 0x4bपूर्ण,
	अणु0x031e, 0x0cपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov8856_reg mode_3280x2464_regs[] = अणु
	अणु0x3000, 0x20पूर्ण,
	अणु0x3003, 0x08पूर्ण,
	अणु0x300e, 0x20पूर्ण,
	अणु0x3010, 0x00पूर्ण,
	अणु0x3015, 0x84पूर्ण,
	अणु0x3018, 0x72पूर्ण,
	अणु0x3021, 0x23पूर्ण,
	अणु0x3033, 0x24पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x9aपूर्ण,
	अणु0x3502, 0x20पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3505, 0x83पूर्ण,
	अणु0x3508, 0x01पूर्ण,
	अणु0x3509, 0x80पूर्ण,
	अणु0x350c, 0x00पूर्ण,
	अणु0x350d, 0x80पूर्ण,
	अणु0x350e, 0x04पूर्ण,
	अणु0x350f, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x72पूर्ण,
	अणु0x3601, 0x40पूर्ण,
	अणु0x3602, 0x30पूर्ण,
	अणु0x3610, 0xc5पूर्ण,
	अणु0x3611, 0x58पूर्ण,
	अणु0x3612, 0x5cपूर्ण,
	अणु0x3613, 0xcaपूर्ण,
	अणु0x3614, 0x20पूर्ण,
	अणु0x3628, 0xffपूर्ण,
	अणु0x3629, 0xffपूर्ण,
	अणु0x362a, 0xffपूर्ण,
	अणु0x3633, 0x10पूर्ण,
	अणु0x3634, 0x10पूर्ण,
	अणु0x3635, 0x10पूर्ण,
	अणु0x3636, 0x10पूर्ण,
	अणु0x3663, 0x08पूर्ण,
	अणु0x3669, 0x34पूर्ण,
	अणु0x366e, 0x10पूर्ण,
	अणु0x3706, 0x86पूर्ण,
	अणु0x370b, 0x7eपूर्ण,
	अणु0x3714, 0x23पूर्ण,
	अणु0x3730, 0x12पूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3764, 0x00पूर्ण,
	अणु0x3765, 0x00पूर्ण,
	अणु0x3769, 0x62पूर्ण,
	अणु0x376a, 0x2aपूर्ण,
	अणु0x376b, 0x30पूर्ण,
	अणु0x3780, 0x00पूर्ण,
	अणु0x3781, 0x24पूर्ण,
	अणु0x3782, 0x00पूर्ण,
	अणु0x3783, 0x23पूर्ण,
	अणु0x3798, 0x2fपूर्ण,
	अणु0x37a1, 0x60पूर्ण,
	अणु0x37a8, 0x6aपूर्ण,
	अणु0x37ab, 0x3fपूर्ण,
	अणु0x37c2, 0x04पूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c9, 0x80पूर्ण,
	अणु0x37cb, 0x16पूर्ण,
	अणु0x37cc, 0x16पूर्ण,
	अणु0x37cd, 0x16पूर्ण,
	अणु0x37ce, 0x16पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x06पूर्ण,
	अणु0x3804, 0x0cपूर्ण,
	अणु0x3805, 0xdfपूर्ण,
	अणु0x3806, 0x09पूर्ण,
	अणु0x3807, 0xa7पूर्ण,
	अणु0x3808, 0x0cपूर्ण,
	अणु0x3809, 0xd0पूर्ण,
	अणु0x380a, 0x09पूर्ण,
	अणु0x380b, 0xa0पूर्ण,
	अणु0x380c, 0x07पूर्ण,
	अणु0x380d, 0x88पूर्ण,
	अणु0x380e, 0x09पूर्ण,
	अणु0x380f, 0xb8पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x00पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x01पूर्ण,
	अणु0x3814, 0x01पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x00पूर्ण,
	अणु0x3817, 0x00पूर्ण,
	अणु0x3818, 0x00पूर्ण,
	अणु0x3819, 0x10पूर्ण,
	अणु0x3820, 0x80पूर्ण,
	अणु0x3821, 0x46पूर्ण,
	अणु0x382a, 0x01पूर्ण,
	अणु0x382b, 0x01पूर्ण,
	अणु0x3830, 0x06पूर्ण,
	अणु0x3836, 0x02पूर्ण,
	अणु0x3862, 0x04पूर्ण,
	अणु0x3863, 0x08पूर्ण,
	अणु0x3cc0, 0x33पूर्ण,
	अणु0x3d85, 0x17पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xdeपूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4003, 0x40पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x0bपूर्ण,
	अणु0x400a, 0x00पूर्ण,
	अणु0x400b, 0x84पूर्ण,
	अणु0x400f, 0x80पूर्ण,
	अणु0x4010, 0xf0पूर्ण,
	अणु0x4011, 0xffपूर्ण,
	अणु0x4012, 0x02पूर्ण,
	अणु0x4013, 0x01पूर्ण,
	अणु0x4014, 0x01पूर्ण,
	अणु0x4015, 0x01पूर्ण,
	अणु0x4042, 0x00पूर्ण,
	अणु0x4043, 0x80पूर्ण,
	अणु0x4044, 0x00पूर्ण,
	अणु0x4045, 0x80पूर्ण,
	अणु0x4046, 0x00पूर्ण,
	अणु0x4047, 0x80पूर्ण,
	अणु0x4048, 0x00पूर्ण,
	अणु0x4049, 0x80पूर्ण,
	अणु0x4041, 0x03पूर्ण,
	अणु0x404c, 0x20पूर्ण,
	अणु0x404d, 0x00पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4203, 0x80पूर्ण,
	अणु0x4307, 0x30पूर्ण,
	अणु0x4317, 0x00पूर्ण,
	अणु0x4503, 0x08पूर्ण,
	अणु0x4601, 0x80पूर्ण,
	अणु0x4800, 0x44पूर्ण,
	अणु0x4816, 0x53पूर्ण,
	अणु0x481b, 0x58पूर्ण,
	अणु0x481f, 0x27पूर्ण,
	अणु0x4837, 0x16पूर्ण,
	अणु0x483c, 0x0fपूर्ण,
	अणु0x484b, 0x05पूर्ण,
	अणु0x5000, 0x57पूर्ण,
	अणु0x5001, 0x0aपूर्ण,
	अणु0x5004, 0x04पूर्ण,
	अणु0x502e, 0x03पूर्ण,
	अणु0x5030, 0x41पूर्ण,
	अणु0x5780, 0x14पूर्ण,
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
	अणु0x5791, 0x04पूर्ण,
	अणु0x5792, 0x00पूर्ण,
	अणु0x5793, 0x52पूर्ण,
	अणु0x5794, 0xa3पूर्ण,
	अणु0x5795, 0x02पूर्ण,
	अणु0x5796, 0x20पूर्ण,
	अणु0x5797, 0x20पूर्ण,
	अणु0x5798, 0xd5पूर्ण,
	अणु0x5799, 0xd5पूर्ण,
	अणु0x579a, 0x00पूर्ण,
	अणु0x579b, 0x50पूर्ण,
	अणु0x579c, 0x00पूर्ण,
	अणु0x579d, 0x2cपूर्ण,
	अणु0x579e, 0x0cपूर्ण,
	अणु0x579f, 0x40पूर्ण,
	अणु0x57a0, 0x09पूर्ण,
	अणु0x57a1, 0x40पूर्ण,
	अणु0x59f8, 0x3dपूर्ण,
	अणु0x5a08, 0x02पूर्ण,
	अणु0x5b00, 0x02पूर्ण,
	अणु0x5b01, 0x10पूर्ण,
	अणु0x5b02, 0x03पूर्ण,
	अणु0x5b03, 0xcfपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e00, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ov8856_reg mode_3264x2448_regs[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0302, 0x3cपूर्ण,
	अणु0x0303, 0x01पूर्ण,
	अणु0x031e, 0x0cपूर्ण,
	अणु0x3000, 0x20पूर्ण,
	अणु0x3003, 0x08पूर्ण,
	अणु0x300e, 0x20पूर्ण,
	अणु0x3010, 0x00पूर्ण,
	अणु0x3015, 0x84पूर्ण,
	अणु0x3018, 0x72पूर्ण,
	अणु0x3021, 0x23पूर्ण,
	अणु0x3033, 0x24पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x9aपूर्ण,
	अणु0x3502, 0x20पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3505, 0x83पूर्ण,
	अणु0x3508, 0x01पूर्ण,
	अणु0x3509, 0x80पूर्ण,
	अणु0x350c, 0x00पूर्ण,
	अणु0x350d, 0x80पूर्ण,
	अणु0x350e, 0x04पूर्ण,
	अणु0x350f, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x72पूर्ण,
	अणु0x3601, 0x40पूर्ण,
	अणु0x3602, 0x30पूर्ण,
	अणु0x3610, 0xc5पूर्ण,
	अणु0x3611, 0x58पूर्ण,
	अणु0x3612, 0x5cपूर्ण,
	अणु0x3613, 0xcaपूर्ण,
	अणु0x3614, 0x60पूर्ण,
	अणु0x3628, 0xffपूर्ण,
	अणु0x3629, 0xffपूर्ण,
	अणु0x362a, 0xffपूर्ण,
	अणु0x3633, 0x10पूर्ण,
	अणु0x3634, 0x10पूर्ण,
	अणु0x3635, 0x10पूर्ण,
	अणु0x3636, 0x10पूर्ण,
	अणु0x3663, 0x08पूर्ण,
	अणु0x3669, 0x34पूर्ण,
	अणु0x366d, 0x00पूर्ण,
	अणु0x366e, 0x10पूर्ण,
	अणु0x3706, 0x86पूर्ण,
	अणु0x370b, 0x7eपूर्ण,
	अणु0x3714, 0x23पूर्ण,
	अणु0x3730, 0x12पूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3764, 0x00पूर्ण,
	अणु0x3765, 0x00पूर्ण,
	अणु0x3769, 0x62पूर्ण,
	अणु0x376a, 0x2aपूर्ण,
	अणु0x376b, 0x30पूर्ण,
	अणु0x3780, 0x00पूर्ण,
	अणु0x3781, 0x24पूर्ण,
	अणु0x3782, 0x00पूर्ण,
	अणु0x3783, 0x23पूर्ण,
	अणु0x3798, 0x2fपूर्ण,
	अणु0x37a1, 0x60पूर्ण,
	अणु0x37a8, 0x6aपूर्ण,
	अणु0x37ab, 0x3fपूर्ण,
	अणु0x37c2, 0x04पूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c9, 0x80पूर्ण,
	अणु0x37cb, 0x16पूर्ण,
	अणु0x37cc, 0x16पूर्ण,
	अणु0x37cd, 0x16पूर्ण,
	अणु0x37ce, 0x16पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x0cपूर्ण,
	अणु0x3804, 0x0cपूर्ण,
	अणु0x3805, 0xdfपूर्ण,
	अणु0x3806, 0x09पूर्ण,
	अणु0x3807, 0xa3पूर्ण,
	अणु0x3808, 0x0cपूर्ण,
	अणु0x3809, 0xc0पूर्ण,
	अणु0x380a, 0x09पूर्ण,
	अणु0x380b, 0x90पूर्ण,
	अणु0x380c, 0x07पूर्ण,
	अणु0x380d, 0x8cपूर्ण,
	अणु0x380e, 0x09पूर्ण,
	अणु0x380f, 0xb2पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x04पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x01पूर्ण,
	अणु0x3814, 0x01पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x00पूर्ण,
	अणु0x3817, 0x00पूर्ण,
	अणु0x3818, 0x00पूर्ण,
	अणु0x3819, 0x10पूर्ण,
	अणु0x3820, 0x80पूर्ण,
	अणु0x3821, 0x46पूर्ण,
	अणु0x382a, 0x01पूर्ण,
	अणु0x382b, 0x01पूर्ण,
	अणु0x3830, 0x06पूर्ण,
	अणु0x3836, 0x02पूर्ण,
	अणु0x3862, 0x04पूर्ण,
	अणु0x3863, 0x08पूर्ण,
	अणु0x3cc0, 0x33पूर्ण,
	अणु0x3d85, 0x17पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xdeपूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4003, 0x40पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x0bपूर्ण,
	अणु0x400a, 0x00पूर्ण,
	अणु0x400b, 0x84पूर्ण,
	अणु0x400f, 0x80पूर्ण,
	अणु0x4010, 0xf0पूर्ण,
	अणु0x4011, 0xffपूर्ण,
	अणु0x4012, 0x02पूर्ण,
	अणु0x4013, 0x01पूर्ण,
	अणु0x4014, 0x01पूर्ण,
	अणु0x4015, 0x01पूर्ण,
	अणु0x4042, 0x00पूर्ण,
	अणु0x4043, 0x80पूर्ण,
	अणु0x4044, 0x00पूर्ण,
	अणु0x4045, 0x80पूर्ण,
	अणु0x4046, 0x00पूर्ण,
	अणु0x4047, 0x80पूर्ण,
	अणु0x4048, 0x00पूर्ण,
	अणु0x4049, 0x80पूर्ण,
	अणु0x4041, 0x03पूर्ण,
	अणु0x404c, 0x20पूर्ण,
	अणु0x404d, 0x00पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4203, 0x80पूर्ण,
	अणु0x4307, 0x30पूर्ण,
	अणु0x4317, 0x00पूर्ण,
	अणु0x4502, 0x50पूर्ण,
	अणु0x4503, 0x08पूर्ण,
	अणु0x4601, 0x80पूर्ण,
	अणु0x4800, 0x44पूर्ण,
	अणु0x4816, 0x53पूर्ण,
	अणु0x481b, 0x50पूर्ण,
	अणु0x481f, 0x27पूर्ण,
	अणु0x4823, 0x3cपूर्ण,
	अणु0x482b, 0x00पूर्ण,
	अणु0x4831, 0x66पूर्ण,
	अणु0x4837, 0x16पूर्ण,
	अणु0x483c, 0x0fपूर्ण,
	अणु0x484b, 0x05पूर्ण,
	अणु0x5000, 0x77पूर्ण,
	अणु0x5001, 0x0aपूर्ण,
	अणु0x5003, 0xc8पूर्ण,
	अणु0x5004, 0x04पूर्ण,
	अणु0x5006, 0x00पूर्ण,
	अणु0x5007, 0x00पूर्ण,
	अणु0x502e, 0x03पूर्ण,
	अणु0x5030, 0x41पूर्ण,
	अणु0x5780, 0x14पूर्ण,
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
	अणु0x5791, 0x04पूर्ण,
	अणु0x5792, 0x00पूर्ण,
	अणु0x5793, 0x52पूर्ण,
	अणु0x5794, 0xa3पूर्ण,
	अणु0x5795, 0x02पूर्ण,
	अणु0x5796, 0x20पूर्ण,
	अणु0x5797, 0x20पूर्ण,
	अणु0x5798, 0xd5पूर्ण,
	अणु0x5799, 0xd5पूर्ण,
	अणु0x579a, 0x00पूर्ण,
	अणु0x579b, 0x50पूर्ण,
	अणु0x579c, 0x00पूर्ण,
	अणु0x579d, 0x2cपूर्ण,
	अणु0x579e, 0x0cपूर्ण,
	अणु0x579f, 0x40पूर्ण,
	अणु0x57a0, 0x09पूर्ण,
	अणु0x57a1, 0x40पूर्ण,
	अणु0x59f8, 0x3dपूर्ण,
	अणु0x5a08, 0x02पूर्ण,
	अणु0x5b00, 0x02पूर्ण,
	अणु0x5b01, 0x10पूर्ण,
	अणु0x5b02, 0x03पूर्ण,
	अणु0x5b03, 0xcfपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e00, 0x00पूर्ण,
	अणु0x5e10, 0xfcपूर्ण
पूर्ण;

अटल स्थिर काष्ठा ov8856_reg mode_1640x1232_regs[] = अणु
	अणु0x3000, 0x20पूर्ण,
	अणु0x3003, 0x08पूर्ण,
	अणु0x300e, 0x20पूर्ण,
	अणु0x3010, 0x00पूर्ण,
	अणु0x3015, 0x84पूर्ण,
	अणु0x3018, 0x72पूर्ण,
	अणु0x3021, 0x23पूर्ण,
	अणु0x3033, 0x24पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x4cपूर्ण,
	अणु0x3502, 0xe0पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3505, 0x83पूर्ण,
	अणु0x3508, 0x01पूर्ण,
	अणु0x3509, 0x80पूर्ण,
	अणु0x350c, 0x00पूर्ण,
	अणु0x350d, 0x80पूर्ण,
	अणु0x350e, 0x04पूर्ण,
	अणु0x350f, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x72पूर्ण,
	अणु0x3601, 0x40पूर्ण,
	अणु0x3602, 0x30पूर्ण,
	अणु0x3610, 0xc5पूर्ण,
	अणु0x3611, 0x58पूर्ण,
	अणु0x3612, 0x5cपूर्ण,
	अणु0x3613, 0xcaपूर्ण,
	अणु0x3614, 0x20पूर्ण,
	अणु0x3628, 0xffपूर्ण,
	अणु0x3629, 0xffपूर्ण,
	अणु0x362a, 0xffपूर्ण,
	अणु0x3633, 0x10पूर्ण,
	अणु0x3634, 0x10पूर्ण,
	अणु0x3635, 0x10पूर्ण,
	अणु0x3636, 0x10पूर्ण,
	अणु0x3663, 0x08पूर्ण,
	अणु0x3669, 0x34पूर्ण,
	अणु0x366e, 0x08पूर्ण,
	अणु0x3706, 0x86पूर्ण,
	अणु0x370b, 0x7eपूर्ण,
	अणु0x3714, 0x27पूर्ण,
	अणु0x3730, 0x12पूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3764, 0x00पूर्ण,
	अणु0x3765, 0x00पूर्ण,
	अणु0x3769, 0x62पूर्ण,
	अणु0x376a, 0x2aपूर्ण,
	अणु0x376b, 0x30पूर्ण,
	अणु0x3780, 0x00पूर्ण,
	अणु0x3781, 0x24पूर्ण,
	अणु0x3782, 0x00पूर्ण,
	अणु0x3783, 0x23पूर्ण,
	अणु0x3798, 0x2fपूर्ण,
	अणु0x37a1, 0x60पूर्ण,
	अणु0x37a8, 0x6aपूर्ण,
	अणु0x37ab, 0x3fपूर्ण,
	अणु0x37c2, 0x14पूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c9, 0x80पूर्ण,
	अणु0x37cb, 0x16पूर्ण,
	अणु0x37cc, 0x16पूर्ण,
	अणु0x37cd, 0x16पूर्ण,
	अणु0x37ce, 0x16पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x06पूर्ण,
	अणु0x3804, 0x0cपूर्ण,
	अणु0x3805, 0xdfपूर्ण,
	अणु0x3806, 0x09पूर्ण,
	अणु0x3807, 0xa7पूर्ण,
	अणु0x3808, 0x06पूर्ण,
	अणु0x3809, 0x68पूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0xd0पूर्ण,
	अणु0x380c, 0x0eपूर्ण,
	अणु0x380d, 0xecपूर्ण,
	अणु0x380e, 0x04पूर्ण,
	अणु0x380f, 0xe8पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x00पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x01पूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x00पूर्ण,
	अणु0x3817, 0x00पूर्ण,
	अणु0x3818, 0x00पूर्ण,
	अणु0x3819, 0x10पूर्ण,
	अणु0x3820, 0x90पूर्ण,
	अणु0x3821, 0x67पूर्ण,
	अणु0x382a, 0x03पूर्ण,
	अणु0x382b, 0x01पूर्ण,
	अणु0x3830, 0x06पूर्ण,
	अणु0x3836, 0x02पूर्ण,
	अणु0x3862, 0x04पूर्ण,
	अणु0x3863, 0x08पूर्ण,
	अणु0x3cc0, 0x33पूर्ण,
	अणु0x3d85, 0x17पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xdeपूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4003, 0x40पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x05पूर्ण,
	अणु0x400a, 0x00पूर्ण,
	अणु0x400b, 0x84पूर्ण,
	अणु0x400f, 0x80पूर्ण,
	अणु0x4010, 0xf0पूर्ण,
	अणु0x4011, 0xffपूर्ण,
	अणु0x4012, 0x02पूर्ण,
	अणु0x4013, 0x01पूर्ण,
	अणु0x4014, 0x01पूर्ण,
	अणु0x4015, 0x01पूर्ण,
	अणु0x4042, 0x00पूर्ण,
	अणु0x4043, 0x80पूर्ण,
	अणु0x4044, 0x00पूर्ण,
	अणु0x4045, 0x80पूर्ण,
	अणु0x4046, 0x00पूर्ण,
	अणु0x4047, 0x80पूर्ण,
	अणु0x4048, 0x00पूर्ण,
	अणु0x4049, 0x80पूर्ण,
	अणु0x4041, 0x03पूर्ण,
	अणु0x404c, 0x20पूर्ण,
	अणु0x404d, 0x00पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4203, 0x80पूर्ण,
	अणु0x4307, 0x30पूर्ण,
	अणु0x4317, 0x00पूर्ण,
	अणु0x4503, 0x08पूर्ण,
	अणु0x4601, 0x80पूर्ण,
	अणु0x4800, 0x44पूर्ण,
	अणु0x4816, 0x53पूर्ण,
	अणु0x481b, 0x58पूर्ण,
	अणु0x481f, 0x27पूर्ण,
	अणु0x4837, 0x16पूर्ण,
	अणु0x483c, 0x0fपूर्ण,
	अणु0x484b, 0x05पूर्ण,
	अणु0x5000, 0x57पूर्ण,
	अणु0x5001, 0x0aपूर्ण,
	अणु0x5004, 0x04पूर्ण,
	अणु0x502e, 0x03पूर्ण,
	अणु0x5030, 0x41पूर्ण,
	अणु0x5780, 0x14पूर्ण,
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
	अणु0x5791, 0x04पूर्ण,
	अणु0x5792, 0x00पूर्ण,
	अणु0x5793, 0x52पूर्ण,
	अणु0x5794, 0xa3पूर्ण,
	अणु0x5795, 0x00पूर्ण,
	अणु0x5796, 0x10पूर्ण,
	अणु0x5797, 0x10पूर्ण,
	अणु0x5798, 0x73पूर्ण,
	अणु0x5799, 0x73पूर्ण,
	अणु0x579a, 0x00पूर्ण,
	अणु0x579b, 0x28पूर्ण,
	अणु0x579c, 0x00पूर्ण,
	अणु0x579d, 0x16पूर्ण,
	अणु0x579e, 0x06पूर्ण,
	अणु0x579f, 0x20पूर्ण,
	अणु0x57a0, 0x04पूर्ण,
	अणु0x57a1, 0xa0पूर्ण,
	अणु0x59f8, 0x3dपूर्ण,
	अणु0x5a08, 0x02पूर्ण,
	अणु0x5b00, 0x02पूर्ण,
	अणु0x5b01, 0x10पूर्ण,
	अणु0x5b02, 0x03पूर्ण,
	अणु0x5b03, 0xcfपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e00, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ov8856_reg mode_1632x1224_regs[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0302, 0x3cपूर्ण,
	अणु0x0303, 0x01पूर्ण,
	अणु0x031e, 0x0cपूर्ण,
	अणु0x3000, 0x20पूर्ण,
	अणु0x3003, 0x08पूर्ण,
	अणु0x300e, 0x20पूर्ण,
	अणु0x3010, 0x00पूर्ण,
	अणु0x3015, 0x84पूर्ण,
	अणु0x3018, 0x72पूर्ण,
	अणु0x3021, 0x23पूर्ण,
	अणु0x3033, 0x24पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x4cपूर्ण,
	अणु0x3502, 0xe0पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3505, 0x83पूर्ण,
	अणु0x3508, 0x01पूर्ण,
	अणु0x3509, 0x80पूर्ण,
	अणु0x350c, 0x00पूर्ण,
	अणु0x350d, 0x80पूर्ण,
	अणु0x350e, 0x04पूर्ण,
	अणु0x350f, 0x00पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3600, 0x72पूर्ण,
	अणु0x3601, 0x40पूर्ण,
	अणु0x3602, 0x30पूर्ण,
	अणु0x3610, 0xc5पूर्ण,
	अणु0x3611, 0x58पूर्ण,
	अणु0x3612, 0x5cपूर्ण,
	अणु0x3613, 0xcaपूर्ण,
	अणु0x3614, 0x60पूर्ण,
	अणु0x3628, 0xffपूर्ण,
	अणु0x3629, 0xffपूर्ण,
	अणु0x362a, 0xffपूर्ण,
	अणु0x3633, 0x10पूर्ण,
	अणु0x3634, 0x10पूर्ण,
	अणु0x3635, 0x10पूर्ण,
	अणु0x3636, 0x10पूर्ण,
	अणु0x3663, 0x08पूर्ण,
	अणु0x3669, 0x34पूर्ण,
	अणु0x366d, 0x00पूर्ण,
	अणु0x366e, 0x08पूर्ण,
	अणु0x3706, 0x86पूर्ण,
	अणु0x370b, 0x7eपूर्ण,
	अणु0x3714, 0x27पूर्ण,
	अणु0x3730, 0x12पूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3764, 0x00पूर्ण,
	अणु0x3765, 0x00पूर्ण,
	अणु0x3769, 0x62पूर्ण,
	अणु0x376a, 0x2aपूर्ण,
	अणु0x376b, 0x30पूर्ण,
	अणु0x3780, 0x00पूर्ण,
	अणु0x3781, 0x24पूर्ण,
	अणु0x3782, 0x00पूर्ण,
	अणु0x3783, 0x23पूर्ण,
	अणु0x3798, 0x2fपूर्ण,
	अणु0x37a1, 0x60पूर्ण,
	अणु0x37a8, 0x6aपूर्ण,
	अणु0x37ab, 0x3fपूर्ण,
	अणु0x37c2, 0x14पूर्ण,
	अणु0x37c3, 0xf1पूर्ण,
	अणु0x37c9, 0x80पूर्ण,
	अणु0x37cb, 0x16पूर्ण,
	अणु0x37cc, 0x16पूर्ण,
	अणु0x37cd, 0x16पूर्ण,
	अणु0x37ce, 0x16पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x0cपूर्ण,
	अणु0x3804, 0x0cपूर्ण,
	अणु0x3805, 0xdfपूर्ण,
	अणु0x3806, 0x09पूर्ण,
	अणु0x3807, 0xa3पूर्ण,
	अणु0x3808, 0x06पूर्ण,
	अणु0x3809, 0x60पूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0xc8पूर्ण,
	अणु0x380c, 0x07पूर्ण,
	अणु0x380d, 0x8cपूर्ण,
	अणु0x380e, 0x09पूर्ण,
	अणु0x380f, 0xb2पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x02पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x01पूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x00पूर्ण,
	अणु0x3817, 0x00पूर्ण,
	अणु0x3818, 0x00पूर्ण,
	अणु0x3819, 0x10पूर्ण,
	अणु0x3820, 0x80पूर्ण,
	अणु0x3821, 0x47पूर्ण,
	अणु0x382a, 0x03पूर्ण,
	अणु0x382b, 0x01पूर्ण,
	अणु0x3830, 0x06पूर्ण,
	अणु0x3836, 0x02पूर्ण,
	अणु0x3862, 0x04पूर्ण,
	अणु0x3863, 0x08पूर्ण,
	अणु0x3cc0, 0x33पूर्ण,
	अणु0x3d85, 0x17पूर्ण,
	अणु0x3d8c, 0x73पूर्ण,
	अणु0x3d8d, 0xdeपूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4003, 0x40पूर्ण,
	अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x05पूर्ण,
	अणु0x400a, 0x00पूर्ण,
	अणु0x400b, 0x84पूर्ण,
	अणु0x400f, 0x80पूर्ण,
	अणु0x4010, 0xf0पूर्ण,
	अणु0x4011, 0xffपूर्ण,
	अणु0x4012, 0x02पूर्ण,
	अणु0x4013, 0x01पूर्ण,
	अणु0x4014, 0x01पूर्ण,
	अणु0x4015, 0x01पूर्ण,
	अणु0x4042, 0x00पूर्ण,
	अणु0x4043, 0x80पूर्ण,
	अणु0x4044, 0x00पूर्ण,
	अणु0x4045, 0x80पूर्ण,
	अणु0x4046, 0x00पूर्ण,
	अणु0x4047, 0x80पूर्ण,
	अणु0x4048, 0x00पूर्ण,
	अणु0x4049, 0x80पूर्ण,
	अणु0x4041, 0x03पूर्ण,
	अणु0x404c, 0x20पूर्ण,
	अणु0x404d, 0x00पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4203, 0x80पूर्ण,
	अणु0x4307, 0x30पूर्ण,
	अणु0x4317, 0x00पूर्ण,
	अणु0x4502, 0x50पूर्ण,
	अणु0x4503, 0x08पूर्ण,
	अणु0x4601, 0x80पूर्ण,
	अणु0x4800, 0x44पूर्ण,
	अणु0x4816, 0x53पूर्ण,
	अणु0x481b, 0x50पूर्ण,
	अणु0x481f, 0x27पूर्ण,
	अणु0x4823, 0x3cपूर्ण,
	अणु0x482b, 0x00पूर्ण,
	अणु0x4831, 0x66पूर्ण,
	अणु0x4837, 0x16पूर्ण,
	अणु0x483c, 0x0fपूर्ण,
	अणु0x484b, 0x05पूर्ण,
	अणु0x5000, 0x77पूर्ण,
	अणु0x5001, 0x0aपूर्ण,
	अणु0x5003, 0xc8पूर्ण,
	अणु0x5004, 0x04पूर्ण,
	अणु0x5006, 0x00पूर्ण,
	अणु0x5007, 0x00पूर्ण,
	अणु0x502e, 0x03पूर्ण,
	अणु0x5030, 0x41पूर्ण,
	अणु0x5795, 0x00पूर्ण,
	अणु0x5796, 0x10पूर्ण,
	अणु0x5797, 0x10पूर्ण,
	अणु0x5798, 0x73पूर्ण,
	अणु0x5799, 0x73पूर्ण,
	अणु0x579a, 0x00पूर्ण,
	अणु0x579b, 0x28पूर्ण,
	अणु0x579c, 0x00पूर्ण,
	अणु0x579d, 0x16पूर्ण,
	अणु0x579e, 0x06पूर्ण,
	अणु0x579f, 0x20पूर्ण,
	अणु0x57a0, 0x04पूर्ण,
	अणु0x57a1, 0xa0पूर्ण,
	अणु0x5780, 0x14पूर्ण,
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
	अणु0x5791, 0x04पूर्ण,
	अणु0x5792, 0x00पूर्ण,
	अणु0x5793, 0x52पूर्ण,
	अणु0x5794, 0xa3पूर्ण,
	अणु0x59f8, 0x3dपूर्ण,
	अणु0x5a08, 0x02पूर्ण,
	अणु0x5b00, 0x02पूर्ण,
	अणु0x5b01, 0x10पूर्ण,
	अणु0x5b02, 0x03पूर्ण,
	अणु0x5b03, 0xcfपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e00, 0x00पूर्ण,
	अणु0x5e10, 0xfcपूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov8856_test_pattern_menu[] = अणु
	"Disabled",
	"Standard Color Bar",
	"Top-Bottom Darker Color Bar",
	"Right-Left Darker Color Bar",
	"Bottom-Top Darker Color Bar"
पूर्ण;

अटल स्थिर s64 link_freq_menu_items[] = अणु
	OV8856_LINK_FREQ_360MHZ,
	OV8856_LINK_FREQ_180MHZ
पूर्ण;

अटल स्थिर काष्ठा ov8856_link_freq_config link_freq_configs[] = अणु
	[OV8856_LINK_FREQ_720MBPS] = अणु
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_720mbps),
			.regs = mipi_data_rate_720mbps,
		पूर्ण
	पूर्ण,
	[OV8856_LINK_FREQ_360MBPS] = अणु
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_360mbps),
			.regs = mipi_data_rate_360mbps,
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ov8856_mode supported_modes[] = अणु
	अणु
		.width = 3280,
		.height = 2464,
		.hts = 1928,
		.vts_def = 2488,
		.vts_min = 2488,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_3280x2464_regs),
			.regs = mode_3280x2464_regs,
		पूर्ण,
		.link_freq_index = OV8856_LINK_FREQ_720MBPS,
	पूर्ण,
	अणु
		.width = 3264,
		.height = 2448,
		.hts = 1932,
		.vts_def = 2482,
		.vts_min = 2482,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_3264x2448_regs),
			.regs = mode_3264x2448_regs,
		पूर्ण,
		.link_freq_index = OV8856_LINK_FREQ_720MBPS,
	पूर्ण,
	अणु
		.width = 1640,
		.height = 1232,
		.hts = 3820,
		.vts_def = 1256,
		.vts_min = 1256,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1640x1232_regs),
			.regs = mode_1640x1232_regs,
		पूर्ण,
		.link_freq_index = OV8856_LINK_FREQ_360MBPS,
	पूर्ण,
	अणु
		.width = 1632,
		.height = 1224,
		.hts = 1932,
		.vts_def = 2482,
		.vts_min = 2482,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1632x1224_regs),
			.regs = mode_1632x1224_regs,
		पूर्ण,
		.link_freq_index = OV8856_LINK_FREQ_360MBPS,
	पूर्ण
पूर्ण;

काष्ठा ov8856 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	काष्ठा clk		*xvclk;
	काष्ठा gpio_desc	*reset_gpio;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(ov8856_supply_names)];

	/* V4L2 Controls */
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl *hblank;
	काष्ठा v4l2_ctrl *exposure;

	/* Current mode */
	स्थिर काष्ठा ov8856_mode *cur_mode;

	/* To serialize asynchronus callbacks */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;
पूर्ण;

अटल u64 to_pixel_rate(u32 f_index)
अणु
	u64 pixel_rate = link_freq_menu_items[f_index] * 2 * OV8856_DATA_LANES;

	करो_भाग(pixel_rate, OV8856_RGB_DEPTH);

	वापस pixel_rate;
पूर्ण

अटल u64 to_pixels_per_line(u32 hts, u32 f_index)
अणु
	u64 ppl = hts * to_pixel_rate(f_index);

	करो_भाग(ppl, OV8856_SCLK);

	वापस ppl;
पूर्ण

अटल पूर्णांक ov8856_पढ़ो_reg(काष्ठा ov8856 *ov8856, u16 reg, u16 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);
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

अटल पूर्णांक ov8856_ग_लिखो_reg(काष्ठा ov8856 *ov8856, u16 reg, u16 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);
	u8 buf[6];

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);
	put_unaligned_be32(val << 8 * (4 - len), buf + 2);
	अगर (i2c_master_send(client, buf, len + 2) != len + 2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ov8856_ग_लिखो_reg_list(काष्ठा ov8856 *ov8856,
				 स्थिर काष्ठा ov8856_reg_list *r_list)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < r_list->num_of_regs; i++) अणु
		ret = ov8856_ग_लिखो_reg(ov8856, r_list->regs[i].address, 1,
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

अटल पूर्णांक ov8856_update_digital_gain(काष्ठा ov8856 *ov8856, u32 d_gain)
अणु
	पूर्णांक ret;

	ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_MWB_R_GAIN,
			       OV8856_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_MWB_G_GAIN,
			       OV8856_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	वापस ov8856_ग_लिखो_reg(ov8856, OV8856_REG_MWB_B_GAIN,
				OV8856_REG_VALUE_16BIT, d_gain);
पूर्ण

अटल पूर्णांक ov8856_test_pattern(काष्ठा ov8856 *ov8856, u32 pattern)
अणु
	अगर (pattern)
		pattern = (pattern - 1) << OV8856_TEST_PATTERN_BAR_SHIFT |
			  OV8856_TEST_PATTERN_ENABLE;

	वापस ov8856_ग_लिखो_reg(ov8856, OV8856_REG_TEST_PATTERN,
				OV8856_REG_VALUE_08BIT, pattern);
पूर्ण

अटल पूर्णांक ov8856_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov8856 *ov8856 = container_of(ctrl->handler,
					     काष्ठा ov8856, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);
	s64 exposure_max;
	पूर्णांक ret = 0;

	/* Propagate change of current control to all related controls */
	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = ov8856->cur_mode->height + ctrl->val -
			       OV8856_EXPOSURE_MAX_MARGIN;
		__v4l2_ctrl_modअगरy_range(ov8856->exposure,
					 ov8856->exposure->minimum,
					 exposure_max, ov8856->exposure->step,
					 exposure_max);
	पूर्ण

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_ANALOG_GAIN,
				       OV8856_REG_VALUE_16BIT, ctrl->val);
		अवरोध;

	हाल V4L2_CID_DIGITAL_GAIN:
		ret = ov8856_update_digital_gain(ov8856, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE:
		/* 4 least signअगरicant bits of expsoure are fractional part */
		ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_EXPOSURE,
				       OV8856_REG_VALUE_24BIT, ctrl->val << 4);
		अवरोध;

	हाल V4L2_CID_VBLANK:
		ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_VTS,
				       OV8856_REG_VALUE_16BIT,
				       ov8856->cur_mode->height + ctrl->val);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		ret = ov8856_test_pattern(ov8856, ctrl->val);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov8856_ctrl_ops = अणु
	.s_ctrl = ov8856_set_ctrl,
पूर्ण;

अटल पूर्णांक ov8856_init_controls(काष्ठा ov8856 *ov8856)
अणु
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	s64 exposure_max, h_blank;
	पूर्णांक ret;

	ctrl_hdlr = &ov8856->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 8);
	अगर (ret)
		वापस ret;

	ctrl_hdlr->lock = &ov8856->mutex;
	ov8856->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr, &ov8856_ctrl_ops,
					   V4L2_CID_LINK_FREQ,
					   ARRAY_SIZE(link_freq_menu_items) - 1,
					   0, link_freq_menu_items);
	अगर (ov8856->link_freq)
		ov8856->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ov8856->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &ov8856_ctrl_ops,
				       V4L2_CID_PIXEL_RATE, 0,
				       to_pixel_rate(OV8856_LINK_FREQ_720MBPS),
				       1,
				       to_pixel_rate(OV8856_LINK_FREQ_720MBPS));
	ov8856->vblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov8856_ctrl_ops,
			  V4L2_CID_VBLANK,
			  ov8856->cur_mode->vts_min - ov8856->cur_mode->height,
			  OV8856_VTS_MAX - ov8856->cur_mode->height, 1,
			  ov8856->cur_mode->vts_def - ov8856->cur_mode->height);
	h_blank = to_pixels_per_line(ov8856->cur_mode->hts,
		  ov8856->cur_mode->link_freq_index) - ov8856->cur_mode->width;
	ov8856->hblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov8856_ctrl_ops,
					   V4L2_CID_HBLANK, h_blank, h_blank, 1,
					   h_blank);
	अगर (ov8856->hblank)
		ov8856->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	v4l2_ctrl_new_std(ctrl_hdlr, &ov8856_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  OV8856_ANAL_GAIN_MIN, OV8856_ANAL_GAIN_MAX,
			  OV8856_ANAL_GAIN_STEP, OV8856_ANAL_GAIN_MIN);
	v4l2_ctrl_new_std(ctrl_hdlr, &ov8856_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  OV8856_DGTL_GAIN_MIN, OV8856_DGTL_GAIN_MAX,
			  OV8856_DGTL_GAIN_STEP, OV8856_DGTL_GAIN_DEFAULT);
	exposure_max = ov8856->cur_mode->vts_def - OV8856_EXPOSURE_MAX_MARGIN;
	ov8856->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &ov8856_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     OV8856_EXPOSURE_MIN, exposure_max,
					     OV8856_EXPOSURE_STEP,
					     exposure_max);
	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &ov8856_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov8856_test_pattern_menu) - 1,
				     0, 0, ov8856_test_pattern_menu);
	अगर (ctrl_hdlr->error)
		वापस ctrl_hdlr->error;

	ov8856->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;
पूर्ण

अटल व्योम ov8856_update_pad_क्रमmat(स्थिर काष्ठा ov8856_mode *mode,
				     काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov8856_start_streaming(काष्ठा ov8856 *ov8856)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);
	स्थिर काष्ठा ov8856_reg_list *reg_list;
	पूर्णांक link_freq_index, ret;

	link_freq_index = ov8856->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = ov8856_ग_लिखो_reg_list(ov8856, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set plls");
		वापस ret;
	पूर्ण

	reg_list = &ov8856->cur_mode->reg_list;
	ret = ov8856_ग_लिखो_reg_list(ov8856, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set mode");
		वापस ret;
	पूर्ण

	ret = __v4l2_ctrl_handler_setup(ov8856->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_MODE_SELECT,
			       OV8856_REG_VALUE_08BIT, OV8856_MODE_STREAMING);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set stream");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ov8856_stop_streaming(काष्ठा ov8856 *ov8856)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);

	अगर (ov8856_ग_लिखो_reg(ov8856, OV8856_REG_MODE_SELECT,
			     OV8856_REG_VALUE_08BIT, OV8856_MODE_STANDBY))
		dev_err(&client->dev, "failed to set stream");
पूर्ण

अटल पूर्णांक ov8856_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov8856 *ov8856 = to_ov8856(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (ov8856->streaming == enable)
		वापस 0;

	mutex_lock(&ov8856->mutex);
	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			mutex_unlock(&ov8856->mutex);
			वापस ret;
		पूर्ण

		ret = ov8856_start_streaming(ov8856);
		अगर (ret) अणु
			enable = 0;
			ov8856_stop_streaming(ov8856);
			pm_runसमय_put(&client->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		ov8856_stop_streaming(ov8856);
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov8856->streaming = enable;
	mutex_unlock(&ov8856->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __ov8856_घातer_on(काष्ठा ov8856 *ov8856)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);
	पूर्णांक ret;

	अगर (is_acpi_node(dev_fwnode(&client->dev)))
		वापस 0;

	ret = clk_prepare_enable(ov8856->xvclk);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to enable xvclk\n");
		वापस ret;
	पूर्ण

	अगर (ov8856->reset_gpio) अणु
		gpiod_set_value_cansleep(ov8856->reset_gpio, 1);
		usleep_range(1000, 2000);
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(ov8856_supply_names),
				    ov8856->supplies);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to enable regulators\n");
		जाओ disable_clk;
	पूर्ण

	gpiod_set_value_cansleep(ov8856->reset_gpio, 0);
	usleep_range(1500, 1800);

	वापस 0;

disable_clk:
	gpiod_set_value_cansleep(ov8856->reset_gpio, 1);
	clk_disable_unprepare(ov8856->xvclk);

	वापस ret;
पूर्ण

अटल व्योम __ov8856_घातer_off(काष्ठा ov8856 *ov8856)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);

	अगर (is_acpi_node(dev_fwnode(&client->dev)))
		वापस;

	gpiod_set_value_cansleep(ov8856->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ov8856_supply_names),
			       ov8856->supplies);
	clk_disable_unprepare(ov8856->xvclk);
पूर्ण

अटल पूर्णांक __maybe_unused ov8856_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov8856 *ov8856 = to_ov8856(sd);

	mutex_lock(&ov8856->mutex);
	अगर (ov8856->streaming)
		ov8856_stop_streaming(ov8856);

	__ov8856_घातer_off(ov8856);
	mutex_unlock(&ov8856->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov8856_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov8856 *ov8856 = to_ov8856(sd);
	पूर्णांक ret;

	mutex_lock(&ov8856->mutex);

	__ov8856_घातer_on(ov8856);
	अगर (ov8856->streaming) अणु
		ret = ov8856_start_streaming(ov8856);
		अगर (ret) अणु
			ov8856->streaming = false;
			ov8856_stop_streaming(ov8856);
			mutex_unlock(&ov8856->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&ov8856->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov8856_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov8856 *ov8856 = to_ov8856(sd);
	स्थिर काष्ठा ov8856_mode *mode;
	s32 vblank_def, h_blank;

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes), width,
				      height, fmt->क्रमmat.width,
				      fmt->क्रमmat.height);

	mutex_lock(&ov8856->mutex);
	ov8856_update_pad_क्रमmat(mode, &fmt->क्रमmat);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		ov8856->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(ov8856->link_freq, mode->link_freq_index);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(ov8856->pixel_rate,
					 to_pixel_rate(mode->link_freq_index));

		/* Update limits and set FPS to शेष */
		vblank_def = mode->vts_def - mode->height;
		__v4l2_ctrl_modअगरy_range(ov8856->vblank,
					 mode->vts_min - mode->height,
					 OV8856_VTS_MAX - mode->height, 1,
					 vblank_def);
		__v4l2_ctrl_s_ctrl(ov8856->vblank, vblank_def);
		h_blank = to_pixels_per_line(mode->hts, mode->link_freq_index) -
			  mode->width;
		__v4l2_ctrl_modअगरy_range(ov8856->hblank, h_blank, h_blank, 1,
					 h_blank);
	पूर्ण

	mutex_unlock(&ov8856->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov8856_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov8856 *ov8856 = to_ov8856(sd);

	mutex_lock(&ov8856->mutex);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(&ov8856->sd, cfg,
							  fmt->pad);
	अन्यथा
		ov8856_update_pad_क्रमmat(ov8856->cur_mode, &fmt->क्रमmat);

	mutex_unlock(&ov8856->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov8856_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	/* Only one bayer order GRBG is supported */
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov8856_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
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

अटल पूर्णांक ov8856_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov8856 *ov8856 = to_ov8856(sd);

	mutex_lock(&ov8856->mutex);
	ov8856_update_pad_क्रमmat(&supported_modes[0],
				 v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0));
	mutex_unlock(&ov8856->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov8856_video_ops = अणु
	.s_stream = ov8856_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov8856_pad_ops = अणु
	.set_fmt = ov8856_set_क्रमmat,
	.get_fmt = ov8856_get_क्रमmat,
	.क्रमागत_mbus_code = ov8856_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov8856_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov8856_subdev_ops = अणु
	.video = &ov8856_video_ops,
	.pad = &ov8856_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ov8856_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov8856_पूर्णांकernal_ops = अणु
	.खोलो = ov8856_खोलो,
पूर्ण;

अटल पूर्णांक ov8856_identअगरy_module(काष्ठा ov8856 *ov8856)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov8856->sd);
	पूर्णांक ret;
	u32 val;

	ret = ov8856_पढ़ो_reg(ov8856, OV8856_REG_CHIP_ID,
			      OV8856_REG_VALUE_24BIT, &val);
	अगर (ret)
		वापस ret;

	अगर (val != OV8856_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x",
			OV8856_CHIP_ID, val);
		वापस -ENXIO;
	पूर्ण

	ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_MODE_SELECT,
			       OV8856_REG_VALUE_08BIT, OV8856_MODE_STREAMING);
	अगर (ret)
		वापस ret;

	ret = ov8856_ग_लिखो_reg(ov8856, OV8856_OTP_MODE_CTRL,
			       OV8856_REG_VALUE_08BIT, OV8856_OTP_MODE_AUTO);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set otp mode");
		वापस ret;
	पूर्ण

	ret = ov8856_ग_लिखो_reg(ov8856, OV8856_OTP_LOAD_CTRL,
			       OV8856_REG_VALUE_08BIT,
			       OV8856_OTP_LOAD_CTRL_ENABLE);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to enable load control");
		वापस ret;
	पूर्ण

	ret = ov8856_पढ़ो_reg(ov8856, OV8856_MODULE_REVISION,
			      OV8856_REG_VALUE_08BIT, &val);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to read module revision");
		वापस ret;
	पूर्ण

	dev_info(&client->dev, "OV8856 revision %x (%s) at address 0x%02x\n",
		 val,
		 val == OV8856_2A_MODULE ? "2A" :
		 val == OV8856_1B_MODULE ? "1B" : "unknown revision",
		 client->addr);

	ret = ov8856_ग_लिखो_reg(ov8856, OV8856_REG_MODE_SELECT,
			       OV8856_REG_VALUE_08BIT, OV8856_MODE_STANDBY);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to exit streaming mode");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov8856_get_hwcfg(काष्ठा ov8856 *ov8856, काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *ep;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	u32 xvclk_rate;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, j;

	अगर (!fwnode)
		वापस -ENXIO;

	ret = fwnode_property_पढ़ो_u32(fwnode, "clock-frequency", &xvclk_rate);
	अगर (ret)
		वापस ret;

	अगर (!is_acpi_node(fwnode)) अणु
		ov8856->xvclk = devm_clk_get(dev, "xvclk");
		अगर (IS_ERR(ov8856->xvclk)) अणु
			dev_err(dev, "could not get xvclk clock (%pe)\n",
				ov8856->xvclk);
			वापस PTR_ERR(ov8856->xvclk);
		पूर्ण

		clk_set_rate(ov8856->xvclk, xvclk_rate);
		xvclk_rate = clk_get_rate(ov8856->xvclk);
	पूर्ण

	अगर (xvclk_rate != OV8856_XVCLK_19_2)
		dev_warn(dev, "external clock rate %u is unsupported",
			 xvclk_rate);

	ov8856->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(ov8856->reset_gpio))
		वापस PTR_ERR(ov8856->reset_gpio);

	क्रम (i = 0; i < ARRAY_SIZE(ov8856_supply_names); i++)
		ov8856->supplies[i].supply = ov8856_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ov8856_supply_names),
				      ov8856->supplies);
	अगर (ret)
		वापस ret;

	ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (!ep)
		वापस -ENXIO;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	अगर (ret)
		वापस ret;

	अगर (bus_cfg.bus.mipi_csi2.num_data_lanes != OV8856_DATA_LANES) अणु
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

अटल पूर्णांक ov8856_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov8856 *ov8856 = to_ov8856(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	pm_runसमय_disable(&client->dev);
	mutex_destroy(&ov8856->mutex);

	__ov8856_घातer_off(ov8856);

	वापस 0;
पूर्ण

अटल पूर्णांक ov8856_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov8856 *ov8856;
	पूर्णांक ret;

	ov8856 = devm_kzalloc(&client->dev, माप(*ov8856), GFP_KERNEL);
	अगर (!ov8856)
		वापस -ENOMEM;

	ret = ov8856_get_hwcfg(ov8856, &client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to get HW configuration: %d",
			ret);
		वापस ret;
	पूर्ण

	v4l2_i2c_subdev_init(&ov8856->sd, client, &ov8856_subdev_ops);

	ret = __ov8856_घातer_on(ov8856);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to power on\n");
		वापस ret;
	पूर्ण

	ret = ov8856_identअगरy_module(ov8856);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		जाओ probe_घातer_off;
	पूर्ण

	mutex_init(&ov8856->mutex);
	ov8856->cur_mode = &supported_modes[0];
	ret = ov8856_init_controls(ov8856);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init controls: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ov8856->sd.पूर्णांकernal_ops = &ov8856_पूर्णांकernal_ops;
	ov8856->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov8856->sd.entity.ops = &ov8856_subdev_entity_ops;
	ov8856->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ov8856->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&ov8856->sd.entity, 1, &ov8856->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&ov8856->sd);
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
	media_entity_cleanup(&ov8856->sd.entity);

probe_error_v4l2_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(ov8856->sd.ctrl_handler);
	mutex_destroy(&ov8856->mutex);

probe_घातer_off:
	__ov8856_घातer_off(ov8856);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov8856_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ov8856_suspend, ov8856_resume)
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id ov8856_acpi_ids[] = अणु
	अणु"OVTI8856"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, ov8856_acpi_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id ov8856_of_match[] = अणु
	अणु .compatible = "ovti,ov8856" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov8856_of_match);

अटल काष्ठा i2c_driver ov8856_i2c_driver = अणु
	.driver = अणु
		.name = "ov8856",
		.pm = &ov8856_pm_ops,
		.acpi_match_table = ACPI_PTR(ov8856_acpi_ids),
		.of_match_table = ov8856_of_match,
	पूर्ण,
	.probe_new = ov8856_probe,
	.हटाओ = ov8856_हटाओ,
पूर्ण;

module_i2c_driver(ov8856_i2c_driver);

MODULE_AUTHOR("Ben Kao <ben.kao@intel.com>");
MODULE_DESCRIPTION("OmniVision OV8856 sensor driver");
MODULE_LICENSE("GPL v2");
