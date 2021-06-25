<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, National Instruments Corp. All rights reserved.
 *
 * Driver क्रम NI Ettus Research USRP E3x0 Button Driver
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

अटल irqवापस_t e3x0_button_release_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा input_dev *idev = data;

	input_report_key(idev, KEY_POWER, 0);
	input_sync(idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t e3x0_button_press_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा input_dev *idev = data;

	input_report_key(idev, KEY_POWER, 1);
	pm_wakeup_event(idev->dev.parent, 0);
	input_sync(idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __maybe_unused e3x0_button_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(platक्रमm_get_irq_byname(pdev, "press"));

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused e3x0_button_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(platक्रमm_get_irq_byname(pdev, "press"));

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(e3x0_button_pm_ops,
			 e3x0_button_suspend, e3x0_button_resume);

अटल पूर्णांक e3x0_button_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input;
	पूर्णांक irq_press, irq_release;
	पूर्णांक error;

	irq_press = platक्रमm_get_irq_byname(pdev, "press");
	अगर (irq_press < 0)
		वापस irq_press;

	irq_release = platक्रमm_get_irq_byname(pdev, "release");
	अगर (irq_release < 0)
		वापस irq_release;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "NI Ettus Research USRP E3x0 Button Driver";
	input->phys = "e3x0_button/input0";
	input->dev.parent = &pdev->dev;

	input_set_capability(input, EV_KEY, KEY_POWER);

	error = devm_request_irq(&pdev->dev, irq_press,
				 e3x0_button_press_handler, 0,
				 "e3x0-button", input);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to request 'press' IRQ#%d: %d\n",
			irq_press, error);
		वापस error;
	पूर्ण

	error = devm_request_irq(&pdev->dev, irq_release,
				 e3x0_button_release_handler, 0,
				 "e3x0-button", input);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to request 'release' IRQ#%d: %d\n",
			irq_release, error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "Can't register input device: %d\n", error);
		वापस error;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id e3x0_button_match[] = अणु
	अणु .compatible = "ettus,e3x0-button", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, e3x0_button_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver e3x0_button_driver = अणु
	.driver		= अणु
		.name	= "e3x0-button",
		.of_match_table = of_match_ptr(e3x0_button_match),
		.pm	= &e3x0_button_pm_ops,
	पूर्ण,
	.probe		= e3x0_button_probe,
पूर्ण;

module_platक्रमm_driver(e3x0_button_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Moritz Fischer <moritz.fischer@ettus.com>");
MODULE_DESCRIPTION("NI Ettus Research USRP E3x0 Button driver");
MODULE_ALIAS("platform:e3x0-button");
