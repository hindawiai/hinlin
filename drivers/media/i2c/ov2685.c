<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ov2685 driver
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

#घोषणा CHIP_ID				0x2685
#घोषणा OV2685_REG_CHIP_ID		0x300a

#घोषणा OV2685_XVCLK_FREQ		24000000

#घोषणा REG_SC_CTRL_MODE		0x0100
#घोषणा     SC_CTRL_MODE_STANDBY	0x0
#घोषणा     SC_CTRL_MODE_STREAMING	BIT(0)

#घोषणा OV2685_REG_EXPOSURE		0x3500
#घोषणा	OV2685_EXPOSURE_MIN		4
#घोषणा	OV2685_EXPOSURE_STEP		1

#घोषणा OV2685_REG_VTS			0x380e
#घोषणा OV2685_VTS_MAX			0x7fff

#घोषणा OV2685_REG_GAIN			0x350a
#घोषणा OV2685_GAIN_MIN			0
#घोषणा OV2685_GAIN_MAX			0x07ff
#घोषणा OV2685_GAIN_STEP		0x1
#घोषणा OV2685_GAIN_DEFAULT		0x0036

#घोषणा OV2685_REG_TEST_PATTERN		0x5080
#घोषणा OV2685_TEST_PATTERN_DISABLED		0x00
#घोषणा OV2685_TEST_PATTERN_COLOR_BAR		0x80
#घोषणा OV2685_TEST_PATTERN_RANDOM		0x81
#घोषणा OV2685_TEST_PATTERN_COLOR_BAR_FADE	0x88
#घोषणा OV2685_TEST_PATTERN_BW_SQUARE		0x92
#घोषणा OV2685_TEST_PATTERN_COLOR_SQUARE	0x82

#घोषणा REG_शून्य			0xFFFF

#घोषणा OV2685_REG_VALUE_08BIT		1
#घोषणा OV2685_REG_VALUE_16BIT		2
#घोषणा OV2685_REG_VALUE_24BIT		3

#घोषणा OV2685_LANES			1
#घोषणा OV2685_BITS_PER_SAMPLE		10

अटल स्थिर अक्षर * स्थिर ov2685_supply_names[] = अणु
	"avdd",		/* Analog घातer */
	"dovdd",	/* Digital I/O घातer */
	"dvdd",		/* Digital core घातer */
पूर्ण;

#घोषणा OV2685_NUM_SUPPLIES ARRAY_SIZE(ov2685_supply_names)

काष्ठा regval अणु
	u16 addr;
	u8 val;
पूर्ण;

काष्ठा ov2685_mode अणु
	u32 width;
	u32 height;
	u32 exp_def;
	u32 hts_def;
	u32 vts_def;
	स्थिर काष्ठा regval *reg_list;
पूर्ण;

काष्ठा ov2685 अणु
	काष्ठा i2c_client	*client;
	काष्ठा clk		*xvclk;
	काष्ठा gpio_desc	*reset_gpio;
	काष्ठा regulator_bulk_data supplies[OV2685_NUM_SUPPLIES];

	bool			streaming;
	काष्ठा mutex		mutex;
	काष्ठा v4l2_subdev	subdev;
	काष्ठा media_pad	pad;
	काष्ठा v4l2_ctrl	*anal_gain;
	काष्ठा v4l2_ctrl	*exposure;
	काष्ठा v4l2_ctrl	*hblank;
	काष्ठा v4l2_ctrl	*vblank;
	काष्ठा v4l2_ctrl	*test_pattern;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	स्थिर काष्ठा ov2685_mode *cur_mode;
पूर्ण;

#घोषणा to_ov2685(sd) container_of(sd, काष्ठा ov2685, subdev)

/* PLL settings bases on 24M xvclk */
अटल काष्ठा regval ov2685_1600x1200_regs[] = अणु
	अणु0x0103, 0x01पूर्ण,
	अणु0x0100, 0x00पूर्ण,
	अणु0x3002, 0x00पूर्ण,
	अणु0x3016, 0x1cपूर्ण,
	अणु0x3018, 0x44पूर्ण,
	अणु0x301d, 0xf0पूर्ण,
	अणु0x3020, 0x00पूर्ण,
	अणु0x3082, 0x37पूर्ण,
	अणु0x3083, 0x03पूर्ण,
	अणु0x3084, 0x09पूर्ण,
	अणु0x3085, 0x04पूर्ण,
	अणु0x3086, 0x00पूर्ण,
	अणु0x3087, 0x00पूर्ण,
	अणु0x3501, 0x4eपूर्ण,
	अणु0x3502, 0xe0पूर्ण,
	अणु0x3503, 0x27पूर्ण,
	अणु0x350b, 0x36पूर्ण,
	अणु0x3600, 0xb4पूर्ण,
	अणु0x3603, 0x35पूर्ण,
	अणु0x3604, 0x24पूर्ण,
	अणु0x3605, 0x00पूर्ण,
	अणु0x3620, 0x24पूर्ण,
	अणु0x3621, 0x34पूर्ण,
	अणु0x3622, 0x03पूर्ण,
	अणु0x3628, 0x10पूर्ण,
	अणु0x3705, 0x3cपूर्ण,
	अणु0x370a, 0x21पूर्ण,
	अणु0x370c, 0x50पूर्ण,
	अणु0x370d, 0xc0पूर्ण,
	अणु0x3717, 0x58पूर्ण,
	अणु0x3718, 0x80पूर्ण,
	अणु0x3720, 0x00पूर्ण,
	अणु0x3721, 0x09पूर्ण,
	अणु0x3722, 0x06पूर्ण,
	अणु0x3723, 0x59पूर्ण,
	अणु0x3738, 0x99पूर्ण,
	अणु0x3781, 0x80पूर्ण,
	अणु0x3784, 0x0cपूर्ण,
	अणु0x3789, 0x60पूर्ण,
	अणु0x3800, 0x00पूर्ण,
	अणु0x3801, 0x00पूर्ण,
	अणु0x3802, 0x00पूर्ण,
	अणु0x3803, 0x00पूर्ण,
	अणु0x3804, 0x06पूर्ण,
	अणु0x3805, 0x4fपूर्ण,
	अणु0x3806, 0x04पूर्ण,
	अणु0x3807, 0xbfपूर्ण,
	अणु0x3808, 0x06पूर्ण,
	अणु0x3809, 0x40पूर्ण,
	अणु0x380a, 0x04पूर्ण,
	अणु0x380b, 0xb0पूर्ण,
	अणु0x380c, 0x06पूर्ण,
	अणु0x380d, 0xa4पूर्ण,
	अणु0x380e, 0x05पूर्ण,
	अणु0x380f, 0x0eपूर्ण,
	अणु0x3810, 0x00पूर्ण,
	अणु0x3811, 0x08पूर्ण,
	अणु0x3812, 0x00पूर्ण,
	अणु0x3813, 0x08पूर्ण,
	अणु0x3814, 0x11पूर्ण,
	अणु0x3815, 0x11पूर्ण,
	अणु0x3819, 0x04पूर्ण,
	अणु0x3820, 0xc0पूर्ण,
	अणु0x3821, 0x00पूर्ण,
	अणु0x3a06, 0x01पूर्ण,
	अणु0x3a07, 0x84पूर्ण,
	अणु0x3a08, 0x01पूर्ण,
	अणु0x3a09, 0x43पूर्ण,
	अणु0x3a0a, 0x24पूर्ण,
	अणु0x3a0b, 0x60पूर्ण,
	अणु0x3a0c, 0x28पूर्ण,
	अणु0x3a0d, 0x60पूर्ण,
	अणु0x3a0e, 0x04पूर्ण,
	अणु0x3a0f, 0x8cपूर्ण,
	अणु0x3a10, 0x05पूर्ण,
	अणु0x3a11, 0x0cपूर्ण,
	अणु0x4000, 0x81पूर्ण,
	अणु0x4001, 0x40पूर्ण,
	अणु0x4008, 0x02पूर्ण,
	अणु0x4009, 0x09पूर्ण,
	अणु0x4300, 0x00पूर्ण,
	अणु0x430e, 0x00पूर्ण,
	अणु0x4602, 0x02पूर्ण,
	अणु0x481b, 0x40पूर्ण,
	अणु0x481f, 0x40पूर्ण,
	अणु0x4837, 0x18पूर्ण,
	अणु0x5000, 0x1fपूर्ण,
	अणु0x5001, 0x05पूर्ण,
	अणु0x5002, 0x30पूर्ण,
	अणु0x5003, 0x04पूर्ण,
	अणु0x5004, 0x00पूर्ण,
	अणु0x5005, 0x0cपूर्ण,
	अणु0x5280, 0x15पूर्ण,
	अणु0x5281, 0x06पूर्ण,
	अणु0x5282, 0x06पूर्ण,
	अणु0x5283, 0x08पूर्ण,
	अणु0x5284, 0x1cपूर्ण,
	अणु0x5285, 0x1cपूर्ण,
	अणु0x5286, 0x20पूर्ण,
	अणु0x5287, 0x10पूर्ण,
	अणुREG_शून्य, 0x00पूर्ण
पूर्ण;

#घोषणा OV2685_LINK_FREQ_330MHZ		330000000
अटल स्थिर s64 link_freq_menu_items[] = अणु
	OV2685_LINK_FREQ_330MHZ
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov2685_test_pattern_menu[] = अणु
	"Disabled",
	"Color Bar",
	"Color Bar FADE",
	"Random Data",
	"Black White Square",
	"Color Square"
पूर्ण;

अटल स्थिर पूर्णांक ov2685_test_pattern_val[] = अणु
	OV2685_TEST_PATTERN_DISABLED,
	OV2685_TEST_PATTERN_COLOR_BAR,
	OV2685_TEST_PATTERN_COLOR_BAR_FADE,
	OV2685_TEST_PATTERN_RANDOM,
	OV2685_TEST_PATTERN_BW_SQUARE,
	OV2685_TEST_PATTERN_COLOR_SQUARE,
पूर्ण;

अटल स्थिर काष्ठा ov2685_mode supported_modes[] = अणु
	अणु
		.width = 1600,
		.height = 1200,
		.exp_def = 0x04ee,
		.hts_def = 0x06a4,
		.vts_def = 0x050e,
		.reg_list = ov2685_1600x1200_regs,
	पूर्ण,
पूर्ण;

/* Write रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक ov2685_ग_लिखो_reg(काष्ठा i2c_client *client, u16 reg,
			    u32 len, u32 val)
अणु
	u32 val_i, buf_i;
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

अटल पूर्णांक ov2685_ग_लिखो_array(काष्ठा i2c_client *client,
			      स्थिर काष्ठा regval *regs)
अणु
	पूर्णांक ret = 0;
	u32 i;

	क्रम (i = 0; ret == 0 && regs[i].addr != REG_शून्य; i++)
		ret = ov2685_ग_लिखो_reg(client, regs[i].addr,
				       OV2685_REG_VALUE_08BIT, regs[i].val);

	वापस ret;
पूर्ण

/* Read रेजिस्टरs up to 4 at a समय */
अटल पूर्णांक ov2685_पढ़ो_reg(काष्ठा i2c_client *client, u16 reg,
			   u32 len, u32 *val)
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

अटल व्योम ov2685_fill_fmt(स्थिर काष्ठा ov2685_mode *mode,
			    काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->code = MEDIA_BUS_FMT_SBGGR10_1X10;
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov2685_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov2685 *ov2685 = to_ov2685(sd);
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &fmt->क्रमmat;

	/* only one mode supported क्रम now */
	ov2685_fill_fmt(ov2685->cur_mode, mbus_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2685_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov2685 *ov2685 = to_ov2685(sd);
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &fmt->क्रमmat;

	ov2685_fill_fmt(ov2685->cur_mode, mbus_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2685_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक ov2685_क्रमागत_frame_sizes(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक index = fse->index;

	अगर (index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	fse->code = MEDIA_BUS_FMT_SBGGR10_1X10;

	fse->min_width  = supported_modes[index].width;
	fse->max_width  = supported_modes[index].width;
	fse->max_height = supported_modes[index].height;
	fse->min_height = supported_modes[index].height;

	वापस 0;
पूर्ण

/* Calculate the delay in us by घड़ी rate and घड़ी cycles */
अटल अंतरभूत u32 ov2685_cal_delay(u32 cycles)
अणु
	वापस DIV_ROUND_UP(cycles, OV2685_XVCLK_FREQ / 1000 / 1000);
पूर्ण

अटल पूर्णांक __ov2685_घातer_on(काष्ठा ov2685 *ov2685)
अणु
	पूर्णांक ret;
	u32 delay_us;
	काष्ठा device *dev = &ov2685->client->dev;

	ret = clk_prepare_enable(ov2685->xvclk);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable xvclk\n");
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(ov2685->reset_gpio, 1);

	ret = regulator_bulk_enable(OV2685_NUM_SUPPLIES, ov2685->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable regulators\n");
		जाओ disable_clk;
	पूर्ण

	/* The minimum delay between घातer supplies and reset rising can be 0 */
	gpiod_set_value_cansleep(ov2685->reset_gpio, 0);
	/* 8192 xvclk cycles prior to the first SCCB transaction */
	delay_us = ov2685_cal_delay(8192);
	usleep_range(delay_us, delay_us * 2);

	/* HACK: ov2685 would output messy data after reset(R0103),
	 * writing रेजिस्टर beक्रमe .s_stream() as a workaround
	 */
	ret = ov2685_ग_लिखो_array(ov2685->client, ov2685->cur_mode->reg_list);
	अगर (ret)
		जाओ disable_supplies;

	वापस 0;

disable_supplies:
	regulator_bulk_disable(OV2685_NUM_SUPPLIES, ov2685->supplies);
disable_clk:
	clk_disable_unprepare(ov2685->xvclk);

	वापस ret;
पूर्ण

अटल व्योम __ov2685_घातer_off(काष्ठा ov2685 *ov2685)
अणु
	/* 512 xvclk cycles after the last SCCB transaction or MIPI frame end */
	u32 delay_us = ov2685_cal_delay(512);

	usleep_range(delay_us, delay_us * 2);
	clk_disable_unprepare(ov2685->xvclk);
	gpiod_set_value_cansleep(ov2685->reset_gpio, 1);
	regulator_bulk_disable(OV2685_NUM_SUPPLIES, ov2685->supplies);
पूर्ण

अटल पूर्णांक ov2685_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov2685 *ov2685 = to_ov2685(sd);
	काष्ठा i2c_client *client = ov2685->client;
	पूर्णांक ret = 0;

	mutex_lock(&ov2685->mutex);

	on = !!on;
	अगर (on == ov2685->streaming)
		जाओ unlock_and_वापस;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&ov2685->client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			जाओ unlock_and_वापस;
		पूर्ण
		ret = __v4l2_ctrl_handler_setup(&ov2685->ctrl_handler);
		अगर (ret) अणु
			pm_runसमय_put(&client->dev);
			जाओ unlock_and_वापस;
		पूर्ण
		ret = ov2685_ग_लिखो_reg(client, REG_SC_CTRL_MODE,
				OV2685_REG_VALUE_08BIT, SC_CTRL_MODE_STREAMING);
		अगर (ret) अणु
			pm_runसमय_put(&client->dev);
			जाओ unlock_and_वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		ov2685_ग_लिखो_reg(client, REG_SC_CTRL_MODE,
				OV2685_REG_VALUE_08BIT, SC_CTRL_MODE_STANDBY);
		pm_runसमय_put(&ov2685->client->dev);
	पूर्ण

	ov2685->streaming = on;

unlock_and_वापस:
	mutex_unlock(&ov2685->mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल पूर्णांक ov2685_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov2685 *ov2685 = to_ov2685(sd);
	काष्ठा v4l2_mbus_framefmt *try_fmt;

	mutex_lock(&ov2685->mutex);

	try_fmt = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);
	/* Initialize try_fmt */
	ov2685_fill_fmt(&supported_modes[0], try_fmt);

	mutex_unlock(&ov2685->mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __maybe_unused ov2685_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov2685 *ov2685 = to_ov2685(sd);

	वापस __ov2685_घातer_on(ov2685);
पूर्ण

अटल पूर्णांक __maybe_unused ov2685_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov2685 *ov2685 = to_ov2685(sd);

	__ov2685_घातer_off(ov2685);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov2685_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ov2685_runसमय_suspend,
			   ov2685_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक ov2685_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov2685 *ov2685 = container_of(ctrl->handler,
					     काष्ठा ov2685, ctrl_handler);
	काष्ठा i2c_client *client = ov2685->client;
	s64 max_expo;
	पूर्णांक ret;

	/* Propagate change of current control to all related controls */
	चयन (ctrl->id) अणु
	हाल V4L2_CID_VBLANK:
		/* Update max exposure जबतक meeting expected vblanking */
		max_expo = ov2685->cur_mode->height + ctrl->val - 4;
		__v4l2_ctrl_modअगरy_range(ov2685->exposure,
					 ov2685->exposure->minimum, max_expo,
					 ov2685->exposure->step,
					 ov2685->exposure->शेष_value);
		अवरोध;
	पूर्ण

	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		ret = ov2685_ग_लिखो_reg(ov2685->client, OV2685_REG_EXPOSURE,
				       OV2685_REG_VALUE_24BIT, ctrl->val << 4);
		अवरोध;
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov2685_ग_लिखो_reg(ov2685->client, OV2685_REG_GAIN,
				       OV2685_REG_VALUE_16BIT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		ret = ov2685_ग_लिखो_reg(ov2685->client, OV2685_REG_VTS,
				       OV2685_REG_VALUE_16BIT,
				       ctrl->val + ov2685->cur_mode->height);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = ov2685_ग_लिखो_reg(ov2685->client, OV2685_REG_TEST_PATTERN,
				       OV2685_REG_VALUE_08BIT,
				       ov2685_test_pattern_val[ctrl->val]);
		अवरोध;
	शेष:
		dev_warn(&client->dev, "%s Unhandled id:0x%x, val:0x%x\n",
			 __func__, ctrl->id, ctrl->val);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov2685_video_ops = अणु
	.s_stream = ov2685_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov2685_pad_ops = अणु
	.क्रमागत_mbus_code = ov2685_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov2685_क्रमागत_frame_sizes,
	.get_fmt = ov2685_get_fmt,
	.set_fmt = ov2685_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov2685_subdev_ops = अणु
	.video	= &ov2685_video_ops,
	.pad	= &ov2685_pad_ops,
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov2685_पूर्णांकernal_ops = अणु
	.खोलो = ov2685_खोलो,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ctrl_ops ov2685_ctrl_ops = अणु
	.s_ctrl = ov2685_set_ctrl,
पूर्ण;

अटल पूर्णांक ov2685_initialize_controls(काष्ठा ov2685 *ov2685)
अणु
	स्थिर काष्ठा ov2685_mode *mode;
	काष्ठा v4l2_ctrl_handler *handler;
	काष्ठा v4l2_ctrl *ctrl;
	u64 exposure_max;
	u32 pixel_rate, h_blank;
	पूर्णांक ret;

	handler = &ov2685->ctrl_handler;
	mode = ov2685->cur_mode;
	ret = v4l2_ctrl_handler_init(handler, 8);
	अगर (ret)
		वापस ret;
	handler->lock = &ov2685->mutex;

	ctrl = v4l2_ctrl_new_पूर्णांक_menu(handler, शून्य, V4L2_CID_LINK_FREQ,
				      0, 0, link_freq_menu_items);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	pixel_rate = (link_freq_menu_items[0] * 2 * OV2685_LANES) /
		     OV2685_BITS_PER_SAMPLE;
	v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_PIXEL_RATE,
			  0, pixel_rate, 1, pixel_rate);

	h_blank = mode->hts_def - mode->width;
	ov2685->hblank = v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_HBLANK,
				h_blank, h_blank, 1, h_blank);
	अगर (ov2685->hblank)
		ov2685->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ov2685->vblank = v4l2_ctrl_new_std(handler, &ov2685_ctrl_ops,
				V4L2_CID_VBLANK, mode->vts_def - mode->height,
				OV2685_VTS_MAX - mode->height, 1,
				mode->vts_def - mode->height);

	exposure_max = mode->vts_def - 4;
	ov2685->exposure = v4l2_ctrl_new_std(handler, &ov2685_ctrl_ops,
				V4L2_CID_EXPOSURE, OV2685_EXPOSURE_MIN,
				exposure_max, OV2685_EXPOSURE_STEP,
				mode->exp_def);

	ov2685->anal_gain = v4l2_ctrl_new_std(handler, &ov2685_ctrl_ops,
				V4L2_CID_ANALOGUE_GAIN, OV2685_GAIN_MIN,
				OV2685_GAIN_MAX, OV2685_GAIN_STEP,
				OV2685_GAIN_DEFAULT);

	ov2685->test_pattern = v4l2_ctrl_new_std_menu_items(handler,
				&ov2685_ctrl_ops, V4L2_CID_TEST_PATTERN,
				ARRAY_SIZE(ov2685_test_pattern_menu) - 1,
				0, 0, ov2685_test_pattern_menu);

	अगर (handler->error) अणु
		ret = handler->error;
		dev_err(&ov2685->client->dev,
			"Failed to init controls(%d)\n", ret);
		जाओ err_मुक्त_handler;
	पूर्ण

	ov2685->subdev.ctrl_handler = handler;

	वापस 0;

err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(handler);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2685_check_sensor_id(काष्ठा ov2685 *ov2685,
				  काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &ov2685->client->dev;
	पूर्णांक ret;
	u32 id = 0;

	ret = ov2685_पढ़ो_reg(client, OV2685_REG_CHIP_ID,
			      OV2685_REG_VALUE_16BIT, &id);
	अगर (id != CHIP_ID) अणु
		dev_err(dev, "Unexpected sensor id(%04x), ret(%d)\n", id, ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "Detected OV%04x sensor\n", CHIP_ID);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2685_configure_regulators(काष्ठा ov2685 *ov2685)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OV2685_NUM_SUPPLIES; i++)
		ov2685->supplies[i].supply = ov2685_supply_names[i];

	वापस devm_regulator_bulk_get(&ov2685->client->dev,
				       OV2685_NUM_SUPPLIES,
				       ov2685->supplies);
पूर्ण

अटल पूर्णांक ov2685_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ov2685 *ov2685;
	पूर्णांक ret;

	ov2685 = devm_kzalloc(dev, माप(*ov2685), GFP_KERNEL);
	अगर (!ov2685)
		वापस -ENOMEM;

	ov2685->client = client;
	ov2685->cur_mode = &supported_modes[0];

	ov2685->xvclk = devm_clk_get(dev, "xvclk");
	अगर (IS_ERR(ov2685->xvclk)) अणु
		dev_err(dev, "Failed to get xvclk\n");
		वापस -EINVAL;
	पूर्ण
	ret = clk_set_rate(ov2685->xvclk, OV2685_XVCLK_FREQ);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set xvclk rate (24MHz)\n");
		वापस ret;
	पूर्ण
	अगर (clk_get_rate(ov2685->xvclk) != OV2685_XVCLK_FREQ)
		dev_warn(dev, "xvclk mismatched, modes are based on 24MHz\n");

	ov2685->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ov2685->reset_gpio)) अणु
		dev_err(dev, "Failed to get reset-gpios\n");
		वापस -EINVAL;
	पूर्ण

	ret = ov2685_configure_regulators(ov2685);
	अगर (ret) अणु
		dev_err(dev, "Failed to get power regulators\n");
		वापस ret;
	पूर्ण

	mutex_init(&ov2685->mutex);
	v4l2_i2c_subdev_init(&ov2685->subdev, client, &ov2685_subdev_ops);
	ret = ov2685_initialize_controls(ov2685);
	अगर (ret)
		जाओ err_destroy_mutex;

	ret = __ov2685_घातer_on(ov2685);
	अगर (ret)
		जाओ err_मुक्त_handler;

	ret = ov2685_check_sensor_id(ov2685, client);
	अगर (ret)
		जाओ err_घातer_off;

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	ov2685->subdev.पूर्णांकernal_ops = &ov2685_पूर्णांकernal_ops;
	ov2685->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
#पूर्ण_अगर
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	ov2685->pad.flags = MEDIA_PAD_FL_SOURCE;
	ov2685->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&ov2685->subdev.entity, 1, &ov2685->pad);
	अगर (ret < 0)
		जाओ err_घातer_off;
#पूर्ण_अगर

	ret = v4l2_async_रेजिस्टर_subdev(&ov2685->subdev);
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
	media_entity_cleanup(&ov2685->subdev.entity);
#पूर्ण_अगर
err_घातer_off:
	__ov2685_घातer_off(ov2685);
err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(&ov2685->ctrl_handler);
err_destroy_mutex:
	mutex_destroy(&ov2685->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov2685_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov2685 *ov2685 = to_ov2685(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&sd->entity);
#पूर्ण_अगर
	v4l2_ctrl_handler_मुक्त(&ov2685->ctrl_handler);
	mutex_destroy(&ov2685->mutex);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		__ov2685_घातer_off(ov2685);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ov2685_of_match[] = अणु
	अणु .compatible = "ovti,ov2685" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov2685_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov2685_i2c_driver = अणु
	.driver = अणु
		.name = "ov2685",
		.pm = &ov2685_pm_ops,
		.of_match_table = of_match_ptr(ov2685_of_match),
	पूर्ण,
	.probe		= &ov2685_probe,
	.हटाओ		= &ov2685_हटाओ,
पूर्ण;

module_i2c_driver(ov2685_i2c_driver);

MODULE_DESCRIPTION("OmniVision ov2685 sensor driver");
MODULE_LICENSE("GPL v2");
