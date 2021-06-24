<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम STM32 Independent Watchकरोg
 *
 * Copyright (C) STMicroelectronics 2017
 * Author: Yannick Fertre <yannick.fertre@st.com> क्रम STMicroelectronics.
 *
 * This driver is based on tegra_wdt.c
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

/* IWDG रेजिस्टरs */
#घोषणा IWDG_KR		0x00 /* Key रेजिस्टर */
#घोषणा IWDG_PR		0x04 /* Prescaler Register */
#घोषणा IWDG_RLR	0x08 /* ReLoad Register */
#घोषणा IWDG_SR		0x0C /* Status Register */
#घोषणा IWDG_WINR	0x10 /* Winकरोws Register */

/* IWDG_KR रेजिस्टर bit mask */
#घोषणा KR_KEY_RELOAD	0xAAAA /* reload counter enable */
#घोषणा KR_KEY_ENABLE	0xCCCC /* peripheral enable */
#घोषणा KR_KEY_EWA	0x5555 /* ग_लिखो access enable */
#घोषणा KR_KEY_DWA	0x0000 /* ग_लिखो access disable */

/* IWDG_PR रेजिस्टर */
#घोषणा PR_SHIFT	2
#घोषणा PR_MIN		BIT(PR_SHIFT)

/* IWDG_RLR रेजिस्टर values */
#घोषणा RLR_MIN		0x2		/* min value recommended */
#घोषणा RLR_MAX		GENMASK(11, 0)	/* max value of reload रेजिस्टर */

/* IWDG_SR रेजिस्टर bit mask */
#घोषणा SR_PVU	BIT(0) /* Watchकरोg prescaler value update */
#घोषणा SR_RVU	BIT(1) /* Watchकरोg counter reload value update */

/* set समयout to 100000 us */
#घोषणा TIMEOUT_US	100000
#घोषणा SLEEP_US	1000

काष्ठा sपंचांग32_iwdg_data अणु
	bool has_pclk;
	u32 max_prescaler;
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_iwdg_data sपंचांग32_iwdg_data = अणु
	.has_pclk = false,
	.max_prescaler = 256,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_iwdg_data sपंचांग32mp1_iwdg_data = अणु
	.has_pclk = true,
	.max_prescaler = 1024,
पूर्ण;

काष्ठा sपंचांग32_iwdg अणु
	काष्ठा watchकरोg_device	wdd;
	स्थिर काष्ठा sपंचांग32_iwdg_data *data;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk_lsi;
	काष्ठा clk		*clk_pclk;
	अचिन्हित पूर्णांक		rate;
पूर्ण;

अटल अंतरभूत u32 reg_पढ़ो(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl_relaxed(base + reg);
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखो(व्योम __iomem *base, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, base + reg);
पूर्ण

अटल पूर्णांक sपंचांग32_iwdg_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sपंचांग32_iwdg *wdt = watchकरोg_get_drvdata(wdd);
	u32 tout, presc, iwdg_rlr, iwdg_pr, iwdg_sr;
	पूर्णांक ret;

	dev_dbg(wdd->parent, "%s\n", __func__);

	tout = clamp_t(अचिन्हित पूर्णांक, wdd->समयout,
		       wdd->min_समयout, wdd->max_hw_heartbeat_ms / 1000);

	presc = DIV_ROUND_UP(tout * wdt->rate, RLR_MAX + 1);

	/* The prescaler is align on घातer of 2 and start at 2 ^ PR_SHIFT. */
	presc = roundup_घात_of_two(presc);
	iwdg_pr = presc <= 1 << PR_SHIFT ? 0 : ilog2(presc) - PR_SHIFT;
	iwdg_rlr = ((tout * wdt->rate) / presc) - 1;

	/* enable ग_लिखो access */
	reg_ग_लिखो(wdt->regs, IWDG_KR, KR_KEY_EWA);

	/* set prescaler & reload रेजिस्टरs */
	reg_ग_लिखो(wdt->regs, IWDG_PR, iwdg_pr);
	reg_ग_लिखो(wdt->regs, IWDG_RLR, iwdg_rlr);
	reg_ग_लिखो(wdt->regs, IWDG_KR, KR_KEY_ENABLE);

	/* रुको क्रम the रेजिस्टरs to be updated (max 100ms) */
	ret = पढ़ोl_relaxed_poll_समयout(wdt->regs + IWDG_SR, iwdg_sr,
					 !(iwdg_sr & (SR_PVU | SR_RVU)),
					 SLEEP_US, TIMEOUT_US);
	अगर (ret) अणु
		dev_err(wdd->parent, "Fail to set prescaler, reload regs\n");
		वापस ret;
	पूर्ण

	/* reload watchकरोg */
	reg_ग_लिखो(wdt->regs, IWDG_KR, KR_KEY_RELOAD);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_iwdg_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sपंचांग32_iwdg *wdt = watchकरोg_get_drvdata(wdd);

	dev_dbg(wdd->parent, "%s\n", __func__);

	/* reload watchकरोg */
	reg_ग_लिखो(wdt->regs, IWDG_KR, KR_KEY_RELOAD);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_iwdg_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	dev_dbg(wdd->parent, "%s timeout: %d sec\n", __func__, समयout);

	wdd->समयout = समयout;

	अगर (watchकरोg_active(wdd))
		वापस sपंचांग32_iwdg_start(wdd);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक sपंचांग32_iwdg_clk_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा sपंचांग32_iwdg *wdt)
अणु
	काष्ठा device *dev = &pdev->dev;
	u32 ret;

	wdt->clk_lsi = devm_clk_get(dev, "lsi");
	अगर (IS_ERR(wdt->clk_lsi))
		वापस dev_err_probe(dev, PTR_ERR(wdt->clk_lsi), "Unable to get lsi clock\n");

	/* optional peripheral घड़ी */
	अगर (wdt->data->has_pclk) अणु
		wdt->clk_pclk = devm_clk_get(dev, "pclk");
		अगर (IS_ERR(wdt->clk_pclk))
			वापस dev_err_probe(dev, PTR_ERR(wdt->clk_pclk),
					     "Unable to get pclk clock\n");

		ret = clk_prepare_enable(wdt->clk_pclk);
		अगर (ret) अणु
			dev_err(dev, "Unable to prepare pclk clock\n");
			वापस ret;
		पूर्ण
		ret = devm_add_action_or_reset(dev,
					       sपंचांग32_clk_disable_unprepare,
					       wdt->clk_pclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = clk_prepare_enable(wdt->clk_lsi);
	अगर (ret) अणु
		dev_err(dev, "Unable to prepare lsi clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, sपंचांग32_clk_disable_unprepare,
				       wdt->clk_lsi);
	अगर (ret)
		वापस ret;

	wdt->rate = clk_get_rate(wdt->clk_lsi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sपंचांग32_iwdg_info = अणु
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_MAGICCLOSE |
			  WDIOF_KEEPALIVEPING,
	.identity	= "STM32 Independent Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops sपंचांग32_iwdg_ops = अणु
	.owner		= THIS_MODULE,
	.start		= sपंचांग32_iwdg_start,
	.ping		= sपंचांग32_iwdg_ping,
	.set_समयout	= sपंचांग32_iwdg_set_समयout,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_iwdg_of_match[] = अणु
	अणु .compatible = "st,stm32-iwdg", .data = &sपंचांग32_iwdg_data पूर्ण,
	अणु .compatible = "st,stm32mp1-iwdg", .data = &sपंचांग32mp1_iwdg_data पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_iwdg_of_match);

अटल पूर्णांक sपंचांग32_iwdg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा sपंचांग32_iwdg *wdt;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->data = of_device_get_match_data(&pdev->dev);
	अगर (!wdt->data)
		वापस -ENODEV;

	/* This is the समयr base. */
	wdt->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->regs)) अणु
		dev_err(dev, "Could not get resource\n");
		वापस PTR_ERR(wdt->regs);
	पूर्ण

	ret = sपंचांग32_iwdg_clk_init(pdev, wdt);
	अगर (ret)
		वापस ret;

	/* Initialize काष्ठा watchकरोg_device. */
	wdd = &wdt->wdd;
	wdd->parent = dev;
	wdd->info = &sपंचांग32_iwdg_info;
	wdd->ops = &sपंचांग32_iwdg_ops;
	wdd->min_समयout = DIV_ROUND_UP((RLR_MIN + 1) * PR_MIN, wdt->rate);
	wdd->max_hw_heartbeat_ms = ((RLR_MAX + 1) * wdt->data->max_prescaler *
				    1000) / wdt->rate;

	watchकरोg_set_drvdata(wdd, wdt);
	watchकरोg_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchकरोg_init_समयout(wdd, 0, dev);

	/*
	 * In हाल of CONFIG_WATCHDOG_HANDLE_BOOT_ENABLED is set
	 * (Means U-Boot/bootloaders leaves the watchकरोg running)
	 * When we get here we should make a decision to prevent
	 * any side effects beक्रमe user space daemon will take care of it.
	 * The best option, taking पूर्णांकo consideration that there is no
	 * way to पढ़ो values back from hardware, is to enक्रमce watchकरोg
	 * being run with deterministic values.
	 */
	अगर (IS_ENABLED(CONFIG_WATCHDOG_HANDLE_BOOT_ENABLED)) अणु
		ret = sपंचांग32_iwdg_start(wdd);
		अगर (ret)
			वापस ret;

		/* Make sure the watchकरोg is serviced */
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	पूर्ण

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdt);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांग32_iwdg_driver = अणु
	.probe		= sपंचांग32_iwdg_probe,
	.driver = अणु
		.name	= "iwdg",
		.of_match_table = of_match_ptr(sपंचांग32_iwdg_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_iwdg_driver);

MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 Independent Watchdog Driver");
MODULE_LICENSE("GPL v2");
