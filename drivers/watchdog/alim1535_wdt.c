<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Watchकरोg क्रम the 7101 PMU version found in the ALi M1535 chipsets
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#घोषणा WATCHDOG_NAME "ALi_M1535"
#घोषणा WATCHDOG_TIMEOUT 60	/* 60 sec शेष समयout */

/* पूर्णांकernal variables */
अटल अचिन्हित दीर्घ ali_is_खोलो;
अटल अक्षर ali_expect_release;
अटल काष्ठा pci_dev *ali_pci;
अटल u32 ali_समयout_bits;		/* stores the computed समयout */
अटल DEFINE_SPINLOCK(ali_lock);	/* Guards the hardware */

/* module parameters */
अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		"Watchdog timeout in seconds. (0 < timeout < 18000, default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	ali_start	-	start watchकरोg countकरोwn
 *
 *	Starts the समयr running providing the समयr has a counter
 *	configuration set.
 */

अटल व्योम ali_start(व्योम)
अणु
	u32 val;

	spin_lock(&ali_lock);

	pci_पढ़ो_config_dword(ali_pci, 0xCC, &val);
	val &= ~0x3F;	/* Mask count */
	val |= (1 << 25) | ali_समयout_bits;
	pci_ग_लिखो_config_dword(ali_pci, 0xCC, val);

	spin_unlock(&ali_lock);
पूर्ण

/*
 *	ali_stop	-	stop the समयr countकरोwn
 *
 *	Stop the ALi watchकरोg countकरोwn
 */

अटल व्योम ali_stop(व्योम)
अणु
	u32 val;

	spin_lock(&ali_lock);

	pci_पढ़ो_config_dword(ali_pci, 0xCC, &val);
	val &= ~0x3F;		/* Mask count to zero (disabled) */
	val &= ~(1 << 25);	/* and क्रम safety mask the reset enable */
	pci_ग_लिखो_config_dword(ali_pci, 0xCC, val);

	spin_unlock(&ali_lock);
पूर्ण

/*
 *	ali_keepalive	-	send a keepalive to the watchकरोg
 *
 *	Send a keepalive to the समयr (actually we restart the समयr).
 */

अटल व्योम ali_keepalive(व्योम)
अणु
	ali_start();
पूर्ण

/*
 *	ali_समय_रखोr	-	compute the समयr reload value
 *	@t: समय in seconds
 *
 *	Computes the समयout values needed
 */

अटल पूर्णांक ali_समय_रखोr(पूर्णांक t)
अणु
	अगर (t < 0)
		वापस -EINVAL;
	अन्यथा अगर (t < 60)
		ali_समयout_bits = t|(1 << 6);
	अन्यथा अगर (t < 3600)
		ali_समयout_bits = (t / 60)|(1 << 7);
	अन्यथा अगर (t < 18000)
		ali_समयout_bits = (t / 300)|(1 << 6)|(1 << 7);
	अन्यथा
		वापस -EINVAL;

	समयout = t;
	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

/*
 *	ali_ग_लिखो	-	ग_लिखोs to ALi watchकरोg
 *	@file: file from VFS
 *	@data: user address of data
 *	@len: length of data
 *	@ppos: poपूर्णांकer to the file offset
 *
 *	Handle a ग_लिखो to the ALi watchकरोg. Writing to the file pings
 *	the watchकरोg and resets it. Writing the magic 'V' sequence allows
 *	the next बंद to turn off the watchकरोg.
 */

अटल sमाप_प्रकार ali_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
						माप_प्रकार len, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* note: just in हाल someone wrote the
			   magic अक्षरacter five months ago... */
			ali_expect_release = 0;

			/* scan to see whether or not we got
			   the magic अक्षरacter */
			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;
				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					ali_expect_release = 42;
			पूर्ण
		पूर्ण

		/* someone wrote to us, we should reload the समयr */
		ali_start();
	पूर्ण
	वापस len;
पूर्ण

/*
 *	ali_ioctl	-	handle watchकरोg ioctls
 *	@file: VFS file poपूर्णांकer
 *	@cmd: ioctl number
 *	@arg: arguments to the ioctl
 *
 *	Handle the watchकरोg ioctls supported by the ALi driver. Really
 *	we want an extension to enable irq ack monitoring and the like
 */

अटल दीर्घ ali_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_KEEPALIVEPING |
					WDIOF_SETTIMEOUT |
					WDIOF_MAGICCLOSE,
		.firmware_version =	0,
		.identity =		"ALi M1535 WatchDog Timer",
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_SETOPTIONS:
	अणु
		पूर्णांक new_options, retval = -EINVAL;

		अगर (get_user(new_options, p))
			वापस -EFAULT;
		अगर (new_options & WDIOS_DISABLECARD) अणु
			ali_stop();
			retval = 0;
		पूर्ण
		अगर (new_options & WDIOS_ENABLECARD) अणु
			ali_start();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		ali_keepalive();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
	अणु
		पूर्णांक new_समयout;
		अगर (get_user(new_समयout, p))
			वापस -EFAULT;
		अगर (ali_समय_रखोr(new_समयout))
			वापस -EINVAL;
		ali_keepalive();
	पूर्ण
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/*
 *	ali_खोलो	-	handle खोलो of ali watchकरोg
 *	@inode: inode from VFS
 *	@file: file from VFS
 *
 *	Open the ALi watchकरोg device. Ensure only one person खोलोs it
 *	at a समय. Also start the watchकरोg running.
 */

अटल पूर्णांक ali_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* /dev/watchकरोg can only be खोलोed once */
	अगर (test_and_set_bit(0, &ali_is_खोलो))
		वापस -EBUSY;

	/* Activate */
	ali_start();
	वापस stream_खोलो(inode, file);
पूर्ण

/*
 *	ali_release	-	बंद an ALi watchकरोg
 *	@inode: inode from VFS
 *	@file: file from VFS
 *
 *	Close the ALi watchकरोg device. Actual shutकरोwn of the समयr
 *	only occurs अगर the magic sequence has been set.
 */

अटल पूर्णांक ali_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/*
	 *      Shut off the समयr.
	 */
	अगर (ali_expect_release == 42)
		ali_stop();
	अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		ali_keepalive();
	पूर्ण
	clear_bit(0, &ali_is_खोलो);
	ali_expect_release = 0;
	वापस 0;
पूर्ण

/*
 *	ali_notअगरy_sys	-	System करोwn notअगरier
 *
 *	Notअगरier क्रम प्रणाली करोwn
 */


अटल पूर्णांक ali_notअगरy_sys(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		ali_stop();		/* Turn the WDT off */
	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Data क्रम PCI driver पूर्णांकerface
 *
 *	This data only exists क्रम exporting the supported
 *	PCI ids via MODULE_DEVICE_TABLE.  We करो not actually
 *	रेजिस्टर a pci_driver, because someone अन्यथा might one day
 *	want to रेजिस्टर another driver on the same PCI id.
 */

अटल स्थिर काष्ठा pci_device_id ali_pci_tbl[] __used = अणु
	अणु PCI_VENDOR_ID_AL, 0x1533, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु PCI_VENDOR_ID_AL, 0x1535, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, ali_pci_tbl);

/*
 *	ali_find_watchकरोg	-	find a 1535 and 7101
 *
 *	Scans the PCI hardware क्रम a 1535 series bridge and matching 7101
 *	watchकरोg device. This may be overtight but it is better to be safe
 */

अटल पूर्णांक __init ali_find_watchकरोg(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	u32 wकरोg;

	/* Check क्रम a 1533/1535 series bridge */
	pdev = pci_get_device(PCI_VENDOR_ID_AL, 0x1535, शून्य);
	अगर (pdev == शून्य)
		pdev = pci_get_device(PCI_VENDOR_ID_AL, 0x1533, शून्य);
	अगर (pdev == शून्य)
		वापस -ENODEV;
	pci_dev_put(pdev);

	/* Check क्रम the a 7101 PMU */
	pdev = pci_get_device(PCI_VENDOR_ID_AL, 0x7101, शून्य);
	अगर (pdev == शून्य)
		वापस -ENODEV;

	अगर (pci_enable_device(pdev)) अणु
		pci_dev_put(pdev);
		वापस -EIO;
	पूर्ण

	ali_pci = pdev;

	/*
	 *	Initialize the समयr bits
	 */
	pci_पढ़ो_config_dword(pdev, 0xCC, &wकरोg);

	/* Timer bits */
	wकरोg &= ~0x3F;
	/* Issued events */
	wकरोg &= ~((1 << 27)|(1 << 26)|(1 << 25)|(1 << 24));
	/* No monitor bits */
	wकरोg &= ~((1 << 16)|(1 << 13)|(1 << 12)|(1 << 11)|(1 << 10)|(1 << 9));

	pci_ग_लिखो_config_dword(pdev, 0xCC, wकरोg);

	वापस 0;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations ali_fops = अणु
	.owner		=	THIS_MODULE,
	.llseek		=	no_llseek,
	.ग_लिखो		=	ali_ग_लिखो,
	.unlocked_ioctl =	ali_ioctl,
	.compat_ioctl	= 	compat_ptr_ioctl,
	.खोलो		=	ali_खोलो,
	.release	=	ali_release,
पूर्ण;

अटल काष्ठा miscdevice ali_miscdev = अणु
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&ali_fops,
पूर्ण;

अटल काष्ठा notअगरier_block ali_notअगरier = अणु
	.notअगरier_call =	ali_notअगरy_sys,
पूर्ण;

/*
 *	watchकरोg_init	-	module initialiser
 *
 *	Scan क्रम a suitable watchकरोg and अगर so initialize it. Return an error
 *	अगर we cannot, the error causes the module to unload
 */

अटल पूर्णांक __init watchकरोg_init(व्योम)
अणु
	पूर्णांक ret;

	/* Check whether or not the hardware watchकरोg is there */
	अगर (ali_find_watchकरोg() != 0)
		वापस -ENODEV;

	/* Check that the समयout value is within it's range;
	   अगर not reset to the शेष */
	अगर (समयout < 1 || समयout >= 18000) अणु
		समयout = WATCHDOG_TIMEOUT;
		pr_info("timeout value must be 0 < timeout < 18000, using %d\n",
			समयout);
	पूर्ण

	/* Calculate the watchकरोg's समयout */
	ali_समय_रखोr(समयout);

	ret = रेजिस्टर_reboot_notअगरier(&ali_notअगरier);
	अगर (ret != 0) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = misc_रेजिस्टर(&ali_miscdev);
	अगर (ret != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ unreg_reboot;
	पूर्ण

	pr_info("initialized. timeout=%d sec (nowayout=%d)\n",
		समयout, nowayout);

out:
	वापस ret;
unreg_reboot:
	unरेजिस्टर_reboot_notअगरier(&ali_notअगरier);
	जाओ out;
पूर्ण

/*
 *	watchकरोg_निकास	-	module de-initialiser
 *
 *	Called जबतक unloading a successfully installed watchकरोg module.
 */

अटल व्योम __निकास watchकरोg_निकास(व्योम)
अणु
	/* Stop the समयr beक्रमe we leave */
	ali_stop();

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&ali_miscdev);
	unरेजिस्टर_reboot_notअगरier(&ali_notअगरier);
	pci_dev_put(ali_pci);
पूर्ण

module_init(watchकरोg_init);
module_निकास(watchकरोg_निकास);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("ALi M1535 PMU Watchdog Timer driver");
MODULE_LICENSE("GPL");
