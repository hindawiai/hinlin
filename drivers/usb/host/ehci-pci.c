<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * EHCI HCD (Host Controller Driver) PCI Bus Glue.
 *
 * Copyright (c) 2000-2004 by David Brownell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ehci.h"
#समावेश "pci-quirks.h"

#घोषणा DRIVER_DESC "EHCI PCI platform driver"

अटल स्थिर अक्षर hcd_name[] = "ehci-pci";

/* defined here to aव्योम adding to pci_ids.h क्रम single instance use */
#घोषणा PCI_DEVICE_ID_INTEL_CE4100_USB	0x2e70

/*-------------------------------------------------------------------------*/
#घोषणा PCI_DEVICE_ID_INTEL_QUARK_X1000_SOC		0x0939
अटल अंतरभूत bool is_पूर्णांकel_quark_x1000(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
		pdev->device == PCI_DEVICE_ID_INTEL_QUARK_X1000_SOC;
पूर्ण

/*
 * This is the list of PCI IDs क्रम the devices that have EHCI USB class and
 * specअगरic drivers क्रम that. One of the example is a ChipIdea device installed
 * on some Intel MID platक्रमms.
 */
अटल स्थिर काष्ठा pci_device_id bypass_pci_id_table[] = अणु
	/* ChipIdea on Intel MID platक्रमm */
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x0811), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x0829), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe006), पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत bool is_bypassed_id(काष्ठा pci_dev *pdev)
अणु
	वापस !!pci_match_id(bypass_pci_id_table, pdev);
पूर्ण

/*
 * 0x84 is the offset of in/out threshold रेजिस्टर,
 * and it is the same offset as the रेजिस्टर of 'hostpc'.
 */
#घोषणा	पूर्णांकel_quark_x1000_insnreg01	hostpc

/* Maximum usable threshold value is 0x7f dwords क्रम both IN and OUT */
#घोषणा INTEL_QUARK_X1000_EHCI_MAX_THRESHOLD	0x007f007f

/* called after घातerup, by probe or प्रणाली-pm "wakeup" */
अटल पूर्णांक ehci_pci_reinit(काष्ठा ehci_hcd *ehci, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक			retval;

	/* we expect अटल quirk code to handle the "extended capabilities"
	 * (currently just BIOS hanकरोff) allowed starting with EHCI 0.96
	 */

	/* PCI Memory-Write-Invalidate cycle support is optional (uncommon) */
	retval = pci_set_mwi(pdev);
	अगर (!retval)
		ehci_dbg(ehci, "MWI active\n");

	/* Reset the threshold limit */
	अगर (is_पूर्णांकel_quark_x1000(pdev)) अणु
		/*
		 * For the Intel QUARK X1000, उठाओ the I/O threshold to the
		 * maximum usable value in order to improve perक्रमmance.
		 */
		ehci_ग_लिखोl(ehci, INTEL_QUARK_X1000_EHCI_MAX_THRESHOLD,
			ehci->regs->पूर्णांकel_quark_x1000_insnreg01);
	पूर्ण

	वापस 0;
पूर्ण

/* called during probe() after chip reset completes */
अटल पूर्णांक ehci_pci_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	काष्ठा pci_dev		*pdev = to_pci_dev(hcd->self.controller);
	u32			temp;
	पूर्णांक			retval;

	ehci->caps = hcd->regs;

	/*
	 * ehci_init() causes memory क्रम DMA transfers to be
	 * allocated.  Thus, any venकरोr-specअगरic workarounds based on
	 * limiting the type of memory used क्रम DMA transfers must
	 * happen beक्रमe ehci_setup() is called.
	 *
	 * Most other workarounds can be करोne either beक्रमe or after
	 * init and reset; they are located here too.
	 */
	चयन (pdev->venकरोr) अणु
	हाल PCI_VENDOR_ID_TOSHIBA_2:
		/* celleb's companion chip */
		अगर (pdev->device == 0x01b5) अणु
#अगर_घोषित CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
			ehci->big_endian_mmio = 1;
#अन्यथा
			ehci_warn(ehci,
				  "unsupported big endian Toshiba quirk\n");
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_NVIDIA:
		/* NVidia reports that certain chips करोn't handle
		 * QH, ITD, or SITD addresses above 2GB.  (But TD,
		 * data buffer, and periodic schedule are normal.)
		 */
		चयन (pdev->device) अणु
		हाल 0x003c:	/* MCP04 */
		हाल 0x005b:	/* CK804 */
		हाल 0x00d8:	/* CK8 */
		हाल 0x00e8:	/* CK8S */
			अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(31)) < 0)
				ehci_warn(ehci, "can't enable NVidia "
					"workaround for >2GB RAM\n");
			अवरोध;

		/* Some NForce2 chips have problems with selective suspend;
		 * fixed in newer silicon.
		 */
		हाल 0x0068:
			अगर (pdev->revision < 0xa4)
				ehci->no_selective_suspend = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_INTEL:
		अगर (pdev->device == PCI_DEVICE_ID_INTEL_CE4100_USB)
			hcd->has_tt = 1;
		अवरोध;
	हाल PCI_VENDOR_ID_TDI:
		अगर (pdev->device == PCI_DEVICE_ID_TDI_EHCI)
			hcd->has_tt = 1;
		अवरोध;
	हाल PCI_VENDOR_ID_AMD:
		/* AMD PLL quirk */
		अगर (usb_amd_quirk_pll_check())
			ehci->amd_pll_fix = 1;
		/* AMD8111 EHCI करोesn't work, according to AMD errata */
		अगर (pdev->device == 0x7463) अणु
			ehci_info(ehci, "ignoring AMD8111 (errata)\n");
			retval = -EIO;
			जाओ करोne;
		पूर्ण

		/*
		 * EHCI controller on AMD SB700/SB800/Hudson-2/3 platक्रमms may
		 * पढ़ो/ग_लिखो memory space which करोes not beदीर्घ to it when
		 * there is शून्य poपूर्णांकer with T-bit set to 1 in the frame list
		 * table. To aव्योम the issue, the frame list link poपूर्णांकer
		 * should always contain a valid poपूर्णांकer to a inactive qh.
		 */
		अगर (pdev->device == 0x7808) अणु
			ehci->use_dummy_qh = 1;
			ehci_info(ehci, "applying AMD SB700/SB800/Hudson-2/3 EHCI dummy qh workaround\n");
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_VIA:
		अगर (pdev->device == 0x3104 && (pdev->revision & 0xf0) == 0x60) अणु
			u8 पंचांगp;

			/* The VT6212 शेषs to a 1 usec EHCI sleep समय which
			 * hogs the PCI bus *badly*. Setting bit 5 of 0x4B makes
			 * that sleep समय use the conventional 10 usec.
			 */
			pci_पढ़ो_config_byte(pdev, 0x4b, &पंचांगp);
			अगर (पंचांगp & 0x20)
				अवरोध;
			pci_ग_लिखो_config_byte(pdev, 0x4b, पंचांगp | 0x20);
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_ATI:
		/* AMD PLL quirk */
		अगर (usb_amd_quirk_pll_check())
			ehci->amd_pll_fix = 1;

		/*
		 * EHCI controller on AMD SB700/SB800/Hudson-2/3 platक्रमms may
		 * पढ़ो/ग_लिखो memory space which करोes not beदीर्घ to it when
		 * there is शून्य poपूर्णांकer with T-bit set to 1 in the frame list
		 * table. To aव्योम the issue, the frame list link poपूर्णांकer
		 * should always contain a valid poपूर्णांकer to a inactive qh.
		 */
		अगर (pdev->device == 0x4396) अणु
			ehci->use_dummy_qh = 1;
			ehci_info(ehci, "applying AMD SB700/SB800/Hudson-2/3 EHCI dummy qh workaround\n");
		पूर्ण
		/* SB600 and old version of SB700 have a bug in EHCI controller,
		 * which causes usb devices lose response in some हालs.
		 */
		अगर ((pdev->device == 0x4386 || pdev->device == 0x4396) &&
				usb_amd_hang_symptom_quirk()) अणु
			u8 पंचांगp;
			ehci_info(ehci, "applying AMD SB600/SB700 USB freeze workaround\n");
			pci_पढ़ो_config_byte(pdev, 0x53, &पंचांगp);
			pci_ग_लिखो_config_byte(pdev, 0x53, पंचांगp | (1<<3));
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_NETMOS:
		/* MosChip frame-index-रेजिस्टर bug */
		ehci_info(ehci, "applying MosChip frame-index workaround\n");
		ehci->frame_index_bug = 1;
		अवरोध;
	हाल PCI_VENDOR_ID_HUAWEI:
		/* Synopsys HC bug */
		अगर (pdev->device == 0xa239) अणु
			ehci_info(ehci, "applying Synopsys HC workaround\n");
			ehci->has_synopsys_hc_bug = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	/* optional debug port, normally in the first BAR */
	temp = pci_find_capability(pdev, PCI_CAP_ID_DBG);
	अगर (temp) अणु
		pci_पढ़ो_config_dword(pdev, temp, &temp);
		temp >>= 16;
		अगर (((temp >> 13) & 7) == 1) अणु
			u32 hcs_params = ehci_पढ़ोl(ehci,
						    &ehci->caps->hcs_params);

			temp &= 0x1fff;
			ehci->debug = hcd->regs + temp;
			temp = ehci_पढ़ोl(ehci, &ehci->debug->control);
			ehci_info(ehci, "debug port %d%s\n",
				  HCS_DEBUG_PORT(hcs_params),
				  (temp & DBGP_ENABLED) ? " IN USE" : "");
			अगर (!(temp & DBGP_ENABLED))
				ehci->debug = शून्य;
		पूर्ण
	पूर्ण

	retval = ehci_setup(hcd);
	अगर (retval)
		वापस retval;

	/* These workarounds need to be applied after ehci_setup() */
	चयन (pdev->venकरोr) अणु
	हाल PCI_VENDOR_ID_NEC:
	हाल PCI_VENDOR_ID_INTEL:
	हाल PCI_VENDOR_ID_AMD:
		ehci->need_io_watchकरोg = 0;
		अवरोध;
	हाल PCI_VENDOR_ID_NVIDIA:
		चयन (pdev->device) अणु
		/* MCP89 chips on the MacBookAir3,1 give EPROTO when
		 * fetching device descriptors unless LPM is disabled.
		 * There are also पूर्णांकermittent problems क्रमागतerating
		 * devices with PPCD enabled.
		 */
		हाल 0x0d9d:
			ehci_info(ehci, "disable ppcd for nvidia mcp89\n");
			ehci->has_ppcd = 0;
			ehci->command &= ~CMD_PPCEE;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/* at least the Genesys GL880S needs fixup here */
	temp = HCS_N_CC(ehci->hcs_params) * HCS_N_PCC(ehci->hcs_params);
	temp &= 0x0f;
	अगर (temp && HCS_N_PORTS(ehci->hcs_params) > temp) अणु
		ehci_dbg(ehci, "bogus port configuration: "
			"cc=%d x pcc=%d < ports=%d\n",
			HCS_N_CC(ehci->hcs_params),
			HCS_N_PCC(ehci->hcs_params),
			HCS_N_PORTS(ehci->hcs_params));

		चयन (pdev->venकरोr) अणु
		हाल 0x17a0:		/* GENESYS */
			/* GL880S: should be PORTS=2 */
			temp |= (ehci->hcs_params & ~0xf);
			ehci->hcs_params = temp;
			अवरोध;
		हाल PCI_VENDOR_ID_NVIDIA:
			/* NF4: should be PCC=10 */
			अवरोध;
		पूर्ण
	पूर्ण

	/* Serial Bus Release Number is at PCI 0x60 offset */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_STMICRO
	    && pdev->device == PCI_DEVICE_ID_STMICRO_USB_HOST)
		;	/* ConneXT has no sbrn रेजिस्टर */
	अन्यथा अगर (pdev->venकरोr == PCI_VENDOR_ID_HUAWEI
			 && pdev->device == 0xa239)
		;	/* HUAWEI Kunpeng920 USB EHCI has no sbrn रेजिस्टर */
	अन्यथा
		pci_पढ़ो_config_byte(pdev, 0x60, &ehci->sbrn);

	/* Keep this around क्रम a जबतक just in हाल some EHCI
	 * implementation uses legacy PCI PM support.  This test
	 * can be हटाओd on 17 Dec 2009 अगर the dev_warn() hasn't
	 * been triggered by then.
	 */
	अगर (!device_can_wakeup(&pdev->dev)) अणु
		u16	port_wake;

		pci_पढ़ो_config_word(pdev, 0x62, &port_wake);
		अगर (port_wake & 0x0001) अणु
			dev_warn(&pdev->dev, "Enabling legacy PCI PM\n");
			device_set_wakeup_capable(&pdev->dev, 1);
		पूर्ण
	पूर्ण

#अगर_घोषित	CONFIG_PM
	अगर (ehci->no_selective_suspend && device_can_wakeup(&pdev->dev))
		ehci_warn(ehci, "selective suspend/wakeup unavailable\n");
#पूर्ण_अगर

	retval = ehci_pci_reinit(ehci, pdev);
करोne:
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_PM

/* suspend/resume, section 4.3 */

/* These routines rely on the PCI bus glue
 * to handle घातerकरोwn and wakeup, and currently also on
 * transceivers that करोn't need any software attention to set up
 * the right sort of wakeup.
 * Also they depend on separate root hub suspend/resume.
 */

अटल पूर्णांक ehci_pci_resume(काष्ठा usb_hcd *hcd, bool hibernated)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	काष्ठा pci_dev		*pdev = to_pci_dev(hcd->self.controller);

	अगर (ehci_resume(hcd, hibernated) != 0)
		(व्योम) ehci_pci_reinit(ehci, pdev);
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा ehci_suspend		शून्य
#घोषणा ehci_pci_resume		शून्य
#पूर्ण_अगर	/* CONFIG_PM */

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_pci_hc_driver;

अटल स्थिर काष्ठा ehci_driver_overrides pci_overrides __initस्थिर = अणु
	.reset =		ehci_pci_setup,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ehci_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अगर (is_bypassed_id(pdev))
		वापस -ENODEV;
	वापस usb_hcd_pci_probe(pdev, id, &ehci_pci_hc_driver);
पूर्ण

अटल व्योम ehci_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	pci_clear_mwi(pdev);
	usb_hcd_pci_हटाओ(pdev);
पूर्ण

/* PCI driver selection metadata; PCI hotplugging uses this */
अटल स्थिर काष्ठा pci_device_id pci_ids [] = अणु अणु
	/* handle any USB 2.0 EHCI controller */
	PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_USB_EHCI, ~0),
	पूर्ण, अणु
	PCI_VDEVICE(STMICRO, PCI_DEVICE_ID_STMICRO_USB_HOST),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

/* pci driver glue; this is a "new style" PCI driver module */
अटल काष्ठा pci_driver ehci_pci_driver = अणु
	.name =		hcd_name,
	.id_table =	pci_ids,

	.probe =	ehci_pci_probe,
	.हटाओ =	ehci_pci_हटाओ,
	.shutकरोwn = 	usb_hcd_pci_shutकरोwn,

#अगर_घोषित CONFIG_PM
	.driver =	अणु
		.pm =	&usb_hcd_pci_pm_ops
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init ehci_pci_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ehci_init_driver(&ehci_pci_hc_driver, &pci_overrides);

	/* Entries क्रम the PCI suspend/resume callbacks are special */
	ehci_pci_hc_driver.pci_suspend = ehci_suspend;
	ehci_pci_hc_driver.pci_resume = ehci_pci_resume;

	वापस pci_रेजिस्टर_driver(&ehci_pci_driver);
पूर्ण
module_init(ehci_pci_init);

अटल व्योम __निकास ehci_pci_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ehci_pci_driver);
पूर्ण
module_निकास(ehci_pci_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("David Brownell");
MODULE_AUTHOR("Alan Stern");
MODULE_LICENSE("GPL");
