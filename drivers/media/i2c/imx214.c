<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * imx214.c - imx214 sensor driver
 *
 * Copyright 2018 Qtechnology A/S
 *
 * Ricarकरो Ribalda <ribalda@kernel.org>
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा IMX214_DEFAULT_CLK_FREQ	24000000
#घोषणा IMX214_DEFAULT_LINK_FREQ 480000000
#घोषणा IMX214_DEFAULT_PIXEL_RATE ((IMX214_DEFAULT_LINK_FREQ * 8LL) / 10)
#घोषणा IMX214_FPS 30
#घोषणा IMX214_MBUS_CODE MEDIA_BUS_FMT_SRGGB10_1X10

अटल स्थिर अक्षर * स्थिर imx214_supply_name[] = अणु
	"vdda",
	"vddd",
	"vdddo",
पूर्ण;

#घोषणा IMX214_NUM_SUPPLIES ARRAY_SIZE(imx214_supply_name)

काष्ठा imx214 अणु
	काष्ठा device *dev;
	काष्ठा clk *xclk;
	काष्ठा regmap *regmap;

	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt fmt;
	काष्ठा v4l2_rect crop;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *unit_size;

	काष्ठा regulator_bulk_data	supplies[IMX214_NUM_SUPPLIES];

	काष्ठा gpio_desc *enable_gpio;

	/*
	 * Serialize control access, get/set क्रमmat, get selection
	 * and start streaming.
	 */
	काष्ठा mutex mutex;

	bool streaming;
पूर्ण;

काष्ठा reg_8 अणु
	u16 addr;
	u8 val;
पूर्ण;

क्रमागत अणु
	IMX214_TABLE_WAIT_MS = 0,
	IMX214_TABLE_END,
	IMX214_MAX_RETRIES,
	IMX214_WAIT_MS
पूर्ण;

/*From imx214_mode_tbls.h*/
अटल स्थिर काष्ठा reg_8 mode_4096x2304[] = अणु
	अणु0x0114, 0x03पूर्ण,
	अणु0x0220, 0x00पूर्ण,
	अणु0x0221, 0x11पूर्ण,
	अणु0x0222, 0x01पूर्ण,
	अणु0x0340, 0x0Cपूर्ण,
	अणु0x0341, 0x7Aपूर्ण,
	अणु0x0342, 0x13पूर्ण,
	अणु0x0343, 0x90पूर्ण,
	अणु0x0344, 0x00पूर्ण,
	अणु0x0345, 0x38पूर्ण,
	अणु0x0346, 0x01पूर्ण,
	अणु0x0347, 0x98पूर्ण,
	अणु0x0348, 0x10पूर्ण,
	अणु0x0349, 0x37पूर्ण,
	अणु0x034A, 0x0Aपूर्ण,
	अणु0x034B, 0x97पूर्ण,
	अणु0x0381, 0x01पूर्ण,
	अणु0x0383, 0x01पूर्ण,
	अणु0x0385, 0x01पूर्ण,
	अणु0x0387, 0x01पूर्ण,
	अणु0x0900, 0x00पूर्ण,
	अणु0x0901, 0x00पूर्ण,
	अणु0x0902, 0x00पूर्ण,
	अणु0x3000, 0x35पूर्ण,
	अणु0x3054, 0x01पूर्ण,
	अणु0x305C, 0x11पूर्ण,

	अणु0x0112, 0x0Aपूर्ण,
	अणु0x0113, 0x0Aपूर्ण,
	अणु0x034C, 0x10पूर्ण,
	अणु0x034D, 0x00पूर्ण,
	अणु0x034E, 0x09पूर्ण,
	अणु0x034F, 0x00पूर्ण,
	अणु0x0401, 0x00पूर्ण,
	अणु0x0404, 0x00पूर्ण,
	अणु0x0405, 0x10पूर्ण,
	अणु0x0408, 0x00पूर्ण,
	अणु0x0409, 0x00पूर्ण,
	अणु0x040A, 0x00पूर्ण,
	अणु0x040B, 0x00पूर्ण,
	अणु0x040C, 0x10पूर्ण,
	अणु0x040D, 0x00पूर्ण,
	अणु0x040E, 0x09पूर्ण,
	अणु0x040F, 0x00पूर्ण,

	अणु0x0301, 0x05पूर्ण,
	अणु0x0303, 0x02पूर्ण,
	अणु0x0305, 0x03पूर्ण,
	अणु0x0306, 0x00पूर्ण,
	अणु0x0307, 0x96पूर्ण,
	अणु0x0309, 0x0Aपूर्ण,
	अणु0x030B, 0x01पूर्ण,
	अणु0x0310, 0x00पूर्ण,

	अणु0x0820, 0x12पूर्ण,
	अणु0x0821, 0xC0पूर्ण,
	अणु0x0822, 0x00पूर्ण,
	अणु0x0823, 0x00पूर्ण,

	अणु0x3A03, 0x09पूर्ण,
	अणु0x3A04, 0x50पूर्ण,
	अणु0x3A05, 0x01पूर्ण,

	अणु0x0B06, 0x01पूर्ण,
	अणु0x30A2, 0x00पूर्ण,

	अणु0x30B4, 0x00पूर्ण,

	अणु0x3A02, 0xFFपूर्ण,

	अणु0x3011, 0x00पूर्ण,
	अणु0x3013, 0x01पूर्ण,

	अणु0x0202, 0x0Cपूर्ण,
	अणु0x0203, 0x70पूर्ण,
	अणु0x0224, 0x01पूर्ण,
	अणु0x0225, 0xF4पूर्ण,

	अणु0x0204, 0x00पूर्ण,
	अणु0x0205, 0x00पूर्ण,
	अणु0x020E, 0x01पूर्ण,
	अणु0x020F, 0x00पूर्ण,
	अणु0x0210, 0x01पूर्ण,
	अणु0x0211, 0x00पूर्ण,
	अणु0x0212, 0x01पूर्ण,
	अणु0x0213, 0x00पूर्ण,
	अणु0x0214, 0x01पूर्ण,
	अणु0x0215, 0x00पूर्ण,
	अणु0x0216, 0x00पूर्ण,
	अणु0x0217, 0x00पूर्ण,

	अणु0x4170, 0x00पूर्ण,
	अणु0x4171, 0x10पूर्ण,
	अणु0x4176, 0x00पूर्ण,
	अणु0x4177, 0x3Cपूर्ण,
	अणु0xAE20, 0x04पूर्ण,
	अणु0xAE21, 0x5Cपूर्ण,

	अणुIMX214_TABLE_WAIT_MS, 10पूर्ण,
	अणु0x0138, 0x01पूर्ण,
	अणुIMX214_TABLE_END, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_8 mode_1920x1080[] = अणु
	अणु0x0114, 0x03पूर्ण,
	अणु0x0220, 0x00पूर्ण,
	अणु0x0221, 0x11पूर्ण,
	अणु0x0222, 0x01पूर्ण,
	अणु0x0340, 0x0Cपूर्ण,
	अणु0x0341, 0x7Aपूर्ण,
	अणु0x0342, 0x13पूर्ण,
	अणु0x0343, 0x90पूर्ण,
	अणु0x0344, 0x04पूर्ण,
	अणु0x0345, 0x78पूर्ण,
	अणु0x0346, 0x03पूर्ण,
	अणु0x0347, 0xFCपूर्ण,
	अणु0x0348, 0x0Bपूर्ण,
	अणु0x0349, 0xF7पूर्ण,
	अणु0x034A, 0x08पूर्ण,
	अणु0x034B, 0x33पूर्ण,
	अणु0x0381, 0x01पूर्ण,
	अणु0x0383, 0x01पूर्ण,
	अणु0x0385, 0x01पूर्ण,
	अणु0x0387, 0x01पूर्ण,
	अणु0x0900, 0x00पूर्ण,
	अणु0x0901, 0x00पूर्ण,
	अणु0x0902, 0x00पूर्ण,
	अणु0x3000, 0x35पूर्ण,
	अणु0x3054, 0x01पूर्ण,
	अणु0x305C, 0x11पूर्ण,

	अणु0x0112, 0x0Aपूर्ण,
	अणु0x0113, 0x0Aपूर्ण,
	अणु0x034C, 0x07पूर्ण,
	अणु0x034D, 0x80पूर्ण,
	अणु0x034E, 0x04पूर्ण,
	अणु0x034F, 0x38पूर्ण,
	अणु0x0401, 0x00पूर्ण,
	अणु0x0404, 0x00पूर्ण,
	अणु0x0405, 0x10पूर्ण,
	अणु0x0408, 0x00पूर्ण,
	अणु0x0409, 0x00पूर्ण,
	अणु0x040A, 0x00पूर्ण,
	अणु0x040B, 0x00पूर्ण,
	अणु0x040C, 0x07पूर्ण,
	अणु0x040D, 0x80पूर्ण,
	अणु0x040E, 0x04पूर्ण,
	अणु0x040F, 0x38पूर्ण,

	अणु0x0301, 0x05पूर्ण,
	अणु0x0303, 0x02पूर्ण,
	अणु0x0305, 0x03पूर्ण,
	अणु0x0306, 0x00पूर्ण,
	अणु0x0307, 0x96पूर्ण,
	अणु0x0309, 0x0Aपूर्ण,
	अणु0x030B, 0x01पूर्ण,
	अणु0x0310, 0x00पूर्ण,

	अणु0x0820, 0x12पूर्ण,
	अणु0x0821, 0xC0पूर्ण,
	अणु0x0822, 0x00पूर्ण,
	अणु0x0823, 0x00पूर्ण,

	अणु0x3A03, 0x04पूर्ण,
	अणु0x3A04, 0xF8पूर्ण,
	अणु0x3A05, 0x02पूर्ण,

	अणु0x0B06, 0x01पूर्ण,
	अणु0x30A2, 0x00पूर्ण,

	अणु0x30B4, 0x00पूर्ण,

	अणु0x3A02, 0xFFपूर्ण,

	अणु0x3011, 0x00पूर्ण,
	अणु0x3013, 0x01पूर्ण,

	अणु0x0202, 0x0Cपूर्ण,
	अणु0x0203, 0x70पूर्ण,
	अणु0x0224, 0x01पूर्ण,
	अणु0x0225, 0xF4पूर्ण,

	अणु0x0204, 0x00पूर्ण,
	अणु0x0205, 0x00पूर्ण,
	अणु0x020E, 0x01पूर्ण,
	अणु0x020F, 0x00पूर्ण,
	अणु0x0210, 0x01पूर्ण,
	अणु0x0211, 0x00पूर्ण,
	अणु0x0212, 0x01पूर्ण,
	अणु0x0213, 0x00पूर्ण,
	अणु0x0214, 0x01पूर्ण,
	अणु0x0215, 0x00पूर्ण,
	अणु0x0216, 0x00पूर्ण,
	अणु0x0217, 0x00पूर्ण,

	अणु0x4170, 0x00पूर्ण,
	अणु0x4171, 0x10पूर्ण,
	अणु0x4176, 0x00पूर्ण,
	अणु0x4177, 0x3Cपूर्ण,
	अणु0xAE20, 0x04पूर्ण,
	अणु0xAE21, 0x5Cपूर्ण,

	अणुIMX214_TABLE_WAIT_MS, 10पूर्ण,
	अणु0x0138, 0x01पूर्ण,
	अणुIMX214_TABLE_END, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_8 mode_table_common[] = अणु
	/* software reset */

	/* software standby settings */
	अणु0x0100, 0x00पूर्ण,

	/* ATR setting */
	अणु0x9300, 0x02पूर्ण,

	/* बाह्यal घड़ी setting */
	अणु0x0136, 0x18पूर्ण,
	अणु0x0137, 0x00पूर्ण,

	/* global setting */
	/* basic config */
	अणु0x0101, 0x00पूर्ण,
	अणु0x0105, 0x01पूर्ण,
	अणु0x0106, 0x01पूर्ण,
	अणु0x4550, 0x02पूर्ण,
	अणु0x4601, 0x00पूर्ण,
	अणु0x4642, 0x05पूर्ण,
	अणु0x6227, 0x11पूर्ण,
	अणु0x6276, 0x00पूर्ण,
	अणु0x900E, 0x06पूर्ण,
	अणु0xA802, 0x90पूर्ण,
	अणु0xA803, 0x11पूर्ण,
	अणु0xA804, 0x62पूर्ण,
	अणु0xA805, 0x77पूर्ण,
	अणु0xA806, 0xAEपूर्ण,
	अणु0xA807, 0x34पूर्ण,
	अणु0xA808, 0xAEपूर्ण,
	अणु0xA809, 0x35पूर्ण,
	अणु0xA80A, 0x62पूर्ण,
	अणु0xA80B, 0x83पूर्ण,
	अणु0xAE33, 0x00पूर्ण,

	/* analog setting */
	अणु0x4174, 0x00पूर्ण,
	अणु0x4175, 0x11पूर्ण,
	अणु0x4612, 0x29पूर्ण,
	अणु0x461B, 0x12पूर्ण,
	अणु0x461F, 0x06पूर्ण,
	अणु0x4635, 0x07पूर्ण,
	अणु0x4637, 0x30पूर्ण,
	अणु0x463F, 0x18पूर्ण,
	अणु0x4641, 0x0Dपूर्ण,
	अणु0x465B, 0x12पूर्ण,
	अणु0x465F, 0x11पूर्ण,
	अणु0x4663, 0x11पूर्ण,
	अणु0x4667, 0x0Fपूर्ण,
	अणु0x466F, 0x0Fपूर्ण,
	अणु0x470E, 0x09पूर्ण,
	अणु0x4909, 0xABपूर्ण,
	अणु0x490B, 0x95पूर्ण,
	अणु0x4915, 0x5Dपूर्ण,
	अणु0x4A5F, 0xFFपूर्ण,
	अणु0x4A61, 0xFFपूर्ण,
	अणु0x4A73, 0x62पूर्ण,
	अणु0x4A85, 0x00पूर्ण,
	अणु0x4A87, 0xFFपूर्ण,

	/* embedded data */
	अणु0x5041, 0x04पूर्ण,
	अणु0x583C, 0x04पूर्ण,
	अणु0x620E, 0x04पूर्ण,
	अणु0x6EB2, 0x01पूर्ण,
	अणु0x6EB3, 0x00पूर्ण,
	अणु0x9300, 0x02पूर्ण,

	/* imagequality */
	/* HDR setting */
	अणु0x3001, 0x07पूर्ण,
	अणु0x6D12, 0x3Fपूर्ण,
	अणु0x6D13, 0xFFपूर्ण,
	अणु0x9344, 0x03पूर्ण,
	अणु0x9706, 0x10पूर्ण,
	अणु0x9707, 0x03पूर्ण,
	अणु0x9708, 0x03पूर्ण,
	अणु0x9E04, 0x01पूर्ण,
	अणु0x9E05, 0x00पूर्ण,
	अणु0x9E0C, 0x01पूर्ण,
	अणु0x9E0D, 0x02पूर्ण,
	अणु0x9E24, 0x00पूर्ण,
	अणु0x9E25, 0x8Cपूर्ण,
	अणु0x9E26, 0x00पूर्ण,
	अणु0x9E27, 0x94पूर्ण,
	अणु0x9E28, 0x00पूर्ण,
	अणु0x9E29, 0x96पूर्ण,

	/* CNR parameter setting */
	अणु0x69DB, 0x01पूर्ण,

	/* Moire reduction */
	अणु0x6957, 0x01पूर्ण,

	/* image enhancement */
	अणु0x6987, 0x17पूर्ण,
	अणु0x698A, 0x03पूर्ण,
	अणु0x698B, 0x03पूर्ण,

	/* white balanace */
	अणु0x0B8E, 0x01पूर्ण,
	अणु0x0B8F, 0x00पूर्ण,
	अणु0x0B90, 0x01पूर्ण,
	अणु0x0B91, 0x00पूर्ण,
	अणु0x0B92, 0x01पूर्ण,
	अणु0x0B93, 0x00पूर्ण,
	अणु0x0B94, 0x01पूर्ण,
	अणु0x0B95, 0x00पूर्ण,

	/* ATR setting */
	अणु0x6E50, 0x00पूर्ण,
	अणु0x6E51, 0x32पूर्ण,
	अणु0x9340, 0x00पूर्ण,
	अणु0x9341, 0x3Cपूर्ण,
	अणु0x9342, 0x03पूर्ण,
	अणु0x9343, 0xFFपूर्ण,
	अणुIMX214_TABLE_END, 0x00पूर्ण
पूर्ण;

/*
 * Declare modes in order, from biggest
 * to smallest height.
 */
अटल स्थिर काष्ठा imx214_mode अणु
	u32 width;
	u32 height;
	स्थिर काष्ठा reg_8 *reg_table;
पूर्ण imx214_modes[] = अणु
	अणु
		.width = 4096,
		.height = 2304,
		.reg_table = mode_4096x2304,
	पूर्ण,
	अणु
		.width = 1920,
		.height = 1080,
		.reg_table = mode_1920x1080,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा imx214 *to_imx214(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा imx214, sd);
पूर्ण

अटल पूर्णांक __maybe_unused imx214_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx214 *imx214 = to_imx214(sd);
	पूर्णांक ret;

	ret = regulator_bulk_enable(IMX214_NUM_SUPPLIES, imx214->supplies);
	अगर (ret < 0) अणु
		dev_err(imx214->dev, "failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(2000, 3000);

	ret = clk_prepare_enable(imx214->xclk);
	अगर (ret < 0) अणु
		regulator_bulk_disable(IMX214_NUM_SUPPLIES, imx214->supplies);
		dev_err(imx214->dev, "clk prepare enable failed\n");
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(imx214->enable_gpio, 1);
	usleep_range(12000, 15000);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx214_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx214 *imx214 = to_imx214(sd);

	gpiod_set_value_cansleep(imx214->enable_gpio, 0);

	clk_disable_unprepare(imx214->xclk);

	regulator_bulk_disable(IMX214_NUM_SUPPLIES, imx214->supplies);
	usleep_range(10, 20);

	वापस 0;
पूर्ण

अटल पूर्णांक imx214_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = IMX214_MBUS_CODE;

	वापस 0;
पूर्ण

अटल पूर्णांक imx214_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->code != IMX214_MBUS_CODE)
		वापस -EINVAL;

	अगर (fse->index >= ARRAY_SIZE(imx214_modes))
		वापस -EINVAL;

	fse->min_width = fse->max_width = imx214_modes[fse->index].width;
	fse->min_height = fse->max_height = imx214_modes[fse->index].height;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक imx214_s_रेजिस्टर(काष्ठा v4l2_subdev *subdev,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा imx214 *imx214 = container_of(subdev, काष्ठा imx214, sd);

	वापस regmap_ग_लिखो(imx214->regmap, reg->reg, reg->val);
पूर्ण

अटल पूर्णांक imx214_g_रेजिस्टर(काष्ठा v4l2_subdev *subdev,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा imx214 *imx214 = container_of(subdev, काष्ठा imx214, sd);
	अचिन्हित पूर्णांक aux;
	पूर्णांक ret;

	reg->size = 1;
	ret = regmap_पढ़ो(imx214->regmap, reg->reg, &aux);
	reg->val = aux;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_subdev_core_ops imx214_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = imx214_g_रेजिस्टर,
	.s_रेजिस्टर = imx214_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा v4l2_mbus_framefmt *
__imx214_get_pad_क्रमmat(काष्ठा imx214 *imx214,
			काष्ठा v4l2_subdev_pad_config *cfg,
			अचिन्हित पूर्णांक pad,
			क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&imx214->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &imx214->fmt;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक imx214_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा imx214 *imx214 = to_imx214(sd);

	mutex_lock(&imx214->mutex);
	क्रमmat->क्रमmat = *__imx214_get_pad_क्रमmat(imx214, cfg, क्रमmat->pad,
						  क्रमmat->which);
	mutex_unlock(&imx214->mutex);

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_rect *
__imx214_get_pad_crop(काष्ठा imx214 *imx214, काष्ठा v4l2_subdev_pad_config *cfg,
		      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&imx214->sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &imx214->crop;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक imx214_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा imx214 *imx214 = to_imx214(sd);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	स्थिर काष्ठा imx214_mode *mode;

	mutex_lock(&imx214->mutex);

	__crop = __imx214_get_pad_crop(imx214, cfg, क्रमmat->pad, क्रमmat->which);

	mode = v4l2_find_nearest_size(imx214_modes,
				      ARRAY_SIZE(imx214_modes), width, height,
				      क्रमmat->क्रमmat.width,
				      क्रमmat->क्रमmat.height);

	__crop->width = mode->width;
	__crop->height = mode->height;

	__क्रमmat = __imx214_get_pad_क्रमmat(imx214, cfg, क्रमmat->pad,
					   क्रमmat->which);
	__क्रमmat->width = __crop->width;
	__क्रमmat->height = __crop->height;
	__क्रमmat->code = IMX214_MBUS_CODE;
	__क्रमmat->field = V4L2_FIELD_NONE;
	__क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;
	__क्रमmat->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(__क्रमmat->colorspace);
	__क्रमmat->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true,
				__क्रमmat->colorspace, __क्रमmat->ycbcr_enc);
	__क्रमmat->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(__क्रमmat->colorspace);

	क्रमmat->क्रमmat = *__क्रमmat;

	mutex_unlock(&imx214->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक imx214_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा imx214 *imx214 = to_imx214(sd);

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	mutex_lock(&imx214->mutex);
	sel->r = *__imx214_get_pad_crop(imx214, cfg, sel->pad,
					sel->which);
	mutex_unlock(&imx214->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक imx214_entity_init_cfg(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु पूर्ण;

	fmt.which = cfg ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	fmt.क्रमmat.width = imx214_modes[0].width;
	fmt.क्रमmat.height = imx214_modes[0].height;

	imx214_set_क्रमmat(subdev, cfg, &fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक imx214_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imx214 *imx214 = container_of(ctrl->handler,
					     काष्ठा imx214, ctrls);
	u8 vals[2];
	पूर्णांक ret;

	/*
	 * Applying V4L2 control value only happens
	 * when घातer is up क्रम streaming
	 */
	अगर (!pm_runसमय_get_अगर_in_use(imx214->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		vals[1] = ctrl->val;
		vals[0] = ctrl->val >> 8;
		ret = regmap_bulk_ग_लिखो(imx214->regmap, 0x202, vals, 2);
		अगर (ret < 0)
			dev_err(imx214->dev, "Error %d\n", ret);
		ret = 0;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	pm_runसमय_put(imx214->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops imx214_ctrl_ops = अणु
	.s_ctrl = imx214_set_ctrl,
पूर्ण;

#घोषणा MAX_CMD 4
अटल पूर्णांक imx214_ग_लिखो_table(काष्ठा imx214 *imx214,
			      स्थिर काष्ठा reg_8 table[])
अणु
	u8 vals[MAX_CMD];
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (; table->addr != IMX214_TABLE_END ; table++) अणु
		अगर (table->addr == IMX214_TABLE_WAIT_MS) अणु
			usleep_range(table->val * 1000,
				     table->val * 1000 + 500);
			जारी;
		पूर्ण

		क्रम (i = 0; i < MAX_CMD; i++) अणु
			अगर (table[i].addr != (table[0].addr + i))
				अवरोध;
			vals[i] = table[i].val;
		पूर्ण

		ret = regmap_bulk_ग_लिखो(imx214->regmap, table->addr, vals, i);

		अगर (ret) अणु
			dev_err(imx214->dev, "write_table error: %d\n", ret);
			वापस ret;
		पूर्ण

		table += i - 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx214_start_streaming(काष्ठा imx214 *imx214)
अणु
	स्थिर काष्ठा imx214_mode *mode;
	पूर्णांक ret;

	mutex_lock(&imx214->mutex);
	ret = imx214_ग_लिखो_table(imx214, mode_table_common);
	अगर (ret < 0) अणु
		dev_err(imx214->dev, "could not sent common table %d\n", ret);
		जाओ error;
	पूर्ण

	mode = v4l2_find_nearest_size(imx214_modes,
				ARRAY_SIZE(imx214_modes), width, height,
				imx214->fmt.width, imx214->fmt.height);
	ret = imx214_ग_लिखो_table(imx214, mode->reg_table);
	अगर (ret < 0) अणु
		dev_err(imx214->dev, "could not sent mode table %d\n", ret);
		जाओ error;
	पूर्ण
	ret = __v4l2_ctrl_handler_setup(&imx214->ctrls);
	अगर (ret < 0) अणु
		dev_err(imx214->dev, "could not sync v4l2 controls\n");
		जाओ error;
	पूर्ण
	ret = regmap_ग_लिखो(imx214->regmap, 0x100, 1);
	अगर (ret < 0) अणु
		dev_err(imx214->dev, "could not sent start table %d\n", ret);
		जाओ error;
	पूर्ण

	mutex_unlock(&imx214->mutex);
	वापस 0;

error:
	mutex_unlock(&imx214->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक imx214_stop_streaming(काष्ठा imx214 *imx214)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(imx214->regmap, 0x100, 0);
	अगर (ret < 0)
		dev_err(imx214->dev, "could not sent stop table %d\n",	ret);

	वापस ret;
पूर्ण

अटल पूर्णांक imx214_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा imx214 *imx214 = to_imx214(subdev);
	पूर्णांक ret;

	अगर (imx214->streaming == enable)
		वापस 0;

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(imx214->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(imx214->dev);
			वापस ret;
		पूर्ण

		ret = imx214_start_streaming(imx214);
		अगर (ret < 0)
			जाओ err_rpm_put;
	पूर्ण अन्यथा अणु
		ret = imx214_stop_streaming(imx214);
		अगर (ret < 0)
			जाओ err_rpm_put;
		pm_runसमय_put(imx214->dev);
	पूर्ण

	imx214->streaming = enable;
	वापस 0;

err_rpm_put:
	pm_runसमय_put(imx214->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक imx214_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fival)
अणु
	fival->पूर्णांकerval.numerator = 1;
	fival->पूर्णांकerval.denominator = IMX214_FPS;

	वापस 0;
पूर्ण

अटल पूर्णांक imx214_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	स्थिर काष्ठा imx214_mode *mode;

	अगर (fie->index != 0)
		वापस -EINVAL;

	mode = v4l2_find_nearest_size(imx214_modes,
				ARRAY_SIZE(imx214_modes), width, height,
				fie->width, fie->height);

	fie->code = IMX214_MBUS_CODE;
	fie->width = mode->width;
	fie->height = mode->height;
	fie->पूर्णांकerval.numerator = 1;
	fie->पूर्णांकerval.denominator = IMX214_FPS;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops imx214_video_ops = अणु
	.s_stream = imx214_s_stream,
	.g_frame_पूर्णांकerval = imx214_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = imx214_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx214_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = imx214_क्रमागत_mbus_code,
	.क्रमागत_frame_size = imx214_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval = imx214_क्रमागत_frame_पूर्णांकerval,
	.get_fmt = imx214_get_क्रमmat,
	.set_fmt = imx214_set_क्रमmat,
	.get_selection = imx214_get_selection,
	.init_cfg = imx214_entity_init_cfg,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx214_subdev_ops = अणु
	.core = &imx214_core_ops,
	.video = &imx214_video_ops,
	.pad = &imx214_subdev_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sensor_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक imx214_get_regulators(काष्ठा device *dev, काष्ठा imx214 *imx214)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IMX214_NUM_SUPPLIES; i++)
		imx214->supplies[i].supply = imx214_supply_name[i];

	वापस devm_regulator_bulk_get(dev, IMX214_NUM_SUPPLIES,
				       imx214->supplies);
पूर्ण

अटल पूर्णांक imx214_parse_fwnode(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *endpoपूर्णांक;
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY,
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	endpoपूर्णांक = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(dev), शून्य);
	अगर (!endpoपूर्णांक) अणु
		dev_err(dev, "endpoint node not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(endpoपूर्णांक, &bus_cfg);
	अगर (ret) अणु
		dev_err(dev, "parsing endpoint node failed\n");
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < bus_cfg.nr_of_link_frequencies; i++)
		अगर (bus_cfg.link_frequencies[i] == IMX214_DEFAULT_LINK_FREQ)
			अवरोध;

	अगर (i == bus_cfg.nr_of_link_frequencies) अणु
		dev_err(dev, "link-frequencies %d not supported, Please review your DT\n",
			IMX214_DEFAULT_LINK_FREQ);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

करोne:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);
	fwnode_handle_put(endpoपूर्णांक);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused imx214_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx214 *imx214 = to_imx214(sd);

	अगर (imx214->streaming)
		imx214_stop_streaming(imx214);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx214_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx214 *imx214 = to_imx214(sd);
	पूर्णांक ret;

	अगर (imx214->streaming) अणु
		ret = imx214_start_streaming(imx214);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	imx214_stop_streaming(imx214);
	imx214->streaming = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक imx214_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा imx214 *imx214;
	अटल स्थिर s64 link_freq[] = अणु
		IMX214_DEFAULT_LINK_FREQ,
	पूर्ण;
	अटल स्थिर काष्ठा v4l2_area unit_size = अणु
		.width = 1120,
		.height = 1120,
	पूर्ण;
	पूर्णांक ret;

	ret = imx214_parse_fwnode(dev);
	अगर (ret)
		वापस ret;

	imx214 = devm_kzalloc(dev, माप(*imx214), GFP_KERNEL);
	अगर (!imx214)
		वापस -ENOMEM;

	imx214->dev = dev;

	imx214->xclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(imx214->xclk)) अणु
		dev_err(dev, "could not get xclk");
		वापस PTR_ERR(imx214->xclk);
	पूर्ण

	ret = clk_set_rate(imx214->xclk, IMX214_DEFAULT_CLK_FREQ);
	अगर (ret) अणु
		dev_err(dev, "could not set xclk frequency\n");
		वापस ret;
	पूर्ण

	ret = imx214_get_regulators(dev, imx214);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot get regulators\n");
		वापस ret;
	पूर्ण

	imx214->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(imx214->enable_gpio)) अणु
		dev_err(dev, "cannot get enable gpio\n");
		वापस PTR_ERR(imx214->enable_gpio);
	पूर्ण

	imx214->regmap = devm_regmap_init_i2c(client, &sensor_regmap_config);
	अगर (IS_ERR(imx214->regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(imx214->regmap);
	पूर्ण

	v4l2_i2c_subdev_init(&imx214->sd, client, &imx214_subdev_ops);

	/*
	 * Enable घातer initially, to aव्योम warnings
	 * from clk_disable on घातer_off
	 */
	imx214_घातer_on(imx214->dev);

	pm_runसमय_set_active(imx214->dev);
	pm_runसमय_enable(imx214->dev);
	pm_runसमय_idle(imx214->dev);

	v4l2_ctrl_handler_init(&imx214->ctrls, 3);

	imx214->pixel_rate = v4l2_ctrl_new_std(&imx214->ctrls, शून्य,
					       V4L2_CID_PIXEL_RATE, 0,
					       IMX214_DEFAULT_PIXEL_RATE, 1,
					       IMX214_DEFAULT_PIXEL_RATE);
	imx214->link_freq = v4l2_ctrl_new_पूर्णांक_menu(&imx214->ctrls, शून्य,
						   V4L2_CID_LINK_FREQ,
						   ARRAY_SIZE(link_freq) - 1,
						   0, link_freq);
	अगर (imx214->link_freq)
		imx214->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	/*
	 * WARNING!
	 * Values obtained reverse engineering blobs and/or devices.
	 * Ranges and functionality might be wrong.
	 *
	 * Sony, please release some रेजिस्टर set करोcumentation क्रम the
	 * device.
	 *
	 * Yours sincerely, Ricarकरो.
	 */
	imx214->exposure = v4l2_ctrl_new_std(&imx214->ctrls, &imx214_ctrl_ops,
					     V4L2_CID_EXPOSURE,
					     0, 3184, 1, 0x0c70);

	imx214->unit_size = v4l2_ctrl_new_std_compound(&imx214->ctrls,
				शून्य,
				V4L2_CID_UNIT_CELL_SIZE,
				v4l2_ctrl_ptr_create((व्योम *)&unit_size));
	ret = imx214->ctrls.error;
	अगर (ret) अणु
		dev_err(&client->dev, "%s control init failed (%d)\n",
			__func__, ret);
		जाओ मुक्त_ctrl;
	पूर्ण

	imx214->sd.ctrl_handler = &imx214->ctrls;
	mutex_init(&imx214->mutex);
	imx214->ctrls.lock = &imx214->mutex;

	imx214->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	imx214->pad.flags = MEDIA_PAD_FL_SOURCE;
	imx214->sd.dev = &client->dev;
	imx214->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&imx214->sd.entity, 1, &imx214->pad);
	अगर (ret < 0) अणु
		dev_err(dev, "could not register media entity\n");
		जाओ मुक्त_ctrl;
	पूर्ण

	imx214_entity_init_cfg(&imx214->sd, शून्य);

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&imx214->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "could not register v4l2 device\n");
		जाओ मुक्त_entity;
	पूर्ण

	वापस 0;

मुक्त_entity:
	media_entity_cleanup(&imx214->sd.entity);
मुक्त_ctrl:
	mutex_destroy(&imx214->mutex);
	v4l2_ctrl_handler_मुक्त(&imx214->ctrls);
	pm_runसमय_disable(imx214->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक imx214_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx214 *imx214 = to_imx214(sd);

	v4l2_async_unरेजिस्टर_subdev(&imx214->sd);
	media_entity_cleanup(&imx214->sd.entity);
	v4l2_ctrl_handler_मुक्त(&imx214->ctrls);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	mutex_destroy(&imx214->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx214_of_match[] = अणु
	अणु .compatible = "sony,imx214" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx214_of_match);

अटल स्थिर काष्ठा dev_pm_ops imx214_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(imx214_suspend, imx214_resume)
	SET_RUNTIME_PM_OPS(imx214_घातer_off, imx214_घातer_on, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver imx214_i2c_driver = अणु
	.driver = अणु
		.of_match_table = imx214_of_match,
		.pm = &imx214_pm_ops,
		.name  = "imx214",
	पूर्ण,
	.probe_new  = imx214_probe,
	.हटाओ = imx214_हटाओ,
पूर्ण;

module_i2c_driver(imx214_i2c_driver);

MODULE_DESCRIPTION("Sony IMX214 Camera driver");
MODULE_AUTHOR("Ricardo Ribalda <ribalda@kernel.org>");
MODULE_LICENSE("GPL v2");
