<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/irq.h>
#समावेश <media/rc-core.h>

#घोषणा GPIO_IR_DEVICE_NAME	"gpio_ir_recv"

काष्ठा gpio_rc_dev अणु
	काष्ठा rc_dev *rcdev;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक irq;
	काष्ठा device *pmdev;
	काष्ठा pm_qos_request qos;
पूर्ण;

अटल irqवापस_t gpio_ir_recv_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक val;
	काष्ठा gpio_rc_dev *gpio_dev = dev_id;
	काष्ठा device *pmdev = gpio_dev->pmdev;

	/*
	 * For some cpuidle प्रणालीs, not all:
	 * Respond to पूर्णांकerrupt taking more latency when cpu in idle.
	 * Invoke asynchronous pm runसमय get from पूर्णांकerrupt context,
	 * this may पूर्णांकroduce a millisecond delay to call resume callback,
	 * where to disable cpuilde.
	 *
	 * Two issues lead to fail to decode first frame, one is latency to
	 * respond to पूर्णांकerrupt, another is delay पूर्णांकroduced by async api.
	 */
	अगर (pmdev)
		pm_runसमय_get(pmdev);

	val = gpiod_get_value(gpio_dev->gpiod);
	अगर (val >= 0)
		ir_raw_event_store_edge(gpio_dev->rcdev, val == 1);

	अगर (pmdev) अणु
		pm_runसमय_mark_last_busy(pmdev);
		pm_runसमय_put_स्वतःsuspend(pmdev);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gpio_ir_recv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gpio_rc_dev *gpio_dev;
	काष्ठा rc_dev *rcdev;
	u32 period = 0;
	पूर्णांक rc;

	अगर (!np)
		वापस -ENODEV;

	gpio_dev = devm_kzalloc(dev, माप(*gpio_dev), GFP_KERNEL);
	अगर (!gpio_dev)
		वापस -ENOMEM;

	gpio_dev->gpiod = devm_gpiod_get(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(gpio_dev->gpiod)) अणु
		rc = PTR_ERR(gpio_dev->gpiod);
		/* Just try again अगर this happens */
		अगर (rc != -EPROBE_DEFER)
			dev_err(dev, "error getting gpio (%d)\n", rc);
		वापस rc;
	पूर्ण
	gpio_dev->irq = gpiod_to_irq(gpio_dev->gpiod);
	अगर (gpio_dev->irq < 0)
		वापस gpio_dev->irq;

	rcdev = devm_rc_allocate_device(dev, RC_DRIVER_IR_RAW);
	अगर (!rcdev)
		वापस -ENOMEM;

	rcdev->priv = gpio_dev;
	rcdev->device_name = GPIO_IR_DEVICE_NAME;
	rcdev->input_phys = GPIO_IR_DEVICE_NAME "/input0";
	rcdev->input_id.bustype = BUS_HOST;
	rcdev->input_id.venकरोr = 0x0001;
	rcdev->input_id.product = 0x0001;
	rcdev->input_id.version = 0x0100;
	rcdev->dev.parent = dev;
	rcdev->driver_name = KBUILD_MODNAME;
	rcdev->min_समयout = 1;
	rcdev->समयout = IR_DEFAULT_TIMEOUT;
	rcdev->max_समयout = 10 * IR_DEFAULT_TIMEOUT;
	rcdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rcdev->map_name = of_get_property(np, "linux,rc-map-name", शून्य);
	अगर (!rcdev->map_name)
		rcdev->map_name = RC_MAP_EMPTY;

	gpio_dev->rcdev = rcdev;

	rc = devm_rc_रेजिस्टर_device(dev, rcdev);
	अगर (rc < 0) अणु
		dev_err(dev, "failed to register rc device (%d)\n", rc);
		वापस rc;
	पूर्ण

	of_property_पढ़ो_u32(np, "linux,autosuspend-period", &period);
	अगर (period) अणु
		gpio_dev->pmdev = dev;
		pm_runसमय_set_स्वतःsuspend_delay(dev, period);
		pm_runसमय_use_स्वतःsuspend(dev);
		pm_runसमय_set_suspended(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, gpio_dev);

	वापस devm_request_irq(dev, gpio_dev->irq, gpio_ir_recv_irq,
				IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
				"gpio-ir-recv-irq", gpio_dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gpio_ir_recv_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_rc_dev *gpio_dev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(gpio_dev->irq);
	अन्यथा
		disable_irq(gpio_dev->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_ir_recv_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_rc_dev *gpio_dev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(gpio_dev->irq);
	अन्यथा
		enable_irq(gpio_dev->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_ir_recv_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_rc_dev *gpio_dev = dev_get_drvdata(dev);

	cpu_latency_qos_हटाओ_request(&gpio_dev->qos);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_ir_recv_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_rc_dev *gpio_dev = dev_get_drvdata(dev);

	cpu_latency_qos_add_request(&gpio_dev->qos, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gpio_ir_recv_pm_ops = अणु
	.suspend        = gpio_ir_recv_suspend,
	.resume         = gpio_ir_recv_resume,
	.runसमय_suspend = gpio_ir_recv_runसमय_suspend,
	.runसमय_resume  = gpio_ir_recv_runसमय_resume,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id gpio_ir_recv_of_match[] = अणु
	अणु .compatible = "gpio-ir-receiver", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_ir_recv_of_match);

अटल काष्ठा platक्रमm_driver gpio_ir_recv_driver = अणु
	.probe  = gpio_ir_recv_probe,
	.driver = अणु
		.name   = KBUILD_MODNAME,
		.of_match_table = of_match_ptr(gpio_ir_recv_of_match),
#अगर_घोषित CONFIG_PM
		.pm	= &gpio_ir_recv_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gpio_ir_recv_driver);

MODULE_DESCRIPTION("GPIO IR Receiver driver");
MODULE_LICENSE("GPL v2");
