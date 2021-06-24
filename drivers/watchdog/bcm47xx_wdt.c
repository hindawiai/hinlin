<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Watchकरोg driver क्रम Broadcom BCM47XX
 *
 *  Copyright (C) 2008 Aleksandar Raकरोvanovic <biblbroks@sezampro.rs>
 *  Copyright (C) 2009 Matthieu CASTET <castet.matthieu@मुक्त.fr>
 *  Copyright (C) 2012-2013 Hauke Mehrtens <hauke@hauke-m.de>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bcm47xx_wdt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRV_NAME		"bcm47xx_wdt"

#घोषणा WDT_DEFAULT_TIME	30	/* seconds */
#घोषणा WDT_SOFTTIMER_MAX	255	/* seconds */
#घोषणा WDT_SOFTTIMER_THRESHOLD	60	/* seconds */

अटल पूर्णांक समयout = WDT_DEFAULT_TIME;
अटल bool nowayout = WATCHDOG_NOWAYOUT;

module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog time in seconds. (default="
				__MODULE_STRING(WDT_DEFAULT_TIME) ")");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अंतरभूत काष्ठा bcm47xx_wdt *bcm47xx_wdt_get(काष्ठा watchकरोg_device *wdd)
अणु
	वापस container_of(wdd, काष्ठा bcm47xx_wdt, wdd);
पूर्ण

अटल पूर्णांक bcm47xx_wdt_hard_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);

	wdt->समयr_set_ms(wdt, wdd->समयout * 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_hard_start(काष्ठा watchकरोg_device *wdd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_hard_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);

	wdt->समयr_set(wdt, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_hard_set_समयout(काष्ठा watchकरोg_device *wdd,
					अचिन्हित पूर्णांक new_समय)
अणु
	काष्ठा bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);
	u32 max_समयr = wdt->max_समयr_ms;

	अगर (new_समय < 1 || new_समय > max_समयr / 1000) अणु
		pr_warn("timeout value must be 1<=x<=%d, using %d\n",
			max_समयr / 1000, new_समय);
		वापस -EINVAL;
	पूर्ण

	wdd->समयout = new_समय;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_restart(काष्ठा watchकरोg_device *wdd,
			       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);

	wdt->समयr_set(wdt, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops bcm47xx_wdt_hard_ops = अणु
	.owner		= THIS_MODULE,
	.start		= bcm47xx_wdt_hard_start,
	.stop		= bcm47xx_wdt_hard_stop,
	.ping		= bcm47xx_wdt_hard_keepalive,
	.set_समयout	= bcm47xx_wdt_hard_set_समयout,
	.restart        = bcm47xx_wdt_restart,
पूर्ण;

अटल व्योम bcm47xx_wdt_soft_समयr_tick(काष्ठा समयr_list *t)
अणु
	काष्ठा bcm47xx_wdt *wdt = from_समयr(wdt, t, soft_समयr);
	u32 next_tick = min(wdt->wdd.समयout * 1000, wdt->max_समयr_ms);

	अगर (!atomic_dec_and_test(&wdt->soft_ticks)) अणु
		wdt->समयr_set_ms(wdt, next_tick);
		mod_समयr(&wdt->soft_समयr, jअगरfies + HZ);
	पूर्ण अन्यथा अणु
		pr_crit("Watchdog will fire soon!!!\n");
	पूर्ण
पूर्ण

अटल पूर्णांक bcm47xx_wdt_soft_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);

	atomic_set(&wdt->soft_ticks, wdd->समयout);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_soft_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);

	bcm47xx_wdt_soft_keepalive(wdd);
	bcm47xx_wdt_soft_समयr_tick(&wdt->soft_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_soft_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);

	del_समयr_sync(&wdt->soft_समयr);
	wdt->समयr_set(wdt, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_soft_set_समयout(काष्ठा watchकरोg_device *wdd,
					अचिन्हित पूर्णांक new_समय)
अणु
	अगर (new_समय < 1 || new_समय > WDT_SOFTTIMER_MAX) अणु
		pr_warn("timeout value must be 1<=x<=%d, using %d\n",
			WDT_SOFTTIMER_MAX, new_समय);
		वापस -EINVAL;
	पूर्ण

	wdd->समयout = new_समय;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info bcm47xx_wdt_info = अणु
	.identity	= DRV_NAME,
	.options	= WDIOF_SETTIMEOUT |
				WDIOF_KEEPALIVEPING |
				WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops bcm47xx_wdt_soft_ops = अणु
	.owner		= THIS_MODULE,
	.start		= bcm47xx_wdt_soft_start,
	.stop		= bcm47xx_wdt_soft_stop,
	.ping		= bcm47xx_wdt_soft_keepalive,
	.set_समयout	= bcm47xx_wdt_soft_set_समयout,
	.restart        = bcm47xx_wdt_restart,
पूर्ण;

अटल पूर्णांक bcm47xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	bool soft;
	काष्ठा bcm47xx_wdt *wdt = dev_get_platdata(&pdev->dev);

	अगर (!wdt)
		वापस -ENXIO;

	soft = wdt->max_समयr_ms < WDT_SOFTTIMER_THRESHOLD * 1000;

	अगर (soft) अणु
		wdt->wdd.ops = &bcm47xx_wdt_soft_ops;
		समयr_setup(&wdt->soft_समयr, bcm47xx_wdt_soft_समयr_tick, 0);
	पूर्ण अन्यथा अणु
		wdt->wdd.ops = &bcm47xx_wdt_hard_ops;
	पूर्ण

	wdt->wdd.info = &bcm47xx_wdt_info;
	wdt->wdd.समयout = WDT_DEFAULT_TIME;
	wdt->wdd.parent = &pdev->dev;
	ret = wdt->wdd.ops->set_समयout(&wdt->wdd, समयout);
	अगर (ret)
		जाओ err_समयr;
	watchकरोg_set_nowayout(&wdt->wdd, nowayout);
	watchकरोg_set_restart_priority(&wdt->wdd, 64);
	watchकरोg_stop_on_reboot(&wdt->wdd);

	ret = watchकरोg_रेजिस्टर_device(&wdt->wdd);
	अगर (ret)
		जाओ err_समयr;

	dev_info(&pdev->dev, "BCM47xx Watchdog Timer enabled (%d seconds%s%s)\n",
		समयout, nowayout ? ", nowayout" : "",
		soft ? ", Software Timer" : "");
	वापस 0;

err_समयr:
	अगर (soft)
		del_समयr_sync(&wdt->soft_समयr);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm47xx_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm47xx_wdt *wdt = dev_get_platdata(&pdev->dev);

	watchकरोg_unरेजिस्टर_device(&wdt->wdd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm47xx_wdt_driver = अणु
	.driver		= अणु
		.name	= "bcm47xx-wdt",
	पूर्ण,
	.probe		= bcm47xx_wdt_probe,
	.हटाओ		= bcm47xx_wdt_हटाओ,
पूर्ण;

module_platक्रमm_driver(bcm47xx_wdt_driver);

MODULE_AUTHOR("Aleksandar Radovanovic");
MODULE_AUTHOR("Hauke Mehrtens <hauke@hauke-m.de>");
MODULE_DESCRIPTION("Watchdog driver for Broadcom BCM47xx");
MODULE_LICENSE("GPL");
