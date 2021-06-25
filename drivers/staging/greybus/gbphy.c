<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Bridged-Phy Bus driver
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"

#घोषणा GB_GBPHY_AUTOSUSPEND_MS	3000

काष्ठा gbphy_host अणु
	काष्ठा gb_bundle *bundle;
	काष्ठा list_head devices;
पूर्ण;

अटल DEFINE_IDA(gbphy_id);

अटल sमाप_प्रकार protocol_id_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	वापस प्र_लिखो(buf, "0x%02x\n", gbphy_dev->cport_desc->protocol_id);
पूर्ण
अटल DEVICE_ATTR_RO(protocol_id);

अटल काष्ठा attribute *gbphy_dev_attrs[] = अणु
	&dev_attr_protocol_id.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(gbphy_dev);

अटल व्योम gbphy_dev_release(काष्ठा device *dev)
अणु
	काष्ठा gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	ida_simple_हटाओ(&gbphy_id, gbphy_dev->id);
	kमुक्त(gbphy_dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gb_gbphy_idle(काष्ठा device *dev)
अणु
	pm_runसमय_mark_last_busy(dev);
	pm_request_स्वतःsuspend(dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops gb_gbphy_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pm_generic_runसमय_suspend,
			   pm_generic_runसमय_resume,
			   gb_gbphy_idle)
पूर्ण;

अटल स्थिर काष्ठा device_type greybus_gbphy_dev_type = अणु
	.name	 =	"gbphy_device",
	.release =	gbphy_dev_release,
	.pm	=	&gb_gbphy_pm_ops,
पूर्ण;

अटल पूर्णांक gbphy_dev_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा gbphy_device *gbphy_dev = to_gbphy_dev(dev);
	काष्ठा greybus_descriptor_cport *cport_desc = gbphy_dev->cport_desc;
	काष्ठा gb_bundle *bundle = gbphy_dev->bundle;
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = bundle->पूर्णांकf;
	काष्ठा gb_module *module = पूर्णांकf->module;
	काष्ठा gb_host_device *hd = पूर्णांकf->hd;

	अगर (add_uevent_var(env, "BUS=%u", hd->bus_id))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "MODULE=%u", module->module_id))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "INTERFACE=%u", पूर्णांकf->पूर्णांकerface_id))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "GREYBUS_ID=%08x/%08x",
			   पूर्णांकf->venकरोr_id, पूर्णांकf->product_id))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "BUNDLE=%u", gbphy_dev->bundle->id))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "BUNDLE_CLASS=%02x", bundle->class))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "GBPHY=%u", gbphy_dev->id))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "PROTOCOL_ID=%02x", cport_desc->protocol_id))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id *
gbphy_dev_match_id(काष्ठा gbphy_device *gbphy_dev,
		   काष्ठा gbphy_driver *gbphy_drv)
अणु
	स्थिर काष्ठा gbphy_device_id *id = gbphy_drv->id_table;

	अगर (!id)
		वापस शून्य;

	क्रम (; id->protocol_id; id++)
		अगर (id->protocol_id == gbphy_dev->cport_desc->protocol_id)
			वापस id;

	वापस शून्य;
पूर्ण

अटल पूर्णांक gbphy_dev_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा gbphy_driver *gbphy_drv = to_gbphy_driver(drv);
	काष्ठा gbphy_device *gbphy_dev = to_gbphy_dev(dev);
	स्थिर काष्ठा gbphy_device_id *id;

	id = gbphy_dev_match_id(gbphy_dev, gbphy_drv);
	अगर (id)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक gbphy_dev_probe(काष्ठा device *dev)
अणु
	काष्ठा gbphy_driver *gbphy_drv = to_gbphy_driver(dev->driver);
	काष्ठा gbphy_device *gbphy_dev = to_gbphy_dev(dev);
	स्थिर काष्ठा gbphy_device_id *id;
	पूर्णांक ret;

	id = gbphy_dev_match_id(gbphy_dev, gbphy_drv);
	अगर (!id)
		वापस -ENODEV;

	/* क्रम old kernels we need get_sync to resume parent devices */
	ret = gb_pm_runसमय_get_sync(gbphy_dev->bundle);
	अगर (ret < 0)
		वापस ret;

	pm_runसमय_set_स्वतःsuspend_delay(dev, GB_GBPHY_AUTOSUSPEND_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	/*
	 * Drivers should call put on the gbphy dev beक्रमe वापसing
	 * from probe अगर they support runसमय pm.
	 */
	ret = gbphy_drv->probe(gbphy_dev, id);
	अगर (ret) अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_suspended(dev);
		pm_runसमय_put_noidle(dev);
		pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	पूर्ण

	gb_pm_runसमय_put_स्वतःsuspend(gbphy_dev->bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gbphy_dev_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा gbphy_driver *gbphy_drv = to_gbphy_driver(dev->driver);
	काष्ठा gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	gbphy_drv->हटाओ(gbphy_dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type gbphy_bus_type = अणु
	.name =		"gbphy",
	.match =	gbphy_dev_match,
	.probe =	gbphy_dev_probe,
	.हटाओ =	gbphy_dev_हटाओ,
	.uevent =	gbphy_dev_uevent,
पूर्ण;

पूर्णांक gb_gbphy_रेजिस्टर_driver(काष्ठा gbphy_driver *driver,
			     काष्ठा module *owner, स्थिर अक्षर *mod_name)
अणु
	पूर्णांक retval;

	अगर (greybus_disabled())
		वापस -ENODEV;

	driver->driver.bus = &gbphy_bus_type;
	driver->driver.name = driver->name;
	driver->driver.owner = owner;
	driver->driver.mod_name = mod_name;

	retval = driver_रेजिस्टर(&driver->driver);
	अगर (retval)
		वापस retval;

	pr_info("registered new driver %s\n", driver->name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_gbphy_रेजिस्टर_driver);

व्योम gb_gbphy_deरेजिस्टर_driver(काष्ठा gbphy_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL_GPL(gb_gbphy_deरेजिस्टर_driver);

अटल काष्ठा gbphy_device *gb_gbphy_create_dev(काष्ठा gb_bundle *bundle,
				काष्ठा greybus_descriptor_cport *cport_desc)
अणु
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक retval;
	पूर्णांक id;

	id = ida_simple_get(&gbphy_id, 1, 0, GFP_KERNEL);
	अगर (id < 0)
		वापस ERR_PTR(id);

	gbphy_dev = kzalloc(माप(*gbphy_dev), GFP_KERNEL);
	अगर (!gbphy_dev) अणु
		ida_simple_हटाओ(&gbphy_id, id);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	gbphy_dev->id = id;
	gbphy_dev->bundle = bundle;
	gbphy_dev->cport_desc = cport_desc;
	gbphy_dev->dev.parent = &bundle->dev;
	gbphy_dev->dev.bus = &gbphy_bus_type;
	gbphy_dev->dev.type = &greybus_gbphy_dev_type;
	gbphy_dev->dev.groups = gbphy_dev_groups;
	gbphy_dev->dev.dma_mask = bundle->dev.dma_mask;
	dev_set_name(&gbphy_dev->dev, "gbphy%d", id);

	retval = device_रेजिस्टर(&gbphy_dev->dev);
	अगर (retval) अणु
		put_device(&gbphy_dev->dev);
		वापस ERR_PTR(retval);
	पूर्ण

	वापस gbphy_dev;
पूर्ण

अटल व्योम gb_gbphy_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gbphy_host *gbphy_host = greybus_get_drvdata(bundle);
	काष्ठा gbphy_device *gbphy_dev, *temp;
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret < 0)
		gb_pm_runसमय_get_noresume(bundle);

	list_क्रम_each_entry_safe(gbphy_dev, temp, &gbphy_host->devices, list) अणु
		list_del(&gbphy_dev->list);
		device_unरेजिस्टर(&gbphy_dev->dev);
	पूर्ण

	kमुक्त(gbphy_host);
पूर्ण

अटल पूर्णांक gb_gbphy_probe(काष्ठा gb_bundle *bundle,
			  स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा gbphy_host *gbphy_host;
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक i;

	अगर (bundle->num_cports == 0)
		वापस -ENODEV;

	gbphy_host = kzalloc(माप(*gbphy_host), GFP_KERNEL);
	अगर (!gbphy_host)
		वापस -ENOMEM;

	gbphy_host->bundle = bundle;
	INIT_LIST_HEAD(&gbphy_host->devices);
	greybus_set_drvdata(bundle, gbphy_host);

	/*
	 * Create a bunch of children devices, one per cport, and bind the
	 * bridged phy drivers to them.
	 */
	क्रम (i = 0; i < bundle->num_cports; ++i) अणु
		gbphy_dev = gb_gbphy_create_dev(bundle, &bundle->cport_desc[i]);
		अगर (IS_ERR(gbphy_dev)) अणु
			gb_gbphy_disconnect(bundle);
			वापस PTR_ERR(gbphy_dev);
		पूर्ण
		list_add(&gbphy_dev->list, &gbphy_host->devices);
	पूर्ण

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_gbphy_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_BRIDGED_PHY) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_gbphy_id_table);

अटल काष्ठा greybus_driver gb_gbphy_driver = अणु
	.name		= "gbphy",
	.probe		= gb_gbphy_probe,
	.disconnect	= gb_gbphy_disconnect,
	.id_table	= gb_gbphy_id_table,
पूर्ण;

अटल पूर्णांक __init gbphy_init(व्योम)
अणु
	पूर्णांक retval;

	retval = bus_रेजिस्टर(&gbphy_bus_type);
	अगर (retval) अणु
		pr_err("gbphy bus register failed (%d)\n", retval);
		वापस retval;
	पूर्ण

	retval = greybus_रेजिस्टर(&gb_gbphy_driver);
	अगर (retval) अणु
		pr_err("error registering greybus driver\n");
		जाओ error_gbphy;
	पूर्ण

	वापस 0;

error_gbphy:
	bus_unरेजिस्टर(&gbphy_bus_type);
	ida_destroy(&gbphy_id);
	वापस retval;
पूर्ण
module_init(gbphy_init);

अटल व्योम __निकास gbphy_निकास(व्योम)
अणु
	greybus_deरेजिस्टर(&gb_gbphy_driver);
	bus_unरेजिस्टर(&gbphy_bus_type);
	ida_destroy(&gbphy_id);
पूर्ण
module_निकास(gbphy_निकास);

MODULE_LICENSE("GPL v2");
