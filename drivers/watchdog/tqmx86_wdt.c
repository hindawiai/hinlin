<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम TQMx86 PLD.
 *
 * The watchकरोg supports घातer of 2 समयouts from 1 to 4096sec.
 * Once started, it cannot be stopped.
 *
 * Based on the venकरोr code written by Vadim V.Vlasov
 * <vvlasov@dev.rtsoft.ru>
 */

#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समयr.h>
#समावेश <linux/watchकरोg.h>

/* शेष समयout (secs) */
#घोषणा WDT_TIMEOUT 32

अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. (1<=timeout<=4096, default="
				__MODULE_STRING(WDT_TIMEOUT) ")");
काष्ठा tqmx86_wdt अणु
	काष्ठा watchकरोg_device wdd;
	व्योम __iomem *io_base;
पूर्ण;

#घोषणा TQMX86_WDCFG	0x00 /* Watchकरोg Configuration Register */
#घोषणा TQMX86_WDCS	0x01 /* Watchकरोg Config/Status Register */

अटल पूर्णांक tqmx86_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा tqmx86_wdt *priv = watchकरोg_get_drvdata(wdd);

	ioग_लिखो8(0x81, priv->io_base + TQMX86_WDCS);

	वापस 0;
पूर्ण

अटल पूर्णांक tqmx86_wdt_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक t)
अणु
	काष्ठा tqmx86_wdt *priv = watchकरोg_get_drvdata(wdd);
	u8 val;

	t = roundup_घात_of_two(t);
	val = ilog2(t) | 0x90;
	val += 3; /* values 0,1,2 correspond to 0.125,0.25,0.5s समयouts */
	ioग_लिखो8(val, priv->io_base + TQMX86_WDCFG);

	wdd->समयout = t;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info tqmx86_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING,
	.identity	= "TQMx86 Watchdog",
पूर्ण;

अटल काष्ठा watchकरोg_ops tqmx86_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= tqmx86_wdt_start,
	.set_समयout	= tqmx86_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक tqmx86_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tqmx86_wdt *priv;
	काष्ठा resource *res;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res)
		वापस -ENODEV;

	priv->io_base = devm_ioport_map(dev, res->start, resource_size(res));
	अगर (!priv->io_base)
		वापस -ENOMEM;

	watchकरोg_set_drvdata(&priv->wdd, priv);

	priv->wdd.parent = dev;
	priv->wdd.info = &tqmx86_wdt_info;
	priv->wdd.ops = &tqmx86_wdt_ops;
	priv->wdd.min_समयout = 1;
	priv->wdd.max_समयout = 4096;
	priv->wdd.max_hw_heartbeat_ms = 4096*1000;
	priv->wdd.समयout = WDT_TIMEOUT;

	watchकरोg_init_समयout(&priv->wdd, समयout, dev);
	watchकरोg_set_nowayout(&priv->wdd, WATCHDOG_NOWAYOUT);

	tqmx86_wdt_set_समयout(&priv->wdd, priv->wdd.समयout);

	err = devm_watchकरोg_रेजिस्टर_device(dev, &priv->wdd);
	अगर (err)
		वापस err;

	dev_info(dev, "TQMx86 watchdog\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tqmx86_wdt_driver = अणु
	.driver		= अणु
		.name	= "tqmx86-wdt",
	पूर्ण,
	.probe		= tqmx86_wdt_probe,
पूर्ण;

module_platक्रमm_driver(tqmx86_wdt_driver);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_DESCRIPTION("TQMx86 Watchdog");
MODULE_ALIAS("platform:tqmx86-wdt");
MODULE_LICENSE("GPL");
