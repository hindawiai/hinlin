<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SBSA(Server Base System Architecture) Generic Watchकरोg driver
 *
 * Copyright (c) 2015, Linaro Ltd.
 * Author: Fu Wei <fu.wei@linaro.org>
 *         Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
 *         Al Stone <al.stone@linaro.org>
 *         Timur Tabi <timur@codeaurora.org>
 *
 * ARM SBSA Generic Watchकरोg has two stage समयouts:
 * the first संकेत (WS0) is क्रम alerting the प्रणाली by पूर्णांकerrupt,
 * the second one (WS1) is a real hardware reset.
 * More details about the hardware specअगरication of this device:
 * ARM DEN0029B - Server Base System Architecture (SBSA)
 *
 * This driver can operate ARM SBSA Generic Watchकरोg as a single stage watchकरोg
 * or a two stages watchकरोg, it's set up by the module parameter "action".
 * In the single stage mode, when the समयout is reached, your प्रणाली
 * will be reset by WS1. The first संकेत (WS0) is ignored.
 * In the two stages mode, when the समयout is reached, the first संकेत (WS0)
 * will trigger panic. If the प्रणाली is getting पूर्णांकo trouble and cannot be reset
 * by panic or restart properly by the kdump kernel(अगर supported), then the
 * second stage (as दीर्घ as the first stage) will be reached, प्रणाली will be
 * reset by WS1. This function can help administrator to backup the प्रणाली
 * context info by panic console output or kdump.
 *
 * SBSA GWDT:
 * अगर action is 1 (the two stages mode):
 * |--------WOR-------WS0--------WOR-------WS1
 * |----समयout-----(panic)----समयout-----reset
 *
 * अगर action is 0 (the single stage mode):
 * |------WOR-----WS0(ignored)-----WOR------WS1
 * |--------------समयout-------------------reset
 *
 * Note: Since this watchकरोg समयr has two stages, and each stage is determined
 * by WOR, in the single stage mode, the समयout is (WOR * 2); in the two
 * stages mode, the समयout is WOR. The maximum समयout in the two stages mode
 * is half of that in the single stage mode.
 */

#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/watchकरोg.h>
#समावेश <यंत्र/arch_समयr.h>

#घोषणा DRV_NAME		"sbsa-gwdt"
#घोषणा WATCHDOG_NAME		"SBSA Generic Watchdog"

/* SBSA Generic Watchकरोg रेजिस्टर definitions */
/* refresh frame */
#घोषणा SBSA_GWDT_WRR		0x000

/* control frame */
#घोषणा SBSA_GWDT_WCS		0x000
#घोषणा SBSA_GWDT_WOR		0x008
#घोषणा SBSA_GWDT_WCV		0x010

/* refresh/control frame */
#घोषणा SBSA_GWDT_W_IIDR	0xfcc
#घोषणा SBSA_GWDT_IDR		0xfd0

/* Watchकरोg Control and Status Register */
#घोषणा SBSA_GWDT_WCS_EN	BIT(0)
#घोषणा SBSA_GWDT_WCS_WS0	BIT(1)
#घोषणा SBSA_GWDT_WCS_WS1	BIT(2)

/**
 * काष्ठा sbsa_gwdt - Internal representation of the SBSA GWDT
 * @wdd:		kernel watchकरोg_device काष्ठाure
 * @clk:		store the System Counter घड़ी frequency, in Hz.
 * @refresh_base:	Virtual address of the watchकरोg refresh frame
 * @control_base:	Virtual address of the watchकरोg control frame
 */
काष्ठा sbsa_gwdt अणु
	काष्ठा watchकरोg_device	wdd;
	u32			clk;
	व्योम __iomem		*refresh_base;
	व्योम __iomem		*control_base;
पूर्ण;

#घोषणा DEFAULT_TIMEOUT		10 /* seconds */

अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		 "Watchdog timeout in seconds. (>=0, default="
		 __MODULE_STRING(DEFAULT_TIMEOUT) ")");

/*
 * action refers to action taken when watchकरोg माला_लो WS0
 * 0 = skip
 * 1 = panic
 * शेषs to skip (0)
 */
अटल पूर्णांक action;
module_param(action, पूर्णांक, 0);
MODULE_PARM_DESC(action, "after watchdog gets WS0 interrupt, do: "
		 "0 = skip(*)  1 = panic");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, S_IRUGO);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 * watchकरोg operation functions
 */
अटल पूर्णांक sbsa_gwdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				 अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा sbsa_gwdt *gwdt = watchकरोg_get_drvdata(wdd);

	wdd->समयout = समयout;

	अगर (action)
		ग_लिखोl(gwdt->clk * समयout,
		       gwdt->control_base + SBSA_GWDT_WOR);
	अन्यथा
		/*
		 * In the single stage mode, The first संकेत (WS0) is ignored,
		 * the समयout is (WOR * 2), so the WOR should be configured
		 * to half value of समयout.
		 */
		ग_लिखोl(gwdt->clk / 2 * समयout,
		       gwdt->control_base + SBSA_GWDT_WOR);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sbsa_gwdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sbsa_gwdt *gwdt = watchकरोg_get_drvdata(wdd);
	u64 समयleft = 0;

	/*
	 * In the single stage mode, अगर WS0 is deनिश्चितed
	 * (watchकरोg is in the first stage),
	 * समयleft = WOR + (WCV - प्रणाली counter)
	 */
	अगर (!action &&
	    !(पढ़ोl(gwdt->control_base + SBSA_GWDT_WCS) & SBSA_GWDT_WCS_WS0))
		समयleft += पढ़ोl(gwdt->control_base + SBSA_GWDT_WOR);

	समयleft += lo_hi_पढ़ोq(gwdt->control_base + SBSA_GWDT_WCV) -
		    arch_समयr_पढ़ो_counter();

	करो_भाग(समयleft, gwdt->clk);

	वापस समयleft;
पूर्ण

अटल पूर्णांक sbsa_gwdt_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sbsa_gwdt *gwdt = watchकरोg_get_drvdata(wdd);

	/*
	 * Writing WRR क्रम an explicit watchकरोg refresh.
	 * You can ग_लिखो anyting (like 0).
	 */
	ग_लिखोl(0, gwdt->refresh_base + SBSA_GWDT_WRR);

	वापस 0;
पूर्ण

अटल पूर्णांक sbsa_gwdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sbsa_gwdt *gwdt = watchकरोg_get_drvdata(wdd);

	/* writing WCS will cause an explicit watchकरोg refresh */
	ग_लिखोl(SBSA_GWDT_WCS_EN, gwdt->control_base + SBSA_GWDT_WCS);

	वापस 0;
पूर्ण

अटल पूर्णांक sbsa_gwdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sbsa_gwdt *gwdt = watchकरोg_get_drvdata(wdd);

	/* Simply ग_लिखो 0 to WCS to clean WCS_EN bit */
	ग_लिखोl(0, gwdt->control_base + SBSA_GWDT_WCS);

	वापस 0;
पूर्ण

अटल irqवापस_t sbsa_gwdt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	panic(WATCHDOG_NAME " timeout");

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sbsa_gwdt_info = अणु
	.identity	= WATCHDOG_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE |
			  WDIOF_CARDRESET,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops sbsa_gwdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= sbsa_gwdt_start,
	.stop		= sbsa_gwdt_stop,
	.ping		= sbsa_gwdt_keepalive,
	.set_समयout	= sbsa_gwdt_set_समयout,
	.get_समयleft	= sbsa_gwdt_get_समयleft,
पूर्ण;

अटल पूर्णांक sbsa_gwdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *rf_base, *cf_base;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा sbsa_gwdt *gwdt;
	पूर्णांक ret, irq;
	u32 status;

	gwdt = devm_kzalloc(dev, माप(*gwdt), GFP_KERNEL);
	अगर (!gwdt)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, gwdt);

	cf_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cf_base))
		वापस PTR_ERR(cf_base);

	rf_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(rf_base))
		वापस PTR_ERR(rf_base);

	/*
	 * Get the frequency of प्रणाली counter from the cp15 पूर्णांकerface of ARM
	 * Generic समयr. We करोn't need to check it, because अगर it वापसs "0",
	 * प्रणाली would panic in very early stage.
	 */
	gwdt->clk = arch_समयr_get_cntfrq();
	gwdt->refresh_base = rf_base;
	gwdt->control_base = cf_base;

	wdd = &gwdt->wdd;
	wdd->parent = dev;
	wdd->info = &sbsa_gwdt_info;
	wdd->ops = &sbsa_gwdt_ops;
	wdd->min_समयout = 1;
	wdd->max_hw_heartbeat_ms = U32_MAX / gwdt->clk * 1000;
	wdd->समयout = DEFAULT_TIMEOUT;
	watchकरोg_set_drvdata(wdd, gwdt);
	watchकरोg_set_nowayout(wdd, nowayout);

	status = पढ़ोl(cf_base + SBSA_GWDT_WCS);
	अगर (status & SBSA_GWDT_WCS_WS1) अणु
		dev_warn(dev, "System reset by WDT.\n");
		wdd->bootstatus |= WDIOF_CARDRESET;
	पूर्ण
	अगर (status & SBSA_GWDT_WCS_EN)
		set_bit(WDOG_HW_RUNNING, &wdd->status);

	अगर (action) अणु
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0) अणु
			action = 0;
			dev_warn(dev, "unable to get ws0 interrupt.\n");
		पूर्ण अन्यथा अणु
			/*
			 * In हाल there is a pending ws0 पूर्णांकerrupt, just ping
			 * the watchकरोg beक्रमe रेजिस्टरing the पूर्णांकerrupt routine
			 */
			ग_लिखोl(0, rf_base + SBSA_GWDT_WRR);
			अगर (devm_request_irq(dev, irq, sbsa_gwdt_पूर्णांकerrupt, 0,
					     pdev->name, gwdt)) अणु
				action = 0;
				dev_warn(dev, "unable to request IRQ %d.\n",
					 irq);
			पूर्ण
		पूर्ण
		अगर (!action)
			dev_warn(dev, "falling back to single stage mode.\n");
	पूर्ण
	/*
	 * In the single stage mode, The first संकेत (WS0) is ignored,
	 * the समयout is (WOR * 2), so the maximum समयout should be द्विगुनd.
	 */
	अगर (!action)
		wdd->max_hw_heartbeat_ms *= 2;

	watchकरोg_init_समयout(wdd, समयout, dev);
	/*
	 * Update समयout to WOR.
	 * Because of the explicit watchकरोg refresh mechanism,
	 * it's also a ping, अगर watchकरोg is enabled.
	 */
	sbsa_gwdt_set_समयout(wdd, wdd->समयout);

	watchकरोg_stop_on_reboot(wdd);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, wdd);
	अगर (ret)
		वापस ret;

	dev_info(dev, "Initialized with %ds timeout @ %u Hz, action=%d.%s\n",
		 wdd->समयout, gwdt->clk, action,
		 status & SBSA_GWDT_WCS_EN ? " [enabled]" : "");

	वापस 0;
पूर्ण

/* Disable watchकरोg अगर it is active during suspend */
अटल पूर्णांक __maybe_unused sbsa_gwdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा sbsa_gwdt *gwdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&gwdt->wdd))
		sbsa_gwdt_stop(&gwdt->wdd);

	वापस 0;
पूर्ण

/* Enable watchकरोg अगर necessary */
अटल पूर्णांक __maybe_unused sbsa_gwdt_resume(काष्ठा device *dev)
अणु
	काष्ठा sbsa_gwdt *gwdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&gwdt->wdd))
		sbsa_gwdt_start(&gwdt->wdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sbsa_gwdt_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sbsa_gwdt_suspend, sbsa_gwdt_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sbsa_gwdt_of_match[] = अणु
	अणु .compatible = "arm,sbsa-gwdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sbsa_gwdt_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id sbsa_gwdt_pdev_match[] = अणु
	अणु .name = DRV_NAME, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sbsa_gwdt_pdev_match);

अटल काष्ठा platक्रमm_driver sbsa_gwdt_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &sbsa_gwdt_pm_ops,
		.of_match_table = sbsa_gwdt_of_match,
	पूर्ण,
	.probe = sbsa_gwdt_probe,
	.id_table = sbsa_gwdt_pdev_match,
पूर्ण;

module_platक्रमm_driver(sbsa_gwdt_driver);

MODULE_DESCRIPTION("SBSA Generic Watchdog Driver");
MODULE_AUTHOR("Fu Wei <fu.wei@linaro.org>");
MODULE_AUTHOR("Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>");
MODULE_AUTHOR("Al Stone <al.stone@linaro.org>");
MODULE_AUTHOR("Timur Tabi <timur@codeaurora.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
