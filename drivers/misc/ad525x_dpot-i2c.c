<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Analog Devices digital potentiometers (I2C bus)
 *
 * Copyright (C) 2010-2011 Michael Hennerich, Analog Devices Inc.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>

#समावेश "ad525x_dpot.h"

/* I2C bus functions */
अटल पूर्णांक ग_लिखो_d8(व्योम *client, u8 val)
अणु
	वापस i2c_smbus_ग_लिखो_byte(client, val);
पूर्ण

अटल पूर्णांक ग_लिखो_r8d8(व्योम *client, u8 reg, u8 val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक ग_लिखो_r8d16(व्योम *client, u8 reg, u16 val)
अणु
	वापस i2c_smbus_ग_लिखो_word_data(client, reg, val);
पूर्ण

अटल पूर्णांक पढ़ो_d8(व्योम *client)
अणु
	वापस i2c_smbus_पढ़ो_byte(client);
पूर्ण

अटल पूर्णांक पढ़ो_r8d8(व्योम *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक पढ़ो_r8d16(व्योम *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_data(client, reg);
पूर्ण

अटल स्थिर काष्ठा ad_dpot_bus_ops bops = अणु
	.पढ़ो_d8	= पढ़ो_d8,
	.पढ़ो_r8d8	= पढ़ो_r8d8,
	.पढ़ो_r8d16	= पढ़ो_r8d16,
	.ग_लिखो_d8	= ग_लिखो_d8,
	.ग_लिखो_r8d8	= ग_लिखो_r8d8,
	.ग_लिखो_r8d16	= ग_लिखो_r8d16,
पूर्ण;

अटल पूर्णांक ad_dpot_i2c_probe(काष्ठा i2c_client *client,
				      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ad_dpot_bus_data bdata = अणु
		.client = client,
		.bops = &bops,
	पूर्ण;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_err(&client->dev, "SMBUS Word Data not Supported\n");
		वापस -EIO;
	पूर्ण

	वापस ad_dpot_probe(&client->dev, &bdata, id->driver_data, id->name);
पूर्ण

अटल पूर्णांक ad_dpot_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस ad_dpot_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad_dpot_id[] = अणु
	अणु"ad5258", AD5258_IDपूर्ण,
	अणु"ad5259", AD5259_IDपूर्ण,
	अणु"ad5251", AD5251_IDपूर्ण,
	अणु"ad5252", AD5252_IDपूर्ण,
	अणु"ad5253", AD5253_IDपूर्ण,
	अणु"ad5254", AD5254_IDपूर्ण,
	अणु"ad5255", AD5255_IDपूर्ण,
	अणु"ad5241", AD5241_IDपूर्ण,
	अणु"ad5242", AD5242_IDपूर्ण,
	अणु"ad5243", AD5243_IDपूर्ण,
	अणु"ad5245", AD5245_IDपूर्ण,
	अणु"ad5246", AD5246_IDपूर्ण,
	अणु"ad5247", AD5247_IDपूर्ण,
	अणु"ad5248", AD5248_IDपूर्ण,
	अणु"ad5280", AD5280_IDपूर्ण,
	अणु"ad5282", AD5282_IDपूर्ण,
	अणु"adn2860", ADN2860_IDपूर्ण,
	अणु"ad5273", AD5273_IDपूर्ण,
	अणु"ad5161", AD5161_IDपूर्ण,
	अणु"ad5171", AD5171_IDपूर्ण,
	अणु"ad5170", AD5170_IDपूर्ण,
	अणु"ad5172", AD5172_IDपूर्ण,
	अणु"ad5173", AD5173_IDपूर्ण,
	अणु"ad5272", AD5272_IDपूर्ण,
	अणु"ad5274", AD5274_IDपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad_dpot_id);

अटल काष्ठा i2c_driver ad_dpot_i2c_driver = अणु
	.driver = अणु
		.name	= "ad_dpot",
	पूर्ण,
	.probe		= ad_dpot_i2c_probe,
	.हटाओ		= ad_dpot_i2c_हटाओ,
	.id_table	= ad_dpot_id,
पूर्ण;

module_i2c_driver(ad_dpot_i2c_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("digital potentiometer I2C bus driver");
MODULE_LICENSE("GPL");
