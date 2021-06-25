<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg driver क्रम IMX2 and later processors
 *
 *  Copyright (C) 2010 Wolfram Sang, Pengutronix e.K. <kernel@pengutronix.de>
 *  Copyright (C) 2014 Freescale Semiconductor, Inc.
 *
 * some parts adapted by similar drivers from Darius Augulis and Vladimir
 * Zapolskiy, additional improvements by Wim Van Sebroeck.
 *
 * NOTE: MX1 has a slightly dअगरferent Watchकरोg than MX2 and later:
 *
 *			MX1:		MX2+:
 *			----		-----
 * Registers:		32-bit		16-bit
 * Stopable समयr:	Yes		No
 * Need to enable clk:	No		Yes
 * Halt on suspend:	Manual		Can be स्वतःmatic
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DRIVER_NAME "imx2-wdt"

#घोषणा IMX2_WDT_WCR		0x00		/* Control Register */
#घोषणा IMX2_WDT_WCR_WT		(0xFF << 8)	/* -> Watchकरोg Timeout Field */
#घोषणा IMX2_WDT_WCR_WDA	BIT(5)		/* -> External Reset WDOG_B */
#घोषणा IMX2_WDT_WCR_SRS	BIT(4)		/* -> Software Reset Signal */
#घोषणा IMX2_WDT_WCR_WRE	BIT(3)		/* -> WDOG Reset Enable */
#घोषणा IMX2_WDT_WCR_WDE	BIT(2)		/* -> Watchकरोg Enable */
#घोषणा IMX2_WDT_WCR_WDZST	BIT(0)		/* -> Watchकरोg समयr Suspend */

#घोषणा IMX2_WDT_WSR		0x02		/* Service Register */
#घोषणा IMX2_WDT_SEQ1		0x5555		/* -> service sequence 1 */
#घोषणा IMX2_WDT_SEQ2		0xAAAA		/* -> service sequence 2 */

#घोषणा IMX2_WDT_WRSR		0x04		/* Reset Status Register */
#घोषणा IMX2_WDT_WRSR_TOUT	BIT(1)		/* -> Reset due to Timeout */

#घोषणा IMX2_WDT_WICR		0x06		/* Interrupt Control Register */
#घोषणा IMX2_WDT_WICR_WIE	BIT(15)		/* -> Interrupt Enable */
#घोषणा IMX2_WDT_WICR_WTIS	BIT(14)		/* -> Interrupt Status */
#घोषणा IMX2_WDT_WICR_WICT	0xFF		/* -> Interrupt Count Timeout */

#घोषणा IMX2_WDT_WMCR		0x08		/* Misc Register */

#घोषणा IMX2_WDT_MAX_TIME	128U
#घोषणा IMX2_WDT_DEFAULT_TIME	60		/* in seconds */

#घोषणा WDOG_SEC_TO_COUNT(s)	((s * 2 - 1) << 8)

काष्ठा imx2_wdt_device अणु
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	काष्ठा watchकरोg_device wकरोg;
	bool ext_reset;
पूर्ण;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अचिन्हित समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds (default="
				__MODULE_STRING(IMX2_WDT_DEFAULT_TIME) ")");

अटल स्थिर काष्ठा watchकरोg_info imx2_wdt_info = अणु
	.identity = "imx2+ watchdog",
	.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info imx2_wdt_preसमयout_info = अणु
	.identity = "imx2+ watchdog",
	.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE |
		   WDIOF_PRETIMEOUT,
पूर्ण;

अटल पूर्णांक imx2_wdt_restart(काष्ठा watchकरोg_device *wकरोg, अचिन्हित दीर्घ action,
			    व्योम *data)
अणु
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);
	अचिन्हित पूर्णांक wcr_enable = IMX2_WDT_WCR_WDE;

	/* Use पूर्णांकernal reset or बाह्यal - not both */
	अगर (wdev->ext_reset)
		wcr_enable |= IMX2_WDT_WCR_SRS; /* करो not निश्चित पूर्णांक reset */
	अन्यथा
		wcr_enable |= IMX2_WDT_WCR_WDA; /* करो not निश्चित ext-reset */

	/* Assert SRS संकेत */
	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WCR, wcr_enable);
	/*
	 * Due to imx6q errata ERR004346 (WDOG: WDOG SRS bit requires to be
	 * written twice), we add another two ग_लिखोs to ensure there must be at
	 * least two ग_लिखोs happen in the same one 32kHz घड़ी period.  We save
	 * the target check here, since the ग_लिखोs shouldn't be a huge burden
	 * क्रम other platक्रमms.
	 */
	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WCR, wcr_enable);
	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WCR, wcr_enable);

	/* रुको क्रम reset to निश्चित... */
	mdelay(500);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम imx2_wdt_setup(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);
	u32 val;

	regmap_पढ़ो(wdev->regmap, IMX2_WDT_WCR, &val);

	/* Suspend समयr in low घातer mode, ग_लिखो once-only */
	val |= IMX2_WDT_WCR_WDZST;
	/* Strip the old watchकरोg Time-Out value */
	val &= ~IMX2_WDT_WCR_WT;
	/* Generate पूर्णांकernal chip-level reset अगर WDOG बार out */
	अगर (!wdev->ext_reset)
		val &= ~IMX2_WDT_WCR_WRE;
	/* Or अगर बाह्यal-reset निश्चित WDOG_B reset only on समय-out */
	अन्यथा
		val |= IMX2_WDT_WCR_WRE;
	/* Keep Watchकरोg Disabled */
	val &= ~IMX2_WDT_WCR_WDE;
	/* Set the watchकरोg's Time-Out value */
	val |= WDOG_SEC_TO_COUNT(wकरोg->समयout);

	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WCR, val);

	/* enable the watchकरोg */
	val |= IMX2_WDT_WCR_WDE;
	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WCR, val);
पूर्ण

अटल अंतरभूत bool imx2_wdt_is_running(काष्ठा imx2_wdt_device *wdev)
अणु
	u32 val;

	regmap_पढ़ो(wdev->regmap, IMX2_WDT_WCR, &val);

	वापस val & IMX2_WDT_WCR_WDE;
पूर्ण

अटल पूर्णांक imx2_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);

	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WSR, IMX2_WDT_SEQ1);
	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WSR, IMX2_WDT_SEQ2);
	वापस 0;
पूर्ण

अटल व्योम __imx2_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				   अचिन्हित पूर्णांक new_समयout)
अणु
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);

	regmap_update_bits(wdev->regmap, IMX2_WDT_WCR, IMX2_WDT_WCR_WT,
			   WDOG_SEC_TO_COUNT(new_समयout));
पूर्ण

अटल पूर्णांक imx2_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				अचिन्हित पूर्णांक new_समयout)
अणु
	अचिन्हित पूर्णांक actual;

	actual = min(new_समयout, IMX2_WDT_MAX_TIME);
	__imx2_wdt_set_समयout(wकरोg, actual);
	wकरोg->समयout = new_समयout;
	वापस 0;
पूर्ण

अटल पूर्णांक imx2_wdt_set_preसमयout(काष्ठा watchकरोg_device *wकरोg,
				   अचिन्हित पूर्णांक new_preसमयout)
अणु
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);

	अगर (new_preसमयout >= IMX2_WDT_MAX_TIME)
		वापस -EINVAL;

	wकरोg->preसमयout = new_preसमयout;

	regmap_update_bits(wdev->regmap, IMX2_WDT_WICR,
			   IMX2_WDT_WICR_WIE | IMX2_WDT_WICR_WICT,
			   IMX2_WDT_WICR_WIE | (new_preसमयout << 1));
	वापस 0;
पूर्ण

अटल irqवापस_t imx2_wdt_isr(पूर्णांक irq, व्योम *wकरोg_arg)
अणु
	काष्ठा watchकरोg_device *wकरोg = wकरोg_arg;
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);

	regmap_ग_लिखो_bits(wdev->regmap, IMX2_WDT_WICR,
			  IMX2_WDT_WICR_WTIS, IMX2_WDT_WICR_WTIS);

	watchकरोg_notअगरy_preसमयout(wकरोg);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक imx2_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);

	अगर (imx2_wdt_is_running(wdev))
		imx2_wdt_set_समयout(wकरोg, wकरोg->समयout);
	अन्यथा
		imx2_wdt_setup(wकरोg);

	set_bit(WDOG_HW_RUNNING, &wकरोg->status);

	वापस imx2_wdt_ping(wकरोg);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops imx2_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = imx2_wdt_start,
	.ping = imx2_wdt_ping,
	.set_समयout = imx2_wdt_set_समयout,
	.set_preसमयout = imx2_wdt_set_preसमयout,
	.restart = imx2_wdt_restart,
पूर्ण;

अटल स्थिर काष्ठा regmap_config imx2_wdt_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x8,
पूर्ण;

अटल व्योम imx2_wdt_action(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक __init imx2_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा imx2_wdt_device *wdev;
	काष्ठा watchकरोg_device *wकरोg;
	व्योम __iomem *base;
	पूर्णांक ret;
	u32 val;

	wdev = devm_kzalloc(dev, माप(*wdev), GFP_KERNEL);
	अगर (!wdev)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	wdev->regmap = devm_regmap_init_mmio_clk(dev, शून्य, base,
						 &imx2_wdt_regmap_config);
	अगर (IS_ERR(wdev->regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(wdev->regmap);
	पूर्ण

	wdev->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(wdev->clk)) अणु
		dev_err(dev, "can't get Watchdog clock\n");
		वापस PTR_ERR(wdev->clk);
	पूर्ण

	wकरोg			= &wdev->wकरोg;
	wकरोg->info		= &imx2_wdt_info;
	wकरोg->ops		= &imx2_wdt_ops;
	wकरोg->min_समयout	= 1;
	wकरोg->समयout		= IMX2_WDT_DEFAULT_TIME;
	wकरोg->max_hw_heartbeat_ms = IMX2_WDT_MAX_TIME * 1000;
	wकरोg->parent		= dev;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret > 0)
		अगर (!devm_request_irq(dev, ret, imx2_wdt_isr, 0,
				      dev_name(dev), wकरोg))
			wकरोg->info = &imx2_wdt_preसमयout_info;

	ret = clk_prepare_enable(wdev->clk);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, imx2_wdt_action, wdev->clk);
	अगर (ret)
		वापस ret;

	regmap_पढ़ो(wdev->regmap, IMX2_WDT_WRSR, &val);
	wकरोg->bootstatus = val & IMX2_WDT_WRSR_TOUT ? WDIOF_CARDRESET : 0;

	wdev->ext_reset = of_property_पढ़ो_bool(dev->of_node,
						"fsl,ext-reset-output");
	platक्रमm_set_drvdata(pdev, wकरोg);
	watchकरोg_set_drvdata(wकरोg, wdev);
	watchकरोg_set_nowayout(wकरोg, nowayout);
	watchकरोg_set_restart_priority(wकरोg, 128);
	watchकरोg_init_समयout(wकरोg, समयout, dev);

	अगर (imx2_wdt_is_running(wdev)) अणु
		imx2_wdt_set_समयout(wकरोg, wकरोg->समयout);
		set_bit(WDOG_HW_RUNNING, &wकरोg->status);
	पूर्ण

	/*
	 * Disable the watchकरोg घातer करोwn counter at boot. Otherwise the घातer
	 * करोwn counter will pull करोwn the #WDOG पूर्णांकerrupt line क्रम one घड़ी
	 * cycle.
	 */
	regmap_ग_लिखो(wdev->regmap, IMX2_WDT_WMCR, 0);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, wकरोg);
पूर्ण

अटल व्योम imx2_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा watchकरोg_device *wकरोg = platक्रमm_get_drvdata(pdev);
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);

	अगर (imx2_wdt_is_running(wdev)) अणु
		/*
		 * We are running, configure max समयout beक्रमe reboot
		 * will take place.
		 */
		imx2_wdt_set_समयout(wकरोg, IMX2_WDT_MAX_TIME);
		imx2_wdt_ping(wकरोg);
		dev_crit(&pdev->dev, "Device shutdown: Expect reboot!\n");
	पूर्ण
पूर्ण

/* Disable watchकरोg अगर it is active or non-active but still running */
अटल पूर्णांक __maybe_unused imx2_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wकरोg = dev_get_drvdata(dev);
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);

	/* The watchकरोg IP block is running */
	अगर (imx2_wdt_is_running(wdev)) अणु
		/*
		 * Don't update wdog->timeout, we'll restore the current value
		 * during resume.
		 */
		__imx2_wdt_set_समयout(wकरोg, IMX2_WDT_MAX_TIME);
		imx2_wdt_ping(wकरोg);
	पूर्ण

	clk_disable_unprepare(wdev->clk);

	वापस 0;
पूर्ण

/* Enable watchकरोg and configure it अगर necessary */
अटल पूर्णांक __maybe_unused imx2_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_device *wकरोg = dev_get_drvdata(dev);
	काष्ठा imx2_wdt_device *wdev = watchकरोg_get_drvdata(wकरोg);
	पूर्णांक ret;

	ret = clk_prepare_enable(wdev->clk);
	अगर (ret)
		वापस ret;

	अगर (watchकरोg_active(wकरोg) && !imx2_wdt_is_running(wdev)) अणु
		/*
		 * If the watchकरोg is still active and resumes
		 * from deep sleep state, need to restart the
		 * watchकरोg again.
		 */
		imx2_wdt_setup(wकरोg);
	पूर्ण
	अगर (imx2_wdt_is_running(wdev)) अणु
		imx2_wdt_set_समयout(wकरोg, wकरोg->समयout);
		imx2_wdt_ping(wकरोg);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx2_wdt_pm_ops, imx2_wdt_suspend,
			 imx2_wdt_resume);

अटल स्थिर काष्ठा of_device_id imx2_wdt_dt_ids[] = अणु
	अणु .compatible = "fsl,imx21-wdt", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx2_wdt_dt_ids);

अटल काष्ठा platक्रमm_driver imx2_wdt_driver = अणु
	.shutकरोwn	= imx2_wdt_shutकरोwn,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.pm     = &imx2_wdt_pm_ops,
		.of_match_table = imx2_wdt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(imx2_wdt_driver, imx2_wdt_probe);

MODULE_AUTHOR("Wolfram Sang");
MODULE_DESCRIPTION("Watchdog driver for IMX2 and later");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
