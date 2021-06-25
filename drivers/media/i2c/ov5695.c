<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ov5695 driver
 *
 * Copyright (C) 2017 Fuzhou Rockchip Electronics Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sysfs.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#अगर_अघोषित V4L2_CID_DIGITAL_GAIN
#घोषणा V4L2_CID_DIGITAL_GAIN		V4L2_CID_GAIN
#पूर्ण_अगर

/* 45Mhz * 4 Binning */
#घोषणा OV5695_PIXEL_RATE		(45 * 1000 * 1000 * 4)
#घोषणा OV5695_XVCLK_FREQ		24000000

#घोषणा CHIP_ID				0x005695
#घोषणा OV5695_REG_CHIP_ID		0x300a

#घोषणा OV5695_REG_CTRL_MODE		0x0100
#घोषणा OV5695_MODE_SW_STANDBY		0x0
#घोषणा OV5695_MODE_STREAMING		BIT(0)

#घोषणा OV5695_REG_EXPOSURE		0x3500
#घोषणा	OV5695_EXPOSURE_MIN		4
#घोषणा	OV5695_EXPOSURE_STEP		1
#घोषणा OV5695_VTS_MAX			0x7fff

#घोषणा OV5695_REG_ANALOG_GAIN		0x3509
#घोषणा	ANALOG_GAIN_MIN			0x10
#घोषणा	ANALOG_GAIN_MAX			0xf8
#घोषणा	ANALOG_GAIN_STEP		1
#घोषणा	ANALOG_GAIN_DEFAULT		0xf8

#घोषणा OV5695_REG_DIGI_GAIN_H		0x350a
#घोषणा OV5695_REG_DIGI_GAIN_L		0x350b
#घोषणा OV5695_DIGI_GAIN_L_MASK		0x3f
#घोषणा OV5695_DIGI_GAIN_H_SHIFT	6
#घोषणा OV5695_DIGI_GAIN_MIN		0
#घोषणा OV5695_DIGI_GAIN_MAX		(0x4000 - 1)
#घोषणा OV5695_DIGI_GAIN_STEP		1
#घोषणा OV5695_DIGI_GAIN_DEFAULT	1024

#घोषणा OV5695_REG_TEST_PATTERN		0x4503
#घोषणा	OV5695_TEST_PATTERN_ENABLE	0x80
#घोषणा	OV5695_TEST_PATTERN_DISABLE	0x0

#घोषणा OV5695_REG_VTS			0x380e

#घोषणा REG_शून्य			0xFFFF

#घोषणा OV5695_REG_VALUE_08BIT		1
#घोषणा OV5695_REG_VALUE_16BIT		2
#घोषणा OV5695_REG_VALUE_24BIT		3

#घोषणा OV5695_LANES			2
#घोषणा OV5695_BITS_PER_SAMPLE		10

अटल स्थिर अक्षर * स्थिर ov5695_supply_names[] = अणु
	"avdd",		/* Analog घातer */
	"dovdd",	/* Digital I/O घातer */
	"dvdd",		/* Digital core घातer */
पूर्ण;

#घोषणा OV5695_NUM_SUPPLIES ARRAY_SIZE(ov5695_supply_names)

काष्ठा regval अणु
	u16 addr;
	u8 val;
पूर्ण;

काष्ठा ov5695_mode अणु
	u32 width;
	u32 height;
	u32 max_fps;
	u32 hts_def;
	u32 vts_def;
	u32 exp_def;
	स्थिर काष्ठा regval *reg_list;
पूर्ण;

काष्ठा ov5695 अणु
	काष्ठा i2c_client	*client;
	काष्ठा clk		*xvclk;
	काष्ठा gpio_desc	*reset_gpio;
	काष्ठा regulator_bulk_data supplies[OV5695_NUM_SUPPLIES];

	काष्ठा v4l2_subdev	subdev;
	काष्ठा media_pad	pad;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl	*exposure;
	काष्ठा v4l2_ctrl	*anal_gain;
	काष्ठा v4l2_ctrl	*digi_gain;
	काष्ठा v4l2_ctrl	*hblank;
	काष्ठा v4l2_ctrl	*vblank;
	काष्ठा v4l2_ctrl	*test_pattern;
	काष्ठा mutex		mutex;
	bool			streaming;
	स्थिर काष्ठा ov5695_mode *cur_mode;
पूर्ण;

#घोषणा to_ov5695(sd) container_of(sd, काष्ठा ov5695, subdev)

/*
 * Xclk 24Mhz
 * Pclk 45Mhz
 * linelength 672(0x2a0)
 * framelength 2232(0x8b8)
 * grabwinकरोw_width 1296
 * grabwinकरोw_height 972
 * max_framerate 30fps
 * mipi_datarate per lane 840Mbps
 */
अटल स्थिर काष्ठा regval ov5695_global_regs[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0100, 0x00पूर्ण,
	अणु0x0300, 0x04पूर्ण,
	अणु0x0301, 0x00पूर्ण,
	अणु0x0302, 0x69पूर्ण,
	अणु0x0303, 0x00पूर्ण,
	अणु0x0304, 0x00पूर्ण,
	अणु0x0305, 0x01पूर्ण,
	अणु0x0307, 0x00पूर्ण,
	अणु0x030b, 0x00पूर्ण,
	अणु0x030c, 0x00पूर्ण,
	अणु0x030d, 0x1eपूर्ण,
	अणु0x030e, 0x04पूर्ण,
	अणु0x030f, 0x03पूर्ण,
	अणु0x0312, 0x01पूर्ण,
	अणु0x3000, 0x00पूर्ण,
	अणु0x3002, 0xa1पूर्ण,
	अणु0x3008, 0x00पूर्ण,
	अणु0x3010, 0x00पूर्ण,
	अणु0x3022, 0x51पूर्ण,
	अणु0x3106, 0x15पूर्ण,
	अणु0x3107, 0x01पूर्ण,
	अणु0x3108, 0x05पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x45पूर्ण,
	अणु0x3502, 0x00पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3504, 0x03पूर्ण,
	अणु0x3505, 0x8cपूर्ण,
	अणु0x3507, 0x03पूर्ण,
	अणु0x3508, 0x00पूर्ण,
	अणु0x3509, 0x10पूर्ण,
	अणु0x350c, 0x00पूर्ण,
	अणु0x350d, 0x80पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3601, 0x55पूर्ण,
	अणु0x3602, 0x58पूर्ण,
	अणु0x3614, 0x30पूर्ण,
	अणु0x3615, 0x77पूर्ण,
	अणु0x3621, 0x08पूर्ण,
	अणु0x3624, 0x40पूर्ण,
	अणु0x3633, 0x0cपूर्ण,
	अणु0x3634, 0x0cपूर्ण,
	अणु0x3635, 0x0cपूर्ण,
	अणु0x3636, 0x0cपूर्ण,
	अणु0x3638, 0x00पूर्ण,
	अणु0x3639, 0x00पूर्ण,
	अणु0x363a, 0x00पूर्ण,
	अणु0x363b, 0x00पूर्ण,
	अणु0x363c, 0xffपूर्ण,
	अणु0x363d, 0xfaपूर्ण,
	अणु0x3650, 0x44पूर्ण,
	अणु0x3651, 0x44पूर्ण,
	अणु0x3652, 0x44पूर्ण,
	अणु0x3653, 0x44पूर्ण,
	अणु0x3654, 0x44पूर्ण,
	अणु0x3655, 0x44पूर्ण,
	अणु0x3656, 0x44पूर्ण,
	अणु0x3657, 0x44पूर्ण,
	अणु0x3660, 0x00पूर्ण,
	अणु0x3661, 0x00पूर्ण,
	अणु0x3662, 0x00पूर्ण,
	अणु0x366a, 0x00पूर्ण,
	अणु0x366e, 0x0cपूर्ण,
	अणु0x3673, 0x04पूर्ण,
	अणु0x3700, 0x14पूर्ण,
	अणु0x3703, 0x0cपूर्ण,
	अणु0x3715, 0x01पूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3734, 0x40पूर्ण,
	अणु0x373f, 0xa0पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x37a1, 0x1dपूर्ण,
	अणु0x37a8, 0x26पूर्ण,
	अणु0x37ab, 0x14पूर्ण,
	अणु0x37c2, 0x04पूर्ण,
	अणु0x37cb, 0x09पूर्ण,
	अणु0x37cc, 0x13पूर्ण,
	अणु0x37cd, 0x1fपूर्ण,
	अणु0x37ce, 0x1fपूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xafपूर्ण,
	अणु0x3808, 0x05पूर्ण,
	अणु0x3809, 0x10पूर्ण,
	अणु0x380a, 0x03पूर्ण,
	अणु0x380b, 0xccपूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xa0पूर्ण,
	अणु0x380e, 0x08पूर्ण,
	अणु0x380f, 0xb8पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x06पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x06पूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x03पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3818, 0x00पूर्ण,
	अणु0x3819, 0x00पूर्ण,
	अणु0x381a, 0x00पूर्ण,
	अणु0x381b, 0x01पूर्ण,
	अणु0x3820, 0x8bपूर्ण,
	अणु0x3821, 0x01पूर्ण,
	अणु0x3c80, 0x08पूर्ण,
	अणु0x3c82, 0x00पूर्ण,
	अणु0x3c83, 0x00पूर्ण,
	अणु0x3c88, 0x00पूर्ण,
	अणु0x3d85, 0x14पूर्ण,
	अणु0x3f02, 0x08पूर्ण,
	अणु0x3f03, 0x10पूर्ण,
	अणु0x4008, 0x02पूर्ण,
	अणु0x4009, 0x09पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4501, 0x00पूर्ण,
	अणु0x4502, 0x10पूर्ण,
	अणु0x4800, 0x00पूर्ण,
	अणु0x481f, 0x2aपूर्ण,
	अणु0x4837, 0x13पूर्ण,
	अणु0x5000, 0x17पूर्ण,
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
	अणु0x5b00, 0x00पूर्ण,
	अणु0x5b01, 0x1cपूर्ण,
	अणु0x5b02, 0x00पूर्ण,
	अणु0x5b03, 0x7fपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e10, 0xfcपूर्ण,
	अणु0x4010, 0xf1पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3505, 0x8cपूर्ण,
	अणु0x3507, 0x03पूर्ण,
	अणु0x3508, 0x00पूर्ण,
	अणु0x3509, 0xf8पूर्ण,
	अणुREG_शून्य, 0x00पूर्ण,
पूर्ण;

/*
 * Xclk 24Mhz
 * Pclk 45Mhz
 * linelength 740(0x2e4)
 * framelength 2024(0x7e8)
 * grabwinकरोw_width 2592
 * grabwinकरोw_height 1944
 * max_framerate 30fps
 * mipi_datarate per lane 840Mbps
 */
अटल स्थिर काष्ठा regval ov5695_2592x1944_regs[] = अणु
	अणु0x3501, 0x7eपूर्ण,
	अणु0x366e, 0x18पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x04पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xabपूर्ण,
	अणु0x3808, 0x0aपूर्ण,
	अणु0x3809, 0x20पूर्ण,
	अणु0x380a, 0x07पूर्ण,
	अणु0x380b, 0x98पूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xe4पूर्ण,
	अणु0x380e, 0x07पूर्ण,
	अणु0x380f, 0xe8पूर्ण,
	अणु0x3811, 0x06पूर्ण,
	अणु0x3813, 0x08पूर्ण,
	अणु0x3814, 0x01पूर्ण,
	अणु0x3816, 0x01पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3820, 0x88पूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x4501, 0x00पूर्ण,
	अणु0x4008, 0x04पूर्ण,
	अणु0x4009, 0x13पूर्ण,
	अणुREG_शून्य, 0x00पूर्ण,
पूर्ण;

/*
 * Xclk 24Mhz
 * Pclk 45Mhz
 * linelength 672(0x2a0)
 * framelength 2232(0x8b8)
 * grabwinकरोw_width 1920
 * grabwinकरोw_height 1080
 * max_framerate 30fps
 * mipi_datarate per lane 840Mbps
 */
अटल स्थिर काष्ठा regval ov5695_1920x1080_regs[] = अणु
	अणु0x3501, 0x45पूर्ण,
	अणु0x366e, 0x18पूर्ण,
	अणु0x3800, 0x01पूर्ण,
	अणु0x3801, 0x50पूर्ण,
	अणु0x3802, 0x01पूर्ण,
	अणु0x3803, 0xb8पूर्ण,
	अणु0x3804, 0x08पूर्ण,
	अणु0x3805, 0xefपूर्ण,
	अणु0x3806, 0x05पूर्ण,
	अणु0x3807, 0xf7पूर्ण,
	अणु0x3808, 0x07पूर्ण,
	अणु0x3809, 0x80पूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0x38पूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xa0पूर्ण,
	अणु0x380e, 0x08पूर्ण,
	अणु0x380f, 0xb8पूर्ण,
	अणु0x3811, 0x06पूर्ण,
	अणु0x3813, 0x04पूर्ण,
	अणु0x3814, 0x01पूर्ण,
	अणु0x3816, 0x01पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3820, 0x88पूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x4501, 0x00पूर्ण,
	अणु0x4008, 0x04पूर्ण,
	अणु0x4009, 0x13पूर्ण,
	अणुREG_शून्य, 0x00पूर्ण
पूर्ण;

/*
 * Xclk 24Mhz
 * Pclk 45Mhz
 * linelength 740(0x02e4)
 * framelength 1012(0x03f4)
 * grabwinकरोw_width 1296
 * grabwinकरोw_height 972
 * max_framerate 60fps
 * mipi_datarate per lane 840Mbps
 */
अटल स्थिर काष्ठा regval ov5695_1296x972_regs[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0100, 0x00पूर्ण,
	अणु0x0300, 0x04पूर्ण,
	अणु0x0301, 0x00पूर्ण,
	अणु0x0302, 0x69पूर्ण,
	अणु0x0303, 0x00पूर्ण,
	अणु0x0304, 0x00पूर्ण,
	अणु0x0305, 0x01पूर्ण,
	अणु0x0307, 0x00पूर्ण,
	अणु0x030b, 0x00पूर्ण,
	अणु0x030c, 0x00पूर्ण,
	अणु0x030d, 0x1eपूर्ण,
	अणु0x030e, 0x04पूर्ण,
	अणु0x030f, 0x03पूर्ण,
	अणु0x0312, 0x01पूर्ण,
	अणु0x3000, 0x00पूर्ण,
	अणु0x3002, 0xa1पूर्ण,
	अणु0x3008, 0x00पूर्ण,
	अणु0x3010, 0x00पूर्ण,
	अणु0x3016, 0x32पूर्ण,
	अणु0x3022, 0x51पूर्ण,
	अणु0x3106, 0x15पूर्ण,
	अणु0x3107, 0x01पूर्ण,
	अणु0x3108, 0x05पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x3eपूर्ण,
	अणु0x3502, 0x00पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3504, 0x03पूर्ण,
	अणु0x3505, 0x8cपूर्ण,
	अणु0x3507, 0x03पूर्ण,
	अणु0x3508, 0x00पूर्ण,
	अणु0x3509, 0x10पूर्ण,
	अणु0x350c, 0x00पूर्ण,
	अणु0x350d, 0x80पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x02पूर्ण,
	अणु0x3512, 0x00पूर्ण,
	अणु0x3601, 0x55पूर्ण,
	अणु0x3602, 0x58पूर्ण,
	अणु0x3611, 0x58पूर्ण,
	अणु0x3614, 0x30पूर्ण,
	अणु0x3615, 0x77पूर्ण,
	अणु0x3621, 0x08पूर्ण,
	अणु0x3624, 0x40पूर्ण,
	अणु0x3633, 0x0cपूर्ण,
	अणु0x3634, 0x0cपूर्ण,
	अणु0x3635, 0x0cपूर्ण,
	अणु0x3636, 0x0cपूर्ण,
	अणु0x3638, 0x00पूर्ण,
	अणु0x3639, 0x00पूर्ण,
	अणु0x363a, 0x00पूर्ण,
	अणु0x363b, 0x00पूर्ण,
	अणु0x363c, 0xffपूर्ण,
	अणु0x363d, 0xfaपूर्ण,
	अणु0x3650, 0x44पूर्ण,
	अणु0x3651, 0x44पूर्ण,
	अणु0x3652, 0x44पूर्ण,
	अणु0x3653, 0x44पूर्ण,
	अणु0x3654, 0x44पूर्ण,
	अणु0x3655, 0x44पूर्ण,
	अणु0x3656, 0x44पूर्ण,
	अणु0x3657, 0x44पूर्ण,
	अणु0x3660, 0x00पूर्ण,
	अणु0x3661, 0x00पूर्ण,
	अणु0x3662, 0x00पूर्ण,
	अणु0x366a, 0x00पूर्ण,
	अणु0x366e, 0x0cपूर्ण,
	अणु0x3673, 0x04पूर्ण,
	अणु0x3700, 0x14पूर्ण,
	अणु0x3703, 0x0cपूर्ण,
	अणु0x3706, 0x24पूर्ण,
	अणु0x3714, 0x27पूर्ण,
	अणु0x3715, 0x01पूर्ण,
	अणु0x3716, 0x00पूर्ण,
	अणु0x3717, 0x02पूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x3734, 0x40पूर्ण,
	अणु0x373f, 0xa0पूर्ण,
	अणु0x3765, 0x20पूर्ण,
	अणु0x37a1, 0x1dपूर्ण,
	अणु0x37a8, 0x26पूर्ण,
	अणु0x37ab, 0x14पूर्ण,
	अणु0x37c2, 0x04पूर्ण,
	अणु0x37c3, 0xf0पूर्ण,
	अणु0x37cb, 0x09पूर्ण,
	अणु0x37cc, 0x13पूर्ण,
	अणु0x37cd, 0x1fपूर्ण,
	अणु0x37ce, 0x1fपूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xafपूर्ण,
	अणु0x3808, 0x05पूर्ण,
	अणु0x3809, 0x10पूर्ण,
	अणु0x380a, 0x03पूर्ण,
	अणु0x380b, 0xccपूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xe4पूर्ण,
	अणु0x380e, 0x03पूर्ण,
	अणु0x380f, 0xf4पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x00पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x06पूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3816, 0x03पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3818, 0x00पूर्ण,
	अणु0x3819, 0x00पूर्ण,
	अणु0x381a, 0x00पूर्ण,
	अणु0x381b, 0x01पूर्ण,
	अणु0x3820, 0x8bपूर्ण,
	अणु0x3821, 0x01पूर्ण,
	अणु0x3c80, 0x08पूर्ण,
	अणु0x3c82, 0x00पूर्ण,
	अणु0x3c83, 0x00पूर्ण,
	अणु0x3c88, 0x00पूर्ण,
	अणु0x3d85, 0x14पूर्ण,
	अणु0x3f02, 0x08पूर्ण,
	अणु0x3f03, 0x10पूर्ण,
	अणु0x4008, 0x02पूर्ण,
	अणु0x4009, 0x09पूर्ण,
	अणु0x404e, 0x20पूर्ण,
	अणु0x4501, 0x00पूर्ण,
	अणु0x4502, 0x10पूर्ण,
	अणु0x4800, 0x00पूर्ण,
	अणु0x481f, 0x2aपूर्ण,
	अणु0x4837, 0x13पूर्ण,
	अणु0x5000, 0x13पूर्ण,
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
	अणु0x5b00, 0x00पूर्ण,
	अणु0x5b01, 0x1cपूर्ण,
	अणु0x5b02, 0x00पूर्ण,
	अणु0x5b03, 0x7fपूर्ण,
	अणु0x5b05, 0x6cपूर्ण,
	अणु0x5e10, 0xfcपूर्ण,
	अणु0x4010, 0xf1पूर्ण,
	अणु0x3503, 0x08पूर्ण,
	अणु0x3505, 0x8cपूर्ण,
	अणु0x3507, 0x03पूर्ण,
	अणु0x3508, 0x00पूर्ण,
	अणु0x3509, 0xf8पूर्ण,
	अणु0x0100, 0x01पूर्ण,
	अणुREG_शून्य, 0x00पूर्ण
पूर्ण;

/*
 * Xclk 24Mhz
 * Pclk 45Mhz
 * linelength 672(0x2a0)
 * framelength 2232(0x8b8)
 * grabwinकरोw_width 1280
 * grabwinकरोw_height 720
 * max_framerate 30fps
 * mipi_datarate per lane 840Mbps
 */
अटल स्थिर काष्ठा regval ov5695_1280x720_regs[] = अणु
	अणु0x3501, 0x45पूर्ण,
	अणु0x366e, 0x0cपूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x01पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x06पूर्ण,
	अणु0x3807, 0xafपूर्ण,
	अणु0x3808, 0x05पूर्ण,
	अणु0x3809, 0x00पूर्ण,
	अणु0x380a, 0x02पूर्ण,
	अणु0x380b, 0xd0पूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xa0पूर्ण,
	अणु0x380e, 0x08पूर्ण,
	अणु0x380f, 0xb8पूर्ण,
	अणु0x3811, 0x06पूर्ण,
	अणु0x3813, 0x02पूर्ण,
	अणु0x3814, 0x03पूर्ण,
	अणु0x3816, 0x03पूर्ण,
	अणु0x3817, 0x01पूर्ण,
	अणु0x3820, 0x8bपूर्ण,
	अणु0x3821, 0x01पूर्ण,
	अणु0x4501, 0x00पूर्ण,
	अणु0x4008, 0x02पूर्ण,
	अणु0x4009, 0x09पूर्ण,
	अणुREG_शून्य, 0x00पूर्ण
पूर्ण;

/*
 * Xclk 24Mhz
 * Pclk 45Mhz
 * linelength 672(0x2a0)
 * framelength 558(0x22e)
 * grabwinकरोw_width 640
 * grabwinकरोw_height 480
 * max_framerate 120fps
 * mipi_datarate per lane 840Mbps
 */
अटल स्थिर काष्ठा regval ov5695_640x480_regs[] = अणु
	अणु0x3501, 0x22पूर्ण,
	अणु0x366e, 0x0cपूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x08पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xa7पूर्ण,
	अणु0x3808, 0x02पूर्ण,
	अणु0x3809, 0x80पूर्ण,
	अणु0x380a, 0x01पूर्ण,
	अणु0x380b, 0xe0पूर्ण,
	अणु0x380c, 0x02पूर्ण,
	अणु0x380d, 0xa0पूर्ण,
	अणु0x380e, 0x02पूर्ण,
	अणु0x380f, 0x2eपूर्ण,
	अणु0x3811, 0x06पूर्ण,
	अणु0x3813, 0x04पूर्ण,
	अणु0x3814, 0x07पूर्ण,
	अणु0x3816, 0x05पूर्ण,
	अणु0x3817, 0x03पूर्ण,
	अणु0x3820, 0x8dपूर्ण,
	अणु0x3821, 0x01पूर्ण,
	अणु0x4501, 0x00पूर्ण,
	अणु0x4008, 0x02पूर्ण,
	अणु0x4009, 0x09पूर्ण,
	अणुREG_शून्य, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ov5695_mode supported_modes[] = अणु
	अणु
		.width = 2592,
		.height = 1944,
		.max_fps = 30,
		.exp_def = 0x0450,
		.hts_def = 0x02e4 * 4,
		.vts_def = 0x07e8,
		.reg_list = ov5695_2592x1944_regs,
	पूर्ण,
	अणु
		.width = 1920,
		.height = 1080,
		.max_fps = 30,
		.exp_def = 0x0450,
		.hts_def = 0x02a0 * 4,
		.vts_def = 0x08b8,
		.reg_list = ov5695_1920x1080_regs,
	पूर्ण,
	अणु
		.width = 1296,
		.height = 972,
		.max_fps = 60,
		.exp_def = 0x03e0,
		.hts_def = 0x02e4 * 4,
		.vts_def = 0x03f4,
		.reg_list = ov5695_1296x972_regs,
	पूर्ण,
	अणु
		.width = 1280,
		.height = 720,
		.max_fps = 30,
		.exp_def = 0x0450,
		.hts_def = 0x02a0 * 4,
		.vts_def = 0x08b8,
		.reg_list = ov5695_1280x720_regs,
	पूर्ण,
	अणु
		.width = 640,
		.height = 480,
		.max_fps = 120,
		.exp_def = 0x0450,
		.hts_def = 0x02a0 * 4,
		.vts_def = 0x022e,
		.reg_list = ov5695_640x480_regs,
	पूर्ण,
पूर्ण;

#घोषणा OV5695_LINK_FREQ_420MHZ		420000000
अटल स्थिर s64 link_freq_menu_items[] = अणु
	OV5695_LINK_FREQ_420MHZ
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov5695_test_pattern_menu[] = अणु
	"Disabled",
	"Vertical Color Bar Type 1",
	"Vertical Color Bar Type 2",
	"Vertical Color Bar Type 3",
	"Vertical Color Bar Type 4"
पूर्ण;

/* Write रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक ov5695_ग_लिखो_reg(काष्ठा i2c_client *client, u16 reg,
			    u32 len, u32 val)
अणु
	u32 buf_i, val_i;
	u8 buf[6];
	u8 *val_p;
	__be32 val_be;

	अगर (len > 4)
		वापस -EINVAL;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	val_be = cpu_to_be32(val);
	val_p = (u8 *)&val_be;
	buf_i = 2;
	val_i = 4 - len;

	जबतक (val_i < 4)
		buf[buf_i++] = val_p[val_i++];

	अगर (i2c_master_send(client, buf, len + 2) != len + 2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5695_ग_लिखो_array(काष्ठा i2c_client *client,
			      स्थिर काष्ठा regval *regs)
अणु
	u32 i;
	पूर्णांक ret = 0;

	क्रम (i = 0; ret == 0 && regs[i].addr != REG_शून्य; i++)
		ret = ov5695_ग_लिखो_reg(client, regs[i].addr,
				       OV5695_REG_VALUE_08BIT, regs[i].val);

	वापस ret;
पूर्ण

/* Read रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक ov5695_पढ़ो_reg(काष्ठा i2c_client *client, u16 reg, अचिन्हित पूर्णांक len,
			   u32 *val)
अणु
	काष्ठा i2c_msg msgs[2];
	u8 *data_be_p;
	__be32 data_be = 0;
	__be16 reg_addr_be = cpu_to_be16(reg);
	पूर्णांक ret;

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

अटल पूर्णांक ov5695_get_reso_dist(स्थिर काष्ठा ov5695_mode *mode,
				काष्ठा v4l2_mbus_framefmt *framefmt)
अणु
	वापस असल(mode->width - framefmt->width) +
	       असल(mode->height - framefmt->height);
पूर्ण

अटल स्थिर काष्ठा ov5695_mode *
ov5695_find_best_fit(काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *framefmt = &fmt->क्रमmat;
	पूर्णांक dist;
	पूर्णांक cur_best_fit = 0;
	पूर्णांक cur_best_fit_dist = -1;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(supported_modes); i++) अणु
		dist = ov5695_get_reso_dist(&supported_modes[i], framefmt);
		अगर (cur_best_fit_dist == -1 || dist < cur_best_fit_dist) अणु
			cur_best_fit_dist = dist;
			cur_best_fit = i;
		पूर्ण
	पूर्ण

	वापस &supported_modes[cur_best_fit];
पूर्ण

अटल पूर्णांक ov5695_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov5695 *ov5695 = to_ov5695(sd);
	स्थिर काष्ठा ov5695_mode *mode;
	s64 h_blank, vblank_def;

	mutex_lock(&ov5695->mutex);

	mode = ov5695_find_best_fit(fmt);
	fmt->क्रमmat.code = MEDIA_BUS_FMT_SBGGR10_1X10;
	fmt->क्रमmat.width = mode->width;
	fmt->क्रमmat.height = mode->height;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) = fmt->क्रमmat;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		ov5695->cur_mode = mode;
		h_blank = mode->hts_def - mode->width;
		__v4l2_ctrl_modअगरy_range(ov5695->hblank, h_blank,
					 h_blank, 1, h_blank);
		vblank_def = mode->vts_def - mode->height;
		__v4l2_ctrl_modअगरy_range(ov5695->vblank, vblank_def,
					 OV5695_VTS_MAX - mode->height,
					 1, vblank_def);
	पूर्ण

	mutex_unlock(&ov5695->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5695_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov5695 *ov5695 = to_ov5695(sd);
	स्थिर काष्ठा ov5695_mode *mode = ov5695->cur_mode;

	mutex_lock(&ov5695->mutex);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
#अन्यथा
		mutex_unlock(&ov5695->mutex);
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		fmt->क्रमmat.width = mode->width;
		fmt->क्रमmat.height = mode->height;
		fmt->क्रमmat.code = MEDIA_BUS_FMT_SBGGR10_1X10;
		fmt->क्रमmat.field = V4L2_FIELD_NONE;
	पूर्ण
	mutex_unlock(&ov5695->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5695_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index != 0)
		वापस -EINVAL;
	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5695_क्रमागत_frame_sizes(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	अगर (fse->code != MEDIA_BUS_FMT_SBGGR10_1X10)
		वापस -EINVAL;

	fse->min_width  = supported_modes[fse->index].width;
	fse->max_width  = supported_modes[fse->index].width;
	fse->max_height = supported_modes[fse->index].height;
	fse->min_height = supported_modes[fse->index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5695_enable_test_pattern(काष्ठा ov5695 *ov5695, u32 pattern)
अणु
	u32 val;

	अगर (pattern)
		val = (pattern - 1) | OV5695_TEST_PATTERN_ENABLE;
	अन्यथा
		val = OV5695_TEST_PATTERN_DISABLE;

	वापस ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_TEST_PATTERN,
				OV5695_REG_VALUE_08BIT, val);
पूर्ण

अटल पूर्णांक __ov5695_start_stream(काष्ठा ov5695 *ov5695)
अणु
	पूर्णांक ret;

	ret = ov5695_ग_लिखो_array(ov5695->client, ov5695_global_regs);
	अगर (ret)
		वापस ret;
	ret = ov5695_ग_लिखो_array(ov5695->client, ov5695->cur_mode->reg_list);
	अगर (ret)
		वापस ret;

	/* In हाल these controls are set beक्रमe streaming */
	ret = __v4l2_ctrl_handler_setup(&ov5695->ctrl_handler);
	अगर (ret)
		वापस ret;

	वापस ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_CTRL_MODE,
				OV5695_REG_VALUE_08BIT, OV5695_MODE_STREAMING);
पूर्ण

अटल पूर्णांक __ov5695_stop_stream(काष्ठा ov5695 *ov5695)
अणु
	वापस ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_CTRL_MODE,
				OV5695_REG_VALUE_08BIT, OV5695_MODE_SW_STANDBY);
पूर्ण

अटल पूर्णांक ov5695_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov5695 *ov5695 = to_ov5695(sd);
	काष्ठा i2c_client *client = ov5695->client;
	पूर्णांक ret = 0;

	mutex_lock(&ov5695->mutex);
	on = !!on;
	अगर (on == ov5695->streaming)
		जाओ unlock_and_वापस;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			जाओ unlock_and_वापस;
		पूर्ण

		ret = __ov5695_start_stream(ov5695);
		अगर (ret) अणु
			v4l2_err(sd, "start stream failed while write regs\n");
			pm_runसमय_put(&client->dev);
			जाओ unlock_and_वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		__ov5695_stop_stream(ov5695);
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov5695->streaming = on;

unlock_and_वापस:
	mutex_unlock(&ov5695->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __ov5695_घातer_on(काष्ठा ov5695 *ov5695)
अणु
	पूर्णांक i, ret;
	काष्ठा device *dev = &ov5695->client->dev;

	ret = clk_prepare_enable(ov5695->xvclk);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable xvclk\n");
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(ov5695->reset_gpio, 1);

	/*
	 * The hardware requires the regulators to be घातered on in order,
	 * so enable them one by one.
	 */
	क्रम (i = 0; i < OV5695_NUM_SUPPLIES; i++) अणु
		ret = regulator_enable(ov5695->supplies[i].consumer);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable %s: %d\n",
				ov5695->supplies[i].supply, ret);
			जाओ disable_reg_clk;
		पूर्ण
	पूर्ण

	gpiod_set_value_cansleep(ov5695->reset_gpio, 0);

	usleep_range(1000, 1200);

	वापस 0;

disable_reg_clk:
	क्रम (--i; i >= 0; i--)
		regulator_disable(ov5695->supplies[i].consumer);
	clk_disable_unprepare(ov5695->xvclk);

	वापस ret;
पूर्ण

अटल व्योम __ov5695_घातer_off(काष्ठा ov5695 *ov5695)
अणु
	काष्ठा device *dev = &ov5695->client->dev;
	पूर्णांक i, ret;

	clk_disable_unprepare(ov5695->xvclk);
	gpiod_set_value_cansleep(ov5695->reset_gpio, 1);

	/*
	 * The hardware requires the regulators to be घातered off in order,
	 * so disable them one by one.
	 */
	क्रम (i = OV5695_NUM_SUPPLIES - 1; i >= 0; i--) अणु
		ret = regulator_disable(ov5695->supplies[i].consumer);
		अगर (ret)
			dev_err(dev, "Failed to disable %s: %d\n",
				ov5695->supplies[i].supply, ret);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused ov5695_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov5695 *ov5695 = to_ov5695(sd);

	वापस __ov5695_घातer_on(ov5695);
पूर्ण

अटल पूर्णांक __maybe_unused ov5695_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov5695 *ov5695 = to_ov5695(sd);

	__ov5695_घातer_off(ov5695);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल पूर्णांक ov5695_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov5695 *ov5695 = to_ov5695(sd);
	काष्ठा v4l2_mbus_framefmt *try_fmt =
				v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);
	स्थिर काष्ठा ov5695_mode *def_mode = &supported_modes[0];

	mutex_lock(&ov5695->mutex);
	/* Initialize try_fmt */
	try_fmt->width = def_mode->width;
	try_fmt->height = def_mode->height;
	try_fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	try_fmt->field = V4L2_FIELD_NONE;

	mutex_unlock(&ov5695->mutex);
	/* No crop or compose */

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops ov5695_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ov5695_runसमय_suspend,
			   ov5695_runसमय_resume, शून्य)
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov5695_पूर्णांकernal_ops = अणु
	.खोलो = ov5695_खोलो,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov5695_video_ops = अणु
	.s_stream = ov5695_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov5695_pad_ops = अणु
	.क्रमागत_mbus_code = ov5695_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov5695_क्रमागत_frame_sizes,
	.get_fmt = ov5695_get_fmt,
	.set_fmt = ov5695_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov5695_subdev_ops = अणु
	.video	= &ov5695_video_ops,
	.pad	= &ov5695_pad_ops,
पूर्ण;

अटल पूर्णांक ov5695_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov5695 *ov5695 = container_of(ctrl->handler,
					     काष्ठा ov5695, ctrl_handler);
	काष्ठा i2c_client *client = ov5695->client;
	s64 max;
	पूर्णांक ret = 0;

	/* Propagate change of current control to all related controls */
	चयन (ctrl->id) अणु
	हाल V4L2_CID_VBLANK:
		/* Update max exposure जबतक meeting expected vblanking */
		max = ov5695->cur_mode->height + ctrl->val - 4;
		__v4l2_ctrl_modअगरy_range(ov5695->exposure,
					 ov5695->exposure->minimum, max,
					 ov5695->exposure->step,
					 ov5695->exposure->शेष_value);
		अवरोध;
	पूर्ण

	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		/* 4 least signअगरicant bits of expsoure are fractional part */
		ret = ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_EXPOSURE,
				       OV5695_REG_VALUE_24BIT, ctrl->val << 4);
		अवरोध;
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_ANALOG_GAIN,
				       OV5695_REG_VALUE_08BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_DIGITAL_GAIN:
		ret = ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_DIGI_GAIN_L,
				       OV5695_REG_VALUE_08BIT,
				       ctrl->val & OV5695_DIGI_GAIN_L_MASK);
		ret = ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_DIGI_GAIN_H,
				       OV5695_REG_VALUE_08BIT,
				       ctrl->val >> OV5695_DIGI_GAIN_H_SHIFT);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		ret = ov5695_ग_लिखो_reg(ov5695->client, OV5695_REG_VTS,
				       OV5695_REG_VALUE_16BIT,
				       ctrl->val + ov5695->cur_mode->height);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = ov5695_enable_test_pattern(ov5695, ctrl->val);
		अवरोध;
	शेष:
		dev_warn(&client->dev, "%s Unhandled id:0x%x, val:0x%x\n",
			 __func__, ctrl->id, ctrl->val);
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov5695_ctrl_ops = अणु
	.s_ctrl = ov5695_set_ctrl,
पूर्ण;

अटल पूर्णांक ov5695_initialize_controls(काष्ठा ov5695 *ov5695)
अणु
	स्थिर काष्ठा ov5695_mode *mode;
	काष्ठा v4l2_ctrl_handler *handler;
	काष्ठा v4l2_ctrl *ctrl;
	s64 exposure_max, vblank_def;
	u32 h_blank;
	पूर्णांक ret;

	handler = &ov5695->ctrl_handler;
	mode = ov5695->cur_mode;
	ret = v4l2_ctrl_handler_init(handler, 8);
	अगर (ret)
		वापस ret;
	handler->lock = &ov5695->mutex;

	ctrl = v4l2_ctrl_new_पूर्णांक_menu(handler, शून्य, V4L2_CID_LINK_FREQ,
				      0, 0, link_freq_menu_items);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_PIXEL_RATE,
			  0, OV5695_PIXEL_RATE, 1, OV5695_PIXEL_RATE);

	h_blank = mode->hts_def - mode->width;
	ov5695->hblank = v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_HBLANK,
				h_blank, h_blank, 1, h_blank);
	अगर (ov5695->hblank)
		ov5695->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	vblank_def = mode->vts_def - mode->height;
	ov5695->vblank = v4l2_ctrl_new_std(handler, &ov5695_ctrl_ops,
				V4L2_CID_VBLANK, vblank_def,
				OV5695_VTS_MAX - mode->height,
				1, vblank_def);

	exposure_max = mode->vts_def - 4;
	ov5695->exposure = v4l2_ctrl_new_std(handler, &ov5695_ctrl_ops,
				V4L2_CID_EXPOSURE, OV5695_EXPOSURE_MIN,
				exposure_max, OV5695_EXPOSURE_STEP,
				mode->exp_def);

	ov5695->anal_gain = v4l2_ctrl_new_std(handler, &ov5695_ctrl_ops,
				V4L2_CID_ANALOGUE_GAIN, ANALOG_GAIN_MIN,
				ANALOG_GAIN_MAX, ANALOG_GAIN_STEP,
				ANALOG_GAIN_DEFAULT);

	/* Digital gain */
	ov5695->digi_gain = v4l2_ctrl_new_std(handler, &ov5695_ctrl_ops,
				V4L2_CID_DIGITAL_GAIN, OV5695_DIGI_GAIN_MIN,
				OV5695_DIGI_GAIN_MAX, OV5695_DIGI_GAIN_STEP,
				OV5695_DIGI_GAIN_DEFAULT);

	ov5695->test_pattern = v4l2_ctrl_new_std_menu_items(handler,
				&ov5695_ctrl_ops, V4L2_CID_TEST_PATTERN,
				ARRAY_SIZE(ov5695_test_pattern_menu) - 1,
				0, 0, ov5695_test_pattern_menu);

	अगर (handler->error) अणु
		ret = handler->error;
		dev_err(&ov5695->client->dev,
			"Failed to init controls(%d)\n", ret);
		जाओ err_मुक्त_handler;
	पूर्ण

	ov5695->subdev.ctrl_handler = handler;

	वापस 0;

err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(handler);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5695_check_sensor_id(काष्ठा ov5695 *ov5695,
				  काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &ov5695->client->dev;
	u32 id = 0;
	पूर्णांक ret;

	ret = ov5695_पढ़ो_reg(client, OV5695_REG_CHIP_ID,
			      OV5695_REG_VALUE_24BIT, &id);
	अगर (id != CHIP_ID) अणु
		dev_err(dev, "Unexpected sensor id(%06x), ret(%d)\n", id, ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "Detected OV%06x sensor\n", CHIP_ID);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5695_configure_regulators(काष्ठा ov5695 *ov5695)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OV5695_NUM_SUPPLIES; i++)
		ov5695->supplies[i].supply = ov5695_supply_names[i];

	वापस devm_regulator_bulk_get(&ov5695->client->dev,
				       OV5695_NUM_SUPPLIES,
				       ov5695->supplies);
पूर्ण

अटल पूर्णांक ov5695_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ov5695 *ov5695;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	ov5695 = devm_kzalloc(dev, माप(*ov5695), GFP_KERNEL);
	अगर (!ov5695)
		वापस -ENOMEM;

	ov5695->client = client;
	ov5695->cur_mode = &supported_modes[0];

	ov5695->xvclk = devm_clk_get(dev, "xvclk");
	अगर (IS_ERR(ov5695->xvclk)) अणु
		dev_err(dev, "Failed to get xvclk\n");
		वापस -EINVAL;
	पूर्ण
	ret = clk_set_rate(ov5695->xvclk, OV5695_XVCLK_FREQ);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set xvclk rate (24MHz)\n");
		वापस ret;
	पूर्ण
	अगर (clk_get_rate(ov5695->xvclk) != OV5695_XVCLK_FREQ)
		dev_warn(dev, "xvclk mismatched, modes are based on 24MHz\n");

	ov5695->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov5695->reset_gpio)) अणु
		dev_err(dev, "Failed to get reset-gpios\n");
		वापस -EINVAL;
	पूर्ण

	ret = ov5695_configure_regulators(ov5695);
	अगर (ret) अणु
		dev_err(dev, "Failed to get power regulators\n");
		वापस ret;
	पूर्ण

	mutex_init(&ov5695->mutex);

	sd = &ov5695->subdev;
	v4l2_i2c_subdev_init(sd, client, &ov5695_subdev_ops);
	ret = ov5695_initialize_controls(ov5695);
	अगर (ret)
		जाओ err_destroy_mutex;

	ret = __ov5695_घातer_on(ov5695);
	अगर (ret)
		जाओ err_मुक्त_handler;

	ret = ov5695_check_sensor_id(ov5695, client);
	अगर (ret)
		जाओ err_घातer_off;

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	sd->पूर्णांकernal_ops = &ov5695_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
#पूर्ण_अगर
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	ov5695->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &ov5695->pad);
	अगर (ret < 0)
		जाओ err_घातer_off;
#पूर्ण_अगर

	ret = v4l2_async_रेजिस्टर_subdev_sensor(sd);
	अगर (ret) अणु
		dev_err(dev, "v4l2 async register subdev failed\n");
		जाओ err_clean_entity;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	वापस 0;

err_clean_entity:
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&sd->entity);
#पूर्ण_अगर
err_घातer_off:
	__ov5695_घातer_off(ov5695);
err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(&ov5695->ctrl_handler);
err_destroy_mutex:
	mutex_destroy(&ov5695->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5695_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov5695 *ov5695 = to_ov5695(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&sd->entity);
#पूर्ण_अगर
	v4l2_ctrl_handler_मुक्त(&ov5695->ctrl_handler);
	mutex_destroy(&ov5695->mutex);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		__ov5695_घातer_off(ov5695);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ov5695_of_match[] = अणु
	अणु .compatible = "ovti,ov5695" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov5695_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov5695_i2c_driver = अणु
	.driver = अणु
		.name = "ov5695",
		.pm = &ov5695_pm_ops,
		.of_match_table = of_match_ptr(ov5695_of_match),
	पूर्ण,
	.probe		= &ov5695_probe,
	.हटाओ		= &ov5695_हटाओ,
पूर्ण;

module_i2c_driver(ov5695_i2c_driver);

MODULE_DESCRIPTION("OmniVision ov5695 sensor driver");
MODULE_LICENSE("GPL v2");
