<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <linux/slab.h>

MODULE_DESCRIPTION("TW9903 I2C subdev driver");
MODULE_LICENSE("GPL v2");

/*
 * This driver is based on the wis-tw9903.c source that was in
 * drivers/staging/media/go7007. That source had commented out code क्रम
 * saturation and scaling (neither seemed to work). If anyone ever माला_लो
 * hardware to test this driver, then that code might be useful to look at.
 * You need to get the kernel sources of, say, kernel 3.8 where that
 * wis-tw9903 driver is still present.
 */

काष्ठा tw9903 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	v4l2_std_id norm;
पूर्ण;

अटल अंतरभूत काष्ठा tw9903 *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tw9903, sd);
पूर्ण

अटल स्थिर u8 initial_रेजिस्टरs[] = अणु
	0x02, 0x44, /* input 1, composite */
	0x03, 0x92, /* correct digital क्रमmat */
	0x04, 0x00,
	0x05, 0x80, /* or 0x00 क्रम PAL */
	0x06, 0x40, /* second पूर्णांकernal current reference */
	0x07, 0x02, /* winकरोw */
	0x08, 0x14, /* winकरोw */
	0x09, 0xf0, /* winकरोw */
	0x0a, 0x81, /* winकरोw */
	0x0b, 0xd0, /* winकरोw */
	0x0c, 0x8c,
	0x0d, 0x00, /* scaling */
	0x0e, 0x11, /* scaling */
	0x0f, 0x00, /* scaling */
	0x10, 0x00, /* brightness */
	0x11, 0x60, /* contrast */
	0x12, 0x01, /* sharpness */
	0x13, 0x7f, /* U gain */
	0x14, 0x5a, /* V gain */
	0x15, 0x00, /* hue */
	0x16, 0xc3, /* sharpness */
	0x18, 0x00,
	0x19, 0x58, /* vbi */
	0x1a, 0x80,
	0x1c, 0x0f, /* video norm */
	0x1d, 0x7f, /* video norm */
	0x20, 0xa0, /* clamping gain (working 0x50) */
	0x21, 0x22,
	0x22, 0xf0,
	0x23, 0xfe,
	0x24, 0x3c,
	0x25, 0x38,
	0x26, 0x44,
	0x27, 0x20,
	0x28, 0x00,
	0x29, 0x15,
	0x2a, 0xa0,
	0x2b, 0x44,
	0x2c, 0x37,
	0x2d, 0x00,
	0x2e, 0xa5, /* burst PLL control (working: a9) */
	0x2f, 0xe0, /* 0xea is blue test frame -- 0xe0 क्रम normal */
	0x31, 0x00,
	0x33, 0x22,
	0x34, 0x11,
	0x35, 0x35,
	0x3b, 0x05,
	0x06, 0xc0, /* reset device */
	0x00, 0x00, /* Terminator (reg 0x00 is पढ़ो-only) */
पूर्ण;

अटल पूर्णांक ग_लिखो_reg(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल पूर्णांक ग_लिखो_regs(काष्ठा v4l2_subdev *sd, स्थिर u8 *regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; regs[i] != 0x00; i += 2)
		अगर (ग_लिखो_reg(sd, regs[i], regs[i + 1]) < 0)
			वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक tw9903_s_video_routing(काष्ठा v4l2_subdev *sd, u32 input,
				      u32 output, u32 config)
अणु
	ग_लिखो_reg(sd, 0x02, 0x40 | (input << 1));
	वापस 0;
पूर्ण

अटल पूर्णांक tw9903_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा tw9903 *dec = to_state(sd);
	bool is_60hz = norm & V4L2_STD_525_60;
	अटल स्थिर u8 config_60hz[] = अणु
		0x05, 0x80,
		0x07, 0x02,
		0x08, 0x14,
		0x09, 0xf0,
		0,    0,
	पूर्ण;
	अटल स्थिर u8 config_50hz[] = अणु
		0x05, 0x00,
		0x07, 0x12,
		0x08, 0x18,
		0x09, 0x20,
		0,    0,
	पूर्ण;

	ग_लिखो_regs(sd, is_60hz ? config_60hz : config_50hz);
	dec->norm = norm;
	वापस 0;
पूर्ण


अटल पूर्णांक tw9903_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा tw9903 *dec = container_of(ctrl->handler, काष्ठा tw9903, hdl);
	काष्ठा v4l2_subdev *sd = &dec->sd;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ग_लिखो_reg(sd, 0x10, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ग_लिखो_reg(sd, 0x11, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		ग_लिखो_reg(sd, 0x15, ctrl->val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tw9903_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tw9903 *dec = to_state(sd);
	bool is_60hz = dec->norm & V4L2_STD_525_60;

	v4l2_info(sd, "Standard: %d Hz\n", is_60hz ? 60 : 50);
	v4l2_ctrl_subdev_log_status(sd);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------*/

अटल स्थिर काष्ठा v4l2_ctrl_ops tw9903_ctrl_ops = अणु
	.s_ctrl = tw9903_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops tw9903_core_ops = अणु
	.log_status = tw9903_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops tw9903_video_ops = अणु
	.s_std = tw9903_s_std,
	.s_routing = tw9903_s_video_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tw9903_ops = अणु
	.core = &tw9903_core_ops,
	.video = &tw9903_video_ops,
पूर्ण;

/* --------------------------------------------------------------------------*/

अटल पूर्णांक tw9903_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tw9903 *dec;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl_handler *hdl;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	dec = devm_kzalloc(&client->dev, माप(*dec), GFP_KERNEL);
	अगर (dec == शून्य)
		वापस -ENOMEM;
	sd = &dec->sd;
	v4l2_i2c_subdev_init(sd, client, &tw9903_ops);
	hdl = &dec->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &tw9903_ctrl_ops,
		V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &tw9903_ctrl_ops,
		V4L2_CID_CONTRAST, 0, 255, 1, 0x60);
	v4l2_ctrl_new_std(hdl, &tw9903_ctrl_ops,
		V4L2_CID_HUE, -128, 127, 1, 0);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण

	/* Initialize tw9903 */
	dec->norm = V4L2_STD_NTSC;

	अगर (ग_लिखो_regs(sd, initial_रेजिस्टरs) < 0) अणु
		v4l2_err(client, "error initializing TW9903\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tw9903_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&to_state(sd)->hdl);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id tw9903_id[] = अणु
	अणु "tw9903", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tw9903_id);

अटल काष्ठा i2c_driver tw9903_driver = अणु
	.driver = अणु
		.name	= "tw9903",
	पूर्ण,
	.probe = tw9903_probe,
	.हटाओ = tw9903_हटाओ,
	.id_table = tw9903_id,
पूर्ण;
module_i2c_driver(tw9903_driver);
