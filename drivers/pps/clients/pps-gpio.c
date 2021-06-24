<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pps-gpio.c -- PPS client driver using GPIO
 *
 * Copyright (C) 2010 Ricarकरो Martins <rयंत्र@fe.up.pt>
 * Copyright (C) 2011 James Nuss <jamesnuss@nanometrics.ca>
 */

#घोषणा PPS_GPIO_NAME "pps-gpio"
#घोषणा pr_fmt(fmt) PPS_GPIO_NAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/list.h>
#समावेश <linux/property.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>

/* Info क्रम each रेजिस्टरed platक्रमm device */
काष्ठा pps_gpio_device_data अणु
	पूर्णांक irq;			/* IRQ used as PPS source */
	काष्ठा pps_device *pps;		/* PPS source device */
	काष्ठा pps_source_info info;	/* PPS source inक्रमmation */
	काष्ठा gpio_desc *gpio_pin;	/* GPIO port descriptors */
	काष्ठा gpio_desc *echo_pin;
	काष्ठा समयr_list echo_समयr;	/* समयr to reset echo active state */
	bool निश्चित_falling_edge;
	bool capture_clear;
	अचिन्हित पूर्णांक echo_active_ms;	/* PPS echo active duration */
	अचिन्हित दीर्घ echo_समयout;	/* समयr समयout value in jअगरfies */
पूर्ण;

/*
 * Report the PPS event
 */

अटल irqवापस_t pps_gpio_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	स्थिर काष्ठा pps_gpio_device_data *info;
	काष्ठा pps_event_समय ts;
	पूर्णांक rising_edge;

	/* Get the समय stamp first */
	pps_get_ts(&ts);

	info = data;

	rising_edge = gpiod_get_value(info->gpio_pin);
	अगर ((rising_edge && !info->निश्चित_falling_edge) ||
			(!rising_edge && info->निश्चित_falling_edge))
		pps_event(info->pps, &ts, PPS_CAPTUREASSERT, data);
	अन्यथा अगर (info->capture_clear &&
			((rising_edge && info->निश्चित_falling_edge) ||
			(!rising_edge && !info->निश्चित_falling_edge)))
		pps_event(info->pps, &ts, PPS_CAPTURECLEAR, data);

	वापस IRQ_HANDLED;
पूर्ण

/* This function will only be called when an ECHO GPIO is defined */
अटल व्योम pps_gpio_echo(काष्ठा pps_device *pps, पूर्णांक event, व्योम *data)
अणु
	/* add_समयr() needs to ग_लिखो पूर्णांकo info->echo_समयr */
	काष्ठा pps_gpio_device_data *info = data;

	चयन (event) अणु
	हाल PPS_CAPTUREASSERT:
		अगर (pps->params.mode & PPS_ECHOASSERT)
			gpiod_set_value(info->echo_pin, 1);
		अवरोध;

	हाल PPS_CAPTURECLEAR:
		अगर (pps->params.mode & PPS_ECHOCLEAR)
			gpiod_set_value(info->echo_pin, 1);
		अवरोध;
	पूर्ण

	/* fire the समयr */
	अगर (info->pps->params.mode & (PPS_ECHOASSERT | PPS_ECHOCLEAR)) अणु
		info->echo_समयr.expires = jअगरfies + info->echo_समयout;
		add_समयr(&info->echo_समयr);
	पूर्ण
पूर्ण

/* Timer callback to reset the echo pin to the inactive state */
अटल व्योम pps_gpio_echo_समयr_callback(काष्ठा समयr_list *t)
अणु
	स्थिर काष्ठा pps_gpio_device_data *info;

	info = from_समयr(info, t, echo_समयr);

	gpiod_set_value(info->echo_pin, 0);
पूर्ण

अटल पूर्णांक pps_gpio_setup(काष्ठा device *dev)
अणु
	काष्ठा pps_gpio_device_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	u32 value;

	data->gpio_pin = devm_gpiod_get(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(data->gpio_pin))
		वापस dev_err_probe(dev, PTR_ERR(data->gpio_pin),
				     "failed to request PPS GPIO\n");

	data->निश्चित_falling_edge =
		device_property_पढ़ो_bool(dev, "assert-falling-edge");

	data->echo_pin = devm_gpiod_get_optional(dev, "echo", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->echo_pin))
		वापस dev_err_probe(dev, PTR_ERR(data->echo_pin),
				     "failed to request ECHO GPIO\n");

	अगर (!data->echo_pin)
		वापस 0;

	ret = device_property_पढ़ो_u32(dev, "echo-active-ms", &value);
	अगर (ret) अणु
		dev_err(dev, "failed to get echo-active-ms from FW\n");
		वापस ret;
	पूर्ण

	/* sanity check on echo_active_ms */
	अगर (!value || value > 999) अणु
		dev_err(dev, "echo-active-ms: %u - bad value from FW\n", value);
		वापस -EINVAL;
	पूर्ण

	data->echo_active_ms = value;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ
get_irqf_trigger_flags(स्थिर काष्ठा pps_gpio_device_data *data)
अणु
	अचिन्हित दीर्घ flags = data->निश्चित_falling_edge ?
		IRQF_TRIGGER_FALLING : IRQF_TRIGGER_RISING;

	अगर (data->capture_clear) अणु
		flags |= ((flags & IRQF_TRIGGER_RISING) ?
				IRQF_TRIGGER_FALLING : IRQF_TRIGGER_RISING);
	पूर्ण

	वापस flags;
पूर्ण

अटल पूर्णांक pps_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pps_gpio_device_data *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	पूर्णांक pps_शेष_params;

	/* allocate space क्रम device info */
	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	dev_set_drvdata(dev, data);

	/* GPIO setup */
	ret = pps_gpio_setup(dev);
	अगर (ret)
		वापस -EINVAL;

	/* IRQ setup */
	ret = gpiod_to_irq(data->gpio_pin);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to map GPIO to IRQ: %d\n", ret);
		वापस -EINVAL;
	पूर्ण
	data->irq = ret;

	/* initialize PPS specअगरic parts of the bookkeeping data काष्ठाure. */
	data->info.mode = PPS_CAPTUREASSERT | PPS_OFFSETASSERT |
		PPS_ECHOASSERT | PPS_CANWAIT | PPS_TSFMT_TSPEC;
	अगर (data->capture_clear)
		data->info.mode |= PPS_CAPTURECLEAR | PPS_OFFSETCLEAR |
			PPS_ECHOCLEAR;
	data->info.owner = THIS_MODULE;
	snम_लिखो(data->info.name, PPS_MAX_NAME_LEN - 1, "%s.%d",
		 pdev->name, pdev->id);
	अगर (data->echo_pin) अणु
		data->info.echo = pps_gpio_echo;
		data->echo_समयout = msecs_to_jअगरfies(data->echo_active_ms);
		समयr_setup(&data->echo_समयr, pps_gpio_echo_समयr_callback, 0);
	पूर्ण

	/* रेजिस्टर PPS source */
	pps_शेष_params = PPS_CAPTUREASSERT | PPS_OFFSETASSERT;
	अगर (data->capture_clear)
		pps_शेष_params |= PPS_CAPTURECLEAR | PPS_OFFSETCLEAR;
	data->pps = pps_रेजिस्टर_source(&data->info, pps_शेष_params);
	अगर (IS_ERR(data->pps)) अणु
		dev_err(dev, "failed to register IRQ %d as PPS source\n",
			data->irq);
		वापस PTR_ERR(data->pps);
	पूर्ण

	/* रेजिस्टर IRQ पूर्णांकerrupt handler */
	ret = devm_request_irq(dev, data->irq, pps_gpio_irq_handler,
			get_irqf_trigger_flags(data), data->info.name, data);
	अगर (ret) अणु
		pps_unरेजिस्टर_source(data->pps);
		dev_err(dev, "failed to acquire IRQ %d\n", data->irq);
		वापस -EINVAL;
	पूर्ण

	dev_info(data->pps->dev, "Registered IRQ %d as PPS source\n",
		 data->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक pps_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pps_gpio_device_data *data = platक्रमm_get_drvdata(pdev);

	pps_unरेजिस्टर_source(data->pps);
	del_समयr_sync(&data->echo_समयr);
	/* reset echo pin in any हाल */
	gpiod_set_value(data->echo_pin, 0);
	dev_info(&pdev->dev, "removed IRQ %d as PPS source\n", data->irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pps_gpio_dt_ids[] = अणु
	अणु .compatible = "pps-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pps_gpio_dt_ids);

अटल काष्ठा platक्रमm_driver pps_gpio_driver = अणु
	.probe		= pps_gpio_probe,
	.हटाओ		= pps_gpio_हटाओ,
	.driver		= अणु
		.name	= PPS_GPIO_NAME,
		.of_match_table	= pps_gpio_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pps_gpio_driver);
MODULE_AUTHOR("Ricardo Martins <rasm@fe.up.pt>");
MODULE_AUTHOR("James Nuss <jamesnuss@nanometrics.ca>");
MODULE_DESCRIPTION("Use GPIO pin as PPS source");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.2.0");
