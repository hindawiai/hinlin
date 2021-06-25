<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016 Yang Ling <gnaygnil@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <loongson1.h>

#घोषणा DEFAULT_HEARTBEAT	30

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0444);

अटल अचिन्हित पूर्णांक heartbeat;
module_param(heartbeat, uपूर्णांक, 0444);

काष्ठा ls1x_wdt_drvdata अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा watchकरोg_device wdt;
पूर्ण;

अटल पूर्णांक ls1x_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा ls1x_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(0x1, drvdata->base + WDT_SET);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा ls1x_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित पूर्णांक max_hw_heartbeat = wdt_dev->max_hw_heartbeat_ms / 1000;
	अचिन्हित पूर्णांक counts;

	wdt_dev->समयout = समयout;

	counts = drvdata->clk_rate * min(समयout, max_hw_heartbeat);
	ग_लिखोl(counts, drvdata->base + WDT_TIMER);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा ls1x_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(0x1, drvdata->base + WDT_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1x_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा ls1x_wdt_drvdata *drvdata = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(0x0, drvdata->base + WDT_EN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ls1x_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "Loongson1 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ls1x_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = ls1x_wdt_start,
	.stop = ls1x_wdt_stop,
	.ping = ls1x_wdt_ping,
	.set_समयout = ls1x_wdt_set_समयout,
पूर्ण;

अटल व्योम ls1x_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक ls1x_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ls1x_wdt_drvdata *drvdata;
	काष्ठा watchकरोg_device *ls1x_wdt;
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक err;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(drvdata->base))
		वापस PTR_ERR(drvdata->base);

	drvdata->clk = devm_clk_get(dev, pdev->name);
	अगर (IS_ERR(drvdata->clk))
		वापस PTR_ERR(drvdata->clk);

	err = clk_prepare_enable(drvdata->clk);
	अगर (err) अणु
		dev_err(dev, "clk enable failed\n");
		वापस err;
	पूर्ण
	err = devm_add_action_or_reset(dev, ls1x_clk_disable_unprepare,
				       drvdata->clk);
	अगर (err)
		वापस err;

	clk_rate = clk_get_rate(drvdata->clk);
	अगर (!clk_rate)
		वापस -EINVAL;
	drvdata->clk_rate = clk_rate;

	ls1x_wdt = &drvdata->wdt;
	ls1x_wdt->info = &ls1x_wdt_info;
	ls1x_wdt->ops = &ls1x_wdt_ops;
	ls1x_wdt->समयout = DEFAULT_HEARTBEAT;
	ls1x_wdt->min_समयout = 1;
	ls1x_wdt->max_hw_heartbeat_ms = U32_MAX / clk_rate * 1000;
	ls1x_wdt->parent = dev;

	watchकरोg_init_समयout(ls1x_wdt, heartbeat, dev);
	watchकरोg_set_nowayout(ls1x_wdt, nowayout);
	watchकरोg_set_drvdata(ls1x_wdt, drvdata);

	err = devm_watchकरोg_रेजिस्टर_device(dev, &drvdata->wdt);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, drvdata);

	dev_info(dev, "Loongson1 Watchdog driver registered\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ls1x_wdt_driver = अणु
	.probe = ls1x_wdt_probe,
	.driver = अणु
		.name = "ls1x-wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ls1x_wdt_driver);

MODULE_AUTHOR("Yang Ling <gnaygnil@gmail.com>");
MODULE_DESCRIPTION("Loongson1 Watchdog Driver");
MODULE_LICENSE("GPL");
