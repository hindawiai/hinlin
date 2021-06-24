<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tlv320aic23b - driver version 0.0.1
 *
 * Copyright (C) 2006 Scott Alfter <salfter@ssai.us>
 *
 * Based on wm8775 driver
 *
 * Copyright (C) 2004 Ulf Eklund <ivtv at eklund.to>
 * Copyright (C) 2005 Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

MODULE_DESCRIPTION("tlv320aic23b driver");
MODULE_AUTHOR("Scott Alfter, Ulf Eklund, Hans Verkuil");
MODULE_LICENSE("GPL");


/* ----------------------------------------------------------------------- */

काष्ठा tlv320aic23b_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
पूर्ण;

अटल अंतरभूत काष्ठा tlv320aic23b_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tlv320aic23b_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा tlv320aic23b_state, hdl)->sd;
पूर्ण

अटल पूर्णांक tlv320aic23b_ग_लिखो(काष्ठा v4l2_subdev *sd, पूर्णांक reg, u16 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक i;

	अगर ((reg < 0 || reg > 9) && (reg != 15)) अणु
		v4l2_err(sd, "Invalid register R%d\n", reg);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		अगर (i2c_smbus_ग_लिखो_byte_data(client,
				(reg << 1) | (val >> 8), val & 0xff) == 0)
			वापस 0;
	v4l2_err(sd, "I2C: cannot write %03x to register R%d\n", val, reg);
	वापस -1;
पूर्ण

अटल पूर्णांक tlv320aic23b_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
अणु
	चयन (freq) अणु
	हाल 32000: /* set sample rate to 32 kHz */
		tlv320aic23b_ग_लिखो(sd, 8, 0x018);
		अवरोध;
	हाल 44100: /* set sample rate to 44.1 kHz */
		tlv320aic23b_ग_लिखो(sd, 8, 0x022);
		अवरोध;
	हाल 48000: /* set sample rate to 48 kHz */
		tlv320aic23b_ग_लिखो(sd, 8, 0x000);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23b_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		tlv320aic23b_ग_लिखो(sd, 0, 0x180); /* mute both channels */
		/* set gain on both channels to +3.0 dB */
		अगर (!ctrl->val)
			tlv320aic23b_ग_लिखो(sd, 0, 0x119);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tlv320aic23b_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tlv320aic23b_state *state = to_state(sd);

	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops tlv320aic23b_ctrl_ops = अणु
	.s_ctrl = tlv320aic23b_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops tlv320aic23b_core_ops = अणु
	.log_status = tlv320aic23b_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops tlv320aic23b_audio_ops = अणु
	.s_घड़ी_freq = tlv320aic23b_s_घड़ी_freq,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tlv320aic23b_ops = अणु
	.core = &tlv320aic23b_core_ops,
	.audio = &tlv320aic23b_audio_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

/* i2c implementation */

/*
 * Generic i2c probe
 * concerning the addresses: i2c wants 7 bit (without the r/w bit), so '>>1'
 */

अटल पूर्णांक tlv320aic23b_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tlv320aic23b_state *state;
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
	v4l2_i2c_subdev_init(sd, client, &tlv320aic23b_ops);

	/* Initialize tlv320aic23b */

	/* RESET */
	tlv320aic23b_ग_लिखो(sd, 15, 0x000);
	/* turn off DAC & mic input */
	tlv320aic23b_ग_लिखो(sd, 6, 0x00A);
	/* left-justअगरied, 24-bit, master mode */
	tlv320aic23b_ग_लिखो(sd, 7, 0x049);
	/* set gain on both channels to +3.0 dB */
	tlv320aic23b_ग_लिखो(sd, 0, 0x119);
	/* set sample rate to 48 kHz */
	tlv320aic23b_ग_लिखो(sd, 8, 0x000);
	/* activate digital पूर्णांकerface */
	tlv320aic23b_ग_लिखो(sd, 9, 0x001);

	v4l2_ctrl_handler_init(&state->hdl, 1);
	v4l2_ctrl_new_std(&state->hdl, &tlv320aic23b_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		पूर्णांक err = state->hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_handler_setup(&state->hdl);
	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23b_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा tlv320aic23b_state *state = to_state(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id tlv320aic23b_id[] = अणु
	अणु "tlv320aic23b", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tlv320aic23b_id);

अटल काष्ठा i2c_driver tlv320aic23b_driver = अणु
	.driver = अणु
		.name	= "tlv320aic23b",
	पूर्ण,
	.probe		= tlv320aic23b_probe,
	.हटाओ		= tlv320aic23b_हटाओ,
	.id_table	= tlv320aic23b_id,
पूर्ण;

module_i2c_driver(tlv320aic23b_driver);
