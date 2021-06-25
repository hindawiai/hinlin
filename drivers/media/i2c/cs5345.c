<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cs5345 Cirrus Logic 24-bit, 192 kHz Stereo Audio ADC
 * Copyright (C) 2007 Hans Verkuil
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

MODULE_DESCRIPTION("i2c device driver for cs5345 Audio ADC");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL");

अटल bool debug;

module_param(debug, bool, 0644);

MODULE_PARM_DESC(debug, "Debugging messages, 0=Off (default), 1=On");

काष्ठा cs5345_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
पूर्ण;

अटल अंतरभूत काष्ठा cs5345_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा cs5345_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा cs5345_state, hdl)->sd;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक cs5345_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक cs5345_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक cs5345_s_routing(काष्ठा v4l2_subdev *sd,
			    u32 input, u32 output, u32 config)
अणु
	अगर ((input & 0xf) > 6) अणु
		v4l2_err(sd, "Invalid input %d.\n", input);
		वापस -EINVAL;
	पूर्ण
	cs5345_ग_लिखो(sd, 0x09, input & 0xf);
	cs5345_ग_लिखो(sd, 0x05, input & 0xf0);
	वापस 0;
पूर्ण

अटल पूर्णांक cs5345_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		cs5345_ग_लिखो(sd, 0x04, ctrl->val ? 0x80 : 0);
		वापस 0;
	हाल V4L2_CID_AUDIO_VOLUME:
		cs5345_ग_लिखो(sd, 0x07, ((u8)ctrl->val) & 0x3f);
		cs5345_ग_लिखो(sd, 0x08, ((u8)ctrl->val) & 0x3f);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक cs5345_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->size = 1;
	reg->val = cs5345_पढ़ो(sd, reg->reg & 0x1f);
	वापस 0;
पूर्ण

अटल पूर्णांक cs5345_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	cs5345_ग_लिखो(sd, reg->reg & 0x1f, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cs5345_log_status(काष्ठा v4l2_subdev *sd)
अणु
	u8 v = cs5345_पढ़ो(sd, 0x09) & 7;
	u8 m = cs5345_पढ़ो(sd, 0x04);
	पूर्णांक vol = cs5345_पढ़ो(sd, 0x08) & 0x3f;

	v4l2_info(sd, "Input:  %d%s\n", v,
			(m & 0x80) ? " (muted)" : "");
	अगर (vol >= 32)
		vol = vol - 64;
	v4l2_info(sd, "Volume: %d dB\n", vol);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops cs5345_ctrl_ops = अणु
	.s_ctrl = cs5345_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops cs5345_core_ops = अणु
	.log_status = cs5345_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = cs5345_g_रेजिस्टर,
	.s_रेजिस्टर = cs5345_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops cs5345_audio_ops = अणु
	.s_routing = cs5345_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops cs5345_ops = अणु
	.core = &cs5345_core_ops,
	.audio = &cs5345_audio_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक cs5345_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs5345_state *state;
	काष्ठा v4l2_subdev *sd;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &cs5345_ops);

	v4l2_ctrl_handler_init(&state->hdl, 2);
	v4l2_ctrl_new_std(&state->hdl, &cs5345_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&state->hdl, &cs5345_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, -24, 24, 1, 0);
	sd->ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		पूर्णांक err = state->hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण
	/* set volume/mute */
	v4l2_ctrl_handler_setup(&state->hdl);

	cs5345_ग_लिखो(sd, 0x02, 0x00);
	cs5345_ग_लिखो(sd, 0x04, 0x01);
	cs5345_ग_लिखो(sd, 0x09, 0x01);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक cs5345_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा cs5345_state *state = to_state(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id cs5345_id[] = अणु
	अणु "cs5345", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs5345_id);

अटल काष्ठा i2c_driver cs5345_driver = अणु
	.driver = अणु
		.name	= "cs5345",
	पूर्ण,
	.probe		= cs5345_probe,
	.हटाओ		= cs5345_हटाओ,
	.id_table	= cs5345_id,
पूर्ण;

module_i2c_driver(cs5345_driver);
