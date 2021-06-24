<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 *
 * [ Initialisation is based on Linus'  ]
 * [ uhci code and gregs ohci fragments ]
 * [ (C) Copyright 1999 Linus Torvalds  ]
 * [ (C) Copyright 1999 Gregory P. Smith]
 *
 * PCI Bus Glue
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ohci.h"
#समावेश "pci-quirks.h"

#घोषणा DRIVER_DESC "OHCI PCI platform driver"

अटल स्थिर अक्षर hcd_name[] = "ohci-pci";


/*-------------------------------------------------------------------------*/

अटल पूर्णांक broken_suspend(काष्ठा usb_hcd *hcd)
अणु
	device_init_wakeup(&hcd->self.root_hub->dev, 0);
	वापस 0;
पूर्ण

/* AMD 756, क्रम most chips (early revs), corrupts रेजिस्टर
 * values on पढ़ो ... so enable the venकरोr workaround.
 */
अटल पूर्णांक ohci_quirk_amd756(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci->flags = OHCI_QUIRK_AMD756;
	ohci_dbg (ohci, "AMD756 erratum 4 workaround\n");

	/* also erratum 10 (suspend/resume issues) */
	वापस broken_suspend(hcd);
पूर्ण

/* Apple's OHCI driver has a lot of bizarre workarounds
 * क्रम this chip.  Evidently control and bulk lists
 * can get confused.  (B&W G3 models, and ...)
 */
अटल पूर्णांक ohci_quirk_opti(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci_dbg (ohci, "WARNING: OPTi workarounds unavailable\n");

	वापस 0;
पूर्ण

/* Check क्रम NSC87560. We have to look at the bridge (fn1) to
 * identअगरy the USB (fn2). This quirk might apply to more or
 * even all NSC stuff.
 */
अटल पूर्णांक ohci_quirk_ns(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hcd->self.controller);
	काष्ठा pci_dev	*b;

	b  = pci_get_slot (pdev->bus, PCI_DEVFN (PCI_SLOT (pdev->devfn), 1));
	अगर (b && b->device == PCI_DEVICE_ID_NS_87560_LIO
	    && b->venकरोr == PCI_VENDOR_ID_NS) अणु
		काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);

		ohci->flags |= OHCI_QUIRK_SUPERIO;
		ohci_dbg (ohci, "Using NSC SuperIO setup\n");
	पूर्ण
	pci_dev_put(b);

	वापस 0;
पूर्ण

/* Check क्रम Compaq's ZFMicro chipset, which needs लघु
 * delays beक्रमe control or bulk queues get re-activated
 * in finish_unlinks()
 */
अटल पूर्णांक ohci_quirk_zfmicro(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci->flags |= OHCI_QUIRK_ZFMICRO;
	ohci_dbg(ohci, "enabled Compaq ZFMicro chipset quirks\n");

	वापस 0;
पूर्ण

/* Check क्रम Toshiba SCC OHCI which has big endian रेजिस्टरs
 * and little endian in memory data काष्ठाures
 */
अटल पूर्णांक ohci_quirk_toshiba_scc(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);

	/* That chip is only present in the southbridge of some
	 * cell based platक्रमms which are supposed to select
	 * CONFIG_USB_OHCI_BIG_ENDIAN_MMIO. We verअगरy here अगर
	 * that was the हाल though.
	 */
#अगर_घोषित CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
	ohci->flags |= OHCI_QUIRK_BE_MMIO;
	ohci_dbg (ohci, "enabled big endian Toshiba quirk\n");
	वापस 0;
#अन्यथा
	ohci_err (ohci, "unsupported big endian Toshiba quirk\n");
	वापस -ENXIO;
#पूर्ण_अगर
पूर्ण

/* Check क्रम NEC chip and apply quirk क्रम allegedly lost पूर्णांकerrupts.
 */

अटल व्योम ohci_quirk_nec_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ohci_hcd *ohci = container_of(work, काष्ठा ohci_hcd, nec_work);
	पूर्णांक status;

	status = ohci_restart(ohci);
	अगर (status != 0)
		ohci_err(ohci, "Restarting NEC controller failed in %s, %d\n",
			 "ohci_restart", status);
पूर्ण

अटल पूर्णांक ohci_quirk_nec(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci->flags |= OHCI_QUIRK_NEC;
	INIT_WORK(&ohci->nec_work, ohci_quirk_nec_worker);
	ohci_dbg (ohci, "enabled NEC chipset lost interrupt quirk\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_quirk_amd700(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);

	अगर (usb_amd_quirk_pll_check())
		ohci->flags |= OHCI_QUIRK_AMD_PLL;

	/* SB800 needs pre-fetch fix */
	अगर (usb_amd_prefetch_quirk()) अणु
		ohci->flags |= OHCI_QUIRK_AMD_PREFETCH;
		ohci_dbg(ohci, "enabled AMD prefetch quirk\n");
	पूर्ण

	ohci->flags |= OHCI_QUIRK_GLOBAL_SUSPEND;
	वापस 0;
पूर्ण

अटल पूर्णांक ohci_quirk_qemu(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);

	ohci->flags |= OHCI_QUIRK_QEMU;
	ohci_dbg(ohci, "enabled qemu quirk\n");
	वापस 0;
पूर्ण

/* List of quirks क्रम OHCI */
अटल स्थिर काष्ठा pci_device_id ohci_pci_quirks[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_AMD, 0x740c),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_amd756,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_OPTI, 0xc861),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_opti,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_ANY_ID),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_ns,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_COMPAQ, 0xa0f8),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_zfmicro,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA_2, 0x01b6),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_toshiba_scc,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_NEC, PCI_DEVICE_ID_NEC_USB),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_nec,
	पूर्ण,
	अणु
		/* Toshiba portege 4000 */
		.venकरोr		= PCI_VENDOR_ID_AL,
		.device		= 0x5237,
		.subvenकरोr	= PCI_VENDOR_ID_TOSHIBA,
		.subdevice	= 0x0004,
		.driver_data	= (अचिन्हित दीर्घ) broken_suspend,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_ITE, 0x8152),
		.driver_data = (अचिन्हित दीर्घ) broken_suspend,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_ATI, 0x4397),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_amd700,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_ATI, 0x4398),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_amd700,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_ATI, 0x4399),
		.driver_data = (अचिन्हित दीर्घ)ohci_quirk_amd700,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_APPLE,
		.device		= 0x003f,
		.subvenकरोr	= PCI_SUBVENDOR_ID_REDHAT_QUMRANET,
		.subdevice	= PCI_SUBDEVICE_ID_QEMU,
		.driver_data	= (अचिन्हित दीर्घ)ohci_quirk_qemu,
	पूर्ण,

	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक ohci_pci_reset (काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci (hcd);
	काष्ठा pci_dev *pdev = to_pci_dev(hcd->self.controller);
	पूर्णांक ret = 0;

	अगर (hcd->self.controller) अणु
		स्थिर काष्ठा pci_device_id *quirk_id;

		quirk_id = pci_match_id(ohci_pci_quirks, pdev);
		अगर (quirk_id != शून्य) अणु
			पूर्णांक (*quirk)(काष्ठा usb_hcd *ohci);
			quirk = (व्योम *)quirk_id->driver_data;
			ret = quirk(hcd);
		पूर्ण
	पूर्ण

	अगर (ret == 0)
		ret = ohci_setup(hcd);
	/*
	* After ohci setup RWC may not be set क्रम add-in PCI cards.
	* This transfers PCI PM wakeup capabilities.
	*/
	अगर (device_can_wakeup(&pdev->dev))
		ohci->hc_control |= OHCI_CTRL_RWC;
	वापस ret;
पूर्ण

अटल काष्ठा hc_driver __पढ़ो_mostly ohci_pci_hc_driver;

अटल स्थिर काष्ठा ohci_driver_overrides pci_overrides __initस्थिर = अणु
	.product_desc =		"OHCI PCI host controller",
	.reset =		ohci_pci_reset,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु अणु
	/* handle any USB OHCI controller */
	PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_USB_OHCI, ~0),
	पूर्ण, अणु
	/* The device in the ConneXT I/O hub has no class reg */
	PCI_VDEVICE(STMICRO, PCI_DEVICE_ID_STMICRO_USB_OHCI),
	पूर्ण, अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (pci, pci_ids);

अटल पूर्णांक ohci_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस usb_hcd_pci_probe(dev, id, &ohci_pci_hc_driver);
पूर्ण

/* pci driver glue; this is a "new style" PCI driver module */
अटल काष्ठा pci_driver ohci_pci_driver = अणु
	.name =		hcd_name,
	.id_table =	pci_ids,

	.probe =	ohci_pci_probe,
	.हटाओ =	usb_hcd_pci_हटाओ,
	.shutकरोwn =	usb_hcd_pci_shutकरोwn,

#अगर_घोषित CONFIG_PM
	.driver =	अणु
		.pm =	&usb_hcd_pci_pm_ops
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init ohci_pci_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ohci_init_driver(&ohci_pci_hc_driver, &pci_overrides);

#अगर_घोषित	CONFIG_PM
	/* Entries क्रम the PCI suspend/resume callbacks are special */
	ohci_pci_hc_driver.pci_suspend = ohci_suspend;
	ohci_pci_hc_driver.pci_resume = ohci_resume;
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&ohci_pci_driver);
पूर्ण
module_init(ohci_pci_init);

अटल व्योम __निकास ohci_pci_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ohci_pci_driver);
पूर्ण
module_निकास(ohci_pci_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_SOFTDEP("pre: ehci_pci");
