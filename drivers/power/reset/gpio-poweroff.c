<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toggles a GPIO pin to घातer करोwn a device
 *
 * Jamie Lentin <jm@lentin.co.uk>
 * Andrew Lunn <andrew@lunn.ch>
 *
 * Copyright (C) 2012 Jamie Lentin
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>

#घोषणा DEFAULT_TIMEOUT_MS 3000
/*
 * Hold configuration here, cannot be more than one instance of the driver
 * since pm_घातer_off itself is global.
 */
अटल काष्ठा gpio_desc *reset_gpio;
अटल u32 समयout = DEFAULT_TIMEOUT_MS;
अटल u32 active_delay = 100;
अटल u32 inactive_delay = 100;

अटल व्योम gpio_घातeroff_करो_घातeroff(व्योम)
अणु
	BUG_ON(!reset_gpio);

	/* drive it active, also inactive->active edge */
	gpiod_direction_output(reset_gpio, 1);
	mdelay(active_delay);

	/* drive inactive, also active->inactive edge */
	gpiod_set_value_cansleep(reset_gpio, 0);
	mdelay(inactive_delay);

	/* drive it active, also inactive->active edge */
	gpiod_set_value_cansleep(reset_gpio, 1);

	/* give it some समय */
	mdelay(समयout);

	WARN_ON(1);
पूर्ण

अटल पूर्णांक gpio_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	bool input = false;
	क्रमागत gpiod_flags flags;

	/* If a pm_घातer_off function has alपढ़ोy been added, leave it alone */
	अगर (pm_घातer_off != शून्य) अणु
		dev_err(&pdev->dev,
			"%s: pm_power_off function already registered\n",
		       __func__);
		वापस -EBUSY;
	पूर्ण

	input = device_property_पढ़ो_bool(&pdev->dev, "input");
	अगर (input)
		flags = GPIOD_IN;
	अन्यथा
		flags = GPIOD_OUT_LOW;

	device_property_पढ़ो_u32(&pdev->dev, "active-delay-ms", &active_delay);
	device_property_पढ़ो_u32(&pdev->dev, "inactive-delay-ms",
				 &inactive_delay);
	device_property_पढ़ो_u32(&pdev->dev, "timeout-ms", &समयout);

	reset_gpio = devm_gpiod_get(&pdev->dev, शून्य, flags);
	अगर (IS_ERR(reset_gpio))
		वापस PTR_ERR(reset_gpio);

	pm_घातer_off = &gpio_घातeroff_करो_घातeroff;
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_घातeroff_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == &gpio_घातeroff_करो_घातeroff)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_gpio_घातeroff_match[] = अणु
	अणु .compatible = "gpio-poweroff", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver gpio_घातeroff_driver = अणु
	.probe = gpio_घातeroff_probe,
	.हटाओ = gpio_घातeroff_हटाओ,
	.driver = अणु
		.name = "poweroff-gpio",
		.of_match_table = of_gpio_घातeroff_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_घातeroff_driver);

MODULE_AUTHOR("Jamie Lentin <jm@lentin.co.uk>");
MODULE_DESCRIPTION("GPIO poweroff driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:poweroff-gpio");
