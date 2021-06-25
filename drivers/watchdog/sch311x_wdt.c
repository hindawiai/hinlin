<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	sch311x_wdt.c - Driver क्रम the SCH311x Super-I/O chips
 *			पूर्णांकegrated watchकरोg.
 *
 *	(c) Copyright 2008 Wim Van Sebroeck <wim@iguana.be>.
 *
 *	Neither Wim Van Sebroeck nor Iguana vzw. admit liability nor
 *	provide warranty क्रम any of this software. This material is
 *	provided "AS-IS" and at no अक्षरge.
 */

/*
 *	Includes, defines, variables, module parameters, ...
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* Includes */
#समावेश <linux/module.h>		/* For module specअगरic items */
#समावेश <linux/moduleparam.h>		/* For new moduleparam's */
#समावेश <linux/types.h>		/* For standard types (like माप_प्रकार) */
#समावेश <linux/त्रुटिसं.स>		/* For the -ENODEV/... values */
#समावेश <linux/kernel.h>		/* For prपूर्णांकk/... */
#समावेश <linux/miscdevice.h>		/* For काष्ठा miscdevice */
#समावेश <linux/watchकरोg.h>		/* For the watchकरोg specअगरic items */
#समावेश <linux/init.h>			/* For __init/__निकास/... */
#समावेश <linux/fs.h>			/* For file operations */
#समावेश <linux/platक्रमm_device.h>	/* For platक्रमm_driver framework */
#समावेश <linux/ioport.h>		/* For io-port access */
#समावेश <linux/spinlock.h>		/* For spin_lock/spin_unlock/... */
#समावेश <linux/uaccess.h>		/* For copy_to_user/put_user/... */
#समावेश <linux/पन.स>			/* For inb/outb/... */

/* Module and version inक्रमmation */
#घोषणा DRV_NAME	"sch311x_wdt"

/* Runसमय रेजिस्टरs */
#घोषणा GP60			0x47
#घोषणा WDT_TIME_OUT		0x65
#घोषणा WDT_VAL			0x66
#घोषणा WDT_CFG			0x67
#घोषणा WDT_CTRL		0x68

/* पूर्णांकernal variables */
अटल अचिन्हित दीर्घ sch311x_wdt_is_खोलो;
अटल अक्षर sch311x_wdt_expect_बंद;
अटल काष्ठा platक्रमm_device *sch311x_wdt_pdev;

अटल पूर्णांक sch311x_ioports[] = अणु 0x2e, 0x4e, 0x162e, 0x164e, 0x00 पूर्ण;

अटल काष्ठा अणु	/* The devices निजी data */
	/* the Runसमय Register base address */
	अचिन्हित लघु runसमय_reg;
	/* The card's boot status */
	पूर्णांक boot_status;
	/* the lock क्रम io operations */
	spinlock_t io_lock;
पूर्ण sch311x_wdt_data;

/* Module load parameters */
अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

#घोषणा WATCHDOG_TIMEOUT 60		/* 60 sec शेष समयout */
अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;	/* in seconds */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in seconds. 1<= timeout <=15300, default="
		__MODULE_STRING(WATCHDOG_TIMEOUT) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
		__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Super-IO functions
 */

अटल अंतरभूत व्योम sch311x_sio_enter(पूर्णांक sio_config_port)
अणु
	outb(0x55, sio_config_port);
पूर्ण

अटल अंतरभूत व्योम sch311x_sio_निकास(पूर्णांक sio_config_port)
अणु
	outb(0xaa, sio_config_port);
पूर्ण

अटल अंतरभूत पूर्णांक sch311x_sio_inb(पूर्णांक sio_config_port, पूर्णांक reg)
अणु
	outb(reg, sio_config_port);
	वापस inb(sio_config_port + 1);
पूर्ण

अटल अंतरभूत व्योम sch311x_sio_outb(पूर्णांक sio_config_port, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, sio_config_port);
	outb(val, sio_config_port + 1);
पूर्ण

/*
 *	Watchकरोg Operations
 */

अटल व्योम sch311x_wdt_set_समयout(पूर्णांक t)
अणु
	अचिन्हित अक्षर समयout_unit = 0x80;

	/* When new समयout is bigger then 255 seconds, we will use minutes */
	अगर (t > 255) अणु
		समयout_unit = 0;
		t /= 60;
	पूर्ण

	/* -- Watchकरोg Timeout --
	 * Bit 0-6 (Reserved)
	 * Bit 7   WDT Time-out Value Units Select
	 *         (0 = Minutes, 1 = Seconds)
	 */
	outb(समयout_unit, sch311x_wdt_data.runसमय_reg + WDT_TIME_OUT);

	/* -- Watchकरोg Timer Time-out Value --
	 * Bit 0-7 Binary coded units (0=Disabled, 1..255)
	 */
	outb(t, sch311x_wdt_data.runसमय_reg + WDT_VAL);
पूर्ण

अटल व्योम sch311x_wdt_start(व्योम)
अणु
	अचिन्हित अक्षर t;

	spin_lock(&sch311x_wdt_data.io_lock);

	/* set watchकरोg's समयout */
	sch311x_wdt_set_समयout(समयout);
	/* enable the watchकरोg */
	/* -- General Purpose I/O Bit 6.0 --
	 * Bit 0,   In/Out: 0 = Output, 1 = Input
	 * Bit 1,   Polarity: 0 = No Invert, 1 = Invert
	 * Bit 2-3, Function select: 00 = GPI/O, 01 = LED1, 11 = WDT,
	 *                           10 = Either Edge Triggered Intr.4
	 * Bit 4-6  (Reserved)
	 * Bit 7,   Output Type: 0 = Push Pull Bit, 1 = Open Drain
	 */
	t = inb(sch311x_wdt_data.runसमय_reg + GP60);
	outb((t & ~0x0d) | 0x0c, sch311x_wdt_data.runसमय_reg + GP60);

	spin_unlock(&sch311x_wdt_data.io_lock);

पूर्ण

अटल व्योम sch311x_wdt_stop(व्योम)
अणु
	अचिन्हित अक्षर t;

	spin_lock(&sch311x_wdt_data.io_lock);

	/* stop the watchकरोg */
	t = inb(sch311x_wdt_data.runसमय_reg + GP60);
	outb((t & ~0x0d) | 0x01, sch311x_wdt_data.runसमय_reg + GP60);
	/* disable समयout by setting it to 0 */
	sch311x_wdt_set_समयout(0);

	spin_unlock(&sch311x_wdt_data.io_lock);
पूर्ण

अटल व्योम sch311x_wdt_keepalive(व्योम)
अणु
	spin_lock(&sch311x_wdt_data.io_lock);
	sch311x_wdt_set_समयout(समयout);
	spin_unlock(&sch311x_wdt_data.io_lock);
पूर्ण

अटल पूर्णांक sch311x_wdt_set_heartbeat(पूर्णांक t)
अणु
	अगर (t < 1 || t > (255*60))
		वापस -EINVAL;

	/* When new समयout is bigger then 255 seconds,
	 * we will round up to minutes (with a max of 255) */
	अगर (t > 255)
		t = (((t - 1) / 60) + 1) * 60;

	समयout = t;
	वापस 0;
पूर्ण

अटल व्योम sch311x_wdt_get_status(पूर्णांक *status)
अणु
	अचिन्हित अक्षर new_status;

	*status = 0;

	spin_lock(&sch311x_wdt_data.io_lock);

	/* -- Watchकरोg समयr control --
	 * Bit 0   Status Bit: 0 = Timer counting, 1 = Timeout occurred
	 * Bit 1   Reserved
	 * Bit 2   Force Timeout: 1 = Forces WD समयout event (self-cleaning)
	 * Bit 3   P20 Force Timeout enabled:
	 *          0 = P20 activity करोes not generate the WD समयout event
	 *          1 = P20 Allows rising edge of P20, from the keyboard
	 *              controller, to क्रमce the WD समयout event.
	 * Bit 4-7 Reserved
	 */
	new_status = inb(sch311x_wdt_data.runसमय_reg + WDT_CTRL);
	अगर (new_status & 0x01)
		*status |= WDIOF_CARDRESET;

	spin_unlock(&sch311x_wdt_data.io_lock);
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल sमाप_प्रकार sch311x_wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			sch311x_wdt_expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					sch311x_wdt_expect_बंद = 42;
			पूर्ण
		पूर्ण
		sch311x_wdt_keepalive();
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ sch311x_wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक status;
	पूर्णांक new_समयout;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options		= WDIOF_KEEPALIVEPING |
					  WDIOF_SETTIMEOUT |
					  WDIOF_MAGICCLOSE,
		.firmware_version	= 1,
		.identity		= DRV_NAME,
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
	अणु
		sch311x_wdt_get_status(&status);
		वापस put_user(status, p);
	पूर्ण
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(sch311x_wdt_data.boot_status, p);

	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक options, retval = -EINVAL;

		अगर (get_user(options, p))
			वापस -EFAULT;
		अगर (options & WDIOS_DISABLECARD) अणु
			sch311x_wdt_stop();
			retval = 0;
		पूर्ण
		अगर (options & WDIOS_ENABLECARD) अणु
			sch311x_wdt_start();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		sch311x_wdt_keepalive();
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, p))
			वापस -EFAULT;
		अगर (sch311x_wdt_set_heartbeat(new_समयout))
			वापस -EINVAL;
		sch311x_wdt_keepalive();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sch311x_wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (test_and_set_bit(0, &sch311x_wdt_is_खोलो))
		वापस -EBUSY;
	/*
	 *	Activate
	 */
	sch311x_wdt_start();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक sch311x_wdt_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (sch311x_wdt_expect_बंद == 42) अणु
		sch311x_wdt_stop();
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		sch311x_wdt_keepalive();
	पूर्ण
	clear_bit(0, &sch311x_wdt_is_खोलो);
	sch311x_wdt_expect_बंद = 0;
	वापस 0;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations sch311x_wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= sch311x_wdt_ग_लिखो,
	.unlocked_ioctl	= sch311x_wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= sch311x_wdt_खोलो,
	.release	= sch311x_wdt_बंद,
पूर्ण;

अटल काष्ठा miscdevice sch311x_wdt_miscdev = अणु
	.minor	= WATCHDOG_MINOR,
	.name	= "watchdog",
	.fops	= &sch311x_wdt_fops,
पूर्ण;

/*
 *	Init & निकास routines
 */

अटल पूर्णांक sch311x_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	spin_lock_init(&sch311x_wdt_data.io_lock);

	अगर (!request_region(sch311x_wdt_data.runसमय_reg + GP60, 1, DRV_NAME)) अणु
		dev_err(dev, "Failed to request region 0x%04x-0x%04x.\n",
			sch311x_wdt_data.runसमय_reg + GP60,
			sch311x_wdt_data.runसमय_reg + GP60);
		err = -EBUSY;
		जाओ निकास;
	पूर्ण

	अगर (!request_region(sch311x_wdt_data.runसमय_reg + WDT_TIME_OUT, 4,
								DRV_NAME)) अणु
		dev_err(dev, "Failed to request region 0x%04x-0x%04x.\n",
			sch311x_wdt_data.runसमय_reg + WDT_TIME_OUT,
			sch311x_wdt_data.runसमय_reg + WDT_CTRL);
		err = -EBUSY;
		जाओ निकास_release_region;
	पूर्ण

	/* Make sure that the watchकरोg is not running */
	sch311x_wdt_stop();

	/* Disable keyboard and mouse पूर्णांकeraction and पूर्णांकerrupt */
	/* -- Watchकरोg समयr configuration --
	 * Bit 0   Reserved
	 * Bit 1   Keyboard enable: 0* = No Reset, 1 = Reset WDT upon KBD Intr.
	 * Bit 2   Mouse enable: 0* = No Reset, 1 = Reset WDT upon Mouse Intr
	 * Bit 3   Reserved
	 * Bit 4-7 WDT Interrupt Mapping: (0000* = Disabled,
	 *            0001=IRQ1, 0010=(Invalid), 0011=IRQ3 to 1111=IRQ15)
	 */
	outb(0, sch311x_wdt_data.runसमय_reg + WDT_CFG);

	/* Check that the heartbeat value is within it's range ;
	 * अगर not reset to the शेष */
	अगर (sch311x_wdt_set_heartbeat(समयout)) अणु
		sch311x_wdt_set_heartbeat(WATCHDOG_TIMEOUT);
		dev_info(dev, "timeout value must be 1<=x<=15300, using %d\n",
			समयout);
	पूर्ण

	/* Get status at boot */
	sch311x_wdt_get_status(&sch311x_wdt_data.boot_status);

	sch311x_wdt_miscdev.parent = dev;

	err = misc_रेजिस्टर(&sch311x_wdt_miscdev);
	अगर (err != 0) अणु
		dev_err(dev, "cannot register miscdev on minor=%d (err=%d)\n",
							WATCHDOG_MINOR, err);
		जाओ निकास_release_region2;
	पूर्ण

	dev_info(dev,
		"SMSC SCH311x WDT initialized. timeout=%d sec (nowayout=%d)\n",
		समयout, nowayout);

	वापस 0;

निकास_release_region2:
	release_region(sch311x_wdt_data.runसमय_reg + WDT_TIME_OUT, 4);
निकास_release_region:
	release_region(sch311x_wdt_data.runसमय_reg + GP60, 1);
	sch311x_wdt_data.runसमय_reg = 0;
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक sch311x_wdt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* Stop the समयr beक्रमe we leave */
	अगर (!nowayout)
		sch311x_wdt_stop();

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&sch311x_wdt_miscdev);
	release_region(sch311x_wdt_data.runसमय_reg + WDT_TIME_OUT, 4);
	release_region(sch311x_wdt_data.runसमय_reg + GP60, 1);
	sch311x_wdt_data.runसमय_reg = 0;
	वापस 0;
पूर्ण

अटल व्योम sch311x_wdt_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	/* Turn the WDT off अगर we have a soft shutकरोwn */
	sch311x_wdt_stop();
पूर्ण

अटल काष्ठा platक्रमm_driver sch311x_wdt_driver = अणु
	.probe		= sch311x_wdt_probe,
	.हटाओ		= sch311x_wdt_हटाओ,
	.shutकरोwn	= sch311x_wdt_shutकरोwn,
	.driver		= अणु
		.name = DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sch311x_detect(पूर्णांक sio_config_port, अचिन्हित लघु *addr)
अणु
	पूर्णांक err = 0, reg;
	अचिन्हित लघु base_addr;
	अचिन्हित अक्षर dev_id;

	sch311x_sio_enter(sio_config_port);

	/* Check device ID. We currently know about:
	 * SCH3112 (0x7c), SCH3114 (0x7d), and SCH3116 (0x7f). */
	reg = क्रमce_id ? क्रमce_id : sch311x_sio_inb(sio_config_port, 0x20);
	अगर (!(reg == 0x7c || reg == 0x7d || reg == 0x7f)) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण
	dev_id = reg == 0x7c ? 2 : reg == 0x7d ? 4 : 6;

	/* Select logical device A (runसमय रेजिस्टरs) */
	sch311x_sio_outb(sio_config_port, 0x07, 0x0a);

	/* Check अगर Logical Device Register is currently active */
	अगर ((sch311x_sio_inb(sio_config_port, 0x30) & 0x01) == 0)
		pr_info("Seems that LDN 0x0a is not active...\n");

	/* Get the base address of the runसमय रेजिस्टरs */
	base_addr = (sch311x_sio_inb(sio_config_port, 0x60) << 8) |
			   sch311x_sio_inb(sio_config_port, 0x61);
	अगर (!base_addr) अणु
		pr_err("Base address not set\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण
	*addr = base_addr;

	pr_info("Found an SMSC SCH311%d chip at 0x%04x\n", dev_id, base_addr);

निकास:
	sch311x_sio_निकास(sio_config_port);
	वापस err;
पूर्ण

अटल पूर्णांक __init sch311x_wdt_init(व्योम)
अणु
	पूर्णांक err, i, found = 0;
	अचिन्हित लघु addr = 0;

	क्रम (i = 0; !found && sch311x_ioports[i]; i++)
		अगर (sch311x_detect(sch311x_ioports[i], &addr) == 0)
			found++;

	अगर (!found)
		वापस -ENODEV;

	sch311x_wdt_data.runसमय_reg = addr;

	err = platक्रमm_driver_रेजिस्टर(&sch311x_wdt_driver);
	अगर (err)
		वापस err;

	sch311x_wdt_pdev = platक्रमm_device_रेजिस्टर_simple(DRV_NAME, addr,
								शून्य, 0);

	अगर (IS_ERR(sch311x_wdt_pdev)) अणु
		err = PTR_ERR(sch311x_wdt_pdev);
		जाओ unreg_platक्रमm_driver;
	पूर्ण

	वापस 0;

unreg_platक्रमm_driver:
	platक्रमm_driver_unरेजिस्टर(&sch311x_wdt_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास sch311x_wdt_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sch311x_wdt_pdev);
	platक्रमm_driver_unरेजिस्टर(&sch311x_wdt_driver);
पूर्ण

module_init(sch311x_wdt_init);
module_निकास(sch311x_wdt_निकास);

MODULE_AUTHOR("Wim Van Sebroeck <wim@iguana.be>");
MODULE_DESCRIPTION("SMSC SCH311x WatchDog Timer Driver");
MODULE_LICENSE("GPL");
