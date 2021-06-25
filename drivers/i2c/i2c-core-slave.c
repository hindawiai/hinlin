<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux I2C core slave support code
 *
 * Copyright (C) 2014 by Wolfram Sang <wsa@sang-engineering.com>
 */

#समावेश <dt-bindings/i2c/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>

#समावेश "i2c-core.h"

पूर्णांक i2c_slave_रेजिस्टर(काष्ठा i2c_client *client, i2c_slave_cb_t slave_cb)
अणु
	पूर्णांक ret;

	अगर (WARN(IS_ERR_OR_शून्य(client) || !slave_cb, "insufficient data\n"))
		वापस -EINVAL;

	अगर (!(client->flags & I2C_CLIENT_SLAVE))
		dev_warn(&client->dev, "%s: client slave flag not set. You might see address collisions\n",
			 __func__);

	अगर (!(client->flags & I2C_CLIENT_TEN)) अणु
		/* Enक्रमce stricter address checking */
		ret = i2c_check_7bit_addr_validity_strict(client->addr);
		अगर (ret) अणु
			dev_err(&client->dev, "%s: invalid address\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!client->adapter->algo->reg_slave) अणु
		dev_err(&client->dev, "%s: not supported by adapter\n", __func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	client->slave_cb = slave_cb;

	i2c_lock_bus(client->adapter, I2C_LOCK_ROOT_ADAPTER);
	ret = client->adapter->algo->reg_slave(client);
	i2c_unlock_bus(client->adapter, I2C_LOCK_ROOT_ADAPTER);

	अगर (ret) अणु
		client->slave_cb = शून्य;
		dev_err(&client->dev, "%s: adapter returned error %d\n", __func__, ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_slave_रेजिस्टर);

पूर्णांक i2c_slave_unरेजिस्टर(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(client))
		वापस -EINVAL;

	अगर (!client->adapter->algo->unreg_slave) अणु
		dev_err(&client->dev, "%s: not supported by adapter\n", __func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	i2c_lock_bus(client->adapter, I2C_LOCK_ROOT_ADAPTER);
	ret = client->adapter->algo->unreg_slave(client);
	i2c_unlock_bus(client->adapter, I2C_LOCK_ROOT_ADAPTER);

	अगर (ret == 0)
		client->slave_cb = शून्य;
	अन्यथा
		dev_err(&client->dev, "%s: adapter returned error %d\n", __func__, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_slave_unरेजिस्टर);

/**
 * i2c_detect_slave_mode - detect operation mode
 * @dev: The device owning the bus
 *
 * This checks the device nodes क्रम an I2C slave by checking the address
 * used in the reg property. If the address match the I2C_OWN_SLAVE_ADDRESS
 * flag this means the device is configured to act as a I2C slave and it will
 * be listening at that address.
 *
 * Returns true अगर an I2C own slave address is detected, otherwise वापसs
 * false.
 */
bool i2c_detect_slave_mode(काष्ठा device *dev)
अणु
	अगर (IS_BUILTIN(CONFIG_OF) && dev->of_node) अणु
		काष्ठा device_node *child;
		u32 reg;

		क्रम_each_child_of_node(dev->of_node, child) अणु
			of_property_पढ़ो_u32(child, "reg", &reg);
			अगर (reg & I2C_OWN_SLAVE_ADDRESS) अणु
				of_node_put(child);
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (IS_BUILTIN(CONFIG_ACPI) && ACPI_HANDLE(dev)) अणु
		dev_dbg(dev, "ACPI slave is not supported yet\n");
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_detect_slave_mode);
