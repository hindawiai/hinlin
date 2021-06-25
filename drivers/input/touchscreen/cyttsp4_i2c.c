<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cyttsp_i2c.c
 * Cypress TrueTouch(TM) Standard Product (TTSP) I2C touchscreen driver.
 * For use with Cypress  Txx4xx parts.
 * Supported parts include:
 * TMA4XX
 * TMA1036
 *
 * Copyright (C) 2009, 2010, 2011 Cypress Semiconductor, Inc.
 * Copyright (C) 2012 Javier Martinez Canillas <javier@करोजबतक0.org>
 * Copyright (C) 2013 Cypress Semiconductor
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 */

#समावेश "cyttsp4_core.h"

#समावेश <linux/i2c.h>
#समावेश <linux/input.h>

#घोषणा CYTTSP4_I2C_DATA_SIZE	(3 * 256)

अटल स्थिर काष्ठा cyttsp4_bus_ops cyttsp4_i2c_bus_ops = अणु
	.bustype	= BUS_I2C,
	.ग_लिखो		= cyttsp_i2c_ग_लिखो_block_data,
	.पढ़ो           = cyttsp_i2c_पढ़ो_block_data,
पूर्ण;

अटल पूर्णांक cyttsp4_i2c_probe(काष्ठा i2c_client *client,
				      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cyttsp4 *ts;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "I2C functionality not Supported\n");
		वापस -EIO;
	पूर्ण

	ts = cyttsp4_probe(&cyttsp4_i2c_bus_ops, &client->dev, client->irq,
			  CYTTSP4_I2C_DATA_SIZE);

	वापस PTR_ERR_OR_ZERO(ts);
पूर्ण

अटल पूर्णांक cyttsp4_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cyttsp4 *ts = i2c_get_clientdata(client);

	cyttsp4_हटाओ(ts);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cyttsp4_i2c_id[] = अणु
	अणु CYTTSP4_I2C_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cyttsp4_i2c_id);

अटल काष्ठा i2c_driver cyttsp4_i2c_driver = अणु
	.driver = अणु
		.name	= CYTTSP4_I2C_NAME,
		.pm	= &cyttsp4_pm_ops,
	पूर्ण,
	.probe		= cyttsp4_i2c_probe,
	.हटाओ		= cyttsp4_i2c_हटाओ,
	.id_table	= cyttsp4_i2c_id,
पूर्ण;

module_i2c_driver(cyttsp4_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard Product (TTSP) I2C driver");
MODULE_AUTHOR("Cypress");
