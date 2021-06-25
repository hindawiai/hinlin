<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Wolfram Sang, Pengutronix
 *
 * Check max730x.c क्रम further details.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/max7301.h>
#समावेश <linux/slab.h>

अटल पूर्णांक max7300_i2c_ग_लिखो(काष्ठा device *dev, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक max7300_i2c_पढ़ो(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक max7300_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max7301 *ts;

	अगर (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	ts = devm_kzalloc(&client->dev, माप(काष्ठा max7301), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->पढ़ो = max7300_i2c_पढ़ो;
	ts->ग_लिखो = max7300_i2c_ग_लिखो;
	ts->dev = &client->dev;

	वापस __max730x_probe(ts);
पूर्ण

अटल पूर्णांक max7300_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस __max730x_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max7300_id[] = अणु
	अणु "max7300", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max7300_id);

अटल काष्ठा i2c_driver max7300_driver = अणु
	.driver = अणु
		.name = "max7300",
	पूर्ण,
	.probe = max7300_probe,
	.हटाओ = max7300_हटाओ,
	.id_table = max7300_id,
पूर्ण;

अटल पूर्णांक __init max7300_init(व्योम)
अणु
	वापस i2c_add_driver(&max7300_driver);
पूर्ण
subsys_initcall(max7300_init);

अटल व्योम __निकास max7300_निकास(व्योम)
अणु
	i2c_del_driver(&max7300_driver);
पूर्ण
module_निकास(max7300_निकास);

MODULE_AUTHOR("Wolfram Sang");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MAX7300 GPIO-Expander");
