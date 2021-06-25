<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम Broadcom BCM2835
 *
 * "bcm2708_wdog" driver written by Luke Diamand that was obtained from
 * branch "rpi-3.6.y" of git://github.com/raspberrypi/linux.git was used
 * as a hardware reference क्रम the Broadcom BCM2835 watchकरोg समयr.
 *
 * Copyright (C) 2013 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/mfd/bcm2835-pm.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा PM_RSTC				0x1c
#घोषणा PM_RSTS				0x20
#घोषणा PM_WDOG				0x24

#घोषणा PM_PASSWORD			0x5a000000

#घोषणा PM_WDOG_TIME_SET		0x000fffff
#घोषणा PM_RSTC_WRCFG_CLR		0xffffffcf
#घोषणा PM_RSTS_HADWRH_SET		0x00000040
#घोषणा PM_RSTC_WRCFG_SET		0x00000030
#घोषणा PM_RSTC_WRCFG_FULL_RESET	0x00000020
#घोषणा PM_RSTC_RESET			0x00000102

/*
 * The Raspberry Pi firmware uses the RSTS रेजिस्टर to know which partition
 * to boot from. The partition value is spपढ़ो पूर्णांकo bits 0, 2, 4, 6, 8, 10.
 * Partition 63 is a special partition used by the firmware to indicate halt.
 */
#घोषणा PM_RSTS_RASPBERRYPI_HALT	0x555

#घोषणा SECS_TO_WDOG_TICKS(x) ((x) << 16)
#घोषणा WDOG_TICKS_TO_SECS(x) ((x) >> 16)

काष्ठा bcm2835_wdt अणु
	व्योम __iomem		*base;
	spinlock_t		lock;
पूर्ण;

अटल काष्ठा bcm2835_wdt *bcm2835_घातer_off_wdt;

अटल अचिन्हित पूर्णांक heartbeat;
अटल bool nowayout = WATCHDOG_NOWAYOUT;

अटल bool bcm2835_wdt_is_running(काष्ठा bcm2835_wdt *wdt)
अणु
	uपूर्णांक32_t cur;

	cur = पढ़ोl(wdt->base + PM_RSTC);

	वापस !!(cur & PM_RSTC_WRCFG_FULL_RESET);
पूर्ण

अटल पूर्णांक bcm2835_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm2835_wdt *wdt = watchकरोg_get_drvdata(wकरोg);
	uपूर्णांक32_t cur;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdt->lock, flags);

	ग_लिखोl_relaxed(PM_PASSWORD | (SECS_TO_WDOG_TICKS(wकरोg->समयout) &
				PM_WDOG_TIME_SET), wdt->base + PM_WDOG);
	cur = पढ़ोl_relaxed(wdt->base + PM_RSTC);
	ग_लिखोl_relaxed(PM_PASSWORD | (cur & PM_RSTC_WRCFG_CLR) |
		  PM_RSTC_WRCFG_FULL_RESET, wdt->base + PM_RSTC);

	spin_unlock_irqrestore(&wdt->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm2835_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	ग_लिखोl_relaxed(PM_PASSWORD | PM_RSTC_RESET, wdt->base + PM_RSTC);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक bcm2835_wdt_get_समयleft(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा bcm2835_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	uपूर्णांक32_t ret = पढ़ोl_relaxed(wdt->base + PM_WDOG);
	वापस WDOG_TICKS_TO_SECS(ret & PM_WDOG_TIME_SET);
पूर्ण

अटल व्योम __bcm2835_restart(काष्ठा bcm2835_wdt *wdt)
अणु
	u32 val;

	/* use a समयout of 10 ticks (~150us) */
	ग_लिखोl_relaxed(10 | PM_PASSWORD, wdt->base + PM_WDOG);
	val = पढ़ोl_relaxed(wdt->base + PM_RSTC);
	val &= PM_RSTC_WRCFG_CLR;
	val |= PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET;
	ग_लिखोl_relaxed(val, wdt->base + PM_RSTC);

	/* No sleeping, possibly atomic. */
	mdelay(1);
पूर्ण

अटल पूर्णांक bcm2835_restart(काष्ठा watchकरोg_device *wकरोg,
			   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा bcm2835_wdt *wdt = watchकरोg_get_drvdata(wकरोg);

	__bcm2835_restart(wdt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops bcm2835_wdt_ops = अणु
	.owner =	THIS_MODULE,
	.start =	bcm2835_wdt_start,
	.stop =		bcm2835_wdt_stop,
	.get_समयleft =	bcm2835_wdt_get_समयleft,
	.restart =	bcm2835_restart,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info bcm2835_wdt_info = अणु
	.options =	WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE |
			WDIOF_KEEPALIVEPING,
	.identity =	"Broadcom BCM2835 Watchdog timer",
पूर्ण;

अटल काष्ठा watchकरोg_device bcm2835_wdt_wdd = अणु
	.info =		&bcm2835_wdt_info,
	.ops =		&bcm2835_wdt_ops,
	.min_समयout =	1,
	.max_समयout =	WDOG_TICKS_TO_SECS(PM_WDOG_TIME_SET),
	.समयout =	WDOG_TICKS_TO_SECS(PM_WDOG_TIME_SET),
पूर्ण;

/*
 * We can't really घातer off, but अगर we करो the normal reset scheme, and
 * indicate to bootcode.bin not to reboot, then most of the chip will be
 * घातered off.
 */
अटल व्योम bcm2835_घातer_off(व्योम)
अणु
	काष्ठा bcm2835_wdt *wdt = bcm2835_घातer_off_wdt;
	u32 val;

	/*
	 * We set the watchकरोg hard reset bit here to distinguish this reset
	 * from the normal (full) reset. bootcode.bin will not reboot after a
	 * hard reset.
	 */
	val = पढ़ोl_relaxed(wdt->base + PM_RSTS);
	val |= PM_PASSWORD | PM_RSTS_RASPBERRYPI_HALT;
	ग_लिखोl_relaxed(val, wdt->base + PM_RSTS);

	/* Continue with normal reset mechanism */
	__bcm2835_restart(wdt);
पूर्ण

अटल पूर्णांक bcm2835_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_pm *pm = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm2835_wdt *wdt;
	पूर्णांक err;

	wdt = devm_kzalloc(dev, माप(काष्ठा bcm2835_wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	spin_lock_init(&wdt->lock);

	wdt->base = pm->base;

	watchकरोg_set_drvdata(&bcm2835_wdt_wdd, wdt);
	watchकरोg_init_समयout(&bcm2835_wdt_wdd, heartbeat, dev);
	watchकरोg_set_nowayout(&bcm2835_wdt_wdd, nowayout);
	bcm2835_wdt_wdd.parent = dev;
	अगर (bcm2835_wdt_is_running(wdt)) अणु
		/*
		 * The currently active समयout value (set by the
		 * bootloader) may be dअगरferent from the module
		 * heartbeat parameter or the value in device
		 * tree. But we just need to set WDOG_HW_RUNNING,
		 * because then the framework will "immediately" ping
		 * the device, updating the समयout.
		 */
		set_bit(WDOG_HW_RUNNING, &bcm2835_wdt_wdd.status);
	पूर्ण

	watchकरोg_set_restart_priority(&bcm2835_wdt_wdd, 128);

	watchकरोg_stop_on_reboot(&bcm2835_wdt_wdd);
	err = devm_watchकरोg_रेजिस्टर_device(dev, &bcm2835_wdt_wdd);
	अगर (err)
		वापस err;

	अगर (pm_घातer_off == शून्य) अणु
		pm_घातer_off = bcm2835_घातer_off;
		bcm2835_घातer_off_wdt = wdt;
	पूर्ण

	dev_info(dev, "Broadcom BCM2835 watchdog timer");
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == bcm2835_घातer_off)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm2835_wdt_driver = अणु
	.probe		= bcm2835_wdt_probe,
	.हटाओ		= bcm2835_wdt_हटाओ,
	.driver = अणु
		.name =		"bcm2835-wdt",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm2835_wdt_driver);

module_param(heartbeat, uपूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Initial watchdog heartbeat in seconds");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

MODULE_ALIAS("platform:bcm2835-wdt");
MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Driver for Broadcom BCM2835 watchdog timer");
MODULE_LICENSE("GPL");
