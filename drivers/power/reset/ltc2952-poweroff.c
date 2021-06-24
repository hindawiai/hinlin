<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LTC2952 (PowerPath) driver
 *
 * Copyright (C) 2014, Xsens Technologies BV <info@xsens.com>
 * Maपूर्णांकainer: Renथऊ Moll <linux@r-moll.nl>
 *
 * ----------------------------------------
 * - Description
 * ----------------------------------------
 *
 * This driver is to be used with an बाह्यal PowerPath Controller (LTC2952).
 * Its function is to determine when a बाह्यal shut करोwn is triggered
 * and react by properly shutting करोwn the प्रणाली.
 *
 * This driver expects a device tree with a ltc2952 entry क्रम pin mapping.
 *
 * ----------------------------------------
 * - GPIO
 * ----------------------------------------
 *
 * The following GPIOs are used:
 * - trigger (input)
 *     A level change indicates the shut-करोwn trigger. If it's state reverts
 *     within the समय-out defined by trigger_delay, the shut करोwn is not
 *     executed. If no pin is asचिन्हित to this input, the driver will start the
 *     watchकरोg toggle immediately. The chip will only घातer off the प्रणाली अगर
 *     it is requested to करो so through the समाप्त line.
 *
 * - watchकरोg (output)
 *     Once a shut करोwn is triggered, the driver will toggle this संकेत,
 *     with an पूर्णांकernal (wde_पूर्णांकerval) to stall the hardware shut करोwn.
 *
 * - समाप्त (output)
 *     The last action during shut करोwn is triggering this संकेतling, such
 *     that the PowerPath Control will घातer करोwn the hardware.
 *
 * ----------------------------------------
 * - Interrupts
 * ----------------------------------------
 *
 * The driver requires a non-shared, edge-triggered पूर्णांकerrupt on the trigger
 * GPIO.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/reboot.h>
#समावेश <linux/property.h>

काष्ठा ltc2952_घातeroff अणु
	काष्ठा hrसमयr समयr_trigger;
	काष्ठा hrसमयr समयr_wde;

	kसमय_प्रकार trigger_delay;
	kसमय_प्रकार wde_पूर्णांकerval;

	काष्ठा device *dev;

	काष्ठा gpio_desc *gpio_trigger;
	काष्ठा gpio_desc *gpio_watchकरोg;
	काष्ठा gpio_desc *gpio_समाप्त;

	bool kernel_panic;
	काष्ठा notअगरier_block panic_notअगरier;
पूर्ण;

#घोषणा to_ltc2952(p, m) container_of(p, काष्ठा ltc2952_घातeroff, m)

/*
 * This global variable is only needed क्रम pm_घातer_off. We should
 * हटाओ it entirely once we करोn't need the global state anymore.
 */
अटल काष्ठा ltc2952_घातeroff *ltc2952_data;

/**
 * ltc2952_घातeroff_समयr_wde - Timer callback
 * Toggles the watchकरोg reset संकेत each wde_पूर्णांकerval
 *
 * @समयr: corresponding समयr
 *
 * Returns HRTIMER_RESTART क्रम an infinite loop which will only stop when the
 * machine actually shuts करोwn
 */
अटल क्रमागत hrसमयr_restart ltc2952_घातeroff_समयr_wde(काष्ठा hrसमयr *समयr)
अणु
	kसमय_प्रकार now;
	पूर्णांक state;
	काष्ठा ltc2952_घातeroff *data = to_ltc2952(समयr, समयr_wde);

	अगर (data->kernel_panic)
		वापस HRTIMER_NORESTART;

	state = gpiod_get_value(data->gpio_watchकरोg);
	gpiod_set_value(data->gpio_watchकरोg, !state);

	now = hrसमयr_cb_get_समय(समयr);
	hrसमयr_क्रमward(समयr, now, data->wde_पूर्णांकerval);

	वापस HRTIMER_RESTART;
पूर्ण

अटल व्योम ltc2952_घातeroff_start_wde(काष्ठा ltc2952_घातeroff *data)
अणु
	hrसमयr_start(&data->समयr_wde, data->wde_पूर्णांकerval, HRTIMER_MODE_REL);
पूर्ण

अटल क्रमागत hrसमयr_restart
ltc2952_घातeroff_समयr_trigger(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा ltc2952_घातeroff *data = to_ltc2952(समयr, समयr_trigger);

	ltc2952_घातeroff_start_wde(data);
	dev_info(data->dev, "executing shutdown\n");
	orderly_घातeroff(true);

	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * ltc2952_घातeroff_handler - Interrupt handler
 * Triggered each समय the trigger संकेत changes state and (de)activates a
 * समय-out (समयr_trigger). Once the समय-out is actually reached the shut
 * करोwn is executed.
 *
 * @irq: IRQ number
 * @dev_id: poपूर्णांकer to the मुख्य data काष्ठाure
 */
अटल irqवापस_t ltc2952_घातeroff_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ltc2952_घातeroff *data = dev_id;

	अगर (data->kernel_panic || hrसमयr_active(&data->समयr_wde)) अणु
		/* shutकरोwn is alपढ़ोy triggered, nothing to करो any more */
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (gpiod_get_value(data->gpio_trigger)) अणु
		hrसमयr_start(&data->समयr_trigger, data->trigger_delay,
			      HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		hrसमयr_cancel(&data->समयr_trigger);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ltc2952_घातeroff_समाप्त(व्योम)
अणु
	gpiod_set_value(ltc2952_data->gpio_समाप्त, 1);
पूर्ण

अटल व्योम ltc2952_घातeroff_शेष(काष्ठा ltc2952_घातeroff *data)
अणु
	data->wde_पूर्णांकerval = 300L * 1E6L;
	data->trigger_delay = kसमय_set(2, 500L*1E6L);

	hrसमयr_init(&data->समयr_trigger, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	data->समयr_trigger.function = ltc2952_घातeroff_समयr_trigger;

	hrसमयr_init(&data->समयr_wde, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	data->समयr_wde.function = ltc2952_घातeroff_समयr_wde;
पूर्ण

अटल पूर्णांक ltc2952_घातeroff_init(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	u32 trigger_delay_ms;
	काष्ठा ltc2952_घातeroff *data = platक्रमm_get_drvdata(pdev);

	ltc2952_घातeroff_शेष(data);

	अगर (!device_property_पढ़ो_u32(&pdev->dev, "trigger-delay-ms",
				      &trigger_delay_ms)) अणु
		data->trigger_delay = kसमय_set(trigger_delay_ms / MSEC_PER_SEC,
			(trigger_delay_ms % MSEC_PER_SEC) * NSEC_PER_MSEC);
	पूर्ण

	data->gpio_watchकरोg = devm_gpiod_get(&pdev->dev, "watchdog",
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(data->gpio_watchकरोg)) अणु
		ret = PTR_ERR(data->gpio_watchकरोg);
		dev_err(&pdev->dev, "unable to claim gpio \"watchdog\"\n");
		वापस ret;
	पूर्ण

	data->gpio_समाप्त = devm_gpiod_get(&pdev->dev, "kill", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->gpio_समाप्त)) अणु
		ret = PTR_ERR(data->gpio_समाप्त);
		dev_err(&pdev->dev, "unable to claim gpio \"kill\"\n");
		वापस ret;
	पूर्ण

	data->gpio_trigger = devm_gpiod_get_optional(&pdev->dev, "trigger",
						     GPIOD_IN);
	अगर (IS_ERR(data->gpio_trigger)) अणु
		/*
		 * It's not a problem if the trigger gpio isn't available, but
		 * it is worth a warning अगर its use was defined in the device
		 * tree.
		 */
		dev_err(&pdev->dev, "unable to claim gpio \"trigger\"\n");
		data->gpio_trigger = शून्य;
	पूर्ण

	अगर (devm_request_irq(&pdev->dev, gpiod_to_irq(data->gpio_trigger),
			     ltc2952_घातeroff_handler,
			     (IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING),
			     "ltc2952-poweroff",
			     data)) अणु
		/*
		 * Some things may have happened:
		 * - No trigger input was defined
		 * - Claiming the GPIO failed
		 * - We could not map to an IRQ
		 * - We couldn't रेजिस्टर an पूर्णांकerrupt handler
		 *
		 * None of these really are problems, but all of them
		 * disqualअगरy the push button from controlling the घातer.
		 *
		 * It is thereक्रमe important to note that अगर the ltc2952
		 * detects a button press क्रम दीर्घ enough, it will still start
		 * its own घातerकरोwn winकरोw and cut the घातer on us अगर we करोn't
		 * start the watchकरोg trigger.
		 */
		अगर (data->gpio_trigger) अणु
			dev_warn(&pdev->dev,
				 "unable to configure the trigger interrupt\n");
			devm_gpiod_put(&pdev->dev, data->gpio_trigger);
			data->gpio_trigger = शून्य;
		पूर्ण
		dev_info(&pdev->dev,
			 "power down trigger input will not be used\n");
		ltc2952_घातeroff_start_wde(data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2952_घातeroff_notअगरy_panic(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ code, व्योम *unused)
अणु
	काष्ठा ltc2952_घातeroff *data = to_ltc2952(nb, panic_notअगरier);

	data->kernel_panic = true;
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ltc2952_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा ltc2952_घातeroff *data;

	अगर (pm_घातer_off) अणु
		dev_err(&pdev->dev, "pm_power_off already registered");
		वापस -EBUSY;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, data);

	ret = ltc2952_घातeroff_init(pdev);
	अगर (ret)
		वापस ret;

	/* TODO: हटाओ ltc2952_data */
	ltc2952_data = data;
	pm_घातer_off = ltc2952_घातeroff_समाप्त;

	data->panic_notअगरier.notअगरier_call = ltc2952_घातeroff_notअगरy_panic;
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &data->panic_notअगरier);
	dev_info(&pdev->dev, "probe successful\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2952_घातeroff_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ltc2952_घातeroff *data = platक्रमm_get_drvdata(pdev);

	pm_घातer_off = शून्य;
	hrसमयr_cancel(&data->समयr_trigger);
	hrसमयr_cancel(&data->समयr_wde);
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &data->panic_notअगरier);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_ltc2952_घातeroff_match[] = अणु
	अणु .compatible = "lltc,ltc2952"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_ltc2952_घातeroff_match);

अटल काष्ठा platक्रमm_driver ltc2952_घातeroff_driver = अणु
	.probe = ltc2952_घातeroff_probe,
	.हटाओ = ltc2952_घातeroff_हटाओ,
	.driver = अणु
		.name = "ltc2952-poweroff",
		.of_match_table = of_ltc2952_घातeroff_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ltc2952_घातeroff_driver);

MODULE_AUTHOR("Renथऊ Moll <rene.moll@xsens.com>");
MODULE_DESCRIPTION("LTC PowerPath power-off driver");
MODULE_LICENSE("GPL v2");
