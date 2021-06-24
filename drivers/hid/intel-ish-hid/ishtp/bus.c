<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ISHTP bus driver
 *
 * Copyright (c) 2012-2016, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश "bus.h"
#समावेश "ishtp-dev.h"
#समावेश "client.h"
#समावेश "hbm.h"

अटल पूर्णांक ishtp_use_dma;
module_param_named(ishtp_use_dma, ishtp_use_dma, पूर्णांक, 0600);
MODULE_PARM_DESC(ishtp_use_dma, "Use DMA to send messages");

#घोषणा to_ishtp_cl_driver(d) container_of(d, काष्ठा ishtp_cl_driver, driver)
#घोषणा to_ishtp_cl_device(d) container_of(d, काष्ठा ishtp_cl_device, dev)
अटल bool ishtp_device_पढ़ोy;

/**
 * ishtp_recv() - process ishtp message
 * @dev: ishtp device
 *
 * If a message with valid header and size is received, then
 * this function calls appropriate handler. The host or firmware
 * address is zero, then they are host bus management message,
 * otherwise they are message fo clients.
 */
व्योम ishtp_recv(काष्ठा ishtp_device *dev)
अणु
	uपूर्णांक32_t	msg_hdr;
	काष्ठा ishtp_msg_hdr	*ishtp_hdr;

	/* Read ISHTP header dword */
	msg_hdr = dev->ops->ishtp_पढ़ो_hdr(dev);
	अगर (!msg_hdr)
		वापस;

	dev->ops->sync_fw_घड़ी(dev);

	ishtp_hdr = (काष्ठा ishtp_msg_hdr *)&msg_hdr;
	dev->ishtp_msg_hdr = msg_hdr;

	/* Sanity check: ISHTP frag. length in header */
	अगर (ishtp_hdr->length > dev->mtu) अणु
		dev_err(dev->devc,
			"ISHTP hdr - bad length: %u; dropped [%08X]\n",
			(अचिन्हित पूर्णांक)ishtp_hdr->length, msg_hdr);
		वापस;
	पूर्ण

	/* ISHTP bus message */
	अगर (!ishtp_hdr->host_addr && !ishtp_hdr->fw_addr)
		recv_hbm(dev, ishtp_hdr);
	/* ISHTP fixed-client message */
	अन्यथा अगर (!ishtp_hdr->host_addr)
		recv_fixed_cl_msg(dev, ishtp_hdr);
	अन्यथा
		/* ISHTP client message */
		recv_ishtp_cl_msg(dev, ishtp_hdr);
पूर्ण
EXPORT_SYMBOL(ishtp_recv);

/**
 * ishtp_send_msg() - Send ishtp message
 * @dev: ishtp device
 * @hdr: Message header
 * @msg: Message contents
 * @ipc_send_compl: completion callback
 * @ipc_send_compl_prm: completion callback parameter
 *
 * Send a multi fragment message via IPC. After sending the first fragment
 * the completion callback is called to schedule transmit of next fragment.
 *
 * Return: This वापसs IPC send message status.
 */
पूर्णांक ishtp_send_msg(काष्ठा ishtp_device *dev, काष्ठा ishtp_msg_hdr *hdr,
		       व्योम *msg, व्योम(*ipc_send_compl)(व्योम *),
		       व्योम *ipc_send_compl_prm)
अणु
	अचिन्हित अक्षर	ipc_msg[IPC_FULL_MSG_SIZE];
	uपूर्णांक32_t	drbl_val;

	drbl_val = dev->ops->ipc_get_header(dev, hdr->length +
					    माप(काष्ठा ishtp_msg_hdr),
					    1);

	स_नकल(ipc_msg, &drbl_val, माप(uपूर्णांक32_t));
	स_नकल(ipc_msg + माप(uपूर्णांक32_t), hdr, माप(uपूर्णांक32_t));
	स_नकल(ipc_msg + 2 * माप(uपूर्णांक32_t), msg, hdr->length);
	वापस	dev->ops->ग_लिखो(dev, ipc_send_compl, ipc_send_compl_prm,
				ipc_msg, 2 * माप(uपूर्णांक32_t) + hdr->length);
पूर्ण

/**
 * ishtp_ग_लिखो_message() - Send ishtp single fragment message
 * @dev: ishtp device
 * @hdr: Message header
 * @buf: message data
 *
 * Send a single fragment message via IPC.  This वापसs IPC send message
 * status.
 *
 * Return: This वापसs IPC send message status.
 */
पूर्णांक ishtp_ग_लिखो_message(काष्ठा ishtp_device *dev, काष्ठा ishtp_msg_hdr *hdr,
			व्योम *buf)
अणु
	वापस ishtp_send_msg(dev, hdr, buf, शून्य, शून्य);
पूर्ण

/**
 * ishtp_fw_cl_by_uuid() - locate index of fw client
 * @dev: ishtp device
 * @uuid: uuid of the client to search
 *
 * Search firmware client using UUID.
 *
 * Return: fw client index or -ENOENT अगर not found
 */
पूर्णांक ishtp_fw_cl_by_uuid(काष्ठा ishtp_device *dev, स्थिर guid_t *uuid)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dev->fw_clients_num; ++i) अणु
		अगर (guid_equal(uuid, &dev->fw_clients[i].props.protocol_name))
			वापस i;
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(ishtp_fw_cl_by_uuid);

/**
 * ishtp_fw_cl_get_client() - वापस client inक्रमmation to client
 * @dev: the ishtp device काष्ठाure
 * @uuid: uuid of the client to search
 *
 * Search firmware client using UUID and reture related client inक्रमmation.
 *
 * Return: poपूर्णांकer of client inक्रमmation on success, शून्य on failure.
 */
काष्ठा ishtp_fw_client *ishtp_fw_cl_get_client(काष्ठा ishtp_device *dev,
					       स्थिर guid_t *uuid)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->fw_clients_lock, flags);
	i = ishtp_fw_cl_by_uuid(dev, uuid);
	spin_unlock_irqrestore(&dev->fw_clients_lock, flags);
	अगर (i < 0 || dev->fw_clients[i].props.fixed_address)
		वापस शून्य;

	वापस &dev->fw_clients[i];
पूर्ण
EXPORT_SYMBOL(ishtp_fw_cl_get_client);

/**
 * ishtp_get_fw_client_id() - Get fw client id
 *
 * This पूर्णांकerface is used to reset HW get FW client id.
 *
 * Return: firmware client id.
 */
पूर्णांक ishtp_get_fw_client_id(काष्ठा ishtp_fw_client *fw_client)
अणु
	वापस fw_client->client_id;
पूर्ण
EXPORT_SYMBOL(ishtp_get_fw_client_id);

/**
 * ishtp_fw_cl_by_id() - वापस index to fw_clients क्रम client_id
 * @dev: the ishtp device काष्ठाure
 * @client_id: fw client id to search
 *
 * Search firmware client using client id.
 *
 * Return: index on success, -ENOENT on failure.
 */
पूर्णांक ishtp_fw_cl_by_id(काष्ठा ishtp_device *dev, uपूर्णांक8_t client_id)
अणु
	पूर्णांक i, res = -ENOENT;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&dev->fw_clients_lock, flags);
	क्रम (i = 0; i < dev->fw_clients_num; i++) अणु
		अगर (dev->fw_clients[i].client_id == client_id) अणु
			res = i;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->fw_clients_lock, flags);

	वापस res;
पूर्ण

/**
 * ishtp_cl_device_probe() - Bus probe() callback
 * @dev: the device काष्ठाure
 *
 * This is a bus probe callback and calls the drive probe function.
 *
 * Return: Return value from driver probe() call.
 */
अटल पूर्णांक ishtp_cl_device_probe(काष्ठा device *dev)
अणु
	काष्ठा ishtp_cl_device *device = to_ishtp_cl_device(dev);
	काष्ठा ishtp_cl_driver *driver;

	अगर (!device)
		वापस 0;

	driver = to_ishtp_cl_driver(dev->driver);
	अगर (!driver || !driver->probe)
		वापस -ENODEV;

	वापस driver->probe(device);
पूर्ण

/**
 * ishtp_cl_bus_match() - Bus match() callback
 * @dev: the device काष्ठाure
 * @drv: the driver काष्ठाure
 *
 * This is a bus match callback, called when a new ishtp_cl_device is
 * रेजिस्टरed during ishtp bus client क्रमागतeration. Use the guid_t in
 * drv and dev to decide whether they match or not.
 *
 * Return: 1 अगर dev & drv matches, 0 otherwise.
 */
अटल पूर्णांक ishtp_cl_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा ishtp_cl_device *device = to_ishtp_cl_device(dev);
	काष्ठा ishtp_cl_driver *driver = to_ishtp_cl_driver(drv);

	वापस guid_equal(driver->guid,
			  &device->fw_client->props.protocol_name);
पूर्ण

/**
 * ishtp_cl_device_हटाओ() - Bus हटाओ() callback
 * @dev: the device काष्ठाure
 *
 * This is a bus हटाओ callback and calls the drive हटाओ function.
 * Since the ISH driver model supports only built in, this is
 * primarily can be called during pci driver init failure.
 *
 * Return: Return value from driver हटाओ() call.
 */
अटल पूर्णांक ishtp_cl_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ishtp_cl_device *device = to_ishtp_cl_device(dev);
	काष्ठा ishtp_cl_driver *driver;

	अगर (!device || !dev->driver)
		वापस 0;

	अगर (device->event_cb) अणु
		device->event_cb = शून्य;
		cancel_work_sync(&device->event_work);
	पूर्ण

	driver = to_ishtp_cl_driver(dev->driver);
	अगर (!driver->हटाओ) अणु
		dev->driver = शून्य;

		वापस 0;
	पूर्ण

	वापस driver->हटाओ(device);
पूर्ण

/**
 * ishtp_cl_device_suspend() - Bus suspend callback
 * @dev:	device
 *
 * Called during device suspend process.
 *
 * Return: Return value from driver suspend() call.
 */
अटल पूर्णांक ishtp_cl_device_suspend(काष्ठा device *dev)
अणु
	काष्ठा ishtp_cl_device *device = to_ishtp_cl_device(dev);
	काष्ठा ishtp_cl_driver *driver;
	पूर्णांक ret = 0;

	अगर (!device)
		वापस 0;

	driver = to_ishtp_cl_driver(dev->driver);
	अगर (driver && driver->driver.pm) अणु
		अगर (driver->driver.pm->suspend)
			ret = driver->driver.pm->suspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ishtp_cl_device_resume() - Bus resume callback
 * @dev:	device
 *
 * Called during device resume process.
 *
 * Return: Return value from driver resume() call.
 */
अटल पूर्णांक ishtp_cl_device_resume(काष्ठा device *dev)
अणु
	काष्ठा ishtp_cl_device *device = to_ishtp_cl_device(dev);
	काष्ठा ishtp_cl_driver *driver;
	पूर्णांक ret = 0;

	अगर (!device)
		वापस 0;

	/*
	 * When ISH needs hard reset, it is करोne asynchrnously, hence bus
	 * resume will  be called beक्रमe full ISH resume
	 */
	अगर (device->ishtp_dev->resume_flag)
		वापस 0;

	driver = to_ishtp_cl_driver(dev->driver);
	अगर (driver && driver->driver.pm) अणु
		अगर (driver->driver.pm->resume)
			ret = driver->driver.pm->resume(dev);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ishtp_cl_device_reset() - Reset callback
 * @device:	ishtp client device instance
 *
 * This is a callback when HW reset is करोne and the device need
 * reinit.
 *
 * Return: Return value from driver reset() call.
 */
अटल पूर्णांक ishtp_cl_device_reset(काष्ठा ishtp_cl_device *device)
अणु
	काष्ठा ishtp_cl_driver *driver;
	पूर्णांक ret = 0;

	device->event_cb = शून्य;
	cancel_work_sync(&device->event_work);

	driver = to_ishtp_cl_driver(device->dev.driver);
	अगर (driver && driver->reset)
		ret = driver->reset(device);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *a,
	अक्षर *buf)
अणु
	पूर्णांक len;

	len = snम_लिखो(buf, PAGE_SIZE, "ishtp:%s\n", dev_name(dev));
	वापस (len >= PAGE_SIZE) ? (PAGE_SIZE - 1) : len;
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *ishtp_cl_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ishtp_cl_dev);

अटल पूर्णांक ishtp_cl_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	अगर (add_uevent_var(env, "MODALIAS=ishtp:%s", dev_name(dev)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ishtp_cl_bus_dev_pm_ops = अणु
	/* Suspend callbacks */
	.suspend = ishtp_cl_device_suspend,
	.resume = ishtp_cl_device_resume,
	/* Hibernate callbacks */
	.मुक्तze = ishtp_cl_device_suspend,
	.thaw = ishtp_cl_device_resume,
	.restore = ishtp_cl_device_resume,
पूर्ण;

अटल काष्ठा bus_type ishtp_cl_bus_type = अणु
	.name		= "ishtp",
	.dev_groups	= ishtp_cl_dev_groups,
	.probe		= ishtp_cl_device_probe,
	.match		= ishtp_cl_bus_match,
	.हटाओ		= ishtp_cl_device_हटाओ,
	.pm		= &ishtp_cl_bus_dev_pm_ops,
	.uevent		= ishtp_cl_uevent,
पूर्ण;

अटल व्योम ishtp_cl_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(to_ishtp_cl_device(dev));
पूर्ण

अटल स्थिर काष्ठा device_type ishtp_cl_device_type = अणु
	.release	= ishtp_cl_dev_release,
पूर्ण;

/**
 * ishtp_bus_add_device() - Function to create device on bus
 * @dev:	ishtp device
 * @uuid:	uuid of the client
 * @name:	Name of the client
 *
 * Allocate ISHTP bus client device, attach it to uuid
 * and रेजिस्टर with ISHTP bus.
 *
 * Return: ishtp_cl_device poपूर्णांकer or शून्य on failure
 */
अटल काष्ठा ishtp_cl_device *ishtp_bus_add_device(काष्ठा ishtp_device *dev,
						    guid_t uuid, अक्षर *name)
अणु
	काष्ठा ishtp_cl_device *device;
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->device_list_lock, flags);
	list_क्रम_each_entry(device, &dev->device_list, device_link) अणु
		अगर (!म_भेद(name, dev_name(&device->dev))) अणु
			device->fw_client = &dev->fw_clients[
				dev->fw_client_presentation_num - 1];
			spin_unlock_irqrestore(&dev->device_list_lock, flags);
			ishtp_cl_device_reset(device);
			वापस device;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->device_list_lock, flags);

	device = kzalloc(माप(काष्ठा ishtp_cl_device), GFP_KERNEL);
	अगर (!device)
		वापस शून्य;

	device->dev.parent = dev->devc;
	device->dev.bus = &ishtp_cl_bus_type;
	device->dev.type = &ishtp_cl_device_type;
	device->ishtp_dev = dev;

	device->fw_client =
		&dev->fw_clients[dev->fw_client_presentation_num - 1];

	dev_set_name(&device->dev, "%s", name);

	spin_lock_irqsave(&dev->device_list_lock, flags);
	list_add_tail(&device->device_link, &dev->device_list);
	spin_unlock_irqrestore(&dev->device_list_lock, flags);

	status = device_रेजिस्टर(&device->dev);
	अगर (status) अणु
		spin_lock_irqsave(&dev->device_list_lock, flags);
		list_del(&device->device_link);
		spin_unlock_irqrestore(&dev->device_list_lock, flags);
		dev_err(dev->devc, "Failed to register ISHTP client device\n");
		put_device(&device->dev);
		वापस शून्य;
	पूर्ण

	ishtp_device_पढ़ोy = true;

	वापस device;
पूर्ण

/**
 * ishtp_bus_हटाओ_device() - Function to relase device on bus
 * @device:	client device instance
 *
 * This is a counterpart of ishtp_bus_add_device.
 * Device is unरेजिस्टरed.
 * the device काष्ठाure is मुक्तd in 'ishtp_cl_dev_release' function
 * Called only during error in pci driver init path.
 */
अटल व्योम ishtp_bus_हटाओ_device(काष्ठा ishtp_cl_device *device)
अणु
	device_unरेजिस्टर(&device->dev);
पूर्ण

/**
 * ishtp_cl_driver_रेजिस्टर() - Client driver रेजिस्टर
 * @driver:	the client driver instance
 * @owner:	Owner of this driver module
 *
 * Once a client driver is probed, it created a client
 * instance and रेजिस्टरs with the bus.
 *
 * Return: Return value of driver_रेजिस्टर or -ENODEV अगर not पढ़ोy
 */
पूर्णांक ishtp_cl_driver_रेजिस्टर(काष्ठा ishtp_cl_driver *driver,
			     काष्ठा module *owner)
अणु
	अगर (!ishtp_device_पढ़ोy)
		वापस -ENODEV;

	driver->driver.name = driver->name;
	driver->driver.owner = owner;
	driver->driver.bus = &ishtp_cl_bus_type;

	वापस driver_रेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL(ishtp_cl_driver_रेजिस्टर);

/**
 * ishtp_cl_driver_unरेजिस्टर() - Client driver unरेजिस्टर
 * @driver:	the client driver instance
 *
 * Unरेजिस्टर client during device removal process.
 */
व्योम ishtp_cl_driver_unरेजिस्टर(काष्ठा ishtp_cl_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL(ishtp_cl_driver_unरेजिस्टर);

/**
 * ishtp_bus_event_work() - event work function
 * @work:	work काष्ठा poपूर्णांकer
 *
 * Once an event is received क्रम a client this work
 * function is called. If the device has रेजिस्टरed a
 * callback then the callback is called.
 */
अटल व्योम ishtp_bus_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ishtp_cl_device *device;

	device = container_of(work, काष्ठा ishtp_cl_device, event_work);

	अगर (device->event_cb)
		device->event_cb(device);
पूर्ण

/**
 * ishtp_cl_bus_rx_event() - schedule event work
 * @device:	client device instance
 *
 * Once an event is received क्रम a client this schedules
 * a work function to process.
 */
व्योम ishtp_cl_bus_rx_event(काष्ठा ishtp_cl_device *device)
अणु
	अगर (!device || !device->event_cb)
		वापस;

	अगर (device->event_cb)
		schedule_work(&device->event_work);
पूर्ण

/**
 * ishtp_रेजिस्टर_event_cb() - Register callback
 * @device:	client device instance
 * @event_cb:	Event processor क्रम an client
 *
 * Register a callback क्रम events, called from client driver
 *
 * Return: Return 0 or -EALREADY अगर alपढ़ोy रेजिस्टरed
 */
पूर्णांक ishtp_रेजिस्टर_event_cb(काष्ठा ishtp_cl_device *device,
	व्योम (*event_cb)(काष्ठा ishtp_cl_device *))
अणु
	अगर (device->event_cb)
		वापस -EALREADY;

	device->event_cb = event_cb;
	INIT_WORK(&device->event_work, ishtp_bus_event_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ishtp_रेजिस्टर_event_cb);

/**
 * ishtp_get_device() - update usage count क्रम the device
 * @cl_device:	client device instance
 *
 * Increment the usage count. The device can't be deleted
 */
व्योम ishtp_get_device(काष्ठा ishtp_cl_device *cl_device)
अणु
	cl_device->reference_count++;
पूर्ण
EXPORT_SYMBOL(ishtp_get_device);

/**
 * ishtp_put_device() - decrement usage count क्रम the device
 * @cl_device:	client device instance
 *
 * Decrement the usage count. The device can be deleted is count = 0
 */
व्योम ishtp_put_device(काष्ठा ishtp_cl_device *cl_device)
अणु
	cl_device->reference_count--;
पूर्ण
EXPORT_SYMBOL(ishtp_put_device);

/**
 * ishtp_set_drvdata() - set client driver data
 * @cl_device:	client device instance
 * @data:	driver data need to be set
 *
 * Set client driver data to cl_device->driver_data.
 */
व्योम ishtp_set_drvdata(काष्ठा ishtp_cl_device *cl_device, व्योम *data)
अणु
	cl_device->driver_data = data;
पूर्ण
EXPORT_SYMBOL(ishtp_set_drvdata);

/**
 * ishtp_get_drvdata() - get client driver data
 * @cl_device:	client device instance
 *
 * Get client driver data from cl_device->driver_data.
 *
 * Return: poपूर्णांकer of driver data
 */
व्योम *ishtp_get_drvdata(काष्ठा ishtp_cl_device *cl_device)
अणु
	वापस cl_device->driver_data;
पूर्ण
EXPORT_SYMBOL(ishtp_get_drvdata);

/**
 * ishtp_dev_to_cl_device() - get ishtp_cl_device instance from device instance
 * @device: device instance
 *
 * Get ish_cl_device instance which embeds device instance in it.
 *
 * Return: poपूर्णांकer to ishtp_cl_device instance
 */
काष्ठा ishtp_cl_device *ishtp_dev_to_cl_device(काष्ठा device *device)
अणु
	वापस to_ishtp_cl_device(device);
पूर्ण
EXPORT_SYMBOL(ishtp_dev_to_cl_device);

/**
 * ishtp_bus_new_client() - Create a new client
 * @dev:	ISHTP device instance
 *
 * Once bus protocol क्रमागतerates a client, this is called
 * to add a device क्रम the client.
 *
 * Return: 0 on success or error code on failure
 */
पूर्णांक ishtp_bus_new_client(काष्ठा ishtp_device *dev)
अणु
	पूर्णांक	i;
	अक्षर	*dev_name;
	काष्ठा ishtp_cl_device	*cl_device;
	guid_t	device_uuid;

	/*
	 * For all reported clients, create an unconnected client and add its
	 * device to ISHTP bus.
	 * If appropriate driver has loaded, this will trigger its probe().
	 * Otherwise, probe() will be called when driver is loaded
	 */
	i = dev->fw_client_presentation_num - 1;
	device_uuid = dev->fw_clients[i].props.protocol_name;
	dev_name = kaप्र_लिखो(GFP_KERNEL, "{%pUL}", &device_uuid);
	अगर (!dev_name)
		वापस	-ENOMEM;

	cl_device = ishtp_bus_add_device(dev, device_uuid, dev_name);
	अगर (!cl_device) अणु
		kमुक्त(dev_name);
		वापस	-ENOENT;
	पूर्ण

	kमुक्त(dev_name);

	वापस	0;
पूर्ण

/**
 * ishtp_cl_device_bind() - bind a device
 * @cl:		ishtp client device
 *
 * Binds connected ishtp_cl to ISHTP bus device
 *
 * Return: 0 on success or fault code
 */
पूर्णांक ishtp_cl_device_bind(काष्ठा ishtp_cl *cl)
अणु
	काष्ठा ishtp_cl_device	*cl_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक	rv;

	अगर (!cl->fw_client_id || cl->state != ISHTP_CL_CONNECTED)
		वापस	-EFAULT;

	rv = -ENOENT;
	spin_lock_irqsave(&cl->dev->device_list_lock, flags);
	list_क्रम_each_entry(cl_device, &cl->dev->device_list,
			device_link) अणु
		अगर (cl_device->fw_client &&
		    cl_device->fw_client->client_id == cl->fw_client_id) अणु
			cl->device = cl_device;
			rv = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cl->dev->device_list_lock, flags);
	वापस	rv;
पूर्ण

/**
 * ishtp_bus_हटाओ_all_clients() - Remove all clients
 * @ishtp_dev:		ishtp device
 * @warm_reset:		Reset due to FW reset dure to errors or S3 suspend
 *
 * This is part of reset/हटाओ flow. This function the मुख्य processing
 * only tarमाला_लो error processing, अगर the FW has क्रमced reset or
 * error to हटाओ connected clients. When warm reset the client devices are
 * not हटाओd.
 */
व्योम ishtp_bus_हटाओ_all_clients(काष्ठा ishtp_device *ishtp_dev,
				  bool warm_reset)
अणु
	काष्ठा ishtp_cl_device	*cl_device, *n;
	काष्ठा ishtp_cl	*cl;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&ishtp_dev->cl_list_lock, flags);
	list_क्रम_each_entry(cl, &ishtp_dev->cl_list, link) अणु
		cl->state = ISHTP_CL_DISCONNECTED;

		/*
		 * Wake any pending process. The रुकोer would check dev->state
		 * and determine that it's not enabled alपढ़ोy,
		 * and will वापस error to its caller
		 */
		wake_up_पूर्णांकerruptible(&cl->रुको_ctrl_res);

		/* Disband any pending पढ़ो/ग_लिखो requests and मुक्त rb */
		ishtp_cl_flush_queues(cl);

		/* Remove all मुक्त and in_process rings, both Rx and Tx */
		ishtp_cl_मुक्त_rx_ring(cl);
		ishtp_cl_मुक्त_tx_ring(cl);

		/*
		 * Free client and ISHTP bus client device काष्ठाures
		 * करोn't मुक्त host client because it is part of the OS fd
		 * काष्ठाure
		 */
	पूर्ण
	spin_unlock_irqrestore(&ishtp_dev->cl_list_lock, flags);

	/* Release DMA buffers क्रम client messages */
	ishtp_cl_मुक्त_dma_buf(ishtp_dev);

	/* हटाओ bus clients */
	spin_lock_irqsave(&ishtp_dev->device_list_lock, flags);
	list_क्रम_each_entry_safe(cl_device, n, &ishtp_dev->device_list,
				 device_link) अणु
		cl_device->fw_client = शून्य;
		अगर (warm_reset && cl_device->reference_count)
			जारी;

		list_del(&cl_device->device_link);
		spin_unlock_irqrestore(&ishtp_dev->device_list_lock, flags);
		ishtp_bus_हटाओ_device(cl_device);
		spin_lock_irqsave(&ishtp_dev->device_list_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ishtp_dev->device_list_lock, flags);

	/* Free all client काष्ठाures */
	spin_lock_irqsave(&ishtp_dev->fw_clients_lock, flags);
	kमुक्त(ishtp_dev->fw_clients);
	ishtp_dev->fw_clients = शून्य;
	ishtp_dev->fw_clients_num = 0;
	ishtp_dev->fw_client_presentation_num = 0;
	ishtp_dev->fw_client_index = 0;
	biपंचांगap_zero(ishtp_dev->fw_clients_map, ISHTP_CLIENTS_MAX);
	spin_unlock_irqrestore(&ishtp_dev->fw_clients_lock, flags);
पूर्ण
EXPORT_SYMBOL(ishtp_bus_हटाओ_all_clients);

/**
 * ishtp_reset_handler() - IPC reset handler
 * @dev:	ishtp device
 *
 * ISHTP Handler क्रम IPC_RESET notअगरication
 */
व्योम ishtp_reset_handler(काष्ठा ishtp_device *dev)
अणु
	अचिन्हित दीर्घ	flags;

	/* Handle FW-initiated reset */
	dev->dev_state = ISHTP_DEV_RESETTING;

	/* Clear BH processing queue - no further HBMs */
	spin_lock_irqsave(&dev->rd_msg_spinlock, flags);
	dev->rd_msg_fअगरo_head = dev->rd_msg_fअगरo_tail = 0;
	spin_unlock_irqrestore(&dev->rd_msg_spinlock, flags);

	/* Handle ISH FW reset against upper layers */
	ishtp_bus_हटाओ_all_clients(dev, true);
पूर्ण
EXPORT_SYMBOL(ishtp_reset_handler);

/**
 * ishtp_reset_compl_handler() - Reset completion handler
 * @dev:	ishtp device
 *
 * ISHTP handler क्रम IPC_RESET sequence completion to start
 * host message bus start protocol sequence.
 */
व्योम ishtp_reset_compl_handler(काष्ठा ishtp_device *dev)
अणु
	dev->dev_state = ISHTP_DEV_INIT_CLIENTS;
	dev->hbm_state = ISHTP_HBM_START;
	ishtp_hbm_start_req(dev);
पूर्ण
EXPORT_SYMBOL(ishtp_reset_compl_handler);

/**
 * ishtp_use_dma_transfer() - Function to use DMA
 *
 * This पूर्णांकerface is used to enable usage of DMA
 *
 * Return non zero अगर DMA can be enabled
 */
पूर्णांक ishtp_use_dma_transfer(व्योम)
अणु
	वापस ishtp_use_dma;
पूर्ण

/**
 * ishtp_device() - Return device poपूर्णांकer
 *
 * This पूर्णांकerface is used to वापस device poपूर्णांकer from ishtp_cl_device
 * instance.
 *
 * Return: device *.
 */
काष्ठा device *ishtp_device(काष्ठा ishtp_cl_device *device)
अणु
	वापस &device->dev;
पूर्ण
EXPORT_SYMBOL(ishtp_device);

/**
 * ishtp_get_pci_device() - Return PCI device dev poपूर्णांकer
 * This पूर्णांकerface is used to वापस PCI device poपूर्णांकer
 * from ishtp_cl_device instance.
 *
 * Return: device *.
 */
काष्ठा device *ishtp_get_pci_device(काष्ठा ishtp_cl_device *device)
अणु
	वापस device->ishtp_dev->devc;
पूर्ण
EXPORT_SYMBOL(ishtp_get_pci_device);

/**
 * ishtp_trace_callback() - Return trace callback
 *
 * This पूर्णांकerface is used to वापस trace callback function poपूर्णांकer.
 *
 * Return: व्योम *.
 */
व्योम *ishtp_trace_callback(काष्ठा ishtp_cl_device *cl_device)
अणु
	वापस cl_device->ishtp_dev->prपूर्णांक_log;
पूर्ण
EXPORT_SYMBOL(ishtp_trace_callback);

/**
 * ish_hw_reset() - Call HW reset IPC callback
 *
 * This पूर्णांकerface is used to reset HW in हाल of error.
 *
 * Return: value from IPC hw_reset callback
 */
पूर्णांक ish_hw_reset(काष्ठा ishtp_device *dev)
अणु
	वापस dev->ops->hw_reset(dev);
पूर्ण
EXPORT_SYMBOL(ish_hw_reset);

/**
 * ishtp_bus_रेजिस्टर() - Function to रेजिस्टर bus
 *
 * This रेजिस्टर ishtp bus
 *
 * Return: Return output of bus_रेजिस्टर
 */
अटल पूर्णांक  __init ishtp_bus_रेजिस्टर(व्योम)
अणु
	वापस bus_रेजिस्टर(&ishtp_cl_bus_type);
पूर्ण

/**
 * ishtp_bus_unरेजिस्टर() - Function to unरेजिस्टर bus
 *
 * This unरेजिस्टर ishtp bus
 */
अटल व्योम __निकास ishtp_bus_unरेजिस्टर(व्योम)
अणु
	bus_unरेजिस्टर(&ishtp_cl_bus_type);
पूर्ण

module_init(ishtp_bus_रेजिस्टर);
module_निकास(ishtp_bus_unरेजिस्टर);

MODULE_LICENSE("GPL");
