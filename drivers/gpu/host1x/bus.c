<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012-2013, NVIDIA Corporation
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/host1x.h>
#समावेश <linux/of.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>

#समावेश "bus.h"
#समावेश "dev.h"

अटल DEFINE_MUTEX(clients_lock);
अटल LIST_HEAD(clients);

अटल DEFINE_MUTEX(drivers_lock);
अटल LIST_HEAD(drivers);

अटल DEFINE_MUTEX(devices_lock);
अटल LIST_HEAD(devices);

काष्ठा host1x_subdev अणु
	काष्ठा host1x_client *client;
	काष्ठा device_node *np;
	काष्ठा list_head list;
पूर्ण;

/**
 * host1x_subdev_add() - add a new subdevice with an associated device node
 * @device: host1x device to add the subdevice to
 * @driver: host1x driver containing the subdevices
 * @np: device node
 */
अटल पूर्णांक host1x_subdev_add(काष्ठा host1x_device *device,
			     काष्ठा host1x_driver *driver,
			     काष्ठा device_node *np)
अणु
	काष्ठा host1x_subdev *subdev;
	काष्ठा device_node *child;
	पूर्णांक err;

	subdev = kzalloc(माप(*subdev), GFP_KERNEL);
	अगर (!subdev)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&subdev->list);
	subdev->np = of_node_get(np);

	mutex_lock(&device->subdevs_lock);
	list_add_tail(&subdev->list, &device->subdevs);
	mutex_unlock(&device->subdevs_lock);

	/* recursively add children */
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_match_node(driver->subdevs, child) &&
		    of_device_is_available(child)) अणु
			err = host1x_subdev_add(device, driver, child);
			अगर (err < 0) अणु
				/* XXX cleanup? */
				of_node_put(child);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * host1x_subdev_del() - हटाओ subdevice
 * @subdev: subdevice to हटाओ
 */
अटल व्योम host1x_subdev_del(काष्ठा host1x_subdev *subdev)
अणु
	list_del(&subdev->list);
	of_node_put(subdev->np);
	kमुक्त(subdev);
पूर्ण

/**
 * host1x_device_parse_dt() - scan device tree and add matching subdevices
 * @device: host1x logical device
 * @driver: host1x driver
 */
अटल पूर्णांक host1x_device_parse_dt(काष्ठा host1x_device *device,
				  काष्ठा host1x_driver *driver)
अणु
	काष्ठा device_node *np;
	पूर्णांक err;

	क्रम_each_child_of_node(device->dev.parent->of_node, np) अणु
		अगर (of_match_node(driver->subdevs, np) &&
		    of_device_is_available(np)) अणु
			err = host1x_subdev_add(device, driver, np);
			अगर (err < 0) अणु
				of_node_put(np);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम host1x_subdev_रेजिस्टर(काष्ठा host1x_device *device,
				   काष्ठा host1x_subdev *subdev,
				   काष्ठा host1x_client *client)
अणु
	पूर्णांक err;

	/*
	 * Move the subdevice to the list of active (रेजिस्टरed) subdevices
	 * and associate it with a client. At the same समय, associate the
	 * client with its parent device.
	 */
	mutex_lock(&device->subdevs_lock);
	mutex_lock(&device->clients_lock);
	list_move_tail(&client->list, &device->clients);
	list_move_tail(&subdev->list, &device->active);
	client->host = &device->dev;
	subdev->client = client;
	mutex_unlock(&device->clients_lock);
	mutex_unlock(&device->subdevs_lock);

	अगर (list_empty(&device->subdevs)) अणु
		err = device_add(&device->dev);
		अगर (err < 0)
			dev_err(&device->dev, "failed to add: %d\n", err);
		अन्यथा
			device->रेजिस्टरed = true;
	पूर्ण
पूर्ण

अटल व्योम __host1x_subdev_unरेजिस्टर(काष्ठा host1x_device *device,
				       काष्ठा host1x_subdev *subdev)
अणु
	काष्ठा host1x_client *client = subdev->client;

	/*
	 * If all subdevices have been activated, we're about to हटाओ the
	 * first active subdevice, so unload the driver first.
	 */
	अगर (list_empty(&device->subdevs)) अणु
		अगर (device->रेजिस्टरed) अणु
			device->रेजिस्टरed = false;
			device_del(&device->dev);
		पूर्ण
	पूर्ण

	/*
	 * Move the subdevice back to the list of idle subdevices and हटाओ
	 * it from list of clients.
	 */
	mutex_lock(&device->clients_lock);
	subdev->client = शून्य;
	client->host = शून्य;
	list_move_tail(&subdev->list, &device->subdevs);
	/*
	 * XXX: Perhaps करोn't करो this here, but rather explicitly हटाओ it
	 * when the device is about to be deleted.
	 *
	 * This is somewhat complicated by the fact that this function is
	 * used to हटाओ the subdevice when a client is unरेजिस्टरed but
	 * also when the composite device is about to be हटाओd.
	 */
	list_del_init(&client->list);
	mutex_unlock(&device->clients_lock);
पूर्ण

अटल व्योम host1x_subdev_unरेजिस्टर(काष्ठा host1x_device *device,
				     काष्ठा host1x_subdev *subdev)
अणु
	mutex_lock(&device->subdevs_lock);
	__host1x_subdev_unरेजिस्टर(device, subdev);
	mutex_unlock(&device->subdevs_lock);
पूर्ण

/**
 * host1x_device_init() - initialize a host1x logical device
 * @device: host1x logical device
 *
 * The driver क्रम the host1x logical device can call this during execution of
 * its &host1x_driver.probe implementation to initialize each of its clients.
 * The client drivers access the subप्रणाली specअगरic driver data using the
 * &host1x_client.parent field and driver data associated with it (usually by
 * calling dev_get_drvdata()).
 */
पूर्णांक host1x_device_init(काष्ठा host1x_device *device)
अणु
	काष्ठा host1x_client *client;
	पूर्णांक err;

	mutex_lock(&device->clients_lock);

	list_क्रम_each_entry(client, &device->clients, list) अणु
		अगर (client->ops && client->ops->early_init) अणु
			err = client->ops->early_init(client);
			अगर (err < 0) अणु
				dev_err(&device->dev, "failed to early initialize %s: %d\n",
					dev_name(client->dev), err);
				जाओ tearकरोwn_late;
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(client, &device->clients, list) अणु
		अगर (client->ops && client->ops->init) अणु
			err = client->ops->init(client);
			अगर (err < 0) अणु
				dev_err(&device->dev,
					"failed to initialize %s: %d\n",
					dev_name(client->dev), err);
				जाओ tearकरोwn;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&device->clients_lock);

	वापस 0;

tearकरोwn:
	list_क्रम_each_entry_जारी_reverse(client, &device->clients, list)
		अगर (client->ops->निकास)
			client->ops->निकास(client);

	/* reset client to end of list क्रम late tearकरोwn */
	client = list_entry(&device->clients, काष्ठा host1x_client, list);

tearकरोwn_late:
	list_क्रम_each_entry_जारी_reverse(client, &device->clients, list)
		अगर (client->ops->late_निकास)
			client->ops->late_निकास(client);

	mutex_unlock(&device->clients_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(host1x_device_init);

/**
 * host1x_device_निकास() - uninitialize host1x logical device
 * @device: host1x logical device
 *
 * When the driver क्रम a host1x logical device is unloaded, it can call this
 * function to tear करोwn each of its clients. Typically this is करोne after a
 * subप्रणाली-specअगरic data काष्ठाure is हटाओd and the functionality can no
 * दीर्घer be used.
 */
पूर्णांक host1x_device_निकास(काष्ठा host1x_device *device)
अणु
	काष्ठा host1x_client *client;
	पूर्णांक err;

	mutex_lock(&device->clients_lock);

	list_क्रम_each_entry_reverse(client, &device->clients, list) अणु
		अगर (client->ops && client->ops->निकास) अणु
			err = client->ops->निकास(client);
			अगर (err < 0) अणु
				dev_err(&device->dev,
					"failed to cleanup %s: %d\n",
					dev_name(client->dev), err);
				mutex_unlock(&device->clients_lock);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_reverse(client, &device->clients, list) अणु
		अगर (client->ops && client->ops->late_निकास) अणु
			err = client->ops->late_निकास(client);
			अगर (err < 0) अणु
				dev_err(&device->dev, "failed to late cleanup %s: %d\n",
					dev_name(client->dev), err);
				mutex_unlock(&device->clients_lock);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&device->clients_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(host1x_device_निकास);

अटल पूर्णांक host1x_add_client(काष्ठा host1x *host1x,
			     काष्ठा host1x_client *client)
अणु
	काष्ठा host1x_device *device;
	काष्ठा host1x_subdev *subdev;

	mutex_lock(&host1x->devices_lock);

	list_क्रम_each_entry(device, &host1x->devices, list) अणु
		list_क्रम_each_entry(subdev, &device->subdevs, list) अणु
			अगर (subdev->np == client->dev->of_node) अणु
				host1x_subdev_रेजिस्टर(device, subdev, client);
				mutex_unlock(&host1x->devices_lock);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&host1x->devices_lock);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक host1x_del_client(काष्ठा host1x *host1x,
			     काष्ठा host1x_client *client)
अणु
	काष्ठा host1x_device *device, *dt;
	काष्ठा host1x_subdev *subdev;

	mutex_lock(&host1x->devices_lock);

	list_क्रम_each_entry_safe(device, dt, &host1x->devices, list) अणु
		list_क्रम_each_entry(subdev, &device->active, list) अणु
			अगर (subdev->client == client) अणु
				host1x_subdev_unरेजिस्टर(device, subdev);
				mutex_unlock(&host1x->devices_lock);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&host1x->devices_lock);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक host1x_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस म_भेद(dev_name(dev), drv->name) == 0;
पूर्ण

अटल पूर्णांक host1x_device_uevent(काष्ठा device *dev,
				काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा device_node *np = dev->parent->of_node;
	अचिन्हित पूर्णांक count = 0;
	काष्ठा property *p;
	स्थिर अक्षर *compat;

	/*
	 * This duplicates most of of_device_uevent(), but the latter cannot
	 * be called from modules and operates on dev->of_node, which is not
	 * available in this हाल.
	 *
	 * Note that this is really only needed क्रम backwards compatibility
	 * with libdrm, which parses this inक्रमmation from sysfs and will
	 * fail अगर it can't find the OF_FULLNAME, specअगरically.
	 */
	add_uevent_var(env, "OF_NAME=%pOFn", np);
	add_uevent_var(env, "OF_FULLNAME=%pOF", np);

	of_property_क्रम_each_string(np, "compatible", p, compat) अणु
		add_uevent_var(env, "OF_COMPATIBLE_%u=%s", count, compat);
		count++;
	पूर्ण

	add_uevent_var(env, "OF_COMPATIBLE_N=%u", count);

	वापस 0;
पूर्ण

अटल पूर्णांक host1x_dma_configure(काष्ठा device *dev)
अणु
	वापस of_dma_configure(dev, dev->of_node, true);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops host1x_device_pm_ops = अणु
	.suspend = pm_generic_suspend,
	.resume = pm_generic_resume,
	.मुक्तze = pm_generic_मुक्तze,
	.thaw = pm_generic_thaw,
	.घातeroff = pm_generic_घातeroff,
	.restore = pm_generic_restore,
पूर्ण;

काष्ठा bus_type host1x_bus_type = अणु
	.name = "host1x",
	.match = host1x_device_match,
	.uevent = host1x_device_uevent,
	.dma_configure = host1x_dma_configure,
	.pm = &host1x_device_pm_ops,
पूर्ण;

अटल व्योम __host1x_device_del(काष्ठा host1x_device *device)
अणु
	काष्ठा host1x_subdev *subdev, *sd;
	काष्ठा host1x_client *client, *cl;

	mutex_lock(&device->subdevs_lock);

	/* unरेजिस्टर subdevices */
	list_क्रम_each_entry_safe(subdev, sd, &device->active, list) अणु
		/*
		 * host1x_subdev_unरेजिस्टर() will हटाओ the client from
		 * any lists, so we'll need to manually add it back to the
		 * list of idle clients.
		 *
		 * XXX: Alternatively, perhaps करोn't हटाओ the client from
		 * any lists in host1x_subdev_unरेजिस्टर() and instead करो
		 * that explicitly from host1x_unरेजिस्टर_client()?
		 */
		client = subdev->client;

		__host1x_subdev_unरेजिस्टर(device, subdev);

		/* add the client to the list of idle clients */
		mutex_lock(&clients_lock);
		list_add_tail(&client->list, &clients);
		mutex_unlock(&clients_lock);
	पूर्ण

	/* हटाओ subdevices */
	list_क्रम_each_entry_safe(subdev, sd, &device->subdevs, list)
		host1x_subdev_del(subdev);

	mutex_unlock(&device->subdevs_lock);

	/* move clients to idle list */
	mutex_lock(&clients_lock);
	mutex_lock(&device->clients_lock);

	list_क्रम_each_entry_safe(client, cl, &device->clients, list)
		list_move_tail(&client->list, &clients);

	mutex_unlock(&device->clients_lock);
	mutex_unlock(&clients_lock);

	/* finally हटाओ the device */
	list_del_init(&device->list);
पूर्ण

अटल व्योम host1x_device_release(काष्ठा device *dev)
अणु
	काष्ठा host1x_device *device = to_host1x_device(dev);

	__host1x_device_del(device);
	kमुक्त(device);
पूर्ण

अटल पूर्णांक host1x_device_add(काष्ठा host1x *host1x,
			     काष्ठा host1x_driver *driver)
अणु
	काष्ठा host1x_client *client, *पंचांगp;
	काष्ठा host1x_subdev *subdev;
	काष्ठा host1x_device *device;
	पूर्णांक err;

	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (!device)
		वापस -ENOMEM;

	device_initialize(&device->dev);

	mutex_init(&device->subdevs_lock);
	INIT_LIST_HEAD(&device->subdevs);
	INIT_LIST_HEAD(&device->active);
	mutex_init(&device->clients_lock);
	INIT_LIST_HEAD(&device->clients);
	INIT_LIST_HEAD(&device->list);
	device->driver = driver;

	device->dev.coherent_dma_mask = host1x->dev->coherent_dma_mask;
	device->dev.dma_mask = &device->dev.coherent_dma_mask;
	dev_set_name(&device->dev, "%s", driver->driver.name);
	device->dev.release = host1x_device_release;
	device->dev.bus = &host1x_bus_type;
	device->dev.parent = host1x->dev;

	of_dma_configure(&device->dev, host1x->dev->of_node, true);

	device->dev.dma_parms = &device->dma_parms;
	dma_set_max_seg_size(&device->dev, अच_पूर्णांक_उच्च);

	err = host1x_device_parse_dt(device, driver);
	अगर (err < 0) अणु
		kमुक्त(device);
		वापस err;
	पूर्ण

	list_add_tail(&device->list, &host1x->devices);

	mutex_lock(&clients_lock);

	list_क्रम_each_entry_safe(client, पंचांगp, &clients, list) अणु
		list_क्रम_each_entry(subdev, &device->subdevs, list) अणु
			अगर (subdev->np == client->dev->of_node) अणु
				host1x_subdev_रेजिस्टर(device, subdev, client);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&clients_lock);

	वापस 0;
पूर्ण

/*
 * Removes a device by first unरेजिस्टरing any subdevices and then removing
 * itself from the list of devices.
 *
 * This function must be called with the host1x->devices_lock held.
 */
अटल व्योम host1x_device_del(काष्ठा host1x *host1x,
			      काष्ठा host1x_device *device)
अणु
	अगर (device->रेजिस्टरed) अणु
		device->रेजिस्टरed = false;
		device_del(&device->dev);
	पूर्ण

	put_device(&device->dev);
पूर्ण

अटल व्योम host1x_attach_driver(काष्ठा host1x *host1x,
				 काष्ठा host1x_driver *driver)
अणु
	काष्ठा host1x_device *device;
	पूर्णांक err;

	mutex_lock(&host1x->devices_lock);

	list_क्रम_each_entry(device, &host1x->devices, list) अणु
		अगर (device->driver == driver) अणु
			mutex_unlock(&host1x->devices_lock);
			वापस;
		पूर्ण
	पूर्ण

	err = host1x_device_add(host1x, driver);
	अगर (err < 0)
		dev_err(host1x->dev, "failed to allocate device: %d\n", err);

	mutex_unlock(&host1x->devices_lock);
पूर्ण

अटल व्योम host1x_detach_driver(काष्ठा host1x *host1x,
				 काष्ठा host1x_driver *driver)
अणु
	काष्ठा host1x_device *device, *पंचांगp;

	mutex_lock(&host1x->devices_lock);

	list_क्रम_each_entry_safe(device, पंचांगp, &host1x->devices, list)
		अगर (device->driver == driver)
			host1x_device_del(host1x, device);

	mutex_unlock(&host1x->devices_lock);
पूर्ण

अटल पूर्णांक host1x_devices_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा host1x *host1x = s->निजी;
	काष्ठा host1x_device *device;

	mutex_lock(&host1x->devices_lock);

	list_क्रम_each_entry(device, &host1x->devices, list) अणु
		काष्ठा host1x_subdev *subdev;

		seq_म_लिखो(s, "%s\n", dev_name(&device->dev));

		mutex_lock(&device->subdevs_lock);

		list_क्रम_each_entry(subdev, &device->active, list)
			seq_म_लिखो(s, "  %pOFf: %s\n", subdev->np,
				   dev_name(subdev->client->dev));

		list_क्रम_each_entry(subdev, &device->subdevs, list)
			seq_म_लिखो(s, "  %pOFf:\n", subdev->np);

		mutex_unlock(&device->subdevs_lock);
	पूर्ण

	mutex_unlock(&host1x->devices_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(host1x_devices);

/**
 * host1x_रेजिस्टर() - रेजिस्टर a host1x controller
 * @host1x: host1x controller
 *
 * The host1x controller driver uses this to रेजिस्टर a host1x controller with
 * the infraकाष्ठाure. Note that all Tegra SoC generations have only ever come
 * with a single host1x instance, so this function is somewhat academic.
 */
पूर्णांक host1x_रेजिस्टर(काष्ठा host1x *host1x)
अणु
	काष्ठा host1x_driver *driver;

	mutex_lock(&devices_lock);
	list_add_tail(&host1x->list, &devices);
	mutex_unlock(&devices_lock);

	mutex_lock(&drivers_lock);

	list_क्रम_each_entry(driver, &drivers, list)
		host1x_attach_driver(host1x, driver);

	mutex_unlock(&drivers_lock);

	debugfs_create_file("devices", S_IRUGO, host1x->debugfs, host1x,
			    &host1x_devices_fops);

	वापस 0;
पूर्ण

/**
 * host1x_unरेजिस्टर() - unरेजिस्टर a host1x controller
 * @host1x: host1x controller
 *
 * The host1x controller driver uses this to हटाओ a host1x controller from
 * the infraकाष्ठाure.
 */
पूर्णांक host1x_unरेजिस्टर(काष्ठा host1x *host1x)
अणु
	काष्ठा host1x_driver *driver;

	mutex_lock(&drivers_lock);

	list_क्रम_each_entry(driver, &drivers, list)
		host1x_detach_driver(host1x, driver);

	mutex_unlock(&drivers_lock);

	mutex_lock(&devices_lock);
	list_del_init(&host1x->list);
	mutex_unlock(&devices_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक host1x_device_probe(काष्ठा device *dev)
अणु
	काष्ठा host1x_driver *driver = to_host1x_driver(dev->driver);
	काष्ठा host1x_device *device = to_host1x_device(dev);

	अगर (driver->probe)
		वापस driver->probe(device);

	वापस 0;
पूर्ण

अटल पूर्णांक host1x_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा host1x_driver *driver = to_host1x_driver(dev->driver);
	काष्ठा host1x_device *device = to_host1x_device(dev);

	अगर (driver->हटाओ)
		वापस driver->हटाओ(device);

	वापस 0;
पूर्ण

अटल व्योम host1x_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा host1x_driver *driver = to_host1x_driver(dev->driver);
	काष्ठा host1x_device *device = to_host1x_device(dev);

	अगर (driver->shutकरोwn)
		driver->shutकरोwn(device);
पूर्ण

/**
 * host1x_driver_रेजिस्टर_full() - रेजिस्टर a host1x driver
 * @driver: host1x driver
 * @owner: owner module
 *
 * Drivers क्रम host1x logical devices call this function to रेजिस्टर a driver
 * with the infraकाष्ठाure. Note that since these drive logical devices, the
 * registration of the driver actually triggers tho logical device creation.
 * A logical device will be created क्रम each host1x instance.
 */
पूर्णांक host1x_driver_रेजिस्टर_full(काष्ठा host1x_driver *driver,
				काष्ठा module *owner)
अणु
	काष्ठा host1x *host1x;

	INIT_LIST_HEAD(&driver->list);

	mutex_lock(&drivers_lock);
	list_add_tail(&driver->list, &drivers);
	mutex_unlock(&drivers_lock);

	mutex_lock(&devices_lock);

	list_क्रम_each_entry(host1x, &devices, list)
		host1x_attach_driver(host1x, driver);

	mutex_unlock(&devices_lock);

	driver->driver.bus = &host1x_bus_type;
	driver->driver.owner = owner;
	driver->driver.probe = host1x_device_probe;
	driver->driver.हटाओ = host1x_device_हटाओ;
	driver->driver.shutकरोwn = host1x_device_shutकरोwn;

	वापस driver_रेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL(host1x_driver_रेजिस्टर_full);

/**
 * host1x_driver_unरेजिस्टर() - unरेजिस्टर a host1x driver
 * @driver: host1x driver
 *
 * Unbinds the driver from each of the host1x logical devices that it is
 * bound to, effectively removing the subप्रणाली devices that they represent.
 */
व्योम host1x_driver_unरेजिस्टर(काष्ठा host1x_driver *driver)
अणु
	काष्ठा host1x *host1x;

	driver_unरेजिस्टर(&driver->driver);

	mutex_lock(&devices_lock);

	list_क्रम_each_entry(host1x, &devices, list)
		host1x_detach_driver(host1x, driver);

	mutex_unlock(&devices_lock);

	mutex_lock(&drivers_lock);
	list_del_init(&driver->list);
	mutex_unlock(&drivers_lock);
पूर्ण
EXPORT_SYMBOL(host1x_driver_unरेजिस्टर);

/**
 * __host1x_client_init() - initialize a host1x client
 * @client: host1x client
 * @key: lock class key क्रम the client-specअगरic mutex
 */
व्योम __host1x_client_init(काष्ठा host1x_client *client, काष्ठा lock_class_key *key)
अणु
	INIT_LIST_HEAD(&client->list);
	__mutex_init(&client->lock, "host1x client lock", key);
	client->usecount = 0;
पूर्ण
EXPORT_SYMBOL(__host1x_client_init);

/**
 * host1x_client_निकास() - uninitialize a host1x client
 * @client: host1x client
 */
व्योम host1x_client_निकास(काष्ठा host1x_client *client)
अणु
	mutex_destroy(&client->lock);
पूर्ण
EXPORT_SYMBOL(host1x_client_निकास);

/**
 * __host1x_client_रेजिस्टर() - रेजिस्टर a host1x client
 * @client: host1x client
 * @key: lock class key क्रम the client-specअगरic mutex
 *
 * Registers a host1x client with each host1x controller instance. Note that
 * each client will only match their parent host1x controller and will only be
 * associated with that instance. Once all clients have been रेजिस्टरed with
 * their parent host1x controller, the infraकाष्ठाure will set up the logical
 * device and call host1x_device_init(), which will in turn call each client's
 * &host1x_client_ops.init implementation.
 */
पूर्णांक __host1x_client_रेजिस्टर(काष्ठा host1x_client *client)
अणु
	काष्ठा host1x *host1x;
	पूर्णांक err;

	mutex_lock(&devices_lock);

	list_क्रम_each_entry(host1x, &devices, list) अणु
		err = host1x_add_client(host1x, client);
		अगर (!err) अणु
			mutex_unlock(&devices_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&devices_lock);

	mutex_lock(&clients_lock);
	list_add_tail(&client->list, &clients);
	mutex_unlock(&clients_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__host1x_client_रेजिस्टर);

/**
 * host1x_client_unरेजिस्टर() - unरेजिस्टर a host1x client
 * @client: host1x client
 *
 * Removes a host1x client from its host1x controller instance. If a logical
 * device has alपढ़ोy been initialized, it will be torn करोwn.
 */
पूर्णांक host1x_client_unरेजिस्टर(काष्ठा host1x_client *client)
अणु
	काष्ठा host1x_client *c;
	काष्ठा host1x *host1x;
	पूर्णांक err;

	mutex_lock(&devices_lock);

	list_क्रम_each_entry(host1x, &devices, list) अणु
		err = host1x_del_client(host1x, client);
		अगर (!err) अणु
			mutex_unlock(&devices_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&devices_lock);
	mutex_lock(&clients_lock);

	list_क्रम_each_entry(c, &clients, list) अणु
		अगर (c == client) अणु
			list_del_init(&c->list);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&clients_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(host1x_client_unरेजिस्टर);

पूर्णांक host1x_client_suspend(काष्ठा host1x_client *client)
अणु
	पूर्णांक err = 0;

	mutex_lock(&client->lock);

	अगर (client->usecount == 1) अणु
		अगर (client->ops && client->ops->suspend) अणु
			err = client->ops->suspend(client);
			अगर (err < 0)
				जाओ unlock;
		पूर्ण
	पूर्ण

	client->usecount--;
	dev_dbg(client->dev, "use count: %u\n", client->usecount);

	अगर (client->parent) अणु
		err = host1x_client_suspend(client->parent);
		अगर (err < 0)
			जाओ resume;
	पूर्ण

	जाओ unlock;

resume:
	अगर (client->usecount == 0)
		अगर (client->ops && client->ops->resume)
			client->ops->resume(client);

	client->usecount++;
unlock:
	mutex_unlock(&client->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(host1x_client_suspend);

पूर्णांक host1x_client_resume(काष्ठा host1x_client *client)
अणु
	पूर्णांक err = 0;

	mutex_lock(&client->lock);

	अगर (client->parent) अणु
		err = host1x_client_resume(client->parent);
		अगर (err < 0)
			जाओ unlock;
	पूर्ण

	अगर (client->usecount == 0) अणु
		अगर (client->ops && client->ops->resume) अणु
			err = client->ops->resume(client);
			अगर (err < 0)
				जाओ suspend;
		पूर्ण
	पूर्ण

	client->usecount++;
	dev_dbg(client->dev, "use count: %u\n", client->usecount);

	जाओ unlock;

suspend:
	अगर (client->parent)
		host1x_client_suspend(client->parent);
unlock:
	mutex_unlock(&client->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(host1x_client_resume);
