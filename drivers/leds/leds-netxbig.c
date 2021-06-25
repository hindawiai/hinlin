<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * leds-netxbig.c - Driver क्रम the 2Big and 5Big Network series LEDs
 *
 * Copyright (C) 2010 LaCie
 *
 * Author: Simon Guinot <sguinot@lacie.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/leds.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

काष्ठा netxbig_gpio_ext अणु
	काष्ठा gpio_desc **addr;
	पूर्णांक		num_addr;
	काष्ठा gpio_desc **data;
	पूर्णांक		num_data;
	काष्ठा gpio_desc *enable;
पूर्ण;

क्रमागत netxbig_led_mode अणु
	NETXBIG_LED_OFF,
	NETXBIG_LED_ON,
	NETXBIG_LED_SATA,
	NETXBIG_LED_TIMER1,
	NETXBIG_LED_TIMER2,
	NETXBIG_LED_MODE_NUM,
पूर्ण;

#घोषणा NETXBIG_LED_INVALID_MODE NETXBIG_LED_MODE_NUM

काष्ठा netxbig_led_समयr अणु
	अचिन्हित दीर्घ		delay_on;
	अचिन्हित दीर्घ		delay_off;
	क्रमागत netxbig_led_mode	mode;
पूर्ण;

काष्ठा netxbig_led अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*शेष_trigger;
	पूर्णांक		mode_addr;
	पूर्णांक		*mode_val;
	पूर्णांक		bright_addr;
	पूर्णांक		bright_max;
पूर्ण;

काष्ठा netxbig_led_platक्रमm_data अणु
	काष्ठा netxbig_gpio_ext	*gpio_ext;
	काष्ठा netxbig_led_समयr *समयr;
	पूर्णांक			num_समयr;
	काष्ठा netxbig_led	*leds;
	पूर्णांक			num_leds;
पूर्ण;

/*
 * GPIO extension bus.
 */

अटल DEFINE_SPINLOCK(gpio_ext_lock);

अटल व्योम gpio_ext_set_addr(काष्ठा netxbig_gpio_ext *gpio_ext, पूर्णांक addr)
अणु
	पूर्णांक pin;

	क्रम (pin = 0; pin < gpio_ext->num_addr; pin++)
		gpiod_set_value(gpio_ext->addr[pin], (addr >> pin) & 1);
पूर्ण

अटल व्योम gpio_ext_set_data(काष्ठा netxbig_gpio_ext *gpio_ext, पूर्णांक data)
अणु
	पूर्णांक pin;

	क्रम (pin = 0; pin < gpio_ext->num_data; pin++)
		gpiod_set_value(gpio_ext->data[pin], (data >> pin) & 1);
पूर्ण

अटल व्योम gpio_ext_enable_select(काष्ठा netxbig_gpio_ext *gpio_ext)
अणु
	/* Enable select is करोne on the raising edge. */
	gpiod_set_value(gpio_ext->enable, 0);
	gpiod_set_value(gpio_ext->enable, 1);
पूर्ण

अटल व्योम gpio_ext_set_value(काष्ठा netxbig_gpio_ext *gpio_ext,
			       पूर्णांक addr, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_ext_lock, flags);
	gpio_ext_set_addr(gpio_ext, addr);
	gpio_ext_set_data(gpio_ext, value);
	gpio_ext_enable_select(gpio_ext);
	spin_unlock_irqrestore(&gpio_ext_lock, flags);
पूर्ण

/*
 * Class LED driver.
 */

काष्ठा netxbig_led_data अणु
	काष्ठा netxbig_gpio_ext	*gpio_ext;
	काष्ठा led_classdev	cdev;
	पूर्णांक			mode_addr;
	पूर्णांक			*mode_val;
	पूर्णांक			bright_addr;
	काष्ठा			netxbig_led_समयr *समयr;
	पूर्णांक			num_समयr;
	क्रमागत netxbig_led_mode	mode;
	पूर्णांक			sata;
	spinlock_t		lock;
पूर्ण;

अटल पूर्णांक netxbig_led_get_समयr_mode(क्रमागत netxbig_led_mode *mode,
				      अचिन्हित दीर्घ delay_on,
				      अचिन्हित दीर्घ delay_off,
				      काष्ठा netxbig_led_समयr *समयr,
				      पूर्णांक num_समयr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_समयr; i++) अणु
		अगर (समयr[i].delay_on == delay_on &&
		    समयr[i].delay_off == delay_off) अणु
			*mode = समयr[i].mode;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक netxbig_led_blink_set(काष्ठा led_classdev *led_cdev,
				 अचिन्हित दीर्घ *delay_on,
				 अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा netxbig_led_data *led_dat =
		container_of(led_cdev, काष्ठा netxbig_led_data, cdev);
	क्रमागत netxbig_led_mode mode;
	पूर्णांक mode_val;
	पूर्णांक ret;

	/* Look क्रम a LED mode with the requested समयr frequency. */
	ret = netxbig_led_get_समयr_mode(&mode, *delay_on, *delay_off,
					 led_dat->समयr, led_dat->num_समयr);
	अगर (ret < 0)
		वापस ret;

	mode_val = led_dat->mode_val[mode];
	अगर (mode_val == NETXBIG_LED_INVALID_MODE)
		वापस -EINVAL;

	spin_lock_irq(&led_dat->lock);

	gpio_ext_set_value(led_dat->gpio_ext, led_dat->mode_addr, mode_val);
	led_dat->mode = mode;

	spin_unlock_irq(&led_dat->lock);

	वापस 0;
पूर्ण

अटल व्योम netxbig_led_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	काष्ठा netxbig_led_data *led_dat =
		container_of(led_cdev, काष्ठा netxbig_led_data, cdev);
	क्रमागत netxbig_led_mode mode;
	पूर्णांक mode_val;
	पूर्णांक set_brightness = 1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&led_dat->lock, flags);

	अगर (value == LED_OFF) अणु
		mode = NETXBIG_LED_OFF;
		set_brightness = 0;
	पूर्ण अन्यथा अणु
		अगर (led_dat->sata)
			mode = NETXBIG_LED_SATA;
		अन्यथा अगर (led_dat->mode == NETXBIG_LED_OFF)
			mode = NETXBIG_LED_ON;
		अन्यथा /* Keep 'timer' mode. */
			mode = led_dat->mode;
	पूर्ण
	mode_val = led_dat->mode_val[mode];

	gpio_ext_set_value(led_dat->gpio_ext, led_dat->mode_addr, mode_val);
	led_dat->mode = mode;
	/*
	 * Note that the brightness रेजिस्टर is shared between all the
	 * SATA LEDs. So, change the brightness setting क्रम a single
	 * SATA LED will affect all the others.
	 */
	अगर (set_brightness)
		gpio_ext_set_value(led_dat->gpio_ext,
				   led_dat->bright_addr, value);

	spin_unlock_irqrestore(&led_dat->lock, flags);
पूर्ण

अटल sमाप_प्रकार sata_store(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buff, माप_प्रकार count)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा netxbig_led_data *led_dat =
		container_of(led_cdev, काष्ठा netxbig_led_data, cdev);
	अचिन्हित दीर्घ enable;
	क्रमागत netxbig_led_mode mode;
	पूर्णांक mode_val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buff, 10, &enable);
	अगर (ret < 0)
		वापस ret;

	enable = !!enable;

	spin_lock_irq(&led_dat->lock);

	अगर (led_dat->sata == enable) अणु
		ret = count;
		जाओ निकास_unlock;
	पूर्ण

	अगर (led_dat->mode != NETXBIG_LED_ON &&
	    led_dat->mode != NETXBIG_LED_SATA)
		mode = led_dat->mode; /* Keep modes 'off' and 'timer'. */
	अन्यथा अगर (enable)
		mode = NETXBIG_LED_SATA;
	अन्यथा
		mode = NETXBIG_LED_ON;

	mode_val = led_dat->mode_val[mode];
	अगर (mode_val == NETXBIG_LED_INVALID_MODE) अणु
		ret = -EINVAL;
		जाओ निकास_unlock;
	पूर्ण

	gpio_ext_set_value(led_dat->gpio_ext, led_dat->mode_addr, mode_val);
	led_dat->mode = mode;
	led_dat->sata = enable;

	ret = count;

निकास_unlock:
	spin_unlock_irq(&led_dat->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार sata_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा netxbig_led_data *led_dat =
		container_of(led_cdev, काष्ठा netxbig_led_data, cdev);

	वापस प्र_लिखो(buf, "%d\n", led_dat->sata);
पूर्ण

अटल DEVICE_ATTR_RW(sata);

अटल काष्ठा attribute *netxbig_led_attrs[] = अणु
	&dev_attr_sata.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(netxbig_led);

अटल पूर्णांक create_netxbig_led(काष्ठा platक्रमm_device *pdev,
			      काष्ठा netxbig_led_platक्रमm_data *pdata,
			      काष्ठा netxbig_led_data *led_dat,
			      स्थिर काष्ठा netxbig_led *ढाँचा)
अणु
	spin_lock_init(&led_dat->lock);
	led_dat->gpio_ext = pdata->gpio_ext;
	led_dat->cdev.name = ढाँचा->name;
	led_dat->cdev.शेष_trigger = ढाँचा->शेष_trigger;
	led_dat->cdev.blink_set = netxbig_led_blink_set;
	led_dat->cdev.brightness_set = netxbig_led_set;
	/*
	 * Because the GPIO extension bus करोn't allow to पढ़ो रेजिस्टरs
	 * value, there is no way to probe the LED initial state.
	 * So, the initial sysfs LED value क्रम the "brightness" and "sata"
	 * attributes are inconsistent.
	 *
	 * Note that the initial LED state can't be reconfigured.
	 * The reason is that the LED behaviour must stay unअगरorm during
	 * the whole boot process (bootloader+linux).
	 */
	led_dat->sata = 0;
	led_dat->cdev.brightness = LED_OFF;
	led_dat->cdev.max_brightness = ढाँचा->bright_max;
	led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led_dat->mode_addr = ढाँचा->mode_addr;
	led_dat->mode_val = ढाँचा->mode_val;
	led_dat->bright_addr = ढाँचा->bright_addr;
	led_dat->समयr = pdata->समयr;
	led_dat->num_समयr = pdata->num_समयr;
	/*
	 * If available, expose the SATA activity blink capability through
	 * a "sata" sysfs attribute.
	 */
	अगर (led_dat->mode_val[NETXBIG_LED_SATA] != NETXBIG_LED_INVALID_MODE)
		led_dat->cdev.groups = netxbig_led_groups;

	वापस devm_led_classdev_रेजिस्टर(&pdev->dev, &led_dat->cdev);
पूर्ण

/**
 * netxbig_gpio_ext_हटाओ() - Clean up GPIO extension data
 * @data: managed resource data to clean up
 *
 * Since we pick GPIO descriptors from another device than the device our
 * driver is probing to, we need to रेजिस्टर a specअगरic callback to मुक्त
 * these up using managed resources.
 */
अटल व्योम netxbig_gpio_ext_हटाओ(व्योम *data)
अणु
	काष्ठा netxbig_gpio_ext *gpio_ext = data;
	पूर्णांक i;

	क्रम (i = 0; i < gpio_ext->num_addr; i++)
		gpiod_put(gpio_ext->addr[i]);
	क्रम (i = 0; i < gpio_ext->num_data; i++)
		gpiod_put(gpio_ext->data[i]);
	gpiod_put(gpio_ext->enable);
पूर्ण

/**
 * netxbig_gpio_ext_get() - Obtain GPIO extension device data
 * @dev: मुख्य LED device
 * @gpio_ext_dev: the GPIO extension device
 * @gpio_ext: the data काष्ठाure holding the GPIO extension data
 *
 * This function walks the subdevice that only contain GPIO line
 * handles in the device tree and obtains the GPIO descriptors from that
 * device.
 */
अटल पूर्णांक netxbig_gpio_ext_get(काष्ठा device *dev,
				काष्ठा device *gpio_ext_dev,
				काष्ठा netxbig_gpio_ext *gpio_ext)
अणु
	काष्ठा gpio_desc **addr, **data;
	पूर्णांक num_addr, num_data;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक ret;
	पूर्णांक i;

	ret = gpiod_count(gpio_ext_dev, "addr");
	अगर (ret < 0) अणु
		dev_err(dev,
			"Failed to count GPIOs in DT property addr-gpios\n");
		वापस ret;
	पूर्ण
	num_addr = ret;
	addr = devm_kसुस्मृति(dev, num_addr, माप(*addr), GFP_KERNEL);
	अगर (!addr)
		वापस -ENOMEM;

	/*
	 * We cannot use devm_ managed resources with these GPIO descriptors
	 * since they are associated with the "GPIO extension device" which
	 * करोes not probe any driver. The device tree parser will however
	 * populate a platक्रमm device क्रम it so we can anyway obtain the
	 * GPIO descriptors from the device.
	 */
	क्रम (i = 0; i < num_addr; i++) अणु
		gpiod = gpiod_get_index(gpio_ext_dev, "addr", i,
					GPIOD_OUT_LOW);
		अगर (IS_ERR(gpiod))
			वापस PTR_ERR(gpiod);
		gpiod_set_consumer_name(gpiod, "GPIO extension addr");
		addr[i] = gpiod;
	पूर्ण
	gpio_ext->addr = addr;
	gpio_ext->num_addr = num_addr;

	ret = gpiod_count(gpio_ext_dev, "data");
	अगर (ret < 0) अणु
		dev_err(dev,
			"Failed to count GPIOs in DT property data-gpios\n");
		वापस ret;
	पूर्ण
	num_data = ret;
	data = devm_kसुस्मृति(dev, num_data, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_data; i++) अणु
		gpiod = gpiod_get_index(gpio_ext_dev, "data", i,
					GPIOD_OUT_LOW);
		अगर (IS_ERR(gpiod))
			वापस PTR_ERR(gpiod);
		gpiod_set_consumer_name(gpiod, "GPIO extension data");
		data[i] = gpiod;
	पूर्ण
	gpio_ext->data = data;
	gpio_ext->num_data = num_data;

	gpiod = gpiod_get(gpio_ext_dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiod)) अणु
		dev_err(dev,
			"Failed to get GPIO from DT property enable-gpio\n");
		वापस PTR_ERR(gpiod);
	पूर्ण
	gpiod_set_consumer_name(gpiod, "GPIO extension enable");
	gpio_ext->enable = gpiod;

	वापस devm_add_action_or_reset(dev, netxbig_gpio_ext_हटाओ, gpio_ext);
पूर्ण

अटल पूर्णांक netxbig_leds_get_of_pdata(काष्ठा device *dev,
				     काष्ठा netxbig_led_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा device_node *gpio_ext_np;
	काष्ठा platक्रमm_device *gpio_ext_pdev;
	काष्ठा device *gpio_ext_dev;
	काष्ठा device_node *child;
	काष्ठा netxbig_gpio_ext *gpio_ext;
	काष्ठा netxbig_led_समयr *समयrs;
	काष्ठा netxbig_led *leds, *led;
	पूर्णांक num_समयrs;
	पूर्णांक num_leds = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/* GPIO extension */
	gpio_ext_np = of_parse_phandle(np, "gpio-ext", 0);
	अगर (!gpio_ext_np) अणु
		dev_err(dev, "Failed to get DT handle gpio-ext\n");
		वापस -EINVAL;
	पूर्ण
	gpio_ext_pdev = of_find_device_by_node(gpio_ext_np);
	अगर (!gpio_ext_pdev) अणु
		dev_err(dev, "Failed to find platform device for gpio-ext\n");
		वापस -ENODEV;
	पूर्ण
	gpio_ext_dev = &gpio_ext_pdev->dev;

	gpio_ext = devm_kzalloc(dev, माप(*gpio_ext), GFP_KERNEL);
	अगर (!gpio_ext) अणु
		of_node_put(gpio_ext_np);
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण
	ret = netxbig_gpio_ext_get(dev, gpio_ext_dev, gpio_ext);
	of_node_put(gpio_ext_np);
	अगर (ret)
		जाओ put_device;
	pdata->gpio_ext = gpio_ext;

	/* Timers (optional) */
	ret = of_property_count_u32_elems(np, "timers");
	अगर (ret > 0) अणु
		अगर (ret % 3) अणु
			ret = -EINVAL;
			जाओ put_device;
		पूर्ण

		num_समयrs = ret / 3;
		समयrs = devm_kसुस्मृति(dev, num_समयrs, माप(*समयrs),
				      GFP_KERNEL);
		अगर (!समयrs) अणु
			ret = -ENOMEM;
			जाओ put_device;
		पूर्ण
		क्रम (i = 0; i < num_समयrs; i++) अणु
			u32 पंचांगp;

			of_property_पढ़ो_u32_index(np, "timers", 3 * i,
						   &समयrs[i].mode);
			अगर (समयrs[i].mode >= NETXBIG_LED_MODE_NUM) अणु
				ret = -EINVAL;
				जाओ put_device;
			पूर्ण
			of_property_पढ़ो_u32_index(np, "timers",
						   3 * i + 1, &पंचांगp);
			समयrs[i].delay_on = पंचांगp;
			of_property_पढ़ो_u32_index(np, "timers",
						   3 * i + 2, &पंचांगp);
			समयrs[i].delay_off = पंचांगp;
		पूर्ण
		pdata->समयr = समयrs;
		pdata->num_समयr = num_समयrs;
	पूर्ण

	/* LEDs */
	num_leds = of_get_available_child_count(np);
	अगर (!num_leds) अणु
		dev_err(dev, "No LED subnodes found in DT\n");
		ret = -ENODEV;
		जाओ put_device;
	पूर्ण

	leds = devm_kसुस्मृति(dev, num_leds, माप(*leds), GFP_KERNEL);
	अगर (!leds) अणु
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	led = leds;
	क्रम_each_available_child_of_node(np, child) अणु
		स्थिर अक्षर *string;
		पूर्णांक *mode_val;
		पूर्णांक num_modes;

		ret = of_property_पढ़ो_u32(child, "mode-addr",
					   &led->mode_addr);
		अगर (ret)
			जाओ err_node_put;

		ret = of_property_पढ़ो_u32(child, "bright-addr",
					   &led->bright_addr);
		अगर (ret)
			जाओ err_node_put;

		ret = of_property_पढ़ो_u32(child, "max-brightness",
					   &led->bright_max);
		अगर (ret)
			जाओ err_node_put;

		mode_val =
			devm_kसुस्मृति(dev,
				     NETXBIG_LED_MODE_NUM, माप(*mode_val),
				     GFP_KERNEL);
		अगर (!mode_val) अणु
			ret = -ENOMEM;
			जाओ err_node_put;
		पूर्ण

		क्रम (i = 0; i < NETXBIG_LED_MODE_NUM; i++)
			mode_val[i] = NETXBIG_LED_INVALID_MODE;

		ret = of_property_count_u32_elems(child, "mode-val");
		अगर (ret < 0 || ret % 2) अणु
			ret = -EINVAL;
			जाओ err_node_put;
		पूर्ण
		num_modes = ret / 2;
		अगर (num_modes > NETXBIG_LED_MODE_NUM) अणु
			ret = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		क्रम (i = 0; i < num_modes; i++) अणु
			पूर्णांक mode;
			पूर्णांक val;

			of_property_पढ़ो_u32_index(child,
						   "mode-val", 2 * i, &mode);
			of_property_पढ़ो_u32_index(child,
						   "mode-val", 2 * i + 1, &val);
			अगर (mode >= NETXBIG_LED_MODE_NUM) अणु
				ret = -EINVAL;
				जाओ err_node_put;
			पूर्ण
			mode_val[mode] = val;
		पूर्ण
		led->mode_val = mode_val;

		अगर (!of_property_पढ़ो_string(child, "label", &string))
			led->name = string;
		अन्यथा
			led->name = child->name;

		अगर (!of_property_पढ़ो_string(child,
					     "linux,default-trigger", &string))
			led->शेष_trigger = string;

		led++;
	पूर्ण

	pdata->leds = leds;
	pdata->num_leds = num_leds;

	वापस 0;

err_node_put:
	of_node_put(child);
put_device:
	put_device(gpio_ext_dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_netxbig_leds_match[] = अणु
	अणु .compatible = "lacie,netxbig-leds", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_netxbig_leds_match);

अटल पूर्णांक netxbig_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा netxbig_led_platक्रमm_data *pdata;
	काष्ठा netxbig_led_data *leds_data;
	पूर्णांक i;
	पूर्णांक ret;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;
	ret = netxbig_leds_get_of_pdata(&pdev->dev, pdata);
	अगर (ret)
		वापस ret;

	leds_data = devm_kसुस्मृति(&pdev->dev,
				 pdata->num_leds, माप(*leds_data),
				 GFP_KERNEL);
	अगर (!leds_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < pdata->num_leds; i++) अणु
		ret = create_netxbig_led(pdev, pdata,
					 &leds_data[i], &pdata->leds[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver netxbig_led_driver = अणु
	.probe		= netxbig_led_probe,
	.driver		= अणु
		.name		= "leds-netxbig",
		.of_match_table	= of_netxbig_leds_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(netxbig_led_driver);

MODULE_AUTHOR("Simon Guinot <sguinot@lacie.com>");
MODULE_DESCRIPTION("LED driver for LaCie xBig Network boards");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-netxbig");
