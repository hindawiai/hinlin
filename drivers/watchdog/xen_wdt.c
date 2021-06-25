<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Xen Watchकरोg Driver
 *
 *	(c) Copyright 2010 Novell, Inc.
 */

#घोषणा DRV_NAME	"xen_wdt"

#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/watchकरोg.h>
#समावेश <xen/xen.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <xen/पूर्णांकerface/sched.h>

अटल काष्ठा platक्रमm_device *platक्रमm_device;
अटल काष्ठा sched_watchकरोg wdt;
अटल समय64_t wdt_expires;

#घोषणा WATCHDOG_TIMEOUT 60 /* in seconds */
अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds "
	"(default=" __MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, S_IRUGO);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल अंतरभूत समय64_t set_समयout(काष्ठा watchकरोg_device *wdd)
अणु
	wdt.समयout = wdd->समयout;
	वापस kसमय_get_seconds() + wdd->समयout;
पूर्ण

अटल पूर्णांक xen_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	समय64_t expires;
	पूर्णांक err;

	expires = set_समयout(wdd);
	अगर (!wdt.id)
		err = HYPERVISOR_sched_op(SCHEDOP_watchकरोg, &wdt);
	अन्यथा
		err = -EBUSY;
	अगर (err > 0) अणु
		wdt.id = err;
		wdt_expires = expires;
		err = 0;
	पूर्ण अन्यथा
		BUG_ON(!err);

	वापस err;
पूर्ण

अटल पूर्णांक xen_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक err = 0;

	wdt.समयout = 0;
	अगर (wdt.id)
		err = HYPERVISOR_sched_op(SCHEDOP_watchकरोg, &wdt);
	अगर (!err)
		wdt.id = 0;

	वापस err;
पूर्ण

अटल पूर्णांक xen_wdt_kick(काष्ठा watchकरोg_device *wdd)
अणु
	समय64_t expires;
	पूर्णांक err;

	expires = set_समयout(wdd);
	अगर (wdt.id)
		err = HYPERVISOR_sched_op(SCHEDOP_watchकरोg, &wdt);
	अन्यथा
		err = -ENXIO;
	अगर (!err)
		wdt_expires = expires;

	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक xen_wdt_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	वापस wdt_expires - kसमय_get_seconds();
पूर्ण

अटल काष्ठा watchकरोg_info xen_wdt_info = अणु
	.identity = DRV_NAME,
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops xen_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = xen_wdt_start,
	.stop = xen_wdt_stop,
	.ping = xen_wdt_kick,
	.get_समयleft = xen_wdt_get_समयleft,
पूर्ण;

अटल काष्ठा watchकरोg_device xen_wdt_dev = अणु
	.info = &xen_wdt_info,
	.ops = &xen_wdt_ops,
	.समयout = WATCHDOG_TIMEOUT,
पूर्ण;

अटल पूर्णांक xen_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sched_watchकरोg wd = अणु .id = ~0 पूर्ण;
	पूर्णांक ret = HYPERVISOR_sched_op(SCHEDOP_watchकरोg, &wd);

	अगर (ret == -ENOSYS) अणु
		dev_err(dev, "watchdog not supported by hypervisor\n");
		वापस -ENODEV;
	पूर्ण

	अगर (ret != -EINVAL) अणु
		dev_err(dev, "unexpected hypervisor error (%d)\n", ret);
		वापस -ENODEV;
	पूर्ण

	watchकरोg_init_समयout(&xen_wdt_dev, समयout, शून्य);
	watchकरोg_set_nowayout(&xen_wdt_dev, nowayout);
	watchकरोg_stop_on_reboot(&xen_wdt_dev);
	watchकरोg_stop_on_unरेजिस्टर(&xen_wdt_dev);

	ret = devm_watchकरोg_रेजिस्टर_device(dev, &xen_wdt_dev);
	अगर (ret)
		वापस ret;

	dev_info(dev, "initialized (timeout=%ds, nowayout=%d)\n",
		 xen_wdt_dev.समयout, nowayout);

	वापस 0;
पूर्ण

अटल पूर्णांक xen_wdt_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	typeof(wdt.id) id = wdt.id;
	पूर्णांक rc = xen_wdt_stop(&xen_wdt_dev);

	wdt.id = id;
	वापस rc;
पूर्ण

अटल पूर्णांक xen_wdt_resume(काष्ठा platक्रमm_device *dev)
अणु
	अगर (!wdt.id)
		वापस 0;
	wdt.id = 0;
	वापस xen_wdt_start(&xen_wdt_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver xen_wdt_driver = अणु
	.probe          = xen_wdt_probe,
	.suspend        = xen_wdt_suspend,
	.resume         = xen_wdt_resume,
	.driver         = अणु
		.name   = DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xen_wdt_init_module(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&xen_wdt_driver);
	अगर (err)
		वापस err;

	platक्रमm_device = platक्रमm_device_रेजिस्टर_simple(DRV_NAME,
								  -1, शून्य, 0);
	अगर (IS_ERR(platक्रमm_device)) अणु
		err = PTR_ERR(platक्रमm_device);
		platक्रमm_driver_unरेजिस्टर(&xen_wdt_driver);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास xen_wdt_cleanup_module(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&xen_wdt_driver);
पूर्ण

module_init(xen_wdt_init_module);
module_निकास(xen_wdt_cleanup_module);

MODULE_AUTHOR("Jan Beulich <jbeulich@novell.com>");
MODULE_DESCRIPTION("Xen WatchDog Timer Driver");
MODULE_LICENSE("GPL");
