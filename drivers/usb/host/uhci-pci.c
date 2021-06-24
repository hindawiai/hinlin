<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UHCI HCD (Host Controller Driver) PCI Bus Glue.
 *
 * Extracted from uhci-hcd.c:
 * Maपूर्णांकainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * (C) Copyright 1999 Linus Torvalds
 * (C) Copyright 1999-2002 Johannes Erdfelt, johannes@erdfelt.com
 * (C) Copyright 1999 Randy Dunlap
 * (C) Copyright 1999 Georg Acher, acher@in.tum.de
 * (C) Copyright 1999 Deti Fliegl, deti@fliegl.de
 * (C) Copyright 1999 Thomas Sailer, sailer@अगरe.ee.ethz.ch
 * (C) Copyright 1999 Roman Weissgaerber, weissg@vienna.at
 * (C) Copyright 2000 Yggdrasil Computing, Inc. (port of new PCI पूर्णांकerface
 *               support from usb-ohci.c by Adam Richter, adam@yggdrasil.com).
 * (C) Copyright 1999 Gregory P. Smith (from usb-ohci.c)
 * (C) Copyright 2004-2007 Alan Stern, stern@rowland.harvard.edu
 */

#समावेश "pci-quirks.h"

/*
 * Make sure the controller is completely inactive, unable to
 * generate पूर्णांकerrupts or करो DMA.
 */
अटल व्योम uhci_pci_reset_hc(काष्ठा uhci_hcd *uhci)
अणु
	uhci_reset_hc(to_pci_dev(uhci_dev(uhci)), uhci->io_addr);
पूर्ण

/*
 * Initialize a controller that was newly discovered or has just been
 * resumed.  In either हाल we can't be sure of its previous state.
 *
 * Returns: 1 अगर the controller was reset, 0 otherwise.
 */
अटल पूर्णांक uhci_pci_check_and_reset_hc(काष्ठा uhci_hcd *uhci)
अणु
	वापस uhci_check_and_reset_hc(to_pci_dev(uhci_dev(uhci)),
				uhci->io_addr);
पूर्ण

/*
 * Store the basic रेजिस्टर settings needed by the controller.
 * This function is called at the end of configure_hc in uhci-hcd.c.
 */
अटल व्योम uhci_pci_configure_hc(काष्ठा uhci_hcd *uhci)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(uhci_dev(uhci));

	/* Enable PIRQ */
	pci_ग_लिखो_config_word(pdev, USBLEGSUP, USBLEGSUP_DEFAULT);

	/* Disable platक्रमm-specअगरic non-PME# wakeup */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL)
		pci_ग_लिखो_config_byte(pdev, USBRES_INTEL, 0);
पूर्ण

अटल पूर्णांक uhci_pci_resume_detect_पूर्णांकerrupts_are_broken(काष्ठा uhci_hcd *uhci)
अणु
	पूर्णांक port;

	चयन (to_pci_dev(uhci_dev(uhci))->venकरोr) अणु
	शेष:
		अवरोध;

	हाल PCI_VENDOR_ID_GENESYS:
		/* Genesys Logic's GL880S controllers don't generate
		 * resume-detect पूर्णांकerrupts.
		 */
		वापस 1;

	हाल PCI_VENDOR_ID_INTEL:
		/* Some of Intel's USB controllers have a bug that causes
		 * resume-detect पूर्णांकerrupts अगर any port has an over-current
		 * condition.  To make matters worse, some motherboards
		 * hardwire unused USB ports' over-current inमाला_दो active!
		 * To prevent problems, we will not enable resume-detect
		 * पूर्णांकerrupts अगर any ports are OC.
		 */
		क्रम (port = 0; port < uhci->rh_numports; ++port) अणु
			अगर (inw(uhci->io_addr + USBPORTSC1 + port * 2) &
					USBPORTSC_OC)
				वापस 1;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक uhci_pci_global_suspend_mode_is_broken(काष्ठा uhci_hcd *uhci)
अणु
	पूर्णांक port;
	स्थिर अक्षर *sys_info;
	अटल स्थिर अक्षर bad_Asus_board[] = "A7V8X";

	/* One of Asus's motherboards has a bug which causes it to
	 * wake up immediately from suspend-to-RAM अगर any of the ports
	 * are connected.  In such हालs we will not set EGSM.
	 */
	sys_info = dmi_get_प्रणाली_info(DMI_BOARD_NAME);
	अगर (sys_info && !म_भेद(sys_info, bad_Asus_board)) अणु
		क्रम (port = 0; port < uhci->rh_numports; ++port) अणु
			अगर (inw(uhci->io_addr + USBPORTSC1 + port * 2) &
					USBPORTSC_CCS)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uhci_pci_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);

	uhci->io_addr = (अचिन्हित दीर्घ) hcd->rsrc_start;

	uhci->rh_numports = uhci_count_ports(hcd);

	/* Intel controllers report the OverCurrent bit active on.
	 * VIA controllers report it active off, so we'll adjust the
	 * bit value.  (It's not standardized in the UHCI spec.)
	 */
	अगर (to_pci_dev(uhci_dev(uhci))->venकरोr == PCI_VENDOR_ID_VIA)
		uhci->oc_low = 1;

	/* HP's server management chip requires a दीर्घer port reset delay. */
	अगर (to_pci_dev(uhci_dev(uhci))->venकरोr == PCI_VENDOR_ID_HP)
		uhci->रुको_क्रम_hp = 1;

	/* Intel controllers use non-PME wakeup संकेतling */
	अगर (to_pci_dev(uhci_dev(uhci))->venकरोr == PCI_VENDOR_ID_INTEL)
		device_set_wakeup_capable(uhci_dev(uhci), true);

	/* Set up poपूर्णांकers to PCI-specअगरic functions */
	uhci->reset_hc = uhci_pci_reset_hc;
	uhci->check_and_reset_hc = uhci_pci_check_and_reset_hc;
	uhci->configure_hc = uhci_pci_configure_hc;
	uhci->resume_detect_पूर्णांकerrupts_are_broken =
		uhci_pci_resume_detect_पूर्णांकerrupts_are_broken;
	uhci->global_suspend_mode_is_broken =
		uhci_pci_global_suspend_mode_is_broken;


	/* Kick BIOS off this hardware and reset अगर the controller
	 * isn't alपढ़ोy safely quiescent.
	 */
	check_and_reset_hc(uhci);
	वापस 0;
पूर्ण

/* Make sure the controller is quiescent and that we're not using it
 * any more.  This is मुख्यly क्रम the benefit of programs which, like kexec,
 * expect the hardware to be idle: not करोing DMA or generating IRQs.
 *
 * This routine may be called in a damaged or failing kernel.  Hence we
 * करो not acquire the spinlock beक्रमe shutting करोwn the controller.
 */
अटल व्योम uhci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा usb_hcd *hcd = pci_get_drvdata(pdev);

	uhci_hc_died(hcd_to_uhci(hcd));
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक uhci_pci_resume(काष्ठा usb_hcd *hcd, bool hibernated);

अटल पूर्णांक uhci_pci_suspend(काष्ठा usb_hcd *hcd, bool करो_wakeup)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);
	काष्ठा pci_dev *pdev = to_pci_dev(uhci_dev(uhci));
	पूर्णांक rc = 0;

	dev_dbg(uhci_dev(uhci), "%s\n", __func__);

	spin_lock_irq(&uhci->lock);
	अगर (!HCD_HW_ACCESSIBLE(hcd) || uhci->dead)
		जाओ करोne_okay;		/* Alपढ़ोy suspended or dead */

	/* All PCI host controllers are required to disable IRQ generation
	 * at the source, so we must turn off PIRQ.
	 */
	pci_ग_लिखो_config_word(pdev, USBLEGSUP, 0);
	clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

	/* Enable platक्रमm-specअगरic non-PME# wakeup */
	अगर (करो_wakeup) अणु
		अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL)
			pci_ग_लिखो_config_byte(pdev, USBRES_INTEL,
					USBPORT1EN | USBPORT2EN);
	पूर्ण

करोne_okay:
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	spin_unlock_irq(&uhci->lock);

	synchronize_irq(hcd->irq);

	/* Check क्रम race with a wakeup request */
	अगर (करो_wakeup && HCD_WAKEUP_PENDING(hcd)) अणु
		uhci_pci_resume(hcd, false);
		rc = -EBUSY;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक uhci_pci_resume(काष्ठा usb_hcd *hcd, bool hibernated)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);

	dev_dbg(uhci_dev(uhci), "%s\n", __func__);

	/* Since we aren't in D3 any more, it's safe to set this flag
	 * even अगर the controller was dead.
	 */
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	spin_lock_irq(&uhci->lock);

	/* Make sure resume from hibernation re-क्रमागतerates everything */
	अगर (hibernated) अणु
		uhci->reset_hc(uhci);
		finish_reset(uhci);
	पूर्ण

	/* The firmware may have changed the controller settings during
	 * a प्रणाली wakeup.  Check it and reconfigure to aव्योम problems.
	 */
	अन्यथा अणु
		check_and_reset_hc(uhci);
	पूर्ण
	configure_hc(uhci);

	/* Tell the core अगर the controller had to be reset */
	अगर (uhci->rh_state == UHCI_RH_RESET)
		usb_root_hub_lost_घातer(hcd->self.root_hub);

	spin_unlock_irq(&uhci->lock);

	/* If पूर्णांकerrupts करोn't work and remote wakeup is enabled then
	 * the suspended root hub needs to be polled.
	 */
	अगर (!uhci->RD_enable && hcd->self.root_hub->करो_remote_wakeup)
		set_bit(HCD_FLAG_POLL_RH, &hcd->flags);

	/* Does the root hub have a port wakeup pending? */
	usb_hcd_poll_rh_status(hcd);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा hc_driver uhci_driver = अणु
	.description =		hcd_name,
	.product_desc =		"UHCI Host Controller",
	.hcd_priv_size =	माप(काष्ठा uhci_hcd),

	/* Generic hardware linkage */
	.irq =			uhci_irq,
	.flags =		HCD_DMA | HCD_USB11,

	/* Basic lअगरecycle operations */
	.reset =		uhci_pci_init,
	.start =		uhci_start,
#अगर_घोषित CONFIG_PM
	.pci_suspend =		uhci_pci_suspend,
	.pci_resume =		uhci_pci_resume,
	.bus_suspend =		uhci_rh_suspend,
	.bus_resume =		uhci_rh_resume,
#पूर्ण_अगर
	.stop =			uhci_stop,

	.urb_enqueue =		uhci_urb_enqueue,
	.urb_dequeue =		uhci_urb_dequeue,

	.endpoपूर्णांक_disable =	uhci_hcd_endpoपूर्णांक_disable,
	.get_frame_number =	uhci_hcd_get_frame_number,

	.hub_status_data =	uhci_hub_status_data,
	.hub_control =		uhci_hub_control,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id uhci_pci_ids[] = अणु अणु
	/* handle any USB UHCI controller */
	PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_USB_UHCI, ~0),
	पूर्ण, अणु /* end: all zeroes */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, uhci_pci_ids);

अटल पूर्णांक uhci_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस usb_hcd_pci_probe(dev, id, &uhci_driver);
पूर्ण

अटल काष्ठा pci_driver uhci_pci_driver = अणु
	.name =		hcd_name,
	.id_table =	uhci_pci_ids,

	.probe =	uhci_pci_probe,
	.हटाओ =	usb_hcd_pci_हटाओ,
	.shutकरोwn =	uhci_shutकरोwn,

#अगर_घोषित CONFIG_PM
	.driver =	अणु
		.pm =	&usb_hcd_pci_pm_ops
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

MODULE_SOFTDEP("pre: ehci_pci");
