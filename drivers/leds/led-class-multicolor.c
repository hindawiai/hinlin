<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// LED Multicolor class पूर्णांकerface
// Copyright (C) 2019-20 Texas Instruments Incorporated - http://www.ti.com/
// Author: Dan Murphy <dmurphy@ti.com>

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/led-class-multicolor.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "leds.h"

पूर्णांक led_mc_calc_color_components(काष्ठा led_classdev_mc *mcled_cdev,
				 क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev *led_cdev = &mcled_cdev->led_cdev;
	पूर्णांक i;

	क्रम (i = 0; i < mcled_cdev->num_colors; i++)
		mcled_cdev->subled_info[i].brightness = brightness *
					mcled_cdev->subled_info[i].पूर्णांकensity /
					led_cdev->max_brightness;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_mc_calc_color_components);

अटल sमाप_प्रकार multi_पूर्णांकensity_store(काष्ठा device *dev,
				काष्ठा device_attribute *पूर्णांकensity_attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_mc *mcled_cdev = lcdev_to_mccdev(led_cdev);
	पूर्णांक nrअक्षरs, offset = 0;
	पूर्णांक पूर्णांकensity_value[LED_COLOR_ID_MAX];
	पूर्णांक i;
	sमाप_प्रकार ret;

	mutex_lock(&led_cdev->led_access);

	क्रम (i = 0; i < mcled_cdev->num_colors; i++) अणु
		ret = माला_पूछो(buf + offset, "%i%n",
			     &पूर्णांकensity_value[i], &nrअक्षरs);
		अगर (ret != 1) अणु
			ret = -EINVAL;
			जाओ err_out;
		पूर्ण
		offset += nrअक्षरs;
	पूर्ण

	offset++;
	अगर (offset < size) अणु
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	क्रम (i = 0; i < mcled_cdev->num_colors; i++)
		mcled_cdev->subled_info[i].पूर्णांकensity = पूर्णांकensity_value[i];

	led_set_brightness(led_cdev, led_cdev->brightness);
	ret = size;
err_out:
	mutex_unlock(&led_cdev->led_access);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार multi_पूर्णांकensity_show(काष्ठा device *dev,
			      काष्ठा device_attribute *पूर्णांकensity_attr,
			      अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_mc *mcled_cdev = lcdev_to_mccdev(led_cdev);
	पूर्णांक len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < mcled_cdev->num_colors; i++) अणु
		len += प्र_लिखो(buf + len, "%d",
			       mcled_cdev->subled_info[i].पूर्णांकensity);
		अगर (i < mcled_cdev->num_colors - 1)
			len += प्र_लिखो(buf + len, " ");
	पूर्ण

	buf[len++] = '\n';
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(multi_पूर्णांकensity);

अटल sमाप_प्रकार multi_index_show(काष्ठा device *dev,
			      काष्ठा device_attribute *multi_index_attr,
			      अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_classdev_mc *mcled_cdev = lcdev_to_mccdev(led_cdev);
	पूर्णांक len = 0;
	पूर्णांक index;
	पूर्णांक i;

	क्रम (i = 0; i < mcled_cdev->num_colors; i++) अणु
		index = mcled_cdev->subled_info[i].color_index;
		len += प्र_लिखो(buf + len, "%s", led_colors[index]);
		अगर (i < mcled_cdev->num_colors - 1)
			len += प्र_लिखो(buf + len, " ");
	पूर्ण

	buf[len++] = '\n';
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(multi_index);

अटल काष्ठा attribute *led_multicolor_attrs[] = अणु
	&dev_attr_multi_पूर्णांकensity.attr,
	&dev_attr_multi_index.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(led_multicolor);

पूर्णांक led_classdev_multicolor_रेजिस्टर_ext(काष्ठा device *parent,
				     काष्ठा led_classdev_mc *mcled_cdev,
				     काष्ठा led_init_data *init_data)
अणु
	काष्ठा led_classdev *led_cdev;

	अगर (!mcled_cdev)
		वापस -EINVAL;

	अगर (mcled_cdev->num_colors <= 0)
		वापस -EINVAL;

	अगर (mcled_cdev->num_colors > LED_COLOR_ID_MAX)
		वापस -EINVAL;

	led_cdev = &mcled_cdev->led_cdev;
	mcled_cdev->led_cdev.groups = led_multicolor_groups;

	वापस led_classdev_रेजिस्टर_ext(parent, led_cdev, init_data);
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_multicolor_रेजिस्टर_ext);

व्योम led_classdev_multicolor_unरेजिस्टर(काष्ठा led_classdev_mc *mcled_cdev)
अणु
	अगर (!mcled_cdev)
		वापस;

	led_classdev_unरेजिस्टर(&mcled_cdev->led_cdev);
पूर्ण
EXPORT_SYMBOL_GPL(led_classdev_multicolor_unरेजिस्टर);

अटल व्योम devm_led_classdev_multicolor_release(काष्ठा device *dev, व्योम *res)
अणु
	led_classdev_multicolor_unरेजिस्टर(*(काष्ठा led_classdev_mc **)res);
पूर्ण

पूर्णांक devm_led_classdev_multicolor_रेजिस्टर_ext(काष्ठा device *parent,
					     काष्ठा led_classdev_mc *mcled_cdev,
					     काष्ठा led_init_data *init_data)
अणु
	काष्ठा led_classdev_mc **dr;
	पूर्णांक ret;

	dr = devres_alloc(devm_led_classdev_multicolor_release,
			  माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = led_classdev_multicolor_रेजिस्टर_ext(parent, mcled_cdev,
						   init_data);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	*dr = mcled_cdev;
	devres_add(parent, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_led_classdev_multicolor_रेजिस्टर_ext);

अटल पूर्णांक devm_led_classdev_multicolor_match(काष्ठा device *dev,
					      व्योम *res, व्योम *data)
अणु
	काष्ठा led_classdev_mc **p = res;

	अगर (WARN_ON(!p || !*p))
		वापस 0;

	वापस *p == data;
पूर्ण

व्योम devm_led_classdev_multicolor_unरेजिस्टर(काष्ठा device *dev,
					     काष्ठा led_classdev_mc *mcled_cdev)
अणु
	WARN_ON(devres_release(dev,
			       devm_led_classdev_multicolor_release,
			       devm_led_classdev_multicolor_match, mcled_cdev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_led_classdev_multicolor_unरेजिस्टर);

MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_DESCRIPTION("Multicolor LED class interface");
MODULE_LICENSE("GPL v2");
