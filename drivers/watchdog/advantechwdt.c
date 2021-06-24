<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Advantech Single Board Computer WDT driver
 *
 *	(c) Copyright 2000-2001 Marek Michalkiewicz <marekm@linux.org.pl>
 *
 *	Based on acquirewdt.c which is based on wdt.c.
 *	Original copyright messages:
 *
 *	(c) Copyright 1996 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	14-Dec-2001 Matt Domsch <Matt_Domsch@dell.com>
 *	    Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT
 *
 *	16-Oct-2002 Rob Radez <rob@osinvestor.com>
 *	    Clean up ioctls, clean up init + निकास, add expect बंद support,
 *	    add wdt_start and wdt_stop as parameters.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


#घोषणा DRV_NAME "advantechwdt"
#घोषणा WATCHDOG_NAME "Advantech WDT"
#घोषणा WATCHDOG_TIMEOUT 60		/* 60 sec शेष समयout */

/* the watchकरोg platक्रमm device */
अटल काष्ठा platक्रमm_device *advwdt_platक्रमm_device;
अटल अचिन्हित दीर्घ advwdt_is_खोलो;
अटल अक्षर adv_expect_बंद;

/*
 *	You must set these - there is no sane way to probe क्रम this board.
 *
 *	To enable or restart, ग_लिखो the समयout value in seconds (1 to 63)
 *	to I/O port wdt_start.  To disable, पढ़ो I/O port wdt_stop.
 *	Both are 0x443 क्रम most boards (tested on a PCA-6276VE-00B1), but
 *	check your manual (at least the PCA-6159 seems to be dअगरferent -
 *	the manual says wdt_stop is 0x43, not 0x443).
 *	(0x43 is also a ग_लिखो-only control रेजिस्टर क्रम the 8254 समयr!)
 */

अटल पूर्णांक wdt_stop = 0x443;
module_param(wdt_stop, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_stop, "Advantech WDT 'stop' io port (default 0x443)");

अटल पूर्णांक wdt_start = 0x443;
module_param(wdt_start, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_start, "Advantech WDT 'start' io port (default 0x443)");

अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;	/* in seconds */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. 1<= timeout <=63, default="
		__MODULE_STRING(WATCHDOG_TIMEOUT) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
		__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Watchकरोg Operations
 */

अटल व्योम advwdt_ping(व्योम)
अणु
	/* Write a watchकरोg value */
	outb_p(समयout, wdt_start);
पूर्ण

अटल व्योम advwdt_disable(व्योम)
अणु
	inb_p(wdt_stop);
पूर्ण

अटल पूर्णांक advwdt_set_heartbeat(पूर्णांक t)
अणु
	अगर (t < 1 || t > 63)
		वापस -EINVAL;
	समयout = t;
	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल sमाप_प्रकार advwdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			adv_expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					adv_expect_बंद = 42;
			पूर्ण
		पूर्ण
		advwdt_ping();
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ advwdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_समयout;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING |
			   WDIOF_SETTIMEOUT |
			   WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = WATCHDOG_NAME,
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक options, retval = -EINVAL;

		अगर (get_user(options, p))
			वापस -EFAULT;
		अगर (options & WDIOS_DISABLECARD) अणु
			advwdt_disable();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			advwdt_ping();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		advwdt_ping();
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, p))
			वापस -EFAULT;
		अगर (advwdt_set_heartbeat(new_समयout))
			वापस -EINVAL;
		advwdt_ping();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक advwdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &advwdt_is_खोलो))
		वापस -EBUSY;
	/*
	 *	Activate
	 */

	advwdt_ping();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक advwdt_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (adv_expect_बंद == 42) अणु
		advwdt_disable();
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		advwdt_ping();
	पूर्ण
	clear_bit(0, &advwdt_is_खोलो);
	adv_expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations advwdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= advwdt_ग_लिखो,
	.unlocked_ioctl	= advwdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= advwdt_खोलो,
	.release	= advwdt_बंद,
पूर्ण;

अटल काष्ठा miscdevice advwdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &advwdt_fops,
पूर्ण;

/*
 *	Init & निकास routines
 */

अटल पूर्णांक __init advwdt_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	अगर (wdt_stop != wdt_start) अणु
		अगर (!request_region(wdt_stop, 1, WATCHDOG_NAME)) अणु
			pr_err("I/O address 0x%04x already in use\n",
			       wdt_stop);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!request_region(wdt_start, 1, WATCHDOG_NAME)) अणु
		pr_err("I/O address 0x%04x already in use\n", wdt_start);
		ret = -EIO;
		जाओ unreg_stop;
	पूर्ण

	/* Check that the heartbeat value is within it's range ;
	 * अगर not reset to the शेष */
	अगर (advwdt_set_heartbeat(समयout)) अणु
		advwdt_set_heartbeat(WATCHDOG_TIMEOUT);
		pr_info("timeout value must be 1<=x<=63, using %d\n", समयout);
	पूर्ण

	ret = misc_रेजिस्टर(&advwdt_miscdev);
	अगर (ret != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ unreg_regions;
	पूर्ण
	pr_info("initialized. timeout=%d sec (nowayout=%d)\n",
		समयout, nowayout);
out:
	वापस ret;
unreg_regions:
	release_region(wdt_start, 1);
unreg_stop:
	अगर (wdt_stop != wdt_start)
		release_region(wdt_stop, 1);
	जाओ out;
पूर्ण

अटल पूर्णांक advwdt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	misc_deरेजिस्टर(&advwdt_miscdev);
	release_region(wdt_start, 1);
	अगर (wdt_stop != wdt_start)
		release_region(wdt_stop, 1);

	वापस 0;
पूर्ण

अटल व्योम advwdt_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	/* Turn the WDT off अगर we have a soft shutकरोwn */
	advwdt_disable();
पूर्ण

अटल काष्ठा platक्रमm_driver advwdt_driver = अणु
	.हटाओ		= advwdt_हटाओ,
	.shutकरोwn	= advwdt_shutकरोwn,
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init advwdt_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("WDT driver for Advantech single board computer initialising\n");

	advwdt_platक्रमm_device = platक्रमm_device_रेजिस्टर_simple(DRV_NAME,
								-1, शून्य, 0);
	अगर (IS_ERR(advwdt_platक्रमm_device))
		वापस PTR_ERR(advwdt_platक्रमm_device);

	err = platक्रमm_driver_probe(&advwdt_driver, advwdt_probe);
	अगर (err)
		जाओ unreg_platक्रमm_device;

	वापस 0;

unreg_platक्रमm_device:
	platक्रमm_device_unरेजिस्टर(advwdt_platक्रमm_device);
	वापस err;
पूर्ण

अटल व्योम __निकास advwdt_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(advwdt_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&advwdt_driver);
	pr_info("Watchdog Module Unloaded\n");
पूर्ण

module_init(advwdt_init);
module_निकास(advwdt_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marek Michalkiewicz <marekm@linux.org.pl>");
MODULE_DESCRIPTION("Advantech Single Board Computer WDT driver");
