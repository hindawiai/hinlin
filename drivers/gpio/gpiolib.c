<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/fs.h>
#समावेश <linux/compat.h>
#समावेश <linux/file.h>
#समावेश <uapi/linux/gpपन.स>

#समावेश "gpiolib.h"
#समावेश "gpiolib-of.h"
#समावेश "gpiolib-acpi.h"
#समावेश "gpiolib-cdev.h"
#समावेश "gpiolib-sysfs.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/gpपन.स>

/* Implementation infraकाष्ठाure क्रम GPIO पूर्णांकerfaces.
 *
 * The GPIO programming पूर्णांकerface allows क्रम inlining speed-critical
 * get/set operations क्रम common हालs, so that access to SOC-पूर्णांकegrated
 * GPIOs can someबार cost only an inकाष्ठाion or two per bit.
 */


/* When debugging, extend minimal trust to callers and platक्रमm code.
 * Also emit diagnostic messages that may help initial bringup, when
 * board setup or driver bugs are most common.
 *
 * Otherwise, minimize overhead in what may be bitbanging codepaths.
 */
#अगर_घोषित	DEBUG
#घोषणा	extra_checks	1
#अन्यथा
#घोषणा	extra_checks	0
#पूर्ण_अगर

/* Device and अक्षर device-related inक्रमmation */
अटल DEFINE_IDA(gpio_ida);
अटल dev_t gpio_devt;
#घोषणा GPIO_DEV_MAX 256 /* 256 GPIO chip devices supported */
अटल पूर्णांक gpio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv);
अटल काष्ठा bus_type gpio_bus_type = अणु
	.name = "gpio",
	.match = gpio_bus_match,
पूर्ण;

/*
 * Number of GPIOs to use क्रम the fast path in set array
 */
#घोषणा FASTPATH_NGPIO CONFIG_GPIOLIB_FASTPATH_LIMIT

/* gpio_lock prevents conflicts during gpio_desc[] table updates.
 * While any GPIO is requested, its gpio_chip is not removable;
 * each GPIO's "requested" flag serves as a lock and refcount.
 */
DEFINE_SPINLOCK(gpio_lock);

अटल DEFINE_MUTEX(gpio_lookup_lock);
अटल LIST_HEAD(gpio_lookup_list);
LIST_HEAD(gpio_devices);

अटल DEFINE_MUTEX(gpio_machine_hogs_mutex);
अटल LIST_HEAD(gpio_machine_hogs);

अटल व्योम gpiochip_मुक्त_hogs(काष्ठा gpio_chip *gc);
अटल पूर्णांक gpiochip_add_irqchip(काष्ठा gpio_chip *gc,
				काष्ठा lock_class_key *lock_key,
				काष्ठा lock_class_key *request_key);
अटल व्योम gpiochip_irqchip_हटाओ(काष्ठा gpio_chip *gc);
अटल पूर्णांक gpiochip_irqchip_init_hw(काष्ठा gpio_chip *gc);
अटल पूर्णांक gpiochip_irqchip_init_valid_mask(काष्ठा gpio_chip *gc);
अटल व्योम gpiochip_irqchip_मुक्त_valid_mask(काष्ठा gpio_chip *gc);

अटल bool gpiolib_initialized;

अटल अंतरभूत व्योम desc_set_label(काष्ठा gpio_desc *d, स्थिर अक्षर *label)
अणु
	d->label = label;
पूर्ण

/**
 * gpio_to_desc - Convert a GPIO number to its descriptor
 * @gpio: global GPIO number
 *
 * Returns:
 * The GPIO descriptor associated with the given GPIO, or %शून्य अगर no GPIO
 * with the given number exists in the प्रणाली.
 */
काष्ठा gpio_desc *gpio_to_desc(अचिन्हित gpio)
अणु
	काष्ठा gpio_device *gdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);

	list_क्रम_each_entry(gdev, &gpio_devices, list) अणु
		अगर (gdev->base <= gpio &&
		    gdev->base + gdev->ngpio > gpio) अणु
			spin_unlock_irqrestore(&gpio_lock, flags);
			वापस &gdev->descs[gpio - gdev->base];
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&gpio_lock, flags);

	अगर (!gpio_is_valid(gpio))
		pr_warn("invalid GPIO %d\n", gpio);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(gpio_to_desc);

/**
 * gpiochip_get_desc - get the GPIO descriptor corresponding to the given
 *                     hardware number क्रम this chip
 * @gc: GPIO chip
 * @hwnum: hardware number of the GPIO क्रम this chip
 *
 * Returns:
 * A poपूर्णांकer to the GPIO descriptor or ``ERR_PTR(-EINVAL)`` अगर no GPIO exists
 * in the given chip क्रम the specअगरied hardware number.
 */
काष्ठा gpio_desc *gpiochip_get_desc(काष्ठा gpio_chip *gc,
				    अचिन्हित पूर्णांक hwnum)
अणु
	काष्ठा gpio_device *gdev = gc->gpiodev;

	अगर (hwnum >= gdev->ngpio)
		वापस ERR_PTR(-EINVAL);

	वापस &gdev->descs[hwnum];
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_get_desc);

/**
 * desc_to_gpio - convert a GPIO descriptor to the पूर्णांकeger namespace
 * @desc: GPIO descriptor
 *
 * This should disappear in the future but is needed since we still
 * use GPIO numbers क्रम error messages and sysfs nodes.
 *
 * Returns:
 * The global GPIO number क्रम the GPIO specअगरied by its descriptor.
 */
पूर्णांक desc_to_gpio(स्थिर काष्ठा gpio_desc *desc)
अणु
	वापस desc->gdev->base + (desc - &desc->gdev->descs[0]);
पूर्ण
EXPORT_SYMBOL_GPL(desc_to_gpio);


/**
 * gpiod_to_chip - Return the GPIO chip to which a GPIO descriptor beदीर्घs
 * @desc:	descriptor to वापस the chip of
 */
काष्ठा gpio_chip *gpiod_to_chip(स्थिर काष्ठा gpio_desc *desc)
अणु
	अगर (!desc || !desc->gdev)
		वापस शून्य;
	वापस desc->gdev->chip;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_to_chip);

/* dynamic allocation of GPIOs, e.g. on a hotplugged device */
अटल पूर्णांक gpiochip_find_base(पूर्णांक ngpio)
अणु
	काष्ठा gpio_device *gdev;
	पूर्णांक base = ARCH_NR_GPIOS - ngpio;

	list_क्रम_each_entry_reverse(gdev, &gpio_devices, list) अणु
		/* found a मुक्त space? */
		अगर (gdev->base + gdev->ngpio <= base)
			अवरोध;
		अन्यथा
			/* nope, check the space right beक्रमe the chip */
			base = gdev->base - ngpio;
	पूर्ण

	अगर (gpio_is_valid(base)) अणु
		pr_debug("%s: found new base at %d\n", __func__, base);
		वापस base;
	पूर्ण अन्यथा अणु
		pr_err("%s: cannot find free range\n", __func__);
		वापस -ENOSPC;
	पूर्ण
पूर्ण

/**
 * gpiod_get_direction - वापस the current direction of a GPIO
 * @desc:	GPIO to get the direction of
 *
 * Returns 0 क्रम output, 1 क्रम input, or an error code in हाल of error.
 *
 * This function may sleep अगर gpiod_cansleep() is true.
 */
पूर्णांक gpiod_get_direction(काष्ठा gpio_desc *desc)
अणु
	काष्ठा gpio_chip *gc;
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret;

	gc = gpiod_to_chip(desc);
	offset = gpio_chip_hwgpio(desc);

	/*
	 * Open drain emulation using input mode may incorrectly report
	 * input here, fix that up.
	 */
	अगर (test_bit(FLAG_OPEN_DRAIN, &desc->flags) &&
	    test_bit(FLAG_IS_OUT, &desc->flags))
		वापस 0;

	अगर (!gc->get_direction)
		वापस -ENOTSUPP;

	ret = gc->get_direction(gc, offset);
	अगर (ret < 0)
		वापस ret;

	/* GPIOF_सूची_IN or other positive, otherwise GPIOF_सूची_OUT */
	अगर (ret > 0)
		ret = 1;

	assign_bit(FLAG_IS_OUT, &desc->flags, !ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_direction);

/*
 * Add a new chip to the global chips list, keeping the list of chips sorted
 * by range(means [base, base + ngpio - 1]) order.
 *
 * Return -EBUSY अगर the new chip overlaps with some other chip's पूर्णांकeger
 * space.
 */
अटल पूर्णांक gpiodev_add_to_list(काष्ठा gpio_device *gdev)
अणु
	काष्ठा gpio_device *prev, *next;

	अगर (list_empty(&gpio_devices)) अणु
		/* initial entry in list */
		list_add_tail(&gdev->list, &gpio_devices);
		वापस 0;
	पूर्ण

	next = list_entry(gpio_devices.next, काष्ठा gpio_device, list);
	अगर (gdev->base + gdev->ngpio <= next->base) अणु
		/* add beक्रमe first entry */
		list_add(&gdev->list, &gpio_devices);
		वापस 0;
	पूर्ण

	prev = list_entry(gpio_devices.prev, काष्ठा gpio_device, list);
	अगर (prev->base + prev->ngpio <= gdev->base) अणु
		/* add behind last entry */
		list_add_tail(&gdev->list, &gpio_devices);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry_safe(prev, next, &gpio_devices, list) अणु
		/* at the end of the list */
		अगर (&next->list == &gpio_devices)
			अवरोध;

		/* add between prev and next */
		अगर (prev->base + prev->ngpio <= gdev->base
				&& gdev->base + gdev->ngpio <= next->base) अणु
			list_add(&gdev->list, &prev->list);
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(&gdev->dev, "GPIO integer space overlap, cannot add chip\n");
	वापस -EBUSY;
पूर्ण

/*
 * Convert a GPIO name to its descriptor
 * Note that there is no guarantee that GPIO names are globally unique!
 * Hence this function will वापस, अगर it exists, a reference to the first GPIO
 * line found that matches the given name.
 */
अटल काष्ठा gpio_desc *gpio_name_to_desc(स्थिर अक्षर * स्थिर name)
अणु
	काष्ठा gpio_device *gdev;
	अचिन्हित दीर्घ flags;

	अगर (!name)
		वापस शून्य;

	spin_lock_irqsave(&gpio_lock, flags);

	list_क्रम_each_entry(gdev, &gpio_devices, list) अणु
		पूर्णांक i;

		क्रम (i = 0; i != gdev->ngpio; ++i) अणु
			काष्ठा gpio_desc *desc = &gdev->descs[i];

			अगर (!desc->name)
				जारी;

			अगर (!म_भेद(desc->name, name)) अणु
				spin_unlock_irqrestore(&gpio_lock, flags);
				वापस desc;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&gpio_lock, flags);

	वापस शून्य;
पूर्ण

/*
 * Take the names from gc->names and assign them to their GPIO descriptors.
 * Warn अगर a name is alपढ़ोy used क्रम a GPIO line on a dअगरferent GPIO chip.
 *
 * Note that:
 *   1. Non-unique names are still accepted,
 *   2. Name collisions within the same GPIO chip are not reported.
 */
अटल पूर्णांक gpiochip_set_desc_names(काष्ठा gpio_chip *gc)
अणु
	काष्ठा gpio_device *gdev = gc->gpiodev;
	पूर्णांक i;

	/* First check all names अगर they are unique */
	क्रम (i = 0; i != gc->ngpio; ++i) अणु
		काष्ठा gpio_desc *gpio;

		gpio = gpio_name_to_desc(gc->names[i]);
		अगर (gpio)
			dev_warn(&gdev->dev,
				 "Detected name collision for GPIO name '%s'\n",
				 gc->names[i]);
	पूर्ण

	/* Then add all names to the GPIO descriptors */
	क्रम (i = 0; i != gc->ngpio; ++i)
		gdev->descs[i].name = gc->names[i];

	वापस 0;
पूर्ण

/*
 * devprop_gpiochip_set_names - Set GPIO line names using device properties
 * @chip: GPIO chip whose lines should be named, अगर possible
 *
 * Looks क्रम device property "gpio-line-names" and अगर it exists assigns
 * GPIO line names क्रम the chip. The memory allocated क्रम the asचिन्हित
 * names beदीर्घ to the underlying firmware node and should not be released
 * by the caller.
 */
अटल पूर्णांक devprop_gpiochip_set_names(काष्ठा gpio_chip *chip)
अणु
	काष्ठा gpio_device *gdev = chip->gpiodev;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(&gdev->dev);
	स्थिर अक्षर **names;
	पूर्णांक ret, i;
	पूर्णांक count;

	count = fwnode_property_string_array_count(fwnode, "gpio-line-names");
	अगर (count < 0)
		वापस 0;

	अगर (count > gdev->ngpio) अणु
		dev_warn(&gdev->dev, "gpio-line-names is length %d but should be at most length %d",
			 count, gdev->ngpio);
		count = gdev->ngpio;
	पूर्ण

	names = kसुस्मृति(count, माप(*names), GFP_KERNEL);
	अगर (!names)
		वापस -ENOMEM;

	ret = fwnode_property_पढ़ो_string_array(fwnode, "gpio-line-names",
						names, count);
	अगर (ret < 0) अणु
		dev_warn(&gdev->dev, "failed to read GPIO line names\n");
		kमुक्त(names);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < count; i++)
		gdev->descs[i].name = names[i];

	kमुक्त(names);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ *gpiochip_allocate_mask(काष्ठा gpio_chip *gc)
अणु
	अचिन्हित दीर्घ *p;

	p = biपंचांगap_alloc(gc->ngpio, GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	/* Assume by शेष all GPIOs are valid */
	biपंचांगap_fill(p, gc->ngpio);

	वापस p;
पूर्ण

अटल पूर्णांक gpiochip_alloc_valid_mask(काष्ठा gpio_chip *gc)
अणु
	अगर (!(of_gpio_need_valid_mask(gc) || gc->init_valid_mask))
		वापस 0;

	gc->valid_mask = gpiochip_allocate_mask(gc);
	अगर (!gc->valid_mask)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक gpiochip_init_valid_mask(काष्ठा gpio_chip *gc)
अणु
	अगर (gc->init_valid_mask)
		वापस gc->init_valid_mask(gc,
					   gc->valid_mask,
					   gc->ngpio);

	वापस 0;
पूर्ण

अटल व्योम gpiochip_मुक्त_valid_mask(काष्ठा gpio_chip *gc)
अणु
	biपंचांगap_मुक्त(gc->valid_mask);
	gc->valid_mask = शून्य;
पूर्ण

अटल पूर्णांक gpiochip_add_pin_ranges(काष्ठा gpio_chip *gc)
अणु
	अगर (gc->add_pin_ranges)
		वापस gc->add_pin_ranges(gc);

	वापस 0;
पूर्ण

bool gpiochip_line_is_valid(स्थिर काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset)
अणु
	/* No mask means all valid */
	अगर (likely(!gc->valid_mask))
		वापस true;
	वापस test_bit(offset, gc->valid_mask);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_line_is_valid);

अटल व्योम gpiodevice_release(काष्ठा device *dev)
अणु
	काष्ठा gpio_device *gdev = container_of(dev, काष्ठा gpio_device, dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);
	list_del(&gdev->list);
	spin_unlock_irqrestore(&gpio_lock, flags);

	ida_मुक्त(&gpio_ida, gdev->id);
	kमुक्त_स्थिर(gdev->label);
	kमुक्त(gdev->descs);
	kमुक्त(gdev);
पूर्ण

#अगर_घोषित CONFIG_GPIO_CDEV
#घोषणा gcdev_रेजिस्टर(gdev, devt)	gpiolib_cdev_रेजिस्टर((gdev), (devt))
#घोषणा gcdev_unरेजिस्टर(gdev)		gpiolib_cdev_unरेजिस्टर((gdev))
#अन्यथा
/*
 * gpiolib_cdev_रेजिस्टर() indirectly calls device_add(), which is still
 * required even when cdev is not selected.
 */
#घोषणा gcdev_रेजिस्टर(gdev, devt)	device_add(&(gdev)->dev)
#घोषणा gcdev_unरेजिस्टर(gdev)		device_del(&(gdev)->dev)
#पूर्ण_अगर

अटल पूर्णांक gpiochip_setup_dev(काष्ठा gpio_device *gdev)
अणु
	पूर्णांक ret;

	ret = gcdev_रेजिस्टर(gdev, gpio_devt);
	अगर (ret)
		वापस ret;

	ret = gpiochip_sysfs_रेजिस्टर(gdev);
	अगर (ret)
		जाओ err_हटाओ_device;

	/* From this poपूर्णांक, the .release() function cleans up gpio_device */
	gdev->dev.release = gpiodevice_release;
	dev_dbg(&gdev->dev, "registered GPIOs %d to %d on %s\n", gdev->base,
		gdev->base + gdev->ngpio - 1, gdev->chip->label ? : "generic");

	वापस 0;

err_हटाओ_device:
	gcdev_unरेजिस्टर(gdev);
	वापस ret;
पूर्ण

अटल व्योम gpiochip_machine_hog(काष्ठा gpio_chip *gc, काष्ठा gpiod_hog *hog)
अणु
	काष्ठा gpio_desc *desc;
	पूर्णांक rv;

	desc = gpiochip_get_desc(gc, hog->chip_hwnum);
	अगर (IS_ERR(desc)) अणु
		chip_err(gc, "%s: unable to get GPIO desc: %ld\n", __func__,
			 PTR_ERR(desc));
		वापस;
	पूर्ण

	अगर (test_bit(FLAG_IS_HOGGED, &desc->flags))
		वापस;

	rv = gpiod_hog(desc, hog->line_name, hog->lflags, hog->dflags);
	अगर (rv)
		gpiod_err(desc, "%s: unable to hog GPIO line (%s:%u): %d\n",
			  __func__, gc->label, hog->chip_hwnum, rv);
पूर्ण

अटल व्योम machine_gpiochip_add(काष्ठा gpio_chip *gc)
अणु
	काष्ठा gpiod_hog *hog;

	mutex_lock(&gpio_machine_hogs_mutex);

	list_क्रम_each_entry(hog, &gpio_machine_hogs, list) अणु
		अगर (!म_भेद(gc->label, hog->chip_label))
			gpiochip_machine_hog(gc, hog);
	पूर्ण

	mutex_unlock(&gpio_machine_hogs_mutex);
पूर्ण

अटल व्योम gpiochip_setup_devs(व्योम)
अणु
	काष्ठा gpio_device *gdev;
	पूर्णांक ret;

	list_क्रम_each_entry(gdev, &gpio_devices, list) अणु
		ret = gpiochip_setup_dev(gdev);
		अगर (ret)
			dev_err(&gdev->dev,
				"Failed to initialize gpio device (%d)\n", ret);
	पूर्ण
पूर्ण

पूर्णांक gpiochip_add_data_with_key(काष्ठा gpio_chip *gc, व्योम *data,
			       काष्ठा lock_class_key *lock_key,
			       काष्ठा lock_class_key *request_key)
अणु
	काष्ठा fwnode_handle *fwnode = gc->parent ? dev_fwnode(gc->parent) : शून्य;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		ret = 0;
	अचिन्हित	i;
	पूर्णांक		base = gc->base;
	काष्ठा gpio_device *gdev;

	/*
	 * First: allocate and populate the पूर्णांकernal stat container, and
	 * set up the काष्ठा device.
	 */
	gdev = kzalloc(माप(*gdev), GFP_KERNEL);
	अगर (!gdev)
		वापस -ENOMEM;
	gdev->dev.bus = &gpio_bus_type;
	gdev->dev.parent = gc->parent;
	gdev->chip = gc;
	gc->gpiodev = gdev;

	of_gpio_dev_init(gc, gdev);
	acpi_gpio_dev_init(gc, gdev);

	/*
	 * Assign fwnode depending on the result of the previous calls,
	 * अगर none of them succeed, assign it to the parent's one.
	 */
	gdev->dev.fwnode = dev_fwnode(&gdev->dev) ?: fwnode;

	gdev->id = ida_alloc(&gpio_ida, GFP_KERNEL);
	अगर (gdev->id < 0) अणु
		ret = gdev->id;
		जाओ err_मुक्त_gdev;
	पूर्ण

	ret = dev_set_name(&gdev->dev, GPIOCHIP_NAME "%d", gdev->id);
	अगर (ret)
		जाओ err_मुक्त_ida;

	device_initialize(&gdev->dev);
	अगर (gc->parent && gc->parent->driver)
		gdev->owner = gc->parent->driver->owner;
	अन्यथा अगर (gc->owner)
		/* TODO: हटाओ chip->owner */
		gdev->owner = gc->owner;
	अन्यथा
		gdev->owner = THIS_MODULE;

	gdev->descs = kसुस्मृति(gc->ngpio, माप(gdev->descs[0]), GFP_KERNEL);
	अगर (!gdev->descs) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_dev_name;
	पूर्ण

	अगर (gc->ngpio == 0) अणु
		chip_err(gc, "tried to insert a GPIO chip with zero lines\n");
		ret = -EINVAL;
		जाओ err_मुक्त_descs;
	पूर्ण

	अगर (gc->ngpio > FASTPATH_NGPIO)
		chip_warn(gc, "line cnt %u is greater than fast path cnt %u\n",
			  gc->ngpio, FASTPATH_NGPIO);

	gdev->label = kstrdup_स्थिर(gc->label ?: "unknown", GFP_KERNEL);
	अगर (!gdev->label) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_descs;
	पूर्ण

	gdev->ngpio = gc->ngpio;
	gdev->data = data;

	spin_lock_irqsave(&gpio_lock, flags);

	/*
	 * TODO: this allocates a Linux GPIO number base in the global
	 * GPIO numberspace क्रम this chip. In the दीर्घ run we want to
	 * get *rid* of this numberspace and use only descriptors, but
	 * it may be a pipe dream. It will not happen beक्रमe we get rid
	 * of the sysfs पूर्णांकerface anyways.
	 */
	अगर (base < 0) अणु
		base = gpiochip_find_base(gc->ngpio);
		अगर (base < 0) अणु
			ret = base;
			spin_unlock_irqrestore(&gpio_lock, flags);
			जाओ err_मुक्त_label;
		पूर्ण
		/*
		 * TODO: it should not be necessary to reflect the asचिन्हित
		 * base outside of the GPIO subप्रणाली. Go over drivers and
		 * see अगर anyone makes use of this, अन्यथा drop this and assign
		 * a poison instead.
		 */
		gc->base = base;
	पूर्ण
	gdev->base = base;

	ret = gpiodev_add_to_list(gdev);
	अगर (ret) अणु
		spin_unlock_irqrestore(&gpio_lock, flags);
		जाओ err_मुक्त_label;
	पूर्ण

	क्रम (i = 0; i < gc->ngpio; i++)
		gdev->descs[i].gdev = gdev;

	spin_unlock_irqrestore(&gpio_lock, flags);

	BLOCKING_INIT_NOTIFIER_HEAD(&gdev->notअगरier);

#अगर_घोषित CONFIG_PINCTRL
	INIT_LIST_HEAD(&gdev->pin_ranges);
#पूर्ण_अगर

	अगर (gc->names)
		ret = gpiochip_set_desc_names(gc);
	अन्यथा
		ret = devprop_gpiochip_set_names(gc);
	अगर (ret)
		जाओ err_हटाओ_from_list;

	ret = gpiochip_alloc_valid_mask(gc);
	अगर (ret)
		जाओ err_हटाओ_from_list;

	ret = of_gpiochip_add(gc);
	अगर (ret)
		जाओ err_मुक्त_gpiochip_mask;

	ret = gpiochip_init_valid_mask(gc);
	अगर (ret)
		जाओ err_हटाओ_of_chip;

	क्रम (i = 0; i < gc->ngpio; i++) अणु
		काष्ठा gpio_desc *desc = &gdev->descs[i];

		अगर (gc->get_direction && gpiochip_line_is_valid(gc, i)) अणु
			assign_bit(FLAG_IS_OUT,
				   &desc->flags, !gc->get_direction(gc, i));
		पूर्ण अन्यथा अणु
			assign_bit(FLAG_IS_OUT,
				   &desc->flags, !gc->direction_input);
		पूर्ण
	पूर्ण

	ret = gpiochip_add_pin_ranges(gc);
	अगर (ret)
		जाओ err_हटाओ_of_chip;

	acpi_gpiochip_add(gc);

	machine_gpiochip_add(gc);

	ret = gpiochip_irqchip_init_valid_mask(gc);
	अगर (ret)
		जाओ err_हटाओ_acpi_chip;

	ret = gpiochip_irqchip_init_hw(gc);
	अगर (ret)
		जाओ err_हटाओ_acpi_chip;

	ret = gpiochip_add_irqchip(gc, lock_key, request_key);
	अगर (ret)
		जाओ err_हटाओ_irqchip_mask;

	/*
	 * By first adding the अक्षरdev, and then adding the device,
	 * we get a device node entry in sysfs under
	 * /sys/bus/gpio/devices/gpiochipN/dev that can be used क्रम
	 * coldplug of device nodes and other udev business.
	 * We can करो this only अगर gpiolib has been initialized.
	 * Otherwise, defer until later.
	 */
	अगर (gpiolib_initialized) अणु
		ret = gpiochip_setup_dev(gdev);
		अगर (ret)
			जाओ err_हटाओ_irqchip;
	पूर्ण
	वापस 0;

err_हटाओ_irqchip:
	gpiochip_irqchip_हटाओ(gc);
err_हटाओ_irqchip_mask:
	gpiochip_irqchip_मुक्त_valid_mask(gc);
err_हटाओ_acpi_chip:
	acpi_gpiochip_हटाओ(gc);
err_हटाओ_of_chip:
	gpiochip_मुक्त_hogs(gc);
	of_gpiochip_हटाओ(gc);
err_मुक्त_gpiochip_mask:
	gpiochip_हटाओ_pin_ranges(gc);
	gpiochip_मुक्त_valid_mask(gc);
err_हटाओ_from_list:
	spin_lock_irqsave(&gpio_lock, flags);
	list_del(&gdev->list);
	spin_unlock_irqrestore(&gpio_lock, flags);
err_मुक्त_label:
	kमुक्त_स्थिर(gdev->label);
err_मुक्त_descs:
	kमुक्त(gdev->descs);
err_मुक्त_dev_name:
	kमुक्त(dev_name(&gdev->dev));
err_मुक्त_ida:
	ida_मुक्त(&gpio_ida, gdev->id);
err_मुक्त_gdev:
	/* failures here can mean प्रणालीs won't boot... */
	अगर (ret != -EPROBE_DEFER) अणु
		pr_err("%s: GPIOs %d..%d (%s) failed to register, %d\n", __func__,
		       gdev->base, gdev->base + gdev->ngpio - 1,
		       gc->label ? : "generic", ret);
	पूर्ण
	kमुक्त(gdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_add_data_with_key);

/**
 * gpiochip_get_data() - get per-subdriver data क्रम the chip
 * @gc: GPIO chip
 *
 * Returns:
 * The per-subdriver data क्रम the chip.
 */
व्योम *gpiochip_get_data(काष्ठा gpio_chip *gc)
अणु
	वापस gc->gpiodev->data;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_get_data);

/**
 * gpiochip_हटाओ() - unरेजिस्टर a gpio_chip
 * @gc: the chip to unरेजिस्टर
 *
 * A gpio_chip with any GPIOs still requested may not be हटाओd.
 */
व्योम gpiochip_हटाओ(काष्ठा gpio_chip *gc)
अणु
	काष्ठा gpio_device *gdev = gc->gpiodev;
	अचिन्हित दीर्घ	flags;
	अचिन्हित पूर्णांक	i;

	/* FIXME: should the legacy sysfs handling be moved to gpio_device? */
	gpiochip_sysfs_unरेजिस्टर(gdev);
	gpiochip_मुक्त_hogs(gc);
	/* Numb the device, cancelling all outstanding operations */
	gdev->chip = शून्य;
	gpiochip_irqchip_हटाओ(gc);
	acpi_gpiochip_हटाओ(gc);
	of_gpiochip_हटाओ(gc);
	gpiochip_हटाओ_pin_ranges(gc);
	gpiochip_मुक्त_valid_mask(gc);
	/*
	 * We accept no more calls पूर्णांकo the driver from this poपूर्णांक, so
	 * शून्य the driver data poपूर्णांकer
	 */
	gdev->data = शून्य;

	spin_lock_irqsave(&gpio_lock, flags);
	क्रम (i = 0; i < gdev->ngpio; i++) अणु
		अगर (gpiochip_is_requested(gc, i))
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&gpio_lock, flags);

	अगर (i != gdev->ngpio)
		dev_crit(&gdev->dev,
			 "REMOVING GPIOCHIP WITH GPIOS STILL REQUESTED\n");

	/*
	 * The gpiochip side माला_दो its use of the device to rest here:
	 * अगर there are no userspace clients, the अक्षरdev and device will
	 * be हटाओd, अन्यथा it will be dangling until the last user is
	 * gone.
	 */
	gcdev_unरेजिस्टर(gdev);
	put_device(&gdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_हटाओ);

/**
 * gpiochip_find() - iterator क्रम locating a specअगरic gpio_chip
 * @data: data to pass to match function
 * @match: Callback function to check gpio_chip
 *
 * Similar to bus_find_device.  It वापसs a reference to a gpio_chip as
 * determined by a user supplied @match callback.  The callback should वापस
 * 0 अगर the device करोesn't match and non-zero अगर it करोes.  If the callback is
 * non-zero, this function will वापस to the caller and not iterate over any
 * more gpio_chips.
 */
काष्ठा gpio_chip *gpiochip_find(व्योम *data,
				पूर्णांक (*match)(काष्ठा gpio_chip *gc,
					     व्योम *data))
अणु
	काष्ठा gpio_device *gdev;
	काष्ठा gpio_chip *gc = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);
	list_क्रम_each_entry(gdev, &gpio_devices, list)
		अगर (gdev->chip && match(gdev->chip, data)) अणु
			gc = gdev->chip;
			अवरोध;
		पूर्ण

	spin_unlock_irqrestore(&gpio_lock, flags);

	वापस gc;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_find);

अटल पूर्णांक gpiochip_match_name(काष्ठा gpio_chip *gc, व्योम *data)
अणु
	स्थिर अक्षर *name = data;

	वापस !म_भेद(gc->label, name);
पूर्ण

अटल काष्ठा gpio_chip *find_chip_by_name(स्थिर अक्षर *name)
अणु
	वापस gpiochip_find((व्योम *)name, gpiochip_match_name);
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB_IRQCHIP

/*
 * The following is irqchip helper code क्रम gpiochips.
 */

अटल पूर्णांक gpiochip_irqchip_init_hw(काष्ठा gpio_chip *gc)
अणु
	काष्ठा gpio_irq_chip *girq = &gc->irq;

	अगर (!girq->init_hw)
		वापस 0;

	वापस girq->init_hw(gc);
पूर्ण

अटल पूर्णांक gpiochip_irqchip_init_valid_mask(काष्ठा gpio_chip *gc)
अणु
	काष्ठा gpio_irq_chip *girq = &gc->irq;

	अगर (!girq->init_valid_mask)
		वापस 0;

	girq->valid_mask = gpiochip_allocate_mask(gc);
	अगर (!girq->valid_mask)
		वापस -ENOMEM;

	girq->init_valid_mask(gc, girq->valid_mask, gc->ngpio);

	वापस 0;
पूर्ण

अटल व्योम gpiochip_irqchip_मुक्त_valid_mask(काष्ठा gpio_chip *gc)
अणु
	biपंचांगap_मुक्त(gc->irq.valid_mask);
	gc->irq.valid_mask = शून्य;
पूर्ण

bool gpiochip_irqchip_irq_valid(स्थिर काष्ठा gpio_chip *gc,
				अचिन्हित पूर्णांक offset)
अणु
	अगर (!gpiochip_line_is_valid(gc, offset))
		वापस false;
	/* No mask means all valid */
	अगर (likely(!gc->irq.valid_mask))
		वापस true;
	वापस test_bit(offset, gc->irq.valid_mask);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_irqchip_irq_valid);

#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY

/**
 * gpiochip_set_hierarchical_irqchip() - connects a hierarchical irqchip
 * to a gpiochip
 * @gc: the gpiochip to set the irqchip hierarchical handler to
 * @irqchip: the irqchip to handle this level of the hierarchy, the पूर्णांकerrupt
 * will then percolate up to the parent
 */
अटल व्योम gpiochip_set_hierarchical_irqchip(काष्ठा gpio_chip *gc,
					      काष्ठा irq_chip *irqchip)
अणु
	/* DT will deal with mapping each IRQ as we go aदीर्घ */
	अगर (is_of_node(gc->irq.fwnode))
		वापस;

	/*
	 * This is क्रम legacy and boardfile "irqchip" fwnodes: allocate
	 * irqs upfront instead of dynamically since we करोn't have the
	 * dynamic type of allocation that hardware description languages
	 * provide. Once all GPIO drivers using board files are gone from
	 * the kernel we can delete this code, but क्रम a transitional period
	 * it is necessary to keep this around.
	 */
	अगर (is_fwnode_irqchip(gc->irq.fwnode)) अणु
		पूर्णांक i;
		पूर्णांक ret;

		क्रम (i = 0; i < gc->ngpio; i++) अणु
			काष्ठा irq_fwspec fwspec;
			अचिन्हित पूर्णांक parent_hwirq;
			अचिन्हित पूर्णांक parent_type;
			काष्ठा gpio_irq_chip *girq = &gc->irq;

			/*
			 * We call the child to parent translation function
			 * only to check अगर the child IRQ is valid or not.
			 * Just pick the rising edge type here as that is what
			 * we likely need to support.
			 */
			ret = girq->child_to_parent_hwirq(gc, i,
							  IRQ_TYPE_EDGE_RISING,
							  &parent_hwirq,
							  &parent_type);
			अगर (ret) अणु
				chip_err(gc, "skip set-up on hwirq %d\n",
					 i);
				जारी;
			पूर्ण

			fwspec.fwnode = gc->irq.fwnode;
			/* This is the hwirq क्रम the GPIO line side of things */
			fwspec.param[0] = girq->child_offset_to_irq(gc, i);
			/* Just pick something */
			fwspec.param[1] = IRQ_TYPE_EDGE_RISING;
			fwspec.param_count = 2;
			ret = __irq_करोमुख्य_alloc_irqs(gc->irq.करोमुख्य,
						      /* just pick something */
						      -1,
						      1,
						      NUMA_NO_NODE,
						      &fwspec,
						      false,
						      शून्य);
			अगर (ret < 0) अणु
				chip_err(gc,
					 "can not allocate irq for GPIO line %d parent hwirq %d in hierarchy domain: %d\n",
					 i, parent_hwirq,
					 ret);
			पूर्ण
		पूर्ण
	पूर्ण

	chip_err(gc, "%s unknown fwnode type proceed anyway\n", __func__);

	वापस;
पूर्ण

अटल पूर्णांक gpiochip_hierarchy_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
						   काष्ठा irq_fwspec *fwspec,
						   अचिन्हित दीर्घ *hwirq,
						   अचिन्हित पूर्णांक *type)
अणु
	/* We support standard DT translation */
	अगर (is_of_node(fwspec->fwnode) && fwspec->param_count == 2) अणु
		वापस irq_करोमुख्य_translate_twocell(d, fwspec, hwirq, type);
	पूर्ण

	/* This is क्रम board files and others not using DT */
	अगर (is_fwnode_irqchip(fwspec->fwnode)) अणु
		पूर्णांक ret;

		ret = irq_करोमुख्य_translate_twocell(d, fwspec, hwirq, type);
		अगर (ret)
			वापस ret;
		WARN_ON(*type == IRQ_TYPE_NONE);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gpiochip_hierarchy_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *d,
					       अचिन्हित पूर्णांक irq,
					       अचिन्हित पूर्णांक nr_irqs,
					       व्योम *data)
अणु
	काष्ठा gpio_chip *gc = d->host_data;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	काष्ठा irq_fwspec *fwspec = data;
	व्योम *parent_arg;
	अचिन्हित पूर्णांक parent_hwirq;
	अचिन्हित पूर्णांक parent_type;
	काष्ठा gpio_irq_chip *girq = &gc->irq;
	पूर्णांक ret;

	/*
	 * The nr_irqs parameter is always one except क्रम PCI multi-MSI
	 * so this should not happen.
	 */
	WARN_ON(nr_irqs != 1);

	ret = gc->irq.child_irq_करोमुख्य_ops.translate(d, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	chip_dbg(gc, "allocate IRQ %d, hwirq %lu\n", irq,  hwirq);

	ret = girq->child_to_parent_hwirq(gc, hwirq, type,
					  &parent_hwirq, &parent_type);
	अगर (ret) अणु
		chip_err(gc, "can't look up hwirq %lu\n", hwirq);
		वापस ret;
	पूर्ण
	chip_dbg(gc, "found parent hwirq %u\n", parent_hwirq);

	/*
	 * We set handle_bad_irq because the .set_type() should
	 * always be invoked and set the right type of handler.
	 */
	irq_करोमुख्य_set_info(d,
			    irq,
			    hwirq,
			    gc->irq.chip,
			    gc,
			    girq->handler,
			    शून्य, शून्य);
	irq_set_probe(irq);

	/* This parent only handles निश्चितed level IRQs */
	parent_arg = girq->populate_parent_alloc_arg(gc, parent_hwirq, parent_type);
	अगर (!parent_arg)
		वापस -ENOMEM;

	chip_dbg(gc, "alloc_irqs_parent for %d parent hwirq %d\n",
		  irq, parent_hwirq);
	irq_set_lockdep_class(irq, gc->irq.lock_key, gc->irq.request_key);
	ret = irq_करोमुख्य_alloc_irqs_parent(d, irq, 1, parent_arg);
	/*
	 * If the parent irqकरोमुख्य is msi, the पूर्णांकerrupts have alपढ़ोy
	 * been allocated, so the EEXIST is good.
	 */
	अगर (irq_करोमुख्य_is_msi(d->parent) && (ret == -EEXIST))
		ret = 0;
	अगर (ret)
		chip_err(gc,
			 "failed to allocate parent hwirq %d for hwirq %lu\n",
			 parent_hwirq, hwirq);

	kमुक्त(parent_arg);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक gpiochip_child_offset_to_irq_noop(काष्ठा gpio_chip *gc,
						      अचिन्हित पूर्णांक offset)
अणु
	वापस offset;
पूर्ण

अटल व्योम gpiochip_hierarchy_setup_करोमुख्य_ops(काष्ठा irq_करोमुख्य_ops *ops)
अणु
	ops->activate = gpiochip_irq_करोमुख्य_activate;
	ops->deactivate = gpiochip_irq_करोमुख्य_deactivate;
	ops->alloc = gpiochip_hierarchy_irq_करोमुख्य_alloc;
	ops->मुक्त = irq_करोमुख्य_मुक्त_irqs_common;

	/*
	 * We only allow overriding the translate() function क्रम
	 * hierarchical chips, and this should only be करोne अगर the user
	 * really need something other than 1:1 translation.
	 */
	अगर (!ops->translate)
		ops->translate = gpiochip_hierarchy_irq_करोमुख्य_translate;
पूर्ण

अटल पूर्णांक gpiochip_hierarchy_add_करोमुख्य(काष्ठा gpio_chip *gc)
अणु
	अगर (!gc->irq.child_to_parent_hwirq ||
	    !gc->irq.fwnode) अणु
		chip_err(gc, "missing irqdomain vital data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!gc->irq.child_offset_to_irq)
		gc->irq.child_offset_to_irq = gpiochip_child_offset_to_irq_noop;

	अगर (!gc->irq.populate_parent_alloc_arg)
		gc->irq.populate_parent_alloc_arg =
			gpiochip_populate_parent_fwspec_twocell;

	gpiochip_hierarchy_setup_करोमुख्य_ops(&gc->irq.child_irq_करोमुख्य_ops);

	gc->irq.करोमुख्य = irq_करोमुख्य_create_hierarchy(
		gc->irq.parent_करोमुख्य,
		0,
		gc->ngpio,
		gc->irq.fwnode,
		&gc->irq.child_irq_करोमुख्य_ops,
		gc);

	अगर (!gc->irq.करोमुख्य)
		वापस -ENOMEM;

	gpiochip_set_hierarchical_irqchip(gc, gc->irq.chip);

	वापस 0;
पूर्ण

अटल bool gpiochip_hierarchy_is_hierarchical(काष्ठा gpio_chip *gc)
अणु
	वापस !!gc->irq.parent_करोमुख्य;
पूर्ण

व्योम *gpiochip_populate_parent_fwspec_twocell(काष्ठा gpio_chip *gc,
					     अचिन्हित पूर्णांक parent_hwirq,
					     अचिन्हित पूर्णांक parent_type)
अणु
	काष्ठा irq_fwspec *fwspec;

	fwspec = kदो_स्मृति(माप(*fwspec), GFP_KERNEL);
	अगर (!fwspec)
		वापस शून्य;

	fwspec->fwnode = gc->irq.parent_करोमुख्य->fwnode;
	fwspec->param_count = 2;
	fwspec->param[0] = parent_hwirq;
	fwspec->param[1] = parent_type;

	वापस fwspec;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_populate_parent_fwspec_twocell);

व्योम *gpiochip_populate_parent_fwspec_fourcell(काष्ठा gpio_chip *gc,
					      अचिन्हित पूर्णांक parent_hwirq,
					      अचिन्हित पूर्णांक parent_type)
अणु
	काष्ठा irq_fwspec *fwspec;

	fwspec = kदो_स्मृति(माप(*fwspec), GFP_KERNEL);
	अगर (!fwspec)
		वापस शून्य;

	fwspec->fwnode = gc->irq.parent_करोमुख्य->fwnode;
	fwspec->param_count = 4;
	fwspec->param[0] = 0;
	fwspec->param[1] = parent_hwirq;
	fwspec->param[2] = 0;
	fwspec->param[3] = parent_type;

	वापस fwspec;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_populate_parent_fwspec_fourcell);

#अन्यथा

अटल पूर्णांक gpiochip_hierarchy_add_करोमुख्य(काष्ठा gpio_chip *gc)
अणु
	वापस -EINVAL;
पूर्ण

अटल bool gpiochip_hierarchy_is_hierarchical(काष्ठा gpio_chip *gc)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_IRQ_DOMAIN_HIERARCHY */

/**
 * gpiochip_irq_map() - maps an IRQ पूर्णांकo a GPIO irqchip
 * @d: the irqकरोमुख्य used by this irqchip
 * @irq: the global irq number used by this GPIO irqchip irq
 * @hwirq: the local IRQ/GPIO line offset on this gpiochip
 *
 * This function will set up the mapping क्रम a certain IRQ line on a
 * gpiochip by assigning the gpiochip as chip data, and using the irqchip
 * stored inside the gpiochip.
 */
पूर्णांक gpiochip_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		     irq_hw_number_t hwirq)
अणु
	काष्ठा gpio_chip *gc = d->host_data;
	पूर्णांक ret = 0;

	अगर (!gpiochip_irqchip_irq_valid(gc, hwirq))
		वापस -ENXIO;

	irq_set_chip_data(irq, gc);
	/*
	 * This lock class tells lockdep that GPIO irqs are in a dअगरferent
	 * category than their parents, so it won't report false recursion.
	 */
	irq_set_lockdep_class(irq, gc->irq.lock_key, gc->irq.request_key);
	irq_set_chip_and_handler(irq, gc->irq.chip, gc->irq.handler);
	/* Chips that use nested thपढ़ो handlers have them marked */
	अगर (gc->irq.thपढ़ोed)
		irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	अगर (gc->irq.num_parents == 1)
		ret = irq_set_parent(irq, gc->irq.parents[0]);
	अन्यथा अगर (gc->irq.map)
		ret = irq_set_parent(irq, gc->irq.map[hwirq]);

	अगर (ret < 0)
		वापस ret;

	/*
	 * No set-up of the hardware will happen अगर IRQ_TYPE_NONE
	 * is passed as शेष type.
	 */
	अगर (gc->irq.शेष_type != IRQ_TYPE_NONE)
		irq_set_irq_type(irq, gc->irq.शेष_type);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_irq_map);

व्योम gpiochip_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा gpio_chip *gc = d->host_data;

	अगर (gc->irq.thपढ़ोed)
		irq_set_nested_thपढ़ो(irq, 0);
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_irq_unmap);

अटल स्थिर काष्ठा irq_करोमुख्य_ops gpiochip_करोमुख्य_ops = अणु
	.map	= gpiochip_irq_map,
	.unmap	= gpiochip_irq_unmap,
	/* Virtually all GPIO irqchips are twocell:ed */
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

/*
 * TODO: move these activate/deactivate in under the hierarchicial
 * irqchip implementation as अटल once SPMI and SSBI (all बाह्यal
 * users) are phased over.
 */
/**
 * gpiochip_irq_करोमुख्य_activate() - Lock a GPIO to be used as an IRQ
 * @करोमुख्य: The IRQ करोमुख्य used by this IRQ chip
 * @data: Outermost irq_data associated with the IRQ
 * @reserve: If set, only reserve an पूर्णांकerrupt vector instead of assigning one
 *
 * This function is a wrapper that calls gpiochip_lock_as_irq() and is to be
 * used as the activate function क्रम the &काष्ठा irq_करोमुख्य_ops. The host_data
 * क्रम the IRQ करोमुख्य must be the &काष्ठा gpio_chip.
 */
पूर्णांक gpiochip_irq_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				 काष्ठा irq_data *data, bool reserve)
अणु
	काष्ठा gpio_chip *gc = करोमुख्य->host_data;

	वापस gpiochip_lock_as_irq(gc, data->hwirq);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_irq_करोमुख्य_activate);

/**
 * gpiochip_irq_करोमुख्य_deactivate() - Unlock a GPIO used as an IRQ
 * @करोमुख्य: The IRQ करोमुख्य used by this IRQ chip
 * @data: Outermost irq_data associated with the IRQ
 *
 * This function is a wrapper that will call gpiochip_unlock_as_irq() and is to
 * be used as the deactivate function क्रम the &काष्ठा irq_करोमुख्य_ops. The
 * host_data क्रम the IRQ करोमुख्य must be the &काष्ठा gpio_chip.
 */
व्योम gpiochip_irq_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				    काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gc = करोमुख्य->host_data;

	वापस gpiochip_unlock_as_irq(gc, data->hwirq);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_irq_करोमुख्य_deactivate);

अटल पूर्णांक gpiochip_to_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = gc->irq.करोमुख्य;

	अगर (!gpiochip_irqchip_irq_valid(gc, offset))
		वापस -ENXIO;

#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
	अगर (irq_करोमुख्य_is_hierarchy(करोमुख्य)) अणु
		काष्ठा irq_fwspec spec;

		spec.fwnode = करोमुख्य->fwnode;
		spec.param_count = 2;
		spec.param[0] = gc->irq.child_offset_to_irq(gc, offset);
		spec.param[1] = IRQ_TYPE_NONE;

		वापस irq_create_fwspec_mapping(&spec);
	पूर्ण
#पूर्ण_अगर

	वापस irq_create_mapping(करोमुख्य, offset);
पूर्ण

अटल पूर्णांक gpiochip_irq_reqres(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	वापस gpiochip_reqres_irq(gc, d->hwirq);
पूर्ण

अटल व्योम gpiochip_irq_relres(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	gpiochip_relres_irq(gc, d->hwirq);
पूर्ण

अटल व्योम gpiochip_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	अगर (gc->irq.irq_mask)
		gc->irq.irq_mask(d);
	gpiochip_disable_irq(gc, d->hwirq);
पूर्ण

अटल व्योम gpiochip_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	gpiochip_enable_irq(gc, d->hwirq);
	अगर (gc->irq.irq_unmask)
		gc->irq.irq_unmask(d);
पूर्ण

अटल व्योम gpiochip_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	gpiochip_enable_irq(gc, d->hwirq);
	gc->irq.irq_enable(d);
पूर्ण

अटल व्योम gpiochip_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	gc->irq.irq_disable(d);
	gpiochip_disable_irq(gc, d->hwirq);
पूर्ण

अटल व्योम gpiochip_set_irq_hooks(काष्ठा gpio_chip *gc)
अणु
	काष्ठा irq_chip *irqchip = gc->irq.chip;

	अगर (!irqchip->irq_request_resources &&
	    !irqchip->irq_release_resources) अणु
		irqchip->irq_request_resources = gpiochip_irq_reqres;
		irqchip->irq_release_resources = gpiochip_irq_relres;
	पूर्ण
	अगर (WARN_ON(gc->irq.irq_enable))
		वापस;
	/* Check अगर the irqchip alपढ़ोy has this hook... */
	अगर (irqchip->irq_enable == gpiochip_irq_enable ||
		irqchip->irq_mask == gpiochip_irq_mask) अणु
		/*
		 * ...and अगर so, give a gentle warning that this is bad
		 * practice.
		 */
		chip_info(gc,
			  "detected irqchip that is shared with multiple gpiochips: please fix the driver.\n");
		वापस;
	पूर्ण

	अगर (irqchip->irq_disable) अणु
		gc->irq.irq_disable = irqchip->irq_disable;
		irqchip->irq_disable = gpiochip_irq_disable;
	पूर्ण अन्यथा अणु
		gc->irq.irq_mask = irqchip->irq_mask;
		irqchip->irq_mask = gpiochip_irq_mask;
	पूर्ण

	अगर (irqchip->irq_enable) अणु
		gc->irq.irq_enable = irqchip->irq_enable;
		irqchip->irq_enable = gpiochip_irq_enable;
	पूर्ण अन्यथा अणु
		gc->irq.irq_unmask = irqchip->irq_unmask;
		irqchip->irq_unmask = gpiochip_irq_unmask;
	पूर्ण
पूर्ण

/**
 * gpiochip_add_irqchip() - adds an IRQ chip to a GPIO chip
 * @gc: the GPIO chip to add the IRQ chip to
 * @lock_key: lockdep class क्रम IRQ lock
 * @request_key: lockdep class क्रम IRQ request
 */
अटल पूर्णांक gpiochip_add_irqchip(काष्ठा gpio_chip *gc,
				काष्ठा lock_class_key *lock_key,
				काष्ठा lock_class_key *request_key)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(&gc->gpiodev->dev);
	काष्ठा irq_chip *irqchip = gc->irq.chip;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक i;

	अगर (!irqchip)
		वापस 0;

	अगर (gc->irq.parent_handler && gc->can_sleep) अणु
		chip_err(gc, "you cannot have chained interrupts on a chip that may sleep\n");
		वापस -EINVAL;
	पूर्ण

	type = gc->irq.शेष_type;

	/*
	 * Specअगरying a शेष trigger is a terrible idea अगर DT or ACPI is
	 * used to configure the पूर्णांकerrupts, as you may end up with
	 * conflicting triggers. Tell the user, and reset to NONE.
	 */
	अगर (WARN(fwnode && type != IRQ_TYPE_NONE,
		 "%pfw: Ignoring %u default trigger\n", fwnode, type))
		type = IRQ_TYPE_NONE;

	अगर (gc->to_irq)
		chip_warn(gc, "to_irq is redefined in %s and you shouldn't rely on it\n", __func__);

	gc->to_irq = gpiochip_to_irq;
	gc->irq.शेष_type = type;
	gc->irq.lock_key = lock_key;
	gc->irq.request_key = request_key;

	/* If a parent irqकरोमुख्य is provided, let's build a hierarchy */
	अगर (gpiochip_hierarchy_is_hierarchical(gc)) अणु
		पूर्णांक ret = gpiochip_hierarchy_add_करोमुख्य(gc);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Some drivers provide custom irqकरोमुख्य ops */
		gc->irq.करोमुख्य = irq_करोमुख्य_create_simple(fwnode,
			gc->ngpio,
			gc->irq.first,
			gc->irq.करोमुख्य_ops ?: &gpiochip_करोमुख्य_ops,
			gc);
		अगर (!gc->irq.करोमुख्य)
			वापस -EINVAL;
	पूर्ण

	अगर (gc->irq.parent_handler) अणु
		व्योम *data = gc->irq.parent_handler_data ?: gc;

		क्रम (i = 0; i < gc->irq.num_parents; i++) अणु
			/*
			 * The parent IRQ chip is alपढ़ोy using the chip_data
			 * क्रम this IRQ chip, so our callbacks simply use the
			 * handler_data.
			 */
			irq_set_chained_handler_and_data(gc->irq.parents[i],
							 gc->irq.parent_handler,
							 data);
		पूर्ण
	पूर्ण

	gpiochip_set_irq_hooks(gc);

	acpi_gpiochip_request_पूर्णांकerrupts(gc);

	वापस 0;
पूर्ण

/**
 * gpiochip_irqchip_हटाओ() - हटाओs an irqchip added to a gpiochip
 * @gc: the gpiochip to हटाओ the irqchip from
 *
 * This is called only from gpiochip_हटाओ()
 */
अटल व्योम gpiochip_irqchip_हटाओ(काष्ठा gpio_chip *gc)
अणु
	काष्ठा irq_chip *irqchip = gc->irq.chip;
	अचिन्हित पूर्णांक offset;

	acpi_gpiochip_मुक्त_पूर्णांकerrupts(gc);

	अगर (irqchip && gc->irq.parent_handler) अणु
		काष्ठा gpio_irq_chip *irq = &gc->irq;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < irq->num_parents; i++)
			irq_set_chained_handler_and_data(irq->parents[i],
							 शून्य, शून्य);
	पूर्ण

	/* Remove all IRQ mappings and delete the करोमुख्य */
	अगर (gc->irq.करोमुख्य) अणु
		अचिन्हित पूर्णांक irq;

		क्रम (offset = 0; offset < gc->ngpio; offset++) अणु
			अगर (!gpiochip_irqchip_irq_valid(gc, offset))
				जारी;

			irq = irq_find_mapping(gc->irq.करोमुख्य, offset);
			irq_dispose_mapping(irq);
		पूर्ण

		irq_करोमुख्य_हटाओ(gc->irq.करोमुख्य);
	पूर्ण

	अगर (irqchip) अणु
		अगर (irqchip->irq_request_resources == gpiochip_irq_reqres) अणु
			irqchip->irq_request_resources = शून्य;
			irqchip->irq_release_resources = शून्य;
		पूर्ण
		अगर (irqchip->irq_enable == gpiochip_irq_enable) अणु
			irqchip->irq_enable = gc->irq.irq_enable;
			irqchip->irq_disable = gc->irq.irq_disable;
		पूर्ण
	पूर्ण
	gc->irq.irq_enable = शून्य;
	gc->irq.irq_disable = शून्य;
	gc->irq.chip = शून्य;

	gpiochip_irqchip_मुक्त_valid_mask(gc);
पूर्ण

/**
 * gpiochip_irqchip_add_करोमुख्य() - adds an irqकरोमुख्य to a gpiochip
 * @gc: the gpiochip to add the irqchip to
 * @करोमुख्य: the irqकरोमुख्य to add to the gpiochip
 *
 * This function adds an IRQ करोमुख्य to the gpiochip.
 */
पूर्णांक gpiochip_irqchip_add_करोमुख्य(काष्ठा gpio_chip *gc,
				काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	अगर (!करोमुख्य)
		वापस -EINVAL;

	gc->to_irq = gpiochip_to_irq;
	gc->irq.करोमुख्य = करोमुख्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_irqchip_add_करोमुख्य);

#अन्यथा /* CONFIG_GPIOLIB_IRQCHIP */

अटल अंतरभूत पूर्णांक gpiochip_add_irqchip(काष्ठा gpio_chip *gc,
				       काष्ठा lock_class_key *lock_key,
				       काष्ठा lock_class_key *request_key)
अणु
	वापस 0;
पूर्ण
अटल व्योम gpiochip_irqchip_हटाओ(काष्ठा gpio_chip *gc) अणुपूर्ण

अटल अंतरभूत पूर्णांक gpiochip_irqchip_init_hw(काष्ठा gpio_chip *gc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gpiochip_irqchip_init_valid_mask(काष्ठा gpio_chip *gc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम gpiochip_irqchip_मुक्त_valid_mask(काष्ठा gpio_chip *gc)
अणु पूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB_IRQCHIP */

/**
 * gpiochip_generic_request() - request the gpio function क्रम a pin
 * @gc: the gpiochip owning the GPIO
 * @offset: the offset of the GPIO to request क्रम GPIO function
 */
पूर्णांक gpiochip_generic_request(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
#अगर_घोषित CONFIG_PINCTRL
	अगर (list_empty(&gc->gpiodev->pin_ranges))
		वापस 0;
#पूर्ण_अगर

	वापस pinctrl_gpio_request(gc->gpiodev->base + offset);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_generic_request);

/**
 * gpiochip_generic_मुक्त() - मुक्त the gpio function from a pin
 * @gc: the gpiochip to request the gpio function क्रम
 * @offset: the offset of the GPIO to मुक्त from GPIO function
 */
व्योम gpiochip_generic_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
#अगर_घोषित CONFIG_PINCTRL
	अगर (list_empty(&gc->gpiodev->pin_ranges))
		वापस;
#पूर्ण_अगर

	pinctrl_gpio_मुक्त(gc->gpiodev->base + offset);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_generic_मुक्त);

/**
 * gpiochip_generic_config() - apply configuration क्रम a pin
 * @gc: the gpiochip owning the GPIO
 * @offset: the offset of the GPIO to apply the configuration
 * @config: the configuration to be applied
 */
पूर्णांक gpiochip_generic_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			    अचिन्हित दीर्घ config)
अणु
	वापस pinctrl_gpio_set_config(gc->gpiodev->base + offset, config);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_generic_config);

#अगर_घोषित CONFIG_PINCTRL

/**
 * gpiochip_add_pingroup_range() - add a range क्रम GPIO <-> pin mapping
 * @gc: the gpiochip to add the range क्रम
 * @pctldev: the pin controller to map to
 * @gpio_offset: the start offset in the current gpio_chip number space
 * @pin_group: name of the pin group inside the pin controller
 *
 * Calling this function directly from a DeviceTree-supported
 * pinctrl driver is DEPRECATED. Please see Section 2.1 of
 * Documentation/devicetree/bindings/gpio/gpio.txt on how to
 * bind pinctrl and gpio drivers via the "gpio-ranges" property.
 */
पूर्णांक gpiochip_add_pingroup_range(काष्ठा gpio_chip *gc,
			काष्ठा pinctrl_dev *pctldev,
			अचिन्हित पूर्णांक gpio_offset, स्थिर अक्षर *pin_group)
अणु
	काष्ठा gpio_pin_range *pin_range;
	काष्ठा gpio_device *gdev = gc->gpiodev;
	पूर्णांक ret;

	pin_range = kzalloc(माप(*pin_range), GFP_KERNEL);
	अगर (!pin_range) अणु
		chip_err(gc, "failed to allocate pin ranges\n");
		वापस -ENOMEM;
	पूर्ण

	/* Use local offset as range ID */
	pin_range->range.id = gpio_offset;
	pin_range->range.gc = gc;
	pin_range->range.name = gc->label;
	pin_range->range.base = gdev->base + gpio_offset;
	pin_range->pctldev = pctldev;

	ret = pinctrl_get_group_pins(pctldev, pin_group,
					&pin_range->range.pins,
					&pin_range->range.npins);
	अगर (ret < 0) अणु
		kमुक्त(pin_range);
		वापस ret;
	पूर्ण

	pinctrl_add_gpio_range(pctldev, &pin_range->range);

	chip_dbg(gc, "created GPIO range %d->%d ==> %s PINGRP %s\n",
		 gpio_offset, gpio_offset + pin_range->range.npins - 1,
		 pinctrl_dev_get_devname(pctldev), pin_group);

	list_add_tail(&pin_range->node, &gdev->pin_ranges);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_add_pingroup_range);

/**
 * gpiochip_add_pin_range() - add a range क्रम GPIO <-> pin mapping
 * @gc: the gpiochip to add the range क्रम
 * @pinctl_name: the dev_name() of the pin controller to map to
 * @gpio_offset: the start offset in the current gpio_chip number space
 * @pin_offset: the start offset in the pin controller number space
 * @npins: the number of pins from the offset of each pin space (GPIO and
 *	pin controller) to accumulate in this range
 *
 * Returns:
 * 0 on success, or a negative error-code on failure.
 *
 * Calling this function directly from a DeviceTree-supported
 * pinctrl driver is DEPRECATED. Please see Section 2.1 of
 * Documentation/devicetree/bindings/gpio/gpio.txt on how to
 * bind pinctrl and gpio drivers via the "gpio-ranges" property.
 */
पूर्णांक gpiochip_add_pin_range(काष्ठा gpio_chip *gc, स्थिर अक्षर *pinctl_name,
			   अचिन्हित पूर्णांक gpio_offset, अचिन्हित पूर्णांक pin_offset,
			   अचिन्हित पूर्णांक npins)
अणु
	काष्ठा gpio_pin_range *pin_range;
	काष्ठा gpio_device *gdev = gc->gpiodev;
	पूर्णांक ret;

	pin_range = kzalloc(माप(*pin_range), GFP_KERNEL);
	अगर (!pin_range) अणु
		chip_err(gc, "failed to allocate pin ranges\n");
		वापस -ENOMEM;
	पूर्ण

	/* Use local offset as range ID */
	pin_range->range.id = gpio_offset;
	pin_range->range.gc = gc;
	pin_range->range.name = gc->label;
	pin_range->range.base = gdev->base + gpio_offset;
	pin_range->range.pin_base = pin_offset;
	pin_range->range.npins = npins;
	pin_range->pctldev = pinctrl_find_and_add_gpio_range(pinctl_name,
			&pin_range->range);
	अगर (IS_ERR(pin_range->pctldev)) अणु
		ret = PTR_ERR(pin_range->pctldev);
		chip_err(gc, "could not create pin range\n");
		kमुक्त(pin_range);
		वापस ret;
	पूर्ण
	chip_dbg(gc, "created GPIO range %d->%d ==> %s PIN %d->%d\n",
		 gpio_offset, gpio_offset + npins - 1,
		 pinctl_name,
		 pin_offset, pin_offset + npins - 1);

	list_add_tail(&pin_range->node, &gdev->pin_ranges);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_add_pin_range);

/**
 * gpiochip_हटाओ_pin_ranges() - हटाओ all the GPIO <-> pin mappings
 * @gc: the chip to हटाओ all the mappings क्रम
 */
व्योम gpiochip_हटाओ_pin_ranges(काष्ठा gpio_chip *gc)
अणु
	काष्ठा gpio_pin_range *pin_range, *पंचांगp;
	काष्ठा gpio_device *gdev = gc->gpiodev;

	list_क्रम_each_entry_safe(pin_range, पंचांगp, &gdev->pin_ranges, node) अणु
		list_del(&pin_range->node);
		pinctrl_हटाओ_gpio_range(pin_range->pctldev,
				&pin_range->range);
		kमुक्त(pin_range);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_हटाओ_pin_ranges);

#पूर्ण_अगर /* CONFIG_PINCTRL */

/* These "optional" allocation calls help prevent drivers from stomping
 * on each other, and help provide better diagnostics in debugfs.
 * They're called even less than the "set direction" calls.
 */
अटल पूर्णांक gpiod_request_commit(काष्ठा gpio_desc *desc, स्थिर अक्षर *label)
अणु
	काष्ठा gpio_chip	*gc = desc->gdev->chip;
	पूर्णांक			ret;
	अचिन्हित दीर्घ		flags;
	अचिन्हित		offset;

	अगर (label) अणु
		label = kstrdup_स्थिर(label, GFP_KERNEL);
		अगर (!label)
			वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&gpio_lock, flags);

	/* NOTE:  gpio_request() can be called in early boot,
	 * beक्रमe IRQs are enabled, क्रम non-sleeping (SOC) GPIOs.
	 */

	अगर (test_and_set_bit(FLAG_REQUESTED, &desc->flags) == 0) अणु
		desc_set_label(desc, label ? : "?");
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
		जाओ out_मुक्त_unlock;
	पूर्ण

	अगर (gc->request) अणु
		/* gc->request may sleep */
		spin_unlock_irqrestore(&gpio_lock, flags);
		offset = gpio_chip_hwgpio(desc);
		अगर (gpiochip_line_is_valid(gc, offset))
			ret = gc->request(gc, offset);
		अन्यथा
			ret = -EINVAL;
		spin_lock_irqsave(&gpio_lock, flags);

		अगर (ret) अणु
			desc_set_label(desc, शून्य);
			clear_bit(FLAG_REQUESTED, &desc->flags);
			जाओ out_मुक्त_unlock;
		पूर्ण
	पूर्ण
	अगर (gc->get_direction) अणु
		/* gc->get_direction may sleep */
		spin_unlock_irqrestore(&gpio_lock, flags);
		gpiod_get_direction(desc);
		spin_lock_irqsave(&gpio_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&gpio_lock, flags);
	वापस 0;

out_मुक्त_unlock:
	spin_unlock_irqrestore(&gpio_lock, flags);
	kमुक्त_स्थिर(label);
	वापस ret;
पूर्ण

/*
 * This descriptor validation needs to be inserted verbatim पूर्णांकo each
 * function taking a descriptor, so we need to use a preprocessor
 * macro to aव्योम endless duplication. If the desc is शून्य it is an
 * optional GPIO and calls should just bail out.
 */
अटल पूर्णांक validate_desc(स्थिर काष्ठा gpio_desc *desc, स्थिर अक्षर *func)
अणु
	अगर (!desc)
		वापस 0;
	अगर (IS_ERR(desc)) अणु
		pr_warn("%s: invalid GPIO (errorpointer)\n", func);
		वापस PTR_ERR(desc);
	पूर्ण
	अगर (!desc->gdev) अणु
		pr_warn("%s: invalid GPIO (no device)\n", func);
		वापस -EINVAL;
	पूर्ण
	अगर (!desc->gdev->chip) अणु
		dev_warn(&desc->gdev->dev,
			 "%s: backing chip is gone\n", func);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

#घोषणा VALIDATE_DESC(desc) करो अणु \
	पूर्णांक __valid = validate_desc(desc, __func__); \
	अगर (__valid <= 0) \
		वापस __valid; \
	पूर्ण जबतक (0)

#घोषणा VALIDATE_DESC_VOID(desc) करो अणु \
	पूर्णांक __valid = validate_desc(desc, __func__); \
	अगर (__valid <= 0) \
		वापस; \
	पूर्ण जबतक (0)

पूर्णांक gpiod_request(काष्ठा gpio_desc *desc, स्थिर अक्षर *label)
अणु
	पूर्णांक ret = -EPROBE_DEFER;
	काष्ठा gpio_device *gdev;

	VALIDATE_DESC(desc);
	gdev = desc->gdev;

	अगर (try_module_get(gdev->owner)) अणु
		ret = gpiod_request_commit(desc, label);
		अगर (ret)
			module_put(gdev->owner);
		अन्यथा
			get_device(&gdev->dev);
	पूर्ण

	अगर (ret)
		gpiod_dbg(desc, "%s: status %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल bool gpiod_मुक्त_commit(काष्ठा gpio_desc *desc)
अणु
	bool			ret = false;
	अचिन्हित दीर्घ		flags;
	काष्ठा gpio_chip	*gc;

	might_sleep();

	gpiod_unexport(desc);

	spin_lock_irqsave(&gpio_lock, flags);

	gc = desc->gdev->chip;
	अगर (gc && test_bit(FLAG_REQUESTED, &desc->flags)) अणु
		अगर (gc->मुक्त) अणु
			spin_unlock_irqrestore(&gpio_lock, flags);
			might_sleep_अगर(gc->can_sleep);
			gc->मुक्त(gc, gpio_chip_hwgpio(desc));
			spin_lock_irqsave(&gpio_lock, flags);
		पूर्ण
		kमुक्त_स्थिर(desc->label);
		desc_set_label(desc, शून्य);
		clear_bit(FLAG_ACTIVE_LOW, &desc->flags);
		clear_bit(FLAG_REQUESTED, &desc->flags);
		clear_bit(FLAG_OPEN_DRAIN, &desc->flags);
		clear_bit(FLAG_OPEN_SOURCE, &desc->flags);
		clear_bit(FLAG_PULL_UP, &desc->flags);
		clear_bit(FLAG_PULL_DOWN, &desc->flags);
		clear_bit(FLAG_BIAS_DISABLE, &desc->flags);
		clear_bit(FLAG_EDGE_RISING, &desc->flags);
		clear_bit(FLAG_EDGE_FALLING, &desc->flags);
		clear_bit(FLAG_IS_HOGGED, &desc->flags);
#अगर_घोषित CONFIG_OF_DYNAMIC
		desc->hog = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_GPIO_CDEV
		WRITE_ONCE(desc->debounce_period_us, 0);
#पूर्ण_अगर
		ret = true;
	पूर्ण

	spin_unlock_irqrestore(&gpio_lock, flags);
	blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
				     GPIOLINE_CHANGED_RELEASED, desc);

	वापस ret;
पूर्ण

व्योम gpiod_मुक्त(काष्ठा gpio_desc *desc)
अणु
	अगर (desc && desc->gdev && gpiod_मुक्त_commit(desc)) अणु
		module_put(desc->gdev->owner);
		put_device(&desc->gdev->dev);
	पूर्ण अन्यथा अणु
		WARN_ON(extra_checks);
	पूर्ण
पूर्ण

/**
 * gpiochip_is_requested - वापस string अगरf संकेत was requested
 * @gc: controller managing the संकेत
 * @offset: of संकेत within controller's 0..(ngpio - 1) range
 *
 * Returns शून्य अगर the GPIO is not currently requested, अन्यथा a string.
 * The string वापसed is the label passed to gpio_request(); अगर none has been
 * passed it is a meaningless, non-शून्य स्थिरant.
 *
 * This function is क्रम use by GPIO controller drivers.  The label can
 * help with diagnostics, and knowing that the संकेत is used as a GPIO
 * can help aव्योम accidentally multiplexing it to another controller.
 */
स्थिर अक्षर *gpiochip_is_requested(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_desc *desc;

	अगर (offset >= gc->ngpio)
		वापस शून्य;

	desc = gpiochip_get_desc(gc, offset);
	अगर (IS_ERR(desc))
		वापस शून्य;

	अगर (test_bit(FLAG_REQUESTED, &desc->flags) == 0)
		वापस शून्य;
	वापस desc->label;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_is_requested);

/**
 * gpiochip_request_own_desc - Allow GPIO chip to request its own descriptor
 * @gc: GPIO chip
 * @hwnum: hardware number of the GPIO क्रम which to request the descriptor
 * @label: label क्रम the GPIO
 * @lflags: lookup flags क्रम this GPIO or 0 अगर शेष, this can be used to
 * specअगरy things like line inversion semantics with the machine flags
 * such as GPIO_OUT_LOW
 * @dflags: descriptor request flags क्रम this GPIO or 0 अगर शेष, this
 * can be used to specअगरy consumer semantics such as खोलो drain
 *
 * Function allows GPIO chip drivers to request and use their own GPIO
 * descriptors via gpiolib API. Dअगरference to gpiod_request() is that this
 * function will not increase reference count of the GPIO chip module. This
 * allows the GPIO chip module to be unloaded as needed (we assume that the
 * GPIO chip driver handles मुक्तing the GPIOs it has requested).
 *
 * Returns:
 * A poपूर्णांकer to the GPIO descriptor, or an ERR_PTR()-encoded negative error
 * code on failure.
 */
काष्ठा gpio_desc *gpiochip_request_own_desc(काष्ठा gpio_chip *gc,
					    अचिन्हित पूर्णांक hwnum,
					    स्थिर अक्षर *label,
					    क्रमागत gpio_lookup_flags lflags,
					    क्रमागत gpiod_flags dflags)
अणु
	काष्ठा gpio_desc *desc = gpiochip_get_desc(gc, hwnum);
	पूर्णांक ret;

	अगर (IS_ERR(desc)) अणु
		chip_err(gc, "failed to get GPIO descriptor\n");
		वापस desc;
	पूर्ण

	ret = gpiod_request_commit(desc, label);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	ret = gpiod_configure_flags(desc, label, lflags, dflags);
	अगर (ret) अणु
		chip_err(gc, "setup of own GPIO %s failed\n", label);
		gpiod_मुक्त_commit(desc);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_request_own_desc);

/**
 * gpiochip_मुक्त_own_desc - Free GPIO requested by the chip driver
 * @desc: GPIO descriptor to मुक्त
 *
 * Function मुक्तs the given GPIO requested previously with
 * gpiochip_request_own_desc().
 */
व्योम gpiochip_मुक्त_own_desc(काष्ठा gpio_desc *desc)
अणु
	अगर (desc)
		gpiod_मुक्त_commit(desc);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_मुक्त_own_desc);

/*
 * Drivers MUST set GPIO direction beक्रमe making get/set calls.  In
 * some हालs this is करोne in early boot, beक्रमe IRQs are enabled.
 *
 * As a rule these aren't called more than once (except क्रम drivers
 * using the खोलो-drain emulation idiom) so these are natural places
 * to accumulate extra debugging checks.  Note that we can't (yet)
 * rely on gpio_request() having been called beक्रमehand.
 */

अटल पूर्णांक gpio_करो_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			      अचिन्हित दीर्घ config)
अणु
	अगर (!gc->set_config)
		वापस -ENOTSUPP;

	वापस gc->set_config(gc, offset, config);
पूर्ण

अटल पूर्णांक gpio_set_config_with_argument(काष्ठा gpio_desc *desc,
					 क्रमागत pin_config_param mode,
					 u32 argument)
अणु
	काष्ठा gpio_chip *gc = desc->gdev->chip;
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(mode, argument);
	वापस gpio_करो_set_config(gc, gpio_chip_hwgpio(desc), config);
पूर्ण

अटल पूर्णांक gpio_set_config_with_argument_optional(काष्ठा gpio_desc *desc,
						  क्रमागत pin_config_param mode,
						  u32 argument)
अणु
	काष्ठा device *dev = &desc->gdev->dev;
	पूर्णांक gpio = gpio_chip_hwgpio(desc);
	पूर्णांक ret;

	ret = gpio_set_config_with_argument(desc, mode, argument);
	अगर (ret != -ENOTSUPP)
		वापस ret;

	चयन (mode) अणु
	हाल PIN_CONFIG_PERSIST_STATE:
		dev_dbg(dev, "Persistence not supported for GPIO %d\n", gpio);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_set_config(काष्ठा gpio_desc *desc, क्रमागत pin_config_param mode)
अणु
	वापस gpio_set_config_with_argument(desc, mode, 0);
पूर्ण

अटल पूर्णांक gpio_set_bias(काष्ठा gpio_desc *desc)
अणु
	क्रमागत pin_config_param bias;
	अचिन्हित पूर्णांक arg;

	अगर (test_bit(FLAG_BIAS_DISABLE, &desc->flags))
		bias = PIN_CONFIG_BIAS_DISABLE;
	अन्यथा अगर (test_bit(FLAG_PULL_UP, &desc->flags))
		bias = PIN_CONFIG_BIAS_PULL_UP;
	अन्यथा अगर (test_bit(FLAG_PULL_DOWN, &desc->flags))
		bias = PIN_CONFIG_BIAS_PULL_DOWN;
	अन्यथा
		वापस 0;

	चयन (bias) अणु
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
	हाल PIN_CONFIG_BIAS_PULL_UP:
		arg = 1;
		अवरोध;

	शेष:
		arg = 0;
		अवरोध;
	पूर्ण

	वापस gpio_set_config_with_argument_optional(desc, bias, arg);
पूर्ण

पूर्णांक gpio_set_debounce_समयout(काष्ठा gpio_desc *desc, अचिन्हित पूर्णांक debounce)
अणु
	वापस gpio_set_config_with_argument_optional(desc,
						      PIN_CONFIG_INPUT_DEBOUNCE,
						      debounce);
पूर्ण

/**
 * gpiod_direction_input - set the GPIO direction to input
 * @desc:	GPIO to set to input
 *
 * Set the direction of the passed GPIO to input, such as gpiod_get_value() can
 * be called safely on it.
 *
 * Return 0 in हाल of success, अन्यथा an error code.
 */
पूर्णांक gpiod_direction_input(काष्ठा gpio_desc *desc)
अणु
	काष्ठा gpio_chip	*gc;
	पूर्णांक			ret = 0;

	VALIDATE_DESC(desc);
	gc = desc->gdev->chip;

	/*
	 * It is legal to have no .get() and .direction_input() specअगरied अगर
	 * the chip is output-only, but you can't specअगरy .direction_input()
	 * and not support the .get() operation, that करोesn't make sense.
	 */
	अगर (!gc->get && gc->direction_input) अणु
		gpiod_warn(desc,
			   "%s: missing get() but have direction_input()\n",
			   __func__);
		वापस -EIO;
	पूर्ण

	/*
	 * If we have a .direction_input() callback, things are simple,
	 * just call it. Else we are some input-only chip so try to check the
	 * direction (अगर .get_direction() is supported) अन्यथा we silently
	 * assume we are in input mode after this.
	 */
	अगर (gc->direction_input) अणु
		ret = gc->direction_input(gc, gpio_chip_hwgpio(desc));
	पूर्ण अन्यथा अगर (gc->get_direction &&
		  (gc->get_direction(gc, gpio_chip_hwgpio(desc)) != 1)) अणु
		gpiod_warn(desc,
			   "%s: missing direction_input() operation and line is output\n",
			   __func__);
		वापस -EIO;
	पूर्ण
	अगर (ret == 0) अणु
		clear_bit(FLAG_IS_OUT, &desc->flags);
		ret = gpio_set_bias(desc);
	पूर्ण

	trace_gpio_direction(desc_to_gpio(desc), 1, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_direction_input);

अटल पूर्णांक gpiod_direction_output_raw_commit(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	काष्ठा gpio_chip *gc = desc->gdev->chip;
	पूर्णांक val = !!value;
	पूर्णांक ret = 0;

	/*
	 * It's OK not to specअगरy .direction_output() अगर the gpiochip is
	 * output-only, but अगर there is then not even a .set() operation it
	 * is pretty tricky to drive the output line.
	 */
	अगर (!gc->set && !gc->direction_output) अणु
		gpiod_warn(desc,
			   "%s: missing set() and direction_output() operations\n",
			   __func__);
		वापस -EIO;
	पूर्ण

	अगर (gc->direction_output) अणु
		ret = gc->direction_output(gc, gpio_chip_hwgpio(desc), val);
	पूर्ण अन्यथा अणु
		/* Check that we are in output mode अगर we can */
		अगर (gc->get_direction &&
		    gc->get_direction(gc, gpio_chip_hwgpio(desc))) अणु
			gpiod_warn(desc,
				"%s: missing direction_output() operation\n",
				__func__);
			वापस -EIO;
		पूर्ण
		/*
		 * If we can't actively set the direction, we are some
		 * output-only chip, so just drive the output as desired.
		 */
		gc->set(gc, gpio_chip_hwgpio(desc), val);
	पूर्ण

	अगर (!ret)
		set_bit(FLAG_IS_OUT, &desc->flags);
	trace_gpio_value(desc_to_gpio(desc), 0, val);
	trace_gpio_direction(desc_to_gpio(desc), 0, ret);
	वापस ret;
पूर्ण

/**
 * gpiod_direction_output_raw - set the GPIO direction to output
 * @desc:	GPIO to set to output
 * @value:	initial output value of the GPIO
 *
 * Set the direction of the passed GPIO to output, such as gpiod_set_value() can
 * be called safely on it. The initial value of the output must be specअगरied
 * as raw value on the physical line without regard क्रम the ACTIVE_LOW status.
 *
 * Return 0 in हाल of success, अन्यथा an error code.
 */
पूर्णांक gpiod_direction_output_raw(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	VALIDATE_DESC(desc);
	वापस gpiod_direction_output_raw_commit(desc, value);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_direction_output_raw);

/**
 * gpiod_direction_output - set the GPIO direction to output
 * @desc:	GPIO to set to output
 * @value:	initial output value of the GPIO
 *
 * Set the direction of the passed GPIO to output, such as gpiod_set_value() can
 * be called safely on it. The initial value of the output must be specअगरied
 * as the logical value of the GPIO, i.e. taking its ACTIVE_LOW status पूर्णांकo
 * account.
 *
 * Return 0 in हाल of success, अन्यथा an error code.
 */
पूर्णांक gpiod_direction_output(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	पूर्णांक ret;

	VALIDATE_DESC(desc);
	अगर (test_bit(FLAG_ACTIVE_LOW, &desc->flags))
		value = !value;
	अन्यथा
		value = !!value;

	/* GPIOs used क्रम enabled IRQs shall not be set as output */
	अगर (test_bit(FLAG_USED_AS_IRQ, &desc->flags) &&
	    test_bit(FLAG_IRQ_IS_ENABLED, &desc->flags)) अणु
		gpiod_err(desc,
			  "%s: tried to set a GPIO tied to an IRQ as output\n",
			  __func__);
		वापस -EIO;
	पूर्ण

	अगर (test_bit(FLAG_OPEN_DRAIN, &desc->flags)) अणु
		/* First see अगर we can enable खोलो drain in hardware */
		ret = gpio_set_config(desc, PIN_CONFIG_DRIVE_OPEN_DRAIN);
		अगर (!ret)
			जाओ set_output_value;
		/* Emulate खोलो drain by not actively driving the line high */
		अगर (value) अणु
			ret = gpiod_direction_input(desc);
			जाओ set_output_flag;
		पूर्ण
	पूर्ण
	अन्यथा अगर (test_bit(FLAG_OPEN_SOURCE, &desc->flags)) अणु
		ret = gpio_set_config(desc, PIN_CONFIG_DRIVE_OPEN_SOURCE);
		अगर (!ret)
			जाओ set_output_value;
		/* Emulate खोलो source by not actively driving the line low */
		अगर (!value) अणु
			ret = gpiod_direction_input(desc);
			जाओ set_output_flag;
		पूर्ण
	पूर्ण अन्यथा अणु
		gpio_set_config(desc, PIN_CONFIG_DRIVE_PUSH_PULL);
	पूर्ण

set_output_value:
	ret = gpio_set_bias(desc);
	अगर (ret)
		वापस ret;
	वापस gpiod_direction_output_raw_commit(desc, value);

set_output_flag:
	/*
	 * When emulating खोलो-source or खोलो-drain functionalities by not
	 * actively driving the line (setting mode to input) we still need to
	 * set the IS_OUT flag or otherwise we won't be able to set the line
	 * value anymore.
	 */
	अगर (ret == 0)
		set_bit(FLAG_IS_OUT, &desc->flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_direction_output);

/**
 * gpiod_set_config - sets @config क्रम a GPIO
 * @desc: descriptor of the GPIO क्रम which to set the configuration
 * @config: Same packed config क्रमmat as generic pinconf
 *
 * Returns:
 * 0 on success, %-ENOTSUPP अगर the controller करोesn't support setting the
 * configuration.
 */
पूर्णांक gpiod_set_config(काष्ठा gpio_desc *desc, अचिन्हित दीर्घ config)
अणु
	काष्ठा gpio_chip *gc;

	VALIDATE_DESC(desc);
	gc = desc->gdev->chip;

	वापस gpio_करो_set_config(gc, gpio_chip_hwgpio(desc), config);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_config);

/**
 * gpiod_set_debounce - sets @debounce समय क्रम a GPIO
 * @desc: descriptor of the GPIO क्रम which to set debounce समय
 * @debounce: debounce समय in microseconds
 *
 * Returns:
 * 0 on success, %-ENOTSUPP अगर the controller करोesn't support setting the
 * debounce समय.
 */
पूर्णांक gpiod_set_debounce(काष्ठा gpio_desc *desc, अचिन्हित पूर्णांक debounce)
अणु
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_DEBOUNCE, debounce);
	वापस gpiod_set_config(desc, config);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_debounce);

/**
 * gpiod_set_transitory - Lose or retain GPIO state on suspend or reset
 * @desc: descriptor of the GPIO क्रम which to configure persistence
 * @transitory: True to lose state on suspend or reset, false क्रम persistence
 *
 * Returns:
 * 0 on success, otherwise a negative error code.
 */
पूर्णांक gpiod_set_transitory(काष्ठा gpio_desc *desc, bool transitory)
अणु
	VALIDATE_DESC(desc);
	/*
	 * Handle FLAG_TRANSITORY first, enabling queries to gpiolib क्रम
	 * persistence state.
	 */
	assign_bit(FLAG_TRANSITORY, &desc->flags, transitory);

	/* If the driver supports it, set the persistence state now */
	वापस gpio_set_config_with_argument_optional(desc,
						      PIN_CONFIG_PERSIST_STATE,
						      !transitory);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_transitory);

/**
 * gpiod_is_active_low - test whether a GPIO is active-low or not
 * @desc: the gpio descriptor to test
 *
 * Returns 1 अगर the GPIO is active-low, 0 otherwise.
 */
पूर्णांक gpiod_is_active_low(स्थिर काष्ठा gpio_desc *desc)
अणु
	VALIDATE_DESC(desc);
	वापस test_bit(FLAG_ACTIVE_LOW, &desc->flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_is_active_low);

/**
 * gpiod_toggle_active_low - toggle whether a GPIO is active-low or not
 * @desc: the gpio descriptor to change
 */
व्योम gpiod_toggle_active_low(काष्ठा gpio_desc *desc)
अणु
	VALIDATE_DESC_VOID(desc);
	change_bit(FLAG_ACTIVE_LOW, &desc->flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_toggle_active_low);

/* I/O calls are only valid after configuration completed; the relevant
 * "is this a valid GPIO" error checks should alपढ़ोy have been करोne.
 *
 * "Get" operations are often inlinable as पढ़ोing a pin value रेजिस्टर,
 * and masking the relevant bit in that रेजिस्टर.
 *
 * When "set" operations are inlinable, they involve writing that mask to
 * one रेजिस्टर to set a low value, or a dअगरferent रेजिस्टर to set it high.
 * Otherwise locking is needed, so there may be little value to inlining.
 *
 *------------------------------------------------------------------------
 *
 * IMPORTANT!!!  The hot paths -- get/set value -- assume that callers
 * have requested the GPIO.  That can include implicit requesting by
 * a direction setting call.  Marking a gpio as requested locks its chip
 * in memory, guaranteeing that these table lookups need no more locking
 * and that gpiochip_हटाओ() will fail.
 *
 * REVISIT when debugging, consider adding some instrumentation to ensure
 * that the GPIO was actually requested.
 */

अटल पूर्णांक gpiod_get_raw_value_commit(स्थिर काष्ठा gpio_desc *desc)
अणु
	काष्ठा gpio_chip	*gc;
	पूर्णांक offset;
	पूर्णांक value;

	gc = desc->gdev->chip;
	offset = gpio_chip_hwgpio(desc);
	value = gc->get ? gc->get(gc, offset) : -EIO;
	value = value < 0 ? value : !!value;
	trace_gpio_value(desc_to_gpio(desc), 1, value);
	वापस value;
पूर्ण

अटल पूर्णांक gpio_chip_get_multiple(काष्ठा gpio_chip *gc,
				  अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	अगर (gc->get_multiple) अणु
		वापस gc->get_multiple(gc, mask, bits);
	पूर्ण अन्यथा अगर (gc->get) अणु
		पूर्णांक i, value;

		क्रम_each_set_bit(i, mask, gc->ngpio) अणु
			value = gc->get(gc, i);
			अगर (value < 0)
				वापस value;
			__assign_bit(i, bits, value);
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

पूर्णांक gpiod_get_array_value_complex(bool raw, bool can_sleep,
				  अचिन्हित पूर्णांक array_size,
				  काष्ठा gpio_desc **desc_array,
				  काष्ठा gpio_array *array_info,
				  अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	पूर्णांक ret, i = 0;

	/*
	 * Validate array_info against desc_array and its size.
	 * It should immediately follow desc_array अगर both
	 * have been obtained from the same gpiod_get_array() call.
	 */
	अगर (array_info && array_info->desc == desc_array &&
	    array_size <= array_info->size &&
	    (व्योम *)array_info == desc_array + array_info->size) अणु
		अगर (!can_sleep)
			WARN_ON(array_info->chip->can_sleep);

		ret = gpio_chip_get_multiple(array_info->chip,
					     array_info->get_mask,
					     value_biपंचांगap);
		अगर (ret)
			वापस ret;

		अगर (!raw && !biपंचांगap_empty(array_info->invert_mask, array_size))
			biपंचांगap_xor(value_biपंचांगap, value_biपंचांगap,
				   array_info->invert_mask, array_size);

		i = find_first_zero_bit(array_info->get_mask, array_size);
		अगर (i == array_size)
			वापस 0;
	पूर्ण अन्यथा अणु
		array_info = शून्य;
	पूर्ण

	जबतक (i < array_size) अणु
		काष्ठा gpio_chip *gc = desc_array[i]->gdev->chip;
		अचिन्हित दीर्घ fastpath[2 * BITS_TO_LONGS(FASTPATH_NGPIO)];
		अचिन्हित दीर्घ *mask, *bits;
		पूर्णांक first, j;

		अगर (likely(gc->ngpio <= FASTPATH_NGPIO)) अणु
			mask = fastpath;
		पूर्ण अन्यथा अणु
			mask = kदो_स्मृति_array(2 * BITS_TO_LONGS(gc->ngpio),
					   माप(*mask),
					   can_sleep ? GFP_KERNEL : GFP_ATOMIC);
			अगर (!mask)
				वापस -ENOMEM;
		पूर्ण

		bits = mask + BITS_TO_LONGS(gc->ngpio);
		biपंचांगap_zero(mask, gc->ngpio);

		अगर (!can_sleep)
			WARN_ON(gc->can_sleep);

		/* collect all inमाला_दो beदीर्घing to the same chip */
		first = i;
		करो अणु
			स्थिर काष्ठा gpio_desc *desc = desc_array[i];
			पूर्णांक hwgpio = gpio_chip_hwgpio(desc);

			__set_bit(hwgpio, mask);
			i++;

			अगर (array_info)
				i = find_next_zero_bit(array_info->get_mask,
						       array_size, i);
		पूर्ण जबतक ((i < array_size) &&
			 (desc_array[i]->gdev->chip == gc));

		ret = gpio_chip_get_multiple(gc, mask, bits);
		अगर (ret) अणु
			अगर (mask != fastpath)
				kमुक्त(mask);
			वापस ret;
		पूर्ण

		क्रम (j = first; j < i; ) अणु
			स्थिर काष्ठा gpio_desc *desc = desc_array[j];
			पूर्णांक hwgpio = gpio_chip_hwgpio(desc);
			पूर्णांक value = test_bit(hwgpio, bits);

			अगर (!raw && test_bit(FLAG_ACTIVE_LOW, &desc->flags))
				value = !value;
			__assign_bit(j, value_biपंचांगap, value);
			trace_gpio_value(desc_to_gpio(desc), 1, value);
			j++;

			अगर (array_info)
				j = find_next_zero_bit(array_info->get_mask, i,
						       j);
		पूर्ण

		अगर (mask != fastpath)
			kमुक्त(mask);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * gpiod_get_raw_value() - वापस a gpio's raw value
 * @desc: gpio whose value will be वापसed
 *
 * Return the GPIO's raw value, i.e. the value of the physical line disregarding
 * its ACTIVE_LOW status, or negative त्रुटि_सं on failure.
 *
 * This function can be called from contexts where we cannot sleep, and will
 * complain अगर the GPIO chip functions potentially sleep.
 */
पूर्णांक gpiod_get_raw_value(स्थिर काष्ठा gpio_desc *desc)
अणु
	VALIDATE_DESC(desc);
	/* Should be using gpiod_get_raw_value_cansleep() */
	WARN_ON(desc->gdev->chip->can_sleep);
	वापस gpiod_get_raw_value_commit(desc);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_raw_value);

/**
 * gpiod_get_value() - वापस a gpio's value
 * @desc: gpio whose value will be वापसed
 *
 * Return the GPIO's logical value, i.e. taking the ACTIVE_LOW status पूर्णांकo
 * account, or negative त्रुटि_सं on failure.
 *
 * This function can be called from contexts where we cannot sleep, and will
 * complain अगर the GPIO chip functions potentially sleep.
 */
पूर्णांक gpiod_get_value(स्थिर काष्ठा gpio_desc *desc)
अणु
	पूर्णांक value;

	VALIDATE_DESC(desc);
	/* Should be using gpiod_get_value_cansleep() */
	WARN_ON(desc->gdev->chip->can_sleep);

	value = gpiod_get_raw_value_commit(desc);
	अगर (value < 0)
		वापस value;

	अगर (test_bit(FLAG_ACTIVE_LOW, &desc->flags))
		value = !value;

	वापस value;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_value);

/**
 * gpiod_get_raw_array_value() - पढ़ो raw values from an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be पढ़ो
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap to store the पढ़ो values
 *
 * Read the raw values of the GPIOs, i.e. the values of the physical lines
 * without regard क्रम their ACTIVE_LOW status.  Return 0 in हाल of success,
 * अन्यथा an error code.
 *
 * This function can be called from contexts where we cannot sleep,
 * and it will complain अगर the GPIO chip functions potentially sleep.
 */
पूर्णांक gpiod_get_raw_array_value(अचिन्हित पूर्णांक array_size,
			      काष्ठा gpio_desc **desc_array,
			      काष्ठा gpio_array *array_info,
			      अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_get_array_value_complex(true, false, array_size,
					     desc_array, array_info,
					     value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_raw_array_value);

/**
 * gpiod_get_array_value() - पढ़ो values from an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be पढ़ो
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap to store the पढ़ो values
 *
 * Read the logical values of the GPIOs, i.e. taking their ACTIVE_LOW status
 * पूर्णांकo account.  Return 0 in हाल of success, अन्यथा an error code.
 *
 * This function can be called from contexts where we cannot sleep,
 * and it will complain अगर the GPIO chip functions potentially sleep.
 */
पूर्णांक gpiod_get_array_value(अचिन्हित पूर्णांक array_size,
			  काष्ठा gpio_desc **desc_array,
			  काष्ठा gpio_array *array_info,
			  अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_get_array_value_complex(false, false, array_size,
					     desc_array, array_info,
					     value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_array_value);

/*
 *  gpio_set_खोलो_drain_value_commit() - Set the खोलो drain gpio's value.
 * @desc: gpio descriptor whose state need to be set.
 * @value: Non-zero क्रम setting it HIGH otherwise it will set to LOW.
 */
अटल व्योम gpio_set_खोलो_drain_value_commit(काष्ठा gpio_desc *desc, bool value)
अणु
	पूर्णांक ret = 0;
	काष्ठा gpio_chip *gc = desc->gdev->chip;
	पूर्णांक offset = gpio_chip_hwgpio(desc);

	अगर (value) अणु
		ret = gc->direction_input(gc, offset);
	पूर्ण अन्यथा अणु
		ret = gc->direction_output(gc, offset, 0);
		अगर (!ret)
			set_bit(FLAG_IS_OUT, &desc->flags);
	पूर्ण
	trace_gpio_direction(desc_to_gpio(desc), value, ret);
	अगर (ret < 0)
		gpiod_err(desc,
			  "%s: Error in set_value for open drain err %d\n",
			  __func__, ret);
पूर्ण

/*
 *  _gpio_set_खोलो_source_value() - Set the खोलो source gpio's value.
 * @desc: gpio descriptor whose state need to be set.
 * @value: Non-zero क्रम setting it HIGH otherwise it will set to LOW.
 */
अटल व्योम gpio_set_खोलो_source_value_commit(काष्ठा gpio_desc *desc, bool value)
अणु
	पूर्णांक ret = 0;
	काष्ठा gpio_chip *gc = desc->gdev->chip;
	पूर्णांक offset = gpio_chip_hwgpio(desc);

	अगर (value) अणु
		ret = gc->direction_output(gc, offset, 1);
		अगर (!ret)
			set_bit(FLAG_IS_OUT, &desc->flags);
	पूर्ण अन्यथा अणु
		ret = gc->direction_input(gc, offset);
	पूर्ण
	trace_gpio_direction(desc_to_gpio(desc), !value, ret);
	अगर (ret < 0)
		gpiod_err(desc,
			  "%s: Error in set_value for open source err %d\n",
			  __func__, ret);
पूर्ण

अटल व्योम gpiod_set_raw_value_commit(काष्ठा gpio_desc *desc, bool value)
अणु
	काष्ठा gpio_chip	*gc;

	gc = desc->gdev->chip;
	trace_gpio_value(desc_to_gpio(desc), 0, value);
	gc->set(gc, gpio_chip_hwgpio(desc), value);
पूर्ण

/*
 * set multiple outमाला_दो on the same chip;
 * use the chip's set_multiple function अगर available;
 * otherwise set the outमाला_दो sequentially;
 * @chip: the GPIO chip we operate on
 * @mask: bit mask array; one bit per output; BITS_PER_LONG bits per word
 *        defines which outमाला_दो are to be changed
 * @bits: bit value array; one bit per output; BITS_PER_LONG bits per word
 *        defines the values the outमाला_दो specअगरied by mask are to be set to
 */
अटल व्योम gpio_chip_set_multiple(काष्ठा gpio_chip *gc,
				   अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	अगर (gc->set_multiple) अणु
		gc->set_multiple(gc, mask, bits);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i;

		/* set outमाला_दो अगर the corresponding mask bit is set */
		क्रम_each_set_bit(i, mask, gc->ngpio)
			gc->set(gc, i, test_bit(i, bits));
	पूर्ण
पूर्ण

पूर्णांक gpiod_set_array_value_complex(bool raw, bool can_sleep,
				  अचिन्हित पूर्णांक array_size,
				  काष्ठा gpio_desc **desc_array,
				  काष्ठा gpio_array *array_info,
				  अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	पूर्णांक i = 0;

	/*
	 * Validate array_info against desc_array and its size.
	 * It should immediately follow desc_array अगर both
	 * have been obtained from the same gpiod_get_array() call.
	 */
	अगर (array_info && array_info->desc == desc_array &&
	    array_size <= array_info->size &&
	    (व्योम *)array_info == desc_array + array_info->size) अणु
		अगर (!can_sleep)
			WARN_ON(array_info->chip->can_sleep);

		अगर (!raw && !biपंचांगap_empty(array_info->invert_mask, array_size))
			biपंचांगap_xor(value_biपंचांगap, value_biपंचांगap,
				   array_info->invert_mask, array_size);

		gpio_chip_set_multiple(array_info->chip, array_info->set_mask,
				       value_biपंचांगap);

		i = find_first_zero_bit(array_info->set_mask, array_size);
		अगर (i == array_size)
			वापस 0;
	पूर्ण अन्यथा अणु
		array_info = शून्य;
	पूर्ण

	जबतक (i < array_size) अणु
		काष्ठा gpio_chip *gc = desc_array[i]->gdev->chip;
		अचिन्हित दीर्घ fastpath[2 * BITS_TO_LONGS(FASTPATH_NGPIO)];
		अचिन्हित दीर्घ *mask, *bits;
		पूर्णांक count = 0;

		अगर (likely(gc->ngpio <= FASTPATH_NGPIO)) अणु
			mask = fastpath;
		पूर्ण अन्यथा अणु
			mask = kदो_स्मृति_array(2 * BITS_TO_LONGS(gc->ngpio),
					   माप(*mask),
					   can_sleep ? GFP_KERNEL : GFP_ATOMIC);
			अगर (!mask)
				वापस -ENOMEM;
		पूर्ण

		bits = mask + BITS_TO_LONGS(gc->ngpio);
		biपंचांगap_zero(mask, gc->ngpio);

		अगर (!can_sleep)
			WARN_ON(gc->can_sleep);

		करो अणु
			काष्ठा gpio_desc *desc = desc_array[i];
			पूर्णांक hwgpio = gpio_chip_hwgpio(desc);
			पूर्णांक value = test_bit(i, value_biपंचांगap);

			/*
			 * Pins applicable क्रम fast input but not क्रम
			 * fast output processing may have been alपढ़ोy
			 * inverted inside the fast path, skip them.
			 */
			अगर (!raw && !(array_info &&
			    test_bit(i, array_info->invert_mask)) &&
			    test_bit(FLAG_ACTIVE_LOW, &desc->flags))
				value = !value;
			trace_gpio_value(desc_to_gpio(desc), 0, value);
			/*
			 * collect all normal outमाला_दो beदीर्घing to the same chip
			 * खोलो drain and खोलो source outमाला_दो are set inभागidually
			 */
			अगर (test_bit(FLAG_OPEN_DRAIN, &desc->flags) && !raw) अणु
				gpio_set_खोलो_drain_value_commit(desc, value);
			पूर्ण अन्यथा अगर (test_bit(FLAG_OPEN_SOURCE, &desc->flags) && !raw) अणु
				gpio_set_खोलो_source_value_commit(desc, value);
			पूर्ण अन्यथा अणु
				__set_bit(hwgpio, mask);
				__assign_bit(hwgpio, bits, value);
				count++;
			पूर्ण
			i++;

			अगर (array_info)
				i = find_next_zero_bit(array_info->set_mask,
						       array_size, i);
		पूर्ण जबतक ((i < array_size) &&
			 (desc_array[i]->gdev->chip == gc));
		/* push collected bits to outमाला_दो */
		अगर (count != 0)
			gpio_chip_set_multiple(gc, mask, bits);

		अगर (mask != fastpath)
			kमुक्त(mask);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * gpiod_set_raw_value() - assign a gpio's raw value
 * @desc: gpio whose value will be asचिन्हित
 * @value: value to assign
 *
 * Set the raw value of the GPIO, i.e. the value of its physical line without
 * regard क्रम its ACTIVE_LOW status.
 *
 * This function can be called from contexts where we cannot sleep, and will
 * complain अगर the GPIO chip functions potentially sleep.
 */
व्योम gpiod_set_raw_value(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	VALIDATE_DESC_VOID(desc);
	/* Should be using gpiod_set_raw_value_cansleep() */
	WARN_ON(desc->gdev->chip->can_sleep);
	gpiod_set_raw_value_commit(desc, value);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_raw_value);

/**
 * gpiod_set_value_nocheck() - set a GPIO line value without checking
 * @desc: the descriptor to set the value on
 * @value: value to set
 *
 * This sets the value of a GPIO line backing a descriptor, applying
 * dअगरferent semantic quirks like active low and खोलो drain/source
 * handling.
 */
अटल व्योम gpiod_set_value_nocheck(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	अगर (test_bit(FLAG_ACTIVE_LOW, &desc->flags))
		value = !value;
	अगर (test_bit(FLAG_OPEN_DRAIN, &desc->flags))
		gpio_set_खोलो_drain_value_commit(desc, value);
	अन्यथा अगर (test_bit(FLAG_OPEN_SOURCE, &desc->flags))
		gpio_set_खोलो_source_value_commit(desc, value);
	अन्यथा
		gpiod_set_raw_value_commit(desc, value);
पूर्ण

/**
 * gpiod_set_value() - assign a gpio's value
 * @desc: gpio whose value will be asचिन्हित
 * @value: value to assign
 *
 * Set the logical value of the GPIO, i.e. taking its ACTIVE_LOW,
 * OPEN_DRAIN and OPEN_SOURCE flags पूर्णांकo account.
 *
 * This function can be called from contexts where we cannot sleep, and will
 * complain अगर the GPIO chip functions potentially sleep.
 */
व्योम gpiod_set_value(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	VALIDATE_DESC_VOID(desc);
	/* Should be using gpiod_set_value_cansleep() */
	WARN_ON(desc->gdev->chip->can_sleep);
	gpiod_set_value_nocheck(desc, value);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_value);

/**
 * gpiod_set_raw_array_value() - assign values to an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be asचिन्हित
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap of values to assign
 *
 * Set the raw values of the GPIOs, i.e. the values of the physical lines
 * without regard क्रम their ACTIVE_LOW status.
 *
 * This function can be called from contexts where we cannot sleep, and will
 * complain अगर the GPIO chip functions potentially sleep.
 */
पूर्णांक gpiod_set_raw_array_value(अचिन्हित पूर्णांक array_size,
			      काष्ठा gpio_desc **desc_array,
			      काष्ठा gpio_array *array_info,
			      अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_set_array_value_complex(true, false, array_size,
					desc_array, array_info, value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_raw_array_value);

/**
 * gpiod_set_array_value() - assign values to an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be asचिन्हित
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap of values to assign
 *
 * Set the logical values of the GPIOs, i.e. taking their ACTIVE_LOW status
 * पूर्णांकo account.
 *
 * This function can be called from contexts where we cannot sleep, and will
 * complain अगर the GPIO chip functions potentially sleep.
 */
पूर्णांक gpiod_set_array_value(अचिन्हित पूर्णांक array_size,
			  काष्ठा gpio_desc **desc_array,
			  काष्ठा gpio_array *array_info,
			  अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_set_array_value_complex(false, false, array_size,
					     desc_array, array_info,
					     value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_array_value);

/**
 * gpiod_cansleep() - report whether gpio value access may sleep
 * @desc: gpio to check
 *
 */
पूर्णांक gpiod_cansleep(स्थिर काष्ठा gpio_desc *desc)
अणु
	VALIDATE_DESC(desc);
	वापस desc->gdev->chip->can_sleep;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_cansleep);

/**
 * gpiod_set_consumer_name() - set the consumer name क्रम the descriptor
 * @desc: gpio to set the consumer name on
 * @name: the new consumer name
 */
पूर्णांक gpiod_set_consumer_name(काष्ठा gpio_desc *desc, स्थिर अक्षर *name)
अणु
	VALIDATE_DESC(desc);
	अगर (name) अणु
		name = kstrdup_स्थिर(name, GFP_KERNEL);
		अगर (!name)
			वापस -ENOMEM;
	पूर्ण

	kमुक्त_स्थिर(desc->label);
	desc_set_label(desc, name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_consumer_name);

/**
 * gpiod_to_irq() - वापस the IRQ corresponding to a GPIO
 * @desc: gpio whose IRQ will be वापसed (alपढ़ोy requested)
 *
 * Return the IRQ corresponding to the passed GPIO, or an error code in हाल of
 * error.
 */
पूर्णांक gpiod_to_irq(स्थिर काष्ठा gpio_desc *desc)
अणु
	काष्ठा gpio_chip *gc;
	पूर्णांक offset;

	/*
	 * Cannot VALIDATE_DESC() here as gpiod_to_irq() consumer semantics
	 * requires this function to not वापस zero on an invalid descriptor
	 * but rather a negative error number.
	 */
	अगर (!desc || IS_ERR(desc) || !desc->gdev || !desc->gdev->chip)
		वापस -EINVAL;

	gc = desc->gdev->chip;
	offset = gpio_chip_hwgpio(desc);
	अगर (gc->to_irq) अणु
		पूर्णांक retirq = gc->to_irq(gc, offset);

		/* Zero means NO_IRQ */
		अगर (!retirq)
			वापस -ENXIO;

		वापस retirq;
	पूर्ण
	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_to_irq);

/**
 * gpiochip_lock_as_irq() - lock a GPIO to be used as IRQ
 * @gc: the chip the GPIO to lock beदीर्घs to
 * @offset: the offset of the GPIO to lock as IRQ
 *
 * This is used directly by GPIO drivers that want to lock करोwn
 * a certain GPIO line to be used क्रम IRQs.
 */
पूर्णांक gpiochip_lock_as_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_desc *desc;

	desc = gpiochip_get_desc(gc, offset);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	/*
	 * If it's fast: flush the direction setting अगर something changed
	 * behind our back
	 */
	अगर (!gc->can_sleep && gc->get_direction) अणु
		पूर्णांक dir = gpiod_get_direction(desc);

		अगर (dir < 0) अणु
			chip_err(gc, "%s: cannot get GPIO direction\n",
				 __func__);
			वापस dir;
		पूर्ण
	पूर्ण

	/* To be valid क्रम IRQ the line needs to be input or खोलो drain */
	अगर (test_bit(FLAG_IS_OUT, &desc->flags) &&
	    !test_bit(FLAG_OPEN_DRAIN, &desc->flags)) अणु
		chip_err(gc,
			 "%s: tried to flag a GPIO set as output for IRQ\n",
			 __func__);
		वापस -EIO;
	पूर्ण

	set_bit(FLAG_USED_AS_IRQ, &desc->flags);
	set_bit(FLAG_IRQ_IS_ENABLED, &desc->flags);

	/*
	 * If the consumer has not set up a label (such as when the
	 * IRQ is referenced from .to_irq()) we set up a label here
	 * so it is clear this is used as an पूर्णांकerrupt.
	 */
	अगर (!desc->label)
		desc_set_label(desc, "interrupt");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_lock_as_irq);

/**
 * gpiochip_unlock_as_irq() - unlock a GPIO used as IRQ
 * @gc: the chip the GPIO to lock beदीर्घs to
 * @offset: the offset of the GPIO to lock as IRQ
 *
 * This is used directly by GPIO drivers that want to indicate
 * that a certain GPIO is no दीर्घer used exclusively क्रम IRQ.
 */
व्योम gpiochip_unlock_as_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_desc *desc;

	desc = gpiochip_get_desc(gc, offset);
	अगर (IS_ERR(desc))
		वापस;

	clear_bit(FLAG_USED_AS_IRQ, &desc->flags);
	clear_bit(FLAG_IRQ_IS_ENABLED, &desc->flags);

	/* If we only had this marking, erase it */
	अगर (desc->label && !म_भेद(desc->label, "interrupt"))
		desc_set_label(desc, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_unlock_as_irq);

व्योम gpiochip_disable_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_desc *desc = gpiochip_get_desc(gc, offset);

	अगर (!IS_ERR(desc) &&
	    !WARN_ON(!test_bit(FLAG_USED_AS_IRQ, &desc->flags)))
		clear_bit(FLAG_IRQ_IS_ENABLED, &desc->flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_disable_irq);

व्योम gpiochip_enable_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_desc *desc = gpiochip_get_desc(gc, offset);

	अगर (!IS_ERR(desc) &&
	    !WARN_ON(!test_bit(FLAG_USED_AS_IRQ, &desc->flags))) अणु
		/*
		 * We must not be output when using IRQ UNLESS we are
		 * खोलो drain.
		 */
		WARN_ON(test_bit(FLAG_IS_OUT, &desc->flags) &&
			!test_bit(FLAG_OPEN_DRAIN, &desc->flags));
		set_bit(FLAG_IRQ_IS_ENABLED, &desc->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_enable_irq);

bool gpiochip_line_is_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= gc->ngpio)
		वापस false;

	वापस test_bit(FLAG_USED_AS_IRQ, &gc->gpiodev->descs[offset].flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_line_is_irq);

पूर्णांक gpiochip_reqres_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;

	अगर (!try_module_get(gc->gpiodev->owner))
		वापस -ENODEV;

	ret = gpiochip_lock_as_irq(gc, offset);
	अगर (ret) अणु
		chip_err(gc, "unable to lock HW IRQ %u for IRQ\n", offset);
		module_put(gc->gpiodev->owner);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_reqres_irq);

व्योम gpiochip_relres_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	gpiochip_unlock_as_irq(gc, offset);
	module_put(gc->gpiodev->owner);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_relres_irq);

bool gpiochip_line_is_खोलो_drain(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= gc->ngpio)
		वापस false;

	वापस test_bit(FLAG_OPEN_DRAIN, &gc->gpiodev->descs[offset].flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_line_is_खोलो_drain);

bool gpiochip_line_is_खोलो_source(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= gc->ngpio)
		वापस false;

	वापस test_bit(FLAG_OPEN_SOURCE, &gc->gpiodev->descs[offset].flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_line_is_खोलो_source);

bool gpiochip_line_is_persistent(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= gc->ngpio)
		वापस false;

	वापस !test_bit(FLAG_TRANSITORY, &gc->gpiodev->descs[offset].flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiochip_line_is_persistent);

/**
 * gpiod_get_raw_value_cansleep() - वापस a gpio's raw value
 * @desc: gpio whose value will be वापसed
 *
 * Return the GPIO's raw value, i.e. the value of the physical line disregarding
 * its ACTIVE_LOW status, or negative त्रुटि_सं on failure.
 *
 * This function is to be called from contexts that can sleep.
 */
पूर्णांक gpiod_get_raw_value_cansleep(स्थिर काष्ठा gpio_desc *desc)
अणु
	might_sleep_अगर(extra_checks);
	VALIDATE_DESC(desc);
	वापस gpiod_get_raw_value_commit(desc);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_raw_value_cansleep);

/**
 * gpiod_get_value_cansleep() - वापस a gpio's value
 * @desc: gpio whose value will be वापसed
 *
 * Return the GPIO's logical value, i.e. taking the ACTIVE_LOW status पूर्णांकo
 * account, or negative त्रुटि_सं on failure.
 *
 * This function is to be called from contexts that can sleep.
 */
पूर्णांक gpiod_get_value_cansleep(स्थिर काष्ठा gpio_desc *desc)
अणु
	पूर्णांक value;

	might_sleep_अगर(extra_checks);
	VALIDATE_DESC(desc);
	value = gpiod_get_raw_value_commit(desc);
	अगर (value < 0)
		वापस value;

	अगर (test_bit(FLAG_ACTIVE_LOW, &desc->flags))
		value = !value;

	वापस value;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_value_cansleep);

/**
 * gpiod_get_raw_array_value_cansleep() - पढ़ो raw values from an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be पढ़ो
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap to store the पढ़ो values
 *
 * Read the raw values of the GPIOs, i.e. the values of the physical lines
 * without regard क्रम their ACTIVE_LOW status.  Return 0 in हाल of success,
 * अन्यथा an error code.
 *
 * This function is to be called from contexts that can sleep.
 */
पूर्णांक gpiod_get_raw_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				       काष्ठा gpio_desc **desc_array,
				       काष्ठा gpio_array *array_info,
				       अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	might_sleep_अगर(extra_checks);
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_get_array_value_complex(true, true, array_size,
					     desc_array, array_info,
					     value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_raw_array_value_cansleep);

/**
 * gpiod_get_array_value_cansleep() - पढ़ो values from an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be पढ़ो
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap to store the पढ़ो values
 *
 * Read the logical values of the GPIOs, i.e. taking their ACTIVE_LOW status
 * पूर्णांकo account.  Return 0 in हाल of success, अन्यथा an error code.
 *
 * This function is to be called from contexts that can sleep.
 */
पूर्णांक gpiod_get_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				   काष्ठा gpio_desc **desc_array,
				   काष्ठा gpio_array *array_info,
				   अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	might_sleep_अगर(extra_checks);
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_get_array_value_complex(false, true, array_size,
					     desc_array, array_info,
					     value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_array_value_cansleep);

/**
 * gpiod_set_raw_value_cansleep() - assign a gpio's raw value
 * @desc: gpio whose value will be asचिन्हित
 * @value: value to assign
 *
 * Set the raw value of the GPIO, i.e. the value of its physical line without
 * regard क्रम its ACTIVE_LOW status.
 *
 * This function is to be called from contexts that can sleep.
 */
व्योम gpiod_set_raw_value_cansleep(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	might_sleep_अगर(extra_checks);
	VALIDATE_DESC_VOID(desc);
	gpiod_set_raw_value_commit(desc, value);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_raw_value_cansleep);

/**
 * gpiod_set_value_cansleep() - assign a gpio's value
 * @desc: gpio whose value will be asचिन्हित
 * @value: value to assign
 *
 * Set the logical value of the GPIO, i.e. taking its ACTIVE_LOW status पूर्णांकo
 * account
 *
 * This function is to be called from contexts that can sleep.
 */
व्योम gpiod_set_value_cansleep(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	might_sleep_अगर(extra_checks);
	VALIDATE_DESC_VOID(desc);
	gpiod_set_value_nocheck(desc, value);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_value_cansleep);

/**
 * gpiod_set_raw_array_value_cansleep() - assign values to an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be asचिन्हित
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap of values to assign
 *
 * Set the raw values of the GPIOs, i.e. the values of the physical lines
 * without regard क्रम their ACTIVE_LOW status.
 *
 * This function is to be called from contexts that can sleep.
 */
पूर्णांक gpiod_set_raw_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				       काष्ठा gpio_desc **desc_array,
				       काष्ठा gpio_array *array_info,
				       अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	might_sleep_अगर(extra_checks);
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_set_array_value_complex(true, true, array_size, desc_array,
				      array_info, value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_raw_array_value_cansleep);

/**
 * gpiod_add_lookup_tables() - रेजिस्टर GPIO device consumers
 * @tables: list of tables of consumers to रेजिस्टर
 * @n: number of tables in the list
 */
व्योम gpiod_add_lookup_tables(काष्ठा gpiod_lookup_table **tables, माप_प्रकार n)
अणु
	अचिन्हित पूर्णांक i;

	mutex_lock(&gpio_lookup_lock);

	क्रम (i = 0; i < n; i++)
		list_add_tail(&tables[i]->list, &gpio_lookup_list);

	mutex_unlock(&gpio_lookup_lock);
पूर्ण

/**
 * gpiod_set_array_value_cansleep() - assign values to an array of GPIOs
 * @array_size: number of elements in the descriptor array / value biपंचांगap
 * @desc_array: array of GPIO descriptors whose values will be asचिन्हित
 * @array_info: inक्रमmation on applicability of fast biपंचांगap processing path
 * @value_biपंचांगap: biपंचांगap of values to assign
 *
 * Set the logical values of the GPIOs, i.e. taking their ACTIVE_LOW status
 * पूर्णांकo account.
 *
 * This function is to be called from contexts that can sleep.
 */
पूर्णांक gpiod_set_array_value_cansleep(अचिन्हित पूर्णांक array_size,
				   काष्ठा gpio_desc **desc_array,
				   काष्ठा gpio_array *array_info,
				   अचिन्हित दीर्घ *value_biपंचांगap)
अणु
	might_sleep_अगर(extra_checks);
	अगर (!desc_array)
		वापस -EINVAL;
	वापस gpiod_set_array_value_complex(false, true, array_size,
					     desc_array, array_info,
					     value_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_set_array_value_cansleep);

/**
 * gpiod_add_lookup_table() - रेजिस्टर GPIO device consumers
 * @table: table of consumers to रेजिस्टर
 */
व्योम gpiod_add_lookup_table(काष्ठा gpiod_lookup_table *table)
अणु
	mutex_lock(&gpio_lookup_lock);

	list_add_tail(&table->list, &gpio_lookup_list);

	mutex_unlock(&gpio_lookup_lock);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_add_lookup_table);

/**
 * gpiod_हटाओ_lookup_table() - unरेजिस्टर GPIO device consumers
 * @table: table of consumers to unरेजिस्टर
 */
व्योम gpiod_हटाओ_lookup_table(काष्ठा gpiod_lookup_table *table)
अणु
	/* Nothing to हटाओ */
	अगर (!table)
		वापस;

	mutex_lock(&gpio_lookup_lock);

	list_del(&table->list);

	mutex_unlock(&gpio_lookup_lock);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_हटाओ_lookup_table);

/**
 * gpiod_add_hogs() - रेजिस्टर a set of GPIO hogs from machine code
 * @hogs: table of gpio hog entries with a zeroed sentinel at the end
 */
व्योम gpiod_add_hogs(काष्ठा gpiod_hog *hogs)
अणु
	काष्ठा gpio_chip *gc;
	काष्ठा gpiod_hog *hog;

	mutex_lock(&gpio_machine_hogs_mutex);

	क्रम (hog = &hogs[0]; hog->chip_label; hog++) अणु
		list_add_tail(&hog->list, &gpio_machine_hogs);

		/*
		 * The chip may have been रेजिस्टरed earlier, so check अगर it
		 * exists and, अगर so, try to hog the line now.
		 */
		gc = find_chip_by_name(hog->chip_label);
		अगर (gc)
			gpiochip_machine_hog(gc, hog);
	पूर्ण

	mutex_unlock(&gpio_machine_hogs_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_add_hogs);

अटल काष्ठा gpiod_lookup_table *gpiod_find_lookup_table(काष्ठा device *dev)
अणु
	स्थिर अक्षर *dev_id = dev ? dev_name(dev) : शून्य;
	काष्ठा gpiod_lookup_table *table;

	mutex_lock(&gpio_lookup_lock);

	list_क्रम_each_entry(table, &gpio_lookup_list, list) अणु
		अगर (table->dev_id && dev_id) अणु
			/*
			 * Valid strings on both ends, must be identical to have
			 * a match
			 */
			अगर (!म_भेद(table->dev_id, dev_id))
				जाओ found;
		पूर्ण अन्यथा अणु
			/*
			 * One of the poपूर्णांकers is शून्य, so both must be to have
			 * a match
			 */
			अगर (dev_id == table->dev_id)
				जाओ found;
		पूर्ण
	पूर्ण
	table = शून्य;

found:
	mutex_unlock(&gpio_lookup_lock);
	वापस table;
पूर्ण

अटल काष्ठा gpio_desc *gpiod_find(काष्ठा device *dev, स्थिर अक्षर *con_id,
				    अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा gpio_desc *desc = ERR_PTR(-ENOENT);
	काष्ठा gpiod_lookup_table *table;
	काष्ठा gpiod_lookup *p;

	table = gpiod_find_lookup_table(dev);
	अगर (!table)
		वापस desc;

	क्रम (p = &table->table[0]; p->key; p++) अणु
		काष्ठा gpio_chip *gc;

		/* idx must always match exactly */
		अगर (p->idx != idx)
			जारी;

		/* If the lookup entry has a con_id, require exact match */
		अगर (p->con_id && (!con_id || म_भेद(p->con_id, con_id)))
			जारी;

		अगर (p->chip_hwnum == U16_MAX) अणु
			desc = gpio_name_to_desc(p->key);
			अगर (desc) अणु
				*flags = p->flags;
				वापस desc;
			पूर्ण

			dev_warn(dev, "cannot find GPIO line %s, deferring\n",
				 p->key);
			वापस ERR_PTR(-EPROBE_DEFER);
		पूर्ण

		gc = find_chip_by_name(p->key);

		अगर (!gc) अणु
			/*
			 * As the lookup table indicates a chip with
			 * p->key should exist, assume it may
			 * still appear later and let the पूर्णांकerested
			 * consumer be probed again or let the Deferred
			 * Probe infraकाष्ठाure handle the error.
			 */
			dev_warn(dev, "cannot find GPIO chip %s, deferring\n",
				 p->key);
			वापस ERR_PTR(-EPROBE_DEFER);
		पूर्ण

		अगर (gc->ngpio <= p->chip_hwnum) अणु
			dev_err(dev,
				"requested GPIO %u (%u) is out of range [0..%u] for chip %s\n",
				idx, p->chip_hwnum, gc->ngpio - 1,
				gc->label);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		desc = gpiochip_get_desc(gc, p->chip_hwnum);
		*flags = p->flags;

		वापस desc;
	पूर्ण

	वापस desc;
पूर्ण

अटल पूर्णांक platक्रमm_gpio_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	काष्ठा gpiod_lookup_table *table;
	काष्ठा gpiod_lookup *p;
	अचिन्हित पूर्णांक count = 0;

	table = gpiod_find_lookup_table(dev);
	अगर (!table)
		वापस -ENOENT;

	क्रम (p = &table->table[0]; p->key; p++) अणु
		अगर ((con_id && p->con_id && !म_भेद(con_id, p->con_id)) ||
		    (!con_id && !p->con_id))
			count++;
	पूर्ण
	अगर (!count)
		वापस -ENOENT;

	वापस count;
पूर्ण

/**
 * fwnode_gpiod_get_index - obtain a GPIO from firmware node
 * @fwnode:	handle of the firmware node
 * @con_id:	function within the GPIO consumer
 * @index:	index of the GPIO to obtain क्रम the consumer
 * @flags:	GPIO initialization flags
 * @label:	label to attach to the requested GPIO
 *
 * This function can be used क्रम drivers that get their configuration
 * from opaque firmware.
 *
 * The function properly finds the corresponding GPIO using whatever is the
 * underlying firmware पूर्णांकerface and then makes sure that the GPIO
 * descriptor is requested beक्रमe it is वापसed to the caller.
 *
 * Returns:
 * On successful request the GPIO pin is configured in accordance with
 * provided @flags.
 *
 * In हाल of error an ERR_PTR() is वापसed.
 */
काष्ठा gpio_desc *fwnode_gpiod_get_index(काष्ठा fwnode_handle *fwnode,
					 स्थिर अक्षर *con_id, पूर्णांक index,
					 क्रमागत gpiod_flags flags,
					 स्थिर अक्षर *label)
अणु
	काष्ठा gpio_desc *desc;
	अक्षर prop_name[32]; /* 32 is max size of property name */
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) अणु
		अगर (con_id)
			snम_लिखो(prop_name, माप(prop_name), "%s-%s",
					    con_id, gpio_suffixes[i]);
		अन्यथा
			snम_लिखो(prop_name, माप(prop_name), "%s",
					    gpio_suffixes[i]);

		desc = fwnode_get_named_gpiod(fwnode, prop_name, index, flags,
					      label);
		अगर (!gpiod_not_found(desc))
			अवरोध;
	पूर्ण

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_gpiod_get_index);

/**
 * gpiod_count - वापस the number of GPIOs associated with a device / function
 *		or -ENOENT अगर no GPIO has been asचिन्हित to the requested function
 * @dev:	GPIO consumer, can be शून्य क्रम प्रणाली-global GPIOs
 * @con_id:	function within the GPIO consumer
 */
पूर्णांक gpiod_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	स्थिर काष्ठा fwnode_handle *fwnode = dev ? dev_fwnode(dev) : शून्य;
	पूर्णांक count = -ENOENT;

	अगर (is_of_node(fwnode))
		count = of_gpio_get_count(dev, con_id);
	अन्यथा अगर (is_acpi_node(fwnode))
		count = acpi_gpio_count(dev, con_id);

	अगर (count < 0)
		count = platक्रमm_gpio_count(dev, con_id);

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_count);

/**
 * gpiod_get - obtain a GPIO क्रम a given GPIO function
 * @dev:	GPIO consumer, can be शून्य क्रम प्रणाली-global GPIOs
 * @con_id:	function within the GPIO consumer
 * @flags:	optional GPIO initialization flags
 *
 * Return the GPIO descriptor corresponding to the function con_id of device
 * dev, -ENOENT अगर no GPIO has been asचिन्हित to the requested function, or
 * another IS_ERR() code अगर an error occurred जबतक trying to acquire the GPIO.
 */
काष्ठा gpio_desc *__must_check gpiod_get(काष्ठा device *dev, स्थिर अक्षर *con_id,
					 क्रमागत gpiod_flags flags)
अणु
	वापस gpiod_get_index(dev, con_id, 0, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get);

/**
 * gpiod_get_optional - obtain an optional GPIO क्रम a given GPIO function
 * @dev: GPIO consumer, can be शून्य क्रम प्रणाली-global GPIOs
 * @con_id: function within the GPIO consumer
 * @flags: optional GPIO initialization flags
 *
 * This is equivalent to gpiod_get(), except that when no GPIO was asचिन्हित to
 * the requested function it will वापस शून्य. This is convenient क्रम drivers
 * that need to handle optional GPIOs.
 */
काष्ठा gpio_desc *__must_check gpiod_get_optional(काष्ठा device *dev,
						  स्थिर अक्षर *con_id,
						  क्रमागत gpiod_flags flags)
अणु
	वापस gpiod_get_index_optional(dev, con_id, 0, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_optional);


/**
 * gpiod_configure_flags - helper function to configure a given GPIO
 * @desc:	gpio whose value will be asचिन्हित
 * @con_id:	function within the GPIO consumer
 * @lflags:	biपंचांगask of gpio_lookup_flags GPIO_* values - वापसed from
 *		of_find_gpio() or of_get_gpio_hog()
 * @dflags:	gpiod_flags - optional GPIO initialization flags
 *
 * Return 0 on success, -ENOENT अगर no GPIO has been asचिन्हित to the
 * requested function and/or index, or another IS_ERR() code अगर an error
 * occurred जबतक trying to acquire the GPIO.
 */
पूर्णांक gpiod_configure_flags(काष्ठा gpio_desc *desc, स्थिर अक्षर *con_id,
		अचिन्हित दीर्घ lflags, क्रमागत gpiod_flags dflags)
अणु
	पूर्णांक ret;

	अगर (lflags & GPIO_ACTIVE_LOW)
		set_bit(FLAG_ACTIVE_LOW, &desc->flags);

	अगर (lflags & GPIO_OPEN_DRAIN)
		set_bit(FLAG_OPEN_DRAIN, &desc->flags);
	अन्यथा अगर (dflags & GPIOD_FLAGS_BIT_OPEN_DRAIN) अणु
		/*
		 * This enक्रमces खोलो drain mode from the consumer side.
		 * This is necessary क्रम some busses like I2C, but the lookup
		 * should *REALLY* have specअगरied them as खोलो drain in the
		 * first place, so prपूर्णांक a little warning here.
		 */
		set_bit(FLAG_OPEN_DRAIN, &desc->flags);
		gpiod_warn(desc,
			   "enforced open drain please flag it properly in DT/ACPI DSDT/board file\n");
	पूर्ण

	अगर (lflags & GPIO_OPEN_SOURCE)
		set_bit(FLAG_OPEN_SOURCE, &desc->flags);

	अगर ((lflags & GPIO_PULL_UP) && (lflags & GPIO_PULL_DOWN)) अणु
		gpiod_err(desc,
			  "both pull-up and pull-down enabled, invalid configuration\n");
		वापस -EINVAL;
	पूर्ण

	अगर (lflags & GPIO_PULL_UP)
		set_bit(FLAG_PULL_UP, &desc->flags);
	अन्यथा अगर (lflags & GPIO_PULL_DOWN)
		set_bit(FLAG_PULL_DOWN, &desc->flags);

	ret = gpiod_set_transitory(desc, (lflags & GPIO_TRANSITORY));
	अगर (ret < 0)
		वापस ret;

	/* No particular flag request, वापस here... */
	अगर (!(dflags & GPIOD_FLAGS_BIT_सूची_SET)) अणु
		gpiod_dbg(desc, "no flags found for %s\n", con_id);
		वापस 0;
	पूर्ण

	/* Process flags */
	अगर (dflags & GPIOD_FLAGS_BIT_सूची_OUT)
		ret = gpiod_direction_output(desc,
				!!(dflags & GPIOD_FLAGS_BIT_सूची_VAL));
	अन्यथा
		ret = gpiod_direction_input(desc);

	वापस ret;
पूर्ण

/**
 * gpiod_get_index - obtain a GPIO from a multi-index GPIO function
 * @dev:	GPIO consumer, can be शून्य क्रम प्रणाली-global GPIOs
 * @con_id:	function within the GPIO consumer
 * @idx:	index of the GPIO to obtain in the consumer
 * @flags:	optional GPIO initialization flags
 *
 * This variant of gpiod_get() allows to access GPIOs other than the first
 * defined one क्रम functions that define several GPIOs.
 *
 * Return a valid GPIO descriptor, -ENOENT अगर no GPIO has been asचिन्हित to the
 * requested function and/or index, or another IS_ERR() code अगर an error
 * occurred जबतक trying to acquire the GPIO.
 */
काष्ठा gpio_desc *__must_check gpiod_get_index(काष्ठा device *dev,
					       स्थिर अक्षर *con_id,
					       अचिन्हित पूर्णांक idx,
					       क्रमागत gpiod_flags flags)
अणु
	अचिन्हित दीर्घ lookupflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	काष्ठा gpio_desc *desc = शून्य;
	पूर्णांक ret;
	/* Maybe we have a device name, maybe not */
	स्थिर अक्षर *devname = dev ? dev_name(dev) : "?";
	स्थिर काष्ठा fwnode_handle *fwnode = dev ? dev_fwnode(dev) : शून्य;

	dev_dbg(dev, "GPIO lookup for consumer %s\n", con_id);

	/* Using device tree? */
	अगर (is_of_node(fwnode)) अणु
		dev_dbg(dev, "using device tree for GPIO lookup\n");
		desc = of_find_gpio(dev, con_id, idx, &lookupflags);
	पूर्ण अन्यथा अगर (is_acpi_node(fwnode)) अणु
		dev_dbg(dev, "using ACPI for GPIO lookup\n");
		desc = acpi_find_gpio(dev, con_id, idx, &flags, &lookupflags);
	पूर्ण

	/*
	 * Either we are not using DT or ACPI, or their lookup did not वापस
	 * a result. In that हाल, use platक्रमm lookup as a fallback.
	 */
	अगर (!desc || gpiod_not_found(desc)) अणु
		dev_dbg(dev, "using lookup tables for GPIO lookup\n");
		desc = gpiod_find(dev, con_id, idx, &lookupflags);
	पूर्ण

	अगर (IS_ERR(desc)) अणु
		dev_dbg(dev, "No GPIO consumer %s found\n", con_id);
		वापस desc;
	पूर्ण

	/*
	 * If a connection label was passed use that, अन्यथा attempt to use
	 * the device name as label
	 */
	ret = gpiod_request(desc, con_id ? con_id : devname);
	अगर (ret) अणु
		अगर (ret == -EBUSY && flags & GPIOD_FLAGS_BIT_NONEXCLUSIVE) अणु
			/*
			 * This happens when there are several consumers क्रम
			 * the same GPIO line: we just वापस here without
			 * further initialization. It is a bit अगर a hack.
			 * This is necessary to support fixed regulators.
			 *
			 * FIXME: Make this more sane and safe.
			 */
			dev_info(dev, "nonexclusive access to GPIO for %s\n",
				 con_id ? con_id : devname);
			वापस desc;
		पूर्ण अन्यथा अणु
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	ret = gpiod_configure_flags(desc, con_id, lookupflags, flags);
	अगर (ret < 0) अणु
		dev_dbg(dev, "setup of GPIO %s failed\n", con_id);
		gpiod_put(desc);
		वापस ERR_PTR(ret);
	पूर्ण

	blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
				     GPIOLINE_CHANGED_REQUESTED, desc);

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_index);

/**
 * fwnode_get_named_gpiod - obtain a GPIO from firmware node
 * @fwnode:	handle of the firmware node
 * @propname:	name of the firmware property representing the GPIO
 * @index:	index of the GPIO to obtain क्रम the consumer
 * @dflags:	GPIO initialization flags
 * @label:	label to attach to the requested GPIO
 *
 * This function can be used क्रम drivers that get their configuration
 * from opaque firmware.
 *
 * The function properly finds the corresponding GPIO using whatever is the
 * underlying firmware पूर्णांकerface and then makes sure that the GPIO
 * descriptor is requested beक्रमe it is वापसed to the caller.
 *
 * Returns:
 * On successful request the GPIO pin is configured in accordance with
 * provided @dflags.
 *
 * In हाल of error an ERR_PTR() is वापसed.
 */
काष्ठा gpio_desc *fwnode_get_named_gpiod(काष्ठा fwnode_handle *fwnode,
					 स्थिर अक्षर *propname, पूर्णांक index,
					 क्रमागत gpiod_flags dflags,
					 स्थिर अक्षर *label)
अणु
	अचिन्हित दीर्घ lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	काष्ठा gpio_desc *desc = ERR_PTR(-ENODEV);
	पूर्णांक ret;

	अगर (is_of_node(fwnode)) अणु
		desc = gpiod_get_from_of_node(to_of_node(fwnode),
					      propname, index,
					      dflags,
					      label);
		वापस desc;
	पूर्ण अन्यथा अगर (is_acpi_node(fwnode)) अणु
		काष्ठा acpi_gpio_info info;

		desc = acpi_node_get_gpiod(fwnode, propname, index, &info);
		अगर (IS_ERR(desc))
			वापस desc;

		acpi_gpio_update_gpiod_flags(&dflags, &info);
		acpi_gpio_update_gpiod_lookup_flags(&lflags, &info);
	पूर्ण अन्यथा
		वापस ERR_PTR(-EINVAL);

	/* Currently only ACPI takes this path */
	ret = gpiod_request(desc, label);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = gpiod_configure_flags(desc, propname, lflags, dflags);
	अगर (ret < 0) अणु
		gpiod_put(desc);
		वापस ERR_PTR(ret);
	पूर्ण

	blocking_notअगरier_call_chain(&desc->gdev->notअगरier,
				     GPIOLINE_CHANGED_REQUESTED, desc);

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_get_named_gpiod);

/**
 * gpiod_get_index_optional - obtain an optional GPIO from a multi-index GPIO
 *                            function
 * @dev: GPIO consumer, can be शून्य क्रम प्रणाली-global GPIOs
 * @con_id: function within the GPIO consumer
 * @index: index of the GPIO to obtain in the consumer
 * @flags: optional GPIO initialization flags
 *
 * This is equivalent to gpiod_get_index(), except that when no GPIO with the
 * specअगरied index was asचिन्हित to the requested function it will वापस शून्य.
 * This is convenient क्रम drivers that need to handle optional GPIOs.
 */
काष्ठा gpio_desc *__must_check gpiod_get_index_optional(काष्ठा device *dev,
							स्थिर अक्षर *con_id,
							अचिन्हित पूर्णांक index,
							क्रमागत gpiod_flags flags)
अणु
	काष्ठा gpio_desc *desc;

	desc = gpiod_get_index(dev, con_id, index, flags);
	अगर (gpiod_not_found(desc))
		वापस शून्य;

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_index_optional);

/**
 * gpiod_hog - Hog the specअगरied GPIO desc given the provided flags
 * @desc:	gpio whose value will be asचिन्हित
 * @name:	gpio line name
 * @lflags:	biपंचांगask of gpio_lookup_flags GPIO_* values - वापसed from
 *		of_find_gpio() or of_get_gpio_hog()
 * @dflags:	gpiod_flags - optional GPIO initialization flags
 */
पूर्णांक gpiod_hog(काष्ठा gpio_desc *desc, स्थिर अक्षर *name,
	      अचिन्हित दीर्घ lflags, क्रमागत gpiod_flags dflags)
अणु
	काष्ठा gpio_chip *gc;
	काष्ठा gpio_desc *local_desc;
	पूर्णांक hwnum;
	पूर्णांक ret;

	gc = gpiod_to_chip(desc);
	hwnum = gpio_chip_hwgpio(desc);

	local_desc = gpiochip_request_own_desc(gc, hwnum, name,
					       lflags, dflags);
	अगर (IS_ERR(local_desc)) अणु
		ret = PTR_ERR(local_desc);
		pr_err("requesting hog GPIO %s (chip %s, offset %d) failed, %d\n",
		       name, gc->label, hwnum, ret);
		वापस ret;
	पूर्ण

	/* Mark GPIO as hogged so it can be identअगरied and हटाओd later */
	set_bit(FLAG_IS_HOGGED, &desc->flags);

	gpiod_info(desc, "hogged as %s%s\n",
		(dflags & GPIOD_FLAGS_BIT_सूची_OUT) ? "output" : "input",
		(dflags & GPIOD_FLAGS_BIT_सूची_OUT) ?
		  (dflags & GPIOD_FLAGS_BIT_सूची_VAL) ? "/high" : "/low" : "");

	वापस 0;
पूर्ण

/**
 * gpiochip_मुक्त_hogs - Scan gpio-controller chip and release GPIO hog
 * @gc:	gpio chip to act on
 */
अटल व्योम gpiochip_मुक्त_hogs(काष्ठा gpio_chip *gc)
अणु
	पूर्णांक id;

	क्रम (id = 0; id < gc->ngpio; id++) अणु
		अगर (test_bit(FLAG_IS_HOGGED, &gc->gpiodev->descs[id].flags))
			gpiochip_मुक्त_own_desc(&gc->gpiodev->descs[id]);
	पूर्ण
पूर्ण

/**
 * gpiod_get_array - obtain multiple GPIOs from a multi-index GPIO function
 * @dev:	GPIO consumer, can be शून्य क्रम प्रणाली-global GPIOs
 * @con_id:	function within the GPIO consumer
 * @flags:	optional GPIO initialization flags
 *
 * This function acquires all the GPIOs defined under a given function.
 *
 * Return a काष्ठा gpio_descs containing an array of descriptors, -ENOENT अगर
 * no GPIO has been asचिन्हित to the requested function, or another IS_ERR()
 * code अगर an error occurred जबतक trying to acquire the GPIOs.
 */
काष्ठा gpio_descs *__must_check gpiod_get_array(काष्ठा device *dev,
						स्थिर अक्षर *con_id,
						क्रमागत gpiod_flags flags)
अणु
	काष्ठा gpio_desc *desc;
	काष्ठा gpio_descs *descs;
	काष्ठा gpio_array *array_info = शून्य;
	काष्ठा gpio_chip *gc;
	पूर्णांक count, biपंचांगap_size;

	count = gpiod_count(dev, con_id);
	अगर (count < 0)
		वापस ERR_PTR(count);

	descs = kzalloc(काष्ठा_size(descs, desc, count), GFP_KERNEL);
	अगर (!descs)
		वापस ERR_PTR(-ENOMEM);

	क्रम (descs->ndescs = 0; descs->ndescs < count; ) अणु
		desc = gpiod_get_index(dev, con_id, descs->ndescs, flags);
		अगर (IS_ERR(desc)) अणु
			gpiod_put_array(descs);
			वापस ERR_CAST(desc);
		पूर्ण

		descs->desc[descs->ndescs] = desc;

		gc = gpiod_to_chip(desc);
		/*
		 * If pin hardware number of array member 0 is also 0, select
		 * its chip as a candidate क्रम fast biपंचांगap processing path.
		 */
		अगर (descs->ndescs == 0 && gpio_chip_hwgpio(desc) == 0) अणु
			काष्ठा gpio_descs *array;

			biपंचांगap_size = BITS_TO_LONGS(gc->ngpio > count ?
						    gc->ngpio : count);

			array = kzalloc(काष्ठा_size(descs, desc, count) +
					काष्ठा_size(array_info, invert_mask,
					3 * biपंचांगap_size), GFP_KERNEL);
			अगर (!array) अणु
				gpiod_put_array(descs);
				वापस ERR_PTR(-ENOMEM);
			पूर्ण

			स_नकल(array, descs,
			       काष्ठा_size(descs, desc, descs->ndescs + 1));
			kमुक्त(descs);

			descs = array;
			array_info = (व्योम *)(descs->desc + count);
			array_info->get_mask = array_info->invert_mask +
						  biपंचांगap_size;
			array_info->set_mask = array_info->get_mask +
						  biपंचांगap_size;

			array_info->desc = descs->desc;
			array_info->size = count;
			array_info->chip = gc;
			biपंचांगap_set(array_info->get_mask, descs->ndescs,
				   count - descs->ndescs);
			biपंचांगap_set(array_info->set_mask, descs->ndescs,
				   count - descs->ndescs);
			descs->info = array_info;
		पूर्ण
		/* Unmark array members which करोn't belong to the 'fast' chip */
		अगर (array_info && array_info->chip != gc) अणु
			__clear_bit(descs->ndescs, array_info->get_mask);
			__clear_bit(descs->ndescs, array_info->set_mask);
		पूर्ण
		/*
		 * Detect array members which beदीर्घ to the 'fast' chip
		 * but their pins are not in hardware order.
		 */
		अन्यथा अगर (array_info &&
			   gpio_chip_hwgpio(desc) != descs->ndescs) अणु
			/*
			 * Don't use fast path अगर all array members processed so
			 * far beदीर्घ to the same chip as this one but its pin
			 * hardware number is dअगरferent from its array index.
			 */
			अगर (biपंचांगap_full(array_info->get_mask, descs->ndescs)) अणु
				array_info = शून्य;
			पूर्ण अन्यथा अणु
				__clear_bit(descs->ndescs,
					    array_info->get_mask);
				__clear_bit(descs->ndescs,
					    array_info->set_mask);
			पूर्ण
		पूर्ण अन्यथा अगर (array_info) अणु
			/* Exclude खोलो drain or खोलो source from fast output */
			अगर (gpiochip_line_is_खोलो_drain(gc, descs->ndescs) ||
			    gpiochip_line_is_खोलो_source(gc, descs->ndescs))
				__clear_bit(descs->ndescs,
					    array_info->set_mask);
			/* Identअगरy 'fast' pins which require invertion */
			अगर (gpiod_is_active_low(desc))
				__set_bit(descs->ndescs,
					  array_info->invert_mask);
		पूर्ण

		descs->ndescs++;
	पूर्ण
	अगर (array_info)
		dev_dbg(dev,
			"GPIO array info: chip=%s, size=%d, get_mask=%lx, set_mask=%lx, invert_mask=%lx\n",
			array_info->chip->label, array_info->size,
			*array_info->get_mask, *array_info->set_mask,
			*array_info->invert_mask);
	वापस descs;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_array);

/**
 * gpiod_get_array_optional - obtain multiple GPIOs from a multi-index GPIO
 *                            function
 * @dev:	GPIO consumer, can be शून्य क्रम प्रणाली-global GPIOs
 * @con_id:	function within the GPIO consumer
 * @flags:	optional GPIO initialization flags
 *
 * This is equivalent to gpiod_get_array(), except that when no GPIO was
 * asचिन्हित to the requested function it will वापस शून्य.
 */
काष्ठा gpio_descs *__must_check gpiod_get_array_optional(काष्ठा device *dev,
							स्थिर अक्षर *con_id,
							क्रमागत gpiod_flags flags)
अणु
	काष्ठा gpio_descs *descs;

	descs = gpiod_get_array(dev, con_id, flags);
	अगर (gpiod_not_found(descs))
		वापस शून्य;

	वापस descs;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_get_array_optional);

/**
 * gpiod_put - dispose of a GPIO descriptor
 * @desc:	GPIO descriptor to dispose of
 *
 * No descriptor can be used after gpiod_put() has been called on it.
 */
व्योम gpiod_put(काष्ठा gpio_desc *desc)
अणु
	अगर (desc)
		gpiod_मुक्त(desc);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_put);

/**
 * gpiod_put_array - dispose of multiple GPIO descriptors
 * @descs:	काष्ठा gpio_descs containing an array of descriptors
 */
व्योम gpiod_put_array(काष्ठा gpio_descs *descs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < descs->ndescs; i++)
		gpiod_put(descs->desc[i]);

	kमुक्त(descs);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_put_array);


अटल पूर्णांक gpio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);

	/*
	 * Only match अगर the fwnode करोesn't alपढ़ोy have a proper काष्ठा device
	 * created क्रम it.
	 */
	अगर (fwnode && fwnode->dev != dev)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक gpio_stub_drv_probe(काष्ठा device *dev)
अणु
	/*
	 * The DT node of some GPIO chips have a "compatible" property, but
	 * never have a काष्ठा device added and probed by a driver to रेजिस्टर
	 * the GPIO chip with gpiolib. In such हालs, fw_devlink=on will cause
	 * the consumers of the GPIO chip to get probe deferred क्रमever because
	 * they will be रुकोing क्रम a device associated with the GPIO chip
	 * firmware node to get added and bound to a driver.
	 *
	 * To allow these consumers to probe, we associate the काष्ठा
	 * gpio_device of the GPIO chip with the firmware node and then simply
	 * bind it to this stub driver.
	 */
	वापस 0;
पूर्ण

अटल काष्ठा device_driver gpio_stub_drv = अणु
	.name = "gpio_stub_drv",
	.bus = &gpio_bus_type,
	.probe = gpio_stub_drv_probe,
पूर्ण;

अटल पूर्णांक __init gpiolib_dev_init(व्योम)
अणु
	पूर्णांक ret;

	/* Register GPIO sysfs bus */
	ret = bus_रेजिस्टर(&gpio_bus_type);
	अगर (ret < 0) अणु
		pr_err("gpiolib: could not register GPIO bus type\n");
		वापस ret;
	पूर्ण

	ret = driver_रेजिस्टर(&gpio_stub_drv);
	अगर (ret < 0) अणु
		pr_err("gpiolib: could not register GPIO stub driver\n");
		bus_unरेजिस्टर(&gpio_bus_type);
		वापस ret;
	पूर्ण

	ret = alloc_chrdev_region(&gpio_devt, 0, GPIO_DEV_MAX, GPIOCHIP_NAME);
	अगर (ret < 0) अणु
		pr_err("gpiolib: failed to allocate char dev region\n");
		driver_unरेजिस्टर(&gpio_stub_drv);
		bus_unरेजिस्टर(&gpio_bus_type);
		वापस ret;
	पूर्ण

	gpiolib_initialized = true;
	gpiochip_setup_devs();

#अगर IS_ENABLED(CONFIG_OF_DYNAMIC) && IS_ENABLED(CONFIG_OF_GPIO)
	WARN_ON(of_reconfig_notअगरier_रेजिस्टर(&gpio_of_notअगरier));
#पूर्ण_अगर /* CONFIG_OF_DYNAMIC && CONFIG_OF_GPIO */

	वापस ret;
पूर्ण
core_initcall(gpiolib_dev_init);

#अगर_घोषित CONFIG_DEBUG_FS

अटल व्योम gpiolib_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_device *gdev)
अणु
	अचिन्हित		i;
	काष्ठा gpio_chip	*gc = gdev->chip;
	अचिन्हित		gpio = gdev->base;
	काष्ठा gpio_desc	*gdesc = &gdev->descs[0];
	bool			is_out;
	bool			is_irq;
	bool			active_low;

	क्रम (i = 0; i < gdev->ngpio; i++, gpio++, gdesc++) अणु
		अगर (!test_bit(FLAG_REQUESTED, &gdesc->flags)) अणु
			अगर (gdesc->name) अणु
				seq_म_लिखो(s, " gpio-%-3d (%-20.20s)\n",
					   gpio, gdesc->name);
			पूर्ण
			जारी;
		पूर्ण

		gpiod_get_direction(gdesc);
		is_out = test_bit(FLAG_IS_OUT, &gdesc->flags);
		is_irq = test_bit(FLAG_USED_AS_IRQ, &gdesc->flags);
		active_low = test_bit(FLAG_ACTIVE_LOW, &gdesc->flags);
		seq_म_लिखो(s, " gpio-%-3d (%-20.20s|%-20.20s) %s %s %s%s",
			gpio, gdesc->name ? gdesc->name : "", gdesc->label,
			is_out ? "out" : "in ",
			gc->get ? (gc->get(gc, i) ? "hi" : "lo") : "?  ",
			is_irq ? "IRQ " : "",
			active_low ? "ACTIVE LOW" : "");
		seq_म_लिखो(s, "\n");
	पूर्ण
पूर्ण

अटल व्योम *gpiolib_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_device *gdev = शून्य;
	loff_t index = *pos;

	s->निजी = "";

	spin_lock_irqsave(&gpio_lock, flags);
	list_क्रम_each_entry(gdev, &gpio_devices, list)
		अगर (index-- == 0) अणु
			spin_unlock_irqrestore(&gpio_lock, flags);
			वापस gdev;
		पूर्ण
	spin_unlock_irqrestore(&gpio_lock, flags);

	वापस शून्य;
पूर्ण

अटल व्योम *gpiolib_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_device *gdev = v;
	व्योम *ret = शून्य;

	spin_lock_irqsave(&gpio_lock, flags);
	अगर (list_is_last(&gdev->list, &gpio_devices))
		ret = शून्य;
	अन्यथा
		ret = list_entry(gdev->list.next, काष्ठा gpio_device, list);
	spin_unlock_irqrestore(&gpio_lock, flags);

	s->निजी = "\n";
	++*pos;

	वापस ret;
पूर्ण

अटल व्योम gpiolib_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक gpiolib_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा gpio_device *gdev = v;
	काष्ठा gpio_chip *gc = gdev->chip;
	काष्ठा device *parent;

	अगर (!gc) अणु
		seq_म_लिखो(s, "%s%s: (dangling chip)", (अक्षर *)s->निजी,
			   dev_name(&gdev->dev));
		वापस 0;
	पूर्ण

	seq_म_लिखो(s, "%s%s: GPIOs %d-%d", (अक्षर *)s->निजी,
		   dev_name(&gdev->dev),
		   gdev->base, gdev->base + gdev->ngpio - 1);
	parent = gc->parent;
	अगर (parent)
		seq_म_लिखो(s, ", parent: %s/%s",
			   parent->bus ? parent->bus->name : "no-bus",
			   dev_name(parent));
	अगर (gc->label)
		seq_म_लिखो(s, ", %s", gc->label);
	अगर (gc->can_sleep)
		seq_म_लिखो(s, ", can sleep");
	seq_म_लिखो(s, ":\n");

	अगर (gc->dbg_show)
		gc->dbg_show(s, gc);
	अन्यथा
		gpiolib_dbg_show(s, gdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations gpiolib_sops = अणु
	.start = gpiolib_seq_start,
	.next = gpiolib_seq_next,
	.stop = gpiolib_seq_stop,
	.show = gpiolib_seq_show,
पूर्ण;
DEFINE_SEQ_ATTRIBUTE(gpiolib);

अटल पूर्णांक __init gpiolib_debugfs_init(व्योम)
अणु
	/* /sys/kernel/debug/gpio */
	debugfs_create_file("gpio", 0444, शून्य, शून्य, &gpiolib_fops);
	वापस 0;
पूर्ण
subsys_initcall(gpiolib_debugfs_init);

#पूर्ण_अगर	/* DEBUG_FS */
