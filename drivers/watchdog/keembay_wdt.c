<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Watchकरोg driver क्रम Intel Keem Bay non-secure watchकरोg.
 *
 * Copyright (C) 2020 Intel Corporation
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/watchकरोg.h>

/* Non-secure watchकरोg रेजिस्टर offsets */
#घोषणा TIM_WATCHDOG		0x0
#घोषणा TIM_WATCHDOG_INT_THRES	0x4
#घोषणा TIM_WDOG_EN		0x8
#घोषणा TIM_SAFE		0xc

#घोषणा WDT_ISR_MASK		GENMASK(9, 8)
#घोषणा WDT_ISR_CLEAR		0x8200ff18
#घोषणा WDT_UNLOCK		0xf1d0dead
#घोषणा WDT_LOAD_MAX		U32_MAX
#घोषणा WDT_LOAD_MIN		1
#घोषणा WDT_TIMEOUT		5

अटल अचिन्हित पूर्णांक समयout = WDT_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout period in seconds (default = "
		 __MODULE_STRING(WDT_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default = "
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

काष्ठा keembay_wdt अणु
	काष्ठा watchकरोg_device	wdd;
	काष्ठा clk		*clk;
	अचिन्हित पूर्णांक		rate;
	पूर्णांक			to_irq;
	पूर्णांक			th_irq;
	व्योम __iomem		*base;
पूर्ण;

अटल अंतरभूत u32 keembay_wdt_पढ़ोl(काष्ठा keembay_wdt *wdt, u32 offset)
अणु
	वापस पढ़ोl(wdt->base + offset);
पूर्ण

अटल अंतरभूत व्योम keembay_wdt_ग_लिखोl(काष्ठा keembay_wdt *wdt, u32 offset, u32 val)
अणु
	ग_लिखोl(WDT_UNLOCK, wdt->base + TIM_SAFE);
	ग_लिखोl(val, wdt->base + offset);
पूर्ण

अटल व्योम keembay_wdt_set_समयout_reg(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा keembay_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	keembay_wdt_ग_लिखोl(wdt, TIM_WATCHDOG, wकरोg->समयout * wdt->rate);
पूर्ण

अटल व्योम keembay_wdt_set_preसमयout_reg(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा keembay_wdt *wdt = watchकरोg_get_drvdata(wकरोg);
	u32 th_val = 0;

	अगर (wकरोg->preसमयout)
		th_val = wकरोg->समयout - wकरोg->preसमयout;

	keembay_wdt_ग_लिखोl(wdt, TIM_WATCHDOG_INT_THRES, th_val * wdt->rate);
पूर्ण

अटल पूर्णांक keembay_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा keembay_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	keembay_wdt_set_समयout_reg(wकरोg);
	keembay_wdt_ग_लिखोl(wdt, TIM_WDOG_EN, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक keembay_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा keembay_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	keembay_wdt_ग_लिखोl(wdt, TIM_WDOG_EN, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक keembay_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	keembay_wdt_set_समयout_reg(wकरोg);

	वापस 0;
पूर्ण

अटल पूर्णांक keembay_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg, u32 t)
अणु
	wकरोg->समयout = t;
	keembay_wdt_set_समयout_reg(wकरोg);

	वापस 0;
पूर्ण

अटल पूर्णांक keembay_wdt_set_preसमयout(काष्ठा watchकरोg_device *wकरोg, u32 t)
अणु
	अगर (t > wकरोg->समयout)
		वापस -EINVAL;

	wकरोg->preसमयout = t;
	keembay_wdt_set_preसमयout_reg(wकरोg);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक keembay_wdt_get_समयleft(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा keembay_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	वापस keembay_wdt_पढ़ोl(wdt, TIM_WATCHDOG) / wdt->rate;
पूर्ण

/*
 * SMC call is used to clear the पूर्णांकerrupt bits, because the TIM_GEN_CONFIG
 * रेजिस्टर is in the secure bank.
 */
अटल irqवापस_t keembay_wdt_to_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा keembay_wdt *wdt = dev_id;
	काष्ठा arm_smccc_res res;

	keembay_wdt_ग_लिखोl(wdt, TIM_WATCHDOG, 1);
	arm_smccc_smc(WDT_ISR_CLEAR, WDT_ISR_MASK, 0, 0, 0, 0, 0, 0, &res);
	dev_crit(wdt->wdd.parent, "Intel Keem Bay non-sec wdt timeout.\n");
	emergency_restart();

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t keembay_wdt_th_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा keembay_wdt *wdt = dev_id;
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(WDT_ISR_CLEAR, WDT_ISR_MASK, 0, 0, 0, 0, 0, 0, &res);
	dev_crit(wdt->wdd.parent, "Intel Keem Bay non-sec wdt pre-timeout.\n");
	watchकरोg_notअगरy_preसमयout(&wdt->wdd);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info keembay_wdt_info = अणु
	.identity	= "Intel Keem Bay Watchdog Timer",
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_PRETIMEOUT |
			  WDIOF_MAGICCLOSE |
			  WDIOF_KEEPALIVEPING,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops keembay_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= keembay_wdt_start,
	.stop		= keembay_wdt_stop,
	.ping		= keembay_wdt_ping,
	.set_समयout	= keembay_wdt_set_समयout,
	.set_preसमयout	= keembay_wdt_set_preसमयout,
	.get_समयleft	= keembay_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक keembay_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा keembay_wdt *wdt;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	/* we करो not need to enable the घड़ी as it is enabled by शेष */
	wdt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(wdt->clk))
		वापस dev_err_probe(dev, PTR_ERR(wdt->clk), "Failed to get clock\n");

	wdt->rate = clk_get_rate(wdt->clk);
	अगर (!wdt->rate)
		वापस dev_err_probe(dev, -EINVAL, "Failed to get clock rate\n");

	wdt->th_irq = platक्रमm_get_irq_byname(pdev, "threshold");
	अगर (wdt->th_irq < 0)
		वापस dev_err_probe(dev, wdt->th_irq, "Failed to get IRQ for threshold\n");

	ret = devm_request_irq(dev, wdt->th_irq, keembay_wdt_th_isr, 0,
			       "keembay-wdt", wdt);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Failed to request IRQ for threshold\n");

	wdt->to_irq = platक्रमm_get_irq_byname(pdev, "timeout");
	अगर (wdt->to_irq < 0)
		वापस dev_err_probe(dev, wdt->to_irq, "Failed to get IRQ for timeout\n");

	ret = devm_request_irq(dev, wdt->to_irq, keembay_wdt_to_isr, 0,
			       "keembay-wdt", wdt);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Failed to request IRQ for timeout\n");

	wdt->wdd.parent		= dev;
	wdt->wdd.info		= &keembay_wdt_info;
	wdt->wdd.ops		= &keembay_wdt_ops;
	wdt->wdd.min_समयout	= WDT_LOAD_MIN;
	wdt->wdd.max_समयout	= WDT_LOAD_MAX / wdt->rate;
	wdt->wdd.समयout	= WDT_TIMEOUT;

	watchकरोg_set_drvdata(&wdt->wdd, wdt);
	watchकरोg_set_nowayout(&wdt->wdd, nowayout);
	watchकरोg_init_समयout(&wdt->wdd, समयout, dev);
	keembay_wdt_set_समयout(&wdt->wdd, wdt->wdd.समयout);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Failed to register watchdog device.\n");

	platक्रमm_set_drvdata(pdev, wdt);
	dev_info(dev, "Initial timeout %d sec%s.\n",
		 wdt->wdd.समयout, nowayout ? ", nowayout" : "");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused keembay_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा keembay_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		वापस keembay_wdt_stop(&wdt->wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused keembay_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा keembay_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		वापस keembay_wdt_start(&wdt->wdd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(keembay_wdt_pm_ops, keembay_wdt_suspend,
			 keembay_wdt_resume);

अटल स्थिर काष्ठा of_device_id keembay_wdt_match[] = अणु
	अणु .compatible = "intel,keembay-wdt" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, keembay_wdt_match);

अटल काष्ठा platक्रमm_driver keembay_wdt_driver = अणु
	.probe		= keembay_wdt_probe,
	.driver		= अणु
		.name		= "keembay_wdt",
		.of_match_table	= keembay_wdt_match,
		.pm		= &keembay_wdt_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(keembay_wdt_driver);

MODULE_DESCRIPTION("Intel Keem Bay SoC watchdog driver");
MODULE_AUTHOR("Wan Ahmad Zainie <wan.ahmad.zainie.wan.mohamad@intel.com");
MODULE_LICENSE("GPL v2");
