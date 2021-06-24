<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IndyDog	0.3	A Hardware Watchकरोg Device क्रम SGI IP22
 *
 *	(c) Copyright 2002 Guiकरो Guenther <agx@sigxcpu.org>,
 *						All Rights Reserved.
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
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sgi/mc.h>

अटल अचिन्हित दीर्घ indyकरोg_alive;
अटल DEFINE_SPINLOCK(indyकरोg_lock);

#घोषणा WATCHDOG_TIMEOUT 30		/* 30 sec शेष समयout */

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल व्योम indyकरोg_start(व्योम)
अणु
	spin_lock(&indyकरोg_lock);
	sgimc->cpuctrl0 |= SGIMC_CCTRL0_WDOG;
	spin_unlock(&indyकरोg_lock);
पूर्ण

अटल व्योम indyकरोg_stop(व्योम)
अणु
	spin_lock(&indyकरोg_lock);
	sgimc->cpuctrl0 &= ~SGIMC_CCTRL0_WDOG;
	spin_unlock(&indyकरोg_lock);

	pr_info("Stopped watchdog timer\n");
पूर्ण

अटल व्योम indyकरोg_ping(व्योम)
अणु
	sgimc->watchकरोgt = 0;
पूर्ण

/*
 *	Allow only one person to hold it खोलो
 */
अटल पूर्णांक indyकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &indyकरोg_alive))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Activate समयr */
	indyकरोg_start();
	indyकरोg_ping();

	pr_info("Started watchdog timer\n");

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक indyकरोg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Shut off the समयr.
	 * Lock it in अगर it's a module and we defined ...NOWAYOUT */
	अगर (!nowayout)
		indyकरोg_stop();		/* Turn the WDT off */
	clear_bit(0, &indyकरोg_alive);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार indyकरोg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *data,
						माप_प्रकार len, loff_t *ppos)
अणु
	/* Refresh the समयr. */
	अगर (len)
		indyकरोg_ping();
	वापस len;
पूर्ण

अटल दीर्घ indyकरोg_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक options, retval = -EINVAL;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options		= WDIOF_KEEPALIVEPING,
		.firmware_version	= 0,
		.identity		= "Hardware Watchdog for SGI IP22",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user((काष्ठा watchकरोg_info *)arg,
				 &ident, माप(ident)))
			वापस -EFAULT;
		वापस 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, (पूर्णांक *)arg);
	हाल WDIOC_SETOPTIONS:
	अणु
		अगर (get_user(options, (पूर्णांक *)arg))
			वापस -EFAULT;
		अगर (options & WDIOS_DISABLECARD) अणु
			indyकरोg_stop();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			indyकरोg_start();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		indyकरोg_ping();
		वापस 0;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(WATCHDOG_TIMEOUT, (पूर्णांक *)arg);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक indyकरोg_notअगरy_sys(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		indyकरोg_stop();		/* Turn the WDT off */

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations indyकरोg_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= indyकरोg_ग_लिखो,
	.unlocked_ioctl	= indyकरोg_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= indyकरोg_खोलो,
	.release	= indyकरोg_release,
पूर्ण;

अटल काष्ठा miscdevice indyकरोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &indyकरोg_fops,
पूर्ण;

अटल काष्ठा notअगरier_block indyकरोg_notअगरier = अणु
	.notअगरier_call = indyकरोg_notअगरy_sys,
पूर्ण;

अटल पूर्णांक __init watchकरोg_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_reboot_notअगरier(&indyकरोg_notअगरier);
	अगर (ret) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = misc_रेजिस्टर(&indyकरोg_miscdev);
	अगर (ret) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		unरेजिस्टर_reboot_notअगरier(&indyकरोg_notअगरier);
		वापस ret;
	पूर्ण

	pr_info("Hardware Watchdog Timer for SGI IP22: 0.3\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास watchकरोg_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&indyकरोg_miscdev);
	unरेजिस्टर_reboot_notअगरier(&indyकरोg_notअगरier);
पूर्ण

module_init(watchकरोg_init);
module_निकास(watchकरोg_निकास);

MODULE_AUTHOR("Guido Guenther <agx@sigxcpu.org>");
MODULE_DESCRIPTION("Hardware Watchdog Device for SGI IP22");
MODULE_LICENSE("GPL");
