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
#समावेश <linux/slab.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा TW2804_REG_AUTOGAIN		0x02
#घोषणा TW2804_REG_HUE			0x0f
#घोषणा TW2804_REG_SATURATION		0x10
#घोषणा TW2804_REG_CONTRAST		0x11
#घोषणा TW2804_REG_BRIGHTNESS		0x12
#घोषणा TW2804_REG_COLOR_KILLER		0x14
#घोषणा TW2804_REG_GAIN			0x3c
#घोषणा TW2804_REG_CHROMA_GAIN		0x3d
#घोषणा TW2804_REG_BLUE_BALANCE		0x3e
#घोषणा TW2804_REG_RED_BALANCE		0x3f

काष्ठा tw2804 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	u8 channel:2;
	u8 input:1;
	पूर्णांक norm;
पूर्ण;

अटल स्थिर u8 global_रेजिस्टरs[] = अणु
	0x39, 0x00,
	0x3a, 0xff,
	0x3b, 0x84,
	0x3c, 0x80,
	0x3d, 0x80,
	0x3e, 0x82,
	0x3f, 0x82,
	0x78, 0x00,
	0xff, 0xff, /* Terminator (reg 0xff करोes not exist) */
पूर्ण;

अटल स्थिर u8 channel_रेजिस्टरs[] = अणु
	0x01, 0xc4,
	0x02, 0xa5,
	0x03, 0x20,
	0x04, 0xd0,
	0x05, 0x20,
	0x06, 0xd0,
	0x07, 0x88,
	0x08, 0x20,
	0x09, 0x07,
	0x0a, 0xf0,
	0x0b, 0x07,
	0x0c, 0xf0,
	0x0d, 0x40,
	0x0e, 0xd2,
	0x0f, 0x80,
	0x10, 0x80,
	0x11, 0x80,
	0x12, 0x80,
	0x13, 0x1f,
	0x14, 0x00,
	0x15, 0x00,
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0xff,
	0x19, 0xff,
	0x1a, 0xff,
	0x1b, 0xff,
	0x1c, 0xff,
	0x1d, 0xff,
	0x1e, 0xff,
	0x1f, 0xff,
	0x20, 0x07,
	0x21, 0x07,
	0x22, 0x00,
	0x23, 0x91,
	0x24, 0x51,
	0x25, 0x03,
	0x26, 0x00,
	0x27, 0x00,
	0x28, 0x00,
	0x29, 0x00,
	0x2a, 0x00,
	0x2b, 0x00,
	0x2c, 0x00,
	0x2d, 0x00,
	0x2e, 0x00,
	0x2f, 0x00,
	0x30, 0x00,
	0x31, 0x00,
	0x32, 0x00,
	0x33, 0x00,
	0x34, 0x00,
	0x35, 0x00,
	0x36, 0x00,
	0x37, 0x00,
	0xff, 0xff, /* Terminator (reg 0xff करोes not exist) */
पूर्ण;

अटल पूर्णांक ग_लिखो_reg(काष्ठा i2c_client *client, u8 reg, u8 value, u8 channel)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg | (channel << 6), value);
पूर्ण

अटल पूर्णांक ग_लिखो_regs(काष्ठा i2c_client *client, स्थिर u8 *regs, u8 channel)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; regs[i] != 0xff; i += 2) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client,
				regs[i] | (channel << 6), regs[i + 1]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_reg(काष्ठा i2c_client *client, u8 reg, u8 channel)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, (reg) | (channel << 6));
पूर्ण

अटल अंतरभूत काष्ठा tw2804 *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tw2804, sd);
पूर्ण

अटल अंतरभूत काष्ठा tw2804 *to_state_from_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा tw2804, hdl);
पूर्ण

अटल पूर्णांक tw2804_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tw2804 *state = to_state(sd);

	v4l2_info(sd, "Standard: %s\n",
			state->norm & V4L2_STD_525_60 ? "60 Hz" : "50 Hz");
	v4l2_info(sd, "Channel: %d\n", state->channel);
	v4l2_info(sd, "Input: %d\n", state->input);
	वापस v4l2_ctrl_subdev_log_status(sd);
पूर्ण

/*
 * These अस्थिर controls are needed because all four channels share
 * these controls. So a change made to them through one channel would
 * require another channel to be updated.
 *
 * Normally this would have been करोne in a dअगरferent way, but since the one
 * board that uses this driver sees this single chip as अगर it was on four
 * dअगरferent i2c adapters (each adapter beदीर्घing to a separate instance of
 * the same USB driver) there is no reliable method that I have found to let
 * the instances know about each other.
 *
 * So implementing these global रेजिस्टरs as अस्थिर is the best we can करो.
 */
अटल पूर्णांक tw2804_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा tw2804 *state = to_state_from_ctrl(ctrl);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&state->sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		ctrl->val = पढ़ो_reg(client, TW2804_REG_GAIN, 0);
		वापस 0;

	हाल V4L2_CID_CHROMA_GAIN:
		ctrl->val = पढ़ो_reg(client, TW2804_REG_CHROMA_GAIN, 0);
		वापस 0;

	हाल V4L2_CID_BLUE_BALANCE:
		ctrl->val = पढ़ो_reg(client, TW2804_REG_BLUE_BALANCE, 0);
		वापस 0;

	हाल V4L2_CID_RED_BALANCE:
		ctrl->val = पढ़ो_reg(client, TW2804_REG_RED_BALANCE, 0);
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tw2804_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा tw2804 *state = to_state_from_ctrl(ctrl);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&state->sd);
	पूर्णांक addr;
	पूर्णांक reg;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		addr = TW2804_REG_AUTOGAIN;
		reg = पढ़ो_reg(client, addr, state->channel);
		अगर (reg < 0)
			वापस reg;
		अगर (ctrl->val == 0)
			reg &= ~(1 << 7);
		अन्यथा
			reg |= 1 << 7;
		वापस ग_लिखो_reg(client, addr, reg, state->channel);

	हाल V4L2_CID_COLOR_KILLER:
		addr = TW2804_REG_COLOR_KILLER;
		reg = पढ़ो_reg(client, addr, state->channel);
		अगर (reg < 0)
			वापस reg;
		reg = (reg & ~(0x03)) | (ctrl->val == 0 ? 0x02 : 0x03);
		वापस ग_लिखो_reg(client, addr, reg, state->channel);

	हाल V4L2_CID_GAIN:
		वापस ग_लिखो_reg(client, TW2804_REG_GAIN, ctrl->val, 0);

	हाल V4L2_CID_CHROMA_GAIN:
		वापस ग_लिखो_reg(client, TW2804_REG_CHROMA_GAIN, ctrl->val, 0);

	हाल V4L2_CID_BLUE_BALANCE:
		वापस ग_लिखो_reg(client, TW2804_REG_BLUE_BALANCE, ctrl->val, 0);

	हाल V4L2_CID_RED_BALANCE:
		वापस ग_लिखो_reg(client, TW2804_REG_RED_BALANCE, ctrl->val, 0);

	हाल V4L2_CID_BRIGHTNESS:
		वापस ग_लिखो_reg(client, TW2804_REG_BRIGHTNESS,
				ctrl->val, state->channel);

	हाल V4L2_CID_CONTRAST:
		वापस ग_लिखो_reg(client, TW2804_REG_CONTRAST,
				ctrl->val, state->channel);

	हाल V4L2_CID_SATURATION:
		वापस ग_लिखो_reg(client, TW2804_REG_SATURATION,
				ctrl->val, state->channel);

	हाल V4L2_CID_HUE:
		वापस ग_लिखो_reg(client, TW2804_REG_HUE,
				ctrl->val, state->channel);

	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tw2804_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा tw2804 *dec = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	bool is_60hz = norm & V4L2_STD_525_60;
	u8 regs[] = अणु
		0x01, is_60hz ? 0xc4 : 0x84,
		0x09, is_60hz ? 0x07 : 0x04,
		0x0a, is_60hz ? 0xf0 : 0x20,
		0x0b, is_60hz ? 0x07 : 0x04,
		0x0c, is_60hz ? 0xf0 : 0x20,
		0x0d, is_60hz ? 0x40 : 0x4a,
		0x16, is_60hz ? 0x00 : 0x40,
		0x17, is_60hz ? 0x00 : 0x40,
		0x20, is_60hz ? 0x07 : 0x0f,
		0x21, is_60hz ? 0x07 : 0x0f,
		0xff, 0xff,
	पूर्ण;

	ग_लिखो_regs(client, regs, dec->channel);
	dec->norm = norm;
	वापस 0;
पूर्ण

अटल पूर्णांक tw2804_s_video_routing(काष्ठा v4l2_subdev *sd, u32 input, u32 output,
	u32 config)
अणु
	काष्ठा tw2804 *dec = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक reg;

	अगर (config && config - 1 != dec->channel) अणु
		अगर (config > 4) अणु
			dev_err(&client->dev,
				"channel %d is not between 1 and 4!\n", config);
			वापस -EINVAL;
		पूर्ण
		dec->channel = config - 1;
		dev_dbg(&client->dev, "initializing TW2804 channel %d\n",
			dec->channel);
		अगर (dec->channel == 0 &&
				ग_लिखो_regs(client, global_रेजिस्टरs, 0) < 0) अणु
			dev_err(&client->dev,
				"error initializing TW2804 global registers\n");
			वापस -EIO;
		पूर्ण
		अगर (ग_लिखो_regs(client, channel_रेजिस्टरs, dec->channel) < 0) अणु
			dev_err(&client->dev,
				"error initializing TW2804 channel %d\n",
				dec->channel);
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (input > 1)
		वापस -EINVAL;

	अगर (input == dec->input)
		वापस 0;

	reg = पढ़ो_reg(client, 0x22, dec->channel);

	अगर (reg >= 0) अणु
		अगर (input == 0)
			reg &= ~(1 << 2);
		अन्यथा
			reg |= 1 << 2;
		reg = ग_लिखो_reg(client, 0x22, reg, dec->channel);
	पूर्ण

	अगर (reg >= 0)
		dec->input = input;
	अन्यथा
		वापस reg;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops tw2804_ctrl_ops = अणु
	.g_अस्थिर_ctrl = tw2804_g_अस्थिर_ctrl,
	.s_ctrl = tw2804_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops tw2804_video_ops = अणु
	.s_std = tw2804_s_std,
	.s_routing = tw2804_s_video_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops tw2804_core_ops = अणु
	.log_status = tw2804_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tw2804_ops = अणु
	.core = &tw2804_core_ops,
	.video = &tw2804_video_ops,
पूर्ण;

अटल पूर्णांक tw2804_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा tw2804 *state;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक err;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &tw2804_ops);
	state->channel = -1;
	state->norm = V4L2_STD_NTSC;

	v4l2_ctrl_handler_init(&state->hdl, 10);
	v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_HUE, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_COLOR_KILLER, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_AUTOGAIN, 0, 1, 1, 0);
	ctrl = v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_GAIN, 0, 255, 1, 128);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
	ctrl = v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_CHROMA_GAIN, 0, 255, 1, 128);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
	ctrl = v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_BLUE_BALANCE, 0, 255, 1, 122);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
	ctrl = v4l2_ctrl_new_std(&state->hdl, &tw2804_ctrl_ops,
				V4L2_CID_RED_BALANCE, 0, 255, 1, 122);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
	sd->ctrl_handler = &state->hdl;
	err = state->hdl.error;
	अगर (err) अणु
		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	वापस 0;
पूर्ण

अटल पूर्णांक tw2804_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा tw2804 *state = to_state(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tw2804_id[] = अणु
	अणु "tw2804", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tw2804_id);

अटल काष्ठा i2c_driver tw2804_driver = अणु
	.driver = अणु
		.name	= "tw2804",
	पूर्ण,
	.probe		= tw2804_probe,
	.हटाओ		= tw2804_हटाओ,
	.id_table	= tw2804_id,
पूर्ण;

module_i2c_driver(tw2804_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TW2804/TW2802 V4L2 i2c driver");
MODULE_AUTHOR("Micronas USA Inc");
