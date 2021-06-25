<शैली गुरु>
/*
 * Watchकरोg driver क्रम Cirrus Logic EP93xx family of devices.
 *
 * Copyright (c) 2004 Ray Lehtiniemi
 * Copyright (c) 2006 Tower Technologies
 * Based on ep93xx driver, bits from alim7101_wdt.c
 *
 * Authors: Ray Lehtiniemi <rayl@mail.com>,
 *	Alessandro Zummo <a.zummo@towertech.it>
 *
 * Copyright (c) 2012 H Hartley Sweeten <hsweeten@visionengravers.com>
 *	Convert to a platक्रमm device and use the watchकरोg framework API
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * This watchकरोg fires after 250msec, which is a too लघु पूर्णांकerval
 * क्रम us to rely on the user space daemon alone. So we ping the
 * wdt each ~200msec and eventually stop करोing it अगर the user space
 * daemon dies.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पन.स>

/* शेष समयout (secs) */
#घोषणा WDT_TIMEOUT 30

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started");

अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds.");

#घोषणा EP93XX_WATCHDOG		0x00
#घोषणा EP93XX_WDSTATUS		0x04

काष्ठा ep93xx_wdt_priv अणु
	व्योम __iomem *mmio;
	काष्ठा watchकरोg_device wdd;
पूर्ण;

अटल पूर्णांक ep93xx_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ep93xx_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(0xaaaa, priv->mmio + EP93XX_WATCHDOG);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ep93xx_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(0xaa55, priv->mmio + EP93XX_WATCHDOG);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ep93xx_wdt_priv *priv = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(0x5555, priv->mmio + EP93XX_WATCHDOG);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ep93xx_wdt_ident = अणु
	.options	= WDIOF_CARDRESET |
			  WDIOF_SETTIMEOUT |
			  WDIOF_MAGICCLOSE |
			  WDIOF_KEEPALIVEPING,
	.identity	= "EP93xx Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ep93xx_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= ep93xx_wdt_start,
	.stop		= ep93xx_wdt_stop,
	.ping		= ep93xx_wdt_ping,
पूर्ण;

अटल पूर्णांक ep93xx_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ep93xx_wdt_priv *priv;
	काष्ठा watchकरोg_device *wdd;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->mmio))
		वापस PTR_ERR(priv->mmio);

	val = पढ़ोl(priv->mmio + EP93XX_WATCHDOG);

	wdd = &priv->wdd;
	wdd->bootstatus = (val & 0x01) ? WDIOF_CARDRESET : 0;
	wdd->info = &ep93xx_wdt_ident;
	wdd->ops = &ep93xx_wdt_ops;
	wdd->min_समयout = 1;
	wdd->max_hw_heartbeat_ms = 200;
	wdd->parent = dev;

	watchकरोg_set_nowayout(wdd, nowayout);

	wdd->समयout = WDT_TIMEOUT;
	watchकरोg_init_समयout(wdd, समयout, dev);

	watchकरोg_set_drvdata(wdd, priv);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	dev_info(dev, "EP93XX watchdog driver %s\n",
		 (val & 0x08) ? " (nCS1 disable detected)" : "");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_wdt_driver = अणु
	.driver		= अणु
		.name	= "ep93xx-wdt",
	पूर्ण,
	.probe		= ep93xx_wdt_probe,
पूर्ण;

module_platक्रमm_driver(ep93xx_wdt_driver);

MODULE_AUTHOR("Ray Lehtiniemi <rayl@mail.com>");
MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("EP93xx Watchdog");
MODULE_LICENSE("GPL");
