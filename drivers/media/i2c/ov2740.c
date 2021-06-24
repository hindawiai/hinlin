<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Intel Corporation.

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/regmap.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#घोषणा OV2740_LINK_FREQ_360MHZ		360000000ULL
#घोषणा OV2740_SCLK			72000000LL
#घोषणा OV2740_MCLK			19200000
#घोषणा OV2740_DATA_LANES		2
#घोषणा OV2740_RGB_DEPTH		10

#घोषणा OV2740_REG_CHIP_ID		0x300a
#घोषणा OV2740_CHIP_ID			0x2740

#घोषणा OV2740_REG_MODE_SELECT		0x0100
#घोषणा OV2740_MODE_STANDBY		0x00
#घोषणा OV2740_MODE_STREAMING		0x01

/* vertical-timings from sensor */
#घोषणा OV2740_REG_VTS			0x380e
#घोषणा OV2740_VTS_DEF			0x088a
#घोषणा OV2740_VTS_MIN			0x0460
#घोषणा OV2740_VTS_MAX			0x7fff

/* horizontal-timings from sensor */
#घोषणा OV2740_REG_HTS			0x380c

/* Exposure controls from sensor */
#घोषणा OV2740_REG_EXPOSURE		0x3500
#घोषणा OV2740_EXPOSURE_MIN		4
#घोषणा OV2740_EXPOSURE_MAX_MARGIN	8
#घोषणा OV2740_EXPOSURE_STEP		1

/* Analog gain controls from sensor */
#घोषणा OV2740_REG_ANALOG_GAIN		0x3508
#घोषणा OV2740_ANAL_GAIN_MIN		128
#घोषणा OV2740_ANAL_GAIN_MAX		1983
#घोषणा OV2740_ANAL_GAIN_STEP		1

/* Digital gain controls from sensor */
#घोषणा OV2740_REG_MWB_R_GAIN		0x500a
#घोषणा OV2740_REG_MWB_G_GAIN		0x500c
#घोषणा OV2740_REG_MWB_B_GAIN		0x500e
#घोषणा OV2740_DGTL_GAIN_MIN		0
#घोषणा OV2740_DGTL_GAIN_MAX		4095
#घोषणा OV2740_DGTL_GAIN_STEP		1
#घोषणा OV2740_DGTL_GAIN_DEFAULT	1024

/* Test Pattern Control */
#घोषणा OV2740_REG_TEST_PATTERN		0x5040
#घोषणा OV2740_TEST_PATTERN_ENABLE	BIT(7)
#घोषणा OV2740_TEST_PATTERN_BAR_SHIFT	2

/* ISP CTRL00 */
#घोषणा OV2740_REG_ISP_CTRL00		0x5000
/* ISP CTRL01 */
#घोषणा OV2740_REG_ISP_CTRL01		0x5001
/* Customer Addresses: 0x7010 - 0x710F */
#घोषणा CUSTOMER_USE_OTP_SIZE		0x100
/* OTP रेजिस्टरs from sensor */
#घोषणा OV2740_REG_OTP_CUSTOMER		0x7010

काष्ठा nvm_data अणु
	काष्ठा i2c_client *client;
	काष्ठा nvmem_device *nvmem;
	काष्ठा regmap *regmap;
	अक्षर *nvm_buffer;
पूर्ण;

क्रमागत अणु
	OV2740_LINK_FREQ_360MHZ_INDEX,
पूर्ण;

काष्ठा ov2740_reg अणु
	u16 address;
	u8 val;
पूर्ण;

काष्ठा ov2740_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा ov2740_reg *regs;
पूर्ण;

काष्ठा ov2740_link_freq_config अणु
	स्थिर काष्ठा ov2740_reg_list reg_list;
पूर्ण;

काष्ठा ov2740_mode अणु
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
	स्थिर काष्ठा ov2740_reg_list reg_list;
पूर्ण;

अटल स्थिर काष्ठा ov2740_reg mipi_data_rate_720mbps[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0302, 0x4bपूर्ण,
	अणु0x030d, 0x4bपूर्ण,
	अणु0x030e, 0x02पूर्ण,
	अणु0x030a, 0x01पूर्ण,
	अणु0x0312, 0x11पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov2740_reg mode_1932x1092_regs[] = अणु
	अणु0x3000, 0x00पूर्ण,
	अणु0x3018, 0x32पूर्ण,
	अणु0x3031, 0x0aपूर्ण,
	अणु0x3080, 0x08पूर्ण,
	अणु0x3083, 0xB4पूर्ण,
	अणु0x3103, 0x00पूर्ण,
	अणु0x3104, 0x01पूर्ण,
	अणु0x3106, 0x01पूर्ण,
	अणु0x3500, 0x00पूर्ण,
	अणु0x3501, 0x44पूर्ण,
	अणु0x3502, 0x40पूर्ण,
	अणु0x3503, 0x88पूर्ण,
	अणु0x3507, 0x00पूर्ण,
	अणु0x3508, 0x00पूर्ण,
	अणु0x3509, 0x80पूर्ण,
	अणु0x350c, 0x00पूर्ण,
	अणु0x350d, 0x80पूर्ण,
	अणु0x3510, 0x00पूर्ण,
	अणु0x3511, 0x00पूर्ण,
	अणु0x3512, 0x20पूर्ण,
	अणु0x3632, 0x00पूर्ण,
	अणु0x3633, 0x10पूर्ण,
	अणु0x3634, 0x10पूर्ण,
	अणु0x3635, 0x10पूर्ण,
	अणु0x3645, 0x13पूर्ण,
	अणु0x3646, 0x81पूर्ण,
	अणु0x3636, 0x10पूर्ण,
	अणु0x3651, 0x0aपूर्ण,
	अणु0x3656, 0x02पूर्ण,
	अणु0x3659, 0x04पूर्ण,
	अणु0x365a, 0xdaपूर्ण,
	अणु0x365b, 0xa2पूर्ण,
	अणु0x365c, 0x04पूर्ण,
	अणु0x365d, 0x1dपूर्ण,
	अणु0x365e, 0x1aपूर्ण,
	अणु0x3662, 0xd7पूर्ण,
	अणु0x3667, 0x78पूर्ण,
	अणु0x3669, 0x0aपूर्ण,
	अणु0x366a, 0x92पूर्ण,
	अणु0x3700, 0x54पूर्ण,
	अणु0x3702, 0x10पूर्ण,
	अणु0x3706, 0x42पूर्ण,
	अणु0x3709, 0x30पूर्ण,
	अणु0x370b, 0xc2पूर्ण,
	अणु0x3714, 0x63पूर्ण,
	अणु0x3715, 0x01पूर्ण,
	अणु0x3716, 0x00पूर्ण,
	अणु0x371a, 0x3eपूर्ण,
	अणु0x3732, 0x0eपूर्ण,
	अणु0x3733, 0x10पूर्ण,
	अणु0x375f, 0x0eपूर्ण,
	अणु0x3768, 0x30पूर्ण,
	अणु0x3769, 0x44पूर्ण,
	अणु0x376a, 0x22पूर्ण,
	अणु0x377b, 0x20पूर्ण,
	अणु0x377c, 0x00पूर्ण,
	अणु0x377d, 0x0cपूर्ण,
	अणु0x3798, 0x00पूर्ण,
	अणु0x37a1, 0x55पूर्ण,
	अणु0x37a8, 0x6dपूर्ण,
	अणु0x37c2, 0x04पूर्ण,
	अणु0x37c5, 0x00पूर्ण,
	अणु0x37c8, 0x00पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x07पूर्ण,
	अणु0x3805, 0x8fपूर्ण,
	अणु0x3806, 0x04पूर्ण,
	अणु0x3807, 0x47पूर्ण,
	अणु0x3808, 0x07पूर्ण,
	अणु0x3809, 0x88पूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0x40पूर्ण,
	अणु0x380c, 0x04पूर्ण,
	अणु0x380d, 0x38पूर्ण,
	अणु0x380e, 0x04पूर्ण,
	अणु0x380f, 0x60पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x04पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x04पूर्ण,
	अणु0x3814, 0x01पूर्ण,
	अणु0x3815, 0x01पूर्ण,
	अणु0x3820, 0x80पूर्ण,
	अणु0x3821, 0x46पूर्ण,
	अणु0x3822, 0x84पूर्ण,
	अणु0x3829, 0x00पूर्ण,
	अणु0x382a, 0x01पूर्ण,
	अणु0x382b, 0x01पूर्ण,
	अणु0x3830, 0x04पूर्ण,
	अणु0x3836, 0x01पूर्ण,
	अणु0x3837, 0x08पूर्ण,
	अणु0x3839, 0x01पूर्ण,
	अणु0x383a, 0x00पूर्ण,
	अणु0x383b, 0x08पूर्ण,
	अणु0x383c, 0x00पूर्ण,
	अणु0x3f0b, 0x00पूर्ण,
	अणु0x4001, 0x20पूर्ण,
	अणु0x4009, 0x07पूर्ण,
	अणु0x4003, 0x10पूर्ण,
	अणु0x4010, 0xe0पूर्ण,
	अणु0x4016, 0x00पूर्ण,
	अणु0x4017, 0x10पूर्ण,
	अणु0x4044, 0x02पूर्ण,
	अणु0x4304, 0x08पूर्ण,
	अणु0x4307, 0x30पूर्ण,
	अणु0x4320, 0x80पूर्ण,
	अणु0x4322, 0x00पूर्ण,
	अणु0x4323, 0x00पूर्ण,
	अणु0x4324, 0x00पूर्ण,
	अणु0x4325, 0x00पूर्ण,
	अणु0x4326, 0x00पूर्ण,
	अणु0x4327, 0x00पूर्ण,
	अणु0x4328, 0x00पूर्ण,
	अणु0x4329, 0x00पूर्ण,
	अणु0x432c, 0x03पूर्ण,
	अणु0x432d, 0x81पूर्ण,
	अणु0x4501, 0x84पूर्ण,
	अणु0x4502, 0x40पूर्ण,
	अणु0x4503, 0x18पूर्ण,
	अणु0x4504, 0x04पूर्ण,
	अणु0x4508, 0x02पूर्ण,
	अणु0x4601, 0x10पूर्ण,
	अणु0x4800, 0x00पूर्ण,
	अणु0x4816, 0x52पूर्ण,
	अणु0x4837, 0x16पूर्ण,
	अणु0x5000, 0x7fपूर्ण,
	अणु0x5001, 0x00पूर्ण,
	अणु0x5005, 0x38पूर्ण,
	अणु0x501e, 0x0dपूर्ण,
	अणु0x5040, 0x00पूर्ण,
	अणु0x5901, 0x00पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x07पूर्ण,
	अणु0x3805, 0x8fपूर्ण,
	अणु0x3806, 0x04पूर्ण,
	अणु0x3807, 0x47पूर्ण,
	अणु0x3808, 0x07पूर्ण,
	अणु0x3809, 0x8cपूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0x44पूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x00पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x01पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov2740_test_pattern_menu[] = अणु
	"Disabled",
	"Color Bar",
	"Top-Bottom Darker Color Bar",
	"Right-Left Darker Color Bar",
	"Bottom-Top Darker Color Bar",
पूर्ण;

अटल स्थिर s64 link_freq_menu_items[] = अणु
	OV2740_LINK_FREQ_360MHZ,
पूर्ण;

अटल स्थिर काष्ठा ov2740_link_freq_config link_freq_configs[] = अणु
	[OV2740_LINK_FREQ_360MHZ_INDEX] = अणु
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_720mbps),
			.regs = mipi_data_rate_720mbps,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov2740_mode supported_modes[] = अणु
	अणु
		.width = 1932,
		.height = 1092,
		.hts = 1080,
		.vts_def = OV2740_VTS_DEF,
		.vts_min = OV2740_VTS_MIN,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1932x1092_regs),
			.regs = mode_1932x1092_regs,
		पूर्ण,
		.link_freq_index = OV2740_LINK_FREQ_360MHZ_INDEX,
	पूर्ण,
पूर्ण;

काष्ठा ov2740 अणु
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
	स्थिर काष्ठा ov2740_mode *cur_mode;

	/* To serialize asynchronus callbacks */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;

	/* NVM data inक्रमamtion */
	काष्ठा nvm_data *nvm;
पूर्ण;

अटल अंतरभूत काष्ठा ov2740 *to_ov2740(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा ov2740, sd);
पूर्ण

अटल u64 to_pixel_rate(u32 f_index)
अणु
	u64 pixel_rate = link_freq_menu_items[f_index] * 2 * OV2740_DATA_LANES;

	करो_भाग(pixel_rate, OV2740_RGB_DEPTH);

	वापस pixel_rate;
पूर्ण

अटल u64 to_pixels_per_line(u32 hts, u32 f_index)
अणु
	u64 ppl = hts * to_pixel_rate(f_index);

	करो_भाग(ppl, OV2740_SCLK);

	वापस ppl;
पूर्ण

अटल पूर्णांक ov2740_पढ़ो_reg(काष्ठा ov2740 *ov2740, u16 reg, u16 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2740->sd);
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2];
	u8 data_buf[4] = अणु0पूर्ण;
	पूर्णांक ret = 0;

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

अटल पूर्णांक ov2740_ग_लिखो_reg(काष्ठा ov2740 *ov2740, u16 reg, u16 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2740->sd);
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

अटल पूर्णांक ov2740_ग_लिखो_reg_list(काष्ठा ov2740 *ov2740,
				 स्थिर काष्ठा ov2740_reg_list *r_list)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2740->sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < r_list->num_of_regs; i++) अणु
		ret = ov2740_ग_लिखो_reg(ov2740, r_list->regs[i].address, 1,
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

अटल पूर्णांक ov2740_update_digital_gain(काष्ठा ov2740 *ov2740, u32 d_gain)
अणु
	पूर्णांक ret = 0;

	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_MWB_R_GAIN, 2, d_gain);
	अगर (ret)
		वापस ret;

	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_MWB_G_GAIN, 2, d_gain);
	अगर (ret)
		वापस ret;

	वापस ov2740_ग_लिखो_reg(ov2740, OV2740_REG_MWB_B_GAIN, 2, d_gain);
पूर्ण

अटल पूर्णांक ov2740_test_pattern(काष्ठा ov2740 *ov2740, u32 pattern)
अणु
	अगर (pattern)
		pattern = (pattern - 1) << OV2740_TEST_PATTERN_BAR_SHIFT |
			  OV2740_TEST_PATTERN_ENABLE;

	वापस ov2740_ग_लिखो_reg(ov2740, OV2740_REG_TEST_PATTERN, 1, pattern);
पूर्ण

अटल पूर्णांक ov2740_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov2740 *ov2740 = container_of(ctrl->handler,
					     काष्ठा ov2740, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2740->sd);
	s64 exposure_max;
	पूर्णांक ret = 0;

	/* Propagate change of current control to all related controls */
	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = ov2740->cur_mode->height + ctrl->val -
			       OV2740_EXPOSURE_MAX_MARGIN;
		__v4l2_ctrl_modअगरy_range(ov2740->exposure,
					 ov2740->exposure->minimum,
					 exposure_max, ov2740->exposure->step,
					 exposure_max);
	पूर्ण

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_ANALOG_GAIN, 2,
				       ctrl->val);
		अवरोध;

	हाल V4L2_CID_DIGITAL_GAIN:
		ret = ov2740_update_digital_gain(ov2740, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE:
		/* 4 least signअगरicant bits of expsoure are fractional part */
		ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_EXPOSURE, 3,
				       ctrl->val << 4);
		अवरोध;

	हाल V4L2_CID_VBLANK:
		ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_VTS, 2,
				       ov2740->cur_mode->height + ctrl->val);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		ret = ov2740_test_pattern(ov2740, ctrl->val);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov2740_ctrl_ops = अणु
	.s_ctrl = ov2740_set_ctrl,
पूर्ण;

अटल पूर्णांक ov2740_init_controls(काष्ठा ov2740 *ov2740)
अणु
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	स्थिर काष्ठा ov2740_mode *cur_mode;
	s64 exposure_max, h_blank, pixel_rate;
	u32 vblank_min, vblank_max, vblank_शेष;
	पूर्णांक size;
	पूर्णांक ret = 0;

	ctrl_hdlr = &ov2740->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 8);
	अगर (ret)
		वापस ret;

	ctrl_hdlr->lock = &ov2740->mutex;
	cur_mode = ov2740->cur_mode;
	size = ARRAY_SIZE(link_freq_menu_items);

	ov2740->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr, &ov2740_ctrl_ops,
						   V4L2_CID_LINK_FREQ,
						   size - 1, 0,
						   link_freq_menu_items);
	अगर (ov2740->link_freq)
		ov2740->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	pixel_rate = to_pixel_rate(OV2740_LINK_FREQ_360MHZ_INDEX);
	ov2740->pixel_rate = v4l2_ctrl_new_std(ctrl_hdlr, &ov2740_ctrl_ops,
					       V4L2_CID_PIXEL_RATE, 0,
					       pixel_rate, 1, pixel_rate);

	vblank_min = cur_mode->vts_min - cur_mode->height;
	vblank_max = OV2740_VTS_MAX - cur_mode->height;
	vblank_शेष = cur_mode->vts_def - cur_mode->height;
	ov2740->vblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov2740_ctrl_ops,
					   V4L2_CID_VBLANK, vblank_min,
					   vblank_max, 1, vblank_शेष);

	h_blank = to_pixels_per_line(cur_mode->hts, cur_mode->link_freq_index);
	h_blank -= cur_mode->width;
	ov2740->hblank = v4l2_ctrl_new_std(ctrl_hdlr, &ov2740_ctrl_ops,
					   V4L2_CID_HBLANK, h_blank, h_blank, 1,
					   h_blank);
	अगर (ov2740->hblank)
		ov2740->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	v4l2_ctrl_new_std(ctrl_hdlr, &ov2740_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  OV2740_ANAL_GAIN_MIN, OV2740_ANAL_GAIN_MAX,
			  OV2740_ANAL_GAIN_STEP, OV2740_ANAL_GAIN_MIN);
	v4l2_ctrl_new_std(ctrl_hdlr, &ov2740_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  OV2740_DGTL_GAIN_MIN, OV2740_DGTL_GAIN_MAX,
			  OV2740_DGTL_GAIN_STEP, OV2740_DGTL_GAIN_DEFAULT);
	exposure_max = cur_mode->vts_def - OV2740_EXPOSURE_MAX_MARGIN;
	ov2740->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &ov2740_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     OV2740_EXPOSURE_MIN, exposure_max,
					     OV2740_EXPOSURE_STEP,
					     exposure_max);
	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &ov2740_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov2740_test_pattern_menu) - 1,
				     0, 0, ov2740_test_pattern_menu);
	अगर (ctrl_hdlr->error)
		वापस ctrl_hdlr->error;

	ov2740->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;
पूर्ण

अटल व्योम ov2740_update_pad_क्रमmat(स्थिर काष्ठा ov2740_mode *mode,
				     काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov2740_load_otp_data(काष्ठा nvm_data *nvm)
अणु
	काष्ठा i2c_client *client;
	काष्ठा ov2740 *ov2740;
	u32 isp_ctrl00 = 0;
	u32 isp_ctrl01 = 0;
	पूर्णांक ret;

	अगर (!nvm)
		वापस -EINVAL;

	अगर (nvm->nvm_buffer)
		वापस 0;

	client = nvm->client;
	ov2740 = to_ov2740(i2c_get_clientdata(client));

	nvm->nvm_buffer = kzalloc(CUSTOMER_USE_OTP_SIZE, GFP_KERNEL);
	अगर (!nvm->nvm_buffer)
		वापस -ENOMEM;

	ret = ov2740_पढ़ो_reg(ov2740, OV2740_REG_ISP_CTRL00, 1, &isp_ctrl00);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to read ISP CTRL00\n");
		जाओ err;
	पूर्ण

	ret = ov2740_पढ़ो_reg(ov2740, OV2740_REG_ISP_CTRL01, 1, &isp_ctrl01);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to read ISP CTRL01\n");
		जाओ err;
	पूर्ण

	/* Clear bit 5 of ISP CTRL00 */
	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_ISP_CTRL00, 1,
			       isp_ctrl00 & ~BIT(5));
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set ISP CTRL00\n");
		जाओ err;
	पूर्ण

	/* Clear bit 7 of ISP CTRL01 */
	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_ISP_CTRL01, 1,
			       isp_ctrl01 & ~BIT(7));
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set ISP CTRL01\n");
		जाओ err;
	पूर्ण

	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_MODE_SELECT, 1,
			       OV2740_MODE_STREAMING);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set streaming mode\n");
		जाओ err;
	पूर्ण

	/*
	 * Users are not allowed to access OTP-related रेजिस्टरs and memory
	 * during the 20 ms period after streaming starts (0x100 = 0x01).
	 */
	msleep(20);

	ret = regmap_bulk_पढ़ो(nvm->regmap, OV2740_REG_OTP_CUSTOMER,
			       nvm->nvm_buffer, CUSTOMER_USE_OTP_SIZE);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to read OTP data, ret %d\n", ret);
		जाओ err;
	पूर्ण

	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_MODE_SELECT, 1,
			       OV2740_MODE_STANDBY);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set streaming mode\n");
		जाओ err;
	पूर्ण

	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_ISP_CTRL01, 1, isp_ctrl01);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set ISP CTRL01\n");
		जाओ err;
	पूर्ण

	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_ISP_CTRL00, 1, isp_ctrl00);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set ISP CTRL00\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	kमुक्त(nvm->nvm_buffer);
	nvm->nvm_buffer = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक ov2740_start_streaming(काष्ठा ov2740 *ov2740)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2740->sd);
	काष्ठा nvm_data *nvm = ov2740->nvm;
	स्थिर काष्ठा ov2740_reg_list *reg_list;
	पूर्णांक link_freq_index;
	पूर्णांक ret = 0;

	ov2740_load_otp_data(nvm);

	link_freq_index = ov2740->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = ov2740_ग_लिखो_reg_list(ov2740, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set plls");
		वापस ret;
	पूर्ण

	reg_list = &ov2740->cur_mode->reg_list;
	ret = ov2740_ग_लिखो_reg_list(ov2740, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set mode");
		वापस ret;
	पूर्ण

	ret = __v4l2_ctrl_handler_setup(ov2740->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	ret = ov2740_ग_लिखो_reg(ov2740, OV2740_REG_MODE_SELECT, 1,
			       OV2740_MODE_STREAMING);
	अगर (ret)
		dev_err(&client->dev, "failed to start streaming");

	वापस ret;
पूर्ण

अटल व्योम ov2740_stop_streaming(काष्ठा ov2740 *ov2740)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2740->sd);

	अगर (ov2740_ग_लिखो_reg(ov2740, OV2740_REG_MODE_SELECT, 1,
			     OV2740_MODE_STANDBY))
		dev_err(&client->dev, "failed to stop streaming");
पूर्ण

अटल पूर्णांक ov2740_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (ov2740->streaming == enable)
		वापस 0;

	mutex_lock(&ov2740->mutex);
	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			mutex_unlock(&ov2740->mutex);
			वापस ret;
		पूर्ण

		ret = ov2740_start_streaming(ov2740);
		अगर (ret) अणु
			enable = 0;
			ov2740_stop_streaming(ov2740);
			pm_runसमय_put(&client->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		ov2740_stop_streaming(ov2740);
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov2740->streaming = enable;
	mutex_unlock(&ov2740->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ov2740_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);

	mutex_lock(&ov2740->mutex);
	अगर (ov2740->streaming)
		ov2740_stop_streaming(ov2740);

	mutex_unlock(&ov2740->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov2740_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov2740->mutex);
	अगर (!ov2740->streaming)
		जाओ निकास;

	ret = ov2740_start_streaming(ov2740);
	अगर (ret) अणु
		ov2740->streaming = false;
		ov2740_stop_streaming(ov2740);
	पूर्ण

निकास:
	mutex_unlock(&ov2740->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2740_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);
	स्थिर काष्ठा ov2740_mode *mode;
	s32 vblank_def, h_blank;

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes), width,
				      height, fmt->क्रमmat.width,
				      fmt->क्रमmat.height);

	mutex_lock(&ov2740->mutex);
	ov2740_update_pad_क्रमmat(mode, &fmt->क्रमmat);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		ov2740->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(ov2740->link_freq, mode->link_freq_index);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(ov2740->pixel_rate,
					 to_pixel_rate(mode->link_freq_index));

		/* Update limits and set FPS to शेष */
		vblank_def = mode->vts_def - mode->height;
		__v4l2_ctrl_modअगरy_range(ov2740->vblank,
					 mode->vts_min - mode->height,
					 OV2740_VTS_MAX - mode->height, 1,
					 vblank_def);
		__v4l2_ctrl_s_ctrl(ov2740->vblank, vblank_def);
		h_blank = to_pixels_per_line(mode->hts, mode->link_freq_index) -
			  mode->width;
		__v4l2_ctrl_modअगरy_range(ov2740->hblank, h_blank, h_blank, 1,
					 h_blank);
	पूर्ण
	mutex_unlock(&ov2740->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2740_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);

	mutex_lock(&ov2740->mutex);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(&ov2740->sd, cfg,
							  fmt->pad);
	अन्यथा
		ov2740_update_pad_क्रमmat(ov2740->cur_mode, &fmt->क्रमmat);

	mutex_unlock(&ov2740->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2740_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2740_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
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

अटल पूर्णांक ov2740_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);

	mutex_lock(&ov2740->mutex);
	ov2740_update_pad_क्रमmat(&supported_modes[0],
				 v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0));
	mutex_unlock(&ov2740->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov2740_video_ops = अणु
	.s_stream = ov2740_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov2740_pad_ops = अणु
	.set_fmt = ov2740_set_क्रमmat,
	.get_fmt = ov2740_get_क्रमmat,
	.क्रमागत_mbus_code = ov2740_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov2740_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov2740_subdev_ops = अणु
	.video = &ov2740_video_ops,
	.pad = &ov2740_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ov2740_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov2740_पूर्णांकernal_ops = अणु
	.खोलो = ov2740_खोलो,
पूर्ण;

अटल पूर्णांक ov2740_identअगरy_module(काष्ठा ov2740 *ov2740)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov2740->sd);
	पूर्णांक ret;
	u32 val;

	ret = ov2740_पढ़ो_reg(ov2740, OV2740_REG_CHIP_ID, 3, &val);
	अगर (ret)
		वापस ret;

	अगर (val != OV2740_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x",
			OV2740_CHIP_ID, val);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov2740_check_hwcfg(काष्ठा device *dev)
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

	अगर (mclk != OV2740_MCLK) अणु
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

	अगर (bus_cfg.bus.mipi_csi2.num_data_lanes != OV2740_DATA_LANES) अणु
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

अटल पूर्णांक ov2740_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	pm_runसमय_disable(&client->dev);
	mutex_destroy(&ov2740->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2740_nvmem_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val,
			     माप_प्रकार count)
अणु
	काष्ठा nvm_data *nvm = priv;
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(nvm->client);
	काष्ठा device *dev = &nvm->client->dev;
	काष्ठा ov2740 *ov2740 = to_ov2740(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov2740->mutex);

	अगर (nvm->nvm_buffer) अणु
		स_नकल(val, nvm->nvm_buffer + off, count);
		जाओ निकास;
	पूर्ण

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ निकास;
	पूर्ण

	ret = ov2740_load_otp_data(nvm);
	अगर (!ret)
		स_नकल(val, nvm->nvm_buffer + off, count);

	pm_runसमय_put(dev);
निकास:
	mutex_unlock(&ov2740->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ov2740_रेजिस्टर_nvmem(काष्ठा i2c_client *client,
				 काष्ठा ov2740 *ov2740)
अणु
	काष्ठा nvm_data *nvm;
	काष्ठा regmap_config regmap_config = अणु पूर्ण;
	काष्ठा nvmem_config nvmem_config = अणु पूर्ण;
	काष्ठा regmap *regmap;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	nvm = devm_kzalloc(dev, माप(*nvm), GFP_KERNEL);
	अगर (!nvm)
		वापस -ENOMEM;

	regmap_config.val_bits = 8;
	regmap_config.reg_bits = 16;
	regmap_config.disable_locking = true;
	regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	nvm->regmap = regmap;
	nvm->client = client;

	nvmem_config.name = dev_name(dev);
	nvmem_config.dev = dev;
	nvmem_config.पढ़ो_only = true;
	nvmem_config.root_only = true;
	nvmem_config.owner = THIS_MODULE;
	nvmem_config.compat = true;
	nvmem_config.base_dev = dev;
	nvmem_config.reg_पढ़ो = ov2740_nvmem_पढ़ो;
	nvmem_config.reg_ग_लिखो = शून्य;
	nvmem_config.priv = nvm;
	nvmem_config.stride = 1;
	nvmem_config.word_size = 1;
	nvmem_config.size = CUSTOMER_USE_OTP_SIZE;

	nvm->nvmem = devm_nvmem_रेजिस्टर(dev, &nvmem_config);

	ret = PTR_ERR_OR_ZERO(nvm->nvmem);
	अगर (!ret)
		ov2740->nvm = nvm;

	वापस ret;
पूर्ण

अटल पूर्णांक ov2740_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov2740 *ov2740;
	पूर्णांक ret = 0;

	ret = ov2740_check_hwcfg(&client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to check HW configuration: %d",
			ret);
		वापस ret;
	पूर्ण

	ov2740 = devm_kzalloc(&client->dev, माप(*ov2740), GFP_KERNEL);
	अगर (!ov2740)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&ov2740->sd, client, &ov2740_subdev_ops);
	ret = ov2740_identअगरy_module(ov2740);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		वापस ret;
	पूर्ण

	mutex_init(&ov2740->mutex);
	ov2740->cur_mode = &supported_modes[0];
	ret = ov2740_init_controls(ov2740);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init controls: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ov2740->sd.पूर्णांकernal_ops = &ov2740_पूर्णांकernal_ops;
	ov2740->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov2740->sd.entity.ops = &ov2740_subdev_entity_ops;
	ov2740->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ov2740->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&ov2740->sd.entity, 1, &ov2740->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&ov2740->sd);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to register V4L2 subdev: %d",
			ret);
		जाओ probe_error_media_entity_cleanup;
	पूर्ण

	ret = ov2740_रेजिस्टर_nvmem(client, ov2740);
	अगर (ret)
		dev_warn(&client->dev, "register nvmem failed, ret %d\n", ret);

	/*
	 * Device is alपढ़ोy turned on by i2c-core with ACPI करोमुख्य PM.
	 * Enable runसमय PM and turn off the device.
	 */
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

probe_error_media_entity_cleanup:
	media_entity_cleanup(&ov2740->sd.entity);

probe_error_v4l2_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(ov2740->sd.ctrl_handler);
	mutex_destroy(&ov2740->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov2740_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ov2740_suspend, ov2740_resume)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id ov2740_acpi_ids[] = अणु
	अणु"INT3474"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, ov2740_acpi_ids);

अटल काष्ठा i2c_driver ov2740_i2c_driver = अणु
	.driver = अणु
		.name = "ov2740",
		.pm = &ov2740_pm_ops,
		.acpi_match_table = ov2740_acpi_ids,
	पूर्ण,
	.probe_new = ov2740_probe,
	.हटाओ = ov2740_हटाओ,
पूर्ण;

module_i2c_driver(ov2740_i2c_driver);

MODULE_AUTHOR("Qiu, Tianshu <tian.shu.qiu@intel.com>");
MODULE_AUTHOR("Shawn Tu <shawnx.tu@intel.com>");
MODULE_AUTHOR("Bingbu Cao <bingbu.cao@intel.com>");
MODULE_DESCRIPTION("OmniVision OV2740 sensor driver");
MODULE_LICENSE("GPL v2");
