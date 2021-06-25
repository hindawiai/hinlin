<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	SoftDog:	A Software Watchकरोg Device
 *
 *	(c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *							All Rights Reserved.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Software only watchकरोg driver. Unlike its big brother the WDT501P
 *	driver this won't always recover a failed machine.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hrसमयr.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/reboot.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/workqueue.h>

#घोषणा TIMER_MARGIN	60		/* Default is 60 seconds */
अटल अचिन्हित पूर्णांक soft_margin = TIMER_MARGIN;	/* in seconds */
module_param(soft_margin, uपूर्णांक, 0);
MODULE_PARM_DESC(soft_margin,
	"Watchdog soft_margin in seconds. (0 < soft_margin < 65536, default="
					__MODULE_STRING(TIMER_MARGIN) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक soft_noboot;
module_param(soft_noboot, पूर्णांक, 0);
MODULE_PARM_DESC(soft_noboot,
	"Softdog action, set to 1 to ignore reboots, 0 to reboot (default=0)");

अटल पूर्णांक soft_panic;
module_param(soft_panic, पूर्णांक, 0);
MODULE_PARM_DESC(soft_panic,
	"Softdog action, set to 1 to panic, 0 to reboot (default=0)");

अटल अक्षर *soft_reboot_cmd;
module_param(soft_reboot_cmd, अक्षरp, 0000);
MODULE_PARM_DESC(soft_reboot_cmd,
	"Set reboot command. Emergency reboot takes place if unset");

अटल bool soft_active_on_boot;
module_param(soft_active_on_boot, bool, 0000);
MODULE_PARM_DESC(soft_active_on_boot,
	"Set to true to active Softdog on boot (default=false)");

अटल काष्ठा hrसमयr softकरोg_ticktock;
अटल काष्ठा hrसमयr softकरोg_preticktock;

अटल पूर्णांक reboot_kthपढ़ो_fn(व्योम *data)
अणु
	kernel_restart(soft_reboot_cmd);
	वापस -EPERM; /* Should not reach here */
पूर्ण

अटल व्योम reboot_work_fn(काष्ठा work_काष्ठा *unused)
अणु
	kthपढ़ो_run(reboot_kthपढ़ो_fn, शून्य, "softdog_reboot");
पूर्ण

अटल क्रमागत hrसमयr_restart softकरोg_fire(काष्ठा hrसमयr *समयr)
अणु
	अटल bool soft_reboot_fired;

	module_put(THIS_MODULE);
	अगर (soft_noboot) अणु
		pr_crit("Triggered - Reboot ignored\n");
	पूर्ण अन्यथा अगर (soft_panic) अणु
		pr_crit("Initiating panic\n");
		panic("Software Watchdog Timer expired");
	पूर्ण अन्यथा अणु
		pr_crit("Initiating system reboot\n");
		अगर (!soft_reboot_fired && soft_reboot_cmd != शून्य) अणु
			अटल DECLARE_WORK(reboot_work, reboot_work_fn);
			/*
			 * The 'kernel_restart' is a 'might-sleep' operation.
			 * Also, executing it in प्रणाली-wide workqueues blocks
			 * any driver from using the same workqueue in its
			 * shutकरोwn callback function. Thus, we should execute
			 * the 'kernel_restart' in a standalone kernel thपढ़ो.
			 * But since starting a kernel thपढ़ो is also a
			 * 'might-sleep' operation, so the 'reboot_work' is
			 * required as a launcher of the kernel thपढ़ो.
			 *
			 * After request the reboot, restart the समयr to
			 * schedule an 'emergency_restart' reboot after
			 * 'TIMER_MARGIN' seconds. It's because अगर the softकरोg
			 * hangs, it might be because of scheduling issues. And
			 * अगर that is the हाल, both 'schedule_work' and
			 * 'kernel_restart' may possibly be malfunctional at the
			 * same समय.
			 */
			soft_reboot_fired = true;
			schedule_work(&reboot_work);
			hrसमयr_add_expires_ns(समयr,
					(u64)TIMER_MARGIN * NSEC_PER_SEC);

			वापस HRTIMER_RESTART;
		पूर्ण
		emergency_restart();
		pr_crit("Reboot didn't ?????\n");
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

अटल काष्ठा watchकरोg_device softकरोg_dev;

अटल क्रमागत hrसमयr_restart softकरोg_preसमयout(काष्ठा hrसमयr *समयr)
अणु
	watchकरोg_notअगरy_preसमयout(&softकरोg_dev);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक softकरोg_ping(काष्ठा watchकरोg_device *w)
अणु
	अगर (!hrसमयr_active(&softकरोg_ticktock))
		__module_get(THIS_MODULE);
	hrसमयr_start(&softकरोg_ticktock, kसमय_set(w->समयout, 0),
		      HRTIMER_MODE_REL);

	अगर (IS_ENABLED(CONFIG_SOFT_WATCHDOG_PRETIMEOUT)) अणु
		अगर (w->preसमयout)
			hrसमयr_start(&softकरोg_preticktock,
				      kसमय_set(w->समयout - w->preसमयout, 0),
				      HRTIMER_MODE_REL);
		अन्यथा
			hrसमयr_cancel(&softकरोg_preticktock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक softकरोg_stop(काष्ठा watchकरोg_device *w)
अणु
	अगर (hrसमयr_cancel(&softकरोg_ticktock))
		module_put(THIS_MODULE);

	अगर (IS_ENABLED(CONFIG_SOFT_WATCHDOG_PRETIMEOUT))
		hrसमयr_cancel(&softकरोg_preticktock);

	वापस 0;
पूर्ण

अटल काष्ठा watchकरोg_info softकरोg_info = अणु
	.identity = "Software Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops softकरोg_ops = अणु
	.owner = THIS_MODULE,
	.start = softकरोg_ping,
	.stop = softकरोg_stop,
पूर्ण;

अटल काष्ठा watchकरोg_device softकरोg_dev = अणु
	.info = &softकरोg_info,
	.ops = &softकरोg_ops,
	.min_समयout = 1,
	.max_समयout = 65535,
	.समयout = TIMER_MARGIN,
पूर्ण;

अटल पूर्णांक __init softकरोg_init(व्योम)
अणु
	पूर्णांक ret;

	watchकरोg_init_समयout(&softकरोg_dev, soft_margin, शून्य);
	watchकरोg_set_nowayout(&softकरोg_dev, nowayout);
	watchकरोg_stop_on_reboot(&softकरोg_dev);

	hrसमयr_init(&softकरोg_ticktock, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	softकरोg_ticktock.function = softकरोg_fire;

	अगर (IS_ENABLED(CONFIG_SOFT_WATCHDOG_PRETIMEOUT)) अणु
		softकरोg_info.options |= WDIOF_PRETIMEOUT;
		hrसमयr_init(&softकरोg_preticktock, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		softकरोg_preticktock.function = softकरोg_preसमयout;
	पूर्ण

	अगर (soft_active_on_boot)
		softकरोg_ping(&softकरोg_dev);

	ret = watchकरोg_रेजिस्टर_device(&softकरोg_dev);
	अगर (ret)
		वापस ret;

	pr_info("initialized. soft_noboot=%d soft_margin=%d sec soft_panic=%d (nowayout=%d)\n",
		soft_noboot, softकरोg_dev.समयout, soft_panic, nowayout);
	pr_info("             soft_reboot_cmd=%s soft_active_on_boot=%d\n",
		soft_reboot_cmd ?: "<not set>", soft_active_on_boot);

	वापस 0;
पूर्ण
module_init(softकरोg_init);

अटल व्योम __निकास softकरोg_निकास(व्योम)
अणु
	watchकरोg_unरेजिस्टर_device(&softकरोg_dev);
पूर्ण
module_निकास(softकरोg_निकास);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("Software Watchdog Device Driver");
MODULE_LICENSE("GPL");
