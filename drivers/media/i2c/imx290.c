<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sony IMX290 CMOS Image Sensor Driver
 *
 * Copyright (C) 2019 FRAMOS GmbH.
 *
 * Copyright (C) 2019 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
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
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा IMX290_STANDBY 0x3000
#घोषणा IMX290_REGHOLD 0x3001
#घोषणा IMX290_XMSTA 0x3002
#घोषणा IMX290_FR_FDG_SEL 0x3009
#घोषणा IMX290_BLKLEVEL_LOW 0x300a
#घोषणा IMX290_BLKLEVEL_HIGH 0x300b
#घोषणा IMX290_GAIN 0x3014
#घोषणा IMX290_HMAX_LOW 0x301c
#घोषणा IMX290_HMAX_HIGH 0x301d
#घोषणा IMX290_PGCTRL 0x308c
#घोषणा IMX290_PHY_LANE_NUM 0x3407
#घोषणा IMX290_CSI_LANE_MODE 0x3443

#घोषणा IMX290_PGCTRL_REGEN BIT(0)
#घोषणा IMX290_PGCTRL_THRU BIT(1)
#घोषणा IMX290_PGCTRL_MODE(n) ((n) << 4)

अटल स्थिर अक्षर * स्थिर imx290_supply_name[] = अणु
	"vdda",
	"vddd",
	"vdddo",
पूर्ण;

#घोषणा IMX290_NUM_SUPPLIES ARRAY_SIZE(imx290_supply_name)

काष्ठा imx290_regval अणु
	u16 reg;
	u8 val;
पूर्ण;

काष्ठा imx290_mode अणु
	u32 width;
	u32 height;
	u32 hmax;
	u8 link_freq_index;

	स्थिर काष्ठा imx290_regval *data;
	u32 data_size;
पूर्ण;

काष्ठा imx290 अणु
	काष्ठा device *dev;
	काष्ठा clk *xclk;
	काष्ठा regmap *regmap;
	u8 nlanes;
	u8 bpp;

	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt current_क्रमmat;
	स्थिर काष्ठा imx290_mode *current_mode;

	काष्ठा regulator_bulk_data supplies[IMX290_NUM_SUPPLIES];
	काष्ठा gpio_desc *rst_gpio;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate;

	काष्ठा mutex lock;
पूर्ण;

काष्ठा imx290_pixfmt अणु
	u32 code;
	u8 bpp;
पूर्ण;

अटल स्थिर काष्ठा imx290_pixfmt imx290_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, 10 पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, 12 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config imx290_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर अक्षर * स्थिर imx290_test_pattern_menu[] = अणु
	"Disabled",
	"Sequence Pattern 1",
	"Horizontal Color-bar Chart",
	"Vertical Color-bar Chart",
	"Sequence Pattern 2",
	"Gradation Pattern 1",
	"Gradation Pattern 2",
	"000/555h Toggle Pattern",
पूर्ण;

अटल स्थिर काष्ठा imx290_regval imx290_global_init_settings[] = अणु
	अणु 0x3007, 0x00 पूर्ण,
	अणु 0x3018, 0x65 पूर्ण,
	अणु 0x3019, 0x04 पूर्ण,
	अणु 0x301a, 0x00 पूर्ण,
	अणु 0x3444, 0x20 पूर्ण,
	अणु 0x3445, 0x25 पूर्ण,
	अणु 0x303a, 0x0c पूर्ण,
	अणु 0x3040, 0x00 पूर्ण,
	अणु 0x3041, 0x00 पूर्ण,
	अणु 0x303c, 0x00 पूर्ण,
	अणु 0x303d, 0x00 पूर्ण,
	अणु 0x3042, 0x9c पूर्ण,
	अणु 0x3043, 0x07 पूर्ण,
	अणु 0x303e, 0x49 पूर्ण,
	अणु 0x303f, 0x04 पूर्ण,
	अणु 0x304b, 0x0a पूर्ण,
	अणु 0x300f, 0x00 पूर्ण,
	अणु 0x3010, 0x21 पूर्ण,
	अणु 0x3012, 0x64 पूर्ण,
	अणु 0x3016, 0x09 पूर्ण,
	अणु 0x3070, 0x02 पूर्ण,
	अणु 0x3071, 0x11 पूर्ण,
	अणु 0x309b, 0x10 पूर्ण,
	अणु 0x309c, 0x22 पूर्ण,
	अणु 0x30a2, 0x02 पूर्ण,
	अणु 0x30a6, 0x20 पूर्ण,
	अणु 0x30a8, 0x20 पूर्ण,
	अणु 0x30aa, 0x20 पूर्ण,
	अणु 0x30ac, 0x20 पूर्ण,
	अणु 0x30b0, 0x43 पूर्ण,
	अणु 0x3119, 0x9e पूर्ण,
	अणु 0x311c, 0x1e पूर्ण,
	अणु 0x311e, 0x08 पूर्ण,
	अणु 0x3128, 0x05 पूर्ण,
	अणु 0x313d, 0x83 पूर्ण,
	अणु 0x3150, 0x03 पूर्ण,
	अणु 0x317e, 0x00 पूर्ण,
	अणु 0x32b8, 0x50 पूर्ण,
	अणु 0x32b9, 0x10 पूर्ण,
	अणु 0x32ba, 0x00 पूर्ण,
	अणु 0x32bb, 0x04 पूर्ण,
	अणु 0x32c8, 0x50 पूर्ण,
	अणु 0x32c9, 0x10 पूर्ण,
	अणु 0x32ca, 0x00 पूर्ण,
	अणु 0x32cb, 0x04 पूर्ण,
	अणु 0x332c, 0xd3 पूर्ण,
	अणु 0x332d, 0x10 पूर्ण,
	अणु 0x332e, 0x0d पूर्ण,
	अणु 0x3358, 0x06 पूर्ण,
	अणु 0x3359, 0xe1 पूर्ण,
	अणु 0x335a, 0x11 पूर्ण,
	अणु 0x3360, 0x1e पूर्ण,
	अणु 0x3361, 0x61 पूर्ण,
	अणु 0x3362, 0x10 पूर्ण,
	अणु 0x33b0, 0x50 पूर्ण,
	अणु 0x33b2, 0x1a पूर्ण,
	अणु 0x33b3, 0x04 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx290_regval imx290_1080p_settings[] = अणु
	/* mode settings */
	अणु 0x3007, 0x00 पूर्ण,
	अणु 0x303a, 0x0c पूर्ण,
	अणु 0x3414, 0x0a पूर्ण,
	अणु 0x3472, 0x80 पूर्ण,
	अणु 0x3473, 0x07 पूर्ण,
	अणु 0x3418, 0x38 पूर्ण,
	अणु 0x3419, 0x04 पूर्ण,
	अणु 0x3012, 0x64 पूर्ण,
	अणु 0x3013, 0x00 पूर्ण,
	अणु 0x305c, 0x18 पूर्ण,
	अणु 0x305d, 0x03 पूर्ण,
	अणु 0x305e, 0x20 पूर्ण,
	अणु 0x305f, 0x01 पूर्ण,
	अणु 0x315e, 0x1a पूर्ण,
	अणु 0x3164, 0x1a पूर्ण,
	अणु 0x3480, 0x49 पूर्ण,
	/* data rate settings */
	अणु 0x3405, 0x10 पूर्ण,
	अणु 0x3446, 0x57 पूर्ण,
	अणु 0x3447, 0x00 पूर्ण,
	अणु 0x3448, 0x37 पूर्ण,
	अणु 0x3449, 0x00 पूर्ण,
	अणु 0x344a, 0x1f पूर्ण,
	अणु 0x344b, 0x00 पूर्ण,
	अणु 0x344c, 0x1f पूर्ण,
	अणु 0x344d, 0x00 पूर्ण,
	अणु 0x344e, 0x1f पूर्ण,
	अणु 0x344f, 0x00 पूर्ण,
	अणु 0x3450, 0x77 पूर्ण,
	अणु 0x3451, 0x00 पूर्ण,
	अणु 0x3452, 0x1f पूर्ण,
	अणु 0x3453, 0x00 पूर्ण,
	अणु 0x3454, 0x17 पूर्ण,
	अणु 0x3455, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx290_regval imx290_720p_settings[] = अणु
	/* mode settings */
	अणु 0x3007, 0x10 पूर्ण,
	अणु 0x303a, 0x06 पूर्ण,
	अणु 0x3414, 0x04 पूर्ण,
	अणु 0x3472, 0x00 पूर्ण,
	अणु 0x3473, 0x05 पूर्ण,
	अणु 0x3418, 0xd0 पूर्ण,
	अणु 0x3419, 0x02 पूर्ण,
	अणु 0x3012, 0x64 पूर्ण,
	अणु 0x3013, 0x00 पूर्ण,
	अणु 0x305c, 0x20 पूर्ण,
	अणु 0x305d, 0x00 पूर्ण,
	अणु 0x305e, 0x20 पूर्ण,
	अणु 0x305f, 0x01 पूर्ण,
	अणु 0x315e, 0x1a पूर्ण,
	अणु 0x3164, 0x1a पूर्ण,
	अणु 0x3480, 0x49 पूर्ण,
	/* data rate settings */
	अणु 0x3405, 0x10 पूर्ण,
	अणु 0x3446, 0x4f पूर्ण,
	अणु 0x3447, 0x00 पूर्ण,
	अणु 0x3448, 0x2f पूर्ण,
	अणु 0x3449, 0x00 पूर्ण,
	अणु 0x344a, 0x17 पूर्ण,
	अणु 0x344b, 0x00 पूर्ण,
	अणु 0x344c, 0x17 पूर्ण,
	अणु 0x344d, 0x00 पूर्ण,
	अणु 0x344e, 0x17 पूर्ण,
	अणु 0x344f, 0x00 पूर्ण,
	अणु 0x3450, 0x57 पूर्ण,
	अणु 0x3451, 0x00 पूर्ण,
	अणु 0x3452, 0x17 पूर्ण,
	अणु 0x3453, 0x00 पूर्ण,
	अणु 0x3454, 0x17 पूर्ण,
	अणु 0x3455, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx290_regval imx290_10bit_settings[] = अणु
	अणु 0x3005, 0x00पूर्ण,
	अणु 0x3046, 0x00पूर्ण,
	अणु 0x3129, 0x1dपूर्ण,
	अणु 0x317c, 0x12पूर्ण,
	अणु 0x31ec, 0x37पूर्ण,
	अणु 0x3441, 0x0aपूर्ण,
	अणु 0x3442, 0x0aपूर्ण,
	अणु 0x300a, 0x3cपूर्ण,
	अणु 0x300b, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx290_regval imx290_12bit_settings[] = अणु
	अणु 0x3005, 0x01 पूर्ण,
	अणु 0x3046, 0x01 पूर्ण,
	अणु 0x3129, 0x00 पूर्ण,
	अणु 0x317c, 0x00 पूर्ण,
	अणु 0x31ec, 0x0e पूर्ण,
	अणु 0x3441, 0x0c पूर्ण,
	अणु 0x3442, 0x0c पूर्ण,
	अणु 0x300a, 0xf0 पूर्ण,
	अणु 0x300b, 0x00 पूर्ण,
पूर्ण;

/* supported link frequencies */
#घोषणा FREQ_INDEX_1080P	0
#घोषणा FREQ_INDEX_720P		1
अटल स्थिर s64 imx290_link_freq_2lanes[] = अणु
	[FREQ_INDEX_1080P] = 445500000,
	[FREQ_INDEX_720P] = 297000000,
पूर्ण;
अटल स्थिर s64 imx290_link_freq_4lanes[] = अणु
	[FREQ_INDEX_1080P] = 222750000,
	[FREQ_INDEX_720P] = 148500000,
पूर्ण;

/*
 * In this function and in the similar ones below We rely on imx290_probe()
 * to ensure that nlanes is either 2 or 4.
 */
अटल अंतरभूत स्थिर s64 *imx290_link_freqs_ptr(स्थिर काष्ठा imx290 *imx290)
अणु
	अगर (imx290->nlanes == 2)
		वापस imx290_link_freq_2lanes;
	अन्यथा
		वापस imx290_link_freq_4lanes;
पूर्ण

अटल अंतरभूत पूर्णांक imx290_link_freqs_num(स्थिर काष्ठा imx290 *imx290)
अणु
	अगर (imx290->nlanes == 2)
		वापस ARRAY_SIZE(imx290_link_freq_2lanes);
	अन्यथा
		वापस ARRAY_SIZE(imx290_link_freq_4lanes);
पूर्ण

/* Mode configs */
अटल स्थिर काष्ठा imx290_mode imx290_modes_2lanes[] = अणु
	अणु
		.width = 1920,
		.height = 1080,
		.hmax = 0x1130,
		.link_freq_index = FREQ_INDEX_1080P,
		.data = imx290_1080p_settings,
		.data_size = ARRAY_SIZE(imx290_1080p_settings),
	पूर्ण,
	अणु
		.width = 1280,
		.height = 720,
		.hmax = 0x19c8,
		.link_freq_index = FREQ_INDEX_720P,
		.data = imx290_720p_settings,
		.data_size = ARRAY_SIZE(imx290_720p_settings),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx290_mode imx290_modes_4lanes[] = अणु
	अणु
		.width = 1920,
		.height = 1080,
		.hmax = 0x0898,
		.link_freq_index = FREQ_INDEX_1080P,
		.data = imx290_1080p_settings,
		.data_size = ARRAY_SIZE(imx290_1080p_settings),
	पूर्ण,
	अणु
		.width = 1280,
		.height = 720,
		.hmax = 0x0ce4,
		.link_freq_index = FREQ_INDEX_720P,
		.data = imx290_720p_settings,
		.data_size = ARRAY_SIZE(imx290_720p_settings),
	पूर्ण,
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा imx290_mode *imx290_modes_ptr(स्थिर काष्ठा imx290 *imx290)
अणु
	अगर (imx290->nlanes == 2)
		वापस imx290_modes_2lanes;
	अन्यथा
		वापस imx290_modes_4lanes;
पूर्ण

अटल अंतरभूत पूर्णांक imx290_modes_num(स्थिर काष्ठा imx290 *imx290)
अणु
	अगर (imx290->nlanes == 2)
		वापस ARRAY_SIZE(imx290_modes_2lanes);
	अन्यथा
		वापस ARRAY_SIZE(imx290_modes_4lanes);
पूर्ण

अटल अंतरभूत काष्ठा imx290 *to_imx290(काष्ठा v4l2_subdev *_sd)
अणु
	वापस container_of(_sd, काष्ठा imx290, sd);
पूर्ण

अटल अंतरभूत पूर्णांक imx290_पढ़ो_reg(काष्ठा imx290 *imx290, u16 addr, u8 *value)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(imx290->regmap, addr, &regval);
	अगर (ret) अणु
		dev_err(imx290->dev, "I2C read failed for addr: %x\n", addr);
		वापस ret;
	पूर्ण

	*value = regval & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_ग_लिखो_reg(काष्ठा imx290 *imx290, u16 addr, u8 value)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(imx290->regmap, addr, value);
	अगर (ret) अणु
		dev_err(imx290->dev, "I2C write failed for addr: %x\n", addr);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx290_set_रेजिस्टर_array(काष्ठा imx290 *imx290,
				     स्थिर काष्ठा imx290_regval *settings,
				     अचिन्हित पूर्णांक num_settings)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_settings; ++i, ++settings) अणु
		ret = imx290_ग_लिखो_reg(imx290, settings->reg, settings->val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Provide 10ms settle समय */
	usleep_range(10000, 11000);

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_ग_लिखो_buffered_reg(काष्ठा imx290 *imx290, u16 address_low,
				     u8 nr_regs, u32 value)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = imx290_ग_लिखो_reg(imx290, IMX290_REGHOLD, 0x01);
	अगर (ret) अणु
		dev_err(imx290->dev, "Error setting hold register\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < nr_regs; i++) अणु
		ret = imx290_ग_लिखो_reg(imx290, address_low + i,
				       (u8)(value >> (i * 8)));
		अगर (ret) अणु
			dev_err(imx290->dev, "Error writing buffered registers\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = imx290_ग_लिखो_reg(imx290, IMX290_REGHOLD, 0x00);
	अगर (ret) अणु
		dev_err(imx290->dev, "Error setting hold register\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx290_set_gain(काष्ठा imx290 *imx290, u32 value)
अणु
	पूर्णांक ret;

	ret = imx290_ग_लिखो_buffered_reg(imx290, IMX290_GAIN, 1, value);
	अगर (ret)
		dev_err(imx290->dev, "Unable to write gain\n");

	वापस ret;
पूर्ण

/* Stop streaming */
अटल पूर्णांक imx290_stop_streaming(काष्ठा imx290 *imx290)
अणु
	पूर्णांक ret;

	ret = imx290_ग_लिखो_reg(imx290, IMX290_STANDBY, 0x01);
	अगर (ret < 0)
		वापस ret;

	msleep(30);

	वापस imx290_ग_लिखो_reg(imx290, IMX290_XMSTA, 0x01);
पूर्ण

अटल पूर्णांक imx290_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा imx290 *imx290 = container_of(ctrl->handler,
					     काष्ठा imx290, ctrls);
	पूर्णांक ret = 0;

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(imx290->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		ret = imx290_set_gain(imx290, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		अगर (ctrl->val) अणु
			imx290_ग_लिखो_reg(imx290, IMX290_BLKLEVEL_LOW, 0x00);
			imx290_ग_लिखो_reg(imx290, IMX290_BLKLEVEL_HIGH, 0x00);
			usleep_range(10000, 11000);
			imx290_ग_लिखो_reg(imx290, IMX290_PGCTRL,
					 (u8)(IMX290_PGCTRL_REGEN |
					 IMX290_PGCTRL_THRU |
					 IMX290_PGCTRL_MODE(ctrl->val)));
		पूर्ण अन्यथा अणु
			imx290_ग_लिखो_reg(imx290, IMX290_PGCTRL, 0x00);
			usleep_range(10000, 11000);
			अगर (imx290->bpp == 10)
				imx290_ग_लिखो_reg(imx290, IMX290_BLKLEVEL_LOW,
						 0x3c);
			अन्यथा /* 12 bits per pixel */
				imx290_ग_लिखो_reg(imx290, IMX290_BLKLEVEL_LOW,
						 0xf0);
			imx290_ग_लिखो_reg(imx290, IMX290_BLKLEVEL_HIGH, 0x00);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(imx290->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops imx290_ctrl_ops = अणु
	.s_ctrl = imx290_set_ctrl,
पूर्ण;

अटल पूर्णांक imx290_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(imx290_क्रमmats))
		वापस -EINVAL;

	code->code = imx290_क्रमmats[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	स्थिर काष्ठा imx290 *imx290 = to_imx290(sd);
	स्थिर काष्ठा imx290_mode *imx290_modes = imx290_modes_ptr(imx290);

	अगर ((fse->code != imx290_क्रमmats[0].code) &&
	    (fse->code != imx290_क्रमmats[1].code))
		वापस -EINVAL;

	अगर (fse->index >= imx290_modes_num(imx290))
		वापस -EINVAL;

	fse->min_width = imx290_modes[fse->index].width;
	fse->max_width = imx290_modes[fse->index].width;
	fse->min_height = imx290_modes[fse->index].height;
	fse->max_height = imx290_modes[fse->index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx290 *imx290 = to_imx290(sd);
	काष्ठा v4l2_mbus_framefmt *framefmt;

	mutex_lock(&imx290->lock);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		framefmt = v4l2_subdev_get_try_क्रमmat(&imx290->sd, cfg,
						      fmt->pad);
	अन्यथा
		framefmt = &imx290->current_क्रमmat;

	fmt->क्रमmat = *framefmt;

	mutex_unlock(&imx290->lock);

	वापस 0;
पूर्ण

अटल अंतरभूत u8 imx290_get_link_freq_index(काष्ठा imx290 *imx290)
अणु
	वापस imx290->current_mode->link_freq_index;
पूर्ण

अटल s64 imx290_get_link_freq(काष्ठा imx290 *imx290)
अणु
	u8 index = imx290_get_link_freq_index(imx290);

	वापस *(imx290_link_freqs_ptr(imx290) + index);
पूर्ण

अटल u64 imx290_calc_pixel_rate(काष्ठा imx290 *imx290)
अणु
	s64 link_freq = imx290_get_link_freq(imx290);
	u8 nlanes = imx290->nlanes;
	u64 pixel_rate;

	/* pixel rate = link_freq * 2 * nr_of_lanes / bits_per_sample */
	pixel_rate = link_freq * 2 * nlanes;
	करो_भाग(pixel_rate, imx290->bpp);
	वापस pixel_rate;
पूर्ण

अटल पूर्णांक imx290_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
		      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा imx290 *imx290 = to_imx290(sd);
	स्थिर काष्ठा imx290_mode *mode;
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	अचिन्हित पूर्णांक i;

	mutex_lock(&imx290->lock);

	mode = v4l2_find_nearest_size(imx290_modes_ptr(imx290),
				      imx290_modes_num(imx290), width, height,
				      fmt->क्रमmat.width, fmt->क्रमmat.height);

	fmt->क्रमmat.width = mode->width;
	fmt->क्रमmat.height = mode->height;

	क्रम (i = 0; i < ARRAY_SIZE(imx290_क्रमmats); i++)
		अगर (imx290_क्रमmats[i].code == fmt->क्रमmat.code)
			अवरोध;

	अगर (i >= ARRAY_SIZE(imx290_क्रमmats))
		i = 0;

	fmt->क्रमmat.code = imx290_क्रमmats[i].code;
	fmt->क्रमmat.field = V4L2_FIELD_NONE;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
	पूर्ण अन्यथा अणु
		क्रमmat = &imx290->current_क्रमmat;
		imx290->current_mode = mode;
		imx290->bpp = imx290_क्रमmats[i].bpp;

		अगर (imx290->link_freq)
			__v4l2_ctrl_s_ctrl(imx290->link_freq,
					   imx290_get_link_freq_index(imx290));
		अगर (imx290->pixel_rate)
			__v4l2_ctrl_s_ctrl_पूर्णांक64(imx290->pixel_rate,
						 imx290_calc_pixel_rate(imx290));
	पूर्ण

	*क्रमmat = fmt->क्रमmat;

	mutex_unlock(&imx290->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_entity_init_cfg(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु 0 पूर्ण;

	fmt.which = cfg ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	fmt.क्रमmat.width = 1920;
	fmt.क्रमmat.height = 1080;

	imx290_set_fmt(subdev, cfg, &fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_ग_लिखो_current_क्रमmat(काष्ठा imx290 *imx290)
अणु
	पूर्णांक ret;

	चयन (imx290->current_क्रमmat.code) अणु
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
		ret = imx290_set_रेजिस्टर_array(imx290, imx290_10bit_settings,
						ARRAY_SIZE(
							imx290_10bit_settings));
		अगर (ret < 0) अणु
			dev_err(imx290->dev, "Could not set format registers\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल MEDIA_BUS_FMT_SRGGB12_1X12:
		ret = imx290_set_रेजिस्टर_array(imx290, imx290_12bit_settings,
						ARRAY_SIZE(
							imx290_12bit_settings));
		अगर (ret < 0) अणु
			dev_err(imx290->dev, "Could not set format registers\n");
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(imx290->dev, "Unknown pixel format\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_set_hmax(काष्ठा imx290 *imx290, u32 val)
अणु
	पूर्णांक ret;

	ret = imx290_ग_लिखो_reg(imx290, IMX290_HMAX_LOW, (val & 0xff));
	अगर (ret) अणु
		dev_err(imx290->dev, "Error setting HMAX register\n");
		वापस ret;
	पूर्ण

	ret = imx290_ग_लिखो_reg(imx290, IMX290_HMAX_HIGH, ((val >> 8) & 0xff));
	अगर (ret) अणु
		dev_err(imx290->dev, "Error setting HMAX register\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Start streaming */
अटल पूर्णांक imx290_start_streaming(काष्ठा imx290 *imx290)
अणु
	पूर्णांक ret;

	/* Set init रेजिस्टर settings */
	ret = imx290_set_रेजिस्टर_array(imx290, imx290_global_init_settings,
					ARRAY_SIZE(
						imx290_global_init_settings));
	अगर (ret < 0) अणु
		dev_err(imx290->dev, "Could not set init registers\n");
		वापस ret;
	पूर्ण

	/* Apply the रेजिस्टर values related to current frame क्रमmat */
	ret = imx290_ग_लिखो_current_क्रमmat(imx290);
	अगर (ret < 0) अणु
		dev_err(imx290->dev, "Could not set frame format\n");
		वापस ret;
	पूर्ण

	/* Apply शेष values of current mode */
	ret = imx290_set_रेजिस्टर_array(imx290, imx290->current_mode->data,
					imx290->current_mode->data_size);
	अगर (ret < 0) अणु
		dev_err(imx290->dev, "Could not set current mode\n");
		वापस ret;
	पूर्ण
	ret = imx290_set_hmax(imx290, imx290->current_mode->hmax);
	अगर (ret < 0)
		वापस ret;

	/* Apply customized values from user */
	ret = v4l2_ctrl_handler_setup(imx290->sd.ctrl_handler);
	अगर (ret) अणु
		dev_err(imx290->dev, "Could not sync v4l2 controls\n");
		वापस ret;
	पूर्ण

	ret = imx290_ग_लिखो_reg(imx290, IMX290_STANDBY, 0x00);
	अगर (ret < 0)
		वापस ret;

	msleep(30);

	/* Start streaming */
	वापस imx290_ग_लिखो_reg(imx290, IMX290_XMSTA, 0x00);
पूर्ण

अटल पूर्णांक imx290_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx290 *imx290 = to_imx290(sd);
	पूर्णांक ret = 0;

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(imx290->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(imx290->dev);
			जाओ unlock_and_वापस;
		पूर्ण

		ret = imx290_start_streaming(imx290);
		अगर (ret) अणु
			dev_err(imx290->dev, "Start stream failed\n");
			pm_runसमय_put(imx290->dev);
			जाओ unlock_and_वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		imx290_stop_streaming(imx290);
		pm_runसमय_put(imx290->dev);
	पूर्ण

unlock_and_वापस:

	वापस ret;
पूर्ण

अटल पूर्णांक imx290_get_regulators(काष्ठा device *dev, काष्ठा imx290 *imx290)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IMX290_NUM_SUPPLIES; i++)
		imx290->supplies[i].supply = imx290_supply_name[i];

	वापस devm_regulator_bulk_get(dev, IMX290_NUM_SUPPLIES,
				       imx290->supplies);
पूर्ण

अटल पूर्णांक imx290_set_data_lanes(काष्ठा imx290 *imx290)
अणु
	पूर्णांक ret = 0, laneval, frsel;

	चयन (imx290->nlanes) अणु
	हाल 2:
		laneval = 0x01;
		frsel = 0x02;
		अवरोध;
	हाल 4:
		laneval = 0x03;
		frsel = 0x01;
		अवरोध;
	शेष:
		/*
		 * We should never hit this since the data lane count is
		 * validated in probe itself
		 */
		dev_err(imx290->dev, "Lane configuration not supported\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	ret = imx290_ग_लिखो_reg(imx290, IMX290_PHY_LANE_NUM, laneval);
	अगर (ret) अणु
		dev_err(imx290->dev, "Error setting Physical Lane number register\n");
		जाओ निकास;
	पूर्ण

	ret = imx290_ग_लिखो_reg(imx290, IMX290_CSI_LANE_MODE, laneval);
	अगर (ret) अणु
		dev_err(imx290->dev, "Error setting CSI Lane mode register\n");
		जाओ निकास;
	पूर्ण

	ret = imx290_ग_लिखो_reg(imx290, IMX290_FR_FDG_SEL, frsel);
	अगर (ret)
		dev_err(imx290->dev, "Error setting FR/FDG SEL register\n");

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक imx290_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx290 *imx290 = to_imx290(sd);
	पूर्णांक ret;

	ret = clk_prepare_enable(imx290->xclk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(IMX290_NUM_SUPPLIES, imx290->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable regulators\n");
		clk_disable_unprepare(imx290->xclk);
		वापस ret;
	पूर्ण

	usleep_range(1, 2);
	gpiod_set_value_cansleep(imx290->rst_gpio, 0);
	usleep_range(30000, 31000);

	/* Set data lane count */
	imx290_set_data_lanes(imx290);

	वापस 0;
पूर्ण

अटल पूर्णांक imx290_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा imx290 *imx290 = to_imx290(sd);

	clk_disable_unprepare(imx290->xclk);
	gpiod_set_value_cansleep(imx290->rst_gpio, 1);
	regulator_bulk_disable(IMX290_NUM_SUPPLIES, imx290->supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx290_pm_ops = अणु
	SET_RUNTIME_PM_OPS(imx290_घातer_off, imx290_घातer_on, शून्य)
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops imx290_video_ops = अणु
	.s_stream = imx290_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops imx290_pad_ops = अणु
	.init_cfg = imx290_entity_init_cfg,
	.क्रमागत_mbus_code = imx290_क्रमागत_mbus_code,
	.क्रमागत_frame_size = imx290_क्रमागत_frame_size,
	.get_fmt = imx290_get_fmt,
	.set_fmt = imx290_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops imx290_subdev_ops = अणु
	.video = &imx290_video_ops,
	.pad = &imx290_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations imx290_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
 * Returns 0 अगर all link frequencies used by the driver क्रम the given number
 * of MIPI data lanes are mentioned in the device tree, or the value of the
 * first missing frequency otherwise.
 */
अटल s64 imx290_check_link_freqs(स्थिर काष्ठा imx290 *imx290,
				   स्थिर काष्ठा v4l2_fwnode_endpoपूर्णांक *ep)
अणु
	पूर्णांक i, j;
	स्थिर s64 *freqs = imx290_link_freqs_ptr(imx290);
	पूर्णांक freqs_count = imx290_link_freqs_num(imx290);

	क्रम (i = 0; i < freqs_count; i++) अणु
		क्रम (j = 0; j < ep->nr_of_link_frequencies; j++)
			अगर (freqs[i] == ep->link_frequencies[j])
				अवरोध;
		अगर (j == ep->nr_of_link_frequencies)
			वापस freqs[i];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक imx290_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा fwnode_handle *endpoपूर्णांक;
	/* Only CSI2 is supported क्रम now: */
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	काष्ठा imx290 *imx290;
	u32 xclk_freq;
	s64 fq;
	पूर्णांक ret;

	imx290 = devm_kzalloc(dev, माप(*imx290), GFP_KERNEL);
	अगर (!imx290)
		वापस -ENOMEM;

	imx290->dev = dev;
	imx290->regmap = devm_regmap_init_i2c(client, &imx290_regmap_config);
	अगर (IS_ERR(imx290->regmap)) अणु
		dev_err(dev, "Unable to initialize I2C\n");
		वापस -ENODEV;
	पूर्ण

	endpoपूर्णांक = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(dev), शून्य);
	अगर (!endpoपूर्णांक) अणु
		dev_err(dev, "Endpoint node not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(endpoपूर्णांक, &ep);
	fwnode_handle_put(endpoपूर्णांक);
	अगर (ret == -ENXIO) अणु
		dev_err(dev, "Unsupported bus type, should be CSI2\n");
		जाओ मुक्त_err;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_err(dev, "Parsing endpoint node failed\n");
		जाओ मुक्त_err;
	पूर्ण

	/* Get number of data lanes */
	imx290->nlanes = ep.bus.mipi_csi2.num_data_lanes;
	अगर (imx290->nlanes != 2 && imx290->nlanes != 4) अणु
		dev_err(dev, "Invalid data lanes: %d\n", imx290->nlanes);
		ret = -EINVAL;
		जाओ मुक्त_err;
	पूर्ण

	dev_dbg(dev, "Using %u data lanes\n", imx290->nlanes);

	अगर (!ep.nr_of_link_frequencies) अणु
		dev_err(dev, "link-frequency property not found in DT\n");
		ret = -EINVAL;
		जाओ मुक्त_err;
	पूर्ण

	/* Check that link frequences क्रम all the modes are in device tree */
	fq = imx290_check_link_freqs(imx290, &ep);
	अगर (fq) अणु
		dev_err(dev, "Link frequency of %lld is not supported\n", fq);
		ret = -EINVAL;
		जाओ मुक्त_err;
	पूर्ण

	/* get प्रणाली घड़ी (xclk) */
	imx290->xclk = devm_clk_get(dev, "xclk");
	अगर (IS_ERR(imx290->xclk)) अणु
		dev_err(dev, "Could not get xclk");
		ret = PTR_ERR(imx290->xclk);
		जाओ मुक्त_err;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(dev_fwnode(dev), "clock-frequency",
				       &xclk_freq);
	अगर (ret) अणु
		dev_err(dev, "Could not get xclk frequency\n");
		जाओ मुक्त_err;
	पूर्ण

	/* बाह्यal घड़ी must be 37.125 MHz */
	अगर (xclk_freq != 37125000) अणु
		dev_err(dev, "External clock frequency %u is not supported\n",
			xclk_freq);
		ret = -EINVAL;
		जाओ मुक्त_err;
	पूर्ण

	ret = clk_set_rate(imx290->xclk, xclk_freq);
	अगर (ret) अणु
		dev_err(dev, "Could not set xclk frequency\n");
		जाओ मुक्त_err;
	पूर्ण

	ret = imx290_get_regulators(dev, imx290);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot get regulators\n");
		जाओ मुक्त_err;
	पूर्ण

	imx290->rst_gpio = devm_gpiod_get_optional(dev, "reset",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(imx290->rst_gpio)) अणु
		dev_err(dev, "Cannot get reset gpio\n");
		ret = PTR_ERR(imx290->rst_gpio);
		जाओ मुक्त_err;
	पूर्ण

	mutex_init(&imx290->lock);

	/*
	 * Initialize the frame क्रमmat. In particular, imx290->current_mode
	 * and imx290->bpp are set to शेषs: imx290_calc_pixel_rate() call
	 * below relies on these fields.
	 */
	imx290_entity_init_cfg(&imx290->sd, शून्य);

	v4l2_ctrl_handler_init(&imx290->ctrls, 4);

	v4l2_ctrl_new_std(&imx290->ctrls, &imx290_ctrl_ops,
			  V4L2_CID_GAIN, 0, 72, 1, 0);

	imx290->link_freq =
		v4l2_ctrl_new_पूर्णांक_menu(&imx290->ctrls, &imx290_ctrl_ops,
				       V4L2_CID_LINK_FREQ,
				       imx290_link_freqs_num(imx290) - 1, 0,
				       imx290_link_freqs_ptr(imx290));
	अगर (imx290->link_freq)
		imx290->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	imx290->pixel_rate = v4l2_ctrl_new_std(&imx290->ctrls, &imx290_ctrl_ops,
					       V4L2_CID_PIXEL_RATE,
					       1, पूर्णांक_उच्च, 1,
					       imx290_calc_pixel_rate(imx290));

	v4l2_ctrl_new_std_menu_items(&imx290->ctrls, &imx290_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(imx290_test_pattern_menu) - 1,
				     0, 0, imx290_test_pattern_menu);

	imx290->sd.ctrl_handler = &imx290->ctrls;

	अगर (imx290->ctrls.error) अणु
		dev_err(dev, "Control initialization error %d\n",
			imx290->ctrls.error);
		ret = imx290->ctrls.error;
		जाओ मुक्त_ctrl;
	पूर्ण

	v4l2_i2c_subdev_init(&imx290->sd, client, &imx290_subdev_ops);
	imx290->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	imx290->sd.dev = &client->dev;
	imx290->sd.entity.ops = &imx290_subdev_entity_ops;
	imx290->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	imx290->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&imx290->sd.entity, 1, &imx290->pad);
	अगर (ret < 0) अणु
		dev_err(dev, "Could not register media entity\n");
		जाओ मुक्त_ctrl;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev(&imx290->sd);
	अगर (ret < 0) अणु
		dev_err(dev, "Could not register v4l2 device\n");
		जाओ मुक्त_entity;
	पूर्ण

	/* Power on the device to match runसमय PM state below */
	ret = imx290_घातer_on(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Could not power on the device\n");
		जाओ मुक्त_entity;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	v4l2_fwnode_endpoपूर्णांक_मुक्त(&ep);

	वापस 0;

मुक्त_entity:
	media_entity_cleanup(&imx290->sd.entity);
मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&imx290->ctrls);
	mutex_destroy(&imx290->lock);
मुक्त_err:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&ep);

	वापस ret;
पूर्ण

अटल पूर्णांक imx290_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा imx290 *imx290 = to_imx290(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);

	mutex_destroy(&imx290->lock);

	pm_runसमय_disable(imx290->dev);
	अगर (!pm_runसमय_status_suspended(imx290->dev))
		imx290_घातer_off(imx290->dev);
	pm_runसमय_set_suspended(imx290->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx290_of_match[] = अणु
	अणु .compatible = "sony,imx290" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx290_of_match);

अटल काष्ठा i2c_driver imx290_i2c_driver = अणु
	.probe_new  = imx290_probe,
	.हटाओ = imx290_हटाओ,
	.driver = अणु
		.name  = "imx290",
		.pm = &imx290_pm_ops,
		.of_match_table = of_match_ptr(imx290_of_match),
	पूर्ण,
पूर्ण;

module_i2c_driver(imx290_i2c_driver);

MODULE_DESCRIPTION("Sony IMX290 CMOS Image Sensor Driver");
MODULE_AUTHOR("FRAMOS GmbH");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_LICENSE("GPL v2");
