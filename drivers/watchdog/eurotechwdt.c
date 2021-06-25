<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Eurotech CPU-1220/1410/1420 on board WDT driver
 *
 *	(c) Copyright 2001 Ascensit <support@ascensit.com>
 *	(c) Copyright 2001 Roकरोlfo Giometti <giometti@ascensit.com>
 *	(c) Copyright 2002 Rob Radez <rob@osinvestor.com>
 *
 *	Based on wdt.c.
 *	Original copyright messages:
 *
 *	(c) Copyright 1996-1997 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>*
 */

/* Changelog:
 *
 * 2001 - Roकरोlfo Giometti
 *	Initial release
 *
 * 2002/04/25 - Rob Radez
 *	clean up #समावेशs
 *	clean up locking
 *	make __setup param unique
 *	proper options in watchकरोg_info
 *	add WDIOC_GETSTATUS and WDIOC_SETOPTIONS ioctls
 *	add expect_बंद support
 *
 * 2002.05.30 - Joel Becker <joel.becker@oracle.com>
 *	Added Matt Domsch's nowayout module option.
 */

/*
 *	The eurotech CPU-1220/1410/1420's watchकरोg is a part
 *	of the on-board SUPER I/O device SMSC FDC 37B782.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


अटल अचिन्हित दीर्घ eurwdt_is_खोलो;
अटल पूर्णांक eurwdt_समयout;
अटल अक्षर eur_expect_बंद;
अटल DEFINE_SPINLOCK(eurwdt_lock);

/*
 * You must set these - there is no sane way to probe क्रम this board.
 */

अटल पूर्णांक io = 0x3f0;
अटल पूर्णांक irq = 10;
अटल अक्षर *ev = "int";

#घोषणा WDT_TIMEOUT		60                /* 1 minute */

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 * Some symbolic names
 */

#घोषणा WDT_CTRL_REG		0x30
#घोषणा WDT_OUTPIN_CFG		0xe2
#घोषणा WDT_EVENT_INT		0x00
#घोषणा WDT_EVENT_REBOOT	0x08
#घोषणा WDT_UNIT_SEL		0xf1
#घोषणा WDT_UNIT_SECS		0x80
#घोषणा WDT_TIMEOUT_VAL		0xf2
#घोषणा WDT_TIMER_CFG		0xf3


module_param_hw(io, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(io, "Eurotech WDT io port (default=0x3f0)");
module_param_hw(irq, पूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "Eurotech WDT irq (default=10)");
module_param(ev, अक्षरp, 0);
MODULE_PARM_DESC(ev, "Eurotech WDT event type (default is `int')");


/*
 * Programming support
 */

अटल अंतरभूत व्योम eurwdt_ग_लिखो_reg(u8 index, u8 data)
अणु
	outb(index, io);
	outb(data, io+1);
पूर्ण

अटल अंतरभूत व्योम eurwdt_lock_chip(व्योम)
अणु
	outb(0xaa, io);
पूर्ण

अटल अंतरभूत व्योम eurwdt_unlock_chip(व्योम)
अणु
	outb(0x55, io);
	eurwdt_ग_लिखो_reg(0x07, 0x08);	/* set the logical device */
पूर्ण

अटल अंतरभूत व्योम eurwdt_set_समयout(पूर्णांक समयout)
अणु
	eurwdt_ग_लिखो_reg(WDT_TIMEOUT_VAL, (u8) समयout);
पूर्ण

अटल अंतरभूत व्योम eurwdt_disable_समयr(व्योम)
अणु
	eurwdt_set_समयout(0);
पूर्ण

अटल व्योम eurwdt_activate_समयr(व्योम)
अणु
	eurwdt_disable_समयr();
	eurwdt_ग_लिखो_reg(WDT_CTRL_REG, 0x01);	/* activate the WDT */
	eurwdt_ग_लिखो_reg(WDT_OUTPIN_CFG,
		!म_भेद("int", ev) ? WDT_EVENT_INT : WDT_EVENT_REBOOT);

	/* Setting पूर्णांकerrupt line */
	अगर (irq == 2 || irq > 15 || irq < 0) अणु
		pr_err("invalid irq number\n");
		irq = 0;	/* अगर invalid we disable पूर्णांकerrupt */
	पूर्ण
	अगर (irq == 0)
		pr_info("interrupt disabled\n");

	eurwdt_ग_लिखो_reg(WDT_TIMER_CFG, irq << 4);

	eurwdt_ग_लिखो_reg(WDT_UNIT_SEL, WDT_UNIT_SECS);	/* we use seconds */
	eurwdt_set_समयout(0);	/* the शेष समयout */
पूर्ण


/*
 * Kernel methods.
 */

अटल irqवापस_t eurwdt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	pr_crit("timeout WDT timeout\n");

#अगर_घोषित ONLY_TESTING
	pr_crit("Would Reboot\n");
#अन्यथा
	pr_crit("Initiating system reboot\n");
	emergency_restart();
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण


/**
 * eurwdt_ping:
 *
 * Reload counter one with the watchकरोg समयout.
 */

अटल व्योम eurwdt_ping(व्योम)
अणु
	/* Write the watchकरोg शेष value */
	eurwdt_set_समयout(eurwdt_समयout);
पूर्ण

/**
 * eurwdt_ग_लिखो:
 * @file: file handle to the watchकरोg
 * @buf: buffer to ग_लिखो (unused as data करोes not matter here
 * @count: count of bytes
 * @ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 * A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 * ग_लिखो of data will करो, as we we करोn't define content meaning.
 */

अटल sमाप_प्रकार eurwdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			eur_expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					eur_expect_बंद = 42;
			पूर्ण
		पूर्ण
		spin_lock(&eurwdt_lock);
		eurwdt_ping();	/* the शेष समयout */
		spin_unlock(&eurwdt_lock);
	पूर्ण
	वापस count;
पूर्ण

/**
 * eurwdt_ioctl:
 * @file: file handle to the device
 * @cmd: watchकरोg command
 * @arg: argument poपूर्णांकer
 *
 * The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 * according to their available features.
 */

अटल दीर्घ eurwdt_ioctl(काष्ठा file *file,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options	  = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity	  = "WDT Eurotech CPU-1220/1410",
	पूर्ण;

	पूर्णांक समय;
	पूर्णांक options, retval = -EINVAL;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(options, p))
			वापस -EFAULT;
		spin_lock(&eurwdt_lock);
		अगर (options & WDIOS_DISABLECARD) अणु
			eurwdt_disable_समयr();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			eurwdt_activate_समयr();
			eurwdt_ping();
			retval = 0;
		पूर्ण
		spin_unlock(&eurwdt_lock);
		वापस retval;

	हाल WDIOC_KEEPALIVE:
		spin_lock(&eurwdt_lock);
		eurwdt_ping();
		spin_unlock(&eurwdt_lock);
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (copy_from_user(&समय, p, माप(पूर्णांक)))
			वापस -EFAULT;

		/* Sanity check */
		अगर (समय < 0 || समय > 255)
			वापस -EINVAL;

		spin_lock(&eurwdt_lock);
		eurwdt_समयout = समय;
		eurwdt_set_समयout(समय);
		spin_unlock(&eurwdt_lock);
		fallthrough;

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(eurwdt_समयout, p);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/**
 * eurwdt_खोलो:
 * @inode: inode of device
 * @file: file handle to device
 *
 * The misc device has been खोलोed. The watchकरोg device is single
 * खोलो and on खोलोing we load the counter.
 */

अटल पूर्णांक eurwdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &eurwdt_is_खोलो))
		वापस -EBUSY;
	eurwdt_समयout = WDT_TIMEOUT;	/* initial समयout */
	/* Activate the WDT */
	eurwdt_activate_समयr();
	वापस stream_खोलो(inode, file);
पूर्ण

/**
 * eurwdt_release:
 * @inode: inode to board
 * @file: file handle to board
 *
 * The watchकरोg has a configurable API. There is a religious dispute
 * between people who want their watchकरोg to be able to shut करोwn and
 * those who want to be sure अगर the watchकरोg manager dies the machine
 * reboots. In the क्रमmer हाल we disable the counters, in the latter
 * हाल you have to खोलो it again very soon.
 */

अटल पूर्णांक eurwdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (eur_expect_बंद == 42)
		eurwdt_disable_समयr();
	अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		eurwdt_ping();
	पूर्ण
	clear_bit(0, &eurwdt_is_खोलो);
	eur_expect_बंद = 0;
	वापस 0;
पूर्ण

/**
 * eurwdt_notअगरy_sys:
 * @this: our notअगरier block
 * @code: the event being reported
 * @unused: unused
 *
 * Our notअगरier is called on प्रणाली shutकरोwns. We want to turn the card
 * off at reboot otherwise the machine will reboot again during memory
 * test or worse yet during the following fsck. This would suck, in fact
 * trust me - अगर it happens it करोes suck.
 */

अटल पूर्णांक eurwdt_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
	व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		eurwdt_disable_समयr();	/* Turn the card off */

	वापस NOTIFY_DONE;
पूर्ण

/*
 * Kernel Interfaces
 */


अटल स्थिर काष्ठा file_operations eurwdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= eurwdt_ग_लिखो,
	.unlocked_ioctl	= eurwdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= eurwdt_खोलो,
	.release	= eurwdt_release,
पूर्ण;

अटल काष्ठा miscdevice eurwdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &eurwdt_fops,
पूर्ण;

/*
 * The WDT card needs to learn about soft shutकरोwns in order to
 * turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block eurwdt_notअगरier = अणु
	.notअगरier_call = eurwdt_notअगरy_sys,
पूर्ण;

/**
 * cleanup_module:
 *
 * Unload the watchकरोg. You cannot करो this with any file handles खोलो.
 * If your watchकरोg is set to जारी ticking on बंद and you unload
 * it, well it keeps ticking. We won't get the पूर्णांकerrupt but the board
 * will not touch PC memory so all is fine. You just have to load a new
 * module in 60 seconds or reboot.
 */

अटल व्योम __निकास eurwdt_निकास(व्योम)
अणु
	eurwdt_lock_chip();

	misc_deरेजिस्टर(&eurwdt_miscdev);

	unरेजिस्टर_reboot_notअगरier(&eurwdt_notअगरier);
	release_region(io, 2);
	मुक्त_irq(irq, शून्य);
पूर्ण

/**
 * eurwdt_init:
 *
 * Set up the WDT watchकरोg board. After grabbing the resources
 * we require we need also to unlock the device.
 * The खोलो() function will actually kick the board off.
 */

अटल पूर्णांक __init eurwdt_init(व्योम)
अणु
	पूर्णांक ret;

	ret = request_irq(irq, eurwdt_पूर्णांकerrupt, 0, "eurwdt", शून्य);
	अगर (ret) अणु
		pr_err("IRQ %d is not free\n", irq);
		जाओ out;
	पूर्ण

	अगर (!request_region(io, 2, "eurwdt")) अणु
		pr_err("IO %X is not free\n", io);
		ret = -EBUSY;
		जाओ outirq;
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&eurwdt_notअगरier);
	अगर (ret) अणु
		pr_err("can't register reboot notifier (err=%d)\n", ret);
		जाओ outreg;
	पूर्ण

	ret = misc_रेजिस्टर(&eurwdt_miscdev);
	अगर (ret) अणु
		pr_err("can't misc_register on minor=%d\n", WATCHDOG_MINOR);
		जाओ outreboot;
	पूर्ण

	eurwdt_unlock_chip();

	ret = 0;
	pr_info("Eurotech WDT driver 0.01 at %X (Interrupt %d) - timeout event: %s\n",
		io, irq, (!म_भेद("int", ev) ? "int" : "reboot"));

out:
	वापस ret;

outreboot:
	unरेजिस्टर_reboot_notअगरier(&eurwdt_notअगरier);

outreg:
	release_region(io, 2);

outirq:
	मुक्त_irq(irq, शून्य);
	जाओ out;
पूर्ण

module_init(eurwdt_init);
module_निकास(eurwdt_निकास);

MODULE_AUTHOR("Rodolfo Giometti");
MODULE_DESCRIPTION("Driver for Eurotech CPU-1220/1410 on board watchdog");
MODULE_LICENSE("GPL");
