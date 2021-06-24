<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम Conexant Digicolor
 *
 * Copyright (C) 2015 Paraकरोx Innovation Ltd.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>

#घोषणा TIMER_A_CONTROL		0
#घोषणा TIMER_A_COUNT		4

#घोषणा TIMER_A_ENABLE_COUNT	BIT(0)
#घोषणा TIMER_A_ENABLE_WATCHDOG	BIT(1)

काष्ठा dc_wdt अणु
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	spinlock_t		lock;
पूर्ण;

अटल अचिन्हित समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds");

अटल व्योम dc_wdt_set(काष्ठा dc_wdt *wdt, u32 ticks)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdt->lock, flags);

	ग_लिखोl_relaxed(0, wdt->base + TIMER_A_CONTROL);
	ग_लिखोl_relaxed(ticks, wdt->base + TIMER_A_COUNT);
	ग_लिखोl_relaxed(TIMER_A_ENABLE_COUNT | TIMER_A_ENABLE_WATCHDOG,
		       wdt->base + TIMER_A_CONTROL);

	spin_unlock_irqrestore(&wdt->lock, flags);
पूर्ण

अटल पूर्णांक dc_wdt_restart(काष्ठा watchकरोg_device *wकरोg, अचिन्हित दीर्घ action,
			  व्योम *data)
अणु
	काष्ठा dc_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	dc_wdt_set(wdt, 1);
	/* रुको क्रम reset to निश्चित... */
	mdelay(500);

	वापस 0;
पूर्ण

अटल पूर्णांक dc_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा dc_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	dc_wdt_set(wdt, wकरोg->समयout * clk_get_rate(wdt->clk));

	वापस 0;
पूर्ण

अटल पूर्णांक dc_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा dc_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	ग_लिखोl_relaxed(0, wdt->base + TIMER_A_CONTROL);

	वापस 0;
पूर्ण

अटल पूर्णांक dc_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg, अचिन्हित पूर्णांक t)
अणु
	काष्ठा dc_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	dc_wdt_set(wdt, t * clk_get_rate(wdt->clk));
	wकरोg->समयout = t;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dc_wdt_get_समयleft(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा dc_wdt *wdt = watchकरोg_get_drvdata(wकरोg);
	uपूर्णांक32_t count = पढ़ोl_relaxed(wdt->base + TIMER_A_COUNT);

	वापस count / clk_get_rate(wdt->clk);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops dc_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= dc_wdt_start,
	.stop		= dc_wdt_stop,
	.set_समयout	= dc_wdt_set_समयout,
	.get_समयleft	= dc_wdt_get_समयleft,
	.restart        = dc_wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info dc_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE
			| WDIOF_KEEPALIVEPING,
	.identity	= "Conexant Digicolor Watchdog",
पूर्ण;

अटल काष्ठा watchकरोg_device dc_wdt_wdd = अणु
	.info		= &dc_wdt_info,
	.ops		= &dc_wdt_ops,
	.min_समयout	= 1,
पूर्ण;

अटल पूर्णांक dc_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dc_wdt *wdt;

	wdt = devm_kzalloc(dev, माप(काष्ठा dc_wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	wdt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(wdt->clk))
		वापस PTR_ERR(wdt->clk);
	dc_wdt_wdd.max_समयout = U32_MAX / clk_get_rate(wdt->clk);
	dc_wdt_wdd.समयout = dc_wdt_wdd.max_समयout;
	dc_wdt_wdd.parent = dev;

	spin_lock_init(&wdt->lock);

	watchकरोg_set_drvdata(&dc_wdt_wdd, wdt);
	watchकरोg_set_restart_priority(&dc_wdt_wdd, 128);
	watchकरोg_init_समयout(&dc_wdt_wdd, समयout, dev);
	watchकरोg_stop_on_reboot(&dc_wdt_wdd);
	वापस devm_watchकरोg_रेजिस्टर_device(dev, &dc_wdt_wdd);
पूर्ण

अटल स्थिर काष्ठा of_device_id dc_wdt_of_match[] = अणु
	अणु .compatible = "cnxt,cx92755-wdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dc_wdt_of_match);

अटल काष्ठा platक्रमm_driver dc_wdt_driver = अणु
	.probe		= dc_wdt_probe,
	.driver = अणु
		.name =		"digicolor-wdt",
		.of_match_table = dc_wdt_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dc_wdt_driver);

MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("Driver for Conexant Digicolor watchdog timer");
MODULE_LICENSE("GPL");
