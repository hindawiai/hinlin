<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	watchकरोg_core.c
 *
 *	(c) Copyright 2008-2011 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	(c) Copyright 2008-2011 Wim Van Sebroeck <wim@iguana.be>.
 *
 *	This source code is part of the generic code that can be used
 *	by all the watchकरोg समयr drivers.
 *
 *	Based on source code of the following authors:
 *	  Matt Domsch <Matt_Domsch@dell.com>,
 *	  Rob Radez <rob@osinvestor.com>,
 *	  Rusty Lynch <rusty@linux.co.पूर्णांकel.com>
 *	  Satyam Sharma <satyam@infradead.org>
 *	  Randy Dunlap <अक्रमy.dunlap@oracle.com>
 *
 *	Neither Alan Cox, CymruNet Ltd., Wim Van Sebroeck nor Iguana vzw.
 *	admit liability nor provide warranty क्रम any of this software.
 *	This material is provided "AS-IS" and at no अक्षरge.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>	/* For EXPORT_SYMBOL/module stuff/... */
#समावेश <linux/types.h>	/* For standard types */
#समावेश <linux/त्रुटिसं.स>	/* For the -ENODEV/... values */
#समावेश <linux/kernel.h>	/* For prपूर्णांकk/panic/... */
#समावेश <linux/reboot.h>	/* For restart handler */
#समावेश <linux/watchकरोg.h>	/* For watchकरोg specअगरic items */
#समावेश <linux/init.h>		/* For __init/__निकास/... */
#समावेश <linux/idr.h>		/* For ida_* macros */
#समावेश <linux/err.h>		/* For IS_ERR macros */
#समावेश <linux/of.h>		/* For of_get_समयout_sec */

#समावेश "watchdog_core.h"	/* For watchकरोg_dev_रेजिस्टर/... */

अटल DEFINE_IDA(watchकरोg_ida);

अटल पूर्णांक stop_on_reboot = -1;
module_param(stop_on_reboot, पूर्णांक, 0444);
MODULE_PARM_DESC(stop_on_reboot, "Stop watchdogs on reboot (0=keep watching, 1=stop)");

/*
 * Deferred Registration infraकाष्ठाure.
 *
 * Someबार watchकरोg drivers needs to be loaded as soon as possible,
 * क्रम example when it's impossible to disable it. To करो so,
 * raising the initcall level of the watchकरोg driver is a solution.
 * But in such हाल, the miscdev is maybe not पढ़ोy (subsys_initcall), and
 * watchकरोg_core need miscdev to रेजिस्टर the watchकरोg as a अक्षर device.
 *
 * The deferred registration infraकाष्ठाure offer a way क्रम the watchकरोg
 * subप्रणाली to रेजिस्टर a watchकरोg properly, even beक्रमe miscdev is पढ़ोy.
 */

अटल DEFINE_MUTEX(wtd_deferred_reg_mutex);
अटल LIST_HEAD(wtd_deferred_reg_list);
अटल bool wtd_deferred_reg_करोne;

अटल व्योम watchकरोg_deferred_registration_add(काष्ठा watchकरोg_device *wdd)
अणु
	list_add_tail(&wdd->deferred,
		      &wtd_deferred_reg_list);
पूर्ण

अटल व्योम watchकरोg_deferred_registration_del(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा list_head *p, *n;
	काष्ठा watchकरोg_device *wdd_पंचांगp;

	list_क्रम_each_safe(p, n, &wtd_deferred_reg_list) अणु
		wdd_पंचांगp = list_entry(p, काष्ठा watchकरोg_device,
				     deferred);
		अगर (wdd_पंचांगp == wdd) अणु
			list_del(&wdd_पंचांगp->deferred);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम watchकरोg_check_min_max_समयout(काष्ठा watchकरोg_device *wdd)
अणु
	/*
	 * Check that we have valid min and max समयout values, अगर
	 * not reset them both to 0 (=not used or unknown)
	 */
	अगर (!wdd->max_hw_heartbeat_ms && wdd->min_समयout > wdd->max_समयout) अणु
		pr_info("Invalid min and max timeout values, resetting to 0!\n");
		wdd->min_समयout = 0;
		wdd->max_समयout = 0;
	पूर्ण
पूर्ण

/**
 * watchकरोg_init_समयout() - initialize the समयout field
 * @wdd: watchकरोg device
 * @समयout_parm: समयout module parameter
 * @dev: Device that stores the समयout-sec property
 *
 * Initialize the समयout field of the watchकरोg_device काष्ठा with either the
 * समयout module parameter (अगर it is valid value) or the समयout-sec property
 * (only अगर it is a valid value and the समयout_parm is out of bounds).
 * If none of them are valid then we keep the old value (which should normally
 * be the शेष समयout value). Note that क्रम the module parameter, '0' means
 * 'use default' जबतक it is an invalid value क्रम the समयout-sec property.
 * It should simply be dropped अगर you want to use the शेष value then.
 *
 * A zero is वापसed on success or -EINVAL अगर all provided values are out of
 * bounds.
 */
पूर्णांक watchकरोg_init_समयout(काष्ठा watchकरोg_device *wdd,
				अचिन्हित पूर्णांक समयout_parm, काष्ठा device *dev)
अणु
	स्थिर अक्षर *dev_str = wdd->parent ? dev_name(wdd->parent) :
			      (स्थिर अक्षर *)wdd->info->identity;
	अचिन्हित पूर्णांक t = 0;
	पूर्णांक ret = 0;

	watchकरोg_check_min_max_समयout(wdd);

	/* check the driver supplied value (likely a module parameter) first */
	अगर (समयout_parm) अणु
		अगर (!watchकरोg_समयout_invalid(wdd, समयout_parm)) अणु
			wdd->समयout = समयout_parm;
			वापस 0;
		पूर्ण
		pr_err("%s: driver supplied timeout (%u) out of range\n",
			dev_str, समयout_parm);
		ret = -EINVAL;
	पूर्ण

	/* try to get the समयout_sec property */
	अगर (dev && dev->of_node &&
	    of_property_पढ़ो_u32(dev->of_node, "timeout-sec", &t) == 0) अणु
		अगर (t && !watchकरोg_समयout_invalid(wdd, t)) अणु
			wdd->समयout = t;
			वापस 0;
		पूर्ण
		pr_err("%s: DT supplied timeout (%u) out of range\n", dev_str, t);
		ret = -EINVAL;
	पूर्ण

	अगर (ret < 0 && wdd->समयout)
		pr_warn("%s: falling back to default timeout (%u)\n", dev_str,
			wdd->समयout);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(watchकरोg_init_समयout);

अटल पूर्णांक watchकरोg_reboot_notअगरier(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ code, व्योम *data)
अणु
	काष्ठा watchकरोg_device *wdd;

	wdd = container_of(nb, काष्ठा watchकरोg_device, reboot_nb);
	अगर (code == SYS_DOWN || code == SYS_HALT) अणु
		अगर (watchकरोg_active(wdd) || watchकरोg_hw_running(wdd)) अणु
			पूर्णांक ret;

			ret = wdd->ops->stop(wdd);
			अगर (ret)
				वापस NOTIFY_BAD;
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक watchकरोg_restart_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा watchकरोg_device *wdd = container_of(nb, काष्ठा watchकरोg_device,
						   restart_nb);

	पूर्णांक ret;

	ret = wdd->ops->restart(wdd, action, data);
	अगर (ret)
		वापस NOTIFY_BAD;

	वापस NOTIFY_DONE;
पूर्ण

/**
 * watchकरोg_set_restart_priority - Change priority of restart handler
 * @wdd: watchकरोg device
 * @priority: priority of the restart handler, should follow these guidelines:
 *   0:   use watchकरोg's restart function as last resort, has limited restart
 *        capabilies
 *   128: शेष restart handler, use अगर no other handler is expected to be
 *        available and/or अगर restart is sufficient to restart the entire प्रणाली
 *   255: preempt all other handlers
 *
 * If a wdd->ops->restart function is provided when watchकरोg_रेजिस्टर_device is
 * called, it will be रेजिस्टरed as a restart handler with the priority given
 * here.
 */
व्योम watchकरोg_set_restart_priority(काष्ठा watchकरोg_device *wdd, पूर्णांक priority)
अणु
	wdd->restart_nb.priority = priority;
पूर्ण
EXPORT_SYMBOL_GPL(watchकरोg_set_restart_priority);

अटल पूर्णांक __watchकरोg_रेजिस्टर_device(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक ret, id = -1;

	अगर (wdd == शून्य || wdd->info == शून्य || wdd->ops == शून्य)
		वापस -EINVAL;

	/* Mandatory operations need to be supported */
	अगर (!wdd->ops->start || (!wdd->ops->stop && !wdd->max_hw_heartbeat_ms))
		वापस -EINVAL;

	watchकरोg_check_min_max_समयout(wdd);

	/*
	 * Note: now that all watchकरोg_device data has been verअगरied, we
	 * will not check this anymore in other functions. If data माला_लो
	 * corrupted in a later stage then we expect a kernel panic!
	 */

	/* Use alias क्रम watchकरोg id अगर possible */
	अगर (wdd->parent) अणु
		ret = of_alias_get_id(wdd->parent->of_node, "watchdog");
		अगर (ret >= 0)
			id = ida_simple_get(&watchकरोg_ida, ret,
					    ret + 1, GFP_KERNEL);
	पूर्ण

	अगर (id < 0)
		id = ida_simple_get(&watchकरोg_ida, 0, MAX_DOGS, GFP_KERNEL);

	अगर (id < 0)
		वापस id;
	wdd->id = id;

	ret = watchकरोg_dev_रेजिस्टर(wdd);
	अगर (ret) अणु
		ida_simple_हटाओ(&watchकरोg_ida, id);
		अगर (!(id == 0 && ret == -EBUSY))
			वापस ret;

		/* Retry in हाल a legacy watchकरोg module exists */
		id = ida_simple_get(&watchकरोg_ida, 1, MAX_DOGS, GFP_KERNEL);
		अगर (id < 0)
			वापस id;
		wdd->id = id;

		ret = watchकरोg_dev_रेजिस्टर(wdd);
		अगर (ret) अणु
			ida_simple_हटाओ(&watchकरोg_ida, id);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Module parameter to क्रमce watchकरोg policy on reboot. */
	अगर (stop_on_reboot != -1) अणु
		अगर (stop_on_reboot)
			set_bit(WDOG_STOP_ON_REBOOT, &wdd->status);
		अन्यथा
			clear_bit(WDOG_STOP_ON_REBOOT, &wdd->status);
	पूर्ण

	अगर (test_bit(WDOG_STOP_ON_REBOOT, &wdd->status)) अणु
		अगर (!wdd->ops->stop)
			pr_warn("watchdog%d: stop_on_reboot not supported\n", wdd->id);
		अन्यथा अणु
			wdd->reboot_nb.notअगरier_call = watchकरोg_reboot_notअगरier;

			ret = रेजिस्टर_reboot_notअगरier(&wdd->reboot_nb);
			अगर (ret) अणु
				pr_err("watchdog%d: Cannot register reboot notifier (%d)\n",
					wdd->id, ret);
				watchकरोg_dev_unरेजिस्टर(wdd);
				ida_simple_हटाओ(&watchकरोg_ida, id);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (wdd->ops->restart) अणु
		wdd->restart_nb.notअगरier_call = watchकरोg_restart_notअगरier;

		ret = रेजिस्टर_restart_handler(&wdd->restart_nb);
		अगर (ret)
			pr_warn("watchdog%d: Cannot register restart handler (%d)\n",
				wdd->id, ret);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * watchकरोg_रेजिस्टर_device() - रेजिस्टर a watchकरोg device
 * @wdd: watchकरोg device
 *
 * Register a watchकरोg device with the kernel so that the
 * watchकरोg समयr can be accessed from userspace.
 *
 * A zero is वापसed on success and a negative त्रुटि_सं code क्रम
 * failure.
 */

पूर्णांक watchकरोg_रेजिस्टर_device(काष्ठा watchकरोg_device *wdd)
अणु
	स्थिर अक्षर *dev_str;
	पूर्णांक ret = 0;

	mutex_lock(&wtd_deferred_reg_mutex);
	अगर (wtd_deferred_reg_करोne)
		ret = __watchकरोg_रेजिस्टर_device(wdd);
	अन्यथा
		watchकरोg_deferred_registration_add(wdd);
	mutex_unlock(&wtd_deferred_reg_mutex);

	अगर (ret) अणु
		dev_str = wdd->parent ? dev_name(wdd->parent) :
			  (स्थिर अक्षर *)wdd->info->identity;
		pr_err("%s: failed to register watchdog device (err = %d)\n",
			dev_str, ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(watchकरोg_रेजिस्टर_device);

अटल व्योम __watchकरोg_unरेजिस्टर_device(काष्ठा watchकरोg_device *wdd)
अणु
	अगर (wdd == शून्य)
		वापस;

	अगर (wdd->ops->restart)
		unरेजिस्टर_restart_handler(&wdd->restart_nb);

	अगर (test_bit(WDOG_STOP_ON_REBOOT, &wdd->status))
		unरेजिस्टर_reboot_notअगरier(&wdd->reboot_nb);

	watchकरोg_dev_unरेजिस्टर(wdd);
	ida_simple_हटाओ(&watchकरोg_ida, wdd->id);
पूर्ण

/**
 * watchकरोg_unरेजिस्टर_device() - unरेजिस्टर a watchकरोg device
 * @wdd: watchकरोg device to unरेजिस्टर
 *
 * Unरेजिस्टर a watchकरोg device that was previously successfully
 * रेजिस्टरed with watchकरोg_रेजिस्टर_device().
 */

व्योम watchकरोg_unरेजिस्टर_device(काष्ठा watchकरोg_device *wdd)
अणु
	mutex_lock(&wtd_deferred_reg_mutex);
	अगर (wtd_deferred_reg_करोne)
		__watchकरोg_unरेजिस्टर_device(wdd);
	अन्यथा
		watchकरोg_deferred_registration_del(wdd);
	mutex_unlock(&wtd_deferred_reg_mutex);
पूर्ण

EXPORT_SYMBOL_GPL(watchकरोg_unरेजिस्टर_device);

अटल व्योम devm_watchकरोg_unरेजिस्टर_device(काष्ठा device *dev, व्योम *res)
अणु
	watchकरोg_unरेजिस्टर_device(*(काष्ठा watchकरोg_device **)res);
पूर्ण

/**
 * devm_watchकरोg_रेजिस्टर_device() - resource managed watchकरोg_रेजिस्टर_device()
 * @dev: device that is रेजिस्टरing this watchकरोg device
 * @wdd: watchकरोg device
 *
 * Managed watchकरोg_रेजिस्टर_device(). For watchकरोg device रेजिस्टरed by this
 * function,  watchकरोg_unरेजिस्टर_device() is स्वतःmatically called on driver
 * detach. See watchकरोg_रेजिस्टर_device() क्रम more inक्रमmation.
 */
पूर्णांक devm_watchकरोg_रेजिस्टर_device(काष्ठा device *dev,
				काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_device **rcwdd;
	पूर्णांक ret;

	rcwdd = devres_alloc(devm_watchकरोg_unरेजिस्टर_device, माप(*rcwdd),
			     GFP_KERNEL);
	अगर (!rcwdd)
		वापस -ENOMEM;

	ret = watchकरोg_रेजिस्टर_device(wdd);
	अगर (!ret) अणु
		*rcwdd = wdd;
		devres_add(dev, rcwdd);
	पूर्ण अन्यथा अणु
		devres_मुक्त(rcwdd);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_watchकरोg_रेजिस्टर_device);

अटल पूर्णांक __init watchकरोg_deferred_registration(व्योम)
अणु
	mutex_lock(&wtd_deferred_reg_mutex);
	wtd_deferred_reg_करोne = true;
	जबतक (!list_empty(&wtd_deferred_reg_list)) अणु
		काष्ठा watchकरोg_device *wdd;

		wdd = list_first_entry(&wtd_deferred_reg_list,
				       काष्ठा watchकरोg_device, deferred);
		list_del(&wdd->deferred);
		__watchकरोg_रेजिस्टर_device(wdd);
	पूर्ण
	mutex_unlock(&wtd_deferred_reg_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक __init watchकरोg_init(व्योम)
अणु
	पूर्णांक err;

	err = watchकरोg_dev_init();
	अगर (err < 0)
		वापस err;

	watchकरोg_deferred_registration();
	वापस 0;
पूर्ण

अटल व्योम __निकास watchकरोg_निकास(व्योम)
अणु
	watchकरोg_dev_निकास();
	ida_destroy(&watchकरोg_ida);
पूर्ण

subsys_initcall_sync(watchकरोg_init);
module_निकास(watchकरोg_निकास);

MODULE_AUTHOR("Alan Cox <alan@lxorguk.ukuu.org.uk>");
MODULE_AUTHOR("Wim Van Sebroeck <wim@iguana.be>");
MODULE_DESCRIPTION("WatchDog Timer Driver Core");
MODULE_LICENSE("GPL");
