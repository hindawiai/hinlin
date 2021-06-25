<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PIC32 watchकरोg driver
 *
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (c) 2016, Microchip Technology Inc.
 */
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/watchकरोg.h>

#समावेश <यंत्र/mach-pic32/pic32.h>

/* Watchकरोg Timer Registers */
#घोषणा WDTCON_REG		0x00

/* Watchकरोg Timer Control Register fields */
#घोषणा WDTCON_WIN_EN		BIT(0)
#घोषणा WDTCON_RMCS_MASK	0x0003
#घोषणा WDTCON_RMCS_SHIFT	0x0006
#घोषणा WDTCON_RMPS_MASK	0x001F
#घोषणा WDTCON_RMPS_SHIFT	0x0008
#घोषणा WDTCON_ON		BIT(15)
#घोषणा WDTCON_CLR_KEY		0x5743

/* Reset Control Register fields क्रम watchकरोg */
#घोषणा RESETCON_TIMEOUT_IDLE	BIT(2)
#घोषणा RESETCON_TIMEOUT_SLEEP	BIT(3)
#घोषणा RESETCON_WDT_TIMEOUT	BIT(4)

काष्ठा pic32_wdt अणु
	व्योम __iomem	*regs;
	व्योम __iomem	*rst_base;
	काष्ठा clk	*clk;
पूर्ण;

अटल अंतरभूत bool pic32_wdt_is_win_enabled(काष्ठा pic32_wdt *wdt)
अणु
	वापस !!(पढ़ोl(wdt->regs + WDTCON_REG) & WDTCON_WIN_EN);
पूर्ण

अटल अंतरभूत u32 pic32_wdt_get_post_scaler(काष्ठा pic32_wdt *wdt)
अणु
	u32 v = पढ़ोl(wdt->regs + WDTCON_REG);

	वापस (v >> WDTCON_RMPS_SHIFT) & WDTCON_RMPS_MASK;
पूर्ण

अटल अंतरभूत u32 pic32_wdt_get_clk_id(काष्ठा pic32_wdt *wdt)
अणु
	u32 v = पढ़ोl(wdt->regs + WDTCON_REG);

	वापस (v >> WDTCON_RMCS_SHIFT) & WDTCON_RMCS_MASK;
पूर्ण

अटल पूर्णांक pic32_wdt_bootstatus(काष्ठा pic32_wdt *wdt)
अणु
	u32 v = पढ़ोl(wdt->rst_base);

	ग_लिखोl(RESETCON_WDT_TIMEOUT, PIC32_CLR(wdt->rst_base));

	वापस v & RESETCON_WDT_TIMEOUT;
पूर्ण

अटल u32 pic32_wdt_get_समयout_secs(काष्ठा pic32_wdt *wdt, काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ rate;
	u32 period, ps, terminal;

	rate = clk_get_rate(wdt->clk);

	dev_dbg(dev, "wdt: clk_id %d, clk_rate %lu (prescale)\n",
		pic32_wdt_get_clk_id(wdt), rate);

	/* शेष, prescaler of 32 (i.e. भाग-by-32) is implicit. */
	rate >>= 5;
	अगर (!rate)
		वापस 0;

	/* calculate terminal count from postscaler. */
	ps = pic32_wdt_get_post_scaler(wdt);
	terminal = BIT(ps);

	/* find समय taken (in secs) to reach terminal count */
	period = terminal / rate;
	dev_dbg(dev,
		"wdt: clk_rate %lu (postscale) / terminal %d, timeout %dsec\n",
		rate, terminal, period);

	वापस period;
पूर्ण

अटल व्योम pic32_wdt_keepalive(काष्ठा pic32_wdt *wdt)
अणु
	/* ग_लिखो key through single half-word */
	ग_लिखोw(WDTCON_CLR_KEY, wdt->regs + WDTCON_REG + 2);
पूर्ण

अटल पूर्णांक pic32_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pic32_wdt *wdt = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(WDTCON_ON, PIC32_SET(wdt->regs + WDTCON_REG));
	pic32_wdt_keepalive(wdt);

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pic32_wdt *wdt = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(WDTCON_ON, PIC32_CLR(wdt->regs + WDTCON_REG));

	/*
	 * Cannot touch रेजिस्टरs in the CPU cycle following clearing the
	 * ON bit.
	 */
	nop();

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pic32_wdt *wdt = watchकरोg_get_drvdata(wdd);

	pic32_wdt_keepalive(wdt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops pic32_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.start		= pic32_wdt_start,
	.stop		= pic32_wdt_stop,
	.ping		= pic32_wdt_ping,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info pic32_wdt_ident = अणु
	.options = WDIOF_KEEPALIVEPING |
			WDIOF_MAGICCLOSE | WDIOF_CARDRESET,
	.identity = "PIC32 Watchdog",
पूर्ण;

अटल काष्ठा watchकरोg_device pic32_wdd = अणु
	.info		= &pic32_wdt_ident,
	.ops		= &pic32_wdt_fops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pic32_wdt_dt_ids[] = अणु
	अणु .compatible = "microchip,pic32mzda-wdt", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_wdt_dt_ids);

अटल व्योम pic32_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक pic32_wdt_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	काष्ठा watchकरोg_device *wdd = &pic32_wdd;
	काष्ठा pic32_wdt *wdt;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->regs))
		वापस PTR_ERR(wdt->regs);

	wdt->rst_base = devm_ioremap(dev, PIC32_BASE_RESET, 0x10);
	अगर (!wdt->rst_base)
		वापस -ENOMEM;

	wdt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(wdt->clk)) अणु
		dev_err(dev, "clk not found\n");
		वापस PTR_ERR(wdt->clk);
	पूर्ण

	ret = clk_prepare_enable(wdt->clk);
	अगर (ret) अणु
		dev_err(dev, "clk enable failed\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, pic32_clk_disable_unprepare,
				       wdt->clk);
	अगर (ret)
		वापस ret;

	अगर (pic32_wdt_is_win_enabled(wdt)) अणु
		dev_err(dev, "windowed-clear mode is not supported.\n");
		वापस -ENODEV;
	पूर्ण

	wdd->समयout = pic32_wdt_get_समयout_secs(wdt, dev);
	अगर (!wdd->समयout) अणु
		dev_err(dev, "failed to read watchdog register timeout\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(dev, "timeout %d\n", wdd->समयout);

	wdd->bootstatus = pic32_wdt_bootstatus(wdt) ? WDIOF_CARDRESET : 0;

	watchकरोg_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchकरोg_set_drvdata(wdd, wdt);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pic32_wdt_driver = अणु
	.probe		= pic32_wdt_drv_probe,
	.driver		= अणु
		.name		= "pic32-wdt",
		.of_match_table = of_match_ptr(pic32_wdt_dt_ids),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(pic32_wdt_driver);

MODULE_AUTHOR("Joshua Henderson <joshua.henderson@microchip.com>");
MODULE_DESCRIPTION("Microchip PIC32 Watchdog Timer");
MODULE_LICENSE("GPL");
