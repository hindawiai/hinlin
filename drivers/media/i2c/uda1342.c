<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/i2c/uda1342.h>
#समावेश <linux/slab.h>

अटल पूर्णांक ग_लिखो_reg(काष्ठा i2c_client *client, पूर्णांक reg, पूर्णांक value)
अणु
	/* UDA1342 wants MSB first, but SMBus sends LSB first */
	i2c_smbus_ग_लिखो_word_data(client, reg, swab16(value));
	वापस 0;
पूर्ण

अटल पूर्णांक uda1342_s_routing(काष्ठा v4l2_subdev *sd,
		u32 input, u32 output, u32 config)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	चयन (input) अणु
	हाल UDA1342_IN1:
		ग_लिखो_reg(client, 0x00, 0x1241); /* select input 1 */
		अवरोध;
	हाल UDA1342_IN2:
		ग_लिखो_reg(client, 0x00, 0x1441); /* select input 2 */
		अवरोध;
	शेष:
		v4l2_err(sd, "input %d not supported\n", input);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_audio_ops uda1342_audio_ops = अणु
	.s_routing = uda1342_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops uda1342_ops = अणु
	.audio = &uda1342_audio_ops,
पूर्ण;

अटल पूर्णांक uda1342_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा v4l2_subdev *sd;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	dev_dbg(&client->dev, "initializing UDA1342 at address %d on %s\n",
		client->addr, adapter->name);

	sd = devm_kzalloc(&client->dev, माप(*sd), GFP_KERNEL);
	अगर (sd == शून्य)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(sd, client, &uda1342_ops);

	ग_लिखो_reg(client, 0x00, 0x8000); /* reset रेजिस्टरs */
	ग_लिखो_reg(client, 0x00, 0x1241); /* select input 1 */

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	वापस 0;
पूर्ण

अटल पूर्णांक uda1342_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id uda1342_id[] = अणु
	अणु "uda1342", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, uda1342_id);

अटल काष्ठा i2c_driver uda1342_driver = अणु
	.driver = अणु
		.name	= "uda1342",
	पूर्ण,
	.probe		= uda1342_probe,
	.हटाओ		= uda1342_हटाओ,
	.id_table	= uda1342_id,
पूर्ण;

module_i2c_driver(uda1342_driver);

MODULE_LICENSE("GPL v2");
