<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i2c-smbus.c - SMBus extensions to the I2C protocol
 *
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2010-2019 Jean Delvare <jdelvare@suse.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

काष्ठा i2c_smbus_alert अणु
	काष्ठा work_काष्ठा	alert;
	काष्ठा i2c_client	*ara;		/* Alert response address */
पूर्ण;

काष्ठा alert_data अणु
	अचिन्हित लघु		addr;
	क्रमागत i2c_alert_protocol	type;
	अचिन्हित पूर्णांक		data;
पूर्ण;

/* If this is the alerting device, notअगरy its driver */
अटल पूर्णांक smbus_करो_alert(काष्ठा device *dev, व्योम *addrp)
अणु
	काष्ठा i2c_client *client = i2c_verअगरy_client(dev);
	काष्ठा alert_data *data = addrp;
	काष्ठा i2c_driver *driver;

	अगर (!client || client->addr != data->addr)
		वापस 0;
	अगर (client->flags & I2C_CLIENT_TEN)
		वापस 0;

	/*
	 * Drivers should either disable alerts, or provide at least
	 * a minimal handler.  Lock so the driver won't change.
	 */
	device_lock(dev);
	अगर (client->dev.driver) अणु
		driver = to_i2c_driver(client->dev.driver);
		अगर (driver->alert)
			driver->alert(client, data->type, data->data);
		अन्यथा
			dev_warn(&client->dev, "no driver alert()!\n");
	पूर्ण अन्यथा
		dev_dbg(&client->dev, "alert with no driver\n");
	device_unlock(dev);

	/* Stop iterating after we find the device */
	वापस -EBUSY;
पूर्ण

/*
 * The alert IRQ handler needs to hand work off to a task which can issue
 * SMBus calls, because those sleeping calls can't be made in IRQ context.
 */
अटल irqवापस_t smbus_alert(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा i2c_smbus_alert *alert = d;
	काष्ठा i2c_client *ara;

	ara = alert->ara;

	क्रम (;;) अणु
		s32 status;
		काष्ठा alert_data data;

		/*
		 * Devices with pending alerts reply in address order, low
		 * to high, because of slave transmit arbitration.  After
		 * responding, an SMBus device stops निश्चितing SMBALERT#.
		 *
		 * Note that SMBus 2.0 reserves 10-bit addresses क्रम future
		 * use.  We neither handle them, nor try to use PEC here.
		 */
		status = i2c_smbus_पढ़ो_byte(ara);
		अगर (status < 0)
			अवरोध;

		data.data = status & 1;
		data.addr = status >> 1;
		data.type = I2C_PROTOCOL_SMBUS_ALERT;

		dev_dbg(&ara->dev, "SMBALERT# from dev 0x%02x, flag %d\n",
			data.addr, data.data);

		/* Notअगरy driver क्रम the device which issued the alert */
		device_क्रम_each_child(&ara->adapter->dev, &data,
				      smbus_करो_alert);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smbalert_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा i2c_smbus_alert *alert;

	alert = container_of(work, काष्ठा i2c_smbus_alert, alert);

	smbus_alert(0, alert);

पूर्ण

/* Setup SMBALERT# infraकाष्ठाure */
अटल पूर्णांक smbalert_probe(काष्ठा i2c_client *ara,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_smbus_alert_setup *setup = dev_get_platdata(&ara->dev);
	काष्ठा i2c_smbus_alert *alert;
	काष्ठा i2c_adapter *adapter = ara->adapter;
	पूर्णांक res, irq;

	alert = devm_kzalloc(&ara->dev, माप(काष्ठा i2c_smbus_alert),
			     GFP_KERNEL);
	अगर (!alert)
		वापस -ENOMEM;

	अगर (setup) अणु
		irq = setup->irq;
	पूर्ण अन्यथा अणु
		irq = of_irq_get_byname(adapter->dev.of_node, "smbus_alert");
		अगर (irq <= 0)
			वापस irq;
	पूर्ण

	INIT_WORK(&alert->alert, smbalert_work);
	alert->ara = ara;

	अगर (irq > 0) अणु
		res = devm_request_thपढ़ोed_irq(&ara->dev, irq,
						शून्य, smbus_alert,
						IRQF_SHARED | IRQF_ONESHOT,
						"smbus_alert", alert);
		अगर (res)
			वापस res;
	पूर्ण

	i2c_set_clientdata(ara, alert);
	dev_info(&adapter->dev, "supports SMBALERT#\n");

	वापस 0;
पूर्ण

/* IRQ and memory resources are managed so they are मुक्तd स्वतःmatically */
अटल पूर्णांक smbalert_हटाओ(काष्ठा i2c_client *ara)
अणु
	काष्ठा i2c_smbus_alert *alert = i2c_get_clientdata(ara);

	cancel_work_sync(&alert->alert);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id smbalert_ids[] = अणु
	अणु "smbus_alert", 0 पूर्ण,
	अणु /* LIST END */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, smbalert_ids);

अटल काष्ठा i2c_driver smbalert_driver = अणु
	.driver = अणु
		.name	= "smbus_alert",
	पूर्ण,
	.probe		= smbalert_probe,
	.हटाओ		= smbalert_हटाओ,
	.id_table	= smbalert_ids,
पूर्ण;

/**
 * i2c_handle_smbus_alert - Handle an SMBus alert
 * @ara: the ARA client on the relevant adapter
 * Context: can't sleep
 *
 * Helper function to be called from an I2C bus driver's पूर्णांकerrupt
 * handler. It will schedule the alert work, in turn calling the
 * corresponding I2C device driver's alert function.
 *
 * It is assumed that ara is a valid i2c client previously वापसed by
 * i2c_new_smbus_alert_device().
 */
पूर्णांक i2c_handle_smbus_alert(काष्ठा i2c_client *ara)
अणु
	काष्ठा i2c_smbus_alert *alert = i2c_get_clientdata(ara);

	वापस schedule_work(&alert->alert);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_handle_smbus_alert);

module_i2c_driver(smbalert_driver);

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
#घोषणा SMBUS_HOST_NOTIFY_LEN	3
काष्ठा i2c_slave_host_notअगरy_status अणु
	u8 index;
	u8 addr;
पूर्ण;

अटल पूर्णांक i2c_slave_host_notअगरy_cb(काष्ठा i2c_client *client,
				    क्रमागत i2c_slave_event event, u8 *val)
अणु
	काष्ठा i2c_slave_host_notअगरy_status *status = client->dev.platक्रमm_data;

	चयन (event) अणु
	हाल I2C_SLAVE_WRITE_RECEIVED:
		/* We only retrieve the first byte received (addr)
		 * since there is currently no support to retrieve the data
		 * parameter from the client.
		 */
		अगर (status->index == 0)
			status->addr = *val;
		अगर (status->index < U8_MAX)
			status->index++;
		अवरोध;
	हाल I2C_SLAVE_STOP:
		अगर (status->index == SMBUS_HOST_NOTIFY_LEN)
			i2c_handle_smbus_host_notअगरy(client->adapter,
						     status->addr);
		fallthrough;
	हाल I2C_SLAVE_WRITE_REQUESTED:
		status->index = 0;
		अवरोध;
	हाल I2C_SLAVE_READ_REQUESTED:
	हाल I2C_SLAVE_READ_PROCESSED:
		*val = 0xff;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i2c_new_slave_host_notअगरy_device - get a client क्रम SMBus host-notअगरy support
 * @adapter: the target adapter
 * Context: can sleep
 *
 * Setup handling of the SMBus host-notअगरy protocol on a given I2C bus segment.
 *
 * Handling is करोne by creating a device and its callback and handling data
 * received via the SMBus host-notअगरy address (0x8)
 *
 * This वापसs the client, which should be ultimately मुक्तd using
 * i2c_मुक्त_slave_host_notअगरy_device(); or an ERRPTR to indicate an error.
 */
काष्ठा i2c_client *i2c_new_slave_host_notअगरy_device(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i2c_board_info host_notअगरy_board_info = अणु
		I2C_BOARD_INFO("smbus_host_notify", 0x08),
		.flags  = I2C_CLIENT_SLAVE,
	पूर्ण;
	काष्ठा i2c_slave_host_notअगरy_status *status;
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	status = kzalloc(माप(काष्ठा i2c_slave_host_notअगरy_status),
			 GFP_KERNEL);
	अगर (!status)
		वापस ERR_PTR(-ENOMEM);

	host_notअगरy_board_info.platक्रमm_data = status;

	client = i2c_new_client_device(adapter, &host_notअगरy_board_info);
	अगर (IS_ERR(client)) अणु
		kमुक्त(status);
		वापस client;
	पूर्ण

	ret = i2c_slave_रेजिस्टर(client, i2c_slave_host_notअगरy_cb);
	अगर (ret) अणु
		i2c_unरेजिस्टर_device(client);
		kमुक्त(status);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस client;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_new_slave_host_notअगरy_device);

/**
 * i2c_मुक्त_slave_host_notअगरy_device - मुक्त the client क्रम SMBus host-notअगरy
 * support
 * @client: the client to मुक्त
 * Context: can sleep
 *
 * Free the i2c_client allocated via i2c_new_slave_host_notअगरy_device
 */
व्योम i2c_मुक्त_slave_host_notअगरy_device(काष्ठा i2c_client *client)
अणु
	अगर (IS_ERR_OR_शून्य(client))
		वापस;

	i2c_slave_unरेजिस्टर(client);
	kमुक्त(client->dev.platक्रमm_data);
	i2c_unरेजिस्टर_device(client);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_मुक्त_slave_host_notअगरy_device);
#पूर्ण_अगर

/*
 * SPD is not part of SMBus but we include it here क्रम convenience as the
 * target प्रणालीs are the same.
 * Restrictions to स्वतःmatic SPD instantiation:
 *  - Only works अगर all filled slots have the same memory type
 *  - Only works क्रम DDR2, DDR3 and DDR4 क्रम now
 *  - Only works on प्रणालीs with 1 to 4 memory slots
 */
#अगर IS_ENABLED(CONFIG_DMI)
व्योम i2c_रेजिस्टर_spd(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक n, slot_count = 0, dimm_count = 0;
	u16 handle;
	u8 common_mem_type = 0x0, mem_type;
	u64 mem_size;
	स्थिर अक्षर *name;

	जबतक ((handle = dmi_memdev_handle(slot_count)) != 0xffff) अणु
		slot_count++;

		/* Skip empty slots */
		mem_size = dmi_memdev_size(handle);
		अगर (!mem_size)
			जारी;

		/* Skip undefined memory type */
		mem_type = dmi_memdev_type(handle);
		अगर (mem_type <= 0x02)		/* Invalid, Other, Unknown */
			जारी;

		अगर (!common_mem_type) अणु
			/* First filled slot */
			common_mem_type = mem_type;
		पूर्ण अन्यथा अणु
			/* Check that all filled slots have the same type */
			अगर (mem_type != common_mem_type) अणु
				dev_warn(&adap->dev,
					 "Different memory types mixed, not instantiating SPD\n");
				वापस;
			पूर्ण
		पूर्ण
		dimm_count++;
	पूर्ण

	/* No useful DMI data, bail out */
	अगर (!dimm_count)
		वापस;

	dev_info(&adap->dev, "%d/%d memory slots populated (from DMI)\n",
		 dimm_count, slot_count);

	अगर (slot_count > 4) अणु
		dev_warn(&adap->dev,
			 "Systems with more than 4 memory slots not supported yet, not instantiating SPD\n");
		वापस;
	पूर्ण

	चयन (common_mem_type) अणु
	हाल 0x13:	/* DDR2 */
	हाल 0x18:	/* DDR3 */
	हाल 0x1C:	/* LPDDR2 */
	हाल 0x1D:	/* LPDDR3 */
		name = "spd";
		अवरोध;
	हाल 0x1A:	/* DDR4 */
	हाल 0x1E:	/* LPDDR4 */
		name = "ee1004";
		अवरोध;
	शेष:
		dev_info(&adap->dev,
			 "Memory type 0x%02x not supported yet, not instantiating SPD\n",
			 common_mem_type);
		वापस;
	पूर्ण

	/*
	 * We करोn't know in which slots the memory modules are. We could
	 * try to guess from the slot names, but that would be rather complex
	 * and unreliable, so better probe all possible addresses until we
	 * have found all memory modules.
	 */
	क्रम (n = 0; n < slot_count && dimm_count; n++) अणु
		काष्ठा i2c_board_info info;
		अचिन्हित लघु addr_list[2];

		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strlcpy(info.type, name, I2C_NAME_SIZE);
		addr_list[0] = 0x50 + n;
		addr_list[1] = I2C_CLIENT_END;

		अगर (!IS_ERR(i2c_new_scanned_device(adap, &info, addr_list, शून्य))) अणु
			dev_info(&adap->dev,
				 "Successfully instantiated SPD at 0x%hx\n",
				 addr_list[0]);
			dimm_count--;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(i2c_रेजिस्टर_spd);
#पूर्ण_अगर

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("SMBus protocol extensions support");
MODULE_LICENSE("GPL");
