<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the OV5645 camera sensor.
 *
 * Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015 By Tech Design S.L. All Rights Reserved.
 * Copyright (C) 2012-2013 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * Based on:
 * - the OV5645 driver from QC msm-3.10 kernel on codeaurora.org:
 *   https://us.codeaurora.org/cgit/quic/la/kernel/msm-3.10/tree/drivers/
 *       media/platक्रमm/msm/camera_v2/sensor/ov5645.c?h=LA.BR.1.2.4_rb1.41
 * - the OV5640 driver posted on linux-media:
 *   https://www.mail-archive.com/linux-media%40vger.kernel.org/msg92671.hपंचांगl
 */

/*
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा OV5645_SYSTEM_CTRL0		0x3008
#घोषणा		OV5645_SYSTEM_CTRL0_START	0x02
#घोषणा		OV5645_SYSTEM_CTRL0_STOP	0x42
#घोषणा OV5645_CHIP_ID_HIGH		0x300a
#घोषणा		OV5645_CHIP_ID_HIGH_BYTE	0x56
#घोषणा OV5645_CHIP_ID_LOW		0x300b
#घोषणा		OV5645_CHIP_ID_LOW_BYTE		0x45
#घोषणा OV5645_IO_MIPI_CTRL00		0x300e
#घोषणा OV5645_PAD_OUTPUT00		0x3019
#घोषणा OV5645_AWB_MANUAL_CONTROL	0x3406
#घोषणा		OV5645_AWB_MANUAL_ENABLE	BIT(0)
#घोषणा OV5645_AEC_PK_MANUAL		0x3503
#घोषणा		OV5645_AEC_MANUAL_ENABLE	BIT(0)
#घोषणा		OV5645_AGC_MANUAL_ENABLE	BIT(1)
#घोषणा OV5645_TIMING_TC_REG20		0x3820
#घोषणा		OV5645_SENSOR_VFLIP		BIT(1)
#घोषणा		OV5645_ISP_VFLIP		BIT(2)
#घोषणा OV5645_TIMING_TC_REG21		0x3821
#घोषणा		OV5645_SENSOR_MIRROR		BIT(1)
#घोषणा OV5645_MIPI_CTRL00		0x4800
#घोषणा OV5645_PRE_ISP_TEST_SETTING_1	0x503d
#घोषणा		OV5645_TEST_PATTERN_MASK	0x3
#घोषणा		OV5645_SET_TEST_PATTERN(x)	((x) & OV5645_TEST_PATTERN_MASK)
#घोषणा		OV5645_TEST_PATTERN_ENABLE	BIT(7)
#घोषणा OV5645_SDE_SAT_U		0x5583
#घोषणा OV5645_SDE_SAT_V		0x5584

/* regulator supplies */
अटल स्थिर अक्षर * स्थिर ov5645_supply_name[] = अणु
	"vdddo", /* Digital I/O (1.8V) supply */
	"vdda",  /* Analog (2.8V) supply */
	"vddd",  /* Digital Core (1.5V) supply */
पूर्ण;

#घोषणा OV5645_NUM_SUPPLIES ARRAY_SIZE(ov5645_supply_name)

काष्ठा reg_value अणु
	u16 reg;
	u8 val;
पूर्ण;

काष्ठा ov5645_mode_info अणु
	u32 width;
	u32 height;
	स्थिर काष्ठा reg_value *data;
	u32 data_size;
	u32 pixel_घड़ी;
	u32 link_freq;
पूर्ण;

काष्ठा ov5645 अणु
	काष्ठा i2c_client *i2c_client;
	काष्ठा device *dev;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep;
	काष्ठा v4l2_mbus_framefmt fmt;
	काष्ठा v4l2_rect crop;
	काष्ठा clk *xclk;

	काष्ठा regulator_bulk_data supplies[OV5645_NUM_SUPPLIES];

	स्थिर काष्ठा ov5645_mode_info *current_mode;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *pixel_घड़ी;
	काष्ठा v4l2_ctrl *link_freq;

	/* Cached रेजिस्टर values */
	u8 aec_pk_manual;
	u8 timing_tc_reg20;
	u8 timing_tc_reg21;

	काष्ठा mutex घातer_lock; /* lock to protect घातer state */
	पूर्णांक घातer_count;

	काष्ठा gpio_desc *enable_gpio;
	काष्ठा gpio_desc *rst_gpio;
पूर्ण;

अटल अंतरभूत काष्ठा ov5645 *to_ov5645(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov5645, sd);
पूर्ण

अटल स्थिर काष्ठा reg_value ov5645_global_init_setting[] = अणु
	अणु 0x3103, 0x11 पूर्ण,
	अणु 0x3008, 0x82 पूर्ण,
	अणु 0x3008, 0x42 पूर्ण,
	अणु 0x3103, 0x03 पूर्ण,
	अणु 0x3503, 0x07 पूर्ण,
	अणु 0x3002, 0x1c पूर्ण,
	अणु 0x3006, 0xc3 पूर्ण,
	अणु 0x3017, 0x00 पूर्ण,
	अणु 0x3018, 0x00 पूर्ण,
	अणु 0x302e, 0x0b पूर्ण,
	अणु 0x3037, 0x13 पूर्ण,
	अणु 0x3108, 0x01 पूर्ण,
	अणु 0x3611, 0x06 पूर्ण,
	अणु 0x3500, 0x00 पूर्ण,
	अणु 0x3501, 0x01 पूर्ण,
	अणु 0x3502, 0x00 पूर्ण,
	अणु 0x350a, 0x00 पूर्ण,
	अणु 0x350b, 0x3f पूर्ण,
	अणु 0x3620, 0x33 पूर्ण,
	अणु 0x3621, 0xe0 पूर्ण,
	अणु 0x3622, 0x01 पूर्ण,
	अणु 0x3630, 0x2e पूर्ण,
	अणु 0x3631, 0x00 पूर्ण,
	अणु 0x3632, 0x32 पूर्ण,
	अणु 0x3633, 0x52 पूर्ण,
	अणु 0x3634, 0x70 पूर्ण,
	अणु 0x3635, 0x13 पूर्ण,
	अणु 0x3636, 0x03 पूर्ण,
	अणु 0x3703, 0x5a पूर्ण,
	अणु 0x3704, 0xa0 पूर्ण,
	अणु 0x3705, 0x1a पूर्ण,
	अणु 0x3709, 0x12 पूर्ण,
	अणु 0x370b, 0x61 पूर्ण,
	अणु 0x370f, 0x10 पूर्ण,
	अणु 0x3715, 0x78 पूर्ण,
	अणु 0x3717, 0x01 पूर्ण,
	अणु 0x371b, 0x20 पूर्ण,
	अणु 0x3731, 0x12 पूर्ण,
	अणु 0x3901, 0x0a पूर्ण,
	अणु 0x3905, 0x02 पूर्ण,
	अणु 0x3906, 0x10 पूर्ण,
	अणु 0x3719, 0x86 पूर्ण,
	अणु 0x3810, 0x00 पूर्ण,
	अणु 0x3811, 0x10 पूर्ण,
	अणु 0x3812, 0x00 पूर्ण,
	अणु 0x3821, 0x01 पूर्ण,
	अणु 0x3824, 0x01 पूर्ण,
	अणु 0x3826, 0x03 पूर्ण,
	अणु 0x3828, 0x08 पूर्ण,
	अणु 0x3a19, 0xf8 पूर्ण,
	अणु 0x3c01, 0x34 पूर्ण,
	अणु 0x3c04, 0x28 पूर्ण,
	अणु 0x3c05, 0x98 पूर्ण,
	अणु 0x3c07, 0x07 पूर्ण,
	अणु 0x3c09, 0xc2 पूर्ण,
	अणु 0x3c0a, 0x9c पूर्ण,
	अणु 0x3c0b, 0x40 पूर्ण,
	अणु 0x3c01, 0x34 पूर्ण,
	अणु 0x4001, 0x02 पूर्ण,
	अणु 0x4514, 0x00 पूर्ण,
	अणु 0x4520, 0xb0 पूर्ण,
	अणु 0x460b, 0x37 पूर्ण,
	अणु 0x460c, 0x20 पूर्ण,
	अणु 0x4818, 0x01 पूर्ण,
	अणु 0x481d, 0xf0 पूर्ण,
	अणु 0x481f, 0x50 पूर्ण,
	अणु 0x4823, 0x70 पूर्ण,
	अणु 0x4831, 0x14 पूर्ण,
	अणु 0x5000, 0xa7 पूर्ण,
	अणु 0x5001, 0x83 पूर्ण,
	अणु 0x501d, 0x00 पूर्ण,
	अणु 0x501f, 0x00 पूर्ण,
	अणु 0x503d, 0x00 पूर्ण,
	अणु 0x505c, 0x30 पूर्ण,
	अणु 0x5181, 0x59 पूर्ण,
	अणु 0x5183, 0x00 पूर्ण,
	अणु 0x5191, 0xf0 पूर्ण,
	अणु 0x5192, 0x03 पूर्ण,
	अणु 0x5684, 0x10 पूर्ण,
	अणु 0x5685, 0xa0 पूर्ण,
	अणु 0x5686, 0x0c पूर्ण,
	अणु 0x5687, 0x78 पूर्ण,
	अणु 0x5a00, 0x08 पूर्ण,
	अणु 0x5a21, 0x00 पूर्ण,
	अणु 0x5a24, 0x00 पूर्ण,
	अणु 0x3008, 0x02 पूर्ण,
	अणु 0x3503, 0x00 पूर्ण,
	अणु 0x5180, 0xff पूर्ण,
	अणु 0x5181, 0xf2 पूर्ण,
	अणु 0x5182, 0x00 पूर्ण,
	अणु 0x5183, 0x14 पूर्ण,
	अणु 0x5184, 0x25 पूर्ण,
	अणु 0x5185, 0x24 पूर्ण,
	अणु 0x5186, 0x09 पूर्ण,
	अणु 0x5187, 0x09 पूर्ण,
	अणु 0x5188, 0x0a पूर्ण,
	अणु 0x5189, 0x75 पूर्ण,
	अणु 0x518a, 0x52 पूर्ण,
	अणु 0x518b, 0xea पूर्ण,
	अणु 0x518c, 0xa8 पूर्ण,
	अणु 0x518d, 0x42 पूर्ण,
	अणु 0x518e, 0x38 पूर्ण,
	अणु 0x518f, 0x56 पूर्ण,
	अणु 0x5190, 0x42 पूर्ण,
	अणु 0x5191, 0xf8 पूर्ण,
	अणु 0x5192, 0x04 पूर्ण,
	अणु 0x5193, 0x70 पूर्ण,
	अणु 0x5194, 0xf0 पूर्ण,
	अणु 0x5195, 0xf0 पूर्ण,
	अणु 0x5196, 0x03 पूर्ण,
	अणु 0x5197, 0x01 पूर्ण,
	अणु 0x5198, 0x04 पूर्ण,
	अणु 0x5199, 0x12 पूर्ण,
	अणु 0x519a, 0x04 पूर्ण,
	अणु 0x519b, 0x00 पूर्ण,
	अणु 0x519c, 0x06 पूर्ण,
	अणु 0x519d, 0x82 पूर्ण,
	अणु 0x519e, 0x38 पूर्ण,
	अणु 0x5381, 0x1e पूर्ण,
	अणु 0x5382, 0x5b पूर्ण,
	अणु 0x5383, 0x08 पूर्ण,
	अणु 0x5384, 0x0a पूर्ण,
	अणु 0x5385, 0x7e पूर्ण,
	अणु 0x5386, 0x88 पूर्ण,
	अणु 0x5387, 0x7c पूर्ण,
	अणु 0x5388, 0x6c पूर्ण,
	अणु 0x5389, 0x10 पूर्ण,
	अणु 0x538a, 0x01 पूर्ण,
	अणु 0x538b, 0x98 पूर्ण,
	अणु 0x5300, 0x08 पूर्ण,
	अणु 0x5301, 0x30 पूर्ण,
	अणु 0x5302, 0x10 पूर्ण,
	अणु 0x5303, 0x00 पूर्ण,
	अणु 0x5304, 0x08 पूर्ण,
	अणु 0x5305, 0x30 पूर्ण,
	अणु 0x5306, 0x08 पूर्ण,
	अणु 0x5307, 0x16 पूर्ण,
	अणु 0x5309, 0x08 पूर्ण,
	अणु 0x530a, 0x30 पूर्ण,
	अणु 0x530b, 0x04 पूर्ण,
	अणु 0x530c, 0x06 पूर्ण,
	अणु 0x5480, 0x01 पूर्ण,
	अणु 0x5481, 0x08 पूर्ण,
	अणु 0x5482, 0x14 पूर्ण,
	अणु 0x5483, 0x28 पूर्ण,
	अणु 0x5484, 0x51 पूर्ण,
	अणु 0x5485, 0x65 पूर्ण,
	अणु 0x5486, 0x71 पूर्ण,
	अणु 0x5487, 0x7d पूर्ण,
	अणु 0x5488, 0x87 पूर्ण,
	अणु 0x5489, 0x91 पूर्ण,
	अणु 0x548a, 0x9a पूर्ण,
	अणु 0x548b, 0xaa पूर्ण,
	अणु 0x548c, 0xb8 पूर्ण,
	अणु 0x548d, 0xcd पूर्ण,
	अणु 0x548e, 0xdd पूर्ण,
	अणु 0x548f, 0xea पूर्ण,
	अणु 0x5490, 0x1d पूर्ण,
	अणु 0x5580, 0x02 पूर्ण,
	अणु 0x5583, 0x40 पूर्ण,
	अणु 0x5584, 0x10 पूर्ण,
	अणु 0x5589, 0x10 पूर्ण,
	अणु 0x558a, 0x00 पूर्ण,
	अणु 0x558b, 0xf8 पूर्ण,
	अणु 0x5800, 0x3f पूर्ण,
	अणु 0x5801, 0x16 पूर्ण,
	अणु 0x5802, 0x0e पूर्ण,
	अणु 0x5803, 0x0d पूर्ण,
	अणु 0x5804, 0x17 पूर्ण,
	अणु 0x5805, 0x3f पूर्ण,
	अणु 0x5806, 0x0b पूर्ण,
	अणु 0x5807, 0x06 पूर्ण,
	अणु 0x5808, 0x04 पूर्ण,
	अणु 0x5809, 0x04 पूर्ण,
	अणु 0x580a, 0x06 पूर्ण,
	अणु 0x580b, 0x0b पूर्ण,
	अणु 0x580c, 0x09 पूर्ण,
	अणु 0x580d, 0x03 पूर्ण,
	अणु 0x580e, 0x00 पूर्ण,
	अणु 0x580f, 0x00 पूर्ण,
	अणु 0x5810, 0x03 पूर्ण,
	अणु 0x5811, 0x08 पूर्ण,
	अणु 0x5812, 0x0a पूर्ण,
	अणु 0x5813, 0x03 पूर्ण,
	अणु 0x5814, 0x00 पूर्ण,
	अणु 0x5815, 0x00 पूर्ण,
	अणु 0x5816, 0x04 पूर्ण,
	अणु 0x5817, 0x09 पूर्ण,
	अणु 0x5818, 0x0f पूर्ण,
	अणु 0x5819, 0x08 पूर्ण,
	अणु 0x581a, 0x06 पूर्ण,
	अणु 0x581b, 0x06 पूर्ण,
	अणु 0x581c, 0x08 पूर्ण,
	अणु 0x581d, 0x0c पूर्ण,
	अणु 0x581e, 0x3f पूर्ण,
	अणु 0x581f, 0x1e पूर्ण,
	अणु 0x5820, 0x12 पूर्ण,
	अणु 0x5821, 0x13 पूर्ण,
	अणु 0x5822, 0x21 पूर्ण,
	अणु 0x5823, 0x3f पूर्ण,
	अणु 0x5824, 0x68 पूर्ण,
	अणु 0x5825, 0x28 पूर्ण,
	अणु 0x5826, 0x2c पूर्ण,
	अणु 0x5827, 0x28 पूर्ण,
	अणु 0x5828, 0x08 पूर्ण,
	अणु 0x5829, 0x48 पूर्ण,
	अणु 0x582a, 0x64 पूर्ण,
	अणु 0x582b, 0x62 पूर्ण,
	अणु 0x582c, 0x64 पूर्ण,
	अणु 0x582d, 0x28 पूर्ण,
	अणु 0x582e, 0x46 पूर्ण,
	अणु 0x582f, 0x62 पूर्ण,
	अणु 0x5830, 0x60 पूर्ण,
	अणु 0x5831, 0x62 पूर्ण,
	अणु 0x5832, 0x26 पूर्ण,
	अणु 0x5833, 0x48 पूर्ण,
	अणु 0x5834, 0x66 पूर्ण,
	अणु 0x5835, 0x44 पूर्ण,
	अणु 0x5836, 0x64 पूर्ण,
	अणु 0x5837, 0x28 पूर्ण,
	अणु 0x5838, 0x66 पूर्ण,
	अणु 0x5839, 0x48 पूर्ण,
	अणु 0x583a, 0x2c पूर्ण,
	अणु 0x583b, 0x28 पूर्ण,
	अणु 0x583c, 0x26 पूर्ण,
	अणु 0x583d, 0xae पूर्ण,
	अणु 0x5025, 0x00 पूर्ण,
	अणु 0x3a0f, 0x30 पूर्ण,
	अणु 0x3a10, 0x28 पूर्ण,
	अणु 0x3a1b, 0x30 पूर्ण,
	अणु 0x3a1e, 0x26 पूर्ण,
	अणु 0x3a11, 0x60 पूर्ण,
	अणु 0x3a1f, 0x14 पूर्ण,
	अणु 0x0601, 0x02 पूर्ण,
	अणु 0x3008, 0x42 पूर्ण,
	अणु 0x3008, 0x02 पूर्ण,
	अणु OV5645_IO_MIPI_CTRL00, 0x40 पूर्ण,
	अणु OV5645_MIPI_CTRL00, 0x24 पूर्ण,
	अणु OV5645_PAD_OUTPUT00, 0x70 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5645_setting_sxga[] = अणु
	अणु 0x3612, 0xa9 पूर्ण,
	अणु 0x3614, 0x50 पूर्ण,
	अणु 0x3618, 0x00 पूर्ण,
	अणु 0x3034, 0x18 पूर्ण,
	अणु 0x3035, 0x21 पूर्ण,
	अणु 0x3036, 0x70 पूर्ण,
	अणु 0x3600, 0x09 पूर्ण,
	अणु 0x3601, 0x43 पूर्ण,
	अणु 0x3708, 0x66 पूर्ण,
	अणु 0x370c, 0xc3 पूर्ण,
	अणु 0x3800, 0x00 पूर्ण,
	अणु 0x3801, 0x00 पूर्ण,
	अणु 0x3802, 0x00 पूर्ण,
	अणु 0x3803, 0x06 पूर्ण,
	अणु 0x3804, 0x0a पूर्ण,
	अणु 0x3805, 0x3f पूर्ण,
	अणु 0x3806, 0x07 पूर्ण,
	अणु 0x3807, 0x9d पूर्ण,
	अणु 0x3808, 0x05 पूर्ण,
	अणु 0x3809, 0x00 पूर्ण,
	अणु 0x380a, 0x03 पूर्ण,
	अणु 0x380b, 0xc0 पूर्ण,
	अणु 0x380c, 0x07 पूर्ण,
	अणु 0x380d, 0x68 पूर्ण,
	अणु 0x380e, 0x03 पूर्ण,
	अणु 0x380f, 0xd8 पूर्ण,
	अणु 0x3813, 0x06 पूर्ण,
	अणु 0x3814, 0x31 पूर्ण,
	अणु 0x3815, 0x31 पूर्ण,
	अणु 0x3820, 0x47 पूर्ण,
	अणु 0x3a02, 0x03 पूर्ण,
	अणु 0x3a03, 0xd8 पूर्ण,
	अणु 0x3a08, 0x01 पूर्ण,
	अणु 0x3a09, 0xf8 पूर्ण,
	अणु 0x3a0a, 0x01 पूर्ण,
	अणु 0x3a0b, 0xa4 पूर्ण,
	अणु 0x3a0e, 0x02 पूर्ण,
	अणु 0x3a0d, 0x02 पूर्ण,
	अणु 0x3a14, 0x03 पूर्ण,
	अणु 0x3a15, 0xd8 पूर्ण,
	अणु 0x3a18, 0x00 पूर्ण,
	अणु 0x4004, 0x02 पूर्ण,
	अणु 0x4005, 0x18 पूर्ण,
	अणु 0x4300, 0x32 पूर्ण,
	अणु 0x4202, 0x00 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5645_setting_1080p[] = अणु
	अणु 0x3612, 0xab पूर्ण,
	अणु 0x3614, 0x50 पूर्ण,
	अणु 0x3618, 0x04 पूर्ण,
	अणु 0x3034, 0x18 पूर्ण,
	अणु 0x3035, 0x11 पूर्ण,
	अणु 0x3036, 0x54 पूर्ण,
	अणु 0x3600, 0x08 पूर्ण,
	अणु 0x3601, 0x33 पूर्ण,
	अणु 0x3708, 0x63 पूर्ण,
	अणु 0x370c, 0xc0 पूर्ण,
	अणु 0x3800, 0x01 पूर्ण,
	अणु 0x3801, 0x50 पूर्ण,
	अणु 0x3802, 0x01 पूर्ण,
	अणु 0x3803, 0xb2 पूर्ण,
	अणु 0x3804, 0x08 पूर्ण,
	अणु 0x3805, 0xef पूर्ण,
	अणु 0x3806, 0x05 पूर्ण,
	अणु 0x3807, 0xf1 पूर्ण,
	अणु 0x3808, 0x07 पूर्ण,
	अणु 0x3809, 0x80 पूर्ण,
	अणु 0x380a, 0x04 पूर्ण,
	अणु 0x380b, 0x38 पूर्ण,
	अणु 0x380c, 0x09 पूर्ण,
	अणु 0x380d, 0xc4 पूर्ण,
	अणु 0x380e, 0x04 पूर्ण,
	अणु 0x380f, 0x60 पूर्ण,
	अणु 0x3813, 0x04 पूर्ण,
	अणु 0x3814, 0x11 पूर्ण,
	अणु 0x3815, 0x11 पूर्ण,
	अणु 0x3820, 0x47 पूर्ण,
	अणु 0x4514, 0x88 पूर्ण,
	अणु 0x3a02, 0x04 पूर्ण,
	अणु 0x3a03, 0x60 पूर्ण,
	अणु 0x3a08, 0x01 पूर्ण,
	अणु 0x3a09, 0x50 पूर्ण,
	अणु 0x3a0a, 0x01 पूर्ण,
	अणु 0x3a0b, 0x18 पूर्ण,
	अणु 0x3a0e, 0x03 पूर्ण,
	अणु 0x3a0d, 0x04 पूर्ण,
	अणु 0x3a14, 0x04 पूर्ण,
	अणु 0x3a15, 0x60 पूर्ण,
	अणु 0x3a18, 0x00 पूर्ण,
	अणु 0x4004, 0x06 पूर्ण,
	अणु 0x4005, 0x18 पूर्ण,
	अणु 0x4300, 0x32 पूर्ण,
	अणु 0x4202, 0x00 पूर्ण,
	अणु 0x4837, 0x0b पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5645_setting_full[] = अणु
	अणु 0x3612, 0xab पूर्ण,
	अणु 0x3614, 0x50 पूर्ण,
	अणु 0x3618, 0x04 पूर्ण,
	अणु 0x3034, 0x18 पूर्ण,
	अणु 0x3035, 0x11 पूर्ण,
	अणु 0x3036, 0x54 पूर्ण,
	अणु 0x3600, 0x08 पूर्ण,
	अणु 0x3601, 0x33 पूर्ण,
	अणु 0x3708, 0x63 पूर्ण,
	अणु 0x370c, 0xc0 पूर्ण,
	अणु 0x3800, 0x00 पूर्ण,
	अणु 0x3801, 0x00 पूर्ण,
	अणु 0x3802, 0x00 पूर्ण,
	अणु 0x3803, 0x00 पूर्ण,
	अणु 0x3804, 0x0a पूर्ण,
	अणु 0x3805, 0x3f पूर्ण,
	अणु 0x3806, 0x07 पूर्ण,
	अणु 0x3807, 0x9f पूर्ण,
	अणु 0x3808, 0x0a पूर्ण,
	अणु 0x3809, 0x20 पूर्ण,
	अणु 0x380a, 0x07 पूर्ण,
	अणु 0x380b, 0x98 पूर्ण,
	अणु 0x380c, 0x0b पूर्ण,
	अणु 0x380d, 0x1c पूर्ण,
	अणु 0x380e, 0x07 पूर्ण,
	अणु 0x380f, 0xb0 पूर्ण,
	अणु 0x3813, 0x06 पूर्ण,
	अणु 0x3814, 0x11 पूर्ण,
	अणु 0x3815, 0x11 पूर्ण,
	अणु 0x3820, 0x47 पूर्ण,
	अणु 0x4514, 0x88 पूर्ण,
	अणु 0x3a02, 0x07 पूर्ण,
	अणु 0x3a03, 0xb0 पूर्ण,
	अणु 0x3a08, 0x01 पूर्ण,
	अणु 0x3a09, 0x27 पूर्ण,
	अणु 0x3a0a, 0x00 पूर्ण,
	अणु 0x3a0b, 0xf6 पूर्ण,
	अणु 0x3a0e, 0x06 पूर्ण,
	अणु 0x3a0d, 0x08 पूर्ण,
	अणु 0x3a14, 0x07 पूर्ण,
	अणु 0x3a15, 0xb0 पूर्ण,
	अणु 0x3a18, 0x01 पूर्ण,
	अणु 0x4004, 0x06 पूर्ण,
	अणु 0x4005, 0x18 पूर्ण,
	अणु 0x4300, 0x32 पूर्ण,
	अणु 0x4837, 0x0b पूर्ण,
	अणु 0x4202, 0x00 पूर्ण
पूर्ण;

अटल स्थिर s64 link_freq[] = अणु
	224000000,
	336000000
पूर्ण;

अटल स्थिर काष्ठा ov5645_mode_info ov5645_mode_info_data[] = अणु
	अणु
		.width = 1280,
		.height = 960,
		.data = ov5645_setting_sxga,
		.data_size = ARRAY_SIZE(ov5645_setting_sxga),
		.pixel_घड़ी = 112000000,
		.link_freq = 0 /* an index in link_freq[] */
	पूर्ण,
	अणु
		.width = 1920,
		.height = 1080,
		.data = ov5645_setting_1080p,
		.data_size = ARRAY_SIZE(ov5645_setting_1080p),
		.pixel_घड़ी = 168000000,
		.link_freq = 1 /* an index in link_freq[] */
	पूर्ण,
	अणु
		.width = 2592,
		.height = 1944,
		.data = ov5645_setting_full,
		.data_size = ARRAY_SIZE(ov5645_setting_full),
		.pixel_घड़ी = 168000000,
		.link_freq = 1 /* an index in link_freq[] */
	पूर्ण,
पूर्ण;

अटल पूर्णांक ov5645_ग_लिखो_reg(काष्ठा ov5645 *ov5645, u16 reg, u8 val)
अणु
	u8 regbuf[3];
	पूर्णांक ret;

	regbuf[0] = reg >> 8;
	regbuf[1] = reg & 0xff;
	regbuf[2] = val;

	ret = i2c_master_send(ov5645->i2c_client, regbuf, 3);
	अगर (ret < 0) अणु
		dev_err(ov5645->dev, "%s: write reg error %d: reg=%x, val=%x\n",
			__func__, ret, reg, val);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5645_पढ़ो_reg(काष्ठा ov5645 *ov5645, u16 reg, u8 *val)
अणु
	u8 regbuf[2];
	पूर्णांक ret;

	regbuf[0] = reg >> 8;
	regbuf[1] = reg & 0xff;

	ret = i2c_master_send(ov5645->i2c_client, regbuf, 2);
	अगर (ret < 0) अणु
		dev_err(ov5645->dev, "%s: write reg error %d: reg=%x\n",
			__func__, ret, reg);
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(ov5645->i2c_client, val, 1);
	अगर (ret < 0) अणु
		dev_err(ov5645->dev, "%s: read reg error %d: reg=%x\n",
			__func__, ret, reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5645_set_aec_mode(काष्ठा ov5645 *ov5645, u32 mode)
अणु
	u8 val = ov5645->aec_pk_manual;
	पूर्णांक ret;

	अगर (mode == V4L2_EXPOSURE_AUTO)
		val &= ~OV5645_AEC_MANUAL_ENABLE;
	अन्यथा /* V4L2_EXPOSURE_MANUAL */
		val |= OV5645_AEC_MANUAL_ENABLE;

	ret = ov5645_ग_लिखो_reg(ov5645, OV5645_AEC_PK_MANUAL, val);
	अगर (!ret)
		ov5645->aec_pk_manual = val;

	वापस ret;
पूर्ण

अटल पूर्णांक ov5645_set_agc_mode(काष्ठा ov5645 *ov5645, u32 enable)
अणु
	u8 val = ov5645->aec_pk_manual;
	पूर्णांक ret;

	अगर (enable)
		val &= ~OV5645_AGC_MANUAL_ENABLE;
	अन्यथा
		val |= OV5645_AGC_MANUAL_ENABLE;

	ret = ov5645_ग_लिखो_reg(ov5645, OV5645_AEC_PK_MANUAL, val);
	अगर (!ret)
		ov5645->aec_pk_manual = val;

	वापस ret;
पूर्ण

अटल पूर्णांक ov5645_set_रेजिस्टर_array(काष्ठा ov5645 *ov5645,
				     स्थिर काष्ठा reg_value *settings,
				     अचिन्हित पूर्णांक num_settings)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_settings; ++i, ++settings) अणु
		ret = ov5645_ग_लिखो_reg(ov5645, settings->reg, settings->val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5645_set_घातer_on(काष्ठा ov5645 *ov5645)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(OV5645_NUM_SUPPLIES, ov5645->supplies);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(ov5645->xclk);
	अगर (ret < 0) अणु
		dev_err(ov5645->dev, "clk prepare enable failed\n");
		regulator_bulk_disable(OV5645_NUM_SUPPLIES, ov5645->supplies);
		वापस ret;
	पूर्ण

	usleep_range(5000, 15000);
	gpiod_set_value_cansleep(ov5645->enable_gpio, 1);

	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ov5645->rst_gpio, 0);

	msleep(20);

	वापस 0;
पूर्ण

अटल व्योम ov5645_set_घातer_off(काष्ठा ov5645 *ov5645)
अणु
	gpiod_set_value_cansleep(ov5645->rst_gpio, 1);
	gpiod_set_value_cansleep(ov5645->enable_gpio, 0);
	clk_disable_unprepare(ov5645->xclk);
	regulator_bulk_disable(OV5645_NUM_SUPPLIES, ov5645->supplies);
पूर्ण

अटल पूर्णांक ov5645_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov5645 *ov5645 = to_ov5645(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov5645->घातer_lock);

	/* If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (ov5645->घातer_count == !on) अणु
		अगर (on) अणु
			ret = ov5645_set_घातer_on(ov5645);
			अगर (ret < 0)
				जाओ निकास;

			ret = ov5645_set_रेजिस्टर_array(ov5645,
					ov5645_global_init_setting,
					ARRAY_SIZE(ov5645_global_init_setting));
			अगर (ret < 0) अणु
				dev_err(ov5645->dev,
					"could not set init registers\n");
				ov5645_set_घातer_off(ov5645);
				जाओ निकास;
			पूर्ण

			usleep_range(500, 1000);
		पूर्ण अन्यथा अणु
			ov5645_ग_लिखो_reg(ov5645, OV5645_IO_MIPI_CTRL00, 0x58);
			ov5645_set_घातer_off(ov5645);
		पूर्ण
	पूर्ण

	/* Update the घातer count. */
	ov5645->घातer_count += on ? 1 : -1;
	WARN_ON(ov5645->घातer_count < 0);

निकास:
	mutex_unlock(&ov5645->घातer_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5645_set_saturation(काष्ठा ov5645 *ov5645, s32 value)
अणु
	u32 reg_value = (value * 0x10) + 0x40;
	पूर्णांक ret;

	ret = ov5645_ग_लिखो_reg(ov5645, OV5645_SDE_SAT_U, reg_value);
	अगर (ret < 0)
		वापस ret;

	वापस ov5645_ग_लिखो_reg(ov5645, OV5645_SDE_SAT_V, reg_value);
पूर्ण

अटल पूर्णांक ov5645_set_hflip(काष्ठा ov5645 *ov5645, s32 value)
अणु
	u8 val = ov5645->timing_tc_reg21;
	पूर्णांक ret;

	अगर (value == 0)
		val &= ~(OV5645_SENSOR_MIRROR);
	अन्यथा
		val |= (OV5645_SENSOR_MIRROR);

	ret = ov5645_ग_लिखो_reg(ov5645, OV5645_TIMING_TC_REG21, val);
	अगर (!ret)
		ov5645->timing_tc_reg21 = val;

	वापस ret;
पूर्ण

अटल पूर्णांक ov5645_set_vflip(काष्ठा ov5645 *ov5645, s32 value)
अणु
	u8 val = ov5645->timing_tc_reg20;
	पूर्णांक ret;

	अगर (value == 0)
		val |= (OV5645_SENSOR_VFLIP | OV5645_ISP_VFLIP);
	अन्यथा
		val &= ~(OV5645_SENSOR_VFLIP | OV5645_ISP_VFLIP);

	ret = ov5645_ग_लिखो_reg(ov5645, OV5645_TIMING_TC_REG20, val);
	अगर (!ret)
		ov5645->timing_tc_reg20 = val;

	वापस ret;
पूर्ण

अटल पूर्णांक ov5645_set_test_pattern(काष्ठा ov5645 *ov5645, s32 value)
अणु
	u8 val = 0;

	अगर (value) अणु
		val = OV5645_SET_TEST_PATTERN(value - 1);
		val |= OV5645_TEST_PATTERN_ENABLE;
	पूर्ण

	वापस ov5645_ग_लिखो_reg(ov5645, OV5645_PRE_ISP_TEST_SETTING_1, val);
पूर्ण

अटल स्थिर अक्षर * स्थिर ov5645_test_pattern_menu[] = अणु
	"Disabled",
	"Vertical Color Bars",
	"Pseudo-Random Data",
	"Color Square",
	"Black Image",
पूर्ण;

अटल पूर्णांक ov5645_set_awb(काष्ठा ov5645 *ov5645, s32 enable_स्वतः)
अणु
	u8 val = 0;

	अगर (!enable_स्वतः)
		val = OV5645_AWB_MANUAL_ENABLE;

	वापस ov5645_ग_लिखो_reg(ov5645, OV5645_AWB_MANUAL_CONTROL, val);
पूर्ण

अटल पूर्णांक ov5645_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov5645 *ov5645 = container_of(ctrl->handler,
					     काष्ठा ov5645, ctrls);
	पूर्णांक ret;

	mutex_lock(&ov5645->घातer_lock);
	अगर (!ov5645->घातer_count) अणु
		mutex_unlock(&ov5645->घातer_lock);
		वापस 0;
	पूर्ण

	चयन (ctrl->id) अणु
	हाल V4L2_CID_SATURATION:
		ret = ov5645_set_saturation(ov5645, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov5645_set_awb(ov5645, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		ret = ov5645_set_agc_mode(ov5645, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov5645_set_aec_mode(ov5645, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = ov5645_set_test_pattern(ov5645, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		ret = ov5645_set_hflip(ov5645, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		ret = ov5645_set_vflip(ov5645, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&ov5645->घातer_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov5645_ctrl_ops = अणु
	.s_ctrl = ov5645_s_ctrl,
पूर्ण;

अटल पूर्णांक ov5645_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5645_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->code != MEDIA_BUS_FMT_UYVY8_2X8)
		वापस -EINVAL;

	अगर (fse->index >= ARRAY_SIZE(ov5645_mode_info_data))
		वापस -EINVAL;

	fse->min_width = ov5645_mode_info_data[fse->index].width;
	fse->max_width = ov5645_mode_info_data[fse->index].width;
	fse->min_height = ov5645_mode_info_data[fse->index].height;
	fse->max_height = ov5645_mode_info_data[fse->index].height;

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__ov5645_get_pad_क्रमmat(काष्ठा ov5645 *ov5645,
			काष्ठा v4l2_subdev_pad_config *cfg,
			अचिन्हित पूर्णांक pad,
			क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&ov5645->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &ov5645->fmt;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ov5645_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov5645 *ov5645 = to_ov5645(sd);

	क्रमmat->क्रमmat = *__ov5645_get_pad_क्रमmat(ov5645, cfg, क्रमmat->pad,
						  क्रमmat->which);
	वापस 0;
पूर्ण

अटल काष्ठा v4l2_rect *
__ov5645_get_pad_crop(काष्ठा ov5645 *ov5645, काष्ठा v4l2_subdev_pad_config *cfg,
		      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&ov5645->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &ov5645->crop;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ov5645_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov5645 *ov5645 = to_ov5645(sd);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	स्थिर काष्ठा ov5645_mode_info *new_mode;
	पूर्णांक ret;

	__crop = __ov5645_get_pad_crop(ov5645, cfg, क्रमmat->pad,
			क्रमmat->which);

	new_mode = v4l2_find_nearest_size(ov5645_mode_info_data,
			       ARRAY_SIZE(ov5645_mode_info_data),
			       width, height,
			       क्रमmat->क्रमmat.width, क्रमmat->क्रमmat.height);

	__crop->width = new_mode->width;
	__crop->height = new_mode->height;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		ret = v4l2_ctrl_s_ctrl_पूर्णांक64(ov5645->pixel_घड़ी,
					     new_mode->pixel_घड़ी);
		अगर (ret < 0)
			वापस ret;

		ret = v4l2_ctrl_s_ctrl(ov5645->link_freq,
				       new_mode->link_freq);
		अगर (ret < 0)
			वापस ret;

		ov5645->current_mode = new_mode;
	पूर्ण

	__क्रमmat = __ov5645_get_pad_क्रमmat(ov5645, cfg, क्रमmat->pad,
			क्रमmat->which);
	__क्रमmat->width = __crop->width;
	__क्रमmat->height = __crop->height;
	__क्रमmat->code = MEDIA_BUS_FMT_UYVY8_2X8;
	__क्रमmat->field = V4L2_FIELD_NONE;
	__क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	क्रमmat->क्रमmat = *__क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5645_entity_init_cfg(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु 0 पूर्ण;

	fmt.which = cfg ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	fmt.क्रमmat.width = 1920;
	fmt.क्रमmat.height = 1080;

	ov5645_set_क्रमmat(subdev, cfg, &fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5645_get_selection(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ov5645 *ov5645 = to_ov5645(sd);

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	sel->r = *__ov5645_get_pad_crop(ov5645, cfg, sel->pad,
					sel->which);
	वापस 0;
पूर्ण

अटल पूर्णांक ov5645_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा ov5645 *ov5645 = to_ov5645(subdev);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = ov5645_set_रेजिस्टर_array(ov5645,
					ov5645->current_mode->data,
					ov5645->current_mode->data_size);
		अगर (ret < 0) अणु
			dev_err(ov5645->dev, "could not set mode %dx%d\n",
				ov5645->current_mode->width,
				ov5645->current_mode->height);
			वापस ret;
		पूर्ण
		ret = v4l2_ctrl_handler_setup(&ov5645->ctrls);
		अगर (ret < 0) अणु
			dev_err(ov5645->dev, "could not sync v4l2 controls\n");
			वापस ret;
		पूर्ण

		ret = ov5645_ग_लिखो_reg(ov5645, OV5645_IO_MIPI_CTRL00, 0x45);
		अगर (ret < 0)
			वापस ret;

		ret = ov5645_ग_लिखो_reg(ov5645, OV5645_SYSTEM_CTRL0,
				       OV5645_SYSTEM_CTRL0_START);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = ov5645_ग_लिखो_reg(ov5645, OV5645_IO_MIPI_CTRL00, 0x40);
		अगर (ret < 0)
			वापस ret;

		ret = ov5645_ग_लिखो_reg(ov5645, OV5645_SYSTEM_CTRL0,
				       OV5645_SYSTEM_CTRL0_STOP);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov5645_core_ops = अणु
	.s_घातer = ov5645_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov5645_video_ops = अणु
	.s_stream = ov5645_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov5645_subdev_pad_ops = अणु
	.init_cfg = ov5645_entity_init_cfg,
	.क्रमागत_mbus_code = ov5645_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov5645_क्रमागत_frame_size,
	.get_fmt = ov5645_get_क्रमmat,
	.set_fmt = ov5645_set_क्रमmat,
	.get_selection = ov5645_get_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov5645_subdev_ops = अणु
	.core = &ov5645_core_ops,
	.video = &ov5645_video_ops,
	.pad = &ov5645_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ov5645_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *endpoपूर्णांक;
	काष्ठा ov5645 *ov5645;
	u8 chip_id_high, chip_id_low;
	अचिन्हित पूर्णांक i;
	u32 xclk_freq;
	पूर्णांक ret;

	ov5645 = devm_kzalloc(dev, माप(काष्ठा ov5645), GFP_KERNEL);
	अगर (!ov5645)
		वापस -ENOMEM;

	ov5645->i2c_client = client;
	ov5645->dev = dev;

	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(dev->of_node, शून्य);
	अगर (!endpoपूर्णांक) अणु
		dev_err(dev, "endpoint node not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(endpoपूर्णांक),
					 &ov5645->ep);

	of_node_put(endpoपूर्णांक);

	अगर (ret < 0) अणु
		dev_err(dev, "parsing endpoint node failed\n");
		वापस ret;
	पूर्ण

	अगर (ov5645->ep.bus_type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(dev, "invalid bus type, must be CSI2\n");
		वापस -EINVAL;
	पूर्ण

	/* get प्रणाली घड़ी (xclk) */
	ov5645->xclk = devm_clk_get(dev, "xclk");
	अगर (IS_ERR(ov5645->xclk)) अणु
		dev_err(dev, "could not get xclk");
		वापस PTR_ERR(ov5645->xclk);
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "clock-frequency", &xclk_freq);
	अगर (ret) अणु
		dev_err(dev, "could not get xclk frequency\n");
		वापस ret;
	पूर्ण

	/* बाह्यal घड़ी must be 24MHz, allow 1% tolerance */
	अगर (xclk_freq < 23760000 || xclk_freq > 24240000) अणु
		dev_err(dev, "external clock frequency %u is not supported\n",
			xclk_freq);
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_rate(ov5645->xclk, xclk_freq);
	अगर (ret) अणु
		dev_err(dev, "could not set xclk frequency\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < OV5645_NUM_SUPPLIES; i++)
		ov5645->supplies[i].supply = ov5645_supply_name[i];

	ret = devm_regulator_bulk_get(dev, OV5645_NUM_SUPPLIES,
				      ov5645->supplies);
	अगर (ret < 0)
		वापस ret;

	ov5645->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov5645->enable_gpio)) अणु
		dev_err(dev, "cannot get enable gpio\n");
		वापस PTR_ERR(ov5645->enable_gpio);
	पूर्ण

	ov5645->rst_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov5645->rst_gpio)) अणु
		dev_err(dev, "cannot get reset gpio\n");
		वापस PTR_ERR(ov5645->rst_gpio);
	पूर्ण

	mutex_init(&ov5645->घातer_lock);

	v4l2_ctrl_handler_init(&ov5645->ctrls, 9);
	v4l2_ctrl_new_std(&ov5645->ctrls, &ov5645_ctrl_ops,
			  V4L2_CID_SATURATION, -4, 4, 1, 0);
	v4l2_ctrl_new_std(&ov5645->ctrls, &ov5645_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&ov5645->ctrls, &ov5645_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&ov5645->ctrls, &ov5645_ctrl_ops,
			  V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&ov5645->ctrls, &ov5645_ctrl_ops,
			  V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	v4l2_ctrl_new_std_menu(&ov5645->ctrls, &ov5645_ctrl_ops,
			       V4L2_CID_EXPOSURE_AUTO, V4L2_EXPOSURE_MANUAL,
			       0, V4L2_EXPOSURE_AUTO);
	v4l2_ctrl_new_std_menu_items(&ov5645->ctrls, &ov5645_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov5645_test_pattern_menu) - 1,
				     0, 0, ov5645_test_pattern_menu);
	ov5645->pixel_घड़ी = v4l2_ctrl_new_std(&ov5645->ctrls,
						&ov5645_ctrl_ops,
						V4L2_CID_PIXEL_RATE,
						1, पूर्णांक_उच्च, 1, 1);
	ov5645->link_freq = v4l2_ctrl_new_पूर्णांक_menu(&ov5645->ctrls,
						   &ov5645_ctrl_ops,
						   V4L2_CID_LINK_FREQ,
						   ARRAY_SIZE(link_freq) - 1,
						   0, link_freq);
	अगर (ov5645->link_freq)
		ov5645->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ov5645->sd.ctrl_handler = &ov5645->ctrls;

	अगर (ov5645->ctrls.error) अणु
		dev_err(dev, "%s: control initialization error %d\n",
		       __func__, ov5645->ctrls.error);
		ret = ov5645->ctrls.error;
		जाओ मुक्त_ctrl;
	पूर्ण

	v4l2_i2c_subdev_init(&ov5645->sd, client, &ov5645_subdev_ops);
	ov5645->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov5645->pad.flags = MEDIA_PAD_FL_SOURCE;
	ov5645->sd.dev = &client->dev;
	ov5645->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&ov5645->sd.entity, 1, &ov5645->pad);
	अगर (ret < 0) अणु
		dev_err(dev, "could not register media entity\n");
		जाओ मुक्त_ctrl;
	पूर्ण

	ret = ov5645_s_घातer(&ov5645->sd, true);
	अगर (ret < 0) अणु
		dev_err(dev, "could not power up OV5645\n");
		जाओ मुक्त_entity;
	पूर्ण

	ret = ov5645_पढ़ो_reg(ov5645, OV5645_CHIP_ID_HIGH, &chip_id_high);
	अगर (ret < 0 || chip_id_high != OV5645_CHIP_ID_HIGH_BYTE) अणु
		dev_err(dev, "could not read ID high\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण
	ret = ov5645_पढ़ो_reg(ov5645, OV5645_CHIP_ID_LOW, &chip_id_low);
	अगर (ret < 0 || chip_id_low != OV5645_CHIP_ID_LOW_BYTE) अणु
		dev_err(dev, "could not read ID low\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	dev_info(dev, "OV5645 detected at address 0x%02x\n", client->addr);

	ret = ov5645_पढ़ो_reg(ov5645, OV5645_AEC_PK_MANUAL,
			      &ov5645->aec_pk_manual);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read AEC/AGC mode\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	ret = ov5645_पढ़ो_reg(ov5645, OV5645_TIMING_TC_REG20,
			      &ov5645->timing_tc_reg20);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read vflip value\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	ret = ov5645_पढ़ो_reg(ov5645, OV5645_TIMING_TC_REG21,
			      &ov5645->timing_tc_reg21);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read hflip value\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	ov5645_s_घातer(&ov5645->sd, false);

	ret = v4l2_async_रेजिस्टर_subdev(&ov5645->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "could not register v4l2 device\n");
		जाओ मुक्त_entity;
	पूर्ण

	ov5645_entity_init_cfg(&ov5645->sd, शून्य);

	वापस 0;

घातer_करोwn:
	ov5645_s_घातer(&ov5645->sd, false);
मुक्त_entity:
	media_entity_cleanup(&ov5645->sd.entity);
मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&ov5645->ctrls);
	mutex_destroy(&ov5645->घातer_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5645_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov5645 *ov5645 = to_ov5645(sd);

	v4l2_async_unरेजिस्टर_subdev(&ov5645->sd);
	media_entity_cleanup(&ov5645->sd.entity);
	v4l2_ctrl_handler_मुक्त(&ov5645->ctrls);
	mutex_destroy(&ov5645->घातer_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov5645_id[] = अणु
	अणु "ov5645", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov5645_id);

अटल स्थिर काष्ठा of_device_id ov5645_of_match[] = अणु
	अणु .compatible = "ovti,ov5645" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov5645_of_match);

अटल काष्ठा i2c_driver ov5645_i2c_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(ov5645_of_match),
		.name  = "ov5645",
	पूर्ण,
	.probe_new = ov5645_probe,
	.हटाओ = ov5645_हटाओ,
	.id_table = ov5645_id,
पूर्ण;

module_i2c_driver(ov5645_i2c_driver);

MODULE_DESCRIPTION("Omnivision OV5645 Camera Driver");
MODULE_AUTHOR("Todor Tomov <todor.tomov@linaro.org>");
MODULE_LICENSE("GPL v2");
