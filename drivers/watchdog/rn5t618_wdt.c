<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Watchकरोg driver क्रम Ricoh RN5T618 PMIC
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/mfd/rn5t618.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DRIVER_NAME "rn5t618-wdt"

अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित पूर्णांक समयout;

module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Initial watchdog timeout in seconds");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा rn5t618_wdt अणु
	काष्ठा watchकरोg_device wdt_dev;
	काष्ठा rn5t618 *rn5t618;
पूर्ण;

/*
 * This array encodes the values of WDOGTIM field क्रम the supported
 * watchकरोg expiration बार. If the watchकरोg is not accessed beक्रमe
 * the समयr expiration, the PMU generates an पूर्णांकerrupt and अगर the CPU
 * करोesn't clear it within one second the प्रणाली is restarted.
 */
अटल स्थिर काष्ठा अणु
	u8 reg_val;
	अचिन्हित पूर्णांक समय;
पूर्ण rn5t618_wdt_map[] = अणु
	अणु 0, 1 पूर्ण,
	अणु 1, 8 पूर्ण,
	अणु 2, 32 पूर्ण,
	अणु 3, 128 पूर्ण,
पूर्ण;

अटल पूर्णांक rn5t618_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				   अचिन्हित पूर्णांक t)
अणु
	काष्ठा rn5t618_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(rn5t618_wdt_map); i++) अणु
		अगर (rn5t618_wdt_map[i].समय + 1 >= t)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(rn5t618_wdt_map))
		वापस -EINVAL;

	ret = regmap_update_bits(wdt->rn5t618->regmap, RN5T618_WATCHDOG,
				 RN5T618_WATCHDOG_WDOGTIM_M,
				 rn5t618_wdt_map[i].reg_val);
	अगर (!ret)
		wdt_dev->समयout = rn5t618_wdt_map[i].समय;

	वापस ret;
पूर्ण

अटल पूर्णांक rn5t618_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा rn5t618_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	पूर्णांक ret;

	ret = rn5t618_wdt_set_समयout(wdt_dev, wdt_dev->समयout);
	अगर (ret)
		वापस ret;

	/* enable reघातer-on */
	ret = regmap_update_bits(wdt->rn5t618->regmap, RN5T618_REPCNT,
				 RN5T618_REPCNT_REPWRON,
				 RN5T618_REPCNT_REPWRON);
	अगर (ret)
		वापस ret;

	/* enable watchकरोg */
	ret = regmap_update_bits(wdt->rn5t618->regmap, RN5T618_WATCHDOG,
				 RN5T618_WATCHDOG_WDOGEN,
				 RN5T618_WATCHDOG_WDOGEN);
	अगर (ret)
		वापस ret;

	/* enable watchकरोg पूर्णांकerrupt */
	वापस regmap_update_bits(wdt->rn5t618->regmap, RN5T618_PWRIREN,
				  RN5T618_PWRIRQ_IR_WDOG,
				  RN5T618_PWRIRQ_IR_WDOG);
पूर्ण

अटल पूर्णांक rn5t618_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा rn5t618_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);

	वापस regmap_update_bits(wdt->rn5t618->regmap, RN5T618_WATCHDOG,
				  RN5T618_WATCHDOG_WDOGEN, 0);
पूर्ण

अटल पूर्णांक rn5t618_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा rn5t618_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* The counter is restarted after a R/W access to watchकरोg रेजिस्टर */
	ret = regmap_पढ़ो(wdt->rn5t618->regmap, RN5T618_WATCHDOG, &val);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(wdt->rn5t618->regmap, RN5T618_WATCHDOG, val);
	अगर (ret)
		वापस ret;

	/* Clear pending watchकरोg पूर्णांकerrupt */
	वापस regmap_update_bits(wdt->rn5t618->regmap, RN5T618_PWRIRQ,
				  RN5T618_PWRIRQ_IR_WDOG, 0);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info rn5t618_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE |
			  WDIOF_KEEPALIVEPING,
	.identity	= DRIVER_NAME,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops rn5t618_wdt_ops = अणु
	.owner          = THIS_MODULE,
	.start          = rn5t618_wdt_start,
	.stop           = rn5t618_wdt_stop,
	.ping           = rn5t618_wdt_ping,
	.set_समयout    = rn5t618_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक rn5t618_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rn5t618 *rn5t618 = dev_get_drvdata(dev->parent);
	काष्ठा rn5t618_wdt *wdt;
	पूर्णांक min_समयout, max_समयout;

	wdt = devm_kzalloc(dev, माप(काष्ठा rn5t618_wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	min_समयout = rn5t618_wdt_map[0].समय;
	max_समयout = rn5t618_wdt_map[ARRAY_SIZE(rn5t618_wdt_map) - 1].समय;

	wdt->rn5t618 = rn5t618;
	wdt->wdt_dev.info = &rn5t618_wdt_info;
	wdt->wdt_dev.ops = &rn5t618_wdt_ops;
	wdt->wdt_dev.min_समयout = min_समयout;
	wdt->wdt_dev.max_समयout = max_समयout;
	wdt->wdt_dev.समयout = max_समयout;
	wdt->wdt_dev.parent = dev;

	watchकरोg_set_drvdata(&wdt->wdt_dev, wdt);
	watchकरोg_init_समयout(&wdt->wdt_dev, समयout, dev);
	watchकरोg_set_nowayout(&wdt->wdt_dev, nowayout);

	platक्रमm_set_drvdata(pdev, wdt);

	वापस watchकरोg_रेजिस्टर_device(&wdt->wdt_dev);
पूर्ण

अटल पूर्णांक rn5t618_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rn5t618_wdt *wdt = platक्रमm_get_drvdata(pdev);

	watchकरोg_unरेजिस्टर_device(&wdt->wdt_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rn5t618_wdt_driver = अणु
	.probe = rn5t618_wdt_probe,
	.हटाओ = rn5t618_wdt_हटाओ,
	.driver = अणु
		.name	= DRIVER_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rn5t618_wdt_driver);

MODULE_ALIAS("platform:rn5t618-wdt");
MODULE_AUTHOR("Beniamino Galvani <b.galvani@gmail.com>");
MODULE_DESCRIPTION("RN5T618 watchdog driver");
MODULE_LICENSE("GPL v2");
