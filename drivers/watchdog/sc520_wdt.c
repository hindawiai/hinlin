<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	AMD Elan SC520 processor Watchकरोg Timer driver
 *
 *	Based on acquirewdt.c by Alan Cox,
 *	     and sbc60xxwdt.c by Jakob Oestergaard <jakob@unthought.net>
 *
 *	The authors करो NOT admit liability nor provide warranty क्रम
 *	any of this software. This material is provided "AS-IS" in
 *	the hope that it may be useful क्रम others.
 *
 *	(c) Copyright 2001    Scott Jennings <linuxdrivers@oro.net>
 *           9/27 - 2001      [Initial release]
 *
 *	Additional fixes Alan Cox
 *	-	Fixed क्रमmatting
 *	-	Removed debug prपूर्णांकks
 *	-	Fixed SMP built kernel deadlock
 *	-	Switched to निजी locks not lock_kernel
 *	-	Used ioremap/ग_लिखोw/पढ़ोw
 *	-	Added NOWAYOUT support
 *	4/12 - 2002 Changes by Rob Radez <rob@osinvestor.com>
 *	-	Change comments
 *	-	Eliminate fop_llseek
 *	-	Change CONFIG_WATCHDOG_NOWAYOUT semantics
 *	-	Add KERN_* tags to prपूर्णांकks
 *	-	fix possible wdt_is_खोलो race
 *	-	Report proper capabilities in watchकरोg_info
 *	-	Add WDIOC_अणुGETSTATUS, GETBOOTSTATUS, SETTIMEOUT,
 *		GETTIMEOUT, SETOPTIONSपूर्ण ioctls
 *	09/8 - 2003 Changes by Wim Van Sebroeck <wim@iguana.be>
 *	-	cleanup of trailing spaces
 *	-	added extra prपूर्णांकk's क्रम startup problems
 *	-	use module_param
 *	-	made समयout (the emulated heartbeat) a module_param
 *	-	made the keepalive ping an पूर्णांकernal subroutine
 *	3/27 - 2004 Changes by Sean Young <sean@mess.org>
 *	-	set MMCR_BASE to 0xfffef000
 *	-	CBAR करोes not need to be पढ़ो
 *	-	हटाओd debugging prपूर्णांकks
 *
 *  This WDT driver is dअगरferent from most other Linux WDT
 *  drivers in that the driver will ping the watchकरोg by itself,
 *  because this particular WDT has a very लघु समयout (1.6
 *  seconds) and it would be insane to count on any userspace
 *  daemon always getting scheduled within that समय frame.
 *
 *  This driver uses memory mapped IO, and spinlock.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


/*
 * The AMD Elan SC520 समयout value is 492us बार a घातer of 2 (0-7)
 *
 *   0: 492us    2: 1.01s    4: 4.03s   6: 16.22s
 *   1: 503ms    3: 2.01s    5: 8.05s   7: 32.21s
 *
 * We will program the SC520 watchकरोg क्रम a समयout of 2.01s.
 * If we reset the watchकरोg every ~250ms we should be safe.
 */

#घोषणा WDT_INTERVAL (HZ/4+1)

/*
 * We must not require too good response from the userspace daemon.
 * Here we require the userspace daemon to send us a heartbeat
 * अक्षर to /dev/watchकरोg every 30 seconds.
 */

#घोषणा WATCHDOG_TIMEOUT 30		/* 30 sec शेष समयout */
/* in seconds, will be multiplied by HZ to get seconds to रुको क्रम a ping */
अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. (1 <= timeout <= 3600, default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 * AMD Elan SC520 - Watchकरोg Timer Registers
 */
#घोषणा MMCR_BASE	0xfffef000	/* The शेष base address */
#घोषणा OFFS_WDTMRCTL	0xCB0	/* Watchकरोg Timer Control Register */

/* WDT Control Register bit definitions */
#घोषणा WDT_EXP_SEL_01	0x0001	/* [01] Time-out = 496 us (with 33 Mhz clk). */
#घोषणा WDT_EXP_SEL_02	0x0002	/* [02] Time-out = 508 ms (with 33 Mhz clk). */
#घोषणा WDT_EXP_SEL_03	0x0004	/* [03] Time-out = 1.02 s (with 33 Mhz clk). */
#घोषणा WDT_EXP_SEL_04	0x0008	/* [04] Time-out = 2.03 s (with 33 Mhz clk). */
#घोषणा WDT_EXP_SEL_05	0x0010	/* [05] Time-out = 4.07 s (with 33 Mhz clk). */
#घोषणा WDT_EXP_SEL_06	0x0020	/* [06] Time-out = 8.13 s (with 33 Mhz clk). */
#घोषणा WDT_EXP_SEL_07	0x0040	/* [07] Time-out = 16.27s (with 33 Mhz clk). */
#घोषणा WDT_EXP_SEL_08	0x0080	/* [08] Time-out = 32.54s (with 33 Mhz clk). */
#घोषणा WDT_IRQ_FLG	0x1000	/* [12] Interrupt Request Flag */
#घोषणा WDT_WRST_ENB	0x4000	/* [14] Watchकरोg Timer Reset Enable */
#घोषणा WDT_ENB		0x8000	/* [15] Watchकरोg Timer Enable */

अटल __u16 __iomem *wdपंचांगrctl;

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
		ग_लिखोw(0xAAAA, wdपंचांगrctl);
		ग_लिखोw(0x5555, wdपंचांगrctl);
		spin_unlock(&wdt_spinlock);

		/* Re-set the समयr पूर्णांकerval */
		mod_समयr(&समयr, jअगरfies + WDT_INTERVAL);
	पूर्ण अन्यथा
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
पूर्ण

/*
 *	Utility routines
 */

अटल व्योम wdt_config(पूर्णांक ग_लिखोval)
अणु
	अचिन्हित दीर्घ flags;

	/* buy some समय (ping) */
	spin_lock_irqsave(&wdt_spinlock, flags);
	पढ़ोw(wdपंचांगrctl);	/* ensure ग_लिखो synchronization */
	ग_लिखोw(0xAAAA, wdपंचांगrctl);
	ग_लिखोw(0x5555, wdपंचांगrctl);
	/* unlock WDT = make WDT configuration रेजिस्टर writable one समय */
	ग_लिखोw(0x3333, wdपंचांगrctl);
	ग_लिखोw(0xCCCC, wdपंचांगrctl);
	/* ग_लिखो WDT configuration रेजिस्टर */
	ग_लिखोw(ग_लिखोval, wdपंचांगrctl);
	spin_unlock_irqrestore(&wdt_spinlock, flags);
पूर्ण

अटल पूर्णांक wdt_startup(व्योम)
अणु
	next_heartbeat = jअगरfies + (समयout * HZ);

	/* Start the समयr */
	mod_समयr(&समयr, jअगरfies + WDT_INTERVAL);

	/* Start the watchकरोg */
	wdt_config(WDT_ENB | WDT_WRST_ENB | WDT_EXP_SEL_04);

	pr_info("Watchdog timer is now enabled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_turnoff(व्योम)
अणु
	/* Stop the समयr */
	del_समयr(&समयr);

	/* Stop the watchकरोg */
	wdt_config(0);

	pr_info("Watchdog timer is now disabled...\n");
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_keepalive(व्योम)
अणु
	/* user land ping */
	next_heartbeat = jअगरfies + (समयout * HZ);
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_set_heartbeat(पूर्णांक t)
अणु
	अगर ((t < 1) || (t > 3600))	/* arbitrary upper limit */
		वापस -EINVAL;

	समयout = t;
	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल sमाप_प्रकार fop_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार ofs;

			/* note: just in हाल someone wrote the magic अक्षरacter
			 * five months ago... */
			wdt_expect_बंद = 0;

			/* now scan */
			क्रम (ofs = 0; ofs != count; ofs++) अणु
				अक्षर c;
				अगर (get_user(c, buf + ofs))
					वापस -EFAULT;
				अगर (c == 'V')
					wdt_expect_बंद = 42;
			पूर्ण
		पूर्ण

		/* Well, anyhow someone wrote to us, we should
		   वापस that favour */
		wdt_keepalive();
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Just in हाल we're alपढ़ोy talking to someone... */
	अगर (test_and_set_bit(0, &wdt_is_खोलो))
		वापस -EBUSY;
	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Good, fire up the show */
	wdt_startup();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक fop_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (wdt_expect_बंद == 42)
		wdt_turnoff();
	अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		wdt_keepalive();
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
		.identity = "SC520",
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

		अगर (wdt_set_heartbeat(new_समयout))
			वापस -EINVAL;

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

अटल व्योम __निकास sc520_wdt_unload(व्योम)
अणु
	अगर (!nowayout)
		wdt_turnoff();

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&wdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	iounmap(wdपंचांगrctl);
पूर्ण

अटल पूर्णांक __init sc520_wdt_init(व्योम)
अणु
	पूर्णांक rc = -EBUSY;

	/* Check that the समयout value is within it's range ;
	   अगर not reset to the शेष */
	अगर (wdt_set_heartbeat(समयout)) अणु
		wdt_set_heartbeat(WATCHDOG_TIMEOUT);
		pr_info("timeout value must be 1 <= timeout <= 3600, using %d\n",
			WATCHDOG_TIMEOUT);
	पूर्ण

	wdपंचांगrctl = ioremap(MMCR_BASE + OFFS_WDTMRCTL, 2);
	अगर (!wdपंचांगrctl) अणु
		pr_err("Unable to remap memory\n");
		rc = -ENOMEM;
		जाओ err_out_region2;
	पूर्ण

	rc = रेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	अगर (rc) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", rc);
		जाओ err_out_ioremap;
	पूर्ण

	rc = misc_रेजिस्टर(&wdt_miscdev);
	अगर (rc) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, rc);
		जाओ err_out_notअगरier;
	पूर्ण

	pr_info("WDT driver for SC520 initialised. timeout=%d sec (nowayout=%d)\n",
		समयout, nowayout);

	वापस 0;

err_out_notअगरier:
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
err_out_ioremap:
	iounmap(wdपंचांगrctl);
err_out_region2:
	वापस rc;
पूर्ण

module_init(sc520_wdt_init);
module_निकास(sc520_wdt_unload);

MODULE_AUTHOR("Scott and Bill Jennings");
MODULE_DESCRIPTION(
	"Driver for watchdog timer in AMD \"Elan\" SC520 uProcessor");
MODULE_LICENSE("GPL");
