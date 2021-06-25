<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /*
    tea6420 - i2c-driver क्रम the tea6420 by SGS Thomson

    Copyright (C) 1998-2003 Michael Hunold <michael@mihu.de>
    Copyright (C) 2008 Hans Verkuil <hverkuil@xs4all.nl>

    The tea6420 is a bus controlled audio-matrix with 5 stereo inमाला_दो,
    4 stereo outमाला_दो and gain control क्रम each output.
    It is cascadable, i.e. it can be found at the addresses 0x98
    and 0x9a on the i2c-bus.

    For detailed inक्रमmation करोwnload the specअगरications directly
    from SGS Thomson at http://www.st.com

  */


#समावेश <linux/module.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-device.h>
#समावेश "tea6420.h"

MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_DESCRIPTION("tea6420 driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(debug, "Debug level (0-1)");


/* make a connection between the input 'i' and the output 'o'
   with gain 'g' (note: i = 6 means 'mute') */
अटल पूर्णांक tea6420_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 i, u32 o, u32 config)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक g = (o >> 4) & 0xf;
	u8 byte;
	पूर्णांक ret;

	o &= 0xf;
	v4l2_dbg(1, debug, sd, "i=%d, o=%d, g=%d\n", i, o, g);

	/* check अगर the parameters are valid */
	अगर (i < 1 || i > 6 || o < 1 || o > 4 || g < 0 || g > 6 || g % 2 != 0)
		वापस -EINVAL;

	byte = ((o - 1) << 5);
	byte |= (i - 1);

	/* to understand this, have a look at the tea6420-specs (p.5) */
	चयन (g) अणु
	हाल 0:
		byte |= (3 << 3);
		अवरोध;
	हाल 2:
		byte |= (2 << 3);
		अवरोध;
	हाल 4:
		byte |= (1 << 3);
		अवरोध;
	हाल 6:
		अवरोध;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte(client, byte);
	अगर (ret) अणु
		v4l2_dbg(1, debug, sd,
			"i2c_smbus_write_byte() failed, ret:%d\n", ret);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_audio_ops tea6420_audio_ops = अणु
	.s_routing = tea6420_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tea6420_ops = अणु
	.audio = &tea6420_audio_ops,
पूर्ण;

अटल पूर्णांक tea6420_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा v4l2_subdev *sd;
	पूर्णांक err, i;

	/* let's see whether this adapter can support what we need */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	sd = devm_kzalloc(&client->dev, माप(*sd), GFP_KERNEL);
	अगर (sd == शून्य)
		वापस -ENOMEM;
	v4l2_i2c_subdev_init(sd, client, &tea6420_ops);

	/* set initial values: set "mute"-input to all outमाला_दो at gain 0 */
	err = 0;
	क्रम (i = 1; i < 5; i++)
		err += tea6420_s_routing(sd, 6, i, 0);
	अगर (err) अणु
		v4l_dbg(1, debug, client, "could not initialize tea6420\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tea6420_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tea6420_id[] = अणु
	अणु "tea6420", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tea6420_id);

अटल काष्ठा i2c_driver tea6420_driver = अणु
	.driver = अणु
		.name	= "tea6420",
	पूर्ण,
	.probe		= tea6420_probe,
	.हटाओ		= tea6420_हटाओ,
	.id_table	= tea6420_id,
पूर्ण;

module_i2c_driver(tea6420_driver);
