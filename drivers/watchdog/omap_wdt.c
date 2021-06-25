<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * omap_wdt.c
 *
 * Watchकरोg driver क्रम the TI OMAP 16xx & 24xx/34xx 32KHz (non-secure) watchकरोg
 *
 * Author: MontaVista Software, Inc.
 *	 <gdavis@mvista.com> or <source@mvista.com>
 *
 * 2003 (c) MontaVista Software, Inc.
 *
 * History:
 *
 * 20030527: George G. Davis <gdavis@mvista.com>
 *	Initially based on linux-2.4.19-rmk7-pxa1/drivers/अक्षर/sa1100_wdt.c
 *	(c) Copyright 2000 Oleg Drokin <green@crimea.edu>
 *	Based on SoftDog driver by Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * Copyright (c) 2004 Texas Instruments.
 *	1. Modअगरied to support OMAP1610 32-KHz watchकरोg समयr
 *	2. Ported to 2.6 kernel
 *
 * Copyright (c) 2005 David Brownell
 *	Use the driver model and standard identअगरiers; handle bigger समयouts.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/reboot.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_data/omap-wd-समयr.h>

#समावेश "omap_wdt.h"

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अचिन्हित समयr_margin;
module_param(समयr_margin, uपूर्णांक, 0);
MODULE_PARM_DESC(समयr_margin, "initial watchdog timeout (in seconds)");

#घोषणा to_omap_wdt_dev(_wकरोg)	container_of(_wकरोg, काष्ठा omap_wdt_dev, wकरोg)

अटल bool early_enable;
module_param(early_enable, bool, 0);
MODULE_PARM_DESC(early_enable,
	"Watchdog is started on module insertion (default=0)");

काष्ठा omap_wdt_dev अणु
	काष्ठा watchकरोg_device wकरोg;
	व्योम __iomem    *base;          /* physical */
	काष्ठा device   *dev;
	bool		omap_wdt_users;
	पूर्णांक		wdt_trgr_pattern;
	काष्ठा mutex	lock;		/* to aव्योम races with PM */
पूर्ण;

अटल व्योम omap_wdt_reload(काष्ठा omap_wdt_dev *wdev)
अणु
	व्योम __iomem    *base = wdev->base;

	/* रुको क्रम posted ग_लिखो to complete */
	जबतक ((पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS)) & 0x08)
		cpu_relax();

	wdev->wdt_trgr_pattern = ~wdev->wdt_trgr_pattern;
	ग_लिखोl_relaxed(wdev->wdt_trgr_pattern, (base + OMAP_WATCHDOG_TGR));

	/* रुको क्रम posted ग_लिखो to complete */
	जबतक ((पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS)) & 0x08)
		cpu_relax();
	/* reloaded WCRR from WLDR */
पूर्ण

अटल व्योम omap_wdt_enable(काष्ठा omap_wdt_dev *wdev)
अणु
	व्योम __iomem *base = wdev->base;

	/* Sequence to enable the watchकरोg */
	ग_लिखोl_relaxed(0xBBBB, base + OMAP_WATCHDOG_SPR);
	जबतक ((पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS)) & 0x10)
		cpu_relax();

	ग_लिखोl_relaxed(0x4444, base + OMAP_WATCHDOG_SPR);
	जबतक ((पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS)) & 0x10)
		cpu_relax();
पूर्ण

अटल व्योम omap_wdt_disable(काष्ठा omap_wdt_dev *wdev)
अणु
	व्योम __iomem *base = wdev->base;

	/* sequence required to disable watchकरोg */
	ग_लिखोl_relaxed(0xAAAA, base + OMAP_WATCHDOG_SPR);	/* TIMER_MODE */
	जबतक (पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS) & 0x10)
		cpu_relax();

	ग_लिखोl_relaxed(0x5555, base + OMAP_WATCHDOG_SPR);	/* TIMER_MODE */
	जबतक (पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS) & 0x10)
		cpu_relax();
पूर्ण

अटल व्योम omap_wdt_set_समयr(काष्ठा omap_wdt_dev *wdev,
				   अचिन्हित पूर्णांक समयout)
अणु
	u32 pre_margin = GET_WLDR_VAL(समयout);
	व्योम __iomem *base = wdev->base;

	/* just count up at 32 KHz */
	जबतक (पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS) & 0x04)
		cpu_relax();

	ग_लिखोl_relaxed(pre_margin, base + OMAP_WATCHDOG_LDR);
	जबतक (पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS) & 0x04)
		cpu_relax();
पूर्ण

अटल पूर्णांक omap_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा omap_wdt_dev *wdev = to_omap_wdt_dev(wकरोg);
	व्योम __iomem *base = wdev->base;

	mutex_lock(&wdev->lock);

	wdev->omap_wdt_users = true;

	pm_runसमय_get_sync(wdev->dev);

	/*
	 * Make sure the watchकरोg is disabled. This is unक्रमtunately required
	 * because writing to various रेजिस्टरs with the watchकरोg running has no
	 * effect.
	 */
	omap_wdt_disable(wdev);

	/* initialize prescaler */
	जबतक (पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS) & 0x01)
		cpu_relax();

	ग_लिखोl_relaxed((1 << 5) | (PTV << 2), base + OMAP_WATCHDOG_CNTRL);
	जबतक (पढ़ोl_relaxed(base + OMAP_WATCHDOG_WPS) & 0x01)
		cpu_relax();

	omap_wdt_set_समयr(wdev, wकरोg->समयout);
	omap_wdt_reload(wdev); /* trigger loading of new समयout value */
	omap_wdt_enable(wdev);

	mutex_unlock(&wdev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा omap_wdt_dev *wdev = to_omap_wdt_dev(wकरोg);

	mutex_lock(&wdev->lock);
	omap_wdt_disable(wdev);
	pm_runसमय_put_sync(wdev->dev);
	wdev->omap_wdt_users = false;
	mutex_unlock(&wdev->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_wdt_ping(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा omap_wdt_dev *wdev = to_omap_wdt_dev(wकरोg);

	mutex_lock(&wdev->lock);
	omap_wdt_reload(wdev);
	mutex_unlock(&wdev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा omap_wdt_dev *wdev = to_omap_wdt_dev(wकरोg);

	mutex_lock(&wdev->lock);
	omap_wdt_disable(wdev);
	omap_wdt_set_समयr(wdev, समयout);
	omap_wdt_enable(wdev);
	omap_wdt_reload(wdev);
	wकरोg->समयout = समयout;
	mutex_unlock(&wdev->lock);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक omap_wdt_get_समयleft(काष्ठा watchकरोg_device *wकरोg)
अणु
	काष्ठा omap_wdt_dev *wdev = to_omap_wdt_dev(wकरोg);
	व्योम __iomem *base = wdev->base;
	u32 value;

	value = पढ़ोl_relaxed(base + OMAP_WATCHDOG_CRR);
	वापस GET_WCCR_SECS(value);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info omap_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "OMAP Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops omap_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= omap_wdt_start,
	.stop		= omap_wdt_stop,
	.ping		= omap_wdt_ping,
	.set_समयout	= omap_wdt_set_समयout,
	.get_समयleft	= omap_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक omap_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_wd_समयr_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा omap_wdt_dev *wdev;
	पूर्णांक ret;

	wdev = devm_kzalloc(&pdev->dev, माप(*wdev), GFP_KERNEL);
	अगर (!wdev)
		वापस -ENOMEM;

	wdev->omap_wdt_users	= false;
	wdev->dev		= &pdev->dev;
	wdev->wdt_trgr_pattern	= 0x1234;
	mutex_init(&wdev->lock);

	/* reserve अटल रेजिस्टर mappings */
	wdev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdev->base))
		वापस PTR_ERR(wdev->base);

	wdev->wकरोg.info = &omap_wdt_info;
	wdev->wकरोg.ops = &omap_wdt_ops;
	wdev->wकरोg.min_समयout = TIMER_MARGIN_MIN;
	wdev->wकरोg.max_समयout = TIMER_MARGIN_MAX;
	wdev->wकरोg.समयout = TIMER_MARGIN_DEFAULT;
	wdev->wकरोg.parent = &pdev->dev;

	watchकरोg_init_समयout(&wdev->wकरोg, समयr_margin, &pdev->dev);

	watchकरोg_set_nowayout(&wdev->wकरोg, nowayout);

	platक्रमm_set_drvdata(pdev, wdev);

	pm_runसमय_enable(wdev->dev);
	pm_runसमय_get_sync(wdev->dev);

	अगर (pdata && pdata->पढ़ो_reset_sources) अणु
		u32 rs = pdata->पढ़ो_reset_sources();
		अगर (rs & (1 << OMAP_MPU_WD_RST_SRC_ID_SHIFT))
			wdev->wकरोg.bootstatus = WDIOF_CARDRESET;
	पूर्ण

	अगर (!early_enable)
		omap_wdt_disable(wdev);

	ret = watchकरोg_रेजिस्टर_device(&wdev->wकरोg);
	अगर (ret) अणु
		pm_runसमय_put(wdev->dev);
		pm_runसमय_disable(wdev->dev);
		वापस ret;
	पूर्ण

	pr_info("OMAP Watchdog Timer Rev 0x%02x: initial timeout %d sec\n",
		पढ़ोl_relaxed(wdev->base + OMAP_WATCHDOG_REV) & 0xFF,
		wdev->wकरोg.समयout);

	अगर (early_enable)
		omap_wdt_start(&wdev->wकरोg);

	pm_runसमय_put(wdev->dev);

	वापस 0;
पूर्ण

अटल व्योम omap_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_wdt_dev *wdev = platक्रमm_get_drvdata(pdev);

	mutex_lock(&wdev->lock);
	अगर (wdev->omap_wdt_users) अणु
		omap_wdt_disable(wdev);
		pm_runसमय_put_sync(wdev->dev);
	पूर्ण
	mutex_unlock(&wdev->lock);
पूर्ण

अटल पूर्णांक omap_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_wdt_dev *wdev = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(wdev->dev);
	watchकरोg_unरेजिस्टर_device(&wdev->wकरोg);

	वापस 0;
पूर्ण

#अगर_घोषित	CONFIG_PM

/* REVISIT ... not clear this is the best way to handle प्रणाली suspend; and
 * it's very inappropriate क्रम selective device suspend (e.g. suspending this
 * through sysfs rather than by stopping the watchकरोg daemon).  Also, this
 * may not play well enough with NOWAYOUT...
 */

अटल पूर्णांक omap_wdt_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा omap_wdt_dev *wdev = platक्रमm_get_drvdata(pdev);

	mutex_lock(&wdev->lock);
	अगर (wdev->omap_wdt_users) अणु
		omap_wdt_disable(wdev);
		pm_runसमय_put_sync(wdev->dev);
	पूर्ण
	mutex_unlock(&wdev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_wdt_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_wdt_dev *wdev = platक्रमm_get_drvdata(pdev);

	mutex_lock(&wdev->lock);
	अगर (wdev->omap_wdt_users) अणु
		pm_runसमय_get_sync(wdev->dev);
		omap_wdt_enable(wdev);
		omap_wdt_reload(wdev);
	पूर्ण
	mutex_unlock(&wdev->lock);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा	omap_wdt_suspend	शून्य
#घोषणा	omap_wdt_resume		शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id omap_wdt_of_match[] = अणु
	अणु .compatible = "ti,omap3-wdt", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_wdt_of_match);

अटल काष्ठा platक्रमm_driver omap_wdt_driver = अणु
	.probe		= omap_wdt_probe,
	.हटाओ		= omap_wdt_हटाओ,
	.shutकरोwn	= omap_wdt_shutकरोwn,
	.suspend	= omap_wdt_suspend,
	.resume		= omap_wdt_resume,
	.driver		= अणु
		.name	= "omap_wdt",
		.of_match_table = omap_wdt_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_wdt_driver);

MODULE_AUTHOR("George G. Davis");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap_wdt");
