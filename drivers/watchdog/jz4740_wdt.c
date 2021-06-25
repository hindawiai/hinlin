<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2010, Paul Cercueil <paul@crapouillou.net>
 *  JZ4740 Watchकरोg driver
 */

#समावेश <linux/mfd/ingenic-tcu.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#घोषणा DEFAULT_HEARTBEAT 5
#घोषणा MAX_HEARTBEAT     2048

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अचिन्हित पूर्णांक heartbeat = DEFAULT_HEARTBEAT;
module_param(heartbeat, uपूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
		"Watchdog heartbeat period in seconds from 1 to "
		__MODULE_STRING(MAX_HEARTBEAT) ", default "
		__MODULE_STRING(DEFAULT_HEARTBEAT));

काष्ठा jz4740_wdt_drvdata अणु
	काष्ठा watchकरोg_device wdt;
	काष्ठा regmap *map;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clk_rate;
पूर्ण;

अटल पूर्णांक jz4740_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा jz4740_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);

	regmap_ग_लिखो(drvdata->map, TCU_REG_WDT_TCNT, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				    अचिन्हित पूर्णांक new_समयout)
अणु
	काष्ठा jz4740_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);
	u16 समयout_value = (u16)(drvdata->clk_rate * new_समयout);
	अचिन्हित पूर्णांक tcer;

	regmap_पढ़ो(drvdata->map, TCU_REG_WDT_TCER, &tcer);
	regmap_ग_लिखो(drvdata->map, TCU_REG_WDT_TCER, 0);

	regmap_ग_लिखो(drvdata->map, TCU_REG_WDT_TDR, समयout_value);
	regmap_ग_लिखो(drvdata->map, TCU_REG_WDT_TCNT, 0);

	अगर (tcer & TCU_WDT_TCER_TCEN)
		regmap_ग_लिखो(drvdata->map, TCU_REG_WDT_TCER, TCU_WDT_TCER_TCEN);

	wdt_dev->समयout = new_समयout;
	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा jz4740_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित पूर्णांक tcer;
	पूर्णांक ret;

	ret = clk_prepare_enable(drvdata->clk);
	अगर (ret)
		वापस ret;

	regmap_पढ़ो(drvdata->map, TCU_REG_WDT_TCER, &tcer);

	jz4740_wdt_set_समयout(wdt_dev, wdt_dev->समयout);

	/* Start watchकरोg अगर it wasn't started alपढ़ोy */
	अगर (!(tcer & TCU_WDT_TCER_TCEN))
		regmap_ग_लिखो(drvdata->map, TCU_REG_WDT_TCER, TCU_WDT_TCER_TCEN);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा jz4740_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);

	regmap_ग_लिखो(drvdata->map, TCU_REG_WDT_TCER, 0);
	clk_disable_unprepare(drvdata->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_wdt_restart(काष्ठा watchकरोg_device *wdt_dev,
			      अचिन्हित दीर्घ action, व्योम *data)
अणु
	wdt_dev->समयout = 0;
	jz4740_wdt_start(wdt_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info jz4740_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "jz4740 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops jz4740_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = jz4740_wdt_start,
	.stop = jz4740_wdt_stop,
	.ping = jz4740_wdt_ping,
	.set_समयout = jz4740_wdt_set_समयout,
	.restart = jz4740_wdt_restart,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id jz4740_wdt_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4740-watchdog", पूर्ण,
	अणु .compatible = "ingenic,jz4780-watchdog", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_wdt_of_matches);
#पूर्ण_अगर

अटल पूर्णांक jz4740_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा jz4740_wdt_drvdata *drvdata;
	काष्ठा watchकरोg_device *jz4740_wdt;
	दीर्घ rate;
	पूर्णांक ret;

	drvdata = devm_kzalloc(dev, माप(काष्ठा jz4740_wdt_drvdata),
			       GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->clk = devm_clk_get(&pdev->dev, "wdt");
	अगर (IS_ERR(drvdata->clk)) अणु
		dev_err(&pdev->dev, "cannot find WDT clock\n");
		वापस PTR_ERR(drvdata->clk);
	पूर्ण

	/* Set smallest घड़ी possible */
	rate = clk_round_rate(drvdata->clk, 1);
	अगर (rate < 0)
		वापस rate;

	ret = clk_set_rate(drvdata->clk, rate);
	अगर (ret)
		वापस ret;

	drvdata->clk_rate = rate;
	jz4740_wdt = &drvdata->wdt;
	jz4740_wdt->info = &jz4740_wdt_info;
	jz4740_wdt->ops = &jz4740_wdt_ops;
	jz4740_wdt->min_समयout = 1;
	jz4740_wdt->max_समयout = 0xffff / rate;
	jz4740_wdt->समयout = clamp(heartbeat,
				    jz4740_wdt->min_समयout,
				    jz4740_wdt->max_समयout);
	jz4740_wdt->parent = dev;
	watchकरोg_set_nowayout(jz4740_wdt, nowayout);
	watchकरोg_set_drvdata(jz4740_wdt, drvdata);

	drvdata->map = device_node_to_regmap(dev->parent->of_node);
	अगर (!drvdata->map) अणु
		dev_err(dev, "regmap not found\n");
		वापस -EINVAL;
	पूर्ण

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &drvdata->wdt);
पूर्ण

अटल काष्ठा platक्रमm_driver jz4740_wdt_driver = अणु
	.probe = jz4740_wdt_probe,
	.driver = अणु
		.name = "jz4740-wdt",
		.of_match_table = of_match_ptr(jz4740_wdt_of_matches),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jz4740_wdt_driver);

MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("jz4740 Watchdog Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:jz4740-wdt");
