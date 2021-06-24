<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	ALi M7101 PMU Computer Watchकरोg Timer driver
 *
 *	Based on w83877f_wdt.c by Scott Jennings <linuxdrivers@oro.net>
 *	and the Cobalt kernel WDT समयr driver by Tim Hockin
 *	                                      <thockin@cobaltnet.com>
 *
 *	(c)2002 Steve Hill <steve@navaho.co.uk>
 *
 *  This WDT driver is dअगरferent from most other Linux WDT
 *  drivers in that the driver will ping the watchकरोg by itself,
 *  because this particular WDT has a very लघु समयout (1.6
 *  seconds) and it would be insane to count on any userspace
 *  daemon always getting scheduled within that समय frame.
 *
 *  Additions:
 *   Aug 23, 2004 - Added use_gpio module parameter क्रम use on revision a1d PMUs
 *                  found on very old cobalt hardware.
 *                  -- Mike Waychison <michael.waychison@sun.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/ioport.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>


#घोषणा WDT_ENABLE 0x9C
#घोषणा WDT_DISABLE 0x8C

#घोषणा ALI_7101_WDT    0x92
#घोषणा ALI_7101_GPIO   0x7D
#घोषणा ALI_7101_GPIO_O 0x7E
#घोषणा ALI_WDT_ARM     0x01

/*
 * We're going to use a 1 second समयout.
 * If we reset the watchकरोg every ~250ms we should be safe.  */

#घोषणा WDT_INTERVAL (HZ/4+1)

/*
 * We must not require too good response from the userspace daemon.
 * Here we require the userspace daemon to send us a heartbeat
 * अक्षर to /dev/watchकरोg every 30 seconds.
 */

#घोषणा WATCHDOG_TIMEOUT 30            /* 30 sec शेष समयout */
/* in seconds, will be multiplied by HZ to get seconds to रुको क्रम a ping */
अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		"Watchdog timeout in seconds. (1<=timeout<=3600, default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल पूर्णांक use_gpio; /* Use the pic (क्रम a1d revision alim7101) */
module_param(use_gpio, पूर्णांक, 0);
MODULE_PARM_DESC(use_gpio,
		"Use the gpio watchdog (required by old cobalt boards).");

अटल व्योम wdt_समयr_ping(काष्ठा समयr_list *);
अटल DEFINE_TIMER(समयr, wdt_समयr_ping);
अटल अचिन्हित दीर्घ next_heartbeat;
अटल अचिन्हित दीर्घ wdt_is_खोलो;
अटल अक्षर wdt_expect_बंद;
अटल काष्ठा pci_dev *alim7101_pmu;

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
		"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 *	Whack the करोg
 */

अटल व्योम wdt_समयr_ping(काष्ठा समयr_list *unused)
अणु
	/* If we got a heartbeat pulse within the WDT_US_INTERVAL
	 * we agree to ping the WDT
	 */
	अक्षर पंचांगp;

	अगर (समय_beक्रमe(jअगरfies, next_heartbeat)) अणु
		/* Ping the WDT (this is actually a disarm/arm sequence) */
		pci_पढ़ो_config_byte(alim7101_pmu, 0x92, &पंचांगp);
		pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_WDT, (पंचांगp & ~ALI_WDT_ARM));
		pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_WDT, (पंचांगp | ALI_WDT_ARM));
		अगर (use_gpio) अणु
			pci_पढ़ो_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, &पंचांगp);
			pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, पंचांगp | 0x20);
			pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, पंचांगp & ~0x20);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
	पूर्ण
	/* Re-set the समयr पूर्णांकerval */
	mod_समयr(&समयr, jअगरfies + WDT_INTERVAL);
पूर्ण

/*
 * Utility routines
 */

अटल व्योम wdt_change(पूर्णांक ग_लिखोval)
अणु
	अक्षर पंचांगp;

	pci_पढ़ो_config_byte(alim7101_pmu, ALI_7101_WDT, &पंचांगp);
	अगर (ग_लिखोval == WDT_ENABLE) अणु
		pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_WDT, (पंचांगp | ALI_WDT_ARM));
		अगर (use_gpio) अणु
			pci_पढ़ो_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, &पंचांगp);
			pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, पंचांगp & ~0x20);
		पूर्ण

	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_WDT, (पंचांगp & ~ALI_WDT_ARM));
		अगर (use_gpio) अणु
			pci_पढ़ो_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, &पंचांगp);
			pci_ग_लिखो_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, पंचांगp | 0x20);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wdt_startup(व्योम)
अणु
	next_heartbeat = jअगरfies + (समयout * HZ);

	/* We must enable beक्रमe we kick off the समयr in हाल the समयr
	   occurs as we ping it */

	wdt_change(WDT_ENABLE);

	/* Start the समयr */
	mod_समयr(&समयr, jअगरfies + WDT_INTERVAL);

	pr_info("Watchdog timer is now enabled\n");
पूर्ण

अटल व्योम wdt_turnoff(व्योम)
अणु
	/* Stop the समयr */
	del_समयr_sync(&समयr);
	wdt_change(WDT_DISABLE);
	pr_info("Watchdog timer is now disabled...\n");
पूर्ण

अटल व्योम wdt_keepalive(व्योम)
अणु
	/* user land ping */
	next_heartbeat = jअगरfies + (समयout * HZ);
पूर्ण

/*
 * /dev/watchकरोg handling
 */

अटल sमाप_प्रकार fop_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार ofs;

			/* note: just in हाल someone wrote the magic अक्षरacter
			 * five months ago... */
			wdt_expect_बंद = 0;

			/* now scan */
			क्रम (ofs = 0; ofs != count; ofs++) अणु
				अक्षर c;
				अगर (get_user(c, buf + ofs))
					वापस -EFAULT;
				अगर (c == 'V')
					wdt_expect_बंद = 42;
			पूर्ण
		पूर्ण
		/* someone wrote to us, we should restart समयr */
		wdt_keepalive();
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Just in हाल we're alपढ़ोy talking to someone... */
	अगर (test_and_set_bit(0, &wdt_is_खोलो))
		वापस -EBUSY;
	/* Good, fire up the show */
	wdt_startup();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक fop_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (wdt_expect_बंद == 42)
		wdt_turnoff();
	अन्यथा अणु
		/* wim: shouldn't there be a: del_समयr(&समयr); */
		pr_crit("device file closed unexpectedly. Will not stop the WDT!\n");
	पूर्ण
	clear_bit(0, &wdt_is_खोलो);
	wdt_expect_बंद = 0;
	वापस 0;
पूर्ण

अटल दीर्घ fop_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT
							| WDIOF_MAGICCLOSE,
		.firmware_version = 1,
		.identity = "ALiM7101",
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
			wdt_turnoff();
			retval = 0;
		पूर्ण
		अगर (new_options & WDIOS_ENABLECARD) अणु
			wdt_startup();
			retval = 0;
		पूर्ण
		वापस retval;
	पूर्ण
	हाल WDIOC_KEEPALIVE:
		wdt_keepalive();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
	अणु
		पूर्णांक new_समयout;

		अगर (get_user(new_समयout, p))
			वापस -EFAULT;
		/* arbitrary upper limit */
		अगर (new_समयout < 1 || new_समयout > 3600)
			वापस -EINVAL;
		समयout = new_समयout;
		wdt_keepalive();
	पूर्ण
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(समयout, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations wdt_fops = अणु
	.owner		=	THIS_MODULE,
	.llseek		=	no_llseek,
	.ग_लिखो		=	fop_ग_लिखो,
	.खोलो		=	fop_खोलो,
	.release	=	fop_बंद,
	.unlocked_ioctl	=	fop_ioctl,
	.compat_ioctl	= 	compat_ptr_ioctl,
पूर्ण;

अटल काष्ठा miscdevice wdt_miscdev = अणु
	.minor	=	WATCHDOG_MINOR,
	.name	=	"watchdog",
	.fops	=	&wdt_fops,
पूर्ण;

अटल पूर्णांक wdt_restart_handle(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ mode,
			      व्योम *cmd)
अणु
	/*
	 * Cobalt devices have no way of rebooting themselves other
	 * than getting the watchकरोg to pull reset, so we restart the
	 * watchकरोg on reboot with no heartbeat.
	 */
	wdt_change(WDT_ENABLE);

	/* loop until the watchकरोg fires */
	जबतक (true)
		;

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block wdt_restart_handler = अणु
	.notअगरier_call = wdt_restart_handle,
	.priority = 128,
पूर्ण;

/*
 *	Notअगरier क्रम प्रणाली करोwn
 */

अटल पूर्णांक wdt_notअगरy_sys(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		wdt_turnoff();

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	The WDT needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block wdt_notअगरier = अणु
	.notअगरier_call = wdt_notअगरy_sys,
पूर्ण;

अटल व्योम __निकास alim7101_wdt_unload(व्योम)
अणु
	wdt_turnoff();
	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&wdt_miscdev);
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	unरेजिस्टर_restart_handler(&wdt_restart_handler);
	pci_dev_put(alim7101_pmu);
पूर्ण

अटल पूर्णांक __init alim7101_wdt_init(व्योम)
अणु
	पूर्णांक rc = -EBUSY;
	काष्ठा pci_dev *ali1543_south;
	अक्षर पंचांगp;

	pr_info("Steve Hill <steve@navaho.co.uk>\n");
	alim7101_pmu = pci_get_device(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M7101,
		शून्य);
	अगर (!alim7101_pmu) अणु
		pr_info("ALi M7101 PMU not present - WDT not set\n");
		वापस -EBUSY;
	पूर्ण

	/* Set the WDT in the PMU to 1 second */
	pci_ग_लिखो_config_byte(alim7101_pmu, ALI_7101_WDT, 0x02);

	ali1543_south = pci_get_device(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M1533,
		शून्य);
	अगर (!ali1543_south) अणु
		pr_info("ALi 1543 South-Bridge not present - WDT not set\n");
		जाओ err_out;
	पूर्ण
	pci_पढ़ो_config_byte(ali1543_south, 0x5e, &पंचांगp);
	pci_dev_put(ali1543_south);
	अगर ((पंचांगp & 0x1e) == 0x00) अणु
		अगर (!use_gpio) अणु
			pr_info("Detected old alim7101 revision 'a1d'.  If this is a cobalt board, set the 'use_gpio' module parameter.\n");
			जाओ err_out;
		पूर्ण
		nowayout = 1;
	पूर्ण अन्यथा अगर ((पंचांगp & 0x1e) != 0x12 && (पंचांगp & 0x1e) != 0x00) अणु
		pr_info("ALi 1543 South-Bridge does not have the correct revision number (???1001?) - WDT not set\n");
		जाओ err_out;
	पूर्ण

	अगर (समयout < 1 || समयout > 3600) अणु
		/* arbitrary upper limit */
		समयout = WATCHDOG_TIMEOUT;
		pr_info("timeout value must be 1 <= x <= 3600, using %d\n",
			समयout);
	पूर्ण

	rc = रेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	अगर (rc) अणु
		pr_err("cannot register reboot notifier (err=%d)\n", rc);
		जाओ err_out;
	पूर्ण

	rc = रेजिस्टर_restart_handler(&wdt_restart_handler);
	अगर (rc) अणु
		pr_err("cannot register restart handler (err=%d)\n", rc);
		जाओ err_out_reboot;
	पूर्ण

	rc = misc_रेजिस्टर(&wdt_miscdev);
	अगर (rc) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       wdt_miscdev.minor, rc);
		जाओ err_out_restart;
	पूर्ण

	अगर (nowayout)
		__module_get(THIS_MODULE);

	pr_info("WDT driver for ALi M7101 initialised. timeout=%d sec (nowayout=%d)\n",
		समयout, nowayout);
	वापस 0;

err_out_restart:
	unरेजिस्टर_restart_handler(&wdt_restart_handler);
err_out_reboot:
	unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
err_out:
	pci_dev_put(alim7101_pmu);
	वापस rc;
पूर्ण

module_init(alim7101_wdt_init);
module_निकास(alim7101_wdt_unload);

अटल स्थिर काष्ठा pci_device_id alim7101_pci_tbl[] __used = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M1533) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M7101) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, alim7101_pci_tbl);

MODULE_AUTHOR("Steve Hill");
MODULE_DESCRIPTION("ALi M7101 PMU Computer Watchdog Timer driver");
MODULE_LICENSE("GPL");
