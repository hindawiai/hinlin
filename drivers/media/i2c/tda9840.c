<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /*
    tda9840 - i2c-driver क्रम the tda9840 by SGS Thomson

    Copyright (C) 1998-2003 Michael Hunold <michael@mihu.de>
    Copyright (C) 2008 Hans Verkuil <hverkuil@xs4all.nl>

    The tda9840 is a stereo/dual sound processor with digital
    identअगरication. It can be found at address 0x84 on the i2c-bus.

    For detailed inक्रमmation करोwnload the specअगरications directly
    from SGS Thomson at http://www.st.com

  */


#समावेश <linux/module.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-device.h>

MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_DESCRIPTION("tda9840 driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(debug, "Debug level (0-1)");

#घोषणा	SWITCH		0x00
#घोषणा	LEVEL_ADJUST	0x02
#घोषणा	STEREO_ADJUST	0x03
#घोषणा	TEST		0x04

#घोषणा TDA9840_SET_MUTE                0x00
#घोषणा TDA9840_SET_MONO                0x10
#घोषणा TDA9840_SET_STEREO              0x2a
#घोषणा TDA9840_SET_LANG1               0x12
#घोषणा TDA9840_SET_LANG2               0x1e
#घोषणा TDA9840_SET_BOTH                0x1a
#घोषणा TDA9840_SET_BOTH_R              0x16
#घोषणा TDA9840_SET_EXTERNAL            0x7a


अटल व्योम tda9840_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (i2c_smbus_ग_लिखो_byte_data(client, reg, val))
		v4l2_dbg(1, debug, sd, "error writing %02x to %02x\n",
				val, reg);
पूर्ण

अटल पूर्णांक tda9840_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक rc;
	u8 byte;

	rc = i2c_master_recv(client, &byte, 1);
	अगर (rc != 1) अणु
		v4l2_dbg(1, debug, sd,
			"i2c_master_recv() failed\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण

	अगर (byte & 0x80) अणु
		v4l2_dbg(1, debug, sd,
			"TDA9840_DETECT: register contents invalid\n");
		वापस -EINVAL;
	पूर्ण

	v4l2_dbg(1, debug, sd, "TDA9840_DETECT: byte: 0x%02x\n", byte);
	वापस byte & 0x60;
पूर्ण

अटल पूर्णांक tda9840_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *t)
अणु
	पूर्णांक stat = tda9840_status(sd);
	पूर्णांक byte;

	अगर (t->index)
		वापस -EINVAL;

	stat = stat < 0 ? 0 : stat;
	अगर (stat == 0 || stat == 0x60) /* mono input */
		byte = TDA9840_SET_MONO;
	अन्यथा अगर (stat == 0x40) /* stereo input */
		byte = (t->audmode == V4L2_TUNER_MODE_MONO) ?
			TDA9840_SET_MONO : TDA9840_SET_STEREO;
	अन्यथा अणु /* bilingual */
		चयन (t->audmode) अणु
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			byte = TDA9840_SET_BOTH;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			byte = TDA9840_SET_LANG2;
			अवरोध;
		शेष:
			byte = TDA9840_SET_LANG1;
			अवरोध;
		पूर्ण
	पूर्ण
	v4l2_dbg(1, debug, sd, "TDA9840_SWITCH: 0x%02x\n", byte);
	tda9840_ग_लिखो(sd, SWITCH, byte);
	वापस 0;
पूर्ण

अटल पूर्णांक tda9840_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *t)
अणु
	पूर्णांक stat = tda9840_status(sd);

	अगर (stat < 0)
		वापस stat;

	t->rxsubchans = V4L2_TUNER_SUB_MONO;

	चयन (stat & 0x60) अणु
	हाल 0x00:
		t->rxsubchans = V4L2_TUNER_SUB_MONO;
		अवरोध;
	हाल 0x20:
		t->rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
		अवरोध;
	हाल 0x40:
		t->rxsubchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_MONO;
		अवरोध;
	शेष: /* Incorrect detect */
		t->rxsubchans = V4L2_TUNER_MODE_MONO;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops tda9840_tuner_ops = अणु
	.s_tuner = tda9840_s_tuner,
	.g_tuner = tda9840_g_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tda9840_ops = अणु
	.tuner = &tda9840_tuner_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक tda9840_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा v4l2_subdev *sd;

	/* let's see whether this adapter can support what we need */
	अगर (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_READ_BYTE_DATA |
			I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	sd = devm_kzalloc(&client->dev, माप(*sd), GFP_KERNEL);
	अगर (sd == शून्य)
		वापस -ENOMEM;
	v4l2_i2c_subdev_init(sd, client, &tda9840_ops);

	/* set initial values क्रम level & stereo - adjusपंचांगent, mode */
	tda9840_ग_लिखो(sd, LEVEL_ADJUST, 0);
	tda9840_ग_लिखो(sd, STEREO_ADJUST, 0);
	tda9840_ग_लिखो(sd, SWITCH, TDA9840_SET_STEREO);
	वापस 0;
पूर्ण

अटल पूर्णांक tda9840_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tda9840_id[] = अणु
	अणु "tda9840", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda9840_id);

अटल काष्ठा i2c_driver tda9840_driver = अणु
	.driver = अणु
		.name	= "tda9840",
	पूर्ण,
	.probe		= tda9840_probe,
	.हटाओ		= tda9840_हटाओ,
	.id_table	= tda9840_id,
पूर्ण;

module_i2c_driver(tda9840_driver);
