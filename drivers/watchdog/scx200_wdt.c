<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* drivers/अक्षर/watchकरोg/scx200_wdt.c

   National Semiconductor SCx200 Watchकरोg support

   Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>

   Some code taken from:
   National Semiconductor PC87307/PC97307 (ala SC1200) WDT driver
   (c) Copyright 2002 Zwane Mwaikambo <zwane@commfireservices.com>


   The author(s) of this software shall not be held liable क्रम damages
   of any nature resulting due to the use of this software. This
   software is provided AS-IS with no warranties. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/scx200.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#घोषणा DEBUG

MODULE_AUTHOR("Christer Weinigel <wingel@nano-system.com>");
MODULE_DESCRIPTION("NatSemi SCx200 Watchdog Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक margin = 60;		/* in seconds */
module_param(margin, पूर्णांक, 0);
MODULE_PARM_DESC(margin, "Watchdog margin in seconds");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Disable watchdog shutdown on close");

अटल u16 wdto_restart;
अटल अक्षर expect_बंद;
अटल अचिन्हित दीर्घ खोलो_lock;
अटल DEFINE_SPINLOCK(scx_lock);

/* Bits of the WDCNFG रेजिस्टर */
#घोषणा W_ENABLE 0x00fa		/* Enable watchकरोg */
#घोषणा W_DISABLE 0x0000	/* Disable watchकरोg */

/* The scaling factor क्रम the समयr, this depends on the value of W_ENABLE */
#घोषणा W_SCALE (32768/1024)

अटल व्योम scx200_wdt_ping(व्योम)
अणु
	spin_lock(&scx_lock);
	outw(wdto_restart, scx200_cb_base + SCx200_WDT_WDTO);
	spin_unlock(&scx_lock);
पूर्ण

अटल व्योम scx200_wdt_update_margin(व्योम)
अणु
	pr_info("timer margin %d seconds\n", margin);
	wdto_restart = margin * W_SCALE;
पूर्ण

अटल व्योम scx200_wdt_enable(व्योम)
अणु
	pr_debug("enabling watchdog timer, wdto_restart = %d\n", wdto_restart);

	spin_lock(&scx_lock);
	outw(0, scx200_cb_base + SCx200_WDT_WDTO);
	outb(SCx200_WDT_WDSTS_WDOVF, scx200_cb_base + SCx200_WDT_WDSTS);
	outw(W_ENABLE, scx200_cb_base + SCx200_WDT_WDCNFG);
	spin_unlock(&scx_lock);

	scx200_wdt_ping();
पूर्ण

अटल व्योम scx200_wdt_disable(व्योम)
अणु
	pr_debug("disabling watchdog timer\n");

	spin_lock(&scx_lock);
	outw(0, scx200_cb_base + SCx200_WDT_WDTO);
	outb(SCx200_WDT_WDSTS_WDOVF, scx200_cb_base + SCx200_WDT_WDSTS);
	outw(W_DISABLE, scx200_cb_base + SCx200_WDT_WDCNFG);
	spin_unlock(&scx_lock);
पूर्ण

अटल पूर्णांक scx200_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* only allow one at a समय */
	अगर (test_and_set_bit(0, &खोलो_lock))
		वापस -EBUSY;
	scx200_wdt_enable();

	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक scx200_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद != 42)
		pr_warn("watchdog device closed unexpectedly, will not disable the watchdog timer\n");
	अन्यथा अगर (!nowayout)
		scx200_wdt_disable();
	expect_बंद = 0;
	clear_bit(0, &खोलो_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक scx200_wdt_notअगरy_sys(काष्ठा notअगरier_block *this,
				      अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_HALT || code == SYS_POWER_OFF)
		अगर (!nowayout)
			scx200_wdt_disable();

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block scx200_wdt_notअगरier = अणु
	.notअगरier_call = scx200_wdt_notअगरy_sys,
पूर्ण;

अटल sमाप_प्रकार scx200_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
				     माप_प्रकार len, loff_t *ppos)
अणु
	/* check क्रम a magic बंद अक्षरacter */
	अगर (len) अणु
		माप_प्रकार i;

		scx200_wdt_ping();

		expect_बंद = 0;
		क्रम (i = 0; i < len; ++i) अणु
			अक्षर c;
			अगर (get_user(c, data + i))
				वापस -EFAULT;
			अगर (c == 'V')
				expect_बंद = 42;
		पूर्ण

		वापस len;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ scx200_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.identity = "NatSemi SCx200 Watchdog",
		.firmware_version = 1,
		.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
						WDIOF_MAGICCLOSE,
	पूर्ण;
	पूर्णांक new_margin;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		वापस 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		अगर (put_user(0, p))
			वापस -EFAULT;
		वापस 0;
	हाल WDIOC_KEEPALIVE:
		scx200_wdt_ping();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_margin, p))
			वापस -EFAULT;
		अगर (new_margin < 1)
			वापस -EINVAL;
		margin = new_margin;
		scx200_wdt_update_margin();
		scx200_wdt_ping();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		अगर (put_user(margin, p))
			वापस -EFAULT;
		वापस 0;
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations scx200_wdt_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.ग_लिखो = scx200_wdt_ग_लिखो,
	.unlocked_ioctl = scx200_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो = scx200_wdt_खोलो,
	.release = scx200_wdt_release,
पूर्ण;

अटल काष्ठा miscdevice scx200_wdt_miscdev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &scx200_wdt_fops,
पूर्ण;

अटल पूर्णांक __init scx200_wdt_init(व्योम)
अणु
	पूर्णांक r;

	pr_debug("NatSemi SCx200 Watchdog Driver\n");

	/* check that we have found the configuration block */
	अगर (!scx200_cb_present())
		वापस -ENODEV;

	अगर (!request_region(scx200_cb_base + SCx200_WDT_OFFSET,
			    SCx200_WDT_SIZE,
			    "NatSemi SCx200 Watchdog")) अणु
		pr_warn("watchdog I/O region busy\n");
		वापस -EBUSY;
	पूर्ण

	scx200_wdt_update_margin();
	scx200_wdt_disable();

	r = रेजिस्टर_reboot_notअगरier(&scx200_wdt_notअगरier);
	अगर (r) अणु
		pr_err("unable to register reboot notifier\n");
		release_region(scx200_cb_base + SCx200_WDT_OFFSET,
				SCx200_WDT_SIZE);
		वापस r;
	पूर्ण

	r = misc_रेजिस्टर(&scx200_wdt_miscdev);
	अगर (r) अणु
		unरेजिस्टर_reboot_notअगरier(&scx200_wdt_notअगरier);
		release_region(scx200_cb_base + SCx200_WDT_OFFSET,
				SCx200_WDT_SIZE);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास scx200_wdt_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&scx200_wdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&scx200_wdt_notअगरier);
	release_region(scx200_cb_base + SCx200_WDT_OFFSET,
		       SCx200_WDT_SIZE);
पूर्ण

module_init(scx200_wdt_init);
module_निकास(scx200_wdt_cleanup);
