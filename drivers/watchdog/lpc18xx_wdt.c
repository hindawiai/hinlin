<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NXP LPC18xx Watchकरोg Timer (WDT)
 *
 * Copyright (c) 2015 Ariel D'Alessandro <ariel@vanguardiasur.com>
 *
 * Notes
 * -----
 * The Watchकरोg consists of a fixed भागide-by-4 घड़ी pre-scaler and a 24-bit
 * counter which decrements on every घड़ी cycle.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

/* Registers */
#घोषणा LPC18XX_WDT_MOD			0x00
#घोषणा LPC18XX_WDT_MOD_WDEN		BIT(0)
#घोषणा LPC18XX_WDT_MOD_WDRESET		BIT(1)

#घोषणा LPC18XX_WDT_TC			0x04
#घोषणा LPC18XX_WDT_TC_MIN		0xff
#घोषणा LPC18XX_WDT_TC_MAX		0xffffff

#घोषणा LPC18XX_WDT_FEED		0x08
#घोषणा LPC18XX_WDT_FEED_MAGIC1		0xaa
#घोषणा LPC18XX_WDT_FEED_MAGIC2		0x55

#घोषणा LPC18XX_WDT_TV			0x0c

/* Clock pre-scaler */
#घोषणा LPC18XX_WDT_CLK_DIV		4

/* Timeout values in seconds */
#घोषणा LPC18XX_WDT_DEF_TIMEOUT		30U

अटल पूर्णांक heartbeat;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeats in seconds (default="
		 __MODULE_STRING(LPC18XX_WDT_DEF_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा lpc18xx_wdt_dev अणु
	काष्ठा watchकरोg_device	wdt_dev;
	काष्ठा clk		*reg_clk;
	काष्ठा clk		*wdt_clk;
	अचिन्हित दीर्घ		clk_rate;
	व्योम __iomem		*base;
	काष्ठा समयr_list	समयr;
	spinlock_t		lock;
पूर्ण;

अटल पूर्णांक lpc18xx_wdt_feed(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ flags;

	/*
	 * An पात condition will occur अगर an पूर्णांकerrupt happens during the feed
	 * sequence.
	 */
	spin_lock_irqsave(&lpc18xx_wdt->lock, flags);
	ग_लिखोl(LPC18XX_WDT_FEED_MAGIC1, lpc18xx_wdt->base + LPC18XX_WDT_FEED);
	ग_लिखोl(LPC18XX_WDT_FEED_MAGIC2, lpc18xx_wdt->base + LPC18XX_WDT_FEED);
	spin_unlock_irqrestore(&lpc18xx_wdt->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lpc18xx_wdt_समयr_feed(काष्ठा समयr_list *t)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = from_समयr(lpc18xx_wdt, t, समयr);
	काष्ठा watchकरोg_device *wdt_dev = &lpc18xx_wdt->wdt_dev;

	lpc18xx_wdt_feed(wdt_dev);

	/* Use safe value (1/2 of real समयout) */
	mod_समयr(&lpc18xx_wdt->समयr, jअगरfies +
		  msecs_to_jअगरfies((wdt_dev->समयout * MSEC_PER_SEC) / 2));
पूर्ण

/*
 * Since LPC18xx Watchकरोg cannot be disabled in hardware, we must keep feeding
 * it with a समयr until userspace watchकरोg software takes over.
 */
अटल पूर्णांक lpc18xx_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = watchकरोg_get_drvdata(wdt_dev);

	lpc18xx_wdt_समयr_feed(&lpc18xx_wdt->समयr);

	वापस 0;
पूर्ण

अटल व्योम __lpc18xx_wdt_set_समयout(काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt)
अणु
	अचिन्हित पूर्णांक val;

	val = DIV_ROUND_UP(lpc18xx_wdt->wdt_dev.समयout * lpc18xx_wdt->clk_rate,
			   LPC18XX_WDT_CLK_DIV);
	ग_लिखोl(val, lpc18xx_wdt->base + LPC18XX_WDT_TC);
पूर्ण

अटल पूर्णांक lpc18xx_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				   अचिन्हित पूर्णांक new_समयout)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = watchकरोg_get_drvdata(wdt_dev);

	lpc18xx_wdt->wdt_dev.समयout = new_समयout;
	__lpc18xx_wdt_set_समयout(lpc18xx_wdt);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक lpc18xx_wdt_get_समयleft(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(lpc18xx_wdt->base + LPC18XX_WDT_TV);
	वापस (val * LPC18XX_WDT_CLK_DIV) / lpc18xx_wdt->clk_rate;
पूर्ण

अटल पूर्णांक lpc18xx_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित पूर्णांक val;

	अगर (समयr_pending(&lpc18xx_wdt->समयr))
		del_समयr(&lpc18xx_wdt->समयr);

	val = पढ़ोl(lpc18xx_wdt->base + LPC18XX_WDT_MOD);
	val |= LPC18XX_WDT_MOD_WDEN;
	val |= LPC18XX_WDT_MOD_WDRESET;
	ग_लिखोl(val, lpc18xx_wdt->base + LPC18XX_WDT_MOD);

	/*
	 * Setting the WDEN bit in the WDMOD रेजिस्टर is not sufficient to
	 * enable the Watchकरोg. A valid feed sequence must be completed after
	 * setting WDEN beक्रमe the Watchकरोg is capable of generating a reset.
	 */
	lpc18xx_wdt_feed(wdt_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_wdt_restart(काष्ठा watchकरोg_device *wdt_dev,
			       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक val;

	/*
	 * Incorrect feed sequence causes immediate watchकरोg reset अगर enabled.
	 */
	spin_lock_irqsave(&lpc18xx_wdt->lock, flags);

	val = पढ़ोl(lpc18xx_wdt->base + LPC18XX_WDT_MOD);
	val |= LPC18XX_WDT_MOD_WDEN;
	val |= LPC18XX_WDT_MOD_WDRESET;
	ग_लिखोl(val, lpc18xx_wdt->base + LPC18XX_WDT_MOD);

	ग_लिखोl(LPC18XX_WDT_FEED_MAGIC1, lpc18xx_wdt->base + LPC18XX_WDT_FEED);
	ग_लिखोl(LPC18XX_WDT_FEED_MAGIC2, lpc18xx_wdt->base + LPC18XX_WDT_FEED);

	ग_लिखोl(LPC18XX_WDT_FEED_MAGIC1, lpc18xx_wdt->base + LPC18XX_WDT_FEED);
	ग_लिखोl(LPC18XX_WDT_FEED_MAGIC1, lpc18xx_wdt->base + LPC18XX_WDT_FEED);

	spin_unlock_irqrestore(&lpc18xx_wdt->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info lpc18xx_wdt_info = अणु
	.identity	= "NXP LPC18xx Watchdog",
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops lpc18xx_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= lpc18xx_wdt_start,
	.stop		= lpc18xx_wdt_stop,
	.ping		= lpc18xx_wdt_feed,
	.set_समयout	= lpc18xx_wdt_set_समयout,
	.get_समयleft	= lpc18xx_wdt_get_समयleft,
	.restart        = lpc18xx_wdt_restart,
पूर्ण;

अटल व्योम lpc18xx_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक lpc18xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	lpc18xx_wdt = devm_kzalloc(dev, माप(*lpc18xx_wdt), GFP_KERNEL);
	अगर (!lpc18xx_wdt)
		वापस -ENOMEM;

	lpc18xx_wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(lpc18xx_wdt->base))
		वापस PTR_ERR(lpc18xx_wdt->base);

	lpc18xx_wdt->reg_clk = devm_clk_get(dev, "reg");
	अगर (IS_ERR(lpc18xx_wdt->reg_clk)) अणु
		dev_err(dev, "failed to get the reg clock\n");
		वापस PTR_ERR(lpc18xx_wdt->reg_clk);
	पूर्ण

	lpc18xx_wdt->wdt_clk = devm_clk_get(dev, "wdtclk");
	अगर (IS_ERR(lpc18xx_wdt->wdt_clk)) अणु
		dev_err(dev, "failed to get the wdt clock\n");
		वापस PTR_ERR(lpc18xx_wdt->wdt_clk);
	पूर्ण

	ret = clk_prepare_enable(lpc18xx_wdt->reg_clk);
	अगर (ret) अणु
		dev_err(dev, "could not prepare or enable sys clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, lpc18xx_clk_disable_unprepare,
				       lpc18xx_wdt->reg_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(lpc18xx_wdt->wdt_clk);
	अगर (ret) अणु
		dev_err(dev, "could not prepare or enable wdt clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, lpc18xx_clk_disable_unprepare,
				       lpc18xx_wdt->wdt_clk);
	अगर (ret)
		वापस ret;

	/* We use the घड़ी rate to calculate समयouts */
	lpc18xx_wdt->clk_rate = clk_get_rate(lpc18xx_wdt->wdt_clk);
	अगर (lpc18xx_wdt->clk_rate == 0) अणु
		dev_err(dev, "failed to get clock rate\n");
		वापस -EINVAL;
	पूर्ण

	lpc18xx_wdt->wdt_dev.info = &lpc18xx_wdt_info;
	lpc18xx_wdt->wdt_dev.ops = &lpc18xx_wdt_ops;

	lpc18xx_wdt->wdt_dev.min_समयout = DIV_ROUND_UP(LPC18XX_WDT_TC_MIN *
				LPC18XX_WDT_CLK_DIV, lpc18xx_wdt->clk_rate);

	lpc18xx_wdt->wdt_dev.max_समयout = (LPC18XX_WDT_TC_MAX *
				LPC18XX_WDT_CLK_DIV) / lpc18xx_wdt->clk_rate;

	lpc18xx_wdt->wdt_dev.समयout = min(lpc18xx_wdt->wdt_dev.max_समयout,
					   LPC18XX_WDT_DEF_TIMEOUT);

	spin_lock_init(&lpc18xx_wdt->lock);

	lpc18xx_wdt->wdt_dev.parent = dev;
	watchकरोg_set_drvdata(&lpc18xx_wdt->wdt_dev, lpc18xx_wdt);

	watchकरोg_init_समयout(&lpc18xx_wdt->wdt_dev, heartbeat, dev);

	__lpc18xx_wdt_set_समयout(lpc18xx_wdt);

	समयr_setup(&lpc18xx_wdt->समयr, lpc18xx_wdt_समयr_feed, 0);

	watchकरोg_set_nowayout(&lpc18xx_wdt->wdt_dev, nowayout);
	watchकरोg_set_restart_priority(&lpc18xx_wdt->wdt_dev, 128);

	platक्रमm_set_drvdata(pdev, lpc18xx_wdt);

	watchकरोg_stop_on_reboot(&lpc18xx_wdt->wdt_dev);
	वापस devm_watchकरोg_रेजिस्टर_device(dev, &lpc18xx_wdt->wdt_dev);
पूर्ण

अटल पूर्णांक lpc18xx_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_wdt_dev *lpc18xx_wdt = platक्रमm_get_drvdata(pdev);

	dev_warn(&pdev->dev, "I quit now, hardware will probably reboot!\n");
	del_समयr(&lpc18xx_wdt->समयr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_wdt_match[] = अणु
	अणु .compatible = "nxp,lpc1850-wwdt" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_wdt_match);

अटल काष्ठा platक्रमm_driver lpc18xx_wdt_driver = अणु
	.driver = अणु
		.name = "lpc18xx-wdt",
		.of_match_table	= lpc18xx_wdt_match,
	पूर्ण,
	.probe = lpc18xx_wdt_probe,
	.हटाओ = lpc18xx_wdt_हटाओ,
पूर्ण;
module_platक्रमm_driver(lpc18xx_wdt_driver);

MODULE_AUTHOR("Ariel D'Alessandro <ariel@vanguardiasur.com.ar>");
MODULE_DESCRIPTION("NXP LPC18xx Watchdog Timer Driver");
MODULE_LICENSE("GPL v2");
