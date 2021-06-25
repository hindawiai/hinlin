<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cs53l32a (Adaptec AVC-2010 and AVC-2410) i2c ivtv driver.
 * Copyright (C) 2005  Martin Vaughan
 *
 * Audio source चयनing क्रम Adaptec AVC-2410 added by Trev Jackson
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

MODULE_DESCRIPTION("i2c device driver for cs53l32a Audio ADC");
MODULE_AUTHOR("Martin Vaughan");
MODULE_LICENSE("GPL");

अटल bool debug;

module_param(debug, bool, 0644);

MODULE_PARM_DESC(debug, "Debugging messages, 0=Off (default), 1=On");


काष्ठा cs53l32a_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
पूर्ण;

अटल अंतरभूत काष्ठा cs53l32a_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा cs53l32a_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा cs53l32a_state, hdl)->sd;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक cs53l32a_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल पूर्णांक cs53l32a_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक cs53l32a_s_routing(काष्ठा v4l2_subdev *sd,
			      u32 input, u32 output, u32 config)
अणु
	/* There are 2 physical inमाला_दो, but the second input can be
	   placed in two modes, the first mode bypasses the PGA (gain),
	   the second goes through the PGA. Hence there are three
	   possible inमाला_दो to choose from. */
	अगर (input > 2) अणु
		v4l2_err(sd, "Invalid input %d.\n", input);
		वापस -EINVAL;
	पूर्ण
	cs53l32a_ग_लिखो(sd, 0x01, 0x01 + (input << 4));
	वापस 0;
पूर्ण

अटल पूर्णांक cs53l32a_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		cs53l32a_ग_लिखो(sd, 0x03, ctrl->val ? 0xf0 : 0x30);
		वापस 0;
	हाल V4L2_CID_AUDIO_VOLUME:
		cs53l32a_ग_लिखो(sd, 0x04, (u8)ctrl->val);
		cs53l32a_ग_लिखो(sd, 0x05, (u8)ctrl->val);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs53l32a_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cs53l32a_state *state = to_state(sd);
	u8 v = cs53l32a_पढ़ो(sd, 0x01);

	v4l2_info(sd, "Input:  %d\n", (v >> 4) & 3);
	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops cs53l32a_ctrl_ops = अणु
	.s_ctrl = cs53l32a_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops cs53l32a_core_ops = अणु
	.log_status = cs53l32a_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops cs53l32a_audio_ops = अणु
	.s_routing = cs53l32a_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops cs53l32a_ops = अणु
	.core = &cs53l32a_core_ops,
	.audio = &cs53l32a_audio_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

/* i2c implementation */

/*
 * Generic i2c probe
 * concerning the addresses: i2c wants 7 bit (without the r/w bit), so '>>1'
 */

अटल पूर्णांक cs53l32a_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs53l32a_state *state;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक i;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	अगर (!id)
		strscpy(client->name, "cs53l32a", माप(client->name));

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &cs53l32a_ops);

	क्रम (i = 1; i <= 7; i++) अणु
		u8 v = cs53l32a_पढ़ो(sd, i);

		v4l2_dbg(1, debug, sd, "Read Reg %d %02x\n", i, v);
	पूर्ण

	v4l2_ctrl_handler_init(&state->hdl, 2);
	v4l2_ctrl_new_std(&state->hdl, &cs53l32a_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, -96, 12, 1, 0);
	v4l2_ctrl_new_std(&state->hdl, &cs53l32a_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		पूर्णांक err = state->hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण

	/* Set cs53l32a पूर्णांकernal रेजिस्टर क्रम Adaptec 2010/2410 setup */

	cs53l32a_ग_लिखो(sd, 0x01, 0x21);
	cs53l32a_ग_लिखो(sd, 0x02, 0x29);
	cs53l32a_ग_लिखो(sd, 0x03, 0x30);
	cs53l32a_ग_लिखो(sd, 0x04, 0x00);
	cs53l32a_ग_लिखो(sd, 0x05, 0x00);
	cs53l32a_ग_लिखो(sd, 0x06, 0x00);
	cs53l32a_ग_लिखो(sd, 0x07, 0x00);

	/* Display results, should be 0x21,0x29,0x30,0x00,0x00,0x00,0x00 */

	क्रम (i = 1; i <= 7; i++) अणु
		u8 v = cs53l32a_पढ़ो(sd, i);

		v4l2_dbg(1, debug, sd, "Read Reg %d %02x\n", i, v);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs53l32a_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा cs53l32a_state *state = to_state(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cs53l32a_id[] = अणु
	अणु "cs53l32a", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs53l32a_id);

अटल काष्ठा i2c_driver cs53l32a_driver = अणु
	.driver = अणु
		.name	= "cs53l32a",
	पूर्ण,
	.probe		= cs53l32a_probe,
	.हटाओ		= cs53l32a_हटाओ,
	.id_table	= cs53l32a_id,
पूर्ण;

module_i2c_driver(cs53l32a_driver);
