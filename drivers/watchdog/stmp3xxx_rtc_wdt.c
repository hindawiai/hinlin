<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg driver क्रम the RTC based watchकरोg in STMP3xxx and i.MX23/28
 *
 * Author: Wolfram Sang <kernel@pengutronix.de>
 *
 * Copyright (C) 2011-12 Wolfram Sang, Pengutronix
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sपंचांगp3xxx_rtc_wdt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>

#घोषणा WDOG_TICK_RATE 1000 /* 1 kHz घड़ी */
#घोषणा STMP3XXX_DEFAULT_TIMEOUT 19
#घोषणा STMP3XXX_MAX_TIMEOUT (अच_पूर्णांक_उच्च / WDOG_TICK_RATE)

अटल पूर्णांक heartbeat = STMP3XXX_DEFAULT_TIMEOUT;
module_param(heartbeat, uपूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeat period in seconds from 1 to "
		 __MODULE_STRING(STMP3XXX_MAX_TIMEOUT) ", default "
		 __MODULE_STRING(STMP3XXX_DEFAULT_TIMEOUT));

अटल पूर्णांक wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा device *dev = watchकरोg_get_drvdata(wdd);
	काष्ठा sपंचांगp3xxx_wdt_pdata *pdata = dev_get_platdata(dev);

	pdata->wdt_set_समयout(dev->parent, wdd->समयout * WDOG_TICK_RATE);
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा device *dev = watchकरोg_get_drvdata(wdd);
	काष्ठा sपंचांगp3xxx_wdt_pdata *pdata = dev_get_platdata(dev);

	pdata->wdt_set_समयout(dev->parent, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित new_समयout)
अणु
	wdd->समयout = new_समयout;
	वापस wdt_start(wdd);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sपंचांगp3xxx_wdt_ident = अणु
	.options = WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = "STMP3XXX RTC Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops sपंचांगp3xxx_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wdt_start,
	.stop = wdt_stop,
	.set_समयout = wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device sपंचांगp3xxx_wdd = अणु
	.info = &sपंचांगp3xxx_wdt_ident,
	.ops = &sपंचांगp3xxx_wdt_ops,
	.min_समयout = 1,
	.max_समयout = STMP3XXX_MAX_TIMEOUT,
	.status = WATCHDOG_NOWAYOUT_INIT_STATUS,
पूर्ण;

अटल पूर्णांक wdt_notअगरy_sys(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ code,
			  व्योम *unused)
अणु
	चयन (code) अणु
	हाल SYS_DOWN:	/* keep enabled, प्रणाली might crash जबतक going करोwn */
		अवरोध;
	हाल SYS_HALT:	/* allow the प्रणाली to actually halt */
	हाल SYS_POWER_OFF:
		wdt_stop(&sपंचांगp3xxx_wdd);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block wdt_notअगरier = अणु
	.notअगरier_call = wdt_notअगरy_sys,
पूर्ण;

अटल पूर्णांक sपंचांगp3xxx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	watchकरोg_set_drvdata(&sपंचांगp3xxx_wdd, dev);

	sपंचांगp3xxx_wdd.समयout = clamp_t(अचिन्हित, heartbeat, 1, STMP3XXX_MAX_TIMEOUT);
	sपंचांगp3xxx_wdd.parent = dev;

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &sपंचांगp3xxx_wdd);
	अगर (ret < 0)
		वापस ret;

	अगर (रेजिस्टर_reboot_notअगरier(&wdt_notअगरier))
		dev_warn(dev, "cannot register reboot notifier\n");

	dev_info(dev, "initialized watchdog with heartbeat %ds\n",
		 sपंचांगp3xxx_wdd.समयout);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगp3xxx_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगp3xxx_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wdd = &sपंचांगp3xxx_wdd;

	अगर (watchकरोg_active(wdd))
		वापस wdt_stop(wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगp3xxx_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wdd = &sपंचांगp3xxx_wdd;

	अगर (watchकरोg_active(wdd))
		वापस wdt_start(wdd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांगp3xxx_wdt_pm_ops,
			 sपंचांगp3xxx_wdt_suspend, sपंचांगp3xxx_wdt_resume);

अटल काष्ठा platक्रमm_driver sपंचांगp3xxx_wdt_driver = अणु
	.driver = अणु
		.name = "stmp3xxx_rtc_wdt",
		.pm = &sपंचांगp3xxx_wdt_pm_ops,
	पूर्ण,
	.probe = sपंचांगp3xxx_wdt_probe,
	.हटाओ = sपंचांगp3xxx_wdt_हटाओ,
पूर्ण;
module_platक्रमm_driver(sपंचांगp3xxx_wdt_driver);

MODULE_DESCRIPTION("STMP3XXX RTC Watchdog Driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Wolfram Sang <kernel@pengutronix.de>");
