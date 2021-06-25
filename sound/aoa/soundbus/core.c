<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soundbus
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/module.h>
#समावेश "soundbus.h"

MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Apple Soundbus");

काष्ठा soundbus_dev *soundbus_dev_get(काष्ठा soundbus_dev *dev)
अणु
	काष्ठा device *पंचांगp;

	अगर (!dev)
		वापस शून्य;
	पंचांगp = get_device(&dev->ofdev.dev);
	अगर (पंचांगp)
		वापस to_soundbus_device(पंचांगp);
	अन्यथा
		वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(soundbus_dev_get);

व्योम soundbus_dev_put(काष्ठा soundbus_dev *dev)
अणु
	अगर (dev)
		put_device(&dev->ofdev.dev);
पूर्ण
EXPORT_SYMBOL_GPL(soundbus_dev_put);

अटल पूर्णांक soundbus_probe(काष्ठा device *dev)
अणु
	पूर्णांक error = -ENODEV;
	काष्ठा soundbus_driver *drv;
	काष्ठा soundbus_dev *soundbus_dev;

	drv = to_soundbus_driver(dev->driver);
	soundbus_dev = to_soundbus_device(dev);

	अगर (!drv->probe)
		वापस error;

	soundbus_dev_get(soundbus_dev);

	error = drv->probe(soundbus_dev);
	अगर (error)
		soundbus_dev_put(soundbus_dev);

	वापस error;
पूर्ण


अटल पूर्णांक soundbus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा soundbus_dev * soundbus_dev;
	काष्ठा platक्रमm_device * of;
	स्थिर अक्षर *compat;
	पूर्णांक retval = 0;
	पूर्णांक cplen, seen = 0;

	अगर (!dev)
		वापस -ENODEV;

	soundbus_dev = to_soundbus_device(dev);
	अगर (!soundbus_dev)
		वापस -ENODEV;

	of = &soundbus_dev->ofdev;

	/* stuff we want to pass to /sbin/hotplug */
	retval = add_uevent_var(env, "OF_NAME=%pOFn", of->dev.of_node);
	अगर (retval)
		वापस retval;

	retval = add_uevent_var(env, "OF_TYPE=%s", of_node_get_device_type(of->dev.of_node));
	अगर (retval)
		वापस retval;

	/* Since the compatible field can contain pretty much anything
	 * it's not really legal to split it out with commas. We split it
	 * up using a number of environment variables instead. */

	compat = of_get_property(of->dev.of_node, "compatible", &cplen);
	जबतक (compat && cplen > 0) अणु
		पूर्णांक पंचांगp = env->buflen;
		retval = add_uevent_var(env, "OF_COMPATIBLE_%d=%s", seen, compat);
		अगर (retval)
			वापस retval;
		compat += env->buflen - पंचांगp;
		cplen -= env->buflen - पंचांगp;
		seen += 1;
	पूर्ण

	retval = add_uevent_var(env, "OF_COMPATIBLE_N=%d", seen);
	अगर (retval)
		वापस retval;
	retval = add_uevent_var(env, "MODALIAS=%s", soundbus_dev->modalias);

	वापस retval;
पूर्ण

अटल पूर्णांक soundbus_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा soundbus_dev * soundbus_dev = to_soundbus_device(dev);
	काष्ठा soundbus_driver * drv = to_soundbus_driver(dev->driver);

	अगर (dev->driver && drv->हटाओ)
		drv->हटाओ(soundbus_dev);
	soundbus_dev_put(soundbus_dev);

	वापस 0;
पूर्ण

अटल व्योम soundbus_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा soundbus_dev * soundbus_dev = to_soundbus_device(dev);
	काष्ठा soundbus_driver * drv = to_soundbus_driver(dev->driver);

	अगर (dev->driver && drv->shutकरोwn)
		drv->shutकरोwn(soundbus_dev);
पूर्ण

/* soundbus_dev_attrs is declared in sysfs.c */
ATTRIBUTE_GROUPS(soundbus_dev);
अटल काष्ठा bus_type soundbus_bus_type = अणु
	.name		= "aoa-soundbus",
	.probe		= soundbus_probe,
	.uevent		= soundbus_uevent,
	.हटाओ		= soundbus_device_हटाओ,
	.shutकरोwn	= soundbus_device_shutकरोwn,
	.dev_groups	= soundbus_dev_groups,
पूर्ण;

पूर्णांक soundbus_add_one(काष्ठा soundbus_dev *dev)
अणु
	अटल पूर्णांक devcount;

	/* sanity checks */
	अगर (!dev->attach_codec ||
	    !dev->ofdev.dev.of_node ||
	    dev->pcmname ||
	    dev->pcmid != -1) अणु
		prपूर्णांकk(KERN_ERR "soundbus: adding device failed sanity check!\n");
		वापस -EINVAL;
	पूर्ण

	dev_set_name(&dev->ofdev.dev, "soundbus:%x", ++devcount);
	dev->ofdev.dev.bus = &soundbus_bus_type;
	वापस of_device_रेजिस्टर(&dev->ofdev);
पूर्ण
EXPORT_SYMBOL_GPL(soundbus_add_one);

व्योम soundbus_हटाओ_one(काष्ठा soundbus_dev *dev)
अणु
	of_device_unरेजिस्टर(&dev->ofdev);
पूर्ण
EXPORT_SYMBOL_GPL(soundbus_हटाओ_one);

पूर्णांक soundbus_रेजिस्टर_driver(काष्ठा soundbus_driver *drv)
अणु
	/* initialize common driver fields */
	drv->driver.name = drv->name;
	drv->driver.bus = &soundbus_bus_type;

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(soundbus_रेजिस्टर_driver);

व्योम soundbus_unरेजिस्टर_driver(काष्ठा soundbus_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(soundbus_unरेजिस्टर_driver);

अटल पूर्णांक __init soundbus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&soundbus_bus_type);
पूर्ण

अटल व्योम __निकास soundbus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&soundbus_bus_type);
पूर्ण

subsys_initcall(soundbus_init);
module_निकास(soundbus_निकास);
