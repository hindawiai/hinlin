<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम simulating a mouse on GPIO lines.
 *
 * Copyright (C) 2007 Aपंचांगel Corporation
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/property.h>
#समावेश <linux/of.h>

/**
 * काष्ठा gpio_mouse
 * @scan_ms: the scan पूर्णांकerval in milliseconds.
 * @up: GPIO line क्रम up value.
 * @करोwn: GPIO line क्रम करोwn value.
 * @left: GPIO line क्रम left value.
 * @right: GPIO line क्रम right value.
 * @bleft: GPIO line क्रम left button.
 * @bmiddle: GPIO line क्रम middle button.
 * @bright: GPIO line क्रम right button.
 *
 * This काष्ठा must be added to the platक्रमm_device in the board code.
 * It is used by the gpio_mouse driver to setup GPIO lines and to
 * calculate mouse movement.
 */
काष्ठा gpio_mouse अणु
	u32 scan_ms;
	काष्ठा gpio_desc *up;
	काष्ठा gpio_desc *करोwn;
	काष्ठा gpio_desc *left;
	काष्ठा gpio_desc *right;
	काष्ठा gpio_desc *bleft;
	काष्ठा gpio_desc *bmiddle;
	काष्ठा gpio_desc *bright;
पूर्ण;

/*
 * Timer function which is run every scan_ms ms when the device is खोलोed.
 * The dev input variable is set to the the input_dev poपूर्णांकer.
 */
अटल व्योम gpio_mouse_scan(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_mouse *gpio = input_get_drvdata(input);
	पूर्णांक x, y;

	अगर (gpio->bleft)
		input_report_key(input, BTN_LEFT,
				 gpiod_get_value(gpio->bleft));
	अगर (gpio->bmiddle)
		input_report_key(input, BTN_MIDDLE,
				 gpiod_get_value(gpio->bmiddle));
	अगर (gpio->bright)
		input_report_key(input, BTN_RIGHT,
				 gpiod_get_value(gpio->bright));

	x = gpiod_get_value(gpio->right) - gpiod_get_value(gpio->left);
	y = gpiod_get_value(gpio->करोwn) - gpiod_get_value(gpio->up);

	input_report_rel(input, REL_X, x);
	input_report_rel(input, REL_Y, y);
	input_sync(input);
पूर्ण

अटल पूर्णांक gpio_mouse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_mouse *gmouse;
	काष्ठा input_dev *input;
	पूर्णांक error;

	gmouse = devm_kzalloc(dev, माप(*gmouse), GFP_KERNEL);
	अगर (!gmouse)
		वापस -ENOMEM;

	/* Assign some शेष scanning समय */
	error = device_property_पढ़ो_u32(dev, "scan-interval-ms",
					 &gmouse->scan_ms);
	अगर (error || gmouse->scan_ms == 0) अणु
		dev_warn(dev, "invalid scan time, set to 50 ms\n");
		gmouse->scan_ms = 50;
	पूर्ण

	gmouse->up = devm_gpiod_get(dev, "up", GPIOD_IN);
	अगर (IS_ERR(gmouse->up))
		वापस PTR_ERR(gmouse->up);
	gmouse->करोwn = devm_gpiod_get(dev, "down", GPIOD_IN);
	अगर (IS_ERR(gmouse->करोwn))
		वापस PTR_ERR(gmouse->करोwn);
	gmouse->left = devm_gpiod_get(dev, "left", GPIOD_IN);
	अगर (IS_ERR(gmouse->left))
		वापस PTR_ERR(gmouse->left);
	gmouse->right = devm_gpiod_get(dev, "right", GPIOD_IN);
	अगर (IS_ERR(gmouse->right))
		वापस PTR_ERR(gmouse->right);

	gmouse->bleft = devm_gpiod_get_optional(dev, "button-left", GPIOD_IN);
	अगर (IS_ERR(gmouse->bleft))
		वापस PTR_ERR(gmouse->bleft);
	gmouse->bmiddle = devm_gpiod_get_optional(dev, "button-middle",
						  GPIOD_IN);
	अगर (IS_ERR(gmouse->bmiddle))
		वापस PTR_ERR(gmouse->bmiddle);
	gmouse->bright = devm_gpiod_get_optional(dev, "button-right",
						 GPIOD_IN);
	अगर (IS_ERR(gmouse->bright))
		वापस PTR_ERR(gmouse->bright);

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = pdev->name;
	input->id.bustype = BUS_HOST;

	input_set_drvdata(input, gmouse);

	input_set_capability(input, EV_REL, REL_X);
	input_set_capability(input, EV_REL, REL_Y);
	अगर (gmouse->bleft)
		input_set_capability(input, EV_KEY, BTN_LEFT);
	अगर (gmouse->bmiddle)
		input_set_capability(input, EV_KEY, BTN_MIDDLE);
	अगर (gmouse->bright)
		input_set_capability(input, EV_KEY, BTN_RIGHT);

	error = input_setup_polling(input, gpio_mouse_scan);
	अगर (error)
		वापस error;

	input_set_poll_पूर्णांकerval(input, gmouse->scan_ms);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "could not register input device\n");
		वापस error;
	पूर्ण

	dev_dbg(dev, "%d ms scan time, buttons: %s%s%s\n",
		gmouse->scan_ms,
		gmouse->bleft ? "" : "left ",
		gmouse->bmiddle ? "" : "middle ",
		gmouse->bright ? "" : "right");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_mouse_of_match[] = अणु
	अणु .compatible = "gpio-mouse", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_mouse_of_match);

अटल काष्ठा platक्रमm_driver gpio_mouse_device_driver = अणु
	.probe		= gpio_mouse_probe,
	.driver		= अणु
		.name	= "gpio_mouse",
		.of_match_table = gpio_mouse_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(gpio_mouse_device_driver);

MODULE_AUTHOR("Hans-Christian Egtvedt <egtvedt@samfundet.no>");
MODULE_DESCRIPTION("GPIO mouse driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio_mouse"); /* work with hotplug and coldplug */
