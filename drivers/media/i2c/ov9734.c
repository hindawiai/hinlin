<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Intel Corporation.

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#घोषणा OV9734_LINK_FREQ_180MHZ		180000000ULL
#घोषणा OV9734_SCLK			36000000LL
#घोषणा OV9734_MCLK			19200000
/* ov9734 only support 1-lane mipi output */
#घोषणा OV9734_DATA_LANES		1
#घोषणा OV9734_RGB_DEPTH		10

#घोषणा OV9734_REG_CHIP_ID		0x300a
#घोषणा OV9734_CHIP_ID			0x9734

#घोषणा OV9734_REG_MODE_SELECT		0x0100
#घोषणा OV9734_MODE_STANDBY		0x00
#घोषणा OV9734_MODE_STREAMING		0x01

/* vertical-timings from sensor */
#घोषणा OV9734_REG_VTS			0x380e
#घोषणा OV9734_VTS_30FPS		0x0322
#घोषणा OV9734_VTS_30FPS_MIN		0x0322
#घोषणा OV9734_VTS_MAX			0x7fff

/* horizontal-timings from sensor */
#घोषणा OV9734_REG_HTS			0x380c

/* Exposure controls from sensor */
#घोषणा OV9734_REG_EXPOSURE		0x3500
#घोषणा OV9734_EXPOSURE_MIN		4
#घोषणा OV9734_EXPOSURE_MAX_MARGIN	4
#घोषणा	OV9734_EXPOSURE_STEP		1

/* Analog gain controls from sensor */
#घोषणा OV9734_REG_ANALOG_GAIN		0x350a
#घोषणा OV9734_ANAL_GAIN_MIN		16
#घोषणा OV9734_ANAL_GAIN_MAX		248
#घोषणा OV9734_ANAL_GAIN_STEP		1

/* Digital gain controls from sensor */
#घोषणा OV9734_REG_MWB_R_GAIN		0x5180
#घोषणा OV9734_REG_MWB_G_GAIN		0x5182
#घोषणा OV9734_REG_MWB_B_GAIN		0x5184
#घोषणा OV9734_DGTL_GAIN_MIN		256
#घोषणा OV9734_DGTL_GAIN_MAX		1023
#घोषणा OV9734_DGTL_GAIN_STEP		1
#घोषणा OV9734_DGTL_GAIN_DEFAULT	256

/* Test Pattern Control */
#घोषणा OV9734_REG_TEST_PATTERN		0x5080
#घोषणा OV9734_TEST_PATTERN_ENABLE	BIT(7)
#घोषणा OV9734_TEST_PATTERN_BAR_SHIFT	2

क्रमागत अणु
	OV9734_LINK_FREQ_180MHZ_INDEX,
पूर्ण;

काष्ठा ov9734_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा ov9734_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा ov9734_reg *regs;
पूर्ण;

काष्ठा ov9734_link_freq_config अणु
	स्थिर काष्ठा ov9734_reg_list reg_list;
पूर्ण;

काष्ठा ov9734_mode अणु
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
	स्थिर काष्ठा ov9734_reg_list reg_list;
पूर्ण;

अटल स्थिर काष्ठा ov9734_reg mipi_data_rate_360mbps[] = अणु
	अणु0x3030, 0x19पूर्ण,
	अणु0x3080, 0x02पूर्ण,
	अणु0x3081, 0x4bपूर्ण,
	अणु0x3082, 0x04पूर्ण,
	अणु0x3083, 0x00पूर्ण,
	अणु0x3084, 0x02पूर्ण,
	अणु0x3085, 0x01पूर्ण,
	अणु0x3086, 0x01पूर्ण,
	अणु0x3089, 0x01पूर्ण,
	अणु0x308a, 0x00पूर्ण,
	अणु0x301e, 0x15पूर्ण,
	अणु0x3103, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9734_reg mode_1296x734_regs[] = अणु
	अणु0x3001, 0x00पूर्ण,
	अणु0x3002, 0x00पूर्ण,
	अणु0x3007, 0x00पूर्ण,
	अणु0x3010, 0x00पूर्ण,
	अणु0x3011, 0x08पूर्ण,
	अणु0x3014, 0x22पूर्ण,
	अणु0x3600, 0x55पूर्ण,
	अणु0x3601, 0x02पूर्ण,
	अणु0x3605, 0x22पूर्ण,
	अणु0x3611, 0xe7पूर्ण,
	अणु0x3654, 0x10पूर्ण,
	अणु0x3655, 0x77पूर्ण,
	अणु0x3656, 0x77पूर्ण,
	अणु0x3657, 0x07पूर्ण,
	अणु0x3658, 0x22पूर्ण,
	अणु0x3659, 0x22पूर्ण,
	अणु0x365a, 0x02पूर्ण,
	अणु0x3784, 0x05पूर्ण,
	अणु0x3785, 0x55पूर्ण,
	अणु0x37c0, 0x07पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x04पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x04पूर्ण,
	अणु0x3804, 0x05पूर्ण,
	अणु0x3805, 0x0bपूर्ण,
	अणु0x3806, 0x02पूर्ण,
	अणु0x3807, 0xdbपूर्ण,
	अणु0x3808, 0x05पूर्ण,
	अणु0x3809, 0x00पूर्ण,
	अणु0x380a, 0x02पूर्ण,
	अणु0x380b, 0xd0पूर्ण,
	अणु0x380c, 0x05पूर्ण,
	अणु0x380d, 0xc6पूर्ण,
	अणु0x380e, 0x03पूर्ण,
	अणु0x380f, 0x22पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x04पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x04पूर्ण,
	अणु0x3816, 0x00पूर्ण,
	अणु0x3817, 0x00पूर्ण,
	अणु0x3818, 0x00पूर्ण,
	अणु0x3819, 0x04पूर्ण,
	अणु0x3820, 0x18पूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x382c, 0x06पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x31पूर्ण,
	अणु0x3502, 0x00पूर्ण,
	अणु0x3503, 0x03पूर्ण,
	अणु0x3504, 0x00पूर्ण,
	अणु0x3505, 0x00पूर्ण,
	अणु0x3509, 0x10पूर्ण,
	अणु0x350a, 0x00पूर्ण,
	अणु0x350b, 0x40पूर्ण,
	अणु0x3d00, 0x00पूर्ण,
	अणु0x3d01, 0x00पूर्ण,
	अणु0x3d02, 0x00पूर्ण,
	अणु0x3d03, 0x00पूर्ण,
	अणु0x3d04, 0x00पूर्ण,
	अणु0x3d05, 0x00पूर्ण,
	अणु0x3d06, 0x00पूर्ण,
	अणु0x3d07, 0x00पूर्ण,
	अणु0x3d08, 0x00पूर्ण,
	अणु0x3d09, 0x00पूर्ण,
	अणु0x3d0a, 0x00पूर्ण,
	अणु0x3d0b, 0x00पूर्ण,
	अणु0x3d0c, 0x00पूर्ण,
	अणु0x3d0d, 0x00पूर्ण,
	अणु0x3d0e, 0x00पूर्ण,
	अणु0x3d0f, 0x00पूर्ण,
	अणु0x3d80, 0x00पूर्ण,
	अणु0x3d81, 0x00पूर्ण,
	अणु0x3d82, 0x38पूर्ण,
	अणु0x3d83, 0xa4पूर्ण,
	अणु0x3d84, 0x00पूर्ण,
	अणु0x3d85, 0x00पूर्ण,
	अणु0x3d86, 0x1fपूर्ण,
	अणु0x3d87, 0x03पूर्ण,
	अणु0x3d8b, 0x00पूर्ण,
	अणु0x3d8f, 0x00पूर्ण,
	अणु0x4001, 0xe0पूर्ण,
	अणु0x4009, 0x0bपूर्ण,
	अणु0x4300, 0x03पूर्ण,
	अणु0x4301, 0xffपूर्ण,
	अणु0x4304, 0x00पूर्ण,
	अणु0x4305, 0x00पूर्ण,
	अणु0x4309, 0x00पूर्ण,
	अणु0x4600, 0x00पूर्ण,
	अणु0x4601, 0x80पूर्ण,
	अणु0x4800, 0x00पूर्ण,
	अणु0x4805, 0x00पूर्ण,
	अणु0x4821, 0x50पूर्ण,
	अणु0x4823, 0x50पूर्ण,
	अणु0x4837, 0x2dपूर्ण,
	अणु0x4a00, 0x00पूर्ण,
	अणु0x4f00, 0x80पूर्ण,
	अणु0x4f01, 0x10पूर्ण,
	अणु0x4f02, 0x00पूर्ण,
	अणु0x4f03, 0x00पूर्ण,
	अणु0x4f04, 0x00पूर्ण,
	अणु0x4f05, 0x00पूर्ण,
	अणु0x4f06, 0x00पूर्ण,
	अणु0x4f07, 0x00पूर्ण,
	अणु0x4f08, 0x00पूर्ण,
	अणु0x4f09, 0x00पूर्ण,
	अणु0x5000, 0x2fपूर्ण,
	अणु0x500c, 0x00पूर्ण,
	अणु0x500d, 0x00पूर्ण,
	अणु0x500e, 0x00पूर्ण,
	अणु0x500f, 0x00पूर्ण,
	अणु0x5010, 0x00पूर्ण,
	अणु0x5011, 0x00पूर्ण,
	अणु0x5012, 0x00पूर्ण,
	अणु0x5013, 0x00पूर्ण,
	अणु0x5014, 0x00पूर्ण,
	अणु0x5015, 0x00पूर्ण,
	अणु0x5016, 0x00पूर्ण,
	अणु0x5017, 0x00पूर्ण,
	अणु0x5080, 0x00पूर्ण,
	अणु0x5180, 0x01पूर्ण,
	अणु0x5181, 0x00पूर्ण,
	अणु0x5182, 0x01पूर्ण,
	अणु0x5183, 0x00पूर्ण,
	अणु0x5184, 0x01पूर्ण,
	अणु0x5185, 0x00पूर्ण,
	अणु0x5708, 0x06पूर्ण,
	अणु0x380f, 0x2aपूर्ण,
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
	अणु0x5791, 0x04पूर्ण,
	अणु0x5792, 0x00पूर्ण,
	अणु0x5793, 0x52पूर्ण,
	अणु0x5794, 0xa3पूर्ण,
	अणु0x5000, 0x3fपूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3805, 0x0fपूर्ण,
	अणु0x3807, 0xdfपूर्ण,
	अणु0x3809, 0x10पूर्ण,
	अणु0x380b, 0xdeपूर्ण,
	अणु0x3811, 0x00पूर्ण,
	अणु0x3813, 0x01पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov9734_test_pattern_menu[] = अणु
	"Disabled",
	"Standard Color Bar",
	"Top-Bottom Darker Color Bar",
	"Right-Left Darker Color Bar",
	"Bottom-Top Darker Color Bar",
पूर्ण;

अटल स्थिर s64 link_freq_menu_items[] = अणु
	OV9734_LINK_FREQ_180MHZ,
पूर्ण;

अटल स्थिर काष्ठा ov9734_link_freq_config link_freq_configs[] = अणु
	[OV9734_LINK_FREQ_180MHZ_INDEX] = अणु
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_360mbps),
			.regs = mipi_data_rate_360mbps,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9734_mode supported_modes[] = अणु
	अणु
		.width = 1296,
		.height = 734,
		.hts = 0x5c6,
		.vts_def = OV9734_VTS_30FPS,
		.vts_min = OV9734_VTS_30FPS_MIN,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1296x734_regs),
			.regs = mode_1296x734_regs,
		पूर्ण,
		.link_freq_index = OV9734_LINK_FREQ_180MHZ_INDEX,
	पूर्ण,
पूर्ण;

काष्ठा ov9734 अणु
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
	स्थिर काष्ठा ov9734_mode *cur_mode;

	/* To serialize asynchronus callbacks */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;
पूर्ण;

अटल अंतरभूत काष्ठा ov9734 *to_ov9734(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा ov9734, sd);
पूर्ण

अटल u64 to_pixel_rate(u32 f_index)
अणु
	u64 pixel_rate = link_freq_menu_items[f_index] * 2 * OV9734_DATA_LANES;

	करो_भाग(pixel_rate, OV9734_RGB_DEPTH);

	वापस pixel_rate;
पूर्ण

अटल u64 to_pixels_per_line(u32 hts, u32 f_index)
अणु
	u64 ppl = hts * to_pixel_rate(f_index);

	करो_भाग(ppl, OV9734_SCLK);

	वापस ppl;
पूर्ण

अटल पूर्णांक ov9734_पढ़ो_reg(काष्ठा ov9734 *ov9734, u16 reg, u16 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov9734->sd);
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2];
	u8 data_buf[4] = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (len > माप(data_buf))
		वापस -EINVAL;

	put_unaligned_be16(reg, addr_buf);
	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = माप(addr_buf);
	msgs[0].buf = addr_buf;
	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = &data_buf[माप(data_buf) - len];

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs))
		वापस ret < 0 ? ret : -EIO;

	*val = get_unaligned_be32(data_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_ग_लिखो_reg(काष्ठा ov9734 *ov9734, u16 reg, u16 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov9734->sd);
	u8 buf[6];
	पूर्णांक ret = 0;

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);
	put_unaligned_be32(val << 8 * (4 - len), buf + 2);

	ret = i2c_master_send(client, buf, len + 2);
	अगर (ret != len + 2)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_ग_लिखो_reg_list(काष्ठा ov9734 *ov9734,
				 स्थिर काष्ठा ov9734_reg_list *r_list)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov9734->sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < r_list->num_of_regs; i++) अणु
		ret = ov9734_ग_लिखो_reg(ov9734, r_list->regs[i].address, 1,
				       r_list->regs[i].val);
		अगर (ret) अणु
			dev_err_ratelimited(&client->dev,
					    "write reg 0x%4.4x return err = %d",
					    r_list->regs[i].address, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_update_digital_gain(काष्ठा ov9734 *ov9734, u32 d_gain)
अणु
	पूर्णांक ret;

	ret = ov9734_ग_लिखो_reg(ov9734, OV9734_REG_MWB_R_GAIN, 2, d_gain);
	अगर (ret)
		वापस ret;

	ret = ov9734_ग_लिखो_reg(ov9734, OV9734_REG_MWB_G_GAIN, 2, d_gain);
	अगर (ret)
		वापस ret;

	वापस ov9734_ग_लिखो_reg(ov9734, OV9734_REG_MWB_B_GAIN, 2, d_gain);
पूर्ण

अटल पूर्णांक ov9734_test_pattern(काष्ठा ov9734 *ov9734, u32 pattern)
अणु
	अगर (pattern)
		pattern = (pattern - 1) << OV9734_TEST_PATTERN_BAR_SHIFT |
			OV9734_TEST_PATTERN_ENABLE;

	वापस ov9734_ग_लिखो_reg(ov9734, OV9734_REG_TEST_PATTERN, 1, pattern);
पूर्ण

अटल पूर्णांक ov9734_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov9734 *ov9734 = container_of(ctrl->handler,
					     काष्ठा ov9734, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov9734->sd);
	s64 exposure_max;
	पूर्णांक ret = 0;

	/* Propagate change of current control to all related controls */
	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = ov9734->cur_mode->height + ctrl->val -
			OV9734_EXPOSURE_MAX_MARGIN;
		__v4l2_ctrl_modअगरy_range(ov9734->exposure,
					 ov9734->exposure->minimum,
					 exposure_max, ov9734->exposure->step,
					 exposure_max);
	पूर्ण

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov9734_ग_लिखो_reg(ov9734, OV9734_REG_ANALOG_GAIN,
				       2, ctrl->val);
		अवरोध;

	हाल V4L2_CID_DIGITAL_GAIN:
		ret = ov9734_update_digital_gain(ov9734, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE:
		/* 4 least signअगरicant bits of expsoure are fractional part */
		ret = ov9734_ग_लिखो_reg(ov9734, OV9734_REG_EXPOSURE,
				       3, ctrl->val << 4);
		अवरोध;

	हाल V4L2_CID_VBLANK:
		ret = ov9734_ग_लिखो_reg(ov9734, OV9734_REG_VTS, 2,
				       ov9734->cur_mode->height + ctrl->val);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		ret = ov9734_test_pattern(ov9734, ctrl->val);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov9734_ctrl_ops = अणु
	.s_ctrl = ov9734_set_ctrl,
पूर्ण;

अटल पूर्णांक ov9734_init_controls(काष्ठा ov9734 *ov9734)
अणु
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	स्थिर काष्ठा ov9734_mode *cur_mode;
	s64 exposure_max, h_blank, pixel_rate;
	u32 vblank_min, vblank_max, vblank_शेष;
	पूर्णांक ret, size;

	ctrl_hdlr = &ov9734->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 8);
	अगर (ret)
		वापस ret;

	ctrl_hdlr->lock = &ov9734->mutex;
	cur_mode = ov9734->cur_mode;
	size = ARRAY_SIZE(link_freq_menu_items);
	ov9734->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr, &ov9734_ctrl_ops,
						   V4L2_CID_LINK_FREQ,
						   size - 1, 0,
						   link_freq_menu_items);
	अगर (ov9734->link_freq)
		ov9734->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	pixel_rate = to_pixel_rate(OV9734_LINK_FREQ_180MHZ_INDEX);
	ov9734->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &ov9734_ctrl_ops,
					       V4L2_CID_PIXEL_RATE, 0,
					       pixel_rate, 1, pixel_rate);
	vblank_min = cur_mode->vts_min - cur_mode->height;
	vblank_max = OV9734_VTS_MAX - cur_mode->height;
	vblank_शेष = cur_mode->vts_def - cur_mode->height;
	ov9734->vblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov9734_ctrl_ops,
					   V4L2_CID_VBLANK, vblank_min,
					   vblank_max, 1, vblank_शेष);
	h_blank = to_pixels_per_line(cur_mode->hts, cur_mode->link_freq_index);
	h_blank -= cur_mode->width;
	ov9734->hblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov9734_ctrl_ops,
					   V4L2_CID_HBLANK, h_blank, h_blank, 1,
					   h_blank);
	अगर (ov9734->hblank)
		ov9734->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	v4l2_ctrl_new_std(ctrl_hdlr, &ov9734_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  OV9734_ANAL_GAIN_MIN, OV9734_ANAL_GAIN_MAX,
			  OV9734_ANAL_GAIN_STEP, OV9734_ANAL_GAIN_MIN);
	v4l2_ctrl_new_std(ctrl_hdlr, &ov9734_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  OV9734_DGTL_GAIN_MIN, OV9734_DGTL_GAIN_MAX,
			  OV9734_DGTL_GAIN_STEP, OV9734_DGTL_GAIN_DEFAULT);
	exposure_max = ov9734->cur_mode->vts_def - OV9734_EXPOSURE_MAX_MARGIN;
	ov9734->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &ov9734_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     OV9734_EXPOSURE_MIN, exposure_max,
					     OV9734_EXPOSURE_STEP,
					     exposure_max);
	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &ov9734_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov9734_test_pattern_menu) - 1,
				     0, 0, ov9734_test_pattern_menu);
	अगर (ctrl_hdlr->error)
		वापस ctrl_hdlr->error;

	ov9734->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;
पूर्ण

अटल व्योम ov9734_update_pad_क्रमmat(स्थिर काष्ठा ov9734_mode *mode,
				     काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov9734_start_streaming(काष्ठा ov9734 *ov9734)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov9734->sd);
	स्थिर काष्ठा ov9734_reg_list *reg_list;
	पूर्णांक link_freq_index, ret;

	link_freq_index = ov9734->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = ov9734_ग_लिखो_reg_list(ov9734, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set plls");
		वापस ret;
	पूर्ण

	reg_list = &ov9734->cur_mode->reg_list;
	ret = ov9734_ग_लिखो_reg_list(ov9734, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set mode");
		वापस ret;
	पूर्ण

	ret = __v4l2_ctrl_handler_setup(ov9734->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	ret = ov9734_ग_लिखो_reg(ov9734, OV9734_REG_MODE_SELECT,
			       1, OV9734_MODE_STREAMING);
	अगर (ret)
		dev_err(&client->dev, "failed to start stream");

	वापस ret;
पूर्ण

अटल व्योम ov9734_stop_streaming(काष्ठा ov9734 *ov9734)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov9734->sd);

	अगर (ov9734_ग_लिखो_reg(ov9734, OV9734_REG_MODE_SELECT,
			     1, OV9734_MODE_STANDBY))
		dev_err(&client->dev, "failed to stop stream");
पूर्ण

अटल पूर्णांक ov9734_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov9734 *ov9734 = to_ov9734(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov9734->mutex);
	अगर (ov9734->streaming == enable) अणु
		mutex_unlock(&ov9734->mutex);
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			mutex_unlock(&ov9734->mutex);
			वापस ret;
		पूर्ण

		ret = ov9734_start_streaming(ov9734);
		अगर (ret) अणु
			enable = 0;
			ov9734_stop_streaming(ov9734);
			pm_runसमय_put(&client->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		ov9734_stop_streaming(ov9734);
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov9734->streaming = enable;
	mutex_unlock(&ov9734->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ov9734_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov9734 *ov9734 = to_ov9734(sd);

	mutex_lock(&ov9734->mutex);
	अगर (ov9734->streaming)
		ov9734_stop_streaming(ov9734);

	mutex_unlock(&ov9734->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov9734_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov9734 *ov9734 = to_ov9734(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov9734->mutex);
	अगर (!ov9734->streaming)
		जाओ निकास;

	ret = ov9734_start_streaming(ov9734);
	अगर (ret) अणु
		ov9734->streaming = false;
		ov9734_stop_streaming(ov9734);
	पूर्ण

निकास:
	mutex_unlock(&ov9734->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ov9734_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov9734 *ov9734 = to_ov9734(sd);
	स्थिर काष्ठा ov9734_mode *mode;
	s32 vblank_def, h_blank;

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes), width,
				      height, fmt->क्रमmat.width,
				      fmt->क्रमmat.height);

	mutex_lock(&ov9734->mutex);
	ov9734_update_pad_क्रमmat(mode, &fmt->क्रमmat);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		ov9734->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(ov9734->link_freq, mode->link_freq_index);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(ov9734->pixel_rate,
					 to_pixel_rate(mode->link_freq_index));

		/* Update limits and set FPS to शेष */
		vblank_def = mode->vts_def - mode->height;
		__v4l2_ctrl_modअगरy_range(ov9734->vblank,
					 mode->vts_min - mode->height,
					 OV9734_VTS_MAX - mode->height, 1,
					 vblank_def);
		__v4l2_ctrl_s_ctrl(ov9734->vblank, vblank_def);
		h_blank = to_pixels_per_line(mode->hts, mode->link_freq_index) -
			mode->width;
		__v4l2_ctrl_modअगरy_range(ov9734->hblank, h_blank, h_blank, 1,
					 h_blank);
	पूर्ण

	mutex_unlock(&ov9734->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov9734 *ov9734 = to_ov9734(sd);

	mutex_lock(&ov9734->mutex);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(&ov9734->sd, cfg,
							  fmt->pad);
	अन्यथा
		ov9734_update_pad_क्रमmat(ov9734->cur_mode, &fmt->क्रमmat);

	mutex_unlock(&ov9734->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
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

अटल पूर्णांक ov9734_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov9734 *ov9734 = to_ov9734(sd);

	mutex_lock(&ov9734->mutex);
	ov9734_update_pad_क्रमmat(&supported_modes[0],
				 v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0));
	mutex_unlock(&ov9734->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov9734_video_ops = अणु
	.s_stream = ov9734_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov9734_pad_ops = अणु
	.set_fmt = ov9734_set_क्रमmat,
	.get_fmt = ov9734_get_क्रमmat,
	.क्रमागत_mbus_code = ov9734_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov9734_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov9734_subdev_ops = अणु
	.video = &ov9734_video_ops,
	.pad = &ov9734_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ov9734_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov9734_पूर्णांकernal_ops = अणु
	.खोलो = ov9734_खोलो,
पूर्ण;

अटल पूर्णांक ov9734_identअगरy_module(काष्ठा ov9734 *ov9734)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov9734->sd);
	पूर्णांक ret;
	u32 val;

	ret = ov9734_पढ़ो_reg(ov9734, OV9734_REG_CHIP_ID, 2, &val);
	अगर (ret)
		वापस ret;

	अगर (val != OV9734_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x",
			OV9734_CHIP_ID, val);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_check_hwcfg(काष्ठा device *dev)
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
	अगर (ret)
		वापस ret;

	अगर (mclk != OV9734_MCLK) अणु
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

अटल पूर्णांक ov9734_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov9734 *ov9734 = to_ov9734(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	pm_runसमय_disable(&client->dev);
	mutex_destroy(&ov9734->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov9734_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov9734 *ov9734;
	पूर्णांक ret;

	ret = ov9734_check_hwcfg(&client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to check HW configuration: %d",
			ret);
		वापस ret;
	पूर्ण

	ov9734 = devm_kzalloc(&client->dev, माप(*ov9734), GFP_KERNEL);
	अगर (!ov9734)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&ov9734->sd, client, &ov9734_subdev_ops);
	ret = ov9734_identअगरy_module(ov9734);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		वापस ret;
	पूर्ण

	mutex_init(&ov9734->mutex);
	ov9734->cur_mode = &supported_modes[0];
	ret = ov9734_init_controls(ov9734);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init controls: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ov9734->sd.पूर्णांकernal_ops = &ov9734_पूर्णांकernal_ops;
	ov9734->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov9734->sd.entity.ops = &ov9734_subdev_entity_ops;
	ov9734->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ov9734->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&ov9734->sd.entity, 1, &ov9734->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&ov9734->sd);
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
	media_entity_cleanup(&ov9734->sd.entity);

probe_error_v4l2_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(ov9734->sd.ctrl_handler);
	mutex_destroy(&ov9734->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov9734_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ov9734_suspend, ov9734_resume)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id ov9734_acpi_ids[] = अणु
	अणु "OVTI9734", पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, ov9734_acpi_ids);

अटल काष्ठा i2c_driver ov9734_i2c_driver = अणु
	.driver = अणु
		.name = "ov9734",
		.pm = &ov9734_pm_ops,
		.acpi_match_table = ov9734_acpi_ids,
	पूर्ण,
	.probe_new = ov9734_probe,
	.हटाओ = ov9734_हटाओ,
पूर्ण;

module_i2c_driver(ov9734_i2c_driver);

MODULE_AUTHOR("Qiu, Tianshu <tian.shu.qiu@intel.com>");
MODULE_AUTHOR("Bingbu Cao <bingbu.cao@intel.com>");
MODULE_DESCRIPTION("OmniVision OV9734 sensor driver");
MODULE_LICENSE("GPL v2");
