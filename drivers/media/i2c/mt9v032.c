<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MT9V022, MT9V024, MT9V032, and MT9V034 CMOS Image Sensors
 *
 * Copyright (C) 2010, Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *
 * Based on the MT9M001 driver,
 *
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/log2.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/module.h>

#समावेश <media/i2c/mt9v032.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>

/* The first four rows are black rows. The active area spans 753x481 pixels. */
#घोषणा MT9V032_PIXEL_ARRAY_HEIGHT			485
#घोषणा MT9V032_PIXEL_ARRAY_WIDTH			753

#घोषणा MT9V032_SYSCLK_FREQ_DEF				26600000

#घोषणा MT9V032_CHIP_VERSION				0x00
#घोषणा		MT9V032_CHIP_ID_REV1			0x1311
#घोषणा		MT9V032_CHIP_ID_REV3			0x1313
#घोषणा		MT9V034_CHIP_ID_REV1			0X1324
#घोषणा MT9V032_COLUMN_START				0x01
#घोषणा		MT9V032_COLUMN_START_MIN		1
#घोषणा		MT9V032_COLUMN_START_DEF		1
#घोषणा		MT9V032_COLUMN_START_MAX		752
#घोषणा MT9V032_ROW_START				0x02
#घोषणा		MT9V032_ROW_START_MIN			4
#घोषणा		MT9V032_ROW_START_DEF			5
#घोषणा		MT9V032_ROW_START_MAX			482
#घोषणा MT9V032_WINDOW_HEIGHT				0x03
#घोषणा		MT9V032_WINDOW_HEIGHT_MIN		1
#घोषणा		MT9V032_WINDOW_HEIGHT_DEF		480
#घोषणा		MT9V032_WINDOW_HEIGHT_MAX		480
#घोषणा MT9V032_WINDOW_WIDTH				0x04
#घोषणा		MT9V032_WINDOW_WIDTH_MIN		1
#घोषणा		MT9V032_WINDOW_WIDTH_DEF		752
#घोषणा		MT9V032_WINDOW_WIDTH_MAX		752
#घोषणा MT9V032_HORIZONTAL_BLANKING			0x05
#घोषणा		MT9V032_HORIZONTAL_BLANKING_MIN		43
#घोषणा		MT9V034_HORIZONTAL_BLANKING_MIN		61
#घोषणा		MT9V032_HORIZONTAL_BLANKING_DEF		94
#घोषणा		MT9V032_HORIZONTAL_BLANKING_MAX		1023
#घोषणा MT9V032_VERTICAL_BLANKING			0x06
#घोषणा		MT9V032_VERTICAL_BLANKING_MIN		4
#घोषणा		MT9V034_VERTICAL_BLANKING_MIN		2
#घोषणा		MT9V032_VERTICAL_BLANKING_DEF		45
#घोषणा		MT9V032_VERTICAL_BLANKING_MAX		3000
#घोषणा		MT9V034_VERTICAL_BLANKING_MAX		32288
#घोषणा MT9V032_CHIP_CONTROL				0x07
#घोषणा		MT9V032_CHIP_CONTROL_MASTER_MODE	(1 << 3)
#घोषणा		MT9V032_CHIP_CONTROL_DOUT_ENABLE	(1 << 7)
#घोषणा		MT9V032_CHIP_CONTROL_SEQUENTIAL		(1 << 8)
#घोषणा MT9V032_SHUTTER_WIDTH1				0x08
#घोषणा MT9V032_SHUTTER_WIDTH2				0x09
#घोषणा MT9V032_SHUTTER_WIDTH_CONTROL			0x0a
#घोषणा MT9V032_TOTAL_SHUTTER_WIDTH			0x0b
#घोषणा		MT9V032_TOTAL_SHUTTER_WIDTH_MIN		1
#घोषणा		MT9V034_TOTAL_SHUTTER_WIDTH_MIN		0
#घोषणा		MT9V032_TOTAL_SHUTTER_WIDTH_DEF		480
#घोषणा		MT9V032_TOTAL_SHUTTER_WIDTH_MAX		32767
#घोषणा		MT9V034_TOTAL_SHUTTER_WIDTH_MAX		32765
#घोषणा MT9V032_RESET					0x0c
#घोषणा MT9V032_READ_MODE				0x0d
#घोषणा		MT9V032_READ_MODE_ROW_BIN_MASK		(3 << 0)
#घोषणा		MT9V032_READ_MODE_ROW_BIN_SHIFT		0
#घोषणा		MT9V032_READ_MODE_COLUMN_BIN_MASK	(3 << 2)
#घोषणा		MT9V032_READ_MODE_COLUMN_BIN_SHIFT	2
#घोषणा		MT9V032_READ_MODE_ROW_FLIP		(1 << 4)
#घोषणा		MT9V032_READ_MODE_COLUMN_FLIP		(1 << 5)
#घोषणा		MT9V032_READ_MODE_DARK_COLUMNS		(1 << 6)
#घोषणा		MT9V032_READ_MODE_DARK_ROWS		(1 << 7)
#घोषणा		MT9V032_READ_MODE_RESERVED		0x0300
#घोषणा MT9V032_PIXEL_OPERATION_MODE			0x0f
#घोषणा		MT9V034_PIXEL_OPERATION_MODE_HDR	(1 << 0)
#घोषणा		MT9V034_PIXEL_OPERATION_MODE_COLOR	(1 << 1)
#घोषणा		MT9V032_PIXEL_OPERATION_MODE_COLOR	(1 << 2)
#घोषणा		MT9V032_PIXEL_OPERATION_MODE_HDR	(1 << 6)
#घोषणा MT9V032_ANALOG_GAIN				0x35
#घोषणा		MT9V032_ANALOG_GAIN_MIN			16
#घोषणा		MT9V032_ANALOG_GAIN_DEF			16
#घोषणा		MT9V032_ANALOG_GAIN_MAX			64
#घोषणा MT9V032_MAX_ANALOG_GAIN				0x36
#घोषणा		MT9V032_MAX_ANALOG_GAIN_MAX		127
#घोषणा MT9V032_FRAME_DARK_AVERAGE			0x42
#घोषणा MT9V032_DARK_AVG_THRESH				0x46
#घोषणा		MT9V032_DARK_AVG_LOW_THRESH_MASK	(255 << 0)
#घोषणा		MT9V032_DARK_AVG_LOW_THRESH_SHIFT	0
#घोषणा		MT9V032_DARK_AVG_HIGH_THRESH_MASK	(255 << 8)
#घोषणा		MT9V032_DARK_AVG_HIGH_THRESH_SHIFT	8
#घोषणा MT9V032_ROW_NOISE_CORR_CONTROL			0x70
#घोषणा		MT9V034_ROW_NOISE_CORR_ENABLE		(1 << 0)
#घोषणा		MT9V034_ROW_NOISE_CORR_USE_BLK_AVG	(1 << 1)
#घोषणा		MT9V032_ROW_NOISE_CORR_ENABLE		(1 << 5)
#घोषणा		MT9V032_ROW_NOISE_CORR_USE_BLK_AVG	(1 << 7)
#घोषणा MT9V032_PIXEL_CLOCK				0x74
#घोषणा MT9V034_PIXEL_CLOCK				0x72
#घोषणा		MT9V032_PIXEL_CLOCK_INV_LINE		(1 << 0)
#घोषणा		MT9V032_PIXEL_CLOCK_INV_FRAME		(1 << 1)
#घोषणा		MT9V032_PIXEL_CLOCK_XOR_LINE		(1 << 2)
#घोषणा		MT9V032_PIXEL_CLOCK_CONT_LINE		(1 << 3)
#घोषणा		MT9V032_PIXEL_CLOCK_INV_PXL_CLK		(1 << 4)
#घोषणा MT9V032_TEST_PATTERN				0x7f
#घोषणा		MT9V032_TEST_PATTERN_DATA_MASK		(1023 << 0)
#घोषणा		MT9V032_TEST_PATTERN_DATA_SHIFT		0
#घोषणा		MT9V032_TEST_PATTERN_USE_DATA		(1 << 10)
#घोषणा		MT9V032_TEST_PATTERN_GRAY_MASK		(3 << 11)
#घोषणा		MT9V032_TEST_PATTERN_GRAY_NONE		(0 << 11)
#घोषणा		MT9V032_TEST_PATTERN_GRAY_VERTICAL	(1 << 11)
#घोषणा		MT9V032_TEST_PATTERN_GRAY_HORIZONTAL	(2 << 11)
#घोषणा		MT9V032_TEST_PATTERN_GRAY_DIAGONAL	(3 << 11)
#घोषणा		MT9V032_TEST_PATTERN_ENABLE		(1 << 13)
#घोषणा		MT9V032_TEST_PATTERN_FLIP		(1 << 14)
#घोषणा MT9V032_AEGC_DESIRED_BIN			0xa5
#घोषणा MT9V032_AEC_UPDATE_FREQUENCY			0xa6
#घोषणा MT9V032_AEC_LPF					0xa8
#घोषणा MT9V032_AGC_UPDATE_FREQUENCY			0xa9
#घोषणा MT9V032_AGC_LPF					0xaa
#घोषणा MT9V032_AEC_AGC_ENABLE				0xaf
#घोषणा		MT9V032_AEC_ENABLE			(1 << 0)
#घोषणा		MT9V032_AGC_ENABLE			(1 << 1)
#घोषणा MT9V034_AEC_MAX_SHUTTER_WIDTH			0xad
#घोषणा MT9V032_AEC_MAX_SHUTTER_WIDTH			0xbd
#घोषणा MT9V032_THERMAL_INFO				0xc1

क्रमागत mt9v032_model अणु
	MT9V032_MODEL_V022_COLOR,	/* MT9V022IX7ATC */
	MT9V032_MODEL_V022_MONO,	/* MT9V022IX7ATM */
	MT9V032_MODEL_V024_COLOR,	/* MT9V024IA7XTC */
	MT9V032_MODEL_V024_MONO,	/* MT9V024IA7XTM */
	MT9V032_MODEL_V032_COLOR,	/* MT9V032C12STM */
	MT9V032_MODEL_V032_MONO,	/* MT9V032C12STC */
	MT9V032_MODEL_V034_COLOR,
	MT9V032_MODEL_V034_MONO,
पूर्ण;

काष्ठा mt9v032_model_version अणु
	अचिन्हित पूर्णांक version;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा mt9v032_model_data अणु
	अचिन्हित पूर्णांक min_row_समय;
	अचिन्हित पूर्णांक min_hblank;
	अचिन्हित पूर्णांक min_vblank;
	अचिन्हित पूर्णांक max_vblank;
	अचिन्हित पूर्णांक min_shutter;
	अचिन्हित पूर्णांक max_shutter;
	अचिन्हित पूर्णांक pclk_reg;
	अचिन्हित पूर्णांक aec_max_shutter_reg;
	स्थिर काष्ठा v4l2_ctrl_config * स्थिर aec_max_shutter_v4l2_ctrl;
पूर्ण;

काष्ठा mt9v032_model_info अणु
	स्थिर काष्ठा mt9v032_model_data *data;
	bool color;
पूर्ण;

अटल स्थिर काष्ठा mt9v032_model_version mt9v032_versions[] = अणु
	अणु MT9V032_CHIP_ID_REV1, "MT9V022/MT9V032 rev1/2" पूर्ण,
	अणु MT9V032_CHIP_ID_REV3, "MT9V022/MT9V032 rev3" पूर्ण,
	अणु MT9V034_CHIP_ID_REV1, "MT9V024/MT9V034 rev1" पूर्ण,
पूर्ण;

काष्ठा mt9v032 अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;

	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा v4l2_rect crop;
	अचिन्हित पूर्णांक hratio;
	अचिन्हित पूर्णांक vratio;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *link_freq;
		काष्ठा v4l2_ctrl *pixel_rate;
	पूर्ण;

	काष्ठा mutex घातer_lock;
	पूर्णांक घातer_count;

	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *standby_gpio;

	काष्ठा mt9v032_platक्रमm_data *pdata;
	स्थिर काष्ठा mt9v032_model_info *model;
	स्थिर काष्ठा mt9v032_model_version *version;

	u32 sysclk;
	u16 aec_agc;
	u16 hblank;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *test_pattern;
		काष्ठा v4l2_ctrl *test_pattern_color;
	पूर्ण;
पूर्ण;

अटल काष्ठा mt9v032 *to_mt9v032(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा mt9v032, subdev);
पूर्ण

अटल पूर्णांक
mt9v032_update_aec_agc(काष्ठा mt9v032 *mt9v032, u16 which, पूर्णांक enable)
अणु
	काष्ठा regmap *map = mt9v032->regmap;
	u16 value = mt9v032->aec_agc;
	पूर्णांक ret;

	अगर (enable)
		value |= which;
	अन्यथा
		value &= ~which;

	ret = regmap_ग_लिखो(map, MT9V032_AEC_AGC_ENABLE, value);
	अगर (ret < 0)
		वापस ret;

	mt9v032->aec_agc = value;
	वापस 0;
पूर्ण

अटल पूर्णांक
mt9v032_update_hblank(काष्ठा mt9v032 *mt9v032)
अणु
	काष्ठा v4l2_rect *crop = &mt9v032->crop;
	अचिन्हित पूर्णांक min_hblank = mt9v032->model->data->min_hblank;
	अचिन्हित पूर्णांक hblank;

	अगर (mt9v032->version->version == MT9V034_CHIP_ID_REV1)
		min_hblank += (mt9v032->hratio - 1) * 10;
	min_hblank = max_t(पूर्णांक, mt9v032->model->data->min_row_समय - crop->width,
			   min_hblank);
	hblank = max_t(अचिन्हित पूर्णांक, mt9v032->hblank, min_hblank);

	वापस regmap_ग_लिखो(mt9v032->regmap, MT9V032_HORIZONTAL_BLANKING,
			    hblank);
पूर्ण

अटल पूर्णांक mt9v032_घातer_on(काष्ठा mt9v032 *mt9v032)
अणु
	काष्ठा regmap *map = mt9v032->regmap;
	पूर्णांक ret;

	gpiod_set_value_cansleep(mt9v032->reset_gpio, 1);

	ret = clk_set_rate(mt9v032->clk, mt9v032->sysclk);
	अगर (ret < 0)
		वापस ret;

	/* System घड़ी has to be enabled beक्रमe releasing the reset */
	ret = clk_prepare_enable(mt9v032->clk);
	अगर (ret)
		वापस ret;

	udelay(1);

	अगर (mt9v032->reset_gpio) अणु
		gpiod_set_value_cansleep(mt9v032->reset_gpio, 0);

		/* After releasing reset we need to रुको 10 घड़ी cycles
		 * beक्रमe accessing the sensor over I2C. As the minimum SYSCLK
		 * frequency is 13MHz, रुकोing 1तगs will be enough in the worst
		 * हाल.
		 */
		udelay(1);
	पूर्ण

	/* Reset the chip and stop data पढ़ो out */
	ret = regmap_ग_लिखो(map, MT9V032_RESET, 1);
	अगर (ret < 0)
		जाओ err;

	ret = regmap_ग_लिखो(map, MT9V032_RESET, 0);
	अगर (ret < 0)
		जाओ err;

	ret = regmap_ग_लिखो(map, MT9V032_CHIP_CONTROL,
			   MT9V032_CHIP_CONTROL_MASTER_MODE);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	clk_disable_unprepare(mt9v032->clk);
	वापस ret;
पूर्ण

अटल व्योम mt9v032_घातer_off(काष्ठा mt9v032 *mt9v032)
अणु
	clk_disable_unprepare(mt9v032->clk);
पूर्ण

अटल पूर्णांक __mt9v032_set_घातer(काष्ठा mt9v032 *mt9v032, bool on)
अणु
	काष्ठा regmap *map = mt9v032->regmap;
	पूर्णांक ret;

	अगर (!on) अणु
		mt9v032_घातer_off(mt9v032);
		वापस 0;
	पूर्ण

	ret = mt9v032_घातer_on(mt9v032);
	अगर (ret < 0)
		वापस ret;

	/* Configure the pixel घड़ी polarity */
	अगर (mt9v032->pdata && mt9v032->pdata->clk_pol) अणु
		ret = regmap_ग_लिखो(map, mt9v032->model->data->pclk_reg,
				MT9V032_PIXEL_CLOCK_INV_PXL_CLK);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Disable the noise correction algorithm and restore the controls. */
	ret = regmap_ग_लिखो(map, MT9V032_ROW_NOISE_CORR_CONTROL, 0);
	अगर (ret < 0)
		वापस ret;

	वापस v4l2_ctrl_handler_setup(&mt9v032->ctrls);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev video operations
 */

अटल काष्ठा v4l2_mbus_framefmt *
__mt9v032_get_pad_क्रमmat(काष्ठा mt9v032 *mt9v032, काष्ठा v4l2_subdev_pad_config *cfg,
			 अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&mt9v032->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &mt9v032->क्रमmat;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा v4l2_rect *
__mt9v032_get_pad_crop(काष्ठा mt9v032 *mt9v032, काष्ठा v4l2_subdev_pad_config *cfg,
		       अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&mt9v032->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &mt9v032->crop;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9v032_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	स्थिर u16 mode = MT9V032_CHIP_CONTROL_DOUT_ENABLE
		       | MT9V032_CHIP_CONTROL_SEQUENTIAL;
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);
	काष्ठा v4l2_rect *crop = &mt9v032->crop;
	काष्ठा regmap *map = mt9v032->regmap;
	अचिन्हित पूर्णांक hbin;
	अचिन्हित पूर्णांक vbin;
	पूर्णांक ret;

	अगर (!enable)
		वापस regmap_update_bits(map, MT9V032_CHIP_CONTROL, mode, 0);

	/* Configure the winकरोw size and row/column bin */
	hbin = fls(mt9v032->hratio) - 1;
	vbin = fls(mt9v032->vratio) - 1;
	ret = regmap_update_bits(map, MT9V032_READ_MODE,
				 ~MT9V032_READ_MODE_RESERVED,
				 hbin << MT9V032_READ_MODE_COLUMN_BIN_SHIFT |
				 vbin << MT9V032_READ_MODE_ROW_BIN_SHIFT);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(map, MT9V032_COLUMN_START, crop->left);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(map, MT9V032_ROW_START, crop->top);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(map, MT9V032_WINDOW_WIDTH, crop->width);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(map, MT9V032_WINDOW_HEIGHT, crop->height);
	अगर (ret < 0)
		वापस ret;

	ret = mt9v032_update_hblank(mt9v032);
	अगर (ret < 0)
		वापस ret;

	/* Switch to master "normal" mode */
	वापस regmap_update_bits(map, MT9V032_CHIP_CONTROL, mode, mode);
पूर्ण

अटल पूर्णांक mt9v032_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);

	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = mt9v032->क्रमmat.code;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9v032_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);

	अगर (fse->index >= 3)
		वापस -EINVAL;
	अगर (mt9v032->क्रमmat.code != fse->code)
		वापस -EINVAL;

	fse->min_width = MT9V032_WINDOW_WIDTH_DEF / (1 << fse->index);
	fse->max_width = fse->min_width;
	fse->min_height = MT9V032_WINDOW_HEIGHT_DEF / (1 << fse->index);
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v032_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);

	क्रमmat->क्रमmat = *__mt9v032_get_pad_क्रमmat(mt9v032, cfg, क्रमmat->pad,
						   क्रमmat->which);
	वापस 0;
पूर्ण

अटल व्योम mt9v032_configure_pixel_rate(काष्ठा mt9v032 *mt9v032)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9v032->subdev);
	पूर्णांक ret;

	ret = v4l2_ctrl_s_ctrl_पूर्णांक64(mt9v032->pixel_rate,
				     mt9v032->sysclk / mt9v032->hratio);
	अगर (ret < 0)
		dev_warn(&client->dev, "failed to set pixel rate (%d)\n", ret);
पूर्ण

अटल अचिन्हित पूर्णांक mt9v032_calc_ratio(अचिन्हित पूर्णांक input, अचिन्हित पूर्णांक output)
अणु
	/* Compute the घातer-of-two binning factor बंदst to the input size to
	 * output size ratio. Given that the output size is bounded by input/4
	 * and input, a generic implementation would be an ineffective luxury.
	 */
	अगर (output * 3 > input * 2)
		वापस 1;
	अगर (output * 3 > input)
		वापस 2;
	वापस 4;
पूर्ण

अटल पूर्णांक mt9v032_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक hratio;
	अचिन्हित पूर्णांक vratio;

	__crop = __mt9v032_get_pad_crop(mt9v032, cfg, क्रमmat->pad,
					क्रमmat->which);

	/* Clamp the width and height to aव्योम भागiding by zero. */
	width = clamp(ALIGN(क्रमmat->क्रमmat.width, 2),
		      max_t(अचिन्हित पूर्णांक, __crop->width / 4,
			    MT9V032_WINDOW_WIDTH_MIN),
		      __crop->width);
	height = clamp(ALIGN(क्रमmat->क्रमmat.height, 2),
		       max_t(अचिन्हित पूर्णांक, __crop->height / 4,
			     MT9V032_WINDOW_HEIGHT_MIN),
		       __crop->height);

	hratio = mt9v032_calc_ratio(__crop->width, width);
	vratio = mt9v032_calc_ratio(__crop->height, height);

	__क्रमmat = __mt9v032_get_pad_क्रमmat(mt9v032, cfg, क्रमmat->pad,
					    क्रमmat->which);
	__क्रमmat->width = __crop->width / hratio;
	__क्रमmat->height = __crop->height / vratio;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		mt9v032->hratio = hratio;
		mt9v032->vratio = vratio;
		mt9v032_configure_pixel_rate(mt9v032);
	पूर्ण

	क्रमmat->क्रमmat = *__क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v032_get_selection(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	sel->r = *__mt9v032_get_pad_crop(mt9v032, cfg, sel->pad, sel->which);
	वापस 0;
पूर्ण

अटल पूर्णांक mt9v032_set_selection(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	काष्ठा v4l2_rect rect;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	/* Clamp the crop rectangle boundaries and align them to a non multiple
	 * of 2 pixels to ensure a GRBG Bayer pattern.
	 */
	rect.left = clamp(ALIGN(sel->r.left + 1, 2) - 1,
			  MT9V032_COLUMN_START_MIN,
			  MT9V032_COLUMN_START_MAX);
	rect.top = clamp(ALIGN(sel->r.top + 1, 2) - 1,
			 MT9V032_ROW_START_MIN,
			 MT9V032_ROW_START_MAX);
	rect.width = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.width, 2),
			     MT9V032_WINDOW_WIDTH_MIN,
			     MT9V032_WINDOW_WIDTH_MAX);
	rect.height = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.height, 2),
			      MT9V032_WINDOW_HEIGHT_MIN,
			      MT9V032_WINDOW_HEIGHT_MAX);

	rect.width = min_t(अचिन्हित पूर्णांक,
			   rect.width, MT9V032_PIXEL_ARRAY_WIDTH - rect.left);
	rect.height = min_t(अचिन्हित पूर्णांक,
			    rect.height, MT9V032_PIXEL_ARRAY_HEIGHT - rect.top);

	__crop = __mt9v032_get_pad_crop(mt9v032, cfg, sel->pad, sel->which);

	अगर (rect.width != __crop->width || rect.height != __crop->height) अणु
		/* Reset the output image size अगर the crop rectangle size has
		 * been modअगरied.
		 */
		__क्रमmat = __mt9v032_get_pad_क्रमmat(mt9v032, cfg, sel->pad,
						    sel->which);
		__क्रमmat->width = rect.width;
		__क्रमmat->height = rect.height;
		अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
			mt9v032->hratio = 1;
			mt9v032->vratio = 1;
			mt9v032_configure_pixel_rate(mt9v032);
		पूर्ण
	पूर्ण

	*__crop = rect;
	sel->r = rect;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev control operations
 */

#घोषणा V4L2_CID_TEST_PATTERN_COLOR	(V4L2_CID_USER_BASE | 0x1001)
/*
 * Value between 1 and 64 to set the desired bin. This is effectively a measure
 * of how bright the image is supposed to be. Both AGC and AEC try to reach
 * this.
 */
#घोषणा V4L2_CID_AEGC_DESIRED_BIN	(V4L2_CID_USER_BASE | 0x1002)
/*
 * LPF is the low pass filter capability of the chip. Both AEC and AGC have
 * this setting. This limits the speed in which AGC/AEC adjust their settings.
 * Possible values are 0-2. 0 means no LPF. For 1 and 2 this equation is used:
 *
 * अगर |(calculated new exp - current exp)| > (current exp / 4)
 *	next exp = calculated new exp
 * अन्यथा
 *	next exp = current exp + ((calculated new exp - current exp) / 2^LPF)
 */
#घोषणा V4L2_CID_AEC_LPF		(V4L2_CID_USER_BASE | 0x1003)
#घोषणा V4L2_CID_AGC_LPF		(V4L2_CID_USER_BASE | 0x1004)
/*
 * Value between 0 and 15. This is the number of frames being skipped beक्रमe
 * updating the स्वतः exposure/gain.
 */
#घोषणा V4L2_CID_AEC_UPDATE_INTERVAL	(V4L2_CID_USER_BASE | 0x1005)
#घोषणा V4L2_CID_AGC_UPDATE_INTERVAL	(V4L2_CID_USER_BASE | 0x1006)
/*
 * Maximum shutter width used क्रम AEC.
 */
#घोषणा V4L2_CID_AEC_MAX_SHUTTER_WIDTH	(V4L2_CID_USER_BASE | 0x1007)

अटल पूर्णांक mt9v032_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9v032 *mt9v032 =
			container_of(ctrl->handler, काष्ठा mt9v032, ctrls);
	काष्ठा regmap *map = mt9v032->regmap;
	u32 freq;
	u16 data;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		वापस mt9v032_update_aec_agc(mt9v032, MT9V032_AGC_ENABLE,
					      ctrl->val);

	हाल V4L2_CID_GAIN:
		वापस regmap_ग_लिखो(map, MT9V032_ANALOG_GAIN, ctrl->val);

	हाल V4L2_CID_EXPOSURE_AUTO:
		वापस mt9v032_update_aec_agc(mt9v032, MT9V032_AEC_ENABLE,
					      !ctrl->val);

	हाल V4L2_CID_EXPOSURE:
		वापस regmap_ग_लिखो(map, MT9V032_TOTAL_SHUTTER_WIDTH,
				    ctrl->val);

	हाल V4L2_CID_HBLANK:
		mt9v032->hblank = ctrl->val;
		वापस mt9v032_update_hblank(mt9v032);

	हाल V4L2_CID_VBLANK:
		वापस regmap_ग_लिखो(map, MT9V032_VERTICAL_BLANKING,
				    ctrl->val);

	हाल V4L2_CID_PIXEL_RATE:
	हाल V4L2_CID_LINK_FREQ:
		अगर (mt9v032->link_freq == शून्य)
			अवरोध;

		freq = mt9v032->pdata->link_freqs[mt9v032->link_freq->val];
		*mt9v032->pixel_rate->p_new.p_s64 = freq;
		mt9v032->sysclk = freq;
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		चयन (mt9v032->test_pattern->val) अणु
		हाल 0:
			data = 0;
			अवरोध;
		हाल 1:
			data = MT9V032_TEST_PATTERN_GRAY_VERTICAL
			     | MT9V032_TEST_PATTERN_ENABLE;
			अवरोध;
		हाल 2:
			data = MT9V032_TEST_PATTERN_GRAY_HORIZONTAL
			     | MT9V032_TEST_PATTERN_ENABLE;
			अवरोध;
		हाल 3:
			data = MT9V032_TEST_PATTERN_GRAY_DIAGONAL
			     | MT9V032_TEST_PATTERN_ENABLE;
			अवरोध;
		शेष:
			data = (mt9v032->test_pattern_color->val <<
				MT9V032_TEST_PATTERN_DATA_SHIFT)
			     | MT9V032_TEST_PATTERN_USE_DATA
			     | MT9V032_TEST_PATTERN_ENABLE
			     | MT9V032_TEST_PATTERN_FLIP;
			अवरोध;
		पूर्ण
		वापस regmap_ग_लिखो(map, MT9V032_TEST_PATTERN, data);

	हाल V4L2_CID_AEGC_DESIRED_BIN:
		वापस regmap_ग_लिखो(map, MT9V032_AEGC_DESIRED_BIN, ctrl->val);

	हाल V4L2_CID_AEC_LPF:
		वापस regmap_ग_लिखो(map, MT9V032_AEC_LPF, ctrl->val);

	हाल V4L2_CID_AGC_LPF:
		वापस regmap_ग_लिखो(map, MT9V032_AGC_LPF, ctrl->val);

	हाल V4L2_CID_AEC_UPDATE_INTERVAL:
		वापस regmap_ग_लिखो(map, MT9V032_AEC_UPDATE_FREQUENCY,
				    ctrl->val);

	हाल V4L2_CID_AGC_UPDATE_INTERVAL:
		वापस regmap_ग_लिखो(map, MT9V032_AGC_UPDATE_FREQUENCY,
				    ctrl->val);

	हाल V4L2_CID_AEC_MAX_SHUTTER_WIDTH:
		वापस regmap_ग_लिखो(map,
				    mt9v032->model->data->aec_max_shutter_reg,
				    ctrl->val);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9v032_ctrl_ops = अणु
	.s_ctrl = mt9v032_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mt9v032_test_pattern_menu[] = अणु
	"Disabled",
	"Gray Vertical Shade",
	"Gray Horizontal Shade",
	"Gray Diagonal Shade",
	"Plain",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9v032_test_pattern_color = अणु
	.ops		= &mt9v032_ctrl_ops,
	.id		= V4L2_CID_TEST_PATTERN_COLOR,
	.type		= V4L2_CTRL_TYPE_INTEGER,
	.name		= "Test Pattern Color",
	.min		= 0,
	.max		= 1023,
	.step		= 1,
	.def		= 0,
	.flags		= 0,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9v032_aegc_controls[] = अणु
	अणु
		.ops		= &mt9v032_ctrl_ops,
		.id		= V4L2_CID_AEGC_DESIRED_BIN,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "AEC/AGC Desired Bin",
		.min		= 1,
		.max		= 64,
		.step		= 1,
		.def		= 58,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9v032_ctrl_ops,
		.id		= V4L2_CID_AEC_LPF,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "AEC Low Pass Filter",
		.min		= 0,
		.max		= 2,
		.step		= 1,
		.def		= 0,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9v032_ctrl_ops,
		.id		= V4L2_CID_AGC_LPF,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "AGC Low Pass Filter",
		.min		= 0,
		.max		= 2,
		.step		= 1,
		.def		= 2,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9v032_ctrl_ops,
		.id		= V4L2_CID_AEC_UPDATE_INTERVAL,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "AEC Update Interval",
		.min		= 0,
		.max		= 16,
		.step		= 1,
		.def		= 2,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9v032_ctrl_ops,
		.id		= V4L2_CID_AGC_UPDATE_INTERVAL,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "AGC Update Interval",
		.min		= 0,
		.max		= 16,
		.step		= 1,
		.def		= 2,
		.flags		= 0,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9v032_aec_max_shutter_width = अणु
	.ops		= &mt9v032_ctrl_ops,
	.id		= V4L2_CID_AEC_MAX_SHUTTER_WIDTH,
	.type		= V4L2_CTRL_TYPE_INTEGER,
	.name		= "AEC Max Shutter Width",
	.min		= 1,
	.max		= 2047,
	.step		= 1,
	.def		= 480,
	.flags		= 0,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9v034_aec_max_shutter_width = अणु
	.ops		= &mt9v032_ctrl_ops,
	.id		= V4L2_CID_AEC_MAX_SHUTTER_WIDTH,
	.type		= V4L2_CTRL_TYPE_INTEGER,
	.name		= "AEC Max Shutter Width",
	.min		= 1,
	.max		= 32765,
	.step		= 1,
	.def		= 480,
	.flags		= 0,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev core operations
 */

अटल पूर्णांक mt9v032_set_घातer(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&mt9v032->घातer_lock);

	/* If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (mt9v032->घातer_count == !on) अणु
		ret = __mt9v032_set_घातer(mt9v032, !!on);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	/* Update the घातer count. */
	mt9v032->घातer_count += on ? 1 : -1;
	WARN_ON(mt9v032->घातer_count < 0);

करोne:
	mutex_unlock(&mt9v032->घातer_lock);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev पूर्णांकernal operations
 */

अटल पूर्णांक mt9v032_रेजिस्टरed(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);
	अचिन्हित पूर्णांक i;
	u32 version;
	पूर्णांक ret;

	dev_info(&client->dev, "Probing MT9V032 at address 0x%02x\n",
			client->addr);

	ret = mt9v032_घातer_on(mt9v032);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "MT9V032 power up failed\n");
		वापस ret;
	पूर्ण

	/* Read and check the sensor version */
	ret = regmap_पढ़ो(mt9v032->regmap, MT9V032_CHIP_VERSION, &version);

	mt9v032_घातer_off(mt9v032);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed reading chip version\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mt9v032_versions); ++i) अणु
		अगर (mt9v032_versions[i].version == version) अणु
			mt9v032->version = &mt9v032_versions[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mt9v032->version == शून्य) अणु
		dev_err(&client->dev, "Unsupported chip version 0x%04x\n",
			version);
		वापस -ENODEV;
	पूर्ण

	dev_info(&client->dev, "%s detected at address 0x%02x\n",
		 mt9v032->version->name, client->addr);

	mt9v032_configure_pixel_rate(mt9v032);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9v032_खोलो(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;

	crop = v4l2_subdev_get_try_crop(subdev, fh->pad, 0);
	crop->left = MT9V032_COLUMN_START_DEF;
	crop->top = MT9V032_ROW_START_DEF;
	crop->width = MT9V032_WINDOW_WIDTH_DEF;
	crop->height = MT9V032_WINDOW_HEIGHT_DEF;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, fh->pad, 0);

	अगर (mt9v032->model->color)
		क्रमmat->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	अन्यथा
		क्रमmat->code = MEDIA_BUS_FMT_Y10_1X10;

	क्रमmat->width = MT9V032_WINDOW_WIDTH_DEF;
	क्रमmat->height = MT9V032_WINDOW_HEIGHT_DEF;
	क्रमmat->field = V4L2_FIELD_NONE;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	वापस mt9v032_set_घातer(subdev, 1);
पूर्ण

अटल पूर्णांक mt9v032_बंद(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस mt9v032_set_घातer(subdev, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9v032_subdev_core_ops = अणु
	.s_घातer	= mt9v032_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9v032_subdev_video_ops = अणु
	.s_stream	= mt9v032_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9v032_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = mt9v032_क्रमागत_mbus_code,
	.क्रमागत_frame_size = mt9v032_क्रमागत_frame_size,
	.get_fmt = mt9v032_get_क्रमmat,
	.set_fmt = mt9v032_set_क्रमmat,
	.get_selection = mt9v032_get_selection,
	.set_selection = mt9v032_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9v032_subdev_ops = अणु
	.core	= &mt9v032_subdev_core_ops,
	.video	= &mt9v032_subdev_video_ops,
	.pad	= &mt9v032_subdev_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops mt9v032_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = mt9v032_रेजिस्टरed,
	.खोलो = mt9v032_खोलो,
	.बंद = mt9v032_बंद,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mt9v032_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = 0xff,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Driver initialization and probing
 */

अटल काष्ठा mt9v032_platक्रमm_data *
mt9v032_get_pdata(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9v032_platक्रमm_data *pdata = शून्य;
	काष्ठा v4l2_fwnode_endpoपूर्णांक endpoपूर्णांक = अणु .bus_type = 0 पूर्ण;
	काष्ठा device_node *np;
	काष्ठा property *prop;

	अगर (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		वापस client->dev.platक्रमm_data;

	np = of_graph_get_next_endpoपूर्णांक(client->dev.of_node, शून्य);
	अगर (!np)
		वापस शून्य;

	अगर (v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(np), &endpoपूर्णांक) < 0)
		जाओ करोne;

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		जाओ करोne;

	prop = of_find_property(np, "link-frequencies", शून्य);
	अगर (prop) अणु
		u64 *link_freqs;
		माप_प्रकार size = prop->length / माप(*link_freqs);

		link_freqs = devm_kसुस्मृति(&client->dev, size,
					  माप(*link_freqs), GFP_KERNEL);
		अगर (!link_freqs)
			जाओ करोne;

		अगर (of_property_पढ़ो_u64_array(np, "link-frequencies",
					       link_freqs, size) < 0)
			जाओ करोne;

		pdata->link_freqs = link_freqs;
		pdata->link_def_freq = link_freqs[0];
	पूर्ण

	pdata->clk_pol = !!(endpoपूर्णांक.bus.parallel.flags &
			    V4L2_MBUS_PCLK_SAMPLE_RISING);

करोne:
	of_node_put(np);
	वापस pdata;
पूर्ण

अटल पूर्णांक mt9v032_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा mt9v032_platक्रमm_data *pdata = mt9v032_get_pdata(client);
	काष्ठा mt9v032 *mt9v032;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mt9v032 = devm_kzalloc(&client->dev, माप(*mt9v032), GFP_KERNEL);
	अगर (!mt9v032)
		वापस -ENOMEM;

	mt9v032->regmap = devm_regmap_init_i2c(client, &mt9v032_regmap_config);
	अगर (IS_ERR(mt9v032->regmap))
		वापस PTR_ERR(mt9v032->regmap);

	mt9v032->clk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(mt9v032->clk))
		वापस PTR_ERR(mt9v032->clk);

	mt9v032->reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						      GPIOD_OUT_HIGH);
	अगर (IS_ERR(mt9v032->reset_gpio))
		वापस PTR_ERR(mt9v032->reset_gpio);

	mt9v032->standby_gpio = devm_gpiod_get_optional(&client->dev, "standby",
							GPIOD_OUT_LOW);
	अगर (IS_ERR(mt9v032->standby_gpio))
		वापस PTR_ERR(mt9v032->standby_gpio);

	mutex_init(&mt9v032->घातer_lock);
	mt9v032->pdata = pdata;
	mt9v032->model = (स्थिर व्योम *)did->driver_data;

	v4l2_ctrl_handler_init(&mt9v032->ctrls, 11 +
			       ARRAY_SIZE(mt9v032_aegc_controls));

	v4l2_ctrl_new_std(&mt9v032->ctrls, &mt9v032_ctrl_ops,
			  V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	v4l2_ctrl_new_std(&mt9v032->ctrls, &mt9v032_ctrl_ops,
			  V4L2_CID_GAIN, MT9V032_ANALOG_GAIN_MIN,
			  MT9V032_ANALOG_GAIN_MAX, 1, MT9V032_ANALOG_GAIN_DEF);
	v4l2_ctrl_new_std_menu(&mt9v032->ctrls, &mt9v032_ctrl_ops,
			       V4L2_CID_EXPOSURE_AUTO, V4L2_EXPOSURE_MANUAL, 0,
			       V4L2_EXPOSURE_AUTO);
	v4l2_ctrl_new_std(&mt9v032->ctrls, &mt9v032_ctrl_ops,
			  V4L2_CID_EXPOSURE, mt9v032->model->data->min_shutter,
			  mt9v032->model->data->max_shutter, 1,
			  MT9V032_TOTAL_SHUTTER_WIDTH_DEF);
	v4l2_ctrl_new_std(&mt9v032->ctrls, &mt9v032_ctrl_ops,
			  V4L2_CID_HBLANK, mt9v032->model->data->min_hblank,
			  MT9V032_HORIZONTAL_BLANKING_MAX, 1,
			  MT9V032_HORIZONTAL_BLANKING_DEF);
	v4l2_ctrl_new_std(&mt9v032->ctrls, &mt9v032_ctrl_ops,
			  V4L2_CID_VBLANK, mt9v032->model->data->min_vblank,
			  mt9v032->model->data->max_vblank, 1,
			  MT9V032_VERTICAL_BLANKING_DEF);
	mt9v032->test_pattern = v4l2_ctrl_new_std_menu_items(&mt9v032->ctrls,
				&mt9v032_ctrl_ops, V4L2_CID_TEST_PATTERN,
				ARRAY_SIZE(mt9v032_test_pattern_menu) - 1, 0, 0,
				mt9v032_test_pattern_menu);
	mt9v032->test_pattern_color = v4l2_ctrl_new_custom(&mt9v032->ctrls,
				      &mt9v032_test_pattern_color, शून्य);

	v4l2_ctrl_new_custom(&mt9v032->ctrls,
			     mt9v032->model->data->aec_max_shutter_v4l2_ctrl,
			     शून्य);
	क्रम (i = 0; i < ARRAY_SIZE(mt9v032_aegc_controls); ++i)
		v4l2_ctrl_new_custom(&mt9v032->ctrls, &mt9v032_aegc_controls[i],
				     शून्य);

	v4l2_ctrl_cluster(2, &mt9v032->test_pattern);

	mt9v032->pixel_rate =
		v4l2_ctrl_new_std(&mt9v032->ctrls, &mt9v032_ctrl_ops,
				  V4L2_CID_PIXEL_RATE, 1, पूर्णांक_उच्च, 1, 1);

	अगर (pdata && pdata->link_freqs) अणु
		अचिन्हित पूर्णांक def = 0;

		क्रम (i = 0; pdata->link_freqs[i]; ++i) अणु
			अगर (pdata->link_freqs[i] == pdata->link_def_freq)
				def = i;
		पूर्ण

		mt9v032->link_freq =
			v4l2_ctrl_new_पूर्णांक_menu(&mt9v032->ctrls,
					       &mt9v032_ctrl_ops,
					       V4L2_CID_LINK_FREQ, i - 1, def,
					       pdata->link_freqs);
		v4l2_ctrl_cluster(2, &mt9v032->link_freq);
	पूर्ण


	mt9v032->subdev.ctrl_handler = &mt9v032->ctrls;

	अगर (mt9v032->ctrls.error) अणु
		dev_err(&client->dev, "control initialization error %d\n",
			mt9v032->ctrls.error);
		ret = mt9v032->ctrls.error;
		जाओ err;
	पूर्ण

	mt9v032->crop.left = MT9V032_COLUMN_START_DEF;
	mt9v032->crop.top = MT9V032_ROW_START_DEF;
	mt9v032->crop.width = MT9V032_WINDOW_WIDTH_DEF;
	mt9v032->crop.height = MT9V032_WINDOW_HEIGHT_DEF;

	अगर (mt9v032->model->color)
		mt9v032->क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	अन्यथा
		mt9v032->क्रमmat.code = MEDIA_BUS_FMT_Y10_1X10;

	mt9v032->क्रमmat.width = MT9V032_WINDOW_WIDTH_DEF;
	mt9v032->क्रमmat.height = MT9V032_WINDOW_HEIGHT_DEF;
	mt9v032->क्रमmat.field = V4L2_FIELD_NONE;
	mt9v032->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;

	mt9v032->hratio = 1;
	mt9v032->vratio = 1;

	mt9v032->aec_agc = MT9V032_AEC_ENABLE | MT9V032_AGC_ENABLE;
	mt9v032->hblank = MT9V032_HORIZONTAL_BLANKING_DEF;
	mt9v032->sysclk = MT9V032_SYSCLK_FREQ_DEF;

	v4l2_i2c_subdev_init(&mt9v032->subdev, client, &mt9v032_subdev_ops);
	mt9v032->subdev.पूर्णांकernal_ops = &mt9v032_subdev_पूर्णांकernal_ops;
	mt9v032->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	mt9v032->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	mt9v032->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&mt9v032->subdev.entity, 1, &mt9v032->pad);
	अगर (ret < 0)
		जाओ err;

	mt9v032->subdev.dev = &client->dev;
	ret = v4l2_async_रेजिस्टर_subdev(&mt9v032->subdev);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	media_entity_cleanup(&mt9v032->subdev.entity);
	v4l2_ctrl_handler_मुक्त(&mt9v032->ctrls);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9v032_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा mt9v032 *mt9v032 = to_mt9v032(subdev);

	v4l2_async_unरेजिस्टर_subdev(subdev);
	v4l2_ctrl_handler_मुक्त(&mt9v032->ctrls);
	media_entity_cleanup(&subdev->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mt9v032_model_data mt9v032_model_data[] = अणु
	अणु
		/* MT9V022, MT9V032 revisions 1/2/3 */
		.min_row_समय = 660,
		.min_hblank = MT9V032_HORIZONTAL_BLANKING_MIN,
		.min_vblank = MT9V032_VERTICAL_BLANKING_MIN,
		.max_vblank = MT9V032_VERTICAL_BLANKING_MAX,
		.min_shutter = MT9V032_TOTAL_SHUTTER_WIDTH_MIN,
		.max_shutter = MT9V032_TOTAL_SHUTTER_WIDTH_MAX,
		.pclk_reg = MT9V032_PIXEL_CLOCK,
		.aec_max_shutter_reg = MT9V032_AEC_MAX_SHUTTER_WIDTH,
		.aec_max_shutter_v4l2_ctrl = &mt9v032_aec_max_shutter_width,
	पूर्ण, अणु
		/* MT9V024, MT9V034 */
		.min_row_समय = 690,
		.min_hblank = MT9V034_HORIZONTAL_BLANKING_MIN,
		.min_vblank = MT9V034_VERTICAL_BLANKING_MIN,
		.max_vblank = MT9V034_VERTICAL_BLANKING_MAX,
		.min_shutter = MT9V034_TOTAL_SHUTTER_WIDTH_MIN,
		.max_shutter = MT9V034_TOTAL_SHUTTER_WIDTH_MAX,
		.pclk_reg = MT9V034_PIXEL_CLOCK,
		.aec_max_shutter_reg = MT9V034_AEC_MAX_SHUTTER_WIDTH,
		.aec_max_shutter_v4l2_ctrl = &mt9v034_aec_max_shutter_width,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt9v032_model_info mt9v032_models[] = अणु
	[MT9V032_MODEL_V022_COLOR] = अणु
		.data = &mt9v032_model_data[0],
		.color = true,
	पूर्ण,
	[MT9V032_MODEL_V022_MONO] = अणु
		.data = &mt9v032_model_data[0],
		.color = false,
	पूर्ण,
	[MT9V032_MODEL_V024_COLOR] = अणु
		.data = &mt9v032_model_data[1],
		.color = true,
	पूर्ण,
	[MT9V032_MODEL_V024_MONO] = अणु
		.data = &mt9v032_model_data[1],
		.color = false,
	पूर्ण,
	[MT9V032_MODEL_V032_COLOR] = अणु
		.data = &mt9v032_model_data[0],
		.color = true,
	पूर्ण,
	[MT9V032_MODEL_V032_MONO] = अणु
		.data = &mt9v032_model_data[0],
		.color = false,
	पूर्ण,
	[MT9V032_MODEL_V034_COLOR] = अणु
		.data = &mt9v032_model_data[1],
		.color = true,
	पूर्ण,
	[MT9V032_MODEL_V034_MONO] = अणु
		.data = &mt9v032_model_data[1],
		.color = false,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id mt9v032_id[] = अणु
	अणु "mt9v022", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V022_COLOR] पूर्ण,
	अणु "mt9v022m", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V022_MONO] पूर्ण,
	अणु "mt9v024", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V024_COLOR] पूर्ण,
	अणु "mt9v024m", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V024_MONO] पूर्ण,
	अणु "mt9v032", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V032_COLOR] पूर्ण,
	अणु "mt9v032m", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V032_MONO] पूर्ण,
	अणु "mt9v034", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V034_COLOR] पूर्ण,
	अणु "mt9v034m", (kernel_uदीर्घ_t)&mt9v032_models[MT9V032_MODEL_V034_MONO] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt9v032_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id mt9v032_of_match[] = अणु
	अणु .compatible = "aptina,mt9v022" पूर्ण,
	अणु .compatible = "aptina,mt9v022m" पूर्ण,
	अणु .compatible = "aptina,mt9v024" पूर्ण,
	अणु .compatible = "aptina,mt9v024m" पूर्ण,
	अणु .compatible = "aptina,mt9v032" पूर्ण,
	अणु .compatible = "aptina,mt9v032m" पूर्ण,
	अणु .compatible = "aptina,mt9v034" पूर्ण,
	अणु .compatible = "aptina,mt9v034m" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt9v032_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver mt9v032_driver = अणु
	.driver = अणु
		.name = "mt9v032",
		.of_match_table = of_match_ptr(mt9v032_of_match),
	पूर्ण,
	.probe		= mt9v032_probe,
	.हटाओ		= mt9v032_हटाओ,
	.id_table	= mt9v032_id,
पूर्ण;

module_i2c_driver(mt9v032_driver);

MODULE_DESCRIPTION("Aptina MT9V032 Camera driver");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_LICENSE("GPL");
