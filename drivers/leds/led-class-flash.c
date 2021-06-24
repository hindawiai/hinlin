<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Flash class पूर्णांकerface
 *
 * Copyright (C) 2015 Samsung Electronics Co., Ltd.
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "leds.h"

#घोषणा has_flash_op(fled_cdev, op)				\
	(fled_cdev && fled_cdev->ops->op)

#घोषणा call_flash_op(fled_cdev, op, args...)		\
	((has_flash_op(fled_cdev, op)) ?			\
			(fled_cdev->ops->op(fled_cdev, args)) :	\
			-EINVAL)

अटल स्थिर अक्षर * स्थिर led_flash_fault_names[] = अणु
	"led-over-voltage",
	"flash-timeout-exceeded",
	"controller-over-temperature",
	"controller-short-circuit",
	"led-power-supply-over-current",
	"indicator-led-fault",
	"led-under-voltage",
	"controller-under-voltage",
	"led-over-temperature",
पूर्ण;

अटल sमाप_प्रकार flash_brightness_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
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

	ret = led_set_flash_brightness(fled_cdev, state);
	अगर (ret < 0)
		जाओ unlock;

	ret = size;
unlock:
	mutex_unlock(&led_cdev->led_access);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार flash_brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);

	/* no lock needed क्रम this */
	led_update_flash_brightness(fled_cdev);

	वापस प्र_लिखो(buf, "%u\n", fled_cdev->brightness.val);
पूर्ण
अटल DEVICE_ATTR_RW(flash_brightness);

अटल sमाप_प्रकार max_flash_brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);

	वापस प्र_लिखो(buf, "%u\n", fled_cdev->brightness.max);
पूर्ण
अटल DEVICE_ATTR_RO(max_flash_brightness);

अटल sमाप_प्रकार flash_strobe_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	अचिन्हित दीर्घ state;
	sमाप_प्रकार ret = -EINVAL;

	mutex_lock(&led_cdev->led_access);

	अगर (led_sysfs_is_disabled(led_cdev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 10, &state);
	अगर (ret)
		जाओ unlock;

	अगर (state > 1) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	ret = led_set_flash_strobe(fled_cdev, state);
	अगर (ret < 0)
		जाओ unlock;
	ret = size;
unlock:
	mutex_unlock(&led_cdev->led_access);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार flash_strobe_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	bool state;
	पूर्णांक ret;

	/* no lock needed क्रम this */
	ret = led_get_flash_strobe(fled_cdev, &state);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", state);
पूर्ण
अटल DEVICE_ATTR_RW(flash_strobe);

अटल sमाप_प्रकार flash_समयout_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	अचिन्हित दीर्घ flash_समयout;
	sमाप_प्रकार ret;

	mutex_lock(&led_cdev->led_access);

	अगर (led_sysfs_is_disabled(led_cdev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 10, &flash_समयout);
	अगर (ret)
		जाओ unlock;

	ret = led_set_flash_समयout(fled_cdev, flash_समयout);
	अगर (ret < 0)
		जाओ unlock;

	ret = size;
unlock:
	mutex_unlock(&led_cdev->led_access);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार flash_समयout_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);

	वापस प्र_लिखो(buf, "%u\n", fled_cdev->समयout.val);
पूर्ण
अटल DEVICE_ATTR_RW(flash_समयout);

अटल sमाप_प्रकार max_flash_समयout_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);

	वापस प्र_लिखो(buf, "%u\n", fled_cdev->समयout.max);
पूर्ण
अटल DEVICE_ATTR_RO(max_flash_समयout);

अटल sमाप_प्रकार flash_fault_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	u32 fault, mask = 0x1;
	अक्षर *pbuf = buf;
	पूर्णांक i, ret, buf_len;

	ret = led_get_flash_fault(fled_cdev, &fault);
	अगर (ret < 0)
		वापस -EINVAL;

	*buf = '\0';

	क्रम (i = 0; i < LED_NUM_FLASH_FAULTS; ++i) अणु
		अगर (fault & mask) अणु
			buf_len = प्र_लिखो(pbuf, "%s ",
					  led_flash_fault_names[i]);
			pbuf += buf_len;
		पूर्ण
		mask <<= 1;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", buf);
पूर्ण
अटल DEVICE_ATTR_RO(flash_fault);

अटल काष्ठा attribute *led_flash_strobe_attrs[] = अणु
	&dev_attr_flash_strobe.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *led_flash_समयout_attrs[] = अणु
	&dev_attr_flash_समयout.attr,
	&dev_attr_max_flash_समयout.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *led_flash_brightness_attrs[] = अणु
	&dev_attr_flash_brightness.attr,
	&dev_attr_max_flash_brightness.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *led_flash_fault_attrs[] = अणु
	&dev_attr_flash_fault.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group led_flash_strobe_group = अणु
	.attrs = led_flash_strobe_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group led_flash_समयout_group = अणु
	.attrs = led_flash_समयout_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group led_flash_brightness_group = अणु
	.attrs = led_flash_brightness_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group led_flash_fault_group = अणु
	.attrs = led_flash_fault_attrs,
पूर्ण;

अटल व्योम led_flash_resume(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);

	call_flash_op(fled_cdev, flash_brightness_set,
					fled_cdev->brightness.val);
	call_flash_op(fled_cdev, समयout_set, fled_cdev->समयout.val);
पूर्ण

अटल व्योम led_flash_init_sysfs_groups(काष्ठा led_classdev_flash *fled_cdev)
अणु
	काष्ठा led_classdev *led_cdev = &fled_cdev->led_cdev;
	स्थिर काष्ठा led_flash_ops *ops = fled_cdev->ops;
	स्थिर काष्ठा attribute_group **flash_groups = fled_cdev->sysfs_groups;

	पूर्णांक num_sysfs_groups = 0;

	flash_groups[num_sysfs_groups++] = &led_flash_strobe_group;

	अगर (ops->flash_brightness_set)
		flash_groups[num_sysfs_groups++] = &led_flash_brightness_group;

	अगर (ops->समयout_set)
		flash_groups[num_sysfs_groups++] = &led_flash_समयout_group;

	अगर (ops->fault_get)
		flash_groups[num_sysfs_groups++] = &led_flash_fault_group;

	led_cdev->groups = flash_groups;
पूर्ण

पूर्णांक led_classdev_flash_रेजिस्टर_ext(काष्ठा device *parent,
				    काष्ठा led_classdev_flash *fled_cdev,
				    काष्ठा led_init_data *init_data)
अणु
	काष्ठा led_classdev *led_cdev;
	स्थिर काष्ठा led_flash_ops *ops;
	पूर्णांक ret;

	अगर (!fled_cdev)
		वापस -EINVAL;

	led_cdev = &fled_cdev->led_cdev;

	अगर (led_cdev->flags & LED_DEV_CAP_FLASH) अणु
		अगर (!led_cdev->brightness_set_blocking)
			वापस -EINVAL;

		ops = fled_cdev->ops;
		अगर (!ops || !ops->strobe_set)
			वापस -EINVAL;

		led_cdev->flash_resume = led_flash_resume;

		/* Select the sysfs attributes to be created क्रम the device */
		led_flash_init_sysfs_groups(fled_cdev);
	पूर्ण

	/* Register led class device */
	ret = led_classdev_रेजिस्टर_ext(parent, led_cdev, init_data);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_flash_रेजिस्टर_ext);

व्योम led_classdev_flash_unरेजिस्टर(काष्ठा led_classdev_flash *fled_cdev)
अणु
	अगर (!fled_cdev)
		वापस;

	led_classdev_unरेजिस्टर(&fled_cdev->led_cdev);
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_flash_unरेजिस्टर);

अटल व्योम devm_led_classdev_flash_release(काष्ठा device *dev, व्योम *res)
अणु
	led_classdev_flash_unरेजिस्टर(*(काष्ठा led_classdev_flash **)res);
पूर्ण

पूर्णांक devm_led_classdev_flash_रेजिस्टर_ext(काष्ठा device *parent,
				     काष्ठा led_classdev_flash *fled_cdev,
				     काष्ठा led_init_data *init_data)
अणु
	काष्ठा led_classdev_flash **dr;
	पूर्णांक ret;

	dr = devres_alloc(devm_led_classdev_flash_release, माप(*dr),
			  GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = led_classdev_flash_रेजिस्टर_ext(parent, fled_cdev, init_data);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	*dr = fled_cdev;
	devres_add(parent, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_led_classdev_flash_रेजिस्टर_ext);

अटल पूर्णांक devm_led_classdev_flash_match(काष्ठा device *dev,
					      व्योम *res, व्योम *data)
अणु
	काष्ठा led_classdev_flash **p = res;

	अगर (WARN_ON(!p || !*p))
		वापस 0;

	वापस *p == data;
पूर्ण

व्योम devm_led_classdev_flash_unरेजिस्टर(काष्ठा device *dev,
					काष्ठा led_classdev_flash *fled_cdev)
अणु
	WARN_ON(devres_release(dev,
			       devm_led_classdev_flash_release,
			       devm_led_classdev_flash_match, fled_cdev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_led_classdev_flash_unरेजिस्टर);

अटल व्योम led_clamp_align(काष्ठा led_flash_setting *s)
अणु
	u32 v, offset;

	v = s->val + s->step / 2;
	v = clamp(v, s->min, s->max);
	offset = v - s->min;
	offset = s->step * (offset / s->step);
	s->val = s->min + offset;
पूर्ण

पूर्णांक led_set_flash_समयout(काष्ठा led_classdev_flash *fled_cdev, u32 समयout)
अणु
	काष्ठा led_classdev *led_cdev = &fled_cdev->led_cdev;
	काष्ठा led_flash_setting *s = &fled_cdev->समयout;

	s->val = समयout;
	led_clamp_align(s);

	अगर (!(led_cdev->flags & LED_SUSPENDED))
		वापस call_flash_op(fled_cdev, समयout_set, s->val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_set_flash_समयout);

पूर्णांक led_get_flash_fault(काष्ठा led_classdev_flash *fled_cdev, u32 *fault)
अणु
	वापस call_flash_op(fled_cdev, fault_get, fault);
पूर्ण
EXPORT_SYMBOL_GPL(led_get_flash_fault);

पूर्णांक led_set_flash_brightness(काष्ठा led_classdev_flash *fled_cdev,
				u32 brightness)
अणु
	काष्ठा led_classdev *led_cdev = &fled_cdev->led_cdev;
	काष्ठा led_flash_setting *s = &fled_cdev->brightness;

	s->val = brightness;
	led_clamp_align(s);

	अगर (!(led_cdev->flags & LED_SUSPENDED))
		वापस call_flash_op(fled_cdev, flash_brightness_set, s->val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_set_flash_brightness);

पूर्णांक led_update_flash_brightness(काष्ठा led_classdev_flash *fled_cdev)
अणु
	काष्ठा led_flash_setting *s = &fled_cdev->brightness;
	u32 brightness;

	अगर (has_flash_op(fled_cdev, flash_brightness_get)) अणु
		पूर्णांक ret = call_flash_op(fled_cdev, flash_brightness_get,
						&brightness);
		अगर (ret < 0)
			वापस ret;

		s->val = brightness;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_update_flash_brightness);

MODULE_AUTHOR("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODULE_DESCRIPTION("LED Flash class interface");
MODULE_LICENSE("GPL v2");
