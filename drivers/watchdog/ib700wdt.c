<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	IB700 Single Board Computer WDT driver
 *
 *	(c) Copyright 2001 Charles Howes <chowes@vsol.net>
 *
 *	Based on advantechwdt.c which is based on acquirewdt.c which
 *	is based on wdt.c.
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
 *	     Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT
 *	     Added समयout module option to override शेष
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


अटल काष्ठा platक्रमm_device *ibwdt_platक्रमm_device;
अटल अचिन्हित दीर्घ ibwdt_is_खोलो;
अटल DEFINE_SPINLOCK(ibwdt_lock);
अटल अक्षर expect_बंद;

/* Module inक्रमmation */
#घोषणा DRV_NAME "ib700wdt"

/*
 *
 * Watchकरोg Timer Configuration
 *
 * The function of the watchकरोg समयr is to reset the प्रणाली
 * स्वतःmatically and is defined at I/O port 0443H.  To enable the
 * watchकरोg समयr and allow the प्रणाली to reset, ग_लिखो I/O port 0443H.
 * To disable the समयr, ग_लिखो I/O port 0441H क्रम the प्रणाली to stop the
 * watchकरोg function.  The समयr has a tolerance of 20% क्रम its
 * पूर्णांकervals.
 *
 * The following describes how the समयr should be programmed.
 *
 * Enabling Watchकरोg:
 * MOV AX,000FH (Choose the values from 0 to F)
 * MOV DX,0443H
 * OUT DX,AX
 *
 * Disabling Watchकरोg:
 * MOV AX,000FH (Any value is fine.)
 * MOV DX,0441H
 * OUT DX,AX
 *
 * Watchकरोg समयr control table:
 * Level   Value  Time/sec | Level Value Time/sec
 *   1       F       0     |   9     7      16
 *   2       E       2     |   10    6      18
 *   3       D       4     |   11    5      20
 *   4       C       6     |   12    4      22
 *   5       B       8     |   13    3      24
 *   6       A       10    |   14    2      26
 *   7       9       12    |   15    1      28
 *   8       8       14    |   16    0      30
 *
 */

#घोषणा WDT_STOP 0x441
#घोषणा WDT_START 0x443

/* Default समयout */
#घोषणा WATCHDOG_TIMEOUT 30		/* 30 seconds +/- 20% */
अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;	/* in seconds */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. 0<= timeout <=30, default="
		__MODULE_STRING(WATCHDOG_TIMEOUT) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");


/*
 *	Watchकरोg Operations
 */

अटल व्योम ibwdt_ping(व्योम)
अणु
	पूर्णांक wd_margin = 15 - ((समयout + 1) / 2);

	spin_lock(&ibwdt_lock);

	/* Write a watchकरोg value */
	outb_p(wd_margin, WDT_START);

	spin_unlock(&ibwdt_lock);
पूर्ण

अटल व्योम ibwdt_disable(व्योम)
अणु
	spin_lock(&ibwdt_lock);
	outb_p(0, WDT_STOP);
	spin_unlock(&ibwdt_lock);
पूर्ण

अटल पूर्णांक ibwdt_set_heartbeat(पूर्णांक t)
अणु
	अगर (t < 0 || t > 30)
		वापस -EINVAL;

	समयout = t;
	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल sमाप_प्रकार ibwdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण
		ibwdt_ping();
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ ibwdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_margin;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;

	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = "IB700 WDT",
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
			ibwdt_disable();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			ibwdt_ping();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		ibwdt_ping();
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_margin, p))
			वापस -EFAULT;
		अगर (ibwdt_set_heartbeat(new_margin))
			वापस -EINVAL;
		ibwdt_ping();
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);

	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ibwdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &ibwdt_is_खोलो))
		वापस -EBUSY;
	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Activate */
	ibwdt_ping();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक ibwdt_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		ibwdt_disable();
	पूर्ण अन्यथा अणु
		pr_crit("WDT device closed unexpectedly.  WDT will not stop!\n");
		ibwdt_ping();
	पूर्ण
	clear_bit(0, &ibwdt_is_खोलो);
	expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations ibwdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= ibwdt_ग_लिखो,
	.unlocked_ioctl	= ibwdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= ibwdt_खोलो,
	.release	= ibwdt_बंद,
पूर्ण;

अटल काष्ठा miscdevice ibwdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &ibwdt_fops,
पूर्ण;

/*
 *	Init & निकास routines
 */

अटल पूर्णांक __init ibwdt_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक res;

#अगर WDT_START != WDT_STOP
	अगर (!request_region(WDT_STOP, 1, "IB700 WDT")) अणु
		pr_err("STOP method I/O %X is not available\n", WDT_STOP);
		res = -EIO;
		जाओ out_nostopreg;
	पूर्ण
#पूर्ण_अगर

	अगर (!request_region(WDT_START, 1, "IB700 WDT")) अणु
		pr_err("START method I/O %X is not available\n", WDT_START);
		res = -EIO;
		जाओ out_nostartreg;
	पूर्ण

	/* Check that the heartbeat value is within it's range ;
	 * अगर not reset to the शेष */
	अगर (ibwdt_set_heartbeat(समयout)) अणु
		ibwdt_set_heartbeat(WATCHDOG_TIMEOUT);
		pr_info("timeout value must be 0<=x<=30, using %d\n", समयout);
	पूर्ण

	res = misc_रेजिस्टर(&ibwdt_miscdev);
	अगर (res) अणु
		pr_err("failed to register misc device\n");
		जाओ out_nomisc;
	पूर्ण
	वापस 0;

out_nomisc:
	release_region(WDT_START, 1);
out_nostartreg:
#अगर WDT_START != WDT_STOP
	release_region(WDT_STOP, 1);
#पूर्ण_अगर
out_nostopreg:
	वापस res;
पूर्ण

अटल पूर्णांक ibwdt_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	misc_deरेजिस्टर(&ibwdt_miscdev);
	release_region(WDT_START, 1);
#अगर WDT_START != WDT_STOP
	release_region(WDT_STOP, 1);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम ibwdt_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	/* Turn the WDT off अगर we have a soft shutकरोwn */
	ibwdt_disable();
पूर्ण

अटल काष्ठा platक्रमm_driver ibwdt_driver = अणु
	.हटाओ		= ibwdt_हटाओ,
	.shutकरोwn	= ibwdt_shutकरोwn,
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ibwdt_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("WDT driver for IB700 single board computer initialising\n");

	ibwdt_platक्रमm_device = platक्रमm_device_रेजिस्टर_simple(DRV_NAME,
								-1, शून्य, 0);
	अगर (IS_ERR(ibwdt_platक्रमm_device))
		वापस PTR_ERR(ibwdt_platक्रमm_device);

	err = platक्रमm_driver_probe(&ibwdt_driver, ibwdt_probe);
	अगर (err)
		जाओ unreg_platक्रमm_device;

	वापस 0;

unreg_platक्रमm_device:
	platक्रमm_device_unरेजिस्टर(ibwdt_platक्रमm_device);
	वापस err;
पूर्ण

अटल व्योम __निकास ibwdt_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(ibwdt_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&ibwdt_driver);
	pr_info("Watchdog Module Unloaded\n");
पूर्ण

module_init(ibwdt_init);
module_निकास(ibwdt_निकास);

MODULE_AUTHOR("Charles Howes <chowes@vsol.net>");
MODULE_DESCRIPTION("IB700 SBC watchdog driver");
MODULE_LICENSE("GPL");

/* end of ib700wdt.c */
