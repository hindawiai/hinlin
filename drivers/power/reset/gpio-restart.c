<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toggles a GPIO pin to restart a device
 *
 * Copyright (C) 2014 Google, Inc.
 *
 * Based on the gpio-घातeroff driver.
 */
#समावेश <linux/reboot.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>

काष्ठा gpio_restart अणु
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा notअगरier_block restart_handler;
	u32 active_delay_ms;
	u32 inactive_delay_ms;
	u32 रुको_delay_ms;
पूर्ण;

अटल पूर्णांक gpio_restart_notअगरy(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा gpio_restart *gpio_restart =
		container_of(this, काष्ठा gpio_restart, restart_handler);

	/* drive it active, also inactive->active edge */
	gpiod_direction_output(gpio_restart->reset_gpio, 1);
	mdelay(gpio_restart->active_delay_ms);

	/* drive inactive, also active->inactive edge */
	gpiod_set_value(gpio_restart->reset_gpio, 0);
	mdelay(gpio_restart->inactive_delay_ms);

	/* drive it active, also inactive->active edge */
	gpiod_set_value(gpio_restart->reset_gpio, 1);

	/* give it some समय */
	mdelay(gpio_restart->रुको_delay_ms);

	WARN_ON(1);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक gpio_restart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_restart *gpio_restart;
	bool खोलो_source = false;
	u32 property;
	पूर्णांक ret;

	gpio_restart = devm_kzalloc(&pdev->dev, माप(*gpio_restart),
			GFP_KERNEL);
	अगर (!gpio_restart)
		वापस -ENOMEM;

	खोलो_source = of_property_पढ़ो_bool(pdev->dev.of_node, "open-source");

	gpio_restart->reset_gpio = devm_gpiod_get(&pdev->dev, शून्य,
			खोलो_source ? GPIOD_IN : GPIOD_OUT_LOW);
	ret = PTR_ERR_OR_ZERO(gpio_restart->reset_gpio);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Could not get reset GPIO\n");
		वापस ret;
	पूर्ण

	gpio_restart->restart_handler.notअगरier_call = gpio_restart_notअगरy;
	gpio_restart->restart_handler.priority = 129;
	gpio_restart->active_delay_ms = 100;
	gpio_restart->inactive_delay_ms = 100;
	gpio_restart->रुको_delay_ms = 3000;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "priority", &property);
	अगर (!ret) अणु
		अगर (property > 255)
			dev_err(&pdev->dev, "Invalid priority property: %u\n",
					property);
		अन्यथा
			gpio_restart->restart_handler.priority = property;
	पूर्ण

	of_property_पढ़ो_u32(pdev->dev.of_node, "active-delay",
			&gpio_restart->active_delay_ms);
	of_property_पढ़ो_u32(pdev->dev.of_node, "inactive-delay",
			&gpio_restart->inactive_delay_ms);
	of_property_पढ़ो_u32(pdev->dev.of_node, "wait-delay",
			&gpio_restart->रुको_delay_ms);

	platक्रमm_set_drvdata(pdev, gpio_restart);

	ret = रेजिस्टर_restart_handler(&gpio_restart->restart_handler);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: cannot register restart handler, %d\n",
				__func__, ret);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_restart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_restart *gpio_restart = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = unरेजिस्टर_restart_handler(&gpio_restart->restart_handler);
	अगर (ret) अणु
		dev_err(&pdev->dev,
				"%s: cannot unregister restart handler, %d\n",
				__func__, ret);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_gpio_restart_match[] = अणु
	अणु .compatible = "gpio-restart", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver gpio_restart_driver = अणु
	.probe = gpio_restart_probe,
	.हटाओ = gpio_restart_हटाओ,
	.driver = अणु
		.name = "restart-gpio",
		.of_match_table = of_gpio_restart_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_restart_driver);

MODULE_AUTHOR("David Riley <davidriley@chromium.org>");
MODULE_DESCRIPTION("GPIO restart driver");
MODULE_LICENSE("GPL");
