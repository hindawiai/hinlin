<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Watchकरोg driver क्रम Aपंचांगel AT91RM9200 (Thunder)
 *
 *  Copyright (C) 2003 SAN People (Pty) Ltd
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/aपंचांगel-st.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#घोषणा WDT_DEFAULT_TIME	5	/* seconds */
#घोषणा WDT_MAX_TIME		256	/* seconds */

अटल पूर्णांक wdt_समय = WDT_DEFAULT_TIME;
अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल काष्ठा regmap *regmap_st;

module_param(wdt_समय, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_समय, "Watchdog time in seconds. (default="
				__MODULE_STRING(WDT_DEFAULT_TIME) ")");

#अगर_घोषित CONFIG_WATCHDOG_NOWAYOUT
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
#पूर्ण_अगर


अटल अचिन्हित दीर्घ at91wdt_busy;

/* ......................................................................... */

अटल पूर्णांक at91rm9200_restart(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	/*
	 * Perक्रमm a hardware reset with the use of the Watchकरोg समयr.
	 */
	regmap_ग_लिखो(regmap_st, AT91_ST_WDMR,
		     AT91_ST_RSTEN | AT91_ST_EXTEN | 1);
	regmap_ग_लिखो(regmap_st, AT91_ST_CR, AT91_ST_WDRST);

	mdelay(2000);

	pr_emerg("Unable to restart system\n");
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block at91rm9200_restart_nb = अणु
	.notअगरier_call = at91rm9200_restart,
	.priority = 192,
पूर्ण;

/*
 * Disable the watchकरोg.
 */
अटल अंतरभूत व्योम at91_wdt_stop(व्योम)
अणु
	regmap_ग_लिखो(regmap_st, AT91_ST_WDMR, AT91_ST_EXTEN);
पूर्ण

/*
 * Enable and reset the watchकरोg.
 */
अटल अंतरभूत व्योम at91_wdt_start(व्योम)
अणु
	regmap_ग_लिखो(regmap_st, AT91_ST_WDMR, AT91_ST_EXTEN | AT91_ST_RSTEN |
				(((65536 * wdt_समय) >> 8) & AT91_ST_WDV));
	regmap_ग_लिखो(regmap_st, AT91_ST_CR, AT91_ST_WDRST);
पूर्ण

/*
 * Reload the watchकरोg समयr.  (ie, pat the watchकरोg)
 */
अटल अंतरभूत व्योम at91_wdt_reload(व्योम)
अणु
	regmap_ग_लिखो(regmap_st, AT91_ST_CR, AT91_ST_WDRST);
पूर्ण

/* ......................................................................... */

/*
 * Watchकरोg device is खोलोed, and watchकरोg starts running.
 */
अटल पूर्णांक at91_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &at91wdt_busy))
		वापस -EBUSY;

	at91_wdt_start();
	वापस stream_खोलो(inode, file);
पूर्ण

/*
 * Close the watchकरोg device.
 * If CONFIG_WATCHDOG_NOWAYOUT is NOT defined then the watchकरोg is also
 *  disabled.
 */
अटल पूर्णांक at91_wdt_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Disable the watchकरोg when file is बंदd */
	अगर (!nowayout)
		at91_wdt_stop();

	clear_bit(0, &at91wdt_busy);
	वापस 0;
पूर्ण

/*
 * Change the watchकरोg समय पूर्णांकerval.
 */
अटल पूर्णांक at91_wdt_समय_रखोout(पूर्णांक new_समय)
अणु
	/*
	 * All counting occurs at SLOW_CLOCK / 128 = 256 Hz
	 *
	 * Since WDV is a 16-bit counter, the maximum period is
	 * 65536 / 256 = 256 seconds.
	 */
	अगर ((new_समय <= 0) || (new_समय > WDT_MAX_TIME))
		वापस -EINVAL;

	/* Set new watchकरोg समय. It will be used when
	   at91_wdt_start() is called. */
	wdt_समय = new_समय;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info at91_wdt_info = अणु
	.identity	= "at91 watchdog",
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
पूर्ण;

/*
 * Handle commands from user-space.
 */
अटल दीर्घ at91_wdt_ioctl(काष्ठा file *file,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक new_value;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &at91_wdt_info,
				माप(at91_wdt_info)) ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_SETOPTIONS:
		अगर (get_user(new_value, p))
			वापस -EFAULT;
		अगर (new_value & WDIOS_DISABLECARD)
			at91_wdt_stop();
		अगर (new_value & WDIOS_ENABLECARD)
			at91_wdt_start();
		वापस 0;
	हाल WDIOC_KEEPALIVE:
		at91_wdt_reload();	/* pat the watchकरोg */
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_value, p))
			वापस -EFAULT;
		अगर (at91_wdt_समय_रखोout(new_value))
			वापस -EINVAL;
		/* Enable new समय value */
		at91_wdt_start();
		/* Return current value */
		वापस put_user(wdt_समय, p);
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(wdt_समय, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/*
 * Pat the watchकरोg whenever device is written to.
 */
अटल sमाप_प्रकार at91_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data,
						माप_प्रकार len, loff_t *ppos)
अणु
	at91_wdt_reload();		/* pat the watchकरोg */
	वापस len;
पूर्ण

/* ......................................................................... */

अटल स्थिर काष्ठा file_operations at91wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.unlocked_ioctl	= at91_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= at91_wdt_खोलो,
	.release	= at91_wdt_बंद,
	.ग_लिखो		= at91_wdt_ग_लिखो,
पूर्ण;

अटल काष्ठा miscdevice at91wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &at91wdt_fops,
पूर्ण;

अटल पूर्णांक at91wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *parent;
	पूर्णांक res;

	अगर (at91wdt_miscdev.parent)
		वापस -EBUSY;
	at91wdt_miscdev.parent = &pdev->dev;

	parent = dev->parent;
	अगर (!parent) अणु
		dev_err(dev, "no parent\n");
		वापस -ENODEV;
	पूर्ण

	regmap_st = syscon_node_to_regmap(parent->of_node);
	अगर (IS_ERR(regmap_st))
		वापस -ENODEV;

	res = misc_रेजिस्टर(&at91wdt_miscdev);
	अगर (res)
		वापस res;

	res = रेजिस्टर_restart_handler(&at91rm9200_restart_nb);
	अगर (res)
		dev_warn(dev, "failed to register restart handler\n");

	pr_info("AT91 Watchdog Timer enabled (%d seconds%s)\n",
		wdt_समय, nowayout ? ", nowayout" : "");
	वापस 0;
पूर्ण

अटल पूर्णांक at91wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक res;

	res = unरेजिस्टर_restart_handler(&at91rm9200_restart_nb);
	अगर (res)
		dev_warn(dev, "failed to unregister restart handler\n");

	misc_deरेजिस्टर(&at91wdt_miscdev);
	at91wdt_miscdev.parent = शून्य;

	वापस res;
पूर्ण

अटल व्योम at91wdt_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	at91_wdt_stop();
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक at91wdt_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t message)
अणु
	at91_wdt_stop();
	वापस 0;
पूर्ण

अटल पूर्णांक at91wdt_resume(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (at91wdt_busy)
		at91_wdt_start();
	वापस 0;
पूर्ण

#अन्यथा
#घोषणा at91wdt_suspend शून्य
#घोषणा at91wdt_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id at91_wdt_dt_ids[] = अणु
	अणु .compatible = "atmel,at91rm9200-wdt" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_wdt_dt_ids);

अटल काष्ठा platक्रमm_driver at91wdt_driver = अणु
	.probe		= at91wdt_probe,
	.हटाओ		= at91wdt_हटाओ,
	.shutकरोwn	= at91wdt_shutकरोwn,
	.suspend	= at91wdt_suspend,
	.resume		= at91wdt_resume,
	.driver		= अणु
		.name	= "atmel_st_watchdog",
		.of_match_table = at91_wdt_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init at91_wdt_init(व्योम)
अणु
	/* Check that the heartbeat value is within range;
	   अगर not reset to the शेष */
	अगर (at91_wdt_समय_रखोout(wdt_समय)) अणु
		at91_wdt_समय_रखोout(WDT_DEFAULT_TIME);
		pr_info("wdt_time value must be 1 <= wdt_time <= 256, using %d\n",
			wdt_समय);
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&at91wdt_driver);
पूर्ण

अटल व्योम __निकास at91_wdt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&at91wdt_driver);
पूर्ण

module_init(at91_wdt_init);
module_निकास(at91_wdt_निकास);

MODULE_AUTHOR("Andrew Victor");
MODULE_DESCRIPTION("Watchdog driver for Atmel AT91RM9200");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:atmel_st_watchdog");
