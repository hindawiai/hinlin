<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Wdt977	0.04:	A Watchकरोg Device क्रम Netwinder W83977AF chip
 *
 *	(c) Copyright 1998 Rebel.com (Woody Suwalski <woody@netwinder.org>)
 *
 *			-----------------------
 *
 *			-----------------------
 *      14-Dec-2001 Matt Domsch <Matt_Domsch@dell.com>
 *           Added nowayout module option to override CONFIG_WATCHDOG_NOWAYOUT
 *	19-Dec-2001 Woody Suwalski: Netwinder fixes, ioctl पूर्णांकerface
 *	06-Jan-2002 Woody Suwalski: For compatibility, convert all समयouts
 *				    from minutes to seconds.
 *      07-Jul-2003 Daniele Bellucci: Audit वापस code of misc_रेजिस्टर in
 *                                    nwwatchकरोg_init.
 *      25-Oct-2005 Woody Suwalski: Convert addresses to #defs, add spinlocks
 *				    हटाओ limitiation to be used on
 *				    Netwinders only
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/mach-types.h>

#घोषणा WATCHDOG_VERSION  "0.04"
#घोषणा WATCHDOG_NAME     "Wdt977"

#घोषणा IO_INDEX_PORT	0x370		/* on some प्रणालीs it can be 0x3F0 */
#घोषणा IO_DATA_PORT	(IO_INDEX_PORT + 1)

#घोषणा UNLOCK_DATA	0x87
#घोषणा LOCK_DATA	0xAA
#घोषणा DEVICE_REGISTER	0x07


#घोषणा	DEFAULT_TIMEOUT	60			/* शेष समयout in seconds */

अटल	पूर्णांक समयout = DEFAULT_TIMEOUT;
अटल	पूर्णांक समयoutM;				/* समयout in minutes */
अटल	अचिन्हित दीर्घ समयr_alive;
अटल	पूर्णांक tesपंचांगode;
अटल	अक्षर expect_बंद;
अटल	DEFINE_SPINLOCK(spinlock);

module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds (60..15300, default="
				__MODULE_STRING(DEFAULT_TIMEOUT) ")");
module_param(tesपंचांगode, पूर्णांक, 0);
MODULE_PARM_DESC(tesपंचांगode, "Watchdog testmode (1 = no reboot), default=0");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 * Start the watchकरोg
 */

अटल पूर्णांक wdt977_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spinlock, flags);

	/* unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* select device Aux2 (device=8) and set watchकरोg regs F2, F3 and F4
	 * F2 has the समयout in minutes
	 * F3 could be set to the POWER LED blink (with GP17 set to PowerLed)
	 *   at समयout, and to reset समयr on kbd/mouse activity (not impl.)
	 * F4 is used to just clear the TIMEOUT'ed state (bit 0)
	 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(समयoutM, IO_DATA_PORT);
	outb_p(0xF3, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);	/* another setting is 0E क्रम
					   kbd/mouse/LED */
	outb_p(0xF4, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);

	/* At last select device Aux1 (dev=7) and set GP16 as a
	 * watchकरोg output. In test mode watch the bit 1 on F4 to
	 * indicate "triggered"
	 */
	अगर (!tesपंचांगode) अणु
		outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
		outb_p(0x07, IO_DATA_PORT);
		outb_p(0xE6, IO_INDEX_PORT);
		outb_p(0x08, IO_DATA_PORT);
	पूर्ण

	/* lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);
	pr_info("activated\n");

	वापस 0;
पूर्ण

/*
 * Stop the watchकरोg
 */

अटल पूर्णांक wdt977_stop(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&spinlock, flags);

	/* unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* select device Aux2 (device=8) and set watchकरोg regs F2,F3 and F4
	* F3 is reset to its शेष state
	* F4 can clear the TIMEOUT'ed state (bit 0) - back to शेष
	* We can not use GP17 as a PowerLed, as we use its usage as a RedLed
	*/
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(0xFF, IO_DATA_PORT);
	outb_p(0xF3, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);
	outb_p(0xF4, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);

	/* at last select device Aux1 (dev=7) and set
	   GP16 as a watchकरोg output */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x07, IO_DATA_PORT);
	outb_p(0xE6, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);

	/* lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);
	pr_info("shutdown\n");

	वापस 0;
पूर्ण

/*
 * Send a keepalive ping to the watchकरोg
 * This is करोne by simply re-writing the समयout to reg. 0xF2
 */

अटल पूर्णांक wdt977_keepalive(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&spinlock, flags);

	/* unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* select device Aux2 (device=8) and kicks watchकरोg reg F2 */
	/* F2 has the समयout in minutes */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(समयoutM, IO_DATA_PORT);

	/* lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);
	spin_unlock_irqrestore(&spinlock, flags);

	वापस 0;
पूर्ण

/*
 * Set the watchकरोg समयout value
 */

अटल पूर्णांक wdt977_set_समयout(पूर्णांक t)
अणु
	पूर्णांक पंचांगrval;

	/* convert seconds to minutes, rounding up */
	पंचांगrval = (t + 59) / 60;

	अगर (machine_is_netwinder()) अणु
		/* we have a hw bug somewhere, so each 977 minute is actually
		 * only 30sec. This limits the max समयout to half of device
		 * max of 255 minutes...
		 */
		पंचांगrval += पंचांगrval;
	पूर्ण

	अगर (पंचांगrval < 1 || पंचांगrval > 255)
		वापस -EINVAL;

	/* समयout is the समयout in seconds, समयoutM is
	   the समयout in minutes) */
	समयout = t;
	समयoutM = पंचांगrval;
	वापस 0;
पूर्ण

/*
 * Get the watchकरोg status
 */

अटल पूर्णांक wdt977_get_status(पूर्णांक *status)
अणु
	पूर्णांक new_status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spinlock, flags);

	/* unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* select device Aux2 (device=8) and पढ़ो watchकरोg reg F4 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF4, IO_INDEX_PORT);
	new_status = inb_p(IO_DATA_PORT);

	/* lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);

	*status = 0;
	अगर (new_status & 1)
		*status |= WDIOF_CARDRESET;

	वापस 0;
पूर्ण


/*
 *	/dev/watchकरोg handling
 */

अटल पूर्णांक wdt977_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* If the watchकरोg is alive we करोn't need to start it again */
	अगर (test_and_set_bit(0, &समयr_alive))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	wdt977_start();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक wdt977_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 *	Shut off the समयr.
	 *	Lock it in अगर it's a module and we set nowayout
	 */
	अगर (expect_बंद == 42) अणु
		wdt977_stop();
		clear_bit(0, &समयr_alive);
	पूर्ण अन्यथा अणु
		wdt977_keepalive();
		pr_crit("Unexpected close, not stopping watchdog!\n");
	पूर्ण
	expect_बंद = 0;
	वापस 0;
पूर्ण


/*
 *      wdt977_ग_लिखो:
 *      @file: file handle to the watchकरोg
 *      @buf: buffer to ग_लिखो (unused as data करोes not matter here
 *      @count: count of bytes
 *      @ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 *      A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 *      ग_लिखो of data will करो, as we we करोn't define content meaning.
 */

अटल sमाप_प्रकार wdt977_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
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

		/* someone wrote to us, we should restart समयr */
		wdt977_keepalive();
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options =		WDIOF_SETTIMEOUT |
				WDIOF_MAGICCLOSE |
				WDIOF_KEEPALIVEPING,
	.firmware_version =	1,
	.identity =		WATCHDOG_NAME,
पूर्ण;

/*
 *      wdt977_ioctl:
 *      @inode: inode of the device
 *      @file: file handle to the device
 *      @cmd: watchकरोg command
 *      @arg: argument poपूर्णांकer
 *
 *      The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *      according to their available features.
 */

अटल दीर्घ wdt977_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक status;
	पूर्णांक new_options, retval = -EINVAL;
	पूर्णांक new_समयout;
	जोड़ अणु
		काष्ठा watchकरोg_info __user *ident;
		पूर्णांक __user *i;
	पूर्ण uarg;

	uarg.i = (पूर्णांक __user *)arg;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(uarg.ident, &ident,
			माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
		wdt977_get_status(&status);
		वापस put_user(status, uarg.i);

	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, uarg.i);

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(new_options, uarg.i))
			वापस -EFAULT;

		अगर (new_options & WDIOS_DISABLECARD) अणु
			wdt977_stop();
			retval = 0;
		पूर्ण

		अगर (new_options & WDIOS_ENABLECARD) अणु
			wdt977_start();
			retval = 0;
		पूर्ण

		वापस retval;

	हाल WDIOC_KEEPALIVE:
		wdt977_keepalive();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, uarg.i))
			वापस -EFAULT;

		अगर (wdt977_set_समयout(new_समयout))
			वापस -EINVAL;

		wdt977_keepalive();
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, uarg.i);

	शेष:
		वापस -ENOTTY;

	पूर्ण
पूर्ण

अटल पूर्णांक wdt977_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
	व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdt977_stop();
	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations wdt977_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= wdt977_ग_लिखो,
	.unlocked_ioctl	= wdt977_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= wdt977_खोलो,
	.release	= wdt977_release,
पूर्ण;

अटल काष्ठा miscdevice wdt977_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &wdt977_fops,
पूर्ण;

अटल काष्ठा notअगरier_block wdt977_notअगरier = अणु
	.notअगरier_call = wdt977_notअगरy_sys,
पूर्ण;

अटल पूर्णांक __init wd977_init(व्योम)
अणु
	पूर्णांक rc;

	pr_info("driver v%s\n", WATCHDOG_VERSION);

	/* Check that the समयout value is within its range;
	   अगर not reset to the शेष */
	अगर (wdt977_set_समयout(समयout)) अणु
		wdt977_set_समयout(DEFAULT_TIMEOUT);
		pr_info("timeout value must be 60 < timeout < 15300, using %d\n",
			DEFAULT_TIMEOUT);
	पूर्ण

	/* on Netwinder the IOports are alपढ़ोy reserved by
	 * arch/arm/mach-footbridge/netwinder-hw.c
	 */
	अगर (!machine_is_netwinder()) अणु
		अगर (!request_region(IO_INDEX_PORT, 2, WATCHDOG_NAME)) अणु
			pr_err("I/O address 0x%04x already in use\n",
			       IO_INDEX_PORT);
			rc = -EIO;
			जाओ err_out;
		पूर्ण
	पूर्ण

	rc = रेजिस्टर_reboot_notअगरier(&wdt977_notअगरier);
	अगर (rc) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", rc);
		जाओ err_out_region;
	पूर्ण

	rc = misc_रेजिस्टर(&wdt977_miscdev);
	अगर (rc) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       wdt977_miscdev.minor, rc);
		जाओ err_out_reboot;
	पूर्ण

	pr_info("initialized. timeout=%d sec (nowayout=%d, testmode=%i)\n",
		समयout, nowayout, tesपंचांगode);

	वापस 0;

err_out_reboot:
	unरेजिस्टर_reboot_notअगरier(&wdt977_notअगरier);
err_out_region:
	अगर (!machine_is_netwinder())
		release_region(IO_INDEX_PORT, 2);
err_out:
	वापस rc;
पूर्ण

अटल व्योम __निकास wd977_निकास(व्योम)
अणु
	wdt977_stop();
	misc_deरेजिस्टर(&wdt977_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wdt977_notअगरier);
	release_region(IO_INDEX_PORT, 2);
पूर्ण

module_init(wd977_init);
module_निकास(wd977_निकास);

MODULE_AUTHOR("Woody Suwalski <woodys@xandros.com>");
MODULE_DESCRIPTION("W83977AF Watchdog driver");
MODULE_LICENSE("GPL");
