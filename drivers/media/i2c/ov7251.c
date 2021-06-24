<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the OV7251 camera sensor.
 *
 * Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 * Copyright (c) 2017-2018, Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा OV7251_SC_MODE_SELECT		0x0100
#घोषणा OV7251_SC_MODE_SELECT_SW_STANDBY	0x0
#घोषणा OV7251_SC_MODE_SELECT_STREAMING		0x1

#घोषणा OV7251_CHIP_ID_HIGH		0x300a
#घोषणा OV7251_CHIP_ID_HIGH_BYTE	0x77
#घोषणा OV7251_CHIP_ID_LOW		0x300b
#घोषणा OV7251_CHIP_ID_LOW_BYTE		0x50
#घोषणा OV7251_SC_GP_IO_IN1		0x3029
#घोषणा OV7251_AEC_EXPO_0		0x3500
#घोषणा OV7251_AEC_EXPO_1		0x3501
#घोषणा OV7251_AEC_EXPO_2		0x3502
#घोषणा OV7251_AEC_AGC_ADJ_0		0x350a
#घोषणा OV7251_AEC_AGC_ADJ_1		0x350b
#घोषणा OV7251_TIMING_FORMAT1		0x3820
#घोषणा OV7251_TIMING_FORMAT1_VFLIP	BIT(2)
#घोषणा OV7251_TIMING_FORMAT2		0x3821
#घोषणा OV7251_TIMING_FORMAT2_MIRROR	BIT(2)
#घोषणा OV7251_PRE_ISP_00		0x5e00
#घोषणा OV7251_PRE_ISP_00_TEST_PATTERN	BIT(7)

काष्ठा reg_value अणु
	u16 reg;
	u8 val;
पूर्ण;

काष्ठा ov7251_mode_info अणु
	u32 width;
	u32 height;
	स्थिर काष्ठा reg_value *data;
	u32 data_size;
	u32 pixel_घड़ी;
	u32 link_freq;
	u16 exposure_max;
	u16 exposure_def;
	काष्ठा v4l2_fract समयperframe;
पूर्ण;

काष्ठा ov7251 अणु
	काष्ठा i2c_client *i2c_client;
	काष्ठा device *dev;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep;
	काष्ठा v4l2_mbus_framefmt fmt;
	काष्ठा v4l2_rect crop;
	काष्ठा clk *xclk;
	u32 xclk_freq;

	काष्ठा regulator *io_regulator;
	काष्ठा regulator *core_regulator;
	काष्ठा regulator *analog_regulator;

	स्थिर काष्ठा ov7251_mode_info *current_mode;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *pixel_घड़ी;
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *gain;

	/* Cached रेजिस्टर values */
	u8 aec_pk_manual;
	u8 pre_isp_00;
	u8 timing_क्रमmat1;
	u8 timing_क्रमmat2;

	काष्ठा mutex lock; /* lock to protect घातer state, ctrls and mode */
	bool घातer_on;

	काष्ठा gpio_desc *enable_gpio;
पूर्ण;

अटल अंतरभूत काष्ठा ov7251 *to_ov7251(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov7251, sd);
पूर्ण

अटल स्थिर काष्ठा reg_value ov7251_global_init_setting[] = अणु
	अणु 0x0103, 0x01 पूर्ण,
	अणु 0x303b, 0x02 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov7251_setting_vga_30fps[] = अणु
	अणु 0x3005, 0x00 पूर्ण,
	अणु 0x3012, 0xc0 पूर्ण,
	अणु 0x3013, 0xd2 पूर्ण,
	अणु 0x3014, 0x04 पूर्ण,
	अणु 0x3016, 0xf0 पूर्ण,
	अणु 0x3017, 0xf0 पूर्ण,
	अणु 0x3018, 0xf0 पूर्ण,
	अणु 0x301a, 0xf0 पूर्ण,
	अणु 0x301b, 0xf0 पूर्ण,
	अणु 0x301c, 0xf0 पूर्ण,
	अणु 0x3023, 0x05 पूर्ण,
	अणु 0x3037, 0xf0 पूर्ण,
	अणु 0x3098, 0x04 पूर्ण, /* pll2 pre भागider */
	अणु 0x3099, 0x28 पूर्ण, /* pll2 multiplier */
	अणु 0x309a, 0x05 पूर्ण, /* pll2 sys भागider */
	अणु 0x309b, 0x04 पूर्ण, /* pll2 adc भागider */
	अणु 0x309d, 0x00 पूर्ण, /* pll2 भागider */
	अणु 0x30b0, 0x0a पूर्ण, /* pll1 pix भागider */
	अणु 0x30b1, 0x01 पूर्ण, /* pll1 भागider */
	अणु 0x30b3, 0x64 पूर्ण, /* pll1 multiplier */
	अणु 0x30b4, 0x03 पूर्ण, /* pll1 pre भागider */
	अणु 0x30b5, 0x05 पूर्ण, /* pll1 mipi भागider */
	अणु 0x3106, 0xda पूर्ण,
	अणु 0x3503, 0x07 पूर्ण,
	अणु 0x3509, 0x10 पूर्ण,
	अणु 0x3600, 0x1c पूर्ण,
	अणु 0x3602, 0x62 पूर्ण,
	अणु 0x3620, 0xb7 पूर्ण,
	अणु 0x3622, 0x04 पूर्ण,
	अणु 0x3626, 0x21 पूर्ण,
	अणु 0x3627, 0x30 पूर्ण,
	अणु 0x3630, 0x44 पूर्ण,
	अणु 0x3631, 0x35 पूर्ण,
	अणु 0x3634, 0x60 पूर्ण,
	अणु 0x3636, 0x00 पूर्ण,
	अणु 0x3662, 0x01 पूर्ण,
	अणु 0x3663, 0x70 पूर्ण,
	अणु 0x3664, 0x50 पूर्ण,
	अणु 0x3666, 0x0a पूर्ण,
	अणु 0x3669, 0x1a पूर्ण,
	अणु 0x366a, 0x00 पूर्ण,
	अणु 0x366b, 0x50 पूर्ण,
	अणु 0x3673, 0x01 पूर्ण,
	अणु 0x3674, 0xff पूर्ण,
	अणु 0x3675, 0x03 पूर्ण,
	अणु 0x3705, 0xc1 पूर्ण,
	अणु 0x3709, 0x40 पूर्ण,
	अणु 0x373c, 0x08 पूर्ण,
	अणु 0x3742, 0x00 पूर्ण,
	अणु 0x3757, 0xb3 पूर्ण,
	अणु 0x3788, 0x00 पूर्ण,
	अणु 0x37a8, 0x01 पूर्ण,
	अणु 0x37a9, 0xc0 पूर्ण,
	अणु 0x3800, 0x00 पूर्ण,
	अणु 0x3801, 0x04 पूर्ण,
	अणु 0x3802, 0x00 पूर्ण,
	अणु 0x3803, 0x04 पूर्ण,
	अणु 0x3804, 0x02 पूर्ण,
	अणु 0x3805, 0x8b पूर्ण,
	अणु 0x3806, 0x01 पूर्ण,
	अणु 0x3807, 0xeb पूर्ण,
	अणु 0x3808, 0x02 पूर्ण, /* width high */
	अणु 0x3809, 0x80 पूर्ण, /* width low */
	अणु 0x380a, 0x01 पूर्ण, /* height high */
	अणु 0x380b, 0xe0 पूर्ण, /* height low */
	अणु 0x380c, 0x03 पूर्ण, /* total horiz timing high */
	अणु 0x380d, 0xa0 पूर्ण, /* total horiz timing low */
	अणु 0x380e, 0x06 पूर्ण, /* total vertical timing high */
	अणु 0x380f, 0xbc पूर्ण, /* total vertical timing low */
	अणु 0x3810, 0x00 पूर्ण,
	अणु 0x3811, 0x04 पूर्ण,
	अणु 0x3812, 0x00 पूर्ण,
	अणु 0x3813, 0x05 पूर्ण,
	अणु 0x3814, 0x11 पूर्ण,
	अणु 0x3815, 0x11 पूर्ण,
	अणु 0x3820, 0x40 पूर्ण,
	अणु 0x3821, 0x00 पूर्ण,
	अणु 0x382f, 0x0e पूर्ण,
	अणु 0x3832, 0x00 पूर्ण,
	अणु 0x3833, 0x05 पूर्ण,
	अणु 0x3834, 0x00 पूर्ण,
	अणु 0x3835, 0x0c पूर्ण,
	अणु 0x3837, 0x00 पूर्ण,
	अणु 0x3b80, 0x00 पूर्ण,
	अणु 0x3b81, 0xa5 पूर्ण,
	अणु 0x3b82, 0x10 पूर्ण,
	अणु 0x3b83, 0x00 पूर्ण,
	अणु 0x3b84, 0x08 पूर्ण,
	अणु 0x3b85, 0x00 पूर्ण,
	अणु 0x3b86, 0x01 पूर्ण,
	अणु 0x3b87, 0x00 पूर्ण,
	अणु 0x3b88, 0x00 पूर्ण,
	अणु 0x3b89, 0x00 पूर्ण,
	अणु 0x3b8a, 0x00 पूर्ण,
	अणु 0x3b8b, 0x05 पूर्ण,
	अणु 0x3b8c, 0x00 पूर्ण,
	अणु 0x3b8d, 0x00 पूर्ण,
	अणु 0x3b8e, 0x00 पूर्ण,
	अणु 0x3b8f, 0x1a पूर्ण,
	अणु 0x3b94, 0x05 पूर्ण,
	अणु 0x3b95, 0xf2 पूर्ण,
	अणु 0x3b96, 0x40 पूर्ण,
	अणु 0x3c00, 0x89 पूर्ण,
	अणु 0x3c01, 0x63 पूर्ण,
	अणु 0x3c02, 0x01 पूर्ण,
	अणु 0x3c03, 0x00 पूर्ण,
	अणु 0x3c04, 0x00 पूर्ण,
	अणु 0x3c05, 0x03 पूर्ण,
	अणु 0x3c06, 0x00 पूर्ण,
	अणु 0x3c07, 0x06 पूर्ण,
	अणु 0x3c0c, 0x01 पूर्ण,
	अणु 0x3c0d, 0xd0 पूर्ण,
	अणु 0x3c0e, 0x02 पूर्ण,
	अणु 0x3c0f, 0x0a पूर्ण,
	अणु 0x4001, 0x42 पूर्ण,
	अणु 0x4004, 0x04 पूर्ण,
	अणु 0x4005, 0x00 पूर्ण,
	अणु 0x404e, 0x01 पूर्ण,
	अणु 0x4300, 0xff पूर्ण,
	अणु 0x4301, 0x00 पूर्ण,
	अणु 0x4315, 0x00 पूर्ण,
	अणु 0x4501, 0x48 पूर्ण,
	अणु 0x4600, 0x00 पूर्ण,
	अणु 0x4601, 0x4e पूर्ण,
	अणु 0x4801, 0x0f पूर्ण,
	अणु 0x4806, 0x0f पूर्ण,
	अणु 0x4819, 0xaa पूर्ण,
	अणु 0x4823, 0x3e पूर्ण,
	अणु 0x4837, 0x19 पूर्ण,
	अणु 0x4a0d, 0x00 पूर्ण,
	अणु 0x4a47, 0x7f पूर्ण,
	अणु 0x4a49, 0xf0 पूर्ण,
	अणु 0x4a4b, 0x30 पूर्ण,
	अणु 0x5000, 0x85 पूर्ण,
	अणु 0x5001, 0x80 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov7251_setting_vga_60fps[] = अणु
	अणु 0x3005, 0x00 पूर्ण,
	अणु 0x3012, 0xc0 पूर्ण,
	अणु 0x3013, 0xd2 पूर्ण,
	अणु 0x3014, 0x04 पूर्ण,
	अणु 0x3016, 0x10 पूर्ण,
	अणु 0x3017, 0x00 पूर्ण,
	अणु 0x3018, 0x00 पूर्ण,
	अणु 0x301a, 0x00 पूर्ण,
	अणु 0x301b, 0x00 पूर्ण,
	अणु 0x301c, 0x00 पूर्ण,
	अणु 0x3023, 0x05 पूर्ण,
	अणु 0x3037, 0xf0 पूर्ण,
	अणु 0x3098, 0x04 पूर्ण, /* pll2 pre भागider */
	अणु 0x3099, 0x28 पूर्ण, /* pll2 multiplier */
	अणु 0x309a, 0x05 पूर्ण, /* pll2 sys भागider */
	अणु 0x309b, 0x04 पूर्ण, /* pll2 adc भागider */
	अणु 0x309d, 0x00 पूर्ण, /* pll2 भागider */
	अणु 0x30b0, 0x0a पूर्ण, /* pll1 pix भागider */
	अणु 0x30b1, 0x01 पूर्ण, /* pll1 भागider */
	अणु 0x30b3, 0x64 पूर्ण, /* pll1 multiplier */
	अणु 0x30b4, 0x03 पूर्ण, /* pll1 pre भागider */
	अणु 0x30b5, 0x05 पूर्ण, /* pll1 mipi भागider */
	अणु 0x3106, 0xda पूर्ण,
	अणु 0x3503, 0x07 पूर्ण,
	अणु 0x3509, 0x10 पूर्ण,
	अणु 0x3600, 0x1c पूर्ण,
	अणु 0x3602, 0x62 पूर्ण,
	अणु 0x3620, 0xb7 पूर्ण,
	अणु 0x3622, 0x04 पूर्ण,
	अणु 0x3626, 0x21 पूर्ण,
	अणु 0x3627, 0x30 पूर्ण,
	अणु 0x3630, 0x44 पूर्ण,
	अणु 0x3631, 0x35 पूर्ण,
	अणु 0x3634, 0x60 पूर्ण,
	अणु 0x3636, 0x00 पूर्ण,
	अणु 0x3662, 0x01 पूर्ण,
	अणु 0x3663, 0x70 पूर्ण,
	अणु 0x3664, 0x50 पूर्ण,
	अणु 0x3666, 0x0a पूर्ण,
	अणु 0x3669, 0x1a पूर्ण,
	अणु 0x366a, 0x00 पूर्ण,
	अणु 0x366b, 0x50 पूर्ण,
	अणु 0x3673, 0x01 पूर्ण,
	अणु 0x3674, 0xff पूर्ण,
	अणु 0x3675, 0x03 पूर्ण,
	अणु 0x3705, 0xc1 पूर्ण,
	अणु 0x3709, 0x40 पूर्ण,
	अणु 0x373c, 0x08 पूर्ण,
	अणु 0x3742, 0x00 पूर्ण,
	अणु 0x3757, 0xb3 पूर्ण,
	अणु 0x3788, 0x00 पूर्ण,
	अणु 0x37a8, 0x01 पूर्ण,
	अणु 0x37a9, 0xc0 पूर्ण,
	अणु 0x3800, 0x00 पूर्ण,
	अणु 0x3801, 0x04 पूर्ण,
	अणु 0x3802, 0x00 पूर्ण,
	अणु 0x3803, 0x04 पूर्ण,
	अणु 0x3804, 0x02 पूर्ण,
	अणु 0x3805, 0x8b पूर्ण,
	अणु 0x3806, 0x01 पूर्ण,
	अणु 0x3807, 0xeb पूर्ण,
	अणु 0x3808, 0x02 पूर्ण, /* width high */
	अणु 0x3809, 0x80 पूर्ण, /* width low */
	अणु 0x380a, 0x01 पूर्ण, /* height high */
	अणु 0x380b, 0xe0 पूर्ण, /* height low */
	अणु 0x380c, 0x03 पूर्ण, /* total horiz timing high */
	अणु 0x380d, 0xa0 पूर्ण, /* total horiz timing low */
	अणु 0x380e, 0x03 पूर्ण, /* total vertical timing high */
	अणु 0x380f, 0x5c पूर्ण, /* total vertical timing low */
	अणु 0x3810, 0x00 पूर्ण,
	अणु 0x3811, 0x04 पूर्ण,
	अणु 0x3812, 0x00 पूर्ण,
	अणु 0x3813, 0x05 पूर्ण,
	अणु 0x3814, 0x11 पूर्ण,
	अणु 0x3815, 0x11 पूर्ण,
	अणु 0x3820, 0x40 पूर्ण,
	अणु 0x3821, 0x00 पूर्ण,
	अणु 0x382f, 0x0e पूर्ण,
	अणु 0x3832, 0x00 पूर्ण,
	अणु 0x3833, 0x05 पूर्ण,
	अणु 0x3834, 0x00 पूर्ण,
	अणु 0x3835, 0x0c पूर्ण,
	अणु 0x3837, 0x00 पूर्ण,
	अणु 0x3b80, 0x00 पूर्ण,
	अणु 0x3b81, 0xa5 पूर्ण,
	अणु 0x3b82, 0x10 पूर्ण,
	अणु 0x3b83, 0x00 पूर्ण,
	अणु 0x3b84, 0x08 पूर्ण,
	अणु 0x3b85, 0x00 पूर्ण,
	अणु 0x3b86, 0x01 पूर्ण,
	अणु 0x3b87, 0x00 पूर्ण,
	अणु 0x3b88, 0x00 पूर्ण,
	अणु 0x3b89, 0x00 पूर्ण,
	अणु 0x3b8a, 0x00 पूर्ण,
	अणु 0x3b8b, 0x05 पूर्ण,
	अणु 0x3b8c, 0x00 पूर्ण,
	अणु 0x3b8d, 0x00 पूर्ण,
	अणु 0x3b8e, 0x00 पूर्ण,
	अणु 0x3b8f, 0x1a पूर्ण,
	अणु 0x3b94, 0x05 पूर्ण,
	अणु 0x3b95, 0xf2 पूर्ण,
	अणु 0x3b96, 0x40 पूर्ण,
	अणु 0x3c00, 0x89 पूर्ण,
	अणु 0x3c01, 0x63 पूर्ण,
	अणु 0x3c02, 0x01 पूर्ण,
	अणु 0x3c03, 0x00 पूर्ण,
	अणु 0x3c04, 0x00 पूर्ण,
	अणु 0x3c05, 0x03 पूर्ण,
	अणु 0x3c06, 0x00 पूर्ण,
	अणु 0x3c07, 0x06 पूर्ण,
	अणु 0x3c0c, 0x01 पूर्ण,
	अणु 0x3c0d, 0xd0 पूर्ण,
	अणु 0x3c0e, 0x02 पूर्ण,
	अणु 0x3c0f, 0x0a पूर्ण,
	अणु 0x4001, 0x42 पूर्ण,
	अणु 0x4004, 0x04 पूर्ण,
	अणु 0x4005, 0x00 पूर्ण,
	अणु 0x404e, 0x01 पूर्ण,
	अणु 0x4300, 0xff पूर्ण,
	अणु 0x4301, 0x00 पूर्ण,
	अणु 0x4315, 0x00 पूर्ण,
	अणु 0x4501, 0x48 पूर्ण,
	अणु 0x4600, 0x00 पूर्ण,
	अणु 0x4601, 0x4e पूर्ण,
	अणु 0x4801, 0x0f पूर्ण,
	अणु 0x4806, 0x0f पूर्ण,
	अणु 0x4819, 0xaa पूर्ण,
	अणु 0x4823, 0x3e पूर्ण,
	अणु 0x4837, 0x19 पूर्ण,
	अणु 0x4a0d, 0x00 पूर्ण,
	अणु 0x4a47, 0x7f पूर्ण,
	अणु 0x4a49, 0xf0 पूर्ण,
	अणु 0x4a4b, 0x30 पूर्ण,
	अणु 0x5000, 0x85 पूर्ण,
	अणु 0x5001, 0x80 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov7251_setting_vga_90fps[] = अणु
	अणु 0x3005, 0x00 पूर्ण,
	अणु 0x3012, 0xc0 पूर्ण,
	अणु 0x3013, 0xd2 पूर्ण,
	अणु 0x3014, 0x04 पूर्ण,
	अणु 0x3016, 0x10 पूर्ण,
	अणु 0x3017, 0x00 पूर्ण,
	अणु 0x3018, 0x00 पूर्ण,
	अणु 0x301a, 0x00 पूर्ण,
	अणु 0x301b, 0x00 पूर्ण,
	अणु 0x301c, 0x00 पूर्ण,
	अणु 0x3023, 0x05 पूर्ण,
	अणु 0x3037, 0xf0 पूर्ण,
	अणु 0x3098, 0x04 पूर्ण, /* pll2 pre भागider */
	अणु 0x3099, 0x28 पूर्ण, /* pll2 multiplier */
	अणु 0x309a, 0x05 पूर्ण, /* pll2 sys भागider */
	अणु 0x309b, 0x04 पूर्ण, /* pll2 adc भागider */
	अणु 0x309d, 0x00 पूर्ण, /* pll2 भागider */
	अणु 0x30b0, 0x0a पूर्ण, /* pll1 pix भागider */
	अणु 0x30b1, 0x01 पूर्ण, /* pll1 भागider */
	अणु 0x30b3, 0x64 पूर्ण, /* pll1 multiplier */
	अणु 0x30b4, 0x03 पूर्ण, /* pll1 pre भागider */
	अणु 0x30b5, 0x05 पूर्ण, /* pll1 mipi भागider */
	अणु 0x3106, 0xda पूर्ण,
	अणु 0x3503, 0x07 पूर्ण,
	अणु 0x3509, 0x10 पूर्ण,
	अणु 0x3600, 0x1c पूर्ण,
	अणु 0x3602, 0x62 पूर्ण,
	अणु 0x3620, 0xb7 पूर्ण,
	अणु 0x3622, 0x04 पूर्ण,
	अणु 0x3626, 0x21 पूर्ण,
	अणु 0x3627, 0x30 पूर्ण,
	अणु 0x3630, 0x44 पूर्ण,
	अणु 0x3631, 0x35 पूर्ण,
	अणु 0x3634, 0x60 पूर्ण,
	अणु 0x3636, 0x00 पूर्ण,
	अणु 0x3662, 0x01 पूर्ण,
	अणु 0x3663, 0x70 पूर्ण,
	अणु 0x3664, 0x50 पूर्ण,
	अणु 0x3666, 0x0a पूर्ण,
	अणु 0x3669, 0x1a पूर्ण,
	अणु 0x366a, 0x00 पूर्ण,
	अणु 0x366b, 0x50 पूर्ण,
	अणु 0x3673, 0x01 पूर्ण,
	अणु 0x3674, 0xff पूर्ण,
	अणु 0x3675, 0x03 पूर्ण,
	अणु 0x3705, 0xc1 पूर्ण,
	अणु 0x3709, 0x40 पूर्ण,
	अणु 0x373c, 0x08 पूर्ण,
	अणु 0x3742, 0x00 पूर्ण,
	अणु 0x3757, 0xb3 पूर्ण,
	अणु 0x3788, 0x00 पूर्ण,
	अणु 0x37a8, 0x01 पूर्ण,
	अणु 0x37a9, 0xc0 पूर्ण,
	अणु 0x3800, 0x00 पूर्ण,
	अणु 0x3801, 0x04 पूर्ण,
	अणु 0x3802, 0x00 पूर्ण,
	अणु 0x3803, 0x04 पूर्ण,
	अणु 0x3804, 0x02 पूर्ण,
	अणु 0x3805, 0x8b पूर्ण,
	अणु 0x3806, 0x01 पूर्ण,
	अणु 0x3807, 0xeb पूर्ण,
	अणु 0x3808, 0x02 पूर्ण, /* width high */
	अणु 0x3809, 0x80 पूर्ण, /* width low */
	अणु 0x380a, 0x01 पूर्ण, /* height high */
	अणु 0x380b, 0xe0 पूर्ण, /* height low */
	अणु 0x380c, 0x03 पूर्ण, /* total horiz timing high */
	अणु 0x380d, 0xa0 पूर्ण, /* total horiz timing low */
	अणु 0x380e, 0x02 पूर्ण, /* total vertical timing high */
	अणु 0x380f, 0x3c पूर्ण, /* total vertical timing low */
	अणु 0x3810, 0x00 पूर्ण,
	अणु 0x3811, 0x04 पूर्ण,
	अणु 0x3812, 0x00 पूर्ण,
	अणु 0x3813, 0x05 पूर्ण,
	अणु 0x3814, 0x11 पूर्ण,
	अणु 0x3815, 0x11 पूर्ण,
	अणु 0x3820, 0x40 पूर्ण,
	अणु 0x3821, 0x00 पूर्ण,
	अणु 0x382f, 0x0e पूर्ण,
	अणु 0x3832, 0x00 पूर्ण,
	अणु 0x3833, 0x05 पूर्ण,
	अणु 0x3834, 0x00 पूर्ण,
	अणु 0x3835, 0x0c पूर्ण,
	अणु 0x3837, 0x00 पूर्ण,
	अणु 0x3b80, 0x00 पूर्ण,
	अणु 0x3b81, 0xa5 पूर्ण,
	अणु 0x3b82, 0x10 पूर्ण,
	अणु 0x3b83, 0x00 पूर्ण,
	अणु 0x3b84, 0x08 पूर्ण,
	अणु 0x3b85, 0x00 पूर्ण,
	अणु 0x3b86, 0x01 पूर्ण,
	अणु 0x3b87, 0x00 पूर्ण,
	अणु 0x3b88, 0x00 पूर्ण,
	अणु 0x3b89, 0x00 पूर्ण,
	अणु 0x3b8a, 0x00 पूर्ण,
	अणु 0x3b8b, 0x05 पूर्ण,
	अणु 0x3b8c, 0x00 पूर्ण,
	अणु 0x3b8d, 0x00 पूर्ण,
	अणु 0x3b8e, 0x00 पूर्ण,
	अणु 0x3b8f, 0x1a पूर्ण,
	अणु 0x3b94, 0x05 पूर्ण,
	अणु 0x3b95, 0xf2 पूर्ण,
	अणु 0x3b96, 0x40 पूर्ण,
	अणु 0x3c00, 0x89 पूर्ण,
	अणु 0x3c01, 0x63 पूर्ण,
	अणु 0x3c02, 0x01 पूर्ण,
	अणु 0x3c03, 0x00 पूर्ण,
	अणु 0x3c04, 0x00 पूर्ण,
	अणु 0x3c05, 0x03 पूर्ण,
	अणु 0x3c06, 0x00 पूर्ण,
	अणु 0x3c07, 0x06 पूर्ण,
	अणु 0x3c0c, 0x01 पूर्ण,
	अणु 0x3c0d, 0xd0 पूर्ण,
	अणु 0x3c0e, 0x02 पूर्ण,
	अणु 0x3c0f, 0x0a पूर्ण,
	अणु 0x4001, 0x42 पूर्ण,
	अणु 0x4004, 0x04 पूर्ण,
	अणु 0x4005, 0x00 पूर्ण,
	अणु 0x404e, 0x01 पूर्ण,
	अणु 0x4300, 0xff पूर्ण,
	अणु 0x4301, 0x00 पूर्ण,
	अणु 0x4315, 0x00 पूर्ण,
	अणु 0x4501, 0x48 पूर्ण,
	अणु 0x4600, 0x00 पूर्ण,
	अणु 0x4601, 0x4e पूर्ण,
	अणु 0x4801, 0x0f पूर्ण,
	अणु 0x4806, 0x0f पूर्ण,
	अणु 0x4819, 0xaa पूर्ण,
	अणु 0x4823, 0x3e पूर्ण,
	अणु 0x4837, 0x19 पूर्ण,
	अणु 0x4a0d, 0x00 पूर्ण,
	अणु 0x4a47, 0x7f पूर्ण,
	अणु 0x4a49, 0xf0 पूर्ण,
	अणु 0x4a4b, 0x30 पूर्ण,
	अणु 0x5000, 0x85 पूर्ण,
	अणु 0x5001, 0x80 पूर्ण,
पूर्ण;

अटल स्थिर s64 link_freq[] = अणु
	240000000,
पूर्ण;

अटल स्थिर काष्ठा ov7251_mode_info ov7251_mode_info_data[] = अणु
	अणु
		.width = 640,
		.height = 480,
		.data = ov7251_setting_vga_30fps,
		.data_size = ARRAY_SIZE(ov7251_setting_vga_30fps),
		.pixel_घड़ी = 48000000,
		.link_freq = 0, /* an index in link_freq[] */
		.exposure_max = 1704,
		.exposure_def = 504,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 3000
		पूर्ण
	पूर्ण,
	अणु
		.width = 640,
		.height = 480,
		.data = ov7251_setting_vga_60fps,
		.data_size = ARRAY_SIZE(ov7251_setting_vga_60fps),
		.pixel_घड़ी = 48000000,
		.link_freq = 0, /* an index in link_freq[] */
		.exposure_max = 840,
		.exposure_def = 504,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 6014
		पूर्ण
	पूर्ण,
	अणु
		.width = 640,
		.height = 480,
		.data = ov7251_setting_vga_90fps,
		.data_size = ARRAY_SIZE(ov7251_setting_vga_90fps),
		.pixel_घड़ी = 48000000,
		.link_freq = 0, /* an index in link_freq[] */
		.exposure_max = 552,
		.exposure_def = 504,
		.समयperframe = अणु
			.numerator = 100,
			.denominator = 9043
		पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक ov7251_regulators_enable(काष्ठा ov7251 *ov7251)
अणु
	पूर्णांक ret;

	/* OV7251 घातer up sequence requires core regulator
	 * to be enabled not earlier than io regulator
	 */

	ret = regulator_enable(ov7251->io_regulator);
	अगर (ret < 0) अणु
		dev_err(ov7251->dev, "set io voltage failed\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(ov7251->analog_regulator);
	अगर (ret) अणु
		dev_err(ov7251->dev, "set analog voltage failed\n");
		जाओ err_disable_io;
	पूर्ण

	ret = regulator_enable(ov7251->core_regulator);
	अगर (ret) अणु
		dev_err(ov7251->dev, "set core voltage failed\n");
		जाओ err_disable_analog;
	पूर्ण

	वापस 0;

err_disable_analog:
	regulator_disable(ov7251->analog_regulator);

err_disable_io:
	regulator_disable(ov7251->io_regulator);

	वापस ret;
पूर्ण

अटल व्योम ov7251_regulators_disable(काष्ठा ov7251 *ov7251)
अणु
	पूर्णांक ret;

	ret = regulator_disable(ov7251->core_regulator);
	अगर (ret < 0)
		dev_err(ov7251->dev, "core regulator disable failed\n");

	ret = regulator_disable(ov7251->analog_regulator);
	अगर (ret < 0)
		dev_err(ov7251->dev, "analog regulator disable failed\n");

	ret = regulator_disable(ov7251->io_regulator);
	अगर (ret < 0)
		dev_err(ov7251->dev, "io regulator disable failed\n");
पूर्ण

अटल पूर्णांक ov7251_ग_लिखो_reg(काष्ठा ov7251 *ov7251, u16 reg, u8 val)
अणु
	u8 regbuf[3];
	पूर्णांक ret;

	regbuf[0] = reg >> 8;
	regbuf[1] = reg & 0xff;
	regbuf[2] = val;

	ret = i2c_master_send(ov7251->i2c_client, regbuf, 3);
	अगर (ret < 0) अणु
		dev_err(ov7251->dev, "%s: write reg error %d: reg=%x, val=%x\n",
			__func__, ret, reg, val);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_ग_लिखो_seq_regs(काष्ठा ov7251 *ov7251, u16 reg, u8 *val,
				 u8 num)
अणु
	u8 regbuf[5];
	u8 nregbuf = माप(reg) + num * माप(*val);
	पूर्णांक ret = 0;

	अगर (nregbuf > माप(regbuf))
		वापस -EINVAL;

	regbuf[0] = reg >> 8;
	regbuf[1] = reg & 0xff;

	स_नकल(regbuf + 2, val, num);

	ret = i2c_master_send(ov7251->i2c_client, regbuf, nregbuf);
	अगर (ret < 0) अणु
		dev_err(ov7251->dev,
			"%s: write seq regs error %d: first reg=%x\n",
			__func__, ret, reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_पढ़ो_reg(काष्ठा ov7251 *ov7251, u16 reg, u8 *val)
अणु
	u8 regbuf[2];
	पूर्णांक ret;

	regbuf[0] = reg >> 8;
	regbuf[1] = reg & 0xff;

	ret = i2c_master_send(ov7251->i2c_client, regbuf, 2);
	अगर (ret < 0) अणु
		dev_err(ov7251->dev, "%s: write reg error %d: reg=%x\n",
			__func__, ret, reg);
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(ov7251->i2c_client, val, 1);
	अगर (ret < 0) अणु
		dev_err(ov7251->dev, "%s: read reg error %d: reg=%x\n",
			__func__, ret, reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_set_exposure(काष्ठा ov7251 *ov7251, s32 exposure)
अणु
	u16 reg;
	u8 val[3];

	reg = OV7251_AEC_EXPO_0;
	val[0] = (exposure & 0xf000) >> 12; /* goes to OV7251_AEC_EXPO_0 */
	val[1] = (exposure & 0x0ff0) >> 4;  /* goes to OV7251_AEC_EXPO_1 */
	val[2] = (exposure & 0x000f) << 4;  /* goes to OV7251_AEC_EXPO_2 */

	वापस ov7251_ग_लिखो_seq_regs(ov7251, reg, val, 3);
पूर्ण

अटल पूर्णांक ov7251_set_gain(काष्ठा ov7251 *ov7251, s32 gain)
अणु
	u16 reg;
	u8 val[2];

	reg = OV7251_AEC_AGC_ADJ_0;
	val[0] = (gain & 0x0300) >> 8; /* goes to OV7251_AEC_AGC_ADJ_0 */
	val[1] = gain & 0xff;          /* goes to OV7251_AEC_AGC_ADJ_1 */

	वापस ov7251_ग_लिखो_seq_regs(ov7251, reg, val, 2);
पूर्ण

अटल पूर्णांक ov7251_set_रेजिस्टर_array(काष्ठा ov7251 *ov7251,
				     स्थिर काष्ठा reg_value *settings,
				     अचिन्हित पूर्णांक num_settings)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_settings; ++i, ++settings) अणु
		ret = ov7251_ग_लिखो_reg(ov7251, settings->reg, settings->val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_set_घातer_on(काष्ठा ov7251 *ov7251)
अणु
	पूर्णांक ret;
	u32 रुको_us;

	ret = ov7251_regulators_enable(ov7251);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(ov7251->xclk);
	अगर (ret < 0) अणु
		dev_err(ov7251->dev, "clk prepare enable failed\n");
		ov7251_regulators_disable(ov7251);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(ov7251->enable_gpio, 1);

	/* रुको at least 65536 बाह्यal घड़ी cycles */
	रुको_us = DIV_ROUND_UP(65536 * 1000,
			       DIV_ROUND_UP(ov7251->xclk_freq, 1000));
	usleep_range(रुको_us, रुको_us + 1000);

	वापस 0;
पूर्ण

अटल व्योम ov7251_set_घातer_off(काष्ठा ov7251 *ov7251)
अणु
	clk_disable_unprepare(ov7251->xclk);
	gpiod_set_value_cansleep(ov7251->enable_gpio, 0);
	ov7251_regulators_disable(ov7251);
पूर्ण

अटल पूर्णांक ov7251_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov7251 *ov7251 = to_ov7251(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov7251->lock);

	/* If the घातer state is not modअगरied - no work to करो. */
	अगर (ov7251->घातer_on == !!on)
		जाओ निकास;

	अगर (on) अणु
		ret = ov7251_set_घातer_on(ov7251);
		अगर (ret < 0)
			जाओ निकास;

		ret = ov7251_set_रेजिस्टर_array(ov7251,
					ov7251_global_init_setting,
					ARRAY_SIZE(ov7251_global_init_setting));
		अगर (ret < 0) अणु
			dev_err(ov7251->dev, "could not set init registers\n");
			ov7251_set_घातer_off(ov7251);
			जाओ निकास;
		पूर्ण

		ov7251->घातer_on = true;
	पूर्ण अन्यथा अणु
		ov7251_set_घातer_off(ov7251);
		ov7251->घातer_on = false;
	पूर्ण

निकास:
	mutex_unlock(&ov7251->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov7251_set_hflip(काष्ठा ov7251 *ov7251, s32 value)
अणु
	u8 val = ov7251->timing_क्रमmat2;
	पूर्णांक ret;

	अगर (value)
		val |= OV7251_TIMING_FORMAT2_MIRROR;
	अन्यथा
		val &= ~OV7251_TIMING_FORMAT2_MIRROR;

	ret = ov7251_ग_लिखो_reg(ov7251, OV7251_TIMING_FORMAT2, val);
	अगर (!ret)
		ov7251->timing_क्रमmat2 = val;

	वापस ret;
पूर्ण

अटल पूर्णांक ov7251_set_vflip(काष्ठा ov7251 *ov7251, s32 value)
अणु
	u8 val = ov7251->timing_क्रमmat1;
	पूर्णांक ret;

	अगर (value)
		val |= OV7251_TIMING_FORMAT1_VFLIP;
	अन्यथा
		val &= ~OV7251_TIMING_FORMAT1_VFLIP;

	ret = ov7251_ग_लिखो_reg(ov7251, OV7251_TIMING_FORMAT1, val);
	अगर (!ret)
		ov7251->timing_क्रमmat1 = val;

	वापस ret;
पूर्ण

अटल पूर्णांक ov7251_set_test_pattern(काष्ठा ov7251 *ov7251, s32 value)
अणु
	u8 val = ov7251->pre_isp_00;
	पूर्णांक ret;

	अगर (value)
		val |= OV7251_PRE_ISP_00_TEST_PATTERN;
	अन्यथा
		val &= ~OV7251_PRE_ISP_00_TEST_PATTERN;

	ret = ov7251_ग_लिखो_reg(ov7251, OV7251_PRE_ISP_00, val);
	अगर (!ret)
		ov7251->pre_isp_00 = val;

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर ov7251_test_pattern_menu[] = अणु
	"Disabled",
	"Vertical Pattern Bars",
पूर्ण;

अटल पूर्णांक ov7251_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov7251 *ov7251 = container_of(ctrl->handler,
					     काष्ठा ov7251, ctrls);
	पूर्णांक ret;

	/* v4l2_ctrl_lock() locks our mutex */

	अगर (!ov7251->घातer_on)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		ret = ov7251_set_exposure(ov7251, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		ret = ov7251_set_gain(ov7251, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = ov7251_set_test_pattern(ov7251, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		ret = ov7251_set_hflip(ov7251, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		ret = ov7251_set_vflip(ov7251, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov7251_ctrl_ops = अणु
	.s_ctrl = ov7251_s_ctrl,
पूर्ण;

अटल पूर्णांक ov7251_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_Y10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->code != MEDIA_BUS_FMT_Y10_1X10)
		वापस -EINVAL;

	अगर (fse->index >= ARRAY_SIZE(ov7251_mode_info_data))
		वापस -EINVAL;

	fse->min_width = ov7251_mode_info_data[fse->index].width;
	fse->max_width = ov7251_mode_info_data[fse->index].width;
	fse->min_height = ov7251_mode_info_data[fse->index].height;
	fse->max_height = ov7251_mode_info_data[fse->index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_क्रमागत_frame_ival(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	अचिन्हित पूर्णांक index = fie->index;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ov7251_mode_info_data); i++) अणु
		अगर (fie->width != ov7251_mode_info_data[i].width ||
		    fie->height != ov7251_mode_info_data[i].height)
			जारी;

		अगर (index-- == 0) अणु
			fie->पूर्णांकerval = ov7251_mode_info_data[i].समयperframe;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__ov7251_get_pad_क्रमmat(काष्ठा ov7251 *ov7251,
			काष्ठा v4l2_subdev_pad_config *cfg,
			अचिन्हित पूर्णांक pad,
			क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&ov7251->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &ov7251->fmt;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ov7251_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov7251 *ov7251 = to_ov7251(sd);

	mutex_lock(&ov7251->lock);
	क्रमmat->क्रमmat = *__ov7251_get_pad_क्रमmat(ov7251, cfg, क्रमmat->pad,
						  क्रमmat->which);
	mutex_unlock(&ov7251->lock);

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_rect *
__ov7251_get_pad_crop(काष्ठा ov7251 *ov7251, काष्ठा v4l2_subdev_pad_config *cfg,
		      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&ov7251->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &ov7251->crop;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 avg_fps(स्थिर काष्ठा v4l2_fract *t)
अणु
	वापस (t->denominator + (t->numerator >> 1)) / t->numerator;
पूर्ण

अटल स्थिर काष्ठा ov7251_mode_info *
ov7251_find_mode_by_ival(काष्ठा ov7251 *ov7251, काष्ठा v4l2_fract *समयperframe)
अणु
	स्थिर काष्ठा ov7251_mode_info *mode = ov7251->current_mode;
	अचिन्हित पूर्णांक fps_req = avg_fps(समयperframe);
	अचिन्हित पूर्णांक max_dist_match = (अचिन्हित पूर्णांक) -1;
	अचिन्हित पूर्णांक i, n = 0;

	क्रम (i = 0; i < ARRAY_SIZE(ov7251_mode_info_data); i++) अणु
		अचिन्हित पूर्णांक dist;
		अचिन्हित पूर्णांक fps_पंचांगp;

		अगर (mode->width != ov7251_mode_info_data[i].width ||
		    mode->height != ov7251_mode_info_data[i].height)
			जारी;

		fps_पंचांगp = avg_fps(&ov7251_mode_info_data[i].समयperframe);

		dist = असल(fps_req - fps_पंचांगp);

		अगर (dist < max_dist_match) अणु
			n = i;
			max_dist_match = dist;
		पूर्ण
	पूर्ण

	वापस &ov7251_mode_info_data[n];
पूर्ण

अटल पूर्णांक ov7251_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov7251 *ov7251 = to_ov7251(sd);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	स्थिर काष्ठा ov7251_mode_info *new_mode;
	पूर्णांक ret = 0;

	mutex_lock(&ov7251->lock);

	__crop = __ov7251_get_pad_crop(ov7251, cfg, क्रमmat->pad, क्रमmat->which);

	new_mode = v4l2_find_nearest_size(ov7251_mode_info_data,
				ARRAY_SIZE(ov7251_mode_info_data),
				width, height,
				क्रमmat->क्रमmat.width, क्रमmat->क्रमmat.height);

	__crop->width = new_mode->width;
	__crop->height = new_mode->height;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		ret = __v4l2_ctrl_s_ctrl_पूर्णांक64(ov7251->pixel_घड़ी,
					       new_mode->pixel_घड़ी);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_s_ctrl(ov7251->link_freq,
					 new_mode->link_freq);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_modअगरy_range(ov7251->exposure,
					       1, new_mode->exposure_max,
					       1, new_mode->exposure_def);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_s_ctrl(ov7251->exposure,
					 new_mode->exposure_def);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_s_ctrl(ov7251->gain, 16);
		अगर (ret < 0)
			जाओ निकास;

		ov7251->current_mode = new_mode;
	पूर्ण

	__क्रमmat = __ov7251_get_pad_क्रमmat(ov7251, cfg, क्रमmat->pad,
					   क्रमmat->which);
	__क्रमmat->width = __crop->width;
	__क्रमmat->height = __crop->height;
	__क्रमmat->code = MEDIA_BUS_FMT_Y10_1X10;
	__क्रमmat->field = V4L2_FIELD_NONE;
	__क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;
	__क्रमmat->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(__क्रमmat->colorspace);
	__क्रमmat->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true,
				__क्रमmat->colorspace, __क्रमmat->ycbcr_enc);
	__क्रमmat->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(__क्रमmat->colorspace);

	क्रमmat->क्रमmat = *__क्रमmat;

निकास:
	mutex_unlock(&ov7251->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov7251_entity_init_cfg(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = cfg ? V4L2_SUBDEV_FORMAT_TRY
			     : V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat = अणु
			.width = 640,
			.height = 480
		पूर्ण
	पूर्ण;

	ov7251_set_क्रमmat(subdev, cfg, &fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा ov7251 *ov7251 = to_ov7251(sd);

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	mutex_lock(&ov7251->lock);
	sel->r = *__ov7251_get_pad_crop(ov7251, cfg, sel->pad,
					sel->which);
	mutex_unlock(&ov7251->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा ov7251 *ov7251 = to_ov7251(subdev);
	पूर्णांक ret;

	mutex_lock(&ov7251->lock);

	अगर (enable) अणु
		ret = ov7251_set_रेजिस्टर_array(ov7251,
					ov7251->current_mode->data,
					ov7251->current_mode->data_size);
		अगर (ret < 0) अणु
			dev_err(ov7251->dev, "could not set mode %dx%d\n",
				ov7251->current_mode->width,
				ov7251->current_mode->height);
			जाओ निकास;
		पूर्ण
		ret = __v4l2_ctrl_handler_setup(&ov7251->ctrls);
		अगर (ret < 0) अणु
			dev_err(ov7251->dev, "could not sync v4l2 controls\n");
			जाओ निकास;
		पूर्ण
		ret = ov7251_ग_लिखो_reg(ov7251, OV7251_SC_MODE_SELECT,
				       OV7251_SC_MODE_SELECT_STREAMING);
	पूर्ण अन्यथा अणु
		ret = ov7251_ग_लिखो_reg(ov7251, OV7251_SC_MODE_SELECT,
				       OV7251_SC_MODE_SELECT_SW_STANDBY);
	पूर्ण

निकास:
	mutex_unlock(&ov7251->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov7251_get_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा ov7251 *ov7251 = to_ov7251(subdev);

	mutex_lock(&ov7251->lock);
	fi->पूर्णांकerval = ov7251->current_mode->समयperframe;
	mutex_unlock(&ov7251->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ov7251_set_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा ov7251 *ov7251 = to_ov7251(subdev);
	स्थिर काष्ठा ov7251_mode_info *new_mode;
	पूर्णांक ret = 0;

	mutex_lock(&ov7251->lock);
	new_mode = ov7251_find_mode_by_ival(ov7251, &fi->पूर्णांकerval);

	अगर (new_mode != ov7251->current_mode) अणु
		ret = __v4l2_ctrl_s_ctrl_पूर्णांक64(ov7251->pixel_घड़ी,
					       new_mode->pixel_घड़ी);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_s_ctrl(ov7251->link_freq,
					 new_mode->link_freq);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_modअगरy_range(ov7251->exposure,
					       1, new_mode->exposure_max,
					       1, new_mode->exposure_def);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_s_ctrl(ov7251->exposure,
					 new_mode->exposure_def);
		अगर (ret < 0)
			जाओ निकास;

		ret = __v4l2_ctrl_s_ctrl(ov7251->gain, 16);
		अगर (ret < 0)
			जाओ निकास;

		ov7251->current_mode = new_mode;
	पूर्ण

	fi->पूर्णांकerval = ov7251->current_mode->समयperframe;

निकास:
	mutex_unlock(&ov7251->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov7251_core_ops = अणु
	.s_घातer = ov7251_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov7251_video_ops = अणु
	.s_stream = ov7251_s_stream,
	.g_frame_पूर्णांकerval = ov7251_get_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = ov7251_set_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov7251_subdev_pad_ops = अणु
	.init_cfg = ov7251_entity_init_cfg,
	.क्रमागत_mbus_code = ov7251_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov7251_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval = ov7251_क्रमागत_frame_ival,
	.get_fmt = ov7251_get_क्रमmat,
	.set_fmt = ov7251_set_क्रमmat,
	.get_selection = ov7251_get_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov7251_subdev_ops = अणु
	.core = &ov7251_core_ops,
	.video = &ov7251_video_ops,
	.pad = &ov7251_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ov7251_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा fwnode_handle *endpoपूर्णांक;
	काष्ठा ov7251 *ov7251;
	u8 chip_id_high, chip_id_low, chip_rev;
	पूर्णांक ret;

	ov7251 = devm_kzalloc(dev, माप(काष्ठा ov7251), GFP_KERNEL);
	अगर (!ov7251)
		वापस -ENOMEM;

	ov7251->i2c_client = client;
	ov7251->dev = dev;

	endpoपूर्णांक = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(dev), शून्य);
	अगर (!endpoपूर्णांक) अणु
		dev_err(dev, "endpoint node not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(endpoपूर्णांक, &ov7251->ep);
	fwnode_handle_put(endpoपूर्णांक);
	अगर (ret < 0) अणु
		dev_err(dev, "parsing endpoint node failed\n");
		वापस ret;
	पूर्ण

	अगर (ov7251->ep.bus_type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(dev, "invalid bus type (%u), must be CSI2 (%u)\n",
			ov7251->ep.bus_type, V4L2_MBUS_CSI2_DPHY);
		वापस -EINVAL;
	पूर्ण

	/* get प्रणाली घड़ी (xclk) */
	ov7251->xclk = devm_clk_get(dev, "xclk");
	अगर (IS_ERR(ov7251->xclk)) अणु
		dev_err(dev, "could not get xclk");
		वापस PTR_ERR(ov7251->xclk);
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(dev_fwnode(dev), "clock-frequency",
				       &ov7251->xclk_freq);
	अगर (ret) अणु
		dev_err(dev, "could not get xclk frequency\n");
		वापस ret;
	पूर्ण

	/* बाह्यal घड़ी must be 24MHz, allow 1% tolerance */
	अगर (ov7251->xclk_freq < 23760000 || ov7251->xclk_freq > 24240000) अणु
		dev_err(dev, "external clock frequency %u is not supported\n",
			ov7251->xclk_freq);
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_rate(ov7251->xclk, ov7251->xclk_freq);
	अगर (ret) अणु
		dev_err(dev, "could not set xclk frequency\n");
		वापस ret;
	पूर्ण

	ov7251->io_regulator = devm_regulator_get(dev, "vdddo");
	अगर (IS_ERR(ov7251->io_regulator)) अणु
		dev_err(dev, "cannot get io regulator\n");
		वापस PTR_ERR(ov7251->io_regulator);
	पूर्ण

	ov7251->core_regulator = devm_regulator_get(dev, "vddd");
	अगर (IS_ERR(ov7251->core_regulator)) अणु
		dev_err(dev, "cannot get core regulator\n");
		वापस PTR_ERR(ov7251->core_regulator);
	पूर्ण

	ov7251->analog_regulator = devm_regulator_get(dev, "vdda");
	अगर (IS_ERR(ov7251->analog_regulator)) अणु
		dev_err(dev, "cannot get analog regulator\n");
		वापस PTR_ERR(ov7251->analog_regulator);
	पूर्ण

	ov7251->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov7251->enable_gpio)) अणु
		dev_err(dev, "cannot get enable gpio\n");
		वापस PTR_ERR(ov7251->enable_gpio);
	पूर्ण

	mutex_init(&ov7251->lock);

	v4l2_ctrl_handler_init(&ov7251->ctrls, 7);
	ov7251->ctrls.lock = &ov7251->lock;

	v4l2_ctrl_new_std(&ov7251->ctrls, &ov7251_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&ov7251->ctrls, &ov7251_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);
	ov7251->exposure = v4l2_ctrl_new_std(&ov7251->ctrls, &ov7251_ctrl_ops,
					     V4L2_CID_EXPOSURE, 1, 32, 1, 32);
	ov7251->gain = v4l2_ctrl_new_std(&ov7251->ctrls, &ov7251_ctrl_ops,
					 V4L2_CID_GAIN, 16, 1023, 1, 16);
	v4l2_ctrl_new_std_menu_items(&ov7251->ctrls, &ov7251_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov7251_test_pattern_menu) - 1,
				     0, 0, ov7251_test_pattern_menu);
	ov7251->pixel_घड़ी = v4l2_ctrl_new_std(&ov7251->ctrls,
						&ov7251_ctrl_ops,
						V4L2_CID_PIXEL_RATE,
						1, पूर्णांक_उच्च, 1, 1);
	ov7251->link_freq = v4l2_ctrl_new_पूर्णांक_menu(&ov7251->ctrls,
						   &ov7251_ctrl_ops,
						   V4L2_CID_LINK_FREQ,
						   ARRAY_SIZE(link_freq) - 1,
						   0, link_freq);
	अगर (ov7251->link_freq)
		ov7251->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ov7251->sd.ctrl_handler = &ov7251->ctrls;

	अगर (ov7251->ctrls.error) अणु
		dev_err(dev, "%s: control initialization error %d\n",
			__func__, ov7251->ctrls.error);
		ret = ov7251->ctrls.error;
		जाओ मुक्त_ctrl;
	पूर्ण

	v4l2_i2c_subdev_init(&ov7251->sd, client, &ov7251_subdev_ops);
	ov7251->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov7251->pad.flags = MEDIA_PAD_FL_SOURCE;
	ov7251->sd.dev = &client->dev;
	ov7251->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&ov7251->sd.entity, 1, &ov7251->pad);
	अगर (ret < 0) अणु
		dev_err(dev, "could not register media entity\n");
		जाओ मुक्त_ctrl;
	पूर्ण

	ret = ov7251_s_घातer(&ov7251->sd, true);
	अगर (ret < 0) अणु
		dev_err(dev, "could not power up OV7251\n");
		जाओ मुक्त_entity;
	पूर्ण

	ret = ov7251_पढ़ो_reg(ov7251, OV7251_CHIP_ID_HIGH, &chip_id_high);
	अगर (ret < 0 || chip_id_high != OV7251_CHIP_ID_HIGH_BYTE) अणु
		dev_err(dev, "could not read ID high\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण
	ret = ov7251_पढ़ो_reg(ov7251, OV7251_CHIP_ID_LOW, &chip_id_low);
	अगर (ret < 0 || chip_id_low != OV7251_CHIP_ID_LOW_BYTE) अणु
		dev_err(dev, "could not read ID low\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	ret = ov7251_पढ़ो_reg(ov7251, OV7251_SC_GP_IO_IN1, &chip_rev);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read revision\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण
	chip_rev >>= 4;

	dev_info(dev, "OV7251 revision %x (%s) detected at address 0x%02x\n",
		 chip_rev,
		 chip_rev == 0x4 ? "1A / 1B" :
		 chip_rev == 0x5 ? "1C / 1D" :
		 chip_rev == 0x6 ? "1E" :
		 chip_rev == 0x7 ? "1F" : "unknown",
		 client->addr);

	ret = ov7251_पढ़ो_reg(ov7251, OV7251_PRE_ISP_00,
			      &ov7251->pre_isp_00);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read test pattern value\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	ret = ov7251_पढ़ो_reg(ov7251, OV7251_TIMING_FORMAT1,
			      &ov7251->timing_क्रमmat1);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read vflip value\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	ret = ov7251_पढ़ो_reg(ov7251, OV7251_TIMING_FORMAT2,
			      &ov7251->timing_क्रमmat2);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read hflip value\n");
		ret = -ENODEV;
		जाओ घातer_करोwn;
	पूर्ण

	ov7251_s_घातer(&ov7251->sd, false);

	ret = v4l2_async_रेजिस्टर_subdev(&ov7251->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "could not register v4l2 device\n");
		जाओ मुक्त_entity;
	पूर्ण

	ov7251_entity_init_cfg(&ov7251->sd, शून्य);

	वापस 0;

घातer_करोwn:
	ov7251_s_घातer(&ov7251->sd, false);
मुक्त_entity:
	media_entity_cleanup(&ov7251->sd.entity);
मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&ov7251->ctrls);
	mutex_destroy(&ov7251->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov7251_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov7251 *ov7251 = to_ov7251(sd);

	v4l2_async_unरेजिस्टर_subdev(&ov7251->sd);
	media_entity_cleanup(&ov7251->sd.entity);
	v4l2_ctrl_handler_मुक्त(&ov7251->ctrls);
	mutex_destroy(&ov7251->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ov7251_of_match[] = अणु
	अणु .compatible = "ovti,ov7251" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov7251_of_match);

अटल काष्ठा i2c_driver ov7251_i2c_driver = अणु
	.driver = अणु
		.of_match_table = ov7251_of_match,
		.name  = "ov7251",
	पूर्ण,
	.probe_new  = ov7251_probe,
	.हटाओ = ov7251_हटाओ,
पूर्ण;

module_i2c_driver(ov7251_i2c_driver);

MODULE_DESCRIPTION("Omnivision OV7251 Camera Driver");
MODULE_AUTHOR("Todor Tomov <todor.tomov@linaro.org>");
MODULE_LICENSE("GPL v2");
