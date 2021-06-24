<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/idr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>

#समावेश "gpiolib.h"
#समावेश "gpiolib-sysfs.h"

#घोषणा GPIO_IRQF_TRIGGER_FALLING	BIT(0)
#घोषणा GPIO_IRQF_TRIGGER_RISING	BIT(1)
#घोषणा GPIO_IRQF_TRIGGER_BOTH		(GPIO_IRQF_TRIGGER_FALLING | \
					 GPIO_IRQF_TRIGGER_RISING)

काष्ठा gpiod_data अणु
	काष्ठा gpio_desc *desc;

	काष्ठा mutex mutex;
	काष्ठा kernfs_node *value_kn;
	पूर्णांक irq;
	अचिन्हित अक्षर irq_flags;

	bool direction_can_change;
पूर्ण;

/*
 * Lock to serialise gpiod export and unexport, and prevent re-export of
 * gpiod whose chip is being unरेजिस्टरed.
 */
अटल DEFINE_MUTEX(sysfs_lock);

/*
 * /sys/class/gpio/gpioN... only क्रम GPIOs that are exported
 *   /direction
 *      * MAY BE OMITTED अगर kernel won't allow direction changes
 *      * is पढ़ो/ग_लिखो as "in" or "out"
 *      * may also be written as "high" or "low", initializing
 *        output value as specअगरied ("out" implies "low")
 *   /value
 *      * always पढ़ोable, subject to hardware behavior
 *      * may be writable, as zero/nonzero
 *   /edge
 *      * configures behavior of poll(2) on /value
 *      * available only अगर pin can generate IRQs on input
 *      * is पढ़ो/ग_लिखो as "none", "falling", "rising", or "both"
 *   /active_low
 *      * configures polarity of /value
 *      * is पढ़ो/ग_लिखो as zero/nonzero
 *      * also affects existing and subsequent "falling" and "rising"
 *        /edge configuration
 */

अटल sमाप_प्रकार direction_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	काष्ठा gpio_desc *desc = data->desc;
	sमाप_प्रकार			status;

	mutex_lock(&data->mutex);

	gpiod_get_direction(desc);
	status = प्र_लिखो(buf, "%s\n",
			test_bit(FLAG_IS_OUT, &desc->flags)
				? "out" : "in");

	mutex_unlock(&data->mutex);

	वापस status;
पूर्ण

अटल sमाप_प्रकार direction_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	काष्ठा gpio_desc *desc = data->desc;
	sमाप_प्रकार			status;

	mutex_lock(&data->mutex);

	अगर (sysfs_streq(buf, "high"))
		status = gpiod_direction_output_raw(desc, 1);
	अन्यथा अगर (sysfs_streq(buf, "out") || sysfs_streq(buf, "low"))
		status = gpiod_direction_output_raw(desc, 0);
	अन्यथा अगर (sysfs_streq(buf, "in"))
		status = gpiod_direction_input(desc);
	अन्यथा
		status = -EINVAL;

	mutex_unlock(&data->mutex);

	वापस status ? : size;
पूर्ण
अटल DEVICE_ATTR_RW(direction);

अटल sमाप_प्रकार value_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	काष्ठा gpio_desc *desc = data->desc;
	sमाप_प्रकार			status;

	mutex_lock(&data->mutex);

	status = gpiod_get_value_cansleep(desc);
	अगर (status < 0)
		जाओ err;

	buf[0] = '0' + status;
	buf[1] = '\n';
	status = 2;
err:
	mutex_unlock(&data->mutex);

	वापस status;
पूर्ण

अटल sमाप_प्रकार value_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	काष्ठा gpio_desc *desc = data->desc;
	sमाप_प्रकार status = 0;

	mutex_lock(&data->mutex);

	अगर (!test_bit(FLAG_IS_OUT, &desc->flags)) अणु
		status = -EPERM;
	पूर्ण अन्यथा अणु
		दीर्घ		value;

		अगर (size <= 2 && है_अंक(buf[0]) &&
		    (size == 1 || buf[1] == '\n'))
			value = buf[0] - '0';
		अन्यथा
			status = kम_से_दीर्घ(buf, 0, &value);
		अगर (status == 0) अणु
			gpiod_set_value_cansleep(desc, value);
			status = size;
		पूर्ण
	पूर्ण

	mutex_unlock(&data->mutex);

	वापस status;
पूर्ण
अटल DEVICE_ATTR_PREALLOC(value, S_IWUSR | S_IRUGO, value_show, value_store);

अटल irqवापस_t gpio_sysfs_irq(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा gpiod_data *data = priv;

	sysfs_notअगरy_dirent(data->value_kn);

	वापस IRQ_HANDLED;
पूर्ण

/* Caller holds gpiod-data mutex. */
अटल पूर्णांक gpio_sysfs_request_irq(काष्ठा device *dev, अचिन्हित अक्षर flags)
अणु
	काष्ठा gpiod_data	*data = dev_get_drvdata(dev);
	काष्ठा gpio_desc	*desc = data->desc;
	अचिन्हित दीर्घ		irq_flags;
	पूर्णांक			ret;

	data->irq = gpiod_to_irq(desc);
	अगर (data->irq < 0)
		वापस -EIO;

	data->value_kn = sysfs_get_dirent(dev->kobj.sd, "value");
	अगर (!data->value_kn)
		वापस -ENODEV;

	irq_flags = IRQF_SHARED;
	अगर (flags & GPIO_IRQF_TRIGGER_FALLING)
		irq_flags |= test_bit(FLAG_ACTIVE_LOW, &desc->flags) ?
			IRQF_TRIGGER_RISING : IRQF_TRIGGER_FALLING;
	अगर (flags & GPIO_IRQF_TRIGGER_RISING)
		irq_flags |= test_bit(FLAG_ACTIVE_LOW, &desc->flags) ?
			IRQF_TRIGGER_FALLING : IRQF_TRIGGER_RISING;

	/*
	 * FIXME: This should be करोne in the irq_request_resources callback
	 *        when the irq is requested, but a few drivers currently fail
	 *        to करो so.
	 *
	 *        Remove this redundant call (aदीर्घ with the corresponding
	 *        unlock) when those drivers have been fixed.
	 */
	ret = gpiochip_lock_as_irq(desc->gdev->chip, gpio_chip_hwgpio(desc));
	अगर (ret < 0)
		जाओ err_put_kn;

	ret = request_any_context_irq(data->irq, gpio_sysfs_irq, irq_flags,
				"gpiolib", data);
	अगर (ret < 0)
		जाओ err_unlock;

	data->irq_flags = flags;

	वापस 0;

err_unlock:
	gpiochip_unlock_as_irq(desc->gdev->chip, gpio_chip_hwgpio(desc));
err_put_kn:
	sysfs_put(data->value_kn);

	वापस ret;
पूर्ण

/*
 * Caller holds gpiod-data mutex (unless called after class-device
 * deregistration).
 */
अटल व्योम gpio_sysfs_मुक्त_irq(काष्ठा device *dev)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	काष्ठा gpio_desc *desc = data->desc;

	data->irq_flags = 0;
	मुक्त_irq(data->irq, data);
	gpiochip_unlock_as_irq(desc->gdev->chip, gpio_chip_hwgpio(desc));
	sysfs_put(data->value_kn);
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	अचिन्हित अक्षर flags;
पूर्ण trigger_types[] = अणु
	अणु "none",    0 पूर्ण,
	अणु "falling", GPIO_IRQF_TRIGGER_FALLING पूर्ण,
	अणु "rising",  GPIO_IRQF_TRIGGER_RISING पूर्ण,
	अणु "both",    GPIO_IRQF_TRIGGER_BOTH पूर्ण,
पूर्ण;

अटल sमाप_प्रकार edge_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	sमाप_प्रकार	status = 0;
	पूर्णांक i;

	mutex_lock(&data->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(trigger_types); i++) अणु
		अगर (data->irq_flags == trigger_types[i].flags) अणु
			status = प्र_लिखो(buf, "%s\n", trigger_types[i].name);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&data->mutex);

	वापस status;
पूर्ण

अटल sमाप_प्रकार edge_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	अचिन्हित अक्षर flags;
	sमाप_प्रकार	status = size;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(trigger_types); i++) अणु
		अगर (sysfs_streq(trigger_types[i].name, buf))
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(trigger_types))
		वापस -EINVAL;

	flags = trigger_types[i].flags;

	mutex_lock(&data->mutex);

	अगर (flags == data->irq_flags) अणु
		status = size;
		जाओ out_unlock;
	पूर्ण

	अगर (data->irq_flags)
		gpio_sysfs_मुक्त_irq(dev);

	अगर (flags) अणु
		status = gpio_sysfs_request_irq(dev, flags);
		अगर (!status)
			status = size;
	पूर्ण

out_unlock:
	mutex_unlock(&data->mutex);

	वापस status;
पूर्ण
अटल DEVICE_ATTR_RW(edge);

/* Caller holds gpiod-data mutex. */
अटल पूर्णांक gpio_sysfs_set_active_low(काष्ठा device *dev, पूर्णांक value)
अणु
	काष्ठा gpiod_data	*data = dev_get_drvdata(dev);
	काष्ठा gpio_desc	*desc = data->desc;
	पूर्णांक			status = 0;
	अचिन्हित पूर्णांक		flags = data->irq_flags;

	अगर (!!test_bit(FLAG_ACTIVE_LOW, &desc->flags) == !!value)
		वापस 0;

	अगर (value)
		set_bit(FLAG_ACTIVE_LOW, &desc->flags);
	अन्यथा
		clear_bit(FLAG_ACTIVE_LOW, &desc->flags);

	/* reconfigure poll(2) support अगर enabled on one edge only */
	अगर (flags == GPIO_IRQF_TRIGGER_FALLING ||
					flags == GPIO_IRQF_TRIGGER_RISING) अणु
		gpio_sysfs_मुक्त_irq(dev);
		status = gpio_sysfs_request_irq(dev, flags);
	पूर्ण

	वापस status;
पूर्ण

अटल sमाप_प्रकार active_low_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	काष्ठा gpio_desc *desc = data->desc;
	sमाप_प्रकार			status;

	mutex_lock(&data->mutex);

	status = प्र_लिखो(buf, "%d\n",
				!!test_bit(FLAG_ACTIVE_LOW, &desc->flags));

	mutex_unlock(&data->mutex);

	वापस status;
पूर्ण

अटल sमाप_प्रकार active_low_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा gpiod_data	*data = dev_get_drvdata(dev);
	sमाप_प्रकार			status;
	दीर्घ			value;

	mutex_lock(&data->mutex);

	status = kम_से_दीर्घ(buf, 0, &value);
	अगर (status == 0)
		status = gpio_sysfs_set_active_low(dev, value);

	mutex_unlock(&data->mutex);

	वापस status ? : size;
पूर्ण
अटल DEVICE_ATTR_RW(active_low);

अटल umode_t gpio_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);
	काष्ठा gpio_desc *desc = data->desc;
	umode_t mode = attr->mode;
	bool show_direction = data->direction_can_change;

	अगर (attr == &dev_attr_direction.attr) अणु
		अगर (!show_direction)
			mode = 0;
	पूर्ण अन्यथा अगर (attr == &dev_attr_edge.attr) अणु
		अगर (gpiod_to_irq(desc) < 0)
			mode = 0;
		अगर (!show_direction && test_bit(FLAG_IS_OUT, &desc->flags))
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल काष्ठा attribute *gpio_attrs[] = अणु
	&dev_attr_direction.attr,
	&dev_attr_edge.attr,
	&dev_attr_value.attr,
	&dev_attr_active_low.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group gpio_group = अणु
	.attrs = gpio_attrs,
	.is_visible = gpio_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *gpio_groups[] = अणु
	&gpio_group,
	शून्य
पूर्ण;

/*
 * /sys/class/gpio/gpiochipN/
 *   /base ... matching gpio_chip.base (N)
 *   /label ... matching gpio_chip.label
 *   /ngpio ... matching gpio_chip.ngpio
 */

अटल sमाप_प्रकार base_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा gpio_chip	*chip = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", chip->base);
पूर्ण
अटल DEVICE_ATTR_RO(base);

अटल sमाप_प्रकार label_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा gpio_chip	*chip = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", chip->label ? : "");
पूर्ण
अटल DEVICE_ATTR_RO(label);

अटल sमाप_प्रकार ngpio_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा gpio_chip	*chip = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", chip->ngpio);
पूर्ण
अटल DEVICE_ATTR_RO(ngpio);

अटल काष्ठा attribute *gpiochip_attrs[] = अणु
	&dev_attr_base.attr,
	&dev_attr_label.attr,
	&dev_attr_ngpio.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(gpiochip);

/*
 * /sys/class/gpio/export ... ग_लिखो-only
 *	पूर्णांकeger N ... number of GPIO to export (full access)
 * /sys/class/gpio/unexport ... ग_लिखो-only
 *	पूर्णांकeger N ... number of GPIO to unexport
 */
अटल sमाप_प्रकार export_store(काष्ठा class *class,
				काष्ठा class_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	दीर्घ			gpio;
	काष्ठा gpio_desc	*desc;
	पूर्णांक			status;
	काष्ठा gpio_chip	*gc;
	पूर्णांक			offset;

	status = kम_से_दीर्घ(buf, 0, &gpio);
	अगर (status < 0)
		जाओ करोne;

	desc = gpio_to_desc(gpio);
	/* reject invalid GPIOs */
	अगर (!desc) अणु
		pr_warn("%s: invalid GPIO %ld\n", __func__, gpio);
		वापस -EINVAL;
	पूर्ण
	gc = desc->gdev->chip;
	offset = gpio_chip_hwgpio(desc);
	अगर (!gpiochip_line_is_valid(gc, offset)) अणु
		pr_warn("%s: GPIO %ld masked\n", __func__, gpio);
		वापस -EINVAL;
	पूर्ण

	/* No extra locking here; FLAG_SYSFS just signअगरies that the
	 * request and export were करोne by on behalf of userspace, so
	 * they may be unकरोne on its behalf too.
	 */

	status = gpiod_request(desc, "sysfs");
	अगर (status) अणु
		अगर (status == -EPROBE_DEFER)
			status = -ENODEV;
		जाओ करोne;
	पूर्ण

	status = gpiod_set_transitory(desc, false);
	अगर (!status) अणु
		status = gpiod_export(desc, true);
		अगर (status < 0)
			gpiod_मुक्त(desc);
		अन्यथा
			set_bit(FLAG_SYSFS, &desc->flags);
	पूर्ण

करोne:
	अगर (status)
		pr_debug("%s: status %d\n", __func__, status);
	वापस status ? : len;
पूर्ण
अटल CLASS_ATTR_WO(export);

अटल sमाप_प्रकार unexport_store(काष्ठा class *class,
				काष्ठा class_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	दीर्घ			gpio;
	काष्ठा gpio_desc	*desc;
	पूर्णांक			status;

	status = kम_से_दीर्घ(buf, 0, &gpio);
	अगर (status < 0)
		जाओ करोne;

	desc = gpio_to_desc(gpio);
	/* reject bogus commands (gpio_unexport ignores them) */
	अगर (!desc) अणु
		pr_warn("%s: invalid GPIO %ld\n", __func__, gpio);
		वापस -EINVAL;
	पूर्ण

	status = -EINVAL;

	/* No extra locking here; FLAG_SYSFS just signअगरies that the
	 * request and export were करोne by on behalf of userspace, so
	 * they may be unकरोne on its behalf too.
	 */
	अगर (test_and_clear_bit(FLAG_SYSFS, &desc->flags)) अणु
		status = 0;
		gpiod_मुक्त(desc);
	पूर्ण
करोne:
	अगर (status)
		pr_debug("%s: status %d\n", __func__, status);
	वापस status ? : len;
पूर्ण
अटल CLASS_ATTR_WO(unexport);

अटल काष्ठा attribute *gpio_class_attrs[] = अणु
	&class_attr_export.attr,
	&class_attr_unexport.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(gpio_class);

अटल काष्ठा class gpio_class = अणु
	.name =		"gpio",
	.owner =	THIS_MODULE,

	.class_groups = gpio_class_groups,
पूर्ण;


/**
 * gpiod_export - export a GPIO through sysfs
 * @desc: GPIO to make available, alपढ़ोy requested
 * @direction_may_change: true अगर userspace may change GPIO direction
 * Context: arch_initcall or later
 *
 * When drivers want to make a GPIO accessible to userspace after they
 * have requested it -- perhaps जबतक debugging, or as part of their
 * खुला पूर्णांकerface -- they may use this routine.  If the GPIO can
 * change direction (some can't) and the caller allows it, userspace
 * will see "direction" sysfs attribute which may be used to change
 * the gpio's direction.  A "value" attribute will always be provided.
 *
 * Returns zero on success, अन्यथा an error.
 */
पूर्णांक gpiod_export(काष्ठा gpio_desc *desc, bool direction_may_change)
अणु
	काष्ठा gpio_chip	*chip;
	काष्ठा gpio_device	*gdev;
	काष्ठा gpiod_data	*data;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			status;
	स्थिर अक्षर		*ioname = शून्य;
	काष्ठा device		*dev;
	पूर्णांक			offset;

	/* can't export until sysfs is available ... */
	अगर (!gpio_class.p) अणु
		pr_debug("%s: called too early!\n", __func__);
		वापस -ENOENT;
	पूर्ण

	अगर (!desc) अणु
		pr_debug("%s: invalid gpio descriptor\n", __func__);
		वापस -EINVAL;
	पूर्ण

	gdev = desc->gdev;
	chip = gdev->chip;

	mutex_lock(&sysfs_lock);

	/* check अगर chip is being हटाओd */
	अगर (!chip || !gdev->mockdev) अणु
		status = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	spin_lock_irqsave(&gpio_lock, flags);
	अगर (!test_bit(FLAG_REQUESTED, &desc->flags) ||
	     test_bit(FLAG_EXPORT, &desc->flags)) अणु
		spin_unlock_irqrestore(&gpio_lock, flags);
		gpiod_dbg(desc, "%s: unavailable (requested=%d, exported=%d)\n",
				__func__,
				test_bit(FLAG_REQUESTED, &desc->flags),
				test_bit(FLAG_EXPORT, &desc->flags));
		status = -EPERM;
		जाओ err_unlock;
	पूर्ण
	spin_unlock_irqrestore(&gpio_lock, flags);

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		status = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	data->desc = desc;
	mutex_init(&data->mutex);
	अगर (chip->direction_input && chip->direction_output)
		data->direction_can_change = direction_may_change;
	अन्यथा
		data->direction_can_change = false;

	offset = gpio_chip_hwgpio(desc);
	अगर (chip->names && chip->names[offset])
		ioname = chip->names[offset];

	dev = device_create_with_groups(&gpio_class, &gdev->dev,
					MKDEV(0, 0), data, gpio_groups,
					ioname ? ioname : "gpio%u",
					desc_to_gpio(desc));
	अगर (IS_ERR(dev)) अणु
		status = PTR_ERR(dev);
		जाओ err_मुक्त_data;
	पूर्ण

	set_bit(FLAG_EXPORT, &desc->flags);
	mutex_unlock(&sysfs_lock);
	वापस 0;

err_मुक्त_data:
	kमुक्त(data);
err_unlock:
	mutex_unlock(&sysfs_lock);
	gpiod_dbg(desc, "%s: status %d\n", __func__, status);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_export);

अटल पूर्णांक match_export(काष्ठा device *dev, स्थिर व्योम *desc)
अणु
	काष्ठा gpiod_data *data = dev_get_drvdata(dev);

	वापस data->desc == desc;
पूर्ण

/**
 * gpiod_export_link - create a sysfs link to an exported GPIO node
 * @dev: device under which to create symlink
 * @name: name of the symlink
 * @desc: GPIO to create symlink to, alपढ़ोy exported
 *
 * Set up a symlink from /sys/.../dev/name to /sys/class/gpio/gpioN
 * node. Caller is responsible क्रम unlinking.
 *
 * Returns zero on success, अन्यथा an error.
 */
पूर्णांक gpiod_export_link(काष्ठा device *dev, स्थिर अक्षर *name,
		      काष्ठा gpio_desc *desc)
अणु
	काष्ठा device *cdev;
	पूर्णांक ret;

	अगर (!desc) अणु
		pr_warn("%s: invalid GPIO\n", __func__);
		वापस -EINVAL;
	पूर्ण

	cdev = class_find_device(&gpio_class, शून्य, desc, match_export);
	अगर (!cdev)
		वापस -ENODEV;

	ret = sysfs_create_link(&dev->kobj, &cdev->kobj, name);
	put_device(cdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_export_link);

/**
 * gpiod_unexport - reverse effect of gpiod_export()
 * @desc: GPIO to make unavailable
 *
 * This is implicit on gpiod_मुक्त().
 */
व्योम gpiod_unexport(काष्ठा gpio_desc *desc)
अणु
	काष्ठा gpiod_data *data;
	काष्ठा device *dev;

	अगर (!desc) अणु
		pr_warn("%s: invalid GPIO\n", __func__);
		वापस;
	पूर्ण

	mutex_lock(&sysfs_lock);

	अगर (!test_bit(FLAG_EXPORT, &desc->flags))
		जाओ err_unlock;

	dev = class_find_device(&gpio_class, शून्य, desc, match_export);
	अगर (!dev)
		जाओ err_unlock;

	data = dev_get_drvdata(dev);

	clear_bit(FLAG_EXPORT, &desc->flags);

	device_unरेजिस्टर(dev);

	/*
	 * Release irq after deregistration to prevent race with edge_store.
	 */
	अगर (data->irq_flags)
		gpio_sysfs_मुक्त_irq(dev);

	mutex_unlock(&sysfs_lock);

	put_device(dev);
	kमुक्त(data);

	वापस;

err_unlock:
	mutex_unlock(&sysfs_lock);
पूर्ण
EXPORT_SYMBOL_GPL(gpiod_unexport);

पूर्णांक gpiochip_sysfs_रेजिस्टर(काष्ठा gpio_device *gdev)
अणु
	काष्ठा device	*dev;
	काष्ठा device	*parent;
	काष्ठा gpio_chip *chip = gdev->chip;

	/*
	 * Many प्रणालीs add gpio chips क्रम SOC support very early,
	 * beक्रमe driver model support is available.  In those हालs we
	 * रेजिस्टर later, in gpiolib_sysfs_init() ... here we just
	 * verअगरy that _some_ field of gpio_class got initialized.
	 */
	अगर (!gpio_class.p)
		वापस 0;

	/*
	 * For sysfs backward compatibility we need to preserve this
	 * preferred parenting to the gpio_chip parent field, अगर set.
	 */
	अगर (chip->parent)
		parent = chip->parent;
	अन्यथा
		parent = &gdev->dev;

	/* use chip->base क्रम the ID; it's alपढ़ोy known to be unique */
	dev = device_create_with_groups(&gpio_class, parent, MKDEV(0, 0), chip,
					gpiochip_groups, GPIOCHIP_NAME "%d",
					chip->base);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	mutex_lock(&sysfs_lock);
	gdev->mockdev = dev;
	mutex_unlock(&sysfs_lock);

	वापस 0;
पूर्ण

व्योम gpiochip_sysfs_unरेजिस्टर(काष्ठा gpio_device *gdev)
अणु
	काष्ठा gpio_desc *desc;
	काष्ठा gpio_chip *chip = gdev->chip;
	अचिन्हित पूर्णांक i;

	अगर (!gdev->mockdev)
		वापस;

	device_unरेजिस्टर(gdev->mockdev);

	/* prevent further gpiod exports */
	mutex_lock(&sysfs_lock);
	gdev->mockdev = शून्य;
	mutex_unlock(&sysfs_lock);

	/* unरेजिस्टर gpiod class devices owned by sysfs */
	क्रम (i = 0; i < chip->ngpio; i++) अणु
		desc = &gdev->descs[i];
		अगर (test_and_clear_bit(FLAG_SYSFS, &desc->flags))
			gpiod_मुक्त(desc);
	पूर्ण
पूर्ण

अटल पूर्णांक __init gpiolib_sysfs_init(व्योम)
अणु
	पूर्णांक		status;
	अचिन्हित दीर्घ	flags;
	काष्ठा gpio_device *gdev;

	status = class_रेजिस्टर(&gpio_class);
	अगर (status < 0)
		वापस status;

	/* Scan and रेजिस्टर the gpio_chips which रेजिस्टरed very
	 * early (e.g. beक्रमe the class_रेजिस्टर above was called).
	 *
	 * We run beक्रमe arch_initcall() so chip->dev nodes can have
	 * रेजिस्टरed, and so arch_initcall() can always gpio_export().
	 */
	spin_lock_irqsave(&gpio_lock, flags);
	list_क्रम_each_entry(gdev, &gpio_devices, list) अणु
		अगर (gdev->mockdev)
			जारी;

		/*
		 * TODO we yield gpio_lock here because
		 * gpiochip_sysfs_रेजिस्टर() acquires a mutex. This is unsafe
		 * and needs to be fixed.
		 *
		 * Also it would be nice to use gpiochip_find() here so we
		 * can keep gpio_chips local to gpiolib.c, but the yield of
		 * gpio_lock prevents us from करोing this.
		 */
		spin_unlock_irqrestore(&gpio_lock, flags);
		status = gpiochip_sysfs_रेजिस्टर(gdev);
		spin_lock_irqsave(&gpio_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&gpio_lock, flags);

	वापस status;
पूर्ण
postcore_initcall(gpiolib_sysfs_init);
