<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux I2C core OF support code
 *
 * Copyright (C) 2008 Jochen Friedrich <jochen@scram.de>
 * based on a previous patch from Jon Smirl <jonsmirl@gmail.com>
 *
 * Copyright (C) 2013, 2018 Wolfram Sang <wsa@kernel.org>
 */

#समावेश <dt-bindings/i2c/i2c.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sysfs.h>

#समावेश "i2c-core.h"

पूर्णांक of_i2c_get_board_info(काष्ठा device *dev, काष्ठा device_node *node,
			  काष्ठा i2c_board_info *info)
अणु
	u32 addr;
	पूर्णांक ret;

	स_रखो(info, 0, माप(*info));

	अगर (of_modalias_node(node, info->type, माप(info->type)) < 0) अणु
		dev_err(dev, "of_i2c: modalias failure on %pOF\n", node);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "reg", &addr);
	अगर (ret) अणु
		dev_err(dev, "of_i2c: invalid reg on %pOF\n", node);
		वापस ret;
	पूर्ण

	अगर (addr & I2C_TEN_BIT_ADDRESS) अणु
		addr &= ~I2C_TEN_BIT_ADDRESS;
		info->flags |= I2C_CLIENT_TEN;
	पूर्ण

	अगर (addr & I2C_OWN_SLAVE_ADDRESS) अणु
		addr &= ~I2C_OWN_SLAVE_ADDRESS;
		info->flags |= I2C_CLIENT_SLAVE;
	पूर्ण

	info->addr = addr;
	info->of_node = node;
	info->fwnode = of_fwnode_handle(node);

	अगर (of_property_पढ़ो_bool(node, "host-notify"))
		info->flags |= I2C_CLIENT_HOST_NOTIFY;

	अगर (of_get_property(node, "wakeup-source", शून्य))
		info->flags |= I2C_CLIENT_WAKE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_i2c_get_board_info);

अटल काष्ठा i2c_client *of_i2c_रेजिस्टर_device(काष्ठा i2c_adapter *adap,
						 काष्ठा device_node *node)
अणु
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info info;
	पूर्णांक ret;

	dev_dbg(&adap->dev, "of_i2c: register %pOF\n", node);

	ret = of_i2c_get_board_info(&adap->dev, node, &info);
	अगर (ret)
		वापस ERR_PTR(ret);

	client = i2c_new_client_device(adap, &info);
	अगर (IS_ERR(client))
		dev_err(&adap->dev, "of_i2c: Failure registering %pOF\n", node);

	वापस client;
पूर्ण

व्योम of_i2c_रेजिस्टर_devices(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा device_node *bus, *node;
	काष्ठा i2c_client *client;

	/* Only रेजिस्टर child devices अगर the adapter has a node poपूर्णांकer set */
	अगर (!adap->dev.of_node)
		वापस;

	dev_dbg(&adap->dev, "of_i2c: walking child nodes\n");

	bus = of_get_child_by_name(adap->dev.of_node, "i2c-bus");
	अगर (!bus)
		bus = of_node_get(adap->dev.of_node);

	क्रम_each_available_child_of_node(bus, node) अणु
		अगर (of_node_test_and_set_flag(node, OF_POPULATED))
			जारी;

		client = of_i2c_रेजिस्टर_device(adap, node);
		अगर (IS_ERR(client)) अणु
			dev_err(&adap->dev,
				 "Failed to create I2C device for %pOF\n",
				 node);
			of_node_clear_flag(node, OF_POPULATED);
		पूर्ण
	पूर्ण

	of_node_put(bus);
पूर्ण

अटल पूर्णांक of_dev_or_parent_node_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	अगर (dev->of_node == data)
		वापस 1;

	अगर (dev->parent)
		वापस dev->parent->of_node == data;

	वापस 0;
पूर्ण

/* must call put_device() when करोne with वापसed i2c_client device */
काष्ठा i2c_client *of_find_i2c_device_by_node(काष्ठा device_node *node)
अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;

	dev = bus_find_device_by_of_node(&i2c_bus_type, node);
	अगर (!dev)
		वापस शून्य;

	client = i2c_verअगरy_client(dev);
	अगर (!client)
		put_device(dev);

	वापस client;
पूर्ण
EXPORT_SYMBOL(of_find_i2c_device_by_node);

/* must call put_device() when करोne with वापसed i2c_adapter device */
काष्ठा i2c_adapter *of_find_i2c_adapter_by_node(काष्ठा device_node *node)
अणु
	काष्ठा device *dev;
	काष्ठा i2c_adapter *adapter;

	dev = bus_find_device(&i2c_bus_type, शून्य, node,
			      of_dev_or_parent_node_match);
	अगर (!dev)
		वापस शून्य;

	adapter = i2c_verअगरy_adapter(dev);
	अगर (!adapter)
		put_device(dev);

	वापस adapter;
पूर्ण
EXPORT_SYMBOL(of_find_i2c_adapter_by_node);

/* must call i2c_put_adapter() when करोne with वापसed i2c_adapter device */
काष्ठा i2c_adapter *of_get_i2c_adapter_by_node(काष्ठा device_node *node)
अणु
	काष्ठा i2c_adapter *adapter;

	adapter = of_find_i2c_adapter_by_node(node);
	अगर (!adapter)
		वापस शून्य;

	अगर (!try_module_get(adapter->owner)) अणु
		put_device(&adapter->dev);
		adapter = शून्य;
	पूर्ण

	वापस adapter;
पूर्ण
EXPORT_SYMBOL(of_get_i2c_adapter_by_node);

अटल स्थिर काष्ठा of_device_id*
i2c_of_match_device_sysfs(स्थिर काष्ठा of_device_id *matches,
				  काष्ठा i2c_client *client)
अणु
	स्थिर अक्षर *name;

	क्रम (; matches->compatible[0]; matches++) अणु
		/*
		 * Adding devices through the i2c sysfs पूर्णांकerface provides us
		 * a string to match which may be compatible with the device
		 * tree compatible strings, however with no actual of_node the
		 * of_match_device() will not match
		 */
		अगर (sysfs_streq(client->name, matches->compatible))
			वापस matches;

		name = म_अक्षर(matches->compatible, ',');
		अगर (!name)
			name = matches->compatible;
		अन्यथा
			name++;

		अगर (sysfs_streq(client->name, name))
			वापस matches;
	पूर्ण

	वापस शून्य;
पूर्ण

स्थिर काष्ठा of_device_id
*i2c_of_match_device(स्थिर काष्ठा of_device_id *matches,
		     काष्ठा i2c_client *client)
अणु
	स्थिर काष्ठा of_device_id *match;

	अगर (!(client && matches))
		वापस शून्य;

	match = of_match_device(matches, &client->dev);
	अगर (match)
		वापस match;

	वापस i2c_of_match_device_sysfs(matches, client);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_of_match_device);

#अगर IS_ENABLED(CONFIG_OF_DYNAMIC)
अटल पूर्णांक of_i2c_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			 व्योम *arg)
अणु
	काष्ठा of_reconfig_data *rd = arg;
	काष्ठा i2c_adapter *adap;
	काष्ठा i2c_client *client;

	चयन (of_reconfig_get_state_change(action, rd)) अणु
	हाल OF_RECONFIG_CHANGE_ADD:
		adap = of_find_i2c_adapter_by_node(rd->dn->parent);
		अगर (adap == शून्य)
			वापस NOTIFY_OK;	/* not क्रम us */

		अगर (of_node_test_and_set_flag(rd->dn, OF_POPULATED)) अणु
			put_device(&adap->dev);
			वापस NOTIFY_OK;
		पूर्ण

		client = of_i2c_रेजिस्टर_device(adap, rd->dn);
		अगर (IS_ERR(client)) अणु
			dev_err(&adap->dev, "failed to create client for '%pOF'\n",
				 rd->dn);
			put_device(&adap->dev);
			of_node_clear_flag(rd->dn, OF_POPULATED);
			वापस notअगरier_from_त्रुटि_सं(PTR_ERR(client));
		पूर्ण
		put_device(&adap->dev);
		अवरोध;
	हाल OF_RECONFIG_CHANGE_REMOVE:
		/* alपढ़ोy depopulated? */
		अगर (!of_node_check_flag(rd->dn, OF_POPULATED))
			वापस NOTIFY_OK;

		/* find our device by node */
		client = of_find_i2c_device_by_node(rd->dn);
		अगर (client == शून्य)
			वापस NOTIFY_OK;	/* no? not meant क्रम us */

		/* unरेजिस्टर takes one ref away */
		i2c_unरेजिस्टर_device(client);

		/* and put the reference of the find */
		put_device(&client->dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

काष्ठा notअगरier_block i2c_of_notअगरier = अणु
	.notअगरier_call = of_i2c_notअगरy,
पूर्ण;
#पूर्ण_अगर /* CONFIG_OF_DYNAMIC */
