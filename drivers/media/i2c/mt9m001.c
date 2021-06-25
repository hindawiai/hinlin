<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम MT9M001 CMOS Image Sensor from Micron
 *
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-subdev.h>

/*
 * mt9m001 i2c address 0x5d
 */

/* mt9m001 selected रेजिस्टर addresses */
#घोषणा MT9M001_CHIP_VERSION		0x00
#घोषणा MT9M001_ROW_START		0x01
#घोषणा MT9M001_COLUMN_START		0x02
#घोषणा MT9M001_WINDOW_HEIGHT		0x03
#घोषणा MT9M001_WINDOW_WIDTH		0x04
#घोषणा MT9M001_HORIZONTAL_BLANKING	0x05
#घोषणा MT9M001_VERTICAL_BLANKING	0x06
#घोषणा MT9M001_OUTPUT_CONTROL		0x07
#घोषणा MT9M001_SHUTTER_WIDTH		0x09
#घोषणा MT9M001_FRAME_RESTART		0x0b
#घोषणा MT9M001_SHUTTER_DELAY		0x0c
#घोषणा MT9M001_RESET			0x0d
#घोषणा MT9M001_READ_OPTIONS1		0x1e
#घोषणा MT9M001_READ_OPTIONS2		0x20
#घोषणा MT9M001_GLOBAL_GAIN		0x35
#घोषणा MT9M001_CHIP_ENABLE		0xF1

#घोषणा MT9M001_MAX_WIDTH		1280
#घोषणा MT9M001_MAX_HEIGHT		1024
#घोषणा MT9M001_MIN_WIDTH		48
#घोषणा MT9M001_MIN_HEIGHT		32
#घोषणा MT9M001_COLUMN_SKIP		20
#घोषणा MT9M001_ROW_SKIP		12
#घोषणा MT9M001_DEFAULT_HBLANK		9
#घोषणा MT9M001_DEFAULT_VBLANK		25

/* MT9M001 has only one fixed colorspace per pixelcode */
काष्ठा mt9m001_datafmt अणु
	u32	code;
	क्रमागत v4l2_colorspace		colorspace;
पूर्ण;

/* Find a data क्रमmat by a pixel code in an array */
अटल स्थिर काष्ठा mt9m001_datafmt *mt9m001_find_datafmt(
	u32 code, स्थिर काष्ठा mt9m001_datafmt *fmt,
	पूर्णांक n)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < n; i++)
		अगर (fmt[i].code == code)
			वापस fmt + i;

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा mt9m001_datafmt mt9m001_colour_fmts[] = अणु
	/*
	 * Order important: first natively supported,
	 * second supported with a GPIO extender
	 */
	अणुMEDIA_BUS_FMT_SBGGR10_1X10, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR8_1X8, V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mt9m001_datafmt mt9m001_monochrome_fmts[] = अणु
	/* Order important - see above */
	अणुMEDIA_BUS_FMT_Y10_1X10, V4L2_COLORSPACE_JPEGपूर्ण,
	अणुMEDIA_BUS_FMT_Y8_1X8, V4L2_COLORSPACE_JPEGपूर्ण,
पूर्ण;

काष्ठा mt9m001 अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* exposure/स्वतः-exposure cluster */
		काष्ठा v4l2_ctrl *स्वतःexposure;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	bool streaming;
	काष्ठा mutex mutex;
	काष्ठा v4l2_rect rect;	/* Sensor winकरोw */
	काष्ठा clk *clk;
	काष्ठा gpio_desc *standby_gpio;
	काष्ठा gpio_desc *reset_gpio;
	स्थिर काष्ठा mt9m001_datafmt *fmt;
	स्थिर काष्ठा mt9m001_datafmt *fmts;
	पूर्णांक num_fmts;
	अचिन्हित पूर्णांक total_h;
	अचिन्हित लघु y_skip_top;	/* Lines to skip at the top */
	काष्ठा media_pad pad;
पूर्ण;

अटल काष्ठा mt9m001 *to_mt9m001(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client), काष्ठा mt9m001, subdev);
पूर्ण

अटल पूर्णांक reg_पढ़ो(काष्ठा i2c_client *client, स्थिर u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
पूर्ण

अटल पूर्णांक reg_ग_लिखो(काष्ठा i2c_client *client, स्थिर u8 reg,
		     स्थिर u16 data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(client, reg, data);
पूर्ण

अटल पूर्णांक reg_set(काष्ठा i2c_client *client, स्थिर u8 reg,
		   स्थिर u16 data)
अणु
	पूर्णांक ret;

	ret = reg_पढ़ो(client, reg);
	अगर (ret < 0)
		वापस ret;
	वापस reg_ग_लिखो(client, reg, ret | data);
पूर्ण

अटल पूर्णांक reg_clear(काष्ठा i2c_client *client, स्थिर u8 reg,
		     स्थिर u16 data)
अणु
	पूर्णांक ret;

	ret = reg_पढ़ो(client, reg);
	अगर (ret < 0)
		वापस ret;
	वापस reg_ग_लिखो(client, reg, ret & ~data);
पूर्ण

काष्ठा mt9m001_reg अणु
	u8 reg;
	u16 data;
पूर्ण;

अटल पूर्णांक multi_reg_ग_लिखो(काष्ठा i2c_client *client,
			   स्थिर काष्ठा mt9m001_reg *regs, पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		पूर्णांक ret = reg_ग_लिखो(client, regs[i].reg, regs[i].data);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_init(काष्ठा i2c_client *client)
अणु
	अटल स्थिर काष्ठा mt9m001_reg init_regs[] = अणु
		/*
		 * Issue a soft reset. This वापसs all रेजिस्टरs to their
		 * शेष values.
		 */
		अणु MT9M001_RESET, 1 पूर्ण,
		अणु MT9M001_RESET, 0 पूर्ण,
		/* Disable chip, synchronous option update */
		अणु MT9M001_OUTPUT_CONTROL, 0 पूर्ण
	पूर्ण;

	dev_dbg(&client->dev, "%s\n", __func__);

	वापस multi_reg_ग_लिखो(client, init_regs, ARRAY_SIZE(init_regs));
पूर्ण

अटल पूर्णांक mt9m001_apply_selection(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	स्थिर काष्ठा mt9m001_reg regs[] = अणु
		/* Blanking and start values - शेष... */
		अणु MT9M001_HORIZONTAL_BLANKING, MT9M001_DEFAULT_HBLANK पूर्ण,
		अणु MT9M001_VERTICAL_BLANKING, MT9M001_DEFAULT_VBLANK पूर्ण,
		/*
		 * The caller provides a supported क्रमmat, as verअगरied per
		 * call to .set_fmt(FORMAT_TRY).
		 */
		अणु MT9M001_COLUMN_START, mt9m001->rect.left पूर्ण,
		अणु MT9M001_ROW_START, mt9m001->rect.top पूर्ण,
		अणु MT9M001_WINDOW_WIDTH, mt9m001->rect.width - 1 पूर्ण,
		अणु MT9M001_WINDOW_HEIGHT,
			mt9m001->rect.height + mt9m001->y_skip_top - 1 पूर्ण,
	पूर्ण;

	वापस multi_reg_ग_लिखो(client, regs, ARRAY_SIZE(regs));
पूर्ण

अटल पूर्णांक mt9m001_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	पूर्णांक ret = 0;

	mutex_lock(&mt9m001->mutex);

	अगर (mt9m001->streaming == enable)
		जाओ करोne;

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0)
			जाओ put_unlock;

		ret = mt9m001_apply_selection(sd);
		अगर (ret)
			जाओ put_unlock;

		ret = __v4l2_ctrl_handler_setup(&mt9m001->hdl);
		अगर (ret)
			जाओ put_unlock;

		/* Switch to master "normal" mode */
		ret = reg_ग_लिखो(client, MT9M001_OUTPUT_CONTROL, 2);
		अगर (ret < 0)
			जाओ put_unlock;
	पूर्ण अन्यथा अणु
		/* Switch to master stop sensor पढ़ोout */
		reg_ग_लिखो(client, MT9M001_OUTPUT_CONTROL, 0);
		pm_runसमय_put(&client->dev);
	पूर्ण

	mt9m001->streaming = enable;
करोne:
	mutex_unlock(&mt9m001->mutex);

	वापस 0;

put_unlock:
	pm_runसमय_put(&client->dev);
	mutex_unlock(&mt9m001->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m001_set_selection(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	काष्ठा v4l2_rect rect = sel->r;

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	अगर (mt9m001->fmts == mt9m001_colour_fmts)
		/*
		 * Bayer क्रमmat - even number of rows क्रम simplicity,
		 * but let the user play with the top row.
		 */
		rect.height = ALIGN(rect.height, 2);

	/* Datasheet requirement: see रेजिस्टर description */
	rect.width = ALIGN(rect.width, 2);
	rect.left = ALIGN(rect.left, 2);

	rect.width = clamp_t(u32, rect.width, MT9M001_MIN_WIDTH,
			MT9M001_MAX_WIDTH);
	rect.left = clamp_t(u32, rect.left, MT9M001_COLUMN_SKIP,
			MT9M001_COLUMN_SKIP + MT9M001_MAX_WIDTH - rect.width);

	rect.height = clamp_t(u32, rect.height, MT9M001_MIN_HEIGHT,
			MT9M001_MAX_HEIGHT);
	rect.top = clamp_t(u32, rect.top, MT9M001_ROW_SKIP,
			MT9M001_ROW_SKIP + MT9M001_MAX_HEIGHT - rect.height);

	mt9m001->total_h = rect.height + mt9m001->y_skip_top +
			   MT9M001_DEFAULT_VBLANK;

	mt9m001->rect = rect;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_get_selection(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = MT9M001_COLUMN_SKIP;
		sel->r.top = MT9M001_ROW_SKIP;
		sel->r.width = MT9M001_MAX_WIDTH;
		sel->r.height = MT9M001_MAX_HEIGHT;
		वापस 0;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = mt9m001->rect;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9m001_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		क्रमmat->क्रमmat = *mf;
		वापस 0;
	पूर्ण

	mf->width	= mt9m001->rect.width;
	mf->height	= mt9m001->rect.height;
	mf->code	= mt9m001->fmt->code;
	mf->colorspace	= mt9m001->fmt->colorspace;
	mf->field	= V4L2_FIELD_NONE;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_s_fmt(काष्ठा v4l2_subdev *sd,
			 स्थिर काष्ठा mt9m001_datafmt *fmt,
			 काष्ठा v4l2_mbus_framefmt *mf)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	काष्ठा v4l2_subdev_selection sel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP,
		.r.left = mt9m001->rect.left,
		.r.top = mt9m001->rect.top,
		.r.width = mf->width,
		.r.height = mf->height,
	पूर्ण;
	पूर्णांक ret;

	/* No support क्रम scaling so far, just crop. TODO: use skipping */
	ret = mt9m001_set_selection(sd, शून्य, &sel);
	अगर (!ret) अणु
		mf->width	= mt9m001->rect.width;
		mf->height	= mt9m001->rect.height;
		mt9m001->fmt	= fmt;
		mf->colorspace	= fmt->colorspace;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m001_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	स्थिर काष्ठा mt9m001_datafmt *fmt;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	v4l_bound_align_image(&mf->width, MT9M001_MIN_WIDTH,
		MT9M001_MAX_WIDTH, 1,
		&mf->height, MT9M001_MIN_HEIGHT + mt9m001->y_skip_top,
		MT9M001_MAX_HEIGHT + mt9m001->y_skip_top, 0, 0);

	अगर (mt9m001->fmts == mt9m001_colour_fmts)
		mf->height = ALIGN(mf->height - 1, 2);

	fmt = mt9m001_find_datafmt(mf->code, mt9m001->fmts,
				   mt9m001->num_fmts);
	अगर (!fmt) अणु
		fmt = mt9m001->fmt;
		mf->code = fmt->code;
	पूर्ण

	mf->colorspace	= fmt->colorspace;
	mf->field	= V4L2_FIELD_NONE;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस mt9m001_s_fmt(sd, fmt, mf);
	cfg->try_fmt = *mf;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक mt9m001_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg > 0xff)
		वापस -EINVAL;

	reg->size = 2;
	reg->val = reg_पढ़ो(client, reg->reg);

	अगर (reg->val > 0xffff)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg > 0xff)
		वापस -EINVAL;

	अगर (reg_ग_लिखो(client, reg->reg, reg->val) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mt9m001_घातer_on(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	पूर्णांक ret;

	ret = clk_prepare_enable(mt9m001->clk);
	अगर (ret)
		वापस ret;

	अगर (mt9m001->standby_gpio) अणु
		gpiod_set_value_cansleep(mt9m001->standby_gpio, 0);
		usleep_range(1000, 2000);
	पूर्ण

	अगर (mt9m001->reset_gpio) अणु
		gpiod_set_value_cansleep(mt9m001->reset_gpio, 1);
		usleep_range(1000, 2000);
		gpiod_set_value_cansleep(mt9m001->reset_gpio, 0);
		usleep_range(1000, 2000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_घातer_off(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);

	gpiod_set_value_cansleep(mt9m001->standby_gpio, 1);
	clk_disable_unprepare(mt9m001->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9m001 *mt9m001 = container_of(ctrl->handler,
					       काष्ठा mt9m001, hdl);
	s32 min, max;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE_AUTO:
		min = mt9m001->exposure->minimum;
		max = mt9m001->exposure->maximum;
		mt9m001->exposure->val =
			(524 + (mt9m001->total_h - 1) * (max - min)) / 1048 + min;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9m001 *mt9m001 = container_of(ctrl->handler,
					       काष्ठा mt9m001, hdl);
	काष्ठा v4l2_subdev *sd = &mt9m001->subdev;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_ctrl *exp = mt9m001->exposure;
	पूर्णांक data;
	पूर्णांक ret;

	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		अगर (ctrl->val)
			ret = reg_set(client, MT9M001_READ_OPTIONS2, 0x8000);
		अन्यथा
			ret = reg_clear(client, MT9M001_READ_OPTIONS2, 0x8000);
		अवरोध;

	हाल V4L2_CID_GAIN:
		/* See Datasheet Table 7, Gain settings. */
		अगर (ctrl->val <= ctrl->शेष_value) अणु
			/* Pack it पूर्णांकo 0..1 step 0.125, रेजिस्टर values 0..8 */
			अचिन्हित दीर्घ range = ctrl->शेष_value - ctrl->minimum;
			data = ((ctrl->val - (s32)ctrl->minimum) * 8 + range / 2) / range;

			dev_dbg(&client->dev, "Setting gain %d\n", data);
			ret = reg_ग_लिखो(client, MT9M001_GLOBAL_GAIN, data);
		पूर्ण अन्यथा अणु
			/* Pack it पूर्णांकo 1.125..15 variable step, रेजिस्टर values 9..67 */
			/* We assume qctrl->maximum - qctrl->शेष_value - 1 > 0 */
			अचिन्हित दीर्घ range = ctrl->maximum - ctrl->शेष_value - 1;
			अचिन्हित दीर्घ gain = ((ctrl->val - (s32)ctrl->शेष_value - 1) *
					       111 + range / 2) / range + 9;

			अगर (gain <= 32)
				data = gain;
			अन्यथा अगर (gain <= 64)
				data = ((gain - 32) * 16 + 16) / 32 + 80;
			अन्यथा
				data = ((gain - 64) * 7 + 28) / 56 + 96;

			dev_dbg(&client->dev, "Setting gain from %d to %d\n",
				 reg_पढ़ो(client, MT9M001_GLOBAL_GAIN), data);
			ret = reg_ग_लिखो(client, MT9M001_GLOBAL_GAIN, data);
		पूर्ण
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		अगर (ctrl->val == V4L2_EXPOSURE_MANUAL) अणु
			अचिन्हित दीर्घ range = exp->maximum - exp->minimum;
			अचिन्हित दीर्घ shutter = ((exp->val - (s32)exp->minimum) * 1048 +
						 range / 2) / range + 1;

			dev_dbg(&client->dev,
				"Setting shutter width from %d to %lu\n",
				reg_पढ़ो(client, MT9M001_SHUTTER_WIDTH), shutter);
			ret = reg_ग_लिखो(client, MT9M001_SHUTTER_WIDTH, shutter);
		पूर्ण अन्यथा अणु
			mt9m001->total_h = mt9m001->rect.height +
				mt9m001->y_skip_top + MT9M001_DEFAULT_VBLANK;
			ret = reg_ग_लिखो(client, MT9M001_SHUTTER_WIDTH,
					mt9m001->total_h);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

/*
 * Interface active, can use i2c. If it fails, it can indeed mean, that
 * this wasn't our capture पूर्णांकerface, so, we रुको क्रम the right one
 */
अटल पूर्णांक mt9m001_video_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	s32 data;
	पूर्णांक ret;

	/* Enable the chip */
	data = reg_ग_लिखो(client, MT9M001_CHIP_ENABLE, 1);
	dev_dbg(&client->dev, "write: %d\n", data);

	/* Read out the chip version रेजिस्टर */
	data = reg_पढ़ो(client, MT9M001_CHIP_VERSION);

	/* must be 0x8411 or 0x8421 क्रम colour sensor and 8431 क्रम bw */
	चयन (data) अणु
	हाल 0x8411:
	हाल 0x8421:
		mt9m001->fmts = mt9m001_colour_fmts;
		mt9m001->num_fmts = ARRAY_SIZE(mt9m001_colour_fmts);
		अवरोध;
	हाल 0x8431:
		mt9m001->fmts = mt9m001_monochrome_fmts;
		mt9m001->num_fmts = ARRAY_SIZE(mt9m001_monochrome_fmts);
		अवरोध;
	शेष:
		dev_err(&client->dev,
			"No MT9M001 chip detected, register read %x\n", data);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	mt9m001->fmt = &mt9m001->fmts[0];

	dev_info(&client->dev, "Detected a MT9M001 chip ID %x (%s)\n", data,
		 data == 0x8431 ? "C12STM" : "C12ST");

	ret = mt9m001_init(client);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to initialise the camera\n");
		जाओ करोne;
	पूर्ण

	/* mt9m001_init() has reset the chip, वापसing रेजिस्टरs to शेषs */
	ret = v4l2_ctrl_handler_setup(&mt9m001->hdl);

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m001_g_skip_top_lines(काष्ठा v4l2_subdev *sd, u32 *lines)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);

	*lines = mt9m001->y_skip_top;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9m001_ctrl_ops = अणु
	.g_अस्थिर_ctrl = mt9m001_g_अस्थिर_ctrl,
	.s_ctrl = mt9m001_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9m001_subdev_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= mt9m001_g_रेजिस्टर,
	.s_रेजिस्टर	= mt9m001_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mt9m001_init_cfg(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);
	काष्ठा v4l2_mbus_framefmt *try_fmt =
		v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);

	try_fmt->width		= MT9M001_MAX_WIDTH;
	try_fmt->height		= MT9M001_MAX_HEIGHT;
	try_fmt->code		= mt9m001->fmts[0].code;
	try_fmt->colorspace	= mt9m001->fmts[0].colorspace;
	try_fmt->field		= V4L2_FIELD_NONE;
	try_fmt->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	try_fmt->quantization	= V4L2_QUANTIZATION_DEFAULT;
	try_fmt->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);

	अगर (code->pad || code->index >= mt9m001->num_fmts)
		वापस -EINVAL;

	code->code = mt9m001->fmts[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m001_get_mbus_config(काष्ठा v4l2_subdev *sd,
				   अचिन्हित पूर्णांक pad,
				   काष्ठा v4l2_mbus_config *cfg)
अणु
	/* MT9M001 has all capture_क्रमmat parameters fixed */
	cfg->flags = V4L2_MBUS_PCLK_SAMPLE_FALLING |
		V4L2_MBUS_HSYNC_ACTIVE_HIGH | V4L2_MBUS_VSYNC_ACTIVE_HIGH |
		V4L2_MBUS_DATA_ACTIVE_HIGH | V4L2_MBUS_MASTER;
	cfg->type = V4L2_MBUS_PARALLEL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9m001_subdev_video_ops = अणु
	.s_stream	= mt9m001_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_sensor_ops mt9m001_subdev_sensor_ops = अणु
	.g_skip_top_lines	= mt9m001_g_skip_top_lines,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9m001_subdev_pad_ops = अणु
	.init_cfg	= mt9m001_init_cfg,
	.क्रमागत_mbus_code = mt9m001_क्रमागत_mbus_code,
	.get_selection	= mt9m001_get_selection,
	.set_selection	= mt9m001_set_selection,
	.get_fmt	= mt9m001_get_fmt,
	.set_fmt	= mt9m001_set_fmt,
	.get_mbus_config = mt9m001_get_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9m001_subdev_ops = अणु
	.core	= &mt9m001_subdev_core_ops,
	.video	= &mt9m001_subdev_video_ops,
	.sensor	= &mt9m001_subdev_sensor_ops,
	.pad	= &mt9m001_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक mt9m001_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m001 *mt9m001;
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		वापस -EIO;
	पूर्ण

	mt9m001 = devm_kzalloc(&client->dev, माप(*mt9m001), GFP_KERNEL);
	अगर (!mt9m001)
		वापस -ENOMEM;

	mt9m001->clk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(mt9m001->clk))
		वापस PTR_ERR(mt9m001->clk);

	mt9m001->standby_gpio = devm_gpiod_get_optional(&client->dev, "standby",
							GPIOD_OUT_LOW);
	अगर (IS_ERR(mt9m001->standby_gpio))
		वापस PTR_ERR(mt9m001->standby_gpio);

	mt9m001->reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(mt9m001->reset_gpio))
		वापस PTR_ERR(mt9m001->reset_gpio);

	v4l2_i2c_subdev_init(&mt9m001->subdev, client, &mt9m001_subdev_ops);
	mt9m001->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
				 V4L2_SUBDEV_FL_HAS_EVENTS;
	v4l2_ctrl_handler_init(&mt9m001->hdl, 4);
	v4l2_ctrl_new_std(&mt9m001->hdl, &mt9m001_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9m001->hdl, &mt9m001_ctrl_ops,
			V4L2_CID_GAIN, 0, 127, 1, 64);
	mt9m001->exposure = v4l2_ctrl_new_std(&mt9m001->hdl, &mt9m001_ctrl_ops,
			V4L2_CID_EXPOSURE, 1, 255, 1, 255);
	/*
	 * Simulated स्वतःexposure. If enabled, we calculate shutter width
	 * ourselves in the driver based on vertical blanking and frame width
	 */
	mt9m001->स्वतःexposure = v4l2_ctrl_new_std_menu(&mt9m001->hdl,
			&mt9m001_ctrl_ops, V4L2_CID_EXPOSURE_AUTO, 1, 0,
			V4L2_EXPOSURE_AUTO);
	mt9m001->subdev.ctrl_handler = &mt9m001->hdl;
	अगर (mt9m001->hdl.error)
		वापस mt9m001->hdl.error;

	v4l2_ctrl_स्वतः_cluster(2, &mt9m001->स्वतःexposure,
					V4L2_EXPOSURE_MANUAL, true);

	mutex_init(&mt9m001->mutex);
	mt9m001->hdl.lock = &mt9m001->mutex;

	/* Second stage probe - when a capture adapter is there */
	mt9m001->y_skip_top	= 0;
	mt9m001->rect.left	= MT9M001_COLUMN_SKIP;
	mt9m001->rect.top	= MT9M001_ROW_SKIP;
	mt9m001->rect.width	= MT9M001_MAX_WIDTH;
	mt9m001->rect.height	= MT9M001_MAX_HEIGHT;

	ret = mt9m001_घातer_on(&client->dev);
	अगर (ret)
		जाओ error_hdl_मुक्त;

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);

	ret = mt9m001_video_probe(client);
	अगर (ret)
		जाओ error_घातer_off;

	mt9m001->pad.flags = MEDIA_PAD_FL_SOURCE;
	mt9m001->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&mt9m001->subdev.entity, 1, &mt9m001->pad);
	अगर (ret)
		जाओ error_घातer_off;

	ret = v4l2_async_रेजिस्टर_subdev(&mt9m001->subdev);
	अगर (ret)
		जाओ error_entity_cleanup;

	pm_runसमय_idle(&client->dev);

	वापस 0;

error_entity_cleanup:
	media_entity_cleanup(&mt9m001->subdev.entity);
error_घातer_off:
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	mt9m001_घातer_off(&client->dev);

error_hdl_मुक्त:
	v4l2_ctrl_handler_मुक्त(&mt9m001->hdl);
	mutex_destroy(&mt9m001->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m001_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m001 *mt9m001 = to_mt9m001(client);

	pm_runसमय_get_sync(&client->dev);

	v4l2_async_unरेजिस्टर_subdev(&mt9m001->subdev);
	media_entity_cleanup(&mt9m001->subdev.entity);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);
	mt9m001_घातer_off(&client->dev);

	v4l2_ctrl_handler_मुक्त(&mt9m001->hdl);
	mutex_destroy(&mt9m001->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mt9m001_id[] = अणु
	अणु "mt9m001", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt9m001_id);

अटल स्थिर काष्ठा dev_pm_ops mt9m001_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mt9m001_घातer_off, mt9m001_घातer_on, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt9m001_of_match[] = अणु
	अणु .compatible = "onnn,mt9m001", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt9m001_of_match);

अटल काष्ठा i2c_driver mt9m001_i2c_driver = अणु
	.driver = अणु
		.name = "mt9m001",
		.pm = &mt9m001_pm_ops,
		.of_match_table = mt9m001_of_match,
	पूर्ण,
	.probe_new	= mt9m001_probe,
	.हटाओ		= mt9m001_हटाओ,
	.id_table	= mt9m001_id,
पूर्ण;

module_i2c_driver(mt9m001_i2c_driver);

MODULE_DESCRIPTION("Micron MT9M001 Camera driver");
MODULE_AUTHOR("Guennadi Liakhovetski <kernel@pengutronix.de>");
MODULE_LICENSE("GPL v2");
