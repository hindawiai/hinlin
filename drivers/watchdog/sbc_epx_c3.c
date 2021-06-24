<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	SBC EPX C3 0.1	A Hardware Watchकरोg Device क्रम the Winप्रणालीs EPX-C3
 *	single board computer
 *
 *	(c) Copyright 2006 Calin A. Culianu <calin@ajvar.org>, All Rights
 *	Reserved.
 *
 *	based on softकरोg.c by Alan Cox <alan@lxorguk.ukuu.org.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

अटल पूर्णांक epx_c3_alive;

#घोषणा WATCHDOG_TIMEOUT 1		/* 1 sec शेष समयout */

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
					__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा EPXC3_WATCHDOG_CTL_REG 0x1ee /* ग_लिखो 1 to enable, 0 to disable */
#घोषणा EPXC3_WATCHDOG_PET_REG 0x1ef /* ग_लिखो anything to pet once enabled */

अटल व्योम epx_c3_start(व्योम)
अणु
	outb(1, EPXC3_WATCHDOG_CTL_REG);
पूर्ण

अटल व्योम epx_c3_stop(व्योम)
अणु

	outb(0, EPXC3_WATCHDOG_CTL_REG);

	pr_info("Stopped watchdog timer\n");
पूर्ण

अटल व्योम epx_c3_pet(व्योम)
अणु
	outb(1, EPXC3_WATCHDOG_PET_REG);
पूर्ण

/*
 *	Allow only one person to hold it खोलो
 */
अटल पूर्णांक epx_c3_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (epx_c3_alive)
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Activate समयr */
	epx_c3_start();
	epx_c3_pet();

	epx_c3_alive = 1;
	pr_info("Started watchdog timer\n");

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक epx_c3_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Shut off the समयr.
	 * Lock it in अगर it's a module and we defined ...NOWAYOUT */
	अगर (!nowayout)
		epx_c3_stop();		/* Turn the WDT off */

	epx_c3_alive = 0;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार epx_c3_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			माप_प्रकार len, loff_t *ppos)
अणु
	/* Refresh the समयr. */
	अगर (len)
		epx_c3_pet();
	वापस len;
पूर्ण

अटल दीर्घ epx_c3_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	पूर्णांक options, retval = -EINVAL;
	पूर्णांक __user *argp = (व्योम __user *)arg;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options		= WDIOF_KEEPALIVEPING,
		.firmware_version	= 0,
		.identity		= "Winsystems EPX-C3 H/W Watchdog",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		वापस 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, argp);
	हाल WDIOC_SETOPTIONS:
		अगर (get_user(options, argp))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD) अणु
			epx_c3_stop();
			retval = 0;
		पूर्ण

		अगर (options & WDIOS_ENABLECARD) अणु
			epx_c3_start();
			retval = 0;
		पूर्ण

		वापस retval;
	हाल WDIOC_KEEPALIVE:
		epx_c3_pet();
		वापस 0;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(WATCHDOG_TIMEOUT, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक epx_c3_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
				व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		epx_c3_stop();		/* Turn the WDT off */

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations epx_c3_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= epx_c3_ग_लिखो,
	.unlocked_ioctl	= epx_c3_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= epx_c3_खोलो,
	.release	= epx_c3_release,
पूर्ण;

अटल काष्ठा miscdevice epx_c3_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &epx_c3_fops,
पूर्ण;

अटल काष्ठा notअगरier_block epx_c3_notअगरier = अणु
	.notअगरier_call = epx_c3_notअगरy_sys,
पूर्ण;

अटल पूर्णांक __init watchकरोg_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!request_region(EPXC3_WATCHDOG_CTL_REG, 2, "epxc3_watchdog"))
		वापस -EBUSY;

	ret = रेजिस्टर_reboot_notअगरier(&epx_c3_notअगरier);
	अगर (ret) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = misc_रेजिस्टर(&epx_c3_miscdev);
	अगर (ret) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		unरेजिस्टर_reboot_notअगरier(&epx_c3_notअगरier);
		जाओ out;
	पूर्ण

	pr_info("Hardware Watchdog Timer for Winsystems EPX-C3 SBC: 0.1\n");

	वापस 0;

out:
	release_region(EPXC3_WATCHDOG_CTL_REG, 2);
	वापस ret;
पूर्ण

अटल व्योम __निकास watchकरोg_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&epx_c3_miscdev);
	unरेजिस्टर_reboot_notअगरier(&epx_c3_notअगरier);
	release_region(EPXC3_WATCHDOG_CTL_REG, 2);
पूर्ण

module_init(watchकरोg_init);
module_निकास(watchकरोg_निकास);

MODULE_AUTHOR("Calin A. Culianu <calin@ajvar.org>");
MODULE_DESCRIPTION("Hardware Watchdog Device for Winsystems EPX-C3 SBC.  "
	"Note that there is no way to probe for this device -- "
	"so only use it if you are *sure* you are running on this specific "
	"SBC system from Winsystems!  It writes to IO ports 0x1ee and 0x1ef!");
MODULE_LICENSE("GPL");
