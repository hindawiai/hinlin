<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <linux/slab.h>

MODULE_DESCRIPTION("OmniVision ov7640 sensor driver");
MODULE_LICENSE("GPL v2");

अटल स्थिर u8 initial_रेजिस्टरs[] = अणु
	0x12, 0x80,
	0x12, 0x54,
	0x14, 0x24,
	0x15, 0x01,
	0x28, 0x20,
	0x75, 0x82,
	0xFF, 0xFF, /* Terminator (reg 0xFF is unused) */
पूर्ण;

अटल पूर्णांक ग_लिखो_regs(काष्ठा i2c_client *client, स्थिर u8 *regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; regs[i] != 0xFF; i += 2)
		अगर (i2c_smbus_ग_लिखो_byte_data(client, regs[i], regs[i + 1]) < 0)
			वापस -1;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_ops ov7640_ops;

अटल पूर्णांक ov7640_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा v4l2_subdev *sd;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	sd = devm_kzalloc(&client->dev, माप(*sd), GFP_KERNEL);
	अगर (sd == शून्य)
		वापस -ENOMEM;
	v4l2_i2c_subdev_init(sd, client, &ov7640_ops);

	client->flags = I2C_CLIENT_SCCB;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	अगर (ग_लिखो_regs(client, initial_रेजिस्टरs) < 0) अणु
		v4l_err(client, "error initializing OV7640\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक ov7640_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov7640_id[] = अणु
	अणु "ov7640", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov7640_id);

अटल काष्ठा i2c_driver ov7640_driver = अणु
	.driver = अणु
		.name	= "ov7640",
	पूर्ण,
	.probe = ov7640_probe,
	.हटाओ = ov7640_हटाओ,
	.id_table = ov7640_id,
पूर्ण;
module_i2c_driver(ov7640_driver);
