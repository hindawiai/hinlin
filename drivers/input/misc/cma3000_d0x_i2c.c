<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implements I2C पूर्णांकerface क्रम VTI CMA300_D0x Accelerometer driver
 *
 * Copyright (C) 2010 Texas Instruments
 * Author: Hemanth V <hemanthv@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input/cma3000.h>
#समावेश "cma3000_d0x.h"

अटल पूर्णांक cma3000_i2c_set(काष्ठा device *dev,
			   u8 reg, u8 val, अक्षर *msg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
	अगर (ret < 0)
		dev_err(&client->dev,
			"%s failed (%s, %d)\n", __func__, msg, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cma3000_i2c_पढ़ो(काष्ठा device *dev, u8 reg, अक्षर *msg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0)
		dev_err(&client->dev,
			"%s failed (%s, %d)\n", __func__, msg, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा cma3000_bus_ops cma3000_i2c_bops = अणु
	.bustype	= BUS_I2C,
#घोषणा CMA3000_BUSI2C     (0 << 4)
	.ctrl_mod	= CMA3000_BUSI2C,
	.पढ़ो		= cma3000_i2c_पढ़ो,
	.ग_लिखो		= cma3000_i2c_set,
पूर्ण;

अटल पूर्णांक cma3000_i2c_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cma3000_accl_data *data;

	data = cma3000_init(&client->dev, client->irq, &cma3000_i2c_bops);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	i2c_set_clientdata(client, data);

	वापस 0;
पूर्ण

अटल पूर्णांक cma3000_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cma3000_accl_data *data = i2c_get_clientdata(client);

	cma3000_निकास(data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cma3000_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cma3000_accl_data *data = i2c_get_clientdata(client);

	cma3000_suspend(data);

	वापस 0;
पूर्ण

अटल पूर्णांक cma3000_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cma3000_accl_data *data = i2c_get_clientdata(client);

	cma3000_resume(data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cma3000_i2c_pm_ops = अणु
	.suspend	= cma3000_i2c_suspend,
	.resume		= cma3000_i2c_resume,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id cma3000_i2c_id[] = अणु
	अणु "cma3000_d01", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cma3000_i2c_id);

अटल काष्ठा i2c_driver cma3000_i2c_driver = अणु
	.probe		= cma3000_i2c_probe,
	.हटाओ		= cma3000_i2c_हटाओ,
	.id_table	= cma3000_i2c_id,
	.driver = अणु
		.name	= "cma3000_i2c_accl",
#अगर_घोषित CONFIG_PM
		.pm	= &cma3000_i2c_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_i2c_driver(cma3000_i2c_driver);

MODULE_DESCRIPTION("CMA3000-D0x Accelerometer I2C Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hemanth V <hemanthv@ti.com>");
