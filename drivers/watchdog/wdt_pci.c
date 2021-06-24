<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Industrial Computer Source PCI-WDT500/501 driver
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
 *		Tim Hockin	:	Added insmod parameters, comment cleanup
 *					Parameterized समयout
 *		JP Nollmann	:	Added support क्रम PCI wdt501p
 *		Alan Cox	:	Split ISA and PCI cards पूर्णांकo two drivers
 *		Jeff Garzik	:	PCI cleanups
 *		Tigran Aivazian	:	Reकाष्ठाured wdtpci_init_one() to handle
 *					failures
 *		Joel Becker	:	Added WDIOC_GET/SETTIMEOUT
 *		Zwane Mwaikambo	:	Magic अक्षर closing, locking changes,
 *					cleanups
 *		Matt Domsch	:	nowayout module option
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


#घोषणा WDT_IS_PCI
#समावेश "wd501p.h"

/* We can only use 1 card due to the /dev/watchकरोg restriction */
अटल पूर्णांक dev_count;

अटल अचिन्हित दीर्घ खोलो_lock;
अटल DEFINE_SPINLOCK(wdtpci_lock);
अटल अक्षर expect_बंद;

अटल resource_माप_प्रकार io;
अटल पूर्णांक irq;

/* Default समयout */
#घोषणा WD_TIMO 60			/* Default heartbeat = 60 seconds */

अटल पूर्णांक heartbeat = WD_TIMO;
अटल पूर्णांक wd_heartbeat;
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat,
		"Watchdog heartbeat in seconds. (0<heartbeat<65536, default="
				__MODULE_STRING(WD_TIMO) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/* Support क्रम the Fan Tachometer on the PCI-WDT501 */
अटल पूर्णांक tachometer;
module_param(tachometer, पूर्णांक, 0);
MODULE_PARM_DESC(tachometer,
		"PCI-WDT501 Fan Tachometer support (0=disable, default=0)");

अटल पूर्णांक type = 500;
module_param(type, पूर्णांक, 0);
MODULE_PARM_DESC(type,
		"PCI-WDT501 Card type (500 or 501 , default=500)");

/*
 *	Programming support
 */

अटल व्योम wdtpci_ctr_mode(पूर्णांक ctr, पूर्णांक mode)
अणु
	ctr <<= 6;
	ctr |= 0x30;
	ctr |= (mode << 1);
	outb(ctr, WDT_CR);
	udelay(8);
पूर्ण

अटल व्योम wdtpci_ctr_load(पूर्णांक ctr, पूर्णांक val)
अणु
	outb(val & 0xFF, WDT_COUNT0 + ctr);
	udelay(8);
	outb(val >> 8, WDT_COUNT0 + ctr);
	udelay(8);
पूर्ण

/**
 *	wdtpci_start:
 *
 *	Start the watchकरोg driver.
 */

अटल पूर्णांक wdtpci_start(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdtpci_lock, flags);

	/*
	 * "pet" the watchकरोg, as Access says.
	 * This resets the घड़ी outमाला_दो.
	 */
	inb(WDT_DC);			/* Disable watchकरोg */
	udelay(8);
	wdtpci_ctr_mode(2, 0);		/* Program CTR2 क्रम Mode 0:
						Pulse on Terminal Count */
	outb(0, WDT_DC);		/* Enable watchकरोg */
	udelay(8);
	inb(WDT_DC);			/* Disable watchकरोg */
	udelay(8);
	outb(0, WDT_CLOCK);		/* 2.0833MHz घड़ी */
	udelay(8);
	inb(WDT_BUZZER);		/* disable */
	udelay(8);
	inb(WDT_OPTONOTRST);		/* disable */
	udelay(8);
	inb(WDT_OPTORST);		/* disable */
	udelay(8);
	inb(WDT_PROGOUT);		/* disable */
	udelay(8);
	wdtpci_ctr_mode(0, 3);		/* Program CTR0 क्रम Mode 3:
						Square Wave Generator */
	wdtpci_ctr_mode(1, 2);		/* Program CTR1 क्रम Mode 2:
						Rate Generator */
	wdtpci_ctr_mode(2, 1);		/* Program CTR2 क्रम Mode 1:
						Retriggerable One-Shot */
	wdtpci_ctr_load(0, 20833);	/* count at 100Hz */
	wdtpci_ctr_load(1, wd_heartbeat);/* Heartbeat */
	/* DO NOT LOAD CTR2 on PCI card! -- JPN */
	outb(0, WDT_DC);		/* Enable watchकरोg */
	udelay(8);

	spin_unlock_irqrestore(&wdtpci_lock, flags);
	वापस 0;
पूर्ण

/**
 *	wdtpci_stop:
 *
 *	Stop the watchकरोg driver.
 */

अटल पूर्णांक wdtpci_stop(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/* Turn the card off */
	spin_lock_irqsave(&wdtpci_lock, flags);
	inb(WDT_DC);			/* Disable watchकरोg */
	udelay(8);
	wdtpci_ctr_load(2, 0);		/* 0 length reset pulses now */
	spin_unlock_irqrestore(&wdtpci_lock, flags);
	वापस 0;
पूर्ण

/**
 *	wdtpci_ping:
 *
 *	Reload counter one with the watchकरोg heartbeat. We करोn't bother
 *	reloading the cascade counter.
 */

अटल पूर्णांक wdtpci_ping(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdtpci_lock, flags);
	/* Write a watchकरोg value */
	inb(WDT_DC);			/* Disable watchकरोg */
	udelay(8);
	wdtpci_ctr_mode(1, 2);		/* Re-Program CTR1 क्रम Mode 2:
							Rate Generator */
	wdtpci_ctr_load(1, wd_heartbeat);/* Heartbeat */
	outb(0, WDT_DC);		/* Enable watchकरोg */
	udelay(8);
	spin_unlock_irqrestore(&wdtpci_lock, flags);
	वापस 0;
पूर्ण

/**
 *	wdtpci_set_heartbeat:
 *	@t:		the new heartbeat value that needs to be set.
 *
 *	Set a new heartbeat value क्रम the watchकरोg device. If the heartbeat
 *	value is incorrect we keep the old value and वापस -EINVAL.
 *	If successful we वापस 0.
 */
अटल पूर्णांक wdtpci_set_heartbeat(पूर्णांक t)
अणु
	/* Arbitrary, can't find the card's limits */
	अगर (t < 1 || t > 65535)
		वापस -EINVAL;

	heartbeat = t;
	wd_heartbeat = t * 100;
	वापस 0;
पूर्ण

/**
 *	wdtpci_get_status:
 *	@status:		the new status.
 *
 *	Extract the status inक्रमmation from a WDT watchकरोg device. There are
 *	several board variants so we have to know which bits are valid. Some
 *	bits शेष to one and some to zero in order to be maximally painful.
 *
 *	we then map the bits onto the status ioctl flags.
 */

अटल पूर्णांक wdtpci_get_status(पूर्णांक *status)
अणु
	अचिन्हित अक्षर new_status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdtpci_lock, flags);
	new_status = inb(WDT_SR);
	spin_unlock_irqrestore(&wdtpci_lock, flags);

	*status = 0;
	अगर (new_status & WDC_SR_ISOI0)
		*status |= WDIOF_EXTERN1;
	अगर (new_status & WDC_SR_ISII1)
		*status |= WDIOF_EXTERN2;
	अगर (type == 501) अणु
		अगर (!(new_status & WDC_SR_TGOOD))
			*status |= WDIOF_OVERHEAT;
		अगर (!(new_status & WDC_SR_PSUOVER))
			*status |= WDIOF_POWEROVER;
		अगर (!(new_status & WDC_SR_PSUUNDR))
			*status |= WDIOF_POWERUNDER;
		अगर (tachometer) अणु
			अगर (!(new_status & WDC_SR_FANGOOD))
				*status |= WDIOF_FANFAULT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	wdtpci_get_temperature:
 *
 *	Reports the temperature in degrees Fahrenheit. The API is in
 *	farenheit. It was deचिन्हित by an imperial measurement luddite.
 */

अटल पूर्णांक wdtpci_get_temperature(पूर्णांक *temperature)
अणु
	अचिन्हित लघु c;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&wdtpci_lock, flags);
	c = inb(WDT_RT);
	udelay(8);
	spin_unlock_irqrestore(&wdtpci_lock, flags);
	*temperature = (c * 11 / 15) + 7;
	वापस 0;
पूर्ण

/**
 *	wdtpci_पूर्णांकerrupt:
 *	@irq:		Interrupt number
 *	@dev_id:	Unused as we करोn't allow multiple devices.
 *
 *	Handle an पूर्णांकerrupt from the board. These are उठाओd when the status
 *	map changes in what the board considers an पूर्णांकeresting way. That means
 *	a failure condition occurring.
 */

अटल irqवापस_t wdtpci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/*
	 *	Read the status रेजिस्टर see what is up and
	 *	then prपूर्णांकk it.
	 */
	अचिन्हित अक्षर status;

	spin_lock(&wdtpci_lock);

	status = inb(WDT_SR);
	udelay(8);

	pr_crit("status %d\n", status);

	अगर (type == 501) अणु
		अगर (!(status & WDC_SR_TGOOD)) अणु
			pr_crit("Overheat alarm (%d)\n", inb(WDT_RT));
			udelay(8);
		पूर्ण
		अगर (!(status & WDC_SR_PSUOVER))
			pr_crit("PSU over voltage\n");
		अगर (!(status & WDC_SR_PSUUNDR))
			pr_crit("PSU under voltage\n");
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
	spin_unlock(&wdtpci_lock);
	वापस IRQ_HANDLED;
पूर्ण


/**
 *	wdtpci_ग_लिखो:
 *	@file: file handle to the watchकरोg
 *	@buf: buffer to ग_लिखो (unused as data करोes not matter here
 *	@count: count of bytes
 *	@ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 *	A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 *	ग_लिखो of data will करो, as we we करोn't define content meaning.
 */

अटल sमाप_प्रकार wdtpci_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
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
		wdtpci_ping();
	पूर्ण
	वापस count;
पूर्ण

/**
 *	wdtpci_ioctl:
 *	@file: file handle to the device
 *	@cmd: watchकरोg command
 *	@arg: argument poपूर्णांकer
 *
 *	The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *	according to their available features. We only actually usefully support
 *	querying capabilities and current status.
 */

अटल दीर्घ wdtpci_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
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
		.identity =		"PCI-WDT500/501",
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
		wdtpci_get_status(&status);
		वापस put_user(status, p);
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_KEEPALIVE:
		wdtpci_ping();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_heartbeat, p))
			वापस -EFAULT;
		अगर (wdtpci_set_heartbeat(new_heartbeat))
			वापस -EINVAL;
		wdtpci_ping();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(heartbeat, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/**
 *	wdtpci_खोलो:
 *	@inode: inode of device
 *	@file: file handle to device
 *
 *	The watchकरोg device has been खोलोed. The watchकरोg device is single
 *	खोलो and on खोलोing we load the counters. Counter zero is a 100Hz
 *	cascade, पूर्णांकo counter 1 which करोwncounts to reboot. When the counter
 *	triggers counter 2 करोwncounts the length of the reset pulse which
 *	set set to be as दीर्घ as possible.
 */

अटल पूर्णांक wdtpci_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &खोलो_lock))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);
	/*
	 *	Activate
	 */
	wdtpci_start();
	वापस stream_खोलो(inode, file);
पूर्ण

/**
 *	wdtpci_release:
 *	@inode: inode to board
 *	@file: file handle to board
 *
 *	The watchकरोg has a configurable API. There is a religious dispute
 *	between people who want their watchकरोg to be able to shut करोwn and
 *	those who want to be sure अगर the watchकरोg manager dies the machine
 *	reboots. In the क्रमmer हाल we disable the counters, in the latter
 *	हाल you have to खोलो it again very soon.
 */

अटल पूर्णांक wdtpci_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		wdtpci_stop();
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping timer!\n");
		wdtpci_ping();
	पूर्ण
	expect_बंद = 0;
	clear_bit(0, &खोलो_lock);
	वापस 0;
पूर्ण

/**
 *	wdtpci_temp_पढ़ो:
 *	@file: file handle to the watchकरोg board
 *	@buf: buffer to ग_लिखो 1 byte पूर्णांकo
 *	@count: length of buffer
 *	@ptr: offset (no seek allowed)
 *
 *	Read reports the temperature in degrees Fahrenheit. The API is in
 *	fahrenheit. It was deचिन्हित by an imperial measurement luddite.
 */

अटल sमाप_प्रकार wdtpci_temp_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
						माप_प्रकार count, loff_t *ptr)
अणु
	पूर्णांक temperature;

	अगर (wdtpci_get_temperature(&temperature))
		वापस -EFAULT;

	अगर (copy_to_user(buf, &temperature, 1))
		वापस -EFAULT;

	वापस 1;
पूर्ण

/**
 *	wdtpci_temp_खोलो:
 *	@inode: inode of device
 *	@file: file handle to device
 *
 *	The temperature device has been खोलोed.
 */

अटल पूर्णांक wdtpci_temp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस stream_खोलो(inode, file);
पूर्ण

/**
 *	wdtpci_temp_release:
 *	@inode: inode to board
 *	@file: file handle to board
 *
 *	The temperature device has been बंदd.
 */

अटल पूर्णांक wdtpci_temp_release(काष्ठा inode *inode, काष्ठा file *file)
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

अटल पूर्णांक wdtpci_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
							व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdtpci_stop();
	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Kernel Interfaces
 */


अटल स्थिर काष्ठा file_operations wdtpci_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= wdtpci_ग_लिखो,
	.unlocked_ioctl	= wdtpci_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= wdtpci_खोलो,
	.release	= wdtpci_release,
पूर्ण;

अटल काष्ठा miscdevice wdtpci_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &wdtpci_fops,
पूर्ण;

अटल स्थिर काष्ठा file_operations wdtpci_temp_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= wdtpci_temp_पढ़ो,
	.खोलो		= wdtpci_temp_खोलो,
	.release	= wdtpci_temp_release,
पूर्ण;

अटल काष्ठा miscdevice temp_miscdev = अणु
	.minor	= TEMP_MINOR,
	.name	= "temperature",
	.fops	= &wdtpci_temp_fops,
पूर्ण;

/*
 *	The WDT card needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block wdtpci_notअगरier = अणु
	.notअगरier_call = wdtpci_notअगरy_sys,
पूर्ण;


अटल पूर्णांक wdtpci_init_one(काष्ठा pci_dev *dev,
					स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret = -EIO;

	dev_count++;
	अगर (dev_count > 1) अणु
		pr_err("This driver only supports one device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (type != 500 && type != 501) अणु
		pr_err("unknown card type '%d'\n", type);
		वापस -ENODEV;
	पूर्ण

	अगर (pci_enable_device(dev)) अणु
		pr_err("Not possible to enable PCI Device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pci_resource_start(dev, 2) == 0x0000) अणु
		pr_err("No I/O-Address for card detected\n");
		ret = -ENODEV;
		जाओ out_pci;
	पूर्ण

	अगर (pci_request_region(dev, 2, "wdt_pci")) अणु
		pr_err("I/O address 0x%llx already in use\n",
		       (अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 2));
		जाओ out_pci;
	पूर्ण

	irq = dev->irq;
	io = pci_resource_start(dev, 2);

	अगर (request_irq(irq, wdtpci_पूर्णांकerrupt, IRQF_SHARED,
			 "wdt_pci", &wdtpci_miscdev)) अणु
		pr_err("IRQ %d is not free\n", irq);
		जाओ out_reg;
	पूर्ण

	pr_info("PCI-WDT500/501 (PCI-WDG-CSM) driver 0.10 at 0x%llx (Interrupt %d)\n",
		(अचिन्हित दीर्घ दीर्घ)io, irq);

	/* Check that the heartbeat value is within its range;
	   अगर not reset to the शेष */
	अगर (wdtpci_set_heartbeat(heartbeat)) अणु
		wdtpci_set_heartbeat(WD_TIMO);
		pr_info("heartbeat value must be 0 < heartbeat < 65536, using %d\n",
			WD_TIMO);
	पूर्ण

	ret = रेजिस्टर_reboot_notअगरier(&wdtpci_notअगरier);
	अगर (ret) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		जाओ out_irq;
	पूर्ण

	अगर (type == 501) अणु
		ret = misc_रेजिस्टर(&temp_miscdev);
		अगर (ret) अणु
			pr_err("cannot register miscdev on minor=%d (err=%d)\n",
			       TEMP_MINOR, ret);
			जाओ out_rbt;
		पूर्ण
	पूर्ण

	ret = misc_रेजिस्टर(&wdtpci_miscdev);
	अगर (ret) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ out_misc;
	पूर्ण

	pr_info("initialized. heartbeat=%d sec (nowayout=%d)\n",
		heartbeat, nowayout);
	अगर (type == 501)
		pr_info("Fan Tachometer is %s\n",
			tachometer ? "Enabled" : "Disabled");

	ret = 0;
out:
	वापस ret;

out_misc:
	अगर (type == 501)
		misc_deरेजिस्टर(&temp_miscdev);
out_rbt:
	unरेजिस्टर_reboot_notअगरier(&wdtpci_notअगरier);
out_irq:
	मुक्त_irq(irq, &wdtpci_miscdev);
out_reg:
	pci_release_region(dev, 2);
out_pci:
	pci_disable_device(dev);
	जाओ out;
पूर्ण


अटल व्योम wdtpci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	/* here we assume only one device will ever have
	 * been picked up and रेजिस्टरed by probe function */
	misc_deरेजिस्टर(&wdtpci_miscdev);
	अगर (type == 501)
		misc_deरेजिस्टर(&temp_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wdtpci_notअगरier);
	मुक्त_irq(irq, &wdtpci_miscdev);
	pci_release_region(pdev, 2);
	pci_disable_device(pdev);
	dev_count--;
पूर्ण


अटल स्थिर काष्ठा pci_device_id wdtpci_pci_tbl[] = अणु
	अणु
		.venकरोr	   = PCI_VENDOR_ID_ACCESSIO,
		.device	   = PCI_DEVICE_ID_ACCESSIO_WDG_CSM,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण,
	अणु 0, पूर्ण, /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, wdtpci_pci_tbl);


अटल काष्ठा pci_driver wdtpci_driver = अणु
	.name		= "wdt_pci",
	.id_table	= wdtpci_pci_tbl,
	.probe		= wdtpci_init_one,
	.हटाओ		= wdtpci_हटाओ_one,
पूर्ण;

module_pci_driver(wdtpci_driver);

MODULE_AUTHOR("JP Nollmann, Alan Cox");
MODULE_DESCRIPTION("Driver for the ICS PCI-WDT500/501 watchdog cards");
MODULE_LICENSE("GPL");
