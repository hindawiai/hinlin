<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt9v011 -Micron 1/4-Inch VGA Digital Image Sensor
//
// Copyright (c) 2009 Mauro Carvalho Chehab <mchehab@kernel.org>

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/i2c/mt9v011.h>

MODULE_DESCRIPTION("Micron mt9v011 sensor driver");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

#घोषणा R00_MT9V011_CHIP_VERSION	0x00
#घोषणा R01_MT9V011_ROWSTART		0x01
#घोषणा R02_MT9V011_COLSTART		0x02
#घोषणा R03_MT9V011_HEIGHT		0x03
#घोषणा R04_MT9V011_WIDTH		0x04
#घोषणा R05_MT9V011_HBLANK		0x05
#घोषणा R06_MT9V011_VBLANK		0x06
#घोषणा R07_MT9V011_OUT_CTRL		0x07
#घोषणा R09_MT9V011_SHUTTER_WIDTH	0x09
#घोषणा R0A_MT9V011_CLK_SPEED		0x0a
#घोषणा R0B_MT9V011_RESTART		0x0b
#घोषणा R0C_MT9V011_SHUTTER_DELAY	0x0c
#घोषणा R0D_MT9V011_RESET		0x0d
#घोषणा R1E_MT9V011_DIGITAL_ZOOM	0x1e
#घोषणा R20_MT9V011_READ_MODE		0x20
#घोषणा R2B_MT9V011_GREEN_1_GAIN	0x2b
#घोषणा R2C_MT9V011_BLUE_GAIN		0x2c
#घोषणा R2D_MT9V011_RED_GAIN		0x2d
#घोषणा R2E_MT9V011_GREEN_2_GAIN	0x2e
#घोषणा R35_MT9V011_GLOBAL_GAIN		0x35
#घोषणा RF1_MT9V011_CHIP_ENABLE		0xf1

#घोषणा MT9V011_VERSION			0x8232
#घोषणा MT9V011_REV_B_VERSION		0x8243

काष्ठा mt9v011 अणु
	काष्ठा v4l2_subdev sd;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_pad pad;
#पूर्ण_अगर
	काष्ठा v4l2_ctrl_handler ctrls;
	अचिन्हित width, height;
	अचिन्हित xtal;
	अचिन्हित hflip:1;
	अचिन्हित vflip:1;

	u16 global_gain, exposure;
	s16 red_bal, blue_bal;
पूर्ण;

अटल अंतरभूत काष्ठा mt9v011 *to_mt9v011(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा mt9v011, sd);
पूर्ण

अटल पूर्णांक mt9v011_पढ़ो(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर addr)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	__be16 buffer;
	पूर्णांक rc, val;

	rc = i2c_master_send(c, &addr, 1);
	अगर (rc != 1)
		v4l2_dbg(0, debug, sd,
			 "i2c i/o error: rc == %d (should be 1)\n", rc);

	msleep(10);

	rc = i2c_master_recv(c, (अक्षर *)&buffer, 2);
	अगर (rc != 2)
		v4l2_dbg(0, debug, sd,
			 "i2c i/o error: rc == %d (should be 2)\n", rc);

	val = be16_to_cpu(buffer);

	v4l2_dbg(2, debug, sd, "mt9v011: read 0x%02x = 0x%04x\n", addr, val);

	वापस val;
पूर्ण

अटल व्योम mt9v011_ग_लिखो(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर addr,
				 u16 value)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	अचिन्हित अक्षर buffer[3];
	पूर्णांक rc;

	buffer[0] = addr;
	buffer[1] = value >> 8;
	buffer[2] = value & 0xff;

	v4l2_dbg(2, debug, sd,
		 "mt9v011: writing 0x%02x 0x%04x\n", buffer[0], value);
	rc = i2c_master_send(c, buffer, 3);
	अगर (rc != 3)
		v4l2_dbg(0, debug, sd,
			 "i2c i/o error: rc == %d (should be 3)\n", rc);
पूर्ण


काष्ठा i2c_reg_value अणु
	अचिन्हित अक्षर reg;
	u16           value;
पूर्ण;

/*
 * Values used at the original driver
 * Some values are marked as Reserved at the datasheet
 */
अटल स्थिर काष्ठा i2c_reg_value mt9v011_init_शेष[] = अणु
		अणु R0D_MT9V011_RESET, 0x0001 पूर्ण,
		अणु R0D_MT9V011_RESET, 0x0000 पूर्ण,

		अणु R0C_MT9V011_SHUTTER_DELAY, 0x0000 पूर्ण,
		अणु R09_MT9V011_SHUTTER_WIDTH, 0x1fc पूर्ण,

		अणु R0A_MT9V011_CLK_SPEED, 0x0000 पूर्ण,
		अणु R1E_MT9V011_DIGITAL_ZOOM,  0x0000 पूर्ण,

		अणु R07_MT9V011_OUT_CTRL, 0x0002 पूर्ण,	/* chip enable */
पूर्ण;


अटल u16 calc_mt9v011_gain(s16 lineargain)
अणु

	u16 digitalgain = 0;
	u16 analogmult = 0;
	u16 analoginit = 0;

	अगर (lineargain < 0)
		lineargain = 0;

	/* recommended minimum */
	lineargain += 0x0020;

	अगर (lineargain > 2047)
		lineargain = 2047;

	अगर (lineargain > 1023) अणु
		digitalgain = 3;
		analogmult = 3;
		analoginit = lineargain / 16;
	पूर्ण अन्यथा अगर (lineargain > 511) अणु
		digitalgain = 1;
		analogmult = 3;
		analoginit = lineargain / 8;
	पूर्ण अन्यथा अगर (lineargain > 255) अणु
		analogmult = 3;
		analoginit = lineargain / 4;
	पूर्ण अन्यथा अगर (lineargain > 127) अणु
		analogmult = 1;
		analoginit = lineargain / 2;
	पूर्ण अन्यथा
		analoginit = lineargain;

	वापस analoginit + (analogmult << 7) + (digitalgain << 9);

पूर्ण

अटल व्योम set_balance(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा mt9v011 *core = to_mt9v011(sd);
	u16 green_gain, blue_gain, red_gain;
	u16 exposure;
	s16 bal;

	exposure = core->exposure;

	green_gain = calc_mt9v011_gain(core->global_gain);

	bal = core->global_gain;
	bal += (core->blue_bal * core->global_gain / (1 << 7));
	blue_gain = calc_mt9v011_gain(bal);

	bal = core->global_gain;
	bal += (core->red_bal * core->global_gain / (1 << 7));
	red_gain = calc_mt9v011_gain(bal);

	mt9v011_ग_लिखो(sd, R2B_MT9V011_GREEN_1_GAIN, green_gain);
	mt9v011_ग_लिखो(sd, R2E_MT9V011_GREEN_2_GAIN, green_gain);
	mt9v011_ग_लिखो(sd, R2C_MT9V011_BLUE_GAIN, blue_gain);
	mt9v011_ग_लिखो(sd, R2D_MT9V011_RED_GAIN, red_gain);
	mt9v011_ग_लिखो(sd, R09_MT9V011_SHUTTER_WIDTH, exposure);
पूर्ण

अटल व्योम calc_fps(काष्ठा v4l2_subdev *sd, u32 *numerator, u32 *denominator)
अणु
	काष्ठा mt9v011 *core = to_mt9v011(sd);
	अचिन्हित height, width, hblank, vblank, speed;
	अचिन्हित row_समय, t_समय;
	u64 frames_per_ms;
	अचिन्हित पंचांगp;

	height = mt9v011_पढ़ो(sd, R03_MT9V011_HEIGHT);
	width = mt9v011_पढ़ो(sd, R04_MT9V011_WIDTH);
	hblank = mt9v011_पढ़ो(sd, R05_MT9V011_HBLANK);
	vblank = mt9v011_पढ़ो(sd, R06_MT9V011_VBLANK);
	speed = mt9v011_पढ़ो(sd, R0A_MT9V011_CLK_SPEED);

	row_समय = (width + 113 + hblank) * (speed + 2);
	t_समय = row_समय * (height + vblank + 1);

	frames_per_ms = core->xtal * 1000l;
	करो_भाग(frames_per_ms, t_समय);
	पंचांगp = frames_per_ms;

	v4l2_dbg(1, debug, sd, "Programmed to %u.%03u fps (%d pixel clcks)\n",
		पंचांगp / 1000, पंचांगp % 1000, t_समय);

	अगर (numerator && denominator) अणु
		*numerator = 1000;
		*denominator = (u32)frames_per_ms;
	पूर्ण
पूर्ण

अटल u16 calc_speed(काष्ठा v4l2_subdev *sd, u32 numerator, u32 denominator)
अणु
	काष्ठा mt9v011 *core = to_mt9v011(sd);
	अचिन्हित height, width, hblank, vblank;
	अचिन्हित row_समय, line_समय;
	u64 t_समय, speed;

	/* Aव्योम bogus calculus */
	अगर (!numerator || !denominator)
		वापस 0;

	height = mt9v011_पढ़ो(sd, R03_MT9V011_HEIGHT);
	width = mt9v011_पढ़ो(sd, R04_MT9V011_WIDTH);
	hblank = mt9v011_पढ़ो(sd, R05_MT9V011_HBLANK);
	vblank = mt9v011_पढ़ो(sd, R06_MT9V011_VBLANK);

	row_समय = width + 113 + hblank;
	line_समय = height + vblank + 1;

	t_समय = core->xtal * ((u64)numerator);
	/* round to the बंदst value */
	t_समय += denominator / 2;
	करो_भाग(t_समय, denominator);

	speed = t_समय;
	करो_भाग(speed, row_समय * line_समय);

	/* Aव्योम having a negative value क्रम speed */
	अगर (speed < 2)
		speed = 0;
	अन्यथा
		speed -= 2;

	/* Aव्योम speed overflow */
	अगर (speed > 15)
		वापस 15;

	वापस (u16)speed;
पूर्ण

अटल व्योम set_res(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा mt9v011 *core = to_mt9v011(sd);
	अचिन्हित vstart, hstart;

	/*
	 * The mt9v011 करोesn't have scaling. So, in order to select the desired
	 * resolution, we're cropping at the middle of the sensor.
	 * hblank and vblank should be adjusted, in order to warrant that
	 * we'll preserve the line timings क्रम 30 fps, no matter what resolution
	 * is selected.
	 * NOTE: datasheet says that width (and height) should be filled with
	 * width-1. However, this करोesn't work, since one pixel per line will
	 * be missing.
	 */

	hstart = 20 + (640 - core->width) / 2;
	mt9v011_ग_लिखो(sd, R02_MT9V011_COLSTART, hstart);
	mt9v011_ग_लिखो(sd, R04_MT9V011_WIDTH, core->width);
	mt9v011_ग_लिखो(sd, R05_MT9V011_HBLANK, 771 - core->width);

	vstart = 8 + (480 - core->height) / 2;
	mt9v011_ग_लिखो(sd, R01_MT9V011_ROWSTART, vstart);
	mt9v011_ग_लिखो(sd, R03_MT9V011_HEIGHT, core->height);
	mt9v011_ग_लिखो(sd, R06_MT9V011_VBLANK, 508 - core->height);

	calc_fps(sd, शून्य, शून्य);
पूर्ण;

अटल व्योम set_पढ़ो_mode(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा mt9v011 *core = to_mt9v011(sd);
	अचिन्हित mode = 0x1000;

	अगर (core->hflip)
		mode |= 0x4000;

	अगर (core->vflip)
		mode |= 0x8000;

	mt9v011_ग_लिखो(sd, R20_MT9V011_READ_MODE, mode);
पूर्ण

अटल पूर्णांक mt9v011_reset(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mt9v011_init_शेष); i++)
		mt9v011_ग_लिखो(sd, mt9v011_init_शेष[i].reg,
			       mt9v011_init_शेष[i].value);

	set_balance(sd);
	set_res(sd);
	set_पढ़ो_mode(sd);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v011_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG8_1X8;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9v011_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा mt9v011 *core = to_mt9v011(sd);

	अगर (क्रमmat->pad || fmt->code != MEDIA_BUS_FMT_SGRBG8_1X8)
		वापस -EINVAL;

	v4l_bound_align_image(&fmt->width, 48, 639, 1,
			      &fmt->height, 32, 480, 1, 0);
	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		core->width = fmt->width;
		core->height = fmt->height;

		set_res(sd);
	पूर्ण अन्यथा अणु
		cfg->try_fmt = *fmt;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v011_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	calc_fps(sd,
		 &ival->पूर्णांकerval.numerator,
		 &ival->पूर्णांकerval.denominator);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v011_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;
	u16 speed;

	speed = calc_speed(sd, tpf->numerator, tpf->denominator);

	mt9v011_ग_लिखो(sd, R0A_MT9V011_CLK_SPEED, speed);
	v4l2_dbg(1, debug, sd, "Setting speed to %d\n", speed);

	/* Recalculate and update fps info */
	calc_fps(sd, &tpf->numerator, &tpf->denominator);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक mt9v011_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = mt9v011_पढ़ो(sd, reg->reg & 0xff);
	reg->size = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v011_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	mt9v011_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xffff);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mt9v011_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9v011 *core =
		container_of(ctrl->handler, काष्ठा mt9v011, ctrls);
	काष्ठा v4l2_subdev *sd = &core->sd;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		core->global_gain = ctrl->val;
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		core->exposure = ctrl->val;
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		core->red_bal = ctrl->val;
		अवरोध;
	हाल V4L2_CID_BLUE_BALANCE:
		core->blue_bal = ctrl->val;
		अवरोध;
	हाल V4L2_CID_HFLIP:
		core->hflip = ctrl->val;
		set_पढ़ो_mode(sd);
		वापस 0;
	हाल V4L2_CID_VFLIP:
		core->vflip = ctrl->val;
		set_पढ़ो_mode(sd);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	set_balance(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9v011_ctrl_ops = अणु
	.s_ctrl = mt9v011_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9v011_core_ops = अणु
	.reset = mt9v011_reset,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = mt9v011_g_रेजिस्टर,
	.s_रेजिस्टर = mt9v011_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9v011_video_ops = अणु
	.g_frame_पूर्णांकerval = mt9v011_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = mt9v011_s_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9v011_pad_ops = अणु
	.क्रमागत_mbus_code = mt9v011_क्रमागत_mbus_code,
	.set_fmt = mt9v011_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9v011_ops = अणु
	.core  = &mt9v011_core_ops,
	.video = &mt9v011_video_ops,
	.pad   = &mt9v011_pad_ops,
पूर्ण;


/****************************************************************************
			I2C Client & Driver
 ****************************************************************************/

अटल पूर्णांक mt9v011_probe(काष्ठा i2c_client *c,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	u16 version;
	काष्ठा mt9v011 *core;
	काष्ठा v4l2_subdev *sd;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक ret;
#पूर्ण_अगर

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(c->adapter,
	     I2C_FUNC_SMBUS_READ_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -EIO;

	core = devm_kzalloc(&c->dev, माप(काष्ठा mt9v011), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	sd = &core->sd;
	v4l2_i2c_subdev_init(sd, c, &mt9v011_ops);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	core->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;

	ret = media_entity_pads_init(&sd->entity, 1, &core->pad);
	अगर (ret < 0)
		वापस ret;
#पूर्ण_अगर

	/* Check अगर the sensor is really a MT9V011 */
	version = mt9v011_पढ़ो(sd, R00_MT9V011_CHIP_VERSION);
	अगर ((version != MT9V011_VERSION) &&
	    (version != MT9V011_REV_B_VERSION)) अणु
		v4l2_info(sd, "*** unknown micron chip detected (0x%04x).\n",
			  version);
		वापस -EINVAL;
	पूर्ण

	v4l2_ctrl_handler_init(&core->ctrls, 5);
	v4l2_ctrl_new_std(&core->ctrls, &mt9v011_ctrl_ops,
			  V4L2_CID_GAIN, 0, (1 << 12) - 1 - 0x20, 1, 0x20);
	v4l2_ctrl_new_std(&core->ctrls, &mt9v011_ctrl_ops,
			  V4L2_CID_EXPOSURE, 0, 2047, 1, 0x01fc);
	v4l2_ctrl_new_std(&core->ctrls, &mt9v011_ctrl_ops,
			  V4L2_CID_RED_BALANCE, -(1 << 9), (1 << 9) - 1, 1, 0);
	v4l2_ctrl_new_std(&core->ctrls, &mt9v011_ctrl_ops,
			  V4L2_CID_BLUE_BALANCE, -(1 << 9), (1 << 9) - 1, 1, 0);
	v4l2_ctrl_new_std(&core->ctrls, &mt9v011_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&core->ctrls, &mt9v011_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);

	अगर (core->ctrls.error) अणु
		पूर्णांक ret = core->ctrls.error;

		v4l2_err(sd, "control initialization error %d\n", ret);
		v4l2_ctrl_handler_मुक्त(&core->ctrls);
		वापस ret;
	पूर्ण
	core->sd.ctrl_handler = &core->ctrls;

	core->global_gain = 0x0024;
	core->exposure = 0x01fc;
	core->width  = 640;
	core->height = 480;
	core->xtal = 27000000;	/* Hz */

	अगर (c->dev.platक्रमm_data) अणु
		काष्ठा mt9v011_platक्रमm_data *pdata = c->dev.platक्रमm_data;

		core->xtal = pdata->xtal;
		v4l2_dbg(1, debug, sd, "xtal set to %d.%03d MHz\n",
			core->xtal / 1000000, (core->xtal / 1000) % 1000);
	पूर्ण

	v4l_info(c, "chip found @ 0x%02x (%s - chip version 0x%04x)\n",
		 c->addr << 1, c->adapter->name, version);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v011_हटाओ(काष्ठा i2c_client *c)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(c);
	काष्ठा mt9v011 *core = to_mt9v011(sd);

	v4l2_dbg(1, debug, sd,
		"mt9v011.c: removing mt9v011 adapter on address 0x%x\n",
		c->addr << 1);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&core->ctrls);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id mt9v011_id[] = अणु
	अणु "mt9v011", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt9v011_id);

अटल काष्ठा i2c_driver mt9v011_driver = अणु
	.driver = अणु
		.name	= "mt9v011",
	पूर्ण,
	.probe		= mt9v011_probe,
	.हटाओ		= mt9v011_हटाओ,
	.id_table	= mt9v011_id,
पूर्ण;

module_i2c_driver(mt9v011_driver);
