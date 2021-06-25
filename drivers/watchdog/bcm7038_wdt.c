<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Broadcom Corporation
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/watchकरोg.h>

#घोषणा WDT_START_1		0xff00
#घोषणा WDT_START_2		0x00ff
#घोषणा WDT_STOP_1		0xee00
#घोषणा WDT_STOP_2		0x00ee

#घोषणा WDT_TIMEOUT_REG		0x0
#घोषणा WDT_CMD_REG		0x4

#घोषणा WDT_MIN_TIMEOUT		1 /* seconds */
#घोषणा WDT_DEFAULT_TIMEOUT	30 /* seconds */
#घोषणा WDT_DEFAULT_RATE	27000000

काष्ठा bcm7038_watchकरोg अणु
	व्योम __iomem		*base;
	काष्ठा watchकरोg_device	wdd;
	u32			rate;
	काष्ठा clk		*clk;
पूर्ण;

अटल bool nowayout = WATCHDOG_NOWAYOUT;

अटल व्योम bcm7038_wdt_set_समयout_reg(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm7038_watchकरोg *wdt = watchकरोg_get_drvdata(wकरोg);
	u32 समयout;

	समयout = wdt->rate * wकरोg->समयout;

	ग_लिखोl(समयout, wdt->base + WDT_TIMEOUT_REG);
पूर्ण

अटल पूर्णांक bcm7038_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm7038_watchकरोg *wdt = watchकरोg_get_drvdata(wकरोg);

	ग_लिखोl(WDT_START_1, wdt->base + WDT_CMD_REG);
	ग_लिखोl(WDT_START_2, wdt->base + WDT_CMD_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7038_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	bcm7038_wdt_set_समयout_reg(wकरोg);
	bcm7038_wdt_ping(wकरोg);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7038_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm7038_watchकरोg *wdt = watchकरोg_get_drvdata(wकरोg);

	ग_लिखोl(WDT_STOP_1, wdt->base + WDT_CMD_REG);
	ग_लिखोl(WDT_STOP_2, wdt->base + WDT_CMD_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7038_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				   अचिन्हित पूर्णांक t)
अणु
	/* Can't modअगरy समयout value अगर watchकरोg समयr is running */
	bcm7038_wdt_stop(wकरोg);
	wकरोg->समयout = t;
	bcm7038_wdt_start(wकरोg);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक bcm7038_wdt_get_समयleft(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm7038_watchकरोg *wdt = watchकरोg_get_drvdata(wकरोg);
	u32 समय_left;

	समय_left = पढ़ोl(wdt->base + WDT_CMD_REG);

	वापस समय_left / wdt->rate;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info bcm7038_wdt_info = अणु
	.identity	= "Broadcom BCM7038 Watchdog Timer",
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
				WDIOF_MAGICCLOSE
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops bcm7038_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= bcm7038_wdt_start,
	.stop		= bcm7038_wdt_stop,
	.set_समयout	= bcm7038_wdt_set_समयout,
	.get_समयleft	= bcm7038_wdt_get_समयleft,
पूर्ण;

अटल व्योम bcm7038_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक bcm7038_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm7038_watchकरोg *wdt;
	पूर्णांक err;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, wdt);

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	wdt->clk = devm_clk_get(dev, शून्य);
	/* If unable to get घड़ी, use शेष frequency */
	अगर (!IS_ERR(wdt->clk)) अणु
		err = clk_prepare_enable(wdt->clk);
		अगर (err)
			वापस err;
		err = devm_add_action_or_reset(dev,
					       bcm7038_clk_disable_unprepare,
					       wdt->clk);
		अगर (err)
			वापस err;
		wdt->rate = clk_get_rate(wdt->clk);
		/* Prevent भागide-by-zero exception */
		अगर (!wdt->rate)
			wdt->rate = WDT_DEFAULT_RATE;
	पूर्ण अन्यथा अणु
		wdt->rate = WDT_DEFAULT_RATE;
		wdt->clk = शून्य;
	पूर्ण

	wdt->wdd.info		= &bcm7038_wdt_info;
	wdt->wdd.ops		= &bcm7038_wdt_ops;
	wdt->wdd.min_समयout	= WDT_MIN_TIMEOUT;
	wdt->wdd.समयout	= WDT_DEFAULT_TIMEOUT;
	wdt->wdd.max_समयout	= 0xffffffff / wdt->rate;
	wdt->wdd.parent		= dev;
	watchकरोg_set_drvdata(&wdt->wdd, wdt);

	watchकरोg_stop_on_reboot(&wdt->wdd);
	watchकरोg_stop_on_unरेजिस्टर(&wdt->wdd);
	err = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);
	अगर (err)
		वापस err;

	dev_info(dev, "Registered BCM7038 Watchdog\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bcm7038_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा bcm7038_watchकरोg *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		वापस bcm7038_wdt_stop(&wdt->wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7038_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा bcm7038_watchकरोg *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		वापस bcm7038_wdt_start(&wdt->wdd);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(bcm7038_wdt_pm_ops, bcm7038_wdt_suspend,
			 bcm7038_wdt_resume);

अटल स्थिर काष्ठा of_device_id bcm7038_wdt_match[] = अणु
	अणु .compatible = "brcm,bcm7038-wdt" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm7038_wdt_match);

अटल काष्ठा platक्रमm_driver bcm7038_wdt_driver = अणु
	.probe		= bcm7038_wdt_probe,
	.driver		= अणु
		.name		= "bcm7038-wdt",
		.of_match_table	= bcm7038_wdt_match,
		.pm		= &bcm7038_wdt_pm_ops,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(bcm7038_wdt_driver);

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for Broadcom 7038 SoCs Watchdog");
MODULE_AUTHOR("Justin Chen");
