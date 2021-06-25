<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Nokia Corporation
 *
 * Written by Timo Kokkonen <timo.t.kokkonen at nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/twl.h>

#घोषणा TWL4030_WATCHDOG_CFG_REG_OFFS	0x3

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक twl4030_wdt_ग_लिखो(अचिन्हित अक्षर val)
अणु
	वापस twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_RECEIVER, val,
					TWL4030_WATCHDOG_CFG_REG_OFFS);
पूर्ण

अटल पूर्णांक twl4030_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	वापस twl4030_wdt_ग_लिखो(wdt->समयout + 1);
पूर्ण

अटल पूर्णांक twl4030_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	वापस twl4030_wdt_ग_लिखो(0);
पूर्ण

अटल पूर्णांक twl4030_wdt_set_समयout(काष्ठा watchकरोg_device *wdt,
				   अचिन्हित पूर्णांक समयout)
अणु
	wdt->समयout = समयout;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info twl4030_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "TWL4030 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops twl4030_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= twl4030_wdt_start,
	.stop		= twl4030_wdt_stop,
	.set_समयout	= twl4030_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक twl4030_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdt;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->info		= &twl4030_wdt_info;
	wdt->ops		= &twl4030_wdt_ops;
	wdt->status		= 0;
	wdt->समयout		= 30;
	wdt->min_समयout	= 1;
	wdt->max_समयout	= 30;
	wdt->parent = dev;

	watchकरोg_set_nowayout(wdt, nowayout);
	platक्रमm_set_drvdata(pdev, wdt);

	twl4030_wdt_stop(wdt);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wdt);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक twl4030_wdt_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा watchकरोg_device *wdt = platक्रमm_get_drvdata(pdev);
	अगर (watchकरोg_active(wdt))
		वापस twl4030_wdt_stop(wdt);

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_wdt_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा watchकरोg_device *wdt = platक्रमm_get_drvdata(pdev);
	अगर (watchकरोg_active(wdt))
		वापस twl4030_wdt_start(wdt);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा twl4030_wdt_suspend        शून्य
#घोषणा twl4030_wdt_resume         शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id twl_wdt_of_match[] = अणु
	अणु .compatible = "ti,twl4030-wdt", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_wdt_of_match);

अटल काष्ठा platक्रमm_driver twl4030_wdt_driver = अणु
	.probe		= twl4030_wdt_probe,
	.suspend	= twl4030_wdt_suspend,
	.resume		= twl4030_wdt_resume,
	.driver		= अणु
		.name		= "twl4030_wdt",
		.of_match_table	= twl_wdt_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(twl4030_wdt_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:twl4030_wdt");

