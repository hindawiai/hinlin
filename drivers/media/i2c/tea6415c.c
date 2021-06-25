<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /*
    tea6415c - i2c-driver क्रम the tea6415c by SGS Thomson

    Copyright (C) 1998-2003 Michael Hunold <michael@mihu.de>
    Copyright (C) 2008 Hans Verkuil <hverkuil@xs4all.nl>

    The tea6415c is a bus controlled video-matrix-चयन
    with 8 inमाला_दो and 6 outमाला_दो.
    It is cascadable, i.e. it can be found at the addresses
    0x86 and 0x06 on the i2c-bus.

    For detailed inक्रमmation करोwnload the specअगरications directly
    from SGS Thomson at http://www.st.com

  */


#समावेश <linux/module.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-device.h>
#समावेश "tea6415c.h"

MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_DESCRIPTION("tea6415c driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(debug, "Debug level (0-1)");


/* makes a connection between the input-pin 'i' and the output-pin 'o' */
अटल पूर्णांक tea6415c_s_routing(काष्ठा v4l2_subdev *sd,
			      u32 i, u32 o, u32 config)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 byte = 0;
	पूर्णांक ret;

	v4l2_dbg(1, debug, sd, "i=%d, o=%d\n", i, o);

	/* check अगर the pins are valid */
	अगर (0 == ((1 == i ||  3 == i ||  5 == i ||  6 == i ||  8 == i || 10 == i || 20 == i || 11 == i)
	      && (18 == o || 17 == o || 16 == o || 15 == o || 14 == o || 13 == o)))
		वापस -EINVAL;

	/* to understand this, have a look at the tea6415c-specs (p.5) */
	चयन (o) अणु
	हाल 18:
		byte = 0x00;
		अवरोध;
	हाल 14:
		byte = 0x20;
		अवरोध;
	हाल 16:
		byte = 0x10;
		अवरोध;
	हाल 17:
		byte = 0x08;
		अवरोध;
	हाल 15:
		byte = 0x18;
		अवरोध;
	हाल 13:
		byte = 0x28;
		अवरोध;
	पूर्ण

	चयन (i) अणु
	हाल 5:
		byte |= 0x00;
		अवरोध;
	हाल 8:
		byte |= 0x04;
		अवरोध;
	हाल 3:
		byte |= 0x02;
		अवरोध;
	हाल 20:
		byte |= 0x06;
		अवरोध;
	हाल 6:
		byte |= 0x01;
		अवरोध;
	हाल 10:
		byte |= 0x05;
		अवरोध;
	हाल 1:
		byte |= 0x03;
		अवरोध;
	हाल 11:
		byte |= 0x07;
		अवरोध;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte(client, byte);
	अगर (ret) अणु
		v4l2_dbg(1, debug, sd,
			"i2c_smbus_write_byte() failed, ret:%d\n", ret);
		वापस -EIO;
	पूर्ण
	वापस ret;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_video_ops tea6415c_video_ops = अणु
	.s_routing = tea6415c_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tea6415c_ops = अणु
	.video = &tea6415c_video_ops,
पूर्ण;

अटल पूर्णांक tea6415c_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा v4l2_subdev *sd;

	/* let's see whether this adapter can support what we need */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);
	sd = devm_kzalloc(&client->dev, माप(*sd), GFP_KERNEL);
	अगर (sd == शून्य)
		वापस -ENOMEM;
	v4l2_i2c_subdev_init(sd, client, &tea6415c_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक tea6415c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tea6415c_id[] = अणु
	अणु "tea6415c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tea6415c_id);

अटल काष्ठा i2c_driver tea6415c_driver = अणु
	.driver = अणु
		.name	= "tea6415c",
	पूर्ण,
	.probe		= tea6415c_probe,
	.हटाओ		= tea6415c_हटाओ,
	.id_table	= tea6415c_id,
पूर्ण;

module_i2c_driver(tea6415c_driver);
