<शैली गुरु>
/*
 * MOXA ART SoCs watchकरोg driver.
 *
 * Copyright (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/moduleparam.h>

#घोषणा REG_COUNT			0x4
#घोषणा REG_MODE			0x8
#घोषणा REG_ENABLE			0xC

काष्ठा moxart_wdt_dev अणु
	काष्ठा watchकरोg_device dev;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक घड़ी_frequency;
पूर्ण;

अटल पूर्णांक heartbeat;

अटल पूर्णांक moxart_wdt_restart(काष्ठा watchकरोg_device *wdt_dev,
			      अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा moxart_wdt_dev *moxart_wdt = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(1, moxart_wdt->base + REG_COUNT);
	ग_लिखोl(0x5ab9, moxart_wdt->base + REG_MODE);
	ग_लिखोl(0x03, moxart_wdt->base + REG_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा moxart_wdt_dev *moxart_wdt = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(0, moxart_wdt->base + REG_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा moxart_wdt_dev *moxart_wdt = watchकरोg_get_drvdata(wdt_dev);

	ग_लिखोl(moxart_wdt->घड़ी_frequency * wdt_dev->समयout,
	       moxart_wdt->base + REG_COUNT);
	ग_लिखोl(0x5ab9, moxart_wdt->base + REG_MODE);
	ग_लिखोl(0x03, moxart_wdt->base + REG_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				  अचिन्हित पूर्णांक समयout)
अणु
	wdt_dev->समयout = समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info moxart_wdt_info = अणु
	.identity       = "moxart-wdt",
	.options        = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops moxart_wdt_ops = अणु
	.owner          = THIS_MODULE,
	.start          = moxart_wdt_start,
	.stop           = moxart_wdt_stop,
	.set_समयout    = moxart_wdt_set_समयout,
	.restart        = moxart_wdt_restart,
पूर्ण;

अटल पूर्णांक moxart_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा moxart_wdt_dev *moxart_wdt;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *clk;
	पूर्णांक err;
	अचिन्हित पूर्णांक max_समयout;
	bool nowayout = WATCHDOG_NOWAYOUT;

	moxart_wdt = devm_kzalloc(dev, माप(*moxart_wdt), GFP_KERNEL);
	अगर (!moxart_wdt)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, moxart_wdt);

	moxart_wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(moxart_wdt->base))
		वापस PTR_ERR(moxart_wdt->base);

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: of_clk_get failed\n", __func__);
		वापस PTR_ERR(clk);
	पूर्ण

	moxart_wdt->घड़ी_frequency = clk_get_rate(clk);
	अगर (moxart_wdt->घड़ी_frequency == 0) अणु
		pr_err("%s: incorrect clock frequency\n", __func__);
		वापस -EINVAL;
	पूर्ण

	max_समयout = अच_पूर्णांक_उच्च / moxart_wdt->घड़ी_frequency;

	moxart_wdt->dev.info = &moxart_wdt_info;
	moxart_wdt->dev.ops = &moxart_wdt_ops;
	moxart_wdt->dev.समयout = max_समयout;
	moxart_wdt->dev.min_समयout = 1;
	moxart_wdt->dev.max_समयout = max_समयout;
	moxart_wdt->dev.parent = dev;

	watchकरोg_init_समयout(&moxart_wdt->dev, heartbeat, dev);
	watchकरोg_set_nowayout(&moxart_wdt->dev, nowayout);
	watchकरोg_set_restart_priority(&moxart_wdt->dev, 128);

	watchकरोg_set_drvdata(&moxart_wdt->dev, moxart_wdt);

	watchकरोg_stop_on_unरेजिस्टर(&moxart_wdt->dev);
	err = devm_watchकरोg_रेजिस्टर_device(dev, &moxart_wdt->dev);
	अगर (err)
		वापस err;

	dev_dbg(dev, "Watchdog enabled (heartbeat=%d sec, nowayout=%d)\n",
		moxart_wdt->dev.समयout, nowayout);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id moxart_watchकरोg_match[] = अणु
	अणु .compatible = "moxa,moxart-watchdog" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, moxart_watchकरोg_match);

अटल काष्ठा platक्रमm_driver moxart_wdt_driver = अणु
	.probe      = moxart_wdt_probe,
	.driver     = अणु
		.name		= "moxart-watchdog",
		.of_match_table	= moxart_watchकरोg_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(moxart_wdt_driver);

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeat in seconds");

MODULE_DESCRIPTION("MOXART watchdog driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonas Jensen <jonas.jensen@gmail.com>");
