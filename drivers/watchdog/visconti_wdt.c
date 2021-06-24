<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 TOSHIBA CORPORATION
 * Copyright (c) 2020 Toshiba Electronic Devices & Storage Corporation
 * Copyright (c) 2020 Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा WDT_CNT			0x00
#घोषणा WDT_MIN			0x04
#घोषणा WDT_MAX			0x08
#घोषणा WDT_CTL			0x0c
#घोषणा WDT_CMD			0x10
#घोषणा WDT_CMD_CLEAR		0x4352
#घोषणा WDT_CMD_START_STOP	0x5354
#घोषणा WDT_DIV			0x30

#घोषणा VISCONTI_WDT_FREQ	2000000 /* 2MHz */
#घोषणा WDT_DEFAULT_TIMEOUT	10U /* in seconds */

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(
	nowayout,
	"Watchdog cannot be stopped once started (default=" __MODULE_STRING(WATCHDOG_NOWAYOUT)")");

काष्ठा visconti_wdt_priv अणु
	काष्ठा watchकरोg_device wdev;
	व्योम __iomem *base;
	u32 भाग;
पूर्ण;

अटल पूर्णांक visconti_wdt_start(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा visconti_wdt_priv *priv = watchकरोg_get_drvdata(wdev);
	u32 समयout = wdev->समयout * VISCONTI_WDT_FREQ;

	ग_लिखोl(priv->भाग, priv->base + WDT_DIV);
	ग_लिखोl(0, priv->base + WDT_MIN);
	ग_लिखोl(समयout, priv->base + WDT_MAX);
	ग_लिखोl(0, priv->base + WDT_CTL);
	ग_लिखोl(WDT_CMD_START_STOP, priv->base + WDT_CMD);

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_wdt_stop(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा visconti_wdt_priv *priv = watchकरोg_get_drvdata(wdev);

	ग_लिखोl(1, priv->base + WDT_CTL);
	ग_लिखोl(WDT_CMD_START_STOP, priv->base + WDT_CMD);

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा visconti_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(WDT_CMD_CLEAR, priv->base + WDT_CMD);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक visconti_wdt_get_समयleft(काष्ठा watchकरोg_device *wdev)
अणु
	काष्ठा visconti_wdt_priv *priv = watchकरोg_get_drvdata(wdev);
	u32 समयout = wdev->समयout * VISCONTI_WDT_FREQ;
	u32 cnt = पढ़ोl(priv->base + WDT_CNT);

	अगर (समयout <= cnt)
		वापस 0;
	समयout -= cnt;

	वापस समयout / VISCONTI_WDT_FREQ;
पूर्ण

अटल पूर्णांक visconti_wdt_set_समयout(काष्ठा watchकरोg_device *wdev, अचिन्हित पूर्णांक समयout)
अणु
	u32 val;
	काष्ठा visconti_wdt_priv *priv = watchकरोg_get_drvdata(wdev);

	wdev->समयout = समयout;
	val = wdev->समयout * VISCONTI_WDT_FREQ;

	/* Clear counter beक्रमe setting समयout because WDT expires */
	ग_लिखोl(WDT_CMD_CLEAR, priv->base + WDT_CMD);
	ग_लिखोl(val, priv->base + WDT_MAX);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info visconti_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "Visconti Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops visconti_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= visconti_wdt_start,
	.stop		= visconti_wdt_stop,
	.ping		= visconti_wdt_ping,
	.get_समयleft	= visconti_wdt_get_समयleft,
	.set_समयout	= visconti_wdt_set_समयout,
पूर्ण;

अटल व्योम visconti_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक visconti_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा watchकरोg_device *wdev;
	काष्ठा visconti_wdt_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *clk;
	पूर्णांक ret;
	अचिन्हित दीर्घ clk_freq;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(dev, PTR_ERR(clk), "Could not get clock\n");

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "Could not enable clock\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, visconti_clk_disable_unprepare, clk);
	अगर (ret)
		वापस ret;

	clk_freq = clk_get_rate(clk);
	अगर (!clk_freq)
		वापस -EINVAL;

	priv->भाग = clk_freq / VISCONTI_WDT_FREQ;

	/* Initialize काष्ठा watchकरोg_device. */
	wdev = &priv->wdev;
	wdev->info = &visconti_wdt_info;
	wdev->ops = &visconti_wdt_ops;
	wdev->parent = dev;
	wdev->min_समयout = 1;
	wdev->max_समयout = 0xffffffff / VISCONTI_WDT_FREQ;
	wdev->समयout = min(wdev->max_समयout, WDT_DEFAULT_TIMEOUT);

	watchकरोg_set_drvdata(wdev, priv);
	watchकरोg_set_nowayout(wdev, nowayout);
	watchकरोg_stop_on_unरेजिस्टर(wdev);

	/* This overrides the शेष समयout only अगर DT configuration was found */
	ret = watchकरोg_init_समयout(wdev, 0, dev);
	अगर (ret)
		dev_warn(dev, "Specified timeout value invalid, using default\n");

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id visconti_wdt_of_match[] = अणु
	अणु .compatible = "toshiba,visconti-wdt", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, visconti_wdt_of_match);

अटल काष्ठा platक्रमm_driver visconti_wdt_driver = अणु
	.driver = अणु
			.name = "visconti_wdt",
			.of_match_table = visconti_wdt_of_match,
		पूर्ण,
	.probe = visconti_wdt_probe,
पूर्ण;
module_platक्रमm_driver(visconti_wdt_driver);

MODULE_DESCRIPTION("TOSHIBA Visconti Watchdog Driver");
MODULE_AUTHOR("Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp");
MODULE_LICENSE("GPL v2");
