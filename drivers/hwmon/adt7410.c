<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADT7410/ADT7420 digital temperature sensor driver
 *
 * Copyright 2012-2013 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>

#समावेश "adt7x10.h"

अटल पूर्णांक adt7410_i2c_पढ़ो_word(काष्ठा device *dev, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_swapped(to_i2c_client(dev), reg);
पूर्ण

अटल पूर्णांक adt7410_i2c_ग_लिखो_word(काष्ठा device *dev, u8 reg, u16 data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(to_i2c_client(dev), reg, data);
पूर्ण

अटल पूर्णांक adt7410_i2c_पढ़ो_byte(काष्ठा device *dev, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(to_i2c_client(dev), reg);
पूर्ण

अटल पूर्णांक adt7410_i2c_ग_लिखो_byte(काष्ठा device *dev, u8 reg, u8 data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(to_i2c_client(dev), reg, data);
पूर्ण

अटल स्थिर काष्ठा adt7x10_ops adt7410_i2c_ops = अणु
	.पढ़ो_word = adt7410_i2c_पढ़ो_word,
	.ग_लिखो_word = adt7410_i2c_ग_लिखो_word,
	.पढ़ो_byte = adt7410_i2c_पढ़ो_byte,
	.ग_लिखो_byte = adt7410_i2c_ग_लिखो_byte,
पूर्ण;

अटल पूर्णांक adt7410_i2c_probe(काष्ठा i2c_client *client)
अणु
	अगर (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	वापस adt7x10_probe(&client->dev, शून्य, client->irq, &adt7410_i2c_ops);
पूर्ण

अटल पूर्णांक adt7410_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस adt7x10_हटाओ(&client->dev, client->irq);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adt7410_ids[] = अणु
	अणु "adt7410", 0 पूर्ण,
	अणु "adt7420", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adt7410_ids);

अटल काष्ठा i2c_driver adt7410_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adt7410",
		.pm	= ADT7X10_DEV_PM_OPS,
	पूर्ण,
	.probe_new	= adt7410_i2c_probe,
	.हटाओ		= adt7410_i2c_हटाओ,
	.id_table	= adt7410_ids,
	.address_list	= I2C_ADDRS(0x48, 0x49, 0x4a, 0x4b),
पूर्ण;
module_i2c_driver(adt7410_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("ADT7410/AD7420 driver");
MODULE_LICENSE("GPL");
