<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	National Semiconductor PC87307/PC97307 (ala SC1200) WDT driver
 *	(c) Copyright 2002 Zwane Mwaikambo <zwane@commfireservices.com>,
 *			All Rights Reserved.
 *	Based on wdt.c and wdt977.c by Alan Cox and Woody Suwalski respectively.
 *
 *	The author(s) of this software shall not be held liable क्रम damages
 *	of any nature resulting due to the use of this software. This
 *	software is provided AS-IS with no warranties.
 *
 *	Changelog:
 *	20020220 Zwane Mwaikambo	Code based on datasheet, no hardware.
 *	20020221 Zwane Mwaikambo	Cleanups as suggested by Jeff Garzik
 *					and Alan Cox.
 *	20020222 Zwane Mwaikambo	Added probing.
 *	20020225 Zwane Mwaikambo	Added ISAPNP support.
 *	20020412 Rob Radez		Broke out start/stop functions
 *		 <rob@osinvestor.com>	Return proper status instead of
 *					temperature warning
 *					Add WDIOC_GETBOOTSTATUS and
 *					WDIOC_SETOPTIONS ioctls
 *					Fix CONFIG_WATCHDOG_NOWAYOUT
 *	20020530 Joel Becker		Add Matt Domsch's nowayout module
 *					option
 *	20030116 Adam Belay		Updated to the latest pnp code
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/pnp.h>
#समावेश <linux/fs.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#घोषणा SC1200_MODULE_VER	"build 20020303"
#घोषणा SC1200_MODULE_NAME	"sc1200wdt"

#घोषणा	MAX_TIMEOUT	255	/* 255 minutes */
#घोषणा PMIR		(io)	/* Power Management Index Register */
#घोषणा PMDR		(io+1)	/* Power Management Data Register */

/* Data Register indexes */
#घोषणा FER1		0x00	/* Function enable रेजिस्टर 1 */
#घोषणा FER2		0x01	/* Function enable रेजिस्टर 2 */
#घोषणा PMC1		0x02	/* Power Management Ctrl 1 */
#घोषणा PMC2		0x03	/* Power Management Ctrl 2 */
#घोषणा PMC3		0x04	/* Power Management Ctrl 3 */
#घोषणा WDTO		0x05	/* Watchकरोg समयout रेजिस्टर */
#घोषणा	WDCF		0x06	/* Watchकरोg config रेजिस्टर */
#घोषणा WDST		0x07	/* Watchकरोg status रेजिस्टर */

/* WDCF bitfields - which devices निश्चित WDO */
#घोषणा KBC_IRQ		0x01	/* Keyboard Controller */
#घोषणा MSE_IRQ		0x02	/* Mouse */
#घोषणा UART1_IRQ	0x03	/* Serial0 */
#घोषणा UART2_IRQ	0x04	/* Serial1 */
/* 5 -7 are reserved */

अटल पूर्णांक समयout = 1;
अटल पूर्णांक io = -1;
अटल पूर्णांक io_len = 2;		/* क्रम non plug and play */
अटल अचिन्हित दीर्घ खोलो_flag;
अटल अक्षर expect_बंद;
अटल DEFINE_SPINLOCK(sc1200wdt_lock);	/* io port access serialisation */

#अगर defined CONFIG_PNP
अटल पूर्णांक isapnp = 1;
अटल काष्ठा pnp_dev *wdt_dev;

module_param(isapnp, पूर्णांक, 0);
MODULE_PARM_DESC(isapnp,
	"When set to 0 driver ISA PnP support will be disabled");
#पूर्ण_अगर

module_param_hw(io, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(io, "io port");
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "range is 0-255 minutes, default is 1");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");



/* Read from Data Register */
अटल अंतरभूत व्योम __sc1200wdt_पढ़ो_data(अचिन्हित अक्षर index,
						अचिन्हित अक्षर *data)
अणु
	outb_p(index, PMIR);
	*data = inb(PMDR);
पूर्ण

अटल व्योम sc1200wdt_पढ़ो_data(अचिन्हित अक्षर index, अचिन्हित अक्षर *data)
अणु
	spin_lock(&sc1200wdt_lock);
	__sc1200wdt_पढ़ो_data(index, data);
	spin_unlock(&sc1200wdt_lock);
पूर्ण

/* Write to Data Register */
अटल अंतरभूत व्योम __sc1200wdt_ग_लिखो_data(अचिन्हित अक्षर index,
						अचिन्हित अक्षर data)
अणु
	outb_p(index, PMIR);
	outb(data, PMDR);
पूर्ण

अटल अंतरभूत व्योम sc1200wdt_ग_लिखो_data(अचिन्हित अक्षर index,
						अचिन्हित अक्षर data)
अणु
	spin_lock(&sc1200wdt_lock);
	__sc1200wdt_ग_लिखो_data(index, data);
	spin_unlock(&sc1200wdt_lock);
पूर्ण


अटल व्योम sc1200wdt_start(व्योम)
अणु
	अचिन्हित अक्षर reg;
	spin_lock(&sc1200wdt_lock);

	__sc1200wdt_पढ़ो_data(WDCF, &reg);
	/* निश्चित WDO when any of the following पूर्णांकerrupts are triggered too */
	reg |= (KBC_IRQ | MSE_IRQ | UART1_IRQ | UART2_IRQ);
	__sc1200wdt_ग_लिखो_data(WDCF, reg);
	/* set the समयout and get the ball rolling */
	__sc1200wdt_ग_लिखो_data(WDTO, समयout);

	spin_unlock(&sc1200wdt_lock);
पूर्ण

अटल व्योम sc1200wdt_stop(व्योम)
अणु
	sc1200wdt_ग_लिखो_data(WDTO, 0);
पूर्ण

/* This वापसs the status of the WDO संकेत, inactive high. */
अटल अंतरभूत पूर्णांक sc1200wdt_status(व्योम)
अणु
	अचिन्हित अक्षर ret;

	sc1200wdt_पढ़ो_data(WDST, &ret);
	/* If the bit is inactive, the watchकरोg is enabled, so वापस
	 * KEEPALIVEPING which is a bit of a kludge because there's nothing
	 * अन्यथा क्रम enabled/disabled status
	 */
	वापस (ret & 0x01) ? 0 : WDIOF_KEEPALIVEPING;
पूर्ण

अटल पूर्णांक sc1200wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* allow one at a समय */
	अगर (test_and_set_bit(0, &खोलो_flag))
		वापस -EBUSY;

	अगर (समयout > MAX_TIMEOUT)
		समयout = MAX_TIMEOUT;

	sc1200wdt_start();
	pr_info("Watchdog enabled, timeout = %d min(s)", समयout);

	वापस stream_खोलो(inode, file);
पूर्ण


अटल दीर्घ sc1200wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_समयout;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT |
							WDIOF_MAGICCLOSE,
		.firmware_version = 0,
		.identity = "PC87307/PC97307",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (copy_to_user(argp, &ident, माप(ident)))
			वापस -EFAULT;
		वापस 0;

	हाल WDIOC_GETSTATUS:
		वापस put_user(sc1200wdt_status(), p);

	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);

	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक options, retval = -EINVAL;

		अगर (get_user(options, p))
			वापस -EFAULT;

		अगर (options & WDIOS_DISABLECARD) अणु
			sc1200wdt_stop();
			retval = 0;
		पूर्ण

		अगर (options & WDIOS_ENABLECARD) अणु
			sc1200wdt_start();
			retval = 0;
		पूर्ण

		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		sc1200wdt_ग_लिखो_data(WDTO, समयout);
		वापस 0;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_समयout, p))
			वापस -EFAULT;
		/* the API states this is given in secs */
		new_समयout /= 60;
		अगर (new_समयout < 0 || new_समयout > MAX_TIMEOUT)
			वापस -EINVAL;
		समयout = new_समयout;
		sc1200wdt_ग_लिखो_data(WDTO, समयout);
		fallthrough;	/* and वापस the new समयout */

	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout * 60, p);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण


अटल पूर्णांक sc1200wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (expect_बंद == 42) अणु
		sc1200wdt_stop();
		pr_info("Watchdog disabled\n");
	पूर्ण अन्यथा अणु
		sc1200wdt_ग_लिखो_data(WDTO, समयout);
		pr_crit("Unexpected close!, timeout = %d min(s)\n", समयout);
	पूर्ण
	clear_bit(0, &खोलो_flag);
	expect_बंद = 0;

	वापस 0;
पूर्ण


अटल sमाप_प्रकार sc1200wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
						माप_प्रकार len, loff_t *ppos)
अणु
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			expect_बंद = 0;

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;

				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण

		sc1200wdt_ग_लिखो_data(WDTO, समयout);
		वापस len;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक sc1200wdt_notअगरy_sys(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		sc1200wdt_stop();

	वापस NOTIFY_DONE;
पूर्ण


अटल काष्ठा notअगरier_block sc1200wdt_notअगरier = अणु
	.notअगरier_call =	sc1200wdt_notअगरy_sys,
पूर्ण;

अटल स्थिर काष्ठा file_operations sc1200wdt_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.ग_लिखो		= sc1200wdt_ग_लिखो,
	.unlocked_ioctl = sc1200wdt_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= sc1200wdt_खोलो,
	.release	= sc1200wdt_release,
पूर्ण;

अटल काष्ठा miscdevice sc1200wdt_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &sc1200wdt_fops,
पूर्ण;


अटल पूर्णांक __init sc1200wdt_probe(व्योम)
अणु
	/* The probe works by पढ़ोing the PMC3 रेजिस्टर's शेष value of 0x0e
	 * there is one caveat, अगर the device disables the parallel port or any
	 * of the UARTs we won't be able to detect it.
	 * NB. This could be करोne with accuracy by पढ़ोing the SID रेजिस्टरs,
	 * but we करोn't have access to those io regions.
	 */

	अचिन्हित अक्षर reg;

	sc1200wdt_पढ़ो_data(PMC3, &reg);
	reg &= 0x0f;		/* we करोn't want the UART busy bits */
	वापस (reg == 0x0e) ? 0 : -ENODEV;
पूर्ण


#अगर defined CONFIG_PNP

अटल स्थिर काष्ठा pnp_device_id scl200wdt_pnp_devices[] = अणु
	/* National Semiconductor PC87307/PC97307 watchकरोg component */
	अणु.id = "NSC0800", .driver_data = 0पूर्ण,
	अणु.id = ""पूर्ण,
पूर्ण;

अटल पूर्णांक scl200wdt_pnp_probe(काष्ठा pnp_dev *dev,
					स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	/* this driver only supports one card at a समय */
	अगर (wdt_dev || !isapnp)
		वापस -EBUSY;

	wdt_dev = dev;
	io = pnp_port_start(wdt_dev, 0);
	io_len = pnp_port_len(wdt_dev, 0);

	अगर (!request_region(io, io_len, SC1200_MODULE_NAME)) अणु
		pr_err("Unable to register IO port %#x\n", io);
		वापस -EBUSY;
	पूर्ण

	pr_info("PnP device found at io port %#x/%d\n", io, io_len);
	वापस 0;
पूर्ण

अटल व्योम scl200wdt_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	अगर (wdt_dev) अणु
		release_region(io, io_len);
		wdt_dev = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा pnp_driver scl200wdt_pnp_driver = अणु
	.name		= "scl200wdt",
	.id_table	= scl200wdt_pnp_devices,
	.probe		= scl200wdt_pnp_probe,
	.हटाओ		= scl200wdt_pnp_हटाओ,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PNP */


अटल पूर्णांक __init sc1200wdt_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("%s\n", SC1200_MODULE_VER);

#अगर defined CONFIG_PNP
	अगर (isapnp) अणु
		ret = pnp_रेजिस्टर_driver(&scl200wdt_pnp_driver);
		अगर (ret)
			जाओ out_clean;
	पूर्ण
#पूर्ण_अगर

	अगर (io == -1) अणु
		pr_err("io parameter must be specified\n");
		ret = -EINVAL;
		जाओ out_pnp;
	पूर्ण

#अगर defined CONFIG_PNP
	/* now that the user has specअगरied an IO port and we haven't detected
	 * any devices, disable pnp support */
	अगर (isapnp)
		pnp_unरेजिस्टर_driver(&scl200wdt_pnp_driver);
	isapnp = 0;
#पूर्ण_अगर

	अगर (!request_region(io, io_len, SC1200_MODULE_NAME)) अणु
		pr_err("Unable to register IO port %#x\n", io);
		ret = -EBUSY;
		जाओ out_pnp;
	पूर्ण

	ret = sc1200wdt_probe();
	अगर (ret)
		जाओ out_io;

	ret = रेजिस्टर_reboot_notअगरier(&sc1200wdt_notअगरier);
	अगर (ret) अणु
		pr_err("Unable to register reboot notifier err = %d\n", ret);
		जाओ out_io;
	पूर्ण

	ret = misc_रेजिस्टर(&sc1200wdt_miscdev);
	अगर (ret) अणु
		pr_err("Unable to register miscdev on minor %d\n",
		       WATCHDOG_MINOR);
		जाओ out_rbt;
	पूर्ण

	/* ret = 0 */

out_clean:
	वापस ret;

out_rbt:
	unरेजिस्टर_reboot_notअगरier(&sc1200wdt_notअगरier);

out_io:
	release_region(io, io_len);

out_pnp:
#अगर defined CONFIG_PNP
	अगर (isapnp)
		pnp_unरेजिस्टर_driver(&scl200wdt_pnp_driver);
#पूर्ण_अगर
	जाओ out_clean;
पूर्ण


अटल व्योम __निकास sc1200wdt_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&sc1200wdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&sc1200wdt_notअगरier);

#अगर defined CONFIG_PNP
	अगर (isapnp)
		pnp_unरेजिस्टर_driver(&scl200wdt_pnp_driver);
	अन्यथा
#पूर्ण_अगर
	release_region(io, io_len);
पूर्ण

module_init(sc1200wdt_init);
module_निकास(sc1200wdt_निकास);

MODULE_AUTHOR("Zwane Mwaikambo <zwane@commfireservices.com>");
MODULE_DESCRIPTION(
	"Driver for National Semiconductor PC87307/PC97307 watchdog component");
MODULE_LICENSE("GPL");
