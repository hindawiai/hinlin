<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cadence WDT driver - Used by Xilinx Zynq
 *
 * Copyright (C) 2010 - 2014 Xilinx, Inc.
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>

#घोषणा CDNS_WDT_DEFAULT_TIMEOUT	10
/* Supports 1 - 516 sec */
#घोषणा CDNS_WDT_MIN_TIMEOUT	1
#घोषणा CDNS_WDT_MAX_TIMEOUT	516

/* Restart key */
#घोषणा CDNS_WDT_RESTART_KEY 0x00001999

/* Counter रेजिस्टर access key */
#घोषणा CDNS_WDT_REGISTER_ACCESS_KEY 0x00920000

/* Counter value भागisor */
#घोषणा CDNS_WDT_COUNTER_VALUE_DIVISOR 0x1000

/* Clock prescaler value and selection */
#घोषणा CDNS_WDT_PRESCALE_64	64
#घोषणा CDNS_WDT_PRESCALE_512	512
#घोषणा CDNS_WDT_PRESCALE_4096	4096
#घोषणा CDNS_WDT_PRESCALE_SELECT_64	1
#घोषणा CDNS_WDT_PRESCALE_SELECT_512	2
#घोषणा CDNS_WDT_PRESCALE_SELECT_4096	3

/* Input घड़ी frequency */
#घोषणा CDNS_WDT_CLK_10MHZ	10000000
#घोषणा CDNS_WDT_CLK_75MHZ	75000000

/* Counter maximum value */
#घोषणा CDNS_WDT_COUNTER_MAX 0xFFF

अटल पूर्णांक wdt_समयout;
अटल पूर्णांक nowayout = WATCHDOG_NOWAYOUT;

module_param(wdt_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(wdt_समयout,
		 "Watchdog time in seconds. (default="
		 __MODULE_STRING(CDNS_WDT_DEFAULT_TIMEOUT) ")");

module_param(nowayout, पूर्णांक, 0644);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/**
 * काष्ठा cdns_wdt - Watchकरोg device काष्ठाure
 * @regs: baseaddress of device
 * @rst: reset flag
 * @clk: काष्ठा clk * of a घड़ी source
 * @prescaler: क्रम saving prescaler value
 * @ctrl_clksel: counter घड़ी prescaler selection
 * @io_lock: spinlock क्रम IO रेजिस्टर access
 * @cdns_wdt_device: watchकरोg device काष्ठाure
 *
 * Structure containing parameters specअगरic to cadence watchकरोg.
 */
काष्ठा cdns_wdt अणु
	व्योम __iomem		*regs;
	bool			rst;
	काष्ठा clk		*clk;
	u32			prescaler;
	u32			ctrl_clksel;
	spinlock_t		io_lock;
	काष्ठा watchकरोg_device	cdns_wdt_device;
पूर्ण;

/* Write access to Registers */
अटल अंतरभूत व्योम cdns_wdt_ग_लिखोreg(काष्ठा cdns_wdt *wdt, u32 offset, u32 val)
अणु
	ग_लिखोl_relaxed(val, wdt->regs + offset);
पूर्ण

/*************************Register Map**************************************/

/* Register Offsets क्रम the WDT */
#घोषणा CDNS_WDT_ZMR_OFFSET	0x0	/* Zero Mode Register */
#घोषणा CDNS_WDT_CCR_OFFSET	0x4	/* Counter Control Register */
#घोषणा CDNS_WDT_RESTART_OFFSET	0x8	/* Restart Register */
#घोषणा CDNS_WDT_SR_OFFSET	0xC	/* Status Register */

/*
 * Zero Mode Register - This रेजिस्टर controls how the समय out is indicated
 * and also contains the access code to allow ग_लिखोs to the रेजिस्टर (0xABC).
 */
#घोषणा CDNS_WDT_ZMR_WDEN_MASK	0x00000001 /* Enable the WDT */
#घोषणा CDNS_WDT_ZMR_RSTEN_MASK	0x00000002 /* Enable the reset output */
#घोषणा CDNS_WDT_ZMR_IRQEN_MASK	0x00000004 /* Enable IRQ output */
#घोषणा CDNS_WDT_ZMR_RSTLEN_16	0x00000030 /* Reset pulse of 16 pclk cycles */
#घोषणा CDNS_WDT_ZMR_ZKEY_VAL	0x00ABC000 /* Access key, 0xABC << 12 */
/*
 * Counter Control रेजिस्टर - This रेजिस्टर controls how fast the समयr runs
 * and the reset value and also contains the access code to allow ग_लिखोs to
 * the रेजिस्टर.
 */
#घोषणा CDNS_WDT_CCR_CRV_MASK	0x00003FFC /* Counter reset value */

/**
 * cdns_wdt_stop - Stop the watchकरोg.
 *
 * @wdd: watchकरोg device
 *
 * Read the contents of the ZMR रेजिस्टर, clear the WDEN bit
 * in the रेजिस्टर and set the access key क्रम successful ग_लिखो.
 *
 * Return: always 0
 */
अटल पूर्णांक cdns_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा cdns_wdt *wdt = watchकरोg_get_drvdata(wdd);

	spin_lock(&wdt->io_lock);
	cdns_wdt_ग_लिखोreg(wdt, CDNS_WDT_ZMR_OFFSET,
			  CDNS_WDT_ZMR_ZKEY_VAL & (~CDNS_WDT_ZMR_WDEN_MASK));
	spin_unlock(&wdt->io_lock);

	वापस 0;
पूर्ण

/**
 * cdns_wdt_reload - Reload the watchकरोg समयr (i.e. pat the watchकरोg).
 *
 * @wdd: watchकरोg device
 *
 * Write the restart key value (0x00001999) to the restart रेजिस्टर.
 *
 * Return: always 0
 */
अटल पूर्णांक cdns_wdt_reload(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा cdns_wdt *wdt = watchकरोg_get_drvdata(wdd);

	spin_lock(&wdt->io_lock);
	cdns_wdt_ग_लिखोreg(wdt, CDNS_WDT_RESTART_OFFSET,
			  CDNS_WDT_RESTART_KEY);
	spin_unlock(&wdt->io_lock);

	वापस 0;
पूर्ण

/**
 * cdns_wdt_start - Enable and start the watchकरोg.
 *
 * @wdd: watchकरोg device
 *
 * The counter value is calculated according to the क्रमmula:
 *		calculated count = (समयout * घड़ी) / prescaler + 1.
 * The calculated count is भागided by 0x1000 to obtain the field value
 * to ग_लिखो to counter control रेजिस्टर.
 * Clears the contents of prescaler and counter reset value. Sets the
 * prescaler to 4096 and the calculated count and access key
 * to ग_लिखो to CCR Register.
 * Sets the WDT (WDEN bit) and either the Reset संकेत(RSTEN bit)
 * or Interrupt संकेत(IRQEN) with a specअगरied cycles and the access
 * key to ग_लिखो to ZMR Register.
 *
 * Return: always 0
 */
अटल पूर्णांक cdns_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा cdns_wdt *wdt = watchकरोg_get_drvdata(wdd);
	अचिन्हित पूर्णांक data = 0;
	अचिन्हित लघु count;
	अचिन्हित दीर्घ घड़ी_f = clk_get_rate(wdt->clk);

	/*
	 * Counter value भागisor to obtain the value of
	 * counter reset to be written to control रेजिस्टर.
	 */
	count = (wdd->समयout * (घड़ी_f / wdt->prescaler)) /
		 CDNS_WDT_COUNTER_VALUE_DIVISOR + 1;

	अगर (count > CDNS_WDT_COUNTER_MAX)
		count = CDNS_WDT_COUNTER_MAX;

	spin_lock(&wdt->io_lock);
	cdns_wdt_ग_लिखोreg(wdt, CDNS_WDT_ZMR_OFFSET,
			  CDNS_WDT_ZMR_ZKEY_VAL);

	count = (count << 2) & CDNS_WDT_CCR_CRV_MASK;

	/* Write counter access key first to be able ग_लिखो to रेजिस्टर */
	data = count | CDNS_WDT_REGISTER_ACCESS_KEY | wdt->ctrl_clksel;
	cdns_wdt_ग_लिखोreg(wdt, CDNS_WDT_CCR_OFFSET, data);
	data = CDNS_WDT_ZMR_WDEN_MASK | CDNS_WDT_ZMR_RSTLEN_16 |
	       CDNS_WDT_ZMR_ZKEY_VAL;

	/* Reset on समयout अगर specअगरied in device tree. */
	अगर (wdt->rst) अणु
		data |= CDNS_WDT_ZMR_RSTEN_MASK;
		data &= ~CDNS_WDT_ZMR_IRQEN_MASK;
	पूर्ण अन्यथा अणु
		data &= ~CDNS_WDT_ZMR_RSTEN_MASK;
		data |= CDNS_WDT_ZMR_IRQEN_MASK;
	पूर्ण
	cdns_wdt_ग_लिखोreg(wdt, CDNS_WDT_ZMR_OFFSET, data);
	cdns_wdt_ग_लिखोreg(wdt, CDNS_WDT_RESTART_OFFSET,
			  CDNS_WDT_RESTART_KEY);
	spin_unlock(&wdt->io_lock);

	वापस 0;
पूर्ण

/**
 * cdns_wdt_समय_रखोout - Set a new समयout value क्रम the watchकरोg device.
 *
 * @wdd: watchकरोg device
 * @new_समय: new समयout value that needs to be set
 * Return: 0 on success
 *
 * Update the watchकरोg_device समयout with new value which is used when
 * cdns_wdt_start is called.
 */
अटल पूर्णांक cdns_wdt_समय_रखोout(काष्ठा watchकरोg_device *wdd,
			       अचिन्हित पूर्णांक new_समय)
अणु
	wdd->समयout = new_समय;

	वापस cdns_wdt_start(wdd);
पूर्ण

/**
 * cdns_wdt_irq_handler - Notअगरies of watchकरोg समयout.
 *
 * @irq: पूर्णांकerrupt number
 * @dev_id: poपूर्णांकer to a platक्रमm device काष्ठाure
 * Return: IRQ_HANDLED
 *
 * The handler is invoked when the watchकरोg बार out and a
 * reset on समयout has not been enabled.
 */
अटल irqवापस_t cdns_wdt_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;

	dev_info(&pdev->dev,
		 "Watchdog timed out. Internal reset not enabled\n");

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Info काष्ठाure used to indicate the features supported by the device
 * to the upper layers. This is defined in watchकरोg.h header file.
 */
अटल स्थिर काष्ठा watchकरोg_info cdns_wdt_info = अणु
	.identity	= "cdns_wdt watchdog",
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
			  WDIOF_MAGICCLOSE,
पूर्ण;

/* Watchकरोg Core Ops */
अटल स्थिर काष्ठा watchकरोg_ops cdns_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = cdns_wdt_start,
	.stop = cdns_wdt_stop,
	.ping = cdns_wdt_reload,
	.set_समयout = cdns_wdt_समय_रखोout,
पूर्ण;

अटल व्योम cdns_clk_disable_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

/************************Platक्रमm Operations*****************************/
/**
 * cdns_wdt_probe - Probe call क्रम the device.
 *
 * @pdev: handle to the platक्रमm device काष्ठाure.
 * Return: 0 on success, negative error otherwise.
 *
 * It करोes all the memory allocation and registration क्रम the device.
 */
अटल पूर्णांक cdns_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, irq;
	अचिन्हित दीर्घ घड़ी_f;
	काष्ठा cdns_wdt *wdt;
	काष्ठा watchकरोg_device *cdns_wdt_device;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	cdns_wdt_device = &wdt->cdns_wdt_device;
	cdns_wdt_device->info = &cdns_wdt_info;
	cdns_wdt_device->ops = &cdns_wdt_ops;
	cdns_wdt_device->समयout = CDNS_WDT_DEFAULT_TIMEOUT;
	cdns_wdt_device->min_समयout = CDNS_WDT_MIN_TIMEOUT;
	cdns_wdt_device->max_समयout = CDNS_WDT_MAX_TIMEOUT;

	wdt->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->regs))
		वापस PTR_ERR(wdt->regs);

	/* Register the पूर्णांकerrupt */
	wdt->rst = of_property_पढ़ो_bool(dev->of_node, "reset-on-timeout");
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!wdt->rst && irq >= 0) अणु
		ret = devm_request_irq(dev, irq, cdns_wdt_irq_handler, 0,
				       pdev->name, pdev);
		अगर (ret) अणु
			dev_err(dev,
				"cannot register interrupt handler err=%d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Initialize the members of cdns_wdt काष्ठाure */
	cdns_wdt_device->parent = dev;

	watchकरोg_init_समयout(cdns_wdt_device, wdt_समयout, dev);
	watchकरोg_set_nowayout(cdns_wdt_device, nowayout);
	watchकरोg_stop_on_reboot(cdns_wdt_device);
	watchकरोg_set_drvdata(cdns_wdt_device, wdt);

	wdt->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(wdt->clk))
		वापस dev_err_probe(dev, PTR_ERR(wdt->clk),
				     "input clock not found\n");

	ret = clk_prepare_enable(wdt->clk);
	अगर (ret) अणु
		dev_err(dev, "unable to enable clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(dev, cdns_clk_disable_unprepare,
				       wdt->clk);
	अगर (ret)
		वापस ret;

	घड़ी_f = clk_get_rate(wdt->clk);
	अगर (घड़ी_f <= CDNS_WDT_CLK_75MHZ) अणु
		wdt->prescaler = CDNS_WDT_PRESCALE_512;
		wdt->ctrl_clksel = CDNS_WDT_PRESCALE_SELECT_512;
	पूर्ण अन्यथा अणु
		wdt->prescaler = CDNS_WDT_PRESCALE_4096;
		wdt->ctrl_clksel = CDNS_WDT_PRESCALE_SELECT_4096;
	पूर्ण

	spin_lock_init(&wdt->io_lock);

	watchकरोg_stop_on_reboot(cdns_wdt_device);
	watchकरोg_stop_on_unरेजिस्टर(cdns_wdt_device);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, cdns_wdt_device);
	अगर (ret)
		वापस ret;
	platक्रमm_set_drvdata(pdev, wdt);

	dev_info(dev, "Xilinx Watchdog Timer with timeout %ds%s\n",
		 cdns_wdt_device->समयout, nowayout ? ", nowayout" : "");

	वापस 0;
पूर्ण

/**
 * cdns_wdt_suspend - Stop the device.
 *
 * @dev: handle to the device काष्ठाure.
 * Return: 0 always.
 */
अटल पूर्णांक __maybe_unused cdns_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdns_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->cdns_wdt_device)) अणु
		cdns_wdt_stop(&wdt->cdns_wdt_device);
		clk_disable_unprepare(wdt->clk);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cdns_wdt_resume - Resume the device.
 *
 * @dev: handle to the device काष्ठाure.
 * Return: 0 on success, त्रुटि_सं otherwise.
 */
अटल पूर्णांक __maybe_unused cdns_wdt_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा cdns_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->cdns_wdt_device)) अणु
		ret = clk_prepare_enable(wdt->clk);
		अगर (ret) अणु
			dev_err(dev, "unable to enable clock\n");
			वापस ret;
		पूर्ण
		cdns_wdt_start(&wdt->cdns_wdt_device);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cdns_wdt_pm_ops, cdns_wdt_suspend, cdns_wdt_resume);

अटल स्थिर काष्ठा of_device_id cdns_wdt_of_match[] = अणु
	अणु .compatible = "cdns,wdt-r1p2", पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_wdt_of_match);

/* Driver Structure */
अटल काष्ठा platक्रमm_driver cdns_wdt_driver = अणु
	.probe		= cdns_wdt_probe,
	.driver		= अणु
		.name	= "cdns-wdt",
		.of_match_table = cdns_wdt_of_match,
		.pm	= &cdns_wdt_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cdns_wdt_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Watchdog driver for Cadence WDT");
MODULE_LICENSE("GPL");
