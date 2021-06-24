<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 MediaTek Inc.

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा OV02A10_ID					0x2509
#घोषणा OV02A10_ID_MASK					GENMASK(15, 0)

#घोषणा OV02A10_REG_CHIP_ID				0x02

/* Bit[1] vertical upside करोwn */
/* Bit[0] horizontal mirror */
#घोषणा REG_MIRROR_FLIP_CONTROL				0x3f

/* Orientation */
#घोषणा REG_MIRROR_FLIP_ENABLE				0x03

/* Bit[2:0] MIPI transmission speed select */
#घोषणा TX_SPEED_AREA_SEL				0xa1
#घोषणा OV02A10_MIPI_TX_SPEED_DEFAULT			0x04

#घोषणा REG_PAGE_SWITCH					0xfd
#घोषणा REG_GLOBAL_EFFECTIVE				0x01
#घोषणा REG_ENABLE					BIT(0)

#घोषणा REG_SC_CTRL_MODE				0xac
#घोषणा SC_CTRL_MODE_STANDBY				0x00
#घोषणा SC_CTRL_MODE_STREAMING				0x01

/* Exposure control */
#घोषणा OV02A10_EXP_SHIFT				8
#घोषणा OV02A10_REG_EXPOSURE_H				0x03
#घोषणा OV02A10_REG_EXPOSURE_L				0x04
#घोषणा	OV02A10_EXPOSURE_MIN				4
#घोषणा OV02A10_EXPOSURE_MAX_MARGIN			4
#घोषणा	OV02A10_EXPOSURE_STEP				1

/* Vblanking control */
#घोषणा OV02A10_VTS_SHIFT				8
#घोषणा OV02A10_REG_VTS_H				0x05
#घोषणा OV02A10_REG_VTS_L				0x06
#घोषणा OV02A10_VTS_MAX					0x209f
#घोषणा OV02A10_BASE_LINES				1224

/* Analog gain control */
#घोषणा OV02A10_REG_GAIN				0x24
#घोषणा OV02A10_GAIN_MIN				0x10
#घोषणा OV02A10_GAIN_MAX				0xf8
#घोषणा OV02A10_GAIN_STEP				0x01
#घोषणा OV02A10_GAIN_DEFAULT				0x40

/* Test pattern control */
#घोषणा OV02A10_REG_TEST_PATTERN			0xb6

#घोषणा HZ_PER_MHZ					1000000L
#घोषणा OV02A10_LINK_FREQ_390MHZ			(390 * HZ_PER_MHZ)
#घोषणा OV02A10_ECLK_FREQ				(24 * HZ_PER_MHZ)

/* Number of lanes supported by this driver */
#घोषणा OV02A10_DATA_LANES				1

/* Bits per sample of sensor output */
#घोषणा OV02A10_BITS_PER_SAMPLE				10

अटल स्थिर अक्षर * स्थिर ov02a10_supply_names[] = अणु
	"dovdd",	/* Digital I/O घातer */
	"avdd",		/* Analog घातer */
	"dvdd",		/* Digital core घातer */
पूर्ण;

काष्ठा ov02a10_reg अणु
	u8 addr;
	u8 val;
पूर्ण;

काष्ठा ov02a10_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा ov02a10_reg *regs;
पूर्ण;

काष्ठा ov02a10_mode अणु
	u32 width;
	u32 height;
	u32 exp_def;
	u32 hts_def;
	u32 vts_def;
	स्थिर काष्ठा ov02a10_reg_list reg_list;
पूर्ण;

काष्ठा ov02a10 अणु
	u32 eclk_freq;
	/* Indication of MIPI transmission speed select */
	u32 mipi_घड़ी_voltage;

	काष्ठा clk *eclk;
	काष्ठा gpio_desc *pd_gpio;
	काष्ठा gpio_desc *rst_gpio;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(ov02a10_supply_names)];

	bool streaming;
	bool upside_करोwn;

	/*
	 * Serialize control access, get/set क्रमmat, get selection
	 * and start streaming.
	 */
	काष्ठा mutex mutex;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt fmt;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *exposure;

	स्थिर काष्ठा ov02a10_mode *cur_mode;
पूर्ण;

अटल अंतरभूत काष्ठा ov02a10 *to_ov02a10(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov02a10, subdev);
पूर्ण

/*
 * eclk 24Mhz
 * pclk 39Mhz
 * linelength 934(0x3a6)
 * framelength 1390(0x56E)
 * grabwinकरोw_width 1600
 * grabwinकरोw_height 1200
 * max_framerate 30fps
 * mipi_datarate per lane 780Mbps
 */
अटल स्थिर काष्ठा ov02a10_reg ov02a10_1600x1200_regs[] = अणु
	अणु0xfd, 0x01पूर्ण,
	अणु0xac, 0x00पूर्ण,
	अणु0xfd, 0x00पूर्ण,
	अणु0x2f, 0x29पूर्ण,
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x21पूर्ण,
	अणु0x30, 0x15पूर्ण,
	अणु0x33, 0x01पूर्ण,
	अणु0xfd, 0x01पूर्ण,
	अणु0x44, 0x00पूर्ण,
	अणु0x2a, 0x4cपूर्ण,
	अणु0x2b, 0x1eपूर्ण,
	अणु0x2c, 0x60पूर्ण,
	अणु0x25, 0x11पूर्ण,
	अणु0x03, 0x01पूर्ण,
	अणु0x04, 0xaeपूर्ण,
	अणु0x09, 0x00पूर्ण,
	अणु0x0a, 0x02पूर्ण,
	अणु0x06, 0xa6पूर्ण,
	अणु0x31, 0x00पूर्ण,
	अणु0x24, 0x40पूर्ण,
	अणु0x01, 0x01पूर्ण,
	अणु0xfb, 0x73पूर्ण,
	अणु0xfd, 0x01पूर्ण,
	अणु0x16, 0x04पूर्ण,
	अणु0x1c, 0x09पूर्ण,
	अणु0x21, 0x42पूर्ण,
	अणु0x12, 0x04पूर्ण,
	अणु0x13, 0x10पूर्ण,
	अणु0x11, 0x40पूर्ण,
	अणु0x33, 0x81पूर्ण,
	अणु0xd0, 0x00पूर्ण,
	अणु0xd1, 0x01पूर्ण,
	अणु0xd2, 0x00पूर्ण,
	अणु0x50, 0x10पूर्ण,
	अणु0x51, 0x23पूर्ण,
	अणु0x52, 0x20पूर्ण,
	अणु0x53, 0x10पूर्ण,
	अणु0x54, 0x02पूर्ण,
	अणु0x55, 0x20पूर्ण,
	अणु0x56, 0x02पूर्ण,
	अणु0x58, 0x48पूर्ण,
	अणु0x5d, 0x15पूर्ण,
	अणु0x5e, 0x05पूर्ण,
	अणु0x66, 0x66पूर्ण,
	अणु0x68, 0x68पूर्ण,
	अणु0x6b, 0x00पूर्ण,
	अणु0x6c, 0x00पूर्ण,
	अणु0x6f, 0x40पूर्ण,
	अणु0x70, 0x40पूर्ण,
	अणु0x71, 0x0aपूर्ण,
	अणु0x72, 0xf0पूर्ण,
	अणु0x73, 0x10पूर्ण,
	अणु0x75, 0x80पूर्ण,
	अणु0x76, 0x10पूर्ण,
	अणु0x84, 0x00पूर्ण,
	अणु0x85, 0x10पूर्ण,
	अणु0x86, 0x10पूर्ण,
	अणु0x87, 0x00पूर्ण,
	अणु0x8a, 0x22पूर्ण,
	अणु0x8b, 0x22पूर्ण,
	अणु0x19, 0xf1पूर्ण,
	अणु0x29, 0x01पूर्ण,
	अणु0xfd, 0x01पूर्ण,
	अणु0x9d, 0x16पूर्ण,
	अणु0xa0, 0x29पूर्ण,
	अणु0xa1, 0x04पूर्ण,
	अणु0xad, 0x62पूर्ण,
	अणु0xae, 0x00पूर्ण,
	अणु0xaf, 0x85पूर्ण,
	अणु0xb1, 0x01पूर्ण,
	अणु0x8e, 0x06पूर्ण,
	अणु0x8f, 0x40पूर्ण,
	अणु0x90, 0x04पूर्ण,
	अणु0x91, 0xb0पूर्ण,
	अणु0x45, 0x01पूर्ण,
	अणु0x46, 0x00पूर्ण,
	अणु0x47, 0x6cपूर्ण,
	अणु0x48, 0x03पूर्ण,
	अणु0x49, 0x8bपूर्ण,
	अणु0x4a, 0x00पूर्ण,
	अणु0x4b, 0x07पूर्ण,
	अणु0x4c, 0x04पूर्ण,
	अणु0x4d, 0xb7पूर्ण,
	अणु0xf0, 0x40पूर्ण,
	अणु0xf1, 0x40पूर्ण,
	अणु0xf2, 0x40पूर्ण,
	अणु0xf3, 0x40पूर्ण,
	अणु0x3f, 0x00पूर्ण,
	अणु0xfd, 0x01पूर्ण,
	अणु0x05, 0x00पूर्ण,
	अणु0x06, 0xa6पूर्ण,
	अणु0xfd, 0x01पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ov02a10_test_pattern_menu[] = अणु
	"Disabled",
	"Eight Vertical Colour Bars",
पूर्ण;

अटल स्थिर s64 link_freq_menu_items[] = अणु
	OV02A10_LINK_FREQ_390MHZ,
पूर्ण;

अटल u64 to_pixel_rate(u32 f_index)
अणु
	u64 pixel_rate = link_freq_menu_items[f_index] * 2 * OV02A10_DATA_LANES;

	करो_भाग(pixel_rate, OV02A10_BITS_PER_SAMPLE);

	वापस pixel_rate;
पूर्ण

अटल स्थिर काष्ठा ov02a10_mode supported_modes[] = अणु
	अणु
		.width = 1600,
		.height = 1200,
		.exp_def = 0x01ae,
		.hts_def = 0x03a6,
		.vts_def = 0x056e,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(ov02a10_1600x1200_regs),
			.regs = ov02a10_1600x1200_regs,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ov02a10_ग_लिखो_array(काष्ठा ov02a10 *ov02a10,
			       स्थिर काष्ठा ov02a10_reg_list *r_list)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < r_list->num_of_regs; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, r_list->regs[i].addr,
						r_list->regs[i].val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ov02a10_fill_fmt(स्थिर काष्ठा ov02a10_mode *mode,
			     काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक ov02a10_set_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov02a10 *ov02a10 = to_ov02a10(sd);
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &fmt->क्रमmat;
	काष्ठा v4l2_mbus_framefmt *frame_fmt;
	पूर्णांक ret = 0;

	mutex_lock(&ov02a10->mutex);

	अगर (ov02a10->streaming && fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/* Only one sensor mode supported */
	mbus_fmt->code = ov02a10->fmt.code;
	ov02a10_fill_fmt(ov02a10->cur_mode, mbus_fmt);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		frame_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	अन्यथा
		frame_fmt = &ov02a10->fmt;

	*frame_fmt = *mbus_fmt;

out_unlock:
	mutex_unlock(&ov02a10->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ov02a10_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा ov02a10 *ov02a10 = to_ov02a10(sd);
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &fmt->क्रमmat;

	mutex_lock(&ov02a10->mutex);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
	पूर्ण अन्यथा अणु
		fmt->क्रमmat = ov02a10->fmt;
		mbus_fmt->code = ov02a10->fmt.code;
		ov02a10_fill_fmt(ov02a10->cur_mode, mbus_fmt);
	पूर्ण

	mutex_unlock(&ov02a10->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ov02a10_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा ov02a10 *ov02a10 = to_ov02a10(sd);

	अगर (code->index != 0)
		वापस -EINVAL;

	code->code = ov02a10->fmt.code;

	वापस 0;
पूर्ण

अटल पूर्णांक ov02a10_क्रमागत_frame_sizes(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	fse->min_width  = supported_modes[fse->index].width;
	fse->max_width  = supported_modes[fse->index].width;
	fse->max_height = supported_modes[fse->index].height;
	fse->min_height = supported_modes[fse->index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक ov02a10_check_sensor_id(काष्ठा ov02a10 *ov02a10)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	u16 chip_id;
	पूर्णांक ret;

	/* Validate the chip ID */
	ret = i2c_smbus_पढ़ो_word_swapped(client, OV02A10_REG_CHIP_ID);
	अगर (ret < 0)
		वापस ret;

	chip_id = le16_to_cpu((__क्रमce __le16)ret);

	अगर ((chip_id & OV02A10_ID_MASK) != OV02A10_ID) अणु
		dev_err(&client->dev, "unexpected sensor id(0x%04x)\n", chip_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov02a10_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov02a10 *ov02a10 = to_ov02a10(sd);
	पूर्णांक ret;

	gpiod_set_value_cansleep(ov02a10->rst_gpio, 1);
	gpiod_set_value_cansleep(ov02a10->pd_gpio, 1);

	ret = clk_prepare_enable(ov02a10->eclk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable eclk\n");
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(ov02a10_supply_names),
				    ov02a10->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable regulators\n");
		जाओ disable_clk;
	पूर्ण
	usleep_range(5000, 6000);

	gpiod_set_value_cansleep(ov02a10->pd_gpio, 0);
	usleep_range(5000, 6000);

	gpiod_set_value_cansleep(ov02a10->rst_gpio, 0);
	usleep_range(5000, 6000);

	ret = ov02a10_check_sensor_id(ov02a10);
	अगर (ret)
		जाओ disable_regulator;

	वापस 0;

disable_regulator:
	regulator_bulk_disable(ARRAY_SIZE(ov02a10_supply_names),
			       ov02a10->supplies);
disable_clk:
	clk_disable_unprepare(ov02a10->eclk);

	वापस ret;
पूर्ण

अटल पूर्णांक ov02a10_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov02a10 *ov02a10 = to_ov02a10(sd);

	gpiod_set_value_cansleep(ov02a10->rst_gpio, 1);
	clk_disable_unprepare(ov02a10->eclk);
	gpiod_set_value_cansleep(ov02a10->pd_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ov02a10_supply_names),
			       ov02a10->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक __ov02a10_start_stream(काष्ठा ov02a10 *ov02a10)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	स्थिर काष्ठा ov02a10_reg_list *reg_list;
	पूर्णांक ret;

	/* Apply शेष values of current mode */
	reg_list = &ov02a10->cur_mode->reg_list;
	ret = ov02a10_ग_लिखो_array(ov02a10, reg_list);
	अगर (ret)
		वापस ret;

	/* Apply customized values from user */
	ret = __v4l2_ctrl_handler_setup(ov02a10->subdev.ctrl_handler);
	अगर (ret)
		वापस ret;

	/* Set orientation to 180 degree */
	अगर (ov02a10->upside_करोwn) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, REG_MIRROR_FLIP_CONTROL,
						REG_MIRROR_FLIP_ENABLE);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "failed to set orientation\n");
			वापस ret;
		पूर्ण
		ret = i2c_smbus_ग_लिखो_byte_data(client, REG_GLOBAL_EFFECTIVE,
						REG_ENABLE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Set MIPI TX speed according to DT property */
	अगर (ov02a10->mipi_घड़ी_voltage != OV02A10_MIPI_TX_SPEED_DEFAULT) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, TX_SPEED_AREA_SEL,
						ov02a10->mipi_घड़ी_voltage);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Set stream on रेजिस्टर */
	वापस i2c_smbus_ग_लिखो_byte_data(client, REG_SC_CTRL_MODE,
					 SC_CTRL_MODE_STREAMING);
पूर्ण

अटल पूर्णांक __ov02a10_stop_stream(काष्ठा ov02a10 *ov02a10)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);

	वापस i2c_smbus_ग_लिखो_byte_data(client, REG_SC_CTRL_MODE,
					 SC_CTRL_MODE_STANDBY);
पूर्ण

अटल पूर्णांक ov02a10_entity_init_cfg(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
		.क्रमmat = अणु
			.width = 1600,
			.height = 1200,
		पूर्ण
	पूर्ण;

	ov02a10_set_fmt(sd, cfg, &fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक ov02a10_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov02a10 *ov02a10 = to_ov02a10(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	पूर्णांक ret;

	mutex_lock(&ov02a10->mutex);

	अगर (ov02a10->streaming == on) अणु
		ret = 0;
		जाओ unlock_and_वापस;
	पूर्ण

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			जाओ unlock_and_वापस;
		पूर्ण

		ret = __ov02a10_start_stream(ov02a10);
		अगर (ret) अणु
			__ov02a10_stop_stream(ov02a10);
			ov02a10->streaming = !on;
			जाओ err_rpm_put;
		पूर्ण
	पूर्ण अन्यथा अणु
		__ov02a10_stop_stream(ov02a10);
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov02a10->streaming = on;
	mutex_unlock(&ov02a10->mutex);

	वापस 0;

err_rpm_put:
	pm_runसमय_put(&client->dev);
unlock_and_वापस:
	mutex_unlock(&ov02a10->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ov02a10_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(ov02a10_घातer_off, ov02a10_घातer_on, शून्य)
पूर्ण;

अटल पूर्णांक ov02a10_set_exposure(काष्ठा ov02a10 *ov02a10, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, REG_PAGE_SWITCH, REG_ENABLE);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, OV02A10_REG_EXPOSURE_H,
					val >> OV02A10_EXP_SHIFT);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, OV02A10_REG_EXPOSURE_L, val);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(client, REG_GLOBAL_EFFECTIVE,
					 REG_ENABLE);
पूर्ण

अटल पूर्णांक ov02a10_set_gain(काष्ठा ov02a10 *ov02a10, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, REG_PAGE_SWITCH, REG_ENABLE);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, OV02A10_REG_GAIN, val);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(client, REG_GLOBAL_EFFECTIVE,
					 REG_ENABLE);
पूर्ण

अटल पूर्णांक ov02a10_set_vblank(काष्ठा ov02a10 *ov02a10, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	u32 vts = val + ov02a10->cur_mode->height - OV02A10_BASE_LINES;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, REG_PAGE_SWITCH, REG_ENABLE);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, OV02A10_REG_VTS_H,
					vts >> OV02A10_VTS_SHIFT);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, OV02A10_REG_VTS_L, vts);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(client, REG_GLOBAL_EFFECTIVE,
					 REG_ENABLE);
पूर्ण

अटल पूर्णांक ov02a10_set_test_pattern(काष्ठा ov02a10 *ov02a10, पूर्णांक pattern)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, REG_PAGE_SWITCH, REG_ENABLE);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, OV02A10_REG_TEST_PATTERN,
					pattern);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, REG_GLOBAL_EFFECTIVE,
					REG_ENABLE);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(client, REG_SC_CTRL_MODE,
					 SC_CTRL_MODE_STREAMING);
पूर्ण

अटल पूर्णांक ov02a10_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov02a10 *ov02a10 = container_of(ctrl->handler,
					       काष्ठा ov02a10, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	s64 max_expo;
	पूर्णांक ret;

	/* Propagate change of current control to all related controls */
	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		/* Update max exposure जबतक meeting expected vblanking */
		max_expo = ov02a10->cur_mode->height + ctrl->val -
			   OV02A10_EXPOSURE_MAX_MARGIN;
		__v4l2_ctrl_modअगरy_range(ov02a10->exposure,
					 ov02a10->exposure->minimum, max_expo,
					 ov02a10->exposure->step,
					 ov02a10->exposure->शेष_value);
	पूर्ण

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		ret = ov02a10_set_exposure(ov02a10, ctrl->val);
		अवरोध;
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = ov02a10_set_gain(ov02a10, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		ret = ov02a10_set_vblank(ov02a10, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		ret = ov02a10_set_test_pattern(ov02a10, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov02a10_video_ops = अणु
	.s_stream = ov02a10_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov02a10_pad_ops = अणु
	.init_cfg = ov02a10_entity_init_cfg,
	.क्रमागत_mbus_code = ov02a10_क्रमागत_mbus_code,
	.क्रमागत_frame_size = ov02a10_क्रमागत_frame_sizes,
	.get_fmt = ov02a10_get_fmt,
	.set_fmt = ov02a10_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov02a10_subdev_ops = अणु
	.video	= &ov02a10_video_ops,
	.pad	= &ov02a10_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations ov02a10_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops ov02a10_ctrl_ops = अणु
	.s_ctrl = ov02a10_set_ctrl,
पूर्ण;

अटल पूर्णांक ov02a10_initialize_controls(काष्ठा ov02a10 *ov02a10)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov02a10->subdev);
	स्थिर काष्ठा ov02a10_mode *mode;
	काष्ठा v4l2_ctrl_handler *handler;
	काष्ठा v4l2_ctrl *ctrl;
	s64 exposure_max;
	s64 vblank_def;
	s64 pixel_rate;
	s64 h_blank;
	पूर्णांक ret;

	handler = &ov02a10->ctrl_handler;
	mode = ov02a10->cur_mode;
	ret = v4l2_ctrl_handler_init(handler, 7);
	अगर (ret)
		वापस ret;

	handler->lock = &ov02a10->mutex;

	ctrl = v4l2_ctrl_new_पूर्णांक_menu(handler, शून्य, V4L2_CID_LINK_FREQ, 0, 0,
				      link_freq_menu_items);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	pixel_rate = to_pixel_rate(0);
	v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_PIXEL_RATE, 0, pixel_rate, 1,
			  pixel_rate);

	h_blank = mode->hts_def - mode->width;
	v4l2_ctrl_new_std(handler, शून्य, V4L2_CID_HBLANK, h_blank, h_blank, 1,
			  h_blank);

	vblank_def = mode->vts_def - mode->height;
	v4l2_ctrl_new_std(handler, &ov02a10_ctrl_ops, V4L2_CID_VBLANK,
			  vblank_def, OV02A10_VTS_MAX - mode->height, 1,
			  vblank_def);

	exposure_max = mode->vts_def - 4;
	ov02a10->exposure = v4l2_ctrl_new_std(handler, &ov02a10_ctrl_ops,
					      V4L2_CID_EXPOSURE,
					      OV02A10_EXPOSURE_MIN,
					      exposure_max,
					      OV02A10_EXPOSURE_STEP,
					      mode->exp_def);

	v4l2_ctrl_new_std(handler, &ov02a10_ctrl_ops,
			  V4L2_CID_ANALOGUE_GAIN, OV02A10_GAIN_MIN,
			  OV02A10_GAIN_MAX, OV02A10_GAIN_STEP,
			  OV02A10_GAIN_DEFAULT);

	v4l2_ctrl_new_std_menu_items(handler, &ov02a10_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(ov02a10_test_pattern_menu) - 1,
				     0, 0, ov02a10_test_pattern_menu);

	अगर (handler->error) अणु
		ret = handler->error;
		dev_err(&client->dev, "failed to init controls(%d)\n", ret);
		जाओ err_मुक्त_handler;
	पूर्ण

	ov02a10->subdev.ctrl_handler = handler;

	वापस 0;

err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(handler);

	वापस ret;
पूर्ण

अटल पूर्णांक ov02a10_check_hwcfg(काष्ठा device *dev, काष्ठा ov02a10 *ov02a10)
अणु
	काष्ठा fwnode_handle *ep;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY,
	पूर्ण;
	अचिन्हित पूर्णांक i, j;
	u32 clk_volt;
	पूर्णांक ret;

	अगर (!fwnode)
		वापस -EINVAL;

	ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (!ep)
		वापस -ENXIO;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	अगर (ret)
		वापस ret;

	/* Optional indication of MIPI घड़ी voltage unit */
	ret = fwnode_property_पढ़ो_u32(ep, "ovti,mipi-clock-voltage",
				       &clk_volt);

	अगर (!ret)
		ov02a10->mipi_घड़ी_voltage = clk_volt;

	क्रम (i = 0; i < ARRAY_SIZE(link_freq_menu_items); i++) अणु
		क्रम (j = 0; j < bus_cfg.nr_of_link_frequencies; j++) अणु
			अगर (link_freq_menu_items[i] ==
				bus_cfg.link_frequencies[j])
				अवरोध;
		पूर्ण

		अगर (j == bus_cfg.nr_of_link_frequencies) अणु
			dev_err(dev, "no link frequency %lld supported\n",
				link_freq_menu_items[i]);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);

	वापस ret;
पूर्ण

अटल पूर्णांक ov02a10_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ov02a10 *ov02a10;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक rotation;
	पूर्णांक ret;

	ov02a10 = devm_kzalloc(dev, माप(*ov02a10), GFP_KERNEL);
	अगर (!ov02a10)
		वापस -ENOMEM;

	ret = ov02a10_check_hwcfg(dev, ov02a10);
	अगर (ret)
		वापस dev_err_probe(dev, ret,
				     "failed to check HW configuration\n");

	v4l2_i2c_subdev_init(&ov02a10->subdev, client, &ov02a10_subdev_ops);

	ov02a10->mipi_घड़ी_voltage = OV02A10_MIPI_TX_SPEED_DEFAULT;
	ov02a10->fmt.code = MEDIA_BUS_FMT_SBGGR10_1X10;

	/* Optional indication of physical rotation of sensor */
	rotation = 0;
	device_property_पढ़ो_u32(dev, "rotation", &rotation);
	अगर (rotation == 180) अणु
		ov02a10->upside_करोwn = true;
		ov02a10->fmt.code = MEDIA_BUS_FMT_SRGGB10_1X10;
	पूर्ण

	ov02a10->eclk = devm_clk_get(dev, "eclk");
	अगर (IS_ERR(ov02a10->eclk))
		वापस dev_err_probe(dev, PTR_ERR(ov02a10->eclk),
				     "failed to get eclk\n");

	ret = device_property_पढ़ो_u32(dev, "clock-frequency",
				       &ov02a10->eclk_freq);
	अगर (ret < 0)
		वापस dev_err_probe(dev, ret,
				     "failed to get eclk frequency\n");

	ret = clk_set_rate(ov02a10->eclk, ov02a10->eclk_freq);
	अगर (ret < 0)
		वापस dev_err_probe(dev, ret,
				     "failed to set eclk frequency (24MHz)\n");

	अगर (clk_get_rate(ov02a10->eclk) != OV02A10_ECLK_FREQ)
		dev_warn(dev, "eclk mismatched, mode is based on 24MHz\n");

	ov02a10->pd_gpio = devm_gpiod_get(dev, "powerdown", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov02a10->pd_gpio))
		वापस dev_err_probe(dev, PTR_ERR(ov02a10->pd_gpio),
				     "failed to get powerdown-gpios\n");

	ov02a10->rst_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov02a10->rst_gpio))
		वापस dev_err_probe(dev, PTR_ERR(ov02a10->rst_gpio),
				     "failed to get reset-gpios\n");

	क्रम (i = 0; i < ARRAY_SIZE(ov02a10_supply_names); i++)
		ov02a10->supplies[i].supply = ov02a10_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ov02a10_supply_names),
				      ov02a10->supplies);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to get regulators\n");

	mutex_init(&ov02a10->mutex);

	/* Set शेष mode */
	ov02a10->cur_mode = &supported_modes[0];

	ret = ov02a10_initialize_controls(ov02a10);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "failed to initialize controls\n");
		जाओ err_destroy_mutex;
	पूर्ण

	/* Initialize subdev */
	ov02a10->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov02a10->subdev.entity.ops = &ov02a10_subdev_entity_ops;
	ov02a10->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ov02a10->pad.flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&ov02a10->subdev.entity, 1, &ov02a10->pad);
	अगर (ret < 0) अणु
		dev_err_probe(dev, ret, "failed to initialize entity pads\n");
		जाओ err_मुक्त_handler;
	पूर्ण

	pm_runसमय_enable(dev);
	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = ov02a10_घातer_on(dev);
		अगर (ret < 0) अणु
			dev_err_probe(dev, ret, "failed to power on\n");
			जाओ err_clean_entity;
		पूर्ण
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev(&ov02a10->subdev);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "failed to register V4L2 subdev\n");
		जाओ err_घातer_off;
	पूर्ण

	वापस 0;

err_घातer_off:
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	अन्यथा
		ov02a10_घातer_off(dev);
err_clean_entity:
	media_entity_cleanup(&ov02a10->subdev.entity);
err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(ov02a10->subdev.ctrl_handler);
err_destroy_mutex:
	mutex_destroy(&ov02a10->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ov02a10_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov02a10 *ov02a10 = to_ov02a10(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		ov02a10_घातer_off(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	mutex_destroy(&ov02a10->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ov02a10_of_match[] = अणु
	अणु .compatible = "ovti,ov02a10" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ov02a10_of_match);

अटल काष्ठा i2c_driver ov02a10_i2c_driver = अणु
	.driver = अणु
		.name = "ov02a10",
		.pm = &ov02a10_pm_ops,
		.of_match_table = ov02a10_of_match,
	पूर्ण,
	.probe_new	= &ov02a10_probe,
	.हटाओ		= &ov02a10_हटाओ,
पूर्ण;
module_i2c_driver(ov02a10_i2c_driver);

MODULE_AUTHOR("Dongchun Zhu <dongchun.zhu@mediatek.com>");
MODULE_DESCRIPTION("OmniVision OV02A10 sensor driver");
MODULE_LICENSE("GPL v2");
