<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Class Core
 *
 * Copyright 2005-2006 Openedhand Ltd.
 *
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <uapi/linux/uleds.h>
#समावेश "leds.h"

DECLARE_RWSEM(leds_list_lock);
EXPORT_SYMBOL_GPL(leds_list_lock);

LIST_HEAD(leds_list);
EXPORT_SYMBOL_GPL(leds_list);

स्थिर अक्षर * स्थिर led_colors[LED_COLOR_ID_MAX] = अणु
	[LED_COLOR_ID_WHITE] = "white",
	[LED_COLOR_ID_RED] = "red",
	[LED_COLOR_ID_GREEN] = "green",
	[LED_COLOR_ID_BLUE] = "blue",
	[LED_COLOR_ID_AMBER] = "amber",
	[LED_COLOR_ID_VIOLET] = "violet",
	[LED_COLOR_ID_YELLOW] = "yellow",
	[LED_COLOR_ID_IR] = "ir",
	[LED_COLOR_ID_MULTI] = "multicolor",
	[LED_COLOR_ID_RGB] = "rgb",
पूर्ण;
EXPORT_SYMBOL_GPL(led_colors);

अटल पूर्णांक __led_set_brightness(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value)
अणु
	अगर (!led_cdev->brightness_set)
		वापस -ENOTSUPP;

	led_cdev->brightness_set(led_cdev, value);

	वापस 0;
पूर्ण

अटल पूर्णांक __led_set_brightness_blocking(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value)
अणु
	अगर (!led_cdev->brightness_set_blocking)
		वापस -ENOTSUPP;

	वापस led_cdev->brightness_set_blocking(led_cdev, value);
पूर्ण

अटल व्योम led_समयr_function(काष्ठा समयr_list *t)
अणु
	काष्ठा led_classdev *led_cdev = from_समयr(led_cdev, t, blink_समयr);
	अचिन्हित दीर्घ brightness;
	अचिन्हित दीर्घ delay;

	अगर (!led_cdev->blink_delay_on || !led_cdev->blink_delay_off) अणु
		led_set_brightness_nosleep(led_cdev, LED_OFF);
		clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(LED_BLINK_ONESHOT_STOP,
			       &led_cdev->work_flags)) अणु
		clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
		वापस;
	पूर्ण

	brightness = led_get_brightness(led_cdev);
	अगर (!brightness) अणु
		/* Time to चयन the LED on. */
		अगर (test_and_clear_bit(LED_BLINK_BRIGHTNESS_CHANGE,
					&led_cdev->work_flags))
			brightness = led_cdev->new_blink_brightness;
		अन्यथा
			brightness = led_cdev->blink_brightness;
		delay = led_cdev->blink_delay_on;
	पूर्ण अन्यथा अणु
		/* Store the current brightness value to be able
		 * to restore it when the delay_off period is over.
		 */
		led_cdev->blink_brightness = brightness;
		brightness = LED_OFF;
		delay = led_cdev->blink_delay_off;
	पूर्ण

	led_set_brightness_nosleep(led_cdev, brightness);

	/* Return in next iteration अगर led is in one-shot mode and we are in
	 * the final blink state so that the led is toggled each delay_on +
	 * delay_off milliseconds in worst हाल.
	 */
	अगर (test_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags)) अणु
		अगर (test_bit(LED_BLINK_INVERT, &led_cdev->work_flags)) अणु
			अगर (brightness)
				set_bit(LED_BLINK_ONESHOT_STOP,
					&led_cdev->work_flags);
		पूर्ण अन्यथा अणु
			अगर (!brightness)
				set_bit(LED_BLINK_ONESHOT_STOP,
					&led_cdev->work_flags);
		पूर्ण
	पूर्ण

	mod_समयr(&led_cdev->blink_समयr, jअगरfies + msecs_to_jअगरfies(delay));
पूर्ण

अटल व्योम set_brightness_delayed(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा led_classdev *led_cdev =
		container_of(ws, काष्ठा led_classdev, set_brightness_work);
	पूर्णांक ret = 0;

	अगर (test_and_clear_bit(LED_BLINK_DISABLE, &led_cdev->work_flags)) अणु
		led_cdev->delayed_set_value = LED_OFF;
		led_stop_software_blink(led_cdev);
	पूर्ण

	ret = __led_set_brightness(led_cdev, led_cdev->delayed_set_value);
	अगर (ret == -ENOTSUPP)
		ret = __led_set_brightness_blocking(led_cdev,
					led_cdev->delayed_set_value);
	अगर (ret < 0 &&
	    /* LED HW might have been unplugged, thereक्रमe करोn't warn */
	    !(ret == -ENODEV && (led_cdev->flags & LED_UNREGISTERING) &&
	    (led_cdev->flags & LED_HW_PLUGGABLE)))
		dev_err(led_cdev->dev,
			"Setting an LED's brightness failed (%d)\n", ret);
पूर्ण

अटल व्योम led_set_software_blink(काष्ठा led_classdev *led_cdev,
				   अचिन्हित दीर्घ delay_on,
				   अचिन्हित दीर्घ delay_off)
अणु
	पूर्णांक current_brightness;

	current_brightness = led_get_brightness(led_cdev);
	अगर (current_brightness)
		led_cdev->blink_brightness = current_brightness;
	अगर (!led_cdev->blink_brightness)
		led_cdev->blink_brightness = led_cdev->max_brightness;

	led_cdev->blink_delay_on = delay_on;
	led_cdev->blink_delay_off = delay_off;

	/* never on - just set to off */
	अगर (!delay_on) अणु
		led_set_brightness_nosleep(led_cdev, LED_OFF);
		वापस;
	पूर्ण

	/* never off - just set to brightness */
	अगर (!delay_off) अणु
		led_set_brightness_nosleep(led_cdev,
					   led_cdev->blink_brightness);
		वापस;
	पूर्ण

	set_bit(LED_BLINK_SW, &led_cdev->work_flags);
	mod_समयr(&led_cdev->blink_समयr, jअगरfies + 1);
पूर्ण


अटल व्योम led_blink_setup(काष्ठा led_classdev *led_cdev,
		     अचिन्हित दीर्घ *delay_on,
		     अचिन्हित दीर्घ *delay_off)
अणु
	अगर (!test_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags) &&
	    led_cdev->blink_set &&
	    !led_cdev->blink_set(led_cdev, delay_on, delay_off))
		वापस;

	/* blink with 1 Hz as शेष अगर nothing specअगरied */
	अगर (!*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	led_set_software_blink(led_cdev, *delay_on, *delay_off);
पूर्ण

व्योम led_init_core(काष्ठा led_classdev *led_cdev)
अणु
	INIT_WORK(&led_cdev->set_brightness_work, set_brightness_delayed);

	समयr_setup(&led_cdev->blink_समयr, led_समयr_function, 0);
पूर्ण
EXPORT_SYMBOL_GPL(led_init_core);

व्योम led_blink_set(काष्ठा led_classdev *led_cdev,
		   अचिन्हित दीर्घ *delay_on,
		   अचिन्हित दीर्घ *delay_off)
अणु
	del_समयr_sync(&led_cdev->blink_समयr);

	clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
	clear_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags);
	clear_bit(LED_BLINK_ONESHOT_STOP, &led_cdev->work_flags);

	led_blink_setup(led_cdev, delay_on, delay_off);
पूर्ण
EXPORT_SYMBOL_GPL(led_blink_set);

व्योम led_blink_set_oneshot(काष्ठा led_classdev *led_cdev,
			   अचिन्हित दीर्घ *delay_on,
			   अचिन्हित दीर्घ *delay_off,
			   पूर्णांक invert)
अणु
	अगर (test_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags) &&
	     समयr_pending(&led_cdev->blink_समयr))
		वापस;

	set_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags);
	clear_bit(LED_BLINK_ONESHOT_STOP, &led_cdev->work_flags);

	अगर (invert)
		set_bit(LED_BLINK_INVERT, &led_cdev->work_flags);
	अन्यथा
		clear_bit(LED_BLINK_INVERT, &led_cdev->work_flags);

	led_blink_setup(led_cdev, delay_on, delay_off);
पूर्ण
EXPORT_SYMBOL_GPL(led_blink_set_oneshot);

व्योम led_stop_software_blink(काष्ठा led_classdev *led_cdev)
अणु
	del_समयr_sync(&led_cdev->blink_समयr);
	led_cdev->blink_delay_on = 0;
	led_cdev->blink_delay_off = 0;
	clear_bit(LED_BLINK_SW, &led_cdev->work_flags);
पूर्ण
EXPORT_SYMBOL_GPL(led_stop_software_blink);

व्योम led_set_brightness(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक brightness)
अणु
	/*
	 * If software blink is active, delay brightness setting
	 * until the next समयr tick.
	 */
	अगर (test_bit(LED_BLINK_SW, &led_cdev->work_flags)) अणु
		/*
		 * If we need to disable soft blinking delegate this to the
		 * work queue task to aव्योम problems in हाल we are called
		 * from hard irq context.
		 */
		अगर (!brightness) अणु
			set_bit(LED_BLINK_DISABLE, &led_cdev->work_flags);
			schedule_work(&led_cdev->set_brightness_work);
		पूर्ण अन्यथा अणु
			set_bit(LED_BLINK_BRIGHTNESS_CHANGE,
				&led_cdev->work_flags);
			led_cdev->new_blink_brightness = brightness;
		पूर्ण
		वापस;
	पूर्ण

	led_set_brightness_nosleep(led_cdev, brightness);
पूर्ण
EXPORT_SYMBOL_GPL(led_set_brightness);

व्योम led_set_brightness_nopm(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value)
अणु
	/* Use brightness_set op अगर available, it is guaranteed not to sleep */
	अगर (!__led_set_brightness(led_cdev, value))
		वापस;

	/* If brightness setting can sleep, delegate it to a work queue task */
	led_cdev->delayed_set_value = value;
	schedule_work(&led_cdev->set_brightness_work);
पूर्ण
EXPORT_SYMBOL_GPL(led_set_brightness_nopm);

व्योम led_set_brightness_nosleep(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value)
अणु
	led_cdev->brightness = min(value, led_cdev->max_brightness);

	अगर (led_cdev->flags & LED_SUSPENDED)
		वापस;

	led_set_brightness_nopm(led_cdev, led_cdev->brightness);
पूर्ण
EXPORT_SYMBOL_GPL(led_set_brightness_nosleep);

पूर्णांक led_set_brightness_sync(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value)
अणु
	अगर (led_cdev->blink_delay_on || led_cdev->blink_delay_off)
		वापस -EBUSY;

	led_cdev->brightness = min(value, led_cdev->max_brightness);

	अगर (led_cdev->flags & LED_SUSPENDED)
		वापस 0;

	वापस __led_set_brightness_blocking(led_cdev, led_cdev->brightness);
पूर्ण
EXPORT_SYMBOL_GPL(led_set_brightness_sync);

पूर्णांक led_update_brightness(काष्ठा led_classdev *led_cdev)
अणु
	पूर्णांक ret = 0;

	अगर (led_cdev->brightness_get) अणु
		ret = led_cdev->brightness_get(led_cdev);
		अगर (ret >= 0) अणु
			led_cdev->brightness = ret;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(led_update_brightness);

u32 *led_get_शेष_pattern(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा fwnode_handle *fwnode = led_cdev->dev->fwnode;
	u32 *pattern;
	पूर्णांक count;

	count = fwnode_property_count_u32(fwnode, "led-pattern");
	अगर (count < 0)
		वापस शून्य;

	pattern = kसुस्मृति(count, माप(*pattern), GFP_KERNEL);
	अगर (!pattern)
		वापस शून्य;

	अगर (fwnode_property_पढ़ो_u32_array(fwnode, "led-pattern", pattern, count)) अणु
		kमुक्त(pattern);
		वापस शून्य;
	पूर्ण

	*size = count;

	वापस pattern;
पूर्ण
EXPORT_SYMBOL_GPL(led_get_शेष_pattern);

/* Caller must ensure led_cdev->led_access held */
व्योम led_sysfs_disable(काष्ठा led_classdev *led_cdev)
अणु
	lockdep_निश्चित_held(&led_cdev->led_access);

	led_cdev->flags |= LED_SYSFS_DISABLE;
पूर्ण
EXPORT_SYMBOL_GPL(led_sysfs_disable);

/* Caller must ensure led_cdev->led_access held */
व्योम led_sysfs_enable(काष्ठा led_classdev *led_cdev)
अणु
	lockdep_निश्चित_held(&led_cdev->led_access);

	led_cdev->flags &= ~LED_SYSFS_DISABLE;
पूर्ण
EXPORT_SYMBOL_GPL(led_sysfs_enable);

अटल व्योम led_parse_fwnode_props(काष्ठा device *dev,
				   काष्ठा fwnode_handle *fwnode,
				   काष्ठा led_properties *props)
अणु
	पूर्णांक ret;

	अगर (!fwnode)
		वापस;

	अगर (fwnode_property_present(fwnode, "label")) अणु
		ret = fwnode_property_पढ़ो_string(fwnode, "label", &props->label);
		अगर (ret)
			dev_err(dev, "Error parsing 'label' property (%d)\n", ret);
		वापस;
	पूर्ण

	अगर (fwnode_property_present(fwnode, "color")) अणु
		ret = fwnode_property_पढ़ो_u32(fwnode, "color", &props->color);
		अगर (ret)
			dev_err(dev, "Error parsing 'color' property (%d)\n", ret);
		अन्यथा अगर (props->color >= LED_COLOR_ID_MAX)
			dev_err(dev, "LED color identifier out of range\n");
		अन्यथा
			props->color_present = true;
	पूर्ण


	अगर (!fwnode_property_present(fwnode, "function"))
		वापस;

	ret = fwnode_property_पढ़ो_string(fwnode, "function", &props->function);
	अगर (ret) अणु
		dev_err(dev,
			"Error parsing 'function' property (%d)\n",
			ret);
	पूर्ण

	अगर (!fwnode_property_present(fwnode, "function-enumerator"))
		वापस;

	ret = fwnode_property_पढ़ो_u32(fwnode, "function-enumerator",
				       &props->func_क्रमागत);
	अगर (ret) अणु
		dev_err(dev,
			"Error parsing 'function-enumerator' property (%d)\n",
			ret);
	पूर्ण अन्यथा अणु
		props->func_क्रमागत_present = true;
	पूर्ण
पूर्ण

पूर्णांक led_compose_name(काष्ठा device *dev, काष्ठा led_init_data *init_data,
		     अक्षर *led_classdev_name)
अणु
	काष्ठा led_properties props = अणुपूर्ण;
	काष्ठा fwnode_handle *fwnode = init_data->fwnode;
	स्थिर अक्षर *devicename = init_data->devicename;

	/* We want to label LEDs that can produce full range of colors
	 * as RGB, not multicolor */
	BUG_ON(props.color == LED_COLOR_ID_MULTI);

	अगर (!led_classdev_name)
		वापस -EINVAL;

	led_parse_fwnode_props(dev, fwnode, &props);

	अगर (props.label) अणु
		/*
		 * If init_data.devicename is शून्य, then it indicates that
		 * DT label should be used as-is क्रम LED class device name.
		 * Otherwise the label is prepended with devicename to compose
		 * the final LED class device name.
		 */
		अगर (!devicename) अणु
			strscpy(led_classdev_name, props.label,
				LED_MAX_NAME_SIZE);
		पूर्ण अन्यथा अणु
			snम_लिखो(led_classdev_name, LED_MAX_NAME_SIZE, "%s:%s",
				 devicename, props.label);
		पूर्ण
	पूर्ण अन्यथा अगर (props.function || props.color_present) अणु
		अक्षर पंचांगp_buf[LED_MAX_NAME_SIZE];

		अगर (props.func_क्रमागत_present) अणु
			snम_लिखो(पंचांगp_buf, LED_MAX_NAME_SIZE, "%s:%s-%d",
				 props.color_present ? led_colors[props.color] : "",
				 props.function ?: "", props.func_क्रमागत);
		पूर्ण अन्यथा अणु
			snम_लिखो(पंचांगp_buf, LED_MAX_NAME_SIZE, "%s:%s",
				 props.color_present ? led_colors[props.color] : "",
				 props.function ?: "");
		पूर्ण
		अगर (init_data->devname_mandatory) अणु
			snम_लिखो(led_classdev_name, LED_MAX_NAME_SIZE, "%s:%s",
				 devicename, पंचांगp_buf);
		पूर्ण अन्यथा अणु
			strscpy(led_classdev_name, पंचांगp_buf, LED_MAX_NAME_SIZE);

		पूर्ण
	पूर्ण अन्यथा अगर (init_data->शेष_label) अणु
		अगर (!devicename) अणु
			dev_err(dev, "Legacy LED naming requires devicename segment");
			वापस -EINVAL;
		पूर्ण
		snम_लिखो(led_classdev_name, LED_MAX_NAME_SIZE, "%s:%s",
			 devicename, init_data->शेष_label);
	पूर्ण अन्यथा अगर (is_of_node(fwnode)) अणु
		strscpy(led_classdev_name, to_of_node(fwnode)->name,
			LED_MAX_NAME_SIZE);
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_compose_name);
