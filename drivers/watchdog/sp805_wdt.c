<शैली गुरु>
/*
 * drivers/अक्षर/watchकरोg/sp805-wdt.c
 *
 * Watchकरोg driver क्रम ARM SP805 watchकरोg module
 *
 * Copyright (C) 2010 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2 or later. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/resource.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

/* शेष समयout in seconds */
#घोषणा DEFAULT_TIMEOUT		60

#घोषणा MODULE_NAME		"sp805-wdt"

/* watchकरोg रेजिस्टर offsets and masks */
#घोषणा WDTLOAD			0x000
	#घोषणा LOAD_MIN	0x00000001
	#घोषणा LOAD_MAX	0xFFFFFFFF
#घोषणा WDTVALUE		0x004
#घोषणा WDTCONTROL		0x008
	/* control रेजिस्टर masks */
	#घोषणा	INT_ENABLE	(1 << 0)
	#घोषणा	RESET_ENABLE	(1 << 1)
	#घोषणा	ENABLE_MASK	(INT_ENABLE | RESET_ENABLE)
#घोषणा WDTINTCLR		0x00C
#घोषणा WDTRIS			0x010
#घोषणा WDTMIS			0x014
	#घोषणा INT_MASK	(1 << 0)
#घोषणा WDTLOCK			0xC00
	#घोषणा	UNLOCK		0x1ACCE551
	#घोषणा	LOCK		0x00000001

/**
 * काष्ठा sp805_wdt: sp805 wdt device काष्ठाure
 * @wdd: instance of काष्ठा watchकरोg_device
 * @lock: spin lock protecting dev काष्ठाure and io access
 * @base: base address of wdt
 * @clk: घड़ी काष्ठाure of wdt
 * @adev: amba device काष्ठाure of wdt
 * @status: current status of wdt
 * @load_val: load value to be set क्रम current समयout
 */
काष्ठा sp805_wdt अणु
	काष्ठा watchकरोg_device		wdd;
	spinlock_t			lock;
	व्योम __iomem			*base;
	काष्ठा clk			*clk;
	u64				rate;
	काष्ठा amba_device		*adev;
	अचिन्हित पूर्णांक			load_val;
पूर्ण;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Set to 1 to keep watchdog running after device release");

/* वापसs true अगर wdt is running; otherwise वापसs false */
अटल bool wdt_is_running(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sp805_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u32 wdtcontrol = पढ़ोl_relaxed(wdt->base + WDTCONTROL);

	वापस (wdtcontrol & ENABLE_MASK) == ENABLE_MASK;
पूर्ण

/* This routine finds load value that will reset प्रणाली in required timout */
अटल पूर्णांक wdt_setload(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा sp805_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u64 load, rate;

	rate = wdt->rate;

	/*
	 * sp805 runs counter with given value twice, after the end of first
	 * counter it gives an पूर्णांकerrupt and then starts counter again. If
	 * पूर्णांकerrupt alपढ़ोy occurred then it resets the प्रणाली. This is why
	 * load is half of what should be required.
	 */
	load = भाग_u64(rate, 2) * समयout - 1;

	load = (load > LOAD_MAX) ? LOAD_MAX : load;
	load = (load < LOAD_MIN) ? LOAD_MIN : load;

	spin_lock(&wdt->lock);
	wdt->load_val = load;
	/* roundup समयout to बंदst positive पूर्णांकeger value */
	wdd->समयout = भाग_u64((load + 1) * 2 + (rate / 2), rate);
	spin_unlock(&wdt->lock);

	वापस 0;
पूर्ण

/* वापसs number of seconds left क्रम reset to occur */
अटल अचिन्हित पूर्णांक wdt_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sp805_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u64 load;

	spin_lock(&wdt->lock);
	load = पढ़ोl_relaxed(wdt->base + WDTVALUE);

	/*If the पूर्णांकerrupt is inactive then समय left is WDTValue + WDTLoad. */
	अगर (!(पढ़ोl_relaxed(wdt->base + WDTRIS) & INT_MASK))
		load += wdt->load_val + 1;
	spin_unlock(&wdt->lock);

	वापस भाग_u64(load, wdt->rate);
पूर्ण

अटल पूर्णांक
wdt_restart(काष्ठा watchकरोg_device *wdd, अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा sp805_wdt *wdt = watchकरोg_get_drvdata(wdd);

	ग_लिखोl_relaxed(UNLOCK, wdt->base + WDTLOCK);
	ग_लिखोl_relaxed(0, wdt->base + WDTCONTROL);
	ग_लिखोl_relaxed(0, wdt->base + WDTLOAD);
	ग_लिखोl_relaxed(INT_ENABLE | RESET_ENABLE, wdt->base + WDTCONTROL);

	/* Flush posted ग_लिखोs. */
	पढ़ोl_relaxed(wdt->base + WDTLOCK);

	वापस 0;
पूर्ण

अटल पूर्णांक wdt_config(काष्ठा watchकरोg_device *wdd, bool ping)
अणु
	काष्ठा sp805_wdt *wdt = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	अगर (!ping) अणु

		ret = clk_prepare_enable(wdt->clk);
		अगर (ret) अणु
			dev_err(&wdt->adev->dev, "clock enable fail");
			वापस ret;
		पूर्ण
	पूर्ण

	spin_lock(&wdt->lock);

	ग_लिखोl_relaxed(UNLOCK, wdt->base + WDTLOCK);
	ग_लिखोl_relaxed(wdt->load_val, wdt->base + WDTLOAD);
	ग_लिखोl_relaxed(INT_MASK, wdt->base + WDTINTCLR);

	अगर (!ping)
		ग_लिखोl_relaxed(INT_ENABLE | RESET_ENABLE, wdt->base +
				WDTCONTROL);

	ग_लिखोl_relaxed(LOCK, wdt->base + WDTLOCK);

	/* Flush posted ग_लिखोs. */
	पढ़ोl_relaxed(wdt->base + WDTLOCK);
	spin_unlock(&wdt->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdt_config(wdd, true);
पूर्ण

/* enables watchकरोg समयrs reset */
अटल पूर्णांक wdt_enable(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdt_config(wdd, false);
पूर्ण

/* disables watchकरोg समयrs reset */
अटल पूर्णांक wdt_disable(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा sp805_wdt *wdt = watchकरोg_get_drvdata(wdd);

	spin_lock(&wdt->lock);

	ग_लिखोl_relaxed(UNLOCK, wdt->base + WDTLOCK);
	ग_लिखोl_relaxed(0, wdt->base + WDTCONTROL);
	ग_लिखोl_relaxed(LOCK, wdt->base + WDTLOCK);

	/* Flush posted ग_लिखोs. */
	पढ़ोl_relaxed(wdt->base + WDTLOCK);
	spin_unlock(&wdt->lock);

	clk_disable_unprepare(wdt->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info wdt_info = अणु
	.options = WDIOF_MAGICCLOSE | WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
	.identity = MODULE_NAME,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= wdt_enable,
	.stop		= wdt_disable,
	.ping		= wdt_ping,
	.set_समयout	= wdt_setload,
	.get_समयleft	= wdt_समयleft,
	.restart	= wdt_restart,
पूर्ण;

अटल पूर्णांक
sp805_wdt_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा sp805_wdt *wdt;
	पूर्णांक ret = 0;

	wdt = devm_kzalloc(&adev->dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	wdt->base = devm_ioremap_resource(&adev->dev, &adev->res);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	अगर (adev->dev.of_node) अणु
		wdt->clk = devm_clk_get(&adev->dev, शून्य);
		अगर (IS_ERR(wdt->clk)) अणु
			dev_err(&adev->dev, "Clock not found\n");
			वापस PTR_ERR(wdt->clk);
		पूर्ण
		wdt->rate = clk_get_rate(wdt->clk);
	पूर्ण अन्यथा अगर (has_acpi_companion(&adev->dev)) अणु
		/*
		 * When Driver probe with ACPI device, घड़ी devices
		 * are not available, so watchकरोg rate get from
		 * घड़ी-frequency property given in _DSD object.
		 */
		device_property_पढ़ो_u64(&adev->dev, "clock-frequency",
					 &wdt->rate);
		अगर (!wdt->rate) अणु
			dev_err(&adev->dev, "no clock-frequency property\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	wdt->adev = adev;
	wdt->wdd.info = &wdt_info;
	wdt->wdd.ops = &wdt_ops;
	wdt->wdd.parent = &adev->dev;

	spin_lock_init(&wdt->lock);
	watchकरोg_set_nowayout(&wdt->wdd, nowayout);
	watchकरोg_set_drvdata(&wdt->wdd, wdt);
	watchकरोg_set_restart_priority(&wdt->wdd, 128);

	/*
	 * If 'timeout-sec' devicetree property is specअगरied, use that.
	 * Otherwise, use DEFAULT_TIMEOUT
	 */
	wdt->wdd.समयout = DEFAULT_TIMEOUT;
	watchकरोg_init_समयout(&wdt->wdd, 0, &adev->dev);
	wdt_setload(&wdt->wdd, wdt->wdd.समयout);

	/*
	 * If HW is alपढ़ोy running, enable/reset the wdt and set the running
	 * bit to tell the wdt subप्रणाली
	 */
	अगर (wdt_is_running(&wdt->wdd)) अणु
		wdt_enable(&wdt->wdd);
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	पूर्ण

	watchकरोg_stop_on_reboot(&wdt->wdd);
	ret = watchकरोg_रेजिस्टर_device(&wdt->wdd);
	अगर (ret)
		जाओ err;
	amba_set_drvdata(adev, wdt);

	dev_info(&adev->dev, "registration successful\n");
	वापस 0;

err:
	dev_err(&adev->dev, "Probe Failed!!!\n");
	वापस ret;
पूर्ण

अटल व्योम sp805_wdt_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा sp805_wdt *wdt = amba_get_drvdata(adev);

	watchकरोg_unरेजिस्टर_device(&wdt->wdd);
	watchकरोg_set_drvdata(&wdt->wdd, शून्य);
पूर्ण

अटल पूर्णांक __maybe_unused sp805_wdt_suspend(काष्ठा device *dev)
अणु
	काष्ठा sp805_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		वापस wdt_disable(&wdt->wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sp805_wdt_resume(काष्ठा device *dev)
अणु
	काष्ठा sp805_wdt *wdt = dev_get_drvdata(dev);

	अगर (watchकरोg_active(&wdt->wdd))
		वापस wdt_enable(&wdt->wdd);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sp805_wdt_dev_pm_ops, sp805_wdt_suspend,
		sp805_wdt_resume);

अटल स्थिर काष्ठा amba_id sp805_wdt_ids[] = अणु
	अणु
		.id	= 0x00141805,
		.mask	= 0x00ffffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, sp805_wdt_ids);

अटल काष्ठा amba_driver sp805_wdt_driver = अणु
	.drv = अणु
		.name	= MODULE_NAME,
		.pm	= &sp805_wdt_dev_pm_ops,
	पूर्ण,
	.id_table	= sp805_wdt_ids,
	.probe		= sp805_wdt_probe,
	.हटाओ = sp805_wdt_हटाओ,
पूर्ण;

module_amba_driver(sp805_wdt_driver);

MODULE_AUTHOR("Viresh Kumar <vireshk@kernel.org>");
MODULE_DESCRIPTION("ARM SP805 Watchdog Driver");
MODULE_LICENSE("GPL");
