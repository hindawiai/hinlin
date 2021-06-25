<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cyttsp_i2c.c
 * Cypress TrueTouch(TM) Standard Product (TTSP) I2C touchscreen driver.
 * For use with Cypress Txx3xx parts.
 * Supported parts include:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copyright (C) 2009, 2010, 2011 Cypress Semiconductor, Inc.
 * Copyright (C) 2012 Javier Martinez Canillas <javier@करोजबतक0.org>
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 */

#समावेश "cyttsp_core.h"

#समावेश <linux/i2c.h>
#समावेश <linux/input.h>

#घोषणा CY_I2C_DATA_SIZE	128

अटल स्थिर काष्ठा cyttsp_bus_ops cyttsp_i2c_bus_ops = अणु
	.bustype	= BUS_I2C,
	.ग_लिखो		= cyttsp_i2c_ग_लिखो_block_data,
	.पढ़ो           = cyttsp_i2c_पढ़ो_block_data,
पूर्ण;

अटल पूर्णांक cyttsp_i2c_probe(काष्ठा i2c_client *client,
				      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cyttsp *ts;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "I2C functionality not Supported\n");
		वापस -EIO;
	पूर्ण

	ts = cyttsp_probe(&cyttsp_i2c_bus_ops, &client->dev, client->irq,
			  CY_I2C_DATA_SIZE);

	अगर (IS_ERR(ts))
		वापस PTR_ERR(ts);

	i2c_set_clientdata(client, ts);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cyttsp_i2c_id[] = अणु
	अणु CY_I2C_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cyttsp_i2c_id);

अटल काष्ठा i2c_driver cyttsp_i2c_driver = अणु
	.driver = अणु
		.name	= CY_I2C_NAME,
		.pm	= &cyttsp_pm_ops,
	पूर्ण,
	.probe		= cyttsp_i2c_probe,
	.id_table	= cyttsp_i2c_id,
पूर्ण;

module_i2c_driver(cyttsp_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard Product (TTSP) I2C driver");
MODULE_AUTHOR("Cypress");
