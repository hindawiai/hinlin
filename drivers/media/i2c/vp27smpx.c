<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vp27smpx - driver version 0.0.1
 *
 * Copyright (C) 2007 Hans Verkuil <hverkuil@xs4all.nl>
 *
 * Based on a tvaudio patch from Takahiro Adachi <tadachi@tadachi-net.com>
 * and Kazuhiko Kawakami <kazz-0@mail.goo.ne.jp>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>

MODULE_DESCRIPTION("vp27smpx driver");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL");


/* ----------------------------------------------------------------------- */

काष्ठा vp27smpx_state अणु
	काष्ठा v4l2_subdev sd;
	पूर्णांक radio;
	u32 audmode;
पूर्ण;

अटल अंतरभूत काष्ठा vp27smpx_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा vp27smpx_state, sd);
पूर्ण

अटल व्योम vp27smpx_set_audmode(काष्ठा v4l2_subdev *sd, u32 audmode)
अणु
	काष्ठा vp27smpx_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 data[3] = अणु 0x00, 0x00, 0x04 पूर्ण;

	चयन (audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
	हाल V4L2_TUNER_MODE_LANG1:
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		data[1] = 0x01;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		data[1] = 0x02;
		अवरोध;
	पूर्ण

	अगर (i2c_master_send(client, data, माप(data)) != माप(data))
		v4l2_err(sd, "I/O error setting audmode\n");
	अन्यथा
		state->audmode = audmode;
पूर्ण

अटल पूर्णांक vp27smpx_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा vp27smpx_state *state = to_state(sd);

	state->radio = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vp27smpx_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा vp27smpx_state *state = to_state(sd);

	state->radio = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vp27smpx_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा vp27smpx_state *state = to_state(sd);

	अगर (!state->radio)
		vp27smpx_set_audmode(sd, vt->audmode);
	वापस 0;
पूर्ण

अटल पूर्णांक vp27smpx_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा vp27smpx_state *state = to_state(sd);

	अगर (state->radio)
		वापस 0;
	vt->audmode = state->audmode;
	vt->capability = V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;
	vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	वापस 0;
पूर्ण

अटल पूर्णांक vp27smpx_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा vp27smpx_state *state = to_state(sd);

	v4l2_info(sd, "Audio Mode: %u%s\n", state->audmode,
			state->radio ? " (Radio)" : "");
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops vp27smpx_core_ops = अणु
	.log_status = vp27smpx_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops vp27smpx_tuner_ops = अणु
	.s_radio = vp27smpx_s_radio,
	.s_tuner = vp27smpx_s_tuner,
	.g_tuner = vp27smpx_g_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops vp27smpx_video_ops = अणु
	.s_std = vp27smpx_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops vp27smpx_ops = अणु
	.core = &vp27smpx_core_ops,
	.tuner = &vp27smpx_tuner_ops,
	.video = &vp27smpx_video_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

/* i2c implementation */

/*
 * Generic i2c probe
 * concerning the addresses: i2c wants 7 bit (without the r/w bit), so '>>1'
 */

अटल पूर्णांक vp27smpx_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vp27smpx_state *state;
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
	v4l2_i2c_subdev_init(sd, client, &vp27smpx_ops);
	state->audmode = V4L2_TUNER_MODE_STEREO;

	/* initialize vp27smpx */
	vp27smpx_set_audmode(sd, state->audmode);
	वापस 0;
पूर्ण

अटल पूर्णांक vp27smpx_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id vp27smpx_id[] = अणु
	अणु "vp27smpx", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vp27smpx_id);

अटल काष्ठा i2c_driver vp27smpx_driver = अणु
	.driver = अणु
		.name	= "vp27smpx",
	पूर्ण,
	.probe		= vp27smpx_probe,
	.हटाओ		= vp27smpx_हटाओ,
	.id_table	= vp27smpx_id,
पूर्ण;

module_i2c_driver(vp27smpx_driver);
