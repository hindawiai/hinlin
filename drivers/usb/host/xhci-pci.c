<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver PCI Bus Glue.
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/reset.h>

#समावेश "xhci.h"
#समावेश "xhci-trace.h"
#समावेश "xhci-pci.h"

#घोषणा SSIC_PORT_NUM		2
#घोषणा SSIC_PORT_CFG2		0x880c
#घोषणा SSIC_PORT_CFG2_OFFSET	0x30
#घोषणा PROG_DONE		(1 << 30)
#घोषणा SSIC_PORT_UNUSED	(1 << 31)
#घोषणा SPARSE_DISABLE_BIT	17
#घोषणा SPARSE_CNTL_ENABLE	0xC12C

/* Device क्रम a quirk */
#घोषणा PCI_VENDOR_ID_FRESCO_LOGIC	0x1b73
#घोषणा PCI_DEVICE_ID_FRESCO_LOGIC_PDK	0x1000
#घोषणा PCI_DEVICE_ID_FRESCO_LOGIC_FL1009	0x1009
#घोषणा PCI_DEVICE_ID_FRESCO_LOGIC_FL1400	0x1400

#घोषणा PCI_VENDOR_ID_ETRON		0x1b6f
#घोषणा PCI_DEVICE_ID_EJ168		0x7023

#घोषणा PCI_DEVICE_ID_INTEL_LYNXPOINT_XHCI	0x8c31
#घोषणा PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_XHCI	0x9c31
#घोषणा PCI_DEVICE_ID_INTEL_WILDCATPOINT_LP_XHCI	0x9cb1
#घोषणा PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI		0x22b5
#घोषणा PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_XHCI		0xa12f
#घोषणा PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI	0x9d2f
#घोषणा PCI_DEVICE_ID_INTEL_BROXTON_M_XHCI		0x0aa8
#घोषणा PCI_DEVICE_ID_INTEL_BROXTON_B_XHCI		0x1aa8
#घोषणा PCI_DEVICE_ID_INTEL_APL_XHCI			0x5aa8
#घोषणा PCI_DEVICE_ID_INTEL_DNV_XHCI			0x19d0
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_XHCI	0x15b5
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_XHCI	0x15b6
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_XHCI	0x15c1
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_XHCI	0x15db
#घोषणा PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_XHCI	0x15d4
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_XHCI		0x15e9
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_XHCI		0x15ec
#घोषणा PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_XHCI		0x15f0
#घोषणा PCI_DEVICE_ID_INTEL_ICE_LAKE_XHCI		0x8a13
#घोषणा PCI_DEVICE_ID_INTEL_CML_XHCI			0xa3af
#घोषणा PCI_DEVICE_ID_INTEL_TIGER_LAKE_XHCI		0x9a13
#घोषणा PCI_DEVICE_ID_INTEL_MAPLE_RIDGE_XHCI		0x1138
#घोषणा PCI_DEVICE_ID_INTEL_ALDER_LAKE_XHCI		0x461e

#घोषणा PCI_DEVICE_ID_AMD_RENOIR_XHCI			0x1639
#घोषणा PCI_DEVICE_ID_AMD_PROMONTORYA_4			0x43b9
#घोषणा PCI_DEVICE_ID_AMD_PROMONTORYA_3			0x43ba
#घोषणा PCI_DEVICE_ID_AMD_PROMONTORYA_2			0x43bb
#घोषणा PCI_DEVICE_ID_AMD_PROMONTORYA_1			0x43bc
#घोषणा PCI_DEVICE_ID_ASMEDIA_1042_XHCI			0x1042
#घोषणा PCI_DEVICE_ID_ASMEDIA_1042A_XHCI		0x1142
#घोषणा PCI_DEVICE_ID_ASMEDIA_1142_XHCI			0x1242
#घोषणा PCI_DEVICE_ID_ASMEDIA_2142_XHCI			0x2142
#घोषणा PCI_DEVICE_ID_ASMEDIA_3242_XHCI			0x3242

अटल स्थिर अक्षर hcd_name[] = "xhci_hcd";

अटल काष्ठा hc_driver __पढ़ो_mostly xhci_pci_hc_driver;

अटल पूर्णांक xhci_pci_setup(काष्ठा usb_hcd *hcd);

अटल स्थिर काष्ठा xhci_driver_overrides xhci_pci_overrides __initस्थिर = अणु
	.reset = xhci_pci_setup,
पूर्ण;

/* called after घातerup, by probe or प्रणाली-pm "wakeup" */
अटल पूर्णांक xhci_pci_reinit(काष्ठा xhci_hcd *xhci, काष्ठा pci_dev *pdev)
अणु
	/*
	 * TODO: Implement finding debug ports later.
	 * TODO: see अगर there are any quirks that need to be added to handle
	 * new extended capabilities.
	 */

	/* PCI Memory-Write-Invalidate cycle support is optional (uncommon) */
	अगर (!pci_set_mwi(pdev))
		xhci_dbg(xhci, "MWI active\n");

	xhci_dbg(xhci, "Finished xhci_pci_reinit\n");
	वापस 0;
पूर्ण

अटल व्योम xhci_pci_quirks(काष्ठा device *dev, काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा pci_dev                  *pdev = to_pci_dev(dev);
	काष्ठा xhci_driver_data         *driver_data;
	स्थिर काष्ठा pci_device_id      *id;

	id = pci_match_id(pdev->driver->id_table, pdev);

	अगर (id && id->driver_data) अणु
		driver_data = (काष्ठा xhci_driver_data *)id->driver_data;
		xhci->quirks |= driver_data->quirks;
	पूर्ण

	/* Look क्रम venकरोr-specअगरic quirks */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_FRESCO_LOGIC &&
			(pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK ||
			 pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_FL1400)) अणु
		अगर (pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK &&
				pdev->revision == 0x0) अणु
			xhci->quirks |= XHCI_RESET_EP_QUIRK;
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Fresco Logic xHC needs configure"
				" endpoint cmd after reset endpoint");
		पूर्ण
		अगर (pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK &&
				pdev->revision == 0x4) अणु
			xhci->quirks |= XHCI_SLOW_SUSPEND;
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Fresco Logic xHC revision %u"
				"must be suspended extra slowly",
				pdev->revision);
		पूर्ण
		अगर (pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_PDK)
			xhci->quirks |= XHCI_BROKEN_STREAMS;
		/* Fresco Logic confirms: all revisions of this chip करो not
		 * support MSI, even though some of them claim to in their PCI
		 * capabilities.
		 */
		xhci->quirks |= XHCI_BROKEN_MSI;
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Fresco Logic revision %u "
				"has broken MSI implementation",
				pdev->revision);
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
	पूर्ण

	अगर (pdev->venकरोr == PCI_VENDOR_ID_FRESCO_LOGIC &&
			pdev->device == PCI_DEVICE_ID_FRESCO_LOGIC_FL1009)
		xhci->quirks |= XHCI_BROKEN_STREAMS;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_NEC)
		xhci->quirks |= XHCI_NEC_HOST;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD && xhci->hci_version == 0x96)
		xhci->quirks |= XHCI_AMD_0x96_HOST;

	/* AMD PLL quirk */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD && usb_amd_quirk_pll_check())
		xhci->quirks |= XHCI_AMD_PLL_FIX;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD &&
		(pdev->device == 0x145c ||
		 pdev->device == 0x15e0 ||
		 pdev->device == 0x15e1 ||
		 pdev->device == 0x43bb))
		xhci->quirks |= XHCI_SUSPEND_DELAY;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD &&
	    (pdev->device == 0x15e0 || pdev->device == 0x15e1))
		xhci->quirks |= XHCI_SNPS_BROKEN_SUSPEND;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD && pdev->device == 0x15e5) अणु
		xhci->quirks |= XHCI_DISABLE_SPARSE;
		xhci->quirks |= XHCI_RESET_ON_RESUME;
	पूर्ण

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD)
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;

	अगर ((pdev->venकरोr == PCI_VENDOR_ID_AMD) &&
		((pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_4) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_3) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_2) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_1)))
		xhci->quirks |= XHCI_U2_DISABLE_WAKE;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD &&
		pdev->device == PCI_DEVICE_ID_AMD_RENOIR_XHCI)
		xhci->quirks |= XHCI_BROKEN_D3COLD;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL) अणु
		xhci->quirks |= XHCI_LPM_SUPPORT;
		xhci->quirks |= XHCI_INTEL_HOST;
		xhci->quirks |= XHCI_AVOID_BEI;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
			pdev->device == PCI_DEVICE_ID_INTEL_PANTHERPOINT_XHCI) अणु
		xhci->quirks |= XHCI_EP_LIMIT_QUIRK;
		xhci->limit_active_eps = 64;
		xhci->quirks |= XHCI_SW_BW_CHECKING;
		/*
		 * PPT desktop boards DH77EB and DH77DF will घातer back on after
		 * a few seconds of being shutकरोwn.  The fix क्रम this is to
		 * चयन the ports from xHCI to EHCI on shutकरोwn.  We can't use
		 * DMI inक्रमmation to find those particular boards (since each
		 * venकरोr will change the board name), so we have to key off all
		 * PPT chipsets.
		 */
		xhci->quirks |= XHCI_SPURIOUS_REBOOT;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
		(pdev->device == PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_WILDCATPOINT_LP_XHCI)) अणु
		xhci->quirks |= XHCI_SPURIOUS_REBOOT;
		xhci->quirks |= XHCI_SPURIOUS_WAKEUP;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
		(pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_BROXTON_M_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_BROXTON_B_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_APL_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_DNV_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEL_CML_XHCI)) अणु
		xhci->quirks |= XHCI_PME_STUCK_QUIRK;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
	    pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI)
		xhci->quirks |= XHCI_SSIC_PORT_UNUSED;
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_APL_XHCI))
		xhci->quirks |= XHCI_INTEL_USB_ROLE_SW;
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_APL_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_DNV_XHCI))
		xhci->quirks |= XHCI_MISSING_CAS;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ICE_LAKE_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_TIGER_LAKE_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_MAPLE_RIDGE_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEL_ALDER_LAKE_XHCI))
		xhci->quirks |= XHCI_DEFAULT_PM_RUNTIME_ALLOW;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_ETRON &&
			pdev->device == PCI_DEVICE_ID_EJ168) अणु
		xhci->quirks |= XHCI_RESET_ON_RESUME;
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
		xhci->quirks |= XHCI_BROKEN_STREAMS;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_RENESAS &&
	    pdev->device == 0x0014) अणु
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
		xhci->quirks |= XHCI_ZERO_64B_REGS;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_RENESAS &&
	    pdev->device == 0x0015) अणु
		xhci->quirks |= XHCI_RESET_ON_RESUME;
		xhci->quirks |= XHCI_ZERO_64B_REGS;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_VIA)
		xhci->quirks |= XHCI_RESET_ON_RESUME;

	/* See https://bugzilla.kernel.org/show_bug.cgi?id=79511 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_VIA &&
			pdev->device == 0x3432)
		xhci->quirks |= XHCI_BROKEN_STREAMS;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_VIA && pdev->device == 0x3483)
		xhci->quirks |= XHCI_LPM_SUPPORT;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_ASMEDIA &&
		pdev->device == PCI_DEVICE_ID_ASMEDIA_1042_XHCI)
		xhci->quirks |= XHCI_BROKEN_STREAMS;
	अगर (pdev->venकरोr == PCI_VENDOR_ID_ASMEDIA &&
		pdev->device == PCI_DEVICE_ID_ASMEDIA_1042A_XHCI) अणु
		xhci->quirks |= XHCI_TRUST_TX_LENGTH;
		xhci->quirks |= XHCI_NO_64BIT_SUPPORT;
	पूर्ण
	अगर (pdev->venकरोr == PCI_VENDOR_ID_ASMEDIA &&
	    (pdev->device == PCI_DEVICE_ID_ASMEDIA_1142_XHCI ||
	     pdev->device == PCI_DEVICE_ID_ASMEDIA_2142_XHCI ||
	     pdev->device == PCI_DEVICE_ID_ASMEDIA_3242_XHCI))
		xhci->quirks |= XHCI_NO_64BIT_SUPPORT;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_ASMEDIA &&
		pdev->device == PCI_DEVICE_ID_ASMEDIA_1042A_XHCI)
		xhci->quirks |= XHCI_ASMEDIA_MODIFY_FLOWCONTROL;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_TI && pdev->device == 0x8241)
		xhci->quirks |= XHCI_LIMIT_ENDPOINT_INTERVAL_7;

	अगर ((pdev->venकरोr == PCI_VENDOR_ID_BROADCOM ||
	     pdev->venकरोr == PCI_VENDOR_ID_CAVIUM) &&
	     pdev->device == 0x9026)
		xhci->quirks |= XHCI_RESET_PLL_ON_DISCONNECT;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD &&
	    (pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_2 ||
	     pdev->device == PCI_DEVICE_ID_AMD_PROMONTORYA_4))
		xhci->quirks |= XHCI_NO_SOFT_RETRY;

	अगर (xhci->quirks & XHCI_RESET_ON_RESUME)
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Resetting on resume");
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल व्योम xhci_pme_acpi_rtd3_enable(काष्ठा pci_dev *dev)
अणु
	अटल स्थिर guid_t पूर्णांकel_dsm_guid =
		GUID_INIT(0xac340cb7, 0xe901, 0x45bf,
			  0xb7, 0xe6, 0x2b, 0x34, 0xec, 0x93, 0x1e, 0x23);
	जोड़ acpi_object *obj;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(&dev->dev), &पूर्णांकel_dsm_guid, 3, 1,
				शून्य);
	ACPI_FREE(obj);
पूर्ण
#अन्यथा
अटल व्योम xhci_pme_acpi_rtd3_enable(काष्ठा pci_dev *dev) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

/* called during probe() after chip reset completes */
अटल पूर्णांक xhci_pci_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd		*xhci;
	काष्ठा pci_dev		*pdev = to_pci_dev(hcd->self.controller);
	पूर्णांक			retval;

	xhci = hcd_to_xhci(hcd);
	अगर (!xhci->sbrn)
		pci_पढ़ो_config_byte(pdev, XHCI_SBRN_OFFSET, &xhci->sbrn);

	/* imod_पूर्णांकerval is the पूर्णांकerrupt moderation value in nanoseconds. */
	xhci->imod_पूर्णांकerval = 40000;

	retval = xhci_gen_setup(hcd, xhci_pci_quirks);
	अगर (retval)
		वापस retval;

	अगर (!usb_hcd_is_primary_hcd(hcd))
		वापस 0;

	अगर (xhci->quirks & XHCI_PME_STUCK_QUIRK)
		xhci_pme_acpi_rtd3_enable(pdev);

	xhci_dbg(xhci, "Got SBRN %u\n", (अचिन्हित पूर्णांक) xhci->sbrn);

	/* Find any debug ports */
	वापस xhci_pci_reinit(xhci, pdev);
पूर्ण

/*
 * We need to रेजिस्टर our own PCI probe function (instead of the USB core's
 * function) in order to create a second roothub under xHCI.
 */
अटल पूर्णांक xhci_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक retval;
	काष्ठा xhci_hcd *xhci;
	काष्ठा usb_hcd *hcd;
	काष्ठा xhci_driver_data *driver_data;
	काष्ठा reset_control *reset;

	driver_data = (काष्ठा xhci_driver_data *)id->driver_data;
	अगर (driver_data && driver_data->quirks & XHCI_RENESAS_FW_QUIRK) अणु
		retval = renesas_xhci_check_request_fw(dev, id);
		अगर (retval)
			वापस retval;
	पूर्ण

	reset = devm_reset_control_get_optional_exclusive(&dev->dev, शून्य);
	अगर (IS_ERR(reset))
		वापस PTR_ERR(reset);
	reset_control_reset(reset);

	/* Prevent runसमय suspending between USB-2 and USB-3 initialization */
	pm_runसमय_get_noresume(&dev->dev);

	/* Register the USB 2.0 roothub.
	 * FIXME: USB core must know to रेजिस्टर the USB 2.0 roothub first.
	 * This is sort of silly, because we could just set the HCD driver flags
	 * to say USB 2.0, but I'm not sure what the implications would be in
	 * the other parts of the HCD code.
	 */
	retval = usb_hcd_pci_probe(dev, id, &xhci_pci_hc_driver);

	अगर (retval)
		जाओ put_runसमय_pm;

	/* USB 2.0 roothub is stored in the PCI device now. */
	hcd = dev_get_drvdata(&dev->dev);
	xhci = hcd_to_xhci(hcd);
	xhci->reset = reset;
	xhci->shared_hcd = usb_create_shared_hcd(&xhci_pci_hc_driver, &dev->dev,
						 pci_name(dev), hcd);
	अगर (!xhci->shared_hcd) अणु
		retval = -ENOMEM;
		जाओ dealloc_usb2_hcd;
	पूर्ण

	retval = xhci_ext_cap_init(xhci);
	अगर (retval)
		जाओ put_usb3_hcd;

	retval = usb_add_hcd(xhci->shared_hcd, dev->irq,
			IRQF_SHARED);
	अगर (retval)
		जाओ put_usb3_hcd;
	/* Roothub alपढ़ोy marked as USB 3.0 speed */

	अगर (!(xhci->quirks & XHCI_BROKEN_STREAMS) &&
			HCC_MAX_PSA(xhci->hcc_params) >= 4)
		xhci->shared_hcd->can_करो_streams = 1;

	/* USB-2 and USB-3 roothubs initialized, allow runसमय pm suspend */
	pm_runसमय_put_noidle(&dev->dev);

	अगर (xhci->quirks & XHCI_DEFAULT_PM_RUNTIME_ALLOW)
		pm_runसमय_allow(&dev->dev);

	वापस 0;

put_usb3_hcd:
	usb_put_hcd(xhci->shared_hcd);
dealloc_usb2_hcd:
	usb_hcd_pci_हटाओ(dev);
put_runसमय_pm:
	pm_runसमय_put_noidle(&dev->dev);
	वापस retval;
पूर्ण

अटल व्योम xhci_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा xhci_hcd *xhci;

	xhci = hcd_to_xhci(pci_get_drvdata(dev));
	अगर (xhci->quirks & XHCI_RENESAS_FW_QUIRK)
		renesas_xhci_pci_निकास(dev);

	xhci->xhc_state |= XHCI_STATE_REMOVING;

	अगर (xhci->quirks & XHCI_DEFAULT_PM_RUNTIME_ALLOW)
		pm_runसमय_क्रमbid(&dev->dev);

	अगर (xhci->shared_hcd) अणु
		usb_हटाओ_hcd(xhci->shared_hcd);
		usb_put_hcd(xhci->shared_hcd);
		xhci->shared_hcd = शून्य;
	पूर्ण

	/* Workaround क्रम spurious wakeups at shutकरोwn with HSW */
	अगर (xhci->quirks & XHCI_SPURIOUS_WAKEUP)
		pci_set_घातer_state(dev, PCI_D3hot);

	usb_hcd_pci_हटाओ(dev);
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * In some Intel xHCI controllers, in order to get D3 working,
 * through a venकरोr specअगरic SSIC CONFIG रेजिस्टर at offset 0x883c,
 * SSIC PORT need to be marked as "unused" beक्रमe putting xHCI
 * पूर्णांकo D3. After D3 निकास, the SSIC port need to be marked as "used".
 * Without this change, xHCI might not enter D3 state.
 */
अटल व्योम xhci_ssic_port_unused_quirk(काष्ठा usb_hcd *hcd, bool suspend)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	u32 val;
	व्योम __iomem *reg;
	पूर्णांक i;

	क्रम (i = 0; i < SSIC_PORT_NUM; i++) अणु
		reg = (व्योम __iomem *) xhci->cap_regs +
				SSIC_PORT_CFG2 +
				i * SSIC_PORT_CFG2_OFFSET;

		/* Notअगरy SSIC that SSIC profile programming is not करोne. */
		val = पढ़ोl(reg) & ~PROG_DONE;
		ग_लिखोl(val, reg);

		/* Mark SSIC port as unused(suspend) or used(resume) */
		val = पढ़ोl(reg);
		अगर (suspend)
			val |= SSIC_PORT_UNUSED;
		अन्यथा
			val &= ~SSIC_PORT_UNUSED;
		ग_लिखोl(val, reg);

		/* Notअगरy SSIC that SSIC profile programming is करोne */
		val = पढ़ोl(reg) | PROG_DONE;
		ग_लिखोl(val, reg);
		पढ़ोl(reg);
	पूर्ण
पूर्ण

/*
 * Make sure PME works on some Intel xHCI controllers by writing 1 to clear
 * the Internal PME flag bit in venकरोr specअगरic PMCTRL रेजिस्टर at offset 0x80a4
 */
अटल व्योम xhci_pme_quirk(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	व्योम __iomem *reg;
	u32 val;

	reg = (व्योम __iomem *) xhci->cap_regs + 0x80a4;
	val = पढ़ोl(reg);
	ग_लिखोl(val | BIT(28), reg);
	पढ़ोl(reg);
पूर्ण

अटल व्योम xhci_sparse_control_quirk(काष्ठा usb_hcd *hcd)
अणु
	u32 reg;

	reg = पढ़ोl(hcd->regs + SPARSE_CNTL_ENABLE);
	reg &= ~BIT(SPARSE_DISABLE_BIT);
	ग_लिखोl(reg, hcd->regs + SPARSE_CNTL_ENABLE);
पूर्ण

अटल पूर्णांक xhci_pci_suspend(काष्ठा usb_hcd *hcd, bool करो_wakeup)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	काष्ठा pci_dev		*pdev = to_pci_dev(hcd->self.controller);
	पूर्णांक			ret;

	/*
	 * Systems with the TI redriver that loses port status change events
	 * need to have the रेजिस्टरs polled during D3, so aव्योम D3cold.
	 */
	अगर (xhci->quirks & (XHCI_COMP_MODE_QUIRK | XHCI_BROKEN_D3COLD))
		pci_d3cold_disable(pdev);

	अगर (xhci->quirks & XHCI_PME_STUCK_QUIRK)
		xhci_pme_quirk(hcd);

	अगर (xhci->quirks & XHCI_SSIC_PORT_UNUSED)
		xhci_ssic_port_unused_quirk(hcd, true);

	अगर (xhci->quirks & XHCI_DISABLE_SPARSE)
		xhci_sparse_control_quirk(hcd);

	ret = xhci_suspend(xhci, करो_wakeup);
	अगर (ret && (xhci->quirks & XHCI_SSIC_PORT_UNUSED))
		xhci_ssic_port_unused_quirk(hcd, false);

	वापस ret;
पूर्ण

अटल पूर्णांक xhci_pci_resume(काष्ठा usb_hcd *hcd, bool hibernated)
अणु
	काष्ठा xhci_hcd		*xhci = hcd_to_xhci(hcd);
	काष्ठा pci_dev		*pdev = to_pci_dev(hcd->self.controller);
	पूर्णांक			retval = 0;

	reset_control_reset(xhci->reset);

	/* The BIOS on प्रणालीs with the Intel Panther Poपूर्णांक chipset may or may
	 * not support xHCI natively.  That means that during प्रणाली resume, it
	 * may चयन the ports back to EHCI so that users can use their
	 * keyboard to select a kernel from GRUB after resume from hibernate.
	 *
	 * The BIOS is supposed to remember whether the OS had xHCI ports
	 * enabled beक्रमe resume, and चयन the ports back to xHCI when the
	 * BIOS/OS semaphore is written, but we all know we can't trust BIOS
	 * ग_लिखोrs.
	 *
	 * Unconditionally चयन the ports back to xHCI after a प्रणाली resume.
	 * It should not matter whether the EHCI or xHCI controller is
	 * resumed first. It's enough to करो the चयनover in xHCI because
	 * USB core won't notice anything as the hub driver doesn't start
	 * running again until after all the devices (including both EHCI and
	 * xHCI host controllers) have been resumed.
	 */

	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL)
		usb_enable_पूर्णांकel_xhci_ports(pdev);

	अगर (xhci->quirks & XHCI_SSIC_PORT_UNUSED)
		xhci_ssic_port_unused_quirk(hcd, false);

	अगर (xhci->quirks & XHCI_PME_STUCK_QUIRK)
		xhci_pme_quirk(hcd);

	retval = xhci_resume(xhci, hibernated);
	वापस retval;
पूर्ण

अटल व्योम xhci_pci_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd		*xhci = hcd_to_xhci(hcd);
	काष्ठा pci_dev		*pdev = to_pci_dev(hcd->self.controller);

	xhci_shutकरोwn(hcd);

	/* Yet another workaround क्रम spurious wakeups at shutकरोwn with HSW */
	अगर (xhci->quirks & XHCI_SPURIOUS_WAKEUP)
		pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा xhci_driver_data reneses_data = अणु
	.quirks  = XHCI_RENESAS_FW_QUIRK,
	.firmware = "renesas_usb_fw.mem",
पूर्ण;

/* PCI driver selection metadata; PCI hotplugging uses this */
अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	अणु PCI_DEVICE(0x1912, 0x0014),
		.driver_data =  (अचिन्हित दीर्घ)&reneses_data,
	पूर्ण,
	अणु PCI_DEVICE(0x1912, 0x0015),
		.driver_data =  (अचिन्हित दीर्घ)&reneses_data,
	पूर्ण,
	/* handle any USB 3.0 xHCI controller */
	अणु PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_USB_XHCI, ~0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);
MODULE_FIRMWARE("renesas_usb_fw.mem");

/* pci driver glue; this is a "new style" PCI driver module */
अटल काष्ठा pci_driver xhci_pci_driver = अणु
	.name =		hcd_name,
	.id_table =	pci_ids,

	.probe =	xhci_pci_probe,
	.हटाओ =	xhci_pci_हटाओ,
	/* suspend and resume implemented later */

	.shutकरोwn = 	usb_hcd_pci_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.driver = अणु
		.pm = &usb_hcd_pci_pm_ops
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init xhci_pci_init(व्योम)
अणु
	xhci_init_driver(&xhci_pci_hc_driver, &xhci_pci_overrides);
#अगर_घोषित CONFIG_PM
	xhci_pci_hc_driver.pci_suspend = xhci_pci_suspend;
	xhci_pci_hc_driver.pci_resume = xhci_pci_resume;
	xhci_pci_hc_driver.shutकरोwn = xhci_pci_shutकरोwn;
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&xhci_pci_driver);
पूर्ण
module_init(xhci_pci_init);

अटल व्योम __निकास xhci_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&xhci_pci_driver);
पूर्ण
module_निकास(xhci_pci_निकास);

MODULE_DESCRIPTION("xHCI PCI Host Controller Driver");
MODULE_LICENSE("GPL");
