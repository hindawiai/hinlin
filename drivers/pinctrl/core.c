<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम the pin control subप्रणाली
 *
 * Copyright (C) 2011-2012 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * Copyright (C) 2012 NVIDIA CORPORATION. All rights reserved.
 */
#घोषणा pr_fmt(fmt) "pinctrl core: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/machine.h>

#अगर_घोषित CONFIG_GPIOLIB
#समावेश "../gpio/gpiolib.h"
#समावेश <यंत्र-generic/gpपन.स>
#पूर्ण_अगर

#समावेश "core.h"
#समावेश "devicetree.h"
#समावेश "pinmux.h"
#समावेश "pinconf.h"


अटल bool pinctrl_dummy_state;

/* Mutex taken to protect pinctrl_list */
अटल DEFINE_MUTEX(pinctrl_list_mutex);

/* Mutex taken to protect pinctrl_maps */
DEFINE_MUTEX(pinctrl_maps_mutex);

/* Mutex taken to protect pinctrldev_list */
अटल DEFINE_MUTEX(pinctrldev_list_mutex);

/* Global list of pin control devices (काष्ठा pinctrl_dev) */
अटल LIST_HEAD(pinctrldev_list);

/* List of pin controller handles (काष्ठा pinctrl) */
अटल LIST_HEAD(pinctrl_list);

/* List of pinctrl maps (काष्ठा pinctrl_maps) */
LIST_HEAD(pinctrl_maps);


/**
 * pinctrl_provide_dummies() - indicate अगर pinctrl provides dummy state support
 *
 * Usually this function is called by platक्रमms without pinctrl driver support
 * but run with some shared drivers using pinctrl APIs.
 * After calling this function, the pinctrl core will वापस successfully
 * with creating a dummy state क्रम the driver to keep going smoothly.
 */
व्योम pinctrl_provide_dummies(व्योम)
अणु
	pinctrl_dummy_state = true;
पूर्ण

स्थिर अक्षर *pinctrl_dev_get_name(काष्ठा pinctrl_dev *pctldev)
अणु
	/* We're not allowed to रेजिस्टर devices without name */
	वापस pctldev->desc->name;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_dev_get_name);

स्थिर अक्षर *pinctrl_dev_get_devname(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस dev_name(pctldev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_dev_get_devname);

व्योम *pinctrl_dev_get_drvdata(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस pctldev->driver_data;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_dev_get_drvdata);

/**
 * get_pinctrl_dev_from_devname() - look up pin controller device
 * @devname: the name of a device instance, as वापसed by dev_name()
 *
 * Looks up a pin control device matching a certain device name or pure device
 * poपूर्णांकer, the pure device poपूर्णांकer will take precedence.
 */
काष्ठा pinctrl_dev *get_pinctrl_dev_from_devname(स्थिर अक्षर *devname)
अणु
	काष्ठा pinctrl_dev *pctldev;

	अगर (!devname)
		वापस शून्य;

	mutex_lock(&pinctrldev_list_mutex);

	list_क्रम_each_entry(pctldev, &pinctrldev_list, node) अणु
		अगर (!म_भेद(dev_name(pctldev->dev), devname)) अणु
			/* Matched on device name */
			mutex_unlock(&pinctrldev_list_mutex);
			वापस pctldev;
		पूर्ण
	पूर्ण

	mutex_unlock(&pinctrldev_list_mutex);

	वापस शून्य;
पूर्ण

काष्ठा pinctrl_dev *get_pinctrl_dev_from_of_node(काष्ठा device_node *np)
अणु
	काष्ठा pinctrl_dev *pctldev;

	mutex_lock(&pinctrldev_list_mutex);

	list_क्रम_each_entry(pctldev, &pinctrldev_list, node)
		अगर (pctldev->dev->of_node == np) अणु
			mutex_unlock(&pinctrldev_list_mutex);
			वापस pctldev;
		पूर्ण

	mutex_unlock(&pinctrldev_list_mutex);

	वापस शून्य;
पूर्ण

/**
 * pin_get_from_name() - look up a pin number from a name
 * @pctldev: the pin control device to lookup the pin on
 * @name: the name of the pin to look up
 */
पूर्णांक pin_get_from_name(काष्ठा pinctrl_dev *pctldev, स्थिर अक्षर *name)
अणु
	अचिन्हित i, pin;

	/* The pin number can be retrived from the pin controller descriptor */
	क्रम (i = 0; i < pctldev->desc->npins; i++) अणु
		काष्ठा pin_desc *desc;

		pin = pctldev->desc->pins[i].number;
		desc = pin_desc_get(pctldev, pin);
		/* Pin space may be sparse */
		अगर (desc && !म_भेद(name, desc->name))
			वापस pin;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * pin_get_name() - look up a pin name from a pin id
 * @pctldev: the pin control device to lookup the pin on
 * @pin: pin number/id to look up
 */
स्थिर अक्षर *pin_get_name(काष्ठा pinctrl_dev *pctldev, स्थिर अचिन्हित pin)
अणु
	स्थिर काष्ठा pin_desc *desc;

	desc = pin_desc_get(pctldev, pin);
	अगर (!desc) अणु
		dev_err(pctldev->dev, "failed to get pin(%d) name\n",
			pin);
		वापस शून्य;
	पूर्ण

	वापस desc->name;
पूर्ण
EXPORT_SYMBOL_GPL(pin_get_name);

/* Deletes a range of pin descriptors */
अटल व्योम pinctrl_मुक्त_pindescs(काष्ठा pinctrl_dev *pctldev,
				  स्थिर काष्ठा pinctrl_pin_desc *pins,
				  अचिन्हित num_pins)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_pins; i++) अणु
		काष्ठा pin_desc *pindesc;

		pindesc = radix_tree_lookup(&pctldev->pin_desc_tree,
					    pins[i].number);
		अगर (pindesc) अणु
			radix_tree_delete(&pctldev->pin_desc_tree,
					  pins[i].number);
			अगर (pindesc->dynamic_name)
				kमुक्त(pindesc->name);
		पूर्ण
		kमुक्त(pindesc);
	पूर्ण
पूर्ण

अटल पूर्णांक pinctrl_रेजिस्टर_one_pin(काष्ठा pinctrl_dev *pctldev,
				    स्थिर काष्ठा pinctrl_pin_desc *pin)
अणु
	काष्ठा pin_desc *pindesc;

	pindesc = pin_desc_get(pctldev, pin->number);
	अगर (pindesc) अणु
		dev_err(pctldev->dev, "pin %d already registered\n",
			pin->number);
		वापस -EINVAL;
	पूर्ण

	pindesc = kzalloc(माप(*pindesc), GFP_KERNEL);
	अगर (!pindesc)
		वापस -ENOMEM;

	/* Set owner */
	pindesc->pctldev = pctldev;

	/* Copy basic pin info */
	अगर (pin->name) अणु
		pindesc->name = pin->name;
	पूर्ण अन्यथा अणु
		pindesc->name = kaप्र_लिखो(GFP_KERNEL, "PIN%u", pin->number);
		अगर (!pindesc->name) अणु
			kमुक्त(pindesc);
			वापस -ENOMEM;
		पूर्ण
		pindesc->dynamic_name = true;
	पूर्ण

	pindesc->drv_data = pin->drv_data;

	radix_tree_insert(&pctldev->pin_desc_tree, pin->number, pindesc);
	pr_debug("registered pin %d (%s) on %s\n",
		 pin->number, pindesc->name, pctldev->desc->name);
	वापस 0;
पूर्ण

अटल पूर्णांक pinctrl_रेजिस्टर_pins(काष्ठा pinctrl_dev *pctldev,
				 स्थिर काष्ठा pinctrl_pin_desc *pins,
				 अचिन्हित num_descs)
अणु
	अचिन्हित i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < num_descs; i++) अणु
		ret = pinctrl_रेजिस्टर_one_pin(pctldev, &pins[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * gpio_to_pin() - GPIO range GPIO number to pin number translation
 * @range: GPIO range used क्रम the translation
 * @gpio: gpio pin to translate to a pin number
 *
 * Finds the pin number क्रम a given GPIO using the specअगरied GPIO range
 * as a base क्रम translation. The distinction between linear GPIO ranges
 * and pin list based GPIO ranges is managed correctly by this function.
 *
 * This function assumes the gpio is part of the specअगरied GPIO range, use
 * only after making sure this is the हाल (e.g. by calling it on the
 * result of successful pinctrl_get_device_gpio_range calls)!
 */
अटल अंतरभूत पूर्णांक gpio_to_pin(काष्ठा pinctrl_gpio_range *range,
				अचिन्हित पूर्णांक gpio)
अणु
	अचिन्हित पूर्णांक offset = gpio - range->base;
	अगर (range->pins)
		वापस range->pins[offset];
	अन्यथा
		वापस range->pin_base + offset;
पूर्ण

/**
 * pinctrl_match_gpio_range() - check अगर a certain GPIO pin is in range
 * @pctldev: pin controller device to check
 * @gpio: gpio pin to check taken from the global GPIO pin space
 *
 * Tries to match a GPIO pin number to the ranges handled by a certain pin
 * controller, वापस the range or शून्य
 */
अटल काष्ठा pinctrl_gpio_range *
pinctrl_match_gpio_range(काष्ठा pinctrl_dev *pctldev, अचिन्हित gpio)
अणु
	काष्ठा pinctrl_gpio_range *range;

	mutex_lock(&pctldev->mutex);
	/* Loop over the ranges */
	list_क्रम_each_entry(range, &pctldev->gpio_ranges, node) अणु
		/* Check अगर we're in the valid range */
		अगर (gpio >= range->base &&
		    gpio < range->base + range->npins) अणु
			mutex_unlock(&pctldev->mutex);
			वापस range;
		पूर्ण
	पूर्ण
	mutex_unlock(&pctldev->mutex);
	वापस शून्य;
पूर्ण

/**
 * pinctrl_पढ़ोy_क्रम_gpio_range() - check अगर other GPIO pins of
 * the same GPIO chip are in range
 * @gpio: gpio pin to check taken from the global GPIO pin space
 *
 * This function is complement of pinctrl_match_gpio_range(). If the वापस
 * value of pinctrl_match_gpio_range() is शून्य, this function could be used
 * to check whether pinctrl device is पढ़ोy or not. Maybe some GPIO pins
 * of the same GPIO chip करोn't have back-end pinctrl पूर्णांकerface.
 * If the वापस value is true, it means that pinctrl device is पढ़ोy & the
 * certain GPIO pin करोesn't have back-end pinctrl device. If the वापस value
 * is false, it means that pinctrl device may not be पढ़ोy.
 */
#अगर_घोषित CONFIG_GPIOLIB
अटल bool pinctrl_पढ़ोy_क्रम_gpio_range(अचिन्हित gpio)
अणु
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_gpio_range *range = शून्य;
	काष्ठा gpio_chip *chip = gpio_to_chip(gpio);

	अगर (WARN(!chip, "no gpio_chip for gpio%i?", gpio))
		वापस false;

	mutex_lock(&pinctrldev_list_mutex);

	/* Loop over the pin controllers */
	list_क्रम_each_entry(pctldev, &pinctrldev_list, node) अणु
		/* Loop over the ranges */
		mutex_lock(&pctldev->mutex);
		list_क्रम_each_entry(range, &pctldev->gpio_ranges, node) अणु
			/* Check अगर any gpio range overlapped with gpio chip */
			अगर (range->base + range->npins - 1 < chip->base ||
			    range->base > chip->base + chip->ngpio - 1)
				जारी;
			mutex_unlock(&pctldev->mutex);
			mutex_unlock(&pinctrldev_list_mutex);
			वापस true;
		पूर्ण
		mutex_unlock(&pctldev->mutex);
	पूर्ण

	mutex_unlock(&pinctrldev_list_mutex);

	वापस false;
पूर्ण
#अन्यथा
अटल bool pinctrl_पढ़ोy_क्रम_gpio_range(अचिन्हित gpio) अणु वापस true; पूर्ण
#पूर्ण_अगर

/**
 * pinctrl_get_device_gpio_range() - find device क्रम GPIO range
 * @gpio: the pin to locate the pin controller क्रम
 * @outdev: the pin control device अगर found
 * @outrange: the GPIO range अगर found
 *
 * Find the pin controller handling a certain GPIO pin from the pinspace of
 * the GPIO subप्रणाली, वापस the device and the matching GPIO range. Returns
 * -EPROBE_DEFER अगर the GPIO range could not be found in any device since it
 * may still have not been रेजिस्टरed.
 */
अटल पूर्णांक pinctrl_get_device_gpio_range(अचिन्हित gpio,
					 काष्ठा pinctrl_dev **outdev,
					 काष्ठा pinctrl_gpio_range **outrange)
अणु
	काष्ठा pinctrl_dev *pctldev;

	mutex_lock(&pinctrldev_list_mutex);

	/* Loop over the pin controllers */
	list_क्रम_each_entry(pctldev, &pinctrldev_list, node) अणु
		काष्ठा pinctrl_gpio_range *range;

		range = pinctrl_match_gpio_range(pctldev, gpio);
		अगर (range) अणु
			*outdev = pctldev;
			*outrange = range;
			mutex_unlock(&pinctrldev_list_mutex);
			वापस 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&pinctrldev_list_mutex);

	वापस -EPROBE_DEFER;
पूर्ण

/**
 * pinctrl_add_gpio_range() - रेजिस्टर a GPIO range क्रम a controller
 * @pctldev: pin controller device to add the range to
 * @range: the GPIO range to add
 *
 * This adds a range of GPIOs to be handled by a certain pin controller. Call
 * this to रेजिस्टर handled ranges after रेजिस्टरing your pin controller.
 */
व्योम pinctrl_add_gpio_range(काष्ठा pinctrl_dev *pctldev,
			    काष्ठा pinctrl_gpio_range *range)
अणु
	mutex_lock(&pctldev->mutex);
	list_add_tail(&range->node, &pctldev->gpio_ranges);
	mutex_unlock(&pctldev->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_add_gpio_range);

व्योम pinctrl_add_gpio_ranges(काष्ठा pinctrl_dev *pctldev,
			     काष्ठा pinctrl_gpio_range *ranges,
			     अचिन्हित nranges)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nranges; i++)
		pinctrl_add_gpio_range(pctldev, &ranges[i]);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_add_gpio_ranges);

काष्ठा pinctrl_dev *pinctrl_find_and_add_gpio_range(स्थिर अक्षर *devname,
		काष्ठा pinctrl_gpio_range *range)
अणु
	काष्ठा pinctrl_dev *pctldev;

	pctldev = get_pinctrl_dev_from_devname(devname);

	/*
	 * If we can't find this device, let's assume that is because
	 * it has not probed yet, so the driver trying to रेजिस्टर this
	 * range need to defer probing.
	 */
	अगर (!pctldev) अणु
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण
	pinctrl_add_gpio_range(pctldev, range);

	वापस pctldev;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_find_and_add_gpio_range);

पूर्णांक pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev, स्थिर अक्षर *pin_group,
				स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;
	पूर्णांक gs;

	अगर (!pctlops->get_group_pins)
		वापस -EINVAL;

	gs = pinctrl_get_group_selector(pctldev, pin_group);
	अगर (gs < 0)
		वापस gs;

	वापस pctlops->get_group_pins(pctldev, gs, pins, num_pins);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_get_group_pins);

काष्ठा pinctrl_gpio_range *
pinctrl_find_gpio_range_from_pin_nolock(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक pin)
अणु
	काष्ठा pinctrl_gpio_range *range;

	/* Loop over the ranges */
	list_क्रम_each_entry(range, &pctldev->gpio_ranges, node) अणु
		/* Check अगर we're in the valid range */
		अगर (range->pins) अणु
			पूर्णांक a;
			क्रम (a = 0; a < range->npins; a++) अणु
				अगर (range->pins[a] == pin)
					वापस range;
			पूर्ण
		पूर्ण अन्यथा अगर (pin >= range->pin_base &&
			   pin < range->pin_base + range->npins)
			वापस range;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_find_gpio_range_from_pin_nolock);

/**
 * pinctrl_find_gpio_range_from_pin() - locate the GPIO range क्रम a pin
 * @pctldev: the pin controller device to look in
 * @pin: a controller-local number to find the range क्रम
 */
काष्ठा pinctrl_gpio_range *
pinctrl_find_gpio_range_from_pin(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक pin)
अणु
	काष्ठा pinctrl_gpio_range *range;

	mutex_lock(&pctldev->mutex);
	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	mutex_unlock(&pctldev->mutex);

	वापस range;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_find_gpio_range_from_pin);

/**
 * pinctrl_हटाओ_gpio_range() - हटाओ a range of GPIOs from a pin controller
 * @pctldev: pin controller device to हटाओ the range from
 * @range: the GPIO range to हटाओ
 */
व्योम pinctrl_हटाओ_gpio_range(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा pinctrl_gpio_range *range)
अणु
	mutex_lock(&pctldev->mutex);
	list_del(&range->node);
	mutex_unlock(&pctldev->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_हटाओ_gpio_range);

#अगर_घोषित CONFIG_GENERIC_PINCTRL_GROUPS

/**
 * pinctrl_generic_get_group_count() - वापसs the number of pin groups
 * @pctldev: pin controller device
 */
पूर्णांक pinctrl_generic_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस pctldev->num_groups;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_generic_get_group_count);

/**
 * pinctrl_generic_get_group_name() - वापसs the name of a pin group
 * @pctldev: pin controller device
 * @selector: group number
 */
स्थिर अक्षर *pinctrl_generic_get_group_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक selector)
अणु
	काष्ठा group_desc *group;

	group = radix_tree_lookup(&pctldev->pin_group_tree,
				  selector);
	अगर (!group)
		वापस शून्य;

	वापस group->name;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_generic_get_group_name);

/**
 * pinctrl_generic_get_group_pins() - माला_लो the pin group pins
 * @pctldev: pin controller device
 * @selector: group number
 * @pins: pins in the group
 * @num_pins: number of pins in the group
 */
पूर्णांक pinctrl_generic_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक selector,
				   स्थिर अचिन्हित पूर्णांक **pins,
				   अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा group_desc *group;

	group = radix_tree_lookup(&pctldev->pin_group_tree,
				  selector);
	अगर (!group) अणु
		dev_err(pctldev->dev, "%s could not find pingroup%i\n",
			__func__, selector);
		वापस -EINVAL;
	पूर्ण

	*pins = group->pins;
	*num_pins = group->num_pins;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_generic_get_group_pins);

/**
 * pinctrl_generic_get_group() - वापसs a pin group based on the number
 * @pctldev: pin controller device
 * @selector: group number
 */
काष्ठा group_desc *pinctrl_generic_get_group(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक selector)
अणु
	काष्ठा group_desc *group;

	group = radix_tree_lookup(&pctldev->pin_group_tree,
				  selector);
	अगर (!group)
		वापस शून्य;

	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_generic_get_group);

अटल पूर्णांक pinctrl_generic_group_name_to_selector(काष्ठा pinctrl_dev *pctldev,
						  स्थिर अक्षर *function)
अणु
	स्थिर काष्ठा pinctrl_ops *ops = pctldev->desc->pctlops;
	पूर्णांक ngroups = ops->get_groups_count(pctldev);
	पूर्णांक selector = 0;

	/* See अगर this pctldev has this group */
	जबतक (selector < ngroups) अणु
		स्थिर अक्षर *gname = ops->get_group_name(pctldev, selector);

		अगर (gname && !म_भेद(function, gname))
			वापस selector;

		selector++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * pinctrl_generic_add_group() - adds a new pin group
 * @pctldev: pin controller device
 * @name: name of the pin group
 * @pins: pins in the pin group
 * @num_pins: number of pins in the pin group
 * @data: pin controller driver specअगरic data
 *
 * Note that the caller must take care of locking.
 */
पूर्णांक pinctrl_generic_add_group(काष्ठा pinctrl_dev *pctldev, स्थिर अक्षर *name,
			      पूर्णांक *pins, पूर्णांक num_pins, व्योम *data)
अणु
	काष्ठा group_desc *group;
	पूर्णांक selector;

	अगर (!name)
		वापस -EINVAL;

	selector = pinctrl_generic_group_name_to_selector(pctldev, name);
	अगर (selector >= 0)
		वापस selector;

	selector = pctldev->num_groups;

	group = devm_kzalloc(pctldev->dev, माप(*group), GFP_KERNEL);
	अगर (!group)
		वापस -ENOMEM;

	group->name = name;
	group->pins = pins;
	group->num_pins = num_pins;
	group->data = data;

	radix_tree_insert(&pctldev->pin_group_tree, selector, group);

	pctldev->num_groups++;

	वापस selector;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_generic_add_group);

/**
 * pinctrl_generic_हटाओ_group() - हटाओs a numbered pin group
 * @pctldev: pin controller device
 * @selector: group number
 *
 * Note that the caller must take care of locking.
 */
पूर्णांक pinctrl_generic_हटाओ_group(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा group_desc *group;

	group = radix_tree_lookup(&pctldev->pin_group_tree,
				  selector);
	अगर (!group)
		वापस -ENOENT;

	radix_tree_delete(&pctldev->pin_group_tree, selector);
	devm_kमुक्त(pctldev->dev, group);

	pctldev->num_groups--;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_generic_हटाओ_group);

/**
 * pinctrl_generic_मुक्त_groups() - हटाओs all pin groups
 * @pctldev: pin controller device
 *
 * Note that the caller must take care of locking. The pinctrl groups
 * are allocated with devm_kzalloc() so no need to मुक्त them here.
 */
अटल व्योम pinctrl_generic_मुक्त_groups(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	radix_tree_क्रम_each_slot(slot, &pctldev->pin_group_tree, &iter, 0)
		radix_tree_delete(&pctldev->pin_group_tree, iter.index);

	pctldev->num_groups = 0;
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम pinctrl_generic_मुक्त_groups(काष्ठा pinctrl_dev *pctldev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_PINCTRL_GROUPS */

/**
 * pinctrl_get_group_selector() - वापसs the group selector क्रम a group
 * @pctldev: the pin controller handling the group
 * @pin_group: the pin group to look up
 */
पूर्णांक pinctrl_get_group_selector(काष्ठा pinctrl_dev *pctldev,
			       स्थिर अक्षर *pin_group)
अणु
	स्थिर काष्ठा pinctrl_ops *pctlops = pctldev->desc->pctlops;
	अचिन्हित ngroups = pctlops->get_groups_count(pctldev);
	अचिन्हित group_selector = 0;

	जबतक (group_selector < ngroups) अणु
		स्थिर अक्षर *gname = pctlops->get_group_name(pctldev,
							    group_selector);
		अगर (gname && !म_भेद(gname, pin_group)) अणु
			dev_dbg(pctldev->dev,
				"found group selector %u for %s\n",
				group_selector,
				pin_group);
			वापस group_selector;
		पूर्ण

		group_selector++;
	पूर्ण

	dev_err(pctldev->dev, "does not have pin group %s\n",
		pin_group);

	वापस -EINVAL;
पूर्ण

bool pinctrl_gpio_can_use_line(अचिन्हित gpio)
अणु
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_gpio_range *range;
	bool result;
	पूर्णांक pin;

	/*
	 * Try to obtain GPIO range, अगर it fails
	 * we're probably dealing with GPIO driver
	 * without a backing pin controller - bail out.
	 */
	अगर (pinctrl_get_device_gpio_range(gpio, &pctldev, &range))
		वापस true;

	mutex_lock(&pctldev->mutex);

	/* Convert to the pin controllers number space */
	pin = gpio_to_pin(range, gpio);

	result = pinmux_can_be_used_क्रम_gpio(pctldev, pin);

	mutex_unlock(&pctldev->mutex);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_gpio_can_use_line);

/**
 * pinctrl_gpio_request() - request a single pin to be used as GPIO
 * @gpio: the GPIO pin number from the GPIO subप्रणाली number space
 *
 * This function should *ONLY* be used from gpiolib-based GPIO drivers,
 * as part of their gpio_request() semantics, platक्रमms and inभागidual drivers
 * shall *NOT* request GPIO pins to be muxed in.
 */
पूर्णांक pinctrl_gpio_request(अचिन्हित gpio)
अणु
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_gpio_range *range;
	पूर्णांक ret;
	पूर्णांक pin;

	ret = pinctrl_get_device_gpio_range(gpio, &pctldev, &range);
	अगर (ret) अणु
		अगर (pinctrl_पढ़ोy_क्रम_gpio_range(gpio))
			ret = 0;
		वापस ret;
	पूर्ण

	mutex_lock(&pctldev->mutex);

	/* Convert to the pin controllers number space */
	pin = gpio_to_pin(range, gpio);

	ret = pinmux_request_gpio(pctldev, range, pin, gpio);

	mutex_unlock(&pctldev->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_gpio_request);

/**
 * pinctrl_gpio_मुक्त() - मुक्त control on a single pin, currently used as GPIO
 * @gpio: the GPIO pin number from the GPIO subप्रणाली number space
 *
 * This function should *ONLY* be used from gpiolib-based GPIO drivers,
 * as part of their gpio_मुक्त() semantics, platक्रमms and inभागidual drivers
 * shall *NOT* request GPIO pins to be muxed out.
 */
व्योम pinctrl_gpio_मुक्त(अचिन्हित gpio)
अणु
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_gpio_range *range;
	पूर्णांक ret;
	पूर्णांक pin;

	ret = pinctrl_get_device_gpio_range(gpio, &pctldev, &range);
	अगर (ret) अणु
		वापस;
	पूर्ण
	mutex_lock(&pctldev->mutex);

	/* Convert to the pin controllers number space */
	pin = gpio_to_pin(range, gpio);

	pinmux_मुक्त_gpio(pctldev, pin, range);

	mutex_unlock(&pctldev->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_gpio_मुक्त);

अटल पूर्णांक pinctrl_gpio_direction(अचिन्हित gpio, bool input)
अणु
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा pinctrl_gpio_range *range;
	पूर्णांक ret;
	पूर्णांक pin;

	ret = pinctrl_get_device_gpio_range(gpio, &pctldev, &range);
	अगर (ret) अणु
		वापस ret;
	पूर्ण

	mutex_lock(&pctldev->mutex);

	/* Convert to the pin controllers number space */
	pin = gpio_to_pin(range, gpio);
	ret = pinmux_gpio_direction(pctldev, range, pin, input);

	mutex_unlock(&pctldev->mutex);

	वापस ret;
पूर्ण

/**
 * pinctrl_gpio_direction_input() - request a GPIO pin to go पूर्णांकo input mode
 * @gpio: the GPIO pin number from the GPIO subप्रणाली number space
 *
 * This function should *ONLY* be used from gpiolib-based GPIO drivers,
 * as part of their gpio_direction_input() semantics, platक्रमms and inभागidual
 * drivers shall *NOT* touch pin control GPIO calls.
 */
पूर्णांक pinctrl_gpio_direction_input(अचिन्हित gpio)
अणु
	वापस pinctrl_gpio_direction(gpio, true);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_gpio_direction_input);

/**
 * pinctrl_gpio_direction_output() - request a GPIO pin to go पूर्णांकo output mode
 * @gpio: the GPIO pin number from the GPIO subप्रणाली number space
 *
 * This function should *ONLY* be used from gpiolib-based GPIO drivers,
 * as part of their gpio_direction_output() semantics, platक्रमms and inभागidual
 * drivers shall *NOT* touch pin control GPIO calls.
 */
पूर्णांक pinctrl_gpio_direction_output(अचिन्हित gpio)
अणु
	वापस pinctrl_gpio_direction(gpio, false);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_gpio_direction_output);

/**
 * pinctrl_gpio_set_config() - Apply config to given GPIO pin
 * @gpio: the GPIO pin number from the GPIO subप्रणाली number space
 * @config: the configuration to apply to the GPIO
 *
 * This function should *ONLY* be used from gpiolib-based GPIO drivers, अगर
 * they need to call the underlying pin controller to change GPIO config
 * (क्रम example set debounce समय).
 */
पूर्णांक pinctrl_gpio_set_config(अचिन्हित gpio, अचिन्हित दीर्घ config)
अणु
	अचिन्हित दीर्घ configs[] = अणु config पूर्ण;
	काष्ठा pinctrl_gpio_range *range;
	काष्ठा pinctrl_dev *pctldev;
	पूर्णांक ret, pin;

	ret = pinctrl_get_device_gpio_range(gpio, &pctldev, &range);
	अगर (ret)
		वापस ret;

	mutex_lock(&pctldev->mutex);
	pin = gpio_to_pin(range, gpio);
	ret = pinconf_set_config(pctldev, pin, configs, ARRAY_SIZE(configs));
	mutex_unlock(&pctldev->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_gpio_set_config);

अटल काष्ठा pinctrl_state *find_state(काष्ठा pinctrl *p,
					स्थिर अक्षर *name)
अणु
	काष्ठा pinctrl_state *state;

	list_क्रम_each_entry(state, &p->states, node)
		अगर (!म_भेद(state->name, name))
			वापस state;

	वापस शून्य;
पूर्ण

अटल काष्ठा pinctrl_state *create_state(काष्ठा pinctrl *p,
					  स्थिर अक्षर *name)
अणु
	काष्ठा pinctrl_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस ERR_PTR(-ENOMEM);

	state->name = name;
	INIT_LIST_HEAD(&state->settings);

	list_add_tail(&state->node, &p->states);

	वापस state;
पूर्ण

अटल पूर्णांक add_setting(काष्ठा pinctrl *p, काष्ठा pinctrl_dev *pctldev,
		       स्थिर काष्ठा pinctrl_map *map)
अणु
	काष्ठा pinctrl_state *state;
	काष्ठा pinctrl_setting *setting;
	पूर्णांक ret;

	state = find_state(p, map->name);
	अगर (!state)
		state = create_state(p, map->name);
	अगर (IS_ERR(state))
		वापस PTR_ERR(state);

	अगर (map->type == PIN_MAP_TYPE_DUMMY_STATE)
		वापस 0;

	setting = kzalloc(माप(*setting), GFP_KERNEL);
	अगर (!setting)
		वापस -ENOMEM;

	setting->type = map->type;

	अगर (pctldev)
		setting->pctldev = pctldev;
	अन्यथा
		setting->pctldev =
			get_pinctrl_dev_from_devname(map->ctrl_dev_name);
	अगर (!setting->pctldev) अणु
		kमुक्त(setting);
		/* Do not defer probing of hogs (circular loop) */
		अगर (!म_भेद(map->ctrl_dev_name, map->dev_name))
			वापस -ENODEV;
		/*
		 * OK let us guess that the driver is not there yet, and
		 * let's defer obtaining this pinctrl handle to later...
		 */
		dev_info(p->dev, "unknown pinctrl device %s in map entry, deferring probe",
			map->ctrl_dev_name);
		वापस -EPROBE_DEFER;
	पूर्ण

	setting->dev_name = map->dev_name;

	चयन (map->type) अणु
	हाल PIN_MAP_TYPE_MUX_GROUP:
		ret = pinmux_map_to_setting(map, setting);
		अवरोध;
	हाल PIN_MAP_TYPE_CONFIGS_PIN:
	हाल PIN_MAP_TYPE_CONFIGS_GROUP:
		ret = pinconf_map_to_setting(map, setting);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (ret < 0) अणु
		kमुक्त(setting);
		वापस ret;
	पूर्ण

	list_add_tail(&setting->node, &state->settings);

	वापस 0;
पूर्ण

अटल काष्ठा pinctrl *find_pinctrl(काष्ठा device *dev)
अणु
	काष्ठा pinctrl *p;

	mutex_lock(&pinctrl_list_mutex);
	list_क्रम_each_entry(p, &pinctrl_list, node)
		अगर (p->dev == dev) अणु
			mutex_unlock(&pinctrl_list_mutex);
			वापस p;
		पूर्ण

	mutex_unlock(&pinctrl_list_mutex);
	वापस शून्य;
पूर्ण

अटल व्योम pinctrl_मुक्त(काष्ठा pinctrl *p, bool inlist);

अटल काष्ठा pinctrl *create_pinctrl(काष्ठा device *dev,
				      काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pinctrl *p;
	स्थिर अक्षर *devname;
	काष्ठा pinctrl_maps *maps_node;
	पूर्णांक i;
	स्थिर काष्ठा pinctrl_map *map;
	पूर्णांक ret;

	/*
	 * create the state cookie holder काष्ठा pinctrl क्रम each
	 * mapping, this is what consumers will get when requesting
	 * a pin control handle with pinctrl_get()
	 */
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);
	p->dev = dev;
	INIT_LIST_HEAD(&p->states);
	INIT_LIST_HEAD(&p->dt_maps);

	ret = pinctrl_dt_to_map(p, pctldev);
	अगर (ret < 0) अणु
		kमुक्त(p);
		वापस ERR_PTR(ret);
	पूर्ण

	devname = dev_name(dev);

	mutex_lock(&pinctrl_maps_mutex);
	/* Iterate over the pin control maps to locate the right ones */
	क्रम_each_maps(maps_node, i, map) अणु
		/* Map must be क्रम this device */
		अगर (म_भेद(map->dev_name, devname))
			जारी;
		/*
		 * If pctldev is not null, we are claiming hog क्रम it,
		 * that means, setting that is served by pctldev by itself.
		 *
		 * Thus we must skip map that is क्रम this device but is served
		 * by other device.
		 */
		अगर (pctldev &&
		    म_भेद(dev_name(pctldev->dev), map->ctrl_dev_name))
			जारी;

		ret = add_setting(p, pctldev, map);
		/*
		 * At this poपूर्णांक the adding of a setting may:
		 *
		 * - Defer, अगर the pinctrl device is not yet available
		 * - Fail, अगर the pinctrl device is not yet available,
		 *   AND the setting is a hog. We cannot defer that, since
		 *   the hog will kick in immediately after the device
		 *   is रेजिस्टरed.
		 *
		 * If the error वापसed was not -EPROBE_DEFER then we
		 * accumulate the errors to see अगर we end up with
		 * an -EPROBE_DEFER later, as that is the worst हाल.
		 */
		अगर (ret == -EPROBE_DEFER) अणु
			pinctrl_मुक्त(p, false);
			mutex_unlock(&pinctrl_maps_mutex);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण
	mutex_unlock(&pinctrl_maps_mutex);

	अगर (ret < 0) अणु
		/* If some other error than deferral occurred, वापस here */
		pinctrl_मुक्त(p, false);
		वापस ERR_PTR(ret);
	पूर्ण

	kref_init(&p->users);

	/* Add the pinctrl handle to the global list */
	mutex_lock(&pinctrl_list_mutex);
	list_add_tail(&p->node, &pinctrl_list);
	mutex_unlock(&pinctrl_list_mutex);

	वापस p;
पूर्ण

/**
 * pinctrl_get() - retrieves the pinctrl handle क्रम a device
 * @dev: the device to obtain the handle क्रम
 */
काष्ठा pinctrl *pinctrl_get(काष्ठा device *dev)
अणु
	काष्ठा pinctrl *p;

	अगर (WARN_ON(!dev))
		वापस ERR_PTR(-EINVAL);

	/*
	 * See अगर somebody अन्यथा (such as the device core) has alपढ़ोy
	 * obtained a handle to the pinctrl क्रम this device. In that हाल,
	 * वापस another poपूर्णांकer to it.
	 */
	p = find_pinctrl(dev);
	अगर (p) अणु
		dev_dbg(dev, "obtain a copy of previously claimed pinctrl\n");
		kref_get(&p->users);
		वापस p;
	पूर्ण

	वापस create_pinctrl(dev, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_get);

अटल व्योम pinctrl_मुक्त_setting(bool disable_setting,
				 काष्ठा pinctrl_setting *setting)
अणु
	चयन (setting->type) अणु
	हाल PIN_MAP_TYPE_MUX_GROUP:
		अगर (disable_setting)
			pinmux_disable_setting(setting);
		pinmux_मुक्त_setting(setting);
		अवरोध;
	हाल PIN_MAP_TYPE_CONFIGS_PIN:
	हाल PIN_MAP_TYPE_CONFIGS_GROUP:
		pinconf_मुक्त_setting(setting);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pinctrl_मुक्त(काष्ठा pinctrl *p, bool inlist)
अणु
	काष्ठा pinctrl_state *state, *n1;
	काष्ठा pinctrl_setting *setting, *n2;

	mutex_lock(&pinctrl_list_mutex);
	list_क्रम_each_entry_safe(state, n1, &p->states, node) अणु
		list_क्रम_each_entry_safe(setting, n2, &state->settings, node) अणु
			pinctrl_मुक्त_setting(state == p->state, setting);
			list_del(&setting->node);
			kमुक्त(setting);
		पूर्ण
		list_del(&state->node);
		kमुक्त(state);
	पूर्ण

	pinctrl_dt_मुक्त_maps(p);

	अगर (inlist)
		list_del(&p->node);
	kमुक्त(p);
	mutex_unlock(&pinctrl_list_mutex);
पूर्ण

/**
 * pinctrl_release() - release the pinctrl handle
 * @kref: the kref in the pinctrl being released
 */
अटल व्योम pinctrl_release(काष्ठा kref *kref)
अणु
	काष्ठा pinctrl *p = container_of(kref, काष्ठा pinctrl, users);

	pinctrl_मुक्त(p, true);
पूर्ण

/**
 * pinctrl_put() - decrease use count on a previously claimed pinctrl handle
 * @p: the pinctrl handle to release
 */
व्योम pinctrl_put(काष्ठा pinctrl *p)
अणु
	kref_put(&p->users, pinctrl_release);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_put);

/**
 * pinctrl_lookup_state() - retrieves a state handle from a pinctrl handle
 * @p: the pinctrl handle to retrieve the state from
 * @name: the state name to retrieve
 */
काष्ठा pinctrl_state *pinctrl_lookup_state(काष्ठा pinctrl *p,
						 स्थिर अक्षर *name)
अणु
	काष्ठा pinctrl_state *state;

	state = find_state(p, name);
	अगर (!state) अणु
		अगर (pinctrl_dummy_state) अणु
			/* create dummy state */
			dev_dbg(p->dev, "using pinctrl dummy state (%s)\n",
				name);
			state = create_state(p, name);
		पूर्ण अन्यथा
			state = ERR_PTR(-ENODEV);
	पूर्ण

	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_lookup_state);

अटल व्योम pinctrl_link_add(काष्ठा pinctrl_dev *pctldev,
			     काष्ठा device *consumer)
अणु
	अगर (pctldev->desc->link_consumers)
		device_link_add(consumer, pctldev->dev,
				DL_FLAG_PM_RUNTIME |
				DL_FLAG_AUTOREMOVE_CONSUMER);
पूर्ण

/**
 * pinctrl_commit_state() - select/activate/program a pinctrl state to HW
 * @p: the pinctrl handle क्रम the device that requests configuration
 * @state: the state handle to select/activate/program
 */
अटल पूर्णांक pinctrl_commit_state(काष्ठा pinctrl *p, काष्ठा pinctrl_state *state)
अणु
	काष्ठा pinctrl_setting *setting, *setting2;
	काष्ठा pinctrl_state *old_state = p->state;
	पूर्णांक ret;

	अगर (p->state) अणु
		/*
		 * For each pinmux setting in the old state, क्रमget SW's record
		 * of mux owner क्रम that pingroup. Any pingroups which are
		 * still owned by the new state will be re-acquired by the call
		 * to pinmux_enable_setting() in the loop below.
		 */
		list_क्रम_each_entry(setting, &p->state->settings, node) अणु
			अगर (setting->type != PIN_MAP_TYPE_MUX_GROUP)
				जारी;
			pinmux_disable_setting(setting);
		पूर्ण
	पूर्ण

	p->state = शून्य;

	/* Apply all the settings क्रम the new state - pinmux first */
	list_क्रम_each_entry(setting, &state->settings, node) अणु
		चयन (setting->type) अणु
		हाल PIN_MAP_TYPE_MUX_GROUP:
			ret = pinmux_enable_setting(setting);
			अवरोध;
		हाल PIN_MAP_TYPE_CONFIGS_PIN:
		हाल PIN_MAP_TYPE_CONFIGS_GROUP:
			ret = 0;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (ret < 0)
			जाओ unapply_new_state;

		/* Do not link hogs (circular dependency) */
		अगर (p != setting->pctldev->p)
			pinctrl_link_add(setting->pctldev, p->dev);
	पूर्ण

	/* Apply all the settings क्रम the new state - pinconf after */
	list_क्रम_each_entry(setting, &state->settings, node) अणु
		चयन (setting->type) अणु
		हाल PIN_MAP_TYPE_MUX_GROUP:
			ret = 0;
			अवरोध;
		हाल PIN_MAP_TYPE_CONFIGS_PIN:
		हाल PIN_MAP_TYPE_CONFIGS_GROUP:
			ret = pinconf_apply_setting(setting);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (ret < 0) अणु
			जाओ unapply_new_state;
		पूर्ण

		/* Do not link hogs (circular dependency) */
		अगर (p != setting->pctldev->p)
			pinctrl_link_add(setting->pctldev, p->dev);
	पूर्ण

	p->state = state;

	वापस 0;

unapply_new_state:
	dev_err(p->dev, "Error applying setting, reverse things back\n");

	list_क्रम_each_entry(setting2, &state->settings, node) अणु
		अगर (&setting2->node == &setting->node)
			अवरोध;
		/*
		 * All we can करो here is pinmux_disable_setting.
		 * That means that some pins are muxed dअगरferently now
		 * than they were beक्रमe applying the setting (We can't
		 * "unmux a pin"!), but it's not a big deal since the pins
		 * are मुक्त to be muxed by another apply_setting.
		 */
		अगर (setting2->type == PIN_MAP_TYPE_MUX_GROUP)
			pinmux_disable_setting(setting2);
	पूर्ण

	/* There's no infinite recursive loop here because p->state is शून्य */
	अगर (old_state)
		pinctrl_select_state(p, old_state);

	वापस ret;
पूर्ण

/**
 * pinctrl_select_state() - select/activate/program a pinctrl state to HW
 * @p: the pinctrl handle क्रम the device that requests configuration
 * @state: the state handle to select/activate/program
 */
पूर्णांक pinctrl_select_state(काष्ठा pinctrl *p, काष्ठा pinctrl_state *state)
अणु
	अगर (p->state == state)
		वापस 0;

	वापस pinctrl_commit_state(p, state);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_select_state);

अटल व्योम devm_pinctrl_release(काष्ठा device *dev, व्योम *res)
अणु
	pinctrl_put(*(काष्ठा pinctrl **)res);
पूर्ण

/**
 * devm_pinctrl_get() - Resource managed pinctrl_get()
 * @dev: the device to obtain the handle क्रम
 *
 * If there is a need to explicitly destroy the वापसed काष्ठा pinctrl,
 * devm_pinctrl_put() should be used, rather than plain pinctrl_put().
 */
काष्ठा pinctrl *devm_pinctrl_get(काष्ठा device *dev)
अणु
	काष्ठा pinctrl **ptr, *p;

	ptr = devres_alloc(devm_pinctrl_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	p = pinctrl_get(dev);
	अगर (!IS_ERR(p)) अणु
		*ptr = p;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(devm_pinctrl_get);

अटल पूर्णांक devm_pinctrl_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा pinctrl **p = res;

	वापस *p == data;
पूर्ण

/**
 * devm_pinctrl_put() - Resource managed pinctrl_put()
 * @p: the pinctrl handle to release
 *
 * Deallocate a काष्ठा pinctrl obtained via devm_pinctrl_get(). Normally
 * this function will not need to be called and the resource management
 * code will ensure that the resource is मुक्तd.
 */
व्योम devm_pinctrl_put(काष्ठा pinctrl *p)
अणु
	WARN_ON(devres_release(p->dev, devm_pinctrl_release,
			       devm_pinctrl_match, p));
पूर्ण
EXPORT_SYMBOL_GPL(devm_pinctrl_put);

/**
 * pinctrl_रेजिस्टर_mappings() - रेजिस्टर a set of pin controller mappings
 * @maps: the pincontrol mappings table to रेजिस्टर. Note the pinctrl-core
 *	keeps a reference to the passed in maps, so they should _not_ be
 *	marked with __initdata.
 * @num_maps: the number of maps in the mapping table
 */
पूर्णांक pinctrl_रेजिस्टर_mappings(स्थिर काष्ठा pinctrl_map *maps,
			      अचिन्हित num_maps)
अणु
	पूर्णांक i, ret;
	काष्ठा pinctrl_maps *maps_node;

	pr_debug("add %u pinctrl maps\n", num_maps);

	/* First sanity check the new mapping */
	क्रम (i = 0; i < num_maps; i++) अणु
		अगर (!maps[i].dev_name) अणु
			pr_err("failed to register map %s (%d): no device given\n",
			       maps[i].name, i);
			वापस -EINVAL;
		पूर्ण

		अगर (!maps[i].name) अणु
			pr_err("failed to register map %d: no map name given\n",
			       i);
			वापस -EINVAL;
		पूर्ण

		अगर (maps[i].type != PIN_MAP_TYPE_DUMMY_STATE &&
				!maps[i].ctrl_dev_name) अणु
			pr_err("failed to register map %s (%d): no pin control device given\n",
			       maps[i].name, i);
			वापस -EINVAL;
		पूर्ण

		चयन (maps[i].type) अणु
		हाल PIN_MAP_TYPE_DUMMY_STATE:
			अवरोध;
		हाल PIN_MAP_TYPE_MUX_GROUP:
			ret = pinmux_validate_map(&maps[i], i);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		हाल PIN_MAP_TYPE_CONFIGS_PIN:
		हाल PIN_MAP_TYPE_CONFIGS_GROUP:
			ret = pinconf_validate_map(&maps[i], i);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		शेष:
			pr_err("failed to register map %s (%d): invalid type given\n",
			       maps[i].name, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	maps_node = kzalloc(माप(*maps_node), GFP_KERNEL);
	अगर (!maps_node)
		वापस -ENOMEM;

	maps_node->maps = maps;
	maps_node->num_maps = num_maps;

	mutex_lock(&pinctrl_maps_mutex);
	list_add_tail(&maps_node->node, &pinctrl_maps);
	mutex_unlock(&pinctrl_maps_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_रेजिस्टर_mappings);

/**
 * pinctrl_unरेजिस्टर_mappings() - unरेजिस्टर a set of pin controller mappings
 * @map: the pincontrol mappings table passed to pinctrl_रेजिस्टर_mappings()
 *	when रेजिस्टरing the mappings.
 */
व्योम pinctrl_unरेजिस्टर_mappings(स्थिर काष्ठा pinctrl_map *map)
अणु
	काष्ठा pinctrl_maps *maps_node;

	mutex_lock(&pinctrl_maps_mutex);
	list_क्रम_each_entry(maps_node, &pinctrl_maps, node) अणु
		अगर (maps_node->maps == map) अणु
			list_del(&maps_node->node);
			kमुक्त(maps_node);
			mutex_unlock(&pinctrl_maps_mutex);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&pinctrl_maps_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_unरेजिस्टर_mappings);

/**
 * pinctrl_क्रमce_sleep() - turn a given controller device पूर्णांकo sleep state
 * @pctldev: pin controller device
 */
पूर्णांक pinctrl_क्रमce_sleep(काष्ठा pinctrl_dev *pctldev)
अणु
	अगर (!IS_ERR(pctldev->p) && !IS_ERR(pctldev->hog_sleep))
		वापस pinctrl_commit_state(pctldev->p, pctldev->hog_sleep);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_क्रमce_sleep);

/**
 * pinctrl_क्रमce_शेष() - turn a given controller device पूर्णांकo शेष state
 * @pctldev: pin controller device
 */
पूर्णांक pinctrl_क्रमce_शेष(काष्ठा pinctrl_dev *pctldev)
अणु
	अगर (!IS_ERR(pctldev->p) && !IS_ERR(pctldev->hog_शेष))
		वापस pinctrl_commit_state(pctldev->p, pctldev->hog_शेष);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_क्रमce_शेष);

/**
 * pinctrl_init_करोne() - tell pinctrl probe is करोne
 *
 * We'll use this समय to चयन the pins from "init" to "default" unless the
 * driver selected some other state.
 *
 * @dev: device to that's करोne probing
 */
पूर्णांक pinctrl_init_करोne(काष्ठा device *dev)
अणु
	काष्ठा dev_pin_info *pins = dev->pins;
	पूर्णांक ret;

	अगर (!pins)
		वापस 0;

	अगर (IS_ERR(pins->init_state))
		वापस 0; /* No such state */

	अगर (pins->p->state != pins->init_state)
		वापस 0; /* Not at init anyway */

	अगर (IS_ERR(pins->शेष_state))
		वापस 0; /* No शेष state */

	ret = pinctrl_select_state(pins->p, pins->शेष_state);
	अगर (ret)
		dev_err(dev, "failed to activate default pinctrl state\n");

	वापस ret;
पूर्ण

अटल पूर्णांक pinctrl_select_bound_state(काष्ठा device *dev,
				      काष्ठा pinctrl_state *state)
अणु
	काष्ठा dev_pin_info *pins = dev->pins;
	पूर्णांक ret;

	अगर (IS_ERR(state))
		वापस 0; /* No such state */
	ret = pinctrl_select_state(pins->p, state);
	अगर (ret)
		dev_err(dev, "failed to activate pinctrl state %s\n",
			state->name);
	वापस ret;
पूर्ण

/**
 * pinctrl_select_शेष_state() - select शेष pinctrl state
 * @dev: device to select शेष state क्रम
 */
पूर्णांक pinctrl_select_शेष_state(काष्ठा device *dev)
अणु
	अगर (!dev->pins)
		वापस 0;

	वापस pinctrl_select_bound_state(dev, dev->pins->शेष_state);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_select_शेष_state);

#अगर_घोषित CONFIG_PM

/**
 * pinctrl_pm_select_शेष_state() - select शेष pinctrl state क्रम PM
 * @dev: device to select शेष state क्रम
 */
पूर्णांक pinctrl_pm_select_शेष_state(काष्ठा device *dev)
अणु
	वापस pinctrl_select_शेष_state(dev);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_pm_select_शेष_state);

/**
 * pinctrl_pm_select_sleep_state() - select sleep pinctrl state क्रम PM
 * @dev: device to select sleep state क्रम
 */
पूर्णांक pinctrl_pm_select_sleep_state(काष्ठा device *dev)
अणु
	अगर (!dev->pins)
		वापस 0;

	वापस pinctrl_select_bound_state(dev, dev->pins->sleep_state);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_pm_select_sleep_state);

/**
 * pinctrl_pm_select_idle_state() - select idle pinctrl state क्रम PM
 * @dev: device to select idle state क्रम
 */
पूर्णांक pinctrl_pm_select_idle_state(काष्ठा device *dev)
अणु
	अगर (!dev->pins)
		वापस 0;

	वापस pinctrl_select_bound_state(dev, dev->pins->idle_state);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_pm_select_idle_state);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक pinctrl_pins_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev = s->निजी;
	स्थिर काष्ठा pinctrl_ops *ops = pctldev->desc->pctlops;
	अचिन्हित i, pin;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा pinctrl_gpio_range *range;
	काष्ठा gpio_chip *chip;
	पूर्णांक gpio_num;
#पूर्ण_अगर

	seq_म_लिखो(s, "registered pins: %d\n", pctldev->desc->npins);

	mutex_lock(&pctldev->mutex);

	/* The pin number can be retrived from the pin controller descriptor */
	क्रम (i = 0; i < pctldev->desc->npins; i++) अणु
		काष्ठा pin_desc *desc;

		pin = pctldev->desc->pins[i].number;
		desc = pin_desc_get(pctldev, pin);
		/* Pin space may be sparse */
		अगर (!desc)
			जारी;

		seq_म_लिखो(s, "pin %d (%s) ", pin, desc->name);

#अगर_घोषित CONFIG_GPIOLIB
		gpio_num = -1;
		list_क्रम_each_entry(range, &pctldev->gpio_ranges, node) अणु
			अगर ((pin >= range->pin_base) &&
			    (pin < (range->pin_base + range->npins))) अणु
				gpio_num = range->base + (pin - range->pin_base);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (gpio_num >= 0)
			chip = gpio_to_chip(gpio_num);
		अन्यथा
			chip = शून्य;
		अगर (chip)
			seq_म_लिखो(s, "%u:%s ", gpio_num - chip->gpiodev->base, chip->label);
		अन्यथा
			seq_माला_दो(s, "0:? ");
#पूर्ण_अगर

		/* Driver-specअगरic info per pin */
		अगर (ops->pin_dbg_show)
			ops->pin_dbg_show(pctldev, s, pin);

		seq_माला_दो(s, "\n");
	पूर्ण

	mutex_unlock(&pctldev->mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pinctrl_pins);

अटल पूर्णांक pinctrl_groups_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev = s->निजी;
	स्थिर काष्ठा pinctrl_ops *ops = pctldev->desc->pctlops;
	अचिन्हित ngroups, selector = 0;

	mutex_lock(&pctldev->mutex);

	ngroups = ops->get_groups_count(pctldev);

	seq_माला_दो(s, "registered pin groups:\n");
	जबतक (selector < ngroups) अणु
		स्थिर अचिन्हित *pins = शून्य;
		अचिन्हित num_pins = 0;
		स्थिर अक्षर *gname = ops->get_group_name(pctldev, selector);
		स्थिर अक्षर *pname;
		पूर्णांक ret = 0;
		पूर्णांक i;

		अगर (ops->get_group_pins)
			ret = ops->get_group_pins(pctldev, selector,
						  &pins, &num_pins);
		अगर (ret)
			seq_म_लिखो(s, "%s [ERROR GETTING PINS]\n",
				   gname);
		अन्यथा अणु
			seq_म_लिखो(s, "group: %s\n", gname);
			क्रम (i = 0; i < num_pins; i++) अणु
				pname = pin_get_name(pctldev, pins[i]);
				अगर (WARN_ON(!pname)) अणु
					mutex_unlock(&pctldev->mutex);
					वापस -EINVAL;
				पूर्ण
				seq_म_लिखो(s, "pin %d (%s)\n", pins[i], pname);
			पूर्ण
			seq_माला_दो(s, "\n");
		पूर्ण
		selector++;
	पूर्ण

	mutex_unlock(&pctldev->mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pinctrl_groups);

अटल पूर्णांक pinctrl_gpioranges_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev = s->निजी;
	काष्ठा pinctrl_gpio_range *range;

	seq_माला_दो(s, "GPIO ranges handled:\n");

	mutex_lock(&pctldev->mutex);

	/* Loop over the ranges */
	list_क्रम_each_entry(range, &pctldev->gpio_ranges, node) अणु
		अगर (range->pins) अणु
			पूर्णांक a;
			seq_म_लिखो(s, "%u: %s GPIOS [%u - %u] PINS {",
				range->id, range->name,
				range->base, (range->base + range->npins - 1));
			क्रम (a = 0; a < range->npins - 1; a++)
				seq_म_लिखो(s, "%u, ", range->pins[a]);
			seq_म_लिखो(s, "%u}\n", range->pins[a]);
		पूर्ण
		अन्यथा
			seq_म_लिखो(s, "%u: %s GPIOS [%u - %u] PINS [%u - %u]\n",
				range->id, range->name,
				range->base, (range->base + range->npins - 1),
				range->pin_base,
				(range->pin_base + range->npins - 1));
	पूर्ण

	mutex_unlock(&pctldev->mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pinctrl_gpioranges);

अटल पूर्णांक pinctrl_devices_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_dev *pctldev;

	seq_माला_दो(s, "name [pinmux] [pinconf]\n");

	mutex_lock(&pinctrldev_list_mutex);

	list_क्रम_each_entry(pctldev, &pinctrldev_list, node) अणु
		seq_म_लिखो(s, "%s ", pctldev->desc->name);
		अगर (pctldev->desc->pmxops)
			seq_माला_दो(s, "yes ");
		अन्यथा
			seq_माला_दो(s, "no ");
		अगर (pctldev->desc->confops)
			seq_माला_दो(s, "yes");
		अन्यथा
			seq_माला_दो(s, "no");
		seq_माला_दो(s, "\n");
	पूर्ण

	mutex_unlock(&pinctrldev_list_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pinctrl_devices);

अटल अंतरभूत स्थिर अक्षर *map_type(क्रमागत pinctrl_map_type type)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"INVALID",
		"DUMMY_STATE",
		"MUX_GROUP",
		"CONFIGS_PIN",
		"CONFIGS_GROUP",
	पूर्ण;

	अगर (type >= ARRAY_SIZE(names))
		वापस "UNKNOWN";

	वापस names[type];
पूर्ण

अटल पूर्णांक pinctrl_maps_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl_maps *maps_node;
	पूर्णांक i;
	स्थिर काष्ठा pinctrl_map *map;

	seq_माला_दो(s, "Pinctrl maps:\n");

	mutex_lock(&pinctrl_maps_mutex);
	क्रम_each_maps(maps_node, i, map) अणु
		seq_म_लिखो(s, "device %s\nstate %s\ntype %s (%d)\n",
			   map->dev_name, map->name, map_type(map->type),
			   map->type);

		अगर (map->type != PIN_MAP_TYPE_DUMMY_STATE)
			seq_म_लिखो(s, "controlling device %s\n",
				   map->ctrl_dev_name);

		चयन (map->type) अणु
		हाल PIN_MAP_TYPE_MUX_GROUP:
			pinmux_show_map(s, map);
			अवरोध;
		हाल PIN_MAP_TYPE_CONFIGS_PIN:
		हाल PIN_MAP_TYPE_CONFIGS_GROUP:
			pinconf_show_map(s, map);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		seq_अ_दो(s, '\n');
	पूर्ण
	mutex_unlock(&pinctrl_maps_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pinctrl_maps);

अटल पूर्णांक pinctrl_show(काष्ठा seq_file *s, व्योम *what)
अणु
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *state;
	काष्ठा pinctrl_setting *setting;

	seq_माला_दो(s, "Requested pin control handlers their pinmux maps:\n");

	mutex_lock(&pinctrl_list_mutex);

	list_क्रम_each_entry(p, &pinctrl_list, node) अणु
		seq_म_लिखो(s, "device: %s current state: %s\n",
			   dev_name(p->dev),
			   p->state ? p->state->name : "none");

		list_क्रम_each_entry(state, &p->states, node) अणु
			seq_म_लिखो(s, "  state: %s\n", state->name);

			list_क्रम_each_entry(setting, &state->settings, node) अणु
				काष्ठा pinctrl_dev *pctldev = setting->pctldev;

				seq_म_लिखो(s, "    type: %s controller %s ",
					   map_type(setting->type),
					   pinctrl_dev_get_name(pctldev));

				चयन (setting->type) अणु
				हाल PIN_MAP_TYPE_MUX_GROUP:
					pinmux_show_setting(s, setting);
					अवरोध;
				हाल PIN_MAP_TYPE_CONFIGS_PIN:
				हाल PIN_MAP_TYPE_CONFIGS_GROUP:
					pinconf_show_setting(s, setting);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&pinctrl_list_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(pinctrl);

अटल काष्ठा dentry *debugfs_root;

अटल व्योम pinctrl_init_device_debugfs(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा dentry *device_root;
	स्थिर अक्षर *debugfs_name;

	अगर (pctldev->desc->name &&
			म_भेद(dev_name(pctldev->dev), pctldev->desc->name)) अणु
		debugfs_name = devm_kaप्र_लिखो(pctldev->dev, GFP_KERNEL,
				"%s-%s", dev_name(pctldev->dev),
				pctldev->desc->name);
		अगर (!debugfs_name) अणु
			pr_warn("failed to determine debugfs dir name for %s\n",
				dev_name(pctldev->dev));
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		debugfs_name = dev_name(pctldev->dev);
	पूर्ण

	device_root = debugfs_create_dir(debugfs_name, debugfs_root);
	pctldev->device_root = device_root;

	अगर (IS_ERR(device_root) || !device_root) अणु
		pr_warn("failed to create debugfs directory for %s\n",
			dev_name(pctldev->dev));
		वापस;
	पूर्ण
	debugfs_create_file("pins", 0444,
			    device_root, pctldev, &pinctrl_pins_fops);
	debugfs_create_file("pingroups", 0444,
			    device_root, pctldev, &pinctrl_groups_fops);
	debugfs_create_file("gpio-ranges", 0444,
			    device_root, pctldev, &pinctrl_gpioranges_fops);
	अगर (pctldev->desc->pmxops)
		pinmux_init_device_debugfs(device_root, pctldev);
	अगर (pctldev->desc->confops)
		pinconf_init_device_debugfs(device_root, pctldev);
पूर्ण

अटल व्योम pinctrl_हटाओ_device_debugfs(काष्ठा pinctrl_dev *pctldev)
अणु
	debugfs_हटाओ_recursive(pctldev->device_root);
पूर्ण

अटल व्योम pinctrl_init_debugfs(व्योम)
अणु
	debugfs_root = debugfs_create_dir("pinctrl", शून्य);
	अगर (IS_ERR(debugfs_root) || !debugfs_root) अणु
		pr_warn("failed to create debugfs directory\n");
		debugfs_root = शून्य;
		वापस;
	पूर्ण

	debugfs_create_file("pinctrl-devices", 0444,
			    debugfs_root, शून्य, &pinctrl_devices_fops);
	debugfs_create_file("pinctrl-maps", 0444,
			    debugfs_root, शून्य, &pinctrl_maps_fops);
	debugfs_create_file("pinctrl-handles", 0444,
			    debugfs_root, शून्य, &pinctrl_fops);
पूर्ण

#अन्यथा /* CONFIG_DEBUG_FS */

अटल व्योम pinctrl_init_device_debugfs(काष्ठा pinctrl_dev *pctldev)
अणु
पूर्ण

अटल व्योम pinctrl_init_debugfs(व्योम)
अणु
पूर्ण

अटल व्योम pinctrl_हटाओ_device_debugfs(काष्ठा pinctrl_dev *pctldev)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक pinctrl_check_ops(काष्ठा pinctrl_dev *pctldev)
अणु
	स्थिर काष्ठा pinctrl_ops *ops = pctldev->desc->pctlops;

	अगर (!ops ||
	    !ops->get_groups_count ||
	    !ops->get_group_name)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * pinctrl_init_controller() - init a pin controller device
 * @pctldesc: descriptor क्रम this pin controller
 * @dev: parent device क्रम this pin controller
 * @driver_data: निजी pin controller data क्रम this pin controller
 */
अटल काष्ठा pinctrl_dev *
pinctrl_init_controller(काष्ठा pinctrl_desc *pctldesc, काष्ठा device *dev,
			व्योम *driver_data)
अणु
	काष्ठा pinctrl_dev *pctldev;
	पूर्णांक ret;

	अगर (!pctldesc)
		वापस ERR_PTR(-EINVAL);
	अगर (!pctldesc->name)
		वापस ERR_PTR(-EINVAL);

	pctldev = kzalloc(माप(*pctldev), GFP_KERNEL);
	अगर (!pctldev)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize pin control device काष्ठा */
	pctldev->owner = pctldesc->owner;
	pctldev->desc = pctldesc;
	pctldev->driver_data = driver_data;
	INIT_RADIX_TREE(&pctldev->pin_desc_tree, GFP_KERNEL);
#अगर_घोषित CONFIG_GENERIC_PINCTRL_GROUPS
	INIT_RADIX_TREE(&pctldev->pin_group_tree, GFP_KERNEL);
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_PINMUX_FUNCTIONS
	INIT_RADIX_TREE(&pctldev->pin_function_tree, GFP_KERNEL);
#पूर्ण_अगर
	INIT_LIST_HEAD(&pctldev->gpio_ranges);
	INIT_LIST_HEAD(&pctldev->node);
	pctldev->dev = dev;
	mutex_init(&pctldev->mutex);

	/* check core ops क्रम sanity */
	ret = pinctrl_check_ops(pctldev);
	अगर (ret) अणु
		dev_err(dev, "pinctrl ops lacks necessary functions\n");
		जाओ out_err;
	पूर्ण

	/* If we're implementing pinmuxing, check the ops क्रम sanity */
	अगर (pctldesc->pmxops) अणु
		ret = pinmux_check_ops(pctldev);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	/* If we're implementing pinconfig, check the ops क्रम sanity */
	अगर (pctldesc->confops) अणु
		ret = pinconf_check_ops(pctldev);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	/* Register all the pins */
	dev_dbg(dev, "try to register %d pins ...\n",  pctldesc->npins);
	ret = pinctrl_रेजिस्टर_pins(pctldev, pctldesc->pins, pctldesc->npins);
	अगर (ret) अणु
		dev_err(dev, "error during pin registration\n");
		pinctrl_मुक्त_pindescs(pctldev, pctldesc->pins,
				      pctldesc->npins);
		जाओ out_err;
	पूर्ण

	वापस pctldev;

out_err:
	mutex_destroy(&pctldev->mutex);
	kमुक्त(pctldev);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक pinctrl_claim_hogs(काष्ठा pinctrl_dev *pctldev)
अणु
	pctldev->p = create_pinctrl(pctldev->dev, pctldev);
	अगर (PTR_ERR(pctldev->p) == -ENODEV) अणु
		dev_dbg(pctldev->dev, "no hogs found\n");

		वापस 0;
	पूर्ण

	अगर (IS_ERR(pctldev->p)) अणु
		dev_err(pctldev->dev, "error claiming hogs: %li\n",
			PTR_ERR(pctldev->p));

		वापस PTR_ERR(pctldev->p);
	पूर्ण

	pctldev->hog_शेष =
		pinctrl_lookup_state(pctldev->p, PINCTRL_STATE_DEFAULT);
	अगर (IS_ERR(pctldev->hog_शेष)) अणु
		dev_dbg(pctldev->dev,
			"failed to lookup the default state\n");
	पूर्ण अन्यथा अणु
		अगर (pinctrl_select_state(pctldev->p,
					 pctldev->hog_शेष))
			dev_err(pctldev->dev,
				"failed to select default state\n");
	पूर्ण

	pctldev->hog_sleep =
		pinctrl_lookup_state(pctldev->p,
				     PINCTRL_STATE_SLEEP);
	अगर (IS_ERR(pctldev->hog_sleep))
		dev_dbg(pctldev->dev,
			"failed to lookup the sleep state\n");

	वापस 0;
पूर्ण

पूर्णांक pinctrl_enable(काष्ठा pinctrl_dev *pctldev)
अणु
	पूर्णांक error;

	error = pinctrl_claim_hogs(pctldev);
	अगर (error) अणु
		dev_err(pctldev->dev, "could not claim hogs: %i\n",
			error);
		mutex_destroy(&pctldev->mutex);
		kमुक्त(pctldev);

		वापस error;
	पूर्ण

	mutex_lock(&pinctrldev_list_mutex);
	list_add_tail(&pctldev->node, &pinctrldev_list);
	mutex_unlock(&pinctrldev_list_mutex);

	pinctrl_init_device_debugfs(pctldev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_enable);

/**
 * pinctrl_रेजिस्टर() - रेजिस्टर a pin controller device
 * @pctldesc: descriptor क्रम this pin controller
 * @dev: parent device क्रम this pin controller
 * @driver_data: निजी pin controller data क्रम this pin controller
 *
 * Note that pinctrl_रेजिस्टर() is known to have problems as the pin
 * controller driver functions are called beक्रमe the driver has a
 * काष्ठा pinctrl_dev handle. To aव्योम issues later on, please use the
 * new pinctrl_रेजिस्टर_and_init() below instead.
 */
काष्ठा pinctrl_dev *pinctrl_रेजिस्टर(काष्ठा pinctrl_desc *pctldesc,
				    काष्ठा device *dev, व्योम *driver_data)
अणु
	काष्ठा pinctrl_dev *pctldev;
	पूर्णांक error;

	pctldev = pinctrl_init_controller(pctldesc, dev, driver_data);
	अगर (IS_ERR(pctldev))
		वापस pctldev;

	error = pinctrl_enable(pctldev);
	अगर (error)
		वापस ERR_PTR(error);

	वापस pctldev;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_रेजिस्टर);

/**
 * pinctrl_रेजिस्टर_and_init() - रेजिस्टर and init pin controller device
 * @pctldesc: descriptor क्रम this pin controller
 * @dev: parent device क्रम this pin controller
 * @driver_data: निजी pin controller data क्रम this pin controller
 * @pctldev: pin controller device
 *
 * Note that pinctrl_enable() still needs to be manually called after
 * this once the driver is पढ़ोy.
 */
पूर्णांक pinctrl_रेजिस्टर_and_init(काष्ठा pinctrl_desc *pctldesc,
			      काष्ठा device *dev, व्योम *driver_data,
			      काष्ठा pinctrl_dev **pctldev)
अणु
	काष्ठा pinctrl_dev *p;

	p = pinctrl_init_controller(pctldesc, dev, driver_data);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	/*
	 * We have pinctrl_start() call functions in the pin controller
	 * driver with create_pinctrl() क्रम at least dt_node_to_map(). So
	 * let's make sure pctldev is properly initialized क्रम the
	 * pin controller driver beक्रमe we करो anything.
	 */
	*pctldev = p;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_रेजिस्टर_and_init);

/**
 * pinctrl_unरेजिस्टर() - unरेजिस्टर pinmux
 * @pctldev: pin controller to unरेजिस्टर
 *
 * Called by pinmux drivers to unरेजिस्टर a pinmux.
 */
व्योम pinctrl_unरेजिस्टर(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pinctrl_gpio_range *range, *n;

	अगर (!pctldev)
		वापस;

	mutex_lock(&pctldev->mutex);
	pinctrl_हटाओ_device_debugfs(pctldev);
	mutex_unlock(&pctldev->mutex);

	अगर (!IS_ERR_OR_शून्य(pctldev->p))
		pinctrl_put(pctldev->p);

	mutex_lock(&pinctrldev_list_mutex);
	mutex_lock(&pctldev->mutex);
	/* TODO: check that no pinmuxes are still active? */
	list_del(&pctldev->node);
	pinmux_generic_मुक्त_functions(pctldev);
	pinctrl_generic_मुक्त_groups(pctldev);
	/* Destroy descriptor tree */
	pinctrl_मुक्त_pindescs(pctldev, pctldev->desc->pins,
			      pctldev->desc->npins);
	/* हटाओ gpio ranges map */
	list_क्रम_each_entry_safe(range, n, &pctldev->gpio_ranges, node)
		list_del(&range->node);

	mutex_unlock(&pctldev->mutex);
	mutex_destroy(&pctldev->mutex);
	kमुक्त(pctldev);
	mutex_unlock(&pinctrldev_list_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pinctrl_unरेजिस्टर);

अटल व्योम devm_pinctrl_dev_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा pinctrl_dev *pctldev = *(काष्ठा pinctrl_dev **)res;

	pinctrl_unरेजिस्टर(pctldev);
पूर्ण

अटल पूर्णांक devm_pinctrl_dev_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा pctldev **r = res;

	अगर (WARN_ON(!r || !*r))
		वापस 0;

	वापस *r == data;
पूर्ण

/**
 * devm_pinctrl_रेजिस्टर() - Resource managed version of pinctrl_रेजिस्टर().
 * @dev: parent device क्रम this pin controller
 * @pctldesc: descriptor क्रम this pin controller
 * @driver_data: निजी pin controller data क्रम this pin controller
 *
 * Returns an error poपूर्णांकer अगर pincontrol रेजिस्टर failed. Otherwise
 * it वापसs valid pinctrl handle.
 *
 * The pinctrl device will be स्वतःmatically released when the device is unbound.
 */
काष्ठा pinctrl_dev *devm_pinctrl_रेजिस्टर(काष्ठा device *dev,
					  काष्ठा pinctrl_desc *pctldesc,
					  व्योम *driver_data)
अणु
	काष्ठा pinctrl_dev **ptr, *pctldev;

	ptr = devres_alloc(devm_pinctrl_dev_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	pctldev = pinctrl_रेजिस्टर(pctldesc, dev, driver_data);
	अगर (IS_ERR(pctldev)) अणु
		devres_मुक्त(ptr);
		वापस pctldev;
	पूर्ण

	*ptr = pctldev;
	devres_add(dev, ptr);

	वापस pctldev;
पूर्ण
EXPORT_SYMBOL_GPL(devm_pinctrl_रेजिस्टर);

/**
 * devm_pinctrl_रेजिस्टर_and_init() - Resource managed pinctrl रेजिस्टर and init
 * @dev: parent device क्रम this pin controller
 * @pctldesc: descriptor क्रम this pin controller
 * @driver_data: निजी pin controller data क्रम this pin controller
 * @pctldev: pin controller device
 *
 * Returns zero on success or an error number on failure.
 *
 * The pinctrl device will be स्वतःmatically released when the device is unbound.
 */
पूर्णांक devm_pinctrl_रेजिस्टर_and_init(काष्ठा device *dev,
				   काष्ठा pinctrl_desc *pctldesc,
				   व्योम *driver_data,
				   काष्ठा pinctrl_dev **pctldev)
अणु
	काष्ठा pinctrl_dev **ptr;
	पूर्णांक error;

	ptr = devres_alloc(devm_pinctrl_dev_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	error = pinctrl_रेजिस्टर_and_init(pctldesc, dev, driver_data, pctldev);
	अगर (error) अणु
		devres_मुक्त(ptr);
		वापस error;
	पूर्ण

	*ptr = *pctldev;
	devres_add(dev, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_pinctrl_रेजिस्टर_and_init);

/**
 * devm_pinctrl_unरेजिस्टर() - Resource managed version of pinctrl_unरेजिस्टर().
 * @dev: device क्रम which which resource was allocated
 * @pctldev: the pinctrl device to unरेजिस्टर.
 */
व्योम devm_pinctrl_unरेजिस्टर(काष्ठा device *dev, काष्ठा pinctrl_dev *pctldev)
अणु
	WARN_ON(devres_release(dev, devm_pinctrl_dev_release,
			       devm_pinctrl_dev_match, pctldev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_pinctrl_unरेजिस्टर);

अटल पूर्णांक __init pinctrl_init(व्योम)
अणु
	pr_info("initialized pinctrl subsystem\n");
	pinctrl_init_debugfs();
	वापस 0;
पूर्ण

/* init early since many drivers really need to initialized pinmux early */
core_initcall(pinctrl_init);
