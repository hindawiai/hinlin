<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम the wm8350
 *
 * Copyright (C) 2007, 2008 Wolfson Microelectronics <linux@wolfsonmicro.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mfd/wm8350/core.h>

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल DEFINE_MUTEX(wdt_mutex);

अटल काष्ठा अणु
	अचिन्हित पूर्णांक समय;  /* Seconds */
	u16 val;	    /* To be set in WM8350_SYSTEM_CONTROL_2 */
पूर्ण wm8350_wdt_cfgs[] = अणु
	अणु 1, 0x02 पूर्ण,
	अणु 2, 0x04 पूर्ण,
	अणु 4, 0x05 पूर्ण,
पूर्ण;

अटल पूर्णांक wm8350_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा wm8350 *wm8350 = watchकरोg_get_drvdata(wdt_dev);
	पूर्णांक ret, i;
	u16 reg;

	क्रम (i = 0; i < ARRAY_SIZE(wm8350_wdt_cfgs); i++)
		अगर (wm8350_wdt_cfgs[i].समय == समयout)
			अवरोध;
	अगर (i == ARRAY_SIZE(wm8350_wdt_cfgs))
		वापस -EINVAL;

	mutex_lock(&wdt_mutex);
	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_SYSTEM_CONTROL_2);
	reg &= ~WM8350_WDOG_TO_MASK;
	reg |= wm8350_wdt_cfgs[i].val;
	ret = wm8350_reg_ग_लिखो(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	wm8350_reg_lock(wm8350);
	mutex_unlock(&wdt_mutex);

	wdt_dev->समयout = समयout;
	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा wm8350 *wm8350 = watchकरोg_get_drvdata(wdt_dev);
	पूर्णांक ret;
	u16 reg;

	mutex_lock(&wdt_mutex);
	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_SYSTEM_CONTROL_2);
	reg &= ~WM8350_WDOG_MODE_MASK;
	reg |= 0x20;
	ret = wm8350_reg_ग_लिखो(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	wm8350_reg_lock(wm8350);
	mutex_unlock(&wdt_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा wm8350 *wm8350 = watchकरोg_get_drvdata(wdt_dev);
	पूर्णांक ret;
	u16 reg;

	mutex_lock(&wdt_mutex);
	wm8350_reg_unlock(wm8350);

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_SYSTEM_CONTROL_2);
	reg &= ~WM8350_WDOG_MODE_MASK;
	ret = wm8350_reg_ग_लिखो(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	wm8350_reg_lock(wm8350);
	mutex_unlock(&wdt_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा wm8350 *wm8350 = watchकरोg_get_drvdata(wdt_dev);
	पूर्णांक ret;
	u16 reg;

	mutex_lock(&wdt_mutex);

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_SYSTEM_CONTROL_2);
	ret = wm8350_reg_ग_लिखो(wm8350, WM8350_SYSTEM_CONTROL_2, reg);

	mutex_unlock(&wdt_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info wm8350_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "WM8350 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops wm8350_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wm8350_wdt_start,
	.stop = wm8350_wdt_stop,
	.ping = wm8350_wdt_ping,
	.set_समयout = wm8350_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device wm8350_wdt = अणु
	.info = &wm8350_wdt_info,
	.ops = &wm8350_wdt_ops,
	.समयout = 4,
	.min_समयout = 1,
	.max_समयout = 4,
पूर्ण;

अटल पूर्णांक wm8350_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = platक्रमm_get_drvdata(pdev);

	अगर (!wm8350) अणु
		pr_err("No driver data supplied\n");
		वापस -ENODEV;
	पूर्ण

	watchकरोg_set_nowayout(&wm8350_wdt, nowayout);
	watchकरोg_set_drvdata(&wm8350_wdt, wm8350);
	wm8350_wdt.parent = &pdev->dev;

	/* Default to 4s समयout */
	wm8350_wdt_set_समयout(&wm8350_wdt, 4);

	वापस watchकरोg_रेजिस्टर_device(&wm8350_wdt);
पूर्ण

अटल पूर्णांक wm8350_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	watchकरोg_unरेजिस्टर_device(&wm8350_wdt);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8350_wdt_driver = अणु
	.probe = wm8350_wdt_probe,
	.हटाओ = wm8350_wdt_हटाओ,
	.driver = अणु
		.name = "wm8350-wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm8350_wdt_driver);

MODULE_AUTHOR("Mark Brown");
MODULE_DESCRIPTION("WM8350 Watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-wdt");
