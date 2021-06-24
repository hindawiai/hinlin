<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	HPE WatchDog Driver
 *	based on
 *
 *	SoftDog	0.05:	A Software Watchकरोg Device
 *
 *	(c) Copyright 2018 Hewlett Packard Enterprise Development LP
 *	Thomas Mingarelli <thomas.mingarelli@hpe.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>
#समावेश <यंत्र/nmi.h>
#समावेश <linux/crash_dump.h>

#घोषणा HPWDT_VERSION			"2.0.4"
#घोषणा SECS_TO_TICKS(secs)		((secs) * 1000 / 128)
#घोषणा TICKS_TO_SECS(ticks)		((ticks) * 128 / 1000)
#घोषणा HPWDT_MAX_TICKS			65535
#घोषणा HPWDT_MAX_TIMER			TICKS_TO_SECS(HPWDT_MAX_TICKS)
#घोषणा DEFAULT_MARGIN			30
#घोषणा PRETIMEOUT_SEC			9

अटल bool ilo5;
अटल अचिन्हित पूर्णांक soft_margin = DEFAULT_MARGIN;	/* in seconds */
अटल bool nowayout = WATCHDOG_NOWAYOUT;
अटल bool preसमयout = IS_ENABLED(CONFIG_HPWDT_NMI_DECODING);
अटल पूर्णांक kdumpसमयout = -1;

अटल व्योम __iomem *pci_mem_addr;		/* the PCI-memory address */
अटल अचिन्हित दीर्घ __iomem *hpwdt_nmistat;
अटल अचिन्हित दीर्घ __iomem *hpwdt_समयr_reg;
अटल अचिन्हित दीर्घ __iomem *hpwdt_समयr_con;

अटल स्थिर काष्ठा pci_device_id hpwdt_devices[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_COMPAQ, 0xB203) पूर्ण,	/* iLO2 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_HP, 0x3306) पूर्ण,	/* iLO3 */
	अणु0पूर्ण,			/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, hpwdt_devices);

अटल स्थिर काष्ठा pci_device_id hpwdt_blacklist[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_HP, 0x3306, PCI_VENDOR_ID_HP, 0x1979) पूर्ण, /* auxilary iLO */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_HP, 0x3306, PCI_VENDOR_ID_HP_3PAR, 0x0289) पूर्ण,  /* CL */
	अणु0पूर्ण,			/* terminate list */
पूर्ण;

अटल काष्ठा watchकरोg_device hpwdt_dev;
/*
 *	Watchकरोg operations
 */
अटल पूर्णांक hpwdt_hw_is_running(व्योम)
अणु
	वापस ioपढ़ो8(hpwdt_समयr_con) & 0x01;
पूर्ण

अटल पूर्णांक hpwdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक control = 0x81 | (preसमयout ? 0x4 : 0);
	पूर्णांक reload = SECS_TO_TICKS(min(wdd->समयout, wdd->max_hw_heartbeat_ms/1000));

	dev_dbg(wdd->parent, "start watchdog 0x%08x:0x%08x:0x%02x\n", wdd->समयout, reload, control);
	ioग_लिखो16(reload, hpwdt_समयr_reg);
	ioग_लिखो8(control, hpwdt_समयr_con);

	वापस 0;
पूर्ण

अटल व्योम hpwdt_stop(व्योम)
अणु
	अचिन्हित दीर्घ data;

	pr_debug("stop  watchdog\n");

	data = ioपढ़ो8(hpwdt_समयr_con);
	data &= 0xFE;
	ioग_लिखो8(data, hpwdt_समयr_con);
पूर्ण

अटल पूर्णांक hpwdt_stop_core(काष्ठा watchकरोg_device *wdd)
अणु
	hpwdt_stop();

	वापस 0;
पूर्ण

अटल व्योम hpwdt_ping_ticks(पूर्णांक val)
अणु
	val = min(val, HPWDT_MAX_TICKS);
	ioग_लिखो16(val, hpwdt_समयr_reg);
पूर्ण

अटल पूर्णांक hpwdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक reload = SECS_TO_TICKS(min(wdd->समयout, wdd->max_hw_heartbeat_ms/1000));

	dev_dbg(wdd->parent, "ping  watchdog 0x%08x:0x%08x\n", wdd->समयout, reload);
	hpwdt_ping_ticks(reload);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक hpwdt_समय_लोleft(काष्ठा watchकरोg_device *wdd)
अणु
	वापस TICKS_TO_SECS(ioपढ़ो16(hpwdt_समयr_reg));
पूर्ण

अटल पूर्णांक hpwdt_समय_रखोout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक val)
अणु
	dev_dbg(wdd->parent, "set_timeout = %d\n", val);

	wdd->समयout = val;
	अगर (val <= wdd->preसमयout) अणु
		dev_dbg(wdd->parent, "pretimeout < timeout. Setting to zero\n");
		wdd->preसमयout = 0;
		preसमयout = false;
		अगर (watchकरोg_active(wdd))
			hpwdt_start(wdd);
	पूर्ण
	hpwdt_ping(wdd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HPWDT_NMI_DECODING
अटल पूर्णांक hpwdt_set_preसमयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक req)
अणु
	अचिन्हित पूर्णांक val = 0;

	dev_dbg(wdd->parent, "set_pretimeout = %d\n", req);
	अगर (req) अणु
		val = PRETIMEOUT_SEC;
		अगर (val >= wdd->समयout)
			वापस -EINVAL;
	पूर्ण

	अगर (val != req)
		dev_dbg(wdd->parent, "Rounding pretimeout to: %d\n", val);

	wdd->preसमयout = val;
	preसमयout = !!val;

	अगर (watchकरोg_active(wdd))
		hpwdt_start(wdd);

	वापस 0;
पूर्ण

अटल पूर्णांक hpwdt_my_nmi(व्योम)
अणु
	वापस ioपढ़ो8(hpwdt_nmistat) & 0x6;
पूर्ण

/*
 *	NMI Handler
 */
अटल पूर्णांक hpwdt_preसमयout(अचिन्हित पूर्णांक ulReason, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक mynmi = hpwdt_my_nmi();
	अटल अक्षर panic_msg[] =
		"00: An NMI occurred. Depending on your system the reason "
		"for the NMI is logged in any one of the following resources:\n"
		"1. Integrated Management Log (IML)\n"
		"2. OA Syslog\n"
		"3. OA Forward Progress Log\n"
		"4. iLO Event Log";

	अगर (ilo5 && ulReason == NMI_UNKNOWN && !mynmi)
		वापस NMI_DONE;

	अगर (ilo5 && !preसमयout && !mynmi)
		वापस NMI_DONE;

	अगर (kdumpसमयout < 0)
		hpwdt_stop();
	अन्यथा अगर (kdumpसमयout == 0)
		;
	अन्यथा अणु
		अचिन्हित पूर्णांक val = max((अचिन्हित पूर्णांक)kdumpसमयout, hpwdt_dev.समयout);
		hpwdt_ping_ticks(SECS_TO_TICKS(val));
	पूर्ण

	hex_byte_pack(panic_msg, mynmi);
	nmi_panic(regs, panic_msg);

	वापस NMI_HANDLED;
पूर्ण
#पूर्ण_अगर /* CONFIG_HPWDT_NMI_DECODING */


अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options = WDIOF_PRETIMEOUT    |
		   WDIOF_SETTIMEOUT    |
		   WDIOF_KEEPALIVEPING |
		   WDIOF_MAGICCLOSE,
	.identity = "HPE iLO2+ HW Watchdog Timer",
पूर्ण;

/*
 *	Kernel पूर्णांकerfaces
 */

अटल स्थिर काष्ठा watchकरोg_ops hpwdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= hpwdt_start,
	.stop		= hpwdt_stop_core,
	.ping		= hpwdt_ping,
	.set_समयout	= hpwdt_समय_रखोout,
	.get_समयleft	= hpwdt_समय_लोleft,
#अगर_घोषित CONFIG_HPWDT_NMI_DECODING
	.set_preसमयout	= hpwdt_set_preसमयout,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा watchकरोg_device hpwdt_dev = अणु
	.info		= &ident,
	.ops		= &hpwdt_ops,
	.min_समयout	= 1,
	.समयout	= DEFAULT_MARGIN,
	.preसमयout	= PRETIMEOUT_SEC,
	.max_hw_heartbeat_ms	= HPWDT_MAX_TIMER * 1000,
पूर्ण;


/*
 *	Init & Exit
 */

अटल पूर्णांक hpwdt_init_nmi_decoding(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_HPWDT_NMI_DECODING
	पूर्णांक retval;
	/*
	 * Only one function can रेजिस्टर क्रम NMI_UNKNOWN
	 */
	retval = रेजिस्टर_nmi_handler(NMI_UNKNOWN, hpwdt_preसमयout, 0, "hpwdt");
	अगर (retval)
		जाओ error;
	retval = रेजिस्टर_nmi_handler(NMI_SERR, hpwdt_preसमयout, 0, "hpwdt");
	अगर (retval)
		जाओ error1;
	retval = रेजिस्टर_nmi_handler(NMI_IO_CHECK, hpwdt_preसमयout, 0, "hpwdt");
	अगर (retval)
		जाओ error2;

	dev_info(&dev->dev,
		"HPE Watchdog Timer Driver: NMI decoding initialized\n");

	वापस 0;

error2:
	unरेजिस्टर_nmi_handler(NMI_SERR, "hpwdt");
error1:
	unरेजिस्टर_nmi_handler(NMI_UNKNOWN, "hpwdt");
error:
	dev_warn(&dev->dev,
		"Unable to register a die notifier (err=%d).\n",
		retval);
	वापस retval;
#पूर्ण_अगर	/* CONFIG_HPWDT_NMI_DECODING */
	वापस 0;
पूर्ण

अटल व्योम hpwdt_निकास_nmi_decoding(व्योम)
अणु
#अगर_घोषित CONFIG_HPWDT_NMI_DECODING
	unरेजिस्टर_nmi_handler(NMI_UNKNOWN, "hpwdt");
	unरेजिस्टर_nmi_handler(NMI_SERR, "hpwdt");
	unरेजिस्टर_nmi_handler(NMI_IO_CHECK, "hpwdt");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक hpwdt_init_one(काष्ठा pci_dev *dev,
					स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक retval;

	/*
	 * First let's find out अगर we are on an iLO2+ server. We will
	 * not run on a legacy ASM box.
	 * So we only support the G5 ProLiant servers and higher.
	 */
	अगर (dev->subप्रणाली_venकरोr != PCI_VENDOR_ID_HP &&
	    dev->subप्रणाली_venकरोr != PCI_VENDOR_ID_HP_3PAR) अणु
		dev_warn(&dev->dev,
			"This server does not have an iLO2+ ASIC.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pci_match_id(hpwdt_blacklist, dev)) अणु
		dev_dbg(&dev->dev, "Not supported on this device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pci_enable_device(dev)) अणु
		dev_warn(&dev->dev,
			"Not possible to enable PCI Device: 0x%x:0x%x.\n",
			ent->venकरोr, ent->device);
		वापस -ENODEV;
	पूर्ण

	pci_mem_addr = pci_iomap(dev, 1, 0x80);
	अगर (!pci_mem_addr) अणु
		dev_warn(&dev->dev,
			"Unable to detect the iLO2+ server memory.\n");
		retval = -ENOMEM;
		जाओ error_pci_iomap;
	पूर्ण
	hpwdt_nmistat	= pci_mem_addr + 0x6e;
	hpwdt_समयr_reg = pci_mem_addr + 0x70;
	hpwdt_समयr_con = pci_mem_addr + 0x72;

	/* Have the core update running समयr until user space is पढ़ोy */
	अगर (hpwdt_hw_is_running()) अणु
		dev_info(&dev->dev, "timer is running\n");
		set_bit(WDOG_HW_RUNNING, &hpwdt_dev.status);
	पूर्ण

	/* Initialize NMI Decoding functionality */
	retval = hpwdt_init_nmi_decoding(dev);
	अगर (retval != 0)
		जाओ error_init_nmi_decoding;

	watchकरोg_stop_on_unरेजिस्टर(&hpwdt_dev);
	watchकरोg_set_nowayout(&hpwdt_dev, nowayout);
	watchकरोg_init_समयout(&hpwdt_dev, soft_margin, शून्य);

	अगर (is_kdump_kernel()) अणु
		preसमयout = false;
		kdumpसमयout = 0;
	पूर्ण

	अगर (preसमयout && hpwdt_dev.समयout <= PRETIMEOUT_SEC) अणु
		dev_warn(&dev->dev, "timeout <= pretimeout. Setting pretimeout to zero\n");
		preसमयout = false;
	पूर्ण
	hpwdt_dev.preसमयout = preसमयout ? PRETIMEOUT_SEC : 0;
	kdumpसमयout = min(kdumpसमयout, HPWDT_MAX_TIMER);

	hpwdt_dev.parent = &dev->dev;
	retval = watchकरोg_रेजिस्टर_device(&hpwdt_dev);
	अगर (retval < 0)
		जाओ error_wd_रेजिस्टर;

	dev_info(&dev->dev, "HPE Watchdog Timer Driver: Version: %s\n",
				HPWDT_VERSION);
	dev_info(&dev->dev, "timeout: %d seconds (nowayout=%d)\n",
				hpwdt_dev.समयout, nowayout);
	dev_info(&dev->dev, "pretimeout: %s.\n",
				preसमयout ? "on" : "off");
	dev_info(&dev->dev, "kdumptimeout: %d.\n", kdumpसमयout);

	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_HP_3PAR)
		ilo5 = true;

	वापस 0;

error_wd_रेजिस्टर:
	hpwdt_निकास_nmi_decoding();
error_init_nmi_decoding:
	pci_iounmap(dev, pci_mem_addr);
error_pci_iomap:
	pci_disable_device(dev);
	वापस retval;
पूर्ण

अटल व्योम hpwdt_निकास(काष्ठा pci_dev *dev)
अणु
	watchकरोg_unरेजिस्टर_device(&hpwdt_dev);
	hpwdt_निकास_nmi_decoding();
	pci_iounmap(dev, pci_mem_addr);
	pci_disable_device(dev);
पूर्ण

अटल काष्ठा pci_driver hpwdt_driver = अणु
	.name = "hpwdt",
	.id_table = hpwdt_devices,
	.probe = hpwdt_init_one,
	.हटाओ = hpwdt_निकास,
पूर्ण;

MODULE_AUTHOR("Tom Mingarelli");
MODULE_DESCRIPTION("hpe watchdog driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(HPWDT_VERSION);

module_param(soft_margin, पूर्णांक, 0);
MODULE_PARM_DESC(soft_margin, "Watchdog timeout in seconds");

module_param_named(समयout, soft_margin, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Alias of soft_margin");

module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
		__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

module_param(kdumpसमयout, पूर्णांक, 0444);
MODULE_PARM_DESC(kdumpसमयout, "Timeout applied for crash kernel transition in seconds");

#अगर_घोषित CONFIG_HPWDT_NMI_DECODING
module_param(preसमयout, bool, 0);
MODULE_PARM_DESC(preसमयout, "Watchdog pretimeout enabled");
#पूर्ण_अगर

module_pci_driver(hpwdt_driver);
