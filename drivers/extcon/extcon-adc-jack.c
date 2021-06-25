<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/extcon/extcon-adc-jack.c
 *
 * Analog Jack extcon driver with ADC-based detection capability.
 *
 * Copyright (C) 2016 Samsung Electronics
 * Chanwoo Choi <cw00.choi@samsung.com>
 *
 * Copyright (C) 2012 Samsung Electronics
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * Modअगरied क्रम calling to IIO to get adc by <anish.singh@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/extcon/extcon-adc-jack.h>
#समावेश <linux/extcon-provider.h>

/**
 * काष्ठा adc_jack_data - पूर्णांकernal data क्रम adc_jack device driver
 * @edev:		extcon device.
 * @cable_names:	list of supported cables.
 * @adc_conditions:	list of adc value conditions.
 * @num_conditions:	size of adc_conditions.
 * @irq:		irq number of attach/detach event (0 अगर not exist).
 * @handling_delay:	पूर्णांकerrupt handler will schedule extcon event
 *			handling at handling_delay jअगरfies.
 * @handler:		extcon event handler called by पूर्णांकerrupt handler.
 * @chan:		iio channel being queried.
 */
काष्ठा adc_jack_data अणु
	काष्ठा device *dev;
	काष्ठा extcon_dev *edev;

	स्थिर अचिन्हित पूर्णांक **cable_names;
	काष्ठा adc_jack_cond *adc_conditions;
	पूर्णांक num_conditions;

	पूर्णांक irq;
	अचिन्हित दीर्घ handling_delay; /* in jअगरfies */
	काष्ठा delayed_work handler;

	काष्ठा iio_channel *chan;
	bool wakeup_source;
पूर्ण;

अटल व्योम adc_jack_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adc_jack_data *data = container_of(to_delayed_work(work),
			काष्ठा adc_jack_data,
			handler);
	काष्ठा adc_jack_cond *def;
	पूर्णांक ret, adc_val;
	पूर्णांक i;

	ret = iio_पढ़ो_channel_raw(data->chan, &adc_val);
	अगर (ret < 0) अणु
		dev_err(data->dev, "read channel() error: %d\n", ret);
		वापस;
	पूर्ण

	/* Get state from adc value with adc_conditions */
	क्रम (i = 0; i < data->num_conditions; i++) अणु
		def = &data->adc_conditions[i];
		अगर (def->min_adc <= adc_val && def->max_adc >= adc_val) अणु
			extcon_set_state_sync(data->edev, def->id, true);
			वापस;
		पूर्ण
	पूर्ण

	/* Set the detached state अगर adc value is not included in the range */
	क्रम (i = 0; i < data->num_conditions; i++) अणु
		def = &data->adc_conditions[i];
		extcon_set_state_sync(data->edev, def->id, false);
	पूर्ण
पूर्ण

अटल irqवापस_t adc_jack_irq_thपढ़ो(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा adc_jack_data *data = _data;

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &data->handler, data->handling_delay);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc_jack_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adc_jack_data *data;
	काष्ठा adc_jack_pdata *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक i, err = 0;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (!pdata->cable_names) अणु
		dev_err(&pdev->dev, "error: cable_names not defined.\n");
		वापस -EINVAL;
	पूर्ण

	data->dev = &pdev->dev;
	data->edev = devm_extcon_dev_allocate(&pdev->dev, pdata->cable_names);
	अगर (IS_ERR(data->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!pdata->adc_conditions) अणु
		dev_err(&pdev->dev, "error: adc_conditions not defined.\n");
		वापस -EINVAL;
	पूर्ण
	data->adc_conditions = pdata->adc_conditions;

	/* Check the length of array and set num_conditions */
	क्रम (i = 0; data->adc_conditions[i].id != EXTCON_NONE; i++);
	data->num_conditions = i;

	data->chan = devm_iio_channel_get(&pdev->dev, pdata->consumer_channel);
	अगर (IS_ERR(data->chan))
		वापस PTR_ERR(data->chan);

	data->handling_delay = msecs_to_jअगरfies(pdata->handling_delay_ms);
	data->wakeup_source = pdata->wakeup_source;

	INIT_DEFERRABLE_WORK(&data->handler, adc_jack_handler);

	platक्रमm_set_drvdata(pdev, data);

	err = devm_extcon_dev_रेजिस्टर(&pdev->dev, data->edev);
	अगर (err)
		वापस err;

	data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (data->irq < 0)
		वापस -ENODEV;

	err = request_any_context_irq(data->irq, adc_jack_irq_thपढ़ो,
			pdata->irq_flags, pdata->name, data);

	अगर (err < 0) अणु
		dev_err(&pdev->dev, "error: irq %d\n", data->irq);
		वापस err;
	पूर्ण

	अगर (data->wakeup_source)
		device_init_wakeup(&pdev->dev, 1);

	adc_jack_handler(&data->handler.work);
	वापस 0;
पूर्ण

अटल पूर्णांक adc_jack_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adc_jack_data *data = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(data->irq, data);
	cancel_work_sync(&data->handler.work);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक adc_jack_suspend(काष्ठा device *dev)
अणु
	काष्ठा adc_jack_data *data = dev_get_drvdata(dev);

	cancel_delayed_work_sync(&data->handler);
	अगर (device_may_wakeup(data->dev))
		enable_irq_wake(data->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक adc_jack_resume(काष्ठा device *dev)
अणु
	काष्ठा adc_jack_data *data = dev_get_drvdata(dev);

	अगर (device_may_wakeup(data->dev))
		disable_irq_wake(data->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(adc_jack_pm_ops,
		adc_jack_suspend, adc_jack_resume);

अटल काष्ठा platक्रमm_driver adc_jack_driver = अणु
	.probe          = adc_jack_probe,
	.हटाओ         = adc_jack_हटाओ,
	.driver         = अणु
		.name   = "adc-jack",
		.pm = &adc_jack_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(adc_jack_driver);

MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_DESCRIPTION("ADC Jack extcon driver");
MODULE_LICENSE("GPL v2");
