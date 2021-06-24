<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * I2C bus driver क्रम ADT7316/7/8 ADT7516/7/9 digital temperature
 * sensor, ADC and DAC
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>

#समावेश "adt7316.h"

/*
 * adt7316 रेजिस्टर access by I2C
 */
अटल पूर्णांक adt7316_i2c_पढ़ो(व्योम *client, u8 reg, u8 *data)
अणु
	काष्ठा i2c_client *cl = client;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(cl, reg);
	अगर (ret < 0) अणु
		dev_err(&cl->dev, "I2C fail to select reg\n");
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0) अणु
		dev_err(&cl->dev, "I2C read error\n");
		वापस ret;
	पूर्ण

	*data = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक adt7316_i2c_ग_लिखो(व्योम *client, u8 reg, u8 data)
अणु
	काष्ठा i2c_client *cl = client;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(cl, reg, data);
	अगर (ret < 0)
		dev_err(&cl->dev, "I2C write error\n");

	वापस ret;
पूर्ण

अटल पूर्णांक adt7316_i2c_multi_पढ़ो(व्योम *client, u8 reg, u8 count, u8 *data)
अणु
	काष्ठा i2c_client *cl = client;
	पूर्णांक i, ret;

	अगर (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	क्रम (i = 0; i < count; i++) अणु
		ret = adt7316_i2c_पढ़ो(cl, reg, &data[i]);
		अगर (ret < 0) अणु
			dev_err(&cl->dev, "I2C multi read error\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adt7316_i2c_multi_ग_लिखो(व्योम *client, u8 reg, u8 count, u8 *data)
अणु
	काष्ठा i2c_client *cl = client;
	पूर्णांक i, ret;

	अगर (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	क्रम (i = 0; i < count; i++) अणु
		ret = adt7316_i2c_ग_लिखो(cl, reg, data[i]);
		अगर (ret < 0) अणु
			dev_err(&cl->dev, "I2C multi write error\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * device probe and हटाओ
 */

अटल पूर्णांक adt7316_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adt7316_bus bus = अणु
		.client = client,
		.irq = client->irq,
		.पढ़ो = adt7316_i2c_पढ़ो,
		.ग_लिखो = adt7316_i2c_ग_लिखो,
		.multi_पढ़ो = adt7316_i2c_multi_पढ़ो,
		.multi_ग_लिखो = adt7316_i2c_multi_ग_लिखो,
	पूर्ण;

	वापस adt7316_probe(&client->dev, &bus, id->name);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adt7316_i2c_id[] = अणु
	अणु "adt7316", 0 पूर्ण,
	अणु "adt7317", 0 पूर्ण,
	अणु "adt7318", 0 पूर्ण,
	अणु "adt7516", 0 पूर्ण,
	अणु "adt7517", 0 पूर्ण,
	अणु "adt7519", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, adt7316_i2c_id);

अटल स्थिर काष्ठा of_device_id adt7316_of_match[] = अणु
	अणु .compatible = "adi,adt7316" पूर्ण,
	अणु .compatible = "adi,adt7317" पूर्ण,
	अणु .compatible = "adi,adt7318" पूर्ण,
	अणु .compatible = "adi,adt7516" पूर्ण,
	अणु .compatible = "adi,adt7517" पूर्ण,
	अणु .compatible = "adi,adt7519" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, adt7316_of_match);

अटल काष्ठा i2c_driver adt7316_driver = अणु
	.driver = अणु
		.name = "adt7316",
		.of_match_table = adt7316_of_match,
		.pm = ADT7316_PM_OPS,
	पूर्ण,
	.probe = adt7316_i2c_probe,
	.id_table = adt7316_i2c_id,
पूर्ण;
module_i2c_driver(adt7316_driver);

MODULE_AUTHOR("Sonic Zhang <sonic.zhang@analog.com>");
MODULE_DESCRIPTION("I2C bus driver for Analog Devices ADT7316/7/9 and ADT7516/7/8 digital temperature sensor, ADC and DAC");
MODULE_LICENSE("GPL v2");
