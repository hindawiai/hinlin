<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011-2013 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2014-2017 Mentor Graphics Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

/* min/typical/max प्रणाली घड़ी (xclk) frequencies */
#घोषणा OV5640_XCLK_MIN  6000000
#घोषणा OV5640_XCLK_MAX 54000000

#घोषणा OV5640_DEFAULT_SLAVE_ID 0x3c

#घोषणा OV5640_REG_SYS_RESET02		0x3002
#घोषणा OV5640_REG_SYS_CLOCK_ENABLE02	0x3006
#घोषणा OV5640_REG_SYS_CTRL0		0x3008
#घोषणा OV5640_REG_SYS_CTRL0_SW_PWDN	0x42
#घोषणा OV5640_REG_SYS_CTRL0_SW_PWUP	0x02
#घोषणा OV5640_REG_CHIP_ID		0x300a
#घोषणा OV5640_REG_IO_MIPI_CTRL00	0x300e
#घोषणा OV5640_REG_PAD_OUTPUT_ENABLE01	0x3017
#घोषणा OV5640_REG_PAD_OUTPUT_ENABLE02	0x3018
#घोषणा OV5640_REG_PAD_OUTPUT00		0x3019
#घोषणा OV5640_REG_SYSTEM_CONTROL1	0x302e
#घोषणा OV5640_REG_SC_PLL_CTRL0		0x3034
#घोषणा OV5640_REG_SC_PLL_CTRL1		0x3035
#घोषणा OV5640_REG_SC_PLL_CTRL2		0x3036
#घोषणा OV5640_REG_SC_PLL_CTRL3		0x3037
#घोषणा OV5640_REG_SLAVE_ID		0x3100
#घोषणा OV5640_REG_SCCB_SYS_CTRL1	0x3103
#घोषणा OV5640_REG_SYS_ROOT_DIVIDER	0x3108
#घोषणा OV5640_REG_AWB_R_GAIN		0x3400
#घोषणा OV5640_REG_AWB_G_GAIN		0x3402
#घोषणा OV5640_REG_AWB_B_GAIN		0x3404
#घोषणा OV5640_REG_AWB_MANUAL_CTRL	0x3406
#घोषणा OV5640_REG_AEC_PK_EXPOSURE_HI	0x3500
#घोषणा OV5640_REG_AEC_PK_EXPOSURE_MED	0x3501
#घोषणा OV5640_REG_AEC_PK_EXPOSURE_LO	0x3502
#घोषणा OV5640_REG_AEC_PK_MANUAL	0x3503
#घोषणा OV5640_REG_AEC_PK_REAL_GAIN	0x350a
#घोषणा OV5640_REG_AEC_PK_VTS		0x350c
#घोषणा OV5640_REG_TIMING_DVPHO		0x3808
#घोषणा OV5640_REG_TIMING_DVPVO		0x380a
#घोषणा OV5640_REG_TIMING_HTS		0x380c
#घोषणा OV5640_REG_TIMING_VTS		0x380e
#घोषणा OV5640_REG_TIMING_TC_REG20	0x3820
#घोषणा OV5640_REG_TIMING_TC_REG21	0x3821
#घोषणा OV5640_REG_AEC_CTRL00		0x3a00
#घोषणा OV5640_REG_AEC_B50_STEP		0x3a08
#घोषणा OV5640_REG_AEC_B60_STEP		0x3a0a
#घोषणा OV5640_REG_AEC_CTRL0D		0x3a0d
#घोषणा OV5640_REG_AEC_CTRL0E		0x3a0e
#घोषणा OV5640_REG_AEC_CTRL0F		0x3a0f
#घोषणा OV5640_REG_AEC_CTRL10		0x3a10
#घोषणा OV5640_REG_AEC_CTRL11		0x3a11
#घोषणा OV5640_REG_AEC_CTRL1B		0x3a1b
#घोषणा OV5640_REG_AEC_CTRL1E		0x3a1e
#घोषणा OV5640_REG_AEC_CTRL1F		0x3a1f
#घोषणा OV5640_REG_HZ5060_CTRL00	0x3c00
#घोषणा OV5640_REG_HZ5060_CTRL01	0x3c01
#घोषणा OV5640_REG_SIGMADELTA_CTRL0C	0x3c0c
#घोषणा OV5640_REG_FRAME_CTRL01		0x4202
#घोषणा OV5640_REG_FORMAT_CONTROL00	0x4300
#घोषणा OV5640_REG_VFIFO_HSIZE		0x4602
#घोषणा OV5640_REG_VFIFO_VSIZE		0x4604
#घोषणा OV5640_REG_JPG_MODE_SELECT	0x4713
#घोषणा OV5640_REG_CCIR656_CTRL00	0x4730
#घोषणा OV5640_REG_POLARITY_CTRL00	0x4740
#घोषणा OV5640_REG_MIPI_CTRL00		0x4800
#घोषणा OV5640_REG_DEBUG_MODE		0x4814
#घोषणा OV5640_REG_ISP_FORMAT_MUX_CTRL	0x501f
#घोषणा OV5640_REG_PRE_ISP_TEST_SET1	0x503d
#घोषणा OV5640_REG_SDE_CTRL0		0x5580
#घोषणा OV5640_REG_SDE_CTRL1		0x5581
#घोषणा OV5640_REG_SDE_CTRL3		0x5583
#घोषणा OV5640_REG_SDE_CTRL4		0x5584
#घोषणा OV5640_REG_SDE_CTRL5		0x5585
#घोषणा OV5640_REG_AVG_READOUT		0x56a1

क्रमागत ov5640_mode_id अणु
	OV5640_MODE_QQVGA_160_120 = 0,
	OV5640_MODE_QCIF_176_144,
	OV5640_MODE_QVGA_320_240,
	OV5640_MODE_VGA_640_480,
	OV5640_MODE_NTSC_720_480,
	OV5640_MODE_PAL_720_576,
	OV5640_MODE_XGA_1024_768,
	OV5640_MODE_720P_1280_720,
	OV5640_MODE_1080P_1920_1080,
	OV5640_MODE_QSXGA_2592_1944,
	OV5640_NUM_MODES,
पूर्ण;

क्रमागत ov5640_frame_rate अणु
	OV5640_15_FPS = 0,
	OV5640_30_FPS,
	OV5640_60_FPS,
	OV5640_NUM_FRAMERATES,
पूर्ण;

क्रमागत ov5640_क्रमmat_mux अणु
	OV5640_FMT_MUX_YUV422 = 0,
	OV5640_FMT_MUX_RGB,
	OV5640_FMT_MUX_DITHER,
	OV5640_FMT_MUX_RAW_DPC,
	OV5640_FMT_MUX_SNR_RAW,
	OV5640_FMT_MUX_RAW_CIP,
पूर्ण;

काष्ठा ov5640_pixfmt अणु
	u32 code;
	u32 colorspace;
पूर्ण;

अटल स्थिर काष्ठा ov5640_pixfmt ov5640_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_JPEG_1X8, V4L2_COLORSPACE_JPEG, पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_COLORSPACE_SRGB, पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_COLORSPACE_SRGB, पूर्ण,
	अणु MEDIA_BUS_FMT_RGB565_2X8_LE, V4L2_COLORSPACE_SRGB, पूर्ण,
	अणु MEDIA_BUS_FMT_RGB565_2X8_BE, V4L2_COLORSPACE_SRGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, V4L2_COLORSPACE_SRGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, V4L2_COLORSPACE_SRGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, V4L2_COLORSPACE_SRGB, पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, V4L2_COLORSPACE_SRGB, पूर्ण,
पूर्ण;

/*
 * FIXME: हटाओ this when a subdev API becomes available
 * to set the MIPI CSI-2 भव channel.
 */
अटल अचिन्हित पूर्णांक भव_channel;
module_param(भव_channel, uपूर्णांक, 0444);
MODULE_PARM_DESC(भव_channel,
		 "MIPI CSI-2 virtual channel (0..3), default 0");

अटल स्थिर पूर्णांक ov5640_framerates[] = अणु
	[OV5640_15_FPS] = 15,
	[OV5640_30_FPS] = 30,
	[OV5640_60_FPS] = 60,
पूर्ण;

/* regulator supplies */
अटल स्थिर अक्षर * स्थिर ov5640_supply_name[] = अणु
	"DOVDD", /* Digital I/O (1.8V) supply */
	"AVDD",  /* Analog (2.8V) supply */
	"DVDD",  /* Digital Core (1.5V) supply */
पूर्ण;

#घोषणा OV5640_NUM_SUPPLIES ARRAY_SIZE(ov5640_supply_name)

/*
 * Image size under 1280 * 960 are SUBSAMPLING
 * Image size upper 1280 * 960 are SCALING
 */
क्रमागत ov5640_करोwnsize_mode अणु
	SUBSAMPLING,
	SCALING,
पूर्ण;

काष्ठा reg_value अणु
	u16 reg_addr;
	u8 val;
	u8 mask;
	u32 delay_ms;
पूर्ण;

काष्ठा ov5640_mode_info अणु
	क्रमागत ov5640_mode_id id;
	क्रमागत ov5640_करोwnsize_mode dn_mode;
	u32 hact;
	u32 htot;
	u32 vact;
	u32 vtot;
	स्थिर काष्ठा reg_value *reg_data;
	u32 reg_data_size;
	u32 max_fps;
पूर्ण;

काष्ठा ov5640_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_exp;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_wb;
		काष्ठा v4l2_ctrl *blue_balance;
		काष्ठा v4l2_ctrl *red_balance;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_gain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
	काष्ठा v4l2_ctrl *brightness;
	काष्ठा v4l2_ctrl *light_freq;
	काष्ठा v4l2_ctrl *saturation;
	काष्ठा v4l2_ctrl *contrast;
	काष्ठा v4l2_ctrl *hue;
	काष्ठा v4l2_ctrl *test_pattern;
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
पूर्ण;

काष्ठा ov5640_dev अणु
	काष्ठा i2c_client *i2c_client;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep; /* the parsed DT endpoपूर्णांक info */
	काष्ठा clk *xclk; /* प्रणाली घड़ी to OV5640 */
	u32 xclk_freq;

	काष्ठा regulator_bulk_data supplies[OV5640_NUM_SUPPLIES];
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *pwdn_gpio;
	bool   upside_करोwn;

	/* lock to protect all members below */
	काष्ठा mutex lock;

	पूर्णांक घातer_count;

	काष्ठा v4l2_mbus_framefmt fmt;
	bool pending_fmt_change;

	स्थिर काष्ठा ov5640_mode_info *current_mode;
	स्थिर काष्ठा ov5640_mode_info *last_mode;
	क्रमागत ov5640_frame_rate current_fr;
	काष्ठा v4l2_fract frame_पूर्णांकerval;

	काष्ठा ov5640_ctrls ctrls;

	u32 prev_sysclk, prev_hts;
	u32 ae_low, ae_high, ae_target;

	bool pending_mode_change;
	bool streaming;
पूर्ण;

अटल अंतरभूत काष्ठा ov5640_dev *to_ov5640_dev(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov5640_dev, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *ctrl_to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा ov5640_dev,
			     ctrls.handler)->sd;
पूर्ण

/*
 * FIXME: all of these रेजिस्टर tables are likely filled with
 * entries that set the रेजिस्टर to their घातer-on शेष values,
 * and which are otherwise not touched by this driver. Those entries
 * should be identअगरied and हटाओd to speed रेजिस्टर load समय
 * over i2c.
 */
/* YUV422 UYVY VGA@30fps */
अटल स्थिर काष्ठा reg_value ov5640_init_setting_30fps_VGA[] = अणु
	अणु0x3103, 0x11, 0, 0पूर्ण, अणु0x3008, 0x82, 0, 5पूर्ण, अणु0x3008, 0x42, 0, 0पूर्ण,
	अणु0x3103, 0x03, 0, 0पूर्ण, अणु0x3630, 0x36, 0, 0पूर्ण,
	अणु0x3631, 0x0e, 0, 0पूर्ण, अणु0x3632, 0xe2, 0, 0पूर्ण, अणु0x3633, 0x12, 0, 0पूर्ण,
	अणु0x3621, 0xe0, 0, 0पूर्ण, अणु0x3704, 0xa0, 0, 0पूर्ण, अणु0x3703, 0x5a, 0, 0पूर्ण,
	अणु0x3715, 0x78, 0, 0पूर्ण, अणु0x3717, 0x01, 0, 0पूर्ण, अणु0x370b, 0x60, 0, 0पूर्ण,
	अणु0x3705, 0x1a, 0, 0पूर्ण, अणु0x3905, 0x02, 0, 0पूर्ण, अणु0x3906, 0x10, 0, 0पूर्ण,
	अणु0x3901, 0x0a, 0, 0पूर्ण, अणु0x3731, 0x12, 0, 0पूर्ण, अणु0x3600, 0x08, 0, 0पूर्ण,
	अणु0x3601, 0x33, 0, 0पूर्ण, अणु0x302d, 0x60, 0, 0पूर्ण, अणु0x3620, 0x52, 0, 0पूर्ण,
	अणु0x371b, 0x20, 0, 0पूर्ण, अणु0x471c, 0x50, 0, 0पूर्ण, अणु0x3a13, 0x43, 0, 0पूर्ण,
	अणु0x3a18, 0x00, 0, 0पूर्ण, अणु0x3a19, 0xf8, 0, 0पूर्ण, अणु0x3635, 0x13, 0, 0पूर्ण,
	अणु0x3636, 0x03, 0, 0पूर्ण, अणु0x3634, 0x40, 0, 0पूर्ण, अणु0x3622, 0x01, 0, 0पूर्ण,
	अणु0x3c01, 0xa4, 0, 0पूर्ण, अणु0x3c04, 0x28, 0, 0पूर्ण, अणु0x3c05, 0x98, 0, 0पूर्ण,
	अणु0x3c06, 0x00, 0, 0पूर्ण, अणु0x3c07, 0x08, 0, 0पूर्ण, अणु0x3c08, 0x00, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3820, 0x41, 0, 0पूर्ण, अणु0x3821, 0x07, 0, 0पूर्ण, अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x06, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण, अणु0x3000, 0x00, 0, 0पूर्ण,
	अणु0x3002, 0x1c, 0, 0पूर्ण, अणु0x3004, 0xff, 0, 0पूर्ण, अणु0x3006, 0xc3, 0, 0पूर्ण,
	अणु0x302e, 0x08, 0, 0पूर्ण, अणु0x4300, 0x3f, 0, 0पूर्ण,
	अणु0x501f, 0x00, 0, 0पूर्ण, अणु0x4407, 0x04, 0, 0पूर्ण,
	अणु0x440e, 0x00, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x4837, 0x0a, 0, 0पूर्ण, अणु0x3824, 0x02, 0, 0पूर्ण,
	अणु0x5000, 0xa7, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण, अणु0x5180, 0xff, 0, 0पूर्ण,
	अणु0x5181, 0xf2, 0, 0पूर्ण, अणु0x5182, 0x00, 0, 0पूर्ण, अणु0x5183, 0x14, 0, 0पूर्ण,
	अणु0x5184, 0x25, 0, 0पूर्ण, अणु0x5185, 0x24, 0, 0पूर्ण, अणु0x5186, 0x09, 0, 0पूर्ण,
	अणु0x5187, 0x09, 0, 0पूर्ण, अणु0x5188, 0x09, 0, 0पूर्ण, अणु0x5189, 0x88, 0, 0पूर्ण,
	अणु0x518a, 0x54, 0, 0पूर्ण, अणु0x518b, 0xee, 0, 0पूर्ण, अणु0x518c, 0xb2, 0, 0पूर्ण,
	अणु0x518d, 0x50, 0, 0पूर्ण, अणु0x518e, 0x34, 0, 0पूर्ण, अणु0x518f, 0x6b, 0, 0पूर्ण,
	अणु0x5190, 0x46, 0, 0पूर्ण, अणु0x5191, 0xf8, 0, 0पूर्ण, अणु0x5192, 0x04, 0, 0पूर्ण,
	अणु0x5193, 0x70, 0, 0पूर्ण, अणु0x5194, 0xf0, 0, 0पूर्ण, अणु0x5195, 0xf0, 0, 0पूर्ण,
	अणु0x5196, 0x03, 0, 0पूर्ण, अणु0x5197, 0x01, 0, 0पूर्ण, अणु0x5198, 0x04, 0, 0पूर्ण,
	अणु0x5199, 0x6c, 0, 0पूर्ण, अणु0x519a, 0x04, 0, 0पूर्ण, अणु0x519b, 0x00, 0, 0पूर्ण,
	अणु0x519c, 0x09, 0, 0पूर्ण, अणु0x519d, 0x2b, 0, 0पूर्ण, अणु0x519e, 0x38, 0, 0पूर्ण,
	अणु0x5381, 0x1e, 0, 0पूर्ण, अणु0x5382, 0x5b, 0, 0पूर्ण, अणु0x5383, 0x08, 0, 0पूर्ण,
	अणु0x5384, 0x0a, 0, 0पूर्ण, अणु0x5385, 0x7e, 0, 0पूर्ण, अणु0x5386, 0x88, 0, 0पूर्ण,
	अणु0x5387, 0x7c, 0, 0पूर्ण, अणु0x5388, 0x6c, 0, 0पूर्ण, अणु0x5389, 0x10, 0, 0पूर्ण,
	अणु0x538a, 0x01, 0, 0पूर्ण, अणु0x538b, 0x98, 0, 0पूर्ण, अणु0x5300, 0x08, 0, 0पूर्ण,
	अणु0x5301, 0x30, 0, 0पूर्ण, अणु0x5302, 0x10, 0, 0पूर्ण, अणु0x5303, 0x00, 0, 0पूर्ण,
	अणु0x5304, 0x08, 0, 0पूर्ण, अणु0x5305, 0x30, 0, 0पूर्ण, अणु0x5306, 0x08, 0, 0पूर्ण,
	अणु0x5307, 0x16, 0, 0पूर्ण, अणु0x5309, 0x08, 0, 0पूर्ण, अणु0x530a, 0x30, 0, 0पूर्ण,
	अणु0x530b, 0x04, 0, 0पूर्ण, अणु0x530c, 0x06, 0, 0पूर्ण, अणु0x5480, 0x01, 0, 0पूर्ण,
	अणु0x5481, 0x08, 0, 0पूर्ण, अणु0x5482, 0x14, 0, 0पूर्ण, अणु0x5483, 0x28, 0, 0पूर्ण,
	अणु0x5484, 0x51, 0, 0पूर्ण, अणु0x5485, 0x65, 0, 0पूर्ण, अणु0x5486, 0x71, 0, 0पूर्ण,
	अणु0x5487, 0x7d, 0, 0पूर्ण, अणु0x5488, 0x87, 0, 0पूर्ण, अणु0x5489, 0x91, 0, 0पूर्ण,
	अणु0x548a, 0x9a, 0, 0पूर्ण, अणु0x548b, 0xaa, 0, 0पूर्ण, अणु0x548c, 0xb8, 0, 0पूर्ण,
	अणु0x548d, 0xcd, 0, 0पूर्ण, अणु0x548e, 0xdd, 0, 0पूर्ण, अणु0x548f, 0xea, 0, 0पूर्ण,
	अणु0x5490, 0x1d, 0, 0पूर्ण, अणु0x5580, 0x02, 0, 0पूर्ण, अणु0x5583, 0x40, 0, 0पूर्ण,
	अणु0x5584, 0x10, 0, 0पूर्ण, अणु0x5589, 0x10, 0, 0पूर्ण, अणु0x558a, 0x00, 0, 0पूर्ण,
	अणु0x558b, 0xf8, 0, 0पूर्ण, अणु0x5800, 0x23, 0, 0पूर्ण, अणु0x5801, 0x14, 0, 0पूर्ण,
	अणु0x5802, 0x0f, 0, 0पूर्ण, अणु0x5803, 0x0f, 0, 0पूर्ण, अणु0x5804, 0x12, 0, 0पूर्ण,
	अणु0x5805, 0x26, 0, 0पूर्ण, अणु0x5806, 0x0c, 0, 0पूर्ण, अणु0x5807, 0x08, 0, 0पूर्ण,
	अणु0x5808, 0x05, 0, 0पूर्ण, अणु0x5809, 0x05, 0, 0पूर्ण, अणु0x580a, 0x08, 0, 0पूर्ण,
	अणु0x580b, 0x0d, 0, 0पूर्ण, अणु0x580c, 0x08, 0, 0पूर्ण, अणु0x580d, 0x03, 0, 0पूर्ण,
	अणु0x580e, 0x00, 0, 0पूर्ण, अणु0x580f, 0x00, 0, 0पूर्ण, अणु0x5810, 0x03, 0, 0पूर्ण,
	अणु0x5811, 0x09, 0, 0पूर्ण, अणु0x5812, 0x07, 0, 0पूर्ण, अणु0x5813, 0x03, 0, 0पूर्ण,
	अणु0x5814, 0x00, 0, 0पूर्ण, अणु0x5815, 0x01, 0, 0पूर्ण, अणु0x5816, 0x03, 0, 0पूर्ण,
	अणु0x5817, 0x08, 0, 0पूर्ण, अणु0x5818, 0x0d, 0, 0पूर्ण, अणु0x5819, 0x08, 0, 0पूर्ण,
	अणु0x581a, 0x05, 0, 0पूर्ण, अणु0x581b, 0x06, 0, 0पूर्ण, अणु0x581c, 0x08, 0, 0पूर्ण,
	अणु0x581d, 0x0e, 0, 0पूर्ण, अणु0x581e, 0x29, 0, 0पूर्ण, अणु0x581f, 0x17, 0, 0पूर्ण,
	अणु0x5820, 0x11, 0, 0पूर्ण, अणु0x5821, 0x11, 0, 0पूर्ण, अणु0x5822, 0x15, 0, 0पूर्ण,
	अणु0x5823, 0x28, 0, 0पूर्ण, अणु0x5824, 0x46, 0, 0पूर्ण, अणु0x5825, 0x26, 0, 0पूर्ण,
	अणु0x5826, 0x08, 0, 0पूर्ण, अणु0x5827, 0x26, 0, 0पूर्ण, अणु0x5828, 0x64, 0, 0पूर्ण,
	अणु0x5829, 0x26, 0, 0पूर्ण, अणु0x582a, 0x24, 0, 0पूर्ण, अणु0x582b, 0x22, 0, 0पूर्ण,
	अणु0x582c, 0x24, 0, 0पूर्ण, अणु0x582d, 0x24, 0, 0पूर्ण, अणु0x582e, 0x06, 0, 0पूर्ण,
	अणु0x582f, 0x22, 0, 0पूर्ण, अणु0x5830, 0x40, 0, 0पूर्ण, अणु0x5831, 0x42, 0, 0पूर्ण,
	अणु0x5832, 0x24, 0, 0पूर्ण, अणु0x5833, 0x26, 0, 0पूर्ण, अणु0x5834, 0x24, 0, 0पूर्ण,
	अणु0x5835, 0x22, 0, 0पूर्ण, अणु0x5836, 0x22, 0, 0पूर्ण, अणु0x5837, 0x26, 0, 0पूर्ण,
	अणु0x5838, 0x44, 0, 0पूर्ण, अणु0x5839, 0x24, 0, 0पूर्ण, अणु0x583a, 0x26, 0, 0पूर्ण,
	अणु0x583b, 0x28, 0, 0पूर्ण, अणु0x583c, 0x42, 0, 0पूर्ण, अणु0x583d, 0xce, 0, 0पूर्ण,
	अणु0x5025, 0x00, 0, 0पूर्ण, अणु0x3a0f, 0x30, 0, 0पूर्ण, अणु0x3a10, 0x28, 0, 0पूर्ण,
	अणु0x3a1b, 0x30, 0, 0पूर्ण, अणु0x3a1e, 0x26, 0, 0पूर्ण, अणु0x3a11, 0x60, 0, 0पूर्ण,
	अणु0x3a1f, 0x14, 0, 0पूर्ण, अणु0x3008, 0x02, 0, 0पूर्ण, अणु0x3c00, 0x04, 0, 300पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_VGA_640_480[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x06, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_XGA_1024_768[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x06, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_QVGA_320_240[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x06, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_QQVGA_160_120[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x06, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_QCIF_176_144[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x06, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_NTSC_720_480[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x3c, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_PAL_720_576[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x04, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9b, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x38, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x06, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0xa3, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_720P_1280_720[] = अणु
	अणु0x3c07, 0x07, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x31, 0, 0पूर्ण,
	अणु0x3815, 0x31, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0xfa, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x06, 0, 0पूर्ण, अणु0x3807, 0xa9, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x04, 0, 0पूर्ण,
	अणु0x3618, 0x00, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3709, 0x52, 0, 0पूर्ण, अणु0x370c, 0x03, 0, 0पूर्ण, अणु0x3a02, 0x02, 0, 0पूर्ण,
	अणु0x3a03, 0xe4, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0xbc, 0, 0पूर्ण,
	अणु0x3a0a, 0x01, 0, 0पूर्ण, अणु0x3a0b, 0x72, 0, 0पूर्ण, अणु0x3a0e, 0x01, 0, 0पूर्ण,
	अणु0x3a0d, 0x02, 0, 0पूर्ण, अणु0x3a14, 0x02, 0, 0पूर्ण, अणु0x3a15, 0xe4, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x02, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x37, 0, 0पूर्ण, अणु0x460c, 0x20, 0, 0पूर्ण,
	अणु0x3824, 0x04, 0, 0पूर्ण, अणु0x5001, 0x83, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_1080P_1920_1080[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x11, 0, 0पूर्ण,
	अणु0x3815, 0x11, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x00, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9f, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x04, 0, 0पूर्ण,
	अणु0x3618, 0x04, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x21, 0, 0पूर्ण,
	अणु0x3709, 0x12, 0, 0पूर्ण, अणु0x370c, 0x00, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x06, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0x83, 0, 0पूर्ण,
	अणु0x3c07, 0x07, 0, 0पूर्ण, अणु0x3c08, 0x00, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3800, 0x01, 0, 0पूर्ण, अणु0x3801, 0x50, 0, 0पूर्ण, अणु0x3802, 0x01, 0, 0पूर्ण,
	अणु0x3803, 0xb2, 0, 0पूर्ण, अणु0x3804, 0x08, 0, 0पूर्ण, अणु0x3805, 0xef, 0, 0पूर्ण,
	अणु0x3806, 0x05, 0, 0पूर्ण, अणु0x3807, 0xf1, 0, 0पूर्ण,
	अणु0x3612, 0x2b, 0, 0पूर्ण, अणु0x3708, 0x64, 0, 0पूर्ण,
	अणु0x3a02, 0x04, 0, 0पूर्ण, अणु0x3a03, 0x60, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण,
	अणु0x3a09, 0x50, 0, 0पूर्ण, अणु0x3a0a, 0x01, 0, 0पूर्ण, अणु0x3a0b, 0x18, 0, 0पूर्ण,
	अणु0x3a0e, 0x03, 0, 0पूर्ण, अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x04, 0, 0पूर्ण,
	अणु0x3a15, 0x60, 0, 0पूर्ण, अणु0x4407, 0x04, 0, 0पूर्ण,
	अणु0x460b, 0x37, 0, 0पूर्ण, अणु0x460c, 0x20, 0, 0पूर्ण, अणु0x3824, 0x04, 0, 0पूर्ण,
	अणु0x4005, 0x1a, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov5640_setting_QSXGA_2592_1944[] = अणु
	अणु0x3c07, 0x08, 0, 0पूर्ण,
	अणु0x3c09, 0x1c, 0, 0पूर्ण, अणु0x3c0a, 0x9c, 0, 0पूर्ण, अणु0x3c0b, 0x40, 0, 0पूर्ण,
	अणु0x3814, 0x11, 0, 0पूर्ण,
	अणु0x3815, 0x11, 0, 0पूर्ण, अणु0x3800, 0x00, 0, 0पूर्ण, अणु0x3801, 0x00, 0, 0पूर्ण,
	अणु0x3802, 0x00, 0, 0पूर्ण, अणु0x3803, 0x00, 0, 0पूर्ण, अणु0x3804, 0x0a, 0, 0पूर्ण,
	अणु0x3805, 0x3f, 0, 0पूर्ण, अणु0x3806, 0x07, 0, 0पूर्ण, अणु0x3807, 0x9f, 0, 0पूर्ण,
	अणु0x3810, 0x00, 0, 0पूर्ण,
	अणु0x3811, 0x10, 0, 0पूर्ण, अणु0x3812, 0x00, 0, 0पूर्ण, अणु0x3813, 0x04, 0, 0पूर्ण,
	अणु0x3618, 0x04, 0, 0पूर्ण, अणु0x3612, 0x29, 0, 0पूर्ण, अणु0x3708, 0x21, 0, 0पूर्ण,
	अणु0x3709, 0x12, 0, 0पूर्ण, अणु0x370c, 0x00, 0, 0पूर्ण, अणु0x3a02, 0x03, 0, 0पूर्ण,
	अणु0x3a03, 0xd8, 0, 0पूर्ण, अणु0x3a08, 0x01, 0, 0पूर्ण, अणु0x3a09, 0x27, 0, 0पूर्ण,
	अणु0x3a0a, 0x00, 0, 0पूर्ण, अणु0x3a0b, 0xf6, 0, 0पूर्ण, अणु0x3a0e, 0x03, 0, 0पूर्ण,
	अणु0x3a0d, 0x04, 0, 0पूर्ण, अणु0x3a14, 0x03, 0, 0पूर्ण, अणु0x3a15, 0xd8, 0, 0पूर्ण,
	अणु0x4001, 0x02, 0, 0पूर्ण, अणु0x4004, 0x06, 0, 0पूर्ण,
	अणु0x4407, 0x04, 0, 0पूर्ण, अणु0x460b, 0x35, 0, 0पूर्ण, अणु0x460c, 0x22, 0, 0पूर्ण,
	अणु0x3824, 0x02, 0, 0पूर्ण, अणु0x5001, 0x83, 0, 70पूर्ण,
पूर्ण;

/* घातer-on sensor init reg table */
अटल स्थिर काष्ठा ov5640_mode_info ov5640_mode_init_data = अणु
	0, SUBSAMPLING, 640, 1896, 480, 984,
	ov5640_init_setting_30fps_VGA,
	ARRAY_SIZE(ov5640_init_setting_30fps_VGA),
	OV5640_30_FPS,
पूर्ण;

अटल स्थिर काष्ठा ov5640_mode_info
ov5640_mode_data[OV5640_NUM_MODES] = अणु
	अणुOV5640_MODE_QQVGA_160_120, SUBSAMPLING,
	 160, 1896, 120, 984,
	 ov5640_setting_QQVGA_160_120,
	 ARRAY_SIZE(ov5640_setting_QQVGA_160_120),
	 OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_QCIF_176_144, SUBSAMPLING,
	 176, 1896, 144, 984,
	 ov5640_setting_QCIF_176_144,
	 ARRAY_SIZE(ov5640_setting_QCIF_176_144),
	 OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_QVGA_320_240, SUBSAMPLING,
	 320, 1896, 240, 984,
	 ov5640_setting_QVGA_320_240,
	 ARRAY_SIZE(ov5640_setting_QVGA_320_240),
	 OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_VGA_640_480, SUBSAMPLING,
	 640, 1896, 480, 1080,
	 ov5640_setting_VGA_640_480,
	 ARRAY_SIZE(ov5640_setting_VGA_640_480),
	 OV5640_60_FPSपूर्ण,
	अणुOV5640_MODE_NTSC_720_480, SUBSAMPLING,
	 720, 1896, 480, 984,
	 ov5640_setting_NTSC_720_480,
	 ARRAY_SIZE(ov5640_setting_NTSC_720_480),
	OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_PAL_720_576, SUBSAMPLING,
	 720, 1896, 576, 984,
	 ov5640_setting_PAL_720_576,
	 ARRAY_SIZE(ov5640_setting_PAL_720_576),
	 OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_XGA_1024_768, SUBSAMPLING,
	 1024, 1896, 768, 1080,
	 ov5640_setting_XGA_1024_768,
	 ARRAY_SIZE(ov5640_setting_XGA_1024_768),
	 OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_720P_1280_720, SUBSAMPLING,
	 1280, 1892, 720, 740,
	 ov5640_setting_720P_1280_720,
	 ARRAY_SIZE(ov5640_setting_720P_1280_720),
	 OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_1080P_1920_1080, SCALING,
	 1920, 2500, 1080, 1120,
	 ov5640_setting_1080P_1920_1080,
	 ARRAY_SIZE(ov5640_setting_1080P_1920_1080),
	 OV5640_30_FPSपूर्ण,
	अणुOV5640_MODE_QSXGA_2592_1944, SCALING,
	 2592, 2844, 1944, 1968,
	 ov5640_setting_QSXGA_2592_1944,
	 ARRAY_SIZE(ov5640_setting_QSXGA_2592_1944),
	 OV5640_15_FPSपूर्ण,
पूर्ण;

अटल पूर्णांक ov5640_init_slave_id(काष्ठा ov5640_dev *sensor)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	काष्ठा i2c_msg msg;
	u8 buf[3];
	पूर्णांक ret;

	अगर (client->addr == OV5640_DEFAULT_SLAVE_ID)
		वापस 0;

	buf[0] = OV5640_REG_SLAVE_ID >> 8;
	buf[1] = OV5640_REG_SLAVE_ID & 0xff;
	buf[2] = client->addr << 1;

	msg.addr = OV5640_DEFAULT_SLAVE_ID;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = माप(buf);

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "%s: failed with %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_ग_लिखो_reg(काष्ठा ov5640_dev *sensor, u16 reg, u8 val)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	काष्ठा i2c_msg msg;
	u8 buf[3];
	पूर्णांक ret;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;
	buf[2] = val;

	msg.addr = client->addr;
	msg.flags = client->flags;
	msg.buf = buf;
	msg.len = माप(buf);

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "%s: error: reg=%x, val=%x\n",
			__func__, reg, val);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_पढ़ो_reg(काष्ठा ov5640_dev *sensor, u16 reg, u8 *val)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	काष्ठा i2c_msg msg[2];
	u8 buf[2];
	पूर्णांक ret;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	msg[0].addr = client->addr;
	msg[0].flags = client->flags;
	msg[0].buf = buf;
	msg[0].len = माप(buf);

	msg[1].addr = client->addr;
	msg[1].flags = client->flags | I2C_M_RD;
	msg[1].buf = buf;
	msg[1].len = 1;

	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "%s: error: reg=%x\n",
			__func__, reg);
		वापस ret;
	पूर्ण

	*val = buf[0];
	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_पढ़ो_reg16(काष्ठा ov5640_dev *sensor, u16 reg, u16 *val)
अणु
	u8 hi, lo;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg(sensor, reg, &hi);
	अगर (ret)
		वापस ret;
	ret = ov5640_पढ़ो_reg(sensor, reg + 1, &lo);
	अगर (ret)
		वापस ret;

	*val = ((u16)hi << 8) | (u16)lo;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_ग_लिखो_reg16(काष्ठा ov5640_dev *sensor, u16 reg, u16 val)
अणु
	पूर्णांक ret;

	ret = ov5640_ग_लिखो_reg(sensor, reg, val >> 8);
	अगर (ret)
		वापस ret;

	वापस ov5640_ग_लिखो_reg(sensor, reg + 1, val & 0xff);
पूर्ण

अटल पूर्णांक ov5640_mod_reg(काष्ठा ov5640_dev *sensor, u16 reg,
			  u8 mask, u8 val)
अणु
	u8 पढ़ोval;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg(sensor, reg, &पढ़ोval);
	अगर (ret)
		वापस ret;

	पढ़ोval &= ~mask;
	val &= mask;
	val |= पढ़ोval;

	वापस ov5640_ग_लिखो_reg(sensor, reg, val);
पूर्ण

/*
 * After trying the various combinations, पढ़ोing various
 * करोcumentations spपढ़ो around the net, and from the various
 * feedback, the घड़ी tree is probably as follows:
 *
 *   +--------------+
 *   |  Ext. Clock  |
 *   +-+------------+
 *     |  +----------+
 *     +->|   PLL1   | - reg 0x3036, क्रम the multiplier
 *        +-+--------+ - reg 0x3037, bits 0-3 क्रम the pre-भागider
 *          |  +--------------+
 *          +->| System Clock |  - reg 0x3035, bits 4-7
 *             +-+------------+
 *               |  +--------------+
 *               +->| MIPI Divider | - reg 0x3035, bits 0-3
 *               |  +-+------------+
 *               |    +----------------> MIPI SCLK
 *               |    +  +-----+
 *               |    +->| / 2 |-------> MIPI BIT CLK
 *               |       +-----+
 *               |  +--------------+
 *               +->| PLL Root Div | - reg 0x3037, bit 4
 *                  +-+------------+
 *                    |  +---------+
 *                    +->| Bit Div | - reg 0x3034, bits 0-3
 *                       +-+-------+
 *                         |  +-------------+
 *                         +->| SCLK Div    | - reg 0x3108, bits 0-1
 *                         |  +-+-----------+
 *                         |    +---------------> SCLK
 *                         |  +-------------+
 *                         +->| SCLK 2X Div | - reg 0x3108, bits 2-3
 *                         |  +-+-----------+
 *                         |    +---------------> SCLK 2X
 *                         |  +-------------+
 *                         +->| PCLK Div    | - reg 0x3108, bits 4-5
 *                            ++------------+
 *                             +  +-----------+
 *                             +->|   P_DIV   | - reg 0x3035, bits 0-3
 *                                +-----+-----+
 *                                       +------------> PCLK
 *
 * This is deviating from the datasheet at least क्रम the रेजिस्टर
 * 0x3108, since it's said here that the PCLK would be घड़ीed from
 * the PLL.
 *
 * There seems to be also (unverअगरied) स्थिरraपूर्णांकs:
 *  - the PLL pre-भागider output rate should be in the 4-27MHz range
 *  - the PLL multiplier output rate should be in the 500-1000MHz range
 *  - PCLK >= SCLK * 2 in YUV, >= SCLK in Raw or JPEG
 *
 * In the two latter हालs, these स्थिरraपूर्णांकs are met since our
 * factors are hardcoded. If we were to change that, we would need to
 * take this पूर्णांकo account. The only varying parts are the PLL
 * multiplier and the प्रणाली घड़ी भागider, which are shared between
 * all these घड़ीs so won't cause any issue.
 */

/*
 * This is supposed to be ranging from 1 to 8, but the value is always
 * set to 3 in the venकरोr kernels.
 */
#घोषणा OV5640_PLL_PREDIV	3

#घोषणा OV5640_PLL_MULT_MIN	4
#घोषणा OV5640_PLL_MULT_MAX	252

/*
 * This is supposed to be ranging from 1 to 16, but the value is
 * always set to either 1 or 2 in the venकरोr kernels.
 */
#घोषणा OV5640_SYSDIV_MIN	1
#घोषणा OV5640_SYSDIV_MAX	16

/*
 * Hardcode these values क्रम scaler and non-scaler modes.
 * FIXME: to be re-calcualted क्रम 1 data lanes setups
 */
#घोषणा OV5640_MIPI_DIV_PCLK	2
#घोषणा OV5640_MIPI_DIV_SCLK	1

/*
 * This is supposed to be ranging from 1 to 2, but the value is always
 * set to 2 in the venकरोr kernels.
 */
#घोषणा OV5640_PLL_ROOT_DIV			2
#घोषणा OV5640_PLL_CTRL3_PLL_ROOT_DIV_2		BIT(4)

/*
 * We only supports 8-bit क्रमmats at the moment
 */
#घोषणा OV5640_BIT_DIV				2
#घोषणा OV5640_PLL_CTRL0_MIPI_MODE_8BIT		0x08

/*
 * This is supposed to be ranging from 1 to 8, but the value is always
 * set to 2 in the venकरोr kernels.
 */
#घोषणा OV5640_SCLK_ROOT_DIV	2

/*
 * This is hardcoded so that the consistency is मुख्यtained between SCLK and
 * SCLK 2x.
 */
#घोषणा OV5640_SCLK2X_ROOT_DIV (OV5640_SCLK_ROOT_DIV / 2)

/*
 * This is supposed to be ranging from 1 to 8, but the value is always
 * set to 1 in the venकरोr kernels.
 */
#घोषणा OV5640_PCLK_ROOT_DIV			1
#घोषणा OV5640_PLL_SYS_ROOT_DIVIDER_BYPASS	0x00

अटल अचिन्हित दीर्घ ov5640_compute_sys_clk(काष्ठा ov5640_dev *sensor,
					    u8 pll_preभाग, u8 pll_mult,
					    u8 sysभाग)
अणु
	अचिन्हित दीर्घ sysclk = sensor->xclk_freq / pll_preभाग * pll_mult;

	/* PLL1 output cannot exceed 1GHz. */
	अगर (sysclk / 1000000 > 1000)
		वापस 0;

	वापस sysclk / sysभाग;
पूर्ण

अटल अचिन्हित दीर्घ ov5640_calc_sys_clk(काष्ठा ov5640_dev *sensor,
					 अचिन्हित दीर्घ rate,
					 u8 *pll_preभाग, u8 *pll_mult,
					 u8 *sysभाग)
अणु
	अचिन्हित दीर्घ best = ~0;
	u8 best_sysभाग = 1, best_mult = 1;
	u8 _sysभाग, _pll_mult;

	क्रम (_sysभाग = OV5640_SYSDIV_MIN;
	     _sysभाग <= OV5640_SYSDIV_MAX;
	     _sysभाग++) अणु
		क्रम (_pll_mult = OV5640_PLL_MULT_MIN;
		     _pll_mult <= OV5640_PLL_MULT_MAX;
		     _pll_mult++) अणु
			अचिन्हित दीर्घ _rate;

			/*
			 * The PLL multiplier cannot be odd अगर above
			 * 127.
			 */
			अगर (_pll_mult > 127 && (_pll_mult % 2))
				जारी;

			_rate = ov5640_compute_sys_clk(sensor,
						       OV5640_PLL_PREDIV,
						       _pll_mult, _sysभाग);

			/*
			 * We have reached the maximum allowed PLL1 output,
			 * increase sysभाग.
			 */
			अगर (!_rate)
				अवरोध;

			/*
			 * Prefer rates above the expected घड़ी rate than
			 * below, even अगर that means being less precise.
			 */
			अगर (_rate < rate)
				जारी;

			अगर (असल(rate - _rate) < असल(rate - best)) अणु
				best = _rate;
				best_sysभाग = _sysभाग;
				best_mult = _pll_mult;
			पूर्ण

			अगर (_rate == rate)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	*sysभाग = best_sysभाग;
	*pll_preभाग = OV5640_PLL_PREDIV;
	*pll_mult = best_mult;

	वापस best;
पूर्ण

/*
 * ov5640_set_mipi_pclk() - Calculate the घड़ी tree configuration values
 *			    क्रम the MIPI CSI-2 output.
 *
 * @rate: The requested bandwidth per lane in bytes per second.
 *	  'Bandwidth Per Lane' is calculated as:
 *	  bpl = HTOT * VTOT * FPS * bpp / num_lanes;
 *
 * This function use the requested bandwidth to calculate:
 * - sample_rate = bpl / (bpp / num_lanes);
 *	         = bpl / (PLL_RDIV * BIT_DIV * PCLK_DIV * MIPI_DIV / num_lanes);
 *
 * - mipi_sclk   = bpl / MIPI_DIV / 2; ( / 2 is क्रम CSI-2 DDR)
 *
 * with these fixed parameters:
 *	PLL_RDIV	= 2;
 *	BIT_DIVIDER	= 2; (MIPI_BIT_MODE == 8 ? 2 : 2,5);
 *	PCLK_DIV	= 1;
 *
 * The MIPI घड़ी generation dअगरfers क्रम modes that use the scaler and modes
 * that करो not. In हाल the scaler is in use, the MIPI_SCLK generates the MIPI
 * BIT CLk, and thus:
 *
 * - mipi_sclk = bpl / MIPI_DIV / 2;
 *   MIPI_DIV = 1;
 *
 * For modes that करो not go through the scaler, the MIPI BIT CLOCK is generated
 * from the pixel घड़ी, and thus:
 *
 * - sample_rate = bpl / (bpp / num_lanes);
 *	         = bpl / (2 * 2 * 1 * MIPI_DIV / num_lanes);
 *		 = bpl / (4 * MIPI_DIV / num_lanes);
 * - MIPI_DIV	 = bpp / (4 * num_lanes);
 *
 * FIXME: this have been tested with 16bpp and 2 lanes setup only.
 * MIPI_DIV is fixed to value 2, but it -might- be changed according to the
 * above क्रमmula क्रम setups with 1 lane or image क्रमmats with dअगरferent bpp.
 *
 * FIXME: this deviates from the sensor manual करोcumentation which is quite
 * thin on the MIPI घड़ी tree generation part.
 */
अटल पूर्णांक ov5640_set_mipi_pclk(काष्ठा ov5640_dev *sensor,
				अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा ov5640_mode_info *mode = sensor->current_mode;
	u8 preभाग, mult, sysभाग;
	u8 mipi_भाग;
	पूर्णांक ret;

	/*
	 * 1280x720 is reported to use 'SUBSAMPLING' only,
	 * but according to the sensor manual it goes through the
	 * scaler beक्रमe subsampling.
	 */
	अगर (mode->dn_mode == SCALING ||
	   (mode->id == OV5640_MODE_720P_1280_720))
		mipi_भाग = OV5640_MIPI_DIV_SCLK;
	अन्यथा
		mipi_भाग = OV5640_MIPI_DIV_PCLK;

	ov5640_calc_sys_clk(sensor, rate, &preभाग, &mult, &sysभाग);

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL0,
			     0x0f, OV5640_PLL_CTRL0_MIPI_MODE_8BIT);

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL1,
			     0xff, sysभाग << 4 | mipi_भाग);
	अगर (ret)
		वापस ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL2, 0xff, mult);
	अगर (ret)
		वापस ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL3,
			     0x1f, OV5640_PLL_CTRL3_PLL_ROOT_DIV_2 | preभाग);
	अगर (ret)
		वापस ret;

	वापस ov5640_mod_reg(sensor, OV5640_REG_SYS_ROOT_DIVIDER,
			      0x30, OV5640_PLL_SYS_ROOT_DIVIDER_BYPASS);
पूर्ण

अटल अचिन्हित दीर्घ ov5640_calc_pclk(काष्ठा ov5640_dev *sensor,
				      अचिन्हित दीर्घ rate,
				      u8 *pll_preभाग, u8 *pll_mult, u8 *sysभाग,
				      u8 *pll_rभाग, u8 *bit_भाग, u8 *pclk_भाग)
अणु
	अचिन्हित दीर्घ _rate = rate * OV5640_PLL_ROOT_DIV * OV5640_BIT_DIV *
				OV5640_PCLK_ROOT_DIV;

	_rate = ov5640_calc_sys_clk(sensor, _rate, pll_preभाग, pll_mult,
				    sysभाग);
	*pll_rभाग = OV5640_PLL_ROOT_DIV;
	*bit_भाग = OV5640_BIT_DIV;
	*pclk_भाग = OV5640_PCLK_ROOT_DIV;

	वापस _rate / *pll_rभाग / *bit_भाग / *pclk_भाग;
पूर्ण

अटल पूर्णांक ov5640_set_dvp_pclk(काष्ठा ov5640_dev *sensor, अचिन्हित दीर्घ rate)
अणु
	u8 preभाग, mult, sysभाग, pll_rभाग, bit_भाग, pclk_भाग;
	पूर्णांक ret;

	ov5640_calc_pclk(sensor, rate, &preभाग, &mult, &sysभाग, &pll_rभाग,
			 &bit_भाग, &pclk_भाग);

	अगर (bit_भाग == 2)
		bit_भाग = 8;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL0,
			     0x0f, bit_भाग);
	अगर (ret)
		वापस ret;

	/*
	 * We need to set sysभाग according to the घड़ी, and to clear
	 * the MIPI भागider.
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL1,
			     0xff, sysभाग << 4);
	अगर (ret)
		वापस ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL2,
			     0xff, mult);
	अगर (ret)
		वापस ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SC_PLL_CTRL3,
			     0x1f, preभाग | ((pll_rभाग - 1) << 4));
	अगर (ret)
		वापस ret;

	वापस ov5640_mod_reg(sensor, OV5640_REG_SYS_ROOT_DIVIDER, 0x30,
			      (ilog2(pclk_भाग) << 4));
पूर्ण

/* set JPEG framing sizes */
अटल पूर्णांक ov5640_set_jpeg_timings(काष्ठा ov5640_dev *sensor,
				   स्थिर काष्ठा ov5640_mode_info *mode)
अणु
	पूर्णांक ret;

	/*
	 * compression mode 3 timing
	 *
	 * Data is transmitted with programmable width (VFIFO_HSIZE).
	 * No padding करोne. Last line may have less data. Varying
	 * number of lines per frame, depending on amount of data.
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_JPG_MODE_SELECT, 0x7, 0x3);
	अगर (ret < 0)
		वापस ret;

	ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_VFIFO_HSIZE, mode->hact);
	अगर (ret < 0)
		वापस ret;

	वापस ov5640_ग_लिखो_reg16(sensor, OV5640_REG_VFIFO_VSIZE, mode->vact);
पूर्ण

/* करोwnload ov5640 settings to sensor through i2c */
अटल पूर्णांक ov5640_set_timings(काष्ठा ov5640_dev *sensor,
			      स्थिर काष्ठा ov5640_mode_info *mode)
अणु
	पूर्णांक ret;

	अगर (sensor->fmt.code == MEDIA_BUS_FMT_JPEG_1X8) अणु
		ret = ov5640_set_jpeg_timings(sensor, mode);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_TIMING_DVPHO, mode->hact);
	अगर (ret < 0)
		वापस ret;

	ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_TIMING_DVPVO, mode->vact);
	अगर (ret < 0)
		वापस ret;

	ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_TIMING_HTS, mode->htot);
	अगर (ret < 0)
		वापस ret;

	वापस ov5640_ग_लिखो_reg16(sensor, OV5640_REG_TIMING_VTS, mode->vtot);
पूर्ण

अटल पूर्णांक ov5640_load_regs(काष्ठा ov5640_dev *sensor,
			    स्थिर काष्ठा ov5640_mode_info *mode)
अणु
	स्थिर काष्ठा reg_value *regs = mode->reg_data;
	अचिन्हित पूर्णांक i;
	u32 delay_ms;
	u16 reg_addr;
	u8 mask, val;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < mode->reg_data_size; ++i, ++regs) अणु
		delay_ms = regs->delay_ms;
		reg_addr = regs->reg_addr;
		val = regs->val;
		mask = regs->mask;

		/* reमुख्य in घातer करोwn mode क्रम DVP */
		अगर (regs->reg_addr == OV5640_REG_SYS_CTRL0 &&
		    val == OV5640_REG_SYS_CTRL0_SW_PWUP &&
		    sensor->ep.bus_type != V4L2_MBUS_CSI2_DPHY)
			जारी;

		अगर (mask)
			ret = ov5640_mod_reg(sensor, reg_addr, mask, val);
		अन्यथा
			ret = ov5640_ग_लिखो_reg(sensor, reg_addr, val);
		अगर (ret)
			अवरोध;

		अगर (delay_ms)
			usleep_range(1000 * delay_ms, 1000 * delay_ms + 100);
	पूर्ण

	वापस ov5640_set_timings(sensor, mode);
पूर्ण

अटल पूर्णांक ov5640_set_स्वतःexposure(काष्ठा ov5640_dev *sensor, bool on)
अणु
	वापस ov5640_mod_reg(sensor, OV5640_REG_AEC_PK_MANUAL,
			      BIT(0), on ? 0 : BIT(0));
पूर्ण

/* पढ़ो exposure, in number of line periods */
अटल पूर्णांक ov5640_get_exposure(काष्ठा ov5640_dev *sensor)
अणु
	पूर्णांक exp, ret;
	u8 temp;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_AEC_PK_EXPOSURE_HI, &temp);
	अगर (ret)
		वापस ret;
	exp = ((पूर्णांक)temp & 0x0f) << 16;
	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_AEC_PK_EXPOSURE_MED, &temp);
	अगर (ret)
		वापस ret;
	exp |= ((पूर्णांक)temp << 8);
	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_AEC_PK_EXPOSURE_LO, &temp);
	अगर (ret)
		वापस ret;
	exp |= (पूर्णांक)temp;

	वापस exp >> 4;
पूर्ण

/* ग_लिखो exposure, given number of line periods */
अटल पूर्णांक ov5640_set_exposure(काष्ठा ov5640_dev *sensor, u32 exposure)
अणु
	पूर्णांक ret;

	exposure <<= 4;

	ret = ov5640_ग_लिखो_reg(sensor,
			       OV5640_REG_AEC_PK_EXPOSURE_LO,
			       exposure & 0xff);
	अगर (ret)
		वापस ret;
	ret = ov5640_ग_लिखो_reg(sensor,
			       OV5640_REG_AEC_PK_EXPOSURE_MED,
			       (exposure >> 8) & 0xff);
	अगर (ret)
		वापस ret;
	वापस ov5640_ग_लिखो_reg(sensor,
				OV5640_REG_AEC_PK_EXPOSURE_HI,
				(exposure >> 16) & 0x0f);
पूर्ण

अटल पूर्णांक ov5640_get_gain(काष्ठा ov5640_dev *sensor)
अणु
	u16 gain;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg16(sensor, OV5640_REG_AEC_PK_REAL_GAIN, &gain);
	अगर (ret)
		वापस ret;

	वापस gain & 0x3ff;
पूर्ण

अटल पूर्णांक ov5640_set_gain(काष्ठा ov5640_dev *sensor, पूर्णांक gain)
अणु
	वापस ov5640_ग_लिखो_reg16(sensor, OV5640_REG_AEC_PK_REAL_GAIN,
				  (u16)gain & 0x3ff);
पूर्ण

अटल पूर्णांक ov5640_set_स्वतःgain(काष्ठा ov5640_dev *sensor, bool on)
अणु
	वापस ov5640_mod_reg(sensor, OV5640_REG_AEC_PK_MANUAL,
			      BIT(1), on ? 0 : BIT(1));
पूर्ण

अटल पूर्णांक ov5640_set_stream_dvp(काष्ठा ov5640_dev *sensor, bool on)
अणु
	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_SYS_CTRL0, on ?
				OV5640_REG_SYS_CTRL0_SW_PWUP :
				OV5640_REG_SYS_CTRL0_SW_PWDN);
पूर्ण

अटल पूर्णांक ov5640_set_stream_mipi(काष्ठा ov5640_dev *sensor, bool on)
अणु
	पूर्णांक ret;

	/*
	 * Enable/disable the MIPI पूर्णांकerface
	 *
	 * 0x300e = on ? 0x45 : 0x40
	 *
	 * FIXME: the sensor manual (version 2.03) reports
	 * [7:5] = 000  : 1 data lane mode
	 * [7:5] = 001  : 2 data lanes mode
	 * But this settings करो not work, जबतक the following ones
	 * have been validated क्रम 2 data lanes mode.
	 *
	 * [7:5] = 010	: 2 data lanes mode
	 * [4] = 0	: Power up MIPI HS Tx
	 * [3] = 0	: Power up MIPI LS Rx
	 * [2] = 1/0	: MIPI पूर्णांकerface enable/disable
	 * [1:0] = 01/00: FIXME: 'debug'
	 */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_IO_MIPI_CTRL00,
			       on ? 0x45 : 0x40);
	अगर (ret)
		वापस ret;

	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_FRAME_CTRL01,
				on ? 0x00 : 0x0f);
पूर्ण

अटल पूर्णांक ov5640_get_sysclk(काष्ठा ov5640_dev *sensor)
अणु
	 /* calculate sysclk */
	u32 xvclk = sensor->xclk_freq / 10000;
	u32 multiplier, preभाग, VCO, sysभाग, pll_rभाग;
	u32 sclk_rभाग_map[] = अणु1, 2, 4, 8पूर्ण;
	u32 bit_भाग2x = 1, sclk_rभाग, sysclk;
	u8 temp1, temp2;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_SC_PLL_CTRL0, &temp1);
	अगर (ret)
		वापस ret;
	temp2 = temp1 & 0x0f;
	अगर (temp2 == 8 || temp2 == 10)
		bit_भाग2x = temp2 / 2;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_SC_PLL_CTRL1, &temp1);
	अगर (ret)
		वापस ret;
	sysभाग = temp1 >> 4;
	अगर (sysभाग == 0)
		sysभाग = 16;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_SC_PLL_CTRL2, &temp1);
	अगर (ret)
		वापस ret;
	multiplier = temp1;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_SC_PLL_CTRL3, &temp1);
	अगर (ret)
		वापस ret;
	preभाग = temp1 & 0x0f;
	pll_rभाग = ((temp1 >> 4) & 0x01) + 1;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_SYS_ROOT_DIVIDER, &temp1);
	अगर (ret)
		वापस ret;
	temp2 = temp1 & 0x03;
	sclk_rभाग = sclk_rभाग_map[temp2];

	अगर (!preभाग || !sysभाग || !pll_rभाग || !bit_भाग2x)
		वापस -EINVAL;

	VCO = xvclk * multiplier / preभाग;

	sysclk = VCO / sysभाग / pll_rभाग * 2 / bit_भाग2x / sclk_rभाग;

	वापस sysclk;
पूर्ण

अटल पूर्णांक ov5640_set_night_mode(काष्ठा ov5640_dev *sensor)
अणु
	 /* पढ़ो HTS from रेजिस्टर settings */
	u8 mode;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_AEC_CTRL00, &mode);
	अगर (ret)
		वापस ret;
	mode &= 0xfb;
	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL00, mode);
पूर्ण

अटल पूर्णांक ov5640_get_hts(काष्ठा ov5640_dev *sensor)
अणु
	/* पढ़ो HTS from रेजिस्टर settings */
	u16 hts;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg16(sensor, OV5640_REG_TIMING_HTS, &hts);
	अगर (ret)
		वापस ret;
	वापस hts;
पूर्ण

अटल पूर्णांक ov5640_get_vts(काष्ठा ov5640_dev *sensor)
अणु
	u16 vts;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg16(sensor, OV5640_REG_TIMING_VTS, &vts);
	अगर (ret)
		वापस ret;
	वापस vts;
पूर्ण

अटल पूर्णांक ov5640_set_vts(काष्ठा ov5640_dev *sensor, पूर्णांक vts)
अणु
	वापस ov5640_ग_लिखो_reg16(sensor, OV5640_REG_TIMING_VTS, vts);
पूर्ण

अटल पूर्णांक ov5640_get_light_freq(काष्ठा ov5640_dev *sensor)
अणु
	/* get banding filter value */
	पूर्णांक ret, light_freq = 0;
	u8 temp, temp1;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_HZ5060_CTRL01, &temp);
	अगर (ret)
		वापस ret;

	अगर (temp & 0x80) अणु
		/* manual */
		ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_HZ5060_CTRL00,
				      &temp1);
		अगर (ret)
			वापस ret;
		अगर (temp1 & 0x04) अणु
			/* 50Hz */
			light_freq = 50;
		पूर्ण अन्यथा अणु
			/* 60Hz */
			light_freq = 60;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* स्वतः */
		ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_SIGMADELTA_CTRL0C,
				      &temp1);
		अगर (ret)
			वापस ret;

		अगर (temp1 & 0x01) अणु
			/* 50Hz */
			light_freq = 50;
		पूर्ण अन्यथा अणु
			/* 60Hz */
		पूर्ण
	पूर्ण

	वापस light_freq;
पूर्ण

अटल पूर्णांक ov5640_set_bandingfilter(काष्ठा ov5640_dev *sensor)
अणु
	u32 band_step60, max_band60, band_step50, max_band50, prev_vts;
	पूर्णांक ret;

	/* पढ़ो preview PCLK */
	ret = ov5640_get_sysclk(sensor);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		वापस -EINVAL;
	sensor->prev_sysclk = ret;
	/* पढ़ो preview HTS */
	ret = ov5640_get_hts(sensor);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		वापस -EINVAL;
	sensor->prev_hts = ret;

	/* पढ़ो preview VTS */
	ret = ov5640_get_vts(sensor);
	अगर (ret < 0)
		वापस ret;
	prev_vts = ret;

	/* calculate banding filter */
	/* 60Hz */
	band_step60 = sensor->prev_sysclk * 100 / sensor->prev_hts * 100 / 120;
	ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_AEC_B60_STEP, band_step60);
	अगर (ret)
		वापस ret;
	अगर (!band_step60)
		वापस -EINVAL;
	max_band60 = (पूर्णांक)((prev_vts - 4) / band_step60);
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL0D, max_band60);
	अगर (ret)
		वापस ret;

	/* 50Hz */
	band_step50 = sensor->prev_sysclk * 100 / sensor->prev_hts;
	ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_AEC_B50_STEP, band_step50);
	अगर (ret)
		वापस ret;
	अगर (!band_step50)
		वापस -EINVAL;
	max_band50 = (पूर्णांक)((prev_vts - 4) / band_step50);
	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL0E, max_band50);
पूर्ण

अटल पूर्णांक ov5640_set_ae_target(काष्ठा ov5640_dev *sensor, पूर्णांक target)
अणु
	/* stable in high */
	u32 fast_high, fast_low;
	पूर्णांक ret;

	sensor->ae_low = target * 23 / 25;	/* 0.92 */
	sensor->ae_high = target * 27 / 25;	/* 1.08 */

	fast_high = sensor->ae_high << 1;
	अगर (fast_high > 255)
		fast_high = 255;

	fast_low = sensor->ae_low >> 1;

	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL0F, sensor->ae_high);
	अगर (ret)
		वापस ret;
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL10, sensor->ae_low);
	अगर (ret)
		वापस ret;
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL1B, sensor->ae_high);
	अगर (ret)
		वापस ret;
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL1E, sensor->ae_low);
	अगर (ret)
		वापस ret;
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL11, fast_high);
	अगर (ret)
		वापस ret;
	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_AEC_CTRL1F, fast_low);
पूर्ण

अटल पूर्णांक ov5640_get_binning(काष्ठा ov5640_dev *sensor)
अणु
	u8 temp;
	पूर्णांक ret;

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_TIMING_TC_REG21, &temp);
	अगर (ret)
		वापस ret;

	वापस temp & BIT(0);
पूर्ण

अटल पूर्णांक ov5640_set_binning(काष्ठा ov5640_dev *sensor, bool enable)
अणु
	पूर्णांक ret;

	/*
	 * TIMING TC REG21:
	 * - [0]:	Horizontal binning enable
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG21,
			     BIT(0), enable ? BIT(0) : 0);
	अगर (ret)
		वापस ret;
	/*
	 * TIMING TC REG20:
	 * - [0]:	Unकरोcumented, but hardcoded init sequences
	 *		are always setting REG21/REG20 bit 0 to same value...
	 */
	वापस ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG20,
			      BIT(0), enable ? BIT(0) : 0);
पूर्ण

अटल पूर्णांक ov5640_set_भव_channel(काष्ठा ov5640_dev *sensor)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	u8 temp, channel = भव_channel;
	पूर्णांक ret;

	अगर (channel > 3) अणु
		dev_err(&client->dev,
			"%s: wrong virtual_channel parameter, expected (0..3), got %d\n",
			__func__, channel);
		वापस -EINVAL;
	पूर्ण

	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_DEBUG_MODE, &temp);
	अगर (ret)
		वापस ret;
	temp &= ~(3 << 6);
	temp |= (channel << 6);
	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_DEBUG_MODE, temp);
पूर्ण

अटल स्थिर काष्ठा ov5640_mode_info *
ov5640_find_mode(काष्ठा ov5640_dev *sensor, क्रमागत ov5640_frame_rate fr,
		 पूर्णांक width, पूर्णांक height, bool nearest)
अणु
	स्थिर काष्ठा ov5640_mode_info *mode;

	mode = v4l2_find_nearest_size(ov5640_mode_data,
				      ARRAY_SIZE(ov5640_mode_data),
				      hact, vact,
				      width, height);

	अगर (!mode ||
	    (!nearest && (mode->hact != width || mode->vact != height)))
		वापस शून्य;

	/* Check to see अगर the current mode exceeds the max frame rate */
	अगर (ov5640_framerates[fr] > ov5640_framerates[mode->max_fps])
		वापस शून्य;

	वापस mode;
पूर्ण

अटल u64 ov5640_calc_pixel_rate(काष्ठा ov5640_dev *sensor)
अणु
	u64 rate;

	rate = sensor->current_mode->vtot * sensor->current_mode->htot;
	rate *= ov5640_framerates[sensor->current_fr];

	वापस rate;
पूर्ण

/*
 * sensor changes between scaling and subsampling, go through
 * exposure calculation
 */
अटल पूर्णांक ov5640_set_mode_exposure_calc(काष्ठा ov5640_dev *sensor,
					 स्थिर काष्ठा ov5640_mode_info *mode)
अणु
	u32 prev_shutter, prev_gain16;
	u32 cap_shutter, cap_gain16;
	u32 cap_sysclk, cap_hts, cap_vts;
	u32 light_freq, cap_bandfilt, cap_maxband;
	u32 cap_gain16_shutter;
	u8 average;
	पूर्णांक ret;

	अगर (!mode->reg_data)
		वापस -EINVAL;

	/* पढ़ो preview shutter */
	ret = ov5640_get_exposure(sensor);
	अगर (ret < 0)
		वापस ret;
	prev_shutter = ret;
	ret = ov5640_get_binning(sensor);
	अगर (ret < 0)
		वापस ret;
	अगर (ret && mode->id != OV5640_MODE_720P_1280_720 &&
	    mode->id != OV5640_MODE_1080P_1920_1080)
		prev_shutter *= 2;

	/* पढ़ो preview gain */
	ret = ov5640_get_gain(sensor);
	अगर (ret < 0)
		वापस ret;
	prev_gain16 = ret;

	/* get average */
	ret = ov5640_पढ़ो_reg(sensor, OV5640_REG_AVG_READOUT, &average);
	अगर (ret)
		वापस ret;

	/* turn off night mode क्रम capture */
	ret = ov5640_set_night_mode(sensor);
	अगर (ret < 0)
		वापस ret;

	/* Write capture setting */
	ret = ov5640_load_regs(sensor, mode);
	अगर (ret < 0)
		वापस ret;

	/* पढ़ो capture VTS */
	ret = ov5640_get_vts(sensor);
	अगर (ret < 0)
		वापस ret;
	cap_vts = ret;
	ret = ov5640_get_hts(sensor);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		वापस -EINVAL;
	cap_hts = ret;

	ret = ov5640_get_sysclk(sensor);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		वापस -EINVAL;
	cap_sysclk = ret;

	/* calculate capture banding filter */
	ret = ov5640_get_light_freq(sensor);
	अगर (ret < 0)
		वापस ret;
	light_freq = ret;

	अगर (light_freq == 60) अणु
		/* 60Hz */
		cap_bandfilt = cap_sysclk * 100 / cap_hts * 100 / 120;
	पूर्ण अन्यथा अणु
		/* 50Hz */
		cap_bandfilt = cap_sysclk * 100 / cap_hts;
	पूर्ण

	अगर (!sensor->prev_sysclk) अणु
		ret = ov5640_get_sysclk(sensor);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 0)
			वापस -EINVAL;
		sensor->prev_sysclk = ret;
	पूर्ण

	अगर (!cap_bandfilt)
		वापस -EINVAL;

	cap_maxband = (पूर्णांक)((cap_vts - 4) / cap_bandfilt);

	/* calculate capture shutter/gain16 */
	अगर (average > sensor->ae_low && average < sensor->ae_high) अणु
		/* in stable range */
		cap_gain16_shutter =
			prev_gain16 * prev_shutter *
			cap_sysclk / sensor->prev_sysclk *
			sensor->prev_hts / cap_hts *
			sensor->ae_target / average;
	पूर्ण अन्यथा अणु
		cap_gain16_shutter =
			prev_gain16 * prev_shutter *
			cap_sysclk / sensor->prev_sysclk *
			sensor->prev_hts / cap_hts;
	पूर्ण

	/* gain to shutter */
	अगर (cap_gain16_shutter < (cap_bandfilt * 16)) अणु
		/* shutter < 1/100 */
		cap_shutter = cap_gain16_shutter / 16;
		अगर (cap_shutter < 1)
			cap_shutter = 1;

		cap_gain16 = cap_gain16_shutter / cap_shutter;
		अगर (cap_gain16 < 16)
			cap_gain16 = 16;
	पूर्ण अन्यथा अणु
		अगर (cap_gain16_shutter > (cap_bandfilt * cap_maxband * 16)) अणु
			/* exposure reach max */
			cap_shutter = cap_bandfilt * cap_maxband;
			अगर (!cap_shutter)
				वापस -EINVAL;

			cap_gain16 = cap_gain16_shutter / cap_shutter;
		पूर्ण अन्यथा अणु
			/* 1/100 < (cap_shutter = n/100) =< max */
			cap_shutter =
				((पूर्णांक)(cap_gain16_shutter / 16 / cap_bandfilt))
				* cap_bandfilt;
			अगर (!cap_shutter)
				वापस -EINVAL;

			cap_gain16 = cap_gain16_shutter / cap_shutter;
		पूर्ण
	पूर्ण

	/* set capture gain */
	ret = ov5640_set_gain(sensor, cap_gain16);
	अगर (ret)
		वापस ret;

	/* ग_लिखो capture shutter */
	अगर (cap_shutter > (cap_vts - 4)) अणु
		cap_vts = cap_shutter + 4;
		ret = ov5640_set_vts(sensor, cap_vts);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* set exposure */
	वापस ov5640_set_exposure(sensor, cap_shutter);
पूर्ण

/*
 * अगर sensor changes inside scaling or subsampling
 * change mode directly
 */
अटल पूर्णांक ov5640_set_mode_direct(काष्ठा ov5640_dev *sensor,
				  स्थिर काष्ठा ov5640_mode_info *mode)
अणु
	अगर (!mode->reg_data)
		वापस -EINVAL;

	/* Write capture setting */
	वापस ov5640_load_regs(sensor, mode);
पूर्ण

अटल पूर्णांक ov5640_set_mode(काष्ठा ov5640_dev *sensor)
अणु
	स्थिर काष्ठा ov5640_mode_info *mode = sensor->current_mode;
	स्थिर काष्ठा ov5640_mode_info *orig_mode = sensor->last_mode;
	क्रमागत ov5640_करोwnsize_mode dn_mode, orig_dn_mode;
	bool स्वतः_gain = sensor->ctrls.स्वतः_gain->val == 1;
	bool स्वतः_exp =  sensor->ctrls.स्वतः_exp->val == V4L2_EXPOSURE_AUTO;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	dn_mode = mode->dn_mode;
	orig_dn_mode = orig_mode->dn_mode;

	/* स्वतः gain and exposure must be turned off when changing modes */
	अगर (स्वतः_gain) अणु
		ret = ov5640_set_स्वतःgain(sensor, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (स्वतः_exp) अणु
		ret = ov5640_set_स्वतःexposure(sensor, false);
		अगर (ret)
			जाओ restore_स्वतः_gain;
	पूर्ण

	/*
	 * All the क्रमmats we support have 16 bits per pixel, seems to require
	 * the same rate than YUV, so we can just use 16 bpp all the समय.
	 */
	rate = ov5640_calc_pixel_rate(sensor) * 16;
	अगर (sensor->ep.bus_type == V4L2_MBUS_CSI2_DPHY) अणु
		rate = rate / sensor->ep.bus.mipi_csi2.num_data_lanes;
		ret = ov5640_set_mipi_pclk(sensor, rate);
	पूर्ण अन्यथा अणु
		rate = rate / sensor->ep.bus.parallel.bus_width;
		ret = ov5640_set_dvp_pclk(sensor, rate);
	पूर्ण

	अगर (ret < 0)
		वापस 0;

	अगर ((dn_mode == SUBSAMPLING && orig_dn_mode == SCALING) ||
	    (dn_mode == SCALING && orig_dn_mode == SUBSAMPLING)) अणु
		/*
		 * change between subsampling and scaling
		 * go through exposure calculation
		 */
		ret = ov5640_set_mode_exposure_calc(sensor, mode);
	पूर्ण अन्यथा अणु
		/*
		 * change inside subsampling or scaling
		 * करोwnload firmware directly
		 */
		ret = ov5640_set_mode_direct(sensor, mode);
	पूर्ण
	अगर (ret < 0)
		जाओ restore_स्वतः_exp_gain;

	/* restore स्वतः gain and exposure */
	अगर (स्वतः_gain)
		ov5640_set_स्वतःgain(sensor, true);
	अगर (स्वतः_exp)
		ov5640_set_स्वतःexposure(sensor, true);

	ret = ov5640_set_binning(sensor, dn_mode != SCALING);
	अगर (ret < 0)
		वापस ret;
	ret = ov5640_set_ae_target(sensor, sensor->ae_target);
	अगर (ret < 0)
		वापस ret;
	ret = ov5640_get_light_freq(sensor);
	अगर (ret < 0)
		वापस ret;
	ret = ov5640_set_bandingfilter(sensor);
	अगर (ret < 0)
		वापस ret;
	ret = ov5640_set_भव_channel(sensor);
	अगर (ret < 0)
		वापस ret;

	sensor->pending_mode_change = false;
	sensor->last_mode = mode;

	वापस 0;

restore_स्वतः_exp_gain:
	अगर (स्वतः_exp)
		ov5640_set_स्वतःexposure(sensor, true);
restore_स्वतः_gain:
	अगर (स्वतः_gain)
		ov5640_set_स्वतःgain(sensor, true);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_set_framefmt(काष्ठा ov5640_dev *sensor,
			       काष्ठा v4l2_mbus_framefmt *क्रमmat);

/* restore the last set video mode after chip घातer-on */
अटल पूर्णांक ov5640_restore_mode(काष्ठा ov5640_dev *sensor)
अणु
	पूर्णांक ret;

	/* first load the initial रेजिस्टर values */
	ret = ov5640_load_regs(sensor, &ov5640_mode_init_data);
	अगर (ret < 0)
		वापस ret;
	sensor->last_mode = &ov5640_mode_init_data;

	ret = ov5640_mod_reg(sensor, OV5640_REG_SYS_ROOT_DIVIDER, 0x3f,
			     (ilog2(OV5640_SCLK2X_ROOT_DIV) << 2) |
			     ilog2(OV5640_SCLK_ROOT_DIV));
	अगर (ret)
		वापस ret;

	/* now restore the last capture mode */
	ret = ov5640_set_mode(sensor);
	अगर (ret < 0)
		वापस ret;

	वापस ov5640_set_framefmt(sensor, &sensor->fmt);
पूर्ण

अटल व्योम ov5640_घातer(काष्ठा ov5640_dev *sensor, bool enable)
अणु
	gpiod_set_value_cansleep(sensor->pwdn_gpio, enable ? 0 : 1);
पूर्ण

अटल व्योम ov5640_reset(काष्ठा ov5640_dev *sensor)
अणु
	अगर (!sensor->reset_gpio)
		वापस;

	gpiod_set_value_cansleep(sensor->reset_gpio, 0);

	/* camera घातer cycle */
	ov5640_घातer(sensor, false);
	usleep_range(5000, 10000);
	ov5640_घातer(sensor, true);
	usleep_range(5000, 10000);

	gpiod_set_value_cansleep(sensor->reset_gpio, 1);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(sensor->reset_gpio, 0);
	usleep_range(20000, 25000);
पूर्ण

अटल पूर्णांक ov5640_set_घातer_on(काष्ठा ov5640_dev *sensor)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	पूर्णांक ret;

	ret = clk_prepare_enable(sensor->xclk);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: failed to enable clock\n",
			__func__);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(OV5640_NUM_SUPPLIES,
				    sensor->supplies);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: failed to enable regulators\n",
			__func__);
		जाओ xclk_off;
	पूर्ण

	ov5640_reset(sensor);
	ov5640_घातer(sensor, true);

	ret = ov5640_init_slave_id(sensor);
	अगर (ret)
		जाओ घातer_off;

	वापस 0;

घातer_off:
	ov5640_घातer(sensor, false);
	regulator_bulk_disable(OV5640_NUM_SUPPLIES, sensor->supplies);
xclk_off:
	clk_disable_unprepare(sensor->xclk);
	वापस ret;
पूर्ण

अटल व्योम ov5640_set_घातer_off(काष्ठा ov5640_dev *sensor)
अणु
	ov5640_घातer(sensor, false);
	regulator_bulk_disable(OV5640_NUM_SUPPLIES, sensor->supplies);
	clk_disable_unprepare(sensor->xclk);
पूर्ण

अटल पूर्णांक ov5640_set_घातer_mipi(काष्ठा ov5640_dev *sensor, bool on)
अणु
	पूर्णांक ret;

	अगर (!on) अणु
		/* Reset MIPI bus settings to their शेष values. */
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_IO_MIPI_CTRL00, 0x58);
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_MIPI_CTRL00, 0x04);
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_PAD_OUTPUT00, 0x00);
		वापस 0;
	पूर्ण

	/*
	 * Power up MIPI HS Tx and LS Rx; 2 data lanes mode
	 *
	 * 0x300e = 0x40
	 * [7:5] = 010	: 2 data lanes mode (see FIXME note in
	 *		  "ov5640_set_stream_mipi()")
	 * [4] = 0	: Power up MIPI HS Tx
	 * [3] = 0	: Power up MIPI LS Rx
	 * [2] = 0	: MIPI पूर्णांकerface disabled
	 */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_IO_MIPI_CTRL00, 0x40);
	अगर (ret)
		वापस ret;

	/*
	 * Gate घड़ी and set LP11 in 'no packets mode' (idle)
	 *
	 * 0x4800 = 0x24
	 * [5] = 1	: Gate घड़ी when 'no packets'
	 * [2] = 1	: MIPI bus in LP11 when 'no packets'
	 */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_MIPI_CTRL00, 0x24);
	अगर (ret)
		वापस ret;

	/*
	 * Set data lanes and घड़ी in LP11 when 'sleeping'
	 *
	 * 0x3019 = 0x70
	 * [6] = 1	: MIPI data lane 2 in LP11 when 'sleeping'
	 * [5] = 1	: MIPI data lane 1 in LP11 when 'sleeping'
	 * [4] = 1	: MIPI घड़ी lane in LP11 when 'sleeping'
	 */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_PAD_OUTPUT00, 0x70);
	अगर (ret)
		वापस ret;

	/* Give lanes some समय to coax पूर्णांकo LP11 state. */
	usleep_range(500, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_set_घातer_dvp(काष्ठा ov5640_dev *sensor, bool on)
अणु
	अचिन्हित पूर्णांक flags = sensor->ep.bus.parallel.flags;
	bool bt656 = sensor->ep.bus_type == V4L2_MBUS_BT656;
	u8 polarities = 0;
	पूर्णांक ret;

	अगर (!on) अणु
		/* Reset settings to their शेष values. */
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_CCIR656_CTRL00, 0x00);
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_IO_MIPI_CTRL00, 0x58);
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_POLARITY_CTRL00, 0x20);
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_PAD_OUTPUT_ENABLE01, 0x00);
		ov5640_ग_लिखो_reg(sensor, OV5640_REG_PAD_OUTPUT_ENABLE02, 0x00);
		वापस 0;
	पूर्ण

	/*
	 * Note about parallel port configuration.
	 *
	 * When configured in parallel mode, the OV5640 will
	 * output 10 bits data on DVP data lines [9:0].
	 * If only 8 bits data are wanted, the 8 bits data lines
	 * of the camera पूर्णांकerface must be physically connected
	 * on the DVP data lines [9:2].
	 *
	 * Control lines polarity can be configured through
	 * devicetree endpoपूर्णांक control lines properties.
	 * If no endpoपूर्णांक control lines properties are set,
	 * polarity will be as below:
	 * - VSYNC:	active high
	 * - HREF:	active low
	 * - PCLK:	active low
	 *
	 * VSYNC & HREF are not configured अगर BT656 bus mode is selected
	 */

	/*
	 * BT656 embedded synchronization configuration
	 *
	 * CCIR656 CTRL00
	 * - [7]:	SYNC code selection (0: स्वतः generate sync code,
	 *		1: sync code from regs 0x4732-0x4735)
	 * - [6]:	f value in CCIR656 SYNC code when fixed f value
	 * - [5]:	Fixed f value
	 * - [4:3]:	Blank toggle data options (00: data=1'h040/1'h200,
	 *		01: data from regs 0x4736-0x4738, 10: always keep 0)
	 * - [1]:	Clip data disable
	 * - [0]:	CCIR656 mode enable
	 *
	 * Default CCIR656 SAV/EAV mode with शेष codes
	 * SAV=0xff000080 & EAV=0xff00009d is enabled here with settings:
	 * - CCIR656 mode enable
	 * - स्वतः generation of sync codes
	 * - blank toggle data 1'h040/1'h200
	 * - clip reserved data (0x00 & 0xff changed to 0x01 & 0xfe)
	 */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_CCIR656_CTRL00,
			       bt656 ? 0x01 : 0x00);
	अगर (ret)
		वापस ret;

	/*
	 * configure parallel port control lines polarity
	 *
	 * POLARITY CTRL0
	 * - [5]:	PCLK polarity (0: active low, 1: active high)
	 * - [1]:	HREF polarity (0: active low, 1: active high)
	 * - [0]:	VSYNC polarity (mismatch here between
	 *		datasheet and hardware, 0 is active high
	 *		and 1 is active low...)
	 */
	अगर (!bt656) अणु
		अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
			polarities |= BIT(1);
		अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			polarities |= BIT(0);
	पूर्ण
	अगर (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		polarities |= BIT(5);

	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_POLARITY_CTRL00, polarities);
	अगर (ret)
		वापस ret;

	/*
	 * घातerकरोwn MIPI TX/RX PHY & enable DVP
	 *
	 * MIPI CONTROL 00
	 * [4] = 1	: Power करोwn MIPI HS Tx
	 * [3] = 1	: Power करोwn MIPI LS Rx
	 * [2] = 0	: DVP enable (MIPI disable)
	 */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_IO_MIPI_CTRL00, 0x18);
	अगर (ret)
		वापस ret;

	/*
	 * enable VSYNC/HREF/PCLK DVP control lines
	 * & D[9:6] DVP data lines
	 *
	 * PAD OUTPUT ENABLE 01
	 * - 6:		VSYNC output enable
	 * - 5:		HREF output enable
	 * - 4:		PCLK output enable
	 * - [3:0]:	D[9:6] output enable
	 */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_PAD_OUTPUT_ENABLE01,
			       bt656 ? 0x1f : 0x7f);
	अगर (ret)
		वापस ret;

	/*
	 * enable D[5:0] DVP data lines
	 *
	 * PAD OUTPUT ENABLE 02
	 * - [7:2]:	D[5:0] output enable
	 */
	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_PAD_OUTPUT_ENABLE02, 0xfc);
पूर्ण

अटल पूर्णांक ov5640_set_घातer(काष्ठा ov5640_dev *sensor, bool on)
अणु
	पूर्णांक ret = 0;

	अगर (on) अणु
		ret = ov5640_set_घातer_on(sensor);
		अगर (ret)
			वापस ret;

		ret = ov5640_restore_mode(sensor);
		अगर (ret)
			जाओ घातer_off;
	पूर्ण

	अगर (sensor->ep.bus_type == V4L2_MBUS_CSI2_DPHY)
		ret = ov5640_set_घातer_mipi(sensor, on);
	अन्यथा
		ret = ov5640_set_घातer_dvp(sensor, on);
	अगर (ret)
		जाओ घातer_off;

	अगर (!on)
		ov5640_set_घातer_off(sensor);

	वापस 0;

घातer_off:
	ov5640_set_घातer_off(sensor);
	वापस ret;
पूर्ण

/* --------------- Subdev Operations --------------- */

अटल पूर्णांक ov5640_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	पूर्णांक ret = 0;

	mutex_lock(&sensor->lock);

	/*
	 * If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (sensor->घातer_count == !on) अणु
		ret = ov5640_set_घातer(sensor, !!on);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Update the घातer count. */
	sensor->घातer_count += on ? 1 : -1;
	WARN_ON(sensor->घातer_count < 0);
out:
	mutex_unlock(&sensor->lock);

	अगर (on && !ret && sensor->घातer_count == 1) अणु
		/* restore controls */
		ret = v4l2_ctrl_handler_setup(&sensor->ctrls.handler);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_try_frame_पूर्णांकerval(काष्ठा ov5640_dev *sensor,
				     काष्ठा v4l2_fract *fi,
				     u32 width, u32 height)
अणु
	स्थिर काष्ठा ov5640_mode_info *mode;
	क्रमागत ov5640_frame_rate rate = OV5640_15_FPS;
	पूर्णांक minfps, maxfps, best_fps, fps;
	पूर्णांक i;

	minfps = ov5640_framerates[OV5640_15_FPS];
	maxfps = ov5640_framerates[OV5640_60_FPS];

	अगर (fi->numerator == 0) अणु
		fi->denominator = maxfps;
		fi->numerator = 1;
		rate = OV5640_60_FPS;
		जाओ find_mode;
	पूर्ण

	fps = clamp_val(DIV_ROUND_CLOSEST(fi->denominator, fi->numerator),
			minfps, maxfps);

	best_fps = minfps;
	क्रम (i = 0; i < ARRAY_SIZE(ov5640_framerates); i++) अणु
		पूर्णांक curr_fps = ov5640_framerates[i];

		अगर (असल(curr_fps - fps) < असल(best_fps - fps)) अणु
			best_fps = curr_fps;
			rate = i;
		पूर्ण
	पूर्ण

	fi->numerator = 1;
	fi->denominator = best_fps;

find_mode:
	mode = ov5640_find_mode(sensor, rate, width, height, false);
	वापस mode ? rate : -EINVAL;
पूर्ण

अटल पूर्णांक ov5640_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;

	अगर (क्रमmat->pad != 0)
		वापस -EINVAL;

	mutex_lock(&sensor->lock);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt = v4l2_subdev_get_try_क्रमmat(&sensor->sd, cfg,
						 क्रमmat->pad);
	अन्यथा
		fmt = &sensor->fmt;

	क्रमmat->क्रमmat = *fmt;

	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_try_fmt_पूर्णांकernal(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_mbus_framefmt *fmt,
				   क्रमागत ov5640_frame_rate fr,
				   स्थिर काष्ठा ov5640_mode_info **new_mode)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	स्थिर काष्ठा ov5640_mode_info *mode;
	पूर्णांक i;

	mode = ov5640_find_mode(sensor, fr, fmt->width, fmt->height, true);
	अगर (!mode)
		वापस -EINVAL;
	fmt->width = mode->hact;
	fmt->height = mode->vact;

	अगर (new_mode)
		*new_mode = mode;

	क्रम (i = 0; i < ARRAY_SIZE(ov5640_क्रमmats); i++)
		अगर (ov5640_क्रमmats[i].code == fmt->code)
			अवरोध;
	अगर (i >= ARRAY_SIZE(ov5640_क्रमmats))
		i = 0;

	fmt->code = ov5640_क्रमmats[i].code;
	fmt->colorspace = ov5640_क्रमmats[i].colorspace;
	fmt->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	fmt->quantization = V4L2_QUANTIZATION_FULL_RANGE;
	fmt->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(fmt->colorspace);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	स्थिर काष्ठा ov5640_mode_info *new_mode;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &क्रमmat->क्रमmat;
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret;

	अगर (क्रमmat->pad != 0)
		वापस -EINVAL;

	mutex_lock(&sensor->lock);

	अगर (sensor->streaming) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = ov5640_try_fmt_पूर्णांकernal(sd, mbus_fmt,
				      sensor->current_fr, &new_mode);
	अगर (ret)
		जाओ out;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	अन्यथा
		fmt = &sensor->fmt;

	*fmt = *mbus_fmt;

	अगर (new_mode != sensor->current_mode) अणु
		sensor->current_mode = new_mode;
		sensor->pending_mode_change = true;
	पूर्ण
	अगर (mbus_fmt->code != sensor->fmt.code)
		sensor->pending_fmt_change = true;

	__v4l2_ctrl_s_ctrl_पूर्णांक64(sensor->ctrls.pixel_rate,
				 ov5640_calc_pixel_rate(sensor));
out:
	mutex_unlock(&sensor->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_set_framefmt(काष्ठा ov5640_dev *sensor,
			       काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	पूर्णांक ret = 0;
	bool is_jpeg = false;
	u8 fmt, mux;

	चयन (क्रमmat->code) अणु
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		/* YUV422, UYVY */
		fmt = 0x3f;
		mux = OV5640_FMT_MUX_YUV422;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		/* YUV422, YUYV */
		fmt = 0x30;
		mux = OV5640_FMT_MUX_YUV422;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
		/* RGB565 अणुg[2:0],b[4:0]पूर्ण,अणुr[4:0],g[5:3]पूर्ण */
		fmt = 0x6F;
		mux = OV5640_FMT_MUX_RGB;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
		/* RGB565 अणुr[4:0],g[5:3]पूर्ण,अणुg[2:0],b[4:0]पूर्ण */
		fmt = 0x61;
		mux = OV5640_FMT_MUX_RGB;
		अवरोध;
	हाल MEDIA_BUS_FMT_JPEG_1X8:
		/* YUV422, YUYV */
		fmt = 0x30;
		mux = OV5640_FMT_MUX_YUV422;
		is_jpeg = true;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		/* Raw, BGBG... / GRGR... */
		fmt = 0x00;
		mux = OV5640_FMT_MUX_RAW_DPC;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
		/* Raw bayer, GBGB... / RGRG... */
		fmt = 0x01;
		mux = OV5640_FMT_MUX_RAW_DPC;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
		/* Raw bayer, GRGR... / BGBG... */
		fmt = 0x02;
		mux = OV5640_FMT_MUX_RAW_DPC;
		अवरोध;
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		/* Raw bayer, RGRG... / GBGB... */
		fmt = 0x03;
		mux = OV5640_FMT_MUX_RAW_DPC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* FORMAT CONTROL00: YUV and RGB क्रमmatting */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_FORMAT_CONTROL00, fmt);
	अगर (ret)
		वापस ret;

	/* FORMAT MUX CONTROL: ISP YUV or RGB */
	ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_ISP_FORMAT_MUX_CTRL, mux);
	अगर (ret)
		वापस ret;

	/*
	 * TIMING TC REG21:
	 * - [5]:	JPEG enable
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG21,
			     BIT(5), is_jpeg ? BIT(5) : 0);
	अगर (ret)
		वापस ret;

	/*
	 * SYSTEM RESET02:
	 * - [4]:	Reset JFIFO
	 * - [3]:	Reset SFIFO
	 * - [2]:	Reset JPEG
	 */
	ret = ov5640_mod_reg(sensor, OV5640_REG_SYS_RESET02,
			     BIT(4) | BIT(3) | BIT(2),
			     is_jpeg ? 0 : (BIT(4) | BIT(3) | BIT(2)));
	अगर (ret)
		वापस ret;

	/*
	 * CLOCK ENABLE02:
	 * - [5]:	Enable JPEG 2x घड़ी
	 * - [3]:	Enable JPEG घड़ी
	 */
	वापस ov5640_mod_reg(sensor, OV5640_REG_SYS_CLOCK_ENABLE02,
			      BIT(5) | BIT(3),
			      is_jpeg ? (BIT(5) | BIT(3)) : 0);
पूर्ण

/*
 * Sensor Controls.
 */

अटल पूर्णांक ov5640_set_ctrl_hue(काष्ठा ov5640_dev *sensor, पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (value) अणु
		ret = ov5640_mod_reg(sensor, OV5640_REG_SDE_CTRL0,
				     BIT(0), BIT(0));
		अगर (ret)
			वापस ret;
		ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_SDE_CTRL1, value);
	पूर्ण अन्यथा अणु
		ret = ov5640_mod_reg(sensor, OV5640_REG_SDE_CTRL0, BIT(0), 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_contrast(काष्ठा ov5640_dev *sensor, पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (value) अणु
		ret = ov5640_mod_reg(sensor, OV5640_REG_SDE_CTRL0,
				     BIT(2), BIT(2));
		अगर (ret)
			वापस ret;
		ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_SDE_CTRL5,
				       value & 0xff);
	पूर्ण अन्यथा अणु
		ret = ov5640_mod_reg(sensor, OV5640_REG_SDE_CTRL0, BIT(2), 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_saturation(काष्ठा ov5640_dev *sensor, पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (value) अणु
		ret = ov5640_mod_reg(sensor, OV5640_REG_SDE_CTRL0,
				     BIT(1), BIT(1));
		अगर (ret)
			वापस ret;
		ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_SDE_CTRL3,
				       value & 0xff);
		अगर (ret)
			वापस ret;
		ret = ov5640_ग_लिखो_reg(sensor, OV5640_REG_SDE_CTRL4,
				       value & 0xff);
	पूर्ण अन्यथा अणु
		ret = ov5640_mod_reg(sensor, OV5640_REG_SDE_CTRL0, BIT(1), 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_white_balance(काष्ठा ov5640_dev *sensor, पूर्णांक awb)
अणु
	पूर्णांक ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_AWB_MANUAL_CTRL,
			     BIT(0), awb ? 0 : 1);
	अगर (ret)
		वापस ret;

	अगर (!awb) अणु
		u16 red = (u16)sensor->ctrls.red_balance->val;
		u16 blue = (u16)sensor->ctrls.blue_balance->val;

		ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_AWB_R_GAIN, red);
		अगर (ret)
			वापस ret;
		ret = ov5640_ग_लिखो_reg16(sensor, OV5640_REG_AWB_B_GAIN, blue);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_exposure(काष्ठा ov5640_dev *sensor,
				    क्रमागत v4l2_exposure_स्वतः_type स्वतः_exposure)
अणु
	काष्ठा ov5640_ctrls *ctrls = &sensor->ctrls;
	bool स्वतः_exp = (स्वतः_exposure == V4L2_EXPOSURE_AUTO);
	पूर्णांक ret = 0;

	अगर (ctrls->स्वतः_exp->is_new) अणु
		ret = ov5640_set_स्वतःexposure(sensor, स्वतः_exp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!स्वतः_exp && ctrls->exposure->is_new) अणु
		u16 max_exp;

		ret = ov5640_पढ़ो_reg16(sensor, OV5640_REG_AEC_PK_VTS,
					&max_exp);
		अगर (ret)
			वापस ret;
		ret = ov5640_get_vts(sensor);
		अगर (ret < 0)
			वापस ret;
		max_exp += ret;
		ret = 0;

		अगर (ctrls->exposure->val < max_exp)
			ret = ov5640_set_exposure(sensor, ctrls->exposure->val);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_gain(काष्ठा ov5640_dev *sensor, bool स्वतः_gain)
अणु
	काष्ठा ov5640_ctrls *ctrls = &sensor->ctrls;
	पूर्णांक ret = 0;

	अगर (ctrls->स्वतः_gain->is_new) अणु
		ret = ov5640_set_स्वतःgain(sensor, स्वतः_gain);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!स्वतः_gain && ctrls->gain->is_new)
		ret = ov5640_set_gain(sensor, ctrls->gain->val);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर test_pattern_menu[] = अणु
	"Disabled",
	"Color bars",
	"Color bars w/ rolling bar",
	"Color squares",
	"Color squares w/ rolling bar",
पूर्ण;

#घोषणा OV5640_TEST_ENABLE		BIT(7)
#घोषणा OV5640_TEST_ROLLING		BIT(6)	/* rolling horizontal bar */
#घोषणा OV5640_TEST_TRANSPARENT		BIT(5)
#घोषणा OV5640_TEST_SQUARE_BW		BIT(4)	/* black & white squares */
#घोषणा OV5640_TEST_BAR_STANDARD	(0 << 2)
#घोषणा OV5640_TEST_BAR_VERT_CHANGE_1	(1 << 2)
#घोषणा OV5640_TEST_BAR_HOR_CHANGE	(2 << 2)
#घोषणा OV5640_TEST_BAR_VERT_CHANGE_2	(3 << 2)
#घोषणा OV5640_TEST_BAR			(0 << 0)
#घोषणा OV5640_TEST_RANDOM		(1 << 0)
#घोषणा OV5640_TEST_SQUARE		(2 << 0)
#घोषणा OV5640_TEST_BLACK		(3 << 0)

अटल स्थिर u8 test_pattern_val[] = अणु
	0,
	OV5640_TEST_ENABLE | OV5640_TEST_BAR_VERT_CHANGE_1 |
		OV5640_TEST_BAR,
	OV5640_TEST_ENABLE | OV5640_TEST_ROLLING |
		OV5640_TEST_BAR_VERT_CHANGE_1 | OV5640_TEST_BAR,
	OV5640_TEST_ENABLE | OV5640_TEST_SQUARE,
	OV5640_TEST_ENABLE | OV5640_TEST_ROLLING | OV5640_TEST_SQUARE,
पूर्ण;

अटल पूर्णांक ov5640_set_ctrl_test_pattern(काष्ठा ov5640_dev *sensor, पूर्णांक value)
अणु
	वापस ov5640_ग_लिखो_reg(sensor, OV5640_REG_PRE_ISP_TEST_SET1,
				test_pattern_val[value]);
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_light_freq(काष्ठा ov5640_dev *sensor, पूर्णांक value)
अणु
	पूर्णांक ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_HZ5060_CTRL01, BIT(7),
			     (value == V4L2_CID_POWER_LINE_FREQUENCY_AUTO) ?
			     0 : BIT(7));
	अगर (ret)
		वापस ret;

	वापस ov5640_mod_reg(sensor, OV5640_REG_HZ5060_CTRL00, BIT(2),
			      (value == V4L2_CID_POWER_LINE_FREQUENCY_50HZ) ?
			      BIT(2) : 0);
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_hflip(काष्ठा ov5640_dev *sensor, पूर्णांक value)
अणु
	/*
	 * If sensor is mounted upside करोwn, mirror logic is inversed.
	 *
	 * Sensor is a BSI (Back Side Illuminated) one,
	 * so image captured is physically mirrored.
	 * This is why mirror logic is inversed in
	 * order to cancel this mirror effect.
	 */

	/*
	 * TIMING TC REG21:
	 * - [2]:	ISP mirror
	 * - [1]:	Sensor mirror
	 */
	वापस ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG21,
			      BIT(2) | BIT(1),
			      (!(value ^ sensor->upside_करोwn)) ?
			      (BIT(2) | BIT(1)) : 0);
पूर्ण

अटल पूर्णांक ov5640_set_ctrl_vflip(काष्ठा ov5640_dev *sensor, पूर्णांक value)
अणु
	/* If sensor is mounted upside करोwn, flip logic is inversed */

	/*
	 * TIMING TC REG20:
	 * - [2]:	ISP vflip
	 * - [1]:	Sensor vflip
	 */
	वापस ov5640_mod_reg(sensor, OV5640_REG_TIMING_TC_REG20,
			      BIT(2) | BIT(1),
			      (value ^ sensor->upside_करोwn) ?
			      (BIT(2) | BIT(1)) : 0);
पूर्ण

अटल पूर्णांक ov5640_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	पूर्णांक val;

	/* v4l2_ctrl_lock() locks our own mutex */

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		val = ov5640_get_gain(sensor);
		अगर (val < 0)
			वापस val;
		sensor->ctrls.gain->val = val;
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		val = ov5640_get_exposure(sensor);
		अगर (val < 0)
			वापस val;
		sensor->ctrls.exposure->val = val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	पूर्णांक ret;

	/* v4l2_ctrl_lock() locks our own mutex */

	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any controls to H/W at this समय. Instead
	 * the controls will be restored right after घातer-up.
	 */
	अगर (sensor->घातer_count == 0)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		ret = ov5640_set_ctrl_gain(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov5640_set_ctrl_exposure(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov5640_set_ctrl_white_balance(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		ret = ov5640_set_ctrl_hue(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = ov5640_set_ctrl_contrast(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		ret = ov5640_set_ctrl_saturation(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = ov5640_set_ctrl_test_pattern(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		ret = ov5640_set_ctrl_light_freq(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		ret = ov5640_set_ctrl_hflip(sensor, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		ret = ov5640_set_ctrl_vflip(sensor, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov5640_ctrl_ops = अणु
	.g_अस्थिर_ctrl = ov5640_g_अस्थिर_ctrl,
	.s_ctrl = ov5640_s_ctrl,
पूर्ण;

अटल पूर्णांक ov5640_init_controls(काष्ठा ov5640_dev *sensor)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &ov5640_ctrl_ops;
	काष्ठा ov5640_ctrls *ctrls = &sensor->ctrls;
	काष्ठा v4l2_ctrl_handler *hdl = &ctrls->handler;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(hdl, 32);

	/* we can use our own mutex क्रम the ctrl lock */
	hdl->lock = &sensor->lock;

	/* Clock related controls */
	ctrls->pixel_rate = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_PIXEL_RATE,
					      0, पूर्णांक_उच्च, 1,
					      ov5640_calc_pixel_rate(sensor));

	/* Auto/manual white balance */
	ctrls->स्वतः_wb = v4l2_ctrl_new_std(hdl, ops,
					   V4L2_CID_AUTO_WHITE_BALANCE,
					   0, 1, 1, 1);
	ctrls->blue_balance = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BLUE_BALANCE,
						0, 4095, 1, 0);
	ctrls->red_balance = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_RED_BALANCE,
					       0, 4095, 1, 0);
	/* Auto/manual exposure */
	ctrls->स्वतः_exp = v4l2_ctrl_new_std_menu(hdl, ops,
						 V4L2_CID_EXPOSURE_AUTO,
						 V4L2_EXPOSURE_MANUAL, 0,
						 V4L2_EXPOSURE_AUTO);
	ctrls->exposure = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_EXPOSURE,
					    0, 65535, 1, 0);
	/* Auto/manual gain */
	ctrls->स्वतः_gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTOGAIN,
					     0, 1, 1, 1);
	ctrls->gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAIN,
					0, 1023, 1, 0);

	ctrls->saturation = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SATURATION,
					      0, 255, 1, 64);
	ctrls->hue = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_HUE,
				       0, 359, 1, 0);
	ctrls->contrast = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST,
					    0, 255, 1, 0);
	ctrls->test_pattern =
		v4l2_ctrl_new_std_menu_items(hdl, ops, V4L2_CID_TEST_PATTERN,
					     ARRAY_SIZE(test_pattern_menu) - 1,
					     0, 0, test_pattern_menu);
	ctrls->hflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_HFLIP,
					 0, 1, 1, 0);
	ctrls->vflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_VFLIP,
					 0, 1, 1, 0);

	ctrls->light_freq =
		v4l2_ctrl_new_std_menu(hdl, ops,
				       V4L2_CID_POWER_LINE_FREQUENCY,
				       V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
				       V4L2_CID_POWER_LINE_FREQUENCY_50HZ);

	अगर (hdl->error) अणु
		ret = hdl->error;
		जाओ मुक्त_ctrls;
	पूर्ण

	ctrls->pixel_rate->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	ctrls->gain->flags |= V4L2_CTRL_FLAG_VOLATILE;
	ctrls->exposure->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_स्वतः_cluster(3, &ctrls->स्वतः_wb, 0, false);
	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_gain, 0, true);
	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_exp, 1, true);

	sensor->sd.ctrl_handler = hdl;
	वापस 0;

मुक्त_ctrls:
	v4l2_ctrl_handler_मुक्त(hdl);
	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->pad != 0)
		वापस -EINVAL;
	अगर (fse->index >= OV5640_NUM_MODES)
		वापस -EINVAL;

	fse->min_width =
		ov5640_mode_data[fse->index].hact;
	fse->max_width = fse->min_width;
	fse->min_height =
		ov5640_mode_data[fse->index].vact;
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_क्रमागत_frame_पूर्णांकerval(
	काष्ठा v4l2_subdev *sd,
	काष्ठा v4l2_subdev_pad_config *cfg,
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	काष्ठा v4l2_fract tpf;
	पूर्णांक ret;

	अगर (fie->pad != 0)
		वापस -EINVAL;
	अगर (fie->index >= OV5640_NUM_FRAMERATES)
		वापस -EINVAL;

	tpf.numerator = 1;
	tpf.denominator = ov5640_framerates[fie->index];

	ret = ov5640_try_frame_पूर्णांकerval(sensor, &tpf,
					fie->width, fie->height);
	अगर (ret < 0)
		वापस -EINVAL;

	fie->पूर्णांकerval = tpf;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);

	mutex_lock(&sensor->lock);
	fi->पूर्णांकerval = sensor->frame_पूर्णांकerval;
	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	स्थिर काष्ठा ov5640_mode_info *mode;
	पूर्णांक frame_rate, ret = 0;

	अगर (fi->pad != 0)
		वापस -EINVAL;

	mutex_lock(&sensor->lock);

	अगर (sensor->streaming) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	mode = sensor->current_mode;

	frame_rate = ov5640_try_frame_पूर्णांकerval(sensor, &fi->पूर्णांकerval,
					       mode->hact, mode->vact);
	अगर (frame_rate < 0) अणु
		/* Always वापस a valid frame पूर्णांकerval value */
		fi->पूर्णांकerval = sensor->frame_पूर्णांकerval;
		जाओ out;
	पूर्ण

	mode = ov5640_find_mode(sensor, frame_rate, mode->hact,
				mode->vact, true);
	अगर (!mode) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (mode != sensor->current_mode ||
	    frame_rate != sensor->current_fr) अणु
		sensor->current_fr = frame_rate;
		sensor->frame_पूर्णांकerval = fi->पूर्णांकerval;
		sensor->current_mode = mode;
		sensor->pending_mode_change = true;

		__v4l2_ctrl_s_ctrl_पूर्णांक64(sensor->ctrls.pixel_rate,
					 ov5640_calc_pixel_rate(sensor));
	पूर्ण
out:
	mutex_unlock(&sensor->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad != 0)
		वापस -EINVAL;
	अगर (code->index >= ARRAY_SIZE(ov5640_क्रमmats))
		वापस -EINVAL;

	code->code = ov5640_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक ov5640_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);
	पूर्णांक ret = 0;

	mutex_lock(&sensor->lock);

	अगर (sensor->streaming == !enable) अणु
		अगर (enable && sensor->pending_mode_change) अणु
			ret = ov5640_set_mode(sensor);
			अगर (ret)
				जाओ out;
		पूर्ण

		अगर (enable && sensor->pending_fmt_change) अणु
			ret = ov5640_set_framefmt(sensor, &sensor->fmt);
			अगर (ret)
				जाओ out;
			sensor->pending_fmt_change = false;
		पूर्ण

		अगर (sensor->ep.bus_type == V4L2_MBUS_CSI2_DPHY)
			ret = ov5640_set_stream_mipi(sensor, enable);
		अन्यथा
			ret = ov5640_set_stream_dvp(sensor, enable);

		अगर (!ret)
			sensor->streaming = enable;
	पूर्ण
out:
	mutex_unlock(&sensor->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov5640_core_ops = अणु
	.s_घातer = ov5640_s_घातer,
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov5640_video_ops = अणु
	.g_frame_पूर्णांकerval = ov5640_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = ov5640_s_frame_पूर्णांकerval,
	.s_stream = ov5640_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov5640_pad_ops = अणु
	.क्रमागत_mbus_code = ov5640_क्रमागत_mbus_code,
	.get_fmt = ov5640_get_fmt,
	.set_fmt = ov5640_set_fmt,
	.क्रमागत_frame_size = ov5640_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval = ov5640_क्रमागत_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov5640_subdev_ops = अणु
	.core = &ov5640_core_ops,
	.video = &ov5640_video_ops,
	.pad = &ov5640_pad_ops,
पूर्ण;

अटल पूर्णांक ov5640_get_regulators(काष्ठा ov5640_dev *sensor)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OV5640_NUM_SUPPLIES; i++)
		sensor->supplies[i].supply = ov5640_supply_name[i];

	वापस devm_regulator_bulk_get(&sensor->i2c_client->dev,
				       OV5640_NUM_SUPPLIES,
				       sensor->supplies);
पूर्ण

अटल पूर्णांक ov5640_check_chip_id(काष्ठा ov5640_dev *sensor)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	पूर्णांक ret = 0;
	u16 chip_id;

	ret = ov5640_set_घातer_on(sensor);
	अगर (ret)
		वापस ret;

	ret = ov5640_पढ़ो_reg16(sensor, OV5640_REG_CHIP_ID, &chip_id);
	अगर (ret) अणु
		dev_err(&client->dev, "%s: failed to read chip identifier\n",
			__func__);
		जाओ घातer_off;
	पूर्ण

	अगर (chip_id != 0x5640) अणु
		dev_err(&client->dev, "%s: wrong chip identifier, expected 0x5640, got 0x%x\n",
			__func__, chip_id);
		ret = -ENXIO;
	पूर्ण

घातer_off:
	ov5640_set_घातer_off(sensor);
	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा fwnode_handle *endpoपूर्णांक;
	काष्ठा ov5640_dev *sensor;
	काष्ठा v4l2_mbus_framefmt *fmt;
	u32 rotation;
	पूर्णांक ret;

	sensor = devm_kzalloc(dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	sensor->i2c_client = client;

	/*
	 * शेष init sequence initialize sensor to
	 * YUV422 UYVY VGA@30fps
	 */
	fmt = &sensor->fmt;
	fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	fmt->quantization = V4L2_QUANTIZATION_FULL_RANGE;
	fmt->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(fmt->colorspace);
	fmt->width = 640;
	fmt->height = 480;
	fmt->field = V4L2_FIELD_NONE;
	sensor->frame_पूर्णांकerval.numerator = 1;
	sensor->frame_पूर्णांकerval.denominator = ov5640_framerates[OV5640_30_FPS];
	sensor->current_fr = OV5640_30_FPS;
	sensor->current_mode =
		&ov5640_mode_data[OV5640_MODE_VGA_640_480];
	sensor->last_mode = sensor->current_mode;

	sensor->ae_target = 52;

	/* optional indication of physical rotation of sensor */
	ret = fwnode_property_पढ़ो_u32(dev_fwnode(&client->dev), "rotation",
				       &rotation);
	अगर (!ret) अणु
		चयन (rotation) अणु
		हाल 180:
			sensor->upside_करोwn = true;
			fallthrough;
		हाल 0:
			अवरोध;
		शेष:
			dev_warn(dev, "%u degrees rotation is not supported, ignoring...\n",
				 rotation);
		पूर्ण
	पूर्ण

	endpoपूर्णांक = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(&client->dev),
						  शून्य);
	अगर (!endpoपूर्णांक) अणु
		dev_err(dev, "endpoint node not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(endpoपूर्णांक, &sensor->ep);
	fwnode_handle_put(endpoपूर्णांक);
	अगर (ret) अणु
		dev_err(dev, "Could not parse endpoint\n");
		वापस ret;
	पूर्ण

	अगर (sensor->ep.bus_type != V4L2_MBUS_PARALLEL &&
	    sensor->ep.bus_type != V4L2_MBUS_CSI2_DPHY &&
	    sensor->ep.bus_type != V4L2_MBUS_BT656) अणु
		dev_err(dev, "Unsupported bus type %d\n", sensor->ep.bus_type);
		वापस -EINVAL;
	पूर्ण

	/* get प्रणाली घड़ी (xclk) */
	sensor->xclk = devm_clk_get(dev, "xclk");
	अगर (IS_ERR(sensor->xclk)) अणु
		dev_err(dev, "failed to get xclk\n");
		वापस PTR_ERR(sensor->xclk);
	पूर्ण

	sensor->xclk_freq = clk_get_rate(sensor->xclk);
	अगर (sensor->xclk_freq < OV5640_XCLK_MIN ||
	    sensor->xclk_freq > OV5640_XCLK_MAX) अणु
		dev_err(dev, "xclk frequency out of range: %d Hz\n",
			sensor->xclk_freq);
		वापस -EINVAL;
	पूर्ण

	/* request optional घातer करोwn pin */
	sensor->pwdn_gpio = devm_gpiod_get_optional(dev, "powerdown",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(sensor->pwdn_gpio))
		वापस PTR_ERR(sensor->pwdn_gpio);

	/* request optional reset pin */
	sensor->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_HIGH);
	अगर (IS_ERR(sensor->reset_gpio))
		वापस PTR_ERR(sensor->reset_gpio);

	v4l2_i2c_subdev_init(&sensor->sd, client, &ov5640_subdev_ops);

	sensor->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
			    V4L2_SUBDEV_FL_HAS_EVENTS;
	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	sensor->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sensor->sd.entity, 1, &sensor->pad);
	अगर (ret)
		वापस ret;

	ret = ov5640_get_regulators(sensor);
	अगर (ret)
		वापस ret;

	mutex_init(&sensor->lock);

	ret = ov5640_check_chip_id(sensor);
	अगर (ret)
		जाओ entity_cleanup;

	ret = ov5640_init_controls(sensor);
	अगर (ret)
		जाओ entity_cleanup;

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&sensor->sd);
	अगर (ret)
		जाओ मुक्त_ctrls;

	वापस 0;

मुक्त_ctrls:
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls.handler);
entity_cleanup:
	media_entity_cleanup(&sensor->sd.entity);
	mutex_destroy(&sensor->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ov5640_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov5640_dev *sensor = to_ov5640_dev(sd);

	v4l2_async_unरेजिस्टर_subdev(&sensor->sd);
	media_entity_cleanup(&sensor->sd.entity);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls.handler);
	mutex_destroy(&sensor->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov5640_id[] = अणु
	अणु"ov5640", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov5640_id);

अटल स्थिर काष्ठा of_device_id ov5640_dt_ids[] = अणु
	अणु .compatible = "ovti,ov5640" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov5640_dt_ids);

अटल काष्ठा i2c_driver ov5640_i2c_driver = अणु
	.driver = अणु
		.name  = "ov5640",
		.of_match_table	= ov5640_dt_ids,
	पूर्ण,
	.id_table = ov5640_id,
	.probe_new = ov5640_probe,
	.हटाओ   = ov5640_हटाओ,
पूर्ण;

module_i2c_driver(ov5640_i2c_driver);

MODULE_DESCRIPTION("OV5640 MIPI Camera Subdev Driver");
MODULE_LICENSE("GPL");
