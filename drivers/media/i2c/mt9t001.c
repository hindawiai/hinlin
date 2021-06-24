<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MT9T001 CMOS Image Sensor from Aptina (Micron)
 *
 * Copyright (C) 2010-2011, Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *
 * Based on the MT9M001 driver,
 *
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-mediabus.h>

#समावेश <media/i2c/mt9t001.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा MT9T001_PIXEL_ARRAY_HEIGHT			1568
#घोषणा MT9T001_PIXEL_ARRAY_WIDTH			2112

#घोषणा MT9T001_CHIP_VERSION				0x00
#घोषणा		MT9T001_CHIP_ID				0x1621
#घोषणा MT9T001_ROW_START				0x01
#घोषणा		MT9T001_ROW_START_MIN			0
#घोषणा		MT9T001_ROW_START_DEF			20
#घोषणा		MT9T001_ROW_START_MAX			1534
#घोषणा MT9T001_COLUMN_START				0x02
#घोषणा		MT9T001_COLUMN_START_MIN		0
#घोषणा		MT9T001_COLUMN_START_DEF		32
#घोषणा		MT9T001_COLUMN_START_MAX		2046
#घोषणा MT9T001_WINDOW_HEIGHT				0x03
#घोषणा		MT9T001_WINDOW_HEIGHT_MIN		1
#घोषणा		MT9T001_WINDOW_HEIGHT_DEF		1535
#घोषणा		MT9T001_WINDOW_HEIGHT_MAX		1567
#घोषणा MT9T001_WINDOW_WIDTH				0x04
#घोषणा		MT9T001_WINDOW_WIDTH_MIN		1
#घोषणा		MT9T001_WINDOW_WIDTH_DEF		2047
#घोषणा		MT9T001_WINDOW_WIDTH_MAX		2111
#घोषणा MT9T001_HORIZONTAL_BLANKING			0x05
#घोषणा		MT9T001_HORIZONTAL_BLANKING_MIN		21
#घोषणा		MT9T001_HORIZONTAL_BLANKING_MAX		1023
#घोषणा MT9T001_VERTICAL_BLANKING			0x06
#घोषणा		MT9T001_VERTICAL_BLANKING_MIN		3
#घोषणा		MT9T001_VERTICAL_BLANKING_MAX		1023
#घोषणा MT9T001_OUTPUT_CONTROL				0x07
#घोषणा		MT9T001_OUTPUT_CONTROL_SYNC		(1 << 0)
#घोषणा		MT9T001_OUTPUT_CONTROL_CHIP_ENABLE	(1 << 1)
#घोषणा		MT9T001_OUTPUT_CONTROL_TEST_DATA	(1 << 6)
#घोषणा		MT9T001_OUTPUT_CONTROL_DEF		0x0002
#घोषणा MT9T001_SHUTTER_WIDTH_HIGH			0x08
#घोषणा MT9T001_SHUTTER_WIDTH_LOW			0x09
#घोषणा		MT9T001_SHUTTER_WIDTH_MIN		1
#घोषणा		MT9T001_SHUTTER_WIDTH_DEF		1561
#घोषणा		MT9T001_SHUTTER_WIDTH_MAX		(1024 * 1024)
#घोषणा MT9T001_PIXEL_CLOCK				0x0a
#घोषणा		MT9T001_PIXEL_CLOCK_INVERT		(1 << 15)
#घोषणा		MT9T001_PIXEL_CLOCK_SHIFT_MASK		(7 << 8)
#घोषणा		MT9T001_PIXEL_CLOCK_SHIFT_SHIFT		8
#घोषणा		MT9T001_PIXEL_CLOCK_DIVIDE_MASK		(0x7f << 0)
#घोषणा MT9T001_FRAME_RESTART				0x0b
#घोषणा MT9T001_SHUTTER_DELAY				0x0c
#घोषणा		MT9T001_SHUTTER_DELAY_MAX		2047
#घोषणा MT9T001_RESET					0x0d
#घोषणा MT9T001_READ_MODE1				0x1e
#घोषणा		MT9T001_READ_MODE_SNAPSHOT		(1 << 8)
#घोषणा		MT9T001_READ_MODE_STROBE_ENABLE		(1 << 9)
#घोषणा		MT9T001_READ_MODE_STROBE_WIDTH		(1 << 10)
#घोषणा		MT9T001_READ_MODE_STROBE_OVERRIDE	(1 << 11)
#घोषणा MT9T001_READ_MODE2				0x20
#घोषणा		MT9T001_READ_MODE_BAD_FRAMES		(1 << 0)
#घोषणा		MT9T001_READ_MODE_LINE_VALID_CONTINUOUS	(1 << 9)
#घोषणा		MT9T001_READ_MODE_LINE_VALID_FRAME	(1 << 10)
#घोषणा MT9T001_READ_MODE3				0x21
#घोषणा		MT9T001_READ_MODE_GLOBAL_RESET		(1 << 0)
#घोषणा		MT9T001_READ_MODE_GHST_CTL		(1 << 1)
#घोषणा MT9T001_ROW_ADDRESS_MODE			0x22
#घोषणा		MT9T001_ROW_SKIP_MASK			(7 << 0)
#घोषणा		MT9T001_ROW_BIN_MASK			(3 << 3)
#घोषणा		MT9T001_ROW_BIN_SHIFT			3
#घोषणा MT9T001_COLUMN_ADDRESS_MODE			0x23
#घोषणा		MT9T001_COLUMN_SKIP_MASK		(7 << 0)
#घोषणा		MT9T001_COLUMN_BIN_MASK			(3 << 3)
#घोषणा		MT9T001_COLUMN_BIN_SHIFT		3
#घोषणा MT9T001_GREEN1_GAIN				0x2b
#घोषणा MT9T001_BLUE_GAIN				0x2c
#घोषणा MT9T001_RED_GAIN				0x2d
#घोषणा MT9T001_GREEN2_GAIN				0x2e
#घोषणा MT9T001_TEST_DATA				0x32
#घोषणा MT9T001_GLOBAL_GAIN				0x35
#घोषणा		MT9T001_GLOBAL_GAIN_MIN			8
#घोषणा		MT9T001_GLOBAL_GAIN_MAX			1024
#घोषणा MT9T001_BLACK_LEVEL				0x49
#घोषणा MT9T001_ROW_BLACK_DEFAULT_OFFSET		0x4b
#घोषणा MT9T001_BLC_DELTA_THRESHOLDS			0x5d
#घोषणा MT9T001_CAL_THRESHOLDS				0x5f
#घोषणा MT9T001_GREEN1_OFFSET				0x60
#घोषणा MT9T001_GREEN2_OFFSET				0x61
#घोषणा MT9T001_BLACK_LEVEL_CALIBRATION			0x62
#घोषणा		MT9T001_BLACK_LEVEL_OVERRIDE		(1 << 0)
#घोषणा		MT9T001_BLACK_LEVEL_DISABLE_OFFSET	(1 << 1)
#घोषणा		MT9T001_BLACK_LEVEL_RECALCULATE		(1 << 12)
#घोषणा		MT9T001_BLACK_LEVEL_LOCK_RED_BLUE	(1 << 13)
#घोषणा		MT9T001_BLACK_LEVEL_LOCK_GREEN		(1 << 14)
#घोषणा MT9T001_RED_OFFSET				0x63
#घोषणा MT9T001_BLUE_OFFSET				0x64

काष्ठा mt9t001 अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;

	काष्ठा clk *clk;
	काष्ठा regulator_bulk_data regulators[2];

	काष्ठा mutex घातer_lock; /* lock to protect घातer_count */
	पूर्णांक घातer_count;

	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा v4l2_rect crop;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *gains[4];

	u16 output_control;
	u16 black_level;
पूर्ण;

अटल अंतरभूत काष्ठा mt9t001 *to_mt9t001(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा mt9t001, subdev);
पूर्ण

अटल पूर्णांक mt9t001_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
पूर्ण

अटल पूर्णांक mt9t001_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u16 data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(client, reg, data);
पूर्ण

अटल पूर्णांक mt9t001_set_output_control(काष्ठा mt9t001 *mt9t001, u16 clear,
				      u16 set)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9t001->subdev);
	u16 value = (mt9t001->output_control & ~clear) | set;
	पूर्णांक ret;

	अगर (value == mt9t001->output_control)
		वापस 0;

	ret = mt9t001_ग_लिखो(client, MT9T001_OUTPUT_CONTROL, value);
	अगर (ret < 0)
		वापस ret;

	mt9t001->output_control = value;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9t001_reset(काष्ठा mt9t001 *mt9t001)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9t001->subdev);
	पूर्णांक ret;

	/* Reset the chip and stop data पढ़ो out */
	ret = mt9t001_ग_लिखो(client, MT9T001_RESET, 1);
	अगर (ret < 0)
		वापस ret;

	ret = mt9t001_ग_लिखो(client, MT9T001_RESET, 0);
	अगर (ret < 0)
		वापस ret;

	mt9t001->output_control = MT9T001_OUTPUT_CONTROL_DEF;

	वापस mt9t001_set_output_control(mt9t001,
					  MT9T001_OUTPUT_CONTROL_CHIP_ENABLE,
					  0);
पूर्ण

अटल पूर्णांक mt9t001_घातer_on(काष्ठा mt9t001 *mt9t001)
अणु
	पूर्णांक ret;

	/* Bring up the supplies */
	ret = regulator_bulk_enable(ARRAY_SIZE(mt9t001->regulators),
				   mt9t001->regulators);
	अगर (ret < 0)
		वापस ret;

	/* Enable घड़ी */
	ret = clk_prepare_enable(mt9t001->clk);
	अगर (ret < 0)
		regulator_bulk_disable(ARRAY_SIZE(mt9t001->regulators),
				       mt9t001->regulators);

	वापस ret;
पूर्ण

अटल व्योम mt9t001_घातer_off(काष्ठा mt9t001 *mt9t001)
अणु
	regulator_bulk_disable(ARRAY_SIZE(mt9t001->regulators),
			       mt9t001->regulators);

	clk_disable_unprepare(mt9t001->clk);
पूर्ण

अटल पूर्णांक __mt9t001_set_घातer(काष्ठा mt9t001 *mt9t001, bool on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9t001->subdev);
	पूर्णांक ret;

	अगर (!on) अणु
		mt9t001_घातer_off(mt9t001);
		वापस 0;
	पूर्ण

	ret = mt9t001_घातer_on(mt9t001);
	अगर (ret < 0)
		वापस ret;

	ret = mt9t001_reset(mt9t001);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to reset the camera\n");
		जाओ e_घातer;
	पूर्ण

	ret = v4l2_ctrl_handler_setup(&mt9t001->ctrls);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to set up control handlers\n");
		जाओ e_घातer;
	पूर्ण

	वापस 0;

e_घातer:
	mt9t001_घातer_off(mt9t001);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev video operations
 */

अटल काष्ठा v4l2_mbus_framefmt *
__mt9t001_get_pad_क्रमmat(काष्ठा mt9t001 *mt9t001, काष्ठा v4l2_subdev_pad_config *cfg,
			 अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&mt9t001->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &mt9t001->क्रमmat;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा v4l2_rect *
__mt9t001_get_pad_crop(काष्ठा mt9t001 *mt9t001, काष्ठा v4l2_subdev_pad_config *cfg,
		       अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_crop(&mt9t001->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &mt9t001->crop;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9t001_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	स्थिर u16 mode = MT9T001_OUTPUT_CONTROL_CHIP_ENABLE;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा mt9t001_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat = &mt9t001->क्रमmat;
	काष्ठा v4l2_rect *crop = &mt9t001->crop;
	अचिन्हित पूर्णांक hratio;
	अचिन्हित पूर्णांक vratio;
	पूर्णांक ret;

	अगर (!enable)
		वापस mt9t001_set_output_control(mt9t001, mode, 0);

	/* Configure the pixel घड़ी polarity */
	अगर (pdata->clk_pol) अणु
		ret  = mt9t001_ग_लिखो(client, MT9T001_PIXEL_CLOCK,
				     MT9T001_PIXEL_CLOCK_INVERT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Configure the winकरोw size and row/column bin */
	hratio = DIV_ROUND_CLOSEST(crop->width, क्रमmat->width);
	vratio = DIV_ROUND_CLOSEST(crop->height, क्रमmat->height);

	ret = mt9t001_ग_लिखो(client, MT9T001_ROW_ADDRESS_MODE, hratio - 1);
	अगर (ret < 0)
		वापस ret;

	ret = mt9t001_ग_लिखो(client, MT9T001_COLUMN_ADDRESS_MODE, vratio - 1);
	अगर (ret < 0)
		वापस ret;

	ret = mt9t001_ग_लिखो(client, MT9T001_COLUMN_START, crop->left);
	अगर (ret < 0)
		वापस ret;

	ret = mt9t001_ग_लिखो(client, MT9T001_ROW_START, crop->top);
	अगर (ret < 0)
		वापस ret;

	ret = mt9t001_ग_लिखो(client, MT9T001_WINDOW_WIDTH, crop->width - 1);
	अगर (ret < 0)
		वापस ret;

	ret = mt9t001_ग_लिखो(client, MT9T001_WINDOW_HEIGHT, crop->height - 1);
	अगर (ret < 0)
		वापस ret;

	/* Switch to master "normal" mode */
	वापस mt9t001_set_output_control(mt9t001, 0, mode);
पूर्ण

अटल पूर्णांक mt9t001_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9t001_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index >= 8 || fse->code != MEDIA_BUS_FMT_SGRBG10_1X10)
		वापस -EINVAL;

	fse->min_width = (MT9T001_WINDOW_WIDTH_DEF + 1) / fse->index;
	fse->max_width = fse->min_width;
	fse->min_height = (MT9T001_WINDOW_HEIGHT_DEF + 1) / fse->index;
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t001_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);

	क्रमmat->क्रमmat = *__mt9t001_get_pad_क्रमmat(mt9t001, cfg, क्रमmat->pad,
						   क्रमmat->which);
	वापस 0;
पूर्ण

अटल पूर्णांक mt9t001_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक hratio;
	अचिन्हित पूर्णांक vratio;

	__crop = __mt9t001_get_pad_crop(mt9t001, cfg, क्रमmat->pad,
					क्रमmat->which);

	/* Clamp the width and height to aव्योम भागiding by zero. */
	width = clamp_t(अचिन्हित पूर्णांक, ALIGN(क्रमmat->क्रमmat.width, 2),
			max_t(अचिन्हित पूर्णांक, __crop->width / 8,
			      MT9T001_WINDOW_HEIGHT_MIN + 1),
			__crop->width);
	height = clamp_t(अचिन्हित पूर्णांक, ALIGN(क्रमmat->क्रमmat.height, 2),
			 max_t(अचिन्हित पूर्णांक, __crop->height / 8,
			       MT9T001_WINDOW_HEIGHT_MIN + 1),
			 __crop->height);

	hratio = DIV_ROUND_CLOSEST(__crop->width, width);
	vratio = DIV_ROUND_CLOSEST(__crop->height, height);

	__क्रमmat = __mt9t001_get_pad_क्रमmat(mt9t001, cfg, क्रमmat->pad,
					    क्रमmat->which);
	__क्रमmat->width = __crop->width / hratio;
	__क्रमmat->height = __crop->height / vratio;

	क्रमmat->क्रमmat = *__क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t001_get_selection(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	sel->r = *__mt9t001_get_pad_crop(mt9t001, cfg, sel->pad, sel->which);
	वापस 0;
पूर्ण

अटल पूर्णांक mt9t001_set_selection(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);
	काष्ठा v4l2_mbus_framefmt *__क्रमmat;
	काष्ठा v4l2_rect *__crop;
	काष्ठा v4l2_rect rect;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	/* Clamp the crop rectangle boundaries and align them to a multiple of 2
	 * pixels.
	 */
	rect.left = clamp(ALIGN(sel->r.left, 2),
			  MT9T001_COLUMN_START_MIN,
			  MT9T001_COLUMN_START_MAX);
	rect.top = clamp(ALIGN(sel->r.top, 2),
			 MT9T001_ROW_START_MIN,
			 MT9T001_ROW_START_MAX);
	rect.width = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.width, 2),
			     MT9T001_WINDOW_WIDTH_MIN + 1,
			     MT9T001_WINDOW_WIDTH_MAX + 1);
	rect.height = clamp_t(अचिन्हित पूर्णांक, ALIGN(sel->r.height, 2),
			      MT9T001_WINDOW_HEIGHT_MIN + 1,
			      MT9T001_WINDOW_HEIGHT_MAX + 1);

	rect.width = min_t(अचिन्हित पूर्णांक, rect.width,
			   MT9T001_PIXEL_ARRAY_WIDTH - rect.left);
	rect.height = min_t(अचिन्हित पूर्णांक, rect.height,
			    MT9T001_PIXEL_ARRAY_HEIGHT - rect.top);

	__crop = __mt9t001_get_pad_crop(mt9t001, cfg, sel->pad, sel->which);

	अगर (rect.width != __crop->width || rect.height != __crop->height) अणु
		/* Reset the output image size अगर the crop rectangle size has
		 * been modअगरied.
		 */
		__क्रमmat = __mt9t001_get_pad_क्रमmat(mt9t001, cfg, sel->pad,
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

#घोषणा V4L2_CID_TEST_PATTERN_COLOR	(V4L2_CID_USER_BASE | 0x1001)
#घोषणा V4L2_CID_BLACK_LEVEL_AUTO	(V4L2_CID_USER_BASE | 0x1002)
#घोषणा V4L2_CID_BLACK_LEVEL_OFFSET	(V4L2_CID_USER_BASE | 0x1003)
#घोषणा V4L2_CID_BLACK_LEVEL_CALIBRATE	(V4L2_CID_USER_BASE | 0x1004)

#घोषणा V4L2_CID_GAIN_RED		(V4L2_CTRL_CLASS_CAMERA | 0x1001)
#घोषणा V4L2_CID_GAIN_GREEN_RED		(V4L2_CTRL_CLASS_CAMERA | 0x1002)
#घोषणा V4L2_CID_GAIN_GREEN_BLUE	(V4L2_CTRL_CLASS_CAMERA | 0x1003)
#घोषणा V4L2_CID_GAIN_BLUE		(V4L2_CTRL_CLASS_CAMERA | 0x1004)

अटल u16 mt9t001_gain_value(s32 *gain)
अणु
	/* Gain is controlled by 2 analog stages and a digital stage. Valid
	 * values क्रम the 3 stages are
	 *
	 * Stage		Min	Max	Step
	 * ------------------------------------------
	 * First analog stage	x1	x2	1
	 * Second analog stage	x1	x4	0.125
	 * Digital stage	x1	x16	0.125
	 *
	 * To minimize noise, the gain stages should be used in the second
	 * analog stage, first analog stage, digital stage order. Gain from a
	 * previous stage should be pushed to its maximum value beक्रमe the next
	 * stage is used.
	 */
	अगर (*gain <= 32)
		वापस *gain;

	अगर (*gain <= 64) अणु
		*gain &= ~1;
		वापस (1 << 6) | (*gain >> 1);
	पूर्ण

	*gain &= ~7;
	वापस ((*gain - 64) << 5) | (1 << 6) | 32;
पूर्ण

अटल पूर्णांक mt9t001_ctrl_मुक्तze(काष्ठा mt9t001 *mt9t001, bool मुक्तze)
अणु
	वापस mt9t001_set_output_control(mt9t001,
		मुक्तze ? 0 : MT9T001_OUTPUT_CONTROL_SYNC,
		मुक्तze ? MT9T001_OUTPUT_CONTROL_SYNC : 0);
पूर्ण

अटल पूर्णांक mt9t001_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अटल स्थिर u8 gains[4] = अणु
		MT9T001_RED_GAIN, MT9T001_GREEN1_GAIN,
		MT9T001_GREEN2_GAIN, MT9T001_BLUE_GAIN
	पूर्ण;

	काष्ठा mt9t001 *mt9t001 =
			container_of(ctrl->handler, काष्ठा mt9t001, ctrls);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9t001->subdev);
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक i;
	u16 value;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN_RED:
	हाल V4L2_CID_GAIN_GREEN_RED:
	हाल V4L2_CID_GAIN_GREEN_BLUE:
	हाल V4L2_CID_GAIN_BLUE:

		/* Disable control updates अगर more than one control has changed
		 * in the cluster.
		 */
		क्रम (i = 0, count = 0; i < 4; ++i) अणु
			काष्ठा v4l2_ctrl *gain = mt9t001->gains[i];

			अगर (gain->val != gain->cur.val)
				count++;
		पूर्ण

		अगर (count > 1) अणु
			ret = mt9t001_ctrl_मुक्तze(mt9t001, true);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		/* Update the gain controls. */
		क्रम (i = 0; i < 4; ++i) अणु
			काष्ठा v4l2_ctrl *gain = mt9t001->gains[i];

			अगर (gain->val == gain->cur.val)
				जारी;

			value = mt9t001_gain_value(&gain->val);
			ret = mt9t001_ग_लिखो(client, gains[i], value);
			अगर (ret < 0) अणु
				mt9t001_ctrl_मुक्तze(mt9t001, false);
				वापस ret;
			पूर्ण
		पूर्ण

		/* Enable control updates. */
		अगर (count > 1) अणु
			ret = mt9t001_ctrl_मुक्तze(mt9t001, false);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		अवरोध;

	हाल V4L2_CID_EXPOSURE:
		ret = mt9t001_ग_लिखो(client, MT9T001_SHUTTER_WIDTH_LOW,
				    ctrl->val & 0xffff);
		अगर (ret < 0)
			वापस ret;

		वापस mt9t001_ग_लिखो(client, MT9T001_SHUTTER_WIDTH_HIGH,
				     ctrl->val >> 16);

	हाल V4L2_CID_TEST_PATTERN:
		वापस mt9t001_set_output_control(mt9t001,
			ctrl->val ? 0 : MT9T001_OUTPUT_CONTROL_TEST_DATA,
			ctrl->val ? MT9T001_OUTPUT_CONTROL_TEST_DATA : 0);

	हाल V4L2_CID_TEST_PATTERN_COLOR:
		वापस mt9t001_ग_लिखो(client, MT9T001_TEST_DATA, ctrl->val << 2);

	हाल V4L2_CID_BLACK_LEVEL_AUTO:
		value = ctrl->val ? 0 : MT9T001_BLACK_LEVEL_OVERRIDE;
		ret = mt9t001_ग_लिखो(client, MT9T001_BLACK_LEVEL_CALIBRATION,
				    value);
		अगर (ret < 0)
			वापस ret;

		mt9t001->black_level = value;
		अवरोध;

	हाल V4L2_CID_BLACK_LEVEL_OFFSET:
		ret = mt9t001_ग_लिखो(client, MT9T001_GREEN1_OFFSET, ctrl->val);
		अगर (ret < 0)
			वापस ret;

		ret = mt9t001_ग_लिखो(client, MT9T001_GREEN2_OFFSET, ctrl->val);
		अगर (ret < 0)
			वापस ret;

		ret = mt9t001_ग_लिखो(client, MT9T001_RED_OFFSET, ctrl->val);
		अगर (ret < 0)
			वापस ret;

		वापस mt9t001_ग_लिखो(client, MT9T001_BLUE_OFFSET, ctrl->val);

	हाल V4L2_CID_BLACK_LEVEL_CALIBRATE:
		वापस mt9t001_ग_लिखो(client, MT9T001_BLACK_LEVEL_CALIBRATION,
				     MT9T001_BLACK_LEVEL_RECALCULATE |
				     mt9t001->black_level);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9t001_ctrl_ops = अणु
	.s_ctrl = mt9t001_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mt9t001_test_pattern_menu[] = अणु
	"Disabled",
	"Enabled",
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9t001_ctrls[] = अणु
	अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_TEST_PATTERN_COLOR,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "Test Pattern Color",
		.min		= 0,
		.max		= 1023,
		.step		= 1,
		.def		= 0,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_BLACK_LEVEL_AUTO,
		.type		= V4L2_CTRL_TYPE_BOOLEAN,
		.name		= "Black Level, Auto",
		.min		= 0,
		.max		= 1,
		.step		= 1,
		.def		= 1,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_BLACK_LEVEL_OFFSET,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "Black Level, Offset",
		.min		= -256,
		.max		= 255,
		.step		= 1,
		.def		= 32,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_BLACK_LEVEL_CALIBRATE,
		.type		= V4L2_CTRL_TYPE_BUTTON,
		.name		= "Black Level, Calibrate",
		.min		= 0,
		.max		= 0,
		.step		= 0,
		.def		= 0,
		.flags		= V4L2_CTRL_FLAG_WRITE_ONLY,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config mt9t001_gains[] = अणु
	अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_GAIN_RED,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "Gain, Red",
		.min		= MT9T001_GLOBAL_GAIN_MIN,
		.max		= MT9T001_GLOBAL_GAIN_MAX,
		.step		= 1,
		.def		= MT9T001_GLOBAL_GAIN_MIN,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_GAIN_GREEN_RED,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "Gain, Green (R)",
		.min		= MT9T001_GLOBAL_GAIN_MIN,
		.max		= MT9T001_GLOBAL_GAIN_MAX,
		.step		= 1,
		.def		= MT9T001_GLOBAL_GAIN_MIN,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_GAIN_GREEN_BLUE,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "Gain, Green (B)",
		.min		= MT9T001_GLOBAL_GAIN_MIN,
		.max		= MT9T001_GLOBAL_GAIN_MAX,
		.step		= 1,
		.def		= MT9T001_GLOBAL_GAIN_MIN,
		.flags		= 0,
	पूर्ण, अणु
		.ops		= &mt9t001_ctrl_ops,
		.id		= V4L2_CID_GAIN_BLUE,
		.type		= V4L2_CTRL_TYPE_INTEGER,
		.name		= "Gain, Blue",
		.min		= MT9T001_GLOBAL_GAIN_MIN,
		.max		= MT9T001_GLOBAL_GAIN_MAX,
		.step		= 1,
		.def		= MT9T001_GLOBAL_GAIN_MIN,
		.flags		= 0,
	पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 subdev core operations
 */

अटल पूर्णांक mt9t001_set_घातer(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&mt9t001->घातer_lock);

	/* If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (mt9t001->घातer_count == !on) अणु
		ret = __mt9t001_set_घातer(mt9t001, !!on);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* Update the घातer count. */
	mt9t001->घातer_count += on ? 1 : -1;
	WARN_ON(mt9t001->घातer_count < 0);

out:
	mutex_unlock(&mt9t001->घातer_lock);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 subdev पूर्णांकernal operations
 */

अटल पूर्णांक mt9t001_रेजिस्टरed(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);
	s32 data;
	पूर्णांक ret;

	ret = mt9t001_घातer_on(mt9t001);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "MT9T001 power up failed\n");
		वापस ret;
	पूर्ण

	/* Read out the chip version रेजिस्टर */
	data = mt9t001_पढ़ो(client, MT9T001_CHIP_VERSION);
	mt9t001_घातer_off(mt9t001);

	अगर (data != MT9T001_CHIP_ID) अणु
		dev_err(&client->dev,
			"MT9T001 not detected, wrong version 0x%04x\n", data);
		वापस -ENODEV;
	पूर्ण

	dev_info(&client->dev, "MT9T001 detected at address 0x%02x\n",
		 client->addr);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t001_खोलो(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा v4l2_rect *crop;

	crop = v4l2_subdev_get_try_crop(subdev, fh->pad, 0);
	crop->left = MT9T001_COLUMN_START_DEF;
	crop->top = MT9T001_ROW_START_DEF;
	crop->width = MT9T001_WINDOW_WIDTH_DEF + 1;
	crop->height = MT9T001_WINDOW_HEIGHT_DEF + 1;

	क्रमmat = v4l2_subdev_get_try_क्रमmat(subdev, fh->pad, 0);
	क्रमmat->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	क्रमmat->width = MT9T001_WINDOW_WIDTH_DEF + 1;
	क्रमmat->height = MT9T001_WINDOW_HEIGHT_DEF + 1;
	क्रमmat->field = V4L2_FIELD_NONE;
	क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;

	वापस mt9t001_set_घातer(subdev, 1);
पूर्ण

अटल पूर्णांक mt9t001_बंद(काष्ठा v4l2_subdev *subdev, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस mt9t001_set_घातer(subdev, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9t001_subdev_core_ops = अणु
	.s_घातer = mt9t001_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9t001_subdev_video_ops = अणु
	.s_stream = mt9t001_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9t001_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = mt9t001_क्रमागत_mbus_code,
	.क्रमागत_frame_size = mt9t001_क्रमागत_frame_size,
	.get_fmt = mt9t001_get_क्रमmat,
	.set_fmt = mt9t001_set_क्रमmat,
	.get_selection = mt9t001_get_selection,
	.set_selection = mt9t001_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9t001_subdev_ops = अणु
	.core = &mt9t001_subdev_core_ops,
	.video = &mt9t001_subdev_video_ops,
	.pad = &mt9t001_subdev_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops mt9t001_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = mt9t001_रेजिस्टरed,
	.खोलो = mt9t001_खोलो,
	.बंद = mt9t001_बंद,
पूर्ण;

अटल पूर्णांक mt9t001_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा mt9t001_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा mt9t001 *mt9t001;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_warn(&client->adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		वापस -EIO;
	पूर्ण

	mt9t001 = devm_kzalloc(&client->dev, माप(*mt9t001), GFP_KERNEL);
	अगर (!mt9t001)
		वापस -ENOMEM;

	mutex_init(&mt9t001->घातer_lock);
	mt9t001->output_control = MT9T001_OUTPUT_CONTROL_DEF;

	mt9t001->regulators[0].supply = "vdd";
	mt9t001->regulators[1].supply = "vaa";

	ret = devm_regulator_bulk_get(&client->dev, 2, mt9t001->regulators);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to get regulators\n");
		वापस ret;
	पूर्ण

	mt9t001->clk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(mt9t001->clk)) अणु
		dev_err(&client->dev, "Unable to get clock\n");
		वापस PTR_ERR(mt9t001->clk);
	पूर्ण

	v4l2_ctrl_handler_init(&mt9t001->ctrls, ARRAY_SIZE(mt9t001_ctrls) +
						ARRAY_SIZE(mt9t001_gains) + 4);

	v4l2_ctrl_new_std(&mt9t001->ctrls, &mt9t001_ctrl_ops,
			  V4L2_CID_EXPOSURE, MT9T001_SHUTTER_WIDTH_MIN,
			  MT9T001_SHUTTER_WIDTH_MAX, 1,
			  MT9T001_SHUTTER_WIDTH_DEF);
	v4l2_ctrl_new_std(&mt9t001->ctrls, &mt9t001_ctrl_ops,
			  V4L2_CID_BLACK_LEVEL, 1, 1, 1, 1);
	v4l2_ctrl_new_std(&mt9t001->ctrls, &mt9t001_ctrl_ops,
			  V4L2_CID_PIXEL_RATE, pdata->ext_clk, pdata->ext_clk,
			  1, pdata->ext_clk);
	v4l2_ctrl_new_std_menu_items(&mt9t001->ctrls, &mt9t001_ctrl_ops,
			V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(mt9t001_test_pattern_menu) - 1, 0,
			0, mt9t001_test_pattern_menu);

	क्रम (i = 0; i < ARRAY_SIZE(mt9t001_ctrls); ++i)
		v4l2_ctrl_new_custom(&mt9t001->ctrls, &mt9t001_ctrls[i], शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(mt9t001_gains); ++i)
		mt9t001->gains[i] = v4l2_ctrl_new_custom(&mt9t001->ctrls,
			&mt9t001_gains[i], शून्य);

	v4l2_ctrl_cluster(ARRAY_SIZE(mt9t001_gains), mt9t001->gains);

	mt9t001->subdev.ctrl_handler = &mt9t001->ctrls;

	अगर (mt9t001->ctrls.error) अणु
		prपूर्णांकk(KERN_INFO "%s: control initialization error %d\n",
		       __func__, mt9t001->ctrls.error);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	mt9t001->crop.left = MT9T001_COLUMN_START_DEF;
	mt9t001->crop.top = MT9T001_ROW_START_DEF;
	mt9t001->crop.width = MT9T001_WINDOW_WIDTH_DEF + 1;
	mt9t001->crop.height = MT9T001_WINDOW_HEIGHT_DEF + 1;

	mt9t001->क्रमmat.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	mt9t001->क्रमmat.width = MT9T001_WINDOW_WIDTH_DEF + 1;
	mt9t001->क्रमmat.height = MT9T001_WINDOW_HEIGHT_DEF + 1;
	mt9t001->क्रमmat.field = V4L2_FIELD_NONE;
	mt9t001->क्रमmat.colorspace = V4L2_COLORSPACE_SRGB;

	v4l2_i2c_subdev_init(&mt9t001->subdev, client, &mt9t001_subdev_ops);
	mt9t001->subdev.पूर्णांकernal_ops = &mt9t001_subdev_पूर्णांकernal_ops;
	mt9t001->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	mt9t001->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	mt9t001->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&mt9t001->subdev.entity, 1, &mt9t001->pad);

करोne:
	अगर (ret < 0) अणु
		v4l2_ctrl_handler_मुक्त(&mt9t001->ctrls);
		media_entity_cleanup(&mt9t001->subdev.entity);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t001_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा mt9t001 *mt9t001 = to_mt9t001(subdev);

	v4l2_ctrl_handler_मुक्त(&mt9t001->ctrls);
	v4l2_device_unरेजिस्टर_subdev(subdev);
	media_entity_cleanup(&subdev->entity);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mt9t001_id[] = अणु
	अणु "mt9t001", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt9t001_id);

अटल काष्ठा i2c_driver mt9t001_driver = अणु
	.driver = अणु
		.name = "mt9t001",
	पूर्ण,
	.probe		= mt9t001_probe,
	.हटाओ		= mt9t001_हटाओ,
	.id_table	= mt9t001_id,
पूर्ण;

module_i2c_driver(mt9t001_driver);

MODULE_DESCRIPTION("Aptina (Micron) MT9T001 Camera driver");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_LICENSE("GPL");
