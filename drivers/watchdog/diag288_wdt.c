<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Watchकरोg driver क्रम z/VM and LPAR using the diag 288 पूर्णांकerface.
 *
 * Under z/VM, expiration of the watchकरोg will send a "system restart" command
 * to CP.
 *
 * The command can be altered using the module parameter "cmd". This is
 * not recommended because it's only supported on z/VM but not whith LPAR.
 *
 * On LPAR, the watchकरोg will always trigger a प्रणाली restart. the module
 * paramter cmd is meaningless here.
 *
 *
 * Copyright IBM Corp. 2004, 2013
 * Author(s): Arnd Bergmann (arndb@de.ibm.com)
 *	      Philipp Hachपंचांगann (phacht@de.ibm.com)
 *
 */

#घोषणा KMSG_COMPONENT "diag288_wdt"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/diag.h>
#समावेश <linux/पन.स>

#घोषणा MAX_CMDLEN 240
#घोषणा DEFAULT_CMD "SYSTEM RESTART"

#घोषणा MIN_INTERVAL 15     /* Minimal समय supported by diag88 */
#घोषणा MAX_INTERVAL 3600   /* One hour should be enough - pure estimation */

#घोषणा WDT_DEFAULT_TIMEOUT 30

/* Function codes - init, change, cancel */
#घोषणा WDT_FUNC_INIT 0
#घोषणा WDT_FUNC_CHANGE 1
#घोषणा WDT_FUNC_CANCEL 2
#घोषणा WDT_FUNC_CONCEAL 0x80000000

/* Action codes क्रम LPAR watchकरोg */
#घोषणा LPARWDT_RESTART 0

अटल अक्षर wdt_cmd[MAX_CMDLEN] = DEFAULT_CMD;
अटल bool conceal_on;
अटल bool nowayout_info = WATCHDOG_NOWAYOUT;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arnd Bergmann <arndb@de.ibm.com>");
MODULE_AUTHOR("Philipp Hachtmann <phacht@de.ibm.com>");

MODULE_DESCRIPTION("System z diag288  Watchdog Timer");

module_param_string(cmd, wdt_cmd, MAX_CMDLEN, 0644);
MODULE_PARM_DESC(cmd, "CP command that is run when the watchdog triggers (z/VM only)");

module_param_named(conceal, conceal_on, bool, 0644);
MODULE_PARM_DESC(conceal, "Enable the CONCEAL CP option while the watchdog is active (z/VM only)");

module_param_named(nowayout, nowayout_info, bool, 0444);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default = CONFIG_WATCHDOG_NOWAYOUT)");

MODULE_ALIAS("vmwatchdog");

अटल पूर्णांक __diag288(अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक समयout,
		     अचिन्हित दीर्घ action, अचिन्हित पूर्णांक len)
अणु
	रेजिस्टर अचिन्हित दीर्घ __func यंत्र("2") = func;
	रेजिस्टर अचिन्हित दीर्घ __समयout यंत्र("3") = समयout;
	रेजिस्टर अचिन्हित दीर्घ __action यंत्र("4") = action;
	रेजिस्टर अचिन्हित दीर्घ __len यंत्र("5") = len;
	पूर्णांक err;

	err = -EINVAL;
	यंत्र अस्थिर(
		"	diag	%1, %3, 0x288\n"
		"0:	la	%0, 0\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: "+d" (err) : "d"(__func), "d"(__समयout),
		  "d"(__action), "d"(__len) : "1", "cc");
	वापस err;
पूर्ण

अटल पूर्णांक __diag288_vm(अचिन्हित पूर्णांक  func, अचिन्हित पूर्णांक समयout,
			अक्षर *cmd, माप_प्रकार len)
अणु
	diag_stat_inc(DIAG_STAT_X288);
	वापस __diag288(func, समयout, virt_to_phys(cmd), len);
पूर्ण

अटल पूर्णांक __diag288_lpar(अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक समयout,
			  अचिन्हित दीर्घ action)
अणु
	diag_stat_inc(DIAG_STAT_X288);
	वापस __diag288(func, समयout, action, 0);
पूर्ण

अटल अचिन्हित दीर्घ wdt_status;

#घोषणा DIAG_WDOG_BUSY	0

अटल पूर्णांक wdt_start(काष्ठा watchकरोg_device *dev)
अणु
	अक्षर *ebc_cmd;
	माप_प्रकार len;
	पूर्णांक ret;
	अचिन्हित पूर्णांक func;

	अगर (test_and_set_bit(DIAG_WDOG_BUSY, &wdt_status))
		वापस -EBUSY;

	ret = -ENODEV;

	अगर (MACHINE_IS_VM) अणु
		ebc_cmd = kदो_स्मृति(MAX_CMDLEN, GFP_KERNEL);
		अगर (!ebc_cmd) अणु
			clear_bit(DIAG_WDOG_BUSY, &wdt_status);
			वापस -ENOMEM;
		पूर्ण
		len = strlcpy(ebc_cmd, wdt_cmd, MAX_CMDLEN);
		ASCEBC(ebc_cmd, MAX_CMDLEN);
		EBC_TOUPPER(ebc_cmd, MAX_CMDLEN);

		func = conceal_on ? (WDT_FUNC_INIT | WDT_FUNC_CONCEAL)
			: WDT_FUNC_INIT;
		ret = __diag288_vm(func, dev->समयout, ebc_cmd, len);
		WARN_ON(ret != 0);
		kमुक्त(ebc_cmd);
	पूर्ण अन्यथा अणु
		ret = __diag288_lpar(WDT_FUNC_INIT,
				     dev->समयout, LPARWDT_RESTART);
	पूर्ण

	अगर (ret) अणु
		pr_err("The watchdog cannot be activated\n");
		clear_bit(DIAG_WDOG_BUSY, &wdt_status);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_stop(काष्ठा watchकरोg_device *dev)
अणु
	पूर्णांक ret;

	diag_stat_inc(DIAG_STAT_X288);
	ret = __diag288(WDT_FUNC_CANCEL, 0, 0, 0);

	clear_bit(DIAG_WDOG_BUSY, &wdt_status);

	वापस ret;
पूर्ण

अटल पूर्णांक wdt_ping(काष्ठा watchकरोg_device *dev)
अणु
	अक्षर *ebc_cmd;
	माप_प्रकार len;
	पूर्णांक ret;
	अचिन्हित पूर्णांक func;

	ret = -ENODEV;

	अगर (MACHINE_IS_VM) अणु
		ebc_cmd = kदो_स्मृति(MAX_CMDLEN, GFP_KERNEL);
		अगर (!ebc_cmd)
			वापस -ENOMEM;
		len = strlcpy(ebc_cmd, wdt_cmd, MAX_CMDLEN);
		ASCEBC(ebc_cmd, MAX_CMDLEN);
		EBC_TOUPPER(ebc_cmd, MAX_CMDLEN);

		/*
		 * It seems to be ok to z/VM to use the init function to
		 * retrigger the watchकरोg. On LPAR WDT_FUNC_CHANGE must
		 * be used when the watchकरोg is running.
		 */
		func = conceal_on ? (WDT_FUNC_INIT | WDT_FUNC_CONCEAL)
			: WDT_FUNC_INIT;

		ret = __diag288_vm(func, dev->समयout, ebc_cmd, len);
		WARN_ON(ret != 0);
		kमुक्त(ebc_cmd);
	पूर्ण अन्यथा अणु
		ret = __diag288_lpar(WDT_FUNC_CHANGE, dev->समयout, 0);
	पूर्ण

	अगर (ret)
		pr_err("The watchdog timer cannot be started or reset\n");
	वापस ret;
पूर्ण

अटल पूर्णांक wdt_set_समयout(काष्ठा watchकरोg_device * dev, अचिन्हित पूर्णांक new_to)
अणु
	dev->समयout = new_to;
	वापस wdt_ping(dev);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = wdt_start,
	.stop = wdt_stop,
	.ping = wdt_ping,
	.set_समयout = wdt_set_समयout,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_info wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.firmware_version = 0,
	.identity = "z Watchdog",
पूर्ण;

अटल काष्ठा watchकरोg_device wdt_dev = अणु
	.parent = शून्य,
	.info = &wdt_info,
	.ops = &wdt_ops,
	.bootstatus = 0,
	.समयout = WDT_DEFAULT_TIMEOUT,
	.min_समयout = MIN_INTERVAL,
	.max_समयout = MAX_INTERVAL,
पूर्ण;

/*
 * It makes no sense to go पूर्णांकo suspend जबतक the watchकरोg is running.
 * Depending on the memory size, the watchकरोg might trigger, जबतक we
 * are still saving the memory.
 */
अटल पूर्णांक wdt_suspend(व्योम)
अणु
	अगर (test_and_set_bit(DIAG_WDOG_BUSY, &wdt_status)) अणु
		pr_err("Linux cannot be suspended while the watchdog is in use\n");
		वापस notअगरier_from_त्रुटि_सं(-EBUSY);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक wdt_resume(व्योम)
अणु
	clear_bit(DIAG_WDOG_BUSY, &wdt_status);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक wdt_घातer_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	चयन (event) अणु
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_SUSPEND:
		वापस wdt_resume();
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
		वापस wdt_suspend();
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block wdt_घातer_notअगरier = अणु
	.notअगरier_call = wdt_घातer_event,
पूर्ण;

अटल पूर्णांक __init diag288_init(व्योम)
अणु
	पूर्णांक ret;
	अक्षर ebc_begin[] = अणु
		194, 197, 199, 201, 213
	पूर्ण;

	watchकरोg_set_nowayout(&wdt_dev, nowayout_info);

	अगर (MACHINE_IS_VM) अणु
		अगर (__diag288_vm(WDT_FUNC_INIT, 15,
				 ebc_begin, माप(ebc_begin)) != 0) अणु
			pr_err("The watchdog cannot be initialized\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (__diag288_lpar(WDT_FUNC_INIT, 30, LPARWDT_RESTART)) अणु
			pr_err("The watchdog cannot be initialized\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (__diag288_lpar(WDT_FUNC_CANCEL, 0, 0)) अणु
		pr_err("The watchdog cannot be deactivated\n");
		वापस -EINVAL;
	पूर्ण

	ret = रेजिस्टर_pm_notअगरier(&wdt_घातer_notअगरier);
	अगर (ret)
		वापस ret;

	ret = watchकरोg_रेजिस्टर_device(&wdt_dev);
	अगर (ret)
		unरेजिस्टर_pm_notअगरier(&wdt_घातer_notअगरier);

	वापस ret;
पूर्ण

अटल व्योम __निकास diag288_निकास(व्योम)
अणु
	watchकरोg_unरेजिस्टर_device(&wdt_dev);
	unरेजिस्टर_pm_notअगरier(&wdt_घातer_notअगरier);
पूर्ण

module_init(diag288_init);
module_निकास(diag288_निकास);
