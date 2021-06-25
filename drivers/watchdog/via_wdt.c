<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VIA Chipset Watchकरोg Driver
 *
 * Copyright (C) 2011 Sigfox
 * Author: Marc Vertes <marc.vertes@sigfox.com>
 * Based on a preliminary version from Harald Welte <HaraldWelte@viatech.com>
 * Timer code by Wim Van Sebroeck <wim@iguana.be>
 *
 * Caveat: PnP must be enabled in BIOS to allow full access to watchकरोg
 * control रेजिस्टरs. If not, the watchकरोg must be configured in BIOS manually.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयr.h>
#समावेश <linux/watchकरोg.h>

/* Configuration रेजिस्टरs relative to the pci device */
#घोषणा VIA_WDT_MMIO_BASE	0xe8	/* MMIO region base address */
#घोषणा VIA_WDT_CONF		0xec	/* watchकरोg enable state */

/* Relevant bits क्रम the VIA_WDT_CONF रेजिस्टर */
#घोषणा VIA_WDT_CONF_ENABLE	0x01	/* 1: enable watchकरोg */
#घोषणा VIA_WDT_CONF_MMIO	0x02	/* 1: enable watchकरोg MMIO */

/*
 * The MMIO region contains the watchकरोg control रेजिस्टर and the
 * hardware समयr counter.
 */
#घोषणा VIA_WDT_MMIO_LEN	8	/* MMIO region length in bytes */
#घोषणा VIA_WDT_CTL		0	/* MMIO addr+0: state/control reg. */
#घोषणा VIA_WDT_COUNT		4	/* MMIO addr+4: समयr counter reg. */

/* Bits क्रम the VIA_WDT_CTL रेजिस्टर */
#घोषणा VIA_WDT_RUNNING		0x01	/* 0: stop, 1: running */
#घोषणा VIA_WDT_FIRED		0x02	/* 1: restarted by expired watchकरोg */
#घोषणा VIA_WDT_PWROFF		0x04	/* 0: reset, 1: घातeroff */
#घोषणा VIA_WDT_DISABLED	0x08	/* 1: समयr is disabled */
#घोषणा VIA_WDT_TRIGGER		0x80	/* 1: start a new countकरोwn */

/* Hardware heartbeat in seconds */
#घोषणा WDT_HW_HEARTBEAT 1

/* Timer heartbeat (500ms) */
#घोषणा WDT_HEARTBEAT	(HZ/2)	/* should be <= ((WDT_HW_HEARTBEAT*HZ)/2) */

/* User space समयout in seconds */
#घोषणा WDT_TIMEOUT_MAX	1023	/* approx. 17 min. */
#घोषणा WDT_TIMEOUT	60
अटल पूर्णांक समयout = WDT_TIMEOUT;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in seconds, between 1 and 1023 "
	"(default = " __MODULE_STRING(WDT_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
	"(default = " __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल काष्ठा watchकरोg_device wdt_dev;
अटल काष्ठा resource wdt_res;
अटल व्योम __iomem *wdt_mem;
अटल अचिन्हित पूर्णांक mmio;
अटल व्योम wdt_समयr_tick(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(समयr, wdt_समयr_tick);
					/* The समयr that pings the watchकरोg */
अटल अचिन्हित दीर्घ next_heartbeat;	/* the next_heartbeat क्रम the समयr */

अटल अंतरभूत व्योम wdt_reset(व्योम)
अणु
	अचिन्हित पूर्णांक ctl = पढ़ोl(wdt_mem);

	ग_लिखोl(ctl | VIA_WDT_TRIGGER, wdt_mem);
पूर्ण

/*
 * Timer tick: the समयr will make sure that the watchकरोg समयr hardware
 * is being reset in समय. The conditions to करो this are:
 *  1) the watchकरोg समयr has been started and /dev/watchकरोg is खोलो
 *     and there is still समय left beक्रमe userspace should send the
 *     next heartbeat/ping. (note: the पूर्णांकernal heartbeat is much smaller
 *     then the बाह्यal/userspace heartbeat).
 *  2) the watchकरोg समयr has been stopped by userspace.
 */
अटल व्योम wdt_समयr_tick(काष्ठा समयr_list *unused)
अणु
	अगर (समय_beक्रमe(jअगरfies, next_heartbeat) ||
	   (!watchकरोg_active(&wdt_dev))) अणु
		wdt_reset();
		mod_समयr(&समयr, jअगरfies + WDT_HEARTBEAT);
	पूर्ण अन्यथा
		pr_crit("I will reboot your machine !\n");
पूर्ण

अटल पूर्णांक wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	/* calculate when the next userspace समयout will be */
	next_heartbeat = jअगरfies + wdd->समयout * HZ;
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	अचिन्हित पूर्णांक ctl = पढ़ोl(wdt_mem);

	ग_लिखोl(wdd->समयout, wdt_mem + VIA_WDT_COUNT);
	ग_लिखोl(ctl | VIA_WDT_RUNNING | VIA_WDT_TRIGGER, wdt_mem);
	wdt_ping(wdd);
	mod_समयr(&समयr, jअगरfies + WDT_HEARTBEAT);
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	अचिन्हित पूर्णांक ctl = पढ़ोl(wdt_mem);

	ग_लिखोl(ctl & ~VIA_WDT_RUNNING, wdt_mem);
	वापस 0;
पूर्ण

अटल पूर्णांक wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
			   अचिन्हित पूर्णांक new_समयout)
अणु
	ग_लिखोl(new_समयout, wdt_mem + VIA_WDT_COUNT);
	wdd->समयout = new_समयout;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info wdt_info = अणु
	.identity =	"VIA watchdog",
	.options =	WDIOF_CARDRESET |
			WDIOF_SETTIMEOUT |
			WDIOF_MAGICCLOSE |
			WDIOF_KEEPALIVEPING,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops wdt_ops = अणु
	.owner =	THIS_MODULE,
	.start =	wdt_start,
	.stop =		wdt_stop,
	.ping =		wdt_ping,
	.set_समयout =	wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device wdt_dev = अणु
	.info =		&wdt_info,
	.ops =		&wdt_ops,
	.min_समयout =	1,
	.max_समयout =	WDT_TIMEOUT_MAX,
पूर्ण;

अटल पूर्णांक wdt_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित अक्षर conf;
	पूर्णांक ret = -ENODEV;

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Allocate a MMIO region which contains watchकरोg control रेजिस्टर
	 * and counter, then configure the watchकरोg to use this region.
	 * This is possible only अगर PnP is properly enabled in BIOS.
	 * If not, the watchकरोg must be configured in BIOS manually.
	 */
	अगर (allocate_resource(&iomem_resource, &wdt_res, VIA_WDT_MMIO_LEN,
			      0xf0000000, 0xffffff00, 0xff, शून्य, शून्य)) अणु
		dev_err(&pdev->dev, "MMIO allocation failed\n");
		जाओ err_out_disable_device;
	पूर्ण

	pci_ग_लिखो_config_dword(pdev, VIA_WDT_MMIO_BASE, wdt_res.start);
	pci_पढ़ो_config_byte(pdev, VIA_WDT_CONF, &conf);
	conf |= VIA_WDT_CONF_ENABLE | VIA_WDT_CONF_MMIO;
	pci_ग_लिखो_config_byte(pdev, VIA_WDT_CONF, conf);

	pci_पढ़ो_config_dword(pdev, VIA_WDT_MMIO_BASE, &mmio);
	अगर (mmio) अणु
		dev_info(&pdev->dev, "VIA Chipset watchdog MMIO: %x\n", mmio);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "MMIO setting failed. Check BIOS.\n");
		जाओ err_out_resource;
	पूर्ण

	अगर (!request_mem_region(mmio, VIA_WDT_MMIO_LEN, "via_wdt")) अणु
		dev_err(&pdev->dev, "MMIO region busy\n");
		जाओ err_out_resource;
	पूर्ण

	wdt_mem = ioremap(mmio, VIA_WDT_MMIO_LEN);
	अगर (wdt_mem == शून्य) अणु
		dev_err(&pdev->dev, "cannot remap VIA wdt MMIO registers\n");
		जाओ err_out_release;
	पूर्ण

	अगर (समयout < 1 || समयout > WDT_TIMEOUT_MAX)
		समयout = WDT_TIMEOUT;

	wdt_dev.समयout = समयout;
	wdt_dev.parent = &pdev->dev;
	watchकरोg_set_nowayout(&wdt_dev, nowayout);
	अगर (पढ़ोl(wdt_mem) & VIA_WDT_FIRED)
		wdt_dev.bootstatus |= WDIOF_CARDRESET;

	ret = watchकरोg_रेजिस्टर_device(&wdt_dev);
	अगर (ret)
		जाओ err_out_iounmap;

	/* start triggering, in हाल of watchकरोg alपढ़ोy enabled by BIOS */
	mod_समयr(&समयr, jअगरfies + WDT_HEARTBEAT);
	वापस 0;

err_out_iounmap:
	iounmap(wdt_mem);
err_out_release:
	release_mem_region(mmio, VIA_WDT_MMIO_LEN);
err_out_resource:
	release_resource(&wdt_res);
err_out_disable_device:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम wdt_हटाओ(काष्ठा pci_dev *pdev)
अणु
	watchकरोg_unरेजिस्टर_device(&wdt_dev);
	del_समयr_sync(&समयr);
	iounmap(wdt_mem);
	release_mem_region(mmio, VIA_WDT_MMIO_LEN);
	release_resource(&wdt_res);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id wdt_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_CX700) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VX800) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VX855) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा pci_driver wdt_driver = अणु
	.name		= "via_wdt",
	.id_table	= wdt_pci_table,
	.probe		= wdt_probe,
	.हटाओ		= wdt_हटाओ,
पूर्ण;

module_pci_driver(wdt_driver);

MODULE_AUTHOR("Marc Vertes");
MODULE_DESCRIPTION("Driver for watchdog timer on VIA chipset");
MODULE_LICENSE("GPL");
