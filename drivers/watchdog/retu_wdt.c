<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Retu watchकरोg driver
 *
 * Copyright (C) 2004, 2005 Nokia Corporation
 *
 * Based on code written by Amit Kucheria and Michael Buesch.
 * Rewritten by Aaro Koskinen.
 */

#समावेश <linux/devm-helpers.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/retu.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>

/* Watchकरोg समयr values in seconds */
#घोषणा RETU_WDT_MAX_TIMER	63

काष्ठा retu_wdt_dev अणु
	काष्ठा retu_dev		*rdev;
	काष्ठा device		*dev;
	काष्ठा delayed_work	ping_work;
पूर्ण;

/*
 * Since Retu watchकरोg cannot be disabled in hardware, we must kick it
 * with a समयr until userspace watchकरोg software takes over. If
 * CONFIG_WATCHDOG_NOWAYOUT is set, we never start the feeding.
 */
अटल व्योम retu_wdt_ping_enable(काष्ठा retu_wdt_dev *wdev)
अणु
	retu_ग_लिखो(wdev->rdev, RETU_REG_WATCHDOG, RETU_WDT_MAX_TIMER);
	schedule_delayed_work(&wdev->ping_work,
			round_jअगरfies_relative(RETU_WDT_MAX_TIMER * HZ / 2));
पूर्ण

अटल व्योम retu_wdt_ping_disable(काष्ठा retu_wdt_dev *wdev)
अणु
	retu_ग_लिखो(wdev->rdev, RETU_REG_WATCHDOG, RETU_WDT_MAX_TIMER);
	cancel_delayed_work_sync(&wdev->ping_work);
पूर्ण

अटल व्योम retu_wdt_ping_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा retu_wdt_dev *wdev = container_of(to_delayed_work(work),
						काष्ठा retu_wdt_dev, ping_work);
	retu_wdt_ping_enable(wdev);
पूर्ण

अटल पूर्णांक retu_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा retu_wdt_dev *wdev = watchकरोg_get_drvdata(wकरोg);

	retu_wdt_ping_disable(wdev);

	वापस retu_ग_लिखो(wdev->rdev, RETU_REG_WATCHDOG, wकरोg->समयout);
पूर्ण

अटल पूर्णांक retu_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा retu_wdt_dev *wdev = watchकरोg_get_drvdata(wकरोg);

	retu_wdt_ping_enable(wdev);

	वापस 0;
पूर्ण

अटल पूर्णांक retu_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा retu_wdt_dev *wdev = watchकरोg_get_drvdata(wकरोg);

	वापस retu_ग_लिखो(wdev->rdev, RETU_REG_WATCHDOG, wकरोg->समयout);
पूर्ण

अटल पूर्णांक retu_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा retu_wdt_dev *wdev = watchकरोg_get_drvdata(wकरोg);

	wकरोg->समयout = समयout;
	वापस retu_ग_लिखो(wdev->rdev, RETU_REG_WATCHDOG, wकरोg->समयout);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info retu_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "Retu watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops retu_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= retu_wdt_start,
	.stop		= retu_wdt_stop,
	.ping		= retu_wdt_ping,
	.set_समयout	= retu_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक retu_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा retu_dev *rdev = dev_get_drvdata(pdev->dev.parent);
	bool nowayout = WATCHDOG_NOWAYOUT;
	काष्ठा watchकरोg_device *retu_wdt;
	काष्ठा retu_wdt_dev *wdev;
	पूर्णांक ret;

	retu_wdt = devm_kzalloc(&pdev->dev, माप(*retu_wdt), GFP_KERNEL);
	अगर (!retu_wdt)
		वापस -ENOMEM;

	wdev = devm_kzalloc(&pdev->dev, माप(*wdev), GFP_KERNEL);
	अगर (!wdev)
		वापस -ENOMEM;

	retu_wdt->info		= &retu_wdt_info;
	retu_wdt->ops		= &retu_wdt_ops;
	retu_wdt->समयout	= RETU_WDT_MAX_TIMER;
	retu_wdt->min_समयout	= 0;
	retu_wdt->max_समयout	= RETU_WDT_MAX_TIMER;
	retu_wdt->parent	= &pdev->dev;

	watchकरोg_set_drvdata(retu_wdt, wdev);
	watchकरोg_set_nowayout(retu_wdt, nowayout);

	wdev->rdev		= rdev;
	wdev->dev		= &pdev->dev;

	ret = devm_delayed_work_स्वतःcancel(&pdev->dev, &wdev->ping_work,
					   retu_wdt_ping_work);
	अगर (ret)
		वापस ret;

	ret = devm_watchकरोg_रेजिस्टर_device(&pdev->dev, retu_wdt);
	अगर (ret < 0)
		वापस ret;

	अगर (nowayout)
		retu_wdt_ping(retu_wdt);
	अन्यथा
		retu_wdt_ping_enable(wdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver retu_wdt_driver = अणु
	.probe		= retu_wdt_probe,
	.driver		= अणु
		.name	= "retu-wdt",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(retu_wdt_driver);

MODULE_ALIAS("platform:retu-wdt");
MODULE_DESCRIPTION("Retu watchdog");
MODULE_AUTHOR("Amit Kucheria");
MODULE_AUTHOR("Aaro Koskinen <aaro.koskinen@iki.fi>");
MODULE_LICENSE("GPL");
