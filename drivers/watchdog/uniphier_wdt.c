<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg driver क्रम the UniPhier watchकरोg समयr
 *
 * (c) Copyright 2014 Panasonic Corporation
 * (c) Copyright 2016 Socionext Inc.
 * All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

/* WDT समयr setting रेजिस्टर */
#घोषणा WDTTIMSET			0x3004
#घोषणा   WDTTIMSET_PERIOD_MASK		(0xf << 0)
#घोषणा   WDTTIMSET_PERIOD_1_SEC	(0x3 << 0)

/* WDT reset selection रेजिस्टर */
#घोषणा WDTRSTSEL			0x3008
#घोषणा   WDTRSTSEL_RSTSEL_MASK		(0x3 << 0)
#घोषणा   WDTRSTSEL_RSTSEL_BOTH		(0x0 << 0)
#घोषणा   WDTRSTSEL_RSTSEL_IRQ_ONLY	(0x2 << 0)

/* WDT control रेजिस्टर */
#घोषणा WDTCTRL				0x300c
#घोषणा   WDTCTRL_STATUS		BIT(8)
#घोषणा   WDTCTRL_CLEAR			BIT(1)
#घोषणा   WDTCTRL_ENABLE		BIT(0)

#घोषणा SEC_TO_WDTTIMSET_PRD(sec) \
		(ilog2(sec) + WDTTIMSET_PERIOD_1_SEC)

#घोषणा WDTST_TIMEOUT			1000 /* usec */

#घोषणा WDT_DEFAULT_TIMEOUT		64   /* Default is 64 seconds */
#घोषणा WDT_PERIOD_MIN			1
#घोषणा WDT_PERIOD_MAX			128

अटल अचिन्हित पूर्णांक समयout = 0;
अटल bool nowayout = WATCHDOG_NOWAYOUT;

काष्ठा uniphier_wdt_dev अणु
	काष्ठा watchकरोg_device wdt_dev;
	काष्ठा regmap	*regmap;
पूर्ण;

/*
 * UniPhier Watchकरोg operations
 */
अटल पूर्णांक uniphier_watchकरोg_ping(काष्ठा watchकरोg_device *w)
अणु
	काष्ठा uniphier_wdt_dev *wdev = watchकरोg_get_drvdata(w);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Clear counter */
	ret = regmap_ग_लिखो_bits(wdev->regmap, WDTCTRL,
				WDTCTRL_CLEAR, WDTCTRL_CLEAR);
	अगर (!ret)
		/*
		 * As SoC specअगरication, after clear counter,
		 * it needs to रुको until counter status is 1.
		 */
		ret = regmap_पढ़ो_poll_समयout(wdev->regmap, WDTCTRL, val,
					       (val & WDTCTRL_STATUS),
					       0, WDTST_TIMEOUT);

	वापस ret;
पूर्ण

अटल पूर्णांक __uniphier_watchकरोg_start(काष्ठा regmap *regmap, अचिन्हित पूर्णांक sec)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(regmap, WDTCTRL, val,
				       !(val & WDTCTRL_STATUS),
				       0, WDTST_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* Setup period */
	ret = regmap_ग_लिखो(regmap, WDTTIMSET,
			   SEC_TO_WDTTIMSET_PRD(sec));
	अगर (ret)
		वापस ret;

	/* Enable and clear watchकरोg */
	ret = regmap_ग_लिखो(regmap, WDTCTRL, WDTCTRL_ENABLE | WDTCTRL_CLEAR);
	अगर (!ret)
		/*
		 * As SoC specअगरication, after clear counter,
		 * it needs to रुको until counter status is 1.
		 */
		ret = regmap_पढ़ो_poll_समयout(regmap, WDTCTRL, val,
					       (val & WDTCTRL_STATUS),
					       0, WDTST_TIMEOUT);

	वापस ret;
पूर्ण

अटल पूर्णांक __uniphier_watchकरोg_stop(काष्ठा regmap *regmap)
अणु
	/* Disable and stop watchकरोg */
	वापस regmap_ग_लिखो_bits(regmap, WDTCTRL, WDTCTRL_ENABLE, 0);
पूर्ण

अटल पूर्णांक __uniphier_watchकरोg_restart(काष्ठा regmap *regmap, अचिन्हित पूर्णांक sec)
अणु
	पूर्णांक ret;

	ret = __uniphier_watchकरोg_stop(regmap);
	अगर (ret)
		वापस ret;

	वापस __uniphier_watchकरोg_start(regmap, sec);
पूर्ण

अटल पूर्णांक uniphier_watchकरोg_start(काष्ठा watchकरोg_device *w)
अणु
	काष्ठा uniphier_wdt_dev *wdev = watchकरोg_get_drvdata(w);
	अचिन्हित पूर्णांक पंचांगp_समयout;

	पंचांगp_समयout = roundup_घात_of_two(w->समयout);

	वापस __uniphier_watchकरोg_start(wdev->regmap, पंचांगp_समयout);
पूर्ण

अटल पूर्णांक uniphier_watchकरोg_stop(काष्ठा watchकरोg_device *w)
अणु
	काष्ठा uniphier_wdt_dev *wdev = watchकरोg_get_drvdata(w);

	वापस __uniphier_watchकरोg_stop(wdev->regmap);
पूर्ण

अटल पूर्णांक uniphier_watchकरोg_set_समयout(काष्ठा watchकरोg_device *w,
					 अचिन्हित पूर्णांक t)
अणु
	काष्ठा uniphier_wdt_dev *wdev = watchकरोg_get_drvdata(w);
	अचिन्हित पूर्णांक पंचांगp_समयout;
	पूर्णांक ret;

	पंचांगp_समयout = roundup_घात_of_two(t);
	अगर (पंचांगp_समयout == w->समयout)
		वापस 0;

	अगर (watchकरोg_active(w)) अणु
		ret = __uniphier_watchकरोg_restart(wdev->regmap, पंचांगp_समयout);
		अगर (ret)
			वापस ret;
	पूर्ण

	w->समयout = पंचांगp_समयout;

	वापस 0;
पूर्ण

/*
 * Kernel Interfaces
 */
अटल स्थिर काष्ठा watchकरोg_info uniphier_wdt_info = अणु
	.identity	= "uniphier-wdt",
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE |
			  WDIOF_OVERHEAT,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops uniphier_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= uniphier_watchकरोg_start,
	.stop		= uniphier_watchकरोg_stop,
	.ping		= uniphier_watchकरोg_ping,
	.set_समयout	= uniphier_watchकरोg_set_समयout,
पूर्ण;

अटल पूर्णांक uniphier_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_wdt_dev *wdev;
	काष्ठा regmap *regmap;
	काष्ठा device_node *parent;
	पूर्णांक ret;

	wdev = devm_kzalloc(dev, माप(*wdev), GFP_KERNEL);
	अगर (!wdev)
		वापस -ENOMEM;

	parent = of_get_parent(dev->of_node); /* parent should be syscon node */
	regmap = syscon_node_to_regmap(parent);
	of_node_put(parent);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	wdev->regmap = regmap;
	wdev->wdt_dev.info = &uniphier_wdt_info;
	wdev->wdt_dev.ops = &uniphier_wdt_ops;
	wdev->wdt_dev.max_समयout = WDT_PERIOD_MAX;
	wdev->wdt_dev.min_समयout = WDT_PERIOD_MIN;
	wdev->wdt_dev.समयout = WDT_DEFAULT_TIMEOUT;
	wdev->wdt_dev.parent = dev;

	watchकरोg_init_समयout(&wdev->wdt_dev, समयout, dev);
	watchकरोg_set_nowayout(&wdev->wdt_dev, nowayout);
	watchकरोg_stop_on_reboot(&wdev->wdt_dev);

	watchकरोg_set_drvdata(&wdev->wdt_dev, wdev);

	uniphier_watchकरोg_stop(&wdev->wdt_dev);
	ret = regmap_ग_लिखो(wdev->regmap, WDTRSTSEL, WDTRSTSEL_RSTSEL_BOTH);
	अगर (ret)
		वापस ret;

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &wdev->wdt_dev);
	अगर (ret)
		वापस ret;

	dev_info(dev, "watchdog driver (timeout=%d sec, nowayout=%d)\n",
		 wdev->wdt_dev.समयout, nowayout);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_wdt_dt_ids[] = अणु
	अणु .compatible = "socionext,uniphier-wdt" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_wdt_dt_ids);

अटल काष्ठा platक्रमm_driver uniphier_wdt_driver = अणु
	.probe		= uniphier_wdt_probe,
	.driver		= अणु
		.name		= "uniphier-wdt",
		.of_match_table	= uniphier_wdt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(uniphier_wdt_driver);

module_param(समयout, uपूर्णांक, 0000);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout seconds in power of 2. (0 < timeout < 128, default="
				__MODULE_STRING(WDT_DEFAULT_TIMEOUT) ")");

module_param(nowayout, bool, 0000);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_AUTHOR("Keiji Hayashibara <hayashibara.keiji@socionext.com>");
MODULE_DESCRIPTION("UniPhier Watchdog Device Driver");
MODULE_LICENSE("GPL v2");
