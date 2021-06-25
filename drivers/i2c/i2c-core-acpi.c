<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux I2C core ACPI support code
 *
 * Copyright (C) 2014 Intel Corp, Author: Lan Tianyu <tianyu.lan@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "i2c-core.h"

काष्ठा i2c_acpi_handler_data अणु
	काष्ठा acpi_connection_info info;
	काष्ठा i2c_adapter *adapter;
पूर्ण;

काष्ठा gsb_buffer अणु
	u8	status;
	u8	len;
	जोड़ अणु
		u16	wdata;
		u8	bdata;
		u8	data[0];
	पूर्ण;
पूर्ण __packed;

काष्ठा i2c_acpi_lookup अणु
	काष्ठा i2c_board_info *info;
	acpi_handle adapter_handle;
	acpi_handle device_handle;
	acpi_handle search_handle;
	पूर्णांक n;
	पूर्णांक index;
	u32 speed;
	u32 min_speed;
	u32 क्रमce_speed;
पूर्ण;

/**
 * i2c_acpi_get_i2c_resource - Gets I2cSerialBus resource अगर type matches
 * @ares:	ACPI resource
 * @i2c:	Poपूर्णांकer to I2cSerialBus resource will be वापसed here
 *
 * Checks अगर the given ACPI resource is of type I2cSerialBus.
 * In this हाल, वापसs a poपूर्णांकer to it to the caller.
 *
 * Returns true अगर resource type is of I2cSerialBus, otherwise false.
 */
bool i2c_acpi_get_i2c_resource(काष्ठा acpi_resource *ares,
			       काष्ठा acpi_resource_i2c_serialbus **i2c)
अणु
	काष्ठा acpi_resource_i2c_serialbus *sb;

	अगर (ares->type != ACPI_RESOURCE_TYPE_SERIAL_BUS)
		वापस false;

	sb = &ares->data.i2c_serial_bus;
	अगर (sb->type != ACPI_RESOURCE_SERIAL_TYPE_I2C)
		वापस false;

	*i2c = sb;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_acpi_get_i2c_resource);

अटल पूर्णांक i2c_acpi_fill_info(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा i2c_acpi_lookup *lookup = data;
	काष्ठा i2c_board_info *info = lookup->info;
	काष्ठा acpi_resource_i2c_serialbus *sb;
	acpi_status status;

	अगर (info->addr || !i2c_acpi_get_i2c_resource(ares, &sb))
		वापस 1;

	अगर (lookup->index != -1 && lookup->n++ != lookup->index)
		वापस 1;

	status = acpi_get_handle(lookup->device_handle,
				 sb->resource_source.string_ptr,
				 &lookup->adapter_handle);
	अगर (ACPI_FAILURE(status))
		वापस 1;

	info->addr = sb->slave_address;
	lookup->speed = sb->connection_speed;
	अगर (sb->access_mode == ACPI_I2C_10BIT_MODE)
		info->flags |= I2C_CLIENT_TEN;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id i2c_acpi_ignored_device_ids[] = अणु
	/*
	 * ACPI video acpi_devices, which are handled by the acpi-video driver
	 * someबार contain a SERIAL_TYPE_I2C ACPI resource, ignore these.
	 */
	अणु ACPI_VIDEO_HID, 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक i2c_acpi_करो_lookup(काष्ठा acpi_device *adev,
			      काष्ठा i2c_acpi_lookup *lookup)
अणु
	काष्ठा i2c_board_info *info = lookup->info;
	काष्ठा list_head resource_list;
	पूर्णांक ret;

	अगर (acpi_bus_get_status(adev) || !adev->status.present)
		वापस -EINVAL;

	अगर (acpi_match_device_ids(adev, i2c_acpi_ignored_device_ids) == 0)
		वापस -ENODEV;

	स_रखो(info, 0, माप(*info));
	lookup->device_handle = acpi_device_handle(adev);

	/* Look up क्रम I2cSerialBus resource */
	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list,
				     i2c_acpi_fill_info, lookup);
	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (ret < 0 || !info->addr)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_acpi_add_resource(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	पूर्णांक *irq = data;
	काष्ठा resource r;

	अगर (*irq <= 0 && acpi_dev_resource_पूर्णांकerrupt(ares, 0, &r))
		*irq = i2c_dev_irq_from_resources(&r, 1);

	वापस 1; /* No need to add resource to the list */
पूर्ण

/**
 * i2c_acpi_get_irq - get device IRQ number from ACPI
 * @client: Poपूर्णांकer to the I2C client device
 *
 * Find the IRQ number used by a specअगरic client device.
 *
 * Return: The IRQ number or an error code.
 */
पूर्णांक i2c_acpi_get_irq(काष्ठा i2c_client *client)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&client->dev);
	काष्ठा list_head resource_list;
	पूर्णांक irq = -ENOENT;
	पूर्णांक ret;

	INIT_LIST_HEAD(&resource_list);

	ret = acpi_dev_get_resources(adev, &resource_list,
				     i2c_acpi_add_resource, &irq);
	अगर (ret < 0)
		वापस ret;

	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (irq == -ENOENT)
		irq = acpi_dev_gpio_irq_get(adev, 0);

	वापस irq;
पूर्ण

अटल पूर्णांक i2c_acpi_get_info(काष्ठा acpi_device *adev,
			     काष्ठा i2c_board_info *info,
			     काष्ठा i2c_adapter *adapter,
			     acpi_handle *adapter_handle)
अणु
	काष्ठा i2c_acpi_lookup lookup;
	पूर्णांक ret;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.info = info;
	lookup.index = -1;

	अगर (acpi_device_क्रमागतerated(adev))
		वापस -EINVAL;

	ret = i2c_acpi_करो_lookup(adev, &lookup);
	अगर (ret)
		वापस ret;

	अगर (adapter) अणु
		/* The adapter must match the one in I2cSerialBus() connector */
		अगर (ACPI_HANDLE(&adapter->dev) != lookup.adapter_handle)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		काष्ठा acpi_device *adapter_adev;

		/* The adapter must be present */
		अगर (acpi_bus_get_device(lookup.adapter_handle, &adapter_adev))
			वापस -ENODEV;
		अगर (acpi_bus_get_status(adapter_adev) ||
		    !adapter_adev->status.present)
			वापस -ENODEV;
	पूर्ण

	info->fwnode = acpi_fwnode_handle(adev);
	अगर (adapter_handle)
		*adapter_handle = lookup.adapter_handle;

	acpi_set_modalias(adev, dev_name(&adev->dev), info->type,
			  माप(info->type));

	वापस 0;
पूर्ण

अटल व्योम i2c_acpi_रेजिस्टर_device(काष्ठा i2c_adapter *adapter,
				     काष्ठा acpi_device *adev,
				     काष्ठा i2c_board_info *info)
अणु
	adev->घातer.flags.ignore_parent = true;
	acpi_device_set_क्रमागतerated(adev);

	अगर (IS_ERR(i2c_new_client_device(adapter, info)))
		adev->घातer.flags.ignore_parent = false;
पूर्ण

अटल acpi_status i2c_acpi_add_device(acpi_handle handle, u32 level,
				       व्योम *data, व्योम **वापस_value)
अणु
	काष्ठा i2c_adapter *adapter = data;
	काष्ठा acpi_device *adev;
	काष्ठा i2c_board_info info;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	अगर (i2c_acpi_get_info(adev, &info, adapter, शून्य))
		वापस AE_OK;

	i2c_acpi_रेजिस्टर_device(adapter, adev, &info);

	वापस AE_OK;
पूर्ण

#घोषणा I2C_ACPI_MAX_SCAN_DEPTH 32

/**
 * i2c_acpi_रेजिस्टर_devices - क्रमागतerate I2C slave devices behind adapter
 * @adap: poपूर्णांकer to adapter
 *
 * Enumerate all I2C slave devices behind this adapter by walking the ACPI
 * namespace. When a device is found it will be added to the Linux device
 * model and bound to the corresponding ACPI handle.
 */
व्योम i2c_acpi_रेजिस्टर_devices(काष्ठा i2c_adapter *adap)
अणु
	acpi_status status;
	acpi_handle handle;

	अगर (!has_acpi_companion(&adap->dev))
		वापस;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     I2C_ACPI_MAX_SCAN_DEPTH,
				     i2c_acpi_add_device, शून्य,
				     adap, शून्य);
	अगर (ACPI_FAILURE(status))
		dev_warn(&adap->dev, "failed to enumerate I2C slaves\n");

	अगर (!adap->dev.parent)
		वापस;

	handle = ACPI_HANDLE(adap->dev.parent);
	अगर (!handle)
		वापस;

	acpi_walk_dep_device_list(handle);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id i2c_acpi_क्रमce_400khz_device_ids[] = अणु
	/*
	 * These Silead touchscreen controllers only work at 400KHz, क्रम
	 * some reason they करो not work at 100KHz. On some devices the ACPI
	 * tables list another device at their bus as only being capable
	 * of 100KHz, testing has shown that these other devices work fine
	 * at 400KHz (as can be expected of any recent i2c hw) so we क्रमce
	 * the speed of the bus to 400 KHz अगर a Silead device is present.
	 */
	अणु "MSSL1680", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल acpi_status i2c_acpi_lookup_speed(acpi_handle handle, u32 level,
					   व्योम *data, व्योम **वापस_value)
अणु
	काष्ठा i2c_acpi_lookup *lookup = data;
	काष्ठा acpi_device *adev;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	अगर (i2c_acpi_करो_lookup(adev, lookup))
		वापस AE_OK;

	अगर (lookup->search_handle != lookup->adapter_handle)
		वापस AE_OK;

	अगर (lookup->speed <= lookup->min_speed)
		lookup->min_speed = lookup->speed;

	अगर (acpi_match_device_ids(adev, i2c_acpi_क्रमce_400khz_device_ids) == 0)
		lookup->क्रमce_speed = I2C_MAX_FAST_MODE_FREQ;

	वापस AE_OK;
पूर्ण

/**
 * i2c_acpi_find_bus_speed - find I2C bus speed from ACPI
 * @dev: The device owning the bus
 *
 * Find the I2C bus speed by walking the ACPI namespace क्रम all I2C slaves
 * devices connected to this bus and use the speed of slowest device.
 *
 * Returns the speed in Hz or zero
 */
u32 i2c_acpi_find_bus_speed(काष्ठा device *dev)
अणु
	काष्ठा i2c_acpi_lookup lookup;
	काष्ठा i2c_board_info dummy;
	acpi_status status;

	अगर (!has_acpi_companion(dev))
		वापस 0;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.search_handle = ACPI_HANDLE(dev);
	lookup.min_speed = अच_पूर्णांक_उच्च;
	lookup.info = &dummy;
	lookup.index = -1;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     I2C_ACPI_MAX_SCAN_DEPTH,
				     i2c_acpi_lookup_speed, शून्य,
				     &lookup, शून्य);

	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(dev, "unable to find I2C bus speed from ACPI\n");
		वापस 0;
	पूर्ण

	अगर (lookup.क्रमce_speed) अणु
		अगर (lookup.क्रमce_speed != lookup.min_speed)
			dev_warn(dev, FW_BUG "DSDT uses known not-working I2C bus speed %d, forcing it to %d\n",
				 lookup.min_speed, lookup.क्रमce_speed);
		वापस lookup.क्रमce_speed;
	पूर्ण अन्यथा अगर (lookup.min_speed != अच_पूर्णांक_उच्च) अणु
		वापस lookup.min_speed;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(i2c_acpi_find_bus_speed);

अटल पूर्णांक i2c_acpi_find_match_adapter(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा i2c_adapter *adapter = i2c_verअगरy_adapter(dev);

	अगर (!adapter)
		वापस 0;

	वापस ACPI_HANDLE(dev) == (acpi_handle)data;
पूर्ण

काष्ठा i2c_adapter *i2c_acpi_find_adapter_by_handle(acpi_handle handle)
अणु
	काष्ठा device *dev;

	dev = bus_find_device(&i2c_bus_type, शून्य, handle,
			      i2c_acpi_find_match_adapter);

	वापस dev ? i2c_verअगरy_adapter(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_acpi_find_adapter_by_handle);

अटल काष्ठा i2c_client *i2c_acpi_find_client_by_adev(काष्ठा acpi_device *adev)
अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;

	dev = bus_find_device_by_acpi_dev(&i2c_bus_type, adev);
	अगर (!dev)
		वापस शून्य;

	client = i2c_verअगरy_client(dev);
	अगर (!client)
		put_device(dev);

	वापस client;
पूर्ण

अटल पूर्णांक i2c_acpi_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ value,
			   व्योम *arg)
अणु
	काष्ठा acpi_device *adev = arg;
	काष्ठा i2c_board_info info;
	acpi_handle adapter_handle;
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_client *client;

	चयन (value) अणु
	हाल ACPI_RECONFIG_DEVICE_ADD:
		अगर (i2c_acpi_get_info(adev, &info, शून्य, &adapter_handle))
			अवरोध;

		adapter = i2c_acpi_find_adapter_by_handle(adapter_handle);
		अगर (!adapter)
			अवरोध;

		i2c_acpi_रेजिस्टर_device(adapter, adev, &info);
		अवरोध;
	हाल ACPI_RECONFIG_DEVICE_REMOVE:
		अगर (!acpi_device_क्रमागतerated(adev))
			अवरोध;

		client = i2c_acpi_find_client_by_adev(adev);
		अगर (!client)
			अवरोध;

		i2c_unरेजिस्टर_device(client);
		put_device(&client->dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

काष्ठा notअगरier_block i2c_acpi_notअगरier = अणु
	.notअगरier_call = i2c_acpi_notअगरy,
पूर्ण;

/**
 * i2c_acpi_new_device - Create i2c-client क्रम the Nth I2cSerialBus resource
 * @dev:     Device owning the ACPI resources to get the client from
 * @index:   Index of ACPI resource to get
 * @info:    describes the I2C device; note this is modअगरied (addr माला_लो set)
 * Context: can sleep
 *
 * By शेष the i2c subsys creates an i2c-client क्रम the first I2cSerialBus
 * resource of an acpi_device, but some acpi_devices have multiple I2cSerialBus
 * resources, in that हाल this function can be used to create an i2c-client
 * क्रम other I2cSerialBus resources in the Current Resource Settings table.
 *
 * Also see i2c_new_client_device, which this function calls to create the
 * i2c-client.
 *
 * Returns a poपूर्णांकer to the new i2c-client, or error poपूर्णांकer in हाल of failure.
 * Specअगरically, -EPROBE_DEFER is वापसed अगर the adapter is not found.
 */
काष्ठा i2c_client *i2c_acpi_new_device(काष्ठा device *dev, पूर्णांक index,
				       काष्ठा i2c_board_info *info)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा i2c_acpi_lookup lookup;
	काष्ठा i2c_adapter *adapter;
	LIST_HEAD(resource_list);
	पूर्णांक ret;

	स_रखो(&lookup, 0, माप(lookup));
	lookup.info = info;
	lookup.device_handle = acpi_device_handle(adev);
	lookup.index = index;

	ret = acpi_dev_get_resources(adev, &resource_list,
				     i2c_acpi_fill_info, &lookup);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (!info->addr)
		वापस ERR_PTR(-EADDRNOTAVAIL);

	adapter = i2c_acpi_find_adapter_by_handle(lookup.adapter_handle);
	अगर (!adapter)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस i2c_new_client_device(adapter, info);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_acpi_new_device);

#अगर_घोषित CONFIG_ACPI_I2C_OPREGION
अटल पूर्णांक acpi_gsb_i2c_पढ़ो_bytes(काष्ठा i2c_client *client,
		u8 cmd, u8 *data, u8 data_len)
अणु

	काष्ठा i2c_msg msgs[2];
	पूर्णांक ret;
	u8 *buffer;

	buffer = kzalloc(data_len, GFP_KERNEL);
	अगर (!buffer)
		वापस AE_NO_MEMORY;

	msgs[0].addr = client->addr;
	msgs[0].flags = client->flags;
	msgs[0].len = 1;
	msgs[0].buf = &cmd;

	msgs[1].addr = client->addr;
	msgs[1].flags = client->flags | I2C_M_RD;
	msgs[1].len = data_len;
	msgs[1].buf = buffer;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0) अणु
		/* Getting a NACK is unक्रमtunately normal with some DSTDs */
		अगर (ret == -EREMOTEIO)
			dev_dbg(&client->adapter->dev, "i2c read %d bytes from client@%#x starting at reg %#x failed, error: %d\n",
				data_len, client->addr, cmd, ret);
		अन्यथा
			dev_err(&client->adapter->dev, "i2c read %d bytes from client@%#x starting at reg %#x failed, error: %d\n",
				data_len, client->addr, cmd, ret);
	/* 2 transfers must have completed successfully */
	पूर्ण अन्यथा अगर (ret == 2) अणु
		स_नकल(data, buffer, data_len);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण

	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_gsb_i2c_ग_लिखो_bytes(काष्ठा i2c_client *client,
		u8 cmd, u8 *data, u8 data_len)
अणु

	काष्ठा i2c_msg msgs[1];
	u8 *buffer;
	पूर्णांक ret = AE_OK;

	buffer = kzalloc(data_len + 1, GFP_KERNEL);
	अगर (!buffer)
		वापस AE_NO_MEMORY;

	buffer[0] = cmd;
	स_नकल(buffer + 1, data, data_len);

	msgs[0].addr = client->addr;
	msgs[0].flags = client->flags;
	msgs[0].len = data_len + 1;
	msgs[0].buf = buffer;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));

	kमुक्त(buffer);

	अगर (ret < 0) अणु
		dev_err(&client->adapter->dev, "i2c write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* 1 transfer must have completed successfully */
	वापस (ret == 1) ? 0 : -EIO;
पूर्ण

अटल acpi_status
i2c_acpi_space_handler(u32 function, acpi_physical_address command,
			u32 bits, u64 *value64,
			व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा gsb_buffer *gsb = (काष्ठा gsb_buffer *)value64;
	काष्ठा i2c_acpi_handler_data *data = handler_context;
	काष्ठा acpi_connection_info *info = &data->info;
	काष्ठा acpi_resource_i2c_serialbus *sb;
	काष्ठा i2c_adapter *adapter = data->adapter;
	काष्ठा i2c_client *client;
	काष्ठा acpi_resource *ares;
	u32 accessor_type = function >> 16;
	u8 action = function & ACPI_IO_MASK;
	acpi_status ret;
	पूर्णांक status;

	ret = acpi_buffer_to_resource(info->connection, info->length, &ares);
	अगर (ACPI_FAILURE(ret))
		वापस ret;

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client) अणु
		ret = AE_NO_MEMORY;
		जाओ err;
	पूर्ण

	अगर (!value64 || !i2c_acpi_get_i2c_resource(ares, &sb)) अणु
		ret = AE_BAD_PARAMETER;
		जाओ err;
	पूर्ण

	client->adapter = adapter;
	client->addr = sb->slave_address;

	अगर (sb->access_mode == ACPI_I2C_10BIT_MODE)
		client->flags |= I2C_CLIENT_TEN;

	चयन (accessor_type) अणु
	हाल ACPI_GSB_ACCESS_ATTRIB_SEND_RCV:
		अगर (action == ACPI_READ) अणु
			status = i2c_smbus_पढ़ो_byte(client);
			अगर (status >= 0) अणु
				gsb->bdata = status;
				status = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			status = i2c_smbus_ग_लिखो_byte(client, gsb->bdata);
		पूर्ण
		अवरोध;

	हाल ACPI_GSB_ACCESS_ATTRIB_BYTE:
		अगर (action == ACPI_READ) अणु
			status = i2c_smbus_पढ़ो_byte_data(client, command);
			अगर (status >= 0) अणु
				gsb->bdata = status;
				status = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			status = i2c_smbus_ग_लिखो_byte_data(client, command,
					gsb->bdata);
		पूर्ण
		अवरोध;

	हाल ACPI_GSB_ACCESS_ATTRIB_WORD:
		अगर (action == ACPI_READ) अणु
			status = i2c_smbus_पढ़ो_word_data(client, command);
			अगर (status >= 0) अणु
				gsb->wdata = status;
				status = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			status = i2c_smbus_ग_लिखो_word_data(client, command,
					gsb->wdata);
		पूर्ण
		अवरोध;

	हाल ACPI_GSB_ACCESS_ATTRIB_BLOCK:
		अगर (action == ACPI_READ) अणु
			status = i2c_smbus_पढ़ो_block_data(client, command,
					gsb->data);
			अगर (status >= 0) अणु
				gsb->len = status;
				status = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			status = i2c_smbus_ग_लिखो_block_data(client, command,
					gsb->len, gsb->data);
		पूर्ण
		अवरोध;

	हाल ACPI_GSB_ACCESS_ATTRIB_MULTIBYTE:
		अगर (action == ACPI_READ) अणु
			status = acpi_gsb_i2c_पढ़ो_bytes(client, command,
					gsb->data, info->access_length);
		पूर्ण अन्यथा अणु
			status = acpi_gsb_i2c_ग_लिखो_bytes(client, command,
					gsb->data, info->access_length);
		पूर्ण
		अवरोध;

	शेष:
		dev_warn(&adapter->dev, "protocol 0x%02x not supported for client 0x%02x\n",
			 accessor_type, client->addr);
		ret = AE_BAD_PARAMETER;
		जाओ err;
	पूर्ण

	gsb->status = status;

 err:
	kमुक्त(client);
	ACPI_FREE(ares);
	वापस ret;
पूर्ण


पूर्णांक i2c_acpi_install_space_handler(काष्ठा i2c_adapter *adapter)
अणु
	acpi_handle handle;
	काष्ठा i2c_acpi_handler_data *data;
	acpi_status status;

	अगर (!adapter->dev.parent)
		वापस -ENODEV;

	handle = ACPI_HANDLE(adapter->dev.parent);

	अगर (!handle)
		वापस -ENODEV;

	data = kzalloc(माप(काष्ठा i2c_acpi_handler_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->adapter = adapter;
	status = acpi_bus_attach_निजी_data(handle, (व्योम *)data);
	अगर (ACPI_FAILURE(status)) अणु
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण

	status = acpi_install_address_space_handler(handle,
				ACPI_ADR_SPACE_GSBUS,
				&i2c_acpi_space_handler,
				शून्य,
				data);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&adapter->dev, "Error installing i2c space handler\n");
		acpi_bus_detach_निजी_data(handle);
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम i2c_acpi_हटाओ_space_handler(काष्ठा i2c_adapter *adapter)
अणु
	acpi_handle handle;
	काष्ठा i2c_acpi_handler_data *data;
	acpi_status status;

	अगर (!adapter->dev.parent)
		वापस;

	handle = ACPI_HANDLE(adapter->dev.parent);

	अगर (!handle)
		वापस;

	acpi_हटाओ_address_space_handler(handle,
				ACPI_ADR_SPACE_GSBUS,
				&i2c_acpi_space_handler);

	status = acpi_bus_get_निजी_data(handle, (व्योम **)&data);
	अगर (ACPI_SUCCESS(status))
		kमुक्त(data);

	acpi_bus_detach_निजी_data(handle);
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_I2C_OPREGION */
