<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम the A21 VME CPU Boards
 *
 * Copyright (C) 2013 MEN Mikro Elektronik Nuernberg GmbH
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of.h>

#घोषणा NUM_GPIOS 6

क्रमागत a21_wdt_gpios अणु
	GPIO_WD_ENAB,
	GPIO_WD_FAST,
	GPIO_WD_TRIG,
	GPIO_WD_RST0,
	GPIO_WD_RST1,
	GPIO_WD_RST2,
पूर्ण;

काष्ठा a21_wdt_drv अणु
	काष्ठा watchकरोg_device wdt;
	काष्ठा gpio_desc *gpios[NUM_GPIOS];
पूर्ण;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			    __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अचिन्हित पूर्णांक a21_wdt_get_bootstatus(काष्ठा a21_wdt_drv *drv)
अणु
	पूर्णांक reset = 0;

	reset |= gpiod_get_value(drv->gpios[GPIO_WD_RST0]) ? (1 << 0) : 0;
	reset |= gpiod_get_value(drv->gpios[GPIO_WD_RST1]) ? (1 << 1) : 0;
	reset |= gpiod_get_value(drv->gpios[GPIO_WD_RST2]) ? (1 << 2) : 0;

	वापस reset;
पूर्ण

अटल पूर्णांक a21_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा a21_wdt_drv *drv = watchकरोg_get_drvdata(wdt);

	gpiod_set_value(drv->gpios[GPIO_WD_ENAB], 1);

	वापस 0;
पूर्ण

अटल पूर्णांक a21_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा a21_wdt_drv *drv = watchकरोg_get_drvdata(wdt);

	gpiod_set_value(drv->gpios[GPIO_WD_ENAB], 0);

	वापस 0;
पूर्ण

अटल पूर्णांक a21_wdt_ping(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा a21_wdt_drv *drv = watchकरोg_get_drvdata(wdt);

	gpiod_set_value(drv->gpios[GPIO_WD_TRIG], 0);
	ndelay(10);
	gpiod_set_value(drv->gpios[GPIO_WD_TRIG], 1);

	वापस 0;
पूर्ण

अटल पूर्णांक a21_wdt_set_समयout(काष्ठा watchकरोg_device *wdt,
			       अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा a21_wdt_drv *drv = watchकरोg_get_drvdata(wdt);

	अगर (समयout != 1 && समयout != 30) अणु
		dev_err(wdt->parent, "Only 1 and 30 allowed as timeout\n");
		वापस -EINVAL;
	पूर्ण

	अगर (समयout == 30 && wdt->समयout == 1) अणु
		dev_err(wdt->parent,
			"Transition from fast to slow mode not allowed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (समयout == 1)
		gpiod_set_value(drv->gpios[GPIO_WD_FAST], 1);
	अन्यथा
		gpiod_set_value(drv->gpios[GPIO_WD_FAST], 0);

	wdt->समयout = समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info a21_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "MEN A21 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops a21_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = a21_wdt_start,
	.stop = a21_wdt_stop,
	.ping = a21_wdt_ping,
	.set_समयout = a21_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device a21_wdt = अणु
	.info = &a21_wdt_info,
	.ops = &a21_wdt_ops,
	.min_समयout = 1,
	.max_समयout = 30,
पूर्ण;

अटल पूर्णांक a21_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा a21_wdt_drv *drv;
	अचिन्हित पूर्णांक reset = 0;
	पूर्णांक num_gpios;
	पूर्णांक ret;
	पूर्णांक i;

	drv = devm_kzalloc(dev, माप(काष्ठा a21_wdt_drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	num_gpios = gpiod_count(dev, शून्य);
	अगर (num_gpios != NUM_GPIOS) अणु
		dev_err(dev, "gpios DT property wrong, got %d want %d",
			num_gpios, NUM_GPIOS);
		वापस -ENODEV;
	पूर्ण

	/* Request the used GPIOs */
	क्रम (i = 0; i < num_gpios; i++) अणु
		क्रमागत gpiod_flags gflags;

		अगर (i < GPIO_WD_RST0)
			gflags = GPIOD_ASIS;
		अन्यथा
			gflags = GPIOD_IN;
		drv->gpios[i] = devm_gpiod_get_index(dev, शून्य, i, gflags);
		अगर (IS_ERR(drv->gpios[i]))
			वापस PTR_ERR(drv->gpios[i]);

		gpiod_set_consumer_name(drv->gpios[i], "MEN A21 Watchdog");

		/*
		 * Retrieve the initial value from the GPIOs that should be
		 * output, then set up the line as output with that value.
		 */
		अगर (i < GPIO_WD_RST0) अणु
			पूर्णांक val;

			val = gpiod_get_value(drv->gpios[i]);
			gpiod_direction_output(drv->gpios[i], val);
		पूर्ण
	पूर्ण

	watchकरोg_init_समयout(&a21_wdt, 30, dev);
	watchकरोg_set_nowayout(&a21_wdt, nowayout);
	watchकरोg_set_drvdata(&a21_wdt, drv);
	a21_wdt.parent = dev;

	reset = a21_wdt_get_bootstatus(drv);
	अगर (reset == 2)
		a21_wdt.bootstatus |= WDIOF_EXTERN1;
	अन्यथा अगर (reset == 4)
		a21_wdt.bootstatus |= WDIOF_CARDRESET;
	अन्यथा अगर (reset == 5)
		a21_wdt.bootstatus |= WDIOF_POWERUNDER;
	अन्यथा अगर (reset == 7)
		a21_wdt.bootstatus |= WDIOF_EXTERN2;

	drv->wdt = a21_wdt;
	dev_set_drvdata(dev, drv);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &a21_wdt);
	अगर (ret)
		वापस ret;

	dev_info(dev, "MEN A21 watchdog timer driver enabled\n");

	वापस 0;
पूर्ण

अटल व्योम a21_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा a21_wdt_drv *drv = dev_get_drvdata(&pdev->dev);

	gpiod_set_value(drv->gpios[GPIO_WD_ENAB], 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id a21_wdt_ids[] = अणु
	अणु .compatible = "men,a021-wdt" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, a21_wdt_ids);

अटल काष्ठा platक्रमm_driver a21_wdt_driver = अणु
	.probe = a21_wdt_probe,
	.shutकरोwn = a21_wdt_shutकरोwn,
	.driver = अणु
		.name = "a21-watchdog",
		.of_match_table = a21_wdt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(a21_wdt_driver);

MODULE_AUTHOR("MEN Mikro Elektronik");
MODULE_DESCRIPTION("MEN A21 Watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:a21-watchdog");
