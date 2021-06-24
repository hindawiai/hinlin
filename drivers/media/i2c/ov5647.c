<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A V4L2 driver क्रम OmniVision OV5647 cameras.
 *
 * Based on Samsung S5K6AAFX SXGA 1/6" 1.3M CMOS Image Sensor driver
 * Copyright (C) 2011 Sylwester Nawrocki <s.nawrocki@samsung.com>
 *
 * Based on Omnivision OV7670 Camera Driver
 * Copyright (C) 2006-7 Jonathan Corbet <corbet@lwn.net>
 *
 * Copyright (C) 2016, Synopsys, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-mediabus.h>

/*
 * From the datasheet, "20ms after PWDN goes low or 20ms after RESETB goes
 * high अगर reset is inserted after PWDN goes high, host can access sensor's
 * SCCB to initialize sensor."
 */
#घोषणा PWDN_ACTIVE_DELAY_MS	20

#घोषणा MIPI_CTRL00_CLOCK_LANE_GATE		BIT(5)
#घोषणा MIPI_CTRL00_LINE_SYNC_ENABLE		BIT(4)
#घोषणा MIPI_CTRL00_BUS_IDLE			BIT(2)
#घोषणा MIPI_CTRL00_CLOCK_LANE_DISABLE		BIT(0)

#घोषणा OV5647_SW_STANDBY		0x0100
#घोषणा OV5647_SW_RESET			0x0103
#घोषणा OV5647_REG_CHIPID_H		0x300a
#घोषणा OV5647_REG_CHIPID_L		0x300b
#घोषणा OV5640_REG_PAD_OUT		0x300d
#घोषणा OV5647_REG_EXP_HI		0x3500
#घोषणा OV5647_REG_EXP_MID		0x3501
#घोषणा OV5647_REG_EXP_LO		0x3502
#घोषणा OV5647_REG_AEC_AGC		0x3503
#घोषणा OV5647_REG_GAIN_HI		0x350a
#घोषणा OV5647_REG_GAIN_LO		0x350b
#घोषणा OV5647_REG_VTS_HI		0x380e
#घोषणा OV5647_REG_VTS_LO		0x380f
#घोषणा OV5647_REG_FRAME_OFF_NUMBER	0x4202
#घोषणा OV5647_REG_MIPI_CTRL00		0x4800
#घोषणा OV5647_REG_MIPI_CTRL14		0x4814
#घोषणा OV5647_REG_AWB			0x5001

#घोषणा REG_TERM 0xfffe
#घोषणा VAL_TERM 0xfe
#घोषणा REG_DLY  0xffff

/* OV5647 native and active pixel array size */
#घोषणा OV5647_NATIVE_WIDTH		2624U
#घोषणा OV5647_NATIVE_HEIGHT		1956U

#घोषणा OV5647_PIXEL_ARRAY_LEFT		16U
#घोषणा OV5647_PIXEL_ARRAY_TOP		16U
#घोषणा OV5647_PIXEL_ARRAY_WIDTH	2592U
#घोषणा OV5647_PIXEL_ARRAY_HEIGHT	1944U

#घोषणा OV5647_VBLANK_MIN		4
#घोषणा OV5647_VTS_MAX			32767

#घोषणा OV5647_EXPOSURE_MIN		4
#घोषणा OV5647_EXPOSURE_STEP		1
#घोषणा OV5647_EXPOSURE_DEFAULT		1000
#घोषणा OV5647_EXPOSURE_MAX		65535

काष्ठा regval_list अणु
	u16 addr;
	u8 data;
पूर्ण;

काष्ठा ov5647_mode अणु
	काष्ठा v4l2_mbus_framefmt	क्रमmat;
	काष्ठा v4l2_rect		crop;
	u64				pixel_rate;
	पूर्णांक				hts;
	पूर्णांक				vts;
	स्थिर काष्ठा regval_list	*reg_list;
	अचिन्हित पूर्णांक			num_regs;
पूर्ण;

काष्ठा ov5647 अणु
	काष्ठा v4l2_subdev		sd;
	काष्ठा media_pad		pad;
	काष्ठा mutex			lock;
	काष्ठा clk			*xclk;
	काष्ठा gpio_desc		*pwdn;
	bool				घड़ी_ncont;
	काष्ठा v4l2_ctrl_handler	ctrls;
	स्थिर काष्ठा ov5647_mode	*mode;
	काष्ठा v4l2_ctrl		*pixel_rate;
	काष्ठा v4l2_ctrl		*hblank;
	काष्ठा v4l2_ctrl		*vblank;
	काष्ठा v4l2_ctrl		*exposure;
	bool				streaming;
पूर्ण;

अटल अंतरभूत काष्ठा ov5647 *to_sensor(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov5647, sd);
पूर्ण

अटल स्थिर काष्ठा regval_list sensor_oe_disable_regs[] = अणु
	अणु0x3000, 0x00पूर्ण,
	अणु0x3001, 0x00पूर्ण,
	अणु0x3002, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regval_list sensor_oe_enable_regs[] = अणु
	अणु0x3000, 0x0fपूर्ण,
	अणु0x3001, 0xffपूर्ण,
	अणु0x3002, 0xe4पूर्ण,
पूर्ण;

अटल काष्ठा regval_list ov5647_2592x1944_10bpp[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x0103, 0x01पूर्ण,
	अणु0x3034, 0x1aपूर्ण,
	अणु0x3035, 0x21पूर्ण,
	अणु0x3036, 0x69पूर्ण,
	अणु0x303c, 0x11पूर्ण,
	अणु0x3106, 0xf5पूर्ण,
	अणु0x3821, 0x06पूर्ण,
	अणु0x3820, 0x00पूर्ण,
	अणु0x3827, 0xecपूर्ण,
	अणु0x370c, 0x03पूर्ण,
	अणु0x3612, 0x5bपूर्ण,
	अणु0x3618, 0x04पूर्ण,
	अणु0x5000, 0x06पूर्ण,
	अणु0x5002, 0x41पूर्ण,
	अणु0x5003, 0x08पूर्ण,
	अणु0x5a00, 0x08पूर्ण,
	अणु0x3000, 0x00पूर्ण,
	अणु0x3001, 0x00पूर्ण,
	अणु0x3002, 0x00पूर्ण,
	अणु0x3016, 0x08पूर्ण,
	अणु0x3017, 0xe0पूर्ण,
	अणु0x3018, 0x44पूर्ण,
	अणु0x301c, 0xf8पूर्ण,
	अणु0x301d, 0xf0पूर्ण,
	अणु0x3a18, 0x00पूर्ण,
	अणु0x3a19, 0xf8पूर्ण,
	अणु0x3c01, 0x80पूर्ण,
	अणु0x3b07, 0x0cपूर्ण,
	अणु0x380c, 0x0bपूर्ण,
	अणु0x380d, 0x1cपूर्ण,
	अणु0x3814, 0x11पूर्ण,
	अणु0x3815, 0x11पूर्ण,
	अणु0x3708, 0x64पूर्ण,
	अणु0x3709, 0x12पूर्ण,
	अणु0x3808, 0x0aपूर्ण,
	अणु0x3809, 0x20पूर्ण,
	अणु0x380a, 0x07पूर्ण,
	अणु0x380b, 0x98पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xa3पूर्ण,
	अणु0x3811, 0x10पूर्ण,
	अणु0x3813, 0x06पूर्ण,
	अणु0x3630, 0x2eपूर्ण,
	अणु0x3632, 0xe2पूर्ण,
	अणु0x3633, 0x23पूर्ण,
	अणु0x3634, 0x44पूर्ण,
	अणु0x3636, 0x06पूर्ण,
	अणु0x3620, 0x64पूर्ण,
	अणु0x3621, 0xe0पूर्ण,
	अणु0x3600, 0x37पूर्ण,
	अणु0x3704, 0xa0पूर्ण,
	अणु0x3703, 0x5aपूर्ण,
	अणु0x3715, 0x78पूर्ण,
	अणु0x3717, 0x01पूर्ण,
	अणु0x3731, 0x02पूर्ण,
	अणु0x370b, 0x60पूर्ण,
	अणु0x3705, 0x1aपूर्ण,
	अणु0x3f05, 0x02पूर्ण,
	अणु0x3f06, 0x10पूर्ण,
	अणु0x3f01, 0x0aपूर्ण,
	अणु0x3a08, 0x01पूर्ण,
	अणु0x3a09, 0x28पूर्ण,
	अणु0x3a0a, 0x00पूर्ण,
	अणु0x3a0b, 0xf6पूर्ण,
	अणु0x3a0d, 0x08पूर्ण,
	अणु0x3a0e, 0x06पूर्ण,
	अणु0x3a0f, 0x58पूर्ण,
	अणु0x3a10, 0x50पूर्ण,
	अणु0x3a1b, 0x58पूर्ण,
	अणु0x3a1e, 0x50पूर्ण,
	अणु0x3a11, 0x60पूर्ण,
	अणु0x3a1f, 0x28पूर्ण,
	अणु0x4001, 0x02पूर्ण,
	अणु0x4004, 0x04पूर्ण,
	अणु0x4000, 0x09पूर्ण,
	अणु0x4837, 0x19पूर्ण,
	अणु0x4800, 0x24पूर्ण,
	अणु0x3503, 0x03पूर्ण,
	अणु0x0100, 0x01पूर्ण,
पूर्ण;

अटल काष्ठा regval_list ov5647_1080p30_10bpp[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x0103, 0x01पूर्ण,
	अणु0x3034, 0x1aपूर्ण,
	अणु0x3035, 0x21पूर्ण,
	अणु0x3036, 0x62पूर्ण,
	अणु0x303c, 0x11पूर्ण,
	अणु0x3106, 0xf5पूर्ण,
	अणु0x3821, 0x06पूर्ण,
	अणु0x3820, 0x00पूर्ण,
	अणु0x3827, 0xecपूर्ण,
	अणु0x370c, 0x03पूर्ण,
	अणु0x3612, 0x5bपूर्ण,
	अणु0x3618, 0x04पूर्ण,
	अणु0x5000, 0x06पूर्ण,
	अणु0x5002, 0x41पूर्ण,
	अणु0x5003, 0x08पूर्ण,
	अणु0x5a00, 0x08पूर्ण,
	अणु0x3000, 0x00पूर्ण,
	अणु0x3001, 0x00पूर्ण,
	अणु0x3002, 0x00पूर्ण,
	अणु0x3016, 0x08पूर्ण,
	अणु0x3017, 0xe0पूर्ण,
	अणु0x3018, 0x44पूर्ण,
	अणु0x301c, 0xf8पूर्ण,
	अणु0x301d, 0xf0पूर्ण,
	अणु0x3a18, 0x00पूर्ण,
	अणु0x3a19, 0xf8पूर्ण,
	अणु0x3c01, 0x80पूर्ण,
	अणु0x3b07, 0x0cपूर्ण,
	अणु0x380c, 0x09पूर्ण,
	अणु0x380d, 0x70पूर्ण,
	अणु0x3814, 0x11पूर्ण,
	अणु0x3815, 0x11पूर्ण,
	अणु0x3708, 0x64पूर्ण,
	अणु0x3709, 0x12पूर्ण,
	अणु0x3808, 0x07पूर्ण,
	अणु0x3809, 0x80पूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0x38पूर्ण,
	अणु0x3800, 0x01पूर्ण,
	अणु0x3801, 0x5cपूर्ण,
	अणु0x3802, 0x01पूर्ण,
	अणु0x3803, 0xb2पूर्ण,
	अणु0x3804, 0x08पूर्ण,
	अणु0x3805, 0xe3पूर्ण,
	अणु0x3806, 0x05पूर्ण,
	अणु0x3807, 0xf1पूर्ण,
	अणु0x3811, 0x04पूर्ण,
	अणु0x3813, 0x02पूर्ण,
	अणु0x3630, 0x2eपूर्ण,
	अणु0x3632, 0xe2पूर्ण,
	अणु0x3633, 0x23पूर्ण,
	अणु0x3634, 0x44पूर्ण,
	अणु0x3636, 0x06पूर्ण,
	अणु0x3620, 0x64पूर्ण,
	अणु0x3621, 0xe0पूर्ण,
	अणु0x3600, 0x37पूर्ण,
	अणु0x3704, 0xa0पूर्ण,
	अणु0x3703, 0x5aपूर्ण,
	अणु0x3715, 0x78पूर्ण,
	अणु0x3717, 0x01पूर्ण,
	अणु0x3731, 0x02पूर्ण,
	अणु0x370b, 0x60पूर्ण,
	अणु0x3705, 0x1aपूर्ण,
	अणु0x3f05, 0x02पूर्ण,
	अणु0x3f06, 0x10पूर्ण,
	अणु0x3f01, 0x0aपूर्ण,
	अणु0x3a08, 0x01पूर्ण,
	अणु0x3a09, 0x4bपूर्ण,
	अणु0x3a0a, 0x01पूर्ण,
	अणु0x3a0b, 0x13पूर्ण,
	अणु0x3a0d, 0x04पूर्ण,
	अणु0x3a0e, 0x03पूर्ण,
	अणु0x3a0f, 0x58पूर्ण,
	अणु0x3a10, 0x50पूर्ण,
	अणु0x3a1b, 0x58पूर्ण,
	अणु0x3a1e, 0x50पूर्ण,
	अणु0x3a11, 0x60पूर्ण,
	अणु0x3a1f, 0x28पूर्ण,
	अणु0x4001, 0x02पूर्ण,
	अणु0x4004, 0x04पूर्ण,
	अणु0x4000, 0x09पूर्ण,
	अणु0x4837, 0x19पूर्ण,
	अणु0x4800, 0x34पूर्ण,
	अणु0x3503, 0x03पूर्ण,
	अणु0x0100, 0x01पूर्ण,
पूर्ण;

अटल काष्ठा regval_list ov5647_2x2binned_10bpp[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x0103, 0x01पूर्ण,
	अणु0x3034, 0x1aपूर्ण,
	अणु0x3035, 0x21पूर्ण,
	अणु0x3036, 0x62पूर्ण,
	अणु0x303c, 0x11पूर्ण,
	अणु0x3106, 0xf5पूर्ण,
	अणु0x3827, 0xecपूर्ण,
	अणु0x370c, 0x03पूर्ण,
	अणु0x3612, 0x59पूर्ण,
	अणु0x3618, 0x00पूर्ण,
	अणु0x5000, 0x06पूर्ण,
	अणु0x5002, 0x41पूर्ण,
	अणु0x5003, 0x08पूर्ण,
	अणु0x5a00, 0x08पूर्ण,
	अणु0x3000, 0x00पूर्ण,
	अणु0x3001, 0x00पूर्ण,
	अणु0x3002, 0x00पूर्ण,
	अणु0x3016, 0x08पूर्ण,
	अणु0x3017, 0xe0पूर्ण,
	अणु0x3018, 0x44पूर्ण,
	अणु0x301c, 0xf8पूर्ण,
	अणु0x301d, 0xf0पूर्ण,
	अणु0x3a18, 0x00पूर्ण,
	अणु0x3a19, 0xf8पूर्ण,
	अणु0x3c01, 0x80पूर्ण,
	अणु0x3b07, 0x0cपूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x3fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0xa3पूर्ण,
	अणु0x3808, 0x05पूर्ण,
	अणु0x3809, 0x10पूर्ण,
	अणु0x380a, 0x03पूर्ण,
	अणु0x380b, 0xccपूर्ण,
	अणु0x380c, 0x07पूर्ण,
	अणु0x380d, 0x68पूर्ण,
	अणु0x3811, 0x0cपूर्ण,
	अणु0x3813, 0x06पूर्ण,
	अणु0x3814, 0x31पूर्ण,
	अणु0x3815, 0x31पूर्ण,
	अणु0x3630, 0x2eपूर्ण,
	अणु0x3632, 0xe2पूर्ण,
	अणु0x3633, 0x23पूर्ण,
	अणु0x3634, 0x44पूर्ण,
	अणु0x3636, 0x06पूर्ण,
	अणु0x3620, 0x64पूर्ण,
	अणु0x3621, 0xe0पूर्ण,
	अणु0x3600, 0x37पूर्ण,
	अणु0x3704, 0xa0पूर्ण,
	अणु0x3703, 0x5aपूर्ण,
	अणु0x3715, 0x78पूर्ण,
	अणु0x3717, 0x01पूर्ण,
	अणु0x3731, 0x02पूर्ण,
	अणु0x370b, 0x60पूर्ण,
	अणु0x3705, 0x1aपूर्ण,
	अणु0x3f05, 0x02पूर्ण,
	अणु0x3f06, 0x10पूर्ण,
	अणु0x3f01, 0x0aपूर्ण,
	अणु0x3a08, 0x01पूर्ण,
	अणु0x3a09, 0x28पूर्ण,
	अणु0x3a0a, 0x00पूर्ण,
	अणु0x3a0b, 0xf6पूर्ण,
	अणु0x3a0d, 0x08पूर्ण,
	अणु0x3a0e, 0x06पूर्ण,
	अणु0x3a0f, 0x58पूर्ण,
	अणु0x3a10, 0x50पूर्ण,
	अणु0x3a1b, 0x58पूर्ण,
	अणु0x3a1e, 0x50पूर्ण,
	अणु0x3a11, 0x60पूर्ण,
	अणु0x3a1f, 0x28पूर्ण,
	अणु0x4001, 0x02पूर्ण,
	अणु0x4004, 0x04पूर्ण,
	अणु0x4000, 0x09पूर्ण,
	अणु0x4837, 0x16पूर्ण,
	अणु0x4800, 0x24पूर्ण,
	अणु0x3503, 0x03पूर्ण,
	अणु0x3820, 0x41पूर्ण,
	अणु0x3821, 0x07पूर्ण,
	अणु0x350a, 0x00पूर्ण,
	अणु0x350b, 0x10पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x1aपूर्ण,
	अणु0x3502, 0xf0पूर्ण,
	अणु0x3212, 0xa0पूर्ण,
	अणु0x0100, 0x01पूर्ण,
पूर्ण;

अटल काष्ठा regval_list ov5647_640x480_10bpp[] = अणु
	अणु0x0100, 0x00पूर्ण,
	अणु0x0103, 0x01पूर्ण,
	अणु0x3035, 0x11पूर्ण,
	अणु0x3036, 0x46पूर्ण,
	अणु0x303c, 0x11पूर्ण,
	अणु0x3821, 0x07पूर्ण,
	अणु0x3820, 0x41पूर्ण,
	अणु0x370c, 0x03पूर्ण,
	अणु0x3612, 0x59पूर्ण,
	अणु0x3618, 0x00पूर्ण,
	अणु0x5000, 0x06पूर्ण,
	अणु0x5003, 0x08पूर्ण,
	अणु0x5a00, 0x08पूर्ण,
	अणु0x3000, 0xffपूर्ण,
	अणु0x3001, 0xffपूर्ण,
	अणु0x3002, 0xffपूर्ण,
	अणु0x301d, 0xf0पूर्ण,
	अणु0x3a18, 0x00पूर्ण,
	अणु0x3a19, 0xf8पूर्ण,
	अणु0x3c01, 0x80पूर्ण,
	अणु0x3b07, 0x0cपूर्ण,
	अणु0x380c, 0x07पूर्ण,
	अणु0x380d, 0x3cपूर्ण,
	अणु0x3814, 0x35पूर्ण,
	अणु0x3815, 0x35पूर्ण,
	अणु0x3708, 0x64पूर्ण,
	अणु0x3709, 0x52पूर्ण,
	अणु0x3808, 0x02पूर्ण,
	अणु0x3809, 0x80पूर्ण,
	अणु0x380a, 0x01पूर्ण,
	अणु0x380b, 0xe0पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x10पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x0aपूर्ण,
	अणु0x3805, 0x2fपूर्ण,
	अणु0x3806, 0x07पूर्ण,
	अणु0x3807, 0x9fपूर्ण,
	अणु0x3630, 0x2eपूर्ण,
	अणु0x3632, 0xe2पूर्ण,
	अणु0x3633, 0x23पूर्ण,
	अणु0x3634, 0x44पूर्ण,
	अणु0x3620, 0x64पूर्ण,
	अणु0x3621, 0xe0पूर्ण,
	अणु0x3600, 0x37पूर्ण,
	अणु0x3704, 0xa0पूर्ण,
	अणु0x3703, 0x5aपूर्ण,
	अणु0x3715, 0x78पूर्ण,
	अणु0x3717, 0x01पूर्ण,
	अणु0x3731, 0x02पूर्ण,
	अणु0x370b, 0x60पूर्ण,
	अणु0x3705, 0x1aपूर्ण,
	अणु0x3f05, 0x02पूर्ण,
	अणु0x3f06, 0x10पूर्ण,
	अणु0x3f01, 0x0aपूर्ण,
	अणु0x3a08, 0x01पूर्ण,
	अणु0x3a09, 0x2eपूर्ण,
	अणु0x3a0a, 0x00पूर्ण,
	अणु0x3a0b, 0xfbपूर्ण,
	अणु0x3a0d, 0x02पूर्ण,
	अणु0x3a0e, 0x01पूर्ण,
	अणु0x3a0f, 0x58पूर्ण,
	अणु0x3a10, 0x50पूर्ण,
	अणु0x3a1b, 0x58पूर्ण,
	अणु0x3a1e, 0x50पूर्ण,
	अणु0x3a11, 0x60पूर्ण,
	अणु0x3a1f, 0x28पूर्ण,
	अणु0x4001, 0x02पूर्ण,
	अणु0x4004, 0x02पूर्ण,
	अणु0x4000, 0x09पूर्ण,
	अणु0x3000, 0x00पूर्ण,
	अणु0x3001, 0x00पूर्ण,
	अणु0x3002, 0x00पूर्ण,
	अणु0x3017, 0xe0पूर्ण,
	अणु0x301c, 0xfcपूर्ण,
	अणु0x3636, 0x06पूर्ण,
	अणु0x3016, 0x08पूर्ण,
	अणु0x3827, 0xecपूर्ण,
	अणु0x3018, 0x44पूर्ण,
	अणु0x3035, 0x21पूर्ण,
	अणु0x3106, 0xf5पूर्ण,
	अणु0x3034, 0x1aपूर्ण,
	अणु0x301c, 0xf8पूर्ण,
	अणु0x4800, 0x34पूर्ण,
	अणु0x3503, 0x03पूर्ण,
	अणु0x0100, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov5647_mode ov5647_modes[] = अणु
	/* 2592x1944 full resolution full FOV 10-bit mode. */
	अणु
		.क्रमmat = अणु
			.code		= MEDIA_BUS_FMT_SBGGR10_1X10,
			.colorspace	= V4L2_COLORSPACE_SRGB,
			.field		= V4L2_FIELD_NONE,
			.width		= 2592,
			.height		= 1944
		पूर्ण,
		.crop = अणु
			.left		= OV5647_PIXEL_ARRAY_LEFT,
			.top		= OV5647_PIXEL_ARRAY_TOP,
			.width		= 2592,
			.height		= 1944
		पूर्ण,
		.pixel_rate	= 87500000,
		.hts		= 2844,
		.vts		= 0x7b0,
		.reg_list	= ov5647_2592x1944_10bpp,
		.num_regs	= ARRAY_SIZE(ov5647_2592x1944_10bpp)
	पूर्ण,
	/* 1080p30 10-bit mode. Full resolution centre-cropped करोwn to 1080p. */
	अणु
		.क्रमmat = अणु
			.code		= MEDIA_BUS_FMT_SBGGR10_1X10,
			.colorspace	= V4L2_COLORSPACE_SRGB,
			.field		= V4L2_FIELD_NONE,
			.width		= 1920,
			.height		= 1080
		पूर्ण,
		.crop = अणु
			.left		= 348 + OV5647_PIXEL_ARRAY_LEFT,
			.top		= 434 + OV5647_PIXEL_ARRAY_TOP,
			.width		= 1928,
			.height		= 1080,
		पूर्ण,
		.pixel_rate	= 81666700,
		.hts		= 2416,
		.vts		= 0x450,
		.reg_list	= ov5647_1080p30_10bpp,
		.num_regs	= ARRAY_SIZE(ov5647_1080p30_10bpp)
	पूर्ण,
	/* 2x2 binned full FOV 10-bit mode. */
	अणु
		.क्रमmat = अणु
			.code		= MEDIA_BUS_FMT_SBGGR10_1X10,
			.colorspace	= V4L2_COLORSPACE_SRGB,
			.field		= V4L2_FIELD_NONE,
			.width		= 1296,
			.height		= 972
		पूर्ण,
		.crop = अणु
			.left		= OV5647_PIXEL_ARRAY_LEFT,
			.top		= OV5647_PIXEL_ARRAY_TOP,
			.width		= 2592,
			.height		= 1944,
		पूर्ण,
		.pixel_rate	= 81666700,
		.hts		= 1896,
		.vts		= 0x59b,
		.reg_list	= ov5647_2x2binned_10bpp,
		.num_regs	= ARRAY_SIZE(ov5647_2x2binned_10bpp)
	पूर्ण,
	/* 10-bit VGA full FOV 60fps. 2x2 binned and subsampled करोwn to VGA. */
	अणु
		.क्रमmat = अणु
			.code		= MEDIA_BUS_FMT_SBGGR10_1X10,
			.colorspace	= V4L2_COLORSPACE_SRGB,
			.field		= V4L2_FIELD_NONE,
			.width		= 640,
			.height		= 480
		पूर्ण,
		.crop = अणु
			.left		= 16 + OV5647_PIXEL_ARRAY_LEFT,
			.top		= OV5647_PIXEL_ARRAY_TOP,
			.width		= 2560,
			.height		= 1920,
		पूर्ण,
		.pixel_rate	= 55000000,
		.hts		= 1852,
		.vts		= 0x1f8,
		.reg_list	= ov5647_640x480_10bpp,
		.num_regs	= ARRAY_SIZE(ov5647_640x480_10bpp)
	पूर्ण,
पूर्ण;

/* Default sensor mode is 2x2 binned 640x480 SBGGR10_1X10. */
#घोषणा OV5647_DEFAULT_MODE	(&ov5647_modes[3])
#घोषणा OV5647_DEFAULT_FORMAT	(ov5647_modes[3].क्रमmat)

अटल पूर्णांक ov5647_ग_लिखो16(काष्ठा v4l2_subdev *sd, u16 reg, u16 val)
अणु
	अचिन्हित अक्षर data[4] = अणु reg >> 8, reg & 0xff, val >> 8, val & 0xffपूर्ण;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	ret = i2c_master_send(client, data, 4);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "%s: i2c write error, reg: %x\n",
			__func__, reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_ग_लिखो(काष्ठा v4l2_subdev *sd, u16 reg, u8 val)
अणु
	अचिन्हित अक्षर data[3] = अणु reg >> 8, reg & 0xff, valपूर्ण;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	ret = i2c_master_send(client, data, 3);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "%s: i2c write error, reg: %x\n",
				__func__, reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_पढ़ो(काष्ठा v4l2_subdev *sd, u16 reg, u8 *val)
अणु
	अचिन्हित अक्षर data_w[2] = अणु reg >> 8, reg & 0xff पूर्ण;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	ret = i2c_master_send(client, data_w, 2);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "%s: i2c write error, reg: %x\n",
			__func__, reg);
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(client, val, 1);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "%s: i2c read error, reg: %x\n",
				__func__, reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_ग_लिखो_array(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा regval_list *regs, पूर्णांक array_size)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < array_size; i++) अणु
		ret = ov5647_ग_लिखो(sd, regs[i].addr, regs[i].data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_set_भव_channel(काष्ठा v4l2_subdev *sd, पूर्णांक channel)
अणु
	u8 channel_id;
	पूर्णांक ret;

	ret = ov5647_पढ़ो(sd, OV5647_REG_MIPI_CTRL14, &channel_id);
	अगर (ret < 0)
		वापस ret;

	channel_id &= ~(3 << 6);

	वापस ov5647_ग_लिखो(sd, OV5647_REG_MIPI_CTRL14,
			    channel_id | (channel << 6));
पूर्ण

अटल पूर्णांक ov5647_set_mode(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov5647 *sensor = to_sensor(sd);
	u8 resetval, rdval;
	पूर्णांक ret;

	ret = ov5647_पढ़ो(sd, OV5647_SW_STANDBY, &rdval);
	अगर (ret < 0)
		वापस ret;

	ret = ov5647_ग_लिखो_array(sd, sensor->mode->reg_list,
				 sensor->mode->num_regs);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "write sensor default regs error\n");
		वापस ret;
	पूर्ण

	ret = ov5647_set_भव_channel(sd, 0);
	अगर (ret < 0)
		वापस ret;

	ret = ov5647_पढ़ो(sd, OV5647_SW_STANDBY, &resetval);
	अगर (ret < 0)
		वापस ret;

	अगर (!(resetval & 0x01)) अणु
		dev_err(&client->dev, "Device was in SW standby");
		ret = ov5647_ग_लिखो(sd, OV5647_SW_STANDBY, 0x01);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_stream_on(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov5647 *sensor = to_sensor(sd);
	u8 val = MIPI_CTRL00_BUS_IDLE;
	पूर्णांक ret;

	ret = ov5647_set_mode(sd);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to program sensor mode: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Apply customized values from user when stream starts. */
	ret =  __v4l2_ctrl_handler_setup(sd->ctrl_handler);
	अगर (ret)
		वापस ret;

	अगर (sensor->घड़ी_ncont)
		val |= MIPI_CTRL00_CLOCK_LANE_GATE |
		       MIPI_CTRL00_LINE_SYNC_ENABLE;

	ret = ov5647_ग_लिखो(sd, OV5647_REG_MIPI_CTRL00, val);
	अगर (ret < 0)
		वापस ret;

	ret = ov5647_ग_लिखो(sd, OV5647_REG_FRAME_OFF_NUMBER, 0x00);
	अगर (ret < 0)
		वापस ret;

	वापस ov5647_ग_लिखो(sd, OV5640_REG_PAD_OUT, 0x00);
पूर्ण

अटल पूर्णांक ov5647_stream_off(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक ret;

	ret = ov5647_ग_लिखो(sd, OV5647_REG_MIPI_CTRL00,
			   MIPI_CTRL00_CLOCK_LANE_GATE | MIPI_CTRL00_BUS_IDLE |
			   MIPI_CTRL00_CLOCK_LANE_DISABLE);
	अगर (ret < 0)
		वापस ret;

	ret = ov5647_ग_लिखो(sd, OV5647_REG_FRAME_OFF_NUMBER, 0x0f);
	अगर (ret < 0)
		वापस ret;

	वापस ov5647_ग_लिखो(sd, OV5640_REG_PAD_OUT, 0x01);
पूर्ण

अटल पूर्णांक ov5647_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा ov5647 *sensor = dev_get_drvdata(dev);
	पूर्णांक ret;

	dev_dbg(dev, "OV5647 power on\n");

	अगर (sensor->pwdn) अणु
		gpiod_set_value_cansleep(sensor->pwdn, 0);
		msleep(PWDN_ACTIVE_DELAY_MS);
	पूर्ण

	ret = clk_prepare_enable(sensor->xclk);
	अगर (ret < 0) अणु
		dev_err(dev, "clk prepare enable failed\n");
		जाओ error_pwdn;
	पूर्ण

	ret = ov5647_ग_लिखो_array(&sensor->sd, sensor_oe_enable_regs,
				 ARRAY_SIZE(sensor_oe_enable_regs));
	अगर (ret < 0) अणु
		dev_err(dev, "write sensor_oe_enable_regs error\n");
		जाओ error_clk_disable;
	पूर्ण

	/* Stream off to coax lanes पूर्णांकo LP-11 state. */
	ret = ov5647_stream_off(&sensor->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "camera not available, check power\n");
		जाओ error_clk_disable;
	पूर्ण

	वापस 0;

error_clk_disable:
	clk_disable_unprepare(sensor->xclk);
error_pwdn:
	gpiod_set_value_cansleep(sensor->pwdn, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5647_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा ov5647 *sensor = dev_get_drvdata(dev);
	u8 rdval;
	पूर्णांक ret;

	dev_dbg(dev, "OV5647 power off\n");

	ret = ov5647_ग_लिखो_array(&sensor->sd, sensor_oe_disable_regs,
				 ARRAY_SIZE(sensor_oe_disable_regs));
	अगर (ret < 0)
		dev_dbg(dev, "disable oe failed\n");

	/* Enter software standby */
	ret = ov5647_पढ़ो(&sensor->sd, OV5647_SW_STANDBY, &rdval);
	अगर (ret < 0)
		dev_dbg(dev, "software standby failed\n");

	rdval &= ~0x01;
	ret = ov5647_ग_लिखो(&sensor->sd, OV5647_SW_STANDBY, rdval);
	अगर (ret < 0)
		dev_dbg(dev, "software standby failed\n");

	clk_disable_unprepare(sensor->xclk);
	gpiod_set_value_cansleep(sensor->pwdn, 1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ov5647_sensor_get_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	पूर्णांक ret;
	u8 val;

	ret = ov5647_पढ़ो(sd, reg->reg & 0xff, &val);
	अगर (ret < 0)
		वापस ret;

	reg->val = val;
	reg->size = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_sensor_set_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	वापस ov5647_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
पूर्ण
#पूर्ण_अगर

/* Subdev core operations registration */
अटल स्थिर काष्ठा v4l2_subdev_core_ops ov5647_subdev_core_ops = अणु
	.subscribe_event	= v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event	= v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर		= ov5647_sensor_get_रेजिस्टर,
	.s_रेजिस्टर		= ov5647_sensor_set_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_rect *
__ov5647_get_pad_crop(काष्ठा ov5647 *ov5647, काष्ठा v4l2_subdev_pad_config *cfg,
		      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&ov5647->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &ov5647->mode->crop;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ov5647_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov5647 *sensor = to_sensor(sd);
	पूर्णांक ret;

	mutex_lock(&sensor->lock);
	अगर (sensor->streaming == enable) अणु
		mutex_unlock(&sensor->lock);
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0)
			जाओ error_unlock;

		ret = ov5647_stream_on(sd);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "stream start failed: %d\n", ret);
			जाओ error_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ov5647_stream_off(sd);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "stream stop failed: %d\n", ret);
			जाओ error_unlock;
		पूर्ण
		pm_runसमय_put(&client->dev);
	पूर्ण

	sensor->streaming = enable;
	mutex_unlock(&sensor->lock);

	वापस 0;

error_unlock:
	pm_runसमय_put(&client->dev);
	mutex_unlock(&sensor->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov5647_subdev_video_ops = अणु
	.s_stream =		ov5647_s_stream,
पूर्ण;

अटल पूर्णांक ov5647_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	स्थिर काष्ठा v4l2_mbus_framefmt *fmt;

	अगर (fse->code != MEDIA_BUS_FMT_SBGGR10_1X10 ||
	    fse->index >= ARRAY_SIZE(ov5647_modes))
		वापस -EINVAL;

	fmt = &ov5647_modes[fse->index].क्रमmat;
	fse->min_width = fmt->width;
	fse->max_width = fmt->width;
	fse->min_height = fmt->height;
	fse->max_height = fmt->height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_get_pad_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	स्थिर काष्ठा v4l2_mbus_framefmt *sensor_क्रमmat;
	काष्ठा ov5647 *sensor = to_sensor(sd);

	mutex_lock(&sensor->lock);
	चयन (क्रमmat->which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		sensor_क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		अवरोध;
	शेष:
		sensor_क्रमmat = &sensor->mode->क्रमmat;
		अवरोध;
	पूर्ण

	*fmt = *sensor_क्रमmat;
	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_set_pad_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा ov5647 *sensor = to_sensor(sd);
	स्थिर काष्ठा ov5647_mode *mode;

	mode = v4l2_find_nearest_size(ov5647_modes, ARRAY_SIZE(ov5647_modes),
				      क्रमmat.width, क्रमmat.height,
				      fmt->width, fmt->height);

	/* Update the sensor mode and apply at it at streamon समय. */
	mutex_lock(&sensor->lock);
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad) = mode->क्रमmat;
	पूर्ण अन्यथा अणु
		पूर्णांक exposure_max, exposure_def;
		पूर्णांक hblank, vblank;

		sensor->mode = mode;
		__v4l2_ctrl_modअगरy_range(sensor->pixel_rate, mode->pixel_rate,
					 mode->pixel_rate, 1, mode->pixel_rate);

		hblank = mode->hts - mode->क्रमmat.width;
		__v4l2_ctrl_modअगरy_range(sensor->hblank, hblank, hblank, 1,
					 hblank);

		vblank = mode->vts - mode->क्रमmat.height;
		__v4l2_ctrl_modअगरy_range(sensor->vblank, OV5647_VBLANK_MIN,
					 OV5647_VTS_MAX - mode->क्रमmat.height,
					 1, vblank);
		__v4l2_ctrl_s_ctrl(sensor->vblank, vblank);

		exposure_max = mode->vts - 4;
		exposure_def = min(exposure_max, OV5647_EXPOSURE_DEFAULT);
		__v4l2_ctrl_modअगरy_range(sensor->exposure,
					 sensor->exposure->minimum,
					 exposure_max, sensor->exposure->step,
					 exposure_def);
	पूर्ण
	*fmt = mode->क्रमmat;
	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ov5647_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP: अणु
		काष्ठा ov5647 *sensor = to_sensor(sd);

		mutex_lock(&sensor->lock);
		sel->r = *__ov5647_get_pad_crop(sensor, cfg, sel->pad,
						sel->which);
		mutex_unlock(&sensor->lock);

		वापस 0;
	पूर्ण

	हाल V4L2_SEL_TGT_NATIVE_SIZE:
		sel->r.top = 0;
		sel->r.left = 0;
		sel->r.width = OV5647_NATIVE_WIDTH;
		sel->r.height = OV5647_NATIVE_HEIGHT;

		वापस 0;

	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.top = OV5647_PIXEL_ARRAY_TOP;
		sel->r.left = OV5647_PIXEL_ARRAY_LEFT;
		sel->r.width = OV5647_PIXEL_ARRAY_WIDTH;
		sel->r.height = OV5647_PIXEL_ARRAY_HEIGHT;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov5647_subdev_pad_ops = अणु
	.क्रमागत_mbus_code		= ov5647_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= ov5647_क्रमागत_frame_size,
	.set_fmt		= ov5647_set_pad_fmt,
	.get_fmt		= ov5647_get_pad_fmt,
	.get_selection		= ov5647_get_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov5647_subdev_ops = अणु
	.core		= &ov5647_subdev_core_ops,
	.video		= &ov5647_subdev_video_ops,
	.pad		= &ov5647_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ov5647_detect(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 पढ़ो;
	पूर्णांक ret;

	ret = ov5647_ग_लिखो(sd, OV5647_SW_RESET, 0x01);
	अगर (ret < 0)
		वापस ret;

	ret = ov5647_पढ़ो(sd, OV5647_REG_CHIPID_H, &पढ़ो);
	अगर (ret < 0)
		वापस ret;

	अगर (पढ़ो != 0x56) अणु
		dev_err(&client->dev, "ID High expected 0x56 got %x", पढ़ो);
		वापस -ENODEV;
	पूर्ण

	ret = ov5647_पढ़ो(sd, OV5647_REG_CHIPID_L, &पढ़ो);
	अगर (ret < 0)
		वापस ret;

	अगर (पढ़ो != 0x47) अणु
		dev_err(&client->dev, "ID Low expected 0x47 got %x", पढ़ो);
		वापस -ENODEV;
	पूर्ण

	वापस ov5647_ग_लिखो(sd, OV5647_SW_RESET, 0x00);
पूर्ण

अटल पूर्णांक ov5647_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat =
				v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);
	काष्ठा v4l2_rect *crop = v4l2_subdev_get_try_crop(sd, fh->pad, 0);

	crop->left = OV5647_PIXEL_ARRAY_LEFT;
	crop->top = OV5647_PIXEL_ARRAY_TOP;
	crop->width = OV5647_PIXEL_ARRAY_WIDTH;
	crop->height = OV5647_PIXEL_ARRAY_HEIGHT;

	*क्रमmat = OV5647_DEFAULT_FORMAT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov5647_subdev_पूर्णांकernal_ops = अणु
	.खोलो = ov5647_खोलो,
पूर्ण;

अटल पूर्णांक ov5647_s_स्वतः_white_balance(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	वापस ov5647_ग_लिखो(sd, OV5647_REG_AWB, val ? 1 : 0);
पूर्ण

अटल पूर्णांक ov5647_s_स्वतःgain(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	पूर्णांक ret;
	u8 reg;

	/* Non-zero turns on AGC by clearing bit 1.*/
	ret = ov5647_पढ़ो(sd, OV5647_REG_AEC_AGC, &reg);
	अगर (ret)
		वापस ret;

	वापस ov5647_ग_लिखो(sd, OV5647_REG_AEC_AGC, val ? reg & ~BIT(1)
							: reg | BIT(1));
पूर्ण

अटल पूर्णांक ov5647_s_exposure_स्वतः(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	पूर्णांक ret;
	u8 reg;

	/*
	 * Everything except V4L2_EXPOSURE_MANUAL turns on AEC by
	 * clearing bit 0.
	 */
	ret = ov5647_पढ़ो(sd, OV5647_REG_AEC_AGC, &reg);
	अगर (ret)
		वापस ret;

	वापस ov5647_ग_लिखो(sd, OV5647_REG_AEC_AGC,
			    val == V4L2_EXPOSURE_MANUAL ? reg | BIT(0)
							: reg & ~BIT(0));
पूर्ण

अटल पूर्णांक ov5647_s_analogue_gain(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	पूर्णांक ret;

	/* 10 bits of gain, 2 in the high रेजिस्टर. */
	ret = ov5647_ग_लिखो(sd, OV5647_REG_GAIN_HI, (val >> 8) & 3);
	अगर (ret)
		वापस ret;

	वापस ov5647_ग_लिखो(sd, OV5647_REG_GAIN_LO, val & 0xff);
पूर्ण

अटल पूर्णांक ov5647_s_exposure(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	पूर्णांक ret;

	/*
	 * Sensor has 20 bits, but the bottom 4 bits are fractions of a line
	 * which we leave as zero (and करोn't receive in "val").
	 */
	ret = ov5647_ग_लिखो(sd, OV5647_REG_EXP_HI, (val >> 12) & 0xf);
	अगर (ret)
		वापस ret;

	ret = ov5647_ग_लिखो(sd, OV5647_REG_EXP_MID, (val >> 4) & 0xff);
	अगर (ret)
		वापस ret;

	वापस ov5647_ग_लिखो(sd, OV5647_REG_EXP_LO, (val & 0xf) << 4);
पूर्ण

अटल पूर्णांक ov5647_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov5647 *sensor = container_of(ctrl->handler,
					    काष्ठा ov5647, ctrls);
	काष्ठा v4l2_subdev *sd = &sensor->sd;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;


	/* v4l2_ctrl_lock() locks our own mutex */

	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		पूर्णांक exposure_max, exposure_def;

		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = sensor->mode->क्रमmat.height + ctrl->val - 4;
		exposure_def = min(exposure_max, OV5647_EXPOSURE_DEFAULT);
		__v4l2_ctrl_modअगरy_range(sensor->exposure,
					 sensor->exposure->minimum,
					 exposure_max, sensor->exposure->step,
					 exposure_def);
	पूर्ण

	/*
	 * If the device is not घातered up करो not apply any controls
	 * to H/W at this समय. Instead the controls will be restored
	 * at s_stream(1) समय.
	 */
	अगर (pm_runसमय_get_अगर_in_use(&client->dev) == 0)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov5647_s_स्वतः_white_balance(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		ret = ov5647_s_स्वतःgain(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov5647_s_exposure_स्वतः(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret =  ov5647_s_analogue_gain(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		ret = ov5647_s_exposure(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		ret = ov5647_ग_लिखो16(sd, OV5647_REG_VTS_HI,
				     sensor->mode->क्रमmat.height + ctrl->val);
		अवरोध;

	/* Read-only, but we adjust it based on mode. */
	हाल V4L2_CID_PIXEL_RATE:
	हाल V4L2_CID_HBLANK:
		/* Read-only, but we adjust it based on mode. */
		अवरोध;

	शेष:
		dev_info(&client->dev,
			 "Control (id:0x%x, val:0x%x) not supported\n",
			 ctrl->id, ctrl->val);
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov5647_ctrl_ops = अणु
	.s_ctrl = ov5647_s_ctrl,
पूर्ण;

अटल पूर्णांक ov5647_init_controls(काष्ठा ov5647 *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->sd);
	पूर्णांक hblank, exposure_max, exposure_def;

	v4l2_ctrl_handler_init(&sensor->ctrls, 8);

	v4l2_ctrl_new_std(&sensor->ctrls, &ov5647_ctrl_ops,
			  V4L2_CID_AUTOGAIN, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&sensor->ctrls, &ov5647_ctrl_ops,
			  V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 0);

	v4l2_ctrl_new_std_menu(&sensor->ctrls, &ov5647_ctrl_ops,
			       V4L2_CID_EXPOSURE_AUTO, V4L2_EXPOSURE_MANUAL,
			       0, V4L2_EXPOSURE_MANUAL);

	exposure_max = sensor->mode->vts - 4;
	exposure_def = min(exposure_max, OV5647_EXPOSURE_DEFAULT);
	sensor->exposure = v4l2_ctrl_new_std(&sensor->ctrls, &ov5647_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     OV5647_EXPOSURE_MIN,
					     exposure_max, OV5647_EXPOSURE_STEP,
					     exposure_def);

	/* min: 16 = 1.0x; max (10 bits); शेष: 32 = 2.0x. */
	v4l2_ctrl_new_std(&sensor->ctrls, &ov5647_ctrl_ops,
			  V4L2_CID_ANALOGUE_GAIN, 16, 1023, 1, 32);

	/* By शेष, PIXEL_RATE is पढ़ो only, but it करोes change per mode */
	sensor->pixel_rate = v4l2_ctrl_new_std(&sensor->ctrls, &ov5647_ctrl_ops,
					       V4L2_CID_PIXEL_RATE,
					       sensor->mode->pixel_rate,
					       sensor->mode->pixel_rate, 1,
					       sensor->mode->pixel_rate);

	/* By शेष, HBLANK is पढ़ो only, but it करोes change per mode. */
	hblank = sensor->mode->hts - sensor->mode->क्रमmat.width;
	sensor->hblank = v4l2_ctrl_new_std(&sensor->ctrls, &ov5647_ctrl_ops,
					   V4L2_CID_HBLANK, hblank, hblank, 1,
					   hblank);

	sensor->vblank = v4l2_ctrl_new_std(&sensor->ctrls, &ov5647_ctrl_ops,
					   V4L2_CID_VBLANK, OV5647_VBLANK_MIN,
					   OV5647_VTS_MAX -
					   sensor->mode->क्रमmat.height, 1,
					   sensor->mode->vts -
					   sensor->mode->क्रमmat.height);

	अगर (sensor->ctrls.error)
		जाओ handler_मुक्त;

	sensor->pixel_rate->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	sensor->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;
	sensor->sd.ctrl_handler = &sensor->ctrls;

	वापस 0;

handler_मुक्त:
	dev_err(&client->dev, "%s Controls initialization failed (%d)\n",
		__func__, sensor->ctrls.error);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls);

	वापस sensor->ctrls.error;
पूर्ण

अटल पूर्णांक ov5647_parse_dt(काष्ठा ov5647 *sensor, काष्ठा device_node *np)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY,
	पूर्ण;
	काष्ठा device_node *ep;
	पूर्णांक ret;

	ep = of_graph_get_next_endpoपूर्णांक(np, शून्य);
	अगर (!ep)
		वापस -EINVAL;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep), &bus_cfg);
	अगर (ret)
		जाओ out;

	sensor->घड़ी_ncont = bus_cfg.bus.mipi_csi2.flags &
			      V4L2_MBUS_CSI2_NONCONTINUOUS_CLOCK;

out:
	of_node_put(ep);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5647_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा device *dev = &client->dev;
	काष्ठा ov5647 *sensor;
	काष्ठा v4l2_subdev *sd;
	u32 xclk_freq;
	पूर्णांक ret;

	sensor = devm_kzalloc(dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	अगर (IS_ENABLED(CONFIG_OF) && np) अणु
		ret = ov5647_parse_dt(sensor, np);
		अगर (ret) अणु
			dev_err(dev, "DT parsing error: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	sensor->xclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(sensor->xclk)) अणु
		dev_err(dev, "could not get xclk");
		वापस PTR_ERR(sensor->xclk);
	पूर्ण

	xclk_freq = clk_get_rate(sensor->xclk);
	अगर (xclk_freq != 25000000) अणु
		dev_err(dev, "Unsupported clock frequency: %u\n", xclk_freq);
		वापस -EINVAL;
	पूर्ण

	/* Request the घातer करोwn GPIO निश्चितed. */
	sensor->pwdn = devm_gpiod_get_optional(dev, "pwdn", GPIOD_OUT_HIGH);
	अगर (IS_ERR(sensor->pwdn)) अणु
		dev_err(dev, "Failed to get 'pwdn' gpio\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&sensor->lock);

	sensor->mode = OV5647_DEFAULT_MODE;

	ret = ov5647_init_controls(sensor);
	अगर (ret)
		जाओ mutex_destroy;

	sd = &sensor->sd;
	v4l2_i2c_subdev_init(sd, client, &ov5647_subdev_ops);
	sd->पूर्णांकernal_ops = &ov5647_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;

	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &sensor->pad);
	अगर (ret < 0)
		जाओ ctrl_handler_मुक्त;

	ret = ov5647_घातer_on(dev);
	अगर (ret)
		जाओ entity_cleanup;

	ret = ov5647_detect(sd);
	अगर (ret < 0)
		जाओ घातer_off;

	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret < 0)
		जाओ घातer_off;

	/* Enable runसमय PM and turn off the device */
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	dev_dbg(dev, "OmniVision OV5647 camera driver probed\n");

	वापस 0;

घातer_off:
	ov5647_घातer_off(dev);
entity_cleanup:
	media_entity_cleanup(&sd->entity);
ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls);
mutex_destroy:
	mutex_destroy(&sensor->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov5647_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov5647 *sensor = to_sensor(sd);

	v4l2_async_unरेजिस्टर_subdev(&sensor->sd);
	media_entity_cleanup(&sensor->sd.entity);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls);
	v4l2_device_unरेजिस्टर_subdev(sd);
	pm_runसमय_disable(&client->dev);
	mutex_destroy(&sensor->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov5647_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ov5647_घातer_off, ov5647_घातer_on, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ov5647_id[] = अणु
	अणु "ov5647", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov5647_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ov5647_of_match[] = अणु
	अणु .compatible = "ovti,ov5647" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov5647_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov5647_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(ov5647_of_match),
		.name	= "ov5647",
		.pm	= &ov5647_pm_ops,
	पूर्ण,
	.probe_new	= ov5647_probe,
	.हटाओ		= ov5647_हटाओ,
	.id_table	= ov5647_id,
पूर्ण;

module_i2c_driver(ov5647_driver);

MODULE_AUTHOR("Ramiro Oliveira <roliveir@synopsys.com>");
MODULE_DESCRIPTION("A low-level driver for OmniVision ov5647 sensors");
MODULE_LICENSE("GPL v2");
