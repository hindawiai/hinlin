<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * txx9wdt: A Hardware Watchकरोg Driver क्रम TXx9 SoCs
 *
 * Copyright (C) 2007 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/txx9पंचांगr.h>

#घोषणा WD_TIMER_CCD	7		/* 1/256 */
#घोषणा WD_TIMER_CLK	(clk_get_rate(txx9_imclk) / (2 << WD_TIMER_CCD))
#घोषणा WD_MAX_TIMEOUT	((0xffffffff >> (32 - TXX9_TIMER_BITS)) / WD_TIMER_CLK)
#घोषणा TIMER_MARGIN	60		/* Default is 60 seconds */

अटल अचिन्हित पूर्णांक समयout = TIMER_MARGIN;	/* in seconds */
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. "
	"(0<समयout<((2^" __MODULE_STRING(TXX9_TIMER_BITS) ")/(IMCLK/256)), "
	"default=" __MODULE_STRING(TIMER_MARGIN) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल काष्ठा txx9_पंचांगr_reg __iomem *txx9wdt_reg;
अटल काष्ठा clk *txx9_imclk;
अटल DEFINE_SPINLOCK(txx9_lock);

अटल पूर्णांक txx9wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	spin_lock(&txx9_lock);
	__raw_ग_लिखोl(TXx9_TMWTMR_TWIE | TXx9_TMWTMR_TWC, &txx9wdt_reg->wपंचांगr);
	spin_unlock(&txx9_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	spin_lock(&txx9_lock);
	__raw_ग_लिखोl(WD_TIMER_CLK * wdt_dev->समयout, &txx9wdt_reg->cpra);
	__raw_ग_लिखोl(WD_TIMER_CCD, &txx9wdt_reg->ccdr);
	__raw_ग_लिखोl(0, &txx9wdt_reg->tisr);	/* clear pending पूर्णांकerrupt */
	__raw_ग_लिखोl(TXx9_TMTCR_TCE | TXx9_TMTCR_CCDE | TXx9_TMTCR_TMODE_WDOG,
		     &txx9wdt_reg->tcr);
	__raw_ग_लिखोl(TXx9_TMWTMR_TWIE | TXx9_TMWTMR_TWC, &txx9wdt_reg->wपंचांगr);
	spin_unlock(&txx9_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	spin_lock(&txx9_lock);
	__raw_ग_लिखोl(TXx9_TMWTMR_WDIS, &txx9wdt_reg->wपंचांगr);
	__raw_ग_लिखोl(__raw_पढ़ोl(&txx9wdt_reg->tcr) & ~TXx9_TMTCR_TCE,
		     &txx9wdt_reg->tcr);
	spin_unlock(&txx9_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक txx9wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
			       अचिन्हित पूर्णांक new_समयout)
अणु
	wdt_dev->समयout = new_समयout;
	txx9wdt_stop(wdt_dev);
	txx9wdt_start(wdt_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info txx9wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "Hardware Watchdog for TXx9",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops txx9wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = txx9wdt_start,
	.stop = txx9wdt_stop,
	.ping = txx9wdt_ping,
	.set_समयout = txx9wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device txx9wdt = अणु
	.info = &txx9wdt_info,
	.ops = &txx9wdt_ops,
पूर्ण;

अटल पूर्णांक __init txx9wdt_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	txx9_imclk = clk_get(शून्य, "imbus_clk");
	अगर (IS_ERR(txx9_imclk)) अणु
		ret = PTR_ERR(txx9_imclk);
		txx9_imclk = शून्य;
		जाओ निकास;
	पूर्ण
	ret = clk_prepare_enable(txx9_imclk);
	अगर (ret) अणु
		clk_put(txx9_imclk);
		txx9_imclk = शून्य;
		जाओ निकास;
	पूर्ण

	txx9wdt_reg = devm_platक्रमm_ioremap_resource(dev, 0);
	अगर (IS_ERR(txx9wdt_reg)) अणु
		ret = PTR_ERR(txx9wdt_reg);
		जाओ निकास;
	पूर्ण

	अगर (समयout < 1 || समयout > WD_MAX_TIMEOUT)
		समयout = TIMER_MARGIN;
	txx9wdt.समयout = समयout;
	txx9wdt.min_समयout = 1;
	txx9wdt.max_समयout = WD_MAX_TIMEOUT;
	txx9wdt.parent = &dev->dev;
	watchकरोg_set_nowayout(&txx9wdt, nowayout);

	ret = watchकरोg_रेजिस्टर_device(&txx9wdt);
	अगर (ret)
		जाओ निकास;

	pr_info("Hardware Watchdog Timer: timeout=%d sec (max %ld) (nowayout= %d)\n",
		समयout, WD_MAX_TIMEOUT, nowayout);

	वापस 0;
निकास:
	अगर (txx9_imclk) अणु
		clk_disable_unprepare(txx9_imclk);
		clk_put(txx9_imclk);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __निकास txx9wdt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	watchकरोg_unरेजिस्टर_device(&txx9wdt);
	clk_disable_unprepare(txx9_imclk);
	clk_put(txx9_imclk);
	वापस 0;
पूर्ण

अटल व्योम txx9wdt_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	txx9wdt_stop(&txx9wdt);
पूर्ण

अटल काष्ठा platक्रमm_driver txx9wdt_driver = अणु
	.हटाओ = __निकास_p(txx9wdt_हटाओ),
	.shutकरोwn = txx9wdt_shutकरोwn,
	.driver = अणु
		.name = "txx9wdt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(txx9wdt_driver, txx9wdt_probe);

MODULE_DESCRIPTION("TXx9 Watchdog Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:txx9wdt");
