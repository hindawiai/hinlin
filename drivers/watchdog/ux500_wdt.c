<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2011-2013
 *
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org> क्रम ST-Ericsson
 * Author: Jonas Aaberg <jonas.aberg@stericsson.com> क्रम ST-Ericsson
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/err.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/ux500_wdt.h>

#समावेश <linux/mfd/dbx500-prcmu.h>

#घोषणा WATCHDOG_TIMEOUT 600 /* 10 minutes */

#घोषणा WATCHDOG_MIN	0
#घोषणा WATCHDOG_MAX28	268435  /* 28 bit resolution in ms == 268435.455 s */
#घोषणा WATCHDOG_MAX32	4294967 /* 32 bit resolution in ms == 4294967.295 s */

अटल अचिन्हित पूर्णांक समयout = WATCHDOG_TIMEOUT;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक ux500_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	वापस prcmu_enable_a9wकरोg(PRCMU_WDOG_ALL);
पूर्ण

अटल पूर्णांक ux500_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	वापस prcmu_disable_a9wकरोg(PRCMU_WDOG_ALL);
पूर्ण

अटल पूर्णांक ux500_wdt_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	वापस prcmu_kick_a9wकरोg(PRCMU_WDOG_ALL);
पूर्ण

अटल पूर्णांक ux500_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				 अचिन्हित पूर्णांक समयout)
अणु
	ux500_wdt_stop(wdd);
	prcmu_load_a9wकरोg(PRCMU_WDOG_ALL, समयout * 1000);
	ux500_wdt_start(wdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ux500_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "Ux500 WDT",
	.firmware_version = 1,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ux500_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = ux500_wdt_start,
	.stop  = ux500_wdt_stop,
	.ping  = ux500_wdt_keepalive,
	.set_समयout = ux500_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device ux500_wdt = अणु
	.info = &ux500_wdt_info,
	.ops = &ux500_wdt_ops,
	.min_समयout = WATCHDOG_MIN,
	.max_समयout = WATCHDOG_MAX32,
पूर्ण;

अटल पूर्णांक ux500_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	काष्ठा ux500_wdt_data *pdata = dev_get_platdata(dev);

	अगर (pdata) अणु
		अगर (pdata->समयout > 0)
			समयout = pdata->समयout;
		अगर (pdata->has_28_bits_resolution)
			ux500_wdt.max_समयout = WATCHDOG_MAX28;
	पूर्ण

	ux500_wdt.parent = dev;
	watchकरोg_set_nowayout(&ux500_wdt, nowayout);

	/* disable स्वतः off on sleep */
	prcmu_config_a9wकरोg(PRCMU_WDOG_CPU1, false);

	/* set HW initial value */
	prcmu_load_a9wकरोg(PRCMU_WDOG_ALL, समयout * 1000);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &ux500_wdt);
	अगर (ret)
		वापस ret;

	dev_info(dev, "initialized\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ux500_wdt_suspend(काष्ठा platक्रमm_device *pdev,
			     pm_message_t state)
अणु
	अगर (watchकरोg_active(&ux500_wdt)) अणु
		ux500_wdt_stop(&ux500_wdt);
		prcmu_config_a9wकरोg(PRCMU_WDOG_CPU1, true);

		prcmu_load_a9wकरोg(PRCMU_WDOG_ALL, समयout * 1000);
		ux500_wdt_start(&ux500_wdt);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ux500_wdt_resume(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (watchकरोg_active(&ux500_wdt)) अणु
		ux500_wdt_stop(&ux500_wdt);
		prcmu_config_a9wकरोg(PRCMU_WDOG_CPU1, false);

		prcmu_load_a9wकरोg(PRCMU_WDOG_ALL, समयout * 1000);
		ux500_wdt_start(&ux500_wdt);
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ux500_wdt_suspend शून्य
#घोषणा ux500_wdt_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ux500_wdt_driver = अणु
	.probe		= ux500_wdt_probe,
	.suspend	= ux500_wdt_suspend,
	.resume		= ux500_wdt_resume,
	.driver		= अणु
		.name	= "ux500_wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ux500_wdt_driver);

MODULE_AUTHOR("Jonas Aaberg <jonas.aberg@stericsson.com>");
MODULE_DESCRIPTION("Ux500 Watchdog Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ux500_wdt");
