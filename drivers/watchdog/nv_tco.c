<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	nv_tco 0.01:	TCO समयr driver क्रम NV chipsets
 *
 *	(c) Copyright 2005 Google Inc., All Rights Reserved.
 *
 *	Based off i8xx_tco.c:
 *	(c) Copyright 2000 kernel concepts <nils@kernelconcepts.de>, All Rights
 *	Reserved.
 *				https://www.kernelconcepts.de
 *
 *	TCO समयr driver क्रम NV chipsets
 *	based on softकरोg.c by Alan Cox <alan@redhat.com>
 */

/*
 *	Includes, defines, variables, module parameters, ...
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#समावेश "nv_tco.h"

/* Module and version inक्रमmation */
#घोषणा TCO_VERSION "0.01"
#घोषणा TCO_MODULE_NAME "NV_TCO"
#घोषणा TCO_DRIVER_NAME   TCO_MODULE_NAME ", v" TCO_VERSION

/* पूर्णांकernal variables */
अटल अचिन्हित पूर्णांक tcobase;
अटल DEFINE_SPINLOCK(tco_lock);	/* Guards the hardware */
अटल अचिन्हित दीर्घ समयr_alive;
अटल अक्षर tco_expect_बंद;
अटल काष्ठा pci_dev *tco_pci;

/* the watchकरोg platक्रमm device */
अटल काष्ठा platक्रमm_device *nv_tco_platक्रमm_device;

/* module parameters */
#घोषणा WATCHDOG_HEARTBEAT 30	/* 30 sec शेष heartbeat (2<heartbeat<39) */
अटल पूर्णांक heartbeat = WATCHDOG_HEARTBEAT;  /* in seconds */
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog heartbeat in seconds. (2<heartbeat<39, "
			    "default=" __MODULE_STRING(WATCHDOG_HEARTBEAT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started"
		" (default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 * Some TCO specअगरic functions
 */
अटल अंतरभूत अचिन्हित अक्षर seconds_to_ticks(पूर्णांक seconds)
अणु
	/* the पूर्णांकernal समयr is stored as ticks which decrement
	 * every 0.6 seconds */
	वापस (seconds * 10) / 6;
पूर्ण

अटल व्योम tco_समयr_start(व्योम)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tco_lock, flags);
	val = inl(TCO_CNT(tcobase));
	val &= ~TCO_CNT_TCOHALT;
	outl(val, TCO_CNT(tcobase));
	spin_unlock_irqrestore(&tco_lock, flags);
पूर्ण

अटल व्योम tco_समयr_stop(व्योम)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tco_lock, flags);
	val = inl(TCO_CNT(tcobase));
	val |= TCO_CNT_TCOHALT;
	outl(val, TCO_CNT(tcobase));
	spin_unlock_irqrestore(&tco_lock, flags);
पूर्ण

अटल व्योम tco_समयr_keepalive(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tco_lock, flags);
	outb(0x01, TCO_RLD(tcobase));
	spin_unlock_irqrestore(&tco_lock, flags);
पूर्ण

अटल पूर्णांक tco_समयr_set_heartbeat(पूर्णांक t)
अणु
	पूर्णांक ret = 0;
	अचिन्हित अक्षर पंचांगrval;
	अचिन्हित दीर्घ flags;
	u8 val;

	/*
	 * note seconds_to_ticks(t) > t, so अगर t > 0x3f, so is
	 * पंचांगrval=seconds_to_ticks(t).  Check that the count in seconds isn't
	 * out of range on it's own (to aव्योम overflow in पंचांगrval).
	 */
	अगर (t < 0 || t > 0x3f)
		वापस -EINVAL;
	पंचांगrval = seconds_to_ticks(t);

	/* "Values of 0h-3h are ignored and should not be attempted" */
	अगर (पंचांगrval > 0x3f || पंचांगrval < 0x04)
		वापस -EINVAL;

	/* Write new heartbeat to watchकरोg */
	spin_lock_irqsave(&tco_lock, flags);
	val = inb(TCO_TMR(tcobase));
	val &= 0xc0;
	val |= पंचांगrval;
	outb(val, TCO_TMR(tcobase));
	val = inb(TCO_TMR(tcobase));

	अगर ((val & 0x3f) != पंचांगrval)
		ret = -EINVAL;
	spin_unlock_irqrestore(&tco_lock, flags);

	अगर (ret)
		वापस ret;

	heartbeat = t;
	वापस 0;
पूर्ण

/*
 *	/dev/watchकरोg handling
 */

अटल पूर्णांक nv_tco_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* /dev/watchकरोg can only be खोलोed once */
	अगर (test_and_set_bit(0, &समयr_alive))
		वापस -EBUSY;

	/* Reload and activate समयr */
	tco_समयr_keepalive();
	tco_समयr_start();
	वापस stream_खोलो(inode, file);
पूर्ण

अटल पूर्णांक nv_tco_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Shut off the समयr */
	अगर (tco_expect_बंद == 42) अणु
		tco_समयr_stop();
	पूर्ण अन्यथा अणु
		pr_crit("Unexpected close, not stopping watchdog!\n");
		tco_समयr_keepalive();
	पूर्ण
	clear_bit(0, &समयr_alive);
	tco_expect_बंद = 0;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार nv_tco_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			    माप_प्रकार len, loff_t *ppos)
अणु
	/* See अगर we got the magic अक्षरacter 'V' and reload the समयr */
	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/*
			 * note: just in हाल someone wrote the magic अक्षरacter
			 * five months ago...
			 */
			tco_expect_बंद = 0;

			/*
			 * scan to see whether or not we got the magic
			 * अक्षरacter
			 */
			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;
				अगर (get_user(c, data + i))
					वापस -EFAULT;
				अगर (c == 'V')
					tco_expect_बंद = 42;
			पूर्ण
		पूर्ण

		/* someone wrote to us, we should reload the समयr */
		tco_समयr_keepalive();
	पूर्ण
	वापस len;
पूर्ण

अटल दीर्घ nv_tco_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_options, retval = -EINVAL;
	पूर्णांक new_heartbeat;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक __user *p = argp;
	अटल स्थिर काष्ठा watchकरोg_info ident = अणु
		.options =		WDIOF_SETTIMEOUT |
					WDIOF_KEEPALIVEPING |
					WDIOF_MAGICCLOSE,
		.firmware_version =	0,
		.identity =		TCO_MODULE_NAME,
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user(argp, &ident, माप(ident)) ? -EFAULT : 0;
	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(0, p);
	हाल WDIOC_SETOPTIONS:
		अगर (get_user(new_options, p))
			वापस -EFAULT;
		अगर (new_options & WDIOS_DISABLECARD) अणु
			tco_समयr_stop();
			retval = 0;
		पूर्ण
		अगर (new_options & WDIOS_ENABLECARD) अणु
			tco_समयr_keepalive();
			tco_समयr_start();
			retval = 0;
		पूर्ण
		वापस retval;
	हाल WDIOC_KEEPALIVE:
		tco_समयr_keepalive();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_heartbeat, p))
			वापस -EFAULT;
		अगर (tco_समयr_set_heartbeat(new_heartbeat))
			वापस -EINVAL;
		tco_समयr_keepalive();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(heartbeat, p);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा file_operations nv_tco_fops = अणु
	.owner =		THIS_MODULE,
	.llseek =		no_llseek,
	.ग_लिखो =		nv_tco_ग_लिखो,
	.unlocked_ioctl =	nv_tco_ioctl,
	.compat_ioctl =		compat_ptr_ioctl,
	.खोलो =			nv_tco_खोलो,
	.release =		nv_tco_release,
पूर्ण;

अटल काष्ठा miscdevice nv_tco_miscdev = अणु
	.minor =	WATCHDOG_MINOR,
	.name =		"watchdog",
	.fops =		&nv_tco_fops,
पूर्ण;

/*
 * Data क्रम PCI driver पूर्णांकerface
 *
 * This data only exists क्रम exporting the supported
 * PCI ids via MODULE_DEVICE_TABLE.  We करो not actually
 * रेजिस्टर a pci_driver, because someone अन्यथा might one day
 * want to रेजिस्टर another driver on the same PCI id.
 */
अटल स्थिर काष्ठा pci_device_id tco_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP78S_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP79_SMBUS,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0, पूर्ण,			/* End of list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, tco_pci_tbl);

/*
 *	Init & निकास routines
 */

अटल अचिन्हित अक्षर nv_tco_getdevice(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	u32 val;

	/* Find the PCI device */
	क्रम_each_pci_dev(dev) अणु
		अगर (pci_match_id(tco_pci_tbl, dev) != शून्य) अणु
			tco_pci = dev;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tco_pci)
		वापस 0;

	/* Find the base io port */
	pci_पढ़ो_config_dword(tco_pci, 0x64, &val);
	val &= 0xffff;
	अगर (val == 0x0001 || val == 0x0000) अणु
		/* Something is wrong here, bar isn't setup */
		pr_err("failed to get tcobase address\n");
		वापस 0;
	पूर्ण
	val &= 0xff00;
	tcobase = val + 0x40;

	अगर (!request_region(tcobase, 0x10, "NV TCO")) अणु
		pr_err("I/O address 0x%04x already in use\n", tcobase);
		वापस 0;
	पूर्ण

	/* Set a reasonable heartbeat beक्रमe we stop the समयr */
	tco_समयr_set_heartbeat(30);

	/*
	 * Stop the TCO beक्रमe we change anything so we करोn't race with
	 * a zeroed समयr.
	 */
	tco_समयr_keepalive();
	tco_समयr_stop();

	/* Disable SMI caused by TCO */
	अगर (!request_region(MCP51_SMI_EN(tcobase), 4, "NV TCO")) अणु
		pr_err("I/O address 0x%04x already in use\n",
		       MCP51_SMI_EN(tcobase));
		जाओ out;
	पूर्ण
	val = inl(MCP51_SMI_EN(tcobase));
	val &= ~MCP51_SMI_EN_TCO;
	outl(val, MCP51_SMI_EN(tcobase));
	val = inl(MCP51_SMI_EN(tcobase));
	release_region(MCP51_SMI_EN(tcobase), 4);
	अगर (val & MCP51_SMI_EN_TCO) अणु
		pr_err("Could not disable SMI caused by TCO\n");
		जाओ out;
	पूर्ण

	/* Check chipset's NO_REBOOT bit */
	pci_पढ़ो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	val |= MCP51_SMBUS_SETUP_B_TCO_REBOOT;
	pci_ग_लिखो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, val);
	pci_पढ़ो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	अगर (!(val & MCP51_SMBUS_SETUP_B_TCO_REBOOT)) अणु
		pr_err("failed to reset NO_REBOOT flag, reboot disabled by hardware\n");
		जाओ out;
	पूर्ण

	वापस 1;
out:
	release_region(tcobase, 0x10);
	वापस 0;
पूर्ण

अटल पूर्णांक nv_tco_init(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	/* Check whether or not the hardware watchकरोg is there */
	अगर (!nv_tco_getdevice())
		वापस -ENODEV;

	/* Check to see अगर last reboot was due to watchकरोg समयout */
	pr_info("Watchdog reboot %sdetected\n",
		inl(TCO_STS(tcobase)) & TCO_STS_TCO2TO_STS ? "" : "not ");

	/* Clear out the old status */
	outl(TCO_STS_RESET, TCO_STS(tcobase));

	/*
	 * Check that the heartbeat value is within it's range.
	 * If not, reset to the शेष.
	 */
	अगर (tco_समयr_set_heartbeat(heartbeat)) अणु
		heartbeat = WATCHDOG_HEARTBEAT;
		tco_समयr_set_heartbeat(heartbeat);
		pr_info("heartbeat value must be 2<heartbeat<39, using %d\n",
			heartbeat);
	पूर्ण

	ret = misc_रेजिस्टर(&nv_tco_miscdev);
	अगर (ret != 0) अणु
		pr_err("cannot register miscdev on minor=%d (err=%d)\n",
		       WATCHDOG_MINOR, ret);
		जाओ unreg_region;
	पूर्ण

	clear_bit(0, &समयr_alive);

	tco_समयr_stop();

	pr_info("initialized (0x%04x). heartbeat=%d sec (nowayout=%d)\n",
		tcobase, heartbeat, nowayout);

	वापस 0;

unreg_region:
	release_region(tcobase, 0x10);
	वापस ret;
पूर्ण

अटल व्योम nv_tco_cleanup(व्योम)
अणु
	u32 val;

	/* Stop the समयr beक्रमe we leave */
	अगर (!nowayout)
		tco_समयr_stop();

	/* Set the NO_REBOOT bit to prevent later reboots, just क्रम sure */
	pci_पढ़ो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	val &= ~MCP51_SMBUS_SETUP_B_TCO_REBOOT;
	pci_ग_लिखो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, val);
	pci_पढ़ो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	अगर (val & MCP51_SMBUS_SETUP_B_TCO_REBOOT) अणु
		pr_crit("Couldn't unset REBOOT bit.  Machine may soon reset\n");
	पूर्ण

	/* Deरेजिस्टर */
	misc_deरेजिस्टर(&nv_tco_miscdev);
	release_region(tcobase, 0x10);
पूर्ण

अटल पूर्णांक nv_tco_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	अगर (tcobase)
		nv_tco_cleanup();

	वापस 0;
पूर्ण

अटल व्योम nv_tco_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	u32 val;

	tco_समयr_stop();

	/* Some BIOSes fail the POST (once) अगर the NO_REBOOT flag is not
	 * unset during shutकरोwn. */
	pci_पढ़ो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	val &= ~MCP51_SMBUS_SETUP_B_TCO_REBOOT;
	pci_ग_लिखो_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, val);
पूर्ण

अटल काष्ठा platक्रमm_driver nv_tco_driver = अणु
	.probe		= nv_tco_init,
	.हटाओ		= nv_tco_हटाओ,
	.shutकरोwn	= nv_tco_shutकरोwn,
	.driver		= अणु
		.name	= TCO_MODULE_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init nv_tco_init_module(व्योम)
अणु
	पूर्णांक err;

	pr_info("NV TCO WatchDog Timer Driver v%s\n", TCO_VERSION);

	err = platक्रमm_driver_रेजिस्टर(&nv_tco_driver);
	अगर (err)
		वापस err;

	nv_tco_platक्रमm_device = platक्रमm_device_रेजिस्टर_simple(
					TCO_MODULE_NAME, -1, शून्य, 0);
	अगर (IS_ERR(nv_tco_platक्रमm_device)) अणु
		err = PTR_ERR(nv_tco_platक्रमm_device);
		जाओ unreg_platक्रमm_driver;
	पूर्ण

	वापस 0;

unreg_platक्रमm_driver:
	platक्रमm_driver_unरेजिस्टर(&nv_tco_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास nv_tco_cleanup_module(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(nv_tco_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&nv_tco_driver);
	pr_info("NV TCO Watchdog Module Unloaded\n");
पूर्ण

module_init(nv_tco_init_module);
module_निकास(nv_tco_cleanup_module);

MODULE_AUTHOR("Mike Waychison");
MODULE_DESCRIPTION("TCO timer driver for NV chipsets");
MODULE_LICENSE("GPL");
