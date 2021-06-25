<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * extcon_gpio.c - Single-state GPIO extcon driver based on extcon class
 *
 * Copyright (C) 2008 Google, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
 *
 * Modअगरied by MyungJoo Ham <myungjoo.ham@samsung.com> to support extcon
 * (originally चयन class is supported)
 */

#समावेश <linux/devm-helpers.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

/**
 * काष्ठा gpio_extcon_data - A simple GPIO-controlled extcon device state container.
 * @edev:		Extcon device.
 * @work:		Work fired by the पूर्णांकerrupt.
 * @debounce_jअगरfies:	Number of jअगरfies to रुको क्रम the GPIO to stabilize, from the debounce
 *			value.
 * @gpiod:		GPIO descriptor क्रम this बाह्यal connector.
 * @extcon_id:		The unique id of specअगरic बाह्यal connector.
 * @debounce:		Debounce समय क्रम GPIO IRQ in ms.
 * @check_on_resume:	Boolean describing whether to check the state of gpio
 *			जबतक resuming from sleep.
 */
काष्ठा gpio_extcon_data अणु
	काष्ठा extcon_dev *edev;
	काष्ठा delayed_work work;
	अचिन्हित दीर्घ debounce_jअगरfies;
	काष्ठा gpio_desc *gpiod;
	अचिन्हित पूर्णांक extcon_id;
	अचिन्हित दीर्घ debounce;
	bool check_on_resume;
पूर्ण;

अटल व्योम gpio_extcon_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक state;
	काष्ठा gpio_extcon_data	*data =
		container_of(to_delayed_work(work), काष्ठा gpio_extcon_data,
			     work);

	state = gpiod_get_value_cansleep(data->gpiod);
	extcon_set_state_sync(data->edev, data->extcon_id, state);
पूर्ण

अटल irqवापस_t gpio_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gpio_extcon_data *data = dev_id;

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &data->work,
			      data->debounce_jअगरfies);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gpio_extcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_extcon_data *data;
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक irq;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(काष्ठा gpio_extcon_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/*
	 * FIXME: extcon_id represents the unique identअगरier of बाह्यal
	 * connectors such as EXTCON_USB, EXTCON_DISP_HDMI and so on. extcon_id
	 * is necessary to रेजिस्टर the extcon device. But, it's not yet
	 * developed to get the extcon id from device-tree or others.
	 * On later, it have to be solved.
	 */
	अगर (data->extcon_id > EXTCON_NONE)
		वापस -EINVAL;

	data->gpiod = devm_gpiod_get(dev, "extcon", GPIOD_IN);
	अगर (IS_ERR(data->gpiod))
		वापस PTR_ERR(data->gpiod);
	irq = gpiod_to_irq(data->gpiod);
	अगर (irq <= 0)
		वापस irq;

	/*
	 * It is unlikely that this is an acknowledged पूर्णांकerrupt that goes
	 * away after handling, what we are looking क्रम are falling edges
	 * अगर the संकेत is active low, and rising edges अगर the संकेत is
	 * active high.
	 */
	अगर (gpiod_is_active_low(data->gpiod))
		irq_flags = IRQF_TRIGGER_FALLING;
	अन्यथा
		irq_flags = IRQF_TRIGGER_RISING;

	/* Allocate the memory of extcon devie and रेजिस्टर extcon device */
	data->edev = devm_extcon_dev_allocate(dev, &data->extcon_id);
	अगर (IS_ERR(data->edev)) अणु
		dev_err(dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(dev, data->edev);
	अगर (ret < 0)
		वापस ret;

	ret = devm_delayed_work_स्वतःcancel(dev, &data->work, gpio_extcon_work);
	अगर (ret)
		वापस ret;

	/*
	 * Request the पूर्णांकerrupt of gpio to detect whether बाह्यal connector
	 * is attached or detached.
	 */
	ret = devm_request_any_context_irq(dev, irq,
					gpio_irq_handler, irq_flags,
					pdev->name, data);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, data);
	/* Perक्रमm initial detection */
	gpio_extcon_work(&data->work.work);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gpio_extcon_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_extcon_data *data;

	data = dev_get_drvdata(dev);
	अगर (data->check_on_resume)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
			&data->work, data->debounce_jअगरfies);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(gpio_extcon_pm_ops, शून्य, gpio_extcon_resume);

अटल काष्ठा platक्रमm_driver gpio_extcon_driver = अणु
	.probe		= gpio_extcon_probe,
	.driver		= अणु
		.name	= "extcon-gpio",
		.pm	= &gpio_extcon_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_extcon_driver);

MODULE_AUTHOR("Mike Lockwood <lockwood@android.com>");
MODULE_DESCRIPTION("GPIO extcon driver");
MODULE_LICENSE("GPL");
