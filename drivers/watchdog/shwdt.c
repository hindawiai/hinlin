<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/watchकरोg/shwdt.c
 *
 * Watchकरोg driver क्रम पूर्णांकegrated watchकरोg in the SuperH processors.
 *
 * Copyright (C) 2001 - 2012  Paul Mundt <lethal@linux-sh.org>
 *
 * 14-Dec-2001 Matt Domsch <Matt_Domsch@dell.com>
 *     Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT
 *
 * 19-Apr-2002 Rob Radez <rob@osinvestor.com>
 *     Added expect बंद support, made emulated समयout runसमय changeable
 *     general cleanups, add some ioctls
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/watchकरोg.h>

#घोषणा DRV_NAME "sh-wdt"

/*
 * Default घड़ी भागision ratio is 5.25 msecs. For an additional table of
 * values, consult the यंत्र-sh/watchकरोg.h. Overload this at module load
 * समय.
 *
 * In order क्रम this to work reliably we need to have HZ set to 1000 or
 * something quite higher than 100 (or we need a proper high-res समयr
 * implementation that will deal with this properly), otherwise the 10ms
 * resolution of a jअगरfy is enough to trigger the overflow. For things like
 * the SH-4 and SH-5, this isn't necessarily that big of a problem, though
 * क्रम the SH-2 and SH-3, this isn't recommended unless the WDT is असलolutely
 * necssary.
 *
 * As a result of this timing problem, the only modes that are particularly
 * feasible are the 4096 and the 2048 भागisors, which yield 5.25 and 2.62ms
 * overflow periods respectively.
 *
 * Also, since we can't really expect userspace to be responsive enough
 * beक्रमe the overflow happens, we मुख्यtain two separate समयrs .. One in
 * the kernel क्रम clearing out WOVF every 2ms or so (again, this depends on
 * HZ == 1000), and another क्रम monitoring userspace ग_लिखोs to the WDT device.
 *
 * As such, we currently use a configurable heartbeat पूर्णांकerval which शेषs
 * to 30s. In this हाल, the userspace daemon is only responsible क्रम periodic
 * ग_लिखोs to the device beक्रमe the next heartbeat is scheduled. If the daemon
 * misses its deadline, the kernel समयr will allow the WDT to overflow.
 */
अटल पूर्णांक घड़ी_भागision_ratio = WTCSR_CKS_4096;
#घोषणा next_ping_period(cks)	(jअगरfies + msecs_to_jअगरfies(cks - 4))

#घोषणा WATCHDOG_HEARTBEAT 30			/* 30 sec शेष heartbeat */
अटल पूर्णांक heartbeat = WATCHDOG_HEARTBEAT;	/* in seconds */
अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल अचिन्हित दीर्घ next_heartbeat;

काष्ठा sh_wdt अणु
	व्योम __iomem		*base;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	spinlock_t		lock;

	काष्ठा समयr_list	समयr;
पूर्ण;

अटल पूर्णांक sh_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा sh_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ flags;
	u8 csr;

	pm_runसमय_get_sync(wdt->dev);
	clk_enable(wdt->clk);

	spin_lock_irqsave(&wdt->lock, flags);

	next_heartbeat = jअगरfies + (heartbeat * HZ);
	mod_समयr(&wdt->समयr, next_ping_period(घड़ी_भागision_ratio));

	csr = sh_wdt_पढ़ो_csr();
	csr |= WTCSR_WT | घड़ी_भागision_ratio;
	sh_wdt_ग_लिखो_csr(csr);

	sh_wdt_ग_लिखो_cnt(0);

	/*
	 * These processors have a bit of an inconsistent initialization
	 * process.. starting with SH-3, RSTS was moved to WTCSR, and the
	 * RSTCSR रेजिस्टर was हटाओd.
	 *
	 * On the SH-2 however, in addition with bits being in dअगरferent
	 * locations, we must deal with RSTCSR outright..
	 */
	csr = sh_wdt_पढ़ो_csr();
	csr |= WTCSR_TME;
	csr &= ~WTCSR_RSTS;
	sh_wdt_ग_लिखो_csr(csr);

#अगर_घोषित CONFIG_CPU_SH2
	csr = sh_wdt_पढ़ो_rstcsr();
	csr &= ~RSTCSR_RSTS;
	sh_wdt_ग_लिखो_rstcsr(csr);
#पूर्ण_अगर
	spin_unlock_irqrestore(&wdt->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा sh_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ flags;
	u8 csr;

	spin_lock_irqsave(&wdt->lock, flags);

	del_समयr(&wdt->समयr);

	csr = sh_wdt_पढ़ो_csr();
	csr &= ~WTCSR_TME;
	sh_wdt_ग_लिखो_csr(csr);

	spin_unlock_irqrestore(&wdt->lock, flags);

	clk_disable(wdt->clk);
	pm_runसमय_put_sync(wdt->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_wdt_keepalive(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा sh_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdt->lock, flags);
	next_heartbeat = jअगरfies + (heartbeat * HZ);
	spin_unlock_irqrestore(&wdt->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_wdt_set_heartbeat(काष्ठा watchकरोg_device *wdt_dev, अचिन्हित t)
अणु
	काष्ठा sh_wdt *wdt = watchकरोg_get_drvdata(wdt_dev);
	अचिन्हित दीर्घ flags;

	अगर (unlikely(t < 1 || t > 3600)) /* arbitrary upper limit */
		वापस -EINVAL;

	spin_lock_irqsave(&wdt->lock, flags);
	heartbeat = t;
	wdt_dev->समयout = t;
	spin_unlock_irqrestore(&wdt->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sh_wdt_ping(काष्ठा समयr_list *t)
अणु
	काष्ठा sh_wdt *wdt = from_समयr(wdt, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdt->lock, flags);
	अगर (समय_beक्रमe(jअगरfies, next_heartbeat)) अणु
		u8 csr;

		csr = sh_wdt_पढ़ो_csr();
		csr &= ~WTCSR_IOVF;
		sh_wdt_ग_लिखो_csr(csr);

		sh_wdt_ग_लिखो_cnt(0);

		mod_समयr(&wdt->समयr, next_ping_period(घड़ी_भागision_ratio));
	पूर्ण अन्यथा
		dev_warn(wdt->dev, "Heartbeat lost! Will not ping "
		         "the watchdog\n");
	spin_unlock_irqrestore(&wdt->lock, flags);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sh_wdt_info = अणु
	.options		= WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT |
				  WDIOF_MAGICCLOSE,
	.firmware_version	= 1,
	.identity		= "SH WDT",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops sh_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= sh_wdt_start,
	.stop		= sh_wdt_stop,
	.ping		= sh_wdt_keepalive,
	.set_समयout	= sh_wdt_set_heartbeat,
पूर्ण;

अटल काष्ठा watchकरोg_device sh_wdt_dev = अणु
	.info	= &sh_wdt_info,
	.ops	= &sh_wdt_ops,
पूर्ण;

अटल पूर्णांक sh_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_wdt *wdt;
	पूर्णांक rc;

	/*
	 * As this driver only covers the global watchकरोg हाल, reject
	 * any attempts to रेजिस्टर per-CPU watchकरोgs.
	 */
	अगर (pdev->id != -1)
		वापस -EINVAL;

	wdt = devm_kzalloc(&pdev->dev, माप(काष्ठा sh_wdt), GFP_KERNEL);
	अगर (unlikely(!wdt))
		वापस -ENOMEM;

	wdt->dev = &pdev->dev;

	wdt->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(wdt->clk)) अणु
		/*
		 * Clock framework support is optional, जारी on
		 * anyways अगर we करोn't find a matching घड़ी.
		 */
		wdt->clk = शून्य;
	पूर्ण

	wdt->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wdt->base))
		वापस PTR_ERR(wdt->base);

	watchकरोg_set_nowayout(&sh_wdt_dev, nowayout);
	watchकरोg_set_drvdata(&sh_wdt_dev, wdt);
	sh_wdt_dev.parent = &pdev->dev;

	spin_lock_init(&wdt->lock);

	rc = sh_wdt_set_heartbeat(&sh_wdt_dev, heartbeat);
	अगर (unlikely(rc)) अणु
		/* Default समयout अगर invalid */
		sh_wdt_set_heartbeat(&sh_wdt_dev, WATCHDOG_HEARTBEAT);

		dev_warn(&pdev->dev,
			 "heartbeat value must be 1<=x<=3600, using %d\n",
			 sh_wdt_dev.समयout);
	पूर्ण

	dev_info(&pdev->dev, "configured with heartbeat=%d sec (nowayout=%d)\n",
		 sh_wdt_dev.समयout, nowayout);

	rc = watchकरोg_रेजिस्टर_device(&sh_wdt_dev);
	अगर (unlikely(rc)) अणु
		dev_err(&pdev->dev, "Can't register watchdog (err=%d)\n", rc);
		वापस rc;
	पूर्ण

	समयr_setup(&wdt->समयr, sh_wdt_ping, 0);
	wdt->समयr.expires	= next_ping_period(घड़ी_भागision_ratio);

	dev_info(&pdev->dev, "initialized.\n");

	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	watchकरोg_unरेजिस्टर_device(&sh_wdt_dev);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम sh_wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	sh_wdt_stop(&sh_wdt_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver sh_wdt_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,

	.probe		= sh_wdt_probe,
	.हटाओ		= sh_wdt_हटाओ,
	.shutकरोwn	= sh_wdt_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init sh_wdt_init(व्योम)
अणु
	अगर (unlikely(घड़ी_भागision_ratio < 0x5 ||
		     घड़ी_भागision_ratio > 0x7)) अणु
		घड़ी_भागision_ratio = WTCSR_CKS_4096;

		pr_info("divisor must be 0x5<=x<=0x7, using %d\n",
			घड़ी_भागision_ratio);
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&sh_wdt_driver);
पूर्ण

अटल व्योम __निकास sh_wdt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sh_wdt_driver);
पूर्ण
module_init(sh_wdt_init);
module_निकास(sh_wdt_निकास);

MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>");
MODULE_DESCRIPTION("SuperH watchdog driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);

module_param(घड़ी_भागision_ratio, पूर्णांक, 0);
MODULE_PARM_DESC(घड़ी_भागision_ratio,
	"Clock division ratio. Valid ranges are from 0x5 (1.31ms) "
	"to 0x7 (5.25ms). (default=" __MODULE_STRING(WTCSR_CKS_4096) ")");

module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
	"Watchdog heartbeat in seconds. (1 <= heartbeat <= 3600, default="
				__MODULE_STRING(WATCHDOG_HEARTBEAT) ")");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
