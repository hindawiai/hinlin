<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Acquire Single Board Computer Watchकरोg Timer driver
 *
 *	Based on wdt.c. Original copyright messages:
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
 *	    Can't add timeout - driver doesn't allow changing value
 */

/*
 *	Theory of Operation:
 *		The Watch-Dog Timer is provided to ensure that standalone
 *		Systems can always recover from catastrophic conditions that
 *		caused the CPU to crash. This condition may have occurred by
 *		बाह्यal EMI or a software bug. When the CPU stops working
 *		correctly, hardware on the board will either perक्रमm a hardware
 *		reset (cold boot) or a non-maskable पूर्णांकerrupt (NMI) to bring the
 *		प्रणाली back to a known state.
 *
 *		The Watch-Dog Timer is controlled by two I/O Ports.
 *		  443 hex	- Read	- Enable or refresh the Watch-Dog Timer
 *		  043 hex	- Read	- Disable the Watch-Dog Timer
 *
 *		To enable the Watch-Dog Timer, a पढ़ो from I/O port 443h must
 *		be perक्रमmed. This will enable and activate the countकरोwn समयr
 *		which will eventually समय out and either reset the CPU or cause
 *		an NMI depending on the setting of a jumper. To ensure that this
 *		reset condition करोes not occur, the Watch-Dog Timer must be
 *		periodically refreshed by पढ़ोing the same I/O port 443h.
 *		The Watch-Dog Timer is disabled by पढ़ोing I/O port 043h.
 *
 *		The Watch-Dog Timer Time-Out Period is set via jumpers.
 *		It can be 1, 2, 10, 20, 110 or 220 seconds.
 */

/*
 *	Includes, defines, variables, module parameters, ...
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* Includes */
#समावेश <linux/module.h>		/* For module specअगरic items */
#समावेश <linux/moduleparam.h>		/* For new moduleparam's */
#समावेश <linux/types.h>		/* For standard types (like माप_प्रकार) */
#समावेश <linux/त्रुटिसं.स>		/* For the -ENODEV/... values */
#समावेश <linux/kernel.h>		/* For prपूर्णांकk/panic/... */
#समावेश <linux/miscdevice.h>		/* For काष्ठा miscdevice */
#समावेश <linux/watchकरोg.h>		/* For the watchकरोg specअगरic items */
#समावेश <linux/fs.h>			/* For file operations */
#समावेश <linux/ioport.h>		/* For io-port access */
#समावेश <linux/platक्रमm_device.h>	/* For platक्रमm_driver framework */
#समावेश <linux/init.h>			/* For __init/__निकास/... */
#समावेश <linux/uaccess.h>		/* For copy_to_user/put_user/... */
#समावेश <linux/पन.स>			/* For inb/outb/... */

/* Module inक्रमmation */
#घोषणा DRV_NAME "acquirewdt"
#घोषणा WATCHDOG_NAME "Acquire WDT"
/* There is no way to see what the correct समय-out period is */
#घोषणा WATCHDOG_HEARTBEAT 0

/* पूर्णांकernal variables */
/* the watchकरोg platक्रमm device */
अटल काष्ठा platक्रमm_device *acq_platक्रमm_device;
अटल अचिन्हित दीर्घ acq_is_खोलो;
अटल अक्षर expect_बंद;

/* module parameters */
/* You must set this - there is no sane way to probe क्रम this board. */
अटल पूर्णांक wdt_stop = 0x43;
module_param(wdt_stop, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_stop, "Acquire WDT 'stop' io port (default 0x43)");

/* You must set this - there is no sane way to probe क्रम this board. */
अटल पूर्णांक wdt_start = 0x443;
module_param(wdt_start, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_start, "Acquire WDT 'start' io port (default 0x443)");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Watchकरोg Operations
 */

अटल व्योम acq_keepalive(व्योम)
अणु
	/* Write a watchकरोg value */
	inb_p(wdt_start);
पूर्ण

अटल व्योम acq_stop(व्योम)
अणु
	/* Turn the card off */
	inb_p(wdt_stop);
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल sमाप_प्रकार acq_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;
			/* note: just in हाल someone wrote the magic अक्षरacter
			   five months ago... */
			expect_बंद = 0;
			/* scan to see whether or not we got the
			   magic अक्षरacter */
			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण
		/* Well, anyhow someone wrote to us, we should
				वापस that favour */
		acq_keepalive();
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ acq_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक options, retval = -EINVAL;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = WATCHDOG_NAME,
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_SETOPTIONS:
	अणु
		अगर (get_user(options, p))
			वापस -EFAULT;
		अगर (options & WDIOS_DISABLECARD) अणु
			acq_stop();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			acq_keepalive();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		acq_keepalive();
		वापस 0;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(WATCHDOG_HEARTBEAT, p);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक acq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &acq_is_खोलो))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Activate */
	acq_keepalive();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक acq_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		acq_stop();
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		acq_keepalive();
	पूर्ण
	clear_bit(0, &acq_is_खोलो);
	expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations acq_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= acq_ग_लिखो,
	.unlocked_ioctl	= acq_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= acq_खोलो,
	.release	= acq_बंद,
पूर्ण;

अटल काष्ठा miscdevice acq_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &acq_fops,
पूर्ण;

/*
 *	Init & निकास routines
 */

अटल पूर्णांक __init acq_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	अगर (wdt_stop != wdt_start) अणु
		अगर (!request_region(wdt_stop, 1, WATCHDOG_NAME)) अणु
			pr_err("I/O address 0x%04x already in use\n", wdt_stop);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!request_region(wdt_start, 1, WATCHDOG_NAME)) अणु
		pr_err("I/O address 0x%04x already in use\n", wdt_start);
		ret = -EIO;
		जाओ unreg_stop;
	पूर्ण
	ret = misc_रेजिस्टर(&acq_miscdev);
	अगर (ret != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ unreg_regions;
	पूर्ण
	pr_info("initialized. (nowayout=%d)\n", nowayout);

	वापस 0;
unreg_regions:
	release_region(wdt_start, 1);
unreg_stop:
	अगर (wdt_stop != wdt_start)
		release_region(wdt_stop, 1);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक acq_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	misc_deरेजिस्टर(&acq_miscdev);
	release_region(wdt_start, 1);
	अगर (wdt_stop != wdt_start)
		release_region(wdt_stop, 1);

	वापस 0;
पूर्ण

अटल व्योम acq_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	/* Turn the WDT off अगर we have a soft shutकरोwn */
	acq_stop();
पूर्ण

अटल काष्ठा platक्रमm_driver acquirewdt_driver = अणु
	.हटाओ		= acq_हटाओ,
	.shutकरोwn	= acq_shutकरोwn,
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init acq_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("WDT driver for Acquire single board computer initialising\n");

	acq_platक्रमm_device = platक्रमm_device_रेजिस्टर_simple(DRV_NAME,
								-1, शून्य, 0);
	अगर (IS_ERR(acq_platक्रमm_device))
		वापस PTR_ERR(acq_platक्रमm_device);

	err = platक्रमm_driver_probe(&acquirewdt_driver, acq_probe);
	अगर (err)
		जाओ unreg_platक्रमm_device;
	वापस 0;

unreg_platक्रमm_device:
	platक्रमm_device_unरेजिस्टर(acq_platक्रमm_device);
	वापस err;
पूर्ण

अटल व्योम __निकास acq_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(acq_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&acquirewdt_driver);
	pr_info("Watchdog Module Unloaded\n");
पूर्ण

module_init(acq_init);
module_निकास(acq_निकास);

MODULE_AUTHOR("David Woodhouse");
MODULE_DESCRIPTION("Acquire Inc. Single Board Computer Watchdog Timer driver");
MODULE_LICENSE("GPL");
