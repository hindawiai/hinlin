<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	sun4v watchकरोg समयr
 *	(c) Copyright 2016 Oracle Corporation
 *
 *	Implement a simple watchकरोg driver using the built-in sun4v hypervisor
 *	watchकरोg support. If समय expires, the hypervisor stops or bounces
 *	the guest करोमुख्य.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/watchकरोg.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mdesc.h>

#घोषणा WDT_TIMEOUT			60
#घोषणा WDT_MAX_TIMEOUT			31536000
#घोषणा WDT_MIN_TIMEOUT			1
#घोषणा WDT_DEFAULT_RESOLUTION_MS	1000	/* 1 second */

अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds (default="
	__MODULE_STRING(WDT_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, S_IRUGO);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक sun4v_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	sun4v_mach_set_watchकरोg(0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4v_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक hverr;

	/*
	 * HV watchकरोg समयr will round up the समयout
	 * passed in to the nearest multiple of the
	 * watchकरोg resolution in milliseconds.
	 */
	hverr = sun4v_mach_set_watchकरोg(wdd->समयout * 1000, शून्य);
	अगर (hverr == HV_EINVAL)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4v_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				 अचिन्हित पूर्णांक समयout)
अणु
	wdd->समयout = समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info sun4v_wdt_ident = अणु
	.options =	WDIOF_SETTIMEOUT |
			WDIOF_MAGICCLOSE |
			WDIOF_KEEPALIVEPING,
	.identity =	"sun4v hypervisor watchdog",
	.firmware_version = 0,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops sun4v_wdt_ops = अणु
	.owner =	THIS_MODULE,
	.start =	sun4v_wdt_ping,
	.stop =		sun4v_wdt_stop,
	.ping =		sun4v_wdt_ping,
	.set_समयout =	sun4v_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device wdd = अणु
	.info = &sun4v_wdt_ident,
	.ops = &sun4v_wdt_ops,
	.min_समयout = WDT_MIN_TIMEOUT,
	.max_समयout = WDT_MAX_TIMEOUT,
	.समयout = WDT_TIMEOUT,
पूर्ण;

अटल पूर्णांक __init sun4v_wdt_init(व्योम)
अणु
	काष्ठा mdesc_handle *handle;
	u64 node;
	स्थिर u64 *value;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ major = 1, minor = 1;

	/*
	 * There are 2 properties that can be set from the control
	 * करोमुख्य क्रम the watchकरोg.
	 * watchकरोg-resolution
	 * watchकरोg-max-समयout
	 *
	 * We can expect a handle to be वापसed otherwise something
	 * serious is wrong. Correct to वापस -ENODEV here.
	 */

	handle = mdesc_grab();
	अगर (!handle)
		वापस -ENODEV;

	node = mdesc_node_by_name(handle, MDESC_NODE_शून्य, "platform");
	err = -ENODEV;
	अगर (node == MDESC_NODE_शून्य)
		जाओ out_release;

	/*
	 * This is a safe way to validate अगर we are on the right
	 * platक्रमm.
	 */
	अगर (sun4v_hvapi_रेजिस्टर(HV_GRP_CORE, major, &minor))
		जाओ out_hv_unreg;

	/* Allow value of watchकरोg-resolution up to 1s (शेष) */
	value = mdesc_get_property(handle, node, "watchdog-resolution", शून्य);
	err = -EINVAL;
	अगर (value) अणु
		अगर (*value == 0 ||
		    *value > WDT_DEFAULT_RESOLUTION_MS)
			जाओ out_hv_unreg;
	पूर्ण

	value = mdesc_get_property(handle, node, "watchdog-max-timeout", शून्य);
	अगर (value) अणु
		/*
		 * If the property value (in ms) is smaller than
		 * min_समयout, वापस -EINVAL.
		 */
		अगर (*value < wdd.min_समयout * 1000)
			जाओ out_hv_unreg;

		/*
		 * If the property value is smaller than
		 * शेष max_समयout  then set watchकरोg max_समयout to
		 * the value of the property in seconds.
		 */
		अगर (*value < wdd.max_समयout * 1000)
			wdd.max_समयout = *value  / 1000;
	पूर्ण

	watchकरोg_init_समयout(&wdd, समयout, शून्य);

	watchकरोg_set_nowayout(&wdd, nowayout);

	err = watchकरोg_रेजिस्टर_device(&wdd);
	अगर (err)
		जाओ out_hv_unreg;

	pr_info("initialized (timeout=%ds, nowayout=%d)\n",
		 wdd.समयout, nowayout);

	mdesc_release(handle);

	वापस 0;

out_hv_unreg:
	sun4v_hvapi_unरेजिस्टर(HV_GRP_CORE);

out_release:
	mdesc_release(handle);
	वापस err;
पूर्ण

अटल व्योम __निकास sun4v_wdt_निकास(व्योम)
अणु
	sun4v_hvapi_unरेजिस्टर(HV_GRP_CORE);
	watchकरोg_unरेजिस्टर_device(&wdd);
पूर्ण

module_init(sun4v_wdt_init);
module_निकास(sun4v_wdt_निकास);

MODULE_AUTHOR("Wim Coekaerts <wim.coekaerts@oracle.com>");
MODULE_DESCRIPTION("sun4v watchdog driver");
MODULE_LICENSE("GPL");
