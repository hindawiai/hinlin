<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Omnivision OV2680 CMOS Image Sensor driver
 *
 * Copyright (C) 2018 Linaro Ltd
 *
 * Based on OV5640 Sensor Driver
 * Copyright (C) 2011-2013 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2014-2017 Mentor Graphics Inc.
 *
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा OV2680_XVCLK_VALUE	24000000

#घोषणा OV2680_CHIP_ID		0x2680

#घोषणा OV2680_REG_STREAM_CTRL		0x0100
#घोषणा OV2680_REG_SOFT_RESET		0x0103

#घोषणा OV2680_REG_CHIP_ID_HIGH		0x300a
#घोषणा OV2680_REG_CHIP_ID_LOW		0x300b

#घोषणा OV2680_REG_R_MANUAL		0x3503
#घोषणा OV2680_REG_GAIN_PK		0x350a
#घोषणा OV2680_REG_EXPOSURE_PK_HIGH	0x3500
#घोषणा OV2680_REG_TIMING_HTS		0x380c
#घोषणा OV2680_REG_TIMING_VTS		0x380e
#घोषणा OV2680_REG_FORMAT1		0x3820
#घोषणा OV2680_REG_FORMAT2		0x3821

#घोषणा OV2680_REG_ISP_CTRL00		0x5080

#घोषणा OV2680_FRAME_RATE		30

#घोषणा OV2680_REG_VALUE_8BIT		1
#घोषणा OV2680_REG_VALUE_16BIT		2
#घोषणा OV2680_REG_VALUE_24BIT		3

#घोषणा OV2680_WIDTH_MAX		1600
#घोषणा OV2680_HEIGHT_MAX		1200

क्रमागत ov2680_mode_id अणु
	OV2680_MODE_QUXGA_800_600,
	OV2680_MODE_720P_1280_720,
	OV2680_MODE_UXGA_1600_1200,
	OV2680_MODE_MAX,
पूर्ण;

काष्ठा reg_value अणु
	u16 reg_addr;
	u8 val;
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov2680_supply_name[] = अणु
	"DOVDD",
	"DVDD",
	"AVDD",
पूर्ण;

#घोषणा OV2680_NUM_SUPPLIES ARRAY_SIZE(ov2680_supply_name)

काष्ठा ov2680_mode_info अणु
	स्थिर अक्षर *name;
	क्रमागत ov2680_mode_id id;
	u32 width;
	u32 height;
	स्थिर काष्ठा reg_value *reg_data;
	u32 reg_data_size;
पूर्ण;

काष्ठा ov2680_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_exp;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_gain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;

	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *test_pattern;
पूर्ण;

काष्ठा ov2680_dev अणु
	काष्ठा i2c_client		*i2c_client;
	काष्ठा v4l2_subdev		sd;

	काष्ठा media_pad		pad;
	काष्ठा clk			*xvclk;
	u32				xvclk_freq;
	काष्ठा regulator_bulk_data	supplies[OV2680_NUM_SUPPLIES];

	काष्ठा gpio_desc		*reset_gpio;
	काष्ठा mutex			lock; /* protect members */

	bool				mode_pending_changes;
	bool				is_enabled;
	bool				is_streaming;

	काष्ठा ov2680_ctrls		ctrls;
	काष्ठा v4l2_mbus_framefmt	fmt;
	काष्ठा v4l2_fract		frame_पूर्णांकerval;

	स्थिर काष्ठा ov2680_mode_info	*current_mode;
पूर्ण;

अटल स्थिर अक्षर * स्थिर test_pattern_menu[] = अणु
	"Disabled",
	"Color Bars",
	"Random Data",
	"Square",
	"Black Image",
पूर्ण;

अटल स्थिर पूर्णांक ov2680_hv_flip_bayer_order[] = अणु
	MEDIA_BUS_FMT_SBGGR10_1X10,
	MEDIA_BUS_FMT_SGRBG10_1X10,
	MEDIA_BUS_FMT_SGBRG10_1X10,
	MEDIA_BUS_FMT_SRGGB10_1X10,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov2680_setting_30fps_QUXGA_800_600[] = अणु
	अणु0x3086, 0x01पूर्ण, अणु0x370a, 0x23पूर्ण, अणु0x3808, 0x03पूर्ण, अणु0x3809, 0x20पूर्ण,
	अणु0x380a, 0x02पूर्ण, अणु0x380b, 0x58पूर्ण, अणु0x380c, 0x06पूर्ण, अणु0x380d, 0xacपूर्ण,
	अणु0x380e, 0x02पूर्ण, अणु0x380f, 0x84पूर्ण, अणु0x3811, 0x04पूर्ण, अणु0x3813, 0x04पूर्ण,
	अणु0x3814, 0x31पूर्ण, अणु0x3815, 0x31पूर्ण, अणु0x3820, 0xc0पूर्ण, अणु0x4008, 0x00पूर्ण,
	अणु0x4009, 0x03पूर्ण, अणु0x4837, 0x1eपूर्ण, अणु0x3501, 0x4eपूर्ण, अणु0x3502, 0xe0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov2680_setting_30fps_720P_1280_720[] = अणु
	अणु0x3086, 0x00पूर्ण, अणु0x3808, 0x05पूर्ण, अणु0x3809, 0x00पूर्ण, अणु0x380a, 0x02पूर्ण,
	अणु0x380b, 0xd0पूर्ण, अणु0x380c, 0x06पूर्ण, अणु0x380d, 0xa8पूर्ण, अणु0x380e, 0x05पूर्ण,
	अणु0x380f, 0x0eपूर्ण, अणु0x3811, 0x08पूर्ण, अणु0x3813, 0x06पूर्ण, अणु0x3814, 0x11पूर्ण,
	अणु0x3815, 0x11पूर्ण, अणु0x3820, 0xc0पूर्ण, अणु0x4008, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_value ov2680_setting_30fps_UXGA_1600_1200[] = अणु
	अणु0x3086, 0x00पूर्ण, अणु0x3501, 0x4eपूर्ण, अणु0x3502, 0xe0पूर्ण, अणु0x3808, 0x06पूर्ण,
	अणु0x3809, 0x40पूर्ण, अणु0x380a, 0x04पूर्ण, अणु0x380b, 0xb0पूर्ण, अणु0x380c, 0x06पूर्ण,
	अणु0x380d, 0xa8पूर्ण, अणु0x380e, 0x05पूर्ण, अणु0x380f, 0x0eपूर्ण, अणु0x3811, 0x00पूर्ण,
	अणु0x3813, 0x00पूर्ण, अणु0x3814, 0x11पूर्ण, अणु0x3815, 0x11पूर्ण, अणु0x3820, 0xc0पूर्ण,
	अणु0x4008, 0x00पूर्ण, अणु0x4837, 0x18पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ov2680_mode_info ov2680_mode_init_data = अणु
	"mode_quxga_800_600", OV2680_MODE_QUXGA_800_600, 800, 600,
	ov2680_setting_30fps_QUXGA_800_600,
	ARRAY_SIZE(ov2680_setting_30fps_QUXGA_800_600),
पूर्ण;

अटल स्थिर काष्ठा ov2680_mode_info ov2680_mode_data[OV2680_MODE_MAX] = अणु
	अणु"mode_quxga_800_600", OV2680_MODE_QUXGA_800_600,
	 800, 600, ov2680_setting_30fps_QUXGA_800_600,
	 ARRAY_SIZE(ov2680_setting_30fps_QUXGA_800_600)पूर्ण,
	अणु"mode_720p_1280_720", OV2680_MODE_720P_1280_720,
	 1280, 720, ov2680_setting_30fps_720P_1280_720,
	 ARRAY_SIZE(ov2680_setting_30fps_720P_1280_720)पूर्ण,
	अणु"mode_uxga_1600_1200", OV2680_MODE_UXGA_1600_1200,
	 1600, 1200, ov2680_setting_30fps_UXGA_1600_1200,
	 ARRAY_SIZE(ov2680_setting_30fps_UXGA_1600_1200)पूर्ण,
पूर्ण;

अटल काष्ठा ov2680_dev *to_ov2680_dev(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov2680_dev, sd);
पूर्ण

अटल काष्ठा device *ov2680_to_dev(काष्ठा ov2680_dev *sensor)
अणु
	वापस &sensor->i2c_client->dev;
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *ctrl_to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा ov2680_dev,
			     ctrls.handler)->sd;
पूर्ण

अटल पूर्णांक __ov2680_ग_लिखो_reg(काष्ठा ov2680_dev *sensor, u16 reg,
			      अचिन्हित पूर्णांक len, u32 val)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	u8 buf[6];
	पूर्णांक ret;

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);
	put_unaligned_be32(val << (8 * (4 - len)), buf + 2);
	ret = i2c_master_send(client, buf, len + 2);
	अगर (ret != len + 2) अणु
		dev_err(&client->dev, "write error: reg=0x%4x: %d\n", reg, ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ov2680_ग_लिखो_reg(s, r, v) \
	__ov2680_ग_लिखो_reg(s, r, OV2680_REG_VALUE_8BIT, v)

#घोषणा ov2680_ग_लिखो_reg16(s, r, v) \
	__ov2680_ग_लिखो_reg(s, r, OV2680_REG_VALUE_16BIT, v)

#घोषणा ov2680_ग_लिखो_reg24(s, r, v) \
	__ov2680_ग_लिखो_reg(s, r, OV2680_REG_VALUE_24BIT, v)

अटल पूर्णांक __ov2680_पढ़ो_reg(काष्ठा ov2680_dev *sensor, u16 reg,
			     अचिन्हित पूर्णांक len, u32 *val)
अणु
	काष्ठा i2c_client *client = sensor->i2c_client;
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2] = अणु reg >> 8, reg & 0xff पूर्ण;
	u8 data_buf[4] = अणु 0, पूर्ण;
	पूर्णांक ret;

	अगर (len > 4)
		वापस -EINVAL;

	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = ARRAY_SIZE(addr_buf);
	msgs[0].buf = addr_buf;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = &data_buf[4 - len];

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(&client->dev, "read error: reg=0x%4x: %d\n", reg, ret);
		वापस -EIO;
	पूर्ण

	*val = get_unaligned_be32(data_buf);

	वापस 0;
पूर्ण

#घोषणा ov2680_पढ़ो_reg(s, r, v) \
	__ov2680_पढ़ो_reg(s, r, OV2680_REG_VALUE_8BIT, v)

#घोषणा ov2680_पढ़ो_reg16(s, r, v) \
	__ov2680_पढ़ो_reg(s, r, OV2680_REG_VALUE_16BIT, v)

#घोषणा ov2680_पढ़ो_reg24(s, r, v) \
	__ov2680_पढ़ो_reg(s, r, OV2680_REG_VALUE_24BIT, v)

अटल पूर्णांक ov2680_mod_reg(काष्ठा ov2680_dev *sensor, u16 reg, u8 mask, u8 val)
अणु
	u32 पढ़ोval;
	पूर्णांक ret;

	ret = ov2680_पढ़ो_reg(sensor, reg, &पढ़ोval);
	अगर (ret < 0)
		वापस ret;

	पढ़ोval &= ~mask;
	val &= mask;
	val |= पढ़ोval;

	वापस ov2680_ग_लिखो_reg(sensor, reg, val);
पूर्ण

अटल पूर्णांक ov2680_load_regs(काष्ठा ov2680_dev *sensor,
			    स्थिर काष्ठा ov2680_mode_info *mode)
अणु
	स्थिर काष्ठा reg_value *regs = mode->reg_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;
	u16 reg_addr;
	u8 val;

	क्रम (i = 0; i < mode->reg_data_size; ++i, ++regs) अणु
		reg_addr = regs->reg_addr;
		val = regs->val;

		ret = ov2680_ग_लिखो_reg(sensor, reg_addr, val);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ov2680_घातer_up(काष्ठा ov2680_dev *sensor)
अणु
	अगर (!sensor->reset_gpio)
		वापस;

	gpiod_set_value(sensor->reset_gpio, 0);
	usleep_range(5000, 10000);
पूर्ण

अटल व्योम ov2680_घातer_करोwn(काष्ठा ov2680_dev *sensor)
अणु
	अगर (!sensor->reset_gpio)
		वापस;

	gpiod_set_value(sensor->reset_gpio, 1);
	usleep_range(5000, 10000);
पूर्ण

अटल पूर्णांक ov2680_bayer_order(काष्ठा ov2680_dev *sensor)
अणु
	u32 क्रमmat1;
	u32 क्रमmat2;
	u32 hv_flip;
	पूर्णांक ret;

	ret = ov2680_पढ़ो_reg(sensor, OV2680_REG_FORMAT1, &क्रमmat1);
	अगर (ret < 0)
		वापस ret;

	ret = ov2680_पढ़ो_reg(sensor, OV2680_REG_FORMAT2, &क्रमmat2);
	अगर (ret < 0)
		वापस ret;

	hv_flip = (क्रमmat2 & BIT(2)  << 1) | (क्रमmat1 & BIT(2));

	sensor->fmt.code = ov2680_hv_flip_bayer_order[hv_flip];

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_vflip_enable(काष्ठा ov2680_dev *sensor)
अणु
	पूर्णांक ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_FORMAT1, BIT(2), BIT(2));
	अगर (ret < 0)
		वापस ret;

	वापस ov2680_bayer_order(sensor);
पूर्ण

अटल पूर्णांक ov2680_vflip_disable(काष्ठा ov2680_dev *sensor)
अणु
	पूर्णांक ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_FORMAT1, BIT(2), BIT(0));
	अगर (ret < 0)
		वापस ret;

	वापस ov2680_bayer_order(sensor);
पूर्ण

अटल पूर्णांक ov2680_hflip_enable(काष्ठा ov2680_dev *sensor)
अणु
	पूर्णांक ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_FORMAT2, BIT(2), BIT(2));
	अगर (ret < 0)
		वापस ret;

	वापस ov2680_bayer_order(sensor);
पूर्ण

अटल पूर्णांक ov2680_hflip_disable(काष्ठा ov2680_dev *sensor)
अणु
	पूर्णांक ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_FORMAT2, BIT(2), BIT(0));
	अगर (ret < 0)
		वापस ret;

	वापस ov2680_bayer_order(sensor);
पूर्ण

अटल पूर्णांक ov2680_test_pattern_set(काष्ठा ov2680_dev *sensor, पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (!value)
		वापस ov2680_mod_reg(sensor, OV2680_REG_ISP_CTRL00, BIT(7), 0);

	ret = ov2680_mod_reg(sensor, OV2680_REG_ISP_CTRL00, 0x03, value - 1);
	अगर (ret < 0)
		वापस ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_ISP_CTRL00, BIT(7), BIT(7));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_gain_set(काष्ठा ov2680_dev *sensor, bool स्वतः_gain)
अणु
	काष्ठा ov2680_ctrls *ctrls = &sensor->ctrls;
	u32 gain;
	पूर्णांक ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_R_MANUAL, BIT(1),
			     स्वतः_gain ? 0 : BIT(1));
	अगर (ret < 0)
		वापस ret;

	अगर (स्वतः_gain || !ctrls->gain->is_new)
		वापस 0;

	gain = ctrls->gain->val;

	ret = ov2680_ग_लिखो_reg16(sensor, OV2680_REG_GAIN_PK, gain);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_gain_get(काष्ठा ov2680_dev *sensor)
अणु
	u32 gain;
	पूर्णांक ret;

	ret = ov2680_पढ़ो_reg16(sensor, OV2680_REG_GAIN_PK, &gain);
	अगर (ret)
		वापस ret;

	वापस gain;
पूर्ण

अटल पूर्णांक ov2680_exposure_set(काष्ठा ov2680_dev *sensor, bool स्वतः_exp)
अणु
	काष्ठा ov2680_ctrls *ctrls = &sensor->ctrls;
	u32 exp;
	पूर्णांक ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_R_MANUAL, BIT(0),
			     स्वतः_exp ? 0 : BIT(0));
	अगर (ret < 0)
		वापस ret;

	अगर (स्वतः_exp || !ctrls->exposure->is_new)
		वापस 0;

	exp = (u32)ctrls->exposure->val;
	exp <<= 4;

	वापस ov2680_ग_लिखो_reg24(sensor, OV2680_REG_EXPOSURE_PK_HIGH, exp);
पूर्ण

अटल पूर्णांक ov2680_exposure_get(काष्ठा ov2680_dev *sensor)
अणु
	पूर्णांक ret;
	u32 exp;

	ret = ov2680_पढ़ो_reg24(sensor, OV2680_REG_EXPOSURE_PK_HIGH, &exp);
	अगर (ret)
		वापस ret;

	वापस exp >> 4;
पूर्ण

अटल पूर्णांक ov2680_stream_enable(काष्ठा ov2680_dev *sensor)
अणु
	वापस ov2680_ग_लिखो_reg(sensor, OV2680_REG_STREAM_CTRL, 1);
पूर्ण

अटल पूर्णांक ov2680_stream_disable(काष्ठा ov2680_dev *sensor)
अणु
	वापस ov2680_ग_लिखो_reg(sensor, OV2680_REG_STREAM_CTRL, 0);
पूर्ण

अटल पूर्णांक ov2680_mode_set(काष्ठा ov2680_dev *sensor)
अणु
	काष्ठा ov2680_ctrls *ctrls = &sensor->ctrls;
	पूर्णांक ret;

	ret = ov2680_gain_set(sensor, false);
	अगर (ret < 0)
		वापस ret;

	ret = ov2680_exposure_set(sensor, false);
	अगर (ret < 0)
		वापस ret;

	ret = ov2680_load_regs(sensor, sensor->current_mode);
	अगर (ret < 0)
		वापस ret;

	अगर (ctrls->स्वतः_gain->val) अणु
		ret = ov2680_gain_set(sensor, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (ctrls->स्वतः_exp->val == V4L2_EXPOSURE_AUTO) अणु
		ret = ov2680_exposure_set(sensor, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	sensor->mode_pending_changes = false;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_mode_restore(काष्ठा ov2680_dev *sensor)
अणु
	पूर्णांक ret;

	ret = ov2680_load_regs(sensor, &ov2680_mode_init_data);
	अगर (ret < 0)
		वापस ret;

	वापस ov2680_mode_set(sensor);
पूर्ण

अटल पूर्णांक ov2680_घातer_off(काष्ठा ov2680_dev *sensor)
अणु
	अगर (!sensor->is_enabled)
		वापस 0;

	clk_disable_unprepare(sensor->xvclk);
	ov2680_घातer_करोwn(sensor);
	regulator_bulk_disable(OV2680_NUM_SUPPLIES, sensor->supplies);
	sensor->is_enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_घातer_on(काष्ठा ov2680_dev *sensor)
अणु
	काष्ठा device *dev = ov2680_to_dev(sensor);
	पूर्णांक ret;

	अगर (sensor->is_enabled)
		वापस 0;

	ret = regulator_bulk_enable(OV2680_NUM_SUPPLIES, sensor->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!sensor->reset_gpio) अणु
		ret = ov2680_ग_लिखो_reg(sensor, OV2680_REG_SOFT_RESET, 0x01);
		अगर (ret != 0) अणु
			dev_err(dev, "sensor soft reset failed\n");
			वापस ret;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण अन्यथा अणु
		ov2680_घातer_करोwn(sensor);
		ov2680_घातer_up(sensor);
	पूर्ण

	ret = clk_prepare_enable(sensor->xvclk);
	अगर (ret < 0)
		वापस ret;

	sensor->is_enabled = true;

	/* Set घड़ी lane पूर्णांकo LP-11 state */
	ov2680_stream_enable(sensor);
	usleep_range(1000, 2000);
	ov2680_stream_disable(sensor);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);
	पूर्णांक ret = 0;

	mutex_lock(&sensor->lock);

	अगर (on)
		ret = ov2680_घातer_on(sensor);
	अन्यथा
		ret = ov2680_घातer_off(sensor);

	mutex_unlock(&sensor->lock);

	अगर (on && ret == 0) अणु
		ret = v4l2_ctrl_handler_setup(&sensor->ctrls.handler);
		अगर (ret < 0)
			वापस ret;

		ret = ov2680_mode_restore(sensor);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_s_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);

	mutex_lock(&sensor->lock);
	fi->पूर्णांकerval = sensor->frame_पूर्णांकerval;
	mutex_unlock(&sensor->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);
	पूर्णांक ret = 0;

	mutex_lock(&sensor->lock);

	अगर (sensor->is_streaming == !!enable)
		जाओ unlock;

	अगर (enable && sensor->mode_pending_changes) अणु
		ret = ov2680_mode_set(sensor);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

	अगर (enable)
		ret = ov2680_stream_enable(sensor);
	अन्यथा
		ret = ov2680_stream_disable(sensor);

	sensor->is_streaming = !!enable;

unlock:
	mutex_unlock(&sensor->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);

	अगर (code->pad != 0 || code->index != 0)
		वापस -EINVAL;

	code->code = sensor->fmt.code;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);
	काष्ठा v4l2_mbus_framefmt *fmt = शून्य;
	पूर्णांक ret = 0;

	अगर (क्रमmat->pad != 0)
		वापस -EINVAL;

	mutex_lock(&sensor->lock);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		fmt = v4l2_subdev_get_try_क्रमmat(&sensor->sd, cfg, क्रमmat->pad);
#अन्यथा
		ret = -EINVAL;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		fmt = &sensor->fmt;
	पूर्ण

	अगर (fmt)
		क्रमmat->क्रमmat = *fmt;

	mutex_unlock(&sensor->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	काष्ठा v4l2_mbus_framefmt *try_fmt;
#पूर्ण_अगर
	स्थिर काष्ठा ov2680_mode_info *mode;
	पूर्णांक ret = 0;

	अगर (क्रमmat->pad != 0)
		वापस -EINVAL;

	mutex_lock(&sensor->lock);

	अगर (sensor->is_streaming) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	mode = v4l2_find_nearest_size(ov2680_mode_data,
				      ARRAY_SIZE(ov2680_mode_data), width,
				      height, fmt->width, fmt->height);
	अगर (!mode) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		try_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		क्रमmat->क्रमmat = *try_fmt;
#पूर्ण_अगर
		जाओ unlock;
	पूर्ण

	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = sensor->fmt.code;
	fmt->colorspace = sensor->fmt.colorspace;

	sensor->current_mode = mode;
	sensor->fmt = क्रमmat->क्रमmat;
	sensor->mode_pending_changes = true;

unlock:
	mutex_unlock(&sensor->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_init_cfg(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = cfg ? V4L2_SUBDEV_FORMAT_TRY
				: V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat = अणु
			.width = 800,
			.height = 600,
		पूर्ण
	पूर्ण;

	वापस ov2680_set_fmt(sd, cfg, &fmt);
पूर्ण

अटल पूर्णांक ov2680_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक index = fse->index;

	अगर (index >= OV2680_MODE_MAX || index < 0)
		वापस -EINVAL;

	fse->min_width = ov2680_mode_data[index].width;
	fse->min_height = ov2680_mode_data[index].height;
	fse->max_width = ov2680_mode_data[index].width;
	fse->max_height = ov2680_mode_data[index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा v4l2_fract tpf;

	अगर (fie->index >= OV2680_MODE_MAX || fie->width > OV2680_WIDTH_MAX ||
	    fie->height > OV2680_HEIGHT_MAX ||
	    fie->which > V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	tpf.denominator = OV2680_FRAME_RATE;
	tpf.numerator = 1;

	fie->पूर्णांकerval = tpf;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);
	काष्ठा ov2680_ctrls *ctrls = &sensor->ctrls;
	पूर्णांक val;

	अगर (!sensor->is_enabled)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		val = ov2680_gain_get(sensor);
		अगर (val < 0)
			वापस val;
		ctrls->gain->val = val;
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		val = ov2680_exposure_get(sensor);
		अगर (val < 0)
			वापस val;
		ctrls->exposure->val = val;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);
	काष्ठा ov2680_ctrls *ctrls = &sensor->ctrls;

	अगर (!sensor->is_enabled)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		वापस ov2680_gain_set(sensor, !!ctrl->val);
	हाल V4L2_CID_GAIN:
		वापस ov2680_gain_set(sensor, !!ctrls->स्वतः_gain->val);
	हाल V4L2_CID_EXPOSURE_AUTO:
		वापस ov2680_exposure_set(sensor, !!ctrl->val);
	हाल V4L2_CID_EXPOSURE:
		वापस ov2680_exposure_set(sensor, !!ctrls->स्वतः_exp->val);
	हाल V4L2_CID_VFLIP:
		अगर (sensor->is_streaming)
			वापस -EBUSY;
		अगर (ctrl->val)
			वापस ov2680_vflip_enable(sensor);
		अन्यथा
			वापस ov2680_vflip_disable(sensor);
	हाल V4L2_CID_HFLIP:
		अगर (sensor->is_streaming)
			वापस -EBUSY;
		अगर (ctrl->val)
			वापस ov2680_hflip_enable(sensor);
		अन्यथा
			वापस ov2680_hflip_disable(sensor);
	हाल V4L2_CID_TEST_PATTERN:
		वापस ov2680_test_pattern_set(sensor, ctrl->val);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov2680_ctrl_ops = अणु
	.g_अस्थिर_ctrl = ov2680_g_अस्थिर_ctrl,
	.s_ctrl = ov2680_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov2680_core_ops = अणु
	.s_घातer = ov2680_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov2680_video_ops = अणु
	.g_frame_पूर्णांकerval	= ov2680_s_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval	= ov2680_s_g_frame_पूर्णांकerval,
	.s_stream		= ov2680_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov2680_pad_ops = अणु
	.init_cfg		= ov2680_init_cfg,
	.क्रमागत_mbus_code		= ov2680_क्रमागत_mbus_code,
	.get_fmt		= ov2680_get_fmt,
	.set_fmt		= ov2680_set_fmt,
	.क्रमागत_frame_size	= ov2680_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= ov2680_क्रमागत_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov2680_subdev_ops = अणु
	.core	= &ov2680_core_ops,
	.video	= &ov2680_video_ops,
	.pad	= &ov2680_pad_ops,
पूर्ण;

अटल पूर्णांक ov2680_mode_init(काष्ठा ov2680_dev *sensor)
अणु
	स्थिर काष्ठा ov2680_mode_info *init_mode;

	/* set initial mode */
	sensor->fmt.code = MEDIA_BUS_FMT_SBGGR10_1X10;
	sensor->fmt.width = 800;
	sensor->fmt.height = 600;
	sensor->fmt.field = V4L2_FIELD_NONE;
	sensor->fmt.colorspace = V4L2_COLORSPACE_SRGB;

	sensor->frame_पूर्णांकerval.denominator = OV2680_FRAME_RATE;
	sensor->frame_पूर्णांकerval.numerator = 1;

	init_mode = &ov2680_mode_init_data;

	sensor->current_mode = init_mode;

	sensor->mode_pending_changes = true;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_v4l2_रेजिस्टर(काष्ठा ov2680_dev *sensor)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &ov2680_ctrl_ops;
	काष्ठा ov2680_ctrls *ctrls = &sensor->ctrls;
	काष्ठा v4l2_ctrl_handler *hdl = &ctrls->handler;
	पूर्णांक ret = 0;

	v4l2_i2c_subdev_init(&sensor->sd, sensor->i2c_client,
			     &ov2680_subdev_ops);

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	sensor->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
#पूर्ण_अगर
	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	sensor->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&sensor->sd.entity, 1, &sensor->pad);
	अगर (ret < 0)
		वापस ret;

	v4l2_ctrl_handler_init(hdl, 7);

	hdl->lock = &sensor->lock;

	ctrls->vflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_VFLIP, 0, 1, 1, 0);
	ctrls->hflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_HFLIP, 0, 1, 1, 0);

	ctrls->test_pattern = v4l2_ctrl_new_std_menu_items(hdl,
					&ov2680_ctrl_ops, V4L2_CID_TEST_PATTERN,
					ARRAY_SIZE(test_pattern_menu) - 1,
					0, 0, test_pattern_menu);

	ctrls->स्वतः_exp = v4l2_ctrl_new_std_menu(hdl, ops,
						 V4L2_CID_EXPOSURE_AUTO,
						 V4L2_EXPOSURE_MANUAL, 0,
						 V4L2_EXPOSURE_AUTO);

	ctrls->exposure = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_EXPOSURE,
					    0, 32767, 1, 0);

	ctrls->स्वतः_gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTOGAIN,
					     0, 1, 1, 1);
	ctrls->gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAIN, 0, 2047, 1, 0);

	अगर (hdl->error) अणु
		ret = hdl->error;
		जाओ cleanup_entity;
	पूर्ण

	ctrls->gain->flags |= V4L2_CTRL_FLAG_VOLATILE;
	ctrls->exposure->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_gain, 0, true);
	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_exp, 1, true);

	sensor->sd.ctrl_handler = hdl;

	ret = v4l2_async_रेजिस्टर_subdev(&sensor->sd);
	अगर (ret < 0)
		जाओ cleanup_entity;

	वापस 0;

cleanup_entity:
	media_entity_cleanup(&sensor->sd.entity);
	v4l2_ctrl_handler_मुक्त(hdl);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_get_regulators(काष्ठा ov2680_dev *sensor)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OV2680_NUM_SUPPLIES; i++)
		sensor->supplies[i].supply = ov2680_supply_name[i];

	वापस devm_regulator_bulk_get(&sensor->i2c_client->dev,
				       OV2680_NUM_SUPPLIES,
				       sensor->supplies);
पूर्ण

अटल पूर्णांक ov2680_check_id(काष्ठा ov2680_dev *sensor)
अणु
	काष्ठा device *dev = ov2680_to_dev(sensor);
	u32 chip_id;
	पूर्णांक ret;

	ov2680_घातer_on(sensor);

	ret = ov2680_पढ़ो_reg16(sensor, OV2680_REG_CHIP_ID_HIGH, &chip_id);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read chip id high\n");
		वापस -ENODEV;
	पूर्ण

	अगर (chip_id != OV2680_CHIP_ID) अणु
		dev_err(dev, "chip id: 0x%04x does not match expected 0x%04x\n",
			chip_id, OV2680_CHIP_ID);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_parse_dt(काष्ठा ov2680_dev *sensor)
अणु
	काष्ठा device *dev = ov2680_to_dev(sensor);
	पूर्णांक ret;

	sensor->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						     GPIOD_OUT_HIGH);
	ret = PTR_ERR_OR_ZERO(sensor->reset_gpio);
	अगर (ret < 0) अणु
		dev_dbg(dev, "error while getting reset gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	sensor->xvclk = devm_clk_get(dev, "xvclk");
	अगर (IS_ERR(sensor->xvclk)) अणु
		dev_err(dev, "xvclk clock missing or invalid\n");
		वापस PTR_ERR(sensor->xvclk);
	पूर्ण

	sensor->xvclk_freq = clk_get_rate(sensor->xvclk);
	अगर (sensor->xvclk_freq != OV2680_XVCLK_VALUE) अणु
		dev_err(dev, "wrong xvclk frequency %d HZ, expected: %d Hz\n",
			sensor->xvclk_freq, OV2680_XVCLK_VALUE);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov2680_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ov2680_dev *sensor;
	पूर्णांक ret;

	sensor = devm_kzalloc(dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	sensor->i2c_client = client;

	ret = ov2680_parse_dt(sensor);
	अगर (ret < 0)
		वापस -EINVAL;

	ret = ov2680_mode_init(sensor);
	अगर (ret < 0)
		वापस ret;

	ret = ov2680_get_regulators(sensor);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get regulators\n");
		वापस ret;
	पूर्ण

	mutex_init(&sensor->lock);

	ret = ov2680_check_id(sensor);
	अगर (ret < 0)
		जाओ lock_destroy;

	ret = ov2680_v4l2_रेजिस्टर(sensor);
	अगर (ret < 0)
		जाओ lock_destroy;

	dev_info(dev, "ov2680 init correctly\n");

	वापस 0;

lock_destroy:
	dev_err(dev, "ov2680 init fail: %d\n", ret);
	mutex_destroy(&sensor->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2680_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);

	v4l2_async_unरेजिस्टर_subdev(&sensor->sd);
	mutex_destroy(&sensor->lock);
	media_entity_cleanup(&sensor->sd.entity);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrls.handler);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov2680_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);

	अगर (sensor->is_streaming)
		ov2680_stream_disable(sensor);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov2680_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov2680_dev *sensor = to_ov2680_dev(sd);
	पूर्णांक ret;

	अगर (sensor->is_streaming) अणु
		ret = ov2680_stream_enable(sensor);
		अगर (ret < 0)
			जाओ stream_disable;
	पूर्ण

	वापस 0;

stream_disable:
	ov2680_stream_disable(sensor);
	sensor->is_streaming = false;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov2680_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ov2680_suspend, ov2680_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id ov2680_dt_ids[] = अणु
	अणु .compatible = "ovti,ov2680" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov2680_dt_ids);

अटल काष्ठा i2c_driver ov2680_i2c_driver = अणु
	.driver = अणु
		.name  = "ov2680",
		.pm = &ov2680_pm_ops,
		.of_match_table	= of_match_ptr(ov2680_dt_ids),
	पूर्ण,
	.probe_new	= ov2680_probe,
	.हटाओ		= ov2680_हटाओ,
पूर्ण;
module_i2c_driver(ov2680_i2c_driver);

MODULE_AUTHOR("Rui Miguel Silva <rui.silva@linaro.org>");
MODULE_DESCRIPTION("OV2680 CMOS Image Sensor driver");
MODULE_LICENSE("GPL v2");
