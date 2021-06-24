<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) STMicroelectronics 2018
// Author: Pascal Paillet <p.paillet@st.com> क्रम STMicroelectronics.

#समावेश <linux/kernel.h>
#समावेश <linux/mfd/stpmic1.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/watchकरोg.h>

/* WATCHDOG CONTROL REGISTER bit */
#घोषणा WDT_START		BIT(0)
#घोषणा WDT_PING		BIT(1)
#घोषणा WDT_START_MASK		BIT(0)
#घोषणा WDT_PING_MASK		BIT(1)
#घोषणा WDT_STOP		0

#घोषणा PMIC_WDT_MIN_TIMEOUT 1
#घोषणा PMIC_WDT_MAX_TIMEOUT 256
#घोषणा PMIC_WDT_DEFAULT_TIMEOUT 30

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा stpmic1_wdt अणु
	काष्ठा stpmic1 *pmic;
	काष्ठा watchकरोg_device wdtdev;
पूर्ण;

अटल पूर्णांक pmic_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा stpmic1_wdt *wdt = watchकरोg_get_drvdata(wdd);

	वापस regmap_update_bits(wdt->pmic->regmap,
				  WCHDG_CR, WDT_START_MASK, WDT_START);
पूर्ण

अटल पूर्णांक pmic_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा stpmic1_wdt *wdt = watchकरोg_get_drvdata(wdd);

	वापस regmap_update_bits(wdt->pmic->regmap,
				  WCHDG_CR, WDT_START_MASK, WDT_STOP);
पूर्ण

अटल पूर्णांक pmic_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा stpmic1_wdt *wdt = watchकरोg_get_drvdata(wdd);

	वापस regmap_update_bits(wdt->pmic->regmap,
				  WCHDG_CR, WDT_PING_MASK, WDT_PING);
पूर्ण

अटल पूर्णांक pmic_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा stpmic1_wdt *wdt = watchकरोg_get_drvdata(wdd);

	wdd->समयout = समयout;
	/* समयout is equal to रेजिस्टर value + 1 */
	वापस regmap_ग_लिखो(wdt->pmic->regmap, WCHDG_TIMER_CR, समयout - 1);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info pmic_watchकरोg_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "STPMIC1 PMIC Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops pmic_watchकरोg_ops = अणु
	.owner = THIS_MODULE,
	.start = pmic_wdt_start,
	.stop = pmic_wdt_stop,
	.ping = pmic_wdt_ping,
	.set_समयout = pmic_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक pmic_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	काष्ठा stpmic1 *pmic;
	काष्ठा stpmic1_wdt *wdt;

	अगर (!dev->parent)
		वापस -EINVAL;

	pmic = dev_get_drvdata(dev->parent);
	अगर (!pmic)
		वापस -EINVAL;

	wdt = devm_kzalloc(dev, माप(काष्ठा stpmic1_wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->pmic = pmic;

	wdt->wdtdev.info = &pmic_watchकरोg_info;
	wdt->wdtdev.ops = &pmic_watchकरोg_ops;
	wdt->wdtdev.min_समयout = PMIC_WDT_MIN_TIMEOUT;
	wdt->wdtdev.max_समयout = PMIC_WDT_MAX_TIMEOUT;
	wdt->wdtdev.parent = dev;

	wdt->wdtdev.समयout = PMIC_WDT_DEFAULT_TIMEOUT;
	watchकरोg_init_समयout(&wdt->wdtdev, 0, dev);

	watchकरोg_set_nowayout(&wdt->wdtdev, nowayout);
	watchकरोg_set_drvdata(&wdt->wdtdev, wdt);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdtdev);
	अगर (ret)
		वापस ret;

	dev_dbg(wdt->pmic->dev, "PMIC Watchdog driver probed\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pmic_wdt_match[] = अणु
	अणु .compatible = "st,stpmic1-wdt" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_pmic_wdt_match);

अटल काष्ठा platक्रमm_driver stpmic1_wdt_driver = अणु
	.probe = pmic_wdt_probe,
	.driver = अणु
		.name = "stpmic1-wdt",
		.of_match_table = of_pmic_wdt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(stpmic1_wdt_driver);

MODULE_DESCRIPTION("Watchdog driver for STPMIC1 device");
MODULE_AUTHOR("Pascal Paillet <p.paillet@st.com>");
MODULE_LICENSE("GPL v2");
