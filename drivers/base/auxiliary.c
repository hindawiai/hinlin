<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020 Intel Corporation
 *
 * Please see Documentation/driver-api/auxiliary_bus.rst क्रम more inक्रमmation.
 */

#घोषणा pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/माला.स>
#समावेश <linux/auxiliary_bus.h>
#समावेश "base.h"

अटल स्थिर काष्ठा auxiliary_device_id *auxiliary_match_id(स्थिर काष्ठा auxiliary_device_id *id,
							    स्थिर काष्ठा auxiliary_device *auxdev)
अणु
	क्रम (; id->name[0]; id++) अणु
		स्थिर अक्षर *p = म_खोजप(dev_name(&auxdev->dev), '.');
		पूर्णांक match_size;

		अगर (!p)
			जारी;
		match_size = p - dev_name(&auxdev->dev);

		/* use dev_name(&auxdev->dev) prefix beक्रमe last '.' अक्षर to match to */
		अगर (म_माप(id->name) == match_size &&
		    !म_भेदन(dev_name(&auxdev->dev), id->name, match_size))
			वापस id;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक auxiliary_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा auxiliary_device *auxdev = to_auxiliary_dev(dev);
	काष्ठा auxiliary_driver *auxdrv = to_auxiliary_drv(drv);

	वापस !!auxiliary_match_id(auxdrv->id_table, auxdev);
पूर्ण

अटल पूर्णांक auxiliary_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	स्थिर अक्षर *name, *p;

	name = dev_name(dev);
	p = म_खोजप(name, '.');

	वापस add_uevent_var(env, "MODALIAS=%s%.*s", AUXILIARY_MODULE_PREFIX,
			      (पूर्णांक)(p - name), name);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops auxiliary_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_generic_runसमय_suspend, pm_generic_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_generic_suspend, pm_generic_resume)
पूर्ण;

अटल पूर्णांक auxiliary_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा auxiliary_driver *auxdrv = to_auxiliary_drv(dev->driver);
	काष्ठा auxiliary_device *auxdev = to_auxiliary_dev(dev);
	पूर्णांक ret;

	ret = dev_pm_करोमुख्य_attach(dev, true);
	अगर (ret) अणु
		dev_warn(dev, "Failed to attach to PM Domain : %d\n", ret);
		वापस ret;
	पूर्ण

	ret = auxdrv->probe(auxdev, auxiliary_match_id(auxdrv->id_table, auxdev));
	अगर (ret)
		dev_pm_करोमुख्य_detach(dev, true);

	वापस ret;
पूर्ण

अटल पूर्णांक auxiliary_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा auxiliary_driver *auxdrv = to_auxiliary_drv(dev->driver);
	काष्ठा auxiliary_device *auxdev = to_auxiliary_dev(dev);

	अगर (auxdrv->हटाओ)
		auxdrv->हटाओ(auxdev);
	dev_pm_करोमुख्य_detach(dev, true);

	वापस 0;
पूर्ण

अटल व्योम auxiliary_bus_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा auxiliary_driver *auxdrv = शून्य;
	काष्ठा auxiliary_device *auxdev;

	अगर (dev->driver) अणु
		auxdrv = to_auxiliary_drv(dev->driver);
		auxdev = to_auxiliary_dev(dev);
	पूर्ण

	अगर (auxdrv && auxdrv->shutकरोwn)
		auxdrv->shutकरोwn(auxdev);
पूर्ण

अटल काष्ठा bus_type auxiliary_bus_type = अणु
	.name = "auxiliary",
	.probe = auxiliary_bus_probe,
	.हटाओ = auxiliary_bus_हटाओ,
	.shutकरोwn = auxiliary_bus_shutकरोwn,
	.match = auxiliary_match,
	.uevent = auxiliary_uevent,
	.pm = &auxiliary_dev_pm_ops,
पूर्ण;

/**
 * auxiliary_device_init - check auxiliary_device and initialize
 * @auxdev: auxiliary device काष्ठा
 *
 * This is the first step in the two-step process to रेजिस्टर an
 * auxiliary_device.
 *
 * When this function वापसs an error code, then the device_initialize will
 * *not* have been perक्रमmed, and the caller will be responsible to मुक्त any
 * memory allocated क्रम the auxiliary_device in the error path directly.
 *
 * It वापसs 0 on success.  On success, the device_initialize has been
 * perक्रमmed.  After this poपूर्णांक any error unwinding will need to include a call
 * to auxiliary_device_uninit().  In this post-initialize error scenario, a call
 * to the device's .release callback will be triggered, and all memory clean-up
 * is expected to be handled there.
 */
पूर्णांक auxiliary_device_init(काष्ठा auxiliary_device *auxdev)
अणु
	काष्ठा device *dev = &auxdev->dev;

	अगर (!dev->parent) अणु
		pr_err("auxiliary_device has a NULL dev->parent\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!auxdev->name) अणु
		pr_err("auxiliary_device has a NULL name\n");
		वापस -EINVAL;
	पूर्ण

	dev->bus = &auxiliary_bus_type;
	device_initialize(&auxdev->dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(auxiliary_device_init);

/**
 * __auxiliary_device_add - add an auxiliary bus device
 * @auxdev: auxiliary bus device to add to the bus
 * @modname: name of the parent device's driver module
 *
 * This is the second step in the two-step process to रेजिस्टर an
 * auxiliary_device.
 *
 * This function must be called after a successful call to
 * auxiliary_device_init(), which will perक्रमm the device_initialize.  This
 * means that अगर this वापसs an error code, then a call to
 * auxiliary_device_uninit() must be perक्रमmed so that the .release callback
 * will be triggered to मुक्त the memory associated with the auxiliary_device.
 *
 * The expectation is that users will call the "auxiliary_device_add" macro so
 * that the caller's KBUILD_MODNAME is स्वतःmatically inserted क्रम the modname
 * parameter.  Only अगर a user requires a custom name would this version be
 * called directly.
 */
पूर्णांक __auxiliary_device_add(काष्ठा auxiliary_device *auxdev, स्थिर अक्षर *modname)
अणु
	काष्ठा device *dev = &auxdev->dev;
	पूर्णांक ret;

	अगर (!modname) अणु
		dev_err(dev, "auxiliary device modname is NULL\n");
		वापस -EINVAL;
	पूर्ण

	ret = dev_set_name(dev, "%s.%s.%d", modname, auxdev->name, auxdev->id);
	अगर (ret) अणु
		dev_err(dev, "auxiliary device dev_set_name failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = device_add(dev);
	अगर (ret)
		dev_err(dev, "adding auxiliary device failed!: %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__auxiliary_device_add);

/**
 * auxiliary_find_device - auxiliary device iterator क्रम locating a particular device.
 * @start: Device to begin with
 * @data: Data to pass to match function
 * @match: Callback function to check device
 *
 * This function वापसs a reference to a device that is 'found'
 * क्रम later use, as determined by the @match callback.
 *
 * The callback should वापस 0 अगर the device करोesn't match and non-zero
 * अगर it करोes.  If the callback वापसs non-zero, this function will
 * वापस to the caller and not iterate over any more devices.
 */
काष्ठा auxiliary_device *auxiliary_find_device(काष्ठा device *start,
					       स्थिर व्योम *data,
					       पूर्णांक (*match)(काष्ठा device *dev, स्थिर व्योम *data))
अणु
	काष्ठा device *dev;

	dev = bus_find_device(&auxiliary_bus_type, start, data, match);
	अगर (!dev)
		वापस शून्य;

	वापस to_auxiliary_dev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(auxiliary_find_device);

/**
 * __auxiliary_driver_रेजिस्टर - रेजिस्टर a driver क्रम auxiliary bus devices
 * @auxdrv: auxiliary_driver काष्ठाure
 * @owner: owning module/driver
 * @modname: KBUILD_MODNAME क्रम parent driver
 */
पूर्णांक __auxiliary_driver_रेजिस्टर(काष्ठा auxiliary_driver *auxdrv,
				काष्ठा module *owner, स्थिर अक्षर *modname)
अणु
	अगर (WARN_ON(!auxdrv->probe) || WARN_ON(!auxdrv->id_table))
		वापस -EINVAL;

	अगर (auxdrv->name)
		auxdrv->driver.name = kaप्र_लिखो(GFP_KERNEL, "%s.%s", modname,
						auxdrv->name);
	अन्यथा
		auxdrv->driver.name = kaप्र_लिखो(GFP_KERNEL, "%s", modname);
	अगर (!auxdrv->driver.name)
		वापस -ENOMEM;

	auxdrv->driver.owner = owner;
	auxdrv->driver.bus = &auxiliary_bus_type;
	auxdrv->driver.mod_name = modname;

	वापस driver_रेजिस्टर(&auxdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__auxiliary_driver_रेजिस्टर);

/**
 * auxiliary_driver_unरेजिस्टर - unरेजिस्टर a driver
 * @auxdrv: auxiliary_driver काष्ठाure
 */
व्योम auxiliary_driver_unरेजिस्टर(काष्ठा auxiliary_driver *auxdrv)
अणु
	driver_unरेजिस्टर(&auxdrv->driver);
	kमुक्त(auxdrv->driver.name);
पूर्ण
EXPORT_SYMBOL_GPL(auxiliary_driver_unरेजिस्टर);

व्योम __init auxiliary_bus_init(व्योम)
अणु
	WARN_ON(bus_रेजिस्टर(&auxiliary_bus_type));
पूर्ण
