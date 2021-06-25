<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Watchकरोg driver क्रम Alphascale ASM9260.
 *
 * Copyright (c) 2014 Oleksij Rempel <linux@rempel-privat.de>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/watchकरोg.h>

#घोषणा CLOCK_FREQ	1000000

/* Watchकरोg Mode रेजिस्टर */
#घोषणा HW_WDMOD			0x00
/* Wake पूर्णांकerrupt. Set by HW, can't be cleared. */
#घोषणा BM_MOD_WDINT			BIT(3)
/* This bit set अगर समयout reached. Cleared by SW. */
#घोषणा BM_MOD_WDTOF			BIT(2)
/* HW Reset on समयout */
#घोषणा BM_MOD_WDRESET			BIT(1)
/* WD enable */
#घोषणा BM_MOD_WDEN			BIT(0)

/*
 * Watchकरोg Timer Constant रेजिस्टर
 * Minimal value is 0xff, the meaning of this value
 * depends on used घड़ी: T = WDCLK * (0xff + 1) * 4
 */
#घोषणा HW_WDTC				0x04
#घोषणा BM_WDTC_MAX(freq)		(0x7fffffff / (freq))

/* Watchकरोg Feed रेजिस्टर */
#घोषणा HW_WDFEED			0x08

/* Watchकरोg Timer Value रेजिस्टर */
#घोषणा HW_WDTV				0x0c

#घोषणा ASM9260_WDT_DEFAULT_TIMEOUT	30

क्रमागत यंत्र9260_wdt_mode अणु
	HW_RESET,
	SW_RESET,
	DEBUG,
पूर्ण;

काष्ठा यंत्र9260_wdt_priv अणु
	काष्ठा device		*dev;
	काष्ठा watchकरोg_device	wdd;
	काष्ठा clk		*clk;
	काष्ठा clk		*clk_ahb;
	काष्ठा reset_control	*rst;

	व्योम __iomem		*iobase;
	पूर्णांक			irq;
	अचिन्हित दीर्घ		wdt_freq;
	क्रमागत यंत्र9260_wdt_mode	mode;
पूर्ण;

अटल पूर्णांक यंत्र9260_wdt_feed(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा यंत्र9260_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ioग_लिखो32(0xaa, priv->iobase + HW_WDFEED);
	ioग_लिखो32(0x55, priv->iobase + HW_WDFEED);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक यंत्र9260_wdt_समय_लोleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा यंत्र9260_wdt_priv *priv = watchकरोg_get_drvdata(wdd);
	u32 counter;

	counter = ioपढ़ो32(priv->iobase + HW_WDTV);

	वापस counter / priv->wdt_freq;
पूर्ण

अटल पूर्णांक यंत्र9260_wdt_updateसमयout(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा यंत्र9260_wdt_priv *priv = watchकरोg_get_drvdata(wdd);
	u32 counter;

	counter = wdd->समयout * priv->wdt_freq;

	ioग_लिखो32(counter, priv->iobase + HW_WDTC);

	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_wdt_enable(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा यंत्र9260_wdt_priv *priv = watchकरोg_get_drvdata(wdd);
	u32 mode = 0;

	अगर (priv->mode == HW_RESET)
		mode = BM_MOD_WDRESET;

	ioग_लिखो32(BM_MOD_WDEN | mode, priv->iobase + HW_WDMOD);

	यंत्र9260_wdt_updateसमयout(wdd);

	यंत्र9260_wdt_feed(wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_wdt_disable(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा यंत्र9260_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	/* The only way to disable WD is to reset it. */
	reset_control_निश्चित(priv->rst);
	reset_control_deनिश्चित(priv->rst);

	वापस 0;
पूर्ण

अटल पूर्णांक यंत्र9260_wdt_समय_रखोout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक to)
अणु
	wdd->समयout = to;
	यंत्र9260_wdt_updateसमयout(wdd);

	वापस 0;
पूर्ण

अटल व्योम यंत्र9260_wdt_sys_reset(काष्ठा यंत्र9260_wdt_priv *priv)
अणु
	/* init WD अगर it was not started */

	ioग_लिखो32(BM_MOD_WDEN | BM_MOD_WDRESET, priv->iobase + HW_WDMOD);

	ioग_लिखो32(0xff, priv->iobase + HW_WDTC);
	/* first pass correct sequence */
	यंत्र9260_wdt_feed(&priv->wdd);
	/*
	 * Then ग_लिखो wrong pattern to the feed to trigger reset
	 * ASAP.
	 */
	ioग_लिखो32(0xff, priv->iobase + HW_WDFEED);

	mdelay(1000);
पूर्ण

अटल irqवापस_t यंत्र9260_wdt_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा यंत्र9260_wdt_priv *priv = devid;
	u32 stat;

	stat = ioपढ़ो32(priv->iobase + HW_WDMOD);
	अगर (!(stat & BM_MOD_WDINT))
		वापस IRQ_NONE;

	अगर (priv->mode == DEBUG) अणु
		dev_info(priv->dev, "Watchdog Timeout. Do nothing.\n");
	पूर्ण अन्यथा अणु
		dev_info(priv->dev, "Watchdog Timeout. Doing SW Reset.\n");
		यंत्र9260_wdt_sys_reset(priv);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक यंत्र9260_restart(काष्ठा watchकरोg_device *wdd, अचिन्हित दीर्घ action,
			   व्योम *data)
अणु
	काष्ठा यंत्र9260_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	यंत्र9260_wdt_sys_reset(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info यंत्र9260_wdt_ident = अणु
	.options          =     WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING
				| WDIOF_MAGICCLOSE,
	.identity         =	"Alphascale asm9260 Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops यंत्र9260_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= यंत्र9260_wdt_enable,
	.stop		= यंत्र9260_wdt_disable,
	.get_समयleft	= यंत्र9260_wdt_समय_लोleft,
	.ping		= यंत्र9260_wdt_feed,
	.set_समयout	= यंत्र9260_wdt_समय_रखोout,
	.restart	= यंत्र9260_restart,
पूर्ण;

अटल व्योम यंत्र9260_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक यंत्र9260_wdt_get_dt_clks(काष्ठा यंत्र9260_wdt_priv *priv)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ clk;

	priv->clk = devm_clk_get(priv->dev, "mod");
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(priv->dev, "Failed to get \"mod\" clk\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	/* configure AHB घड़ी */
	priv->clk_ahb = devm_clk_get(priv->dev, "ahb");
	अगर (IS_ERR(priv->clk_ahb)) अणु
		dev_err(priv->dev, "Failed to get \"ahb\" clk\n");
		वापस PTR_ERR(priv->clk_ahb);
	पूर्ण

	err = clk_prepare_enable(priv->clk_ahb);
	अगर (err) अणु
		dev_err(priv->dev, "Failed to enable ahb_clk!\n");
		वापस err;
	पूर्ण
	err = devm_add_action_or_reset(priv->dev,
				       यंत्र9260_clk_disable_unprepare,
				       priv->clk_ahb);
	अगर (err)
		वापस err;

	err = clk_set_rate(priv->clk, CLOCK_FREQ);
	अगर (err) अणु
		dev_err(priv->dev, "Failed to set rate!\n");
		वापस err;
	पूर्ण

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		dev_err(priv->dev, "Failed to enable clk!\n");
		वापस err;
	पूर्ण
	err = devm_add_action_or_reset(priv->dev,
				       यंत्र9260_clk_disable_unprepare,
				       priv->clk);
	अगर (err)
		वापस err;

	/* wdt has पूर्णांकernal भागider */
	clk = clk_get_rate(priv->clk);
	अगर (!clk) अणु
		dev_err(priv->dev, "Failed, clk is 0!\n");
		वापस -EINVAL;
	पूर्ण

	priv->wdt_freq = clk / 2;

	वापस 0;
पूर्ण

अटल व्योम यंत्र9260_wdt_get_dt_mode(काष्ठा यंत्र9260_wdt_priv *priv)
अणु
	स्थिर अक्षर *पंचांगp;
	पूर्णांक ret;

	/* शेष mode */
	priv->mode = HW_RESET;

	ret = of_property_पढ़ो_string(priv->dev->of_node,
				      "alphascale,mode", &पंचांगp);
	अगर (ret < 0)
		वापस;

	अगर (!म_भेद(पंचांगp, "hw"))
		priv->mode = HW_RESET;
	अन्यथा अगर (!म_भेद(पंचांगp, "sw"))
		priv->mode = SW_RESET;
	अन्यथा अगर (!म_भेद(पंचांगp, "debug"))
		priv->mode = DEBUG;
	अन्यथा
		dev_warn(priv->dev, "unknown reset-type: %s. Using default \"hw\" mode.",
			 पंचांगp);
पूर्ण

अटल पूर्णांक यंत्र9260_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा यंत्र9260_wdt_priv *priv;
	काष्ठा watchकरोg_device *wdd;
	पूर्णांक ret;
	अटल स्थिर अक्षर * स्थिर mode_name[] = अणु "hw", "sw", "debug", पूर्ण;

	priv = devm_kzalloc(dev, माप(काष्ठा यंत्र9260_wdt_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	priv->iobase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->iobase))
		वापस PTR_ERR(priv->iobase);

	priv->rst = devm_reset_control_get_exclusive(dev, "wdt_rst");
	अगर (IS_ERR(priv->rst))
		वापस PTR_ERR(priv->rst);

	ret = यंत्र9260_wdt_get_dt_clks(priv);
	अगर (ret)
		वापस ret;

	wdd = &priv->wdd;
	wdd->info = &यंत्र9260_wdt_ident;
	wdd->ops = &यंत्र9260_wdt_ops;
	wdd->min_समयout = 1;
	wdd->max_समयout = BM_WDTC_MAX(priv->wdt_freq);
	wdd->parent = dev;

	watchकरोg_set_drvdata(wdd, priv);

	/*
	 * If 'timeout-sec' unspecअगरied in devicetree, assume a 30 second
	 * शेष, unless the max समयout is less than 30 seconds, then use
	 * the max instead.
	 */
	wdd->समयout = ASM9260_WDT_DEFAULT_TIMEOUT;
	watchकरोg_init_समयout(wdd, 0, dev);

	यंत्र9260_wdt_get_dt_mode(priv);

	अगर (priv->mode != HW_RESET)
		priv->irq = platक्रमm_get_irq(pdev, 0);

	अगर (priv->irq > 0) अणु
		/*
		 * Not all supported platक्रमms specअगरy an पूर्णांकerrupt क्रम the
		 * watchकरोg, so let's make it optional.
		 */
		ret = devm_request_irq(dev, priv->irq, यंत्र9260_wdt_irq, 0,
				       pdev->name, priv);
		अगर (ret < 0)
			dev_warn(dev, "failed to request IRQ\n");
	पूर्ण

	watchकरोg_set_restart_priority(wdd, 128);

	watchकरोg_stop_on_reboot(wdd);
	watchकरोg_stop_on_unरेजिस्टर(wdd);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	dev_info(dev, "Watchdog enabled (timeout: %d sec, mode: %s)\n",
		 wdd->समयout, mode_name[priv->mode]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id यंत्र9260_wdt_of_match[] = अणु
	अणु .compatible = "alphascale,asm9260-wdt"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, यंत्र9260_wdt_of_match);

अटल काष्ठा platक्रमm_driver यंत्र9260_wdt_driver = अणु
	.driver = अणु
		.name = "asm9260-wdt",
		.of_match_table	= यंत्र9260_wdt_of_match,
	पूर्ण,
	.probe = यंत्र9260_wdt_probe,
पूर्ण;
module_platक्रमm_driver(यंत्र9260_wdt_driver);

MODULE_DESCRIPTION("asm9260 WatchDog Timer Driver");
MODULE_AUTHOR("Oleksij Rempel <linux@rempel-privat.de>");
MODULE_LICENSE("GPL");
