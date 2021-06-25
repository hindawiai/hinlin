<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	SMsC 37B787 Watchकरोg Timer driver क्रम Linux 2.6.x.x
 *
 *	Based on acquirewdt.c by Alan Cox <alan@lxorguk.ukuu.org.uk>
 *	and some other existing drivers
 *
 *	The authors करो NOT admit liability nor provide warranty क्रम
 *	any of this software. This material is provided "AS-IS" in
 *	the hope that it may be useful क्रम others.
 *
 *	(C) Copyright 2003-2006  Sven Anders <anders@anduras.de>
 *
 *  History:
 *	2003 - Created version 1.0 क्रम Linux 2.4.x.
 *	2006 - Ported to Linux 2.6, added nowayout and MAGICCLOSE
 *	       features. Released version 1.1
 *
 *  Theory of operation:
 *
 *	A Watchकरोg Timer (WDT) is a hardware circuit that can
 *	reset the computer प्रणाली in हाल of a software fault.
 *	You probably knew that alपढ़ोy.
 *
 *	Usually a userspace daemon will notअगरy the kernel WDT driver
 *	via the /dev/watchकरोg special device file that userspace is
 *	still alive, at regular पूर्णांकervals.  When such a notअगरication
 *	occurs, the driver will usually tell the hardware watchकरोg
 *	that everything is in order, and that the watchकरोg should रुको
 *	क्रम yet another little जबतक to reset the प्रणाली.
 *	If userspace fails (RAM error, kernel bug, whatever), the
 *	notअगरications cease to occur, and the hardware watchकरोg will
 *	reset the प्रणाली (causing a reboot) after the समयout occurs.
 *
 * Create device with:
 *  mknod /dev/watchकरोg c 10 130
 *
 * For an example userspace keep-alive daemon, see:
 *   Documentation/watchकरोg/wdt.rst
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


/* enable support क्रम minutes as units? */
/* (करोes not always work correctly, so disabled by शेष!) */
#घोषणा SMSC_SUPPORT_MINUTES
#अघोषित SMSC_SUPPORT_MINUTES

#घोषणा MAX_TIMEOUT     255

#घोषणा UNIT_SECOND     0
#घोषणा UNIT_MINUTE     1

#घोषणा VERSION		"1.1"

#घोषणा IOPORT		0x3F0
#घोषणा IOPORT_SIZE     2
#घोषणा IODEV_NO	8

अटल पूर्णांक unit = UNIT_SECOND;	/* समयr's unit */
अटल पूर्णांक समयout = 60;	/* समयout value: शेष is 60 "units" */
अटल अचिन्हित दीर्घ समयr_enabled;   /* is the समयr enabled? */

अटल अक्षर expect_बंद;       /* is the बंद expected? */

अटल DEFINE_SPINLOCK(io_lock);/* to guard the watchकरोg from io races */

अटल bool nowayout = WATCHDOG_NOWAYOUT;

/* -- Low level function ----------------------------------------*/

/* unlock the IO chip */

अटल अंतरभूत व्योम खोलो_io_config(व्योम)
अणु
	outb(0x55, IOPORT);
	mdelay(1);
	outb(0x55, IOPORT);
पूर्ण

/* lock the IO chip */
अटल अंतरभूत व्योम बंद_io_config(व्योम)
अणु
	outb(0xAA, IOPORT);
पूर्ण

/* select the IO device */
अटल अंतरभूत व्योम select_io_device(अचिन्हित अक्षर devno)
अणु
	outb(0x07, IOPORT);
	outb(devno, IOPORT+1);
पूर्ण

/* ग_लिखो to the control रेजिस्टर */
अटल अंतरभूत व्योम ग_लिखो_io_cr(अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	outb(reg, IOPORT);
	outb(data, IOPORT+1);
पूर्ण

/* पढ़ो from the control रेजिस्टर */
अटल अंतरभूत अक्षर पढ़ो_io_cr(अचिन्हित अक्षर reg)
अणु
	outb(reg, IOPORT);
	वापस inb(IOPORT+1);
पूर्ण

/* -- Medium level functions ------------------------------------*/

अटल अंतरभूत व्योम gpio_bit12(अचिन्हित अक्षर reg)
अणु
	/* -- General Purpose I/O Bit 1.2 --
	 * Bit 0,   In/Out: 0 = Output, 1 = Input
	 * Bit 1,   Polarity: 0 = No Invert, 1 = Invert
	 * Bit 2,   Group Enable Intr.: 0 = Disable, 1 = Enable
	 * Bit 3/4, Function select: 00 = GPI/O, 01 = WDT, 10 = P17,
	 *                           11 = Either Edge Triggered Intr. 2
	 * Bit 5/6  (Reserved)
	 * Bit 7,   Output Type: 0 = Push Pull Bit, 1 = Open Drain
	 */
	ग_लिखो_io_cr(0xE2, reg);
पूर्ण

अटल अंतरभूत व्योम gpio_bit13(अचिन्हित अक्षर reg)
अणु
	/* -- General Purpose I/O Bit 1.3 --
	 * Bit 0,  In/Out: 0 = Output, 1 = Input
	 * Bit 1,  Polarity: 0 = No Invert, 1 = Invert
	 * Bit 2,  Group Enable Intr.: 0 = Disable, 1 = Enable
	 * Bit 3,  Function select: 0 = GPI/O, 1 = LED
	 * Bit 4-6 (Reserved)
	 * Bit 7,  Output Type: 0 = Push Pull Bit, 1 = Open Drain
	 */
	ग_लिखो_io_cr(0xE3, reg);
पूर्ण

अटल अंतरभूत व्योम wdt_समयr_units(अचिन्हित अक्षर new_units)
अणु
	/* -- Watchकरोg समयr units --
	 * Bit 0-6 (Reserved)
	 * Bit 7,  WDT Time-out Value Units Select
	 *         (0 = Minutes, 1 = Seconds)
	 */
	ग_लिखो_io_cr(0xF1, new_units);
पूर्ण

अटल अंतरभूत व्योम wdt_समयout_value(अचिन्हित अक्षर new_समयout)
अणु
	/* -- Watchकरोg Timer Time-out Value --
	 * Bit 0-7 Binary coded units (0=Disabled, 1..255)
	 */
	ग_लिखो_io_cr(0xF2, new_समयout);
पूर्ण

अटल अंतरभूत व्योम wdt_समयr_conf(अचिन्हित अक्षर conf)
अणु
	/* -- Watchकरोg समयr configuration --
	 * Bit 0   Joystick enable: 0* = No Reset, 1 = Reset WDT upon
	 *							Gameport I/O
	 * Bit 1   Keyboard enable: 0* = No Reset, 1 = Reset WDT upon KBD Intr.
	 * Bit 2   Mouse enable: 0* = No Reset, 1 = Reset WDT upon Mouse Intr
	 * Bit 3   Reset the समयr
	 *         (Wrong in SMsC करोcumentation? Given as: PowerLED Timout
	 *							Enabled)
	 * Bit 4-7 WDT Interrupt Mapping: (0000* = Disabled,
	 *            0001=IRQ1, 0010=(Invalid), 0011=IRQ3 to 1111=IRQ15)
	 */
	ग_लिखो_io_cr(0xF3, conf);
पूर्ण

अटल अंतरभूत व्योम wdt_समयr_ctrl(अचिन्हित अक्षर reg)
अणु
	/* -- Watchकरोg समयr control --
	 * Bit 0   Status Bit: 0 = Timer counting, 1 = Timeout occurred
	 * Bit 1   Power LED Toggle: 0 = Disable Toggle, 1 = Toggle at 1 Hz
	 * Bit 2   Force Timeout: 1 = Forces WD समयout event (self-cleaning)
	 * Bit 3   P20 Force Timeout enabled:
	 *          0 = P20 activity करोes not generate the WD समयout event
	 *          1 = P20 Allows rising edge of P20, from the keyboard
	 *              controller, to क्रमce the WD समयout event.
	 * Bit 4   (Reserved)
	 * -- Soft घातer management --
	 * Bit 5   Stop Counter: 1 = Stop software घातer करोwn counter
	 *            set via रेजिस्टर 0xB8, (self-cleaning)
	 *            (Upon पढ़ो: 0 = Counter running, 1 = Counter stopped)
	 * Bit 6   Restart Counter: 1 = Restart software घातer करोwn counter
	 *            set via रेजिस्टर 0xB8, (self-cleaning)
	 * Bit 7   SPOFF: 1 = Force software घातer करोwn (self-cleaning)
	 */
	ग_लिखो_io_cr(0xF4, reg);
पूर्ण

/* -- Higher level functions ------------------------------------*/

/* initialize watchकरोg */

अटल व्योम wb_smsc_wdt_initialize(व्योम)
अणु
	अचिन्हित अक्षर old;

	spin_lock(&io_lock);
	खोलो_io_config();
	select_io_device(IODEV_NO);

	/* enable the watchकरोg */
	gpio_bit13(0x08);  /* Select pin 80 = LED not GPIO */
	gpio_bit12(0x0A);  /* Set pin 79 = WDT not
			      GPIO/Output/Polarity=Invert */
	/* disable the समयout */
	wdt_समयout_value(0);

	/* reset control रेजिस्टर */
	wdt_समयr_ctrl(0x00);

	/* reset configuration रेजिस्टर */
	wdt_समयr_conf(0x00);

	/* पढ़ो old (समयr units) रेजिस्टर */
	old = पढ़ो_io_cr(0xF1) & 0x7F;
	अगर (unit == UNIT_SECOND)
		old |= 0x80;	/* set to seconds */

	/* set the watchकरोg समयr units */
	wdt_समयr_units(old);

	बंद_io_config();
	spin_unlock(&io_lock);
पूर्ण

/* shutकरोwn the watchकरोg */

अटल व्योम wb_smsc_wdt_shutकरोwn(व्योम)
अणु
	spin_lock(&io_lock);
	खोलो_io_config();
	select_io_device(IODEV_NO);

	/* disable the watchकरोg */
	gpio_bit13(0x09);
	gpio_bit12(0x09);

	/* reset watchकरोg config रेजिस्टर */
	wdt_समयr_conf(0x00);

	/* reset watchकरोg control रेजिस्टर */
	wdt_समयr_ctrl(0x00);

	/* disable समयout */
	wdt_समयout_value(0x00);

	बंद_io_config();
	spin_unlock(&io_lock);
पूर्ण

/* set समयout => enable watchकरोg */

अटल व्योम wb_smsc_wdt_set_समयout(अचिन्हित अक्षर new_समयout)
अणु
	spin_lock(&io_lock);
	खोलो_io_config();
	select_io_device(IODEV_NO);

	/* set Power LED to blink, अगर we enable the समयout */
	wdt_समयr_ctrl((new_समयout == 0) ? 0x00 : 0x02);

	/* set समयout value */
	wdt_समयout_value(new_समयout);

	बंद_io_config();
	spin_unlock(&io_lock);
पूर्ण

/* get समयout */

अटल अचिन्हित अक्षर wb_smsc_wdt_get_समयout(व्योम)
अणु
	अचिन्हित अक्षर set_समयout;

	spin_lock(&io_lock);
	खोलो_io_config();
	select_io_device(IODEV_NO);
	set_समयout = पढ़ो_io_cr(0xF2);
	बंद_io_config();
	spin_unlock(&io_lock);

	वापस set_समयout;
पूर्ण

/* disable watchकरोg */

अटल व्योम wb_smsc_wdt_disable(व्योम)
अणु
	/* set the समयout to 0 to disable the watchकरोg */
	wb_smsc_wdt_set_समयout(0);
पूर्ण

/* enable watchकरोg by setting the current समयout */

अटल व्योम wb_smsc_wdt_enable(व्योम)
अणु
	/* set the current समयout... */
	wb_smsc_wdt_set_समयout(समयout);
पूर्ण

/* reset the समयr */

अटल व्योम wb_smsc_wdt_reset_समयr(व्योम)
अणु
	spin_lock(&io_lock);
	खोलो_io_config();
	select_io_device(IODEV_NO);

	/* reset the समयr */
	wdt_समयout_value(समयout);
	wdt_समयr_conf(0x08);

	बंद_io_config();
	spin_unlock(&io_lock);
पूर्ण

/* वापस, अगर the watchकरोg is enabled (समयout is set...) */

अटल पूर्णांक wb_smsc_wdt_status(व्योम)
अणु
	वापस (wb_smsc_wdt_get_समयout() == 0) ? 0 : WDIOF_KEEPALIVEPING;
पूर्ण


/* -- File operations -------------------------------------------*/

/* खोलो => enable watchकरोg and set initial समयout */

अटल पूर्णांक wb_smsc_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* /dev/watchकरोg can only be खोलोed once */

	अगर (test_and_set_bit(0, &समयr_enabled))
		वापस -EBUSY;

	अगर (nowayout)
		__module_get(THIS_MODULE);

	/* Reload and activate समयr */
	wb_smsc_wdt_enable();

	pr_info("Watchdog enabled. Timeout set to %d %s\n",
		समयout, (unit == UNIT_SECOND) ? "second(s)" : "minute(s)");

	वापस stream_खोलो(inode, file);
पूर्ण

/* बंद => shut off the समयr */

अटल पूर्णांक wb_smsc_wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Shut off the समयr. */

	अगर (expect_बंद == 42) अणु
		wb_smsc_wdt_disable();
		pr_info("Watchdog disabled, sleeping again...\n");
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		wb_smsc_wdt_reset_समयr();
	पूर्ण

	clear_bit(0, &समयr_enabled);
	expect_बंद = 0;
	वापस 0;
पूर्ण

/* ग_लिखो => update the समयr to keep the machine alive */

अटल sमाप_प्रकार wb_smsc_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
				 माप_प्रकार len, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* reset expect flag */
			expect_बंद = 0;

			/* scan to see whether or not we got the
			   magic अक्षरacter */
			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;
				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण

		/* someone wrote to us, we should reload the समयr */
		wb_smsc_wdt_reset_समयr();
	पूर्ण
	वापस len;
पूर्ण

/* ioctl => control पूर्णांकerface */

अटल दीर्घ wb_smsc_wdt_ioctl(काष्ठा file *file,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_समयout;

	जोड़ अणु
		काष्ठा watchकरोg_info __user *ident;
		पूर्णांक __user *i;
	पूर्ण uarg;

	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_KEEPALIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCLOSE,
		.firmware_version =	0,
		.identity =		"SMsC 37B787 Watchdog",
	पूर्ण;

	uarg.i = (पूर्णांक __user *)arg;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(uarg.ident, &ident, माप(ident))
								? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
		वापस put_user(wb_smsc_wdt_status(), uarg.i);
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, uarg.i);
	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक options, retval = -EINVAL;

		अगर (get_user(options, uarg.i))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD) अणु
			wb_smsc_wdt_disable();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			wb_smsc_wdt_enable();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		wb_smsc_wdt_reset_समयr();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, uarg.i))
			वापस -EFAULT;
		/* the API states this is given in secs */
		अगर (unit == UNIT_MINUTE)
			new_समयout /= 60;
		अगर (new_समयout < 0 || new_समयout > MAX_TIMEOUT)
			वापस -EINVAL;
		समयout = new_समयout;
		wb_smsc_wdt_set_समयout(समयout);
		fallthrough;	/* and वापस the new समयout */
	हाल WDIOC_GETTIMEOUT:
		new_समयout = समयout;
		अगर (unit == UNIT_MINUTE)
			new_समयout *= 60;
		वापस put_user(new_समयout, uarg.i);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/* -- Notअगरier funtions -----------------------------------------*/

अटल पूर्णांक wb_smsc_wdt_notअगरy_sys(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT) अणु
		/* set समयout to 0, to aव्योम possible race-condition */
		समयout = 0;
		wb_smsc_wdt_disable();
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/* -- Module's काष्ठाures ---------------------------------------*/

अटल स्थिर काष्ठा file_operations wb_smsc_wdt_fops = अणु
	.owner	  = THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= wb_smsc_wdt_ग_लिखो,
	.unlocked_ioctl	= wb_smsc_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= wb_smsc_wdt_खोलो,
	.release	= wb_smsc_wdt_release,
पूर्ण;

अटल काष्ठा notअगरier_block wb_smsc_wdt_notअगरier = अणु
	.notअगरier_call  = wb_smsc_wdt_notअगरy_sys,
पूर्ण;

अटल काष्ठा miscdevice wb_smsc_wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &wb_smsc_wdt_fops,
पूर्ण;

/* -- Module init functions -------------------------------------*/

/* module's "constructor" */

अटल पूर्णांक __init wb_smsc_wdt_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("SMsC 37B787 watchdog component driver "
		VERSION " initialising...\n");

	अगर (!request_region(IOPORT, IOPORT_SIZE, "SMsC 37B787 watchdog")) अणु
		pr_err("Unable to register IO port %#x\n", IOPORT);
		ret = -EBUSY;
		जाओ out_pnp;
	पूर्ण

	/* set new maximum, अगर it's too big */
	अगर (समयout > MAX_TIMEOUT)
		समयout = MAX_TIMEOUT;

	/* init the watchकरोg समयr */
	wb_smsc_wdt_initialize();

	ret = रेजिस्टर_reboot_notअगरier(&wb_smsc_wdt_notअगरier);
	अगर (ret) अणु
		pr_err("Unable to register reboot notifier err = %d\n", ret);
		जाओ out_io;
	पूर्ण

	ret = misc_रेजिस्टर(&wb_smsc_wdt_miscdev);
	अगर (ret) अणु
		pr_err("Unable to register miscdev on minor %d\n",
		       WATCHDOG_MINOR);
		जाओ out_rbt;
	पूर्ण

	/* output info */
	pr_info("Timeout set to %d %s\n",
		समयout, (unit == UNIT_SECOND) ? "second(s)" : "minute(s)");
	pr_info("Watchdog initialized and sleeping (nowayout=%d)...\n",
		nowayout);
out_clean:
	वापस ret;

out_rbt:
	unरेजिस्टर_reboot_notअगरier(&wb_smsc_wdt_notअगरier);

out_io:
	release_region(IOPORT, IOPORT_SIZE);

out_pnp:
	जाओ out_clean;
पूर्ण

/* module's "destructor" */

अटल व्योम __निकास wb_smsc_wdt_निकास(व्योम)
अणु
	/* Stop the समयr beक्रमe we leave */
	अगर (!nowayout) अणु
		wb_smsc_wdt_shutकरोwn();
		pr_info("Watchdog disabled\n");
	पूर्ण

	misc_deरेजिस्टर(&wb_smsc_wdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wb_smsc_wdt_notअगरier);
	release_region(IOPORT, IOPORT_SIZE);

	pr_info("SMsC 37B787 watchdog component driver removed\n");
पूर्ण

module_init(wb_smsc_wdt_init);
module_निकास(wb_smsc_wdt_निकास);

MODULE_AUTHOR("Sven Anders <anders@anduras.de>");
MODULE_DESCRIPTION("Driver for SMsC 37B787 watchdog component (Version "
								VERSION ")");
MODULE_LICENSE("GPL");

#अगर_घोषित SMSC_SUPPORT_MINUTES
module_param(unit, पूर्णांक, 0);
MODULE_PARM_DESC(unit,
		"set unit to use, 0=seconds or 1=minutes, default is 0");
#पूर्ण_अगर

module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "range is 1-255 units, default is 60");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
