<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MT9P031 CMOS Image Sensor from Aptina
 *
 * Copyright (C) 2011, Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 * Copyright (C) 2011, Javier Martin <javier.martin@vista-silicon.com>
 * Copyright (C) 2011, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 *
 * Based on the MT9V032 driver and Bastian Hecht's code.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/i2c/mt9p031.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "aptina-pll.h"

#घोषणा MT9P031_PIXEL_ARRAY_WIDTH			2752
#घोषणा MT9P031_PIXEL_ARRAY_HEIGHT			2004

#घोषणा MT9P031_CHIP_VERSION				0x00
#घोषणा		MT9P031_CHIP_VERSION_VALUE		0x1801
#घोषणा MT9P031_ROW_START				0x01
#घोषणा		MT9P031_ROW_START_MIN			0
#घोषणा		MT9P031_ROW_START_MAX			2004
#घोषणा		MT9P031_ROW_START_DEF			54
#घोषणा MT9P031_COLUMN_START				0x02
#घोषणा		MT9P031_COLUMN_START_MIN		0
#घोषणा		MT9P031_COLUMN_START_MAX		2750
#घोषणा		MT9P031_COLUMN_START_DEF		16
#घोषणा MT9P031_WINDOW_HEIGHT				0x03
#घोषणा		MT9P031_WINDOW_HEIGHT_MIN		2
#घोषणा		MT9P031_WINDOW_HEIGHT_MAX		2006
#घोषणा		MT9P031_WINDOW_HEIGHT_DEF		1944
#घोषणा MT9P031_WINDOW_WIDTH				0x04
#घोषणा		MT9P031_WINDOW_WIDTH_MIN		2
#घोषणा		MT9P031_WINDOW_WIDTH_MAX		2752
#घोषणा		MT9P031_WINDOW_WIDTH_DEF		2592
#घोषणा MT9P031_HORIZONTAL_BLANK			0x05
#घोषणा		MT9P031_HORIZONTAL_BLANK_MIN		0
#घोषणा		MT9P031_HORIZONTAL_BLANK_MAX		4095
#घोषणा MT9P031_VERTICAL_BLANK				0x06
#घोषणा		MT9P031_VERTICAL_BLANK_MIN		1
#घोषणा		MT9P031_VERTICAL_BLANK_MAX		4096
#घोषणा		MT9P031_VERTICAL_BLANK_DEF		26
#घोषणा MT9P031_OUTPUT_CONTROL				0x07
#घोषणा		MT9P031_OUTPUT_CONTROL_CEN		2
#घोषणा		MT9P031_OUTPUT_CONTROL_SYN		1
#घोषणा		MT9P031_OUTPUT_CONTROL_DEF		0x1f82
#घोषणा MT9P031_SHUTTER_WIDTH_UPPER			0x08
#घोषणा MT9P031_SHUTTER_WIDTH_LOWER			0x09
#घोषणा		MT9P031_SHUTTER_WIDTH_MIN		1
#घोषणा		MT9P031_SHUTTER_WIDTH_MAX		1048575
#घोषणा		MT9P031_SHUTTER_WIDTH_DEF		1943
#घोषणा	MT9P031_PLL_CONTROL				0x10
#घोषणा		MT9P031_PLL_CONTROL_PWROFF		0x0050
#घोषणा		MT9P031_PLL_CONTROL_PWRON		0x0051
#घोषणा		MT9P031_PLL_CONTROL_USEPLL		0x0052
#घोषणा	MT9P031_PLL_CONFIG_1				0x11
#घोषणा	MT9P031_PLL_CONFIG_2				0x12
#घोषणा MT9P031_PIXEL_CLOCK_CONTROL			0x0a
#घोषणा		MT9P031_PIXEL_CLOCK_INVERT		(1 << 15)
#घोषणा		MT9P031_PIXEL_CLOCK_SHIFT(n)		((n) << 8)
#घोषणा		MT9P031_PIXEL_CLOCK_DIVIDE(n)		((n) << 0)
#घोषणा MT9P031_FRAME_RESTART				0x0b
#घोषणा MT9P031_SHUTTER_DELAY				0x0c
#घोषणा MT9P031_RST					0x0d
#घोषणा		MT9P031_RST_ENABLE			1
#घोषणा		MT9P031_RST_DISABLE			0
#घोषणा MT9P031_READ_MODE_1				0x1e
#घोषणा MT9P031_READ_MODE_2				0x20
#घोषणा		MT9P031_READ_MODE_2_ROW_MIR		(1 << 15)
#घोषणा		MT9P031_READ_MODE_2_COL_MIR		(1 << 14)
#घोषणा		MT9P031_READ_MODE_2_ROW_BLC		(1 << 6)
#घोषणा MT9P031_ROW_ADDRESS_MODE			0x22
#घोषणा MT9P031_COLUMN_ADDRESS_MODE			0x23
#घोषणा MT9P031_GLOBAL_GAIN				0x35
#घोषणा		MT9P031_GLOBAL_GAIN_MIN			8
#घोषणा		MT9P031_GLOBAL_GAIN_MAX			1024
#घोषणा		MT9P031_GLOBAL_GAIN_DEF			8
#घोषणा		MT9P031_GLOBAL_GAIN_MULT		(1 << 6)
#घोषणा MT9P031_ROW_BLACK_TARGET			0x49
#घोषणा MT9P031_ROW_BLACK_DEF_OFFSET			0x4b
#घोषणा MT9P031_GREEN1_OFFSET				0x60
#घोषणा MT9P031_GREEN2_OFFSET				0x61
#घोषणा MT9P031_BLACK_LEVEL_CALIBRATION			0x62
#घोषणा		MT9P031_BLC_MANUAL_BLC			(1 << 0)
#घोषणा MT9P031_RED_OFFSET				0x63
#घोषणा MT9P031_BLUE_OFFSET				0x64
#घोषणा MT9P031_TEST_PATTERN				0xa0
#घोषणा		MT9P031_TEST_PATTERN_SHIFT		3
#घोषणा		MT9P031_TEST_PATTERN_ENABLE		(1 << 0)
#घोषणा		MT9P031_TEST_PATTERN_DISABLE		(0 << 0)
#घोषणा MT9P031_TEST_PATTERN_GREEN			0xa1
#घोषणा MT9P031_TEST_PATTERN_RED			0xa2
#घोषणा MT9P031_TEST_PATTERN_BLUE			0xa3

क्रमागत mt9p031_model अणु
	MT9P031_MODEL_COLOR,
	MT9P031_MODEL_MONOCHROME,
पूर्ण;

काष्ठा mt9p031 अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;
	काष्ठा v4l2_rect crop;  /* Sensor winकरोw */
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा mt9p031_platक्रमm_data *pdata;
	काष्ठा mutex घातer_lock; /* lock to protect घातer_count */
	पूर्णांक घातer_count;

	काष्ठा clk *clk;
	काष्ठा regulator_bulk_data regulators[3];

	क्रमागत mt9p031_model model;
	काष्ठा aptina_pll pll;
	अचिन्हित पूर्णांक clk_भाग;
	bool use_pll;
	काष्ठा gpio_desc *reset;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *blc_स्वतः;
	काष्ठा v4l2_ctrl *blc_offset;

	/* Registers cache */
	u16 output_control;
	u16 mode2;
पूर्ण;

अटल काष्ठा mt9p031 *to_mt9p031(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा mt9p031, subdev);
पूर्ण

अटल पूर्णांक mt9p031_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
पूर्ण

अटल पूर्णांक mt9p031_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u16 data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(client, reg, data);
पूर्ण

अटल पूर्णांक mt9p031_set_output_control(काष्ठा mt9p031 *mt9p031, u16 clear,
				      u16 set)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	u16 value = (mt9p031->output_control & ~clear) | set;
	पूर्णांक ret;

	ret = mt9p031_ग_लिखो(client, MT9P031_OUTPUT_CONTROL, value);
	अगर (ret < 0)
		वापस ret;

	mt9p031->output_control = value;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_set_mode2(काष्ठा mt9p031 *mt9p031, u16 clear, u16 set)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	u16 value = (mt9p031->mode2 & ~clear) | set;
	पूर्णांक ret;

	ret = mt9p031_ग_लिखो(client, MT9P031_READ_MODE_2, value);
	अगर (ret < 0)
		वापस ret;

	mt9p031->mode2 = value;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_reset(काष्ठा mt9p031 *mt9p031)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	पूर्णांक ret;

	/* Disable chip output, synchronous option update */
	ret = mt9p031_ग_लिखो(client, MT9P031_RST, MT9P031_RST_ENABLE);
	अगर (ret < 0)
		वापस ret;
	ret = mt9p031_ग_लिखो(client, MT9P031_RST, MT9P031_RST_DISABLE);
	अगर (ret < 0)
		वापस ret;

	ret = mt9p031_ग_लिखो(client, MT9P031_PIXEL_CLOCK_CONTROL,
			    MT9P031_PIXEL_CLOCK_DIVIDE(mt9p031->clk_भाग));
	अगर (ret < 0)
		वापस ret;

	वापस mt9p031_set_output_control(mt9p031, MT9P031_OUTPUT_CONTROL_CEN,
					  0);
पूर्ण

अटल पूर्णांक mt9p031_clk_setup(काष्ठा mt9p031 *mt9p031)
अणु
	अटल स्थिर काष्ठा aptina_pll_limits limits = अणु
		.ext_घड़ी_min = 6000000,
		.ext_घड़ी_max = 27000000,
		.पूर्णांक_घड़ी_min = 2000000,
		.पूर्णांक_घड़ी_max = 13500000,
		.out_घड़ी_min = 180000000,
		.out_घड़ी_max = 360000000,
		.pix_घड़ी_max = 96000000,
		.n_min = 1,
		.n_max = 64,
		.m_min = 16,
		.m_max = 255,
		.p1_min = 1,
		.p1_max = 128,
	पूर्ण;

	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	काष्ठा mt9p031_platक्रमm_data *pdata = mt9p031->pdata;
	पूर्णांक ret;

	mt9p031->clk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(mt9p031->clk))
		वापस PTR_ERR(mt9p031->clk);

	ret = clk_set_rate(mt9p031->clk, pdata->ext_freq);
	अगर (ret < 0)
		वापस ret;

	/* If the बाह्यal घड़ी frequency is out of bounds क्रम the PLL use the
	 * pixel घड़ी भागider only and disable the PLL.
	 */
	अगर (pdata->ext_freq > limits.ext_घड़ी_max) अणु
		अचिन्हित पूर्णांक भाग;

		भाग = DIV_ROUND_UP(pdata->ext_freq, pdata->target_freq);
		भाग = roundup_घात_of_two(भाग) / 2;

		mt9p031->clk_भाग = min_t(अचिन्हित पूर्णांक, भाग, 64);
		mt9p031->use_pll = false;

		वापस 0;
	पूर्ण

	mt9p031->pll.ext_घड़ी = pdata->ext_freq;
	mt9p031->pll.pix_घड़ी = pdata->target_freq;
	mt9p031->use_pll = true;

	वापस aptina_pll_calculate(&client->dev, &limits, &mt9p031->pll);
पूर्ण

अटल पूर्णांक mt9p031_pll_enable(काष्ठा mt9p031 *mt9p031)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	पूर्णांक ret;

	अगर (!mt9p031->use_pll)
		वापस 0;

	ret = mt9p031_ग_लिखो(client, MT9P031_PLL_CONTROL,
			    MT9P031_PLL_CONTROL_PWRON);
	अगर (ret < 0)
		वापस ret;

	ret = mt9p031_ग_लिखो(client, MT9P031_PLL_CONFIG_1,
			    (mt9p031->pll.m << 8) | (mt9p031->pll.n - 1));
	अगर (ret < 0)
		वापस ret;

	ret = mt9p031_ग_लिखो(client, MT9P031_PLL_CONFIG_2, mt9p031->pll.p1 - 1);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 2000);
	ret = mt9p031_ग_लिखो(client, MT9P031_PLL_CONTROL,
			    MT9P031_PLL_CONTROL_PWRON |
			    MT9P031_PLL_CONTROL_USEPLL);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक mt9p031_pll_disable(काष्ठा mt9p031 *mt9p031)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);

	अगर (!mt9p031->use_pll)
		वापस 0;

	वापस mt9p031_ग_लिखो(client, MT9P031_PLL_CONTROL,
			     MT9P031_PLL_CONTROL_PWROFF);
पूर्ण

अटल पूर्णांक mt9p031_घातer_on(काष्ठा mt9p031 *mt9p031)
अणु
	पूर्णांक ret;

	/* Ensure RESET_BAR is active */
	अगर (mt9p031->reset) अणु
		gpiod_set_value(mt9p031->reset, 1);
		usleep_range(1000, 2000);
	पूर्ण

	/* Bring up the supplies */
	ret = regulator_bulk_enable(ARRAY_SIZE(mt9p031->regulators),
				   mt9p031->regulators);
	अगर (ret < 0)
		वापस ret;

	/* Enable घड़ी */
	अगर (mt9p031->clk) अणु
		ret = clk_prepare_enable(mt9p031->clk);
		अगर (ret) अणु
			regulator_bulk_disable(ARRAY_SIZE(mt9p031->regulators),
					       mt9p031->regulators);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Now RESET_BAR must be high */
	अगर (mt9p031->reset) अणु
		gpiod_set_value(mt9p031->reset, 0);
		usleep_range(1000, 2000);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt9p031_घातer_off(काष्ठा mt9p031 *mt9p031)
अणु
	अगर (mt9p031->reset) अणु
		gpiod_set_value(mt9p031->reset, 1);
		usleep_range(1000, 2000);
	पूर्ण

	regulator_bulk_disable(ARRAY_SIZE(mt9p031->regulators),
			       mt9p031->regulators);

	clk_disable_unprepare(mt9p031->clk);
पूर्ण

अटल पूर्णांक __mt9p031_set_घातer(काष्ठा mt9p031 *mt9p031, bool on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	पूर्णांक ret;

	अगर (!on) अणु
		mt9p031_घातer_off(mt9p031);
		वापस 0;
	पूर्ण

	ret = mt9p031_घातer_on(mt9p031);
	अगर (ret < 0)
		वापस ret;

	ret = mt9p031_reset(mt9p031);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to reset the camera\n");
		वापस ret;
	पूर्ण

	वापस v4l2_ctrl_handler_setup(&mt9p031->ctrls);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev video operations
 */

अटल पूर्णांक mt9p031_set_params(काष्ठा mt9p031 *mt9p031)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat = &mt9p031->क्रमmat;
	स्थिर काष्ठा v4l2_rect *crop = &mt9p031->crop;
	अचिन्हित पूर्णांक hblank;
	अचिन्हित पूर्णांक vblank;
	अचिन्हित पूर्णांक xskip;
	अचिन्हित पूर्णांक yskip;
	अचिन्हित पूर्णांक xbin;
	अचिन्हित पूर्णांक ybin;
	पूर्णांक ret;

	/* Winकरोws position and size.
	 *
	 * TODO: Make sure the start coordinates and winकरोw size match the
	 * skipping, binning and mirroring (see description of रेजिस्टरs 2 and 4
	 * in table 13, and Binning section on page 41).
	 */
	ret = mt9p031_ग_लिखो(client, MT9P031_COLUMN_START, crop->left);
	अगर (ret < 0)
		वापस ret;
	ret = mt9p031_ग_लिखो(client, MT9P031_ROW_START, crop->top);
	अगर (ret < 0)
		वापस ret;
	ret = mt9p031_ग_लिखो(client, MT9P031_WINDOW_WIDTH, crop->width - 1);
	अगर (ret < 0)
		वापस ret;
	ret = mt9p031_ग_लिखो(client, MT9P031_WINDOW_HEIGHT, crop->height - 1);
	अगर (ret < 0)
		वापस ret;

	/* Row and column binning and skipping. Use the maximum binning value
	 * compatible with the skipping settings.
	 */
	xskip = DIV_ROUND_CLOSEST(crop->width, क्रमmat->width);
	yskip = DIV_ROUND_CLOSEST(crop->height, क्रमmat->height);
	xbin = 1 << (ffs(xskip) - 1);
	ybin = 1 << (ffs(yskip) - 1);

	ret = mt9p031_ग_लिखो(client, MT9P031_COLUMN_ADDRESS_MODE,
			    ((xbin - 1) << 4) | (xskip - 1));
	अगर (ret < 0)
		वापस ret;
	ret = mt9p031_ग_लिखो(client, MT9P031_ROW_ADDRESS_MODE,
			    ((ybin - 1) << 4) | (yskip - 1));
	अगर (ret < 0)
		वापस ret;

	/* Blanking - use minimum value क्रम horizontal blanking and शेष
	 * value क्रम vertical blanking.
	 */
	hblank = 346 * ybin + 64 + (80 >> min_t(अचिन्हित पूर्णांक, xbin, 3));
	vblank = MT9P031_VERTICAL_BLANK_DEF;

	ret = mt9p031_ग_लिखो(client, MT9P031_HORIZONTAL_BLANK, hblank - 1);
	अगर (ret < 0)
		वापस ret;
	ret = mt9p031_ग_लिखो(client, MT9P031_VERTICAL_BLANK, vblank - 1);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक mt9p031_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);
	पूर्णांक ret;

	अगर (!enable) अणु
		/* Stop sensor पढ़ोout */
		ret = mt9p031_set_output_control(mt9p031,
						 MT9P031_OUTPUT_CONTROL_CEN, 0);
		अगर (ret < 0)
			वापस ret;

		वापस mt9p031_pll_disable(mt9p031);
	पूर्ण

	ret = mt9p031_set_params(mt9p031);
	अगर (ret < 0)
		वापस ret;

	/* Switch to master "normal" mode */
	ret = mt9p031_set_output_control(mt9p031, 0,
					 MT9P031_OUTPUT_CONTROL_CEN);
	अगर (ret < 0)
		वापस ret;

	वापस mt9p031_pll_enable(mt9p031);
पूर्ण

अटल पूर्णांक mt9p031_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);

	अगर (code->pad || code->index)
		वापस -EINVAL;

	code->code = mt9p031->क्रमmat.code;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);

	अगर (fse->index >= 8 || fse->code != mt9p031->क्रमmat.code)
		वापस -EINVAL;

	fse->min_width = MT9P031_WINDOW_WIDTH_DEF
		       / min_t(अचिन्हित पूर्णांक, 7, fse->index + 1);
	fse->max_width = fse->min_width;
	fse->min_height = MT9P031_WINDOW_HEIGHT_DEF / (fse->index + 1);
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__mt9p031_get_pad_क्रमmat(काष्ठा mt9p031 *mt9p031, काष्ठा v4l2_subdev_pad_config *cfg,
			 अचिन्हित पूर्णांक pad, u32 which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&mt9p031->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &mt9p031->क्रमmat;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा v4l2_rect *
__mt9p031_get_pad_crop(काष्ठा mt9p031 *mt9p031, काष्ठा v4l2_subdev_pad_config *cfg,
		     अचिन्हित पूर्णांक pad, u32 which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&mt9p031->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &mt9p031->crop;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9p031_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);

	fmt->क्रमmat = *__mt9p031_get_pad_क्रमmat(mt9p031, cfg, fmt->pad,
						fmt->which);
	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक hratio;
	अचिन्हित पूर्णांक vratio;

	__crop = __mt9p031_get_pad_crop(mt9p031, cfg, क्रमmat->pad,
					क्रमmat->which);

	/* Clamp the width and height to aव्योम भागiding by zero. */
	width = clamp_t(अचिन्हित पूर्णांक, ALIGN(क्रमmat->क्रमmat.width, 2),
			max_t(अचिन्हित पूर्णांक, __crop->width / 7,
			      MT9P031_WINDOW_WIDTH_MIN),
			__crop->width);
	height = clamp_t(अचिन्हित पूर्णांक, ALIGN(क्रमmat->क्रमmat.height, 2),
			 max_t(अचिन्हित पूर्णांक, __crop->height / 8,
			       MT9P031_WINDOW_HEIGHT_MIN),
			 __crop->height);

	hratio = DIV_ROUND_CLOSEST(__crop->width, width);
	vratio = DIV_ROUND_CLOSEST(__crop->height, height);

	__क्रमmat = __mt9p031_get_pad_क्रमmat(mt9p031, cfg, क्रमmat->pad,
					    क्रमmat->which);
	__क्रमmat->width = __crop->width / hratio;
	__क्रमmat->height = __crop->height / vratio;

	क्रमmat->क्रमmat = *__क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_get_selection(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	sel->r = *__mt9p031_get_pad_crop(mt9p031, cfg, sel->pad, sel->which);
	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_set_selection(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	काष्ठा v4l2_rect rect;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	/* Clamp the crop rectangle boundaries and align them to a multiple of 2
	 * pixels to ensure a GRBG Bayer pattern.
	 */
	rect.left = clamp(ALIGN(sel->r.left, 2), MT9P031_COLUMN_START_MIN,
			  MT9P031_COLUMN_START_MAX);
	rect.top = clamp(ALIGN(sel->r.top, 2), MT9P031_ROW_START_MIN,
			 MT9P031_ROW_START_MAX);
	rect.width = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.width, 2),
			     MT9P031_WINDOW_WIDTH_MIN,
			     MT9P031_WINDOW_WIDTH_MAX);
	rect.height = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.height, 2),
			      MT9P031_WINDOW_HEIGHT_MIN,
			      MT9P031_WINDOW_HEIGHT_MAX);

	rect.width = min_t(अचिन्हित पूर्णांक, rect.width,
			   MT9P031_PIXEL_ARRAY_WIDTH - rect.left);
	rect.height = min_t(अचिन्हित पूर्णांक, rect.height,
			    MT9P031_PIXEL_ARRAY_HEIGHT - rect.top);

	__crop = __mt9p031_get_pad_crop(mt9p031, cfg, sel->pad, sel->which);

	अगर (rect.width != __crop->width || rect.height != __crop->height) अणु
		/* Reset the output image size अगर the crop rectangle size has
		 * been modअगरied.
		 */
		__क्रमmat = __mt9p031_get_pad_क्रमmat(mt9p031, cfg, sel->pad,
						    sel->which);
		__क्रमmat->width = rect.width;
		__क्रमmat->height = rect.height;
	पूर्ण

	*__crop = rect;
	sel->r = rect;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev control operations
 */

#घोषणा V4L2_CID_BLC_AUTO		(V4L2_CID_USER_BASE | 0x1002)
#घोषणा V4L2_CID_BLC_TARGET_LEVEL	(V4L2_CID_USER_BASE | 0x1003)
#घोषणा V4L2_CID_BLC_ANALOG_OFFSET	(V4L2_CID_USER_BASE | 0x1004)
#घोषणा V4L2_CID_BLC_DIGITAL_OFFSET	(V4L2_CID_USER_BASE | 0x1005)

अटल पूर्णांक mt9p031_restore_blc(काष्ठा mt9p031 *mt9p031)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	पूर्णांक ret;

	अगर (mt9p031->blc_स्वतः->cur.val != 0) अणु
		ret = mt9p031_set_mode2(mt9p031, 0,
					MT9P031_READ_MODE_2_ROW_BLC);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (mt9p031->blc_offset->cur.val != 0) अणु
		ret = mt9p031_ग_लिखो(client, MT9P031_ROW_BLACK_TARGET,
				    mt9p031->blc_offset->cur.val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9p031 *mt9p031 =
			container_of(ctrl->handler, काष्ठा mt9p031, ctrls);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9p031->subdev);
	u16 data;
	पूर्णांक ret;

	अगर (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		ret = mt9p031_ग_लिखो(client, MT9P031_SHUTTER_WIDTH_UPPER,
				    (ctrl->val >> 16) & 0xffff);
		अगर (ret < 0)
			वापस ret;

		वापस mt9p031_ग_लिखो(client, MT9P031_SHUTTER_WIDTH_LOWER,
				     ctrl->val & 0xffff);

	हाल V4L2_CID_GAIN:
		/* Gain is controlled by 2 analog stages and a digital stage.
		 * Valid values क्रम the 3 stages are
		 *
		 * Stage                Min     Max     Step
		 * ------------------------------------------
		 * First analog stage   x1      x2      1
		 * Second analog stage  x1      x4      0.125
		 * Digital stage        x1      x16     0.125
		 *
		 * To minimize noise, the gain stages should be used in the
		 * second analog stage, first analog stage, digital stage order.
		 * Gain from a previous stage should be pushed to its maximum
		 * value beक्रमe the next stage is used.
		 */
		अगर (ctrl->val <= 32) अणु
			data = ctrl->val;
		पूर्ण अन्यथा अगर (ctrl->val <= 64) अणु
			ctrl->val &= ~1;
			data = (1 << 6) | (ctrl->val >> 1);
		पूर्ण अन्यथा अणु
			ctrl->val &= ~7;
			data = ((ctrl->val - 64) << 5) | (1 << 6) | 32;
		पूर्ण

		वापस mt9p031_ग_लिखो(client, MT9P031_GLOBAL_GAIN, data);

	हाल V4L2_CID_HFLIP:
		अगर (ctrl->val)
			वापस mt9p031_set_mode2(mt9p031,
					0, MT9P031_READ_MODE_2_COL_MIR);
		अन्यथा
			वापस mt9p031_set_mode2(mt9p031,
					MT9P031_READ_MODE_2_COL_MIR, 0);

	हाल V4L2_CID_VFLIP:
		अगर (ctrl->val)
			वापस mt9p031_set_mode2(mt9p031,
					0, MT9P031_READ_MODE_2_ROW_MIR);
		अन्यथा
			वापस mt9p031_set_mode2(mt9p031,
					MT9P031_READ_MODE_2_ROW_MIR, 0);

	हाल V4L2_CID_TEST_PATTERN:
		/* The digital side of the Black Level Calibration function must
		 * be disabled when generating a test pattern to aव्योम artअगरacts
		 * in the image. Activate (deactivate) the BLC-related controls
		 * when the test pattern is enabled (disabled).
		 */
		v4l2_ctrl_activate(mt9p031->blc_स्वतः, ctrl->val == 0);
		v4l2_ctrl_activate(mt9p031->blc_offset, ctrl->val == 0);

		अगर (!ctrl->val) अणु
			/* Restore the BLC settings. */
			ret = mt9p031_restore_blc(mt9p031);
			अगर (ret < 0)
				वापस ret;

			वापस mt9p031_ग_लिखो(client, MT9P031_TEST_PATTERN,
					     MT9P031_TEST_PATTERN_DISABLE);
		पूर्ण

		ret = mt9p031_ग_लिखो(client, MT9P031_TEST_PATTERN_GREEN, 0x05a0);
		अगर (ret < 0)
			वापस ret;
		ret = mt9p031_ग_लिखो(client, MT9P031_TEST_PATTERN_RED, 0x0a50);
		अगर (ret < 0)
			वापस ret;
		ret = mt9p031_ग_लिखो(client, MT9P031_TEST_PATTERN_BLUE, 0x0aa0);
		अगर (ret < 0)
			वापस ret;

		/* Disable digital BLC when generating a test pattern. */
		ret = mt9p031_set_mode2(mt9p031, MT9P031_READ_MODE_2_ROW_BLC,
					0);
		अगर (ret < 0)
			वापस ret;

		ret = mt9p031_ग_लिखो(client, MT9P031_ROW_BLACK_DEF_OFFSET, 0);
		अगर (ret < 0)
			वापस ret;

		वापस mt9p031_ग_लिखो(client, MT9P031_TEST_PATTERN,
				((ctrl->val - 1) << MT9P031_TEST_PATTERN_SHIFT)
				| MT9P031_TEST_PATTERN_ENABLE);

	हाल V4L2_CID_BLC_AUTO:
		ret = mt9p031_set_mode2(mt9p031,
				ctrl->val ? 0 : MT9P031_READ_MODE_2_ROW_BLC,
				ctrl->val ? MT9P031_READ_MODE_2_ROW_BLC : 0);
		अगर (ret < 0)
			वापस ret;

		वापस mt9p031_ग_लिखो(client, MT9P031_BLACK_LEVEL_CALIBRATION,
				     ctrl->val ? 0 : MT9P031_BLC_MANUAL_BLC);

	हाल V4L2_CID_BLC_TARGET_LEVEL:
		वापस mt9p031_ग_लिखो(client, MT9P031_ROW_BLACK_TARGET,
				     ctrl->val);

	हाल V4L2_CID_BLC_ANALOG_OFFSET:
		data = ctrl->val & ((1 << 9) - 1);

		ret = mt9p031_ग_लिखो(client, MT9P031_GREEN1_OFFSET, data);
		अगर (ret < 0)
			वापस ret;
		ret = mt9p031_ग_लिखो(client, MT9P031_GREEN2_OFFSET, data);
		अगर (ret < 0)
			वापस ret;
		ret = mt9p031_ग_लिखो(client, MT9P031_RED_OFFSET, data);
		अगर (ret < 0)
			वापस ret;
		वापस mt9p031_ग_लिखो(client, MT9P031_BLUE_OFFSET, data);

	हाल V4L2_CID_BLC_DIGITAL_OFFSET:
		वापस mt9p031_ग_लिखो(client, MT9P031_ROW_BLACK_DEF_OFFSET,
				     ctrl->val & ((1 << 12) - 1));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9p031_ctrl_ops = अणु
	.s_ctrl = mt9p031_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mt9p031_test_pattern_menu[] = अणु
	"Disabled",
	"Color Field",
	"Horizontal Gradient",
	"Vertical Gradient",
	"Diagonal Gradient",
	"Classic Test Pattern",
	"Walking 1s",
	"Monochrome Horizontal Bars",
	"Monochrome Vertical Bars",
	"Vertical Color Bars",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9p031_ctrls[] = अणु
	अणु
		.ops		= &mt9p031_ctrl_ops,
		.id		= V4L2_CID_BLC_AUTO,
		.type		= V4L2_CTRL_TYPE_BOOLEAN,
		.name		= "BLC, Auto",
		.min		= 0,
		.max		= 1,
		.step		= 1,
		.def		= 1,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9p031_ctrl_ops,
		.id		= V4L2_CID_BLC_TARGET_LEVEL,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "BLC Target Level",
		.min		= 0,
		.max		= 4095,
		.step		= 1,
		.def		= 168,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9p031_ctrl_ops,
		.id		= V4L2_CID_BLC_ANALOG_OFFSET,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "BLC Analog Offset",
		.min		= -255,
		.max		= 255,
		.step		= 1,
		.def		= 32,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9p031_ctrl_ops,
		.id		= V4L2_CID_BLC_DIGITAL_OFFSET,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "BLC Digital Offset",
		.min		= -2048,
		.max		= 2047,
		.step		= 1,
		.def		= 40,
		.flags		= 0,
	पूर्ण
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev core operations
 */

अटल पूर्णांक mt9p031_set_घातer(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&mt9p031->घातer_lock);

	/* If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (mt9p031->घातer_count == !on) अणु
		ret = __mt9p031_set_घातer(mt9p031, !!on);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* Update the घातer count. */
	mt9p031->घातer_count += on ? 1 : -1;
	WARN_ON(mt9p031->घातer_count < 0);

out:
	mutex_unlock(&mt9p031->घातer_lock);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev पूर्णांकernal operations
 */

अटल पूर्णांक mt9p031_रेजिस्टरed(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);
	s32 data;
	पूर्णांक ret;

	ret = mt9p031_घातer_on(mt9p031);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "MT9P031 power up failed\n");
		वापस ret;
	पूर्ण

	/* Read out the chip version रेजिस्टर */
	data = mt9p031_पढ़ो(client, MT9P031_CHIP_VERSION);
	mt9p031_घातer_off(mt9p031);

	अगर (data != MT9P031_CHIP_VERSION_VALUE) अणु
		dev_err(&client->dev, "MT9P031 not detected, wrong version "
			"0x%04x\n", data);
		वापस -ENODEV;
	पूर्ण

	dev_info(&client->dev, "MT9P031 detected at address 0x%02x\n",
		 client->addr);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9p031_खोलो(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;

	crop = v4l2_subdev_get_try_crop(subdev, fh->pad, 0);
	crop->left = MT9P031_COLUMN_START_DEF;
	crop->top = MT9P031_ROW_START_DEF;
	crop->width = MT9P031_WINDOW_WIDTH_DEF;
	crop->height = MT9P031_WINDOW_HEIGHT_DEF;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, fh->pad, 0);

	अगर (mt9p031->model == MT9P031_MODEL_MONOCHROME)
		क्रमmat->code = MEDIA_BUS_FMT_Y12_1X12;
	अन्यथा
		क्रमmat->code = MEDIA_BUS_FMT_SGRBG12_1X12;

	क्रमmat->width = MT9P031_WINDOW_WIDTH_DEF;
	क्रमmat->height = MT9P031_WINDOW_HEIGHT_DEF;
	क्रमmat->field = V4L2_FIELD_NONE;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	वापस mt9p031_set_घातer(subdev, 1);
पूर्ण

अटल पूर्णांक mt9p031_बंद(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस mt9p031_set_घातer(subdev, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9p031_subdev_core_ops = अणु
	.s_घातer        = mt9p031_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9p031_subdev_video_ops = अणु
	.s_stream       = mt9p031_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9p031_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = mt9p031_क्रमागत_mbus_code,
	.क्रमागत_frame_size = mt9p031_क्रमागत_frame_size,
	.get_fmt = mt9p031_get_क्रमmat,
	.set_fmt = mt9p031_set_क्रमmat,
	.get_selection = mt9p031_get_selection,
	.set_selection = mt9p031_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9p031_subdev_ops = अणु
	.core   = &mt9p031_subdev_core_ops,
	.video  = &mt9p031_subdev_video_ops,
	.pad    = &mt9p031_subdev_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops mt9p031_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = mt9p031_रेजिस्टरed,
	.खोलो = mt9p031_खोलो,
	.बंद = mt9p031_बंद,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Driver initialization and probing
 */

अटल काष्ठा mt9p031_platक्रमm_data *
mt9p031_get_pdata(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9p031_platक्रमm_data *pdata;
	काष्ठा device_node *np;

	अगर (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		वापस client->dev.platक्रमm_data;

	np = of_graph_get_next_endpoपूर्णांक(client->dev.of_node, शून्य);
	अगर (!np)
		वापस शून्य;

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		जाओ करोne;

	of_property_पढ़ो_u32(np, "input-clock-frequency", &pdata->ext_freq);
	of_property_पढ़ो_u32(np, "pixel-clock-frequency", &pdata->target_freq);

करोne:
	of_node_put(np);
	वापस pdata;
पूर्ण

अटल पूर्णांक mt9p031_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा mt9p031_platक्रमm_data *pdata = mt9p031_get_pdata(client);
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा mt9p031 *mt9p031;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_warn(&client->dev,
			"I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		वापस -EIO;
	पूर्ण

	mt9p031 = devm_kzalloc(&client->dev, माप(*mt9p031), GFP_KERNEL);
	अगर (mt9p031 == शून्य)
		वापस -ENOMEM;

	mt9p031->pdata = pdata;
	mt9p031->output_control	= MT9P031_OUTPUT_CONTROL_DEF;
	mt9p031->mode2 = MT9P031_READ_MODE_2_ROW_BLC;
	mt9p031->model = did->driver_data;

	mt9p031->regulators[0].supply = "vdd";
	mt9p031->regulators[1].supply = "vdd_io";
	mt9p031->regulators[2].supply = "vaa";

	ret = devm_regulator_bulk_get(&client->dev, 3, mt9p031->regulators);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to get regulators\n");
		वापस ret;
	पूर्ण

	mutex_init(&mt9p031->घातer_lock);

	v4l2_ctrl_handler_init(&mt9p031->ctrls, ARRAY_SIZE(mt9p031_ctrls) + 6);

	v4l2_ctrl_new_std(&mt9p031->ctrls, &mt9p031_ctrl_ops,
			  V4L2_CID_EXPOSURE, MT9P031_SHUTTER_WIDTH_MIN,
			  MT9P031_SHUTTER_WIDTH_MAX, 1,
			  MT9P031_SHUTTER_WIDTH_DEF);
	v4l2_ctrl_new_std(&mt9p031->ctrls, &mt9p031_ctrl_ops,
			  V4L2_CID_GAIN, MT9P031_GLOBAL_GAIN_MIN,
			  MT9P031_GLOBAL_GAIN_MAX, 1, MT9P031_GLOBAL_GAIN_DEF);
	v4l2_ctrl_new_std(&mt9p031->ctrls, &mt9p031_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9p031->ctrls, &mt9p031_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9p031->ctrls, &mt9p031_ctrl_ops,
			  V4L2_CID_PIXEL_RATE, pdata->target_freq,
			  pdata->target_freq, 1, pdata->target_freq);
	v4l2_ctrl_new_std_menu_items(&mt9p031->ctrls, &mt9p031_ctrl_ops,
			  V4L2_CID_TEST_PATTERN,
			  ARRAY_SIZE(mt9p031_test_pattern_menu) - 1, 0,
			  0, mt9p031_test_pattern_menu);

	क्रम (i = 0; i < ARRAY_SIZE(mt9p031_ctrls); ++i)
		v4l2_ctrl_new_custom(&mt9p031->ctrls, &mt9p031_ctrls[i], शून्य);

	mt9p031->subdev.ctrl_handler = &mt9p031->ctrls;

	अगर (mt9p031->ctrls.error) अणु
		prपूर्णांकk(KERN_INFO "%s: control initialization error %d\n",
		       __func__, mt9p031->ctrls.error);
		ret = mt9p031->ctrls.error;
		जाओ करोne;
	पूर्ण

	mt9p031->blc_स्वतः = v4l2_ctrl_find(&mt9p031->ctrls, V4L2_CID_BLC_AUTO);
	mt9p031->blc_offset = v4l2_ctrl_find(&mt9p031->ctrls,
					     V4L2_CID_BLC_DIGITAL_OFFSET);

	v4l2_i2c_subdev_init(&mt9p031->subdev, client, &mt9p031_subdev_ops);
	mt9p031->subdev.पूर्णांकernal_ops = &mt9p031_subdev_पूर्णांकernal_ops;

	mt9p031->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	mt9p031->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&mt9p031->subdev.entity, 1, &mt9p031->pad);
	अगर (ret < 0)
		जाओ करोne;

	mt9p031->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	mt9p031->crop.width = MT9P031_WINDOW_WIDTH_DEF;
	mt9p031->crop.height = MT9P031_WINDOW_HEIGHT_DEF;
	mt9p031->crop.left = MT9P031_COLUMN_START_DEF;
	mt9p031->crop.top = MT9P031_ROW_START_DEF;

	अगर (mt9p031->model == MT9P031_MODEL_MONOCHROME)
		mt9p031->क्रमmat.code = MEDIA_BUS_FMT_Y12_1X12;
	अन्यथा
		mt9p031->क्रमmat.code = MEDIA_BUS_FMT_SGRBG12_1X12;

	mt9p031->क्रमmat.width = MT9P031_WINDOW_WIDTH_DEF;
	mt9p031->क्रमmat.height = MT9P031_WINDOW_HEIGHT_DEF;
	mt9p031->क्रमmat.field = V4L2_FIELD_NONE;
	mt9p031->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;

	mt9p031->reset = devm_gpiod_get_optional(&client->dev, "reset",
						 GPIOD_OUT_HIGH);

	ret = mt9p031_clk_setup(mt9p031);
	अगर (ret)
		जाओ करोne;

	ret = v4l2_async_रेजिस्टर_subdev(&mt9p031->subdev);

करोne:
	अगर (ret < 0) अणु
		v4l2_ctrl_handler_मुक्त(&mt9p031->ctrls);
		media_entity_cleanup(&mt9p031->subdev.entity);
		mutex_destroy(&mt9p031->घातer_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt9p031_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा mt9p031 *mt9p031 = to_mt9p031(subdev);

	v4l2_ctrl_handler_मुक्त(&mt9p031->ctrls);
	v4l2_async_unरेजिस्टर_subdev(subdev);
	media_entity_cleanup(&subdev->entity);
	mutex_destroy(&mt9p031->घातer_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mt9p031_id[] = अणु
	अणु "mt9p031", MT9P031_MODEL_COLOR पूर्ण,
	अणु "mt9p031m", MT9P031_MODEL_MONOCHROME पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt9p031_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id mt9p031_of_match[] = अणु
	अणु .compatible = "aptina,mt9p031", पूर्ण,
	अणु .compatible = "aptina,mt9p031m", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt9p031_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver mt9p031_i2c_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(mt9p031_of_match),
		.name = "mt9p031",
	पूर्ण,
	.probe          = mt9p031_probe,
	.हटाओ         = mt9p031_हटाओ,
	.id_table       = mt9p031_id,
पूर्ण;

module_i2c_driver(mt9p031_i2c_driver);

MODULE_DESCRIPTION("Aptina MT9P031 Camera driver");
MODULE_AUTHOR("Bastian Hecht <hechtb@gmail.com>");
MODULE_LICENSE("GPL v2");
