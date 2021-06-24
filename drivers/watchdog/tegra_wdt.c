<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

/* minimum and maximum watchकरोg trigger समयout, in seconds */
#घोषणा MIN_WDT_TIMEOUT			1
#घोषणा MAX_WDT_TIMEOUT			255

/*
 * Base of the WDT रेजिस्टरs, from the समयr base address.  There are
 * actually 5 watchकरोgs that can be configured (by pairing with an available
 * समयr), at bases 0x100 + (WDT ID) * 0x20, where WDT ID is 0 through 4.
 * This driver only configures the first watchकरोg (WDT ID 0).
 */
#घोषणा WDT_BASE			0x100
#घोषणा WDT_ID				0

/*
 * Register base of the समयr that's selected क्रम pairing with the watchकरोg.
 * This driver arbitrarily uses समयr 5, which is currently unused by
 * other drivers (in particular, the Tegra घड़ीsource driver).  If this
 * needs to change, take care that the new समयr is not used by the
 * घड़ीsource driver.
 */
#घोषणा WDT_TIMER_BASE			0x60
#घोषणा WDT_TIMER_ID			5

/* WDT रेजिस्टरs */
#घोषणा WDT_CFG				0x0
#घोषणा WDT_CFG_PERIOD_SHIFT		4
#घोषणा WDT_CFG_PERIOD_MASK		0xff
#घोषणा WDT_CFG_INT_EN			(1 << 12)
#घोषणा WDT_CFG_PMC2CAR_RST_EN		(1 << 15)
#घोषणा WDT_STS				0x4
#घोषणा WDT_STS_COUNT_SHIFT		4
#घोषणा WDT_STS_COUNT_MASK		0xff
#घोषणा WDT_STS_EXP_SHIFT		12
#घोषणा WDT_STS_EXP_MASK		0x3
#घोषणा WDT_CMD				0x8
#घोषणा WDT_CMD_START_COUNTER		(1 << 0)
#घोषणा WDT_CMD_DISABLE_COUNTER		(1 << 1)
#घोषणा WDT_UNLOCK			(0xc)
#घोषणा WDT_UNLOCK_PATTERN		(0xc45a << 0)

/* Timer रेजिस्टरs */
#घोषणा TIMER_PTV			0x0
#घोषणा TIMER_EN			(1 << 31)
#घोषणा TIMER_PERIODIC			(1 << 30)

काष्ठा tegra_wdt अणु
	काष्ठा watchकरोg_device	wdd;
	व्योम __iomem		*wdt_regs;
	व्योम __iomem		*पंचांगr_regs;
पूर्ण;

#घोषणा WDT_HEARTBEAT 120
अटल पूर्णांक heartbeat = WDT_HEARTBEAT;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
	"Watchdog heartbeats in seconds. (default = "
	__MODULE_STRING(WDT_HEARTBEAT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक tegra_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा tegra_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u32 val;

	/*
	 * This thing has a fixed 1MHz घड़ी.  Normally, we would set the
	 * period to 1 second by writing 1000000ul, but the watchकरोg प्रणाली
	 * reset actually occurs on the 4th expiration of this counter,
	 * so we set the period to 1/4 of this amount.
	 */
	val = 1000000ul / 4;
	val |= (TIMER_EN | TIMER_PERIODIC);
	ग_लिखोl(val, wdt->पंचांगr_regs + TIMER_PTV);

	/*
	 * Set number of periods and start counter.
	 *
	 * Interrupt handler is not required क्रम user space
	 * WDT accesses, since the caller is responsible to ping the
	 * WDT to reset the counter beक्रमe expiration, through ioctls.
	 */
	val = WDT_TIMER_ID |
	      (wdd->समयout << WDT_CFG_PERIOD_SHIFT) |
	      WDT_CFG_PMC2CAR_RST_EN;
	ग_लिखोl(val, wdt->wdt_regs + WDT_CFG);

	ग_लिखोl(WDT_CMD_START_COUNTER, wdt->wdt_regs + WDT_CMD);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा tegra_wdt *wdt = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(WDT_UNLOCK_PATTERN, wdt->wdt_regs + WDT_UNLOCK);
	ग_लिखोl(WDT_CMD_DISABLE_COUNTER, wdt->wdt_regs + WDT_CMD);
	ग_लिखोl(0, wdt->पंचांगr_regs + TIMER_PTV);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा tegra_wdt *wdt = watchकरोg_get_drvdata(wdd);

	ग_लिखोl(WDT_CMD_START_COUNTER, wdt->wdt_regs + WDT_CMD);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				 अचिन्हित पूर्णांक समयout)
अणु
	wdd->समयout = समयout;

	अगर (watchकरोg_active(wdd)) अणु
		tegra_wdt_stop(wdd);
		वापस tegra_wdt_start(wdd);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक tegra_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा tegra_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u32 val;
	पूर्णांक count;
	पूर्णांक exp;

	val = पढ़ोl(wdt->wdt_regs + WDT_STS);

	/* Current countकरोwn (from समयout) */
	count = (val >> WDT_STS_COUNT_SHIFT) & WDT_STS_COUNT_MASK;

	/* Number of expirations (we are रुकोing क्रम the 4th expiration) */
	exp = (val >> WDT_STS_EXP_SHIFT) & WDT_STS_EXP_MASK;

	/*
	 * The entire thing is भागided by 4 because we are ticking करोwn 4 बार
	 * faster due to needing to रुको क्रम the 4th expiration.
	 */
	वापस (((3 - exp) * wdd->समयout) + count) / 4;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info tegra_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_MAGICCLOSE |
			  WDIOF_KEEPALIVEPING,
	.firmware_version = 0,
	.identity	= "Tegra Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops tegra_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = tegra_wdt_start,
	.stop = tegra_wdt_stop,
	.ping = tegra_wdt_ping,
	.set_समयout = tegra_wdt_set_समयout,
	.get_समयleft = tegra_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक tegra_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा tegra_wdt *wdt;
	व्योम __iomem *regs;
	पूर्णांक ret;

	/* This is the समयr base. */
	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	/*
	 * Allocate our watchकरोg driver data, which has the
	 * काष्ठा watchकरोg_device nested within it.
	 */
	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	/* Initialize काष्ठा tegra_wdt. */
	wdt->wdt_regs = regs + WDT_BASE;
	wdt->पंचांगr_regs = regs + WDT_TIMER_BASE;

	/* Initialize काष्ठा watchकरोg_device. */
	wdd = &wdt->wdd;
	wdd->समयout = heartbeat;
	wdd->info = &tegra_wdt_info;
	wdd->ops = &tegra_wdt_ops;
	wdd->min_समयout = MIN_WDT_TIMEOUT;
	wdd->max_समयout = MAX_WDT_TIMEOUT;
	wdd->parent = dev;

	watchकरोg_set_drvdata(wdd, wdt);

	watchकरोg_set_nowayout(wdd, nowayout);

	watchकरोg_stop_on_unरेजिस्टर(wdd);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, wdt);

	dev_info(dev, "initialized (heartbeat = %d sec, nowayout = %d)\n",
		 heartbeat, nowayout);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_wdt_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		tegra_wdt_stop(&wdt->wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_wdt_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		tegra_wdt_start(&wdt->wdd);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id tegra_wdt_of_match[] = अणु
	अणु .compatible = "nvidia,tegra30-timer", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_wdt_of_match);

अटल स्थिर काष्ठा dev_pm_ops tegra_wdt_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tegra_wdt_runसमय_suspend,
				tegra_wdt_runसमय_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_wdt_driver = अणु
	.probe		= tegra_wdt_probe,
	.driver		= अणु
		.name	= "tegra-wdt",
		.pm	= &tegra_wdt_pm_ops,
		.of_match_table = tegra_wdt_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_wdt_driver);

MODULE_AUTHOR("NVIDIA Corporation");
MODULE_DESCRIPTION("Tegra Watchdog Driver");
MODULE_LICENSE("GPL v2");
