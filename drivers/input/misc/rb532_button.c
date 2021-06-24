<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम the S1 button on Routerboard 532
 *
 * Copyright (C) 2009  Phil Sutter <n0-1@मुक्तwrt.org>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach-rc32434/gpपन.स>
#समावेश <यंत्र/mach-rc32434/rb.h>

#घोषणा DRV_NAME "rb532-button"

#घोषणा RB532_BTN_RATE 100 /* msec */
#घोषणा RB532_BTN_KSYM BTN_0

/* The S1 button state is provided by GPIO pin 1. But as this
 * pin is also used क्रम uart input as alternate function, the
 * operational modes must be चयनed first:
 * 1) disable uart using set_latch_u5()
 * 2) turn off alternate function implicitly through
 *    gpio_direction_input()
 * 3) पढ़ो the GPIO's current value
 * 4) unकरो step 2 by enabling alternate function (in this
 *    mode the GPIO direction is fixed, so no change needed)
 * 5) turn on uart again
 * The GPIO value occurs to be inverted, so pin high means
 * button is not pressed.
 */
अटल bool rb532_button_pressed(व्योम)
अणु
	पूर्णांक val;

	set_latch_u5(0, LO_FOFF);
	gpio_direction_input(GPIO_BTN_S1);

	val = gpio_get_value(GPIO_BTN_S1);

	rb532_gpio_set_func(GPIO_BTN_S1);
	set_latch_u5(LO_FOFF, 0);

	वापस !val;
पूर्ण

अटल व्योम rb532_button_poll(काष्ठा input_dev *input)
अणु
	input_report_key(input, RB532_BTN_KSYM, rb532_button_pressed());
	input_sync(input);
पूर्ण

अटल पूर्णांक rb532_button_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input;
	पूर्णांक error;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "rb532 button";
	input->phys = "rb532/button0";
	input->id.bustype = BUS_HOST;

	input_set_capability(input, EV_KEY, RB532_BTN_KSYM);

	error = input_setup_polling(input, rb532_button_poll);
	अगर (error)
		वापस error;

	input_set_poll_पूर्णांकerval(input, RB532_BTN_RATE);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rb532_button_driver = अणु
	.probe = rb532_button_probe,
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rb532_button_driver);

MODULE_AUTHOR("Phil Sutter <n0-1@freewrt.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Support for S1 button on Routerboard 532");
MODULE_ALIAS("platform:" DRV_NAME);
