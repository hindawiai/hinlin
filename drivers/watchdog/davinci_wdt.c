<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/अक्षर/watchकरोg/davinci_wdt.c
 *
 * Watchकरोg driver क्रम DaVinci DM644x/DM646x processors
 *
 * Copyright (C) 2006-2013 Texas Instruments.
 *
 * 2007 (c) MontaVista Software, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

#घोषणा MODULE_NAME "DAVINCI-WDT: "

#घोषणा DEFAULT_HEARTBEAT 60
#घोषणा MAX_HEARTBEAT     600	/* really the max margin is 264/27MHz*/

/* Timer रेजिस्टर set definition */
#घोषणा PID12	(0x0)
#घोषणा EMUMGT	(0x4)
#घोषणा TIM12	(0x10)
#घोषणा TIM34	(0x14)
#घोषणा PRD12	(0x18)
#घोषणा PRD34	(0x1C)
#घोषणा TCR	(0x20)
#घोषणा TGCR	(0x24)
#घोषणा WDTCR	(0x28)

/* TCR bit definitions */
#घोषणा ENAMODE12_DISABLED	(0 << 6)
#घोषणा ENAMODE12_ONESHOT	(1 << 6)
#घोषणा ENAMODE12_PERIODIC	(2 << 6)

/* TGCR bit definitions */
#घोषणा TIM12RS_UNRESET		(1 << 0)
#घोषणा TIM34RS_UNRESET		(1 << 1)
#घोषणा TIMMODE_64BIT_WDOG      (2 << 2)

/* WDTCR bit definitions */
#घोषणा WDEN			(1 << 14)
#घोषणा WDFLAG			(1 << 15)
#घोषणा WDKEY_SEQ0		(0xa5c6 << 16)
#घोषणा WDKEY_SEQ1		(0xda7e << 16)

अटल पूर्णांक heartbeat;

/*
 * काष्ठा to hold data क्रम each WDT device
 * @base - base io address of WD device
 * @clk - source घड़ी of WDT
 * @wdd - hold watchकरोg device as is in WDT core
 */
काष्ठा davinci_wdt_device अणु
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा watchकरोg_device	wdd;
पूर्ण;

अटल पूर्णांक davinci_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	u32 tgcr;
	u32 समयr_margin;
	अचिन्हित दीर्घ wdt_freq;
	काष्ठा davinci_wdt_device *davinci_wdt = watchकरोg_get_drvdata(wdd);

	wdt_freq = clk_get_rate(davinci_wdt->clk);

	/* disable, पूर्णांकernal घड़ी source */
	ioग_लिखो32(0, davinci_wdt->base + TCR);
	/* reset समयr, set mode to 64-bit watchकरोg, and unreset */
	ioग_लिखो32(0, davinci_wdt->base + TGCR);
	tgcr = TIMMODE_64BIT_WDOG | TIM12RS_UNRESET | TIM34RS_UNRESET;
	ioग_लिखो32(tgcr, davinci_wdt->base + TGCR);
	/* clear counter regs */
	ioग_लिखो32(0, davinci_wdt->base + TIM12);
	ioग_लिखो32(0, davinci_wdt->base + TIM34);
	/* set समयout period */
	समयr_margin = (((u64)wdd->समयout * wdt_freq) & 0xffffffff);
	ioग_लिखो32(समयr_margin, davinci_wdt->base + PRD12);
	समयr_margin = (((u64)wdd->समयout * wdt_freq) >> 32);
	ioग_लिखो32(समयr_margin, davinci_wdt->base + PRD34);
	/* enable run continuously */
	ioग_लिखो32(ENAMODE12_PERIODIC, davinci_wdt->base + TCR);
	/* Once the WDT is in pre-active state ग_लिखो to
	 * TIM12, TIM34, PRD12, PRD34, TCR, TGCR, WDTCR are
	 * ग_लिखो रक्षित (except क्रम the WDKEY field)
	 */
	/* put watchकरोg in pre-active state */
	ioग_लिखो32(WDKEY_SEQ0 | WDEN, davinci_wdt->base + WDTCR);
	/* put watchकरोg in active state */
	ioग_लिखो32(WDKEY_SEQ1 | WDEN, davinci_wdt->base + WDTCR);
	वापस 0;
पूर्ण

अटल पूर्णांक davinci_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा davinci_wdt_device *davinci_wdt = watchकरोg_get_drvdata(wdd);

	/* put watchकरोg in service state */
	ioग_लिखो32(WDKEY_SEQ0, davinci_wdt->base + WDTCR);
	/* put watchकरोg in active state */
	ioग_लिखो32(WDKEY_SEQ1, davinci_wdt->base + WDTCR);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक davinci_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	u64 समयr_counter;
	अचिन्हित दीर्घ freq;
	u32 val;
	काष्ठा davinci_wdt_device *davinci_wdt = watchकरोg_get_drvdata(wdd);

	/* अगर समयout has occured then वापस 0 */
	val = ioपढ़ो32(davinci_wdt->base + WDTCR);
	अगर (val & WDFLAG)
		वापस 0;

	freq = clk_get_rate(davinci_wdt->clk);

	अगर (!freq)
		वापस 0;

	समयr_counter = ioपढ़ो32(davinci_wdt->base + TIM12);
	समयr_counter |= ((u64)ioपढ़ो32(davinci_wdt->base + TIM34) << 32);

	करो_भाग(समयr_counter, freq);

	वापस wdd->समयout - समयr_counter;
पूर्ण

अटल पूर्णांक davinci_wdt_restart(काष्ठा watchकरोg_device *wdd,
			       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा davinci_wdt_device *davinci_wdt = watchकरोg_get_drvdata(wdd);
	u32 tgcr, wdtcr;

	/* disable, पूर्णांकernal घड़ी source */
	ioग_लिखो32(0, davinci_wdt->base + TCR);

	/* reset समयr, set mode to 64-bit watchकरोg, and unreset */
	tgcr = 0;
	ioग_लिखो32(tgcr, davinci_wdt->base + TGCR);
	tgcr = TIMMODE_64BIT_WDOG | TIM12RS_UNRESET | TIM34RS_UNRESET;
	ioग_लिखो32(tgcr, davinci_wdt->base + TGCR);

	/* clear counter and period regs */
	ioग_लिखो32(0, davinci_wdt->base + TIM12);
	ioग_लिखो32(0, davinci_wdt->base + TIM34);
	ioग_लिखो32(0, davinci_wdt->base + PRD12);
	ioग_लिखो32(0, davinci_wdt->base + PRD34);

	/* put watchकरोg in pre-active state */
	wdtcr = WDKEY_SEQ0 | WDEN;
	ioग_लिखो32(wdtcr, davinci_wdt->base + WDTCR);

	/* put watchकरोg in active state */
	wdtcr = WDKEY_SEQ1 | WDEN;
	ioग_लिखो32(wdtcr, davinci_wdt->base + WDTCR);

	/* ग_लिखो an invalid value to the WDKEY field to trigger a restart */
	wdtcr = 0x00004000;
	ioग_लिखो32(wdtcr, davinci_wdt->base + WDTCR);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info davinci_wdt_info = अणु
	.options = WDIOF_KEEPALIVEPING,
	.identity = "DaVinci/Keystone Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops davinci_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= davinci_wdt_start,
	.stop		= davinci_wdt_ping,
	.ping		= davinci_wdt_ping,
	.get_समयleft	= davinci_wdt_get_समयleft,
	.restart	= davinci_wdt_restart,
पूर्ण;

अटल व्योम davinci_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक davinci_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा davinci_wdt_device *davinci_wdt;

	davinci_wdt = devm_kzalloc(dev, माप(*davinci_wdt), GFP_KERNEL);
	अगर (!davinci_wdt)
		वापस -ENOMEM;

	davinci_wdt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(davinci_wdt->clk))
		वापस dev_err_probe(dev, PTR_ERR(davinci_wdt->clk),
				     "failed to get clock node\n");

	ret = clk_prepare_enable(davinci_wdt->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, davinci_clk_disable_unprepare,
				       davinci_wdt->clk);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, davinci_wdt);

	wdd			= &davinci_wdt->wdd;
	wdd->info		= &davinci_wdt_info;
	wdd->ops		= &davinci_wdt_ops;
	wdd->min_समयout	= 1;
	wdd->max_समयout	= MAX_HEARTBEAT;
	wdd->समयout		= DEFAULT_HEARTBEAT;
	wdd->parent		= dev;

	watchकरोg_init_समयout(wdd, heartbeat, dev);

	dev_info(dev, "heartbeat %d sec\n", wdd->समयout);

	watchकरोg_set_drvdata(wdd, davinci_wdt);
	watchकरोg_set_nowayout(wdd, 1);
	watchकरोg_set_restart_priority(wdd, 128);

	davinci_wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(davinci_wdt->base))
		वापस PTR_ERR(davinci_wdt->base);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wdd);
पूर्ण

अटल स्थिर काष्ठा of_device_id davinci_wdt_of_match[] = अणु
	अणु .compatible = "ti,davinci-wdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_wdt_of_match);

अटल काष्ठा platक्रमm_driver platक्रमm_wdt_driver = अणु
	.driver = अणु
		.name = "davinci-wdt",
		.of_match_table = davinci_wdt_of_match,
	पूर्ण,
	.probe = davinci_wdt_probe,
पूर्ण;

module_platक्रमm_driver(platक्रमm_wdt_driver);

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("DaVinci Watchdog Driver");

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
		 "Watchdog heartbeat period in seconds from 1 to "
		 __MODULE_STRING(MAX_HEARTBEAT) ", default "
		 __MODULE_STRING(DEFAULT_HEARTBEAT));

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:davinci-wdt");
