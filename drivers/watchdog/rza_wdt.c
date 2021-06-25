<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas RZ/A Series WDT Driver
 *
 * Copyright (C) 2017 Renesas Electronics America, Inc.
 * Copyright (C) 2017 Chris Bअक्रमt
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DEFAULT_TIMEOUT		30

/* Watchकरोg Timer Registers */
#घोषणा WTCSR			0
#घोषणा WTCSR_MAGIC		0xA500
#घोषणा WTSCR_WT		BIT(6)
#घोषणा WTSCR_TME		BIT(5)
#घोषणा WTSCR_CKS(i)		(i)

#घोषणा WTCNT			2
#घोषणा WTCNT_MAGIC		0x5A00

#घोषणा WRCSR			4
#घोषणा WRCSR_MAGIC		0x5A00
#घोषणा WRCSR_RSTE		BIT(6)
#घोषणा WRCSR_CLEAR_WOVF	0xA500	/* special value */

/* The maximum CKS रेजिस्टर setting value to get the दीर्घest समयout */
#घोषणा CKS_3BIT		0x7
#घोषणा CKS_4BIT		0xF

#घोषणा DIVIDER_3BIT		16384	/* Clock भागider when CKS = 0x7 */
#घोषणा DIVIDER_4BIT		4194304	/* Clock भागider when CKS = 0xF */

काष्ठा rza_wdt अणु
	काष्ठा watchकरोg_device wdev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	u8 count;
	u8 cks;
पूर्ण;

अटल व्योम rza_wdt_calc_समयout(काष्ठा rza_wdt *priv, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ rate = clk_get_rate(priv->clk);
	अचिन्हित पूर्णांक ticks;

	अगर (priv->cks == CKS_4BIT) अणु
		ticks = DIV_ROUND_UP(समयout * rate, DIVIDER_4BIT);

		/*
		 * Since max_समयout was set in probe, we know that the समयout
		 * value passed will never calculate to a tick value greater
		 * than 256.
		 */
		priv->count = 256 - ticks;

	पूर्ण अन्यथा अणु
		/* Start समयr with दीर्घest समयout */
		priv->count = 0;
	पूर्ण

	pr_debug("%s: timeout set to %u (WTCNT=%d)\n", __func__,
		 समयout, priv->count);
पूर्ण

अटल पूर्णांक rza_wdt_start(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rza_wdt *priv = watchकरोg_get_drvdata(wdev);

	/* Stop समयr */
	ग_लिखोw(WTCSR_MAGIC | 0, priv->base + WTCSR);

	/* Must dummy पढ़ो WRCSR:WOVF at least once beक्रमe clearing */
	पढ़ोb(priv->base + WRCSR);
	ग_लिखोw(WRCSR_CLEAR_WOVF, priv->base + WRCSR);

	rza_wdt_calc_समयout(priv, wdev->समयout);

	ग_लिखोw(WRCSR_MAGIC | WRCSR_RSTE, priv->base + WRCSR);
	ग_लिखोw(WTCNT_MAGIC | priv->count, priv->base + WTCNT);
	ग_लिखोw(WTCSR_MAGIC | WTSCR_WT | WTSCR_TME |
	       WTSCR_CKS(priv->cks), priv->base + WTCSR);

	वापस 0;
पूर्ण

अटल पूर्णांक rza_wdt_stop(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rza_wdt *priv = watchकरोg_get_drvdata(wdev);

	ग_लिखोw(WTCSR_MAGIC | 0, priv->base + WTCSR);

	वापस 0;
पूर्ण

अटल पूर्णांक rza_wdt_ping(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा rza_wdt *priv = watchकरोg_get_drvdata(wdev);

	ग_लिखोw(WTCNT_MAGIC | priv->count, priv->base + WTCNT);

	pr_debug("%s: timeout = %u\n", __func__, wdev->समयout);

	वापस 0;
पूर्ण

अटल पूर्णांक rza_set_समयout(काष्ठा watchकरोg_device *wdev, अचिन्हित पूर्णांक समयout)
अणु
	wdev->समयout = समयout;
	rza_wdt_start(wdev);
	वापस 0;
पूर्ण

अटल पूर्णांक rza_wdt_restart(काष्ठा watchकरोg_device *wdev, अचिन्हित दीर्घ action,
			    व्योम *data)
अणु
	काष्ठा rza_wdt *priv = watchकरोg_get_drvdata(wdev);

	/* Stop समयr */
	ग_लिखोw(WTCSR_MAGIC | 0, priv->base + WTCSR);

	/* Must dummy पढ़ो WRCSR:WOVF at least once beक्रमe clearing */
	पढ़ोb(priv->base + WRCSR);
	ग_लिखोw(WRCSR_CLEAR_WOVF, priv->base + WRCSR);

	/*
	 * Start समयr with fastest घड़ी source and only 1 घड़ी left beक्रमe
	 * overflow with reset option enabled.
	 */
	ग_लिखोw(WRCSR_MAGIC | WRCSR_RSTE, priv->base + WRCSR);
	ग_लिखोw(WTCNT_MAGIC | 255, priv->base + WTCNT);
	ग_लिखोw(WTCSR_MAGIC | WTSCR_WT | WTSCR_TME, priv->base + WTCSR);

	/*
	 * Actually make sure the above sequence hits hardware beक्रमe sleeping.
	 */
	wmb();

	/* Wait क्रम WDT overflow (reset) */
	udelay(20);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info rza_wdt_ident = अणु
	.options = WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT,
	.identity = "Renesas RZ/A WDT Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops rza_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = rza_wdt_start,
	.stop = rza_wdt_stop,
	.ping = rza_wdt_ping,
	.set_समयout = rza_set_समयout,
	.restart = rza_wdt_restart,
पूर्ण;

अटल पूर्णांक rza_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rza_wdt *priv;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	rate = clk_get_rate(priv->clk);
	अगर (rate < 16384) अणु
		dev_err(dev, "invalid clock rate (%ld)\n", rate);
		वापस -ENOENT;
	पूर्ण

	priv->wdev.info = &rza_wdt_ident,
	priv->wdev.ops = &rza_wdt_ops,
	priv->wdev.parent = dev;

	priv->cks = (u8)(uपूर्णांकptr_t) of_device_get_match_data(dev);
	अगर (priv->cks == CKS_4BIT) अणु
		/* Assume slowest घड़ी rate possible (CKS=0xF) */
		priv->wdev.max_समयout = (DIVIDER_4BIT * U8_MAX) / rate;

	पूर्ण अन्यथा अगर (priv->cks == CKS_3BIT) अणु
		/* Assume slowest घड़ी rate possible (CKS=7) */
		rate /= DIVIDER_3BIT;

		/*
		 * Since the max possible समयout of our 8-bit count
		 * रेजिस्टर is less than a second, we must use
		 * max_hw_heartbeat_ms.
		 */
		priv->wdev.max_hw_heartbeat_ms = (1000 * U8_MAX) / rate;
		dev_dbg(dev, "max hw timeout of %dms\n",
			priv->wdev.max_hw_heartbeat_ms);
	पूर्ण

	priv->wdev.min_समयout = 1;
	priv->wdev.समयout = DEFAULT_TIMEOUT;

	watchकरोg_init_समयout(&priv->wdev, 0, dev);
	watchकरोg_set_drvdata(&priv->wdev, priv);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &priv->wdev);
	अगर (ret)
		dev_err(dev, "Cannot register watchdog device\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id rza_wdt_of_match[] = अणु
	अणु .compatible = "renesas,r7s9210-wdt",	.data = (व्योम *)CKS_4BIT, पूर्ण,
	अणु .compatible = "renesas,rza-wdt",	.data = (व्योम *)CKS_3BIT, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rza_wdt_of_match);

अटल काष्ठा platक्रमm_driver rza_wdt_driver = अणु
	.probe = rza_wdt_probe,
	.driver = अणु
		.name = "rza_wdt",
		.of_match_table = rza_wdt_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rza_wdt_driver);

MODULE_DESCRIPTION("Renesas RZ/A WDT Driver");
MODULE_AUTHOR("Chris Brandt <chris.brandt@renesas.com>");
MODULE_LICENSE("GPL v2");
