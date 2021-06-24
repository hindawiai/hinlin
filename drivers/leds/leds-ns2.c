<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * leds-ns2.c - Driver क्रम the Network Space v2 (and parents) dual-GPIO LED
 *
 * Copyright (C) 2010 LaCie
 *
 * Author: Simon Guinot <sguinot@lacie.com>
 *
 * Based on leds-gpio.c by Raphael Assenat <raph@8d.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश "leds.h"

क्रमागत ns2_led_modes अणु
	NS_V2_LED_OFF,
	NS_V2_LED_ON,
	NS_V2_LED_SATA,
पूर्ण;

/*
 * If the size of this काष्ठाure or types of its members is changed,
 * the filling of array modval in function ns2_led_रेजिस्टर must be changed
 * accordingly.
 */
काष्ठा ns2_led_modval अणु
	u32			mode;
	u32			cmd_level;
	u32			slow_level;
पूर्ण __packed;

/*
 * The Network Space v2 dual-GPIO LED is wired to a CPLD. Three dअगरferent LED
 * modes are available: off, on and SATA activity blinking. The LED modes are
 * controlled through two GPIOs (command and slow): each combination of values
 * क्रम the command/slow GPIOs corresponds to a LED mode.
 */

काष्ठा ns2_led अणु
	काष्ठा led_classdev	cdev;
	काष्ठा gpio_desc	*cmd;
	काष्ठा gpio_desc	*slow;
	bool			can_sleep;
	अचिन्हित अक्षर		sata; /* True when SATA mode active. */
	rwlock_t		rw_lock; /* Lock GPIOs. */
	पूर्णांक			num_modes;
	काष्ठा ns2_led_modval	*modval;
पूर्ण;

अटल पूर्णांक ns2_led_get_mode(काष्ठा ns2_led *led, क्रमागत ns2_led_modes *mode)
अणु
	पूर्णांक i;
	पूर्णांक cmd_level;
	पूर्णांक slow_level;

	cmd_level = gpiod_get_value_cansleep(led->cmd);
	slow_level = gpiod_get_value_cansleep(led->slow);

	क्रम (i = 0; i < led->num_modes; i++) अणु
		अगर (cmd_level == led->modval[i].cmd_level &&
		    slow_level == led->modval[i].slow_level) अणु
			*mode = led->modval[i].mode;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम ns2_led_set_mode(काष्ठा ns2_led *led, क्रमागत ns2_led_modes mode)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < led->num_modes; i++)
		अगर (mode == led->modval[i].mode)
			अवरोध;

	अगर (i == led->num_modes)
		वापस;

	ग_लिखो_lock_irqsave(&led->rw_lock, flags);

	अगर (!led->can_sleep) अणु
		gpiod_set_value(led->cmd, led->modval[i].cmd_level);
		gpiod_set_value(led->slow, led->modval[i].slow_level);
		जाओ निकास_unlock;
	पूर्ण

	gpiod_set_value_cansleep(led->cmd, led->modval[i].cmd_level);
	gpiod_set_value_cansleep(led->slow, led->modval[i].slow_level);

निकास_unlock:
	ग_लिखो_unlock_irqrestore(&led->rw_lock, flags);
पूर्ण

अटल व्योम ns2_led_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा ns2_led *led = container_of(led_cdev, काष्ठा ns2_led, cdev);
	क्रमागत ns2_led_modes mode;

	अगर (value == LED_OFF)
		mode = NS_V2_LED_OFF;
	अन्यथा अगर (led->sata)
		mode = NS_V2_LED_SATA;
	अन्यथा
		mode = NS_V2_LED_ON;

	ns2_led_set_mode(led, mode);
पूर्ण

अटल पूर्णांक ns2_led_set_blocking(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	ns2_led_set(led_cdev, value);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ns2_led_sata_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buff, माप_प्रकार count)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा ns2_led *led = container_of(led_cdev, काष्ठा ns2_led, cdev);
	पूर्णांक ret;
	अचिन्हित दीर्घ enable;

	ret = kम_से_अदीर्घ(buff, 10, &enable);
	अगर (ret < 0)
		वापस ret;

	enable = !!enable;

	अगर (led->sata == enable)
		जाओ निकास;

	led->sata = enable;

	अगर (!led_get_brightness(led_cdev))
		जाओ निकास;

	अगर (enable)
		ns2_led_set_mode(led, NS_V2_LED_SATA);
	अन्यथा
		ns2_led_set_mode(led, NS_V2_LED_ON);

निकास:
	वापस count;
पूर्ण

अटल sमाप_प्रकार ns2_led_sata_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा ns2_led *led = container_of(led_cdev, काष्ठा ns2_led, cdev);

	वापस प्र_लिखो(buf, "%d\n", led->sata);
पूर्ण

अटल DEVICE_ATTR(sata, 0644, ns2_led_sata_show, ns2_led_sata_store);

अटल काष्ठा attribute *ns2_led_attrs[] = अणु
	&dev_attr_sata.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(ns2_led);

अटल पूर्णांक ns2_led_रेजिस्टर(काष्ठा device *dev, काष्ठा fwnode_handle *node,
			    काष्ठा ns2_led *led)
अणु
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा ns2_led_modval *modval;
	क्रमागत ns2_led_modes mode;
	पूर्णांक nmodes, ret;

	led->cmd = devm_fwnode_gpiod_get_index(dev, node, "cmd", 0, GPIOD_ASIS,
					       fwnode_get_name(node));
	अगर (IS_ERR(led->cmd))
		वापस PTR_ERR(led->cmd);

	led->slow = devm_fwnode_gpiod_get_index(dev, node, "slow", 0,
						GPIOD_ASIS,
						fwnode_get_name(node));
	अगर (IS_ERR(led->slow))
		वापस PTR_ERR(led->slow);

	ret = fwnode_property_count_u32(node, "modes-map");
	अगर (ret < 0 || ret % 3) अणु
		dev_err(dev, "Missing or malformed modes-map for %pfw\n", node);
		वापस -EINVAL;
	पूर्ण

	nmodes = ret / 3;
	modval = devm_kसुस्मृति(dev, nmodes, माप(*modval), GFP_KERNEL);
	अगर (!modval)
		वापस -ENOMEM;

	fwnode_property_पढ़ो_u32_array(node, "modes-map", (व्योम *)modval,
				       nmodes * 3);

	rwlock_init(&led->rw_lock);

	led->cdev.blink_set = शून्य;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->cdev.groups = ns2_led_groups;
	led->can_sleep = gpiod_cansleep(led->cmd) || gpiod_cansleep(led->slow);
	अगर (led->can_sleep)
		led->cdev.brightness_set_blocking = ns2_led_set_blocking;
	अन्यथा
		led->cdev.brightness_set = ns2_led_set;
	led->num_modes = nmodes;
	led->modval = modval;

	ret = ns2_led_get_mode(led, &mode);
	अगर (ret < 0)
		वापस ret;

	/* Set LED initial state. */
	led->sata = (mode == NS_V2_LED_SATA) ? 1 : 0;
	led->cdev.brightness = (mode == NS_V2_LED_OFF) ? LED_OFF : LED_FULL;

	init_data.fwnode = node;

	ret = devm_led_classdev_रेजिस्टर_ext(dev, &led->cdev, &init_data);
	अगर (ret)
		dev_err(dev, "Failed to register LED for node %pfw\n", node);

	वापस ret;
पूर्ण

अटल पूर्णांक ns2_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fwnode_handle *child;
	काष्ठा ns2_led *leds;
	पूर्णांक count;
	पूर्णांक ret;

	count = device_get_child_node_count(dev);
	अगर (!count)
		वापस -ENODEV;

	leds = devm_kzalloc(dev, array_size(माप(*leds), count), GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	device_क्रम_each_child_node(dev, child) अणु
		ret = ns2_led_रेजिस्टर(dev, child, leds++);
		अगर (ret) अणु
			fwnode_handle_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_ns2_leds_match[] = अणु
	अणु .compatible = "lacie,ns2-leds", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ns2_leds_match);

अटल काष्ठा platक्रमm_driver ns2_led_driver = अणु
	.probe		= ns2_led_probe,
	.driver		= अणु
		.name		= "leds-ns2",
		.of_match_table	= of_ns2_leds_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ns2_led_driver);

MODULE_AUTHOR("Simon Guinot <sguinot@lacie.com>");
MODULE_DESCRIPTION("Network Space v2 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-ns2");
