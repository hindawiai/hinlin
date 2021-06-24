<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	न_अंकO7240 SBC Watchकरोg device driver
 *
 *	Based on w83877f.c by Scott Jennings,
 *
 *	(c) Copyright 2007  Gilles GIGAN <gilles.gigan@jcu.edu.au>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>

#घोषणा SBC7240_ENABLE_PORT		0x443
#घोषणा SBC7240_DISABLE_PORT		0x043
#घोषणा SBC7240_SET_TIMEOUT_PORT	SBC7240_ENABLE_PORT
#घोषणा SBC7240_MAGIC_CHAR		'V'

#घोषणा SBC7240_TIMEOUT		30
#घोषणा SBC7240_MAX_TIMEOUT		255
अटल पूर्णांक समयout = SBC7240_TIMEOUT;	/* in seconds */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds. (1<=timeout<="
		 __MODULE_STRING(SBC7240_MAX_TIMEOUT) ", default="
		 __MODULE_STRING(SBC7240_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Disable watchdog when closing device file");

#घोषणा SBC7240_OPEN_STATUS_BIT		0
#घोषणा SBC7240_ENABLED_STATUS_BIT	1
#घोषणा SBC7240_EXPECT_CLOSE_STATUS_BIT	2
अटल अचिन्हित दीर्घ wdt_status;

/*
 * Utility routines
 */

अटल व्योम wdt_disable(व्योम)
अणु
	/* disable the watchकरोg */
	अगर (test_and_clear_bit(SBC7240_ENABLED_STATUS_BIT, &wdt_status)) अणु
		inb_p(SBC7240_DISABLE_PORT);
		pr_info("Watchdog timer is now disabled\n");
	पूर्ण
पूर्ण

अटल व्योम wdt_enable(व्योम)
अणु
	/* enable the watchकरोg */
	अगर (!test_and_set_bit(SBC7240_ENABLED_STATUS_BIT, &wdt_status)) अणु
		inb_p(SBC7240_ENABLE_PORT);
		pr_info("Watchdog timer is now enabled\n");
	पूर्ण
पूर्ण

अटल पूर्णांक wdt_set_समयout(पूर्णांक t)
अणु
	अगर (t < 1 || t > SBC7240_MAX_TIMEOUT) अणु
		pr_err("timeout value must be 1<=x<=%d\n", SBC7240_MAX_TIMEOUT);
		वापस -1;
	पूर्ण
	/* set the समयout */
	outb_p((अचिन्हित)t, SBC7240_SET_TIMEOUT_PORT);
	समयout = t;
	pr_info("timeout set to %d seconds\n", t);
	वापस 0;
पूर्ण

/* Whack the करोg */
अटल अंतरभूत व्योम wdt_keepalive(व्योम)
अणु
	अगर (test_bit(SBC7240_ENABLED_STATUS_BIT, &wdt_status))
		inb_p(SBC7240_ENABLE_PORT);
पूर्ण

/*
 * /dev/watchकरोg handling
 */
अटल sमाप_प्रकार fop_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार i;
	अक्षर c;

	अगर (count) अणु
		अगर (!nowayout) अणु
			clear_bit(SBC7240_EXPECT_CLOSE_STATUS_BIT,
				&wdt_status);

			/* is there a magic अक्षर ? */
			क्रम (i = 0; i != count; i++) अणु
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == SBC7240_MAGIC_CHAR) अणु
					set_bit(SBC7240_EXPECT_CLOSE_STATUS_BIT,
						&wdt_status);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		wdt_keepalive();
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(SBC7240_OPEN_STATUS_BIT, &wdt_status))
		वापस -EBUSY;

	wdt_enable();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक fop_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_clear_bit(SBC7240_EXPECT_CLOSE_STATUS_BIT, &wdt_status)
	    || !nowayout) अणु
		wdt_disable();
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		wdt_keepalive();
	पूर्ण

	clear_bit(SBC7240_OPEN_STATUS_BIT, &wdt_status);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options = WDIOF_KEEPALIVEPING|
		   WDIOF_SETTIMEOUT|
		   WDIOF_MAGICCLOSE,
	.firmware_version = 1,
	.identity = "SBC7240",
पूर्ण;


अटल दीर्घ fop_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user((व्योम __user *)arg, &ident, माप(ident))
						 ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, (पूर्णांक __user *)arg);
	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक options;
		पूर्णांक retval = -EINVAL;

		अगर (get_user(options, (पूर्णांक __user *)arg))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD) अणु
			wdt_disable();
			retval = 0;
		पूर्ण

		अगर (options & WDIOS_ENABLECARD) अणु
			wdt_enable();
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

		अगर (get_user(new_समयout, (पूर्णांक __user *)arg))
			वापस -EFAULT;

		अगर (wdt_set_समयout(new_समयout))
			वापस -EINVAL;
	पूर्ण
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, (पूर्णांक __user *)arg);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations wdt_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.ग_लिखो = fop_ग_लिखो,
	.खोलो = fop_खोलो,
	.release = fop_बंद,
	.unlocked_ioctl = fop_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल काष्ठा miscdevice wdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &wdt_fops,
पूर्ण;

/*
 *	Notअगरier क्रम प्रणाली करोwn
 */

अटल पूर्णांक wdt_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
			  व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdt_disable();
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block wdt_notअगरier = अणु
	.notअगरier_call = wdt_notअगरy_sys,
पूर्ण;

अटल व्योम __निकास sbc7240_wdt_unload(व्योम)
अणु
	pr_info("Removing watchdog\n");
	misc_deरेजिस्टर(&wdt_miscdev);

	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	release_region(SBC7240_ENABLE_PORT, 1);
पूर्ण

अटल पूर्णांक __init sbc7240_wdt_init(व्योम)
अणु
	पूर्णांक rc = -EBUSY;

	अगर (!request_region(SBC7240_ENABLE_PORT, 1, "SBC7240 WDT")) अणु
		pr_err("I/O address 0x%04x already in use\n",
		       SBC7240_ENABLE_PORT);
		rc = -EIO;
		जाओ err_out;
	पूर्ण

	/* The IO port 0x043 used to disable the watchकरोg
	 * is alपढ़ोy claimed by the प्रणाली समयr, so we
	 * can't request_region() it ...*/

	अगर (समयout < 1 || समयout > SBC7240_MAX_TIMEOUT) अणु
		समयout = SBC7240_TIMEOUT;
		pr_info("timeout value must be 1<=x<=%d, using %d\n",
			SBC7240_MAX_TIMEOUT, समयout);
	पूर्ण
	wdt_set_समयout(समयout);
	wdt_disable();

	rc = रेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	अगर (rc) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", rc);
		जाओ err_out_region;
	पूर्ण

	rc = misc_रेजिस्टर(&wdt_miscdev);
	अगर (rc) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       wdt_miscdev.minor, rc);
		जाओ err_out_reboot_notअगरier;
	पूर्ण

	pr_info("Watchdog driver for SBC7240 initialised (nowayout=%d)\n",
		nowayout);

	वापस 0;

err_out_reboot_notअगरier:
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
err_out_region:
	release_region(SBC7240_ENABLE_PORT, 1);
err_out:
	वापस rc;
पूर्ण

module_init(sbc7240_wdt_init);
module_निकास(sbc7240_wdt_unload);

MODULE_AUTHOR("Gilles Gigan");
MODULE_DESCRIPTION("Watchdog device driver for single board"
		   " computers EPIC Nano 7240 from iEi");
MODULE_LICENSE("GPL");
