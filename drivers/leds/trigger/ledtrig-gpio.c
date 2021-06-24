<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ledtrig-gio.c - LED Trigger Based on GPIO events
 *
 * Copyright 2009 Felipe Balbi <me@felipebalbi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश "../leds.h"

काष्ठा gpio_trig_data अणु
	काष्ठा led_classdev *led;

	अचिन्हित desired_brightness;	/* desired brightness when led is on */
	अचिन्हित inverted;		/* true when gpio is inverted */
	अचिन्हित gpio;			/* gpio that triggers the leds */
पूर्ण;

अटल irqवापस_t gpio_trig_irq(पूर्णांक irq, व्योम *_led)
अणु
	काष्ठा led_classdev *led = _led;
	काष्ठा gpio_trig_data *gpio_data = led_get_trigger_data(led);
	पूर्णांक पंचांगp;

	पंचांगp = gpio_get_value_cansleep(gpio_data->gpio);
	अगर (gpio_data->inverted)
		पंचांगp = !पंचांगp;

	अगर (पंचांगp) अणु
		अगर (gpio_data->desired_brightness)
			led_set_brightness_nosleep(gpio_data->led,
					   gpio_data->desired_brightness);
		अन्यथा
			led_set_brightness_nosleep(gpio_data->led, LED_FULL);
	पूर्ण अन्यथा अणु
		led_set_brightness_nosleep(gpio_data->led, LED_OFF);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार gpio_trig_brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_trig_data *gpio_data = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", gpio_data->desired_brightness);
पूर्ण

अटल sमाप_प्रकार gpio_trig_brightness_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा gpio_trig_data *gpio_data = led_trigger_get_drvdata(dev);
	अचिन्हित desired_brightness;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &desired_brightness);
	अगर (ret < 1 || desired_brightness > 255) अणु
		dev_err(dev, "invalid value\n");
		वापस -EINVAL;
	पूर्ण

	gpio_data->desired_brightness = desired_brightness;

	वापस n;
पूर्ण
अटल DEVICE_ATTR(desired_brightness, 0644, gpio_trig_brightness_show,
		gpio_trig_brightness_store);

अटल sमाप_प्रकार gpio_trig_inverted_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_trig_data *gpio_data = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", gpio_data->inverted);
पूर्ण

अटल sमाप_प्रकार gpio_trig_inverted_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा led_classdev *led = led_trigger_get_led(dev);
	काष्ठा gpio_trig_data *gpio_data = led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ inverted;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &inverted);
	अगर (ret < 0)
		वापस ret;

	अगर (inverted > 1)
		वापस -EINVAL;

	gpio_data->inverted = inverted;

	/* After inverting, we need to update the LED. */
	अगर (gpio_is_valid(gpio_data->gpio))
		gpio_trig_irq(0, led);

	वापस n;
पूर्ण
अटल DEVICE_ATTR(inverted, 0644, gpio_trig_inverted_show,
		gpio_trig_inverted_store);

अटल sमाप_प्रकार gpio_trig_gpio_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gpio_trig_data *gpio_data = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", gpio_data->gpio);
पूर्ण

अटल sमाप_प्रकार gpio_trig_gpio_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा led_classdev *led = led_trigger_get_led(dev);
	काष्ठा gpio_trig_data *gpio_data = led_trigger_get_drvdata(dev);
	अचिन्हित gpio;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &gpio);
	अगर (ret < 1) अणु
		dev_err(dev, "couldn't read gpio number\n");
		वापस -EINVAL;
	पूर्ण

	अगर (gpio_data->gpio == gpio)
		वापस n;

	अगर (!gpio_is_valid(gpio)) अणु
		अगर (gpio_is_valid(gpio_data->gpio))
			मुक्त_irq(gpio_to_irq(gpio_data->gpio), led);
		gpio_data->gpio = gpio;
		वापस n;
	पूर्ण

	ret = request_thपढ़ोed_irq(gpio_to_irq(gpio), शून्य, gpio_trig_irq,
			IRQF_ONESHOT | IRQF_SHARED | IRQF_TRIGGER_RISING
			| IRQF_TRIGGER_FALLING, "ledtrig-gpio", led);
	अगर (ret) अणु
		dev_err(dev, "request_irq failed with error %d\n", ret);
	पूर्ण अन्यथा अणु
		अगर (gpio_is_valid(gpio_data->gpio))
			मुक्त_irq(gpio_to_irq(gpio_data->gpio), led);
		gpio_data->gpio = gpio;
		/* After changing the GPIO, we need to update the LED. */
		gpio_trig_irq(0, led);
	पूर्ण

	वापस ret ? ret : n;
पूर्ण
अटल DEVICE_ATTR(gpio, 0644, gpio_trig_gpio_show, gpio_trig_gpio_store);

अटल काष्ठा attribute *gpio_trig_attrs[] = अणु
	&dev_attr_desired_brightness.attr,
	&dev_attr_inverted.attr,
	&dev_attr_gpio.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(gpio_trig);

अटल पूर्णांक gpio_trig_activate(काष्ठा led_classdev *led)
अणु
	काष्ठा gpio_trig_data *gpio_data;

	gpio_data = kzalloc(माप(*gpio_data), GFP_KERNEL);
	अगर (!gpio_data)
		वापस -ENOMEM;

	gpio_data->led = led;
	gpio_data->gpio = -ENOENT;

	led_set_trigger_data(led, gpio_data);

	वापस 0;
पूर्ण

अटल व्योम gpio_trig_deactivate(काष्ठा led_classdev *led)
अणु
	काष्ठा gpio_trig_data *gpio_data = led_get_trigger_data(led);

	अगर (gpio_is_valid(gpio_data->gpio))
		मुक्त_irq(gpio_to_irq(gpio_data->gpio), led);
	kमुक्त(gpio_data);
पूर्ण

अटल काष्ठा led_trigger gpio_led_trigger = अणु
	.name		= "gpio",
	.activate	= gpio_trig_activate,
	.deactivate	= gpio_trig_deactivate,
	.groups		= gpio_trig_groups,
पूर्ण;
module_led_trigger(gpio_led_trigger);

MODULE_AUTHOR("Felipe Balbi <me@felipebalbi.com>");
MODULE_DESCRIPTION("GPIO LED trigger");
MODULE_LICENSE("GPL v2");
