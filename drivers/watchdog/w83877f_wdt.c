<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	W83877F Computer Watchकरोg Timer driver
 *
 *      Based on acquirewdt.c by Alan Cox,
 *           and sbc60xxwdt.c by Jakob Oestergaard <jakob@unthought.net>
 *
 *	The authors करो NOT admit liability nor provide warranty क्रम
 *	any of this software. This material is provided "AS-IS" in
 *      the hope that it may be useful क्रम others.
 *
 *	(c) Copyright 2001    Scott Jennings <linuxdrivers@oro.net>
 *
 *           4/19 - 2001      [Initial revision]
 *           9/27 - 2001      Added spinlocking
 *           4/12 - 2002      [rob@osinvestor.com] Eliminate extra comments
 *                            Eliminate fop_पढ़ो
 *                            Eliminate extra spin_unlock
 *                            Added KERN_* tags to prपूर्णांकks
 *                            add CONFIG_WATCHDOG_NOWAYOUT support
 *                            fix possible wdt_is_खोलो race
 *                            changed watchकरोg_info to correctly reflect what
 *			      the driver offers
 *                            added WDIOC_GETSTATUS, WDIOC_GETBOOTSTATUS,
 *			      WDIOC_SETTIMEOUT,
 *                            WDIOC_GETTIMEOUT, and WDIOC_SETOPTIONS ioctls
 *           09/8 - 2003      [wim@iguana.be] cleanup of trailing spaces
 *                            added extra prपूर्णांकk's क्रम startup problems
 *                            use module_param
 *                            made समयout (the emulated heartbeat) a
 *			      module_param
 *                            made the keepalive ping an पूर्णांकernal subroutine
 *
 *  This WDT driver is dअगरferent from most other Linux WDT
 *  drivers in that the driver will ping the watchकरोg by itself,
 *  because this particular WDT has a very लघु समयout (1.6
 *  seconds) and it would be insane to count on any userspace
 *  daemon always getting scheduled within that समय frame.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#घोषणा OUR_NAME "w83877f_wdt"

#घोषणा ENABLE_W83877F_PORT 0x3F0
#घोषणा ENABLE_W83877F 0x87
#घोषणा DISABLE_W83877F 0xAA
#घोषणा WDT_PING 0x443
#घोषणा WDT_REGISTER 0x14
#घोषणा WDT_ENABLE 0x9C
#घोषणा WDT_DISABLE 0x8C

/*
 * The W83877F seems to be fixed at 1.6s समयout (at least on the
 * EMACS PC-104 board I'm using). If we reset the watchकरोg every
 * ~250ms we should be safe.  */

#घोषणा WDT_INTERVAL (HZ/4+1)

/*
 * We must not require too good response from the userspace daemon.
 * Here we require the userspace daemon to send us a heartbeat
 * अक्षर to /dev/watchकरोg every 30 seconds.
 */

#घोषणा WATCHDOG_TIMEOUT 30            /* 30 sec शेष समयout */
/* in seconds, will be multiplied by HZ to get seconds to रुको क्रम a ping */
अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. (1<=timeout<=3600, default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ")");


अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल व्योम wdt_समयr_ping(काष्ठा समयr_list *);
अटल DEFINE_TIMER(समयr, wdt_समयr_ping);
अटल अचिन्हित दीर्घ next_heartbeat;
अटल अचिन्हित दीर्घ wdt_is_खोलो;
अटल अक्षर wdt_expect_बंद;
अटल DEFINE_SPINLOCK(wdt_spinlock);

/*
 *	Whack the करोg
 */

अटल व्योम wdt_समयr_ping(काष्ठा समयr_list *unused)
अणु
	/* If we got a heartbeat pulse within the WDT_US_INTERVAL
	 * we agree to ping the WDT
	 */
	अगर (समय_beक्रमe(jअगरfies, next_heartbeat)) अणु
		/* Ping the WDT */
		spin_lock(&wdt_spinlock);

		/* Ping the WDT by पढ़ोing from WDT_PING */
		inb_p(WDT_PING);

		/* Re-set the समयr पूर्णांकerval */
		mod_समयr(&समयr, jअगरfies + WDT_INTERVAL);

		spin_unlock(&wdt_spinlock);

	पूर्ण अन्यथा
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
पूर्ण

/*
 * Utility routines
 */

अटल व्योम wdt_change(पूर्णांक ग_लिखोval)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&wdt_spinlock, flags);

	/* buy some समय */
	inb_p(WDT_PING);

	/* make W83877F available */
	outb_p(ENABLE_W83877F,  ENABLE_W83877F_PORT);
	outb_p(ENABLE_W83877F,  ENABLE_W83877F_PORT);

	/* enable watchकरोg */
	outb_p(WDT_REGISTER,    ENABLE_W83877F_PORT);
	outb_p(ग_लिखोval,        ENABLE_W83877F_PORT+1);

	/* lock the W8387FF away */
	outb_p(DISABLE_W83877F, ENABLE_W83877F_PORT);

	spin_unlock_irqrestore(&wdt_spinlock, flags);
पूर्ण

अटल व्योम wdt_startup(व्योम)
अणु
	next_heartbeat = jअगरfies + (समयout * HZ);

	/* Start the समयr */
	mod_समयr(&समयr, jअगरfies + WDT_INTERVAL);

	wdt_change(WDT_ENABLE);

	pr_info("Watchdog timer is now enabled\n");
पूर्ण

अटल व्योम wdt_turnoff(व्योम)
अणु
	/* Stop the समयr */
	del_समयr(&समयr);

	wdt_change(WDT_DISABLE);

	pr_info("Watchdog timer is now disabled...\n");
पूर्ण

अटल व्योम wdt_keepalive(व्योम)
अणु
	/* user land ping */
	next_heartbeat = jअगरfies + (समयout * HZ);
पूर्ण

/*
 * /dev/watchकरोg handling
 */

अटल sमाप_प्रकार fop_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार ofs;

			/* note: just in हाल someone wrote the magic
			   अक्षरacter five months ago... */
			wdt_expect_बंद = 0;

			/* scan to see whether or not we got the
			   magic अक्षरacter */
			क्रम (ofs = 0; ofs != count; ofs++) अणु
				अक्षर c;
				अगर (get_user(c, buf + ofs))
					वापस -EFAULT;
				अगर (c == 'V')
					wdt_expect_बंद = 42;
			पूर्ण
		पूर्ण

		/* someone wrote to us, we should restart समयr */
		wdt_keepalive();
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Just in हाल we're alपढ़ोy talking to someone... */
	अगर (test_and_set_bit(0, &wdt_is_खोलो))
		वापस -EBUSY;

	/* Good, fire up the show */
	wdt_startup();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक fop_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (wdt_expect_बंद == 42)
		wdt_turnoff();
	अन्यथा अणु
		del_समयr(&समयr);
		pr_crit("device file closed unexpectedly. Will not stop the WDT!\n");
	पूर्ण
	clear_bit(0, &wdt_is_खोलो);
	wdt_expect_बंद = 0;
	वापस 0;
पूर्ण

अटल दीर्घ fop_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = "W83877F",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक new_options, retval = -EINVAL;

		अगर (get_user(new_options, p))
			वापस -EFAULT;

		अगर (new_options & WDIOS_DISABLECARD) अणु
			wdt_turnoff();
			retval = 0;
		पूर्ण

		अगर (new_options & WDIOS_ENABLECARD) अणु
			wdt_startup();
			retval = 0;
		पूर्ण

		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		wdt_keepalive();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
	अणु
		पूर्णांक new_समयout;

		अगर (get_user(new_समयout, p))
			वापस -EFAULT;

		/* arbitrary upper limit */
		अगर (new_समयout < 1 || new_समयout > 3600)
			वापस -EINVAL;

		समयout = new_समयout;
		wdt_keepalive();
	पूर्ण
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= fop_ग_लिखो,
	.खोलो		= fop_खोलो,
	.release	= fop_बंद,
	.unlocked_ioctl	= fop_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल काष्ठा miscdevice wdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &wdt_fops,
पूर्ण;

/*
 *	Notअगरier क्रम प्रणाली करोwn
 */

अटल पूर्णांक wdt_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
	व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdt_turnoff();
	वापस NOTIFY_DONE;
पूर्ण

/*
 *	The WDT needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block wdt_notअगरier = अणु
	.notअगरier_call = wdt_notअगरy_sys,
पूर्ण;

अटल व्योम __निकास w83877f_wdt_unload(व्योम)
अणु
	wdt_turnoff();

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&wdt_miscdev);

	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	release_region(WDT_PING, 1);
	release_region(ENABLE_W83877F_PORT, 2);
पूर्ण

अटल पूर्णांक __init w83877f_wdt_init(व्योम)
अणु
	पूर्णांक rc = -EBUSY;

	अगर (समयout < 1 || समयout > 3600) अणु /* arbitrary upper limit */
		समयout = WATCHDOG_TIMEOUT;
		pr_info("timeout value must be 1 <= x <= 3600, using %d\n",
			समयout);
	पूर्ण

	अगर (!request_region(ENABLE_W83877F_PORT, 2, "W83877F WDT")) अणु
		pr_err("I/O address 0x%04x already in use\n",
		       ENABLE_W83877F_PORT);
		rc = -EIO;
		जाओ err_out;
	पूर्ण

	अगर (!request_region(WDT_PING, 1, "W8387FF WDT")) अणु
		pr_err("I/O address 0x%04x already in use\n", WDT_PING);
		rc = -EIO;
		जाओ err_out_region1;
	पूर्ण

	rc = रेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	अगर (rc) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", rc);
		जाओ err_out_region2;
	पूर्ण

	rc = misc_रेजिस्टर(&wdt_miscdev);
	अगर (rc) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       wdt_miscdev.minor, rc);
		जाओ err_out_reboot;
	पूर्ण

	pr_info("WDT driver for W83877F initialised. timeout=%d sec (nowayout=%d)\n",
		समयout, nowayout);

	वापस 0;

err_out_reboot:
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
err_out_region2:
	release_region(WDT_PING, 1);
err_out_region1:
	release_region(ENABLE_W83877F_PORT, 2);
err_out:
	वापस rc;
पूर्ण

module_init(w83877f_wdt_init);
module_निकास(w83877f_wdt_unload);

MODULE_AUTHOR("Scott and Bill Jennings");
MODULE_DESCRIPTION("Driver for watchdog timer in w83877f chip");
MODULE_LICENSE("GPL");
