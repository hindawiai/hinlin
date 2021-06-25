<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Class Core
 *
 * Copyright (C) 2005 John Lenz <lenz@cs.wisc.edu>
 * Copyright (C) 2005-2007 Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <uapi/linux/uleds.h>
#समावेश <linux/of.h>
#समावेश "leds.h"

अटल काष्ठा class *leds_class;

अटल sमाप_प्रकार brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	/* no lock needed क्रम this */
	led_update_brightness(led_cdev);

	वापस प्र_लिखो(buf, "%u\n", led_cdev->brightness);
पूर्ण

अटल sमाप_प्रकार brightness_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	sमाप_प्रकार ret;

	mutex_lock(&led_cdev->led_access);

	अगर (led_sysfs_is_disabled(led_cdev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 10, &state);
	अगर (ret)
		जाओ unlock;

	अगर (state == LED_OFF)
		led_trigger_हटाओ(led_cdev);
	led_set_brightness(led_cdev, state);
	flush_work(&led_cdev->set_brightness_work);

	ret = size;
unlock:
	mutex_unlock(&led_cdev->led_access);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(brightness);

अटल sमाप_प्रकार max_brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", led_cdev->max_brightness);
पूर्ण
अटल DEVICE_ATTR_RO(max_brightness);

#अगर_घोषित CONFIG_LEDS_TRIGGERS
अटल BIN_ATTR(trigger, 0644, led_trigger_पढ़ो, led_trigger_ग_लिखो, 0);
अटल काष्ठा bin_attribute *led_trigger_bin_attrs[] = अणु
	&bin_attr_trigger,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group led_trigger_group = अणु
	.bin_attrs = led_trigger_bin_attrs,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा attribute *led_class_attrs[] = अणु
	&dev_attr_brightness.attr,
	&dev_attr_max_brightness.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group led_group = अणु
	.attrs = led_class_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *led_groups[] = अणु
	&led_group,
#अगर_घोषित CONFIG_LEDS_TRIGGERS
	&led_trigger_group,
#पूर्ण_अगर
	शून्य,
पूर्ण;

#अगर_घोषित CONFIG_LEDS_BRIGHTNESS_HW_CHANGED
अटल sमाप_प्रकार brightness_hw_changed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	अगर (led_cdev->brightness_hw_changed == -1)
		वापस -ENODATA;

	वापस प्र_लिखो(buf, "%u\n", led_cdev->brightness_hw_changed);
पूर्ण

अटल DEVICE_ATTR_RO(brightness_hw_changed);

अटल पूर्णांक led_add_brightness_hw_changed(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा device *dev = led_cdev->dev;
	पूर्णांक ret;

	ret = device_create_file(dev, &dev_attr_brightness_hw_changed);
	अगर (ret) अणु
		dev_err(dev, "Error creating brightness_hw_changed\n");
		वापस ret;
	पूर्ण

	led_cdev->brightness_hw_changed_kn =
		sysfs_get_dirent(dev->kobj.sd, "brightness_hw_changed");
	अगर (!led_cdev->brightness_hw_changed_kn) अणु
		dev_err(dev, "Error getting brightness_hw_changed kn\n");
		device_हटाओ_file(dev, &dev_attr_brightness_hw_changed);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम led_हटाओ_brightness_hw_changed(काष्ठा led_classdev *led_cdev)
अणु
	sysfs_put(led_cdev->brightness_hw_changed_kn);
	device_हटाओ_file(led_cdev->dev, &dev_attr_brightness_hw_changed);
पूर्ण

व्योम led_classdev_notअगरy_brightness_hw_changed(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक brightness)
अणु
	अगर (WARN_ON(!led_cdev->brightness_hw_changed_kn))
		वापस;

	led_cdev->brightness_hw_changed = brightness;
	sysfs_notअगरy_dirent(led_cdev->brightness_hw_changed_kn);
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_notअगरy_brightness_hw_changed);
#अन्यथा
अटल पूर्णांक led_add_brightness_hw_changed(काष्ठा led_classdev *led_cdev)
अणु
	वापस 0;
पूर्ण
अटल व्योम led_हटाओ_brightness_hw_changed(काष्ठा led_classdev *led_cdev)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * led_classdev_suspend - suspend an led_classdev.
 * @led_cdev: the led_classdev to suspend.
 */
व्योम led_classdev_suspend(काष्ठा led_classdev *led_cdev)
अणु
	led_cdev->flags |= LED_SUSPENDED;
	led_set_brightness_nopm(led_cdev, 0);
	flush_work(&led_cdev->set_brightness_work);
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_suspend);

/**
 * led_classdev_resume - resume an led_classdev.
 * @led_cdev: the led_classdev to resume.
 */
व्योम led_classdev_resume(काष्ठा led_classdev *led_cdev)
अणु
	led_set_brightness_nopm(led_cdev, led_cdev->brightness);

	अगर (led_cdev->flash_resume)
		led_cdev->flash_resume(led_cdev);

	led_cdev->flags &= ~LED_SUSPENDED;
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_resume);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक led_suspend(काष्ठा device *dev)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	अगर (led_cdev->flags & LED_CORE_SUSPENDRESUME)
		led_classdev_suspend(led_cdev);

	वापस 0;
पूर्ण

अटल पूर्णांक led_resume(काष्ठा device *dev)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	अगर (led_cdev->flags & LED_CORE_SUSPENDRESUME)
		led_classdev_resume(led_cdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(leds_class_dev_pm_ops, led_suspend, led_resume);

/**
 * of_led_get() - request a LED device via the LED framework
 * @np: device node to get the LED device from
 * @index: the index of the LED
 *
 * Returns the LED device parsed from the phandle specअगरied in the "leds"
 * property of a device tree node or a negative error-code on failure.
 */
काष्ठा led_classdev *of_led_get(काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा device *led_dev;
	काष्ठा led_classdev *led_cdev;
	काष्ठा device_node *led_node;

	led_node = of_parse_phandle(np, "leds", index);
	अगर (!led_node)
		वापस ERR_PTR(-ENOENT);

	led_dev = class_find_device_by_of_node(leds_class, led_node);
	of_node_put(led_node);

	अगर (!led_dev)
		वापस ERR_PTR(-EPROBE_DEFER);

	led_cdev = dev_get_drvdata(led_dev);

	अगर (!try_module_get(led_cdev->dev->parent->driver->owner))
		वापस ERR_PTR(-ENODEV);

	वापस led_cdev;
पूर्ण
EXPORT_SYMBOL_GPL(of_led_get);

/**
 * led_put() - release a LED device
 * @led_cdev: LED device
 */
व्योम led_put(काष्ठा led_classdev *led_cdev)
अणु
	module_put(led_cdev->dev->parent->driver->owner);
पूर्ण
EXPORT_SYMBOL_GPL(led_put);

अटल व्योम devm_led_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा led_classdev **p = res;

	led_put(*p);
पूर्ण

/**
 * devm_of_led_get - Resource-managed request of a LED device
 * @dev:	LED consumer
 * @index:	index of the LED to obtain in the consumer
 *
 * The device node of the device is parse to find the request LED device.
 * The LED device वापसed from this function is स्वतःmatically released
 * on driver detach.
 *
 * @वापस a poपूर्णांकer to a LED device or ERR_PTR(त्रुटि_सं) on failure.
 */
काष्ठा led_classdev *__must_check devm_of_led_get(काष्ठा device *dev,
						  पूर्णांक index)
अणु
	काष्ठा led_classdev *led;
	काष्ठा led_classdev **dr;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	/* Not using device tree? */
	अगर (!IS_ENABLED(CONFIG_OF) || !dev->of_node)
		वापस ERR_PTR(-ENOTSUPP);

	led = of_led_get(dev->of_node, index);
	अगर (IS_ERR(led))
		वापस led;

	dr = devres_alloc(devm_led_release, माप(काष्ठा led_classdev *),
			  GFP_KERNEL);
	अगर (!dr) अणु
		led_put(led);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	*dr = led;
	devres_add(dev, dr);

	वापस led;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_led_get);

अटल पूर्णांक led_classdev_next_name(स्थिर अक्षर *init_name, अक्षर *name,
				  माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ret = 0;
	काष्ठा device *dev;

	strlcpy(name, init_name, len);

	जबतक ((ret < len) &&
	       (dev = class_find_device_by_name(leds_class, name))) अणु
		put_device(dev);
		ret = snम_लिखो(name, len, "%s_%u", init_name, ++i);
	पूर्ण

	अगर (ret >= len)
		वापस -ENOMEM;

	वापस i;
पूर्ण

/**
 * led_classdev_रेजिस्टर_ext - रेजिस्टर a new object of led_classdev class
 *			       with init data.
 *
 * @parent: parent of LED device
 * @led_cdev: the led_classdev काष्ठाure क्रम this device.
 * @init_data: LED class device initialization data
 */
पूर्णांक led_classdev_रेजिस्टर_ext(काष्ठा device *parent,
			      काष्ठा led_classdev *led_cdev,
			      काष्ठा led_init_data *init_data)
अणु
	अक्षर composed_name[LED_MAX_NAME_SIZE];
	अक्षर final_name[LED_MAX_NAME_SIZE];
	स्थिर अक्षर *proposed_name = composed_name;
	पूर्णांक ret;

	अगर (init_data) अणु
		अगर (init_data->devname_mandatory && !init_data->devicename) अणु
			dev_err(parent, "Mandatory device name is missing");
			वापस -EINVAL;
		पूर्ण
		ret = led_compose_name(parent, init_data, composed_name);
		अगर (ret < 0)
			वापस ret;

		अगर (init_data->fwnode)
			fwnode_property_पढ़ो_string(init_data->fwnode,
				"linux,default-trigger",
				&led_cdev->शेष_trigger);
	पूर्ण अन्यथा अणु
		proposed_name = led_cdev->name;
	पूर्ण

	ret = led_classdev_next_name(proposed_name, final_name, माप(final_name));
	अगर (ret < 0)
		वापस ret;

	mutex_init(&led_cdev->led_access);
	mutex_lock(&led_cdev->led_access);
	led_cdev->dev = device_create_with_groups(leds_class, parent, 0,
				led_cdev, led_cdev->groups, "%s", final_name);
	अगर (IS_ERR(led_cdev->dev)) अणु
		mutex_unlock(&led_cdev->led_access);
		वापस PTR_ERR(led_cdev->dev);
	पूर्ण
	अगर (init_data && init_data->fwnode) अणु
		led_cdev->dev->fwnode = init_data->fwnode;
		led_cdev->dev->of_node = to_of_node(init_data->fwnode);
	पूर्ण

	अगर (ret)
		dev_warn(parent, "Led %s renamed to %s due to name collision",
				proposed_name, dev_name(led_cdev->dev));

	अगर (led_cdev->flags & LED_BRIGHT_HW_CHANGED) अणु
		ret = led_add_brightness_hw_changed(led_cdev);
		अगर (ret) अणु
			device_unरेजिस्टर(led_cdev->dev);
			led_cdev->dev = शून्य;
			mutex_unlock(&led_cdev->led_access);
			वापस ret;
		पूर्ण
	पूर्ण

	led_cdev->work_flags = 0;
#अगर_घोषित CONFIG_LEDS_TRIGGERS
	init_rwsem(&led_cdev->trigger_lock);
#पूर्ण_अगर
#अगर_घोषित CONFIG_LEDS_BRIGHTNESS_HW_CHANGED
	led_cdev->brightness_hw_changed = -1;
#पूर्ण_अगर
	/* add to the list of leds */
	करोwn_ग_लिखो(&leds_list_lock);
	list_add_tail(&led_cdev->node, &leds_list);
	up_ग_लिखो(&leds_list_lock);

	अगर (!led_cdev->max_brightness)
		led_cdev->max_brightness = LED_FULL;

	led_update_brightness(led_cdev);

	led_init_core(led_cdev);

#अगर_घोषित CONFIG_LEDS_TRIGGERS
	led_trigger_set_शेष(led_cdev);
#पूर्ण_अगर

	mutex_unlock(&led_cdev->led_access);

	dev_dbg(parent, "Registered led device: %s\n",
			led_cdev->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_रेजिस्टर_ext);

/**
 * led_classdev_unरेजिस्टर - unरेजिस्टरs a object of led_properties class.
 * @led_cdev: the led device to unरेजिस्टर
 *
 * Unरेजिस्टरs a previously रेजिस्टरed via led_classdev_रेजिस्टर object.
 */
व्योम led_classdev_unरेजिस्टर(काष्ठा led_classdev *led_cdev)
अणु
	अगर (IS_ERR_OR_शून्य(led_cdev->dev))
		वापस;

#अगर_घोषित CONFIG_LEDS_TRIGGERS
	करोwn_ग_लिखो(&led_cdev->trigger_lock);
	अगर (led_cdev->trigger)
		led_trigger_set(led_cdev, शून्य);
	up_ग_लिखो(&led_cdev->trigger_lock);
#पूर्ण_अगर

	led_cdev->flags |= LED_UNREGISTERING;

	/* Stop blinking */
	led_stop_software_blink(led_cdev);

	led_set_brightness(led_cdev, LED_OFF);

	flush_work(&led_cdev->set_brightness_work);

	अगर (led_cdev->flags & LED_BRIGHT_HW_CHANGED)
		led_हटाओ_brightness_hw_changed(led_cdev);

	device_unरेजिस्टर(led_cdev->dev);

	करोwn_ग_लिखो(&leds_list_lock);
	list_del(&led_cdev->node);
	up_ग_लिखो(&leds_list_lock);

	mutex_destroy(&led_cdev->led_access);
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_unरेजिस्टर);

अटल व्योम devm_led_classdev_release(काष्ठा device *dev, व्योम *res)
अणु
	led_classdev_unरेजिस्टर(*(काष्ठा led_classdev **)res);
पूर्ण

/**
 * devm_led_classdev_रेजिस्टर_ext - resource managed led_classdev_रेजिस्टर_ext()
 *
 * @parent: parent of LED device
 * @led_cdev: the led_classdev काष्ठाure क्रम this device.
 * @init_data: LED class device initialization data
 */
पूर्णांक devm_led_classdev_रेजिस्टर_ext(काष्ठा device *parent,
				   काष्ठा led_classdev *led_cdev,
				   काष्ठा led_init_data *init_data)
अणु
	काष्ठा led_classdev **dr;
	पूर्णांक rc;

	dr = devres_alloc(devm_led_classdev_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	rc = led_classdev_रेजिस्टर_ext(parent, led_cdev, init_data);
	अगर (rc) अणु
		devres_मुक्त(dr);
		वापस rc;
	पूर्ण

	*dr = led_cdev;
	devres_add(parent, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_led_classdev_रेजिस्टर_ext);

अटल पूर्णांक devm_led_classdev_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा led_classdev **p = res;

	अगर (WARN_ON(!p || !*p))
		वापस 0;

	वापस *p == data;
पूर्ण

/**
 * devm_led_classdev_unरेजिस्टर() - resource managed led_classdev_unरेजिस्टर()
 * @parent: The device to unरेजिस्टर.
 * @led_cdev: the led_classdev काष्ठाure क्रम this device.
 */
व्योम devm_led_classdev_unरेजिस्टर(काष्ठा device *dev,
				  काष्ठा led_classdev *led_cdev)
अणु
	WARN_ON(devres_release(dev,
			       devm_led_classdev_release,
			       devm_led_classdev_match, led_cdev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_led_classdev_unरेजिस्टर);

अटल पूर्णांक __init leds_init(व्योम)
अणु
	leds_class = class_create(THIS_MODULE, "leds");
	अगर (IS_ERR(leds_class))
		वापस PTR_ERR(leds_class);
	leds_class->pm = &leds_class_dev_pm_ops;
	leds_class->dev_groups = led_groups;
	वापस 0;
पूर्ण

अटल व्योम __निकास leds_निकास(व्योम)
अणु
	class_destroy(leds_class);
पूर्ण

subsys_initcall(leds_init);
module_निकास(leds_निकास);

MODULE_AUTHOR("John Lenz, Richard Purdie");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LED Class Interface");
