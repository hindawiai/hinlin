<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Freescale MPL115A2 pressure/temperature sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * (7-bit I2C slave address 0x60)
 *
 * Datasheet: http://www.nxp.com/files/sensors/करोc/data_sheet/MPL115A2.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>

#समावेश "mpl115.h"

अटल पूर्णांक mpl115_i2c_init(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mpl115_i2c_पढ़ो(काष्ठा device *dev, u8 address)
अणु
	वापस i2c_smbus_पढ़ो_word_swapped(to_i2c_client(dev), address);
पूर्ण

अटल पूर्णांक mpl115_i2c_ग_लिखो(काष्ठा device *dev, u8 address, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(to_i2c_client(dev), address, value);
पूर्ण

अटल स्थिर काष्ठा mpl115_ops mpl115_i2c_ops = अणु
	.init = mpl115_i2c_init,
	.पढ़ो = mpl115_i2c_पढ़ो,
	.ग_लिखो = mpl115_i2c_ग_लिखो,
पूर्ण;

अटल पूर्णांक mpl115_i2c_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EOPNOTSUPP;

	वापस mpl115_probe(&client->dev, id->name, &mpl115_i2c_ops);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mpl115_i2c_id[] = अणु
	अणु "mpl115", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mpl115_i2c_id);

अटल काष्ठा i2c_driver mpl115_i2c_driver = अणु
	.driver = अणु
		.name	= "mpl115",
	पूर्ण,
	.probe = mpl115_i2c_probe,
	.id_table = mpl115_i2c_id,
पूर्ण;
module_i2c_driver(mpl115_i2c_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Freescale MPL115A2 pressure/temperature driver");
MODULE_LICENSE("GPL");
