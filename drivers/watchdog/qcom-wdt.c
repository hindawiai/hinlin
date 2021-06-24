<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/of_device.h>

क्रमागत wdt_reg अणु
	WDT_RST,
	WDT_EN,
	WDT_STS,
	WDT_BARK_TIME,
	WDT_BITE_TIME,
पूर्ण;

#घोषणा QCOM_WDT_ENABLE		BIT(0)

अटल स्थिर u32 reg_offset_data_apcs_पंचांगr[] = अणु
	[WDT_RST] = 0x38,
	[WDT_EN] = 0x40,
	[WDT_STS] = 0x44,
	[WDT_BARK_TIME] = 0x4C,
	[WDT_BITE_TIME] = 0x5C,
पूर्ण;

अटल स्थिर u32 reg_offset_data_kpss[] = अणु
	[WDT_RST] = 0x4,
	[WDT_EN] = 0x8,
	[WDT_STS] = 0xC,
	[WDT_BARK_TIME] = 0x10,
	[WDT_BITE_TIME] = 0x14,
पूर्ण;

काष्ठा qcom_wdt_match_data अणु
	स्थिर u32 *offset;
	bool preसमयout;
पूर्ण;

काष्ठा qcom_wdt अणु
	काष्ठा watchकरोg_device	wdd;
	अचिन्हित दीर्घ		rate;
	व्योम __iomem		*base;
	स्थिर u32		*layout;
पूर्ण;

अटल व्योम __iomem *wdt_addr(काष्ठा qcom_wdt *wdt, क्रमागत wdt_reg reg)
अणु
	वापस wdt->base + wdt->layout[reg];
पूर्ण

अटल अंतरभूत
काष्ठा qcom_wdt *to_qcom_wdt(काष्ठा watchकरोg_device *wdd)
अणु
	वापस container_of(wdd, काष्ठा qcom_wdt, wdd);
पूर्ण

अटल irqवापस_t qcom_wdt_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा watchकरोg_device *wdd = arg;

	watchकरोg_notअगरy_preसमयout(wdd);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qcom_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा qcom_wdt *wdt = to_qcom_wdt(wdd);
	अचिन्हित पूर्णांक bark = wdd->समयout - wdd->preसमयout;

	ग_लिखोl(0, wdt_addr(wdt, WDT_EN));
	ग_लिखोl(1, wdt_addr(wdt, WDT_RST));
	ग_लिखोl(bark * wdt->rate, wdt_addr(wdt, WDT_BARK_TIME));
	ग_लिखोl(wdd->समयout * wdt->rate, wdt_addr(wdt, WDT_BITE_TIME));
	ग_लिखोl(QCOM_WDT_ENABLE, wdt_addr(wdt, WDT_EN));
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा qcom_wdt *wdt = to_qcom_wdt(wdd);

	ग_लिखोl(0, wdt_addr(wdt, WDT_EN));
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा qcom_wdt *wdt = to_qcom_wdt(wdd);

	ग_लिखोl(1, wdt_addr(wdt, WDT_RST));
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				अचिन्हित पूर्णांक समयout)
अणु
	wdd->समयout = समयout;
	वापस qcom_wdt_start(wdd);
पूर्ण

अटल पूर्णांक qcom_wdt_set_preसमयout(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित पूर्णांक समयout)
अणु
	wdd->preसमयout = समयout;
	वापस qcom_wdt_start(wdd);
पूर्ण

अटल पूर्णांक qcom_wdt_restart(काष्ठा watchकरोg_device *wdd, अचिन्हित दीर्घ action,
			    व्योम *data)
अणु
	काष्ठा qcom_wdt *wdt = to_qcom_wdt(wdd);
	u32 समयout;

	/*
	 * Trigger watchकरोg bite:
	 *    Setup BITE_TIME to be 128ms, and enable WDT.
	 */
	समयout = 128 * wdt->rate / 1000;

	ग_लिखोl(0, wdt_addr(wdt, WDT_EN));
	ग_लिखोl(1, wdt_addr(wdt, WDT_RST));
	ग_लिखोl(समयout, wdt_addr(wdt, WDT_BARK_TIME));
	ग_लिखोl(समयout, wdt_addr(wdt, WDT_BITE_TIME));
	ग_लिखोl(QCOM_WDT_ENABLE, wdt_addr(wdt, WDT_EN));

	/*
	 * Actually make sure the above sequence hits hardware beक्रमe sleeping.
	 */
	wmb();

	mdelay(150);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_wdt_is_running(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा qcom_wdt *wdt = to_qcom_wdt(wdd);

	वापस (पढ़ोl(wdt_addr(wdt, WDT_EN)) & QCOM_WDT_ENABLE);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops qcom_wdt_ops = अणु
	.start		= qcom_wdt_start,
	.stop		= qcom_wdt_stop,
	.ping		= qcom_wdt_ping,
	.set_समयout	= qcom_wdt_set_समयout,
	.set_preसमयout	= qcom_wdt_set_preसमयout,
	.restart        = qcom_wdt_restart,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info qcom_wdt_info = अणु
	.options	= WDIOF_KEEPALIVEPING
			| WDIOF_MAGICCLOSE
			| WDIOF_SETTIMEOUT
			| WDIOF_CARDRESET,
	.identity	= KBUILD_MODNAME,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info qcom_wdt_pt_info = अणु
	.options	= WDIOF_KEEPALIVEPING
			| WDIOF_MAGICCLOSE
			| WDIOF_SETTIMEOUT
			| WDIOF_PRETIMEOUT
			| WDIOF_CARDRESET,
	.identity	= KBUILD_MODNAME,
पूर्ण;

अटल व्योम qcom_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल स्थिर काष्ठा qcom_wdt_match_data match_data_apcs_पंचांगr = अणु
	.offset = reg_offset_data_apcs_पंचांगr,
	.preसमयout = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_wdt_match_data match_data_kpss = अणु
	.offset = reg_offset_data_kpss,
	.preसमयout = true,
पूर्ण;

अटल पूर्णांक qcom_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qcom_wdt *wdt;
	काष्ठा resource *res;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा qcom_wdt_match_data *data;
	u32 percpu_offset;
	पूर्णांक irq, ret;
	काष्ठा clk *clk;

	data = of_device_get_match_data(dev);
	अगर (!data) अणु
		dev_err(dev, "Unsupported QCOM WDT module\n");
		वापस -ENODEV;
	पूर्ण

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOMEM;

	/* We use CPU0's DGT क्रम the watchकरोg */
	अगर (of_property_पढ़ो_u32(np, "cpu-offset", &percpu_offset))
		percpu_offset = 0;

	res->start += percpu_offset;
	res->end += percpu_offset;

	wdt->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to get input clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "failed to setup clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, qcom_clk_disable_unprepare, clk);
	अगर (ret)
		वापस ret;

	/*
	 * We use the घड़ी rate to calculate the max समयout, so ensure it's
	 * not zero to aव्योम a भागide-by-zero exception.
	 *
	 * WATCHDOG_CORE assumes units of seconds, अगर the WDT is घड़ीed such
	 * that it would bite beक्रमe a second elapses it's usefulness is
	 * limited.  Bail अगर this is the हाल.
	 */
	wdt->rate = clk_get_rate(clk);
	अगर (wdt->rate == 0 ||
	    wdt->rate > 0x10000000U) अणु
		dev_err(dev, "invalid clock rate\n");
		वापस -EINVAL;
	पूर्ण

	/* check अगर there is preसमयout support */
	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (data->preसमयout && irq > 0) अणु
		ret = devm_request_irq(dev, irq, qcom_wdt_isr, 0,
				       "wdt_bark", &wdt->wdd);
		अगर (ret)
			वापस ret;

		wdt->wdd.info = &qcom_wdt_pt_info;
		wdt->wdd.preसमयout = 1;
	पूर्ण अन्यथा अणु
		अगर (irq == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		wdt->wdd.info = &qcom_wdt_info;
	पूर्ण

	wdt->wdd.ops = &qcom_wdt_ops;
	wdt->wdd.min_समयout = 1;
	wdt->wdd.max_समयout = 0x10000000U / wdt->rate;
	wdt->wdd.parent = dev;
	wdt->layout = data->offset;

	अगर (पढ़ोl(wdt_addr(wdt, WDT_STS)) & 1)
		wdt->wdd.bootstatus = WDIOF_CARDRESET;

	/*
	 * If 'timeout-sec' unspecअगरied in devicetree, assume a 30 second
	 * शेष, unless the max समयout is less than 30 seconds, then use
	 * the max instead.
	 */
	wdt->wdd.समयout = min(wdt->wdd.max_समयout, 30U);
	watchकरोg_init_समयout(&wdt->wdd, 0, dev);

	/*
	 * If WDT is alपढ़ोy running, call WDT start which
	 * will stop the WDT, set समयouts as bootloader
	 * might use dअगरferent ones and set running bit
	 * to inक्रमm the WDT subप्रणाली to ping the WDT
	 */
	अगर (qcom_wdt_is_running(&wdt->wdd)) अणु
		qcom_wdt_start(&wdt->wdd);
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &wdt->wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdt);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा qcom_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		qcom_wdt_stop(&wdt->wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा qcom_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		qcom_wdt_start(&wdt->wdd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(qcom_wdt_pm_ops, qcom_wdt_suspend, qcom_wdt_resume);

अटल स्थिर काष्ठा of_device_id qcom_wdt_of_table[] = अणु
	अणु .compatible = "qcom,kpss-timer", .data = &match_data_apcs_पंचांगr पूर्ण,
	अणु .compatible = "qcom,scss-timer", .data = &match_data_apcs_पंचांगr पूर्ण,
	अणु .compatible = "qcom,kpss-wdt", .data = &match_data_kpss पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_wdt_of_table);

अटल काष्ठा platक्रमm_driver qcom_watchकरोg_driver = अणु
	.probe	= qcom_wdt_probe,
	.driver	= अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= qcom_wdt_of_table,
		.pm		= &qcom_wdt_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_watchकरोg_driver);

MODULE_DESCRIPTION("QCOM KPSS Watchdog Driver");
MODULE_LICENSE("GPL v2");
