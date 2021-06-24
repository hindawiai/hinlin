<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cyttsp_i2c_common.c
 * Cypress TrueTouch(TM) Standard Product (TTSP) I2C touchscreen driver.
 * For use with Cypress Txx3xx and Txx4xx parts.
 * Supported parts include:
 * CY8CTST341
 * CY8CTMA340
 * TMA4XX
 * TMA1036
 *
 * Copyright (C) 2009, 2010, 2011 Cypress Semiconductor, Inc.
 * Copyright (C) 2012 Javier Martinez Canillas <javier@करोजबतक0.org>
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश "cyttsp4_core.h"

पूर्णांक cyttsp_i2c_पढ़ो_block_data(काष्ठा device *dev, u8 *xfer_buf,
				      u16 addr, u8 length, व्योम *values)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 client_addr = client->addr | ((addr >> 8) & 0x1);
	u8 addr_lo = addr & 0xFF;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client_addr,
			.flags = 0,
			.len = 1,
			.buf = &addr_lo,
		पूर्ण,
		अणु
			.addr = client_addr,
			.flags = I2C_M_RD,
			.len = length,
			.buf = values,
		पूर्ण,
	पूर्ण;
	पूर्णांक retval;

	retval = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (retval < 0)
		वापस retval;

	वापस retval != ARRAY_SIZE(msgs) ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(cyttsp_i2c_पढ़ो_block_data);

पूर्णांक cyttsp_i2c_ग_लिखो_block_data(काष्ठा device *dev, u8 *xfer_buf,
				       u16 addr, u8 length, स्थिर व्योम *values)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 client_addr = client->addr | ((addr >> 8) & 0x1);
	u8 addr_lo = addr & 0xFF;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client_addr,
			.flags = 0,
			.len = length + 1,
			.buf = xfer_buf,
		पूर्ण,
	पूर्ण;
	पूर्णांक retval;

	xfer_buf[0] = addr_lo;
	स_नकल(&xfer_buf[1], values, length);

	retval = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (retval < 0)
		वापस retval;

	वापस retval != ARRAY_SIZE(msgs) ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(cyttsp_i2c_ग_लिखो_block_data);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cypress");
