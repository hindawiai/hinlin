<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * m52790 i2c ivtv driver.
 * Copyright (C) 2007  Hans Verkuil
 *
 * A/V source चयनing Mitsubishi M52790SP/FP
 */


#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/i2c/m52790.h>
#समावेश <media/v4l2-device.h>

MODULE_DESCRIPTION("i2c device driver for m52790 A/V switch");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL");


काष्ठा m52790_state अणु
	काष्ठा v4l2_subdev sd;
	u16 input;
	u16 output;
पूर्ण;

अटल अंतरभूत काष्ठा m52790_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा m52790_state, sd);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक m52790_ग_लिखो(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा m52790_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	u8 sw1 = (state->input | state->output) & 0xff;
	u8 sw2 = (state->input | state->output) >> 8;

	वापस i2c_smbus_ग_लिखो_byte_data(client, sw1, sw2);
पूर्ण

/* Note: audio and video are linked and cannot be चयनed separately.
   So audio and video routing commands are identical क्रम this chip.
   In theory the video amplअगरier and audio modes could be handled
   separately क्रम the output, but that seems to be overसमाप्त right now.
   The same holds क्रम implementing an audio mute control, this is now
   part of the audio output routing. The normal हाल is that another
   chip takes care of the actual muting so making it part of the
   output routing seems to be the right thing to करो क्रम now. */
अटल पूर्णांक m52790_s_routing(काष्ठा v4l2_subdev *sd,
			    u32 input, u32 output, u32 config)
अणु
	काष्ठा m52790_state *state = to_state(sd);

	state->input = input;
	state->output = output;
	m52790_ग_लिखो(sd);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक m52790_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा m52790_state *state = to_state(sd);

	अगर (reg->reg != 0)
		वापस -EINVAL;
	reg->size = 1;
	reg->val = state->input | state->output;
	वापस 0;
पूर्ण

अटल पूर्णांक m52790_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा m52790_state *state = to_state(sd);

	अगर (reg->reg != 0)
		वापस -EINVAL;
	state->input = reg->val & 0x0303;
	state->output = reg->val & ~0x0303;
	m52790_ग_लिखो(sd);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक m52790_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा m52790_state *state = to_state(sd);

	v4l2_info(sd, "Switch 1: %02x\n",
			(state->input | state->output) & 0xff);
	v4l2_info(sd, "Switch 2: %02x\n",
			(state->input | state->output) >> 8);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops m52790_core_ops = अणु
	.log_status = m52790_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = m52790_g_रेजिस्टर,
	.s_रेजिस्टर = m52790_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops m52790_audio_ops = अणु
	.s_routing = m52790_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops m52790_video_ops = अणु
	.s_routing = m52790_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops m52790_ops = अणु
	.core = &m52790_core_ops,
	.audio = &m52790_audio_ops,
	.video = &m52790_video_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

/* i2c implementation */

अटल पूर्णांक m52790_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा m52790_state *state;
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
	v4l2_i2c_subdev_init(sd, client, &m52790_ops);
	state->input = M52790_IN_TUNER;
	state->output = M52790_OUT_STEREO;
	m52790_ग_लिखो(sd);
	वापस 0;
पूर्ण

अटल पूर्णांक m52790_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id m52790_id[] = अणु
	अणु "m52790", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, m52790_id);

अटल काष्ठा i2c_driver m52790_driver = अणु
	.driver = अणु
		.name	= "m52790",
	पूर्ण,
	.probe		= m52790_probe,
	.हटाओ		= m52790_हटाओ,
	.id_table	= m52790_id,
पूर्ण;

module_i2c_driver(m52790_driver);
