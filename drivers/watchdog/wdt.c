<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Industrial Computer Source WDT501 driver
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
 *	Release 0.10.
 *
 *	Fixes
 *		Dave Gregorich	:	Modularisation and minor bugs
 *		Alan Cox	:	Added the watchकरोg ioctl() stuff
 *		Alan Cox	:	Fixed the reboot problem (as noted by
 *					Matt Crocker).
 *		Alan Cox	:	Added wdt= boot option
 *		Alan Cox	:	Cleaned up copy/user stuff
 *		Tim Hockin	:	Added insmod parameters, comment
 *					cleanup, parameterized समयout
 *		Tigran Aivazian	:	Reकाष्ठाured wdt_init() to handle
 *					failures
 *		Joel Becker	:	Added WDIOC_GET/SETTIMEOUT
 *		Matt Domsch	:	Added nowayout module option
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

#समावेश "wd501p.h"

अटल अचिन्हित दीर्घ wdt_is_खोलो;
अटल अक्षर expect_बंद;

/*
 *	Module parameters
 */

#घोषणा WD_TIMO 60			/* Default heartbeat = 60 seconds */

अटल पूर्णांक heartbeat = WD_TIMO;
अटल पूर्णांक wd_heartbeat;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
	"Watchdog heartbeat in seconds. (0 < heartbeat < 65536, default="
				__MODULE_STRING(WD_TIMO) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/* You must set these - there is no sane way to probe क्रम this board. */
अटल पूर्णांक io = 0x240;
अटल पूर्णांक irq = 11;

अटल DEFINE_SPINLOCK(wdt_lock);

module_param_hw(io, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(io, "WDT io port (default=0x240)");
module_param_hw(irq, पूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "WDT irq (default=11)");

/* Support क्रम the Fan Tachometer on the WDT501-P */
अटल पूर्णांक tachometer;
module_param(tachometer, पूर्णांक, 0);
MODULE_PARM_DESC(tachometer,
		"WDT501-P Fan Tachometer support (0=disable, default=0)");

अटल पूर्णांक type = 500;
module_param(type, पूर्णांक, 0);
MODULE_PARM_DESC(type,
		"WDT501-P Card type (500 or 501, default=500)");

/*
 *	Programming support
 */

अटल व्योम wdt_ctr_mode(पूर्णांक ctr, पूर्णांक mode)
अणु
	ctr <<= 6;
	ctr |= 0x30;
	ctr |= (mode << 1);
	outb_p(ctr, WDT_CR);
पूर्ण

अटल व्योम wdt_ctr_load(पूर्णांक ctr, पूर्णांक val)
अणु
	outb_p(val&0xFF, WDT_COUNT0+ctr);
	outb_p(val>>8, WDT_COUNT0+ctr);
पूर्ण

/**
 *	wdt_start:
 *
 *	Start the watchकरोg driver.
 */

अटल पूर्णांक wdt_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&wdt_lock, flags);
	inb_p(WDT_DC);			/* Disable watchकरोg */
	wdt_ctr_mode(0, 3);		/* Program CTR0 क्रम Mode 3:
						Square Wave Generator */
	wdt_ctr_mode(1, 2);		/* Program CTR1 क्रम Mode 2:
						Rate Generator */
	wdt_ctr_mode(2, 0);		/* Program CTR2 क्रम Mode 0:
						Pulse on Terminal Count */
	wdt_ctr_load(0, 8948);		/* Count at 100Hz */
	wdt_ctr_load(1, wd_heartbeat);	/* Heartbeat */
	wdt_ctr_load(2, 65535);		/* Length of reset pulse */
	outb_p(0, WDT_DC);		/* Enable watchकरोg */
	spin_unlock_irqrestore(&wdt_lock, flags);
	वापस 0;
पूर्ण

/**
 *	wdt_stop:
 *
 *	Stop the watchकरोg driver.
 */

अटल पूर्णांक wdt_stop(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&wdt_lock, flags);
	/* Turn the card off */
	inb_p(WDT_DC);			/* Disable watchकरोg */
	wdt_ctr_load(2, 0);		/* 0 length reset pulses now */
	spin_unlock_irqrestore(&wdt_lock, flags);
	वापस 0;
पूर्ण

/**
 *	wdt_ping:
 *
 *	Reload counter one with the watchकरोg heartbeat. We करोn't bother
 *	reloading the cascade counter.
 */

अटल व्योम wdt_ping(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&wdt_lock, flags);
	/* Write a watchकरोg value */
	inb_p(WDT_DC);			/* Disable watchकरोg */
	wdt_ctr_mode(1, 2);		/* Re-Program CTR1 क्रम Mode 2:
							Rate Generator */
	wdt_ctr_load(1, wd_heartbeat);	/* Heartbeat */
	outb_p(0, WDT_DC);		/* Enable watchकरोg */
	spin_unlock_irqrestore(&wdt_lock, flags);
पूर्ण

/**
 *	wdt_set_heartbeat:
 *	@t:		the new heartbeat value that needs to be set.
 *
 *	Set a new heartbeat value क्रम the watchकरोg device. If the heartbeat
 *	value is incorrect we keep the old value and वापस -EINVAL. If
 *	successful we वापस 0.
 */

अटल पूर्णांक wdt_set_heartbeat(पूर्णांक t)
अणु
	अगर (t < 1 || t > 65535)
		वापस -EINVAL;

	heartbeat = t;
	wd_heartbeat = t * 100;
	वापस 0;
पूर्ण

/**
 *	wdt_get_status:
 *
 *	Extract the status inक्रमmation from a WDT watchकरोg device. There are
 *	several board variants so we have to know which bits are valid. Some
 *	bits शेष to one and some to zero in order to be maximally painful.
 *
 *	we then map the bits onto the status ioctl flags.
 */

अटल पूर्णांक wdt_get_status(व्योम)
अणु
	अचिन्हित अक्षर new_status;
	पूर्णांक status = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdt_lock, flags);
	new_status = inb_p(WDT_SR);
	spin_unlock_irqrestore(&wdt_lock, flags);

	अगर (new_status & WDC_SR_ISOI0)
		status |= WDIOF_EXTERN1;
	अगर (new_status & WDC_SR_ISII1)
		status |= WDIOF_EXTERN2;
	अगर (type == 501) अणु
		अगर (!(new_status & WDC_SR_TGOOD))
			status |= WDIOF_OVERHEAT;
		अगर (!(new_status & WDC_SR_PSUOVER))
			status |= WDIOF_POWEROVER;
		अगर (!(new_status & WDC_SR_PSUUNDR))
			status |= WDIOF_POWERUNDER;
		अगर (tachometer) अणु
			अगर (!(new_status & WDC_SR_FANGOOD))
				status |= WDIOF_FANFAULT;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 *	wdt_get_temperature:
 *
 *	Reports the temperature in degrees Fahrenheit. The API is in
 *	farenheit. It was deचिन्हित by an imperial measurement luddite.
 */

अटल पूर्णांक wdt_get_temperature(व्योम)
अणु
	अचिन्हित लघु c;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdt_lock, flags);
	c = inb_p(WDT_RT);
	spin_unlock_irqrestore(&wdt_lock, flags);
	वापस (c * 11 / 15) + 7;
पूर्ण

अटल व्योम wdt_decode_501(पूर्णांक status)
अणु
	अगर (!(status & WDC_SR_TGOOD))
		pr_crit("Overheat alarm (%d)\n", inb_p(WDT_RT));
	अगर (!(status & WDC_SR_PSUOVER))
		pr_crit("PSU over voltage\n");
	अगर (!(status & WDC_SR_PSUUNDR))
		pr_crit("PSU under voltage\n");
पूर्ण

/**
 *	wdt_पूर्णांकerrupt:
 *	@irq:		Interrupt number
 *	@dev_id:	Unused as we करोn't allow multiple devices.
 *
 *	Handle an पूर्णांकerrupt from the board. These are उठाओd when the status
 *	map changes in what the board considers an पूर्णांकeresting way. That means
 *	a failure condition occurring.
 */

अटल irqवापस_t wdt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/*
	 *	Read the status रेजिस्टर see what is up and
	 *	then prपूर्णांकk it.
	 */
	अचिन्हित अक्षर status;

	spin_lock(&wdt_lock);
	status = inb_p(WDT_SR);

	pr_crit("WDT status %d\n", status);

	अगर (type == 501) अणु
		wdt_decode_501(status);
		अगर (tachometer) अणु
			अगर (!(status & WDC_SR_FANGOOD))
				pr_crit("Possible fan fault\n");
		पूर्ण
	पूर्ण
	अगर (!(status & WDC_SR_WCCR)) अणु
#अगर_घोषित SOFTWARE_REBOOT
#अगर_घोषित ONLY_TESTING
		pr_crit("Would Reboot\n");
#अन्यथा
		pr_crit("Initiating system reboot\n");
		emergency_restart();
#पूर्ण_अगर
#अन्यथा
		pr_crit("Reset in 5ms\n");
#पूर्ण_अगर
	पूर्ण
	spin_unlock(&wdt_lock);
	वापस IRQ_HANDLED;
पूर्ण


/**
 *	wdt_ग_लिखो:
 *	@file: file handle to the watchकरोg
 *	@buf: buffer to ग_लिखो (unused as data करोes not matter here
 *	@count: count of bytes
 *	@ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 *	A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 *	ग_लिखो of data will करो, as we we करोn't define content meaning.
 */

अटल sमाप_प्रकार wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
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
		wdt_ping();
	पूर्ण
	वापस count;
पूर्ण

/**
 *	wdt_ioctl:
 *	@file: file handle to the device
 *	@cmd: watchकरोg command
 *	@arg: argument poपूर्णांकer
 *
 *	The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *	according to their available features. We only actually usefully support
 *	querying capabilities and current status.
 */

अटल दीर्घ wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	पूर्णांक new_heartbeat;
	पूर्णांक status;

	काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_SETTIMEOUT|
					WDIOF_MAGICCLOSE|
					WDIOF_KEEPALIVEPING,
		.firmware_version =	1,
		.identity =		"WDT500/501",
	पूर्ण;

	/* Add options according to the card we have */
	ident.options |= (WDIOF_EXTERN1|WDIOF_EXTERN2);
	अगर (type == 501) अणु
		ident.options |= (WDIOF_OVERHEAT|WDIOF_POWERUNDER|
							WDIOF_POWEROVER);
		अगर (tachometer)
			ident.options |= WDIOF_FANFAULT;
	पूर्ण

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
		status = wdt_get_status();
		वापस put_user(status, p);
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_KEEPALIVE:
		wdt_ping();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_heartbeat, p))
			वापस -EFAULT;
		अगर (wdt_set_heartbeat(new_heartbeat))
			वापस -EINVAL;
		wdt_ping();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(heartbeat, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/**
 *	wdt_खोलो:
 *	@inode: inode of device
 *	@file: file handle to device
 *
 *	The watchकरोg device has been खोलोed. The watchकरोg device is single
 *	खोलो and on खोलोing we load the counters. Counter zero is a 100Hz
 *	cascade, पूर्णांकo counter 1 which करोwncounts to reboot. When the counter
 *	triggers counter 2 करोwncounts the length of the reset pulse which
 *	set set to be as दीर्घ as possible.
 */

अटल पूर्णांक wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &wdt_is_खोलो))
		वापस -EBUSY;
	/*
	 *	Activate
	 */
	wdt_start();
	वापस stream_खोलो(inode, file);
पूर्ण

/**
 *	wdt_release:
 *	@inode: inode to board
 *	@file: file handle to board
 *
 *	The watchकरोg has a configurable API. There is a religious dispute
 *	between people who want their watchकरोg to be able to shut करोwn and
 *	those who want to be sure अगर the watchकरोg manager dies the machine
 *	reboots. In the क्रमmer हाल we disable the counters, in the latter
 *	हाल you have to खोलो it again very soon.
 */

अटल पूर्णांक wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		wdt_stop();
		clear_bit(0, &wdt_is_खोलो);
	पूर्ण अन्यथा अणु
		pr_crit("WDT device closed unexpectedly.  WDT will not stop!\n");
		wdt_ping();
	पूर्ण
	expect_बंद = 0;
	वापस 0;
पूर्ण

/**
 *	wdt_temp_पढ़ो:
 *	@file: file handle to the watchकरोg board
 *	@buf: buffer to ग_लिखो 1 byte पूर्णांकo
 *	@count: length of buffer
 *	@ptr: offset (no seek allowed)
 *
 *	Temp_पढ़ो reports the temperature in degrees Fahrenheit. The API is in
 *	farenheit. It was deचिन्हित by an imperial measurement luddite.
 */

अटल sमाप_प्रकार wdt_temp_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
						माप_प्रकार count, loff_t *ptr)
अणु
	पूर्णांक temperature = wdt_get_temperature();

	अगर (copy_to_user(buf, &temperature, 1))
		वापस -EFAULT;

	वापस 1;
पूर्ण

/**
 *	wdt_temp_खोलो:
 *	@inode: inode of device
 *	@file: file handle to device
 *
 *	The temperature device has been खोलोed.
 */

अटल पूर्णांक wdt_temp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस stream_खोलो(inode, file);
पूर्ण

/**
 *	wdt_temp_release:
 *	@inode: inode to board
 *	@file: file handle to board
 *
 *	The temperature device has been बंदd.
 */

अटल पूर्णांक wdt_temp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/**
 *	notअगरy_sys:
 *	@this: our notअगरier block
 *	@code: the event being reported
 *	@unused: unused
 *
 *	Our notअगरier is called on प्रणाली shutकरोwns. We want to turn the card
 *	off at reboot otherwise the machine will reboot again during memory
 *	test or worse yet during the following fsck. This would suck, in fact
 *	trust me - अगर it happens it करोes suck.
 */

अटल पूर्णांक wdt_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
	व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdt_stop();
	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Kernel Interfaces
 */


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
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &wdt_fops,
पूर्ण;

अटल स्थिर काष्ठा file_operations wdt_temp_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= wdt_temp_पढ़ो,
	.खोलो		= wdt_temp_खोलो,
	.release	= wdt_temp_release,
पूर्ण;

अटल काष्ठा miscdevice temp_miscdev = अणु
	.minor	= TEMP_MINOR,
	.name	= "temperature",
	.fops	= &wdt_temp_fops,
पूर्ण;

/*
 *	The WDT card needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block wdt_notअगरier = अणु
	.notअगरier_call = wdt_notअगरy_sys,
पूर्ण;

/**
 *	cleanup_module:
 *
 *	Unload the watchकरोg. You cannot करो this with any file handles खोलो.
 *	If your watchकरोg is set to जारी ticking on बंद and you unload
 *	it, well it keeps ticking. We won't get the पूर्णांकerrupt but the board
 *	will not touch PC memory so all is fine. You just have to load a new
 *	module in 60 seconds or reboot.
 */

अटल व्योम __निकास wdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&wdt_miscdev);
	अगर (type == 501)
		misc_deरेजिस्टर(&temp_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	मुक्त_irq(irq, शून्य);
	release_region(io, 8);
पूर्ण

/**
 *	wdt_init:
 *
 *	Set up the WDT watchकरोg board. All we have to करो is grab the
 *	resources we require and bitch अगर anyone beat us to them.
 *	The खोलो() function will actually kick the board off.
 */

अटल पूर्णांक __init wdt_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (type != 500 && type != 501) अणु
		pr_err("unknown card type '%d'\n", type);
		वापस -ENODEV;
	पूर्ण

	/* Check that the heartbeat value is within it's range;
	   अगर not reset to the शेष */
	अगर (wdt_set_heartbeat(heartbeat)) अणु
		wdt_set_heartbeat(WD_TIMO);
		pr_info("heartbeat value must be 0 < heartbeat < 65536, using %d\n",
			WD_TIMO);
	पूर्ण

	अगर (!request_region(io, 8, "wdt501p")) अणु
		pr_err("I/O address 0x%04x already in use\n", io);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = request_irq(irq, wdt_पूर्णांकerrupt, 0, "wdt501p", शून्य);
	अगर (ret) अणु
		pr_err("IRQ %d is not free\n", irq);
		जाओ outreg;
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	अगर (ret) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		जाओ outirq;
	पूर्ण

	अगर (type == 501) अणु
		ret = misc_रेजिस्टर(&temp_miscdev);
		अगर (ret) अणु
			pr_err("cannot register miscdev on minor=%d (err=%d)\n",
			       TEMP_MINOR, ret);
			जाओ outrbt;
		पूर्ण
	पूर्ण

	ret = misc_रेजिस्टर(&wdt_miscdev);
	अगर (ret) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ ouपंचांगisc;
	पूर्ण

	pr_info("WDT500/501-P driver 0.10 at 0x%04x (Interrupt %d). heartbeat=%d sec (nowayout=%d)\n",
		io, irq, heartbeat, nowayout);
	अगर (type == 501)
		pr_info("Fan Tachometer is %s\n",
			tachometer ? "Enabled" : "Disabled");
	वापस 0;

ouपंचांगisc:
	अगर (type == 501)
		misc_deरेजिस्टर(&temp_miscdev);
outrbt:
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
outirq:
	मुक्त_irq(irq, शून्य);
outreg:
	release_region(io, 8);
out:
	वापस ret;
पूर्ण

module_init(wdt_init);
module_निकास(wdt_निकास);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("Driver for ISA ICS watchdog cards (WDT500/501)");
MODULE_LICENSE("GPL");
