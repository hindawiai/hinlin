<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Message Protocol bus layer
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#समावेश "common.h"

अटल DEFINE_IDA(scmi_bus_id);
अटल DEFINE_IDR(scmi_protocols);
अटल DEFINE_SPINLOCK(protocol_lock);

अटल स्थिर काष्ठा scmi_device_id *
scmi_dev_match_id(काष्ठा scmi_device *scmi_dev, काष्ठा scmi_driver *scmi_drv)
अणु
	स्थिर काष्ठा scmi_device_id *id = scmi_drv->id_table;

	अगर (!id)
		वापस शून्य;

	क्रम (; id->protocol_id; id++)
		अगर (id->protocol_id == scmi_dev->protocol_id) अणु
			अगर (!id->name)
				वापस id;
			अन्यथा अगर (!म_भेद(id->name, scmi_dev->name))
				वापस id;
		पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक scmi_dev_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा scmi_driver *scmi_drv = to_scmi_driver(drv);
	काष्ठा scmi_device *scmi_dev = to_scmi_dev(dev);
	स्थिर काष्ठा scmi_device_id *id;

	id = scmi_dev_match_id(scmi_dev, scmi_drv);
	अगर (id)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक scmi_match_by_id_table(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा scmi_device *sdev = to_scmi_dev(dev);
	काष्ठा scmi_device_id *id_table = data;

	वापस sdev->protocol_id == id_table->protocol_id &&
		!म_भेद(sdev->name, id_table->name);
पूर्ण

काष्ठा scmi_device *scmi_child_dev_find(काष्ठा device *parent,
					पूर्णांक prot_id, स्थिर अक्षर *name)
अणु
	काष्ठा scmi_device_id id_table;
	काष्ठा device *dev;

	id_table.protocol_id = prot_id;
	id_table.name = name;

	dev = device_find_child(parent, &id_table, scmi_match_by_id_table);
	अगर (!dev)
		वापस शून्य;

	वापस to_scmi_dev(dev);
पूर्ण

स्थिर काष्ठा scmi_protocol *scmi_protocol_get(पूर्णांक protocol_id)
अणु
	स्थिर काष्ठा scmi_protocol *proto;

	proto = idr_find(&scmi_protocols, protocol_id);
	अगर (!proto || !try_module_get(proto->owner)) अणु
		pr_warn("SCMI Protocol 0x%x not found!\n", protocol_id);
		वापस शून्य;
	पूर्ण

	pr_debug("Found SCMI Protocol 0x%x\n", protocol_id);

	वापस proto;
पूर्ण

व्योम scmi_protocol_put(पूर्णांक protocol_id)
अणु
	स्थिर काष्ठा scmi_protocol *proto;

	proto = idr_find(&scmi_protocols, protocol_id);
	अगर (proto)
		module_put(proto->owner);
पूर्ण

अटल पूर्णांक scmi_dev_probe(काष्ठा device *dev)
अणु
	काष्ठा scmi_driver *scmi_drv = to_scmi_driver(dev->driver);
	काष्ठा scmi_device *scmi_dev = to_scmi_dev(dev);
	स्थिर काष्ठा scmi_device_id *id;

	id = scmi_dev_match_id(scmi_dev, scmi_drv);
	अगर (!id)
		वापस -ENODEV;

	अगर (!scmi_dev->handle)
		वापस -EPROBE_DEFER;

	वापस scmi_drv->probe(scmi_dev);
पूर्ण

अटल पूर्णांक scmi_dev_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा scmi_driver *scmi_drv = to_scmi_driver(dev->driver);
	काष्ठा scmi_device *scmi_dev = to_scmi_dev(dev);

	अगर (scmi_drv->हटाओ)
		scmi_drv->हटाओ(scmi_dev);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type scmi_bus_type = अणु
	.name =	"scmi_protocol",
	.match = scmi_dev_match,
	.probe = scmi_dev_probe,
	.हटाओ = scmi_dev_हटाओ,
पूर्ण;

पूर्णांक scmi_driver_रेजिस्टर(काष्ठा scmi_driver *driver, काष्ठा module *owner,
			 स्थिर अक्षर *mod_name)
अणु
	पूर्णांक retval;

	retval = scmi_protocol_device_request(driver->id_table);
	अगर (retval)
		वापस retval;

	driver->driver.bus = &scmi_bus_type;
	driver->driver.name = driver->name;
	driver->driver.owner = owner;
	driver->driver.mod_name = mod_name;

	retval = driver_रेजिस्टर(&driver->driver);
	अगर (!retval)
		pr_debug("registered new scmi driver %s\n", driver->name);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(scmi_driver_रेजिस्टर);

व्योम scmi_driver_unरेजिस्टर(काष्ठा scmi_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->driver);
	scmi_protocol_device_unrequest(driver->id_table);
पूर्ण
EXPORT_SYMBOL_GPL(scmi_driver_unरेजिस्टर);

अटल व्योम scmi_device_release(काष्ठा device *dev)
अणु
	kमुक्त(to_scmi_dev(dev));
पूर्ण

काष्ठा scmi_device *
scmi_device_create(काष्ठा device_node *np, काष्ठा device *parent, पूर्णांक protocol,
		   स्थिर अक्षर *name)
अणु
	पूर्णांक id, retval;
	काष्ठा scmi_device *scmi_dev;

	scmi_dev = kzalloc(माप(*scmi_dev), GFP_KERNEL);
	अगर (!scmi_dev)
		वापस शून्य;

	scmi_dev->name = kstrdup_स्थिर(name ?: "unknown", GFP_KERNEL);
	अगर (!scmi_dev->name) अणु
		kमुक्त(scmi_dev);
		वापस शून्य;
	पूर्ण

	id = ida_simple_get(&scmi_bus_id, 1, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		kमुक्त_स्थिर(scmi_dev->name);
		kमुक्त(scmi_dev);
		वापस शून्य;
	पूर्ण

	scmi_dev->id = id;
	scmi_dev->protocol_id = protocol;
	scmi_dev->dev.parent = parent;
	scmi_dev->dev.of_node = np;
	scmi_dev->dev.bus = &scmi_bus_type;
	scmi_dev->dev.release = scmi_device_release;
	dev_set_name(&scmi_dev->dev, "scmi_dev.%d", id);

	retval = device_रेजिस्टर(&scmi_dev->dev);
	अगर (retval)
		जाओ put_dev;

	वापस scmi_dev;
put_dev:
	kमुक्त_स्थिर(scmi_dev->name);
	put_device(&scmi_dev->dev);
	ida_simple_हटाओ(&scmi_bus_id, id);
	वापस शून्य;
पूर्ण

व्योम scmi_device_destroy(काष्ठा scmi_device *scmi_dev)
अणु
	kमुक्त_स्थिर(scmi_dev->name);
	scmi_handle_put(scmi_dev->handle);
	ida_simple_हटाओ(&scmi_bus_id, scmi_dev->id);
	device_unरेजिस्टर(&scmi_dev->dev);
पूर्ण

व्योम scmi_set_handle(काष्ठा scmi_device *scmi_dev)
अणु
	scmi_dev->handle = scmi_handle_get(&scmi_dev->dev);
पूर्ण

पूर्णांक scmi_protocol_रेजिस्टर(स्थिर काष्ठा scmi_protocol *proto)
अणु
	पूर्णांक ret;

	अगर (!proto) अणु
		pr_err("invalid protocol\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!proto->instance_init) अणु
		pr_err("missing init for protocol 0x%x\n", proto->id);
		वापस -EINVAL;
	पूर्ण

	spin_lock(&protocol_lock);
	ret = idr_alloc(&scmi_protocols, (व्योम *)proto,
			proto->id, proto->id + 1, GFP_ATOMIC);
	spin_unlock(&protocol_lock);
	अगर (ret != proto->id) अणु
		pr_err("unable to allocate SCMI idr slot for 0x%x - err %d\n",
		       proto->id, ret);
		वापस ret;
	पूर्ण

	pr_debug("Registered SCMI Protocol 0x%x\n", proto->id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(scmi_protocol_रेजिस्टर);

व्योम scmi_protocol_unरेजिस्टर(स्थिर काष्ठा scmi_protocol *proto)
अणु
	spin_lock(&protocol_lock);
	idr_हटाओ(&scmi_protocols, proto->id);
	spin_unlock(&protocol_lock);

	pr_debug("Unregistered SCMI Protocol 0x%x\n", proto->id);

	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(scmi_protocol_unरेजिस्टर);

अटल पूर्णांक __scmi_devices_unरेजिस्टर(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा scmi_device *scmi_dev = to_scmi_dev(dev);

	scmi_device_destroy(scmi_dev);
	वापस 0;
पूर्ण

अटल व्योम scmi_devices_unरेजिस्टर(व्योम)
अणु
	bus_क्रम_each_dev(&scmi_bus_type, शून्य, शून्य, __scmi_devices_unरेजिस्टर);
पूर्ण

पूर्णांक __init scmi_bus_init(व्योम)
अणु
	पूर्णांक retval;

	retval = bus_रेजिस्टर(&scmi_bus_type);
	अगर (retval)
		pr_err("scmi protocol bus register failed (%d)\n", retval);

	वापस retval;
पूर्ण

व्योम __निकास scmi_bus_निकास(व्योम)
अणु
	scmi_devices_unरेजिस्टर();
	bus_unरेजिस्टर(&scmi_bus_type);
	ida_destroy(&scmi_bus_id);
पूर्ण
