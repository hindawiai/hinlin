<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	ICP Wafer 5823 Single Board Computer WDT driver
 *	http://www.icpamerica.com/wafer_5823.php
 *	May also work on other similar models
 *
 *	(c) Copyright 2002 Justin Cormack <justin@street-vision.com>
 *
 *	Release 0.02
 *
 *	Based on advantechwdt.c which is based on wdt.c.
 *	Original copyright messages:
 *
 *	(c) Copyright 1996-1997 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#घोषणा WATCHDOG_NAME "Wafer 5823 WDT"
#घोषणा PFX WATCHDOG_NAME ": "
#घोषणा WD_TIMO 60			/* 60 sec शेष समयout */

अटल अचिन्हित दीर्घ wafwdt_is_खोलो;
अटल अक्षर expect_बंद;
अटल DEFINE_SPINLOCK(wafwdt_lock);

/*
 *	You must set these - there is no sane way to probe क्रम this board.
 *
 *	To enable, ग_लिखो the समयout value in seconds (1 to 255) to I/O
 *	port WDT_START, then पढ़ो the port to start the watchकरोg. To pat
 *	the करोg, पढ़ो port WDT_STOP to stop the समयr, then पढ़ो WDT_START
 *	to restart it again.
 */

अटल पूर्णांक wdt_stop = 0x843;
अटल पूर्णांक wdt_start = 0x443;

अटल पूर्णांक समयout = WD_TIMO;  /* in seconds */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		"Watchdog timeout in seconds. 1 <= timeout <= 255, default="
				__MODULE_STRING(WD_TIMO) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल व्योम wafwdt_ping(व्योम)
अणु
	/* pat watchकरोg */
	spin_lock(&wafwdt_lock);
	inb_p(wdt_stop);
	inb_p(wdt_start);
	spin_unlock(&wafwdt_lock);
पूर्ण

अटल व्योम wafwdt_start(व्योम)
अणु
	/* start up watchकरोg */
	outb_p(समयout, wdt_start);
	inb_p(wdt_start);
पूर्ण

अटल व्योम wafwdt_stop(व्योम)
अणु
	/* stop watchकरोg */
	inb_p(wdt_stop);
पूर्ण

अटल sमाप_प्रकार wafwdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			expect_बंद = 0;

			/* scan to see whether or not we got the magic
			   अक्षरacter */
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
		wafwdt_ping();
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ wafwdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_समयout;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT |
							WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = "Wafer 5823 WDT",
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
			wafwdt_stop();
			retval = 0;
		पूर्ण

		अगर (options & WDIOS_ENABLECARD) अणु
			wafwdt_start();
			retval = 0;
		पूर्ण

		वापस retval;
	पूर्ण

	हाल WDIOC_KEEPALIVE:
		wafwdt_ping();
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, p))
			वापस -EFAULT;
		अगर ((new_समयout < 1) || (new_समयout > 255))
			वापस -EINVAL;
		समयout = new_समयout;
		wafwdt_stop();
		wafwdt_start();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);

	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wafwdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &wafwdt_is_खोलो))
		वापस -EBUSY;

	/*
	 *      Activate
	 */
	wafwdt_start();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक wafwdt_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42)
		wafwdt_stop();
	अन्यथा अणु
		pr_crit("WDT device closed unexpectedly.  WDT will not stop!\n");
		wafwdt_ping();
	पूर्ण
	clear_bit(0, &wafwdt_is_खोलो);
	expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 *	Notअगरier क्रम प्रणाली करोwn
 */

अटल पूर्णांक wafwdt_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
								व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wafwdt_stop();
	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations wafwdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= wafwdt_ग_लिखो,
	.unlocked_ioctl	= wafwdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= wafwdt_खोलो,
	.release	= wafwdt_बंद,
पूर्ण;

अटल काष्ठा miscdevice wafwdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &wafwdt_fops,
पूर्ण;

/*
 *	The WDT needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block wafwdt_notअगरier = अणु
	.notअगरier_call = wafwdt_notअगरy_sys,
पूर्ण;

अटल पूर्णांक __init wafwdt_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("WDT driver for Wafer 5823 single board computer initialising\n");

	अगर (समयout < 1 || समयout > 255) अणु
		समयout = WD_TIMO;
		pr_info("timeout value must be 1 <= x <= 255, using %d\n",
			समयout);
	पूर्ण

	अगर (wdt_stop != wdt_start) अणु
		अगर (!request_region(wdt_stop, 1, "Wafer 5823 WDT")) अणु
			pr_err("I/O address 0x%04x already in use\n", wdt_stop);
			ret = -EIO;
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (!request_region(wdt_start, 1, "Wafer 5823 WDT")) अणु
		pr_err("I/O address 0x%04x already in use\n", wdt_start);
		ret = -EIO;
		जाओ error2;
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&wafwdt_notअगरier);
	अगर (ret != 0) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		जाओ error3;
	पूर्ण

	ret = misc_रेजिस्टर(&wafwdt_miscdev);
	अगर (ret != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ error4;
	पूर्ण

	pr_info("initialized. timeout=%d sec (nowayout=%d)\n",
		समयout, nowayout);

	वापस ret;
error4:
	unरेजिस्टर_reboot_notअगरier(&wafwdt_notअगरier);
error3:
	release_region(wdt_start, 1);
error2:
	अगर (wdt_stop != wdt_start)
		release_region(wdt_stop, 1);
error:
	वापस ret;
पूर्ण

अटल व्योम __निकास wafwdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&wafwdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wafwdt_notअगरier);
	अगर (wdt_stop != wdt_start)
		release_region(wdt_stop, 1);
	release_region(wdt_start, 1);
पूर्ण

module_init(wafwdt_init);
module_निकास(wafwdt_निकास);

MODULE_AUTHOR("Justin Cormack");
MODULE_DESCRIPTION("ICP Wafer 5823 Single Board Computer WDT driver");
MODULE_LICENSE("GPL");

/* end of wafer5823wdt.c */
