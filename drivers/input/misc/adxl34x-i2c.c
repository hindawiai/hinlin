<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADLX345/346 Three-Axis Digital Accelerometers (I2C Interface)
 *
 * Enter bugs at http://blackfin.uclinux.org/
 *
 * Copyright (C) 2009 Michael Hennerich, Analog Devices Inc.
 */

#समावेश <linux/input.h>	/* BUS_I2C */
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>
#समावेश <linux/pm.h>
#समावेश "adxl34x.h"

अटल पूर्णांक adxl34x_smbus_पढ़ो(काष्ठा device *dev, अचिन्हित अक्षर reg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक adxl34x_smbus_ग_लिखो(काष्ठा device *dev,
			       अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक adxl34x_smbus_पढ़ो_block(काष्ठा device *dev,
				    अचिन्हित अक्षर reg, पूर्णांक count,
				    व्योम *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस i2c_smbus_पढ़ो_i2c_block_data(client, reg, count, buf);
पूर्ण

अटल पूर्णांक adxl34x_i2c_पढ़ो_block(काष्ठा device *dev,
				  अचिन्हित अक्षर reg, पूर्णांक count,
				  व्योम *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	ret = i2c_master_send(client, &reg, 1);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_master_recv(client, buf, count);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != count)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा adxl34x_bus_ops adxl34x_smbus_bops = अणु
	.bustype	= BUS_I2C,
	.ग_लिखो		= adxl34x_smbus_ग_लिखो,
	.पढ़ो		= adxl34x_smbus_पढ़ो,
	.पढ़ो_block	= adxl34x_smbus_पढ़ो_block,
पूर्ण;

अटल स्थिर काष्ठा adxl34x_bus_ops adxl34x_i2c_bops = अणु
	.bustype	= BUS_I2C,
	.ग_लिखो		= adxl34x_smbus_ग_लिखो,
	.पढ़ो		= adxl34x_smbus_पढ़ो,
	.पढ़ो_block	= adxl34x_i2c_पढ़ो_block,
पूर्ण;

अटल पूर्णांक adxl34x_i2c_probe(काष्ठा i2c_client *client,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adxl34x *ac;
	पूर्णांक error;

	error = i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA);
	अगर (!error) अणु
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		वापस -EIO;
	पूर्ण

	ac = adxl34x_probe(&client->dev, client->irq, false,
			   i2c_check_functionality(client->adapter,
						   I2C_FUNC_SMBUS_READ_I2C_BLOCK) ?
				&adxl34x_smbus_bops : &adxl34x_i2c_bops);
	अगर (IS_ERR(ac))
		वापस PTR_ERR(ac);

	i2c_set_clientdata(client, ac);

	वापस 0;
पूर्ण

अटल पूर्णांक adxl34x_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adxl34x *ac = i2c_get_clientdata(client);

	वापस adxl34x_हटाओ(ac);
पूर्ण

अटल पूर्णांक __maybe_unused adxl34x_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा adxl34x *ac = i2c_get_clientdata(client);

	adxl34x_suspend(ac);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused adxl34x_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा adxl34x *ac = i2c_get_clientdata(client);

	adxl34x_resume(ac);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(adxl34x_i2c_pm, adxl34x_i2c_suspend,
			 adxl34x_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id adxl34x_id[] = अणु
	अणु "adxl34x", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, adxl34x_id);

अटल स्थिर काष्ठा of_device_id adxl34x_of_id[] = अणु
	/*
	 * The ADXL346 is backward-compatible with the ADXL345. Dअगरferences are
	 * handled by runसमय detection of the device model, there's thus no
	 * need क्रम listing the "adi,adxl346" compatible value explicitly.
	 */
	अणु .compatible = "adi,adxl345", पूर्ण,
	/*
	 * Deprecated, DT nodes should use one or more of the device-specअगरic
	 * compatible values "adi,adxl345" and "adi,adxl346".
	 */
	अणु .compatible = "adi,adxl34x", पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, adxl34x_of_id);

अटल काष्ठा i2c_driver adxl34x_driver = अणु
	.driver = अणु
		.name = "adxl34x",
		.pm = &adxl34x_i2c_pm,
		.of_match_table = adxl34x_of_id,
	पूर्ण,
	.probe    = adxl34x_i2c_probe,
	.हटाओ   = adxl34x_i2c_हटाओ,
	.id_table = adxl34x_id,
पूर्ण;

module_i2c_driver(adxl34x_driver);

MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("ADXL345/346 Three-Axis Digital Accelerometer I2C Bus Driver");
MODULE_LICENSE("GPL");
