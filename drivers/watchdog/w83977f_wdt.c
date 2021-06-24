<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	W83977F Watchकरोg Timer Driver क्रम Winbond W83977F I/O Chip
 *
 *	(c) Copyright 2005  Jose Goncalves <jose.goncalves@inov.pt>
 *
 *      Based on w83877f_wdt.c by Scott Jennings,
 *           and wdt977.c by Woody Suwalski
 *
 *			-----------------------
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
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>


#घोषणा WATCHDOG_VERSION  "1.00"
#घोषणा WATCHDOG_NAME     "W83977F WDT"

#घोषणा IO_INDEX_PORT     0x3F0
#घोषणा IO_DATA_PORT      (IO_INDEX_PORT+1)

#घोषणा UNLOCK_DATA       0x87
#घोषणा LOCK_DATA         0xAA
#घोषणा DEVICE_REGISTER   0x07

#घोषणा	DEFAULT_TIMEOUT   45		/* शेष समयout in seconds */

अटल	पूर्णांक समयout = DEFAULT_TIMEOUT;
अटल	पूर्णांक समयoutW;			/* समयout in watchकरोg counter units */
अटल	अचिन्हित दीर्घ समयr_alive;
अटल	पूर्णांक tesपंचांगode;
अटल	अक्षर expect_बंद;
अटल	DEFINE_SPINLOCK(spinlock);

module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		"Watchdog timeout in seconds (15..7635), default="
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

अटल पूर्णांक wdt_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spinlock, flags);

	/* Unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/*
	 * Select device Aux2 (device=8) to set watchकरोg regs F2, F3 and F4.
	 * F2 has the समयout in watchकरोg counter units.
	 * F3 is set to enable watchकरोg LED blink at समयout.
	 * F4 is used to just clear the TIMEOUT'ed state (bit 0).
	 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(समयoutW, IO_DATA_PORT);
	outb_p(0xF3, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF4, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);

	/* Set device Aux2 active */
	outb_p(0x30, IO_INDEX_PORT);
	outb_p(0x01, IO_DATA_PORT);

	/*
	 * Select device Aux1 (dev=7) to set GP16 as the watchकरोg output
	 * (in reg E6) and GP13 as the watchकरोg LED output (in reg E3).
	 * Map GP16 at pin 119.
	 * In test mode watch the bit 0 on F4 to indicate "triggered" or
	 * check watchकरोg LED on SBC.
	 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x07, IO_DATA_PORT);
	अगर (!tesपंचांगode) अणु
		अचिन्हित pin_map;

		outb_p(0xE6, IO_INDEX_PORT);
		outb_p(0x0A, IO_DATA_PORT);
		outb_p(0x2C, IO_INDEX_PORT);
		pin_map = inb_p(IO_DATA_PORT);
		pin_map |= 0x10;
		pin_map &= ~(0x20);
		outb_p(0x2C, IO_INDEX_PORT);
		outb_p(pin_map, IO_DATA_PORT);
	पूर्ण
	outb_p(0xE3, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);

	/* Set device Aux1 active */
	outb_p(0x30, IO_INDEX_PORT);
	outb_p(0x01, IO_DATA_PORT);

	/* Lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);

	pr_info("activated\n");

	वापस 0;
पूर्ण

/*
 * Stop the watchकरोg
 */

अटल पूर्णांक wdt_stop(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spinlock, flags);

	/* Unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/*
	 * Select device Aux2 (device=8) to set watchकरोg regs F2, F3 and F4.
	 * F2 is reset to its शेष value (watchकरोg समयr disabled).
	 * F3 is reset to its शेष state.
	 * F4 clears the TIMEOUT'ed state (bit 0) - back to शेष.
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

	/*
	 * Select device Aux1 (dev=7) to set GP16 (in reg E6) and
	 * Gp13 (in reg E3) as inमाला_दो.
	 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x07, IO_DATA_PORT);
	अगर (!tesपंचांगode) अणु
		outb_p(0xE6, IO_INDEX_PORT);
		outb_p(0x01, IO_DATA_PORT);
	पूर्ण
	outb_p(0xE3, IO_INDEX_PORT);
	outb_p(0x01, IO_DATA_PORT);

	/* Lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);

	pr_info("shutdown\n");

	वापस 0;
पूर्ण

/*
 * Send a keepalive ping to the watchकरोg
 * This is करोne by simply re-writing the समयout to reg. 0xF2
 */

अटल पूर्णांक wdt_keepalive(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spinlock, flags);

	/* Unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* Select device Aux2 (device=8) to kick watchकरोg reg F2 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(समयoutW, IO_DATA_PORT);

	/* Lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);

	वापस 0;
पूर्ण

/*
 * Set the watchकरोg समयout value
 */

अटल पूर्णांक wdt_set_समयout(पूर्णांक t)
अणु
	अचिन्हित पूर्णांक पंचांगrval;

	/*
	 * Convert seconds to watchकरोg counter समय units, rounding up.
	 * On PCM-5335 watchकरोg units are 30 seconds/step with 15 sec startup
	 * value. This inक्रमmation is supplied in the PCM-5335 manual and was
	 * checked by me on a real board. This is a bit strange because W83977f
	 * datasheet says counter unit is in minutes!
	 */
	अगर (t < 15)
		वापस -EINVAL;

	पंचांगrval = ((t + 15) + 29) / 30;

	अगर (पंचांगrval > 255)
		वापस -EINVAL;

	/*
	 * समयout is the समयout in seconds,
	 * समयoutW is the समयout in watchकरोg counter units.
	 */
	समयoutW = पंचांगrval;
	समयout = (समयoutW * 30) - 15;
	वापस 0;
पूर्ण

/*
 * Get the watchकरोg status
 */

अटल पूर्णांक wdt_get_status(पूर्णांक *status)
अणु
	पूर्णांक new_status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spinlock, flags);

	/* Unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* Select device Aux2 (device=8) to पढ़ो watchकरोg reg F4 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF4, IO_INDEX_PORT);
	new_status = inb_p(IO_DATA_PORT);

	/* Lock the SuperIO chip */
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

अटल पूर्णांक wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* If the watchकरोg is alive we करोn't need to start it again */
	अगर (test_and_set_bit(0, &समयr_alive))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	wdt_start();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 * Shut off the समयr.
	 * Lock it in अगर it's a module and we set nowayout
	 */
	अगर (expect_बंद == 42) अणु
		wdt_stop();
		clear_bit(0, &समयr_alive);
	पूर्ण अन्यथा अणु
		wdt_keepalive();
		pr_crit("unexpected close, not stopping watchdog!\n");
	पूर्ण
	expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 *      wdt_ग_लिखो:
 *      @file: file handle to the watchकरोg
 *      @buf: buffer to ग_लिखो (unused as data करोes not matter here
 *      @count: count of bytes
 *      @ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 *      A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 *      ग_लिखो of data will करो, as we we करोn't define content meaning.
 */

अटल sमाप_प्रकार wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार ofs;

			/* note: just in हाल someone wrote the
			   magic अक्षरacter दीर्घ ago */
			expect_बंद = 0;

			/* scan to see whether or not we got the
			   magic अक्षरacter */
			क्रम (ofs = 0; ofs != count; ofs++) अणु
				अक्षर c;
				अगर (get_user(c, buf + ofs))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण

		/* someone wrote to us, we should restart समयr */
		wdt_keepalive();
	पूर्ण
	वापस count;
पूर्ण

/*
 *      wdt_ioctl:
 *      @inode: inode of the device
 *      @file: file handle to the device
 *      @cmd: watchकरोg command
 *      @arg: argument poपूर्णांकer
 *
 *      The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *      according to their available features.
 */

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.firmware_version =	1,
	.identity = WATCHDOG_NAME,
पूर्ण;

अटल दीर्घ wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
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
		wdt_get_status(&status);
		वापस put_user(status, uarg.i);

	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, uarg.i);

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(new_options, uarg.i))
			वापस -EFAULT;

		अगर (new_options & WDIOS_DISABLECARD) अणु
			wdt_stop();
			retval = 0;
		पूर्ण

		अगर (new_options & WDIOS_ENABLECARD) अणु
			wdt_start();
			retval = 0;
		पूर्ण

		वापस retval;

	हाल WDIOC_KEEPALIVE:
		wdt_keepalive();
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, uarg.i))
			वापस -EFAULT;

		अगर (wdt_set_समयout(new_समयout))
			वापस -EINVAL;

		wdt_keepalive();
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, uarg.i);

	शेष:
		वापस -ENOTTY;

	पूर्ण
पूर्ण

अटल पूर्णांक wdt_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
	व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdt_stop();
	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= wdt_ग_लिखो,
	.unlocked_ioctl	= wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= wdt_खोलो,
	.release	= wdt_release,
पूर्ण;

अटल काष्ठा miscdevice wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &wdt_fops,
पूर्ण;

अटल काष्ठा notअगरier_block wdt_notअगरier = अणु
	.notअगरier_call = wdt_notअगरy_sys,
पूर्ण;

अटल पूर्णांक __init w83977f_wdt_init(व्योम)
अणु
	पूर्णांक rc;

	pr_info("driver v%s\n", WATCHDOG_VERSION);

	/*
	 * Check that the समयout value is within it's range;
	 * अगर not reset to the शेष
	 */
	अगर (wdt_set_समयout(समयout)) अणु
		wdt_set_समयout(DEFAULT_TIMEOUT);
		pr_info("timeout value must be 15 <= timeout <= 7635, using %d\n",
			DEFAULT_TIMEOUT);
	पूर्ण

	अगर (!request_region(IO_INDEX_PORT, 2, WATCHDOG_NAME)) अणु
		pr_err("I/O address 0x%04x already in use\n", IO_INDEX_PORT);
		rc = -EIO;
		जाओ err_out;
	पूर्ण

	rc = रेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	अगर (rc) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", rc);
		जाओ err_out_region;
	पूर्ण

	rc = misc_रेजिस्टर(&wdt_miscdev);
	अगर (rc) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       wdt_miscdev.minor, rc);
		जाओ err_out_reboot;
	पूर्ण

	pr_info("initialized. timeout=%d sec (nowayout=%d testmode=%d)\n",
		समयout, nowayout, tesपंचांगode);

	वापस 0;

err_out_reboot:
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
err_out_region:
	release_region(IO_INDEX_PORT, 2);
err_out:
	वापस rc;
पूर्ण

अटल व्योम __निकास w83977f_wdt_निकास(व्योम)
अणु
	wdt_stop();
	misc_deरेजिस्टर(&wdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	release_region(IO_INDEX_PORT, 2);
पूर्ण

module_init(w83977f_wdt_init);
module_निकास(w83977f_wdt_निकास);

MODULE_AUTHOR("Jose Goncalves <jose.goncalves@inov.pt>");
MODULE_DESCRIPTION("Driver for watchdog timer in W83977F I/O chip");
MODULE_LICENSE("GPL");
