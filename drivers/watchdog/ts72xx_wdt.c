<शैली गुरु>
/*
 * Watchकरोg driver क्रम Technologic Systems TS-72xx based SBCs
 * (TS-7200, TS-7250 and TS-7260). These boards have बाह्यal
 * glue logic CPLD chip, which includes programmable watchकरोg
 * समयr.
 *
 * Copyright (c) 2009 Mika Westerberg <mika.westerberg@iki.fi>
 *
 * This driver is based on ep93xx_wdt and wm831x_wdt drivers.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पन.स>

#घोषणा TS72XX_WDT_DEFAULT_TIMEOUT	30

अटल पूर्णांक समयout;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds.");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Disable watchdog shutdown on close");

/* priv->control_reg */
#घोषणा TS72XX_WDT_CTRL_DISABLE		0x00
#घोषणा TS72XX_WDT_CTRL_250MS		0x01
#घोषणा TS72XX_WDT_CTRL_500MS		0x02
#घोषणा TS72XX_WDT_CTRL_1SEC		0x03
#घोषणा TS72XX_WDT_CTRL_RESERVED	0x04
#घोषणा TS72XX_WDT_CTRL_2SEC		0x05
#घोषणा TS72XX_WDT_CTRL_4SEC		0x06
#घोषणा TS72XX_WDT_CTRL_8SEC		0x07

/* priv->feed_reg */
#घोषणा TS72XX_WDT_FEED_VAL		0x05

काष्ठा ts72xx_wdt_priv अणु
	व्योम __iomem	*control_reg;
	व्योम __iomem	*feed_reg;
	काष्ठा watchकरोg_device wdd;
	अचिन्हित अक्षर regval;
पूर्ण;

अटल पूर्णांक ts72xx_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ts72xx_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ग_लिखोb(TS72XX_WDT_FEED_VAL, priv->feed_reg);
	ग_लिखोb(priv->regval, priv->control_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक ts72xx_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ts72xx_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ग_लिखोb(TS72XX_WDT_FEED_VAL, priv->feed_reg);
	ग_लिखोb(TS72XX_WDT_CTRL_DISABLE, priv->control_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक ts72xx_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ts72xx_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ग_लिखोb(TS72XX_WDT_FEED_VAL, priv->feed_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक ts72xx_wdt_समय_रखोout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक to)
अणु
	काष्ठा ts72xx_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	अगर (to == 1) अणु
		priv->regval = TS72XX_WDT_CTRL_1SEC;
	पूर्ण अन्यथा अगर (to == 2) अणु
		priv->regval = TS72XX_WDT_CTRL_2SEC;
	पूर्ण अन्यथा अगर (to <= 4) अणु
		priv->regval = TS72XX_WDT_CTRL_4SEC;
		to = 4;
	पूर्ण अन्यथा अणु
		priv->regval = TS72XX_WDT_CTRL_8SEC;
		अगर (to <= 8)
			to = 8;
	पूर्ण

	wdd->समयout = to;

	अगर (watchकरोg_active(wdd)) अणु
		ts72xx_wdt_stop(wdd);
		ts72xx_wdt_start(wdd);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ts72xx_wdt_ident = अणु
	.options		= WDIOF_KEEPALIVEPING |
				  WDIOF_SETTIMEOUT |
				  WDIOF_MAGICCLOSE,
	.firmware_version	= 1,
	.identity		= "TS-72XX WDT",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ts72xx_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= ts72xx_wdt_start,
	.stop		= ts72xx_wdt_stop,
	.ping		= ts72xx_wdt_ping,
	.set_समयout	= ts72xx_wdt_समय_रखोout,
पूर्ण;

अटल पूर्णांक ts72xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ts72xx_wdt_priv *priv;
	काष्ठा watchकरोg_device *wdd;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->control_reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->control_reg))
		वापस PTR_ERR(priv->control_reg);

	priv->feed_reg = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->feed_reg))
		वापस PTR_ERR(priv->feed_reg);

	wdd = &priv->wdd;
	wdd->info = &ts72xx_wdt_ident;
	wdd->ops = &ts72xx_wdt_ops;
	wdd->min_समयout = 1;
	wdd->max_hw_heartbeat_ms = 8000;
	wdd->parent = dev;

	watchकरोg_set_nowayout(wdd, nowayout);

	wdd->समयout = TS72XX_WDT_DEFAULT_TIMEOUT;
	watchकरोg_init_समयout(wdd, समयout, dev);

	watchकरोg_set_drvdata(wdd, priv);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	dev_info(dev, "TS-72xx Watchdog driver\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ts72xx_wdt_driver = अणु
	.probe		= ts72xx_wdt_probe,
	.driver		= अणु
		.name	= "ts72xx-wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ts72xx_wdt_driver);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@iki.fi>");
MODULE_DESCRIPTION("TS-72xx SBC Watchdog");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ts72xx-wdt");
